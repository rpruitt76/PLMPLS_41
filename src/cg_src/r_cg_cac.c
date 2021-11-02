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
* File Name    : r_cg_cac.c
* Version      : Code Generator for RX64M V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F564MLDxFB
* Tool-Chain   : CCRX
* Description  : This file implements device driver for CAC module.
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
#include "r_cg_cac.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_CAC_Create
* Description  : This function initializes the clock frequency accuracy measurement circuit.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CAC_Create(void)
{
    /* Cancel CAC stop state in LPC */
    MSTP(CAC) = 0U;

    /* Set CAC control registers */
    CAC.CACR1.BYTE = _0A_CAC_TARGET_CLOCK_PCLKB | _00_CAC_TIMER_CLOCK_SOURCE_1 | _00_CAC_VALID_EDGE_RISING;
    CAC.CACR2.BYTE = _01_CAC_REF_SIGNAL_INTERNAL | _00_CAC_REF_CLOCK_MAIN_OSC | _00_CAC_REF_CLOCK_SOURCE_32 | 
                     _40_CAC_DIGITAL_FILTER_DIV_1;
    CAC.CAICR.BYTE = _01_CAC_FERRIE_INTERRUPT_ENABLE | _00_CAC_MENDIE_INTERRUPT_DISABLE | 
                     _00_CAC_OVFIE_INTERRUPT_DISABLE;

    /* Set upper and lower limit register values */
    CAC.CAULVR = _002A_CAC_UPPER_LIMIT;
    CAC.CALLVR = _0026_CAC_LOWER_LIMIT;
}

/***********************************************************************************************************************
* Function Name: R_CAC_Start
* Description  : This function enables the clock frequency accuracy measurement circuit.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CAC_Start(void)
{
    /* Enable CAC interrupts */
    ICU.GENBL0.BIT.EN26 = 1U;

    /* Enable clock frequency measurement */
    CAC.CACR0.BIT.CFME = 1U;

    while (0U == CAC.CACR0.BIT.CFME);
}

/***********************************************************************************************************************
* Function Name: R_CAC_Stop
* Description  : This function stops the clock frequency accuracy measurement circuit.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CAC_Stop(void)
{
    /* Disable CAC interrupts */
    ICU.GENBL0.BIT.EN26 = 0U;

    /* Disable clock frequency measurement */
    CAC.CACR0.BIT.CFME = 0U;
    
    while (1U == CAC.CACR0.BIT.CFME);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
