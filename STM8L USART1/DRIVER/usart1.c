/* Includes ------------------------------------------------------------------*/
#include "usart1.h"


u8 USART1_RX_BUF[USART_BUF_SIZE]; 	//接收缓冲区,最大58个字节
u8 USART1_RX_CNT = 0;   	        //接收到的数据长度


/**
  ****************************************************************************** 
  * @function           USART1_Init
  * @para               uint32_t baud 波特率      
  * @brief              串口初始化函数
  * @attention          字长：8位     停止位：1位     校验：无
  ******************************************************************************
  */
  
void USART1_Init(uint32_t baud)
{
    USART_DeInit(USART1);       //复位USART1
    /* 使能USART1时钟 */
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
    /* 映射配置USART1IO口 */
    SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortC, ENABLE);
    GPIO_Init(USART1_RX_PORT, USART1_RX_PIN, GPIO_Mode_In_PU_No_IT);//RXD
    GPIO_Init(USART1_TX_PORT, USART1_TX_PIN, GPIO_Mode_Out_PP_High_Slow);//TXD
    GPIO_ExternalPullUpConfig(USART1_RX_PORT, USART1_RX_PIN, ENABLE);
    GPIO_ExternalPullUpConfig(USART1_TX_PORT, USART1_TX_PIN, ENABLE);
    /* USART1初始化 */
    USART_Init(USART1, baud, USART_WordLength_8b, 
               USART_StopBits_1, USART_Parity_No, 
               (USART_Mode_Tx|USART_Mode_Rx));
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); //使能接收中断
    USART_ITConfig(USART1,USART_IT_IDLE,ENABLE); //使能IDLE空闲接收中断
    USART_Cmd (USART1,ENABLE);                   //使能USART1
    memset( USART1_RX_BUF, '\0', sizeof(USART1_RX_BUF) );
}

/**
  ******************************************************************************
  * @brief USART1 RX 中断处理函数，处理不定长度接收数据
  * @param  None
  * @retval None
  ******************************************************************************
  */
INTERRUPT_HANDLER(USART1_RX_TIM5_CC_IRQHandler,28)
{
    u8 temp;
      
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)     //收到数据
    {
        temp = USART_ReceiveData8(USART1);                    //读取收到数据
        if(USART1_RX_CNT <= USART_BUF_SIZE)
        {
            USART1_RX_BUF[USART1_RX_CNT] = temp;
            USART1_RX_CNT++;
        }
    }
    else if(USART_GetITStatus(USART1,USART_IT_IDLE) != RESET)//判断IDLE是否空闲
    {
        USART1->SR;
        USART1->DR;                    
    }
    if(USART1->SR & USART_IT_OR)                          //判断串口中断是否过载
    {
        USART_ClearITPendingBit(USART1,USART_IT_OR);
    }       
}
  
/**
  ****************************************************************************** 
  * @function           USART1_ReceiveData
  * @para               u8 *buf 缓冲区首地址, u8 *len  数据长度
  * @brief              接收串口数据，长度不定
  * @retval             0, 1
  ******************************************************************************
  */

u8 USART1_ReceiveData(u8 *buf, u8 *len)
{
    u8 rxlen=USART1_RX_CNT;
    u8 i=0;
    *len=0;				//默认为0
    delay_ums(10);
    if(rxlen==USART1_RX_CNT&&rxlen)     //接收到了数据,且接收完成了
    {
        for(i=0;i<rxlen;i++)
        {
                buf[i]=USART1_RX_BUF[i];	
        }		
        *len=USART1_RX_CNT;	        //记录本次数据长度
        USART1_RX_CNT=0;	        //清零
        return 1;
    }
    return 0;
}


/**
  ****************************************************************************** 
  * @function           USART1_SendByte
  * @para               u8 data 要发送的数据
  * @brief              一次发送一个字节，8bit
  ******************************************************************************
  */

void USART1_SendByte(u8 data)
{   /* 一次发送一个字节 */
    USART_SendData8(USART1, data);
    /* 等待传输结束 */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

/**
  ****************************************************************************** 
  * @function           UART1_SendData
  * @para               u8 *buf 要发送的数据缓冲区首地址
  *                     u8 len  数剧个数
  * @brief              发送指定长度数据(数组)
  ******************************************************************************
  */

void USART1_SendData(u8 *buf, u8 len)
{
    u8 cnt = 0;
    for(cnt = 0; cnt < len; cnt++)
    {
        /* 等待传输结束 */
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
        USART_SendData8(USART1, buf[cnt]);
    }
}



INTERRUPT_HANDLER(USART1_TX_TIM5_UPD_OVF_TRG_BRK_IRQHandler,27)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

  

/*****************************END OF FILE**************************************/
