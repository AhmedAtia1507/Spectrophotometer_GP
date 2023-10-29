/*
 * RCC_prg.c
 *
 *  Created on: Aug 8, 2023
 *      Author: Mohanad
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "RCC_int.h"
#include "RCC_cfg.h"
#include "RCC_prv.h"

void MRCC_vInit(void)
{
	/* 1- CSS (ON/OFF) */
	CLR_BIT(RCC->CR, CSS_ON);		// OFF by default

	/* 2- HSE_BYP */
	CLR_BIT(RCC->CR, HSEBYP);

	/* 3- Select clock switch (HSI/HSE/PLL) */
	SET_BIT(RCC->CFGR, SW0);		// HSI

	/* 4- Bus prescalers */
	RCC->CFGR &= 0xFFFFF0FF;
	RCC->CFGR |= (RCC_AHB_PS << 4);

	/* 5- PLL config */
	SET_BIT(RCC->PLLCFGR, PLLSRC);		// HSI is PLL clock source

	/* 6- Enable The Selected clock (HSI/HSE/PLL) */
#if RCC_HSE_ENABLE == ENABLE
	SET_BIT(RCC->CR, HSE_ON);
//#elseif RCC_HSI_ENABLE == ENABLE
//	SET_BIT(RCC->CR, HSI_ON);
#else
	SET_BIT(RCC->CR, PLL_ON);
#endif
}

void MRCC_vEnableClock(u32 A_u32BusId, u32 A_u32Peripheral)
{
	switch(A_u32BusId)
	{
	case AHB1_:
		SET_BIT(RCC->AHB1ENR, A_u32Peripheral);
		break;
	case AHB2_:
		SET_BIT(RCC->AHB2ENR, A_u32Peripheral);
		break;
	case APB1_:
		SET_BIT(RCC->APB1ENR, A_u32Peripheral);
		break;
	case APB2_:
		SET_BIT(RCC->APB2ENR, A_u32Peripheral);
		break;
	}
}

void MRCC_vDisableClock(u32 A_u32BusId, u32 A_u32Peripheral)
{
	switch(A_u32BusId)
	{
	case AHB1_:
		SET_BIT(RCC->AHB1RSTR, A_u32Peripheral);
		break;
	case AHB2_:
		SET_BIT(RCC->AHB2RSTR, A_u32Peripheral);
		break;
	case APB1_:
		SET_BIT(RCC->APB1RSTR, A_u32Peripheral);
		break;
	case APB2_:
		SET_BIT(RCC->APB2RSTR, A_u32Peripheral);
		break;
	}
}
