#ifndef __ADC_H
#define __ADC_H

#include "stm32f4xx.h"
#include "sys.h"

void Adc_PA5_Init(void);
u16 Get_PA5_Adc_Value(void);

#endif
