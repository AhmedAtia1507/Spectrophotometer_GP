#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/Std_Types.h"

#include "../../MCAL/RCC/RCC_Interface.h"
#include "../../MCAL/GPIO/GPIO_Interface.h"
#include "../../MCAL/NVIC/NVIC_Interface.h"
#include "../../MCAL/UART/UART_Interface.h"
#include "../../MCAL/STK/STK_Interface.h"
#include "../../MCAL/RTC/RTC_Interface.h"

#include "../../HAL/ESP32/ESP32_Interface.h"
#include "../../HAL/STEPPER_MOTOR/MOTORS_Interface.h"
#include "../../HAL/ADS1115/ADC.h"

#include "../../APP/SCommands/SCommands_Interface.h"
#include "../../APP/SPECTRO/SPECTRO_Interface.h"
#include "../../APP/Signal_Conditioning/signal_conditioning.h"
#include "APP/SpectroStatus/SpectroStatus_Interface.h"


int main(void)
{
	/////////////////////////////////////////////////
	/////////////////////////////////////////////////
	SPECTRO_InitSoftware();
	




	//SPECTRO_InitSystem();
	//SPECTRO_Status_t Loc_uint32SpectroStatus = ERROR_INITIALIZING;

	//SpectroStatus_GetCurrentStatus(&Loc_uint32SpectroStatus);

	//if(Loc_uint32SpectroStatus == IDLE)
	//{
	//	HMOTOR_GoHome(HMOTOR_WL_SELECT);
	//}

	MSTK_uint8Delay(3000);
		MGPIO_SetPinValue(MGPIO_PORTA, MGPIO_PIN9, MGPIO_HIGH);
  MGPIO_SetPinValue(MGPIO_PORTB, MGPIO_PIN14, MGPIO_HIGH);
	HMOTOR_Step(HMOTOR_WL_SELECT, 85, HMOTORS_CLKWISE_DIRECTION, 6);
	HMOTOR_GoHome(HMOTOR_LAMP_SELECT);
	HMOTOR_GoHome(HMOTOR_FILTER_SELECT);
	HMOTOR_GoHome(HMOTOR_WL_SELECT);
	
	HMOTOR_MoveLampMotor(HMOTOR_LAMP_VIS);
	
	//float32 Loc_float32Ref[2] = {0.0};
	float32 Loc_float32Gain = 0.0;
	
	
	uint32 Loc_uint32Index = 0;
	float32 de7k[33] = {0.0};
	uint32 de7keteen[33] = {0.0};
	
	adc_init();
	HMOTOR_Step(HMOTOR_WL_SELECT, 77, HMOTORS_CLKWISE_DIRECTION, 20);
	for(Loc_uint32Index = 0; Loc_uint32Index < 33; Loc_uint32Index++)
	{
		MUART_SendIntegerValue(UART3, Loc_uint32Index);
		MUART_TxChar(UART3, ':');
		MUART_TxChar(UART3, ' ');
		//read_reference_voltage(&de7k[0][index], &Loc_float32Gain[0]);
		read_sample_voltage(&de7k[Loc_uint32Index], &Loc_float32Gain);
		HESP32_SendDetectorValues(&de7k[Loc_uint32Index], &Loc_float32Gain);
		HMOTOR_GetCurrentMotorSteps(HMOTOR_WL_SELECT, &de7keteen[Loc_uint32Index]);
		HMOTOR_Step(HMOTOR_WL_SELECT, 1, HMOTORS_CLKWISE_DIRECTION, 20);
		MSTK_uint8Delay(50);
		
	}
	uint32 middle_step = Medium_Step_Index(de7k, 33);
	MUART_SendIntegerValue(UART3, middle_step);
	MUART_TxChar(UART3, '\n');
	HMOTOR_Step(HMOTOR_WL_SELECT, 33, HMOTORS_CCLKWISE_DIRECTION, 20);
	HMOTOR_Step(HMOTOR_WL_SELECT, middle_step, HMOTORS_CLKWISE_DIRECTION, 20);
	
	for(Loc_uint32Index = 0; Loc_uint32Index < 20; Loc_uint32Index++)
	{
		MUART_SendIntegerValue(UART3, Loc_uint32Index);
		MUART_TxChar(UART3, ':');
		MUART_TxChar(UART3, ' ');
		//read_reference_voltage(&de7k[0][index], &Loc_float32Gain[0]);
		read_sample_voltage(&de7k[Loc_uint32Index], &Loc_float32Gain);
		HESP32_SendDetectorValues(&de7k[Loc_uint32Index], &Loc_float32Gain);
		HMOTOR_Step(HMOTOR_WL_SELECT, 1, HMOTORS_CLKWISE_DIRECTION, 20);
		MSTK_uint8Delay(50);
		
	}
	HMOTOR_Step(HMOTOR_WL_SELECT, 20, HMOTORS_CCLKWISE_DIRECTION, 20);
	for(Loc_uint32Index = 0; Loc_uint32Index < 20; Loc_uint32Index++)
	{
		MUART_SendIntegerValue(UART3, Loc_uint32Index);
		MUART_TxChar(UART3, ':');
		MUART_TxChar(UART3, ' ');
//		read_reference_voltage(&de7k[0][index], &Loc_float32Gain[0]);
		read_sample_voltage(&de7k[Loc_uint32Index], &Loc_float32Gain);
		HESP32_SendDetectorValues(&de7k[Loc_uint32Index], &Loc_float32Gain);
		HMOTOR_Step(HMOTOR_WL_SELECT, 1, HMOTORS_CCLKWISE_DIRECTION, 20);
		MSTK_uint8Delay(50);
		
	}	
	//HMOTOR_Step(HMOTOR_WL_SELECT, 2500, HMOTORS_CLKWISE_DIRECTION, 10);
		//for(Loc_uint32Index = 0; Loc_uint32Index < 3500; Loc_uint32Index++)
		//{
			//MUART_SendIntegerValue(UART3, (Loc_uint32Index + 2500));
			//MUART_TxChar(UART3, ':');
			//MUART_TxChar(UART3, ' ');
			//read_reference_voltage(&Loc_float32Ref[0], &Loc_float32Gain[0]);
			//read_sample_voltage(&Loc_float32Ref[1], &Loc_float32Gain[1]);
			//HESP32_SendDetectorValues(Loc_float32Ref, Loc_float32Gain);
			//HMOTOR_Step(HMOTOR_WL_SELECT, 1, HMOTORS_CLKWISE_DIRECTION, 20);
			//MSTK_uint8Delay(50);
		
	//}
	while(1)
	{
			//for(Loc_uint32Index = 0; Loc_uint32Index < 30; Loc_uint32Index++)
			//{
				//MUART_SendIntegerValue(UART3, Loc_uint32Index);
				//MUART_TxChar(UART3, ':');
				//MUART_TxChar(UART3, ' ');
				//read_reference_voltage(&Loc_float32Ref[0], &Loc_float32Gain[0]);
				//read_sample_voltage(&Loc_float32Ref[1], &Loc_float32Gain[1]);
				//HESP32_SendDetectorValues(Loc_float32Ref, Loc_float32Gain);
				//HMOTOR_Step(HMOTOR_WL_SELECT, 1, HMOTORS_CLKWISE_DIRECTION, 20);
				//MSTK_uint8Delay(50);
		
			//}
			//MSTK_uint8Delay(2000);
			//HMOTOR_Step(HMOTOR_WL_SELECT, 30, HMOTORS_CCLKWISE_DIRECTION, 10);
			//read_reference_voltage(&Loc_float32Ref[0], &Loc_float32Gain[0]);
			//read_sample_voltage(&Loc_float32Ref[1], &Loc_float32Gain[1]);
			//HESP32_SendDetectorValues(Loc_float32Ref, Loc_float32Gain);
			//MSTK_uint8Delay(2000);
			//HMOTOR_Step(HMOTOR_WL_SELECT, 15, HMOTORS_CLKWISE_DIRECTION, 10);
			
			
			//HMOTOR_Step(HMOTOR_FILTER_SELECT, 1500, HMOTORS_CLKWISE_DIRECTION, 10);
			//HMOTOR_Step(HMOTOR_FILTER_SELECT, 1500, HMOTORS_CCLKWISE_DIRECTION, 10);
			//MSTK_uint8Delay(500);
			//HMOTOR_Step(HMOTOR_WL_SELECT, 1, HMOTORS_CLKWISE_DIRECTION, 10);
		//read_reference_voltage(&Loc_float32Ref, &Loc_float32Gain);
		//read_sample_voltage(&Loc_float32Sample, &Loc_float32Gain);
		//MSTK_uint8Delay(100);
	}
	return 0;
}
