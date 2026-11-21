#include "actions.h"
#include "screens.h"
#include "ui.h"

// Funkce definovaná ve firmwaru pro trvalé uložení do paměti NVS ESP32
extern void persist_screen_selection(enum ScreensEnum screenId);

static inline void navigate_to(enum ScreensEnum screenId) {
    lv_indev_t *indev = lv_indev_get_act();
    if (indev != NULL) {
        lv_indev_wait_release(indev);
    }
    loadScreen(screenId);
    persist_screen_selection(screenId);
}

void action_to_all(lv_event_t *e) {
    LV_UNUSED(e);
    navigate_to(SCREEN_ID_ALL);
}

void action_all_page(lv_event_t *e) {
    LV_UNUSED(e);
    navigate_to(SCREEN_ID_ALL);
}

void action_settings_page(lv_event_t *e) {
    LV_UNUSED(e);
    navigate_to(SCREEN_ID_SETTINGS);
}

void action_wallpaper_page(lv_event_t *e) {
    LV_UNUSED(e);
    navigate_to(SCREEN_ID_WALLPAPER);
}

void action_agent_page(lv_event_t *e) {
    LV_UNUSED(e);
    navigate_to(SCREEN_ID_AGENT_STATUS);
}

void action_cpu_page(lv_event_t *e) {
    LV_UNUSED(e);
    navigate_to(SCREEN_ID_CPU);
}

void action_gpu_page(lv_event_t *e) {
    LV_UNUSED(e);
    navigate_to(SCREEN_ID_GPU);
}

void action_ra_mamd_disk_page(lv_event_t *e) {
    LV_UNUSED(e);
    navigate_to(SCREEN_ID_RAM_AND_DISK);
}

void action_net_page(lv_event_t *e) {
    LV_UNUSED(e);
    navigate_to(SCREEN_ID_NET);
}

void action_main_page(lv_event_t *e) {
    LV_UNUSED(e);
    navigate_to(SCREEN_ID_MAIN);
}
