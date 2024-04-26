/*
 * STK_prv.h
 *
 *  Created on: Aug 23, 2023
 *      Author: Mohanad
 */

#ifndef MCAL_SYSTICK_STK_PRV_H_
#define MCAL_SYSTICK_STK_PRV_H_

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#define STK_BASE_ADDRESS		0xE000E010

typedef struct
{
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;
}STK_MemMap_t;

#define STK		((volatile STK_MemMap_t*)(STK_BASE_ADDRESS))

#define CLKSOURCE			2
#define TICKINT				1
#define STK_ENABLE			0
#define COUNTFLAG			16

#define STK_AHB				1
#define STK_AHB_PS_8		8
#define ENABLE				1
#define DISABLE				0
enum{
	SINGLE,
	PERIODIC
};
#endif /* MCAL_SYSTICK_STK_PRV_H_ */
