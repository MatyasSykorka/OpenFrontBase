#ifndef OPENFRONTBASE_WALLPAPER_H
#define OPENFRONTBASE_WALLPAPER_H

#include <lvgl.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Indikátor, zda je k dispozici platná uživatelská tapeta
extern const bool has_custom_wallpaper;

// Deskriptor obrázku tapety pro LVGL
extern const lv_img_dsc_t custom_wallpaper;

// Inicializuje widget tapety:
// - Pokud je přítomna uživatelská tapeta, nastaví ji
// - Přesune obrázek do úplného pozadí (za hodiny a dotykové tlačítko)
// - Přesune hodiny a tlačítko do popředí
void init_wallpaper_widget(lv_obj_t *img_obj, lv_obj_t *clock_obj, lv_obj_t *bttn_obj);

#ifdef __cplusplus
}
#endif

#endif // OPENFRONTBASE_WALLPAPER_H
