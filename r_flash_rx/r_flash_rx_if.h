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
* Copyright (C) 2014 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_flash_rx_if.h
* Description  : This module provides the interface file to be included by the user when using the FLASH API
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description           
*           12.04.2014 1.00    First Release
*           24.11.2014 1.10    Enhanced non_fcu driver. Added timeout check, clearing of FLASH.FASR.BIT.EXS, and
*                              additional checking of .PRGERR
***********************************************************************************************************************/

#ifndef FLASH_INTERFACE_HEADER_FILE
#define FLASH_INTERFACE_HEADER_FILE

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Version Number of API. */
#define FLASH_RX_VERSION_MAJOR           (1)
#define FLASH_RX_VERSION_MINOR           (10)

/* Private header file for this MCU
 * Includes MCU specific definitions and API declaration*/
#include "platform.h"
/* User specific options for Flash API */
#include "r_flash_rx_config.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/* Flash API error codes */
typedef enum _flash_err
{
    FLASH_SUCCESS = 0,
    FLASH_ERR_BUSY,             // Peripheral Busy
    FLASH_ERR_ACCESSW,          // Access window error
    FLASH_ERR_FAILURE,          // Operation failure, Programming or erasing error due to something other than lock bit
    FLASH_ERR_CMD_LOCKED,       // RX64M - Peripheral in command locked state
    FLASH_ERR_LOCKBIT_SET,      // RX64M - Pgm/Erase error due to lock bit.
    FLASH_ERR_FREQUENCY,        // RX64M - Illegal Frequency value attempted (4-60Mhz)
    FLASH_ERR_ALIGNED,          // RX600/RX200 - The address that was supplied was not on aligned correctly for ROM or DF
    FLASH_ERR_BOUNDARY,         // RX600/RX200 - Writes cannot cross the 1MB boundary on some parts
    FLASH_ERR_OVERFLOW,         // RX600/RX200 - Address + number of bytes' for this operation went past the end of this memory area.
    FLASH_ERR_BYTES,            // Invalid number of bytes passed
    FLASH_ERR_ADDRESS,          // Invalid address or address not on a programming boundary
    FLASH_ERR_BLOCKS,           // The "number of blocks" argument is invalid
    FLASH_ERR_PARAM,            // Illegal parameter
    FLASH_ERR_NULL_PTR,         // received null ptr; missing required argument
    FLASH_ERR_TIMEOUT,          // Timeout Condition
} flash_err_t;

/*Commands supported by the R_FLASH_Control function*/
typedef enum _flash_cmd
{
    /* All MCUs */
    FLASH_CMD_RESET,
    FLASH_CMD_STATUS_GET,

    // RX100 Commands
    FLASH_CMD_ACCESSWINDOW_SET,             // RX100 - Sets the Access Window boundaries for Code Flash
    FLASH_CMD_ACCESSWINDOW_GET,             // RX100 - Returns the Access Window boundaries for Code Flash
    FLASH_CMD_SWAPFLAG_TOGGLE,              // RX100 - Inverts the start-up program swap flag
    FLASH_CMD_SWAPFLAG_GET,                 // RX100 - Returns the current value of the start-up program swap flag(will swap take place on reset).
    FLASH_CMD_SWAPSTATE_GET,                // RX100 - Retrieves the current physical state of the start-up program area(which one is active).
    FLASH_CMD_SWAPSTATE_SET,                // RX100 - Swaps the start-up program areas without setting the start-up program swap flag.

    /* non-RX100 Commands */
    FLASH_CMD_LOCKBIT_WRITE,                // RX64M -
    FLASH_CMD_LOCKBIT_READ,
    FLASH_CMD_LOCKBIT_ENABLE,
    FLASH_CMD_LOCKBIT_DISABLE,
    FLASH_CMD_SET_BGO_CALLBACK,             // RX64M - Specify callback function for Flash ISR
    FLASH_CMD_CONFIG_OPTION_AND_SECURITY,
    FLASH_CMD_CONFIG_CLOCK,
    FLASH_CMD_LOCKBIT_PROTECTION,           // Enables or disables lock bit protection
    FLASH_CMD_LOCKBIT_PROGRAM               // Programs the lock bit for a specified ROM erasure block.

}flash_cmd_t;

/*Result type for certain operations*/
typedef enum _flash_res
{
    FLASH_RES_INVALID,                    // Invalid condition
    FLASH_RES_LOCKBIT_STATE_PROTECTED,    // RX64M - Result for FLASH_CMD_LOCKBIT_READ
    FLASH_RES_LOCKBIT_STATE_NON_PROTECTED,// RX64M - Result for FLASH_CMD_LOCKBIT_READ
    FLASH_RES_BLANK,                      // Return status for Blank Check Function
    FLASH_RES_NOT_BLANK                   // Return status for Blank Check Function
}flash_res_t;

typedef enum _flash_type
{
    FLASH_TYPE_CODE_FLASH = 0,
    FLASH_TYPE_DATA_FLASH,
    FLASH_TYPE_INVALID
}flash_type_t;


/*RX64M Event type returned by the ISR callback when used in BGO mode*/
typedef enum _flash_interrupt_event
{
    FLASH_INT_EVENT_INITIALIZED,
    FLASH_INT_EVENT_ERASE_COMPLETE,
    FLASH_INT_EVENT_WRITE_COMPLETE,
    FLASH_INT_EVENT_BLANK,
    FLASH_INT_EVENT_NOT_BLANK,
    FLASH_INT_EVENT_ERR_DF_ACCESS,
    FLASH_INT_EVENT_ERR_CF_ACCESS,
    FLASH_INT_EVENT_ERR_CMD_LOCKED,
    FLASH_INT_EVENT_ERR_LOCKBIT_SET,
    FLASH_INT_EVENT_ERR_FAILURE
}flash_interrupt_event_t;



#if defined(BSP_MCU_SERIES_RX100) || defined(BSP_MCU_RX231)
/*******************************************************************************************
 *   RX100 series and RX231 MCU specific control command structures                        *
 *                                                                                         *
 ******************************************************************************************/
#include "..\src\non_fcu\rx100\r_flash_rx100_if.h"

/* Config struct to be used with R_Flash_Control for FLASH_CMD_ACCESSWINDOW_SET command*/
typedef struct _flash_access_window_config
{
    uint32_t start_addr;                  // start address of Access Window Setting
    uint32_t end_addr;                    // end address of Access Window Setting
}flash_access_window_config_t;

typedef enum _start_up_select_type
{
    STARTUP_AREA_TEMPORARY_DEFAULT = 2,
    STARTUP_AREA_TEMPORARY_ALTERNATE,
}start_up_select_type;

#elif defined(BSP_MCU_RX63_ALL) || defined(BSP_MCU_RX62_ALL) || defined(BSP_MCU_RX610) || defined(BSP_MCU_RX210) || defined(BSP_MCU_RX21A) || defined(BSP_MCU_RX220)
/*******************************************************************************************
 *  RX610, RX621, RX62N, RX62T, RX62G, RX630, RX631, RX63N, RX63T, RX210, RX21A, RX220 MCU *
 *  control command structures                                                             *
 *                                                                                         *
 ******************************************************************************************/
#include "r_flash_fcu_if.h"

typedef struct _flash_access_window_config
{
    uint16_t read_en_mask;
    uint16_t write_en_mask;             // Address of or in ROM erasure block to read the lock bit of
}flash_access_window_config_t;

typedef enum _flash_lock_bit
{
    FLASH_LOCK_BIT_SET = 0,
    FLASH_LOCK_BIT_NOT_SET,
}flash_lock_bit_t;

typedef struct _flash_read_lockbit_config
{
    uint32_t block_addr;             // Address of or in ROM erasure block to read the lock bit of
    flash_lock_bit_t  result;        // result of the read (FLASH_LOCK_BIT_SET, or FLASH_LOCK_BIT_NOT_SET)
}flash_read_lockbit_config_t;

typedef struct _flash_program_lockbit_config
{
    uint32_t block_addr;             // Address of, or address within ROM erasure block to program the lockbit
}flash_program_lockbit_config_t;

typedef struct _flash_lockbit_enable
{
    bool enable;                     // enable or disable lockbit
}flash_lockbit_enable_t;

#elif defined(BSP_MCU_RX64M)
/*******************************************************************************************
 *   RX64M MCU specific control command structures                                         *
 *                                                                                         *
 ******************************************************************************************/
#include "r_flash_fcu_64m_if.h"
/* Config struct to be used with R_Flash_Control for FLASH_CMD_LOCKBIT_WRITE and FLASH_CMD_LOCKBIT_READ command*/
typedef struct _flash_lockbit_config
{
    flash_block_address_t block_start_address;
    flash_res_t result;                     //Returned by API when using FLASH_CMD_LOCKBIT_READ
    uint32_t num_blocks;                    //Set by user for FLASH_CMD_LOCKBIT_WRITE
}flash_lockbit_config_t;

/* Config struct to be used with R_Flash_Control for FLASH_CMD_BGO_ENABLE_DF command*/
typedef struct _flash_interrupt_config
{
    void (*pcallback)(void *);
    uint8_t int_priority;
}flash_interrupt_config_t;

/*Event type for ISR callback*/
typedef struct
{
    flash_interrupt_event_t event;         //Which Flash event caused this interrupt
} flash_int_cb_args_t;

typedef union _flash_control_arg
{
    flash_lockbit_config_t lockbit_cmd;
    flash_interrupt_config_t bgo_cmd;
}flash_control_arg_t;

#endif






/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
flash_err_t R_FLASH_Open(void);
flash_err_t R_FLASH_Write(uint32_t src_address, uint32_t dest_address, uint32_t num_bytes);
flash_err_t R_FLASH_Erase(flash_block_address_t block_start_address, uint32_t num_blocks);
flash_err_t R_FLASH_BlankCheck(uint32_t address, uint32_t num_bytes, flash_res_t *blank_check_result);
flash_err_t R_FLASH_Control(flash_cmd_t cmd, void *pcfg);
uint32_t R_FLASH_GetVersion (void);
void R_FlashCodeCopy(void);

#endif /* FLASH_INTERFACE_HEADER_FILE */


