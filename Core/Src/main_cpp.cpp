//
// Created by yekai on 2021/5/18.
//

#include <MatKeyboard.h>
#include <cstring>
#include <cstdio>
#include <porting/lv_port_disp.h>
#include "main_cpp.h"
#include "usart.h"
#include "main.h"
#include "LCD.h"
#include "lvgl.h"
#include "tim.h"

LV_IMG_DECLARE(watch_bg);
LV_IMG_DECLARE(hour);
LV_IMG_DECLARE(minute);
LV_IMG_DECLARE(second);

lv_obj_t *lvMinute;
lv_obj_t *lvHour;
lv_obj_t *lvSecond;

uint8_t Minute = 59;
uint8_t Hour = 8;
uint8_t Second = 2;

static void update_time(struct _lv_task_t *arg) {
    if (lvHour != NULL) {
        // Hour,Minute,Second;
        uint16_t h = Hour * 300 + Minute / 12 % 12 * 60;
        lv_img_set_angle(lvHour, h);
        lv_img_set_angle(lvMinute, Minute * 6 * 10);
        lv_img_set_angle(lvSecond, Second * 6 * 10);
    }
    if (++Second >= 60) {
        Second = 0;
        if (++Minute >= 60) {
            Minute = 0;
            if (++Hour >= 12) Hour = 0;
        }
    }
}

void analog(lv_obj_t *win) {
    lv_obj_t *central = win;

    lv_obj_set_size(central, LV_HOR_RES_MAX, LV_VER_RES_MAX);
    lv_obj_set_pos(central, 0, 0);

    lv_obj_t *img = lv_img_create(central, NULL);
    lv_img_set_src(img, &watch_bg);

    lv_obj_set_size(img, 200, 200);
    lv_obj_set_auto_realign(img, true);
    lv_obj_align(img, central, LV_ALIGN_CENTER, 0, 0);

    lvHour = lv_img_create(central, NULL);
    lv_img_set_src(lvHour, &hour);
    lv_obj_align(lvHour, img, LV_ALIGN_CENTER, 0, 0);
    uint16_t h = Hour * 300 + Minute / 12 % 12 * 60;
    lv_img_set_angle(lvHour, h);

    lvMinute = lv_img_create(central, NULL);
    lv_img_set_src(lvMinute, &minute);
    lv_obj_align(lvMinute, img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_angle(lvHour, Minute * 60);

    lvSecond = lv_img_create(central, NULL);
    lv_img_set_src(lvSecond, &second);
    lv_obj_align(lvSecond, img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_angle(lvSecond, Second * 60);

    lv_task_create(update_time, 1000, LV_TASK_PRIO_LOW, NULL);
}

void main_cpp() {
    char ch[30];
    uint8_t i = 0;
    Key key;
    key.Keyboard_Init();
    LCD_Init();
    LCD_Clear(BLUE);
    HAL_TIM_Base_Start_IT(&htim14);

    lv_init();
    lv_port_disp_init();
    analog(lv_scr_act());

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (true) {
//        LCD_DrawPic(0, 0, 240, 480, gImage_bear);
//        LCD_Fast_DrawPoint(i, i, i * 0xf0);
//        LCD_Draw_Circle(50, 50, 20);
//        key.ReadNum();
//        sprintf(ch, "cpp:%d\r\n", key.num);
//        HAL_UART_Transmit(&huart1, (uint8_t *) ch, strlen(ch), 0xff);
    }
#pragma clang diagnostic pop

}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim->Instance == htim14.Instance){
        lv_tick_inc(5);
        lv_task_handler();
    }
}