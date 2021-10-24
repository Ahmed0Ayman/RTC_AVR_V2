/*
 * I_C.c
 *
 * Created: 4/26/2021 5:14:47 PM
 *  Author: Ahmed_Ayman
 */ 

#include "HAL_I2c.h"


static uint8_t IS_Current_opreration;
static uint8_t SLAVE_ADD ;

typedef enum {MasterTransmitMode = 0x01,MasterReceiveMode,SlaveTransmitMode,SlaveReceiveMode,ReadyMode}CurrOper;





void I2C_INIT_FUN(I2C_Handler_t * Handler)
{
	// INIT. i2c peripheral
	I2C->I2C_TWBR = ((((uint64_t)F_CPU)/(uint64_t)(Handler->Init.I2C_Clk_Speed))-16)/2;
	I2C->I2C_TWAR = Handler->Init.I2C_SlaveADD;
	I2C->I2C_TWCR = 0x00 ;
	I2C->I2C_TWSR = 0x00 ;
	
	if(Handler->Init.I2C_INIT_MODE == I2C_INIT_EN)
	{
	sei();
	I2C->I2C_TWCR |= 0x01 ;
	}else{
	I2C->I2C_TWCR &= ~0x01 ;	
	}
}

/* brief  @ : this function used to transmit data in master transmit mode
 * param. @ : handler this handler of I2c peripheral 
 * param. @ : DevAdd this is the address of the slave device that you want to communicate with
 * param. @ : pTxData this is pointer to the buffer that will hold the transmitted data 
 * param. @ : DataSize number of bytes that you need to read 
*/ 
I2C_STATUS HAL_I2C_Master_Transmit(I2C_Handler_t * Handler,uint8_t DevAdd ,uint8_t * PTxData,uint8_t DataSize)
{

	Handler->buffer = PTxData ;
	Handler->Size   = DataSize;
	
	I2C_EN_START();
	while((I2C->I2C_TWCR & 0x80)==0);
	I2C->I2C_TWDR = DevAdd;
	I2C_EN();
	while(!(I2C->I2C_TWCR & 0x80));
	while(Handler->Size-- > 1)
	{
		I2C->I2C_TWDR = *(Handler->buffer++) ;
		I2C_EN();
		while(!(I2C->I2C_TWCR & 0x80));
	}
	I2C_EN_STOP();
	while(!(I2C->I2C_TWCR & 0x80));

	return I2C_NORMAL;	
}


/* brief  @ : this function used to transmit data in master receive mode
 * param. @ : handler this handler of I2c peripheral 
 * param. @ : DevAdd this is the address of the slave device that you want to communicate with
 * param. @ : pTxData this is pointer to the buffer that will hold the transmitted data 
 * param. @ : DataSize number of bytes that you need to read 
*/ 
I2C_STATUS HAL_I2C_Master_Receive(I2C_Handler_t * Handler ,uint8_t DevAdd  ,uint8_t * pTxData ,uint8_t DataSize )
{
	
	Handler->buffer = pTxData ;
	Handler->Size   = DataSize;
	
	I2C_EN();
	while(!(I2C->I2C_TWCR & 0x80));
	I2C->I2C_TWDR =( DevAdd | 1);
	I2C_EN();
	while(!(I2C->I2C_TWCR & 0x80));
	while(Handler->Size-- > 1)
	{
		I2C_EN();
		while(!(I2C->I2C_TWCR & 0x80));
		I2C->I2C_TWDR = *(Handler->buffer++) ;		
	}
	I2C_EN_STOP();

	return I2C_NORMAL;
}


/* brief  @ : this function used to receive data in slave mode
 * param. @ : handler this handler of I2c peripheral 
 * param. @ : DevAdd this is the address of the slave device that you want to communicate with
 * param. @ : pRxData this is pointer to the buffer that will hold the transmitted data 
 * param. @ : DataSize number of bytes that you need to receive 
*/ 
I2C_STATUS HAL_I2C_Slave_Transmit(I2C_Handler_t * Handler  ,uint8_t * pRxData ,uint8_t DataSize )
{
	Handler->buffer = pRxData ;
	Handler->Size   = DataSize;
	
	I2C_EN_ACK();
	while((I2C->I2C_TWCR & 0x80) != 0);
	while(Handler->Size-- >1)       
	{
		I2C_EN_ACK();
		while((I2C->I2C_TWCR & 0x80) != 0);
		*(Handler->buffer++) = I2C->I2C_TWDR ;
	}
	I2C_EN_NACK() ;
	while((I2C->I2C_TWCR & 0x80) != 0);
	return I2C_NORMAL;
}


I2C_STATUS HAL_I2C_Slave_Receive(I2C_Handler_t * Handler  ,uint8_t * pTxData,uint8_t DataSize )
{
		Handler->buffer = pTxData ;
		Handler->Size   = DataSize;
		
		I2C_EN_ACK();
		while((I2C->I2C_TWCR & 0x80) != 0);
		while(Handler->Size-- >1)
		{
			I2C->I2C_TWDR = *(Handler->buffer++);
			I2C_EN_ACK();
			while((I2C->I2C_TWCR & 0x80) != 0);
		}
		I2C_EN_NACK() ;
		while((I2C->I2C_TWCR & 0x80) != 0);
	
	return I2C_NORMAL;	
}




I2C_STATUS HAL_I2C_Master_Transmit_IT(I2C_Handler_t * Handler ,uint8_t DevAdd ,uint8_t * pTxData,uint8_t DataSize )
{
	
	if(IS_Current_opreration == ReadyMode)
	{
	Handler->buffer = pTxData ;
	Handler->Size   = DataSize;
	SLAVE_ADD = DevAdd ;
	I2C_EN_START();
	IS_Current_opreration = MasterTransmitMode; 
	}
	return I2C_NORMAL;	
}


I2C_STATUS HAL_I2C_Master_Receive_IT(I2C_Handler_t * Handler ,uint8_t DeviceAdd  ,uint8_t * pRxData ,uint8_t DataSize )
{
	
	return I2C_NORMAL;	
}

I2C_STATUS HAL_I2C_Slave_Transmit_IT(I2C_Handler_t * Handler  ,uint8_t * pTxData,uint8_t DataSize )
{
	
	
	return I2C_NORMAL;	
}


I2C_STATUS HAL_I2C_Slave_Receive_IT(I2C_Handler_t * Handler  ,uint8_t * pRxData ,uint8_t DataSize )
{
	
	
		return I2C_NORMAL;
}

/* brief  @ : this function used to handle all operation of dealing with reading from dev. memory 
 * param. @ : handler this handler of I2c peripheral 
 * param. @ : DevAdd this is the address of the slave device that you want to communicate with 
 * param. @ : memAdd this is the internal memory address that you need to write data to 
 * param. @ : pRxData this is pointer to the buffer that hold the writing data 
 * param. @ : DataSize number of bytes that you need to write 
*/ 
I2C_STATUS HAL_I2C_Mem_Write(I2C_Handler_t * Handler ,uint8_t DevAdd,uint8_t MemAdd ,uint8_t * pTxData ,uint8_t DataSize )
{
	Handler->buffer = pTxData ;
	Handler->Size   = DataSize;
	
	
	I2C_EN_START();
	while(!(I2C->I2C_TWCR & 0x80));
	
	
	I2C->I2C_TWDR = DevAdd ;
	I2C_EN();
	while(!(I2C->I2C_TWCR & 0x80));

	I2C->I2C_TWDR = MemAdd;
	I2C_EN();
	while(!(I2C->I2C_TWCR & 0x80));
	

	while(Handler->Size-- > 0)
	{
		I2C->I2C_TWDR = *(Handler->buffer++) ;
		I2C_EN();
		while(!(I2C->I2C_TWCR & 0x80));
	}
	I2C_EN_STOP();
	
	return I2C_NORMAL;	
}

/* brief  @ : this function used to handle all operation of dealing with memory 
 * param. @ : handler this handler of I2c peripheral 
 * param. @ : DevAdd this is the address of the slave device that you want to communicate with 
 * param. @ : memAdd this is the internal memory address that you need to read data from it 
 * param. @ : pRxData this is pointer to the buffer that will hold the reading data 
 * param. @ : DataSize number of bytes that you need to read 
*/ 
I2C_STATUS HAL_I2C_Mem_Read(I2C_Handler_t * Handler ,uint8_t DevAdd,uint8_t MemAdd ,uint8_t * pRxData ,uint8_t DataSize )
{
	Handler->buffer = pRxData ;
	Handler->Size   = DataSize;
	
	I2C_EN_START();
	while(!(I2C->I2C_TWCR & 0x80));
	
	
	I2C->I2C_TWDR = DevAdd ;
	I2C_EN();
	while(!(I2C->I2C_TWCR & 0x80));

	I2C->I2C_TWDR = MemAdd;
	I2C_EN();
	while(!(I2C->I2C_TWCR & 0x80));
	
	
	I2C_EN_START();
	while(!(I2C->I2C_TWCR & 0x80));	

	I2C->I2C_TWDR = DevAdd | 1 ;
	I2C_EN();
	while(!(I2C->I2C_TWCR & 0x80));
	
		
	while(Handler->Size-- > 0)
	{
		I2C_EN_ACK();
		while(!(I2C->I2C_TWCR & 0x80));
		*(Handler->buffer++) = I2C->I2C_TWDR ;
	}
	I2C_EN_NACK();
	while(!(I2C->I2C_TWCR & 0x80));	
	I2C_EN_STOP();
	return I2C_NORMAL;		
}


 void I2C_Handler_Process(I2C_Handler_t * Handler)
 {
	 uint8_t Status =0;
	 ClearBit(I2C->I2C_TWCR , I2C_IT_FLAG); /* first clear the flag this enable us to operate on i2c */
	 if(Handler->Size != 0)
	 {
	 Status = I2C->I2C_TWSR & 0xf1 ; 
	 switch(IS_Current_opreration)
	 {
		 case MasterTransmitMode :
		 switch(Status)
		 {
			case 0x08 :  /* start condition has been transmitted */
					I2C->I2C_TWDR = SLAVE_ADD<<1;
		 			I2C_EN();
			break; 
			case 0x18 :
			case 0x28 :
					I2C->I2C_TWDR = *(Handler->buffer++) ;
					Handler->Size--;
		 			I2C_EN();
			break;
			default:
			
			break; 
		 }
		 break; 
		 default: 
		 
		 break; 
		}
	 
	 }
	 
 }