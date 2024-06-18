/**
 * @file LCD_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2024-01-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/Std_Types.h"

#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/STK/STK_Interface.h"

#include "LCD_Private.h"
#include "LCD_Interface.h"
#include "LCD_Config.h"

/**
 * @brief: Function to initialize the LCD
 * 
 */
Std_ReturnType LCD_Init(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    MGPIO_SetPinMode(LCD_RS_PORT_ID, LCD_RS_PIN_ID, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    MGPIO_SetPinMode(LCD_RW_PORT_ID, LCD_RW_PIN_ID, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    MGPIO_SetPinMode(LCD_E_PORT_ID, LCD_E_PIN_ID, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    MGPIO_SetPinMode(LCD_INPUT_PORTS_ID, LCD_D4_PIN_ID, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    MGPIO_SetPinMode(LCD_INPUT_PORTS_ID, LCD_D5_PIN_ID, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    MGPIO_SetPinMode(LCD_INPUT_PORTS_ID, LCD_D6_PIN_ID, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    MGPIO_SetPinMode(LCD_INPUT_PORTS_ID, LCD_D7_PIN_ID, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    MSTK_uint8Delay(35);

    LCD_WriteCommand4Bit(MODE_4_BIT);
    MSTK_uint8Delay(5);
    
    LCD_WriteCommand4Bit(FUNCTION_SET_COMMAND);
    MSTK_uint8Delay(5);

    LCD_WriteCommand4Bit(DISPLAY_SET_COMMAND);
    MSTK_uint8Delay(5);

    LCD_ClearDisplay();
    MSTK_uint8Delay(5);

    LCD_WriteCommand4Bit(FIRST_LINE_OFFSET);
    MSTK_uint8Delay(30);

    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to write a command in the LCD
 * 
 * @param Copy_uint8Command: The command to be written
 */
Std_ReturnType LCD_WriteCommand4Bit(uint8 Copy_uint8Command)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    MGPIO_SetPinValue(LCD_RS_PORT_ID, LCD_RS_PIN_ID, MGPIO_LOW);
    MGPIO_SetPinValue(LCD_RW_PORT_ID, LCD_RW_PIN_ID, MGPIO_LOW);
    MSTK_uint8Delay(5);

    MGPIO_SetNibbleValue(LCD_INPUT_PORTS_ID, LCD_D4_PIN_ID, LCD_D7_PIN_ID, (uint16)(Copy_uint8Command >> 4));
    MSTK_uint8Delay(5);
    LCD_Peek();
    MSTK_uint8Delay(5);

    MGPIO_SetNibbleValue(LCD_INPUT_PORTS_ID, LCD_D4_PIN_ID, LCD_D7_PIN_ID, (uint16)(Copy_uint8Command & 0x0F));
    MSTK_uint8Delay(5);
    LCD_Peek();
    MSTK_uint8Delay(5);

    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to display a character in the LCD
 * 
 * @param Copy_uint8Char: The character to be displayed
 */
Std_ReturnType LCD_WriteChar4Bit(uint8 Copy_uint8Char)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    MGPIO_SetPinValue(LCD_RS_PORT_ID, LCD_RS_PIN_ID, MGPIO_HIGH);
    MGPIO_SetPinValue(LCD_RW_PORT_ID, LCD_RW_PIN_ID, MGPIO_LOW);
    MSTK_uint8Delay(5);

    MGPIO_SetNibbleValue(LCD_INPUT_PORTS_ID, LCD_D4_PIN_ID, LCD_D7_PIN_ID, (uint16)(Copy_uint8Char >> 4));
    MSTK_uint8Delay(5);
    LCD_Peek();
    MSTK_uint8Delay(5);

    MGPIO_SetNibbleValue(LCD_INPUT_PORTS_ID, LCD_D4_PIN_ID, LCD_D7_PIN_ID, (uint16)(Copy_uint8Char & 0x0F));
    MSTK_uint8Delay(5);
    LCD_Peek();
    MSTK_uint8Delay(5);

    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to change the LCD cursor's position
 * 
 * @param Copy_uint8RowID: The ID of the row in which the cursor will be in (first row or second row) 
 * @param Copy_uint8ColumnID: The ID of the column in which the cursor will be in
 */
Std_ReturnType LCD_SetCursorPosition(uint8 Copy_uint8RowID, uint8 Copy_uint8ColumnID)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    if(Copy_uint8RowID == LCD_FIRST_ROW || Copy_uint8RowID == LCD_SECOND_ROW)
    {
        if(Copy_uint8ColumnID >= 0 && Copy_uint8ColumnID <= 15)
        {
            uint8 Loc_uint8CursorPos = 0;
            switch (Copy_uint8RowID)
            {
                case LCD_FIRST_ROW:
                {
                    Loc_uint8CursorPos = FIRST_LINE_OFFSET;
                    Loc_uint8CursorPos += Copy_uint8ColumnID;
                    LCD_WriteCommand4Bit(Loc_uint8CursorPos);
                    
                    Loc_uint8FuncStatus = E_OK;
                    break;
                }
                case LCD_SECOND_ROW:
                {
                    Loc_uint8CursorPos = SECOND_LINE_OFFSET;
                    Loc_uint8CursorPos += Copy_uint8ColumnID;
                    LCD_WriteCommand4Bit(Loc_uint8CursorPos);
                    
                    Loc_uint8FuncStatus = E_OK;
                    break;
                }
                default:
                {
                    Loc_uint8FuncStatus = E_NOT_OK;
                    break;
                }
            }
            
        }
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }

    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to Display a string in the LCD
 * 
 * @param P_uint8String: The String to be displayed
 */
Std_ReturnType LCD_WriteString(uint8* P_uint8String)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    if(P_uint8String != NULL_PTR)
    {
        uint8 Loc_uint8Index = 0;
        while(P_uint8String[Loc_uint8Index] != '\0')
        {
            LCD_WriteChar4Bit(P_uint8String[Loc_uint8Index]);
            Loc_uint8Index++;
        }
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }

    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to display an integer in the LCD
 * 
 * @param Copy_uint32Value: The integer value to be displayed
 */
Std_ReturnType LCD_WriteIntegerValue(uint32 Copy_uint32Value)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    if(Copy_uint32Value == 0)
    {
        LCD_WriteChar4Bit((Copy_uint32Value + 48));
    }
    else
    {
        uint32 Loc_uint8TempValue = Copy_uint32Value;
        uint8 Loc_uint8CharArray[20] = {0},Loc_uint8Count = 0, Loc_uint8Index = 0;
        while(Loc_uint8TempValue != 0)
        {
            Loc_uint8CharArray[Loc_uint8Count] = ((Loc_uint8TempValue % 10) + 48);
            Loc_uint8TempValue /= 10;
            Loc_uint8Count++;
        }
        
        for(Loc_uint8Index = 0; Loc_uint8Index < Loc_uint8Count; Loc_uint8Index++)
        {
            LCD_WriteChar4Bit(Loc_uint8CharArray[Loc_uint8Count - Loc_uint8Index - 1]);
        }
    }

    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to toggle the enable pin of the LCD for a short amount of time
 * 
 */
Std_ReturnType LCD_Peek(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    MGPIO_SetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, MGPIO_HIGH);
    MSTK_uint8Delay(2);
    MGPIO_SetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, MGPIO_LOW);
    
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to clear the LCD display
 * 
 */
Std_ReturnType LCD_ClearDisplay(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    LCD_WriteCommand4Bit(CLEAR_DISPLAY);

    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}