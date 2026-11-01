#include <Arduino.h>
#include <esp_display_panel.hpp>
#include <lvgl.h>
#include "lvgl_v8_port.h"
#include <ArduinoJson.h>

// Vygenerované UI z EEZ Studia
#include "src/ui/ui.h"
#include "src/ui/screens.h"
#include "src/ui/actions.h"

using namespace esp_panel::board;

// Piny expandéru CH422G na desce Waveshare ESP32-S3-Touch-LCD-4.3
#define TP_RST              1
#define LCD_BL              2
#define LCD_RST             3

Board *board = nullptr;
String serialRxBuffer = "";
unsigned long lastStatTimeMs = 0;
bool isBacklightOn = true;

// Struktura pro držení posledních přijatých dat z PC
struct TelemetryState {
    String cpuName = "Waiting for PC...";
    String gpuName = "Waiting for PC...";
    String ramName = "System RAM";
    String diskName = "System Disk";
    int ramTotalGb = 0;
    int diskTotalGb = 0;

    int pcPowerW = 0;
    int cpuLoad = 0;
    int cpuTemp = 0;
    int cpuFreq = 0;
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
void setChildLabelText(lv_obj_t *parent, uint32_t index, const char *text);

void setup() {
    BoardSerial.begin(115200);
#if ARDUINO_USB_CDC_ON_BOOT
    Serial.begin(115200);
#endif
    serialRxBuffer.reserve(1024);
    delay(500);

    // 1. Inicializace desky Waveshare (RGB displej, dotyk GT911 a expandér CH422G)
    board = new Board();
    board->init();
    board->begin();

    // 2. Spuštění LVGL tasku
    lvgl_port_init(board->getLCD(), board->getTouch());

    // 3. Vykreslení UI z EEZ Studia
    if (lvgl_port_lock(-1)) {
        ui_init();
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

        // Automatické přepnutí na obrazovku All po přijetí specifikací z PC
        if (lvgl_port_lock(-1)) {
            loadScreen(SCREEN_ID_ALL);
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

        telemetry.pcPowerW = doc["pc_power_w"] | 0;

        telemetry.cpuLoad = doc["cpu"]["load"] | 0;
        telemetry.cpuTemp = doc["cpu"]["temp"] | 0;
        telemetry.cpuFreq = doc["cpu"]["freq"] | 0;
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

        updateUiWidgets();
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

void setChildLabelText(lv_obj_t *parent, uint32_t index, const char *text) {
    lv_obj_t *child = lv_obj_get_child(parent, index);
    if (child != nullptr) {
        lv_label_set_text(child, text);
    }
}

void updateUiWidgets() {
    if (lvgl_port_lock(-1)) {
        if (objects.all != nullptr) {
            char buf[32];

            // --- CPU (indexy 6 až 10) ---
            snprintf(buf, sizeof(buf), "%d RPM", telemetry.cpuFanRpm);
            setChildLabelText(objects.all, 6, buf);

            snprintf(buf, sizeof(buf), "%d C", telemetry.cpuTemp);
            setChildLabelText(objects.all, 7, buf);

            snprintf(buf, sizeof(buf), "%d MHz", telemetry.cpuFreq);
            setChildLabelText(objects.all, 8, buf);

            snprintf(buf, sizeof(buf), "%d W", telemetry.cpuPowerW);
            setChildLabelText(objects.all, 9, buf);

            snprintf(buf, sizeof(buf), "%d %%", telemetry.cpuLoad);
            setChildLabelText(objects.all, 10, buf);

            // --- RAM (indexy 14 a 15) ---
            snprintf(buf, sizeof(buf), "%d MB (%d %%)", telemetry.ramUsedMb, telemetry.ramLoad);
            setChildLabelText(objects.all, 14, buf);

            snprintf(buf, sizeof(buf), "%d GB", telemetry.ramTotalGb);
            setChildLabelText(objects.all, 15, buf);

            // --- GPU (indexy 22 až 26, VRAM 28 a 30) ---
            snprintf(buf, sizeof(buf), "%d %%", telemetry.gpuFanPct);
            setChildLabelText(objects.all, 22, buf);

            snprintf(buf, sizeof(buf), "%d C", telemetry.gpuTemp);
            setChildLabelText(objects.all, 23, buf);

            snprintf(buf, sizeof(buf), "%d MHz", telemetry.gpuFreq);
            setChildLabelText(objects.all, 24, buf);

            snprintf(buf, sizeof(buf), "%d W", telemetry.gpuPowerW);
            setChildLabelText(objects.all, 25, buf);

            snprintf(buf, sizeof(buf), "%d %%", telemetry.gpuLoad);
            setChildLabelText(objects.all, 26, buf);

            snprintf(buf, sizeof(buf), "%d MB", telemetry.vramTotalMb);
            setChildLabelText(objects.all, 28, buf);

            snprintf(buf, sizeof(buf), "%d MB", telemetry.vramUsedMb);
            setChildLabelText(objects.all, 30, buf);

            // --- ROM / Disk (indexy 34, 35 a 37) ---
            snprintf(buf, sizeof(buf), "%d GB (%d %%)", telemetry.diskUsedGb, telemetry.diskUsedPct);
            setChildLabelText(objects.all, 34, buf);

            snprintf(buf, sizeof(buf), "%d GB", telemetry.diskTotalGb);
            setChildLabelText(objects.all, 35, buf);

            snprintf(buf, sizeof(buf), "%d C", telemetry.diskTemp);
            setChildLabelText(objects.all, 37, buf);

            // --- NET (indexy 41 a 42) ---
            snprintf(buf, sizeof(buf), "%d KB/s", telemetry.netUlKbps);
            setChildLabelText(objects.all, 41, buf);

            snprintf(buf, sizeof(buf), "%d KB/s", telemetry.netDlKbps);
            setChildLabelText(objects.all, 42, buf);
        }

        lvgl_port_unlock();
    }
}