/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"

static lv_obj_t * kb;
static void kb_event_cb(lv_obj_t * event_kb, lv_event_t event)
{
    /* Just call the regular event handler */
    lv_keyboard_def_event_cb(event_kb, event);
    if(event == LV_EVENT_APPLY || event == LV_EVENT_CANCEL){
        if(NULL != kb){
            lv_obj_del(kb);
        }
    }
}
static void text_area_event_cb(lv_obj_t* ta, lv_event_t event)
{

    if(event == LV_EVENT_CLICKED){
        if( !lv_debug_check_obj_valid(kb) ){
            /* Create a keyboard and make it fill the width of the above text areas */
            kb = lv_keyboard_create(lv_scr_act(), NULL);
            lv_obj_set_event_cb(kb, kb_event_cb);
            lv_obj_set_size(kb,  LV_HOR_RES, LV_VER_RES / 2);
        }
        lv_keyboard_set_textarea(kb, ta);
        lv_keyboard_set_cursor_manage(kb, true);
    }
}

void setup_scr_screen(lv_ui *ui){

    //Write codes screen
    ui->screen = lv_obj_create(NULL, NULL);

    //Write codes screen_dis
    ui->screen_dis = lv_label_create(ui->screen, NULL);
    lv_label_set_text(ui->screen_dis, "距 离");
    lv_label_set_long_mode(ui->screen_dis, LV_LABEL_LONG_BREAK);
    lv_label_set_align(ui->screen_dis, LV_LABEL_ALIGN_CENTER);

    //Write style LV_LABEL_PART_MAIN for screen_dis
    static lv_style_t style_screen_dis_main;
    lv_style_init(&style_screen_dis_main);

    //Write style state: LV_STATE_DEFAULT for style_screen_dis_main
    lv_style_set_radius(&style_screen_dis_main, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&style_screen_dis_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&style_screen_dis_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&style_screen_dis_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_style_set_bg_opa(&style_screen_dis_main, LV_STATE_DEFAULT, 255);
    lv_style_set_text_color(&style_screen_dis_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&style_screen_dis_main, LV_STATE_DEFAULT, &lv_font_simsun_36);
    lv_style_set_text_letter_space(&style_screen_dis_main, LV_STATE_DEFAULT, 2);
    lv_style_set_pad_left(&style_screen_dis_main, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_right(&style_screen_dis_main, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_top(&style_screen_dis_main, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_bottom(&style_screen_dis_main, LV_STATE_DEFAULT, 0);
    lv_obj_add_style(ui->screen_dis, LV_LABEL_PART_MAIN, &style_screen_dis_main);
    lv_obj_set_pos(ui->screen_dis, 24, 43);
    lv_obj_set_size(ui->screen_dis, 188, 0);

    //Write codes screen_angle
    ui->screen_angle = lv_label_create(ui->screen, NULL);
    lv_label_set_text(ui->screen_angle, "角 度");
    lv_label_set_long_mode(ui->screen_angle, LV_LABEL_LONG_BREAK);
    lv_label_set_align(ui->screen_angle, LV_LABEL_ALIGN_CENTER);

    //Write style LV_LABEL_PART_MAIN for screen_angle
    static lv_style_t style_screen_angle_main;
    lv_style_init(&style_screen_angle_main);

    //Write style state: LV_STATE_DEFAULT for style_screen_angle_main
    lv_style_set_radius(&style_screen_angle_main, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&style_screen_angle_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&style_screen_angle_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&style_screen_angle_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_style_set_bg_opa(&style_screen_angle_main, LV_STATE_DEFAULT, 255);
    lv_style_set_text_color(&style_screen_angle_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&style_screen_angle_main, LV_STATE_DEFAULT, &lv_font_simsun_36);
    lv_style_set_text_letter_space(&style_screen_angle_main, LV_STATE_DEFAULT, 2);
    lv_style_set_pad_left(&style_screen_angle_main, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_right(&style_screen_angle_main, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_top(&style_screen_angle_main, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_bottom(&style_screen_angle_main, LV_STATE_DEFAULT, 0);
    lv_obj_add_style(ui->screen_angle, LV_LABEL_PART_MAIN, &style_screen_angle_main);
    lv_obj_set_pos(ui->screen_angle, 27, 153);
    lv_obj_set_size(ui->screen_angle, 188, 0);

    //Write codes screen_distance
    ui->screen_distance = lv_textarea_create(ui->screen, NULL);

    //Write style LV_PAGE_PART_BG for screen_distance
    static lv_style_t style_screen_distance_bg;
    lv_style_init(&style_screen_distance_bg);

    //Write style state: LV_STATE_DEFAULT for style_screen_distance_bg
    lv_style_set_radius(&style_screen_distance_bg, LV_STATE_DEFAULT, 0);
    lv_style_set_border_color(&style_screen_distance_bg, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
    lv_style_set_border_width(&style_screen_distance_bg, LV_STATE_DEFAULT, 2);
    lv_style_set_text_color(&style_screen_distance_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&style_screen_distance_bg, LV_STATE_DEFAULT, &lv_font_simsun_20);
    lv_style_set_text_letter_space(&style_screen_distance_bg, LV_STATE_DEFAULT, 2);
    lv_style_set_pad_left(&style_screen_distance_bg, LV_STATE_DEFAULT, 2);
    lv_style_set_pad_right(&style_screen_distance_bg, LV_STATE_DEFAULT, 2);
    lv_style_set_pad_top(&style_screen_distance_bg, LV_STATE_DEFAULT, 2);
    lv_style_set_pad_bottom(&style_screen_distance_bg, LV_STATE_DEFAULT, 2);
    lv_obj_add_style(ui->screen_distance, LV_PAGE_PART_BG, &style_screen_distance_bg);

    //Write style LV_PAGE_PART_SCROLLABLE for screen_distance
    static lv_style_t style_screen_distance_scrollable;
    lv_style_init(&style_screen_distance_scrollable);

    //Write style state: LV_STATE_DEFAULT for style_screen_distance_scrollable
    lv_style_set_radius(&style_screen_distance_scrollable, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&style_screen_distance_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&style_screen_distance_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&style_screen_distance_scrollable, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_style_set_bg_opa(&style_screen_distance_scrollable, LV_STATE_DEFAULT, 255);
    lv_obj_add_style(ui->screen_distance, LV_PAGE_PART_SCROLLABLE, &style_screen_distance_scrollable);

    //Write style LV_PAGE_PART_EDGE_FLASH for screen_distance
    static lv_style_t style_screen_distance_edge_flash;
    lv_style_init(&style_screen_distance_edge_flash);

    //Write style state: LV_STATE_DEFAULT for style_screen_distance_edge_flash
    lv_style_set_radius(&style_screen_distance_edge_flash, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&style_screen_distance_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&style_screen_distance_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&style_screen_distance_edge_flash, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_style_set_bg_opa(&style_screen_distance_edge_flash, LV_STATE_DEFAULT, 255);
    lv_obj_add_style(ui->screen_distance, LV_PAGE_PART_EDGE_FLASH, &style_screen_distance_edge_flash);
    lv_obj_set_pos(ui->screen_distance, 20, 96);
    lv_obj_set_size(ui->screen_distance, 160, 44);
    lv_textarea_set_text(ui->screen_distance,"Hello World");
    lv_obj_set_event_cb(ui->screen_distance, text_area_event_cb);
    lv_textarea_set_text_align(ui->screen_distance, LV_LABEL_ALIGN_LEFT);

    //Write codes screen_label_1
    ui->screen_label_1 = lv_label_create(ui->screen, NULL);
    lv_label_set_text(ui->screen_label_1, "cm");
    lv_label_set_long_mode(ui->screen_label_1, LV_LABEL_LONG_BREAK);
    lv_label_set_align(ui->screen_label_1, LV_LABEL_ALIGN_CENTER);

    //Write style LV_LABEL_PART_MAIN for screen_label_1
    static lv_style_t style_screen_label_1_main;
    lv_style_init(&style_screen_label_1_main);

    //Write style state: LV_STATE_DEFAULT for style_screen_label_1_main
    lv_style_set_radius(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&style_screen_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&style_screen_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&style_screen_label_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_style_set_bg_opa(&style_screen_label_1_main, LV_STATE_DEFAULT, 255);
    lv_style_set_text_color(&style_screen_label_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&style_screen_label_1_main, LV_STATE_DEFAULT, &lv_font_simsun_20);
    lv_style_set_text_letter_space(&style_screen_label_1_main, LV_STATE_DEFAULT, 2);
    lv_style_set_pad_left(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_right(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_top(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_bottom(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
    lv_obj_add_style(ui->screen_label_1, LV_LABEL_PART_MAIN, &style_screen_label_1_main);
    lv_obj_set_pos(ui->screen_label_1, 191, 99);
    lv_obj_set_size(ui->screen_label_1, 26, 0);

    //Write codes screen_angl
    ui->screen_angl = lv_textarea_create(ui->screen, NULL);

    //Write style LV_PAGE_PART_BG for screen_angl
    static lv_style_t style_screen_angl_bg;
    lv_style_init(&style_screen_angl_bg);

    //Write style state: LV_STATE_DEFAULT for style_screen_angl_bg
    lv_style_set_radius(&style_screen_angl_bg, LV_STATE_DEFAULT, 0);
    lv_style_set_border_color(&style_screen_angl_bg, LV_STATE_DEFAULT, lv_color_make(0x01, 0xa2, 0xb1));
    lv_style_set_border_width(&style_screen_angl_bg, LV_STATE_DEFAULT, 2);
    lv_style_set_text_color(&style_screen_angl_bg, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&style_screen_angl_bg, LV_STATE_DEFAULT, &lv_font_simsun_20);
    lv_style_set_text_letter_space(&style_screen_angl_bg, LV_STATE_DEFAULT, 2);
    lv_style_set_pad_left(&style_screen_angl_bg, LV_STATE_DEFAULT, 2);
    lv_style_set_pad_right(&style_screen_angl_bg, LV_STATE_DEFAULT, 2);
    lv_style_set_pad_top(&style_screen_angl_bg, LV_STATE_DEFAULT, 2);
    lv_style_set_pad_bottom(&style_screen_angl_bg, LV_STATE_DEFAULT, 2);
    lv_obj_add_style(ui->screen_angl, LV_PAGE_PART_BG, &style_screen_angl_bg);

    //Write style LV_PAGE_PART_SCROLLABLE for screen_angl
    static lv_style_t style_screen_angl_scrollable;
    lv_style_init(&style_screen_angl_scrollable);

    //Write style state: LV_STATE_DEFAULT for style_screen_angl_scrollable
    lv_style_set_radius(&style_screen_angl_scrollable, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&style_screen_angl_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&style_screen_angl_scrollable, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&style_screen_angl_scrollable, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_style_set_bg_opa(&style_screen_angl_scrollable, LV_STATE_DEFAULT, 255);
    lv_obj_add_style(ui->screen_angl, LV_PAGE_PART_SCROLLABLE, &style_screen_angl_scrollable);

    //Write style LV_PAGE_PART_EDGE_FLASH for screen_angl
    static lv_style_t style_screen_angl_edge_flash;
    lv_style_init(&style_screen_angl_edge_flash);

    //Write style state: LV_STATE_DEFAULT for style_screen_angl_edge_flash
    lv_style_set_radius(&style_screen_angl_edge_flash, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&style_screen_angl_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&style_screen_angl_edge_flash, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&style_screen_angl_edge_flash, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_style_set_bg_opa(&style_screen_angl_edge_flash, LV_STATE_DEFAULT, 255);
    lv_obj_add_style(ui->screen_angl, LV_PAGE_PART_EDGE_FLASH, &style_screen_angl_edge_flash);
    lv_obj_set_pos(ui->screen_angl, 19, 202);
    lv_obj_set_size(ui->screen_angl, 160, 44);
    lv_textarea_set_text(ui->screen_angl,"Hello World");
    lv_obj_set_event_cb(ui->screen_angl, text_area_event_cb);
    lv_textarea_set_text_align(ui->screen_angl, LV_LABEL_ALIGN_LEFT);

    //Write codes screen_label_2
    ui->screen_label_2 = lv_label_create(ui->screen, NULL);
    lv_label_set_text(ui->screen_label_2, "o");
    lv_label_set_long_mode(ui->screen_label_2, LV_LABEL_LONG_BREAK);
    lv_label_set_align(ui->screen_label_2, LV_LABEL_ALIGN_CENTER);

    //Write style LV_LABEL_PART_MAIN for screen_label_2
    static lv_style_t style_screen_label_2_main;
    lv_style_init(&style_screen_label_2_main);

    //Write style state: LV_STATE_DEFAULT for style_screen_label_2_main
    lv_style_set_radius(&style_screen_label_2_main, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_color(&style_screen_label_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&style_screen_label_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&style_screen_label_2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    lv_style_set_bg_opa(&style_screen_label_2_main, LV_STATE_DEFAULT, 255);
    lv_style_set_text_color(&style_screen_label_2_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&style_screen_label_2_main, LV_STATE_DEFAULT, &lv_font_simsun_20);
    lv_style_set_text_letter_space(&style_screen_label_2_main, LV_STATE_DEFAULT, 2);
    lv_style_set_pad_left(&style_screen_label_2_main, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_right(&style_screen_label_2_main, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_top(&style_screen_label_2_main, LV_STATE_DEFAULT, 0);
    lv_style_set_pad_bottom(&style_screen_label_2_main, LV_STATE_DEFAULT, 0);
    lv_obj_add_style(ui->screen_label_2, LV_LABEL_PART_MAIN, &style_screen_label_2_main);
    lv_obj_set_pos(ui->screen_label_2, 191, 203);
    lv_obj_set_size(ui->screen_label_2, 26, 0);
}