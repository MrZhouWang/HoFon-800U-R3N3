#define LED_GLOBAL
#include "include.h"
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : ADC初始化
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
void led_blink(void)
{
	pLEDOUTR = ON;	
	delay_ms(500);	
	pLEDOUTR = OFF;	

	pLEDOUTG = ON;	
	delay_ms(500);
	pLEDOUTG = OFF;
		
	pLEDOUTB = ON;	
	delay_ms(500);	
	pLEDOUTB = OFF;
}
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : IO初始化
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
void PORT_Init (void)
{	
	P0MDIN  &= ~0x02;    	// P0.1,为模拟输入 	0=模拟输入，1=数字输入
	P0MDIN  |= ~0x10;     // P0.4 DIGITAL INPUT
	P0MDOUT |= 0x6d;	    // P0.0,2,3,5,6为推挽输出方式	
  XBR0  	|= 0x3F;  	  // 跳过使用的IO口P0.0 1 2 3 5 6 	
	XBR2    |= 0X40;	    // 使能交叉开关，使能弱上拉

  
	pOUTPUT  	= OFF;	 	  // 关掉发射管
	pLEDOUTB 	= OFF;	
	pLEDOUTG 	= OFF;	
	pLEDOUTR 	= OFF;	
	pEMILEDCTL  = OFF;    // 管关断
}