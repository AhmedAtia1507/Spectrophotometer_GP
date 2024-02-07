#include "BIT_MATH.h"
#include "Std_Types.h"

#include "RCC_Interface.h"
#include "GPIO_Interface.h"

#include "NVIC_Interface.h"

#include "UART_Interface.h"

static volatile uint8 commands[2][20] = {
																						"turn on led 1",
																						"turn off led 1",
																						"turn on led 2",
																						"turn off led 2"
};

static volatile uint8 RxCommand[20] = {0};
void RxString(void)
{
		uint16 Loc_uint16RxChar = 0;
		MUART_RxCharAsynchronous(UART1, &Loc_uint16RxChar);
}

//#define MAFIO_BASE_ADDRESS	0x40010000U
//#define MAFIO_MAPR_R			(*(volatile uint32*)(MAFIO_BASE_ADDRESS + 0x04))
//#define MAFIO_MAPR_UART1_REMAP_BIT		2
//void ISR(void)
//{
//    uint16 Loc_uint16RxChar = 0;
//    MUART_RxCharAsynchronous(UART1, &Loc_uint16RxChar);
//	MUART_TxChar(UART1, Loc_uint16RxChar);
//    if(Loc_uint16RxChar == '1')
//    {
//        MGPIO_SetPinValue(MGPIO_PORTB, MGPIO_PIN0, MGPIO_HIGH);
//        MGPIO_SetPinValue(MGPIO_PORTB, MGPIO_PIN1, MGPIO_LOW);
//		MUART_TxString(UART1, "Red LED Successfully Turned On");
//    }
//    else if(Loc_uint16RxChar == '2')
//    {
//        MGPIO_SetPinValue(MGPIO_PORTB, MGPIO_PIN0, MGPIO_LOW);
//        MGPIO_SetPinValue(MGPIO_PORTB, MGPIO_PIN1, MGPIO_HIGH);
//		MUART_TxString(UART1, "Yellow LED Successfully Turned On");
//    }
//    else
//    {
//        /*Do nothing*/
//    }
//}
//int main(void)
//{
//	//We initialize the clock of the microcontroller
//    MRCC_InitClock();

//	//Then, we enable the clocks of the peripherals UART1, GPIO Port A & GPIO Port B 
//    MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_USART1_EN);
//    MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);
//    MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPB_EN);
//		MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_AFIO_EN);
//	
//		MAFIO_MAPR_R |= (1 << MAFIO_MAPR_UART1_REMAP_BIT);
//	//Then, We Enable Interrupt of UART 1 "If a character is received through the serial port, an interrupt is generated"
//    MNVIC_EnableInterrupt(MNVIC_USART1);

//	//We configure the direction of UART Pins "Tx pin --> Output Push-Pull" "Rx pin ---> Input Pull Up"
////    MGPIO_SetPinMode(MUART1_TX_PORT_ID, MUART1_TX_PIN_ID, MGPIO_OUTPUT_AF_PUSH_PULL_2MHZ);
////    MGPIO_SetPinMode(MUART1_RX_PORT_ID, MUART1_RX_PIN_ID, MGPIO_INPUT_PULL_UP_OR_DOWN_MODE);
////	MGPIO_ActivatePullUp(MUART1_RX_PORT_ID, MUART1_RX_PIN_ID);
//		MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN6, MGPIO_OUTPUT_AF_PUSH_PULL_2MHZ);
//    MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN7, MGPIO_INPUT_PULL_UP_OR_DOWN_MODE);
//	MGPIO_ActivatePullUp(MGPIO_PORTB, MGPIO_PIN7);

//	//We configure the direction of LED Pins as output push pull
//    MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN0, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
//    MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN1, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
//    MUART_SetRxCompleteCallback(UART1, ISR);
//    MUART_Init(UART1);

//    while(1)
//    {

//    }
//    return 0;
//}