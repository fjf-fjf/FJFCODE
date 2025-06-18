#include "tim.h"

/*************************************
��ʱ��˵��:
TIM3 -- APB1
TIM3Ƶ�ʣ�84MHZ
TIM3:16λ��ʱ��
*************************************/
void Tim3_Init(void)
{
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	
	//ʹ�ܶ�ʱ��ʱ�ӡ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	 
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1); 	//����Ԥ��Ƶ�� 84��Ƶ 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= (1000-1); //�������� ��װ��ֵ ȷ�����ʱ�䣺1000/1MHZ = 1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1; //ʱ�ӷ�Ƶ��ETR TI�йأ����ö�ʱ��ʱ���Լ���
	
	
	//��ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	
	//����ʱ���жϣ�����NVIC��
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;   				//ͨ����ţ�����stm32f4xx.h�в鿴
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; 	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
	
	
	//��ʱ�����ж����ж�Դ����ѡ�����е�һ��
	//TIM3_DIER  ��������ж�
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	//ʹ�ܶ�ʱ����
	TIM_Cmd(TIM3, ENABLE);

}

void Tim3_NoISR_Init(u32 Period)
{
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	
	//ʹ�ܶ�ʱ��ʱ�ӡ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	 
	TIM_TimeBaseInitStruct.TIM_Prescaler	= (84-1); 	//����Ԥ��Ƶ�� 84��Ƶ 84MHZ/84 = 1MHZ
	TIM_TimeBaseInitStruct.TIM_Period		= Period; //�������� ��װ��ֵ ȷ�����ʱ�䣺1000/1MHZ = 1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode	= TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision= TIM_CKD_DIV1; //ʱ�ӷ�Ƶ��ETR TI�йأ����ö�ʱ��ʱ���Լ���
	
	
	//��ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	

	//ʹ�ܶ�ʱ����
	TIM_Cmd(TIM3, DISABLE);

}


//��ʱ���жϷ�����
void TIM3_IRQHandler(void)
{
	//�ж϶�ʱ���ı�־λ
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		//��1ms���һ�� ��ѹ3.3V 0V  3.3V  0V
		GPIO_ToggleBits(GPIOF, GPIO_Pin_9);
		
		//��־λ������ձ�־λ��CPU��Ϊ��һ��������������һֱִ���жϷ�����
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}	


}


