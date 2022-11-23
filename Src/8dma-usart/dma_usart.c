//
// Created by ZlqPC on 2022/8/28.
//

#include "dma_usart.h"

#if defined __USART_DMA_USART_USE__

#include "usart.h"

DMA_HandleTypeDef learnDma;

#define SEND_BUFF_SIZE              100  // 串口DMA发送缓冲区大小
uint8_t aTxBuffer[SEND_BUFF_SIZE];       // 串口DMA发送缓冲区

void init() {
    initUsart();
    UART_HandleTypeDef handleTypeDef = getUart();
    for (int i = 0; i < SEND_BUFF_SIZE; i++) {
        aTxBuffer[i] = 0x99;
    }
    HAL_StatusTypeDef statusTypeDef = HAL_UART_Transmit_DMA(&handleTypeDef, aTxBuffer, SEND_BUFF_SIZE);
    switch (statusTypeDef) {
        case HAL_OK:
            printf("HAL_OK\n");
            break;
        case HAL_ERROR:
            printf("HAL_ERROR\n");
            break;
        case HAL_BUSY:
            printf("HAL_BUSY\n");
            break;
        case HAL_TIMEOUT:
            printf("HAL_TIMEOUT\n");
            break;
        default:
            break;
    }
}

void start() {
}


void CallBack( DMA_HandleTypeDef * _hdma){
}

void callInit(UART_HandleTypeDef *huart) {
    __HAL_RCC_DMA1_CLK_ENABLE();
    learnDma.Instance = DMA1_Channel4;
    learnDma.Init.Mode = DMA_CIRCULAR;
    learnDma.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    learnDma.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    learnDma.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    learnDma.Init.MemInc = DMA_MINC_ENABLE;
    learnDma.Init.PeriphInc = DMA_PINC_DISABLE;
    learnDma.Init.Direction = DMA_MEMORY_TO_PERIPH;
    HAL_DMA_Init(&learnDma);
    __HAL_LINKDMA(huart, hdmatx, learnDma);
    HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 8, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
    HAL_DMA_RegisterCallback(&learnDma, HAL_DMA_XFER_ERROR_CB_ID, CallBack);
}


void DMA1_Channel4_IRQHandler(){
    HAL_DMA_IRQHandler(&learnDma);
}

void callDeInit(UART_HandleTypeDef *huart) {
    __HAL_RCC_DMA1_CLK_DISABLE();
    HAL_DMA_DeInit(huart->hdmatx);
    HAL_NVIC_DisableIRQ(USART1_IRQn);
    HAL_NVIC_DisableIRQ(DMA1_Channel1_IRQn);
}
#endif
