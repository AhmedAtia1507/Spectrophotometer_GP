/**
 * @file SCB_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-09-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _SCB_INTERFACE_H_
#define _SCB_INTERFACE_H_

#define SCB_PRIORITY_GROUP_4_SUB_0             0x05FA0300
#define SCB_PRIORITY_GROUP_3_SUB_1             0x05FA0400
#define SCB_PRIORITY_GROUP_2_SUB_2             0x05FA0500
#define SCB_PRIORITY_GROUP_1_SUB_3             0x05FA0600
#define SCB_PRIORITY_GROUP_0_SUB_4             0x05FA0700

/************************System Handler Priority Registers (SCB_SHPRx) register numbers******************************/

#define SCB_SHPR_MEM_MANAGEMENT_FAULT                   0
#define SCB_SHPR_BUS_FAULT                              1
#define SCB_SHPR_USAGE_FAULT                            2
#define SCB_SHPR_SVCALL                                 7
#define SCB_SHPR_PENDSV                                 10
#define SCB_SHPR_SYSTICK                                11
/**
 * @brief: Function to Force a large system reset of all major components except for debug
 * 
 */
void MSCB_SystemReset(void);
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
Std_ReturnType MSCB_SetNMIPendingFlag(void);
/**
 * @brief: Function to set the SysTick Interrupt Pending Flag
 * 
 * @return Std_ReturnType
 * @retval E_OK: SysTick Interrupt Pending Flag is successfully set
 * @retval E_NOT_OK: SysTick Interrupt Pending Flag is not set
 */
Std_ReturnType MSCB_SetSysTickPendingFlag(void);
/**
 * @brief: Function to clear the SysTick Interrupt Pending Flag
 * 
 * @return Std_ReturnType 
 * @retval E_OK: SysTick Interrupt Pending Flag is successfully cleared
 * @retval E_NOT_OK: SysTick Interrupt Pending Flag is not cleared
 */
Std_ReturnType MSCB_ClearSysTickPendingFlag(void);
/**
 * @brief: Function to set the PendSV Interrupt Pending Flag
 * 
 * @return Std_ReturnType 
 * @retval E_OK: PendSV Interrupt Pending Flag is successfully set
 * @retval E_NOT_OK: PendSV Interrupt Pending Flag is not set
 */
Std_ReturnType MSCB_SetPendSVPendingFlag(void);
/**
 * @brief: Function to clear the PendSV Interrupt Pending Flag
 * 
 * @return Std_ReturnType 
 * @retval E_OK: PendSV Interrupt Pending Flag is successfully cleared
 * @retval E_NOT_OK: PendSV Interrupt Pending Flag is not cleared
 */
Std_ReturnType MSCB_ClearPendSVPendingFlag(void);
/**
 * @brief: Function to get the Interrupt Request Number of the interrupt currently executing
 *        
 * @param P_uint8ActiveIRQNum: Pointer to pass the IRQ number in it 
 * 
 * @return Std_ReturnType 
 * @retval E_OK: Active IRQ Number is successfully obtained
 * @retval E_NOT_OK: Active IRQ number is not obtained
 */
Std_ReturnType MSCB_GetActiveIRQ(uint8* P_uint8ActiveIRQNum);
/**
 * @brief: Function to set the interrupt priority grouping
 * 
 * @param Copy_uint32PriorityGrouping: Interrupt priority grouping
 * @return Std_ReturnType
 * @retval E_OK: Priority Grouping has been set
 * @retval E_NOT_OK: Priority Grouping has not been set   
 */
Std_ReturnType MSCB_SetPriorityGrouping(uint32 Copy_uint32PriorityGrouping);
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
Std_ReturnType MSCB_SetSystemHandlerPriority(uint8 Copy_uint8SystemHandler, uint8 Copy_uint8SysHandlerPriority);
/**
 * @brief: Function to enable the Memory Management Fault
 * 
 * @note: If not enabled, the processor will consider the memory management fault as hard fault 
 * 
 * @return Std_ReturnType
 * @retval E_OK: Memory Management Fault is successfully enabled
 * @retval E_NOT_OK: Memory Management Fault is not enabled
 */
Std_ReturnType MSCB_EnableMemFault(void);
/**
 * @brief: Function to enable the Bus Fault
 * 
 * @note: If not enabled, the processor will consider the Bus fault as hard fault 
 * 
 * @return Std_ReturnType
 * @retval E_OK: Bus Fault is successfully enabled
 * @retval E_NOT_OK: Bus Fault is not enabled
 */
Std_ReturnType MSCB_EnableBusFault(void);
/**
 * @brief: Function to enable the Usage Fault
 * 
 * @note: If not enabled, the processor will consider the Usage fault as hard fault 
 * 
 * @return Std_ReturnType
 * @retval E_OK: Usage Fault is successfully enabled
 * @retval E_NOT_OK: Usage Fault is not enabled
 */
Std_ReturnType MSCB_EnableUsageFault(void);
#endif /*_SCB_INTERFACE_H_*/