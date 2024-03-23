/*
 * I2C_Interface.h
 *
 *  Created on: Dec 10, 2023
 *      Author: Mohanad
 */

#ifndef MCAL_I2C_I2C_INTERFACE_H_
#define MCAL_I2C_I2C_INTERFACE_H_

#include "../../LIB/STD_TYPES/Std_Types.h"
#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/RCC/RCC_Interface.h"
#include "I2C_Config.h"
#include "I2C_private.h"

#define I2C_EVENT_MASTER_BYTE_TRANSMITTING		((uint32)0x00070080) /* TRA, BUSY, MSL, TXE flags */

typedef enum
{
	With_Stop,
	Without_Stop
}Stop_Condition;

typedef enum
{
	Start,
	repeated_start
}Repeated_Start;

typedef enum {DISABLE = 0, ENABLE = 1} FunctionalState;
typedef enum {RESET = 0, SET = 1} FlagStatus;
typedef enum {I2C_Direction_Transmitter = 0, I2C_Direction_Receiver = 1} I2C_Direction;
typedef enum
{
	I2C_FLAG_BUSY = 0,
	EV5,
	EV6,
	EV7,
	EV8,
	EV8_1,
	MASTER_BYTE_TRANSMITTING = ((uint32)0x00070080),  /* TRA, BUSY, MSL, TXE flags */
}Status;

void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
void MCAL_I2C_DInit(I2C_TypeDef* I2Cx);
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx);

//Master Polling Mechanism
void MCAL_I2C_MASTER_TX(I2C_TypeDef* I2Cx, uint16 devAddr, uint8 *dataOut, uint32 dataLen, Stop_Condition Stop, Repeated_Start start);
void MCAL_I2C_MASTER_RX(I2C_TypeDef* I2Cx, uint16 devAddr, uint8 *dataOut, uint32 dataLen, Stop_Condition Stop, Repeated_Start start);

//Slave interrupt mechanism

//Generic APIs
void I2C_GenerateSTART(I2C_TypeDef *I2Cx, FunctionalState NewState, Repeated_Start start);
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, Status flag);
void I2C_SendAddress(I2C_TypeDef* I2Cx, uint16 Address, I2C_Direction Direction);
void I2C_GenerateSTOP(I2C_TypeDef *I2Cx, FunctionalState NewState);
void I2C_ACKnowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
void delay_ms(uint32 milliseconds);
void MCAL_I2C_RESET();

#endif /* MCAL_I2C_I2C_INTERFACE_H_ */
