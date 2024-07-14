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
typedef enum
{
    HESP32_SCAN,
    HESP32_SCAN_TIME
}Operation_t;

/**
 * @brief Function to convert a floating-point number to a string representation with specified precision.
 * 
 * @param P_uint8Buffer:            Pointer to the buffer where the resulting string will be stored.
 * @param Copy_float32FloatNum:     The floating-point number to convert.
 * @param Loc_uint32precision:      The number of digits to include after the decimal point.
 */
void float_to_string_manual                         (uint8* P_uint8Buffer, float32 Copy_float32FloatNum, uint32 Loc_uint32precision);
/**
 * @brief: Function to initialize peripherals used in communication between
 *          ESP32 and STM32F103C8T6 
 * 
 * @return Std_ReturnType
 * @retval E_OK:                    Initialization is successful
 * @retval E_NOT_OK:                Failed to initialize communication 
 */
Std_ReturnType HESP32_InitInterface                 (void);
/**
 * @brief Sends a command to the ESP32 module via UART.
 * 
 * @param P_uint8Command:                       Pointer to the command string to be sent.
 * 
 * @return Std_ReturnType 
 * @retval E_OK:                                Command is sent successfully
 * @retval E_NOT_OK:                            Otherwise
 */
Std_ReturnType HESP32_SendCommand                (uint8* P_uint8Command);
/**
 * @brief: Function to set the callback function for a specific command.
 * 
 * @param Copy_uint8CommandNumber:              Command number for which the callback function is to be set.
 * @param P_CommandCallbackFunc:                Pointer to the callback function.
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                Callback function is set successfully
 * @retval E_NOT_OK:                            Otherwise
 */
Std_ReturnType HESP32_SetCommandCallbackFunction    (uint8 Copy_uint8CommandNumber,ptr_to_Callback_func P_CommandCallbackFunc);
/**
 * @brief: Function to set the argument callback function for a specific command.
 * 
 * @param Copy_uint8CommandNumber:                  Command number for which the argument callback function is to be set.
 * @param P_CommandCallbackFunc:                    Pointer to the argument callback function.
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                    Argument callback function is set successfully
 * @retval E_NOT_OK:                                Otherwise
 */
Std_ReturnType HESP32_SetCommandCallbackArgFunction (uint8 Copy_uint8CommandNumber, ptr_to_Arg_Callback_func P_CommandCallbackFunc);
/**
 * @brief: Function to send the date and time.
 * 
 * @param P_SDateToBeSent:                          Pointer to a struct containing the date.
 * @param P_STimeToBeSent:                          Pointer to a struct containing the time.
 * @return Std_ReturnType 
 * @retval E_OK:                                    If the date and time are sent successfully
 * @retval E_NOT_OK:                                Otherwise.
 */
Std_ReturnType HESP32_SendDateTime                  (Sdate_t* P_SDateToBeSent, Stime_t* P_STimeToBeSent);
/**
 * @brief Function to send the time to ESP32.
 * 
 * @param P_STimeToBeSent:                          Pointer to a struct containing the time.
 * @return Std_ReturnType
 * @retval E_OK:                                    If the time is sent successfully
 * @retval E_NOT_OK:                                Otherwise
 */
Std_ReturnType HESP32_SendTime                      (Stime_t* P_STimeToBeSent);
/**
 * @brief Function to send the motor status including motor steps and current wavelength.
 * 
 * @param P_uint32MotorSteps:                       Pointer to an array containing motor steps for each motor.
 * @param P_float32CurrentWL:                       Pointer to a float containing the current wavelength.
 * @param Copy_uint8MotorNum:                       Number of motors (1 or 3).
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                    Data is sent successfully
 * @retval E_NOT_OK:                                Otherwise
 */
Std_ReturnType HESP32_SendMotorStatus               (uint32* P_uint32MotorSteps, float32* P_float32CurrentWL, uint8 Copy_uint8MotorNum);
/**
 * @brief Function to send the wavelength, reference intensity, and sample intensity.
 * 
 * @param Copy_float32WL                            Currnet Wavelength
 * @param Copy_float32RefIntensity                  Reference Intensity
 * @param Copy_float32SampleIntensity               Sample Intensity
 * @param Copy_uint32OperationType                  Operation type (HESP32_SCAN or HESP32_SCAN_TIME)
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                    If the data is sent successfully
 * @retval E_NOT_OK:                                Otherwise
 */
Std_ReturnType HESP32_SendIntensities               (float32 Copy_float32WL, float32 Copy_float32RefIntensity, float32 Copy_float32SampleIntensity, Operation_t Copy_uint32OperationType);
/**
 * @brief Function to send the voltages to ESP32.
 * 
 * @param PP_uint8Voltages:                         2D array of voltage values to be sent
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                    If the voltages are sent successfully
 * @retval E_NOT_OK:                                Otherwise.
 */
Std_ReturnType HESP32_SendVoltages                  (uint8 PP_uint8Voltages[][32]);
/**
 * @brief: Function to send the detector readings and gain values
 * 
 * @param P_float32Readings:                        Pointer to an array containing the detector readings
 * @param P_float32GainValues:                      Pointer to an array containing the gain values
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                    If the data is sent successfully
 * @retval E_NOT_OK:                                Otherwise
 */
Std_ReturnType HESP32_SendDetectorValues            (float32* P_float32Readings, float32* P_float32GainValues);

/**
 * @brief Function to send all detector readings and gain values.
 * 
 * @param P_float32Readings:                        Pointer to an array containing the detector readings
 * @param P_float32GainValues:                      Pointer to an array containing the gain values
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                    If the data is sent successfully
 * @retval E_NOT_OK:                                Otherwise
 */
Std_ReturnType HESP32_SendAllDetectorValues         (float32* P_float32Readings, float32* P_float32GainValues);

#endif /*_ESP32_INTERFACE_H_*/
