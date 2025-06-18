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
	
	//�жϵ����ȼ����飬һ����Ŀֻ������һ��
	//�ж����ȼ���Ϊ�ڶ��飬��ռ����Χ:0~3  ��Ӧ:0~3
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();
	

	//��ʼ����GPIOF_ODRĬ��Ϊ�͵�ƽ�����Ե���
	Led_Init();
	
	Usart1_Init(115200);



	
	
	while (1)
	{

	}
	return 0;
}
