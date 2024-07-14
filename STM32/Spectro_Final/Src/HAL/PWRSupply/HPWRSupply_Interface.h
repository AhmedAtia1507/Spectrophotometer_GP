/**
 * @file HPWRSupply_interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2024-03-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _HPWRSUPPLY_INTERFACE_H_
#define _HPWRSUPPLY_INTERFACE_H_

typedef enum HPWRSupply_Choice
{
    HPWRSUPPLY_UV_SUPPLY,
    HPWRSUPPLY_VIS_SUPPLY
} HPWRSupply_Choice_t;

typedef enum HPWRSupply_Mode
{
    HPWRSUPPLY_OFF,
    HPWRSUPPLY_ON
}HPWRSupply_Mode_t;

typedef enum HPWRSupply_Status
{
    HPWRSUPPLY_STATUS_OK     = 2,
    HPWRSUPPLY_STATUS_NOT_OK    ,
    HPWRSUPPLY_STATUS_OFF
}HPWRSupply_Status_t;

/**
 * @brief: Function to initialize interface with UV and Visible Lamp Power Supplies
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                    Interface Initialized
 * @retval E_NOT_OK:                                Interface not initialized 
 */
Std_ReturnType HPWRSupply_InitSupplies              (void);
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
Std_ReturnType HPWRSupply_SetSupplyMode             (HPWRSupply_Choice_t Copy_uint32SupplyChoice, HPWRSupply_Mode_t Copy_uint32SupplyMode);
/**
 * @brief: Function to check if supply's performance is as expected or not
 * 
 * @param Copy_uint32SupplyChoice:                  The power supply whose status is to be checked 
 * @param P_uint32SupplyStatus:                     Power Supply Status (Ok or not Ok or Off)
 * @return Std_ReturnType 
 */
Std_ReturnType HPWRSupply_CheckSupplyStatus         (HPWRSupply_Choice_t Copy_uint32SupplyChoice, HPWRSupply_Status_t* P_uint32SupplyStatus);
#endif /*_HPWRSUPPLY_INTERFACE_H_*/