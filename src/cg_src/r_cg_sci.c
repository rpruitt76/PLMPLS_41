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
* File Name    : r_cg_sci.c
* Version      : Code Generator for RX64M V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F564MLDxFB
* Tool-Chain   : CCRX
* Description  : This file implements device driver for SCI module.
* Creation Date: 2/2/2015
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_sci.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_flash_rx_if.h"
#include <LaserP.h>
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"
#include "r_cg_port.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
uint8_t * gp_sci5_tx_address;               /* SCI5 transmit buffer address */
uint16_t  g_sci5_tx_count;                  /* SCI5 transmit data number */
uint8_t * gp_sci5_rx_address;               /* SCI5 receive buffer address */
uint16_t  g_sci5_rx_count;                  /* SCI5 receive data number */
uint16_t  g_sci5_rx_length;                 /* SCI5 receive data length */
volatile uint8_t * gp_sci6_tx_address;               /* SCI6 transmit buffer address */
volatile uint16_t  g_sci6_tx_count;                  /* SCI6 transmit data number */
volatile uint8_t * gp_sci6_rx_address;               /* SCI6 receive buffer address */
volatile uint16_t  g_sci6_rx_count;                  /* SCI6 receive data number */
volatile uint16_t  g_sci6_rx_length;                 /* SCI6 receive data length */
/* Start user code for global. Do not edit comment generated here */
uint8_t   gp_sci5_tx_errorType;             /* SCI5 Transmit Error Type */
uint8_t   gp_sci5_rx_errorType;             /* SCI5 Receive Error Type */
uint8_t   gp_sci5_tx_state = TX_NOINIT;     /* SCI5 Transmit State */
uint8_t   gp_sci5_rx_state = RX_NOINIT;     /* SCI5 Receive State */
char      gp_sci5_rx_string[RX_BUFFERSIZE];           /* SCI5 Buffer to receive characters */
int       gp_sci5_rx_stringcnt;             /* Count to number characters received */

uint8_t   gp_sci6_tx_errorType;             /* SCI6 Transmit Error Type */
uint8_t   gp_sci6_rx_errorType;             /* SCI6 Receive Error Type */
uint8_t   gp_sci6_tx_state = TX_NOINIT;     /* SCI6 Transmit State */
uint8_t   gp_sci6_rx_state = RX_NOINIT;     /* SCI6 Receive State */
char      gp_sci6_rx_string[RX_BUFFERSIZE];           /* SCI6 Buffer to receive characters */
int       gp_sci6_rx_stringcnt;             /* Count to number characters received */
volatile uint8_t	sci6_Tx_Complete;				// SCI6 Tx Complete.
volatile uint8_t	sci6_Rx_Complete;				// SCI6 RX Complete
volatile uint8_t	sci6_Error;						// SCI6 Error.
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_SCI5_Create
* Description  : This function initializes SCI5.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCI5_Create(void)
{
	int x;

    /* Cancel SCI5 module stop state */
    MSTP(SCI5) = 0U;

    /* Set interrupt priority */
    IPR(SCI5, RXI5) = _02_SCI_PRIORITY_LEVEL2;
    IPR(SCI5, TXI5) = _02_SCI_PRIORITY_LEVEL2;

    /* Clear the control register */
    SCI5.SCR.BYTE = 0x00U;

    /* Set clock enable */
    SCI5.SCR.BYTE = _00_SCI_INTERNAL_SCK_UNUSED;

    /* Clear the SIMR1.IICM, SPMR.CKPH, and CKPOL bit, and set SPMR */
    SCI5.SIMR1.BIT.IICM = 0U;
    //SCI5.SPMR.BYTE = _02_SCI_CTS | _00_SCI_CLOCK_NOT_INVERTED | _00_SCI_CLOCK_NOT_DELAYED;
    SCI5.SPMR.BYTE = _00_SCI_CLOCK_NOT_INVERTED | _00_SCI_CLOCK_NOT_DELAYED;

    /* Set control registers */
    SCI5.SMR.BYTE = _00_SCI_CLOCK_PCLK | _00_SCI_STOP_1 | _00_SCI_PARITY_EVEN | _00_SCI_PARITY_DISABLE | 
                    _00_SCI_DATA_LENGTH_8 | _00_SCI_MULTI_PROCESSOR_DISABLE | _00_SCI_ASYNCHRONOUS_MODE;
    SCI5.SCMR.BYTE = _00_SCI_SERIAL_MODE | _00_SCI_DATA_INVERT_NONE | _00_SCI_DATA_LSB_FIRST | 
                     _10_SCI_DATA_LENGTH_8_OR_7 | _62_SCI_SCMR_DEFAULT;
    SCI5.SEMR.BYTE = _00_SCI_LOW_LEVEL_START_BIT | _00_SCI_NOISE_FILTER_DISABLE | _00_SCI_16_BASE_CLOCK | 
    				 _40_SCI_BAUDRATE_DOUBLE | _00_SCI_BIT_MODULATION_DISABLE;

    /* Set bitrate */
    SCI5.BRR = 0x61U;

    /* Set RXD5 pin */
    MPC.PC2PFS.BYTE = 0x0AU;
    PORTC.PMR.BYTE |= 0x04U;

    /* Set TXD5 pin */
    PORTC.PODR.BYTE |= 0x08U;
    MPC.PC3PFS.BYTE = 0x0AU;
    PORTC.PMR.BYTE |= 0x08U;
    PORTC.PDR.BYTE |= 0x08U;

    /* Set CTS5# pin */
    //MPC.PC0PFS.BYTE = 0x0BU;
    //PORTC.PMR.BYTE |= 0x01U;

    // Clear buffer and count
    for(x = 0; x<RX_BUFFERSIZE; x++)
      gp_sci5_rx_string[x] = 0x00;
    gp_sci5_rx_stringcnt = 0;

}
/***********************************************************************************************************************
* Function Name: R_SCI5_Start
* Description  : This function starts SCI5.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCI5_Start(void)
{
    /* Clear interrupt flag */
    IR(SCI5,TXI5) = 0U;
    IR(SCI5,RXI5) = 0U;

    /* Enable SCI interrupt */
    IEN(SCI5,TXI5) = 1U;
    ICU.GENBL0.BIT.EN10 = 1U;
    IEN(SCI5,RXI5) = 1U;
    ICU.GENBL0.BIT.EN11 = 1U;
}
/***********************************************************************************************************************
* Function Name: R_SCI5_Stop
* Description  : This function stops SCI5.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCI5_Stop(void)
{
    PORTC.PMR.BYTE &= 0xF7U;
    SCI5.SCR.BIT.TE = 0U;      /* Disable serial transmit */
    SCI5.SCR.BIT.RE = 0U;      /* Disable serial receive */
    SCI5.SCR.BIT.TIE = 0U;     /* Disable TXI interrupt */
    SCI5.SCR.BIT.RIE = 0U;     /* Disable RXI and ERI interrupt */

    /* Disable SCI interrupt */
    IR(SCI5,TXI5) = 0U;
    IEN(SCI5,TXI5) = 0U;
    ICU.GENBL0.BIT.EN10 = 0U;
    IR(SCI5,RXI5) = 0U;
    IEN(SCI5,RXI5) = 0U;
    ICU.GENBL0.BIT.EN11 = 0U;
}
/***********************************************************************************************************************
* Function Name: R_SCI5_Serial_Receive
* Description  : This function receives SCI5 data.
* Arguments    : rx_buf -
*                    receive buffer pointer (Not used when receive data handled by DTC or DMAC)
*                rx_num -
*                    buffer size (Not used when receive data handled by DTC or DMAC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_SCI5_Serial_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (rx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_sci5_rx_count = 0U;
        g_sci5_rx_length = rx_num;
        gp_sci5_rx_address = rx_buf;
        SCI5.SCR.BIT.RIE = 1U;
        SCI5.SCR.BIT.RE = 1U;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: R_SCI5_Serial_Send
* Description  : This function transmits SCI5 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer (Not used when transmit data handled by DTC)
*                tx_num -
*                    buffer size (Not used when transmit data handled by DTC or DMAC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_SCI5_Serial_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
#ifdef DEBUGGR
	debug1(D_SCI5_SEND);
#endif

    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_sci5_tx_address = tx_buf;
        g_sci5_tx_count = tx_num;
        MPC.PC3PFS.BYTE = 0x0AU;
        PORTC.PMR.BYTE |= 0x08U;
        SCI5.SCR.BIT.TIE = 1U;
        SCI5.SCR.BIT.TE = 1U;
    }

    return (status);
}

/***************************************************************************************************
 *
 * 		SCI6 Code
 *
 ***************************************************************************************************/
/***********************************************************************************************************************
* Function Name: R_SCI6_Create
* Description  : This function initializes SCI6.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCI6_Create(void)
{
#if 0
	/* Cancel SCI5 module stop state */
    MSTP(SCI6) = 0U;

    /* Set interrupt priority */
    IPR(SCI6, RXI6) = _02_SCI_PRIORITY_LEVEL2;
    IPR(SCI6, TXI6) = _02_SCI_PRIORITY_LEVEL2;

    /* Clear the control register */
    SCI6.SCR.BYTE = 0x00U;

    /* Set clock enable */
    SCI6.SCR.BYTE = _00_SCI_INTERNAL_SCK_UNUSED;

    /* Clear the SIMR1.IICM, SPMR.CKPH, and CKPOL bit, and set SPMR */
    SCI6.SIMR1.BIT.IICM = 0U;
    //SCI6.SPMR.BYTE = _02_SCI_CTS | _00_SCI_CLOCK_NOT_INVERTED | _00_SCI_CLOCK_NOT_DELAYED;
    SCI6.SPMR.BYTE = _00_SCI_CLOCK_NOT_INVERTED | _00_SCI_CLOCK_NOT_DELAYED;

    /* Set control registers */
    SCI6.SMR.BYTE = _00_SCI_CLOCK_PCLK | _00_SCI_STOP_1 | _00_SCI_PARITY_EVEN | _00_SCI_PARITY_DISABLE |
                    _00_SCI_DATA_LENGTH_8 | _00_SCI_MULTI_PROCESSOR_DISABLE | _00_SCI_ASYNCHRONOUS_MODE;
    SCI6.SCMR.BYTE = _00_SCI_SERIAL_MODE | _00_SCI_DATA_INVERT_NONE | _00_SCI_DATA_LSB_FIRST |
                     _10_SCI_DATA_LENGTH_8_OR_7 | _62_SCI_SCMR_DEFAULT;
    SCI6.SEMR.BYTE = _00_SCI_LOW_LEVEL_START_BIT | _00_SCI_NOISE_FILTER_DISABLE | _00_SCI_16_BASE_CLOCK |
    				 _40_SCI_BAUDRATE_DOUBLE | _00_SCI_BIT_MODULATION_DISABLE;

    /* Set bitrate */
    SCI6.BRR = 0x61U;

    /* Set RXD6 / SMISO6 pin 	PG810 */
    MPC.P01PFS.BYTE = 0x0AU;	// P01:	RXD6 or SMISO6
    PORT0.PMR.BYTE |= 0x02U;	// 22.3.4 Port Mode Register (PMR)(Pg 785)	P01: Alternate Function.

    /* Set TXD6 / SMOSI6 pin  	PG810 */
    PORT0.PODR.BYTE	|= 0x01;	// 22.3.2 Port Output Data Register (PODR)(Pg 783)	P00: Set Bit High
    MPC.P00PFS.BYTE = 0x0AU;	// P00: TXD6 or SMOSI6
    PORT0.PMR.BYTE |= 0x01U;	// 22.3.4 Port Mode Register (PMR)(Pg 785)	P00: Alternate Function.
    PORT0.PDR.BYTE |= 0x01U;	// 22.3.1 Port Direction Register (PDR)(Pg 782)	P00: OUTPUT

    /* Set NONE / SCK6 pin 		PG810 */
    MPC.P02PFS.BYTE = 0x0AU;	// P02: NONE or SCK6
    PORT0.PMR.BYTE |= 0x04U;	// 22.3.4 Port Mode Register (PMR)(Pg 785)	P02: Alternate Function.
#endif
	uint8_t temp_var;
	//uint8_t temp_var2;

    /* Cancel SCI6 module stop state */
    MSTP(SCI6) = 0U;

    /* Setup SCI6 Enable Pins....
     * 		PLLC SPI Enable Pin(PLLC_Enable)(Input to PLLC)
     * 			Port P03(Pin 4)	xxxx.1xxx
     * 		PLLD SPI Enable Pin(PLLD_Enable)(Input to PLLD)
     * 			Port P24(Pin 33)	xxx1.xxxx
     */
#if 0
#endif
    /*
     * 		PLLC_Enable...P03 / Pin 4
     */
    //	PORT0.PODR.BYTE |= _08_Pm3_OUTPUT_1; 		// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P03: High Output
    //temp_var = PORT0.PODR.BYTE;
    //temp_var = temp_var | _08_Pm3_OUTPUT_1;
    //PORT0.PODR.BYTE = temp_var;
    PORT0.PODR.BIT.B3 = 0;							// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P03: LOW Output
    //	PORT0.DSCR.BYTE |= _08_Pm3_HIDRV_ON;		// 22.3.8 Drive Capacity Control Register (DSCR)(Pg 789) ...P03: High-drive output
    temp_var = PORT0.DSCR.BYTE;
    temp_var = temp_var | _08_Pm3_HIDRV_ON;
    PORT0.DSCR.BYTE = temp_var;
    //temp_var = PORT0.PMR.BYTE;
    //temp_var2 = _08_Pm3_MODE_OUTPUT;
    //temp_var2 = temp_var2 ^ 0xff;
    //temp_var = temp_var & temp_var2;
    //PORT0.PMR.BYTE = temp_var;
    PORT0.PMR.BYTE &= (_08_Pm3_MODE_OUTPUT ^ 0xff);	// 22.3.4 Port Mode Register (PMR)(Pg 785)...P03: Uses the pin as a general I/O pin.
    PORT0.PDR.BYTE |= _08_Pm3_MODE_OUTPUT;			// 22.3.1 Port Direction Register (PDR)(Pg 782)	P02: OUTPUT...P03: Output (Functions as an output pin.)

    /*
     *		PLLD_Enable...P24 / Pin 33
     */
    //	PORT2.PODR.BYTE |= _10_Pm4_OUTPUT_1;
    //temp_var = PORT2.PODR.BYTE;						// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P24: High Output
    //temp_var = temp_var | _10_Pm4_OUTPUT_1;
    //PORT2.PODR.BYTE = temp_var;
    PORT2.PODR.BIT.B4 = 0;							// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P24: Low Output
    //	PORT2.DSCR.BYTE |= _10_Pm4_HIDRV_ON;
    temp_var = PORT2.DSCR.BYTE;
    temp_var = temp_var | _10_Pm4_HIDRV_ON;
    PORT2.DSCR.BYTE = temp_var;
    //temp_var = PORT2.PMR.BYTE;
    //temp_var2 = _10_Pm4_MODE_OUTPUT;
    //temp_var2 = temp_var2 ^ 0xff;
    //temp_var = temp_var & temp_var2;
    //PORT2.PMR.BYTE = temp_var;
    PORT2.PMR.BYTE &= (_10_Pm4_MODE_OUTPUT ^ 0xff);
    PORT2.PDR.BYTE |= _10_Pm4_MODE_OUTPUT;			// 22.3.1 Port Direction Register (PDR)(Pg 782)	P24: OUTPUT...P24: Output (Functions as an output pin.)

    /* Set interrupt priority */
    IPR(SCI6, RXI6) = _0F_SCI_PRIORITY_LEVEL15;
    IPR(SCI6, TXI6) = _0F_SCI_PRIORITY_LEVEL15;

    /* Clear the control register */
    SCI6.SCR.BYTE = 0x00U;

    /* Set clock enable */
    //SCI6.SCR.BYTE |= _01_SCI_INTERNAL_SCK_OUTPUT;

    /* Clear the SIMR1.IICM */
    SCI6.SIMR1.BIT.IICM = 0U;

    /* Set control registers */
    SCI6.SPMR.BYTE = _00_SCI_SS_PIN_DISABLE | _00_SCI_SPI_MASTER | _00_SCI_CLOCK_NOT_INVERTED |
                     _00_SCI_CLOCK_NOT_DELAYED;
    SCI6.SMR.BYTE = _00_SCI_DATA_LENGTH_8 | _80_SCI_CLOCK_SYNCHRONOUS_MODE | _01_SCI_CLOCK_PCLK_4;
    SCI6.SCMR.BYTE = _00_SCI_SERIAL_MODE | _00_SCI_DATA_INVERT_NONE | _08_SCI_DATA_MSB_FIRST |
                     _10_SCI_DATA_LENGTH_8_OR_7 | _62_SCI_SCMR_DEFAULT;
    SCI6.SEMR.BYTE = _00_SCI_BIT_MODULATION_DISABLE;

    /* Set bitrate */
    SCI6.BRR = 0x4AU;

    /* Set RXD6 / SMISO6 pin 	PG810 */
    MPC.P01PFS.BYTE = 0x0AU;	// P01:	RXD6 or SMISO6
    PORT0.PMR.BYTE |= 0x02U;	// 22.3.4 Port Mode Register (PMR)(Pg 785)	P01: Alternate Function.

    /* Set TXD6 / SMOSI6 pin  	PG810 */
    //PORT0.PODR.BYTE	|= 0x01;	// 22.3.2 Port Output Data Register (PODR)(Pg 783)	P00: Set Bit High
    PORT0.PODR.BIT.B0 = 0;		// 22.3.2 Port Output Data Register (PODR)(Pg 783)	P00: Set Bit Low
    MPC.P00PFS.BYTE = 0x0AU;	// P00: TXD6 or SMOSI6
    PORT0.PMR.BYTE |= 0x01U;	// 22.3.4 Port Mode Register (PMR)(Pg 785)	P00: Alternate Function.
    PORT0.PDR.BYTE |= 0x01U;	// 22.3.1 Port Direction Register (PDR)(Pg 782)	P00: OUTPUT

    /* Set NONE / SCK6 pin 		PG810 */
    //PORT0.PODR.BYTE	|= 0x04;	// 22.3.2 Port Output Data Register (PODR)(Pg 783)	P02: Set Bit High
    //PORT0.PODR.BIT.B2 = 0;		// 22.3.2 Port Output Data Register (PODR)(Pg 783)	P02: Set Bit Low
    MPC.P02PFS.BYTE = 0x0AU;	// P02: NONE or SCK6
    PORT0.PMR.BYTE |= 0x04U;	// 22.3.4 Port Mode Register (PMR)(Pg 785)	P02: Alternate Function.
    PORT0.PDR.BYTE |= 0x04U;	// 22.3.1 Port Direction Register (PDR)(Pg 782)	P02: OUTPUT
}
/***********************************************************************************************************************
* Function Name: R_SCI6_Start
* Description  : This function starts SCI6.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCI6_Start(void)
{
    /* Clear interrupt flag */
    IR(SCI6,TXI6) = 0U;
    IR(SCI6,RXI6) = 0U;

    /* Enable SCI interrupt */
    IEN(SCI6,TXI6) = 1U;
    ICU.GENBL0.BIT.EN12 = 1U;
//    ICU.GENBL0.BIT.EN10 = 1U;
    IEN(SCI6,RXI6) = 1U;
    ICU.GENBL0.BIT.EN13 = 1U;
//    ICU.GENBL0.BIT.EN11 = 1U;
#if 0
	/* Enable TXI and TEI interrupt */
    IEN(SCI6,TXI6) = 1U;
    ICU.GENBL0.BIT.EN12 = 1U;

    /* Enable RXI interrupt */
    IEN(SCI6,RXI6) = 1U;
    /* Enable ERI interrupt */
    ICU.GENBL0.BIT.EN13 = 1U;

    /* Clear interrupt flags */
    IR(SCI6,TXI6) = 0U;
    IR(SCI6,RXI6) = 0U;
#endif
}
/***********************************************************************************************************************
* Function Name: R_SCI6_Stop
* Description  : This function stops SCI6.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SCI6_Stop(void)
{
    PORT0.PMR.BYTE &= 0xFEU;
    SCI6.SCR.BIT.TE = 0U;      /* Disable serial transmit */
    SCI6.SCR.BIT.RE = 0U;      /* Disable serial receive */
    SCI6.SCR.BIT.TIE = 0U;     /* Disable TXI interrupt */
    SCI6.SCR.BIT.RIE = 0U;     /* Disable RXI and ERI interrupt */

    /* Disable SCI interrupt */
    IR(SCI6,TXI6) = 0U;
    IEN(SCI6,TXI6) = 0U;
//    ICU.GENBL0.BIT.EN10 = 0U;
    ICU.GENBL0.BIT.EN12 = 0U;
    IR(SCI6,RXI6) = 0U;
    IEN(SCI6,RXI6) = 0U;
//    ICU.GENBL0.BIT.EN11 = 0U;
    ICU.GENBL0.BIT.EN13 = 0U;
#if 0
	/* Set SMOSI6 pin */
    PORT0.PMR.BYTE &= 0xFEU;
    SCI6.SCR.BYTE &= 0xCFU;      /* Disable serial transmit and receive */

    /* Disable TXI and TEI interrupt */
    IEN(SCI6,TXI6) = 0U;
    ICU.GENBL0.BIT.EN12 = 0U;

    /* Disable RXI interrupt */
    IEN(SCI6,RXI6) = 0U;
    /* Disable ERI interrupt */
    ICU.GENBL0.BIT.EN13 = 0U;

    /* Clear interrupt flags */
    IR(SCI6,TXI6) = 0U;
    IR(SCI6,RXI6) = 0U;
#endif
}

/***********************************************************************************************************************
* Function Name: R_SCI6_Serial_Send
* Description  : This function transmits SCI6 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer (Not used when transmit data handled by DTC)
*                tx_num -
*                    buffer size (Not used when transmit data handled by DTC or DMAC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_SCI6_Serial_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
#ifdef DEBUGGR
	debug1(D_SCI5_SEND);
#endif

    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_sci6_tx_address = tx_buf;
        g_sci6_tx_count = tx_num;
        MPC.P00PFS.BYTE = 0x0AU;	// P00: TXD6 or SMOSI6
        PORT0.PMR.BYTE |= 0x01U;	// 22.3.4 Port Mode Register (PMR)(Pg 785)	P00: Alternate Function.
        SCI6.SCR.BIT.TIE = 1U;
        SCI6.SCR.BIT.TE = 1U;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_SCI6_Serial_Receive
* Description  : This function receives SCI6 data.
* Arguments    : rx_buf -
*                    receive buffer pointer (Not used when receive data handled by DTC or DMAC)
*                rx_num -
*                    buffer size (Not used when receive data handled by DTC or DMAC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_SCI6_Serial_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (rx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_sci6_rx_count = 0U;
        g_sci6_rx_length = rx_num;
        gp_sci6_rx_address = rx_buf;
        SCI6.SCR.BIT.RIE = 1U;
        SCI6.SCR.BIT.RE = 1U;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_SCI6_SPI_Master_Send_Receive
* Description  : This function sends and receives SPI6 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer (Not used when transmit data handled by DTC or DMAC)
*                tx_num -
*                    buffer size (Not used when transmit data handled by DTC or DMAC)
*                rx_buf -
*                    receive buffer pointer (Not used when receive data handled by DTC or DMAC)
*                rx_num -
*                    buffer size (Not used when receive data handled by DTC or DMAC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_SCI6_SPI_Master_Send_Receive(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_sci6_tx_count = tx_num;
        gp_sci6_tx_address = tx_buf;
        gp_sci6_rx_address = rx_buf;
        g_sci6_rx_count = 0U;
        g_sci6_rx_length = rx_num;

        /* Set SMOSI6 pin */
        MPC.P00PFS.BYTE = 0x0AU;
        PORT0.PMR.BYTE |= 0x01U;

        /* Set TE, TIE, RE, RIE bits simultaneously */
        //SCI6.SCR.BYTE |= 0xF0U;
        SCI6.SCR.BIT.TIE = 1U;
        SCI6.SCR.BIT.TE = 1U;
        SCI6.SCR.BIT.RE = 1U;
        SCI6.SCR.BIT.RIE = 1U;
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: SCI6_SPI_Init_User_Vars
* Description  : This function Clears key flags for Processing SCI6 Data.
* Arguments    : NONE
* Return Value : NONE
***********************************************************************************************************************/
void SCI6_SPI_Init_User_Vars( void )
{
	sci6_Tx_Complete = 0x00;	// Clear Tx Complete Flag.
	sci6_Rx_Complete = 0x00;	// Clear Rx Complete Flag.
	sci6_Error = 0x00;			// Clear SPI Error Flag.
}
/* End user code. Do not edit comment generated here */
