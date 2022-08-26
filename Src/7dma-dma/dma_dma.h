//
// Created by ZlqPC on 2022/7/30.
//

#include "root_select.h"

#if defined __USART_DMA_DMA_USE__

#include "stdio.h"
#include "string.h"
#include "stm32f1xx_hal.h"

// 使能usart
#define USART_ENABLE __HAL_RCC_USART1_CLK_ENABLE();

// 串口
#define USART USART1

// 波特率
#define BAUD_RATE 9600

// 停止位
#define STOP_BITS UART_STOPBITS_1

// 校验位
#define PARITY UART_PARITY_NONE

// 字长
#define WORD_LENGTH UART_WORDLENGTH_8B

// 采样
#define OVER_SAMPLING UART_OVERSAMPLING_16

// 硬件控制流
#define HW_FLOW_CTL UART_HWCONTROL_NONE

// 模式，输入输出
#define MODE UART_MODE_TX_RX

void init(void);

void start(void);

#endif