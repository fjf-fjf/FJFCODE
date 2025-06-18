#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "tft.h"
#include "bmp.h"
#include "touch.h" 
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_demo_widgets.h"



extern GPIO_InitTypeDef      GPIO_InitStructure;
extern NVIC_InitTypeDef     NVIC_InitStructure;        
extern SPI_InitTypeDef      SPI_InitStructure;



#endif
