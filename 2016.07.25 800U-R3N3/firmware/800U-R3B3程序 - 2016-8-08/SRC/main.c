#define MAIN_GLOBAL
#include "include.h"			

INT8U	sampcnt=0;
//////////////////////////////////////////////////////////////////////////////////
//// �������� : ϵͳƵ������
//// ������� : 
//// ���ز��� : 
//// ˵��     :  
//////////////////////////////////////////////////////////////////////////////////
void OSCILLATOR_Init (void)
{   	
	INT8U	i;
	OSCICN   = 0x05;			          //Ƶ��Ϊ24.5Mhz	/4
	for(i = 50; i>0; i--);
	while((OSCICN & 0x10) == 0) ;		// �ж��Ƿ�������
}
//////////////////////////////////////////////////////////////////////////////////
//// �������� : ������
//// ������� : 
//// ���ز��� : 
//// ˵��     :  
//////////////////////////////////////////////////////////////////////////////////
void main(void)
{	
	PCA0MD &= ~0x40; 		     //���Ź���ʱ������ֹ
	RSTSRC |= 0x02;					 //ʹ��VDD��ѹ����
	PORT_Init ();					   // Initialize crossbar and GPIO
	led_blink();													
	
	
	
  					 																						 //
	Timer0_Init ();					 // Timer0 �Զ���װģʽ2
	ADC_Init ();					   // ����ADC
	
	OSCILLATOR_Init();				   // Initialize the system clock		
  	
  Base_ADC();              //  �ɼ���׼ֵ

	PCA0CPL2 = 0xff;				   // 33ms
	PCA0MD  |= 0x60; 		     // ���Ź���ʱ�������� ���������Ź�
	Interrupt_Init ();			 // ���ж�
	while(1)
	{
		PCA0CPH2 = 1;//ι��

      if(f_prossout == TRUE)
			{	
				  f_prossout = FALSE;
					if(sampDat>Dval)
						 out++;
					else
						 out=0;	
			}		
					if(out>Dnum)
					{
						 out=100;
						 pLEDOUTG = ON;
					}
					else
						 pLEDOUTG = OFF;
	} 
}
