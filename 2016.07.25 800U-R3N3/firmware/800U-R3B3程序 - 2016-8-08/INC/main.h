#ifndef _MAIN_H_
#define _MAIN_H_

#include "include.h"



#ifdef MAIN_GLOBAL
#define EXT_MAIN
#else
#define EXT_MAIN extern
#endif

#define		FSLEDONTIME	100	 	   // ռ�ձȴ򿪷���ܳ���ʱ��
#define		Dval	0x98	         // ��ֵ�Ƚ�
#define		Dnum	50 	           // �ڵ������Ƚ� 

//  ȫ�ֱ�������
EXT_MAIN bit		f_OUT;			  // ���״̬��־

EXT_MAIN bit		f_prossout;		// ����һ�������־���ɼ�һ���������ٴ���TRUE ������



EXT_MAIN volatile INT8U	RevBase;		  // ��׼��ѹֵ
EXT_MAIN volatile INT8U sampDat ;
EXT_MAIN volatile INT8U out ;
EXT_MAIN INT16U 	count;		  	      // ��10us���������650ms
 




#endif


