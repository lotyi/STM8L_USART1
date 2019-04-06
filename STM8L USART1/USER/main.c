/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "clock.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "usart1.h"


/* 若不设置系统时钟，则系统时钟默认为 2M Hz */


void main(void)
{
    u8 RX_BUF[USART_BUF_SIZE]; 
    u8 len; 
	u8 t = 0;
	u8 buf[4]={0};
	u8 temp = 0, humi = 0;
	
    disableInterrupts();
	CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//设置系统时钟16M，1分频
	
    LED_Init();
    KEY_Init();
    LED1(ON);
    USART1_Init(9600);
    enableInterrupts();   //开总中断

    while (1)
    {  
        if(USART1_ReceiveData(RX_BUF, &len)) {USART1_SendData(RX_BUF, len);}
	  	
		
	  	GPIO_ToggleBits(LED1_PORT, LED1_PIN);
		delay_ms(100);
		//USART1_SendByte(buf[2]);
    }   
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occu rred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
