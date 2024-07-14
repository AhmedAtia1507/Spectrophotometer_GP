/**
 * @file HPWRSupply_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2024-03-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _HPWRSUPPLY_PRIVATE_H_
#define _HPWRSUPPLY_PRIVATE_H_

#define HPWRSUPPLY_NO_OF_SENSE_CHANNELS                         3
#define HPWRSUPPLY_NO_OF_CONTROL_PINS                           2

static volatile uint8 glbl_uint8PWRSupplySenseChannelIDs[HPWRSUPPLY_NO_OF_SENSE_CHANNELS] = \  
                                                                {
                                                                    HPWRSUPPLY_VIS_POWER_SENSE_1_CHANNEL_ID,
                                                                    HPWRSUPPLY_VIS_POWER_SENSE_2_CHANNEL_ID,
                                                                    HPWRSUPPLY_UV_POWER_SENSE_CHANNEL_ID
                                                                };

static volatile uint8 glbl_uint8PWRSupplySensePortIDs[HPWRSUPPLY_NO_OF_SENSE_CHANNELS] = \   
                                                                {
                                                                    HPWRSUPPLY_VIS_POWER_SENSE_1_PORT_ID,
                                                                    HPWRSUPPLY_VIS_POWER_SENSE_2_PORT_ID,
                                                                    HPWRSUPPLY_UV_POWER_SENSE_PORT_ID
                                                                };

static volatile uint8 glbl_uint8PWRSupplySensePinIDs[HPWRSUPPLY_NO_OF_SENSE_CHANNELS] = \   
                                                                {
                                                                    HPWRSUPPLY_VIS_POWER_SENSE_1_PIN_ID,
                                                                    HPWRSUPPLY_VIS_POWER_SENSE_2_PIN_ID,
                                                                    HPWRSUPPLY_UV_POWER_SENSE_PIN_ID
                                                                };

static volatile uint8 glbl_uint8PWRSupplyControlPortIDs[HPWRSUPPLY_NO_OF_CONTROL_PINS] = \   
                                                                {
                                                                    HPWRSUPPLY_VIS_POWER_CONTROL_PORT_ID,
                                                                    HPWRSUPPLY_UV_POWER_CONTROL_PORT_ID
                                                                };

static volatile uint8 glbl_uint8PWRSupplyControlPinIDs[HPWRSUPPLY_NO_OF_CONTROL_PINS] = \    
                                                                {
                                                                    HPWRSUPPLY_VIS_POWER_CONTROL_PIN_ID,
                                                                    HPWRSUPPLY_UV_POWER_CONTROL_PIN_ID
                                                                };
#endif /*_HPWRSUPPLY_PRIVATE_H_*/