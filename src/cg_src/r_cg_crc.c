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
* File Name    : r_cg_crc.c
* Version      : Code Generator for RX64M V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F564MLDxFB
* Tool-Chain   : CCRX
* Description  : This file implements device driver for CRC module.
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
#include "r_cg_crc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_CRC_SetCRC16
* Description  : This function set CRC module using CRC16 algorithm.
* Arguments    : order -
*                    specifies the output bit order
* Return Value : None
***********************************************************************************************************************/
void R_CRC_SetCRC16(crc_bitorder order)
{
    uint16_t protect_dummy = (uint16_t)(SYSTEM.PRCR.WORD & 0x000BU);

    /* Disable protect bit */
    SYSTEM.PRCR.WORD = 0xA502U;

    /* Cancel CRC stop state in LPC */
    MSTP(CRC) = 0U;

    /* Set CRC control registers */
    if (order == CRC_LSB)
    {
        CRC.CRCCR.BYTE = _80_CRC_CLEAR_CRCDOR | _00_CRC_LSB_FIRST | _02_CRC_16;
    }
    else if (order == CRC_MSB)
    {
        CRC.CRCCR.BYTE = _80_CRC_CLEAR_CRCDOR | _04_CRC_MSB_FIRST | _02_CRC_16;
    }

    /* Restore the previous state of the protect register */
    SYSTEM.PRCR.WORD = (uint16_t)(0xA500U | protect_dummy);
}
/***********************************************************************************************************************
* Function Name: R_CRC_Input_Data
* Description  : This function writes data to CRC input register.
* Arguments    : data -
*                    value to be written to input register
* Return Value : None
***********************************************************************************************************************/
void R_CRC_Input_Data(uint8_t data)
{
    /* Clear output register */
    CRC.CRCCR.BIT.DORCLR = 1U;

    /* Set initial value for data output register */
    CRC.CRCDOR = 0x0000U;

    /* Write data */
    CRC.CRCDIR = data;
}
/***********************************************************************************************************************
* Function Name: R_CRC_Get_Result
* Description  : This function gets result from CRC output register.
* Arguments    : result -
*                    value of output register read
* Return Value : None
***********************************************************************************************************************/
void R_CRC_Get_Result(uint16_t * const result)
{
    *result = (uint16_t)(CRC.CRCDOR);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
