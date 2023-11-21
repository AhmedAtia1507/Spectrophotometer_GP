/**
 * @file Std_Types.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: Header file to 
 * @version 1.0
 * @date 2023-10-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_

#include "Platform_Types.h"

#define E_OK                        0x00u
#define E_NOT_OK                    0x01u

typedef uint8                       Std_ReturnType;

#define STD_HIGH                    0x01u
#define STD_LOW                     0x00u

#define STD_ACTIVE                  0x01u
#define STD_IDLE                    0x00u

#define STD_ON                      0x01u
#define STD_OFF                     0x00u

#define NULL_PTR                    ((VoidPtr) 0)
#endif /*_STD_TYPES_H_*/