#include "UART_Interface.h"
#include "UART_Config.h"
#include "RCC_Interface.h"
#include "GPIO_Interface.h"

int main()
{
	MRCC_InitClock();
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_USART1_EN);

	MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN9, MGPIO_OUTPUT_AF_PUSH_PULL_2MHZ);
	MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN10, MGPIO_INPUT_FLOATING_MODE);
	MUART_Init(UART1);
	uint8 a[] = "1-9-2-18-9\n";


	while(1)
	{
		MUART_TxString(UART1, a);
	}
}
