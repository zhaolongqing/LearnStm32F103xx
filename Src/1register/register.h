//
// Created by ZlqPC on 2022/7/11.
//

#include "../root_select.h"

/**
 * 寄存器编程
 * 通过直接找芯片对应的寄存器地址来直接操作
 */
#if defined __REGISTER_H_USE__

#include "stm32f1xx_hal.h"

// RCC地址
#define AHB_RCC_BASE 0x40021000UL

// APB2ENR使能地址,后面的是偏移地址
#define RCC_APB2ENR AHB_RCC_BASE + 0x18UL

// APB2基地址
#define APB2 0x40010000UL

// CRL偏移地址
#define CRL 0x00UL

// CRH偏移地址
#define CRH 0x04UL

// BSRR偏移地址
#define BSRR 0x10UL

#define ODR 0x0CUL

// GPIOB低地址
#define APB2_GPIOB APB2 + 0x0C00UL

// GPIOG低地址
#define APB2_GPIOG APB2 + 0x2000UL

// GPIOB使能位
#define OFFSET_GPIOB 0x00000008UL

// GPIOG使能位
#define OFFSET_GPIOG 0x00000100UL

//所有使能位
#define OFFSET_GPIO OFFSET_GPIOB|OFFSET_GPIOG

void init(void);

void start(void);

void toggleGPIOB0(void);

void toggleGPIOG6(void);

void toggleGPIOG7(void);

void openGPIOB0(void);

void openGPIOG6(void);

void openGPIOG7(void);

void closeGPIOB0(void);

void closeGPIOG6(void);

void closeGPIOG7(void);

#endif