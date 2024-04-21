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
#include "../NVIC/NVIC_Config.h"
#include "../NVIC/NVIC_Interface.h"
#include "../NVIC/NVIC_Private.h"


///**
// * @brief: Static Global Variable to Save the Priority Grouping Type In
// *          (I had to make this variable so that when user calls MNVIC_u8SetPriorityGrouping function
// *              I have to save the value that the user has entered in order to use it in set priority
// *              function)
// * 
// */
//static volatile u32 glob_u32PriorityGrouping = NVIC_PRIORITY_GROUP_4_SUB_0;
/**
 * @brief: Function to enable interrupt of a peripheral
 * 
 * @param Copy_u8InterruptNumber: ID of the peripheral
 * @return Std_ReturnType
 * @retval E_OK: Peripheral Interrupt is enabled successfully
 * @retval E_NOT_OK: Peripheral Interrupt is not enabled 
 */
Std_ReturnType MNVIC_u8EnableInterrupt(NVIC_InterruptType Copy_u32InterruptNumber)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    if(Copy_u32InterruptNumber < 32)
    {
        SET_BIT((NVIC -> ISER[0]), Copy_u32InterruptNumber);
        Loc_u8FuncStatus = E_OK;
    }
    else if(Copy_u32InterruptNumber < NVIC_NUMBER_OF_INTERRUPTS)
    {
        Copy_u32InterruptNumber -= 32;
        SET_BIT((NVIC -> ISER[1]), Copy_u32InterruptNumber);
        Loc_u8FuncStatus = E_OK;
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}
/**
 * @brief: Function to disable interrupt of a peripheral
 * 
 * @param Copy_u8InterruptNumber: ID of the peripheral
 * @return Std_ReturnType
 * @retval E_OK: Peripheral Interrupt is disabled successfully
 * @retval E_NOT_OK: Peripheral Interrupt is not disabled 
 */
Std_ReturnType MNVIC_u8DisableInterrupt(NVIC_InterruptType Copy_u32InterruptNumber)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    if(Copy_u32InterruptNumber < 32)
    {
        SET_BIT((NVIC -> ICER[0]), Copy_u32InterruptNumber);
        Loc_u8FuncStatus = E_OK;
    }
    else if(Copy_u32InterruptNumber < NVIC_NUMBER_OF_INTERRUPTS)
    {
        Copy_u32InterruptNumber -= 32;
        SET_BIT((NVIC -> ICER[1]), Copy_u32InterruptNumber);
        Loc_u8FuncStatus = E_OK;
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}
/**
 * @brief: Function to set pending flag of interrupt of a peripheral
 *      "This function can be used to fire an interrupt without having to wait for the actual interrupt to happen"
 * @param Copy_u8InterruptNumber: ID of the peripheral
 * @return Std_ReturnType
 * @retval E_OK: Peripheral Interrupt Pending Flag is set successfully
 * @retval E_NOT_OK: Peripheral Interrupt Pending Flag is not set 
 */
Std_ReturnType MNVIC_u8SetPendingFlag(NVIC_InterruptType Copy_u32InterruptNumber)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    if(Copy_u32InterruptNumber < 32)
    {
        SET_BIT((NVIC -> ISPR[0]), Copy_u32InterruptNumber);
        Loc_u8FuncStatus = E_OK;
    }
    else if(Copy_u32InterruptNumber < NVIC_NUMBER_OF_INTERRUPTS)
    {
        Copy_u32InterruptNumber -= 32;
        SET_BIT((NVIC -> ISPR[1]), Copy_u32InterruptNumber);
        Loc_u8FuncStatus = E_OK;
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}
/**
 * @brief: Function to clear pending flag of interrupt of a peripheral
 * 
 * @param Copy_u8InterruptNumber: ID of the peripheral
 * @return Std_ReturnType
 * @retval E_OK: Peripheral Interrupt Pending Flag is cleared successfully
 * @retval E_NOT_OK: Peripheral Interrupt Pending Flag is not cleared 
 */
Std_ReturnType MNVIC_u8ClearPendingFlag(NVIC_InterruptType Copy_u32InterruptNumber)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    if(Copy_u32InterruptNumber < 32)
    {
        SET_BIT((NVIC -> ICPR[0]), Copy_u32InterruptNumber);
        Loc_u8FuncStatus = E_OK;
    }
    else if(Copy_u32InterruptNumber < NVIC_NUMBER_OF_INTERRUPTS)
    {
        Copy_u32InterruptNumber -= 32;
        SET_BIT((NVIC -> ICPR[1]), Copy_u32InterruptNumber);
        Loc_u8FuncStatus = E_OK;
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}
/**
 * @brief: Function to get the status of active flag of an interrupt
 * 
 * @param Copy_u32InterruptNumber: ID of the interrupt
 * @param P_u8ActiveFlag: Pointer to send the status of active flag in (High or low)
 * @return Std_ReturnType
 * @retval E_OK: Peripheral Interrupt Active Flag Status is read successfully
 * @retval E_NOT_OK: Peripheral Interrupt Active Flag Status is not read  
 */
Std_ReturnType MNVIC_u8GetActiveFlag(NVIC_InterruptType Copy_u32InterruptNumber, uint8* P_u8ActiveFlag)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    if(P_u8ActiveFlag != 0)
    {
        if(Copy_u32InterruptNumber < 32)
        {
            *P_u8ActiveFlag = GET_BIT((NVIC -> IABR[0]), Copy_u32InterruptNumber);
            Loc_u8FuncStatus = E_OK;
        }
        else if(Copy_u32InterruptNumber < NVIC_NUMBER_OF_INTERRUPTS)
        {
            Copy_u32InterruptNumber -= 32;
            *P_u8ActiveFlag = GET_BIT((NVIC -> IABR[1]), Copy_u32InterruptNumber);
            Loc_u8FuncStatus = E_OK;
        }
        else
        {
            Loc_u8FuncStatus = E_NOT_OK;
        }
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}

/**
 * @brief: Function to set the priority of an interrupt
 * 
 * @param Copy_u32InterruptNumber: ID of the interrupt
 * @param Copy_u8GroupPriority: Group Priority of the interrupt
 * @param Copy_u8SubGroupPriority: Sub priority of the interrupt
 * @return Std_ReturnType
 * @retval E_OK: Priority has been set successfully
 * @retval E_NOT_OK: Priority has not been set  
 */
Std_ReturnType MNVIC_u8SetInterruptPriority(NVIC_InterruptType Copy_u32InterruptNumber, uint8 Copy_u8GroupPriority, uint8 Copy_u8SubGroupPriority)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    if(Copy_u32InterruptNumber < NVIC_NUMBER_OF_INTERRUPTS)
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
        uint16 Loc_u16AIRCRPriorityGroupVal = (uint16)(SCB_AIRCR & (0xFFFF));
        uint8 Loc_u8PriorityValue = 0;

        switch(Loc_u16AIRCRPriorityGroupVal)
        {
            case NVIC_PRIORITY_GROUP_4_SUB_0:
            {
                Loc_u8PriorityValue = (Copy_u8GroupPriority << 4);
                NVIC -> IPR[Copy_u32InterruptNumber] = Loc_u8PriorityValue;
                break;
            }
            case NVIC_PRIORITY_GROUP_3_SUB_1:
            case NVIC_PRIORITY_GROUP_2_SUB_2:
            case NVIC_PRIORITY_GROUP_1_SUB_3:
            {
                Loc_u8PriorityValue = ((Copy_u8SubGroupPriority) | (Copy_u8GroupPriority << ((Loc_u16AIRCRPriorityGroupVal - (uint16)NVIC_PRIORITY_GROUP_4_SUB_0) / 0x100)));
                NVIC -> IPR[Copy_u32InterruptNumber] = Loc_u8PriorityValue << 4;
                break;
            }
            case NVIC_PRIORITY_GROUP_0_SUB_4:
            {
                Loc_u8PriorityValue = (Copy_u8SubGroupPriority << 4);
                NVIC -> IPR[Copy_u32InterruptNumber] = Loc_u8PriorityValue;
                break;
            }
            default:
            {
                Loc_u8FuncStatus = E_NOT_OK;
                break;
            }
        }

    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}
