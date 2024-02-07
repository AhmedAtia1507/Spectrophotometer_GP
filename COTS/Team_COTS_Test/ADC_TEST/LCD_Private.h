/**
 * @file LCD_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2024-01-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _LCD_PRIVATE_H_
#define _LCD_PRIVATE_H_

#define MODE_4_BIT                              0x02

/*Options for function set command*/
#define FUNCTION_SET_4BIT_MODE_1LINE_5BY8_SIZE  0x20
#define FUNCTION_SET_4BIT_MODE_1LINE_5BY11_SIZE 0x24
#define FUNCTION_SET_4BIT_MODE_2LINE_5BY8_SIZE  0x28
#define FUNCTION_SET_4BIT_MODE_2LINE_5BY11_SIZE 0x2C

/*Options for Display Command*/
#define DISPLAY_OFF                             0x08
#define DISPLAY_ON                              0x0C
#define DISPLAY_ON_CURSOR_ON                    0x0E
#define DISPLAY_ON_CURSOR_ON_BLINKING_ON        0x0F

/*Options for Entry Mode*/
#define ENTRY_MODE_INCREASE_NO_SHIFT            0x06
#define ENTRY_MODE_INCREASE_WITH_SHIFT          0x07
#define ENTRY_MODE_DECREASE_NO_SHIFT            0x04
#define ENTRY_MODE_DECREASE_WITH_SHIFT          0x05

/*LCD Commands*/
#define CLEAR_DISPLAY                           0x01
#define SHIFT_CURSOR_LEFT                       0x10
#define SHIFT_CURSOR_RIGHT                      0x14
#define FIRST_LINE_OFFSET                       0x80
#define SECOND_LINE_OFFSET                      0xC0

#endif /*_LCD_PRIVATE_H_*/