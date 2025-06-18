#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "pwm.h"
#include "motor.h"
#include "smartcar.h"
#include "HCSR04.h"
#include "duoji.h"
#include "EXIT.h"
#include "Bluetooth.h"
#include "mode.h"
#include "linewalking.h"


extern uint8_t avoid_flag; // 避障功能标志位
extern uint8_t Auto_Line_flag; // 循迹功能标志位

float Distance; //障碍物距离

//对PC13引脚进行初始化，用于控制LED灯
void GPIO_led(void)
{
	//对结构体变量进行初始化
	GPIO_InitTypeDef GPIO_InitStructure;

	//使能GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//设置GPIOC的Pin13为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}


int main(void)
{
 
 	 SmartCar_Init();//动力模块初始化
 	 HCSR04_Init();//超声波模块初始化
 	 LineWalking_GPIO_Init(); // 线走模式GPIO初始化
 	UART2_Config(9600);//蓝牙初始化用于连接蓝牙，其中已有中断函数
 	UART1_Config(115200);//串口1初始化用于调试
 	 UART3_Config(9600);//串口3用于和语音助手通信
 	 UART2_SendString("AT\r\n"); //测试指令  响应"OK\r\n"
	 printf("AT\r\n"); //测试指令  响应"OK\r\n"
	Servo_SetAngle(90);//居中超声波舵机
	Servo_SetAngle7(90);//居中摄像头左右舵机
	 Servo_SetAngle8(80);//居中摄像头上下舵机
	//GPIO_led(); //初始化PC13引脚


	while(1)
	{
		//点亮LED灯
//		GPIO_SetBits(GPIOC, GPIO_Pin_13);
//		Delay_ms(500);
//		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//		Delay_ms(500);
		
		

//		Servo_SetAngle7(160);
//		Delay_ms(1000);
//		//Servo_SetAngle7(90);
//		//Delay_ms(1000);
//		Servo_SetAngle7(0);
//		Delay_ms(1000);
		
//		Servo_SetAngle8(10);
//		Delay_ms(1000);
//		Servo_SetAngle8(20);
//		Delay_ms(1000);
//		Servo_SetAngle8(30);
//		Delay_ms(1000);
		
		
//		Servo_SetAngle(0);    // 0度右转
//      Delay_ms(1000); 
//      Servo_SetAngle(90);   // 90度中间
//      Delay_ms(1000);
//      Servo_SetAngle(180);  // 180度左转
//      Delay_ms(1000);

		 // 避障模式
		  if (avoid_flag  == 1)
		  {
			
		  	auto_avoidance_mode(); 
			
		  }
		  // 循迹模式
		  else if (Auto_Line_flag  == 1)
		  {
		 	linewalking_task();
		  }
		
		

		
		
	}
	
	

	

	
	
	
	
	
	
	
	
}

//  // TIM2中断服务函数用于判断标志位是否发生，并执行相应的动作
// void TIM2_IRQHandler(void)
// {
//     if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) // 检查TIM2更新中断是否发生
//     {
//         TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // 清除TIM2更新中断标志位

// 		//Obstacle_Avoidance_Flag = 1; // 避障功能开启
//     }
// }



