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
* File Name    : rskrx113.h
* H/W Platform : RSKRX113
* Description  : Board specific definitions for the RSKRX113.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 14.02.2014 1.00     First release
***********************************************************************************************************************/

#ifndef RSKRX113_H
#define RSKRX113_H

/* Local defines */
#define LED_ON              (0)
#define LED_OFF             (1)
#define SET_BIT_HIGH        (1)
#define SET_BIT_LOW         (0)
#define SET_BYTE_HIGH       (0xFF)
#define SET_BYTE_LOW        (0x00)

/* Switches */
#define SW_ACTIVE           0
#define SW1                 PORTJ.PIDR.BIT.B0
#define SW2                 PORT3.PIDR.BIT.B2
#define SW3                 PORT2.PIDR.BIT.B7
#define SW1_PDR             PORTJ.PDR.BIT.B0
#define SW2_PDR             PORT3.PDR.BIT.B2
#define SW3_PDR             PORT2.PDR.BIT.B7
#define SW1_PMR             PORTJ.PMR.BIT.B0
#define SW2_PMR             PORT3.PMR.BIT.B2
#define SW3_PMR             PORT2.PMR.BIT.B7

/* LEDs */
#define LED0                PORT2.PODR.BIT.B2
#define LED1                PORT2.PODR.BIT.B3
#define LED2                PORT2.PODR.BIT.B4
#define LED3                PORT2.PODR.BIT.B5
#define LED0_PDR            PORT2.PDR.BIT.B2
#define LED1_PDR            PORT2.PDR.BIT.B3
#define LED2_PDR            PORT2.PDR.BIT.B4
#define LED3_PDR            PORT2.PDR.BIT.B5

#endif /* RSKRX113_H */
