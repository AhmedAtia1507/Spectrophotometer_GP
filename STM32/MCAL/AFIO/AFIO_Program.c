/**
 * @file AFIO_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/Std_Types.h"

#include "AFIO_Private.h"
#include "AFIO_Interface.h"
#include "AFIO_Config.h"

Std_ReturnType MAFIO_SetEXTIPinConfigurations(uint8 Copy_uint8EXTILine, uint8 Copy_uint8Port)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if((Copy_uint8Port <= MAFIO_PORTG_PIN) && (Copy_uint8EXTILine <= MAFIO_EXTI15))
    {
        uint8 Loc_uint8RegIndex = Copy_uint8EXTILine / 4;
        uint8 Loc_uint8RegOffset = Copy_uint8EXTILine % 4;

        MAFIO ->EXTICR[Loc_uint8RegIndex] &= ~((0b1111) << Loc_uint8RegOffset * 4);
        MAFIO ->EXTICR[Loc_uint8RegIndex] |= ((Copy_uint8Port) << Loc_uint8RegOffset * 4);
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}