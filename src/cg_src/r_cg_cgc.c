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
* File Name    : r_cg_cgc.c
* Version      : Code Generator for RX64M V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F564MLDxFB
* Tool-Chain   : CCRX
* Description  : This file implements device driver for CGC module.
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
#include "r_cg_cgc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"
#include "r_cg_cac.h"
#include "r_cg_lpc.h"
#include "r_cg_icu.h"
#include "r_cg_port.h"
#include "r_cg_mtu3.h"
#include "r_cg_tmr.h"
#include "r_cg_cmt.h"
#include "r_cg_rtc.h"
#include "r_cg_wdt.h"
#include "r_cg_sci.h"
#include "r_flash_rx_if.h"
#include <stdio.h>
#include <string.h>
#include <LaserP.h>

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_CGC_Create
* Description  : This function initializes the clock generator.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CGC_Create(void)
{
	int x;
	int temp1;
	//NOT NEEDED..Handled by BSP....2/17/15 RP
	/* Set main clock control registers */
    //SYSTEM.MOFCR.BYTE = _00_CGC_MAINOSC_RESONATOR | _00_CGC_MAINOSC_UNDER24M;
    //SYSTEM.MOFCR.BIT.MOFXIN = 1U;
    //SYSTEM.MOSCWTCR.BYTE = _5C_CGC_MOSCWTCR_VALUE;

	//NOT NEEDED..Handled by BSP....2/17/15 RP
    /* Set main clock operation */
    //SYSTEM.MOSCCR.BIT.MOSTP = 0U;

	//NOT NEEDED..Handled by BSP....2/17/15 RP
    /* Wait for main clock oscillator wait counter overflow */
    //while (1U != SYSTEM.OSCOVFSR.BIT.MOOVF);

	//NOT NEEDED..Handled by BSP....2/17/15 RP
    /* Set system clock */
    //SYSTEM.SCKCR.LONG = _00000004_CGC_PCLKD_DIV_16 | _00000040_CGC_PCLKC_DIV_16 | _00000200_CGC_PCLKB_DIV_4 |
    //                    _00002000_CGC_PCLKA_DIV_4 | _00040000_CGC_BCLK_DIV_16 | _00000000_CGC_ICLK_DIV_1 |
    //                    _40000000_CGC_FCLK_DIV_16;

	//NOT NEEDED..Handled by BSP....2/17/15 RP
    /* Set PLL circuit */
    //SYSTEM.PLLCR.WORD = _0001_CGC_PLL_FREQ_DIV_2 | 0 | _1300_CGC_PLL_FREQ_MUL_10_0;
    //SYSTEM.PLLCR2.BIT.PLLEN = 0U;

	//NOT NEEDED..Handled by BSP....2/17/15 RP
    /* Wait for PLL wait counter overflow */
    //while (1U != SYSTEM.OSCOVFSR.BIT.PLOVF);

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    /* Set RTC clock source */
    RTC.RCR4.BYTE = _00_RTC_SOURCE_SELECT_SUB;

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    /* Stop sub-clock */
    RTC.RCR3.BIT.RTCEN = 0U;

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    /* Wait for the register modification to complete */
    while (0U != RTC.RCR3.BIT.RTCEN);

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    /* Stop sub-clock */
    SYSTEM.SOSCCR.BIT.SOSTP = 1U;

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    /* Wait for the register modification to complete */
    while (1U != SYSTEM.SOSCCR.BIT.SOSTP);

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    /* Wait for sub-clock oscillation stopping */
    while (0U != SYSTEM.OSCOVFSR.BIT.SOOVF);

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    // Set sub-clock drive capacity...Drive capacity for low CL
    RTC.RCR3.BIT.RTCDV = 1U;

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    /* Wait for the register modification to complete */
    while (1U != RTC.RCR3.BIT.RTCDV);
    
	//NOT NEEDED..Handled by BSP....8/28/15 RP
    /* Set sub-clock oscillation wait time */
    SYSTEM.SOSCWTCR.BYTE = _25_CGC_SOSCWTCR_VALUE;
    //SYSTEM.SOSCWTCR.BYTE = 200;

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    // Set sub-clock...OPERATION STARTED
    SYSTEM.SOSCCR.BIT.SOSTP = 0U;

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    /* Wait for the register modification to complete */
    while (0U != SYSTEM.SOSCCR.BIT.SOSTP);

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    /* Wait for sub-clock to be stable */
    //while (1U != SYSTEM.OSCOVFSR.BIT.SOOVF);
    long_delay(1);
    for (x=0; x<25; x++)
    {
    	accurate_delay(100);
    	temp1 = SYSTEM.OSCOVFSR.BIT.SOOVF;
    	// If Subclock stabilizes, then break.
    	if (temp1 == 1)
    		break;
    }
    // Test if we had overflow.....This indicates that Subclock not working.
    if( x>= 25)
    {
    	// Indicate Error.
    	subClock_Fail = 1;			// We have a Subclock Failure.

    	// Reconfigure Subclock to use Main clock devider.
        /* Set RTC clock source */
        RTC.RCR4.BYTE = _01_RTC_SOURCE_SELECT_MAIN_FORCED;
 }
    else
    {
    	subClock_Fail = 0;			// No Subclock Failure.
    }
    SYSTEM.SOSCWTCR.BYTE = 0x00U;

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    /* Set IWDT */
    //SYSTEM.ILOCOCR.BIT.ILCSTP = 0U;

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    /* Set UCLK */
    //SYSTEM.SCKCR2.WORD = _0040_CGC_UCLK_DIV_5;

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    /* Set SDCLK */
    //SYSTEM.SCKCR.BIT.PSTOP0 = 1U;

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    /* Set clock source */
    //SYSTEM.SCKCR3.WORD = _0400_CGC_CLOCKSOURCE_PLL;

	//NOT NEEDED..Handled by BSP....8/28/15 RP
    /* Set LOCO */
    //SYSTEM.LOCOCR.BIT.LCSTP = 0U;
}


/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
