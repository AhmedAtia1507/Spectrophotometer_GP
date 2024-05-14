/**
 * @file SCommands_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2024-02-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string.h>
#include <stdlib.h>

#include "../../LIB/STD_TYPES/Std_Types.h"

#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/RTC/RTC_Interface.h"
#include "../../MCAL/UART/UART_Interface.h"
#include "../../MCAL/STK/STK_Interface.h"
#include "../../MCAL/NVIC/NVIC_Interface.h"
#include "../../MCAL/SCB/SCB_Interface.h"
#include "../../MCAL/RCC/RCC_Interface.h"

#include "../../HAL/ESP32/ESP32_Interface.h"
#include "../../HAL/SPWRVolt/SPWRVolt_Interface.h"
#include "../../HAL/STEPPER_MOTOR/MOTORS_Interface.h"
#include "../../HAL/EEPROM/I2C_Slave_EEPROM.h"
#include "../../HAL/PWRSupply/HPWRSupply_Interface.h"
#include "../../HAL/MCP4151/MCP4151.h"

#include "../SpectroStatus/SpectroStatus_Interface.h"
#include "../Signal_Conditioning/signal_conditioning.h"

#include "SCommands_Config.h"
#include "SCommands_Interface.h"
#include "SCommands_Private.h"


Std_ReturnType SCommands_Init(void)
{
	HESP32_SetCommandCallbackFunction       (0, SCommands_GetUVStatus);
	HESP32_SetCommandCallbackFunction       (1, SCommands_SetUVOn);
	HESP32_SetCommandCallbackFunction       (2, SCommands_SetUVOff);
	HESP32_SetCommandCallbackFunction       (3, SCommands_GetVisStatus);
	HESP32_SetCommandCallbackFunction       (4, SCommands_SetVisOn);
	HESP32_SetCommandCallbackFunction       (5, SCommands_SetVisOff);
	HESP32_SetCommandCallbackFunction       (6, SCommands_GetSupplyVoltages);

	HESP32_SetCommandCallbackFunction       (7, SCommands_SendCurrentMotorsSteps);
	HESP32_SetCommandCallbackFunction       (8, SCommands_HomeLampMotor);
	HESP32_SetCommandCallbackFunction       (9, SCommands_HomeWLSelectMotor);
	HESP32_SetCommandCallbackFunction       (10, SCommands_HomeFilterSelectMotor);
	HESP32_SetCommandCallbackFunction       (11, SCommands_SendCurrentWL);
	HESP32_SetCommandCallbackFunction       (12, SCommands_SendCurrentDateTime);
	HESP32_SetCommandCallbackFunction       (13, SCommands_SendCurrentDetectorValues);
	HESP32_SetCommandCallbackFunction       (14, SCommands_GetLampMotorPosition);
	HESP32_SetCommandCallbackFunction       (15, SCommands_SetLampMotorVisible);
	HESP32_SetCommandCallbackFunction       (16, SCommands_SetLampMotorUV);

	HESP32_SetCommandCallbackArgFunction    (17, SCommands_UpdateDateTime);
	HESP32_SetCommandCallbackArgFunction    (18, SCommands_SaveFilterMotorCalibSteps);
	HESP32_SetCommandCallbackArgFunction    (19, SCommands_SaveFilterMotorCalibWL);
	HESP32_SetCommandCallbackArgFunction    (20, SCommands_StartOperation);
	HESP32_SetCommandCallbackArgFunction    (21, SCommands_SetReferenceGain);
	HESP32_SetCommandCallbackArgFunction    (22, SCommands_SetSampleGain);
	HESP32_SetCommandCallbackArgFunction    (23, SCommands_MoveFilterLeft);
	HESP32_SetCommandCallbackArgFunction    (24, SCommands_MoveFilterRight);
	HESP32_SetCommandCallbackArgFunction    (25, SCommands_SelectFilter);
	HESP32_SetCommandCallbackArgFunction    (26, SCommands_SelectGratingWL);
	HESP32_SetCommandCallbackArgFunction    (27, SCommands_MoveGratingLeft);
	HESP32_SetCommandCallbackArgFunction    (28, SCommands_MoveGratingRight);

	HESP32_InitInterface();

	return E_OK;
}

void SCommands_GetUVStatus(void)
{
	SpectroStatus_SetNewStatus(BUSY);
	uint8 Loc_uint8LampStatus = MGPIO_LOW;
	MGPIO_GetPinValue(SPECTRO_UV_POWER_CONTROL_PORT_ID, SPECTRO_UV_POWER_CONTROL_PIN_ID, &Loc_uint8LampStatus);
	if(Loc_uint8LampStatus == MGPIO_HIGH)
	{
		HESP32_SendCommand("on");
	}
	else if(Loc_uint8LampStatus == MGPIO_LOW)
	{
		HESP32_SendCommand("off");
	}
	else
	{
		/*Do nothing*/
	}
	//HPWRSupply_Status_t Loc_uint32SupplyStatus = HPWRSUPPLY_STATUS_OFF;
	//HPWRSupply_CheckSupplyStatus(HPWRSUPPLY_UV_SUPPLY, &Loc_uint32SupplyStatus);
	//if(Loc_uint32SupplyStatus == HPWRSUPPLY_STATUS_OK)
	//{
	//    HESP32_SendCommand("on");
	//}
	//else
	//{
	//    HESP32_SendCommand("off");
	//}
	SpectroStatus_SetNewStatus(IDLE);
}


void SCommands_SetUVOn(void)
{
	SpectroStatus_SetNewStatus(BUSY);
	MGPIO_SetPinValue(SPECTRO_UV_POWER_CONTROL_PORT_ID, SPECTRO_UV_POWER_CONTROL_PIN_ID, MGPIO_HIGH);
	HESP32_SendCommand("on");
	//Std_ReturnType Loc_uint8UVStatus = HPWRSupply_SetSupplyMode(HPWRSUPPLY_UV_SUPPLY, HPWRSUPPLY_ON);
	//if(Loc_uint8UVStatus == E_OK)
	//{
	//    HESP32_SendCommand("on");
	//}
	//else
	//{
	//    HESP32_SendCommand("off");
	//}
	SpectroStatus_SetNewStatus(IDLE);
}


void SCommands_SetUVOff(void)
{
	SpectroStatus_SetNewStatus(BUSY);
	MGPIO_SetPinValue(SPECTRO_UV_POWER_CONTROL_PORT_ID, SPECTRO_UV_POWER_CONTROL_PIN_ID, MGPIO_LOW);
	HESP32_SendCommand("off");
	//Std_ReturnType Loc_uint8UVStatus = HPWRSupply_SetSupplyMode(HPWRSUPPLY_UV_SUPPLY, HPWRSUPPLY_OFF);
	//if(Loc_uint8UVStatus == E_OK)
	//{
	//    HESP32_SendCommand("off");
	//}
	//else
	//{
	//    HESP32_SendCommand("on");
	//}
	SpectroStatus_SetNewStatus(IDLE);
}


void SCommands_GetVisStatus(void)
{
	SpectroStatus_SetNewStatus(BUSY);
	uint8 Loc_uint8LampStatus = MGPIO_LOW;
	MGPIO_GetPinValue(SPECTRO_VIS_POWER_CONTROL_PORT_ID, SPECTRO_VIS_POWER_CONTROL_PIN_ID, &Loc_uint8LampStatus);
	if(Loc_uint8LampStatus == MGPIO_HIGH)
	{
		HESP32_SendCommand("on");
	}
	else if(Loc_uint8LampStatus == MGPIO_LOW)
	{
		HESP32_SendCommand("off");
	}
	else
	{
		/*Do nothing*/
	}
	//HPWRSupply_Status_t Loc_uint32SupplyStatus = HPWRSUPPLY_STATUS_OFF;
	//HPWRSupply_CheckSupplyStatus(HPWRSUPPLY_VIS_SUPPLY, &Loc_uint32SupplyStatus);
	//if(Loc_uint32SupplyStatus == HPWRSUPPLY_STATUS_OK)
	//{
	//    HESP32_SendCommand("on");
	//}
	//else
	//{
	//    HESP32_SendCommand("off");
	//}
	SpectroStatus_SetNewStatus(IDLE);
}


void SCommands_SetVisOn(void)
{
	SpectroStatus_SetNewStatus(BUSY);
	MGPIO_SetPinValue(SPECTRO_VIS_POWER_CONTROL_PORT_ID, SPECTRO_VIS_POWER_CONTROL_PIN_ID, MGPIO_HIGH);
	HESP32_SendCommand("on");
	//Std_ReturnType Loc_uint8UVStatus = HPWRSupply_SetSupplyMode(HPWRSUPPLY_VIS_SUPPLY, HPWRSUPPLY_ON);
	//if(Loc_uint8UVStatus == E_OK)
	//{
	//    HESP32_SendCommand("on");
	//}
	//else
	//{
	//    HESP32_SendCommand("off");
	//}
	SpectroStatus_SetNewStatus(IDLE);
}


void SCommands_SetVisOff(void)
{
	SpectroStatus_SetNewStatus(BUSY);
	MGPIO_SetPinValue(SPECTRO_VIS_POWER_CONTROL_PORT_ID, SPECTRO_VIS_POWER_CONTROL_PIN_ID, MGPIO_LOW);
	HESP32_SendCommand("off");
	//Std_ReturnType Loc_uint8UVStatus = HPWRSupply_SetSupplyMode(HPWRSUPPLY_VIS_SUPPLY, HPWRSUPPLY_OFF);
	//if(Loc_uint8UVStatus == E_OK)
	//{
	//    HESP32_SendCommand("off");
	//}
	//else
	//{
	//    HESP32_SendCommand("on");
	//}
	SpectroStatus_SetNewStatus(IDLE);
}

void SCommands_GetSupplyVoltages(void)
{
	SpectroStatus_SetNewStatus(BUSY);
	uint16 Loc_uint16VoltageConversion = 0;
	float32 Loc_float32VoltageValue = 0.0;
	uint8 glbl_uint8VoltageBuffer[5][32] = {{0}};
	uint16 Loc_uint16EnteredVoltageConversion = 0;
	uint16 Loc_uint16_33VoltageConversion = 0;
	float32 Loc_float32EnteredVoltageValue = 0.0;
	float32 Loc_float32_33VoltageValue = 0.0;

	/*************************************************P12*****************************************************/
	SPWRVolt_GetVoltage(SPWRVOLT_DCDC_POS_12, &Loc_uint16VoltageConversion);

	Loc_float32VoltageValue = (float32)((float32)((float32)Loc_uint16VoltageConversion / 4096) * 3.3f) * 4;

	float_to_string_manual((glbl_uint8VoltageBuffer[0] + 1),Loc_float32VoltageValue, 3);
	glbl_uint8VoltageBuffer[0][0] = '+';

	/************************************************N12*****************************************************/
	SPWRVolt_GetVoltage(SPWRVOLT_DCDC_NEG_12, &Loc_uint16EnteredVoltageConversion);
	SPWRVolt_GetVoltage(SPWRVOLT_SUPPLY_33, &Loc_uint16_33VoltageConversion);

	Loc_float32EnteredVoltageValue = (float32)((float32)((float32)Loc_uint16EnteredVoltageConversion / 4096) * 3.3f) ;
	Loc_float32_33VoltageValue = (float32)((float32)((float32)Loc_uint16_33VoltageConversion / 4096) * 3.3f) * 2 ;

	Loc_float32VoltageValue = ((Loc_float32_33VoltageValue - Loc_float32EnteredVoltageValue) * 11) - 3.3f;

	//snprintf((glbl_uint8VoltageBuffer + 1), (sizeof(glbl_uint8VoltageBuffer) - 1), "%.*f", 3,Loc_float32FinalVoltageValue);
	float_to_string_manual((glbl_uint8VoltageBuffer[1] + 1),Loc_float32VoltageValue, 3);
	glbl_uint8VoltageBuffer[1][0] = '-';

	/************************************************P5*****************************************************/
	SPWRVolt_GetVoltage(SPWRVOLT_SUPPLY_5, &Loc_uint16VoltageConversion);

	Loc_float32VoltageValue = ((float32)((float32)((float32)Loc_uint16VoltageConversion / 4096) * 3.3f) + 0.16f) * 2;

	//snprintf(glbl_uint8VoltageBuffer, sizeof(glbl_uint8VoltageBuffer), "%.*f", 3,Loc_float32VoltageValue);
	float_to_string_manual((glbl_uint8VoltageBuffer[2]),Loc_float32VoltageValue, 3);

	/***********************************************P3.3****************************************************/
	SPWRVolt_GetVoltage(SPWRVOLT_SUPPLY_33, &Loc_uint16VoltageConversion);

	Loc_float32VoltageValue = (float32)((float32)((float32)Loc_uint16VoltageConversion / 4096) * 3.3f) * 2;

	//snprintf(glbl_uint8VoltageBuffer, sizeof(glbl_uint8VoltageBuffer), "%.*f", 3,Loc_float32VoltageValue);
	float_to_string_manual((glbl_uint8VoltageBuffer[3]),Loc_float32VoltageValue, 3);

	/***********************************************Supply 12***********************************************/
	SPWRVolt_GetVoltage(SPWRVOLT_SUPPLY_12, &Loc_uint16VoltageConversion);

	Loc_float32VoltageValue = (float32)((float32)((float32)Loc_uint16VoltageConversion / 4096) * 3.3f) * 4;

	//snprintf(glbl_uint8VoltageBuffer, sizeof(glbl_uint8VoltageBuffer), "%.*f", 3,Loc_float32VoltageValue);
	float_to_string_manual((glbl_uint8VoltageBuffer[4]),Loc_float32VoltageValue, 3);

	/*******************************************Send Voltages***********************************************/
	HESP32_SendVoltages(glbl_uint8VoltageBuffer);
	SpectroStatus_SetNewStatus(IDLE);
}


void SCommands_SendCurrentMotorsSteps   (void)
{
	SpectroStatus_SetNewStatus(BUSY);
	uint32 Loc_uint32MotorsCurrentSteps[3] = {0};
	uint32 Loc_uint32CurrentWL = 0;
	uint8 Loc_uint8Index = 0;

	for(Loc_uint8Index = HMOTOR_LAMP_SELECT; Loc_uint8Index < (HMOTOR_WL_SELECT + 1); Loc_uint8Index++)
	{
		HMOTOR_GetCurrentMotorSteps(Loc_uint8Index, &Loc_uint32MotorsCurrentSteps[Loc_uint8Index]);
	}
	HMOTOR_GetCurrentWL(&Loc_uint32CurrentWL);
	HESP32_SendMotorStatus(Loc_uint32MotorsCurrentSteps, &Loc_uint32CurrentWL, 3);
	SpectroStatus_SetNewStatus(IDLE);
}


void SCommands_HomeLampMotor    (void)
{
	SpectroStatus_SetNewStatus(BUSY);
	uint32 Loc_uint32LampCurrentSteps = 0;
	uint32 Loc_uint32CurrentWL = 0;
	HMOTOR_GoHome(HMOTOR_LAMP_SELECT);
	HMOTOR_GetCurrentMotorSteps(HMOTOR_LAMP_SELECT, &Loc_uint32LampCurrentSteps);
	HMOTOR_GetCurrentWL(&Loc_uint32CurrentWL);
	HESP32_SendMotorStatus(&Loc_uint32LampCurrentSteps, &Loc_uint32CurrentWL, 1);
	SpectroStatus_SetNewStatus(IDLE);
}


void SCommands_HomeWLSelectMotor (void)
{
	SpectroStatus_SetNewStatus(BUSY);
	uint32 Loc_uint32WLCurrentSteps = 0;
	uint32 Loc_uint32CurrentWL = 0;
	HMOTOR_GoHome(HMOTOR_WL_SELECT);
	HMOTOR_GetCurrentMotorSteps(HMOTOR_WL_SELECT, &Loc_uint32WLCurrentSteps);
	HMOTOR_GetCurrentWL(&Loc_uint32CurrentWL);
	HESP32_SendMotorStatus(&Loc_uint32WLCurrentSteps, &Loc_uint32CurrentWL, 1);
	SpectroStatus_SetNewStatus(IDLE);
}


void SCommands_HomeFilterSelectMotor  (void)
{
	SpectroStatus_SetNewStatus(BUSY);
	uint32 Loc_uint32FilterCurrentSteps = 0;
	uint32 Loc_uint32CurrentWL = 0;
	HMOTOR_GoHome(HMOTOR_FILTER_SELECT);
	HMOTOR_GetCurrentMotorSteps(HMOTOR_FILTER_SELECT, &Loc_uint32FilterCurrentSteps);
	HMOTOR_GetCurrentWL(&Loc_uint32CurrentWL);
	HESP32_SendMotorStatus(&Loc_uint32FilterCurrentSteps, &Loc_uint32CurrentWL, 1);
	SpectroStatus_SetNewStatus(IDLE);
}


void SCommands_SendCurrentWL    (void)
{
	SpectroStatus_SetNewStatus(BUSY);
	uint8 P_uint8WL[20] = {0};
	uint32 Loc_uint32CurrentWL = 0;
	HMOTOR_GetCurrentWL(&Loc_uint32CurrentWL);
	//snprintf(P_uint8WL, sizeof(P_uint8WL), "%d", Loc_uint32CurrentWL);
	float_to_string_manual(P_uint8WL, Loc_uint32CurrentWL, 0);
	HESP32_SendCommand(P_uint8WL);
	SpectroStatus_SetNewStatus(IDLE);
}

void SCommands_GetLampMotorPosition(void)
{
	SpectroStatus_SetNewStatus(BUSY);

	uint32 Loc_uint32LampSteps = 0;
	HMOTOR_GetCurrentMotorSteps(HMOTOR_LAMP_SELECT, &Loc_uint32LampSteps);

	if(Loc_uint32LampSteps == 0)
	{
		HESP32_SendCommand("UV Lamp");
	}
	else if(Loc_uint32LampSteps == 100)
	{
		HESP32_SendCommand("VI Lamp");
	}
	else
	{
		/*Do nothing*/
	}
}

void SCommands_SetLampMotorVisible(void)
{
	Std_ReturnType Loc_uint8FuncStatus = HMOTOR_MoveLampMotor(HMOTOR_LAMP_VIS);
	if(Loc_uint8FuncStatus == E_OK)
	{
		HESP32_SendCommand("moved");
	}
	else
	{
		HESP32_SendCommand("failed to move");
	}
}

void SCommands_SetLampMotorUV(void)
{
	Std_ReturnType Loc_uint8FuncStatus = HMOTOR_MoveLampMotor(HMOTOR_LAMP_UV);
	if(Loc_uint8FuncStatus == E_OK)
	{
		HESP32_SendCommand("moved");
	}
	else
	{
		HESP32_SendCommand("failed to move");
	}
}

void SCommands_SendCurrentDateTime(void)
{
	SpectroStatus_SetNewStatus(BUSY);
	Sdate_t current_date;
	Stime_t current_time;

	MRTC_GetDateAndTime(&current_date, &current_time);

	HESP32_SendDateTime(&current_date, &current_time);
	SpectroStatus_SetNewStatus(IDLE);
}

void SCommands_SendCurrentDetectorValues(void)
{
	SpectroStatus_SetNewStatus(BUSY);
	float32 Loc_float32Readings[4] = {0.0f};
	float32 Loc_float32SampleReading = 0.0f;
	float32 Loc_float32ReferenceReading = 0.0f;
	float32 Loc_float32Gain[2] = {0.0f};

	read_reference_voltage(&Loc_float32ReferenceReading, &Loc_float32Gain[0]);

	if((Loc_float32Gain[0] > 0.98f) && (Loc_float32Gain[0] < 1.01f))
	{
		Loc_float32Readings[0] = Loc_float32ReferenceReading;
		Loc_float32Readings[1] = Loc_float32ReferenceReading;
	}
	else if(Loc_float32Gain[0] > 1.01f)
	{
		Loc_float32Readings[0] = Loc_float32ReferenceReading / Loc_float32Gain[0];
		Loc_float32Readings[1] = Loc_float32ReferenceReading;
	}
	else
	{
		/*Do nothing*/
	}

	read_sample_voltage(&Loc_float32SampleReading, &Loc_float32Gain[1]);

	if((Loc_float32Gain[1] > 0.98f) && (Loc_float32Gain[1] < 1.01f))
	{
		Loc_float32Readings[2] = Loc_float32SampleReading;
		Loc_float32Readings[3] = Loc_float32SampleReading;
	}
	else if(Loc_float32Gain[1] > 1.01f)
	{
		Loc_float32Readings[2] = Loc_float32SampleReading / Loc_float32Gain[1];
		Loc_float32Readings[3] = Loc_float32SampleReading;
	}
	else
	{
		/*Do nothing*/
	}


	HESP32_SendDetectorValues(Loc_float32Readings, Loc_float32Gain);
	SpectroStatus_SetNewStatus(IDLE);
}

void SCommands_UpdateDateTime(uint8* P_uint8DateTime)
{
	SpectroStatus_SetNewStatus(BUSY);
	if(P_uint8DateTime != NULL_PTR)
	{
		Sdate_t date;
		Stime_t time;

		uint8* Loc_PToken = NULL_PTR;
		uint8 Loc_uint8Count = 0;
		Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

		Loc_PToken = strtok(P_uint8DateTime, "/");

		if(Loc_PToken != NULL_PTR)
		{
			date.m_months = atoi(Loc_PToken);

			while(Loc_PToken != NULL_PTR)
			{
				Loc_uint8Count++;

				if(Loc_uint8Count < 3)
				{
					Loc_PToken = strtok(NULL_PTR, "/");

					if(Loc_PToken != NULL_PTR)
					{
						switch(Loc_uint8Count)
						{
						case 1:
						{
							date.m_days = atoi(Loc_PToken);
							break;
						}
						case 2:
						{
							Loc_PToken = strtok(Loc_PToken, " ");
							break;
						}
						}
					}
				}
				else if(Loc_uint8Count == 3)
				{
					date.m_years = atoi(Loc_PToken);
					Loc_PToken = strtok(NULL_PTR, ":");
					if(Loc_PToken != NULL_PTR)
					{
						time.m_hours = atoi(Loc_PToken);
					}
				}
				else
				{
					Loc_PToken = strtok(NULL_PTR, ":");
					if(Loc_PToken != NULL_PTR)
					{
						switch(Loc_uint8Count)
						{
						case 4:
						{
							time.m_minutes = atoi(Loc_PToken);
							break;
						}
						case 5:
						{
							time.m_seconds = atoi(Loc_PToken);
							break;
						}
						}
					}
				}
			}
		}

		if(Loc_uint8Count == 6)
		{
			Loc_uint8FuncStatus = MRTC_SetDateAndTime(&date, &time);
			if(Loc_uint8FuncStatus == E_OK)
			{
				HESP32_SendCommand("time update success");
			}
			else
			{
				HESP32_SendCommand("time update failed");
			}
		}
		else
		{
			HESP32_SendCommand("time update failed");
		}
	}
	else
	{
		HESP32_SendCommand("time update failed");
	}
	SpectroStatus_SetNewStatus(IDLE);
}


void SCommands_MoveFilterSelectMotor         (uint8* P_uint8MotorSteps)
{
	SpectroStatus_SetNewStatus(BUSY);
	if(P_uint8MotorSteps != NULL_PTR)
	{
		uint32 Loc_uint32FilterCurrentSteps = 0;
		HMOTOR_GetCurrentMotorSteps(HMOTOR_FILTER_SELECT, &Loc_uint32FilterCurrentSteps);

		uint32 Loc_uint32MotorSteps = atoi(P_uint8MotorSteps);
		uint32 Loc_uint32MotorDiff = 0;
		if(Loc_uint32MotorSteps > Loc_uint32FilterCurrentSteps)
		{
			Loc_uint32MotorDiff = Loc_uint32MotorSteps - Loc_uint32FilterCurrentSteps;
			HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32MotorDiff, HMOTORS_CLKWISE_DIRECTION, 10);
		}
		else if(Loc_uint32MotorSteps < Loc_uint32FilterCurrentSteps)
		{
			Loc_uint32MotorDiff = Loc_uint32FilterCurrentSteps - Loc_uint32MotorSteps;
			HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32MotorDiff, HMOTORS_CCLKWISE_DIRECTION, 10);
		}
		else
		{
			/*Do nothing*/
		}
		HESP32_SendCommand("moved");
	}
	else
	{
		HESP32_SendCommand("failed to move");
	}
	SpectroStatus_SetNewStatus(IDLE);
}


void SCommands_SaveFilterMotorCalibSteps          (uint8* P_uint8MotorSteps)
{
	SpectroStatus_SetNewStatus(BUSY);
	if(P_uint8MotorSteps != NULL_PTR)
	{
		uint32 Loc_uint32FilterSteps = atoi(P_uint8MotorSteps);
		eeprom_write_Nbytes(EEPROM_MOTOR_STEPS_MEM_ADDRESS, &Loc_uint32FilterSteps, 4);
		HESP32_SendCommand("saved");
	}
	else
	{
		HESP32_SendCommand("failed to save");
	}
	SpectroStatus_SetNewStatus(IDLE);
}


void SCommands_SaveFilterMotorCalibWL          (uint8* P_uint8Wavelength)
{
	SpectroStatus_SetNewStatus(BUSY);
	if(P_uint8Wavelength != NULL_PTR)
	{
		uint32 Loc_uint32FilterWL = atoi(P_uint8Wavelength);
		eeprom_write_Nbytes(EEPROM_MOTOR_WL_MEM_ADDRESS, &Loc_uint32FilterWL, 4);
		HESP32_SendCommand("saved");
	}
	else
	{
		HESP32_SendCommand("failed to save");
	}
	SpectroStatus_SetNewStatus(IDLE);
}

static volatile uint32 glbl_uint32randomSeed = 1234;
// Function to seed the random number generator
void seed_random() {
	srand(glbl_uint32randomSeed);
}
// Function to generate random float between min and max
float32 random_float(float32 min, float32 max) {
	float32 scale_factor = 1.0f / RAND_MAX;
	uint32 random_int = rand();
	float32 random_float = random_int * scale_factor;
	random_float = (max - min) * random_float + min;
	return random_float;
}

// Function to generate random I_reference and I_sample
void generate_random_values(float32 *I_reference, float32 *I_sample) {
	seed_random();
	glbl_uint32randomSeed++;
	*I_reference = random_float(0.0f, 12.0f);
	*I_sample = random_float(0.0f, 12.0f);

	// Ensure I_reference is greater than or equal to I_sample
	if (*I_reference < *I_sample) {
		// Swap values if necessary
		float32 temp = *I_reference;
		*I_reference = *I_sample;
		*I_sample = temp;
	}
}
float32 gain_ref;
float32 gain_sample;

void SCommands_StartOperation         (uint8* P_uint8ScanParam)
{
	SpectroStatus_SetNewStatus(BUSY);
	if(P_uint8ScanParam != NULL_PTR)
	{
		//Loc_float32ScanParameters[0] --> start wavelength
		//Loc_float32ScanParameters[1] --> end wavelength
		//Loc_float32ScanParameters[2] --> wavelength resolution
		float32 Loc_float32ScanParameters[3] = {0.0};
		uint8* P_uint8Token = NULL_PTR;
		uint8 Loc_uint8Index = 0;

		// separate the string input P_uint8ScanParam to three strings
		P_uint8Token = strtok(P_uint8ScanParam, " ");
		Loc_float32ScanParameters[Loc_uint8Index] = atof(P_uint8Token);
		Loc_uint8Index++;

		while((P_uint8Token != NULL_PTR) && (Loc_uint8Index < 3))
		{
			P_uint8Token = strtok(NULL_PTR, " ");
			Loc_float32ScanParameters[Loc_uint8Index++] = atof(P_uint8Token);
		}

		//        if(Loc_uint8Index == 3)
		//        {
		//            //HMOTOR_GoHome(HMOTOR_FILTER_SELECT);
		//
		//
		//            float32 Loc_float32Index = Loc_float32ScanParameters[0];
		//            float32 Loc_float32RefIntensity = 0.0;
		//            float32 Loc_float32SampleIntensity = 0.0;
		//
		//            Sdate_t Loc_SCurrentDate = {0};
		//            Stime_t Loc_SCurrentTime = {0};
		//
		//            while(Loc_float32Index < Loc_float32ScanParameters[1])
		//            {
		//                generate_random_values(&Loc_float32RefIntensity, &Loc_float32SampleIntensity);
		//                MRTC_GetDateAndTime(&Loc_SCurrentDate, &Loc_SCurrentTime);
		//                HESP32_SendIntensities(Loc_float32Index, Loc_float32RefIntensity, Loc_float32SampleIntensity, &Loc_SCurrentDate, &Loc_SCurrentTime);
		//                //HMOTOR_Step(HMOTOR_FILTER_SELECT, 1, HMOTORS_CLKWISE_DIRECTION);
		//                MSTK_uint8Delay(1000);
		//                Loc_float32Index += Loc_float32ScanParameters[2];
		//            }
		//			//HESP32_SendCommand("done");
		//        }



		if(Loc_uint8Index == 3)
		{
			//HMOTOR_GoHome(HMOTOR_FILTER_SELECT);
			// Move the motor to the location of the first wavelength


			float32 Loc_float32Index = Loc_float32ScanParameters[0];
			float32 Loc_float32RefIntensity = 0.0;
			float32 Loc_float32SampleIntensity = 0.0;

			Sdate_t Loc_SCurrentDate = {0};
			Stime_t Loc_SCurrentTime = {0};

			while(Loc_float32Index < Loc_float32ScanParameters[1])
			{
				HMOTOR_MoveMotors(Loc_float32Index);
				read_reference_voltage(&Loc_float32RefIntensity, &gain_ref);
				read_sample_voltage(&Loc_float32SampleIntensity, &gain_sample);
				MRTC_GetDateAndTime(&Loc_SCurrentDate, &Loc_SCurrentTime);
				HESP32_SendIntensities(Loc_float32Index, Loc_float32RefIntensity, Loc_float32SampleIntensity, &Loc_SCurrentDate, &Loc_SCurrentTime);
				MSTK_uint8Delay(1000);
				Loc_float32Index += Loc_float32ScanParameters[2];
			}
			//HESP32_SendCommand("done");
		}
		else
		{
			/*Do nothing*/
		}
	}
	else
	{
		/*Do nothing*/
	}
	SpectroStatus_SetNewStatus(IDLE);
}

void SCommands_SetReferenceGain(uint8* P_uint8GainToBeSet)
{
	SpectroStatus_SetNewStatus(BUSY);
	if(P_uint8GainToBeSet != NULL_PTR)
	{
		float32 Loc_uint32GainToBeSet = (float32)(atof(P_uint8GainToBeSet));
		Set_Reference_Gain(Loc_uint32GainToBeSet);
		HESP32_SendCommand("applied");
	}
	else
	{
		HESP32_SendCommand("not applied");
	}
	SpectroStatus_SetNewStatus(IDLE);
}
void SCommands_SetSampleGain(uint8* P_uint8GainToBeSet)
{
	SpectroStatus_SetNewStatus(BUSY);
	if(P_uint8GainToBeSet != NULL_PTR)
	{
		float32 Loc_uint32GainToBeSet = (float32)(atof(P_uint8GainToBeSet));
		Set_Sample_Gain(Loc_uint32GainToBeSet);
		HESP32_SendCommand("applied");
	}
	else
	{
		HESP32_SendCommand("not applied");
	}
	SpectroStatus_SetNewStatus(IDLE);
}

void SCommands_MoveFilterRight(uint8* P_uint8FilterSteps)
{
	SpectroStatus_SetNewStatus(BUSY);
	if(P_uint8FilterSteps != NULL_PTR)
	{
		uint32 Loc_uint32FilterSteps = atoi(P_uint8FilterSteps);
		HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32FilterSteps, HMOTORS_CLKWISE_DIRECTION, 10);
		HESP32_SendCommand("moved");
	}
	else
	{
		HESP32_SendCommand("failed to move");
	}
	SpectroStatus_SetNewStatus(IDLE);
}
void SCommands_MoveFilterLeft(uint8* P_uint8FilterSteps)
{
	SpectroStatus_SetNewStatus(BUSY);
	if(P_uint8FilterSteps != NULL_PTR)
	{
		uint32 Loc_uint32FilterSteps = atoi(P_uint8FilterSteps);
		HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32FilterSteps, HMOTORS_CCLKWISE_DIRECTION, 10);
		HESP32_SendCommand("moved");
	}
	else
	{
		HESP32_SendCommand("failed to move");
	}
	SpectroStatus_SetNewStatus(IDLE);
}
void SCommands_SelectFilter(uint8* P_uint8FilterSelect)
{
	SpectroStatus_SetNewStatus(BUSY);
	if(P_uint8FilterSelect != NULL_PTR)
	{
		HMOTOR_Filter_Select_t Loc_uint8FilterSelect = (P_uint8FilterSelect[1] - '0') - 1;
		HMOTOR_MoveFilterMotor(Loc_uint8FilterSelect);
		HESP32_SendCommand("moved");
	}
	else
	{
		HESP32_SendCommand("failed to move");
	}
	SpectroStatus_SetNewStatus(IDLE);
}

void SCommands_SelectGratingWL(uint8* P_uint8WL)
{
	SpectroStatus_SetNewStatus(BUSY);
	if(P_uint8WL != NULL_PTR)
	{
		float32 Loc_float32WL = atof(P_uint8WL);
		HMOTOR_MoveWLSelectMotor(Loc_float32WL);
		HESP32_SendCommand("moved");
	}
	else
	{
		HESP32_SendCommand("failed to move");
	}
	SpectroStatus_SetNewStatus(IDLE);
}
void SCommands_MoveGratingLeft(uint8* P_uint8WLSteps)
{
	SpectroStatus_SetNewStatus(BUSY);
	if(P_uint8WLSteps != NULL_PTR)
	{
		uint32 Loc_uint32WLSteps = atoi(P_uint8WLSteps);
		HMOTOR_Step(HMOTOR_WL_SELECT, Loc_uint32WLSteps, HMOTORS_CCLKWISE_DIRECTION, 10);
		HESP32_SendCommand("moved");
	}
	else
	{
		HESP32_SendCommand("failed to move");
	}
	SpectroStatus_SetNewStatus(IDLE);
}
void SCommands_MoveGratingRight(uint8* P_uint8WLSteps)
{
	SpectroStatus_SetNewStatus(BUSY);
	if(P_uint8WLSteps != NULL_PTR)
	{
		uint32 Loc_uint32WLSteps = atoi(P_uint8WLSteps);
		HMOTOR_Step(HMOTOR_WL_SELECT, Loc_uint32WLSteps, HMOTORS_CLKWISE_DIRECTION, 10);
		HESP32_SendCommand("moved");
	}
	else
	{
		HESP32_SendCommand("failed to move");
	}
	SpectroStatus_SetNewStatus(IDLE);
}

//void SCommands_GetDcDcP12Voltage(void)
//{
//    SpectroStatus_SetNewStatus(BUSY);
//    uint16 Loc_uint16VoltageConversion = 0;
//    float32 Loc_float32VoltageValue = 0.0;
//    uint8 glbl_uint8VoltageBuffer[32] = {0};
//
//    SPWRVolt_GetVoltage(SPWRVOLT_DCDC_POS_12, &Loc_uint16VoltageConversion);
//
//    Loc_float32VoltageValue = (float32)((float32)((float32)Loc_uint16VoltageConversion / 4096) * 3.3f) * 4;
//
//    //snprintf((glbl_uint8VoltageBuffer + 1), (sizeof(glbl_uint8VoltageBuffer) - 1), "%.*f", 3,Loc_float32VoltageValue);
//    float_to_string_manual((glbl_uint8VoltageBuffer + 1),Loc_float32VoltageValue, 3);
//    glbl_uint8VoltageBuffer[0] = '+';
//
//    HESP32_SendCommand(glbl_uint8VoltageBuffer);
//    SpectroStatus_SetNewStatus(IDLE);
//}
//
//
//void SCommands_GetDcDcN12Voltage(void)
//{
//    SpectroStatus_SetNewStatus(BUSY);
//    uint16 Loc_uint16EnteredVoltageConversion = 0;
//    uint16 Loc_uint16_33VoltageConversion = 0;
//    float32 Loc_float32EnteredVoltageValue = 0.0;
//    float32 Loc_float32_33VoltageValue = 0.0;
//    float32 Loc_float32FinalVoltageValue = 0.0;
//    uint8 glbl_uint8VoltageBuffer[32] = {0};
//
//    SPWRVolt_GetVoltage(SPWRVOLT_DCDC_NEG_12, &Loc_uint16EnteredVoltageConversion);
//    SPWRVolt_GetVoltage(SPWRVOLT_SUPPLY_33, &Loc_uint16_33VoltageConversion);
//
//    Loc_float32EnteredVoltageValue = (float32)((float32)((float32)Loc_uint16EnteredVoltageConversion / 4096) * 3.3f) ;
//    Loc_float32_33VoltageValue = (float32)((float32)((float32)Loc_uint16_33VoltageConversion / 4096) * 3.3f) * 2 ;
//
//    Loc_float32FinalVoltageValue = ((Loc_float32_33VoltageValue - Loc_float32EnteredVoltageValue) * 11) - 3.3f;
//
//    //snprintf((glbl_uint8VoltageBuffer + 1), (sizeof(glbl_uint8VoltageBuffer) - 1), "%.*f", 3,Loc_float32FinalVoltageValue);
//	float_to_string_manual((glbl_uint8VoltageBuffer + 1),Loc_float32FinalVoltageValue, 3);
//    glbl_uint8VoltageBuffer[0] = '-';
//    
//    HESP32_SendCommand(glbl_uint8VoltageBuffer);
//    SpectroStatus_SetNewStatus(IDLE);
//}
//
//
//void SCommands_GetSupply5Voltage(void)
//{
//    SpectroStatus_SetNewStatus(BUSY);
//    uint16 Loc_uint16VoltageConversion = 0;
//    float32 Loc_float32VoltageValue = 0.0;
//    uint8 glbl_uint8VoltageBuffer[32] = {0};
//
//    SPWRVolt_GetVoltage(SPWRVOLT_SUPPLY_5, &Loc_uint16VoltageConversion);
//
//    Loc_float32VoltageValue = ((float32)((float32)((float32)Loc_uint16VoltageConversion / 4096) * 3.3f) + 0.16f) * 2;
//
//    //snprintf(glbl_uint8VoltageBuffer, sizeof(glbl_uint8VoltageBuffer), "%.*f", 3,Loc_float32VoltageValue);
//    float_to_string_manual((glbl_uint8VoltageBuffer),Loc_float32VoltageValue, 3);
//    HESP32_SendCommand(glbl_uint8VoltageBuffer);
//    SpectroStatus_SetNewStatus(IDLE);
//}
//
//
//void SCommands_GetSupply33Voltage(void)
//{
//    SpectroStatus_SetNewStatus(BUSY);
//    uint16 Loc_uint16VoltageConversion = 0;
//    float32 Loc_float32VoltageValue = 0.0;
//    uint8 glbl_uint8VoltageBuffer[32] = {0};
//
//    SPWRVolt_GetVoltage(SPWRVOLT_SUPPLY_33, &Loc_uint16VoltageConversion);
//
//    Loc_float32VoltageValue = (float32)((float32)((float32)Loc_uint16VoltageConversion / 4096) * 3.3f) * 2;
//
//    //snprintf(glbl_uint8VoltageBuffer, sizeof(glbl_uint8VoltageBuffer), "%.*f", 3,Loc_float32VoltageValue);
//    float_to_string_manual((glbl_uint8VoltageBuffer),Loc_float32VoltageValue, 3);
//    
//    HESP32_SendCommand(glbl_uint8VoltageBuffer);
//    SpectroStatus_SetNewStatus(IDLE);
//}
//
//void SCommands_GetSupply12Voltage(void)
//{
//    SpectroStatus_SetNewStatus(BUSY);
//    uint16 Loc_uint16VoltageConversion = 0;
//    float32 Loc_float32VoltageValue = 0.0;
//    uint8 glbl_uint8VoltageBuffer[32] = {0};
//
//    SPWRVolt_GetVoltage(SPWRVOLT_SUPPLY_12, &Loc_uint16VoltageConversion);
//
//    Loc_float32VoltageValue = (float32)((float32)((float32)Loc_uint16VoltageConversion / 4096) * 3.3f) * 4;
//
//    //snprintf(glbl_uint8VoltageBuffer, sizeof(glbl_uint8VoltageBuffer), "%.*f", 3,Loc_float32VoltageValue);
//    float_to_string_manual((glbl_uint8VoltageBuffer),Loc_float32VoltageValue, 3);
//    
//    HESP32_SendCommand(glbl_uint8VoltageBuffer);
//    SpectroStatus_SetNewStatus(IDLE);
//}
