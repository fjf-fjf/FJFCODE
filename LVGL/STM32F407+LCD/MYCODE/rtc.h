#ifndef __RTC_H
#define __RTC_H


#include "stm32f4xx.h"
#include "delay.h"
#include "stdio.h"
#include "sys.h"

void Rtc_Init(void);
void Rtc_read(void);
void RTC_Alarm_AInit(void);
void RTC_Alarm_BInit(void);
#endif