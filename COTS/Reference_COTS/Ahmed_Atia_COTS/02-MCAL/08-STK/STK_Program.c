#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "STK_Private.h"
#include "STK_Interface.h"
#include "STK_Config.h"

static ptr_to_callback_func STK_PCallbackFunc = NULL;

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
Std_ReturnType STK_u8CalculateReloadValue(u32 Copy_u32msTime, u32* P_u32ReloadValue)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    if(P_u32ReloadValue != NULL)
    {
        u32 Loc_u32ReloadValue = 0;
        #if STK_CLOCK_SOURCE == STK_CLOCK_SOURCE_AHB_DIV_8
            Loc_u32ReloadValue = ((Copy_u32msTime / 1000) * (STK_AHB_CLOCK_FREQUENCY / 8));
        #elif STK_CLOCK_SOURCE == STK_CLOCK_SOURCE_AHB
            Loc_u32ReloadValue = ((Copy_u32msTime / 1000) * STK_AHB_CLOCK_FREQUENCY);
        #else
            #error "SysTick Timer Clock Source is not Identified"
        #endif /*STK_CLOCK_SOURCE*/
        if(Loc_u32ReloadValue <= 0xFFFFFF)
        {
            *P_u32ReloadValue = Loc_u32ReloadValue;
            Loc_u8FuncStatus = E_OK;
        }
        else
        {
            Loc_u8FuncStatus = E_NOT_OK;
        }
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}

/**
 * @brief: Function to initialize SysTick Timer Peripheral:
 *          1) Determine Interrupt Status "Enabled or Disabled"
 *          2) Determine SysTick Clock "(AHB / 8) or AHB"
 *          
 * 
 * @return Std_ReturnType
 * @retval E_OK: SysTick Timer is Successfully initialized
 * @retval E_NOT_OK: SysTick Timer is not initialized 
 */
Std_ReturnType MSTK_u8Init(void)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    /*Initialize value of LOAD and VAL register "To make sure that there is no value in it"*/
    STK -> LOAD = 0x000000;
    STK -> VAL = 0x000000;

    #if STK_CLOCK_SOURCE == STK_CLOCK_SOURCE_AHB_DIV_8
        CLR_BIT((STK -> CTRL), STK_CTRL_CLKSOURCE);
    #elif STK_CLOCK_SOURCE == STK_CLOCK_SOURCE_AHB
        SET_BIT((STK -> CTRL), STK_CTRL_CLKSOURCE);
    #else
        #error "SysTick Timer Clock Source is not Identified"
    #endif /*STK_CLOCK_SOURCE*/

    #if STK_INTERRUPT_STATUS == STK_INTERRUPT_ENABLED
        SET_BIT((STK -> CTRL), STK_CTRL_TICKINT);
    #elif STK_INTERRUPT_STATUS == STK_INTERRUPT_DISABLED
        CLR_BIT((STK -> CTRL), STK_CTRL_TICKINT);
    #else
        #error "Systick Timer Interrupt Status is not Identified"
    #endif /*STK_INTERRUPT_STATUS*/

    Loc_u8FuncStatus = E_OK;
    return Loc_u8FuncStatus;
}
/**
 * @brief: Function to set the duration of the timer
 * 
 * @param Copy_u32msTime: Time duration in milliseconds 
 * @return Std_ReturnType
 * @retval E_OK: SysTick Timer Duration is successfully set
 * @retval E_NOT_OK: SysTick Timer Duration is not set  
 */
Std_ReturnType MSTK_u8SetTimerDuration(u32 Copy_u32msTime)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    u32 Loc_u32ReloadValue = 0;
    Std_ReturnType Loc_u8ReloadStatus = STK_u8CalculateReloadValue(Copy_u32msTime, &Loc_u32ReloadValue);
    if(Loc_u8ReloadStatus == E_OK)
    {
        STK -> LOAD = Loc_u32ReloadValue;
        Loc_u8FuncStatus = E_OK;
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}
/**
 * @brief: Function to start the SysTick Timer
 * 
 * @return Std_ReturnType
 * @retval E_OK: SysTick Timer is Successfully started
 * @retval E_NOT_OK: SysTick Timer is not started 
 */
Std_ReturnType MSTK_u8StartTimer(void)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    SET_BIT((STK -> CTRL), STK_CTRL_ENABLE);
    Loc_u8FuncStatus = E_OK;
    return Loc_u8FuncStatus;
}
/**
 * @brief: Function to pause the SysTick Timer
 * 
 * @return Std_ReturnType
 * @retval E_OK: SysTick Timer is Successfully paused
 * @retval E_NOT_OK: SysTick Timer is not paused 
 */
Std_ReturnType MSTK_u8PauseTimer(void)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    CLR_BIT((STK -> CTRL), STK_CTRL_ENABLE);
    Loc_u8FuncStatus = E_OK;
    return Loc_u8FuncStatus;
}
/**
 * @brief: Function to Stop the SysTick Timer "Reset Timer"
 * 
 * @return Std_ReturnType 
 * @retval E_OK: SysTick Timer is Successfully stopped
 * @retval E_NOT_OK: SysTick Timer is not stopped 
 */
Std_ReturnType MSTK_u8StopTimer(void)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    CLR_BIT((STK -> CTRL), STK_CTRL_ENABLE);
    STK -> VAL = 0x000000;
    Loc_u8FuncStatus = E_OK;
    return Loc_u8FuncStatus;
}
/**
 * @brief: Function to perform delay on program using SysTick Timer
 * 
 * @param Copy_u32msTime: Delay Duration in ms
 * @return Std_ReturnType 
 * @retval E_OK: SysTick Delay is done successfully
 * @retval E_NOT_OK: SysTick Delay is not done 
 */
Std_ReturnType MSTK_u8Delay(u32 Copy_u32msTime)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    u32 Loc_u32ReloadValue = 0;
    u8 Loc_u8ReloadStatus = STK_u8CalculateReloadValue(Copy_u32msTime, &Loc_u32ReloadValue);
    if(Loc_u8ReloadStatus == E_OK)
    {
        //Disable Timer
        CLR_BIT((STK -> CTRL), STK_CTRL_ENABLE);

        //Make Sure that there is no value in the VAL register
        STK -> VAL = 0x000000;

        //Set Load value
        STK -> LOAD = Loc_u32ReloadValue;

        //Start Timer
        SET_BIT((STK -> CTRL), STK_CTRL_ENABLE);

        //Wait until counter is set to zero
        while(GET_BIT((STK -> CTRL), STK_CTRL_COUNTFLAG) == 0);

        //Disable Timer
        CLR_BIT((STK -> CTRL), STK_CTRL_ENABLE);

        //Make Sure that there is no value in the VAL & LOAD register
        STK -> VAL = 0x000000;
        STK -> LOAD = 0x000000;

        Loc_u8FuncStatus = E_OK;
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}
/**
 * @brief: Function to set the callback function of SysTick Timer Interrupt
 * 
 * @param P_CallbackFunc: Function to be executed when the timer counts to 0
 * @return Std_ReturnType
 * @retval E_OK: SysTick Timer Callback Function is successfully set
 * @retval E_NOT_OK: SysTick Timer Callback Function is not set  
 */
Std_ReturnType MSTK_u8SetCallbackFunction(ptr_to_callback_func P_CallbackFunc)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    if(P_CallbackFunc != NULL)
    {
        STK_PCallbackFunc = P_CallbackFunc;
        Loc_u8FuncStatus = E_OK;
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}

void SysTick_Handler(void)
{
	if(STK_PCallbackFunc != NULL)
	{
		STK_PCallbackFunc();
	}
	else
	{
		/*Do nothing*/
	}
}
