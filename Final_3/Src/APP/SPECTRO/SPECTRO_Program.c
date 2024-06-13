/**
 * @file SPECTRO_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * 
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/Std_Types.h"

#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/RTC/RTC_Interface.h"
#include "../../MCAL/UART/UART_Interface.h"
#include "../../MCAL/STK/STK_Interface.h"
#include "../../MCAL/NVIC/NVIC_Interface.h"
#include "../../MCAL/SCB/SCB_Interface.h"
#include "../../MCAL/RCC/RCC_Interface.h"
#include "../../MCAL/GPTMR/GPTMR_Interface.h"

#include "../../HAL/ESP32/ESP32_Interface.h"
#include "../../HAL/SPWRVolt/SPWRVolt_Interface.h"
#include "../../HAL/STEPPER_MOTOR/MOTORS_Interface.h"
#include "../../HAL/EEPROM/I2C_Slave_EEPROM.h"
#include "../../HAL/PWRSupply/HPWRSupply_Interface.h"
#include "../../HAL/ADS1115/ADC.h"
#include "../../HAL/MCP4151/MCP4151.h"

#include "../../APP/SCommands/SCommands_Interface.h"
#include "../../APP/SPECTRO/SPECTRO_Interface.h"
#include "../../APP/SpectroStatus/SpectroStatus_Interface.h"
#include "../../APP/Signal_Conditioning/signal_conditioning.h"


Std_ReturnType SPECTRO_InitSystem(void)
{
	SpectroStatus_SetNewStatus(INITIALIZING);
	Std_ReturnType Loc_uint8InitStatus = E_NOT_OK;
	Loc_uint8InitStatus = SPECTRO_InitSoftware();
	if(Loc_uint8InitStatus == E_OK)
	{
		Loc_uint8InitStatus = SPECTRO_InitHardware();
		if(Loc_uint8InitStatus == E_OK)
		{
			SpectroStatus_SetNewStatus(IDLE);
		}
		else
		{
			SpectroStatus_SetNewStatus(ERROR_INITIALIZING);
		}
	}
	else
	{
		SpectroStatus_SetNewStatus(ERROR_INITIALIZING);
	}
	return Loc_uint8InitStatus;
}

Std_ReturnType SPECTRO_InitSoftware(void)
{
	/***********************************Initialize System Clock***********************************/
	MRCC_InitClock();

	/***********************************Enable Peripherals' clocks***********************************/

	MRCC_EnablePeripheralClock              (MRCC_APB2,MRCC_APB2_IOPA_EN);
	MRCC_EnablePeripheralClock              (MRCC_APB2,MRCC_APB2_IOPB_EN);
	MRCC_EnablePeripheralClock              (MRCC_APB2, MRCC_APB2_IOPC_EN);
	MRCC_EnablePeripheralClock              (MRCC_APB2, MRCC_APB2_AFIO_EN);
	MRCC_EnablePeripheralClock              (MRCC_APB1, MRCC_APB1_SPI2_EN);
	MRCC_EnablePeripheralClock              (MRCC_APB1, MRCC_APB1_TIM2_EN);


	/***********************************Setting Interrupts' Priorities***********************************/
	MSCB_SetPriorityGrouping                (MSCB_PRIORITY_GROUP_4_SUB_0);
	MNVIC_SetInterruptPriority              (MNVIC_EXTI15_10, 0, 0);
	MNVIC_SetInterruptPriority              (MNVIC_USART3, 1, 0);
	MNVIC_SetInterruptPriority				(MNVIC_TIM5, 2, 0);

	MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN8, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
	MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN2, MGPIO_OUTPUT_PUSH_PULL_2MHZ);

	MRTC_Init();
	MSTK_uint8Init();
	adc_init();
	//eeprom_init();
	uint8 Loc_uint8dummyData = 27;
	eeprom_write_Nbytes(EEPROM_MOTOR_STEPS_MEM_ADDRESS, &Loc_uint8dummyData, 1);
	SCommands_Init();
	SPWRVolt_Init();


	//eeprom_init();

	MCP4151_Init();
	HPWRSupply_InitSupplies();
	HMOTORS_Init();

	MNVIC_EnableInterrupt(MNVIC_TIM2);
	MGPTMR_SetTimerPeriod(MGPTMR2, 5);
	MGPTMR_Init(MGPTMR2);



	return E_OK;
}
Std_ReturnType SPECTRO_InitHardware(void)
{
	Std_ReturnType Loc_uint8InitStatus = E_NOT_OK;

	Loc_uint8InitStatus = HPWRSupply_SetSupplyMode(HPWRSUPPLY_UV_SUPPLY, HPWRSUPPLY_ON);

	if(Loc_uint8InitStatus == E_OK)
	{
		Loc_uint8InitStatus = HPWRSupply_SetSupplyMode(HPWRSUPPLY_UV_SUPPLY, HPWRSUPPLY_OFF);
		if(Loc_uint8InitStatus == E_OK)
		{
			Loc_uint8InitStatus = HPWRSupply_SetSupplyMode(HPWRSUPPLY_VIS_SUPPLY, HPWRSUPPLY_ON);
			if(Loc_uint8InitStatus == E_OK)
			{
				Loc_uint8InitStatus = HPWRSupply_SetSupplyMode(HPWRSUPPLY_VIS_SUPPLY, HPWRSUPPLY_OFF);
				if(Loc_uint8InitStatus == E_OK)
				{
					Loc_uint8InitStatus = SPECTRO_InitCalibration();
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
	return Loc_uint8InitStatus;
}

static volatile uint32 glbl_uint32FunctionCounter = 0;
static volatile float32 glbl_float32MaxValue[2] = {0.0};
static volatile uint32 glbl_float32MaxStepsIndex = 0;
static volatile float32 glbl_float32MaxSteps[2] = {0.0};
static volatile uint8 glbl_uint8Buffer[32] = {0};

void SPECTRO_CalibrationScan(void)
{
	glbl_uint32FunctionCounter++;
	HMOTOR_StepNoDelay(HMOTOR_WL_SELECT, HMOTORS_CLKWISE_DIRECTION);
	if((glbl_uint32FunctionCounter <= 400) || (glbl_uint32FunctionCounter >= 6620))
	{
		float32 de7k = 0.0, gain = 0.0;
		if(glbl_uint32FunctionCounter <= 400)
		{
			read_reference_voltage(&de7k, &gain);
			MUART_SendIntegerValue(UART3, glbl_uint32FunctionCounter);
			MUART_TxChar(UART3, ':');
			MUART_TxChar(UART3, ' ');

			float_to_string_manual(glbl_uint8Buffer, de7k, 3);
			MUART_TxString(UART3, glbl_uint8Buffer);
			MUART_TxChar(UART3, '\n');

			if(de7k > glbl_float32MaxValue[0])
			{
				glbl_float32MaxValue[0] = de7k;
				glbl_float32MaxSteps[0] = glbl_uint32FunctionCounter;
			}
		}
		else if((glbl_uint32FunctionCounter >= 6300) && (glbl_uint32FunctionCounter < 7300))
		{
			read_reference_voltage(&de7k, &gain);
			MUART_SendIntegerValue(UART3, glbl_uint32FunctionCounter);
			MUART_TxChar(UART3, ':');
			MUART_TxChar(UART3, ' ');

			float_to_string_manual(glbl_uint8Buffer, de7k, 3);
			MUART_TxString(UART3, glbl_uint8Buffer);
			MUART_TxChar(UART3, '\n');
			if(de7k > glbl_float32MaxValue[1])
			{
				glbl_float32MaxValue[1] = de7k;
				glbl_float32MaxSteps[1] = glbl_uint32FunctionCounter;
			}
		}
		else if((glbl_uint32FunctionCounter >= 7300))
		{
			MGPTMR_StopTimer(MGPTMR2);
		}
	}
	else
	{
	}
}

Std_ReturnType SPECTRO_InitCalibration(void)
{
	float32 Loc_uint32StepsPerNm = 0;
	HMOTOR_GoHome(HMOTOR_LAMP_SELECT);
	//HMOTOR_GoHome(HMOTOR_FILTER_SELECT);
	HMOTOR_GoHome(HMOTOR_WL_SELECT);

	//turn on visible lamp
	HPWRSupply_SetSupplyMode(HPWRSUPPLY_UV_SUPPLY, HPWRSUPPLY_ON);
	HMOTOR_MoveLampMotor(HMOTOR_LAMP_UV);
	//HMOTOR_MoveFilterMotor(HMOTOR_FILTER_AIR);

	//Zero Wavelength
	uint32 Loc_uint32Index = 0;
	float32	Loc_float32Gain = 0;
	//float32 Loc_uint32WhiteLightIntensities[110] = {0};
	float32 Loc_float32Reading = 0.0;

	MGPTMR_SetTimerUpdateCallbackFunc(MGPTMR2, SPECTRO_CalibrationScan);
	MGPTMR_StartTimer(MGPTMR2);
	

	//uint32 Loc_uint32ZeroWLSteps = 0;
	//HMOTOR_Step(HMOTOR_WL_SELECT, 77, HMOTORS_CLKWISE_DIRECTION, 10);
	//adc_init();
	//for(Loc_uint32Index = 0; Loc_uint32Index < 110; Loc_uint32Index++)
	//{
	//	MUART_SendIntegerValue(UART3, Loc_uint32Index);
	//	MUART_TxChar(UART3, ':');
	//	MUART_TxChar(UART3, ' ');
	//	read_sample_voltage(&Loc_uint32WhiteLightIntensities[Loc_uint32Index], &Loc_float32Gain);
	//	//HMOTOR_GetCurrentMotorSteps(HMOTOR_WL_SELECT, &Loc_uint32WhiteLightSteps[Loc_uint32Index]);
	//	HESP32_SendDetectorValues(&Loc_uint32WhiteLightIntensities[Loc_uint32Index], &Loc_float32Gain);
	//	HMOTOR_Step(HMOTOR_WL_SELECT, 1, HMOTORS_CLKWISE_DIRECTION, 4);
	//	MSTK_uint8Delay(50);
	//}
	//uint32 Loc_uint32MiddleStepIndex = Medium_Step_Index(Loc_uint32WhiteLightIntensities, 110);
	//Loc_uint32ZeroWLSteps = Loc_uint32MiddleStepIndex;
	//MUART_TxString(UART3, "Zero Wavelength Steps = ");
	//MUART_SendIntegerValue(UART3, Loc_uint32ZeroWLSteps);
	//MUART_TxChar(UART3, '\n');


	//HPWRSupply_SetSupplyMode(HPWRSUPPLY_VIS_SUPPLY, HPWRSUPPLY_OFF);
	//HPWRSupply_SetSupplyMode(HPWRSUPPLY_UV_SUPPLY, HPWRSUPPLY_ON);
	//HMOTOR_MoveLampMotor(HMOTOR_LAMP_UV);
//
	//float32 Loc_float32Voltages = 0.0;
	//uint32 Loc_uint32MaxIndex = 0;
	//float32 Loc_float32MaxIntensity = 0.0;
	//HMOTOR_Step(HMOTOR_WL_SELECT, 790, HMOTORS_CLKWISE_DIRECTION, 4);
	//MUART_SendIntegerValue(UART3, 0);
	//MUART_TxChar(UART3, ':');
	//MUART_TxChar(UART3, ' ');
	//read_reference_voltage(&Loc_float32Voltages, &Loc_float32Gain);
	//HESP32_SendDetectorValues(&Loc_float32Voltages, &Loc_float32Gain);
	////read_sample_voltage(&reading, &gain);
	////HESP32_SendDetectorValues(&reading, &gain);
	//Loc_float32MaxIntensity = Loc_float32Voltages;
	////adc_init();
	//for(Loc_uint32Index = 1; Loc_uint32Index < 600; Loc_uint32Index++)
	//{
	//	MUART_SendIntegerValue(UART3, Loc_uint32Index);
	//	MUART_TxChar(UART3, ':');
	//	MUART_TxChar(UART3, ' ');
	//	read_reference_voltage(&Loc_float32Voltages, &Loc_float32Gain);
	//	HESP32_SendDetectorValues(&Loc_float32Voltages, &Loc_float32Gain);
	//	HMOTOR_Step(HMOTOR_WL_SELECT, 1, HMOTORS_CLKWISE_DIRECTION, 4);
	//	MSTK_uint8Delay(50);
	//	if(Loc_float32Voltages > Loc_float32MaxIntensity)
	//	{
	//		Loc_float32MaxIntensity = Loc_float32Voltages;
	//		Loc_uint32MaxIndex = Loc_uint32Index;
	//	}
	//}
	//MUART_TxString(UART3, "UV Maximum Steps = ");
	//MUART_SendIntegerValue(UART3, (Loc_uint32MaxIndex + 900));
	//MUART_TxChar(UART3, '\n');
//
	//Loc_uint32StepsPerNm = (float32)(Loc_uint32MaxIndex + 900 - Loc_uint32ZeroWLSteps) / 656.1f;
	//uint8 Loc_uint8Buffer[32] = {0};
	//float_to_string_manual(Loc_uint8Buffer, Loc_uint32StepsPerNm, 3);
	//MUART_TxString(UART3, "Steps/nm = ");
	////MUART_SendIntegerValue(UART3, Loc_uint32StepsPerNm);
	//MUART_TxString(UART3, Loc_uint8Buffer);
	//MUART_TxChar(UART3, '\n');
	//HMOTOR_GetWLSelectCalibration(Loc_uint32ZeroWLSteps, Loc_uint32StepsPerNm);
	//HMOTOR_GoHome(HMOTOR_WL_SELECT);
	//HMOTOR_Step(HMOTOR_WL_SELECT, Loc_uint32ZeroWLSteps, HMOTORS_CLKWISE_DIRECTION, 4);
	return E_OK;
}

//*************************************************************************/
//*************************************************************************/
//**********************Mohanad was here***********************************/
//*************************************************************************/
//*************************************************************************/

unsigned char Medium_Step_Index(float* readings, unsigned char size)
{
	float max = readings[0], min = readings[0];
	for(unsigned char i = 0; i < size; i++)
	{
		if(readings[i] > max)
		{
			max = readings[i];
		}
		if(readings[i] < min)
		{
			min = readings[i];
		}
	}
	float threshold = (max+min)/2.0f;
	unsigned char first_step_index = 0, last_step_index = 0, indicator = 0;
	for(unsigned char i = 0; i < size; i++)
	{
		if((readings[i] > threshold) && (indicator == 0))
		{
			indicator = 1;
			first_step_index = i;
			continue;
		}
		if((readings[i] < threshold) && (indicator == 1))
		{
			last_step_index = i;
			break;
		}
	}
	return (((last_step_index + first_step_index)/2));
}
