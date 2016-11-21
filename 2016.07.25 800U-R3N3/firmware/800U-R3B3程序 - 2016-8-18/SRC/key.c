#define KEY_GLOBAL
#include "include.h"
UINT8  KeyStatus_flag = 0;
//////////////////////////////////////////////////////////////////////////////////
//// 功能描述 : 按键状态监测
//// 输入参数 : 
//// 返回参数 : 
//// 说明     :  
//////////////////////////////////////////////////////////////////////////////////
void key_status()
{
	  if((f_prossout == TRUE)&&(basecount>100)) //按键检测机制 限定是在基准采样完后再做比较
	  {	
			 f_prossout = FALSE;
			 if((sampDat-RevBase)>Dval)
				 out++;
			 else
				 out=0;	
	  }		
		if(out>Dnum)           //有按键
		{
			 out=100;
			 KeyStatus = ON;      
		}
		else
			 KeyStatus = OFF;
}



