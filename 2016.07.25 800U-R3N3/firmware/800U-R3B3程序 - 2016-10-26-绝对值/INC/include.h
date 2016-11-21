#ifndef __INCLUDE_H_
#define __INCLUDE_H_


// 类型重新定义
typedef unsigned char  		BOOLEAN;
typedef unsigned char  		INT8U;              /* Unsigned  8 bit quantity           */
typedef unsigned char  		UINT8;              /* Unsigned  8 bit quantity           */
typedef signed   char  		INT8S;              /* Signed    8 bit quantity           */
typedef unsigned int		  INT16U;             /* Unsigned 16 bit quantity           */
typedef signed   int 		  INT16S;          	/* Signed   16 bit quantity           */
typedef unsigned long int   INT32U;          	/* Unsigned 32 bit quantity           */
typedef signed   long int   INT32S;         	/* Signed   32 bit quantity           */
typedef float          		FP32;               /* Single precision floating point    */
typedef double         		FP64;               /* Double precision floating point    */

typedef INT16U   OS_STK;                  		/* Each stack entry is 32-bit wide                    */
typedef INT16U   OS_CPU_SR;                		/* Define size of CPU status register (PSR = 32 bits) */



#include "C8051F300.H"
#include "timer.h"
#include "adc.h"
#include "led.h"
#include "main.h"
#include "delay.h"
#include "exti.h"
#include "key.h"







#endif


