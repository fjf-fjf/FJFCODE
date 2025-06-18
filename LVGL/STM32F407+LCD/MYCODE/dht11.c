#include "dht11.h"


/**********************************
引脚说明：

PG9 -- DQ(DHT11)
***********************************/

void Dht11_Init(void)
{
	GPIO_InitTypeDef  	GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9;				//第9号引脚
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;			//输出模式
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;			//推挽输出，增强驱动能力，引脚的输出电流更大
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_25MHz;			//引脚的速度最大为25MHz
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;			//没有使用内部上拉电阻
	GPIO_Init(GPIOG, &GPIO_InitStructure);	
	
	//温湿度模块还没有工作，那么它的触发引脚是高电平
	PGout(9) = 1;
}

//引脚模式变更
void Dht11_Pin_Mode(GPIOMode_TypeDef mode)
{
	GPIO_InitTypeDef  	GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;				//第9号引脚
	GPIO_InitStructure.GPIO_Mode  = mode;					//输入/输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//推挽输出，增强驱动能力，引脚的输出电流更大
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;		//引脚的速度最大为100MHz
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;		//没有使用内部上拉电阻
	GPIO_Init(GPIOG, &GPIO_InitStructure);	
}

//启动DHT11
int Dht11_Start(void)
{
	u16 t = 0;
	
	
	//启动信号 
	//做为输出模式
	Dht11_Pin_Mode(GPIO_Mode_OUT);
	PGout(9) = 1;
	delay_ms(2);
	PGout(9) = 0;
	delay_ms(20);
	PGout(9) = 1;
	delay_us(30);
	
	//回响信号 
	//做为输入模式
	Dht11_Pin_Mode(GPIO_Mode_IN);	
	//判断回响信号有低与高电平即可
	
	
	//下面是比较简单的过滤回响信号的代码，下面代码，如果硬件有坏，有可以出现卡死现象
	//while(PGin(9) == 1);
	//while(PGin(9) == 0);
	//while(PGin(9) == 1);
	
	
	
	//等待低电平的到来
	while(PGin(9) == 1)
	{
		t++;
		delay_us(2);
		
		if(t >= 100) //等待200us未有低电平到来，则返回
			return -1;
	}
	//延时40us，再过滤低电平
	delay_us(40);
	
	t = 0;
	//等待高电平的到来,过滤低电平
	while(PGin(9) == 0)
	{
		t++;
		delay_us(2);
		
		if(t >= 100) //等待200us未有高电平到来，则返回
			return -1;
	}	
	
	//延时40us
	delay_us(40);	
	
	t = 0;
	//等待低电平的到来，过滤高电平
	while(PGin(9) == 1)
	{
		t++;
		delay_us(2);
		
		if(t >= 100) //等待200us未有低电平到来，则返回
			return -1;
	}	
	
	//执行到这里，接下来就是DHT11传输40位数据
	
	return 0;
	

}

//接受一个字节
u8 Dht11_Recv_Byte(void)
{
	u16 t = 0, time_count = 0;
	u8 i, rxdata = 0x00; //0000 0000
	
	for(i=0; i<8; i++)
	{
		
		TIM3->CNT = 0;
		
#if 1
		t = 0;
		//等待高电平的到来,过滤低电平
		while(PGin(9) == 0)
		{
			t++;
			delay_us(2);
			
			if(t >= 100) //等待200us未有高电平到来，则返回
				return 0;
		}
		//使能定时器，开始计数
		TIM_Cmd(TIM3, ENABLE);		
		t = 0;
		//等待低电平的到来，过滤高电平
		while(PGin(9) == 1)
		{
			t++;
			delay_us(2);
			
			if(t >= 100) //等待200us未有低电平到来，则返回
				return -1;
		}	
	
				

#else
		while(PGin(9) == 0);
		//使能定时器，开始计数
		TIM_Cmd(TIM3, ENABLE);	
		while(PGin(9) == 1);

#endif
		
		//获取高电平持续时间
		time_count = TIM3->CNT;
		TIM_Cmd(TIM3, DISABLE);
		
		//time_count高电平持续时间
		
		if( 55 <= time_count && time_count <= 80)
		{
			rxdata |= (1<<(7-i));
		}
		
		//下面可不要
//		if( 23 <= time_count && time_count <= 35)
//		{
//			rxdata &= ~(1<<(7-i));
//		}		

	
	}
	
	return rxdata;
	
}


int Dht11_Data(u8 *data)
{
	int ret, i;
	
	ret = Dht11_Start();
	if(ret != 0)
		return -1;
	
	for(i=0; i<5; i++)
	{
		data[i] = Dht11_Recv_Byte();
	}
	
	//校验判断
	if(data[4] == data[0]+data[1]+data[2]+data[3])
		return 0;
	else
		return -1;
	
}


