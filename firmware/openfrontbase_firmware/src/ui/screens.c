#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

screen_cpu_state_t screen_cpu_state;

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

//
// Screens
//

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_btnmatrix_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 480);
            static const char *map[10] = {
                "All",
                "Settings",
                "Wallpaper",
                "Agent status",
                "\n",
                "CPU",
                "GPU",
                "RAM & Disk",
                "Net",
                NULL,
            };
            lv_btnmatrix_set_map(obj, map);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_darken(lv_color_hex(0x600000), 64), LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_AUTO, LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}

void create_screen_all() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.all = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            // cpu_conteiner_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.cpu_conteiner_1 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 470, 270);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_darken(lv_color_hex(0x430000), 64), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x7a0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // cpu_main_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_main_label_1 = obj;
                    lv_obj_set_pos(obj, 25, 15);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "CPU");
                }
                {
                    // cpu_name_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_name_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 45);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "CPU name");
                }
                {
                    // cpu_usage_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_usage_text_1 = obj;
                    lv_obj_set_pos(obj, 135, 240);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextUsage");
                }
                {
                    // cpu_power_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_power_text_1 = obj;
                    lv_obj_set_pos(obj, 135, 200);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextPower");
                }
                {
                    // cpu_clock_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_clock_text_1 = obj;
                    lv_obj_set_pos(obj, 135, 160);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextClock");
                }
                {
                    // cpu_temp_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_temp_text_1 = obj;
                    lv_obj_set_pos(obj, 135, 120);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // cpu_fan_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_fan_text_1 = obj;
                    lv_obj_set_pos(obj, 135, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextFan");
                }
                {
                    // cpu_power_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_power_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 200);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Power");
                }
                {
                    // cpu_clock_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_clock_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 160);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Clock");
                }
                {
                    // cpu_temp_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_temp_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 120);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Temperature");
                }
                {
                    // cpu_fan_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_fan_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Fan speed");
                }
                {
                    // cpu_usage_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_usage_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 240);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Usage");
                }
            }
        }
        {
            // gpu_conteiner_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.gpu_conteiner_1 = obj;
            lv_obj_set_pos(obj, 472, 0);
            lv_obj_set_size(obj, 328, 350);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_darken(lv_color_hex(0x430000), 64), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x7a0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // gpu_title_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_title_label_1 = obj;
                    lv_obj_set_pos(obj, 25, 15);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "GPU");
                }
                {
                    // gpu_name_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_name_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 45);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "GPU name");
                }
                {
                    // gpu_fan_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_fan_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Fan speed");
                }
                {
                    // gpu_temp_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_temp_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 120);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Temperature");
                }
                {
                    // gpu_clock_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_clock_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 160);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Clock");
                }
                {
                    // gpu_power_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_power_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 200);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Power");
                }
                {
                    // gpu_usage_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_usage_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 240);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Usage");
                }
                {
                    // gpu_fan_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_fan_text_1 = obj;
                    lv_obj_set_pos(obj, 150, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextFan");
                }
                {
                    // gpu_temp_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_temp_text_1 = obj;
                    lv_obj_set_pos(obj, 150, 120);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // gpu_clock_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_clock_text_1 = obj;
                    lv_obj_set_pos(obj, 150, 160);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextClock");
                }
                {
                    // gpu_power_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_power_text_1 = obj;
                    lv_obj_set_pos(obj, 150, 200);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextPower");
                }
                {
                    // gpu_usage_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_usage_text_1 = obj;
                    lv_obj_set_pos(obj, 150, 240);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextUsage");
                }
                {
                    // gpu_vram_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_vram_label_1 = obj;
                    lv_obj_set_pos(obj, 13, 280);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "VRAM");
                }
                {
                    // gpu_vram_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_vram_text_1 = obj;
                    lv_obj_set_pos(obj, 150, 280);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextVram");
                }
                {
                    // gpu_vram_usage_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_vram_usage_label_1 = obj;
                    lv_obj_set_pos(obj, 14, 320);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "VRAM usage");
                }
                {
                    // gpu_vram_usage_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_vram_usage_text_1 = obj;
                    lv_obj_set_pos(obj, 150, 320);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextVramUsage");
                }
            }
        }
        {
            // disk_conteiner_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.disk_conteiner_1 = obj;
            lv_obj_set_pos(obj, 9, 284);
            lv_obj_set_size(obj, 335, 190);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_darken(lv_color_hex(0x430000), 64), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x7a0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // disk_title_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_title_label_1 = obj;
                    lv_obj_set_pos(obj, 25, 15);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "System disk");
                }
                {
                    // disk_name_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_name_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 45);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Disk name");
                }
                {
                    // disk_temp_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_temp_text_1 = obj;
                    lv_obj_set_pos(obj, 135, 160);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // disk_used_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_used_text_1 = obj;
                    lv_obj_set_pos(obj, 135, 120);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextUsed");
                }
                {
                    // disk_capacity_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_capacity_text_1 = obj;
                    lv_obj_set_pos(obj, 135, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextCapacity");
                }
                {
                    // disk_temp_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_temp_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 160);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Temperature");
                }
                {
                    // disk_used_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_used_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 120);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Used");
                }
                {
                    // disk_capacity_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_capacity_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Capacity");
                }
            }
        }
        {
            // ram_conteiner_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.ram_conteiner_1 = obj;
            lv_obj_set_pos(obj, 231, 120);
            lv_obj_set_size(obj, 239, 150);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_darken(lv_color_hex(0x430000), 64), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x7a0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // ram_title_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.ram_title_label_1 = obj;
                    lv_obj_set_pos(obj, 25, 15);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "RAM");
                }
                {
                    // ram_name_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.ram_name_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 45);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "RAM name");
                }
                {
                    // ram_used_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.ram_used_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 120);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Used");
                }
                {
                    // ram_capacity_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.ram_capacity_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Capacity");
                }
                {
                    // ram_used_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.ram_used_text_1 = obj;
                    lv_obj_set_pos(obj, 100, 120);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextUsed");
                }
                {
                    // ram_capacity_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.ram_capacity_text_1 = obj;
                    lv_obj_set_pos(obj, 100, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextCapacity");
                }
            }
        }
        {
            // home_bttn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn = obj;
            lv_obj_set_pos(obj, 160, 80);
            lv_obj_set_size(obj, 480, 320);
            lv_obj_add_event_cb(obj, action_main_page, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_EDITED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Home");
                }
            }
        }
    }
    
    tick_screen_all();
}

void tick_screen_all() {
}

void create_screen_cpu() {
    screen_cpu_state_t *state = &screen_cpu_state;
    (void)state;
    lv_obj_t *obj = lv_obj_create(0);
    objects.cpu = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            // cpu_main_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_main_label = obj;
            lv_obj_set_pos(obj, 362, 430);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "CPU");
        }
        {
            // cpu_name_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_name_label = obj;
            lv_obj_set_pos(obj, 0, 18);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "CPU name");
        }
        {
            // cpu_arc_normal_usage
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.cpu_arc_normal_usage = obj;
            lv_obj_set_pos(obj, 190, 60);
            lv_obj_set_size(obj, 420, 420);
            lv_arc_set_range(obj, 0, 90);
            lv_arc_set_value(obj, 5);
            lv_arc_set_bg_start_angle(obj, 160);
            lv_arc_set_bg_end_angle(obj, 0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_arc_width(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0x313131), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 30, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // cpu_arc_warning_usage
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.cpu_arc_warning_usage = obj;
            lv_obj_set_pos(obj, 190, 60);
            lv_obj_set_size(obj, 420, 420);
            lv_arc_set_range(obj, 90, 100);
            lv_arc_set_value(obj, 0);
            lv_arc_set_bg_start_angle(obj, 0);
            lv_arc_set_bg_end_angle(obj, 20);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_arc_width(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0x1f0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 30, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0x7f0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // cpu_arc_usage_design
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.cpu_arc_usage_design = obj;
            lv_obj_set_pos(obj, 190, 60);
            lv_obj_set_size(obj, 420, 420);
            lv_arc_set_range(obj, 0, 1);
            lv_arc_set_value(obj, 1);
            lv_arc_set_bg_start_angle(obj, 160);
            lv_arc_set_bg_end_angle(obj, 20);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // cpu_meter_usage
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.cpu_meter_usage = obj;
            lv_obj_set_pos(obj, 190, 60);
            lv_obj_set_size(obj, 420, 420);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                state->scale = scale;
                lv_meter_set_scale_ticks(obj, scale, 51, 2, 18, lv_color_hex(0xcccccc));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 4, 32, lv_color_darken(lv_color_hex(0xcccccc), 64), 22);
                lv_meter_set_scale_range(obj, scale, 0, 100, 220, 160);
            }
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // cpu_usage_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_usage_label = obj;
            lv_obj_set_pos(obj, 352, 337);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Usage");
        }
        {
            // cpu_usage_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_usage_text = obj;
            lv_obj_set_pos(obj, 0, 230);
            lv_obj_set_size(obj, 300, 52);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "TextUsage");
        }
        {
            // cpu_arc_temp
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.cpu_arc_temp = obj;
            lv_obj_set_pos(obj, 490, 130);
            lv_obj_set_size(obj, 300, 300);
            lv_arc_set_value(obj, 30);
            lv_arc_set_mode(obj, LV_ARC_MODE_REVERSE);
            lv_arc_set_bg_start_angle(obj, 250);
            lv_arc_set_bg_end_angle(obj, 20);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0x313131), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // cpu_arc_temp_design
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.cpu_arc_temp_design = obj;
            lv_obj_set_pos(obj, 490, 130);
            lv_obj_set_size(obj, 300, 300);
            lv_arc_set_range(obj, 0, 1);
            lv_arc_set_value(obj, 1);
            lv_arc_set_bg_start_angle(obj, 250);
            lv_arc_set_bg_end_angle(obj, 20);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // cpu_temp_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_temp_label = obj;
            lv_obj_set_pos(obj, 596, 344);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Temperature");
        }
        {
            // cpu_temp_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_temp_text = obj;
            lv_obj_set_pos(obj, 280, 232);
            lv_obj_set_size(obj, 120, 50);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_46, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "0");
        }
        {
            // cpu_temp_meter
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.cpu_temp_meter = obj;
            lv_obj_set_pos(obj, 490, 130);
            lv_obj_set_size(obj, 300, 300);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                state->scale1 = scale;
                lv_meter_set_scale_ticks(obj, scale, 51, 2, 10, lv_color_hex(0xcccccc));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 4, 22, lv_color_darken(lv_color_hex(0xcccccc), 64), 15);
                lv_meter_set_scale_range(obj, scale, 100, 0, 130, 250);
            }
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // cpu_arc_clock
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.cpu_arc_clock = obj;
            lv_obj_set_pos(obj, 10, 130);
            lv_obj_set_size(obj, 300, 300);
            lv_arc_set_range(obj, 0, 10000);
            lv_arc_set_value(obj, 1500);
            lv_arc_set_bg_start_angle(obj, 240);
            lv_arc_set_bg_end_angle(obj, 10);
            lv_arc_set_rotation(obj, 280);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0x313131), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // cpu_arc_clock_design
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.cpu_arc_clock_design = obj;
            lv_obj_set_pos(obj, 10, 130);
            lv_obj_set_size(obj, 300, 300);
            lv_arc_set_range(obj, 0, 1);
            lv_arc_set_value(obj, 1);
            lv_arc_set_bg_start_angle(obj, 240);
            lv_arc_set_bg_end_angle(obj, 10);
            lv_arc_set_rotation(obj, 280);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // cpu_clock_meter
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.cpu_clock_meter = obj;
            lv_obj_set_pos(obj, 10, 130);
            lv_obj_set_size(obj, 300, 300);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                state->scale2 = scale;
                lv_meter_set_scale_ticks(obj, scale, 51, 2, 10, lv_color_hex(0xcccccc));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 4, 22, lv_color_darken(lv_color_hex(0xcccccc), 64), 15);
                lv_meter_set_scale_range(obj, scale, 0, 10, 130, 160);
            }
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // cpu_clock_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_clock_label = obj;
            lv_obj_set_pos(obj, 86, 341);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Clock");
        }
        {
            // cpu_label_ghz
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_label_ghz = obj;
            lv_obj_set_pos(obj, 109, 374);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "GHz");
        }
        {
            // cpu_clock_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_clock_text = obj;
            lv_obj_set_pos(obj, 78, 232);
            lv_obj_set_size(obj, 110, 50);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_46, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "0.00");
        }
        {
            // cpu_fan_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_fan_label = obj;
            lv_obj_set_pos(obj, 43, 440);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Fan speed");
        }
        {
            // cpu_fan_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_fan_text = obj;
            lv_obj_set_pos(obj, 156, 440);
            lv_obj_set_size(obj, 100, 18);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "TextFan");
        }
        {
            // cpu_power_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_power_text = obj;
            lv_obj_set_pos(obj, 660, 442);
            lv_obj_set_size(obj, 100, 18);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "TextPower");
        }
        {
            // cpu_power_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_power_label = obj;
            lv_obj_set_pos(obj, 584, 442);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Power");
        }
        {
            // home_bttn_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn_1 = obj;
            lv_obj_set_pos(obj, 160, 80);
            lv_obj_set_size(obj, 480, 320);
            lv_obj_add_event_cb(obj, action_main_page, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_HOVERED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Home");
                }
            }
        }
        {
            // cpu_bottom_line
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.cpu_bottom_line = obj;
            lv_obj_set_pos(obj, 0, 400);
            lv_obj_set_size(obj, 800, 20);
            static lv_point_t line_points[] = {
                { 0, 0 }
            };
            lv_line_set_points(obj, line_points, 1);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x900000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_cpu();
}

void tick_screen_cpu() {
    screen_cpu_state_t *state = &screen_cpu_state;
    (void)state;
}

void create_screen_gpu() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.gpu = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // gpu_conteiner
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.gpu_conteiner = obj;
            lv_obj_set_pos(obj, 50, 25);
            lv_obj_set_size(obj, 328, 371);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_darken(lv_color_hex(0x430000), 64), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x7a0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // gpu_title_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_title_label = obj;
                    lv_obj_set_pos(obj, 25, 15);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "GPU");
                }
                {
                    // gpu_name_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_name_label = obj;
                    lv_obj_set_pos(obj, 12, 60);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "GPU name");
                }
                {
                    // gpu_fan_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_fan_label = obj;
                    lv_obj_set_pos(obj, 12, 100);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Fan speed");
                }
                {
                    // gpu_temp_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_temp_label = obj;
                    lv_obj_set_pos(obj, 12, 140);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Temperature");
                }
                {
                    // gpu_clock_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_clock_label = obj;
                    lv_obj_set_pos(obj, 12, 180);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Clock");
                }
                {
                    // gpu_power_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_power_label = obj;
                    lv_obj_set_pos(obj, 12, 220);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Power");
                }
                {
                    // gpu_usage_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_usage_label = obj;
                    lv_obj_set_pos(obj, 12, 260);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Usage");
                }
                {
                    // gpu_fan_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_fan_text = obj;
                    lv_obj_set_pos(obj, 150, 100);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextFan");
                }
                {
                    // gpu_temp_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_temp_text = obj;
                    lv_obj_set_pos(obj, 150, 140);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // gpu_clock_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_clock_text = obj;
                    lv_obj_set_pos(obj, 150, 180);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextClock");
                }
                {
                    // gpu_power_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_power_text = obj;
                    lv_obj_set_pos(obj, 150, 220);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextPower");
                }
                {
                    // gpu_usage_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_usage_text = obj;
                    lv_obj_set_pos(obj, 150, 260);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextUsage");
                }
                {
                    // gpu_vram_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_vram_label = obj;
                    lv_obj_set_pos(obj, 13, 300);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "VRAM");
                }
                {
                    // gpu_vram_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_vram_text = obj;
                    lv_obj_set_pos(obj, 150, 300);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextVram");
                }
                {
                    // gpu_vram_usage_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_vram_usage_label = obj;
                    lv_obj_set_pos(obj, 14, 340);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "VRAM usage");
                }
                {
                    // gpu_vram_usage_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_vram_usage_text = obj;
                    lv_obj_set_pos(obj, 150, 340);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextVramUsage");
                }
            }
        }
        {
            // home_bttn_2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn_2 = obj;
            lv_obj_set_pos(obj, 160, 80);
            lv_obj_set_size(obj, 480, 320);
            lv_obj_add_event_cb(obj, action_main_page, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_HOVERED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Home");
                }
            }
        }
    }
    
    tick_screen_gpu();
}

void tick_screen_gpu() {
}

void create_screen_ram_and_disk() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.ram_and_disk = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            // ram_conteiner
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.ram_conteiner = obj;
            lv_obj_set_pos(obj, 40, 50);
            lv_obj_set_size(obj, 239, 170);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_darken(lv_color_hex(0x430000), 64), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x7a0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // ram_title_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.ram_title_label = obj;
                    lv_obj_set_pos(obj, 25, 15);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "RAM");
                }
                {
                    // ram_name_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.ram_name_label = obj;
                    lv_obj_set_pos(obj, 12, 60);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "RAM name");
                }
                {
                    // ram_used_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.ram_used_label = obj;
                    lv_obj_set_pos(obj, 12, 140);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Used");
                }
                {
                    // ram_capacity_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.ram_capacity_label = obj;
                    lv_obj_set_pos(obj, 12, 100);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Capacity");
                }
                {
                    // ram_used_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.ram_used_text = obj;
                    lv_obj_set_pos(obj, 100, 140);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextUsed");
                }
                {
                    // ram_capacity_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.ram_capacity_text = obj;
                    lv_obj_set_pos(obj, 100, 100);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextCapacity");
                }
            }
        }
        {
            // disk_conteiner
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.disk_conteiner = obj;
            lv_obj_set_pos(obj, 422, 50);
            lv_obj_set_size(obj, 335, 215);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_darken(lv_color_hex(0x430000), 64), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x7a0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // disk_title_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_title_label = obj;
                    lv_obj_set_pos(obj, 25, 15);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "System disk");
                }
                {
                    // disk_name_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_name_label = obj;
                    lv_obj_set_pos(obj, 12, 60);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Disk name");
                }
                {
                    // disk_temp_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_temp_text = obj;
                    lv_obj_set_pos(obj, 135, 180);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // disk_used_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_used_text = obj;
                    lv_obj_set_pos(obj, 135, 140);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextUsed");
                }
                {
                    // disk_capacity_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_capacity_text = obj;
                    lv_obj_set_pos(obj, 135, 100);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextCapacity");
                }
                {
                    // disk_temp_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_temp_label = obj;
                    lv_obj_set_pos(obj, 12, 180);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Temperature");
                }
                {
                    // disk_used_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_used_label = obj;
                    lv_obj_set_pos(obj, 12, 140);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Used");
                }
                {
                    // disk_capacity_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_capacity_label = obj;
                    lv_obj_set_pos(obj, 12, 100);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Capacity");
                }
            }
        }
        {
            // home_bttn_3
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn_3 = obj;
            lv_obj_set_pos(obj, 160, 80);
            lv_obj_set_size(obj, 480, 320);
            lv_obj_add_event_cb(obj, action_main_page, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_HOVERED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Home");
                }
            }
        }
    }
    
    tick_screen_ram_and_disk();
}

void tick_screen_ram_and_disk() {
}

void create_screen_net() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.net = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            // net_conteiner
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.net_conteiner = obj;
            lv_obj_set_pos(obj, 45, 40);
            lv_obj_set_size(obj, 283, 180);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_darken(lv_color_hex(0x430000), 64), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x7a0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // net_title_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.net_title_label = obj;
                    lv_obj_set_pos(obj, 25, 15);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Net");
                }
                {
                    // network_device_name_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.network_device_name_label = obj;
                    lv_obj_set_pos(obj, 12, 60);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Net name");
                }
                {
                    // net_download_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.net_download_label = obj;
                    lv_obj_set_pos(obj, 12, 140);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Download");
                }
                {
                    // net_upload_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.net_upload_label = obj;
                    lv_obj_set_pos(obj, 12, 100);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Upload");
                }
                {
                    // net_download_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.net_download_text = obj;
                    lv_obj_set_pos(obj, 150, 140);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextDownload");
                }
                {
                    // net_upload_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.net_upload_text = obj;
                    lv_obj_set_pos(obj, 150, 100);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextUpload");
                }
            }
        }
        {
            // home_bttn_4
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn_4 = obj;
            lv_obj_set_pos(obj, 160, 80);
            lv_obj_set_size(obj, 480, 320);
            lv_obj_add_event_cb(obj, action_main_page, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_HOVERED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Home");
                }
            }
        }
    }
    
    tick_screen_net();
}

void tick_screen_net() {
}

void create_screen_agent_status() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.agent_status = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            // home_bttn_5
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn_5 = obj;
            lv_obj_set_pos(obj, 160, 80);
            lv_obj_set_size(obj, 480, 320);
            lv_obj_add_event_cb(obj, action_main_page, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_HOVERED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Home");
                }
            }
        }
    }
    
    tick_screen_agent_status();
}

void tick_screen_agent_status() {
}

void create_screen_wallpaper() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.wallpaper = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            // clock_time
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.clock_time = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_roboto_bold_96px, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "clock");
        }
        {
            // image_wallpaper
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.image_wallpaper = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 480);
        }
        {
            // home_bttn_6
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn_6 = obj;
            lv_obj_set_pos(obj, 160, 80);
            lv_obj_set_size(obj, 480, 320);
            lv_obj_add_event_cb(obj, action_main_page, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_HOVERED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "");
                }
            }
        }
    }
    
    tick_screen_wallpaper();
}

void tick_screen_wallpaper() {
}

void create_screen_settings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            // home_bttn_7
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn_7 = obj;
            lv_obj_set_pos(obj, 350, 421);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_main_page, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_darken(lv_color_hex(0x9a0000), 64), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Home");
                }
            }
        }
    }
    
    tick_screen_settings();
}

void tick_screen_settings() {
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_all,
    tick_screen_cpu,
    tick_screen_gpu,
    tick_screen_ram_and_disk,
    tick_screen_net,
    tick_screen_agent_status,
    tick_screen_wallpaper,
    tick_screen_settings,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 9) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
    { "Roboto bold title 64px", &ui_font_roboto_bold_title_64px },
    { "Roboto bold title 72px", &ui_font_roboto_bold_title_72px },
    { "Roboto bold 96px", &ui_font_roboto_bold_96px },
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;

//
//
//

void create_screens() {

// Set default LVGL theme
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_main();
    create_screen_all();
    create_screen_cpu();
    create_screen_gpu();
    create_screen_ram_and_disk();
    create_screen_net();
    create_screen_agent_status();
    create_screen_wallpaper();
    create_screen_settings();
}