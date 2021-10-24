/*
 * RTC.h
 *
 * Created: 8/24/2021 7:31:29 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef RTC_H_
#define RTC_H_


#include "HAL_I2c.h"
#include "HAL_GPIO.h"


#define RTC_Time_Format_24			0x00u
#define RTC_Time_Format_12			0x01u



#define RTC_Format_BCD				0x01u
#define RTC_Format_BIN				0x02u




#define RTC_Time_AM					0x01u
#define RTC_Time_PM					0x02u



#define RTC_Date_Month_January		0x01u
#define RTC_Date_Month_Fabraury		0x02u
#define RTC_Date_Month_March		0x03u
#define RTC_Date_Month_April		0x04u
#define RTC_Date_Month_May			0x05u
#define RTC_Date_Month_June			0x06u
#define RTC_Date_Month_July			0x07u
#define RTC_Date_Month_August		0x08u
#define RTC_Date_Month_September	0x09u
#define RTC_Date_Month_October		0x010u
#define RTC_Date_Month_November		0x011u
#define RTC_Date_Month_December		0x012u



#define RTC_Date_Day_Saturday       0x01u
#define RTC_Date_Day_Sunday			0x02u
#define RTC_Date_Day_Monday			0x03u
#define RTC_Date_Day_Tuseday		0x04u
#define RTC_Date_Day_Wensday		0x05u
#define RTC_Date_Day_Thrusday       0x06u
#define RTC_Date_Day_Friday			0x07u


#define DS1305_Addr					0xd0u



#define DS1305_Alarm0				0x07u
#define DS1305_Alarm1				0x0Bu



typedef struct {

		uint8_t Seconds ;
		uint8_t Minutes ;
 		uint8_t Hours ;
		 
		uint8_t RTC_Time_Format ;  /* must be one of RTC_Format_...*/
		uint8_t RTC_AM_PM ;			/* must be one of RTC_Time_...*/
	
}Time_Typedef;

typedef struct {

	uint8_t Day ;				/** must be one of  RTC_Date_Day_ */
	uint8_t DayDate;			/*  must be from   0-31 */
	uint8_t month ;				/*  must be one of RTC_Date_Month_  */
	uint8_t  Year ;				/* must be from 0-99 */
	uint8_t RTC_Time_Format ;	  /* must be one of RTC_Format_...*/
	
}Date_Typedef;

typedef struct {
	uint8_t Seconds;
	uint8_t Minutes ;
	uint8_t  Hours ;	
	uint8_t Day ;				/** must be one of  RTC_Date_Day_ */
	uint8_t RTC_Time_Format ;	  /* must be one of RTC_Format_...*/
	
}Alarm_Typedef;




/* brief : must be call from  main to initialize RTC 
 * param : void 
 * return : void 
*/
void DS1305_Init(void);




/* brief : this function used to set DS1305 Time 
 * param : Time_Typedef handler struct pointer hold all Time informations 
 * return : void 
 */
void RTC_Set_Time(Time_Typedef * Time);



/* brief : this function used to Get DS1305 Current Time 
 * param : Time_Typedef handler struct pointer hold all Time informations that read from DS1305 
 * return : void 
 */
void RTC_Get_Time(Time_Typedef * Time);




/* brief : this function used to Set DS1305 Current Date 
 * param : Date_Typedef handler struct pointer hold all Date informations that will send from DS1305 
 * return : void 
 */
void RTC_Set_Date(Date_Typedef * Date);




/* brief : this function used to Get DS1305 Current Date 
 * param : Date_Typedef handler struct pointer hold all Date informations that read from DS1305 
 * return : void 
 */
void RTC_Get_Date(Date_Typedef * Date);





/* brief : this function used to Set DS1305 Current Alarm
 *  param : uint8_t Alarm_Num must be one of DS1305_Alarm....
 * return : void 
 */
void RTC_Set_Alarm(Alarm_Typedef * Time , uint8_t Alarm_Num);




/* brief : this function used to GEt DS1305 Current Alarm
 * param : uint8_t Alarm_Num must be one of DS1305_Alarm....
 * return : void 
 */
void RTC_Get_Alarm(Alarm_Typedef * Time , uint8_t Alarm_Num);





/* brief : this function used to Convert Data from BCD to Binary 
 * param : uint8_t the Byte of data that we need to convert it 
 * return : void 
 */
uint8_t Convert_BCD_To_BIN(uint8_t BCD);





/* brief : this function used to Convert Data from  Binary to BCD 
 * param : uint8_t the Byte of data that we need to convert it 
 * return : void 
 */
uint8_t Convert_BIN_To_BCD(uint8_t BCD);



#endif /* RTC_H_ */