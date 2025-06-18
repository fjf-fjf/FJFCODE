#include "rtc.h"

//如果需要重置时间，需要改动BKP的值即可
#define  BKP  0x2504

void Rtc_Init(void)
{
	
	RTC_InitTypeDef		RTC_InitStruct;
	RTC_TimeTypeDef		RTC_TimeStruct;
	RTC_DateTypeDef		RTC_DateStruct;
	//使能PWR时钟：
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	//使能后备寄存器访问,它是断电可保存数据的寄存器 
	PWR_BackupAccessCmd(ENABLE);
	
	//判断后备寄存器值
	//RTC_BKP_DR0:这是一个寄存器
	if(RTC_ReadBackupRegister(RTC_BKP_DR0) != BKP) 
	{
	
		//配置RTC时钟源，使能RTC时钟：
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		//如果使用LSE，要打开LSE：
		RCC_LSEConfig(RCC_LSE_ON);
		
		//等待时钟源稳定
		//方法1
		//delay_ms(20);
		/* Wait till LSE is ready */  
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
		{
		}

		RTC_InitStruct.RTC_HourFormat	= RTC_HourFormat_24; //小时制选择
		RTC_InitStruct.RTC_AsynchPrediv	= 0x7F;		//异步预分频器 128分频
		RTC_InitStruct.RTC_SynchPrediv	= 0xFF;		//同步预分频器 256分频
		//初始化RTC(同步/异步分频系数和时钟格式)：
		RTC_Init(&RTC_InitStruct);	
		RTC_TimeStruct.RTC_H12		= RTC_H12_PM; //下午，在24小时制时，这个参数是无用
		RTC_TimeStruct.RTC_Hours	= 9; //时
		RTC_TimeStruct.RTC_Minutes	= 16; //分
		RTC_TimeStruct.RTC_Seconds	= 10; //秒
		//RTC_Format_BIN,写10进制，硬件自动转换为2进制进行存储
		RTC_SetTime (RTC_Format_BIN, &RTC_TimeStruct);
		
		
		RTC_DateStruct.RTC_Year		= 25; 	//年
		RTC_DateStruct.RTC_Month	= 5;	//月
		RTC_DateStruct.RTC_Date		= 9;	//日
		RTC_DateStruct.RTC_WeekDay  = 5;	//星期
		//设置日期：
		RTC_SetDate(RTC_Format_BIN, &RTC_DateStruct);
	
		//将BKP写入后备寄存器
		RTC_WriteBackupRegister(RTC_BKP_DR0, BKP);
	}
	
}

//闹钟A初始化
void RTC_Alarm_AInit(void)
{
	
	RTC_AlarmTypeDef	RTC_AlarmStruct;
	RTC_TimeTypeDef 	RTC_AlarmTime;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;	
	
	//关闭闹钟：
	RTC_AlarmCmd(RTC_Alarm_A,DISABLE); 
	
	//闹钟时间设置
	RTC_AlarmTime.RTC_H12		= RTC_H12_AM; //上午，在24小时制时，这个参数是无用
	RTC_AlarmTime.RTC_Hours		= 9; //时
	RTC_AlarmTime.RTC_Minutes	= 17; //分
	RTC_AlarmTime.RTC_Seconds	= 10; //秒

	
	RTC_AlarmStruct.RTC_AlarmTime			= RTC_AlarmTime; //时间设置
	RTC_AlarmStruct.RTC_AlarmMask			= RTC_AlarmMask_None;//无掩码位，按实际设置时间来响应
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel	= RTC_AlarmDateWeekDaySel_Date; //按日期响应新课程 
	RTC_AlarmStruct.RTC_AlarmDateWeekDay	= 9;
	
	//配置闹钟参数：
	RTC_SetAlarm(RTC_Format_BIN,RTC_Alarm_A, &RTC_AlarmStruct);
	//开启配置闹钟中断：
	
	
	//配置外部中断控制器
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line17;  			//外部中断线14
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt; 	//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//中断线使能
	EXTI_Init(&EXTI_InitStructure);
	
	//NVIC配置
	NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;   				//通道编号，可在stm32f4xx.h中查看
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; 	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	//开启闹钟A中断
	RTC_ITConfig(RTC_IT_ALRA, ENABLE);
	//开启闹钟：
	RTC_AlarmCmd(RTC_Alarm_A,ENABLE);

}


//闹钟A初始化
void RTC_Alarm_BInit(void)
{
	
	RTC_AlarmTypeDef	RTC_AlarmStruct;
	RTC_TimeTypeDef 	RTC_AlarmTime;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;	
	
	//关闭闹钟：
	RTC_AlarmCmd(RTC_Alarm_B,DISABLE); 
	
	//闹钟时间设置
	RTC_AlarmTime.RTC_H12		= RTC_H12_AM; //上午，在24小时制时，这个参数是无用
	RTC_AlarmTime.RTC_Hours		= 9; //时
	RTC_AlarmTime.RTC_Minutes	= 18; //分
	RTC_AlarmTime.RTC_Seconds	= 10; //秒

	
	RTC_AlarmStruct.RTC_AlarmTime			= RTC_AlarmTime; //时间设置
	RTC_AlarmStruct.RTC_AlarmMask			= RTC_AlarmMask_None;//无掩码位，按实际设置时间来响应
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel	= RTC_AlarmDateWeekDaySel_Date; //按日期响应新课程 
	RTC_AlarmStruct.RTC_AlarmDateWeekDay	= 9;
	
	//配置闹钟参数：
	RTC_SetAlarm(RTC_Format_BIN,RTC_Alarm_B, &RTC_AlarmStruct);
	//开启配置闹钟中断：
	
	
	//配置外部中断控制器
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line17;  			//外部中断线14
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt; 	//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//中断线使能
	EXTI_Init(&EXTI_InitStructure);
	
	//NVIC配置
	NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;   				//通道编号，可在stm32f4xx.h中查看
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; 	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	//开启闹钟B中断
	RTC_ITConfig(RTC_IT_ALRB, ENABLE);
	//开启闹钟：
	RTC_AlarmCmd(RTC_Alarm_B,ENABLE);

}



//闹钟(包括闹钟A与闹钟B)中断服务代码
void RTC_Alarm_IRQHandler(void)
{
	//判断中断线状态，如果有中断，中断位标志为1
	if(EXTI_GetITStatus(EXTI_Line17) == SET)
	{
		//判断闹钟A的标志位是否置1
		if(RTC_GetFlagStatus(RTC_FLAG_ALRAF) == SET)
		{
			//亮灯
			PFout(9) = 0;
			
			//清空标志位
			RTC_ClearFlag(RTC_FLAG_ALRAF);
		}
	
		//判断闹钟B的标志位是否置1
		if(RTC_GetFlagStatus(RTC_FLAG_ALRBF) == SET)
		{
			//灭灯
			PFout(9) = 1;
			
			//清空标志位
			RTC_ClearFlag(RTC_FLAG_ALRBF);
		}		
		
		//清空中断线
		EXTI_ClearITPendingBit(EXTI_Line17);
	}


}




//读取数据
void Rtc_read(void)
{
	RTC_TimeTypeDef		RTC_Timedata;
	RTC_DateTypeDef	 	RTC_Datedata;
	
	RTC_GetTime(RTC_Format_BIN, &RTC_Timedata);
	RTC_GetDate(RTC_Format_BIN, &RTC_Datedata);
	
	printf("20%d年%d月%d日星期%d %d:%d:%d\n",RTC_Datedata.RTC_Year,RTC_Datedata.RTC_Month,RTC_Datedata.RTC_Date, \
	RTC_Datedata.RTC_WeekDay,RTC_Timedata.RTC_Hours,RTC_Timedata.RTC_Minutes,RTC_Timedata.RTC_Seconds);
	//printf("%d骞碶r\n",RTC_Datedata.RTC_Year);

}


