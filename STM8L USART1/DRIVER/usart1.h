/**
  ******************************************************************************
  * @brief  ���������ļ�
  *         PC5--->TXD     PC6--->RXD
  ******************************************************************************
  */
#ifndef __USART1_H__
#define __USART1_H__

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "stm8l15x_usart.h"
#include "stm8l15x_clk.h"
#include "stm8l15x_gpio.h"
#include "delay.h"
#include "string.h"

/* Exported types ------------------------------------------------------------*/

#define USART1_RX_PORT  GPIOC
#define USART1_RX_PIN   GPIO_Pin_6
  
#define USART1_TX_PORT  GPIOC
#define USART1_TX_PIN   GPIO_Pin_5
      
#define USART_BUF_SIZE   58

extern u8 USART1_RX_BUF[USART_BUF_SIZE]; //���ջ�����,���58���ֽ�
extern u8 USART1_RX_CNT;   	          //���յ������ݳ���

/* Exported functions ------------------------------------------------------- */

void USART1_Init(uint32_t baud);
 u8   USART1_ReceiveData(u8 *buf, u8 *len);
void USART1_SendByte(u8 data);
void USART1_SendData(u8 *buf, u8 len);




#endif


/*****************************END OF FILE**************************************/
