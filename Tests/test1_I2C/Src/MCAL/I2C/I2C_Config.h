/*
 * I2c_Config.h
 *
 *  Created on: Dec 10, 2023
 *      Author: Mohanad
 */

#ifndef MCAL_I2C_I2C_CONFIG_H_
#define MCAL_I2C_I2C_CONFIG_H_

#include "I2C_private.h"
#include "../../LIB/STD_TYPES.h"

struct S_I2C_Slave_Device_Address
{
	u16 Enable_Dual_ADD;	//1-Enable	0-Disable
	u16 Primary_slave_address;
	u16 Secondary_slave_address;
	u16 I2C_Addressing_Slave_mode; //@I2C_Addressing_Slave_
};

typedef enum
{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ,			//The APP layer should send the data (I2C_Slave_Send_Data) in this state
	I2C_EV_DATA_RCV				//The APP layer should read the data (I2C_Slave_Receive_Data) in this state
}Slave_State;

typedef struct
{
	u32 I2C_ClockSpeed;							/* Specifies the clock frequency
														This parameter must be set to @I2C_SCLK_ */

	u16 StretchMode;								//@I2C_StretchMode_

	u16 I2C_Mode;									/* Specifies the I2C mode.
														This parameter can be a value of @I2C_mode */

	struct S_I2C_Slave_Device_Address	I2C_Slave_Device_Address;

	u16 I2C_ACK_Control;							/* Enables or disables the acknowledgement
														This parameter can be a value of @I2C_Ack */

	u16 General_Call_Address_Detection;			//@I2C_ENGC

	void(* P_Slave_Event_CallBack)(Slave_State state);  //Set the C Function() which will be called

}I2C_InitTypeDef;

// * ====================================================================
//Reference Macros
// * ====================================================================

//@I2C_SCLK_
//>> Standard Speed (up to 100 khz)
//>> Fast Speed (up to 400 khz)
//>> to configure clock before enabling the peripheral
//---I2C_CR2.FREQ[5:0]: Peripheral clock frequency
//>> Configure the clock control registers
//-T_high = CCR * TPCLK1
//-SM or FM (Standard mode or Fast mode)
//>> Configure the rise time registers I2C_TRISE

#define I2C_SCLK_SM_50k				(500000U)
#define I2C_SCLK_SM_100k			(100000U)
#define I2C_SCLK_FM_200k			(200000U)	// Fast Mode is not supported yet
#define I2C_SCLK_FM_400k			(400000U)	// Fast Mode is not supported yet
// we can put many values



//@I2C_StretchMode_
//I2C_CR1
//Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
//0 : Clock stretching enabled
//1 : Clock stretching disabled
#define I2C_StretchMode_Enable		(0x00000000U)
#define I2C_StretchMode_Disable		I2C_CR1_NOSTRETCH



//@I2C_mode
//I2C_CR1
//Bit 1 SMBUS: SMBus mode
//0 : I2C mode
//1 : SMBus mode
#define I2C_mode_I2C				0
#define I2C_mode_SMBus				I2C_CR1_SMBUS



//@I2C_Addressing_Slave_
//I2C_OAR1.ADDMODE
//Bit 15 ADDMODE Addressing mode (slave mode)
//0 : 7-bit slave address (10-bit address not acknowledged
//1 : 10-bit slave address (7-bit address not acknowledged)
#define I2C_Addressing_Slave_mode_7Bit			0x00000000U
#define I2C_Addressing_Slave_mode_10Bit			(u16)(1<<15)



//@I2C_Ack
//I2C_CR1
//0 : No acknowledge returned
//1 : Acknowledge returned after a byte is received (matched address or data)
#define I2C_Ack_Enable			(I2C_CR1_ACK)
#define I2C_Ack_Disable			((u16)0x0000)



//@ref I2C_ENGC
//I2C_CR1
//Bit 6 ENGC: General call enable
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed
#define I2C_ENGC_Enable                   I2C_CR1_ENGC
#define I2C_ENGC_Disable                  0x00000000U

#endif /* MCAL_I2C_I2C_CONFIG_H_ */
