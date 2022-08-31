//
// Created by ZlqPC on 2022/8/28.
//

#include "usart.h"

#if defined __USART_DMA_USART_USE__

#include "string.h"

UART_HandleTypeDef handleTypeDef;
uint8_t receiveData;

UART_HandleTypeDef getUart(){
    return handleTypeDef;
}

void initFirst();

void initUsart() {
    __HAL_RCC_USART1_CLK_ENABLE();
    handleTypeDef.Instance = USART1;
    handleTypeDef.Init.Mode = USART_MODE_TX_RX;
    handleTypeDef.Init.WordLength = USART_WORDLENGTH_8B;
    handleTypeDef.Init.StopBits = USART_STOPBITS_1;
    handleTypeDef.Init.Parity = USART_PARITY_NONE;
    handleTypeDef.Init.BaudRate = 9600;
    handleTypeDef.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    handleTypeDef.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&handleTypeDef);

    // 设置中断优先级为7,因为DMA传输也是有中断的且DMA会连续传输，所以UART中断优先级应该高于DMA
    HAL_NVIC_SetPriority(USART1_IRQn, 7, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

    initFirst();
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitTypeDef initTypeDef = {0};
        initTypeDef.Pin = GPIO_PIN_9;
        initTypeDef.Mode = GPIO_MODE_AF_PP;
        initTypeDef.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &initTypeDef);
        initTypeDef.Pin = GPIO_PIN_10;
        initTypeDef.Mode = GPIO_MODE_AF_INPUT;
        initTypeDef.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &initTypeDef);

        callInit(huart);

    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        __HAL_RCC_GPIOA_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9);
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10);
        HAL_NVIC_DisableIRQ(USART1_IRQn);
        callDeInit(huart);
    }
}


/**
 * 回调中断函数
 */
void USART1_IRQHandler() {
    HAL_UART_IRQHandler(&handleTypeDef);
}

/**
 * 处理中断函数
 * @param huart
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    HAL_UART_Transmit(huart, &receiveData, 1, 0);
    HAL_UART_Receive_IT(huart, &receiveData, 1);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
    printf("传输完成");
}

void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart){
    printf("已经传输一半");
}

/**
 * 处理错误中断函数
 * @param huart
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
    uint32_t code = huart->ErrorCode;
    printf("运行错误：%lu", code);
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

void initFirst() {
    uint8_t txBuf[100];

    // 把数据复制到数组中
    memcpy(txBuf, "这是一个串口中断接收回显实验\n", 100);

    // 把数据传输到指定的地址
    HAL_UART_Transmit(&handleTypeDef, txBuf, strlen((char *) txBuf), 1000);

    memcpy(txBuf, "输入数据并以回车键结束\n", 100);
    HAL_UART_Transmit(&handleTypeDef, txBuf, strlen((char *) txBuf), 1000);

    // 接收数据中断并进入回调函数
    HAL_UART_Receive_IT(&handleTypeDef, &receiveData, 1);
}

__weak void callInit(UART_HandleTypeDef *huart) {}

__weak void callDeInit(UART_HandleTypeDef *huart) {}

#endif