/*
 * EXTI_prg.c
 *
 *  Created on: Aug 14, 2023
 *      Author: Mohanad
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "EXTI_int.h"
#include "EXTI_prv.h"
#include "../GPIO/GPIO_int.h"

void (*CallBack[16])(void) = {0};

void MEXTI_vEnableLine(u8 A_u8Line, u8 A_u8Trigger)
{
	if(A_u8Line < 16)
	{
		SET_BIT(EXTI->IMR, A_u8Line);
		MEXTI_vSetTrigger(A_u8Line, A_u8Trigger);
	}
}

void MEXTI_vDisableLine(u8 A_u8Line)
{
	if(A_u8Line < 16)
	{
		CLR_BIT(EXTI->IMR, A_u8Line);
	}
}

void MEXTI_vSetTrigger(u8 A_u8Line, u8 A_u8Trigger)
{
	if(A_u8Line < 16)
	{
		switch(A_u8Trigger)
		{
		case EXTI_RISING:
			SET_BIT(EXTI->RTSR, A_u8Line);
			CLR_BIT(EXTI->FTSR, A_u8Line);
			break;
		case EXTI_FALLING:
			CLR_BIT(EXTI->RTSR, A_u8Line);
			SET_BIT(EXTI->FTSR, A_u8Line);
			break;
		case EXTI_ONCHANGE:
			SET_BIT(EXTI->RTSR, A_u8Line);
			SET_BIT(EXTI->FTSR, A_u8Line);
			break;
		}
	}
}

void MEXTI_vSoftwareTrigger(u8 A_u8Line)	// used for testing
{
	SET_BIT(EXTI->SWIER, A_u8Line);
}

void MEXTI_vClearFlag(u8 A_u8Line)
{
	EXTI->PR = (1 << A_u8Line);
}

void MEXTI_vSetCallBack(u8 A_u8Line, void (*A_ptr)(void))
{
	switch(A_u8Line)
	{
	case EXTI_LINE0:
		CallBack[0] = A_ptr;
		break;
	case EXTI_LINE1:
		CallBack[1] = A_ptr;
		break;
	case EXTI_LINE2:
		CallBack[2] = A_ptr;
		break;
	case EXTI_LINE3:
		CallBack[3] = A_ptr;
		break;
	case EXTI_LINE4:
		CallBack[4] = A_ptr;
		break;
	case EXTI_LINE5:
	case EXTI_LINE6:
	case EXTI_LINE7:
	case EXTI_LINE8:
	case EXTI_LINE9:
		CallBack[5] = A_ptr;
		break;
	case EXTI_LINE10:
	case EXTI_LINE11:
	case EXTI_LINE12:
	case EXTI_LINE13:
	case EXTI_LINE14:
	case EXTI_LINE15:
		CallBack[11] = A_ptr;
		break;
	}
}

void MEXTI_vSelectionLineCfg(u8 A_u8PortId, u8 A_u8PinNo)
{
	SYSCFG->EXTICR[A_u8PinNo/4] |= A_u8PortId << ((A_u8PinNo%4)*4);
}

void EXTI0_IRQHandler(void)
{
	MEXTI_vClearFlag(EXTI_LINE0);
	if(CallBack[EXTI_LINE0] != 0)
	{
		CallBack[EXTI_LINE0]();
	}
}

void EXTI1_IRQHandler(void)
{
	MEXTI_vClearFlag(EXTI_LINE1);
	if(CallBack[EXTI_LINE1] != 0)
	{
		CallBack[EXTI_LINE1]();
	}
}

void EXTI2_IRQHandler(void)
{
	MEXTI_vClearFlag(EXTI_LINE2);
	if(CallBack[EXTI_LINE2] != 0)
	{
		CallBack[EXTI_LINE2]();
	}
}

void EXTI3_IRQHandler(void)
{
	MEXTI_vClearFlag(EXTI_LINE3);
	if(CallBack[EXTI_LINE3] != 0)
	{
		CallBack[EXTI_LINE3]();
	}
}

void EXTI4_IRQHandler(void)
{
	MEXTI_vClearFlag(EXTI_LINE4);
	if(CallBack[EXTI_LINE4] != 0)
	{
		CallBack[EXTI_LINE4]();
	}
}

void EXTI9_5_IRQHandler(void)
{
	MEXTI_vClearFlag(EXTI_LINE5);
	if(CallBack[EXTI_LINE5] != 0)
	{
		CallBack[EXTI_LINE5]();
	}
}

void EXTI15_10_IRQHandler(void)
{
	MEXTI_vClearFlag(EXTI_LINE11);
	if(CallBack[EXTI_LINE11] != 0)
	{
		CallBack[EXTI_LINE11]();
	}
}
