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
screen_gpu_state_t screen_gpu_state;

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
            lv_obj_set_pos(obj, 6, 8);
            lv_obj_set_size(obj, 513, 144);
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
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "CPU name");
                }
                {
                    // cpu_usage_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_usage_text_1 = obj;
                    lv_obj_set_pos(obj, 92, 15);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextUsage");
                }
                {
                    // cpu_power_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_power_text_1 = obj;
                    lv_obj_set_pos(obj, 348, 110);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // cpu_clock_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_clock_text_1 = obj;
                    lv_obj_set_pos(obj, 348, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // cpu_temp_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_temp_text_1 = obj;
                    lv_obj_set_pos(obj, 135, 110);
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
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // cpu_power_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_power_label_1 = obj;
                    lv_obj_set_pos(obj, 277, 110);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Power");
                }
                {
                    // cpu_clock_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_clock_label_1 = obj;
                    lv_obj_set_pos(obj, 277, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Clock");
                }
                {
                    // cpu_temp_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cpu_temp_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 110);
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
            }
        }
        {
            // gpu_conteiner_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.gpu_conteiner_1 = obj;
            lv_obj_set_pos(obj, 6, 162);
            lv_obj_set_size(obj, 513, 173);
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
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "GPU name");
                }
                {
                    // gpu_fan_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_fan_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 82);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Fan speed");
                }
                {
                    // gpu_temp_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_temp_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 112);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Temperature");
                }
                {
                    // gpu_clock_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_clock_label_1 = obj;
                    lv_obj_set_pos(obj, 251, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Clock");
                }
                {
                    // gpu_power_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_power_label_1 = obj;
                    lv_obj_set_pos(obj, 251, 110);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Power");
                }
                {
                    // gpu_fan_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_fan_text_1 = obj;
                    lv_obj_set_pos(obj, 150, 82);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // gpu_temp_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_temp_text_1 = obj;
                    lv_obj_set_pos(obj, 150, 112);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // gpu_clock_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_clock_text_1 = obj;
                    lv_obj_set_pos(obj, 389, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // gpu_power_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_power_text_1 = obj;
                    lv_obj_set_pos(obj, 389, 110);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // gpu_usage_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_usage_text_1 = obj;
                    lv_obj_set_pos(obj, 92, 15);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "TextUsage");
                }
                {
                    // gpu_vram_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_vram_label_1 = obj;
                    lv_obj_set_pos(obj, 13, 142);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "VRAM");
                }
                {
                    // gpu_vram_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_vram_text_1 = obj;
                    lv_obj_set_pos(obj, 150, 142);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // gpu_vram_usage_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_vram_usage_label_1 = obj;
                    lv_obj_set_pos(obj, 251, 142);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "VRAM usage");
                }
                {
                    // gpu_vram_usage_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.gpu_vram_usage_text_1 = obj;
                    lv_obj_set_pos(obj, 389, 142);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
            }
        }
        {
            // disk_conteiner_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.disk_conteiner_1 = obj;
            lv_obj_set_pos(obj, 9, 399);
            lv_obj_set_size(obj, 780, 75);
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
                    lv_obj_set_pos(obj, 176, 12);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Disk name");
                }
                {
                    // disk_temp_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_temp_text_1 = obj;
                    lv_obj_set_pos(obj, 135, 50);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // disk_used_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_used_text_1 = obj;
                    lv_obj_set_pos(obj, 559, 49);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // disk_capacity_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_capacity_text_1 = obj;
                    lv_obj_set_pos(obj, 319, 49);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // disk_temp_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_temp_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 50);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Temperature");
                }
                {
                    // disk_used_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_used_label_1 = obj;
                    lv_obj_set_pos(obj, 501, 49);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Used");
                }
                {
                    // disk_capacity_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.disk_capacity_label_1 = obj;
                    lv_obj_set_pos(obj, 232, 49);
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
            lv_obj_set_pos(obj, 524, 8);
            lv_obj_set_size(obj, 271, 144);
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
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "RAM name");
                }
                {
                    // ram_used_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.ram_used_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 110);
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
                    lv_obj_set_pos(obj, 100, 110);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // ram_capacity_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.ram_capacity_text_1 = obj;
                    lv_obj_set_pos(obj, 100, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
            }
        }
        {
            // net_conteiner_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.net_conteiner_1 = obj;
            lv_obj_set_pos(obj, 524, 162);
            lv_obj_set_size(obj, 271, 173);
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
                    // net_title_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.net_title_label_1 = obj;
                    lv_obj_set_pos(obj, 25, 15);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Net");
                }
                {
                    // network_device_name_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.network_device_name_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 45);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Net name");
                }
                {
                    // net_download_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.net_download_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 110);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Download");
                }
                {
                    // net_upload_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.net_upload_label_1 = obj;
                    lv_obj_set_pos(obj, 12, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Upload");
                }
                {
                    // net_download_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.net_download_text_1 = obj;
                    lv_obj_set_pos(obj, 117, 110);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
                {
                    // net_upload_text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.net_upload_text_1 = obj;
                    lv_obj_set_pos(obj, 117, 80);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "0");
                }
            }
        }
        {
            // home_bttn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn = obj;
            lv_obj_set_pos(obj, 320, 400);
            lv_obj_set_size(obj, 160, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
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
            lv_obj_set_pos(obj, 0, 15);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
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
            lv_obj_set_pos(obj, 0, 214);
            lv_obj_set_size(obj, 300, 52);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "0 %");
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
            // cpu_temp_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_temp_label = obj;
            lv_obj_set_pos(obj, 595, 354);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Temperature");
        }
        {
            // cpu_label_deg
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_label_deg = obj;
            lv_obj_set_pos(obj, 670, 282);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "°C");
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
            lv_obj_set_pos(obj, 86, 351);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Clock");
        }
        {
            // cpu_label_ghz
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_label_ghz = obj;
            lv_obj_set_pos(obj, 114, 282);
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
            lv_label_set_text_static(obj, "0");
        }
        {
            // cpu_power_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cpu_power_text = obj;
            lv_obj_set_pos(obj, 660, 442);
            lv_obj_set_size(obj, 100, 18);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0 W");
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
        {
            // home_bttn_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn_1 = obj;
            lv_obj_set_pos(obj, 320, 400);
            lv_obj_set_size(obj, 160, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_cpu();
}

void tick_screen_cpu() {
    screen_cpu_state_t *state = &screen_cpu_state;
    (void)state;
}

void create_screen_gpu() {
    screen_gpu_state_t *state = &screen_gpu_state;
    (void)state;
    lv_obj_t *obj = lv_obj_create(0);
    objects.gpu = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // gpu_title_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_title_label = obj;
            lv_obj_set_pos(obj, 362, 430);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "GPU");
        }
        {
            // gpu_vram_usage_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_vram_usage_label = obj;
            lv_obj_set_pos(obj, 611, 60);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "VRAM usage");
        }
        {
            // gpu_vram_usage_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_vram_usage_text = obj;
            lv_obj_set_pos(obj, 624, 82);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0");
        }
        {
            // gpu_vram_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_vram_label = obj;
            lv_obj_set_pos(obj, 92, 60);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "VRAM");
        }
        {
            // gpu_vram_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_vram_text = obj;
            lv_obj_set_pos(obj, 75, 84);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0");
        }
        {
            // gpu_usage_text_o
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_usage_text_o = obj;
            lv_obj_set_pos(obj, 0, 214);
            lv_obj_set_size(obj, 300, 52);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "0 %");
        }
        {
            // gpu_usage_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_usage_label = obj;
            lv_obj_set_pos(obj, 352, 337);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Usage");
        }
        {
            // gpu_temp_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_temp_text = obj;
            lv_obj_set_pos(obj, 280, 232);
            lv_obj_set_size(obj, 120, 50);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_46, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "0");
        }
        {
            // gpu_temp_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_temp_label = obj;
            lv_obj_set_pos(obj, 596, 352);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Temperature");
        }
        {
            // gpu_name_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_name_label = obj;
            lv_obj_set_pos(obj, 0, 15);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "GPU name");
        }
        {
            // gpu_fan_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_fan_text = obj;
            lv_obj_set_pos(obj, 141, 440);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0");
        }
        {
            // gpu_fan_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_fan_label = obj;
            lv_obj_set_pos(obj, 41, 440);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Fan speed");
        }
        {
            // gpu_arc_normal_usage
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.gpu_arc_normal_usage = obj;
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
            // gpu_arc_warning_usage
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.gpu_arc_warning_usage = obj;
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
            // gpu_arc_usage_design
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.gpu_arc_usage_design = obj;
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
            // gpu_meter_usage
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.gpu_meter_usage = obj;
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
            // gpu_arc_temp
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.gpu_arc_temp = obj;
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
            // gpu_arc_temp_design
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.gpu_arc_temp_design = obj;
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
            // gpu_temp_meter
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.gpu_temp_meter = obj;
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
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // gpu_power_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_power_text = obj;
            lv_obj_set_pos(obj, 660, 442);
            lv_obj_set_size(obj, 100, 18);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0 W");
        }
        {
            // gpu_power_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_power_label = obj;
            lv_obj_set_pos(obj, 584, 442);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Power");
        }
        {
            // gpu_arc_clock
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.gpu_arc_clock = obj;
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
            // gpu_arc_clock_design
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.gpu_arc_clock_design = obj;
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
            // gpu_clock_meter
            lv_obj_t *obj = lv_meter_create(parent_obj);
            objects.gpu_clock_meter = obj;
            lv_obj_set_pos(obj, 10, 130);
            lv_obj_set_size(obj, 300, 300);
            {
                lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                state->scale2 = scale;
                lv_meter_set_scale_ticks(obj, scale, 26, 2, 10, lv_color_hex(0xcccccc));
                lv_meter_set_scale_major_ticks(obj, scale, 5, 4, 22, lv_color_darken(lv_color_hex(0xcccccc), 64), 15);
                lv_meter_set_scale_range(obj, scale, 0, 5, 130, 160);
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
            // gpu_clock_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_clock_label = obj;
            lv_obj_set_pos(obj, 41, 352);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Core clock");
        }
        {
            // gpu_label_ghz
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_label_ghz = obj;
            lv_obj_set_pos(obj, 114, 282);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "GHz");
        }
        {
            // gpu_clock_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_clock_text = obj;
            lv_obj_set_pos(obj, 78, 232);
            lv_obj_set_size(obj, 110, 50);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_46, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "0.00");
        }
        {
            // gpu_label_deg
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.gpu_label_deg = obj;
            lv_obj_set_pos(obj, 670, 282);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "°C");
        }
        {
            // gpu_bottom_line
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.gpu_bottom_line = obj;
            lv_obj_set_pos(obj, 0, 400);
            lv_obj_set_size(obj, 800, 20);
            static lv_point_t line_points[] = {
                { 0, 0 }
            };
            lv_line_set_points(obj, line_points, 1);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x900000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // home_bttn_2
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn_2 = obj;
            lv_obj_set_pos(obj, 320, 400);
            lv_obj_set_size(obj, 160, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_gpu();
}

void tick_screen_gpu() {
    screen_gpu_state_t *state = &screen_gpu_state;
    (void)state;
}

void create_screen_ram_and_disk() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.ram_and_disk = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            // bar_disk_usage_indicator
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.bar_disk_usage_indicator = obj;
            lv_obj_set_pos(obj, 606, 62);
            lv_obj_set_size(obj, 180, 350);
            lv_bar_set_value(obj, 25, LV_ANIM_OFF);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x828282), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // bar_ram_usage_indicator
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.bar_ram_usage_indicator = obj;
            lv_obj_set_pos(obj, 201, 62);
            lv_obj_set_size(obj, 180, 350);
            lv_bar_set_value(obj, 25, LV_ANIM_OFF);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x828282), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 1, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // ram_title_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ram_title_label = obj;
            lv_obj_set_pos(obj, 135, 431);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "RAM");
        }
        {
            // ram_name_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ram_name_label = obj;
            lv_obj_set_pos(obj, -224, 15);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "RAM name");
        }
        {
            // ram_capacity_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ram_capacity_label = obj;
            lv_obj_set_pos(obj, 6, 92);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Capacity");
        }
        {
            // ram_capacity_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ram_capacity_text = obj;
            lv_obj_set_pos(obj, 6, 126);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0");
        }
        {
            // ram_used_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ram_used_text = obj;
            lv_obj_set_pos(obj, -117, 334);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0");
        }
        {
            // ram_used_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ram_used_label = obj;
            lv_obj_set_pos(obj, 249, 367);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Used");
        }
        {
            // disk_title_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.disk_title_label = obj;
            lv_obj_set_pos(obj, 493, 431);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "System disk");
        }
        {
            // disk_name_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.disk_name_label = obj;
            lv_obj_set_pos(obj, 196, 15);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Disk name");
        }
        {
            // disk_temp_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.disk_temp_text = obj;
            lv_obj_set_pos(obj, 420, 237);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0");
        }
        {
            // disk_used_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.disk_used_text = obj;
            lv_obj_set_pos(obj, 296, 334);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0");
        }
        {
            // disk_capacity_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.disk_capacity_text = obj;
            lv_obj_set_pos(obj, 420, 126);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0");
        }
        {
            // disk_temp_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.disk_temp_label = obj;
            lv_obj_set_pos(obj, 420, 202);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Temperature");
        }
        {
            // disk_used_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.disk_used_label = obj;
            lv_obj_set_pos(obj, 662, 367);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Used");
        }
        {
            // disk_capacity_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.disk_capacity_label = obj;
            lv_obj_set_pos(obj, 420, 92);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Capacity");
        }
        {
            // ram_disk_between_line
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.ram_disk_between_line = obj;
            lv_obj_set_pos(obj, 390, 0);
            lv_obj_set_size(obj, 20, 480);
            static lv_point_t line_points[] = {
                { 0, 0 }
            };
            lv_line_set_points(obj, line_points, 1);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x900000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // home_bttn_3
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn_3 = obj;
            lv_obj_set_pos(obj, 320, 400);
            lv_obj_set_size(obj, 160, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
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
            // net_title_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.net_title_label = obj;
            lv_obj_set_pos(obj, 362, 430);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Net");
        }
        {
            // network_device_name_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.network_device_name_label = obj;
            lv_obj_set_pos(obj, 325, 15);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Net name");
        }
        {
            // net_download_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.net_download_label = obj;
            lv_obj_set_pos(obj, 47, 78);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Download");
        }
        {
            // net_upload_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.net_upload_label = obj;
            lv_obj_set_pos(obj, 513, 78);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Upload");
        }
        {
            // net_download_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.net_download_text = obj;
            lv_obj_set_pos(obj, 47, 118);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0");
        }
        {
            // net_upload_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.net_upload_text = obj;
            lv_obj_set_pos(obj, 514, 118);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0");
        }
        {
            // net_bottom_line
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.net_bottom_line = obj;
            lv_obj_set_pos(obj, 0, 400);
            lv_obj_set_size(obj, 800, 20);
            static lv_point_t line_points[] = {
                { 0, 0 }
            };
            lv_line_set_points(obj, line_points, 1);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x900000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // net_down_peak_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.net_down_peak_label = obj;
            lv_obj_set_pos(obj, 47, 164);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Peak");
        }
        {
            // net_up_peak_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.net_up_peak_label = obj;
            lv_obj_set_pos(obj, 514, 164);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Peak");
        }
        {
            // net_upload_peak_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.net_upload_peak_text = obj;
            lv_obj_set_pos(obj, 515, 198);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0");
        }
        {
            // net_download_peak_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.net_download_peak_text = obj;
            lv_obj_set_pos(obj, 47, 198);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0");
        }
        {
            // net_traffic_chart
            lv_obj_t *obj = lv_chart_create(parent_obj);
            objects.net_traffic_chart = obj;
            lv_obj_set_pos(obj, 34, 240);
            lv_obj_set_size(obj, 732, 151);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_border_color(obj, lv_color_hex(0x900000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_width(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_height(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_line_width(obj, 3, LV_PART_ITEMS | LV_STATE_DEFAULT);
        }
        {
            // home_bttn_4
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn_4 = obj;
            lv_obj_set_pos(obj, 320, 400);
            lv_obj_set_size(obj, 160, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
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
            // ai_agent_status_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ai_agent_status_label = obj;
            lv_obj_set_pos(obj, 299, 430);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Agent status");
        }
        {
            // agent_llm_name_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.agent_llm_name_text = obj;
            lv_obj_set_pos(obj, 0, 15);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "LLM name");
        }
        {
            // llm_tool_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.llm_tool_label = obj;
            lv_obj_set_pos(obj, 90, 140);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Tool calling");
        }
        {
            // llm_tok_per_sec_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.llm_tok_per_sec_label = obj;
            lv_obj_set_pos(obj, 90, 200);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Tokens per second");
        }
        {
            // llm_mem_usage_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.llm_mem_usage_label = obj;
            lv_obj_set_pos(obj, 90, 260);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Memory usage");
        }
        {
            // llm_status_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.llm_status_label = obj;
            lv_obj_set_pos(obj, 90, 80);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Status");
        }
        {
            // llm_context_win_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.llm_context_win_label = obj;
            lv_obj_set_pos(obj, 90, 320);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Context window");
        }
        {
            // net_bottom_line_1
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.net_bottom_line_1 = obj;
            lv_obj_set_pos(obj, 0, 400);
            lv_obj_set_size(obj, 800, 20);
            static lv_point_t line_points[] = {
                { 0, 0 }
            };
            lv_line_set_points(obj, line_points, 1);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x900000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // llm_status_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.llm_status_text = obj;
            lv_obj_set_pos(obj, 409, 80);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "StatusText");
        }
        {
            // llm_tool_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.llm_tool_text = obj;
            lv_obj_set_pos(obj, 409, 140);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "ToolCallingText");
        }
        {
            // llm_tok_per_sec_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.llm_tok_per_sec_text = obj;
            lv_obj_set_pos(obj, 409, 200);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "TokensPerSecondText");
        }
        {
            // llm_mem_usage_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.llm_mem_usage_text = obj;
            lv_obj_set_pos(obj, 409, 260);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "MemoryUsageText");
        }
        {
            // llm_context_win_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.llm_context_win_text = obj;
            lv_obj_set_pos(obj, 410, 320);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "ContextWindowText");
        }
        {
            // home_bttn_5
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn_5 = obj;
            lv_obj_set_pos(obj, 320, 400);
            lv_obj_set_size(obj, 160, 80);
            lv_obj_add_event_cb(obj, action_main_page, LV_EVENT_CLICKED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
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
            // image_wallpaper
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.image_wallpaper = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 480);
        }
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
            // home_bttn_6
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn_6 = obj;
            lv_obj_set_pos(obj, 320, 400);
            lv_obj_set_size(obj, 160, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
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
            // set_colour_all_pages_ui_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.set_colour_all_pages_ui_label = obj;
            lv_obj_set_pos(obj, 100, 70);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Colour");
        }
        {
            // set_colour_indicator_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.set_colour_indicator_label = obj;
            lv_obj_set_pos(obj, 100, 150);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Indicator colour");
        }
        {
            // set_colour_bg_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.set_colour_bg_label = obj;
            lv_obj_set_pos(obj, 100, 230);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Background colour");
        }
        {
            // set_lang_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.set_lang_label = obj;
            lv_obj_set_pos(obj, 101, 310);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Language");
        }
        {
            // set_bottom_line
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.set_bottom_line = obj;
            lv_obj_set_pos(obj, 0, 400);
            lv_obj_set_size(obj, 800, 20);
            static lv_point_t line_points[] = {
                { 0, 0 }
            };
            lv_line_set_points(obj, line_points, 1);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x900000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // set_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.set_label = obj;
            lv_obj_set_pos(obj, 329, 430);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Settings");
        }
        {
            // set_colour_all_pages_ui_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.set_colour_all_pages_ui_text = obj;
            lv_obj_set_pos(obj, 458, 70);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "ColourText");
        }
        {
            // set_colour_indicator_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.set_colour_indicator_text = obj;
            lv_obj_set_pos(obj, 458, 150);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "IndicatorColourText");
        }
        {
            // set_colour_bg_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.set_colour_bg_text = obj;
            lv_obj_set_pos(obj, 458, 230);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "BackgroundColourText");
        }
        {
            // set_lang_text
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.set_lang_text = obj;
            lv_obj_set_pos(obj, 458, 310);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "LanguageText");
        }
        {
            // home_bttn_7
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.home_bttn_7 = obj;
            lv_obj_set_pos(obj, 320, 400);
            lv_obj_set_size(obj, 160, 80);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_img_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
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