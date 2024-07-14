/**
 * @file EXTI_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 *  
 * @version 1.0
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _EXTI_INTERFACE_H_
#define _EXTI_INTERFACE_H_

#define MEXTI_EXTI0                                 0
#define MEXTI_EXTI1                                 1
#define MEXTI_EXTI2                                 2
#define MEXTI_EXTI3                                 3
#define MEXTI_EXTI4                                 4
#define MEXTI_EXTI5                                 5
#define MEXTI_EXTI6                                 6
#define MEXTI_EXTI7                                 7
#define MEXTI_EXTI8                                 8
#define MEXTI_EXTI9                                 9
#define MEXTI_EXTI10                                10
#define MEXTI_EXTI11                                11
#define MEXTI_EXTI12                                12
#define MEXTI_EXTI13                                13
#define MEXTI_EXTI14                                14
#define MEXTI_EXTI15                                15

#define MEXTI_INT_AT_RISING_EDGE                    0
#define MEXTI_INT_AT_FALLING_EDGE                   1
#define MEXTI_INT_AT_BOTH_EDGES                     2

typedef void (*ptr_to_EXTICallback)(void);
/**
 * @brief: Function to enable external interrupt on one of the EXTI Lines with a specific mode
 * 
 * @param Copy_uint8EXTILine:                   EXTI Line whose interrupt is to be enabled
 * @param Copy_uint8EXTIMode:                   EXTI Mode (Interrupt at rising, falling or both edges)
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                Interrupt on EXTI Line successfully enabled
 * @retval E_NOT_OK:                            Interrupt on EXTI Line not enabled 
 */
Std_ReturnType MEXTI_EnableExternalInterrupt    (uint8 Copy_uint8EXTILine, uint8 Copy_uint8EXTIMode);
/**
 * @brief: Function to disable the external interrupt on one of the EXTI Lines
 * 
 * @param Copy_uint8EXTILine:                   EXTI Line whose interrupt is to be disabled
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                Interrupt on EXTI Line successfully disabled
 * @retval E_NOT_OK:                            Interrupt on EXTI Line not disabled  
 */
Std_ReturnType MEXTI_DisableExternalInterrupt   (uint8 Copy_uint8EXTILine);
/**
 * @brief: Function to trigger External Interrupt on one of the EXTI Lines using software
 * 
 * @param Copy_uint8EXTILine:                   EXTI Line whose interrupt is to be triggered
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                Interrupt on EXTI Line successfully triggered
 * @retval E_NOT_OK:                            Interrupt on EXTI Line not triggered  
 */
Std_ReturnType MEXTI_SoftwareTrigger            (uint8 Copy_uint8EXTILine);
/**
 * @brief: Function to set the function which will be executed when external interrupt on a specific
 *          EXTI Line occurs
 * 
 * @param Copy_uint8EXTILine:                   EXTI Line whose interrupt function is to be set
 * @param P_EXTICallBackFunc:                   Pointer to function that will be executed when EXTI occurs
 *  
 * @return Std_ReturnType
 * @retval E_OK:                                Interrupt function successfully set
 * @retval E_NOT_OK:                            Interrupt function not set 
 */
Std_ReturnType MEXTI_SetCallbackFunction        (uint8 Copy_uint8EXTILine, ptr_to_EXTICallback P_EXTICallBackFunc);
#endif /*_EXTI_INTERFACE_H_*/