/********************************************************************************
工作状态下 

      使能     按键	    灯        输出
			
			 0		   按下		  黄    	   有
			 0		   松开		  灭	       无
			 1		   松开		  红	       无
			 1		   按下		  绿         有	   

使能：1 使能输入   0 无使能输入


基准采样在定时器初上电几个周期内完成，与平时采样环境保持一致

2016.09.18  感应离开延时100ms灯色切换
2016.10.27  开关状态对比值采用绝对值
2016.10.27  基准采样在上电的时候取100次平均值 标准基准值在1.35V左右 如果基准值不在这个范围内则红灯常亮在报警状态
2016.10.28  集准采样发生异常设备会进行相应的异常指示
********************************************************************************/

#define MAIN_GLOBAL
#include "include.h"			
INT8U sysStatus = SYSTEM_INIT;	  //系统状态
INT16U 	basecount=0;
INT8U   out=0;
INT16U RevBase=0;
bit f_prossout= FALSE;
bit valid_ok = FALSE;
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 系统频率设置
//// 输入参数 : 
//// 返回参数 : 
//// 说明     : 
//////////////////////////////////////////////////////////////////////////////////
void OSCILLATOR_Init (void)
{   	
	INT8U	i;
	OSCICN   = 0x06;			          //频率为25Mhz	/2 =12.5
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
	
	OSCILLATOR_Init();			     // Initialize the system clock														
	Timer0_Init ();						   // Timer0 自动重装模式2

	ADC_Init ();					   		 // 设置ADC
	

  delay_ms(100);		
	
	Base_ADC();                  //基准采样
	led_blink();	
	PCA0CPL2 = 0xff;				     // 33ms
	PCA0MD  |= 0x60; 		         // 看门狗定时器被启用 ，锁定看门狗
	Interrupt_Init ();			     // 开中断
	while(1)
	{
		PCA0CPH2 = 1;              //喂狗
		if(AD_Base_OK != OK)       //采集基准电压失败 指示 
		{
			 if(ADC_BaseErrNum == 0)
	        ADC_BASE_ERR_BLINK();		
		}	
    else
		{
			 key_status();              //按键状态检测
		   PCA0CPH2 = 1;              //喂狗	
		   Disp_Main();               //显示
		   PCA0CPH2 = 1;              //喂狗	
		   CMD_led_flash();           //刷新灯色     
		}
		PCA0CPH2 = 1;                 //喂狗			
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
			 if (KeyStatus == ON)                          //无输入时按键按下时黄灯亮
			 {
				  OUTPUT_ON;                                 //输出开
				  LedStatus = KEY_PRESS_LED_NOIN ;	
          LedDelayCnt=KEY_COUNT;	                   //设置按键松开灯亮延时		在定时器里延时	 
			 }
			 else if(KeyStatus == OFF)                     //当按键松开时
			 {
				  OUTPUT_OFF;                                //输出关
				  if(LedDelayCnt == 0)
						 LedStatus = KEY_RELEASE_LED_NOIN; 				
			 }	 				 
		}
		
		else if (p_signal_input == 0)                     //有输入
		{
			 if (KeyStatus == ON)  
			 {	
				  OUTPUT_ON;                                  //输出开
				  LedStatus = KEY_PRESS_LED_IN ;              //按键按下灯色
				  sysStatus = 1;								              //第一次按下
				  LedDelayCnt=KEY_COUNT;	                    //设置按键松开灯亮延时					 
			 }
			 else if(KeyStatus == OFF)                      //当按键松开时
			 {				  
				  OUTPUT_OFF;                                 //输出关
			    if(LedDelayCnt == 0)                        //不马上关闭按键按下时候的状态
					{                      
						 LedStatus = KEY_RELEASE_LED_IN; 
						 sysStatus=0;
					}
			 }
		 }
}
