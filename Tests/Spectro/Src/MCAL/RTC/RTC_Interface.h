/**
 * @file RTC_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _RTC_INTERFACE_H_
#define _RTC_INTERFACE_H_

typedef struct Sdate
{
    uint16 m_years;
    uint8 m_months;
    uint8 m_days;
}Sdate_t;

typedef struct Stime
{
    uint8 m_hours;
    uint8 m_minutes;
    uint8 m_seconds;
}Stime_t;

typedef void(*ptr_to_func_t)(void);

/**
 * @brief: Function to initialize RTC Peripheral
 * 
 * @return Std_ReturnType
 * @retval E_OK: RTC is Successfully initialized
 * @retval E_NOT_OK: RTC is not initialized 
 */
Std_ReturnType MRTC_Init            (void);
/**
 * @brief: Function to set the date and time of the RTC
 * 
 * @param P_SDateToBeSet: Date to be set
 * @param P_STimeToBeSet: Time to be set
 * 
 * @return Std_ReturnType
 * @retval E_OK: Date and time are successfully set
 * @retval E_NOT_OK: Date and time are not set
 */
Std_ReturnType MRTC_SetDateAndTime         (Sdate_t* P_SDateToBeSet, Stime_t* P_STimeToBeSet);
/**
 * @brief: Function to set the time of the RTC (24h. format)
 * 
 * @param P_STimeToBeSet: Time to be set
 * 
 * @return Std_ReturnType
 * @retval E_OK: Time is successfully set
 * @retval E_NOT_OK: Time is not set
 */
Std_ReturnType MRTC_SetTime         (Stime_t* P_STimeToBeSet);
/**
 * @brief: Function to get the date and time of the RTC
 * 
 * @param P_SDateToBeRead: Date stored in RTC
 * @param P_STimeToBeRead: Time stored in RTC
 * 
 * @return Std_ReturnType
 * @retval E_OK: Date & Time is successfully read
 * @retval E_NOT_OK: Date & Time is not read
 */
Std_ReturnType MRTC_GetDateAndTime  (Sdate_t* P_SDateToBeRead, Stime_t* P_STimeToBeRead);
Std_ReturnType MRTC_SetSecondIntCallbackFunc(ptr_to_func_t P_funcIntCallback);
#endif /*_RTC_INTERFACE_H_*/