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
    
    
    /***********************************Setting Interrupts' Priorities***********************************/
	MSCB_SetPriorityGrouping                (MSCB_PRIORITY_GROUP_4_SUB_0);
	MNVIC_SetInterruptPriority              (MNVIC_EXTI15_10, 0, 0);
	MNVIC_SetInterruptPriority              (MNVIC_USART3, 1, 0);
	
	//MRTC_Init();
	MSTK_uint8Init();
	eeprom_init();
	uint32 Loc_uint32dummyData = 32;
	//eeprom_write_Nbytes(EEPROM_MOTOR_STEPS_MEM_ADDRESS, &Loc_uint32dummyData, 4);
    //SCommands_Init();
    //SPWRVolt_Init();
    
    
    //eeprom_init();
    adc_init();
    MCP4151_Init();
    //HPWRSupply_InitSupplies();
	//HMOTORS_Init();

    return E_OK;
}
Std_ReturnType SPECTRO_InitHardware(void)
{
    Std_ReturnType Loc_uint8InitStatus = E_NOT_OK;

    Loc_uint8InitStatus = HPWRSupply_SetSupplyMode(HPWRSUPPLY_VIS_SUPPLY, HPWRSUPPLY_ON);

    if(Loc_uint8InitStatus == E_OK)
    {
        Loc_uint8InitStatus = HPWRSupply_SetSupplyMode(HPWRSUPPLY_VIS_SUPPLY, HPWRSUPPLY_OFF);
        if(Loc_uint8InitStatus == E_OK)
        {
            Loc_uint8InitStatus = HPWRSupply_SetSupplyMode(HPWRSUPPLY_UV_SUPPLY, HPWRSUPPLY_ON);
            if(Loc_uint8InitStatus == E_OK)
            {
                Loc_uint8InitStatus = HPWRSupply_SetSupplyMode(HPWRSUPPLY_UV_SUPPLY, HPWRSUPPLY_OFF);
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
Std_ReturnType SPECTRO_InitCalibration(void)
{
    uint32 Loc_uint32StepsPerNm = 0;
	HMOTOR_GoHome(HMOTOR_LAMP_SELECT);
	HMOTOR_GoHome(HMOTOR_FILTER_SELECT);
	HMOTOR_GoHome(HMOTOR_WL_SELECT);

	//turn on visible lamp
    HPWRSupply_SetSupplyMode(HPWRSUPPLY_VIS_SUPPLY, HPWRSUPPLY_ON);
	HMOTOR_MoveLampMotor(HMOTOR_LAMP_VIS);
	HMOTOR_MoveFilterMotor(HMOTOR_FILTER_AIR);

	float32 Loc_float32ADCValue = 0.0;
    
	//Zero Wavelength
	uint32 Loc_uint32Index = 0, Loc_uint32Indicator = 0;
	uint32 Loc_uint32WhiteLightSteps = 0;
	for(Loc_uint32Index = 0; Loc_uint32Index < 1500; Loc_uint32Index++)
	{
		//check adc until very high intensity
		// if found, indicator = 1
		//save start position of white light
	}

    HMOTOR_GetCurrentMotorSteps(HMOTOR_WL_SELECT, &Loc_uint32WhiteLightSteps);

	if(Loc_uint32Indicator == 1)
	{
		HPWRSupply_SetSupplyMode(HPWRSUPPLY_VIS_SUPPLY, HPWRSUPPLY_OFF);
        HPWRSupply_SetSupplyMode(HPWRSUPPLY_UV_SUPPLY, HPWRSUPPLY_ON);
		HMOTOR_MoveLampMotor(HMOTOR_LAMP_UV);

		uint8 Loc_uint8Index_2 = 0;
		float32 Loc_float32Voltages[20] = {0.0};
		uint32 Loc_uint32Steps[20] = {0};
        uint32 Loc_uint32CurrentFilterSteps = 0;

        HMOTOR_GetCurrentMotorSteps(HMOTOR_FILTER_SELECT, &Loc_uint32CurrentFilterSteps);

		for(Loc_uint32Index = 0; Loc_uint32Index < 4500; Loc_uint32Index++)
		{
			//Check adc value
			if(Loc_float32ADCValue > 2.0f)
			{
				Loc_float32Voltages[Loc_uint8Index_2] = Loc_float32ADCValue;
				Loc_uint32Steps[Loc_uint8Index_2] = Loc_uint32CurrentFilterSteps;
				Loc_uint8Index_2++;
			}
			if(Loc_uint8Index_2 > 20)
			{
				break;
			}
			// move monochromator and check if adc value is greater than threshold
		}

		float32 Loc_float32MaxIntensity = Loc_float32Voltages[0];
		uint8 Loc_uint8MaxIndex = 0;

		for(Loc_uint32Index = 1; Loc_uint32Index < 20; Loc_uint32Index++)
		{
			if(Loc_float32Voltages[Loc_uint32Index] > Loc_float32MaxIntensity)
			{
				Loc_float32MaxIntensity = Loc_float32Voltages[Loc_uint32Index];
				Loc_uint8MaxIndex = Loc_uint32Index;
			}
		}

		Loc_uint32StepsPerNm = (Loc_uint32Steps[Loc_uint8MaxIndex] - Loc_uint32WhiteLightSteps) / 656.1f;
		return E_OK;
	}
	else
	{
		return E_NOT_OK;
	}
}