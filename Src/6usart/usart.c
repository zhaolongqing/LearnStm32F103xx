//
// Created by ZlqPC on 2022/7/23.
//

#include "usart.h"

#if defined __HAL_USART1_USE__

void init() {

    // 注：启用时钟先启用总的APB2外设时钟再启用下面的时钟一步一步
    // 1.使能usart时钟
    __HAL_RCC_USART1_CLK_ENABLE();
    // 2.使能GPIO
    __HAL_RCC_GPIOA_CLK_ENABLE();
    // 3.初始化引脚PA9、PA10
    GPIO_InitTypeDef typeDef = {0};\
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

    // 4.设置USART的工作模式


    // 1.配置中断优先级组,系统默认是第四个，即四位最高可配置15
    HAL_NVIC_SetPriority(USART1_IRQn, 7, 0);
    // 2.使能中断
    HAL_NVIC_EnableIRQ(USART1_IRQn);


}

void start() {

}

#endif