/*
 * I2C_Slave_EEPROM.c
 *
 *  Created on: Dec 10, 2023
 *      Author: Mohanad
 */

#include "../../LIB/STD_TYPES/Std_Types.h"

#include "EEPROM.h"

void delay_ms(uint32 milliseconds);

void eeprom_init(void)
{

	//==================I2C INIT =============================
	//		PB6 : I2C1_SCL
	//		PB7 : I2C1_SDA

	I2C_InitTypeDef I2C1CFG ;

	//I2C Controller act as a Master

	I2C1CFG.General_Call_Address_Detection = I2C_ENGC_Enable ;
	I2C1CFG.I2C_ACK_Control =I2C_Ack_Enable ;
	I2C1CFG.I2C_ClockSpeed = I2C_SCLK_SM_100k ;
	I2C1CFG.I2C_Mode = I2C_mode_I2C ;
	I2C1CFG.P_Slave_Event_CallBack = NULL_PTR ;
	I2C1CFG.StretchMode = I2C_StretchMode_Enable;

	MCAL_I2C_GPIO_Set_Pins (I2C1);
	MCAL_I2C_Init(I2C1, &I2C1CFG);
	MCAL_I2C_RESET();
	MCAL_I2C_Init(I2C1, &I2C1CFG);


}
Std_ReturnType eeprom_write_Nbytes(uint32 Memory_address, uint8* bytes, uint8 Data_Length)
{
	uint8 i=0 ;
	//MISRA C++ 2008, 18-4-1 - Dynamic heap memory allocation shall not be used
	//Violate MISRA Rule
	//(unsigned char*)malloc(Data_Length+2)  ;
	uint8 buffer[256]  ;
	//buffer[0] = (uint8)(Memory_address>>8) ; 	//upper byte Memory Address
	//buffer[1] = (uint8)Memory_address ; 	//lower byte Memory Address
	buffer[0] = (uint8)(Memory_address) ; 	//Memory Address

	for (i=1 ; i<(Data_Length+1) ; i++ )
	{buffer[i] = bytes[i-1] ;}

	MCAL_I2C_MASTER_TX(I2C1, EEPROM_Slave_address, buffer, (Data_Length+1), With_Stop, Start);

	return E_OK;
}


Std_ReturnType eeprom_read_byte(uint32 address , uint8* dataOut, uint8 dataLen)
{

	uint8 buffer[2];
	//buffer[0] = (uint8)(address>>8) ; 	//Upper Memory Address
	//buffer[1] = (uint8)(address) ; 	//Lower Memory Address
	buffer[0] = (uint8)(address) ; 	//Memory Address

	MCAL_I2C_MASTER_TX(I2C1, EEPROM_Slave_address , buffer, 1,Without_Stop ,Start); //Write Address Only
	delay_ms(20);
	MCAL_I2C_MASTER_RX(I2C1, EEPROM_Slave_address, dataOut, dataLen,With_Stop,repeated_start); 			//Read Data

	return E_OK;

}

//void delay_ms(uint32 milliseconds) {
//    // Assuming a 1 MHz clock frequency for illustration purposes
//    // Adjust the loop count based on your actual clock frequency
//    // This is a simple and blocking delay function
//    // In a real application, you might want to use a timer for more accurate timing
//
//    // Calculate the loop count needed for the specified delay
//    uint32 loop_count = milliseconds * 1000;
//
//    // Perform the delay using a loop
//    for (uint32 i = 0; i < loop_count; i++) {
//        // Do nothing
//    }
//}
