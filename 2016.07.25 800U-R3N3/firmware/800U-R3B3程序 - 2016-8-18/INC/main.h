#ifndef _MAIN_H_
#define _MAIN_H_

#include "include.h"



#ifdef MAIN_GLOBAL
#define EXT_MAIN
#else
#define EXT_MAIN extern
#endif

#define		FSLEDONTIME	 1000	 	   			// 占空比打开发射管持续时间
#define		Dval	       1        			// 差值比较
#define		Dnum	       5  	          // 遮挡次数比较 
#define   SYSTEM_INIT	 0         			// 系统状态
#define   KEY_COUNT    10000           //按键关断计时


EXT_MAIN bit		f_prossout;		        // 处理一次输出标志，采集一定脉冲数再处理，TRUE 待处理



EXT_MAIN volatile INT8U	RevBase;		// 基准电压值
EXT_MAIN volatile INT8U sampDat ;
EXT_MAIN volatile INT8U out ;
EXT_MAIN INT16U 	count;		  	      // 对10us计数，最大650ms
EXT_MAIN INT16U 	basecount;          //基础电压采样计时

extern void Disp_Main(void);


#endif


