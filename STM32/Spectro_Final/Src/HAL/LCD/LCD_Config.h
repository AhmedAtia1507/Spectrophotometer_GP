/**
 * @file LCD_Config.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2024-01-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _LCD_CONFIG_H_
#define _LCD_CONFIG_H_

/*
    Options for Function Set command
    1) FUNCTION_SET_4BIT_MODE_1LINE_5BY8_SIZE  0x20
    2) FUNCTION_SET_4BIT_MODE_1LINE_5BY11_SIZE 0x24
    3) FUNCTION_SET_4BIT_MODE_2LINE_5BY8_SIZE  0x28
    4) FUNCTION_SET_4BIT_MODE_2LINE_5BY11_SIZE 0x2C
*/
#define FUNCTION_SET_COMMAND    FUNCTION_SET_4BIT_MODE_2LINE_5BY8_SIZE

/*
    Options for Display Set Command
    1) DISPLAY_OFF                             0x08
    2) DISPLAY_ON                              0x0C
    3) DISPLAY_ON_CURSOR_ON                    0x0E
    4) DISPLAY_ON_CURSOR_ON_BLINKING_ON        0x0F
*/
#define DISPLAY_SET_COMMAND     DISPLAY_ON_CURSOR_ON_BLINKING_ON

/*
    Options for Entry Mode Set Command
    1) ENTRY_MODE_INCREASE_NO_SHIFT            0x06
    2) ENTRY_MODE_INCREASE_WITH_SHIFT          0x07
    3) ENTRY_MODE_DECREASE_NO_SHIFT            0x04
    4) ENTRY_MODE_DECREASE_WITH_SHIFT          0x05
*/
#define ENTRY_MODE_SET_COMMAND  ENTRY_MODE_INCREASE_NO_SHIFT

#define LCD_RS_PORT_ID                      MGPIO_PORTB
#define LCD_RS_PIN_ID                       MGPIO_PIN0

#define LCD_RW_PORT_ID                      MGPIO_PORTB
#define LCD_RW_PIN_ID                       MGPIO_PIN1

#define LCD_E_PORT_ID                       MGPIO_PORTA
#define LCD_E_PIN_ID                        MGPIO_PIN3

#define LCD_INPUT_PORTS_ID                  MGPIO_PORTA
#define LCD_D4_PIN_ID                       MGPIO_PIN4
#define LCD_D5_PIN_ID                       MGPIO_PIN5
#define LCD_D6_PIN_ID                       MGPIO_PIN6
#define LCD_D7_PIN_ID                       MGPIO_PIN7

#endif /*_LCD_CONFIG_H_*/