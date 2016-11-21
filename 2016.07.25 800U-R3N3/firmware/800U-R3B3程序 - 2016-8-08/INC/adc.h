#ifndef __ADC_H_
#define __ADC_H_

#define		WDVAL	  0x60//0x40	//0x26	//0.5V		   �ȶ�
#define		WDSSVAL	  0x23//0x2A	//0x1E	//0.4V		   ������˸
#define		NOSSVAL	  0x20//0x20	//0X17	//0.3V		   �е�����
#define		NOVAL	  0x1A//0x1A	//0X11	//0.23V		   ���ź�										  //0X11
#define 	TRUE		1		//��־����
#define 	FALSE		0		//��־�ļ�

#define 	ON			1		        //IO�ڿ��ƵĿ��ع�,�͵�ƽ��
#define 	OFF			0		        //IO�ڿ��ƵĿ��ع�,�ߵ�ƽ��


void ADC_Init (void);
INT8U ADC_Samp (void);
void Base_ADC();
#endif


