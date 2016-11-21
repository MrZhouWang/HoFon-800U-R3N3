#define LED_GLOBAL
#include "include.h"
UINT8  KeyStatus = OFF;		//����״̬
INT8U LedStatus = LED_NONE;   //��״̬
INT16U  LedDelayCnt = 0;
//////////////////////////////////////////////////////////////////////////////////
//// �������� : ADC��ʼ��
//// ������� : 
//// ���ز��� : 
//// ˵��     :  
//////////////////////////////////////////////////////////////////////////////////
void led_blink(void)
{
	LED_R_ON ;
	delay_ms(1000);	
	LED_R_OFF ;	


	LED_G_ON ;	
	delay_ms(1000);
	LED_G_OFF ;
		
	LED_B_ON;	
	delay_ms(1000);	
	LED_G_OFF ;
}
//////////////////////////////////////////////////////////////////////////////////
//// �������� : IO��ʼ��
//// ������� : 
//// ���ز��� : 
//// ˵��     :  
//////////////////////////////////////////////////////////////////////////////////
void PORT_Init (void)
{	
	P0MDIN  &= ~0x02;    	// P0.1,Ϊģ������ 	0=ģ�����룬1=��������
	P0MDIN  |= 0x10;      // P0.4 DIGITAL INPUT
	P0MDOUT |= 0x28;	    // P0.3,5,Ϊ���������ʽ	
	P0MDOUT &= ~(0x45);	  // P0.1,2,6ΪOpen Drain�����ʽ	
  XBR0  	|= 0x3F;  	  // ����ʹ�õ�IO��P0.0 1 2 3 5 6 	
	XBR2    |= 0X40;	    // ʹ�ܽ��濪�أ�ʹ��������

  
	pOUTPUT  	= OFF;	 	  // �ص����
  LED_G_OFF ;   
  LED_B_OFF ;
  LED_R_OFF ;
	   
	pEMILEDCTL = OFF;     //����ܹض�
}
//////////////////////////////////////////////////////////////////////////////////
//// �������� : led����
//// ������� : 
//// ���ز��� : 
//// ˵��     :  
//////////////////////////////////////////////////////////////////////////////////
void led_light_ctrl(INT8U leds)
{
	switch (leds)
	{
		case LED_RED:  		LED_G_OFF; LED_B_OFF;  LED_R_ON;  break;		
		case LED_GREEN:		LED_R_OFF; LED_B_OFF;  LED_G_ON;  break;
		case LED_BLUE:		LED_R_OFF; LED_G_OFF;  LED_B_ON;  break;
		
		case LED_RG:  		LED_B_OFF; LED_R_ON;   LED_G_ON;  break;		
		case LED_RB:		  LED_G_OFF; LED_R_ON;   LED_B_ON;  break;
		case LED_GB:		  LED_R_OFF; LED_G_ON;   LED_B_ON;  break;
		case LED_RGB:		  LED_R_ON;  LED_G_ON;   LED_B_ON;  break;			
		default:			    LED_R_OFF; LED_G_OFF; LED_B_OFF;  break;
	}
}
//////////////////////////////////////////////////////////////////////////////////
//// �������� : led��˸����
//// ������� : 
//// ���ز��� : 
//// ˵��     :  
//////////////////////////////////////////////////////////////////////////////////
void CMD_led_flash(void)
{
	if(LedStatus != LED_NONE)
  {

			led_light_ctrl(LedStatus);			// ��������Ӧ��ɫ

	}
	else//��ǰ����ʾ
	{
		led_light_ctrl(LED_NONE);	
	}
}

