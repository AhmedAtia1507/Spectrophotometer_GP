/**
 * @file main.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2024-02-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "BIT_MATH.h"
#include "Std_Types.h"

#include "RCC_Interface.h"
#include "GPIO_Interface.h"

#include "NVIC_Interface.h"
#include "STK_Interface.h"
#include "LCD_Interface.h"
#include "ADC_Interface.h"
#include "GPTMR_Interface.h"
#include "SCB_Interface.h"

void ADC_ISR(void)
{
    uint16 Loc_uint16ADCValue = 0;
    MADC_RxConvertedDataAsynchronous(MADC1, &Loc_uint16ADCValue);

    LCD_ClearDisplay();
    LCD_WriteString("ADC Value: ");
    LCD_WriteIntegerValue((uint32)(Loc_uint16ADCValue));
}

void TIM_ISR(void)
{
    MADC_StartConversion(MADC1, MADC_Channel_3);
}

int main(void)
{
    MRCC_InitClock();
		
		MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_ADC1_EN);
    MRCC_EnablePeripheralClock(MRCC_APB1, MRCC_APB1_TIM2_EN);
    MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);
    MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPB_EN);

    MSTK_uint8Init();

    LCD_Init();

    MNVIC_EnableInterrupt(MNVIC_ADC1_2);
    MNVIC_EnableInterrupt(MNVIC_TIM2);

	MSCB_SetPriorityGrouping(SCB_PRIORITY_GROUP_4_SUB_0);
	MNVIC_SetInterruptPriority(MNVIC_ADC1_2, 0, 0);
	MNVIC_SetInterruptPriority(MNVIC_TIM2, 1, 0);
    MGPTMR_Init(MGPTMR2);
	MGPTMR_SetTimerPeriod(MGPTMR2, 1000);
    MGPTMR_SetTimerUpdateCallbackFunc(MGPTMR2, TIM_ISR);
	
    MADC_SetConversionCompleteCallback(MADC1, ADC_ISR);
    MADC_Init(MADC1);

    MGPTMR_StartTimer(MGPTMR2);
    while(1)
    {

    }
    return 0;
}