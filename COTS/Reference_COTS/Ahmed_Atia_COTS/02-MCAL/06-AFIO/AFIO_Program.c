/**
 * @file AFIO_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-09-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "AFIO_Private.h"
#include "AFIO_Interface.h"
#include "AFIO_Config.h"

Std_ReturnType MAFIO_u8SetEXTIPinConfigurations(u8 Copy_u8EXTILine, u8 Copy_u8Port)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    if((Copy_u8Port <= AFIO_PORTG_PIN) && (Copy_u8EXTILine <= AFIO_EXTI15))
    {
        u8 Loc_u8RegIndex = Copy_u8EXTILine / 4;
        u8 Loc_u8RegOffset = Copy_u8EXTILine % 4;

        AFIO ->EXTICR[Loc_u8RegIndex] &= ~((0b1111) << Loc_u8RegOffset * 4);
        AFIO ->EXTICR[Loc_u8RegIndex] |= ((Copy_u8Port) << Loc_u8RegOffset * 4);
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}