/**
 * @file ADC_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * 
 * @version 1.0
 * @date 2023-10-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/Std_Types.h"

#include "ADC_Private.h"
#include "ADC_Interface.h"
#include "ADC_Config.h"

/**
 * @brief: Array of two pointers to structures that represents the registers of ADC 1 and 2 peripherals
 *  
 */
static volatile MADC_Typedef_t* (ADC[2]) = {ADC1, ADC2};
/**
 * @brief: Array of two pointers to functions that are executed when ADCx Conversion Complete Interrupt Occurs
 * 
 */
static volatile ptr_to_func_t (glbl_EOCCallbackFunc[2]) = {NULL_PTR};

/**
 * @brief: Function to initialize the specified ADC Peripheral (ADC1 or ADC2)
 * 
 * @param Copy_uint32ADCSelect:                     ADC to be initialized
 *  
 * @return Std_ReturnType
 * @retval E_OK:                                    ADC successfully initialized
 * @retval E_NOT_OK:                                ADC not initialized 
 */
Std_ReturnType MADC_Init                            (ADC_Select_t Copy_uint32ADCSelect)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    
    /************************************************************************************************* 
        1) Set ADC Operation Mode
    *************************************************************************************************/
    ADC[Copy_uint32ADCSelect] -> CR1 &= ~((0b1111) << (MADC_CR1_DUALMOD_START_BIT));
    ADC[Copy_uint32ADCSelect] -> CR1 |= ((MADC_OPERATION_MODE) << (MADC_CR1_DUALMOD_START_BIT));

    /************************************************************************************************* 
        2) Set End of conversion interrupt status
    *************************************************************************************************/
    #if MADC_EOC_INTERRUPT_STATUS == MADC_EOC_INTERRUPT_ENABLED
        SET_BIT((ADC[Copy_uint32ADCSelect] -> CR1), MADC_CR1_EOCIE_BIT);
    #elif MADC_EOC_INTERRUPT_STATUS == MADC_EOC_INTERRUPT_DISABLED
        CLR_BIT((ADC[Copy_uint32ADCSelect] -> CR1), MADC_CR1_EOCIE_BIT);
    #else
        #error "ADC End of Conversion Interrupt Status is not specified"
    #endif /*MADC_EOC_INTERRUPT_STATUS*/

    /************************************************************************************************* 
        3) Disable ADC Continuous Conversion
    *************************************************************************************************/
    CLR_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_CONT_BIT);

    /************************************************************************************************* 
        4) Set ADC Data Alignment (Right Adjust or Left Adjust)
    *************************************************************************************************/
    #if MADC_DATA_BITS_ADJUST_SELECT == MADC_RIGHT_ADJUST_DATA_BITS
        /*
            Right Align: means that the 12-bits data's least significant bit is at bit 0 in the
                            ADC data register
        */
        CLR_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_ALIGN_BIT);
    #elif MADC_DATA_BITS_ADJUST_SELECT == MADC_LEFT_ADJUST_DATA_BITS
        /*
            Left Align: means that the 12-bits data's Most significant bit is at bit 15 in the
                            ADC data register
        */
        SET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_ALIGN_BIT);
    #else
        #error "ADC Data Bits Adjustment is not specified"
    #endif /*MADC_DATA_BITS_ADJUST_SELECT*/

    /************************************************************************************************* 
        5) Configure External Trigger Status
    *************************************************************************************************/
    #if MADC_EXTERNAL_TRIGGER_STATUS == MADC_EXTERNAL_TRIGGER_ENABLED
        SET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_EXTTRIG_BIT);
        ADC[Copy_uint32ADCSelect] -> CR2 &= ~((0b111) << (MADC_CR2_EXTSEL_START_BIT));
        ADC[Copy_uint32ADCSelect] -> CR2 |= ((MADC_EXTERNAL_TRIGGER_SELECT) << (MADC_CR2_EXTSEL_START_BIT));
    #elif MADC_EXTERNAL_TRIGGER_STATUS == MADC_EXTERNAL_TRIGGER_DISABLED
        CLR_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_EXTTRIG_BIT);
    #else
    #endif /*MADC_EXTERNAL_TRIGGER_STATUS*/

    /************************************************************************************************* 
        6) Enable ADC Peripheral
    *************************************************************************************************/
    SET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_ADON_BIT);

    /************************************************************************************************* 
        7) Reset ADC Calibration
    *************************************************************************************************/
    SET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_RSTCAL_BIT);
    while(GET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_RSTCAL_BIT));

    /************************************************************************************************* 
        8) Start ADC Calibration
    *************************************************************************************************/
    SET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_CAL_BIT);
    while(GET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_CAL_BIT));
    
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to trigger Specified ADC Conversion
 * 
 * @param Copy_uint32ADCSelect:                     ADC to be triggered 
 * @param Copy_uint32ChannelSelect:                 ADC Channel to read analog signal from
 *  
 * @return Std_ReturnType
 * @retval E_OK:                                    ADC Conversion Triggered
 * @retval E_NOT_OK:                                ADC Conversion not triggered 
 */
Std_ReturnType MADC_StartConversion                 (ADC_Select_t Copy_uint32ADCSelect, ADC_Channel_t Copy_uint32ChannelSelect)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    /************************************************************************************************* 
        1) Select Channel to read analog signal from
    *************************************************************************************************/
    ADC[Copy_uint32ADCSelect] -> SQR1 &= ~((0b1111) << 20);
    ADC[Copy_uint32ADCSelect] -> SQR3 &= ~((0b11111) << 0);
    ADC[Copy_uint32ADCSelect] -> SQR3 |= ((Copy_uint32ChannelSelect) << 0);
    
    /************************************************************************************************* 
        2) Trigger ADC Conversion
    *************************************************************************************************/
    SET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_SWSTART_BIT);
	
    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to receive converted data from the specified ADC asynchronously
 * 
 * @param Copy_uint32ADCSelect:                     ADC from which to read the converted data
 * @param P_uint16ConvertedData:                    Pointer to store the received converted data
 *   
 * @return Std_ReturnType
 * @retval E_OK:                                    Data Successfully read
 * @retval E_NOT_OK:                                Data not read 
 */
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
/**
 * @brief: Function to perform ADC conversion on a specified channel and retrieve the converted data
 * 
 * @param Copy_uint32ADCSelect:                     ADC to be used for conversion 
 * @param Copy_uint32ChannelSelect:                 ADC Channel to be converted 
 * @param P_uint16ConvertedData:                    Pointer to store the converted data
 *  
 * @return Std_ReturnType
 * @retval E_OK:                                    Conversion completed successfully and data retrieved
 * @retval E_NOT_OK:                                Conversion failed  
 */
Std_ReturnType MADC_Conversion                      (ADC_Select_t Copy_uint32ADCSelect, ADC_Channel_t Copy_uint32ChannelSelect, uint16* P_uint16ConvertedData)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if(P_uint16ConvertedData != NULL_PTR)
    {
        /************************************************************************************************* 
            1) Select Channel to read analog signal from
        *************************************************************************************************/
        ADC[Copy_uint32ADCSelect] -> SQR1 &= ~((0b1111) << 20);
        ADC[Copy_uint32ADCSelect] -> SQR3 &= ~((0b11111) << 0);
        ADC[Copy_uint32ADCSelect] -> SQR3 = (Copy_uint32ChannelSelect) << 0;

        /************************************************************************************************* 
            2) Trigger ADC Conversion
        *************************************************************************************************/
        SET_BIT((ADC[Copy_uint32ADCSelect] -> CR2), MADC_CR2_SWSTART_BIT);

        /************************************************************************************************* 
            3) Wait for ADC conversion to complete
        *************************************************************************************************/
        while(!(GET_BIT((ADC[Copy_uint32ADCSelect] -> SR), MADC_SR_EOC_BIT)));

        /************************************************************************************************* 
            4) Read Converted Data
        *************************************************************************************************/
        *P_uint16ConvertedData = ADC[Copy_uint32ADCSelect] -> DR;
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to set the function to be executed when specified ADC conversion is complete 
 * 
 * @param Copy_uint32ADCSelect:                     ADC for which interrupt function is set
 * @param P_funcCallback:                           Pointer to the interrupt function
 * 
 * @return Std_ReturnType
 * @retval E_OK:                                    Interrupt function successfully set
 * @retval E_NOT_OK:                                Interrupt function not set
 */
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

/**
 * @brief: Function that represents the Interrupt Service Routine for ADC 1 and 2 Conversion Complete Interrupts
 * 
 */
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
