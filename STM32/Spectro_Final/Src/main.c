/**
 * @file main.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2024-02-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "LIB/BIT_MATH/BIT_MATH.h"
#include "LIB/STD_TYPES/Std_Types.h"

#include "HAL/EEPROM/I2C_Slave_EEPROM.h"
#include "APP/SPECTRO/SPECTRO_Interface.h"

int main(void)
{
	SPECTRO_InitSystem();

	while(1)
	{

	}
	return 0;
}
