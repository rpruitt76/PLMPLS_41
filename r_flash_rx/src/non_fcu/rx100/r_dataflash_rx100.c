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
* File Name    : r_dataflash_rx100.c
* Description  : Flash Control Processing of E2 Data Flash.
* Limitation   : none
*******************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*                17.07.2014 1.00     First Release
*                12.11.2014 1.10     As per Japan: Removed call to
*                                    R_DF_Enable_DataFlashAccess(). Added
*                                    FLASH.FASR.BIT.EXS clearing to multiple
*                                    functions. Removed RX110 no data flash
*                                    warning. Fixed PRGERR check in R_DF_Write_Check().
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , “Project Includes”
******************************************************************************/
#include "platform.h"
#ifdef BSP_MCU_RX11_ALL
#ifndef BSP_MCU_RX110
#include "r_flash_common_rx100.h"
#include "r_dataflash_rx100.h"
#include "r_flash_rx100_if.h"


/******************************************************************************
Macro definitions
******************************************************************************/


/******************************************************************************
Private global variables and functions
******************************************************************************/
static r_dataflash_data_t  data_flash_info;
static r_dataflash_erase_t data_flase_erase_info;

static void r_df_write_fpmcr (uint8_t value);
static void r_df_delay_us (unsigned long us, unsigned long khz);


/*******************************************************************************
* Outline      : E2 Data Flash Access Enable
* Header       : r_dataflash_rx100.h
* Function Name: R_DF_Enable_DataFlashAccess
* Description  : Enable the E2 Data Flash Access and wait for the DataFlash STOP recovery time
* Arguments    : none
* Return Value : none
*******************************************************************************/
void R_DF_Enable_DataFlashAccess(void)
{

    /* E2 DataFlash Access enable */
    FLASH.DFLCTL.BIT.DFLEN = 1;

    if(1 == FLASH.DFLCTL.BIT.DFLEN)
     {
         nop();
     }

    /* Wait for 5us over (tDSTOP) */
    r_df_delay_us(WAIT_TDSTOP, ICLK_KHZ);

}

/*******************************************************************************
* Outline      : Transition to P/E mode
* Header       : r_dataflash_rx100.h
* Function Name: R_DF_Enter_PE_Mode
* Description  : Executes the sequence to enter P/E mode.
* Arguments    : none
* Return Value : None
*******************************************************************************/
void R_DF_Enter_PE_Mode(void)
{

    FLASH.FENTRYR.WORD = FENTRYR_DATAFLASH_PE_MODE;

    if (OPCCR_HIGH_SPEED_MODE == SYSTEM.OPCCR.BIT.OPCM)
    {
        r_df_write_fpmcr(DATAFLASH_PE_MODE);
    }
    else
    {
        r_df_write_fpmcr(DATAFLASH_PE_MODE | LVPE_MODE);
    }

    FLASH.FISR.BIT.PCKA = FCLK_MHZ - 1;
}

/*******************************************************************************
* Outline      : Transition to read mode
* Header       : r_dataflash_rx100.h
* Function Name: R_DF_Enter_Read_Mode
* Description  : Executes the sequence to enter read mode.
* Arguments    : None
* Return Value : None
*******************************************************************************/
void R_DF_Enter_Read_Mode(void)
{

    r_df_write_fpmcr(READ_MODE);

    /* Wait for 5us over (tMS) */
    r_df_delay_us(WAIT_TMS_HIGH, ICLK_KHZ);


    FLASH.FENTRYR.WORD = FENTRYR_READ_MODE;

    while (0x0000 != FLASH.FENTRYR.WORD)
    {
        /* Confirm that the written value can be read correctly. */
    }
}

/*******************************************************************************
* Outline      : Programming
* Header       : r_dataflash_rx100.h
* Function Name: R_DF_Write
* Description  : Programs the specified data to the E2 Data Flash data. Address validation
*                has already been performed by the caller.
* Arguments    : psrc_addr   : Start address of the (RAM) area which stores the programming data
*              : dest_addr   : Flash Start address which will be written
*              : byte_length : Number of bytes to write
* Return Value : None
*******************************************************************************/
void R_DF_Write(uint32_t *psrc_addr, const uint32_t dest_addr, const uint32_t byte_length )
{
    data_flash_info.start_addr = (uint32_t)psrc_addr;     // Ram Source for data to write
    data_flash_info.end_addr   = dest_addr;    // Flash Start address which will be written
    data_flash_info.write_cnt = byte_length / DATAFLASH_WRITE_LENGTH;  //  Number of bytes to write

    FLASH.FASR.BIT.EXS = 0;

    // Pass in Read form address
    R_DF_Write_Operation (psrc_addr, dest_addr);
}

/*******************************************************************************
* Outline      : Programming
* Header       : r_dataflash_rx100.h
* Function Name: R_DF_Write_Operation
* Description  : Programs the specified data to the E2 Data Flash data.
* Arguments    : block_start_addr   : Start address (read form) for erasing
*              : block_end_addr     : End address (read form) for erasing
* Return Value : none
*******************************************************************************/
void R_DF_Write_Operation (const uint32_t *psrc_addr,  const uint32_t dest_addr)
{
    uint32_t dest_addr_idx;

    dest_addr_idx = dest_addr - DATAFLASH_ADDR_OFFSET;  /* Conversion to the P/E address from the read address */
    //printf("R_DF_Write - addr: %x  data: %x\r\n",dest_addr, (uint8_t)(*psrc_addr & 0x00FF));

    /* Write start address setting */
     FLASH.FSARH = (uint8_t)((dest_addr_idx >> 16) & 0x0F);
     FLASH.FSARL = (uint16_t)(dest_addr_idx & 0xFFFF);

     /* Write data setting */
     FLASH.FWBH = (uint16_t)0x0000;
     FLASH.FWBL = (uint8_t)(*psrc_addr & 0x00FF);

     /* Execute Write command */
     FLASH.FCR.BYTE = FCR_WRITE;
}

/*******************************************************************************
* Outline      : Verifying write command execution
* Header       : r_dataflash_rx100.h
* Function Name: R_DF_Write_Check
* Description  : Waits for the write command to be completed
               : and verifies the result of the command execution.
* Arguments    : none
* Return Value : FLASH_SUCCESS       - Command executed successfully
*              : FLASH_ERR_BUSY      - Command being executed
*              : FLASH_ERR_TIMEOUT   - Command timed out
*              : FLASH_ERR_FAILURE   - Command failed for some reason
*******************************************************************************/
flash_err_t R_DF_Write_Check (void)
{
    flash_err_t status;

    /* Check FREADY Flag bit*/
    if (1 != FLASH.FSTATR1.BIT.FRDY)
    {
        return FLASH_ERR_BUSY;
    }

    /* Clear FCR register */
    FLASH.FCR.BYTE = FCR_CLEAR;

    while (0 != FLASH.FSTATR1.BIT.FRDY)
    {
        /* Check that execute command is completed. */
        /* Wait until FRDY is 1 unless timeout occurs. */
        if (g_current_parameters.wait_cnt-- <= 0)
        {
          /* if FRDY is not set to 0 after max timeout, return error*/
           return FLASH_ERR_TIMEOUT;
        }
    }

    if ((0 != FLASH.FSTATR0.BIT.ILGLERR) || (0 != FLASH.FSTATR0.BIT.PRGERR))
    {
        r_df_reset();
        status = FLASH_ERR_FAILURE;
    }
    else
    {
        data_flash_info.start_addr += DATAFLASH_WRITE_LENGTH;
        data_flash_info.end_addr += DATAFLASH_WRITE_LENGTH;;
        data_flash_info.write_cnt--;

        if (data_flash_info.write_cnt)
        {
            R_DF_Write_Operation((const uint32_t *)data_flash_info.start_addr, data_flash_info.end_addr);
            status = FLASH_ERR_BUSY;
        }
        else
        {
            status = FLASH_SUCCESS;
        }
    }

    return status;
}
/*******************************************************************************
* Outline      : Erasing
* Header       : r_dataflash_rx100.h
* Function Name: R_DF_Erase
* Description  : Performs block erasing between specified addresses. Address validation
*                has already been performed by the caller.
* Arguments    : start_addr   : Start address for erasing
*              : num_blocks   : # of blocks to erase
* Return Value : none
*******************************************************************************/
void R_DF_Erase (uint32_t start_addr, uint32_t num_blocks)
{

    data_flase_erase_info.start_addr = start_addr;
    data_flase_erase_info.end_addr   = start_addr+(num_blocks*BLOCK_SIZE);

    FLASH.FASR.BIT.EXS = 0;

    // Pass in Read form address
    R_DF_Erase_Operation (data_flase_erase_info.start_addr, data_flase_erase_info.end_addr);
}

/*******************************************************************************
* Outline      : Erasing
* Header       : r_dataflash_rx100.h
* Function Name: R_DF_Erase_Operation
* Description  : Performs block erasing between specified addresses.
* Arguments    : block_start_addr   : Start address (read form) for erasing
*              : block_end_addr     : End address (read form) for erasing
* Return Value : none
*******************************************************************************/
void R_DF_Erase_Operation (const uint32_t start_addr, const uint32_t end_addr)
{
    uint32_t block_start_addr;
    uint32_t block_end_addr;

    block_start_addr = start_addr - DATAFLASH_ADDR_OFFSET;  /* Conversion to the P/E address from the read address */
    block_end_addr   = block_start_addr + BLOCK_SIZE - 1;

    /* Erase start address setting */
    FLASH.FSARH = (uint8_t)((block_start_addr >> 16) & 0x0F);
    FLASH.FSARL = (uint16_t)(block_start_addr & 0xFFFF);

    /* Erase end address setting */
    FLASH.FEARH = (uint8_t)((block_end_addr >> 16) & 0x0F);
    FLASH.FEARL = (uint16_t)(block_end_addr & 0xFFFF);

    /* Execute Erase command */
    FLASH.FCR.BYTE = FCR_ERASE;
}

/*******************************************************************************
* Outline      : Verifying erase command execution
* Header       : r_dataflash_rx100.h
* Function Name: R_DF_Erase_Check
* Description  : Waits for the erase command to be completed
               : and verifies the result of the command execution.
* Arguments    : none
* Return Value : FLASH_SUCCESS       - Command executed successfully
*              : FLASH_ERR_BUSY      - BUSY status
*              : FLASH_ERR_TIMEOUT   - Erase command timed out
*              : FLASH_ERR_FAILURE   - Command failed for some reason
*******************************************************************************/
flash_err_t R_DF_Erase_Check (void)
{
    flash_err_t status;

    /* Check FREADY Flag bit*/
    if (1 != FLASH.FSTATR1.BIT.FRDY)
    {
        return FLASH_ERR_BUSY;
    }

    /* Clear FCR register */
    FLASH.FCR.BYTE = FCR_CLEAR;

    while (0 != FLASH.FSTATR1.BIT.FRDY)
    {
        /* Check that execute command is completed. */
        /* Wait until FRDY is 1 unless timeout occurs. */
        if (g_current_parameters.wait_cnt-- <= 0)
        {
          /* if FRDY is not set to 0 after max timeout, return error*/
           return FLASH_ERR_TIMEOUT;
        }
    }

    if ((0 != FLASH.FSTATR0.BIT.ILGLERR) || (0 != FLASH.FSTATR0.BIT.ERERR))
    {
        r_df_reset();
        status = FLASH_ERR_FAILURE;
    }
    else
    {
        /* Next Block */
        data_flase_erase_info.start_addr += BLOCK_SIZE;

        if(data_flase_erase_info.start_addr < data_flase_erase_info.end_addr)
        {
            R_DF_Erase_Operation(data_flase_erase_info.start_addr,data_flase_erase_info.end_addr);
            status = FLASH_ERR_BUSY;
        }
        else
        {
            status = FLASH_SUCCESS;
        }
    }

    return status;
}





/*******************************************************************************
* Outline      : Blank check
* Header       : r_dataflash_rx100.h
* Function Name: R_DF_BlankCheck
* Description  : Performs blank check for the area between specified addresses.
* Arguments    : start_addr   : Start address for blank check
*              : end_addr     : End address for blank check
* Return Value : FLASH_SUCCESS             - The checked addresses are all blank
*              : FLASH_ERR_FAILURE - Blank check error
*******************************************************************************/
void R_DF_BlankCheck(uint32_t start_addr, uint32_t end_addr)
{
    uint32_t start_addr_idx;
    uint32_t end_addr_idx;

    start_addr_idx = start_addr - DATAFLASH_ADDR_OFFSET;  /* Conversion to the P/E address from the read address */
    end_addr_idx   = end_addr - DATAFLASH_ADDR_OFFSET;    /* Conversion to the P/E address from the read address */

    FLASH.FASR.BIT.EXS = 0;

    /* BlankCheck start address setting */
    FLASH.FSARH = (uint8_t)((start_addr_idx >> 16) & 0x0F);
    FLASH.FSARL = (uint16_t)(start_addr_idx & 0xFFFF);

    /* BlankCheck end address setting */
    FLASH.FEARH = (uint8_t)((end_addr_idx >> 16) & 0x0F);
    FLASH.FEARL = (uint16_t)(end_addr_idx & 0xFFFF);

    /* Execute BlankCheck command */
    FLASH.FCR.BYTE = FCR_BLANKCHECK;


}
/*******************************************************************************
* Outline      : Blank check
* Header       : r_dataflash_rx100.h
* Function Name: R_DF_BlankCheck_Check
* Description  : Performs blank check for the area between specified addresses.
* Arguments    : none
* Return Value : FLASH_SUCCESS       - Command executed successfully, area is blank
*              : FLASH_ERR_BUSY      - Command being executed
*              : FLASH_ERR_TIMEOUT   - Command timed out
*              : FLASH_ERR_FAILURE   - Command failed for some reason or area
*                                      is not blank
*******************************************************************************/
flash_err_t R_DF_BlankCheck_Check (void)
{

    /* Check FREADY Flag bit*/
    if (1 != FLASH.FSTATR1.BIT.FRDY)
    {
        return FLASH_ERR_BUSY;
    }

    /* Clear FCR register */
    FLASH.FCR.BYTE = FCR_CLEAR;

    while (0 != FLASH.FSTATR1.BIT.FRDY)
    {
        /* Check that execute command is completed. */
        /* Wait until FRDY is 1 unless timeout occurs. */
        if (g_current_parameters.wait_cnt-- <= 0)
        {
          /* if FRDY is not set to 0 after max timeout, return error*/
           return FLASH_ERR_TIMEOUT;
        }
    }

    if (0 != FLASH.FSTATR0.BIT.ILGLERR)
    {
        r_df_reset();
        return FLASH_ERR_FAILURE;
    }

    if (0 != FLASH.FSTATR0.BIT.BCERR)           // Tested Flash Area is not blank
    {
        r_df_reset();
        return FLASH_ERR_FAILURE;             // Not really an error...
    }


    return FLASH_SUCCESS;
}
/*******************************************************************************
* Outline      : Terminate the command operation
* Header       : r_dataflash_rx100.h
* Function Name: R_DF_Terminate
* Description  : Forced Terminate erase command.
* Arguments    : none
* Return Value : FLASH_SUCCESS or FLASH_ERR_TIMEOUT
*******************************************************************************/
flash_err_t R_DF_Terminate (void)
{

    /* Terminate the command operation */
    FLASH.FCR.BIT.STOP = 1;

    /* Check FREADY Flag bit*/
    while (1 != FLASH.FSTATR1.BIT.FRDY)
    {
        /* Check that execute command is completed. */
    }

    /* Clear FCR register */
    FLASH.FCR.BYTE = FCR_CLEAR;

    while (0 != FLASH.FSTATR1.BIT.FRDY)
    {
        /* Check that execute command is completed. */
        /* Wait until FRDY is 1 unless timeout occurs. */
        if (g_current_parameters.wait_cnt-- <= 0)
        {
          /* if FRDY is not set to 0 after max timeout, return error*/
           return FLASH_ERR_TIMEOUT;
        }
    }
    return FLASH_SUCCESS;
}



/*******************************************************************************
* Outline      : Setting the FPMCR register
* Header       : r_dataflash_rx100.h
* Function Name: r_df_write_fpmcr
* Description  : Specifies the argument set to the FPMCR register by the program sequence.
* Arguments    : value     : Setting value for the FPMCR register
* Return Value : none
*******************************************************************************/
static void r_df_write_fpmcr (uint8_t value)
{
    FLASH.FPR = 0xA5;
    FLASH.FPMCR.BYTE = value;
    FLASH.FPMCR.BYTE = (uint8_t)~value;
    FLASH.FPMCR.BYTE = value;

    if(value == FLASH.FPMCR.BYTE)
    {
        nop();
    }

}

/*******************************************************************************
* Outline      : Flash reset
* Header       : r_dataflash_rx100.h
* Function Name: r_df_reset
* Description  : Resets the flash control circuit.
* Arguments    : none
* Return Value : none
*******************************************************************************/
void r_df_reset (void)
{
    /* Reset Flash */
    FLASH.FRESETR.BIT.FRESET = 1;
    FLASH.FRESETR.BIT.FRESET = 0;
}

/*******************************************************************************
* Outline      : Intrinsic function to specify the number of loops
* Header       : none
* Function Name: r_df_delay
* Description  : Wait processing that loops at a fixed five cycles.
* Arguments    : R1 : Waiting loop counter
* Return Value : none
*******************************************************************************/
#pragma inline_asm r_df_delay
static void r_df_delay  (unsigned long loop_cnt)
{
    BRA     ?+
    NOP
?:
    NOP
    SUB     #01H,R1
    BNE     ?-

}


/*******************************************************************************
* Outline      : Function that specifies the execution time
* Header       : none
* Function Name: r_df_delay_us
* Description  : The number of loops is calculated based on the execution time (Î¼s)
*              : and the sytem clock (ICLK) frequency, and the intrinsic function
*              : that specifies the number of loops is called.
* Arguments    : us  : Execution time
               : khz : ICLK frequency when calling the function
* Return Value : none
*******************************************************************************/
static void r_df_delay_us (unsigned long us, unsigned long khz)
{

    signed long loop_cnt; /* Argument of R_DELAY function */

    /* Calculation of a loop count */
    loop_cnt = us * khz;
    loop_cnt = (loop_cnt / 5000 );      /* Division about cycle of 1 loop */
    loop_cnt = loop_cnt - 4;            /* Overhead is reduced from a loop count. */

    /* R_DELAY function is performed when loop_cnt is 1 or more. */
    if(loop_cnt > 0)
    {
        r_df_delay((unsigned long)loop_cnt);
    }
}

#endif
#endif
/* end of file */

