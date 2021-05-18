//
// Created by yekai on 2021/5/17.
//

#include "MatKeyboard.h"

void SetRowHigh() {
    HAL_GPIO_WritePin(KBD_R1_GPIO_Port, KBD_R1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KBD_R2_GPIO_Port, KBD_R2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KBD_R3_GPIO_Port, KBD_R3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KBD_R4_GPIO_Port, KBD_R4_Pin, GPIO_PIN_SET);
}

void SetRowLow() {
    HAL_GPIO_WritePin(KBD_R1_GPIO_Port, KBD_R1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KBD_R2_GPIO_Port, KBD_R2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KBD_R3_GPIO_Port, KBD_R3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KBD_R4_GPIO_Port, KBD_R4_Pin, GPIO_PIN_RESET);
}

void SetColHigh() {
    HAL_GPIO_WritePin(KBD_C1_GPIO_Port, KBD_C1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KBD_C2_GPIO_Port, KBD_C2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KBD_C3_GPIO_Port, KBD_C3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KBD_C4_GPIO_Port, KBD_C4_Pin, GPIO_PIN_SET);
}

void SetColLow() {
    HAL_GPIO_WritePin(KBD_C1_GPIO_Port, KBD_C1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KBD_C2_GPIO_Port, KBD_C2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KBD_C3_GPIO_Port, KBD_C3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KBD_C4_GPIO_Port, KBD_C4_Pin, GPIO_PIN_RESET);
}

void Keyboard_Init() {
    SetRowLow();
    SetColHigh();
    HAL_Delay(10);
}

uint8_t ScanCol() {
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

uint8_t ScanRow() {
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

void KeyScan(struct Key *key) {
    key->l = 0;
    key->r = 0;
    key->r = ScanCol();
    if (key->r) {
        HAL_Delay(10);
        SetColLow();
        SetRowHigh();
        HAL_Delay(10);
        key->l = ScanRow();
        while (ScanRow()) {}
    }
    if (key->r && key->l) {
        TransposeMat(key);
    }
    Keyboard_Init();
}

void TransposeMat(struct Key *key) {
    key->l = 5 - key->l;
}

/*
 *   1  2  3  4
 * ----------------
 *   7  8  9  BK  |  1
 *   4  5  6      |  2
 *   1  2  3      |  3
 *   0        OK  |  4
 */
uint16_t ReadNum() {
    struct Key key;
    uint16_t num = 0;
    while (!((key.l == 4) && (key.r == 4))) {
        KeyScan(&key);
        if (key.l && key.r) {
            switch (key.l * 10 + key.r) {
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
                    num = num * 10 +4;
                    break;
                case 22:
                    num = num * 10 +5;
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
                    num = num * 10 +3;
                    break;
                case 14:
                    num = num * 10;
                    break;
                default:
                    break;
            }
        }
    }
    return num;
}


