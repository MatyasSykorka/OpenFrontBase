#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_ALL = 2,
    SCREEN_ID_SETTINGS = 3,
    SCREEN_ID_WALLPAPER = 4,
    SCREEN_ID_CPU = 5,
    SCREEN_ID_GPU = 6,
    SCREEN_ID_RAM = 7,
    SCREEN_ID_ROM = 8,
    SCREEN_ID_AGENT_STATUS = 9,
    _SCREEN_ID_LAST = 9
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *all;
    lv_obj_t *settings;
    lv_obj_t *wallpaper;
    lv_obj_t *cpu;
    lv_obj_t *gpu;
    lv_obj_t *ram;
    lv_obj_t *rom;
    lv_obj_t *agent_status;

    // Labely na obrazovce All
    lv_obj_t *lbl_cpu_fan;
    lv_obj_t *lbl_cpu_celsius;
    lv_obj_t *lbl_cpu_clock;
    lv_obj_t *lbl_cpu_power;
    lv_obj_t *lbl_cpu_load;
    lv_obj_t *lbl_ram_used;
    lv_obj_t *lbl_ram_total;
    lv_obj_t *lbl_gpu_fan;
    lv_obj_t *lbl_gpu_celsius;
    lv_obj_t *lbl_gpu_clock;
    lv_obj_t *lbl_gpu_power;
    lv_obj_t *lbl_gpu_load;
    lv_obj_t *lbl_vram;
    lv_obj_t *lbl_vram_used;
    lv_obj_t *lbl_rom_used;
    lv_obj_t *lbl_rom_total;
    lv_obj_t *lbl_rom_celsius;
    lv_obj_t *lbl_upl;
    lv_obj_t *lbl_down;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void create_screen_all();
void tick_screen_all();

void create_screen_settings();
void tick_screen_settings();

void create_screen_wallpaper();
void tick_screen_wallpaper();

void create_screen_cpu();
void tick_screen_cpu();

void create_screen_gpu();
void tick_screen_gpu();

void create_screen_ram();
void tick_screen_ram();

void create_screen_rom();
void tick_screen_rom();

void create_screen_agent_status();
void tick_screen_agent_status();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/