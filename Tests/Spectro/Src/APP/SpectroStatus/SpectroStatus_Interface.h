/**
 * @file SpectroStatus_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _SPECTROSTATUS_INTERFACE_H_
#define _SPECTROSTATUS_INTERFACE_H_

typedef enum Spectrophotometer_Status
{
    IDLE,
    BUSY,
    INITIALIZING,
    ERROR_INITIALIZING
}SPECTRO_Status_t;

/**
 * @brief: Function to get the current status of our spectrophotometer 
 * 
 * @param P_uint32SpectroStatus:    Spectrophotometer Status
 * 
 * @return Std_ReturnType
 * @retval E_OK:                    Spectrophotometer's Status is given  
 * @retval E_NOT_OK:                Error giving status
 */
Std_ReturnType SpectroStatus_GetCurrentStatus       (SPECTRO_Status_t* P_uint32SpectroStatus);
/**
 * @brief: Function to set the new status of our spectrophotometer
 * 
 * @param Copy_uint32SpectroStatus: Spectrophotometer Status to be set
 * 
 * @return Std_ReturnType
 * @retval E_OK:                    Spectrophotometer's Status Successfully Set
 * @retval E_NOT_OK:                Spectrophotometer's Status not Set 
 */
Std_ReturnType SpectroStatus_SetNewStatus           (SPECTRO_Status_t Copy_uint32SpectroStatus);
#endif /*_SPECTROSTATUS_INTERFACE_H_*/