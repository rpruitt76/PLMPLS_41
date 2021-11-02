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
 * File Name    : r_flash_rx_config_reference.h
 * Description  : Configures the FLASH API module for RX200 and RX600 Series MCU's.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 12.04.2014 1.00    First Release
***********************************************************************************************************************/
#ifndef FLASH_CONFIG_HEADER_FILE
#define FLASH_CONFIG_HEADER_FILE

/***********************************************************************************************************************
 Configuration Options
 ***********************************************************************************************************************/
/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING */
/* Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting
   Setting to 1 includes parameter checking; 0 compiles out parameter checking */
#define FLASH_CFG_PARAM_CHECKING_ENABLE     (1)


/******************************************************************************
 ENABLE BGO/NON-BLOCKING DATA FLASH OPERATIONS (non-RX110)
******************************************************************************/
/* Setting this to 0 will cause Data Flash operations to block and not return until
 * the operation is complete.
 * Setting to 1 places the API in 'BGO' mode. In this mode the Flash API routines
 * that deal with Data Flash will return after the operation has been started
 * instead of blocking until it is complete. For MCU devices that support a Flash
 * interrupt (ie RX63N), notification of the operation completion will be done
 * via the interrupt. For devices that do not support a Flash interrupt
 * (ie. RX111), the completion must be polled for using a Control command.  */
#define FLASH_CFG_DATA_FLASH_BGO   (0)


/******************************************************************************
 ENABLE CODE FLASH PROGRAMMING
******************************************************************************/
/* Setting to 1 configures the API such that code is included to program the User
 * ROM program area of Flash. Since this code must be executed from within RAM,
 * the sections 'PFRAM'(ROM) and 'RPFRAM'(RAM) must be added to the linker
 * settings. Also the linker option '-rom=PFRAM=RPFRAM' must be added.
   If this macro is not defined (commented out) then the user does not need to
   setup and initialize the PFRAM and RPFRAM sections.
   If you are only using Data Flash set this to 0 */

#define FLASH_CFG_CODE_FLASH_ENABLE (1)


/******************************************************************************
 ENABLE BGO/NON-BLOCKING CODE FLASH (ROM) OPERATIONS
******************************************************************************/
/* EXTRA CARE SHOULD BE TAKEN IF YOU ENABLE FLASH_CFG_ROM_BGO. SINCE
 PROGRAM/ERASE FUNCTIONS WILL BE NON-BLOCKING THE API WILL RETURN BEFORE THE
 ROM OPERATION HAS FINISHED. THIS MEANS THAT THE USER CODE THAT CALLS THE FLASH
 API FUNCTION MUST BE IN RAM OR EXTERNAL MEMORY. THIS WOULD ALSO MEAN THAT THE
 USER HAS TO RELOCATE THE INTERRUPT VECTOR TABLE TO SOMEWHERE OTHER THAN
 ROM OR DATA FLASH. IF THE USER ATTEMPTS TO ACCESS ROM DURING A ROM PROGRAM/
 ERASE OPERATION THE FLASH CONTROL UNIT WILL THROW AN ERROR.

 /* Setting this to 0 will cause Code Flash (ROM) operations to block and not
  * return until the operation is complete.
 * Setting to 1 places the API in 'BGO' mode. In this mode the Flash API routines
 * that deal with ROM will return after the operation has been started
 * instead of blocking until it is complete. For MCU devices that support a Flash
 * interrupt (ie RX63N), notification of the operation completion will be done
 * via the interrupt. For devices that do not support a Flash interrupt
 * (ie. RX111), the completion must be polled for using a Control command.
******************************************************************************/
#define FLASH_CFG_CODE_FLASH_BGO   (0)


/******************************************************************************
 SET IPL OF FLASH READY INTERRUPT (non-RX100)
******************************************************************************/
/* For MCU devices that support a Flash interrupt (ie RX63n), this
 * defines the interrupt priority level for that interrupt. */
#define FLASH_CFG_FLASH_READY_IPL  (5)


/******************************************************************************
 ENABLE OR DISABLE LOCK BIT PROTECTION (non-RX100)
******************************************************************************/
/* Each erasure block has a corresponding lock bit that can be used to
   protect that block from being programmed/erased after the lock bit is
   set. The use of lock bits can be used or ignored.
   Setting this to 1 will cause lock bits to be ignored and programs/erases to a
   block will not be limited.
   Setting this to 0 will cause lock bits to be used as the user configures through
   the Control command. This only applies to MCU's that implement Lock Bits (ie RX63N)
   and to ROM as the DF does not have lock bits. */
#define FLASH_CFG_IGNORE_LOCK_BITS  (1)


#endif /* FLASH_CONFIG_HEADER_FILE */

