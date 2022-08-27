//
// Created by ZlqPC on 2022/7/30.
//

#include "dma_dma.h"

#if defined __USART_DMA_DMA_USE__

typedef enum {
    FAILED = 0,
    PASSED = 1
} TestStatus;

// 内存到内存
DMA_HandleTypeDef hdma_memtomem_dma1_channel1;
static const uint32_t SRC_Const_Buffer[32] = {
        0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10,
        0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
        0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
        0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
        0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
        0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
        0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
        0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80};
uint32_t DST_Buffer[32];

/**
 * 检查数据是否相等
 * @param pBuffer
 * @param pBuffer1
 * @param bufferLength
 * @return
 */
TestStatus bufferCmp(const uint32_t *pBuffer, uint32_t *pBuffer1, uint16_t bufferLength) {
    while (bufferLength--) {
        if (*pBuffer != *pBuffer1) {
            return FAILED;
        }
        pBuffer++;
        pBuffer1++;
    }
    return PASSED;
}

void initDMA() {
    // 使能DMA1
    __HAL_RCC_DMA1_CLK_ENABLE();
    // 配置DMA1
    hdma_memtomem_dma1_channel1.Instance = DMA1_Channel1;
    hdma_memtomem_dma1_channel1.Init.Direction = DMA_MEMORY_TO_MEMORY;
    hdma_memtomem_dma1_channel1.Init.PeriphInc = DMA_PINC_ENABLE;
    hdma_memtomem_dma1_channel1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_memtomem_dma1_channel1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_memtomem_dma1_channel1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_memtomem_dma1_channel1.Init.Mode = DMA_NORMAL;
    hdma_memtomem_dma1_channel1.Init.Priority = DMA_PRIORITY_HIGH;
    HAL_DMA_Init(&hdma_memtomem_dma1_channel1);
}

void init() {
    initPrint();
    initDMA();
    printf("开始传输\n");
    HAL_StatusTypeDef harStatus = HAL_DMA_Start(
            &hdma_memtomem_dma1_channel1,
            (uint32_t) &SRC_Const_Buffer,
            (uint32_t) &DST_Buffer,
            32
    );
    __IO TestStatus TransferStatus = FAILED;
    if (harStatus == HAL_OK) {
        TransferStatus = bufferCmp(SRC_Const_Buffer, DST_Buffer, 32);
        if (TransferStatus == PASSED) {
            printf("数据传输成功\n");
        } else {
            printf("数据传输失败\n");
        }
    }
}

void start() {

}

#endif