# OpenFrontBase

**CZ:** Open-source moderní náhrada za panel Asus ROG Front Base. Dotykový telemetrický panel do dvojité 5.25" pozice PC skříně postavený na desce Waveshare ESP32-S3-Touch-LCD-4.3 (LVGL 8.4) a multiplatformním C# (.NET 8) agentovi pro Windows 11 a Linux.

**EN:** Open-source modern replacement for the Asus ROG Front Base panel. A dual 5.25" bay touchscreen telemetry panel powered by Waveshare ESP32-S3-Touch-LCD-4.3 (LVGL 8.4) and a cross-platform C# (.NET 8) background agent for Windows 11 and Linux.

## Struktura projektu / Project Structure
- `firmware/` – ESP32-S3 Arduino C++ firmware & LVGL 8.4.0 UI
- `pc-client/` – Multiplatformní C# (.NET 8) služba na pozadí / Cross-platform background agent
- `ui-design/` – Projekt pro EEZ Studio / EEZ Studio project
- `STL/` – 3D modely šasi (2x 5.25" bay) a schémata / 3D enclosure models and schematics
- `docs/` – Dokumentace a specifikace protokolu / Documentation and protocol spec

## Licence / License
MIT License
