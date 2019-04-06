/**
  ******************************************************************************
  * @file    key.c 
  * @brief   按键驱动，查询方式
  *
  ******************************************************************************  
  */
  
  
#include "key.h"


/* Exported functions ------------------------------------------------------- */
void KEY_Init(void)
{
    GPIO_Init(KEY1_PORT, KEY1_PIN, GPIO_Mode_In_FL_No_IT);  //PB1初始化
    GPIO_SetBits(KEY1_PORT, KEY1_PIN); //默认高电平
}
/**
  ****************************************************************************** 
  * @function   KEY_Scan
  * @para       u8 mode   
  * @retval     KEY1_PRESS->1   0
  * @brief      按键扫描函数，mode:1,连按，0，不支持
  ******************************************************************************
  */

u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1;    //按键松开标志
    if(mode)    key_up = 1;
    if (key_up && (!GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN)))
    {
        delay_ums(10);
        key_up = 0;  //按键按下标志
        if (!GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN))
            return KEY1_PRESS;
    }
    else if(GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN))
            key_up = 1;
    
    return 0;
}