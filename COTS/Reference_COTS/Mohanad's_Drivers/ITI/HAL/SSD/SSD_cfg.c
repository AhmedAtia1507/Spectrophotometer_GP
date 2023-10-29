/*
 * SSD_cfg.c
 *
 *  Created on: Aug 22, 2023
 *      Author: Mohanad
 */
#include "../../MCAL/GPIO/GPIO_int.h"
#include "SSD_int.h"
#include "SSD_cfg.h"

SSD_cfg_t SSD_1[7] = {
		{.port = SSD1_PORTA, .pin = SSD1_PINA},
		{.port = SSD1_PORTB, .pin = SSD1_PINB},
		{.port = SSD1_PORTC, .pin = SSD1_PINC},
		{.port = SSD1_PORTD, .pin = SSD1_PIND},
		{.port = SSD1_PORTE, .pin = SSD1_PINE},
		{.port = SSD1_PORTF, .pin = SSD1_PINF},
		{.port = SSD1_PORTG, .pin = SSD1_PING},
};

SSD_cfg_t SSD_2[7] = {
		{.port = SSD2_PORTA, .pin = SSD2_PINA},
		{.port = SSD2_PORTB, .pin = SSD2_PINB},
		{.port = SSD2_PORTC, .pin = SSD2_PINC},
		{.port = SSD2_PORTD, .pin = SSD2_PIND},
		{.port = SSD2_PORTE, .pin = SSD2_PINE},
		{.port = SSD2_PORTF, .pin = SSD2_PINF},
		{.port = SSD2_PORTG, .pin = SSD2_PING},
};
