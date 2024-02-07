/**
 * @file RTC_Config.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _RTC_CONFIG_H_
#define _RTC_CONFIG_H_

/*
RTC Clock Source Selection:
1) LSE Clock:                               MRTC_LSE_CLOCK
2) LSI Clock:                               MRTC_LSI_CLOCK
3) HSE Clock divided by 128                 MRTC_HSE_CLOCK_DIV_128
*/
#define MRTC_CLOCK_SOURCE                   MRTC_LSE_CLOCK
/*
RTC Second Interrupt Status:
1) Disabled:                                MRTC_SECOND_INTERRUPT_DISABLED
2) Enabled:                                 MRTC_SECOND_INTERRUPT_ENABLED
*/
#define MRTC_SECOND_INTERRUPT_STATUS        MRTC_SECOND_INTERRUPT_ENABLED
#endif /*_RTC_CONFIG_H_*/