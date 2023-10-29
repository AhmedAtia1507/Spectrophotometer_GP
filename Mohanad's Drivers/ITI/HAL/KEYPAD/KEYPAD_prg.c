/*
 * KEYPAD_prg.c
 *
 *  Created on: Sep 7, 2023
 *      Author: Mohanad
 */

#include "KEYPAD_int.h"
#include "KEYPAD_cfg.h"
#include "../../MCAL/GPIO/GPIO_int.h"
#include "../../LIB/BIT_MATH.h"

extern u8 KeypadRowPins[NUM_OF_ROWS];
extern u8 KeypadColPins[NUM_OF_COLUMNS];
extern u8 Keypad_u8Values[NUM_OF_ROWS][NUM_OF_COLUMNS];

u8 HKEYPAD_vGetPressedKey()
{
	u8 L_u8Return = 0;
	u8 L_u8Col;
	u8 L_u8Row;
	for(L_u8Col = 0; L_u8Col < NUM_OF_COLUMNS; L_u8Col++)
	{
		MGPIO_vSetPinValue(KEYPAD_PORT, KeypadColPins[L_u8Col], GPIO_LOW);
		for(L_u8Row = 0; L_u8Row < NUM_OF_ROWS; L_u8Row++)
		{
			if(!MGPIO_u8GetPinValue(KEYPAD_PORT, KeypadRowPins[L_u8Row]))
			{
				L_u8Return = Keypad_u8Values[L_u8Row][L_u8Col];
			}
		}
		MGPIO_vSetPinValue(KEYPAD_PORT, KeypadColPins[L_u8Col], GPIO_HIGH);
	}
	return L_u8Return;
}
