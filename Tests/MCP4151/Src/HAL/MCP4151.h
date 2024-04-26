/*
 * MCP4151.h
 *
 *  Created on: Apr 21, 2024
 *      Author: Mohanad
 */

#ifndef HAL_MCP4151_H_
#define HAL_MCP4151_H_

#include "SPI_Interface.h"
#include "GPIO_Interface.h"

#define MCU_Act_As_Master
#define RESISTANCE_ON_PCB				100000
#define MCP_TOTAL_RESISTANCE_REFERENCE	48400
#define MCP_TOTAL_RESISTANCE_SAMPLE		48400
#define WIPER_RESISTANCE				311

typedef enum
{
	REFERENCE,
	SAMPLE
}ref_sample;

//************************************************************************************//
//********************* Functions used to control gain on the PCB *********************//
//************************************************************************************//
void MCP4151_Init();
void Set_Sample_Gain(float32 gain);
void Set_Reference_Gain(float32 gain);

//************************************************************************************//
//******************* Additional functions to provide info for user ******************//
//************************************************************************************//
uint8 steps_calculate(float32 gain, ref_sample x);
float32 get_reference_gain(float32 gain);
float32 get_sample_gain(float32 gain);

#endif /* HAL_MCP4151_H_ */
