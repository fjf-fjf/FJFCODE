#include <stdio.h>
#include "led.h"
#include "delay.h"
#include "usart.h"



int main(void)
{
	uint8_t buf[32]={0};
	
	uint16_t tp_x,tp_y;
	
	uint8_t tp_finger_num=0;
	
	uint8_t tp_sta;
	
	u8 i;
	
	//中断的优先级分组，一个项目只能设置一次
	//中断优先级分为第二组，抢占级范围:0~3  响应:0~3
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();
	

	//初始化后GPIOF_ODR默认为低电平，所以灯亮
	Led_Init();
	
	Usart1_Init(115200);



	
	
	while (1)
	{

	}
	return 0;
}
