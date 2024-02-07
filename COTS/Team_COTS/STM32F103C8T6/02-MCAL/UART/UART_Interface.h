/**
 * @file UART_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: Header file to:
 *          1) Define function prototypes used to control 
 *                  Universal Asynchronous Receiver/Transmitter peripheral
 *          2) Define Macros to be used in other files for UART Peripheral 
 * @version 1.0
 * @date 2023-11-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _UART_INTERFACE_H_
#define _UART_INTERFACE_H_

typedef enum MUART_Select
{
    UART1,
    UART2,
    UART3
} MUART_Select_t;

#define MUART1_TX_PORT_ID                       MGPIO_PORTA
#define MUART1_TX_PIN_ID                        MGPIO_PIN9

#define MUART1_RX_PORT_ID                       MGPIO_PORTA
#define MUART1_RX_PIN_ID                        MGPIO_PIN10

#define MUART2_TX_PORT_ID                       MGPIO_PORTA
#define MUART2_TX_PIN_ID                        MGPIO_PIN2

#define MUART2_RX_PORT_ID                       MGPIO_PORTA
#define MUART2_RX_PIN_ID                        MGPIO_PIN3

#define MUART3_TX_PORT_ID                       MGPIO_PORTB
#define MUART3_TX_PIN_ID                        MGPIO_PIN10

#define MUART3_RX_PORT_ID                       MGPIO_PORTB
#define MUART3_RX_PIN_ID                        MGPIO_PIN11

typedef void(*ptr_to_Callback)(void);
/**
 * @brief: Function to initialize the UART Peripheral
 * 
 * @param Copy_UARTChoice: UART to be initialized
 * 
 * @return Std_ReturnType
 * @retval E_OK:        UART Peripheral is successfully initialized
 * @retval E_NOT_OK:    UART Peripheral is not initialized
 */
Std_ReturnType MUART_Init(MUART_Select_t Copy_UARTChoice);
/**
 * @brief: Function to Send a character using UART Peripheral
 * 
 * @param Copy_UARTChoice: Which UART to send the Data on
 * @param Copy_uint16TxChar: Characted to be sent
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Character successfully sent
 * @retval E_NOT_OK:    Character not sent 
 */
Std_ReturnType MUART_TxChar(MUART_Select_t Copy_UARTChoice, uint16 Copy_uint8TxChar);
/**
 * @brief: Function to Send a character using UART Peripheral
 * 
 * @param Copy_UARTChoice: Which UART to send the Data on
 * @param Copy_uint16TxChar: Characted to be sent
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Character successfully sent
 * @retval E_NOT_OK:    Character not sent 
 */
Std_ReturnType MUART_TxCharAsynchronous(MUART_Select_t Copy_UARTChoice, uint16 Copy_uint16TxChar);
/**
 * @brief: Function to Receive a character from UART Peripheral
 * 
 * @param Copy_UARTChoice: Which UART to receive data from
 * @param P_uint16RxChar: Pointer to pass the received data on 
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Character successfully received
 * @retval E_NOT_OK:    Character not received 
 */
Std_ReturnType MUART_RxChar(MUART_Select_t Copy_UARTChoice, uint16* P_uint16RxChar);
/**
 * @brief: Function to Send a character using UART Peripheral
 * 
 * @param Copy_UARTChoice: Which UART to send the Data on
 * @param P_uint16RxChar: Pointer to pass the received data on
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Character successfully sent
 * @retval E_NOT_OK:    Character not sent 
 */
Std_ReturnType MUART_RxCharAsynchronous(MUART_Select_t Copy_UARTChoice, uint16* P_uint16RxChar);
/**
 * @brief: Function to transmit a string on UART Peripheral
 * 
 * @param Copy_UARTChoice: Which UART to send data on
 * @param P_uint8TxString: String to be sent
 * 
 * @return Std_ReturnType
 * @retval E_OK:        String successfully received
 * @retval E_NOT_OK:    String not received 
 */
Std_ReturnType MUART_TxString(MUART_Select_t Copy_UARTChoice, uint8* P_uint8TxString);
/**
 * @brief: Function to set the callback function of Tx Complete Interrupt
 * 
 * @param Copy_UARTChoice: Choice of UART (1,2,3)
 * @param P_TxCompleteCallbackFunc: Callback function to be set
 * @return Std_ReturnType
 * @retval E_OK:        Callback Function successfully set
 * @retval E_NOT_OK:    Callback function not set  
 */
Std_ReturnType MUART_SetTxCompleteCallback(MUART_Select_t Copy_UARTChoice, ptr_to_Callback P_TxCompleteCallbackFunc);
/**
 * @brief: Function to set the callback function of Rx Complete Interrupt
 * 
 * @param Copy_UARTChoice: Choice of UART (1,2,3)
 * @param P_RxCompleteCallbackFunc: Callback function to be set
 * @return Std_ReturnType
 * @retval E_OK:        Callback Function successfully set
 * @retval E_NOT_OK:    Callback function not set  
 */
Std_ReturnType MUART_SetRxCompleteCallback(MUART_Select_t Copy_UARTChoice, ptr_to_Callback P_RxCompleteCallbackFunc);

Std_ReturnType MUART_SendIntegerValue(MUART_Select_t Copy_UARTChoice, uint32 Copy_uint32Value);
#endif /*_UART_INTERFACE_H_*/