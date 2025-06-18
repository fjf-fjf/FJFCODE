#include "iic.h"

/****************************************
引脚说明
SCL -- PB8
SDA -- PB9

*****************************************/

void Iic_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	//打开GPIOB组时钟 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	

	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_9|GPIO_Pin_8;		//引脚8
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;				//输出模式
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_OD;				//开漏输出 外部有上拉电阻，可配置为开漏
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_UP;					//上拉
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz;				//速度
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
	
	//空闲状态
	SCL = 1;
	SDA_OUT = 1;
}

//数据引脚模式
void Iic_Sda_Mode(GPIOMode_TypeDef mode)
{

	GPIO_InitTypeDef  GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_9;		//引脚8
	GPIO_InitStruct.GPIO_Mode	= mode;							//输出模式
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_OD;				//开漏输出
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_UP;					//上拉
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz;				//速度
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
}

//延时是为了给从机有一定的时间响应
//启动信号
void Iic_Start(void)
{
	//数据为输出
	Iic_Sda_Mode(GPIO_Mode_OUT);
	
	SCL = 1;
	SDA_OUT = 1;
	
	delay_us(5);
	
	SDA_OUT = 0;
	
	delay_us(5);
	
	SCL = 0;

}
//停止信号
void Iic_Stop(void)
{
	//数据为输出
	Iic_Sda_Mode(GPIO_Mode_OUT);
	SCL = 0;
	SDA_OUT = 0;
	
	delay_us(5);
	
	SCL = 1;
	
	delay_us(5);
	
	SDA_OUT = 1;

}

//发送一位数据，数据转换为引脚电平
//Ack = 1:引脚为高电平  Ack=0，引脚为低电平
void Iic_Send_Ack(u8 Ack)
{
	//数据为输出
	Iic_Sda_Mode(GPIO_Mode_OUT);


	SCL = 0;
	
	//在时钟为低电平时，可变更引脚状态
	if(Ack == 1)
		SDA_OUT = 1;
	else
		SDA_OUT = 0;
	
	delay_us(5);
	
	SCL = 1;
	
	delay_us(5);
	
	SCL = 0;

}


//发送一个字节（一个字节8位）
//先发高位数据:1001 1000
void Iic_Send_Byte(u8 txdata)
{
	u8 i;
	//数据为输出
	Iic_Sda_Mode(GPIO_Mode_OUT);
	
	//8位要8个脉冲
	
	SCL = 0;
	
	for(i=0; i<8; i++)
	{
		
		//在时钟为低电平时，可变更引脚状态
		if( txdata & (1<<(7-i)))
			SDA_OUT = 1;
		else
			SDA_OUT = 0;
			
		delay_us(5);
		
		SCL = 1;
		
		delay_us(5);
		
		SCL = 0;	
	
	
	}
	

}

//接受一位数据,判断引脚电平
u8 Iic_Recv_Ack(void)
{
	u8 ack = 0;
	
	//数据为输入
	Iic_Sda_Mode(GPIO_Mode_IN);


	SCL = 0;
	
	delay_us(5);

	//在时钟线为高电平时，判断引脚数据，接受数据	
	SCL = 1;
	
	delay_us(5);
	
	if(SDA_IN)
		ack = 1;
	else
		ack = 0;	

	SCL = 0;	

	return ack;
}

//接受一个字节
u8 Iic_Recv_Byte(void)
{
	u8 i, rxdata = 0x00;
	
	//数据为输入
	Iic_Sda_Mode(GPIO_Mode_IN);


	//8位要8个脉冲
	SCL = 0;
	
	for(i=0; i<8; i++)
	{
			
		delay_us(5);
		
		SCL = 1;
		
		delay_us(5);
		
		//在时钟线为高电平时，判断引脚数据，接受数据	
		if(SDA_IN)
			rxdata |= (1<<(7-i));
//		else
//			rxdata &= ~(1<<(7-i));		
		
		
		SCL = 0;	
	
	
	}

	return rxdata;
}

/*******************************
u8 addr:写数据起始地址
u8 *write_buff：数据首地址
u8 len：数据长度
********************************/
void At24c02_Write_Page(u8 addr, u8 *write_buff, u8 len)
{
	u8 i, ack;
	
	//启动信号
	Iic_Start();

	//STM32做为输出，发送设备地址，并对24C02执行写操作	
	Iic_Send_Byte(AT24C02_ADD_W);
	ack = Iic_Recv_Ack();
	if(ack == 1)
	{
		printf("ack failure 1\n");
		return;
	}

	//STM32发送写数据起始地址
	Iic_Send_Byte(addr);
	ack = Iic_Recv_Ack();
	if(ack == 1)
	{
		printf("ack failure 2\n");
		return;
	}	
	
#if 0
	for(i=0; i<len; i++)
	{
		//STM32发送数据，写数据
		Iic_Send_Byte(*write_buff);
		ack = Iic_Recv_Ack();
		if(ack == 1)
		{
			printf("ack failure 3\n");
			return;
		}			
	
		//指针指向下一数据空间
		write_buff++;
	}
#else
	while(len--)
	{
	
		//STM32发送数据，写数据
		Iic_Send_Byte(*write_buff);
		ack = Iic_Recv_Ack();
		if(ack == 1)
		{
			printf("ack failure 3\n");
			return;
		}			
	
		//指针指向下一数据空间
		write_buff++;
		
	}
	
#endif
	
	//停止信号
	Iic_Stop();
	
	
	printf("write finish\n");

}


