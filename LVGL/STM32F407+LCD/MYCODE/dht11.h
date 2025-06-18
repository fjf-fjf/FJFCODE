#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"



void Dht11_Init(void);
int Dht11_Start(void);
u8 Dht11_Recv_Byte(void);

/*************************************
����˵������ȡ��ʪ�ȣ���У�飩
����ֵ��
�ɹ���0��ʧ�ܣ�-1
u8 *data����������
**************************************/
int Dht11_Data(u8 *data);


#endif
