/**
 * @file MOTORS_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * 
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

/**
 * @brief: Function to initialize interface with stepper motors
 * 
 * @return Std_ReturnType
 * @retval E_OK:										Interface Successfully Initialized
 * @retval E_NOT_OK:									Interface not initialized 
 */
Std_ReturnType HMOTORS_Init                             (void);
/**
 * @brief: Function to move specified motor number of steps with a specified speed at a specified direction
 * 
 * @param Copy_uint32MotorSelect:						Motor to be moved
 * @param Copy_uint32NoOfSetps:							Number of steps the motor should move
 * @param Copy_uint8Direction:							Direction of motor rotation (clockwise or counter-clockwise) 
 * @param Copy_uint8MotorSpeed:							Speed of the motor (delay between steps)
 * 
 * @return Std_ReturnType
 * @retval E_OK:										Motor Successfully moved
 * @retval E_NOT_OK:									Motor not moved 
 */
Std_ReturnType HMOTOR_Step                              (HMOTORS_Select_t Copy_uint32MotorSelect, uint32 Copy_uint32NoOfSetps, uint8 Copy_uint8Direction, uint8 Copy_uint8MotorSpeed);
/**
 * @brief: Function to move the specified motor to its homing position
 * 
 * @param Copy_uint32MotorSelect:						Motor to be moved to the homing position
 *  
 * @return Std_ReturnType
 * @retval E_OK:										Motor successfully at homing position
 * @retval E_NOT_OK:									Motor not at home 
 */
Std_ReturnType HMOTOR_GoHome                            (HMOTORS_Select_t Copy_uint32MotorSelect);
/**
 * @brief: Function to retrieve the specified motor's current position 
 * 
 * @param Copy_uint32MotorSelect:						Motor whose steps is to be retrieved 
 * @param P_sint32MotorSteps:							Pointer to save the number of steps in
 *  
 * @return Std_ReturnType
 * @retval E_OK:										Motor's steps successfully retrieved
 * @retval E_NOT_OK:									Motor's steps not retrieved 
 */
Std_ReturnType HMOTOR_GetCurrentMotorSteps              (HMOTORS_Select_t Copy_uint32MotorSelect, sint32* P_sint32MotorSteps);
/**
 * @brief: Function to retrieve the current wavelength based on the motor steps.
 * 
 * @param P_float32CurrentWL: 							Pointer where the current wavelength will be stored.
 * 
 * @return Std_ReturnType
 * @retval E_OK:										Wavelength successfully retrieved
 * @retval E_NOT_OK:									Wavelength not retrieved 
 */
Std_ReturnType HMOTOR_GetCurrentWL                      (float32* P_float32CurrentWL);
/**
 * @brief: Function to move lamp motor to select one of the lamps (UV or Visible)
 * 
 * @param Copy_uint32LampSelect:					    Lamp to be selected
 * 
 * @return Std_ReturnType
 * @retval E_OK:									    Lamp motor successfully moved
 * @retval E_NOT_OK:								    Lamp motor not moved 
 */
Std_ReturnType HMOTOR_MoveLampMotor                     (HMOTOR_Lamp_Select_t Copy_uint32LampSelect);
/**
 * @brief: Function to move the filter wheel motor to the specified filter
 * 
 * @param Copy_uint32FilterSelect:						The selected filter to move the motor to
 *  
 * @return Std_ReturnType
 * @retval E_OK:										Motor Successfully moved
 * @retval E_NOT_OK:									Motor not moved 
 */
Std_ReturnType HMOTOR_MoveFilterMotor                   (HMOTOR_Filter_Select_t Copy_uint32FilterSelect);
/**
 * @brief: Function to move the wavelength select motor to position that represents the specified wavelength
 * 
 * @param Copy_float32NextWL:							Wavelength to move motor to
 * 
 * @return Std_ReturnType
 * @retval E_OK:										Motor Successfully moved
 * @retval E_NOT_OK:									Motor not moved 
 */
Std_ReturnType HMOTOR_MoveWLSelectMotor                 (float32 Copy_float32NextWL);
/**
 * @brief: Function to update the values of zero wavelength steps and steps/nm after calibration
 * 
 * @param Copy_uint32ZeroWLSteps:						the number of steps from home position to position of zero wavelength				
 * @param Copy_sint32StepsPerNm:						number of steps to be taken to move one wavelength 
 * @return Std_ReturnType 
 */
Std_ReturnType HMOTOR_GetWLSelectCalibration            (sint32 Copy_sint32ZeroWLSteps, float32 Copy_uint32StepsPerNm);
/**
 * @brief: Function to move specified motor one step without delay after pulse creation
 * 
 * @param Copy_uint32MotorSelect:						Motor to be moved
 * @param Copy_uint8Direction:							Direction of motor rotation (clockwise or counter-clockwise) 
 * 
 * @return Std_ReturnType
 * @retval E_OK:										Motor Successfully moved
 * @retval E_NOT_OK:									Motor not moved 
 */
Std_ReturnType HMOTOR_StepNoDelay                       (HMOTORS_Select_t Copy_uint32MotorSelect, uint8 Copy_uint8Direction);
/**
 * @brief: Function to retrieve the number of steps per 1nm in order to be used in other drivers
 * 
 * @param P_float32StepsPerNm: 							Pointer to save number of steps to be taken to move one wavelength
 * 	
 * @return Std_ReturnType
 * @retval E_OK:										Value Successfully retrieved
 * @retval E_NOT_OK:									Value not retrieved 
 */
Std_ReturnType HMOTOR_GetStepsPerNm						(float32* P_float32StepsPerNm);
#endif /*_MOTORS_INTERFACE_H_*/
