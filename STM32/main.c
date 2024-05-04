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


#include "../../APP/SCommands/SCommands_Interface.h"
#include "../../APP/SPECTRO/SPECTRO_Interface.h"
#include "../../APP/Signal_Conditioning/signal_conditioning.h"

int main(void)
{
  	SPECTRO_InitSoftware();
	MSTK_uint8Delay(3000);
  	//MGPIO_SetPinValue(MGPIO_PORTB, MGPIO_PIN14, MGPIO_HIGH);
//	HMOTOR_GoHome(HMOTOR_LAMP_SELECT);
//	HMOTOR_GoHome(HMOTOR_FILTER_SELECT);
//	HMOTOR_GoHome(HMOTOR_WL_SELECT);
	
//	HMOTOR_MoveLampMotor(HMOTOR_LAMP_VIS);
	
	float32 Loc_float32Ref[2] = {0.0};
	float32 Loc_float32Gain[2] = {0.0};
	
//	HMOTOR_Step(HMOTOR_WL_SELECT, 85, HMOTORS_CLKWISE_DIRECTION, 6);
	uint32 Loc_uint32Index = 0;
	for(Loc_uint32Index = 0; Loc_uint32Index < 20; Loc_uint32Index++)
	{
			read_reference_voltage(&Loc_float32Ref[0], &Loc_float32Gain[0]);
		read_sample_voltage(&Loc_float32Ref[1], &Loc_float32Gain[1]);
//		HESP32_SendDetectorValues(Loc_float32Ref, Loc_float32Gain);
//		HMOTOR_Step(HMOTOR_WL_SELECT, 1, HMOTORS_CLKWISE_DIRECTION, 6);
		MSTK_uint8Delay(500);
		
	}	
	while(1)
	{
			
			//HMOTOR_Step(HMOTOR_FILTER_SELECT, 1500, HMOTORS_CLKWISE_DIRECTION, 10);
			//MSTK_uint8Delay(500);
			//HMOTOR_Step(HMOTOR_FILTER_SELECT, 1500, HMOTORS_CCLKWISE_DIRECTION, 10);
			//MSTK_uint8Delay(500);
			//HMOTOR_Step(HMOTOR_WL_SELECT, 1, HMOTORS_CLKWISE_DIRECTION, 10);
		//read_reference_voltage(&Loc_float32Ref, &Loc_float32Gain);
		//read_sample_voltage(&Loc_float32Sample, &Loc_float32Gain);
		//MSTK_uint8Delay(100);
	}
	return 0;
}
