/*
 * interrupt.c
 *
 * Created: 10/24/2021 12:46:43 AM
 *  Author: Ahmed_Ayman
 */ 

#include "interrup.h"




EXIT_Handler_t  exti_handler ;



void InterrutInt(void)
{
		exti_handler.EXTI_NUM = EXTI_NUM_0 ;
		exti_handler.EXTI_EDGE_DETECTION = EXTI_EDGE_LOW_LENEL ;
		EXTI_Init(&exti_handler);
		
		exti_handler.EXTI_NUM = EXTI_NUM_1 ;
		exti_handler.EXTI_EDGE_DETECTION = EXTI_EDGE_LOW_LENEL ;
		EXTI_Init(&exti_handler);
		
		exti_handler.EXTI_NUM = EXTI_NUM_2 ;
		exti_handler.EXTI_EDGE_DETECTION = EXTI_EDGE_LOW_LENEL ;
		EXTI_Init(&exti_handler);
		
	
}