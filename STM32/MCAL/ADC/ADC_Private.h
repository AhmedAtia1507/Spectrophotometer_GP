/**
 * @file ADC_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _ADC_PRIVATE_H_
#define _ADC_PRIVATE_H_

#define MADC1_BASE_ADDRESS                              0x40012400U
#define MADC2_BASE_ADDRESS                              0x40012800U

typedef struct MADC_Registers
{
    /*ADC Status Register*/
    volatile uint32 SR;
    
    /*ADC Control Register 1*/
    volatile uint32 CR1;
    
    /*ADC Control Register 2*/
    volatile uint32 CR2;
    
    /*ADC Sample Time Register 1*/
    volatile uint32 SMPR1;
    
    /*ADC Sample Time Register 2*/
    volatile uint32 SMPR2;

    /*ADC Injected Channel Data Offset Register*/
    volatile uint32 JOFR1;
    volatile uint32 JOFR2;
    volatile uint32 JOFR3;
    volatile uint32 JOFR4;

    /*ADC Watchdog High Threshold Register*/
    volatile uint32 HTR;

    /*ADC Watchdog Low Threshold Register*/
    volatile uint32 LTR;

    /*ADC Regular Sequence Register 1*/
    volatile uint32 SQR1;

    /*ADC Regular Sequence Register 2*/
    volatile uint32 SQR2;

    /*ADC Regular Sequence Register 3*/
    volatile uint32 SQR3;

    /*ADC Injected Sequence Register*/
    volatile uint32 JSQR;

    /*ADC Injected Data Register*/
    volatile uint32 JDR1;
    volatile uint32 JDR2;
    volatile uint32 JDR3;
    volatile uint32 JDR4;

    /*ADC Regular Data Register*/
    volatile uint32 DR;

} MADC_Typedef_t;

#define ADC1                                        ((volatile MADC_Typedef_t*)(MADC1_BASE_ADDRESS))
#define ADC2                                        ((volatile MADC_Typedef_t*)(MADC2_BASE_ADDRESS))

/*********************************ADC Status Register (ADC_SR) bits***********************************/

/*
Analog Watchdog Flag:
1) Set by hardware when the converted voltage crosses the values programmed in ADC_LTR 
        and ADC_HTR registers.
2) Cleared by Software
*/
#define MADC_SR_AWD_BIT                             0
/*
End of Conversion:
1) Set by hardware at the end of a group channel conversion (regular or injected).
2) Cleared by Software or by reading the ADC_DR "Data register".
*/
#define MADC_SR_EOC_BIT                             1
/*
Injected Channel end of conversion:
1) Set by hardware at the end of all injected group channel conversion.
2) Cleared by Software.
*/
#define MADC_SR_JEOC_BIT                            2
/*
Injected Channel Start Flag:
1) Set by hardware when injected channel group conversion starts.
2) Cleared by Software.
*/
#define MADC_SR_JSTRT_BIT                           3
/*
Regular Channel Start Flag:
1) Set by hardware when regular channel conversion starts.
2) Cleared by Software.
*/
#define MADC_SR_STRT_BIT                            4

/******************************ADC Control Register 1 (ADC_CR1) Bits**************************/

/*
Analog Watchdog channel select bits (5 bits):
1) Set and cleared by software.
2) They select the input channel to be guarded by the analog watchdog
        00000 for channel 0
        00001 for channel 1
        ..
        ..
        10001 for channel 17
*/
#define MADC_CR1_AWDCH_START_BIT                    0
/*
Interrupt enable for end of conversion:
    Set and cleared by software to enable/disable the EOC interrupt
*/
#define MADC_CR1_EOCIE_BIT                          5
/*
Analog Watchdog Interrupt Enable:
    Set and Cleared by Software to enable/disable the analog watchdog interrupt
*/
#define MADC_CR1_AWDIE_BIT                          6
/*
Interrupt Enable for Injected Channels:
    Set and cleared by software to enable/disable the EOC Interrupt for injected channels
*/
#define MADC_CR1_JEOCIE_BIT                         7
/*
Scan Mode:
1) Set and Cleared by software to enable/disable Scan mode.
2) In Scan Mode, the inputs selected through the ADC_SQRx or ADC_JSQRx registers
    are converted.
*/
#define MADC_CR1_SCAN_BIT                           8
/*
Enable the watchdog on a single channel in scan mode:
    Set and Cleared by Software to enable/disable the analog watchdog on the channel
    identified by the AWDCH[4:0] bits
*/
#define MADC_CR1_AWDSGL_BIT                         9
/*
Automatic Injected Group Conversion:
    Set and Cleared by software to enable/disable automatic injected group conversion after
    regular group conversion.
*/
#define MADC_CR1_JAUTO_BIT                          10
/*
Discontinuous Mode on Regular Channels:
    Set and cleared by software to enable/disable Discontinuous mode on regular channels
*/
#define MADC_CR1_DISCEN_BIT                         11
/*
Discontinuous Mode on Injected Channels:
    Set and cleared by software to enable/disable Discontinuous mode on injected channels
*/
#define MADC_CR1_JDISCEN_BIT                        12
/*
Discontinuous Mode Channel Count (3 bits):
    Written by software to define the number of regular channels to be convected in Discontinuous mode
        after receiving an external trigger
        000 ---> 1 channel
        001 ---> 2 channels
        ..
        ..
        111 ---> 8 channels
*/
#define MADC_CR1_DISCNUM_START_BIT                  13
/*
Dual mode selection (4 bits):
    Written by software to select the operating mode.
*/
#define MADC_CR1_DUALMOD_START_BIT                  16
/*
Analog Watchdog enable on injected channels:
    Set and Cleared by Software
*/
#define MADC_CR1_JAWDEN_BIT                         22
/*
Analog Watchdog Enable on regular channels:
    Set and Reset by Software
*/
#define MADC_CR1_AWDEN_BIT                          23 

/*****************************************ADC Control Register 2 (ADC_CR2) bits********************************************/

/*
A/D Converter ON/OFF:
1) Set and Cleared by Software.
2) If this bit holds a zero and a 1 is written to it, it wakes up the ADC from power down state.
3) Conversion Starts when this bit holds a value of 1 and a 1 is written to it.
4) The application should allow a delay of t_stab (1.5 clock cycle) between power up and start of conversion.
*/
#define MADC_CR2_ADON_BIT                           0
/*
Continuous Conversion Mode:
1) Set and Cleared by software.
2) If set, conversion takes place continuously till this bit is reset.
*/
#define MADC_CR2_CONT_BIT                           1
/*
A/D Calibration:
1) Set by software to start the calibration.
2) Reset by hardware after calibration is complete. 
*/
#define MADC_CR2_CAL_BIT                            2
/*
Reset Calibration:
1) Set by software and cleared by hardware.
2) Cleared after the calibration registers are initialized.
*/
#define MADC_CR2_RSTCAL_BIT                         3
/*
Direct Memory Access Mode:
    Set and Cleared by software
*/
#define MADC_CR2_DMA_BIT                            8
/*
Data Alignment:
    0 ----> Right Alignment "Converted data LSB at bit 0"
    1 ----> Left Alignment "Converted data MSB at position 31"
*/
#define MADC_CR2_ALIGN_BIT                          11
/*
External Event Select for Injected Group (3 bits):
    Select the external event used to trigger the start of conversion of an
    injected group
*/
#define MADC_CR2_JEXTSEL_START_BIT                  12
/*
External Trigger Conversion Mode for Injected Channels:
    Set and cleared by software to enable/disable the external trigger used to start conversion
    of an injected channel group.
*/
#define MADC_CR2_JEXTTRIG_BIT                       15
/*
External Event Select for regular group (3 bits):
    These bits select the external event used to trigger the start of 
    conversion of a regular group.
*/
#define MADC_CR2_EXTSEL_START_BIT                   17
/*
External Trigger Conversion Mode for Regular Channels:
    Set/Cleared by software to enable/disable the external trigger used to
    start conversion of a regular channel group.
*/      
#define MADC_CR2_EXTTRIG_BIT                        20
/*
Start conversion of injected channels:
1) Set by software and cleared by software/hardware as soon as the conversion starts.
2) Starts a conversion of a group of injected channels.
*/
#define MADC_CR2_JSWSTART_BIT                       21
/*
Start Conversion of Regular Channels:
1) Set by software to start conversion and cleared by hardware as soon as the conversion starts
2) Starts a conversion of a group of injected channels if SWSTART is selected as trigger
    event by the EXTSEL[2:0].
*/
#define MADC_CR2_SWSTART_BIT                        22
/*
Temperature Sensor and V_REFINT enable:
    Set & Cleared by software to enable/disable the temperature sensor and V_REFINT channel
*/
#define MADC_CR2_TSVREFE_BIT                        23


#define MADC_EXTERNAL_TRIGGER_ENABLED               1
#define MADC_EXTERNAL_TRIGGER_DISABLED              2

/***************************************External Trigger Events********************************/
#define MADC_TRIGGER_TIMER1_CC1_EVENT               0b000
#define MADC_TRIGGER_TIMER1_CC2_EVENT               0b001
#define MADC_TRIGGER_TIMER1_CC3_EVENT               0b010
#define MADC_TRIGGER_TIMER2_CC2_EVENT               0b011
#define MADC_TRIGGER_TIMER3_TRGO_EVENT              0b100
#define MADC_TRIGGER_TIMER4_CC4_EVENT               0b101
#define MADC_TRIGGER_EXTI_LINE_11_EVENT             0b110
#define MADC_TRIGGER_SWSTART                        0b111

/*****************************************ADC Operating Modes********************************************/
#define MADC_INDEPENDENT_MODE                       0b0000
#define MADC_COMBINED_REG_SIMUL_INJ_SIMUL           0b0001
#define MADC_COMBINED_REG_SIMUL_ALTERNATE_TRIG      0b0010
#define MADC_COMBINED_INJ_SIMUL_FAST_INTERLEAVED    0b0011
#define MADC_COMBINED_INJ_SIMUL_SLOW_INTERLEAVED    0b0100
#define MADC_INJ_SIMUL_MODE_ONLY                    0b0101
#define MADC_REG_SIMUL_MODE_ONLY                    0b0110
#define MADC_FAST_INTERLEAVED_ONLY                  0b0111
#define MADC_SLOW_INTERLEAVED_ONLY                  0b1000
#define MADC_ALTERNATE_TRIG_ONLY                    0b1001

/**************************************ADC Sample Times*****************************************/
#define MADC_SAMPLE_TIME_1_H_CYCLE                  0b000
#define MADC_SAMPLE_TIME_7_H_CYCLE                  0b001
#define MADC_SAMPLE_TIME_13_H_CYCLE                 0b010
#define MADC_SAMPLE_TIME_28_H_CYCLE                 0b011
#define MADC_SAMPLE_TIME_41_H_CYCLE                 0b100
#define MADC_SAMPLE_TIME_55_H_CYCLE                 0b101
#define MADC_SAMPLE_TIME_71_H_CYCLE                 0b110
#define MADC_SAMPLE_TIME_239_H_CYCLE                0b111

#define MADC_RIGHT_ADJUST_DATA_BITS                 0
#define MADC_LEFT_ADJUST_DATA_BITS                  1

#define MADC_EOC_INTERRUPT_ENABLED                  1
#define MADC_EOC_INTERRUPT_DISABLED                 2
#endif /*_ADC_PRIVATE_H_*/