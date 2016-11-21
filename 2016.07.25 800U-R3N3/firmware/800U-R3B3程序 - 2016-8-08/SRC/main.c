#define MAIN_GLOBAL
#include "include.h"			

INT8U	sampcnt=0;
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 系统频率设置
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
void OSCILLATOR_Init (void)
{   	
	INT8U	i;
	OSCICN   = 0x05;			          //频率为24.5Mhz	/4
	for(i = 50; i>0; i--);
	while((OSCICN & 0x10) == 0) ;		// 判断是否正常振荡
}
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 主函数
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
void main(void)
{	
	PCA0MD &= ~0x40; 		     //看门狗定时器被禁止
	RSTSRC |= 0x02;					 //使能VDD电压监视
	PORT_Init ();					   // Initialize crossbar and GPIO
	led_blink();													
	
	
	
  					 																						 //
	Timer0_Init ();					 // Timer0 自动重装模式2
	ADC_Init ();					   // 设置ADC
	
	OSCILLATOR_Init();				   // Initialize the system clock		
  	
  Base_ADC();              //  采集基准值

	PCA0CPL2 = 0xff;				   // 33ms
	PCA0MD  |= 0x60; 		     // 看门狗定时器被启用 ，锁定看门狗
	Interrupt_Init ();			 // 开中断
	while(1)
	{
		PCA0CPH2 = 1;//喂狗

      if(f_prossout == TRUE)
			{	
				  f_prossout = FALSE;
					if(sampDat>Dval)
						 out++;
					else
						 out=0;	
			}		
					if(out>Dnum)
					{
						 out=100;
						 pLEDOUTG = ON;
					}
					else
						 pLEDOUTG = OFF;
	} 
}
