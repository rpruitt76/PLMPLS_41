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
* File Name    : rpbrx111.h
* H/W Platform : RPBRX111
* Description  : Board specific definitions for the RPBRX111.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 22.10.2013 1.00     First Release
***********************************************************************************************************************/

#ifndef RPBRX111_H
#define RPBRX111_H

/* Local defines */
#define LED_ON              (0)
#define LED_OFF             (1)
#define SET_BIT_HIGH        (1)
#define SET_BIT_LOW         (0)
#define SET_BYTE_HIGH       (0xFF)
#define SET_BYTE_LOW        (0x00)

/* Switches */
#define SW_ACTIVE           0
#define SW1                 PORTB.PIDR.BIT.B1
#define SW2                 PORTE.PIDR.BIT.B3
#define SW1_PDR             PORTB.PDR.BIT.B1
#define SW2_PDR             PORTE.PDR.BIT.B3
#define SW1_PMR             PORTB.PMR.BIT.B1
#define SW2_PMR             PORTE.PMR.BIT.B3

/* LEDs */
#define LED0                PORT0.PODR.BIT.B5
#define LED1                PORT4.PODR.BIT.B1
#define LED2                PORTB.PODR.BIT.B7
#define LED3                PORTB.PODR.BIT.B6
#define LED0_PDR            PORT0.PDR.BIT.B5
#define LED1_PDR            PORT4.PDR.BIT.B1
#define LED2_PDR            PORTB.PDR.BIT.B7
#define LED3_PDR            PORTB.PDR.BIT.B6

/* Pins to enable certain board functions. */
/* IDLE_EN is used to enable LEDs and switches. */
#define IDLE_EN             PORTE.PODR.BIT.B4
#define IDLE_EN_PDR         PORTE.PDR.BIT.B4
/* POT_EN is used to enable the potentiometer bias voltage. */
#define POT_EN              PORT0.PODR.BIT.B3
#define POT_EN_PDR          PORT0.PDR.BIT.B3

#endif /* RPBRX111_H */
