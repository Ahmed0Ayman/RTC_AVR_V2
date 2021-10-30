

#include "mytasks.h"

extern SemaphoreHandle_t xMutexGoalKeeper;



	/* must be local for each function but here I'll made it as one global variable to minimize stack */
struct _GoalKeeperStruct  Buf = {0} ;	  
		
		
extern bool ShowTimeStatus ;


extern QueueHandle_t  XQueueGoalKeeper ;

extern QueueHandle_t  XMailboxGoalKeeper ;

extern QueueHandle_t  XQueueUpdateRTC ;

extern SemaphoreHandle_t xBinaryShowTimeTask;

extern SemaphoreHandle_t xBinaryShowDateTask;

extern TaskHandle_t    ShowDateTaskhandler ;



extern Seg7_Handler S7egHendler ;


/* main task that functionality is present  Time on the 7 Segment display */
void   ShowTimeTask(void  * param)
{

	

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

		Buf.RTCDate.RTC_Time_Format = RTC_Format_BIN ;
		Buf.RTCTime.RTC_Time_Format = RTC_Format_BIN ;
		vTaskSuspend(ShowDateTaskhandler);

	while(1)
	{
		/* access I2C non shared resources so we need to protect it through mutex */
		xSemaphoreTake(xMutexGoalKeeper,portMAX_DELAY);
		RTC_Get_Time(&Buf.RTCTime);
		RTC_Get_Date(&Buf.RTCDate);
		xSemaphoreGive(xMutexGoalKeeper);		
		
		/* use mailbox to send message */
		xQueueOverwrite(XMailboxGoalKeeper,&Buf);
		vTaskDelay(400);
		
	}
}



void UpdateRTC_Task(void * Param)
{
	
	uint8_t state = 0;
	while(1)
	{
		xQueueReceive(XQueueUpdateRTC,&state,portMAX_DELAY);
		xSemaphoreTake(xMutexGoalKeeper,portMAX_DELAY);		/* must take mutex before enter critical section (I2C)*/
		RTC_Get_Time(&Buf.RTCTime);
		RTC_Get_Date(&Buf.RTCDate);
		taskENTER_CRITICAL();
	if(state == Decrease)
	{
		if(ShowTimeStatus == Suspend)  // increase time
		{
				Buf.RTCTime.Seconds--;	
		}
		else   // increase date 
		{
				Buf.RTCDate.DayDate--;
		}
	}else
	{
		
		if(ShowTimeStatus == Suspend)  // increase time
		{
			Buf.RTCTime.Seconds++;
		}
		else   // increase date
		{
			Buf.RTCDate.DayDate++;
		}
		
	}
		taskEXIT_CRITICAL();
		
		
		
		RTC_Set_Time(&Buf.RTCTime);
		RTC_Set_Date(&Buf.RTCDate);
		xSemaphoreGive(xMutexGoalKeeper);		
		
	}
	
}



