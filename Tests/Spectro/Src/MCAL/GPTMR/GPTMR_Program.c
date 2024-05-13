/**
 * @file GPTMR_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/Std_Types.h"

#include "GPTMR_Private.h"
#include "GPTMR_Interface.h"
#include "GPTMR_Config.h"

static volatile MGPTMR_Typedef_t* (GPTMR[3]) = {TIM2, TIM3, TIM4};
static volatile ptr_to_func_t (glbl_PCallbackFunc[3]) = {NULL_PTR};

/**
 * @brief: Function to calculate the preload value from a given period in ms
 * 
 * @param Copy_uint32PeriodInMs:                        Period in ms 
 * @param P_uint16PreloadValue:                         Preload value to be set
 *  
 * @return Std_ReturnType
 * @retval E_OK:                                        Preload value successfully calculated
 * @retval E_NOT_OK:                                    Preload value not calculated 
 */
Std_ReturnType MGPTMR_GetPreloadValue                   (uint32 Copy_uint32PeriodInMs, uint16* P_uint16PreloadValue)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_uint16PreloadValue != NULL_PTR)
    {
        uint32 Loc_uint32TempPreload = (Copy_uint32PeriodInMs * (MGPTMR_CLK_FREQ / (MGPTMR_CLK_PRESCALER * 1000))) - 1;
        if(Loc_uint32TempPreload <= 0xFFFF)
        {
            *P_uint16PreloadValue = Loc_uint32TempPreload;
        }
        else
        {
            *P_uint16PreloadValue = 0xFFFF;
        }
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to initialize General Purpose Timer (GPTMRx)
 * 
 * @param Copy_uint32TimerSelect:   Timer to be initialized
 * 
 * @return Std_ReturnType
 * @retval E_OK:                    Timer Successfully Initialized.
 * @retval E_NOT_OK:                Timer not initialized.
 */
Std_ReturnType MGPTMR_Init                              (GPTMR_Select_t Copy_uint32TimerSelect)
{
    #if MGPTMR_UEV_STATUS == MGPTMR_UEV_ENABLED

        //Enable update event by clearing UDIS "Update Disable" bit
        CLR_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_UDIS_BIT);
        
        #if MGPTMR_UEV_SOURCE == MGPTMR_UEV_SOURCE_ALL

            CLR_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_URS_BIT);
    
        #elif MGPTMR_UEV_SOURCE == MGPTMR_UEV_SOURCE_OVERFLOW_UNDERFLOW
    
            SET_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_URS_BIT);
    
        #else
    
            #error "GPTMR Update Event Source Not Specified"
    
        #endif /*MGPTMR_UEV_SOURCE*/
    
    #elif MGPTMR_UEV_STATUS == MGPTMR_UEV_DISABLED
    
        //Disable update event by clearing UDIS "Update Disable" bit
        SET_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_UDIS_BIT);
    
    #else
    
        #error "GPTMR Update Event Status not specified"
    
    #endif /*MGPTMR_UEV_STATUS*/

    #if MGPTMR_ONE_PULSE_MODE_STATUS == MGPTMR_ONE_PULSE_MODE_ENABLED
    
        SET_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_OPM_BIT);
    
    #elif MGPTMR_ONE_PULSE_MODE_STATUS == MGPTMR_ONE_PULSE_MODE_DISABLED
    
        CLR_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_OPM_BIT);
    
    #else
    
        #error "GPTMR One Pulse Mode Status Not Specified"
    
    #endif /*MGPTMR_ONE_PULSE_MODE_STATUS*/

    #if MGPTMR_COUNTER_ALLIGNMENT == MGPTMR_EDGE_ALLIGNED_MODE
        
        CLR_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_CMS_START_BIT);
        CLR_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_CMS_START_BIT + 1);
        
        #if MGPTMR_COUNTER_DIRECTION == MGPTMR_COUNTER_UPCOUNTER
    
            CLR_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_DIR_BIT);
    
        #elif MGPTMR_COUNTER_DIRECTION == MGPTMR_COUNTER_DOWNCOUNTER
    
            SET_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_DIR_BIT);
    
        #else
    
            #error "GPTMR Counter Direction not Specified"
    
        #endif /*MGPTMR_COUNTER_DIRECTION*/

    #elif MGPTMR_COUNTER_ALLIGNMENT == MGPTMR_CENTER_ALLIGNED_MODE_1

        SET_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_CMS_START_BIT);
        CLR_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_CMS_START_BIT + 1);
    
    #elif MGPTMR_COUNTER_ALLIGNMENT == MGPTMR_CENTER_ALLIGNED_MODE_2
    
        CLR_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_CMS_START_BIT);
        SET_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_CMS_START_BIT + 1);
    
    #elif MGPTMR_COUNTER_ALLIGNMENT == MGPTMR_CENTER_ALLIGNED_MODE_3
    
        SET_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_CMS_START_BIT);
        SET_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_CMS_START_BIT + 1);
    
    #else
        #error "GPTMR Counter Allignment is not specified"
    #endif /*MGPTMR_COUNTER_ALLIGNMENT*/
    
    #if MGPTMR_AUTO_RELOAD_STATUS == MGPTMR_AUTO_RELOAD_ENABLED
    
        SET_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_ARPE_BIT);
    
    #elif MGPTMR_AUTO_RELOAD_STATUS == MGPTMR_AUTO_RELOAD_DISABLED
    
        CLR_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_ARPE_BIT);
    
    #else
    
        #error "GPTMR Auto Reload Status not Specified"
    
    #endif /*MGPTMR_AUTO_RELOAD_STATUS*/

    #if MGPTMR_UPDATE_INTERRUPT_STATUS == MGPTMR_UPDATE_INTERRUPT_ENABLED
    
        SET_BIT((GPTMR[Copy_uint32TimerSelect] -> DIER), MGPTMR_DIER_UIE_BIT);
    
    #elif MGPTMR_UPDATE_INTERRUPT_STATUS == MGPTMR_UPDATE_INTERRUPT_DISABLED
    
        CLR_BIT((GPTMR[Copy_uint32TimerSelect] -> DIER), MGPTMR_DIER_UIE_BIT);
    
    #else
    
        #error "GPTMR Update Interrupt Status not Specified"
    
    #endif /*MGPTMR_UPDATE_INTERRUPT_STATUS*/

    #if (MGPTMR_CLK_PRESCALER >= 1) || (MGPTMR_CLK_PRESCALER <= 65536)
    
        GPTMR[Copy_uint32TimerSelect] -> PSC = (uint16)((uint16)(MGPTMR_CLK_PRESCALER) - 1);
    
    #else
    
        #error "GPTMR Prescalar must have a value between 1 and 65536"
    
    #endif /*MGPTMR_CLK_PRESCALER*/
		
		CLR_BIT((GPTMR[Copy_uint32TimerSelect] -> SR), MGPTMR_SR_UIF_BIT);

    return E_OK; 
}
/**
 * @brief: Function to start the General Purpose Timer (GPTMRx)
 * 
 * @param Copy_uint32TimerSelect:   ID of the timer to be started
 * 
 * @return Std_ReturnType
 * @retval E_OK:                    Timer Successfully Started to Count.
 * @retval E_NOT_OK:                Timer not started.
 */
Std_ReturnType MGPTMR_StartTimer                        (GPTMR_Select_t Copy_uint32TimerSelect)
{
    SET_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_CEN_BIT);
    GPTMR[Copy_uint32TimerSelect] -> CNT = 0;
    return E_OK;
}
/**
 * @brief: Function to stop the General Purpose Timer (GPTMRx)
 * 
 * @param Copy_uint32TimerSelect:   ID of the timer to be stopped
 * 
 * @return Std_ReturnType
 * @retval E_OK:                    Timer Successfully Stopped Counting.
 * @retval E_NOT_OK:                Timer not stopped.
 */
Std_ReturnType MGPTMR_StopTimer                         (GPTMR_Select_t Copy_uint32TimerSelect)
{
    CLR_BIT((GPTMR[Copy_uint32TimerSelect] -> CR1), MGPTMR_CR1_CEN_BIT);
    return E_OK;
}
/**
 * @brief: Function to set the period of the general purpose timer (GPTMRx)
 * 
 * @param Copy_uint32TimerSelect:   ID of the timer whose period is to be set
 * @param Copy_uint32PeriodInMs:    Period to be set
 * 
 * @return Std_ReturnType
 * @retval E_OK:                    Period Successfully Set
 * @retval E_NOT_OK:                Period not set 
 */
Std_ReturnType MGPTMR_SetTimerPeriod                    (GPTMR_Select_t Copy_uint32TimerSelect, uint32 Copy_uint32PeriodInMs)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    uint16 Loc_uint16PreloadValue = 0;
    Loc_uint8FuncStatus = MGPTMR_GetPreloadValue(Copy_uint32PeriodInMs, &Loc_uint16PreloadValue);

    if(Loc_uint8FuncStatus == E_OK)
    {
        GPTMR[Copy_uint32TimerSelect] -> ARR = Loc_uint16PreloadValue;
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to set the callback function of the GPTMR Update Interrupt
 * 
 * @param Copy_uint32TimerSelect:   ID of the timer whose interrupt function to be set 
 * @param P_UpdateCallbackFunc:     Function to be set
 * 
 * @return Std_ReturnType
 * @retval E_OK:                    Function Successfully Set
 * @retval E_NOT_OK:                Function not set  
 */
Std_ReturnType MGPTMR_SetTimerUpdateCallbackFunc        (GPTMR_Select_t Copy_uint32TimerSelect, ptr_to_func_t P_UpdateCallbackFunc)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_UpdateCallbackFunc != NULL_PTR)
    {
        glbl_PCallbackFunc[Copy_uint32TimerSelect] = P_UpdateCallbackFunc;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}

void TIM2_IRQHandler(void)
{
    if(glbl_PCallbackFunc[0] != NULL_PTR)
    {
        (glbl_PCallbackFunc[0])();
    }
    else
    {
        /*Do nothing*/
    }
    CLR_BIT((GPTMR[0] -> SR), MGPTMR_SR_UIF_BIT);
}

void TIM3_IRQHandler(void)
{
    if(glbl_PCallbackFunc[1] != NULL_PTR)
    {
        (glbl_PCallbackFunc[1])();
    }
    else
    {
        /*Do nothing*/
    }
    CLR_BIT((GPTMR[1] -> SR), MGPTMR_SR_UIF_BIT);
}

void TIM4_IRQHandler(void)
{
    if(glbl_PCallbackFunc[2] != NULL_PTR)
    {
        (glbl_PCallbackFunc[2])();
    }
    else
    {
        /*Do nothing*/
    }
    CLR_BIT((GPTMR[2] -> SR), MGPTMR_SR_UIF_BIT);
}