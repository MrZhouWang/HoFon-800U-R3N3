/*=========================================================
// 程序更改说明
//  2015年2月5日更改  版本v1.0
//	 1.在800U-T3N3 IB的基础上修改，取消485通信功能
     2.触控芯片为CBM7008
//	 MCU:STC15W408AS   8K Flash  512RAM  EEPROM 5K 	  UART 分组可当三组用 SOP16封装，14个IO口，
         内带晶振和上电复位电路

// 功能说明

工作状态下
有输入信号时，红灯亮，此时手按触控按键，红灯灭，绿灯亮，有信号输出，手离开触控按键后，绿灯灭，无输出信号。

//  2015年8月5日更改  版本v1.1
	1.添加800U-P3N3 IO 型号，通过在main。h文件选择相应的型号进行条件编译，生成目标文件


//  2015年8月24日更改  版本v2.0  	 GNN（G 有使能绿灯亮 N 有按键无灯亮 N 按键松开无灯亮）
1.更改说明
工作状态下 

     使能     按键	    灯    输出
			
			 0		   按下		  灭	   有
			 0		   松开		  灭	   无
			 1		   松开		  绿	   无
			 1		   按下		  绿	   有

使能：1 使能输入   0 无使能输入



//  2015年9月8日更改  版本v2.1 	  	 适用800U T3N3 IO和800U P3N3 IO
1.更改V2.0版本的架构，通过条件编译，使能时亮灯颜色，按键按下亮灯颜色，松开亮灯颜色可选择，如RGG GNN RGB GRN等

RGG （R 有使能红灯亮 G 有按键绿灯亮 G 按键松开绿灯亮）
2.工作状态下 

           使能        按键	      灯      输出
			
			 0		   按下		  灭	   有
			 0		   松开		  灭	   无
			 1		   松开		  红	   无
			 1		   按下		  绿（常亮）有	   

使能：1 使能输入   0 无使能输入


客户定制5套，使能输入亮红灯 无输入灭  按键按下亮黄灯 松开灭		20151218

=========================================================*/

#define AP_CPU_GLOBALS	
#include "extern_symbol.h" 

INT8U sysStatus = SYSTEM_INIT;	  //  0
INT8U LedStatus = NONE;
//INT8U p_mcu_flag = 0;    // 信号输出标志

UINT8  KeyStatus = 0;		//按键状态
UINT8  KeyStatus_flag = 0;		//按键状态标志
UINT8  LedDelayCnt = 0;		 //延时计数器


/*******************************************************************************
	 					1毫秒延迟函数
*******************************************************************************/
void Delay1Ms() 
{
    UINT16 i = 852;
    while (i != 0) {i--;}
}

/*******************************************************************************
	 					毫秒延迟函数
    input   usDelay     延迟时间值
	output  none
*******************************************************************************/

void DelayMs(UINT16 usDelay)
{
    for(; usDelay>0; usDelay--)
    {
        Delay1Ms();
    }   
}

/*******************************************************************************
	 					250uS毫秒延迟函数
*******************************************************************************/
// void Delay125Us() 
// {
//    UINT16 i = 426;
//  //    UINT16 i = 156;
//     while (i != 0) {i--;}
// }


void Timer0Init(void)		//50毫秒@11.0592MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0x00;		//设置定时器模式
	TL0 = 0x00;		//定时初值
	TH0 = 0x4C;		//定时初值
	TF0 = 0;		//清除IF0标志
    ET0 = 1;
	TR0 = 1;		//定时器0开始计数
}


/*******************************************************************************
	 					 看门狗复位点亮蓝灯
*******************************************************************************/
void WDT_Reset(void)
{
	WDT_CONTR = WDT_CONTR & 0x0F;
}

/*******************************************************************************
	 					  端口初始化
*******************************************************************************/
void IO_Init(void)
{
	//推挽输出 PxM1和PxM0对应配成0x00,0x10
	 P5M1 = 0x00;
	 P5M0 = 0x10;

	//开漏输出	PxM1和PxM0对应配成11
	P3M1 = 0x0C;				   // SDA和SCL口配成开漏，3.3V
	P3M0 = 0x0C;	

	P1M1 = 0x1C;				   // BLUE和RED和GREEN口配成开漏，5V
	P1M0 = 0x1C;

	p_led_red = 1; 		
	p_led_green = 1;
	p_mcu_ctr = 1;
}

/***********************************************************
    				根据编号控制灯亮灭
************************************************************/

void led_light_ctrl(INT8U status)
{
	
	switch(status)
	{
	 case RED:	
	 			p_led_red   = LED_ON;	  //红灯亮
				p_led_green = LED_OFF;	  //绿灯灭
				p_led_blue  = LED_OFF;	  //蓝灯灭
				break;
	 case GREEN: 
	 			p_led_green = LED_ON;	  //绿灯亮
				p_led_red   = LED_OFF;	  //红灯灭
				p_led_blue  = LED_OFF;	  //蓝灯灭
				break;
	
	 case BLUE: 
	 			p_led_blue  = LED_ON;	  //蓝灯亮
				p_led_red   = LED_OFF;	  //红灯灭
				p_led_green = LED_OFF;	  //绿灯灭
				break;	

	 case RG_YELLOW:					  //合成黄色
	 			p_led_red   = LED_ON;	  //红灯亮
				p_led_green = LED_ON;	  //绿灯亮
				p_led_blue  = LED_OFF;	  //蓝灯灭
				break;
	 case RB_GREEN: 
	 			p_led_green = LED_ON;	  //绿灯亮
				p_led_red   = LED_ON;	  //红灯亮
				p_led_blue  = LED_OFF;	  //蓝灯灭
				break;
	
	 case GB_BLUE: 
	 			p_led_blue  = LED_ON;	  //蓝灯亮
				p_led_red   = LED_OFF;	  //红灯灭
				p_led_green = LED_ON;	  //绿灯亮
				break;

	 case RGB_WHITE: 
	 			p_led_blue  = LED_ON;	  //蓝灯亮
				p_led_red   = LED_ON;	  //红灯亮
				p_led_green = LED_ON;	  //绿灯亮
				break;

	 default:
	 			p_led_red   = LED_OFF;	  //红灯灭
				p_led_green = LED_OFF;	  //绿灯灭
				p_led_blue  = LED_OFF;	  //蓝灯灭
	}
}


/***********************************************************
    				singal_output 
************************************************************/
//void singal_output(void)

void KeyCheck(void)
{
//	UINT8  KeyStatus = 0;
	#if	 (MACHINETYPE == T3N3_800U)
	    if (Scan_Val()==1)                                          //有按键	
	    {        
			KeyStatus = 1;										//按键状态置1	        
	    } 

	    if (Scan_Val()!=1)
	    {   
		    KeyStatus = 0;
	    } 

	#elif  (MACHINETYPE == P3N3_800U)
	    if (p_KEY_OK == 0)                                          //有按键	
	    {        
			KeyStatus = 1;	 
			KeyStatus_flag = 1;       								//	按键状态标志置1
	    } 
		    
	    if (p_KEY_OK != 0)
	    {   
		   	KeyStatus = 0;
			if (KeyStatus_flag == 1)  
			{
				 KeyStatus_flag = 0;
				 LedDelayCnt = 50;
			}
	    } 
		
	#endif
}

/***********************************************************
    				              T0中断
************************************************************/
void T0_int (void) interrupt 1
{
	EA = 0;		              //定时器0开始计数	
    WDT_CONTR = 0x30;         //喂狗		
    EA = 1;
}

/*******************************************************************************
	 						main program				
*******************************************************************************/   
int main(void) 
{   
	INT8U sysStatus = 0;
	IO_Init();
    WDT_Reset();
	DelayMs(300);														   // 等待电源稳定

	#if	 (MACHINETYPE == T3N3_800U)    		                                
		CBM7008_init();	
	#endif
															// 必须开机后200ms再设置灵敏度	
	Timer0Init();			                                
	EA = 1;
	while(1)
	{	
		KeyCheck();     
//		test = ~test;
        DelayMs(10);
	
		//灯输出由使能控制
		if (p_signal_input == 1)									   //无使能输入
		{
		   //无使能输入
		  if( LedDelayCnt != 0 )
			{ LedDelayCnt--; }
			else
			{
				led_light_ctrl(NONE);									   //灯全灭
				LedStatus = NONE;
			}

			if (KeyStatus == 1)
			{
				 LedStatus = KEY_PRESS_LED;						              ///////
			}
			sysStatus = 0;											   // 无使能
			
		}
		else                        								   //有使能输入
		{
			//有使能输入

		   	LedStatus = EN_SIGNAL_ON_LED;					 //使能对应灯色
				
			if (KeyStatus == 1)  
			{	//有按键
				LedStatus = KEY_PRESS_LED;					//按键按下灯色
				sysStatus = 1;								//第一次按下
			}
			else  if(sysStatus == 1)
		    {	//无按键
				if( LedDelayCnt != 0 )
				{ 
					LedDelayCnt--;
					LedStatus = KEY_PRESS_LED;
				}					                         //按键按下灯色 }
				else  if (KeyStatus_flag == 1)
				{				
					LedStatus = KEY_RELEASE_LED;				//	按键按下灯色
				}
				else
				{
					 LedStatus =  EN_SIGNAL_ON_LED;
				}
			}
		   	//在使能情况下不灭灯
		    if (LedStatus == NONE)
			{
				LedStatus = EN_SIGNAL_ON_LED;
			}
										
		 }

		 led_light_ctrl(LedStatus);

		// 24V输出由按键控制
		if (KeyStatus == 1)                                          //有按键	
		{        
		   p_mcu_ctr = 0;       									//24V信号输出 
		// Delay250Us();
		   DelayMs(1);
		  if (p_singal_out == 1)                                  //反馈信号异常
		  {    
		    p_mcu_ctr = 1;                                       //关闭输出    0 关闭							        
		  }
		}
		else //if(KeyStatus == 0)
		{
			p_mcu_ctr = 1;
		}
	}
}			
