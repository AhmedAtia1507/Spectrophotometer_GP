/*
 * S2P_cfg.c
 *
 *  Created on: Aug 22, 2023
 *      Author: admin
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/GPIO/GPIO_int.h"

	GPIO_cfg_t  S2P_ShiftPin ={
			.mode=GPIO_MODE_OUTPUT,
			.port=GPIO_PORTA,
			.pin= GPIO_PIN0,
			.out_type=GPIO_OUTPUTTYPE_PUSHPULL,
			.speed=GPIO_OUTSPEED_LOW
	};
	GPIO_cfg_t  S2P_LatchPin ={
			.mode=GPIO_MODE_OUTPUT,
			.port=GPIO_PORTA,
			.pin= GPIO_PIN1,
			.out_type=GPIO_OUTPUTTYPE_PUSHPULL,
			.speed=GPIO_OUTSPEED_LOW
	};
	GPIO_cfg_t  S2P_DataPin ={
			.mode=GPIO_MODE_OUTPUT,
			.port=GPIO_PORTA,
			.pin= GPIO_PIN2,
			.out_type=GPIO_OUTPUTTYPE_PUSHPULL,
			.speed=GPIO_OUTSPEED_LOW
	};
