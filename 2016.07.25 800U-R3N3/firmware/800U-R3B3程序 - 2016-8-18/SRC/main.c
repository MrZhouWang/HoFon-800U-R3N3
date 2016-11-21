/********************************************************************************
工作状态下 

      使能     按键	    灯        输出
			
			 0		   按下		  黄    	   有
			 0		   松开		  灭	       无
			 1		   松开		  红	       无
			 1		   按下		  绿         有	   

使能：1 使能输入   0 无使能输入
********************************************************************************/

#define MAIN_GLOBAL
#include "include.h"			
INT8U sysStatus = SYSTEM_INIT;	  //系统状态
INT16U 	basecount=0;
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
	for(i = 500; i>0; i--);
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
	//delay_ms(100);	
	PCA0MD &= ~0x40; 		         //看门狗定时器被禁止
	RSTSRC |= 0x02;					     //使能VDD电压监视
	PORT_Init ();					  		 // Initialize crossbar and GPIO
	led_blink();														
	Timer0_Init ();						   // Timer0 自动重装模式2
	ADC_Init ();					   		 // 设置ADC
	OSCILLATOR_Init();			     // Initialize the system clock	

  delay_ms(100);		
  //Base_ADC();                  //  采集基准值
	
	
	PCA0CPL2 = 0xff;				     // 33ms
	PCA0MD  |= 0x60; 		         // 看门狗定时器被启用 ，锁定看门狗
	Interrupt_Init ();			     // 开中断
	while(1)
	{
		PCA0CPH2 = 1;              //喂狗	
		key_status();              //按键状态检测
		PCA0CPH2 = 1;              //喂狗	
		Disp_Main();               //显示
		PCA0CPH2 = 1;              //喂狗	
		CMD_led_flash();           //刷新灯色
    PCA0CPH2 = 1;              //喂狗			
	} 
}
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 触控机制
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
void Disp_Main(void)
{
	 	if(p_signal_input == 1)        	                 //无输入
		{
			 LedStatus &= DISEN_SIGNAL_ON_LED;             //使能对应灯色
			 if (KeyStatus == ON)                          //无输入时按键按下时黄灯亮
			 {
				  OUTPUT_ON;                                 //输出开
				  LedStatus = KEY_PRESS_LED_NOIN ;	
          LedDelayCnt=KEY_COUNT;	                   //设置按键松开灯亮延时			 
			 }
			 else if(KeyStatus == OFF)                     //当按键松开时
			 {
				  OUTPUT_OFF;                                //输出关
				  if(LedDelayCnt == 0)
						 LedStatus &= KEY_RELEASE_LED_NOIN; 				
			 }	 				 
		}
		else if (p_signal_input == 0)                     //有输入
		{
			 if(LedDelayCnt == 0)                           //不能马上切换颜色
			 { 
					LedStatus = EN_SIGNAL_ON_LED;	              //使能对应灯色
			 }
			 if (KeyStatus == ON)  
			 {	
				  OUTPUT_ON;                                  //输出开
				  LedStatus = KEY_PRESS_LED_IN ;              //按键按下灯色
				  sysStatus = 1;								              //第一次按下
				  LedDelayCnt=KEY_COUNT;	                    //设置按键松开灯亮延时					 
			 }
			 else if(KeyStatus == OFF)                      //当按键松开时
			 {				  
			    if(LedDelayCnt == 0)                        //不马上关闭按键按下时候的状态
					{
						 OUTPUT_OFF;                              //输出关
						 LedStatus &= KEY_RELEASE_LED_IN; 
						 sysStatus=0;
					}
			 }
		 }
}
