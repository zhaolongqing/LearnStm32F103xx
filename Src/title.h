//
// Created by ZlqPC on 2020/7/3.
//

#ifndef LEARN_TITLE_H
#define LEARN_TITLE_H

/**
 * 定义指定选项进行
 * 某项选择
 * 练习方法目前包括：
 * INIT
 * START
 */

#include "root_select.h"

#ifdef __REGISTER_H_USE__   /* 寄存器编程 */
#include "1register/register.h"
#define INIT init();
#define START start();

#elif defined __LED_H_USE__   /* 流水灯 */
#include "2led/led.h"
#define INIT LED_GPIO_Init();
#define START led_start();

#elif defined __BEEP_H_USE__ /*蜂鸣器*/
#include "3beep/beep.h"
#define INIT BEEP_GPIO_Init();
#define START beep_start();

#elif defined __KEY_SHAKE_H_USE__ /*根据按键点亮灯*/
#include "4key_shake/key_shake.h"
#define INIT init();
#define START start();

#elif defined __HAL_KEY_EXIT_USE__ /*中断按键点亮灯*/
#include "5key_exti/key_exit.h"
#define INIT init();
#define START start();

#endif

#endif //LEARN_TITLE_H
