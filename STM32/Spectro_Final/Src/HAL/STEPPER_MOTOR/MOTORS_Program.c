/**
 * @file MOTORS_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2024-01-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/Std_Types.h"

#include <stdlib.h>

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

/************************************************************************************************* 
    Alternate function remap and debug I/O configuration register:
		Used to free JTAG Debug Pins in order to be used in interfacing with stepper motors
*************************************************************************************************/
#define MAFIO_MAPR_R													*((volatile uint32*)(0x40010000 + 0x04))

/**
 * @brief: Array that stores the number of steps that each motor is currently in
 * 
 */
static volatile sint32 glbl_sint32MotorSteps    [HMOTORS_NUM_MOTORS]    = {0};
/**
 * @brief: Array that indicates whether the motor is at home position or not
 * 
 */
static volatile uint8 glbl_uint8HomingIndicator	[HMOTORS_NUM_MOTORS] 	= {HMOTORS_MOTOR_NOT_AT_HOME, HMOTORS_MOTOR_NOT_AT_HOME, HMOTORS_MOTOR_NOT_AT_HOME, HMOTORS_MOTOR_NOT_AT_HOME};
/**
 * @brief: Holds the calibration value of filter wheel motor
 * 
 */
static volatile uint32 glbl_uint32FilterInitCalibration 				= 28;
/**
 * @brief: Holds the number of steps from home position to position of zero wavelength
 * 
 */
static volatile sint32 glbl_sint32ZeroWLSteps							= 0;
/**
 * @brief: Holds the number of steps to be taken to move one wavelength
 * 
 */
static volatile float32 glbl_float32StepsPerNm							= 0.0;

/**
 * @brief: Function to initialize interface with stepper motors
 * 
 * @return Std_ReturnType
 * @retval E_OK:										Interface Successfully Initialized
 * @retval E_NOT_OK:									Interface not initialized 
 */
Std_ReturnType HMOTORS_Init(void)
{
	/************************************************************************************************* 
        1) Disable JTAG Debug in order to free PB3 and PB4 to be used to control WL select motor
    *************************************************************************************************/
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_AFIO_EN);
	MAFIO_MAPR_R &= ~((0b111) << 24);
	MAFIO_MAPR_R |= ((0b010) << 24);
	
	uint8 Loc_uint8Index = 0;
	
	/************************************************************************************************* 
        2) Set Homing Sensors' Pins to be input pull-up
    *************************************************************************************************/
	for(Loc_uint8Index = 0; Loc_uint8Index < (HMOTORS_NUM_MOTORS - 1); Loc_uint8Index++)
	{
		MGPIO_SetPinMode(glbl_uint8MotorHomingPortIDs[Loc_uint8Index],\
							glbl_uint8MotorHomingPinIDs[Loc_uint8Index], MGPIO_INPUT_PULL_UP_OR_DOWN_MODE);
		MGPIO_ActivatePullUp(glbl_uint8MotorHomingPortIDs[Loc_uint8Index],\
								glbl_uint8MotorHomingPinIDs[Loc_uint8Index]);
	}

	/************************************************************************************************* 
        3) Set Directions of step and dir pins to be output push-pull
    *************************************************************************************************/
	for(Loc_uint8Index = 0; Loc_uint8Index < HMOTORS_NUM_MOTORS; Loc_uint8Index++)
	{
		MGPIO_SetPinMode(glbl_uint8MotorsStepPortIDs[Loc_uint8Index],\
							glbl_uint8MotorsStepPinIDs[Loc_uint8Index], MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    	MGPIO_SetPinMode(glbl_uint8MotorsDirPortIDs[Loc_uint8Index],\
							glbl_uint8MotorsDirPinIDs[Loc_uint8Index], MGPIO_OUTPUT_PUSH_PULL_2MHZ);
	}

	/************************************************************************************************* 
        4) Enable External Interrupt on homing sensors' pins 
    *************************************************************************************************/
	MNVIC_EnableInterrupt(MNVIC_EXTI15_10);
	MNVIC_EnableInterrupt(MNVIC_EXTI0);

	MEXTI_SetCallbackFunction(MEXTI_EXTI13, HMOTOR_FilterHomeIndicator);
	MEXTI_SetCallbackFunction(MEXTI_EXTI0, HMOTOR_WLHomeIndicator);
	
	MAFIO_SetEXTIPinConfigurations(MAFIO_EXTI13, MGPIO_PORTC);
	MAFIO_SetEXTIPinConfigurations(MAFIO_EXTI0, MGPIO_PORTA);

	MEXTI_EnableExternalInterrupt(MEXTI_EXTI13, MEXTI_INT_AT_FALLING_EDGE);
	MEXTI_EnableExternalInterrupt(MEXTI_EXTI0, MEXTI_INT_AT_FALLING_EDGE);

	/************************************************************************************************* 
        5) Get Value of Filter Calibration from EEPROM
    *************************************************************************************************/
	//eeprom_read_byte(EEPROM_MOTOR_STEPS_MEM_ADDRESS, &glbl_uint32FilterInitCalibration, 1);

	return E_OK;
}
/**
 * @brief: Function to move specified motor number of steps with a specified speed at a specified direction
 * 
 * @param Copy_uint32MotorSelect:						Motor to be moved
 * @param Copy_uint32NoOfSetps:							Number of steps the motor should move
 * @param Copy_uint8Direction:							Direction of motor rotation (clockwise or counter-clockwise) 
 * @param Copy_uint8MotorSpeed:							Speed of the motor (delay between steps)
 * 
 * @return Std_ReturnType
 * @retval E_OK:										Motor Successfully moved
 * @retval E_NOT_OK:									Motor not moved 
 */
Std_ReturnType HMOTOR_Step(HMOTORS_Select_t Copy_uint32MotorSelect, uint32 Copy_uint32NoOfSetps, uint8 Copy_uint8Direction, uint8 Copy_uint8MotorSpeed)
{
	Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
	uint32 Loc_uint32Index = 0;

	/************************************************************************************************* 
        1) Specify the direction of the motor movement (clockwise or counter-clockwise)
    *************************************************************************************************/
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
			break;
		}
	}

	/************************************************************************************************* 
        2) Move motor with specified number of steps
    *************************************************************************************************/
	for(Loc_uint32Index = 0; Loc_uint32Index < (Copy_uint32NoOfSetps); Loc_uint32Index++)
	{
		/*
			Step is performed when sending a pulse through STEP pin
		*/
		MGPIO_SetPinValue(glbl_uint8MotorsStepPortIDs[Copy_uint32MotorSelect],\ 
								glbl_uint8MotorsStepPinIDs[Copy_uint32MotorSelect], MGPIO_HIGH);
		
		MSTK_uint8Delay(Copy_uint8MotorSpeed / 2);
		
		MGPIO_SetPinValue(glbl_uint8MotorsStepPortIDs[Copy_uint32MotorSelect],\ 
								glbl_uint8MotorsStepPinIDs[Copy_uint32MotorSelect], MGPIO_LOW);
		
		MSTK_uint8Delay(Copy_uint8MotorSpeed / 2);

		// update the value of the global variable to keep track of the motor's current position
		if(Copy_uint8Direction == HMOTORS_CLKWISE_DIRECTION)
		{
			glbl_sint32MotorSteps[Copy_uint32MotorSelect] ++;
		}
		else if(Copy_uint8Direction == HMOTORS_CCLKWISE_DIRECTION)
		{
			glbl_sint32MotorSteps[Copy_uint32MotorSelect] --;
		}
		else
		{
			Loc_uint8FuncStatus = E_NOT_OK;
		}
	}
	return Loc_uint8FuncStatus;
}

/**
 * @brief: Function to move lamp motor to select one of the lamps (UV or Visible)
 * 
 * @param Copy_uint32LampSelect:					    Lamp to be selected
 * 
 * @return Std_ReturnType
 * @retval E_OK:									    Lamp motor successfully moved
 * @retval E_NOT_OK:								    Lamp motor not moved 
 */
Std_ReturnType HMOTOR_MoveLampMotor(HMOTOR_Lamp_Select_t Copy_uint32LampSelect)
{
	switch(Copy_uint32LampSelect)
	{
		case HMOTOR_LAMP_UV:
		{
			// Check if motor is already in the UV position or not
			if(glbl_sint32MotorSteps[HMOTOR_LAMP_SELECT] != 0)
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
			// Check if motor is already in the Visible position or not
			if(glbl_sint32MotorSteps[HMOTOR_LAMP_SELECT] != 100)
			{
				HMOTOR_Step(HMOTOR_LAMP_SELECT, 100, HMOTORS_CCLKWISE_DIRECTION, 10);
				glbl_sint32MotorSteps[HMOTOR_LAMP_SELECT] = 100;
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

/**
 * @brief: Function to move the filter wheel motor to the specified filter
 * 
 * @param Copy_uint32FilterSelect:						The selected filter to move the motor to
 *  
 * @return Std_ReturnType
 * @retval E_OK:										Motor Successfully moved
 * @retval E_NOT_OK:									Motor not moved 
 */
Std_ReturnType HMOTOR_MoveFilterMotor(HMOTOR_Filter_Select_t Copy_uint32FilterSelect)
{
    uint32 Loc_uint32StepsDifference = 0;

	// Calculate the target position based on the filter selection
    uint32 Loc_uint32TargetPosition = glbl_uint32FilterInitCalibration + (Copy_uint32FilterSelect * 50);

	// If the current motor steps are greater than the target position, move clockwise
    if (glbl_sint32MotorSteps[HMOTOR_FILTER_SELECT] > Loc_uint32TargetPosition)
    {
        Loc_uint32StepsDifference = glbl_sint32MotorSteps[HMOTOR_FILTER_SELECT] - Loc_uint32TargetPosition;
        HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CLKWISE_DIRECTION, 10);
    }
	// Else if the current motor steps are less than the target position, move counter-clockwise
    else if (glbl_sint32MotorSteps[HMOTOR_FILTER_SELECT] < Loc_uint32TargetPosition)
    {
        Loc_uint32StepsDifference = Loc_uint32TargetPosition - glbl_sint32MotorSteps[HMOTOR_FILTER_SELECT];
        HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32StepsDifference, HMOTORS_CCLKWISE_DIRECTION, 10);
    }
	else
	{
		/*Do nothing*/
	}

	// Indicate that the motor is not at the home position
    glbl_uint8HomingIndicator[HMOTOR_FILTER_SELECT] = HMOTORS_MOTOR_NOT_AT_HOME;
    return E_OK;
}
/**
 * @brief: Function to update the values of zero wavelength steps and steps/nm after calibration
 * 
 * @param Copy_uint32ZeroWLSteps:						the number of steps from home position to position of zero wavelength				
 * @param Copy_uint32StepsPerNm:						number of steps to be taken to move one wavelength 
 * @return Std_ReturnType 
 */
Std_ReturnType HMOTOR_GetWLSelectCalibration            (sint32 Copy_sint32ZeroWLSteps, float32 Copy_uint32StepsPerNm)
{
	glbl_sint32ZeroWLSteps = Copy_sint32ZeroWLSteps;
	glbl_float32StepsPerNm = Copy_uint32StepsPerNm;
	return E_OK;
}
/**
 * @brief: Function to move the wavelength select motor to position that represents the specified wavelength
 * 
 * @param Copy_float32NextWL:							Wavelength to move motor to
 * 
 * @return Std_ReturnType
 * @retval E_OK:										Motor Successfully moved
 * @retval E_NOT_OK:									Motor not moved 
 */
Std_ReturnType HMOTOR_MoveWLSelectMotor                 (float32 Copy_float32NextWL)
{
	if((Copy_float32NextWL > -0.01f) && (Copy_float32NextWL < 0.01f))
	{
		// The motor is to be moved to the position of zero wavelength
		if(glbl_sint32MotorSteps[HMOTOR_WL_SELECT] < glbl_sint32ZeroWLSteps)
		{
			/*
				If the motor current position is less than the zero wavelength position, motor will move in the 
				clockwise direction
			*/
			HMOTOR_Step(HMOTOR_WL_SELECT, (uint32)(abs(glbl_sint32MotorSteps[HMOTOR_WL_SELECT] - glbl_sint32ZeroWLSteps)), HMOTORS_CLKWISE_DIRECTION, 4);
		}
		else if(glbl_sint32MotorSteps[HMOTOR_WL_SELECT] > glbl_sint32ZeroWLSteps)
		{
			/*
				If the motor current position is greater than the zero wavelength position, motor will move in the 
				counter-clockwise direction
			*/
			HMOTOR_Step(HMOTOR_WL_SELECT, (uint32)(abs(glbl_sint32ZeroWLSteps - glbl_sint32MotorSteps[HMOTOR_WL_SELECT])), HMOTORS_CCLKWISE_DIRECTION, 4);
		}
	}
	else
	{
		/*
			We calculate the number of steps that represents the specified wavelength:

													number of steps
			Number of steps = Wavelength (nm) * ------------------------- + Zero WL Steps
														1 nm
		*/
		float32 Loc_uint32NextSteps = Copy_float32NextWL * glbl_float32StepsPerNm;
		Loc_uint32NextSteps += glbl_sint32ZeroWLSteps;

		// Then, we calculate the difference between the current position and the calculated position
		sint32 Loc_uint32StepsDifference = roundf(Loc_uint32NextSteps - glbl_sint32MotorSteps[HMOTOR_WL_SELECT]);

		/*
			if the steps difference is greater than zero, motor will move in the clockwise direction,
			otherwise, motor will move in the counter-clockwise direction
		*/
		if(Loc_uint32StepsDifference > 0)
		{
			HMOTOR_Step(HMOTOR_WL_SELECT, Loc_uint32StepsDifference, HMOTORS_CLKWISE_DIRECTION, 4);
		}
		else
		{
			HMOTOR_Step(HMOTOR_WL_SELECT, (uint32)(-Loc_uint32StepsDifference), HMOTORS_CCLKWISE_DIRECTION, 4);
		}
	}
	return E_OK;
}
/**
 * @brief: Function to move the specified motor to its homing position
 * 
 * @param Copy_uint32MotorSelect:						Motor to be moved to the homing position
 *  
 * @return Std_ReturnType
 * @retval E_OK:										Motor successfully at homing position
 * @retval E_NOT_OK:									Motor not at home 
 */
Std_ReturnType HMOTOR_GoHome  (HMOTORS_Select_t Copy_uint32MotorSelect)
{
	if(Copy_uint32MotorSelect > 0)
	{
		uint8 Loc_uint8SensorReading = MGPIO_HIGH;
		uint32 Loc_uint8Index = 0;
		uint32 Loc_uint32NoSteps = 0;
		
		MSTK_uint8Delay(100);

		/*
			We check if the motor is already in the homing position or not by checking the status of the pin
			connected to the homing sensor
		*/
		switch(Copy_uint32MotorSelect)
		{
			case HMOTOR_FILTER_SELECT:
			{
				MGPIO_GetPinValue(MGPIO_PORTC, MGPIO_PIN13, &Loc_uint8SensorReading);
				Loc_uint8SensorReading = !Loc_uint8SensorReading;
				break;
			}
			case HMOTOR_WL_SELECT:
			{
				MGPIO_GetPinValue(MGPIO_PORTA, MGPIO_PIN0, &Loc_uint8SensorReading);
				break;
			}
			default:
			{
				return E_NOT_OK;
				break;
			}
		}

		// If the homing sensor pin reads low, it means that the motor is at its homing position
		if(Loc_uint8SensorReading == MGPIO_LOW)
		{
			HMOTOR_Step(Copy_uint32MotorSelect, 400, HMOTORS_CLKWISE_DIRECTION, 4);
		}

		//We set the maximum number of steps the motor can move for each available motor
		switch(Copy_uint32MotorSelect)
		{
			case HMOTOR_WL_SELECT:
			{
				/*
					As Wavelength select motor driver's microstepping is activated so that motor moves a half step per
					command, the maximum number of steps is doubled
				*/
				Loc_uint32NoSteps = 12000;
				break;
			}
			case HMOTOR_FILTER_SELECT:
			{
				Loc_uint32NoSteps = 6000;
				break;
			}
			default:
			{
				Loc_uint32NoSteps = 0;
				break;
			}
		}

		/*
			We move the motor in the counter-clockwise direction until it reaches the homing sensor
		*/
		glbl_uint8HomingIndicator[(Copy_uint32MotorSelect)] = HMOTORS_MOTOR_NOT_AT_HOME;
		for(Loc_uint8Index = 0; Loc_uint8Index < Loc_uint32NoSteps; Loc_uint8Index++)
		{
			if((glbl_uint8HomingIndicator[(Copy_uint32MotorSelect)]) == HMOTORS_MOTOR_NOT_AT_HOME)
			{
				HMOTOR_Step(Copy_uint32MotorSelect, 1, HMOTORS_CCLKWISE_DIRECTION, 4);
			}
		}

		/*
			Then, We pull it away from the homing position and slowly move it towards the homing sensor
			for accurate positioning
		*/
		HMOTOR_Step(Copy_uint32MotorSelect, 320, HMOTORS_CLKWISE_DIRECTION, 4);
		glbl_uint8HomingIndicator[(Copy_uint32MotorSelect)] = HMOTORS_MOTOR_NOT_AT_HOME;

		Loc_uint8Index = 0;
		for(Loc_uint8Index = 0; Loc_uint8Index < Loc_uint32NoSteps; Loc_uint8Index++)
		{
			if((glbl_uint8HomingIndicator[(Copy_uint32MotorSelect)]) == HMOTORS_MOTOR_NOT_AT_HOME)
			{
				HMOTOR_Step(Copy_uint32MotorSelect, 1, HMOTORS_CCLKWISE_DIRECTION, 10);
			}
		}
		if(Copy_uint32MotorSelect == HMOTOR_WL_SELECT)
		{
			HMOTOR_Step(Copy_uint32MotorSelect, 20, HMOTORS_CCLKWISE_DIRECTION, 10);
		}

		// Then, we put our steps indicator's value to zero 
		glbl_sint32MotorSteps[Copy_uint32MotorSelect] = 0;

	}
	else if(Copy_uint32MotorSelect == HMOTOR_LAMP_SELECT)
	{
		// In case of the lamp select motor, its homing position is simply the UV position and no need for homing
		// sensor to indicate its position
		HMOTOR_Step(Copy_uint32MotorSelect, 100, HMOTORS_CLKWISE_DIRECTION, 10);
		glbl_uint8HomingIndicator[(Copy_uint32MotorSelect)] = HMOTORS_MOTOR_AT_HOME;
		glbl_sint32MotorSteps[Copy_uint32MotorSelect] = 0;
	}
	else
	{
		return E_NOT_OK;
	}
	return E_OK;
}
/**
 * @brief: Function to retrieve the specified motor's current position 
 * 
 * @param Copy_uint32MotorSelect:						Motor whose steps is to be retrieved 
 * @param P_uint32MotorSteps:							Pointer to save the number of steps in
 *  
 * @return Std_ReturnType
 * @retval E_OK:										Motor's steps successfully retrieved
 * @retval E_NOT_OK:									Motor's steps not retrieved 
 */
Std_ReturnType HMOTOR_GetCurrentMotorSteps    (HMOTORS_Select_t Copy_uint32MotorSelect, sint32* P_sint32MotorSteps)
{
	Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
	if(P_sint32MotorSteps != NULL_PTR)
	{
		*P_sint32MotorSteps = glbl_sint32MotorSteps[Copy_uint32MotorSelect];
		Loc_uint8FuncStatus = E_OK;
	}
	else
	{
		Loc_uint8FuncStatus = E_NOT_OK;
	}
	return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to retrieve the current wavelength based on the motor steps.
 * 
 * @param P_float32CurrentWL: 							Pointer where the current wavelength will be stored.
 * 
 * @return Std_ReturnType
 * @retval E_OK:										Wavelength successfully retrieved
 * @retval E_NOT_OK:									Wavelength not retrieved 
 */
Std_ReturnType HMOTOR_GetCurrentWL            (float32* P_float32CurrentWL)
{
	Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
	if(P_float32CurrentWL != NULL_PTR)
	{
		*P_float32CurrentWL = (glbl_sint32MotorSteps[HMOTOR_WL_SELECT] - glbl_sint32ZeroWLSteps) / glbl_float32StepsPerNm;
		Loc_uint8FuncStatus = E_OK;
	}
	else
	{
		Loc_uint8FuncStatus = E_NOT_OK;
	}
	return Loc_uint8FuncStatus;
}

/**
 * @brief: Function to move specified motor one step without delay after pulse creation
 * 
 * @param Copy_uint32MotorSelect:						Motor to be moved
 * @param Copy_uint8Direction:							Direction of motor rotation (clockwise or counter-clockwise) 
 * 
 * @return Std_ReturnType
 * @retval E_OK:										Motor Successfully moved
 * @retval E_NOT_OK:									Motor not moved 
 */
Std_ReturnType HMOTOR_StepNoDelay(HMOTORS_Select_t Copy_uint32MotorSelect, uint8 Copy_uint8Direction)
{
	/************************************************************************************************* 
        1) Specify the direction of the motor movement (clockwise or counter-clockwise)
    *************************************************************************************************/
	switch(Copy_uint8Direction)
	{
		case HMOTORS_CLKWISE_DIRECTION:
		{
			MGPIO_SetPinValue(glbl_uint8MotorsDirPortIDs[Copy_uint32MotorSelect],\ 
								glbl_uint8MotorsDirPinIDs[Copy_uint32MotorSelect], MGPIO_HIGH);
			break;
		}
		case HMOTORS_CCLKWISE_DIRECTION:
		{
			MGPIO_SetPinValue(glbl_uint8MotorsDirPortIDs[Copy_uint32MotorSelect],\ 
								glbl_uint8MotorsDirPinIDs[Copy_uint32MotorSelect], MGPIO_LOW);
			break;
		}
		default:
		{
			return E_NOT_OK;
			break;
		}
	}

	/************************************************************************************************* 
        2) Move motor one step by sending pulse with duration 10 us
    *************************************************************************************************/
	MGPIO_SetPinValue(glbl_uint8MotorsStepPortIDs[Copy_uint32MotorSelect],\ 
							glbl_uint8MotorsStepPinIDs[Copy_uint32MotorSelect], MGPIO_HIGH);
	
	MSTK_uint8DelayUs(10);
	
	MGPIO_SetPinValue(glbl_uint8MotorsStepPortIDs[Copy_uint32MotorSelect],\ 
							glbl_uint8MotorsStepPinIDs[Copy_uint32MotorSelect], MGPIO_LOW);

	// Update the value of the steps' indicator to keep track of the motor's current position
	if(Copy_uint8Direction == HMOTORS_CLKWISE_DIRECTION)
	{
		glbl_sint32MotorSteps[Copy_uint32MotorSelect] ++;
	}
	else if(Copy_uint8Direction == HMOTORS_CCLKWISE_DIRECTION)
	{
		glbl_sint32MotorSteps[Copy_uint32MotorSelect] --;
	}
	else
	{
		return E_NOT_OK;
	}
	return E_OK;
}
/**
 * @brief: Function to retrieve the number of steps per 1nm in order to be used in other drivers
 * 
 * @param P_float32StepsPerNm: 							Pointer to save number of steps to be taken to move one wavelength
 * 	
 * @return Std_ReturnType
 * @retval E_OK:										Value Successfully retrieved
 * @retval E_NOT_OK:									Value not retrieved 
 */
Std_ReturnType HMOTOR_GetStepsPerNm			(float32* P_float32StepsPerNm)
{
	if(P_float32StepsPerNm != NULL_PTR)
	{
		*P_float32StepsPerNm = glbl_float32StepsPerNm;
		return E_OK;
	}
	else
	{
		return E_NOT_OK;
	}
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
