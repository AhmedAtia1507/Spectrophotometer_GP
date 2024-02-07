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
#include "BIT_MATH.h"
#include "Std_Types.h"

#include "GPIO_Private.h"
#include "GPIO_Interface.h"
#include "GPIO_Config.h"

/**
 * @brief: Function to set the mode of the GPIO Pin
 * 
 * @param Copy_uint8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_uint8PinID: ID of the pin (0 --> 15)
 * @param Copy_uint8PinMode: Mode of the Pin 
 * @return Std_ReturnType
 * @retval E_OK: Pin Mode has been set successfully
 * @retval E_NOT_OK: Pin mode has not been set 
 */
Std_ReturnType MGPIO_SetPinMode(uint8 Copy_uint8PortID, uint8 Copy_uint8PinID, uint8 Copy_uint8PinMode)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    switch(Copy_uint8PortID)
    {
        case MGPIO_PORTA:
        {
            if(Copy_uint8PinID <= MGPIO_PIN7)
            {
                MGPIOA_CRL &= ~((0b1111) << (4 * Copy_uint8PinID));
                MGPIOA_CRL |= ((Copy_uint8PinMode) << (4 * Copy_uint8PinID));
                Loc_uint8FuncStatus = E_OK;
            }
            else if(Copy_uint8PinID <= MGPIO_PIN15)
            {
                MGPIOA_CRH &= ~((0b1111) << (4 * (Copy_uint8PinID - 8)));
                MGPIOA_CRH |= ((Copy_uint8PinMode) << (4 * (Copy_uint8PinID - 8)));
                Loc_uint8FuncStatus = E_OK;
            }
            break;
        }
        case MGPIO_PORTB:
        {
            if(Copy_uint8PinID <= MGPIO_PIN7)
            {
                MGPIOB_CRL &= ~((0b1111) << (4 * Copy_uint8PinID));
                MGPIOB_CRL |= ((Copy_uint8PinMode) << (4 * Copy_uint8PinID));
                Loc_uint8FuncStatus = E_OK;
            }
            else if(Copy_uint8PinID <= MGPIO_PIN15)
            {
                MGPIOB_CRH &= ~((0b1111) << (4 * (Copy_uint8PinID - 8)));
                MGPIOB_CRH |= ((Copy_uint8PinMode) << (4 * (Copy_uint8PinID - 8)));
                Loc_uint8FuncStatus = E_OK;
            }
            break;
        }
        case MGPIO_PORTC:
        {
            if(Copy_uint8PinID <= MGPIO_PIN7)
            {
                MGPIOC_CRL &= ~((0b1111) << (4 * Copy_uint8PinID));
                MGPIOC_CRL |= ((Copy_uint8PinMode) << (4 * Copy_uint8PinID));
                Loc_uint8FuncStatus = E_OK;
            }
            else if(Copy_uint8PinID <= MGPIO_PIN15)
            {

                MGPIOC_CRH &= ~((0b1111) << (4 * (Copy_uint8PinID - 8)));
                MGPIOC_CRH |= ((Copy_uint8PinMode) << (4 * (Copy_uint8PinID - 8)));
                Loc_uint8FuncStatus = E_OK;
            }
            break;
        }
        default:
        {
            Loc_uint8FuncStatus = E_NOT_OK;
            break;
        }
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to set the value of the output GPIO Pin
 * 
 * @param Copy_uint8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_uint8PinID: ID of the pin (0 --> 15)
 * @param Copy_uint8PinValue: Value to be set (High or Low) 
 * @return Std_ReturnType
 * @retval E_OK: Pin Value has been set successfully
 * @retval E_NOT_OK: Pin Value has not been set
 */
Std_ReturnType MGPIO_SetPinValue(uint8 Copy_uint8PortID, uint8 Copy_uint8PinID, uint8 Copy_uint8PinValue)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if((Copy_uint8PortID <= MGPIO_PORTC) && (Copy_uint8PinID <= MGPIO_PIN15))
    {
        switch (Copy_uint8PortID)
        {
            case MGPIO_PORTA:
            {
                if(Copy_uint8PinValue == MGPIO_HIGH)
                {
                    SET_BIT(MGPIOA_ODR, Copy_uint8PinID);
                    Loc_uint8FuncStatus = E_OK;
                }
                else if(Copy_uint8PinValue == MGPIO_LOW)
                {
                    CLR_BIT(MGPIOA_ODR, Copy_uint8PinID);
                    Loc_uint8FuncStatus = E_OK;
                }
                else
                {
                    Loc_uint8FuncStatus = E_NOT_OK;
                }
                break;
            }
            case MGPIO_PORTB:
            {
                if(Copy_uint8PinValue == MGPIO_HIGH)
                {
                    SET_BIT(MGPIOB_ODR, Copy_uint8PinID);
                    Loc_uint8FuncStatus = E_OK;
                }
                else if(Copy_uint8PinValue == MGPIO_LOW)
                {
                    CLR_BIT(MGPIOB_ODR, Copy_uint8PinID);
                    Loc_uint8FuncStatus = E_OK;
                }
                else
                {
                    Loc_uint8FuncStatus = E_NOT_OK;
                }
                break;
            }
            case MGPIO_PORTC:
            {
                if(Copy_uint8PinValue == MGPIO_HIGH)
                {
                    SET_BIT(MGPIOC_ODR, Copy_uint8PinID);
                    Loc_uint8FuncStatus = E_OK;
                }
                else if(Copy_uint8PinValue == MGPIO_LOW)
                {
                    CLR_BIT(MGPIOC_ODR, Copy_uint8PinID);
                    Loc_uint8FuncStatus = E_OK;
                }
                else
                {
                    Loc_uint8FuncStatus = E_NOT_OK;
                }
                break;
            }
            default:
            {
                Loc_uint8FuncStatus = E_NOT_OK;
                break;
            }
        }
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to get the value of the input GPIO Pin
 * 
 * @param Copy_uint8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_uint8PinID: ID of the pin (0 --> 15)
 * @param Copy_uint8PinValue: Value of input pin (High or Low) 
 * @return Std_ReturnType
 * @retval E_OK: Pin Value has been read successfully
 * @retval E_NOT_OK: Pin Value has not been read
 */
Std_ReturnType MGPIO_GetPinValue(uint8 Copy_uint8PortID, uint8 Copy_uint8PinID, uint8* P_uint8PinValue)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    if((P_uint8PinValue != NULL_PTR) && (Copy_uint8PortID <= MGPIO_PORTC) && (Copy_uint8PinID <= MGPIO_PIN15))
    {
        switch(Copy_uint8PortID)
        {
            case MGPIO_PORTA:
            {
                *P_uint8PinValue = GET_BIT(MGPIOA_IDR, Copy_uint8PinID);
                Loc_uint8FuncStatus = E_OK;
                break;
            }
            case MGPIO_PORTB:
            {
                *P_uint8PinValue = GET_BIT(MGPIOB_IDR, Copy_uint8PinID);
                Loc_uint8FuncStatus = E_OK;
                break;
            }
            case MGPIO_PORTC:
            {
                *P_uint8PinValue = GET_BIT(MGPIOC_IDR, Copy_uint8PinID);
                Loc_uint8FuncStatus = E_OK;
                break;
            }
            default:
            {
                Loc_uint8FuncStatus = E_NOT_OK;
                break;
            }
        }
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to activate the internal pull-up resistor
 * 
 * @param Copy_uint8PortID: ID of the port containing the pin (A, B, C)
 * @param Copy_uint8PinID: ID of the pin (0 --> 15)
 * @return Std_ReturnType
 * @retval E_OK: Pull-up has been activated successfully
 * @retval E_NOT_OK: Pull-up has not been activated 
 */
Std_ReturnType MGPIO_ActivatePullUp(uint8 Copy_uint8PortID, uint8 Copy_uint8PinID)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if((Copy_uint8PortID <= MGPIO_PORTC) && (Copy_uint8PinID <= MGPIO_PIN15))
    {
        switch(Copy_uint8PortID)
        {
            case MGPIO_PORTA:
            {
                SET_BIT(MGPIOA_ODR, Copy_uint8PinID);
                Loc_uint8FuncStatus = E_OK;
                break;
            }
            case MGPIO_PORTB:
            {
                SET_BIT(MGPIOB_ODR, Copy_uint8PinID);
                Loc_uint8FuncStatus = E_OK;
                break;
            }
            case MGPIO_PORTC:
            {
                SET_BIT(MGPIOC_ODR, Copy_uint8PinID);
                Loc_uint8FuncStatus = E_OK;
                break;
            }
            default:
            {
                Loc_uint8FuncStatus = E_NOT_OK;
                break;
            }
        }
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}