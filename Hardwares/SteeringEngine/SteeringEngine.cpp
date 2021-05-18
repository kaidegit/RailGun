//
// Created by yekai on 2021/5/18.
//

#include "SteeringEngine.h"


Steering::Steering(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t initCompare)
        : SteeringTim(htim), SteeringChannel(Channel), SteeringCompare(initCompare) {
    __HAL_TIM_SET_COMPARE(SteeringTim, SteeringChannel, 1);
    HAL_TIM_PWM_Start(SteeringTim, SteeringChannel);
    for (auto i = 1; i < 2500; i += 5) {
        __HAL_TIM_SET_COMPARE(SteeringTim, SteeringChannel, i);
        HAL_Delay(15);
    }
    for (auto i = 2500; i > initCompare; i -= 5) {
        __HAL_TIM_SET_COMPARE(SteeringTim, SteeringChannel, i);
        HAL_Delay(15);
    }
    __HAL_TIM_SET_COMPARE(SteeringTim, SteeringChannel, initCompare);
}

void Steering::SetSteeringCompare(uint32_t compare) {
    if (compare - SteeringCompare > 0) {
        for (auto i = SteeringCompare; i < compare; i += 5) {
            __HAL_TIM_SET_COMPARE(SteeringTim, SteeringChannel, i);
            HAL_Delay(15);
        }
    } else {
        for (auto i = SteeringCompare; i > compare; i -= 5) {
            __HAL_TIM_SET_COMPARE(SteeringTim, SteeringChannel, i);
            HAL_Delay(15);
        }
    }
    __HAL_TIM_SET_COMPARE(SteeringTim, SteeringChannel, compare);
    SteeringCompare = compare;
}
