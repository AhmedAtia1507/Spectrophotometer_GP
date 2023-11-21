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

int main(void)
{
    Std_ReturnType Loc_uint8FuncStatus = MRCC_InitClock();

    if(Loc_uint8FuncStatus == E_OK)
    {
        Loc_uint8FuncStatus = MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);
        if(Loc_uint8FuncStatus == E_OK)
        {
            Loc_uint8FuncStatus = MGPIO_SetPinMode(LED_PORT, LED_PIN, MGPIO_OUTPUT_PUSH_PULL_2MHZ);
            if(Loc_uint8FuncStatus == E_OK)
            {
                Loc_uint8FuncStatus = MGPIO_SetPinValue(LED_PORT, LED_PIN, MGPIO_HIGH);
            }
            else
            {

            }
        }
        else
        {

        }
    }
    else
    {
        /*Do nothing*/
    }
    while(1)
    {

    }
    return 0;
}
