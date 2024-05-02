/**
 * @file SpectroStatus_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/Std_Types.h"

#include "SpectroStatus_Interface.h"

static volatile SPECTRO_Status_t glbl_uint32SpectroCurrentStatus = IDLE;
/**
 * @brief: Function to get the current status of our spectrophotometer 
 * 
 * @param P_uint32SpectroStatus:    Spectrophotometer Status
 * 
 * @return Std_ReturnType
 * @retval E_OK:                    Spectrophotometer's Status is given  
 * @retval E_NOT_OK:                Error giving status
 */
Std_ReturnType SpectroStatus_GetCurrentStatus       (SPECTRO_Status_t* P_uint32SpectroStatus)
{
    if(P_uint32SpectroStatus != NULL_PTR)
    {
        *P_uint32SpectroStatus = glbl_uint32SpectroCurrentStatus;
        return E_OK;
    }
    else
    {
        return E_NOT_OK;
    }
}
/**
 * @brief: Function to set the new status of our spectrophotometer
 * 
 * @param Copy_uint32SpectroStatus: Spectrophotometer Status to be set
 * 
 * @return Std_ReturnType
 * @retval E_OK:                    Spectrophotometer's Status Successfully Set
 * @retval E_NOT_OK:                Spectrophotometer's Status not Set 
 */
Std_ReturnType SpectroStatus_SetNewStatus           (SPECTRO_Status_t Copy_uint32SpectroStatus)
{
    glbl_uint32SpectroCurrentStatus = Copy_uint32SpectroStatus;
    return E_OK;
}