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

#include "../EEPROM/I2C_Slave_EEPROM.h"

#include "MOTORS_Config.h"
#include "MOTORS_Private.h"
#include "MOTORS_Interface.h"

#define MAFIO_MAPR_R													*((volatile uint32*)(0x40010000 + 0x04))

static volatile uint32 glbl_uint32MotorSteps    [HMOTORS_NUM_MOTORS]    = {0};
static volatile float32 glbl_float32CurrentWL              				= 0.0;
static volatile uint8 glbl_uint8HomingIndicator	[HMOTORS_NUM_MOTORS] 	= {HMOTORS_MOTOR_NOT_AT_HOME, HMOTORS_MOTOR_NOT_AT_HOME, HMOTORS_MOTOR_NOT_AT_HOME, HMOTORS_MOTOR_NOT_AT_HOME};
static volatile uint32 glbl_uint32FilterInitCalibration 				= 28;
static volatile uint32 glbl_uint32ZeroWLSteps							= 120;
static volatile uint32 glbl_uint32StepsPerNm							= 5;

Std_ReturnType HMOTORS_Init(void)
{
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_AFIO_EN);
	MAFIO_MAPR_R &= ~((0b111) << 24);
	MAFIO_MAPR_R |= ((0b010) << 24);
	
	uint8 Loc_uint8Index = 0;
	
	for(Loc_uint8Index = 0; Loc_uint8Index < (HMOTORS_NUM_MOTORS - 1); Loc_uint8Index++)
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

	//GET FIRST VALUE OF FILTER CALIBRATION
	eeprom_read_byte(EEPROM_MOTOR_STEPS_MEM_ADDRESS, &glbl_uint32FilterInitCalibration, 4);

	return E_OK;
}

Std_ReturnType HMOTOR_Step(HMOTORS_Select_t Copy_uint32MotorSelect, uint32 Copy_uint32NoOfSetps, uint8 Copy_uint8Direction, uint8 Copy_uint8MotorSpeed)
{
	Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

	uint32 Loc_uint32Index = 0;
	switch(Copy_uint8Direction)
	{
		case HMOTORS_CLKWISE_DIRECTION:
		{
			MGPIO_SetPinValue(glbl_uint8MotorsDirPortIDs[Copy_uint32MotorSelect],\ 
								glbl_uint8MotorsDirPinIDs[Copy_uint32MotorSelect], MGPIO_HIGH);
			Loc_uint8FuncStatus = E_OK;
			break;
		}
		case HMOTORS_CCLKWISE_DIRECTION:
		{
			MGPIO_SetPinValue(glbl_uint8MotorsDirPortIDs[Copy_uint32MotorSelect],\ 
								glbl_uint8MotorsDirPinIDs[Copy_uint32MotorSelect], MGPIO_LOW);
			Loc_uint8FuncStatus = E_OK;
		
			break;
		}
		default:
		{
			Loc_uint8FuncStatus = E_NOT_OK;
		}
	}
	for(Loc_uint32Index = 0; Loc_uint32Index < (Copy_uint32NoOfSetps); Loc_uint32Index++)
	{
		MGPIO_SetPinValue(glbl_uint8MotorsStepPortIDs[Copy_uint32MotorSelect],\ 
								glbl_uint8MotorsStepPinIDs[Copy_uint32MotorSelect], MGPIO_HIGH);
		
		MSTK_uint8Delay(Copy_uint8MotorSpeed / 2);
		
		MGPIO_SetPinValue(glbl_uint8MotorsStepPortIDs[Copy_uint32MotorSelect],\ 
								glbl_uint8MotorsStepPinIDs[Copy_uint32MotorSelect], MGPIO_LOW);
		
		MSTK_uint8Delay(Copy_uint8MotorSpeed / 2);
		if(Copy_uint8Direction == HMOTORS_CLKWISE_DIRECTION)
		{
			glbl_uint32MotorSteps[Copy_uint32MotorSelect] ++;
		}
		else if(Copy_uint8Direction == HMOTORS_CCLKWISE_DIRECTION)
		{
			glbl_uint32MotorSteps[Copy_uint32MotorSelect] --;
		}
		else
		{
			Loc_uint8FuncStatus = E_NOT_OK;
		}
	}
	return Loc_uint8FuncStatus;
}

// lamp motor
Std_ReturnType HMOTOR_MoveLampMotor(HMOTOR_Lamp_Select_t Copy_uint32LampSelect)
{
	switch(Copy_uint32LampSelect)
	{
		case HMOTOR_LAMP_UV:
		{
			if(glbl_uint32MotorSteps[HMOTOR_LAMP_SELECT] != 0)
			{
				HMOTOR_GoHome(HMOTOR_LAMP_SELECT);
			}
			else
			{
				/*Do nothing*/
			}
			break;
		}
		case HMOTOR_LAMP_VIS:
		{
			if(glbl_uint32MotorSteps[HMOTOR_LAMP_SELECT] != 100)
			{
				HMOTOR_Step(HMOTOR_LAMP_SELECT, 100, HMOTORS_CCLKWISE_DIRECTION, 10);
				glbl_uint32MotorSteps[HMOTOR_LAMP_SELECT] = 100;
				glbl_uint8HomingIndicator[HMOTOR_LAMP_SELECT] = HMOTORS_MOTOR_NOT_AT_HOME;
			}
			else
			{
				/*Do nothing*/
			}
			break;
		}
		default:
		{
			return E_NOT_OK;
			break;
		}
	}
	return E_OK;
}

//filter wheel
Std_ReturnType HMOTOR_MoveFilterMotor(HMOTOR_Filter_Select_t Copy_uint32FilterSelect)
{
	uint32 Loc_uint32StepsDifference = 0;
	switch(Copy_uint32FilterSelect)
	{
		case HMOTOR_FILTER_AIR:
		{
			if(glbl_uint32MotorSteps[1] > glbl_uint32FilterInitCalibration)
			{
				Loc_uint32StepsDifference = glbl_uint32MotorSteps[1] - glbl_uint32FilterInitCalibration;
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CLKWISE_DIRECTION, 10);
			}
			else if(glbl_uint32MotorSteps[1] < glbl_uint32FilterInitCalibration)
			{
				Loc_uint32StepsDifference = glbl_uint32FilterInitCalibration - glbl_uint32MotorSteps[1];
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CCLKWISE_DIRECTION, 10); 
			}
			break;
		}
		case HMOTOR_FILTER_1:
		{
			if(glbl_uint32MotorSteps[1] > (glbl_uint32FilterInitCalibration + 50))
			{
				Loc_uint32StepsDifference = glbl_uint32MotorSteps[1] - (glbl_uint32FilterInitCalibration + 50);
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CLKWISE_DIRECTION, 10);
			}
			else if(glbl_uint32MotorSteps[1] < (glbl_uint32FilterInitCalibration + 50))
			{
				Loc_uint32StepsDifference = (glbl_uint32FilterInitCalibration + 50) - glbl_uint32MotorSteps[1];
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CCLKWISE_DIRECTION, 10); 
			}
			break;
		}
		case HMOTOR_FILTER_2:
		{
			if(glbl_uint32MotorSteps[1] > (glbl_uint32FilterInitCalibration + 100))
			{
				Loc_uint32StepsDifference = glbl_uint32MotorSteps[1] - (glbl_uint32FilterInitCalibration + 100);
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CLKWISE_DIRECTION, 10);
			}
			else if(glbl_uint32MotorSteps[1] < (glbl_uint32FilterInitCalibration + 100))
			{
				Loc_uint32StepsDifference = (glbl_uint32FilterInitCalibration + 100) - glbl_uint32MotorSteps[1];
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CCLKWISE_DIRECTION, 10); 
			}
			break;
		}
		case HMOTOR_FILTER_3:
		{
			if(glbl_uint32MotorSteps[1] > (glbl_uint32FilterInitCalibration + 150))
			{
				Loc_uint32StepsDifference = glbl_uint32MotorSteps[1] - (glbl_uint32FilterInitCalibration + 150);
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CLKWISE_DIRECTION, 10);
			}
			else if(glbl_uint32MotorSteps[1] < (glbl_uint32FilterInitCalibration + 150))
			{
				Loc_uint32StepsDifference = (glbl_uint32FilterInitCalibration + 150) - glbl_uint32MotorSteps[1];
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CCLKWISE_DIRECTION, 10); 
			}
			break;
		}
		case HMOTOR_FILTER_4:
		{
			if(glbl_uint32MotorSteps[1] > (glbl_uint32FilterInitCalibration + 200))
			{
				Loc_uint32StepsDifference = glbl_uint32MotorSteps[1] - (glbl_uint32FilterInitCalibration + 200);
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CLKWISE_DIRECTION, 10);
			}
			else if(glbl_uint32MotorSteps[1] < (glbl_uint32FilterInitCalibration + 200))
			{
				Loc_uint32StepsDifference = (glbl_uint32FilterInitCalibration + 200) - glbl_uint32MotorSteps[1];
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CCLKWISE_DIRECTION, 10); 
			}
			break;
		}
		case HMOTOR_FILTER_5:
		{
			if(glbl_uint32MotorSteps[1] > (glbl_uint32FilterInitCalibration + 250))
			{
				Loc_uint32StepsDifference = glbl_uint32MotorSteps[1] - (glbl_uint32FilterInitCalibration + 250);
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CLKWISE_DIRECTION, 10);
			}
			else if(glbl_uint32MotorSteps[1] < (glbl_uint32FilterInitCalibration + 250))
			{
				Loc_uint32StepsDifference = (glbl_uint32FilterInitCalibration + 250) - glbl_uint32MotorSteps[1];
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CCLKWISE_DIRECTION, 10); 
			}
			break;
		}
		case HMOTOR_FILTER_6:
		{
			if(glbl_uint32MotorSteps[1] > (glbl_uint32FilterInitCalibration + 300))
			{
				Loc_uint32StepsDifference = glbl_uint32MotorSteps[1] - (glbl_uint32FilterInitCalibration + 300);
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CLKWISE_DIRECTION, 10);
			}
			else if(glbl_uint32MotorSteps[1] < (glbl_uint32FilterInitCalibration + 300))
			{
				Loc_uint32StepsDifference = (glbl_uint32FilterInitCalibration + 300) - glbl_uint32MotorSteps[1];
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CCLKWISE_DIRECTION, 10); 
			}
			break;
		}
		case HMOTOR_FILTER_7:
		{
			if(glbl_uint32MotorSteps[1] > (glbl_uint32FilterInitCalibration + 350))
			{
				Loc_uint32StepsDifference = glbl_uint32MotorSteps[1] - (glbl_uint32FilterInitCalibration + 350);
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CLKWISE_DIRECTION, 10);
			}
			else if(glbl_uint32MotorSteps[1] < (glbl_uint32FilterInitCalibration + 350))
			{
				Loc_uint32StepsDifference = (glbl_uint32FilterInitCalibration + 350) - glbl_uint32MotorSteps[1];
				HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CCLKWISE_DIRECTION, 10); 
			}
			break;
		}
		default:
		{
			return E_NOT_OK;
			break;
		}
	}
	glbl_uint8HomingIndicator[HMOTOR_FILTER_SELECT] = HMOTORS_MOTOR_NOT_AT_HOME;
	return E_OK;
}

Std_ReturnType HMOTOR_GetWLSelectCalibration            (uint32 Copy_uint32ZeroWLSteps, uint32 Copy_uint32StepsPerNm)
{
	glbl_uint32ZeroWLSteps = Copy_uint32ZeroWLSteps;
	glbl_uint32StepsPerNm = Copy_uint32StepsPerNm;
	return E_OK;
}

Std_ReturnType HMOTOR_MoveWLSelectMotor                 (float32 Copy_float32NextWL)
{
	if((Copy_float32NextWL > -0.01f) && (Copy_float32NextWL < 0.01f))
	{
		if(glbl_uint32MotorSteps[3] > glbl_uint32ZeroWLSteps)
		{
			HMOTOR_Step(HMOTOR_WL_SELECT, (glbl_uint32MotorSteps[3] - glbl_uint32ZeroWLSteps), HMOTORS_CLKWISE_DIRECTION, 10);
		}
		else if(glbl_uint32MotorSteps[3] < glbl_uint32ZeroWLSteps)
		{
			HMOTOR_Step(HMOTOR_WL_SELECT, (glbl_uint32ZeroWLSteps - glbl_uint32MotorSteps[3]), HMOTORS_CCLKWISE_DIRECTION, 10);
		}
		glbl_float32CurrentWL = 0.0f;
	}
	else
	{
		float32 Loc_float32WLDifference = Copy_float32NextWL - glbl_float32CurrentWL;
		uint32 Loc_uint32MotorSteps = 0;

		if(Loc_float32WLDifference > 0.098f)
		{
			Loc_uint32MotorSteps = (uint32)(Loc_float32WLDifference * (float32)glbl_uint32StepsPerNm);
			HMOTOR_Step(HMOTOR_WL_SELECT, Loc_uint32MotorSteps, HMOTORS_CLKWISE_DIRECTION, 10);
			glbl_float32CurrentWL = Copy_float32NextWL;
		}
		else if(Loc_float32WLDifference < -0.098f)
		{
			Loc_uint32MotorSteps = (uint32)((-Loc_float32WLDifference) * (float32)glbl_uint32StepsPerNm);
			HMOTOR_Step(HMOTOR_WL_SELECT, Loc_uint32MotorSteps, HMOTORS_CCLKWISE_DIRECTION, 10);
			glbl_float32CurrentWL = Copy_float32NextWL;
		}
	}
	return E_OK;
}
Std_ReturnType HMOTOR_MoveMotors(float32 Copy_float32NextWL)
{
	if((Copy_float32NextWL > -0.001f) && (Copy_float32NextWL < 1100.1f))
	{
		if(Copy_float32NextWL < 326.0f)
		{
			HMOTOR_MoveLampMotor(HMOTOR_LAMP_UV);
		}
		else
		{
			HMOTOR_MoveLampMotor(HMOTOR_LAMP_VIS);
		}

		if((Copy_float32NextWL > -0.001f) && (Copy_float32NextWL < 326.0f))
		{
			HMOTOR_MoveFilterMotor(HMOTOR_FILTER_AIR);
		}
		else if((Copy_float32NextWL > 325.9f) && (Copy_float32NextWL < 383.0f))
		{
			HMOTOR_MoveFilterMotor(HMOTOR_FILTER_1);
		}
		else if((Copy_float32NextWL > 382.9f) && (Copy_float32NextWL < 420.0f))
		{
			HMOTOR_MoveFilterMotor(HMOTOR_FILTER_2);
		}
		else if((Copy_float32NextWL > 419.9f) && (Copy_float32NextWL < 558.0f))
		{
			HMOTOR_MoveFilterMotor(HMOTOR_FILTER_3);
		}
		else if((Copy_float32NextWL > 557.9f) && (Copy_float32NextWL < 683.0f))
		{
			HMOTOR_MoveFilterMotor(HMOTOR_FILTER_4);
		}
		else if((Copy_float32NextWL > 682.9f) && (Copy_float32NextWL < 794.0f))
		{
			HMOTOR_MoveFilterMotor(HMOTOR_FILTER_5);
		}
		else if((Copy_float32NextWL > 793.9f) && (Copy_float32NextWL < 980.0f))
		{
			HMOTOR_MoveFilterMotor(HMOTOR_FILTER_6);
		}
		else if((Copy_float32NextWL > 979.9f) && (Copy_float32NextWL < 1100.1f))
		{
			HMOTOR_MoveFilterMotor(HMOTOR_FILTER_7);
		}
		else
		{
			/*Do nothing*/
		}

		HMOTOR_MoveWLSelectMotor(Copy_float32NextWL);
	}
	else
	{
		return E_NOT_OK;
	}
}
Std_ReturnType HMOTOR_GoHome  (HMOTORS_Select_t Copy_uint32MotorSelect)
{
	if(Copy_uint32MotorSelect > 0)
	{
		uint8 Loc_uint8SensorReading = MGPIO_HIGH;
		
		MSTK_uint8Delay(100);
		switch(Copy_uint32MotorSelect)
		{
			case HMOTOR_FILTER_SELECT:
			{
					MGPIO_GetPinValue(MGPIO_PORTC, MGPIO_PIN13, &Loc_uint8SensorReading);
					break;
			}
			case HMOTOR_WL_SELECT:
			{
					MGPIO_GetPinValue(MGPIO_PORTA, MGPIO_PIN0, &Loc_uint8SensorReading);
					break;
			}
		}
		if(Loc_uint8SensorReading != MGPIO_LOW)
		{
			uint32 Loc_uint8Index = 0;
			glbl_uint8HomingIndicator[(Copy_uint32MotorSelect)] = HMOTORS_MOTOR_NOT_AT_HOME;
			
			for(Loc_uint8Index = 0; Loc_uint8Index < 6000; Loc_uint8Index++)
			{
				if((glbl_uint8HomingIndicator[(Copy_uint32MotorSelect)]) == HMOTORS_MOTOR_NOT_AT_HOME)
				{
					HMOTOR_Step(Copy_uint32MotorSelect, 1, HMOTORS_CCLKWISE_DIRECTION, 10);
				}
			}

			HMOTOR_Step(Copy_uint32MotorSelect, 160, HMOTORS_CLKWISE_DIRECTION, 10);
			glbl_uint8HomingIndicator[(Copy_uint32MotorSelect)] = HMOTORS_MOTOR_NOT_AT_HOME;
			
			Loc_uint8Index = 0;
			for(Loc_uint8Index = 0; Loc_uint8Index < 6000; Loc_uint8Index++)
			{
				if((glbl_uint8HomingIndicator[(Copy_uint32MotorSelect)]) == HMOTORS_MOTOR_NOT_AT_HOME)
				{
					HMOTOR_Step(Copy_uint32MotorSelect, 1, HMOTORS_CCLKWISE_DIRECTION, 50);
				}
			}
			if(Copy_uint32MotorSelect == HMOTOR_WL_SELECT)
			{
				HMOTOR_Step(Copy_uint32MotorSelect, 10, HMOTORS_CCLKWISE_DIRECTION, 50);
			}
			glbl_uint32MotorSteps[Copy_uint32MotorSelect] = 0;
			//glbl_uint8HomingIndicator[(Copy_uint32MotorSelect)] = HMOTORS_MOTOR_NOT_AT_HOME;
		}
	}
	else if(Copy_uint32MotorSelect == HMOTOR_LAMP_SELECT)
	{
		HMOTOR_Step(Copy_uint32MotorSelect, 100, HMOTORS_CLKWISE_DIRECTION, 10);
		glbl_uint8HomingIndicator[(Copy_uint32MotorSelect)] = HMOTORS_MOTOR_AT_HOME;
		glbl_uint32MotorSteps[Copy_uint32MotorSelect] = 0;
	}
	else
	{
		return E_NOT_OK;
	}
	return E_OK;
}
Std_ReturnType HMOTOR_GetCurrentMotorSteps    (HMOTORS_Select_t Copy_uint32MotorSelect, uint32* P_uint32MotorSteps)
{
	Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
	if(P_uint32MotorSteps != NULL_PTR)
	{
		*P_uint32MotorSteps = glbl_uint32MotorSteps[Copy_uint32MotorSelect];
		Loc_uint8FuncStatus = E_OK;
	}
	else
	{
		Loc_uint8FuncStatus = E_NOT_OK;
	}
	return Loc_uint8FuncStatus;
}
Std_ReturnType HMOTOR_GetCurrentWL            (uint32* P_uint32CurrentWL)
{
	Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
	if(P_uint32CurrentWL != NULL_PTR)
	{
		*P_uint32CurrentWL = glbl_float32CurrentWL;
		Loc_uint8FuncStatus = E_OK;
	}
	else
	{
		Loc_uint8FuncStatus = E_NOT_OK;
	}
	return Loc_uint8FuncStatus;
}

void HMOTOR_FilterHomeIndicator(void)
{
	glbl_uint8HomingIndicator[1] = HMOTORS_MOTOR_AT_HOME;
}
void HMOTOR_WLHomeIndicator(void)
{
	glbl_uint8HomingIndicator[2] = HMOTORS_MOTOR_AT_HOME;
}
void HMOTOR4_HomeIndicator(void)
{
	glbl_uint8HomingIndicator[3] = HMOTORS_MOTOR_AT_HOME;
}