/**
 * @file NVIC_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: Header file to:
 *          1) define memory mapping for Nested Vectored Interrupt Controller Registers
 *          2) Define Macros for choices of pre-build configurations for NVIC Peripheral
 * @version 1.0
 * @date 2023-09-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _NVIC_PRIVATE_H_
#define _NVIC_PRIVATE_H_

/**
 * @brief: Structure to define registers in NVIC Peripheral
 * 
 */
typedef struct MNVIC_Registers
{
    /*
        Interrupt Set Enable Register:
        1) Each bit in these registers corresponds to a specific interrupt.
        2) Each interrupt has a number specified at vector table "Refer to STM32F10x Register Description Page 204"
        3) According to CMSIS Mapping, the interrupt set enable registers are made as 
            array of registers of type uint32:
            -NVIC_ISER0 ---> Can Enable Interrupts whose numbers from (0 --> 31)
            -NVIC_ISER1 ---> Can Enable Interrupts whose numbers from (32 --> 63)
            -NVIC_ISER2 ---> Can Enable Interrupts whose numbers from (64 --> 67)
    */
    volatile uint32 ISER[3U];
    volatile uint32 reserved_1[29U];

    /*
        Interrupt Clear Enable Register:
        1) Each bit in these registers corresponds to a specific interrupt.
        2) Each interrupt has a number specified at vector table "Refer to STM32F10x Register Description Page 204"
        3) According to CMSIS Mapping, the interrupt clear enable registers are made as 
            array of registers of type uint32:
            -NVIC_ICER0 ---> Can Disable Interrupts whose numbers from (0 --> 31)
            -NVIC_ICER1 ---> Can Disable Interrupts whose numbers from (32 --> 63)
            -NVIC_ICER2 ---> Can Disable Interrupts whose numbers from (64 --> 67)
    */
    volatile uint32 ICER[3U];
    volatile uint32 reserved_2[29U];

    /*
        Interrupt Set Pending Register:
        1) Each bit in these registers corresponds to a specific interrupt.
        2) Each interrupt has a number specified at vector table "Refer to STM32F10x Register Description Page 204"
        3) According to CMSIS Mapping, the interrupt set pending registers are made as 
            array of registers of type uint32:
            -NVIC_ISPR0 ---> Can Set the pending flag for Interrupts whose numbers from (0 --> 31)
            -NVIC_ISPR1 ---> Can Set the pending flag for Interrupts whose numbers from (32 --> 63)
            -NVIC_ISPR2 ---> Can Set the pending flag for Interrupts whose numbers from (64 --> 67)
    */
    volatile uint32 ISPR[3U];
    volatile uint32 reserved_3[29U];

    /*
        Interrupt Clear Pending Register:
        1) Each bit in these registers corresponds to a specific interrupt.
        2) Each interrupt has a number specified at vector table "Refer to STM32F10x Register Description Page 204"
        3) According to CMSIS Mapping, the interrupt clear pending registers are made as 
            array of registers of type uint32:
            -NVIC_ICPR0 ---> Can Clear the pending flag for Interrupts whose numbers from (0 --> 31)
            -NVIC_ICPR1 ---> Can Clear the pending flag for Interrupts whose numbers from (32 --> 63)
            -NVIC_ICPR2 ---> Can Clear the pending flag for Interrupts whose numbers from (64 --> 67)
    */
    volatile uint32 ICPR[3U];
    volatile uint32 reserved_4[29U];

    /*
        Interrupt Active Bit Register:
        1) Each bit in these registers corresponds to a specific interrupt.
        2) Each interrupt has a number specified at vector table "Refer to STM32F10x Register Description Page 204"
        3) According to CMSIS Mapping, the interrupt active bit registers are made as 
            array of registers of type uint32:
            -NVIC_IABR0 ---> User Can read the active flag for Interrupts whose numbers from (0 --> 31)
            -NVIC_IABR1 ---> User Can read the active flag for Interrupts whose numbers from (32 --> 63)
            -NVIC_IABR2 ---> User Can read the active flag for Interrupts whose numbers from (64 --> 67)
        
        "Active Flag is high --> means that the interrupt service routine of this interrupt is currently running"
    */
    volatile uint32 IABR[3U];
    volatile uint32 reserved_5[61U];

    /*
        Interrupt Priority Register:
        1) This register is divided into 4 blocks 
            "Each Block has the size of 1 byte and corresponds to the priority of an interrupt"
        2) As there is ,in general, 81 interrupts in STM32, an array of 21 registers is created to hold the priorities
            of these interrupts such as each register contains the priorities of 4 interrupts:
            -NVIC_IPR0 --> Contains the priorities of interrupts from (0 --> 3)
            -NVIC_IPR1 --> Contains the priorities of interrupts from (4 --> 7)
            -NVIC_IPR2 --> Contains the priorities of interrupts from (8 --> 11)
            -NVIC_IPR3 --> Contains the priorities of interrupts from (12 --> 15)
            -NVIC_IPR4 --> Contains the priorities of interrupts from (16 --> 19)
            -NVIC_IPR5 --> Contains the priorities of interrupts from (20 --> 23)
            -NVIC_IPR6 --> Contains the priorities of interrupts from (24 --> 27)
            -NVIC_IPR7 --> Contains the priorities of interrupts from (28 --> 31)
            -NVIC_IPR8 --> Contains the priorities of interrupts from (32 --> 35)
            -NVIC_IPR9 --> Contains the priorities of interrupts from (36 --> 39)
            -NVIC_IPR10 --> Contains the priorities of interrupts from (40 --> 43)
            -NVIC_IPR11 --> Contains the priorities of interrupts from (44 --> 47)
            -NVIC_IPR12 --> Contains the priorities of interrupts from (48 --> 51)
            -NVIC_IPR13 --> Contains the priorities of interrupts from (52 --> 55)
            -NVIC_IPR14 --> Contains the priorities of interrupts from (56 --> 59)
            -NVIC_IPR15 --> Contains the priorities of interrupts from (60 --> 63)
            -NVIC_IPR16 --> Contains the priorities of interrupts from (64 --> 67)
            -NVIC_IPR17 --> Contains the priorities of interrupts from (68 --> 71)
            -NVIC_IPR18 --> Contains the priorities of interrupts from (72 --> 75)
            -NVIC_IPR19 --> Contains the priorities of interrupts from (76 --> 79)
            -NVIC_IPR20 --> Contains the priorities of interrupt (80)

                    -----------------------------------------------------------------------------------
            IPR0    |         IP[3]      |          IP[2]     |         IP[1]      |      IP[0]       |
                    ----------------------------------------------------------------------------------

        3) For Simplicity, as these registers are stored in memory consequently, instead of defining 21 registers of
        size 4 bytes, we will define 84 registers of size 1 byte in order to access interrupt priority of interrupt
        of our choice directly 
    */
    volatile uint8 IPR[84];
    volatile uint32 reserved_6[695U];

    /*Software Trigger Interrupt Register*/
    volatile uint32 STIR;
} MNVIC_TypeDef;

#define MNVIC_BASE_ADDRESS                              0xE000E100U
#define MSCB_BASE_ADDRESS                               0xE000ED00U

#define NVIC                                            ((MNVIC_TypeDef *)MNVIC_BASE_ADDRESS)





/*Application Interrupt and Reset control Register*/
#define MSCB_AIRCR                                      (*(volatile uint32*)(MSCB_BASE_ADDRESS + 0x0C))

/**
 * @brief: There are 5 cases of Interrupt Grouping Priorities:
 *      1) MNVIC_PRIORITY_GROUP_4_SUB_0: Which means that there will be 4 bits for group priorities
 *                                      and no bit for subpriority
 *                                      (Meaning that the grouping priority ranges from 0 to 15 and no subpriority)
 *      2) MNVIC_PRIORITY_GROUP_3_SUB_1: Which means that there will be 3 bits for group priorities
 *                                      and 1 bit for subpriority
 *                                      (Meaning that the grouping priority ranges from 0 to 7 and subpriority can
 *                                       have the values 0 and 1)
 * 
 *      1) MNVIC_PRIORITY_GROUP_2_SUB_2: Which means that there will be 4 bits for group priorities
 *                                      and no bit for subpriority
 *                                      (Meaning that the grouping priority ranges from 0 to 3 and subpriority ranges
 *                                          from 0 to 3)
 * 
 *      1) MNVIC_PRIORITY_GROUP_1_SUB_3: Which means that there will be 1 bit for group priorities
 *                                      and 3 bit for subpriority
 *                                      (Meaning that the grouping priority can
 *                                       have the values 0 and 1 and subpriority ranges from 0 to 7)
 *      
 *      1) MNVIC_PRIORITY_GROUP_0_SUB_4: Which means that there will be 4 bits for group priorities
 *                                      and no bit for subpriority
 *                                      (Meaning that no group priority and subpriority ranges from 0 to 15)
 *                                      (Which can also indicate that there will be no nesting as all peripherals
 *                                       will have the same group priority)
 * 
 *      As you can see below, the values start with (05FA) which is ,as stated in datasheet, the value that must
 *      be put in the most significant 2 bytes of Application Interrupt and Reset Control register (MSCB_AIRCR) in
 *      order to write anything on this register
 * 
 *      Based on the value put in PRIGROUP Bits in MSCB_AIRCR, for each interrupt, the most significant
 *      4 bits in the Interrupt Priority Register Corresponding to this interrupt will be divided according
 *      to this table:
 * 
 *        PRIGROUP "3 bits"|   PRI division  | Max. No. of group priorities "G"|  Subgroups "S"
 *       __________________|_________________|_________________________________|________________|
 *                         |   7          4  |                                 |
 *             011 "3"     |   -----------   |              16                 |      0
 *                         |  |     G    |   |                                 |
 *                         |  -----------    |                                 |
 *       ----------------------------------------------------------------------------------------
 *                         |   7      5  4   |                                 |
 *             100 "4"     |   ----------    |              8                  |      2
 *                         |  |  G   | S|    |                                 |
 *                         |  ----------     |                                 |
 *       ----------------------------------------------------------------------------------------
 *                         |   7    6    4   |                                 |
 *             101 "5"     |   ----------    |              4                  |      4
 *                         |  |  G |  S |    |                                 |
 *                         |  ----------     |                                 |
 *       ----------------------------------------------------------------------------------------
 *                         |   7  6       4  |                                 |
 *             011 "3"     |   -----------   |              2                  |      8
 *                         |  |G |   S   |   |                                 |
 *                         |  -----------    |                                 |
 *       ----------------------------------------------------------------------------------------
 *                         |   7          4  |                                 |
 *             011 "3"     |   -----------   |              0                  |      16
 *                         |  |     S    |   |                                 |
 *                         |  -----------    |                                 |
 *       ----------------------------------------------------------------------------------------
 */
#define MNVIC_PRIORITY_GROUP_4_SUB_0             0x0300
#define MNVIC_PRIORITY_GROUP_3_SUB_1             0x0400
#define MNVIC_PRIORITY_GROUP_2_SUB_2             0x0500
#define MNVIC_PRIORITY_GROUP_1_SUB_3             0x0600
#define MNVIC_PRIORITY_GROUP_0_SUB_4             0x0700
#endif /*_NVIC_PRIVATE_H_*/