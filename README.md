# OpenFrontBase

![Espressif](https://img.shields.io/badge/espressif-%23E7352C.svg?style=for-the-badge&logo=espressif&logoColor=white)
![C++](https://img.shields.io/badge/c%2B%2B-%2300599C.svg?style=for-the-badge&logo=cplusplus&logoColor=white)
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![C#](https://custom-icon-badges.demolab.com/badge/C%23-%23239120.svg?style=for-the-badge&logo=cshrp&logoColor=white)
![Arduino IDE](https://img.shields.io/badge/Arduino%20IDE-%2300979D.svg?style=for-the-badge&logo=Arduino&logoColor=white)
![FreeCAD](https://img.shields.io/badge/freecad-%23418FDE.svg?style=for-the-badge&logo=freecad&logoColor=white)
![EEZ Studio](https://img.shields.io/badge/EEZ%20Studio-%230072C6.svg?style=for-the-badge&logo=windows-terminal&logoColor=white)
![LVGL](https://img.shields.io/badge/LVGL-%23E60012.svg?style=for-the-badge&logo=lvgl&logoColor=white)

**CZ:** Open-source moderní DIY náhrada za panel Asus ROG Front Base. Dotykový telemetrický panel do dvojité 5.25" pozice PC skříně postavený na desce Waveshare ESP32-S3-Touch-LCD-4.3 (LVGL 8.4) a multiplatformním C# (.NET 8) agentovi pro Windows 11 a Linux.

**EN:** Open-source modern DIY replacement for the Asus ROG Front Base panel. A dual 5.25" bay touchscreen telemetry panel powered by Waveshare ESP32-S3-Touch-LCD-4.3 (LVGL 8.4) and a cross-platform C# (.NET 8) background agent for Windows 11 and Linux.

**Compatible with:**

![Windows](https://custom-icon-badges.demolab.com/badge/Windows-0078D6?style=for-the-badge&logo=windows11&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

*Tested on an x86_64 systems.*

## Struktura projektu / Project Structure
- `firmware/` – ESP32-S3 Arduino C++ firmware & LVGL 8.4.0 UI
- `pc-client/` – Multiplatformní C# (.NET 8) služba na pozadí / Cross-platform background agent
- `ui-design/` – Projekt pro EEZ Studio / EEZ Studio project
- `STL/` – 3D modely šasi (2x 5.25" bay) a schémata / 3D enclosure models and schematics
- `docs/` – Dokumentace a specifikace protokolu / Documentation and protocol spec

## Licence / License
- **OpenFrontBase:** [MIT License](LICENSE)
- **Third-Party Assets (Roboto Font):** [Apache License 2.0](THIRD-PARTY-LICENSES.md)
