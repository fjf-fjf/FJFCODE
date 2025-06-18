#include "iwdg.h"


void Iwdg_Init(void)
{
	//ȡ���Ĵ���д������
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	//���ö������Ź���Ԥ��Ƶϵ����ȷ��ʱ��:125HZ
	IWDG_SetPrescaler(IWDG_Prescaler_256);
	//���ÿ��Ź���װ��ֵ��ȷ�����ʱ��:2s(2S�ڱ���ι���������ι�����������)
	IWDG_SetReload(250);
	
	//ʹ�ܿ��Ź�
	IWDG_Enable();
	//Ӧ�ó���ι��:
	IWDG_ReloadCounter();
}