#include "BIT_MATH.h"
#include "Std_Types.h"

#include "MOTORS_Private.h"
#include "MOTORS_Interface.h"
#include "MOTORS_Config.h"

#include "RCC_Interface.h"
#include "GPIO_Interface.h"
#include "STK_Interface.h"

void HMOTORS_Init(void)
{
    #if HMOTORS_STEP_PORT_ID ==     MGPIO_PORTA
        MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);
    #elif HMOTORS_STEP_PORT_ID ==   MGPIO_PORTB
        MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPB_EN);
    #elif HMOTORS_STEP_PORT_ID ==   MGPIO_PORTC
        MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPC_EN);
    #else
        #error "Step Port ID is not Specified"
    #endif /*HMOTORS_STEP_PORT_ID*/
    
    #if HMOTORS_DIR_PORT_ID ==      MGPIO_PORTA
        MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);
    #elif HMOTORS_DIR_PORT_ID ==    MGPIO_PORTB
        MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPB_EN);
    #elif HMOTORS_DIR_PORT_ID ==    MGPIO_PORTC
        MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPC_EN);
    #else
        #error "Direction Port ID is not Specified"
    #endif /*HMOTORS_DIR_PORT_ID*/

    MGPIO_SetPinMode(HMOTORS_STEP_PORT_ID, HMOTORS_STEP_PIN_ID, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    MGPIO_SetPinMode(HMOTORS_DIR_PORT_ID, HMOTORS_DIR_PIN_ID, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
}

void HMOTOR_Step(uint32 Copy_uint8NoOfSetps, uint8 Copy_uint8Direction)
{
		uint8 Loc_uint8Index = 0;
		switch(Copy_uint8Direction)
		{
			case HMOTORS_CLKWISE_DIRECTION:
			{
				MGPIO_SetPinValue(HMOTORS_DIR_PORT_ID, HMOTORS_DIR_PIN_ID, MGPIO_HIGH);
				break;
			}
			case HMOTORS_CCLKWISE_DIRECTION:
			{
				MGPIO_SetPinValue(HMOTORS_DIR_PORT_ID, HMOTORS_DIR_PIN_ID, MGPIO_LOW);
				break;
			}
		}
		for(Loc_uint8Index = 0; Loc_uint8Index < (Copy_uint8NoOfSetps); Loc_uint8Index++)
		{
			MGPIO_SetPinValue(HMOTORS_STEP_PORT_ID, HMOTORS_STEP_PIN_ID, MGPIO_HIGH);
			MSTK_uint8Delay(3);
			MGPIO_SetPinValue(HMOTORS_STEP_PORT_ID, HMOTORS_STEP_PIN_ID, MGPIO_LOW);
			MSTK_uint8Delay(3);
		}
}