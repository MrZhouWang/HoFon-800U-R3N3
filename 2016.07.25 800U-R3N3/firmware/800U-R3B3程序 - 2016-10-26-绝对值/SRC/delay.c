#include "include.h"
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 1ms延时
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
void delay(void)																								
{  
	unsigned char i, j;

	i = 8;
	j = 114;
	do
	{
		while (--j);
	} while (--i);
}
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : ms级延时
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
void delay_ms( INT16U cnt)																							
{  

	while(cnt > 0)
	{
       delay();
	     cnt--;
	}
}