/*
 * EXTI_int.h
 *
 *  Created on: Aug 14, 2023
 *      Author: Mohanad
 */

#ifndef MCAL_EXTI_EXTI_INT_H_
#define MCAL_EXTI_EXTI_INT_H_

enum
{
	EXTI_LINE0,
	EXTI_LINE1,
	EXTI_LINE2,
	EXTI_LINE3,
	EXTI_LINE4,
	EXTI_LINE5,
	EXTI_LINE6,
	EXTI_LINE7,
	EXTI_LINE8,
	EXTI_LINE9,
	EXTI_LINE10,
	EXTI_LINE11,
	EXTI_LINE12,
	EXTI_LINE13,
	EXTI_LINE14,
	EXTI_LINE15
};

enum
{
	EXTI_RISING,
	EXTI_FALLING,
	EXTI_ONCHANGE,
};

// A_u8PortId
#define PA	0b0000
#define PB	0b0001
#define PC	0b0010
#define PD	0b0011
#define PE	0b0100
#define PH	0b0111

void MEXTI_vEnableLine(u8 A_u8Line, u8 A_u8Trigger);

void MEXTI_vDisableLine(u8 A_u8Line);

void MEXTI_vSetTrigger(u8 A_u8Line, u8 A_u8Trigger);

void MEXTI_vSoftwareTrigger(u8 A_u8Line);	// used for testing

void MEXTI_vClearFlag(u8 A_u8Line);

void MEXTI_vSetCallBack(u8 A_u8Line, void (*A_ptr)(void));

void MEXTI_vSelectionLineCfg(u8 A_u8PortId, u8 A_u8PinNo);

#endif /* MCAL_EXTI_EXTI_INT_H_ */
