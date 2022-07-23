//
// Created by ZlqPC on 2022/7/15.
//

#include "register.h"

#ifdef __REGISTER_H_USE__

#include "stdint.h"


void init() {
//    uint32_t *reg = (uint32_t *) RCC_APB2ENR;
//    (*(uint32_t *) RCC_APB2ENR)
//    *reg = *reg | OFFSET_GPIO;

    // RCC时钟 GPIOG/GPIOB使能
    volatile uint32_t reg;
    reg = *(uint32_t *) (RCC_APB2ENR);
    reg = reg | OFFSET_GPIO;
    *(uint32_t *) (RCC_APB2ENR) = reg;

    // 设置所有端口GPIOx_CRL(端口配置低寄存器)为输出模式，推挽输出
    // 重置数据位
    *(uint32_t *) (APB2_GPIOB + CRL) &= 0B0000;
    // GPIOB0
    *(uint32_t *) (APB2_GPIOB + CRL) |= 0B0001;

    // 重置数据位
    *(uint32_t *) (APB2_GPIOG + CRL) &= 0x00000000;
    // GPIOG6和GPIOG7设置为输出模式
    *(uint32_t *) (APB2_GPIOG + CRL) |= 0x11000000;

    // 初始化状态
    closeGPIOB0();
    closeGPIOG6();
    closeGPIOG7();
}


void start() {
    toggleGPIOB0();
    HAL_Delay(2000);
    toggleGPIOG6();
    HAL_Delay(2000);
    toggleGPIOG7();
    HAL_Delay(2000);
}

void toggleGPIOB0() {
    if ((*(uint16_t *) (APB2_GPIOB + ODR) & 0x0001UL) != 0x0001UL) {
        // GPIOB0打开其它全关
        openGPIOB0();
        closeGPIOG6();
        closeGPIOG7();
    }
}
void toggleGPIOG6() {
    if ((*(uint16_t *) (APB2_GPIOG + ODR) & 0x0040UL) != 0x0040UL) {
        // GPIOB0打开其它全关
        openGPIOG6();
        closeGPIOB0();
        closeGPIOG7();
    }
}
void toggleGPIOG7() {
    if ((*(uint16_t *) (APB2_GPIOG + ODR) & 0x0080UL) != 0x0080UL) {
        // GPIOB0打开其它全关
        openGPIOG7();
        closeGPIOB0();
        closeGPIOG6();
    }
}


void openGPIOB0() {
    // 初始化灯为都打开GPIOx_BSRR(端口位设置寄存器)
    // 设置对应的GPIOB0端口位BS为1
    *(uint32_t *) (APB2_GPIOB + BSRR) |= 0x0001UL;
}

void openGPIOG6() {
    // 以下的可以合一起
    // 设置对应的GPIOG6端口位BS为1
    *(uint32_t *) (APB2_GPIOG + BSRR) |= 0x0040UL;
}

void openGPIOG7() {
    // 以下的可以合一起
    // 设置对应的GPIOG7端口位BS为1
    *(uint32_t *) (APB2_GPIOG + BSRR) |= 0x0080UL;
}

void closeGPIOB0() {
    *(uint32_t *) (APB2_GPIOB + BSRR) |= 0x0001UL << 16;
}

void closeGPIOG6() {
    *(uint32_t *) (APB2_GPIOG + BSRR) |= 0x0040UL << 16;
}

void closeGPIOG7() {
    *(uint32_t *) (APB2_GPIOG + BSRR) |= 0x0080UL << 16;
}

#endif