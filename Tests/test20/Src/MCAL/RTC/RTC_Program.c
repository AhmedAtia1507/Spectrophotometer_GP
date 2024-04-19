/**
 * @file RTC_Program.c
 * @author Ahmed Atia Said (atiaa6501@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../../LIB/BIT_MATH/BIT_MATH.h"
#include "../../LIB/STD_TYPES/Std_Types.h"

#include "RTC_Private.h"
#include "RTC_Interface.h"
#include "RTC_Config.h"

#include <time.h>

static volatile Sdate_t glbl_SReferenceDate = {2024, 1, 25};
static volatile Stime_t glbl_SReferenceTime = {17,12,0};
static volatile uint32 glbl_uint32ReferenceSeconds = 0;
static volatile ptr_to_func_t glbl_PCallbackFunc = NULL_PTR;

Std_ReturnType MRTC_CalculateSeconds(Sdate_t* P_SDate, Stime_t* P_STime, uint32* P_uint32Seconds)
{
    struct tm time = {};
    
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if((P_SDate != NULL_PTR) && (P_STime != NULL_PTR) && (P_uint32Seconds != NULL_PTR))
    {
        struct tm Loc_SspecificTime = {0};
        Loc_SspecificTime.tm_year = (P_SDate -> m_years) - 1900; //year since 1900
        Loc_SspecificTime.tm_mon = (P_SDate -> m_months) - 1; //Month (0 ---> 11) (Jan = 0)
        Loc_SspecificTime.tm_mday = (P_SDate -> m_days); //Day (1 ---> 31)
        Loc_SspecificTime.tm_hour = (P_STime -> m_hours);
        Loc_SspecificTime.tm_min = (P_STime -> m_minutes);
        Loc_SspecificTime.tm_sec = (P_STime -> m_seconds);

        time_t Loc_SspecificTime_t = mktime(&Loc_SspecificTime);

        *P_uint32Seconds = (uint32)(difftime(Loc_SspecificTime_t, 0));

        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
Std_ReturnType MRTC_CalculateDateTime(uint32* P_uint32Seconds, Sdate_t* P_SDate, Stime_t* P_STime)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if((P_SDate != NULL_PTR) && (P_STime != NULL_PTR) && (P_uint32Seconds != NULL_PTR))
    {
        time_t Loc_tInputTime = (time_t)(*P_uint32Seconds);

        struct tm Loc_SspecificTime = {0};
        Loc_SspecificTime.tm_year = (glbl_SReferenceDate . m_years) - 1900; //year since 1900
        Loc_SspecificTime.tm_mon = (glbl_SReferenceDate . m_months) - 1; //Month (0 ---> 11) (Jan = 0)
        Loc_SspecificTime.tm_mday = (glbl_SReferenceDate . m_days); //Day (1 ---> 31)
        Loc_SspecificTime.tm_hour = (glbl_SReferenceTime . m_hours);
        Loc_SspecificTime.tm_min = (glbl_SReferenceTime . m_minutes);
        Loc_SspecificTime.tm_sec = (glbl_SReferenceTime . m_seconds);

        time_t Loc_SspecificTime_t = mktime(&Loc_SspecificTime);

        time_t Loc_tSumTime = Loc_tInputTime + Loc_SspecificTime_t;

        struct tm* Loc_PBrokenTime = localtime(&Loc_tSumTime);

        P_SDate -> m_years = (Loc_PBrokenTime -> tm_year) + 1900;
        P_SDate -> m_months = (Loc_PBrokenTime -> tm_mon) + 1;
        P_SDate -> m_days = (Loc_PBrokenTime -> tm_mday);
        P_STime -> m_hours = Loc_PBrokenTime -> tm_hour;
        P_STime -> m_minutes = Loc_PBrokenTime -> tm_min;
        P_STime ->m_seconds = Loc_PBrokenTime -> tm_sec;
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to initialize RTC Peripheral
 * 
 * @return Std_ReturnType
 * @retval E_OK: RTC is Successfully initialized
 * @retval E_NOT_OK: RTC is not initialized 
 */
Std_ReturnType MRTC_Init(void)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;

    //Enable Power Control Clock in order to access backup and RTC Registers
    SET_BIT(MRCC_APB1ENR_R, MRCC_APB1ENR_PWREN_BIT);
    //Enable access to backup and RTC Registers
    SET_BIT(MPWR_CR_R, MPWR_CR_DBP_BIT);


    #if MRTC_CLOCK_SOURCE == MRTC_LSE_CLOCK
        //Enable external 32KHz Oscillator
        SET_BIT(MRCC_BDCR_R, MRCC_BDCR_LSEON_BIT);
        //Wait until external 32KHz Oscillator is ready
        while(!(GET_BIT(MRCC_BDCR_R, MRCC_BDCR_LSERDY_BIT)));
        //Set Clock Source of RTC to be Low-speed external clock
        SET_BIT(MRCC_BDCR_R , MRCC_BDCR_RTCSEL_START_BIT);
        CLR_BIT(MRCC_BDCR_R, (MRCC_BDCR_RTCSEL_START_BIT + 1));
				SET_BIT(MRCC_BDCR_R, MRCC_BDCR_RTCEN_BIT);
    #elif MRTC_CLOCK_SOURCE == MRTC_LSI_CLOCK
    #elif MRTC_CLOCK_SOURCE == MRTC_HSE_CLOCK_DIV_128
    #else
        #error "RTC Clock Source is not specified!!"
    #endif /*MRTC_CLOCK_SOURCE*/

    //Enter Configuration mode
    //CLR_BIT((RTC -> CRL), MRTC_CRL_RTOFF_BIT);
	while(!(GET_BIT((RTC -> CRL), MRTC_CRL_RTOFF_BIT)));
    SET_BIT((RTC -> CRL), MRTC_CRL_CNF_BIT);
    //RTC -> PRLH = 0;
    RTC -> PRLL = 0x7FFF;
    CLR_BIT((RTC -> CRL), MRTC_CRL_CNF_BIT);
    //SET_BIT((RTC -> CRL), MRTC_CRL_RTOFF_BIT);
	while(!(GET_BIT((RTC -> CRL), MRTC_CRL_RTOFF_BIT)));

    #if MRTC_SECOND_INTERRUPT_STATUS == MRTC_SECOND_INTERRUPT_ENABLED
        SET_BIT((RTC -> CRH), MRTC_CRH_SECIE_BIT);
    #elif MRTC_SECOND_INTERRUPT_STATUS == MRTC_SECOND_INTERRUPT_DISABLED
        CLR_BIT((RTC -> CRH), MRTC_CRH_SECIE_BIT);
    #else
        #error "RTC Second Interrupt Not Specified"
    #endif /*MRTC_SECOND_INTERRUPT_STATUS*/


    //Check for synchronization of RTC Registers
    CLR_BIT((RTC -> CRL), MRTC_CRL_RSF_BIT);
    while(!(GET_BIT((RTC -> CRL), MRTC_CRL_RSF_BIT)));

    //Enable RTC Clock
    SET_BIT(MRCC_BDCR_R, MRCC_BDCR_RTCEN_BIT);
    MRTC_CalculateSeconds(&glbl_SReferenceDate, &glbl_SReferenceTime, &glbl_uint32ReferenceSeconds);

    Loc_uint8FuncStatus = E_OK;
    return Loc_uint8FuncStatus;
}
/**
 * @brief: Function to set the date and time of the RTC
 * 
 * @param P_SDateToBeSet: Date to be set
 * @param P_STimeToBeSet: Time to be set
 * 
 * @return Std_ReturnType
 * @retval E_OK: Date and time are successfully set
 * @retval E_NOT_OK: Date and time are not set
 */
Std_ReturnType MRTC_SetDateAndTime         (Sdate_t* P_SDateToBeSet, Stime_t* P_STimeToBeSet)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if((P_SDateToBeSet != NULL_PTR) && (P_STimeToBeSet != NULL_PTR))
    {
        uint32 Loc_uint32SecondsToBeSet = 0;
        Std_ReturnType Loc_uint8FunctStatus = MRTC_CalculateSeconds(P_SDateToBeSet, P_STimeToBeSet, &Loc_uint32SecondsToBeSet);
        if(Loc_uint8FunctStatus == E_OK)
        {
            Loc_uint32SecondsToBeSet -= glbl_uint32ReferenceSeconds;

            //Enter Configuration mode
            while(!(GET_BIT((RTC -> CRL), MRTC_CRL_RTOFF_BIT)));
            SET_BIT((RTC -> CRL), MRTC_CRL_CNF_BIT);
            RTC -> CNTH = (Loc_uint32SecondsToBeSet >> 16);
            RTC -> CNTL = (Loc_uint32SecondsToBeSet & 0xFFFF);
            CLR_BIT((RTC -> CRL), MRTC_CRL_CNF_BIT);
            while(!(GET_BIT((RTC -> CRL), MRTC_CRL_RTOFF_BIT)));

            Loc_uint8FuncStatus = E_OK;
        }
        else
        {
            Loc_uint8FuncStatus = E_NOT_OK;
        }
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}

/**
 * @brief: Function to get the date and time of the RTC
 * 
 * @param P_SDateToBeRead: Date stored in RTC
 * @param P_STimeToBeRead: Time stored in RTC
 * 
 * @return Std_ReturnType
 * @retval E_OK: Date & Time is successfully read
 * @retval E_NOT_OK: Date & Time is not read
 */
Std_ReturnType MRTC_GetDateAndTime  (Sdate_t* P_SDateToBeRead, Stime_t* P_STimeToBeRead)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    if((P_SDateToBeRead != NULL_PTR) && (P_STimeToBeRead != NULL_PTR))
    {
        uint32 Loc_uint32SecondsInReg = ((RTC -> CNTH) << 16) | (RTC -> CNTL);
        Std_ReturnType Loc_uint8FunctStatus = MRTC_CalculateDateTime(&Loc_uint32SecondsInReg, P_SDateToBeRead, P_STimeToBeRead);
        if(Loc_uint8FunctStatus == E_OK)
        {

            Loc_uint8FuncStatus = E_OK;
        }
        else
        {
            Loc_uint8FuncStatus = E_NOT_OK;
        }
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }
    return Loc_uint8FuncStatus;
}

Std_ReturnType MRTC_SetSecondIntCallbackFunc(ptr_to_func_t P_funcIntCallback)
{
    Std_ReturnType Loc_uint8FuncStatus = E_NOT_OK;
    
    if(P_funcIntCallback != NULL_PTR)
    {
        glbl_PCallbackFunc = P_funcIntCallback;
        Loc_uint8FuncStatus = E_OK;
    }
    else
    {
        Loc_uint8FuncStatus = E_NOT_OK;
    }

    return Loc_uint8FuncStatus;
}
void RTC_IRQHandler(void)
{
    if(glbl_PCallbackFunc != NULL_PTR)
    {
        glbl_PCallbackFunc();
				CLR_BIT(RTC->CRL, MRTC_CRL_SECF_BIT);
    }
    else
    {
        /*Do nothing*/
    }
}