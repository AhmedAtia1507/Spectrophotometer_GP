#include "BIT_MATH.h"
#include "Std_Types.h"

#include "RCC_Interface.h"
#include "GPIO_Interface.h"

#include "NVIC_Interface.h"

#include "UART_Interface.h"

void ISR(void)
{
    uint16 Loc_uint16RxChar = 0;
    MUART_RxCharAsynchronous(UART2, &Loc_uint16RxChar);
		MUART_TxChar(UART2, Loc_uint16RxChar);
    if(Loc_uint16RxChar == '1')
    {
        MGPIO_SetPinValue(MGPIO_PORTB, MGPIO_PIN0, MGPIO_HIGH);
        MGPIO_SetPinValue(MGPIO_PORTB, MGPIO_PIN1, MGPIO_LOW);
    }
    else if(Loc_uint16RxChar == '2')
    {
        MGPIO_SetPinValue(MGPIO_PORTB, MGPIO_PIN0, MGPIO_LOW);
        MGPIO_SetPinValue(MGPIO_PORTB, MGPIO_PIN1, MGPIO_HIGH);
    }
    else
    {
        MGPIO_SetPinValue(MGPIO_PORTB, MGPIO_PIN0, MGPIO_HIGH);
    }
}
int main(void)
{
    MRCC_InitClock();

    MRCC_EnablePeripheralClock(MRCC_APB1, MRCC_APB1_USART2_EN);
    MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);
    MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPB_EN);
    MNVIC_EnableInterrupt(MNVIC_USART2);

    MGPIO_SetPinMode(MUART2_TX_PORT_ID, MUART2_TX_PIN_ID, MGPIO_OUTPUT_AF_PUSH_PULL_2MHZ);
    MGPIO_SetPinMode(MUART2_RX_PORT_ID, MUART2_RX_PIN_ID, MGPIO_OUTPUT_AF_PUSH_PULL_2MHZ);
    MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN0, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN1, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    MUART_SetRxCompleteCallback(UART2, ISR);
    MUART_Init(UART2);

    MUART_TxString(UART2, "Hello! Welcome");
    MUART_TxString(UART2, "Please Choose One of the options");
		MUART_TxString(UART2, "1. Red LED");
	MUART_TxString(UART2, "2. Yellow LED");
    while(1)
    {

    }
    return 0;
}
