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
* File Name    : r_flash_common_rx100.h
* Description  : Header file for Flash common data
*                processing of E2 Code Flash.
* Limitation   : none
*******************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 17.07.2014 1.00     First Release
*******************************************************************************/
#ifndef R_FLASH_COMMON_RX100_H_
#define R_FLASH_COMMON_RX100_H_

/******************************************************************************
Includes <System Includes> , "Project Includes"
******************************************************************************/
#include "r_flash_rx_config.h"
#include "platform.h"



/******************************************************************************
Typedef definitions
******************************************************************************/
/*==== Wait Process definition ====*/
#define WAIT_TDIS       (3)
#define WAIT_TMS_MID    (4)
#define WAIT_TMS_HIGH   (6)
#define WAIT_TDSTOP     (6)

#define MHZ             (1000000)
#define KHZ             (1000)
#define FCLK_MHZ        ((BSP_FCLK_HZ + 999999) / MHZ)
#define ICLK_KHZ        (BSP_ICLK_HZ / KHZ)


/*==== Flash information ====*/
/* Used for CodeFlash */
#define CODEFLASH_WRITE_LENGTH              (4)
#define BLOCK_SIZE                          (0x0400)

#define CODEFLASH_READ_BASE_END_ADDR        (0xFFFFFFFF)
#define CODEFLASH_WRITE_BASE_END_ADDR       (0x0007FFFF)
#define CODEFLASH_ADDR_OFFSET    (CODEFLASH_READ_BASE_END_ADDR - CODEFLASH_WRITE_BASE_END_ADDR)

/* Used for DataFlash */
#define DATAFLASH_WRITE_LENGTH              (1)

#define DATAFLASH_READ_BASE_END_ADDR        (0x00101FFF)
#define DATAFLASH_WRITE_BASE_END_ADDR       (0x000F2FFF)
#define DATAFLASH_ADDR_OFFSET    (DATAFLASH_READ_BASE_END_ADDR - DATAFLASH_WRITE_BASE_END_ADDR)




#endif /* R_FLASH_COMMON_RX100_H_ */

/* End of File */
