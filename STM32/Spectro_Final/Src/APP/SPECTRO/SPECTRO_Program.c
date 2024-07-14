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


/**
 * @brief: Function to initialize the spectrophotometer system.
 * 
 * This function sets the system status to INITIALIZING, initializes software and hardware, 
 * and updates the system status accordingly.
 * 
 * @return Std_ReturnType
 * @retval E_OK: 					If initialization is successful
 * @retval E_NOT_OK: 				Otherwise
 */
Std_ReturnType SPECTRO_InitSystem	(void)
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

/**
 * @brief Function to initialize the software components of the spectrophotometer system.
 * 
 * This function initializes the system clock, enables peripheral clocks, sets interrupt priorities,
 * and initializes various modules such as RTC, SysTick, ADC, commands, power supply voltages, MCP4151,
 * motors, and timers.
 * 
 * @return Std_ReturnType
 * @retval E_OK: 						If software initialization is successful
 * @retval E_NOT_OK: 					Otherwise
 */
Std_ReturnType SPECTRO_InitSoftware		(void)
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
	MNVIC_SetInterruptPriority				(MNVIC_TIM2, 2, 0);

	MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN8, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
	MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN2, MGPIO_OUTPUT_PUSH_PULL_2MHZ);

	MRTC_Init();
	MSTK_uint8Init();
	adc_init();
	SCommands_Init();
	SPWRVolt_Init();

	MCP4151_Init();
	HPWRSupply_InitSupplies();
	HMOTORS_Init();

	MNVIC_EnableInterrupt(MNVIC_TIM2);
	MGPTMR_Init(MGPTMR2);

	return E_OK;
}
/**
 * @brief Function to initialize the hardware components of the spectrophotometer system.
 * 
 * This function checks on UV and VIS supplies, and initiates the system calibration.
 * 
 * @return Std_ReturnType
 * @retval E_OK: 						If hardware initialization is successful
 * @retval E_NOT_OK: 					Otherwise
 */
Std_ReturnType SPECTRO_InitHardware		(void)
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

static volatile sint32 glbl_sint32FunctionCounter = 0;
static volatile float32 glbl_float32MaxValue[2] = {0.0};
static volatile uint32 glbl_float32MaxStepsIndex = 0;
static volatile sint32 glbl_sint32MaxSteps[2] = {0.0};
static volatile sint32 glbl_sint32SavedZeroWL = 0;
static volatile sint32 glbl_sint32ZeroWLStartStep = 0;
static volatile sint32 glbl_sint32ZeroWLStopStep = 0;

/**
 * @brief Function to perform a calibration scan to determine the zero wavelength and 656.1 nm steps.
 * 
 * This function moves the wavelength selection motor step by step and reads the reference voltage
 * at specific steps to determine the maximum values for zero wavelength and 656.1 nm.
 */
void SPECTRO_CalibrationScan			(void)
{
	glbl_sint32FunctionCounter++;
	HMOTOR_StepNoDelay(HMOTOR_WL_SELECT, HMOTORS_CLKWISE_DIRECTION);
	float32 de7k = 0.0, gain = 0.0;

	if((glbl_sint32FunctionCounter >= glbl_sint32ZeroWLStartStep) && (glbl_sint32FunctionCounter <= glbl_sint32ZeroWLStopStep))
	{
		read_reference_voltage(&de7k, &gain);
		if(de7k > glbl_float32MaxValue[0])
		{
			glbl_float32MaxValue[0] = de7k;
			glbl_sint32MaxSteps[0] = glbl_sint32FunctionCounter; //zero WL steps
		}
	}
	else if((glbl_sint32FunctionCounter >= (glbl_sint32ZeroWLStopStep + 6000)) && (glbl_sint32FunctionCounter <= (glbl_sint32ZeroWLStopStep + 7000)))
	{
		read_reference_voltage(&de7k, &gain);
		if(de7k > glbl_float32MaxValue[1])
		{
			glbl_float32MaxValue[1] = de7k;
			glbl_sint32MaxSteps[1] = glbl_sint32FunctionCounter; //656.1nm Steps
		}
	}
	else if((glbl_sint32FunctionCounter > (glbl_sint32ZeroWLStopStep + 7500)))
	{
		MGPTMR_StopTimer(MGPTMR2);
		float32 Loc_float32StepsPerNm = ((float32)glbl_sint32MaxSteps[1] - (float32)glbl_sint32MaxSteps[0]) / 656.1f;
		HMOTOR_GetWLSelectCalibration(glbl_sint32MaxSteps[0], Loc_float32StepsPerNm);
		HMOTOR_MoveWLSelectMotor(190);
	}
}

/**
 * @brief Initializes the calibration process for the spectrophotometer system.
 * 
 * This function homes the motors, reads the saved zero wavelength from EEPROM, and starts a calibration scan
 * to determine the zero wavelength and 656.1 nm steps.
 * 
 * @return Std_ReturnType 
 * @retval E_OK: 						If calibration initialization is successful
 * @retval E_NOT_OK: 					Otherwise
 */
Std_ReturnType SPECTRO_InitCalibration	(void)
{
	float32 Loc_uint32StepsPerNm = 0;
	HMOTOR_GoHome(HMOTOR_LAMP_SELECT);
	//HMOTOR_GoHome(HMOTOR_FILTER_SELECT);
	HMOTOR_GoHome(HMOTOR_WL_SELECT);

	//turn on uv lamp
	eeprom_read_integer(EEPROM_GRATING_STEPS_MEM_ADDRESS, &glbl_sint32SavedZeroWL);

	if(glbl_sint32SavedZeroWL == 0)
	{
		glbl_sint32ZeroWLStartStep = 0;
		glbl_sint32ZeroWLStopStep = 400;
	}
	else
	{
		glbl_sint32ZeroWLStartStep = glbl_sint32SavedZeroWL - 20;
		glbl_sint32ZeroWLStopStep = glbl_sint32SavedZeroWL + 20;
		
		if(glbl_sint32SavedZeroWL < 0)
		{
			HMOTOR_Step(HMOTOR_WL_SELECT, (uint32)(-(glbl_sint32ZeroWLStartStep - 1)), HMOTORS_CCLKWISE_DIRECTION, 4);
		}
		else if(glbl_sint32SavedZeroWL > 0)
		{
			HMOTOR_Step(HMOTOR_WL_SELECT, (uint32)((glbl_sint32ZeroWLStartStep - 1)), HMOTORS_CLKWISE_DIRECTION, 4);
		}
		else
		{
			/*Do nothing*/
		}
	}

	glbl_sint32FunctionCounter = glbl_sint32ZeroWLStartStep;

	HPWRSupply_SetSupplyMode(HPWRSUPPLY_UV_SUPPLY, HPWRSUPPLY_ON);
	HPWRSupply_SetSupplyMode(HPWRSUPPLY_VIS_SUPPLY, HPWRSUPPLY_ON);

	HMOTOR_MoveLampMotor(HMOTOR_LAMP_UV);
	MGPTMR_SetTimerUpdateCallbackFunc(MGPTMR2, SPECTRO_CalibrationScan);
	MGPTMR_SetTimerPeriod(MGPTMR2, 15);
	MGPTMR_StartTimer(MGPTMR2);
	
	return E_OK;
}

//*************************************************************************/
//*************************************************************************/
//**********************Mohanad was here***********************************/
//*************************************************************************/
//*************************************************************************/

