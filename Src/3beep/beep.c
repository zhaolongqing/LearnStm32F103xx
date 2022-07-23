//
// Created by ZlqPC on 2022/7/17.
//

#include "beep.h"

#if defined __BEEP_H_USE__

#define BEEP_TOGGLE HAL_GPIO_TogglePin(GPIOD, BEEP)
#define BEEP_ON HAL_GPIO_WritePin(GPIOD, BEEP, GPIO_PIN_SET)
#define BEEP_OFF HAL_GPIO_WritePin(GPIOD, BEEP, GPIO_PIN_RESET)

void BEEP_GPIO_Init() {
    GPIO_InitTypeDef beep;
    beep.Mode = GPIO_MODE_OUTPUT_PP;
    beep.Pin = GPIO_PIN_7;
    beep.Speed = GPIO_SPEED_FREQ_LOW;
    beep.Pull = GPIO_PULLDOWN;

    // 初始化时钟
    __HAL_RCC_GPIOD_CLK_ENABLE();

    // 初始化引脚
    HAL_GPIO_Init(GPIOD, &beep);

    HAL_GPIO_WritePin(GPIOD, BEEP, GPIO_PIN_RESET);
}

void beep_start() {
    HAL_GPIO_TogglePin(GPIOD, BEEP);
    int delayTime = 5000;
    if (HAL_GPIO_ReadPin(GPIOD, BEEP)) {
        delayTime = 200;
    }
    HAL_Delay(delayTime);
}

#endif
