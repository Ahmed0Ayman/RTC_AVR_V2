/*
 * HAL_GPIO.h
 *
 * Created: 4/12/2021 3:14:06 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

#include "GPIO_TYPEDEF.h"
#include <avr/io.h>
#include <avr/sleep.h>

typedef struct 
{
	uint8_t pinS ;  /* select one of GPIO_PIN_ */
	uint8_t mode ;  /* select one of GPIO_MODE_ */
	uint8_t pull ;  /* elect one of GPIO_NOPULL or GPIO_PULLUP */

}GPIO_InitTypeDef; /* typedef struct used to hold the chosen bit configuration */ 

typedef struct    
{
	uint8_t Sleep_Mode ;     /* select one of SLEEP_MODE_ */
	uint8_t WakeUpSource ;   /* select one of SLEEP_SOURCE */
	uint8_t IntLevelSense ;   /* select one of INT1_LEVEL_ */

}SleepModeConf;   /* typedef struct hold the info. about the selected sleep mode */

typedef enum
{
	GPIO_PIN_RESET = 0,
	GPIO_PIN_SET   =1
}GPIO_PinState;


#define GPIO_PIN_0						0X01U
#define GPIO_PIN_1						0X02U
#define GPIO_PIN_2						0X04U
#define GPIO_PIN_3						0X08U
#define GPIO_PIN_4						0X10U
#define GPIO_PIN_5						0X20U
#define GPIO_PIN_6						0X40U
#define GPIO_PIN_7						0X80U
#define GPIO_PIN_AL						0XFFU

#define GPIO_MODE_INPUT					0X00U
#define GPIO_MODE_OUTPUT				0X01U


#define  GPIO_NOPULL					0X00U
#define  GPIO_PULLUP					0X01U





/* IN data sheet their is a multiple sources 
* can wake up the MCU but the external interrupt in 
* a common one between all modes */
#define SLEEP_SOURCE_INT0         0X40U  

#define SLEEP_SOURCE_INT1         0X80U  

#define SLEEP_SOURCE_INT2         0X20U  



#define INT1_LEVEL_0_LOW           0X00U

#define INT1_LEVEL_0_ANY           0X01U

#define INT1_LEVEL_0_RISING_EDGE         0X02U

#define INT1_LEVEL_0_FAILING_EDGE       0X03U

#define INT2_LEVEL_FAILING_EDGE         0X00U
 
#define INT2_LEVEL_RISING_EDGE           0X01U


/*
 * brief  : this function used to initialize GPIO port 
 * param. : PORT pointer to GPIO port
 * param. : PIN_CONFIG pointer to struct hold all configuration
 * return : void 
 */
void HAL_GPIO_INIT_PIN(GPIO_TypeDef * PORT, GPIO_InitTypeDef *  PIN_CONFIG);

/*
 * brief  : this function used to read the specific pin 
 * param. : PORT pointer to GPIO port
 * param. : PIN_NUM the pin number must be one of GPIO_PIN_ 
 * return : return on of  GPIO_PIN_RESET or GPIO_PIN_SET 
 */
GPIO_PinState HAL_GPIO_READPIN(GPIO_TypeDef * PORT,uint8_t PIN_NUM);

/*
 * brief  : this function used to write specific value to specific pin 
 * param. : PORT pointer to GPIO port
 * param. : PIN_NUM the pin number must be one of GPIO_PIN_ 
 * param. : PIN_NUM the pin number must be one of GPIO_PIN_RESET or GPIO_PIN_SET
 * return : void  
 */
void HAL_GPIO_WRITEPIN(GPIO_TypeDef * PORT,uint8_t PIN_NUM,GPIO_PinState PIN_STATE);

/*
 * brief  : this function used to toggle the specific pin 
 * param. : PORT pointer to GPIO port
 * param. : PIN_NUM the pin number must be one of GPIO_PIN_ 
 * return : void  
 */
void HAL_GPIO_TOGGLE_PIN(GPIO_TypeDef * PORT,uint8_t PIN_NUM);




/*
 * brief  : this function used to write specific value to specific port 
 * param. : PORT pointer to GPIO port
 * param. : PINS  the pins need to write this value to  
 * param. : PINS_STATE the pins state 
 * return : void  
 */
void HAL_GPIO_WRITEPORT(GPIO_TypeDef * PORT,uint8_t PINS,GPIO_PinState PINS_Value,uint8_t Pins_Mask);


/*
 * brief  : this function used to disable sleep mode  
 * return : void 
 */
void SleepModeDisable(void);

/*
 * brief  : this function used to enter sleep mode 
 * return : void 
 */
void SleepModeEnter(void);

/*
 * brief  : this function used to initialize sleep mode in MCU
 * param. : SleepModeInit pointer to struct hold sleep mode config
 * return : void 
 */
void HAL_GPIO_SLEEP_MODE_INIT(SleepModeConf * SleepModeInit);

/*
 * brief  : this function used to enable sleep mode  
 * return : void 
 */
void SleepModeEnable(void);




#endif /* HAL_GPIO_H_ */
