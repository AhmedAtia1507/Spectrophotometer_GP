/*
 * STK_int.h
 *
 *  Created on: Aug 23, 2023
 *      Author: Mohanad
 */

#include "../../LIB/STD_TYPES.h"

void MSTK_vInit(void);
void MSTK_vStartTimer(void);
void MSTK_vStopTimer(void);
void MSTK_vSetBusyWait(uint32 A_u32Tick);
void MSTK_vSetInterval_Single  (uint32 A_u32Tick , void(*CallBackFun)(void));
void MSTK_vSetInterval_Periodic(uint32 A_u32Tick , void(*CallBackFun)(void));
uint32 MSTK_u32GetElapsedTime(void);
uint32 MSTK_u32GetRemainingTime(void);
