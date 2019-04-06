#include "led.h"


void LED_Init(void)
{
    GPIO_Init(LED1_PORT, LED1_PIN, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(LED2_PORT, LED2_PIN, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(LED3_PORT, LED3_PIN, GPIO_Mode_Out_PP_High_Fast);
}
/**
  ************************************************************
  * @brief  ¿ØÖÆLED¿ª¹Ø
  * @para   u8   ON/OFF
  *************************************************************
  */
void LED1(u8 state)
{
    if(state)
    {
        GPIO_ResetBits(LED1_PORT,LED1_PIN);
    }
    if(!state)
    {
        GPIO_SetBits(LED1_PORT,LED1_PIN);
    }
}

void LED2(u8 state)
{
    if(state)
    {
        GPIO_ResetBits(LED2_PORT,LED2_PIN);
    }
    if(!state)
    {
        GPIO_SetBits(LED2_PORT,LED2_PIN);
    }
}

void LED3(u8 state)
{
    if(state)
    {
        GPIO_ResetBits(LED3_PORT,LED3_PIN);
    }
    if(!state)
    {
        GPIO_SetBits(LED3_PORT,LED3_PIN);
    }
}