#include "iwdg.h"


void Iwdg_Init(void)
{
	//取消寄存器写保护：
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	//设置独立看门狗的预分频系数，确定时钟:125HZ
	IWDG_SetPrescaler(IWDG_Prescaler_256);
	//设置看门狗重装载值，确定溢出时间:2s(2S内必须喂狗，如果不喂狗，则会重启)
	IWDG_SetReload(250);
	
	//使能看门狗
	IWDG_Enable();
	//应用程序喂狗:
	IWDG_ReloadCounter();
}