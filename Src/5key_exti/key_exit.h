//
// Created by ZlqPC on 2022/7/17.
//

/**
 * 硬件中断
 */

#include "../root_select.h"

#if defined __HAL_KEY_EXIT_USE__

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
