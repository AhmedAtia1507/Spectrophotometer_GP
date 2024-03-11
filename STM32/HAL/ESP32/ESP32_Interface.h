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
typedef void(*ptr_to_Arg_Callback_func)(uint8*);
/**
 * @brief: Function to initialize peripherals used in communication between
 *          ESP32 and STM32F103C8T6 
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Initialization is successful
 * @retval E_NOT_OK:    Failed to initialize communication 
 */
Std_ReturnType HESP32_InitInterface                 (void);

Std_ReturnType HESP32_SendCommand                   (uint8* P_uint8Command);

Std_ReturnType HESP32_SetCommandCallbackFunction    (uint8 Copy_uint8CommandNumber, ptr_to_Callback_func P_CommandCallbackFunc);

Std_ReturnType HESP32_SetCommandCallbackArgFunction (uint8 Copy_uint8CommandNumber, ptr_to_Arg_Callback_func P_CommandCallbackFunc);

Std_ReturnType HESP32_SendDataTime                  (Sdate_t* P_SDateToBeSent, Stime_t* P_STimeToBeSent);

Std_ReturnType HESP32_SendMotorStatus               (uint32* P_uint32MotorSteps, uint32* P_uint32CurrentWL, uint8 Copy_uint8MotorNum);

Std_ReturnType HESP32_SendIntensities               (float32* P_float32RefIntensity, float32* P_float32SampleIntensity);
#endif /*_ESP32_INTERFACE_H_*/