/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "guider_fonts.h"

typedef struct
{
    lv_obj_t *screen;
    lv_obj_t *screen_distance;
    lv_obj_t *screen_angle;
    lv_obj_t *screen_distance_text;
    lv_obj_t *screen_label_1;
    lv_obj_t *screen_angle_text;
    lv_obj_t *screen_label_2;
    lv_obj_t *screen_shoot;
    lv_obj_t *screen_shoot_label;
    lv_obj_t *main;
    lv_obj_t *main_Manual;
    lv_obj_t *main_Manual_label;
    lv_obj_t *main_Auto;
    lv_obj_t *main_Auto_label;
    lv_obj_t *init;
    lv_obj_t *init_init;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen(lv_ui *ui);
void setup_scr_main(lv_ui *ui);
void setup_scr_init(lv_ui *ui);
#ifdef __cplusplus
}
#endif
#endif