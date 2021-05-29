//
// Created by yekai on 2021/5/22.
//

#ifndef RAILGUN_SHOOT_H
#define RAILGUN_SHOOT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

enum Position {
    LEFT = 0, RIGHT, NFD, STOP
};

void Shoot(uint16_t dis, uint16_t angle);

void AutoShoot();

void RunningShoot();

void Charge(uint16_t seconds);

#ifdef __cplusplus
}
#endif

#endif //RAILGUN_SHOOT_H
