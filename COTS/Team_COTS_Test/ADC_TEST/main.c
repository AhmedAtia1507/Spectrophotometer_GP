#include "BIT_MATH.h"
#include "Std_Types.h"

#include "RCC_Interface.h"
#include "NVIC_Interface.h"
#include "GPIO_Interface.h"

#include "ADC_Interface.h"
#include "STK_Interface.h"

#include "UART_Interface.h"

void ISR_ADC(void)
{
    uint16 Loc_uint16ADCValue = 0;
    MADC_RxConvertedDataAsynchronous(MADC1, &Loc_uint16ADCValue);

    MUART_TxString(UART1, "ADC Value: ");
    MUART_SendIntegerValue(UART1, Loc_uint16ADCValue);
		MUART_TxChar(UART1, 13);
	
		//MSTK_uint8StartTimer();
}

void ISR_STK(void)
{
			MADC_StartConversion(MADC1, MADC_Channel_2);
}
int main(void)
{
    MRCC_InitClock();

    MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_ADC1_EN);
    MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);
    MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPB_EN);
		MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_USART1_EN);

		MGPIO_SetPinMode(MUART1_TX_PORT_ID, MUART1_TX_PIN_ID, MGPIO_OUTPUT_AF_PUSH_PULL_2MHZ);
	MGPIO_SetPinMode(MUART1_RX_PORT_ID, MUART1_RX_PIN_ID, MGPIO_INPUT_PULL_UP_OR_DOWN_MODE);
	MGPIO_ActivatePullUp(MUART1_RX_PORT_ID, MUART1_RX_PIN_ID);
    MUART_Init(UART1);

    MNVIC_EnableInterrupt(MNVIC_ADC1_2);
	
		
		

    MGPIO_SetPinMode(MADC_CHANNEL_2_PORT_ID, MADC_CHANNEL_2_PIN_ID, MGPIO_INPUT_ANALOG_MODE);

    MADC_SetConversionCompleteCallback(MADC1, ISR_ADC);
    MADC_Init(MADC1);
		MSTK_uint8Init();
    MSTK_uint8SetTimerDuration(3000);
    MSTK_uint8SetCallbackFunction(ISR_STK);
    MSTK_uint8StartTimer();
    while(1)
    {

    }
    return 0;
}
