/*
 * STK_prg.c
 *
 *  Created on: Aug 23, 2023
 *      Author: Mohanad
 */

#include "STK_int.h"
#include "STK_prv.h"
#include "STK_cfg.h"

u8 G_u8Flag;
void (*G_vCallBack) (void) = 0 ;

void MSTK_vInit(void)
{
	/* Choose Clk source */
	switch(STK_CLK_SOURCE)
	{
	case STK_AHB:
		SET_BIT(STK->CTRL, CLKSOURCE);
		break;
	case STK_AHB_PS_8:
		CLR_BIT(STK->CTRL, CLKSOURCE);
		break;
	}

	/* Interrupt enable or disable */
	switch(STK_INTERRUPT_EN)
	{
	case ENABLE:
		SET_BIT(STK->CTRL, TICKINT);
		break;
	case DISABLE:
		CLR_BIT(STK->CTRL, TICKINT);
		break;
	}

	/* Disable Timer */
	CLR_BIT(STK->CTRL, STK_ENABLE);
}

void MSTK_vStartTimer(void)
{
	SET_BIT(STK->CTRL, STK_ENABLE);
}

void MSTK_vStopTimer(void)
{
	CLR_BIT(STK->CTRL, STK_ENABLE);
}

void  MSTK_vSetBusyWait(u32 A_u32Tick)
{
	STK->VAL = 0;
	STK->LOAD = A_u32Tick;
	MSTK_vStartTimer();
	while(!GET_BIT(STK->CTRL, COUNTFLAG));
	MSTK_vStopTimer();
}

void MSTK_vSetInterval_Single  (u32 A_u32Tick , void(*CallBackFun)(void))
{
	G_u8Flag = SINGLE;
	G_vCallBack = CallBackFun;
	STK->VAL = 0;
	STK->LOAD = A_u32Tick;
	SET_BIT(STK->CTRL, TICKINT);
	MSTK_vStartTimer();
}

void MSTK_vSetInterval_Periodic(u32 A_u32Tick , void(*CallBackFun)(void))
{
	G_u8Flag = PERIODIC;
	G_vCallBack = CallBackFun;
	STK->VAL = 0;
	STK->LOAD = A_u32Tick;
	SET_BIT(STK->CTRL, TICKINT);
	MSTK_vStartTimer();
}

u32 MSTK_u32GetElapsedTime(void)
{
	return  (STK->LOAD-STK->VAL) ;
}

u32 MSTK_u32GetRemainingTime(void)
{
	return  (STK->VAL) ;
}

void SysTick_Handler(void)
{
	if(G_vCallBack != 0)
	{
		G_vCallBack();
	}
	if(G_u8Flag == SINGLE)
	{
		G_u8Flag = PERIODIC;
		MSTK_vStopTimer();
	}
}
