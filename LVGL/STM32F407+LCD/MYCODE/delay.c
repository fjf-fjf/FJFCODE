#include "delay.h"

u32 my_nus = 21;  		//��21MHZ����21��������ʱ1us
u32 my_nms = 21000;  	//��21MHZ����21000��������ʱ1ms

void Delay_Init(void)
{
	//HCLK = 168MHZ  HCLK/8 = 21MHZ
	//SysTick��ʱ����ʱ��Ƶ��:21MHZ
	//ʹ���ⲿ�ο���ʱ��
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

}

//nus:ȡֵ��Χ��1~798,915
void delay_us(int nus)
{
	//�������ж�
	u32 temp = 0x00;
	
	
	//��װ��ֵ�Ĵ�����ʼֵ
	SysTick->LOAD = nus*my_nus - 1;
	//���ü�����Ϊ0
	SysTick->VAL = 0x00;
	//ʹ�ܶ�ʱ������ʱ���е�SysTick->VALֵΪ0��Ӳ�����Զ���SysTick->LOAD����װ��SysTick->VAL
	SysTick->CTRL |=(1<<0);
	
	//�ȴ�SysTick->CTRL��16λΪ1
	while(1)
	{
		temp = SysTick->CTRL;
		
		if(temp & (1<<16)) //���Ϊ��,˵��16Ϊλ1
			break;
		
        //���ϵͳ��ʱ���Ƿ�����ر�    
        if((temp & 0x1)==0) //�жϵ�0λ�Ƿ�Ϊ0��0��ʾ��ʱ�����ر���
            return -1;    	
	}
	
	//�رն�ʱ��
	SysTick->CTRL &= ~(1<<0);
	
}



//nms:ȡֵ��Χ��1~798
void delay_ms(int nms)
{
	//�������ж�
	u32 temp = 0x00;
	
	
	//��װ��ֵ�Ĵ�����ʼֵ
	SysTick->LOAD = nms*my_nms - 1;
	//���ü�����Ϊ0
	SysTick->VAL = 0x00;
	//ʹ�ܶ�ʱ������ʱ���е�SysTick->VALֵΪ0��Ӳ�����Զ���SysTick->LOAD����װ��SysTick->VAL
	SysTick->CTRL |=(1<<0);
	
	//�ȴ�SysTick->CTRL��16λΪ1
	while(1)
	{
		temp = SysTick->CTRL;
		
		if(temp & (1<<16)) //���Ϊ��,˵��16Ϊλ1
			break;
		
        //���ϵͳ��ʱ���Ƿ�����ر�    
        if((temp & 0x1)==0) //�жϵ�0λ�Ƿ�Ϊ0��0��ʾ��ʱ�����ر���
            return -1;    	
	}
	
	//�رն�ʱ��
	SysTick->CTRL &= ~(1<<0);
	
}

void delay_s(int ns)
{
	int i;
	for(i=0; i<ns; i++)
	{
		delay_ms(500);
		delay_ms(500);
	}
}

