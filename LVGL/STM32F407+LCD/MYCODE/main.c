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
//粗延时(就是延时不一定准确的意思)

void delay(int n)
{
	int i, j;
	
	for(i=0; i<n; i++)
		for(j=0; j<10000; j++);
}

u8 g_buffer[32] = {0}, g_rxbuffer[32]={0};
u8 g_rxflag = 0;
u8 g_count = 0, g_i = 0;

//每接收一个字节都会进行中断
void USART1_IRQHandler(void)
{
	
	//判断串口接收标志位的标志位
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		//清空标志位，方便接收一位数据
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		//接受数据
		g_buffer[g_count++] = USART_ReceiveData(USART1);
		
		//如果收到数据为':'表示收到结束符
		if(g_buffer[g_count-1] == ':')
		{
			//将g_buffer重新赋值到g_rxbuffer，且过滤结束符
			for(g_i=0; g_i < g_count-1; g_i++)
			{
				g_rxbuffer[g_i] = g_buffer[g_i];
			}
			
			g_rxflag = 1; //表示数据接受完成
			
			g_count = 0; //下一数据从g_buffer[0]开始存储
			
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
	
	//中断的优先级分组，一个项目只能设置一次
	//中断优先级分为第二组，抢占级范围:0~3  响应:0~3
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();
	

	//初始化后GPIOF_ODR默认为低电平，所以灯亮
	Led_Init();
	
	Usart1_Init(115200);

	/* lcd初始化 */
	lcd_init();
	
	/* 清屏为白色 */
	lcd_clear(WHITE);	
	
	/* 显示方向， 竖屏 */
	lcd_set_direction(2);
	
	
	tp_init();
	
	/* 显示标题 */
	lcd_show_string(30,140,"TP Test By Teacher.Chen",RED,WHITE,16,0);
	
	
	
	while (1)
	{
		/* 检测是否有触摸屏事件触发 */
		if(g_tp_event)
		{
			/* 持续访问 */
			while(1)
			{
				/* 检测是否有触摸屏事件触发 */
				if(g_tp_event == 0)
					continue;
				
				g_tp_event=0;
				
				/* 获取点击的坐标值 */
				if(tp_sta=tp_read(&tp_x,&tp_y))
				{
					/* 显示描点 */
					lcd_fill(tp_x,tp_y,5,5,RED);
					
					/* 清除上次的坐标值显示区域 */
					lcd_fill(20,g_lcd_height-20,160,20,BLUE);
					
					/* 显示坐标值 */
					sprintf(buf,"x=%d y=%d sta=%02X",tp_x,tp_y,tp_sta);
					printf("%s\r\n",buf);
					lcd_show_string(20,g_lcd_height-20,buf,WHITE,BLUE,16,0);
					
				}		

				if(tp_finger_num_get() == 0)
					break;				
			}
			
			delay_ms(2000);
			
			/* 清屏 */
			lcd_fill(0,0,g_lcd_width,g_lcd_height,WHITE);
			
			/* 显示标题 */
			lcd_show_string(30,140,"TP Test By Teacher.Chen",RED,WHITE,16,0);
		}		
	}
	return 0;
}
