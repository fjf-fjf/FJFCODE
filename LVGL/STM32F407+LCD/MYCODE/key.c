#include "key.h"

/************************************
����˵����
KEY0����PA0
KEY0���£�PA0Ϊ�͵�ƽ
KEY0δ���£�PA0Ϊ�ߵ�ƽ

************************************/
void Key_PA0_Init(void)
{
	//�ṹ�����
	GPIO_InitTypeDef	GPIO_InitStruct;

	//ʹ��GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	

	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_0; 	//����0
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_IN;	//����ģʽ
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_UP; //���������·�����ü���
	
	
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
��������:����ɨ��
����ֵ��
�ɹ�:���·��ذ�����־λ���磺KEY0��־λ1
ʧ��:0

u8 mode:�Ƿ�֧������
0:��֧������
1:֧������

*************************************/
u8 Key_Scan(u8 mode)
{
	//key_up������һ�ε�ֵ 
	static u8 key_up = 1;  //������־
	
	if(mode == 1) //֧������
		key_up = 1; 
					
	if(key_up &&  (PAin(0) == 0))
	{
		delays(10);
		key_up = 0; 
		if(PAin(0) == 0)
		{
			return 1; // KEY0��־ֵΪ1
		}
	}
	else if(PAin(0) == 1) //δ����--Ҳ�������Ϊ�ɿ�
	{
		key_up = 1; //�����ɿ�key_up == 1
	}
	
	//δ���������������ɿ���
	return 0;

}





