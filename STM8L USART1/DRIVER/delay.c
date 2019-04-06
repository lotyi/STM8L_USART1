/**
  ******************************************************************************
  * @file    delay.c
  * @author  Microcontroller Division
  * @version V1.2.0
  * @date    09/2010
  * @brief   delay functions
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/

#include "delay.h"
/**
  * @brief  delay for some time in ms unit
  * @caller auto_test
  * @param  n_ms is how many ms of time to delay
  * @retval None
  */
void delay_ms(u16 n_ms)
{
/* Init TIMER 4 */
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
 /* HSI div by 1 --> Auto-Reload value: 16M / 64 = 1/4M, 1/4M / 1k = 250*/ 
 /* 定时器溢出时间为：1ms */
  TIM4_TimeBaseInit(TIM4_Prescaler_64,(250-1));
  TIM4_ClearFlag(TIM4_FLAG_Update);
  TIM4_Cmd(ENABLE);
  while(n_ms--)
  {
    while(TIM4_GetFlagStatus(TIM4_FLAG_Update) == 0) ;
    TIM4_ClearFlag(TIM4_FLAG_Update);
  }
  TIM4_Cmd(DISABLE);
}

/**
  *****************************************************************************
  * @brief  delay for some time in 10us unit(partial accurate)
  * @caller auto_test
  * @param n_10us is how many 10us of time to delay
  * @retval None
  *****************************************************************************
  */
void delay_10us(u16 n_10us)
{
/* Init TIMER 4 */
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
/* SYS_CLK_HSI_DIV1 Auto-Reload value: 16M / 1 = 16M, 16M / 100k = 160 */
  /* 定时器频率为16M，一次延时10us */
  TIM4_TimeBaseInit(TIM4_Prescaler_1,(160-1));
  TIM4_ClearFlag(TIM4_FLAG_Update);
  TIM4_Cmd(ENABLE);
  while(n_10us--)
  {
    while(TIM4_GetFlagStatus(TIM4_FLAG_Update) == 0) ;
    TIM4_ClearFlag(TIM4_FLAG_Update);
  }
  TIM4_Cmd(DISABLE);
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, DISABLE);

}

/**
  *****************************************************************************
  * @brief  delay for some time in us unit(partial accurate)
  * @caller auto_test
  * @param n_us is how many 10us of time to delay
  * @retval None
  *****************************************************************************
  */
void delay_us(u16 n_us)
{
/* Init TIMER 4 */
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
/* SYS_CLK_HSI_DIV1 Auto-Reload value: 16M / 1 = 16M, 16M / 1000k = 16 */
  /* 定时器频率为16M，一次延时10us */
  TIM4_TimeBaseInit(TIM4_Prescaler_1,(16-1));
  TIM4_ClearFlag(TIM4_FLAG_Update);
  TIM4_Cmd(ENABLE);
  while(n_us--)
  {
    while(TIM4_GetFlagStatus(TIM4_FLAG_Update) == 0) ;
    TIM4_ClearFlag(TIM4_FLAG_Update);
  }
  TIM4_Cmd(DISABLE);
  //CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, DISABLE);

}

/**
  *****************************************************************************
  * @function       delay_ums
  * @brief       	延迟X * ms,延时时间不精确
  * @para       	ms：延迟ms
  * @attention      系统频率为16M时相对准确，若为2M则不可用
  *****************************************************************************
  */
void delay_ums(u16 ms)//延迟函数，MS级别
{
    unsigned int x,y;
    for(x = ms;x>0;x--)
    {
        for(y = 5000;y>0;y--);
    }
}


/**
  *****************************************************************************
  * @function       delay_nus
  * @brief       	延迟X * us,延时时间不精确
  * @para       	ms：延迟us
  * @attention      系统频率为16M时相对准确，若为2M则不可用
  ****************************************************************************
  */
void delay_nus(u32 nCount)  
{
  	for(char i=0;i<5;i++) 
  	{
    	while (nCount != 0) 
    	{
      		nCount--; 
    	} 
  	} 
}



/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
