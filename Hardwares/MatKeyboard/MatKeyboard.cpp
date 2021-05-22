//
// Created by yekai on 2021/5/17.
//

#include <cstdio>
#include <gui_guider.h>
#include "MatKeyboard.h"
#include "usart.h"

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
    l = 5 - l;
}

/*
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
                default:
                    break;
            }
            char ch[30];
            sprintf(ch, "%d\r\n", num);
            switch (dis) {
                case 0:
                    lv_textarea_set_text(guider_ui.screen_distance_text, ch);
                    break;
                case 1:
                    lv_textarea_set_text(guider_ui.screen_angle_text, ch);
                    break;
                default:
                    break;
            }
        }
    }
    if (dis == 2) {
        HAL_UART_Transmit(&huart1, (uint8_t *) "shoot\r\n", 8, 0xff);
        lv_scr_load(guider_ui.main);
    }
    l = 0;
    r = 0;
}

void Key::ReadBtn() {
    l = 0;
    r = 0;
    dis = 0;
    while (!((l == 4) && (r == 4))) {
        KeyScan();
        if (l && r) {
            switch (l * 10 + r) {
                case 24:
                    if (dis == 1) {
                        dis = 0;
                        lv_btn_toggle(guider_ui.main_Manual);
                        lv_btn_toggle(guider_ui.main_Auto);
                    }
                    break;
                case 34:
                    if (dis == 0) {
                        dis = 1;
                        lv_btn_toggle(guider_ui.main_Manual);
                        lv_btn_toggle(guider_ui.main_Auto);
                    }
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
        ReadNum();
    } else if (dis == 1) {
        HAL_UART_Transmit(&huart1, (uint8_t *) "auto shoot\r\n", 13, 0xff);
    }
}

Key::Key() : l(0), r(0), num(0), dis(0) {}


