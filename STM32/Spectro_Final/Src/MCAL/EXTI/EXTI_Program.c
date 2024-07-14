/**
 * @file EXTI_Program.c
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

#include "EXTI_Private.h"
#include "EXTI_Interface.h"
#include "EXTI_Config.h"

/**
 * @brief: An array of pointers to 16 functions that are executed when the corresponding external interrupt occurs
 * 
 */
static volatile ptr_to_EXTICallback glbl_PEXTICallbackFunctions[16] = {NULL_PTR};

/**
 * @brief: Function to enable external interrupt on one of the EXTI Lines with a specific mode
 * 
 * @param Copy_uint8EXTILine:                   EXTI Line whose interrupt is to be enabled
 * @param Copy_uint8EXTIMode:                   EXTI Mode (Interrupt at rising, falling or both edges)
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                Interrupt on EXTI Line successfully enabled
 * @retval E_NOT_OK:                            Interrupt on EXTI Line not enabled 
 */
Std_ReturnType MEXTI_EnableExternalInterrupt(uint8 Copy_uint8EXTILine, uint8 Copy_uint8EXTIMode)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    if((Copy_uint8EXTILine <= MEXTI_EXTI15) && (Copy_uint8EXTIMode <= MEXTI_INT_AT_BOTH_EDGES))
    {
        /************************************************************************************************* 
            1) Set External Interrupt Mode (Interrupt occurs at rising, falling or at both edges)
        *************************************************************************************************/
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

        /************************************************************************************************* 
            2) Enable External Interrupt on specified EXTI Line
        *************************************************************************************************/
        SET_BIT((MEXTI -> IMR), Copy_uint8EXTILine);

        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to disable the external interrupt on one of the EXTI Lines
 * 
 * @param Copy_uint8EXTILine:                   EXTI Line whose interrupt is to be disabled
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                Interrupt on EXTI Line successfully disabled
 * @retval E_NOT_OK:                            Interrupt on EXTI Line not disabled  
 */
Std_ReturnType MEXTI_DisableExternalInterrupt(uint8 Copy_uint8EXTILine)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(Copy_uint8EXTILine <= MEXTI_EXTI15)
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
/**
 * @brief: Function to trigger External Interrupt on one of the EXTI Lines using software
 * 
 * @param Copy_uint8EXTILine:                   EXTI Line whose interrupt is to be triggered
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                Interrupt on EXTI Line successfully triggered
 * @retval E_NOT_OK:                            Interrupt on EXTI Line not triggered  
 */
Std_ReturnType MEXTI_SoftwareTrigger(uint8 Copy_uint8EXTILine)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(Copy_uint8EXTILine <= MEXTI_EXTI15)
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
/**
 * @brief: Function to set the function which will be executed when external interrupt on a specific
 *          EXTI Line occurs
 * 
 * @param Copy_uint8EXTILine:                   EXTI Line whose interrupt function is to be set
 * @param P_EXTICallBackFunc:                   Pointer to function that will be executed when EXTI occurs
 *  
 * @return Std_ReturnType
 * @retval E_OK:                                Interrupt function successfully set
 * @retval E_NOT_OK:                            Interrupt function not set 
 */
Std_ReturnType MEXTI_SetCallbackFunction(uint8 Copy_uint8EXTILine, ptr_to_EXTICallback P_EXTICallBackFunc)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(Copy_uint8EXTILine <= MEXTI_EXTI15)
    {
        glbl_PEXTICallbackFunctions[Copy_uint8EXTILine] = P_EXTICallBackFunc;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function that represents the interrupt service routine for EXTI0 Line
 * 
 */
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
    SET_BIT((MEXTI -> PR), 0);
}
/**
 * @brief: Function that represents the interrupt service routine for EXTI1 Line
 * 
 */
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
    SET_BIT((MEXTI -> PR), 1);
}
/**
 * @brief: Function that represents the interrupt service routine for EXTI2 Line
 * 
 */
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
    SET_BIT((MEXTI -> PR), 2);
}
/**
 * @brief: Function that represents the interrupt service routine for EXTI3 Line
 * 
 */
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
    SET_BIT((MEXTI -> PR), 3);
}
/**
 * @brief: Function that represents the interrupt service routine for EXTI4 Line
 * 
 */
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
    SET_BIT((MEXTI -> PR), 4);
}
/**
 * @brief: Function that represents the interrupt service routine for EXTI5 to EXTI9 Lines
 * 
 */
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
        SET_BIT((MEXTI -> PR), 5);
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
        SET_BIT((MEXTI -> PR), 6);
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
        SET_BIT((MEXTI -> PR), 7);
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
        SET_BIT((MEXTI -> PR), 8);
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
        SET_BIT((MEXTI -> PR), 9);
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function that represents the interrupt service routine for EXTI10 to EXTI15 Lines
 * 
 */
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
        SET_BIT((MEXTI -> PR), 10);
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
        SET_BIT((MEXTI -> PR), 11);
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
        SET_BIT((MEXTI -> PR), 12);
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
        SET_BIT((MEXTI -> PR), 13);
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
        SET_BIT((MEXTI -> PR), 14);
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
        SET_BIT((MEXTI -> PR), 15);
    }
    else
    {
        /*Do nothing*/
    }
}