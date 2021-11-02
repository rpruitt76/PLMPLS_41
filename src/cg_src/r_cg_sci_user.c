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
* File Name    : r_cg_sci_user.c
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
#include  <stdio.h>
#include <string.h>
#include "r_flash_rx_if.h"
#include "LaserP.h"
//#include  <os.h>
#include "r_cg_userdefine.h"
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_sci.h"
/* Start user code for include. Do not edit comment generated here */
extern uint8_t   gp_sci5_tx_errorType;             /* SCI5 Transmit Error Type */
extern uint8_t   gp_sci5_rx_errorType;             /* SCI5 Receive Error Type */
extern char      gp_sci5_rx_string[RX_BUFFERSIZE];           /* SCI5 Buffer to receive characters */
extern int       gp_sci5_rx_stringcnt;             /* Count to number characters received */

extern uint8_t   gp_sci6_tx_errorType;             /* SCI6 Transmit Error Type */
extern uint8_t   gp_sci6_rx_errorType;             /* SCI6 Receive Error Type */
//extern uint8_t   gp_sci6_tx_state = TX_NOINIT;     /* SCI6 Transmit State */
//extern uint8_t   gp_sci6_rx_state = RX_NOINIT;     /* SCI6 Receive State */
extern char      gp_sci6_rx_string[RX_BUFFERSIZE];           /* SCI6 Buffer to receive characters */
extern int       gp_sci6_rx_stringcnt;             /* Count to number characters received */

/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern uint8_t * gp_sci5_tx_address;                /* SCI5 send buffer address */
extern uint16_t  g_sci5_tx_count;                   /* SCI5 send data number */
extern uint8_t * gp_sci5_rx_address;                /* SCI5 receive buffer address */
extern uint16_t  g_sci5_rx_count;                   /* SCI5 receive data number */
extern uint16_t  g_sci5_rx_length;                  /* SCI5 receive data length */
extern uint8_t * gp_sci6_tx_address;                /* SCI6 send buffer address */
extern uint16_t  g_sci6_tx_count;                   /* SCI6 send data number */
extern uint8_t * gp_sci6_rx_address;                /* SCI6 receive buffer address */
extern uint16_t  g_sci6_rx_count;                   /* SCI6 receive data number */
extern uint16_t  g_sci6_rx_length;                  /* SCI6 receive data length */
/* Start user code for global. Do not edit comment generated here */
static uint8_t	Special_SCI_State;					// Track Special State for Processing.
static char		Temp_String[5];						// Temp String to Collect Characters
extern uint8_t	sci6_Tx_Complete;					// SCI6 Tx Complete.
extern uint8_t	sci6_Rx_Complete;					// SCI6 RX Complete
extern uint8_t	sci6_Error;							// SCI6 Error.

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_sci5_transmit_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if FAST_INTERRUPT_VECTOR == VECT_SCI5_TXI5
#pragma interrupt r_sci5_transmit_interrupt(vect=VECT(SCI5,TXI5),fint)
#else
#pragma interrupt r_sci5_transmit_interrupt(vect=VECT(SCI5,TXI5))
#endif
static void r_sci5_transmit_interrupt(void)
{
#ifdef DEBUGGR
	debug1(D_SCI5_TXINT);
#endif
    if (g_sci5_tx_count > 0U)
    {
        SCI5.TDR = *gp_sci5_tx_address;
        gp_sci5_tx_address++;
        g_sci5_tx_count--;
    }
    else
    {
        SCI5.SCR.BIT.TIE = 0U;
        SCI5.SCR.BIT.TEIE = 1U;
    }
}

/***********************************************************************************************************************
* Function Name: r_sci5_transmitend_interrupt
* Description  : This function is TEI5 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_sci5_transmitend_interrupt(void)
{
#ifdef DEBUGGR
	debug1(D_SCI5_TXEND);
#endif
    MPC.PC3PFS.BYTE = 0x00U;
    PORTC.PMR.BYTE &= 0xF7U;
    SCI5.SCR.BIT.TIE = 0U;
    SCI5.SCR.BIT.TE = 0U;
    SCI5.SCR.BIT.TEIE = 0U;

    r_sci5_callback_transmitend();
}

/***********************************************************************************************************************
* Function Name: r_sci5_receive_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if FAST_INTERRUPT_VECTOR == VECT_SCI5_RXI5
#pragma interrupt r_sci5_receive_interrupt(vect=VECT(SCI5,RXI5),fint)
#else
#pragma interrupt r_sci5_receive_interrupt(vect=VECT(SCI5,RXI5))
#endif
static void r_sci5_receive_interrupt(void)
{
	if (Special_SCI_State == 0)
	{
		if (g_sci5_rx_length > g_sci5_rx_count)
		{
			while ((SCI5.SSR.BYTE & 0x40) > 0)
			{
				*gp_sci5_rx_address = SCI5.RDR;
				gp_sci5_rx_address++;
				g_sci5_rx_count++;
			}

			if (g_sci5_rx_length <= g_sci5_rx_count)
			{
				r_sci5_callback_receiveend();
			}
		}
    }
    else
    {
    	r_sci5_callback_receiveend();
    }
}

/***********************************************************************************************************************
* Function Name: r_sci5_receiveerror_interrupt
* Description  : This function is ERI5 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_sci5_receiveerror_interrupt(void)
{
    uint8_t err_type;

    /* Clear overrun, framing and parity error flags */
    err_type = SCI5.SSR.BYTE;
    err_type &= 0xC7U;
    err_type |= 0xC0U;
    SCI5.SSR.BYTE = err_type;
}
/***********************************************************************************************************************
* Function Name: r_sci5_callback_transmitend
* Description  : This function is a callback function when SCI5 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_sci5_callback_transmitend(void)
{
    /* Start user code. Do not edit comment generated here */
    gp_sci5_tx_state = TX_COMPLETE;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_sci5_callback_receiveend
* Description  : This function is a callback function when SCI5 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_sci5_callback_receiveend(void)
{
	//int x;
	//int temp1;
	char tempChar;
    /* Start user code. Do not edit comment generated here */
	if (Special_SCI_State == 0)
	{
		gp_sci5_rx_state = RX_RECEIVED;
	}
	else
	{
		// Special RX_STRING2 mode		****HERE****
		// Transfer contents of received characters to buffer
		while ((SCI5.SSR.BYTE & 0x40) > 0)
		{
			// Transfer character to buffer
			tempChar = SCI5.RDR;
			gp_sci5_rx_string[gp_sci5_rx_stringcnt++] = tempChar;
			// Test for completion character
			if (tempChar == 0x0d)
			{
				gp_sci5_rx_state = RX_MSG_READY;
				// We are done...Clear Buffer
		    	while ((SCI5.SSR.BYTE & 0x40) > 0)
		    	{
		    		tempChar = SCI5.RDR;
		    	}
			}
		}
		if(gp_sci5_rx_state != RX_MSG_READY)
		{
			// Restart Reception
			R_SCI5_Serial_Receive((uint8_t *)Temp_String, 1); // Receive one character at a time.
		}
	}
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
//*****************************************************************************
//*
//* routine: R_SCI5_Serial_Print
//* Date:    January 11, 2015
//* Author:  Ralph Pruitt
//* SCI5 Serial Send Command
//*
//*****************************************************************************
unsigned char R_SCI5_Serial_Print( char str[], unsigned char task_cmd)
{
	MD_STATUS err;

#ifdef DEBUGGR
	debug1(D_SCI5_PRINT);
#endif

//	int tempcnt;
//  OS_ERR  err;
  if(task_cmd == TX_STATUS)
  {
    return(gp_sci5_tx_state);
  }
  else if(task_cmd == TX_SEND)
  {
    // Test Transmit flag and only fill buffer if flag is clear
    if(gp_sci5_tx_state != TX_BUSY)
    {
      // Clear Transmit flag for transmission
      gp_sci5_tx_errorType = 0x00;
      // Start Transmission
      gp_sci5_tx_state = TX_BUSY;
      //printf("***R_SCI5_Serial_Send str:%s Length:%d\n", str, strlen(str));
      if(strlen(str) > 0)
      {
          err = R_SCI5_Serial_Send((uint8_t *) str, (uint16_t)strlen(str));
          //printf(" ERR: %d\n", err);
          if (err > 0)
          {
        	  gp_sci5_tx_state = TX_COMPLETE;
        	  return TX_ERRORCD;
          }
      }
      else
      {
    	  gp_sci5_tx_state = TX_COMPLETE;
    	  return TX_ERRORCD;
      }
      return(0x00);
    }
    else
      return(TX_BUSY);
  }
  else if(task_cmd == TX_SEND_WAIT)
  {
    // Test Transmit flag and only fill buffer if flag is clear
    if(gp_sci5_tx_state != TX_BUSY)
    {
      // Clear Transmit flag for transmission
      gp_sci5_tx_errorType = 0x00;
      // Start Transmission
      gp_sci5_tx_state = TX_BUSY;
      //printf("***R_SCI5_Serial_Send str:%s Length:%d\n", str, strlen(str));
      if(strlen(str) > 0)
      {
          err = R_SCI5_Serial_Send((uint8_t *) str, (uint16_t)strlen(str));
          //printf(" ERR: %d\n", err);
          if (err > 0)
          {
        	  gp_sci5_tx_state = TX_COMPLETE;
        	  return TX_ERRORCD;
          }
      }
      else
      {
    	  gp_sci5_tx_state = TX_COMPLETE;
    	  return TX_ERRORCD;
      }
//      tempcnt = 0;
      while( gp_sci5_tx_state == TX_BUSY)
      {
        // Wait 5 msec
//        OSTimeDlyHMSM(0u, 0u, 0u, 50,
//                    OS_OPT_TIME_HMSM_STRICT,
//                    &err);
    	  accurate_delay(5);
//    	  tempcnt++;
/*    	  if(tempcnt>50)
    	  {
    		  // Reinitialize the SCI Port. It is hung.
    		  R_SCI5_Create();
    		  R_SCI5_Start();
    		  gp_sci5_tx_state = TX_COMPLETE;
    		  return(0xff);
    	  } */
      }
      return(0x00);
    }
    else
      return(TX_BUSY);
  }
  else
    return(0xff);
}

//*****************************************************************************
//*
//* routine: R_SCI5_Serial_Receive
//* Date:    January 12, 2015
//* Author:  Ralph Pruitt
//* SCI5 Serial Receive Command
//*
//*****************************************************************************
unsigned char R_SCI5_Serial_Rceive( char str[], unsigned char task_cmd)
{
//  OS_ERR  err;
  int x;
  if(task_cmd == RX_STATUS)
  {
    return(gp_sci5_rx_state);
  }
  else if(task_cmd == RX_ERRORCD)
  {
    return(gp_sci5_rx_errorType);
  }
  else if(task_cmd == RX_STRING)
  {
	Special_SCI_State = 0;
    // Test Receive flag and only fill buffer if flag is clear
    if((gp_sci5_rx_state == RX_COMPLETE) || (gp_sci5_rx_state == RX_ERROR))
    {
      // Clear Receive flag
      gp_sci5_rx_errorType = RX_COMPLETE;
      // Clear buffer and count
      for(x = 0; x<RX_BUFFERSIZE; x++)
        gp_sci5_rx_string[x] = 0x00;
      gp_sci5_rx_stringcnt = 0;

      // Start Reception
      R_SCI5_Serial_Receive((uint8_t *) str, 1); // Receie one character at a time.
      gp_sci5_rx_state = RX_BUSY;
      return(RX_BUSY);
    }
   else if(gp_sci5_rx_state == RX_RECEIVED)
   {
      // Transfer contents of received characters to buffer
      for(x=0; x<g_sci5_rx_count; x++)
      {
        // Transfer character to buffer
        gp_sci5_rx_string[gp_sci5_rx_stringcnt++] = gp_sci5_rx_address[x];
        // Test for completion character
        if (gp_sci5_rx_address[x] == 0x0d)
          gp_sci5_rx_state = RX_MSG_READY;
      }
      if(gp_sci5_rx_state != RX_MSG_READY)
      {
        // Restart Reception
        R_SCI5_Serial_Receive((uint8_t *) str, 1); // Receive one character at a time.
        gp_sci5_rx_state = RX_BUSY;
      }
      return(RX_BUSY);
    }
    else if(gp_sci5_rx_state == RX_MSG_READY)
    {
      for(x=0; x<gp_sci5_rx_stringcnt; x++)
        str[x] = gp_sci5_rx_string[x];
      gp_sci5_rx_state = RX_COMPLETE;
      return(RX_COMPLETE);
    }
    else if(gp_sci5_rx_state == RX_ERROR)
      return(RX_ERROR);
    else
      return(RX_BUSY);

  } // END of RX_STRING Processing
  else if(task_cmd == RX_STRING2)
  {
	Special_SCI_State = 1;			//   ****HERE****
    // Test Receive flag and only fill buffer if flag is clear
    if((gp_sci5_rx_state == RX_COMPLETE) || (gp_sci5_rx_state == RX_ERROR))
    {
      // Clear Receive flag
      gp_sci5_rx_errorType = RX_COMPLETE;
      // Clear buffer and count
      for(x = 0; x<RX_BUFFERSIZE; x++)
        gp_sci5_rx_string[x] = 0x00;
      for(x = 0; x<5; x++)
        Temp_String[x] = 0x00;
      gp_sci5_rx_stringcnt = 0;

      // Start Reception
      R_SCI5_Serial_Receive((uint8_t *) Temp_String, 1); // Receive one character at a time.
      gp_sci5_rx_state = RX_BUSY;
      return(RX_BUSY);
    }
   else if(gp_sci5_rx_state == RX_RECEIVED)
   {
      // Transfer contents of received characters to buffer
      for(x=0; x<g_sci5_rx_count; x++)
      {
        // Transfer character to buffer
        gp_sci5_rx_string[gp_sci5_rx_stringcnt++] = gp_sci5_rx_address[x];
        // Test for completion character
        if (gp_sci5_rx_address[x] == 0x0d)
          gp_sci5_rx_state = RX_MSG_READY;
      }
      if(gp_sci5_rx_state != RX_MSG_READY)
      {
        // Restart Reception
        R_SCI5_Serial_Receive((uint8_t *) str, 1); // Receive one character at a time.
        gp_sci5_rx_state = RX_BUSY;
      }
      return(RX_BUSY);
    }
    else if(gp_sci5_rx_state == RX_MSG_READY)
    {
      for(x=0; x<gp_sci5_rx_stringcnt; x++)
        str[x] = gp_sci5_rx_string[x];
      gp_sci5_rx_state = RX_COMPLETE;
      return(RX_COMPLETE);
    }
    else if(gp_sci5_rx_state == RX_ERROR)
      return(RX_ERROR);
    else
      return(RX_BUSY);

  } // END of RX_STRING Processing
  else if(task_cmd == RX_STRING_WAIT)
  {
	Special_SCI_State = 0;
	// Enable Interrupts just in case...
	SEI();
	// Clear buffer before starting next Receive cycle.
	for (x=0; x<5; x++)
		str[x] = SCI5.RDR;
	gp_sci5_rx_state = RX_COMPLETE;
    // Test Receive flag and only fill buffer if flag is clear
    if((gp_sci5_rx_state == RX_COMPLETE) || (gp_sci5_rx_state == RX_ERROR))
    {
      // Clear Receive flag
      gp_sci5_rx_errorType = RX_COMPLETE;
      // Clear buffer and count
      for(x = 0; x<RX_BUFFERSIZE; x++)
        gp_sci5_rx_string[x] = 0x00;
      gp_sci5_rx_stringcnt = 0;

      // Start Reception
      gp_sci5_rx_state = RX_BUSY;
      R_SCI5_Serial_Receive((uint8_t *) str, 1); // Receie one character at a time.
      while( gp_sci5_rx_state != RX_COMPLETE)
      {
        // Wait 10 msec
        //OSTimeDlyHMSM(0u, 0u, 0u, 10,
        //            OS_OPT_TIME_HMSM_STRICT,
        //            &err);
        if(gp_sci5_rx_state == RX_RECEIVED)
        {
          // Transfer contents of received characters to buffer
          for(x=0; x<g_sci5_rx_count; x++)
          {
            // Transfer character to buffer
            gp_sci5_rx_string[gp_sci5_rx_stringcnt++] = str[x];
            // Test for completion character
            if (str[x] == 0x0d)
            {
              gp_sci5_rx_state = RX_MSG_READY;
            }
          }
          if(gp_sci5_rx_state == RX_RECEIVED)
          {
            // Restart Reception
            gp_sci5_rx_state = RX_BUSY;
            R_SCI5_Serial_Receive((uint8_t *) str, 1); // Receive one character at a time.
          }
        } // EndIf(gp_sci5_rx_state == RX_RECEIVED)
        else if(gp_sci5_rx_state == RX_MSG_READY)
        {
          for(x=0; x<gp_sci5_rx_stringcnt; x++)
            str[x] = gp_sci5_rx_string[x];
          gp_sci5_rx_state = RX_COMPLETE;
        } // EndElse (gp_sci5_rx_state == RX_RECEIVED)
      } // EndWhile ( gp_sci5_rx_state != RX_COMPLETE)
      return(0x00);
    } // EndIf ((gp_sci5_rx_state == RX_COMPLETE) || (gp_sci5_rx_state == RX_ERROR))
    else
      // Can't task if we are busy with another event.
      return(0xff);
  } // END of RX_STRING_WAIT Processing
  else if(task_cmd == RX_CHAR)
  {
	Special_SCI_State = 0;
    // Test Receive flag and only fill buffer if flag is clear
    if((gp_sci5_rx_state == RX_COMPLETE) || (gp_sci5_rx_state == RX_ERROR))
    {
      // Clear Receive flag
      gp_sci5_rx_errorType = RX_COMPLETE;
      // Clear buffer and count
      gp_sci5_rx_stringcnt = 0;

      // Start Reception
      R_SCI5_Serial_Receive((uint8_t *) str, 1); // Receie one character at a time.
      gp_sci5_rx_state = RX_BUSY;
      return(RX_BUSY);
    }
   else if(gp_sci5_rx_state == RX_RECEIVED)
   {
      // Transfer contents of received characters to buffer
      gp_sci5_rx_state = RX_COMPLETE;
      return(0);
    }
    else if(gp_sci5_rx_state == RX_ERROR)
      return(RX_ERROR);
    else
      return(RX_BUSY);
  } // END of RX_CHAR Processing
  else if(task_cmd == RX_CHAR_WAIT)
  {
	Special_SCI_State = 0;
    // Test Receive flag and only fill buffer if flag is clear
    if((gp_sci5_rx_state == RX_COMPLETE) || (gp_sci5_rx_state == RX_ERROR))
    {
      // Clear Receive flag
      gp_sci5_rx_errorType = RX_COMPLETE;
      // Clear buffer and count
      gp_sci5_rx_stringcnt = 0;

      // Start Reception
      R_SCI5_Serial_Receive((uint8_t *) str, 1); // Receie one character at a time.
      gp_sci5_rx_state = RX_BUSY;
      while( gp_sci5_tx_state != RX_COMPLETE)
      {
        // Wait 10 msec
        //OSTimeDlyHMSM(0u, 0u, 0u, 10,
        //            OS_OPT_TIME_HMSM_STRICT,
        //            &err);
        if(gp_sci5_rx_state == RX_RECEIVED)
        {
          // Transfer contents of received characters to buffer
            gp_sci5_rx_state = RX_COMPLETE;
        }
      }
      return(0x00);
    }
    else
      // Can't task if we are busy with another event.
      return(0xff);
  } // END of RX_CHAR_WAIT Processing
  else
    return(0xff);
}

/***********************************************************************************************************************
* Function Name: r_sci5_Setup
* Description  : This sets up all needed callbacks for the BSP
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
unsigned char R_SCI5_Setup( void)
{
	bsp_int_err_t err;

	// Init Special State.
	Special_SCI_State = 0;

	/* Register Transmit end _callback() to be called whenever a SCI5 Transmit ends. */
	err = R_BSP_InterruptWrite(BSP_INT_SRC_BL0_SCI5_TEI5, (bsp_int_cb_t)r_sci5_transmitend_interrupt);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	/* Register Receive Error _callback() to be called whenever a SCI5 Receive Error occurs. */
	err = R_BSP_InterruptWrite(BSP_INT_SRC_BL0_SCI5_ERI5, (bsp_int_cb_t)r_sci5_receiveerror_interrupt);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	// Set internal States ready for operation.
	gp_sci5_tx_state = TX_COMPLETE;
	gp_sci5_rx_state = RX_COMPLETE;

	return 0;

}


/***********************************************************************************************************************
* Function Name: r_sci5_Enable
* Description  : This Enables Group Interrupts.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
unsigned char R_SCI5_Enable( void)
{
	bsp_int_err_t err;
	bsp_int_ctrl_t data1;

	data1.ipl = 5;	// Set Priority to 5.

	/* Enable SCI5 Transmit ends Interrupt. */
	err = R_BSP_InterruptControl(BSP_INT_SRC_BL0_SCI5_TEI5,
								BSP_INT_CMD_GROUP_INTERRUPT_ENABLE,
								(void *)&data1);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	/* Enable SCI5 Receive Error Interrupt. */
	err = R_BSP_InterruptControl(BSP_INT_SRC_BL0_SCI5_ERI5,
								BSP_INT_CMD_GROUP_INTERRUPT_ENABLE,
								(void *)&data1);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	return 0;
}

/***********************************************************************************************************************
* Function Name: r_sci5_Disable
* Description  : This Enables Group Interrupts.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
unsigned char R_SCI5_Disable( void)
{
	bsp_int_err_t err;


	/* Enable SCI5 Transmit ends Interrupt. */
	err = R_BSP_InterruptControl(BSP_INT_SRC_BL0_SCI5_TEI5,
								BSP_INT_CMD_GROUP_INTERRUPT_DISABLE,
								FIT_NO_PTR);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	/* Enable SCI5 Receive Error Interrupt. */
	err = R_BSP_InterruptControl(BSP_INT_SRC_BL0_SCI5_ERI5,
								BSP_INT_CMD_GROUP_INTERRUPT_DISABLE,
								FIT_NO_PTR);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	return 0;
}

/***************************************************************************************************
 *
 * 		SCI6 User Code
 *
 ***************************************************************************************************/
/***********************************************************************************************************************
* Function Name: r_sci6_transmit_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if FAST_INTERRUPT_VECTOR == VECT_SCI6_TXI6
#pragma interrupt r_sci6_transmit_interrupt(vect=VECT(SCI6,TXI6),fint)
#else
#pragma interrupt r_sci6_transmit_interrupt(vect=VECT(SCI6,TXI6))
#endif
static void r_sci6_transmit_interrupt(void)
{
    if (g_sci6_tx_count > 0U)
    {
        SCI6.TDR = *gp_sci6_tx_address;
        gp_sci6_tx_address++;
        g_sci6_tx_count--;
    }
    else
    {
        SCI6.SCR.BIT.TIE = 0U;
        SCI6.SCR.BIT.TEIE = 1U;
    }
}
/***********************************************************************************************************************
* Function Name: r_sci6_transmitend_interrupt
* Description  : This function is TEI6 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_sci6_transmitend_interrupt(void)
{
#ifdef DEBUGGR
	debug1(D_SCI5_TXEND);
#endif
    /* Clear SMOSI6 pin */
	// Section 23.2.2 P0n Pin Function Control Register (P0nPFS) (n = 0 to 3, 5, 7)
    MPC.P00PFS.BYTE = 0x00U;	//
    PORT0.PMR.BYTE &= 0xFEU;

    SCI6.SCR.BIT.TIE = 0U;
    SCI6.SCR.BIT.TE = 0U;
    SCI6.SCR.BIT.TEIE = 0U;

    r_sci6_callback_transmitend();
#if 0
    SCI6.SCR.BIT.TIE = 0U;
    SCI6.SCR.BIT.TE = 0U;
    SCI6.SCR.BIT.TEIE = 0U;

	/* Clear TE and RE bits */
    if(0U == SCI6.SCR.BIT.RIE)
    {
        SCI6.SCR.BYTE &= 0xCFU;
    }

    r_sci6_callback_transmitend();
#endif
}
/***********************************************************************************************************************
* Function Name: r_sci6_receive_interrupt
* Description  : None
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if FAST_INTERRUPT_VECTOR == VECT_SCI6_RXI6
#pragma interrupt r_sci6_receive_interrupt(vect=VECT(SCI6,RXI6),fint)
#else
#pragma interrupt r_sci6_receive_interrupt(vect=VECT(SCI6,RXI6))
#endif
static void r_sci6_receive_interrupt(void)
{
	if (g_sci6_rx_length > g_sci6_rx_count)
	{
		while ((SCI6.SSR.BYTE & 0x40) > 0)
		{
			*gp_sci6_rx_address = SCI6.RDR;
			gp_sci6_rx_address++;
			g_sci6_rx_count++;
		}

		if (g_sci6_rx_length <= g_sci6_rx_count)
		{
			r_sci6_callback_receiveend();
		}
	}
#if 0
    if (g_sci6_rx_length > g_sci6_rx_count)
    {
        *gp_sci6_rx_address = SCI6.RDR;
        gp_sci6_rx_address++;
        g_sci6_rx_count++;

        if (g_sci6_rx_length == g_sci6_rx_count)
        {
		    SCI6.SCR.BIT.RIE = 0;

            /* Clear TE and RE bits */
            if((0U == SCI6.SCR.BIT.TIE) && (0U == SCI6.SCR.BIT.TEIE))
            {
                SCI6.SCR.BYTE &= 0xCFU;
            }

            r_sci6_callback_receiveend();
        }
    }
#endif
}
/***********************************************************************************************************************
* Function Name: r_sci6_receiveerror_interrupt
* Description  : This function is ERI6 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_sci6_receiveerror_interrupt(void)
{
    uint8_t err_type;

    /* Clear overrun, framing and parity error flags */
    err_type = SCI6.SSR.BYTE;
    err_type &= 0xC7U;
    err_type |= 0xC0U;
    SCI6.SSR.BYTE = err_type;
#if 0
	uint8_t err_type;

    r_sci6_callback_receiveerror();

    /* Clear overrun error flag */
    err_type = SCI6.SSR.BYTE;
    err_type &= 0xDFU;
    err_type |= 0xC0U;
    SCI6.SSR.BYTE = err_type;
#endif
}
/***********************************************************************************************************************
* Function Name: r_sci6_callback_transmitend
* Description  : This function is a callback function when SCI6 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_sci6_callback_transmitend(void)
{
    /* Start user code. Do not edit comment generated here */
	gp_sci6_tx_state = TX_COMPLETE;
	//sci6_Tx_Complete = 0x01;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_sci6_callback_receiveend
* Description  : This function is a callback function when SCI6 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_sci6_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
	//int x;
	//int temp1;
	char tempChar;

	// Transfer contents of received characters to buffer
	while ((SCI6.SSR.BYTE & 0x40) > 0) {
		// Transfer character to buffer
		tempChar = SCI6.RDR;
		gp_sci6_rx_string[gp_sci6_rx_stringcnt++] = tempChar;
		// Test for completion character
		if (tempChar == 0x0d) {
			gp_sci6_rx_state = RX_MSG_READY;
			// We are done...Clear Buffer
			while ((SCI6.SSR.BYTE & 0x40) > 0) {
				tempChar = SCI6.RDR;
			}
		}
	}
	if (gp_sci6_rx_state != RX_MSG_READY) {
		// Restart Reception
		R_SCI6_Serial_Receive((uint8_t*) Temp_String, 1);// Receive one character at a time.
	}
    /* End user code. Do not edit comment generated here */
#if 0
    /* Start user code. Do not edit comment generated here */
	sci6_Rx_Complete = 0x01;
    /* End user code. Do not edit comment generated here */
#endif
}
/***********************************************************************************************************************
* Function Name: r_sci6_callback_receiveerror
* Description  : This function is a callback function when SCI6 reception encounters error.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#if 0
static void r_sci6_callback_receiveerror(void)
{
    /* Start user code. Do not edit comment generated here */
	sci6_Error = 0x01;
    /* End user code. Do not edit comment generated here */
}
#endif

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: R_SCI6_SPI_Send
* Description  : This function Sets up the SCI6 port for SPI Communication and sends the passed string. It also is used
* to collect ata from the receive side of the SPI Port.
* Arguments    : uint8_t str[]: 	Passed Buffer of Bytes to send to the SPI Port.
* 				 int wrtLen:		Number of Bytes to transmit.
* 				 uint8_t retStr[]:	Pointer to Buffer for receive Traffic.
* 				 int rdLen:			Number of Bytes to receive from SPI Bus
* Return Value : MD_STATUS:			TX_BUSY(1):		SPI BUS Busy...Can't Task
* 									TX_COMPLETE(0):	Successful Send and Receive of SPI Data.
* 									TX_ERRORCD(3):	Error occurred when Tasking SPI Command.
***********************************************************************************************************************/
unsigned char R_SCI6_SPI_Send( uint8_t str[], int wrtLen, uint8_t retStr[], int rdLen )
{
	MD_STATUS err;

#ifdef DEBUGGR
	debug1(D_SCI5_PRINT);
#endif
		// Test Transmit flag and only fill buffer if flag is clear
		if (gp_sci6_tx_state != TX_BUSY) {
			// Clear Transmit flag for transmission
			gp_sci6_tx_errorType = 0x00;
			// Start Transmission
			gp_sci6_tx_state = TX_BUSY;
			//printf("***R_SCI6_Serial_Send str:%s Length:%d\n", str, strlen(str));
			if (wrtLen > 0) {
				err = R_SCI6_SPI_Master_Send_Receive((uint8_t*)str, wrtLen, (uint8_t*)retStr, rdLen);
				/*err = R_SCI6_Serial_Send((uint8_t*) str,
						(uint16_t) strlen(str)); */
				//printf(" ERR: %d\n", err);
				if (err > 0) {
					gp_sci6_tx_state = TX_COMPLETE;
					return TX_ERRORCD;
				}
			} else {
				gp_sci6_tx_state = TX_COMPLETE;
				return TX_ERRORCD;
			}
			while (gp_sci6_tx_state == TX_BUSY) {
				// Wait 10 usec
				short_delay(10);
			}
			return (0x00);
		} else
			return (TX_BUSY);
}

/***********************************************************************************************************************
* Function Name: R_SCI6_SPI_Receive
* Description  : This function Sets up the SCI6 port for SPI Communication and sends the passed string. It also is used
* to collect ata from the receive side of the SPI Port.
* Arguments    : uint8_t str[]: 	Passed Buffer of Bytes to send to the SPI Port.
* 				 int wrtLen:		Number of Bytes to transmit.
* 				 uint8_t retStr[]:	Pointer to Buffer for receive Traffic.
* 				 int rdLen:			Number of Bytes to receive from SPI Bus
* Return Value : MD_STATUS:			TX_BUSY(1):		SPI BUS Busy...Can't Task
* 									TX_COMPLETE(0):	Successful Send and Receive of SPI Data.
* 									TX_ERRORCD(3):	Error occurred when Tasking SPI Command.
***********************************************************************************************************************/
#define SPI_DELAY_USEC	5		// Set Delay to 5 usec per transition on Clock
unsigned char R_SCI6_SPI_Receive( uint8_t str[], int wrtLen, uint8_t retStr[], int rdLen )
{
	//MD_STATUS err;
	int tmpByte, tmpWrt, tmpRd;
	//int BlkRd;
	uint8_t TempWrtData, TempRdData, TmpValue;

#ifdef DEBUGGR
	debug1(D_SCI5_PRINT);
#endif
		// Test Transmit flag and only fill buffer if flag is clear
		if (gp_sci6_tx_state != TX_BUSY) {
			// Clear Transmit flag for transmission
			gp_sci6_tx_errorType = 0x00;
			// Start Transmission
			gp_sci6_tx_state = TX_BUSY;
			//printf("***R_SCI6_Serial_Send str:%s Length:%d\n", str, strlen(str));
			if (wrtLen > 0) {
			    /**********************************************
			     *
			     * 		Code to Bit Bang Interface for Receive.
			     *
			     **********************************************/
			    /*
			     * 	1. Enable SPI_SDI, SPI_SDO, and SPI_SCK as IO Pins.
			     */
			    /* Set SPI_SDO / SMISO6 pin 	PG810 */
			    PORT0.PMR.BIT.B1 = 0x00;	// 22.3.4 Port Mode Register (PMR)(Pg 785)	P01: Uses the pin as a general I/O pin.
			    PORT0.PDR.BIT.B1 = 0x00;	// 22.3.1 Port Direction Register (PDR)(Pg 782)	P01: Input (Functions as an input pin.)
			    /* Set SPI_SDI / SMOSI6 pin  	PG810 */
			    PORT0.PODR.BIT.B0 = 0;		// 22.3.2 Port Output Data Register (PODR)(Pg 783)	P00: Set Bit Low
			    PORT0.PMR.BIT.B0 = 0x00;	// 22.3.4 Port Mode Register (PMR)(Pg 785)	P00: Uses the pin as a general I/O pin.
			    PORT0.PDR.BIT.B0 = 0x01;	// 22.3.1 Port Direction Register (PDR)(Pg 782)	P00: OUTPUT
			    /* Set SPI_SCK / SCK6 pin 		PG810 */
			    PORT0.PODR.BIT.B2 = 1;		// 22.3.2 Port Output Data Register (PODR)(Pg 783)	P02: Set Bit High
			    PORT0.PMR.BIT.B2 = 0x00;	// 22.3.4 Port Mode Register (PMR)(Pg 785)	P02: Uses the pin as a general I/O pin.
			    PORT0.PDR.BIT.B2 = 0x01;	// 22.3.1 Port Direction Register (PDR)(Pg 782)	P02: OUTPUT

			    /*
			     * 	2. Bit Bang Data through IO Pins
			     */
			    // Set Key Variables for Accumulation of data.
			    tmpRd = 0;

			    // Start Outside Loop
			    for (tmpWrt=0; tmpWrt<wrtLen; tmpWrt++)
			    {
			    	TempWrtData = *str;
			    	TempRdData = 0;
			    	// Setup Inside Loop
			    	for (tmpByte=0; tmpByte<8; tmpByte++)
			    	{
			    		// Rotate TempRdData to the left by 1 bit.
		    			TempRdData = TempRdData << 1;
			    		// Set CLK Low.
			    		PORT0.PODR.BIT.B2 = 0;		// SPI_SCK: LOW
			    		// Read MSB Bit and determine if it is high.
			    		if ((TempWrtData & 0x80) > 0)
			    			PORT0.PODR.BIT.B0 = 1;		// SPI_SDI: HIGH
			    		else
			    			PORT0.PODR.BIT.B0 = 0;		// SPI_SDI: LOW
			    		// Now Rotate TempWrtData to the left by 1 bit.
			    		TempWrtData = TempWrtData << 1;
			    		// Wait SPI_DELAY_USEC usec
			    		short_delay(SPI_DELAY_USEC);
			    		// Set Clock High
			    		PORT0.PODR.BIT.B2 = 1;		// SPI_SCK: HIGH
			    		// Wait SPI_DELAY_USEC usec
			    		short_delay(SPI_DELAY_USEC);
			    		// Determine if we need to sample Read Bit
			    		if (tmpRd < rdLen)
			    		{
			    			// Read Input Pin and determine logic
			    			TmpValue = PORT0.PIDR.BIT.B1;	// read SPI_SDO.
			    			if (TmpValue)
			    				TempRdData |= 1;	// Rotate in Value of High.
			    			else
			    				TempRdData |= 0;	// Rotate in Value of Low.
			    		} // EndIf (tmpRd < rdLen)
			    	} // EndFor (tmpByte=0; tmpByte<8; tmpByte++)
			    	// Byte has been written and read...Time to update varaibles.
			    	str++;
		    		if (tmpRd < rdLen)
		    		{
		    			*retStr = TempRdData;
		    			retStr++;
		    			tmpRd++;
		    		} // EndIf (tmpRd < rdLen)
			    } // EndFor (tmpWrt=0; tmpWrt<wrtLen; tmpWrt++)

			    /*
			     *  3. Reset SPI_SDI, SPI_SDO, and SPI_SCK as SPI BUS Pins.
			     */
			    /* Set SPI_SDO / SMISO6 pin 	PG810 */
			    PORT0.PMR.BIT.B1 = 0x01;	// 22.3.4 Port Mode Register (PMR)(Pg 785)	P01: Uses the pin as a general I/O pin.
			    PORT0.PDR.BIT.B1 = 0x00;	// 22.3.1 Port Direction Register (PDR)(Pg 782)	P01: Input (Functions as an input pin.)
			    /* Set TXD6 / SMOSI6 pin  	PG810 */
			    PORT0.PODR.BIT.B0 = 0;		// 22.3.2 Port Output Data Register (PODR)(Pg 783)	P00: Set Bit Low
			    PORT0.PMR.BIT.B0 = 0x01;	// 22.3.4 Port Mode Register (PMR)(Pg 785)	P00: Alternate Function.
			    PORT0.PDR.BIT.B0 = 0x01;	// 22.3.1 Port Direction Register (PDR)(Pg 782)	P00: OUTPUT
			    /* Set NONE / SCK6 pin 		PG810 */
			    PORT0.PODR.BIT.B2 = 1;		// 22.3.2 Port Output Data Register (PODR)(Pg 783)	P02: Set Bit High
			    PORT0.PMR.BIT.B2 = 0x01;	// 22.3.4 Port Mode Register (PMR)(Pg 785)	P02: Alternate Function.
			    PORT0.PDR.BIT.B2 = 0x01;	// 22.3.1 Port Direction Register (PDR)(Pg 782)	P02: OUTPUT

			    gp_sci6_tx_state = TX_COMPLETE;
				return MD_OK;
			} else {
				gp_sci6_tx_state = TX_COMPLETE;
				return TX_ERRORCD;
			}
		} else
			return (TX_BUSY);
}

//*****************************************************************************
//*
//* routine: R_SCI6_Serial_Print
//* Date:    November 10, 2020
//* Author:  Ralph Pruitt
//* SCI6 Serial Send Command
//*
//*****************************************************************************
unsigned char R_SCI6_Serial_Print( char str[], unsigned char task_cmd)
{
	MD_STATUS err;

#ifdef DEBUGGR
	debug1(D_SCI5_PRINT);
#endif
#if 0
	if (task_cmd == TX_STATUS) {
		return (gp_sci6_tx_state);
	} else if (task_cmd == TX_SEND) {
		// Test Transmit flag and only fill buffer if flag is clear
		if (gp_sci6_tx_state != TX_BUSY) {
			// Clear Transmit flag for transmission
			gp_sci6_tx_errorType = 0x00;
			// Start Transmission
			gp_sci6_tx_state = TX_BUSY;
			//printf("***R_SCI5_Serial_Send str:%s Length:%d\n", str, strlen(str));
			if (strlen(str) > 0) {
				err = R_SCI6_Serial_Send((uint8_t*) str,
						(uint16_t) strlen(str));
				//printf(" ERR: %d\n", err);
				if (err > 0) {
					gp_sci6_tx_state = TX_COMPLETE;
					return TX_ERRORCD;
				}
			} else {
				gp_sci6_tx_state = TX_COMPLETE;
				return TX_ERRORCD;
			}
			return (0x00);
		} else
			return (TX_BUSY);
	} else if (task_cmd == TX_SEND_WAIT) {
#endif
		// Test Transmit flag and only fill buffer if flag is clear
		if (gp_sci6_tx_state != TX_BUSY) {
			// Clear Transmit flag for transmission
			gp_sci6_tx_errorType = 0x00;
			// Start Transmission
			gp_sci6_tx_state = TX_BUSY;
			//printf("***R_SCI6_Serial_Send str:%s Length:%d\n", str, strlen(str));
			if (strlen(str) > 0) {
				err = R_SCI6_Serial_Send((uint8_t*) str,
						(uint16_t) strlen(str));
				//printf(" ERR: %d\n", err);
				if (err > 0) {
					gp_sci6_tx_state = TX_COMPLETE;
					return TX_ERRORCD;
				}
			} else {
				gp_sci6_tx_state = TX_COMPLETE;
				return TX_ERRORCD;
			}
			while (gp_sci6_tx_state == TX_BUSY) {
				// Wait 1 msec
				accurate_delay(1);
			}
			return (0x00);
		} else
			return (TX_BUSY);
//	} else
//		return (0xff);
}

//*****************************************************************************
//*
//* routine: R_SCI6_Serial_Receive
//* Date:    November 10, 2020
//* Author:  Ralph Pruitt
//* SCI5 Serial Receive Command
//*
//*****************************************************************************
unsigned char R_SCI6_Serial_Rceive( char str[], unsigned char task_cmd)
{
//  OS_ERR  err;
  int x;
  if(task_cmd == RX_STATUS)
  {
    return(gp_sci6_rx_state);
  }
  else if(task_cmd == RX_ERRORCD)
  {
    return(gp_sci6_rx_errorType);
  }
  else if(task_cmd == RX_STRING)
  {
    // Test Receive flag and only fill buffer if flag is clear
    if((gp_sci6_rx_state == RX_COMPLETE) || (gp_sci5_rx_state == RX_ERROR))
    {
      // Clear Receive flag
      gp_sci6_rx_errorType = RX_COMPLETE;
      // Clear buffer and count
      for(x = 0; x<RX_BUFFERSIZE; x++)
        gp_sci6_rx_string[x] = 0x00;
      gp_sci6_rx_stringcnt = 0;

      // Start Reception
      R_SCI6_Serial_Receive((uint8_t *) str, 1); // Receie one character at a time.
      gp_sci6_rx_state = RX_BUSY;
      return(RX_BUSY);
    }
   else if(gp_sci6_rx_state == RX_RECEIVED)
   {
      // Transfer contents of received characters to buffer
      for(x=0; x<g_sci6_rx_count; x++)
      {
        // Transfer character to buffer
        gp_sci6_rx_string[gp_sci6_rx_stringcnt++] = gp_sci6_rx_address[x];
        // Test for completion character
        if (gp_sci6_rx_address[x] == 0x0d)
          gp_sci6_rx_state = RX_MSG_READY;
      }
      if(gp_sci6_rx_state != RX_MSG_READY)
      {
        // Restart Reception
        R_SCI6_Serial_Receive((uint8_t *) str, 1); // Receive one character at a time.
        gp_sci6_rx_state = RX_BUSY;
      }
      return(RX_BUSY);
    }
    else if(gp_sci6_rx_state == RX_MSG_READY)
    {
      for(x=0; x<gp_sci6_rx_stringcnt; x++)
        str[x] = gp_sci6_rx_string[x];
      gp_sci6_rx_state = RX_COMPLETE;
      return(RX_COMPLETE);
    }
    else if(gp_sci6_rx_state == RX_ERROR)
      return(RX_ERROR);
    else
      return(RX_BUSY);

  } // END of RX_STRING Processing
  else if(task_cmd == RX_STRING2)
  {
    // Test Receive flag and only fill buffer if flag is clear
    if((gp_sci6_rx_state == RX_COMPLETE) || (gp_sci6_rx_state == RX_ERROR))
    {
      // Clear Receive flag
      gp_sci6_rx_errorType = RX_COMPLETE;
      // Clear buffer and count
      for(x = 0; x<RX_BUFFERSIZE; x++)
        gp_sci6_rx_string[x] = 0x00;
      for(x = 0; x<5; x++)
        Temp_String[x] = 0x00;
      gp_sci6_rx_stringcnt = 0;

      // Start Reception
      R_SCI6_Serial_Receive((uint8_t *) Temp_String, 1); // Receie one character at a time.
      gp_sci6_rx_state = RX_BUSY;
      return(RX_BUSY);
    }
   else if(gp_sci6_rx_state == RX_RECEIVED)
   {
      // Transfer contents of received characters to buffer
      for(x=0; x<g_sci6_rx_count; x++)
      {
        // Transfer character to buffer
        gp_sci6_rx_string[gp_sci6_rx_stringcnt++] = gp_sci6_rx_address[x];
        // Test for completion character
        if (gp_sci6_rx_address[x] == 0x0d)
          gp_sci6_rx_state = RX_MSG_READY;
      }
      if(gp_sci6_rx_state != RX_MSG_READY)
      {
        // Restart Reception
        R_SCI6_Serial_Receive((uint8_t *) str, 1); // Receive one character at a time.
        gp_sci6_rx_state = RX_BUSY;
      }
      return(RX_BUSY);
    }
    else if(gp_sci6_rx_state == RX_MSG_READY)
    {
      for(x=0; x<gp_sci6_rx_stringcnt; x++)
        str[x] = gp_sci6_rx_string[x];
      gp_sci6_rx_state = RX_COMPLETE;
      return(RX_COMPLETE);
    }
    else if(gp_sci6_rx_state == RX_ERROR)
      return(RX_ERROR);
    else
      return(RX_BUSY);

  } // END of RX_STRING Processing
  else if(task_cmd == RX_STRING_WAIT)
  {
	// Enable Interrupts just in case...
	SEI();
	// Clear buffer before starting next Receive cycle.
	for (x=0; x<5; x++)
		str[x] = SCI5.RDR;
	gp_sci6_rx_state = RX_COMPLETE;
    // Test Receive flag and only fill buffer if flag is clear
    if((gp_sci6_rx_state == RX_COMPLETE) || (gp_sci6_rx_state == RX_ERROR))
    {
      // Clear Receive flag
      gp_sci6_rx_errorType = RX_COMPLETE;
      // Clear buffer and count
      for(x = 0; x<RX_BUFFERSIZE; x++)
        gp_sci6_rx_string[x] = 0x00;
      gp_sci6_rx_stringcnt = 0;

      // Start Reception
      gp_sci6_rx_state = RX_BUSY;
      R_SCI6_Serial_Receive((uint8_t *) str, 1); // Receie one character at a time.
      while( gp_sci6_rx_state != RX_COMPLETE)
      {
        // Wait 10 msec
        //OSTimeDlyHMSM(0u, 0u, 0u, 10,
        //            OS_OPT_TIME_HMSM_STRICT,
        //            &err);
        if(gp_sci6_rx_state == RX_RECEIVED)
        {
          // Transfer contents of received characters to buffer
          for(x=0; x<g_sci6_rx_count; x++)
          {
            // Transfer character to buffer
            gp_sci6_rx_string[gp_sci6_rx_stringcnt++] = str[x];
            // Test for completion character
            if (str[x] == 0x0d)
            {
              gp_sci6_rx_state = RX_MSG_READY;
            }
          }
          if(gp_sci6_rx_state == RX_RECEIVED)
          {
            // Restart Reception
            gp_sci6_rx_state = RX_BUSY;
            R_SCI6_Serial_Receive((uint8_t *) str, 1); // Receive one character at a time.
          }
        } // EndIf(gp_sci5_rx_state == RX_RECEIVED)
        else if(gp_sci6_rx_state == RX_MSG_READY)
        {
          for(x=0; x<gp_sci6_rx_stringcnt; x++)
            str[x] = gp_sci6_rx_string[x];
          gp_sci6_rx_state = RX_COMPLETE;
        } // EndElse (gp_sci5_rx_state == RX_RECEIVED)
      } // EndWhile ( gp_sci5_rx_state != RX_COMPLETE)
      return(0x00);
    } // EndIf ((gp_sci5_rx_state == RX_COMPLETE) || (gp_sci5_rx_state == RX_ERROR))
    else
      // Can't task if we are busy with another event.
      return(0xff);
  } // END of RX_STRING_WAIT Processing
  else if(task_cmd == RX_CHAR)
  {
    // Test Receive flag and only fill buffer if flag is clear
    if((gp_sci6_rx_state == RX_COMPLETE) || (gp_sci6_rx_state == RX_ERROR))
    {
      // Clear Receive flag
      gp_sci6_rx_errorType = RX_COMPLETE;
      // Clear buffer and count
      gp_sci6_rx_stringcnt = 0;

      // Start Reception
      R_SCI6_Serial_Receive((uint8_t *) str, 1); // Receie one character at a time.
      gp_sci6_rx_state = RX_BUSY;
      return(RX_BUSY);
    }
   else if(gp_sci6_rx_state == RX_RECEIVED)
   {
      // Transfer contents of received characters to buffer
      gp_sci6_rx_state = RX_COMPLETE;
      return(0);
    }
    else if(gp_sci6_rx_state == RX_ERROR)
      return(RX_ERROR);
    else
      return(RX_BUSY);
  } // END of RX_CHAR Processing
  else if(task_cmd == RX_CHAR_WAIT)
  {
    // Test Receive flag and only fill buffer if flag is clear
    if((gp_sci6_rx_state == RX_COMPLETE) || (gp_sci6_rx_state == RX_ERROR))
    {
      // Clear Receive flag
      gp_sci6_rx_errorType = RX_COMPLETE;
      // Clear buffer and count
      gp_sci6_rx_stringcnt = 0;

      // Start Reception
      R_SCI6_Serial_Receive((uint8_t *) str, 1); // Receie one character at a time.
      gp_sci6_rx_state = RX_BUSY;
      while( gp_sci6_tx_state != RX_COMPLETE)
      {
        // Wait 10 msec
        //OSTimeDlyHMSM(0u, 0u, 0u, 10,
        //            OS_OPT_TIME_HMSM_STRICT,
        //            &err);
        if(gp_sci6_rx_state == RX_RECEIVED)
        {
          // Transfer contents of received characters to buffer
            gp_sci6_rx_state = RX_COMPLETE;
        }
      }
      return(0x00);
    }
    else
      // Can't task if we are busy with another event.
      return(0xff);
  } // END of RX_CHAR_WAIT Processing
  else
    return(0xff);
}

/***********************************************************************************************************************
* Function Name: r_sci6_Setup
* Description  : This sets up all needed callbacks for the BSP
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
unsigned char R_SCI6_Setup( void)
{
	bsp_int_err_t err;

	/* Register Transmit end _callback() to be called whenever a SCI6 Transmit ends. */
	err = R_BSP_InterruptWrite(BSP_INT_SRC_BL0_SCI6_TEI6, (bsp_int_cb_t)r_sci6_transmitend_interrupt);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	/* Register Receive Error _callback() to be called whenever a SCI6 Receive Error occurs. */
	err = R_BSP_InterruptWrite(BSP_INT_SRC_BL0_SCI6_ERI6, (bsp_int_cb_t)r_sci6_receiveerror_interrupt);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	// Set internal States ready for operation.
	gp_sci6_tx_state = TX_COMPLETE;
	gp_sci6_rx_state = RX_COMPLETE;

	return 0;

}

/***********************************************************************************************************************
* Function Name: r_sci6_Disable
* Description  : This Enables Group Interrupts.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
unsigned char R_SCI6_Disable( void)
{
	bsp_int_err_t err;


	/* Disable SCI6 Transmit ends Interrupt. */
	err = R_BSP_InterruptControl(BSP_INT_SRC_BL0_SCI6_TEI6,
								BSP_INT_CMD_GROUP_INTERRUPT_DISABLE,
								FIT_NO_PTR);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	/* Disable SCI6 Receive Error Interrupt. */
	err = R_BSP_InterruptControl(BSP_INT_SRC_BL0_SCI6_ERI6,
								BSP_INT_CMD_GROUP_INTERRUPT_DISABLE,
								FIT_NO_PTR);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	return 0;
}

/***********************************************************************************************************************
* Function Name: r_sci6_Enable
* Description  : This Enables Group Interrupts.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
unsigned char R_SCI6_Enable( void)
{
	bsp_int_err_t err;
	bsp_int_ctrl_t data1;

	data1.ipl = 5;	// Set Priority to 5.

	/* Enable SCI6 Transmit ends Interrupt. */
	err = R_BSP_InterruptControl(BSP_INT_SRC_BL0_SCI6_TEI6,
								BSP_INT_CMD_GROUP_INTERRUPT_ENABLE,
								(void *)&data1);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	/* Enable SCI6 Receive Error Interrupt. */
	err = R_BSP_InterruptControl(BSP_INT_SRC_BL0_SCI6_ERI6,
								BSP_INT_CMD_GROUP_INTERRUPT_ENABLE,
								(void *)&data1);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	return 0;
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: sci6_getRxComplete
* Description  : This function returns the status of the Current SPI RX Complete Operation
* Arguments    : None
* Return Value : uint8_t Status:		0 - Waiting on Event Complete.
* 										1 - Event Complete
***********************************************************************************************************************/
uint8_t	sci6_getRxComplete( void )
{
	return sci6_Rx_Complete;
}

/***********************************************************************************************************************
* Function Name: sci6_getTxComplete
* Description  : This function returns the status of the Current SPI TX Complete Operation
* Arguments    : None
* Return Value : uint8_t Status:		0 - Waiting on Event Complete.
* 										1 - Event Complete
***********************************************************************************************************************/
uint8_t	sci6_getTxComplete( void )
{
	return sci6_Tx_Complete;
}

/***********************************************************************************************************************
* Function Name: sci6_getSPIError
* Description  : This function returns the status of the Current SPI Error Status.
* Arguments    : None
* Return Value : uint8_t Status:		0 - No Errors
* 										1 - Error During event.
***********************************************************************************************************************/
uint8_t	sci6_getSPIError( void )
{
	return sci6_Error;
}

#if 0
/***********************************************************************************************************************
* Function Name: r_sci6_Setup
* Description  : This sets up all needed callbacks for the BSP
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
unsigned char R_SCI6_Setup( void)
{
	bsp_int_err_t err;

	// Init Special State.

	/* Register Transmit end _callback() to be called whenever a SCI5 Transmit ends. */
	err = R_BSP_InterruptWrite(BSP_INT_SRC_BL0_SCI6_TEI6, (bsp_int_cb_t)r_sci6_callback_transmitend);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	/* Register Receive Error _callback() to be called whenever a SCI5 Receive Error occurs. */
	err = R_BSP_InterruptWrite(BSP_INT_SRC_BL0_SCI6_ERI6, (bsp_int_cb_t)r_sci6_callback_receiveerror);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	// Set internal States ready for operation.
	//gp_sci5_tx_state = TX_COMPLETE;
	//gp_sci5_rx_state = RX_COMPLETE;

	return 0;

}


/***********************************************************************************************************************
* Function Name: r_sci6_Enable
* Description  : This Enables Group Interrupts.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
unsigned char R_SCI6_Enable( void)
{
	bsp_int_err_t err;
	bsp_int_ctrl_t data1;

	data1.ipl = 5;	// Set Priority to 5.

	/* Enable SCI5 Transmit ends Interrupt. */
	err = R_BSP_InterruptControl(BSP_INT_SRC_BL0_SCI5_TEI5,
								BSP_INT_CMD_GROUP_INTERRUPT_ENABLE,
								(void *)&data1);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	/* Enable SCI5 Receive Error Interrupt. */
	err = R_BSP_InterruptControl(BSP_INT_SRC_BL0_SCI5_ERI5,
								BSP_INT_CMD_GROUP_INTERRUPT_ENABLE,
								(void *)&data1);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	return 0;
}
#endif

#if 0
/***********************************************************************************************************************
* Function Name: r_sci6_Setup
* Description  : This sets up all needed callbacks for the BSP
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
unsigned char R_SCI6_Setup( void )
{
	bsp_int_err_t err;

	// Init Special State.
	Special_SCI_State = 0;

	/* Register Transmit end _callback() to be called whenever a SCI5 Transmit ends. */
	err = R_BSP_InterruptWrite(BSP_INT_SRC_BL0_SCI6_TEI6, (bsp_int_cb_t)r_sci6_transmitend_interrupt);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	/* Register Receive Error _callback() to be called whenever a SCI5 Receive Error occurs. */
	err = R_BSP_InterruptWrite(BSP_INT_SRC_BL0_SCI6_ERI6, (bsp_int_cb_t)r_sci6_receiveerror_interrupt);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	// Set internal States ready for operation.
	//gp_sci5_tx_state = TX_COMPLETE;
	//gp_sci5_rx_state = RX_COMPLETE;

	return 0;

}
#endif

#if 0
/***********************************************************************************************************************
* Function Name: r_sci6_Enable
* Description  : This Enables Group Interrupts.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
unsigned char R_SCI6_Enable( void )
{
	bsp_int_err_t err;
	bsp_int_ctrl_t data1;

	data1.ipl = 5;	// Set Priority to 5.

	/* Enable SCI5 Transmit ends Interrupt. */
	err = R_BSP_InterruptControl(BSP_INT_SRC_BL0_SCI6_TEI6,
								BSP_INT_CMD_GROUP_INTERRUPT_ENABLE,
								(void *)&data1);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	/* Enable SCI5 Receive Error Interrupt. */
	err = R_BSP_InterruptControl(BSP_INT_SRC_BL0_SCI6_ERI6,
								BSP_INT_CMD_GROUP_INTERRUPT_ENABLE,
								(void *)&data1);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	return 0;
}

/***********************************************************************************************************************
* Function Name: r_sci6_Disable
* Description  : This Enables Group Interrupts.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
unsigned char R_SCI6_Disable( void )
{
	bsp_int_err_t err;


	/* Enable SCI5 Transmit ends Interrupt. */
	err = R_BSP_InterruptControl(BSP_INT_SRC_BL0_SCI6_TEI6,
								BSP_INT_CMD_GROUP_INTERRUPT_DISABLE,
								FIT_NO_PTR);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	/* Enable SCI5 Receive Error Interrupt. */
	err = R_BSP_InterruptControl(BSP_INT_SRC_BL0_SCI6_ERI6,
								BSP_INT_CMD_GROUP_INTERRUPT_DISABLE,
								FIT_NO_PTR);
	if (BSP_INT_SUCCESS != err)
	{
		return 0xff;
	}

	return 0;
}
#endif

/* End user code. Do not edit comment generated here */
