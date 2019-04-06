/* Includes ------------------------------------------------------------------*/
#include "clock.h"


u8 CLK_HSE_Init(void)
{
  	CLK_HSEConfig(CLK_HSE_ON);
  	CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSE);    //�л�HSEΪϵͳʱ��
	while(CLK_GetFlagStatus(CLK_FLAG_HSERDY)==RESET);//�ȴ�HSE׼������
   	CLK_SYSCLKSourceSwitchCmd(ENABLE);				  //ʹ���л�
	if(CLK_GetSYSCLKSource()==CLK_SYSCLKSource_HSE) //����Ƿ��л��ɹ�
	{
		return 0;
	}
	return 1;
}















