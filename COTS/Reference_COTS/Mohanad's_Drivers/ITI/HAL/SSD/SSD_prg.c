/*
 * SSD_prg.c
 *
 *  Created on: Aug 22, 2023
 *      Author: Mohanad
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "SSD_int.h"
#include "../../MCAL/GPIO/GPIO_int.h"

static u8 G_u8SsdArr[10] = {
		0x3F,     // 0
		0x06,     // 1
		0x5B,
		0x4f,
		0x66,
		0x6D,
		0x7D,
		0x07,
		0x7F,
		0x6F       //9
};

void HSSD_vInit(SSD_cfg_t *A_xptr)
{
	u8 L_u8Iterator;
	for(L_u8Iterator = 0; L_u8Iterator < 7; L_u8Iterator++)
	{
		MGPIO_vSetPinMode(A_xptr[L_u8Iterator].port, A_xptr[L_u8Iterator].pin, GPIO_MODE_OUTPUT);
		MGPIO_vSetPinOutputType(A_xptr[L_u8Iterator].port, A_xptr[L_u8Iterator].pin, GPIO_OUTTYPE_PUSHPULL);
		MGPIO_vSetPinOutputType(A_xptr[L_u8Iterator].port, A_xptr[L_u8Iterator].pin, GPIO_OUTSPEED_LOW);
	}
}

void HSSD_vDisplay(SSD_cfg_t *A_xptr,u8 A_u8Val,u8 A_u8Type)
{
	u8 L_u8Iterator;
	if(A_u8Type == SSD_COMMON_CATHOD)
	{
		for(L_u8Iterator = 0; L_u8Iterator < 7; L_u8Iterator++)
		{
			MGPIO_vSetPinValue(A_xptr[L_u8Iterator].port, A_xptr[L_u8Iterator].pin, GET_BIT(G_u8SsdArr[A_u8Val], L_u8Iterator));
		}
	}
	else if(A_u8Type == SSD_COMMON_ANODE)
	{
		for(L_u8Iterator = 0; L_u8Iterator < 7; L_u8Iterator++)
		{
			MGPIO_vSetPinValue(A_xptr[L_u8Iterator].port, A_xptr[L_u8Iterator].pin, !GET_BIT(G_u8SsdArr[A_u8Val], L_u8Iterator));
		}
	}
}

void HSSD_vTurnOff(SSD_cfg_t *A_xptr,u8 A_u8Type)
{
	u8 L_u8Iterator;
	if(A_u8Type == SSD_COMMON_CATHOD)
	{
		for(L_u8Iterator = 0; L_u8Iterator < 7; L_u8Iterator++)
		{
			MGPIO_vSetPinValue(A_xptr[L_u8Iterator].port, A_xptr[L_u8Iterator].pin, GPIO_LOW);
		}
	}
	else if(A_u8Type == SSD_COMMON_ANODE)
	{
		for(L_u8Iterator = 0; L_u8Iterator < 7; L_u8Iterator++)
		{
			MGPIO_vSetPinValue(A_xptr[L_u8Iterator].port, A_xptr[L_u8Iterator].pin, GPIO_HIGH);
		}
	}
}
