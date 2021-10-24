/*
 * GPIO_TYPEDEF.h
 *
 * Created: 4/12/2021 3:45:55 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef HAL_TYPEDEF_H_
#define HAL_TYPEDEF_H_
#include <stdint.h>


typedef struct 
{
	uint8_t PIN_REG;
	uint8_t DDR_REG;
	uint8_t PORT_REG;	
}GPIO_TypeDef;


#define PORTD_BASE						0X30U 
#define PORTC_BASE						0X33U 
#define PORTA_BASE						0X39U
#define PORTB_BASE						0X36U
#define  ADC_BASE						0X24U


#define SetBit(REG,BIT)            ((REG) |=(BIT))            
#define ReadBit(REG,BIT)           (((REG)&(BIT))>>(BIT))
#define ClearBit(REG,BIT)          ((REG) &=~(BIT))
#define ClearREG(REG)              (REG=0x00U)
#define ReadREG(REG)               ((REG))



#define GPIOA				((GPIO_TypeDef  *) PORTA_BASE)
#define GPIOB				((GPIO_TypeDef  *) PORTB_BASE)
#define GPIOC				((GPIO_TypeDef  *) PORTC_BASE)
#define GPIOD				((GPIO_TypeDef  *) PORTD_BASE)








#endif /* TYPEDEF_H_ */