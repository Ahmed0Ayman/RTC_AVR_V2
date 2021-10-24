

#ifndef __HAL_I2C__
#define __HAL_I2C__


/*
 * I2c.h
 *
 * Created: 4/26/2021 5:14:35 PM
 *  Author: Ahmed_Ayman
 */ 
#include <stdint.h>
#define F_CPU   16000000
#include "avr/interrupt.h"
#include "GPIO_TYPEDEF.h"

typedef struct 
{
	uint8_t I2C_TWBR ;
	uint8_t I2C_TWSR ;
	uint8_t I2C_TWAR ;
	uint8_t I2C_TWDR ;
	uint8_t Reserved[0x32];
	uint8_t I2C_TWCR ;
}I2CTypeDef_t;

typedef struct 
{
	uint32_t I2C_Clk_Speed ;
	uint8_t I2C_SlaveADD ;
	uint8_t I2C_INIT_MODE ;

}I2C_InitTypeDef;


typedef struct
{
	I2C_InitTypeDef Init  ;
	uint8_t * buffer ;
	uint8_t Size ;

}I2C_Handler_t;

typedef enum 
{
	I2C_BUSY =0,
	I2C_NORMAL,
	I2C_ERROR ,
	
}I2C_STATUS;

#define I2C_IT_FLAG								0X80U 
#define I2C_ACK_EN								0X40U
#define I2C_START_EN							0X20U
#define I2C_STOP_EN								0X10U
#define I2C_COLLISION_FLAG						0X08U
#define I2C_EN_Priph							0X04U
#define I2C_IT_EN								0X01U

#define I2C_PRE_SCALLER_1						0X00U
#define I2C_PRE_SCALLER_4						0X01U
#define I2C_PRE_SCALLER_16						0X02U
#define I2C_PRE_SCALLER_64						0X03U

#define I2C_SPEED_NORMAL						0X01U
#define I2C_SPEED_FAST							0X02U

#define I2C_INIT_EN								0x01u
#define I2C_INIT_DIS							0X02U
 
#define I2C_Base								0X20U

#define I2C      ((I2CTypeDef_t volatile *)I2C_Base) 

#define  I2C_EN_START()             I2C->I2C_TWCR = 0xA4U
#define  I2C_EN()					I2C->I2C_TWCR = 0x84U
#define  I2C_EN_STOP()              I2C->I2C_TWCR = 0x94U
#define  I2C_EN_ACK()               I2C->I2C_TWCR = 0XC4U
#define  I2C_EN_NACK()              I2C->I2C_TWCR = 0X84U
 


#define I2C_STATUS_VAL         (I2C->I2C_TWSR & 0XF1)


void I2C_INIT_FUN(I2C_Handler_t * Handler);






/* brief  @ : this function used to transmit data in master transmit mode
 * param. @ : handler this handler of I2c peripheral 
 * param. @ : DevAdd this is the address of the slave device that you want to communicate with
 * param. @ : pTxData this is pointer to the buffer that will hold the transmitted data 
 * param. @ : DataSize number of bytes that you need to read 
*/ 
I2C_STATUS HAL_I2C_Master_Transmit(I2C_Handler_t * Handler,uint8_t DevAdd ,uint8_t * PTxData,uint8_t DataSize);




/* brief  @ : this function used to transmit data in master receive mode
 * param. @ : handler this handler of I2c peripheral 
 * param. @ : DevAdd this is the address of the slave device that you want to communicate with
 * param. @ : pTxData this is pointer to the buffer that will hold the transmitted data 
 * param. @ : DataSize number of bytes that you need to read 
*/ 
I2C_STATUS HAL_I2C_Master_Receive(I2C_Handler_t * Handler ,uint8_t DeviceAdd  ,uint8_t * pData ,uint8_t Size );




/* brief  @ : this function used to receive data in slave mode
 * param. @ : handler this handler of I2c peripheral 
 * param. @ : DevAdd this is the address of the slave device that you want to communicate with
 * param. @ : pRxData this is pointer to the buffer that will hold the transmitted data 
 * param. @ : DataSize number of bytes that you need to receive 
*/ 
I2C_STATUS HAL_I2C_Slave_Transmit(I2C_Handler_t * Handler  ,uint8_t * pTxData,uint8_t DataSize );


I2C_STATUS HAL_I2C_Slave_Receive(I2C_Handler_t * Handler  ,uint8_t * pRxData ,uint8_t DataSize );


I2C_STATUS HAL_I2C_Master_Transmit_IT(I2C_Handler_t * Handler ,uint8_t DeviceAdd ,uint8_t * pTxData,uint8_t DataSize );


I2C_STATUS HAL_I2C_Master_Receive_IT(I2C_Handler_t * Handler ,uint8_t DeviceAdd  ,uint8_t * pTxData ,uint8_t DataSize );


I2C_STATUS HAL_I2C_Slave_Transmit_IT(I2C_Handler_t * Handler  ,uint8_t * pTxData,uint8_t DataSize );


I2C_STATUS HAL_I2C_Slave_Receive_IT(I2C_Handler_t * Handler  ,uint8_t * pTxData ,uint8_t DataSize );




/* brief  @ : this function used to handle all operation of dealing with reading from dev. memory 
 * param. @ : handler this handler of I2c peripheral 
 * param. @ : DevAdd this is the address of the slave device that you want to communicate with 
 * param. @ : memAdd this is the internal memory address that you need to write data to 
 * param. @ : pRxData this is pointer to the buffer that hold the writing data 
 * param. @ : DataSize number of bytes that you need to write 
*/ 
I2C_STATUS HAL_I2C_Mem_Write(I2C_Handler_t * Handler ,uint8_t DeviceAdd,uint8_t MemAdd ,uint8_t * pTxData ,uint8_t DataSize );





/* brief  @ : this function used to handle all operation of dealing with memory 
 * param. @ : handler this handler of I2c peripheral 
 * param. @ : DevAdd this is the address of the slave device that you want to communicate with 
 * param. @ : memAdd this is the internal memory address that you need to read data from it 
 * param. @ : pRxData this is pointer to the buffer that will hold the reading data 
 * param. @ : DataSize number of bytes that you need to read 
*/ 
I2C_STATUS HAL_I2C_Mem_Read(I2C_Handler_t * Handler ,uint8_t DeviceAdd,uint8_t MemAdd ,uint8_t * pRxData ,uint8_t DataSize );






#endif