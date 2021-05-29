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
#include "SteeringEngine.h"

lv_ui guider_ui;
Steering topSteering(&htim2, TIM_CHANNEL_1);
Steering bottomSteering(&htim2, TIM_CHANNEL_3);
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

    topSteering.init(1400, 1800, 1700);
    bottomSteering.init(1250, 1800, 1530);

    lv_scr_load(guider_ui.main);
    lv_btn_toggle(guider_ui.main_Manual);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (true) {
        key.ReadBtn();
    }
#pragma clang diagnostic pop

}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == htim14.Instance) {
        lv_tick_inc(5);
        lv_task_handler();
    } else if (htim->Instance == htim13.Instance){
        HAL_GPIO_WritePin(Shot_Control_GPIO_Port,Shot_Control_Pin,GPIO_PIN_RESET);
        HAL_TIM_Base_Stop_IT(&htim13);
    }
}