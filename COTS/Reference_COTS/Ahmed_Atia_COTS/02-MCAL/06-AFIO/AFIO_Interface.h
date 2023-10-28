/**
 * @file AFIO_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-09-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _AFIO_INTERFACE_H_
#define _AFIO_INTERFACE_H_

#define AFIO_EXTI0                                      0
#define AFIO_EXTI1                                      1
#define AFIO_EXTI2                                      2
#define AFIO_EXTI3                                      3
#define AFIO_EXTI4                                      4
#define AFIO_EXTI5                                      5
#define AFIO_EXTI6                                      6
#define AFIO_EXTI7                                      7
#define AFIO_EXTI8                                      8
#define AFIO_EXTI9                                      9
#define AFIO_EXTI10                                     10
#define AFIO_EXTI11                                     11
#define AFIO_EXTI12                                     12
#define AFIO_EXTI13                                     13
#define AFIO_EXTI14                                     14
#define AFIO_EXTI15                                     15

#define AFIO_PORTA_PIN                                  0b0000
#define AFIO_PORTB_PIN                                  0b0001
#define AFIO_PORTC_PIN                                  0b0010
#define AFIO_PORTD_PIN                                  0b0011
#define AFIO_PORTE_PIN                                  0b0100
#define AFIO_PORTF_PIN                                  0b0101
#define AFIO_PORTG_PIN                                  0b0110

Std_ReturnType MAFIO_u8SetEXTIPinConfigurations(u8 Copy_u8EXTILine, u8 Copy_u8Port);
#endif /*_AFIO_INTERFACE_H_*/