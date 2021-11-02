/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2013, 2014 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_rtc.c
* Version      : Code Generator for RX64M V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F564MLDxFB
* Tool-Chain   : CCRX
* Description  : This file implements device driver for RTC module.
* Creation Date: 2/2/2015
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_rtc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_RTC_Create
* Description  : This function initializes the RTC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Create(void)
{
    /* Disable ALM, PRD and CUP interrupts */
    IEN(RTC,ALM) = 0U;
    IEN(RTC,PRD) = 0U;

    /* Set sub-clock oscillator */
    while (RTC.RCR3.BIT.RTCEN != 1U)
    {
        RTC.RCR3.BIT.RTCEN = 1U;
    }

    /* Stop all counters */
    RTC.RCR2.BYTE = 0x00U;
    while (RTC.RCR2.BIT.START != 0U);

    /* Select count mode */
    RTC.RCR2.BIT.CNTMD = 0U;
    while (RTC.RCR2.BIT.CNTMD != 0U);

    /* Execute RTC software reset */
    RTC.RCR2.BIT.RESET = 1U;
    while (RTC.RCR2.BIT.RESET != 0U);

    /* Set control registers */
    RTC.RCR1.BYTE = _00_RTC_ALARM_INT_DISABLE | _00_RTC_CARRY_INT_DISABLE | _04_RTC_PERIOD_INT_ENABLE | 
                    _E0_RTC_PERIODIC_INT_PERIOD_1;
    RTC.RCR2.BYTE |= _40_RTC_HOUR_MODE_24;
    while (RTC.RCR2.BIT.HR24 != 1U)

    /* Stop RTC counter */
    RTC.RCR2.BIT.START = 0U;
    while (RTC.RCR2.BIT.START != 0U);

    /* Clear ALM,PRD,CUP IR */
    IR(RTC,ALM) = 0U;
    IR(RTC,PRD) = 0U;

    /* Set counter time */
    //RTC.RSECCNT.BYTE = _00_RTC_COUNT_SECOND_VALUE;
    //RTC.RMINCNT.BYTE = _00_RTC_COUNT_MINUTE_VALUE;
    //RTC.RHRCNT.BYTE = _00_RTC_COUNT_HOUR_VALUE;
    //RTC.RWKCNT.BYTE = _06_RTC_COUNT_WEEK_VALUE;
    //RTC.RDAYCNT.BYTE = _18_RTC_COUNT_DAY_VALUE;
    //RTC.RMONCNT.BYTE = _10_RTC_COUNT_MONTH_VALUE;
    //RTC.RYRCNT.WORD = _0014_RTC_COUNT_YEAR_VALUE;

    /* Set time capture */
    RTC.RTCCR0.BYTE = _00_RTC_TIME_CAPTURE_NO_EVENT | _00_RTC_TIME_CAPTURE_NOISE_FILTER_OFF | 
                      _00_RTC_TIME_CAPTURE_EVENT_DISABLE;
    RTC.RTCCR1.BYTE = _00_RTC_TIME_CAPTURE_NO_EVENT | _00_RTC_TIME_CAPTURE_NOISE_FILTER_OFF | 
                      _00_RTC_TIME_CAPTURE_EVENT_DISABLE;
    RTC.RTCCR2.BYTE = _00_RTC_TIME_CAPTURE_NO_EVENT | _00_RTC_TIME_CAPTURE_NOISE_FILTER_OFF | 
                      _00_RTC_TIME_CAPTURE_EVENT_DISABLE;

    /* Set PRD priority level */
    IPR(RTC,PRD) = _01_RTC_PRIORITY_LEVEL1;
}

/***********************************************************************************************************************
* Function Name: R_RTC_Start
* Description  : This function starts RTC counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Start(void)
{
    /* Enable PRD interrupt */
    IEN(RTC,PRD) = 1U;

    /* Set the START bit to 1 */
    RTC.RCR2.BIT.START = 1U;
    while (RTC.RCR2.BIT.START != 1U);
}

/***********************************************************************************************************************
* Function Name: R_RTC_Stop
* Description  : This function stops RTC counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Stop(void)
{
    /* Disable PRD interrupt */
    IEN(RTC,PRD) = 0U;

    /* Stop all counters */
    RTC.RCR2.BIT.START = 0U;
    while (RTC.RCR2.BIT.START != 0U);
}

/***********************************************************************************************************************
* Function Name: R_RTC_Restart
* Description  : This function restarts RTC counter.
* Arguments    : counter_write_val -
*                    counter write value
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Restart(rtc_calendarcounter_value_t counter_write_val)
{
    /* Disable ALM, PRD and CUP interrupts */
    IEN(RTC,ALM) = 0U;
    IEN(RTC,PRD) = 0U;

    /* Stop all counters */
    RTC.RCR2.BIT.START = 0U;
    while (RTC.RCR2.BIT.START != 0U);

    /* Execute RTC software reset */
    RTC.RCR2.BIT.RESET = 1U;
    while (RTC.RCR2.BIT.RESET != 0U);

    /* Set control registers */
    RTC.RCR2.BYTE = _40_RTC_HOUR_MODE_24;

    /* Set counter values */
    RTC.RSECCNT.BYTE = counter_write_val.rseccnt;
    RTC.RMINCNT.BYTE = counter_write_val.rmincnt;
    RTC.RHRCNT.BYTE = counter_write_val.rhrcnt;
    RTC.RWKCNT.BYTE = counter_write_val.rwkcnt;
    RTC.RDAYCNT.BYTE = counter_write_val.rdaycnt;
    RTC.RMONCNT.BYTE = counter_write_val.rmoncnt;
    RTC.RYRCNT.WORD = counter_write_val.ryrcnt;

    /* Enable PRD interrupt */
    IEN(RTC,PRD) = 1U;

    /* Set the START bit to 1 */
    RTC.RCR2.BIT.START = 1U;
    while (RTC.RCR2.BIT.START != 1U);
}

/***********************************************************************************************************************
* Function Name: R_RTC_Get_CalendarCounterValue
* Description  : This function get RTC calendar counter value.
* Arguments    : counter_read_val -
*                    counter read pointer
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Get_CalendarCounterValue(rtc_calendarcounter_value_t * const counter_read_val)
{
    /* Enable RTC CUP interrupt */
    RTC.RCR1.BYTE |= _02_RTC_CARRY_INT_ENABLE;

    /* Read counter registers */
    counter_read_val->rseccnt = RTC.RSECCNT.BYTE;
    counter_read_val->rmincnt = RTC.RMINCNT.BYTE;
    counter_read_val->rhrcnt = RTC.RHRCNT.BYTE;
    counter_read_val->rwkcnt = RTC.RWKCNT.BYTE;
    counter_read_val->rdaycnt = RTC.RDAYCNT.BYTE;
    counter_read_val->rmoncnt = RTC.RMONCNT.BYTE;
    counter_read_val->ryrcnt = RTC.RYRCNT.WORD;

    /* Disable RTC CUP interrupt */
    RTC.RCR1.BYTE &= ~(_02_RTC_CARRY_INT_ENABLE);
}

/***********************************************************************************************************************
* Function Name: R_RTC_Set_CalendarCounterValue
* Description  : This function set RTC calendar counter value.
* Arguments    : counter_write_val -
*                    counter write value
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Set_CalendarCounterValue(rtc_calendarcounter_value_t counter_write_val)
{
    /* Stop all counters */
    RTC.RCR2.BIT.START = 0U;
    while (RTC.RCR2.BIT.START != 0U);

    /* Execute RTC software reset */
    RTC.RCR2.BIT.RESET = 1U;
    while (RTC.RCR2.BIT.RESET != 0U);

    /* Set control registers */
    RTC.RCR2.BYTE = _40_RTC_HOUR_MODE_24;

    /* Set counter values */
    RTC.RSECCNT.BYTE = counter_write_val.rseccnt;
    RTC.RMINCNT.BYTE = counter_write_val.rmincnt;
    RTC.RHRCNT.BYTE = counter_write_val.rhrcnt;
    RTC.RWKCNT.BYTE = counter_write_val.rwkcnt;
    RTC.RDAYCNT.BYTE = counter_write_val.rdaycnt;
    RTC.RMONCNT.BYTE = counter_write_val.rmoncnt;
    RTC.RYRCNT.WORD = counter_write_val.ryrcnt;
}

/***********************************************************************************************************************
* Function Name: R_RTC_Set_ConstPeriodInterruptOn
* Description  : This function set RTC constant period interrupt and enable the interrupt(PRD).
* Arguments    : period -
*                    new period of constant period interrupt
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Set_ConstPeriodInterruptOn(rtc_int_period_t period)
{
    /* Disable ICU PRD interrupt */
    IEN(RTC,PRD) = 0U;

    /* Clear IR flag of PRD interrupt*/
    IR(RTC,PRD) = 0U;

    /* Set RTC control register 1 */
    RTC.RCR1.BYTE = (uint8_t)(period | (RTC.RCR1.BYTE & 0x0FU) | _04_RTC_PERIOD_INT_ENABLE);

    /* Enable ICU PRD interrupt */
    IEN(RTC,PRD) = 1U;
}

/***********************************************************************************************************************
* Function Name: R_RTC_Set_ConstPeriodInterruptOff
* Description  : This function disable RTC constant period interrupt(PRD).
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_RTC_Set_ConstPeriodInterruptOff(void)
{
    /* Disable ICU PRD interrupt */
    IEN(RTC,PRD) = 0U;

    /* Clear IR flag of PRD interrupt*/
    IR(RTC,PRD) = 0U;

    /* Disable RTC PRD interrupt */
    RTC.RCR1.BIT.PIE = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
