/*
 * TIM2_5_Interface.h
 *
 *  Created on: Nov 21, 2023
 *      Author: Mohanad
 */

#ifndef MCAL_TIM2_5_TIM2_5_INTERFACE_H_
#define MCAL_TIM2_5_TIM2_5_INTERFACE_H_

#define TIM2_BASE_ADDRESS		0x40000000
#define TIM3_BASE_ADDRESS		0x40000400
#define TIM4_BASE_ADDRESS		0x40000800
#define TIM5_BASE_ADDRESS		0x40000C00

typedef struct
{
	u32 CR1;
	u32 CR2;
	u32 SMCR;
	u32 DIER;
	u32 SR;
	u32 EGR;
	u32 CCMR1;
	u32 CCMR2;
	u32 CCER;
	u32 CNT;
	u32 PSC;
	u32 ARR;
	u32 reserved_0;
	u32 CCR1;
	u32 CCR2;
	u32 CCR3;
	u32 CCR4;
	u32 reserved_1;
	u32 DCR;
	u32 DMAR;
}TIMx_MemMap_t;

#define TIM2	((volatile TIMx_MemMap_t*)(TIM2_BASE_ADDRESS))
#define TIM3	((volatile TIMx_MemMap_t*)(TIM3_BASE_ADDRESS))
#define TIM4	((volatile TIMx_MemMap_t*)(TIM4_BASE_ADDRESS))
#define TIM5	((volatile TIMx_MemMap_t*)(TIM5_BASE_ADDRESS))

#endif /* MCAL_TIM2_5_TIM2_5_INTERFACE_H_ */
