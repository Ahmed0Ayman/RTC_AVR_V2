

#ifndef MYTASKS_H_
#define MYTASKS_H_



#include "FreeRTOS.h"
#include "task.h"
#include "mytasks.h"
#include "semphr.h"
#include "queue.h"
#include <stdbool.h>

#include "RTC.h"
#include "S7egmant.h"
#include "RTCBits.h"
#include "main.h"

#define Suspend  0u
#define Resumed  1u


#define Increase  0u
#define Decrease  1u


struct _GoalKeeperStruct
{
	Time_Typedef  RTCTime ;	
	Date_Typedef  RTCDate ;	
}RTC_Data;



void ShowTimeTask( void * Param );
void ShowDateTask(void  * param);
void SET_Task(void * Param);
void GoalKeeper_Task(void * Param);
void UpdateRTC_Task(void * Param);



#endif /* MYTASKS_H_ */