#include "wallpaper.h"

// ==============================================================================
// UŽIVATELSKÁ TAPETA (800x480 px, 16-bit RGB565)
// ==============================================================================
// Pro nahrání vlastní tapety:
// 1. Vložte libovolný obrázek (PNG / JPG) do této složky (src/picture/)
// 2. Spusťte: python3 convert_wallpaper.py vas_obrazek.png
//    Skript automaticky vygeneruje data tapety a aktivuje ji.
// ==============================================================================

#if __has_include("custom_wallpaper_data.h")
#include "custom_wallpaper_data.h"
const bool has_custom_wallpaper = true;
#else
const bool has_custom_wallpaper = false;

const lv_img_dsc_t custom_wallpaper = {
    .header.always_zero = 0,
    .header.w = 800,
    .header.h = 480,
    .data_size = 0,
    .header.cf = LV_IMG_CF_TRUE_COLOR,
    .data = NULL,
};
#endif

void init_wallpaper_widget(lv_obj_t *img_obj, lv_obj_t *clock_obj, lv_obj_t *bttn_obj) {
    if (img_obj != NULL) {
        if (has_custom_wallpaper && custom_wallpaper.data != NULL) {
            lv_img_set_src(img_obj, &custom_wallpaper);
            lv_obj_clear_flag(img_obj, LV_OBJ_FLAG_HIDDEN);
        } else {
            // Pokud tapeta ještě nebyla nahrána, skryjeme img widget
            // a nastavíme pozadí na moderní tmavý gradient
            lv_obj_add_flag(img_obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_t *screen = lv_obj_get_parent(img_obj);
            if (screen != NULL) {
                lv_obj_set_style_bg_color(screen, lv_color_hex(0x180404), LV_PART_MAIN);
                lv_obj_set_style_bg_grad_color(screen, lv_color_hex(0x060606), LV_PART_MAIN);
                lv_obj_set_style_bg_grad_dir(screen, LV_GRAD_DIR_VER, LV_PART_MAIN);
            }
        }
        // Přesuneme tapetu do úplného pozadí
        lv_obj_move_background(img_obj);
    }

    // Hodiny musí být vždy v popředí nad tapetou
    if (clock_obj != NULL) {
        lv_obj_move_foreground(clock_obj);
    }

    // Dotyková oblast tlačítka návratu musí být na vrchu
    if (bttn_obj != NULL) {
        lv_obj_move_foreground(bttn_obj);
    }
}
