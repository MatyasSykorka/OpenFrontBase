#!/usr/bin/env python3
"""
OpenFrontBase Wallpaper Converter
Převede libovolný obrázek (PNG, JPG, BMP, WEBP...) na formát LVGL 8 (800x480 RGB565).
Výstupem je soubor custom_wallpaper_data.h, který firmware automaticky načte.

Použití:
    python3 convert_wallpaper.py <obrazek>
"""

import sys
import os
from PIL import Image

TARGET_WIDTH = 800
TARGET_HEIGHT = 480

def convert_image(input_path, output_header_path):
    if not os.path.isfile(input_path):
        print(f"Chyba: Soubor '{input_path}' nebyl nalezen.")
        sys.exit(1)

    print(f"Načítám obrázek: {input_path}")
    img = Image.open(input_path).convert("RGB")

    # Zachování poměru stran a oříznutí na střed (crop to fill 800x480)
    img_ratio = img.width / img.height
    target_ratio = TARGET_WIDTH / TARGET_HEIGHT

    if img_ratio > target_ratio:
        # Obrázek je širší než 16:9.6 -> oříznout boky
        new_width = int(img.height * target_ratio)
        offset = (img.width - new_width) // 2
        img = img.crop((offset, 0, offset + new_width, img.height))
    else:
        # Obrázek je vyšší -> oříznout vršek a spodek
        new_height = int(img.width / target_ratio)
        offset = (img.height - new_height) // 2
        img = img.crop((0, offset, img.width, offset + new_height))

    img = img.resize((TARGET_WIDTH, TARGET_HEIGHT), Image.Resampling.LANCZOS)
    print(f"Obrázek upraven na rozlišení {TARGET_WIDTH}x{TARGET_HEIGHT} px")

    # Převod na RGB565 (LVGL 16-bit)
    pixels = img.load()
    raw_bytes = bytearray()

    for y in range(TARGET_HEIGHT):
        for x in range(TARGET_WIDTH):
            r, g, b = pixels[x, y]
            # 16-bit RGB565: 5 bitů R, 6 bitů G, 5 bitů B
            rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
            # Little endian (LV_COLOR_16_SWAP = 0)
            raw_bytes.append(rgb565 & 0xFF)
            raw_bytes.append((rgb565 >> 8) & 0xFF)

    print(f"Generuji C záhlaví: {output_header_path} ({len(raw_bytes)} bajtů)...")

    with open(output_header_path, "w", encoding="utf-8") as f:
        f.write("/* Vygenerováno automaticky pomocí convert_wallpaper.py pro OpenFrontBase */\n")
        f.write("#ifndef CUSTOM_WALLPAPER_DATA_H\n")
        f.write("#define CUSTOM_WALLPAPER_DATA_H\n\n")
        f.write("#include <lvgl.h>\n\n")
        f.write(f"#define WALLPAPER_WIDTH {TARGET_WIDTH}\n")
        f.write(f"#define WALLPAPER_HEIGHT {TARGET_HEIGHT}\n\n")
        f.write("static const uint8_t custom_wallpaper_map[] = {\n")

        line = []
        for i, byte in enumerate(raw_bytes):
            line.append(f"0x{byte:02x}")
            if len(line) >= 16:
                f.write("    " + ", ".join(line) + ",\n")
                line = []
        if line:
            f.write("    " + ", ".join(line) + ",\n")

        f.write("};\n\n")
        f.write("const lv_img_dsc_t custom_wallpaper = {\n")
        f.write("    .header.always_zero = 0,\n")
        f.write(f"    .header.w = {TARGET_WIDTH},\n")
        f.write(f"    .header.h = {TARGET_HEIGHT},\n")
        f.write(f"    .data_size = {len(raw_bytes)},\n")
        f.write("    .header.cf = LV_IMG_CF_TRUE_COLOR,\n")
        f.write("    .data = custom_wallpaper_map,\n")
        f.write("};\n\n")
        f.write("#endif // CUSTOM_WALLPAPER_DATA_H\n")

    print("Hotovo! Tapeta je připravena. Stačí znovu přeložit a nahrát kód do ESP32 v Arduino IDE.")

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    if len(sys.argv) < 2:
        print("Použití: python3 convert_wallpaper.py <cesta_k_obrazku.png/.jpg>")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = os.path.join(script_dir, "custom_wallpaper_data.h")
    convert_image(input_file, output_file)
