# Vlastní tapeta pro OpenFrontBase / Custom Wallpaper

Tato složka slouží pro uložení a převod vlastní tapety na displej (rozlišení **800×480 px**).  
*This folder is used to store and convert a custom wallpaper for the display (**800×480 px** resolution).*

---

## Jak nahrát vlastní tapetu (CZ)

1. Zkopírujte libovolný obrázek (např. `muj_obrazek.png` nebo `.jpg`) do této složky.
2. V terminálu spusťte přiložený konvertor:
   ```bash
   python3 convert_wallpaper.py muj_obrazek.png
   ```
   *(Skript automaticky ořízne a přizpůsobí obrázek na 800×480 px a vygeneruje soubor `custom_wallpaper_data.h`).*
3. Otevřete Arduino IDE a nahrajte firmware do desky.

Tapeta se automaticky zobrazí na obrazovce **Wallpaper** pod velkými hodinami.  
Stiskem kdekoliv na obrazovce tapety se vrátíte zpět do hlavní nabídky.

---

## How to Install a Custom Wallpaper (EN)

1. Copy any image (e.g. `my_image.png` or `.jpg`) into this directory (`src/picture/`).
2. Run the included converter script in your terminal:
   ```bash
   python3 convert_wallpaper.py my_image.png
   ```
   *(The script automatically crops, resizes the image to 800×480 px, and generates `custom_wallpaper_data.h`).*
3. Open Arduino IDE and flash the firmware to the ESP32-S3 board.

The wallpaper will automatically be displayed on the **Wallpaper** screen underneath the large clock.  
Tap anywhere on the wallpaper screen to return to the main menu.

