/**
 * @file ADC_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2024-01-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "BIT_MATH.h"
#include "Std_Types.h"

#include "ADC_Private.h"
#include "ADC_Interface.h"
#include "ADC_Config.h"

static volatile MADC_Typedef_t* (ADC[2]) = {ADC1, ADC2};
static volatile ptr_to_func_t (glbl_EOCCallbackFunc[2]) = {NULL_PTR};

Std_ReturnType MADC_Init                            (ADC_Select_t Copy_uint32ADCSelect)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    
    ADC[Copy_uint32ADCSelect] -> CR1 &= ~((0b1111) << (MADC_CR1_DUALMOD_START_BIT));
    ADC[Copy_uint32ADCSelect] -> CR1 |= ((MADC_OPERATION_MODE) << (MADC_CR1_DUALMOD_START_BIT));

    #if MADC_EOC_INTERRUPT_STATUS == MADC_EOC_INTERRUPT_ENABLED
        SET_BIT((ADC[Copy_uint32ADCSelect] -> CR1), MADC_CR1_EOCIE_BIT);
    #elif MADC_EOC_INTERRUPT_STATUS == MADC_EOC_INTERRUPT_DISABLED
        CLR_BIT((ADC[Copy_uint32ADCSelect] -> CR1), MADC_CR1_EOCIE_BIT);
    #else
        #error "ADC End of Conversion Interrupt Status is not specified"
    #endif /*MADC_EOC_INTERRUPT_STATUS*/

    CLR_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_CONT_BIT);

    #if MADC_DATA_BITS_ADJUST_SELECT == MADC_RIGHT_ADJUST_DATA_BITS
        CLR_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_ALIGN_BIT);
    #elif MADC_DATA_BITS_ADJUST_SELECT == MADC_LEFT_ADJUST_DATA_BITS
        SET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_ALIGN_BIT);
    #else
        #error "ADC Data Bits Adjustment is not specified"
    #endif /*MADC_DATA_BITS_ADJUST_SELECT*/

    #if MADC_EXTERNAL_TRIGGER_STATUS == MADC_EXTERNAL_TRIGGER_ENABLED
        SET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_EXTTRIG_BIT);
        ADC[Copy_uint32ADCSelect] -> CR2 &= ~((0b111) << (MADC_CR2_EXTSEL_START_BIT));
        ADC[Copy_uint32ADCSelect] -> CR2 |= ((MADC_EXTERNAL_TRIGGER_SELECT) << (MADC_CR2_EXTSEL_START_BIT));
    #elif MADC_EXTERNAL_TRIGGER_STATUS == MADC_EXTERNAL_TRIGGER_DISABLED
        CLR_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_EXTTRIG_BIT);
    #else
    #endif /*MADC_EXTERNAL_TRIGGER_STATUS*/

    SET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_ADON_BIT);

    SET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_RSTCAL_BIT);
    while(GET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_RSTCAL_BIT));

    SET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_CAL_BIT);
    while(GET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_CAL_BIT));
    
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
Std_ReturnType MADC_StartConversion                 (ADC_Select_t Copy_uint32ADCSelect, ADC_Channel_t Copy_uint32ChannelSelect)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    ADC[Copy_uint32ADCSelect] -> SQR1 &= ~((0b1111) << 20);
    ADC[Copy_uint32ADCSelect] -> SQR3 &= ~((0b11111) << 0);
    ADC[Copy_uint32ADCSelect] -> SQR3 |= ((Copy_uint32ChannelSelect) << 0);
    
    SET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_SWSTART_BIT);
	
    //while(!(GET_BIT((ADC[Copy_uint32ADCSelect] -> SR), MADC_SR_STRT_BIT)));
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
Std_ReturnType MADC_RxConvertedDataAsynchronous     (ADC_Select_t Copy_uint32ADCSelect, uint16* P_uint16ConvertedData)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_uint16ConvertedData != NULL_PTR)
    {
        *P_uint16ConvertedData = ADC[Copy_uint32ADCSelect] -> DR;
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
Std_ReturnType MADC_Conversion                      (ADC_Select_t Copy_uint32ADCSelect, ADC_Channel_t Copy_uint32ChannelSelect, uint16* P_uint16ConvertedData)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_uint16ConvertedData != NULL_PTR)
    {
        ADC[Copy_uint32ADCSelect] -> SQR1 &= ~((0b1111) << 20);
        ADC[Copy_uint32ADCSelect] -> SQR3 &= ~((0b11111) << 0);
        ADC[Copy_uint32ADCSelect] -> SQR3 = (Copy_uint32ChannelSelect) << 0;

        SET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_SWSTART_BIT);

        while(!(GET_BIT((ADC[Copy_uint32ADCSelect] -> SR), MADC_SR_EOC_BIT)));

        *P_uint16ConvertedData = ADC[Copy_uint32ADCSelect] -> DR;
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
Std_ReturnType MADC_SetConversionCompleteCallback   (ADC_Select_t Copy_uint32ADCSelect, ptr_to_func_t P_funcCallback)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_funcCallback != NULL_PTR)
    {
        glbl_EOCCallbackFunc[Copy_uint32ADCSelect] = P_funcCallback;
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}

void ADC1_2_IRQHandler(void)
{
    if(GET_BIT((ADC[0] -> SR), MADC_SR_EOC_BIT))
    {
        if(glbl_EOCCallbackFunc[0] != NULL_PTR)
        {
            (glbl_EOCCallbackFunc[0])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else if(GET_BIT((ADC[1] -> SR), MADC_SR_EOC_BIT))
    {
		if(glbl_EOCCallbackFunc[1] != NULL_PTR)
        {
            (glbl_EOCCallbackFunc[1])();
        }
        else
        {
            /*Do nothing*/
        }
    }
    else
    {
        /*Do nothing*/
    }
}
