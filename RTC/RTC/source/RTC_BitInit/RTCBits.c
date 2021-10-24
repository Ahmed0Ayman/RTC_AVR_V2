/*
 * RTCBits.c
 *
 * Created: 10/23/2021 12:12:08 PM
 *  Author: Ahmed_Ayman
 */ 
#include "RTCBits.h"



/* here we have struct that initialize all bits required for 7 segments bits this makes our code more flexable */ 
Seg7_Handler S7egHendler = {
	
/* each bit has two attributes Port and Pin number */
.S7eg_Bits[S7eg_Bit0].Port = GPIOC ,
.S7eg_Bits[S7eg_Bit0].Pin_Num = GPIO_PIN_4 ,
.S7eg_Bits[S7eg_Bit1].Port = GPIOC ,
.S7eg_Bits[S7eg_Bit1].Pin_Num = GPIO_PIN_5 ,
.S7eg_Bits[S7eg_Bit2].Port = GPIOC ,
.S7eg_Bits[S7eg_Bit2].Pin_Num = GPIO_PIN_6 ,
.S7eg_Bits[S7eg_Bit3].Port = GPIOC ,
.S7eg_Bits[S7eg_Bit3].Pin_Num = GPIO_PIN_7 ,


.S7eg_Control[S7eg_ControlBit0].Port = GPIOA ,
.S7eg_Control[S7eg_ControlBit0].Pin_Num = GPIO_PIN_0 ,
.S7eg_Control[S7eg_ControlBit1].Port = GPIOA ,
.S7eg_Control[S7eg_ControlBit1].Pin_Num = GPIO_PIN_1 ,
.S7eg_Control[S7eg_ControlBit2].Port = GPIOA ,
.S7eg_Control[S7eg_ControlBit2].Pin_Num = GPIO_PIN_2, 
.S7eg_Control[S7eg_ControlBit3].Port = GPIOA ,
.S7eg_Control[S7eg_ControlBit3].Pin_Num = GPIO_PIN_3 ,
.S7eg_Control[S7eg_ControlBit4].Port = GPIOA ,
.S7eg_Control[S7eg_ControlBit4].Pin_Num = GPIO_PIN_4 ,
.S7eg_Control[S7eg_ControlBit5].Port = GPIOA ,
.S7eg_Control[S7eg_ControlBit5].Pin_Num = GPIO_PIN_5 ,

	
	
};


	
	
	