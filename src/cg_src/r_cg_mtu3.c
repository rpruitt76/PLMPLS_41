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
* File Name    : r_cg_mtu3.c
* Version      : Code Generator for RX64M V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F564MLDxFB
* Tool-Chain   : CCRX
* Description  : This file implements device driver for MTU3 module.
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
/* Start user code for include. Do not edit comment generated here */
#include "r_flash_rx_if.h"
#include "LaserP.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_mtu3.h"
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_MTU3_Create
* Description  : This function initializes the MTU3 Unit0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_Create(void)
{
    /* Cancel MTU stop state in LPC */
    MSTP(MTU3) = 0U;

    /* Enable read/write to MTU registers */
    MTU.TRWERA.BYTE = _01_MTU_RWE_ENABLE;
    MTU.TRWERB.BYTE = _01_MTU_RWE_ENABLE;

    /* Stop all channels */
    MTU.TSTRA.BYTE = _00_MTU_CST0_OFF | _00_MTU_CST1_OFF | _00_MTU_CST2_OFF | _00_MTU_CST3_OFF | _00_MTU_CST4_OFF | 
                     _00_MTU_CST8_OFF;
    MTU5.TSTR.BYTE = _00_MTU_CSTW5_OFF | _00_MTU_CSTV5_OFF | _00_MTU_CSTU5_OFF;
    MTU.TSTRB.BIT.CST6 = 0U;
    MTU.TSTRB.BIT.CST7 = 0U;

    /* Channel 0 is used as normal mode */
    MTU0.TCR.BYTE = _00_MTU_CKEG_RISE | _40_MTU_CKCL_B;
    MTU0.TCR2.BYTE = _05_MTU_PCLK_1024;
    MTU0.TIER.BYTE |= _00_MTU_TGIEA_DISABLE | _00_MTU_TGIEB_DISABLE | _00_MTU_TGIEC_DISABLE | _00_MTU_TGIED_DISABLE | 
                      _00_MTU_TCIEU_DISABLE | _00_MTU_TCIEV_DISABLE | _00_MTU_TTGE2_DISABLE | _00_MTU_TTGE_DISABLE;
    MTU0.TIER2.BYTE = _00_MTU_TGIEE_DISABLE | _00_MTU_TGIEF_DISABLE;
    MTU0.TGRB = _0B72_TCNTB_VALUE;
    MTU0.TGRC = _0003_TCNTC_VALUE;
    MTU0.TGRE = _0003_TCNTE_VALUE;
    MTU0.TGRF = _0003_TCNTF_VALUE;
    MTU0.TMDR1.BYTE = _00_MTU_NORMAL;
    MTU.TSYRA.BYTE |= _00_MTU_SYNC0_OFF;
    MTU0.TIORH.BYTE = _30_MTU_IOB_LT | _08_MTU_IOA_IR;
    MTU0.TIORL.BYTE = _80_MTU_IOD_IR | _00_MTU_IOC_DISABLE;

    /* Channel 1 is used as normal mode */
    MTU1.TCR.BYTE = _00_MTU_CKEG_RISE | _20_MTU_CKCL_A;
    MTU1.TCR2.BYTE = _04_MTU_PCLK_1024;
    MTU1.TIER.BYTE |= _00_MTU_TGIEA_DISABLE | _00_MTU_TGIEB_DISABLE | _00_MTU_TGIEC_DISABLE | _00_MTU_TGIED_DISABLE | 
                      _00_MTU_TCIEU_DISABLE | _00_MTU_TCIEV_DISABLE | _00_MTU_TTGE2_DISABLE | _00_MTU_TTGE_DISABLE;
    MTU1.TGRA = _0B72_TCNTA_VALUE;
    MTU1.TGRB = _0003_TCNTB_VALUE;
    MTU1.TMDR1.BYTE = _00_MTU_NORMAL;
    MTU.TSYRA.BYTE |= _00_MTU_SYNC1_OFF;
    MTU1.TIOR.BYTE = _00_MTU_IOB_DISABLE | _03_MTU_IOA_LT;

    /* Channel 3 is used as normal mode */
    MTU3.TCR.BYTE = _00_MTU_PCLK_1 | _00_MTU_CKEG_RISE | _20_MTU_CKCL_A;
    MTU3.TCR2.BYTE = _00_MTU_PCLK_1;
    MTU3.TIER.BYTE |= _00_MTU_TGIEA_DISABLE | _00_MTU_TGIEB_DISABLE | _00_MTU_TGIEC_DISABLE | _00_MTU_TGIED_DISABLE | 
                      _00_MTU_TCIEU_DISABLE | _00_MTU_TCIEV_DISABLE | _00_MTU_TTGE2_DISABLE | _00_MTU_TTGE_DISABLE;
    MTU3.TGRA = _0002_TCNTA_VALUE;
    MTU3.TGRE = _0BB8_TCNTE_VALUE;
    MTU3.TMDR1.BYTE = _00_MTU_NORMAL;
    MTU.TSYRA.BYTE |= _00_MTU_SYNC3_OFF;
    MTU.TOERA.BYTE |= _C8_MTU_OE3D_ENABLE | _C1_MTU_OE3B_ENABLE;
    MTU3.TIORH.BYTE = _80_MTU_IOB_IR | _03_MTU_IOA_LT;
    MTU3.TIORL.BYTE = _80_MTU_IOD_IR | _08_MTU_IOC_IR;

    /* Channel 4 is used as normal mode */
    MTU4.TCR.BYTE = _05_MTU_PCLK_1024 | _00_MTU_CKEG_RISE | _40_MTU_CKCL_B;
    MTU4.TCR2.BYTE = _00_MTU_PCLK_1;
    MTU4.TIER.BYTE |= _00_MTU_TGIEA_DISABLE | _00_MTU_TGIEB_DISABLE | _00_MTU_TGIEC_DISABLE | _00_MTU_TGIED_DISABLE | 
                      _00_MTU_TCIEU_DISABLE | _00_MTU_TCIEV_DISABLE | _00_MTU_TTGE2_DISABLE | _00_MTU_TTGE_DISABLE;
    MTU4.TGRB = _0B72_TCNTB_VALUE;
    MTU4.TGRE = _0003_TCNTE_VALUE;
    MTU4.TGRF = _0003_TCNTF_VALUE;
    MTU4.TMDR1.BYTE = _00_MTU_NORMAL;
    MTU.TSYRA.BYTE |= _00_MTU_SYNC4_OFF;
    MTU4.TCNT = 0x0000U;
    MTU4.TADCR.WORD = _0000_MTU_UT4AE_DISABLE | _0000_MTU_UT4BE_DISABLE | _0000_MTU_BF_DISABLE;
    MTU.TOERA.BYTE |= _E0_MTU_OE4D_ENABLE | _D0_MTU_OE4C_ENABLE | _C4_MTU_OE4B_ENABLE | _C2_MTU_OE4A_ENABLE;
    MTU4.TIORH.BYTE = _30_MTU_IOB_LT | _08_MTU_IOA_IR;
    MTU4.TIORL.BYTE = _80_MTU_IOD_IR | _08_MTU_IOC_IR;

    /* Channel 6 is used as normal mode */
    MTU6.TCR.BYTE = _00_MTU_PCLK_1 | _00_MTU_CKEG_RISE | _C0_MTU_CKCL_D;
    MTU6.TCR2.BYTE = _00_MTU_PCLK_1;
    MTU6.TIER.BYTE |= _00_MTU_TGIEA_DISABLE | _00_MTU_TGIEB_DISABLE | _00_MTU_TGIEC_DISABLE | _00_MTU_TGIED_DISABLE | 
                      _00_MTU_TCIEU_DISABLE | _00_MTU_TCIEV_DISABLE | _00_MTU_TTGE2_DISABLE | _00_MTU_TTGE_DISABLE;
    MTU6.TGRD = _0003_TCNTD_VALUE;
    MTU6.TGRE = _0BB8_TCNTE_VALUE;
    MTU6.TMDR1.BYTE = _00_MTU_NORMAL;
    MTU.TSYRB.BIT.SYNC6 = 0U;
    MTU.TOERB.BYTE |= _C8_MTU_OE6D_ENABLE | _C1_MTU_OE6B_ENABLE;
    MTU6.TIORH.BYTE = _80_MTU_IOB_IR | _08_MTU_IOA_IR;
    MTU6.TIORL.BYTE = _30_MTU_IOD_LT | _08_MTU_IOC_IR;

    /* Channel 7 is used as normal mode */
    MTU7.TCR.BYTE = _05_MTU_PCLK_1024 | _00_MTU_CKEG_RISE | _40_MTU_CKCL_B;
    MTU7.TCR2.BYTE = _00_MTU_PCLK_1;
    MTU7.TIER.BYTE |= _00_MTU_TGIEA_DISABLE | _00_MTU_TGIEB_DISABLE | _00_MTU_TGIEC_DISABLE | _00_MTU_TGIED_DISABLE | 
                      _00_MTU_TCIEU_DISABLE | _00_MTU_TCIEV_DISABLE | _00_MTU_TTGE2_DISABLE | _00_MTU_TTGE_DISABLE;
    MTU7.TGRB = _0B72_TCNTB_VALUE;
    MTU7.TGRE = _0003_TCNTE_VALUE;
    MTU7.TGRF = _0003_TCNTF_VALUE;
    MTU7.TMDR1.BYTE = _00_MTU_NORMAL;
    MTU.TSYRB.BIT.SYNC7 = 0U;
    MTU7.TCNT = 0x0000U;
    MTU7.TADCR.WORD = _0000_MTU_UT4AE_DISABLE | _0000_MTU_UT4BE_DISABLE | _0000_MTU_BF_DISABLE;
    MTU.TOERB.BYTE |= _E0_MTU_OE7D_ENABLE | _D0_MTU_OE7C_ENABLE | _C4_MTU_OE7B_ENABLE | _C2_MTU_OE7A_ENABLE;
    MTU7.TIORH.BYTE = _30_MTU_IOB_LT | _08_MTU_IOA_IR;
    MTU7.TIORL.BYTE = _80_MTU_IOD_IR | _08_MTU_IOC_IR;
    
    /* Disable read/write to MTU registers */
    MTU.TRWERA.BYTE = _00_MTU_RWE_DISABLE;
    MTU.TRWERB.BYTE = _00_MTU_RWE_DISABLE;

    /* Set MTIOC0A pin */
    MPC.P34PFS.BYTE = 0x01U;
    PORT3.PMR.BYTE |= 0x10U;
    /* Set MTIOC0B pin */
    MPC.P13PFS.BYTE = 0x01U;
    PORT1.PMR.BYTE |= 0x08U;
    /* Set MTIOC0D pin */
    MPC.PA3PFS.BYTE = 0x01U;
    PORTA.PMR.BYTE |= 0x08U;
    /* Set MTIOC1A pin */
    MPC.P20PFS.BYTE = 0x01U;
    PORT2.PMR.BYTE |= 0x01U;
    /* Set MTIOC3A pin */
    MPC.P14PFS.BYTE = 0x01U;
    PORT1.PMR.BYTE |= 0x10U;
    /* Set MTIOC3B pin */
    MPC.P80PFS.BYTE = 0x01U;
    PORT8.PMR.BYTE |= 0x01U;
    /* Set MTIOC3C pin */
    MPC.P56PFS.BYTE = 0x01U;
    PORT5.PMR.BYTE |= 0x40U;
    /* Set MTIOC3D pin */
    MPC.P81PFS.BYTE = 0x01U;
    PORT8.PMR.BYTE |= 0x02U;
    /* Set MTIOC4A pin */
    MPC.P82PFS.BYTE = 0x01U;
    PORT8.PMR.BYTE |= 0x04U;
    /* Set MTIOC4B pin */
    MPC.P17PFS.BYTE = 0x08U;
    PORT1.PMR.BYTE |= 0x80U;
    /* Set MTIOC4C pin */
    MPC.P25PFS.BYTE = 0x01U;
    PORT2.PMR.BYTE |= 0x20U;
    /* Set MTIOC4D pin */
    MPC.P31PFS.BYTE = 0x01U;
    PORT3.PMR.BYTE |= 0x02U;
    /* Set MTIOC6A pin */
    MPC.PE7PFS.BYTE = 0x08U;
    PORTE.PMR.BYTE |= 0x80U;
    /* Set MTIOC6B pin */
    MPC.PA5PFS.BYTE = 0x08U;
    PORTA.PMR.BYTE |= 0x20U;
    /* Set MTIOC6C pin */
    MPC.PE6PFS.BYTE = 0x08U;
    PORTE.PMR.BYTE |= 0x40U;
    /* Set MTIOC6D pin */
    MPC.PA0PFS.BYTE = 0x08U;
    PORTA.PMR.BYTE |= 0x01U;
    /* Set MTIOC7A pin */
    MPC.PA2PFS.BYTE = 0x08U;
    PORTA.PMR.BYTE |= 0x04U;
    /* Set MTIOC7B pin */
    MPC.PA1PFS.BYTE = 0x08U;
    PORTA.PMR.BYTE |= 0x02U;
    /* Set MTIOC7C pin */
    MPC.P67PFS.BYTE = 0x08U;
    PORT6.PMR.BYTE |= 0x80U;
    /* Set MTIOC7D pin */
    MPC.P66PFS.BYTE = 0x08U;
    PORT6.PMR.BYTE |= 0x40U;
}
/***********************************************************************************************************************
* Function Name: R_MTU3_C0_Start
* Description  : This function starts MTU unit0 channel 0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_C0_Start(void)
{
    MTU.TSTRA.BYTE |= _01_MTU_CST0_ON;
}
/***********************************************************************************************************************
* Function Name: R_MTU3_C0_Stop
* Description  : This function stops MTU0 channel 0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_C0_Stop(void)
{
    MTU.TSTRA.BIT.CST0 = 0U;
}
/***********************************************************************************************************************
* Function Name: R_MTU3_C1_Start
* Description  : This function starts MTU unit0 channel 1 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_C1_Start(void)
{
    MTU.TSTRA.BYTE |= _02_MTU_CST1_ON;
}
/***********************************************************************************************************************
* Function Name: R_MTU3_C1_Stop
* Description  : This function stops MTU0 channel 1 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_C1_Stop(void)
{
    MTU.TSTRA.BIT.CST1 = 0U;
}
/***********************************************************************************************************************
* Function Name: R_MTU3_C3_Start
* Description  : This function starts MTU unit0 channel 3 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_C3_Start(void)
{
    MTU.TSTRA.BYTE |= _40_MTU_CST3_ON;
}
/***********************************************************************************************************************
* Function Name: R_MTU3_C3_Stop
* Description  : This function stops MTU0 channel 3 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_C3_Stop(void)
{
    MTU.TSTRA.BIT.CST3 = 0U;
}
/***********************************************************************************************************************
* Function Name: R_MTU3_C4_Start
* Description  : This function starts MTU unit0 channel 4 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_C4_Start(void)
{
    MTU.TSTRA.BYTE |= _80_MTU_CST4_ON;
}
/***********************************************************************************************************************
* Function Name: R_MTU3_C4_Stop
* Description  : This function stops MTU0 channel 4 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_C4_Stop(void)
{
    MTU.TSTRA.BIT.CST4 = 0U;
}
/***********************************************************************************************************************
* Function Name: R_MTU3_C6_Start
* Description  : This function starts MTU unit0 channel 6 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_C6_Start(void)
{
    MTU.TSTRB.BYTE |= _40_MTU_CST3_ON;
}
/***********************************************************************************************************************
* Function Name: R_MTU3_C6_Stop
* Description  : This function stops MTU0 channel 6 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_C6_Stop(void)
{
    MTU.TSTRB.BIT.CST6 = 0U;
}
/***********************************************************************************************************************
* Function Name: R_MTU3_C7_Start
* Description  : This function starts MTU unit0 channel 7 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_C7_Start(void)
{
    MTU.TSTRB.BIT.CST7 = 1U;
}
/***********************************************************************************************************************
* Function Name: R_MTU3_C7_Stop
* Description  : This function stops MTU0 channel 7 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_C7_Stop(void)
{
    MTU.TSTRB.BIT.CST7 = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: R_MTU3_plmCreate
* Description  : This function initializes the MTU3 Unit0 module according to the passed parameters.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_plmCreate(struct plmLaser_entry laser1, struct plmLaser_entry laser2, struct plmLaser_entry laser3, struct plmLaser_entry laser4)
{
    /* Cancel MTU stop state in LPC */
    MSTP(MTU3) = 0U;

    /* Enable read/write to MTU registers */
    MTU.TRWERA.BYTE = _01_MTU_RWE_ENABLE;
    MTU.TRWERB.BYTE = _01_MTU_RWE_ENABLE;

    /* Stop all channels */
    MTU.TSTRA.BYTE = _00_MTU_CST0_OFF | _00_MTU_CST1_OFF | _00_MTU_CST2_OFF | _00_MTU_CST3_OFF | _00_MTU_CST4_OFF |
                     _00_MTU_CST8_OFF;
    MTU5.TSTR.BYTE = _00_MTU_CSTW5_OFF | _00_MTU_CSTV5_OFF | _00_MTU_CSTU5_OFF;
    MTU.TSTRB.BIT.CST6 = 0U;
    MTU.TSTRB.BIT.CST7 = 0U;

    /* Channel 0 is used as normal mode */
    if (laser1.cnt_value > 0)
    {
		if( (cntrl_flg & 0x01) > 0 )
			laser1.cnt_value = 0;
		if (laser1.Special1 == MODE_TCR2)
		{
			MTU0.TCR.BYTE = _00_MTU_CKEG_RISE | _40_MTU_CKCL_B;
			MTU0.TCR2.BYTE = laser1.prescaler;
		}
		else
		{
			MTU0.TCR.BYTE = _00_MTU_CKEG_RISE | _40_MTU_CKCL_B | laser1.prescaler;
			MTU0.TCR2.BYTE = 0;
		}
		MTU0.TIER.BYTE |= _00_MTU_TGIEA_DISABLE | _00_MTU_TGIEB_DISABLE | _00_MTU_TGIEC_DISABLE | _00_MTU_TGIED_DISABLE |
						  _00_MTU_TCIEU_DISABLE | _00_MTU_TCIEV_DISABLE | _00_MTU_TTGE2_DISABLE | _00_MTU_TTGE_DISABLE;
		MTU0.TIER2.BYTE = _00_MTU_TGIEE_DISABLE | _00_MTU_TGIEF_DISABLE;
		MTU0.TGRB = laser1.cnt_value;
		MTU0.TGRC = _0003_TCNTC_VALUE;
		MTU0.TGRE = _0003_TCNTE_VALUE;
		MTU0.TGRF = _0003_TCNTF_VALUE;
		MTU0.TMDR1.BYTE = _00_MTU_NORMAL;
		MTU.TSYRA.BYTE |= _00_MTU_SYNC0_OFF;
		MTU0.TIORH.BYTE = _30_MTU_IOB_LT | _08_MTU_IOA_IR;
		MTU0.TIORL.BYTE = _80_MTU_IOD_IR | _00_MTU_IOC_DISABLE;
    }
    else
    {
    	// Turn off Channel 0
    	R_MTU3_LaserDiode0_Off();
    }
    /* Channel 1 is used as normal mode */
	if (laser2.cnt_value > 0)
	{
		if( (cntrl_flg & 0x02) > 0 )
			laser2.cnt_value = 0;
		if (laser2.Special1 == MODE_TCR2)
		{
			MTU1.TCR.BYTE = _00_MTU_CKEG_RISE | _20_MTU_CKCL_A;
			MTU1.TCR2.BYTE = laser2.prescaler;
		}
		else
		{
			MTU1.TCR.BYTE = _00_MTU_CKEG_RISE | _20_MTU_CKCL_A | laser2.prescaler;
			MTU1.TCR2.BYTE = 0;
		}
		MTU1.TIER.BYTE |= _00_MTU_TGIEA_DISABLE | _00_MTU_TGIEB_DISABLE | _00_MTU_TGIEC_DISABLE | _00_MTU_TGIED_DISABLE |
						  _00_MTU_TCIEU_DISABLE | _00_MTU_TCIEV_DISABLE | _00_MTU_TTGE2_DISABLE | _00_MTU_TTGE_DISABLE;
		MTU1.TGRA = laser2.cnt_value;
		MTU1.TGRB = _0003_TCNTB_VALUE;
		MTU1.TMDR1.BYTE = _00_MTU_NORMAL;
		MTU.TSYRA.BYTE |= _00_MTU_SYNC1_OFF;
		MTU1.TIOR.BYTE = _00_MTU_IOB_DISABLE | _03_MTU_IOA_LT;
	}
	else
	{
	  	// Turn off Channel 1
	   	R_MTU3_LaserDiode1_Off();
	}

    /* Channel 3 is used as normal mode */
	if (laser3.cnt_value > 0)
	{
		if( (cntrl_flg & 0x04) > 0 )
			laser3.cnt_value = 0;
		//P14/Pin 43: MTU3: PLLInput2...OFF
		MPC.P14PFS.BYTE = 0x00U;					// No Periph Control.
		PORT1.PMR.BYTE &= ~0x10U;					// Setup as I/O.
		PORT1.PDR.BYTE |= 0x10U;					// Setup as Output.
		PORT1.PODR.BYTE |= 0x10U;					// Set as HIGH.
		R_MTU3_LaserDiode2a_Off();
	}
	else
	{
	  	// Turn off Channel 2
	   	R_MTU3_LaserDiode2a_Off();
	}

	/* Channel 4 is used as normal mode */
	if (laser3.cnt_value > 0)
	{
		if( (cntrl_flg & 0x04) > 0 )
			laser3.cnt_value = 0;
		if (laser3.Special1 == MODE_TCR2) {
			MTU4.TCR.BYTE = _00_MTU_CKEG_RISE | _40_MTU_CKCL_B;
			MTU4.TCR2.BYTE = laser3.prescaler;
		} else {
			MTU4.TCR.BYTE = _00_MTU_CKEG_RISE | _40_MTU_CKCL_B
					| laser3.prescaler;
			MTU4.TCR2.BYTE = 0;
		}
		MTU4.TIER.BYTE |= _00_MTU_TGIEA_DISABLE | _00_MTU_TGIEB_DISABLE
				| _00_MTU_TGIEC_DISABLE | _00_MTU_TGIED_DISABLE |
				_00_MTU_TCIEU_DISABLE | _00_MTU_TCIEV_DISABLE
				| _00_MTU_TTGE2_DISABLE | _00_MTU_TTGE_DISABLE;
		MTU4.TGRB = laser3.cnt_value;
		MTU4.TGRE = _0003_TCNTE_VALUE;
		MTU4.TGRF = _0003_TCNTF_VALUE;
		MTU4.TMDR1.BYTE = _00_MTU_NORMAL;
		MTU.TSYRA.BYTE |= _00_MTU_SYNC4_OFF;
		MTU4.TCNT = 0x0000U;
		MTU4.TADCR.WORD = _0000_MTU_UT4AE_DISABLE | _0000_MTU_UT4BE_DISABLE
				| _0000_MTU_BF_DISABLE;
		MTU.TOERA.BYTE |= _E0_MTU_OE4D_ENABLE | _D0_MTU_OE4C_ENABLE
				| _C4_MTU_OE4B_ENABLE | _C2_MTU_OE4A_ENABLE;
		MTU4.TIORH.BYTE = _30_MTU_IOB_LT | _08_MTU_IOA_IR;
		MTU4.TIORL.BYTE = _80_MTU_IOD_IR | _08_MTU_IOC_IR;
	}
	else
	{
	  	// Turn off Channel 2
	   	R_MTU3_LaserDiode2b_Off();
	}

	/* Channel 6 is used as normal mode */
	if (laser4.cnt_value > 0)
	{
		if( (cntrl_flg & 0x08) > 0 )
			laser4.cnt_value = 0;
		//PA0/Pin 97: MTU6: PLLInput3
		MPC.PA0PFS.BYTE = 0x00U;					// No Periph Control.
		PORTA.PMR.BYTE &= ~0x01U;					// Setup as I/O.
		PORTA.PDR.BYTE |= 0x01U;					// Setup as Output.
		PORTA.PODR.BYTE |= 0x01U;					// Set as HIGH.
		R_MTU3_LaserDiode3a_Off();
	}
	else
	{
	  	// Turn off Channel 3
	   	R_MTU3_LaserDiode3a_Off();
	}

    /* Channel 7 is used as normal mode */
	if (laser4.cnt_value > 0)
	{
		if( (cntrl_flg & 0x08) > 0 )
			laser4.cnt_value = 0;
		if (laser4.Special1 == MODE_TCR2) {
			MTU7.TCR.BYTE = _00_MTU_CKEG_RISE | _40_MTU_CKCL_B;
			MTU7.TCR2.BYTE = laser4.prescaler;
		} else {
			MTU7.TCR.BYTE = _00_MTU_CKEG_RISE | _40_MTU_CKCL_B
					| laser4.prescaler;
			MTU7.TCR2.BYTE = 0;
		}
		MTU7.TIER.BYTE |= _00_MTU_TGIEA_DISABLE | _00_MTU_TGIEB_DISABLE
				| _00_MTU_TGIEC_DISABLE | _00_MTU_TGIED_DISABLE |
				_00_MTU_TCIEU_DISABLE | _00_MTU_TCIEV_DISABLE
				| _00_MTU_TTGE2_DISABLE | _00_MTU_TTGE_DISABLE;
		MTU7.TGRB = laser4.cnt_value;
		MTU7.TGRE = _0003_TCNTE_VALUE;
		MTU7.TGRF = _0003_TCNTF_VALUE;
		MTU7.TMDR1.BYTE = _00_MTU_NORMAL;
		MTU.TSYRB.BIT.SYNC7 = 0U;
		MTU7.TCNT = 0x0000U;
		MTU7.TADCR.WORD = _0000_MTU_UT4AE_DISABLE | _0000_MTU_UT4BE_DISABLE
				| _0000_MTU_BF_DISABLE;
		MTU.TOERB.BYTE |= _E0_MTU_OE7D_ENABLE | _D0_MTU_OE7C_ENABLE
				| _C4_MTU_OE7B_ENABLE | _C2_MTU_OE7A_ENABLE;
		MTU7.TIORH.BYTE = _30_MTU_IOB_LT | _08_MTU_IOA_IR;
		MTU7.TIORL.BYTE = _80_MTU_IOD_IR | _08_MTU_IOC_IR;
		R_MTU3_LaserDiode3b_Off();
	}
	else
	{
	  	// Turn off Channel 3
	   	R_MTU3_LaserDiode3b_Off();
	}

    /* Disable read/write to MTU registers */
    MTU.TRWERA.BYTE = _00_MTU_RWE_DISABLE;
    MTU.TRWERB.BYTE = _00_MTU_RWE_DISABLE;

    /* Set MTIOC0A pin */
    MPC.P34PFS.BYTE = 0x01U;
    PORT3.PMR.BYTE |= 0x10U;
    /* Set MTIOC0B pin */
    MPC.P13PFS.BYTE = 0x01U;
    PORT1.PMR.BYTE |= 0x08U;
    /* Set MTIOC0D pin */
    MPC.PA3PFS.BYTE = 0x01U;
    PORTA.PMR.BYTE |= 0x08U;
    /* Set MTIOC1A pin */
    MPC.P20PFS.BYTE = 0x01U;
    PORT2.PMR.BYTE |= 0x01U;

    /* Set MTIOC4B pin */
	MPC.P17PFS.BYTE = 0x08U;
	PORT1.PMR.BYTE |= 0x80U;

    /* Set MTIOC3B pin */
    MPC.P80PFS.BYTE = 0x01U;
    PORT8.PMR.BYTE |= 0x01U;
    /* Set MTIOC3C pin */
    MPC.P56PFS.BYTE = 0x01U;
    PORT5.PMR.BYTE |= 0x40U;
    /* Set MTIOC3D pin */
    MPC.P81PFS.BYTE = 0x01U;
    PORT8.PMR.BYTE |= 0x02U;
    /* Set MTIOC4A pin */
    MPC.P82PFS.BYTE = 0x01U;
    PORT8.PMR.BYTE |= 0x04U;
    /* Set MTIOC4C pin */
    MPC.P25PFS.BYTE = 0x01U;
    PORT2.PMR.BYTE |= 0x20U;
    /* Set MTIOC4D pin */
    MPC.P31PFS.BYTE = 0x01U;
    PORT3.PMR.BYTE |= 0x02U;
    /* Set MTIOC6A pin */
    MPC.PE7PFS.BYTE = 0x08U;
    PORTE.PMR.BYTE |= 0x80U;
    /* Set MTIOC6B pin */
    MPC.PA5PFS.BYTE = 0x08U;
    PORTA.PMR.BYTE |= 0x20U;
    /* Set MTIOC6C pin */
    MPC.PE6PFS.BYTE = 0x08U;
    PORTE.PMR.BYTE |= 0x40U;

	/* Set MTIOC7B pin */
	MPC.PA1PFS.BYTE = 0x08U;
	PORTA.PMR.BYTE |= 0x02U;

    /* Set MTIOC7A pin */
    MPC.PA2PFS.BYTE = 0x08U;
    PORTA.PMR.BYTE |= 0x04U;
    /* Set MTIOC7C pin */
    MPC.P67PFS.BYTE = 0x08U;
    PORT6.PMR.BYTE |= 0x80U;
    /* Set MTIOC7D pin */
    MPC.P66PFS.BYTE = 0x08U;
    PORT6.PMR.BYTE |= 0x40U;
}

/***********************************************************************************************************************
* Function Name: R_MTU3_AllLasers_Off
* Description  : This function turns off all lasers.
* Author: Ralph Pruitt
* Date: Feb 22 2015
* Updated:
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_AllLasers_Off( void)
{
	R_MTU3_LaserDiode0_Off();
	R_MTU3_LaserDiode1_Off();
	R_MTU3_LaserDiode2a_Off();
	R_MTU3_LaserDiode2b_Off();
	R_MTU3_LaserDiode3a_Off();
	R_MTU3_LaserDiode3b_Off();
}

/***********************************************************************************************************************
* Function Name: R_MTU3_LaserDiode0_Off
* Description  : This function turns off Laser Diode 0 Timer and tri-states the Pin P13.
* Author: Ralph Pruitt
* Date: Feb 22 2015
* Updated:
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_LaserDiode0_Off( void)
{
	// This function stops MTU0 channel 0 counter.
	R_MTU3_C0_Stop();

	/* Set MTIOC0B pin Tri-State.*/
	PORT1.PMR.BYTE &= ~0x08U;
	PORT1.PDR.BYTE &= ~0x08U;
}

/***********************************************************************************************************************
* Function Name: R_MTU3_LaserDiode0_Enable
* Description  : This function enables Laser Diode 0 Timer on Pin P13.
* Author: Ralph Pruitt
* Date: Feb 22 2015
* Updated:
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_LaserDiode0_Enable( void)
{
	/* Set MTIOC0B pin Enabled.*/
	PORT1.PMR.BYTE |=  0x08U;
	PORT1.PDR.BYTE  |=  0x08U;
}

/***********************************************************************************************************************
* Function Name: R_MTU3_LaserDiode1_Off
* Description  : This function turns off Laser Diode 1 Timer and tri-states the Pin P20.
* Author: Ralph Pruitt
* Date: Feb 22 2015
* Updated:
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_LaserDiode1_Off( void)
{
	// This function stops MTU0 channel 1 counter.
	R_MTU3_C1_Stop();

	/* Set MTIOC1A pin Tri-State.*/
	PORT2.PMR.BYTE &=~ 0x01U;
	PORT2.PDR.BYTE &= ~0x01U;
}

/***********************************************************************************************************************
* Function Name: R_MTU3_LaserDiode1_Enable
* Description  : This function enables Laser Diode 1 Timer on Pin P20.
* Author: Ralph Pruitt
* Date: Feb 22 2015
* Updated:
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_LaserDiode1_Enable( void)
{
	/* Set MTIOC1A pin Enabled.*/
	PORT2.PMR.BYTE |= 0x01U;
	PORT2.PDR.BYTE |= 0x01U;
}

/***********************************************************************************************************************
* Function Name: R_MTU3_LaserDiode2a_Off
* Description  : This function turns off Laser Diode 2a Timer and tri-states the Pin P14.
* Author: Ralph Pruitt
* Date: Feb 22 2015
* Updated:
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_LaserDiode2a_Off( void)
{
	// 1. Stop PLLInputC
	// This function stops MTU0 channel 0 counter.
	R_MTU3_C3_Stop();

	/* Set MTIOC3A pin Tri-State.*/
	PORT1.PMR.BYTE &= ~0x10U;
	PORT1.PDR.BYTE &= ~0x10U;
	// 2. Power Down U5 Multiplier.....PLLC_Enable(ACTIVE HIGH)...P02
	//PORT0.PDR.BYTE |= 0x04;
	//PORT0.PODR.BYTE &= ~0x04;
	//PORT0.PDR.BYTE &= ~0x03U;
}

/***********************************************************************************************************************
* Function Name: R_MTU3_LaserDiode2a_Enable
* Description  : This function enables Laser Diode 2a Timer and enables Pin P14.
* Author: Ralph Pruitt
* Date: Feb 22 2015
* Updated:
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_LaserDiode2a_Enable( void)
{
	// 1. Enable PLLInputC
	/* Set MTIOC3A pin Enabled.*/
	PORT1.PMR.BYTE |= 0x10U;
	PORT1.PDR.BYTE |= 0x10U;
	// 2. Power Up U5 Multiplier.....PLLC_Enable(Active HIGH)...P02
	//PORT0.PDR.BYTE |= 0x03U;
	//PORT0.PDR.BYTE |= 0x04;
	//PORT0.PODR.BYTE |= 0x04;
}

/***********************************************************************************************************************
* Function Name: R_MTU3_LaserDiode2b_Off
* Description  : This function turns off Laser Diode 2b Timer and tri-states the Pin P17.
* Author: Ralph Pruitt
* Date: Feb 22 2015
* Updated:
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_LaserDiode2b_Off( void)
{
	// This function stops MTU0 channel 4 counter.
	R_MTU3_C4_Stop();

	/* Set MTIOC4B pin Tri-State.*/
	PORT1.PMR.BYTE &= ~0x80U;
	PORT1.PDR.BYTE &= ~0x80U;
}

/***********************************************************************************************************************
* Function Name: R_MTU3_LaserDiode2b_Enable
* Description  : This function enables Laser Diode 2b Timer on Pin P17.
* Author: Ralph Pruitt
* Date: Feb 22 2015
* Updated:
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_LaserDiode2b_Enable( void)
{
	/* Set MTIOC4B pin Enabled.*/
	PORT1.PMR.BYTE |= 0x80U;
	PORT1.PDR.BYTE |= 0x80U;
}

/***********************************************************************************************************************
* Function Name: R_MTU3_LaserDiode3a_Off
* Description  : This function turns off Laser Diode 3a Timer and tri-states the Pin PA0.
* Author: Ralph Pruitt
* Date: Feb 22 2015
* Updated:
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_LaserDiode3a_Off( void)
{
	// 1. Stop PLLInputD
	// This function stops MTU0 channel 0 counter.
	R_MTU3_C6_Stop();

	/* Set MTIOC6D pin Tri-State.*/
	PORTA.PMR.BYTE &= ~0x01U;
	PORTA.PDR.BYTE &= ~0x01U;
	// 2. Power Down U6 Multiplier.....PLLD_Enable(ACTIVE HIGH)...P24
	//PORT2.PDR.BYTE |= 0x10;
	//PORT2.PODR.BYTE &= ~0x10;
	//PORT2.PDR.BYTE &= ~0x0CU;
}

/***********************************************************************************************************************
* Function Name: R_MTU3_LaserDiode3a_Enable
* Description  : This function enables Laser Diode 3a Timer on Pin PA0.
* Author: Ralph Pruitt
* Date: Feb 22 2015
* Updated:
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_LaserDiode3a_Enable( void)
{
	// 1. Enable PLLInputD
	/* Set MTIOC6D pin Enabled.*/
	PORTA.PMR.BYTE |= 0x01U;
	PORTA.PDR.BYTE |= 0x01U;
	// 2. Power Up U6 Multiplier.....PLLD_Enable(Active HIGH)...P24
	//PORT2.PDR.BYTE |= 0x0CU;
	//PORT2.PDR.BYTE |= 0x10;
	//PORT2.PODR.BYTE |= 0x10;
}

/***********************************************************************************************************************
* Function Name: R_MTU3_LaserDiode3b_Off
* Description  : This function turns off Laser Diode 3b Timer and tri-states the Pin PA1.
* Author: Ralph Pruitt
* Date: Feb 22 2015
* Updated:
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_LaserDiode3b_Off( void)
{
	// This function stops MTU0 channel 7 counter.
	R_MTU3_C7_Stop();

	/* Set MTIOC7B pin Tri-State.*/
	PORTA.PMR.BYTE &= ~0x02U;
	PORTA.PDR.BYTE &= ~0x02U;
}

/***********************************************************************************************************************
* Function Name: R_MTU3_LaserDiode3b_Enable
* Description  : This function enables Laser Diode 3b Timer on Pin PA1.
* Author: Ralph Pruitt
* Date: Feb 22 2015
* Updated:
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MTU3_LaserDiode3b_Enable( void)
{
	/* Set MTIOC7B pin Enabled.*/
	PORTA.PMR.BYTE |= 0x02U;
	PORTA.PDR.BYTE |= 0x02U;
}

/* End user code. Do not edit comment generated here */
