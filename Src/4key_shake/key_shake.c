//
// Created by ZlqPC on 2022/7/17.
//

#include "../root_select.h"

#if defined __KEY_SHAKE_H_USE__

#include "key_shake.h"


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
            .Speed = GPIO_SPEED_FREQ_LOW,
            .Pin = KEY1.PIN,
            .Mode = GPIO_MODE_INPUT,
            .Pull = GPIO_PULLDOWN
    };
    HAL_GPIO_Init(KEY1.GPIO, &key1);
    GPIO_InitTypeDef key2 = {
            .Speed = GPIO_SPEED_FREQ_LOW,
            .Pin = KEY2.PIN,
            .Mode = GPIO_MODE_INPUT,
            .Pull = GPIO_PULLUP
    };
    HAL_GPIO_Init(KEY2.GPIO, &key2);


}

int isDown1 = 0;
int isDown2 = 0;

void start() {

    // 通过软件实现消抖
    // 读取此时按键值并判断是否是被按下状态，如果是被按下状态进入函数内
    if (KEY_STATE(KEY1) == GPIO_PIN_SET && !isDown1) {
        // 延时一小段时间，消除抖动
        HAL_Delay(10);
        while (KEY_STATE(KEY1) == GPIO_PIN_SET && !isDown1) {
            LED_TOGGLE(LED1);
            isDown1 = 1;
        }
    } else if (KEY_STATE(KEY1) == GPIO_PIN_RESET && isDown1) {
        // 延时一小段时间，消除抖动
        HAL_Delay(10);
        while (KEY_STATE(KEY1) == GPIO_PIN_RESET && isDown1) {
            isDown1 = 0;
        }
    }

    // 通过硬件实现消抖
    // 读取此时按键值并判断是否是被按下状态，如果是被按下状态进入函数内
    if (KEY_STATE(KEY2) == GPIO_PIN_RESET && !isDown2) {
        while (KEY_STATE(KEY2) == GPIO_PIN_RESET && !isDown2) {
            LED_TOGGLE(LED2);
            isDown2 = 1;
        }
    } else if (KEY_STATE(KEY2) == GPIO_PIN_SET && isDown2) {
        while (KEY_STATE(KEY2) == GPIO_PIN_SET && isDown2) {
            isDown2 = 0;
        }
    }
}


#endif


