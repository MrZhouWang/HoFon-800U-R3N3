/********************************************************************************
����״̬�� 

      ʹ��     ����	    ��        ���
			
			 0		   ����		  ��    	   ��
			 0		   �ɿ�		  ��	       ��
			 1		   �ɿ�		  ��	       ��
			 1		   ����		  ��         ��	   

ʹ�ܣ�1 ʹ������   0 ��ʹ������


��׼�����ڶ�ʱ�����ϵ缸����������ɣ���ƽʱ������������һ��

2016.09.18  ��Ӧ�뿪��ʱ100ms��ɫ�л�
2016.10.27  ����״̬�Ա�ֵ���þ���ֵ
2016.10.27  ��׼�������ϵ��ʱ��ȡ100��ƽ��ֵ ��׼��׼ֵ��1.35V���� �����׼ֵ���������Χ�����Ƴ����ڱ���״̬
2016.10.28  ��׼���������쳣�豸�������Ӧ���쳣ָʾ
********************************************************************************/

#define MAIN_GLOBAL
#include "include.h"			
INT8U sysStatus = SYSTEM_INIT;	  //ϵͳ״̬
INT16U 	basecount=0;
INT8U   out=0;
INT16U RevBase=0;
bit f_prossout= FALSE;
bit valid_ok = FALSE;
//////////////////////////////////////////////////////////////////////////////////
//// �������� : ϵͳƵ������
//// ������� : 
//// ���ز��� : 
//// ˵��     : 
//////////////////////////////////////////////////////////////////////////////////
void OSCILLATOR_Init (void)
{   	
	INT8U	i;
	OSCICN   = 0x06;			          //Ƶ��Ϊ25Mhz	/2 =12.5
	for(i = 500; i>0; i--);
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
	//delay_ms(100);	
	PCA0MD &= ~0x40; 		         //���Ź���ʱ������ֹ
	RSTSRC |= 0x02;					     //ʹ��VDD��ѹ����
	PORT_Init ();					  		 // Initialize crossbar and GPIO
	
	OSCILLATOR_Init();			     // Initialize the system clock														
	Timer0_Init ();						   // Timer0 �Զ���װģʽ2

	ADC_Init ();					   		 // ����ADC
	

  delay_ms(100);		
	
	Base_ADC();                  //��׼����
	led_blink();	
	PCA0CPL2 = 0xff;				     // 33ms
	PCA0MD  |= 0x60; 		         // ���Ź���ʱ�������� ���������Ź�
	Interrupt_Init ();			     // ���ж�
	while(1)
	{
		PCA0CPH2 = 1;              //ι��
		if(AD_Base_OK != OK)       //�ɼ���׼��ѹʧ�� ָʾ 
		{
			 if(ADC_BaseErrNum == 0)
	        ADC_BASE_ERR_BLINK();		
		}	
    else
		{
			 key_status();              //����״̬���
		   PCA0CPH2 = 1;              //ι��	
		   Disp_Main();               //��ʾ
		   PCA0CPH2 = 1;              //ι��	
		   CMD_led_flash();           //ˢ�µ�ɫ     
		}
		PCA0CPH2 = 1;                 //ι��			
	} 
}
//////////////////////////////////////////////////////////////////////////////////
//// �������� : ���ػ���
//// ������� : 
//// ���ز��� : 
//// ˵��     :  
//////////////////////////////////////////////////////////////////////////////////
void Disp_Main(void)
{
	 	if(p_signal_input == 1)        	                 //������
		{            
			 if (KeyStatus == ON)                          //������ʱ��������ʱ�Ƶ���
			 {
				  OUTPUT_ON;                                 //�����
				  LedStatus = KEY_PRESS_LED_NOIN ;	
          LedDelayCnt=KEY_COUNT;	                   //���ð����ɿ�������ʱ		�ڶ�ʱ������ʱ	 
			 }
			 else if(KeyStatus == OFF)                     //�������ɿ�ʱ
			 {
				  OUTPUT_OFF;                                //�����
				  if(LedDelayCnt == 0)
						 LedStatus = KEY_RELEASE_LED_NOIN; 				
			 }	 				 
		}
		
		else if (p_signal_input == 0)                     //������
		{
			 if (KeyStatus == ON)  
			 {	
				  OUTPUT_ON;                                  //�����
				  LedStatus = KEY_PRESS_LED_IN ;              //�������µ�ɫ
				  sysStatus = 1;								              //��һ�ΰ���
				  LedDelayCnt=KEY_COUNT;	                    //���ð����ɿ�������ʱ					 
			 }
			 else if(KeyStatus == OFF)                      //�������ɿ�ʱ
			 {				  
				  OUTPUT_OFF;                                 //�����
			    if(LedDelayCnt == 0)                        //�����Ϲرհ�������ʱ���״̬
					{                      
						 LedStatus = KEY_RELEASE_LED_IN; 
						 sysStatus=0;
					}
			 }
		 }
}
