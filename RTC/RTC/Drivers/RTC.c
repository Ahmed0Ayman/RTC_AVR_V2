/*
 * RTC.c
 *
 * Created: 8/24/2021 7:31:13 PM
 *  Author: Ahmed_Ayman
 */ 


#include "RTC.h"


/* handler to initialize I2c for RTC communications */
static I2C_Handler_t I2cHandler ={.Init.I2C_Clk_Speed = I2C_SPEED_NORMAL,
	.Init.I2C_INIT_MODE = I2C_INIT_DIS ,
	.Init.I2C_SlaveADD = 0xd0 
	 } ;


/* brief : must be call from  main to initialize RTC 
 * param : void 
 * return : void 
*/
void DS1305_Init(void)
{
	I2C_INIT_FUN(&I2cHandler);
	
}/* End_Of DS1305_Init() */


/* brief : this function used to set DS1305 Time 
 * param : Time_Typedef handler struct pointer hold all Time informations 
 * return : void 
 */
void RTC_Set_Time(Time_Typedef * Time)
{
	/* temp handler to hold all actual timing info that will send to DS1305 */
	Time_Typedef TempTime ;
	
	/* check if any need to convert to BCD formate */
	if(Time->RTC_Time_Format == RTC_Format_BIN)
	{
		TempTime.Hours   = Convert_BIN_To_BCD(Time->Hours);
		TempTime.Minutes = Convert_BIN_To_BCD(Time->Minutes);
		TempTime.Seconds = Convert_BIN_To_BCD(Time->Seconds);							
	}else{
		TempTime.Hours   = Time->Hours	  & 0x7f ;
		TempTime.Minutes = Time->Minutes & 0x7f ;
		TempTime.Seconds = Time->Seconds & 0x7f ;
	}

if(Time->RTC_AM_PM != 0u)
{
	
	if(Time->RTC_AM_PM == RTC_Time_PM )	// PM logic high & AM logic low
	TempTime.Hours |= 0x40u ;
	else
	TempTime.Hours |= 0x60u ;
}


/*here we'll send all Time information to DS1305 Module */
HAL_I2C_Mem_Write(&I2cHandler,0xd0,0x00,&TempTime.Seconds,3);
	
	
	
}/* End_Of RTC_Set_Time() */


/* brief : this function used to Get DS1305 Current Time 
 * param : Time_Typedef handler struct pointer hold all Time informations that read from DS1305 
 * return : void 
 */
void RTC_Get_Time(Time_Typedef * Time)
{
	
		Time_Typedef TempTime ;
		
		HAL_I2C_Mem_Read(&I2cHandler,0xd0,0,&TempTime.Seconds,3);
		
					if(!(TempTime.Hours & 0x40))
					{
						Time->Hours   &= 0x7f ;
					}else{
						if(!(TempTime.Hours & 0x40))
						Time->RTC_AM_PM = RTC_Time_AM ;
						else
						Time->RTC_AM_PM = RTC_Time_PM ;
						TempTime.Hours &= 0x1f ;
					}
					TempTime.Minutes &= 0x7f ;
					TempTime.Seconds &= 0x7f ;
					
		/* check the format of the data that requested by the user */			
		if(Time->RTC_Time_Format == RTC_Format_BIN)
		{

			/* read data from DS1305 always in BCD format so first we need if that format is required by the user or not */	
			Time->Hours   = Convert_BCD_To_BIN(TempTime.Hours) ;
			Time->Minutes = Convert_BCD_To_BIN(TempTime.Minutes);
			Time->Seconds = Convert_BCD_To_BIN(TempTime.Seconds);
			
		}else{
			Time->Hours   = TempTime.Hours ;
			Time->Minutes = TempTime.Minutes;
			Time->Seconds = TempTime.Seconds;			
		}
		
	
}/* End_Of RTC_Get_Time() */



/* brief : this function used to Set DS1305 Current Date 
 * param : Date_Typedef handler struct pointer hold all Date informations that will send from DS1305 
 * return : void 
 */
void RTC_Set_Date(Date_Typedef * Date)
{
	Date_Typedef TempDate ;
	
	/* check the format of the data that send by the user in Date_Typedef Var */
	if(Date->RTC_Time_Format == RTC_Format_BIN)
	{
		
		TempDate.DayDate   = Convert_BIN_To_BCD(Date->DayDate);
		TempDate.Year = Convert_BIN_To_BCD(Date->Year);
		TempDate.month = Convert_BIN_To_BCD(Date->month);
		
		}else{
		TempDate.DayDate   = Date->DayDate   & 0x3f ;
		TempDate.Year  = Date->Year  ;
		TempDate.month = Date->month & 0x3f ;
		}
	TempDate.Day = Date->Day;
	
	/* here we'll set up the data For Ds1305 Module */
	HAL_I2C_Mem_Write(&I2cHandler,0xd0,0x03,&TempDate.Day,4);

	
}/* End_Of RTC_Set_Time() */



/* brief : this function used to Get DS1305 Current Date 
 * param : Date_Typedef handler struct pointer hold all Date informations that read from DS1305 
 * return : void 
 */
void RTC_Get_Date(Date_Typedef * Date)
{
	Date_Typedef TempDate ;
			
			HAL_I2C_Mem_Read(&I2cHandler,0xd0,3,&TempDate.Day,4);
			
			if(Date->RTC_Time_Format == RTC_Format_BIN)
			{

				/* read data from DS1305 always in BCD format so first we need if that format is required by the user or not */
				Date->DayDate   = Convert_BCD_To_BIN(TempDate.DayDate) ;
				Date->month = Convert_BCD_To_BIN(TempDate.month);
				Date->Year = Convert_BCD_To_BIN(TempDate.Year);
				
		}
		else{
			Date->DayDate   =TempDate.DayDate ;
			Date->month = TempDate.month;
			Date->Year = TempDate.Year;
		}
			Date->Day   =TempDate.Day ;


}/* End_Of RTC_Get_Date() */





/* brief : this function used to Set DS1305 Current Alarm
 *  param : uint8_t Alarm_Num must be one of DS1305_Alarm....
 * return : void 
 */
void RTC_Set_Alarm(Alarm_Typedef * Alarm , uint8_t Alarm_Num)
{
		Alarm_Typedef TempAlarm ;
		
		if(Alarm->RTC_Time_Format == RTC_Format_BIN)
		{
			
			TempAlarm.Day   = Convert_BIN_To_BCD(Alarm->Day);
			TempAlarm.Seconds = Convert_BIN_To_BCD(Alarm->Seconds);
			TempAlarm.Minutes = Convert_BIN_To_BCD(Alarm->Minutes);
			TempAlarm.Hours   =  Convert_BIN_To_BCD(Alarm->Hours);
			}else{
			TempAlarm.Day   = Alarm->Day ;
			TempAlarm.Seconds  = Alarm->Seconds  ;
			TempAlarm.Minutes = Alarm->Minutes ;
			TempAlarm.Hours   = Alarm->Hours;


		}
		TempAlarm.Day = Alarm->Day;
		HAL_I2C_Mem_Write(&I2cHandler,0xd0,Alarm_Num,&TempAlarm.Seconds,4);
	
	
}



/* brief : this function used to GEt DS1305 Current Alarm
 * param : uint8_t Alarm_Num must be one of DS1305_Alarm....
 * return : void 
 */
void RTC_Get_Alarm(Alarm_Typedef * Alarm, uint8_t Alarm_Num)
{
			Alarm_Typedef TempAlarm ;
			
			
			HAL_I2C_Mem_Read(&I2cHandler,0xd0,Alarm_Num,&TempAlarm.Seconds,3);
			if(Alarm->RTC_Time_Format == RTC_Format_BIN)
			{

				/* read data from DS1305 always in BCD format so first we need if that format is required by the user or not */
				Alarm->Minutes = Convert_BCD_To_BIN(TempAlarm.Minutes);
				Alarm->Seconds = Convert_BCD_To_BIN(TempAlarm.Seconds);
				Alarm->Hours = Convert_BCD_To_BIN(TempAlarm.Hours);				
			}
			else{

				Alarm->Minutes = TempAlarm.Minutes;
				Alarm->Seconds = TempAlarm.Seconds;
				Alarm->Hours =   TempAlarm.Hours;
				
			}
			Alarm->Day   =TempAlarm.Day ;
	
}



/* brief : this function used to Convert Data from BCD to Binary 
 * param : uint8_t the Byte of data that we need to convert it 
 * return : void 
 */
uint8_t Convert_BCD_To_BIN(uint8_t BCD_Num)
{
	uint8_t BCD_Low =0;
	
	
	BCD_Low = 0x0fu & BCD_Num ;
	return ((BCD_Num>>4u)*10 + BCD_Low );
	
}



/* brief : this function used to Convert Data from  Binary to BCD 
 * param : uint8_t the Byte of data that we need to convert it 
 * return : void 
 */
uint8_t Convert_BIN_To_BCD(uint8_t BIN_Num)
{
	
	uint8_t BCD_Low =0;
	
	
	if(BIN_Num > 99u) // check if the wrong data send from the Application
	return 0x99u;
	if(BIN_Num == 0)
	return 0;
	
	BCD_Low = BIN_Num % 10u ;
	BIN_Num /= 10u ;
	return (BIN_Num <<4u | BCD_Low );
	
	
	
}



