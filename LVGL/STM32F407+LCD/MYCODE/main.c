#include <stdio.h>
#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"
#include "string.h"
#include "dht11.h"
#include "iwdg.h"
#include "rtc.h"
#include "adc.h"
#include "iic.h"
#include "i2c_ee.h"
#include "spiflash.h"
#include "includes.h"
//����ʱ(������ʱ��һ��׼ȷ����˼)

void delay(int n)
{
	int i, j;
	
	for(i=0; i<n; i++)
		for(j=0; j<10000; j++);
}

u8 g_buffer[32] = {0}, g_rxbuffer[32]={0};
u8 g_rxflag = 0;
u8 g_count = 0, g_i = 0;

//ÿ����һ���ֽڶ�������ж�
void USART1_IRQHandler(void)
{
	
	//�жϴ��ڽ��ձ�־λ�ı�־λ
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		//��ձ�־λ���������һλ����
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		//��������
		g_buffer[g_count++] = USART_ReceiveData(USART1);
		
		//����յ�����Ϊ':'��ʾ�յ�������
		if(g_buffer[g_count-1] == ':')
		{
			//��g_buffer���¸�ֵ��g_rxbuffer���ҹ��˽�����
			for(g_i=0; g_i < g_count-1; g_i++)
			{
				g_rxbuffer[g_i] = g_buffer[g_i];
			}
			
			g_rxflag = 1; //��ʾ���ݽ������
			
			g_count = 0; //��һ���ݴ�g_buffer[0]��ʼ�洢
			
			memset(g_buffer, 0, sizeof(g_buffer));
			
		}
	
		printf("%c", g_buffer[g_count-1]);
		
		//printf("%c\r\n", g_buffer[g_count-1]);
		
	}	
}




int main(void)
{
	uint8_t buf[32]={0};
	
	uint16_t tp_x,tp_y;
	
	uint8_t tp_finger_num=0;
	
	uint8_t tp_sta;
	
	//�жϵ����ȼ����飬һ����Ŀֻ������һ��
	//�ж����ȼ���Ϊ�ڶ��飬��ռ����Χ:0~3  ��Ӧ:0~3
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();
	

	//��ʼ����GPIOF_ODRĬ��Ϊ�͵�ƽ�����Ե���
	Led_Init();
	
	Usart1_Init(115200);

	/* lcd��ʼ�� */
	lcd_init();
	
	/* ����Ϊ��ɫ */
	lcd_clear(WHITE);	
	
	/* ��ʾ���� ���� */
	lcd_set_direction(2);
	
	
	tp_init();
	
	/* ��ʾ���� */
	lcd_show_string(30,140,"TP Test By Teacher.Chen",RED,WHITE,16,0);
	
	
	
	while (1)
	{
		/* ����Ƿ��д������¼����� */
		if(g_tp_event)
		{
			/* �������� */
			while(1)
			{
				/* ����Ƿ��д������¼����� */
				if(g_tp_event == 0)
					continue;
				
				g_tp_event=0;
				
				/* ��ȡ���������ֵ */
				if(tp_sta=tp_read(&tp_x,&tp_y))
				{
					/* ��ʾ��� */
					lcd_fill(tp_x,tp_y,5,5,RED);
					
					/* ����ϴε�����ֵ��ʾ���� */
					lcd_fill(20,g_lcd_height-20,160,20,BLUE);
					
					/* ��ʾ����ֵ */
					sprintf(buf,"x=%d y=%d sta=%02X",tp_x,tp_y,tp_sta);
					printf("%s\r\n",buf);
					lcd_show_string(20,g_lcd_height-20,buf,WHITE,BLUE,16,0);
					
				}		

				if(tp_finger_num_get() == 0)
					break;				
			}
			
			delay_ms(2000);
			
			/* ���� */
			lcd_fill(0,0,g_lcd_width,g_lcd_height,WHITE);
			
			/* ��ʾ���� */
			lcd_show_string(30,140,"TP Test By Teacher.Chen",RED,WHITE,16,0);
		}		
	}
	return 0;
}
