/**
 * @file Platform_Types.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: Header file to define datatypes used in all files according to AUTOSAR Standards 
 * @version 1.0
 * @date 2023-10-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _PLATFORM_TYPES_H_
#define _PLATFORM_TYPES_H_

typedef enum
{
    CPU_TYPE_8,
    CPU_TYPE_16,
    CPU_TYPE_32,
    CPU_TYPE_64
}CPU_TYPE_t;

#define CPU_TYPE                    CPU_TYPE_32

typedef enum
{
    MSB_FIRST,
    LSB_FIRST
}CPU_BIT_ORDER_t;

#define CPU_BIT_ORDER               LSB_FIRST

typedef enum
{
    HIGH_BYTE_FIRST,
    LOW_BYTE_FIRST
}CPU_BYTE_ORDER_t;

#define CPU_BYTE_ORDER              LOW_BYTE_FIRST

#ifndef TRUE
    #define TRUE                    (boolean)true
#endif
#ifndef FALSE
    #define FALSE                   (boolean)false
#endif

typedef unsigned char               boolean;

typedef unsigned char               uint8;
typedef unsigned short              uint16;
typedef unsigned long               uint32;
typedef unsigned long long          uint64;

typedef signed char                 sint8;
typedef signed short                sint16;
typedef signed long                 sint32;
typedef signed long long            sint64;

typedef unsigned char               uint8_least;
typedef unsigned short              uint16_least;
typedef unsigned long               uint32_least;

typedef signed char                 sint8_least;
typedef signed short                sint16_least;
typedef signed long                 sint32_least;

typedef float                       float32;
typedef double                      float64;

typedef void*                       VoidPtr;
typedef const void*                 ConstVoidPtr;

#endif /*_PLATFORM_TYPES_H_*/