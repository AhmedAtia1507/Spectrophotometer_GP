/**
 * @file MOTORS_Config.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2024-01-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _MOTORS_CONFIG_H_
#define _MOTORS_CONFIG_H_


#define HMOTOR_LAMP_SELECT_STEP_PORT_ID                         MGPIO_PORTB
#define HMOTOR_LAMP_SELECT_STEP_PIN_ID                          MGPIO_PIN8

#define HMOTOR_LAMP_SELECT_DIR_PORT_ID                          MGPIO_PORTB
#define HMOTOR_LAMP_SELECT_DIR_PIN_ID                           MGPIO_PIN5

#define HMOTOR_WL_SELECT_STEP_PORT_ID                           MGPIO_PORTB
#define HMOTOR_WL_SELECT_STEP_PIN_ID                            MGPIO_PIN4

#define HMOTOR_WL_SELECT_DIR_PORT_ID                            MGPIO_PORTB
#define HMOTOR_WL_SELECT_DIR_PIN_ID                             MGPIO_PIN3

#define HMOTOR_FILTER_SELECT_STEP_PORT_ID                       MGPIO_PORTA
#define HMOTOR_FILTER_SELECT_STEP_PIN_ID                        MGPIO_PIN15

#define HMOTOR_FILTER_SELECT_DIR_PORT_ID                        MGPIO_PORTA
#define HMOTOR_FILTER_SELECT_DIR_PIN_ID                         MGPIO_PIN12

#define HMOTOR4_STEP_PORT_ID                                    MGPIO_PORTA
#define HMOTOR4_STEP_PIN_ID                                     MGPIO_PIN11

#define HMOTOR4_DIR_PORT_ID                                     MGPIO_PORTA
#define HMOTOR4_DIR_PIN_ID                                      MGPIO_PIN10

#define HMOTOR_FILTER_SELECT_HOMING_PORT_ID                     MGPIO_PORTC
#define HMOTOR_FILTER_SELECT_HOMING_PIN_ID                      MGPIO_PIN13

#define HMOTOR_WL_SELECT_HOMING_PORT_ID                         MGPIO_PORTA
#define HMOTOR_WL_SELECT_HOMING_PIN_ID                          MGPIO_PIN0

#define HMOTOR4_HOMING_PORT_ID                                  MGPIO_PORTC
#define HMOTOR4_HOMING_PIN_ID                                   MGPIO_PIN15

#endif /*_MOTORS_CONFIG_H_*/