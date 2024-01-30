/**
 * @file UART_Config.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _UART_CONFIG_H_
#define _UART_CONFIG_H_

/*
UART Number of Data Bits Choice:
    1) 8 Data Bits:     MUART_EIGHT_DATA_BITS
    2) 9 Data Bits:     MUART_NINE_DATA_BITS
*/
#define MUART_NO_OF_DATA_BITS           MUART_EIGHT_DATA_BITS
/*
UART Parity Choice:
    1) No Parity:       MUART_NO_PARITY
    2) Even Parity:     MUART_EVEN_PARITY
    3) Odd Parity:      MUART_ODD_PARITY
*/
#define MUART_PARITY_CHOICE             MUART_NO_PARITY
/*
UART Number of Stop Bits Choice:
    1) 0.5 Stop bit:    MUART_HALF_STOP_BIT
    2) 1 Stop bit:      MUART_ONE_STOP_BIT
    3) 1.5 Stop bit:    MUART_ONE_HALF_STOP_BIT
    4) 2 Stop Bits:     MUART_TWO_STOP_BIT
*/
#define MUART_NO_OF_STOP_BITS           MUART_ONE_STOP_BIT

#define MUART_BAUD_RATE                 115200

/*
UART Transmit Complete Interrupt Status:
    1) Enabled:         MUART_TX_COMPLETE_INT_ENABLED
    2) Disabled:        MUART_TX_COMPLETE_INT_DISABLED
*/
#define MUART_TX_COMPLETE_INT_STATUS    MUART_TX_COMPLETE_INT_DISABLED

/*
UART Receive Complete Interrupt Status:
    1) Enabled:         MUART_RX_COMPLETE_INT_ENABLED
    2) Disabled:        MUART_RX_COMPLETE_INT_DISABLED
*/
#define MUART_RX_COMPLETE_INT_STATUS    MUART_RX_COMPLETE_INT_ENABLED

#define MUART_CLK_FREQ                  8000000
#endif /*_UART_CONFIG_H_*/