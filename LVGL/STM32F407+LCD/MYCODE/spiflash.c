#include "spiflash.h"




/*********************************
����˵����

ʹ��SPI1
SCK����PB3
MISO����PB4
MOSI����PB5


CS����PB14 -- �������

**********************************/

#if 0

void Spiflash_Init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	SPI_InitTypeDef		SPI_InitStruct;

	
	//ʹ��SPIx��IO��ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	//SCK MISO MOSIS
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;   	//����3 4 5
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;  	//����ģʽ
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 	
	
	//CS
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_14; //����14
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT; 	//���ģʽ
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;	//����ģʽ
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_25MHz; //����ٶ�
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP; //����
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	//���ù���ѡ��
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);	
	
	
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; //84MHZ/64
	//������ʽ0
	SPI_InitStruct.SPI_CPHA		= SPI_CPHA_1Edge; 	//��һ����
	SPI_InitStruct.SPI_CPOL		= SPI_CPOL_Low; 	//�͵�ƽ
	SPI_InitStruct.SPI_DataSize	= SPI_DataSize_8b;	//����Ϊ8λ
	SPI_InitStruct.SPI_Direction= SPI_Direction_2Lines_FullDuplex; //ȫ˫��
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB; //�ȴ���λ
	SPI_InitStruct.SPI_Mode		= SPI_Mode_Master;  //����
	SPI_InitStruct.SPI_NSS		= SPI_NSS_Soft;  //�������CS
	SPI_InitStruct.SPI_CRCPolynomial = 7;  //CRCУ��
	//��ʼ��SPIx,����SPIx����ģʽ
	SPI_Init(SPI1, &SPI_InitStruct);
	//ʹ��SPIx
	SPI_Cmd( SPI1, ENABLE);	
	
	//��ʹ��оƬ
	F_CS = 1;

}

//SPI��һ���ֽڣ�������һ���ֽ�
u8 Spi1_Send_Recv_Byte(u8 txdata)
{
	u8 rxdata = 0x00;
	
	//�ȴ����͵ı�־λ
	while( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) ==  0);
	//�������ݵĻ�����Ϊ�գ������ٴη�������
	SPI_I2S_SendData(SPI1, txdata);
	
	
	//�ȴ����ܵı�־λ
	while( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) ==  0);
	//�������ǿգ���ȥ��������
	rxdata = SPI_I2S_ReceiveData(SPI1);	
	
	return rxdata;
}

#else

void Spiflash_Init(void)
{

	GPIO_InitTypeDef  	GPIO_InitStruct;
	SPI_InitTypeDef		SPI_InitStruct;
	
	//ʹ��GPIOB��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 

	
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_14;	//����3 5 14
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;	  //���ģʽ
	GPIO_InitStruct.GPIO_OType= GPIO_OType_PP;  //�������
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_25MHz;//�ٶ�25MHZ
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;   //����
	GPIO_Init(GPIOB, &GPIO_InitStruct);		
	
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_4;	//����4
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;	  //����ģʽ
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;   //����
	GPIO_Init(GPIOB, &GPIO_InitStruct);		
	

	//��ʹ��оƬ
	F_CS = 1;

}

//SPI��һ���ֽڣ�������һ���ֽ�
u8 Spi1_Send_Recv_Byte(u8 txdata)
{
	u8 rxdata = 0x00;
	

	return rxdata;
}


#endif



u16 W25q128_id(void)
{
	u16 id = 0x00;
	
	//ʹ��оƬ
	F_CS = 0;	

	//���Ͷ����������豸ID������
	Spi1_Send_Recv_Byte(0x90);

	//��ַ��ַ��ͣ��ȷ���λ��ַ
	//�����ַ������0x000000
	Spi1_Send_Recv_Byte(0x00);
	Spi1_Send_Recv_Byte(0x00);
	Spi1_Send_Recv_Byte(0x00);
	
	//���������ַ�(0xBB)����ȡ������ID
	id |= Spi1_Send_Recv_Byte(0xBB)<<8; //������ID�ƶ�15λ~8λ
	id |= Spi1_Send_Recv_Byte(0xBB);    //����ID������7λ~0λ
	
	//��ʹ��оƬ
	F_CS = 1;		
	
	return id;
}


void Write_Enable(void)
{
	F_CS = 0;
	//����дʹ������
	Spi1_Send_Recv_Byte(0x06);
	
	F_CS = 1;

}
//u32 addr:������ʼ��ַ
void Erase_Sector(u32 addr)
{
	u8 status;
	//дʹ��
	Write_Enable();

	F_CS = 0;
	//���Ͳ�������
	Spi1_Send_Recv_Byte(0x20);
	
	//���Ͳ�����ʼ��ַ  0x11A025
	Spi1_Send_Recv_Byte((addr>>16)&0xFF ); //��23~16λ��ַ(addr>>16) ==> 0x0000  11
	Spi1_Send_Recv_Byte((addr>>8)&0xFF );  //��15~8λ��ַ (addr>>8)  ==> 0x0011  A0
	Spi1_Send_Recv_Byte(addr&0xFF );  		//��7~0λ��ַ addr       ==> 0x11A0  25
	
	F_CS = 1;

	
	//�ȴ��������
	F_CS = 0;
	
	//���Ͷ�״̬�Ĵ���1����
	Spi1_Send_Recv_Byte(0x05);	
	
	//�ȴ��������
	while(1)
	{
		//�ж�BUSYλ�Ƿ�Ϊ0
		if((Spi1_Send_Recv_Byte(0x05) & 0x01) == 0)
			break;
	}
	

	F_CS = 1;
}


void Page_Write(u32 addr, u8 *write_buff, u32 len)
{
	//дʹ��
	Write_Enable();

	
	//ʹ��оƬ
	F_CS = 0;
	
	//����д��������
	Spi1_Send_Recv_Byte(0x02);
	
	Spi1_Send_Recv_Byte((addr>>16)&0xFF); //�ȷ�23~16λ��ַ
	Spi1_Send_Recv_Byte((addr>>8)&0xFF);  //��15~8λ��ַ
	Spi1_Send_Recv_Byte(addr&0xFF);     //��7~0λ��ַ

	
	
	//д����
	while(len--)
	{
		Spi1_Send_Recv_Byte(*write_buff); 
		write_buff++;
	}
	
	
	
	//��ʹ��оƬ
	F_CS = 1;
	
	F_CS = 0;
	//���Ͷ�״̬�Ĵ���1����
	Spi1_Send_Recv_Byte(0x05);	
	
	while(1)
	{
		
	
		//�ж����λ�Ƿ�Ϊ1
		if( (Spi1_Send_Recv_Byte(0xFF) & 0x01) == 0)
			break;
	
	}
	
	F_CS = 1;
	
}

//������
void Read_Data(u32 addr, u8 *read_buff, u32 len)
{
	//ʹ��оƬ
	F_CS = 0;
	
	//���Ͷ���������
	Spi1_Send_Recv_Byte(0x03);
	
	//����24λ��ַ  �ȷ���λ
	Spi1_Send_Recv_Byte(addr>>16); //�ȷ�23~16λ��ַ
	Spi1_Send_Recv_Byte(addr>>8);  //��15~8λ��ַ
	Spi1_Send_Recv_Byte(addr);     //��7~0λ��ַ
	
	while(len--)
	{
		//0x77:�����ַ�
		*read_buff = Spi1_Send_Recv_Byte(0x77); 
		read_buff++;
	}

	F_CS = 1;
}




