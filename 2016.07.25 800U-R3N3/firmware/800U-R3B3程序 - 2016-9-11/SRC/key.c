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
	  if((f_prossout == TRUE)&&(AD_Base == OK)) //���������� �޶����ڻ�׼������������Ƚ�
	  {	
			 f_prossout = FALSE;
			 
			 if((sampDat>RevBase)&&(sampDat-RevBase)>Dval)
				 out++;
			 else                //����ڵ�ʱ����Ч ���¼�ʱ
				 out=0;	
	  }		
		if(out>Dnum)           //�а���
		{
			 out=Dnum+1;
			 KeyStatus = ON;      
		}
		else
			 KeyStatus = OFF;
}



