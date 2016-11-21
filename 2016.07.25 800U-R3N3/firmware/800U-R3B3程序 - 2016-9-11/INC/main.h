#ifndef _MAIN_H_
#define _MAIN_H_

#include "include.h"



#ifdef MAIN_GLOBAL
#define EXT_MAIN
#else
#define EXT_MAIN extern
#endif

#define		FSLEDONTIME	 100	 	   			// 占空比打开发射管持续时间 定时器内时间计数大于此值时开一次发射管
#define		Dval	       15        			// 遮挡与基准值差值比较        越大设备越稳定
#define		Dnum	       50  	        // 遮挡次数比较    
#define   SYSTEM_INIT	 0         			// 系统状态
#define   KEY_COUNT    10000          //按键关断计时  用于按键移开时灯色平稳切换
#define   BASE_AD_COUNT  500          //记录上电开始中断前面多少个采样可以作为基准采样

#define   OK 8
#define   NO_OK 0


///***基准采样，判断条件越是苛刻越是可以判断精确************************/
//#define   First_Base  50              //第一次开始确定不在空闲
//#define   Second_Base 55              //等待十个发射脉冲之后依然在空闲
//#define   StardBase   3              //小于此数据表示在空闲           




EXT_MAIN bit f_prossout;		          // 处理一次输出标志，采集一定脉冲数再处理，TRUE 待处理


EXT_MAIN volatile INT8U AD_BaseOne;            //确保不是在按键触发式的采样标志
EXT_MAIN volatile INT8U AD_Base;               //电压采样完成  标志
EXT_MAIN volatile INT16U RevBase;		  // 基准电压值
EXT_MAIN volatile INT8U sampDat ;
EXT_MAIN volatile INT8U out ;
EXT_MAIN volatile INT16U 	count;		  	      // 对10us计数，最大650ms
EXT_MAIN volatile INT16U 	basecount;            //基础电压采样计时

extern void Disp_Main(void);


#endif


