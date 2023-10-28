/**
 * @file AFIO_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-09-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _AFIO_PRIVATE_H_
#define _AFIO_PRIVATE_H_

typedef struct AFIO_Registers
{
    /*Event Control Register*/
    volatile u32 EVCR;
    /*Alternate function remap and debug I/O Configuration
        Register*/
    volatile u32 MAPR;
    /*External Interrupt Configuration Register*/
    volatile u32 EXTICR[4];
    /*AF Remap and Debug I/O Configuration Register 2*/
    volatile u32 MAPR2;
}AFIO_Typedef;

#define AFIO_BASE_ADDRESS                           0x40010000U

#define AFIO                                        ((AFIO_Typedef *)(AFIO_BASE_ADDRESS))
#endif /*_AFIO_PRIVATE_H_*/