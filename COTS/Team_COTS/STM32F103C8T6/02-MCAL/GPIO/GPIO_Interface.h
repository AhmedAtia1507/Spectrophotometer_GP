/**
 * @file GPIO_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: C header file used to:
 *         1) Declare functions used to configure General Purpose Input/Output Peripheral.
 *         2) Define Macros used in multiple files 
 * @version 1.0
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _GPIO_INTERFACE_H_
#define _GPIO_INTERFACE_H_


#define MGPIO_PORTA                                 0           /* GPIO Port A */
#define MGPIO_PORTB                                 1           /* GPIO Port B */
#define MGPIO_PORTC                                 2           /* GPIO Port C */


#define MGPIO_LOW                                   0           /* GPIO Low value */
#define MGPIO_HIGH                                  1           /* GPIO High value */


#define MGPIO_PIN0                                  0           /* GPIO Pin 0 */
#define MGPIO_PIN1                                  1           /* GPIO Pin 1 */
#define MGPIO_PIN2                                  2           /* GPIO Pin 2 */
#define MGPIO_PIN3                                  3           /* GPIO Pin 3 */
#define MGPIO_PIN4                                  4           /* GPIO Pin 4 */
#define MGPIO_PIN5                                  5           /* GPIO Pin 5 */
#define MGPIO_PIN6                                  6           /* GPIO Pin 6 */
#define MGPIO_PIN7                                  7           /* GPIO Pin 7 */
#define MGPIO_PIN8                                  8           /* GPIO Pin 8 */
#define MGPIO_PIN9                                  9           /* GPIO Pin 9 */
#define MGPIO_PIN10                                 10          /* GPIO Pin 10 */
#define MGPIO_PIN11                                 11          /* GPIO Pin 11 */
#define MGPIO_PIN12                                 12          /* GPIO Pin 12 */
#define MGPIO_PIN13                                 13          /* GPIO Pin 13 */
#define MGPIO_PIN14                                 14          /* GPIO Pin 14 */
#define MGPIO_PIN15                                 15          /* GPIO Pin 15 */



#define MGPIO_INPUT_ANALOG_MODE                     (uint32)0b0000     /* GPIO Input Analog Mode */
#define MGPIO_INPUT_FLOATING_MODE                   (uint32)0b0100     /* GPIO Input Floating Mode */
#define MGPIO_INPUT_PULL_UP_OR_DOWN_MODE            (uint32)0b1000     /* GPIO Input Pull down Mode */


#define MGPIO_OUTPUT_PUSH_PULL_10MHZ                (uint32)0b0001     /* GPIO Output Push-Pull Mode, 10MHz */
#define MGPIO_OUTPUT_OPEN_DRAIN_10MHZ               (uint32)0b0101     /* GPIO Output Open-Drain Mode, 10MHz */
#define MGPIO_OUTPUT_AF_PUSH_PULL_10MHZ             (uint32)0b1001     /* GPIO Output Alternate Function Push-Pull Mode, 10MHz */
#define MGPIO_OUTPUT_AF_OPEN_DRAIN_10MHZ            (uint32)0b1101     /* GPIO Output Alternate Function Open-Drain Mode, 10MHz */

#define MGPIO_OUTPUT_PUSH_PULL_2MHZ                 (uint32)0b0010     /* GPIO Output Push-Pull Mode, 2MHz */
#define MGPIO_OUTPUT_OPEN_DRAIN_2MHZ                (uint32)0b0110     /* GPIO Output Open-Drain Mode, 2MHz */
#define MGPIO_OUTPUT_AF_PUSH_PULL_2MHZ              (uint32)0b1010     /* GPIO Output Alternate Function Push-Pull Mode, 2MHz */
#define MGPIO_OUTPUT_AF_OPEN_DRAIN_2MHZ             (uint32)0b1110     /* GPIO Output Alternate Function Open-Drain Mode, 2MHz */

#define MGPIO_OUTPUT_PUSH_PULL_50MHZ                (uint32)0b0011     /* GPIO Output Push-Pull Mode, 50MHz */
#define MGPIO_OUTPUT_OPEN_DRAIN_50MHZ               (uint32)0b0111     /* GPIO Output Open-Drain Mode, 50MHz */
#define MGPIO_OUTPUT_AF_PUSH_PULL_50MHZ             (uint32)0b1011     /* GPIO Output Alternate Function Push-Pull Mode, 50MHz */
#define MGPIO_OUTPUT_AF_OPEN_DRAIN_50MHZ            (uint32)0b1111     /* GPIO Output Alternate Function Open-Drain Mode, 50MHz */

/**
 * @brief: Function to set the mode of the GPIO Pin
 * 
 * @param Copy_uint8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_uint8PinID: ID of the pin (0 --> 15)
 * @param Copy_uint8PinMode: Mode of the Pin 
 * @return Std_ReturnType
 * @retval E_OK: Pin Mode has been set successfully
 * @retval E_NOT_OK: Pin mode has not been set 
 */
Std_ReturnType MGPIO_SetPinMode     (uint8 Copy_uint8PortID, uint8 Copy_uint8PinID, uint8 Copy_uint8PinMode);
/**
 * @brief: Function to set the value of the output GPIO Pin
 * 
 * @param Copy_uint8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_uint8PinID: ID of the pin (0 --> 15)
 * @param Copy_uint8PinValue: Value to be set (High or Low) 
 * @return Std_ReturnType
 * @retval E_OK: Pin Value has been set successfully
 * @retval E_NOT_OK: Pin Value has not been set
 */
Std_ReturnType MGPIO_SetPinValue    (uint8 Copy_uint8PortID, uint8 Copy_uint8PinID, uint8 Copy_uint8PinValue);
/**
 * @brief: Function to toggle the value of the output GPIO Pin
 * 
 * @param Copy_uint8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_uint8PinID: ID of the pin (0 --> 15)
 *  
 * @return Std_ReturnType
 * @retval E_OK: Pin Value has been toggled successfully
 * @retval E_NOT_OK: Pin Value has not been toggled
 */
Std_ReturnType MGPIO_TogglePinValue    (uint8 Copy_uint8PortID, uint8 Copy_uint8PinID);
/**
 * @brief: Function to get the value of the input GPIO Pin
 * 
 * @param Copy_uint8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_uint8PinID: ID of the pin (0 --> 15)
 * @param Copy_uint8PinValue: Value of input pin (High or Low) 
 * @return Std_ReturnType
 * @retval E_OK: Pin Value has been read successfully
 * @retval E_NOT_OK: Pin Value has not been read
 */
Std_ReturnType MGPIO_GetPinValue    (uint8 Copy_uint8PortID, uint8 Copy_uint8PinID, uint8* P_uint8PinValue);
/**
 * @brief: Function to activate the internal pull-up resistor
 * 
 * @param Copy_uint8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_uint8PinID: ID of the pin (0 --> 15)
 * @return Std_ReturnType
 * @retval E_OK: Pull-up has been activated successfully
 * @retval E_NOT_OK: Pull-up has not been activated 
 */
Std_ReturnType MGPIO_ActivatePullUp (uint8 Copy_uint8PortID, uint8 Copy_uint8PinID);
/**
 * @brief: Function to set the value of a range of output GPIO pins 
 * 
 * @param Copy_uint8PortID: ID of the port containing the pins 
 * @param Copy_uint8StartPinID: ID of the start pin in the range 
 * @param Copy_uint8EndPinID: ID of the end pin in the range
 * @param Copy_uint16NibbleValue: Value to be set
 * @return Std_ReturnType
 * @retval E_OK: Value has been set successfully
 * @retval E_NOT_OK: Value has not been set  
 */
Std_ReturnType MGPIO_SetNibbleValue (uint8 Copy_uint8PortID, uint8 Copy_uint8StartPinID, uint8 Copy_uint8EndPinID, uint16 Copy_uint16NibbleValue);
#endif /*_GPIO_INTERFACE_H_*/