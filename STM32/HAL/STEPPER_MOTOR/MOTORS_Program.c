/**
 * @file MOTORS_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/Std_Types.h"

#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/RCC/RCC_Interface.h"
#include "../../MCAL/STK/STK_Interface.h"
#include "../../MCAL/EXTI/EXTI_Interface.h"
#include "../../MCAL/NVIC/NVIC_Interface.h"
#include "../../MCAL/AFIO/AFIO_Interface.h"

#include "MOTORS_Config.h"
#include "MOTORS_Private.h"
#include "MOTORS_Interface.h"

#define MAFIO_MAPR_R											*((volatile uint32*)(0x40010000 + 0x04))
void HMOTOR4_HomeIndicator(void);
void HMOTOR_WLHomeIndicator(void);
void HMOTOR_FilterHomeIndicator(void);

static volatile uint8 glbl_uint8HomingIndicator[HMOTORS_NUM_MOTORS - 1] = {HMOTORS_MOTOR_NOT_AT_HOME};

void HMOTORS_Init(void)
{
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_AFIO_EN);
	MAFIO_MAPR_R &= ~((0b111) << 24);
	MAFIO_MAPR_R |= ((0b010) << 24);
	
	uint8 Loc_uint8Index = 0;
	
	for(Loc_uint8Index = 0; Loc_uint8Index < (HMOTORS_NUM_MOTORS - 2); Loc_uint8Index++)
	{
		MGPIO_SetPinMode(glbl_uint8MotorHomingPortIDs[Loc_uint8Index],\
							glbl_uint8MotorHomingPinIDs[Loc_uint8Index], MGPIO_INPUT_PULL_UP_OR_DOWN_MODE);
		MGPIO_ActivatePullUp(glbl_uint8MotorHomingPortIDs[Loc_uint8Index],\
								glbl_uint8MotorHomingPinIDs[Loc_uint8Index]);
	}
	for(Loc_uint8Index = 0; Loc_uint8Index < HMOTORS_NUM_MOTORS; Loc_uint8Index++)
	{
		MGPIO_SetPinMode(glbl_uint8MotorsStepPortIDs[Loc_uint8Index],\
							glbl_uint8MotorsStepPinIDs[Loc_uint8Index], MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    	MGPIO_SetPinMode(glbl_uint8MotorsDirPortIDs[Loc_uint8Index],\
							glbl_uint8MotorsDirPinIDs[Loc_uint8Index], MGPIO_OUTPUT_PUSH_PULL_2MHZ);
	}

	MNVIC_EnableInterrupt(MNVIC_EXTI15_10);
	MNVIC_EnableInterrupt(MNVIC_EXTI0);

	MEXTI_SetCallbackFunction(MEXTI_EXTI13, HMOTOR_FilterHomeIndicator);
	MEXTI_SetCallbackFunction(MEXTI_EXTI0, HMOTOR_WLHomeIndicator);
	
	MAFIO_SetEXTIPinConfigurations(MAFIO_EXTI13, MGPIO_PORTC);
	MAFIO_SetEXTIPinConfigurations(MAFIO_EXTI0, MGPIO_PORTA);

	MEXTI_EnableExternalInterrupt(MEXTI_EXTI13, MEXTI_INT_AT_FALLING_EDGE);
	MEXTI_EnableExternalInterrupt(MEXTI_EXTI0, MEXTI_INT_AT_FALLING_EDGE);
}

void HMOTOR_Step(HMOTORS_Select_t Copy_uint32MotorSelect, uint8 Copy_uint8NoOfSetps, uint8 Copy_uint8Direction)
{
	uint8 Loc_uint8Index = 0;
	switch(Copy_uint8Direction)
	{
		case HMOTORS_CLKWISE_DIRECTION:
		{
			MGPIO_SetPinValue(glbl_uint8MotorsDirPortIDs[Copy_uint32MotorSelect],\ 
								glbl_uint8MotorsDirPinIDs[Copy_uint32MotorSelect], MGPIO_LOW);
			break;
		}
		case HMOTORS_CCLKWISE_DIRECTION:
		{
			MGPIO_SetPinValue(glbl_uint8MotorsDirPortIDs[Copy_uint32MotorSelect],\ 
								glbl_uint8MotorsDirPinIDs[Copy_uint32MotorSelect], MGPIO_HIGH);
			break;
		}
	}
	for(Loc_uint8Index = 0; Loc_uint8Index < (Copy_uint8NoOfSetps); Loc_uint8Index++)
	{
		MGPIO_SetPinValue(glbl_uint8MotorsStepPortIDs[Copy_uint32MotorSelect],\ 
								glbl_uint8MotorsStepPinIDs[Copy_uint32MotorSelect], MGPIO_HIGH);
		
		MSTK_uint8Delay(3);
		
		MGPIO_SetPinValue(glbl_uint8MotorsStepPortIDs[Copy_uint32MotorSelect],\ 
								glbl_uint8MotorsStepPinIDs[Copy_uint32MotorSelect], MGPIO_LOW);
		
		MSTK_uint8Delay(3);
	}
}

void HMOTOR_GoHome  (HMOTORS_Select_t Copy_uint32MotorSelect)
{
	if(Copy_uint32MotorSelect > 0)
	{
		glbl_uint8HomingIndicator[(Copy_uint32MotorSelect - 1)] = HMOTORS_MOTOR_NOT_AT_HOME;

		while((glbl_uint8HomingIndicator[(Copy_uint32MotorSelect - 1)]) == HMOTORS_MOTOR_NOT_AT_HOME)
		{
			HMOTOR_Step(Copy_uint32MotorSelect, 1, HMOTORS_CCLKWISE_DIRECTION);
		}
		
		glbl_uint8HomingIndicator[(Copy_uint32MotorSelect - 1)] = HMOTORS_MOTOR_NOT_AT_HOME;
	}
	else
	{
		/*Do nothing*/
	}
}

void HMOTOR_FilterHomeIndicator(void)
{
	glbl_uint8HomingIndicator[0] = HMOTORS_MOTOR_AT_HOME;
}
void HMOTOR_WLHomeIndicator(void)
{
	glbl_uint8HomingIndicator[1] = HMOTORS_MOTOR_AT_HOME;
}
void HMOTOR4_HomeIndicator(void)
{
	glbl_uint8HomingIndicator[2] = HMOTORS_MOTOR_AT_HOME;
}