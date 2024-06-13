/*
 * MCP4151.c
 *
 *  Created on: Apr 21, 2024
 *      Author: Mohanad
 */
#include "MCP4151.h"
#include "math.h"

// Function to provide a delay in milliseconds
void delay_ms(uint32 milliseconds) {
	// Assuming a 1 MHz clock frequency for illustration purposes
	// Adjust the loop count based on your actual clock frequency
	// This is a simple and blocking delay function
	// In a real application, you might want to use a timer for more accurate timing

	// Calculate the loop count needed for the specified delay
	uint32 loop_count = milliseconds * 1000;

	// Perform the delay using a loop
	for (uint32 i = 0; i < loop_count; i++) {
		// Do nothing
	}
}
void delay_micro(uint32 milliseconds) {
	// Assuming a 1 MHz clock frequency for illustration purposes
	// Adjust the loop count based on your actual clock frequency
	// This is a simple and blocking delay function
	// In a real application, you might want to use a timer for more accurate timing

	// Calculate the loop count needed for the specified delay
	uint32 loop_count = milliseconds;

	// Perform the delay using a loop
	for (uint32 i = 0; i < loop_count; i++) {
		// Do nothing
	}
}
void MCP4151_Sample_SetWiperPosition(uint8 position){

	uint16 command = 0x00;
	MGPIO_SetPinValue(MGPIO_PORTA, MGPIO_PIN8, MGPIO_LOW);
	delay_micro(10);
	MCAL_SPI_SendData(SPI2, &command, Pollingenable);
	delay_micro(10);
	command = position;
	MCAL_SPI_SendData(SPI2, &command, Pollingenable);
	delay_micro(10);
	MGPIO_SetPinValue(MGPIO_PORTA, MGPIO_PIN8, MGPIO_HIGH);
}

void MCP4151_Referance_SetWiperPosition(uint8 position){

	uint16 command = 0x00;
	MGPIO_SetPinValue(MGPIO_PORTA, MGPIO_PIN2, MGPIO_LOW);
	delay_ms(10);
	MCAL_SPI_SendData(SPI2, &command, Pollingenable);
	delay_ms(10);
	command = position;
	MCAL_SPI_SendData(SPI2, &command, Pollingenable);
	delay_ms(10);
	MGPIO_SetPinValue(MGPIO_PORTA, MGPIO_PIN2, MGPIO_HIGH);
}

/**================================================================
 * @Fn				 -MCP4151 Init
 * @brief			 -Initializes SPI
 * @param[in]		 -none
 * @retval			 -none
 * Note				 -SPI2 used
 */
void MCP4151_Init()
{
	//SPI Init

	SPI_Config SPI2CFG;

	SPI2CFG.CLKPhase = SPI_Clock_Phase_2EDGE_first_data_capture_edge;
	SPI2CFG.CLKPolarity = SPI_CLKPolarity_HIGH_when_idle;
	SPI2CFG.DataSize = SPI_DataSize_8BIT;
	SPI2CFG.Frame_Format = SPI_Frame_Format_MSB_transmitted_first;
	SPI2CFG.SPI_BAUDRATEPRESCALER = SPI_BAUDRATEPRESCALER_16;
	SPI2CFG.Communication_Mode = SPI_Direction_2LINES;

#ifdef MCU_Act_As_Master

	SPI2CFG.Device_Mode = SPI_Device_Mode_MASTER;
	SPI2CFG.IRQ_Enable = SPI_IRQ_Enable_NONE;
	SPI2CFG.NSS = SPI_NSS_soft_NSSInternalSoft_Set;
	SPI2CFG.P_IRQ_CallBack = 0;

#endif

	MCAL_SPI_Init(SPI2,&SPI2CFG);
	MCAL_SPI_GPIO_Set_Pins (SPI2);
}


/**================================================================
 * @Fn				 -Set_Sample_Gain
 * @brief			 -Sets the gain of sample voltage, sends required steps to the MCP4151 connected to sample
 * @param[in]		 -gain: required gain to be set
 * @retval			 -none
 * Note			 	 -The gain value is changed according to the required steps which is rounded to the nearest integer
 * 					 -To get the resulted gain value, use the function "get_reference_gain"
 */
void Set_Sample_Gain(float32 gain)
{
	//Sample
	MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN8, MGPIO_OUTPUT_PUSH_PULL_10MHZ);
	MGPIO_SetPinValue(MGPIO_PORTA, MGPIO_PIN8, MGPIO_HIGH);
	delay_micro(5);
	ref_sample x = SAMPLE;
	uint8 steps = steps_calculate(gain, x);
	MCP4151_Sample_SetWiperPosition(steps);
}

/**================================================================
 * @Fn				 -Set_Reference_Gain
 * @brief			 -Sets the gain of reference voltage, sends required steps to the MCP4151 connected to reference
 * @param[in]		 -gain: required gain to be set
 * @retval			 -none
 * Note			 	 -The gain value is changed according to the required steps which is rounded to the nearest integer
 * 					 -To get the resulted gain value, use the function "get_sample_gain"
 */
void Set_Reference_Gain(float32 gain)
{
	//Referance
	MGPIO_SetPinMode(MGPIO_PORTA, MGPIO_PIN2, MGPIO_OUTPUT_PUSH_PULL_10MHZ);
	MGPIO_SetPinValue(MGPIO_PORTA, MGPIO_PIN2, MGPIO_HIGH);
	delay_ms(5);
	ref_sample x = REFERENCE;
	uint8 steps = steps_calculate(gain, x);
	MCP4151_Referance_SetWiperPosition(steps);
}


/**================================================================
 * @Fn				 -steps_calculate
 * @brief			 -Calculates the steps required to be sent to the MCP4151
 * @param[in]		 -gain: required gain to be set
 * @param[in]		 -x: where x can be REFERENCE or SAMPLE
 * @retval			 -steps: calculated no. of steps
 * Note			 	 -The number of steps is rounded to the nearest integer
 */
uint8 steps_calculate(float32 gain, ref_sample x)
{
	int total_resistance;
	if (x == REFERENCE)
		total_resistance = MCP_TOTAL_RESISTANCE_REFERENCE;
	else
		total_resistance = MCP_TOTAL_RESISTANCE_SAMPLE;
	float32 R;
	R = (RESISTANCE_ON_PCB / (gain - 1)) + WIPER_RESISTANCE;
	float32 steps_result;
	steps_result = ((total_resistance - R) * 256) / total_resistance;
	uint8 steps = round(steps_result);
	return steps;
}

/**================================================================
 * @Fn				 -steps_calculate
 * @brief			 -Calculates the resulted gain value according to the
 * 					  changed number of steps which is rounded to the nearest integer
 * @param[in]		 -gain: required gain to be set
 * @retval			 -gain: resulted gain for the reference
 * Note			 	 -none
 */
float32 get_reference_gain(float32 gain)
{
	ref_sample x = REFERENCE;
	uint8 steps = steps_calculate(gain, x);
	float32 R = MCP_TOTAL_RESISTANCE_REFERENCE - steps * (MCP_TOTAL_RESISTANCE_REFERENCE / 256.0);
	gain = 1 + (RESISTANCE_ON_PCB / R);
	return gain;
}

/**================================================================
 * @Fn				 -steps_calculate
 * @brief			 -Calculates the resulted gain value according to the
 * 					  changed number of steps which is rounded to the nearest integer
 * @param[in]		 -gain: required gain to be set
 * @retval			 -gain: resulted gain for the sample
 * Note			 	 -none
 */
float32 get_sample_gain(float32 gain)
{
	ref_sample x = SAMPLE;
	uint8 steps = steps_calculate(gain, x);
	float32 R = MCP_TOTAL_RESISTANCE_SAMPLE- steps * (MCP_TOTAL_RESISTANCE_SAMPLE / 256.0);
	gain = 1 + (RESISTANCE_ON_PCB / R);
	return gain;
}


