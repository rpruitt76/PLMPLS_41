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
* File Name    : hwsetup.c
* Device(s)    : RX
* H/W Platform : RSKRX113
* Description  : Defines the initialization routines used each time the MCU is restarted.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 14.02.2014 1.00     First release
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* I/O Register and board definitions */
#include "platform.h"

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* MCU I/O port configuration function declaration */
static void output_ports_configure(void);

/* Interrupt configuration function declaration */
static void interrupts_configure(void);

/* MCU peripheral module configuration function declaration */
static void peripheral_modules_enable(void);


/***********************************************************************************************************************
* Function name: hardware_setup
* Description  : Contains setup functions called at device restart
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
void hardware_setup(void)
{
    output_ports_configure();
    interrupts_configure();
    peripheral_modules_enable();
    bsp_non_existent_port_init();
}

/***********************************************************************************************************************
* Function name: output_ports_configure
* Description  : Configures the port and pin direction settings, and sets the pin outputs to a safe level.
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void output_ports_configure(void)
{
    /* Enable LEDs. */
    /* Start with LEDs off. */
    LED0 = LED_OFF;
    LED1 = LED_OFF;
    LED2 = LED_OFF;
    LED3 = LED_OFF;

    /* Set LED pins as outputs. */
    LED0_PDR = 1;
    LED1_PDR = 1;
    LED2_PDR = 1;
    LED3_PDR = 1;

    /* Enable switches. */
    /* Set pins as inputs. */
    SW1_PDR = 0;
    SW2_PDR = 0;
    SW3_PDR = 0;

    /* Set port mode registers for switches. */
    SW1_PMR = 0;
    SW2_PMR = 0;
    SW3_PMR = 0;
    
    /* Unlock MPC registers to enable writing to them. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC);
    
    /* TXD1 is output. */
    PORT1.PMR.BIT.B6 = 0;
    MPC.P16PFS.BYTE  = 0x0A;
    PORT1.PDR.BIT.B6 = 1;
    PORT1.PMR.BIT.B6 = 1;
    /* RXD1 is input. */
    PORT1.PMR.BIT.B5 = 0;
    MPC.P15PFS.BYTE  = 0x0A;    
    PORT1.PDR.BIT.B5 = 0;
    PORT1.PMR.BIT.B5 = 1;
        
    /* Configure the pin connected to the ADC Pot as an input */
    PORT4.PMR.BIT.B0 = 0;
    MPC.P40PFS.BYTE = 0x80;     //Set ASEL bit and clear the rest
    PORT4.PDR.BIT.B0 = 0;
    // for analog, leave PMR at 0

    /* Lock MPC registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC);
}

/***********************************************************************************************************************
* Function name: interrupts_configure
* Description  : Configures interrupts used
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void interrupts_configure(void)
{
    /* Add code here to setup additional interrupts */
}

/***********************************************************************************************************************
* Function name: peripheral_modules_enable
* Description  : Enables and configures peripheral devices on the MCU
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void peripheral_modules_enable(void)
{
    /* Add code here to enable peripherals used by the application */
}
