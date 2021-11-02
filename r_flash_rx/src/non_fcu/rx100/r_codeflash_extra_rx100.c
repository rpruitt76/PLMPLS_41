/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2014 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name    : r_codeflash_extra_rx100.c
* Description  : Flash Control Access window and swap control
*                processing of E2 Code Flash.
* Limitation   : none
*******************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*                17.07.2014 1.00     First Release
*                12.11.2014 1.10     Removed FLASH.DFLCTL.BIT.DFLEN operations in
*                                    in R_CF_SetAccessWindow() and r_cf_set_startup_area(),
*                                    and FLASH.FASR.BIT.EXS clearing in 
*                                    R_CF_SetAccessWindow and R_CF_GetCurrentStartupArea
*                                    as per Japan.
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , “Project Includes”
******************************************************************************/
#include "platform.h"
#ifdef BSP_MCU_RX11_ALL
#include "r_flash_common_rx100.h"
#include "r_codeflash_extra_rx100.h"
#include "r_flash_rx100_if.h"


/******************************************************************************
Private global variables and functions
******************************************************************************/
static void r_cf_extra_operation (const uint32_t start_addr_startup_value, const uint32_t end_addr, r_flash_command_t command);
static flash_err_t r_cf_extra_check (void);
static flash_err_t r_cf_set_startup_area (uint32_t value);

#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
#pragma section FRAM
#endif

/*******************************************************************************
* Outline      : Setting the access window
* Header       : r_codeflash_extra_rx100.h
* Function Name: R_CF_SetAccessWindow
* Description  : Specifies the setting for the access window.
* Arguments    : start_addr : start address of Access Window Setting
               : end_addr   : end address of Access Window Setting. This should be one
                              beyond the actual last byte to allow write access for.
                              here as required by the spec.
* Return Value : FLASH_SUCCESS            - Command executed successfully
*              : FLASH_ERR_ACCESSW        - AccessWindow setting error
*******************************************************************************/
flash_err_t R_CF_SetAccessWindow (flash_access_window_config_t  *pAccessInfo)
{
    flash_err_t      err = FLASH_SUCCESS;

    uint32_t start_addr_idx;
    uint32_t end_addr_idx;

    err = flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH);
    if (FLASH_SUCCESS != err)
        return(err);


    start_addr_idx = pAccessInfo->start_addr - CODEFLASH_ADDR_OFFSET;    /* Conversion to the P/E address from the read address */
    end_addr_idx   = (pAccessInfo->end_addr) - CODEFLASH_ADDR_OFFSET;      /* Conversion to the P/E address from the read address */

    /* == Select Extra Area == */
    FLASH.FASR.BIT.EXS = 1;

    r_cf_extra_operation(start_addr_idx, end_addr_idx, (r_flash_command_t)R_FLASH_ACCESSWINDOW);

    do
    {
        err = r_cf_extra_check();
    }
    while (FLASH_ERR_BUSY == err);

    flash_pe_mode_exit();

    return err;

}

/*******************************************************************************
* Outline      : Getting the access window
* Header       : r_codeflash_extra_rx100.h
* Function Name: R_CF_GetAccessWindow
* Description  : Return the read address form of the current access window area setting
* Arguments    : none
* Return Value : FLASH_SUCCESS
*******************************************************************************/
flash_err_t R_CF_GetAccessWindow (flash_access_window_config_t  *pAccessInfo)
{
    pAccessInfo->start_addr = (FLASH.FAWSMR << 10) + CODEFLASH_ADDR_OFFSET;
    pAccessInfo->end_addr = (FLASH.FAWEMR << 10) + CODEFLASH_ADDR_OFFSET;

    return FLASH_SUCCESS;
}


/*******************************************************************************
* Outline      : Switching the start-up program
* Header       : r_codeflash_extra_rx100.h
* Function Name: R_CF_ToggleStartupArea
* Description  : Check the current start-up area setting
*              : and specifies the area currently not used as the start-up area.
* Arguments    : none
* Return Value : FLASH_SUCCESS -
*                Switched successfully.
*                FLASH_ERR_FAILURE -
*                Unable to Switch to P/E Mode.
*                FLASH_ERR_PARAM -
*                Illegal parameter passed
*******************************************************************************/
flash_err_t R_CF_ToggleStartupArea (void)
{
    uint8_t startup_area_flag;
    uint16_t reg_fscmr;
    flash_err_t err = FLASH_SUCCESS;

    err = flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH);
    if (FLASH_SUCCESS != err)
        return(err);

    reg_fscmr = FLASH.FSCMR.WORD;
    startup_area_flag  = (uint8_t)((reg_fscmr >> 8) & 0x01);

    if (DEFAULT_AREA == startup_area_flag)
    {
        r_cf_set_startup_area(STARTUP_AREA_VALUE);
    }
    else
    {
        r_cf_set_startup_area(DEFAULT_AREA_VALUE);
    }

    reg_fscmr = FLASH.FSCMR.WORD;

    flash_pe_mode_exit();

    return err;
}

/*******************************************************************************
* Outline      : Setting for switching the start-up program
* Header       : r_codeflash_extra_rx100.h
* Function Name: r_cf_set_startup_area
* Description  : Set the start-up area information that is specified by the argument.
* Arguments    : value : Setting information for the FWBH register
* Return Value : FLASH_SUCCESS -  Command executed successfully
*              : FLASH_ERR_ACCESSW - Start-up program switching error
*******************************************************************************/
static flash_err_t r_cf_set_startup_area (uint32_t value)
{
    flash_err_t err = FLASH_SUCCESS;

    /* Select Extra Area */
    FLASH.FASR.BIT.EXS = 1;

    r_cf_extra_operation(value, DUMMY, R_FLASH_STARTUPAREA);

    do
    {
        err = r_cf_extra_check();
    }
    while (FLASH_ERR_BUSY == err);

    return err;

}

/*******************************************************************************
* Outline      : Return which startup area (Default or Alternate) is active
* Header       : r_codeflash_extra_rx100.h
* Function Name: R_CF_GetCurrentStartupArea
* Description  : Return which startup area (Default or Alternate) is active
* Arguments    : none
* Return Value : startup_area_flag - 0 ==> Alternate area
*                                    1 ==> Default area
*******************************************************************************/
uint8_t R_CF_GetCurrentStartupArea(void)
{
    uint8_t startup_area_flag;
    uint16_t reg_fscmr;

    reg_fscmr = FLASH.FSCMR.WORD;
    startup_area_flag  = (uint8_t)((reg_fscmr >> 8) & 0x01);
    return(startup_area_flag);
}


/*******************************************************************************
* Outline      :
* Header       : r_codeflash_extra_rx100.h
* Function Name: R_CF_GetCurrentSwapState
* Description  : Return which startup area (Default or Alternate) is active
* Arguments    : none
* Return Value : startup_area_select - 2 ==> The start-up area is switched to
*                                            the default area temporarily.
*                                      3 ==> The start-up area is switched to
*                                            the alternate area temporarily.
*******************************************************************************/
uint8_t R_CF_GetCurrentSwapState(void)
{
    uint8_t startup_area_select;

    startup_area_select = FLASH.FISR.BIT.SAS;
    return(startup_area_select);
}

/*******************************************************************************
* Outline      :
* Header       : r_codeflash_extra_rx100.h
* Function Name: R_CF_SetCurrentSwapState
* Description  : Return which startup area (Default or Alternate) is active
* Arguments    : none
* Return Value : startup_area_select - 2 ==> The start-up area is switched to
*                                            the default area temporarily.
*                                      3 ==> The start-up area is switched to
*                                            the alternate area temporarily.
*******************************************************************************/
void R_CF_SetCurrentSwapState(uint8_t value)
{
    flash_err_t err = FLASH_SUCCESS;

    err = flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH);
    if (FLASH_SUCCESS != err)
        return;

    FLASH.FISR.BIT.SAS = value;
    flash_pe_mode_exit();
}


/*******************************************************************************
* Outline      : Command processing for the extra area
* Header       : r_codeflash_extra_rx100.h
* Function Name: r_cf_extra_operation
* Description  : Issues a command to the extra area.
* Arguments    : start_addr_startup_value : start Address of the AccessWindow, or StartupAreaflag setting value
*              : end_addr : end Address of AccessWindow Setting, or Dummy value (start-up area information program)
*              : command  : select from R_FLASH_ACCESSWINDOW or R_FLASH_STARTUPAREA
* Return Value : none
*******************************************************************************/
static void r_cf_extra_operation (const uint32_t start_addr_startup_value, const uint32_t end_addr, r_flash_command_t command)
{

    if (R_FLASH_ACCESSWINDOW == command)
    {
        /* Access Window start address setting */
        FLASH.FWBH = (uint16_t)(end_addr >> 10);
        FLASH.FWBL = (uint16_t)(start_addr_startup_value >> 10);

        /* Execute Access Window command */
        FLASH.FEXCR.BYTE = FEXCR_AW;
    }
    else
    {
        /* Startup Area Flag value setting */
        FLASH.FWBH = (uint16_t)(0xFFFF);
        FLASH.FWBL = (uint16_t)(start_addr_startup_value);

        /* Execute Startup Area Flag command */
        FLASH.FEXCR.BYTE = FEXCR_STARTUP;
    }

}

/*******************************************************************************
* Outline      : Verifying the execution result for the extra area
* Header       : r_codeflash_extra_rx100.h
* Function Name: r_cf_extra_check
* Description  : Waits for completing of the command execution
*              : and verifies the result of the execution.
* Arguments    : none
* Return Value : FLASH_SUCCESS           - Command executed successfully
*              : FLASH_ERR_BUSY         - Command being executed
*              : FLASH_ERR_ACCESSW      - Extra area command error
*******************************************************************************/
static flash_err_t r_cf_extra_check (void)
{

    /* Check EXFREADY Flag bit*/
    if (1 != FLASH.FSTATR1.BIT.EXRDY)
    {
        return FLASH_ERR_BUSY;
    }

    /* Clear FEXCR register */
    FLASH.FEXCR.BYTE = FEXCR_CLEAR;

    while (0 != FLASH.FSTATR1.BIT.EXRDY)
    {
        /* Check that execute command is completed. */
    }

    if ((0 != FLASH.FSTATR0.BIT.EILGLERR) || (0 != FLASH.FSTATR0.BIT.PRGERR))
    {
        flash_reset();
        return FLASH_ERR_ACCESSW;
    }

    return FLASH_SUCCESS;
}

#pragma section //end FRAM

#endif
/* end of file */
