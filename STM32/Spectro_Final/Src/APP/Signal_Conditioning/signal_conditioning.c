/*
 * signal_conditioning.c
 *
 *  Created on: Apr 23, 2024
 *      Author: Mohanad
 */

#include "signal_conditioning.h"
#include "../../HAL/MCP4151/MCP4151.h"
#include "../../HAL/ADS1115/ADC.h"

typedef enum
{
	NO_GAIN,
	GAIN_50,
	GAIN_30,
	GAIN_15
}ADC_gain_t;

void read_reference_voltage(float32 *ref, float32 *gain)
{
	float32 reading;
	ADC_config config;
	config.OS = OS_BEGIN_SINGLE_CONVERSION;
	config.MUX = MUX_AIN0_GND;
	config.PGA = PGA_4_096;
	config.MODE = MODE_SINGLE_SHOT;
	config.DR = DR_860SPS;
	config.COMP_MODE = COMP_MODE_DEFAULT;
	config.COMP_POL = COMP_POL_DEFAULT;
	config.COMP_LAT = COMP_LAT_DEFAULT;
	config.COMP_QUE = COMP_QUE_DEFAULT;
	*gain = 1.0f;

	static ADC_gain_t ref_gain_t = NO_GAIN;
	ref_sample x;
	x = REFERENCE;
	reading = adc_read_mv(config);
	if(reading < 50.0)
	{
		if(ref_gain_t != GAIN_50)
		{
			Set_Reference_Gain(50.0);
			ref_gain_t = GAIN_50;
		}
		config.MUX = MUX_AIN1_GND;
		reading = adc_read_mv(config);
		reading /= get_reference_gain(50.0);
		*gain = get_reference_gain(50.0);
	}
	else if(reading < 100.0)
	{
		if(ref_gain_t != GAIN_30)
		{
			Set_Reference_Gain(30.0);
			ref_gain_t = GAIN_30;
		}
		config.MUX = MUX_AIN1_GND;
		reading = adc_read_mv(config);
		reading /= get_reference_gain(30.0);
		*gain = get_reference_gain(30.0);
	}
	else if(reading < 200.0)
	{
		if(ref_gain_t != GAIN_15)
		{
			Set_Reference_Gain(15.0);
			ref_gain_t = GAIN_15;
		}
		config.MUX = MUX_AIN1_GND;
		reading = adc_read_mv(config);
		reading /= get_reference_gain(15.0);
		*gain = get_reference_gain(15.0);
	}
	else
	{
		ref_gain_t = NO_GAIN;
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
	reading *= (11.0 + 29.4)/11.0;
	*ref = reading;
}

void read_sample_voltage(float32 *sample, float32 *gain)
{
	float32 reading;
	ADC_config config;
	config.OS = OS_BEGIN_SINGLE_CONVERSION;
	config.MUX = MUX_AIN2_GND;
	config.PGA = PGA_4_096;
	config.MODE = MODE_SINGLE_SHOT;
	config.DR = DR_860SPS;
	config.COMP_MODE = COMP_MODE_DEFAULT;
	config.COMP_POL = COMP_POL_DEFAULT;
	config.COMP_LAT = COMP_LAT_DEFAULT;
	config.COMP_QUE = COMP_QUE_DEFAULT;
	*gain = 1.0f;

	static ADC_gain_t sample_gain_t = NO_GAIN;
	ref_sample x;
	x = SAMPLE;
	reading = adc_read_mv(config);
	if(reading < 50.0)
	{
		if(sample_gain_t != GAIN_50)
		{
			Set_Sample_Gain(50.0);
			sample_gain_t = GAIN_50;
		}
		config.MUX = MUX_AIN3_GND;
		reading = adc_read_mv(config);
		reading /= get_sample_gain(50.0);
		*gain = get_sample_gain(50.0);
	}
	else if(reading < 100.0)
	{
		if(sample_gain_t != GAIN_30)
		{
			Set_Sample_Gain(30.0);
			sample_gain_t = GAIN_30;
		}
		config.MUX = MUX_AIN3_GND;
		reading = adc_read_mv(config);
		reading /= get_sample_gain(30.0);
		*gain = get_sample_gain(30.0);
	}
	else if(reading < 200.0)
	{
		if(sample_gain_t != GAIN_15)
		{
			Set_Sample_Gain(15.0);
			sample_gain_t = GAIN_15;
		}
		config.MUX = MUX_AIN3_GND;
		reading = adc_read_mv(config);
		reading /= get_sample_gain(15.0);
		*gain = get_sample_gain(15.0);
	}
	else
	{
		sample_gain_t = NO_GAIN;
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

	reading *= (11.0 + 29.4)/11.0;
	*sample = reading;
}
