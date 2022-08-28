//
// Created by ZlqPC on 2022/7/24.
//

#include "usart_print.h"

#if defined __USART_PRINT_USE__

UART_HandleTypeDef handleTypeDef;
GPIO_InitTypeDef gpioInitTypeDef;

// 初始化串口
void init() {
    __HAL_RCC_USART1_CLK_ENABLE();
    handleTypeDef.Instance = USART1;
    handleTypeDef.Init.BaudRate = 9600;
    handleTypeDef.Init.StopBits = UART_STOPBITS_1;
    handleTypeDef.Init.Parity = UART_PARITY_NONE;
    handleTypeDef.Init.WordLength = UART_WORDLENGTH_8B;
    handleTypeDef.Init.OverSampling = UART_OVERSAMPLING_16;
    handleTypeDef.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    handleTypeDef.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&handleTypeDef);

    char string[] = "开始输出:";
    printf("%s\n", string);
}

// 初始化引脚
void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        gpioInitTypeDef.Pin = GPIO_PIN_9;
        gpioInitTypeDef.Mode = GPIO_MODE_AF_PP;
        gpioInitTypeDef.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &gpioInitTypeDef);
        gpioInitTypeDef.Pin = GPIO_PIN_10;
        gpioInitTypeDef.Mode = GPIO_MODE_AF_INPUT;
        gpioInitTypeDef.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &gpioInitTypeDef);
    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        __HAL_RCC_GPIOA_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9);
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10);
    }
}

int __io_putchar(int ch) {
    HAL_UART_Transmit(&handleTypeDef, (uint8_t *) &ch, 1, 0xffff);
    return ch;
}

int __io_getchar(void) {
    char ch;
    HAL_UART_Receive(&handleTypeDef, (uint8_t *) &ch, 1, 0xffff);
    return ch;
}

int _read(int file, char *ptr, int len){
    *ptr++ = __io_getchar();
    return 1;
}

void start() {
    char ch = getchar();
    printf("%s", &ch);
}


#endif