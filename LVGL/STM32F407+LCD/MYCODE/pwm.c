#include "pwm.h"

/************************************
引脚说明：
LED0连接在PF9,低电平灯亮；高电平，灯灭
TIM14_CH1(TIM14 -- APB1 16位  84MHZ)
************************************/

void Pwm_PF9_Init(void)
{
	GPIO_InitTypeDef 			GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  			TIM_OCInitStructure;

	
	//定时器时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	//GPIOF时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9;	//引脚9
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;	//复用功能
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz; //输出速率
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP ; //上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure); 
	
	//引脚映射   TIM14_CH1挂引脚PF9 
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);

	
	//定时器周期(T)1ms  (f)1000HZ  f = 1/T
	TIM_TimeBaseStructure.TIM_Prescaler		= (84-1); 	//设置预分频器 84分频 84MHZ/84 = 1MHZ
	TIM_TimeBaseStructure.TIM_Period		= (1000-1); //计数周期 重装载值 确定溢出时间：1000/1MHZ = 1ms
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseStructure.TIM_ClockDivision= TIM_CKD_DIV1; //时钟分频与ETR TI有关，配置定时器时忽略即可
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);
	
	//配置定时器通道
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;  //PWM1模#式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//通道输出使能
	TIM_OCInitStructure.TIM_Pulse 		= 0;         //CCR1的初始化
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_Low; //输出极性，这里根据LED0灯的原理，极性电平选择低电平
	//OC1--通道1
	TIM_OC1Init(TIM14, &TIM_OCInitStructure);
	//使能预装载寄存器
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);
	
	
	//使能重装载寄存器--ARR
	TIM_ARRPreloadConfig(TIM14, ENABLE);
	
	//使能定时器
	TIM_Cmd(TIM14, ENABLE);

	//上面配置，没有配置中断， PWM产生不需要CPU参与

}