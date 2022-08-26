//
// Created by ZlqPC on 2022/7/30.
//

#include "dma_dma.h"

#if defined __USART_DMA_DMA_USE__

UART_HandleTypeDef handleTypeDef;

void init() {
    USART_ENABLE
    handleTypeDef.Instance = USART;
    handleTypeDef.Init.BaudRate = BAUD_RATE;
    handleTypeDef.Init.HwFlowCtl = HW_FLOW_CTL;
    handleTypeDef.Init.Mode = MODE;
    handleTypeDef.Init.OverSampling = OVER_SAMPLING;
    handleTypeDef.Init.Parity = PARITY;
    handleTypeDef.Init.StopBits = STOP_BITS;
    handleTypeDef.Init.WordLength = WORD_LENGTH;
}

void start() {

}

#endif