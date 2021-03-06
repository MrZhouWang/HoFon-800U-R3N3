#include "include.h"
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : ADC初始化
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
void ADC_Init (void)
{
	AMX0SL = 0X81;      //正端P0.1,负端GND
	ADC0CF = 0x09;      //转换频率为6M（6M max），2倍增益  ,1/2系统时钟 !!!
 	REF0CN = 0x0a;      //VDD作为电压基准, 使能内部ADC参考电压
	ADC0CN 	= 0x80;			//使能ADC0 工作于连续跟踪方式 向AD0BUSY写1启动AD
}
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : ADC采集一次
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
INT8U ADC_Samp (void)
{
	INT8U	tmp,dat;
	AD0INT  = 0;	//清除转换完成标志
	AD0BUSY = 1;	//启动一次转换
	dat = 0;
	
	for(tmp = 50;tmp > 0;tmp --)	   	// F300  2*nop + 19*3*nop + 2*nop = 61nop = 61*40ns*4=9.6us
	{
		if( 1 == AD0INT )//超过限流值关断一段时间
		{
			AD0INT = 0;
			AD0BUSY = 0;
			dat = 	ADC0;
			break;
		}								
	}
	return(dat);
}
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 采集基准电压
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
//void Base_ADC()
//{
//		INT8U	cnt,i;
//		for(i=0;i<100;i++)  //延时一会 
//	  {
//			 pEMILEDCTL = ON;			    // 发射管打开	
//			 cnt++;
//			 RevBase += ADC_Samp();     // 采集基端数据
//			 for(cnt=0;cnt<15;cnt++);  //延时一会 
//			 pEMILEDCTL = OFF;			    // 发射管关闭
//			 delay_ms(1);
//	  }
//	  RevBase=RevBase/100;
//   // RevBase= 0x90;
//		 cnt++;
//		 
//}