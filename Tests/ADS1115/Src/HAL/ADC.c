/*
 * ADC.c
 *
 *  Created on: Feb 12, 2024
 *      Author: Mohanad
 */

#include "../MCAL/I2C/I2C_Interface.h"
#include "ADC.h"

uint8 ch4[2];

void adc_init(void)
{

	//==================I2C INIT =============================
	//		PB6 : I2C1_SCL
	//		PB7 : I2C1_SDA

	I2C_InitTypeDef I2C1CFG ;

	//I2C Controller act as a Master

	I2C1CFG.General_Call_Address_Detection = I2C_ENGC_Enable ;
	I2C1CFG.I2C_ACK_Control =I2C_Ack_Enable ;
	I2C1CFG.I2C_ClockSpeed = I2C_SCLK_SM_100k ;
	I2C1CFG.I2C_Mode = I2C_mode_I2C ;
	I2C1CFG.P_Slave_Event_CallBack = 0 ;
	I2C1CFG.StretchMode = I2C_StretchMode_Enable;

	MCAL_I2C_GPIO_Set_Pins (I2C1);
	MCAL_I2C_Init(I2C1, &I2C1CFG);
	MCAL_I2C_RESET();
	MCAL_I2C_Init(I2C1, &I2C1CFG);
}

float32 adc_read_mv(ADC_config a)
{
	uint16 Slave_address = 0x49;
	uint8 ch[3], ch2[2];
	uint8 ch4[2];
	uint16 reading;
	float32 mv;
	ch[0] = 0x01;
	ch[1] = (a.OS << 7) | (a.MUX << 4) | (a.PGA<<1) | (a.MODE<<0);
	ch[2] = (a.DR<<5) | (a.COMP_MODE<<4) | (a.COMP_POL<<3) | (a.COMP_LAT<<2) | (a.COMP_QUE);
	MCAL_I2C_MASTER_TX(I2C1, Slave_address, ch, 3, With_Stop, Start);
	ch[0] = 0x00;
	MCAL_I2C_MASTER_TX(I2C1, Slave_address, ch, 1, With_Stop, Start);
	delay_ms(10);
	MCAL_I2C_MASTER_RX(I2C1, Slave_address, ch4 , 2, With_Stop,Start);
	reading = (ch4[1] << 8) | ch4[0];
	mv = ((float32)reading * ((float32)4.096/(float32)0x8000))*1000;
	return mv;
}
