//
// Created by yekai on 2021/5/18.
//

#include <MatKeyboard.h>
#include <cstring>
#include <cstdio>
#include "main_cpp.h"
#include "usart.h"
#include "main.h"

void main_cpp() {
    char ch[30];
    Key key;
    key.Keyboard_Init();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (true) {
        key.ReadNum();
        sprintf(ch, "cpp:%d\r\n", key.num);
        HAL_UART_Transmit(&huart1, (uint8_t *) ch, strlen(ch), 0xff);
    }
#pragma clang diagnostic pop

}
