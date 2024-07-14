/**
 * @file SPWRVolt_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _SPWRVOLT_INTERFACE_H_
#define _SPWRVOLT_INTERFACE_H_

typedef enum Power_Voltages
{
    SPWRVOLT_SUPPLY_33,
    SPWRVOLT_DCDC_NEG_12,
    SPWRVOLT_SUPPLY_12,
    SPWRVOLT_SUPPLY_5,
    SPWRVOLT_DCDC_POS_12
}SPWRVolt_Choice_t;

/**
 * @brief: Function to initialize interface with various power supplies
 * 
 * @return Std_ReturnType
 * @retval E_OK:                        Interface Successfully Initialized
 * @retval E_NOT_OK:                    Interface not initialized 
 */
Std_ReturnType SPWRVolt_Init            (void);
/**
 * @brief: Function to read voltage from a certain power supply
 * 
 * @param Copy_uint32VoltageChoice:     Choice for Power supply voltage to be read
 * @return Std_ReturnType
 * @retval E_OK:                        Voltage Successfully Read
 * @retval E_NOT_OK:                    Voltage not read 
 */
Std_ReturnType SPWRVolt_GetVoltage      (SPWRVolt_Choice_t Copy_uint32VoltageChoice, uint16* P_uint16VoltageValue);
#endif /*_SPWRVOLT_INTERFACE_H_*/