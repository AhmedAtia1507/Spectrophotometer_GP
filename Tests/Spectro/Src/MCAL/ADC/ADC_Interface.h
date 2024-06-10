/**
 * @file ADC_Interface.h
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _ADC_INTERFACE_H_
#define _ADC_INTERFACE_H_

typedef enum ADC_Choice
{
    MADC1,
    MADC2
}ADC_Select_t;

typedef enum ADC_Channel_Choice
{
	MADC_Channel_0,
    MADC_Channel_1,
    MADC_Channel_2,
    MADC_Channel_3,
    MADC_Channel_4,
    MADC_Channel_5,
    MADC_Channel_6,
    MADC_Channel_7,
    MADC_Channel_8,
    MADC_Channel_9
}ADC_Channel_t;

#define MADC_CHANNEL_0_PORT_ID                      MGPIO_PORTA
#define MADC_CHANNEL_0_PIN_ID                       MGPIO_PIN0

#define MADC_CHANNEL_1_PORT_ID                      MGPIO_PORTA
#define MADC_CHANNEL_1_PIN_ID                       MGPIO_PIN1

#define MADC_CHANNEL_2_PORT_ID                      MGPIO_PORTA
#define MADC_CHANNEL_2_PIN_ID                       MGPIO_PIN2

#define MADC_CHANNEL_3_PORT_ID                      MGPIO_PORTA
#define MADC_CHANNEL_3_PIN_ID                       MGPIO_PIN3

#define MADC_CHANNEL_4_PORT_ID                      MGPIO_PORTA
#define MADC_CHANNEL_4_PIN_ID                       MGPIO_PIN4

#define MADC_CHANNEL_5_PORT_ID                      MGPIO_PORTA
#define MADC_CHANNEL_5_PIN_ID                       MGPIO_PIN5

#define MADC_CHANNEL_6_PORT_ID                      MGPIO_PORTA
#define MADC_CHANNEL_6_PIN_ID                       MGPIO_PIN6

#define MADC_CHANNEL_7_PORT_ID                      MGPIO_PORTA
#define MADC_CHANNEL_7_PIN_ID                       MGPIO_PIN7

#define MADC_CHANNEL_8_PORT_ID                      MGPIO_PORTB
#define MADC_CHANNEL_8_PIN_ID                       MGPIO_PIN0

#define MADC_CHANNEL_9_PORT_ID                      MGPIO_PORTB
#define MADC_CHANNEL_9_PIN_ID                       MGPIO_PIN1

typedef void(*ptr_to_func_t)(void);

Std_ReturnType MADC_Init                            (ADC_Select_t Copy_uint32ADCSelect);
Std_ReturnType MADC_StartConversion                 (ADC_Select_t Copy_uint32ADCSelect, ADC_Channel_t Copy_uint32ChannelSelect);
Std_ReturnType MADC_RxConvertedDataAsynchronous     (ADC_Select_t Copy_uint32ADCSelect, uint16* P_uint16ConvertedData);
Std_ReturnType MADC_Conversion                      (ADC_Select_t Copy_uint32ADCSelect, ADC_Channel_t Copy_uint32ChannelSelect, uint16* P_uint16ConvertedData);
Std_ReturnType MADC_SetConversionCompleteCallback   (ADC_Select_t Copy_uint32ADCSelect, ptr_to_func_t P_funcCallback);            
#endif /*_ADC_INTERFACE_H_*/