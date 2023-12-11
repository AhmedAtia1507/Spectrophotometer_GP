/**
 * @file UART_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "BIT_MATH.h"
#include "Std_Types.h"

#include "UART_Private.h"
#include "UART_Interface.h"
#include "UART_Config.h"
#include "GPIO_Interface.h"

static volatile MUART_Typedef* (UART[3]) = {MUART1, MUART2, MUART3};
static volatile ptr_to_Callback Glbl_PTxCompleteFunc[3] = {NULL_PTR};
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
    
    #if MUART_NO_OF_DATA_BITS == MUART_EIGHT_DATA_BITS
        CLR_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_M_BIT);
    #elif MUART_NO_OF_DATA_BITS == MUART_NINE_DATA_BITS
        SET_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_M_BIT);
    #else
        #error "UART No of Data Bits is not Specified Correctly"
    #endif /*MUART_NO_OF_DATA_BITS*/

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

    ((UART[Copy_UARTChoice]) -> CR2) &= ~(((uint32) 0b11) << MUART_CR2_STOP_START_BIT);
    
    #if ((MUART_NO_OF_STOP_BITS == MUART_HALF_STOP_BIT) || (MUART_NO_OF_STOP_BITS == MUART_ONE_STOP_BIT) || (MUART_NO_OF_STOP_BITS == MUART_ONE_HALF_STOP_BIT) || (MUART_NO_OF_STOP_BITS == MUART_TWO_STOP_BIT))
        ((UART[Copy_UARTChoice]) -> CR2) |= (((uint32) MUART_NO_OF_STOP_BITS) << MUART_CR2_STOP_START_BIT);
    #else
        #error "UART Number of Stop Bits not Specified"
    #endif /*MUART_NO_OF_STOP_BITS*/

    #if MUART_TX_COMPLETE_INT_STATUS == MUART_TX_COMPLETE_INT_ENABLED
        SET_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_TCIE_BIT);
    #elif MUART_TX_COMPLETE_INT_STATUS == MUART_TX_COMPLETE_INT_DISABLED
        CLR_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_TCIE_BIT);
    #else
        #error "UART Tx Complete Interrupt Status not Specified"
    #endif /*MUART_TX_COMPLETE_INT_STATUS*/

    #if MUART_RX_COMPLETE_INT_STATUS == MUART_RX_COMPLETE_INT_ENABLED
        SET_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_RXNEIE_BIT);
    #elif MUART_RX_COMPLETE_INT_STATUS == MUART_RX_COMPLETE_INT_DISABLED
        CLR_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_RXNEIE_BIT);
    #else
        #error "UART Rx Complete Interrupt Status not Specified"
    #endif /*MUART_RX_COMPLETE_INT_STATUS*/
    
    /********************Calculate Baud Rate**************************/
    float32 Loc_float32UARTDIV = (float32)MUART_CLK_FREQ / (16 * MUART_BAUD_RATE);

    uint16 Loc_uint16Mantissa = (uint16)Loc_float32UARTDIV;
    uint16 Loc_uint16Fraction = (uint16)(((Loc_float32UARTDIV - Loc_uint16Mantissa) * 16) + 0.5);

    if(Loc_uint16Fraction >= 16)
    {
        Loc_uint16Fraction -= 16;
        Loc_uint16Mantissa += 1;
    }
    ((UART[Copy_UARTChoice]) -> BRR) = (Loc_uint16Fraction << MUART_BRR_FRACTION_START_BIT) | (Loc_uint16Mantissa << MUART_BRR_MANTISSA_START_BIT);

    SET_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_TE_BIT);
    SET_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_RE_BIT);
    SET_BIT(((UART[Copy_UARTChoice]) -> CR1), MUART_CR1_UE_BIT);
		
	CLR_BIT(((UART[Copy_UARTChoice]) -> SR) , MUART_SR_TC_BIT);
    CLR_BIT(((UART[Copy_UARTChoice]) -> SR) , MUART_SR_RXNE_BIT);
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
Std_ReturnType MUART_TxChar(MUART_Select_t Copy_UARTChoice, uint16 Copy_uint16TxChar)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    /*Wait until Tx Data Register is empty*/
    while(!(GET_BIT(((UART[Copy_UARTChoice]) -> SR), MUART_SR_TXE_BIT)));

    #if MUART_NO_OF_DATA_BITS == MUART_EIGHT_DATA_BITS
        (UART[Copy_UARTChoice] -> DR) = Copy_uint16TxChar & ((uint16)(0x00FF));
    #elif MUART_NO_OF_DATA_BITS == MUART_NINE_DATA_BITS
        (UART[Copy_UARTChoice] -> DR) = Copy_uint16TxChar & ((uint16)(0x01FF));
    #else
        #error "UART Number of Data Bits not Specified"
    #endif /*MUART_NO_OF_DATA_BITS*/
    
    /*Wait while transmit is complete*/
    while(!(GET_BIT(((UART[Copy_UARTChoice]) -> SR), MUART_SR_TC_BIT)));
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
    /*Wait until Tx Data Register is empty*/
    while(!(GET_BIT(((UART[Copy_UARTChoice]) -> SR), MUART_SR_TXE_BIT)));

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
        /*Wait until there is a data ready to be received*/
        while(!(GET_BIT(((UART[Copy_UARTChoice]) -> SR), MUART_SR_RXNE_BIT)));
        CLR_BIT(((UART[Copy_UARTChoice]) -> SR) , MUART_SR_RXNE_BIT);
        
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
        Loc_uint8FuncStatus = E_OK;
        Glbl_PTxCompleteFunc[Copy_UARTChoice] = P_TxCompleteCallbackFunc;
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
        Loc_uint8FuncStatus = E_OK;
        Glbl_PRxCompleteFunc[Copy_UARTChoice] = P_RxCompleteCallbackFunc;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}

void USART1_IRQHandler(void)
{
    //if(GET_BIT(((UART[0]) -> SR), MUART_SR_TC_BIT) != 0)
    //{
	//	CLR_BIT(((UART[0]) -> SR) , MUART_SR_TC_BIT);
	//	CLR_BIT(((UART[0]) -> SR) , MUART_SR_RXNE_BIT);
    //    if(Glbl_PTxCompleteFunc[0] != NULL_PTR)
    //    {
    //        (Glbl_PTxCompleteFunc[0])();
    //    }
    //    else
    //    {
    //        /*Do nothing*/
    //    }
    //}
    //else if(GET_BIT(((UART[0]) -> SR), MUART_SR_RXNE_BIT) != 0)
    //{
	//	CLR_BIT(((UART[0]) -> SR) , MUART_SR_TC_BIT);
	//	CLR_BIT(((UART[0]) -> SR) , MUART_SR_RXNE_BIT);
    //    if(Glbl_PRxCompleteFunc[0] != NULL_PTR)
    //    {
    //        (Glbl_PRxCompleteFunc[0])();
    //    }
    //    else
    //    {
    //        /*Do nothing*/
    //    }
    //}
    //else
    //{
    //    /*Do nothing*/
    //}
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
void USART2_IRQHandler(void)
{
//    if(GET_BIT(((UART[1]) -> SR), MUART_SR_TC_BIT) != 0)
//    {
//				CLR_BIT(((UART[1]) -> SR) , MUART_SR_TC_BIT);
//				CLR_BIT(((UART[1]) -> SR) , MUART_SR_RXNE_BIT);
//        if(Glbl_PTxCompleteFunc[1] != NULL_PTR)
//        {
//            (Glbl_PTxCompleteFunc[1])();
//        }
//        else
//        {
//            /*Do nothing*/
//        }
//    }
//    else if(GET_BIT(((UART[1]) -> SR), MUART_SR_RXNE_BIT) != 0)
//    {
//				CLR_BIT(((UART[1]) -> SR) , MUART_SR_TC_BIT);
//				CLR_BIT(((UART[1]) -> SR) , MUART_SR_RXNE_BIT);
//        if(Glbl_PRxCompleteFunc[1] != NULL_PTR)
//        {
//            (Glbl_PRxCompleteFunc[1])();
//        }
//        else
//        {
//            /*Do nothing*/
//        }
//    }
//    else
//    {
//        /*Do nothing*/
//    }
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
void USART3_IRQHandler(void)
{
    //if(GET_BIT(((UART[2]) -> SR), MUART_SR_TC_BIT) != 0)
    //{
	//	CLR_BIT(((UART[2]) -> SR) , MUART_SR_TC_BIT);
	//	CLR_BIT(((UART[2]) -> SR) , MUART_SR_RXNE_BIT);
    //    if(Glbl_PTxCompleteFunc[2] != NULL_PTR)
    //    {
    //        (Glbl_PTxCompleteFunc[2])();
    //    }
    //    else
    //    {
    //        /*Do nothing*/
    //    }
    //}
    //else if(GET_BIT(((UART[2]) -> SR), MUART_SR_RXNE_BIT) != 0)
    //{
	//	CLR_BIT(((UART[2]) -> SR) , MUART_SR_TC_BIT);
	//	CLR_BIT(((UART[2]) -> SR) , MUART_SR_RXNE_BIT);
    //    if(Glbl_PRxCompleteFunc[2] != NULL_PTR)
    //    {
    //        (Glbl_PRxCompleteFunc[2])();
    //    }
    //    else
    //    {
    //        /*Do nothing*/
    //    }
    //}
    //else
    //{
    //    /*Do nothing*/
    //}
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