/**
 * @file EXTI_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _EXTI_PRIVATE_H_
#define _EXTI_PRIVATE_H_

typedef struct EXTI_Registers
{
    /*Interrupt Mask Register*/
    volatile uint32 IMR;
    /*Event Mask Register*/
    volatile uint32 EMR;
    /*Rising Trigger Selection Register*/
    volatile uint32 RTSR;
    /*Falling Trigger Selection Register*/
    volatile uint32 FTSR;
    /*Software Interrupt Event Register*/
    volatile uint32 SWIER;
    /*Pending Register*/
    volatile uint32 PR;
}MEXTI_RegDef_t;

#define MEXTI_BASE_ADDRESS                       0x40010400U
#define MEXTI                                    ((MEXTI_RegDef_t *)(MEXTI_BASE_ADDRESS))     
#endif /*_EXTI_PRIVATE_H_*/