#ifndef _LED_H_
#define _LED_H_
#include "include.h"

#ifdef LED_GLOBAL
#define EXT_LED
#else
#define EXT_LED extern
#endif


sbit pEMILEDCTL  = P0^3;	//���ⷢ�����
sbit pOUTPUT  = P0^5;			//������� 	NPN���
sbit pINPUT   = P0^4;			//����
sbit pLEDOUTG = P0^0;			//LED״̬�����
sbit pLEDOUTB = P0^2;			//LED״̬�����
sbit pLEDOUTR = P0^6;			//LED״̬�����




/***************��˸����***************************/
#define LED_FLASH_MODE_ALWAYS		0X00
#define LED_FLASH_MODE_1V1			0X01
#define LED_FLASH_MODE_1V2			0X02
#define LED_FLASH_MODE_1V5			0X03
#define LED_FLASH_MODE_1V10			0X04
#define LED_FLASH_MODE_2V1			0X05
#define LED_FLASH_MODE_5V1			0X06
#define LED_FLASH_MODE_10V1			0X07



EXT_LED volatile INT8U LedStatus ;        //LED״̬
EXT_LED volatile INT8U led_flash_NO;			//���鿪��״̬
EXT_LED volatile UINT8 led_flash_mode ;   //��˸����
EXT_LED volatile UINT8 KeyStatus;         //����״̬
EXT_LED volatile INT16U LedDelayCnt;       //������ʱ

sbit p_signal_input   = P0^4;             //�����ź�

#define LED_NONE	0
#define LED_RED		0x01
#define LED_GREEN	0x02
#define LED_BLUE	0x04

#define RG_YELLOW		0x08
#define RB_RED		  0x10                  //Ʒ��
#define GB_BLUE		  0x20                  //��
#define RGB_WHITE		0x40

#define LED_RG		0x08
#define LED_RB		0x10
#define LED_GB	  0x20
#define LED_RGB		0x40

#define LED_G_OFF (pLEDOUTG = 1)   
#define LED_B_OFF (pLEDOUTB = 1)
#define LED_R_OFF (pLEDOUTR = 1) 

#define LED_G_ON  (pLEDOUTG = 0)
#define LED_B_ON  (pLEDOUTB = 0)
#define LED_R_ON  (pLEDOUTR = 0)


#define OUTPUT_ON  (pOUTPUT = 1)
#define OUTPUT_OFF (pOUTPUT = 0)

#define KEY_PRESS_LED_NOIN    LED_GREEN	      //������ʱ��������ʱ״̬
#define KEY_RELEASE_LED_NOIN  LED_RED         //������ʱ�����ͷ�ʱ״̬

#define KEY_PRESS_LED_IN      RGB_WHITE		    //������ʱ��������ʱ״̬
#define KEY_RELEASE_LED_IN    LED_BLUE	      //������ʱ�����ͷ�ʱ״̬

//#define EN_SIGNAL_ON_LED      LED_BLUE	      //�������ź�
//#define DISEN_SIGNAL_ON_LED   LED_RED	//(~LED_GREEN)	  //�������ź�



extern void led_blink(void);
extern void PORT_Init (void);
extern void led_light_ctrl(INT8U leds);
extern void CMD_led_flash(void);
#endif

