/**
 * @file LCD_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2024-01-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _LCD_INTERFACE_H_
#define _LCD_INTERFACE_H_

#define LCD_FIRST_ROW           0
#define LCD_SECOND_ROW          1


/**
 * @brief: Function to initialize the LCD
 * 
 */
Std_ReturnType LCD_Init(void);
/**
 * @brief: Function to write a command in the LCD
 * 
 * @param Copy_uint8Command: The command to be written
 */
Std_ReturnType LCD_WriteCommand4Bit(uint8 Copy_uint8Command);
/**
 * @brief: Function to display a character in the LCD
 * 
 * @param Copy_uint8Char: The character to be displayed
 */
Std_ReturnType LCD_WriteChar4Bit(uint8 Copy_uint8Char);
/**
 * @brief: Function to change the LCD cursor's position
 * 
 * @param Copy_uint8RowID: The ID of the row in which the cursor will be in (first row or second row) 
 * @param Copy_uint8ColumnID: The ID of the column in which the cursor will be in
 */
Std_ReturnType LCD_SetCursorPosition(uint8 Copy_uint8RowID, uint8 Copy_uint8ColumnID);
/**
 * @brief: Function to Display a string in the LCD
 * 
 * @param P_uint8String: The String to be displayed
 */
Std_ReturnType LCD_WriteString(uint8* P_uint8String);
/**
 * @brief: Function to display an integer in the LCD
 * 
 * @param Copy_uint32Value: The integer value to be displayed
 */
Std_ReturnType LCD_WriteIntegerValue(uint32 Copy_uint32Value);
/**
 * @brief: Function to toggle the enable pin of the LCD for a short amount of time
 * 
 */
Std_ReturnType LCD_Peek(void);
/**
 * @brief: Function to clear the LCD display
 * 
 */
Std_ReturnType LCD_ClearDisplay(void);

#endif /*_LCD_INTERFACE_H_*/