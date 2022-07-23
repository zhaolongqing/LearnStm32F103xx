//
// Created by ZlqPC on 2020/7/3.
//

#include "../root_select.h"

#if defined __LED_H_USE__

#ifndef LEARN_LED_H
#define LEARN_LED_H

#include "stm32f1xx_hal.h"

#define LED1 GPIO_PIN_0
#define LED2 GPIO_PIN_6
#define LED3 GPIO_PIN_7

#define LED1_TOGGLE HAL_GPIO_TogglePin(GPIOB, LED1)
#define LED1_ON HAL_GPIO_WritePin(GPIOB, LED1, GPIO_PIN_SET)
#define LED1_OFF HAL_GPIO_WritePin(GPIOB, LED1, GPIO_PIN_RESET)

#define LED2_TOGGLE HAL_GPIO_TogglePin(GPIOG, LED2)
#define LED2_ON HAL_GPIO_WritePin(GPIOG, LED2, GPIO_PIN_SET)
#define LED2_OFF HAL_GPIO_WritePin(GPIOG, LED2, GPIO_PIN_RESET)

#define LED3_TOGGLE HAL_GPIO_TogglePin(GPIOG, LED3)
#define LED3_ON HAL_GPIO_WritePin(GPIOG, LED3, GPIO_PIN_SET)
#define LED3_OFF HAL_GPIO_WritePin(GPIOG, LED3, GPIO_PIN_RESET)

void LED_GPIO_Init(void);

void led_start();

#endif

#endif //LEARN_LED_H
