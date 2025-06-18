#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"



void Dht11_Init(void);
int Dht11_Start(void);
u8 Dht11_Recv_Byte(void);

/*************************************
函数说明：获取温湿度（带校验）
返回值：
成功：0，失败：-1
u8 *data：传入数组
**************************************/
int Dht11_Data(u8 *data);


#endif
