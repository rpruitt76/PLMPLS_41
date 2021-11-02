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
* File Name    : r_cg_icu.c
* Version      : Code Generator for RX64M V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F564MLDxFB
* Tool-Chain   : CCRX
* Description  : This file implements device driver for ICU module.
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
#include "r_cg_icu.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_ICU_Create
* Description  : This function initializes ICU module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ICU_Create(void)
{
    /* Disable IRQ interrupts */
    ICU.IER[0x08].BYTE = _00_ICU_IRQ0_DISABLE | _00_ICU_IRQ1_DISABLE | _00_ICU_IRQ2_DISABLE | _00_ICU_IRQ3_DISABLE |
                         _00_ICU_IRQ4_DISABLE | _00_ICU_IRQ5_DISABLE | _00_ICU_IRQ6_DISABLE | _00_ICU_IRQ7_DISABLE;
    ICU.IER[0x09].BYTE = _00_ICU_IRQ8_DISABLE | _00_ICU_IRQ9_DISABLE | _00_ICU_IRQ10_DISABLE | _00_ICU_IRQ11_DISABLE |
                         _00_ICU_IRQ12_DISABLE | _00_ICU_IRQ13_DISABLE | _00_ICU_IRQ14_DISABLE | _00_ICU_IRQ15_DISABLE;

    /* Disable software interrupt */
    IEN(ICU,SWINT) = 0U;
    IEN(ICU,SWINT2) = 0U;

    /* Set IRQ8~15 digital filter */
    ICU.IRQFLTE1.BYTE = _80_ICU_IRQ15_FILTER_ENABLE;
    ICU.IRQFLTC1.WORD = _C000_ICU_IRQ15_FILTER_PCLK_64;

    /* Set IRQ settings */
    ICU.IRQCR[15].BYTE = _00_ICU_IRQ_EDGE_LOW_LEVEL;

    /* Set SWINT Priority level */
    IPR(ICU,SWINT) = _02_ICU_PRIORITY_LEVEL2;

    /* Set SWINT2 priority level */
    IPR(ICU,SWINT2) = _01_ICU_PRIORITY_LEVEL1;

    /* Set IRQ15 priority level */
    IPR(ICU,IRQ15) = _03_ICU_PRIORITY_LEVEL3;

    /* Set IRQ15 pin */
    MPC.P47PFS.BYTE = 0x40U;
    PORT4.PDR.BYTE &= 0x7FU;
    PORT4.PMR.BYTE &= 0x7FU;

}
/***********************************************************************************************************************
* Function Name: R_ICU_Software_Start
* Description  : This function enables SWINT interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ICU_Software_Start(void)
{
    /* Enable software interrupt */
    IEN(ICU,SWINT) = 1U;
}
/***********************************************************************************************************************
* Function Name: R_ICU_SoftwareInterrupt_Generate
* Description  : This function generates SWINT interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ICU_SoftwareInterrupt_Generate(void)
{
    /* Generate software interrupt */
    ICU.SWINTR.BIT.SWINT = 1U;
}
/***********************************************************************************************************************
* Function Name: R_ICU_Software_Stop
* Description  : This function disables SWINT interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ICU_Software_Stop(void)
{
    /* Disable software interrupt */
    IEN(ICU,SWINT) = 0U;
}
/***********************************************************************************************************************
* Function Name: R_ICU_Software2_Start
* Description  : This function enables SWINT2 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ICU_Software2_Start(void)
{
    /* Enable software interrupt */
    IEN(ICU,SWINT2) = 1U;
}
/***********************************************************************************************************************
* Function Name: R_ICU_SoftwareInterrupt2_Generate
* Description  : This function generates SWINT2 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ICU_SoftwareInterrupt2_Generate(void)
{
    /* Generate software interrupt */
    ICU.SWINT2R.BIT.SWINT2 = 1U;
}
/***********************************************************************************************************************
* Function Name: R_ICU_Software2_Stop
* Description  : This function disables SWINT2 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ICU_Software2_Stop(void)
{
    /* Disable software interrupt */
    IEN(ICU,SWINT2) = 0U;
}
/***********************************************************************************************************************
* Function Name: R_ICU_IRQ15_Start
* Description  : This function enables IRQ15 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ICU_IRQ15_Start(void)
{
    /* Enable IRQ15 interrupt */
    IEN(ICU,IRQ15) = 1U;
}
/***********************************************************************************************************************
* Function Name: R_ICU_IRQ15_Stop
* Description  : This function disables IRQ15 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_ICU_IRQ15_Stop(void)
{
    /* Disable IRQ15 interrupt */
    IEN(ICU,IRQ15) = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
