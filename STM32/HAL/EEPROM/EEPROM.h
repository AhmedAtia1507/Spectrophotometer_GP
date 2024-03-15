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
Std_ReturnType eeprom_write_Nbytes(uint32 Memory_address, uint8* bytes, uint8 Data_Length);
Std_ReturnType eeprom_read_byte(uint32 address, uint8 *dataOut, uint8 dataLen);

#endif /* HAL_I2C_EEPROM_I2C_SLAVE_EEPROM_H_ */
