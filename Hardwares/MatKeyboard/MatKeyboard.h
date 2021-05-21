//
// Created by yekai on 2021/5/17.
//

#ifndef __MATKEYBOARD_H
#define __MATKEYBOARD_H

#include "main.h"


class Key {
public:
    Key() ;

    void Keyboard_Init();

    void KeyScan();

    void SetRowHigh();

    void SetRowLow();

    void SetColHigh();

    void SetColLow();

    uint8_t ScanCol();

    uint8_t ScanRow();

    void TransposeMat();

    void ReadNum();

    uint8_t r;
    uint8_t l;
    uint16_t num;
    uint8_t dis;
};


#endif //RAILGUN_MATKEYBOARD_H
