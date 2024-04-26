/**
 * @file GPIO_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-09-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "GPIO_Private.h"
#include "GPIO_Interface.h"
#include "GPIO_Config.h"

/**
 * @brief: Function to set the mode of the GPIO Pin
 * 
 * @param Copy_u8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_u8PinID: ID of the pin (0 --> 15)
 * @param Copy_u8PinMode: Mode of the Pin 
 * @return Std_ReturnType
 * @retval E_OK: Pin Mode has been set successfully
 * @retval E_NOT_OK: Pin mode has not been set 
 */
Std_ReturnType MGPIO_u8SetPinMode(uint8 Copy_u8PortID, uint8 Copy_u8PinID, uint8 Copy_u8PinMode)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;

    switch(Copy_u8PortID)
    {
        case GPIO_PORTA:
        {
            if(Copy_u8PinID <= GPIO_PIN7)
            {
                GPIOA_CRL &= ~((0b1111) << (4 * Copy_u8PinID));
                GPIOA_CRL |= ((Copy_u8PinMode) << (4 * Copy_u8PinID));
                Loc_u8FuncStatus = E_OK;
            }
            else if(Copy_u8PinID <= GPIO_PIN15)
            {
                GPIOA_CRH &= ~((0b1111) << (4 * (Copy_u8PinID - 8)));
                GPIOA_CRH |= ((Copy_u8PinMode) << (Copy_u8PinID - 8));
                Loc_u8FuncStatus = E_OK;
            }
            break;
        }
        case GPIO_PORTB:
        {
            if(Copy_u8PinID <= GPIO_PIN7)
            {
                GPIOB_CRL &= ~((0b1111) << (4 * Copy_u8PinID));
                GPIOB_CRL |= ((Copy_u8PinMode) << (4 * Copy_u8PinID));
                Loc_u8FuncStatus = E_OK;
            }
            else if(Copy_u8PinID <= GPIO_PIN15)
            {
                GPIOB_CRH &= ~((0b1111) << (4 * (Copy_u8PinID - 8)));
                GPIOB_CRH |= ((Copy_u8PinMode) << (4 * (Copy_u8PinID-8)));
                Loc_u8FuncStatus = E_OK;
            }
            break;
        }
        case GPIO_PORTC:
        {
            if(Copy_u8PinID <= GPIO_PIN7)
            {
                GPIOC_CRL &= ~((0b1111) << (4 * Copy_u8PinID));
                GPIOC_CRL |= ((Copy_u8PinMode) << (4 * Copy_u8PinID));
                Loc_u8FuncStatus = E_OK;
            }
            else if(Copy_u8PinID <= GPIO_PIN15)
            {

                GPIOC_CRH &= ~((0b1111) << (4 * (Copy_u8PinID - 8)));
                GPIOC_CRH |= ((Copy_u8PinMode) << (Copy_u8PinID - 8));
                Loc_u8FuncStatus = E_OK;
            }
            break;
        }
        default:
        {
            Loc_u8FuncStatus = E_NOT_OK;
            break;
        }
    }
    return Loc_u8FuncStatus;
}
/**
 * @brief: Function to set the value of the output GPIO Pin
 * 
 * @param Copy_u8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_u8PinID: ID of the pin (0 --> 15)
 * @param Copy_u8PinValue: Value to be set (High or Low) 
 * @return Std_ReturnType
 * @retval E_OK: Pin Value has been set successfully
 * @retval E_NOT_OK: Pin Value has not been set
 */
Std_ReturnType MGPIO_u8SetPinValue(uint8 Copy_u8PortID, uint8 Copy_u8PinID, uint8 Copy_u8PinValue)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    if((Copy_u8PortID <= GPIO_PORTC) && (Copy_u8PinID <= GPIO_PIN15))
    {
        switch (Copy_u8PortID)
        {
            case GPIO_PORTA:
            {
                if(Copy_u8PinValue == GPIO_HIGH)
                {
                    SET_BIT(GPIOA_ODR, Copy_u8PinID);
                    Loc_u8FuncStatus = E_OK;
                }
                else if(Copy_u8PinValue == GPIO_LOW)
                {
                    CLR_BIT(GPIOA_ODR, Copy_u8PinID);
                    Loc_u8FuncStatus = E_OK;
                }
                else
                {
                    Loc_u8FuncStatus = E_NOT_OK;
                }
                break;
            }
            case GPIO_PORTB:
            {
                if(Copy_u8PinValue == GPIO_HIGH)
                {
                    SET_BIT(GPIOB_ODR, Copy_u8PinID);
                    Loc_u8FuncStatus = E_OK;
                }
                else if(Copy_u8PinValue == GPIO_LOW)
                {
                    CLR_BIT(GPIOB_ODR, Copy_u8PinID);
                    Loc_u8FuncStatus = E_OK;
                }
                else
                {
                    Loc_u8FuncStatus = E_NOT_OK;
                }
                break;
            }
            case GPIO_PORTC:
            {
                if(Copy_u8PinValue == GPIO_HIGH)
                {
                    SET_BIT(GPIOC_ODR, Copy_u8PinID);
                    Loc_u8FuncStatus = E_OK;
                }
                else if(Copy_u8PinValue == GPIO_LOW)
                {
                    CLR_BIT(GPIOC_ODR, Copy_u8PinID);
                    Loc_u8FuncStatus = E_OK;
                }
                else
                {
                    Loc_u8FuncStatus = E_NOT_OK;
                }
                break;
            }
            default:
            {
                Loc_u8FuncStatus = E_NOT_OK;
                break;
            }
        }
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}
/**
 * @brief: Function to get the value of the input GPIO Pin
 * 
 * @param Copy_u8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_u8PinID: ID of the pin (0 --> 15)
 * @param Copy_u8PinValue: Value of input pin (High or Low) 
 * @return Std_ReturnType
 * @retval E_OK: Pin Value has been read successfully
 * @retval E_NOT_OK: Pin Value has not been read
 */
Std_ReturnType MGPIO_u8GetPinValue(uint8 Copy_u8PortID, uint8 Copy_u8PinID, uint8* P_u8PinValue)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;

    if((P_u8PinValue != 0) && (Copy_u8PortID <= GPIO_PORTC) && (Copy_u8PinID <= GPIO_PIN15))
    {
        switch(Copy_u8PortID)
        {
            case GPIO_PORTA:
            {
                *P_u8PinValue = GET_BIT(GPIOA_IDR, Copy_u8PinID);
                Loc_u8FuncStatus = E_OK;
                break;
            }
            case GPIO_PORTB:
            {
                *P_u8PinValue = GET_BIT(GPIOB_IDR, Copy_u8PinID);
                Loc_u8FuncStatus = E_OK;
                break;
            }
            case GPIO_PORTC:
            {
                *P_u8PinValue = GET_BIT(GPIOC_IDR, Copy_u8PinID);
                Loc_u8FuncStatus = E_OK;
                break;
            }
            default:
            {
                Loc_u8FuncStatus = E_NOT_OK;
                break;
            }
        }
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}
/**
 * @brief: Function to activate the internal pull-up resistor
 * 
 * @param Copy_u8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_u8PinID: ID of the pin (0 --> 15)
 * @return Std_ReturnType
 * @retval E_OK: Pull-up has been activated successfully
 * @retval E_NOT_OK: Pull-up has not been activated 
 */
Std_ReturnType MGPIO_u8ActivatePullUp(uint8 Copy_u8PortID, uint8 Copy_u8PinID)
{
    Std_ReturnType Loc_u8FuncStatus = E_NOT_OK;
    if((Copy_u8PortID <= GPIO_PORTC) && (Copy_u8PinID <= GPIO_PIN15))
    {
        switch(Copy_u8PortID)
        {
            case GPIO_PORTA:
            {
                SET_BIT(GPIOA_ODR, Copy_u8PinID);
                Loc_u8FuncStatus = E_OK;
                break;
            }
            case GPIO_PORTB:
            {
                SET_BIT(GPIOB_ODR, Copy_u8PinID);
                Loc_u8FuncStatus = E_OK;
                break;
            }
            case GPIO_PORTC:
            {
                SET_BIT(GPIOC_ODR, Copy_u8PinID);
                Loc_u8FuncStatus = E_OK;
                break;
            }
            default:
            {
                Loc_u8FuncStatus = E_NOT_OK;
                break;
            }
        }
    }
    else
    {
        Loc_u8FuncStatus = E_NOT_OK;
    }
    return Loc_u8FuncStatus;
}
