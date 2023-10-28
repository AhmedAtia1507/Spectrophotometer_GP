#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_Private.h"
#include "EXTI_Interface.h"
#include "EXTI_Config.h"

static volatile ptr_to_EXTICallback glbl_PEXTICallbackFunctions[20] = {NULL};

Std_ReturnType MEXTI_u8EnableExternalInterrupt(u8 Copy_u8EXTILine, u8 Copy_u8EXTIMode)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    if((Copy_u8EXTILine <= MEXTI_EXTI19) && (Copy_u8EXTIMode <= MEXTI_INT_AT_BOTH_EDGES))
    {
        switch(Copy_u8EXTIMode)
        {
            case MEXTI_INT_AT_RISING_EDGE:
            {
                SET_BIT((EXTI->RTSR), Copy_u8EXTILine);
                Loc_u8FuncStatus = E_OK;
                break;
            }
            case MEXTI_INT_AT_FALLING_EDGE:
            {
                SET_BIT((EXTI->FTSR), Copy_u8EXTILine);
                Loc_u8FuncStatus = E_OK;
                break;
            }
            case MEXTI_INT_AT_BOTH_EDGES:
            {
                SET_BIT((EXTI->RTSR), Copy_u8EXTILine);
                SET_BIT((EXTI->FTSR), Copy_u8EXTILine);
                Loc_u8FuncStatus = E_OK;
            }
            default:
            {
                Loc_u8FuncStatus = E_NOT_OK;
                break;
            }
        }

        SET_BIT((EXTI -> IMR), Copy_u8EXTILine);
        Loc_u8FuncStatus = E_OK;
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}
Std_ReturnType MEXTI_u8DisableExternalInterrupt(u8 Copy_u8EXTILine)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    if(Copy_u8EXTILine <= MEXTI_EXTI19)
    {
        CLR_BIT((EXTI -> IMR), Copy_u8EXTILine);
        Loc_u8FuncStatus = E_OK;
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}
Std_ReturnType MEXTI_u8SoftwareTrigger(u8 Copy_u8EXTILine)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    if(Copy_u8EXTILine <= MEXTI_EXTI19)
    {
        SET_BIT((EXTI->SWIER), Copy_u8EXTILine);
        Loc_u8FuncStatus = E_OK;
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}
Std_ReturnType MEXTI_u8SetCallbackFunction(u8 Copy_u8EXTILine, ptr_to_EXTICallback P_EXTICallBackFunc)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    if(Copy_u8EXTILine <= MEXTI_EXTI19)
    {
        glbl_PEXTICallbackFunctions[Copy_u8EXTILine] = P_EXTICallBackFunc;
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}
void EXTI0_IRQHandler(void)
{
    if(glbl_PEXTICallbackFunctions[0] != NULL)
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
    if(glbl_PEXTICallbackFunctions[1] != NULL)
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
    if(glbl_PEXTICallbackFunctions[2] != NULL)
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
    if(glbl_PEXTICallbackFunctions[3] != NULL)
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
    if(glbl_PEXTICallbackFunctions[4] != NULL)
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
    if(GET_BIT((EXTI->PR), 5))
    {
        if(glbl_PEXTICallbackFunctions[5] != NULL)
        {
            (glbl_PEXTICallbackFunctions[5])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((EXTI->PR), 6))
    {
        if(glbl_PEXTICallbackFunctions[6] != NULL)
        {
            (glbl_PEXTICallbackFunctions[6])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((EXTI->PR), 7))
    {
        if(glbl_PEXTICallbackFunctions[7] != NULL)
        {
            (glbl_PEXTICallbackFunctions[7])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((EXTI->PR), 8))
    {
        if(glbl_PEXTICallbackFunctions[8] != NULL)
        {
            (glbl_PEXTICallbackFunctions[8])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((EXTI->PR), 9))
    {
        if(glbl_PEXTICallbackFunctions[9] != NULL)
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
    if(GET_BIT((EXTI->PR), 10))
    {
        if(glbl_PEXTICallbackFunctions[10] != NULL)
        {
            (glbl_PEXTICallbackFunctions[10])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((EXTI->PR), 11))
    {
        if(glbl_PEXTICallbackFunctions[11] != NULL)
        {
            (glbl_PEXTICallbackFunctions[11])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((EXTI->PR), 12))
    {
        if(glbl_PEXTICallbackFunctions[12] != NULL)
        {
            (glbl_PEXTICallbackFunctions[12])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((EXTI->PR), 13))
    {
        if(glbl_PEXTICallbackFunctions[13] != NULL)
        {
            (glbl_PEXTICallbackFunctions[13])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((EXTI->PR), 14))
    {
        if(glbl_PEXTICallbackFunctions[14] != NULL)
        {
            (glbl_PEXTICallbackFunctions[14])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((EXTI->PR), 15))
    {
        if(glbl_PEXTICallbackFunctions[15] != NULL)
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