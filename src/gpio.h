/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for
  *                      the gpio LED Controls including control of Enable Pins,
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

#ifndef GPIO_H_
#define GPIO_H_
/******************************************************************************
 *
 * Module Includes
 *
 *****************************************************************************/
#include "hmc832.h"

/******************************************************************************
 *
 * Module Defines
 *
 *****************************************************************************/

/******************************************************************************
 *
 * Module Enums
 *
 *****************************************************************************/
typedef enum
{
  GPIO_PIN_RESET = 0,
  GPIO_PIN_SET = 1,
  GPIO_ERROR = 2
}GPIO_PinState;

typedef enum
{
	P_ENP = 0,						// (Output/ Active High/ LF Laser Power Supply Enable)
	P_EN = 1,						// (Output/ Active High/ 5V Power Supply Enable)
	HF_Laser_Enable = 2,			// (Output/ Active High/ HF Laser Power Supply Enable)
	LCDPWR = 3,						// (Output/ Active High/ LCD Power Supply Enable)
	SDPWREN = 4,					// (Output/ Active High/ Enable Power to SD Circuit)
	BCKLGHT = 5,					// (Output/ Active High/ LCD Backlight Enable)
	EFR32_RESET = 6,				// (Output/ Active Low/ Reset Bluetooth Module/ DISABLED)
	LD3_LF_Enable = 7,				// (Output/ Active LOW/ Enable Low Frequency Laser Diode 3)
	LD4_LF_Enable = 8,				// (Output/ Active LOW/ Enable Low Frequency Laser Diode 4)
	LD12_LF_Enable = 9,				// (Output/ Active LOW/ Enable Low Frequency Laser Diode 1 and Laser Diode 2)
	PLL_CLK_EN = 10,				// (Output/ Active High/ HF Clock Enable)
	PLLC_Enable = 11,				// (Output/ Active Low/ PLLC Enable)(Init handled by R_SCI6_Create(void))
	PLLD_Enable = 12,				// (Output/ Active Low/ PLLD Enable)(Init handled by R_SCI6_Create(void))
	LD0_HF_ENABLE = 13,				// (Output/ Active Low/ Enable HF Laser 1 Driver Circuit)
	LD1_HF_ENABLE = 14,				// (Output/ Active Low/ Enable HF Laser 2 Driver Circuit)
	LD2_HF_ENABLE = 15,				// (Output/ Active Low/ Enable HF Laser 3 Driver Circuit)
	LD3_HF_ENABLE = 16,				// (Output/ Active Low/ Enable HF Laser 4 Driver Circuit)
	PinDiode0 = 17,					// (Analog Input/Optical Power on Laser Diode 1)
	PinDiode1 = 18,					// (Analog Input/Optical Power on Laser Diode 1)
	PinDiode2 = 19,					// (Analog Input/Optical Power on Laser Diode 1)
	PinDiode3 = 20,					// (Analog Input/Optical Power on Laser Diode 1)
	HF_Laser_Flt = 21,				// (Input/ Active Low/ HF Laser Power Switch Fault Detect)
	BATVLTG = 22,					// (Analog Input/ Battery Voltage Level)
	START_PIN = 23					// (Digital Input/ Assert Low)
}PLM_PLUS_io_TypeDef;

typedef enum
{
	LASER12_CNTL,					// LF Laser 1 and Laser 2 Control
	LASER3_CNTL,					// LF Laser 3 Control
	LASER4_CNTL,					// LF Laser 4 Control
	LASERALL_CNTL					// All LF Laser Control(Lasers 1-4)
}PLM_PLUS_Laser_TypeDef;

typedef enum
{
	HF_LSR1_CNTL,					// HF Laser 1 Control
	HF_LSR2_CNTL,					// HF Laser 2 Control
	HF_LSR3_CNTL,					// HF Laser 3 Control
	HF_LSR4_CNTL,					// HF Laser 4 Control
	HF_LSR12_CNTL,					// HF Laser 1 and Laser 2 Control
	HF_LSR34_CNTL,					// HF Laser 3 and Laser 4 Control
	HF_LSR_ALL_CNTL					// All HF Laser Control(Lasers 1-4)
}PLM_PLUS_HFLaser_TypeDef;

/******************************************************************************
 *
 * Module Structures
 *
 *****************************************************************************/

/******************************************************************************
 *
 * Module Prototypes
 *
 *****************************************************************************/
void GPIO_Init(void);
void GPIO_Sleep(void);
void PLMpls_gpio_On(PLM_PLUS_io_TypeDef Port);
void PLMpls_gpio_Off(PLM_PLUS_io_TypeDef Port);
void PLMpls_gpio_Toggle(PLM_PLUS_io_TypeDef Port);
int PLMpls_gpio_GetPort(PLM_PLUS_io_TypeDef Port);
int PLMpls_gpio_GetPortPin(PLM_PLUS_io_TypeDef Port);
GPIO_PinState PLMpls_gpio_ReadPin(PLM_PLUS_io_TypeDef Port);
HAL_StatusTypeDef PLMpls_LFlaser_enable( PLM_PLUS_Laser_TypeDef laserCntl );
HAL_StatusTypeDef PLMpls_LFlaser_disable( PLM_PLUS_Laser_TypeDef laserCntl );
HAL_StatusTypeDef PLMpls_HFlaser_enable( PLM_PLUS_HFLaser_TypeDef laserCntl );
HAL_StatusTypeDef PLMpls_HFlaser_disable( PLM_PLUS_HFLaser_TypeDef laserCntl );

#endif /* GPIO_H_ */
