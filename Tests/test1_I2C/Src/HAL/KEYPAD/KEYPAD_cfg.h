/*
 * KEYPAD_cfg.h
 *
 *  Created on: Sep 7, 2023
 *      Author: Mohanad
 */

#ifndef HAL_KEYPAD_KEYPAD_CFG_H_
#define HAL_KEYPAD_KEYPAD_CFG_H_

#include "../../MCAL/GPIO/GPIO_Interface.h"

#define NUM_OF_ROWS			4
#define NUM_OF_COLUMNS		4
#define KEYPAD_PORT			GPIO_PORTB

u8 KeypadRowPins[NUM_OF_ROWS] = {GPIO_PIN4, GPIO_PIN5, GPIO_PIN6, GPIO_PIN7};
u8 KeypadColPins[NUM_OF_COLUMNS] = {GPIO_PIN8, GPIO_PIN9, GPIO_PIN10, GPIO_PIN3};
u8 Keypad_u8Values[NUM_OF_ROWS][NUM_OF_COLUMNS] = {
		{
			'1','2','3','A'
		},
		{
			'4','5','6','B'
		},
		{
			'7','8','9','C'
		},
		{
			'*','0','#','D'
		}
};

#endif /* HAL_KEYPAD_KEYPAD_CFG_H_ */
