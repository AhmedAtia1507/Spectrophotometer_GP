/**
 * @file ESP32_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _ESP32_INTERFACE_H_
#define _ESP32_INTERFACE_H_

typedef void(*ptr_to_Callback_func)(void);
/**
 * @brief: Function to initialize peripherals used in communication between
 *          ESP32 and STM32F103C8T6 
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Initialization is successful
 * @retval E_NOT_OK:    Failed to initialize communication 
 */
Std_ReturnType HESP32_InitInterface              (void);

Std_ReturnType HESP32_SendCommand                (uint8* P_uint8Command);

Std_ReturnType HESP32_SetTaskCallbackFunction    (uint8 Copy_uint8TaskNumber, ptr_to_Callback_func P_TaskCallbackFunc);
#endif /*_ESP32_INTERFACE_H_*/