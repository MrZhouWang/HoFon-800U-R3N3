 #include "include.h"
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 定时器0初始化
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
void Timer0_Init (void)			 // 30us
{
	TR0 = 1;          //Timer0启动,即TCON=0x10;
	ET0 = 1;          //T0溢出中断允许
 	TH0 = (255-10);		//10US 
 	TMOD = 2;			    //定时器0 8bit自动重装载
 	CKCON |= 0x01;		//4分频率  6/4
	EA =0;
}
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 定时器0中断入口函数
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
void Timer0(void) interrupt 1 				//10us
{
	count++;					                  //对10us计数				

  if(LedDelayCnt>0)                   //按键关断计时
		 LedDelayCnt--;
	
	if(count>FSLEDONTIME)               //持续发射
	{	
			if(basecount<100)
				 basecount++;
		count=0;
		pEMILEDCTL = ON;			            // 发射管打开
    count++;
		sampDat = ADC_Samp(); 	          // 采集高端数据	
		if((basecount%10)==0)             //电压采样
		{
			  basecount=101;
				RevBase+=sampDat;
		}
		RevBase=RevBase/10;
		f_prossout = TRUE;
	}
	else
	{
		 pEMILEDCTL = OFF;			          // 发射管关闭
	}
	}

//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 定时器0开启
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
void Interrupt_Init (void)
{
	EA = 1; //中断允许总控制位
}