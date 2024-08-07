/**
 * @file UART_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/Std_Types.h"

#include "UART_Private.h"
#include "UART_Interface.h"
#include "UART_Config.h"

/**
 * @brief: An array of three pointers to structs that contains the registers of each UART peripheral inside STM32
 * 
 * 
 */
static volatile MUART_Typedef* (UART[3]) = {MUART1, MUART2, MUART3};

/**
 * @brief: An array of three pointers to functions that represent the functions to be executed when
 *          UART Tx Complete Interrupt Occurs  
 * 
 */
static volatile ptr_to_Callback Glbl_PTxCompleteFunc[3] = {NULL_PTR};
/**
 * @brief: An array of three pointers to functions that represent the functions to be executed when
 *          UART Rx Complete Interrupt Occurs  
 * 
 */
static volatile ptr_to_Callback Glbl_PRxCompleteFunc[3] = {NULL_PTR};

/**
 * @brief: Function to initialize the UART Peripheral
 * 
 * @param Copy_UARTChoice: UART to be initialized
 * 
 * @return Std_ReturnType
 * @retval E_OK:        UART Peripheral is successfully initialized
 * @retval E_NOT_OK:    UART Peripheral is not initialized
 */
Std_ReturnType MUART_Init(MUART_Select_t Copy_UARTChoice)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    
    /*************************************************************************************************
                            1. Select the number of data bits (8 or 9)
    *************************************************************************************************/
    #if MUART_NO_OF_DATA_BITS == MUART_EIGHT_DATA_BITS
        CLR_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_M_BIT);
    #elif MUART_NO_OF_DATA_BITS == MUART_NINE_DATA_BITS
        SET_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_M_BIT);
    #else
        #error "UART No of Data Bits is not Specified Correctly"
    #endif /*MUART_NO_OF_DATA_BITS*/

    /************************************************************************************************* 
                            2. Set Parity (No parity, even parity or odd parity)
    *************************************************************************************************/
    #if MUART_PARITY_CHOICE == MUART_NO_PARITY
        CLR_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_PCE_BIT);
    #elif MUART_PARITY_CHOICE == MUART_EVEN_PARITY
        SET_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_PCE_BIT);
        CLR_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_PS_BIT);
    #elif MUART_PARITY_CHOICE == MUART_ODD_PARITY
        SET_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_PCE_BIT);
        SET_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_PS_BIT);
    #else
        #error "UART Parity Control not Specified"
    #endif

    /************************************************************************************************* 
                            3. Set the number of stop bits (0.5, 1, 1.5 or 2 bits)
    *************************************************************************************************/
    ((UART[Copy_UARTChoice]) -> CR2) &= ~(((uint32) 0b11) << MUART_CR2_STOP_START_BIT);
    
    #if ((MUART_NO_OF_STOP_BITS == MUART_HALF_STOP_BIT) || (MUART_NO_OF_STOP_BITS == MUART_ONE_STOP_BIT) || (MUART_NO_OF_STOP_BITS == MUART_ONE_HALF_STOP_BIT) || (MUART_NO_OF_STOP_BITS == MUART_TWO_STOP_BIT))
        ((UART[Copy_UARTChoice]) -> CR2) |= (((uint32) MUART_NO_OF_STOP_BITS) << MUART_CR2_STOP_START_BIT);
    #else
        #error "UART Number of Stop Bits not Specified"
    #endif /*MUART_NO_OF_STOP_BITS*/

    /************************************************************************************************* 
                            4. Set the Tx Complete Interrupt Status (Enabled or Disabled)
    *************************************************************************************************/
    #if MUART_TX_COMPLETE_INT_STATUS == MUART_TX_COMPLETE_INT_ENABLED
        SET_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_TCIE_BIT);
    #elif MUART_TX_COMPLETE_INT_STATUS == MUART_TX_COMPLETE_INT_DISABLED
        CLR_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_TCIE_BIT);
    #else
        #error "UART Tx Complete Interrupt Status not Specified"
    #endif /*MUART_TX_COMPLETE_INT_STATUS*/

    /************************************************************************************************* 
                            5. Set the Rx Complete Interrupt Status (Enabled or Disabled)
    *************************************************************************************************/
    #if MUART_RX_COMPLETE_INT_STATUS == MUART_RX_COMPLETE_INT_ENABLED
        SET_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_RXNEIE_BIT);
    #elif MUART_RX_COMPLETE_INT_STATUS == MUART_RX_COMPLETE_INT_DISABLED
        CLR_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_RXNEIE_BIT);
    #else
        #error "UART Rx Complete Interrupt Status not Specified"
    #endif /*MUART_RX_COMPLETE_INT_STATUS*/
    
    /************************************************************************************************* 
                                            6. Set UART Baud Rate
    *************************************************************************************************/

    /*
        UART Baud Rate is not directly set. Instead, A baud rate divisor is calculated and set according
        to the following equation:
                                            UART Clock Frequency
        UART Baud Rate Divisor = -------------------------------------------
                                            16 * UART Baud Rate
        
        Note that the minimum value for baud rate divisor is 1. So, for example, in case the clock
        frequency equals 8MHz, then the maximum allowed baud rate equals 500000 baud/s
    */
    #if (MUART_CLK_FREQ / (16 * MUART_BAUD_RATE)) >= 1
        float32 Loc_float32UARTDIV = (float32)MUART_CLK_FREQ / (16 * MUART_BAUD_RATE);

        /*
            UART Baud rate divisor is set in the register as a floating point number where:

                                    UART Baud rate Register (UARTx_BRR)
                                15 - 4                                  3 - 0
            ----------------------------------------------------------------------------------
            |                 Mantissa Part              |         Fraction Part             |
            ---------------------------------------------------------------------------------

            which are calculated using the equations below
        */
        uint16 Loc_uint16Mantissa = (uint16)Loc_float32UARTDIV;
        uint16 Loc_uint16Fraction = (uint16)(((Loc_float32UARTDIV - Loc_uint16Mantissa) * 16) + 0.5);

        if(Loc_uint16Fraction >= 16)
        {
            Loc_uint16Fraction -= 16;
            Loc_uint16Mantissa += 1;
        }
        ((UART[Copy_UARTChoice]) -> BRR) = (Loc_uint16Fraction << MUART_BRR_FRACTION_START_BIT) | (Loc_uint16Mantissa << MUART_BRR_MANTISSA_START_BIT);
    #else
        #error "Error in setting UART Peripheral Baud Rate"
    #endif /*(MUART_CLK_FREQ / (16 * MUART_BAUD_RATE))*/

    /************************************************************************************************* 
                        7. Enable Tx Buffer, Rx Buffer and Enable UART Peripheral
    *************************************************************************************************/
    SET_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_TE_BIT);
    SET_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_RE_BIT);
    SET_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_UE_BIT);
	
    /************************************************************************************************* 
                        8. Make Sure that Tx Complete and Rx not empty flags are cleared
    *************************************************************************************************/
	CLR_BIT(((UART[Copy_UARTChoice]) -> SR) , MUART_SR_TC_BIT);
    CLR_BIT(((UART[Copy_UARTChoice]) -> SR) , MUART_SR_RXNE_BIT);
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}

/**
 * @brief: Function to Send a character using UART Peripheral
 * 
 * @param Copy_UARTChoice: Which UART to send the Data on
 * @param Copy_uint16TxChar: Character to be sent
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Character successfully sent
 * @retval E_NOT_OK:    Character not sent 
 */
Std_ReturnType MUART_TxChar(MUART_Select_t Copy_UARTChoice, uint16 Copy_uint16TxChar)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    /************************************************************************************************* 
                        1. Make Sure that Tx Buffer is empty before sending
    *************************************************************************************************/
    while(!(GET_BIT(((UART[Copy_UARTChoice]) -> SR), MUART_SR_TXE_BIT)));

    /************************************************************************************************* 
                        2. Send Character through UART
    *************************************************************************************************/
    /*
        Here, we make sure that data is compatiable with UART number of data bits' configuration 
                set at initialization
    */
    #if MUART_NO_OF_DATA_BITS == MUART_EIGHT_DATA_BITS
        (UART[Copy_UARTChoice] -> DR) = Copy_uint16TxChar & ((uint16)(0x00FF));
    #elif MUART_NO_OF_DATA_BITS == MUART_NINE_DATA_BITS
        (UART[Copy_UARTChoice] -> DR) = Copy_uint16TxChar & ((uint16)(0x01FF));
    #else
        #error "UART Number of Data Bits not Specified"
    #endif /*MUART_NO_OF_DATA_BITS*/
    
    /************************************************************************************************* 
                        3. Wait until transmit is complete
    *************************************************************************************************/
    while(!(GET_BIT(((UART[Copy_UARTChoice]) -> SR), MUART_SR_TC_BIT)));

    /************************************************************************************************* 
                        4. Clear Tx Complete Flag
    *************************************************************************************************/
    CLR_BIT(((UART[Copy_UARTChoice]) -> SR) , MUART_SR_TC_BIT);

    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
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
Std_ReturnType MUART_TxCharAsynchronous(MUART_Select_t Copy_UARTChoice, uint16 Copy_uint16TxChar)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    /************************************************************************************************* 
                        1. Make Sure that Tx Buffer is empty before sending
    *************************************************************************************************/
    while(!(GET_BIT(((UART[Copy_UARTChoice]) -> SR), MUART_SR_TXE_BIT)));

    /************************************************************************************************* 
                        2. Send Character through UART
    *************************************************************************************************/
    /*
        Here, we make sure that data is compatiable with UART number of data bits' configuration 
                set at initialization
    */
    #if MUART_NO_OF_DATA_BITS == MUART_EIGHT_DATA_BITS
        (UART[Copy_UARTChoice] -> DR) = Copy_uint16TxChar & ((uint16)(0x00FF));
    #elif MUART_NO_OF_DATA_BITS == MUART_NINE_DATA_BITS
        (UART[Copy_UARTChoice] -> DR) = Copy_uint16TxChar & ((uint16)(0x01FF));
    #else
        #error "UART Number of Data Bits not Specified"
    #endif /*MUART_NO_OF_DATA_BITS*/

    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
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
Std_ReturnType MUART_RxChar(MUART_Select_t Copy_UARTChoice, uint16* P_uint16RxChar)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_uint16RxChar != NULL_PTR)
    {
        /************************************************************************************************* 
                        1. Wait until there is data to be received
        *************************************************************************************************/
        while(!(GET_BIT(((UART[Copy_UARTChoice]) -> SR), MUART_SR_RXNE_BIT)));

        /************************************************************************************************* 
                        2. Clear Rx Not Empty Flag
        *************************************************************************************************/
        CLR_BIT(((UART[Copy_UARTChoice]) -> SR) , MUART_SR_RXNE_BIT);
        
        /************************************************************************************************* 
                        3. Get Data from Rx buffer
        *************************************************************************************************/
        #if MUART_NO_OF_DATA_BITS == MUART_EIGHT_DATA_BITS
            #if MUART_PARITY_CHOICE == MUART_NO_PARITY
                *P_uint16RxChar = (((UART[Copy_UARTChoice]) -> DR) & (uint16)(0xFF));
            #elif (MUART_PARITY_CHOICE == MUART_EVEN_PARITY) | (MUART_PARITY_CHOICE == MUART_ODD_PARITY)
                *P_uint16RxChar = (((UART[Copy_UARTChoice]) -> DR) & (uint16)(0x7F));
            #else
                #error "UART Parity Choice is not specified"
            #endif /*MUART_PARITY_CHOICE*/
        #elif MUART_NO_OF_DATA_BITS == MUART_NINE_DATA_BITS
            #if MUART_PARITY_CHOICE == MUART_NO_PARITY
                *P_uint16RxChar = (((UART[Copy_UARTChoice]) -> DR) & (uint16)(0x1FF));
            #elif (MUART_PARITY_CHOICE == MUART_EVEN_PARITY) | (MUART_PARITY_CHOICE == MUART_ODD_PARITY)
                *P_uint16RxChar = (((UART[Copy_UARTChoice]) -> DR) & (uint16)(0xFF));
            #else
                #error "UART Parity Choice is not specified"
            #endif /*MUART_PARITY_CHOICE*/
        #else
            #error "UART Number of Data Bits not Specified"
        #endif /*MUART_NO_OF_DATA_BITS*/

        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to Send a character using UART Peripheral
 * 
 * @param Copy_UARTChoice: Which UART to send the Data on
 * @param P_uint8RxChar: Pointer to pass the received data on
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Character successfully received
 * @retval E_NOT_OK:    Character not received 
 */
Std_ReturnType MUART_RxCharAsynchronous(MUART_Select_t Copy_UARTChoice, uint16* P_uint16RxChar)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_uint16RxChar != NULL_PTR)
    {
        /************************************************************************************************* 
                        1. Get Data from Rx buffer
        *************************************************************************************************/
        #if MUART_NO_OF_DATA_BITS == MUART_EIGHT_DATA_BITS
            #if MUART_PARITY_CHOICE == MUART_NO_PARITY
                *P_uint16RxChar = (((UART[Copy_UARTChoice]) -> DR) & (uint16)(0xFF));
            #elif (MUART_PARITY_CHOICE == MUART_EVEN_PARITY) | (MUART_PARITY_CHOICE == MUART_ODD_PARITY)
                *P_uint16RxChar = (((UART[Copy_UARTChoice]) -> DR) & (uint16)(0x7F));
            #else
                #error "UART Parity Choice is not specified"
            #endif /*MUART_PARITY_CHOICE*/
        #elif MUART_NO_OF_DATA_BITS == MUART_NINE_DATA_BITS
            #if MUART_PARITY_CHOICE == MUART_NO_PARITY
                *P_uint16RxChar = (((UART[Copy_UARTChoice]) -> DR) & (uint16)(0x1FF));
            #elif (MUART_PARITY_CHOICE == MUART_EVEN_PARITY) | (MUART_PARITY_CHOICE == MUART_ODD_PARITY)
                *P_uint16RxChar = (((UART[Copy_UARTChoice]) -> DR) & (uint16)(0xFF));
            #else
                #error "UART Parity Choice is not specified"
            #endif /*MUART_PARITY_CHOICE*/
        #else
            #error "UART Number of Data Bits not Specified"
        #endif /*MUART_NO_OF_DATA_BITS*/

        /************************************************************************************************* 
                        2. Clear Rx Not Empty Flag
        *************************************************************************************************/
        CLR_BIT(((UART[Copy_UARTChoice]) -> SR) , MUART_SR_RXNE_BIT);

		Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
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
Std_ReturnType MUART_TxString(MUART_Select_t Copy_UARTChoice, uint8* P_uint8TxString)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_uint8TxString != NULL_PTR)
    {
        uint8 Loc_uint8Index = 0;

        /************************************************************************************************* 
                        Transmit each character in input string until null character is reached
        *************************************************************************************************/
        while(P_uint8TxString[Loc_uint8Index] != '\0')
        {
            MUART_TxChar(Copy_UARTChoice, P_uint8TxString[Loc_uint8Index]);
            Loc_uint8Index++;
        }
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to set the callback function of Tx Complete Interrupt
 * 
 * @param Copy_UARTChoice: Choice of UART (1,2,3)
 * @param P_TxCompleteCallbackFunc: Callback function to be set
 * @return Std_ReturnType
 * @retval E_OK:        Callback Function successfully set
 * @retval E_NOT_OK:    Callback function not set  
 */
Std_ReturnType MUART_SetTxCompleteCallback(MUART_Select_t Copy_UARTChoice, ptr_to_Callback P_TxCompleteCallbackFunc)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_TxCompleteCallbackFunc != NULL_PTR)
    {
        /************************************************************************************************* 
                    Here, We set the function to be executed when the Tx Complete Interrupt of
                                UARTx Occurs
        *************************************************************************************************/
        Glbl_PTxCompleteFunc[Copy_UARTChoice] = P_TxCompleteCallbackFunc;
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to set the callback function of Rx Complete Interrupt
 * 
 * @param Copy_UARTChoice: Choice of UART (1,2,3)
 * @param P_RxCompleteCallbackFunc: Callback function to be set
 * @return Std_ReturnType
 * @retval E_OK:        Callback Function successfully set
 * @retval E_NOT_OK:    Callback function not set  
 */
Std_ReturnType MUART_SetRxCompleteCallback(MUART_Select_t Copy_UARTChoice, ptr_to_Callback P_RxCompleteCallbackFunc)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_RxCompleteCallbackFunc != NULL_PTR)
    {
        /************************************************************************************************* 
                    Here, We set the function to be executed when the Rx Complete Interrupt of
                                UARTx Occurs
        *************************************************************************************************/
        Glbl_PRxCompleteFunc[Copy_UARTChoice] = P_RxCompleteCallbackFunc;
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to send an integer value through UART Communication Protocol
 * 
 * @param Copy_UARTChoice: Choice of UART (1,2,3)
 * @param Copy_uint32Value: Integer Value to be sent
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Integer Value Successfully Sent
 * @retval E_NOT_OK:    Integer Value not sent   
 */
Std_ReturnType MUART_SendIntegerValue(MUART_Select_t Copy_UARTChoice, uint32 Copy_uint32Value)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    if(Copy_uint32Value == 0)
    {
        /************************************************************************************************* 
                In order to convert an integer value to a character, simply add 48 ('0' character's 
                ASCII Value) to the integer
        *************************************************************************************************/
        MUART_TxChar(Copy_UARTChoice, (Copy_uint32Value + 48));
    }
    else
    {
        uint32 Loc_uint8TempValue = Copy_uint32Value;
        uint8 Loc_uint8CharArray[20] = {0}, Loc_uint8Count = 0, Loc_uint8Index = 0;

        /************************************************************************************************* 
        ex. if the number to be sent is 1234:
        1) We get the first digit of the number:
            1234 % 10 = 4 -------> Convert it to character -------> Add it to the array which will be used
                                                                    to send characters through UART
        2) Then, we divide the number by 10 to get rid of this digit
            (1234 / 10) = 123 "Integer value / Integer value = Integer value"
        *************************************************************************************************/
        while(Loc_uint8TempValue != 0)
        {
            Loc_uint8CharArray[Loc_uint8Count] = ((Loc_uint8TempValue % 10) + 48);
            Loc_uint8TempValue /= 10;
            Loc_uint8Count++;
        }
        /************************************************************************************************* 
                            We send the characters in the array one by one through UART
            note that the elements in the array has the numbers in opposite order to the original number
                    ex. if the number is 1234, the array will be equal to {'4', '3', '2', '1'}
        *************************************************************************************************/
        for(Loc_uint8Index = 0; Loc_uint8Index < Loc_uint8Count; Loc_uint8Index++)
        {
            MUART_TxChar(Copy_UARTChoice, Loc_uint8CharArray[Loc_uint8Count - Loc_uint8Index - 1]);
        }
    }

    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}

/**
 * @brief: 1) This function represents the interrupt service routine of UART 1 Peripheral.
 *         2) Inside the function, we call the corresponding pointer to the function which is set to be executed in
 *            case interrupt occurs
 */
void USART1_IRQHandler(void)
{
    if(Glbl_PRxCompleteFunc[0] != NULL_PTR)
    {
        (Glbl_PRxCompleteFunc[0])();
    }
    else
    {
        /*Do nothing*/
    }
    CLR_BIT(((UART[0]) -> SR) , MUART_SR_TC_BIT);
    CLR_BIT(((UART[0]) -> SR) , MUART_SR_RXNE_BIT);
}
/**
 * @brief: 1) This function represents the interrupt service routine of UART 2 Peripheral.
 *         2) Inside the function, we call the corresponding pointer to the function which is set to be executed in
 *            case interrupt occurs
 */
void USART2_IRQHandler(void)
{
	if(Glbl_PRxCompleteFunc[1] != NULL_PTR)
    {
        (Glbl_PRxCompleteFunc[1])();
    }
    else
    {
        /*Do nothing*/
    }
    CLR_BIT(((UART[1]) -> SR) , MUART_SR_TC_BIT);
    CLR_BIT(((UART[1]) -> SR) , MUART_SR_RXNE_BIT);

}
/**
 * @brief: 1) This function represents the interrupt service routine of UART 3 Peripheral.
 *         2) Inside the function, we call the corresponding pointer to the function which is set to be executed in
 *            case interrupt occurs
 */
void USART3_IRQHandler(void)
{
    if(Glbl_PRxCompleteFunc[2] != NULL_PTR)
    {
        (Glbl_PRxCompleteFunc[2])();
    }
    else
    {
        /*Do nothing*/
    }
    CLR_BIT(((UART[2]) -> SR) , MUART_SR_TC_BIT);
    CLR_BIT(((UART[2]) -> SR) , MUART_SR_RXNE_BIT);
}