/**
 * @file main.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: C main to test the GPIO & RCC Drivers functionality
 * @version 1.0
 * @date 2023-11-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "LIB/BIT_MATH.h"
#include "LIB/Std_Types.h"

#include "MCAL/RCC/RCC_Interface.h"
#include "MCAL/GPIO/GPIO_Interface.h"
#include "MCAL/TIM2_5/TIM2_5_Interface.h"
#include "MCAL/NVIC/NVIC_Interface.h"

int i = 1;
int interrupt_flag = 0;

int main(void)
{
//	MRCC_u8InitClock();
//	MRCC_u8EnablePeripheralClock(RCC_APB2, RCC_APB2_IOPA_EN);
//	MGPIO_u8SetPinMode(GPIO_PORTA, GPIO_PIN0, GPIO_OUTPUT_PUSH_PULL_2MHZ);
//	MGPIO_u8SetPinValue(GPIO_PORTA, GPIO_PIN0, 0);
//	MGPIO_u8SetPinValue(GPIO_PORTA, GPIO_PIN0, 1);
//	int i;
//	while(1)
//	{
//		MGPIO_u8SetPinValue(GPIO_PORTA, GPIO_PIN0, 1);
//		for(i = 0; i < 2000; i++);
//		MGPIO_u8SetPinValue(GPIO_PORTA, GPIO_PIN0, 0);
//		for(i = 0; i < 2000; i++);
//	}

	MRCC_u8InitClock();
	MRCC_u8EnablePeripheralClock(RCC_APB1, RCC_APB1_TIM2_EN);
	MRCC_u8EnablePeripheralClock(RCC_APB2, RCC_APB2_IOPA_EN);
	MGPIO_u8SetPinMode(GPIO_PORTA, GPIO_PIN0, GPIO_OUTPUT_PUSH_PULL_2MHZ);
	MNVIC_u8EnableInterrupt(NVIC_TIM2);
	TIM2->PSC = 1;				// prescaller = 2
	TIM2->DIER |= (1<<0);		// UIE enabled
	TIM2->ARR = 4000;
	interrupt_flag = 0;
	TIM2->CNT = 0;						// counter value = 0;
	TIM2->CR1 |= (1 << 0);				// CEN = 1 counter enable
	MGPIO_u8SetPinValue(GPIO_PORTA, GPIO_PIN0, 1);
	while(!interrupt_flag);
	TIM2->CR1 &= ~(1<<0);				// CEN = 0 counter disable

	while(1)
	{

		if(i == 0)
		{
			i++;
		}
		else
		{
			i--;
		}
	}

}

void TIM2_IRQHandler()
{
	interrupt_flag = 1;
	MGPIO_u8SetPinValue(GPIO_PORTA, GPIO_PIN0, 0);
	TIM2->SR &= ~(1<<0);		// clear UIF flag bit;
}
