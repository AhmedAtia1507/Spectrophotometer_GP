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

#define RCC_MAX_CLOCK_FREQ                  72000000
/*
    Options for Clock Sources:
    1) High Speed External Clock: RCC_HSE_CLOCK
    2) High Speed Internal Clock: RCC_HSI_CLOCK
    3) Phase-locked loop clock: RCC_PLL_CLOCK
*/
#define RCC_CLOCK_SOURCE                    RCC_PLL_CLOCK

#if RCC_CLOCK_SOURCE == RCC_HSE_CLOCK
    /*
        Options for HSE Clock Source:
        1) Crystal Oscillator: RCC_HSE_CRYSTAL_CLOCK "4 --> 16 MHz"
        2) RC Circuit Oscillator: RCC_HSE_RC_CLOCK "4 --> 25MHz"
    */
    #define RCC_HSE_CLOCK_SOURCE            RCC_HSE_CRYSTAL_CLOCK

    #define RCC_HSE_CLOCK_FREQ              8000000
#elif RCC_CLOCK_SOURCE == RCC_PLL_CLOCK
    /*
        Options for PLL Input Clock:
        1) High-Speed Internal Clock Divided by 2: RCC_HSI_CLOCK_DIV_2
        2) High-Speed External Clock Divided by 2: RCC_HSE_CLOCK_DIV_2
        3) High-Speed External Clock: RCC_HSE_CLOCK
    */
    #define RCC_PLL_CLOCK_INPUT             RCC_HSE_CLOCK_DIV_2

    #if (RCC_PLL_CLOCK_INPUT == RCC_HSE_CLOCK_DIV_2) || (RCC_PLL_CLOCK_INPUT == RCC_HSE_CLOCK)
        #define RCC_PLL_HSE_CLOCK_FREQ              8000000
    #endif /*RCC_PLL_CLOCK_INPUT*/
    /*
        Options for PLL Multiplier:
        Any integer number between 2 to 16
        "PLL multiplies the input frequency by the number of your choice"
    */
    #define RCC_PLL_MULTIPLIER              16             
#endif /*RCC_CLOCK_SOURCE*/

/*
    Options for Advanced High Performance Bus Clock Prescalar
    1) RCC_AHB_CLK_DIV_1  
    2) RCC_AHB_CLK_DIV_2  
    3) RCC_AHB_CLK_DIV_4  
    4) RCC_AHB_CLK_DIV_8  
    5) RCC_AHB_CLK_DIV_16 
    6) RCC_AHB_CLK_DIV_64 
    7) RCC_AHB_CLK_DIV_128
    8) RCC_AHB_CLK_DIV_256
    9) RCC_AHB_CLK_DIV_512
*/
#define RCC_AHB_PRESCALAR                   RCC_AHB_CLK_DIV_1

/*
    Options for Advanced Peripheral Bus 1 Clock Prescalar
    1) RCC_APB1_CLK_DIV_1 
    2) RCC_APB1_CLK_DIV_2 
    3) RCC_APB1_CLK_DIV_4 
    4) RCC_APB1_CLK_DIV_8 
    5) RCC_APB1_CLK_DIV_16
*/
#define RCC_APB1_PRESCALAR                  RCC_APB1_CLK_DIV_1

/*
    Options for Advanced Peripheral Bus 2 Clock Prescalar
    1) RCC_APB2_CLK_DIV_1 
    2) RCC_APB2_CLK_DIV_2 
    3) RCC_APB2_CLK_DIV_4 
    4) RCC_APB2_CLK_DIV_8 
    5) RCC_APB2_CLK_DIV_16
*/
#define RCC_APB2_PRESCALAR                  RCC_APB2_CLK_DIV_1

#endif /*_RCC_CONFIG_H_*/