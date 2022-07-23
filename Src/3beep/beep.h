//
// Created by ZlqPC on 2022/7/17.
//

#include "../root_select.h"

#if defined __BEEP_H_USE__

#ifndef LEARN_BEEP_H
#define LEARN_BEEP_H

#include "stm32f1xx_hal.h"

#define BEEP GPIO_PIN_7

void BEEP_GPIO_Init(void);

void beep_start();

#endif //LEARN_BEEP_H

#endif