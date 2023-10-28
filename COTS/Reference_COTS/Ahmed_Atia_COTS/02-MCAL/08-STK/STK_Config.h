/**
 * @file STK_Config.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-09-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _STK_CONFIG_H_
#define _STK_CONFIG_H_

/*
    Options for SysTick Timer Clock Source:
    1) AHB Clock divided by 8: STK_CLOCK_SOURCE_AHB_DIV_8
    2) AHB Clock: STK_CLOCK_SOURCE_AHB
*/
#define STK_CLOCK_SOURCE                                STK_CLOCK_SOURCE_AHB

/*
    Options for SysTick Interrupt Status:
    1) SysTick interrupt enabled "When timer counts down to 0": STK_INTERRUPT_ENABLED
    2) SysTick Interrupt disabled:STK_INTERRUPT_DISABLED
*/
#define STK_INTERRUPT_STATUS                            STK_INTERRUPT_ENABLED

#define STK_AHB_CLOCK_FREQUENCY                         8000000
#endif /*_STK_CONFIG_H_*/
