/**
 * @file MOTORS_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2024-01-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _MOTORS_INTERFACE_H_
#define _MOTORS_INTERFACE_H_

typedef enum Motor_Select
{
    HMOTOR_LAMP_SELECT,
    HMOTOR_FILTER_SELECT,
    HMOTOR_WL_SELECT
}HMOTORS_Select_t;

typedef enum Lamp_Motor_Select
{
    HMOTOR_LAMP_UV,
    HMOTOR_LAMP_VIS
}HMOTOR_Lamp_Select_t;

typedef enum Filter_Motor_Select
{
    HMOTOR_FILTER_AIR,
    HMOTOR_FILTER_1,
    HMOTOR_FILTER_2,
    HMOTOR_FILTER_3,
    HMOTOR_FILTER_4,
    HMOTOR_FILTER_5,
    HMOTOR_FILTER_6,
    HMOTOR_FILTER_7,
}HMOTOR_Filter_Select_t;

#define HMOTORS_CLKWISE_DIRECTION		    	        1
#define HMOTORS_CCLKWISE_DIRECTION		                2

#define HMOTORS_FULL_CYCLE                              24
#define HMOTORS_WL_SELECT_FULL_CYCLE					48

Std_ReturnType HMOTORS_Init                             (void);
Std_ReturnType HMOTOR_Step                              (HMOTORS_Select_t Copy_uint32MotorSelect, uint32 Copy_uint32NoOfSetps, uint8 Copy_uint8Direction, uint8 Copy_uint8MotorSpeed);
Std_ReturnType HMOTOR_GoHome                            (HMOTORS_Select_t Copy_uint32MotorSelect);
Std_ReturnType HMOTOR_GetCurrentMotorSteps              (HMOTORS_Select_t Copy_uint32MotorSelect, uint32* P_uint32MotorSteps);
Std_ReturnType HMOTOR_GetCurrentWL                      (uint32* P_uint32CurrentWL);
Std_ReturnType HMOTOR_MoveLampMotor                     (HMOTOR_Lamp_Select_t Copy_uint32LampSelect);
Std_ReturnType HMOTOR_MoveFilterMotor                   (HMOTOR_Filter_Select_t Copy_uint32FilterSelect);
Std_ReturnType HMOTOR_MoveWLSelectMotor                 (float32 Copy_float32NextWL);
Std_ReturnType HMOTOR_GetWLSelectCalibration            (uint32 Copy_uint32ZeroWLSteps, float32 Copy_uint32StepsPerNm);
#endif /*_MOTORS_INTERFACE_H_*/