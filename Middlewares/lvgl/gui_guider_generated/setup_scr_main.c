/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_main(lv_ui *ui){

    //Write codes main
    ui->main = lv_obj_create(NULL, NULL);

    //Write codes main_Manual
    ui->main_Manual = lv_btn_create(ui->main, NULL);

    //Write style LV_BTN_PART_MAIN for main_Manual
    static lv_style_t style_main_Manual_main;
    lv_style_init(&style_main_Manual_main);

    //Write style state: LV_STATE_DEFAULT for style_main_Manual_main
    lv_style_set_radius(&style_main_Manual_main, LV_STATE_DEFAULT, 50);
    lv_style_set_bg_color(&style_main_Manual_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&style_main_Manual_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&style_main_Manual_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_style_set_bg_opa(&style_main_Manual_main, LV_STATE_DEFAULT, 255);
    lv_style_set_border_color(&style_main_Manual_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
    lv_style_set_border_width(&style_main_Manual_main, LV_STATE_DEFAULT, 2);
    lv_style_set_border_opa(&style_main_Manual_main, LV_STATE_DEFAULT, 255);
    lv_style_set_outline_color(&style_main_Manual_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
    lv_style_set_outline_opa(&style_main_Manual_main, LV_STATE_DEFAULT, 255);
    lv_obj_add_style(ui->main_Manual, LV_BTN_PART_MAIN, &style_main_Manual_main);
    lv_obj_set_pos(ui->main_Manual, 10, 145);
    lv_obj_set_size(ui->main_Manual, 100, 50);
    ui->main_Manual_label = lv_label_create(ui->main_Manual, NULL);
    lv_label_set_text(ui->main_Manual_label, "手动模式");
    lv_obj_set_style_local_text_color(ui->main_Manual_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
    lv_obj_set_style_local_text_font(ui->main_Manual_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_12);

    //Write codes main_Auto
    ui->main_Auto = lv_btn_create(ui->main, NULL);

    //Write style LV_BTN_PART_MAIN for main_Auto
    static lv_style_t style_main_Auto_main;
    lv_style_init(&style_main_Auto_main);

    //Write style state: LV_STATE_DEFAULT for style_main_Auto_main
    lv_style_set_radius(&style_main_Auto_main, LV_STATE_DEFAULT, 50);
    lv_style_set_bg_color(&style_main_Auto_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&style_main_Auto_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&style_main_Auto_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_style_set_bg_opa(&style_main_Auto_main, LV_STATE_DEFAULT, 255);
    lv_style_set_border_color(&style_main_Auto_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
    lv_style_set_border_width(&style_main_Auto_main, LV_STATE_DEFAULT, 2);
    lv_style_set_border_opa(&style_main_Auto_main, LV_STATE_DEFAULT, 255);
    lv_style_set_outline_color(&style_main_Auto_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
    lv_style_set_outline_opa(&style_main_Auto_main, LV_STATE_DEFAULT, 255);
    lv_obj_add_style(ui->main_Auto, LV_BTN_PART_MAIN, &style_main_Auto_main);
    lv_obj_set_pos(ui->main_Auto, 130, 145);
    lv_obj_set_size(ui->main_Auto, 100, 50);
    ui->main_Auto_label = lv_label_create(ui->main_Auto, NULL);
    lv_label_set_text(ui->main_Auto_label, "自动模式");
    lv_obj_set_style_local_text_color(ui->main_Auto_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
    lv_obj_set_style_local_text_font(ui->main_Auto_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_12);

    //Write codes main_Running
    ui->main_Running = lv_btn_create(ui->main, NULL);

    //Write style LV_BTN_PART_MAIN for main_Running
    static lv_style_t style_main_Running_main;
    lv_style_init(&style_main_Running_main);

    //Write style state: LV_STATE_DEFAULT for style_main_Running_main
    lv_style_set_radius(&style_main_Running_main, LV_STATE_DEFAULT, 50);
    lv_style_set_bg_color(&style_main_Running_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&style_main_Running_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&style_main_Running_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_style_set_bg_opa(&style_main_Running_main, LV_STATE_DEFAULT, 255);
    lv_style_set_border_color(&style_main_Running_main, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
    lv_style_set_border_width(&style_main_Running_main, LV_STATE_DEFAULT, 2);
    lv_style_set_border_opa(&style_main_Running_main, LV_STATE_DEFAULT, 255);
    lv_style_set_outline_color(&style_main_Running_main, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
    lv_style_set_outline_opa(&style_main_Running_main, LV_STATE_DEFAULT, 255);
    lv_obj_add_style(ui->main_Running, LV_BTN_PART_MAIN, &style_main_Running_main);
    lv_obj_set_pos(ui->main_Running, 69, 218);
    lv_obj_set_size(ui->main_Running, 100, 50);
    ui->main_Running_label = lv_label_create(ui->main_Running, NULL);
    lv_label_set_text(ui->main_Running_label, "运动模式");
    lv_obj_set_style_local_text_color(ui->main_Running_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
    lv_obj_set_style_local_text_font(ui->main_Running_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simsun_12);
}