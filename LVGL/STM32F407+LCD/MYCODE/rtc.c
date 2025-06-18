#include "rtc.h"

//�����Ҫ����ʱ�䣬��Ҫ�Ķ�BKP��ֵ����
#define  BKP  0x2504

void Rtc_Init(void)
{
	
	RTC_InitTypeDef		RTC_InitStruct;
	RTC_TimeTypeDef		RTC_TimeStruct;
	RTC_DateTypeDef		RTC_DateStruct;
	//ʹ��PWRʱ�ӣ�
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	//ʹ�ܺ󱸼Ĵ�������,���Ƕϵ�ɱ������ݵļĴ��� 
	PWR_BackupAccessCmd(ENABLE);
	
	//�жϺ󱸼Ĵ���ֵ
	//RTC_BKP_DR0:����һ���Ĵ���
	if(RTC_ReadBackupRegister(RTC_BKP_DR0) != BKP) 
	{
	
		//����RTCʱ��Դ��ʹ��RTCʱ�ӣ�
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		//���ʹ��LSE��Ҫ��LSE��
		RCC_LSEConfig(RCC_LSE_ON);
		
		//�ȴ�ʱ��Դ�ȶ�
		//����1
		//delay_ms(20);
		/* Wait till LSE is ready */  
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
		{
		}

		RTC_InitStruct.RTC_HourFormat	= RTC_HourFormat_24; //Сʱ��ѡ��
		RTC_InitStruct.RTC_AsynchPrediv	= 0x7F;		//�첽Ԥ��Ƶ�� 128��Ƶ
		RTC_InitStruct.RTC_SynchPrediv	= 0xFF;		//ͬ��Ԥ��Ƶ�� 256��Ƶ
		//��ʼ��RTC(ͬ��/�첽��Ƶϵ����ʱ�Ӹ�ʽ)��
		RTC_Init(&RTC_InitStruct);	
		RTC_TimeStruct.RTC_H12		= RTC_H12_PM; //���磬��24Сʱ��ʱ���������������
		RTC_TimeStruct.RTC_Hours	= 9; //ʱ
		RTC_TimeStruct.RTC_Minutes	= 16; //��
		RTC_TimeStruct.RTC_Seconds	= 10; //��
		//RTC_Format_BIN,д10���ƣ�Ӳ���Զ�ת��Ϊ2���ƽ��д洢
		RTC_SetTime (RTC_Format_BIN, &RTC_TimeStruct);
		
		
		RTC_DateStruct.RTC_Year		= 25; 	//��
		RTC_DateStruct.RTC_Month	= 5;	//��
		RTC_DateStruct.RTC_Date		= 9;	//��
		RTC_DateStruct.RTC_WeekDay  = 5;	//����
		//�������ڣ�
		RTC_SetDate(RTC_Format_BIN, &RTC_DateStruct);
	
		//��BKPд��󱸼Ĵ���
		RTC_WriteBackupRegister(RTC_BKP_DR0, BKP);
	}
	
}

//����A��ʼ��
void RTC_Alarm_AInit(void)
{
	
	RTC_AlarmTypeDef	RTC_AlarmStruct;
	RTC_TimeTypeDef 	RTC_AlarmTime;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;	
	
	//�ر����ӣ�
	RTC_AlarmCmd(RTC_Alarm_A,DISABLE); 
	
	//����ʱ������
	RTC_AlarmTime.RTC_H12		= RTC_H12_AM; //���磬��24Сʱ��ʱ���������������
	RTC_AlarmTime.RTC_Hours		= 9; //ʱ
	RTC_AlarmTime.RTC_Minutes	= 17; //��
	RTC_AlarmTime.RTC_Seconds	= 10; //��

	
	RTC_AlarmStruct.RTC_AlarmTime			= RTC_AlarmTime; //ʱ������
	RTC_AlarmStruct.RTC_AlarmMask			= RTC_AlarmMask_None;//������λ����ʵ������ʱ������Ӧ
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel	= RTC_AlarmDateWeekDaySel_Date; //��������Ӧ�¿γ� 
	RTC_AlarmStruct.RTC_AlarmDateWeekDay	= 9;
	
	//�������Ӳ�����
	RTC_SetAlarm(RTC_Format_BIN,RTC_Alarm_A, &RTC_AlarmStruct);
	//�������������жϣ�
	
	
	//�����ⲿ�жϿ�����
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line17;  			//�ⲿ�ж���14
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt; 	//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);
	
	//NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;   				//ͨ����ţ�����stm32f4xx.h�в鿴
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; 	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
	
	//��������A�ж�
	RTC_ITConfig(RTC_IT_ALRA, ENABLE);
	//�������ӣ�
	RTC_AlarmCmd(RTC_Alarm_A,ENABLE);

}


//����A��ʼ��
void RTC_Alarm_BInit(void)
{
	
	RTC_AlarmTypeDef	RTC_AlarmStruct;
	RTC_TimeTypeDef 	RTC_AlarmTime;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;	
	
	//�ر����ӣ�
	RTC_AlarmCmd(RTC_Alarm_B,DISABLE); 
	
	//����ʱ������
	RTC_AlarmTime.RTC_H12		= RTC_H12_AM; //���磬��24Сʱ��ʱ���������������
	RTC_AlarmTime.RTC_Hours		= 9; //ʱ
	RTC_AlarmTime.RTC_Minutes	= 18; //��
	RTC_AlarmTime.RTC_Seconds	= 10; //��

	
	RTC_AlarmStruct.RTC_AlarmTime			= RTC_AlarmTime; //ʱ������
	RTC_AlarmStruct.RTC_AlarmMask			= RTC_AlarmMask_None;//������λ����ʵ������ʱ������Ӧ
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel	= RTC_AlarmDateWeekDaySel_Date; //��������Ӧ�¿γ� 
	RTC_AlarmStruct.RTC_AlarmDateWeekDay	= 9;
	
	//�������Ӳ�����
	RTC_SetAlarm(RTC_Format_BIN,RTC_Alarm_B, &RTC_AlarmStruct);
	//�������������жϣ�
	
	
	//�����ⲿ�жϿ�����
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line17;  			//�ⲿ�ж���14
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt; 	//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);
	
	//NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;   				//ͨ����ţ�����stm32f4xx.h�в鿴
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; 	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
	
	//��������B�ж�
	RTC_ITConfig(RTC_IT_ALRB, ENABLE);
	//�������ӣ�
	RTC_AlarmCmd(RTC_Alarm_B,ENABLE);

}



//����(��������A������B)�жϷ������
void RTC_Alarm_IRQHandler(void)
{
	//�ж��ж���״̬��������жϣ��ж�λ��־Ϊ1
	if(EXTI_GetITStatus(EXTI_Line17) == SET)
	{
		//�ж�����A�ı�־λ�Ƿ���1
		if(RTC_GetFlagStatus(RTC_FLAG_ALRAF) == SET)
		{
			//����
			PFout(9) = 0;
			
			//��ձ�־λ
			RTC_ClearFlag(RTC_FLAG_ALRAF);
		}
	
		//�ж�����B�ı�־λ�Ƿ���1
		if(RTC_GetFlagStatus(RTC_FLAG_ALRBF) == SET)
		{
			//���
			PFout(9) = 1;
			
			//��ձ�־λ
			RTC_ClearFlag(RTC_FLAG_ALRBF);
		}		
		
		//����ж���
		EXTI_ClearITPendingBit(EXTI_Line17);
	}


}




//��ȡ����
void Rtc_read(void)
{
	RTC_TimeTypeDef		RTC_Timedata;
	RTC_DateTypeDef	 	RTC_Datedata;
	
	RTC_GetTime(RTC_Format_BIN, &RTC_Timedata);
	RTC_GetDate(RTC_Format_BIN, &RTC_Datedata);
	
	printf("20%d��%d��%d������%d %d:%d:%d\n",RTC_Datedata.RTC_Year,RTC_Datedata.RTC_Month,RTC_Datedata.RTC_Date, \
	RTC_Datedata.RTC_WeekDay,RTC_Timedata.RTC_Hours,RTC_Timedata.RTC_Minutes,RTC_Timedata.RTC_Seconds);
	//printf("%d年\r\n",RTC_Datedata.RTC_Year);

}


