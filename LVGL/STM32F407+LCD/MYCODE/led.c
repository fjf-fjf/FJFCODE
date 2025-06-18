#include "led.h"

/************************************
引脚说明：
LED0连接在PF9
PF9输出低电平，灯亮；输出高电平，灯灭

LED1 -- PF10
LED2 -- PE13
LED3 -- PE14
************************************/

void Led_Init(void)
{	
	//结构体变量
	GPIO_InitTypeDef	GPIO_InitStruct;

	//使能GPIOE组时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);	
	//使能GPIOF组时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_9 | GPIO_Pin_10; //引脚9 10
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;//输出
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_PP;//推挽模式
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_25MHz;//25MHZ速度
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_NOPULL; //无上下拉
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_13 | GPIO_Pin_14; //引脚13 14
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;//输出
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_PP;//推挽模式
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_25MHz;//25MHZ速度
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_NOPULL; //无上下拉
	GPIO_Init(GPIOE, &GPIO_InitStruct);	
	
	//灯全灭
	PFout(9)  = 1;
	PFout(10) = 1;
	PEout(13) = 1;
	PEout(14) = 1;
}
