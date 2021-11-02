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
* File Name    : mcu_init.c
* Description  : Performs initialization common to all MCUs in this Group
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 07.05.2013 1.00     First Release
*         : 25.06.2013 1.10     Updated for v1.00 of HW manual. Ports H & J and 40-pin package were added.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Get specifics on this MCU. */
#include "platform.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* RX MCUs come in different packages and different pin counts. For MCUs that do not have the maximum number of pins
 * for their group (e.g. MCU with 100 pins when maximum is 144 pins) these 'non-existent' pins that are not bonded out
 * need to be initialized to save power. The macros below define the non-existent pins on each port for smaller
 * pin count MCUs. If a pin is non-existent then its value is set to a 1. These values are then ORed into the
 * direction registers to set non-existent pins as outputs which can help save power.
 */
#if   (BSP_PACKAGE_PINS == 64)
    /* Do nothing, this is the maximum number of pins. */
#elif (BSP_PACKAGE_PINS == 48)
    #define BSP_PRV_PORT0_NE_PIN_MASK     (0x28)    /* Missing pins: P03 P05 */
    #define BSP_PRV_PORT1_NE_PIN_MASK     (0x00)    /* Missing pins: None */
    #define BSP_PRV_PORT2_NE_PIN_MASK     (0x00)    /* Missing pins: None */
    #define BSP_PRV_PORT3_NE_PIN_MASK     (0x07)    /* Missing pins: P30 P31 P32 */
    #define BSP_PRV_PORT4_NE_PIN_MASK     (0x18)    /* Missing pins: P43 P44 */
    #define BSP_PRV_PORT5_NE_PIN_MASK     (0x30)    /* Missing pins: P54 P55 */
    #define BSP_PRV_PORTA_NE_PIN_MASK     (0x01)    /* Missing pins: PA0 */
    #define BSP_PRV_PORTB_NE_PIN_MASK     (0xC0)    /* Missing pins: PB6 PB7 */
    #define BSP_PRV_PORTC_NE_PIN_MASK     (0x00)    /* Missing pins: None */
    #define BSP_PRV_PORTE_NE_PIN_MASK     (0x60)    /* Missing pins: PE5 PE6 */
    #define BSP_PRV_PORTH_NE_PIN_MASK     (0x00)    /* Missing pins: None */
    #define BSP_PRV_PORTJ_NE_PIN_MASK     (0x00)    /* Missing pins: None */
#elif (BSP_PACKAGE_PINS == 40)
    #define BSP_PRV_PORT0_NE_PIN_MASK     (0x28)    /* Missing pins: P03 P05 */
    #define BSP_PRV_PORT1_NE_PIN_MASK     (0x00)    /* Missing pins: None */
    #define BSP_PRV_PORT2_NE_PIN_MASK     (0x00)    /* Missing pins: None */
    #define BSP_PRV_PORT3_NE_PIN_MASK     (0x03)    /* Missing pins: P30 P31 */
    #define BSP_PRV_PORT4_NE_PIN_MASK     (0x19)    /* Missing pins: P40 P43 P44 */
    #define BSP_PRV_PORT5_NE_PIN_MASK     (0x30)    /* Missing pins: P54 P55 */
    #define BSP_PRV_PORTA_NE_PIN_MASK     (0x01)    /* Missing pins: PA0 */
    #define BSP_PRV_PORTB_NE_PIN_MASK     (0xE2)    /* Missing pins: PB1 PB5 PB6 PB7 */
    #define BSP_PRV_PORTC_NE_PIN_MASK     (0xEF)    /* Missing pins: PC0 PC1 PC2 PC3 PC5 PC6 PC7 */
    #define BSP_PRV_PORTE_NE_PIN_MASK     (0xE0)    /* Missing pins: PE5 PE6 PE7 */
    #define BSP_PRV_PORTH_NE_PIN_MASK     (0x80)    /* Missing pins: PH7 */
    #define BSP_PRV_PORTJ_NE_PIN_MASK     (0x00)    /* Missing pins: None */
#elif (BSP_PACKAGE_PINS == 36)
    #define BSP_PRV_PORT0_NE_PIN_MASK     (0x28)    /* Missing pins: P03 P05 */
    #define BSP_PRV_PORT1_NE_PIN_MASK     (0x00)    /* Missing pins: None */
    #define BSP_PRV_PORT2_NE_PIN_MASK     (0x40)    /* Missing pins: P26 */
    #define BSP_PRV_PORT3_NE_PIN_MASK     (0x07)    /* Missing pins: P30 P31 P32 */
    #define BSP_PRV_PORT4_NE_PIN_MASK     (0x59)    /* Missing pins: P40 P43 P44 P46 */
    #define BSP_PRV_PORT5_NE_PIN_MASK     (0x30)    /* Missing pins: P54 P55 */
    #define BSP_PRV_PORTA_NE_PIN_MASK     (0x03)    /* Missing pins: PA0 PA1 */
    #define BSP_PRV_PORTB_NE_PIN_MASK     (0xE2)    /* Missing pins: PB1 PB5 PB6 PB7 */
    #define BSP_PRV_PORTC_NE_PIN_MASK     (0xEF)    /* Missing pins: PC0 PC1 PC2 PC3 PC5 PC6 PC7 */
    #define BSP_PRV_PORTE_NE_PIN_MASK     (0xE0)    /* Missing pins: PE5 PE6 PE7 */
    #define BSP_PRV_PORTH_NE_PIN_MASK     (0x80)    /* Missing pins: PH7 */
    #define BSP_PRV_PORTJ_NE_PIN_MASK     (0x00)    /* Missing pins: None */
#else
    #error "ERROR - This package is not defined in mcu_init.c"
#endif

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: bsp_non_existent_port_init
* Description  : For MCUs that do not have the maximum number of pins for their group (e.g. MCU with 100 pins when
*                maximum is 144 pins) these 'non-existent' pins that are not bonded out need to be initialized to save
*                power.
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void bsp_non_existent_port_init (void)
{
#if (BSP_PACKAGE_PINS != 64)
    /* OR in missing pin masks from above. */
    PORT0.PDR.BYTE |= BSP_PRV_PORT0_NE_PIN_MASK;
    PORT1.PDR.BYTE |= BSP_PRV_PORT1_NE_PIN_MASK;
    PORT2.PDR.BYTE |= BSP_PRV_PORT2_NE_PIN_MASK;
    PORT3.PDR.BYTE |= BSP_PRV_PORT3_NE_PIN_MASK;
    PORT4.PDR.BYTE |= BSP_PRV_PORT4_NE_PIN_MASK;
    PORT5.PDR.BYTE |= BSP_PRV_PORT5_NE_PIN_MASK;
    PORTA.PDR.BYTE |= BSP_PRV_PORTA_NE_PIN_MASK;
    PORTB.PDR.BYTE |= BSP_PRV_PORTB_NE_PIN_MASK;
    PORTC.PDR.BYTE |= BSP_PRV_PORTC_NE_PIN_MASK;
    PORTE.PDR.BYTE |= BSP_PRV_PORTE_NE_PIN_MASK;
    PORTH.PDR.BYTE |= BSP_PRV_PORTH_NE_PIN_MASK;
    PORTJ.PDR.BYTE |= BSP_PRV_PORTJ_NE_PIN_MASK;
#endif
}

