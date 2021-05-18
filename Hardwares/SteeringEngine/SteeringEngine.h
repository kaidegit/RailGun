//
// Created by yekai on 2021/5/18.
//

#pragma once

#include "main.h"

class Steering{
public:
    Steering(TIM_HandleTypeDef *htim, uint32_t Channel,uint32_t initCompare);
    void SetSteeringCompare(uint32_t compare);
private:
    TIM_HandleTypeDef *SteeringTim;
    uint32_t SteeringChannel;
    uint32_t SteeringCompare;
};

