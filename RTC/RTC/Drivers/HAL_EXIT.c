
/*
 * HAL_EXIT.c
 *
 * Created: 5/8/2021 12:58:33 AM
 *  Author: Ahmed_Ayman
 */ 

#include "HAL_EXIT.h"


/* static pointer to function used by the library */
 PtrFun ptr_Int0 ,ptr_Int1 ,ptr_Int2;



/*
 * brief this function used to enable and configure the selected INIT 
 * param : Handler is pointer to struct hold all INIT configurations 
 * return : void 
 */
void EXTI_Init(EXIT_Handler_t * Handler)
{
	
	if(Handler->EXTI_NUM == EXTI_NUM_2) /* INIT2 only available for edge detection */
	{
		if(Handler->EXTI_EDGE_DETECTION == EXTI_EDGE_FAILING_EDGE)
			MCUCSR &=~(1<<ISC2);
		else
			MCUCSR |= (1<<ISC2);
		
	}else{   /* set configurations for INIT1 or INIT2  */
		
		MCUCR &=~(0x0f);
		if(Handler->EXTI_NUM == EXTI_NUM_0)
		{
		MCUCR |= Handler->EXTI_EDGE_DETECTION;
		}
		else
		{
		MCUCR |= (Handler->EXTI_EDGE_DETECTION<<(2*Handler->EXTI_NUM));
		}
		
	}
	
	
	GICR |= (1<<(5+Handler->EXTI_NUM));  /* enable the required INIT */
	
	sei();
	
}/* END_FUN EXTI_Init()  */




/*
 * brief this function used to call back user function when the INIT0 is triggered
 * param : PtrToFun pointer to  user function  
 * return : void 
 */
void EXIT_INT0_CallBack(PtrFun PtrToFun)
{
	
	ptr_Int0 = PtrToFun ;
	
	
}/* END_FUN EXIT_INT0_CallBack()  */





/*
 * brief this function used to call back user function when the INIT1 is triggered
 * param : PtrToFun pointer to  user function  
 * return : void 
 */
void EXIT_INT1_CallBack(PtrFun PtrToFun)
{
	
	ptr_Int1 = PtrToFun ;
	
}/* END_FUN EXIT_INT1_CallBack()  */





/*
 * brief this function used to call back user function when the INIT2 is triggered
 * param : PtrToFun pointer to  user function  
 * return : void 
 */
void EXIT_INT2_CallBack(PtrFun PtrToFun)
{
	
	ptr_Int2 = PtrToFun ;
	
}/* END_FUN EXIT_INT2_CallBack()  */






/*
 * brief : this function used to generate an software interrupt on a configured pin 
 * param : Handler is a pointer to struct that hold all information a bout the INIT 
 * return : void 
*/  
void EXTI_Gen_SoftWareINIT(EXIT_Handler_t * Handler)
{
	
	if(Handler->EXTI_NUM == EXTI_NUM_0)
		DDRD  |= 0x4 ;
		PORTD |= 0x4 ;
	if(Handler->EXTI_NUM == EXTI_NUM_1)
		DDRD  |= 0x8 ;
		PORTD |= 0x8 ;
	if(Handler->EXTI_NUM == EXTI_NUM_2)
		DDRB  |= 0x4 ;
		PORTB |= 0x4 ;
		
}/* END_FUN EXTI_Gen_SoftWareINIT()  */





/*
 * brief : this function used to disable the determined INIT  
 * param : Handler is a pointer to struct that hold all information a bout the INIT 
 * return : void 
*/  
void EXIT_DISABLE(EXIT_Handler_t * Handler)
{
	GICR &=~(1<<(5+Handler->EXTI_NUM));  /* disable the required INIT */
}


/* INIT0 Function */
ISR(INT0_vect)
{
	ptr_Int0();
}
/* INIT0 Function */
ISR(INT1_vect)
{
	ptr_Int1();
}
/* INIT0 Function */
ISR(INT2_vect)
{
	ptr_Int2();
}