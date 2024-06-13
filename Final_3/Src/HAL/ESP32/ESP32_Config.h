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
#define HESP32_NO_OF_COMMANDS                  					29
#define HESP32_NO_OF_NON_ARG_COMMANDS							17
#define HESP32_NO_OF_ARG_COMMANDS								12	
#define HESP32_MAX_BUFFER_SPACE									40


static volatile uint8 HESP32_AvailableTasks[HESP32_NO_OF_COMMANDS][30] =   {	/******************Commands with no arguments******************/
																				"get-uv",					//send uv status (on/off)
																				"set-uv-on",				//turn uv lamp on (reply with current status)
																				"set-uv-off",				//turn uv lamp off
																				"get-vi",					//send visible lamp status (on/off)
																				"set-vi-on",				//turn visible lamp on
																				"set-vi-off",				//turn visible lamp off
																				"get-voltages",				//send current supplies voltages ---> reply: p12 n12 p5 p33 twelve
																				"get-motors-steps",			//send motor steps & current wavelength --> reply "lamp-grating-filter-wavelength"
																				"set-lamp-motor-home",			//move lamp motor to home ---> reply current step after reaching home
																				"set-grating-motor-home",			//move grating motor to home ---> reply current step after reaching home
																				"set-filter-motor-home",			//move filter motor to home ---> reply current step after reaching home
																				"get-current-wav",			//send the current wavelength --> reply (number)
																				"get-time",					//send current date and time to ESP ---> reply(day/month/year hh:mm:ss)
																				"get-det-readings",			//send current detector readings ---> reply "reference-reference_amplified-sample-sample_amp-current_ref_gain-current_sample_gain"
																				"get-lamp-motor-position",	//send lamp motor current position ---> reply "UV Lamp" or "VI Lamp"
																				"set-lamp-moter-VI",		//set the lamp motor to be in the VI ---> reply: "moved" or "failed to move"
																				"set-lamp-moter-UV",		//set the lamp motor to be in the UV ---> reply: "moved" or "failed to move"

																				/******************Commands with arguments******************/
																				"set-time",					//update current date and time --> reply(time update success / time update failed)
																				"savestep",					//save the value in the eeprom  ==> respond with "saved" or "failed to save"
																				"savewave",					//save the value in the eeprom  ==> respond with "saved" or "failed to save"
																				"Scan",						//start scan of spectro "begin end step"
																				"set-ref-newgain-to", 		//apply new reference gain to signal conditioning ----> reply "applied"/"not applied"
																				"set-sample-newgain-to",	//apply sample new gain to signal conditioning circuit ---> reply "applied"/"not applied"
																				"set-filtermoter-to-L",		//send filter motor to "value" steps to the left ---> reply "moved" or "failed to move"
																				"set-filtermoter-to-R",		//send filter motor to "value" steps to the right ---> reply "moved" or "failed to move"
																				"set-filtermoter-to",		//send filter motor to filter Fx ----> reply: "moved" or "failed to move"
																				"set-gratingmoter-to-WL",	//send grating motor to wavelength x nm ---> reply: "moved" or "failed to move"
																				"set-gratingmoter-to-L",	//send grating motor to x steps to the left ----> reply: "moved" or "failed to move"
																				"set-gratingmoter-to-R"		//send grating motor to x steps to the right ---> reply: "moved" or "failed to move"
};

#endif /*_ESP32_CONFIG_H_*/
