/********************************************************************************************************************
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
* Copyright (C) 2014 Renesas Electronics Corporation. All rights reserved.
********************************************************************************************************************/
/*******************************************************************************************************************
* File Name : r_flash_rx.c
* Description  : This module implements the Flash API layer functions for the RX1xx
********************************************************************************************************************/
/*******************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           12.11.2014 1.10    Support for RX110, RX111, RX113
*                              Changed WAIT_MAX_ROM_WRITE to WAIT_MAX_ERASE_DF_1K in flash_api_erase().
********************************************************************************************************************/

/********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"
#ifdef BSP_MCU_RX11_ALL
#include <machine.h>

#include "r_flash_rx_if.h"

/* Private header file for this package. */
#include "r_flash_rx100_if.h"
#include "r_flash_common_rx100.h"
#include "r_dataflash_rx100.h"
#include "r_codeflash_rx100.h"
#include "r_codeflash_extra_rx100.h"

/* include definition for NULL*/
#include <stddef.h>


/*********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
BSP_CFG_USER_LOCKING_TYPE g_GetStatus_Lock;         // GetStatus command software lock

/*********************************************************************************************************************
 External variables and functions
 *********************************************************************************************************************/
extern flash_states_t g_flash_state;

flash_err_t flash_lock_state (flash_states_t new_state);
#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
#pragma section FRAM
#endif

/***********************************************************************************************************************
* Function Name: flash_api_open
* Description  : Function will initialize the flash for the RX100 family.
* Arguments    : void
* Return Value : FLASH_SUCCESS -
*                    API initialized successfully.
*                FLASH_ERR_BUSY
*                    API has already been initialized and another operation is ongoing.
*                FLASH_ERR_FAILURE
*                    Initialization failed.
*                    A RESET was performed on the Flash circuit to rectify any internal errors
***********************************************************************************************************************/
flash_err_t flash_api_open(void)
{

    /* Allow Initialization if not initialized or
     * if no operation is ongoing and re-initialization is desired */
    if ((FLASH_UNINITIALIZED == g_flash_state) || (FLASH_READY == g_flash_state))
    {
        if (FLASH_SUCCESS != flash_lock_state(FLASH_INITIALIZATION))
            {
                /* API already initialized */
                return FLASH_ERR_BUSY;
            }
    }

    /* Release state so other operations can be performed. */
    flash_release_state();

#ifndef BSP_MCU_RX110
    /* Make E2 DataFlash Access enable */
     R_DF_Enable_DataFlashAccess();
#endif

    return FLASH_SUCCESS;
}

/*****************************************************************************
* Function Name: flash_api_control()
* Description  : This function executes RX11 specific flash control commands.
*
* Arguments    : flash_cmd_t cmd -
*                 command.
*                void *pcfg -
*                 Pointer to configuration. This argument can be NULL for
*                 commands that do not require a configuration.
*
*                Command                                |   Argument
*                FLASH_CMD_RESET------------------------| NULL
*                FLASH_CMD_STATUS_GET-------------------| NULL
*                FLASH_CMD_ACCESSWINDOW_SET----------------| void (*pAccessInfo)(void *)
*                FLASH_CMD_ACCESSWINDOW_GET---------------|  void (*pAccessInfo)(void *)
*                FLASH_CMD_SWAPFLAG_TOGGLE----------------| NULL
*                FLASH_CMD_SWAPFLAG_GET---------------| void (*uint32_t)(void *)
*
* Return Value : FLASH_SUCCESS -
*                    Operation completed successfully.
*                FLASH_ERR_FAILURE -
*                    Operation not available for this MCU
*                FLASH_ERR_ADRRESS -
*                    Address is an invalid Code/Data Flash block start address
*                FLASH_ERR_NULL_PTR -
*                    Pointer was NULL for a command that expects a configuration structure
*                FLASH_ERR_BUSY -
*                    Flash peripheral is busy with another operation or not initialized
******************************************************************************/
flash_err_t flash_api_control(flash_cmd_t cmd,  void  *pcfg)
{
    flash_err_t err = FLASH_SUCCESS;
    uint32_t *pSwapInfo = pcfg;
    flash_access_window_config_t  *pAccessInfo = pcfg;

    (void)&pSwapInfo;        /* Prevent compiler warning for not using 'pSwapInfo' AND not generate any code  */
    (void)&pAccessInfo;      /* Prevent compiler warning for not using 'pAccessInfo' AND not generate any code  */

    /*If the command is to reset the Flash, then no attempt is made to grab the lock
     * before executing the reset since the assumption is that the RESET command
     * is used to terminate any existing operation. */
    if (cmd == FLASH_CMD_RESET)
    {
        flash_release_state();
        flash_reset();           // reset the flash circuit
        return err;
    }

    if(g_flash_state != FLASH_READY)
    {
        // There is an operation in progress. If we don't have some form of BGO enabled, then this is an error.
#if (FLASH_CFG_DATA_FLASH_BGO == 0) && (FLASH_CFG_CODE_FLASH_BGO ==0)
       // In blocking mode we will return busy if the flash state is busy no matter what
        return FLASH_ERR_BUSY;  /* API not initialized or busy with another operation*/
#else
        // We are in polling/BGO mode. We may have an operation running in the background.
        // If that's the case then we need to be able to call GetStatus() to kick it along and complete
        // the original started operation. Therefore in this case we need to allow a FLASH_CMD_STATUS_GET
        // even when the g_flash_stat is not ready.
        if (cmd == FLASH_CMD_STATUS_GET)
        {
            // Use a software lock to insure no one sneaks in.
            if (flash_softwareLock(&g_GetStatus_Lock) != true)
                return FLASH_ERR_BUSY;

            err = flash_get_status();
            flash_softwareUnlock(&g_GetStatus_Lock);
            return err;
        }
#endif
     }



    switch (cmd)
    {
#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)

    case FLASH_CMD_SWAPFLAG_TOGGLE:                // Inverts the start-up program swap flag
        // This function is available in products with a 32-Kbyte or larger ROM
        if (BSP_ROM_SIZE_BYTES < 32768)
            return FLASH_ERR_FAILURE;
        err = R_CF_ToggleStartupArea();
        break;

    case FLASH_CMD_SWAPFLAG_GET:                   // Returns the the current value of the start-up program swap flag.
#if (FLASH_CFG_PARAM_CHECKING_ENABLE == 1)
        if ((pSwapInfo == NULL) || (pSwapInfo == FIT_NO_PTR))
        {
            return FLASH_ERR_NULL_PTR;
        }
#endif
        // This function is available in products with a 32-Kbyte or larger ROM
         if (BSP_ROM_SIZE_BYTES < 32768)
            return FLASH_ERR_FAILURE;
        *pSwapInfo = R_CF_GetCurrentStartupArea();
    break;

    case FLASH_CMD_SWAPSTATE_GET:                   // Retrieves the current physical state of the start-up program area(which one is active)..
        *pSwapInfo = R_CF_GetCurrentSwapState();

    break;

    case FLASH_CMD_SWAPSTATE_SET:                   // Swaps the start-up program areas without setting the start-up program swap flag.
        R_CF_SetCurrentSwapState((uint8_t)*pSwapInfo);
    break;



        // When providing block numbers, the start address is the larger block number (lower address)
        //        access_info.start_addr =  (uint32_t)FLASH_CF_BLOCK_3;     // ie. This will allow writing block 3
        //        access_info.end_addr =  (uint32_t)(FLASH_CF_BLOCK_2);
        //        access_info.start_addr =  (uint32_t)FLASH_CF_BLOCK_8;     // ie. This will allow writing blocks 3 - 8
        //        access_info.end_addr =  (uint32_t)(FLASH_CF_BLOCK_2);
        //        any address in the block can also be provided, it will map to the Block # in which it lives.
        //        ie. access_info.start_addr = (uint32_t)FLASH_CF_BLOCK_3 = 0xFFFFF000 or 0xFFFFF020, etc

    case FLASH_CMD_ACCESSWINDOW_SET:        // Works on full blocks only. Provide code block numbers or any address within a block
#if (FLASH_CFG_PARAM_CHECKING_ENABLE == 1)
        if ((pAccessInfo == NULL) || (pAccessInfo == FIT_NO_PTR))
        {
            return FLASH_ERR_NULL_PTR;
        }

        if ((pAccessInfo->start_addr > pAccessInfo->end_addr)  ||
            (pAccessInfo->start_addr < (uint32_t)FLASH_CF_LOWEST_VALID_BLOCK) ||
            (pAccessInfo->start_addr >= (uint32_t)FLASH_CF_BLOCK_END)    ||
            (pAccessInfo->end_addr < (uint32_t)FLASH_CF_LOWEST_VALID_BLOCK) ||
            (pAccessInfo->end_addr > (uint32_t)FLASH_CF_BLOCK_END))
            return(FLASH_ERR_ACCESSW);
#endif
        err = R_CF_SetAccessWindow(pAccessInfo);
    break;

    case FLASH_CMD_ACCESSWINDOW_GET:
        if ((pAccessInfo == NULL) || (pAccessInfo == FIT_NO_PTR))
        {
            return FLASH_ERR_NULL_PTR;
        }
        err = R_CF_GetAccessWindow(pAccessInfo);
    break;
#endif

    case FLASH_CMD_STATUS_GET:
        err = flash_get_status();
    break;

    default:
        err = FLASH_ERR_PARAM;
    }
    return err;
}


/*****************************************************************************
* Function Name: flash_api_write()
* Description  : This function executes RX11x specific functionality to write to
*                 the specified Code or Data Flash memory area.
*                Note that this function does not insure that the block(s) being written are blank.
*                If that information is required, R_FLASH_BlankCheck() should be used.
* Arguments    : uint32_t src_address -
*                 Source buffer address (data being written to Flash)
*                uint32_t dest_address -
*                 Destination address.
*                uint32_t num_bytes
*                 Number of bytes to be written
* Return Value : FLASH_SUCCESS -
*                    Write completed successfully; successfully initialized in case of BGO mode.
*                FLASH_ERR_BYTES -
*                    Number of bytes exceeds max range or is 0 or is not a valid multiple of the minimum programming
*                    size for the specified flash
*                FLASH_ERR_ADRRESS -
*                    src/dest address is an invalid Code/Data Flash block start address or
*                    address is not aligned with the minimum programming size for the Code/Data Flash
*                    For Code Flash programming the src address HAS to be a RAM address since ROM cannot be accessed
*                    during Code Flash programming
*                FLASH_ERR_BUSY -
*                    Flash peripheral is busy with another operation or not initialized
*                FLASH_ERR_FAILURE
*                    Flash Write operation failed for some other reason. This can be a result of trying to write to an area
*                    that has been protected via access control.
******************************************************************************/
flash_err_t flash_api_write(uint32_t src_address, uint32_t dest_address, uint32_t num_bytes)
{
    flash_err_t err;

    /*Check if API is busy*/
    if(g_flash_state != FLASH_READY)
    {
        /* API not initialized or busy with another operation*/
        return FLASH_ERR_BUSY;
    }

    /*Grab the current flash state*/
    if (FLASH_SUCCESS != flash_lock_state(FLASH_WRITING))
    {
        /* API busy with another operation*/
        return FLASH_ERR_BUSY;
    }


#if (FLASH_CFG_PARAM_CHECKING_ENABLE == 1)
    if (num_bytes == 0)
    {
        flash_release_state();
        return FLASH_ERR_BYTES;
    }

#endif

#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
    /*Check address validity and that it is on a Code Flash programming boundary*/
    // Ensure start address is valid and on 256 (for CF) byte boundary
    if (((dest_address >= (uint32_t)FLASH_CF_LOWEST_VALID_BLOCK)) &&  (!(dest_address & (FLASH_MIN_PGM_SIZE_CF-1))))
    {
        /*Check if there is enough space in the destination, and that num_bytes is a multiple of programming size*/
        if ((num_bytes-1 + (dest_address) > (uint32_t)FLASH_CF_BLOCK_END) ||
            (num_bytes & (FLASH_MIN_PGM_SIZE_CF-1)) ||
            (num_bytes-1 + (dest_address) < (uint32_t)FLASH_CF_BLOCK_INVALID))        // Overflowed
        {
            err = FLASH_ERR_BYTES;
        }
        else
        {
            /*There are no parameter errors. Switch to the CF PE mode*/
            err = flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH);
            g_current_parameters.current_operation = FLASH_CUR_CF_WRITE;
            g_current_parameters.wait_cnt = WAIT_MAX_ROM_WRITE;
        }

    }
#endif
#ifndef BSP_MCU_RX110       // RX110 has no DF

    /*Check address validity and that it is on a Data Flash programming boundary*/
    else if (((dest_address >= FLASH_DF_BLOCK_0) && (dest_address < FLASH_DF_BLOCK_INVALID ))
            &&
            (!(dest_address & (FLASH_MIN_PGM_SIZE_DF-1))))
    {

        /*Check if there is enough space in the destination, and that num_bytes is a multiple of programming size*/
        if ((num_bytes + (dest_address) > FLASH_DF_BLOCK_INVALID) || (num_bytes & (FLASH_MIN_PGM_SIZE_DF-1)))
        {
            err = FLASH_ERR_BYTES;
        }
        else
        {
            /*There are no parameter errors. Switch to the DF PE mode*/
            err = flash_pe_mode_enter(FLASH_TYPE_DATA_FLASH);
            g_current_parameters.current_operation = FLASH_CUR_DF_WRITE;
            g_current_parameters.wait_cnt = WAIT_MAX_DF_WRITE;
        }

    }
#endif
    else
    {
        err = FLASH_ERR_ADDRESS;
    }

    /*If parameters passed are not valid or there was an error entering PE mode,
     * then release the state and return the error condition*/
    if (FLASH_SUCCESS != err)
    {
        flash_release_state();
        return err;
    }

    /*Write the data*/
    err = flash_write(src_address, dest_address, num_bytes);
    if (FLASH_SUCCESS != err)
    {
        /*If there is an error, then reset the Flash circuit: This will clear error flags and exit the P/E mode*/
        flash_reset();
        /*Release the lock*/
        flash_release_state();
        return err;
    }


    /*If in non-BGO (Blocking) mode, then current operation is completed and the result is in result. Exit from PE mode and return status*/
#if (FLASH_CFG_CODE_FLASH_BGO == 0)
    if (g_current_parameters.current_operation == FLASH_CUR_CF_WRITE)
    {
        /*Return to read mode*/
        err = flash_pe_mode_exit();
        if (FLASH_SUCCESS != err)
        {
            /*Reset the Flash circuit: This will stop any existing processes and exit PE mode*/
            flash_reset();
        }
        /*Release lock and reset the state to Idle*/
        flash_release_state();
    }
#endif

#if (FLASH_CFG_DATA_FLASH_BGO == 0)
    if (g_current_parameters.current_operation == FLASH_CUR_DF_WRITE)
    {
        /*Return to read mode*/
        err = flash_pe_mode_exit();
        if (FLASH_SUCCESS != err)
        {
            /*Reset the Flash circuit: This will stop any existing processes and exit PE mode*/
            flash_reset();
        }
        /*Release lock and reset the state to Idle*/
        flash_release_state();
    }
#endif



    /*If BGO is enabled, then
     *return result of started Write process*/
    return err;
}


/***********************************************************************************************************************
* Function Name: flash_api_erase
* Description  : This function executes RX11x specific functionality to erase the specified Code or Data Flash blocks.
* Arguments    : uint32_t block_start_address -
*                 Start address of the first block. Actual address or entry from "flash_block_address_t" enum can be used
*                 Note - An additional 'feature' of the RX100 is that any address within a block may be specified and the
*                        entire contents of that block will be erased. The address supplied need not be on an Erase boundary
*                        or even an even boundary.
*                uint32_t num_blocks -
*                 Number of blocks to erase.
* Return Value : FLASH_SUCCESS -
*                    Erase completed successfully; successfully initialized in case of BGO mode.
*                FLASH_ERR_BLOCKS -
*                    Number of blocks exceeds max range or is 0
*                FLASH_ERR_ADRRESS -
*                    Start address is an invalid Code/Data Flash block start address
*                FLASH_ERR_BUSY -
*                    Flash peripheral is busy with another operation
*                FLASH_ERR_FAILURE
*                    Flash Write operation failed for some other reason. This can be a result of trying to erase an area
*                    that has been protected via access control.
***********************************************************************************************************************/
flash_err_t flash_api_erase(flash_block_address_t block_start_address, uint32_t num_blocks)
{
    flash_err_t err;

    /*Check if API is busy*/
    if(g_flash_state != FLASH_READY)
    {
        /* API not initialized or busy with another operation*/
        return FLASH_ERR_BUSY;
    }
    /*Grab the current flash state*/
    if (FLASH_SUCCESS != flash_lock_state(FLASH_ERASING))
    {
        /* API busy with another operation*/
        return FLASH_ERR_BUSY;
    }


#ifndef BSP_MCU_RX110       // RX110 has no DF
    if ((block_start_address >= FLASH_DF_BLOCK_0) && (block_start_address < FLASH_DF_BLOCK_INVALID ))
    {
        if ((num_blocks > FLASH_NUM_BLOCKS_DF) ||
            (num_blocks <= 0) ||
            ((num_blocks * FLASH_DF_BLOCK_SIZE)-1  + (block_start_address) >= (uint32_t)FLASH_DF_BLOCK_INVALID))        // Overflowed)
        {
            err = FLASH_ERR_BLOCKS;
        }
        else
        { /*No errors in parameters. Enter Data Flash PE mode*/
            err = flash_pe_mode_enter(FLASH_TYPE_DATA_FLASH);
            g_current_parameters.current_operation = FLASH_CUR_DF_ERASE;
            g_current_parameters.wait_cnt = WAIT_MAX_ERASE_DF_1K;
        }
    }
#endif

#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
#ifndef BSP_MCU_RX110       // RX110 has no DF
    else
#endif

    /*Check address and num_blocks validity and switch to Code Flash or Data Flash P/E mode*/
    if ((block_start_address <= FLASH_CF_BLOCK_0) && (block_start_address >= FLASH_CF_LOWEST_VALID_BLOCK))
    {
        if ((num_blocks >= FLASH_NUM_BLOCKS_CF) ||
            (num_blocks <= 0) ||
            ((num_blocks * FLASH_CF_BLOCK_SIZE)-1  + (block_start_address) < (uint32_t)FLASH_CF_BLOCK_INVALID))        // Overflowed

        {
            err = FLASH_ERR_BLOCKS;
        }
        else
        { /*No errors in parameters. Enter Code Flash PE mode*/
            err = flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH);
            g_current_parameters.current_operation = FLASH_CUR_CF_ERASE;
            g_current_parameters.wait_cnt = WAIT_MAX_ERASE_CF_1K;
        }
    }
#endif
    else
    {
        err = FLASH_ERR_ADDRESS;
    }

    if (FLASH_SUCCESS != err)
    {
        flash_release_state();
        return err;
    }


    /*Erase the Blocks*/
    err = flash_erase((uint32_t)block_start_address, num_blocks);
    if (FLASH_SUCCESS != err)
    {
        /*If there is an error, then reset the Flash circuit: This will clear error flags and exit the P/E mode*/
        flash_reset();
        flash_release_state();
        return err;
    }

    /*If in non-BGO (Blocking) mode, then current operation is completed and the result is in result. Exit from PE mode and return status*/
#if (FLASH_CFG_CODE_FLASH_BGO == 0)
    if (g_current_parameters.current_operation == FLASH_CUR_CF_ERASE)
    {
        /*Return to read mode*/
        err = flash_pe_mode_exit();
        if (FLASH_SUCCESS != err)
        {
            /*Reset the Flash circuit: This will stop any existing processes and exit PE mode*/
            flash_reset();
        }
        /*Release lock and reset the state to Idle*/
        flash_release_state();
    }
#endif

#if (FLASH_CFG_DATA_FLASH_BGO == 0)
    if (g_current_parameters.current_operation == FLASH_CUR_DF_ERASE)
    {
        /*Return to read mode*/
        err = flash_pe_mode_exit();
        if (FLASH_SUCCESS != err)
        {
            /*Reset the Flash circuit: This will stop any existing processes and exit PE mode*/
            flash_reset();
        }
        /*Release lock and reset the state to Idle*/
        flash_release_state();
    }
#endif



    /*If BGO is enabled, then return result of started Erase process*/
    return err;
}



/***********************************************************************************************************************
* Function Name: flash_api_blankcheck
* Description  : This function executes RX11x specific functionality to blank check the specified Flash area.
*                The function will incrementally check the area from the start address onward.
*                The minimum number of bytes is 4 for CF and 1 for DF.
*                The max is 256K for CF, 8192 for DF.
*                For parts that may support > 256K CF, then the address range provided may not span a 256K boundary.
*                For example: with a 512K part one could not specify a range of 255K - 257K even though that is
*                a 2K range. That would require two seperate BlankCheck calls. One for 255-256, one for 256-257
* Arguments    : uint32_t address -
*                 Start address to perform blank check. Actual address or entry from "flash_block_address_t" enum can be used
*                uint32_t num_blocks -
*                 Number of bytes to perform blank check operation for.
*                flash_res_t *result
*                 Returns the result of the blank check operation. This field is valid only in non-BGO mode
*                 operation
* Return Value : FLASH_SUCCESS
*                 Operation was completed successfully
*                FLASH_ERR_BYTES -
*                    Number of bytes exceeds max range (1-65535) or is not a multiple of the minimum
*                    Code or Data programming size.
*                FLASH_ERR_ADRRESS -
*                    Start address is an invalid Data Flash Address
*                FLASH_ERR_BUSY
*                    Flash peripheral is busy with another operation or not initialized
*                FLASH_ERR_FAILURE -
*                    Operation failed for some other reason.*
***********************************************************************************************************************/
flash_err_t flash_api_blankcheck(uint32_t address, uint32_t num_bytes, flash_res_t *result)
{
    flash_err_t err = FLASH_SUCCESS;

    /*Check if API is busy*/
    if(g_flash_state != FLASH_READY)
    {
        /* API not initialized or busy with another operation*/
        return FLASH_ERR_BUSY;
    }

    /*Grab the current flash state*/
    if (FLASH_SUCCESS != flash_lock_state(FLASH_BLANKCHECK))
    {
        /* API busy with another operation*/
        return FLASH_ERR_BUSY;
    }
#ifndef BSP_MCU_RX110       // RX110 has no DF
    if (((address >= FLASH_DF_BLOCK_0) && (address < FLASH_DF_BLOCK_INVALID )))
    {
        /*Check if the range is valid, num_bytes is a multiple of the programming size, is larger than 0 and less than 65536*/
        if (
                ((uint32_t)(num_bytes + address) > FLASH_DF_BLOCK_INVALID) ||
                (num_bytes & (FLASH_MIN_PGM_SIZE_DF-1)) ||
                (num_bytes == 0) ||
                (num_bytes > 8192)
        )
        {
            err = FLASH_ERR_BYTES;
        }
        else
        {
            /*There are no parameter errors. Switch to the CF PE mode*/
            err = flash_pe_mode_enter(FLASH_TYPE_DATA_FLASH);
            g_current_parameters.current_operation = FLASH_CUR_DF_BLANKCHECK;
            g_current_parameters.wait_cnt = WAIT_MAX_BLANK_CHECK;
        }
    }
#endif

#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
#ifndef BSP_MCU_RX110       // RX110 has no DF
    else
#endif
    if (((address <= ((uint32_t)FLASH_CF_BLOCK_0)) && (address >= (uint32_t)(FLASH_CF_LOWEST_VALID_BLOCK))))
    {
#if (BSP_ROM_SIZE_BYTES > 262144L)
        // For parts with ROM > 256K, Blankcheck requests may not span the 256K boundary
        // Is the address in the first 256K?
        if (address < (uint32_t)FLASH_CF_256KBOUNDARY) // for 384 part range is 0xFFFA0000 -  0xFFFFFFFF
        {
            if ((uint32_t)(address + num_bytes) > (uint32_t)FLASH_CF_256KBOUNDARY)
            {
                err = FLASH_ERR_ADRRESS;
            }
        }
       else
#endif
        /*Check if the range is valid, num_bytes is a multiple of 4, is larger than 0 and less than 65536*/
        if (
                ((uint32_t)((num_bytes-1) + address) < (uint32_t)FLASH_CF_LOWEST_VALID_BLOCK) ||
                (num_bytes & (FLASH_MIN_PGM_SIZE_CF-1)) ||
                (num_bytes == 0) ||
                (num_bytes > 0x40000)
        )
        {
            err = FLASH_ERR_BYTES;
        }
        else
        {
            /*There are no parameter errors. Switch to the CF PE mode*/
            err = flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH);
            g_current_parameters.current_operation = FLASH_CUR_CF_BLANKCHECK;
            g_current_parameters.wait_cnt = WAIT_MAX_BLANK_CHECK;
        }
    }
#endif
    else
    {
        err = FLASH_ERR_ADDRESS;
    }


    if (FLASH_SUCCESS != err)
    {
        flash_reset();
        flash_release_state();
        return err;
    }


    /*WAIT_MAX_BLANK_CHECK specifies the wait time for a 4 byte blank check,
     * num_bytes is divided by 4 and then multiplied to calculate the wait time for the entire operation*/
    g_current_parameters.wait_cnt = (WAIT_MAX_BLANK_CHECK * (num_bytes >> 2));


    /*Initialize the result*/
    *result = FLASH_RES_INVALID;

    /*Start the blankcheck operation*/

    err = flash_blankcheck(address, num_bytes, result);
    if (FLASH_SUCCESS != err)
    {
        /*If there is an error, then reset the flash circuit: This will clear error flags and exit the P/E mode*/
        flash_reset();
        flash_release_state();
        return err;
    }

    /*If in non-BGO (Blocking) mode, then current operation is completed and the result is in result. Exit from PE mode and return status*/
#if (FLASH_CFG_CODE_FLASH_BGO == 0)
    if (g_current_parameters.current_operation == FLASH_CUR_CF_BLANKCHECK)
    {
        /*Return to read mode*/
        err = flash_pe_mode_exit();
        if (FLASH_SUCCESS != err)
        {
            /*Reset the Flash circuit: This will stop any existing processes and exit PE mode*/
            flash_reset();
        }
        /*Release lock and reset the state to Idle*/
        flash_release_state();
    }
#endif

#if (FLASH_CFG_DATA_FLASH_BGO == 0)
    if (g_current_parameters.current_operation == FLASH_CUR_DF_BLANKCHECK)
    {
        /*Return to read mode*/
        err = flash_pe_mode_exit();
        if (FLASH_SUCCESS != err)
        {
            /*Reset the Flash circuit: This will stop any existing processes and exit PE mode*/
            flash_reset();
        }
        /*Release lock and reset the state to Idle*/
        flash_release_state();
    }
#endif

    /*If BGO is enabled, then return result of started Erase process*/
    return err;
}


/***********************************************************************************************************
* Function Name: flash_get_status
* Description  : Returns the current state of the flash
*                NOTE1: This function does not have to execute from in RAM. It must be in RAM though if
*                CF BGO is enabled and this function is called during a ROM P/E operation.
* Arguments    : none
* Return Value : FLASH_SUCCESS -
*                    Flash is ready to use
*                FLASH_ERR_BUSY -
*                    Flash is busy with another operation or is uninitialized
***********************************************************************************************************/
flash_err_t flash_get_status (void)
{
    flash_err_t err = FLASH_SUCCESS;

#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)

    if (FLASH_CUR_CF_ERASE  == g_current_parameters.current_operation)
    {
            err = R_CF_Erase_Check();
    }
    else
   if (FLASH_CUR_CF_WRITE  == g_current_parameters.current_operation)
    {
            err = R_CF_Write_Check();
    }
    else
    if (FLASH_CUR_CF_BLANKCHECK  == g_current_parameters.current_operation)
    {
            err = R_CF_BlankCheck_Check();
    }
#endif

#ifndef BSP_MCU_RX110       // RX110 has no DF

    if (FLASH_CUR_DF_ERASE == g_current_parameters.current_operation)
    {
            err = R_DF_Erase_Check();
    }
    else
    if (FLASH_CUR_DF_WRITE  == g_current_parameters.current_operation)
    {
            err = R_DF_Write_Check();
    }
    else
    if (FLASH_CUR_DF_BLANKCHECK  == g_current_parameters.current_operation)
    {
            err = R_DF_BlankCheck_Check();
    }
#endif

 if (err != FLASH_ERR_BUSY)
 {

    /*Release lock and Set current state to Idle*/
    flash_pe_mode_exit();
    flash_release_state();
 }

    return(err);
}

#endif

#pragma section // end FLASH_SECTION_ROM
