/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file contains all the functions prototypes for
  *                      the gpio Controls including control of Enable Pins,
  *                      Power Pins, and control of generic IO Pins.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2020 Cold Laser Therapeutics LLC
  * 		Created on: Nov 27, 2020
  * 		Author: rprui
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of WeatherCloud nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/******************************************************************************
 *
 * Module Includes
 *
 *****************************************************************************/
#include "r_flash_rx_if.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LaserP.h"
#include "gpio.h"

/*****************************************************************************
 *
 * Signal Bit Definitions
 *
 ****************************************************************************/

/******************************************************************************
 *
 * Module Variables
 *
 *****************************************************************************/

/******************************************************************************
 *
 * Routines
 *
 *****************************************************************************/

/*****************************************************************************
 *
 * routine: GPIO_Init
 * Date: 	November 27, 2020
 * Updated: November 27, 2020
 * Author:  Ralph Pruitt
 * This routine Performs the initialization for all custom IO Pins for use in
 * the PLM PLUS Design.
 *
 * INPUT: None
 *
 * OUTPUT: None
 *****************************************************************************/
void GPIO_Init(void)
{
	/*
	 * LD3_LF_Enable:	(Output/ Active LOW/ Enable Low Frequency Laser Diode 3)
	 * 		Output/High
	 */
	PORT0.PODR.BIT.B5 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P05: HIGH Output
	PORT0.PMR.BIT.B5 = 0;				// 22.3.4 Port Mode Register (PMR)(Pg 785)...P05: Uses the pin as a general I/O pin.
	PORT0.PDR.BIT.B5 = 1;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P05: OUTPUT

	/*
	 * LD4_LF_Enable:	(Output/ Active LOW/ Enable Low Frequency Laser Diode 4)
	 * 		Output/High
	 */
	PORT0.PODR.BIT.B7 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P07: HIGH Output
	PORT0.PMR.BIT.B7 = 0;				// 22.3.4 Port Mode Register (PMR)(Pg 785)...P07: Uses the pin as a general I/O pin.
	PORT0.PDR.BIT.B7 = 1;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P07: OUTPUT

	/*
	 * LD12_LF_Enable:	(Output/ Active LOW/ Enable Low Frequency Laser Diode 1 and Laser Diode 2)
	 * 		Output/High
	 */
	PORT9.PODR.BIT.B2 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P92: HIGH Output
	PORT9.DSCR.BIT.B2 = 1;				// 22.3.8 Drive Capacity Control Register (DSCR)(Pg 789) ...P92: High-drive output
	PORT9.PMR.BIT.B2 = 0;				// 22.3.4 Port Mode Register (PMR)(Pg 785)...P92: Uses the pin as a general I/O pin.
	PORT9.PDR.BIT.B2 = 1;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P92: OUTPUT

	/*
	 * HF_Laser_Enable:	(Output/ Active Low/ HF Laser Power Supply Enable)
	 * 		Output/High
	 */
	PORT2.PODR.BIT.B5 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P03: High Output
	PORT2.PMR.BIT.B5 = 0;				// 22.3.4 Port Mode Register (PMR)(Pg 785)...P03: Uses the pin as a general I/O pin.
	PORT2.PDR.BIT.B5 = 1;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P03: OUTPUT

	/*
	 * HF_Laser_Flt:	(Input/ Active Low/ HF Laser Power Switch Fault Detect)
	 * 		Tristate/Input
	 */
	PORT3.PDR.BIT.B3 = 0;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P33: Input

	/*
	 * PLL_CLK_EN:	(Output/ Active High/ HF Clock Enable)
	 * 		Output/Low
	 */
	PORT9.PODR.BIT.B3 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P93: LOW Output
	PORT9.DSCR.BIT.B3 = 1;				// 22.3.8 Drive Capacity Control Register (DSCR)(Pg 789) ...P93: High-drive output
	PORT9.PMR.BIT.B3 = 0;				// 22.3.4 Port Mode Register (PMR)(Pg 785)...P93: Uses the pin as a general I/O pin.
	PORT9.PDR.BIT.B3 = 1;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P93: OUTPUT

	/*
	 * EFR32_RESET:	(Output/ Active Low/ Reset Bluetooth Module/ DISABLED)
	 * 		Output/High
	 */
	PORTA.PODR.BIT.B3 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...PA3: HIGH Output
	PORTA.DSCR.BIT.B3 = 1;				// 22.3.8 Drive Capacity Control Register (DSCR)(Pg 789) ...PA3: High-drive output
	PORTA.PMR.BIT.B3 = 0;				// 22.3.4 Port Mode Register (PMR)(Pg 785)...PA3: Uses the pin as a general I/O pin.
	PORTA.PDR.BIT.B3 = 1;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	PA3: OUTPUT

	/*
	 * LD0_HF_ENABLE:	(Output/ Active Low/ Enable HF Laser 1 Driver Circuit)
	 * 		Output/High
	 */
	PORTE.PODR.BIT.B0 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...PE0: HIGH Output
	PORTE.DSCR.BIT.B0 = 1;				// 22.3.8 Drive Capacity Control Register (DSCR)(Pg 789) ...PE0: High-drive output
	PORTE.PMR.BIT.B0 = 0;				// 22.3.4 Port Mode Register (PMR)(Pg 785)...PE0: Uses the pin as a general I/O pin.
	PORTE.PDR.BIT.B0 = 1;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	PE0: OUTPUT

	/*
	 * LD1_HF_ENABLE:	(Output/ Active Low/ Enable HF Laser 2 Driver Circuit)
	 * 		Output/High
	 */
	PORTE.PODR.BIT.B1 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...PE1: HIGH Output
	PORTE.DSCR.BIT.B1 = 1;				// 22.3.8 Drive Capacity Control Register (DSCR)(Pg 789) ...PE1: High-drive output
	PORTE.PMR.BIT.B1 = 0;				// 22.3.4 Port Mode Register (PMR)(Pg 785)...PE1: Uses the pin as a general I/O pin.
	PORTE.PDR.BIT.B1 = 1;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	PE1: OUTPUT

	/*
	 * LD2_HF_ENABLE:	(Output/ Active Low/ Enable HF Laser 3 Driver Circuit)
	 * 		Output/High
	 */
	PORT2.PODR.BIT.B2 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P22: HIGH Output
	PORT2.PMR.BIT.B2 = 0;				// 22.3.4 Port Mode Register (PMR)(Pg 785)...P22: Uses the pin as a general I/O pin.
	PORT2.PDR.BIT.B2 = 1;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P22: OUTPUT
	/*
	 * LD3_HF_ENABLE:	(Output/ Active Low/ Enable HF Laser 4 Driver Circuit)
	 * 		Output/High
	 */
	PORT2.PODR.BIT.B3 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P23: HIGH Output
	PORT2.PMR.BIT.B3 = 0;				// 22.3.4 Port Mode Register (PMR)(Pg 785)...P23: Uses the pin as a general I/O pin.
	PORT2.PDR.BIT.B3 = 1;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P23: OUTPUT
}

/*****************************************************************************
 *
 * routine: GPIO_Sleep
 * Date: 	November 27, 2020
 * Updated: November 27, 2020
 * Author:  Ralph Pruitt
 * This routine all critical external IO Pins into low power mode. Many of these
 * are placed into a Tri-State High Impedance Input State.
 *
 * INPUT: None
 *
 * OUTPUT: None
 *****************************************************************************/
void GPIO_Sleep(void)
{
	/*
	 * LD3_LF_Enable:	(Output/ Active LOW/ Enable Low Frequency Laser Diode 3)
	 * 		Tristate/Input
	 */
	PORT0.PDR.BIT.B5 = 0;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P05: Input

	/*
	 * LD4_LF_Enable:	(Output/ Active LOW/ Enable Low Frequency Laser Diode 4)
	 * 		Tristate/Input
	 */
	PORT0.PDR.BIT.B7 = 0;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P07: Input

	/*
	 * LD12_LF_Enable:	(Output/ Active LOW/ Enable Low Frequency Laser Diode 1 and Laser Diode 2)
	 * 		Tristate/Input
	 */
	PORT9.PDR.BIT.B2 = 0;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P92: Input

	/*
	 * HF_Laser_Enable:	(Output/ Active High/ HF Laser Power Supply Enable)
	 * 		Tristate/Input
	 */
	PORT2.PDR.BIT.B5 = 0;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P25: Input

	/*
	 * HF_Laser_Flt:	(Input/ Active Low/ HF Laser Power Switch Fault Detect)
	 * 		Tristate/Input
	 */
	PORT3.PDR.BIT.B3 = 0;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P33: Input

	/*
	 * PLL_CLK_EN:	(Output/ Active High/ HF Clock Enable)
	 * 		Tristate/Input
	 */
	PORT9.PDR.BIT.B3 = 0;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P93: Input

	/*
	 * EFR32_RESET:	(Output/ Active Low/ Reset Bluetooth Module/ DISABLED)
	 * 		Tristate/Input
	 */
	PORTA.PDR.BIT.B3 = 0;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	PA3: Input

	/*
	 * LD0_HF_ENABLE:	(Output/ Active Low/ Enable HF Laser 1 Driver Circuit)
	 * 		Tristate/Input
	 */
	PORTE.PDR.BIT.B0 = 0;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	PE0: Input

	/*
	 * LD1_HF_ENABLE:	(Output/ Active Low/ Enable HF Laser 2 Driver Circuit)
	 * 		Tristate/Input
	 */
	PORTE.PDR.BIT.B1 = 0;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	PE1: Input

	/*
	 * LD2_HF_ENABLE:	(Output/ Active Low/ Enable HF Laser 3 Driver Circuit)
	 * 		Tristate/Input
	 */
	PORT2.PDR.BIT.B2 = 0;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P22: Input

	/*
	 * LD3_HF_ENABLE:	(Output/ Active Low/ Enable HF Laser 4 Driver Circuit)
	 * 		Tristate/Input
	 */
	PORT2.PDR.BIT.B3 = 0;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P23: Input

	/*
	 * (Output/ Active Low/ PLLC Enable)(Init handled by R_SCI6_Create(void))
	 * 		Tristate/Input
	 */
	PORT0.PDR.BIT.B3 = 0;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P03: Input

	/*
	 * (Output/ Active Low/ PLLD Enable)(Init handled by R_SCI6_Create(void))
	 * 		Tristate/Input
	 */
	PORT2.PDR.BIT.B4 =  0;				// 22.3.1 Port Direction Register (PDR)(Pg 782)	P24: INPUT

}

/*****************************************************************************
 *
 * routine: PLMpls_gpio_On
 * Date: 	November 27, 2020
 * Updated: November 27, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine Turns selected gpio On.
 *
 * INPUT:
 * 	@param  PLM_PLUS_io_TypeDef 	-	Port
 *
 * OUTPUT:
 * 	@retval int		- None
 *****************************************************************************/
/**
  * @brief  Turns selected gpio On.
  * @param  Led: Specifies the gpio to be set on.
  *   This parameter can be one of following parameters:
  * @retval None
  */
void PLMpls_gpio_On(PLM_PLUS_io_TypeDef Port)
{
	switch ( Port )
	{
	case P_ENP:
		PORT9.PODR.BIT.B0 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P90:
		break;
	case P_EN:
		PORT9.PODR.BIT.B1 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P91:
		break;
	case HF_Laser_Enable:
		PORT2.PODR.BIT.B5 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P03:
		break;
	case LCDPWR:
		PORT6.PODR.BIT.B4 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P64:
		break;
	case SDPWREN:
		PORT4.PODR.BIT.B6 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P46:
		break;
	case BCKLGHT:
		PORT6.PODR.BIT.B5 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P65:
		break;
	case EFR32_RESET:
		PORTA.PODR.BIT.B3 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...PA3:
		break;
	case LD3_LF_Enable:
		PORT0.PODR.BIT.B5 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P05:
		break;
	case LD4_LF_Enable:
		PORT0.PODR.BIT.B7 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P07:
		break;
	case LD12_LF_Enable:
		PORT9.PODR.BIT.B2 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P92:
		break;
	case PLL_CLK_EN:
		PORT9.PODR.BIT.B3 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P93:
		break;
	case PLLC_Enable:
		PORT0.PODR.BIT.B3 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P03:
		break;
	case PLLD_Enable:
		PORT2.PODR.BIT.B4 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P24:
		break;
	case LD0_HF_ENABLE:
		PORTE.PODR.BIT.B0 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...PE0:
		break;
	case LD1_HF_ENABLE:
		PORTE.PODR.BIT.B1 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...PE1:
		break;
	case LD2_HF_ENABLE:
		PORT2.PODR.BIT.B2 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P22:
		break;
	case LD3_HF_ENABLE:
		PORT2.PODR.BIT.B3 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P23:
		break;
	} // EndSwitch ( Port )
}

/*****************************************************************************
 *
 * routine: PLMpls_gpio_Off
 * Date: 	November 27, 2020
 * Updated: November 27, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine Turns selected gpio Off.
 *
 * INPUT:
 * 	@param  PLM_PLUS_io_TypeDef 	-	Port
 *
 * OUTPUT:
 * 	@retval int		- None
 *****************************************************************************/
void PLMpls_gpio_Off(PLM_PLUS_io_TypeDef Port)
{
	switch ( Port )
	{
	case P_ENP:
		PORT9.PODR.BIT.B0 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P90:
		break;
	case P_EN:
		PORT9.PODR.BIT.B1 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P91:
		break;
	case HF_Laser_Enable:
		PORT2.PODR.BIT.B5 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P03:
		break;
	case LCDPWR:
		PORT6.PODR.BIT.B4 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P64:
		break;
	case SDPWREN:
		PORT4.PODR.BIT.B6 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P46:
		break;
	case BCKLGHT:
		PORT6.PODR.BIT.B5 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P65:
		break;
	case EFR32_RESET:
		PORTA.PODR.BIT.B3 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...PA3:
		break;
	case LD3_LF_Enable:
		PORT0.PODR.BIT.B5 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P05:
		break;
	case LD4_LF_Enable:
		PORT0.PODR.BIT.B7 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P07:
		break;
	case LD12_LF_Enable:
		PORT9.PODR.BIT.B2 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P92:
		break;
	case PLL_CLK_EN:
		PORT9.PODR.BIT.B3 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P93:
		break;
	case PLLC_Enable:
		PORT0.PODR.BIT.B3 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P03:
		break;
	case PLLD_Enable:
		PORT2.PODR.BIT.B4 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P24:
		break;
	case LD0_HF_ENABLE:
		PORTE.PODR.BIT.B0 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...PE0:
		break;
	case LD1_HF_ENABLE:
		PORTE.PODR.BIT.B1 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...PE1:
		break;
	case LD2_HF_ENABLE:
		PORT2.PODR.BIT.B2 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P22:
		break;
	case LD3_HF_ENABLE:
		PORT2.PODR.BIT.B3 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P23:
		break;
	} // EndSwitch ( Port )
}

/*****************************************************************************
 *
 * routine: PLMpls_gpio_Toggle
 * Date: 	November 27, 2020
 * Updated: November 27, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine Toggles the selected gpio.
 *
 * INPUT:
 * 	@param  PLM_PLUS_io_TypeDef 	-	Port
 *
 * OUTPUT:
 * 	@retval int		- None
 *****************************************************************************/
void PLMpls_gpio_Toggle(PLM_PLUS_io_TypeDef Port)
{
	uint8_t Read_Val;
	switch ( Port )
	{
	case P_ENP:
		// Read Pin
		Read_Val = PORT9.PIDR.BIT.B0;
		if (Read_Val)
			PORT9.PODR.BIT.B0 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P90:
		else
			PORT9.PODR.BIT.B0 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P90:
		break;
	case P_EN:
		// Read Pin
		Read_Val = PORT9.PIDR.BIT.B1;
		if (Read_Val)
			PORT9.PODR.BIT.B1 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P91:
		else
			PORT9.PODR.BIT.B1 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P91:
		break;
	case HF_Laser_Enable:
		// Read Pin
		Read_Val = PORT2.PIDR.BIT.B5;
		if (Read_Val)
			PORT2.PODR.BIT.B5 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P03:
		else
			PORT2.PODR.BIT.B5 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P03:
		break;
	case LCDPWR:
		// Read Pin
		Read_Val = PORT6.PIDR.BIT.B4;
		if (Read_Val)
			PORT6.PODR.BIT.B4 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P64:
		else
			PORT6.PODR.BIT.B4 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P64:
		break;
	case SDPWREN:
		// Read Pin
		Read_Val = PORT4.PIDR.BIT.B6;
		if (Read_Val)
			PORT4.PODR.BIT.B6 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P46:
		else
			PORT4.PODR.BIT.B6 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P46:
		break;
	case BCKLGHT:
		// Read Pin
		Read_Val = PORT6.PIDR.BIT.B5;
		if (Read_Val)
			PORT6.PODR.BIT.B5 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P65:
		else
			PORT6.PODR.BIT.B5 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P65:
		break;
	case EFR32_RESET:
		// Read Pin
		Read_Val = PORTA.PIDR.BIT.B3;
		if (Read_Val)
			PORTA.PODR.BIT.B3 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...PA3:
		else
			PORTA.PODR.BIT.B3 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...PA3:
		break;
	case LD3_LF_Enable:
		// Read Pin
		Read_Val = PORT0.PIDR.BIT.B5;
		if (Read_Val)
			PORT0.PODR.BIT.B5 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P05:
		else
			PORT0.PODR.BIT.B5 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P05:
		break;
	case LD4_LF_Enable:
		// Read Pin
		Read_Val = PORT0.PIDR.BIT.B7;
		if (Read_Val)
			PORT0.PODR.BIT.B7 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P07:
		else
			PORT0.PODR.BIT.B7 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P07:
		break;
	case LD12_LF_Enable:
		// Read Pin
		Read_Val = PORT9.PIDR.BIT.B2;
		if (Read_Val)
			PORT9.PODR.BIT.B2 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P92:
		else
			PORT9.PODR.BIT.B2 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P92:
		break;
	case PLL_CLK_EN:
		// Read Pin
		Read_Val = PORT9.PIDR.BIT.B3;
		if (Read_Val)
			PORT9.PODR.BIT.B3 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P93:
		else
			PORT9.PODR.BIT.B3 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P93:
		break;
	case PLLC_Enable:
		// Read Pin
		Read_Val = PORT0.PIDR.BIT.B3;
		if (Read_Val)
			PORT0.PODR.BIT.B3 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P03:
		else
			PORT0.PODR.BIT.B3 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P03:
		break;
	case PLLD_Enable:
		// Read Pin
		Read_Val = PORT2.PIDR.BIT.B4;
		if (Read_Val)
			PORT2.PODR.BIT.B4 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P24:
		else
			PORT2.PODR.BIT.B4 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P24:
		break;
	case LD0_HF_ENABLE:
		// Read Pin
		Read_Val = PORTE.PIDR.BIT.B0;
		if (Read_Val)
			PORTE.PODR.BIT.B0 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...PE0:
		else
			PORTE.PODR.BIT.B0 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...PE0:
		break;
	case LD1_HF_ENABLE:
		// Read Pin
		Read_Val = PORTE.PIDR.BIT.B1;
		if (Read_Val)
			PORTE.PODR.BIT.B1 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...PE1:
		else
			PORTE.PODR.BIT.B1 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...PE1:
		break;
	case LD2_HF_ENABLE:
		// Read Pin
		Read_Val = PORT2.PIDR.BIT.B2;
		if (Read_Val)
			PORT2.PODR.BIT.B2 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P22:
		else
			PORT2.PODR.BIT.B2 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P22:
		break;
	case LD3_HF_ENABLE:
		// Read Pin
		Read_Val = PORT2.PIDR.BIT.B3;
		if (Read_Val)
			PORT2.PODR.BIT.B3 = 0;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P23:
		else
			PORT2.PODR.BIT.B3 = 1;				// 22.3.2 Port Output Data Register (PODR)(Pg 783)...P23:
		break;
	} // EndSwitch ( Port )
}

/*****************************************************************************
 *
 * routine: PLMpls_gpio_GetPort
 * Date: 	November 27, 2020
 * Updated: November 27, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine Gets Port from Port Structure.
 *
 * INPUT:
 * 	@param  PLM_PLUS_io_TypeDef 	-	Port
 *
 * OUTPUT:
 * 	@retval int: Port 	-	0-255:	Port Value
 * 							-1: 	ERROR
 *****************************************************************************/
int PLMpls_gpio_GetPort(PLM_PLUS_io_TypeDef Port)
{
	switch ( Port )
	{
	case P_ENP:
		return PORT9.PIDR.BYTE;
	case P_EN:
		return PORT9.PIDR.BYTE;
	case HF_Laser_Enable:
		return PORT2.PIDR.BYTE;
	case LCDPWR:
		return PORT6.PIDR.BYTE;
	case SDPWREN:
		return PORT4.PIDR.BYTE;
	case BCKLGHT:
		return PORT6.PIDR.BYTE;
	case EFR32_RESET:
		return PORTA.PIDR.BYTE;
	case LD3_LF_Enable:
		return PORT0.PIDR.BYTE;
	case LD4_LF_Enable:
		return PORT0.PIDR.BYTE;
	case LD12_LF_Enable:
		return PORT9.PIDR.BYTE;
	case PLL_CLK_EN:
		return PORT9.PIDR.BYTE;
	case PLLC_Enable:
		return PORT0.PIDR.BYTE;
	case PLLD_Enable:
		return PORT2.PIDR.BYTE;
	case LD0_HF_ENABLE:
		return PORTE.PIDR.BYTE;
	case LD1_HF_ENABLE:
		return PORTE.PIDR.BYTE;
	case LD2_HF_ENABLE:
		return PORT2.PIDR.BYTE;
	case LD3_HF_ENABLE:
		return PORT2.PIDR.BYTE;
	case PinDiode0:
		return PORT4.PIDR.BYTE;
	case PinDiode1:
		return PORT4.PIDR.BYTE;
	case PinDiode2:
		return PORT4.PIDR.BYTE;
	case PinDiode3:
		return PORT4.PIDR.BYTE;
	case HF_Laser_Flt:
		return PORT3.PIDR.BYTE;
	case BATVLTG:
		return PORT4.PIDR.BYTE;
	case START:
		return PORT4.PIDR.BYTE;
	default:
		return -1;
	} // EndSwitch ( Port )
}

/*****************************************************************************
 *
 * routine: PLMpls_gpio_GetPortPin
 * Date: 	November 27, 2020
 * Updated: November 27, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine Gets Port Pin from Port Structure.
 *
 * INPUT:
 * 	@param  PLM_PLUS_io_TypeDef 	-	Port
 *
 * OUTPUT:
 * 	@retval int: Port 	-	0-1:	Pin
 * 							-1: 	ERROR
 *****************************************************************************/
int PLMpls_gpio_GetPortPin(PLM_PLUS_io_TypeDef Port)
{
	switch ( Port )
	{
	case P_ENP:
		return PORT9.PIDR.BIT.B0;
	case P_EN:
		return PORT9.PIDR.BIT.B1;
	case HF_Laser_Enable:
		return PORT2.PIDR.BIT.B5;
	case LCDPWR:
		return PORT6.PIDR.BIT.B4;
	case SDPWREN:
		return PORT4.PIDR.BIT.B6;
	case BCKLGHT:
		return PORT6.PIDR.BIT.B5;
	case EFR32_RESET:
		return PORTA.PIDR.BIT.B3;
	case LD3_LF_Enable:
		return PORT0.PIDR.BIT.B5;
	case LD4_LF_Enable:
		return PORT0.PIDR.BIT.B7;
	case LD12_LF_Enable:
		return PORT9.PIDR.BIT.B2;
	case PLL_CLK_EN:
		return PORT9.PIDR.BIT.B3;
	case PLLC_Enable:
		return PORT0.PIDR.BIT.B3;
	case PLLD_Enable:
		return PORT2.PIDR.BIT.B4;
	case LD0_HF_ENABLE:
		return PORTE.PIDR.BIT.B0;
	case LD1_HF_ENABLE:
		return PORTE.PIDR.BIT.B1;
	case LD2_HF_ENABLE:
		return PORT2.PIDR.BIT.B2;
	case LD3_HF_ENABLE:
		return PORT2.PIDR.BIT.B3;
	case PinDiode0:
		return PORT4.PIDR.BIT.B1;
	case PinDiode1:
		return PORT4.PIDR.BIT.B2;
	case PinDiode2:
		return PORT4.PIDR.BIT.B3;
	case PinDiode3:
		return PORT4.PIDR.BIT.B4;
	case HF_Laser_Flt:
		return PORT3.PIDR.BIT.B3;
	case BATVLTG:
		return PORT4.PIDR.BIT.B0;
	case START:
		return PORT4.PIDR.BIT.B5;
	default:
		return -1;
	} // EndSwitch ( Port )
}

/*****************************************************************************
 *
 * routine: PLMpls_gpio_ReadPin
 * Date: 	November 27, 2020
 * Updated: November 27, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine Gets Port Pin from Port Structure.
 *
 * INPUT:
 * 	@param  PLM_PLUS_io_TypeDef 	-	Port
 *
 * OUTPUT:
 * 	@retval GPIO_PinState	-	Port State:		0:	GPIO_PIN_RESET
 * 												1:	GPIO_PIN_SET
 * 												2:  GPIO_ERROR
 *****************************************************************************/
GPIO_PinState PLMpls_gpio_ReadPin(PLM_PLUS_io_TypeDef Port)
{
	int PortVal;

	switch ( Port )
	{
	case P_ENP:
		PortVal = PORT9.PIDR.BIT.B0;
		break;
	case P_EN:
		PortVal = PORT9.PIDR.BIT.B1;
		break;
	case HF_Laser_Enable:
		PortVal = PORT2.PIDR.BIT.B5;
		break;
	case LCDPWR:
		PortVal = PORT6.PIDR.BIT.B4;
		break;
	case SDPWREN:
		PortVal = PORT4.PIDR.BIT.B6;
		break;
	case BCKLGHT:
		PortVal = PORT6.PIDR.BIT.B5;
		break;
	case EFR32_RESET:
		PortVal = PORTA.PIDR.BIT.B3;
		break;
	case LD3_LF_Enable:
		PortVal = PORT0.PIDR.BIT.B5;
		break;
	case LD4_LF_Enable:
		PortVal = PORT0.PIDR.BIT.B7;
		break;
	case LD12_LF_Enable:
		PortVal = PORT9.PIDR.BIT.B2;
		break;
	case PLL_CLK_EN:
		PortVal = PORT9.PIDR.BIT.B3;
		break;
	case PLLC_Enable:
		PortVal = PORT0.PIDR.BIT.B3;
		break;
	case PLLD_Enable:
		PortVal = PORT2.PIDR.BIT.B4;
		break;
	case LD0_HF_ENABLE:
		PortVal = PORTE.PIDR.BIT.B0;
		break;
	case LD1_HF_ENABLE:
		PortVal = PORTE.PIDR.BIT.B1;
		break;
	case LD2_HF_ENABLE:
		PortVal = PORT2.PIDR.BIT.B2;
		break;
	case LD3_HF_ENABLE:
		PortVal = PORT2.PIDR.BIT.B3;
		break;
	case PinDiode0:
		PortVal = PORT4.PIDR.BIT.B1;
		break;
	case PinDiode1:
		PortVal = PORT4.PIDR.BIT.B2;
		break;
	case PinDiode2:
		PortVal = PORT4.PIDR.BIT.B3;
		break;
	case PinDiode3:
		PortVal = PORT4.PIDR.BIT.B4;
		break;
	case HF_Laser_Flt:
		PortVal = PORT3.PIDR.BIT.B3;
		break;
	case BATVLTG:
		PortVal = PORT4.PIDR.BIT.B0;
		break;
	case START:
		PortVal = PORT4.PIDR.BIT.B5;
		break;
	default:
		PortVal = -1;
		break;
	} // EndSwitch ( Port )
	if (PortVal > 0)
		return GPIO_PIN_SET;
	else if (PortVal == 0)
		return GPIO_PIN_RESET;
	else
		return GPIO_ERROR;
}

/*****************************************************************************
 *
 * routine: PLMpls_LFlaser_enable
 * Date: 	December 1, 2020
 * Updated: December 1, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine Enables the Sink Pins for the LF Laser Drivers
 *
 * INPUT:
 * 	@param PLM_PLUS_Laser_TypeDef 	-	laserCntl: The Enums for this selection:
 * 						LASER12_CNTL:		LF Laser 1 and Laser 2 Control
 * 						LASER3_CNTL:		LF Laser 3 Control
 * 						LASER4_CNTL:		LF Laser 4 Control
 * 						LASERALL_CNTL:		All LF Laser Control(Lasers 1-4)
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef PLMpls_LFlaser_enable( PLM_PLUS_Laser_TypeDef laserCntl )
{
	switch ( laserCntl )
	{
	case LASER12_CNTL:
		// Enable LF Laser 12 Driver.
		PLMpls_gpio_Off( LD12_LF_Enable );
		return HAL_OK;
		break;
	case LASER3_CNTL:
		// Enable LF Laser 3 Driver.
		PLMpls_gpio_Off( LD3_LF_Enable );
		return HAL_OK;
		break;
	case LASER4_CNTL:
		// Enable LF Laser 4 Driver.
		PLMpls_gpio_Off( LD4_LF_Enable );
		return HAL_OK;
		break;
	case LASERALL_CNTL:
		// Enable ALL LF Laser Drivers
		PLMpls_gpio_Off( LD12_LF_Enable );
		PLMpls_gpio_Off( LD3_LF_Enable );
		PLMpls_gpio_Off( LD4_LF_Enable );
		return HAL_OK;
		break;
	default:
		return HAL_ERROR;
		break;
	} // EndSwitch ( laserCntl )
}

/*****************************************************************************
 *
 * routine: PLMpls_LFlaser_disable
 * Date: 	December 1, 2020
 * Updated: December 1, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine disbales the Sink Pins for the LF Laser Drivers
 *
 * INPUT:
 * 	@param PLM_PLUS_Laser_TypeDef 	-	laserCntl: The Enums for this selection:
 * 						LASER12_CNTL:		LF Laser 1 and Laser 2 Control
 * 						LASER3_CNTL:		LF Laser 3 Control
 * 						LASER4_CNTL:		LF Laser 4 Control
 * 						LASERALL_CNTL:		All LF Laser Control(Lasers 1-4)
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef PLMpls_LFlaser_disable( PLM_PLUS_Laser_TypeDef laserCntl )
{
	switch ( laserCntl )
	{
	case LASER12_CNTL:
		// Enable LF Laser 12 Driver.
		PLMpls_gpio_On( LD12_LF_Enable );
		return HAL_OK;
		break;
	case LASER3_CNTL:
		// Enable LF Laser 3 Driver.
		PLMpls_gpio_On( LD3_LF_Enable );
		return HAL_OK;
		break;
	case LASER4_CNTL:
		// Enable LF Laser 4 Driver.
		PLMpls_gpio_On( LD4_LF_Enable );
		return HAL_OK;
		break;
	case LASERALL_CNTL:
		// Enable ALL LF Laser Drivers
		PLMpls_gpio_On( LD12_LF_Enable );
		PLMpls_gpio_On( LD3_LF_Enable );
		PLMpls_gpio_On( LD4_LF_Enable );
		return HAL_OK;
		break;
	default:
		return HAL_ERROR;
		break;
	} // EndSwitch ( laserCntl )
}

/*****************************************************************************
 *
 * routine: PLMpls_HFlaser_enable
 * Date: 	December 1, 2020
 * Updated: December 1, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine Enables the HF Laser Drivers
 *
 * INPUT:
 * 	@param PLM_PLUS_HFLaser_TypeDef 	-	laserCntl: The Enums for this selection:
 * 						HF_LSR1_CNTL:		HF Laser 1 Control
 * 						HF_LSR2_CNTL:		HF Laser 2 Control
 * 						HF_LSR3_CNTL:		HF Laser 3 Control
 * 						HF_LSR4_CNTL:		HF Laser 4 Control
 * 						HF_LSR12_CNTL:		HF Laser 1 and Laser 2 Control
 * 						HF_LSR34_CNTL:		HF Laser 3 and Laser 4 Control
 * 						HF_LSR_ALL_CNTL:	All HF Laser Control(Lasers 1-4)
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef PLMpls_HFlaser_enable( PLM_PLUS_HFLaser_TypeDef laserCntl )
{
	switch ( laserCntl )
	{
	case HF_LSR1_CNTL:
		// Enable HF Laser 1 Driver.
		PLMpls_gpio_Off( LD0_HF_ENABLE );
		return HAL_OK;
		break;
	case HF_LSR2_CNTL:
		// Enable HF Laser 2 Driver.
		PLMpls_gpio_Off( LD1_HF_ENABLE );
		return HAL_OK;
		break;
	case HF_LSR3_CNTL:
		// Enable HF Laser 3 Driver.
		PLMpls_gpio_Off( LD2_HF_ENABLE );
		return HAL_OK;
		break;
	case HF_LSR4_CNTL:
		// Enable HF Laser 4 Driver.
		PLMpls_gpio_Off( LD3_HF_ENABLE );
		return HAL_OK;
		break;
	case HF_LSR12_CNTL:
		// Enable HF Laser 1 and Laser 2 Drivers.
		PLMpls_gpio_Off( LD0_HF_ENABLE );
		PLMpls_gpio_Off( LD1_HF_ENABLE );
		return HAL_OK;
		break;
	case HF_LSR34_CNTL:
		// Enable HF Laser 3 and Laser 4 Drivers.
		PLMpls_gpio_Off( LD2_HF_ENABLE );
		PLMpls_gpio_Off( LD3_HF_ENABLE );
		return HAL_OK;
		break;
	case HF_LSR_ALL_CNTL:
		// Enable ALL HF Laser Drivers
		PLMpls_gpio_Off( LD0_HF_ENABLE );
		PLMpls_gpio_Off( LD1_HF_ENABLE );
		PLMpls_gpio_Off( LD2_HF_ENABLE );
		PLMpls_gpio_Off( LD3_HF_ENABLE );
		return HAL_OK;
		break;
	default:
		return HAL_ERROR;
		break;
	} // EndSwitch ( laserCntl )
}

/*****************************************************************************
 *
 * routine: PLMpls_HFlaser_disable
 * Date: 	December 1, 2020
 * Updated: December 1, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine disables the HF Laser Drivers.
 *
 * INPUT:
 * 	@param PLM_PLUS_HFLaser_TypeDef 	-	laserCntl: The Enums for this selection:
 * 						HF_LSR1_CNTL:		HF Laser 1 Control
 * 						HF_LSR2_CNTL:		HF Laser 2 Control
 * 						HF_LSR3_CNTL:		HF Laser 3 Control
 * 						HF_LSR4_CNTL:		HF Laser 4 Control
 * 						HF_LSR12_CNTL:		HF Laser 1 and Laser 2 Control
 * 						HF_LSR34_CNTL:		HF Laser 3 and Laser 4 Control
 * 						HF_LSR_ALL_CNTL:	All HF Laser Control(Lasers 1-4)
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef PLMpls_HFlaser_disable( PLM_PLUS_HFLaser_TypeDef laserCntl )
{
	switch ( laserCntl )
	{
	case HF_LSR1_CNTL:
		// Enable HF Laser 1 Driver.
		PLMpls_gpio_On( LD0_HF_ENABLE );
		return HAL_OK;
		break;
	case HF_LSR2_CNTL:
		// Enable HF Laser 2 Driver.
		PLMpls_gpio_On( LD1_HF_ENABLE );
		return HAL_OK;
		break;
	case HF_LSR3_CNTL:
		// Enable HF Laser 3 Driver.
		PLMpls_gpio_On( LD2_HF_ENABLE );
		return HAL_OK;
		break;
	case HF_LSR4_CNTL:
		// Enable HF Laser 4 Driver.
		PLMpls_gpio_On( LD3_HF_ENABLE );
		return HAL_OK;
		break;
	case HF_LSR12_CNTL:
		// Enable HF Laser 1 and Laser 2 Drivers.
		PLMpls_gpio_On( LD0_HF_ENABLE );
		PLMpls_gpio_On( LD1_HF_ENABLE );
		return HAL_OK;
		break;
	case HF_LSR34_CNTL:
		// Enable HF Laser 3 and Laser 4 Drivers.
		PLMpls_gpio_On( LD2_HF_ENABLE );
		PLMpls_gpio_On( LD3_HF_ENABLE );
		return HAL_OK;
		break;
	case HF_LSR_ALL_CNTL:
		// Enable ALL HF Laser Drivers
		PLMpls_gpio_On( LD0_HF_ENABLE );
		PLMpls_gpio_On( LD1_HF_ENABLE );
		PLMpls_gpio_On( LD2_HF_ENABLE );
		PLMpls_gpio_On( LD3_HF_ENABLE );
		return HAL_OK;
		break;
	default:
		return HAL_ERROR;
		break;
	} // EndSwitch ( laserCntl )
}

/*****************************************************************************
 *
 * routine: Template
 * Date: 	November 27, 2020
 * Updated: November 27, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine is a TEMPLATE.
 *
 * INPUT:
 * 	@param  int		- Template Variable
 *
 * OUTPUT:
 * 	@retval int		- Template Output
 *****************************************************************************/


/******************************************************************************
 *
 * END OF MODULE
 *
 *****************************************************************************/

