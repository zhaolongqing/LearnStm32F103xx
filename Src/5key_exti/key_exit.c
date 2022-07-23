//
// Created by ZlqPC on 2022/7/17.
//

#include "key_exit.h"

#if defined __HAL_KEY_EXIT_USE__

Device KEY1 = {.GPIO = GPIOA, .PIN=GPIO_PIN_0};// 按键KEY1

Device KEY2 = {.GPIO = GPIOC, .PIN=GPIO_PIN_13};// 按键KEY2

Device LED1 = {.GPIO = GPIOG, .PIN=GPIO_PIN_6};// 灯LED1

Device LED2 = {.GPIO = GPIOG, .PIN=GPIO_PIN_7};// 灯LED2

void init() {

    GPIO_InitTypeDef device = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    device.Speed = GPIO_SPEED_FREQ_LOW;
    device.Pin = LED1.PIN;
    device.Mode = GPIO_MODE_OUTPUT_PP;
    device.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(LED1.GPIO, &device);

    device.Speed = GPIO_SPEED_FREQ_LOW;
    device.Pin = LED2.PIN;
    device.Mode = GPIO_MODE_OUTPUT_PP;
    device.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(LED2.GPIO, &device);

    device.Pin = KEY1.PIN;
    device.Speed = GPIO_SPEED_FREQ_LOW;
    // 上升沿时触发中断
    device.Mode = GPIO_MODE_IT_RISING;
    device.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(KEY1.GPIO, &device);

    // 设置中断优先级
    HAL_NVIC_SetPriority(EXTI0_IRQn, 7, 0);
    // 使能中断
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

    device.Pin = KEY2.PIN;
    device.Speed = GPIO_SPEED_FREQ_LOW;
// 下降沿时触发中断
    device.Mode = GPIO_MODE_IT_FALLING;
    device.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY2.GPIO, &device);

    // 设置中断优先级
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 7, 0);
    // 使能中断
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/**
 * 此函数是由汇编调用的函数,在startup_stm32f103xe.s有
 */
void EXTI0_IRQHandler(void) {

    // 触发key1引脚中断
    HAL_GPIO_EXTI_IRQHandler(KEY1.PIN);
}

/**
 * 此函数是由汇编调用的函数,在startup_stm32f103xe.s有
 */
void EXTI15_10_IRQHandler() {

    // 触发key2引脚
    HAL_GPIO_EXTI_IRQHandler(KEY2.PIN);
}

// 覆写HAL_GPIO_EXTI_Callback,回调函数。
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == KEY1.PIN) {
        HAL_Delay(20);
        if (KEY_STATE(KEY1) == GPIO_PIN_SET) {
            LED_TOGGLE(LED1);
        }
    } else if (GPIO_Pin == KEY2.PIN) {
        HAL_Delay(20);
        if (KEY_STATE(KEY2) == GPIO_PIN_RESET) {
            LED_TOGGLE(LED2);
        }
    }
}

void start() {
}


#endif