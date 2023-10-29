/*
 * NVIC_prv.h
 *
 *  Created on: Aug 14, 2023
 *      Author: Mohanad
 */

#ifndef MCAL_NVIC_NVIC_PRV_H_
#define MCAL_NVIC_NVIC_PRV_H_

#include "../../LIB/STD_TYPES.h"

#define NVIC_BASE_ADDRESS	0xE000E100
#define SCB_BASE_ADDRESS	0xE000ED00

typedef struct
{
	u32 ISER[32];
	u32 ICER[32];
	u32 ISPR[32];
	u32 ICPR[32];
	u32 IABR[64];
	u8 IPR[240];
}NVIC_MemMap_t;

typedef struct
{
	u32 CPUID;
	u32 ICSR;
	u32 VTOR;
	u32 AIRCR;
	u32 SCR;
	u32 CCR;
	u32 SHPR1;
	u32 SHPR2;
	u32 SHPR3;
	u32 SHCSR;
	u32 CFSR;
	u32 HFSR;
	u32 RESERVED;
	u32 MMAR;
	u32 BFAR;
	u32 AFSR;
}SCB_MemMap_t;

#define NVIC	((volatile NVIC_MemMap_t*)(NVIC_BASE_ADDRESS))
#define SCB		((volatile SCB_MemMap_t*)(SCB_BASE_ADDRESS))

#endif /* MCAL_NVIC_NVIC_PRV_H_ */
