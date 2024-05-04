/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: Dec 10, 2023
 *      Author: Mohanad
 */

#ifndef HAL_I2C_EEPROM_I2C_SLAVE_EEPROM_H_
#define HAL_I2C_EEPROM_I2C_SLAVE_EEPROM_H_

#include "../../LIB/STD_TYPES/Std_Types.h"
#include "../../MCAL/I2C/I2C_Interface.h"

#define EEPROM_Slave_address		    0b1010000
#define EEPROM_MOTOR_WL_MEM_ADDRESS     0xD0
#define EEPROM_MOTOR_STEPS_MEM_ADDRESS  0xD8

void eeprom_init(void);
unsigned char eeprom_write_Nbytes(unsigned int Memory_address, unsigned char* bytes, uint8 Data_Length);
unsigned char eeprom_read_byte(unsigned int address, uint8 *dataOut, uint8 dataLen);

#endif /* HAL_I2C_EEPROM_I2C_SLAVE_EEPROM_H_ */
