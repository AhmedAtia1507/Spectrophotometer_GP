/**
 * @file UART_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: C header file to define memory mapping for UART Peripheral
 *              "Universal Asynchronous Receiver/Transmitter"  
 * @version 1.0
 * @date 2023-11-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _UART_PRIVATE_H_
#define _UART_PRIVATE_H_

#include "Std_Types.h"
/*
    We Have 3 UART in our microcontroller
    UART 1 -----> Connected to APB2 Bus
    UART 2 & 3 ----> Connected to APB1 Bus
*/
#define MUART1_BASE_ADDRESS                         0x40013800U
#define MUART2_BASE_ADDRESS                         0x40004400U
#define MUART3_BASE_ADDRESS                         0x40004800U

typedef struct MUART_Registers
{
    /*UART Status Register*/
    volatile uint32 SR;
    /*
    UART Data Register:
        Contains the received or transmitted data character, depending
        on whether it is read from or written to
    */
    volatile uint32 DR;
    /*UART Baud rate register*/
    volatile uint32 BRR;
    /*UART Control Register 1*/
    volatile uint32 CR1;
    /*UART Control Register 2*/
    volatile uint32 CR2;
    /*UART Control Register 3*/
    volatile uint32 CR3;
    /*Guard Time and Prescalar Register*/
    volatile uint32 GTPR;
} MUART_Typedef;

#define MUART1                                      ((MUART_Typedef *)(MUART1_BASE_ADDRESS))
#define MUART2                                      ((MUART_Typedef *)(MUART2_BASE_ADDRESS))
#define MUART3                                      ((MUART_Typedef *)(MUART3_BASE_ADDRESS))

/************************UART Status Register "SR" Bits*************************/

/*
Parity Error:
    1) Set by hardware when a parity error occurs in receiver mode.
    2) Cleared by software sequence:
        A read to status register ---> A read to UART data register
        Note: Software must wait for the RXNE flag to be set before clearing PE bit
    3) An Interrupt is generated if PEIE = 1 in UART_CR1 register
*/
#define MUART_SR_PE_BIT                             0
/*
Framing Error:
    1) Set by hardware when a de-synchronization, excessive noise or a break character
        is detected.
    2) Cleared by software sequence:
        A read to status register ---> A read to UART data register
    3) This bit does not generate interrupt as it sets at the same time as RXNE bit
        which itself does generate interrupt
    */
#define MUART_SR_FE_BIT                             1
/*
Noise Error Flag:
    1) Set by hardware when noise is detected on a received frame.
    2) Cleared by software sequence:
        A read to status register ---> A read to UART data register
*/
#define MUART_SR_NE_BIT                             2
/*
Overrun Error:
    1) Set by hardware when the word currently being received in the shift
        register is ready to be transferred into the RDR register while RXNE = 1
    2) An interrupt is generated if RXNEIE = 1 in the UART_CR1 register.
    3) Cleared by software sequence:
        A read to status register ---> A read to UART data register
*/
#define MUART_SR_ORE_BIT                            3
/*
IDLE Line Detected:
    1) Set by hardware when an Idle line is detected:
    2) An Interrupt is generated if IDLEIE = 1 in the UART_CR1 register
    3) Cleared by software sequence:
        A read to status register ---> A read to UART data register
    4) IDLE bit will not be set again untile the RXNE bit has been set itself
        (i.e. a new idle line occurs)
*/
#define MUART_SR_IDLE_BIT                           4
/*
Read Data Register Not Empty:
    1) Set by hardware when the content of the RDR shift register has been
        transferred to the UART Data register.
    2) An Interrupt is generated if RXNEIE = 1 in the UART_CR1 register
    3) Cleared by a read to the UART Data register.
    4) Can also be cleared by writing a zero to it.
*/
#define MUART_SR_RXNE_BIT                           5
/*
Transmission complete:
    1) Set by hardware if the transmission of a frame containing data is complete
        and TXE is set
    2) An Interrupt is generated if TCIE = 1 in the USART_CR1 register.
    3) Cleared by software sequence:
        A read to status register ---> A write to UART data register
    4) Can also be cleared by writing a zero to it.
*/
#define MUART_SR_TC_BIT                             6
/*
Transmit Data Register Empty:
    1) Set by hardware when the content of the TDR register has been transferred
        into the shift register.
    2) An Interrupt is generated if the TXEIE bit = 1 in the UART_CR1 register
    3) Cleared by a write to the UART Data register
*/
#define MUART_SR_TXE_BIT                            7
/*
LIN Break Detection Flag
    1) Set by hardware when the LIN Break is detected.
    2) Cleared by writing it to zero.
    3) An interrupt is generated if LBDIE = 1 in the UART_CR2 register
*/
#define MUART_SR_LBD_BIT                            8
/*
CTS Flag:
    1) Set by hardware when the CTS input toggles, If the CTSE bit is set
    2) Cleared by writing a zero to it.
    3) An interrupt is generated if CTSIE = 1 in the UART_CR3 register
*/
#define MUART_SR_CTS_BIT                            9

/************************UART Baud Rate Register "BRR" Bits*************************/

/*Fraction part of the UART Divider "4 bits"*/
#define MUART_BRR_FRACTION_START_BIT                0
/*Mantissa Part of the UART Divider "12 bits"*/
#define MUART_BRR_MANTISSA_START_BIT                4

/************************UART Control Register 1 "CR1" Bits*************************/

/*
Send break:
    1) Used to send break characters.
    2) Can be set and cleared by software.
    3) Should be set by software and will be reset by hardware during the
        stop bit of break.
*/
#define MUART_CR1_SBK_BIT                           0
/*
Receiver Wakeup:
    1) Determines if the UART is in mute mode or not.
    2) Set and cleared by software and can be cleared by hardware when a wakeup
        sequence is recognized
*/
#define MUART_CR1_RWU_BIT                           1
/*
Receiver Enable:
    Enables Receiver. Set and Cleared by software.
*/
#define MUART_CR1_RE_BIT                            2
/*
Transmitter Enable:
    Enables Transmitter. Set and Cleared by software
*/
#define MUART_CR1_TE_BIT                            3
/*
IDLE Interrupt Enable:
    Set and Cleared by software.
*/
#define MUART_CR1_IDLEIE_BIT                        4
/*Receiver not empty interrupt enable*/
#define MUART_CR1_RXNEIE_BIT                        5
/*Transmission Complete Interrupt Enable*/
#define MUART_CR1_TCIE_BIT                          6
/*Transmit register empty interrupt enable*/
#define MUART_CR1_TXEIE_BIT                         7
/*Parity Error Interrupt Enable*/
#define MUART_CR1_PEIE_BIT                          8
/*
Parity Selection:
    Selects the odd or even parity when the parity generation/detection is enabled (PCE bit set)
    0 ----> Even Parity
    1 ----> Odd Parity
*/
#define MUART_CR1_PS_BIT                            9
/*
Parity Control Enable:
    1) Selects the hardware parity control (Generation & Detection).
    2) When the parity control is enabled, the computed parity is inserted at the MSB
        position (9th bit if M = 1 ; 8th bit if M = 0) and parity is checked on the received data.
    3) Once it is set, PCE will be active after the current byte
*/
#define MUART_CR1_PCE_BIT                           10
/*
Wakeup Method:
    1) Determines the UART Wakeup Method.
    2) Set and Cleared by Software
    0 -----> Idle Line
    1 -----> Address Mark
*/
#define MUART_CR1_WAKE_BIT                          11
/*
Word Length:
    Determines the word length:
    0 ----> 1 Start bit, 8 Data bits, n Stop Bits
    1 ----> 1 Start bit, 9 Data bits, n Stop Bits
*/
#define MUART_CR1_M_BIT                             12
/*UART Enable*/
#define MUART_CR1_UE_BIT                            13

/************************UART Control Register 2 "CR2" Bits*************************/

/*
Address of the UART Node "4 bits":
    1) Gives the address of the UART Node.
    2) Used in multiprocessor communication during mute mode, for wakeup
        with address mark detection
*/
#define MUART_CR2_ADD_START_BIT                     0
/*
LIN break detection length:
    Selection between 11 bit or 10 bit break detection.
    0 -----> 10 bit break detection
    1 -----> 11 bit break detection
*/
#define MUART_CR2_LBDL_BIT                          5
/*LIN Break Detection Interrupt Enable*/
#define MUART_CR2_LBDIE_BIT                         6
/*Last bit Clock Pulse: Available only on synchronous mode*/
#define MUART_CR2_LBCL_BIT                          8
#define MUART_CR2_CPHA_BIT                          9
#define MUART_CR2_CPOL_BIT                          10
#define MUART_CR2_CLKEN_BIT                         11
/*
STOP Bits "2 bits":
    00 -----> 1 Stop Bit
    01 -----> 0.5 Stop Bit
    10 -----> 2 Stop Bits
    11 -----> 1.5 Stop Bits
*/
#define MUART_CR2_STOP_START_BIT                    12
#define MUART_CR2_LINEN_BIT                         14

/************************UART Control Register 3 "CR3" Bits*************************/

/*
Error Interrupt Enable:
    This bit is required to enable interrupt generation in case of a framing error,
    overrun error or noise error
*/
#define MUART_CR3_EIE_BIT                           0
#define MUART_CR3_IREN_BIT                          1
#define MUART_CR3_IRLP_BIT                          2
/*
Half-Duplex Selection:
    0 ----> Half Duplex mode is not selected
    1 ----> Half Duplex mode is selected
*/
#define MUART_CR3_HDSEL_BIT                         3
/*
Smartcard Negative Acknowledge enable
    0 ----> NACK Transmission in case of parity error is disabled
    1 ----> NACK Transmission in case of parity error is enabled
*/
#define MUART_CR3_NACK_BIT                          4
/*Smartcard mode enable*/
#define MUART_CR3_SCEN_BIT                          5
#define MUART_CR3_DMAR_BIT                          6
#define MUART_CR3_DMAT_BIT                          7
#define MUART_CR3_RTSE_BIT                          8


#define MUART_ONE_STOP_BIT                          0b00
#define MUART_HALF_STOP_BIT                         0b01
#define MUART_TWO_STOP_BIT                          0b10
#define MUART_ONE_HALF_STOP_BIT                     0b11

#define MUART_NO_PARITY                             1
#define MUART_EVEN_PARITY                           2
#define MUART_ODD_PARITY                            3

#define MUART_EIGHT_DATA_BITS                       1
#define MUART_NINE_DATA_BITS                        2

#define MUART_TX_COMPLETE_INT_ENABLED               1
#define MUART_TX_COMPLETE_INT_DISABLED              2

#define MUART_RX_COMPLETE_INT_ENABLED               1
#define MUART_RX_COMPLETE_INT_DISABLED              2
#endif /*_UART_PRIVATE_H_*/