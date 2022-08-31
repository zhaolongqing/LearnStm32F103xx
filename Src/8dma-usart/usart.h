//
// Created by ZlqPC on 2022/8/28.
//

#include "root_select.h"

#if defined __USART_DMA_USART_USE__

#include "stm32f1xx_hal.h"
#include "stdio.h"

void initUsart();

void callInit(UART_HandleTypeDef *huart);

void callDeInit(UART_HandleTypeDef *huart);

UART_HandleTypeDef getUart();

#endif
