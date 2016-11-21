	#include "extern_symbol.h"	
//IIC总线模拟实现文件
#if	 (MACHINETYPE == T3N3_800U)

	#include "CBM7008.h" 
 
/************************************************************************
** 功能描述：循环延时　Delay1us*tim 
************************************************************************/
void delay_us(INT16U us)
{
 //  	while (--us > 1);
// 		while (--us > 10);
//	while (--us > 0);
//	INT16U	j;
	for (; us > 0; us--)
//	{	for(j=0;j<8;j++);    }
	{	_nop_();  _nop_(); _nop_();  }
}

/************************************************************************
** 功能描述：START Data Transfer
 	A high-to-low transition of SDA with SCL high is a start condition
which must precede any other command

* Not Busy Stutas: scl = 1; scl = 1;
************************************************************************/

void iic_start(void)
{
	SETSDA();       //需在SCL之前设定
	delay_us(5);    //延时至少4.7us
	SETSCL();       //硬件进入SDA检测状态
	delay_us(5);    //延时至少4.7us
	RESETSDA();     //SDA由1->0,产生开始信号
	delay_us(5);    //延时至少4us
	RESETSCL();     //SCL变为无效
}
/************************************************************************
** 功能描述： Stop Data Transfer
	A low-to-high transition of SDA with SCL high is a stop condition.

* Not Busy Stutas: scl = 1; scl = 1;
************************************************************************/

void iic_stop(void)
{
//    RESETSCL();
//	delay_us(5);    //至少延时4us
	RESETSDA();     //在SCL之前拉低
	delay_us(5);    //至少延时4us
    SETSCL();       //硬件进入SDA检测状态
    delay_us(5);    //至少延时4us
    SETSDA();       //SDA由0->1,产生结束信号
    delay_us(5);    //延时至少4.7us
}

///************************************************************************
//** 功能描述：由主向从发送应答码
//** 输入参数: 0-ACK,1-NAK		             
//** 输出参数: 无
//** 时序: SCL下降沿输出数据,数据改变必须在SCL低电平时
//		      
//** data change at scl = 0;;
//************************************************************************/
//
//void iic_send_ack(bit ack)
//{
//    SDA = ack;      //产生应答电平
//    SCL = 1;        //发送应答信号
//    delay_us(5);    //延时至少4us
//    SCL = 0;        //整个期间保持应答信号
//}
///************************************************************************
//** 功能描述：取得由从到主的应答码
//** 输入参数: 无	             
//** 输出参数: 0-ACK,1-NAK
//** 时序: SCL下降沿输出数据,数据改变必须在SCL低电平时
//		       
//** data change at scl = 0;;
//************************************************************************/
//
//bit iic_get_ack(void)
//{
//    bit ret;        //用来接收返回值
//    SDA = 1;        //电阻上拉,进入读(8051)
//    SCL = 1;        //进入应答检测
//    delay_us(5);    //至少延时4us
//    ret = SDA;      //保存应答信号
//    SCL = 0;
//    return ret;
//}
/************************************************************************
** 功能描述：写IIC总线写1个字节 
** 输入参数: 8位数据dat		             
** 输出参数: 无
** 时序: SCL上升沿传送数据,数据改变必须在SCL低电平时
		 SCL 9个上升沿 其中8个为传送数据, 第9个为检测应答信号用        
** 检测应答信号,并作10ms的超时保护
** data change at scl = 0;
************************************************************************/

INT8U iic_write_byte(INT8U dat)
{
 	INT8U i;
	INT8U flg;

	for(i = 8; i > 0; i--)			// 这样写就会用djnz指令
	{				
		RESETSCL(); delay_us(2);
		
		//编译器漏洞：加括号，确保 & 运算在 == 之前
		if((dat  & 0x80) == 0x80) 
			{ SETSDA(); }
		else{ RESETSDA(); }
		dat <<= 1;delay_us(3);
		SETSCL(); delay_us(5);	
	}
	
	//检测应答信号
	//ACKNOWLEDGE：写数据时，应答信号由24LCXX发出 
	RESETSCL();delay_us(4);
	SETSDA();  delay_us(1);
	SETSCL();  delay_us(5);
	
	//While the SCL is high,then ADDRESS OR ACKNOWLEDGE VALID
	flg = FALSE;
	for(i = 200; i > 0; i--)	//这样写就会用djnz指令
	{						
		if(READSDABIT() == 0)
		{flg = TRUE; break;}			//Acknowledge Succ
		else{ delay_us(250); }			//250us
	}
	
	RESETSCL();delay_us(3);
	SETSDA();//Delay1us(2);

	return(flg);						//Acknowledge Err
}
/************************************************************************
** 功能描述：从IIC总线读取1个字节 
** 输入参数: ack = 1 则回发应答位0，否则发应答位1		             
** 输出参数: 返回8位数据
** 时序: SCL高电平输出数据,数据改变必须在SCL低电平时
		 SCL 8个下降沿       
** data change at scl = 0;;
************************************************************************/

INT8U iic_read_byte(INT8U ack)
{	
	INT8U i,dat = 0;
		
	RESETSCL();delay_us(4);
	SETSDA();  delay_us(1);		//写1，做为输入 防止钳位
	
	for(i = 8; i > 0; i--)
	{			//这样写就会用djnz指令
		SETSCL(); delay_us(2);
		(0 != READSDABIT()) ? (dat = ((dat << 1) | 0x01)) 
				   : (dat = ((dat << 1) & 0xfe));
		delay_us(3) ;
		RESETSCL(); delay_us(5);
	}
	// 输出应答信号
	if(1 == ack)
		{ RESETSDA(); delay_us(2); }
	else{   SETSDA(); delay_us(2); }
	SETSCL(); delay_us(5);
	RESETSCL(); delay_us(3);
//	SETSDA(); 
	return(dat);		
}


/************************************************************************
** 功能描述：IIC总线写数据
** 输入参数: waddr 寄存器地址，	wdata 数据             
** 输出参数: 返回状态
** 时序:   S--Slave address+W~A--Mem Address~A--Data~A--P
S               开始条件
Slave address+W 设备地址与写bit“0”
A               应答bit
Mem Address     CBM70XX内存地址
Data            CBM70XX中数据
P               停止条件
************************************************************************/

//INT8U iic_write_data(INT8U waddr, INT8U wdata)
//{
//	iic_start();				// 起始条件
//	iic_write_byte(DEV_ADDR_W);	// 写设备地址,检测应答位
////	delay_us(5);			    // 延时
//
//	iic_write_byte(waddr);	 	// 写寄存器地址,检测应答位
////	delay_us(5);			   	// 延时
//
//	iic_write_byte(wdata);		// 写数据,检测应答位
////	delay_us(5);				// 延时
//	iic_stop();					// 结束条件
//	return 1;			  	
//}
/************************************************************************
** 功能描述：读IIC总线数据，标准模式，最后一数据无应答位，指示传送完毕
** 输入参数: raddr 寄存器地址           
** 输出参数:  无
** 时序: 	 S--Slave address+W~A--Mem Address~A--P--S--Slave address+R~A--Data1~A--DataN--P
S               开始条件
Slave address+W 设备地址与写bit“0”
A               应答bit
Mem Address     CBM70XX内存地址
Data            CBM70XX中数据
P               停止条件
Slave address+R 设备地址与读bit“1”

************************************************************************/
//INT8U iic_read_Ndata(INT8U raddr)
//{
//	INT8U temp;//,i;
//	iic_start();				// 起始条件
//	iic_write_byte(DEV_ADDR_W);	// 写设备地址(写)
////	delay_us(5);				// 延时
//	iic_write_byte(raddr);		// 写寄存器地址
////	delay_us(5);				// 延时
//	iic_stop();					// 结束条件
//	iic_start();				// 起始条件
//	iic_write_byte(DEV_ADDR_R);	// 设备地址(读)
////	delay_us(5);				// 延时
//
//	temp = iic_read_byte(0);	// 读数据，不回发应答位
//	iic_stop();					// 结束条件
//
//	return(temp);				// 返回读取数据
//}
/************************************************************************
** 功能描述：读IIC总线数据，快速模式，最后一数据无应答位，指示传送完毕
** 输入参数: raddr 寄存器地址  ，cnt 读的个数         
** 输出参数:  无
** 时序: 	 S--Slave address+R~A--Data1~A--DataN--P
S               开始条件
Slave address+R 设备地址与读bit“1”
A               应答bit
Data            CBM70XX中数据
P               停止条件

************************************************************************/
//INT8U iic_FastRead_Ndata(INT8U raddr)//,INT8U cnt)
//{
//	INT8U temp;//,i;
//	iic_start();				// 起始条件
////	iic_write_byte(WR_ADDR);	// 写设备地址(写)
////	delay_us(5);				// 延时
////	iic_write_byte(raddr);		// 写寄存器地址
////	delay_us(5);				// 延时
//
//	iic_write_byte(DEV_ADDR_R);	// 写设备地址(读)
////	delay_us(5);				// 延时
//
////	for(i = 0;i < cnt;i++)
////	{ 
////		Mpr121Rebur[i] = iic_read_byte(); 
////		if(i+1 >= cnt)
////			{ iic_send_ack(1);}		//无应答信号
////		else{ iic_send_ack(0);}		//有应答信号
////	}
//
//	temp = iic_read_byte(0);	// 读数据
//	iic_stop();					// 结束条件
//
//	return (temp);				// 返回读取数据
//}
/************************************************************************
** 功能描述：IO配置		  
************************************************************************/
void   CBM7008IO_Config(void)
{


	pSDA = 1;//	配置开漏


	pSCL = 1 ;	  //配置开漏

}
/************************************************************************
** 功能描述：复位24C08	  
************************************************************************/
//void Ini_CBM7008(void)
//{	
//	SETSCL()  ;Delay_us(10);
//	SETSDA()  ;Delay_us(10);
//}

/************************************************************************
** 功能描述：设置CBM7008灵敏度            
** 输出参数: 返回状态 ,
灵敏度顺序ADD，SUB，FUNC，>>,<<
lmd=25 	 ,ADD 和 SUB 和FUNC 用力按有响应
************************************************************************/

void Set_CBM7008_nLMD(void)
{
	INT8U	OkLmd;             //= para.str.CBM7008LMD;

	if( (OkLmd > MAX_CBM7008LMD)||(OkLmd < MIN_CBM7008LMD) )
	{ OkLmd = DEF_CBM7008LMD; }

	iic_start();				// 起始条件
	iic_write_byte(DEV_ADDR_W);	// 写设备地址,检测应答位
//	delay_us(5);			    // 延时

	iic_write_byte(MEM_ADDR_SET_NLMD);	 	// 写寄存器地址,检测应答位
//	delay_us(5);			   	// 延时

	iic_write_byte(48);		// 写KEY0灵敏度,检测应答位	  无按键
//	iic_write_byte(30);		// 写KEY1灵敏度,检测应答位	  无按键
//	iic_write_byte(32);		// 写KEY1灵敏度,检测应答位	  无按键
//	iic_write_byte(32);		// 写KEY1灵敏度,检测应答位	  OK键
	iic_write_byte(OkLmd);   // OK键
	iic_write_byte(48);		// 写KEY2灵敏度,检测应答位	  无按键
	iic_write_byte(48);		// 写KEY3灵敏度,检测应答位	  无按键
	iic_write_byte(48);		// 写KEY4灵敏度,检测应答位	  无按键
	iic_write_byte(48);		// 写KEY5灵敏度,检测应答位	  无按键
	iic_write_byte(48);		// 写KEY6灵敏度,检测应答位	  无按键
	iic_write_byte(48);		// 写KEY7灵敏度,检测应答位	  无按键
//	delay_us(5);				// 延时
	iic_stop();					// 结束条件			  	
}

/************************************************************************
** 功能描述：设置CBM7008灵敏度            
** 输出参数: 返回状态
************************************************************************/

//void Set_CBM7008_1LMD(INT8U ord,INT8U lmd)
//{
//	iic_start();				// 起始条件
//	iic_write_byte(DEV_ADDR_W);	// 写设备地址,检测应答位
////	delay_us(5);			    // 延时
//
//	iic_write_byte(MEM_ADDR_SET_1LMD);	 	// 写寄存器地址,检测应答位
////	delay_us(5);			   	// 延时
//
//	iic_write_byte(ord);		// 写KEY0灵敏度,检测应答位	  无按键
//	iic_write_byte(lmd);
//
////	delay_us(5);				// 延时
//	iic_stop();					// 结束条件			  	
//}
/************************************************************************
** 功能描述：读CBM7008 ID            
** 输出参数: 返回ID号
************************************************************************/

INT16U Get_CBM7008_ID(void)
{
	INT16U temp=0;//,i;
	iic_start();				// 起始条件
	iic_write_byte(DEV_ADDR_W);	// 写设备地址(写)
//	delay_us(5);				// 延时
	iic_write_byte(MEM_ADDR_GET_ID);		// 写寄存器地址
//	delay_us(5);				// 延时
	iic_stop();					// 结束条件
	iic_start();				// 起始条件
	iic_write_byte(DEV_ADDR_R);	// 设备地址(读)
//	delay_us(5);				// 延时

	temp = iic_read_byte(1)*256; //读数据，回发应答位 		CB
	temp += iic_read_byte(0);	// 读数据，不回发应答位

	iic_stop();					// 结束条件	
	return(temp);	  	
}

/************************************************************************
** 功能描述：读CBM7008 灵敏度            
** 输出参数: 返回ID号
************************************************************************/
//INT8U lmd[8];
void Get_CBM7008_nLMD(void)
{
//	INT8U lmd[8];//,i;
	iic_start();				// 起始条件
	iic_write_byte(DEV_ADDR_W);	// 写设备地址(写)
//	delay_us(5);				// 延时
	iic_write_byte(MEM_ADDR_GET_NLMD);		// 写寄存器地址
//	delay_us(5);				// 延时
	iic_stop();					// 结束条件
	iic_start();				// 起始条件
	iic_write_byte(DEV_ADDR_R);	// 设备地址(读)
//	delay_us(5);				// 延时

	lmd[0] =  iic_read_byte(1);
	lmd[1] =  iic_read_byte(1);
	lmd[2] =  iic_read_byte(1);
	lmd[3] =  iic_read_byte(1);
	lmd[4] =  iic_read_byte(1);
	lmd[5] =  iic_read_byte(1);
	lmd[6] =  iic_read_byte(1);
	lmd[7] =  iic_read_byte(0);

	iic_stop();					// 结束条件		  	
}

/************************************************************************
** 功能描述：读CBM7008 按键状态            
** 输出参数: 返回按键信息
************************************************************************/

INT8U Get_CBM7008_KeySts(void)
{
	INT8U	chksum,keysts;
	iic_start();				// 起始条件
	iic_write_byte(DEV_ADDR_W);	// 写设备地址(写)
//	delay_us(5);				// 延时
	iic_write_byte(MEM_ADDR_GET_KEYSTS);		// 写寄存器地址
//	delay_us(5);				// 延时
	iic_stop();					// 结束条件
	iic_start();				// 起始条件
	iic_write_byte(DEV_ADDR_R);	// 设备地址(读)
//	delay_us(5);				// 延时

	keysts = iic_read_byte(1);	// 读按键状态
	chksum = iic_read_byte(0);	// 读校验和

	iic_stop();					// 结束条件	

	if( chksum != (INT8U)(keysts+MEM_ADDR_GET_KEYSTS) )
	{ keysts = 0; }
	return(keysts);	  	
}

/************************************************************************
** 功能描述：CBM7008 initlize
** 
************************************************************************/
void CBM7008_init(void)
{
	INT8U	i;
	CBM7008IO_Config();			// IO 口配置
//	Ini_CBM7008();				// IIC 初始化
	
	for(i = 0; i < 3; i++)
	{
		if(CBM7008ID == Get_CBM7008_ID())			// 读ID
		{ 
			Set_CBM7008_nLMD();			// 设置灵敏度
			Get_CBM7008_nLMD();			// 读灵敏度		
			return; 
		}
		DelayMs(300);						 // 延时150ms
	}
}

/************************************************************************
* 获取键按值
* 返回键值
************************************************************************/
INT8U	Scan_Val(void)
{
 	INT8U	keyval = CMD_KEY_NULL;		 //0
	//-------------------------------------------
	//检测列1           延时1us
	keyval = Get_CBM7008_KeySts();

	if((keyval & 0x02) == 0x02)				
	{ keyval = CMD_KEY_OK; }						  //		 键值为1
	//-------------------------------------------		
	return( keyval );
}

#endif