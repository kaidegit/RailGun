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
#include "gui_guider.h"
#include "events_init.h"

lv_ui guider_ui;

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
    setup_ui(&guider_ui);
    events_init(&guider_ui);


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (true) {
        key.ReadNum();
//        sprintf(ch, "%d\r\n", key.num);
//        lv_textarea_set_text(guider_ui.screen_distance,ch);
        HAL_UART_Transmit(&huart1, (uint8_t *) ch, strlen(ch), 0xff);
    }
#pragma clang diagnostic pop

}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim->Instance == htim14.Instance){
        lv_tick_inc(5);
        lv_task_handler();
    }
}