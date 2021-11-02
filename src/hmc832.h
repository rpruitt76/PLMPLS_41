/*****************************************************************************
 * hmc832.h
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
#ifndef HMC832_H_
#define HMC832_H_
/******************************************************************************
 *
 * Module Includes
 *
 *****************************************************************************/
#include <stdbool.h>

/******************************************************************************
 *
 * Module Defines
 *
 *****************************************************************************/
/*
 *  Misc Defines
 */
#define PLL_STRNG_LEN		0x04	 	// Number of Bytes for a PLL String
#define	CHIP_ID_VAL			0x0A7975	// Chip ID read from CHIP_ID Register.
#define	SELF_TEST_VAL		0x1259		// Result read from Self Test Register
#define HMC_MAX_FREQ		3000000000.0	// Maximum Frequency that can be supported...3.0GHz
#define HMC_MIN_FREQ		0.1				// Minimum Frequency that can be supported...0.1Hz
#define HMC_MIN_HFREQ		25000000		// Minimum High Frequency that can be supported...25.0MHz
#define HMC_THRESH_FREQ		50000000		// Frequency that allows us to use higher VCO Frequency...50.0MHz
#define HMC_LOW_VCO_FREQ	1500000000.0	// Low VCO Frequency...1.5GHz
#define HMC_HIGH_VCO_FREQ	2200000000.0	// High VCO Frequency...2.2GHz
#define HMC_BASE_OSC_FREQ	16000000.0		// U6 Osc = 16.0MHz
#define HMC_FRAC_FACTOR		16777216		// Magic Factor used to Calculate the Fraction Factor...2^24...

/*
 *  PLL REGISTER Defines
 */
#define CHIP_ID_REG			0x00	 	// Register 0x00, ID Register
#define RESET_REG			0x01		// Register 0x01, RST Register (Default 0x000002)
#define	REFDIV_REG			0x02		// Register 0x02, REFDIV Register (Default 0x000001)
#define	FREQ_INT_REG		0x03		// Register 0x03, Frequency Register, Integer Part (Default 0x000019)
#define	FREQ_FRAC_REG		0x04		// Register 0x04, Frequency Register, Fractional Part (Default 0x000000)
#define	SPI_VCO_REG			0x05		// Register 0x05, VCO SPI Register (Default 0x000000)
#define	DELTA_SIGCONF_REG	0x06		// Register 0x06, Delta-Sigma Configuration Register (Default 0x200B4A)
#define	LOCK_DET_REG		0x07		// Register 0x07, Lock Detect Register (Default 0x00014D)
#define	ANALOG_EN_REG		0x08		// Register 0x08, Analog EN Register, (Default 0xC1BEFF)
#define	CHRG_PUMP_REG		0x09		// Register 0x09, Charge Pump Register (Default 0x403264)
#define	AUTO_CALIB_REG		0x0A		// Register 0x0A, VCO Autocalibration Configuration Register (Default 0x002205)
#define	PHASE_DET_REG		0x0B		// Register 0x0B, PD Register (Default 0x0F8061)
#define	EXACT_PH_MD_REG		0x0C		// Register 0x0C, Exact Frequency Mode Register (Default 0x000000)
#define GPO_SPI_RDIV_REG	0x0F		// Register 0x0F, GPO_SPI_RDIV Register (Default 0x000001)
										//    GENERAL-PURPOSE, SERIAL PORT INTERFACE, AND REFERENCE DIVIDER (GPO_SPI_RDIV) REGISTER
#define TUNE_VCO_REG		0x10		// Register 0x10, VCO Tune Register (Default 0x000020)
#define	SAR_REG				0x11		// Register 0x11, SAR Register (Default 0x07FFFF)
#define	GPO2_REG			0x12		// Register 0x12, GPO2 Register (Default 0x000000)
#define	BLTIN_STST_REG		0x13		// Register 0x13, BIST Register (Default 0x001259)

/*
 * VCO SUBSYSTEM REGISTER Defines
 */
#define	VCO_TUNING_REG		0x00		// VCO_REG 0x00 Tuning
#define	VCO_ENAB_REG		0x01		// VCO_REG 0x01 Enable
#define	VCO_OUT_DVDR_REG	0x02		// VCO_REG 0x02 VCO Output Divider
#define	VCO_CONFIG_REG		0x03		// VCO_REG 0x03 Configuration
#define	VCO_CAL_BIAS_REG	0x04		// VCO_REG 0x04 CAL/Bias
#define	VCO_CF_CAL_REG		0x05		// VCO_REG 0x05 CF_CAL
#define	VCO_CAL_MSB_REG		0x06		// VCO_REG 0x06 MSB Calibration
#define	VCO_PWR_CNTRL_REG	0x07		// VCO_REG 0x07 Output Power Control


/******************************************************************************
 *
 * Module Enums
 *
 *****************************************************************************/
/**
  * @brief  HAL Status structures definition
  */
typedef enum
{
  HAL_OK       = 0x00,
  HAL_ERROR    = 0x01,
  HAL_BUSY     = 0x02,
  HAL_TIMEOUT  = 0x03
} HAL_StatusTypeDef;

typedef enum
{
  NOT_INIT = 0,
  AVAILABLE = 1,
  INIT_ERR = 2,
  ERR_DET = 3
} HMC_Status;

typedef enum
{
  PLL_C_HW,
  PLL_D_HW,
  TOTAL_PLLS
} PLL_Hardware;

/******************************************************************************
 *
 * Module Structures
 *
 *****************************************************************************/
/*
 *  Misc Structures
 */

// PLL Parameter Structure
typedef struct PLL_Parameter
{
	float			Desired_Freq;				// Target Frequency to Setup Parameters
	uint32_t		R_Divider;					// Reference Divider to use with Baseline Frequency
	uint32_t		Output_Divider;				// VCO Output Divider: VCO_REG 0x02 VCO Output Divider
	uint32_t		N_Divider_int;				// N Divider Int:  Register 0x03, Frequency Register, Integer Part (Default 0x000019)
	uint32_t		N_Divider_frac;				// N Divider Frac: Register 0x04, Frequency Register, Fractional Part (Default 0x000000)
}PLL_Parameters;
typedef struct PLL_Parameters *PLL_ParametersPtr;

// PLL_Port_Reg		32 Bit Register...4 Bytes Sent MSB to LSB
typedef struct PLL_PortReg
{
	unsigned long	CHIP_ADDR:3;				// Bits 0-2:	3-bit chip address, A2:A0, MSB first
	unsigned long	ADDRESS:5;					// Bits 3-7:	5-bit register address
	unsigned long	DATA:24;					// Bits 8-31:	24-bit data, D23:D0, MSB first
}PLL_Port_Reg;
typedef struct PLL_Port_Reg *PLL_Port_RegPtr;

// VCO_Port_Reg		16 Bit Register.....MSB to LSB
typedef struct VCO_PortReg
{
	unsigned int	VCO_ID:3;						// Bits 0-2:	Internal VCO subsystem ID.
	unsigned int	VCO_REGADDR:4;					// Bits 3-6:	VCO subsystem register address. These bits are for interfacing with the VCO. See the VCO Serial Port Interface (VSPI) section.
	unsigned int	VCO_DATA:9;						// Bits 7-15:	VCO subsystem data. These bits are for the data to be written to the VCO subsystem.
}VCO_Port_Reg;
typedef struct VCO_Port_Reg *VCO_Port_RegPtr;

typedef union PLL_PortRegs
{
	PLL_Port_Reg	PLL_Port;						// PLL_Port_Reg		32 Bit Register...4 Bytes Sent MSB to LSB
	uint32_t		DATA;							// 32 Bit Data.
	uint8_t			DString[PLL_STRNG_LEN];			// Port Data in 8 Bit Values.
}PLL_Port_Regs;
typedef union PLL_Port_Regs *PLL_Port_RegsPtr;

typedef union VCO_PortRegs
{
	VCO_Port_Reg	VCO_Port;						// VCO_Port_Reg		16 Bit Register.....MSB to LSB
	uint16_t		DATA;							// 16 Bit Data.
}VCO_Port_Regs;
typedef union VCO_Port_Regs *VCO_Port_RegsPtr;

/*
 *  PLL Structures
 */
// chip_id_reg			0x00	 	// Register 0x00, ID Register
typedef struct chip_idreg
{
	unsigned long	CHIP_ID:24;					// Bits 0-23:	HMC832LP6GE chip ID( 0xA7975)
	unsigned long	RESERVED1:8;				// Bits 24-31:	RESERVED
}chip_id_reg;
typedef struct chip_id_reg *chip_id_regPtr;
typedef struct chip_idRDreg
{
	unsigned long	Read_Adr:5;					// Bits 0-4:	Read address for next cycle, open mode only. This is a write only register.
	unsigned long	Soft_Rst:1;					// Bits 5:		Soft reset for both SPI modes (set to 0 for proper operation).
	unsigned long	RESERVED1:18;				// Bits 6-23:	RESERVED
	unsigned long	RESERVED2:8;				// Bits 24-31:	RESERVED
}chip_idRD_reg;
typedef struct chip_idRD_reg *chip_idRD_regPtr;

// reset_reg			0x01		// Register 0x01, RST Register (Default 0x000002)
typedef struct resetreg
{
	unsigned long	RST_CHIPEN_PIN_SELECT:1;	// Bits 0:		0 = take PLL enable via SPI (RST_CHIPEN_FROM_SPI) Register 0x01[1].
	unsigned long	RST_CHIPEN_FROM_SPI:1;		// Bits 1:		0 = Soft reset for both SPI modes (set to 0 for proper operation).
	unsigned long	RST_INT_BIAS_REF_SRC:1;		// Bits 2:		0 = Soft reset Internal bias reference sources (set to 0 for proper operation).
	unsigned long	RST_PD_BLOCK:1;				// Bits 3:		0 = Soft reset PD block (set to 0 for proper operation).
	unsigned long	RST_CP_BLOCK:1;				// Bits 4:		0 = Soft reset CP block (set to 0 for proper operation).
	unsigned long	RST_REF_PATH_BFFR:1;		// Bits 5:		0 = Soft reset Reference path buffer (set to 0 for proper operation).
	unsigned long	RST_VCO_PATH_BFFR:1;		// Bits 6:		0 = Soft reset VCO path buffer (set to 0 for proper operation).
	unsigned long	RST_DGTL_IO_TST_PDS:1;		// Bits 7:		0 = Soft reset Digital I/O test pads (set to 0 for proper operation).
	unsigned long	RESERVED1:16;				// Bits 8-23:	RESERVED
	unsigned long	RESERVED2:8;				// Bits 24-31:	RESERVED
}reset_reg;
typedef struct reset_reg *reset_regPtr;

// refdiv_reg			0x02		// Register 0x02, REFDIV Register (Default 0x000001)
typedef struct refdivreg
{
	unsigned long	RDIV:14;					// Bits 0-13:	Reference divider.
	unsigned long	RESERVED1:10;				// Bits 14-23:	RESERVED
	unsigned long	RESERVED2:8;				// Bits 24-31:	RESERVED
}refdiv_reg;
typedef struct refdiv_reg *refdiv_regPtr;

// freq_int_reg		0x03		// Register 0x03, Frequency Register, Integer Part (Default 0x000019)
typedef struct freq_intreg
{
	unsigned long	NTG_REG:19;					// Bits 0-18:	Integer divider register. These bits are the VCO divider integer part, used in all modes, see Equation 12.
	unsigned long	RESERVED1:5;				// Bits 19-23:	RESERVED
	unsigned long	RESERVED2:8;				// Bits 24-31:	RESERVED
}freq_int_reg;
typedef struct freq_int_reg *freq_int_regPtr;

// freq_frac_reg		0x04		// Register 0x04, Frequency Register, Fractional Part (Default 0x000000)
typedef struct freq_fracreg
{
	unsigned long	FRAC:24;					// Bits 0-23:	VCO divider fractional part (24-bit unsigned), see the Fractional Frequency Tuning section.
	unsigned long	RESERVED1:8;				// Bits 24-31:	RESERVED
}freq_frac_reg;
typedef struct freq_frac_reg *freq_frac_regPtr;

// SPI_VCO_REG			0x05		// Register 0x05, VCO SPI Register (Default 0x000000)
typedef struct spi_vcoreg
{
	unsigned long	VCO_ID:3;						// Bits 0-2:	Internal VCO subsystem ID.
	unsigned long	VCO_REGADDR:4;					// Bits 3-6:	VCO subsystem register address. These bits are for interfacing with the VCO. See the VCO Serial Port Interface (VSPI) section.
	unsigned long	VCO_DATA:9;						// Bits 7-15:	VCO subsystem data. These bits are for the data to be written to the VCO subsystem.
	unsigned long	RESERVED1:8;					// Bits 16-23:	RESERVED
	unsigned long	RESERVED2:8;					// Bits 24-31:	RESERVED
}spi_vco_reg;
typedef struct spi_vco_reg *spi_vco_regPtr;

// delta_sigconf_reg	0x06		// Register 0x06, Delta-Sigma Configuration Register (Default 0x200B4A)
typedef struct delta_sigconfreg
{
	unsigned long	SEED:2;							// Bits 0-1:	Selects the seed in fractional mode.
	unsigned long	RESERVED1:5;					// BitS 2-6:	RESERVED
	unsigned long	FRAC_BYPASS:1;					// Bit 7:		Bypass fractional mode.
	unsigned long	INIT_VALUE:3;					// Bits 8-10:	Initialization: Program to 0x07.
	unsigned long	SD_ENABLE:1;					// Bits 11:		This bit controls whether autocalibration starts on an integer or a fractional write.
	unsigned long	RESERVED2:9;					// Bits 12-20:	RESERVED
	unsigned long	AUTO_CLK_CONFIG:1;				// Bits 21:		Program to 0.
	unsigned long	RESERVED3:2;					// Bits 22-23:	RESERVED
	unsigned long	RESERVED4:8;					// Bits 24-31:	RESERVED
}delta_sigconf_reg;
typedef struct delta_sigconf_reg *delta_sigconf_regPtr;

// lock_det_reg		0x07		// Register 0x07, Lock Detect Register (Default 0x00014D)
typedef struct lock_detreg
{
	unsigned long	LKD_WINCNT_MAX:3;				// Bits 0-2:	Lock detect window sets the number of consecutive counts of divided VCO that must land inside the lock detect window to declare lock
	unsigned long	ENAB_INT_LK_DTCT:1;				// Bit 3:		Enable internal lock detect. See the Serial Port section
	unsigned long	RESERVED1:2;					// BitS 4-5:	RESERVED
	unsigned long	LK_DTCT_WNDW_TYP:1;				// Bit 6:		Lock detect window type. Lock detection window timer selection
	unsigned long	LD_DGTL_WNDW:3;					// Bits 7-9:	LD digital window duration. Lock detection, digital window duration
	unsigned long	LD_DGTL_TMR:2;					// Bits 10-11:	LD digital timer frequency control. Lock detect digital timer frequency control.
	unsigned long	RESERVED2:1;					// Bits 12:		RESERVED
	unsigned long	AUTO_RELOCK:1;					// Bit 13:		Automatic relock: one try
	unsigned long	RESERVED3:10;					// Bits 14-23:	RESERVED
	unsigned long	RESERVED4:8;					// Bits 24-31:	RESERVED
}lock_det_reg;
typedef struct lock_det_reg *lock_det_regPtr;

// analog_en_reg		0x08		// Register 0x08, Analog EN Register, (Default 0xC1BEFF)
typedef struct analog_enreg
{
	unsigned long	RESERVED1:5;					// BitS 0-4:	RESERVED
	unsigned long	GPO_PAD_EN:1;					// Bit 5:		enables GPO port or allows a shared SPI
	unsigned long	RESERVED2:4;					// Bits 6-9:	RESERVED
	unsigned long	VCO_BUF_PRESC_ENAB:1;			// Bit 10:		VCO buffer and prescaler bias enable. VCO buffer and prescaler bias enable
	unsigned long	RESERVED3:10;					// Bits 11-20:	RESERVED
	unsigned long	HIGH_FREQ_REF:1;				// Bit 21:		Program to 1 for XTAL > 200 MHz
	unsigned long	RESERVED4:2;					// Bits 22-23:	RESERVED
	unsigned long	RESERVED5:8;					// Bits 24-31:	RESERVED
}analog_en_reg;
typedef struct analog_en_reg *analog_en_regPtr;

// chrg_pump_reg		0x09		// Register 0x09, Charge Pump Register (Default 0x403264)
typedef struct chrg_pumpreg
{
	unsigned long	CP_DN_GAIN:7;					// Bits 0-6:	Charge pump DN gain control, 20 μA per step. Affects fractional phase
													//					noise and lock detect settings.
	unsigned long	CP_UP_GAIN:7;					// Bits 7-13:	Charge pump up gain control, 20 μA per step. Affects fractional phase
	unsigned long	OFFSET_MAG:7;					// Bits 14-20:	Offset magnitude. Charge pump offset control, 5 μA per step. Affects fractional phase
													//					noise and lock detect settings.
	unsigned long	OFFSET_UP_ENAB:1;				// Bit 21:		Offset up enable. Recommended setting = 1 in fractional mode, 0 otherwise.
	unsigned long	OFFSET_DN_ENAB:1;				// Bit 22:		Offset DN enable. Recommended setting = 0.
	unsigned long	RESERVED1:1;					// Bit 23:		RESERVED
	unsigned long	RESERVED2:8;					// Bits 24-31:	RESERVED
}chrg_pump_reg;
typedef struct chrg_pump_reg *chrg_pump_regPtr;

// auto_calib_reg		0x0A		// Register 0x0A, VCO Autocalibration Configuration Register (Default 0x002205)
typedef struct auto_calibreg
{
	unsigned long	VTUNE_RESLN:3;					// Bits 0-2:	R divider cycles
	unsigned long	RESERVED1:7;					// BitS 3-9:	RESERVED
	unsigned long	FORCE_CURVE:1;					// Bit 10:		Program 0
	unsigned long	AUTO_CAL_DISABLE:1;				// Bit 11:		Program 0 for normal operation using VCO autocalibration
	unsigned long	NO_VSPI_TRIG:1;					// Bit 12:		this bit disables the serial transfers to the VCO subsystem (via Register 0x05)
	unsigned long	FSM_VSPI_CLK_SLCT:2;			// Bit 13-14:	These bits set the autocalibration FSM and VSPI clock (50 MHz maximum)
	unsigned long	RESERVED2:9;					// Bits 15-23:	RESERVED
	unsigned long	RESERVED3:8;					// Bits 24-31:	RESERVED
}auto_calib_reg;
typedef struct auto_calib_reg *auto_calib_regPtr;

// phase_det_reg		0x0B		// Register 0x0B, PD Register (Default 0x0F8061)
typedef struct phase_detreg
{
	unsigned long	PD_DEL_SEL:3;					// Bits 0-2:	Sets PD reset path delay (recommended setting is 001).
	unsigned long	RESERVED1:2;					// BitS 3-4:	RESERVED
	unsigned long	PD_UP_EN:1;						// Bit 5:		Enables the PD up output.
	unsigned long	PD_DN_EN:1;						// Bit 6:		Enables the PD down output.
	unsigned long	CSP_MODE:2;						// Bits 7-8:	Cycle slip prevention mode.
	unsigned long	FORCE_CP_UP:1;					// Bit 9:		Forces CP up output to turn on; use for test only.
	unsigned long	FORCE_CP_DN:1;					// Bit 10:		Forces CP down output to turn on; use for test only.
	unsigned long	RESERVED2:13;					// Bits 11-23:	RESERVED
	unsigned long	RESERVED3:8;					// Bits 24-31:	RESERVED
}phase_det_reg;
typedef struct phase_det_reg *phase_det_regPtr;

// exact_ph_md_reg		0x0C		// Register 0x0C, Exact Frequency Mode Register (Default 0x000000)
typedef struct exact_ph_mdreg
{
	unsigned long	NUM_CHNNLS_FPD:14;				// Bits 0-13:	Number of Channels per fPD. The comparison frequency divided by the correction
													//					rate must be an integer.
	unsigned long	RESERVED1:10;					// Bits 14-23:	RESERVED
	unsigned long	RESERVED2:8;					// Bits 24-31:	RESERVED
}exact_ph_md_reg;
typedef struct exact_ph_md_reg *exact_ph_md_regPtr;

// gpo_spi_rdiv_reg	0x0F		// Register 0x0F, GPO_SPI_RDIV Register (Default 0x000001)
typedef struct gpo_spi_rdivreg
{
	unsigned long	GPO_SELECT:5;					// Bits 0-4:	The signal selected here is an output to the SDO pin when the SDO pin is enable via Register 0x08[5]
	unsigned long	GPO_TST_DATA:1;					// Bit 5:		GPO Test Data
	unsigned long	PRVNT_AUTOMX_LDO:1;				// Bit 6:		automuxes between SDO and GPO data
	unsigned long	LDO_DRV_ALWY_ON:1;				// Bit 7:		LD_SDO pin driver always on
	unsigned long	DISABLE_PFET:1;					// Bit 8:
	unsigned long	DISABLE_NFET:1;					// Bit 9:
	unsigned long	RESERVED1:14;					// Bits 10-23:	RESERVED
	unsigned long	RESERVED2:8;					// Bits 24-31:	RESERVED
}gpo_spi_rdiv_reg;
typedef struct gpo_spi_rdiv_reg *gpo_spi_rdiv_regPtr;

// tune_vco_reg		0x10		// Register 0x10, VCO Tune Register (Default 0x000020)
typedef struct tune_vcoreg
{
	unsigned long	VCO_SWTCH_SETTING:8;			// Bits 0-7:	Indicates the VCO switch setting selected by the autocalibration state machine to yield the
													//					nearest free running VCO frequency
	unsigned long	AUTO_CALIB_BUSY:1;				// Bit 8:		Busy when the autocalibration state machine is searching for the nearest switch setting to
	unsigned long	RESERVED1:15;					// Bits 9-23:	RESERVED
	unsigned long	RESERVED2:8;					// Bits 24-31:	RESERVED
}tune_vco_reg;
typedef struct tune_vco_reg *tune_vco_regPtr;

// sar_reg				0x11		// Register 0x11, SAR Register (Default 0x07FFFF)
typedef struct sarreg
{
	unsigned long	SAR_ERR_MAG_CNT:19;				// Bits 0-18:	SAR error magnitude counts
	unsigned long	SAR_ERROR_SIGN:1;				// Bit 19:		SAR error sign.
	unsigned long	RESERVED1:5;					// Bits 20-23:	RESERVED
	unsigned long	RESERVED2:8;					// Bits 24-31:	RESERVED
}sar_reg;
typedef struct sar_reg *sar_regPtr;

// gpo2_reg			0x12		// Register 0x12, GPO2 Register (Default 0x000000)
typedef struct gpo2reg
{
	unsigned long	GPO:1;							// Bit 0:		GPO state
	unsigned long	LOCK_DETECT:1;					// Bit 1:		Lock detect status
	unsigned long	RESERVED1:22;					// Bits 2-23:	RESERVED
	unsigned long	RESERVED2:8;					// Bits 24-31:	RESERVED
}gpo2_reg;
typedef struct gpo2_reg *gpo2_regPtr;

// bltin_stst_reg		0x13		// Register 0x13, BIST Register (Default 0x001259)
typedef struct bltin_ststreg
{
	unsigned long	SLF_TEST_RESULT:17;				// Bits 0-16:	Self Test Result(0x001259)
	unsigned long	RESERVED1:7;					// Bits 17-23:	RESERVED
	unsigned long	RESERVED2:8;					// Bits 24-31:	RESERVED
}bltin_stst_reg;
typedef struct bltin_stst_reg *bltin_stst_regPtr;

#if 0
typedef union pllregisters
{
	uint8_t				DString[PLL_STRNG_LEN];
	uint32_t			Data;
	chip_id_reg			chip_id;					// Register 0x00, ID Register...WRITE
}pll_registers;
typedef union pll_registers *pll_registersPtr;
#endif

typedef union pllregisters
{
	uint8_t				DString[PLL_STRNG_LEN];
	uint32_t			Data;
	chip_id_reg			chip_id;					// Register 0x00, ID Register...WRITE
	chip_idRD_reg		chip_idRD;					// Register 0x00, ID Register...READ
	reset_reg			reset;						// Register 0x01, RST Register (Default 0x000002)
	refdiv_reg			refdiv;						// Register 0x02, REFDIV Register (Default 0x000001)
	freq_int_reg		freq_int;					// Register 0x03, Frequency Register, Integer Part (Default 0x000019)
	freq_frac_reg		freq_frac;					// Register 0x04, Frequency Register, Fractional Part (Default 0x000000)
	spi_vco_reg			spi_vco;					// Register 0x05, VCO SPI Register (Default 0x000000)
	delta_sigconf_reg	delta_sigconf;				// Register 0x06, Delta-Sigma Configuration Register (Default 0x200B4A)
	lock_det_reg		lock_det;					// Register 0x07, Lock Detect Register (Default 0x00014D)
	analog_en_reg		analog_en;					// Register 0x08, Analog EN Register, (Default 0xC1BEFF)
	chrg_pump_reg		chrg_pump;					// Register 0x09, Charge Pump Register (Default 0x403264)
	auto_calib_reg		auto_calib;					// Register 0x0A, VCO Autocalibration Configuration Register (Default 0x002205)
	phase_det_reg		phase_det;					// Register 0x0B, PD Register (Default 0x0F8061)
	exact_ph_md_reg		exact_ph_md;				// Register 0x0C, Exact Frequency Mode Register (Default 0x000000)
	gpo_spi_rdiv_reg	gpo_spi_rdiv;				// Register 0x0F, GPO_SPI_RDIV Register (Default 0x000001)
	tune_vco_reg		tune_vco;					// Register 0x10, VCO Tune Register (Default 0x000020)
	sar_reg				sar;						// Register 0x11, SAR Register (Default 0x07FFFF)
	gpo2_reg			gpo2;						// Register 0x12, GPO2 Register (Default 0x000000)
	bltin_stst_reg		bltin_stst;					// Register 0x13, BIST Register (Default 0x001259)
}pll_registers;
typedef union pll_registers *pll_registersPtr;

/*
 *  VCO Structures
 */
// vco_TUNING_reg		0x00		// VCO_REG 0x00 Tuning
typedef struct vco_tuningreg
{
	unsigned int	CAL:1;							// Bit 0:
	unsigned int	CAPS:8;							// Bits 1-8:	VCO subband selection(Default - 16d)
	unsigned int	RESERVED1:7;					// Bits 9-15:	RESERVED
}vco_tuning_reg;
typedef struct vco_tuning_reg *vco_tuning_regPtr;

// vco_ENAB_reg		0x01		// VCO_REG 0x01 Enable
typedef struct vco_ENABreg
{
	unsigned int	MSTR_ENAB_VCO_SBSYSTM:1;		// Bit 0:		0: all VCO subsystem blocks are turned off.
	unsigned int	VCO_ENABLE:1;					// Bit 1:		Enables VCOs.
	unsigned int	PLL_BFFR_ENABLE:1;				// Bit 2:		Enables PLL buffer to N divider.
	unsigned int	IN_OUT_MSTR_ENABLE:1;			// Bit 3:		Enables output stage and the output divider. It does not enable/disable the VCO.
	unsigned int	RESERVED1:1;					// Bit 4:		RESERVED
	unsigned int	OUT_STGE_ENABLE:1;				// Bit 5:		Output stage enable.(Default - 1d)
	unsigned int	RESERVED2:2;					// Bits 6-7:	RESERVED
	unsigned int	RESERVED3:1;					// Bit 8:		RESERVED
	unsigned int	RESERVED4:7;					// Bits 9-15:	RESERVED
}vco_ENAB_reg;
typedef struct vco_ENAB_reg *vco_ENAB_regPtr;

// vco_OUT_DVDR_reg	0x02		// VCO_REG 0x02 VCO Output Divider
typedef struct vco_OUT_DVDRreg
{
	unsigned int	RF_DVDR_RATIO:6;				// Bits 0-5:	VCO output divider(Default - 1d)
	unsigned int	RESERVED1:3;					// Bits 6-8:	RESERVED
	unsigned int	RESERVED2:7;					// Bits 6-15:	RESERVED
}vco_OUT_DVDR_reg;
typedef struct vco_OUT_DVDR_reg *vco_OUT_DVDR_regPtr;

// vco_CONFIG_reg		0x03		// VCO_REG 0x03 Configuration
typedef struct vco_CONFIGreg
{
	unsigned int	MSTR_ENAB_VCO_SBSYSTM:2;		// Bit 0-1:		Selects output noise floor performance level at a cost of increased current consumption.
	unsigned int	RF_N_OUT_ENAB:1;				// Bit 2:		Enables the output on RF_N pin. Required for differential operation, or single-ended
													//					output on the RF_N pin.
	unsigned int	RF_P_OUT_ENAB:1;				// Bit 3:		Enables the output on RF_P pin. Required for differential operation, or single-ended
	unsigned int	RESERVED1:1;					// Bit 4:		RESERVED
	unsigned int	RETURN_LOSS:1;					// Bit 5:		0: return loss = −5 dB typical (highest output power).
	unsigned int	RESERVED2:1;					// Bit 6:		RESERVED
	unsigned int	MUTE_MODE:2;					// Bits 7-8:	Defines when the mute function is enabled
	unsigned int	RESERVED3:7;					// Bits 9-15:	RESERVED
}vco_CONFIG_reg;
typedef struct vco_CONFIG_reg *vco_CONFIG_regPtr;

// vco_CAL_BIAS_reg	0x04		// VCO_REG 0x04 CAL/Bias
typedef struct vco_CAL_BIASreg
{
	unsigned int	INITIALIZATION:9;				// Bits 0-8:	VCO CALIBRATION/BIAS INITIALIZATION(Default - 201d)
	unsigned int	RESERVED1:7;					// Bits 9-15:	RESERVED
}vco_CAL_BIAS_reg;
typedef struct vco_CAL_BIAS_reg *vco_CAL_BIAS_regPtr;

// vco_CF_CAL_reg		0x05		// VCO_REG 0x05 CF_CAL
typedef struct vco_CF_CALreg
{
	unsigned int	INITIALIZATION:9;				// Bits 0-8:	VCO CF CALIBRATION INITIALIZATION(Default - 170d)
	unsigned int	RESERVED1:7;					// Bits 9-15:	RESERVED
}vco_CF_CAL_reg;
typedef struct vco_CF_CAL_reg *vco_CF_CAL_regPtr;

// vco_CAL_MSB_reg		0x06		// VCO_REG 0x06 MSB Calibration
typedef struct vco_CAL_MSBreg
{
	unsigned int	INITIALIZATION:9;				// Bits 0-8:	VCO MSB CALIBRATION INITIALIZATION(Default - 255d)
	unsigned int	RESERVED1:7;					// Bits 9-15:	RESERVED
}vco_CAL_MSB_reg;
typedef struct vco_CAL_MSB_reg *vco_CAL_MSB_regPtr;

// vco_PWR_CNTRL_reg	0x07		// VCO_REG 0x07 Output Power Control
typedef struct vco_PWR_CNTRLreg
{
	unsigned int	OUT_STGE_GN_CNTL:4;				// Bits 0-3:	Output stage gain control in 1 dB steps
	unsigned int	INITIALIZATION:1;				// Bit 4:		Program to 1d
	unsigned int	RESERVED1:11;					// Bits 5-8:	RESERVED
	unsigned int	RESERVED2:11;					// Bits 9-15:	RESERVED
}vco_PWR_CNTRL_reg;
typedef struct vco_PWR_CNTRL_reg *vco_PWR_CNTRL_regPtr;

typedef union vcoregisters
{
	uint16_t			Data;
	vco_tuning_reg		vco_tuning;					// VCO_REG 0x00 Tuning
	vco_ENAB_reg		vco_ENAB;					// VCO_REG 0x01 Enable
	vco_OUT_DVDR_reg	vco_OUT_DVDR;				// VCO_REG 0x02 VCO Output Divider
	vco_CONFIG_reg		vco_CONFIG;					// VCO_REG 0x03 Configuration
	vco_CAL_BIAS_reg	vco_CAL_BIAS;				// VCO_REG 0x04 CAL/Bias
	vco_CF_CAL_reg		vco_CF_CAL;					// VCO_REG 0x05 CF_CAL
	vco_CAL_MSB_reg		vco_CAL_MSB;				// VCO_REG 0x06 MSB Calibration
	vco_PWR_CNTRL_reg	vco_PWR_CNTRL;				// VCO_REG 0x07 Output Power Control
}vco_registers;
typedef struct vco_registers *vco_registersPtr;

/******************************************************************************
 *
 * Module Prototypes
 *
 *****************************************************************************/
HAL_StatusTypeDef hmc_spi_init( void );
HAL_StatusTypeDef hmc_spi_write( PLL_Hardware hmc_hw, uint8_t PLL_Register, pll_registers pll_data );
HAL_StatusTypeDef hmc_spi_write_read( PLL_Hardware hmc_hw, uint8_t PLL_Register, pll_registers pll_data, PLL_Port_Regs *Rd_Data_Ptr );
HAL_StatusTypeDef hmc_Self_Test( PLL_Hardware hmc_hw );
bool hmc_verify_hw( PLL_Hardware hmc_hw );
HAL_StatusTypeDef hmc_pll_powerDn( PLL_Hardware hmc_hw );
HAL_StatusTypeDef hmc_pll_powerUp( PLL_Hardware hmc_hw );
HAL_StatusTypeDef hmc_vco_write( PLL_Hardware hmc_hw, uint8_t vco_Register, vco_registers vco_data );
HAL_StatusTypeDef hmc_vco_powerDn( PLL_Hardware hmc_hw );
HAL_StatusTypeDef hmc_vco_powerUp( PLL_Hardware hmc_hw );
HAL_StatusTypeDef hmc_sleep_plls( void );
HAL_StatusTypeDef hmc_powerup_plls( void );
HAL_StatusTypeDef hmc_calc_parameters( PLL_Parameters *pll_paramPtr );
HAL_StatusTypeDef hmc_SetupFreq( PLL_Hardware hmc_hw, float Target_Freq );
HAL_StatusTypeDef hmc_Enable_VCO( PLL_Hardware hmc_hw );
HAL_StatusTypeDef hmc_Disable_VCO( PLL_Hardware hmc_hw );
bool hmc_TestPll_Lock(PLL_Hardware hmc_hw);
unsigned char R_SCI6_SPI_Receive2( uint8_t str[], int wrtLen, uint8_t retStr[], int rdLen, int EnableCnt, PLL_Hardware hmc_hw );
void hmc_PwrOff_Lsrs( void );

#endif /* HMC832_H_ */
