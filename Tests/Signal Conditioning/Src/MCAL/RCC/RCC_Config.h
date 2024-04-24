/**
 * @file RCC_Config.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: C header file to define pre-build configurations for RCC Peripheral
 * @version 1.0
 * @date 2023-08-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _RCC_CONFIG_H_
#define _RCC_CONFIG_H_

#define MRCC_MAX_CLOCK_FREQ                         72000000
/*
    Options for Clock Sources:
    1) High Speed External Clock:   MRCC_HSE_CLOCK
    2) High Speed Internal Clock:   MRCC_HSI_CLOCK
    3) Phase-locked loop clock:     MRCC_PLL_CLOCK
*/
#define MRCC_CLOCK_SOURCE                           MRCC_HSE_CLOCK

#if MRCC_CLOCK_SOURCE == MRCC_HSE_CLOCK
    /*
        Options for HSE Clock Source:
        1) Crystal Oscillator:      MRCC_HSE_CRYSTAL_CLOCK "4 --> 16 MHz"
        2) RC Circuit Oscillator:   MRCC_HSE_RC_CLOCK "4 --> 25MHz"
    */
    #define MRCC_HSE_CLOCK_SOURCE                   MRCC_HSE_CRYSTAL_CLOCK

    #define MRCC_HSE_CLOCK_FREQ                     8000000
#elif MRCC_CLOCK_SOURCE == MRCC_PLL_CLOCK
    /*
        Options for PLL Input Clock:
        1) High-Speed Internal Clock Divided by 2: MRCC_HSI_CLOCK_DIV_2
        2) High-Speed External Clock Divided by 2: MRCC_HSE_CLOCK_DIV_2
        3) High-Speed External Clock:              MRCC_HSE_CLOCK
    */
    #define MRCC_PLL_CLOCK_INPUT                    MRCC_HSE_CLOCK_DIV_2

    #if (MRCC_PLL_CLOCK_INPUT == MRCC_HSE_CLOCK_DIV_2) || (MRCC_PLL_CLOCK_INPUT == MRCC_HSE_CLOCK)
        #define RCC_PLL_HSE_CLOCK_FREQ              8000000
    #endif /*MRCC_PLL_CLOCK_INPUT*/
    /*
        Options for PLL Multiplier:
        Any integer number between 2 to 16
        "PLL multiplies the input frequency by the number of your choice"
    */
    #define RCC_PLL_MULTIPLIER                      16             
#endif /*MRCC_CLOCK_SOURCE*/

/*
    Options for Advanced High Performance Bus Clock Prescalar
    1) MRCC_AHB_CLK_DIV_1  
    2) MRCC_AHB_CLK_DIV_2  
    3) MRCC_AHB_CLK_DIV_4  
    4) MRCC_AHB_CLK_DIV_8  
    5) MRCC_AHB_CLK_DIV_16 
    6) MRCC_AHB_CLK_DIV_64 
    7) MRCC_AHB_CLK_DIV_128
    8) MRCC_AHB_CLK_DIV_256
    9) MRCC_AHB_CLK_DIV_512
*/
#define MRCC_AHB_PRESCALAR                          MRCC_AHB_CLK_DIV_1

/*
    Options for Advanced Peripheral Bus 1 Clock Prescalar
    1) MRCC_APB1_CLK_DIV_1 
    2) MRCC_APB1_CLK_DIV_2 
    3) MRCC_APB1_CLK_DIV_4 
    4) MRCC_APB1_CLK_DIV_8 
    5) MRCC_APB1_CLK_DIV_16
*/
#define MRCC_APB1_PRESCALAR                         MRCC_APB1_CLK_DIV_1

/*
    Options for Advanced Peripheral Bus 2 Clock Prescalar
    1) MRCC_APB2_CLK_DIV_1 
    2) MRCC_APB2_CLK_DIV_2 
    3) MRCC_APB2_CLK_DIV_4 
    4) MRCC_APB2_CLK_DIV_8 
    5) MRCC_APB2_CLK_DIV_16
*/
#define MRCC_APB2_PRESCALAR                         MRCC_APB2_CLK_DIV_1

#endif /*_RCC_CONFIG_H_*/