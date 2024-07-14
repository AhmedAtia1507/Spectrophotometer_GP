/*
 * ADC.h
 *
 *  Created on: Feb 12, 2024
 *      Author: Mohanad
 */

#ifndef HAL_ADC_H_
#define HAL_ADC_H_

typedef struct
{
	unsigned short COMP_QUE:2;
	unsigned short COMP_LAT:1;
	unsigned short COMP_POL:1;
	unsigned short COMP_MODE:1;
	unsigned short DR:3;
	unsigned short MODE:1;
	unsigned short PGA:3;
	unsigned short MUX:3;
	unsigned short OS:1;
}ADC_config;

typedef enum
{
	OS_NO_EFFECT = 0,
	OS_BEGIN_SINGLE_CONVERSION = 1,
	MUX_AIN0_AIN1 = 0b000,
	MUX_AIN0_AIN3 = 0b001,
	MUX_AIN1_AIN3 = 0b010,
	MUX_AIN2_AIN3 = 0b011,
	MUX_AIN0_GND = 0b100,
	MUX_AIN1_GND = 0b101,
	MUX_AIN2_GND = 0b110,
	MUX_AIN3_GND = 0b111,
	PGA_6_144 = 0b000,
	PGA_4_096 = 0b001,
	PGA_2_048 = 0b010,
	PGA_1_024 = 0b011,
	PGA_0_512 = 0b100,
	PGA_0_256 = 0b101,
	MODE_CONT_CONVERSION = 0,
	MODE_SINGLE_SHOT = 1,
	DR_8SPS = 0b000,
	DR_16SPS = 0b001,
	DR_32SPS = 0b010,
	DR_64SPS = 0b011,
	DR_128SPS = 0b100,
	DR_250SPS = 0b101,
	DR_475SPS = 0b110,
	DR_860SPS = 0b111,
	COMP_MODE_DEFAULT = 0,
	COMP_POL_DEFAULT = 0,
	COMP_LAT_DEFAULT = 0,
	COMP_QUE_DEFAULT = 11

}ADC_Config_t;

void adc_init(void);
float32 adc_read_mv(ADC_config a);

#endif /* HAL_ADC_H_ */
