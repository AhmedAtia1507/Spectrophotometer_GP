/**
 * @file main.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: C main to test the GPIO & RCC Drivers functionality
 * @version 1.0
 * @date 2023-11-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "BIT_MATH.h"
#include "Std_Types.h"

#include "RCC_Interface.h"
#include "GPIO_Interface.h"

#define LED_PORT                    MGPIO_PORTA
#define LED_PIN                     MGPIO_PIN2
#define SW_PORT                     MGPIO_PORTB
#define SW_PIN                      MGPIO_PIN11

int main(void)
{
    //Here, We Intitalize the clock by selecting the clock source as HSE clock "High Speed External"
    MRCC_InitClock();

    //And We enable clock for peripherals GPIO Port A & B
    MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);
    MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPB_EN);

    //We set the mode of the LED Pin as output and the Switch Pin as Input Pull up    
    MGPIO_SetPinMode(LED_PORT, LED_PIN, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
    MGPIO_SetPinMode(SW_PORT, SW_PIN, MGPIO_INPUT_PULL_UP_OR_DOWN_MODE);
    MGPIO_ActivatePullUp(SW_PORT, SW_PIN);

    uint8 Loc_uint8SWValue = 0;

    while(1)
    {
        //If the switch is pressed, toggle the value of the LED pin
        MGPIO_GetPinValue(SW_PORT, SW_PIN, &Loc_uint8SWValue);
        if(Loc_uint8SWValue == MGPIO_LOW)
        {
          MGPIO_TogglePinValue(LED_PORT, LED_PIN);
          while(Loc_uint8SWValue == MGPIO_LOW)
          {
            MGPIO_GetPinValue(SW_PORT, SW_PIN, &Loc_uint8SWValue);
          }
        }
    }
    return 0;
}
