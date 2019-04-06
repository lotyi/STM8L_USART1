/* Includes ------------------------------------------------------------------*/
#include "clock.h"


u8 CLK_HSE_Init(void)
{
  	CLK_HSEConfig(CLK_HSE_ON);
  	CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSE);    //切换HSE为系统时钟
	while(CLK_GetFlagStatus(CLK_FLAG_HSERDY)==RESET);//等待HSE准备就绪
   	CLK_SYSCLKSourceSwitchCmd(ENABLE);				  //使能切换
	if(CLK_GetSYSCLKSource()==CLK_SYSCLKSource_HSE) //监测是否切换成功
	{
		return 0;
	}
	return 1;
}















