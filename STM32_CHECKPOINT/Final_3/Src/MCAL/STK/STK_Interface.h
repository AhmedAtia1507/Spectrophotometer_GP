
#ifndef _STK_INTERFACE_H_
#define _STK_INTERFACE_H_


typedef void(*ptr_to_callback_func)(void);
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
Std_ReturnType MSTK_uint8Init(void);
/**
 * @brief: Function to set the duration of the timer
 * 
 * @param Copy_uint32msTime: Time duration in milliseconds 
 * @return Std_ReturnType
 * @retval E_OK: SysTick Timer Duration is successfully set
 * @retval E_NOT_OK: SysTick Timer Duration is not set  
 */
Std_ReturnType MSTK_uint8SetTimerDuration(uint32 Copy_uint32msTime);
/**
 * @brief: Function to start the SysTick Timer
 * 
 * @return Std_ReturnType
 * @retval E_OK: SysTick Timer is Successfully started
 * @retval E_NOT_OK: SysTick Timer is not started 
 */
Std_ReturnType MSTK_uint8StartTimer(void);
/**
 * @brief: Function to pause the SysTick Timer
 * 
 * @return Std_ReturnType
 * @retval E_OK: SysTick Timer is Successfully paused
 * @retval E_NOT_OK: SysTick Timer is not paused 
 */
Std_ReturnType MSTK_uint8PauseTimer(void);
/**
 * @brief: Function to Stop the SysTick Timer
 * 
 * @return Std_ReturnType 
 * @retval E_OK: SysTick Timer is Successfully stopped
 * @retval E_NOT_OK: SysTick Timer is not stopped 
 */
Std_ReturnType MSTK_uint8StopTimer(void);
/**
 * @brief: Function to perform delay on program using SysTick Timer
 * 
 * @param Copy_uint32msTime: Delay Duration in ms
 * @return Std_ReturnType 
 * @retval E_OK: SysTick Delay is done successfully
 * @retval E_NOT_OK: SysTick Delay is not done 
 */
Std_ReturnType MSTK_uint8Delay(uint32 Copy_uint32msTime);
/**
 * @brief: Function to perform delay on program using SysTick Timer
 * 
 * @param Copy_uint32msTime: Delay Duration in us
 * @return Std_ReturnType 
 * @retval E_OK: SysTick Delay is done successfully
 * @retval E_NOT_OK: SysTick Delay is not done 
 */
Std_ReturnType MSTK_uint8DelayUs(uint32 Copy_uint32usTime);
/**
 * @brief: Function to set the callback function of SysTick Timer Interrupt
 * 
 * @param P_CallbackFunc: Function to be executed when the timer counts to 0
 * @return Std_ReturnType
 * @retval E_OK: SysTick Timer Callback Function is successfully set
 * @retval E_NOT_OK: SysTick Timer Callback Function is not set  
 */
Std_ReturnType MSTK_uint8SetCallbackFunction(ptr_to_callback_func P_CallbackFunc);
#endif /*_STK_INTERFACE_H_*/