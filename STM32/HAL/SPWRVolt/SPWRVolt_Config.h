/**
 * @file SPWRVolt_Config.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _SPWRVOLT_CONFIG_H_
#define _SPWRVOLT_CONFIG_H_

#define SPWRVOLT_NO_OF_VOLTAGE_SOURCES                      5

#define SPWRVOLT_SUPPLY_33_VOLT_CHANNEL_ID                  MADC_Channel_1
#define SPWRVOLT_DCDC_NEG_12_VOLT_CHANNEL_ID                MADC_Channel_3
#define SPWRVOLT_SUPPLY_12_VOLT_CHANNEL_ID                  MADC_Channel_4
#define SPWRVOLT_SUPPLY_5_VOLT_CHANNEL_ID                   MADC_Channel_5
#define SPWRVOLT_DCDC_POS_12_VOLT_CHANNEL_ID                MADC_Channel_6

static volatile uint8 SPWRVolt_VoltagesPortIDs[SPWRVOLT_NO_OF_VOLTAGE_SOURCES] = \
                                                        {
                                                            MADC_CHANNEL_1_PORT_ID,
                                                            MADC_CHANNEL_3_PORT_ID,
                                                            MADC_CHANNEL_4_PORT_ID,
                                                            MADC_CHANNEL_5_PORT_ID,
                                                            MADC_CHANNEL_6_PORT_ID
                                                        };
static volatile uint8 SPWRVolt_VoltagesPinIDs[SPWRVOLT_NO_OF_VOLTAGE_SOURCES] = \
                                                        {
                                                            MADC_CHANNEL_1_PIN_ID,
                                                            MADC_CHANNEL_3_PIN_ID,
                                                            MADC_CHANNEL_4_PIN_ID,
                                                            MADC_CHANNEL_5_PIN_ID,
                                                            MADC_CHANNEL_6_PIN_ID
                                                        };
static volatile uint8 SPWRVolt_VoltageChannels[SPWRVOLT_NO_OF_VOLTAGE_SOURCES] = \
                                                        {
                                                            SPWRVOLT_SUPPLY_33_VOLT_CHANNEL_ID,
                                                            SPWRVOLT_DCDC_NEG_12_VOLT_CHANNEL_ID,
                                                            SPWRVOLT_SUPPLY_12_VOLT_CHANNEL_ID,
                                                            SPWRVOLT_SUPPLY_5_VOLT_CHANNEL_ID,
                                                            SPWRVOLT_DCDC_POS_12_VOLT_CHANNEL_ID
                                                        };
#endif /*_SPWRVOLT_CONFIG_H_*/