/**
 * @file NVIC_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: C file to Implement functions used to control NVIC Peripheral
 * @version 1.0
 * @date 2023-09-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "BIT_MATH.h"
#include "Std_Types.h"

#include "NVIC_Private.h"
#include "NVIC_Interface.h"
#include "NVIC_Config.h"

/**
 * @brief: Function to enable interrupt of a peripheral
 * 
 * @param Copy_uint8InterruptNumber: ID of the peripheral
 * @return Std_ReturnType
 * @retval E_OK: Peripheral Interrupt is enabled successfully
 * @retval E_NOT_OK: Peripheral Interrupt is not enabled 
 */
Std_ReturnType MNVIC_EnableInterrupt(MNVIC_InterruptType Copy_uint32InterruptNumber)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(Copy_uint32InterruptNumber < 32)
    {
        SET_BIT((NVIC -> ISER[0]), Copy_uint32InterruptNumber);
        Loc_uint8FuncStatus = E_OK;
    }
    else if(Copy_uint32InterruptNumber < NVIC_NUMBER_OF_INTERRUPTS)
    {
        Copy_uint32InterruptNumber -= 32;
        SET_BIT((NVIC -> ISER[1]), Copy_uint32InterruptNumber);
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to disable interrupt of a peripheral
 * 
 * @param Copy_uint8InterruptNumber: ID of the peripheral
 * @return Std_ReturnType
 * @retval E_OK: Peripheral Interrupt is disabled successfully
 * @retval E_NOT_OK: Peripheral Interrupt is not disabled 
 */
Std_ReturnType MNVIC_DisableInterrupt(MNVIC_InterruptType Copy_uint32InterruptNumber)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(Copy_uint32InterruptNumber < 32)
    {
        SET_BIT((NVIC -> ICER[0]), Copy_uint32InterruptNumber);
        Loc_uint8FuncStatus = E_OK;
    }
    else if(Copy_uint32InterruptNumber < NVIC_NUMBER_OF_INTERRUPTS)
    {
        Copy_uint32InterruptNumber -= 32;
        SET_BIT((NVIC -> ICER[1]), Copy_uint32InterruptNumber);
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to set pending flag of interrupt of a peripheral
 *      "This function can be used to fire an interrupt without having to wait for the actual interrupt to happen"
 * @param Copy_uint8InterruptNumber: ID of the peripheral
 * @return Std_ReturnType
 * @retval E_OK: Peripheral Interrupt Pending Flag is set successfully
 * @retval E_NOT_OK: Peripheral Interrupt Pending Flag is not set 
 */
Std_ReturnType MNVIC_SetPendingFlag(MNVIC_InterruptType Copy_uint32InterruptNumber)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(Copy_uint32InterruptNumber < 32)
    {
        SET_BIT((NVIC -> ISPR[0]), Copy_uint32InterruptNumber);
        Loc_uint8FuncStatus = E_OK;
    }
    else if(Copy_uint32InterruptNumber < NVIC_NUMBER_OF_INTERRUPTS)
    {
        Copy_uint32InterruptNumber -= 32;
        SET_BIT((NVIC -> ISPR[1]), Copy_uint32InterruptNumber);
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to clear pending flag of interrupt of a peripheral
 * 
 * @param Copy_uint8InterruptNumber: ID of the peripheral
 * @return Std_ReturnType
 * @retval E_OK: Peripheral Interrupt Pending Flag is cleared successfully
 * @retval E_NOT_OK: Peripheral Interrupt Pending Flag is not cleared 
 */
Std_ReturnType MNVIC_ClearPendingFlag(MNVIC_InterruptType Copy_uint32InterruptNumber)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(Copy_uint32InterruptNumber < 32)
    {
        SET_BIT((NVIC -> ICPR[0]), Copy_uint32InterruptNumber);
        Loc_uint8FuncStatus = E_OK;
    }
    else if(Copy_uint32InterruptNumber < NVIC_NUMBER_OF_INTERRUPTS)
    {
        Copy_uint32InterruptNumber -= 32;
        SET_BIT((NVIC -> ICPR[1]), Copy_uint32InterruptNumber);
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to get the status of active flag of an interrupt
 * 
 * @param Copy_uint32InterruptNumber: ID of the interrupt
 * @param P_uint8ActiveFlag: Pointer to send the status of active flag in (High or low)
 * @return Std_ReturnType
 * @retval E_OK: Peripheral Interrupt Active Flag Status is read successfully
 * @retval E_NOT_OK: Peripheral Interrupt Active Flag Status is not read  
 */
Std_ReturnType MNVIC_GetActiveFlag(MNVIC_InterruptType Copy_uint32InterruptNumber, uint8* P_uint8ActiveFlag)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_uint8ActiveFlag != NULL_PTR)
    {
        if(Copy_uint32InterruptNumber < 32)
        {
            *P_uint8ActiveFlag = GET_BIT((NVIC -> IABR[0]), Copy_uint32InterruptNumber);
            Loc_uint8FuncStatus = E_OK;
        }
        else if(Copy_uint32InterruptNumber < NVIC_NUMBER_OF_INTERRUPTS)
        {
            Copy_uint32InterruptNumber -= 32;
            *P_uint8ActiveFlag = GET_BIT((NVIC -> IABR[1]), Copy_uint32InterruptNumber);
            Loc_uint8FuncStatus = E_OK;
        }
        else
        {
            Loc_uint8FuncStatus = E_NOT_OK;
        }
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}

/**
 * @brief: Function to set the priority of an interrupt
 * 
 * @param Copy_uint32InterruptNumber: ID of the interrupt
 * @param Copy_uint8GroupPriority: Group Priority of the interrupt
 * @param Copy_uint8SubGroupPriority: Sub priority of the interrupt
 * 
 * @return Std_ReturnType
 * @retval E_OK: Priority has been set successfully
 * @retval E_NOT_OK: Priority has not been set
 * 
 * @warning: In order for grouping to be successfully set, you have to use MSCB_uint8SetPriorityGrouping
 *          to set the shape of the priority grouping, otherwise the priority will not be set  
 * 
 */
Std_ReturnType MNVIC_SetInterruptPriority(MNVIC_InterruptType Copy_uint32InterruptNumber, uint8 Copy_uint8GroupPriority, uint8 Copy_uint8SubGroupPriority)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(Copy_uint32InterruptNumber < NVIC_NUMBER_OF_INTERRUPTS)
    {
        /*
            In order to set the priority of interrupt:
                In the interrupt priority register that corresponds to the interrupt number entered to this function,
                    Set the interrupt priority and subpriority according to grouping style set

                Note that in the interrupt priority register, the least significant 4 bits 
                    are reserved "You Can't write on them", so you have only the most significant 4 bits to write on

                                             -----------------------------------
                                            |     Priority    ||||||||||||||||||                 
                                             -----------------------------------
        */
        uint32 Loc_uint32AIRCRValue = MSCB_AIRCR;
        uint16 Loc_uint16AIRCRPriorityGroupVal = Loc_uint32AIRCRValue & 0xFFFF;
        uint8 Loc_uint8PriorityValue = 0;

        switch(Loc_uint16AIRCRPriorityGroupVal)
        {
            case MNVIC_PRIORITY_GROUP_4_SUB_0:
            {
                Loc_uint8PriorityValue = (Copy_uint8GroupPriority << 4);
                NVIC -> IPR[Copy_uint32InterruptNumber] = Loc_uint8PriorityValue;
                break;
            }
            case MNVIC_PRIORITY_GROUP_3_SUB_1:
            case MNVIC_PRIORITY_GROUP_2_SUB_2:
            case MNVIC_PRIORITY_GROUP_1_SUB_3:
            {
                Loc_uint8PriorityValue = ((Copy_uint8SubGroupPriority) | (Copy_uint8GroupPriority << ((Loc_uint16AIRCRPriorityGroupVal - (uint16)MNVIC_PRIORITY_GROUP_4_SUB_0) / 0x100)));
                NVIC -> IPR[Copy_uint32InterruptNumber] = Loc_uint8PriorityValue << 4;
                break;
            }
            case MNVIC_PRIORITY_GROUP_0_SUB_4:
            {
                Loc_uint8PriorityValue = (Copy_uint8SubGroupPriority << 4);
                NVIC -> IPR[Copy_uint32InterruptNumber] = Loc_uint8PriorityValue;
                break;
            }
            default:
            {
                Loc_uint8FuncStatus = E_NOT_OK;
                break;
            }
        }

    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
