/*
 * LCD_prg.c
 *
 *  Created on: Sep 7, 2023
 *      Author: Mohanad
 */

#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "LCD_cfg.h"
#include "LCD_int.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/SYSTICK/STK_int.h"

void HLCD_vInit()
{
	MSTK_vInit();

	/* Delay 30ms to ensure the initialization of the LCD driver */
	MSTK_vSetBusyWait(LCD_TICKS);

	/* Return Home  */
	HLCD_vSendCmd(LCD_HOME);
	MSTK_vSetBusyWait(LCD_TICKS);

	/* Function Set  */
	HLCD_vSendCmd(LCD_SET_8BIT);
	MSTK_vSetBusyWait(LCD_TICKS);

	/* Display ON OFF Control */
	HLCD_vSendCmd(LCD_DISPLAY_ON);
	MSTK_vSetBusyWait(LCD_TICKS);

	/* Clear Display */
	HLCD_vSendCmd(LCD_CLEAR);
	MSTK_vSetBusyWait(LCD_TICKS);

	/* Entry Mode Set  */
	HLCD_vSendCmd(LCD_ENTRY_MODE);
	MSTK_vSetBusyWait(LCD_TICKS);

}

void HLCD_vSendCmd(u8 COMMAND)
{
	/* Set RS to low */
	MGPIO_u8SetPinValue(LCD_PORT, RS_PIN, GPIO_LOW);

	/* Set RW to low */
	MGPIO_u8SetPinValue(LCD_PORT, RW_PIN, GPIO_LOW);

	/* Set E to high */
	MGPIO_u8SetPinValue(LCD_PORT, E_PIN, GPIO_HIGH);

	/* Load command to data register */
	MGPIO_u8SetPinValue(LCD_PORT, D0_PIN, GET_BIT(COMMAND, 0));
	MGPIO_u8SetPinValue(LCD_PORT, D1_PIN, GET_BIT(COMMAND, 1));
	MGPIO_u8SetPinValue(LCD_PORT, D2_PIN, GET_BIT(COMMAND, 2));
	MGPIO_u8SetPinValue(LCD_PORT, D3_PIN, GET_BIT(COMMAND, 3));
	MGPIO_u8SetPinValue(LCD_PORT, D4_PIN, GET_BIT(COMMAND, 4));
	MGPIO_u8SetPinValue(LCD_PORT, D5_PIN, GET_BIT(COMMAND, 5));
	MGPIO_u8SetPinValue(LCD_PORT, D6_PIN, GET_BIT(COMMAND, 6));
	MGPIO_u8SetPinValue(LCD_PORT, D7_PIN, GET_BIT(COMMAND, 7));

	/* Set E to low */
	MGPIO_u8SetPinValue(LCD_PORT, E_PIN, GPIO_LOW);

	/* Wait 2 ms */
	MSTK_vSetBusyWait(LCD_TICKS);

}

void HLCD_vWriteChar(u8 Character)
{
	/* Set RS to low */
	MGPIO_u8SetPinValue(LCD_PORT, RS_PIN, GPIO_HIGH);

	/* Set RW to low */
	MGPIO_u8SetPinValue(LCD_PORT, RW_PIN, GPIO_LOW);

	/* Set E to high */
	MGPIO_u8SetPinValue(LCD_PORT, E_PIN, GPIO_HIGH);

	/* Load command to data register */
	MGPIO_u8SetPinValue(LCD_PORT, D0_PIN, GET_BIT(Character, 0));
	MGPIO_u8SetPinValue(LCD_PORT, D1_PIN, GET_BIT(Character, 1));
	MGPIO_u8SetPinValue(LCD_PORT, D2_PIN, GET_BIT(Character, 2));
	MGPIO_u8SetPinValue(LCD_PORT, D3_PIN, GET_BIT(Character, 3));
	MGPIO_u8SetPinValue(LCD_PORT, D4_PIN, GET_BIT(Character, 4));
	MGPIO_u8SetPinValue(LCD_PORT, D5_PIN, GET_BIT(Character, 5));
	MGPIO_u8SetPinValue(LCD_PORT, D6_PIN, GET_BIT(Character, 6));
	MGPIO_u8SetPinValue(LCD_PORT, D7_PIN, GET_BIT(Character, 7));

	/* Set E to low */
	MGPIO_u8SetPinValue(LCD_PORT, E_PIN, GPIO_LOW);

	/* Wait 2 ms */
	MSTK_vSetBusyWait(LCD_TICKS);
}

void HLCD_vWriteString(u8 *ptr, u32 StrSize)
{
	u8 i = 0;
	while(i < StrSize)
	{
		HLCD_vWriteChar(ptr[i]);
		i++;
	}
}

void HLCD_vCursor_Position (u8 Y,u8 X)
{
	if (X>0 && X<=16)
	{
	    switch(Y)
	    {
		    case 1:
		    	HLCD_vSendCmd(X+127);
		    break;
		    case 2:
		    	HLCD_vSendCmd(X+191);
		    break;
		    default:
		    break;
	    }
	}
}
