#ifndef __TIM_H
#define __TIM_H

#include "stm32f4xx.h"


void Tim3_Init(void);
void Tim3_NoISR_Init(u32 Period);

#endif
