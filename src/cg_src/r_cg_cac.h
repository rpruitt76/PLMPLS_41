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
* File Name    : r_cg_cac.h
* Version      : Code Generator for RX64M V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F564MLDxFB
* Tool-Chain   : CCRX
* Description  : This file implements device driver for CAC module.
* Creation Date: 2/2/2015
***********************************************************************************************************************/
#ifndef CAC_H
#define CAC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/* 
    CAC Control Register 0 (CACR0)
*/
/* Clock Frequency Measurement Enable (CFME) */
#define _00_CAC_DISABLE                     (0x00U) /* Clock frequency measurement is disabled */
#define _01_CAC_ENABLE                      (0x01U) /* Clock frequency measurement is enabled */

/*
    CAC Control Register 1 (CACR1)
*/
/* CACREF Pin Input Enable (CACREFE) */
#define _00_CAC_CACREF_PIN_DISABLE          (0x00U) /* CACREF pin input is disabled */
#define _01_CAC_CACREF_PIN_ENABLE           (0x01U) /* CACREF pin input is enabled */
/* Measurement Target Clock Select (FMCS[2:0]) */
#define _00_CAC_TARGET_CLOCK_MAIN_OSC       (0x00U) /* Main clock */
#define _02_CAC_TARGET_CLOCK_SUB_OSC        (0x02U) /* Sub-clock */
#define _04_CAC_TARGET_CLOCK_HOCO           (0x04U) /* HOCO clock */
#define _06_CAC_TARGET_CLOCK_LOCO           (0x06U) /* LOCO clock */
#define _08_CAC_TARGET_CLOCK_IWDTCLK        (0x08U) /* IWDTCLK clock */
#define _0A_CAC_TARGET_CLOCK_PCLKB          (0x0AU) /* Peripheral module clock (PCLKB) */
/* Timer Count Clock Source Select (TCSS[1:0]) */
#define _00_CAC_TIMER_CLOCK_SOURCE_1        (0x00U) /* No division */
#define _10_CAC_TIMER_CLOCK_SOURCE_4        (0x10U) /* x 1/4 clock */
#define _20_CAC_TIMER_CLOCK_SOURCE_8        (0x20U) /* x 1/8 clock */
#define _30_CAC_TIMER_CLOCK_SOURCE_32       (0x30U) /* x 1/32 clock */
/* Valid Edge Select (EDGES[1:0]) */
#define _00_CAC_VALID_EDGE_RISING           (0x00U) /* Rising edge */
#define _40_CAC_VALID_EDGE_FALLING          (0x40U) /* Falling edge */
#define _80_CAC_VALID_EDGE_BOTH             (0x80U) /* Both rising and falling edges */

/*
    CAC Control Register 2 (CACR2)
*/
/* Reference Signal Select (RPS) */
#define _00_CAC_REF_SIGNAL_EXTERNAL         (0x00U) /* CACREF pin input */
#define _01_CAC_REF_SIGNAL_INTERNAL         (0x01U) /* Internally generated signal */
/* Measurement Reference Clock Select (RSCS[2:0]) */
#define _00_CAC_REF_CLOCK_MAIN_OSC          (0x00U) /* Main clock */
#define _02_CAC_REF_CLOCK_SUB_OSC           (0x02U) /* Sub-clock */
#define _04_CAC_REF_CLOCK_HOCO              (0x04U) /* HOCO clock */
#define _06_CAC_REF_CLOCK_LOCO              (0x06U) /* LOCO clock */
#define _08_CAC_REF_CLOCK_IWDTCLK           (0x08U) /* IWDTCLK clock */
#define _0A_CAC_REF_CLOCK_PCLKB             (0x0AU) /* Peripheral module clock (PCLKB) */
/* Reference Signal Generation Clock Frequency Division Ratio Select (RCDS[1:0]) */
#define _00_CAC_REF_CLOCK_SOURCE_32         (0x00U) /* x 1/32 clock */
#define _10_CAC_REF_CLOCK_SOURCE_128        (0x10U) /* x 1/128 clock */
#define _20_CAC_REF_CLOCK_SOURCE_1024       (0x20U) /* x 1/1024 clock */
#define _30_CAC_REF_CLOCK_SOURCE_8192       (0x30U) /* x 1/8192 clock */
/* Digital Filter Selection (DFS[1:0]) */
#define _00_CAC_DIGITAL_FILTER_DISABLED     (0x00U) /* Digital filtering is disabled */
#define _40_CAC_DIGITAL_FILTER_DIV_1        (0x40U) /* Digital filter sampling is at frequency measuring clock / 1 */
#define _80_CAC_DIGITAL_FILTER_DIV_4        (0x80U) /* Digital filter sampling is at frequency measuring clock / 4 */
#define _C0_CAC_DIGITAL_FILTER_DIV_16       (0xC0U) /* Digital filter sampling is at frequency measuring clock / 16 */

/*
    CAC Interrupt Control Register (CAICR)
*/
/* Frequency Error Interrupt Enable (FERRIE) */
#define _00_CAC_FERRIE_INTERRUPT_DISABLE    (0x00U) /* Frequency error interrupt is disabled */
#define _01_CAC_FERRIE_INTERRUPT_ENABLE     (0x01U) /* Frequency error interrupt is enabled */
/* Measurement End Interrupt Enable (MENDIE) */
#define _00_CAC_MENDIE_INTERRUPT_DISABLE    (0x00U) /* Measurement end interrupt is disabled */
#define _02_CAC_MENDIE_INTERRUPT_ENABLE     (0x02U) /* Measurement end interrupt is enabled */
/* Overflow Interrupt Enable (OVFIE) */
#define _00_CAC_OVFIE_INTERRUPT_DISABLE     (0x00U) /* Overflow interrupt is disabled */
#define _04_CAC_OVFIE_INTERRUPT_ENABLE      (0x04U) /* Overflow interrupt is enabled */


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _002A_CAC_UPPER_LIMIT               (0x002AU)
#define _0026_CAC_LOWER_LIMIT               (0x0026U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_CAC_Create(void);
void R_CAC_Start(void);
void R_CAC_Stop(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif