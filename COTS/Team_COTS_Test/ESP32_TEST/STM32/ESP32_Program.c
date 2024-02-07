/**
 * @file ESP32_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "BIT_MATH.h"
#include "Std_Types.h"

#include "RCC_Interface.h"
#include "GPIO_Interface.h"
#include "UART_Interface.h"
#include "NVIC_Interface.h"

#include "ESP32_Interface.h"
#include "ESP32_Private.h"
#include "ESP32_Config.h"

static volatile ptr_to_Callback_func glbl_PCallbackFunc[HESP32_NO_OF_TASKS - 1] = {NULL_PTR};
static volatile ptr_to_AbsCallback_func glbl_PAbsCallbackFunc[HESP32_NO_OF_ABS_TASKS] = {NULL_PTR};
static volatile uint8 glbl_uint8CommandBuffer[20] = {0};
static volatile uint8 glbl_uint8BufferIndex = 0;
static volatile uint8 glbl_uint8AbsWavelengthFlag = 0;
static volatile uint8 glbl_uint8AbsWavelengthCounter = 0;
static volatile float32 glbl_float32AbsWavelength = 0.0;

void HESP32_ParseReceivedCommand  (void)
{
    uint16 Loc_uint16RxChar = 0;
    MUART_RxCharAsynchronous(HESP32_UART_CHOICE, &Loc_uint16RxChar);
		
    if((uint8)Loc_uint16RxChar == 0x0D)
    {
        glbl_uint8CommandBuffer[glbl_uint8BufferIndex] = '\0';
        if(glbl_uint8AbsWavelengthFlag == 0)
        {
            uint8 Loc_uint8Index = 0; 
		    uint8 Loc_uint8FoundCommand = HESP32_COMMAND_NOT_FOUND;
		    uint8 Loc_uint8Compare = 0;

            for(Loc_uint8Index = 0; Loc_uint8Index < HESP32_NO_OF_TASKS; Loc_uint8Index++)
            {
		    	Loc_uint8Compare = strncmp((HESP32_AvailableTasks[Loc_uint8Index]), glbl_uint8CommandBuffer, strlen((HESP32_AvailableTasks[Loc_uint8Index])));
                if(Loc_uint8Compare == 0)
                {
                    Loc_uint8FoundCommand = HESP32_COMMAND_FOUND;
                    if(Loc_uint8Index == (HESP32_NO_OF_TASKS - 1))
                    {
                        glbl_uint8AbsWavelengthFlag = 1;
                    }
                    else
                    {
                        if((glbl_PCallbackFunc[Loc_uint8Index]) != NULL_PTR)
                        {
															HESP32_SendCommand("acknowledged");
													MUART_TxChar(UART1, 13);
                            (glbl_PCallbackFunc[Loc_uint8Index])();
                        }
                    }
		    		break;
                }
                else
		    	{
                }
            }
            glbl_uint8BufferIndex = 0;
            if(Loc_uint8FoundCommand == HESP32_COMMAND_NOT_FOUND)
            {
							HESP32_SendCommand("invalid command");
							MUART_TxChar(UART1, 13);
            }
        }
        else
        {
						if(glbl_uint8AbsWavelengthCounter == 0)
						{
								glbl_float32AbsWavelength = strtof(glbl_uint8CommandBuffer, NULL_PTR);
								glbl_uint8AbsWavelengthCounter++;
								glbl_uint8BufferIndex = 0;
						}
						else
						{
								uint8 Loc_uin8Index = 0, Loc_uint8Compare = 0;
								for(Loc_uin8Index = 0; Loc_uin8Index < HESP32_NO_OF_ABS_TASKS; Loc_uin8Index++)
								{
										Loc_uint8Compare = strncmp(glbl_uint8CommandBuffer, HESP32_AvailableAbsTasks[Loc_uin8Index], strlen(HESP32_AvailableAbsTasks[Loc_uin8Index]));
										if(Loc_uint8Compare == 0)
										{
												if(glbl_PAbsCallbackFunc[Loc_uin8Index] != NULL_PTR)
												{
													(glbl_PAbsCallbackFunc[Loc_uin8Index])(&glbl_float32AbsWavelength);
													glbl_uint8AbsWavelengthCounter++;
												}
										}
								}
								if(glbl_uint8AbsWavelengthCounter == 3)
								{
									glbl_uint8AbsWavelengthCounter = 0;
									glbl_uint8AbsWavelengthFlag = 0;
								}
								glbl_uint8BufferIndex = 0;
						}
        }
        
    }
    else
    {
        glbl_uint8CommandBuffer[glbl_uint8BufferIndex] = (uint8)(Loc_uint16RxChar);
        glbl_uint8BufferIndex++;
    }
}
/**
 * @brief: Function to initialize peripherals used in communication between
 *          ESP32 and STM32F103C8T6 
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Initialization is successful
 * @retval E_NOT_OK:    Failed to initialize communication 
 */
Std_ReturnType HESP32_InitInterface              (void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    #if HESP32_UART_CHOICE == HESP32_UART1
        //Enable Clock for UART1 and its tx and rx pins
        MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_USART1_EN);
        MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);

        //Set Tx pin to be output alternate function and rx to be input pull-up
        MGPIO_SetPinMode(MUART1_TX_PORT_ID, MUART1_TX_PIN_ID, MGPIO_OUTPUT_AF_PUSH_PULL_2MHZ);
        MGPIO_SetPinMode(MUART1_RX_PORT_ID, MUART1_RX_PIN_ID, MGPIO_INPUT_PULL_UP_OR_DOWN_MODE);
        MGPIO_ActivatePullUp(MUART1_RX_PORT_ID, MUART1_RX_PIN_ID);

        //Enable Interrupt for UART 1
        MNVIC_EnableInterrupt(MNVIC_USART1);

        MUART_SetRxCompleteCallback(UART1, HESP32_ParseReceivedCommand);
        
        //Initialize UART 1 peripheral
        MUART_Init(UART1);

    #elif HESP32_UART_CHOICE == HESP32_UART2
        //Enable Clock for UART2 and its tx and rx pins
        MRCC_EnablePeripheralClock(MRCC_APB1, MRCC_APB1_USART2_EN);
        MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);

        //Set Tx pin to be output alternate function and rx to be input pull-up
        MGPIO_SetPinMode(MUART2_TX_PORT_ID, MUART2_TX_PIN_ID, MGPIO_OUTPUT_AF_PUSH_PULL_2MHZ);
        MGPIO_SetPinMode(MUART2_RX_PORT_ID, MUART2_RX_PIN_ID, MGPIO_INPUT_PULL_UP_OR_DOWN_MODE);
        MGPIO_ActivatePullUp(MUART2_RX_PORT_ID, MUART2_RX_PIN_ID);

        //Enable Interrupt for UART 2
        MNVIC_EnableInterrupt(MNVIC_USART2);

        MUART_SetRxCompleteCallback(UART2, HESP32_ParseReceivedCommand);

        //Initialize UART 2 peripheral
        MUART_Init(UART2);
    #elif HESP32_UART_CHOICE == HESP32_UART3
        //Enable Clock for UART3 and its tx and rx pins
        MRCC_EnablePeripheralClock(MRCC_APB1, MRCC_APB1_USART3_EN);
        MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPB_EN);

        //Set Tx pin to be output alternate function and rx to be input pull-up
        MGPIO_SetPinMode(MUART3_TX_PORT_ID, MUART3_TX_PIN_ID, MGPIO_OUTPUT_AF_PUSH_PULL_2MHZ);
        MGPIO_SetPinMode(MUART3_RX_PORT_ID, MUART3_RX_PIN_ID, MGPIO_INPUT_PULL_UP_OR_DOWN_MODE);
        MGPIO_ActivatePullUp(MUART3_RX_PORT_ID, MUART3_RX_PIN_ID);

        //Enable Interrupt for UART 3
        MNVIC_EnableInterrupt(MNVIC_USART3);

        MUART_SetRxCompleteCallback(UART3, HESP32_ParseReceivedCommand);
        
        //Initialize UART 1 peripheral
        MUART_Init(UART3);
    #else
        #error "UART Choice for communication is not specified"
    #endif /*HESP32_UART_CHOICE*/
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}

Std_ReturnType HESP32_SendCommand                (uint8* P_uint8Command)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_uint8Command != NULL_PTR)
    {
        MUART_TxString(HESP32_UART_CHOICE , P_uint8Command);
        MUART_TxChar(HESP32_UART_CHOICE, '\n');
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}

Std_ReturnType HESP32_SetTaskCallbackFunction    (uint8 Copy_uint8TaskNumber,ptr_to_Callback_func P_TaskCallbackFunc)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if((Copy_uint8TaskNumber < HESP32_NO_OF_TASKS) && (P_TaskCallbackFunc != NULL_PTR))
    {
        glbl_PCallbackFunc[Copy_uint8TaskNumber] = P_TaskCallbackFunc;
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}

Std_ReturnType HESP32_SetAbsCallbackFunction    (uint8 Copy_uint8TaskNumber,ptr_to_AbsCallback_func P_AbsCallbackFunc)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if((Copy_uint8TaskNumber < HESP32_NO_OF_ABS_TASKS) && (P_AbsCallbackFunc != NULL_PTR))
    {
        glbl_PAbsCallbackFunc[Copy_uint8TaskNumber] = P_AbsCallbackFunc;
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}