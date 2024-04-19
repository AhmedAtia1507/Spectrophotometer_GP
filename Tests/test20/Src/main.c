#include "MCAL/I2C/I2C_Interface.h"
#include "HAL/I2C_EEPROM/I2C_Slave_EEPROM.h"
void delay_ms(uint32 milliseconds);

unsigned char ch2[7] = {0};
void main()
{
	MRCC_InitClock();
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPB_EN);
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_AFIO_EN);

	//Test case 1
	unsigned char ch1[] = {0x1,0x2,0x3,0x4,0x5,0x6,0x7};


	eeprom_init();
	eeprom_write_Nbytes(0xA0,ch1,7);
	delay_ms(20);
	eeprom_read_byte(0xA1, ch2, 7);
	delay_ms(20);

	//Test case 2
	ch1[0] = 0xA;
	ch1[1] = 0xB;
	ch1[2] = 0xC;
	ch1[3] = 0xD;

	eeprom_write_Nbytes(0x21,ch1,4);
	delay_ms(20);
	eeprom_read_byte(0x21, ch2, 4);
	delay_ms(20);

	while(1)
	{

	}
}


