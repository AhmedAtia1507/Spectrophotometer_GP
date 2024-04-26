/*
 * LCD_cfg.h
 *
 *  Created on: Sep 7, 2023
 *      Author: Mohanad
 */

#ifndef HAL_LCD_LCD_CFG_H_
#define HAL_LCD_LCD_CFG_H_

#include "../../MCAL/GPIO/GPIO_Interface.h"

#define LCD_PORT	GPIO_PORTA
#define RS_PIN		GPIO_PIN8
#define RW_PIN		GPIO_PIN9
#define E_PIN		GPIO_PIN10
#define D0_PIN		GPIO_PIN0
#define D1_PIN		GPIO_PIN1
#define D2_PIN		GPIO_PIN2
#define D3_PIN		GPIO_PIN3
#define D4_PIN		GPIO_PIN4
#define D5_PIN		GPIO_PIN5
#define D6_PIN		GPIO_PIN6
#define D7_PIN		GPIO_PIN7

#define LCD_TICKS	200000			// Set it to be 2ms

#endif /* HAL_LCD_LCD_CFG_H_ */
