#ifndef _MAIN_H_
#define _MAIN_H_

/********************************************************************************************************
*                                              Global CONSTANS
********************************************************************************************************/
/***********************************************************************************
* ������������(�ο�uC/OS_II.H)
*	1���� extern_symbol.h ��ÿ��ȫ�ֱ��������� AP_CPU_EXT ��ǰ׺
* 	2���� main.c �в�������Ч����  	
*      	#define OS_CPU_GLOBALS��OS_CPU_EXT ��ǿ��Ϊ �� ��(��)
*		#include "Head File/extern_symbol.h"�����б��������� 
*	3���������ļ��в�������Ч����
*		δ���� OS_CPU_GLOBALS��OS_CPU_EXT ��ǿ��Ϊ extern
*		#include "Head File/extern_symbol.h"�����б����� ��extern�� ������
*	4���� main.c ��ͬʱ�� #include "Head File/parameter_map.h" ���������Ϊ��
*		A���� extern_symbol.h �����ȶ���ṹ���ͣ����������������ռ�)
*		B��Ȼ���� parameter_map.h �жԱ������г�ʼ��
* 		C�������ļ��� ���� extern_symbol.h����ʱ���ȶ���ṹ���ͣ�Ȼ������ extern ����
*	5��ע�⣺�� main.c �У������� #define OS_CPU_GLOBALS Ȼ�������� parameter_map.h
************************************************************************************/
#ifdef  AP_CPU_GLOBALS				//�Ƿ���������Դ�ļ����壬����ģ������		
	#define AP_CPU_EXT				//û������ ����ǿ��Ϊ�գ���ʱΪ��������     
#else                                                                           
	#define AP_CPU_EXT  extern		//����������ǿ��Ϊ extern����ʱΪ��������   
#endif
/***********************************************************************************/
#define	T3N3_800U  0
#define	P3N3_800U  1

//#define	MACHINETYPE  T3N3_800U
#define	MACHINETYPE  P3N3_800U

#if	 (MACHINETYPE == T3N3_800U)
	#include "CBM7008.h"

#elif	 (MACHINETYPE == P3N3_800U)
	sbit p_signal_input   = P3^7;
	sbit p_singal_out     = P3^6;
	sbit p_mcu_ctr        = P1^1;
	sbit p_KEY_OK         = P1^0;
#endif

//sbit test = P1^1;

sbit p_led_red    = P1^4;      
sbit p_led_green  =  P1^3;      
sbit p_led_blue   = P1^2;
									
#define CMD_KEY_NULL 	0
#define CMD_KEY_OK		1

#define SYSTEM_INIT		0

#define L_SIGNAL		0
#define L_BUTTON   	    1



#define NONE			  0
#define RED				  1
#define GREEN			  2
#define BLUE			  3

#define RG_YELLOW		  4
#define RB_GREEN		  5
#define GB_BLUE			  6
#define RGB_WHITE		  7


//enable led 
#define EN_SIGNAL_ON_LED  RED			
//#define EN_SIGNAL_ON_LED  GREEN
//#define EN_SIGNAL_ON_LED  BLUE
//#define EN_SIGNAL_ON_LED  RG_YELLOW
//#define EN_SIGNAL_ON_LED  NONE	

//KEY press
//#define KEY_PRESS_LED  RED			
//#define KEY_PRESS_LED  GREEN
//#define KEY_PRESS_LED  BLUE
#define KEY_PRESS_LED  RG_YELLOW	
//#define KEY_PRESS_LED  NONE

//KEY release
//#define KEY_RELEASE_LED  RED			
//#define KEY_RELEASE_LED  GREEN
//#define KEY_RELEASE_LED  BLUE	
//#define KEY_RELEASE_LED  RG_YELLOW	
#define KEY_RELEASE_LED  NONE

void DelayMs(UINT16 usDelay);

#endif
