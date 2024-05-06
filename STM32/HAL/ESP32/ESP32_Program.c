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
#include <stdio.h>
#include <math.h>


#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/Std_Types.h"

#include "../../MCAL/RCC/RCC_Interface.h"
#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/UART/UART_Interface.h"
#include "../../MCAL/NVIC/NVIC_Interface.h"
#include "../../MCAL/RTC/RTC_Interface.h"

#include "ESP32_Interface.h"
#include "ESP32_Private.h"
#include "ESP32_Config.h"

static volatile ptr_to_Callback_func glbl_PCallbackFunc[(HESP32_NO_OF_COMMANDS - 1)] = {NULL_PTR};

#if HESP32_NO_OF_ARG_COMMANDS == 1
    static volatile ptr_to_Arg_Callback_func glbl_PArgCallbackFunc = NULL_PTR;
#elif HESP32_NO_OF_ARG_COMMANDS > 1
    static volatile ptr_to_Arg_Callback_func glbl_PArgCallbackFunc[HESP32_NO_OF_ARG_COMMANDS] = {NULL_PTR};
#else
#endif /*HESP32_NO_OF_ARG_COMMANDS*/

static volatile uint8 glbl_uint8CommandBuffer[HESP32_MAX_BUFFER_SPACE] = {0};
static volatile uint8 glbl_uint8BufferIndex = 0;

void float_to_string_manual(uint8* P_uint8Buffer, float32 Copy_float32FloatNum, uint32 Loc_uint32precision) 
{
    uint32 Loc_uint32IntPart = 0, Loc_uint32DecimalPart = 0;
    uint32 i = 0, k = 0;
    uint8 Loc_uint8TempBuffer[8] = {0};
    boolean is_negative = FALSE;

    // Handle sign and extract integer part (modify for specific needs)
    if (Copy_float32FloatNum < 0) 
    {
        Copy_float32FloatNum = -Copy_float32FloatNum;
        is_negative = TRUE;
    }
    Loc_uint32IntPart = (sint32)Copy_float32FloatNum;

    // Handle decimal part if needed (modify for precision)
    if (Loc_uint32precision > 0) 
    {
        Copy_float32FloatNum *= pow(10, Loc_uint32precision);
        Loc_uint32DecimalPart = (uint32)Copy_float32FloatNum;
    }

    // Convert integer part to string (replace with your implementation)
    if (is_negative) 
    {
        P_uint8Buffer[i++] = '-';
    }
    do 
    {
        //buf[i++] = int_part % 10 + '0';
        Loc_uint8TempBuffer[k++] = Loc_uint32IntPart % 10 + '0';
        Loc_uint32IntPart /= 10;
    } while (Loc_uint32IntPart > 0);

    // Append sign, decimal point, and decimal digits (modify for precision)
    for(sint32 j = (k - 1); j >= 0; j--)
    {
        P_uint8Buffer[i++] = Loc_uint8TempBuffer[j];
    }

    if (Loc_uint32precision > 0) 
    {
        uint8 temp = 0;
        P_uint8Buffer[i++] = '.';
        for (sint32 j = 0; j < Loc_uint32precision; j++) 
        {
            Loc_uint8TempBuffer[j] = Loc_uint32DecimalPart % 10 + '0';
            Loc_uint32DecimalPart /= 10;
        }
        for (sint32 j = (Loc_uint32precision - 1); j >= 0; j--) 
        {
            P_uint8Buffer[i++] = Loc_uint8TempBuffer[j];
        }
    }
    P_uint8Buffer[i] = '\0'; // Null terminate the string
}

void HESP32_ParseReceivedCommand  (void)
{
    uint16 Loc_uint16RxChar = 0;
    MUART_RxCharAsynchronous(HESP32_UART_CHOICE, &Loc_uint16RxChar);
	
    if(glbl_uint8BufferIndex < HESP32_MAX_BUFFER_SPACE)
    {
        if((uint8)Loc_uint16RxChar == '\n')
        {
            glbl_uint8CommandBuffer[glbl_uint8BufferIndex] = '\0';
            
            uint8 Loc_uint8Index = 0; 
	    	uint8 Loc_uint8FoundCommand = HESP32_COMMAND_NOT_FOUND;
	    	uint8 Loc_uint8Compare = 0;

            for(Loc_uint8Index = 0; Loc_uint8Index < HESP32_NO_OF_COMMANDS; Loc_uint8Index++)
            {
	    		Loc_uint8Compare = strncmp((HESP32_AvailableTasks[Loc_uint8Index]), glbl_uint8CommandBuffer, strlen((HESP32_AvailableTasks[Loc_uint8Index])));
                if(Loc_uint8Compare == 0)
                {
                    Loc_uint8FoundCommand = HESP32_COMMAND_FOUND;
                    //HESP32_SendCommand("acknowledged");
                    
                    if(Loc_uint8Index < HESP32_NO_OF_NON_ARG_COMMANDS)
                    {
                        if((glbl_PCallbackFunc[Loc_uint8Index]) != NULL_PTR)
                        {
                            (glbl_PCallbackFunc[Loc_uint8Index])();
                        }
                    }
                    else
                    {
                        #if HESP32_NO_OF_ARG_COMMANDS == 1
                            if(glbl_PArgCallbackFunc != NULL_PTR)
                            {
                                glbl_PArgCallbackFunc((glbl_uint8CommandBuffer + strlen((HESP32_AvailableTasks[Loc_uint8Index])) + 1));
                            }
                        #elif HESP32_NO_OF_ARG_COMMANDS > 1
                            if((glbl_PArgCallbackFunc[Loc_uint8Index - HESP32_NO_OF_NON_ARG_COMMANDS]) != NULL_PTR)
                            {
                                (glbl_PArgCallbackFunc[Loc_uint8Index - HESP32_NO_OF_NON_ARG_COMMANDS])((glbl_uint8CommandBuffer + strlen((HESP32_AvailableTasks[Loc_uint8Index])) + 1));
                            }
                        #else
                        #endif /*HESP32_NO_OF_ARG_COMMANDS*/
                    }
	    			break;
                }
                else
	    		{
                    /*Do nothing*/
                }
            }
            glbl_uint8BufferIndex = 0;
            if(Loc_uint8FoundCommand == HESP32_COMMAND_NOT_FOUND)
            {
	    		//HESP32_SendCommand("invalid command");
            }
            else
            {
	    		/*Do nothing*/
            }
        }
        else
        {
            glbl_uint8CommandBuffer[glbl_uint8BufferIndex] = (uint8)(Loc_uint16RxChar);
            glbl_uint8BufferIndex++;
        }
    }
    else
    {
        glbl_uint8BufferIndex = 0;
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

Std_ReturnType HESP32_SetCommandCallbackFunction    (uint8 Copy_uint8CommandNumber,ptr_to_Callback_func P_CommandCallbackFunc)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if((Copy_uint8CommandNumber < HESP32_NO_OF_COMMANDS) && (P_CommandCallbackFunc != NULL_PTR))
    {
        glbl_PCallbackFunc[Copy_uint8CommandNumber] = P_CommandCallbackFunc;
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}

Std_ReturnType HESP32_SetCommandCallbackArgFunction (uint8 Copy_uint8CommandNumber, ptr_to_Arg_Callback_func P_CommandCallbackFunc)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if((Copy_uint8CommandNumber < HESP32_NO_OF_COMMANDS) && (P_CommandCallbackFunc != NULL_PTR))
    {
        #if HESP32_NO_OF_ARG_COMMANDS == 1
            glbl_PArgCallbackFunc = P_CommandCallbackFunc;
        #elif HESP32_NO_OF_ARG_COMMANDS > 1
            glbl_PArgCallbackFunc[Copy_uint8CommandNumber - HESP32_NO_OF_NON_ARG_COMMANDS] = P_CommandCallbackFunc;
        #else
        #endif /*HESP32_NO_OF_ARG_COMMANDS*/
        
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}

Std_ReturnType HESP32_SendMotorStatus               (uint32* P_uint32MotorSteps, uint32* P_uint32CurrentWL, uint8 Copy_uint8MotorNum)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if((P_uint32MotorSteps != NULL_PTR) && (P_uint32CurrentWL != NULL_PTR) && ((Copy_uint8MotorNum == 1) || (Copy_uint8MotorNum == 3)))
    {
        uint8 Loc_uint8Index = 0;
        for(Loc_uint8Index = 0; Loc_uint8Index < Copy_uint8MotorNum; Loc_uint8Index++)
        {
            MUART_SendIntegerValue(HESP32_UART_CHOICE, P_uint32MotorSteps[Loc_uint8Index]);
            if((Loc_uint8Index < 2) && (Copy_uint8MotorNum == 3))
            {
                MUART_TxChar(HESP32_UART_CHOICE, '-');
            }
			else
			{
				break;
			}
        }
        if(Copy_uint8MotorNum == 3)
        {
			MUART_TxChar(HESP32_UART_CHOICE, '-');
            MUART_SendIntegerValue(HESP32_UART_CHOICE, *P_uint32CurrentWL);
        }
        MUART_TxChar(HESP32_UART_CHOICE, '\n');
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
Std_ReturnType HESP32_SendDateTime                  (Sdate_t* P_SDateToBeSent, Stime_t* P_STimeToBeSent)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    if((P_SDateToBeSent != NULL_PTR) && (P_STimeToBeSent != NULL_PTR))
    {
        MUART_SendIntegerValue(HESP32_UART_CHOICE,(uint32)(P_SDateToBeSent -> m_months));
        MUART_TxChar(HESP32_UART_CHOICE, '/');
        MUART_SendIntegerValue(HESP32_UART_CHOICE,(uint32)(P_SDateToBeSent -> m_days));
        MUART_TxChar(HESP32_UART_CHOICE, '/');
        MUART_SendIntegerValue(HESP32_UART_CHOICE,(uint32)(P_SDateToBeSent -> m_years));
        MUART_TxChar(HESP32_UART_CHOICE, ' ');
        
        MUART_SendIntegerValue(HESP32_UART_CHOICE,(uint32)(P_STimeToBeSent -> m_hours));
        MUART_TxChar(HESP32_UART_CHOICE, ':');
        MUART_SendIntegerValue(HESP32_UART_CHOICE,(uint32)(P_STimeToBeSent -> m_minutes));
        MUART_TxChar(HESP32_UART_CHOICE, ':');
        MUART_SendIntegerValue(HESP32_UART_CHOICE,(uint32)(P_STimeToBeSent -> m_seconds));
        MUART_TxChar(HESP32_UART_CHOICE, '\n');
        
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }

    return Loc_uint8FuncStatus;
}

Std_ReturnType HESP32_SendIntensities\               
    (float32 Copy_float32CurrentWL ,float32 P_float32RefIntensity, float32 P_float32SampleIntensity, Sdate_t* P_SCurrentDate, Stime_t* P_SCurrentTime)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if((P_SCurrentDate != NULL_PTR) && (P_SCurrentTime != NULL_PTR))
    {
        uint8 Loc_uint8IntensityBuffer[32] = {0};
        MUART_SendIntegerValue(HESP32_UART_CHOICE,(uint32)(P_SCurrentDate -> m_months));
        MUART_TxChar(HESP32_UART_CHOICE, '/');
        MUART_SendIntegerValue(HESP32_UART_CHOICE,(uint32)(P_SCurrentDate -> m_days));
        MUART_TxChar(HESP32_UART_CHOICE, '/');
        MUART_SendIntegerValue(HESP32_UART_CHOICE,(uint32)(P_SCurrentDate -> m_years));
        MUART_TxString(HESP32_UART_CHOICE, "||");

        MUART_SendIntegerValue(HESP32_UART_CHOICE,(uint32)(P_SCurrentTime -> m_hours));
        MUART_TxChar(HESP32_UART_CHOICE, ':');
        MUART_SendIntegerValue(HESP32_UART_CHOICE,(uint32)(P_SCurrentTime -> m_minutes));
        MUART_TxChar(HESP32_UART_CHOICE, ':');
        MUART_SendIntegerValue(HESP32_UART_CHOICE,(uint32)(P_SCurrentTime -> m_seconds));
        MUART_TxChar(HESP32_UART_CHOICE, ' ');

        //snprintf(Loc_uint8IntensityBuffer, sizeof(Loc_uint8IntensityBuffer), "%f", Copy_float32CurrentWL);
        float_to_string_manual(Loc_uint8IntensityBuffer, Copy_float32CurrentWL, 3);
        MUART_TxString(HESP32_UART_CHOICE, Loc_uint8IntensityBuffer);
        MUART_TxChar(HESP32_UART_CHOICE, ' ');
        //snprintf(Loc_uint8IntensityBuffer, sizeof(Loc_uint8IntensityBuffer), "%f", *P_float32RefIntensity);
        float_to_string_manual(Loc_uint8IntensityBuffer, P_float32RefIntensity, 3);
        MUART_TxString(HESP32_UART_CHOICE, Loc_uint8IntensityBuffer);
        MUART_TxChar(HESP32_UART_CHOICE, ' ');
        //snprintf(Loc_uint8IntensityBuffer, sizeof(Loc_uint8IntensityBuffer), "%f", *P_float32SampleIntensity);
        float_to_string_manual(Loc_uint8IntensityBuffer, P_float32SampleIntensity, 3);
        MUART_TxString(HESP32_UART_CHOICE, Loc_uint8IntensityBuffer);
        
        
        MUART_TxChar(HESP32_UART_CHOICE, '\n');
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}

Std_ReturnType HESP32_SendVoltages(uint8 PP_uint8Voltages[][32])
{
    if(PP_uint8Voltages != NULL_PTR)
    {
        uint8 Loc_uint8Index = 0;
        for(Loc_uint8Index = 0; Loc_uint8Index < 5; Loc_uint8Index++)
        {
            MUART_TxString(HESP32_UART_CHOICE, PP_uint8Voltages[Loc_uint8Index]);
            if(Loc_uint8Index < 4)
            {
                MUART_TxChar(HESP32_UART_CHOICE, ' ');
            }
        }
        MUART_TxChar(HESP32_UART_CHOICE, '\n');
        return E_OK;

    }
    else
    {
        return E_NOT_OK;
    }
}

Std_ReturnType HESP32_SendDetectorValues(float32* P_float32Readings, float32* P_float32GainValues)
{
    if((P_float32GainValues != NULL_PTR) && (P_float32Readings != NULL_PTR))
    {
        uint8 Loc_uint8Index = 0;
        uint8 Loc_uint8DetBuffer[32] = {0};
        for(Loc_uint8Index = 0; Loc_uint8Index < 1; Loc_uint8Index++)
        {
            float_to_string_manual(Loc_uint8DetBuffer, P_float32Readings[Loc_uint8Index], 3);
            MUART_TxString(HESP32_UART_CHOICE, Loc_uint8DetBuffer);
            MUART_TxChar(HESP32_UART_CHOICE, ' ');
        }
        for(Loc_uint8Index = 0; Loc_uint8Index < 1; Loc_uint8Index++)
        {
            float_to_string_manual(Loc_uint8DetBuffer, P_float32GainValues[Loc_uint8Index], 3);
            MUART_TxString(HESP32_UART_CHOICE, Loc_uint8DetBuffer);
            if(Loc_uint8Index < 1)
            {
                MUART_TxChar(HESP32_UART_CHOICE, ' ');
            }
        }
        MUART_TxChar(HESP32_UART_CHOICE, '\n');
        return E_OK;
    }
    else
    {
        return E_NOT_OK;
    }
}












//if(glbl_uint8AbsWavelengthCounter == 0)
	    		//{
	    		//	glbl_float32AbsWavelength = atof(glbl_uint8CommandBuffer);
	    		//	glbl_uint8AbsWavelengthCounter++;
	    		//	glbl_uint8BufferIndex = 0;
	    		//}
	    		//else
	    		//{
	    		//	uint8 Loc_uint8Index = 0, Loc_uint8Compare = 0;
	    		//	for(Loc_uint8Index = 0; Loc_uint8Index < HESP32_NO_OF_ABS_TASKS; Loc_uint8Index++)
	    		//	{
	    		//		Loc_uint8Compare = strncmp(glbl_uint8CommandBuffer, HESP32_AvailableAbsTasks[Loc_uint8Index], strlen(HESP32_AvailableAbsTasks[Loc_uint8Index]));
	    		//		if(Loc_uint8Compare == 0)
	    		//		{
	    		//			if(glbl_PAbsCallbackFunc[Loc_uint8Index] != NULL_PTR)
	    		//			{
                //                //snprintf
	    		//				(glbl_PAbsCallbackFunc[Loc_uint8Index])(&glbl_float32AbsWavelength);
	    		//				glbl_uint8AbsWavelengthCounter++;
	    		//			}
	    		//		}
	    		//	}
	    		//	if(glbl_uint8AbsWavelengthCounter == 3)
	    		//	{
	    		//		glbl_uint8AbsWavelengthCounter = 0;
	    		//		glbl_uint8AbsWavelengthFlag = 0;
	    		//	}
	    		//	glbl_uint8BufferIndex = 0;
	    		//}