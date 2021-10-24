/*
 * _7Segmant.h
 *
 * Created: 8/26/2021 12:39:28 PM
 *  Author: Ahmed_Ayman
 */ 

#ifndef S7EGMANT_H_
#define S7EGMANT_H_


#include "HAL_GPIO.h"
#include "avr/io.h"
#define F_CPU 16000000
#include "util/delay.h"

#include "FreeRTOS.h"
#include "task.h"



#define S7eg_One		0x01u
#define S7eg_Two		0x02u
#define S7eg_Three		0x03u
#define S7eg_Four		0x04u
#define S7eg_Five		0x05u

struct _Control{
		GPIO_TypeDef * Port ;
		uint8_t        Pin_Num  ;
	};

typedef struct _Control control_Typedef  ;
typedef struct _Control S7eg_Typedef  ;

typedef struct {
	control_Typedef S7eg_Control[6] ;
	S7eg_Typedef	S7eg_Bits[4]  ;

	}Seg7_Handler;

	
void S7egment_Init(Seg7_Handler *  Segment_Handler);

void S7egment_Write(uint8_t Num , uint8_t S7eg_Num,Seg7_Handler *  Segment_Handler);



















#endif /* S7EGMANT_H_ */