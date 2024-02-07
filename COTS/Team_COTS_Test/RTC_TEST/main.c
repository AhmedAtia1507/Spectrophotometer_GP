#include "BIT_MATH.h"
#include "Std_Types.h"

#include "RCC_Interface.h"
#include "RTC_Interface.h"

#include "GPIO_Interface.h"
#include "NVIC_Interface.h"

#include "STK_Interface.h"
#include "LCD_Interface.h"

void LCD_WRITE_DATE_TIME(Sdate_t* date, Stime_t* time)
{
	if((date != NULL_PTR) && (time != NULL_PTR))
	{
		LCD_WriteString("Date: ");
		LCD_WriteIntegerValue((uint32)(date -> m_days));
		LCD_WriteChar4Bit('/');
		LCD_WriteIntegerValue((uint32)(date -> m_months));
		LCD_WriteChar4Bit('/');
		LCD_WriteIntegerValue((uint32)(date -> m_years));
		
		LCD_SetCursorPosition(LCD_SECOND_ROW,0);
		LCD_WriteString("Time: ");
		LCD_WriteIntegerValue((uint32)(time -> m_hours));
		LCD_WriteChar4Bit(':');
		LCD_WriteIntegerValue((uint32)(time -> m_minutes));
		LCD_WriteChar4Bit(':');
		LCD_WriteIntegerValue((uint32)(time -> m_seconds));
		
	}
}
Sdate_t date;
Stime_t time;
void ISR(void)
{
	static uint8 Loc_uint8NoOfSeconds = 0;
	if(Loc_uint8NoOfSeconds == 2)
	{
		LCD_ClearDisplay();
		MRTC_GetDateAndTime(&date, &time);
		LCD_WRITE_DATE_TIME(&date, &time);
		Loc_uint8NoOfSeconds = 0;
	}
	else
	{
		Loc_uint8NoOfSeconds++;
	}
}

int main(void)
{
	MRCC_InitClock();
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPA_EN);
	MRCC_EnablePeripheralClock(MRCC_APB2, MRCC_APB2_IOPB_EN);
	
	MSTK_uint8Init();
	LCD_Init();
	
	MNVIC_EnableInterrupt(MNVIC_RTC);
    MRTC_SetSecondIntCallbackFunc(ISR);
	MRTC_Init();
	MRTC_GetDateAndTime(&date, &time);
	LCD_WRITE_DATE_TIME(&date, &time);
    while(1)
    {
        
    }
	return 0;
}

