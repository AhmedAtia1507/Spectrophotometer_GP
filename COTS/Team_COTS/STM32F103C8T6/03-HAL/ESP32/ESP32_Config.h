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
 * 1) UART 1:               HESP32_UART1
 * 2) UART 2:               HESP32_UART2
 * 3) UART 3:               HESP32_UART3
 */
#define HESP32_UART_CHOICE                  HESP32_UART1
#define HESP32_NO_OF_TASKS                  10
#define HESP32_NO_OF_ABS_TASKS							2

//uint8 HESP32_AvailableTasks[HESP32_NO_OF_TASKS][20] =   {  	"command1", //UV led on
//																														"command2", //UV led off
//																														"command3",
//																														"command4",
//																														"command5",
//																														"command6",
//																														"UV",
//																														"VI",
//																														"WL",
//																														"wavelength"
//};
uint8 HESP32_AvailableTasks[HESP32_NO_OF_TASKS][20] =   {  	"command1", //UV led on
																														"uv led off", //UV led off
																														"vis led off",
																														"command4",
																														"command5",
																														"command6",
																														"uv led on",
																														"vis led on",
																														"get wavelength",
																														"wavelength"
};

uint8 HESP32_AvailableAbsTasks[HESP32_NO_OF_ABS_TASKS][20] ={	"reference",
																															"sample"
};
#endif /*_ESP32_CONFIG_H_*/