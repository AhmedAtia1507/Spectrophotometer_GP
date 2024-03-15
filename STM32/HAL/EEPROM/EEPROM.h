/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: Dec 10, 2023
 *      Author: Mohanad
 */

#ifndef HAL_I2C_EEPROM_I2C_SLAVE_EEPROM_H_
#define HAL_I2C_EEPROM_I2C_SLAVE_EEPROM_H_

#include "../../MCAL/I2C/I2C_Interface.h"

#define EEPROM_Slave_address		0b1010000

void eeprom_init(void);
unsigned char eeprom_write_Nbytes(unsigned int Memory_address, unsigned char* bytes, u8 Data_Length);
unsigned char eeprom_read_byte(unsigned int address, u8 *dataOut, u8 dataLen);

#endif /* HAL_I2C_EEPROM_I2C_SLAVE_EEPROM_H_ */
