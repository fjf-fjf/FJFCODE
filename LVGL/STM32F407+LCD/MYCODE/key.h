#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"
#include "sys.h"

void Key_PA0_Init(void);
u8 Key_Scan(u8 mode);

#endif
