#include <Arduino.h>
#include <esp_display_panel.hpp>
#include <lvgl.h>
#include "lvgl_v8_port.h"
#include <ArduinoJson.h>

// Vygenerované UI z EEZ Studia
#include "src/ui/ui.h"
#include "src/ui/screens.h"
#include "src/ui/actions.h"

// Piny I2C sběrnice na desce Waveshare ESP32-S3-Touch-LCD-4.3
#define I2C_MASTER_NUM      0
#define I2C_MASTER_SDA_IO   8
#define I2C_MASTER_SCL_IO   9

// Piny expandéru CH422G
#define TP_RST              1
#define LCD_BL              2
#define LCD_RST             3

ESP_IOExpander *expander = nullptr;
ESP_Panel *panel = nullptr;
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

// Dopředné deklarace funkcí
void processSerialLine(const String &line);
void updateUiWidgets();
void setBacklight(bool enable);

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("1: start");

    panel = new ESP_Panel();
    panel->init();
    panel->begin();
    Serial.println("2: panel OK");

    lvgl_port_init(panel->getLcd(), panel->getTouch());
    Serial.println("3: lvgl OK");

    if (lvgl_port_lock(-1)) {
        ui_init();
        lvgl_port_unlock();
    }
    Serial.println("4: ui OK");
}

void loop() {
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
        Serial.println(out);

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
    if (expander != nullptr) {
        expander->digitalWrite(LCD_BL, enable ? HIGH : LOW);
        isBacklightOn = enable;
    }
}

void updateUiWidgets() {
    if (lvgl_port_lock(-1)) {
        // Zde budeme postupně mapovat hodnoty do labelů, jakmile jim v EEZ Studiu nastavíme ID
        lvgl_port_unlock();
    }
}