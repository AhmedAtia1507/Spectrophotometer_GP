/*
 * LCD_int.h
 *
 *  Created on: Sep 7, 2023
 *      Author: Mohanad
 */

#ifndef HAL_LCD_LCD_INT_H_
#define HAL_LCD_LCD_INT_H_

#include "../../LIB/STD_TYPES.h"

#define LCD_CLEAR          		0x01        /* replace all characters with ASCII 'space'                       */
#define LCD_HOME           		0x02        /* return cursor to first position on first line                   */
#define LCD_ENTRY_MODE      	0x06        // shift cursor from left to right on read/write
#define LCD_DISPLAY_OFF     	0x08        // turn display off
#define LCD_DISPLAY_ON      	0x0C        // display on, cursor off, don't blink character
#define LCD_FUNCTION_RESET  	0x30        // reset the LCD
#define LCD_SET_8BIT 			0x38        // 8-bit data, 2-line display, 5 x 7 font
#define LCD_SET_CURSOR      	0x80        // set cursor position
#define LCD_CURSOR_ON			0x0F		// LCD ON, cursor ON
#define LCD_DEC_CURSOR			0x04		// Decrement cursor (shift cursor to left)
#define LCD_INC_CURSOR			0x06		// Increment cursor (shift cursor to right)
#define LCD_CURSOR_BLINK		0x0E		// Display ON, cursor blinking
#define LCD_CURSOR_FIRST_LINE	0x80		// Force cursor to beginning of first line
#define LCD_CURSOR_SECOND_LINE	0xC0		// Force cursor to beginning of second line

void HLCD_vInit();
void HLCD_vSendCmd(u8 COMMAND);
void HLCD_vWriteChar(u8 Character);
void HLCD_vWriteString(u8 *ptr, u32 StrSize);
void HLCD_vCursor_Position (u8 Y,u8 X);

#endif /* HAL_LCD_LCD_INT_H_ */
