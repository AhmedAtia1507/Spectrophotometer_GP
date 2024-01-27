#include "MCAL/I2C/I2C_Interface.h"
#include "MCAL/RCC/RCC_Interface.h"
#include "MCAL/I2C/I2C_private.h"
#include "MCAL/I2C/I2C_Config.h"

void delay_ms(u32 milliseconds);

#define MAFIO_BASE_ADDRESS				0x40010000U
#define MAFIO_MAPR_R					(*(volatile u32*)(MAFIO_BASE_ADDRESS + 0x04))
#define MAFIO_MAPR_I2C1_REMAP_BIT		1

u8 ch2[2];
u8 ch[3];

int main()
{
	MRCC_u8InitClock();
	MRCC_u8EnablePeripheralClock(RCC_APB2, RCC_APB2_IOPB_EN);
	MRCC_u8EnablePeripheralClock(RCC_APB2, RCC_APB2_AFIO_EN);
	MAFIO_MAPR_R |= (1 << MAFIO_MAPR_I2C1_REMAP_BIT);

	//==================I2C INIT =============================
	//		PB6 : I2C1_SCL
	//		PB7 : I2C1_SDA

	I2C_InitTypeDef I2C1CFG ;

	//I2C Controller act as a Master

	I2C1CFG.General_Call_Address_Detection = I2C_ENGC_Enable ;
	I2C1CFG.I2C_ACK_Control =I2C_Ack_Enable ;
	I2C1CFG.I2C_ClockSpeed = I2C_SCLK_SM_100k ;
	I2C1CFG.I2C_Mode = I2C_mode_I2C ;
	I2C1CFG.P_Slave_Event_CallBack = NULL ;
	I2C1CFG.StretchMode = I2C_StretchMode_Enable;

	MCAL_I2C_GPIO_Set_Pins (I2C1);
	MCAL_I2C_Init(I2C1, &I2C1CFG);
	MCAL_I2C_RESET();
	MCAL_I2C_Init(I2C1, &I2C1CFG);

	u16 Slave_address = 0x48;
	u16 reading;
	ch[0] = 0x01;
	ch[1] = 0xc1;
	ch[2] = 0b11100011;
	MCAL_I2C_MASTER_TX(I2C1, Slave_address, ch, 3, With_Stop, Start);
	ch[0] = 0x00;
	MCAL_I2C_MASTER_TX(I2C1, Slave_address, ch, 1, With_Stop, Start);
	delay_ms(10);
	while(1)
	{
		ch[0] = 0b00000001;
		ch[1] = 0b11000011;
		ch[2] = 0b10000011;
		MCAL_I2C_MASTER_TX(I2C1, Slave_address, ch, 3, With_Stop, Start);
		ch[0] = 0x00;
		MCAL_I2C_MASTER_TX(I2C1, Slave_address, ch, 1, With_Stop, Start);
		delay_ms(10);
		MCAL_I2C_MASTER_RX(I2C1, Slave_address, ch2 , 2, With_Stop,Start);
		delay_ms(1000);
	}
	return 0;
}


