/*
 * EXTI_prv.h
 *
 *  Created on: Aug 14, 2023
 *      Author: Mohanad
 */

#ifndef MCAL_EXTI_EXTI_PRV_H_
#define MCAL_EXTI_EXTI_PRV_H_

#define EXTI_BASE_ADDRESS		0x40013C00
#define SYSCFG_BASE_ADDRESS		0x40013800

typedef struct
{
	u32 IMR;
	u32 EMR;
	u32 RTSR;
	u32 FTSR;
	u32 SWIER;
	u32 PR;
}EXTI_MemMap_t;		// t --> table

typedef struct
{
	u32 MEMRMP;
	u32 PMC;
	u32 EXTICR[4];
	u32 RESERVED_1;
	u32 RESERVED_2;
	u32 CMPCR;
}SYSCFG_MemMap_t;

#define EXTI		((volatile EXTI_MemMap_t*)EXTI_BASE_ADDRESS)
#define SYSCFG		((volatile SYSCFG_MemMap_t*)SYSCFG_BASE_ADDRESS)

#endif /* MCAL_EXTI_EXTI_PRV_H_ */
