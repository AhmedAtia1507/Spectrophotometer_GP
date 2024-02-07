#include "BIT_MATH.h"
#include "Std_Types.h"

#include "RCC_Interface.h"
#include "GPIO_Interface.h"
#include "AFIO_Interface.h"

#include "EXTI_Interface.h"
#include "NVIC_Interface.h"
#include "SCB_Interface.h"

void ISR_EXTI4(void)
{
	//When rising edge occurs, toggle the value of Green LED Pin
	MGPIO_TogglePinValue(MGPIO_PORTA, MGPIO_PIN7);
}
void ISR_EXTI6(void)
{
	//When falling edge occurs, set the value of Green LED pin to be high and get stuck in an infinity loop
	//MGPIO_SetPinValue(MGPIO_PORTA, MGPIO_PIN5, MGPIO_HIGH);
	MGPIO_TogglePinValue(MGPIO_PORTA, MGPIO_PIN5);
//	while(1)
//	{

//	}
}
int main(void)
{
	//We initalize clock source of microcontroller to be HSE "High Speed External"
	MRCC_InitClock();
	
	//We enable the clock of GPIO Port A & B
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);
	//MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPB_EN);
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPC_EN);
	MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN5, MGPIO_OUTPUT_PUSH_PULL_2MHZ);

//	//Set Priority grouping to "4 bits for group priority and no bits for group subpriority"
//	MSCB_SetPriorityGrouping(MSCB_PRIORITY_GROUP_4_SUB_0);

//	//Set External Interrupt 4 as the highest priority "0"
//	MNVIC_SetInterruptPriority(MNVIC_EXTI9_5, 2, 0);
//	MNVIC_SetInterruptPriority(MNVIC_EXTI4, 1, 0);

	//Enable Interrupt of External Interrupt 4 & 6
//	MNVIC_EnableInterrupt(MNVIC_EXTI9_5);
//	MNVIC_EnableInterrupt(MNVIC_EXTI4);
	MNVIC_EnableInterrupt(MNVIC_EXTI15_10);
	
	//We set the pin of the external interrupt 6 to be input pull up and the Yellow LED pin to be output
	MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN5, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
	//MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN6, MGPIO_INPUT_PULL_UP_OR_DOWN_MODE);
	//MGPIO_ActivatePullUp(MGPIO_PORTB, MGPIO_PIN6);
	
	MGPIO_SetPinMode(MGPIO_PORTC, MGPIO_PIN13, MGPIO_INPUT_PULL_UP_OR_DOWN_MODE);
	MGPIO_ActivatePullUp(MGPIO_PORTC, MGPIO_PIN13);

	//Set the pin of the external interrupt 4 to be input pull down and the green LED to be output
	//MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN4, MGPIO_INPUT_PULL_UP_OR_DOWN_MODE);
	MGPIO_SetPinMode(MGPIO_PORTC, MGPIO_PIN15, MGPIO_INPUT_PULL_UP_OR_DOWN_MODE);
	MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN7, MGPIO_OUTPUT_PUSH_PULL_2MHZ);

	//We configure the External Interrupt lines 4 and 6 to be in GPIO Port B Pin 4 and 6
	MAFIO_SetEXTIPinConfigurations(MEXTI_EXTI13, MAFIO_PORTC_PIN);
	MAFIO_SetEXTIPinConfigurations(MEXTI_EXTI15, MAFIO_PORTC_PIN);
	
	//Set the callback function of EXTI 4 and 6
	MEXTI_SetCallbackFunction(MEXTI_EXTI13, ISR_EXTI4);
	MEXTI_SetCallbackFunction(MEXTI_EXTI15, ISR_EXTI6);
	
	

	//Enable External Interrupt 6 "Interrupt occurs at falling edge"
	MEXTI_EnableExternalInterrupt(MEXTI_EXTI15, MEXTI_INT_AT_RISING_EDGE);

	//Enable External Interrupt 4 "Interrupt occurs at rising edge"
	MEXTI_EnableExternalInterrupt(MEXTI_EXTI13, MEXTI_INT_AT_FALLING_EDGE);
	
	while(1)
	{
	}
	return 0;
}
