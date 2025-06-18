#include "key.h"

/************************************
引脚说明：
KEY0连接PA0
KEY0按下，PA0为低电平
KEY0未按下，PA0为高电平

************************************/
void Key_PA0_Init(void)
{
	//结构体变量
	GPIO_InitTypeDef	GPIO_InitStruct;

	//使能GPIOA组时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	

	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_0; 	//引脚0
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;	//输入模式
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_UP; //根据外面电路来设置即可
	
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void delays(int n)
{
	int i, j;
	
	for(i=0; i<n; i++)
		for(j=0; j<10000; j++);
}

//u8 == unsigned char
/************************************
函数功能:按键扫描
返回值：
成功:按下返回按键标志位，如：KEY0标志位1
失败:0

u8 mode:是否支持连按
0:不支持连按
1:支持连按

*************************************/
u8 Key_Scan(u8 mode)
{
	//key_up保存上一次的值 
	static u8 key_up = 1;  //按键标志
	
	if(mode == 1) //支持连按
		key_up = 1; 
					
	if(key_up &&  (PAin(0) == 0))
	{
		delays(10);
		key_up = 0; 
		if(PAin(0) == 0)
		{
			return 1; // KEY0标志值为1
		}
	}
	else if(PAin(0) == 1) //未按下--也可以理解为松开
	{
		key_up = 1; //按键松开key_up == 1
	}
	
	//未操作按键（按键松开）
	return 0;

}





