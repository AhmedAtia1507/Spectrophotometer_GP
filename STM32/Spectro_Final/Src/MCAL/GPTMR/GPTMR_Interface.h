/**
 * @file GPTMR_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2024-02-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _GPTMR_INTERFACE_H_
#define _GPTMR_INTERFACE_H_

typedef enum GPTMR_Timers
{
    MGPTMR2,
    MGPTMR3,
    MGPTMR4
} GPTMR_Select_t;

typedef void(*ptr_to_func_t)(void);

/**
 * @brief: Function to initialize General Purpose Timer (GPTMRx)
 * 
 * @param Copy_uint32TimerSelect:   Timer to be initialized
 * 
 * @return Std_ReturnType
 * @retval E_OK:                    Timer Successfully Initialized.
 * @retval E_NOT_OK:                Timer not initialized.
 */
Std_ReturnType MGPTMR_Init                              (GPTMR_Select_t Copy_uint32TimerSelect);
/**
 * @brief: Function to start the General Purpose Timer (GPTMRx)
 * 
 * @param Copy_uint32TimerSelect:   ID of the timer to be started
 * 
 * @return Std_ReturnType
 * @retval E_OK:                    Timer Successfully Started to Count.
 * @retval E_NOT_OK:                Timer not started.
 */
Std_ReturnType MGPTMR_StartTimer                        (GPTMR_Select_t Copy_uint32TimerSelect);
/**
 * @brief: Function to stop the General Purpose Timer (GPTMRx)
 * 
 * @param Copy_uint32TimerSelect:   ID of the timer to be stopped
 * 
 * @return Std_ReturnType
 * @retval E_OK:                    Timer Successfully Stopped Counting.
 * @retval E_NOT_OK:                Timer not stopped.
 */
Std_ReturnType MGPTMR_StopTimer                         (GPTMR_Select_t Copy_uint32TimerSelect);
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
Std_ReturnType MGPTMR_SetTimerPeriod                    (GPTMR_Select_t Copy_uint32TimerSelect, uint32 Copy_uint32PeriodInMs);
/**
 * @brief: Function to set the callback function of the GPTMR Update Interrupt
 * 
 * @param Copy_uint32TimerSelect:   ID of the timer whose interrupt function to be set 
 * @param P_UpdateCallbackFunc:     Function to be executed when Timer Update Interrupt Occurs
 * 
 * @return Std_ReturnType
 * @retval E_OK:                    Function Successfully Set
 * @retval E_NOT_OK:                Function not set  
 */
Std_ReturnType MGPTMR_SetTimerUpdateCallbackFunc        (GPTMR_Select_t Copy_uint32TimerSelect, ptr_to_func_t P_UpdateCallbackFunc);
#endif /*_GPTMR_INTERFACE_H_*/