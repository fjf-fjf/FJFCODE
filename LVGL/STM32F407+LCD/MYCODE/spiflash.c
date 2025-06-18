#include "spiflash.h"




/*********************************
引脚说明：

使用SPI1
SCK连接PB3
MISO连接PB4
MOSI连接PB5


CS连接PB14 -- 软件控制

**********************************/

#if 0

void Spiflash_Init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	SPI_InitTypeDef		SPI_InitStruct;

	
	//使能SPIx和IO口时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	//SCK MISO MOSIS
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;   	//引脚3 4 5
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;  	//复用模式
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 	
	
	//CS
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_14; //引脚14
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT; 	//输出模式
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;	//推挽模式
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_25MHz; //输出速度
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	//复用功能选择
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);	
	
	
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; //84MHZ/64
	//工作方式0
	SPI_InitStruct.SPI_CPHA		= SPI_CPHA_1Edge; 	//第一边沿
	SPI_InitStruct.SPI_CPOL		= SPI_CPOL_Low; 	//低电平
	SPI_InitStruct.SPI_DataSize	= SPI_DataSize_8b;	//数据为8位
	SPI_InitStruct.SPI_Direction= SPI_Direction_2Lines_FullDuplex; //全双工
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB; //先传高位
	SPI_InitStruct.SPI_Mode		= SPI_Mode_Master;  //主机
	SPI_InitStruct.SPI_NSS		= SPI_NSS_Soft;  //软件控制CS
	SPI_InitStruct.SPI_CRCPolynomial = 7;  //CRC校验
	//初始化SPIx,设置SPIx工作模式
	SPI_Init(SPI1, &SPI_InitStruct);
	//使能SPIx
	SPI_Cmd( SPI1, ENABLE);	
	
	//不使能芯片
	F_CS = 1;

}

//SPI发一个字节，可以收一个字节
u8 Spi1_Send_Recv_Byte(u8 txdata)
{
	u8 rxdata = 0x00;
	
	//等待发送的标志位
	while( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) ==  0);
	//发送数据的缓冲区为空，才能再次发送数据
	SPI_I2S_SendData(SPI1, txdata);
	
	
	//等待接受的标志位
	while( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) ==  0);
	//缓冲区非空，才去接受数据
	rxdata = SPI_I2S_ReceiveData(SPI1);	
	
	return rxdata;
}

#else

void Spiflash_Init(void)
{

	GPIO_InitTypeDef  	GPIO_InitStruct;
	SPI_InitTypeDef		SPI_InitStruct;
	
	//使能GPIOB组时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 

	
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_14;	//引脚3 5 14
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;	  //输出模式
	GPIO_InitStruct.GPIO_OType= GPIO_OType_PP;  //输出推挽
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_25MHz;//速度25MHZ
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;   //上拉
	GPIO_Init(GPIOB, &GPIO_InitStruct);		
	
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_4;	//引脚4
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;	  //输入模式
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;   //上拉
	GPIO_Init(GPIOB, &GPIO_InitStruct);		
	

	//不使能芯片
	F_CS = 1;

}

//SPI发一个字节，可以收一个字节
u8 Spi1_Send_Recv_Byte(u8 txdata)
{
	u8 rxdata = 0x00;
	

	return rxdata;
}


#endif



u16 W25q128_id(void)
{
	u16 id = 0x00;
	
	//使能芯片
	F_CS = 0;	

	//发送读生产商与设备ID的命令
	Spi1_Send_Recv_Byte(0x90);

	//地址拆分发送，先发高位地址
	//下面地址合起来0x000000
	Spi1_Send_Recv_Byte(0x00);
	Spi1_Send_Recv_Byte(0x00);
	Spi1_Send_Recv_Byte(0x00);
	
	//发送任意字符(0xBB)，获取生产商ID
	id |= Spi1_Send_Recv_Byte(0xBB)<<8; //将生产ID移动15位~8位
	id |= Spi1_Send_Recv_Byte(0xBB);    //设置ID放置在7位~0位
	
	//不使能芯片
	F_CS = 1;		
	
	return id;
}


void Write_Enable(void)
{
	F_CS = 0;
	//发送写使能命令
	Spi1_Send_Recv_Byte(0x06);
	
	F_CS = 1;

}
//u32 addr:擦除起始地址
void Erase_Sector(u32 addr)
{
	u8 status;
	//写使能
	Write_Enable();

	F_CS = 0;
	//发送擦除命令
	Spi1_Send_Recv_Byte(0x20);
	
	//发送擦除起始地址  0x11A025
	Spi1_Send_Recv_Byte((addr>>16)&0xFF ); //发23~16位地址(addr>>16) ==> 0x0000  11
	Spi1_Send_Recv_Byte((addr>>8)&0xFF );  //发15~8位地址 (addr>>8)  ==> 0x0011  A0
	Spi1_Send_Recv_Byte(addr&0xFF );  		//发7~0位地址 addr       ==> 0x11A0  25
	
	F_CS = 1;

	
	//等待擦除完成
	F_CS = 0;
	
	//发送读状态寄存器1命令
	Spi1_Send_Recv_Byte(0x05);	
	
	//等待擦除完成
	while(1)
	{
		//判断BUSY位是否为0
		if((Spi1_Send_Recv_Byte(0x05) & 0x01) == 0)
			break;
	}
	

	F_CS = 1;
}


void Page_Write(u32 addr, u8 *write_buff, u32 len)
{
	//写使能
	Write_Enable();

	
	//使能芯片
	F_CS = 0;
	
	//发送写数据命令
	Spi1_Send_Recv_Byte(0x02);
	
	Spi1_Send_Recv_Byte((addr>>16)&0xFF); //先发23~16位地址
	Spi1_Send_Recv_Byte((addr>>8)&0xFF);  //发15~8位地址
	Spi1_Send_Recv_Byte(addr&0xFF);     //发7~0位地址

	
	
	//写数据
	while(len--)
	{
		Spi1_Send_Recv_Byte(*write_buff); 
		write_buff++;
	}
	
	
	
	//不使能芯片
	F_CS = 1;
	
	F_CS = 0;
	//发送读状态寄存器1命令
	Spi1_Send_Recv_Byte(0x05);	
	
	while(1)
	{
		
	
		//判断最低位是否为1
		if( (Spi1_Send_Recv_Byte(0xFF) & 0x01) == 0)
			break;
	
	}
	
	F_CS = 1;
	
}

//读数据
void Read_Data(u32 addr, u8 *read_buff, u32 len)
{
	//使能芯片
	F_CS = 0;
	
	//发送读数据命令
	Spi1_Send_Recv_Byte(0x03);
	
	//发送24位地址  先发高位
	Spi1_Send_Recv_Byte(addr>>16); //先发23~16位地址
	Spi1_Send_Recv_Byte(addr>>8);  //发15~8位地址
	Spi1_Send_Recv_Byte(addr);     //发7~0位地址
	
	while(len--)
	{
		//0x77:任意字符
		*read_buff = Spi1_Send_Recv_Byte(0x77); 
		read_buff++;
	}

	F_CS = 1;
}




