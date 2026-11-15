# Vlastní tapeta pro OpenFrontBase (Wallpaper)

Tato složka slouží pro uložení a převod vlastní tapety na displej (rozlišení **800×480 px**).

## Jak nahrát vlastní tapetu:

1. Zkopírujte libovolný obrázek (např. `muj_obrazek.png` nebo `.jpg`) do této složky.
2. V terminálu spusťte přiložený konvertor:
   ```bash
   python3 convert_wallpaper.py muj_obrazek.png
   ```
   *(Skript automaticky ořízne a přizpůsobí obrázek na 800×480 px a vygeneruje soubor `custom_wallpaper_data.h`).*
3. Otevřete Arduino IDE a nahrajte firmware do desky.

Tapeta se automaticky zobrazí na obrazovce **Wallpaper** pod velkými hodinami.
Stiskem kdekoliv na obrazovce tapety se vrátíte zpět do hlavní nabídky.
