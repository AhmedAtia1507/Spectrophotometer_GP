/**
 * @file EXTI_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_Private.h"
#include "EXTI_Interface.h"
#include "EXTI_Config.h"

static volatile ptr_to_EXTICallback glbl_PEXTICallbackFunctions[20] = {NULL_PTR};

Std_ReturnType MEXTI_EnableExternalInterrupt(uint8 Copy_uint8EXTILine, uint8 Copy_uint8EXTIMode)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if((Copy_uint8EXTILine <= MEXTI_EXTI19) && (Copy_uint8EXTIMode <= MEXTI_INT_AT_BOTH_EDGES))
    {
        switch(Copy_uint8EXTIMode)
        {
            case MEXTI_INT_AT_RISING_EDGE:
            {
                SET_BIT((MEXTI->RTSR), Copy_uint8EXTILine);
                Loc_uint8FuncStatus = E_OK;
                break;
            }
            case MEXTI_INT_AT_FALLING_EDGE:
            {
                SET_BIT((MEXTI->FTSR), Copy_uint8EXTILine);
                Loc_uint8FuncStatus = E_OK;
                break;
            }
            case MEXTI_INT_AT_BOTH_EDGES:
            {
                SET_BIT((MEXTI->RTSR), Copy_uint8EXTILine);
                SET_BIT((MEXTI->FTSR), Copy_uint8EXTILine);
                Loc_uint8FuncStatus = E_OK;
            }
            default:
            {
                Loc_uint8FuncStatus = E_NOT_OK;
                break;
            }
        }

        SET_BIT((MEXTI -> IMR), Copy_uint8EXTILine);
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
Std_ReturnType MEXTI_DisableExternalInterrupt(uint8 Copy_uint8EXTILine)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(Copy_uint8EXTILine <= MEXTI_EXTI19)
    {
        CLR_BIT((MEXTI -> IMR), Copy_uint8EXTILine);
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
Std_ReturnType MEXTI_SoftwareTrigger(uint8 Copy_uint8EXTILine)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(Copy_uint8EXTILine <= MEXTI_EXTI19)
    {
        SET_BIT((MEXTI->SWIER), Copy_uint8EXTILine);
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
Std_ReturnType MEXTI_SetCallbackFunction(uint8 Copy_uint8EXTILine, ptr_to_EXTICallback P_EXTICallBackFunc)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(Copy_uint8EXTILine <= MEXTI_EXTI19)
    {
        glbl_PEXTICallbackFunctions[Copy_uint8EXTILine] = P_EXTICallBackFunc;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
void EXTI0_IRQHandler(void)
{
    if(glbl_PEXTICallbackFunctions[0] != NULL_PTR)
    {
        (glbl_PEXTICallbackFunctions[0])();
    }
    else
    {
        /*Do nothing*/
    }
}
void EXTI1_IRQHandler(void)
{
    if(glbl_PEXTICallbackFunctions[1] != NULL_PTR)
    {
        (glbl_PEXTICallbackFunctions[1])();
    }
    else
    {
        /*Do nothing*/
    }
}
void EXTI2_IRQHandler(void)
{
    if(glbl_PEXTICallbackFunctions[2] != NULL_PTR)
    {
        (glbl_PEXTICallbackFunctions[2])();
    }
    else
    {
        /*Do nothing*/
    }
}
void EXTI3_IRQHandler(void)
{
    if(glbl_PEXTICallbackFunctions[3] != NULL_PTR)
    {
        (glbl_PEXTICallbackFunctions[3])();
    }
    else
    {
        /*Do nothing*/
    }
}
void EXTI4_IRQHandler(void)
{
    if(glbl_PEXTICallbackFunctions[4] != NULL_PTR)
    {
        (glbl_PEXTICallbackFunctions[4])();
    }
    else
    {
        /*Do nothing*/
    }
}
void EXTI9_5_IRQHandler(void)
{
    if(GET_BIT((MEXTI->PR), 5))
    {
        if(glbl_PEXTICallbackFunctions[5] != NULL_PTR)
        {
            (glbl_PEXTICallbackFunctions[5])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((MEXTI->PR), 6))
    {
        if(glbl_PEXTICallbackFunctions[6] != NULL_PTR)
        {
            (glbl_PEXTICallbackFunctions[6])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((MEXTI->PR), 7))
    {
        if(glbl_PEXTICallbackFunctions[7] != NULL_PTR)
        {
            (glbl_PEXTICallbackFunctions[7])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((MEXTI->PR), 8))
    {
        if(glbl_PEXTICallbackFunctions[8] != NULL_PTR)
        {
            (glbl_PEXTICallbackFunctions[8])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((MEXTI->PR), 9))
    {
        if(glbl_PEXTICallbackFunctions[9] != NULL_PTR)
        {
            (glbl_PEXTICallbackFunctions[9])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else
    {
        /*Do nothing*/
    }
}
void EXTI15_10_IRQHandler(void)
{
    if(GET_BIT((MEXTI->PR), 10))
    {
        if(glbl_PEXTICallbackFunctions[10] != NULL_PTR)
        {
            (glbl_PEXTICallbackFunctions[10])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((MEXTI->PR), 11))
    {
        if(glbl_PEXTICallbackFunctions[11] != NULL_PTR)
        {
            (glbl_PEXTICallbackFunctions[11])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((MEXTI->PR), 12))
    {
        if(glbl_PEXTICallbackFunctions[12] != NULL_PTR)
        {
            (glbl_PEXTICallbackFunctions[12])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((MEXTI->PR), 13))
    {
        if(glbl_PEXTICallbackFunctions[13] != NULL_PTR)
        {
            (glbl_PEXTICallbackFunctions[13])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((MEXTI->PR), 14))
    {
        if(glbl_PEXTICallbackFunctions[14] != NULL_PTR)
        {
            (glbl_PEXTICallbackFunctions[14])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((MEXTI->PR), 15))
    {
        if(glbl_PEXTICallbackFunctions[15] != NULL_PTR)
        {
            (glbl_PEXTICallbackFunctions[15])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else
    {
        /*Do nothing*/
    }
}