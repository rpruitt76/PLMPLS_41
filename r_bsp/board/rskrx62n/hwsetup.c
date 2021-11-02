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
* H/W Platform : RSK+RX62N
* Description  : Defines the initialization routines used each time the MCU is restarted.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 31.10.2011 1.00     First Release
*         : 07.05.2013 1.10     Added a call to bsp_non_existent_port_init() which initializes non-bonded out GPIO pins.
*         : 25.06.2013 1.20     Moved call to bsp_non_existent_port_init() in hardware_setup() to last so that user
*                               does not have to worry about writing 'missing' bits in PDR registers.
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
    LED0_DDR = 1;
    LED1_DDR = 1;
    LED2_DDR = 1;
    LED3_DDR = 1;

    /* Enable switches. */
    /* Set pins as inputs. */
    SW1_DDR = 0;
    SW2_DDR = 0;
    SW3_DDR = 0;

    /* Set Input Buffer Control registers for switches. */
    SW1_ICR = 1;
    SW2_ICR = 1;
    SW3_ICR = 1;

    /* Setup pins for on-board SPI flash. */
    /* Choose A pin group and enable RSPIB pins */    
    IOPORT.PFHSPI.BYTE = 0x0E;

    /* MISOB-A */
    PORT3.DDR.BIT.B0 = 0;
    PORT3.ICR.BIT.B0 = 1;
    /* SSLB0-A */
    PORT3.DR.BIT.B1  = 1;
    PORT3.DDR.BIT.B1 = 1;
    /* RSPCKB-A */
    PORT2.DR.BIT.B7  = 1;
    PORT2.DDR.BIT.B7 = 1;
    /* MOSIB-A */
    PORT2.DR.BIT.B6  = 1;
    PORT2.DDR.BIT.B6 = 1;

    /* Setup pins for on-board I2C EEPROM. */
    /* SDA0 */
    PORT1.DDR.BIT.B3 = 0;
    PORT1.ICR.BIT.B3 = 1;
    /* SCL0 */
    PORT1.DDR.BIT.B2 = 0;
    PORT1.ICR.BIT.B2 = 1;
    
    /* Configure the pin connected to the ADC Pot as an input */
    PORT4.DDR.BIT.B0 = 0;
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
