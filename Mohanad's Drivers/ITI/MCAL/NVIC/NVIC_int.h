/*
 * NVIC_int.h
 *
 *  Created on: Aug 14, 2023
 *      Author: Mohanad
 */

#ifndef MCAL_NVIC_NVIC_INT_H_
#define MCAL_NVIC_NVIC_INT_H_

#include "../../LIB/STD_TYPES.h"

#define NVIC_16_GROUPS   0b011  // 3
#define NVIC_8_GROUPS    0b100  // 4
                                // 5   6  7

#define  NVIC_SYSTICK       -5
#define  NVIC_PEND_SV       -6
#define  NVIC_SV_CALL       -4
#define NVIC_USAGE_FAULT    -1
#define NVIC_BUS_FAULT      -2
#define NVIC_MEMORY_MANAGE  -3

#define NVIC_EXTI0			6
#define NVIC_EXTI1			7
#define NVIC_EXTI2			8
#define NVIC_EXTI3			9
#define NVIC_EXTI4			10
#define NVIC_EXTI9_5		23
#define NVIC_EXTI15_10		40
#define NVIC_USART1			37
#define NVIC_USART2			38
#define NVIC_USART6			71

void MNVIC_vEnableInterruptPeripheral(u8 A_u8IntId);
void MNVIC_vDisableInterruptPeripheral(u8 A_u8IntId);
void MNVIC_vSetPending(u8 A_u8IntId);
void MNVIC_vClearPending(u8 A_u8IntId);
u8 MNVIC_u8GetPending();
void MNVIC_vSetPriorityCfg(u8 A_u8GroupPriority);
void MNVIC_vSetPriority(s8 A_s8IntId , u8 A_u8GroupPriority,u8 A_u8SubPriority);

#endif /* MCAL_NVIC_NVIC_INT_H_ */
