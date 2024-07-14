/**
 * @file HPWRSupply_Config.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2024-03-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _HPWRSUPPLY_CONFIG_H_
#define _HPWRSUPPLY_CONFIG_H_

#define HPWRSUPPLY_UV_POWER_CONTROL_PORT_ID                         MGPIO_PORTA
#define HPWRSUPPLY_UV_POWER_CONTROL_PIN_ID                          MGPIO_PIN9

#define HPWRSUPPLY_VIS_POWER_CONTROL_PORT_ID                        MGPIO_PORTB
#define HPWRSUPPLY_VIS_POWER_CONTROL_PIN_ID                         MGPIO_PIN14

#define HPWRSUPPLY_VIS_POWER_SENSE_1_CHANNEL_ID                     MADC_Channel_8
#define HPWRSUPPLY_VIS_POWER_SENSE_2_CHANNEL_ID                     MADC_Channel_9

#define HPWRSUPPLY_VIS_POWER_SENSE_1_PORT_ID                        MGPIO_PORTB
#define HPWRSUPPLY_VIS_POWER_SENSE_1_PIN_ID                         MGPIO_PIN0

#define HPWRSUPPLY_VIS_POWER_SENSE_2_PORT_ID                        MGPIO_PORTB
#define HPWRSUPPLY_VIS_POWER_SENSE_2_PIN_ID                         MGPIO_PIN1

#define HPWRSUPPLY_UV_POWER_SENSE_CHANNEL_ID                        MADC_Channel_7

#define HPWRSUPPLY_UV_POWER_SENSE_PORT_ID                           MGPIO_PORTA
#define HPWRSUPPLY_UV_POWER_SENSE_PIN_ID                            MGPIO_PIN7


#endif /*_HPWRSUPPLY_CONFIG_H_*/