/**
 * @file STK_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: Header file that contains the memory mapping of SysTick Timer Peripheral 
 * @version 1.0
 * @date 2023-09-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _STK_PRIVATE_H_
#define _STK_PRIVATE_H_

/*
    SysTick Timer: 
    1) It is a 24-bit System Count-Down Timer. It counts down every SysTick Clock Cycle.
    2) Counts Down from the reload value to zero then reloads the value in the LOAD register
        on the next clock.
*/
typedef struct STK_Registers
{
    /*
        SysTick Control & Status Register: 
            Enables the SysTick features
    */
    volatile u32 CTRL;
    /*
        SysTick Reload Value Register:
            Contains the Reload Value that the Timer will count down from
    */
    volatile u32 LOAD;
    /*
        SysTick Current Value Register:
            This Register contains the current value of the SysTick Counter
        -If this register is read, it will return the current value of the SysTick Counter
        -If a write operation is executed with any value, it will clear it to 0 and also clears the COUNTFLAG
            bit in STK_CTRL register to 0
    */
    volatile u32 VAL;
    /*SysTick Calibration Value Register*/
    volatile u32 CALIB;
}STK_RegDef_t;

#define STK_BASE_ADDRESS                                0xE000E010U
#define STK                                             ((STK_RegDef_t *)STK_BASE_ADDRESS)
/*********************************SysTick Control & Status Register (STK_CTRL) Bits**************************/

/*
    Counter Enable:
        1) When ENABLE is set to 1, the counter loads the RELOAD value from the 
            LOAD Register and then Counts Down.
        2) On reaching 0, it sets the COUNTFLAG and optionally asserts the SysTick depending on the value of
            TICKINT "Fires an interrupt if enabled".
        3) It then loads the value again and begins counting
*/
#define STK_CTRL_ENABLE                                 0
/*
    SysTick Exception Request Enable:
    0 --> Counting down to zero does not assert the SysTick Exception Request
    1 --> Counting down to zero asserts the SysTick Exception Request
*/
#define STK_CTRL_TICKINT                                1
/*
    SysTick Clock Source Selection:
    0 ----> (Advanced High-Performance Bus Clock "AHB") / 8
    1 ----> Advanced High-Performance Bus Clock "AHB"
*/
#define STK_CTRL_CLKSOURCE                              2
/*
    This flag returns 1 if the SysTick Timer Counted to 0 since the
    last time this was read
*/
#define STK_CTRL_COUNTFLAG                              16

/**************************Options for SysTick Clock****************************/

#define STK_CLOCK_SOURCE_AHB_DIV_8                      1
#define STK_CLOCK_SOURCE_AHB                            2

/*************************Options for Interrupt Status*************************/

#define STK_INTERRUPT_ENABLED                           1
#define STK_INTERRUPT_DISABLED                          2

/**
 * @brief: Function to Calculate the reload value of the SysTick timer that relates to
 *          the given time
 * 
 * @param Copy_u32msTime: Duration in milliseconds
 * @param P_u32ReloadValue: Pointer to pass the reload value in it
 * 
 * @return Std_ReturnType
 * @retval E_OK: Reload value is successfully calculated
 * @retval E_NOT_OK: Reload value can not be calculated 
 */
Std_ReturnType STK_u8CalculateReloadValue(u32 Copy_u32msTime, u32* P_u32ReloadValue);
#endif /*_STK_PRIVATE_H_*/