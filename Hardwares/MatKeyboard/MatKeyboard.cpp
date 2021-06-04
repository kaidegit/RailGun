//
// Created by yekai on 2021/5/17.
//

#include <cstdio>
#include <gui_guider.h>
#include "MatKeyboard.h"
#include "usart.h"
#include "shoot.h"
#include "SteeringEngine.h"
#include "main_cpp.h"

uint16_t distance;

uint16_t angle;

uint16_t temp;

char ch[30];

extern Steering topSteering;
extern Steering bottomSteering;

void Key::SetRowHigh() {
    HAL_GPIO_WritePin(KBD_R1_GPIO_Port, KBD_R1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KBD_R2_GPIO_Port, KBD_R2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KBD_R3_GPIO_Port, KBD_R3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KBD_R4_GPIO_Port, KBD_R4_Pin, GPIO_PIN_SET);
}

void Key::SetRowLow() {
    HAL_GPIO_WritePin(KBD_R1_GPIO_Port, KBD_R1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KBD_R2_GPIO_Port, KBD_R2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KBD_R3_GPIO_Port, KBD_R3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KBD_R4_GPIO_Port, KBD_R4_Pin, GPIO_PIN_RESET);
}

void Key::SetColHigh() {
    HAL_GPIO_WritePin(KBD_C1_GPIO_Port, KBD_C1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KBD_C2_GPIO_Port, KBD_C2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KBD_C3_GPIO_Port, KBD_C3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KBD_C4_GPIO_Port, KBD_C4_Pin, GPIO_PIN_SET);
}

void Key::SetColLow() {
    HAL_GPIO_WritePin(KBD_C1_GPIO_Port, KBD_C1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KBD_C2_GPIO_Port, KBD_C2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KBD_C3_GPIO_Port, KBD_C3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KBD_C4_GPIO_Port, KBD_C4_Pin, GPIO_PIN_RESET);
}

void Key::Keyboard_Init() {
    SetRowLow();
    SetColHigh();
    HAL_Delay(10);
}

uint8_t Key::ScanCol() {
    if (!HAL_GPIO_ReadPin(KBD_C1_GPIO_Port, KBD_C1_Pin)) {
        return 1;
    }
    if (!HAL_GPIO_ReadPin(KBD_C2_GPIO_Port, KBD_C2_Pin)) {
        return 2;
    }
    if (!HAL_GPIO_ReadPin(KBD_C3_GPIO_Port, KBD_C3_Pin)) {
        return 3;
    }
    if (!HAL_GPIO_ReadPin(KBD_C4_GPIO_Port, KBD_C4_Pin)) {
        return 4;
    }
    return 0;
}

uint8_t Key::ScanRow() {
    if (!HAL_GPIO_ReadPin(KBD_R1_GPIO_Port, KBD_R1_Pin)) {
        return 1;
    }
    if (!HAL_GPIO_ReadPin(KBD_R2_GPIO_Port, KBD_R2_Pin)) {
        return 2;
    }
    if (!HAL_GPIO_ReadPin(KBD_R3_GPIO_Port, KBD_R3_Pin)) {
        return 3;
    }
    if (!HAL_GPIO_ReadPin(KBD_R4_GPIO_Port, KBD_R4_Pin)) {
        return 4;
    }
    return 0;
}

void Key::KeyScan() {
    l = 0;
    r = 0;
    r = ScanCol();
    if (r) {
        HAL_Delay(10);
        SetColLow();
        SetRowHigh();
        HAL_Delay(10);
        l = ScanRow();
        while (ScanRow()) {}
    }
    if (r && l) {
        TransposeMat();
    }
    Keyboard_Init();
}

void Key::TransposeMat() {
    auto temp = r;
    l = 5 - l;
    r = l;
    l = 5 - temp;
}

/*
 *
 * l 1  2  3  4
 * ----------------  r
 *   7  8  9  BK  |  1
 *   4  5  6  ^   |  2
 *   1  2  3  v   |  3
 *   0  <  >  OK  |  4
 */
void Key::ReadNum() {
    num = 0;
    l = 0;
    r = 0;
    while (!((l == 4) && (r == 4) && (dis == 2))) {
        KeyScan();
        if (l && r) {
            switch (l * 10 + r) {
                case 11:
                    num = num * 10 + 7;
                    break;
                case 21:
                    num = num * 10 + 8;
                    break;
                case 31:
                    num = num * 10 + 9;
                    break;
                case 41:
                    num = num / 10;
                    break;
                case 12:
                    num = num * 10 + 4;
                    break;
                case 22:
                    num = num * 10 + 5;
                    break;
                case 32:
                    num = num * 10 + 6;
                    break;
                case 13:
                    num = num * 10 + 1;
                    break;
                case 23:
                    num = num * 10 + 2;
                    break;
                case 33:
                    num = num * 10 + 3;
                    break;
                case 14:
                    num = num * 10;
                    break;
                case 42:
                    switch (dis) {
                        case 1: // 角度框 -> 距离框
                            num = 0;
                            dis--;
                            lv_textarea_set_cursor_hidden(guider_ui.screen_distance_text, false);
                            lv_textarea_set_cursor_hidden(guider_ui.screen_angle_text, true);
                            break;
                        case 2: // 发射按钮 -> 角度框
                            num = 0;
                            dis--;
                            lv_textarea_set_cursor_hidden(guider_ui.screen_angle_text, false);
                            lv_btn_toggle(guider_ui.screen_shoot);
                            break;
                        default:
                            break;
                    }
                    break;
                case 43:
                    switch (dis) {
                        case 0: // 距离框 -> 角度框
                            num = 0;
                            dis++;
                            lv_textarea_set_cursor_hidden(guider_ui.screen_angle_text, false);
                            lv_textarea_set_cursor_hidden(guider_ui.screen_distance_text, true);
                            break;
                        case 1: // 角度框 -> 发射按钮
                            num = 0;
                            dis++;
                            lv_textarea_set_cursor_hidden(guider_ui.screen_angle_text, true);
                            lv_btn_toggle(guider_ui.screen_shoot);
                            break;
                        default:
                            break;
                    }
                    break;
                case 24:
                    lv_switch_off(guider_ui.screen_sw_1, LV_ANIM_ON);
                    break;
                case 34:
                    lv_switch_on(guider_ui.screen_sw_1, LV_ANIM_ON);
                    break;
                default:
                    break;
            }
            char ch[30];
            sprintf(ch, "%d\r\n", num);
            switch (dis) {
                case 0:
                    lv_textarea_set_text(guider_ui.screen_distance_text, ch);
                    distance = num;
                    break;
                case 1:
                    lv_textarea_set_text(guider_ui.screen_angle_text, ch);
                    angle = num;
                    break;
                default:
                    break;
            }
        }
    }
    if (dis == 2) {
        Shoot(distance, angle);
        lv_scr_load(guider_ui.main);
    }
    l = 0;
    r = 0;
}

void Key::ReadBtn() {
    l = 0;
    r = 0;
    dis = 0;
    lv_obj_set_state(guider_ui.main_Manual, LV_STATE_CHECKED);
    lv_obj_clear_state(guider_ui.main_Auto, LV_STATE_CHECKED);
    lv_obj_clear_state(guider_ui.main_Running, LV_STATE_CHECKED);
    while (!((l == 4) && (r == 4))) {
        KeyScan();
        if (l && r) {
            switch (l * 10 + r) {
                // 向左移动
                case 24:
                    // 自动 -> 手动
                    if (dis == 1) {
                        dis = 0;
                        lv_btn_toggle(guider_ui.main_Manual);
                        lv_btn_toggle(guider_ui.main_Auto);
                        // 运动 -> 自动
                    } else if (dis == 2) {
                        dis = 1;
                        lv_btn_toggle(guider_ui.main_Running);
                        lv_btn_toggle(guider_ui.main_Auto);
                    }
                    break;
                    // 向右移动
                case 34:
                    // 手动 -> 自动
                    if (dis == 0) {
                        dis = 1;
                        lv_btn_toggle(guider_ui.main_Manual);
                        lv_btn_toggle(guider_ui.main_Auto);
                        // 自动 -> 运动
                    } else if (dis == 1) {
                        dis = 2;
                        lv_btn_toggle(guider_ui.main_Auto);
                        lv_btn_toggle(guider_ui.main_Running);
                    }
                    break;
                case 42:
                    topSteering.SetSteeringCompare(topSteering.SteeringCompare + 5);

                    sprintf(ch, "%lu", topSteering.SteeringCompare);
                    lv_label_set_text(guider_ui.main_Running_label, ch);
                    break;
                case 43:
                    topSteering.SetSteeringCompare(topSteering.SteeringCompare - 5);
                    sprintf(ch, "%lu", topSteering.SteeringCompare);
                    lv_label_set_text(guider_ui.main_Running_label, ch);
                    break;
                case 11:
                    temp = topSteering.SteeringCompare;
                    topSteering.SetSteeringCompare(1700);
                    HAL_Delay(2000);
                    topSteering.SetSteeringCompare(temp);
                    HAL_GPIO_WritePin(Charge_Control_GPIO_Port, Charge_Control_Pin, GPIO_PIN_SET);
                    HAL_Delay(4000);
                    HAL_GPIO_WritePin(Charge_Control_GPIO_Port, Charge_Control_Pin, GPIO_PIN_RESET);
                    HAL_GPIO_WritePin(Shot_Control_GPIO_Port, Shot_Control_Pin, GPIO_PIN_RESET);
                    HAL_Delay(500);
                    HAL_GPIO_WritePin(Shot_Control_GPIO_Port, Shot_Control_Pin, GPIO_PIN_SET);
                    break;
                default:
                    break;
            }
        }
    }
    if (dis == 0) {
        lv_scr_load(guider_ui.screen);
        lv_textarea_set_cursor_hidden(guider_ui.screen_distance_text, false);
        lv_textarea_set_cursor_hidden(guider_ui.screen_angle_text, true);
        lv_obj_clear_state(guider_ui.screen_shoot, LV_STATE_CHECKED);
        lv_textarea_set_text(guider_ui.screen_distance_text, "0");
        lv_textarea_set_text(guider_ui.screen_angle_text, "0");
        ReadNum();
    } else if (dis == 1) {
        AutoShoot();
    } else if (dis == 2) {
        RunningShoot();
    }
}


Key::Key() : l(0), r(0), num(0), dis(0) {}


