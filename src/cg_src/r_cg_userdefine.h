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
* File Name    : r_cg_userdefine.h
* Version      : Code Generator for RX64M V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F564MLDxFB
* Tool-Chain   : CCRX
* Description  : This file includes user definition.
* Creation Date: 2/2/2015
***********************************************************************************************************************/
#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/
#define FAST_INTERRUPT_VECTOR 0

/* Start user code for function. Do not edit comment generated here */
extern unsigned char R_SCI5_Serial_Print( char str[], unsigned char task_cmd);
extern unsigned char R_SCI5_Serial_Rceive( char str[], unsigned char task_cmd);
extern unsigned char R_SCI5_Setup( void );
extern unsigned char R_SCI5_Enable( void );
extern unsigned char R_SCI5_Disable( void );
extern unsigned char R_SCI6_Serial_Print( char str[], unsigned char task_cmd);
unsigned char R_SCI6_SPI_Send( uint8_t str[], int wrtLen, uint8_t retStr[], int rdLen );
unsigned char R_SCI6_SPI_Receive( uint8_t str[], int wrtLen, uint8_t retStr[], int rdLen );
extern unsigned char R_SCI6_Serial_Rceive( char str[], unsigned char task_cmd);
extern unsigned char R_SCI6_Setup( void );
extern unsigned char R_SCI6_Enable( void );
extern unsigned char R_SCI6_Disable( void );
unsigned char R_SCI6_Setup( void );
unsigned char R_SCI6_Enable( void );
unsigned char R_SCI6_Disable( void );
/* End user code. Do not edit comment generated here */
#endif
