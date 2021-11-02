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
* File Name    : rskrx62n.h
* H/W Platform : RSK+RX62N
* Description  : Board specific definitions for the RSK+RX62N.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 31.10.2011 1.00     First Release
***********************************************************************************************************************/

#ifndef RSKRX62N_H
#define RSKRX62N_H

/* Local defines */
#define LED_ON              (0)
#define LED_OFF             (1)
#define SET_BIT_HIGH        (1)
#define SET_BIT_LOW         (0)
#define SET_BYTE_HIGH       (0xFF)
#define SET_BYTE_LOW        (0x00)

/* Switches */
#define SW_ACTIVE           0
#define SW1                 PORT0.PORT.BIT.B0
#define SW2                 PORT0.PORT.BIT.B1
#define SW3                 PORT0.PORT.BIT.B7
#define SW1_DDR             PORT0.DDR.BIT.B0
#define SW2_DDR             PORT0.DDR.BIT.B1
#define SW3_DDR             PORT0.DDR.BIT.B7
#define SW1_ICR             PORT0.ICR.BIT.B0
#define SW2_ICR             PORT0.ICR.BIT.B1
#define SW3_ICR             PORT0.ICR.BIT.B7

/* LEDs */
#define LED0                PORT0.DR.BIT.B2
#define LED1                PORT0.DR.BIT.B3
#define LED2                PORT0.DR.BIT.B5
#define LED3                PORT3.DR.BIT.B4
#define LED0_DDR            PORT0.DDR.BIT.B2
#define LED1_DDR            PORT0.DDR.BIT.B3
#define LED2_DDR            PORT0.DDR.BIT.B5
#define LED3_DDR            PORT3.DDR.BIT.B4

/* Chip select. */
#define FLASH_CS            PORT3.DR.BIT.B1        // SSL0

#endif /* RSKRX62N_H */
