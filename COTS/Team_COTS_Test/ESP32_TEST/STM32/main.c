#include "BIT_MATH.h"
#include "Std_Types.h"

#include "RCC_Interface.h"
#include "GPIO_Interface.h"
#include "NVIC_Interface.h"
#include "UART_Interface.h"
#include "STK_Interface.h"

#include "ESP32_Interface.h"

void uv_LED_On(void)
{
		MGPIO_SetPinValue(MGPIO_PORTA, MGPIO_PIN5, MGPIO_HIGH);
		HESP32_SendCommand("UV Led Successfully turned on");
		MUART_TxChar(UART1, 13);
}
void uv_LED_Off(void)
{
		MGPIO_SetPinValue(MGPIO_PORTA, MGPIO_PIN5, MGPIO_LOW);
		HESP32_SendCommand("UV Led Successfully turned off");
		MUART_TxChar(UART1, 13);
}
void vis_LED_On(void)
{
		MGPIO_SetPinValue(MGPIO_PORTA, MGPIO_PIN4, MGPIO_HIGH);
		HESP32_SendCommand("Visible Led Successfully turned on");
		MUART_TxChar(UART1, 13);
}
void vis_LED_Off(void)
{
		MGPIO_SetPinValue(MGPIO_PORTA, MGPIO_PIN4, MGPIO_LOW);
		HESP32_SendCommand("Visible Led Successfully turned off");
	MUART_TxChar(UART1, 13);
}
void uv_status(void)
{
		uint8 Loc_uint8UvStatus = 0;
		MGPIO_GetPinValue(MGPIO_PORTA, MGPIO_PIN5, &Loc_uint8UvStatus);
		switch(Loc_uint8UvStatus)
		{
			case MGPIO_HIGH:
			{
				HESP32_SendCommand("on");
				break;
			}
			case MGPIO_LOW:
			{
				HESP32_SendCommand("off");
				break;
			}
		}
}
void vis_status(void)
{
		uint8 Loc_uint8UvStatus = 0;
		MGPIO_GetPinValue(MGPIO_PORTA, MGPIO_PIN4, &Loc_uint8UvStatus);
		switch(Loc_uint8UvStatus)
		{
			case MGPIO_HIGH:
			{
				HESP32_SendCommand("on");
				break;
			}
			case MGPIO_LOW:
			{
				HESP32_SendCommand("off");
				break;
			}
		}
}
void wavelength(void)
{
	HESP32_SendCommand("1000");
}
void Abs_Check_1(float32* P_float32RxAbs)
{
		if(P_float32RxAbs != NULL_PTR)
		{
				HESP32_SendCommand("17.23");
		}
		else
		{
		}
}
void Abs_Check_2(float32* P_float32RxAbs)
{
		if(P_float32RxAbs != NULL_PTR)
		{
				HESP32_SendCommand("30.94");
		}
		else
		{
		}
}
int main(void)
{
    MRCC_InitClock();
		MRCC_EnablePeripheralClock(MRCC_APB2,MRCC_APB2_IOPA_EN);
    //UV LED
    MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN5, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    
    //VIS LED
    MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN4, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
		
    HESP32_SetTaskCallbackFunction(6, uv_LED_On);
    //HESP32_SetTaskCallbackFunction(0, uv_LED_On);
    HESP32_SetTaskCallbackFunction(7, vis_LED_On);
    HESP32_SetTaskCallbackFunction(8, wavelength);
		HESP32_SetTaskCallbackFunction(1, uv_LED_Off);
	HESP32_SetTaskCallbackFunction(2, vis_LED_Off);
    HESP32_SetTaskCallbackFunction(0, uv_status);
    //HESP32_SetTaskCallbackFunction(5, vis_status);
    HESP32_SetAbsCallbackFunction(0, Abs_Check_1);
		HESP32_SetAbsCallbackFunction(1, Abs_Check_2);
    HESP32_InitInterface();
    while(1)
    {

    }
}
