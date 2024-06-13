/**
 * @file HPWRSupply_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2024-03-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/Std_Types.h"

#include "../../MCAL/RCC/RCC_Interface.h"
#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"
#include "../../MCAL/GPTMR/GPTMR_Interface.h"
#include "../../MCAL/NVIC/NVIC_Interface.h"
#include "../../MCAL/STK/STK_Interface.h"

#include "HPWRSupply_Interface.h"
#include "HPWRSupply_Config.h"
#include "HPWRSupply_Private.h"

static volatile HPWRSupply_Mode_t glbl_uint8SupplyFlags[HPWRSUPPLY_NO_OF_CONTROL_PINS] = {HPWRSUPPLY_OFF};
static volatile uint16 glbl_uint16SenseValue[HPWRSUPPLY_NO_OF_SENSE_CHANNELS] = {0};
static volatile uint8 glbl_uint8SlowChannelFlag = 0;


void HPWRSupply_GetSenseValue(void)
{
    uint16 Loc_uint16VoltageValue = 0;
    
    /****************************Check if VIS supply is turned on or off****************************/
    if(glbl_uint8SupplyFlags[0] == HPWRSUPPLY_ON)
    {
        MADC_Conversion(MADC1, glbl_uint8PWRSupplySenseChannelIDs[0], &Loc_uint16VoltageValue);
        glbl_uint16SenseValue[0] = Loc_uint16VoltageValue;
        if(glbl_uint8SlowChannelFlag == 1)
        {
            MADC_Conversion(MADC1, glbl_uint8PWRSupplySenseChannelIDs[1], &Loc_uint16VoltageValue);
            glbl_uint16SenseValue[1] = Loc_uint16VoltageValue;
            glbl_uint8SlowChannelFlag = 0;
        }
        else
        {
            glbl_uint8SlowChannelFlag = 1;
        }
    }
    else
    {
        /*Do nothing*/
    }

    /****************************Check if UV supply is turned on or off****************************/
    if(glbl_uint8SupplyFlags[1] == HPWRSUPPLY_ON)
    {
        MADC_Conversion(MADC1, glbl_uint8PWRSupplySenseChannelIDs[2], &Loc_uint16VoltageValue);
        glbl_uint16SenseValue[2] = Loc_uint16VoltageValue;
    }
    else
    {
        /*Do nothing*/
    }
}
/**
 * @brief: Function to initialize interface with UV and Visible Lamp Power Supplies
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                    Interface Initialized
 * @retval E_NOT_OK:                                Interface not initialized 
 */
Std_ReturnType HPWRSupply_InitSupplies              (void)
{
    MRCC_EnablePeripheralClock(MRCC_APB1, MRCC_APB1_TIM4_EN);
    MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_ADC1_EN);
    uint8 Loc_uint8Index = 0;

    /************************Initialize Pins Used in PWRSupply Interface************************/
    for(Loc_uint8Index = 0; Loc_uint8Index < HPWRSUPPLY_NO_OF_SENSE_CHANNELS; Loc_uint8Index++)
    {
        MGPIO_SetPinMode(glbl_uint8PWRSupplySensePortIDs[Loc_uint8Index],\
                            glbl_uint8PWRSupplySensePinIDs[Loc_uint8Index], MGPIO_INPUT_ANALOG_MODE);
    }

    for(Loc_uint8Index = 0; Loc_uint8Index < HPWRSUPPLY_NO_OF_CONTROL_PINS; Loc_uint8Index++)
    {
        MGPIO_SetPinMode(glbl_uint8PWRSupplyControlPortIDs[Loc_uint8Index],\
                            glbl_uint8PWRSupplyControlPinIDs[Loc_uint8Index], MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    }


    MNVIC_EnableInterrupt(MNVIC_TIM4);

    //MADC_Init(MADC1);
    
    MGPTMR_SetTimerPeriod(MGPTMR4, 2000);

    MGPTMR_SetTimerUpdateCallbackFunc(MGPTMR4, HPWRSupply_GetSenseValue);
    MGPTMR_Init(MGPTMR4);
    MGPTMR_StartTimer(MGPTMR4);
}
/**
 * @brief: Function to set mode of power supply (On/Off)
 * 
 * @param Copy_uint32SupplyChoice:                  The power supply whose mode to be set
 * @param Copy_uint32SupplyMode:                    Power Supply on or off
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                    Supply's mode set successfully
 * @retval E_NOT_OK:                                Supply's mode not set  
 */
Std_ReturnType HPWRSupply_SetSupplyMode             (HPWRSupply_Choice_t Copy_uint32SupplyChoice, HPWRSupply_Mode_t Copy_uint32SupplyMode)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    switch(Copy_uint32SupplyChoice)
    {
        case HPWRSUPPLY_VIS_SUPPLY:
        {
            if(Copy_uint32SupplyMode == HPWRSUPPLY_ON)
            {
                MGPIO_SetPinValue(glbl_uint8PWRSupplyControlPortIDs[0], glbl_uint8PWRSupplyControlPinIDs[0], MGPIO_HIGH);
                glbl_uint8SupplyFlags[0] = HPWRSUPPLY_ON;
                MSTK_uint8Delay(4000);
                HPWRSupply_Status_t Loc_uint32SupplyStatus = HPWRSUPPLY_STATUS_OFF;
                HPWRSupply_CheckSupplyStatus(HPWRSUPPLY_VIS_SUPPLY, &Loc_uint32SupplyStatus);
                if(Loc_uint32SupplyStatus == HPWRSUPPLY_STATUS_OK)
                {
                    Loc_uint8FuncStatus = E_OK;
                }
                else
                {
                    Loc_uint8FuncStatus = E_NOT_OK;
                }
            }
            else if(Copy_uint32SupplyMode == HPWRSUPPLY_OFF)
            {
                MGPIO_SetPinValue(glbl_uint8PWRSupplyControlPortIDs[0], glbl_uint8PWRSupplyControlPinIDs[0], MGPIO_LOW);
                MSTK_uint8Delay(4000);
                HPWRSupply_Status_t Loc_uint32SupplyStatus = HPWRSUPPLY_STATUS_OK;
                HPWRSupply_CheckSupplyStatus(HPWRSUPPLY_VIS_SUPPLY, &Loc_uint32SupplyStatus);
								glbl_uint8SupplyFlags[0] = HPWRSUPPLY_OFF;
                if(Loc_uint32SupplyStatus == HPWRSUPPLY_STATUS_OFF)
                {
                    Loc_uint8FuncStatus = E_OK;
                }
                else
                {
                    Loc_uint8FuncStatus = E_NOT_OK;
                }
            }
            else
            {
                Loc_uint8FuncStatus = E_NOT_OK;
            }
            break;
        }
        case HPWRSUPPLY_UV_SUPPLY:
        {
            if(Copy_uint32SupplyMode == HPWRSUPPLY_ON)
            {
                MGPIO_SetPinValue(glbl_uint8PWRSupplyControlPortIDs[1], glbl_uint8PWRSupplyControlPinIDs[1], MGPIO_LOW);
                glbl_uint8SupplyFlags[1] = HPWRSUPPLY_ON;
								MSTK_uint8Delay(11000);
                Loc_uint8FuncStatus = E_OK;
            }
            else if(Copy_uint32SupplyMode == HPWRSUPPLY_OFF)
            {
                MGPIO_SetPinValue(glbl_uint8PWRSupplyControlPortIDs[1], glbl_uint8PWRSupplyControlPinIDs[1], MGPIO_HIGH);
                glbl_uint8SupplyFlags[0] = HPWRSUPPLY_OFF;
                Loc_uint8FuncStatus = E_OK;
            }
            else
            {
                Loc_uint8FuncStatus = E_NOT_OK;
            }
            break;
        }
        default:
        {
            Loc_uint8FuncStatus = E_NOT_OK;
            break;
        }
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to check if supply's performance is as expected or not
 * 
 * @param Copy_uint32SupplyChoice:                  The power supply whose status is to be checked 
 * @param P_uint32SupplyStatus:                     Power Supply Status (Ok or not Ok or Off)
 * @return Std_ReturnType 
 */
Std_ReturnType HPWRSupply_CheckSupplyStatus         (HPWRSupply_Choice_t Copy_uint32SupplyChoice, HPWRSupply_Status_t* P_uint32SupplyStatus)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_uint32SupplyStatus != NULL_PTR)
    {
        switch(Copy_uint32SupplyChoice)
        {
            case HPWRSUPPLY_VIS_SUPPLY:
            {
                float32 Loc_float32VisSupplySenseVoltage = ((float32)glbl_uint16SenseValue[0] / 4096) * 3.3f;
                /*Check if Loc_float32VisSupplySenseVoltage is equal to a certain value*/
                /*if it is equal, supply is working well*/
                if((Loc_float32VisSupplySenseVoltage > 0.124f) && (Loc_float32VisSupplySenseVoltage < 0.2f))
                {
                    *P_uint32SupplyStatus = HPWRSUPPLY_STATUS_OK;
                    Loc_uint8FuncStatus = E_OK;
                }
                else if(Loc_float32VisSupplySenseVoltage < 0.05f)
                {
                    *P_uint32SupplyStatus = HPWRSUPPLY_STATUS_OFF;
                }
                else
                {
                    *P_uint32SupplyStatus = HPWRSUPPLY_STATUS_NOT_OK;
                }
                break;
            }
            case HPWRSUPPLY_UV_SUPPLY:
            {
                float32 Loc_float32UVSupplySenseVoltage = ((float32)glbl_uint16SenseValue[2] / 4096) * 3.3f;
                /*Check if Loc_float32UVSupplySenseVoltage is equal to a certain value*/
                *P_uint32SupplyStatus = HPWRSUPPLY_STATUS_OK;
                /*if it is equal, supply is working well*/
                break;
            }
            default:
            {
                Loc_uint8FuncStatus = E_NOT_OK;
                break;
            }
        }
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
