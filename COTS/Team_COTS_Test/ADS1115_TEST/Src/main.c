#include "MCAL/I2C/I2C_Interface.h"
#include "MCAL/RCC/RCC_Interface.h"
#include "MCAL/I2C/I2C_private.h"
#include "MCAL/I2C/I2C_Config.h"
#include "HAL/ADC.h"

void delay_ms(uint32 milliseconds);

uint8 ch2[2];
uint8 ch[3];
float32 mv;

int main()
{
	MRCC_u8InitClock();
	MRCC_u8EnablePeripheralClock(RCC_APB2, RCC_APB2_IOPB_EN);
	MRCC_u8EnablePeripheralClock(RCC_APB2, RCC_APB2_AFIO_EN);

	adc_init();
	ADC_config config;
	config.OS = OS_NO_EFFECT;
	config.MUX = MUX_AIN0_GND;
	config.PGA = PGA_4_096;
	config.MODE = MODE_SINGLE_SHOT;
	config.DR = DR_128SPS;
	config.COMP_MODE = COMP_MODE_DEFAULT;
	config.COMP_POL = COMP_POL_DEFAULT;
	config.COMP_LAT = COMP_LAT_DEFAULT;
	config.COMP_QUE = COMP_QUE_DEFAULT;

	while(1)
	{
		mv = adc_read_mv(config);
		delay_ms(1000);
	}
	return 0;
}


