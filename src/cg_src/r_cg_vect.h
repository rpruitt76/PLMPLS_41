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
* File Name    : r_cg_vect.h
* Version      : Code Generator for RX64M V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F564MLDxFB
* Tool-Chain   : CCRX
* Description  : This file contains definition of vector.
* Creation Date: 2/2/2015
***********************************************************************************************************************/
#ifndef _VECT_H
#define _VECT_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/* Undefined */
#pragma interrupt (r_undefined_exception)
void r_undefined_exception(void);

/* Reserved */
#pragma interrupt (r_reserved_exception)
void r_reserved_exception(void);

/* NMI */
#pragma interrupt (r_nmi_exception)
void r_nmi_exception(void);

/* BRK */
#pragma interrupt (r_brk_exception(vect=0))
void r_brk_exception(void);

/* ICU GROUPBE0 */
#pragma interrupt (r_icu_group_be0_interrupt(vect=106))
void r_icu_group_be0_interrupt(void);

/* ICU GROUPBL0 */
#pragma interrupt (r_icu_group_bl0_interrupt(vect=110))
void r_icu_group_bl0_interrupt(void);

/* ICU GROUPBL1 */
#pragma interrupt (r_icu_group_bl1_interrupt(vect=111))
void r_icu_group_bl1_interrupt(void);

/* ICU GROUPAL0 */
#pragma interrupt (r_icu_group_al0_interrupt(vect=112))
void r_icu_group_al0_interrupt(void);

/* ICU GROUPAL1 */
#pragma interrupt (r_icu_group_al1_interrupt(vect=113))
void r_icu_group_al1_interrupt(void);

/*;<<VECTOR DATA START (POWER ON RESET)>> */
/*;Power On Reset PC */
extern void PowerON_Reset_PC(void);
/*;<<VECTOR DATA END (POWER ON RESET)>> */

#endif