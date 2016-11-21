#include<C8051F300.H>
//============================================================================================================
// �������¶���
typedef unsigned char  		BOOLEAN;
typedef unsigned char  		INT8U;              /* Unsigned  8 bit quantity           */
typedef signed   char  		INT8S;              /* Signed    8 bit quantity           */
typedef unsigned int		INT16U;             /* Unsigned 16 bit quantity           */
typedef signed   int 		INT16S;          	/* Signed   16 bit quantity           */
typedef unsigned long int   INT32U;          	/* Unsigned 32 bit quantity           */
typedef signed   long int   INT32S;         	/* Signed   32 bit quantity           */
typedef float          		FP32;               /* Single precision floating point    */
typedef double         		FP64;               /* Double precision floating point    */

typedef INT16U   OS_STK;                  		/* Each stack entry is 32-bit wide                    */
typedef INT16U   OS_CPU_SR;                		/* Define size of CPU status register (PSR = 32 bits) */

//============================================================================================================
//	void OSCILLATOR_Init (void);		   // Configure the system clock
//	void PORT_Init (void);				   // Configure the Crossbar and GPIO
//	void Comparator0_Init (void);		   // Configure Comparator0
//	void Timer0_Init (void);
//	void ADC_Init (void);			
//	void Interrupt_Init(void);
//============================================================================================================
// IO�ڶ���
////	sbit FSOUT = P0^0;			//�������
////	sbit kOUT = P0^4;			//�������
////	sbit LEDOUT = P0^5;			//LED���
//	sbit FSOUT  = P0^2;			//��ⷢ�����
////	sbit kOUT   = P0^5;			//�������	PNP���
//	sbit pChkOC = P0^5;			//��ⳣ������	0=������1=����
//	sbit kOUT2  = P0^4;			//������� 	NPN���
//	sbit LEDOUT = P0^3;			//LED״̬�����

	sbit pEMILEDCTL  = P0^0;	//���ⷢ�����
	sbit pOUTPUT  = P0^5;			//������� 	NPN���
	sbit pINPUT   = P0^4;			//����
	sbit pLEDOUTG = P0^3;			//LED״̬�����
	sbit pLEDOUTB = P0^2;			//LED״̬�����
	sbit pLEDOUTR = P0^6;			//LED״̬�����

//	INT16U 	count1;
//	INT32U 	closetime;
	
//============================================================================================================
//��������																											  
//#define		WDVAL	  	0x2E	//0.6V		   �ȶ�
//#define		WDSSVAL	  	0x26	//0.5V		   ������˸
//#define		NOSSVAL	  	0x1E	//0.4V		   �е�����
//#define		NOVAL	  	0x19	//0.33V		   ���ź�

//#define		WDVAL	  0x40	//0x26	//0.5V		   �ȶ�
//#define		WDSSVAL	  0x2A	//0x1E	//0.4V		   ������˸
//#define		NOSSVAL	  0x20	//0X17	//0.3V		   �е�����
//#define		NOVAL	  0x1A	//0X11	//0.23V		   ���ź�										  //0X11


#define		WDVAL	  0xD0//0x40	//0x26	//0.5V		   �ȶ�
#define		WDSSVAL	  0x23//0x2A	//0x1E	//0.4V		   ������˸
#define		NOSSVAL	  0x20//0x20	//0X17	//0.3V		   �е�����
#define		NOVAL	  0x1A//0x1A	//0X11	//0.23V		   ���ź�										  //0X11

//#define		OVERCURVAL	70		//0.9V		   ���PNP�Ƿ����
//#define		BASEVAL		107		//1.43V		   ��׼��ѹֵ

#define 	TRUE		1		//��־����
#define 	FALSE		0		//��־�ļ�

#define 	ON			1		//IO�ڿ��ƵĿ��ع�,�͵�ƽ��
#define 	OFF			0		//IO�ڿ��ƵĿ��ع�,�ߵ�ƽ��

#define		FSLEDZKB	100//20	 	// ռ�ձȣ�1/12,10us һ��,12,20	
#define		PROSSCNT	10		// �ɼ����ٸ��㴦��һ��

#define		SAMPCNTMAX  50		// �ɼ�������
//========================================================================
/////////////////////////////////////////////////

//  ȫ�ֱ�������
	bit		f_OUT;			// ���״̬��־
	bit		f_FSLedOut;		// ���ⷢ�俪�ر�־�� TRUE  = ��
	bit		f_pross;		// �ߵͶ������ɼ���ɱ�־��TRUE ������
	bit		f_prossout;		// ����һ�������־���ɼ�һ���������ٴ���TRUE ������
	bit		f_shanshuo;		// ��˸��־	��	TRUE��˸

	INT8U	ledemicnt;		// ���ⷢ��ضϼ��ʱ��
	INT8U	out	;			// ��Ч�ڵ�����
//	INT8U	timinc;
	INT8U	buwendin;		// �ڵ��ٽ磬���ȶ�����
//	INT8U	occnt;
	INT8U	sampcnt;	    // ��������

	INT8U	RevBase;		// ��׼��ѹֵ
	INT8U	prosscnt;		// �������ڼ���
	INT8U  idata  sampDat[SAMPCNTMAX] ,difDat[SAMPCNTMAX],DsampDat[SAMPCNTMAX];

	INT16U 	count;		  	// ��10us���������650ms
	INT16U 	count1;		  	// ��10us���������650ms
	INT16U 	shanshuocishu;	// ��˸�仯ֵ,�����ض�ʱ��
//=========================================================================												
void delay(void)																								
{  
	INT8U i,j;
    for(i=30;i>0;i--)
	for(j=30;j>0;j--) ;
}

// ��ʱms
void delay_Xms( INT16U cnt)																							
{  

	while(cnt > 0)
	{
       delay();
	   cnt--;
	}
}
/////////////////////////////////////////////////
//void Comparator0_Init (void)
//{CPT0MD=2;//��Ӧʱ��320ns
//CPT0MX=0x11;//P0.2+  P0.3-
//CPT0CN=0x8C;//ʹ�ܱȽ�����0x8F�ز�20mV
//}
/////////////////////////////////////////////////
void Interrupt_Init (void)
{
	EA = 1; //�ж������ܿ���λ
}
/////////////////////////////////////////////////
void Timer0_Init (void)			 // 30us
{
	TR0 = 1;          //Timer0����,��TCON=0x10;
	ET0 = 1;          //T0����ж�����
 	//TH0 = (256-150);		//100US 
  TH0 = 0Xf0;			//10US  
 	TMOD = 2;			    //��ʱ��0 8bit�Զ���װ��
 	CKCON |= 0x01;		//4��Ƶ��  6/4
}
/////////////////////////////////////////////////
void ADC_Init (void)
{
//	AMX0SL = 0X80;//����P0.0,����GND
	AMX0SL = 0X81;//����P0.1,����GND
//	ADC0CF = 0x01;//ת��Ƶ��Ϊ6M��max����1������
	ADC0CF = 0x09;//ת��Ƶ��Ϊ3M��6M max����1������  ,1/2ϵͳʱ�� !!!

// 	ADC0CF = 0x11;//ת��Ƶ��Ϊϵͳʱ��1/2��1������
//	ADC0CF = 0x09;//ת��Ƶ��Ϊϵͳʱ��1/3��1������
//	ADC0CF = 0x19;//ת��Ƶ��Ϊ6M��max����1������
 	REF0CN = 0x0a;//VDD��Ϊ��ѹ��׼, ʹ���ڲ�ADC�ο���ѹ
 //	ADC0LT=0x40;//����70LSB����Ϊ����(��2R)
 	//EIE1=2;//����ADC���ڱȽ�ƥ���ж�
 	//EIP1=2;//ADC���ڱȽ�ƥ���ж�Ϊ�����ȼ�
// 	AD0EN=1;//ʹ��ADC


	ADC0CN 	= 0x80;			//ʹ��ADC0 �������������ٷ�ʽ ��AD0BUSYд1����AD
}

// ʹ���ڲ�����4��Ƶ
void OSCILLATOR_Init (void)
{   	
	INT8U	i;
	OSCICN   = 0x05;			//Ƶ��Ϊ24.5Mhz	/4
//	OSCICN   = 0x06;			//Ƶ��Ϊ24.5Mhz	/2
//	OSCICN   = 0x07;			//Ƶ��Ϊ24.5Mhz

	for(i = 50; i>0; i--);
	while((OSCICN & 0x10) == 0) ;		// �ж��Ƿ�������
}
/**************************************************************************************************
Port I/O initialization consists of the following steps:
Step 1. Select the input mode (analog or digital) for all Port pins, using the Port0 Input Mode
register (P0MDIN).
Step 2. Select the output mode (open-drain or push-pull) for all Port pins, using the Port0 Output
Mode register (P0MDOUT).
Step 3. Set XBR0 to skip any pins selected as analog inputs or special functions.
Step 4. Assign Port pins to desired peripherals.
Step 5. Enable the Crossbar.
***************************************************************************************************/
void PORT_Init (void)
{	 
//// 	 P0MDIN  = 0xFE;	// P0.0,Ϊģ������ 	0=ģ�����룬1=��������
//	P0MDIN  = 0xFD;	// P0.1,Ϊģ������ 	0=ģ�����룬1=��������
////	 P0MDOUT = 0x1C;	// P0.2,3,4Ϊ���������ʽ
//	P0MDOUT = 0x60;	// P0.0,2,3,5,6Ϊ���������ʽ	
////	 XBR0  	 = 0x01;	// ����P0.0
//  XBR0  	 = 0x02;	// ����P0.1	  ����ΪADC����
//	XBR2    = 0X40;	// ʹ�ܽ��濪�أ�ʹ��������
////	 P0 	 = 0x03;	// �����

//	// �ص������
//	pOUTPUT  	= OFF;																							 //
//	pLEDOUTB 	= ON;	
//	pLEDOUTG 	= OFF;	
//	pLEDOUTR 	= OFF;	
//	pEMILEDCTL  = OFF;			 // �ܹض�
	
	
	
	
  P0MDIN  &= ~0x02;    	// P0.1,Ϊģ������ 	0=ģ�����룬1=��������
	P0MDIN  |= ~0x10;     // P0.4 DIGITAL INPUT
	P0MDOUT |= 0x6d;	    // P0.0,2,3,5,6Ϊ���������ʽ	
  XBR0  	|= 0x3F;  	  // ����ʹ�õ�IO��P0.0 1 2 3 5 6 	
	XBR2    |= 0X40;	    // ʹ�ܽ��濪�أ�ʹ��������

  
	pOUTPUT  	= OFF;	 	  // �ص������
	pLEDOUTB 	= OFF;	
	pLEDOUTG 	= OFF;	
	pLEDOUTR 	= OFF;	
	pEMILEDCTL  = OFF;    // �ܹض�
}

/////////////////////////////////////////////////

// ADC �ɼ�
INT8U ADC_Samp (void)
{
	INT8U	tmp,dat;
	AD0INT  = 0;	//���ת����ɱ�־
	AD0BUSY = 1;	//����һ��ת��
	dat = 0;
//	for(tmp = 50;tmp > 0;tmp --)	   	// F300  2*nop + 19*3*nop + 2*nop = 61nop = 61*40ns*4=9.6us	 
	for(tmp = 100;tmp > 0;tmp --)	   	// F300  2*nop + 19*3*nop + 2*nop = 61nop = 61*40ns*4=9.6us
	{
		if( 1 == AD0INT )//��������ֵ�ض�һ��ʱ��
		{
			AD0INT = 0;
			AD0BUSY = 0;
			dat = 	ADC0;
			break;
		}								
	}
	return(dat);
}

/**************************************************************************************************
Timer0 10us�ж�һ�Σ�����ܿ�ͨʱ��Ϊ10us
***************************************************************************************************/

void Timer0(void) interrupt 1 				// 10us
{
	count++;					 // ��10us����
  count1++;
//	if(count1>50000)
//	{
//		 count1=0;
//		 pLEDOUTB ^= ON;
//  }	

		
	// ����ܴ�
	if(f_FSLedOut == TRUE)
	{			
		//sampDat[sampcnt] = ADC_Samp(); 	// �ɼ��߶�����	
		pEMILEDCTL  = OFF;		 // �ܹض�
		
		f_FSLedOut = FALSE;		 // �ܹض�״̬
		ledemicnt = FSLEDZKB;	 // �´ο�ͨʱ��
		
		if(sampcnt >= SAMPCNTMAX)
		{	sampcnt = 0; }
    
		
		
//		pEMILEDCTL  = OFF;		 // �ܹض�	 
	}							   
 	else
   	{
		// ����ܹرպ�10us�ɼ��Ͷ� 
		if(ledemicnt == FSLEDZKB)//�ж���û�м�⵽һ������			  
	    {
			if(sampcnt >= SAMPCNTMAX)
			{	sampcnt = 0; }

			DsampDat[sampcnt] = ADC_Samp(); 	// �ɼ��Ͷ�����
				
			sampcnt++;							// �ɼ��洢λ��+1
			f_pross = TRUE;						// 1�θߵͶ������ɼ���ɱ�־

			// �ɼ���һ���ĵ�����һ���ж�
			if(prosscnt++ >= PROSSCNT)
			{
			 	f_prossout = TRUE;			   // ����һ�������־
				prosscnt = 0;				   // ������0
			}	 	
		} 

	 	// �ص����ʱ�䵽���򿪷����
		if(0 == (ledemicnt--))
		{
			
			pEMILEDCTL = ON;			 // ����ܴ�
			f_FSLedOut = TRUE;		     // ����ܴ�״̬
			f_FSLedOut = TRUE;		     // ����ܴ�״̬;
      sampDat[sampcnt] = ADC_Samp(); 	// �ɼ��߶�����	
//			if(sampcnt >= SAMPCNTMAX)
//			{	sampcnt = 0; }
//
//			DsampDat[sampcnt] = ADC_Samp(); 	// �ɼ��Ͷ�����

		}
	}
}



/////////////////////////////////////////////////
void main(void)
{	
	PCA0MD &= ~0x40; 		    	   //���Ź���ʱ������ֹ
	RSTSRC |= 0x02;					   //ʹ��VDD��ѹ����
//	OSCILLATOR_Init();				   // Initialize the system clock
	PORT_Init ();					   // Initialize crossbar and GPIO
	
	// ����	
	pLEDOUTR = ON;	
	delay_Xms(500);	
	pLEDOUTR = OFF;	

	pLEDOUTG = ON;	
	delay_Xms(500);
	pLEDOUTG = OFF;
		
	pLEDOUTB = ON;	
	delay_Xms(500);	
	pLEDOUTB = OFF;
																				 
																				 																						 //
	Timer0_Init ();					   // Timer0 �Զ���װģʽ2
	ADC_Init ();					   // ����ADC
//	Comparator0_Init();				   // Initialize Comparator0
	OSCILLATOR_Init();				   // Initialize the system clock
//	Interrupt_Init ();						

	//  �ɼ���׼ֵ
	{
		INT8U	cnt,i;
		INT16U  sum = 0;	
		for(cnt = 128;cnt > 0;cnt-- )
		{ 
			sum += ADC_Samp(); 
			for(i = 50; i > 0; i--)	;	// ��ʱ
		}
		RevBase =  sum/128;
	}
//	RevBase =  111;

	PCA0CPL2 = 30;				// 33ms
	PCA0MD  |= 0x60; 		    // ���Ź���ʱ�������� ���������Ź�
		 
	out    = 0;	 				// �ڵ���Ч����
//	timinc = 0;	 
//	occnt  = 0;
	f_pross = FALSE;			// �������ɼ���ɱ��־
	Interrupt_Init ();			// ���ж�
	while(1)
	{
		INT8U  dat0,dat1,dif;
		
//		pEMILEDCTL  = ON;		 // �ܹض�
//		dat0 = ADC_Samp();
//		if(dat0>200)
//			 pLEDOUTG = ON;	
//		else
//			 pLEDOUTG = OFF;	
			
//		
   	PCA0CPH2 = 1;//ι��

		// ���һ�������ɼ����
		if( (f_pross == TRUE)&&(sampcnt > 0) )
		{
			 f_pross = FALSE;			 // �������ɼ���ɱ��־

			 // ��֤���鲻����
			 if(sampcnt >= SAMPCNTMAX)
			 {	sampcnt = SAMPCNTMAX; }

			 // �߶�-�Ͷ� ��������difDat[]
			 dat0 = sampDat[sampcnt-1];
			 dat1 = DsampDat[sampcnt-1];
			 
			 if(dat0 > dat1)
			 		{ dif = dat0 - dat1; }
			 else	{ dif = dat1 - dat0; }

			 difDat[sampcnt-1] = dif ;

			 // ȡ�߶˺͵Ͷ����ֵ��ֵ���Ĵ���dat0
			 if(dat0 > RevBase)
			 		{ dat0 = dat0 - RevBase; }
			 else	{ dat0 = RevBase - dat0; }

			 if(dat1 > RevBase)
			 		{ dat1 = dat1 - RevBase; }
			 else	{ dat1 = RevBase - dat1; }

			 if(dat0 < dat1) { dat0 = dat1 ; }

			 // �����ֵ�����ȶ�ֵ�����ߵ���-��ֵ�����ȶ�ֵһ���ж࣬��out+1��ȷ��Ϊ�ڵ�
			 if( (dif >= WDVAL)||(dat0 >= (WDVAL/2+5)) )
			 { out++; }
			 // �����ֵС�����ź�ֵ�����ҵ���-��ֵ�����ȶ�ֵһ���ж࣬��out-1��ȷ��Ϊ���ڵ�
			 else if((dif <= NOVAL)&&(dat0 <= NOVAL))
			 { if(out > 0)out--; }

			 // �����ֵ�����ڵ��ٽ�ֵ�����ߵ���-��ֵ�����ٽ�ֵһ���ж࣬��buwendin+1
			 if((dif >= WDSSVAL)||(dat0 >= (WDSSVAL/2+5)))
			 { buwendin++; }
			  // �����������Ҳ�ֵС�����ڵ��ٽ�ֵ���ҵ���-��ֵ�����ٽ�ֵһ���ж࣬��buwendin+1
			 else  if((f_OUT == FALSE)&&(dif <= NOSSVAL)&&(dat0 <= NOSSVAL))
			 { if(buwendin > 0)buwendin--; }

			 // ȷ��ȷ���ڵ����������ж�����
			 if( out > PROSSCNT )   
			 { out = PROSSCNT; }

			 // ȷ��ȷ�ϲ��ȶ����������ж�����
			 if( buwendin > PROSSCNT )   
			 { buwendin = PROSSCNT; }		
		}

		// ����һ�������־���ɼ�һ���������ٴ���ÿ2ms����һ��
		if(f_prossout == TRUE)
		{
			f_prossout = FALSE;		 // �崦��һ�������־

			f_shanshuo = FALSE;		 // ����˸��־

			// �ж��ڵ���Ч������û����ر����
			if(out <= 1)		//1
		   	{ 
		   		f_OUT = FALSE;			 // �������Ч��־
				pOUTPUT = OFF;			 // �����
			  	pLEDOUTG  = OFF; 	     // ��״ָ̬ʾ��
			} 
			// ���ڲɼ�һ������Ϊ��Ч
			else if(out > PROSSCNT/2)
		   	{
				f_OUT   = TRUE;			 // �������Ч��־
				pOUTPUT = ON;			 // �����
				pLEDOUTG  = ON;			 // ��״ָ̬ʾ��				
			}
		 	else if(buwendin > PROSSCNT/2)	//8
			{ 
				f_shanshuo = TRUE; 		// ����˸��־
				count = 0; 				// �����ʱ�� 
			}


			// LED״ָ̬ʾ����˸
		 	if(f_shanshuo == TRUE)
		 	{
		 		if(count >= 20000)
					{ pLEDOUTG = ON; }
				else{ pLEDOUTG = OFF;	}

				if( count >= 40000 )
				{	count = 0;   }
		 	}
		}
	} 
}
