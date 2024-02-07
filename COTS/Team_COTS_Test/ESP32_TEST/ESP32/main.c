#include "BIT_MATH.h"
#include "Std_Types.h"

#include "RCC_Interface.h"
#include "GPIO_Interface.h"
#include "NVIC_Interface.h"
#include "UART_Interface.h"
#include "STK_Interface.h"

#include "ESP32_Interface.h"

void acknowledged(void)
{
    MGPIO_SetPinValue(MGPIO_PORTB, MGPIO_PIN1, MGPIO_HIGH);
    MGPIO_SetPinValue(MGPIO_PORTB, MGPIO_PIN2, MGPIO_LOW);
}
void invalid_command(void)
{
    MGPIO_SetPinValue(MGPIO_PORTB, MGPIO_PIN1, MGPIO_LOW);
    MGPIO_SetPinValue(MGPIO_PORTB, MGPIO_PIN2, MGPIO_HIGH);
}
int main(void)
{
    MRCC_InitClock();
		MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPB_EN);
    //Acknowledge LED
    MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN1, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    
    //invalid command LED
    MGPIO_SetPinMode(MGPIO_PORTB, MGPIO_PIN2, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
	
    MSTK_uint8Init();
    HESP32_SetTaskCallbackFunction(0, acknowledged);
    HESP32_SetTaskCallbackFunction(1, invalid_command);
    
    HESP32_InitInterface();


    while(1)
    {
//        HESP32_SendCommand("set uv on");
//        MSTK_uint8Delay(2000);

//        HESP32_SendCommand("set uv off");
//        MSTK_uint8Delay(2000);

//        HESP32_SendCommand("set vis on");
//        MSTK_uint8Delay(2000);

//        HESP32_SendCommand("set vis off");
//        MSTK_uint8Delay(2000);

//        HESP32_SendCommand("SET VIS ON");
//        MSTK_uint8Delay(2000);
    }
}
