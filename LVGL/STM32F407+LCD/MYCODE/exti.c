#include "exti.h"

/********************************************
引脚说明

KEY0连接PA0
PA0---EXTI0
选择下降沿触发

********************************************/

void Exti_PA0_Init(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	//使能GPIOA组时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//使能SYSCFG组时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	//配置引脚PA0
	GPIO_InitStructure.GPIO_Pin	   	= GPIO_Pin_0; 	//引脚0
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN;	//输入模式
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP; //根据外面电路来设置即可
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//连接EXTI0到PA0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	
	//配置外部中断控制器
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line0;  			//外部中断线0
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt; 	//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//中断线使能
	EXTI_Init(&EXTI_InitStructure);
	
	//NVIC配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;   //外部中断线0的通道编号，可在stm32f4xx.h中查看
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; 	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//通道使能
	NVIC_Init(&NVIC_InitStructure);


}

//EXTI0中断服务函数

/**************************************

a.中断函数格式: void  中断服务函数名(void)
b.判断一个函数是否为中断服务函数名，需要查看能否在startup_stm32f40_41xxx.s中
查找的到，能查到，表示它是中断服务函数，否则不是。
c.中断服务函数是不需要调用的，当满足中断条件后,CPU自动去执行的函数。
d.中断是不能执行过长时间

***************************************/


void  EXTI0_IRQHandler(void)
{
	//判断中断线状态，如果有中断，中断位标志为1
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
	
		GPIO_ToggleBits(GPIOF, GPIO_Pin_9);
		
		//清空中断线
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}