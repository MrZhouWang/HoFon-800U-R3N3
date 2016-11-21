//iic.h - 实现相关的头文件
#if	 (MACHINETYPE == T3N3_800U)
	#include "extern_symbol.h"

	#ifndef __CBM7008_H__
	#define __CBM7008_H__
 
// *******************************常量定义********************************** //

//#define    CBM7008GPIO    GPIOB

#define	   SETSDA()	       (pSDA = 1)
#define	   RESETSDA()	   (pSDA = 0)  
#define	   SETSCL()	       (pSCL = 1) 
#define	   RESETSCL()	   (pSCL = 0)
#define	   READSDABIT()	    pSDA

// 设备地址0x00~0xFF,默认0x22
#define DEV_ADDR_W		((0x22<<1)&0xFE)
#define DEV_ADDR_R		((0x22<<1)|0x01)	

// 内部寄存器地址
#define MEM_ADDR_GET_ID		0x01	//芯片ID,                读，2byte 数据	 byte0:0xCB,byte1:0x72,
#define MEM_ADDR_GET_NLMD	0x0B	//获取所有按键灵敏度参数 读  Nbyte 数据
#define MEM_ADDR_SET_1LMD	0x21	//设置单个按键灵敏度参数 写	 2byte 数据
#define MEM_ADDR_SET_NLMD	0x22	//设置多个按键灵敏度参数 写	 Nbyte 数据
#define MEM_ADDR_GET_KEYSTS	 0xA8 	//获取按键信息			 读  2byte 数据

AP_CPU_EXT INT8U IDATA lmd[8];	  // CMB7008灵敏度

#define MAX_CBM7008LMD      48    	 //1
#define MIN_CBM7008LMD      20    	 //0
#define DEF_CBM7008LMD      30    	 //1
																				
#define CBM7008ID	0xCB72

sbit pSDA = P3^2;
sbit pSCL = P3^3;

sbit p_singal_out     = P1^5;
sbit p_signal_input   = P1^0;
sbit p_mcu_ctr        = P5^4;

//======================================================
void CBM7008_init();
INT8U Scan_Val();
void Set_CBM7008_nLMD();
//======================================================
#endif
#endif
