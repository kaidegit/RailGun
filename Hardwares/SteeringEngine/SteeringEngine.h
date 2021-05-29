//
// Created by yekai on 2021/5/18.
//

#pragma once

#include "main.h"

class Steering {
public:
    Steering(TIM_HandleTypeDef *htim, uint32_t Channel);

    void init(uint16_t startCompare, uint16_t endCompare, uint16_t initCompare);

    void SetSteeringCompare(uint32_t compare);

    uint32_t SteeringCompare;
private:
    TIM_HandleTypeDef *SteeringTim;
    uint32_t SteeringChannel;
    uint16_t maxCompare;
    uint16_t minCompare;
};

