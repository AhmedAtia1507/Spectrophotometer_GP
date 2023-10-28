/**
 * @file GPIO_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: C header file used to:
 *         1) Declare functions used to configure General Purpose Input/Output Peripheral.
 *         2) Define Macros used in multiple files 
 * @version 1.0
 * @date 2023-08-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _GPIO_INTERFACE_H_
#define _GPIO_INTERFACE_H_


#define GPIO_PORTA          0                               /* GPIO Port A */
#define GPIO_PORTB          1                               /* GPIO Port B */
#define GPIO_PORTC          2                               /* GPIO Port C */


#define GPIO_LOW            0                               /* GPIO Low value */
#define GPIO_HIGH           1                               /* GPIO High value */


#define GPIO_PIN0           0                               /* GPIO Pin 0 */
#define GPIO_PIN1           1                               /* GPIO Pin 1 */
#define GPIO_PIN2           2                               /* GPIO Pin 2 */
#define GPIO_PIN3           3                               /* GPIO Pin 3 */
#define GPIO_PIN4           4                               /* GPIO Pin 4 */
#define GPIO_PIN5           5                               /* GPIO Pin 5 */
#define GPIO_PIN6           6                               /* GPIO Pin 6 */
#define GPIO_PIN7           7                               /* GPIO Pin 7 */
#define GPIO_PIN8           8                               /* GPIO Pin 8 */
#define GPIO_PIN9           9                               /* GPIO Pin 9 */
#define GPIO_PIN10          10                              /* GPIO Pin 10 */
#define GPIO_PIN11          11                              /* GPIO Pin 11 */
#define GPIO_PIN12          12                              /* GPIO Pin 12 */
#define GPIO_PIN13          13                              /* GPIO Pin 13 */
#define GPIO_PIN14          14                              /* GPIO Pin 14 */
#define GPIO_PIN15          15                              /* GPIO Pin 15 */



#define GPIO_INPUT_ANALOG_MOD                    0b0000     /* GPIO Input Analog Mode */
#define GPIO_INPUT_FLOATING_MOD                  0b0100     /* GPIO Input Floating Mode */
#define GPIO_INPUT_PULL_UP_OR_DOWN_MOD           0b1000     /* GPIO Input Pull down Mode */


#define GPIO_OUTPUT_PUSH_PULL_10MHZ              0b0001     /* GPIO Output Push-Pull Mode, 10MHz */
#define GPIO_OUTPUT_OPEN_DRAIN_10MHZ             0b0101     /* GPIO Output Open-Drain Mode, 10MHz */
#define GPIO_OUTPUT_AF_PUSH_PULL_10MHZ           0b1001     /* GPIO Output Alternate Function Push-Pull Mode, 10MHz */
#define GPIO_OUTPUT_AF_OPEN_DRAIN_10MHZ          0b1101     /* GPIO Output Alternate Function Open-Drain Mode, 10MHz */

#define GPIO_OUTPUT_PUSH_PULL_2MHZ               0b0010     /* GPIO Output Push-Pull Mode, 2MHz */
#define GPIO_OUTPUT_OPEN_DRAIN_2MHZ              0b0110     /* GPIO Output Open-Drain Mode, 2MHz */
#define GPIO_OUTPUT_AF_PUSH_PULL_2MHZ            0b1010     /* GPIO Output Alternate Function Push-Pull Mode, 2MHz */
#define GPIO_OUTPUT_AF_OPEN_DRAIN_2MHZ           0b1110     /* GPIO Output Alternate Function Open-Drain Mode, 2MHz */

#define GPIO_OUTPUT_PUSH_PULL_50MHZ              0b0011     /* GPIO Output Push-Pull Mode, 50MHz */
#define GPIO_OUTPUT_OPEN_DRAIN_50MHZ             0b0111     /* GPIO Output Open-Drain Mode, 50MHz */
#define GPIO_OUTPUT_AF_PUSH_PULL_50MHZ           0b1011     /* GPIO Output Alternate Function Push-Pull Mode, 50MHz */
#define GPIO_OUTPUT_AF_OPEN_DRAIN_50MHZ          0b1111     /* GPIO Output Alternate Function Open-Drain Mode, 50MHz */

/**
 * @brief: Function to set the mode of the GPIO Pin
 * 
 * @param Copy_u8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_u8PinID: ID of the pin (0 --> 15)
 * @param Copy_u8PinMode: Mode of the Pin 
 * @return Std_ReturnType
 * @retval E_OK: Pin Mode has been set successfully
 * @retval E_NOT_OK: Pin mode has not been set 
 */
Std_ReturnType MGPIO_u8SetPinMode(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinMode);
/**
 * @brief: Function to set the value of the output GPIO Pin
 * 
 * @param Copy_u8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_u8PinID: ID of the pin (0 --> 15)
 * @param Copy_u8PinValue: Value to be set (High or Low) 
 * @return Std_ReturnType
 * @retval E_OK: Pin Value has been set successfully
 * @retval E_NOT_OK: Pin Value has not been set
 */
Std_ReturnType MGPIO_u8SetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinValue);
/**
 * @brief: Function to get the value of the input GPIO Pin
 * 
 * @param Copy_u8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_u8PinID: ID of the pin (0 --> 15)
 * @param Copy_u8PinValue: Value of input pin (High or Low) 
 * @return Std_ReturnType
 * @retval E_OK: Pin Value has been read successfully
 * @retval E_NOT_OK: Pin Value has not been read
 */
Std_ReturnType MGPIO_u8GetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID, u8* P_u8PinValue);
/**
 * @brief: Function to activate the internal pull-up resistor
 * 
 * @param Copy_u8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_u8PinID: ID of the pin (0 --> 15)
 * @return Std_ReturnType
 * @retval E_OK: Pull-up has been activated successfully
 * @retval E_NOT_OK: Pull-up has not been activated 
 */
Std_ReturnType MGPIO_u8ActivatePullUp(u8 Copy_u8PortID, u8 Copy_u8PinID);
#endif /*_GPIO_INTERFACE_H_*/