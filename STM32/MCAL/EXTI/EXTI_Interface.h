/**
 * @file EXTI_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
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
#define MEXTI_EXTI16                                16
#define MEXTI_EXTI17                                17
#define MEXTI_EXTI18                                18
#define MEXTI_EXTI19                                19

#define MEXTI_INT_AT_RISING_EDGE                    0
#define MEXTI_INT_AT_FALLING_EDGE                   1
#define MEXTI_INT_AT_BOTH_EDGES                     2

typedef void (*ptr_to_EXTICallback)(void);

Std_ReturnType MEXTI_EnableExternalInterrupt(uint8 Copy_uint8EXTILine, uint8 Copy_uint8EXTIMode);
Std_ReturnType MEXTI_DisableExternalInterrupt(uint8 Copy_uint8EXTILine);
Std_ReturnType MEXTI_SoftwareTrigger(uint8 Copy_uint8EXTILine);
Std_ReturnType MEXTI_SetCallbackFunction(uint8 Copy_uint8EXTILine, ptr_to_EXTICallback P_EXTICallBackFunc);
#endif /*_EXTI_INTERFACE_H_*/