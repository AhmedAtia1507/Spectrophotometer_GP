/*
 * signal_conditioning.c
 *
 *  Created on: Apr 23, 2024
 *      Author: Mohanad
 */

#include "signal_conditioning.h"
#include "../../HAL/MCP4151/MCP4151.h"
#include "../../HAL/ADS1115/ADC.h"

void read_reference_voltage(float32 *ref, float32 *gain)
{
	float32 reading;
	ADC_config config;
	config.OS = OS_NO_EFFECT;
	config.MUX = MUX_AIN0_GND;
	config.PGA = PGA_4_096;
	config.MODE = MODE_CONT_CONVERSION;
	config.DR = DR_128SPS;
	config.COMP_MODE = COMP_MODE_DEFAULT;
	config.COMP_POL = COMP_POL_DEFAULT;
	config.COMP_LAT = COMP_LAT_DEFAULT;
	config.COMP_QUE = COMP_QUE_DEFAULT;
	*gain = 1.0f;

	ref_sample x;
	x = REFERENCE;
	reading = adc_read_mv(config);
	if(reading < 50.0)
	{
		config.MUX = MUX_AIN1_GND;
		Set_Reference_Gain(50.0);
		reading = adc_read_mv(config);
		reading /= get_reference_gain(50.0);
		*gain = get_reference_gain(50.0);
	}
	else if(reading < 100.0)
	{
		config.MUX = MUX_AIN1_GND;
		Set_Reference_Gain(30.0);
		reading = adc_read_mv(config);
		reading /= get_reference_gain(30.0);
		*gain = get_reference_gain(30.0);
	}
	else if(reading < 200.0)
	{
		config.MUX = MUX_AIN1_GND;
		Set_Reference_Gain(15.0);
		reading = adc_read_mv(config);
		reading /= get_reference_gain(15.0);
		*gain = get_reference_gain(15.0);
	}
//	else if(reading < 500.0)
//	{
//		config.MUX = MUX_AIN1_GND;
//		Set_Reference_Gain(5.0);
//		reading = adc_read_mv(config);
//		reading /= get_reference_gain(5.0);
//		*gain = get_reference_gain(5.0);
//	}
//	else if(reading < 1000.0)
//	{
//		config.MUX = MUX_AIN1_GND;
//		Set_Reference_Gain(3.0);
//		reading = adc_read_mv(config);
//		reading /= get_reference_gain(3.0);
//		*gain = get_reference_gain(3.0);
//	};
	reading *= (11.0 + 29.0)/11.0;
	*ref = reading;
}

void read_sample_voltage(float32 *sample, float32 *gain)
{
	float32 reading;
	ADC_config config;
	config.OS = OS_NO_EFFECT;
	config.MUX = MUX_AIN2_GND;
	config.PGA = PGA_4_096;
	config.MODE = MODE_CONT_CONVERSION;
	config.DR = DR_128SPS;
	config.COMP_MODE = COMP_MODE_DEFAULT;
	config.COMP_POL = COMP_POL_DEFAULT;
	config.COMP_LAT = COMP_LAT_DEFAULT;
	config.COMP_QUE = COMP_QUE_DEFAULT;
	*gain = 1.0f;

	ref_sample x;
	x = SAMPLE;
	reading = adc_read_mv(config);
	if(reading < 50.0)
	{
		config.MUX = MUX_AIN3_GND;
		Set_Sample_Gain(50.0);
		reading = adc_read_mv(config);
		reading /= get_reference_gain(50.0);
		*gain = get_sample_gain(50.0);
	}
	else if(reading < 100.0)
	{
		config.MUX = MUX_AIN3_GND;
		Set_Sample_Gain(30.0);
		reading = adc_read_mv(config);
		reading /= get_sample_gain(30.0);
		*gain = get_sample_gain(30.0);
	}
	else if(reading < 200.0)
	{
		config.MUX = MUX_AIN3_GND;
		Set_Sample_Gain(15.0);
		reading = adc_read_mv(config);
		reading /= get_sample_gain(15.0);
		*gain = get_sample_gain(15.0);
	}
//	else if(reading < 500.0)
//	{
//		config.MUX = MUX_AIN3_GND;
//		Set_Sample_Gain(5.0);
//		reading = adc_read_mv(config);
//		reading /= get_sample_gain(5.0);
//		*gain = get_sample_gain(5.0);
//	}
//	else if(reading < 1000.0)
//	{
//		config.MUX = MUX_AIN3_GND;
//		Set_Sample_Gain(3.0);
//		reading = adc_read_mv(config);
//		reading /= get_sample_gain(3.0);
//		*gain = get_sample_gain(3.0);
//	};

	reading *= (11.0 + 29.0)/11.0;
	*sample = reading;
}
