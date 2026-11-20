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
    SCREEN_ID_CPU = 3,
    SCREEN_ID_GPU = 4,
    SCREEN_ID_RAM_AND_DISK = 5,
    SCREEN_ID_NET = 6,
    SCREEN_ID_AGENT_STATUS = 7,
    SCREEN_ID_WALLPAPER = 8,
    SCREEN_ID_SETTINGS = 9,
    _SCREEN_ID_LAST = 9
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *all;
    lv_obj_t *cpu;
    lv_obj_t *gpu;
    lv_obj_t *ram_and_disk;
    lv_obj_t *net;
    lv_obj_t *agent_status;
    lv_obj_t *wallpaper;
    lv_obj_t *settings;
    lv_obj_t *obj0;
    lv_obj_t *cpu_conteiner_1;
    lv_obj_t *cpu_main_label_1;
    lv_obj_t *cpu_name_label_1;
    lv_obj_t *cpu_usage_text_1;
    lv_obj_t *cpu_power_text_1;
    lv_obj_t *cpu_clock_text_1;
    lv_obj_t *cpu_temp_text_1;
    lv_obj_t *cpu_fan_text_1;
    lv_obj_t *cpu_power_label_1;
    lv_obj_t *cpu_clock_label_1;
    lv_obj_t *cpu_temp_label_1;
    lv_obj_t *cpu_fan_label_1;
    lv_obj_t *cpu_usage_label_1;
    lv_obj_t *gpu_conteiner_1;
    lv_obj_t *gpu_title_label_1;
    lv_obj_t *gpu_name_label_1;
    lv_obj_t *gpu_fan_label_1;
    lv_obj_t *gpu_temp_label_1;
    lv_obj_t *gpu_clock_label_1;
    lv_obj_t *gpu_power_label_1;
    lv_obj_t *gpu_usage_label_1;
    lv_obj_t *gpu_fan_text_1;
    lv_obj_t *gpu_temp_text_1;
    lv_obj_t *gpu_clock_text_1;
    lv_obj_t *gpu_power_text_1;
    lv_obj_t *gpu_usage_text_1;
    lv_obj_t *gpu_vram_label_1;
    lv_obj_t *gpu_vram_text_1;
    lv_obj_t *gpu_vram_usage_label_1;
    lv_obj_t *gpu_vram_usage_text_1;
    lv_obj_t *disk_conteiner_1;
    lv_obj_t *disk_title_label_1;
    lv_obj_t *disk_name_label_1;
    lv_obj_t *disk_temp_text_1;
    lv_obj_t *disk_used_text_1;
    lv_obj_t *disk_capacity_text_1;
    lv_obj_t *disk_temp_label_1;
    lv_obj_t *disk_used_label_1;
    lv_obj_t *disk_capacity_label_1;
    lv_obj_t *ram_conteiner_1;
    lv_obj_t *ram_title_label_1;
    lv_obj_t *ram_name_label_1;
    lv_obj_t *ram_used_label_1;
    lv_obj_t *ram_capacity_label_1;
    lv_obj_t *ram_used_text_1;
    lv_obj_t *ram_capacity_text_1;
    lv_obj_t *home_bttn;
    lv_obj_t *cpu_main_label;
    lv_obj_t *cpu_name_label;
    lv_obj_t *cpu_arc_normal_usage;
    lv_obj_t *cpu_arc_warning_usage;
    lv_obj_t *cpu_arc_usage_design;
    lv_obj_t *cpu_meter_usage;
    lv_obj_t *cpu_usage_label;
    lv_obj_t *cpu_usage_text;
    lv_obj_t *cpu_arc_temp;
    lv_obj_t *cpu_arc_temp_design;
    lv_obj_t *cpu_temp_label;
    lv_obj_t *cpu_temp_text;
    lv_obj_t *cpu_temp_meter;
    lv_obj_t *cpu_arc_clock;
    lv_obj_t *cpu_arc_clock_design;
    lv_obj_t *cpu_clock_meter;
    lv_obj_t *cpu_clock_label;
    lv_obj_t *cpu_label_ghz;
    lv_obj_t *cpu_clock_text;
    lv_obj_t *cpu_fan_label;
    lv_obj_t *cpu_fan_text;
    lv_obj_t *cpu_power_text;
    lv_obj_t *cpu_power_label;
    lv_obj_t *home_bttn_1;
    lv_obj_t *cpu_bottom_line;
    lv_obj_t *gpu_conteiner;
    lv_obj_t *gpu_title_label;
    lv_obj_t *gpu_name_label;
    lv_obj_t *gpu_fan_label;
    lv_obj_t *gpu_temp_label;
    lv_obj_t *gpu_clock_label;
    lv_obj_t *gpu_power_label;
    lv_obj_t *gpu_usage_label;
    lv_obj_t *gpu_fan_text;
    lv_obj_t *gpu_temp_text;
    lv_obj_t *gpu_clock_text;
    lv_obj_t *gpu_power_text;
    lv_obj_t *gpu_usage_text;
    lv_obj_t *gpu_vram_label;
    lv_obj_t *gpu_vram_text;
    lv_obj_t *gpu_vram_usage_label;
    lv_obj_t *gpu_vram_usage_text;
    lv_obj_t *home_bttn_2;
    lv_obj_t *ram_conteiner;
    lv_obj_t *ram_title_label;
    lv_obj_t *ram_name_label;
    lv_obj_t *ram_used_label;
    lv_obj_t *ram_capacity_label;
    lv_obj_t *ram_used_text;
    lv_obj_t *ram_capacity_text;
    lv_obj_t *disk_conteiner;
    lv_obj_t *disk_title_label;
    lv_obj_t *disk_name_label;
    lv_obj_t *disk_temp_text;
    lv_obj_t *disk_used_text;
    lv_obj_t *disk_capacity_text;
    lv_obj_t *disk_temp_label;
    lv_obj_t *disk_used_label;
    lv_obj_t *disk_capacity_label;
    lv_obj_t *home_bttn_3;
    lv_obj_t *net_conteiner;
    lv_obj_t *net_title_label;
    lv_obj_t *network_device_name_label;
    lv_obj_t *net_download_label;
    lv_obj_t *net_upload_label;
    lv_obj_t *net_download_text;
    lv_obj_t *net_upload_text;
    lv_obj_t *home_bttn_4;
    lv_obj_t *home_bttn_5;
    lv_obj_t *clock_time;
    lv_obj_t *image_wallpaper;
    lv_obj_t *home_bttn_6;
    lv_obj_t *home_bttn_7;
} objects_t;

extern objects_t objects;

typedef struct {
    lv_meter_scale_t *scale;
    lv_meter_scale_t *scale1;
    lv_meter_scale_t *scale2;
} screen_cpu_state_t;

extern screen_cpu_state_t screen_cpu_state;

void create_screen_main();
void tick_screen_main();

void create_screen_all();
void tick_screen_all();

void create_screen_cpu();
void tick_screen_cpu();

void create_screen_gpu();
void tick_screen_gpu();

void create_screen_ram_and_disk();
void tick_screen_ram_and_disk();

void create_screen_net();
void tick_screen_net();

void create_screen_agent_status();
void tick_screen_agent_status();

void create_screen_wallpaper();
void tick_screen_wallpaper();

void create_screen_settings();
void tick_screen_settings();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/