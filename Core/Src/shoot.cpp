//
// Created by yekai on 2021/5/22.
//

#include <cstdlib>
#include <SteeringEngine.h>
#include "shoot.h"
#include "usart.h"
#include "cstring"
#include "tim.h"
#include <cmath>
#include <gui_guider.h>
#include <cstdio>

char uartByte;
bool receivingFlag;
bool receiveDone;
char uartBuf[30];
enum Position pos_flag;
uint16_t pos_err;
uint8_t len;
uint16_t dis_rec, angle_rec;
uint8_t mode;

bool position;
bool isShot = false;

extern Steering topSteering;
extern Steering bottomSteering;

// 手动输入模式
void Shoot(uint16_t dis, uint16_t angle) {
//    switch ((dis + 5) / 10) {
//        case 20:
//            topSteering.SetSteeringCompare(1510);
//            break;
//        case 21:
//            topSteering.SetSteeringCompare(1515);
//            break;
//        case 22:
//            topSteering.SetSteeringCompare(1525);
//            break;
//        case 23:
//            topSteering.SetSteeringCompare(1530);
//            break;
//        case 24:
//            topSteering.SetSteeringCompare(1535);
//            break;
//        case 25:
//            topSteering.SetSteeringCompare(1540);
//            break;
//        case 26:
//            topSteering.SetSteeringCompare(1550);
//            break;
//        case 27:
//            topSteering.SetSteeringCompare(1555);
//            break;
//        case 28:
//            topSteering.SetSteeringCompare(1565);
//            break;
//        case 29:
//            topSteering.SetSteeringCompare(1570);
//            break;
//        case 30:
//            topSteering.SetSteeringCompare(1575);
//            break;
//        case 31:
//            topSteering.SetSteeringCompare(1580);
//            break;
//        default:
//            if (dis>300){
//                topSteering.SetSteeringCompare(1580);
//            } else {
//                topSteering.SetSteeringCompare(1510);
//            }
//            break;
//    }
    auto p1 = -1.537793861264471e-06;
    auto p2 = 0.001674084311962;
    auto p3 = -0.675897479945635;
    auto p4 = 1.208877170121495e+02;
    auto p5 = -6.545889634786366e+03;
    auto pwm_top = p1 * pow(dis, 4) + p2 * pow(dis, 3) + p3 * pow(dis, 2) + p4 * dis + p5;
    topSteering.SetSteeringCompare((uint32_t) pwm_top);

    if (lv_switch_get_state(guider_ui.screen_sw_1)) {
        auto pwm_btm = -0.000386123680241354 * pow(angle, 4) + 0.0280159056629665 * pow(angle, 3) -
                       0.676912107500386 * pow(angle, 2) - 3.11750994103909 * pow(angle, 1) + 1532.09954751131;
        bottomSteering.SetSteeringCompare((uint32_t) pwm_btm);
    } else {
        auto pwm_btm = -0.000149184149184174 * pow(angle, 4) + 0.0141724941724961 * pow(angle, 3) -
                       0.427599067599110 * pow(angle, 2) + 13.3431901431904 * pow(angle, 1) + 1531.43956043956;
        bottomSteering.SetSteeringCompare((uint32_t) pwm_btm);
    }

    Charge(4);
    HAL_GPIO_WritePin(Shot_Control_GPIO_Port, Shot_Control_Pin, GPIO_PIN_RESET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(Shot_Control_GPIO_Port, Shot_Control_Pin, GPIO_PIN_SET);
    HAL_Delay(2000);
    topSteering.SetSteeringCompare(1700);
    HAL_UART_Transmit(&huart1, (uint8_t *) "shoot\r\n", strlen("shoot\r\n"), 0xff);
}

// 自动模式
void AutoShoot() {
    receiveDone = false;
    pos_flag = LEFT;
    enum Position last_move;
    while (!((pos_flag == STOP) || (pos_flag == DIS))) {
        receiveDone = false;
        if (pos_flag == LEFT) {
            last_move = LEFT;
            HAL_UART_Receive_IT(&huart6, (uint8_t *) &uartByte, 1);
            bottomSteering.SetSteeringCompare(bottomSteering.SteeringCompare + 5);
        } else if (pos_flag == RIGHT) {
            last_move = RIGHT;
            HAL_UART_Receive_IT(&huart6, (uint8_t *) &uartByte, 1);
            bottomSteering.SetSteeringCompare(bottomSteering.SteeringCompare - 5);
        } else if (pos_flag == NFD) {
            HAL_UART_Receive_IT(&huart6, (uint8_t *) &uartByte, 1);
            if (bottomSteering.SteeringCompare > 1530) {
                bottomSteering.SetSteeringCompare(1350);
            } else {
                bottomSteering.SetSteeringCompare(1700);
            }
            HAL_Delay(100);
        }
//        HAL_Delay(30);
        while (!receiveDone) {}
    }

    if (last_move == LEFT) {
        bottomSteering.SetSteeringCompare(bottomSteering.SteeringCompare - 5);
    } else {
        bottomSteering.SetSteeringCompare(bottomSteering.SteeringCompare + 5);
    }
    while (pos_flag != DIS) {
        receiveDone = false;
        HAL_UART_Receive_IT(&huart6, (uint8_t *) &uartByte, 1);
        while (!receiveDone) {}
    }

//    pos_err -= 30;
//    switch ((pos_err + 5) / 10) {
//        case 20:
//            topSteering.SetSteeringCompare(1510);
//            break;
//        case 21:
//            topSteering.SetSteeringCompare(1515);
//            break;
//        case 22:
//            topSteering.SetSteeringCompare(1525);
//            break;
//        case 23:
//            topSteering.SetSteeringCompare(1530);
//            break;
//        case 24:
//            topSteering.SetSteeringCompare(1535);
//            break;
//        case 25:
//            topSteering.SetSteeringCompare(1540);
//            break;
//        case 26:
//            topSteering.SetSteeringCompare(1550);
//            break;
//        case 27:
//            topSteering.SetSteeringCompare(1555);
//            break;
//        case 28:
//            topSteering.SetSteeringCompare(1565);
//            break;
//        case 29:
//            topSteering.SetSteeringCompare(1570);
//            break;
//        case 30:
//            topSteering.SetSteeringCompare(1575);
//            break;
//        case 31:
//            topSteering.SetSteeringCompare(1580);
//            break;
//        default:
//            break;
//    }
    auto p1 = -1.537793861264471e-06;
    auto p2 = 0.001674084311962;
    auto p3 = -0.675897479945635;
    auto p4 = 1.208877170121495e+02;
    auto p5 = -6.545889634786366e+03;
    pos_err -= 30;
    auto pwm_top = p1 * pow(pos_err, 4) + p2 * pow(pos_err, 3) + p3 * pow(pos_err, 2) + p4 * pos_err + p5;
    topSteering.SetSteeringCompare(pwm_top);


    Charge(5);
    HAL_GPIO_WritePin(Shot_Control_GPIO_Port, Shot_Control_Pin, GPIO_PIN_RESET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(Shot_Control_GPIO_Port, Shot_Control_Pin, GPIO_PIN_SET);
    topSteering.SetSteeringCompare(1700);

//    HAL_UART_Transmit(&huart1, (uint8_t *) "auto shoot\r\n", strlen("auto shoot\r\n"), 0xff);
}

// 运动射击模式
void RunningShoot() {
    isShot = false;
    // 充电
    HAL_GPIO_WritePin(Charge_Control_GPIO_Port, Charge_Control_Pin, GPIO_PIN_SET);
    // 仰角0度
    topSteering.SetSteeringCompare(1455);
    // 水平方向与中轴线夹角-30
    bottomSteering.SetSteeringCompare(1270);
    HAL_Delay(1000);
    topSteering.SetSteeringCompare(1585);
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);


    // -30~30~-30
    while (!isShot) {
        for (auto i = 1270; i < 1809; i += 3) {
            bottomSteering.SetSteeringCompare(i);
//            HAL_UART_Receive_IT(&huart6, (uint8_t *) &uartByte, 1);
//            while (!receiveDone) {}
//            if (pos_flag == STOP) {
//                HAL_GPIO_WritePin(Charge_Control_GPIO_Port, Charge_Control_Pin, GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(Shot_Control_GPIO_Port, Shot_Control_Pin, GPIO_PIN_SET);
//                isShot = true;
//            }
            HAL_Delay(10);
        }
        for (auto i = 1809; i > 1270; i -= 3) {
            bottomSteering.SetSteeringCompare(i);
//            HAL_UART_Receive_IT(&huart6, (uint8_t *) &uartByte, 1);
//            while (!receiveDone) {}
//            if (pos_flag == STOP) {
//                HAL_GPIO_WritePin(Charge_Control_GPIO_Port, Charge_Control_Pin, GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(Shot_Control_GPIO_Port, Shot_Control_Pin, GPIO_PIN_SET);
//                isShot = true;
//            }
            HAL_Delay(10);
        }
    }
    HAL_GPIO_WritePin(Shot_Control_GPIO_Port, Shot_Control_Pin, GPIO_PIN_SET);
    topSteering.SetSteeringCompare(1700);
    // 延时500ms

//    __HAL_TIM_SetCounter(&htim13, 0);
//    HAL_TIM_Base_Start_IT(&htim13);

//   }
//    }


}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == htim2.Instance) {
        HAL_GPIO_WritePin(Charge_Control_GPIO_Port, Charge_Control_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(Shot_Control_GPIO_Port, Shot_Control_Pin, GPIO_PIN_RESET);
        isShot = true;
        HAL_TIM_IC_Stop_IT(&htim2, TIM_CHANNEL_2);
    }
}

void Charge(uint16_t seconds) {
    HAL_GPIO_WritePin(Charge_Control_GPIO_Port, Charge_Control_Pin, GPIO_PIN_SET);
    HAL_Delay(seconds * 1000);
    HAL_GPIO_WritePin(Charge_Control_GPIO_Port, Charge_Control_Pin, GPIO_PIN_RESET);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == huart6.Instance) {
        // (为起始符，\"为结束符
        if (uartByte == '(') {
            receivingFlag = true;
        } else if (uartByte == '\"') {
            char x_str[15] = {0};
            char y_str[15] = {0};
            uint8_t i, j;
            for (i = 0; (i < len) && (uartBuf[i] != ','); i++) {
                x_str[i] = uartBuf[i];
            }
            for (i++, j = 0; i < len; i++, j++) {
                y_str[j] = uartBuf[i];
            }
            // 接收出错，重新接收
//            if (strlen(x_str) != 1) {
//                HAL_UART_Receive_IT(huart, (uint8_t *) &uartByte, 1);
//                return;
//            }
            if (x_str[0] == 'l') {
                pos_flag = LEFT;
            } else if (x_str[0] == 'r') {
                pos_flag = RIGHT;
            } else if (x_str[0] == 'n') {
                pos_flag = NFD;
            } else if (x_str[0] == 's') {
                pos_flag = STOP;
            } else if (x_str[0] == 'd') {
                pos_flag = DIS;
            }
            if (x_str[0] != 's') {
                pos_err = atoi(y_str);
            }
            receiveDone = true;
            receivingFlag = false;
            memset(uartBuf, 0, sizeof(uartBuf));
            len = 0;
            return;
        } else if (receivingFlag) {
            uartBuf[len] = uartByte;
            len++;
            if (len > 25) {
                len = 0;
                memset(uartBuf, 0, sizeof(uartBuf));
                receivingFlag = false;
            }
        }
    }
    HAL_UART_Receive_IT(huart, (uint8_t *) &uartByte, 1);
}






