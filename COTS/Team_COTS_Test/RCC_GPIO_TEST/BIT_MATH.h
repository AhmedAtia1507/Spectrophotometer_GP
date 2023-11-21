/**
 * @file BIT_MATH.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: C header file to define function-like macros used to do bitwise operations on registers
 * @version 1.0
 * @date 2023-08-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _BIT_MATH_H_
#define _BIT_MATH_H_

#define SET_BIT(REG,BIT)                        (REG |= (1 << BIT))
#define CLR_BIT(REG,BIT)                        (REG &= ~(1 << BIT))
#define TOGGLE_BIT(REG,BIT)                     (REG ^= (1 << BIT))
#define GET_BIT(REG,BIT)                        ((REG >> BIT) & 1)

#endif /*_BIT_MATH_H_*/
