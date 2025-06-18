#include "iic.h"

/****************************************
����˵��
SCL -- PB8
SDA -- PB9

*****************************************/

void Iic_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	//��GPIOB��ʱ�� 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	

	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_9|GPIO_Pin_8;		//����8
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;				//���ģʽ
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_OD;				//��©��� �ⲿ���������裬������Ϊ��©
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_UP;					//����
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz;				//�ٶ�
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
	
	//����״̬
	SCL = 1;
	SDA_OUT = 1;
}

//��������ģʽ
void Iic_Sda_Mode(GPIOMode_TypeDef mode)
{

	GPIO_InitTypeDef  GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_9;		//����8
	GPIO_InitStruct.GPIO_Mode	= mode;							//���ģʽ
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_OD;				//��©���
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_UP;					//����
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_50MHz;				//�ٶ�
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
}

//��ʱ��Ϊ�˸��ӻ���һ����ʱ����Ӧ
//�����ź�
void Iic_Start(void)
{
	//����Ϊ���
	Iic_Sda_Mode(GPIO_Mode_OUT);
	
	SCL = 1;
	SDA_OUT = 1;
	
	delay_us(5);
	
	SDA_OUT = 0;
	
	delay_us(5);
	
	SCL = 0;

}
//ֹͣ�ź�
void Iic_Stop(void)
{
	//����Ϊ���
	Iic_Sda_Mode(GPIO_Mode_OUT);
	SCL = 0;
	SDA_OUT = 0;
	
	delay_us(5);
	
	SCL = 1;
	
	delay_us(5);
	
	SDA_OUT = 1;

}

//����һλ���ݣ�����ת��Ϊ���ŵ�ƽ
//Ack = 1:����Ϊ�ߵ�ƽ  Ack=0������Ϊ�͵�ƽ
void Iic_Send_Ack(u8 Ack)
{
	//����Ϊ���
	Iic_Sda_Mode(GPIO_Mode_OUT);


	SCL = 0;
	
	//��ʱ��Ϊ�͵�ƽʱ���ɱ������״̬
	if(Ack == 1)
		SDA_OUT = 1;
	else
		SDA_OUT = 0;
	
	delay_us(5);
	
	SCL = 1;
	
	delay_us(5);
	
	SCL = 0;

}


//����һ���ֽڣ�һ���ֽ�8λ��
//�ȷ���λ����:1001 1000
void Iic_Send_Byte(u8 txdata)
{
	u8 i;
	//����Ϊ���
	Iic_Sda_Mode(GPIO_Mode_OUT);
	
	//8λҪ8������
	
	SCL = 0;
	
	for(i=0; i<8; i++)
	{
		
		//��ʱ��Ϊ�͵�ƽʱ���ɱ������״̬
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

//����һλ����,�ж����ŵ�ƽ
u8 Iic_Recv_Ack(void)
{
	u8 ack = 0;
	
	//����Ϊ����
	Iic_Sda_Mode(GPIO_Mode_IN);


	SCL = 0;
	
	delay_us(5);

	//��ʱ����Ϊ�ߵ�ƽʱ���ж��������ݣ���������	
	SCL = 1;
	
	delay_us(5);
	
	if(SDA_IN)
		ack = 1;
	else
		ack = 0;	

	SCL = 0;	

	return ack;
}

//����һ���ֽ�
u8 Iic_Recv_Byte(void)
{
	u8 i, rxdata = 0x00;
	
	//����Ϊ����
	Iic_Sda_Mode(GPIO_Mode_IN);


	//8λҪ8������
	SCL = 0;
	
	for(i=0; i<8; i++)
	{
			
		delay_us(5);
		
		SCL = 1;
		
		delay_us(5);
		
		//��ʱ����Ϊ�ߵ�ƽʱ���ж��������ݣ���������	
		if(SDA_IN)
			rxdata |= (1<<(7-i));
//		else
//			rxdata &= ~(1<<(7-i));		
		
		
		SCL = 0;	
	
	
	}

	return rxdata;
}

/*******************************
u8 addr:д������ʼ��ַ
u8 *write_buff�������׵�ַ
u8 len�����ݳ���
********************************/
void At24c02_Write_Page(u8 addr, u8 *write_buff, u8 len)
{
	u8 i, ack;
	
	//�����ź�
	Iic_Start();

	//STM32��Ϊ����������豸��ַ������24C02ִ��д����	
	Iic_Send_Byte(AT24C02_ADD_W);
	ack = Iic_Recv_Ack();
	if(ack == 1)
	{
		printf("ack failure 1\n");
		return;
	}

	//STM32����д������ʼ��ַ
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
		//STM32�������ݣ�д����
		Iic_Send_Byte(*write_buff);
		ack = Iic_Recv_Ack();
		if(ack == 1)
		{
			printf("ack failure 3\n");
			return;
		}			
	
		//ָ��ָ����һ���ݿռ�
		write_buff++;
	}
#else
	while(len--)
	{
	
		//STM32�������ݣ�д����
		Iic_Send_Byte(*write_buff);
		ack = Iic_Recv_Ack();
		if(ack == 1)
		{
			printf("ack failure 3\n");
			return;
		}			
	
		//ָ��ָ����һ���ݿռ�
		write_buff++;
		
	}
	
#endif
	
	//ֹͣ�ź�
	Iic_Stop();
	
	
	printf("write finish\n");

}


