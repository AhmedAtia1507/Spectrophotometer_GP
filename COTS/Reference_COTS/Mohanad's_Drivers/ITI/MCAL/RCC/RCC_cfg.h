/*
 * RCC_cfg.h
 *
 *  Created on: Aug 8, 2023
 *      Author: Mohanad
 */

#ifndef MCAL_RCC_RCC_CFG_H_
#define MCAL_RCC_RCC_CFG_H_

/*
 * ENABLE
 * DISABLE
 */
#define RCC_HSE_ENABLE		ENABLE
#define RCC_HSI_ENABLE		DISABLE
#define RCC_PLL_ENABLE		DISABLE

/*
 * RCC_AHB_PS_0
 * RCC_AHB_PS_2
 * RCC_AHB_PS_4
 * RCC_AHB_PS_8
 * RCC_AHB_PS_16
 * RCC_AHB_PS_64
 * RCC_AHB_PS_128
 * RCC_AHB_PS_256
 * RCC_AHB_PS_512
 */
#define RCC_AHB_PS			RCC_AHB_PS_0

#endif /* MCAL_RCC_RCC_CFG_H_ */
