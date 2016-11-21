#define LED_GLOBAL
#include "include.h"
UINT8  KeyStatus = OFF;		//按键状态
INT8U LedStatus = LED_NONE;   //灯状态
INT16U  LedDelayCnt = 0;
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : ADC初始化
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
void led_blink(void)
{
	LED_R_ON ;
	delay_ms(1000);	
	LED_R_OFF ;	


	LED_G_ON ;	
	delay_ms(1000);
	LED_G_OFF ;
		
	LED_B_ON;	
	delay_ms(1000);	
	LED_G_OFF ;
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
	P0MDIN  |= 0x10;      // P0.4 DIGITAL INPUT
	P0MDOUT |= 0x28;	    // P0.3,5,为推挽输出方式	
	P0MDOUT &= ~(0x45);	  // P0.1,2,6为Open Drain输出方式	
  XBR0  	|= 0x3F;  	  // 跳过使用的IO口P0.0 1 2 3 5 6 	
	XBR2    |= 0X40;	    // 使能交叉开关，使能弱上拉

  
	pOUTPUT  	= OFF;	 	  // 关掉输出
  LED_G_OFF ;   
  LED_B_OFF ;
  LED_R_OFF ;
	   
	pEMILEDCTL = OFF;     //发射管关断
}
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : led控制
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
void led_light_ctrl(INT8U leds)
{
	switch (leds)
	{
		case LED_RED:  		LED_G_OFF; LED_B_OFF;  LED_R_ON;  break;		
		case LED_GREEN:		LED_R_OFF; LED_B_OFF;  LED_G_ON;  break;
		case LED_BLUE:		LED_R_OFF; LED_G_OFF;  LED_B_ON;  break;
		
		case LED_RG:  		LED_B_OFF; LED_R_ON;   LED_G_ON;  break;		
		case LED_RB:		  LED_G_OFF; LED_R_ON;   LED_B_ON;  break;
		case LED_GB:		  LED_R_OFF; LED_G_ON;   LED_B_ON;  break;
		case LED_RGB:		  LED_R_ON;  LED_G_ON;   LED_B_ON;  break;			
		default:			    LED_R_OFF; LED_G_OFF; LED_B_OFF;  break;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : led闪烁控制
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
void CMD_led_flash(void)
{
	if(LedStatus != LED_NONE)
  {

			led_light_ctrl(LedStatus);			// 仅点亮对应颜色

	}
	else//当前不显示
	{
		led_light_ctrl(LED_NONE);	
	}
}

