#ifndef _MAIN_H_
#define _MAIN_H_

#include "include.h"



#ifdef MAIN_GLOBAL
#define EXT_MAIN
#else
#define EXT_MAIN extern
#endif

#define		FSLEDONTIME	 1000	 	   			// ռ�ձȴ򿪷���ܳ���ʱ��
#define		Dval	       1        			// ��ֵ�Ƚ�
#define		Dnum	       5  	          // �ڵ������Ƚ� 
#define   SYSTEM_INIT	 0         			// ϵͳ״̬
#define   KEY_COUNT    10000           //�����ضϼ�ʱ


EXT_MAIN bit		f_prossout;		        // ����һ�������־���ɼ�һ���������ٴ���TRUE ������



EXT_MAIN volatile INT8U	RevBase;		// ��׼��ѹֵ
EXT_MAIN volatile INT8U sampDat ;
EXT_MAIN volatile INT8U out ;
EXT_MAIN INT16U 	count;		  	      // ��10us���������650ms
EXT_MAIN INT16U 	basecount;          //������ѹ������ʱ

extern void Disp_Main(void);


#endif


