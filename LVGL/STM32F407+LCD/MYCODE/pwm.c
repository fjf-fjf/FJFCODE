#include "pwm.h"

/************************************
����˵����
LED0������PF9,�͵�ƽ�������ߵ�ƽ������
TIM14_CH1(TIM14 -- APB1 16λ  84MHZ)
************************************/

void Pwm_PF9_Init(void)
{
	GPIO_InitTypeDef 			GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  			TIM_OCInitStructure;

	
	//��ʱ��ʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	//GPIOFʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9;	//����9
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;	//���ù���
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz; //�������
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP; //�������
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP ; //����
	GPIO_Init(GPIOF, &GPIO_InitStructure); 
	
	//����ӳ��   TIM14_CH1������PF9 
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);

	
	//��ʱ������(T)1ms  (f)1000HZ  f = 1/T
	TIM_TimeBaseStructure.TIM_Prescaler		= (84-1); 	//����Ԥ��Ƶ�� 84��Ƶ 84MHZ/84 = 1MHZ
	TIM_TimeBaseStructure.TIM_Period		= (1000-1); //�������� ��װ��ֵ ȷ�����ʱ�䣺1000/1MHZ = 1ms
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseStructure.TIM_ClockDivision= TIM_CKD_DIV1; //ʱ�ӷ�Ƶ��ETR TI�йأ����ö�ʱ��ʱ���Լ���
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);
	
	//���ö�ʱ��ͨ��
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;  //PWM1ģ#ʽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//ͨ�����ʹ��
	TIM_OCInitStructure.TIM_Pulse 		= 0;         //CCR1�ĳ�ʼ��
	TIM_OCInitStructure.TIM_OCPolarity 	= TIM_OCPolarity_Low; //������ԣ��������LED0�Ƶ�ԭ�����Ե�ƽѡ��͵�ƽ
	//OC1--ͨ��1
	TIM_OC1Init(TIM14, &TIM_OCInitStructure);
	//ʹ��Ԥװ�ؼĴ���
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);
	
	
	//ʹ����װ�ؼĴ���--ARR
	TIM_ARRPreloadConfig(TIM14, ENABLE);
	
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM14, ENABLE);

	//�������ã�û�������жϣ� PWM��������ҪCPU����

}