/**
 * @file SCB_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-09-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _SCB_PRIVATE_H_
#define _SCB_PRIVATE_H_

#define SCB_BASE_ADDRESS                                0xE000ED00U

typedef struct SCB_Registers
{
    /*CPUID Base Register:
        -Contains the processor part number, version and implementation information
        -for more information about this register, please refer to STM32F103x Programming Manual Page 130
    */
    volatile uint32 CPUID;
    
    /*Interrupt Control and State Register:
        1) Provides:
            -Set-Pending bit for the Non-Maskable Interrupt (NMI) exception
            -Set Pending and Clear Pending bits for PendSV and SysTick Exceptions
        2) Indicates:
            -Exception number of the exception being executed
            -Whether there are preempted active exceptions
            -The exception number of the highest priority pending exception
            -Whether any interrupts are pending
        */
    volatile uint32 ICSR;
    
    /*Vector Table Offset Register:
        1) Using it, you can determine the offset of the vector table base from memory address 0x00
        2) Note that in order to do that, you have to allign the offset to the number of exception entries in the
            vector table "The minimum allignment is 128 words (512 bytes)".
                        (Table offset is put in bits 28:9)
        3) Bit 29 of this register determines whether the vector table is in the code or SRAM memory region:
            0 -----> Code
            1 -----> SRAM
    */
    volatile uint32 VTOR;
    
    /*Application Interrupt and Reset Control Register:
        1) Provides Priority Grouping Control for the Exception model, endian status for data accesses
            and reset control of the system
        2) Note that in order to write to this register, you must write 0x5FA to the VECTKEY field "Bits 31:16",
            otherwise, the processor ignores the write
    */
    volatile uint32 AIRCR;
    
    /*System Control Register:
        This Register Controls features of entry to and exit from low power state*/
    volatile uint32 SCR;
    
    /*Configuration and control register:
        This register controls entry to thread mode and enables:
        1) The handlers for NMI, hard fault and faults escalated by FAULTMASK to ignore bus faults
        2) Trapping of divide by zero and unaligned accesses
        3) Access to the STIR "NVIC Software Trigger Interrupt Register" by unprivileged software
    */
    volatile uint32 CCR;
    
    /*System Handler Priority Registers:
        1) They are used to set the priority level "0 --> 15" of the exception handlers that have 
            configurable priority
        2) They are Byte accessible
    */
    volatile uint8 SHPR[12];
    
    /*System Handler Control and State Register:
        -It enables the system handlers and indicates:
            1) The Pending Status of the bus fault, memory management fault and SVC exceptions.
            2) The active status of the system handlers.
        -If you disable a system handler and the corresponding fault occurs, the processor treats the
            fault as hard fault.
        -You can write to this register to change the pending or active status of system exceptions.
    */
    volatile uint32 SHCSR;
    
    /*Configurable Fault Status Register*/
    volatile uint32 CFSR;
    
    /*Hard Fault Status Register*/
    volatile uint32 HFSR;
    
    /*Memory Management Fault Address Register:
        1) Holds the address of the location that generated the memory management fault
        2) Note that the MMARVALID bit of the MMFSR must be set to 1 first 
    */
    volatile uint32 MMAR;
    
    /*Bus Fault Address Register:
        1) Holds the address of the location that generated the bus fault
        2) Note that the BFARVALID bit of the BFSR must be set to 1 first
    */
    volatile uint32 BFAR;
}SCB_RegDef_t;

#define SCB                                                 ((SCB_RegDef_t *) SCB_BASE_ADDRESS)

/************************Interrupt control and state register (SCB_ICSR) Bits******************************/

/**
 *  @brief Active Vector "9 bits": 
 *      Contains the active exception number
 *  @note: from the value obtained in these bits, you can identify the interrupt request number (IRQ)
 *  by simply subtracting 16 from this value. Then, you can use it to get the bit number in the interrupt clear-enable, set-enable, clear-pending,
 *  set-pending or priority registers
 */
#define SCB_ICSR_VECTACTIVE_START                           0
/**
 * @brief: Return to base level:
 *          Indicates whether there are preempted active exceptions
 * @retval 0: There are preempted active exceptions to execute
 * @retval 1: There are no active exceptions, or the currently executing exception is the
 *            only active exception
 */
#define SCB_ICSR_RETOBASE                                   11
/**
 * @brief: Pending vector "10 bits":
 *          Indicates the exception number of the highest priority enabled exception
 * @retval 0: No pending Exception.
 * @retval any other value: the exception number of the highest priority enabled exception.
 * 
 * @note: The value indicated by this field includes the effect of BASEPRI and FAULTMASK registers,
 *          but not any effect of the PRIMASK register.
 * 
 */
#define SCB_ICSR_VECTPENDING_START                          12
/**
 * @brief: Interrupt Pending Flag, excluding NMI and Faults.
 * 
 * @retval 0: Interrupt not pending
 * @retval 1: Interrupt Pending
 */
#define SCB_ICSR_ISRPENDING                                 22
/**
 * @brief: SysTick Exception Clear Pending bit
 * 
 * @note: This bit is write-only
 */
#define SCB_ICSR_PENDSTCLR                                  25
/**
 * @brief: SysTick Exception Set Pending Bit.
 * 
 */
#define SCB_ICSR_PENDSTSET                                  26
/**
 * @brief: PendSV Clear Pending Bit
 * 
 * @note: This bit is write-only
 */
#define SCB_ICSR_PENDSVCLR                                  27
/**
 * @brief: PendSV Set Pending Bit
 * 
 * @note: Writing 1 to this bit is the only way to set PendSV
 *        exception state to pending
 */
#define SCB_ICSR_PENDSVSET                                  28
/**
 * @brief: Non-Maskable Interrupt "NMI" Set Pending Bit
 * 
 * @note: As NMI is the highest priority exception, normally the processor enter
 *        the NMI exception handler as soon as it registers a write of 1 to this bit,
 *        and entering the handler clears this bit to 0
 * 
 * @note: A read of this bit by NMI exception handler returns 1 only if the NMI Signal 
 *        is reasserted while the processor is executing that handler
 */
#define SCB_ICSR_NMIPENDSET                                 31

/************************Application Interrupt & Reset Control Register (SCB_AIRCR) Bits******************************/

/**
 * @brief: System Reset Request Bit:
 *          Forces a large system reset of all major components except for debug
 * 
 */
#define SCB_AIRCR_SYSRESETREQ                               2
/**
 * @brief: Interrupt Priority Grouping Field "3 bits":
 *          This field determines the split of group priority from subpriority.
 * 
 */
#define SCB_AIRCR_PRIGROUP_START                            8
/**
 * @brief: Data Endianness Bit
 * 
 * @note: Read-only
 * @retval 0: Little-Endian
 */
#define SCB_AIRCR_ENDIANNESS                                15
/**
 * @brief: Register Key "16 bits":
 *          Reads as 0xFA05
 * @note: On Register Write, write 0x5FA to these bits, otherwise the write is
 *          ignored
 */
#define SCB_AIRCR_VECTKEY_START                             16

/************************System Control register (SCB_SCR) Bits******************************/

/**
 * @brief: Sleep on exit:
 *          1) Configures Sleep on exit when returning from handler mode to thread mode
 *                      "When the processor has finished interrupt"
 *          2) Setting this bit to 1 enables an interrupt driven application to avoid returning
 *              to an empty main application
 */
#define SCB_SCR_SLEEPONEXIT                                 1
/**
 * @brief: Controls whether the processor uses sleep or deep sleep as its low power mode
 *          (0 ---> Sleep)
 *          (1 ---> Deep Sleep)
 */
#define SCB_SCR_SLEEPDEEP                                   2
/**
 * @brief: Send Event on Pending Bit:
 *          1) When an event or interrupt enters pending state, the event signal wakes up the
 *              processor from WFE "Wait for event"
 *          2) If the processor is not waiting for an event, the event is registered and affects the next WFE
 *          3) The processor also wakes up on execution of an SEV "Send Event" Instruction or an external event.
 * 
 *          4) Writing 0 to this bit means that only enabled interrupts or events can wakeup the processor and disabled
 *              interrupts will be excluded.
 *          5) Writing 1 to this bit means that enabled events and all interrupts, including disabled interrupts, can wakeup
 *              the processor
 */
#define SCB_SCB_SEVEONPEND                                  4

/************************Configuration and Control Register (SCB_CCR) Bits******************************/

/**
 * @brief: This bit configures how the processor enters thread mode
 * 
 *         0 --> Processor can enter thread mode only when no exception is active
 *         1 --> Processor can enter thread mode from any level under the control of an 
 *                  EXC_RETURN value "Refer to Exception return in STM32F103x Programming Manual Page 38"
 */
#define SCB_CCR_NONBASETHRDENA                              0
/**
 * @brief: Enables Unprivileged software access to the STIR "NVIC Software Trigger Interrupt Register"
 * 
 */
#define SCB_CCR_USERSETMPEND                                1
/**
 * @brief: Enable Unaligned access trap
 *          1 --> Trap Unaligned half-word and word accesses
 * 
 * @note: If this bit is set to 1, an unaligned access generates a usage fault
 */
#define SCB_CCR_UNALIGN_TRP                                 3
/**
 * @brief: Enables Faulting or halting when the processor executes a division instruction with a 
 *          divisor of 0
 */
#define SCB_CCR_DIV_0_TRP                                   4
/**
 * @brief: 1) Enables Handlers with priority -1 or -2 to ignore data bus faults caused by load and store
 *              instructions.
 *         2) This applies to the hard fault, NMI and FAULTMASK escalated handlers.
 *         3) The normal use of this bit is to probe system devices and bridges to detect control path problems and
 *              fix them.
 * 
 * @warning: Set this bit to 1 only when the handler and its data are in absolutely safe memory.
 */
#define SCB_CCR_BFHFNMIGN                                   8
/**
 * @brief: Configures stack alignment on exception entry.
 *          1) On Exception Entry: Processor uses this bit to indicate the stack alignment
 *          2) On return from the exception: It uses this bit to restore the correct stack alignment
 * 
 *          0 ---> 4-Byte alligned
 *          1 ---> 8-Byte alligned
 */
#define SCB_CCR_STKALIGN                                    9



/************************System Handler Control and State Register (SCB_SHCSR) Bits******************************/

/*Memory Management Fault Exception Active Bit*/
#define SCB_SHCSR_MEMFAULTACT                               0
/*Bus Fault Exception Active Bit*/
#define SCB_SHCSR_BUSFAULTACT                               1
/*Usage Fault Exception Active Bit*/
#define SCB_SHCSR_USGFAULTACT                               3
/*SVC Call Active Bit*/
#define SCB_SHCSR_MEMFAULTACT                               7
/*Debug Monitor Active Bit*/
#define SCB_SHCSR_MONITORACT                                8
/*PendSV Exception Active Bit*/
#define SCB_SHCSR_PENDSVACT                                 10
/*SysTick Exception Active Bit*/
#define SCB_SHCSR_SYSTICKACT                                11
/*Usage Fault Exception Pending Bit*/
#define SCB_SHCSR_USGFAULTPENDED                            12
/*Memory Management Fault Exception Pending Bit*/
#define SCB_SHCSR_MEMFAULTPENDED                            13
/*Bus Fault Exception Pending Bit*/
#define SCB_SHCSR_BUSFAULTPENDED                            14
/*SVC Call Pending Bit*/
#define SCB_SHCSR_SVCALLPENDED                              15
/*Memory Management Fault Enable Bit*/
#define SCB_SHCSR_MEMFAULTENA                               16
/*Bus Fault Enable Bit*/
#define SCB_SHCSR_BUSFAULTENA                               17
/*Usage Fault Enable Bit*/
#define SCB_SHCSR_USGFAULTENA                               18
#endif /*_SCB_PRIVATE_H_*/