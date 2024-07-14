/**
 * @file AFIO_Program.c
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

#include "AFIO_Private.h"
#include "AFIO_Interface.h"
#include "AFIO_Config.h"
/**
 * @brief: Function to set EXTI pin configurations for a specified EXTI Line
 * 
 * @param Copy_uint8EXTILine:               EXTI Line to be configured (0-15)
 * @param Copy_uint8Port:                   Port to configure the EXTI Line for (A-G)
 * 
 * @return Std_ReturnType
 * @retval E_OK:                            Configuration Successfully Set
 * @retval E_NOT_OK:                        Configuration not set 
 */
Std_ReturnType MAFIO_SetEXTIPinConfigurations(uint8 Copy_uint8EXTILine, uint8 Copy_uint8Port)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if((Copy_uint8Port <= MAFIO_PORTG_PIN) && (Copy_uint8EXTILine <= MAFIO_EXTI15))
    {
        // Calculate the index and offset for the EXTICR register
        uint8 Loc_uint8RegIndex = Copy_uint8EXTILine / 4;
        uint8 Loc_uint8RegOffset = Copy_uint8EXTILine % 4;

        // Clear the existing configuration for the specified EXTI line
        MAFIO ->EXTICR[Loc_uint8RegIndex] &= ~((0b1111) << Loc_uint8RegOffset * 4);
        
        // Set the new configuration for the specified EXTI line and port
        MAFIO ->EXTICR[Loc_uint8RegIndex] |= ((Copy_uint8Port) << Loc_uint8RegOffset * 4);
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}