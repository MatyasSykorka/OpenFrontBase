#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_all_page(lv_event_t * e);
extern void action_settings_page(lv_event_t * e);
extern void action_wallpaper_page(lv_event_t * e);
extern void action_agent_page(lv_event_t * e);
extern void action_cpu_page(lv_event_t * e);
extern void action_gpu_page(lv_event_t * e);
extern void action_ra_mamd_disk_page(lv_event_t * e);
extern void action_net_page(lv_event_t * e);
extern void action_main_page(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/