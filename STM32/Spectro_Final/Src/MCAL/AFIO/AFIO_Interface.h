/**
 * @file AFIO_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * 
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _AFIO_INTERFACE_H_
#define _AFIO_INTERFACE_H_

#define MAFIO_EXTI0                                     0
#define MAFIO_EXTI1                                     1
#define MAFIO_EXTI2                                     2
#define MAFIO_EXTI3                                     3
#define MAFIO_EXTI4                                     4
#define MAFIO_EXTI5                                     5
#define MAFIO_EXTI6                                     6
#define MAFIO_EXTI7                                     7
#define MAFIO_EXTI8                                     8
#define MAFIO_EXTI9                                     9
#define MAFIO_EXTI10                                    10
#define MAFIO_EXTI11                                    11
#define MAFIO_EXTI12                                    12
#define MAFIO_EXTI13                                    13
#define MAFIO_EXTI14                                    14
#define MAFIO_EXTI15                                    15

#define MAFIO_PORTA_PIN                                 0b0000
#define MAFIO_PORTB_PIN                                 0b0001
#define MAFIO_PORTC_PIN                                 0b0010
#define MAFIO_PORTD_PIN                                 0b0011
#define MAFIO_PORTE_PIN                                 0b0100
#define MAFIO_PORTF_PIN                                 0b0101
#define MAFIO_PORTG_PIN                                 0b0110
/**
 * @brief: Function to set EXTI pin configurations for a specified EXTI Line
 * 
 * @param Copy_uint8EXTILine:               EXTI Line to be configured (0-15)
 * @param Copy_uint8Port:                   Port to configure the EXTI Line for (A-G)
 * 
 * @return Std_ReturnType
 * @retval E_OK:                            Configuration Successfully Set
 * @retval E_NOT_OK:                        Configuration not set 
 */
Std_ReturnType MAFIO_SetEXTIPinConfigurations(uint8 Copy_uint8EXTILine, uint8 Copy_uint8Port);
#endif /*_AFIO_INTERFACE_H_*/