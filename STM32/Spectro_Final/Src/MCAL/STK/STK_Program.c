/**
 * @file STK_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/Std_Types.h"

#include "STK_Private.h"
#include "STK_Interface.h"
#include "STK_Config.h"

/**
 * @brief: A pointer to function to be executed when SysTick Timer Interrupt Occurs
 * 
 */
static ptr_to_callback_func STK_PCallbackFunc = NULL_PTR;

/**
 * @brief: Function to Calculate the reload value of the SysTick timer that relates to
 *          the given time
 * 
 * @param Copy_uint32msTime: Duration in milliseconds
 * @param P_uint32ReloadValue: Pointer to pass the reload value in it
 * 
 * @return Std_ReturnType
 * @retval E_OK: Reload value is successfully calculated
 * @retval E_NOT_OK: Reload value can not be calculated 
 */
Std_ReturnType STK_uint8CalculateReloadValue(uint32 Copy_uint32msTime, uint32* P_uint32ReloadValue)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_uint32ReloadValue != NULL_PTR)
    {
        uint32 Loc_uint32ReloadValue = 0;

        /************************************************************************************************* 
            We Calculate Reload Value to be set by multiplying time period to be set by the Systick Timer 
                        Clock Frequency (AHB Clock Frequency or AHB Clock Frequency divided by 8)
        *************************************************************************************************/
        #if STK_CLOCK_SOURCE == STK_CLOCK_SOURCE_AHB_DIV_8
            Loc_uint32ReloadValue = ((Copy_uint32msTime * (STK_AHB_CLOCK_FREQUENCY / 8000)));
        #elif STK_CLOCK_SOURCE == STK_CLOCK_SOURCE_AHB
            Loc_uint32ReloadValue = ((Copy_uint32msTime* STK_AHB_CLOCK_FREQUENCY) / 1000);
        #else
            #error "SysTick Timer Clock Source is not Identified"
        #endif /*STK_CLOCK_SOURCE*/

        /************************************************************************************************* 
            Since the SysTick Timer is a 24-bit downcounter, Its maximum value to be set is 0xFFFFFF
        *************************************************************************************************/
        if(Loc_uint32ReloadValue <= 0xFFFFFF)
        {
            *P_uint32ReloadValue = Loc_uint32ReloadValue;
            Loc_uint8FuncStatus = E_OK;
        }
        else
        {
            Loc_uint8FuncStatus = E_NOT_OK;
        }
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to Calculate the reload value of the SysTick timer that relates to
 *          the given time
 * 
 * @param Copy_uint32msTime: Duration in microseconds
 * @param P_uint32ReloadValue: Pointer to pass the reload value in it
 * 
 * @return Std_ReturnType
 * @retval E_OK: Reload value is successfully calculated
 * @retval E_NOT_OK: Reload value can not be calculated 
 */
Std_ReturnType STK_uint8CalculateReloadValueUs(uint32 Copy_uint32usTime, uint32* P_uint32ReloadValue)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_uint32ReloadValue != NULL_PTR)
    {
        uint32 Loc_uint32ReloadValue = 0;

        /************************************************************************************************* 
            We Calculate Reload Value to be set by multiplying time period to be set by the Systick Timer 
                        Clock Frequency (AHB Clock Frequency or AHB Clock Frequency divided by 8)
        *************************************************************************************************/
        #if STK_CLOCK_SOURCE == STK_CLOCK_SOURCE_AHB_DIV_8
            Loc_uint32ReloadValue = ((Copy_uint32usTime * (STK_AHB_CLOCK_FREQUENCY / 8000000)));
        #elif STK_CLOCK_SOURCE == STK_CLOCK_SOURCE_AHB
            Loc_uint32ReloadValue = (Copy_uint32usTime * (STK_AHB_CLOCK_FREQUENCY / 1000000));
        #else
            #error "SysTick Timer Clock Source is not Identified"
        #endif /*STK_CLOCK_SOURCE*/
        
        /************************************************************************************************* 
            Since the SysTick Timer is a 24-bit downcounter, Its maximum value to be set is 0xFFFFFF
        *************************************************************************************************/
        if(Loc_uint32ReloadValue <= 0xFFFFFF)
        {
            *P_uint32ReloadValue = Loc_uint32ReloadValue;
            Loc_uint8FuncStatus = E_OK;
        }
        else
        {
            Loc_uint8FuncStatus = E_NOT_OK;
        }
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to initialize SysTick Timer Peripheral:
 *          1) Determine Interrupt Status "Enabled or Disabled"
 *          2) Determine SysTick Clock "(AHB / 8) or AHB"
 *          
 * 
 * @return Std_ReturnType
 * @retval E_OK:        SysTick Timer is Successfully initialized
 * @retval E_NOT_OK:    SysTick Timer is not initialized 
 */
Std_ReturnType MSTK_uint8Init(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    /************************************************************************************************* 
            1. Initialize Value of LOAD "Reload Value" and VAL "counter" Registers
    *************************************************************************************************/
    STK -> LOAD = 0x000000;
    STK -> VAL = 0x000000;

    /************************************************************************************************* 
            2. Select the SysTick Timer Clock Source ((AHB / 8) or AHB)
    *************************************************************************************************/
    #if STK_CLOCK_SOURCE == STK_CLOCK_SOURCE_AHB_DIV_8
        CLR_BIT((STK -> CTRL), STK_CTRL_CLKSOURCE);
    #elif STK_CLOCK_SOURCE == STK_CLOCK_SOURCE_AHB
        SET_BIT((STK -> CTRL), STK_CTRL_CLKSOURCE);
    #else
        #error "SysTick Timer Clock Source is not Identified"
    #endif /*STK_CLOCK_SOURCE*/

    /************************************************************************************************* 
            3. Set the SysTick Timer Interrupt Status "When Timer Reaches Zero"
    *************************************************************************************************/
    #if STK_INTERRUPT_STATUS == STK_INTERRUPT_ENABLED
        SET_BIT((STK -> CTRL), STK_CTRL_TICKINT);
    #elif STK_INTERRUPT_STATUS == STK_INTERRUPT_DISABLED
        CLR_BIT((STK -> CTRL), STK_CTRL_TICKINT);
    #else
        #error "Systick Timer Interrupt Status is not Identified"
    #endif /*STK_INTERRUPT_STATUS*/

    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to set the duration of the timer
 * 
 * @param Copy_uint32msTime:    Time duration in milliseconds 
 * @return Std_ReturnType
 * @retval E_OK:                SysTick Timer Duration is successfully set
 * @retval E_NOT_OK:            SysTick Timer Duration is not set  
 */
Std_ReturnType MSTK_uint8SetTimerDuration(uint32 Copy_uint32msTime)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    uint32 Loc_uint32ReloadValue = 0;

    /************************************************************************************************* 
            1. Calculate Reload Value to be set
    *************************************************************************************************/
    Std_ReturnType Loc_uint8ReloadStatus = STK_uint8CalculateReloadValue(Copy_uint32msTime, &Loc_uint32ReloadValue);

    if(Loc_uint8ReloadStatus == E_OK)
    {
        /************************************************************************************************* 
                2. Set the reload value of SysTick Timer
        *************************************************************************************************/
        STK -> LOAD = Loc_uint32ReloadValue;
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to start the SysTick Timer
 * 
 * @return Std_ReturnType
 * @retval E_OK:                SysTick Timer is Successfully started
 * @retval E_NOT_OK:            SysTick Timer is not started 
 */
Std_ReturnType MSTK_uint8StartTimer(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    SET_BIT((STK -> CTRL), STK_CTRL_ENABLE);
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to pause the SysTick Timer
 * 
 * @return Std_ReturnType
 * @retval E_OK:                SysTick Timer is Successfully paused
 * @retval E_NOT_OK:            SysTick Timer is not paused 
 */
Std_ReturnType MSTK_uint8PauseTimer(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    CLR_BIT((STK -> CTRL), STK_CTRL_ENABLE);
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to Stop the SysTick Timer "Reset Timer"
 * 
 * @return Std_ReturnType 
 * @retval E_OK:                SysTick Timer is Successfully stopped
 * @retval E_NOT_OK:            SysTick Timer is not stopped 
 */
Std_ReturnType MSTK_uint8StopTimer(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    CLR_BIT((STK -> CTRL), STK_CTRL_ENABLE);
    STK -> VAL = 0x000000;
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to perform delay on program using SysTick Timer
 * 
 * @param Copy_uint32msTime: Delay Duration in ms
 * @return Std_ReturnType 
 * @retval E_OK: SysTick Delay is done successfully
 * @retval E_NOT_OK: SysTick Delay is not done 
 */
Std_ReturnType MSTK_uint8Delay(uint32 Copy_uint32msTime)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    uint32 Loc_uint32ReloadValue = 0;
    
    /************************************************************************************************* 
            1. Calculate the Reload Value to be set
    *************************************************************************************************/
    uint8 Loc_uint8ReloadStatus = STK_uint8CalculateReloadValue(Copy_uint32msTime, &Loc_uint32ReloadValue);
    
    if(Loc_uint8ReloadStatus == E_OK)
    {
        /************************************************************************************************* 
            2. Disable SysTick Timer
        *************************************************************************************************/
        CLR_BIT((STK -> CTRL), STK_CTRL_ENABLE);

        /************************************************************************************************* 
            3. Make Sure that there is no value in the VAL register
        *************************************************************************************************/
        STK -> VAL = 0x000000;

        /************************************************************************************************* 
            4. Set the Reload Value
        *************************************************************************************************/
        STK -> LOAD = Loc_uint32ReloadValue;

        /************************************************************************************************* 
            5. Start SysTick Timer
        *************************************************************************************************/
        SET_BIT((STK -> CTRL), STK_CTRL_ENABLE);

        /************************************************************************************************* 
            6. Wait Until Counter Reaches Zero
        *************************************************************************************************/
        while(GET_BIT((STK -> CTRL), STK_CTRL_COUNTFLAG) == 0);

        /************************************************************************************************* 
            7. Disable SysTick Timer and set the registers' values to zero
        *************************************************************************************************/
        CLR_BIT((STK -> CTRL), STK_CTRL_ENABLE);

        STK -> VAL = 0x000000;
        STK -> LOAD = 0x000000;

        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to perform delay on program using SysTick Timer
 * 
 * @param Copy_uint32msTime: Delay Duration in us
 * @return Std_ReturnType 
 * @retval E_OK: SysTick Delay is done successfully
 * @retval E_NOT_OK: SysTick Delay is not done 
 */
Std_ReturnType MSTK_uint8DelayUs(uint32 Copy_uint32usTime)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    uint32 Loc_uint32ReloadValue = 0;
    
    /************************************************************************************************* 
            1. Calculate the Reload Value to be set
    *************************************************************************************************/
    uint8 Loc_uint8ReloadStatus = STK_uint8CalculateReloadValueUs(Copy_uint32usTime, &Loc_uint32ReloadValue);
    
    if(Loc_uint8ReloadStatus == E_OK)
    {
        /************************************************************************************************* 
            2. Disable SysTick Timer
        *************************************************************************************************/
        CLR_BIT((STK -> CTRL), STK_CTRL_ENABLE);

        /************************************************************************************************* 
            3. Make Sure that there is no value in the VAL register
        *************************************************************************************************/
        STK -> VAL = 0x000000;

        /************************************************************************************************* 
            4. Set the Reload Value
        *************************************************************************************************/
        STK -> LOAD = Loc_uint32ReloadValue;

        /************************************************************************************************* 
            5. Start SysTick Timer
        *************************************************************************************************/
        SET_BIT((STK -> CTRL), STK_CTRL_ENABLE);

        /************************************************************************************************* 
            6. Wait Until Counter Reaches Zero
        *************************************************************************************************/
        while(GET_BIT((STK -> CTRL), STK_CTRL_COUNTFLAG) == 0);

        /************************************************************************************************* 
            7. Disable SysTick Timer and set the registers' values to zero
        *************************************************************************************************/
        CLR_BIT((STK -> CTRL), STK_CTRL_ENABLE);

        STK -> VAL = 0x000000;
        STK -> LOAD = 0x000000;

        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to set the callback function of SysTick Timer Interrupt
 * 
 * @param P_CallbackFunc:   Function to be executed when the timer counts to 0
 * @return Std_ReturnType
 * @retval E_OK:            SysTick Timer Callback Function is successfully set
 * @retval E_NOT_OK:        SysTick Timer Callback Function is not set  
 */
Std_ReturnType MSTK_uint8SetCallbackFunction(ptr_to_callback_func P_CallbackFunc)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_CallbackFunc != NULL_PTR)
    {
        STK_PCallbackFunc = P_CallbackFunc;
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}

void SysTick_Handler(void)
{
	if(STK_PCallbackFunc != NULL_PTR)
	{
		STK_PCallbackFunc();
	}
	else
	{
		/*Do nothing*/
	}
}
