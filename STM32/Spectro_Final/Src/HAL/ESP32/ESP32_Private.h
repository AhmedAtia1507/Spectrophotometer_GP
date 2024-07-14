/**
 * @file ESP32_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _ESP32_PRIVATE_H_
#define _ESP32_PRIVATE_H_

#define HESP32_UART1                        0
#define HESP32_UART2                        1
#define HESP32_UART3                        2

#define HESP32_COMMAND_FOUND                1
#define HESP32_COMMAND_NOT_FOUND            0

void HESP32_ParseReceivedCommand  (void);
#endif /*_ESP32_PRIVATE_H_*/