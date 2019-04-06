/**
  ******************************************************************************
  * @file    key.c 
  * @brief   ������������ѯ��ʽ
  *
  ******************************************************************************  
  */
  
  
#include "key.h"


/* Exported functions ------------------------------------------------------- */
void KEY_Init(void)
{
    GPIO_Init(KEY1_PORT, KEY1_PIN, GPIO_Mode_In_FL_No_IT);  //PB1��ʼ��
    GPIO_SetBits(KEY1_PORT, KEY1_PIN); //Ĭ�ϸߵ�ƽ
}
/**
  ****************************************************************************** 
  * @function   KEY_Scan
  * @para       u8 mode   
  * @retval     KEY1_PRESS->1   0
  * @brief      ����ɨ�躯����mode:1,������0����֧��
  ******************************************************************************
  */

u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1;    //�����ɿ���־
    if(mode)    key_up = 1;
    if (key_up && (!GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN)))
    {
        delay_ums(10);
        key_up = 0;  //�������±�־
        if (!GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN))
            return KEY1_PRESS;
    }
    else if(GPIO_ReadInputDataBit(KEY1_PORT, KEY1_PIN))
            key_up = 1;
    
    return 0;
}