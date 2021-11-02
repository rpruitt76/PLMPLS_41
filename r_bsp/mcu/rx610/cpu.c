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
* File Name	   : cpu.c
* Description  : This module implements CPU specific functions. An example is enabling/disabling interrupts. 
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 14.03.2013 1.00     First Release
*         : 16.07.2013 1.10     Added bsp_register_protect_open() function.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Platform support. */
#include "platform.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* This macro is used to suppress compiler messages about a parameter not being used in a function. The nice thing
 * about using this implementation is that it does not take any extra RAM or ROM.
 */
#define INTERNAL_NOT_USED(p)        ((void)(p))

/***********************************************************************************************************************
Error checking
***********************************************************************************************************************/
#if !defined(__RENESAS__)
    #error "ERROR - Need to add compiler specific code in cpu.c"
#endif

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
* Function Name: R_BSP_InterruptsDisable
* Description  : Globally disable interrupts.
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void R_BSP_InterruptsDisable (void)
{
#if defined(__RENESAS__)
    /* Use the compiler intrinsic function to clear the I flag. This function is available with for the Renesas RX 
       compiler. This may need to be changed for other compilers. */
    clrpsw_i();
#endif
} 

/***********************************************************************************************************************
* Function Name: R_BSP_InterruptsEnable
* Description  : Globally enable interrupts.
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void R_BSP_InterruptsEnable (void)
{
#if defined(__RENESAS__)
    /* Use the compiler intrinsic function to set the I flag. This function is available with for the Renesas RX 
       compiler. This may need to be changed for other compilers. */
    setpsw_i();
#endif
} 

/***********************************************************************************************************************
* Function Name: R_BSP_CpuInterruptLevelRead
* Description  : Reads the processor interrupt priority level.
* Arguments    : none
* Return Value : The current processor IPL
***********************************************************************************************************************/
uint32_t R_BSP_CpuInterruptLevelRead (void)
{
#if defined(__RENESAS__)
    /* Use the compiler intrinsic function to read the CPU IPL. This function is available with for the Renesas RX 
       compiler. This may need to be changed for other compilers. */
    return (uint32_t)get_ipl();
#endif
}

/***********************************************************************************************************************
* Function Name: R_BSP_CpuInterruptLevelWrite
* Description  : Writes the processor interrupt priority level.
* Arguments    : level -
*                    The level to set the processor's IPL to.
* Return Value : true -
*                    The level was set successfully.
*                false -
*                    Invalid level input. 
***********************************************************************************************************************/
bool R_BSP_CpuInterruptLevelWrite (uint32_t level)
{
#if (BSP_CFG_PARAM_CHECKING_ENABLE == 1)
    /* Check for valid level. */
    if (level > BSP_MCU_IPL_MAX)
    {
        return false;
    }
#endif

#if defined(__RENESAS__)
    /* Use the compiler intrinsic function to set the CPU IPL. This function is available with for the Renesas RX 
       compiler. This may need to be changed for other compilers. */
    set_ipl((signed long)level);
#endif

    return true;
}

/***********************************************************************************************************************
* Function Name: R_BSP_RegisterProtectEnable
* Description  : Enables register protection. Registers that are protected cannot be written to. Register protection is 
*                enabled by using the Protect Register (PRCR) and the MPC's Write-Protect Register (PWPR).
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void R_BSP_RegisterProtectEnable (bsp_reg_protect_t regs_to_protect)
{
    /* No registers to protect. */

    /* This code is only used to remove compiler info messages about this parameter not being used. */
    INTERNAL_NOT_USED(regs_to_protect);
}

/***********************************************************************************************************************
* Function Name: R_BSP_RegisterProtectDisable
* Description  : Disables register protection. Registers that are protected cannot be written to. Register protection is
*                disabled by using the Protect Register (PRCR) and the MPC's Write-Protect Register (PWPR).
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void R_BSP_RegisterProtectDisable (bsp_reg_protect_t regs_to_unprotect)
{
    /* No registers to protect. */

    /* This code is only used to remove compiler info messages about this parameter not being used. */
    INTERNAL_NOT_USED(regs_to_unprotect);
}

/***********************************************************************************************************************
* Function Name: bsp_register_protect_open
* Description  : Initializes variables needed for register protection functionality.
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void bsp_register_protect_open (void)
{
    /* No registers to protect. */
}

