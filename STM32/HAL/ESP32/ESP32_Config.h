/**
 * @file ESP32_Config.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _ESP32_CONFIG_H_
#define _ESP32_CONFIG_H_

/**
 * @brief: Defines which UART that will be used to connect to the ESP32
 * 
 * Options:
 * 1) UART 1:               									HESP32_UART1
 * 2) UART 2:               									HESP32_UART2
 * 3) UART 3:               									HESP32_UART3
 */
#define HESP32_UART_CHOICE                  					HESP32_UART3
#define HESP32_NO_OF_COMMANDS                  					22
#define HESP32_NO_OF_NON_ARG_COMMANDS							17
#define HESP32_NO_OF_ARG_COMMANDS								5	
#define HESP32_MAX_BUFFER_SPACE									50


static volatile uint8 HESP32_AvailableTasks[HESP32_NO_OF_COMMANDS][20] =   {	"snduv",			//send uv status (on/off)
																				"uvon",				//turn uv lamp on (reply with current status)
																				"uvoff",			//turn uv lamp off
																				"sndvi",			//send visible lamp status (on/off)
																				"vion",				//turn visible lamp on
																				"vioff",			//turn visible lamp off
																				"p12",				//read 12v from dc/dc converter --> reply(+11.9)
																				"n12",				//read -12v from dc/dc converter --> reply(-11.9)
																				"p5",				//read 5v from supply ---> reply(4.9)
																				"p33",				//read 3.3v from regulator ---> reply(3.24)
																				"twelve",			//read 12v from supply ---> reply(11.9)
																				"sndmotorsteps",	//send motor steps & current wavelength --> reply "lamp-grating-filter-wavelength"
																				"lampmotorhome",	//move lamp motor to home ---> reply current step after reaching home
																				"gratingmotorhome",	//move grating motor to home ---> reply current step after reaching home
																				"filtermotorhome",	//move filter motor to home ---> reply current step after reaching home
																				"crnt-wav",			//send the current wavelength --> reply (number)
																				"sndtime",			//send current date and time to ESP ---> reply(day/month/year hh:mm:ss)
																				"updatedate",		//update current date and time --> reply(time update success / time update failed)
																				"movto",			//send the filter moter to sthe "value" steps position ==> respond with "moved" or "failed to move"
																				"savestep",			//save the value in the eeprom  ==> respond with "saved" or "failed to save"
																				"savewave",			//save the value in the eeprom  ==> respond with "saved" or "failed to save"
																				"startscan"			//start scan of spectro "begin end step" 
};

#endif /*_ESP32_CONFIG_H_*/