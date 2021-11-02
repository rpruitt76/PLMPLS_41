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
* File Name    : r_cg_lpc.c
* Version      : Code Generator for RX64M V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F564MLDxFB
* Tool-Chain   : CCRX
* Description  : This file implements device driver for LPC module.
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
#include "r_cg_lpc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_LPC_Create
* Description  : This function initializes the LPC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_LPC_Create(void)
{
    /* Set operating power control */
    SYSTEM.OPCCR.BIT.OPCM = _00_LPC_HIGH_SPEED_MODE;

    while (1U == SYSTEM.OPCCR.BIT.OPCMTSF);

    SYSTEM.DPSIER1.BYTE = _80_LPC_DIRQ15E_ENABLED;
    SYSTEM.DPSIEGR1.BYTE = _80_LPC_DIRQ15EG_RISING;
    SYSTEM.DPSBYCR.BIT.IOKEEP = 0U;
    SYSTEM.DPSBYCR.BIT.DEEPCUT = _03_LPC_POWER_OFF_LVD;
    SYSTEM.SBYCR.BIT.OPE = 0U;

    /* Set sleep mode return clock source */
    SYSTEM.RSTCKCR.BYTE = _82_LPC_RETURN_CLK_MAIN_OSC;
}

/***********************************************************************************************************************
* Function Name: R_LPC_AllModuleClockStop
* Description  : This function stops all module clock.
* Arguments    : None
* Return Value : status -
*                    MD_OK
***********************************************************************************************************************/
MD_STATUS R_LPC_AllModuleClockStop(void)
{
    MD_STATUS status = MD_OK;

    uint16_t protect_dummy = (uint16_t)(SYSTEM.PRCR.WORD & 0x000BU);
    uint32_t mstpcra_dummy = SYSTEM.MSTPCRA.LONG;
    uint32_t mstpcrb_dummy = SYSTEM.MSTPCRB.LONG;
    uint32_t mstpcrc_dummy = SYSTEM.MSTPCRC.LONG;
    uint32_t mstpcrd_dummy = SYSTEM.MSTPCRD.LONG;

    /* Disable protect bit */
    SYSTEM.PRCR.WORD = 0xA503U;

    /* Set module stop for MTU, CMT, S12ADb, DA and DTC */
    SYSTEM.MSTPCRA.LONG = 0xFFFFFFFFU;

    /* Set module stop for SCI, DOC, ELC, RSPI, USB, RIIC and CRC */
    SYSTEM.MSTPCRB.LONG = 0xFFFFFFFFU;

    /* Set module stop for RAM and CAC. */
    SYSTEM.MSTPCRC.LONG = 0xFFFFFFFFU;

    /* Set module stop for SSI, MMC, SRC, etc. */
    SYSTEM.MSTPCRD.LONG = 0xFFFFFFFFU;

    /* Select sleep or all-module clock stop */
    SYSTEM.SBYCR.BIT.SSBY = 0U;

    /* Prevent out-of-order execution */
    while (SYSTEM.SBYCR.BIT.SSBY != 0U);

    /* Initiate the low-power mode */
    wait();

    /* Restore the modules that were enabled before stopping */
    SYSTEM.MSTPCRA.LONG = mstpcra_dummy;
    SYSTEM.MSTPCRB.LONG = mstpcrb_dummy;
    SYSTEM.MSTPCRC.LONG = mstpcrc_dummy;
    SYSTEM.MSTPCRD.LONG = mstpcrd_dummy;

    /* Restore the previous state of the protect register */
    SYSTEM.PRCR.WORD = (uint16_t)(0xA500U | protect_dummy);

    return status;
}

/***********************************************************************************************************************
* Function Name: R_LPC_Sleep
* Description  : This function enables sleep mode.
* Arguments    : None
* Return Value : status -
*                    MD_OK or MD_ERROR1
***********************************************************************************************************************/
MD_STATUS R_LPC_Sleep(void)
{
    MD_STATUS status = MD_OK;

    uint16_t protect_dummy = (uint16_t)(SYSTEM.PRCR.WORD & 0x000BU);

    /* Disable protect bit */
    SYSTEM.PRCR.WORD = 0xA503U;

    /* When RSTCKEN is enable, the possible clock source is HOCO or main clock oscillator */
    if ((SYSTEM.RSTCKCR.BIT.RSTCKEN == 1U) && (SYSTEM.SCKCR3.BIT.CKSEL != _0100_LPC_CLOCKSOURCE_HOCO) &&
        (SYSTEM.SCKCR3.BIT.CKSEL  != _0200_LPC_CLOCKSOURCE_MAINCLK))
    {
        status = MD_ERROR1;
    }

    /* Select sleep mode */
    SYSTEM.SBYCR.BIT.SSBY = 0U;

    /* Prevent out-of-order execution */
    while (SYSTEM.SBYCR.BIT.SSBY != 0U);

    /* Initiate the low-power mode */
    wait();

    /* Restore the previous state of the protect register */
    SYSTEM.PRCR.WORD = (uint16_t)(0xA500U | protect_dummy);

    return status;
}

/***********************************************************************************************************************
* Function Name: R_LPC_SoftwareStandby
* Description  : This function enables software standby mode.
* Arguments    : None
* Return Value : status -
*                    MD_OK or MD_ERROR1
***********************************************************************************************************************/
MD_STATUS R_LPC_SoftwareStandby(void)
{
    MD_STATUS status = MD_OK;

    uint16_t protect_dummy = (uint16_t)(SYSTEM.PRCR.WORD & 0x000BU);

    /* Disable protect bit */
    SYSTEM.PRCR.WORD = 0xA503U;

    /* When oscillation stop detection function is enabled, SSBY bit is invalid */
    if (SYSTEM.OSTDCR.BIT.OSTDE == 1U)
    {
        status = MD_ERROR1;
    }

    /* Select standby mode */
    SYSTEM.SBYCR.BIT.SSBY = 1U;
    SYSTEM.DPSBYCR.BIT.DPSBY = 0U;

    /* Prevent out-of-order execution */
    while (SYSTEM.SBYCR.BIT.SSBY != 1U);

    /* Initiate the low-power mode */
    wait();

    /* Restore the previous state of the protect register */
    SYSTEM.PRCR.WORD = (uint16_t)(0xA500U | protect_dummy);

    return status;
}

/***********************************************************************************************************************
* Function Name: R_LPC_DeepSoftwareStandby
* Description  : This function enables deep software standby mode.
* Arguments    : None
* Return Value : status -
*                    MD_OK
***********************************************************************************************************************/
MD_STATUS R_LPC_DeepSoftwareStandby(void)
{
    MD_STATUS status = MD_OK;

    uint16_t protect_dummy = (uint16_t)(SYSTEM.PRCR.WORD & 0x000BU);

    /* Save the current state of DTC */
    uint8_t dummy_mstpa28 = SYSTEM.MSTPCRA.BIT.MSTPA28;
    uint8_t dummy_dtcst = DTC.DTCST.BIT.DTCST;

    /* Disable protect bit */
    SYSTEM.PRCR.WORD = 0xA503U;

    /* Set DTC module to stop state */
    DTC.DTCST.BIT.DTCST = 0U;
    SYSTEM.MSTPCRA.BIT.MSTPA28 = 1U;

    /* Enable deep software standby mode */
    SYSTEM.SBYCR.BIT.SSBY = 1U;
    SYSTEM.DPSBYCR.BIT.DPSBY = 1U;

    /* Prevent out-of-order execution */
    while (SYSTEM.SBYCR.BIT.SSBY != 1U);

    /* Initiate the low-power mode */
    wait();

    /* Restore the state of DTC if necessary */
    if (0U == dummy_mstpa28)
    {
        SYSTEM.MSTPCRA.BIT.MSTPA28 = 0U;
        DTC.DTCST.BIT.DTCST = dummy_dtcst;
    }

    /* Restore the previous state of the protect register */
    SYSTEM.PRCR.WORD = (uint16_t)(0xA500U | protect_dummy);

    return status;
}

/***********************************************************************************************************************
* Function Name: R_LPC_ChangeOperatingPowerControl
* Description  : This function allows operating power control to be changed.
* Arguments    : mode -
*                    clock operation mode
* Return Value : status -
*                    MD_OK, MD_ERROR1, MD_ERROR2 or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_LPC_ChangeOperatingPowerControl(operating_mode_t mode)
{
    MD_STATUS status = MD_OK;
    operating_mode_t old_mode;

    uint16_t protect_dummy = (uint16_t)(SYSTEM.PRCR.WORD & 0x000BU);

    /* Get the current mode */
    if (SYSTEM.OPCCR.BIT.OPCM == _06_LPC_LOW_SPEED_MODE1)
    {
        old_mode = LOW_SPEED1;
    }
    else
    {
        if (SYSTEM.OPCCR.BIT.OPCM == _00_LPC_HIGH_SPEED_MODE)
        {
            old_mode = HIGH_SPEED;
        }
        else
        {
            old_mode = LOW_SPEED2;
        }
    }

    /* Disable protect bit */
    SYSTEM.PRCR.WORD = 0xA503U;

    if (mode != old_mode)
    {
        /* Set the desired operating power control mode */
        switch (mode)
        {
            case LOW_SPEED1:
                /* OPCCR should not be set when OPCMTSF bit is 1 */
                if ((0U == SYSTEM.OPCCR.BIT.OPCMTSF) && (1U == SYSTEM.PLLCR2.BIT.PLLEN))
                {
                    /* Set low-speed operating mode 1 */
                    SYSTEM.OPCCR.BIT.OPCM = 6U;

                    while (SYSTEM.OPCCR.BIT.OPCMTSF != 0U);
                }
                else
                {
                    status = MD_ERROR1;
                }

                break;

            case LOW_SPEED2:
                /* OPCCR should not be set when OPCMTSF bit is 1 */
                if (0U == SYSTEM.OPCCR.BIT.OPCMTSF)
                {
                    /* Low-speed mode 2 should not be set when PLL is in operation */
                    if ((1U == SYSTEM.PLLCR2.BIT.PLLEN) && (1U == SYSTEM.HOCOCR.BIT.HCSTP)
                         && (0U == SYSTEM.OSTDCR.BIT.OSTDE))
                    {
                        /* Set Low-speed operating mode 2 */
                        SYSTEM.OPCCR.BIT.OPCM = 7U;
                    }
                    else
                    {
                        status = MD_ERROR2;
                    }

                    while (SYSTEM.OPCCR.BIT.OPCMTSF != 0U);
                }

                break;
                
            case HIGH_SPEED:
                /* OPCCR should not be set when OPCMTSF bit is 1 */
                if (0U == SYSTEM.OPCCR.BIT.OPCMTSF)
                {
                    /* Set high-speed operating mode */
                    SYSTEM.OPCCR.BIT.OPCM = 0U;

                    while (SYSTEM.OPCCR.BIT.OPCMTSF != 0U);
                }

                break;

            default:

                status =  MD_ARGERROR;

                break;
        }
    }

    /* Restore the previous state of the protect register */
    SYSTEM.PRCR.WORD = (uint16_t)(0xA500U | protect_dummy);

    return status;
}

/***********************************************************************************************************************
* Function Name: R_LPC_ChangeSleepModeReturnClock
* Description  : This function allows sleep mode return clock to be changed.
* Arguments    : clock -
*                    return clock operation mode
* Return Value : status -
*                    MD_OK, MD_ARGERROR or MD_ERROR1
***********************************************************************************************************************/
MD_STATUS R_LPC_ChangeSleepModeReturnClock(return_clock_t clock)
{
    MD_STATUS status = MD_OK;
    return_clock_t old_clock;

    uint16_t protect_dummy = (uint16_t)(SYSTEM.PRCR.WORD & 0x000BU);

    /* Get the current return clock */
    if (0U == SYSTEM.RSTCKCR.BIT.RSTCKEN)
    {
        old_clock = RETURN_DISABLE;
    }
    else
    {
        if (1U == SYSTEM.RSTCKCR.BIT.RSTCKSEL)
        {
            old_clock = RETURN_HOCO;
        }
        else if (2U == SYSTEM.RSTCKCR.BIT.RSTCKSEL)
        {
            old_clock = RETURN_MAIN_CLOCK;
        }
        else
        {
            return MD_ERROR1;
        }
    }

    /* Disable protect bit */
    SYSTEM.PRCR.WORD = 0xA503U;

    if (clock != old_clock)
    {
        /* Set the desired sleep mode return clock source */
        switch (clock)
        {
            case RETURN_DISABLE:
                SYSTEM.RSTCKCR.BYTE = _00_LPC_RETURN_DISABLED;
                break;

            case RETURN_HOCO:
                SYSTEM.RSTCKCR.BYTE = _81_LPC_RETURN_CLK_HOCO;
                break;

            case RETURN_MAIN_CLOCK:
                SYSTEM.RSTCKCR.BYTE = _82_LPC_RETURN_CLK_MAIN_OSC;
                break;

            default:
                status =  MD_ARGERROR;
                break;
        }
    }

    /* Restore the previous state of the protect register */
    SYSTEM.PRCR.WORD = (uint16_t)(0xA500U | protect_dummy);

    return status;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
