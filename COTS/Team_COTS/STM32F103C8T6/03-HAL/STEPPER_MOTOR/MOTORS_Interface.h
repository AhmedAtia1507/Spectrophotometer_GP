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

#define HMOTORS_CLKWISE_DIRECTION		    	        1
#define HMOTORS_CCLKWISE_DIRECTION		                2

#define HMOTORS_FULL_CYCLE                              24

void HMOTORS_Init(void);
void HMOTOR_Step(uint32 Copy_uint8NoOfSetps, uint8 Copy_uint8Direction);

#endif /*_MOTORS_INTERFACE_H_*/