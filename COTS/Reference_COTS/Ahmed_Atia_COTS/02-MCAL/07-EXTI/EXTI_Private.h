/**
 * @file EXTI_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-09-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _EXTI_PRIVATE_H_
#define _EXTI_PRIVATE_H_

typedef struct EXTI_Registers
{
    /*Interrupt Mask Register*/
    volatile u32 IMR;
    /*Event Mask Register*/
    volatile u32 EMR;
    /*Rising Trigger Selection Register*/
    volatile u32 RTSR;
    /*Falling Trigger Selection Register*/
    volatile u32 FTSR;
    /*Software Interrupt Event Register*/
    volatile u32 SWIER;
    /*Pending Register*/
    volatile u32 PR;
}EXTI_RegDef_t;

#define EXTI_BASE_ADDRESS                       0x40010400U
#define EXTI                                    ((EXTI_RegDef_t *)(EXTI_BASE_ADDRESS))     
#endif /*_EXTI_PRIVATE_H_*/