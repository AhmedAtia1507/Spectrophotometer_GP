/**
 * @file SPECTRO_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _SPECTRO_INTERFACE_H_
#define _SPECTRO_INTERFACE_H_

/**
 * @brief: Function to initialize the spectrophotometer system.
 * 
 * This function sets the system status to INITIALIZING, initializes software and hardware, 
 * and updates the system status accordingly.
 * 
 * @return Std_ReturnType
 * @retval E_OK: 					If initialization is successful
 * @retval E_NOT_OK: 				Otherwise
 */
Std_ReturnType SPECTRO_InitSystem	(void);
/**
 * @brief Function to initialize the software components of the spectrophotometer system.
 * 
 * This function initializes the system clock, enables peripheral clocks, sets interrupt priorities,
 * and initializes various modules such as RTC, SysTick, ADC, commands, power supply voltages, MCP4151,
 * motors, and timers.
 * 
 * @return Std_ReturnType
 * @retval E_OK: 						If software initialization is successful
 * @retval E_NOT_OK: 					Otherwise
 */
Std_ReturnType SPECTRO_InitSoftware		(void);
/**
 * @brief Function to initialize the hardware components of the spectrophotometer system.
 * 
 * This function checks on UV and VIS supplies, and initiates the system calibration.
 * 
 * @return Std_ReturnType
 * @retval E_OK: 						If hardware initialization is successful
 * @retval E_NOT_OK: 					Otherwise
 */
Std_ReturnType SPECTRO_InitHardware		(void);
/**
 * @brief Initializes the calibration process for the spectrophotometer system.
 * 
 * This function homes the motors, reads the saved zero wavelength from EEPROM, and starts a calibration scan
 * to determine the zero wavelength and 656.1 nm steps.
 * 
 * @return Std_ReturnType 
 * @retval E_OK: 						If calibration initialization is successful
 * @retval E_NOT_OK: 					Otherwise
 */
Std_ReturnType SPECTRO_InitCalibration	(void);
#endif /*_SPECTRO_INTERFACE_H_*/