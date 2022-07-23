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
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    GPIO_InitTypeDef led1 = {
            .Speed = GPIO_SPEED_FREQ_LOW,
            .Pin = LED1.PIN,
            .Mode = GPIO_MODE_OUTPUT_PP,
            .Pull = GPIO_NOPULL
    };
    HAL_GPIO_Init(LED1.GPIO, &led1);
    GPIO_InitTypeDef led2 = {
            .Speed = GPIO_SPEED_FREQ_LOW,
            .Pin = LED2.PIN,
            .Mode = GPIO_MODE_OUTPUT_PP,
            .Pull = GPIO_NOPULL
    };
    HAL_GPIO_Init(LED2.GPIO, &led2);
    GPIO_InitTypeDef key1 = {
            .Pin = KEY1.PIN,

            // 下降沿时触发中断
            .Mode = GPIO_MODE_IT_FALLING,
            .Pull = GPIO_PULLUP
    };
    HAL_GPIO_Init(KEY1.GPIO, &key1);

    // 设置中断优先级
    HAL_NVIC_SetPriority(EXTI0_IRQn, 7, 0);
    // 使能中断
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

    GPIO_InitTypeDef key2 = {
            .Pin = KEY1.PIN,

            // 上升沿时触发中断
            .Mode = GPIO_MODE_IT_RISING,
            .Pull = GPIO_PULLDOWN
    };
    HAL_GPIO_Init(KEY2.GPIO, &key2);

    // 设置中断优先级
//    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 7, 0);
    // 使能中断
//    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/**
 * 此函数是由汇编调用的函数,在startup_stm32f103xe.s有
 */
/*void EXTI0_IRQHandler(void) {

    // 触发key1引脚中断
    HAL_GPIO_EXTI_IRQHandler(KEY1.PIN);
}*/

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
        // 消除中断
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
    } else if (GPIO_Pin == KEY2.PIN) {
        if (KEY_STATE(KEY2) == GPIO_PIN_SET) {
            LED_TOGGLE(KEY2);
        }
        // 消除中断
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
    }
}

void start() {
}


#endif