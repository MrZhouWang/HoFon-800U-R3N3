#ifndef _MAIN_H_
#define _MAIN_H_

#include "include.h"



#ifdef MAIN_GLOBAL
#define EXT_MAIN
#else
#define EXT_MAIN extern
#endif

#define		FSLEDONTIME	 100	 	   			// ռ�ձȴ򿪷���ܳ���ʱ�� ��ʱ����ʱ��������ڴ�ֵʱ��һ�η����
#define		Dval	       15        			// �ڵ����׼ֵ��ֵ�Ƚ�        Խ���豸Խ�ȶ�
#define		Dnum	       50  	        // �ڵ������Ƚ�    
#define   SYSTEM_INIT	 0         			// ϵͳ״̬
#define   KEY_COUNT    10000          //�����ضϼ�ʱ  ���ڰ����ƿ�ʱ��ɫƽ���л�
#define   BASE_AD_COUNT  500          //��¼�ϵ翪ʼ�ж�ǰ����ٸ�����������Ϊ��׼����

#define   OK 8
#define   NO_OK 0


///***��׼�������ж�����Խ�ǿ���Խ�ǿ����жϾ�ȷ************************/
//#define   First_Base  50              //��һ�ο�ʼȷ�����ڿ���
//#define   Second_Base 55              //�ȴ�ʮ����������֮����Ȼ�ڿ���
//#define   StardBase   3              //С�ڴ����ݱ�ʾ�ڿ���           




EXT_MAIN bit f_prossout;		          // ����һ�������־���ɼ�һ���������ٴ���TRUE ������


EXT_MAIN volatile INT8U AD_BaseOne;            //ȷ�������ڰ�������ʽ�Ĳ�����־
EXT_MAIN volatile INT8U AD_Base;               //��ѹ�������  ��־
EXT_MAIN volatile INT16U RevBase;		  // ��׼��ѹֵ
EXT_MAIN volatile INT8U sampDat ;
EXT_MAIN volatile INT8U out ;
EXT_MAIN volatile INT16U 	count;		  	      // ��10us���������650ms
EXT_MAIN volatile INT16U 	basecount;            //������ѹ������ʱ

extern void Disp_Main(void);


#endif


