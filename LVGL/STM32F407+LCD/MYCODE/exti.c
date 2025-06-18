#include "exti.h"

/********************************************
����˵��

KEY0����PA0
PA0---EXTI0
ѡ���½��ش���

********************************************/

void Exti_PA0_Init(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	//ʹ��GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//ʹ��SYSCFG��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	//��������PA0
	GPIO_InitStructure.GPIO_Pin	   	= GPIO_Pin_0; 	//����0
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN;	//����ģʽ
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP; //���������·�����ü���
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//����EXTI0��PA0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	
	//�����ⲿ�жϿ�����
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line0;  			//�ⲿ�ж���0
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt; 	//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش��� 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);
	
	//NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;   //�ⲿ�ж���0��ͨ����ţ�����stm32f4xx.h�в鿴
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; 	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);


}

//EXTI0�жϷ�����

/**************************************

a.�жϺ�����ʽ: void  �жϷ�������(void)
b.�ж�һ�������Ƿ�Ϊ�жϷ�����������Ҫ�鿴�ܷ���startup_stm32f40_41xxx.s��
���ҵĵ����ܲ鵽����ʾ�����жϷ������������ǡ�
c.�жϷ������ǲ���Ҫ���õģ��������ж�������,CPU�Զ�ȥִ�еĺ�����
d.�ж��ǲ���ִ�й���ʱ��

***************************************/


void  EXTI0_IRQHandler(void)
{
	//�ж��ж���״̬��������жϣ��ж�λ��־Ϊ1
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{
	
		GPIO_ToggleBits(GPIOF, GPIO_Pin_9);
		
		//����ж���
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}