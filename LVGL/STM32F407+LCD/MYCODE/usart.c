#include "usart.h"
#include "stdio.h"

#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
    int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
int _sys_exit(int x) 
{ 
    x = x; 
} 
//printf������¶��򵽴������
int fputc(int ch, FILE *f)
{     
    USART_SendData(USART1,ch);  //ͨ�����ڷ�������
    //�ȴ����ݷ������
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);      
    return ch;
}

/********************************************
����˵��

PA9  ---- USART1_TX(���Ͷ�)
PA10 ---- USART1_RX(���ն�)
********************************************/
void Usart1_Init(uint32_t myBaudRate)
{
	
	GPIO_InitTypeDef 	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStruct;
	NVIC_InitTypeDef    NVIC_InitStructure;
	
	//����ʱ��ʹ�ܣ�GPIOAʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//GPIO ��ʼ�����ã�Ҫ����ģʽΪ���ù��ܡ�
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9|GPIO_Pin_10;	//����9 10
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;	//���ù���
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz; //�������
	GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP; //�������
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP ; //����
	GPIO_Init(GPIOA, &GPIO_InitStructure); 		
	
	
	//�������Ÿ�����ӳ�䣺���� GPIO_PinAFConfig ������
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	

	
	USART_InitStruct.USART_BaudRate		= myBaudRate;  //������
	USART_InitStruct.USART_Mode			= USART_Mode_Tx|USART_Mode_Rx; //���ÿ��տɷ�--ȫ˫��
	USART_InitStruct.USART_Parity		= USART_Parity_No; //����żУ��	
	USART_InitStruct.USART_StopBits		= USART_StopBits_1; //1λֹͣλ
	USART_InitStruct.USART_WordLength	= USART_WordLength_8b; //�ֳ���1�ֽ�
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
	//5�����ڲ�����ʼ�������ò����ʣ��ֳ�����żУ��Ȳ�����
	USART_Init(USART1, &USART_InitStruct);
	
	
	//ϣ�������ݵ����������жϣ�ȥȡ����
	//�����жϲ��ҳ�ʼ�� NVIC��ʹ���жϣ������Ҫ���������жϲ���Ҫ������裩
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;   				//ͨ����ţ�����stm32f4xx.h�в鿴
	//������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; 	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;			//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	
	
	
	//����Ϊ�����жϣ���ʾ�����ݹ�����CPUҪ�жϽ��н��գ�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 

	//ʹ�ܴ��ڡ�
	USART_Cmd(USART1, ENABLE);

}