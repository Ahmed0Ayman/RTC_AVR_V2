/*
 * HAL_GPIO.c
 *
 * Created: 4/12/2021 3:13:45 PM
 *  Author: Ahmed_Ayman
 */ 


#include "HAL_GPIO.h"




/*
 * brief  : this function used to initialize GPIO port 
 * param. : PORT pointer to GPIO port
 * param. : PIN_CONFIG pointer to struct hold all configuration
 * return : void 
 */
void HAL_GPIO_INIT_PIN(GPIO_TypeDef * PORT, GPIO_InitTypeDef *  PIN_CONFIG)
{

		if(PIN_CONFIG->mode == GPIO_MODE_OUTPUT)
		{
			PORT->DDR_REG  |= PIN_CONFIG->pinS ;      //SET ALL PINS AS OUTPUT
			if(PIN_CONFIG->pull == GPIO_PULLUP)
			{
			PORT->PORT_REG |= PIN_CONFIG->pinS ;     // SET PULL UP RES.
			}
		}else{  // PINS MODE CONFIGURED AS INPUT
			
			PORT->DDR_REG &= ~(PIN_CONFIG->pinS);
		}

}/* END_FUN HAL_GPIO_INIT_PIN()*/




/*
 * brief  : this function used to read the specific pin 
 * param. : PORT pointer to GPIO port
 * param. : PIN_NUM the pin number must be one of GPIO_PIN_ 
 * return : return on of  GPIO_PIN_RESET or GPIO_PIN_SET 
 */
GPIO_PinState HAL_GPIO_READPIN(GPIO_TypeDef * PORT,uint8_t PIN_NUM)
{
	if(PORT->PIN_REG & PIN_NUM)  /* check if specific pin is set */
	{
		return GPIO_PIN_SET ;
	}
	else              /* if read pin is zero */
	{
		return GPIO_PIN_RESET ;
	}
}/* END_FUN HAL_GPIO_READPIN()*/



/*
 * brief  : this function used to write specific value to specific pin 
 * param. : PORT pointer to GPIO port
 * param. : PIN_NUM the pin number must be one of GPIO_PIN_ 
 * param. : PIN_NUM the pin number must be one of GPIO_PIN_RESET or GPIO_PIN_SET
 * return : void  
 */
void HAL_GPIO_WRITEPIN(GPIO_TypeDef * PORT,uint8_t PIN_NUM,GPIO_PinState PIN_STATE)
{
	if(PIN_STATE != GPIO_PIN_RESET)
	{
		PORT->PORT_REG |= PIN_NUM ;
	}
	else
	{
		PORT->PORT_REG &= ~(PIN_NUM);
	}
	
}/* END_FUN HAL_GPIO_WRITEPIN()*/




/*
 * brief  : this function used to write specific value to specific port 
 * param. : PORT pointer to GPIO port
 * param. : PINS  the pins need to write this value to  
 * param. : PINS_STATE the pins state 
 * return : void  
 */
void HAL_GPIO_WRITEPORT(GPIO_TypeDef * PORT,uint8_t PINS,GPIO_PinState PINS_Value,uint8_t Pins_Mask)
{
	PORT->PORT_REG &=~(PINS);
	PORT->PORT_REG |=(PINS_Value & Pins_Mask);
}/* END_FUN HAL_GPIO_WRITEPORT()*/





/*
 * brief  : this function used to toggle the specific pin 
 * param. : PORT pointer to GPIO port
 * param. : PIN_NUM the pin number must be one of GPIO_PIN_ 
 * return : void  
 */
void HAL_GPIO_TOGGLE_PIN(GPIO_TypeDef * PORT,uint8_t PIN_NUM)
{
	    uint8_t old_state = PORT->PIN_REG;
		PORT->PORT_REG = (~((old_state)&(PIN_NUM))&(PIN_NUM));
			   
}/* END_FUN HAL_GPIO_TOGGLE_PIN()*/



/*
 * brief  : this function used to initialize sleep mode in MCU
 * param. : SleepModeInit pointer to struct hold sleep mode config
 * return : void 
 */
void HAL_GPIO_SLEEP_MODE_INIT(SleepModeConf * SleepModeInit)
{


	GICR |= SleepModeInit->WakeUpSource ;  /* enable external interrupt */ 
	if(SleepModeInit->WakeUpSource  == SLEEP_SOURCE_INT1)
	MCUCR |= (SleepModeInit->IntLevelSense) << 2;    /* select the INT1 interrupt level*/ 
	else if((SleepModeInit->WakeUpSource)  == SLEEP_SOURCE_INT0)
	MCUCR |= SleepModeInit->IntLevelSense ;		/* select the INT0  interrupt level */
	else
	MCUCSR |= SleepModeInit->IntLevelSense << 6 ;   /* set INT2 level */

	MCUCR |= SleepModeInit->Sleep_Mode << 4;

	SREG |= 0x80;    /* set I bit enable global interrupt */
	
	
}/* END_FUN HAL_GPIO_SLEEP_MODE_INIT()*/



/*
 * brief  : this function used to enter sleep mode 
 * return : void 
 */
void SleepModeEnter(void)
{
__asm__ __volatile__ ( "sleep\n\t" :: );   /* call sleep instruction inline asm */ 


}/* END_FUN SleepModeEnter()*/



/*
 * brief  : this function used to disable sleep mode  
 * return : void 
 */
void SleepModeDisable(void)
{
	MCUCR &= 0x7f;  /* set SE bit to enable sleep mode */
	
	
}/* END_FUN SleepModeDisable()*/




/*
 * brief  : this function used to enable sleep mode  
 * return : void 
 */
void SleepModeEnable(void)
{
	MCUCR |= 0x80;  /* set SE bit to enable sleep mode  */
	
}/* END_FUN SleepModeEnable()*/
