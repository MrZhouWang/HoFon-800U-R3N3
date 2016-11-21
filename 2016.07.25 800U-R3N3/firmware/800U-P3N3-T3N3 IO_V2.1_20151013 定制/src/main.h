#ifndef _MAIN_H_
#define _MAIN_H_

/********************************************************************************************************
*                                              Global CONSTANS
********************************************************************************************************/
/***********************************************************************************
* 变量声明方法(参考uC/OS_II.H)
*	1、在 extern_symbol.h 中每个全局变量都加上 AP_CPU_EXT 的前缀
* 	2、在 main.c 中产生如下效果：  	
*      	#define OS_CPU_GLOBALS：OS_CPU_EXT 被强制为 ‘ ’(空)
*		#include "Head File/extern_symbol.h"：所有变量被定义 
*	3、在其余文件中产生如下效果：
*		未声明 OS_CPU_GLOBALS：OS_CPU_EXT 被强制为 extern
*		#include "Head File/extern_symbol.h"：所有变量被 ‘extern’ 声明、
*	4、在 main.c 中同时有 #include "Head File/parameter_map.h" 其过程描述为：
*		A、在 extern_symbol.h 中首先定义结构类型，并定义变量及分配空间)
*		B、然后在 parameter_map.h 中对变量进行初始化
* 		C、其他文件中 引用 extern_symbol.h，此时首先定义结构类型，然后再做 extern 声明
*	5、注意：在 main.c 中，必须先 #define OS_CPU_GLOBALS 然后再引用 parameter_map.h
************************************************************************************/
#ifdef  AP_CPU_GLOBALS				//是否声明，该源文件定义，其他模块引用		
	#define AP_CPU_EXT				//没有声明 ，则强制为空，此时为变量定义     
#else                                                                           
	#define AP_CPU_EXT  extern		//已声明，则强制为 extern，此时为变量声明   
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
