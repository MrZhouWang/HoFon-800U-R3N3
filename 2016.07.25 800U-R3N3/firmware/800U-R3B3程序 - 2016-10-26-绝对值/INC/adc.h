#ifndef __ADC_H_
#define __ADC_H_


#define 	TRUE		1		                        //��־����
#define 	FALSE		0		                        //��־�ļ�

#define 	ADC_BASE_CARITICAL_LOW    60			  //�����׼��ѹֵ���ٽ�ֵ   �ͽ�� 0.8v
#define 	ADC_BASE_CARITICAL_HIGH   115			  //�����׼��ѹֵ���ٽ�ֵ   �߽�� 1.5V


#define 	ON			1		                        //IO�ڿ��ƵĿ��ع�,�͵�ƽ��
#define 	OFF			0		                        //IO�ڿ��ƵĿ��ع�,�ߵ�ƽ��




extern void ADC_Init (void);
extern INT8U ADC_Samp (void);
extern void Base_ADC();
#endif


