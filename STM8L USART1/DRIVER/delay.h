/**
  ******************************************************************************
  * @file    delay.h
  * @author  Microcontroller Division
  * @version V1.2.0
  * @date    09/2010
  * @brief   delay functions header
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
#ifndef __DELAY_H__
#define __DELAY_H__

#include "stm8l15x.h"
#include "stm8l15x_clk.h"
#include "stm8l15x_tim4.h"

//系统时钟默认为2M
//CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
//------------------------------------------------------------------------------
// Function Name : delay_ms
// Description   : delay for some time in ms unit
// Input         : n_ms is how many ms of time to delay
//------------------------------------------------------------------------------
void delay_ms(u16 n_ms) ;


//------------------------------------------------------------------------------
// Function Name : delay_10us
// Description   : delay for some time in 10us unit(partial accurate)
// Input         : n_10us is how many 10us of time to delay
//------------------------------------------------------------------------------
void delay_10us(u16 n_10us);

//------------------------------------------------------------------------------
// Function Name : delay_us
// Description   : delay for some time in us unit(partial accurate)
// Input         : n_us is how many 10us of time to delay
//------------------------------------------------------------------------------
void delay_us(u16 n_us);

//------------------------------------------------------------------------------
// Function Name : delay_ums
// Description   : delay for some time in 10us unit(not very accurate)
// Input         : ums is how many 10us of time to delay
//------------------------------------------------------------------------------
void delay_ums(u16 ms);

void delay_nus(u32 nCount);

#endif
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
