#include <Arduino.h>
#include <esp_display_panel.hpp>
#include <lvgl.h>
#include "lvgl_v8_port.h"
#include <ArduinoJson.h>
#include <Preferences.h>

// Vygenerované UI z EEZ Studia
#include "src/ui/ui.h"
#include "src/ui/screens.h"
#include "src/ui/actions.h"
#include "src/picture/wallpaper.h"

using namespace esp_panel::board;

// Piny expandéru CH422G na desce Waveshare ESP32-S3-Touch-LCD-4.3
#define TP_RST              1
#define LCD_BL              2
#define LCD_RST             3

Board *board = nullptr;
String serialRxBuffer = "";
unsigned long lastStatTimeMs = 0;
bool isBacklightOn = true;

// === OPTIMALIZACE 1: NVS zápisy na Core 0 (neblokují PSRAM DMA pro RGB LCD) ===
static QueueHandle_t nvsWriteQueue = nullptr;

static void nvsWriteTask(void *arg) {
    int screenId;
    while (true) {
        if (xQueueReceive(nvsWriteQueue, &screenId, portMAX_DELAY) == pdTRUE) {
            // Počkáme krátce – seskupí případné rychlé změny obrazovek
            vTaskDelay(pdMS_TO_TICKS(500));
            // Vyprázdníme frontu – vezmeme jen poslední hodnotu
            int latest = screenId;
            while (xQueueReceive(nvsWriteQueue, &latest, 0) == pdTRUE) {}

            Preferences p;
            p.begin("openfront", false);
            if (p.getInt("last_scr", -1) != latest) {
                p.putInt("last_scr", latest);
            }
            p.end();
        }
    }
}

// === OPTIMALIZACE 2: Rate-limiting UI aktualizací ===
static unsigned long lastUiUpdateMs = 0;
static bool uiUpdatePending = false;
#define UI_UPDATE_INTERVAL_MS  200  // Max 5 aktualizací za sekundu

// Struktura pro držení posledních přijatých dat z PC
struct TelemetryState {
    String cpuName = "Waiting for PC...";
    String gpuName = "Waiting for PC...";
    String ramName = "System RAM";
    String diskName = "System Disk";
    String netName = "Network";
    int ramTotalGb = 0;
    int diskTotalGb = 0;

    int pcPowerW = 0;
    int cpuLoad = 0;
    int cpuTemp = 0;
    float cpuFreq = 0.0f;
    int cpuFanRpm = 0;
    int cpuPowerW = 0;

    int gpuLoad = 0;
    int gpuTemp = 0;
    int gpuFreq = 0;
    int gpuFanPct = 0;
    int gpuPowerW = 0;
    int vramUsedMb = 0;
    int vramTotalMb = 0;

    int ramLoad = 0;
    int ramUsedMb = 0;

    int diskUsedPct = 0;
    int diskUsedGb = 0;
    int diskTemp = 0;

    int netDlKbps = 0;
    int netUlKbps = 0;

    String timeStr = "--:--";
    String dateStr = "";
} telemetry;

// Waveshare ESP32-S3-Touch-LCD-4.3 má USB-C vyvedený přes čip CH343 na UART0 (Serial0).
// Pokud je v Arduino IDE zapnuto "USB CDC On Boot: Enabled", objekt 'Serial' míří na interní USB CDC.
// Proto definujeme BoardSerial tak, aby vždy komunikoval přes CH343 (UART0) a zároveň obsluhoval i Serial.
#if ARDUINO_USB_CDC_ON_BOOT
#define BoardSerial Serial0
#else
#define BoardSerial Serial
#endif

// Dopředné deklarace funkcí
void processSerialLine(const String &line);
void updateUiWidgets();
void setBacklight(bool enable);
static void onMainBtnMatrixClick(lv_event_t *e);

// === OPTIMALIZACE 1: NVS zápis přes frontu na Core 0 (neblokuje PSRAM/Flash DMA) ===
extern "C" void persist_screen_selection(enum ScreensEnum screenId) {
    if (nvsWriteQueue != nullptr) {
        int id = (int)screenId;
        xQueueOverwrite(nvsWriteQueue, &id);
    }
}

static inline void setLabelText(lv_obj_t *obj, const char *text) {
    if (obj != nullptr && text != nullptr) {
        const char *cur = lv_label_get_text(obj);
        if (cur == nullptr || strcmp(cur, text) != 0) {
            lv_label_set_text(obj, text);
        }
    }
}

// === OPTIMALIZACE 6: Hystereze arc widgetů (snižuje počet překreslení) ===
static inline void setArcValue(lv_obj_t *obj, int val) {
    if (obj != nullptr) {
        int cur = lv_arc_get_value(obj);
        // Překreslit jen při změně > 1 (hystereze), ale vždy pro krajní hodnoty
        if (abs(cur - val) > 1 || (val == 0 && cur != 0) || (val == 100 && cur != 100)) {
            lv_arc_set_value(obj, val);
        }
    }
}

// Časovač pro pomalé blikání ukazatele teploty bílo-červeně při teplotě nad 90 °C
static void onTempBlinkTimer(lv_timer_t *timer) {
    static bool isCpuRed = false;
    if (objects.cpu_arc_temp != nullptr) {
        if (telemetry.cpuTemp >= 90) {
            isCpuRed = !isCpuRed;
            lv_color_t color = isCpuRed ? lv_color_hex(0xff0000) : lv_color_hex(0xffffff);
            lv_obj_set_style_arc_color(objects.cpu_arc_temp, color, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else if (isCpuRed) {
            isCpuRed = false;
            lv_obj_set_style_arc_color(objects.cpu_arc_temp, lv_color_hex(0xffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
    }

    static bool isGpuRed = false;
    if (objects.gpu_arc_temp != nullptr) {
        if (telemetry.gpuTemp >= 90) {
            isGpuRed = !isGpuRed;
            lv_color_t color = isGpuRed ? lv_color_hex(0xff0000) : lv_color_hex(0xffffff);
            lv_obj_set_style_arc_color(objects.gpu_arc_temp, color, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        } else if (isGpuRed) {
            isGpuRed = false;
            lv_obj_set_style_arc_color(objects.gpu_arc_temp, lv_color_hex(0xffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
    }
}

void setup() {
    BoardSerial.begin(115200);
#if ARDUINO_USB_CDC_ON_BOOT
    Serial.begin(115200);
#endif
    serialRxBuffer.reserve(1024);
    delay(500);

    // === OPTIMALIZACE 1: Spuštění NVS write tasku na Core 0 ===
    nvsWriteQueue = xQueueCreate(1, sizeof(int));  // xQueueOverwrite potřebuje délku 1
    xTaskCreatePinnedToCore(nvsWriteTask, "nvs_wr", 4096, NULL, 1, NULL, 0);  // Core 0!

    // Inicializace NVS paměti – jednorázové čtení poslední obrazovky
    Preferences prefs;
    prefs.begin("openfront", false);
    int savedScreen = prefs.getInt("last_scr", (int)SCREEN_ID_ALL);
    prefs.end();

    // 1. Inicializace desky Waveshare (RGB displej, dotyk GT911 a expandér CH422G)
    board = new Board();
    board->init();
    board->begin();

    // 2. Spuštění LVGL tasku
    lvgl_port_init(board->getLCD(), board->getTouch());

    // 3. Vykreslení UI z EEZ Studia
    if (lvgl_port_lock(-1)) {
        ui_init();

        // Časovač pro varovné blikání ukazatele teploty
        lv_timer_create(onTempBlinkTimer, 500, NULL);

        // Inicializace tapety (umístění do pozadí, hodiny a dotyková plocha do popředí)
        init_wallpaper_widget(objects.image_wallpaper, objects.clock_time, objects.home_bttn_6);

        // Obsluha přepínání obrazovek z tlačítek pro návrat (Home)
        lv_obj_t *homeButtons[] = {
            objects.home_bttn,
            objects.home_bttn_1,
            objects.home_bttn_2,
            objects.home_bttn_3,
            objects.home_bttn_4,
            objects.home_bttn_5,
            objects.home_bttn_6,
            objects.home_bttn_7
        };
        for (lv_obj_t *btn : homeButtons) {
            if (btn != nullptr) {
                lv_obj_add_event_cb(btn, action_main_page, LV_EVENT_CLICKED, NULL);
            }
        }

        // Obsluha přepínání obrazovek z matice tlačítek na hlavní obrazovce (Screen Main)
        lv_obj_t *btnm = objects.obj0 != nullptr ? objects.obj0 : (objects.main != nullptr ? lv_obj_get_child(objects.main, 0) : nullptr);
        if (btnm != nullptr) {
            lv_obj_add_event_cb(btnm, onMainBtnMatrixClick, LV_EVENT_CLICKED, NULL);
        }

        // Načtení naposledy otevřené obrazovky z NVS paměti (výchozí: ALL)
        if (savedScreen >= _SCREEN_ID_FIRST && savedScreen <= _SCREEN_ID_LAST) {
            loadScreen((enum ScreensEnum)savedScreen);
        }

        updateUiWidgets();
        lvgl_port_unlock();
    }
}

void loop() {
    // Příjem z UART0 (převodník CH343 na desce)
    while (BoardSerial.available() > 0) {
        char c = (char)BoardSerial.read();
        if (c == '\n') {
            serialRxBuffer.trim();
            if (serialRxBuffer.startsWith("{")) {
                processSerialLine(serialRxBuffer);
            }
            serialRxBuffer = "";
        }
        else if (c != '\r') {
            if (serialRxBuffer.length() < 1020) {
                serialRxBuffer += c;
            }
            else {
                serialRxBuffer = "";
            }
        }
    }

#if ARDUINO_USB_CDC_ON_BOOT
    // Příjem z nativního USB CDC (pokud je využito)
    while (Serial.available() > 0) {
        char c = (char)Serial.read();
        if (c == '\n') {
            serialRxBuffer.trim();
            if (serialRxBuffer.startsWith("{")) {
                processSerialLine(serialRxBuffer);
            }
            serialRxBuffer = "";
        }
        else if (c != '\r') {
            if (serialRxBuffer.length() < 1020) {
                serialRxBuffer += c;
            }
            else {
                serialRxBuffer = "";
            }
        }
    }
#endif

    // Zhasnutí podsvícení po 15 sekundách bez dat z PC
    if (lastStatTimeMs > 0 && (millis() - lastStatTimeMs > 15000) && isBacklightOn) {
        setBacklight(false);
    }

    // === OPTIMALIZACE 2: Rate-limited aktualizace UI (max každých 200 ms) ===
    if (uiUpdatePending && (millis() - lastUiUpdateMs >= UI_UPDATE_INTERVAL_MS)) {
        updateUiWidgets();
        lastUiUpdateMs = millis();
        uiUpdatePending = false;
    }

    delay(5);
}

void processSerialLine(const String &line) {
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, line);
    if (err) {
        return;
    }

    const char *type = doc["type"] | "";

    if (strcmp(type, "hello") == 0) {
        JsonDocument ack;
        ack["v"] = 1;
        ack["type"] = "hello_ack";
        ack["fw"] = "0.1.0";
        ack["device"] = "OpenFrontBase";
        ack["theme"] = 0;
        ack["bl"] = isBacklightOn;

        String out;
        serializeJson(ack, out);
        BoardSerial.println(out);
#if ARDUINO_USB_CDC_ON_BOOT
        Serial.println(out);
#endif

        if (!isBacklightOn) {
            setBacklight(true);
        }
    }
    else if (strcmp(type, "specs") == 0) {
        telemetry.cpuName = doc["cpu_name"] | "Unknown CPU";
        telemetry.gpuName = doc["gpu_name"] | "Unknown GPU";
        telemetry.ramName = doc["ram_name"] | "System RAM";
        telemetry.ramTotalGb = doc["ram_total_gb"] | 0;
        telemetry.diskName = doc["disk_name"] | "System Disk";
        telemetry.diskTotalGb = doc["disk_total_gb"] | 0;
        telemetry.netName = doc["net_name"] | "Network";

        // Přečtení poslední obrazovky z NVS (jednorázový read na Core 1 je OK)
        Preferences p;
        p.begin("openfront", true);  // read-only → neblokuje Flash zápis
        int savedScreen = p.getInt("last_scr", (int)SCREEN_ID_ALL);
        p.end();
        if (savedScreen < _SCREEN_ID_FIRST || savedScreen > _SCREEN_ID_LAST) {
            savedScreen = (int)SCREEN_ID_ALL;
        }

        if (lvgl_port_lock(-1)) {
            loadScreen((enum ScreensEnum)savedScreen);
            lvgl_port_unlock();
        }

        updateUiWidgets();
    }
    else if (strcmp(type, "stat") == 0) {
        lastStatTimeMs = millis();

        bool screenOn = doc["scr_on"] | true;
        if (screenOn && !isBacklightOn) {
            setBacklight(true);
        }
        else if (!screenOn && isBacklightOn) {
            setBacklight(false);
        }

        telemetry.timeStr = doc["time"] | "";
        telemetry.dateStr = doc["date"] | "";

        telemetry.pcPowerW = doc["pc_power_w"] | 0;

        telemetry.cpuLoad = doc["cpu"]["load"] | 0;
        telemetry.cpuTemp = doc["cpu"]["temp"] | 0;
        float rawFreq = doc["cpu"]["freq"] | 0.0f;
        if (rawFreq > 50.0f) {
            telemetry.cpuFreq = rawFreq / 1000.0f;
        } else {
            telemetry.cpuFreq = rawFreq;
        }
        telemetry.cpuFanRpm = doc["cpu"]["fan_rpm"] | 0;
        telemetry.cpuPowerW = doc["cpu"]["power_w"] | 0;

        telemetry.gpuLoad = doc["gpu"]["load"] | 0;
        telemetry.gpuTemp = doc["gpu"]["temp"] | 0;
        telemetry.gpuFreq = doc["gpu"]["freq"] | 0;
        telemetry.gpuFanPct = doc["gpu"]["fan_pct"] | 0;
        telemetry.gpuPowerW = doc["gpu"]["power_w"] | 0;
        telemetry.vramUsedMb = doc["gpu"]["vram_used"] | 0;
        telemetry.vramTotalMb = doc["gpu"]["vram_total"] | 0;

        telemetry.ramLoad = doc["ram"]["load"] | 0;
        telemetry.ramUsedMb = doc["ram"]["used_mb"] | 0;

        telemetry.diskUsedPct = doc["disk"]["used_pct"] | 0;
        telemetry.diskUsedGb = doc["disk"]["used_gb"] | 0;
        telemetry.diskTemp = doc["disk"]["temp"] | 0;

        telemetry.netDlKbps = doc["net"]["dl_kbps"] | 0;
        telemetry.netUlKbps = doc["net"]["ul_kbps"] | 0;

        // === OPTIMALIZACE 2: Pouze označíme, že je potřeba aktualizovat UI ===
        uiUpdatePending = true;
    }
}

void setBacklight(bool enable) {
    if (board != nullptr && board->getBacklight() != nullptr) {
        if (enable) {
            board->getBacklight()->on();
        }
        else {
            board->getBacklight()->off();
        }
        isBacklightOn = enable;
    }
}

static void onMainBtnMatrixClick(lv_event_t *e) {
    lv_obj_t *obj = lv_event_get_target(e);
    uint16_t id = lv_btnmatrix_get_selected_btn(obj);
    if (id == LV_BTNMATRIX_BTN_NONE) return;
    const char *txt = lv_btnmatrix_get_btn_text(obj, id);
    if (!txt) return;

    enum ScreensEnum target = SCREEN_ID_MAIN;
    if (strcasecmp(txt, "All") == 0) {
        target = SCREEN_ID_ALL;
    } else if (strcasecmp(txt, "Settings") == 0) {
        target = SCREEN_ID_SETTINGS;
    } else if (strcasecmp(txt, "Wallpaper") == 0) {
        target = SCREEN_ID_WALLPAPER;
    } else if (strcasecmp(txt, "Agent status") == 0) {
        target = SCREEN_ID_AGENT_STATUS;
    } else if (strcasecmp(txt, "CPU") == 0) {
        target = SCREEN_ID_CPU;
    } else if (strcasecmp(txt, "GPU") == 0) {
        target = SCREEN_ID_GPU;
    } else if (strcasecmp(txt, "RAM & Disk") == 0) {
        target = SCREEN_ID_RAM_AND_DISK;
    } else if (strcasecmp(txt, "Net") == 0) {
        target = SCREEN_ID_NET;
    } else {
        return;
    }

    lv_indev_t *indev = lv_indev_get_act();
    if (indev != nullptr) {
        lv_indev_wait_release(indev);
    }

    loadScreen(target);
    persist_screen_selection(target);
}

void updateUiWidgets() {
    if (lvgl_port_lock(-1)) {
        char buf[64];

        // === OPTIMALIZACE 3: Zjistíme aktivní obrazovku a aktualizujeme jen relevantní widgety ===
        lv_obj_t *activeScreen = lv_scr_act();
        bool isAll = (activeScreen == objects.all);
        bool isCpu = (activeScreen == objects.cpu);
        bool isGpu = (activeScreen == objects.gpu);
        bool isRamDisk = (activeScreen == objects.ram_and_disk);
        bool isNet = (activeScreen == objects.net);
        bool isWallpaper = (activeScreen == objects.wallpaper);

        // ==========================================
        // 0. NÁZVY KOMPONENT (Specs) – jen na relevantních obrazovkách
        // ==========================================
        if (isAll || isCpu) {
            setLabelText(objects.cpu_name_label_1, telemetry.cpuName.c_str());
            setLabelText(objects.cpu_name_label, telemetry.cpuName.c_str());
        }
        if (isAll || isGpu) {
            setLabelText(objects.gpu_name_label_1, telemetry.gpuName.c_str());
            setLabelText(objects.gpu_name_label, telemetry.gpuName.c_str());
        }
        if (isAll || isRamDisk) {
            setLabelText(objects.ram_name_label_1, telemetry.ramName.c_str());
            setLabelText(objects.ram_name_label, telemetry.ramName.c_str());
            setLabelText(objects.disk_name_label_1, telemetry.diskName.c_str());
            setLabelText(objects.disk_name_label, telemetry.diskName.c_str());
        }
        if (isNet) {
            setLabelText(objects.network_device_name_label, telemetry.netName.c_str());
        }

        // ==========================================
        // 1. CPU TELEMETRIE (Obrazovka All + samostatná CPU)
        // ==========================================
        if (isAll || isCpu) {
            snprintf(buf, sizeof(buf), "%d RPM", telemetry.cpuFanRpm);
            setLabelText(objects.cpu_fan_text_1, buf);
            setLabelText(objects.cpu_fan_text, buf);

            snprintf(buf, sizeof(buf), "%d °C", telemetry.cpuTemp);
            setLabelText(objects.cpu_temp_text_1, buf);
            snprintf(buf, sizeof(buf), "%d", telemetry.cpuTemp);
            setLabelText(objects.cpu_temp_text, buf);

            snprintf(buf, sizeof(buf), "%.2f GHz", telemetry.cpuFreq);
            setLabelText(objects.cpu_clock_text_1, buf);
            snprintf(buf, sizeof(buf), "%.2f", telemetry.cpuFreq);
            setLabelText(objects.cpu_clock_text, buf);

            if (objects.cpu_arc_clock != nullptr) {
                int val = (int)roundf(telemetry.cpuFreq * 1000.0f);
                if (val < 0) val = 0;
                if (val > 10000) val = 10000;
                setArcValue(objects.cpu_arc_clock, val);
            }
            if (objects.cpu_arc_temp != nullptr) {
                int t = telemetry.cpuTemp;
                if (t < 0) t = 0;
                if (t > 100) t = 100;
                setArcValue(objects.cpu_arc_temp, t);
            }
            if (objects.cpu_arc_normal_usage != nullptr) {
                int normalUsage = telemetry.cpuLoad > 90 ? 90 : telemetry.cpuLoad;
                if (normalUsage < 0) normalUsage = 0;
                setArcValue(objects.cpu_arc_normal_usage, normalUsage);
            }
            if (objects.cpu_arc_warning_usage != nullptr) {
                int warnUsage = telemetry.cpuLoad > 90 ? telemetry.cpuLoad : 90;
                if (warnUsage > 100) warnUsage = 100;
                setArcValue(objects.cpu_arc_warning_usage, warnUsage);
            }

            snprintf(buf, sizeof(buf), "%d W", telemetry.cpuPowerW);
            setLabelText(objects.cpu_power_text_1, buf);
            setLabelText(objects.cpu_power_text, buf);

            snprintf(buf, sizeof(buf), "%d %%", telemetry.cpuLoad);
            setLabelText(objects.cpu_usage_text_1, buf);
            setLabelText(objects.cpu_usage_text, buf);
        }

        // ==========================================
        // 2. GPU TELEMETRIE (Obrazovka All + samostatná GPU)
        // ==========================================
        if (isAll || isGpu) {
            snprintf(buf, sizeof(buf), "%d %%", telemetry.gpuFanPct);
            setLabelText(objects.gpu_fan_text_1, buf);
            setLabelText(objects.gpu_fan_text, buf);

            snprintf(buf, sizeof(buf), "%d °C", telemetry.gpuTemp);
            setLabelText(objects.gpu_temp_text_1, buf);
            snprintf(buf, sizeof(buf), "%d", telemetry.gpuTemp);
            setLabelText(objects.gpu_temp_text, buf);

            if (objects.gpu_arc_temp != nullptr) {
                int t = telemetry.gpuTemp;
                if (t < 0) t = 0;
                if (t > 100) t = 100;
                setArcValue(objects.gpu_arc_temp, t);
            }

            snprintf(buf, sizeof(buf), "%d MHz", telemetry.gpuFreq);
            setLabelText(objects.gpu_clock_text_1, buf);
            float gpuFreqGhz = telemetry.gpuFreq > 50 ? (telemetry.gpuFreq / 1000.0f) : (float)telemetry.gpuFreq;
            snprintf(buf, sizeof(buf), "%.2f", gpuFreqGhz);
            setLabelText(objects.gpu_clock_text, buf);

            if (objects.gpu_arc_clock != nullptr) {
                int val = (int)roundf(gpuFreqGhz * 1000.0f);
                if (val < 0) val = 0;
                if (val > 10000) val = 10000;
                setArcValue(objects.gpu_arc_clock, val);
            }

            snprintf(buf, sizeof(buf), "%d W", telemetry.gpuPowerW);
            setLabelText(objects.gpu_power_text_1, buf);
            setLabelText(objects.gpu_power_text, buf);

            snprintf(buf, sizeof(buf), "%d %%", telemetry.gpuLoad);
            setLabelText(objects.gpu_usage_text_1, buf);
            setLabelText(objects.gpu_usage_text_o, buf);

            if (objects.gpu_arc_normal_usage != nullptr) {
                int normalUsage = telemetry.gpuLoad > 90 ? 90 : telemetry.gpuLoad;
                if (normalUsage < 0) normalUsage = 0;
                setArcValue(objects.gpu_arc_normal_usage, normalUsage);
            }
            if (objects.gpu_arc_warning_usage != nullptr) {
                int warnUsage = telemetry.gpuLoad > 90 ? telemetry.gpuLoad : 90;
                if (warnUsage > 100) warnUsage = 100;
                setArcValue(objects.gpu_arc_warning_usage, warnUsage);
            }

            snprintf(buf, sizeof(buf), "%d MB", telemetry.vramTotalMb);
            setLabelText(objects.gpu_vram_text_1, buf);
            setLabelText(objects.gpu_vram_text, buf);

            snprintf(buf, sizeof(buf), "%d MB", telemetry.vramUsedMb);
            setLabelText(objects.gpu_vram_usage_text_1, buf);
            setLabelText(objects.gpu_vram_usage_text, buf);
        }

        // ==========================================
        // 3. RAM TELEMETRIE (Obrazovka All + RAM & Disk)
        // ==========================================
        if (isAll || isRamDisk) {
            snprintf(buf, sizeof(buf), "%d GB", telemetry.ramTotalGb);
            setLabelText(objects.ram_capacity_text_1, buf);
            setLabelText(objects.ram_capacity_text, buf);

            snprintf(buf, sizeof(buf), "%d MB (%d %%)", telemetry.ramUsedMb, telemetry.ramLoad);
            setLabelText(objects.ram_used_text_1, buf);
            setLabelText(objects.ram_used_text, buf);
        }

        // ==========================================
        // 4. DISK / ROM (Obrazovka All + RAM & Disk)
        // ==========================================
        if (isAll || isRamDisk) {
            snprintf(buf, sizeof(buf), "%d GB", telemetry.diskTotalGb);
            setLabelText(objects.disk_capacity_text_1, buf);
            setLabelText(objects.disk_capacity_text, buf);

            snprintf(buf, sizeof(buf), "%d GB (%d %%)", telemetry.diskUsedGb, telemetry.diskUsedPct);
            setLabelText(objects.disk_used_text_1, buf);
            setLabelText(objects.disk_used_text, buf);

            snprintf(buf, sizeof(buf), "%d °C", telemetry.diskTemp);
            setLabelText(objects.disk_temp_text_1, buf);
            setLabelText(objects.disk_temp_text, buf);
        }

        // ==========================================
        // 5. NET (Obrazovka Net)
        // ==========================================
        if (isNet) {
            snprintf(buf, sizeof(buf), "%d KB/s", telemetry.netDlKbps);
            setLabelText(objects.net_download_text, buf);

            snprintf(buf, sizeof(buf), "%d KB/s", telemetry.netUlKbps);
            setLabelText(objects.net_upload_text, buf);
        }

        // ==========================================
        // 6. WALLPAPER / CLOCK (Obrazovka Wallpaper)
        // ==========================================
        if (isWallpaper) {
            if (telemetry.timeStr.length() > 0) {
                setLabelText(objects.clock_time, telemetry.timeStr.c_str());
            }
        }

        lvgl_port_unlock();
    }
}
