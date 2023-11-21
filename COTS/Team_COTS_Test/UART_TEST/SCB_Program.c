#include "Std_Types.h"
#include "BIT_MATH.h"

#include "SCB_Private.h"
#include "SCB_Interface.h"
#include "SCB_Config.h"

/**
 * @brief: Function to Force a large system reset of all major components except for debug
 * 
 */
void MSCB_voidSystemReset(void)
{
    /*Unlocking the write on AIRCR register and setting the system reset request bit*/
    SCB -> AIRCR |= (0x5FA >> SCB_AIRCR_VECTKEY_START) | (1 << SCB_AIRCR_SYSRESETREQ);

    /*We have to wait a little while the system reset is being processed*/
    for(;;);
}
/**
 * @brief: Function to set the interrupt priority grouping
 * 
 * @param Copy_uint32PriorityGrouping: Interrupt priority grouping
 * @return Std_ReturnType
 * @retval E_OK: Priority Grouping has been set
 * @retval E_NOT_OK: Priority Grouping has not been set   
 */
Std_ReturnType MSCB_uint8SetPriorityGrouping(uint32 Copy_uint32PriorityGrouping)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    switch(Copy_uint32PriorityGrouping)
    {
        case SCB_PRIORITY_GROUP_0_SUB_4:
        case SCB_PRIORITY_GROUP_1_SUB_3:
        case SCB_PRIORITY_GROUP_2_SUB_2:
        case SCB_PRIORITY_GROUP_3_SUB_1:
        case SCB_PRIORITY_GROUP_4_SUB_0:
        {
            SCB -> AIRCR = Copy_uint32PriorityGrouping;
            Loc_uint8FuncStatus = E_OK;
            break;
        }
        default:
        {
            Loc_uint8FuncStatus = E_NOT_OK;
            break;
        }
    }
    return Loc_uint8FuncStatus;
}

/**
 * @brief: Function to set the NMI Interrupt Pending flag
 * 
 * @note: There is no function for clearing NMI Pending flag as it is automatically cleared
 *          as processor enters the Handler of Non-Maskable Interrupt
 * 
 * @return Std_ReturnType
 * @retval E_OK: NMI Pending Flag is successfully set
 * @retval E_NOT_OK: NMI Pending Flag is not set
 */
Std_ReturnType MSCB_uint8SetNMIPendingFlag(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    SET_BIT(SCB -> ICSR, SCB_ICSR_NMIPENDSET);
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to set the SysTick Interrupt Pending Flag
 * 
 * @return Std_ReturnType
 * @retval E_OK: SysTick Interrupt Pending Flag is successfully set
 * @retval E_NOT_OK: SysTick Interrupt Pending Flag is not set
 */
Std_ReturnType MSCB_uint8SetSysTickPendingFlag(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    SET_BIT(SCB -> ICSR, SCB_ICSR_PENDSTSET);
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to clear the SysTick Interrupt Pending Flag
 * 
 * @return Std_ReturnType 
 * @retval E_OK: SysTick Interrupt Pending Flag is successfully cleared
 * @retval E_NOT_OK: SysTick Interrupt Pending Flag is not cleared
 */
Std_ReturnType MSCB_uint8ClearSysTickPendingFlag(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    SET_BIT(SCB -> ICSR, SCB_ICSR_PENDSTCLR);
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to set the PendSV Interrupt Pending Flag
 * 
 * @return Std_ReturnType 
 * @retval E_OK: PendSV Interrupt Pending Flag is successfully set
 * @retval E_NOT_OK: PendSV Interrupt Pending Flag is not set
 */
Std_ReturnType MSCB_uint8SetPendSVPendingFlag(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    SET_BIT(SCB -> ICSR, SCB_ICSR_PENDSVSET);
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to clear the PendSV Interrupt Pending Flag
 * 
 * @return Std_ReturnType 
 * @retval E_OK: PendSV Interrupt Pending Flag is successfully cleared
 * @retval E_NOT_OK: PendSV Interrupt Pending Flag is not cleared
 */
Std_ReturnType MSCB_uint8ClearPendSVPendingFlag(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    SET_BIT(SCB -> ICSR, SCB_ICSR_PENDSVCLR);
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to get the Interrupt Request Number of the interrupt currently executing
 *        
 * @param P_uint8ActiveIRQNum: Pointer to pass the IRQ number in it 
 * 
 * @return Std_ReturnType 
 * @retval E_OK: Active IRQ Number is successfully obtained
 * @retval E_NOT_OK: Active IRQ number is not obtained
 */
Std_ReturnType MSCB_uint8GetActiveIRQ(uint8* P_uint8ActiveIRQNum)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_uint8ActiveIRQNum != NULL_PTR)
    {
        uint16 Loc_uint16ExceptionNum = (SCB -> ICSR) & ((0b111111111) << SCB_ICSR_VECTACTIVE_START);
        *P_uint8ActiveIRQNum = (uint8)Loc_uint16ExceptionNum - 16;
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to set the priority of system handlers
 *          -Memory Management Fault
 *          -Bus Fault
 *          -Usage Fault
 *          -SV Call
 *          -PendSV
 *          -SysTick
 * 
 * @param Copy_uint8SystemHandler: Exception number of System Handler
 * @param Copy_uint8SysHandlerPriority: Priority of System Handler to be set
 * 
 * @return Std_ReturnType
 * @retval E_OK: System Handler Priority has been set
 * @retval E_NOT_OK: System Handler Priority has not been set   
 */
Std_ReturnType MSCB_uint8SetSystemHandlerPriority(uint8 Copy_uint8SystemHandler, uint8 Copy_uint8SysHandlerPriority)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(Copy_uint8SysHandlerPriority < 16)
    {
        switch(Copy_uint8SystemHandler)
        {
            case SCB_SHPR_BUS_FAULT:
            case SCB_SHPR_MEM_MANAGEMENT_FAULT:
            case SCB_SHPR_PENDSV:
            case SCB_SHPR_SVCALL:
            case SCB_SHPR_SYSTICK:
            case SCB_SHPR_USAGE_FAULT:
            {
                SCB -> SHPR[Copy_uint8SystemHandler] = (Copy_uint8SysHandlerPriority << 4);
                Loc_uint8FuncStatus = E_OK;
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
/**
 * @brief: Function to enable the Memory Management Fault
 * 
 * @note: If not enabled, the processor will consider the memory management fault as hard fault 
 * 
 * @return Std_ReturnType
 * @retval E_OK: Memory Management Fault is successfully enabled
 * @retval E_NOT_OK: Memory Management Fault is not enabled
 */
Std_ReturnType MSCB_uint8EnableMemFault(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    SET_BIT(SCB -> SHCSR, SCB_SHCSR_MEMFAULTENA);
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to enable the Bus Fault
 * 
 * @note: If not enabled, the processor will consider the Bus fault as hard fault 
 * 
 * @return Std_ReturnType
 * @retval E_OK: Bus Fault is successfully enabled
 * @retval E_NOT_OK: Bus Fault is not enabled
 */
Std_ReturnType MSCB_uint8EnableBusFault(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    SET_BIT(SCB -> SHCSR, SCB_SHCSR_BUSFAULTENA);
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to enable the Usage Fault
 * 
 * @note: If not enabled, the processor will consider the Usage fault as hard fault 
 * 
 * @return Std_ReturnType
 * @retval E_OK: Usage Fault is successfully enabled
 * @retval E_NOT_OK: Usage Fault is not enabled
 */
Std_ReturnType MSCB_uint8EnableUsageFault(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    SET_BIT(SCB -> SHCSR, SCB_SHCSR_USGFAULTENA);
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}