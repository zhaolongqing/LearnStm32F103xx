//
// Created by ZlqPC on 2022/7/17.
//

/**
 * 按键有抖动的情况，并且需要进行软件消抖
 * 工程介绍：按键扫描
 * 当key1按下之后，led1根据当前灯的状态亮起或关闭
 * 当key2按下之后，led2根据当前灯的状态亮起或关闭
 */

#include "../root_select.h"

#if defined __KEY_SHAKE_H_USE__

#include "stm32f1xx_hal.h"

typedef struct {
    GPIO_TypeDef *GPIO;
    uint16_t PIN;
} Device;

// 控制led
#define LED_TOGGLE(led) (HAL_GPIO_TogglePin((led).GPIO,(led).PIN))
// 读取状态
#define KEY_STATE(led) (HAL_GPIO_ReadPin((led).GPIO,(led).PIN))

void init();

void start();

#endif
