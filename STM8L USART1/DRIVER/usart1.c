/* Includes ------------------------------------------------------------------*/
#include "usart1.h"


u8 USART1_RX_BUF[USART_BUF_SIZE]; 	//���ջ�����,���58���ֽ�
u8 USART1_RX_CNT = 0;   	        //���յ������ݳ���


/**
  ****************************************************************************** 
  * @function           USART1_Init
  * @para               uint32_t baud ������      
  * @brief              ���ڳ�ʼ������
  * @attention          �ֳ���8λ     ֹͣλ��1λ     У�飺��
  ******************************************************************************
  */
  
void USART1_Init(uint32_t baud)
{
    USART_DeInit(USART1);       //��λUSART1
    /* ʹ��USART1ʱ�� */
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
    /* ӳ������USART1IO�� */
    SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortC, ENABLE);
    GPIO_Init(USART1_RX_PORT, USART1_RX_PIN, GPIO_Mode_In_PU_No_IT);//RXD
    GPIO_Init(USART1_TX_PORT, USART1_TX_PIN, GPIO_Mode_Out_PP_High_Slow);//TXD
    GPIO_ExternalPullUpConfig(USART1_RX_PORT, USART1_RX_PIN, ENABLE);
    GPIO_ExternalPullUpConfig(USART1_TX_PORT, USART1_TX_PIN, ENABLE);
    /* USART1��ʼ�� */
    USART_Init(USART1, baud, USART_WordLength_8b, 
               USART_StopBits_1, USART_Parity_No, 
               (USART_Mode_Tx|USART_Mode_Rx));
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); //ʹ�ܽ����ж�
    USART_ITConfig(USART1,USART_IT_IDLE,ENABLE); //ʹ��IDLE���н����ж�
    USART_Cmd (USART1,ENABLE);                   //ʹ��USART1
    memset( USART1_RX_BUF, '\0', sizeof(USART1_RX_BUF) );
}

/**
  ******************************************************************************
  * @brief USART1 RX �жϴ����������������Ƚ�������
  * @param  None
  * @retval None
  ******************************************************************************
  */
INTERRUPT_HANDLER(USART1_RX_TIM5_CC_IRQHandler,28)
{
    u8 temp;
      
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)     //�յ�����
    {
        temp = USART_ReceiveData8(USART1);                    //��ȡ�յ�����
        if(USART1_RX_CNT <= USART_BUF_SIZE)
        {
            USART1_RX_BUF[USART1_RX_CNT] = temp;
            USART1_RX_CNT++;
        }
    }
    else if(USART_GetITStatus(USART1,USART_IT_IDLE) != RESET)//�ж�IDLE�Ƿ����
    {
        USART1->SR;
        USART1->DR;                    
    }
    if(USART1->SR & USART_IT_OR)                          //�жϴ����ж��Ƿ����
    {
        USART_ClearITPendingBit(USART1,USART_IT_OR);
    }       
}
  
/**
  ****************************************************************************** 
  * @function           USART1_ReceiveData
  * @para               u8 *buf �������׵�ַ, u8 *len  ���ݳ���
  * @brief              ���մ������ݣ����Ȳ���
  * @retval             0, 1
  ******************************************************************************
  */

u8 USART1_ReceiveData(u8 *buf, u8 *len)
{
    u8 rxlen=USART1_RX_CNT;
    u8 i=0;
    *len=0;				//Ĭ��Ϊ0
    delay_ums(10);
    if(rxlen==USART1_RX_CNT&&rxlen)     //���յ�������,�ҽ��������
    {
        for(i=0;i<rxlen;i++)
        {
                buf[i]=USART1_RX_BUF[i];	
        }		
        *len=USART1_RX_CNT;	        //��¼�������ݳ���
        USART1_RX_CNT=0;	        //����
        return 1;
    }
    return 0;
}


/**
  ****************************************************************************** 
  * @function           USART1_SendByte
  * @para               u8 data Ҫ���͵�����
  * @brief              һ�η���һ���ֽڣ�8bit
  ******************************************************************************
  */

void USART1_SendByte(u8 data)
{   /* һ�η���һ���ֽ� */
    USART_SendData8(USART1, data);
    /* �ȴ�������� */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

/**
  ****************************************************************************** 
  * @function           UART1_SendData
  * @para               u8 *buf Ҫ���͵����ݻ������׵�ַ
  *                     u8 len  �������
  * @brief              ����ָ����������(����)
  ******************************************************************************
  */

void USART1_SendData(u8 *buf, u8 len)
{
    u8 cnt = 0;
    for(cnt = 0; cnt < len; cnt++)
    {
        /* �ȴ�������� */
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
