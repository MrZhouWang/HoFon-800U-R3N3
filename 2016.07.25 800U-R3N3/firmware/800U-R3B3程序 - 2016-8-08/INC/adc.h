#ifndef __ADC_H_
#define __ADC_H_

#define		WDVAL	  0x60//0x40	//0x26	//0.5V		   稳定
#define		WDSSVAL	  0x23//0x2A	//0x1E	//0.4V		   持续闪烁
#define		NOSSVAL	  0x20//0x20	//0X17	//0.3V		   有挡就无
#define		NOVAL	  0x1A//0x1A	//0X11	//0.23V		   无信号										  //0X11
#define 	TRUE		1		//标志的真
#define 	FALSE		0		//标志的假

#define 	ON			1		        //IO口控制的开关管,低电平开
#define 	OFF			0		        //IO口控制的开关管,高电平关


void ADC_Init (void);
INT8U ADC_Samp (void);
void Base_ADC();
#endif


