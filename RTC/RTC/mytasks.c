

#include "mytasks.h"

extern SemaphoreHandle_t xMutexGoalKeeper;





extern QueueHandle_t  XQueueGoalKeeper ;

extern QueueHandle_t  XMailboxGoalKeeper ;

extern SemaphoreHandle_t xBinaryShowTimeTask;

extern SemaphoreHandle_t xBinaryShowDateTask;

extern TaskHandle_t    ShowDateTaskhandler ;



extern Seg7_Handler S7egHendler ;


/* main task that functionality is present  Time on the 7 Segment display */
void   ShowTimeTask(void  * param)
{

	
	struct _GoalKeeperStruct  Buf = {0} ;	
			Buf.RTCTime.RTC_Time_Format = RTC_Format_BIN ;

	
	while(1)
	{
			xQueueReceive(XMailboxGoalKeeper, &Buf ,1);	
			S7egment_Write(Buf.RTCTime.Hours  , 0,&S7egHendler);
			S7egment_Write(Buf.RTCTime.Minutes ,2,&S7egHendler);
			S7egment_Write(Buf.RTCTime.Seconds ,4,&S7egHendler);	
			vTaskDelay(1);
		
	}
}

void ShowDateTask(void  * param)
{
	
	
	
struct _GoalKeeperStruct  Buf = {0} ;
	Buf.RTCDate.RTC_Time_Format = RTC_Format_BIN ;
	
	while(1)
	{
			xQueueReceive(XMailboxGoalKeeper, &Buf ,1);			
			S7egment_Write(Buf.RTCDate.Year , 0,&S7egHendler);
			S7egment_Write(Buf.RTCDate.month,2,&S7egHendler);
			S7egment_Write(Buf.RTCDate.DayDate  ,4,&S7egHendler);
			vTaskDelay(1);	
	}	
}

void  GoalKeeper_Task(void * Param)
{
struct _GoalKeeperStruct  Buf = {0} ;
		Buf.RTCDate.RTC_Time_Format = RTC_Format_BIN ;
		Buf.RTCTime.RTC_Time_Format = RTC_Format_BIN ;
		vTaskSuspend(ShowDateTaskhandler);

	while(1)
	{
		/* access I2C non shared resources so we need to protect it through mutex */
		xSemaphoreTake(xMutexGoalKeeper,1);
		RTC_Get_Time(&Buf.RTCTime);
		RTC_Get_Date(&Buf.RTCDate);
		xSemaphoreGive(xMutexGoalKeeper);		
		
		/* use mailbox to send message */
		xQueueOverwrite(XMailboxGoalKeeper,&Buf);
		vTaskDelay(700);
		
	}
}



void SET_Task(void * Param)
{
	
	while(1)
	{
		
		
		
	}
	
}
