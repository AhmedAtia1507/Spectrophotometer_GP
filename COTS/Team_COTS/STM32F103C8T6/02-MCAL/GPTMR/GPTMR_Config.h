/**
 * @file GPTMR_Config.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2024-02-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _GPTMR_CONFIG_H_
#define _GPTMR_CONFIG_H_

#define MGPTMR_CLK_FREQ                                             8000000
/*
Options for Update Event Status:
1) Enabled:                                                         MGPTMR_UEV_ENABLED
2) Disabled:                                                        MGPTMR_UEV_DISABLED
*/
#define MGPTMR_UEV_STATUS                                           MGPTMR_UEV_ENABLED

#if MGPTMR_UEV_STATUS == MGPTMR_UEV_ENABLED
    /*
    Options for Update Event Source:
    1)  1. Counter Overflow/Underflow
        2. Setting the UG bit
        3. Update generation through the slave mode controller      MGPTMR_UEV_SOURCE_ALL
    2) Counter Overflow/Underflow Only                              MGPTMR_UEV_SOURCE_OVERFLOW_UNDERFLOW
    */
    #define MGPTMR_UEV_SOURCE                                       MGPTMR_UEV_SOURCE_ALL
#endif /*MGPTMR_UEV_STATUS*/

/*
Options for One Pulse Mode Status:
1) Enabled:                                                         MGPTMR_ONE_PULSE_MODE_ENABLED
2) Disabled:                                                        MGPTMR_ONE_PULSE_MODE_DISABLED
*/
#define MGPTMR_ONE_PULSE_MODE_STATUS                                MGPTMR_ONE_PULSE_MODE_DISABLED


/*
Options for Counter Allignment:
1) Edge-Alligned Mode:                                              MGPTMR_EDGE_ALLIGNED_MODE
2) Center-Alligned Mode 1:                                          MGPTMR_CENTER_ALLIGNED_MODE_1
3) Center-Alligned Mode 2:                                          MGPTMR_CENTER_ALLIGNED_MODE_2
4) Center-Alligned Mode 3:                                          MGPTMR_CENTER_ALLIGNED_MODE_3
*/
#define MGPTMR_COUNTER_ALLIGNMENT                                   MGPTMR_EDGE_ALLIGNED_MODE

#if MGPTMR_COUNTER_ALLIGNMENT == MGPTMR_EDGE_ALLIGNED_MODE
    /*
    Options for counter direction:
    1) upcounter:                                                   MGPTMR_COUNTER_UPCOUNTER
    2) downcounter:                                                 MGPTMR_COUNTER_DOWNCOUNTER
    */
    #define MGPTMR_COUNTER_DIRECTION                                MGPTMR_COUNTER_UPCOUNTER
#endif /*MGPTMR_COUNTER_ALLIGNMENT*/

/*
Options for Auto-Reload Preload Values:
1) Enabled:                                                         MGPTMR_AUTO_RELOAD_ENABLED
2) Disabled:                                                        MGPTMR_AUTO_RELOAD_DISABLED
*/
#define MGPTMR_AUTO_RELOAD_STATUS                                   MGPTMR_AUTO_RELOAD_ENABLED

/*
Timer Clock Prescalar:
    Can have any value between 1 and 65536
*/
#define MGPTMR_CLK_PRESCALER                                        1000

/*
Options for Update Interrupt Status:
1) Enabled:                                                         MGPTMR_UPDATE_INTERRUPT_ENABLED
2) Disabled:                                                        MGPTMR_UPDATE_INTERRUPT_DISABLED
*/
#define MGPTMR_UPDATE_INTERRUPT_STATUS                              MGPTMR_UPDATE_INTERRUPT_ENABLED
#endif /*_GPTMR_CONFIG_H_*/