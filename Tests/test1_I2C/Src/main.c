#include "MCAL/I2C/I2C_Interface.h"
#include "HAL/I2C_EEPROM/I2C_Slave_EEPROM.h"
void delay_ms(u32 milliseconds);

unsigned char ch2[7] = {0};
void main()
{
	MRCC_u8InitClock();
	MRCC_u8EnablePeripheralClock(RCC_APB2, RCC_APB2_IOPA_EN);
	MRCC_u8EnablePeripheralClock(RCC_APB2, RCC_APB2_IOPB_EN);
	MRCC_u8EnablePeripheralClock(RCC_APB2, RCC_APB2_AFIO_EN);

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

	eeprom_write_Nbytes(0xFFF,ch1,4);
	eeprom_read_byte(0xFFF, ch2, 4);

	while(1)
	{

	}
}

void delay_ms(u32 milliseconds) {
    // Assuming a 1 MHz clock frequency for illustration purposes
    // Adjust the loop count based on your actual clock frequency
    // This is a simple and blocking delay function
    // In a real application, you might want to use a timer for more accurate timing

    // Calculate the loop count needed for the specified delay
    u32 loop_count = milliseconds * 1000;

    // Perform the delay using a loop
    for (u32 i = 0; i < loop_count; i++) {
        // Do nothing
    }
}
