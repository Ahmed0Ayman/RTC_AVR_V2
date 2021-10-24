/*
 * _7Segmant.c
 *
 * Created: 8/26/2021 12:39:18 PM
 *  Author: Ahmed_Ayman
 */ 

#include "S7egmant.h"



	
void S7egment_Init(Seg7_Handler *  Segment_Handler)
{
		GPIO_InitTypeDef  S7eg_PIN_CONFIG ;

	
	S7eg_PIN_CONFIG.mode = GPIO_MODE_OUTPUT ;
	S7eg_PIN_CONFIG.pull = GPIO_NOPULL ;
	/*initialize all control bits  */
	for (int i=0 ; i < 6 ;i++ )
	{
		S7eg_PIN_CONFIG.pinS = Segment_Handler->S7eg_Control[i].Pin_Num ;	
		HAL_GPIO_INIT_PIN(Segment_Handler->S7eg_Control[i].Port,&S7eg_PIN_CONFIG);	
	}


	/*initialize 7 segment BCD Bits */	
	for (int i=0 ; i < 4 ;i++ )
	{
		S7eg_PIN_CONFIG.pinS = Segment_Handler->S7eg_Bits[i].Pin_Num;
		HAL_GPIO_INIT_PIN(Segment_Handler->S7eg_Bits[i].Port,&S7eg_PIN_CONFIG);
	}	
	
	
	
}
void S7egment_Write(uint8_t Num_To_S7eg , uint8_t S7eg_Num,Seg7_Handler *  Segment_Handler)
{


	uint8_t High_Num=0,Low_Num=0 ;
	Low_Num = Num_To_S7eg % 10 ;
	if (Num_To_S7eg == 0)
	{
		
	}
	else
	{
	Num_To_S7eg /= 10 ;
	if (Num_To_S7eg > 0){
		High_Num = Num_To_S7eg % 10 ;
		}else{
		High_Num = 0 ;
	}
	}

	for(int i =0 ;i<4 ;i++)
	HAL_GPIO_WRITEPIN(Segment_Handler->S7eg_Bits[i].Port,Segment_Handler->S7eg_Bits[i].Pin_Num,(High_Num>>i)&(0x01));
	HAL_GPIO_WRITEPIN(Segment_Handler->S7eg_Control[S7eg_Num].Port,Segment_Handler->S7eg_Control[S7eg_Num].Pin_Num,1);
	vTaskDelay(1);
	HAL_GPIO_WRITEPIN(Segment_Handler->S7eg_Control[S7eg_Num].Port,Segment_Handler->S7eg_Control[S7eg_Num].Pin_Num,0);

	
	for(int i =0 ;i<4 ;i++)
	HAL_GPIO_WRITEPIN(Segment_Handler->S7eg_Bits[i].Port,Segment_Handler->S7eg_Bits[i].Pin_Num,(Low_Num>>i)&(0x01));
	HAL_GPIO_WRITEPIN(Segment_Handler->S7eg_Control[S7eg_Num+1].Port,Segment_Handler->S7eg_Control[S7eg_Num+1].Pin_Num,1);
	vTaskDelay(6);	
	HAL_GPIO_WRITEPIN(Segment_Handler->S7eg_Control[S7eg_Num+1].Port,Segment_Handler->S7eg_Control[S7eg_Num+1].Pin_Num,0);
}