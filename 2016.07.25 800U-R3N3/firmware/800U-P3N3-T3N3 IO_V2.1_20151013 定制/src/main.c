/*=========================================================
// �������˵��
//  2015��2��5�ո���  �汾v1.0
//	 1.��800U-T3N3 IB�Ļ������޸ģ�ȡ��485ͨ�Ź���
     2.����оƬΪCBM7008
//	 MCU:STC15W408AS   8K Flash  512RAM  EEPROM 5K 	  UART ����ɵ������� SOP16��װ��14��IO�ڣ�
         �ڴ�������ϵ縴λ��·

// ����˵��

����״̬��
�������ź�ʱ�����������ʱ�ְ����ذ�����������̵��������ź���������뿪���ذ������̵���������źš�

//  2015��8��5�ո���  �汾v1.1
	1.���800U-P3N3 IO �ͺţ�ͨ����main��h�ļ�ѡ����Ӧ���ͺŽ����������룬����Ŀ���ļ�


//  2015��8��24�ո���  �汾v2.0  	 GNN��G ��ʹ���̵��� N �а����޵��� N �����ɿ��޵�����
1.����˵��
����״̬�� 

     ʹ��     ����	    ��    ���
			
			 0		   ����		  ��	   ��
			 0		   �ɿ�		  ��	   ��
			 1		   �ɿ�		  ��	   ��
			 1		   ����		  ��	   ��

ʹ�ܣ�1 ʹ������   0 ��ʹ������



//  2015��9��8�ո���  �汾v2.1 	  	 ����800U T3N3 IO��800U P3N3 IO
1.����V2.0�汾�ļܹ���ͨ���������룬ʹ��ʱ������ɫ����������������ɫ���ɿ�������ɫ��ѡ����RGG GNN RGB GRN��

RGG ��R ��ʹ�ܺ���� G �а����̵��� G �����ɿ��̵�����
2.����״̬�� 

           ʹ��        ����	      ��      ���
			
			 0		   ����		  ��	   ��
			 0		   �ɿ�		  ��	   ��
			 1		   �ɿ�		  ��	   ��
			 1		   ����		  �̣���������	   

ʹ�ܣ�1 ʹ������   0 ��ʹ������


�ͻ�����5�ף�ʹ����������� ��������  �����������Ƶ� �ɿ���		20151218

=========================================================*/

#define AP_CPU_GLOBALS	
#include "extern_symbol.h" 

INT8U sysStatus = SYSTEM_INIT;	  //  0
INT8U LedStatus = NONE;
//INT8U p_mcu_flag = 0;    // �ź������־

UINT8  KeyStatus = 0;		//����״̬
UINT8  KeyStatus_flag = 0;		//����״̬��־
UINT8  LedDelayCnt = 0;		 //��ʱ������


/*******************************************************************************
	 					1�����ӳٺ���
*******************************************************************************/
void Delay1Ms() 
{
    UINT16 i = 852;
    while (i != 0) {i--;}
}

/*******************************************************************************
	 					�����ӳٺ���
    input   usDelay     �ӳ�ʱ��ֵ
	output  none
*******************************************************************************/

void DelayMs(UINT16 usDelay)
{
    for(; usDelay>0; usDelay--)
    {
        Delay1Ms();
    }   
}

/*******************************************************************************
	 					250uS�����ӳٺ���
*******************************************************************************/
// void Delay125Us() 
// {
//    UINT16 i = 426;
//  //    UINT16 i = 156;
//     while (i != 0) {i--;}
// }


void Timer0Init(void)		//50����@11.0592MHz
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0x00;		//���ö�ʱ��ģʽ
	TL0 = 0x00;		//��ʱ��ֵ
	TH0 = 0x4C;		//��ʱ��ֵ
	TF0 = 0;		//���IF0��־
    ET0 = 1;
	TR0 = 1;		//��ʱ��0��ʼ����
}


/*******************************************************************************
	 					 ���Ź���λ��������
*******************************************************************************/
void WDT_Reset(void)
{
	WDT_CONTR = WDT_CONTR & 0x0F;
}

/*******************************************************************************
	 					  �˿ڳ�ʼ��
*******************************************************************************/
void IO_Init(void)
{
	//������� PxM1��PxM0��Ӧ���0x00,0x10
	 P5M1 = 0x00;
	 P5M0 = 0x10;

	//��©���	PxM1��PxM0��Ӧ���11
	P3M1 = 0x0C;				   // SDA��SCL����ɿ�©��3.3V
	P3M0 = 0x0C;	

	P1M1 = 0x1C;				   // BLUE��RED��GREEN����ɿ�©��5V
	P1M0 = 0x1C;

	p_led_red = 1; 		
	p_led_green = 1;
	p_mcu_ctr = 1;
}

/***********************************************************
    				���ݱ�ſ��Ƶ�����
************************************************************/

void led_light_ctrl(INT8U status)
{
	
	switch(status)
	{
	 case RED:	
	 			p_led_red   = LED_ON;	  //�����
				p_led_green = LED_OFF;	  //�̵���
				p_led_blue  = LED_OFF;	  //������
				break;
	 case GREEN: 
	 			p_led_green = LED_ON;	  //�̵���
				p_led_red   = LED_OFF;	  //�����
				p_led_blue  = LED_OFF;	  //������
				break;
	
	 case BLUE: 
	 			p_led_blue  = LED_ON;	  //������
				p_led_red   = LED_OFF;	  //�����
				p_led_green = LED_OFF;	  //�̵���
				break;	

	 case RG_YELLOW:					  //�ϳɻ�ɫ
	 			p_led_red   = LED_ON;	  //�����
				p_led_green = LED_ON;	  //�̵���
				p_led_blue  = LED_OFF;	  //������
				break;
	 case RB_GREEN: 
	 			p_led_green = LED_ON;	  //�̵���
				p_led_red   = LED_ON;	  //�����
				p_led_blue  = LED_OFF;	  //������
				break;
	
	 case GB_BLUE: 
	 			p_led_blue  = LED_ON;	  //������
				p_led_red   = LED_OFF;	  //�����
				p_led_green = LED_ON;	  //�̵���
				break;

	 case RGB_WHITE: 
	 			p_led_blue  = LED_ON;	  //������
				p_led_red   = LED_ON;	  //�����
				p_led_green = LED_ON;	  //�̵���
				break;

	 default:
	 			p_led_red   = LED_OFF;	  //�����
				p_led_green = LED_OFF;	  //�̵���
				p_led_blue  = LED_OFF;	  //������
	}
}


/***********************************************************
    				singal_output 
************************************************************/
//void singal_output(void)

void KeyCheck(void)
{
//	UINT8  KeyStatus = 0;
	#if	 (MACHINETYPE == T3N3_800U)
	    if (Scan_Val()==1)                                          //�а���	
	    {        
			KeyStatus = 1;										//����״̬��1	        
	    } 

	    if (Scan_Val()!=1)
	    {   
		    KeyStatus = 0;
	    } 

	#elif  (MACHINETYPE == P3N3_800U)
	    if (p_KEY_OK == 0)                                          //�а���	
	    {        
			KeyStatus = 1;	 
			KeyStatus_flag = 1;       								//	����״̬��־��1
	    } 
		    
	    if (p_KEY_OK != 0)
	    {   
		   	KeyStatus = 0;
			if (KeyStatus_flag == 1)  
			{
				 KeyStatus_flag = 0;
				 LedDelayCnt = 50;
			}
	    } 
		
	#endif
}

/***********************************************************
    				              T0�ж�
************************************************************/
void T0_int (void) interrupt 1
{
	EA = 0;		              //��ʱ��0��ʼ����	
    WDT_CONTR = 0x30;         //ι��		
    EA = 1;
}

/*******************************************************************************
	 						main program				
*******************************************************************************/   
int main(void) 
{   
	INT8U sysStatus = 0;
	IO_Init();
    WDT_Reset();
	DelayMs(300);														   // �ȴ���Դ�ȶ�

	#if	 (MACHINETYPE == T3N3_800U)    		                                
		CBM7008_init();	
	#endif
															// ���뿪����200ms������������	
	Timer0Init();			                                
	EA = 1;
	while(1)
	{	
		KeyCheck();     
//		test = ~test;
        DelayMs(10);
	
		//�������ʹ�ܿ���
		if (p_signal_input == 1)									   //��ʹ������
		{
		   //��ʹ������
		  if( LedDelayCnt != 0 )
			{ LedDelayCnt--; }
			else
			{
				led_light_ctrl(NONE);									   //��ȫ��
				LedStatus = NONE;
			}

			if (KeyStatus == 1)
			{
				 LedStatus = KEY_PRESS_LED;						              ///////
			}
			sysStatus = 0;											   // ��ʹ��
			
		}
		else                        								   //��ʹ������
		{
			//��ʹ������

		   	LedStatus = EN_SIGNAL_ON_LED;					 //ʹ�ܶ�Ӧ��ɫ
				
			if (KeyStatus == 1)  
			{	//�а���
				LedStatus = KEY_PRESS_LED;					//�������µ�ɫ
				sysStatus = 1;								//��һ�ΰ���
			}
			else  if(sysStatus == 1)
		    {	//�ް���
				if( LedDelayCnt != 0 )
				{ 
					LedDelayCnt--;
					LedStatus = KEY_PRESS_LED;
				}					                         //�������µ�ɫ }
				else  if (KeyStatus_flag == 1)
				{				
					LedStatus = KEY_RELEASE_LED;				//	�������µ�ɫ
				}
				else
				{
					 LedStatus =  EN_SIGNAL_ON_LED;
				}
			}
		   	//��ʹ������²����
		    if (LedStatus == NONE)
			{
				LedStatus = EN_SIGNAL_ON_LED;
			}
										
		 }

		 led_light_ctrl(LedStatus);

		// 24V����ɰ�������
		if (KeyStatus == 1)                                          //�а���	
		{        
		   p_mcu_ctr = 0;       									//24V�ź���� 
		// Delay250Us();
		   DelayMs(1);
		  if (p_singal_out == 1)                                  //�����ź��쳣
		  {    
		    p_mcu_ctr = 1;                                       //�ر����    0 �ر�							        
		  }
		}
		else //if(KeyStatus == 0)
		{
			p_mcu_ctr = 1;
		}
	}
}			
