/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2013, 2014 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_crc.h
* Version      : Code Generator for RX64M V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F564MLDxFB
* Tool-Chain   : CCRX
* Description  : This file implements device driver for CRC module.
* Creation Date: 2/2/2015
***********************************************************************************************************************/
#ifndef CRC_H
#define CRC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    CRC Control Register (CRCCR)
*/
/* CRC Generating Polynomial Switching (GPS[1:0]) */
#define _00_CRC_DISABLE                    (0x00U) /* disable CRC execution */
#define _01_CRC_8                          (0x01U) /* CRC-8 execution */
#define _02_CRC_16                         (0x02U) /* CRC-16 execution */
#define _03_CRC_CCITT                      (0x03U) /* CRC-CCITT execution */
/* CRC Calculation Switching (LMS) */
#define _00_CRC_LSB_FIRST                  (0x00U) /* Performs CRC for LSB-first communication */
#define _04_CRC_MSB_FIRST                  (0x04U) /* Performs CRC for MSB-first communication */
/* CRCDOR Register Clear (DORCLR) */
#define _80_CRC_CLEAR_CRCDOR               (0x80U) /* Performs CRC for MSB-first communication */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
    CRC_LSB = 0U, 
    CRC_MSB
} crc_bitorder;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_CRC_SetCRC16(crc_bitorder order);
void R_CRC_Input_Data(uint8_t data);
void R_CRC_Get_Result(uint16_t * const result);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif