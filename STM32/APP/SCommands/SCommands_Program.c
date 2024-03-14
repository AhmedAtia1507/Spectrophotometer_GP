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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

#include "SCommands_Config.h"
#include "SCommands_Interface.h"

void get_uv_status                              (void);
void uv_on                                      (void);
void uv_off                                     (void);
void get_vis_status                             (void);
void vis_on                                     (void);
void vis_off                                    (void);
void read_dcdc_p12                              (void);
void read_dcdc_n12                              (void);
void read_supply_5                              (void);
void read_supply_33                             (void);
void read_supply_12                             (void);
void send_motor_steps                           (void);
void home_lamp_motor                            (void);
void home_grating_motor                         (void);
void home_filter_motor                          (void);
void send_current_WL                            (void);
void sndTime                                    (void);
void UpTime                                     (uint8*);
void move_motor                                 (uint8*);
void save_step                                  (uint8*);
void save_wave                                  (uint8*);
void start_scan                                 (uint8*);

static volatile uint8 glbl_uint8VoltageBuffer   [20]    = {0};
static volatile uint32 glbl_uint8MotorSteps     [3]     = {0};
static volatile uint32 glbl_uint8CurrentWL              = 0;



Std_ReturnType SCommands_Init(void)
{
    /***********************************Initialize System Clock***********************************/
    MRCC_InitClock();

    /***********************************Enable Peripherals' clocks***********************************/
	
    MRCC_EnablePeripheralClock              (MRCC_APB2,MRCC_APB2_IOPA_EN);
	MRCC_EnablePeripheralClock              (MRCC_APB2,MRCC_APB2_IOPB_EN);
	MRCC_EnablePeripheralClock              (MRCC_APB2, MRCC_APB2_IOPC_EN);
    
    /***********************************Setting Interrupts' Priorities***********************************/
	MSCB_SetPriorityGrouping                (MSCB_PRIORITY_GROUP_4_SUB_0);
	MNVIC_SetInterruptPriority              (MNVIC_EXTI15_10, 0, 0);
	MNVIC_SetInterruptPriority              (MNVIC_USART3, 1, 0);
	
    MGPIO_SetPinMode                        (SPECTRO_VIS_POWER_CONTROL_PORT_ID, SPECTRO_VIS_POWER_CONTROL_PIN_ID, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    MGPIO_SetPinMode                        (SPECTRO_UV_POWER_CONTROL_PORT_ID, SPECTRO_UV_POWER_CONTROL_PIN_ID, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
	
	HESP32_SetCommandCallbackFunction       (0, get_uv_status);
    HESP32_SetCommandCallbackFunction       (1, uv_on);
    HESP32_SetCommandCallbackFunction       (2, uv_off);
    HESP32_SetCommandCallbackFunction       (3, get_vis_status);
    HESP32_SetCommandCallbackFunction       (4, vis_on);
    HESP32_SetCommandCallbackFunction       (5, vis_off);
    HESP32_SetCommandCallbackFunction       (6, read_dcdc_p12);
    HESP32_SetCommandCallbackFunction       (7, read_dcdc_n12);
    HESP32_SetCommandCallbackFunction       (8, read_supply_5);
    HESP32_SetCommandCallbackFunction       (9, read_supply_33);
    HESP32_SetCommandCallbackFunction       (10, read_supply_12);
    HESP32_SetCommandCallbackFunction       (11, send_motor_steps);
    HESP32_SetCommandCallbackFunction       (12, home_lamp_motor);
    HESP32_SetCommandCallbackFunction       (13, home_grating_motor);
    HESP32_SetCommandCallbackFunction       (14, home_filter_motor);
    HESP32_SetCommandCallbackFunction       (15, send_current_WL);
    HESP32_SetCommandCallbackFunction       (16, sndTime);
    HESP32_SetCommandCallbackArgFunction    (17, UpTime);
    HESP32_SetCommandCallbackArgFunction    (18, move_motor);
    HESP32_SetCommandCallbackArgFunction    (19, save_step);
    HESP32_SetCommandCallbackArgFunction    (20, save_wave);
    HESP32_SetCommandCallbackArgFunction    (21, start_scan);

    HESP32_InitInterface();
    SPWRVolt_Init();
    MSTK_uint8Init();
    HMOTORS_Init();
	MRTC_Init();
    
    return E_OK;
}

void get_uv_status(void)
{
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
}
void uv_on(void)
{
    MGPIO_SetPinValue(SPECTRO_UV_POWER_CONTROL_PORT_ID, SPECTRO_UV_POWER_CONTROL_PIN_ID, MGPIO_HIGH);
    HESP32_SendCommand("on");
}
void uv_off(void)
{
    MGPIO_SetPinValue(SPECTRO_UV_POWER_CONTROL_PORT_ID, SPECTRO_UV_POWER_CONTROL_PIN_ID, MGPIO_LOW);
    HESP32_SendCommand("off");
}
void get_vis_status(void)
{
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
}
void vis_on(void)
{
    MGPIO_SetPinValue(SPECTRO_VIS_POWER_CONTROL_PORT_ID, SPECTRO_VIS_POWER_CONTROL_PIN_ID, MGPIO_HIGH);
    HESP32_SendCommand("on");
}
void vis_off(void)
{
    MGPIO_SetPinValue(SPECTRO_VIS_POWER_CONTROL_PORT_ID, SPECTRO_VIS_POWER_CONTROL_PIN_ID, MGPIO_LOW);
    HESP32_SendCommand("off");
}

void read_dcdc_p12(void)
{
    uint16 Loc_uint16VoltageConversion = 0;
    float32 Loc_float32VoltageValue = 0.0;

    SPWRVolt_GetVoltage(SPWRVOLT_DCDC_POS_12, &Loc_uint16VoltageConversion);

    Loc_float32VoltageValue = (float32)((float32)((float32)Loc_uint16VoltageConversion / 4096) * 3.3f) * 4;

    snprintf((glbl_uint8VoltageBuffer + 1), (sizeof(glbl_uint8VoltageBuffer) - 1), "%f", Loc_float32VoltageValue);
    glbl_uint8VoltageBuffer[0] = '+';

    HESP32_SendCommand(glbl_uint8VoltageBuffer);
}
void read_dcdc_n12(void)
{
    uint16 Loc_uint16EnteredVoltageConversion = 0;
    uint16 Loc_uint16_33VoltageConversion = 0;
    float32 Loc_float32EnteredVoltageValue = 0.0;
    float32 Loc_float32_33VoltageValue = 0.0;
    float32 Loc_float32FinalVoltageValue = 0.0;

    SPWRVolt_GetVoltage(SPWRVOLT_DCDC_NEG_12, &Loc_uint16EnteredVoltageConversion);
    SPWRVolt_GetVoltage(SPWRVOLT_SUPPLY_33, &Loc_uint16_33VoltageConversion);

    Loc_float32EnteredVoltageValue = (float32)((float32)((float32)Loc_uint16EnteredVoltageConversion / 4096) * 3.3f) ;
    Loc_float32_33VoltageValue = (float32)((float32)((float32)Loc_uint16_33VoltageConversion / 4096) * 3.3f) ;

    Loc_float32FinalVoltageValue = ((Loc_float32_33VoltageValue - Loc_float32EnteredVoltageValue) * 11) - 3.3f;

    snprintf((glbl_uint8VoltageBuffer + 1), (sizeof(glbl_uint8VoltageBuffer) - 1), "%f", Loc_float32FinalVoltageValue);
    glbl_uint8VoltageBuffer[0] = '-';
    
    HESP32_SendCommand(glbl_uint8VoltageBuffer);
}
void read_supply_5(void)
{
    uint16 Loc_uint16VoltageConversion = 0;
    float32 Loc_float32VoltageValue = 0.0;

    SPWRVolt_GetVoltage(SPWRVOLT_SUPPLY_5, &Loc_uint16VoltageConversion);

    Loc_float32VoltageValue = (float32)((float32)((float32)Loc_uint16VoltageConversion / 4096) * 3.3f) * 2;

    snprintf(glbl_uint8VoltageBuffer, sizeof(glbl_uint8VoltageBuffer), "%f", Loc_float32VoltageValue);
    
    HESP32_SendCommand(glbl_uint8VoltageBuffer);
}
void read_supply_33(void)
{
    uint16 Loc_uint16VoltageConversion = 0;
    float32 Loc_float32VoltageValue = 0.0;

    SPWRVolt_GetVoltage(SPWRVOLT_SUPPLY_33, &Loc_uint16VoltageConversion);

    Loc_float32VoltageValue = (float32)((float32)((float32)Loc_uint16VoltageConversion / 4096) * 3.3f) * 2;

    snprintf(glbl_uint8VoltageBuffer, sizeof(glbl_uint8VoltageBuffer), "%f", Loc_float32VoltageValue);
    
    HESP32_SendCommand(glbl_uint8VoltageBuffer);
}

void read_supply_12(void)
{
    uint16 Loc_uint16VoltageConversion = 0;
    float32 Loc_float32VoltageValue = 0.0;

    SPWRVolt_GetVoltage(SPWRVOLT_SUPPLY_12, &Loc_uint16VoltageConversion);

    Loc_float32VoltageValue = (float32)((float32)((float32)Loc_uint16VoltageConversion / 4096) * 3.3f) * 4;

    snprintf(glbl_uint8VoltageBuffer, sizeof(glbl_uint8VoltageBuffer), "%f", Loc_float32VoltageValue);
    
    HESP32_SendCommand(glbl_uint8VoltageBuffer);
}
void send_motor_steps   (void)
{
    HESP32_SendMotorStatus(glbl_uint8MotorSteps, &glbl_uint8CurrentWL, 3);
}
void home_lamp_motor    (void)
{
    HMOTOR_GoHome(HMOTOR_LAMP_SELECT);
    glbl_uint8MotorSteps[0] = 0;
    HESP32_SendMotorStatus(&glbl_uint8MotorSteps[0], &glbl_uint8CurrentWL, 1);
}
void home_grating_motor (void)
{
    HMOTOR_GoHome(HMOTOR_WL_SELECT);
    glbl_uint8MotorSteps[2] = 0;
    HESP32_SendMotorStatus(&glbl_uint8MotorSteps[2], &glbl_uint8CurrentWL, 1);
}
void home_filter_motor  (void)
{
    HMOTOR_GoHome(HMOTOR_FILTER_SELECT);
    glbl_uint8MotorSteps[1] = 0;
		glbl_uint8CurrentWL = 190;
    HESP32_SendMotorStatus(&glbl_uint8MotorSteps[1], &glbl_uint8CurrentWL, 1);
}
void send_current_WL    (void)
{
    uint8 P_uint8WL[20] = {0};
    snprintf(P_uint8WL, sizeof(P_uint8WL), "%d", glbl_uint8CurrentWL);
    HESP32_SendCommand(P_uint8WL);
}
void sndTime(void)
{
    Sdate_t current_date;
    Stime_t current_time;

    MRTC_GetDateAndTime(&current_date, &current_time);

    HESP32_SendDataTime(&current_date, &current_time);
}

void UpTime(uint8* P_uint8DateTime)
{
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
}
void move_motor         (uint8* P_uint8MotorSteps)
{
    if(P_uint8MotorSteps != NULL_PTR)
    {
        uint32 Loc_uint32MotorSteps = atoi(P_uint8MotorSteps);
        uint32 Loc_uint32MotorDiff = 0;
        if(Loc_uint32MotorSteps > glbl_uint8MotorSteps[1])
        {
            Loc_uint32MotorDiff = Loc_uint32MotorSteps - glbl_uint8MotorSteps[1];
            HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32MotorDiff, HMOTORS_CLKWISE_DIRECTION);
            glbl_uint8MotorSteps[1] = Loc_uint32MotorSteps;
        }
        else if(Loc_uint32MotorSteps < glbl_uint8MotorSteps[1])
        {
            Loc_uint32MotorDiff = glbl_uint8MotorSteps[1] - Loc_uint32MotorSteps;
            HMOTOR_Step(HMOTOR_FILTER_SELECT, Loc_uint32MotorDiff, HMOTORS_CCLKWISE_DIRECTION);
            glbl_uint8MotorSteps[1] = Loc_uint32MotorSteps;
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
}
void save_step          (uint8* P_uint8MotorSteps)
{
	if(P_uint8MotorSteps != NULL_PTR)
	{
		HESP32_SendCommand("saved");
	}
	else
	{
		HESP32_SendCommand("failed to save");
	}
}
void save_wave          (uint8* P_uint8Wavelength)
{
	if(P_uint8Wavelength != NULL_PTR)
	{
		HESP32_SendCommand("saved");
	}
	else
	{
		HESP32_SendCommand("failed to save");
	}
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


void start_scan         (uint8* P_uint8ScanParam)
{
    if(P_uint8ScanParam != NULL_PTR)
    {
        float32 Loc_float32ScanParameters[3] = {0.0};
        uint8* P_uint8Token = NULL_PTR;
        uint8 Loc_uint8Index = 0;

        P_uint8Token = strtok(P_uint8ScanParam, " ");
        Loc_float32ScanParameters[Loc_uint8Index] = atof(P_uint8Token);
        Loc_uint8Index++;

        while((P_uint8Token != NULL_PTR) && (Loc_uint8Index < 3))
        {
            P_uint8Token = strtok(NULL_PTR, " ");
            Loc_float32ScanParameters[Loc_uint8Index++] = atof(P_uint8Token);
        }

        if(Loc_uint8Index == 3)
        {
            HMOTOR_GoHome(HMOTOR_FILTER_SELECT);
            glbl_uint8MotorSteps[1] = 0;

            float32 Loc_float32Index = Loc_float32ScanParameters[0];
            float32 Loc_float32RefIntensity = 0.0;
            float32 Loc_float32SampleIntensity = 0.0;

            while(Loc_float32Index < Loc_float32ScanParameters[1])
            {
                generate_random_values(&Loc_float32RefIntensity, &Loc_float32SampleIntensity);
                HESP32_SendIntensities(&Loc_float32RefIntensity, &Loc_float32SampleIntensity);
                HMOTOR_Step(HMOTOR_FILTER_SELECT, 1, HMOTORS_CLKWISE_DIRECTION);
                MSTK_uint8Delay(1000);
                Loc_float32Index += Loc_float32ScanParameters[2];
            }
			HESP32_SendCommand("done");
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