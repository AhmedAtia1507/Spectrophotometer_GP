/**
 * @file STD_TYPES.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: C header file to define standard datatypes used in other files 
 * @version 1.0
 * @date 2023-08-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_

typedef unsigned char                   u8;
typedef signed char                     s8;

typedef unsigned short int              u16;
typedef signed short int                s16;

typedef unsigned long int               u32;
typedef signed long int                 s32;

typedef unsigned long long int          u64;
typedef signed long long int            s64;

typedef float                           f32;
typedef double                          f64;

#define NULL                            ((void*) 0)

typedef u8                              Std_ReturnType;

#define E_OK                            ((Std_ReturnType) 1)
#define E_NOT_OK                        ((Std_ReturnType) 0)

#endif /*_STD_TYPES_H_*/
