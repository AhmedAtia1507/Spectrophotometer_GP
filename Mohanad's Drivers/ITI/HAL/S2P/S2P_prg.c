/*
 * S2P_prg.c
 *
 *  Created on: Aug 22, 2023
 *      Author: admin
 */


#include  "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_int.h"
#include "../../MCAL/SYSTICK/STK_int.h"

#include "S2P_cfg.h"
#include "S2P_prv.h"
#include "S2P_int.h"
extern GPIO_cfg_t  S2P_ShiftPin ;
extern GPIO_cfg_t  S2P_LatchPin ;
extern GPIO_cfg_t  S2P_DataPin ;

static void S2P_svShiftData(void)
{
	MGPIO_vSetPinValue(S2P_ShiftPin.port,S2P_ShiftPin.pin,GPIO_HIGH);
	/*delay*/
	MSTK_vSetBusyWait(1);//1u
	MGPIO_vSetPinValue(S2P_ShiftPin.port,S2P_ShiftPin.pin,GPIO_LOW);
	/*delay*/
	MSTK_vSetBusyWait(1);
}
static void S2P_svLatchData(void)
{
	MGPIO_vSetPinValue(S2P_LatchPin.port,S2P_LatchPin.pin,GPIO_HIGH);
	/*delay*/
	MSTK_vSetBusyWait(1);
	MGPIO_vSetPinValue(S2P_LatchPin.port,S2P_LatchPin.pin,GPIO_LOW);
	/*delay*/
	MSTK_vSetBusyWait(1);
}
void HS2P_vInit(void)
{
	MGPIO_vInit(&S2P_ShiftPin);
	MGPIO_vInit(&S2P_LatchPin);
	MGPIO_vInit(&S2P_DataPin);
}
void HS2P_vSendData(u32 A_u32Data)
{
	/*put data on data pin*/ //1
	/*shift 1 0*/ // 1110  1010
	for(int i=0;i<8*S2P_NUMBER_OF_REGS;i++)
	{
		MGPIO_vSetPinValue(S2P_DataPin.port,S2P_DataPin.pin,GET_BIT(A_u32Data,i));
		S2P_svShiftData();
	}
	/*latch 1 0*/
	S2P_svLatchData();
}

void HS2P_vSendData_Arr(u8 *A_u8Data , u8 A_u8Size) // 0b1110101
{
	/*put data on data pin*/ //1
	/*shift 1 0*/ // 1110  1010
	for(int j=0;j<A_u8Size;j++)
	{
		for(int i=0;i<8;i++)
		{
			MGPIO_vSetPinValue(S2P_DataPin.port,S2P_DataPin.pin,GET_BIT(A_u8Data[j],i));
			S2P_svShiftData();
		}
	}
	/*latch 1 0*/
	S2P_svLatchData();
}


