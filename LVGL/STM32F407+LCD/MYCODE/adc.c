#include "adc.h"



/************************************
引脚说明：
可调电阻连接在PA5
ADC12_IN5(通道5)
PA5电压变化范围:0~3.3V

************************************/


void Adc_PA5_Init(void)
{
	//结构体变量
	GPIO_InitTypeDef		GPIO_InitStruct;
	ADC_CommonInitTypeDef	ADC_CommonInitStruct;
	ADC_InitTypeDef			ADC_InitStruct;
	
	
	//开启PA口时钟和ADC1时钟，设置PA5为模拟模式。
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  
	
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_5; 	//引脚5
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AN;	//模拟模式
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_NOPULL; //无上下拉
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	
	ADC_CommonInitStruct.ADC_Prescaler	=  ADC_Prescaler_Div4; //84MHZ/4 = 21MHZ  ADC转换频率不能超过36MHZ
	ADC_CommonInitStruct.ADC_Mode		= ADC_Mode_Independent; //独立模式
	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //不使用DMA
	ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_13Cycles; //两个输入ADC采样间隔 双重 或者三重才起作用
	//初始化ADC_CCR寄存器。
	ADC_CommonInit(&ADC_CommonInitStruct);
	
	
	ADC_InitStruct.ADC_Resolution	= ADC_Resolution_12b;//ADC分辨率选择 4096等分
	ADC_InitStruct.ADC_DataAlign	= ADC_DataAlign_Right; //数据右对齐
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//不使用扫描
	ADC_InitStruct.ADC_ContinuousConvMode 	= DISABLE; //单次转换
	ADC_InitStruct.ADC_NbrOfConversion = 1; 	//转换通道数目
	//使用软件触发,下面参数无意义
	ADC_InitStruct.ADC_ExternalTrigConv	  	=	ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStruct.ADC_ExternalTrigConvEdge	=ADC_ExternalTrigConvEdge_None;  //无边沿检测
	
	//初始化ADC1参数，设置ADC1的工作模式以及规则序列的相关信息。
	ADC_Init(ADC1, &ADC_InitStruct);
	
	
	//使能ADC。
	 ADC_Cmd(ADC1, ENABLE);
	//配置规则通道参数：
	//规则序列:1 第一个转换
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_15Cycles);
	

}

u16 Get_PA5_Adc_Value(void)
{
	u16 value;
	
	//开启软件转换：
	
	ADC_SoftwareStartConv(ADC1);
	
	//等待转换标志完成
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

	value =  ADC_GetConversionValue(ADC1);
	
	return value;
}

