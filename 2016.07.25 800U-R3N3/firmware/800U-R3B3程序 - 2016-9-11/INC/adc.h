#ifndef __ADC_H_
#define __ADC_H_
#define 	TRUE		1		//标志的真
#define 	FALSE		0		//标志的假

#define 	ON			1		        //IO口控制的开关管,低电平开
#define 	OFF			0		        //IO口控制的开关管,高电平关


extern void ADC_Init (void);
extern INT8U ADC_Samp (void);
//extern void Base_ADC();
#endif


