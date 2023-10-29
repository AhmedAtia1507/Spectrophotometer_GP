/*
 * NVIC_prg.c
 *
 *  Created on: Aug 14, 2023
 *      Author: Mohanad
 */
#include "NVIC_int.h"
#include "NVIC_prv.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

static u8 A_u8GroupPriorty ;

void MNVIC_vEnableInterruptPeripheral(u8 A_u8IntId)
{
	NVIC->ISER[A_u8IntId/32] = 1 << (A_u8IntId%32);
};

void MNVIC_vDisableInterruptPeripheral(u8 A_u8IntId)
{
	NVIC->ICER[A_u8IntId/32] = 1 << (A_u8IntId%32);
};

void MNVIC_vSetPending(u8 A_u8IntId)
{
	NVIC->ISPR[A_u8IntId/32] = 1 << (A_u8IntId%32);
};

void MNVIC_vClearPending(u8 A_u8IntId)
{
	NVIC->ICPR[A_u8IntId/32] = 1 << (A_u8IntId%32);
};

u8 MNVIC_u8GetPending(A_u8IntId)
{
	return GET_BIT(NVIC->IABR[A_u8IntId/32], (A_u8IntId%32));
};

void MNVIC_vSetPriorityCfg(u8 A_u8Group)
{
	A_u8GroupPriorty = 0x05FA0000 | (A_u8Group<<8);
	SCB->AIRCR = A_u8GroupPriorty  ;
}

void MNVIC_vSetPriority(s8 A_s8IntId , u8 A_u8GroupPriority,u8 A_u8SubPriority)
{
	u32 L_u32Periority = (SCB->AIRCR & (0x00000700)>>8);
	/*configure software periority of Group Priority and Sub Priority*/
	L_u32Periority = A_u8SubPriority | (A_u8GroupPriority<<(L_u32Periority - 3)) ;
	/*interrupts of core peripheral*/
	if (A_s8IntId < 0)
	{
		if (A_s8IntId     == NVIC_MEMORY_MANAGE     ||
				A_s8IntId == NVIC_BUS_FAULT     ||
				A_s8IntId == NVIC_USAGE_FAULT
		)
		{
			A_s8IntId += 3;
			SCB->SHPR1 &= ~((0b1111)        << ((8 * A_s8IntId) + 4));
			SCB->SHPR1 |=  ((L_u32Periority) << ((8 * A_s8IntId) + 4));
		}
		else if(A_s8IntId == NVIC_SV_CALL)
		{
			A_s8IntId += 7;
			SCB->SHPR2 &= ~((0b1111)        << ((8 * A_s8IntId) + 4));
			SCB->SHPR2 |=  ((L_u32Periority) << ((8 * A_s8IntId) + 4));
		}
		else if (A_s8IntId == NVIC_PEND_SV || A_s8IntId == NVIC_SYSTICK)
		{
			A_s8IntId += 8;
			SCB->SHPR3 &= ~((0b1111)        << ((8 * A_s8IntId) + 4));
			SCB->SHPR3 |=  ((L_u32Periority) << ((8 * A_s8IntId) + 4));
		}
	}
	/*interrupts of vendor peripheral*/
	else if (A_s8IntId >= 0)
	{
		NVIC -> IPR [A_s8IntId] = L_u32Periority << 4 ;
	}
}
