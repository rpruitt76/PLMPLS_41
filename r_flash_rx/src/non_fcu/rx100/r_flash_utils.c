/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_flash_rx11x.c
 * Description  : This module implements the RX11x specific sections of the FLASH API
 ***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 12.07.2014 1.00    First Release
***********************************************************************************************************************/

/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"
#ifdef BSP_MCU_RX11_ALL


/* Configuration for this package. */
#include "r_flash_rx_config.h"

/* Public interface header file for this package. */
#include "r_flash_rx_if.h"

/* Private header file for this package. */
#include "r_flash_rx100_if.h"

/* Private header file for this MCU */
//#include "r_flash_utils.h"

#include "r_flash_common_rx100.h"
#include "r_dataflash_rx100.h"
#include "r_codeflash_rx100.h"
#include "r_codeflash_extra_rx100.h"
/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: flash_codecopy
 * Description  : Copies Flash API code from ROM to RAM. This function needs to be called before any program/erase
 *     functions.
 *
 * Arguments    : none
 * Return Value : none
 * NOTE         : This function does not have to execute from in RAM.
 ***********************************************************************************************************************/
void flash_codecopy(void)
{

    /* Pointer to beginning of RAM section where API code will be copied to. */
    uint8_t * p_ram_section;
    /* Pointer to beginning of ROM section with API code. */
    uint8_t * p_rom_section;
    /* Number of bytes copied. */
    uint32_t bytes_copied;

    /* Initialize RAM section pointer. */
    p_ram_section = (uint8_t *) __sectop("RPFRAM");

    /* Initialize ROM section pointer. */
    p_rom_section = (uint8_t *) __sectop("PFRAM");

    /* Copy over code from ROM to RAM. */
    for (bytes_copied = 0; bytes_copied < __secsize("PFRAM"); bytes_copied++)
    {
        /* Copy over data 1 byte at a time. */
        p_ram_section[bytes_copied] = p_rom_section[bytes_copied];
    }

}


#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
/*All the functions below need to be placed in RAM if Code Flash programming is to be supported */
#pragma section FRAM
#endif


/***********************************************************************************************************************
 * Function Name: flash_clock_config
 * Description  : Function sets the internal FCu register to the current FCLK frequency
 * Arguments    : uint32_t : Specify current FCLK frequency
 * Return Value : FLASH_SUCCESS -
 *                Switched successfully.
 * NOTE         : Legal values are 4000000 - 60000000 (4 MHz to 60 MHz)
 ***********************************************************************************************************************/
flash_err_t flash_clock_config(uint32_t cur_fclk)
{
	/*Set the Clock*/
    FLASH.FISR.BIT.PCKA = (uint16_t)((0x1E00) + (cur_fclk/1000000));
	return FLASH_SUCCESS;
}
/***********************************************************************************************************************
 * Function Name: flash_pe_mode_enter
 * Description  : Function switches the peripheral to P/E mode for Code Flash or Data Flash.
 * Arguments    : flash_type_t : Specify Code Flash or Data Flash
 * Return Value : FLASH_SUCCESS -
 *                Switched successfully.
 *                FLASH_ERR_FAILURE -
 *                Unable to Switch to P/E Mode.
 *                FLASH_ERR_PARAM -
 *                Illegal parameter passed
 ***********************************************************************************************************************/
flash_err_t flash_pe_mode_enter(flash_type_t flash_type)
{
	flash_err_t err = FLASH_SUCCESS;

	if (flash_type == FLASH_TYPE_DATA_FLASH)
	{
#ifndef BSP_MCU_RX110       // RX110 has no DF
	    R_DF_Enter_PE_Mode();           // Sets PCKA clock
#endif
	}
#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
	else if (flash_type == FLASH_TYPE_CODE_FLASH)
	{
	    R_CF_Enter_PE_Mode();
	}
#endif
	else
	{
		err = FLASH_ERR_PARAM;
	}
	return err;
}





/***********************************************************************************************************************
 * Function Name: flash_erase
 * Description  : Function erases a block of Code or Data Flash
 ** Arguments   : uint32_t block address
 * Return Value : FLASH_SUCCESS -
 *                Block Erased successfully.
 *                FLASH_ERR_TIMEOUT
 *                Erase operation timed out.
 *                FLASH_ERR_FAILURE
 *                Erase operation failed for some other reason
 ***********************************************************************************************************************/
flash_err_t flash_erase(uint32_t block_address, uint32_t num_blocks)
{
	flash_err_t err = FLASH_SUCCESS;

    if (FLASH.FENTRYR.WORD == 0x0080)
	{
#ifndef BSP_MCU_RX110       // RX110 has no DF
        R_DF_Enter_PE_Mode();           // Sets PCKA clock

        // Write the actual registers for first block
        R_DF_Erase(block_address, num_blocks);  // Set the start and end and do first block

	    // If configured for Blocking mode then don't return until the entire operation is complete
#if (FLASH_CFG_DATA_FLASH_BGO == 0)
	    do
	    {
	        err = R_DF_Erase_Check();
	    }
	    while (FLASH_ERR_BUSY == err);
        R_DF_Enter_Read_Mode();         // We're done, return to read mode
#endif
#endif
	}
#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
    else if (FLASH.FENTRYR.WORD == 0x0001)
	{

        // Write the actual registers for first block
        R_CF_Erase(block_address, num_blocks);  // Set the start and end and do first block

        // If configured for Blocking mode then don't return until the entire operation is complete
#if (FLASH_CFG_CODE_FLASH_BGO == 0)
        do
        {
            err = R_CF_Erase_Check();
        }
        while (FLASH_ERR_BUSY == err);
        R_CF_Enter_Read_Mode();         // We're done, return to read mode
#endif

	}
#endif
    else
    {
        //should never get here
        return FLASH_ERR_FAILURE;
    }

	return err;
}


/***********************************************************************************************************************
 * Function Name: flash_write
 * Description  : Function writes of Code or Data Flash
 ** Arguments   : uint32_t src_address - the RAM area to take the data from
 **               uint32_t dest_address - the Flash address to write the data to
 **               uint32_t num - the count of bytes to write
 * Return Value : FLASH_SUCCESS -
 *                Block Erased successfully.
 *                FLASH_ERR_TIMEOUT
 *                Erase operation timed out.
 *                FLASH_ERR_FAILURE
 *                Erase operation failed for some other reason
 ***********************************************************************************************************************/
flash_err_t flash_write(uint32_t src_address, uint32_t dest_address, uint32_t num)
{
    flash_err_t err = FLASH_SUCCESS;
#if (FLASH_CFG_CODE_FLASH_BGO == 0) || (FLASH_CFG_DATA_FLASH_BGO == 0)
    flash_err_t status;
#endif

    if (FLASH.FENTRYR.WORD == 0x0080)
    {
#ifndef BSP_MCU_RX110       // RX110 has no DF
        R_DF_Enter_PE_Mode();           // Sets PCKA clock

        // Write the actual registers for first block
        R_DF_Write((uint32_t *)src_address, dest_address, num);  // Set the start and end and do first write

        // If configured for Blocking mode then don't return until the entire operation is complete
#if (FLASH_CFG_DATA_FLASH_BGO == 0)
        do
        {
            status = R_DF_Write_Check();
        }
        while (FLASH_ERR_BUSY == status);
        R_DF_Enter_Read_Mode();         // We're done, return to read mode
#endif
#endif
     }
#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
    else if (FLASH.FENTRYR.WORD == 0x0001)
    {
        R_CF_Enter_PE_Mode();

        R_CF_Write((uint32_t *)src_address, dest_address, num);  // Set the start and end and do first write
        // If configured for Blocking mode then don't return until the entire operation is complete

#if (FLASH_CFG_CODE_FLASH_BGO == 0)
        do
        {
            status = R_CF_Write_Check();
        }
        while (FLASH_ERR_BUSY == status);
        R_CF_Enter_Read_Mode();         // We're done, return to read mode
#endif

    }
#endif
    else
    {
        //should never get here
        return FLASH_ERR_FAILURE;
    }
    return err;
}
/***********************************************************************************************************************
 * Function Name: flash_blankcheck
 * Description  : Function checks if the specified Data Flash address range is blank
 * Arguments    : uint32_t address -
 *                 Start address to perform blank check. Actual address or entry from "flash_block_address_t" enum can be used
 *                uint32_t num_blocks -
 *                 Number of bytes to perform blank check operation for.
 *                flash_res_t *result
 *                 Returns the result of the blank check operation. This field is valid only in non-BGO mode
 *                  operation
 * Return Value : FLASH_ERR_TIMEOUT
 *                Operation timed out.
 *                FLASH_ERR_FAILURE
 *                Operation failure
 *                FLASH_SUCCESS
 *                Operation started successfully (BGO/polling)
 *                Operation completed (Blocking)
 ***********************************************************************************************************************/
flash_err_t flash_blankcheck(uint32_t start_address, uint32_t num_bytes, flash_res_t *result)
{
	flash_err_t err = FLASH_SUCCESS;
    (void)&err;        /* Prevent compiler warning for not using 'err' AND not generate any code  */

    if (FLASH.FENTRYR.WORD == 0x0080)
    {
#ifndef BSP_MCU_RX110       // RX110 has no DF
        R_DF_Enter_PE_Mode();           // Sets PCKA clock
        R_DF_BlankCheck (start_address, start_address+num_bytes-1);     // We want to blank check 0 - num_bytes-1
#if (FLASH_CFG_DATA_FLASH_BGO == 0)
        do
        {
            err = R_DF_BlankCheck_Check();
        }
        while (FLASH_ERR_BUSY == err);
        R_DF_Enter_Read_Mode();         // We're done, return to read mode

        // If we blocked until done then we have the result here
        if (err != FLASH_SUCCESS)
        {
            *result = FLASH_RES_NOT_BLANK;
        }
        else
        {
            *result = FLASH_RES_BLANK;
        }
#endif
#endif
    }
#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
    else if (FLASH.FENTRYR.WORD == 0x0001)
    {
        R_CF_Enter_PE_Mode();
        R_CF_BlankCheck (start_address, start_address+num_bytes-1);   // We want to blank check 0 - num_bytes-1
#if (FLASH_CFG_CODE_FLASH_BGO == 0)
        do
        {
            err = R_CF_BlankCheck_Check();
        }
        while (FLASH_ERR_BUSY == err);
        R_CF_Enter_Read_Mode();         // We're done, return to read mode

        // If we blocked until done then we have the result here
        if (err != FLASH_SUCCESS)
        {
            *result = FLASH_RES_NOT_BLANK;
        }
        else
        {
            *result = FLASH_RES_BLANK;
        }
#endif


    }
#endif

	return FLASH_SUCCESS;       // Always succeeds, blank status is in result
}




/***********************************************************************************************************************
 * Function Name: flash_pe_mode_exit
 * Description  : Exit PE mode to either DF or CF Read
 **********************************************************************************************************************/
flash_err_t flash_pe_mode_exit()
{

    if (FLASH.FENTRYR.WORD == 0x0080)
    {
#ifndef BSP_MCU_RX110       // RX110 has no DF
        R_DF_Enter_Read_Mode();
#endif
    }
#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
    else if (FLASH.FENTRYR.WORD == 0x0001)
    {
        R_CF_Enter_Read_Mode();
    }
#endif
    return(FLASH_SUCCESS);
}

/***********************************************************************************************************************
 * Function Name: flash_read_mode_exit
 * Description  : Exit read mode to CF or DF P/E mode
 ** Arguments   : uint32_t block address
 * Return Value : FLASH_SUCCESS -
 ***********************************************************************************************************************/
void flash_read_mode_exit()
{

    if (FLASH.FENTRYR.WORD == 0x0080)
    {
#ifndef BSP_MCU_RX110       // RX110 has no DF
        R_DF_Enter_PE_Mode();           // Sets PCKA clock
#endif

    }
#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)

    else if (FLASH.FENTRYR.WORD == 0x0001)
    {
        R_CF_Enter_PE_Mode();           // Sets PCKA clock
    }
#endif
}


/***********************************************************************************************************************
 * Function Name: flash_reset
 * Description  : Function resets the Flash peripheral
 ** Arguments   : None
 * Return Value : FLASH_SUCCESS -
 *                Flash circuit successfully reset.
 ***********************************************************************************************************************/
flash_err_t flash_reset() {

    /* Flash control circuit. */
     FLASH.FRESETR.BIT.FRESET = 1;
     FLASH.FRESETR.BIT.FRESET = 0;
   return FLASH_SUCCESS;
}

/***********************************************************************************************************************
* Function Name: flash_SoftwareLock
* Description  : Attempt to acquire the lock that has been sent in.
* Arguments    : plock -
*                    Pointer to lock structure with lock to try and acquire.
* Return Value : true -
*                    Lock was acquired.
*                false -
*                    Lock was not acquired.
***********************************************************************************************************************/
bool flash_softwareLock (BSP_CFG_USER_LOCKING_TYPE * const plock)
{
    bool ret = false;

    /* Variable used in trying to acquire lock. Using the xchg instruction makes this atomic */
    int32_t is_locked = true;

    /* Try to acquire semaphore to obtain lock */
    xchg(&is_locked, &plock->lock);

    /* Check to see if semaphore was successfully taken */
    if (is_locked == false)
    {
        /* Lock obtained, return success. */
        ret = true;
    }
    else
    {
        /* Lock was not obtained, another task already has it. */
    }

    return ret;
} /* End of function R_BSP_SoftwareLock() */

/***********************************************************************************************************************
* Function Name: flash_softwareUnlock
* Description  : Release hold on lock.
* Arguments    : plock -
*                    Pointer to lock structure with lock to release.
* Return Value : true -
*                    Lock was released.
*                false -
*                    Lock was not released.
***********************************************************************************************************************/
bool flash_softwareUnlock (BSP_CFG_USER_LOCKING_TYPE * const plock)
{
    /* Set lock back to unlocked. */
    plock->lock = false;

    return true;
} /* End of function R_BSP_SoftwareUnlock() */



#endif
