//
// Created by yekai on 2021/5/17.
//

#ifndef __MATKEYBOARD_H
#define __MATKEYBOARD_H

#include "main.h"

struct Key{
    uint8_t r;
    uint8_t l;
};

void SetRowHigh();

void SetRowLow();

void SetColHigh();

void SetColLow();

void Keyboard_Init();

uint8_t ScanCol();

uint8_t ScanRow();

void KeyScan(struct Key *key);

void TransposeMat(struct Key *key);

uint16_t ReadNum();

#endif //RAILGUN_MATKEYBOARD_H
