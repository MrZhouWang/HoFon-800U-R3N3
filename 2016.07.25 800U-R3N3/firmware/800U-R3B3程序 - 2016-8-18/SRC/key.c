#define KEY_GLOBAL
#include "include.h"
UINT8  KeyStatus_flag = 0;
//////////////////////////////////////////////////////////////////////////////////
//// �������� : ����״̬���
//// ������� : 
//// ���ز��� : 
//// ˵��     :  
//////////////////////////////////////////////////////////////////////////////////
void key_status()
{
	  if((f_prossout == TRUE)&&(basecount>100)) //���������� �޶����ڻ�׼������������Ƚ�
	  {	
			 f_prossout = FALSE;
			 if((sampDat-RevBase)>Dval)
				 out++;
			 else
				 out=0;	
	  }		
		if(out>Dnum)           //�а���
		{
			 out=100;
			 KeyStatus = ON;      
		}
		else
			 KeyStatus = OFF;
}



