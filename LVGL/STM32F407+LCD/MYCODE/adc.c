#include "adc.h"



/************************************
����˵����
�ɵ�����������PA5
ADC12_IN5(ͨ��5)
PA5��ѹ�仯��Χ:0~3.3V

************************************/


void Adc_PA5_Init(void)
{
	//�ṹ�����
	GPIO_InitTypeDef		GPIO_InitStruct;
	ADC_CommonInitTypeDef	ADC_CommonInitStruct;
	ADC_InitTypeDef			ADC_InitStruct;
	
	
	//����PA��ʱ�Ӻ�ADC1ʱ�ӣ�����PA5Ϊģ��ģʽ��
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  
	
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_5; 	//����5
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AN;	//ģ��ģʽ
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_NOPULL; //��������
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	
	ADC_CommonInitStruct.ADC_Prescaler	=  ADC_Prescaler_Div4; //84MHZ/4 = 21MHZ  ADCת��Ƶ�ʲ��ܳ���36MHZ
	ADC_CommonInitStruct.ADC_Mode		= ADC_Mode_Independent; //����ģʽ
	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //��ʹ��DMA
	ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_13Cycles; //��������ADC������� ˫�� �������ز�������
	//��ʼ��ADC_CCR�Ĵ�����
	ADC_CommonInit(&ADC_CommonInitStruct);
	
	
	ADC_InitStruct.ADC_Resolution	= ADC_Resolution_12b;//ADC�ֱ���ѡ�� 4096�ȷ�
	ADC_InitStruct.ADC_DataAlign	= ADC_DataAlign_Right; //�����Ҷ���
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//��ʹ��ɨ��
	ADC_InitStruct.ADC_ContinuousConvMode 	= DISABLE; //����ת��
	ADC_InitStruct.ADC_NbrOfConversion = 1; 	//ת��ͨ����Ŀ
	//ʹ���������,�������������
	ADC_InitStruct.ADC_ExternalTrigConv	  	=	ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStruct.ADC_ExternalTrigConvEdge	=ADC_ExternalTrigConvEdge_None;  //�ޱ��ؼ��
	
	//��ʼ��ADC1����������ADC1�Ĺ���ģʽ�Լ��������е������Ϣ��
	ADC_Init(ADC1, &ADC_InitStruct);
	
	
	//ʹ��ADC��
	 ADC_Cmd(ADC1, ENABLE);
	//���ù���ͨ��������
	//��������:1 ��һ��ת��
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_15Cycles);
	

}

u16 Get_PA5_Adc_Value(void)
{
	u16 value;
	
	//�������ת����
	
	ADC_SoftwareStartConv(ADC1);
	
	//�ȴ�ת����־���
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

	value =  ADC_GetConversionValue(ADC1);
	
	return value;
}

