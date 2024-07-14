/**
 * @file SPWRVolt_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/Std_Types.h"

#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/GPTMR/GPTMR_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"
#include "../../MCAL/RCC/RCC_Interface.h"
#include "../../MCAL/NVIC/NVIC_Interface.h"

#include "SPWRVolt_Interface.h"
#include "SPWRVolt_Config.h"

/**
 * @brief: Array to store the converted data from ADC for each voltage channel
 * 
 */
static volatile uint16 glbl_uint16VoltageValues[SPWRVOLT_NO_OF_VOLTAGE_SOURCES] = {0};
static volatile uint8 glbl_uint8VoltageIndex = 0;


void SPWRVolt_GetConversionValue    (void)
{
    uint16 Loc_uint16VoltageValue = 0;
    /*
        Every one second, The ADC converts the value of one of the voltage channels in order
    */
    MADC_Conversion(MADC1, SPWRVolt_VoltageChannels[glbl_uint8VoltageIndex], &Loc_uint16VoltageValue);
    glbl_uint16VoltageValues[glbl_uint8VoltageIndex] = Loc_uint16VoltageValue;

    glbl_uint8VoltageIndex++;
    if(glbl_uint8VoltageIndex == SPWRVOLT_NO_OF_VOLTAGE_SOURCES)
    {
        glbl_uint8VoltageIndex = 0;
    }
}

/**
 * @brief: Function to initialize interface with various power supplies
 * 
 * @return Std_ReturnType
 * @retval E_OK:            Interface Successfully Initialized
 * @retval E_NOT_OK:        Interface not initialized 
 */
Std_ReturnType SPWRVolt_Init        (void)
{
    /*
        Enable Clocks for ADC1 and GPTMR3 Peripherals
    */
    MRCC_EnablePeripheralClock(MRCC_APB1, MRCC_APB1_TIM3_EN);
    MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_ADC1_EN);
    
	uint8 Loc_uint8Index = 0;
    /*
        Set Channels' pins to be input analog
    */
    for(Loc_uint8Index = 0; Loc_uint8Index < SPWRVOLT_NO_OF_VOLTAGE_SOURCES; Loc_uint8Index++)
    {
        MGPIO_SetPinMode(SPWRVolt_VoltagesPortIDs[Loc_uint8Index], SPWRVolt_VoltagesPinIDs[Loc_uint8Index], MGPIO_INPUT_ANALOG_MODE);
    }
	
    // Initialize ADC1 Peripheral
    MADC_Init(MADC1);

    // Set Timer Update Interrupt Function
    MGPTMR_SetTimerUpdateCallbackFunc(MGPTMR3, SPWRVolt_GetConversionValue);

    //Set timer period to be one second
    MGPTMR_SetTimerPeriod(MGPTMR3, 1000);
	
    // Enable Timer 3 Interrupt and initialize Timer 3 
	MNVIC_EnableInterrupt(MNVIC_TIM3);
    MGPTMR_Init(MGPTMR3);

    // Get the digital value for the first voltage channel
    SPWRVolt_GetConversionValue();

    //Start Timer 3
    MGPTMR_StartTimer(MGPTMR3);

    return E_OK;
}
/**
 * @brief: Function to read voltage from a certain power supply
 * 
 * @param Copy_uint32VoltageChoice: Choice for Power supply voltage to be read
 * @return Std_ReturnType
 * @retval E_OK:            Voltage Successfully Read
 * @retval E_NOT_OK:        Voltage not read 
 */
Std_ReturnType SPWRVolt_GetVoltage  (SPWRVolt_Choice_t Copy_uint32VoltageChoice, uint16* P_uint16VoltageValue)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_uint16VoltageValue != NULL_PTR)
    {
        *P_uint16VoltageValue = glbl_uint16VoltageValues[Copy_uint32VoltageChoice];
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
