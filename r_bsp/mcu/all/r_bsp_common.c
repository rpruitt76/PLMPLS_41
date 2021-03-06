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
* Copyright (C) 2013 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_bsp_common.c
* Description  : Implements functions that apply to all r_bsp boards and MCUs.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 06.05.2013 1.00     First Release
*         * 26.03.2014 1.10     Added R_BSP_SoftwareDelay() function
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Get information about current board and MCU. */
#include "platform.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define OVERHEAD_LOOP_COUNT  4		// overhead of 20 cycles or 4 loops to call/return from delayWait() function.
#define CPU_CYCLES_PER_LOOP  5		// known number (5) of CPU cycles required to execute the delayWait() loop
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: R_BSP_GetVersion
* Description  : Returns the current version of this module. The version number is encoded where the top 2 bytes are the
*                major version number and the bottom 2 bytes are the minor version number. For example, Version 4.25
*                would be returned as 0x00040019.
* Arguments    : none
* Return Value : Version of this module.
***********************************************************************************************************************/
#pragma inline(R_BSP_GetVersion)
uint32_t R_BSP_GetVersion (void)
{
    /* These version macros are defined in platform.h. */
    return ((((uint32_t)R_BSP_VERSION_MAJOR) << 16) | (uint32_t)R_BSP_VERSION_MINOR);
}


/***********************************************************************************************************************
* Function Name: delayWait
* Description  : This asm loop executes a known number (5) of CPU cycles. If a value of '4' is passed
*                in as an argument, then this function would consume 20 CPU cycles before returning.
* Arguments    : loop_cnt - A single 32-bit value is provided as the number of loops to execute.
*              :
* Return Value : None
***********************************************************************************************************************/
#pragma inline_asm delayWait
static void delayWait (unsigned long loop_cnt)
{
    BRA ?+
    NOP
    ?:
    NOP		//Added to adjust timing.
    NOP
    SUB #01H, R1
    BNE ?-
}

/***********************************************************************************************************************
* Function Name: R_BSP_SoftwareDelay
* Description  : Delay the specified duration in units and return.
* Arguments    : uint32_t count  - the number of 'units' to delay
*              : bsp_delay_units_t units - the 'base' for the units specified. Valid values are:
*                BSP_DELAY_MICROSECS,  BSP_DELAY_MILLISECS, BSP_DELAY_SECS.
*                Accuracy is very good at millisecond and second level, less so at microsecond level simply due to the
*                overhead associated with implementing the call.
*                Note that there is an additional overhead of 20 cycles for the actual delayWait() function call and
*                return.
*
* Return Value : true if delay executed.
*                false if delay/units combination resulted in overflow/underflow
***********************************************************************************************************************/
bool R_BSP_SoftwareDelay(uint32_t delay, bsp_delay_units_t units)
{
    uint64_t loop_cnt;

    // Calculate the number of loops, accounting for the overhead of 20 cycles (4 loops at 5 cycles/loop)
    loop_cnt = (((uint64_t)delay * (uint64_t)BSP_ICLK_HZ) / (CPU_CYCLES_PER_LOOP * units)) - OVERHEAD_LOOP_COUNT;

#ifdef BSP_CFG_PARAM_CHECKING_ENABLE
    // Make sure the request is valid and did not result in an overflow
    if ((loop_cnt > 0xFFFFFFFF) || (loop_cnt == 0) || ((units != BSP_DELAY_MICROSECS) && (units != BSP_DELAY_MILLISECS) && (units != BSP_DELAY_SECS)))
            return(false);
#endif
    delayWait((uint32_t)loop_cnt);
    return(true);
}



