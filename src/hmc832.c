/*****************************************************************************
 * hmc832.c
 *
 *  Created on: Nov 24, 2020
 *      Author: rprui
 *  This is all the support code to interface with the the HMC832 Fractional-N PLL
 *  with Integrated VCO 25 MHz to 3000 MHz.
 *
 *****************************************************************************
 * Laser Pulsar Embedded Software
 * Date: November 24, 2020
 * Designer: Ralph Pruitt
 * Property: Cold Laser Therapeutics, LLC
 * Copyright: November 24, 2020
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
#include <stdbool.h>
#include <math.h>
#include "LaserP.h"
#include "hmc832.h"
#include "gpio.h"
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "r_cg_sci.h"

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
static uint8_t PLL_State[TOTAL_PLLS];	// Current State of PLL Hardware.

/******************************************************************************
 *
 * Routines
 *
 *****************************************************************************/

/*****************************************************************************
 *
 * routine: hmc_spi_init
 * Date: 	November 28, 2020
 * Updated: November 28, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine performs the low level init of the HMC SPI Bus. It
 * then flushes the SPI channel in preperation of SPi communication to PLLC
 * and PLLD..
 *
 * INPUT:
 * 	@param  None
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef hmc_spi_init(void) {
	int x;
	uint8_t TempBuffr[10];
	uint8_t RxBuffr[10];
	MD_STATUS err1;

	// Set Hardware No Init.
	PLL_State[PLL_C_HW] = NOT_INIT;
	PLL_State[PLL_D_HW] = NOT_INIT;

	// Initialize and start SCI6/SPI.
	if (R_SCI6_Setup() != 0)		// Setup callbacks for SCI6.
			{
		// Set Hardware Error.
		PLL_State[PLL_C_HW] = INIT_ERR;
		PLL_State[PLL_D_HW] = INIT_ERR;
		// return Error Status.
		return HAL_ERROR;
	}
	if (R_SCI6_Enable() != 0)		// Enable Ints for SCI6.
			{
		// Set Hardware Error.
		PLL_State[PLL_C_HW] = INIT_ERR;
		PLL_State[PLL_D_HW] = INIT_ERR;
		// return Error Status.
		return HAL_ERROR;
	}
	R_SCI6_Create();
	R_SCI6_Start();

	/************************************************************
	 *
	 * 		Flush SPI(SCI6) Bus and Verify Operation.
	 *
	 ***********************************************************/
	// Clear Buffers
	for (x = 0; x < 10; x++) {
		TempBuffr[x] = 0x00;
		RxBuffr[x] = 0x00;
	}

	// Initialize SPI Bus Enable Pins low.
	PLMpls_gpio_Off(PLLC_Enable);// Clear PLLC SPI Enable Pin(PLLC_Enable)(Input to PLLC)
	PLMpls_gpio_Off(PLLD_Enable);// Clear PLLD SPI Enable Pin(PLLD_Enable)(Input to PLLD)

	// Now Cycle SPI Bus with a 32 Bit Operation to Flsuh Contents...
	TempBuffr[0] = 0x00;		// Bits 16-23 Data
	TempBuffr[1] = 0x00;		// Bits 08-15 Data
	TempBuffr[2] = 0x00;		// Bits 00-07 Data
	TempBuffr[3] = 0x00;		// Bits 3-7: R0-R4	Bits0-2: A0-A2

	err1 = R_SCI6_SPI_Send(TempBuffr, 4, RxBuffr, 0);
	if (err1 == MD_OK) {
		// We Are Good Time to Clean up Enable Pins.
		PLMpls_gpio_On(PLLC_Enable);// Set PLLC SPI Enable Pin(PLLC_Enable)(Input to PLLC)
		PLMpls_gpio_On(PLLD_Enable);// Set PLLD SPI Enable Pin(PLLD_Enable)(Input to PLLD)

		accurate_delay(1);

		// Set Hardware ready to task.
		PLL_State[PLL_C_HW] = AVAILABLE;
		PLL_State[PLL_D_HW] = AVAILABLE;
		// return Good Status.
		return HAL_OK;
	} else {
		// Set Hardware Error.
		PLL_State[PLL_C_HW] = INIT_ERR;
		PLL_State[PLL_D_HW] = INIT_ERR;
		// return Error Status.
		return HAL_ERROR;
	}
}

/*****************************************************************************
 *
 * routine: hmc_spi_write
 * Date: 	November 28, 2020
 * Updated: November 28, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine performs a write operation to the Target PLL and PLL
 * Register. It sets the target register to the data passed.
 *
 * INPUT:
 *  @param	PLL_Hardware hmc_hw		// HMC Hardware to target command.
 *  									PLL_C_HW
 *  									PLL_D_HW
 * 	@param  uint8_t PLL_Register	// HMC register to write
 * 	@param	pll_registers pll_data	// PLL Data to pass to HMC Hardware
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
#define ENABLE_DELAY	5	// Delay between Enable and Disable of PLL before and after transfer of data.
HAL_StatusTypeDef hmc_spi_write(PLL_Hardware hmc_hw, uint8_t PLL_Register,
		pll_registers pll_data) {
	int x;
	uint8_t TempBuffr[10];
	uint8_t RxBuffr[10];
	MD_STATUS err1;
	PLL_Port_Regs Port_Data;

	// Verify parameters.
	if ((hmc_hw < PLL_C_HW) || (hmc_hw > PLL_D_HW))
		return HAL_ERROR;
//	if (PLL_Register > (uint8_t) BLTIN_STST_REG)
	if (PLL_Register > (uint8_t) 0x1F)
		return HAL_ERROR;

	// Now validate if Hardware is available
	if (PLL_State[hmc_hw] != AVAILABLE)
		return HAL_ERROR;

	// Ready to Task Command.
	// Clear Buffers
	for (x = 0; x < 10; x++) {
		TempBuffr[x] = 0x00;
		RxBuffr[x] = 0x00;
	}

	// Time to Build final command. First Transfer in Data
	Port_Data.PLL_Port.DATA = (pll_data.Data & 0xffffff);
	// Now load Address to buffer.
	Port_Data.PLL_Port.ADDRESS = PLL_Register;
	// Last blank out Chip Address.
	Port_Data.PLL_Port.CHIP_ADDR = 0x00;

	// Transfer full command to Buffer.
	TempBuffr[0] = Port_Data.DString[3];		// Load Data....MSB
	TempBuffr[1] = Port_Data.DString[2];		// Load Data
	TempBuffr[2] = Port_Data.DString[1];		// Load Data
	TempBuffr[3] = Port_Data.DString[0];		// Load Data....LSB

	// Write Command.
	if (hmc_hw == PLL_C_HW)
		PLMpls_gpio_Off(PLLC_Enable);		// Clear PLLC SPI Enable
	else
		PLMpls_gpio_Off(PLLD_Enable);		// Clear PLLD SPI Enable

	// Wait ENABLE_DELAY usec
	short_delay( ENABLE_DELAY );

	// Send Data to SPI Bus.
	err1 = R_SCI6_SPI_Send(TempBuffr, 4, RxBuffr, 0);

	// Wait ENABLE_DELAY usec
	short_delay( ENABLE_DELAY );

	if (hmc_hw == PLL_C_HW)
		PLMpls_gpio_On(PLLC_Enable);		// Set PLLC SPI Enable
	else
		PLMpls_gpio_On(PLLD_Enable);		// Set PLLD SPI Enable

	// Check for error
	if (err1 != MD_OK)
		return HAL_ERROR;
	else
		return HAL_OK;
}

/*****************************************************************************
 *
 * routine: hmc_spi_write_read
 * Date: 	November 28, 2020
 * Updated: November 28, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine performs a write operation to the Target PLL and PLL
 * Register. It sets the target register to the data passed.
 *
 * INPUT:
 *  @param	PLL_Hardware hmc_hw		// HMC Hardware to target command.
 *  									PLL_C_HW
 *  									PLL_D_HW
 * 	@param  uint8_t PLL_Register	// HMC register to write
 * 	@param	pll_registers pll_data	// PLL Data to pass to HMC Hardware
 * 	@param	pll_registers *Rd_Data_Ptr 	// Pointer to Returned Data from HMC Hardware.
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef hmc_spi_write_read(PLL_Hardware hmc_hw, uint8_t PLL_Register,
		pll_registers pll_data, PLL_Port_Regs *Rd_Data_Ptr) {
	int x;
	uint8_t TempBuffr[10];
	uint8_t RxBuffr[10];
	MD_STATUS err1;
	PLL_Port_Regs Port_Data;
	pll_registers pll_data1;

	// Verify parameters.
	if ((hmc_hw < PLL_C_HW) || (hmc_hw > PLL_D_HW))
		return HAL_ERROR;
//	if (PLL_Register > (uint8_t) BLTIN_STST_REG)
	if (PLL_Register > (uint8_t) 0x1F)
		return HAL_ERROR;

	// Now validate if Hardware is available
	if (PLL_State[hmc_hw] != AVAILABLE)
		return HAL_ERROR;

	// Ready to Task Command.
	// Clear Buffers
	for (x = 0; x < 10; x++) {
		TempBuffr[x] = 0x00;
		RxBuffr[x] = 0x00;
	}

	// Time to Build final command. First Transfer in Data
	Port_Data.PLL_Port.DATA = (pll_data.Data & 0xffffff);
	// Now load Address to buffer.
	Port_Data.PLL_Port.ADDRESS = PLL_Register;
	// Last blank out Chip Address.
	Port_Data.PLL_Port.CHIP_ADDR = 0x00;

	// Transfer full command to Buffer.
	TempBuffr[0] = Port_Data.DString[3];		// Load Data....MSB
	TempBuffr[1] = Port_Data.DString[2];		// Load Data
	TempBuffr[2] = Port_Data.DString[1];		// Load Data
	TempBuffr[3] = Port_Data.DString[0];		// Load Data....LSB

	// Write Command.
	if (hmc_hw == PLL_C_HW)
		PLMpls_gpio_Off(PLLC_Enable);		// Clear PLLC SPI Enable
	else
		PLMpls_gpio_Off(PLLD_Enable);		// Clear PLLD SPI Enable

	// Wait ENABLE_DELAY usec
	short_delay( ENABLE_DELAY );

	// Send Data to SPI Bus.
	//err1 = R_SCI6_SPI_Send( TempBuffr, 4, RxBuffr, 0 );
	//err1 = R_SCI6_SPI_Receive2(TempBuffr, 4, RxBuffr, 4, 30, hmc_hw);
	err1 = R_SCI6_SPI_Receive(TempBuffr, 4, RxBuffr, 4);


	// Wait ENABLE_DELAY usec
	short_delay( ENABLE_DELAY );

	if (hmc_hw == PLL_C_HW)
		PLMpls_gpio_On(PLLC_Enable);		// Set PLLC SPI Enable
	else
		PLMpls_gpio_On(PLLD_Enable);		// Set PLLD SPI Enable

	// Check for error
	if (err1 != MD_OK)
		return HAL_ERROR;

	// Delay 100 usec before next event.
//	short_delay(100);
	/*
	 * Time to read Data from Target Register.
	 */

	// Build New Command to read from Key Register.

	// 1. Clear pll_data1;
	pll_data1.Data = 0x00;

	// 2. Build in PLL_Register
	pll_data1.chip_idRD.Read_Adr = PLL_Register;

	// 3. Now Finish building command for read...
	// Time to Build final command. First Transfer in Data
	Port_Data.PLL_Port.DATA = (pll_data1.Data & 0xffffff);
	// Now load Address to buffer.
	Port_Data.PLL_Port.ADDRESS = 0x00;
	// Last blank out Chip Address.
	Port_Data.PLL_Port.CHIP_ADDR = 0x00;

	// Transfer full command to Buffer.
	// NEW BETTER CODE
	TempBuffr[0] = Port_Data.DString[3];		// Load Data....MSB
	TempBuffr[1] = Port_Data.DString[2];		// Load Data
	TempBuffr[2] = Port_Data.DString[1];		// Load Data
	TempBuffr[3] = Port_Data.DString[0];		// Load Data....LSB

	// Blank out Address and Chip Address.
	TempBuffr[3] = 0x00;

//#if 0
	// Write Command.
	if (hmc_hw == PLL_C_HW)
		PLMpls_gpio_Off(PLLC_Enable);		// Clear PLLC SPI Enable
	else
		PLMpls_gpio_Off(PLLD_Enable);		// Clear PLLD SPI Enable

	// Wait ENABLE_DELAY usec
	short_delay( ENABLE_DELAY );
//#endif
	// Read Data from SPI Bus.
	err1 = R_SCI6_SPI_Receive(TempBuffr, 4, RxBuffr, 4);

	// Wait ENABLE_DELAY usec
	short_delay( ENABLE_DELAY );

	if (hmc_hw == PLL_C_HW)
		PLMpls_gpio_On(PLLC_Enable);		// Set PLLC SPI Enable
	else
		PLMpls_gpio_On(PLLD_Enable);		// Set PLLD SPI Enable

	// Delay 1 msec.
	accurate_delay(1);

	/*
	 * Perform a Second Read to get True Value.....
	 */
	// Transfer full command to Buffer.
	// NEW BETTER CODE
	TempBuffr[0] = Port_Data.DString[3];		// Load Data....MSB
	TempBuffr[1] = Port_Data.DString[2];		// Load Data
	TempBuffr[2] = Port_Data.DString[1];		// Load Data
	TempBuffr[3] = Port_Data.DString[0];		// Load Data....LSB

	// Blank out Address and Chip Address.
	TempBuffr[3] = 0x00;

//#if 0
	// Write Command.
	if (hmc_hw == PLL_C_HW)
		PLMpls_gpio_Off(PLLC_Enable);		// Clear PLLC SPI Enable
	else
		PLMpls_gpio_Off(PLLD_Enable);		// Clear PLLD SPI Enable

	// Wait ENABLE_DELAY usec
	short_delay( ENABLE_DELAY );
//#endif
	// Read Data from SPI Bus.
	err1 = R_SCI6_SPI_Receive(TempBuffr, 4, RxBuffr, 4);

	// Wait ENABLE_DELAY usec
	short_delay( ENABLE_DELAY );

	if (hmc_hw == PLL_C_HW)
		PLMpls_gpio_On(PLLC_Enable);		// Set PLLC SPI Enable
	else
		PLMpls_gpio_On(PLLD_Enable);		// Set PLLD SPI Enable

	// Delay 1 msec.
	accurate_delay(1);

	if (err1 == MD_OK) {
		// NEW BETTER CODE
		// Time to Build final Report. First Transfer in Data
		Port_Data.DString[3] = RxBuffr[0];		// Load Data....MSB
		Port_Data.DString[2] = RxBuffr[1];		// Load Data
		Port_Data.DString[1] = RxBuffr[2];		// Load Data
		Port_Data.DString[0] = RxBuffr[3];		// Load Data....LSB
		Rd_Data_Ptr->DATA = Port_Data.DATA;
		return HAL_OK;
	} else
		return HAL_ERROR;
}

/*****************************************************************************
 *
 * routine: hmc_Self_Test
 * Date: 	November 28, 2020
 * Updated: November 28, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine verified the Chip ID and then performs a Self Test on
 * the Target PLL.
 *
 * INPUT:
 *  @param	PLL_Hardware hmc_hw		// HMC Hardware to target command.
 *  									PLL_C_HW
 *  									PLL_D_HW
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef hmc_Self_Test(PLL_Hardware hmc_hw) {
	int x;
	pll_registers pll_data1, pll_rxdata1;
	PLL_Port_Regs pll_rxdata2;

	// Verify parameters.
	if ((hmc_hw < PLL_C_HW) || (hmc_hw > PLL_D_HW))
		return HAL_ERROR;
	// Must Force PLL to be Available.
	PLL_State[hmc_hw] = AVAILABLE;

	// Clear Buffers
	for (x = 0; x < PLL_STRNG_LEN; x++) {
		pll_data1.DString[x] = 0x00;
		pll_rxdata1.DString[x] = 0x00;
	}

	pll_data1.chip_id.CHIP_ID = 0x000000;
	if (hmc_spi_write_read(hmc_hw, CHIP_ID_REG, pll_data1, &pll_rxdata2)
			== HAL_OK) {
		pll_rxdata1.Data = pll_rxdata2.PLL_Port.DATA;
		// Test Chip ID received
		if (pll_rxdata1.chip_id.CHIP_ID == CHIP_ID_VAL) {
			PLL_State[hmc_hw] = AVAILABLE;
			return HAL_OK;
		} else {
			PLL_State[hmc_hw] = INIT_ERR;
			return HAL_ERROR;
		}
	} else
		return HAL_ERROR;
}

/*****************************************************************************
 *
 * routine: hmc_verify_hw
 * Date: 	November 30, 2020
 * Updated: November 30, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine returns true if the selected hardware is available.
 *
 * INPUT:
 *  @param	PLL_Hardware hmc_hw		// HMC Hardware to target command.
 *  									PLL_C_HW
 *  									PLL_D_HW
 *
 * OUTPUT:
 * 	@retval bool	-	TRUE	= 1:	Selected HW is AVAILABLE.
 * 						FALSE	= 0:	Selected HW is not available.
 *
 *****************************************************************************/
bool hmc_verify_hw(PLL_Hardware hmc_hw) {
	// Now validate if Hardware is available
	if (PLL_State[hmc_hw] != AVAILABLE)
		return FALSE;
	else
		return TRUE;
}

/*****************************************************************************
 *
 * routine: hmc_pll_powerDn
 * Date: 	November 30, 2020
 * Updated: November 30, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine powers down the selected PLL by programming the RST
 * register.
 *
 * INPUT:
 *  @param	PLL_Hardware hmc_hw		// HMC Hardware to target command.
 *  									PLL_C_HW
 *  									PLL_D_HW
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef hmc_pll_powerDn(PLL_Hardware hmc_hw) {
	int x;
	pll_registers pll_data1;
	PLL_Port_Regs pll_rxdata2;

	// Verify parameters.
	if ((hmc_hw < PLL_C_HW) || (hmc_hw > PLL_D_HW))
		return HAL_ERROR;
	// Must Force PLL to be Available.
	PLL_State[hmc_hw] = AVAILABLE;

	// Clear Buffers
	for (x = 0; x < PLL_STRNG_LEN; x++) {
		pll_data1.DString[x] = 0x00;
	}

	pll_data1.reset.RST_CHIPEN_PIN_SELECT = 0x00;// Bit 0: 0 = take PLL enable via SPI (RST_CHIPEN_FROM_SPI) Register 0x01[1]
	pll_data1.reset.RST_CHIPEN_FROM_SPI = 0x00;	// Bit 1: 0 = Soft reset for both SPI modes (set to 0 for proper operation).
	pll_data1.reset.RST_INT_BIAS_REF_SRC = 0x00;// Bit 2: 0 = Soft reset Internal bias reference sources (set to 0 for proper operation).
	pll_data1.reset.RST_PD_BLOCK = 0x00;// Bit 3: 0 = Soft reset PD block (set to 0 for proper operation).
	pll_data1.reset.RST_CP_BLOCK = 0x00;// Bit 4: 0 = Soft reset CP block (set to 0 for proper operation).
	pll_data1.reset.RST_REF_PATH_BFFR = 0x00;// Bit 5: 0 = Soft reset Reference path buffer (set to 0 for proper operation).
	pll_data1.reset.RST_VCO_PATH_BFFR = 0x00;// Bit 6: 0 = Soft reset VCO path buffer (set to 0 for proper operation).
	pll_data1.reset.RST_DGTL_IO_TST_PDS = 0x00;	// Bit 7: 0 = Soft reset Digital I/O test pads (set to 0 for proper operation).
	if (hmc_spi_write_read(hmc_hw, RESET_REG, pll_data1, &pll_rxdata2)
			== HAL_OK) {
		PLL_State[hmc_hw] = AVAILABLE;
		return HAL_OK;
	} else {
		PLL_State[hmc_hw] = ERR_DET;
		return HAL_ERROR;
	}
}

/*****************************************************************************
 *
 * routine: hmc_pll_powerUp
 * Date: 	November 30, 2020
 * Updated: November 30, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine powers Up the selected PLL by programming the RST
 * register.
 *
 * INPUT:
 *  @param	PLL_Hardware hmc_hw		// HMC Hardware to target command.
 *  									PLL_C_HW
 *  									PLL_D_HW
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef hmc_pll_powerUp(PLL_Hardware hmc_hw) {
	int x;
	pll_registers pll_data1;
	PLL_Port_Regs pll_rxdata2;

	// Verify parameters.
	if ((hmc_hw < PLL_C_HW) || (hmc_hw > PLL_D_HW))
		return HAL_ERROR;
	// Must Force PLL to be Available.
	PLL_State[hmc_hw] = AVAILABLE;

	// Clear Buffers
	for (x = 0; x < PLL_STRNG_LEN; x++) {
		pll_data1.DString[x] = 0x00;
	}

	pll_data1.reset.RST_CHIPEN_PIN_SELECT = 0x00;// Bit 0: 0 = take PLL enable via SPI (RST_CHIPEN_FROM_SPI) Register 0x01[1]
	pll_data1.reset.RST_CHIPEN_FROM_SPI = 0x01;	// Bit 1: 1 = Enable both SPI modes (set to 0 for proper operation).
	pll_data1.reset.RST_INT_BIAS_REF_SRC = 0x01;// Bit 2: 1 = Enable Internal bias reference sources (set to 0 for proper operation).
	pll_data1.reset.RST_PD_BLOCK = 0x01;// Bit 3: 1 = Enable PD block (set to 0 for proper operation).
	pll_data1.reset.RST_CP_BLOCK = 0x01;// Bit 4: 1 = Enable CP block (set to 0 for proper operation).
	pll_data1.reset.RST_REF_PATH_BFFR = 0x01;// Bit 5: 1 = Enable Reference path buffer (set to 0 for proper operation).
	pll_data1.reset.RST_VCO_PATH_BFFR = 0x01;// Bit 6: 1 = Enable VCO path buffer (set to 0 for proper operation).
	pll_data1.reset.RST_DGTL_IO_TST_PDS = 0x01;	// Bit 7: 1 = Enable Digital I/O test pads (set to 0 for proper operation).

	if (hmc_spi_write_read(hmc_hw, RESET_REG, pll_data1, &pll_rxdata2)
			== HAL_OK) {
		PLL_State[hmc_hw] = AVAILABLE;
		return HAL_OK;
	} else {
		PLL_State[hmc_hw] = ERR_DET;
		return HAL_ERROR;
	}
}

/*****************************************************************************
 *
 * routine: hmc_vco_write
 * Date: 	November 28, 2020
 * Updated: November 28, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine performs a write operation to the Target VCO Register
 * through selected PLL. It sets the target register to the data passed.
 *
 * INPUT:
 *  @param	PLL_Hardware hmc_hw		// HMC Hardware to target command.
 *  									PLL_C_HW
 *  									PLL_D_HW
 * 	@param  uint8_t vco_Register	// HMC VCO register to write
 * 	@param	vco_registers vco_data	// VCO Data to pass to HMC Hardware
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef hmc_vco_write(PLL_Hardware hmc_hw, uint8_t vco_Register,
		vco_registers vco_data) {
	int x;
	pll_registers pll_data1;
	PLL_Port_Regs pll_rxdata2;

	// Verify parameters.
	if ((hmc_hw < PLL_C_HW) || (hmc_hw > PLL_D_HW))
		return HAL_ERROR;
	// Now validate if Hardware is available
	if (PLL_State[hmc_hw] != AVAILABLE)
		return HAL_ERROR;

	// Clear Buffers
	for (x = 0; x < PLL_STRNG_LEN; x++) {
		pll_data1.DString[x] = 0x00;
	}

	// Time to Build final command. First Transfer in Data
	pll_data1.spi_vco.VCO_DATA = (vco_data.Data & 0x03FF);
	// Now load Address to buffer.
	pll_data1.spi_vco.VCO_REGADDR = vco_Register;
	// Last blank out Chip Address.
	pll_data1.spi_vco.VCO_ID = 0x00;
	if (hmc_spi_write_read(hmc_hw, SPI_VCO_REG, pll_data1, &pll_rxdata2)
			== HAL_OK) {
		PLL_State[hmc_hw] = AVAILABLE;
		return HAL_OK;
	} else {
		PLL_State[hmc_hw] = ERR_DET;
		return HAL_ERROR;
	}
}

/*****************************************************************************
 *
 * routine: hmc_vco_powerDn
 * Date: 	November 30, 2020
 * Updated: November 30, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine powers down the selected VCO in a PLL by programming
 * the VCO ENABLE REGISTER.
 *
 * INPUT:
 *  @param	PLL_Hardware hmc_hw		// HMC Hardware to target command.
 *  									PLL_C_HW
 *  									PLL_D_HW
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef hmc_vco_powerDn(PLL_Hardware hmc_hw) {
	vco_registers vco_data1;

	// Verify parameters.
	if ((hmc_hw < PLL_C_HW) || (hmc_hw > PLL_D_HW))
		return HAL_ERROR;
	// Must Force PLL to be Available.
	PLL_State[hmc_hw] = AVAILABLE;

	// Clear vco_data1
	vco_data1.Data = 0x0000;

	vco_data1.vco_ENAB.MSTR_ENAB_VCO_SBSYSTM = 0x00;	// Bit 0: all VCO subsystem blocks are turned off.
	vco_data1.vco_ENAB.VCO_ENABLE = 0x00;				// Bit 1: Enables VCOs.
	vco_data1.vco_ENAB.PLL_BFFR_ENABLE = 0x00;			// Bit 2: Enables PLL buffer to N divider.
	vco_data1.vco_ENAB.IN_OUT_MSTR_ENABLE = 0x00;		// Bit 3: Enables output stage and the output divider. It does not enable/disable the VCO.
	vco_data1.vco_ENAB.RESERVED1 = 0x00;				// Bit 4: RESERVED
	vco_data1.vco_ENAB.OUT_STGE_ENABLE = 0x00;			// Bit 5: Output stage enable.
	vco_data1.vco_ENAB.RESERVED2 = 0x00;				// Bits 6-7:	RESERVED
	vco_data1.vco_ENAB.RESERVED3 = 0x00;				// Bit 8:		RESERVED
	if (hmc_vco_write(hmc_hw, VCO_ENAB_REG, vco_data1) == HAL_OK) {
		PLL_State[hmc_hw] = AVAILABLE;
		return HAL_OK;
	} else {
		PLL_State[hmc_hw] = ERR_DET;
		return HAL_ERROR;
	}
}

/*****************************************************************************
 *
 * routine: hmc_vco_powerUp
 * Date: 	November 30, 2020
 * Updated: November 30, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine powers Up the selected VCO in a PLL by programming
 * the VCO ENABLE REGISTER.
 *
 * INPUT:
 *  @param	PLL_Hardware hmc_hw		// HMC Hardware to target command.
 *  									PLL_C_HW
 *  									PLL_D_HW
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef hmc_vco_powerUp(PLL_Hardware hmc_hw) {
	vco_registers vco_data1;

	// Verify parameters.
	if ((hmc_hw < PLL_C_HW) || (hmc_hw > PLL_D_HW))
		return HAL_ERROR;
	// Must Force PLL to be Available.
	PLL_State[hmc_hw] = AVAILABLE;

	// Clear vco_data1
	vco_data1.Data = 0x0000;

	vco_data1.vco_ENAB.MSTR_ENAB_VCO_SBSYSTM = 0x01;	// Bit 0: all VCO subsystem blocks are turned off.
	vco_data1.vco_ENAB.VCO_ENABLE = 0x01;				// Bit 1: Enables VCOs.
	vco_data1.vco_ENAB.PLL_BFFR_ENABLE = 0x01;			// Bit 2: Enables PLL buffer to N divider.
	vco_data1.vco_ENAB.IN_OUT_MSTR_ENABLE = 0x01;		// Bit 3: Enables output stage and the output divider. It does not enable/disable the VCO.
	vco_data1.vco_ENAB.RESERVED1 = 0x01;				// Bit 4: RESERVED
	vco_data1.vco_ENAB.OUT_STGE_ENABLE = 0x01;			// Bit 5: Output stage enable.
	vco_data1.vco_ENAB.RESERVED2 = 0x03;				// Bits 6-7:	RESERVED
	vco_data1.vco_ENAB.RESERVED3 = 0x01;				// Bit 8:		RESERVED
	if (hmc_vco_write(hmc_hw, VCO_ENAB_REG, vco_data1) == HAL_OK) {
		PLL_State[hmc_hw] = AVAILABLE;
		return HAL_OK;
	} else {
		PLL_State[hmc_hw] = ERR_DET;
		return HAL_ERROR;
	}
}

/*****************************************************************************
 *
 * routine: hmc_sleep_plls
 * Date: 	November 30, 2020
 * Updated: November 30, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine powers down both PLLs and related VCOs.
 *
 * INPUT:
 *  @param	None
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef hmc_sleep_plls(void) {
	HAL_StatusTypeDef Status;

	Status = HAL_OK;

	// Power Down Clock Circuit.
	PLMpls_gpio_Off(PLL_CLK_EN);		// Disable HF Clock by Setting Pin Low.

	/*
	 * Disable VCO Output .
	 */
	if (hmc_Disable_VCO(PLL_C_HW) != HAL_OK)
		Status = HAL_ERROR;
	if (hmc_Disable_VCO(PLL_D_HW) != HAL_OK)
		Status = HAL_ERROR;

	/*
	 * Power Down VCOs.
	 */
	if (hmc_vco_powerDn(PLL_C_HW) != HAL_OK)
		Status = HAL_ERROR;
	if (hmc_vco_powerDn(PLL_D_HW) != HAL_OK)
		Status = HAL_ERROR;

	/*
	 * Power Down PLLs.
	 */
	if (hmc_pll_powerDn(PLL_C_HW) != HAL_OK)
		Status = HAL_ERROR;
	if (hmc_pll_powerDn(PLL_D_HW) != HAL_OK)
		Status = HAL_ERROR;

	return Status;
}

/*****************************************************************************
 *
 * routine: hmc_powerup_plls
 * Date: 	November 30, 2020
 * Updated: November 30, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine powers up both PLLs and related VCOs.
 *
 * INPUT:
 *  @param	None
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef hmc_powerup_plls(void) {
	HAL_StatusTypeDef Status;

	Status = HAL_OK;

	/*
	 * Power Up PLLs.
	 */
	if (hmc_pll_powerUp(PLL_C_HW) != HAL_OK)
		Status = HAL_ERROR;
	if (hmc_pll_powerUp(PLL_D_HW) != HAL_OK)
		Status = HAL_ERROR;

	/*
	 * Disable VCO Output until needed.
	 */
	if (hmc_Disable_VCO(PLL_C_HW) != HAL_OK)
		Status = HAL_ERROR;
	if (hmc_Disable_VCO(PLL_D_HW) != HAL_OK)
		Status = HAL_ERROR;

	/*
	 * Power Up VCOs.
	 */
	if (hmc_vco_powerUp(PLL_C_HW) != HAL_OK)
		Status = HAL_ERROR;
	if (hmc_vco_powerUp(PLL_D_HW) != HAL_OK)
		Status = HAL_ERROR;

	// Power Up Clock Circuit.
	PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

	return Status;
}

/*****************************************************************************
 *
 * routine: hmc_calc_parameters
 * Date: 	December 2, 2020
 * Updated: December 2, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine Calculates all the key Factors from the passed Freq
 * in the passed Structure Pointer.
 *
 * INPUT:
 *  @param	PLL_Parameters *pll_paramPtr	-	Pointer to Parameter Structure
 *  		float		Desired_Freq:		Target Frequency to Setup Parameters
 *  		uint32_t	R_Divider:			Reference Divider to use with
 *  											Baseline Frequency
 *  		uint32_t	Output_Divider:		VCO Output Divider: VCO_REG 0x02 VCO
 *  											Output Divider
 *  		uint32_t	N_Divider_int:		N Divider Int: Frequency Register,
 *  											Integer Part (Default 0x000019)
 *  		uint32_t	N_Divider_frac:		N Divider Frac: Register 0x04,
 *  											Frequency Register, Fractional Part
 *  											(Default 0x000000)
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef hmc_calc_parameters(PLL_Parameters *pll_paramPtr) {
	float temp_Out_Freq, N_Ratio_float;
	if ((pll_paramPtr->Desired_Freq < HMC_MIN_HFREQ)
			|| (pll_paramPtr->Desired_Freq > HMC_MAX_FREQ)) {
		return HAL_ERROR;
	}

	if (pll_paramPtr->Desired_Freq < HMC_THRESH_FREQ)
		// Calculate Target Output Ratio.
		pll_paramPtr->Output_Divider = (HMC_LOW_VCO_FREQ
				/ pll_paramPtr->Desired_Freq);
	else
		// Calculate Target Output Ratio.
		pll_paramPtr->Output_Divider = (HMC_HIGH_VCO_FREQ
				/ pll_paramPtr->Desired_Freq);

	// Now, Calculate True Output Frequency.
	temp_Out_Freq = (pll_paramPtr->Desired_Freq * pll_paramPtr->Output_Divider);

	// OK...Time to Calculate the N Ratio
	N_Ratio_float = (temp_Out_Freq / HMC_BASE_OSC_FREQ);

	// Now Build Int Variant for Structure.
	pll_paramPtr->N_Divider_int = floor(N_Ratio_float);

	// Now Build Fraction for Structure.
	pll_paramPtr->N_Divider_frac = (N_Ratio_float - pll_paramPtr->N_Divider_int)
			* HMC_FRAC_FACTOR;

	return HAL_OK;
}

/*****************************************************************************
 *
 * routine: hmc_SetupFreq
 * Date: 	December 2, 2020
 * Updated: December 2, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine Calculates all the key Factors from the passed Freq
 * in the passed Structure Pointer.
 *
 *  @param	PLL_Hardware hmc_hw		// HMC Hardware to target command.
 *  									PLL_C_HW
 *  									PLL_D_HW
 *  @param	float Target_Freq		Target Frequency to set Target PLL
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
#define TIMEOUT_LOOP 50		// Number of times to repeat a command before giving up.
#define WAIT_DELAY	10
//#define TEST_CD 1
HAL_StatusTypeDef hmc_SetupFreq(PLL_Hardware hmc_hw, float Target_Freq) {
	int x;
	pll_registers pll_data1;
#ifdef TEST_CD
	pll_registers pll_rxdata1;
#endif
	PLL_Port_Regs pll_rxdata2;
	PLL_Parameters Template_Parms;
	vco_registers vco_data1;

	// Verify parameters.
	if ((Target_Freq < HMC_MIN_HFREQ) || (Target_Freq > HMC_MAX_FREQ)) {
		return HAL_ERROR;
	}
	if ((hmc_hw < PLL_C_HW) || (hmc_hw > PLL_D_HW))
		return HAL_ERROR;
	// Now validate if Hardware is available
	if (PLL_State[hmc_hw] != AVAILABLE)
		return HAL_ERROR;

	// Set Desired Freq into Structure.
	Template_Parms.Desired_Freq = Target_Freq;

	// Now Calculate Params.
	if (hmc_calc_parameters(&Template_Parms) != HAL_OK)
		return HAL_ERROR;

	/*************************************
	 * Time to Set Parameters in Hardware.
	 ************************************/
	// BIT BANG SETTINGS...
	// 1. Write to REG 0 20.
	// 			Reg00 = 00100000  -  RESET command.
	pll_data1.Data = 0x20;
	if (hmc_spi_write_read(hmc_hw, 0x00, pll_data1, &pll_rxdata2) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command

	/*
	 *  2. Write to REG 1 2.
	 *		Reg01 = 00000010 - Default = 2.
	 * 			This value assigns PLL Chip Enable control to the SPI Reg 1 [1], 1 enabled, 0 disabled.
	 * 			To assign PLL CE control to CE pin, write Reg 1[0]=1.
	 */
	pll_data1.Data = 0x02;
	if (hmc_spi_write_read(hmc_hw, 0x01, pll_data1, &pll_rxdata2) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command

	/*
	 * 	3. Write to REG 2 1.
	 * 		Reg02 = 00000001 - REFDIV Register =  0x01 Ref Divider Register-Default value = 1h (Rdiv=1). Program as needed.
	 */
	pll_data1.Data = 0x01;
	if (hmc_spi_write_read(hmc_hw, 0x02, pll_data1, &pll_rxdata2) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command

	/*
	 * 	4. Frequency Register, Integer Part Integer VCO Divider Register-Progarm as needed to set frequency.
	 */
	// Clear Buffers
	for (x = 0; x < PLL_STRNG_LEN; x++) {
		pll_data1.DString[x] = 0x00;
#ifdef TEST_CD
		pll_rxdata1.DString[x] = 0x00;
#endif
	}

	pll_data1.freq_int.NTG_REG = (Template_Parms.N_Divider_int & 0x7ffff); // This is a 19 Bit Field.

#ifdef TEST_CD
		for (x=0;x<TIMEOUT_LOOP;x++)
	{
#endif
		if (hmc_spi_write_read(hmc_hw, FREQ_INT_REG, pll_data1, &pll_rxdata2)
			!= HAL_OK)
			return HAL_ERROR;
#ifdef TEST_CD
		pll_rxdata1.Data = pll_rxdata2.PLL_Port.DATA;
		if (pll_data1.freq_int.NTG_REG == pll_rxdata1.freq_int.NTG_REG)
			break;
	}
	if ( x==TIMEOUT_LOOP )
		return HAL_ERROR;
#endif

	// 5. Write to REG 5 1010   // Reg02 = 000010000 = fo (VCO output Div-by-32);
	// Clear Buffer
	vco_data1.Data = 0x0000;

	vco_data1.vco_OUT_DVDR.RF_DVDR_RATIO =
			(Template_Parms.Output_Divider & 0x7f);	// This is a 7 Bit Field.

	pll_data1.Data = 0x00;
	pll_data1.spi_vco.VCO_REGADDR = 0x02;		// Reg02
	pll_data1.spi_vco.VCO_ID = 0x00;			// ID always zero
	pll_data1.spi_vco.VCO_DATA = vco_data1.Data;			// Set Divisor.
	if (hmc_spi_write_read(hmc_hw, 0x05, pll_data1, &pll_rxdata2) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command

	/*
	 * Power Up VCOs.
	 */
	if (hmc_vco_powerUp(hmc_hw) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command

	// 6. Write to REG 5 F98    // Reg03 = 000011111 = Hi Perf, RF_P & RF_N enabled, 5dB RL,
	pll_data1.Data = 0x0F98;
	if (hmc_spi_write_read(hmc_hw, 0x05, pll_data1, &pll_rxdata2) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command

	// 7. Write to REG 5 4B38   // Reg07 = 010010110 = o/p -6dB.  For maximum o/p power program 4DB8h.
	pll_data1.Data = 0x4B38;
	if (hmc_spi_write_read(hmc_hw, 0x05, pll_data1, &pll_rxdata2) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command

	// 8. Write to REG 5 0.
	pll_data1.Data = 0x0;
	if (hmc_spi_write_read(hmc_hw, 0x05, pll_data1, &pll_rxdata2) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command

	/*
	 * 	9. Write to REG 6 F4A.
	 * 		Reg06 = F4A Delta-Sigma Modulator Configuration Register. Program this value for Frac Mode.
	 */
	pll_data1.Data = 0x0F4A;
	if (hmc_spi_write_read(hmc_hw, 0x06, pll_data1, &pll_rxdata2) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command

	/*
	 * 	10. Write to REG 7 14D.
	 * 		14Dh is the default value for LD programming (correct for 50MHz comparison).
	 * 		For different configurations, especially higher PFD rates, this may need to change.
	 */
	pll_data1.Data = 0x014D;
	if (hmc_spi_write_read(hmc_hw, 0x07, pll_data1, &pll_rxdata2) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command

	/*
	 * 	11. Write to REG 8 C1BEFF.
	 * 		Default value = C1BEFFh.  No need to program.
	 */
	pll_data1.Data = 0xC1BEFF;
	if (hmc_spi_write_read(hmc_hw, 0x08, pll_data1, &pll_rxdata2) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command

	/*
	 * 	12. Write to REG 9 3FFEFD.
	 * 		CP Register-Program as needed. 3FFEFDh = 2.54mA CP current with 635uA Up CP Offset current.
	 */
	pll_data1.Data = 0x3FFEFD;
	if (hmc_spi_write_read(hmc_hw, 0x09, pll_data1, &pll_rxdata2) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command

	/*
	 * 	13. Write to REG A 2046.
	 * 		VCO Tuning Configuration Register-Program this value.
	 */
	pll_data1.Data = 0x2046;
	if (hmc_spi_write_read(hmc_hw, 0x0A, pll_data1, &pll_rxdata2) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command

	/*
	 * 	14. Write to REG B 4F8061.
	 * 		PFD/CP Control Register.  Default value = F8061h.
	 * 		4F8061h sets LD/SDO output level to 3.3V from 1.8V default (bit[22]=1 sets 3.3V output level).
	 */
	pll_data1.Data = 0x4F8061;
	if (hmc_spi_write_read(hmc_hw, 0x0B, pll_data1, &pll_rxdata2) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command

	/*
	 * 	15. Write to REG C 0.
	 * 		Exact Frequency register.  Default value =0h.  No need to program if not using Exact Frequency Mode.
	 */
	pll_data1.Data = 0x00;
	if (hmc_spi_write_read(hmc_hw, 0x0C, pll_data1, &pll_rxdata2) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command

	/*
	 * 	16. Write to REG F 81.
	 * 		Default vaue =1. 81h configures LD/SDO pin to output LD status always,
	 * 			except during SPI reads when the pin is automatically mux'ed to output the serial data.
	 */
#if 0
	pll_data1.Data = 0x81;
	if (hmc_spi_write_read(hmc_hw, 0x0F, pll_data1, &pll_rxdata2) != HAL_OK)
		return HAL_ERROR;
	accurate_delay(WAIT_DELAY);		// Wait before next Command
#endif

	/*
	 * 	17. Write to REG 4 0.
	 * 		Fractional VCO Divider Register-Program as needed to set frequency. When this register is written, a VCO auto-cal is initiated.
	 */
	for (x = 0; x < PLL_STRNG_LEN; x++) {
		pll_data1.DString[x] = 0x00;
#ifdef TEST_CD
		pll_rxdata1.DString[x] = 0x00;
#endif
	}

	pll_data1.freq_frac.FRAC = (Template_Parms.N_Divider_frac & 0xffffff); // This is a 24 Bit Field.

#ifdef TEST_CD
	for (x=0;x<TIMEOUT_LOOP;x++)
	{
#endif
		if (hmc_spi_write_read(hmc_hw, FREQ_FRAC_REG, pll_data1, &pll_rxdata2)
			!= HAL_OK)
			return HAL_ERROR;
#ifdef TEST_CD
		pll_rxdata1.Data = pll_rxdata2.PLL_Port.DATA;
		if (pll_data1.freq_frac.FRAC == pll_rxdata1.freq_frac.FRAC)
			break;
	}
	if ( x==TIMEOUT_LOOP )
		return HAL_ERROR;
#endif
	return HAL_OK;
}

/*****************************************************************************
 *
 * routine: hmc_Enable_VCO
 * Date: 	December 4, 2020
 * Updated: December 4, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine enables the Output Section of the VCO by enabling
 * the Output Pins of the VCO.
 *
 *  @param	PLL_Hardware hmc_hw		// HMC Hardware to target command.
 *  									PLL_C_HW
 *  									PLL_D_HW
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef hmc_Enable_VCO( PLL_Hardware hmc_hw )
{
	vco_registers vco_data1;

	if ((hmc_hw < PLL_C_HW) || (hmc_hw > PLL_D_HW))
		return HAL_ERROR;
	// Must Force PLL to be Available.
	PLL_State[hmc_hw] = AVAILABLE;

	// Clear Buffer
	vco_data1.Data = 0x0000;

	vco_data1.vco_CONFIG.MSTR_ENAB_VCO_SBSYSTM = 2;		// Bit 0-1:High Performance		Selects output noise floor performance level at a cost of increased current consumption.
	vco_data1.vco_CONFIG.RF_N_OUT_ENAB = 1;				// Bit 2:ENABLE					Enables the output on RF_N pin. Required for differential operation, or single-ended
	vco_data1.vco_CONFIG.RF_P_OUT_ENAB = 1;				// Bit 3:ENABLE					Enables the output on RF_P pin. Required for differential operation, or single-ended
	vco_data1.vco_CONFIG.RESERVED1 = 0x01;				// Bit 4:						RESERVED
	vco_data1.vco_CONFIG.RETURN_LOSS = 0x00;			// Bit 5:0	 					0: 0: return loss = −5 dB typical (highest output power).
														//								See "RF PROGRAMMABLE OUTPUT RETURN LOSS"(Pg 35)
	vco_data1.vco_CONFIG.RESERVED2 = 0x00;				// Bit 6:						RESERVED
	vco_data1.vco_CONFIG.MUTE_MODE = 0x01;				// Bits 7-8:					during VCO calibration (see the VCO Calibration section for more details).
	if (hmc_vco_write(hmc_hw, VCO_CONFIG_REG, vco_data1) != HAL_OK)
		return HAL_ERROR;

	return HAL_OK;
}

/*****************************************************************************
 *
 * routine: hmc_Disable_VCO
 * Date: 	December 4, 2020
 * Updated: December 4, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine Disables the Output Section of the VCO by disabling
 * the Output Pins of the VCO.
 *
 *  @param	PLL_Hardware hmc_hw		// HMC Hardware to target command.
 *  									PLL_C_HW
 *  									PLL_D_HW
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Error during Init
 * 									HAL_BUSY     = 0x02:	Can't Task. Busy
 * 									HAL_TIMEOUT  = 0x03:	Timeout on tasking.
 *
 *****************************************************************************/
HAL_StatusTypeDef hmc_Disable_VCO( PLL_Hardware hmc_hw )
{
	vco_registers vco_data1;

	if ((hmc_hw < PLL_C_HW) || (hmc_hw > PLL_D_HW))
		return HAL_ERROR;
	// Must Force PLL to be Available.
	PLL_State[hmc_hw] = AVAILABLE;

	// Clear Buffer
	vco_data1.Data = 0x0000;

	vco_data1.vco_CONFIG.MSTR_ENAB_VCO_SBSYSTM = 1;		// Bit 0-1:01					Selects output noise floor: low current consumption mode.
	vco_data1.vco_CONFIG.RF_N_OUT_ENAB = 0;				// Bit 2:DISABLE				Enables the output on RF_N pin. Required for differential operation, or single-ended
	vco_data1.vco_CONFIG.RF_P_OUT_ENAB = 0;				// Bit 3:DISABLE				Enables the output on RF_P pin. Required for differential operation, or single-ended
	vco_data1.vco_CONFIG.RESERVED1 = 0x01;				// Bit 4:						RESERVED
	vco_data1.vco_CONFIG.RETURN_LOSS = 0x01;			// Bit 5:1	 					1: return loss = −10 dB typical.
														//								See "RF PROGRAMMABLE OUTPUT RETURN LOSS"(Pg 35)
	vco_data1.vco_CONFIG.RESERVED2 = 0x00;				// Bit 6:						RESERVED
	vco_data1.vco_CONFIG.MUTE_MODE = 0x01;				// Bits 7-8:					during VCO calibration (see the VCO Calibration section for more details).
	if (hmc_vco_write(hmc_hw, VCO_CONFIG_REG, vco_data1) != HAL_OK)
		return HAL_ERROR;

	return HAL_OK;
}

/*****************************************************************************
 *
 * routine: hmc_TestPll_Lock
 * Date: 	November 30, 2020
 * Updated: November 30, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine Tests the PLL Lock in the General Purpose 2 register
 * on the indicated PLL.
 *
 * INPUT:
 *  @param	PLL_Hardware hmc_hw		// HMC Hardware to target command.
 *  									PLL_C_HW
 *  									PLL_D_HW
 *
 * OUTPUT:
 * 	@retval bool	-	TRUE	= 1:	PLL Is in Locked Freq.
 * 						FALSE	= 0:	PLL Is not in Locked Freq.
 *
 *****************************************************************************/
bool hmc_TestPll_Lock(PLL_Hardware hmc_hw) {
	int x;
	pll_registers pll_data1, pll_rxdata1;
	PLL_Port_Regs pll_rxdata2;

	if ((hmc_hw < PLL_C_HW) || (hmc_hw > PLL_D_HW))
		return FALSE;
	// Now validate if Hardware is available
	if (PLL_State[hmc_hw] != AVAILABLE)
		return FALSE;

	// Clear Buffers
	for (x = 0; x < PLL_STRNG_LEN; x++) {
		pll_data1.DString[x] = 0x00;
		pll_rxdata1.DString[x] = 0x00;
	}

	if (hmc_spi_write_read(hmc_hw, GPO2_REG, pll_data1, &pll_rxdata2) != HAL_OK)
		return FALSE;
	pll_rxdata1.Data = pll_rxdata2.PLL_Port.DATA;

	if (pll_rxdata1.gpo2.LOCK_DETECT > 0)
		return TRUE;
	else
		return FALSE;
}

/***********************************************************************************************************************
* Function Name: R_SCI6_SPI_Receive2
* Description  : This function Sets up the SCI6 port for SPI Communication and sends the passed string. It also is used
* to collect ata from the receive side of the SPI Port.
* Arguments    : uint8_t str[]: 		Passed Buffer of Bytes to send to the SPI Port.
* 				 int wrtLen:			Number of Bytes to transmit.
* 				 uint8_t retStr[]:		Pointer to Buffer for receive Traffic.
* 				 int rdLen:				Number of Bytes to receive from SPI Bus
* 				 int EnableCnt:			Number of Clocks before raising Designated Enable Pin.
* 				 PLL_Hardware hmc_hw	HMC Hardware to target command.
 *  									PLL_C_HW
 *  									PLL_D_HW
* Return Value : MD_STATUS:			TX_BUSY(1):		SPI BUS Busy...Can't Task
* 									TX_COMPLETE(0):	Successful Send and Receive of SPI Data.
* 									TX_ERRORCD(3):	Error occurred when Tasking SPI Command.
***********************************************************************************************************************/
#define SPI2_DELAY_USEC	200		// Set Delay to 20 usec per transition on Clock
unsigned char R_SCI6_SPI_Receive2( uint8_t str[], int wrtLen, uint8_t retStr[], int rdLen, int EnableCnt, PLL_Hardware hmc_hw )
{
	//MD_STATUS err;
	int tmpByte, tmpWrt, tmpRd, tmpClkCnt;
	int OneShotSPI_Set;
	//int BlkRd;
	uint8_t TempWrtData, TempRdData, TmpValue;

#ifdef DEBUGGR
	debug1(D_SCI5_PRINT);
#endif
		// Test Transmit flag and only fill buffer if flag is clear
		if (gp_sci6_tx_state != TX_BUSY) {
			// Start Transmission
			gp_sci6_tx_state = TX_BUSY;
			//printf("***R_SCI6_Serial_Send str:%s Length:%d\n", str, strlen(str));
			if (wrtLen > 0) {
				// Set Count for
				tmpClkCnt=0;
				// Clear One Shot Flag;
				OneShotSPI_Set = 0;
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
			    		// Increment tmpClkCnt and Test against EnableCnt.
			    		tmpClkCnt++;
			    		if (( tmpClkCnt>EnableCnt ) &&
			    			(OneShotSPI_Set == 0x00))
			    		{
			    			// Set One Shot Flag.
			    			OneShotSPI_Set = 1;
			    			// Time to set Designated Enable Pin Low.
			    			if (hmc_hw == PLL_C_HW)
			    				PLMpls_gpio_Off(PLLC_Enable);		// Clear PLLC SPI Enable
			    			else
			    				PLMpls_gpio_Off(PLLD_Enable);		// Clear PLLD SPI Enable
			    		}
			    		// Now Rotate TempWrtData to the left by 1 bit.
			    		TempWrtData = TempWrtData << 1;
			    		// Wait SPI_DELAY_USEC usec
			    		short_delay(SPI2_DELAY_USEC);
			    		// Set Clock High
			    		PORT0.PODR.BIT.B2 = 1;		// SPI_SCK: HIGH
			    		// Wait SPI_DELAY_USEC usec
			    		short_delay(SPI2_DELAY_USEC);
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
			     * Time to Wait and then set Enable Pin...
			     */
	    		// Wait SPI_DELAY_USEC usec
	    		short_delay(SPI2_DELAY_USEC);

	    		// Time to set Designated Enable Pin High.
    			if (hmc_hw == PLL_C_HW)
    				PLMpls_gpio_On(PLLC_Enable);		// Clear PLLC SPI Enable
    			else
    				PLMpls_gpio_On(PLLD_Enable);		// Clear PLLD SPI Enable

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

/*****************************************************************************
 *
 * routine: hmc_PwrOff_Lsrs
 * Date: 	December 20, 2020
 * Updated: November 30, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine Performs a FULL shutdown of lasers and PLLs
 *
 * INPUT:
 *  @param	None
 *
 * OUTPUT:
 * 	@retval None
 *
 *****************************************************************************/
void hmc_PwrOff_Lsrs( void )
{
	// Powerup PLLs just in case they are jammed.
	hmc_powerup_plls();

	// Power Down Clock Circuit.
	PLMpls_gpio_Off(PLL_CLK_EN);	// Disable HF Clock by Setting Pin Low.

	/*
	 * Power Down HF Laser Driver HW.
	 */
	PLMpls_HFlaser_disable( HF_LSR_ALL_CNTL );
	accurate_delay(10);

	/*
	 * Power Down Driver Power Supply.
	 */
	//PLMpls_gpio_Off( HF_Laser_Enable );
	PLMpls_gpio_On( HF_Laser_Enable );
	accurate_delay(10);

	/*
	 * Disable VCO Output .
	 */
	hmc_Disable_VCO(PLL_C_HW);
	accurate_delay(10);
	hmc_Disable_VCO(PLL_D_HW);

	/*
	 * Power Down VCOs.
	 */
	hmc_vco_powerDn(PLL_C_HW);
	accurate_delay(10);
	hmc_vco_powerDn(PLL_D_HW);

	/*
	 * Power Down PLLs.
	 */
	hmc_pll_powerDn(PLL_C_HW);
	accurate_delay(10);
	hmc_pll_powerDn(PLL_D_HW);

	/*
	 * Power Down All Laser Circuits.
	 */
	lasers_off();
}


/*****************************************************************************
 *
 * routine: Template
 * Date: 	November 28, 2020
 * Updated: November 28, 2020
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
