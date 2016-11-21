#ifndef _LED_H_
#define _LED_H_
#include "include.h"

#ifdef LED_GLOBAL
#define EXT_LED
#else
#define EXT_LED extern
#endif


sbit pEMILEDCTL  = P0^0;	//红外发射输出
sbit pOUTPUT  = P0^5;			//开关输出 	NPN输出
sbit pINPUT   = P0^4;			//输入
sbit pLEDOUTG = P0^3;			//LED状态灯输出
sbit pLEDOUTB = P0^2;			//LED状态灯输出
sbit pLEDOUTR = P0^6;			//LED状态灯输出



extern void led_blink(void);
extern void PORT_Init (void);
#endif

