/*
 * RCC_int.h
 *
 *  Created on: Aug 8, 2023
 *      Author: Mohanad
 */

#ifndef MCAL_RCC_RCC_INT_H_
#define MCAL_RCC_RCC_INT_H_

#include "../../LIB/STD_TYPES.h"

// A_u32BusId
#define AHB1_			1
#define AHB2_			2
#define APB1_			3
#define APB2_			4
// A_u32Peripheral
#define RCC_GPIOA_EN		0
#define RCC_GPIOB_EN		1
#define RCC_GPIOC_EN		2
#define RCC_GPIOD_EN		3
#define RCC_GPIOE_EN		4
#define RCC_CRC_EN			12
#define RCC_SYSCFG_EN		14
#define RCC_DMA1_EN			21
#define RCC_DMA2_EN			22

void MRCC_vInit(void);

void MRCC_vEnableClock(u32 A_u32BusId, u32 A_u32Peripheral);

void MRCC_vDisableClock(u32 A_u32BusId, u32 A_u32Peripheral);

#endif /* MCAL_RCC_RCC_INT_H_ */
