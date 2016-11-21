#ifndef _LED_H_
#define _LED_H_
#include "include.h"

#ifdef LED_GLOBAL
#define EXT_LED
#else
#define EXT_LED extern
#endif


sbit pEMILEDCTL  = P0^0;	//���ⷢ�����
sbit pOUTPUT  = P0^5;			//������� 	NPN���
sbit pINPUT   = P0^4;			//����
sbit pLEDOUTG = P0^3;			//LED״̬�����
sbit pLEDOUTB = P0^2;			//LED״̬�����
sbit pLEDOUTR = P0^6;			//LED״̬�����



extern void led_blink(void);
extern void PORT_Init (void);
#endif

