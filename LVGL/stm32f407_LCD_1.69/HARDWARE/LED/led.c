#include "led.h"

/************************************
����˵����
LED0������PF9
PF9����͵�ƽ������������ߵ�ƽ������

LED1 -- PF10
LED2 -- PE13
LED3 -- PE14
************************************/

void Led_Init(void)
{	
	//�ṹ�����
	GPIO_InitTypeDef	GPIO_InitStruct;

	//ʹ��GPIOE��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);	
	//ʹ��GPIOF��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_9 | GPIO_Pin_10; //����9 10
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;//���
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_PP;//����ģʽ
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_25MHz;//25MHZ�ٶ�
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_NOPULL; //��������
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_13 | GPIO_Pin_14; //����13 14
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_OUT;//���
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_PP;//����ģʽ
	GPIO_InitStruct.GPIO_Speed	= GPIO_Speed_25MHz;//25MHZ�ٶ�
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_NOPULL; //��������
	GPIO_Init(GPIOE, &GPIO_InitStruct);	
	
	//��ȫ��
	PFout(9)  = 1;
	PFout(10) = 1;
	PEout(13) = 1;
	PEout(14) = 1;
}
