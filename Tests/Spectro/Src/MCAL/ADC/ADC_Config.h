/**
 * @file ADC_Config.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _ADC_CONFIG_H_
#define _ADC_CONFIG_H_

/*
Modes of Operation for ADC:

1) Independent mode:                                                            MADC_INDEPENDENT_MODE
2) Combined regular simultaneous + injected simultaneous mode                   MADC_COMBINED_REG_SIMUL_INJ_SIMUL
3) Combined regular simultaneous + alternate trigger mode                       MADC_COMBINED_REG_SIMUL_ALTERNATE_TRIG
4) Combined injected simultaneous + fast interleaved mode                       MADC_COMBINED_INJ_SIMUL_FAST_INTERLEAVED
5) Combined injected simultaneous + slow Interleaved mode                       MADC_COMBINED_INJ_SIMUL_SLOW_INTERLEAVED
6) Injected simultaneous mode only                                              MADC_INJ_SIMUL_MODE_ONLY
7) Regular simultaneous mode only                                               MADC_REG_SIMUL_MODE_ONLY
8) Fast interleaved mode only                                                   MADC_FAST_INTERLEAVED_ONLY
9) Slow interleaved mode only                                                   MADC_SLOW_INTERLEAVED_ONLY
10) Alternate trigger mode only                                                 MADC_ALTERNATE_TRIG_ONLY
*/
#define MADC_OPERATION_MODE                                                     MADC_INDEPENDENT_MODE

/*
Sample Time for each channel in ADC:
1) 1.5 Cycles:                                                                  MADC_SAMPLE_TIME_1_H_CYCLE
2) 7.5 Cycles:                                                                  MADC_SAMPLE_TIME_7_H_CYCLE
3) 13.5 Cycles:                                                                 MADC_SAMPLE_TIME_13_H_CYCLE
4) 28.5 Cycles:                                                                 MADC_SAMPLE_TIME_28_H_CYCLE
5) 41.5 Cycles:                                                                 MADC_SAMPLE_TIME_41_H_CYCLE
6) 55.5 Cycles:                                                                 MADC_SAMPLE_TIME_55_H_CYCLE
7) 71.5 Cycles:                                                                 MADC_SAMPLE_TIME_71_H_CYCLE
8) 239.5 Cycles:                                                                MADC_SAMPLE_TIME_239_H_CYCLE
*/
#define MADC_CHANNEL_SAMPLE_TIME                                                MADC_SAMPLE_TIME_1_H_CYCLE

/*
External Trigger Enable for ADC:
1) Enabled:                                                                     MADC_EXTERNAL_TRIGGER_ENABLED
2) Disabled:                                                                    MADC_EXTERNAL_TRIGGER_DISABLED
*/
#define MADC_EXTERNAL_TRIGGER_STATUS                                            MADC_EXTERNAL_TRIGGER_ENABLED

#if MADC_EXTERNAL_TRIGGER_STATUS == MADC_EXTERNAL_TRIGGER_ENABLED
    /*
    External Trigger for regular start of conversion:
    1) Timer 1 CC1 event                                                        MADC_TRIGGER_TIMER1_CC1_EVENT
    2) Timer 1 CC2 event                                                        MADC_TRIGGER_TIMER1_CC2_EVENT
    3) Timer 1 CC3 event                                                        MADC_TRIGGER_TIMER1_CC3_EVENT
    4) Timer 2 CC2 event                                                        MADC_TRIGGER_TIMER2_CC2_EVENT
    5) Timer 3 TRGO event                                                       MADC_TRIGGER_TIMER3_TRGO_EVENT
    6) Timer 4 CC4 event                                                        MADC_TRIGGER_TIMER4_CC4_EVENT
    7) EXTI line 11                                                             MADC_TRIGGER_EXTI_LINE_11_EVENT
    8) SWSTART                                                                  MADC_TRIGGER_SWSTART
    */ 
    #define MADC_EXTERNAL_TRIGGER_SELECT                                        MADC_TRIGGER_SWSTART
#endif /*MADC_EXTERNAL_TRIGGER_STATUS*/

/*
Data Bits Adjust
1) Right-Adjust:                                                                MADC_RIGHT_ADJUST_DATA_BITS
2) Left-Adjust:                                                                 MADC_LEFT_ADJUST_DATA_BITS
*/
#define MADC_DATA_BITS_ADJUST_SELECT                                            MADC_RIGHT_ADJUST_DATA_BITS

/*
Interrupt Status for End of Conversion:
1) Enabled                                                                      MADC_EOC_INTERRUPT_ENABLED
2) Disabled                                                                     MADC_EOC_INTERRUPT_DISABLED
*/
#define MADC_EOC_INTERRUPT_STATUS                                               MADC_EOC_INTERRUPT_DISABLED
#endif /*_ADC_CONFIG_H_*/