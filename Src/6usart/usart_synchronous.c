//
// Created by ZlqPC on 2022/7/23.
//

#include "usart_synchronous.h"

#if defined __HAL_USART1_USE__

#include "string.h"

UART_HandleTypeDef uartHandleTypeDef = {0};

uint8_t data;

void deviceHandle() {
    uint8_t txBuf[100];

    // 把数据复制到数组中
    memcpy(txBuf, "这是一个串口中断接收回显实验\n", 100);

    // 把数据传输到指定的地址
    HAL_UART_Transmit(&uartHandleTypeDef, txBuf, strlen((char *) txBuf), 1000);

    memcpy(txBuf, "输入数据并以回车键结束\n", 100);
    HAL_UART_Transmit(&uartHandleTypeDef, txBuf, strlen((char *) txBuf), 1000);

    // 接收数据中断并进入回调函数
    HAL_UART_Receive_IT(&uartHandleTypeDef, &data, 1);
}

void init() {

    // 注：启用时钟先启用总的APB2外设时钟再启用下面的时钟一步一步
    // 1.使能usart时钟
    __HAL_RCC_USART1_CLK_ENABLE();

    // 2.设置USART的工作模式
    uartHandleTypeDef.Instance = USART1;
    uartHandleTypeDef.Init.BaudRate = 9600;
    uartHandleTypeDef.Init.Parity = USART_PARITY_NONE;
    uartHandleTypeDef.Init.StopBits = USART_STOPBITS_1;
    uartHandleTypeDef.Init.WordLength = USART_WORDLENGTH_8B;
    uartHandleTypeDef.Init.Mode = USART_MODE_TX_RX;
    uartHandleTypeDef.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uartHandleTypeDef.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&uartHandleTypeDef);

    // 3.配置中断优先级组,系统默认是第四个，即四位最高可配置15
    HAL_NVIC_SetPriority(USART1_IRQn, 7, 0);
    // 4.使能中断
    HAL_NVIC_EnableIRQ(USART1_IRQn);

    deviceHandle();
}

/**
 * 覆写UART并初始化
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        // 1.使能GPIO
        __HAL_RCC_GPIOA_CLK_ENABLE();
        // 1.初始化引脚PA9、PA10
        GPIO_InitTypeDef typeDef = {0};
        typeDef.Pin = GPIO_PIN_9;
        // 由于是串口所以速度应该是最高的
        typeDef.Speed = GPIO_SPEED_FREQ_HIGH;
        // PA9是复用推挽输出（专门用于特殊的IO口）见原理图，由输出接输入
        typeDef.Mode = GPIO_MODE_AF_PP;
        // 初始化PA9
        HAL_GPIO_Init(GPIOA, &typeDef);
        typeDef.Pin = GPIO_PIN_10;
        // PA10是复用输入模式
        typeDef.Mode = GPIO_MODE_AF_INPUT;
        // 初始化PA10
        HAL_GPIO_Init(GPIOA, &typeDef);
    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        __HAL_RCC_USART1_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9);
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10);
        HAL_NVIC_DisableIRQ(USART1_IRQn);
    }
}

void start() {}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    HAL_UART_Transmit(huart, &data, 1, 0);
    HAL_UART_Receive_IT(huart, &data, 1);
}

#endif