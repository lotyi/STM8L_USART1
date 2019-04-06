#ifndef __LED_H__

#define __LED_H__

#include "stm8l15x.h"
#include "stm8l15x_gpio.h"

#define LED1_PORT GPIOD
#define LED2_PORT GPIOC
#define LED3_PORT GPIOB

#define LED1_PIN GPIO_Pin_0
#define LED2_PIN GPIO_Pin_4
#define LED3_PIN GPIO_Pin_2

#define ON  1
#define OFF 0

void LED_Init(void);
void LED1(u8 state);
void LED2(u8 state);
void LED3(u8 state);

#endif