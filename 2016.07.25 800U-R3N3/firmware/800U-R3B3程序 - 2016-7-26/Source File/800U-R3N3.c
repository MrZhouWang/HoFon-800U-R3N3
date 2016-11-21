#include<C8051F300.H>
//============================================================================================================
// 类型重新定义
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
// IO口定义
////	sbit FSOUT = P0^0;			//发射输出
////	sbit kOUT = P0^4;			//开关输出
////	sbit LEDOUT = P0^5;			//LED输出
//	sbit FSOUT  = P0^2;			//红光发射输出
////	sbit kOUT   = P0^5;			//开关输出	PNP输出
//	sbit pChkOC = P0^5;			//检测常开常闭	0=常开，1=常闭
//	sbit kOUT2  = P0^4;			//开关输出 	NPN输出
//	sbit LEDOUT = P0^3;			//LED状态灯输出

	sbit pEMILEDCTL  = P0^0;	//红外发射输出
	sbit pOUTPUT  = P0^5;			//开关输出 	NPN输出
	sbit pINPUT   = P0^4;			//输入
	sbit pLEDOUTG = P0^3;			//LED状态灯输出
	sbit pLEDOUTB = P0^2;			//LED状态灯输出
	sbit pLEDOUTR = P0^6;			//LED状态灯输出

//	INT16U 	count1;
//	INT32U 	closetime;
	
//============================================================================================================
//常量定义																											  
//#define		WDVAL	  	0x2E	//0.6V		   稳定
//#define		WDSSVAL	  	0x26	//0.5V		   持续闪烁
//#define		NOSSVAL	  	0x1E	//0.4V		   有挡就无
//#define		NOVAL	  	0x19	//0.33V		   无信号

//#define		WDVAL	  0x40	//0x26	//0.5V		   稳定
//#define		WDSSVAL	  0x2A	//0x1E	//0.4V		   持续闪烁
//#define		NOSSVAL	  0x20	//0X17	//0.3V		   有挡就无
//#define		NOVAL	  0x1A	//0X11	//0.23V		   无信号										  //0X11


#define		WDVAL	  0xD0//0x40	//0x26	//0.5V		   稳定
#define		WDSSVAL	  0x23//0x2A	//0x1E	//0.4V		   持续闪烁
#define		NOSSVAL	  0x20//0x20	//0X17	//0.3V		   有挡就无
#define		NOVAL	  0x1A//0x1A	//0X11	//0.23V		   无信号										  //0X11

//#define		OVERCURVAL	70		//0.9V		   检测PNP是否过流
//#define		BASEVAL		107		//1.43V		   基准电压值

#define 	TRUE		1		//标志的真
#define 	FALSE		0		//标志的假

#define 	ON			1		//IO口控制的开关管,低电平开
#define 	OFF			0		//IO口控制的开关管,高电平关

#define		FSLEDZKB	100//20	 	// 占空比，1/12,10us 一次,12,20	
#define		PROSSCNT	10		// 采集多少个点处理一次

#define		SAMPCNTMAX  50		// 采集最大点数
//========================================================================
/////////////////////////////////////////////////

//  全局变量定义
	bit		f_OUT;			// 输出状态标志
	bit		f_FSLedOut;		// 红外发射开关标志， TRUE  = 打开
	bit		f_pross;		// 高低端完整采集完成标志，TRUE 待处理
	bit		f_prossout;		// 处理一次输出标志，采集一定脉冲数再处理，TRUE 待处理
	bit		f_shanshuo;		// 闪烁标志	，	TRUE闪烁

	INT8U	ledemicnt;		// 红外发射关断间隔时间
	INT8U	out	;			// 有效遮挡次数
//	INT8U	timinc;
	INT8U	buwendin;		// 遮挡临界，不稳定次数
//	INT8U	occnt;
	INT8U	sampcnt;	    // 采样点数

	INT8U	RevBase;		// 基准电压值
	INT8U	prosscnt;		// 发射周期计数
	INT8U  idata  sampDat[SAMPCNTMAX] ,difDat[SAMPCNTMAX],DsampDat[SAMPCNTMAX];

	INT16U 	count;		  	// 对10us计数，最大650ms
	INT16U 	count1;		  	// 对10us计数，最大650ms
	INT16U 	shanshuocishu;	// 闪烁变化值,过流关断时间
//=========================================================================												
void delay(void)																								
{  
	INT8U i,j;
    for(i=30;i>0;i--)
	for(j=30;j>0;j--) ;
}

// 延时ms
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
//{CPT0MD=2;//反应时间320ns
//CPT0MX=0x11;//P0.2+  P0.3-
//CPT0CN=0x8C;//使能比较器，0x8F回差20mV
//}
/////////////////////////////////////////////////
void Interrupt_Init (void)
{
	EA = 1; //中断允许总控制位
}
/////////////////////////////////////////////////
void Timer0_Init (void)			 // 30us
{
	TR0 = 1;          //Timer0启动,即TCON=0x10;
	ET0 = 1;          //T0溢出中断允许
 	//TH0 = (256-150);		//100US 
  TH0 = 0Xf0;			//10US  
 	TMOD = 2;			    //定时器0 8bit自动重装载
 	CKCON |= 0x01;		//4分频率  6/4
}
/////////////////////////////////////////////////
void ADC_Init (void)
{
//	AMX0SL = 0X80;//正端P0.0,负端GND
	AMX0SL = 0X81;//正端P0.1,负端GND
//	ADC0CF = 0x01;//转换频率为6M（max），1倍增益
	ADC0CF = 0x09;//转换频率为3M（6M max），1倍增益  ,1/2系统时钟 !!!

// 	ADC0CF = 0x11;//转换频率为系统时钟1/2，1倍增益
//	ADC0CF = 0x09;//转换频率为系统时钟1/3，1倍增益
//	ADC0CF = 0x19;//转换频率为6M（max），1倍增益
 	REF0CN = 0x0a;//VDD作为电压基准, 使能内部ADC参考电压
 //	ADC0LT=0x40;//超过70LSB就认为过流(串2R)
 	//EIE1=2;//允许ADC窗口比较匹配中断
 	//EIP1=2;//ADC窗口比较匹配中断为高优先级
// 	AD0EN=1;//使能ADC


	ADC0CN 	= 0x80;			//使能ADC0 工作于连续跟踪方式 向AD0BUSY写1启动AD
}

// 使用内部晶振，4分频
void OSCILLATOR_Init (void)
{   	
	INT8U	i;
	OSCICN   = 0x05;			//频率为24.5Mhz	/4
//	OSCICN   = 0x06;			//频率为24.5Mhz	/2
//	OSCICN   = 0x07;			//频率为24.5Mhz

	for(i = 50; i>0; i--);
	while((OSCICN & 0x10) == 0) ;		// 判断是否正常振荡
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
//// 	 P0MDIN  = 0xFE;	// P0.0,为模拟输入 	0=模拟输入，1=数字输入
//	P0MDIN  = 0xFD;	// P0.1,为模拟输入 	0=模拟输入，1=数字输入
////	 P0MDOUT = 0x1C;	// P0.2,3,4为推挽输出方式
//	P0MDOUT = 0x60;	// P0.0,2,3,5,6为推挽输出方式	
////	 XBR0  	 = 0x01;	// 跳过P0.0
//  XBR0  	 = 0x02;	// 跳过P0.1	  ，作为ADC输入
//	XBR2    = 0X40;	// 使能交叉开关，使能弱上拉
////	 P0 	 = 0x03;	// 关输出

//	// 关掉发射管
//	pOUTPUT  	= OFF;																							 //
//	pLEDOUTB 	= ON;	
//	pLEDOUTG 	= OFF;	
//	pLEDOUTR 	= OFF;	
//	pEMILEDCTL  = OFF;			 // 管关断
	
	
	
	
  P0MDIN  &= ~0x02;    	// P0.1,为模拟输入 	0=模拟输入，1=数字输入
	P0MDIN  |= ~0x10;     // P0.4 DIGITAL INPUT
	P0MDOUT |= 0x6d;	    // P0.0,2,3,5,6为推挽输出方式	
  XBR0  	|= 0x3F;  	  // 跳过使用的IO口P0.0 1 2 3 5 6 	
	XBR2    |= 0X40;	    // 使能交叉开关，使能弱上拉

  
	pOUTPUT  	= OFF;	 	  // 关掉发射管
	pLEDOUTB 	= OFF;	
	pLEDOUTG 	= OFF;	
	pLEDOUTR 	= OFF;	
	pEMILEDCTL  = OFF;    // 管关断
}

/////////////////////////////////////////////////

// ADC 采集
INT8U ADC_Samp (void)
{
	INT8U	tmp,dat;
	AD0INT  = 0;	//清除转换完成标志
	AD0BUSY = 1;	//启动一次转换
	dat = 0;
//	for(tmp = 50;tmp > 0;tmp --)	   	// F300  2*nop + 19*3*nop + 2*nop = 61nop = 61*40ns*4=9.6us	 
	for(tmp = 100;tmp > 0;tmp --)	   	// F300  2*nop + 19*3*nop + 2*nop = 61nop = 61*40ns*4=9.6us
	{
		if( 1 == AD0INT )//超过限流值关断一段时间
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
Timer0 10us中断一次，发射管开通时间为10us
***************************************************************************************************/

void Timer0(void) interrupt 1 				// 10us
{
	count++;					 // 对10us计数
  count1++;
//	if(count1>50000)
//	{
//		 count1=0;
//		 pLEDOUTB ^= ON;
//  }	

		
	// 发射管打开
	if(f_FSLedOut == TRUE)
	{			
		//sampDat[sampcnt] = ADC_Samp(); 	// 采集高端数据	
		pEMILEDCTL  = OFF;		 // 管关断
		
		f_FSLedOut = FALSE;		 // 管关断状态
		ledemicnt = FSLEDZKB;	 // 下次开通时间
		
		if(sampcnt >= SAMPCNTMAX)
		{	sampcnt = 0; }
    
		
		
//		pEMILEDCTL  = OFF;		 // 管关断	 
	}							   
 	else
   	{
		// 发射管关闭后10us采集低端 
		if(ledemicnt == FSLEDZKB)//判断有没有检测到一个脉冲			  
	    {
			if(sampcnt >= SAMPCNTMAX)
			{	sampcnt = 0; }

			DsampDat[sampcnt] = ADC_Samp(); 	// 采集低端数据
				
			sampcnt++;							// 采集存储位置+1
			f_pross = TRUE;						// 1次高低端完整采集完成标志

			// 采集够一定的点数做一次判断
			if(prosscnt++ >= PROSSCNT)
			{
			 	f_prossout = TRUE;			   // 处理一次输出标志
				prosscnt = 0;				   // 计数清0
			}	 	
		} 

	 	// 关掉间隔时间到，打开发射管
		if(0 == (ledemicnt--))
		{
			
			pEMILEDCTL = ON;			 // 发射管打开
			f_FSLedOut = TRUE;		     // 发射管打开状态
			f_FSLedOut = TRUE;		     // 发射管打开状态;
      sampDat[sampcnt] = ADC_Samp(); 	// 采集高端数据	
//			if(sampcnt >= SAMPCNTMAX)
//			{	sampcnt = 0; }
//
//			DsampDat[sampcnt] = ADC_Samp(); 	// 采集低端数据

		}
	}
}



/////////////////////////////////////////////////
void main(void)
{	
	PCA0MD &= ~0x40; 		    	   //看门狗定时器被禁止
	RSTSRC |= 0x02;					   //使能VDD电压监视
//	OSCILLATOR_Init();				   // Initialize the system clock
	PORT_Init ();					   // Initialize crossbar and GPIO
	
	// 开灯	
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
	Timer0_Init ();					   // Timer0 自动重装模式2
	ADC_Init ();					   // 设置ADC
//	Comparator0_Init();				   // Initialize Comparator0
	OSCILLATOR_Init();				   // Initialize the system clock
//	Interrupt_Init ();						

	//  采集基准值
	{
		INT8U	cnt,i;
		INT16U  sum = 0;	
		for(cnt = 128;cnt > 0;cnt-- )
		{ 
			sum += ADC_Samp(); 
			for(i = 50; i > 0; i--)	;	// 延时
		}
		RevBase =  sum/128;
	}
//	RevBase =  111;

	PCA0CPL2 = 30;				// 33ms
	PCA0MD  |= 0x60; 		    // 看门狗定时器被启用 ，锁定看门狗
		 
	out    = 0;	 				// 遮挡有效个数
//	timinc = 0;	 
//	occnt  = 0;
	f_pross = FALSE;			// 清完整采集完成标标志
	Interrupt_Init ();			// 开中断
	while(1)
	{
		INT8U  dat0,dat1,dif;
		
//		pEMILEDCTL  = ON;		 // 管关断
//		dat0 = ADC_Samp();
//		if(dat0>200)
//			 pLEDOUTG = ON;	
//		else
//			 pLEDOUTG = OFF;	
			
//		
   	PCA0CPH2 = 1;//喂狗

		// 如果一次完整采集完成
		if( (f_pross == TRUE)&&(sampcnt > 0) )
		{
			 f_pross = FALSE;			 // 清完整采集完成标标志

			 // 保证数组不超界
			 if(sampcnt >= SAMPCNTMAX)
			 {	sampcnt = SAMPCNTMAX; }

			 // 高端-低端 ，保存入difDat[]
			 dat0 = sampDat[sampcnt-1];
			 dat1 = DsampDat[sampcnt-1];
			 
			 if(dat0 > dat1)
			 		{ dif = dat0 - dat1; }
			 else	{ dif = dat1 - dat0; }

			 difDat[sampcnt-1] = dif ;

			 // 取高端和低端与均值差值最大的存入dat0
			 if(dat0 > RevBase)
			 		{ dat0 = dat0 - RevBase; }
			 else	{ dat0 = RevBase - dat0; }

			 if(dat1 > RevBase)
			 		{ dat1 = dat1 - RevBase; }
			 else	{ dat1 = RevBase - dat1; }

			 if(dat0 < dat1) { dat0 = dat1 ; }

			 // 如果差值大于稳定值，或者单端-均值大于稳定值一半有多，则out+1，确认为遮挡
			 if( (dif >= WDVAL)||(dat0 >= (WDVAL/2+5)) )
			 { out++; }
			 // 如果差值小于无信号值，而且单端-均值大于稳定值一半有多，则out-1，确认为无遮挡
			 else if((dif <= NOVAL)&&(dat0 <= NOVAL))
			 { if(out > 0)out--; }

			 // 如果差值大于遮挡临界值，或者单端-均值大于临界值一半有多，则buwendin+1
			 if((dif >= WDSSVAL)||(dat0 >= (WDSSVAL/2+5)))
			 { buwendin++; }
			  // 如果无输出，且差值小于无遮挡临界值，且单端-均值大于临界值一半有多，则buwendin+1
			 else  if((f_OUT == FALSE)&&(dif <= NOSSVAL)&&(dat0 <= NOSSVAL))
			 { if(buwendin > 0)buwendin--; }

			 // 确保确认遮挡个数不超判断条件
			 if( out > PROSSCNT )   
			 { out = PROSSCNT; }

			 // 确保确认不稳定个数不超判断条件
			 if( buwendin > PROSSCNT )   
			 { buwendin = PROSSCNT; }		
		}

		// 处理一次输出标志，采集一定脉冲数再处理，每2ms处理一次
		if(f_prossout == TRUE)
		{
			f_prossout = FALSE;		 // 清处理一次输出标志

			f_shanshuo = FALSE;		 // 清闪烁标志

			// 判断遮挡有效次数，没有则关闭输出
			if(out <= 1)		//1
		   	{ 
		   		f_OUT = FALSE;			 // 清输出有效标志
				pOUTPUT = OFF;			 // 关输出
			  	pLEDOUTG  = OFF; 	     // 关状态指示灯
			} 
			// 大于采集一半则认为有效
			else if(out > PROSSCNT/2)
		   	{
				f_OUT   = TRUE;			 // 置输出有效标志
				pOUTPUT = ON;			 // 开输出
				pLEDOUTG  = ON;			 // 开状态指示灯				
			}
		 	else if(buwendin > PROSSCNT/2)	//8
			{ 
				f_shanshuo = TRUE; 		// 置闪烁标志
				count = 0; 				// 清计数时间 
			}


			// LED状态指示灯闪烁
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
