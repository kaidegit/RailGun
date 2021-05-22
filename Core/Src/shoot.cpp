//
// Created by yekai on 2021/5/22.
//

#include <cstdlib>
#include "shoot.h"
#include "usart.h"
#include "cstring"

char uartByte;
bool receivingFlag;
bool receiveDone;
char uartBuf[30];
uint8_t len;
uint16_t dis_rec, angle_rec;

void Shoot(uint16_t dis, uint16_t angle) {
    HAL_UART_Transmit(&huart1, (uint8_t *) "shoot\r\n", strlen("shoot\r\n"), 0xff);
}

void AutoShoot() {
    receiveDone = false;
    HAL_UART_Receive_IT(&huart1, (uint8_t *) &uartByte, 1);
    while (!receiveDone) {}
    Shoot(dis_rec, angle_rec);
    HAL_UART_Transmit(&huart1, (uint8_t *) "auto shoot\r\n", strlen("auto shoot\r\n"), 0xff);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == huart1.Instance) {
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
            dis_rec = atoi(x_str);
            angle_rec = atoi(y_str);
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
    HAL_UART_Receive_IT(huart, (uint8_t *)&uartByte, 1);
}


