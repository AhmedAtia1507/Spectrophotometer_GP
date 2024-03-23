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
    HMOTOR_WL_SELECT,
    HMOTOR4
}HMOTORS_Select_t;

#define HMOTORS_CLKWISE_DIRECTION		    	        1
#define HMOTORS_CCLKWISE_DIRECTION		                2

#define HMOTORS_FULL_CYCLE                              24

void HMOTORS_Init   (void);
void HMOTOR_Step    (HMOTORS_Select_t Copy_uint32MotorSelect, uint8 Copy_uint8NoOfSetps, uint8 Copy_uint8Direction);
void HMOTOR_GoHome  (HMOTORS_Select_t Copy_uint32MotorSelect);

#endif /*_MOTORS_INTERFACE_H_*/