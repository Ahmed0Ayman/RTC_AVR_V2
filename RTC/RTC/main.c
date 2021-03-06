
#include "main.h"



bool ShowTimeStatus = Suspend ;

SemaphoreHandle_t xMutexGoalKeeper;

QueueHandle_t  XMailboxGoalKeeper ;

QueueHandle_t  XQueueSYNC ;


QueueHandle_t  XQueueUpdateRTC ;


TaskHandle_t    ShowTimeTaskhandler ;
TaskHandle_t    ShowDateTaskhandler ;


Time_Typedef  Time ={.Hours =10 ,.Minutes = 20 ,.RTC_Time_Format = RTC_Format_BIN },  \
gettime ={.RTC_Time_Format = RTC_Format_BIN}   ;
Date_Typedef  Date ={.DayDate = 24 ,.Year = 21 ,.month = 10,.RTC_Time_Format = RTC_Format_BIN},\
getdate = {.RTC_Time_Format = RTC_Format_BIN};


int main(void)
{
	
	DS1305_Init();
	S7egment_Init(&S7egHendler);
	RTC_Set_Time(&Time);
	RTC_Set_Date(&Date);
	
	
	InterrutInt();
	EXIT_INT0_CallBack(INT0_Handler);
	EXIT_INT1_CallBack(INT1_Handler);
	EXIT_INT2_CallBack(INT2_Handler);
	
		
	xMutexGoalKeeper = xSemaphoreCreateMutex();	
	
	
	
	XMailboxGoalKeeper  =		xQueueCreate(1,sizeof(RTC_Data));
	
	XQueueSYNC			=		xQueueCreate(1,sizeof(uint8_t));
	
	XQueueUpdateRTC		=		xQueueCreate(1,sizeof(uint8_t));
	
	
	xTaskCreate(ShowTimeTask,NULL,200,NULL,1,&ShowTimeTaskhandler);
	xTaskCreate(ShowDateTask,NULL,200,NULL,1,&ShowDateTaskhandler);	
	xTaskCreate(GoalKeeper_Task,NULL,200,NULL,3,NULL);	
	xTaskCreate(SYNC_Task,NULL,85,NULL,3,NULL);	
	xTaskCreate(UpdateRTC_Task,NULL,100,NULL,4,NULL);	
	
		vTaskStartScheduler();


    /* Replace with your application code */
    while (1) 
    {	

    }
}

/* used to handle Set clock functionality */
void INT0_Handler(void )
{

	 static uint8_t i =0 ;

		xQueueSendFromISR(XQueueSYNC , &i , NULL);
		
		
	if(i++ == 1)
		i=0 ;
}

void INT1_Handler(void )
{
	uint8_t state  =  Increase  ;
	xQueueSendFromISR(XQueueUpdateRTC,&state,NULL);	

}

void INT2_Handler(void )
{
	uint8_t state = Decrease ;
	
	xQueueSendFromISR(XQueueUpdateRTC,&state,NULL);	

}



void SYNC_Task(void  * Param) 
{
int i =0 ;

	while(1)
	{
		xQueueReceive(XQueueSYNC , &i ,portMAX_DELAY);
		if (i == 0)
		{
		
		vTaskSuspend(ShowTimeTaskhandler);
		vTaskResume(ShowDateTaskhandler);
		taskENTER_CRITICAL();
		ShowTimeStatus  =  Suspend ;
		taskEXIT_CRITICAL();
		
		
		}
		else
		{
		vTaskSuspend(ShowDateTaskhandler);
		vTaskResume(ShowTimeTaskhandler);	
		
		taskENTER_CRITICAL();
		ShowTimeStatus  =  Resumed ;	
		taskEXIT_CRITICAL();		
				
			
		}
		vTaskDelay(5);
		
	}

}
