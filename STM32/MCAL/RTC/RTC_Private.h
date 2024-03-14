/**
 * @file RTC_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _RTC_PRIVATE_H_
#define _RTC_PRIVATE_H_

/*
RTC Core and Clock Configuration "MRCC_BDCR" are in the backup domain
To enable access to backup registers and RTC:
    1) Enable the power and backup interface clocks by setting PWREN and BKPEN
        bits in RCC_APB1ENR
    2) Set the DBP bit in the Power Control Registe (PWR_CR)
*/
/*
RTC Registers Writing Sequence:
    1) Poll RTOFF Bit in RTC_CRL, wait until its value goes to '1'
    2) Set the CNF bit to enter configuration mode
    3) Write to one or more RTC Registers.
    4) Clear the CNF bit to exit configuration mode.
    5) Poll RTOFF, wait until its value goes to '1' to check the end of the write

Note: The write operation only executes when the CNF bit is cleared.
*/
#define RCC_BASE_ADDRESS                            0x40021000U
#define PWR_BASE_ADDRESS                            0x40007000U
#define BKP_BASE_ADDRESS                            0x40006C00U
#define RTC_BASE_ADDRESS                            0x40002800U

#define MRCC_APB1ENR_R                              (*(volatile uint32*)(RCC_BASE_ADDRESS + 0x1C))
#define MRCC_APB1ENR_PWREN_BIT                      28
#define MRCC_APB1ENR_BKPEN_BIT                      27

#define MRCC_BDCR_R                                 (*(volatile uint32*)(RCC_BASE_ADDRESS + 0x20))
/*
RTC Clock Source Selection:
    1) Set by software to select the clock source for RTC.
    2) Once the RTC Clock source has been selected, it cannot be changed anymore unless
        the backup domain is reset
    3) BDRST bit can be used to reset them
*/
#define MRCC_BDCR_RTCSEL_START_BIT                  8
#define MRCC_BDCR_RTCEN_BIT                         15
#define MRCC_BDCR_LSEON_BIT                         0
#define MRCC_BDCR_LSERDY_BIT                        1

#define MRTC_LSE_CLOCK                              1
#define MRTC_LSI_CLOCK                              2
#define MRTC_HSE_CLOCK_DIV_128                      3


#define MPWR_CR_R                                   (*(volatile uint32*)(PWR_BASE_ADDRESS + 0x00))
/*Disable Backup domain write protection*/
#define MPWR_CR_DBP_BIT                             8

typedef struct RTC_Registers
{
    /*RTC Control Register High*/
    volatile uint32 CRH;
    /*RTC Control Register Low*/
    volatile uint32 CRL;
    /*RTC Prescalar Load Register High "First 4 bits only"*/
    volatile uint32 PRLH;
    /*RTC Prescalar Load Register Low "First 16 bits only"*/
    volatile uint32 PRLL;
    /*RTC Prescalar Divider Register High "First 16 bits only"*/
    volatile uint32 DIVH;
    /*RTC Prescalar Divider Register Low "First 16 bits only"*/
    volatile uint32 DIVL;
    /*RTC Counter Register High "First 16 bits only"*/
    volatile uint32 CNTH;
    /*RTC Counter Register Low "First 16 bits only"*/
    volatile uint32 CNTL;
    /*RTC Alarm Register High "First 16 bits only"*/
    volatile uint32 ALRH;
    /*RTC Alarm Register Low "First 16 bits only"*/
    volatile uint32 ALRL;
}RTC_Typedef_t;

#define RTC                                         ((volatile RTC_Typedef_t*)(RTC_BASE_ADDRESS))
/*******************************RTC Control Register High "RTC_CRH" Bits**********************************/

/*Second Interrupt Enable*/
#define MRTC_CRH_SECIE_BIT                          0
/*Alarm Interrupt Enable*/
#define MRTC_CRH_ALRIE_BIT                          1
/*Overflow Interrupt Enable*/
#define MRTC_CRH_OWIE_BIT                           2

/*******************************RTC Control Register Low "RTC_CRL" Bits**********************************/

/*
Second Flag:
    1) Set by hardware when the 32-bit programmable prescalar overflows, thus
        incrementing the RTC Counter. Hence, the flag provides a periodic signal with
        a period corresponding to the resolution programmed for the RTC Counter "Usually One Second"
    2) An Interrupt is generated if SECIE = 1 in the RTC_CRH.
    3) It can be cleared only by software.
    4) Writing '1' has no effect
*/
#define MRTC_CRL_SECF_BIT                           0
/*
Alarm Flag:
    1) Set by hardware when the 32-bit programmable counter reaches the threshold set in the
        RTC_ALR register
    2) An interrupt is generated if ALRIE = 1 in the RTC_CRH register.
    3) Can be cleared only by software
    4) Writing '1' has no effect
*/
#define MRTC_CRL_ALRF_BIT                           1
/*
Overflow flag:
    1) Set by Hardware when the 32-bit programmable counter overflows.
    2) An Interrupt is generated if OWIE = 1 in the RTC_CRH register.
    3) Can be cleared only by software
    4) Writing '1' has no effect
*/
#define MRTC_CRL_OWF_BIT                            2
/*
Registers Synchronized Flag
    1) Set by hardware at each time RTC_CNT and RTC_DIV registers are updated
        and cleared by software.
    2) Before any read operation after an APB1 reset or an APB1 Clock Stop, this bit must be cleared
        by software and the user application must wait until it is set to be sure
        that the RTC_CNT, RTC_ALR or RTC_PRL registers are synchronized
*/
#define MRTC_CRL_RSF_BIT                            3
/*
Configuration Flag:
    1) Must be set by software to enter in configuration mode so as to allow new values
        to be written in the RTC_CNT, RTC_ALR or RTC_PRL registers
    2) The write operation is only executed when the CNF bit is reset by software after
        has been set
*/
#define MRTC_CRL_CNF_BIT                            4
/*
RTC Operation Off:
    1) With this bit, the RTC reports the status of the last write operation performed on
        its registers, indicating if it has been completed or not.
    0 ----> It is not possible to write to any of the RTC registersز
*/
#define MRTC_CRL_RTOFF_BIT                          5



/********************************************MRTC Interrupt Status**********************************/
#define MRTC_SECOND_INTERRUPT_ENABLED               0
#define MRTC_SECOND_INTERRUPT_DISABLED              1
#endif /*_RTC_PRIVATE_H_*/