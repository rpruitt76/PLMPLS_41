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
*******************************************************************************/
/* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.   */
/*******************************************************************************
* File Name		: usb_fud.h
* Version 		: 1.00
* Device 		: Renesas RX630 (or generic)
* Tool Chain 	: HEW
* H/W Platform	: RSK Generic
* Description 	: Flash Update Routines
			Uses the USB MSD drivers
         Uses the Flash Api drivers
******************************************************************************/
/******************************************************************************
* History 		: 2012 Ver. 1.00 First Release
******************************************************************************/

#ifndef __fud_H__
#define __fud_H__

// ==================================================================
// Includes
#include <stdint.h>
#include "ram_disk.h"
#include "r_flash_rx_if.h"

// ==================================================================
// Classes/Structures

/// Defines Flash Updater States.
typedef enum 
{
   FudState_Idle,
   FudState_FileSector,
   FudState_WaitData,
   FudState_Programming,
   FudState_Finished,
   FudState_Error
} FudStates;

// ==================================================================
// Public Function Prototypes
void InitFud(void);

int ProcessFud(uint32_t _NumBytes, uint8_t* _pBuffer);

void TestFudReset(void);


//void SetFudState(FudStates newState);
void SetFudIdle(void);
void SetFudFileSector();
void SetFudProgramming(void);
void SetFudError(void);

FudStates GetFudState(void);

void JumpToApplication(void);
//void SoftReset(void);

// ==================================================================
// Macros

/// Reset Vector
#define		FL_TARGET_REST_VECT_ADDR		0xFFFFFFFCu

/// User Area for EraseAllFlash
/// - User area also always includes BLOCK_0 for FVT/Options
#define USER_FLASH_START_BLOCK   FLASH_CF_BLOCK_11
#define USER_FLASH_END_BLOCK     FLASH_CF_BLOCK_133

/// Boot area address
/// - Be sure these area match the blocks declared above
#define BOOT_ADDRESS_LOW         0xfffd8000
#define BOOT_ADDERSS_HIGH        0xfffdffff

#endif
