/**
 * @file MOTORS_Private.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 *  
 * @version 1.0
 * @date 2024-01-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _MOTORS_PRIVATE_H_
#define _MOTORS_PRIVATE_H_

#define HMOTORS_NUM_MOTORS                                                  3

#define HMOTORS_MOTOR_AT_HOME												1
#define HMOTORS_MOTOR_NOT_AT_HOME											0

static volatile uint8 glbl_uint8MotorsStepPortIDs[HMOTORS_NUM_MOTORS] = 	{
																				HMOTOR_LAMP_SELECT_STEP_PORT_ID,
																				HMOTOR_FILTER_SELECT_STEP_PORT_ID,
																				HMOTOR_WL_SELECT_STEP_PORT_ID
																			};
static volatile uint8 glbl_uint8MotorsStepPinIDs[HMOTORS_NUM_MOTORS] = 		{	
																				HMOTOR_LAMP_SELECT_STEP_PIN_ID,
																				HMOTOR_FILTER_SELECT_STEP_PIN_ID,
																				HMOTOR_WL_SELECT_STEP_PIN_ID
																			};
static volatile uint8 glbl_uint8MotorsDirPortIDs[HMOTORS_NUM_MOTORS] = 		{
																				HMOTOR_LAMP_SELECT_DIR_PORT_ID,
																				HMOTOR_FILTER_SELECT_DIR_PORT_ID,
																				HMOTOR_WL_SELECT_DIR_PORT_ID
																			};
static volatile uint8 glbl_uint8MotorsDirPinIDs[HMOTORS_NUM_MOTORS] = 		{
																				HMOTOR_LAMP_SELECT_DIR_PIN_ID,
																				HMOTOR_FILTER_SELECT_DIR_PIN_ID,
																				HMOTOR_WL_SELECT_DIR_PIN_ID
																			};

static volatile uint8 glbl_uint8MotorHomingPortIDs[HMOTORS_NUM_MOTORS - 1]= {
																				HMOTOR_FILTER_SELECT_HOMING_PORT_ID,
																				HMOTOR_WL_SELECT_HOMING_PORT_ID
																			};

static volatile uint8 glbl_uint8MotorHomingPinIDs[HMOTORS_NUM_MOTORS - 1]= {
																				HMOTOR_FILTER_SELECT_HOMING_PIN_ID,
																				HMOTOR_WL_SELECT_HOMING_PIN_ID
																			};

void HMOTOR4_HomeIndicator(void);
void HMOTOR_WLHomeIndicator(void);
void HMOTOR_FilterHomeIndicator(void);
#endif /*_MOTORS_PRIVATE_H_*/