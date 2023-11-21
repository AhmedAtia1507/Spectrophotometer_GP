/**
 * @file RCC_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief: C file to implement functions used to configure RCC Peripheral
 *  
 * @version 1.0
 * @date 2023-08-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "BIT_MATH.h"
#include "Std_Types.h"

#include "RCC_Private.h"
#include "RCC_Config.h"
#include "RCC_Interface.h"


/**
 * @brief: Function to initialize the clock of the micro controller whether it is:
 *         1) HSI: High Speed Internal clock (RC Circuit) (freq. 8MHz)
 *         2) HSE: High Speed External Clock -(RC Circuit) --> (Freq. 4 --> 25 MHz)
 *                                           -(Crystal Oscillator) (Freq. 4 --> 16 MHz)
 *         3) PLL: Phase-Locked Loop Clock (Output frequency = input frequency * number) 
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Clock Initialized Successfully
 * @retval E_NOT_OK:    Clock is not initialized Successfully
 */
Std_ReturnType MRCC_InitClock(void)
{
    #if MRCC_CLOCK_SOURCE == MRCC_HSI_CLOCK
        //Enable High-Speed Internal Clock
        SET_BIT(RCC_CR, RCC_CR_HSION);
        //Wait until HSI Clock is ready
        while(GET_BIT(RCC_CR, RCC_CR_HSIRDY) == 0);

        //Set System Clock Source to be HSI Clock
        CLR_BIT(RCC_CFGR, RCC_CFGR_SW_START);
        CLR_BIT(RCC_CFGR, (RCC_CFGR_SW_START + 1));

    #elif MRCC_CLOCK_SOURCE == MRCC_HSE_CLOCK
        #if (MRCC_HSE_CLOCK_FREQ <= 16000000)
            #if MRCC_HSE_CLOCK_SOURCE == MRCC_HSE_CRYSTAL_CLOCK
                /*Bypass is not enabled*/
                CLR_BIT(RCC_CR, RCC_CR_HSEBYP);
            #elif MRCC_HSE_CLOCK_SOURCE == MRCC_HSE_RC_CLOCK
                SET_BIT(RCC_CR, RCC_CR_HSEBYP);
            #else
                #error "External Clock Source is not specified correctly"
            #endif

            //Enable High-Speed External Clock
            SET_BIT(RCC_CR, RCC_CR_HSEON);
            //Wait until HSE Clock is ready
            while(GET_BIT(RCC_CR, RCC_CR_HSERDY) == 0);

            //Set System Clock Source to be HSE Clock
            SET_BIT(RCC_CFGR, RCC_CFGR_SW_START);
            CLR_BIT(RCC_CFGR, (RCC_CFGR_SW_START + 1));

        #else
            #error "HSE Clock Frequency Exceeded Max. Frequency"
        #endif

    #elif MRCC_CLOCK_SOURCE == MRCC_PLL_CLOCK
        #if MRCC_PLL_CLOCK_INPUT == MRCC_HSE_CLOCK
            /*Set PLL Input Clock Source to be HSE Clock*/
            SET_BIT(RCC_CFGR, RCC_CFGR_PLLSRC);
            /*HSE Clock is not divided by 2*/
            CLR_BIT(RCC_CFGR, RCC_CFGR_PLLXTPRE);

            #if (RCC_PLL_MULTIPLIER <= 16) && (RCC_PLL_MULTIPLIER >= 0)
                if((RCC_PLL_HSE_CLOCK_FREQ * RCC_PLL_MULTIPLIER) <= MRCC_MAX_CLOCK_FREQ)
                {
                    RCC_CFGR &= ~((0b1111) << RCC_CFGR_PLLMUL_START);
                    RCC_CFGR |=  (((uint32)(RCC_PLL_MULTIPLIER - 2)) << RCC_CFGR_PLLMUL_START);

                    //Enable Phase-locked loop Clock
                    SET_BIT(RCC_CR, RCC_CR_PLLON);
                    //Wait until PLL Clock is ready
                    while(GET_BIT(RCC_CR, RCC_CR_PLLRDY) == 0);
                }
            #else
                #error "The multiplier value for PLL is not valid"
            #endif
        #elif MRCC_PLL_CLOCK_INPUT == MRCC_HSE_CLOCK_DIV_2
            /*Set PLL Input Clock Source to be HSE Clock*/
            SET_BIT(RCC_CFGR, RCC_CFGR_PLLSRC);
            /*HSE Clock is divided by 2*/
            SET_BIT(RCC_CFGR, RCC_CFGR_PLLXTPRE);

            #if (RCC_PLL_MULTIPLIER <= 16) && (RCC_PLL_MULTIPLIER >= 0)
                if(((RCC_PLL_HSE_CLOCK_FREQ / 2) * RCC_PLL_MULTIPLIER) <= MRCC_MAX_CLOCK_FREQ)
                {
                    RCC_CFGR &= ~((0b1111) << RCC_CFGR_PLLMUL_START);
                    RCC_CFGR |=  (((uint32)(RCC_PLL_MULTIPLIER - 2)) << RCC_CFGR_PLLMUL_START);

                    //Enable Phase-locked loop Clock
                    SET_BIT(RCC_CR, RCC_CR_PLLON);
                    //Wait until PLL Clock is ready
                    while(GET_BIT(RCC_CR, RCC_CR_PLLRDY) == 0);
                }
            #else
                #error "The multiplier value for PLL is not valid"
            #endif
        #elif MRCC_PLL_CLOCK_INPUT == MRCC_HSI_CLOCK_DIV_2
            /*Set PLL Input Clock Source to be HSI Clock Divided by 2*/
            CLR_BIT(RCC_CFGR, RCC_CFGR_PLLSRC);
        #else
            #error "PLL input clock is not specified correctly"
        #endif

        //Set System Clock Source to be PLL Clock
        CLR_BIT(RCC_CFGR, RCC_CFGR_SW_START);
        SET_BIT(RCC_CFGR, (RCC_CFGR_SW_START + 1));

    #else
        #error "Clock Source is not Specified Correctly"
    #endif
    //Set Prescalars for AHB, APB1 and APB2 Clocks
    RCC_CFGR &= ~(((uint32)0b1111) << (RCC_CFGR_HPRE_START));
    RCC_CFGR |= (((uint32)(MRCC_AHB_PRESCALAR)) << (RCC_CFGR_HPRE_START));
    
    RCC_CFGR &= ~(((uint32)0b111) << (RCC_CFGR_PPRE1_START));
    RCC_CFGR |= (((uint32)(MRCC_AHB_PRESCALAR)) << (RCC_CFGR_PPRE1_START));
    
    RCC_CFGR &= ~(((uint32)0b111) << (RCC_CFGR_PPRE2_START));
    RCC_CFGR |= (((uint32)(MRCC_AHB_PRESCALAR)) << (RCC_CFGR_PPRE2_START));

    return E_OK;
}
/**
 * @brief: Function to enable clock for any peripheral except RCC itself and 
 *          Core Peripherals
 * 
 * @param Copy_uint8BusID: ID of the bus the peripheral is connected to
 * @param Copy_uint8Peripheral: The peripheral whose clock is to be enabled
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Peripheral Clock Enabled Successfully
 * @retval E_NOT_OK:    Peripheral Clock is not Enabled Successfully 
 */
Std_ReturnType MRCC_EnablePeripheralClock(uint8 Copy_uint8BusID, uint8 Copy_uint8Peripheral)
{
    Std_ReturnType Loc_uint8ErrorCheck = E_NOT_OK;
    switch(Copy_uint8BusID)
    {
        case MRCC_AHB:
        {
            SET_BIT(MRCC_AHBENR, Copy_uint8Peripheral);
            Loc_uint8ErrorCheck = E_OK;
            break;
        }
        case MRCC_APB1:
        {
            SET_BIT(MRCC_APB1ENR, Copy_uint8Peripheral);
            Loc_uint8ErrorCheck = E_OK;
            break;
        }
        case MRCC_APB2:
        {
            SET_BIT(MRCC_APB2ENR, Copy_uint8Peripheral);
            Loc_uint8ErrorCheck = E_OK;
            break;
        }
        default:
        {
            Loc_uint8ErrorCheck = E_NOT_OK;
            break;
        }
    }
    return Loc_uint8ErrorCheck;
}
/**
 * @brief: Function to disable clock for any peripheral except RCC itself and 
 *          Core Peripherals
 * 
 * @param Copy_uint8BusID: ID of the bus the peripheral is connected to
 * @param Copy_uint8Peripheral: The peripheral whose clock is to be disabled
 * 
 * @return Std_ReturnType
 * @retval E_OK:        Peripheral Clock Disabled Successfully
 * @retval E_NOT_OK:    Peripheral Clock is not Disabled Successfully 
 */
Std_ReturnType MRCC_DisablePeripheralClock(uint8 Copy_uint8BusID, uint8 Copy_uint8Peripheral)
{
    Std_ReturnType Loc_uint8ErrorCheck = E_NOT_OK;
    switch(Copy_uint8BusID)
    {
        case MRCC_AHB:
        {
            CLR_BIT(MRCC_AHBENR, Copy_uint8Peripheral);
            Loc_uint8ErrorCheck = E_OK;
            break;
        }
        case MRCC_APB1:
        {
            CLR_BIT(MRCC_APB1ENR, Copy_uint8Peripheral);
            Loc_uint8ErrorCheck = E_OK;
            break;
        }
        case MRCC_APB2:
        {
            CLR_BIT(MRCC_APB2ENR, Copy_uint8Peripheral);
            Loc_uint8ErrorCheck = E_OK;
            break;
        }
        default:
        {
            Loc_uint8ErrorCheck = E_NOT_OK;
            break;
        }
    }
    return Loc_uint8ErrorCheck;
}