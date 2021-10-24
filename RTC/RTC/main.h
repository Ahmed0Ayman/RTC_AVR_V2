/*
 * main.h
 *
 * Created: 10/24/2021 2:37:47 AM
 *  Author: Ahmed_Ayman
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000

#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "mytasks.h"
#include "semphr.h"
#include "queue.h"
#include "RTC.h"
#include "S7egmant.h"
#include "RTCBits.h"
#include "util/delay.h"
#include "interrup.h"




extern Time_Typedef  Time ;
extern Date_Typedef  Date ;
extern Seg7_Handler S7egHendler;


void INT0_Handler(void);
void INT1_Handler(void);
void INT2_Handler(void);


void SYNC_Task(void * Param);









#endif /* MAIN_H_ */