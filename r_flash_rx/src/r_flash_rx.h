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
* File Name    : r_flash_rx.h
* Description  : This is a private header file used internally by the FLASH API module. It should not be modified or
* 				 included by the user in their application.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description           
*         : 12.07.2014 1.00    First Release
***********************************************************************************************************************/

#ifndef RX_FLASH_API_PRIVATE_HEADER_FILE
#define RX_FLASH_API_PRIVATE_HEADER_FILE

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Tests to make sure the user configured the code correctly. */
/*
#if !defined(FLASH_MACRO) 
    #error "One of the required configuration options is not defined in r_flash_config.h!"
#endif
*/
#define USER_LOCKING_TYPE bsp_lock_t


/* 'size' parameter for RX600/RX200 flash_api_fcu_blankcheck.
 * The number of bytes checked by the smallest blank check is always the
 * smallest data flash programming size. */
#define BLANK_CHECK_SMALLEST         0
/* 'size' parameter for R_FlashDataAreaBlankCheck */
#define BLANK_CHECK_ENTIRE_BLOCK     1


/* Memory specifics for the each MCU group */
#if   defined(BSP_MCU_RX111)
    #include "./src/targets/rx111/r_flash_rx111.h"
#elif   defined(BSP_MCU_RX110)
    #include "./src/targets/rx110/r_flash_rx110.h"
#elif   defined(BSP_MCU_RX113)
    #include "./src/targets/rx113/r_flash_rx113.h"
#elif   defined(BSP_MCU_RX610)
    #include "./src/targets/rx610/r_flash_rx610.h"
#elif defined(BSP_MCU_RX621) || defined(BSP_MCU_RX62N)
    #include "./src/targets/rx62n/r_flash_rx62n.h"
#elif defined(BSP_MCU_RX62T)
    #include "./src/targets/rx62t/r_flash_rx62t.h"
#elif defined(BSP_MCU_RX62G)
    #include "./src/targets/rx62g/r_flash_rx62g.h"
#elif defined(BSP_MCU_RX630)
    #include "./src/targets/rx630/r_flash_rx630.h"
#elif defined(BSP_MCU_RX631) || defined(BSP_MCU_RX63N)
    #include "./src/targets/rx63n/r_flash_rx63n.h"
#elif defined(BSP_MCU_RX63T)
    #include "./src/targets/rx63t/r_flash_rx63t.h"
#elif defined(BSP_MCU_RX210)
    #include "./src/targets/rx210/r_flash_rx210.h"
#elif defined(BSP_MCU_RX21A)
    #include "./src/targets/rx21a/r_flash_rx21a.h"
#elif defined(BSP_MCU_RX220)
    #include "./src/targets/rx220/r_flash_rx220.h"
#elif defined(BSP_MCU_RX64M)
    #include "./src/targets/rx64m/r_flash_rx64m.h"
#else
    #error "!!! No 'targets' folder for this MCU Group !!!"
#endif

/* These functions are only used when BGO (non-blocking) mode is enabled */
#if ((FLASH_CFG_DATA_FLASH_BGO == 1) || (FLASH_CFG_CODE_FLASH_BGO == 1))
/* Callback function to call when flash erase is finished */
void FlashEraseDone(void);
/* Callback function to call when flash write is finished */
void FlashWriteDone(void);
/* Function to take care of flash errors */
void FlashError(void);
/* Callback function to call when flash blank check is finished. 'result'
   argument is 0 if block was blank and 1 if it was not */
void FlashBlankCheckDone(uint8_t result);
#endif


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

typedef enum
{
    FLASH_UNINITIALIZED = 0,
    FLASH_INITIALIZATION,
    FLASH_READY,
    FLASH_WRITING,
    FLASH_ERASING,
    FLASH_BLANKCHECK,
#if !defined(BSP_MCU_RX64M)
    FLASH_GETSTATUS,
    FLASH_LOCK_BIT
#endif
} flash_states_t;


typedef enum _current
{
 FLASH_CUR_INVALID,
 FLASH_CUR_IDLE,
 FLASH_CUR_CF_ERASE,
 FLASH_CUR_CF_WRITE,
 FLASH_CUR_CF_BGO_WRITE,
 FLASH_CUR_CF_BGO_ERASE,
 FLASH_CUR_DF_ERASE,
 FLASH_CUR_DF_BGO_ERASE,
 FLASH_CUR_DF_WRITE,
 FLASH_CUR_DF_BLANKCHECK,
 FLASH_CUR_DF_BGO_BLANKCHECK,
 FLASH_CUR_CF_BLANKCHECK,              // RX100 Series
#if defined(BSP_MCU_RX64M)
 FLASH_CUR_DF_BGO_WRITE,
 FLASH_CUR_FCU_INIT,
 FLASH_CUR_LOCKBIT_SET,
#endif


}flash_cur_t;

typedef struct _current_parameters
{
 uint32_t src_addr;                     // Source address for operation in progress
 uint32_t dest_addr;                    // Destination address for operation in progress
 uint32_t total_count;                  // total number of bytes to write/erase
 uint32_t current_count;                // bytes of total completed
 flash_cur_t current_operation;         // Operation in progress, ie. FLASH_CUR_CF_ERASE
 uint16_t min_pgm_size;                 // As defined for the part, usually differs for CF and DF
 uint32_t wait_cnt;                     // Worst case wait time for operation completion
#if defined(BSP_MCU_RX64M)
 bool bgo_enabled_df;
 bool bgo_enabled_cf;
#endif
}current_param_t;

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/
extern current_param_t g_current_parameters;            // Current operation parameters

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
#endif /* RX_FLASH_API_PRIVATE_HEADER_FILE */
