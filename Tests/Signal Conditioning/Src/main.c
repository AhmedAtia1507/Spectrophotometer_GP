#include "MCAL/I2C/I2C_Interface.h"
#include "MCAL/RCC/RCC_Interface.h"
#include "MCAL/I2C/I2C_private.h"
#include "MCAL/I2C/I2C_Config.h"
#include "HAL/ADC.h"
#include "MCP4151.h"
#include "Signal_Conditioning/signal_conditioning.h"
#include "HAL/I2C_Slave_EEPROM.h"

void delay_ms(uint32 milliseconds);
float32 ref;
float32 sample;
float32 gain;
float32 calculated_ref;
float32 calculated_sample;
float32 gain_ref;
float32 gain_sample;

int main()
{
	MRCC_InitClock();
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPB_EN);
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_AFIO_EN);
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_AFIO_EN);
	MRCC_EnablePeripheralClock(MRCC_APB1, MRCC_APB1_SPI2_EN);

	adc_init();
	MCP4151_Init();
	uint8 de7k;
	eeprom_write_Nbytes(EEPROM_Slave_address, 7, 1);
	MSTK_uint8Delay(500);
	eeprom_read_byte(EEPROM_Slave_address, &de7k, 1);
	MSTK_uint8Delay(500);
	while(1)
	{
		read_reference_voltage(&calculated_ref, &gain_ref);
		read_sample_voltage(&calculated_sample, &gain_sample);
		delay_ms(10);
	}
	return 0;
}




















//#include "MCAL/I2C/I2C_Interface.h"
//#include "MCAL/RCC/RCC_Interface.h"
//#include "MCAL/I2C/I2C_private.h"
//#include "MCAL/I2C/I2C_Config.h"
//#include "HAL/ADC.h"
//#include "MCP4151.h"
//#include "Signal_Conditioning/signal_conditioning.h"
//
//void delay_ms(uint32 milliseconds);
//
//uint8 ch2[2];
//uint8 ch[3];
//float32 ref;
//float32 ref_amp_5;
//float32 ref_amp_10;
//float32 ref_amp_15;
//float32 ref_amp_20;
//float32 ref_amp_25;
//float32 ref_amp_30;
//float32 sample;
//float32 sample_amp;
//float32 gain_5;
//float32 gain_10;
//float32 gain_15;
//float32 gain_20;
//float32 gain_25;
//float32 gain_30;
//uint8 steps;
//float32 calculated_ref;
//float32 calculated_sample;
//float32 gain_ref;
//float32 gain_sample;
//
//int main()
//{
//	MRCC_InitClock();
//	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPB_EN);
//	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_AFIO_EN);
//	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);
//	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_AFIO_EN);
//	MRCC_EnablePeripheralClock(MRCC_APB1, MRCC_APB1_SPI2_EN);
//
//	adc_init();
//	ADC_config config;
//	config.OS = OS_NO_EFFECT;
//	config.MUX = MUX_AIN0_GND;
//	config.PGA = PGA_4_096;
//	config.MODE = MODE_CONT_CONVERSION;
//	config.DR = DR_128SPS;
//	config.COMP_MODE = COMP_MODE_DEFAULT;
//	config.COMP_POL = COMP_POL_DEFAULT;
//	config.COMP_LAT = COMP_LAT_DEFAULT;
//	config.COMP_QUE = COMP_QUE_DEFAULT;
//
//	MCP4151_Init();
//	ref_sample x;
//	x = REFERENCE;
//	steps = steps_calculate(10.0, x);
//	//Set_Reference_Gain(5.0);
//	//Set_Sample_Gain(10.0);
//	gain_5 = get_reference_gain(5.0);
//	gain_10 = get_reference_gain(10.0);
//	gain_15 = get_reference_gain(15.0);
//	gain_20 = get_reference_gain(20.0);
//	gain_25 = get_reference_gain(25.0);
//	gain_30 = get_reference_gain(30.0);
//
//	while(1)
//	{
//		ref = adc_read_mv(config);
//		delay_ms(5);
//		config.MUX = MUX_AIN1_GND;
//		Set_Reference_Gain(5.0);
//		ref_amp_5 = adc_read_mv(config);
//		delay_ms(5);
//		Set_Reference_Gain(10.0);
//		ref_amp_10 = adc_read_mv(config);
//		delay_ms(5);
//		Set_Reference_Gain(15.0);
//		ref_amp_15 = adc_read_mv(config);
//		delay_ms(5);
//		Set_Reference_Gain(20.0);
//		ref_amp_20 = adc_read_mv(config);
//		delay_ms(5);
//		Set_Reference_Gain(25.0);
//		ref_amp_25 = adc_read_mv(config);
//		delay_ms(5);
//		Set_Reference_Gain(30.0);
//		ref_amp_30 = adc_read_mv(config);
//		delay_ms(5);
//		config.MUX = MUX_AIN0_GND;
//		delay_ms(5);
//		read_reference_voltage(&calculated_ref, &gain_ref);
//		read_sample_voltage(&calculated_sample, &gain_sample);
//		delay_ms(5);
//	}
//	return 0;
//}


