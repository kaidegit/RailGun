//
// Created by yekai on 2021/5/18.
//

#include "SteeringEngine.h"


Steering::Steering(TIM_HandleTypeDef *htim, uint32_t Channel)
        : SteeringTim(htim), SteeringChannel(Channel) {
}

void Steering::SetSteeringCompare(uint32_t compare) {
    if ((compare > maxCompare) || (compare < minCompare)) {
        return;
    }
    if (compare > SteeringCompare) {
        for (auto i = SteeringCompare; i < compare; i += 3) {
            __HAL_TIM_SET_COMPARE(SteeringTim, SteeringChannel, i);
            HAL_Delay(30);
        }
    } else {
        for (auto i = SteeringCompare; i > compare; i -= 3) {
            __HAL_TIM_SET_COMPARE(SteeringTim, SteeringChannel, i);
            HAL_Delay(30);
        }
    }
    __HAL_TIM_SET_COMPARE(SteeringTim, SteeringChannel, compare);
    SteeringCompare = compare;
}

void Steering::init(uint16_t startCompare, uint16_t endCompare, uint16_t initCompare) {
    minCompare = startCompare;
    maxCompare = endCompare;
    __HAL_TIM_SET_COMPARE(SteeringTim, SteeringChannel, 1);
    HAL_TIM_PWM_Start(SteeringTim, SteeringChannel);
    for (auto i = startCompare; i < endCompare; i += 5) {
        __HAL_TIM_SET_COMPARE(SteeringTim, SteeringChannel, i);
        HAL_Delay(15);
    }
    for (auto i = endCompare; i > initCompare; i -= 5) {
        __HAL_TIM_SET_COMPARE(SteeringTim, SteeringChannel, i);
        HAL_Delay(15);
    }
    __HAL_TIM_SET_COMPARE(SteeringTim, SteeringChannel, initCompare);
    SteeringCompare = initCompare;
}
