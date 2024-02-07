#include "BIT_MATH.h"
#include "Std_Types.h"

#include "RCC_Interface.h"
#include "GPIO_Interface.h"
#include "STK_Interface.h"

#include "MOTORS_Interface.h"

int main(void)
{
    MRCC_InitClock();
    MSTK_uint8Init();
		HMOTORS_Init();
    
    while(1)
    {
        HMOTOR_Step(3 * HMOTORS_FULL_CYCLE, HMOTORS_CLKWISE_DIRECTION);
				MSTK_uint8Delay(1000);
				HMOTOR_Step(3 * HMOTORS_FULL_CYCLE,HMOTORS_CCLKWISE_DIRECTION);
				MSTK_uint8Delay(1000);
    }
}