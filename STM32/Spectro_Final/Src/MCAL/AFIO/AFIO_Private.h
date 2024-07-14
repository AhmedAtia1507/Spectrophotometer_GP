/**
 * @file AFIO_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 *  
 * @version 1.0
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _AFIO_PRIVATE_H_
#define _AFIO_PRIVATE_H_

typedef struct AFIO_Registers
{
    /*Event Control Register*/
    volatile uint32 EVCR;
    /*Alternate function remap and debug I/O Configuration
        Register*/
    volatile uint32 MAPR;
    /*External Interrupt Configuration Register*/
    volatile uint32 EXTICR[4];
    /*AF Remap and Debug I/O Configuration Register 2*/
    volatile uint32 MAPR2;
}MAFIO_Typedef;

#define MAFIO_BASE_ADDRESS                           0x40010000U

#define MAFIO                                        ((MAFIO_Typedef *)(MAFIO_BASE_ADDRESS))
#endif /*_AFIO_PRIVATE_H_*/