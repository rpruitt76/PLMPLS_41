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
* File Name    : r_cg_main.c
* Version      : Code Generator for RX64M V1.01.00.02 [31 Jul 2014]
* Device(s)    : R5F564MLDxFB
* Tool-Chain   : CCRX
* Description  : This file implements main function.
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
#include "r_cg_cgc.h"
#include "r_cg_cac.h"
#include "r_cg_lpc.h"
#include "r_cg_icu.h"
#include "r_cg_port.h"
#include "r_cg_mtu3.h"
#include "r_cg_tmr.h"
#include "r_cg_cmt.h"
#include "r_cg_rtc.h"
#include "r_cg_wdt.h"
#include "r_cg_sci.h"
#include "r_cg_crc.h"
#include "r_cg_s12ad.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_flash_rx_if.h"
#include <stdio.h>
#include <string.h>
#include <LaserP.h>
#include "r_cg_userdefine.h"
#include "monitor.h"
#include "spin_led.h"
#include <stdlib.h>
#include <math.h>
#include "usb_common.h"
#include "usb_msc.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"
#include "gpio.h"
#include "hmc832.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
void main_plm(void);

static unsigned int laser_hold;
//static unsigned char once, OverRide;
static unsigned char OverRide;
/* End user code. Do not edit comment generated here */


void R_MAIN_UserInit(void);
void my_sw_warmstart_beep(void)
{
	// 6. Re-enable Key Hardware after wake-up.
	SYSTEM.PRCR.WORD = 0xA50BU;
	SYSTEM.SBYCR.WORD &= ~0x8000U;
	SYSTEM.DPSIER1.BYTE |= 0x80;
	SYSTEM.DPSIFR1.BYTE = 0;
	SYSTEM.DPSBYCR.BYTE = 0x03U;
	SYSTEM.PRCR.WORD = 0xA500U;

	power_up2();
	accurate_delay(100);					// Wait for power to stabilize.
	audio_flg = 1;						// Enable Audio
	init_sound();
	speaker_enable();
	force_beep(50);		 				// Force Beep.
	speaker_disable();
	audio_flg = 0;						// Disable Audio
	power_dn();
}

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
	speaker_disable();
	R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
	//Force Msgs
	StrmOn = 1;
    printf2("PLM/Beacon II OS\n");
    if (subClock_Fail == 1)
    	printf2("RTC Sub-Clock Failed.\n");

#ifdef MONITOR_TSK
    while (1U)
    {
    	MonitorTask();
    }
#else
    // Start USB Code first
    switch (USBMSC_Init())
    {
		case USB_ERR_OK:
			printf2("USBMSC_Init: OK\n");
			break;
		case USB_ERR_FAIL:
			printf2("USBMSC_Init: USB_ERR_FAIL\n");
			break;
		case USB_ERR_PARAM:
			printf2("USBMSC_Init: USB_ERR_PARAM\n");
			break;
		case USB_ERR_STATE:
			printf2("USBMSC_Init: USB_ERR_STATE\n");
			break;
		case USB_ERR_BULK_OUT:
			printf2("USBMSC_Init: USB_ERR_BULK_OUT\n");
			break;
		case USB_ERR_BULK_OUT_NO_BUFFER:
			printf2("USBMSC_Init: USB_ERR_BULK_OUT_NO_BUFFER\n");
			break;
		case USB_ERR_CONTROL_OUT:
			printf2("USBMSC_Init: USB_ERR_CONTROL_OUT\n");
			break;
		case USB_ERR_NOT_CONNECTED:
			printf2("USBMSC_Init: USB_ERR_NOT_CONNECTED\n");
			break;
		case USB_ERR_UNKNOWN_REQUEST:
			printf2("USBMSC_Init: USB_ERR_UNKNOWN_REQUEST\n");
			break;
		case USB_ERR_INVALID_REQUEST:
			printf2("USBMSC_Init: USB_ERR_INVALID_REQUEST\n");
			break;
		case USB_ERR_CANCEL:
			printf2("USBMSC_Init: USB_ERR_CANCEL\n");
			break;
		case USB_ERR_BUSY:
			printf2("USBMSC_Init: USB_ERR_BUSY\n");
			break;
		default:
			printf2("USBMSC_Init: Unknown return code.\n");
			break;
    }
    // Msgs normal.
    StrmOn = 0;
    // Call PLM Main processing task
    main_plm();
#endif
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
	flash_err_t err;
	uint8_t write_buffer[65] = "Hello World...";
	int x;
	char tmpString[80];

	/*
	 * Add call to gpio Init Driver for tracked GPIOs...11/27/2020...RP
	 */
	GPIO_Init();

	// Disable any ints that must not be active during powerup.
	//R_ICU_IRQ15_Stop();			// Deactivate Keypad Interrupt.

	for (x =strlen((char *)write_buffer); x<64; x++)
			write_buffer[x] = 0x30 + (x & 0x0f);

		write_buffer[64] = 0x00;
	// Initialize the API.
	err= R_FLASH_Open();
	// Check for errors.
	if (FLASH_SUCCESS != err)
	{
		sprintf(tmpString, "ERROR: Flash_Open failed: %d\n", err);
		printf2(tmpString);
	}
	// Initialize and start SCI5.
	if (R_SCI5_Setup() != 0)		// Setup callbacks for SCI5.
		printf2("ERROR: R_SCI5_Setup() Failed!!\n");
	if (R_SCI5_Enable() != 0)		// Enable Ints for SCI5.
		printf2("ERROR: R_SCI5_Enable() Failed!!\n");
	R_SCI5_Create();
	R_SCI5_Start();

	// Initialize and start SCI6/SPI.
	StrmOn = 1;
	if (hmc_spi_init() == HAL_OK)
		printf2("SUCCESS: hmc_spi_init() Passed!!\n");
	else
		printf2("ERROR: hmc_spi_init() Failed!!\n");

#ifdef FLASH_TEST
	/* Erase Data Flash blocks 0. */
	err = R_FLASH_Erase(FLASH_DF_BLOCK_0, 1);
	/* Check for errors. */
	if (FLASH_SUCCESS != err)
	{
		printf2("ERROR: R_FLASH_Erase failed: %d\n", err);
	}

	// Check for status through control function and move operation to
	// completion.
//	do
//	{
//		// This will move the write sequence along...
//		err = R_FLASH_Control(FLASH_CMD_STATUS_GET, NULL);
//	}
//	while (FLASH_ERR_BUSY == err);

	// Lets see if we can write  the Flash memory
	/* Write data to internal memory. */
	err = R_FLASH_Write((uint32_t)write_buffer, &lser1e_time, strlen(write_buffer));
	//err = R_FLASH_Write((uint32_t)write_buffer, FLASH_DF_BLOCK_0, strlen(write_buffer));
	/* Check for errors. */
	if (FLASH_SUCCESS != err)
	{
		printf2("ERROR: R_FLASH_Write failed: %d\n", err);
	}
#endif

	// Enable Interrupts Here.
	SEI();

#if SPIN_LEDS_APP_EN > 0u
  #if BSP_CFG_LED_EN   > 0u
	// Turn off LEDs
    BSP_LED_Off();                                             /* Turn all LEDs off.                                   */
  #endif
#endif
	/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
//*****************************************************************************
//*
//* routine: main_plm
//* Date: 	 December 1, 2003
//* Author:  Ralph Pruitt
//* This is the main execution software. It is executed after a power-up reset.
//* It will then initialize hardware and then loop on the overall loopiing software.
//*
//*****************************************************************************
//
#define SCI5_STRIKE_MAX		5
void main_plm(void)
{
  char tmpString[80];
  char tempchar;
  //char tempcharSave;
  //char *tempString_ptr;
  char parm1[80];
  char cmdString[80];

  char *tempstr;
  char tempstrTemp[20];
  char tempstrTemp1[20];
  char tempstrTemp2[20];
  char temp_String[80];
  int hour, minute, second, month, day, year;
  //unsigned char status, key_var, old_key, sav_sec, sav_min, incr_flg;
  unsigned char key_var, once, sav_sec, incr_flg;
  unsigned int sav_min;
  char *char1;
  static unsigned int update_num;
  static unsigned int save_prog;				 // Program Number
  char Prog_str[10];
  char *Ptr1;
  struct laser_entry *data1;
  struct laser_entry data2;
  float sav_laser1, sav_laser2, sav_laser3, sav_laser4;
  int x;
  struct plmLaser_entry laser1P_time;
  struct plmLaser_entry laser2P_time;
  struct plmLaser_entry laser3P_time;
  struct plmLaser_entry laser4P_time;
  //struct plmLaserE_entry laser3P_time;
  //struct plmLaserE_entry laser4P_time;
  float Sweep_Tst;
  char **ptr1;
  int  tmpleaseDays;
  int  tmpMode;


  #ifdef DEBUGGR
  debug1(1);
  #endif
  // Reset Beacon II and Hold in Reset State: EFR32_RESET = LOW
  PLMpls_gpio_Off(EFR32_RESET);

  // Initialize Key aspects of PLM Hardware.
  init_devices();

  // Release Beacon II Reset and wait 200msec: EFR32_RESET = HIGH
  PLMpls_gpio_On(EFR32_RESET);
  // Wait to allow Beacon II to boot first....5 Seconds.
  for (x=0; x<5; x++)
  {
	  beep_tick();
	  long_delay(1);
  }

  strcpy(Bat_Lvl, Battery_Test());
  if (tst_bat()) {
//  if (mode != LOW_BAT) {
    #if GRAPHICS
    init_lcd2();	 	 	   		 		  	    // Initialize Graphics LCD Display.
    #else
    init_lcd();	 	 	   		 		  	    // Initialize Alpha LCD Display.
    #endif

  }
  //insert your functional code here...
  once = 0;
  Booted = 0;

  if (tst_bat()) {
//  if (mode != LOW_BAT) {
    restore_vars();		   			   	 		// Restore Key Variables.

    //EEPROM_READ((int)&eopmin_cnt, opmin_cnt);	 		 // Read the data to EEPROM.
    opmin_cnt = eopmin_cnt;

    //EEPROM_READ((int)&eserial_number, serial_number);	 // Read the data to EEPROM.
    serial_number = eserial_number;

#if LEASEOP
    //EEPROM_READ((int)&eopmin_lmt, opmin_lmt);	         // Read the data to EEPROM.
    opmin_lmt = eopmin_lmt;
#endif

    // Restore if Stack overflow for clean restart..
    if ((mode != Factory) &&
	    (mode != Soft_PD) &&
	    (mode != Soft_PD_CONTINUE) &&
	    (mode != Locked_CONTINUE) &&
	    (mode != Locked)) {
      mode = Boot_Screen;		   	     // Stack overflow....force to Boot Screen.
      once = 0;						 // Reset once flag.
    }
  }
  else {
    restore_vars();		   			   	 		// Restore Key Variables.
    //EEPROM_READ((int)&eopmin_cnt, opmin_cnt);	 		 // Read the data to EEPROM.
    opmin_cnt = eopmin_cnt;

    //EEPROM_READ((int)&eserial_number, serial_number);	 // Read the data to EEPROM.
    serial_number = eserial_number;

#if LEASEOP
    //EEPROM_READ((int)&eopmin_lmt, opmin_lmt);	         // Read the data to EEPROM.
    opmin_lmt = eopmin_lmt;
#endif
    if (mode != Locked)							// Preserve Locked Mode
	  mode = Low_PD;							// Force Mode to Low Power....
  }

  // Init Receive for Monitor....Prime Buffer
  tempchar = 0x00;
  R_SCI5_Serial_Rceive( &tempchar, RX_CHAR);

  // Enable Streaming for Monitor
   	StrmOn = 1;

    printf2("***************************************************************\n");
    printf2("PLM Monitor Starting... \n\n");
    printf2("***************************************************************\n");
    printf2("PLM PLUS OS Version 4.04\n");
    printf2("Copyright: Feb 5, 2022\n");
    printf2("Property of Cold Laser Therapeutics, LLC\n");
    printf2("***************************************************************\n\n\n");

  // Initialize PLM Monitor Code.
    // Clear strings for next pass;
    for (x=0; x<80; x++)
    {
    	tmpString[x] = 0x00;
    	cmdString[x] = 0x00;
    	parm1[x] = 0x00;
    }
    // Force tempchar to clear.
    //tempString_ptr = tmpString;
    //sci5_strikeCnt = 0;
    gp_sci5_rx_state = RX_COMPLETE;
    OverRide = 0;

    printf2("\n");
    printf2(" > ");

    /*
   	 *  Spi Bus Test Code...
   	 */

	StrmOn = 1;
	/*
	 * Power Up PLLs.
	 */
	if ( hmc_powerup_plls() == HAL_OK)
		monPrint("STATUS", "PLLs Powered Up.");					// PLLs Powered Up.
	else
		monPrint("ERROR", "PLLs failed Power Up.");				// PLLs failed Power Up.

	// Test PLL Modules and report status
	for (x=0;x<50;x++)
	{
		// Wait 100msec.
		accurate_delay( 10 );
		if (hmc_Self_Test( PLL_D_HW ) == HAL_OK)
			break;
	}
	for (x=0;x<50;x++)
	{
		// Wait 100msec.
		accurate_delay( 10 );
		if (hmc_Self_Test( PLL_C_HW ) == HAL_OK)
			break;
	}

	/*
	 * Self Test PLLs.
	 */
	if (hmc_Self_Test( PLL_C_HW ) == HAL_OK)
		monPrint("STATUS", "PLLC Self Test Passed.");			// Self Test Status
	else
		monPrint("ERROR", "PLLC failed Self Test.");			// Self Test Status

	if (hmc_Self_Test( PLL_D_HW ) == HAL_OK)
		monPrint("STATUS", "PLLD Self Test Passed.");			// Self Test Status
	else
		monPrint("ERROR", "PLLD failed Self Test.");			// Self Test Status

	// Verify PLL Modules and report status
	if ( hmc_verify_hw( PLL_C_HW ) )
		monPrint("STATUS", "PLLC is AVAILABLE.");				// PLL Available
	else
		monPrint("ERROR", "PLLC is not AVAILABLE.");			// PLL Not Available

	if ( hmc_verify_hw( PLL_D_HW ) )
		monPrint("STATUS", "PLLD is AVAILABLE.");				// PLL Available
	else
		monPrint("ERROR", "PLLD is not AVAILABLE.");			// PLL Not Available

	/*
	 * Power Down PLLs.
	 */

	if ( hmc_sleep_plls() == HAL_OK)
		monPrint("STATUS", "VCO PLLs Powered Down.");				// VCOs Powered Down.
	else
		monPrint("ERROR", "VCO PLLs failed Power Down.");			// VCOs failed Power Down.
#if 0
	/*
	 * TEST Code to Power Up PLLs.
	 */
	if ( hmc_powerup_plls() == HAL_OK)
		monPrint("STATUS", "PLLs Powered Up.");					// PLLs Powered Up.
	else
		monPrint("ERROR", "PLLs failed Power Up.");				// PLLs failed Power Up.
#endif
	/*
	 * Enable LF Lasers.
	 */
	PLMpls_LFlaser_enable(LASERALL_CNTL);						// Enable LF Lasers.


	StrmOn = 0;

  // Loop Forever
  while (1){
    key_down_flg = 0;	 			 // This flag is set when a Keypress is detected.
    // restore_vars();		   			   	 		// Restore Key Variables.
//	if (mode > (Blank_Settings+10)) {
	if (mode > END_SETTING) {
  	  lser1_time = 500;	 		 // Laser 1 Load.
  	  lser2_time = 250;	 		 // Laser 2 Load.
  	  lser3_time = 125;	 		 // Laser 3 Load.
  	  lser4_time = 50;	 		 // Laser 4 Load.
  	  stimer_low = 250;		 	 // Timer 2 Count Saved.
  	  sprescale = 2;			 	 // Timer 2 Prescale.
	  mode = 0;				 	 // System Tasking Mode.
	  sm = 1;					 // Sub-Mode Variable
#ifdef CLW
	  if (opMode == 3)			// Legacy is only active.
	  {
		  prog_num = CUSTOM4_START;				 // Program Number
	  }
	  else
	  {
		  prog_num = CUSTOM_START;				 // Program Number
	  }
#else
	  prog_num = CUSTOM_START;				 // Program Number
#endif
	  tmr_min = 5;				 // Timer Minutes
	  tmr_sec = 0;				 // Timer Seconds

	  save_vars();  	 	  				    // Save Updated Variables.
	}
	// Test for OverRide from Monitor
	if (OverRide > 0)
	{
		Clr_Mode();		// Clear Modes for new Mode
		once = 0;
		OverRide = 0;	// Clear OverRide Flag.
	}

	switch (mode) {
//*******************************************************************************
//*
//*   Factory Default Mode
//*
//*	  Factory Default Mode
//*******************************************************************************
	  case Factory:								// Factory Default Mode.
		printf2("*** Factory Default Mode ***\n");
		monPrint("MNTR", "Factory");			// Send Factory Status Message
	    mode = Factory_Screen;					// Change Mode to Factory Screen.
	    break;

//*******************************************************************************
//*
//*   Factory_Screen
//*
//*	  Factory_Screen
//*******************************************************************************
	  case Factory_Screen:						// Factory_Screen.
	    if (once == 0) {
		  printf2("*** Factory_Screen ***\n");
		  monPrint("MNTR", "Factory_Screen");	// Send Status Message
		  beep_3Bp();							// Beep Start Screen
		  factory_screen();						// Display Factory Screen.
		  two_sec_start();						// Two Second Timer Start.
		  once = 1;								// Set Once Flag.
		}
	    else
		  printf2(".");
	    if (two_sec_test() == 0) {
		  mode = Boot_Screen; 	  				// Set Mode to Boot_Screen.
		  once = 0;								// Reset once flag.
  		  clear_screen();						// Clear Screen.
		}
	    break;

//*******************************************************************************
//*
//*   Boot_Screen
//*
//*	  Boot_Screen
//*******************************************************************************
	  case Boot_Screen:							// Boot_Screen.
	    if (once == 0) {
		  printf2("*** Boot_Screen ***\n");
		  monPrint("MNTR", "Boot_Screen");	// Send Status Message
		  //Clear Timer Static Var...
		  Init_Timer();
		  beep_ArpUp();							// Beep Start Screen
		  boot_screen();						// Display Boot Screen.
		  if((opMode != 0) && (opMode != 3))
		  {
	          five_sec_clear();	  	 	 	  		// Clear Five Second Timer.
			  five_sec_start();						// Five Second Timer Start.
		  }
		  else
		  {
	          two_sec_clear();	  	 	 	  		// Clear two Second Timer.
			  two_sec_start();						// Two Second Timer Start.
		  }
		  // If Limit is passed....Then we must limit access to this unit.
		  once = 1;								// Set Once Flag.
		}
	    else
		  printf2(".");
	    if (((five_sec_test() == 0) && (opMode != 0) && (opMode != 3)) ||
	    	((two_sec_test() == 0) && ((opMode == 0) || (opMode == 3))))	{
	      if((opMode != 0) && (opMode != 3))
	      {
		      five_sec_clear();	  	 	 	  		// Clear Five Second Timer.
	      }
	      else
	      {
		      two_sec_clear();	  	 	 	  		// Clear two Second Timer.
	      }

          // Test Mode and Expired Status
          tmpleaseDays = CalcLeaseDays();		// Get the Lease Days status
          if ((tmpleaseDays == -1) && (opMode != 0) && (opMode != 3))
          {
		    mode = PBFEntryScreen;				        // Set Mode.
		    once = 0;								// Reset once flag.
  		    clear_screen();						// Clear Screen.
		  }
		  else{
		    mode = Main; 	  				        // Set Mode.
		    once = 0;								// Reset once flag.
  		    clear_screen();						// Clear Screen.
	      }
		}
	    break;

//*******************************************************************************
//*
//*   Date Entry Screen
//*
//*******************************************************************************
   	case DateEntryScreen:							// Show Date Entry Scree.
		if (once == 0) {
#if NEW_LCD
//		  init_lcd2();						    // Initialize the LCD Screen.
#endif
			nobeep_flg = 1;					    // Turn On Beep.
			init_devices();						// Init Device...Some hw not on.
			force_beep(50);		 				// Force Beep.
#if GRAPHICS
			init_lcd2();
#else
			init_lcd();
#endif
            strcpy(lease_str, "            ");			// Copy a Blank string to lease_str.
            DateEntryScrn();							// Display Sound Config Screen.
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
			once = 1;								// Set Once Flag.
			laser_hold = 0;						// Clear laser_hold var.
			beep_3Bp();							// Beep Start Screen
		}
		if (((Timeout_test() == 0) && Timeout_active()) ||
				(mode == LOW_BAT)) {
			nobeep_flg = 1;					    // Turn On Beep.
			if (mode == LOW_BAT)
				mode = Low_PD;	  				    // We are now in true Low Power Mode..
			else
				mode = Soft_PD; 	  				// Set Mode to Soft_PD.
			once = 0;								// Reset once flag.
		} // End If Test two_min_test Failed
		else {
			key_var = scan_keyboard();			// Scan Keyboard.
			if (key_var == 0){
				laser_hold = 1;						// Set laser_hold only if Laser key released.
				nobeep_flg = 1;					    // Turn On Beep.
			}
			if((key_var > 0) && (laser_hold == 1)) {
				laser_hold = 0; 			  	    // Only one Keypress is legal.
				nobeep_flg = 0;					    // Turn Off Beep Till mode determined.
				switch (key_var) {
				  case BACK:
					Backspace_Char(lease_str, LEASE_STR_LEN);
					lease_str[LEASE_STR_LEN-1] = NULL;
					break;

				  case ZERO:
				  case ONE:
				  case TWO:
				  case THREE:
				  case FOUR:
				  case FIVE:
				  case SIX:
				  case SEVEN:
				  case EIGHT:
				  case NINE:
					  char1 = get_numstr(key_var);		// Get New Digit.
					  shft_str_left(lease_str , LEASE_STR_LEN);		// Shift String Left by one digit.
					  lease_str[LEASE_STR_LEN-2] = char1[0];
					  lease_str[LEASE_STR_LEN-1] = NULL;
					  break;

				  case PERIOD:
					  shft_str_left(lease_str , LEASE_STR_LEN);		// Shift String Left by one digit.
					  lease_str[LEASE_STR_LEN-2] = '/';
					  lease_str[LEASE_STR_LEN-1] = NULL;
					  break;

				  case SELECT:
					  SetDatemonitor( lease_str );
//			    	  nobeep_flg = 1;					    // Turn On Beep.
					  mode = Main; 	  					// Set Mode to Main.
					  once = 0;								// Reset once flag.
					  break;

				  case CANCEL:
					  mode = Main; 	  					// Set Mode to Main.
					  once = 0;								// Reset once flag.
					  break;

				} // End Switch on key_var
				DateEntryScrn();							// Display Config Screen.

				if (mode != DateEntryScreen) {
					once = 0;							// Reset once flag.
					Timeout_clear();				   // Clear 5 MInute Timer.
				}
				else
					if(Timeout_active())
						Timout_start();					// TimeOut Timer Start.
			} //Endif Key Founr
		} // End If two_min_test active
		break;

//*******************************************************************************
//*
//*   Time Entry Screen
//*
//*******************************************************************************
	case TimeEntryScreen:							// Show Time Entry Screen.
		if (once == 0) {
#if NEW_LCD
//		  init_lcd2();						    // Initialize the LCD Screen.
#endif
			nobeep_flg = 1;					    // Turn On Beep.
			init_devices();						// Init Device...Some hw not on.
			force_beep(50);		 				// Force Beep.
#if GRAPHICS
			init_lcd2();
#else
			init_lcd();
#endif
            strcpy(lease_str, "            ");			// Copy a Blank string to lease_str.
            TimeEntryScrn();							// Display Sound Config Screen.
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
			once = 1;								// Set Once Flag.
			laser_hold = 0;						// Clear laser_hold var.
			beep_3Bp();							// Beep Start Screen
		}
		if (((Timeout_test() == 0) && Timeout_active()) ||
				(mode == LOW_BAT)) {
			nobeep_flg = 1;					    // Turn On Beep.
			if (mode == LOW_BAT)
				mode = Low_PD;	  				    // We are now in true Low Power Mode..
			else
				mode = Soft_PD; 	  				// Set Mode to Soft_PD.
			once = 0;								// Reset once flag.
		} // End If Test two_min_test Failed
		else {
			key_var = scan_keyboard();			// Scan Keyboard.
			if (key_var == 0){
				laser_hold = 1;						// Set laser_hold only if Laser key released.
				nobeep_flg = 1;					    // Turn On Beep.
			}
			if((key_var > 0) && (laser_hold == 1)) {
				laser_hold = 0; 			  	    // Only one Keypress is legal.
				nobeep_flg = 0;					    // Turn Off Beep Till mode determined.
				switch (key_var) {
				  case BACK:
					Backspace_Char(lease_str, LEASE_STR_LEN);
					lease_str[LEASE_STR_LEN-1] = NULL;
					break;

				  case ZERO:
				  case ONE:
				  case TWO:
				  case THREE:
				  case FOUR:
				  case FIVE:
				  case SIX:
				  case SEVEN:
				  case EIGHT:
				  case NINE:
					  char1 = get_numstr(key_var);		// Get New Digit.
					  shft_str_left(lease_str , LEASE_STR_LEN);		// Shift String Left by one digit.
					  lease_str[LEASE_STR_LEN-2] = char1[0];
					  lease_str[LEASE_STR_LEN-1] = NULL;
					  break;

				  case PERIOD:
					  shft_str_left(lease_str , LEASE_STR_LEN);		// Shift String Left by one digit.
					  lease_str[LEASE_STR_LEN-2] = ':';
					  lease_str[LEASE_STR_LEN-1] = NULL;
					  break;

				  case SELECT:
					  SetTimemonitor( lease_str );
//			    	  nobeep_flg = 1;					    // Turn On Beep.
					  mode = Main; 	  					// Set Mode to Main.
					  once = 0;								// Reset once flag.
					  break;

				  case CANCEL:
					  mode = Main; 	  					// Set Mode to Main.
					  once = 0;								// Reset once flag.
					  break;

				} // End Switch on key_var
				TimeEntryScrn();							// Display Config Screen.

				if (mode != TimeEntryScreen) {
					once = 0;							// Reset once flag.
					Timeout_clear();				   // Clear 5 MInute Timer.
				}
				else
					if(Timeout_active())
						Timout_start();					// TimeOut Timer Start.
			} //Endif Key Founr
		} // End If two_min_test active
		break;

//*******************************************************************************
//*
//*   SerialNumScreen
//*
//*******************************************************************************
	case SerialNumScreen:							// Show Key Entry Screen.
		if (once == 0) {
#if NEW_LCD
//		  init_lcd2();						    // Initialize the LCD Screen.
#endif
			nobeep_flg = 1;					    // Turn On Beep.
			init_devices();						// Init Device...Some hw not on.
			force_beep(50);		 				// Force Beep.
#if GRAPHICS
			init_lcd2();
#else
			init_lcd();
#endif
            strcpy(lease_str, "            ");			// Copy a Blank string to lease_str.
			SerialNumScrn();							// Display Sound Config Screen.
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
			once = 1;								// Set Once Flag.
			laser_hold = 0;						// Clear laser_hold var.
			beep_3Bp();							// Beep Start Screen
		}
		if (((Timeout_test() == 0) && Timeout_active()) ||
				(mode == LOW_BAT)) {
			nobeep_flg = 1;					    // Turn On Beep.
			if (mode == LOW_BAT)
				mode = Low_PD;	  				    // We are now in true Low Power Mode..
			else
				mode = Soft_PD; 	  				// Set Mode to Soft_PD.
			once = 0;								// Reset once flag.
		} // End If Test two_min_test Failed
		else {
			key_var = scan_keyboard();			// Scan Keyboard.
			if (key_var == 0){
				laser_hold = 1;						// Set laser_hold only if Laser key released.
				nobeep_flg = 1;					    // Turn On Beep.
			}
			if((key_var > 0) && (laser_hold == 1)) {
				laser_hold = 0; 			  	    // Only one Keypress is legal.
				nobeep_flg = 0;					    // Turn Off Beep Till mode determined.
				switch (key_var) {
				  case BACK:
					Backspace_Char(lease_str, LEASE_STR_LEN);
					lease_str[LEASE_STR_LEN-1] = NULL;
					break;

				  case ZERO:
				  case ONE:
				  case TWO:
				  case THREE:
				  case FOUR:
				  case FIVE:
				  case SIX:
				  case SEVEN:
				  case EIGHT:
				  case NINE:
					  char1 = get_numstr(key_var);		// Get New Digit.
					  shft_str_left(lease_str , LEASE_STR_LEN);		// Shift String Left by one digit.
					  lease_str[LEASE_STR_LEN-2] = char1[0];
					  lease_str[LEASE_STR_LEN-1] = NULL;
					  break;

				  case SELECT:
					  serial_number = strtoul( lease_str, ptr1, 10);
					  EEPROM_WRITE((uint32_t)&serial_number, (uint32_t)&eserial_number, sizeof(serial_number));	 		 // Write the data to EEPROM.
//			    	  nobeep_flg = 1;					    // Turn On Beep.
					  mode = Main; 	  					// Set Mode to Main.
					  once = 0;								// Reset once flag.
					  break;

				  case CANCEL:
					  mode = Main; 	  					// Set Mode to Main.
					  once = 0;								// Reset once flag.
					  break;

				} // End Switch on key_var
				SerialNumScrn();							// Display Config Screen.

				if (mode != SerialNumScreen) {
					once = 0;							// Reset once flag.
					Timeout_clear();				   // Clear 5 MInute Timer.
				}
				else
					if(Timeout_active())
						Timout_start();					// TimeOut Timer Start.
			} //Endif Key Founr
		} // End If two_min_test active
		break;

//*******************************************************************************
//*
//*   PBFEntryScreen
//*
//*   PBFEntryScreen
//*******************************************************************************
	case PBFEntryScreen:							// Show Key Entry Screen.
		if (once == 0) {
			nobeep_flg = 1;					    // Turn On Beep.
            strcpy(lease_str, "            ");			// Copy a Blank string to lease_str.
            PBFEntryScrn();							// Display Sound Config Screen.
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
			once = 1;								// Set Once Flag.
			laser_hold = 0;						// Clear laser_hold var.
			beep_3Bp();							// Beep Start Screen
		}
		if (((Timeout_test() == 0) && Timeout_active()) ||
				(mode == LOW_BAT)) {
			nobeep_flg = 1;					    // Turn On Beep.
			if (mode == LOW_BAT)
				mode = Low_PD;	  				    // We are now in true Low Power Mode..
			else
				mode = Soft_PD; 	  				// Set Mode to Soft_PD.
			once = 0;								// Reset once flag.
		} // End If Test two_min_test Failed
		else {
			key_var = scan_keyboard();			// Scan Keyboard.
			if (key_var == 0){
				laser_hold = 1;						// Set laser_hold only if Laser key released.
				nobeep_flg = 1;					    // Turn On Beep.
			}
			if((key_var > 0) && (laser_hold == 1)) {
				laser_hold = 0; 			  	    // Only one Keypress is legal.
				nobeep_flg = 0;					    // Turn Off Beep Till mode determined.
				switch (key_var) {
				  case BACK:
					Backspace_Char(lease_str, LEASE_STR_LEN);
					lease_str[LEASE_STR_LEN-1] = NULL;
					break;

				  case ZERO:
				  case ONE:
				  case TWO:
				  case THREE:
				  case FOUR:
				  case FIVE:
				  case SIX:
				  case SEVEN:
				  case EIGHT:
				  case NINE:
					  char1 = get_numstr(key_var);		// Get New Digit.
					  shft_str_left(lease_str , LEASE_STR_LEN);		// Shift String Left by one digit.
					  lease_str[LEASE_STR_LEN-2] = char1[0];
					  lease_str[LEASE_STR_LEN-1] = NULL;
					  break;

				  case SELECT:
					  // Time to validate if passed cde is good.
					  if (decodePBFcode( lease_str, &tmpleaseDays, &tmpMode))
					  {
						  // Validate lease Days and tmpMode
						  if((tmpleaseDays<=90) && (tmpleaseDays>=0))
						  {
							  if((tmpMode<=3) && (tmpMode>=0))
							  {
								  // We have a good Code. Change modes and Lease Days.
								  opMode = tmpMode;
								  leaseDays = tmpleaseDays;
								  getDate(&leaseMnth, &leaseDay, &leaseYear);
								  // Write new values to Data Flash.
								  EEPROM_WRITE((uint32_t)&opMode, (uint32_t)&eopMode, sizeof(opMode));	 			// Write opMode to Flash.
								  EEPROM_WRITE((uint32_t)&leaseDays, (uint32_t)&eleaseDays, sizeof(leaseDays));	 	// Write leaseDays to Flash.
								  EEPROM_WRITE((uint32_t)&leaseDay, (uint32_t)&eleaseDay, sizeof(leaseDay));	 		// Write leaseDay to Flash.
								  EEPROM_WRITE((uint32_t)&leaseMnth, (uint32_t)&eleaseMnth, sizeof(leaseMnth));	 	// Write leaseMnth to Flash.
								  EEPROM_WRITE((uint32_t)&leaseYear, (uint32_t)&eleaseYear, sizeof(leaseYear));	 	// Write leaseYear to Flash.
								  WDR(); //this prevents a timout on enabling

								  // Set Mode to Correct Mode
								  mode = Main; 	  					// Set Mode to Main.
								  once = 0;								// Reset once flag.
							  }
							  else
							  {
								  // We have a bad code need to change mode to enter code again.
								  mode = PBFErrorScreen; 	  					// Set Mode to Main.
								  once = 0;								// Reset once flag.
							  }
						  }
						  else
						  {
							  // We have a bad code need to change mode to enter code again.
							  mode = PBFErrorScreen; 	  					// Set Mode to Main.
							  once = 0;								// Reset once flag.
						  }
					  }
					  else
					  {
						  // We have a bad code need to change mode to enter code again.
						  mode = PBFErrorScreen; 	  					// Set Mode to Main.
						  once = 0;								// Reset once flag.
					  }
					  break;

				} // End Switch on key_var
				PBFEntryScrn();							// Display Config Screen.

				if (mode != PBFEntryScreen) {
					once = 0;							// Reset once flag.
					Timeout_clear();				   // Clear 5 MInute Timer.
				}
				else
					if(Timeout_active())
						Timout_start();					// TimeOut Timer Start.
			} //Endif Key Founr
		} // End If two_min_test active
		break;

//*******************************************************************************
//*
//*   PBFErrorScreen
//*
//*	  PBFErrorScreen
//*******************************************************************************
	case PBFErrorScreen:						// PBFErrorScreen.
		if (once == 0) {
			nobeep_flg = 1;					    // Turn On Beep.
			PBFErrorScrn(1);					// Display Sound Config Screen.
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
			once = 1;							// Set Once Flag.
			laser_hold = 0;						// Clear laser_hold var.
			beep_3Bp();							// Beep Start Screen
		}
		if (((Timeout_test() == 0) && Timeout_active()) ||
				(mode == LOW_BAT)) {
			nobeep_flg = 1;					    // Turn On Beep.
			if (mode == LOW_BAT)
				mode = Low_PD;	  				// We are now in true Low Power Mode..
			else
				mode = PBFEntryScreen; 	  		// Set Mode to PBFEntryScreen.
			once = 0;							// Reset once flag.
		} // End If Test two_min_test Failed
		else
		{
			key_var = scan_keyboard();			// Scan Keyboard.
			if (key_var == 0){
				laser_hold = 1;					// Set laser_hold only if Laser key released.
				nobeep_flg = 1;					// Turn On Beep.
			}
			if((key_var > 0) && (laser_hold == 1)) {
				laser_hold = 0; 			  	// Only one Keypress is legal.
				nobeep_flg = 0;					// Turn Off Beep Till mode determined.
				switch (key_var) {
				  case SELECT:
					  // Set Mode to Correct Mode
					  mode = PBFEntryScreen; 	// Set Mode to Main.
					  once = 0;					// Reset once flag.
			    	  nobeep_flg = 1;			// Turn On Beep.
					  break;

				} // End Switch on key_var
				PBFErrorScrn(1);				// Display Config Screen.
			} //Endif ((key_var > 0) && (laser_hold == 1))
		} // End If two_min_test active
	    break;

//*******************************************************************************
//*
//*   	ShowTimeMode
//*
//*   ShowTimeMode
//*******************************************************************************
	case ShowTimeMode:							// Show Key Entry Screen.
		if (once == 0) {
			TimeScrn();							// Display Sound Config Screen.
			accurate_delay( 200 );				// Delay 200 msec
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
			once = 1;								// Set Once Flag.
			laser_hold = 1;						// Clear laser_hold var.
			nobeep_flg = 0;					    // Turn Off Beep.
		}
		if ((Timeout_test() == 0) && Timeout_active()) {
			nobeep_flg = 1;					    // Turn On Beep.
			mode = Main; 	  					// Set Mode to Main.
			once = 0;								// Reset once flag.
		} // End If Test two_min_test Failed
		else if (mode == LOW_BAT) {
			nobeep_flg = 1;					    // Turn On Beep.
			mode = Low_PD;	  				    // We are now in true Low Power Mode..
			once = 0;								// Reset once flag.
		} // End If Test two_min_test Failed
		else {
			key_var = scan_keyboard();			// Scan Keyboard.
			if (key_var == 0){
				nobeep_flg = 1;					    // Turn On Beep.
				mode = Main; 	  					// Set Mode to Main.
				once = 0;								// Reset once flag.
			}
			if (key_var > 0) {
				laser_hold = 0; 			  	    // Only one Keypress is legal.
				nobeep_flg = 0;					    // Turn Off Beep Till mode determined.
				switch (key_var) {
				  case FIVE:
					  TimeScrn();							// Display Sound Config Screen.
					  accurate_delay( 200 );				// Delay 200 msec
					  break;
				  default:
					  mode = Main; 	  					// Set Mode to Main.
					  once = 0;								// Reset once flag.
					  break;
				} // End Switch on key_var

				if (mode != ShowTimeMode) {
					once = 0;							// Reset once flag.
					Timeout_clear();				   // Clear 5 MInute Timer.
				}
				else
					if(Timeout_active())
						Timout_start();					// TimeOut Timer Start.
			} //Endif Key Founr
		} // End If two_min_test active
		break;


//*******************************************************************************
//*
//*   MonitorMode
//*
//*   TODO: MonitorMode
//*******************************************************************************
	case MonitorMode:							// Show Key Entry Screen.
		monPrint("MNTR", "MonitorMode");		// Send Status Message
		if (once == 0) {
			MonitorScrn();							// Display Sound Config Screen.
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
			once = 1;								// Set Once Flag.
			laser_hold = 0;						// Clear laser_hold var.
			nobeep_flg = 1;					    // Turn On Beep.
			beep_3Bp();							// Beep Start Screen
			MonitorTask();						// Slave to monitor
		}
		if ((Timeout_test() == 0) && Timeout_active()) {
			nobeep_flg = 1;					    // Turn On Beep.
			mode = Main; 	  					// Set Mode to Main.
			once = 0;								// Reset once flag.
		} // End If Test two_min_test Failed
		else if (mode == LOW_BAT) {
			nobeep_flg = 1;					    // Turn On Beep.
			mode = Low_PD;	  				    // We are now in true Low Power Mode..
			once = 0;								// Reset once flag.
		} // End If Test two_min_test Failed
		else {
			key_var = scan_keyboard();			// Scan Keyboard.
			if (key_var == 0){
				laser_hold = 1;						// Set laser_hold only if Laser key released.
				nobeep_flg = 1;					    // Turn On Beep.
			}
			if((key_var > 0) && (laser_hold == 1)) {
				laser_hold = 0; 			  	    // Only one Keypress is legal.
				nobeep_flg = 0;					    // Turn Off Beep Till mode determined.
				switch (key_var) {
				  case CANCEL:
					  mode = Main; 	  					// Set Mode to Main.
					  once = 0;								// Reset once flag.
					  break;
				} // End Switch on key_var
				MonitorScrn();							// Display Config Screen.

				if (mode != SerialNumScreen) {
					once = 0;							// Reset once flag.
					Timeout_clear();				   // Clear 5 MInute Timer.
				}
				else
					if(Timeout_active())
						Timout_start();					// TimeOut Timer Start.
			} //Endif Key Founr
		} // End If two_min_test active
		break;

 #if LEASEOP
//*******************************************************************************
//*
//*   KeyScreen
//*
//*	  TODO: KeyScreen
//*******************************************************************************
	case KeyScreen:							// Show Key Entry Screen.
	  if (once == 0) {
#if NEW_LCD
//	    init_lcd2();						    // Initialize the LCD Screen.
#endif
		KeyEntryScrn();							// Display Sound Config Screen.
		if(Timeout_active())
			Timout_start();					// TimeOut Timer Start.
		once = 1;								// Set Once Flag.
		laser_hold = 0;						// Clear laser_hold var.
		beep_3Bp();							// Beep Start Screen
	  }
	  if (((Timeout_test() == 0) && Timeout_active()) ||
			  (mode == LOW_BAT)) {
		  nobeep_flg = 1;					    // Turn On Beep.
		  if (mode == LOW_BAT)
			  mode = Low_PD;	  				    // We are now in true Low Power Mode..
		  else
			  mode = Soft_PD; 	  				// Set Mode to Soft_PD.
		  once = 0;								// Reset once flag.
	  } // End If Test two_min_test Failed
	  else {
		  key_var = scan_keyboard();			// Scan Keyboard.
		  if (key_var == 0){
			  laser_hold = 1;						// Set laser_hold only if Laser key released.
			  nobeep_flg = 1;					    // Turn On Beep.
		  }
		  if((key_var > 0) && (laser_hold == 1)) {
			  laser_hold = 0; 			  	    // Only one Keypress is legal.
			  nobeep_flg = 0;					    // Turn Off Beep Till mode determined.
			  switch (key_var) {
			    case BACK:
			    	Backspace_Char(lease_str, LEASE_STR_LEN);
			    	lease_str[LEASE_STR_LEN-1] = NULL;
			    	break;

			    case ZERO:
			    case ONE:
			    case TWO:
			    case THREE:
			    case FOUR:
			    case FIVE:
			    case SIX:
			    case SEVEN:
			    case EIGHT:
			    case NINE:
			    	char1 = get_numstr(key_var);		// Get New Digit.
			    	shft_str_left(lease_str , LEASE_STR_LEN);		// Shift String Left by one digit.
			    	lease_str[LEASE_STR_LEN-2] = char1[0];
			    	lease_str[LEASE_STR_LEN-1] = NULL;
			    	break;
			    case CANCEL:
			    	nobeep_flg = 1;					    // Turn On Beep.
			    	mode = Soft_PD; 	  					// Set Mode to Soft_PD.
			    	once = 0;								// Reset once flag.
			    	break;
			    case SELECT:
			    	// Verify length is correct....
			    	temp_var4 = strlen(lease_str);
			    	if ( temp_var4 == 12 ) {
			    	//if ( strlen(lease_str) == 12) {
			    		//Find Key index.
			    		temp_var4 = atoi(&lease_str[11]);
			    		// Clear out temp_str
			    		for (x=0; x<12; x++)
			    			temp_str[x] = 0;
			    		// Get serial Number from string.
			    		strncpy( temp_str, lease_str, 8);
			    		temp_var3 = strtoul( temp_str, ptr1, 10);
			    		temp_var3 = temp_var3 - keyu[temp_var4];
			    		// Validate Serial Number matches.
			    		if ( serial_number == temp_var3) {
			    			// Clear out temp_str
	    					for (x=0; x<12; x++)
	    						temp_str[x] = 0;
	    				    // Now extract new Limit.
	    					strncpy(temp_str, lease_str+8, 4);
	    				    opmin_lmt = strtoul( temp_str, ptr1, 10);
	    					opmin_lmt = opmin_lmt - (keyl[temp_var4]*10);
	    					opmin_lmt = opmin_lmt * 100;
	    					// Write New limit to Var and to EEPROM.
	    			        EEPROM_WRITE((int)&eopmin_lmt, opmin_lmt, sizeof(opmin_lmt));	 		 // Write the data to EEPROM.
			    		}
			    	}
//			    	nobeep_flg = 1;					    // Turn On Beep.
			    	mode = Boot_Screen; 	  					// Set Mode to Boot_Screen.
			    	once = 0;								// Reset once flag.
			    	break;

			  } // End Switch on key_var
			  KeyEntryScrn();							// Display Config Screen.

			  if (mode != KeyScreen) {
				  once = 0;							// Reset once flag.
				  Timeout_clear();				   // Clear 5 MInute Timer.
			  }
			  else
					if(Timeout_active())
						Timout_start();					// TimeOut Timer Start.
		  } //Endif Key Founr
	  } // End If two_min_test active
	  break;
#endif

//*******************************************************************************
//*
//*   Special4
//*
//*	  TODO: Special4
//*******************************************************************************
	case Special4:							// Special Sequence From PowerOff to Load Serial Flash....Step 1
	  if (once == 0) {
		  laser_hold = 0;						// Reset Var for next Char.
		  once = 1;								// Set Once Flag.
	  }
	  key_var = scan_keyboard();				// Scan Keyboard.
	  if (five_sec_test() == 0) {
		  nobeep_flg = 1;					    // Turn On Beep.
		  mode = Main; 	  					// Set Mode to Soft_PD.
		  once = 0;								// Reset once flag.
	  }
	  if (key_var == 0)
	  {
		  laser_hold = 1;						// Set laser_hold only if Laser key released.
		  nobeep_flg = 1;					    // Turn On Beep....Key Up.
	  }
	  if((key_var > 0) && (laser_hold == 1)) {
		  if (key_var == TWO) {
//			  force_beep(50);						    // Beep Once for this key.
			  nobeep_flg = 0;					    // Turn Off Beep till Key Up.
			  mode = Special4a;	   					// Set New Mode.
			  once = 0;								// Reset once flag.
		  }
#if LEASEOP
		  else if (key_var == NINE) {
//			  force_beep(50);						    // Beep Once for this key.
			  mode = KeyScreen;	   					// Set New Mode.
			  once = 0;							// Reset once flag.
			  nobeep_flg = 1;					    // Turn On Beep.
			  init_devices();						// Init Device...Some hw not on.
//			  force_beep(50);		 				// Force Beep.
#if GRAPHICS
			  init_lcd2();
#else
			  init_lcd();
#endif
		  }
#endif
		  else {
			  nobeep_flg = 1;					    // Turn On Beep.
			  mode = Main; 	  					// Set Mode to Soft_PD.
			  once = 0;								// Reset once flag.
		  }
	  }
	  break;

//*******************************************************************************
//*
//*   Special4a
//*
//*	  TODO: Special4a
//*******************************************************************************
	case Special4a:							// Special Sequence From PowerOff to Load Serial Flash....Step 2
  	  if (once == 0) {
  		  laser_hold = 0;						// Reset Var for next Char.
  		  once = 1;								// Set Once Flag.
  	  }
  	  key_var = scan_keyboard();				// Scan Keyboard.
  	  if (five_sec_test() == 0) {
  		  nobeep_flg = 1;					    // Turn On Beep.
  		  mode = Main; 	  					// Set Mode to Soft_PD.
  		  once = 0;								// Reset once flag.
  	  }
  	  if (key_var == 0)
	  {
		  laser_hold = 1;						// Set laser_hold only if Laser key released.
		  nobeep_flg = 1;					    // Turn On Beep....Key Up.
	  }
  	  if((key_var > 0) && (laser_hold == 1)) {
  		  if (key_var == NINE) {
//  			  force_beep(50);						    // Beep Once for this key.
			  nobeep_flg = 0;					    // Turn Off Beep till Key Up.
  			  mode = Special9;	   					// Set New Mode.
  			  once = 0;								// Reset once flag.
  		  }
  		  else {
  			  nobeep_flg = 1;					    // Turn On Beep.
  			  mode = Main; 	  					// Set Mode to Soft_PD.
  			  once = 0;								// Reset once flag.
  		  }
  	  }
  	  break;

//*******************************************************************************
//*
//*   Special9
//*
//*	  TODO: Special9
//*******************************************************************************
	case Special9:							// Special Sequence From PowerOff to Load Serial Flash....Step 3
	  if (once == 0) {
		  laser_hold = 0;						// Reset Var for next Char.
		  once = 1;								// Set Once Flag.
	  }
	  key_var = scan_keyboard();				// Scan Keyboard.
	  if (five_sec_test() == 0) {
		  nobeep_flg = 1;					    // Turn On Beep.
		  mode = Main; 	  					// Set Mode to Soft_PD.
		  once = 0;								// Reset once flag.
	  }
	  if (key_var == 0)
	  {
		  laser_hold = 1;						// Set laser_hold only if Laser key released.
		  nobeep_flg = 1;					    // Turn On Beep....Key Up.
	  }
	  if((key_var > 0) && (laser_hold == 1)) {
		  if (key_var == THREE) {
//			  force_beep(50);						    // Beep Once for this key.
			  nobeep_flg = 0;					    // Turn Off Beep till Key Up.
			  mode = Special3;	   					// Set New Mode.
			  once = 0;								// Reset once flag.
		  }
		  else {
			  nobeep_flg = 1;					    // Turn On Beep.
			  mode = Main; 	  					// Set Mode to Soft_PD.
			  once = 0;								// Reset once flag.
		  }
	  }
	  break;

//*******************************************************************************
//*
//*   Special3
//*
//*	  TODO: Special3
//*******************************************************************************
	case Special3:							// Special Sequence From PowerOff to Load Serial Flash....Step 4
	  if (once == 0) {
		  laser_hold = 0;						// Reset Var for next Char.
		  once = 1;								// Set Once Flag.
	  }
	  key_var = scan_keyboard();				// Scan Keyboard.
	  if (five_sec_test() == 0) {
		  nobeep_flg = 1;					    // Turn On Beep.
		  mode = Main; 	  					// Set Mode to Soft_PD.
		  once = 0;								// Reset once flag.
	  }
	  if (key_var == 0)
	  {
		  laser_hold = 1;						// Set laser_hold only if Laser key released.
		  nobeep_flg = 1;					    // Turn On Beep....Key Up.
	  }
	  if((key_var > 0) && (laser_hold == 1)) {
		  if (key_var == LASER) {
//			  force_beep(50);						    // Beep Once for this key.
			  nobeep_flg = 0;					    // Turn Off Beep till Key Up.
			  mode = SpecialSelect;	   					// Set New Mode.
			  once = 0;								// Reset once flag.
		  }
		  else if (key_var == SELECT) {
//			  force_beep(50);						    // Beep Once for this key.
			  nobeep_flg = 0;					    // Turn Off Beep till Key Up.
			  mode = SerialNumScreen;	   					// Set New Mode.
			  once = 0;								// Reset once flag.
		  }
		  else if (key_var == POWER) {
//			  force_beep(50);						    // Beep Once for this key.
			  nobeep_flg = 0;					    // Turn Off Beep till Key Up.
			  mode = PBFEntryScreen;	   					// Set New Mode.
			  once = 0;								// Reset once flag.
		  }
		  else if (key_var == CANCEL) {
//			  force_beep(50);						// Beep Once for this key.
			  nobeep_flg = 0;					    // Turn Off Beep till Key Up.
			  mode = DateEntryScreen;	   			// Set New Mode.
			  once = 0;								// Reset once flag.
		  }
		  else if (key_var == DELETE) {
//			  force_beep(50);						// Beep Once for this key.
			  nobeep_flg = 0;					    // Turn Off Beep till Key Up.
			  mode = TimeEntryScreen;	   			// Set New Mode.
			  once = 0;								// Reset once flag.
		  }
		  else {
			  nobeep_flg = 1;					    // Turn On Beep.
			  mode = Main; 	  					// Set Mode to Soft_PD.
			  once = 0;								// Reset once flag.
		  }
	  }
	  break;

	  //*******************************************************************************
	  //*
	  //*   SpecialSelect
	  //*
	  //*	  TODO: SpecialSelect
	  //*******************************************************************************
	  	case SpecialSelect:							// Special Sequence From PowerOff to Load Serial Flash....Step 4
	  	  if (once == 0) {
	  		  laser_hold = 0;						// Reset Var for next Char.
	  		  once = 1;								// Set Once Flag.
	  	  }
	  	  key_var = scan_keyboard();				// Scan Keyboard.
	  	  if (five_sec_test() == 0) {
	  		  nobeep_flg = 1;					    // Turn On Beep.
	  		  mode = Main; 	  					// Set Mode to Soft_PD.
	  		  once = 0;								// Reset once flag.
	  	  }
	  	  if (key_var == 0)
		  {
			  laser_hold = 1;						// Set laser_hold only if Laser key released.
			  nobeep_flg = 1;					    // Turn On Beep....Key Up.
		  }
	  	  if((key_var > 0) && (laser_hold == 1)) {
	  		  if (key_var == SELECT)
	  		  {
//	  			  force_beep(50);						    // Beep Once for this key.
				  nobeep_flg = 0;					    // Turn Off Beep till Key Up.
	  			  mode = MonitorMode;	   					// Set New Mode.
	  			  once = 0;								// Reset once flag.
	  		  }
	  		  else {
	  			  nobeep_flg = 1;					    // Turn On Beep.
	  			  mode = Main; 	  					// Set Mode to Soft_PD.
	  			  once = 0;								// Reset once flag.
	  		  }
	  	  }
	  	  break;

//*******************************************************************************
//*
//*   ProgramMode
//*
//*	  TODO: ProgramMode
//*******************************************************************************
	case ProgramMode:							// Special Sequence From PowerOff to Load Serial Flash....FINAL STEP
	  if (once == 0) {
		  laser_hold = 0;						// Reset Var for next Char.
		  once = 1;								// Set Once Flag.
		  init_devices();						// Power-up Vdd for Programming.
//		  spi_init();  						 	// Initialize SPI Interface.
		  five_sec_clear();					    // Clear 5 Second Timer.
		  nobeep_flg = 1;					    // Turn On Beep.
		  beep_ArpUp();						    // Indicate Special Mode via Sound.
		  long_delay(1);						// Delay 1 Second to allow FPGA to bootup.
		  laser_off();							// Turn off Lasers.
#if Vers1_2HW
#else
		  // Asser P_EN and then wait 100msec to allow VDD power supply to stabilize.
	      //        PORTE |= (1<<PORTE5); 								// Assert P_EN(Turn on U6(3.3V) and U9(1.8V).
		  accurate_delay(VDD_PWRDELAY);
#endif
		  // Power Down SPI and Tri State Port B Pins 0-3.
//	    		  SPCR = (0<<SPE);
//	    		  PORTB = 0x00;
//	    		  DDRB = 0x00;
		  nobeep_flg = 0;					    // Turn Off Beep.
	  }
	  key_var = 0;
	  while (key_var != ONE)
	  {
		  key_var = scan_keyboard();				// Scan Keyboard.
		  if (key_var == 0)
			  laser_hold = 1;						// Set laser_hold only if Laser key released.
	  }
	  if((key_var > 0) && (laser_hold == 1)) {
		  if (key_var == ONE) {
			  nobeep_flg = 1;					    // Turn On Beep.
			  init_devices();						// Power-up Vdd for Programming.
//			  spi_init();  						 	// Initialize SPI Interface.
			  beep_ArpDn();	   			   	   	// Perform ArpDown for this mode.
			  nobeep_flg = 1;					    // Turn On Beep.
			  mode = Soft_PD; 	  					// Set Mode to Soft_PD.
			  once = 0;								// Reset once flag.
		  }
	  }
	  break;

#if MARKIVE
//*******************************************************************************
//*
//*   SndScreen
//*
//*	  TODO: SndScreen
//*******************************************************************************
	case SndScreen:							// Show Sound Configuration Screen.
	  if (once == 0) {
#if NEW_LCD
//		  init_lcd2();						    // Initialize the LCD Screen.
#endif
		  snd_screen();							// Display Sound Config Screen.
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		  once = 1;								// Set Once Flag.
		  laser_hold = 0;						// Clear laser_hold var.
	  }
	  if (((Timeout_test() == 0) && Timeout_active()) ||
			  (mode == LOW_BAT)) {
		  nobeep_flg = 1;					    // Turn On Beep.
		  if (mode == LOW_BAT)
			  mode = Low_PD;	  				    // We are now in true Low Power Mode..
		  else
			  mode = Soft_PD; 	  				// Set Mode to Soft_PD.
		  once = 0;								// Reset once flag.
	  } // End If Test two_min_test Failed
	  else {
		  key_var = scan_keyboard();			// Scan Keyboard.
		  if (key_var == 0){
			  laser_hold = 1;						// Set laser_hold only if Laser key released.
			  nobeep_flg = 1;					    // Turn On Beep.
		  }
		  if((key_var > 0) && (laser_hold == 1)) {
			  laser_hold = 0; 			  	    // Only one Keypress is legal.
			  nobeep_flg = 0;					    // Turn Off Beep Till mode determined.
			  switch (key_var) {
			    case LASER:
					if(Timeout_active())
						Timout_start();					// TimeOut Timer Start.
			    	SndCnfig++;						// Increment Sound Var.
			    	if (SndCnfig>=MAX_SNDS)
			    		SndCnfig = 0;		  			// If past limit, reset to zero.
			    	snd_screen();							// Display Sound Config Screen.
			    	break;

			    case FOUR:
			    	nobeep_flg = 1;					    // Turn On Beep.
			    	mode = Main; 	  					// Set Mode to Main.
			    	once = 0;								// Reset once flag.
			    	break;

			  } // End Switch on key_var
			  if (mode != SndScreen) {
				  once = 0;							// Reset once flag.
				  Timeout_clear();				   // Clear 5 MInute Timer.
			  }
			  else
					if(Timeout_active())
						Timout_start();					// TimeOut Timer Start.
		  } //
	  } // End If two_min_test active
	  break;

//*******************************************************************************
//*
//*   DB_Screen
//*
//*	  TODO: DB_Screen
//*******************************************************************************
	case DB_Screen:							// Show Database Screen and wait for release.
	  if (once == 0) {
		  nobeep_flg = 0;					    // Turn Off Beep.
		  laser_hold = 0;						// Reset Var for next Char.
		  once = 1;								// Set Once Flag.
		  db_screen();
	  }
	  key_var = scan_keyboard();				// Scan Keyboard.
	  if (key_var == 0) {
		  laser_hold = 1;						// Set laser_hold only if Laser key released.
		  nobeep_flg = 1;					    // Turn On Beep.
		  mode = Main; 	  					// Set Mode to Soft_PD.
		  once = 0;								// Reset once flag.
	  }
	  break;
#endif


//*******************************************************************************
//*
//*   Locked_CONTINUE
//*
//*	  TODO: Locked_CONTINUE
//*******************************************************************************
	  case Locked_CONTINUE:						// Locked_CONTINUE.
		printf2("*** Locked_CONTINUE ***\n");
		monPrint("MNTR", "Locked");				// Send Status Message
		// Clear LCD Screen.
		clear_screen();

		// Turn Off LCD Screen.
		turnoff_lcd();
		key_var = scan_keyboard();				// Scan Keyboard.
		if (key_var == POWER) {
	  	  force_beep(50);						// Beep Once for this key.
		  mode = Locked_1;	   					// Set New Mode.
		  five_sec_start();						// Activate 5 Second Timer.
		  once = 0;								// Reset once flag.
		}
	    if (five_sec_test() == 0) {
		  mode = Locked;  				        // Set Mode.
		  once = 0;								// Reset once flag.
		}
	    break;

//*******************************************************************************
//*
//*   Locked
//*
//*	  TODO: Locked
//*******************************************************************************
	  case Locked:								// Locked.
		printf2("*** Locked ***\n");
		monPrint("MNTR", "Locked");				// Send Status Message
	    beep_3low();							// Indicate Locked Mode.
		nobeep_flg = 0;					    	// Turn Off Beep.
    	save_vars();  	 	  					    // Save Updated Variables.
	    sleep_code();							// Place Hardware into Sleep Mode.
		key_var = scan_keyboard();				// Scan Keyboard.
		if (key_var == POWER) {
	  	  force_beep(50);						// Beep Once for this key.
		  mode = Locked_1;	   					// Set New Mode.
		  five_sec_start();						// Activate 5 Second Timer.
		  once = 0;								// Reset once flag.
		}
	    if (five_sec_test() == 0) {
		  mode = Locked;  				        // Set Mode.
		  once = 0;								// Reset once flag.
		}
	    break;

//*******************************************************************************
//*
//*   Locked_1
//*
//*	  TODO: Locked_1
//*******************************************************************************
	  case Locked_1:							// Locked_1.
	    if (once == 0) {
		  printf2("*** Locked_1 ***\n");
		  monPrint("MNTR", "Locked");				// Send Status Message
		  laser_hold = 0;						// Reset Var for next Char.
		  once = 1;								// Set Once Flag.
		}
	    else
		  printf2(".");
		key_var = scan_keyboard();				// Scan Keyboard.
	    if (five_sec_test() == 0) {
		  mode = Locked;  				        // Set Mode.
		  once = 0;								// Reset once flag.
		}

		if (key_var == 0)
		  laser_hold = 1;						// Set laser_hold only if Laser key released.
		if((key_var > 0) && (laser_hold == 1)) {
		  if (key_var == SELECT) {
			force_beep(50);						    // Beep Once for this key.
		    mode = Locked_2;	   					// Set New Mode.
		    once = 0;								// Reset once flag.
		  }
		  else {
		    mode = Locked;  				        // Set Mode.
		    once = 0;								// Reset once flag.
		  }
		}
	    break;

//*******************************************************************************
//*
//*   Locked_2
//*
//*	  TODO: Locked_2
//*******************************************************************************
	  case Locked_2:							// Locked_2.
	    if (once == 0) {
		  printf2("*** Locked_2 ***\n");
		  monPrint("MNTR", "Locked");				// Send Status Message
		  laser_hold = 0;						// Reset Var for next Char.
		  once = 1;								// Set Once Flag.
		}
	    else
		  printf2(".");
		key_var = scan_keyboard();				// Scan Keyboard.
	    if (five_sec_test() == 0) {
		  mode = Locked;  				        // Set Mode.
		  once = 0;								// Reset once flag.
		}
		if (key_var == 0)
		  laser_hold = 1;						// Set laser_hold only if Laser key released.
		if((key_var > 0) && (laser_hold == 1)) {
		  if (key_var == LASER) {
			force_beep(50);						// Beep Once for this key.
			nobeep_flg = 1;					   	// Turn On Beep.
		    mode = Main; 	   					// Set New Mode.
 		    init_devices();						// Init Device...Some hw not on.
		    once = 0;							// Reset once flag.
  		    strcpy(Bat_Lvl, Battery_Test());
			#if GRAPHICS
			init_lcd2();						// Initialize the LCD Screen.
			#else
			init_lcd();							// Initialize the LCD Screen.
			#endif
			beep_ArpUp();						// Beep Power-up Indication.
			five_sec_clear();					// Clear 5 Second Timer.
		  }
		  else {
		    mode = Locked;  				        // Set Mode.
		    once = 0;								// Reset once flag.
		  }
		}
	    break;

//*******************************************************************************
//*
//*   Main
//*
//*	  TODO: Main
//*******************************************************************************
	  case Main:								// Main.
	    //remain_screen();						// Display Main Screen.
		// long_delay(2);
        accurate_delay(SCRNRF);					// Delay for screen refresh
	    if (once == 0) {
		  printf2("*** Main ***\n");
		  for (x=0;x<20;x++)
			  tempstrTemp[x]=0x00;
		  str_chg_long3(tempstrTemp, 9, serial_number);
		  getTime(&hour, &minute, &second);
		  getDate(&month, &day, &year);
		  monPrint("MNTR", "Main");					// Send Status Message
		  //monPrint("BAT_LVL", Battery_Level());		// Send Status Message
		  //monPrint("SERIAL_NUM", tempstrTemp);			// Send Status Message
		  for (x=0;x<20;x++)
			  tempstrTemp1[x]=0x00;
		  sprintf(tempstrTemp1, "%02d:%02d:%02d", hour, minute, second);
		  //monPrint("TIME", tempstrTemp);			// Send Status Message
		  for (x=0;x<20;x++)
			  tempstrTemp2[x]=0x00;
		  sprintf(tempstrTemp2, "%02d/%02d/%04d", month, day, year);
		  sprintf(temp_String,"%s|%s|%s|%s", Battery_Level(), tempstrTemp, tempstrTemp1, tempstrTemp2);
		  //monPrint("DATE", tempstrTemp);			// Send Status Message
		  monPrint("STATUS", temp_String);			// Send Status Message
		  data1 = read_entry(prog_num);			// Read Current Mode Entry.
		  Ptr1 = data1->string1;
		  while (*Ptr1 == 0x20)
			  Ptr1++;
		  // Print out Program String.
	      sprintf(Prog_str,"%d",prog_num);
	      // Clean Out temp string before using it.
		  for (x=0;x<80;x++)
			  temp_String[x]=0x00;
		  if ((prog_num > CUSTOM4_END) && (prog_num <= USER_REND)) {
			  sprintf(temp_String, "%s/CUSTOM", Prog_str, Ptr1);
			  monPrint("PROG", temp_String);		// temp_String
			  monPrint("LASER1", lser1_strng);			// Send Status Message
			  monPrint("LASER2", lser2_strng);			// Send Status Message
			  monPrint("LASER3", lser3_strng);			// Send Status Message
			  monPrint("LASER4", lser4_strng);			// Send Status Message
		  }
		  else
		  {
			  sprintf(temp_String, "%s/%s", Prog_str, Ptr1);
			  monPrint("PROG", temp_String);		// temp_String
		  }
		  remain_screen();						// Display Main Screen.
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		  once = 1;								// Set Once Flag.
		  Booted = 1;							// We are now Booted.
		  laser_hold = 0;						// Clear laser_hold var.
		}
	    else
		  printf2(".");
	    if (((Timeout_test() == 0) && Timeout_active())  || (mode == LOW_BAT)) {
	    	nobeep_flg = 1;					    // Turn On Beep.
		    if (mode != LOW_BAT)
				mode = Soft_PD; 	  				// Set Mode to Soft_PD.
	    	once = 0;								// Reset once flag.
		} // End If Test two_min_test Failed
		else {
		  key_var = scan_keyboard();			// Scan Keyboard.
		  if (key_var == 0)
		  {
		    laser_hold = 1;						// Set laser_hold only if Laser key released.
			nobeep_flg = 1;					    // Turn On Beep.
		    accurate_delay(DELAY_KEY);			// Found a key. Delay a little to foe key glitch.
		  }
		  if((key_var > 0) && (laser_hold == 1)) {
			laser_hold = 0; 			  	    // Only one Keypress is legal.
			nobeep_flg = 0;					    // Turn Off Beep Till mode determined.
		    switch (key_var) {
			  case TIME:
				monPrint_Key(key_var);		// Display Key
				//nobeep_flg = 1;					    // Turn On Beep.
				mode = Timed_Laser_Armed;				// Set New Mode.
			    break;

			  case LASER:
				monPrint_Key(key_var);		// Display Key
				mode = Laser_On_Armed;				// Set New Mode.
			    break;

			  case SELECT:
				monPrint_Key(key_var);		// Display Key
				mode = Program;					// Set New Mode.
			    break;

			  case FOUR:
				monPrint_Key(key_var);		// Display Key
				mode = Special4;					// Set New Mode.
				five_sec_clear();					// Clear 5 Second Timer.
				five_sec_start();					// Start 5 Second Timeout.
			    break;

			  case FIVE:
				monPrint_Key(key_var);		// Display Key
				mode = ShowTimeMode;				// Set New Mode.
				five_sec_clear();					// Clear 5 Second Timer.
				five_sec_start();					// Start 5 Second Timeout.
			    break;

			  case POWER:
				monPrint_Key(key_var);		// Display Key
				mode = Test1;					// Set New Mode.
			    nobeep_flg = 0;					    // Turn On Beep.
			    break;

			  case OFF:
				monPrint_Key(key_var);		// Display Key
		        mode = Soft_PD; 	  					// Set Mode to Soft_PD.
		        once = 0;								// Reset once flag.
			    nobeep_flg = 1;					    // Turn On Beep.
			    break;
			  case ONE:
				monPrint_Key(key_var);		// Display Key
		        mode = Soft_PD; 	  					// Set Mode to Soft_PD.
		        once = 0;								// Reset once flag.
			    nobeep_flg = 1;					    // Turn On Beep.
			    break;
//			  case ONE:
			  case TWO:
			  case THREE:
//			  case ONE:
//			  case ONE:
			  case SIX:
			  case SEVEN:
			  case EIGHT:
			  case NINE:
			  case ZERO:
			  case PERIOD:
			  case BACK:
			  case UP:
			  case DOWN:
			  case LEFT:
			  case RIGHT:
//			  case LASER:
			  case CANCEL:
//			  case SELECT:
			  case DELETE:
//			  case TIME:
			  case LIGHT:
//			  case POWER:
//			  case OFF:
			  case START:
				monPrint_Key(key_var);		// Display Key
			    break;
		    } // End Switch on key_var
			if (mode != Main) {
		      once = 0;							// Reset once flag.
			  Timeout_clear();				   // Clear 5 MInute Timer.
			}
			else
				if(Timeout_active())
					Timout_start();					// TimeOut Timer Start.
		  } //Endif Key Founr
		} // End If two_min_test active
	    break;

//*******************************************************************************
//*
//*   Timed_Laser_Armed
//*
//*	  TODO: Timed_Laser_Armed
//*******************************************************************************
	  case Timed_Laser_Armed:							// Timed_Test.
	    if (once == 0) {
		  printf2("*** Timed_Laser_Armed ***\n");
		  monPrint("MNTR", "Timed_Laser_Armed");			// Send Factory Status Message
	      sprintf(Prog_str,"%d",prog_num);
	      data1 = read_entry(prog_num);			// Read Current Mode Entry.
	      Ptr1 = data1->string1;
	      while (*Ptr1 == 0x20)
	      	Ptr1++;
	      // Clean Out temp string before using it.
	      for (x=0;x<80;x++)
	    	  temp_String[x]=0x00;
		  if ((prog_num > CUSTOM4_END) && (prog_num <= USER_REND)) {
			  sprintf(temp_String, "%s/CUSTOM", Prog_str, Ptr1);
			  monPrint("PROG", temp_String);		// temp_String
			  monPrint("LASER1", lser1_strng);			// Send Status Message
			  monPrint("LASER2", lser2_strng);			// Send Status Message
			  monPrint("LASER3", lser3_strng);			// Send Status Message
			  monPrint("LASER4", lser4_strng);			// Send Status Message
		  }
		  else
		  {
			  sprintf(temp_String, "%s/%s", Prog_str, Ptr1);
			  monPrint("PROG", temp_String);		// temp_String
		  }
	      //monPrint("PROG_NUM", Prog_str);		// Send Status Message
	      //monPrint("PROG_STR", Ptr1);		// Send Status Message
		  TL_Armed_screen();					// Print Timed Laser Armed Screen
		  beep_3Bp();							// Beep Three Times and wait for start.
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		  once = 1;								// Set Once Flag.
		}
	    else
		  printf2(".");
	    if (((Timeout_test() == 0) && Timeout_active()) ||
	    		(mode == LOW_BAT))
	    {
	    	nobeep_flg = 1;					    // Turn On Beep.
			Timeout_clear();					// Clear 2 Minute Timer.
	    	if (mode == LOW_BAT)
	    		mode = Low_PD;	  				    // We are now in true Low Power Mode..
	    	else
	    		mode = Soft_PD; 	  				// Set Mode to Soft_PD.
			once = 0;								// Reset once flag.
		}
	    else
	    {
			key_var = scan_keyboard();				// Scan Keyboard.
			if (key_var == 0){
				laser_hold = 1;						// Set laser_hold only if Laser key released.
				nobeep_flg = 1;					    // Turn On Beep.
			}
			if ((key_var > 0) && (laser_hold == 1))
			{
		      laser_hold = 0; 			  	    // Only one Keypress is legal.
			  nobeep_flg = 0;					    // Turn Off Beep Till mode determined.
			  monPrint_Key(key_var);		// Display Key
			  if (key_var == START)
			  {
				mode = Timed_Laser_Armed2;			// Set New Mode.
				once = 0;							// Reset once flag.
			  }
			  else if (key_var == CANCEL)
			  {
				mode = Main;						// Set New Mode.
				once = 0;							// Reset once flag.
				Timeout_clear();					// Clear 2 Minute Timer.
			  }
			}
	    }
	    break;

//*******************************************************************************
//*
//*   Timed_Laser_Armed2
//*
//*	  TODO: Timed_Laser_Armed2
//*******************************************************************************
	  case Timed_Laser_Armed2:							// Timed_Test.
	    if (once == 0) {
		  printf2("*** Timed_Laser_Armed2 ***\n");
		  once = 1;								// Set Once Flag.
		}
	    else
		  printf2(".");
	    if (((Timeout_test() == 0) && Timeout_active()) ||
	    		(mode == LOW_BAT))
	    {
	    	nobeep_flg = 1;					    // Turn On Beep.
			Timeout_clear();					// Clear 2 Minute Timer.
	    	if (mode == LOW_BAT)
	    		mode = Low_PD;	  				    // We are now in true Low Power Mode..
	    	else
	    		mode = Soft_PD; 	  				// Set Mode to Soft_PD.
			once = 0;								// Reset once flag.
		}
	    else
	    {
			key_var = scan_keyboard();				// Scan Keyboard.
			if (key_var == 0){
				// Key release
				mode = Timed_Laser;					// Set New Mode.
				once = 0;							// Reset once flag.
				Timeout_clear();					// Clear 2 Minute Timer.
				nobeep_flg = 1;					    // Turn On Beep.
			}
	    }
	    break;

//*******************************************************************************
//*
//*   Low_PD
//*
//*	  TODO: Low_PD
//*******************************************************************************
	  case Low_PD:								// Soft_PD.
		printf2("*** Low_PD ***\n");
		monPrint("MNTR", "BAT_LOW");				// Send Status Message
		nobeep_flg = 0;					    	// Turn Off Beep.
	    sleep_code();							// Place Hardware into Sleep Mode.
  		restore_vars();		   			   	 		// Restore Key Variables.
		mode = Low_PD;							// Restore mode back to Low_PD.
		key_var = scan_keyboard();				// Scan Keyboard.
//  		strcpy(Bat_Lvl, Battery_Test());
  		if (!(tst_bat())) {
//        if (mode == LOW_BAT) {					// If still Low Power Mode...Then Power Down.
		  mode = Low_PD;
		}
		else { 	 			 					// Else This is a normal Wakeup...Continue.
		  if (key_var == LASER) {
		    mode = Laser_On;					// Set New Mode.
 		    init_devices();						// Init Device...Some hw not on.
      		#if GRAPHICS
      		init_lcd2();
      		#else
      		init_lcd();
      		#endif
      		monPrint("MNTR", "PU_LaserOn");				// Send Status Message
		    force_beep(50);		 				// Force Beep.
		    nobeep_flg = 1;					    // Turn On Beep.
		    once = 0;							// Reset once flag.
		  }
		  else if (key_var == LIGHT) {
		    mode = Boot_Screen;					// Set New Mode.
 		    init_devices();						// Init Device...Some hw not on.
      		#if GRAPHICS
      		init_lcd2();
      		#else
      		init_lcd();
      		#endif
		    force_beep(50);		 				// Force Beep.
		    nobeep_flg = 1;					    // Turn On Beep.
		    once = 0;							// Reset once flag.
		  }
		  else if (key_var == POWER) {
		    mode = Test1;						// Set New Mode.
 		    init_devices();						// Init Device...Some hw not on.
      		#if GRAPHICS
      		init_lcd2();
      		#else
      		init_lcd();
      		#endif
		    force_beep(50);		 				// Force Beep.
		    nobeep_flg = 1;					    // Turn On Beep.
		    once = 0;							// Reset once flag.
		  }
		}
	    break;

//*******************************************************************************
//*
//*   Soft_PD
//*
//*	  TODO: Soft_PD
//*******************************************************************************
	  case Soft_PD:								// Soft_PD.
		printf2("*** Soft_PD ***\n");
		monPrint("MNTR", "POWER_DOWN");				// Send Status Message
		nobeep_flg = 0;					    	// Turn Off Beep.
    	save_vars();  	 	  					    // Save Updated Variables.
	    sleep_code();							// Place Hardware into Sleep Mode.
        once = 0;								// Need to reset var to allow for normal screen operation from main().
		if (mode != Low_PD) {					// Did Mode change due to sleep?
  		  restore_vars();		   			   	 		// Restore Key Variables.
		  key_var = scan_keyboard();				// Scan Keyboard.
//		  remain_screen();						// Display Main Screen.
		  if (key_var == LASER) {
		    force_beep(50);		 				// Force Beep.
		    nobeep_flg = 1;					    // Turn On Beep.
		    mode = Laser_On;					// Set New Mode.
 		    init_devices();						// Init Device...Some hw not on.
      		#if GRAPHICS
      		init_lcd2();
      		#else
      		init_lcd();
      		#endif
      		monPrint("MNTR", "PU_LaserOn");				// Send Status Message
      		once = 0;							// Reset once flag.
//  		    strcpy(Bat_Lvl, Battery_Test());
		  }
		  else if (key_var == LIGHT) {
			force_beep(50);		 				// Force Beep.
			nobeep_flg = 1;					    // Turn On Beep.
		    mode = Boot_Screen;					// Set New Mode.
 		    init_devices();						// Init Device...Some hw not on.
      		#if GRAPHICS
      		init_lcd2();
      		#else
      		init_lcd();
      		#endif
		    once = 0;							// Reset once flag.
//  		    strcpy(Bat_Lvl, Battery_Test());
		  }
		  else if (key_var == POWER) {
			force_beep(50);		 				// Force Beep.
			nobeep_flg = 1;					    // Turn On Beep.
		    mode = Test1;						// Set New Mode.
 		    init_devices();						// Init Device...Some hw not on.
      		#if GRAPHICS
      		init_lcd2();
      		#else
      		init_lcd();
      		#endif
		    once = 0;							// Reset once flag.
//  		    strcpy(Bat_Lvl, Battery_Test());
		  }
		}
		else {
  		  restore_vars();		   			   	 		// Restore Key Variables.
		  mode = Low_PD;								// Force Low Power Mode.
		}
	    break;

//*******************************************************************************
//*
//*   Soft_PD_CONTINUE
//*   Locked_CONTINUE
//*
//*	  TODO: Locked_CONTINUE
//*******************************************************************************
	  case Soft_PD_CONTINUE:					// Soft_PD_CONTINUE.
		  printf2("*** Soft_PD_CONTINUE ***\n");
		  once = 0;								// Need to reset var to allow for normal screen operation from main().
		  if (mode != Low_PD) {					// Did Mode change due to sleep?
			  restore_vars();		   			   	 		// Restore Key Variables.
//			  force_beep(50);		 				// Force Beep.
			  nobeep_flg = 1;					    // Turn On Beep.
			  mode = Boot_Screen;					// Set New Mode.
			  init_devices();						// Init Device...Some hw not on.
#if GRAPHICS
			  init_lcd2();
#else
			  init_lcd();
#endif
			  once = 0;							// Reset once flag.
		  }
		  else {
			  restore_vars();		   			   	 		// Restore Key Variables.
			  mode = Low_PD;								// Force Low Power Mode.
		  }
		  break;

//*******************************************************************************
//*
//*   Test1
//*
//*	  TODO: Test1
//*******************************************************************************
	  case Test1:								// Test1.
	    if (once == 0) {
		  printf2("*** Test1 ***\n");
		  five_sec_start();						// Five Second Timer Start.
		  once = 1;								// Set Once Flag.
		}
	    else
	    	printf2(".");
		key_var = scan_keyboard();				// Scan Keyboard.
        if (key_var == 0) {
  		  nobeep_flg = 1;					    // Mode Found. Turn On Beep.
          mode = Five_Min_Armed;					// Set New Mode.
          once = 0;								// Reset once flag.
        }
		else {
		  if (key_var != POWER) {
			nobeep_flg = 1;					    // Mode Found. Turn On Beep.
		    mode = Five_Min_Armed;					// Set New Mode.
		    once = 0;								// Reset once flag.
		  }
		  else if (five_sec_test() == 0) {
			nobeep_flg = 1;					    // Mode Found. Turn On Beep.
		    mode = Locked;							// Set New Mode.
		    once = 0;								// Reset once flag.
		  }
		}
	    break;

//*******************************************************************************
//*
//*   Five_Min_Armed
//*
//*	  TODO: Five_Min_Armed
//*******************************************************************************
	  case Five_Min_Armed:							// Five Min Armed Test.
		  if (once == 0) {
			  printf2("*** Five_Min_Armed ***\n");
			  monPrint("MNTR", "Five_Min_Armed");			// Send Factory Status Message
		      sprintf(Prog_str,"%d",prog_num);
		      data1 = read_entry(prog_num);			// Read Current Mode Entry.
		      Ptr1 = data1->string1;
		      while (*Ptr1 == 0x20)
		       	Ptr1++;
		      // Clean Out temp string before using it.
		      for (x=0;x<80;x++)
		    	  temp_String[x]=0x00;
			  if ((prog_num > CUSTOM4_END) && (prog_num <= USER_REND)) {
				  sprintf(temp_String, "%s/CUSTOM", Prog_str, Ptr1);
				  monPrint("PROG", temp_String);		// temp_String
				  monPrint("LASER1", lser1_strng);			// Send Status Message
				  monPrint("LASER2", lser2_strng);			// Send Status Message
				  monPrint("LASER3", lser3_strng);			// Send Status Message
				  monPrint("LASER4", lser4_strng);			// Send Status Message
			  }
			  else
			  {
				  sprintf(temp_String, "%s/%s", Prog_str, Ptr1);
				  monPrint("PROG", temp_String);		// temp_String
			  }
		      //monPrint("PROG_NUM", Prog_str);		// Send Status Message
		      //monPrint("PROG_STR", Ptr1);		// Send Status Message
			  Laser_Armed_screen();					// Print Timed Laser Armed Screen
			  beep_3Bp();							// Beep Three Times and wait for start.
				if(Timeout_active())
					Timout_start();					// TimeOut Timer Start.
			  once = 1;								// Set Once Flag.
		  }
		  else
			  printf2(".");
		  if (((Timeout_test() == 0) && Timeout_active()) ||
				  (mode == LOW_BAT))
		  {
			  nobeep_flg = 1;					    // Turn On Beep.
			  Timeout_clear();					// Clear 2 Minute Timer.
			  if (mode == LOW_BAT)
				  mode = Low_PD;	  				    // We are now in true Low Power Mode..
			  else
				  mode = Soft_PD; 	  				// Set Mode to Soft_PD.
			  once = 0;								// Reset once flag.
		  }
		  else
		  {
			  key_var = scan_keyboard();				// Scan Keyboard.
			  if (key_var == 0){
				  laser_hold = 1;						// Set laser_hold only if Laser key released.
				  nobeep_flg = 1;					    // Turn On Beep.
			  }
			  if ((key_var > 0) && (laser_hold == 1))
			  {
				  laser_hold = 0; 			  	    // Only one Keypress is legal.
				  nobeep_flg = 0;					    // Turn Off Beep Till mode determined.
				  monPrint_Key(key_var);		// Display Key
				  if (key_var == START)
				  {
					  mode = Five_Min_Armed2;			// Set New Mode.
					  once = 0;							// Reset once flag.
				  }
				  else if (key_var == CANCEL)
				  {
					  mode = Main;						// Set New Mode.
					  once = 0;							// Reset once flag.
					  Timeout_clear();					// Clear 2 Minute Timer.
				  }
			  }
		  }
		  break;

//*******************************************************************************
//*
//*   Five_Min_Armed2
//*
//*	  TODO: Five_Min_Armed2
//*******************************************************************************
	  case Five_Min_Armed2:							// Five Min Armed Test.
		  if (once == 0) {
			  printf2("*** Five_Min_Armed2 ***\n");
			  once = 1;								// Set Once Flag.
		  }
		  else
			  printf2(".");
		  if (((Timeout_test() == 0) && Timeout_active()) ||
				  (mode == LOW_BAT))
		  {
			  nobeep_flg = 1;					    // Turn On Beep.
			  Timeout_clear();					// Clear 2 Minute Timer.
			  if (mode == LOW_BAT)
				  mode = Low_PD;	  				    // We are now in true Low Power Mode..
			  else
				  mode = Soft_PD; 	  				// Set Mode to Soft_PD.
			  once = 0;								// Reset once flag.
		  }
		  else
		  {
			  key_var = scan_keyboard();				// Scan Keyboard.
			  if (key_var == 0){
				  // Key release
				  mode = Five_Min_Mode;					// Set New Mode.
				  once = 0;							// Reset once flag.
				  Timeout_clear();					// Clear 2 Minute Timer.
				  nobeep_flg = 1;					    // Turn On Beep.
			  }
		  }
		  break;






//*******************************************************************************
//*
//*   Laser_On_Armed
//*
//*	  TODO: Laser_On_Armed
//*******************************************************************************
	  case Laser_On_Armed:							// Laser_On_Armed Test.
		  if (once == 0) {
			  printf2("*** Laser_On_Armed ***\n");
			  monPrint("MNTR", "Laser_On_Armed");			// Send Factory Status Message
		      sprintf(Prog_str,"%d",prog_num);
		      data1 = read_entry(prog_num);			// Read Current Mode Entry.
		      Ptr1 = data1->string1;
		      while (*Ptr1 == 0x20)
		       	Ptr1++;
		      // Clean Out temp string before using it.
		      for (x=0;x<80;x++)
		    	  temp_String[x]=0x00;
			  if ((prog_num > CUSTOM4_END) && (prog_num <= USER_REND)) {
				  sprintf(temp_String, "%s/CUSTOM", Prog_str, Ptr1);
				  monPrint("PROG", temp_String);		// temp_String
				  monPrint("LASER1", lser1_strng);			// Send Status Message
				  monPrint("LASER2", lser2_strng);			// Send Status Message
				  monPrint("LASER3", lser3_strng);			// Send Status Message
				  monPrint("LASER4", lser4_strng);			// Send Status Message
			  }
			  else
			  {
				  sprintf(temp_String, "%s/%s", Prog_str, Ptr1);
				  monPrint("PROG", temp_String);		// temp_String
			  }
		      //monPrint("PROG_NUM", Prog_str);		// Send Status Message
		      //monPrint("PROG_STR", Ptr1);		// Send Status Message
		      Pulse_Armed_screen();					// Print Timed Laser Armed Screen
			  accurate_delay(200);					// Delay 200msec to allow Initial Beep to complete
			  nobeep_flg = 1;					    // Turn On Beep.
			  beep_3Bp();							// Beep Three Times and wait for start.
			  nobeep_flg = 0;					    // Turn Off Beep.
				if(Timeout_active())
					Timout_start();					// TimeOut Timer Start.
			  once = 1;								// Set Once Flag.
		  }
		  else
			  printf2(".");
		  if (((Timeout_test() == 0) && Timeout_active()) ||
				  (mode == LOW_BAT))
		  {
			  nobeep_flg = 1;					    // Turn On Beep.
			  Timeout_clear();					// Clear 2 Minute Timer.
			  if (mode == LOW_BAT)
				  mode = Low_PD;	  				    // We are now in true Low Power Mode..
			  else
				  mode = Soft_PD; 	  				// Set Mode to Soft_PD.
			  once = 0;								// Reset once flag.
		  }
		  else
		  {
			  key_var = scan_keyboard();				// Scan Keyboard.
			  if (key_var == 0){
				  laser_hold = 1;						// Set laser_hold only if Laser key released.
				  nobeep_flg = 1;					    // Turn On Beep.
			  }
			  if ((key_var > 0) && (laser_hold == 1))
			  {
				  laser_hold = 0; 			  	    // Only one Keypress is legal.
				  nobeep_flg = 0;					    // Turn Off Beep Till mode determined.
				  monPrint_Key(key_var);		// Display Key
				  if (key_var == START)
				  {
					  mode = Laser_On_Armed2;			// Set New Mode.
					  once = 0;							// Reset once flag.
				  }
				  else if (key_var == CANCEL)
				  {
					  mode = Main;						// Set New Mode.
					  once = 0;							// Reset once flag.
					  Timeout_clear();					// Clear 2 Minute Timer.
				  }
			  }
		  }
		  break;

//*******************************************************************************
//*
//*   Laser_On_Armed2
//*
//*	  TODO: Laser_On_Armed2
//*******************************************************************************
	  case Laser_On_Armed2:							// Laser_On_Armed2 Test.
		  if (once == 0) {
			  printf2("*** Laser_On_Armed2 ***\n");
			  once = 1;								// Set Once Flag.
		  }
		  else
			  printf2(".");
		  if (((Timeout_test() == 0) && Timeout_active()) ||
				  (mode == LOW_BAT))
		  {
			  nobeep_flg = 1;					    // Turn On Beep.
			  Timeout_clear();					// Clear 2 Minute Timer.
			  if (mode == LOW_BAT)
				  mode = Low_PD;	  				    // We are now in true Low Power Mode..
			  else
				  mode = Soft_PD; 	  				// Set Mode to Soft_PD.
			  once = 0;								// Reset once flag.
		  }
		  else
		  {
			  key_var = scan_keyboard();				// Scan Keyboard.
			  if (key_var == 0){
				  // Key release
				  mode = Main;					// Set New Mode.
				  once = 0;							// Reset once flag.
				  Timeout_clear();					// Clear 2 Minute Timer.
				  nobeep_flg = 1;					    // Turn On Beep.
			  }
			  else
			  {
				  mode = Laser_On;					// Set New Mode.
				  once = 0;							// Reset once flag.
				  Timeout_clear();					// Clear 2 Minute Timer.
			  }
		  }
		  break;

//*******************************************************************************
//*
//*   Laser_On
//*
//*	  TODO: Laser_On
//*******************************************************************************
	  case Laser_On:							// Laser_On.
#ifdef DEBUGGR
		debug1(4);
#endif
		// remain_screen();						// Display Main Screen.
	    if (once == 0) {
	      printf2("*** Laser_On ***\n");
	      monPrint("MNTR", "Laser_On");			// Send Status Message
          laser_flg = 1;	 			   		// New Event Set laser_flg.
		  tmr_min = 5; 							// Set Timer to 5 Minutes.
		  tmr_sec = 0;							// and 0 Seconds.
		  cnt_dwn_flg = 1;						// Enable Timer and start Count Down.
		  tmr_update_flg = 1;					// Don't Update Timer Vars for This Event.
		  sweep_flg = 0;						// Deactivate any previous Sweep Mode flags.
		  clear_screen();						// Clear Screen to remove any residue from screen.
		  nobeep_flg = 1;					    // Turn On Beep.
		  init_laser(prog_num, LASERSINIT);		// Start Laser Now.
		  nobeep_flg = 0;					    // Turn Off Beep.
		  remain_screen();						// Display Main Screen.
		  two_sec_start();						// Two Second Timer Start.
		  once = 1;								// Set Once Flag.
		}
	    else
		  printf2(".");
	    update_time();							// Update Timer Only.
		key_var = tst_Start();					// Test for Start Key Held
#ifdef DEBUGGR
		debug1(13);
#endif
		if (cnt_dwn_flg == 0) {
		  if (macro_flg > 0) {
		    //Update to next step for Macro.
		    init_laser( macro1.prog_save, LASERSINIT);
		    //Update Display for next Step.
			remain_screen();
			if (macro_flg > 0)
			  cnt_dwn_flg = 1;			  	   // Arm timer for next loop.
		  }
		  else {
			  nobeep_flg = 1;					    // Turn On Beep.
			  laser_off();	   	   					// Turn-Off Laser.
			  monPrint("MNTR", "laser_off");		// Send Status Message
			  mode = Wait_Release;	  				// Set New Mode.
			  once = 0;								// Reset once flag.
		  }
		}
		else if((key_var==0) ||
				(mode == LOW_BAT)) {
		  nobeep_flg = 1;					    // Turn On Beep.
		  sweep_flg = 0;						  //Turn Off Sweep.
//		  macro_flg = 0;		   		  			   // Turn Macros off.
		  cleanup_macros();						// Test and cleanup Macro Vars.
		  cnt_dwn_flg = 0;						// Arm Timer to Deactivate Timer.
		  tmr_update_flg = 2;					// Arm Update to Deactivate Var Update.
  		  if (mode != LOW_BAT)
  		  {
  			  laser_off();	  	   					// Turn-Off Laser.
  			  monPrint("MNTR", "laser_off");		// Send Status Message
  	  		  restore_vars();  			   	 		// Restore Key Variables.
  			  mode = Main;	  						// Set New Mode.
  		  }
		  once = 0;								// Reset once flag.
		}
#ifdef DEBUGGR
		debug1(14);
#endif
	    break;

//*******************************************************************************
//*
//*   Wait_Release
//*
//*	  TODO: Wait_Release
//*******************************************************************************
	  case Wait_Release:						// Wait_Release.
		printf2("*** Wait_Release ***\n");
		key_var = scan_keyboard();				// Scan Keyboard.
		if (key_var == 0) {
		  tmr_update_flg = 2;					// Arm Update to Deactivate Var Update.
  		  restore_vars();  			   	 		// Restore Key Variables.
		  mode = Main;	   						// Set New Mode.
		  once = 0;								// Reset once flag.
		}
	    break;

//*******************************************************************************
//*
//*   Timed_Laser
//*
//*	  TODO: Timed_Laser
//*******************************************************************************
	  case Timed_Laser:							// Timed_Laser.
	    update_time();							// Update Timer Only.
	    if (once == 0) {
		  printf2("*** Timed_Laser ***\n");
		  monPrint("MNTR", "Timed_Laser_On");		// Send Status Message
          laser_flg = 1;	 			   		// New Event Set laser_flg.
		  asrt_col6(); 							// Assert Col 1 for Key Test Later.
		  cnt_dwn_flg = 1;						// Enable Timer and start Count Down.
		  tmr_update_flg = 1;					// Don't Update Timer Vars for This Event.
		  sweep_flg = 0;						// Deactivate any previous Sweep Mode flags.
		  clear_screen();						// Clear Screen to remove any residue from screen.
		  init_laser(prog_num, LASERSINIT);		// Start Laser Now.
		  remain_screen();
		  once = 1;								// Set Once Flag.
		  laser_hold = 0;						// Clear laser_hold var.
		}
	    else
		  printf2(".");
	    asrt_col0(); 							// Assert Col 1 for Key Test Later.
		key_var = tst_cancel();					// Test for Cancel Key
		asrt_col6(); 							// Assert Col 1 for Key Test Later.
		if (cnt_dwn_flg == 0) {
		  laser_off();	   	   					// Turn-Off Laser.
		  sweep_flg = 0;						  //Turn Off Sweep.
		  if (macro_flg > 0) {
		    nobeep_flg = 0;					// Turn Off Beep Till mode determined.
		    laser_off();	   	   					// Turn-Off Laser.
		    monPrint("MNTR", "Timed_Laser_off");		// Send Status Message
			sweep_flg = 0;						  //Turn Off Sweep.
		    nobeep_flg = 1;					// Turn On Beep.
		    beep_3Bp();	  	 			 		// Beep 3 Times.
		    nobeep_flg = 0;					// Turn Off Beep Till mode determined.
	        fast_flg = 0;	  				   		// Deactivate Sweep Processing.
			if (macro1.macro_step >= macro1.macro1->num_entries) {
			  macro_flg = 3;						// Set to special mode.
		      init_laser(prog_num, LASERSINIT);		// Last Run...Cleanup.
		      tmr_update_flg = 2;					// Arm Update to Deactivate Var Update.
  		      restore_vars();  			   	 		// Restore Key Variables.
		      mode = Main;	  						// Set New Mode.
		      once = 0;								// Reset once flag.
			}
			else {
			  // Test Delay of next entry...If zero...force execution of next step.
			  if ((macro1.macro1->mac_entry[macro1.macro_step-1].delay.minutes == 0) &&
			  	  (macro1.macro1->mac_entry[macro1.macro_step-1].delay.seconds == 0)) {
		    	  //Update to next step for Macro.
		    	  init_laser( macro1.prog_save, LASERSINIT);
		    	  //Update Display for next Step.
				  remain_screen();
				  //if (macro_flg > 0)
			  	  // cnt_dwn_flg = 1;			  	   // Arm timer for next loop.
			  }
			  // Else force normal Pause.
			  else {
		      	   mode = Pause_Laser;						// Set New Mode.
		      	   once = 0;								// Reset once flag.
			  	   macro_flg = 3;							// Set to special mode.
			  }
			}
		    //Update Display for next Step.
			remain_screen();
			cnt_dwn_flg = 1;			  	   // Arm timer for next loop.
		  }
		  else {
		    tmr_update_flg = 2;					// Arm Update to Deactivate Var Update.
  		    restore_vars();  			   	 		// Restore Key Variables.
		    mode = Main;	  						// Set New Mode.
		    once = 0;								// Reset once flag.
		  }
		}
		else if((key_var==1)  ||
		        (mode == LOW_BAT)){
//		  macro_flg = 2;
 		  sweep_flg = 0;						  //Turn Off Sweep.
  		  cleanup_macros();						// Test and cleanup Macro Vars.
		  cnt_dwn_flg = 0;						// Arm Timer to Deactivate Timer.
		  tmr_update_flg = 2;					// Arm Update to Deactivate Var Update.
  		  if (mode != LOW_BAT)
  		  {
  			  laser_off();	  	   					// Turn-Off Laser.
  	  		  restore_vars();  			   	 		// Restore Key Variables.
  			  mode = Main;	  						// Set New Mode.
  		  }
		  once = 0;								// Reset once flag.
        }

	    asrt_col0(); 							// Assert Col 1 for Key Test Later.
		key_var = tst_cancel();					// Test for Cancel Key
		if((key_var==1)  ||
		        (mode == LOW_BAT)){
//		  macro_flg = 2;
 		  sweep_flg = 0;						  //Turn Off Sweep.
  		  cleanup_macros();						// Test and cleanup Macro Vars.
		  cnt_dwn_flg = 0;						// Arm Timer to Deactivate Timer.
		  tmr_update_flg = 2;					// Arm Update to Deactivate Var Update.
  		  if (mode != LOW_BAT)
  		  {
  			  laser_off();	  	   					// Turn-Off Laser.
  	  		  restore_vars();  			   	 		// Restore Key Variables.
  			  mode = Main;	  						// Set New Mode.
  		  }
		  once = 0;								// Reset once flag.
        }
	    key_var = tst_Start();					// Test Start Key.
		if (key_var == 0)
		  laser_hold = 1;						// Set laser_hold only if Laser key released.
		if((key_var == 1) && (laser_hold == 1)) {
		    if (macro_flg > 0)
			  macro_flg = 2;							// Set to special mode.
			nobeep_flg = 0;					// Turn Off Beep Till mode determined.
		    laser_off();	   	   					// Turn-Off Laser.
			nobeep_flg = 1;					// Turn On Beep.
			beep_3Bp();	  	 			 		// Beep 3 Times.
			nobeep_flg = 0;					// Turn Off Beep Till mode determined.
		    cnt_dwn_flg = 0;						// Deactivate Timer.
			sweep_flg = 0xF0;							// Force sweep_flg into illegal state.
	        fast_flg = 0;	  				   		// Deactivate Sweep Processing.
		    mode = Pause_Laser;						// Set New Mode.
		    once = 0;								// Reset once flag.
		}
	    break;

//*******************************************************************************
//*
//*   Pause_Laser
//*
//*	  TODO: Pause_Laser
//*******************************************************************************
	  case Pause_Laser:							// Pause_Laser.
	    if (once == 0) {
		  printf2("*** Pause_Laser ***\n");
		  monPrint("MNTR", "Pause_Laser");		// Send Status Message
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		  once = 1;								// Set Once Flag.
		}
	    else
		  printf2(".");
		key_var = scan_keyboard();				// Scan Keyboard.
        if (key_var == 0) {
		  mode = Pause_Laser2;					// Set New Mode.
		  once = 0;								// Reset once flag.
		}
		else if ((Timeout_test() == 0) && Timeout_active()) {
		  nobeep_flg = 1;					    // Turn On Beep Till mode determined.
		  cleanup_macros();						// Test and cleanup Macro Vars.
		  mode = Soft_PD;							// Set New Mode.
		  once = 0;									// Reset once flag.
		}
	    break;

//*******************************************************************************
//*
//*   Pause_Laser2
//*
//*	  TODO: Pause_Laser2
//*******************************************************************************
	  case Pause_Laser2:						// Pause_Laser2.
	    if (once == 0) {
		  printf2("*** Pause_Laser2 ***\n");
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		  once = 1;								// Set Once Flag.
		}
	    else
		  printf2(".");
		key_var = scan_keyboard();				// Scan Keyboard.
	    if (key_var == 0){
		    laser_hold = 1;						// Set laser_hold only if Laser key released.
	        nobeep_flg = 1;					    // Turn On Beep.
	    }
		if ((key_var > 0) && (laser_hold == 1))
		{
		  laser_hold = 0;						// Set laser_hold only if Laser key released.
	      nobeep_flg = 0;					    // Turn On Beep.
          monPrint_Key(key_var);		// Display Key
		  if (key_var == START) {
			nobeep_flg = 1;					    // Turn On Beep Till mode determined.
		    cnt_dwn_flg = 1;						// Enable Timer and start Count Down.
			laser_flg = 1;							// Restarting...Set Laser Flag.
		    init_laser(prog_num, LASERSINIT);		// Start Laser Now.
		    monPrint("MNTR", "Un-Pause_Laser");		// Send Status Message
		    mode = Pause_Laser3;					// Set New Mode.
		    once = 0;								// Reset once flag.
	      }
		  else if (key_var == CANCEL) {
			nobeep_flg = 1;					    // Turn On Beep Till mode determined.
			beep_ArpDn();						// Indicate Operation Canceled.
			monPrint("MNTR", "Event_Cancel");		// Send Status Message
		    cnt_dwn_flg = 0;						// Arm Timer to Deactivate Timer.
		    tmr_update_flg = 2;					// Arm Update to Deactivate Var Update.
  		    restore_vars();  			   	 		// Restore Key Variables.
		    cleanup_macros();						// Test and cleanup Macro Vars.
		    mode = Main;	  						// Set New Mode.
		    once = 0;								// Reset once flag.
	      }
		}
		else if ((Timeout_test() == 0) && Timeout_active()) {
		  nobeep_flg = 1;					    // Turn On Beep Till mode determined.
		  cleanup_macros();						// Test and cleanup Macro Vars.
		  mode = Soft_PD;							// Set New Mode.
		  once = 0;									// Reset once flag.
		}
	    break;

//*******************************************************************************
//*
//*   Pause_Laser3
//*
//*	  TODO: Pause_Laser3
//*******************************************************************************
	  case Pause_Laser3:						// Pause_Laser3.
		printf2("*** Pause_Laser3 ***\n");
//		remain_screen();						// Display Main Screen.
	    asrt_col6(); 							// Assert Col 1 for Key Test Later.
		key_var = tst_laser();					// Test for Laser Key Held
		if (cnt_dwn_flg == 0) {
		  remain_screen();						// Display Main Screen.
		  laser_off();	   	   					// Turn-Off Laser.
		  sweep_flg = 0;						  //Turn Off Sweep.
		  cleanup_macros();						// Test and cleanup Macro Vars.
		  cnt_dwn_flg = 0;						// Arm Timer to Deactivate Timer.
		  tmr_update_flg = 2;					// Arm Update to Deactivate Var Update.
  		  restore_vars();  			   	 		// Restore Key Variables.
		  mode = Main;	  						// Set New Mode.
		  once = 0;								// Reset once flag.
		}
        if (key_var == 0) {
		  mode = Timed_Laser;					// Set New Mode.
		  once = 1;								// Set once flag.
		  laser_hold = 0;						// Clear laser_hold var.
		}
	    break;

//*******************************************************************************
//*
//*   Five_Min_Mode
//*
//*	  TODO: Five_Min_Mode
//*******************************************************************************
	  case Five_Min_Mode:						// Five_Min_Mode.
#ifdef DEBUGGR
		debug1(7);
#endif
	    asrt_col1(); 							// Assert Col 1 for Key Test Later.
	    if (once == 0) {
		  printf2("*** Five_Min_Mode ***\n");
		  monPrint("MNTR", "Five_Min_Mode_On");		// Send Status Message
//		  remain_screen();						// Display Main Screen.
          laser_flg = 1;	 			   		// New Event Set laser_flg.
		  tmr_min = 5; 							// Set Timer to 5 Minutes.
		  tmr_sec = 0;							// and 0 Seconds.
		  cnt_dwn_flg = 1;						// Enable Timer and start Count Down.
		  tmr_update_flg = 1;					// Don't Update Timer Vars for This Event.
		  clear_screen();						// Clear Screen to remove any residue from screen.
		  init_laser(prog_num, LASERSINIT);		// Start Laser Now.
		  remain_screen();
		  once = 1;								// Set Once Flag.
		  laser_hold = 0;						// Clear laser_hold var.
#ifdef DEBUGGR
	    debug1(9);
#endif
		}
	    else
		  printf2(".");
		asrt_col0(); 							// Assert Col 1 for Key Test Later.
	    update_time();							// Update Timer Only.
		key_var = tst_cancel();					// Test for Cancel Key
		asrt_col1(); 							// Assert Col 1 for Key Test Later.
		if (cnt_dwn_flg == 0)
		{
#ifdef DEBUGGR
	      debug1(10);
#endif
		  laser_off();	   	   					// Turn-Off Laser.
		  monPrint("MNTR", "Five_Min_Mode_Off");		// Send Status Message
		  sweep_flg = 0;						  //Turn Off Sweep.
		  // Test for Macro and update.
		  if (macro_flg > 0)
		  {
#ifdef DEBUGGR
   		      debug1(16);
#endif
   		      //Update to next step for Macro.
   		      init_laser( macro1.prog_save, LASERSINIT);
   		      monPrint("MNTR", "Five_Min_Mode_Next");		// Send Status Message
   		      //Update Display for next Step.
   		      remain_screen();
   		      if ((macro1.macro_step == macro1.macro1->num_entries) &&
   		    		  (tmr_min == 0) &&
   		    		  (tmr_sec == 0))
   		      {
   		    	  cnt_dwn_flg = 0;			  	   // Arm timer for next loop.
   		      }
   		      else if (macro_flg > 0)
   		    	  cnt_dwn_flg = 1;			  	   // Arm timer for next loop.
		  }
		  else {
			  tmr_update_flg = 2;					// Arm Update to Deactivate Var Update.
			  restore_vars();  			   	 		// Restore Key Variables.
			  mode = Main;	  						// Set New Mode.
			  once = 0;								// Reset once flag.
		  } // EndElse (macro_flg > 0)
		} // EndIf (cnt_dwn_flg == 0)
		else if((key_var==1)  ||
		        (mode == LOW_BAT))
		{
#ifdef DEBUGGR
		  debug1(11);
#endif
		  sweep_flg = 0;						  //Turn Off Sweep.
//		  macro_flg = 0;		   		  			   // Turn Macros off.
		  cleanup_macros();						// Test and cleanup Macro Vars.
		  cnt_dwn_flg = 0;						// Deactivate Timer.
		  tmr_update_flg = 2;					// Arm Update to Deactivate Var Update.
  		  if (mode != LOW_BAT)
  		  {
  			  laser_off();	   	   					// Turn-Off Laser.
  			  monPrint("MNTR", "Five_Min_Mode_Off");		// Send Status Message
  	  		  restore_vars();  			   	 		// Restore Key Variables.
  			  mode = Main;	  						// Set New Mode.
  		  }
		  once = 0;								// Reset once flag.
		}
		key_var = tst_Start();					// Test for Power Key
		if (key_var == 0)
		  laser_hold = 1;						// Set laser_hold only if Laser key released.
		if((key_var == 1) && (laser_hold == 1)) {
#ifdef DEBUGGR
		  debug1(17);
#endif
		  laser_off();	   	   					// Turn-Off Laser.
		  monPrint("MNTR", "Five_Min_Mode_Off");		// Send Status Message
		  sweep_flg = 0;						  //Turn Off Sweep.
//		  macro_flg = 0;		   		  			   // Turn Macros off.
		  cleanup_macros();						// Test and cleanup Macro Vars.
		  cnt_dwn_flg = 0;						// Deactivate Timer.
		  tmr_update_flg = 2;					// Arm Update to Deactivate Var Update.
  		  restore_vars();  			   	 		// Restore Key Variables.
		  mode = Pause1;							// Set New Mode.
		  once = 0;								// Reset once flag.
		}
	    break;

//*******************************************************************************
//*
//*   Pause1
//*
//*	  TODO: Pause1
//*******************************************************************************
	  case Pause1:								// Pause1.
	    if (once == 0) {
		  printf2("*** Pause1 ***\n");
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		  once = 1;								// Set Once Flag.
		}
	    else
		  printf2(".");
		key_var = scan_keyboard();				// Scan Keyboard.
        if (key_var == 0) {
  		  cleanup_macros();						// Test and cleanup Macro Vars.
		  mode = Main;							// Set New Mode.
		  once = 0;								// Reset once flag.
		}
		else if ((Timeout_test() == 0) && Timeout_active()) {
		  cleanup_macros();						// Test and cleanup Macro Vars.
		  mode = Soft_PD;							// Set New Mode.
		  once = 0;									// Reset once flag.
		}
	    break;

//*******************************************************************************
//*
//*   Pause
//*
//*	  TODO: Pause
//*******************************************************************************
/*	  case Pause:								// Pause.
	    if (once == 0) {
		  printf2("*** Pause ***\n");
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		  once = 1;								// Set Once Flag.
		}
	    else
		  printf2(".");
		key_var = scan_keyboard();				// Scan Keyboard.
        if (key_var > 0) {
		  if (key_var == POWER) {
		    cnt_dwn_flg = 1;						// Enable Timer and start Count Down.
		    init_laser(prog_num, LASERSINIT);		// Start Laser Now.
		    mode = Pause2;							// Set New Mode.
		    once = 0;								// Reset once flag.
	      }
		  else if (key_var == CANCEL) {
		    cnt_dwn_flg = 0;						// Arm Timer to Deactivate Timer.
		    tmr_update_flg = 2;					// Arm Update to Deactivate Var Update.
  		    restore_vars();  			   	 		// Restore Key Variables.
		    mode = Main;   							// Set New Mode.
		    once = 0;								// Reset once flag.
	      }
		}
		else if ((Timeout_test() == 0) && Timeout_active()) {
		  mode = Soft_PD;							// Set New Mode.
		  once = 0;									// Reset once flag.
		}
	    break;  */

//*******************************************************************************
//*
//*   Pause2
//*
//*	  TODO: Pause2
//*******************************************************************************
/*	  case Pause2:								// Pause2.
		printf2("*** Pause2 ***\n");
		remain_screen();						// Display Main Screen.
		key_var = tst_laser();					// Test for Laser Key Held
		if (cnt_dwn_flg == 0) {
		  laser_off();	   	   					// Turn-Off Laser.
		  cnt_dwn_flg = 0;						// Arm Timer to Deactivate Timer.
		  tmr_update_flg = 2;					// Arm Update to Deactivate Var Update.
  		  restore_vars();  			   	 		// Restore Key Variables.
		  mode = Main;	  						// Set New Mode.
		  once = 0;								// Reset once flag.
		}
        if (key_var == 0) {
		  mode = Five_Min_Mode;					// Set New Mode.
		  once = 1;								// Set once flag.
		  laser_hold = 0;						// Clear laser_hold var.
		}
	    break;   */

//*******************************************************************************
//*
//*   Program
//*
//*	  TODO: Program
//*******************************************************************************
	  case Program:								// Program.
        // Only refresh if new Character.
		if(laser_hold == 0) {
          quick_laser(prog_num);
		  remain_screen();							// Display Main Screen.
		}
		if (incr_flg == 0)
          set_cursor(LINE4, 12, BLINK);
	    if (once == 0) {
		  printf2("*** Program ***\n");
		  monPrint("MNTR", "Program");		// Send Status Message
		  save_prog = prog_num;					// Save Program Number..If canceled.
		  laser_hold = 0;						// Clear laser_hold var.
		  update_num = 0;						// Clear update_num var.
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		  once = 1;								// Set Once Flag.
		}
	    else
		  printf2(".");
	    if ((Timeout_test() == 0) && Timeout_active()) {
	      nobeep_flg = 1;					    // Turn On Beep.
		  prog_num = save_prog;					// Restore prog_num.
		  mode = Soft_PD; 	  					// Set Mode to Soft_PD.
		  once = 0;								// Reset once flag.
		} // End If Test two_min_test Failed
		else {
		  key_var = scan_keyboard();			// Scan Keyboard.
		  if (key_var == 0)
		  {
		    laser_hold = 1;						// Set laser_hold only if Laser key released.
			nobeep_flg = 1;					    // Turn On Beep.
		  }
		  if((key_var > 0) && (laser_hold == 1)) {
            monPrint_Key(key_var);		// Display Key
			laser_hold = 0;						// New Character...Refresh.
			nobeep_flg = 0;					    // Turn On Beep.
		    switch (key_var) {
			  case UP:
		  	    update_num = 0;					// Clear update_num var.
				prog_num++;					    // Increment Program Number.
#ifdef CLW
			    if (prog_num > PROG_NUMBR)	   // PROG_NUMBR == CSTMSUPR2_REND
			    {
				    if (opMode == 3)			// Legacy is only active.
				    {
				    	prog_num = CUSTOM4_START;
				    }
				    else
				    {
				    	prog_num = CUSTOM_START;
				    }
			    }
#else
			    if (prog_num > PROG_NUMBR)	   // PROG_NUMBR == CSTMSUPR2_REND
				  prog_num = CUSTOM_START;
#endif
#ifdef CLW
			    else if (opMode == 3)			// Legacy is only active.
			    {
			    	if ((prog_num > CUSTOM4_REND) && (prog_num <= CUSTOM4_END))
			    		prog_num = USER_STRT;
			    	else if ((prog_num > CUSTOM_START) && (prog_num < CUSTOM4_START))
			    		prog_num = CUSTOM4_START;
			    }
			    else
			    {
			    	if ((prog_num > CUSTOM_REND) && (prog_num <= CUSTOM_END))
			    		prog_num = CUSTOM2_START;
			    	else if ((prog_num > CUSTOM2_REND) && (prog_num <= CUSTOM2_END))
			    		prog_num = CUSTOM3_START;
			    	else if ((prog_num > CUSTOM3_REND) && (prog_num <= CUSTOM3_END))
			    		prog_num = CUSTOM4_START;
			    	else if ((prog_num > CUSTOM4_REND) && (prog_num <= CUSTOM4_END))
			    		prog_num = USER_STRT;
			    }
#else
			    else if ((prog_num > CUSTOM_REND) && (prog_num <= CUSTOM_END))
				  prog_num = USER_STRT;
#endif
				if ((prog_num > USER_REND) && (prog_num <= USER_END))
				  prog_num = SWEEP_STRT;
				else if ((prog_num > SWEEP_REND) && (prog_num <= SWEEP_END))
				  prog_num = CSTMSUPR_STRT;
				else if ((prog_num > CSTMSUPR_REND) && (prog_num <= CSTMSUPR_END))
				  prog_num = USERSUPR_STRT;
#ifdef CLW
				else if ((prog_num > USERSUPR_REND) && (prog_num <= USERSUPR_END))
				{
				    if (opMode == 3)			// Legacy is only active.
				    {
				    	prog_num = CUSTOM4_START;
				    }
				    else
				    {
				    	prog_num = CUSTOM_START;
				    }
				}
#else
				else if ((prog_num > USERSUPR_REND) && (prog_num <= USERSUPR_END))
				  prog_num = CUSTOM_START;
#endif
				mode = Incr_Prog;				// Set New Mode.
			    break;

			  case DOWN:
		  	    update_num = 0;					// Clear update_num var.
			    if (prog_num == 0)
				  prog_num = PROG_NUMBR;
				else
				  prog_num--;				    // Decrement Program Number.
   				//Test Prog_num and skip unsed areas.
#ifdef CLW
			    if (opMode == 3)			// Legacy is only active.
			    {
				    if (prog_num < CUSTOM4_START)
				    {
					  prog_num = PROG_NUMBR;
				    }
			    }
			    else
			    {
				    if (prog_num == 0)
				    {
					  prog_num = PROG_NUMBR;
				    }
			    }
#else
			    if (prog_num == 0)
			    {
				  prog_num = PROG_NUMBR;
			    }
#endif
#ifdef CLW
			    if (opMode == 3)			// Legacy is only active.
			    {
				    if ((prog_num > CUSTOM4_REND) && (prog_num <= CUSTOM4_END))
				    	prog_num = CUSTOM4_REND;
			    }
			    else
			    {
			    	if ((prog_num > CUSTOM_REND) && (prog_num <= CUSTOM_END))
			    		prog_num = CUSTOM_REND;
			    	else if ((prog_num > CUSTOM2_REND) && (prog_num <= CUSTOM2_END))
			    		prog_num = CUSTOM2_REND;
			    	else if ((prog_num > CUSTOM3_REND) && (prog_num <= CUSTOM3_END))
			    		prog_num = CUSTOM3_REND;
			    	else if ((prog_num > CUSTOM4_REND) && (prog_num <= CUSTOM4_END))
			    		prog_num = CUSTOM4_REND;
			    }
#else
			    else if ((prog_num > CUSTOM_REND) && (prog_num <= CUSTOM_END))
				  prog_num = CUSTOM_REND;
#endif
				if ((prog_num > USER_REND) && (prog_num <= USER_END))
				  prog_num = USER_REND;
				else if ((prog_num > SWEEP_REND) && (prog_num <= SWEEP_END))
				  prog_num = SWEEP_REND;
				else if ((prog_num > CSTMSUPR_REND) && (prog_num <= CSTMSUPR_END))
				  prog_num = CSTMSUPR_REND;
				else if ((prog_num > USERSUPR_REND) && (prog_num <= USERSUPR_END))
				  prog_num = USERSUPR_REND;
				mode = Decr_Prog;				// Set New Mode.
			    break;

			  case TIME:
				prog_num = save_prog;			// Restore prog_num.
		        sprintf(Prog_str,"%d",prog_num);
		        data1 = read_entry(prog_num);			// Read Current Mode Entry.
		        Ptr1 = data1->string1;
		        while (*Ptr1 == 0x20)
		        	Ptr1++;
		        // Clean Out temp string before using it.
		        for (x=0;x<80;x++)
		        	temp_String[x]=0x00;
		        if ((prog_num > CUSTOM4_END) && (prog_num <= USER_REND)) {
		        	sprintf(temp_String, "%s/CUSTOM", Prog_str, Ptr1);
		        	monPrint("PROG", temp_String);		// temp_String
		        	monPrint("LASER1", lser1_strng);			// Send Status Message
		        	monPrint("LASER2", lser2_strng);			// Send Status Message
		        	monPrint("LASER3", lser3_strng);			// Send Status Message
		        	monPrint("LASER4", lser4_strng);			// Send Status Message
		        }
		        else
		        {
		        	sprintf(temp_String, "%s/%s", Prog_str, Ptr1);
		        	monPrint("PROG", temp_String);		// temp_String
		        }
		        //monPrint("PROG_NUM", Prog_str);		// Send Status Message
		        //monPrint("PROG_STR", Ptr1);		// Send Status Message
				mode = Time_Value;				// Set New Mode.
		        once = 0;							// Reset once flag.
			    break;

			  case LASER:
	  			if ((((prog_num >= USER_STRT) && (prog_num <= USER_REND)) ||
	  					((prog_num >= SWEEP_STRT) && (prog_num <= SWEEP_REND)) ||
	  					((prog_num >= USERSUPR_STRT) && (prog_num <= USERSUPR_REND))) &&
						(data1->entry_flg == 0)) {
	  				if (prog_num > PROG_NUMBR)
					    prog_num = PROG_NUMBR;
			        sprintf(Prog_str,"%d",prog_num);
			        data1 = read_entry(prog_num);			// Read Current Mode Entry.
			        Ptr1 = data1->string1;
			        while (*Ptr1 == 0x20)
			        	Ptr1++;
			        // Clean Out temp string before using it.
			        for (x=0;x<80;x++)
			        	temp_String[x]=0x00;
			        if ((prog_num > CUSTOM4_END) && (prog_num <= USER_REND)) {
			        	sprintf(temp_String, "%s/CUSTOM", Prog_str, Ptr1);
			        	monPrint("PROG", temp_String);		// temp_String
			        	monPrint("LASER1", lser1_strng);			// Send Status Message
			        	monPrint("LASER2", lser2_strng);			// Send Status Message
			        	monPrint("LASER3", lser3_strng);			// Send Status Message
			        	monPrint("LASER4", lser4_strng);			// Send Status Message
			        }
			        else
			        {
			        	sprintf(temp_String, "%s/%s", Prog_str, Ptr1);
			        	monPrint("PROG", temp_String);		// temp_String
			        }
			        //monPrint("PROG_NUM", Prog_str);		// Send Status Message
			        //monPrint("PROG_STR", Ptr1);		// Send Status Message
			        mode = Laser_Value;				// Set New Mode.
			        once = 0;							// Reset once flag.
	  			}
			    break;

			  case DELETE:
  			    if (prog_num > PROG_CNT) {
				  mode = Delete_Prog;				// Set New Mode.
		          once = 0;							// Reset once flag.
				}
			    break;

			  case SELECT:
			    sprintf(Prog_str,"%d",prog_num);
			    data1 = read_entry(prog_num);			// Read Current Mode Entry.
		        Ptr1 = data1->string1;
		        while (*Ptr1 == 0x20)
		        	Ptr1++;
		        // Clean Out temp string before using it.
		        for (x=0;x<80;x++)
		        	temp_String[x]=0x00;
		        if ((prog_num > CUSTOM4_END) && (prog_num <= USER_REND)) {
		        	sprintf(temp_String, "%s/CUSTOM", Prog_str, Ptr1);
		        	monPrint("PROG", temp_String);		// temp_String
		        	monPrint("LASER1", lser1_strng);			// Send Status Message
		        	monPrint("LASER2", lser2_strng);			// Send Status Message
		        	monPrint("LASER3", lser3_strng);			// Send Status Message
		        	monPrint("LASER4", lser4_strng);			// Send Status Message
		        }
		        else
		        {
		        	sprintf(temp_String, "%s/%s", Prog_str, Ptr1);
		        	monPrint("PROG", temp_String);		// temp_String
		        }
			    //monPrint("PROG_NUM", Prog_str);		// Send Status Message
			    //monPrint("PROG_STR", Ptr1);		// Send Status Message
				mode = Activate_Prog;			// Set New Mode.
		        once = 0;							// Reset once flag.
			    break;

			  case CANCEL:
		        prog_num = save_prog;			// Restore prog_num.
		        sprintf(Prog_str,"%d",prog_num);
		        data1 = read_entry(prog_num);			// Read Current Mode Entry.
		        Ptr1 = data1->string1;
		        while (*Ptr1 == 0x20)
		        	Ptr1++;
		        // Clean Out temp string before using it.
		        for (x=0;x<80;x++)
		        	temp_String[x]=0x00;
		        if ((prog_num > CUSTOM4_END) && (prog_num <= USER_REND)) {
		        	sprintf(temp_String, "%s/CUSTOM", Prog_str, Ptr1);
		        	monPrint("PROG", temp_String);		// temp_String
		        	monPrint("LASER1", lser1_strng);			// Send Status Message
		        	monPrint("LASER2", lser2_strng);			// Send Status Message
		        	monPrint("LASER3", lser3_strng);			// Send Status Message
		        	monPrint("LASER4", lser4_strng);			// Send Status Message
		        }
		        else
		        {
		        	sprintf(temp_String, "%s/%s", Prog_str, Ptr1);
		        	monPrint("PROG", temp_String);		// temp_String
		        }
		        //monPrint("PROG_NUM", Prog_str);		// Send Status Message
		        //monPrint("PROG_STR", Ptr1);		// Send Status Message
				mode = Main;					// Set New Mode.
		        once = 0;							// Reset once flag.
			    break;

			  case ZERO:
			  case ONE:
			  case TWO:
			  case THREE:
			  case FOUR:
			  case FIVE:
			  case SIX:
			  case SEVEN:
			  case EIGHT:
			  case NINE:
		        if (update_num == 0) {
		          update_num = 1;						// Set laser_hold only if Laser key released.
                  strcpy(prog_str, "  ");			// Copy a Blank string to prog_str.
			    }
				shft_str_left(prog_str, 3);					// Shift String to the left by one.
				tempstr = get_numstr(key_var);
			    strncat(prog_str, tempstr, 1);		// Add Number to this string.
				prog_num = atoi(prog_str);					// Build new Prog Number.
				mode = Build_Prog;			// Set New Mode.
			    break;

			  case BACK:
			    prog_str[2] = prog_str[1];
			    prog_str[1] = prog_str[0];
			    prog_str[0] = ' ';
				prog_num = atoi(prog_str);					// Build new Prog Number.
				mode = Build_Prog;			// Set New Mode.
			    break;
			} // End Switch on key_var
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		  } //Endif Key Found
		} // End If two_min_test active
	    break;

//*******************************************************************************
//*
//*   Incr_Prog
//*
//*	  TODO: Incr_Prog
//*******************************************************************************
	  case Incr_Prog:							// Incr_Prog.

//*******************************************************************************
//*
//*   Decr_Prog
//*
//*	  TODO: Decr_Prog
//*******************************************************************************
	  case Decr_Prog:							// Decr_Prog.
		printf2("*** Decr_Prog ***\n");
        if (incr_flg == 0) {
          p5_sec_start();						// 0.5 Second Timer Start.
		  incr_flg = 1;							// Set incr_flg.
		}
//*******************************************************************************
//*
//*   Build_Prog
//*
//*	  TODO: Build_Prog
//*******************************************************************************
	  case Build_Prog:							// Build_Prog.
		printf2("*** Build_Prog ***\n");
        quick_laser(prog_num);
		remain_screen();							// Display Main Screen.
		if (incr_flg == 0)
          set_cursor(LINE4, 12, BLINK);
		key_var = scan_keyboard();				// Scan Keyboard.
	    if ((p5_sec_test() == 0) && (incr_flg == 1)) {
		  if (key_var == UP) {
		    prog_num++;					    	// Increment Program Number.
			//Test Prog_num and skip unsed areas.
#ifdef CLW
		    if (prog_num > PROG_NUMBR)	   // PROG_NUMBR == CSTMSUPR2_REND
		    {
			    if (opMode == 3)			// Legacy is only active.
			    {
			    	prog_num = CUSTOM4_START;
			    }
			    else
			    {
			    	prog_num = CUSTOM_START;
			    }
		    }
#else
		    if (prog_num > PROG_NUMBR)	   // PROG_NUMBR == CSTMSUPR2_REND
		    {
			  prog_num = CUSTOM_START;
		    }
#endif
#ifdef CLW
		    else if (opMode == 3)			// Legacy is only active.
		    {
		    	if ((prog_num > CUSTOM4_REND) && (prog_num <= CUSTOM4_END))
		    		prog_num = USER_STRT;
		    	else if ((prog_num > CUSTOM_START) && (prog_num < CUSTOM4_START))
		    		prog_num = CUSTOM4_START;
		    }
		    else
		    {
		    	if ((prog_num > CUSTOM_REND) && (prog_num <= CUSTOM_END))
		    		prog_num = CUSTOM2_START;
		    	else if ((prog_num > CUSTOM2_REND) && (prog_num <= CUSTOM2_END))
		    		prog_num = CUSTOM3_START;
		    	else if ((prog_num > CUSTOM3_REND) && (prog_num <= CUSTOM3_END))
		    		prog_num = CUSTOM4_START;
		    	else if ((prog_num > CUSTOM4_REND) && (prog_num <= CUSTOM4_END))
		    		prog_num = USER_STRT;
		    }
#else
		    else if ((prog_num > CUSTOM_REND) && (prog_num <= CUSTOM_END))
			  prog_num = USER_STRT;
#endif
			if ((prog_num > USER_REND) && (prog_num <= USER_END))
			  prog_num = SWEEP_STRT;
			else if ((prog_num > SWEEP_REND) && (prog_num <= SWEEP_END))
			  prog_num = CSTMSUPR_STRT;
			else if ((prog_num > CSTMSUPR_REND) && (prog_num <= CSTMSUPR_END))
			  prog_num = USERSUPR_STRT;
			else if ((prog_num > USERSUPR_REND) && (prog_num <= USERSUPR_END))
			{
#ifdef CLW
			    if (opMode == 3)			// Legacy is only active.
			    {
			    	prog_num = CUSTOM4_START;
			    }
			    else
			    {
			    	prog_num = CUSTOM_START;
			    }
#else
				prog_num = CUSTOM_START;
#endif
			}
		  }
		  else if (key_var == DOWN) {
		    prog_num--;	   	  	   				// Decrement Program Number.
			//Test Prog_num and skip unsed areas.
#ifdef CLW
			    if (opMode == 3)			// Legacy is only active.
			    {
				    if (prog_num < CUSTOM4_START)
				    {
					  prog_num = PROG_NUMBR;
				    }
			    }
			    else
			    {
				    if (prog_num == 0)
				    {
					  prog_num = PROG_NUMBR;
				    }
			    }
#else
			    if (prog_num == 0)
			    {
				  prog_num = PROG_NUMBR;
			    }
#endif
#ifdef CLW
		    if (opMode == 3)			// Legacy is only active.
		    {
		    	if ((prog_num > CUSTOM4_REND) && (prog_num <= CUSTOM4_END))
		    		prog_num = CUSTOM4_REND;
		    }
		    else
		    {
		    	if ((prog_num > CUSTOM_REND) && (prog_num <= CUSTOM_END))
		    		prog_num = CUSTOM_REND;
		    	else if ((prog_num > CUSTOM2_REND) && (prog_num <= CUSTOM2_END))
		    		prog_num = CUSTOM2_REND;
		    	else if ((prog_num > CUSTOM3_REND) && (prog_num <= CUSTOM3_END))
		    		prog_num = CUSTOM3_REND;
		    	else if ((prog_num > CUSTOM4_REND) && (prog_num <= CUSTOM4_END))
		    		prog_num = CUSTOM4_REND;
		    }
#else
		    else if ((prog_num > CUSTOM_REND) && (prog_num <= CUSTOM_END))
			  prog_num = CUSTOM_REND;
#endif
			if ((prog_num > USER_REND) && (prog_num <= USER_END))
			  prog_num = USER_REND;
			else if ((prog_num > SWEEP_REND) && (prog_num <= SWEEP_END))
			  prog_num = SWEEP_REND;
			else if ((prog_num > CSTMSUPR_REND) && (prog_num <= CSTMSUPR_END))
			  prog_num = CSTMSUPR_REND;
			else if ((prog_num > USERSUPR_REND) && (prog_num <= USERSUPR_END))
			  prog_num = USERSUPR_REND;
		  }
		  Delay();							// Delay a little.
//          p5_sec_start();						// 0.5 Second Timer Start.
		} // End If Test two_min_test Failed

        if (key_var == 0) {
		  mode = Program;						// Set New Mode.
		  incr_flg = 0;							// Set incr_flg.
		}
	    break;

//*******************************************************************************
//*
//*   Activate_Prog
//*
//*	  TODO: Activate_Prog
//*******************************************************************************
	  case Activate_Prog:						// Activate_Prog.
		printf2("*** Activate_Prog ***\n");
	    if (prog_num > PROG_NUMBR)
		  prog_num = PROG_NUMBR;
	    if (prog_num == SWEEP_NUM)
		  sweep1.sweep1 = read_sweep(prog_num);			// Read Sweep Entry.
		else{
	      data1 = read_entry(prog_num);			// Read Current Mode Entry.
		  strcpy(save_str, data1->string1);
	      entry_flg = data1->entry_flg;
		}
	    save_prog = prog_num;					// Update save_prg. New permanent value.
		mode = Main;							// Set New Mode.
		once = 0;								// Reset once flag.
	    break;

//*******************************************************************************
//*
//*   Time_Value
//*
//*	  TODO: Time_Value
//*******************************************************************************
	  case Time_Value:							// Time_Value.
		// Refresh screen only if we have new chars.
		if(laser_hold == 0) {
		  remain_screen();							// Display Main Screen.
		}
		if (incr_flg == 0)
          set_cursor(LINE1, 9, BLINK);
	    if (once == 0) {
	      printf2("*** Time_Value ***\n");
		  monPrint("MNTR", "Time_Value");					// Send Status Message
		  lsr_update_flg = 1;					// Don't Update Laser Values.
		  laser_hold = 0;						// Clear laser_hold var.
		  tmr_update_flg = 1;					// Deactivate Updates to timers.
		  update_num = 0;						// Clear update_num var.
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		  once = 1;								// Set Once Flag.
		  sav_sec = tmr_sec;					// Save Timer Seconds.
		  sav_min = tmr_min;					// Save Timer Minutes.
		}
	    else
		  printf2(".");
	    if ((Timeout_test() == 0) && Timeout_active()) {
	      nobeep_flg = 1;					    // Turn On Beep.
		  tmr_update_flg = 0;					// Re-activate Updates to timers.
		  mode = Soft_PD; 	  					// Set Mode to Soft_PD.
		  once = 0;								// Reset once flag.
		  tmr_sec = sav_sec;					// Restore Timer Seconds.
		  tmr_min = sav_min;					// Restore Timer Minutes.
		  lsr_update_flg = 0;					// Clear Flag.
		} // End If Test two_min_test Failed
		else {
		  key_var = scan_keyboard();			// Scan Keyboard.
		  if (key_var == 0)
		  {
		    laser_hold = 1;						// Set laser_hold only if Laser key released.
		    nobeep_flg = 1;					    // Turn On Beep.
		  }
		  if((key_var > 0) && (laser_hold == 1)) {
            monPrint_Key(key_var);		// Display Key
			laser_hold = 0;						// Set laser_hold only if Laser key released.
			nobeep_flg = 0;					    // Turn Off Beep.
		    switch (key_var) {
			  case UP:
		  	    update_num = 0;						// Clear update_num var.
			    tmr_sec++;	  					// Increment Second Count.
			    if (tmr_sec >= 60) {
				  tmr_min++;
				  if (tmr_min > 99)
				    tmr_min = 99;
				  tmr_sec -= 60;
				}
				mode = Incr_Second;				// Set New Mode.
			    break;

			  case DOWN:
		  	    update_num = 0;						// Clear update_num var.
			    if (tmr_sec == 0) {
				  if (tmr_min != 0) {
				    tmr_sec = 59;
			        if (tmr_min != 0)
				      tmr_min--;
				  }
				}
				else
				  tmr_sec--;				    // Decrement Second Count.
				mode = Decr_Second;				// Set New Mode.
			    break;

			  case RIGHT:
		  	    update_num = 0;						// Clear update_num var.
			    tmr_min++;	  					// Increment Second Count.
				if (tmr_min > 99)
				  tmr_min = 99;
				mode = Incr_Minute;				// Set New Mode.
			    break;

			  case LEFT:
		  	    update_num = 0;						// Clear update_num var.
			    if (tmr_min != 0)
				  tmr_min--;
				mode = Decr_Minute;				// Set New Mode.
			    break;

			  case BACK:
			    tmr_secstr[1] = tmr_secstr[0];
				tmr_secstr[0] = tmr_minstr[1];
				tmr_minstr[1] = tmr_minstr[0];
				tmr_minstr[0] = ' ';
				tmr_min = atoi(tmr_minstr);		// Build new tmr_min.
				tmr_sec = atoi(tmr_secstr);		// Build new tmr_min.
				mode = Remove_1Key;				// Set New Mode.
			    break;

			  case SELECT:
				sprintf(temp_String,"%s:%s", tmr_minstr, tmr_secstr);
				monPrint("SETTIMER", temp_String);					// Send Status Message
				mode = Save_Settings;			// Set New Mode.
		        once = 0;							// Reset once flag.
			    break;

			  case CANCEL:
				tmr_sec = sav_sec;					// Restore Timer Seconds.
				tmr_min = sav_min;					// Restore Timer Minutes.
		  	  	tmr_update_flg = 0;				// Re-activate Updates to timers.
				mode = Main;					// Set New Mode.
		        once = 0;							// Reset once flag.
		  		lsr_update_flg = 0;					// Clear Flag.
			    break;

			  case ZERO:
			  case ONE:
			  case TWO:
			  case THREE:
			  case FOUR:
			  case FIVE:
			  case SIX:
			  case SEVEN:
			  case EIGHT:
			  case NINE:
		        if (update_num == 0) {
		          update_num = 1;						// Set laser_hold only if Laser key released.
                  strcpy(tmr_minstr, "  ");			// Copy a Blank string to tmr_minstr.
                  strcpy(tmr_secstr, "  ");			// Copy a Blank string to tmr_secstr.
			    }
			    tmr_minstr[0] = tmr_minstr[1];
				tmr_minstr[1] = tmr_secstr[0];
				tmr_secstr[0] = tmr_secstr[1];
				char1 = get_numstr(key_var);
			    tmr_secstr[1] = char1[0];
				tmr_min = atoi(tmr_minstr);		// Build new tmr_min.
				tmr_sec = atoi(tmr_secstr);		// Build new tmr_min.
				mode = Buffer_Build;			// Set New Mode.
			    break;

			} // End Switch on key_var
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		  } //Endif Key Found
		} // End If two_min_test active
	    break;

//*******************************************************************************
//*
//*   Incr_Second
//*
//*	  TODO: Incr_Second
//*******************************************************************************
	  case Incr_Second:							// Incr_Second.

//*******************************************************************************
//*
//*   Decr_Second
//*
//*	  TODO: Decr_Second
//*******************************************************************************
	  case Decr_Second:							// Decr_Second.

//*******************************************************************************
//*
//*   Incr_Minute
//*
//*	  TODO: Incr_Minute
//*******************************************************************************
	  case Incr_Minute:							// Incr_Minute.

//*******************************************************************************
//*
//*   Decr_Minute
//*
//*	  TODO: Decr_Minute
//*******************************************************************************
	  case Decr_Minute:							// Decr_Minute.
		printf2("*** Decr_Minute ***\n");
        if (incr_flg == 0) {
          p5_sec_start();						// 0.5 Second Timer Start.
		  incr_flg = 1;							// Set incr_flg.
		}

//*******************************************************************************
//*
//*   Remove_1Key
//*
//*	  TODO: Remove_1Key
//*******************************************************************************
	  case Remove_1Key:							// Remove_1Key.

//*******************************************************************************
//*
//*   Buffer_Build
//*
//*	  TODO: Buffer_Build
//*******************************************************************************
	  case Buffer_Build:						// Buffer_Build.
		printf2("*** Buffer_Build ***\n");
		remain_screen();						// Display Main Screen.
		if (incr_flg == 0)
          set_cursor(LINE1, 9, BLINK);
		key_var = scan_keyboard();				// Scan Keyboard.
	    if ((p5_sec_test() == 0) && (incr_flg == 1)) {
		  if (key_var == UP) {
			tmr_sec++;	  					// Increment Second Count.
			if (tmr_sec >= 60) {
			  tmr_min++;
			  if (tmr_min > 99)
			    tmr_min = 99;
			  tmr_sec -= 60;
			}
		  }
		  else if (key_var == DOWN) {
			if (tmr_sec == 0) {
			  if (tmr_min != 0) {
			    tmr_sec = 59;
			    if (tmr_min != 0)
				  tmr_min--;
			  }
			}
			else
			  tmr_sec--;				    // Decrement Second Count.
		  }
		  else if (key_var == LEFT) {
			if (tmr_min != 0)
			  tmr_min--;
		  }
		  else if (key_var == RIGHT) {
			tmr_min++;	  					// Increment Second Count.
			if (tmr_min > 99)
			  tmr_min = 99;
		  }
		  Delay();							// Delay a little.
//          p5_sec_start();						// 0.5 Second Timer Start.
		} // End If Test two_min_test Failed

        if (key_var == 0) {
		  mode = Time_Value;					// Set New Mode.
		  incr_flg = 0;
		}
	    break;

//*******************************************************************************
//*
//*   Save_Settings
//*
//*	  TODO: Save_Settings
//*******************************************************************************
	  case Save_Settings:						// Save_Settings.
		printf2("*** Save_Settings ***\n");
	    tmr_update_flg = 0;						// Force to zero....Need to update Timer.
    	save_vars();  	 	  					// Save Updated Variables.
		lsr_update_flg = 0;					// Clear Flag.
		tmr_update_flg = 0;						// Re-activate Updates to timers.
		mode = Main;							// Set New Mode.
		once = 0;								// Reset once flag.
	    break;

//*******************************************************************************
//*
//*   Laser_Value
//*
//*	  TODO: Laser_Value
//*******************************************************************************
	  case Laser_Value:							// Laser_Value.
		printf2("*** Laser_Value ***\n");
		monPrint("MNTR", "Laser_Value");					// Send Status Message
 		alsr_update_flg = 1;		 			// Set Flags for Updating.
        if ((prog_num >= SWEEP_STRT) && (prog_num <= SWEEP_REND)) {
  		  sm = 5;	 			  				// Yes..Set sm to 5.
  	      read_sweep2(prog_num);						// Read Sweep Entry.
  		  display_sweep();						// Update String to Display value.
  		}
        else if ((prog_num >= USERSUPR_STRT) && (prog_num <= USERSUPR_REND)) {
  		  sm = 6;	 			  				// Yes..Set sm to 6.
  	      read_macro2(prog_num);						// Read Macro Entry.
          macro1.macro_flg = 0;					// Setup for Editing new Macros
  		  macro1.macro_step = 0;				// Set to First Step.
  		  macro1.minute_flg = 0;				// Set to point to minutes.
  		  display_macro();						// Update String to Display value.
  		}
		if (laser1_disp <= 0)
		{
		  strcpy(lser1_strng, "      0");	    	// Copy Default String.
		}

		if (laser2_disp <= 0)
		{
		  strcpy(lser2_strng, "      0");	    	// Copy Default String.
		}

		if (laser3_disp <= 0)
		{
		  strcpy(lser3_strng, "      0");	    	// Copy Default String.
		}

		if (laser4_disp <= 0)
		{
		  strcpy(lser4_strng, "      0");	    	// Copy Default String.
		}
	    switch (sm) {
		  case 1:
		  mode = Laser1_Value;					// Set New Mode.
		  break;

		  case 2:
		  mode = Laser2_Value;					// Set New Mode.
		  break;

		  case 3:
		  mode = Laser3_Value;					// Set New Mode.
		  break;

		  case 4:
		  mode = Laser4_Value;					// Set New Mode.
		  break;

		  case 5:
		  mode = Laser1_Value;					// Set New Mode.
		  break;

		  case 6:
		  mode = Laser1_Value;					// Set New Mode.
		  break;
		}
		once = 0;								// Reset once flag.
	    break;

//*******************************************************************************
//*
//*   Laser2_Value
//*
//*	  TODO: Laser2_Value
//*******************************************************************************
	  case Laser2_Value:						// Laser2_Value.

//*******************************************************************************
//*
//*   Laser3_Value
//*
//*	  TODO: Laser3_Value
//*******************************************************************************
	  case Laser3_Value:						// Laser3_Value.

//*******************************************************************************
//*
//*   Laser4_Value
//*
//*	  TODO: Laser4_Value
//*******************************************************************************
	  case Laser4_Value:						// Laser4_Value.

//*******************************************************************************
//*
//*   Laser1_Value
//*
//*	  TODO: Laser1_Value
//*******************************************************************************
	  case Laser1_Value:						// Laser1_Value.
		smmain_screen();							// Display Main Screen.
		// Force Cursor to Blink for Active Laser.
		switch (sm)
		{
		  // Laser 1 Settings
		  case 1:
            set_cursor(LINE2, 9, BLINK);
		    break;

		  // Laser 2 Settings
		  case 2:
            set_cursor(LINE2, 19, BLINK);
		    break;

		  // Laser 3 Settings
		  case 3:
            set_cursor(LINE3, 9, BLINK);
		    break;

		  // Laser 4 Settings
		  case 4:
            set_cursor(LINE3, 19, BLINK);
		    break;

		  case 5:
		  case 6:
            set_cursor(LINE2, 9, BLINK);
		    break;
		}

	    if (once == 0) {
		  printf2("*** Laser1_Value ***\n");
		  lsr_update_flg = 1;					// Deactivate Updates to timers.
		  sav_laser1 = laser1_disp;				// Save Laser1.
		  sav_laser2 = laser2_disp;				// Save Laser2.
		  sav_laser3 = laser3_disp;				// Save Laser3.
		  sav_laser4 = laser4_disp;				// Save Laser4.
		  update_num = 0;						// Clear update_num var.
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		  laser_hold = 0;						// Clear laser_hold var.
		  once = 1;								// Set Once Flag.
		}
	    else
		  printf2(".");
	    if ((Timeout_test() == 0) && Timeout_active()) {
	      nobeep_flg = 1;					    // Turn On Beep.
		  lsr_update_flg = 0;					// Re-activate Updates to timers.
 		  alsr_update_flg = 0;		 			// Clear Flag/ Canceled.
		  mode = Soft_PD; 	  					// Set Mode to Soft_PD.
		  once = 0;								// Reset once flag.
		  laser1_disp = sav_laser1;				// Restore Laser1.
		  laser2_disp = sav_laser2;				// Restore Laser2.
		  laser3_disp = sav_laser3;				// Restore Laser3.
		  laser4_disp = sav_laser4;				// Restore Laser4.
		  if ((sm == 5) || (sm == 6)) {			// If sweep or macro, then restore original settings.
		    sm = 1;	   							// Restore to sm to 1;
		  }
		} // End If Test two_min_test Failed
		else {
		  key_var = scan_keyboard();			// Scan Keyboard.
		  if (key_var == 0)
		  {
		    laser_hold = 1;						// Set laser_hold only if Laser key released.
			nobeep_flg = 1;					    // Turn On Beep.
		  }
		  if((key_var > 0) && (laser_hold == 1)) {
            monPrint_Key(key_var);		// Display Key
			laser_hold = 0;						// Set laser_hold only if Laser key released.
			nobeep_flg = 0;					    // Turn Off Beep.
		    switch (key_var) {
			  case UP:
			    switch (sm)
				{
				  // Laser 1 Settings
				  case 1:
				    // No Action.
				    break;

				  // Laser 2 Settings
				  case 2:
					// SM=1...Mode=Laser1.
					update_num = 0;						// Clear update_num var.
					str_chg_to_long2();
					sm = 1;							// Set new sm.
					mode = LSR3_SM1; 				// Set Mode.
					break;

				  // Laser 3 Settings
				  case 3:
				  	// SM=1...Mode=Laser1.
		  	        update_num = 0;						// Clear update_num var.
					str_chg_to_long2();
				    sm = 2;							// Set new sm.
			        mode = LSR3_SM1; 				// Set Mode.
				    break;

				  // Laser 4 Settings
				  case 4:
				  	// SM=2...Mode=Laser2.
		  	        update_num = 0;						// Clear update_num var.
					str_chg_to_long2();
				    sm = 3;							// Set new sm.
			        mode = LSR4_SM2; 				// Set Mode.
				    break;
				  // Sweep Settings
				  case 5:
				  	// SM=5...Mode=Sweep.
			  	    update_num = 0;						// Clear update_num var.
			  	    str_chg_to_long2();
			  	    update_sweep();	   					// Update Sweep Structure.
			  	    mode = LSR3_SM1; 					// Set Mode.
			  	    sweep1.sweep_key++;					// Increment Pointer to next entry.
			  	    if (sweep1.sweep_key >16)
			  	    	sweep1.sweep_key = 0;	 			// If past end, wrap.
			  		display_sweep();					// Update String to Display value.
			  		break;
				  // Macro Settings
				  case 6:
					// SM=6...Mode=Macro.
					update_num = 0;						// Clear update_num var.
					str_chg_to_long2();
					update_macro();	   					// Update Macro Structure.
					mode = LSR3_SM1; 					// Set Mode.
					macro1.macro_flg++;					// Increment pointer and then test.
					if (macro1.macro_flg > 2) {
						macro1.macro_flg = 0;
						macro1.macro_step++;
						if (macro1.macro_step >= UMACRO_LMT)
						    macro1.macro_step = 0;
					}
					if (macro1.macro_flg == 1) 			    // Time Parameter?
						macro1.minute_flg = 0;				// Yes...Set to point to minutes.
					else if (macro1.macro_flg == 2)			// Delay Parameter?
						macro1.minute_flg = 1;				// Yes...Set to point to Seconds.

			  		display_macro();					// Update String to Display value.
			  		break;
				}
		        break;

			  case DOWN:
			    switch (sm)
				{
				  // Laser 1 Settings
				  case 1:
		  	        update_num = 0;						// Clear update_num var.
				  	// sm=3...Mode=Laser3.
					str_chg_to_long2();	  			// Convert Key String.
				    sm = 2;							// Set for Laser 3 Entry.
			        mode = LSR1_SM3; 				// Set Mode.
				    break;

				  // Laser 2 Settings
				  case 2:
		  	        update_num = 0;						// Clear update_num var.
				  	// sm=4...Mode=Laser4.
					str_chg_to_long2();	  			// Convert Key String.
				    sm = 3;							// Set new sm.
			        mode = LSR2_SM4; 			// Set Mode.
				    break;

				  // Laser 3 Settings
				  case 3:
					update_num = 0;						// Clear update_num var.
					// sm=4...Mode=Laser4.
					str_chg_to_long2();	  			// Convert Key String.
					sm = 4;							// Set new sm.
					mode = LSR2_SM4; 			// Set Mode.
				    break;

				  // Laser 4 Settings
				  case 4:
				    // No Action.
				    break;
				  // Sweep Settings
				  case 5:
					// SM=5...Mode=Sweep.
					update_num = 0;						// Clear update_num var.
					str_chg_to_long2();
					update_sweep();	   					// Update Sweep Structure.
					mode = LSR3_SM1; 					// Set Mode.
					if (sweep1.sweep_key == 0)
						sweep1.sweep_key = 16;	 			// If past end, wrap.
					else
						sweep1.sweep_key--;					// Decrement Pointer to previous entry.
			  		display_sweep();					// Update String to Display value.
			  		break;
			  	  // Macro Settings
				  case 6:
					// SM=6...Mode=Macro.
					update_num = 0;						// Clear update_num var.
					str_chg_to_long2();
					update_macro();	   					// Update Sweep Structure.
					mode = LSR3_SM1; 					// Set Mode.
					if (macro1.macro_flg == 0) {
						macro1.macro_flg = 2;
						if (macro1.macro_step == 0)
						    macro1.macro_step = (UMACRO_LMT-1);
						else
						    macro1.macro_step--;
					}
					else
						macro1.macro_flg--;
					if (macro1.macro_flg == 1) 			    // Time Parameter?
						macro1.minute_flg = 0;				// Yes...Set to point to minutes.
					else if (macro1.macro_flg == 2)			// Delay Parameter?
						macro1.minute_flg = 1;				// Yes...Set to point to Seconds.
			  		display_macro();					// Update String to Display value.
			  		break;
				}
			    break;

			  case RIGHT:
			    switch (sm)
				{
				  // Laser 1 Settings
				  case 1:
				    // No Action.
				    break;

				  // Laser 2 Settings
				  case 2:
				    // No Action.
				    break;

				  // Laser 3 Settings
				  case 3:
				    // No Action.
				    break;

				  // Laser 4 Settings
				  case 4:
				    // No Action.
				    break;
				  // Macro Settings
				  case 6:
					// SM=6...Mode=Macro.
					update_num = 0;						// Clear update_num var.
					str_chg_to_long2();
					update_macro();	   					// Update Sweep Structure.
					mode = LSR3_SM1; 					// Set Mode.

					if (macro1.minute_flg == 0)
						macro1.minute_flg = 1;
			  		display_macro();					// Update String to Display value.
			  		break;
				}
			    break;

			  case LEFT:
			    switch (sm)
				{
				  // Laser 1 Settings
				  case 1:
				    // No Action.
				    break;

				  // Laser 2 Settings
				  case 2:
				    // No Action.
				    break;

				  // Laser 3 Settings
				  case 3:
				    // No Action.
				    break;

				  // Laser 4 Settings
				  case 4:
				    // No Action.
				    break;
				  case 6:
				  	// SM=6...Mode=Macro.
		  	        update_num = 0;						// Clear update_num var.
					str_chg_to_long2();
					update_macro();	   					// Update Sweep Structure.
			        mode = LSR3_SM1; 					// Set Mode.

					if (macro1.minute_flg == 1)
					  macro1.minute_flg = 0;
		  			display_macro();					// Update String to Display value.
				    break;
				}
			    break;

			  case BACK:
			    switch (sm)
				{
				  // Laser 1 Settings
				  case 1:
				  case 5:  	 		 				// Sweep String
				    Backspace_Char(lser1_strng, FREQ_STR_LEN);
				    mode = LSR1_RemvKey;			// Set New Mode.
				    break;

				  // Laser 2 Settings
				  case 2:
				    Backspace_Char(lser2_strng, FREQ_STR_LEN);
				    mode = LSR2_RemvKey;			// Set New Mode.
				    break;

				  // Laser 3 Settings
				  case 3:
				    Backspace_Char(lser3_strng, FREQ_STR_LEN);
				    mode = LSR3_RemvKey;			// Set New Mode.
				    break;

				  // Laser 4 Settings
				  case 4:
				    Backspace_Char(lser4_strng, FREQ_STR_LEN);
				    mode = LSR4_RemvKey;			// Set New Mode.
				    break;
				  case 6:
	                switch (macro1.macro_flg)
	                {
	                  case 2:  //BackSpace Delay Time.
	                  case 1:  //BackSpace Execution Time.
					    if (macro1.minute_flg == 0)
						  Backspace_Char(min_str, 2);
						else
						  Backspace_Char(sec_str, 2);
		                break;
					  case 0:
					    Backspace_Char(progwk_str, 3);
						break;
					}
				    break;
				}
			    break;

			  case DELETE:
			    switch (sm)
				{
				  // Laser 1 Settings
				  case 1:
				  case 5:  	 		 				// Sweep String
			        //strcpy(lser1_strng, "        0");	// Copy Default String.
			        strncpy(lser1_strng, "         0", FREQ_STR_LEN);	// Copy Default String.
				    laser1_disp = 0				  ; // Blank Value.
				    mode = LSR1_BlnkLaser;			// Set New Mode.
				    break;

				  // Laser 2 Settings
				  case 2:
			        //strcpy(lser2_strng, "        0");	// Copy Default String.
			        strncpy(lser2_strng, "         0", FREQ_STR_LEN);	// Copy Default String.
				    laser2_disp = 0				  ; // Blank Value.
				    mode = LSR2_BlnkLaser;			// Set New Mode.
				    break;

				  // Laser 3 Settings
				  case 3:
			        //strcpy(lser3_strng, "        0");	// Copy Default String.
			        strncpy(lser3_strng, "         0", FREQ_STR_LEN);	// Copy Default String.
				    laser3_disp = 0				  ; // Blank Value.
				    mode = LSR3_BlnkLaser;			// Set New Mode.
				    break;

				  // Laser 4 Settings
				  case 4:
			        //strcpy(lser4_strng, "        0");	// Copy Default String.
			        strncpy(lser4_strng, "         0", FREQ_STR_LEN);	// Copy Default String.
				    laser4_disp = 0				  ; // Blank Value.
				    mode = LSR4_BlnkLaser;			// Set New Mode.
				    break;
				  case 6:
 	                switch (macro1.macro_flg)
	                {
	                  case 2:  //Blank Delay Time.
	                  case 1:  //Blank Execution Time.
					    strcpy(min_str, "00");
						strcpy(sec_str, "00");
						min_chg = 0;
						sec_chg = 0;
		                break;
					  case 0:
					    strcpy(progwk_str, "000");
						progwk_num = 0;
						break;
					}
				    mode = LSR1_BlnkLaser;			// Set New Mode.
				    break;
				}
			    break;

			  case SELECT:
				str_chg_to_long2();
				if (sm == 5)	   					// Only Update Sweep...if a sweep mode.
					update_sweep();	   					// Update Sweep Structure.
				else if (sm == 6)
					update_macro();					// Update Macro Structure.
				mode = LSR1_SaveLsr;			// Set New Mode.
		        once = 0;							// Reset once flag.
			    break;

			  case CANCEL:
		  	  	lsr_update_flg = 0;				// Re-activate Updates to Lasers.
 				alsr_update_flg = 0;		 	// Clear Flag/ Canceled.
		        laser1_disp = sav_laser1;				// Restore Laser1.
		        laser2_disp = sav_laser2;				// Restore Laser2.
		        laser3_disp = sav_laser3;				// Restore Laser3.
		        laser4_disp = sav_laser4;				// Restore Laser4.
				mode = Main;					// Set New Mode.
		        once = 0;							// Reset once flag.
		  		if ((sm == 5) || (sm == 6)){		// If sweep or macro, then restore original settings.
		          sm = 1;	   							// Restore to sm to 1;
		        }
			    break;

			  case ZERO:
			  case ONE:
			  case TWO:
			  case THREE:
			  case FOUR:
			  case FIVE:
			  case SIX:
			  case SEVEN:
			  case EIGHT:
			  case NINE:
			  case PERIOD:
				char1 = get_numstr(key_var);		// Get New Digit.
				mode = LSR1_BffrBuild;				// Set New Mode.
			    switch (sm)
				{
				  // Laser 1 Settings
				  case 1:
				  case 5:  	 		 				// Sweep String
					if (update_num == 0) {
		              update_num = 1;						// Set laser_hold only if Laser key released.
                      //strcpy(lser1_strng, "         ");	// Copy a Blank string to string.
                      strncpy(lser1_strng, "          ", FREQ_STR_LEN);	// Copy a Blank string to string.
			        }
				    shft_str_left(lser1_strng , FREQ_STR_LEN);		// Shift String Left by one digit.
			        lser1_strng[FREQ_STR_LEN-1] = char1[0];
				    break;

				  // Laser 2 Settings
				  case 2:
					if (update_num == 0) {
		              update_num = 1;						// Set laser_hold only if Laser key released.
                      //strcpy(lser2_strng, "         ");	// Copy a Blank string to string.
                      strncpy(lser2_strng, "          ", FREQ_STR_LEN);	// Copy a Blank string to string.
			        }
				    shft_str_left(lser2_strng , FREQ_STR_LEN);		// Shift String Left by one digit.
			        lser2_strng[FREQ_STR_LEN-1] = char1[0];
				    break;

				  // Laser 3 Settings
				  case 3:
					if (update_num == 0) {
		              update_num = 1;						// Set laser_hold only if Laser key released.
                      //strcpy(lser3_strng, "         ");	// Copy a Blank string to string.
                      strncpy(lser3_strng, "          ", FREQ_STR_LEN);	// Copy a Blank string to string.
			        }
				    shft_str_left(lser3_strng , FREQ_STR_LEN);		// Shift String Left by one digit.
			        lser3_strng[FREQ_STR_LEN-1] = char1[0];
				    break;

				  // Laser 4 Settings
				  case 4:
					if (update_num == 0) {
		              update_num = 1;						// Set laser_hold only if Laser key released.
                      //strcpy(lser4_strng, "         ");	// Copy a Blank string to string.
                      strncpy(lser4_strng, "          ", FREQ_STR_LEN);	// Copy a Blank string to string.
			        }
				    shft_str_left(lser4_strng , FREQ_STR_LEN);		// Shift String Left by one digit.
			        lser4_strng[FREQ_STR_LEN-1] = char1[0];
				    break;
				  case 6:  	 		 				// Sweep String
				    if (char1[0] != '.') {			//Period Illegal for this mode.
 	                 switch (macro1.macro_flg)
	                 {
	                  case 2:  //BackSpace Delay Time.
	                  case 1:  //BackSpace Execution Time.
					    if (macro1.minute_flg == 0) {
					      if (update_num == 0) {
		                    update_num = 1;						// Set laser_hold only if Laser key released.
                            strcpy(min_str, "00");				// Copy a Blank string to string.
			              }
				          shft_str_left(min_str , 2);		// Shift String Left by one digit.
			              min_str[1] = char1[0];
						}
						else {
					      if (update_num == 0) {
		                    update_num = 1;						// Set laser_hold only if Laser key released.
                            strcpy(sec_str, "00");				// Copy a Blank string to string.
			              }
				          shft_str_left(sec_str , 2);		// Shift String Left by one digit.
			              sec_str[1] = char1[0];
						}
		                break;
					  case 0:
					    if (update_num == 0) {
		                  update_num = 1;						// Set laser_hold only if Laser key released.
                          strcpy(progwk_str, "000");				// Copy a Blank string to string.
			            }
				        shft_str_left(progwk_str , 3);		// Shift String Left by one digit.
			            progwk_str[2] = char1[0];
						break;
					 } // EndSwitch (macro1.macro_flg)
					} //EndIf (char1[0] != '.')
				    break;
				} // EndSwitch (sm)
			    break;

			} // End Switch on key_var
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		  } //Endif Key Found
		} // End If two_min_test active
	    break;

//*******************************************************************************
//*
//*   LSR2_SM4
//*
//*	  TODO: LSR2_SM4
//*******************************************************************************
	  case LSR2_SM4:							// LSR2_SM4.

//*******************************************************************************
//*
//*   LSR2_SM1
//*
//*	  TODO: LSR2_SM1
//*******************************************************************************
	  case LSR2_SM1:							// LSR2_SM1.

//*******************************************************************************
//*
//*   LSR2_BffrBuild
//*
//*	  TODO: LSR2_BffrBuild
//*******************************************************************************
	  case LSR2_BffrBuild:						// LSR2_BffrBuild.

//*******************************************************************************
//*
//*   LSR2_RemvKey
//*
//*	  TODO: LSR2_RemvKey
//*******************************************************************************
	  case LSR2_RemvKey:						// LSR2_RemvKey.

//*******************************************************************************
//*
//*   LSR2_BlnkLaser
//*
//*	  TODO: LSR2_BlnkLaser
//*******************************************************************************
	  case LSR2_BlnkLaser:						// LSR2_BlnkLaser.

//*******************************************************************************
//*
//*   LSR3_SM1
//*
//*	  TODO: LSR3_SM1
//*******************************************************************************
	  case LSR3_SM1:							// LSR3_SM1.

//*******************************************************************************
//*
//*   LSR3_SM4
//*
//*	  TODO: LSR3_SM4
//*******************************************************************************
	  case LSR3_SM4:							// LSR3_SM4.

//*******************************************************************************
//*
//*   LSR3_BffrBuild
//*
//*	  TODO: LSR3_BffrBuild
//*******************************************************************************
	  case LSR3_BffrBuild:						// LSR3_BffrBuild.

//*******************************************************************************
//*
//*   LSR3_RemvKey
//*
//*	  TODO: LSR3_RemvKey
//*******************************************************************************
	  case LSR3_RemvKey:						// LSR3_RemvKey.

//*******************************************************************************
//*
//*   LSR3_BlnkLaser
//*
//*	  TODO: LSR3_BlnkLaser
//*******************************************************************************
	  case LSR3_BlnkLaser:						// LSR3_BlnkLaser.

//*******************************************************************************
//*
//*   LSR4_SM2
//*
//*	  TODO: LSR4_SM2
//*******************************************************************************
	  case LSR4_SM2:							// LSR4_SM2.

//*******************************************************************************
//*
//*   LSR4_SM3
//*
//*	  TODO: LSR4_SM3
//*******************************************************************************
	  case LSR4_SM3:							// LSR4_SM3.

//*******************************************************************************
//*
//*   LSR4_BffrBuild
//*
//*	  TODO: LSR4_BffrBuild
//*******************************************************************************
	  case LSR4_BffrBuild:						// LSR4_BffrBuild.

//*******************************************************************************
//*
//*   LSR4_RemvKey
//*
//*	  TODO: LSR4_RemvKey
//*******************************************************************************
	  case LSR4_RemvKey:						// LSR4_RemvKey.

//*******************************************************************************
//*
//*   LSR4BlnkLaser
//*
//*	  TODO: LSR4BlnkLaser
//*******************************************************************************
	  case LSR4_BlnkLaser:						// LSR4BlnkLaser.

//*******************************************************************************
//*
//*   LSR1_SM3
//*
//*	  TODO: LSR1_SM3
//*******************************************************************************
	  case LSR1_SM3:							// LSR1_SM3.

//*******************************************************************************
//*
//*   LSR1_SM2
//*
//*	  TODO: LSR1_SM2
//*******************************************************************************
	  case LSR1_SM2:							// LSR1_SM2.

//*******************************************************************************
//*
//*   LSR1_BffrBuild
//*
//*	  TODO: LSR1_BffrBuild
//*******************************************************************************
	  case LSR1_BffrBuild:						// LSR1_BffrBuild.

//*******************************************************************************
//*
//*   LSR1_RemvKey
//*
//*	  TODO: LSR1_RemvKey
//*******************************************************************************
	  case LSR1_RemvKey:						// LSR1_RemvKey.

//*******************************************************************************
//*
//*   LSR1_BlnkLaser
//*
//*	  TODO: LSR1_BlnkLaser
//*******************************************************************************
	  case LSR1_BlnkLaser:						// LSR1_BlnkLaser.
		printf2("*** LSR1_BlnkLaser ***\n");
		smmain_screen();						// Display Main Screen.
		// Force Cursor to Blink for Active Laser.
		switch (sm)
		{
		  // Laser 1 Settings
		  case 1:
            set_cursor(LINE2, 9, BLINK);
		    break;

		  // Laser 2 Settings
		  case 2:
            set_cursor(LINE2, 19, BLINK);
		    break;

		  // Laser 3 Settings
		  case 3:
            set_cursor(LINE3, 9, BLINK);
		    break;

		  // Laser 4 Settings
		  case 4:
            set_cursor(LINE3, 19, BLINK);
		    break;
		}
		key_var = scan_keyboard();				// Scan Keyboard.
        if (key_var == 0) {
		  mode = Laser1_Value;					// Set New Mode.
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		}
	    break;

//*******************************************************************************
//*
//*   LSR2_SaveLsr
//*
//*	  TODO: LSR2_SaveLsr
//*******************************************************************************
	  case LSR2_SaveLsr:						// LSR2_SaveLsr.

//*******************************************************************************
//*
//*   LSR3_SaveLsr
//*
//*	  TODO: LSR3_SaveLsr
//*******************************************************************************
	  case LSR3_SaveLsr:						// LSR3_SaveLsr.

//*******************************************************************************
//*
//*   LSR4_SaveLsr
//*
//*	  TODO: LSR4_SaveLsr
//*******************************************************************************
	  case LSR4_SaveLsr:						// LSR4_SaveLsr.

//*******************************************************************************
//*
//*   LSR1_SaveLsr
//*
//*	  TODO: LSR1_SaveLsr
//*******************************************************************************
	  case LSR1_SaveLsr:						// LSR1_SaveLsr.
		printf2("*** LSR1_SaveLsr ***\n");
		str_chg_to_long2();						// Update Last Var\Modified.
	    lsr_update_flg = 0;						// Re-activate Updates to lasers.
		if (sm == 6) {							// If macro, then restore original settings.
		  sm = 1;	   							// Restore to sm to 1;
		  // Save Settings to EEPROM.
		  x = 0;
		  while (x < UMACRO_LMT) {
		    if ((macro2.mac_entry[x].delay.minutes == 0) &&
			    (macro2.mac_entry[x].delay.seconds == 0) &&
			    (macro2.mac_entry[x].Time.minutes == 0) &&
			    (macro2.mac_entry[x].Time.seconds == 0))
			  break;
			x++;
		  }
		  macro2.num_entries = x;

		  update_macro();	   					// Update Macro Structure.
		  write_macro(prog_num);		// Write Updated Data to Macro Entry.
		  // Cleanup Macro vars.
          macro1.macro_flg = 0;					// Setup for running Macros
		  macro1.macro_step = 0;				// Set to First Step.
		  macro1.minute_flg = 0;				// Set to point to minutes.
		}
		else if (sm == 5) {							// If sweep, then restore original settings.
		  sm = 1;	   							// Restore to sm to 1;
		  // Save Settings to EEPROM.
		  if ((sweep2.sweep_low == 0)  ||
		      (sweep2.sweep_high == 0)) {
  			set_cursor(LINE2, 0, NOCURSOR);
    		strcpy(tempstr, "ERR. Init Values");
			write_lcd(tempstr);
			for (x=0; x<55; x++) {
			  Delay();		   	   		    // Delay for 2 Seconds.
			}
		  	lsr_update_flg = 0;				// Re-activate Updates to Lasers.
 			alsr_update_flg = 0;		 	// Clear Flag/ Canceled.
		    laser1_disp = sav_laser1;				// Restore Laser1.
		    laser2_disp = sav_laser2;				// Restore Laser2.
		    laser3_disp = sav_laser3;				// Restore Laser3.
		    laser4_disp = sav_laser4;				// Restore Laser4.
			mode = Main;					// Set New Mode.
		    once = 0;							// Reset once flag.
		  	if (sm == 5) {						// If sweep, then restore original settings.
		       sm = 1;	   							// Restore to sm to 1;
			   // Restore from EEPROM the original settings.
		    }
		  }
		  else {
		    update_sweep();	   					// Update Sweep Structure.
		    write_sweep(prog_num, sweep2);					// Write Updated Data to Sweep Entry.
		  }
		}
		else {
		  data2.entry_flg = entry_flg;
		  strcpy(data2.string1, save_str);
		  data2.laser1_time = laser1_disp;
		  data2.laser2_time = laser2_disp;
		  data2.laser3_time = laser3_disp;
		  data2.laser4_time = laser4_disp;
		  write_entry(prog_num, data2);  	 		// Write New Entry.
		}
		sweep_flg = 0;						// Deactivate any previous Sweep Mode flags.
		init_laser(prog_num, INITIALIZE);		// Start Laser to Load Settings.
	    mode = Main;	  						// Set New Mode.
 		alsr_update_flg = 0;		 			// Clear Flags/ Done.
		once = 0;								// Reset once flag.
	    break;

//*******************************************************************************
//*
//*   New_Prog
//*
//*	  TODO: New_Prog
//*******************************************************************************
/*	  case New_Prog:							// New_Prog.
	    if (once == 0) {
		  printf2("*** New_Prog ***\n");
		  laser_hold = 0;						// Clear laser_hold var.
	      New_Prog_Screen();						// Display Screen.
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		  once = 1;								// Set Once Flag.
		}
	    else
		  printf2(".");
		key_var = scan_keyboard();				// Scan Keyboard.
	    if ((Timeout_test() == 0) && Timeout_active()) {
		  mode = Soft_PD; 	  					// Set Mode to Soft_PD.
		  once = 0;								// Reset once flag.
		} // End If Test two_min_test Failed
		if (key_var == 0)
		  laser_hold = 1;						// Set laser_hold only if Laser key released.
		if((key_var > 0) && (laser_hold == 1)) {
		  if (key_var == CANCEL) {
		    mode = Main;	  						// Set New Mode.
		    once = 0;								// Reset once flag.
		  }
		  else if(key_var == SELECT) {
		    mode = New_Prog_SM1;					// Set New Mode.
		    once = 0;								// Reset once flag.
		  }
		}
	    break;  */

//*******************************************************************************
//*
//*   New_Prog_SM1
//*
//*	  TODO: New_Prog_SM1
//*******************************************************************************
/*	  case New_Prog_SM1:						// New_Prog_SM1.
		printf2("*** New_Prog_SM1 ***\n");
		remain_screen();						// Display Main Screen.
		key_var = scan_keyboard();				// Scan Keyboard.
        if (key_var == 0) {
		  mode = Laser_Value;					// Set New Mode.
		  sm = 1;								// Set Sub-Mode.
		}
	    break;  */

//*******************************************************************************
//*
//*   Delete_Prog
//*
//*	  TODO: Delete_Prog
//*******************************************************************************
	  case Delete_Prog:							// Delete_Prog.
	    if (once == 0) {
		  printf2("*** Delete_Prog ***\n");
		  monPrint("MNTR", "Delete_Prog");					// Send Status Message
	      Delete_Prog_Screen();					// Display Screen.
			if(Timeout_active())
				Timout_start();					// TimeOut Timer Start.
		  laser_hold = 0;						// Clear laser_hold var.
		  once = 1;								// Set Once Flag.
		}
	    else
		  printf2(".");
		key_var = scan_keyboard();				// Scan Keyboard.
	    if ((Timeout_test() == 0) && Timeout_active()) {
	      nobeep_flg = 1;					    // Turn On Beep.
		  mode = Soft_PD; 	  					// Set Mode to Soft_PD.
		  once = 0;								// Reset once flag.
		} // End If Test two_min_test Failed
		if (key_var == 0)
		{
		  laser_hold = 1;						// Set laser_hold only if Laser key released.
		  nobeep_flg = 1;					    // Turn On Beep.
		}
		if((key_var > 0) && (laser_hold == 1)) {
          monPrint_Key(key_var);		// Display Key
		  laser_hold = 0;						// Set laser_hold only if Laser key released.
		  nobeep_flg = 0;					    // Turn Off Beep.
		  if (key_var == CANCEL) {
			monPrint("DELETE_PROG", "NO");					// Send Status Message
		    mode = Main;	  						// Set New Mode.
		    once = 0;								// Reset once flag.
		  }
		  else if(key_var == SELECT) {
			monPrint("DELETE_PROG", "YES");					// Send Status Message
		    mode = Blank_Settings;					// Set New Mode.
		    once = 0;								// Reset once flag.
		  }
		}
	    break;

//*******************************************************************************
//*
//*   LOW_BAT
//*
//*	  TODO: LOW_BAT
//*******************************************************************************
	  case LOW_BAT:							    // Delete_Prog.
	    if (once != 2) {
		  printf2("*** LOW_BAT ***\n");
		  laser_off();	  	   					// Turn-Off Laser.
		  cnt_dwn_flg = 0;						// Arm Timer to Deactivate Timer.
		  tmr_update_flg = 2;					// Arm Update to Deactivate Var Update.
  		  restore_vars();  			   	 		// Restore Key Variables.
		  mode = LOW_BAT;						// Force mode.
          LowBat_Screen();					// Display Screen.
		  two_sec_start();						// Two Minute Timer Start.
		  once = 2;								// Set Once Flag.
		}
	    else
		  printf2(".");
	    if (two_sec_test() == 0) {
		  mode = Soft_PD; 	  					// Set Mode to Soft_PD.
		  once = 0;								// Reset once flag.
		} // End If Test two_min_test Failed
	    break;

//*******************************************************************************
//*
//*   Blank_Settings
//*
//*	  TODO: Blank_Settings
//*******************************************************************************
	  case Blank_Settings:						// Blank_Settings.
		remain_screen();							// Display Main Screen.
	    if (once == 0) {
	      printf2("*** Blank_Settings ***\n");
#ifdef CLW
	      if ((prog_num > CUSTOM4_END) && (prog_num <= USER_END)) {
#else
	      if ((prog_num > CUSTOM_END) && (prog_num <= USER_END)) {
#endif
            if (prog_num <= USER_REND) {
			  once = 1;								// Set Once Flag.
			  strcpy(data2.string1, "");
			  data2.laser1_time = 0;
			  data2.laser2_time = 0;
			  data2.laser3_time = 0;
			  data2.laser4_time = 0;
			  data2.entry_flg = 0;
			  write_entry(prog_num, data2);  	 		// Write New Entry.
            }
          }
		  else if ((prog_num >= USERSUPR_STRT) && (prog_num <= USERSUPR_REND)) {
			  macro2.num_entries = 0;
			  strcpy(macro2.string1, MACRO_STRING);
			  for (x=0; x<UMACRO_LMT; x++) {
				  macro2.mac_entry[x].delay.minutes = 0;
				  macro2.mac_entry[x].delay.seconds = 0;
				  macro2.mac_entry[x].Time.minutes = 0;
				  macro2.mac_entry[x].Time.seconds = 0;
				  macro2.mac_entry[x].num_audio = 0;
				  macro2.mac_entry[x].protocol = 0;
			  }
			  write_macro(prog_num);
		  }
		  else if ((prog_num >= SWEEP_STRT) && (prog_num <= SWEEP_REND)) {
			  sweep2.tmr_min = 0;
			  sweep2.tmr_sec = 0;
			  sweep2.sweep_low = 10;
			  sweep2.sweep_high = 1000;
			  for (x=0; x<SWEEP_LIMIT; x++) {
				  sweep2.laser_time[x] = 0;
			  }
			  write_sweep(prog_num, sweep2);					// Write Updated Data to Sweep Entry.
		  }
		} // EndIf (once == 0)
	    else
		  printf2(".");
		key_var = scan_keyboard();				// Scan Keyboard.
        if (key_var == 0) {
		  mode = Main;							// Set New Mode.
		  once = 0;								// Reset once flag.
		}
	    break;

	} // End Case on Mode.
//	save_vars();  	 	  					    // Save Updated Variables.
	proc_buffer();								// Process All Outstanding Events.
#ifdef DEBUGGR
	debug1(15);
#endif

	// Kick the Watchdog Timer.
    WDR(); //this prevents a timout on enabling

	// Process Sweep Flag.
	if ((sweep_flg > 0) && (sweep_flg< 0xF0)) {
	  //  Update Sweep Display....
	  sweep_disp();
//      sweep_flg = 0;   	   	 		   		   	  // Reset Sweep Flag.
	  if (sweep1.sweep_flg == 1) {
	    if (sweep1.sweep_dir == 0) {
	      lser2_time -= (sweep1.sweep_lmt * sweep_flg);		  // Decrement by sweep1_sweep_lmt;
		  // Clear cntrl_flg.
		  cntrl_flg = 0;

		  laser1P_time = calc_sweeptimeP( lser2_time, LaserDiode0);
		  if(laser1P_time.Special1 == MODE_ERROR)
		  {
			  laser1P_time.Special1 = 0;
			  laser1P_time.cnt_value =  0;
			  laser1P_time.prescaler = 0;
		  }
		  laser2P_time = calc_sweeptimeP( lser2_time, LaserDiode1);
		  if(laser2P_time.Special1 == MODE_ERROR)
		  {
			  laser2P_time.Special1 = 0;
			  laser2P_time.cnt_value =  0;
			  laser2P_time.prescaler = 0;
		  }
		  Sweep_Tst = (OSC_FREQUENCY/2)/lser2_time;
		  laser3P_time = calc_sweeptimeP( lser2_time, LaserDiode2);
		  if(laser3P_time.Special1 == MODE_ERROR)
		  {
			  laser3P_time.Special1 = 0;
			  laser3P_time.cnt_value =  0;
			  laser3P_time.prescaler = 0;
		  }
		  laser4P_time = calc_sweeptimeP( lser2_time, LaserDiode3);
		  if(laser4P_time.Special1 == MODE_ERROR)
		  {
			  laser4P_time.Special1 = 0;
			  laser4P_time.cnt_value =  0;
			  laser4P_time.prescaler = 0;
		  }
		  write_plmLasers( laser1P_time, laser2P_time, laser3P_time, laser4P_time );
		}
	    else {
	      lser2_time += (sweep1.sweep_lmt * sweep_flg);		  // Increment by sweep1_sweep_lmt;
		  // Clear cntrl_flg.
		  cntrl_flg = 0;
		  laser1P_time = calc_sweeptimeP( lser2_time, LaserDiode0);
		  if(laser1P_time.Special1 == MODE_ERROR)
		  {
			  laser1P_time.Special1 = 0;
			  laser1P_time.cnt_value =  0;
			  laser1P_time.prescaler = 0;
		  }
		  laser2P_time = calc_sweeptimeP( lser2_time, LaserDiode1);
		  if(laser2P_time.Special1 == MODE_ERROR)
		  {
			  laser2P_time.Special1 = 0;
			  laser2P_time.cnt_value =  0;
			  laser2P_time.prescaler = 0;
		  }
		  Sweep_Tst = (OSC_FREQUENCY/2)/lser2_time;
		  laser3P_time = calc_sweeptimeP( lser2_time, LaserDiode2);
		  if(laser3P_time.Special1 == MODE_ERROR)
		  {
			  laser3P_time.Special1 = 0;
			  laser3P_time.cnt_value =  0;
			  laser3P_time.prescaler = 0;
		  }
		  laser4P_time = calc_sweeptimeP( lser2_time, LaserDiode3);
		  if(laser4P_time.Special1 == MODE_ERROR)
		  {
			  laser4P_time.Special1 = 0;
			  laser4P_time.cnt_value =  0;
			  laser4P_time.prescaler = 0;
		  }
		  write_plmLasers( laser1P_time, laser2P_time, laser3P_time, laser4P_time );
		}
	    sweep1.sweep_cnt = 1;		  			  // Reset Count for next tick.
	  }
	  else {
	    if (sweep1.sweep_dir == 0) {
	      lser2_time -= sweep_flg;	   	  	 				  // Decrement by 1;
		  // Clear cntrl_flg.
		  cntrl_flg = 0;
		  laser1P_time = calc_sweeptimeP( lser2_time, LaserDiode0);
		  if(laser1P_time.Special1 == MODE_ERROR)
		  {
			  laser1P_time.Special1 = 0;
			  laser1P_time.cnt_value =  0;
			  laser1P_time.prescaler = 0;
		  }
		  laser2P_time = calc_sweeptimeP( lser2_time, LaserDiode1);
		  if(laser2P_time.Special1 == MODE_ERROR)
		  {
			  laser2P_time.Special1 = 0;
			  laser2P_time.cnt_value =  0;
			  laser2P_time.prescaler = 0;
		  }
		  Sweep_Tst = (OSC_FREQUENCY/2)/lser2_time;
		  laser3P_time = calc_sweeptimeP( lser2_time, LaserDiode2);
		  if(laser3P_time.Special1 == MODE_ERROR)
		  {
			  laser3P_time.Special1 = 0;
			  laser3P_time.cnt_value =  0;
			  laser3P_time.prescaler = 0;
		  }
		  laser4P_time = calc_sweeptimeP( lser2_time, LaserDiode3);
		  if(laser4P_time.Special1 == MODE_ERROR)
		  {
			  laser4P_time.Special1 = 0;
			  laser4P_time.cnt_value =  0;
			  laser4P_time.prescaler = 0;
		  }
		  write_plmLasers( laser1P_time, laser2P_time, laser3P_time, laser4P_time );
		}
	    else {
	      lser2_time += sweep_flg;	   	  	 				  // Increment by 1;
		  // Clear cntrl_flg.
		  cntrl_flg = 0;

		  laser1P_time = calc_sweeptimeP( lser2_time, LaserDiode0);
		  if(laser1P_time.Special1 == MODE_ERROR)
		  {
			  laser1P_time.Special1 = 0;
			  laser1P_time.cnt_value =  0;
			  laser1P_time.prescaler = 0;
		  }
		  laser2P_time = calc_sweeptimeP( lser2_time, LaserDiode1);
		  if(laser2P_time.Special1 == MODE_ERROR)
		  {
			  laser2P_time.Special1 = 0;
			  laser2P_time.cnt_value =  0;
			  laser2P_time.prescaler = 0;
		  }
		  Sweep_Tst = (OSC_FREQUENCY/2)/lser2_time;
		  laser3P_time = calc_sweeptimeP( lser2_time, LaserDiode2);
		  if(laser3P_time.Special1 == MODE_ERROR)
		  {
			  laser3P_time.Special1 = 0;
			  laser3P_time.cnt_value =  0;
			  laser3P_time.prescaler = 0;
		  }
		  laser4P_time = calc_sweeptimeP( lser2_time, LaserDiode3);
		  if(laser4P_time.Special1 == MODE_ERROR)
		  {
			  laser4P_time.Special1 = 0;
			  laser4P_time.cnt_value =  0;
			  laser4P_time.prescaler = 0;
		  }
		  write_plmLasers( laser1P_time, laser2P_time, laser3P_time, laser4P_time );
		}
	    sweep1.sweep_cnt = sweep1.sweep_lmt;		  // Reset Count for next tick.
	  }
      sweep_flg = 0;   	   	 		   		   	  // Reset Sweep Flag.
	  switch(sweep1.sweep_state)
	  {
	    case 0:									  // Initial Sweep
	      if (sweep1.sweep_dir == 0) {
		    if (sweep1.t_freq1 >= lser2_time) {
	  		  sweep_disp();	 								  // Update Display
		      sweep1.sweep_state++;		   		  // Increment to next state.
			  sweep1.sweep_dir = 1;
			}
		  }
	      else {
		    if (sweep1.t_freq1 <= lser2_time) {
	  		  sweep_disp();	 								  // Update Display
		      sweep1.sweep_state++;		   		  // Increment to next state.
			  sweep1.sweep_dir = 0;
			}
		  }
		  break;
	    case 1:									  // Sweep Back.
	      if (sweep1.sweep_dir == 0) {
		    if (sweep1.t_freq2 >= lser2_time) {
	  		  sweep_disp();	 								  // Update Display
		      sweep1.sweep_state++;		   		  // Increment to next state.
			  sweep1.sweep_dir = 1;
			}
		  }
	      else {
		    if (sweep1.t_freq2 <= lser2_time) {
	  		  sweep_disp();	 						   // Update Display
		      sweep1.sweep_state++;		   		  	   // Increment to next state.
			  sweep1.sweep_dir = 0;
			}
		  }
		  break;
	    case 2:									  	   // Final Sweep
	      if (sweep1.sweep_dir == 0) {
		    if (sweep1.t_freq3 >= lser2_time) {
		      if (sweep1.sweep_ptr >= 16) {
	  		    sweep_disp();	 					  // Update Display
		  	    laser_off();	   	   				  // Turn-Off Laser.
				sweep_flg = 0;						  //Turn Off Sweep.
	            cnt_dwn_flg = 0;	 		 	 	  // Stop Event and disable Sweep Ticks.
			    fast_flg = 0;
				sweep1.sweep_ptr = 0;				  // Force Sweep off.
			  }
			  else {
		        setup_sweep(lser2_time);	 	 	  // Setup next Frequency


				  laser1P_time = calc_sweeptimeP( lser2_time, LaserDiode0);
				  if(laser1P_time.Special1 == MODE_ERROR)
				  {
					  laser1P_time.Special1 = 0;
					  laser1P_time.cnt_value =  0;
					  laser1P_time.prescaler = 0;
				  }
				  laser2P_time = calc_sweeptimeP( lser2_time, LaserDiode1);
				  if(laser2P_time.Special1 == MODE_ERROR)
				  {
					  laser2P_time.Special1 = 0;
					  laser2P_time.cnt_value =  0;
					  laser2P_time.prescaler = 0;
				  }
				  Sweep_Tst = (OSC_FREQUENCY/2)/lser2_time;
				  laser3P_time = calc_sweeptimeP( lser2_time, LaserDiode2);
				  if(laser3P_time.Special1 == MODE_ERROR)
				  {
					  laser3P_time.Special1 = 0;
					  laser3P_time.cnt_value =  0;
					  laser3P_time.prescaler = 0;
				  }
				  laser4P_time = calc_sweeptimeP( lser2_time, LaserDiode3);
				  if(laser4P_time.Special1 == MODE_ERROR)
				  {
					  laser4P_time.Special1 = 0;
					  laser4P_time.cnt_value =  0;
					  laser4P_time.prescaler = 0;
				  }
				  write_plmLasers( laser1P_time, laser2P_time, laser3P_time, laser4P_time );
		        sweep_disp();						  // Update Display
			  } // EndElse (sweep1.sweep_ptr >= 16)
			} // EndIf (sweep1.t_freq3 >= lser2_time)
		  } // EndIf (sweep1.sweep_dir == 0)
	      else {
		    if (sweep1.t_freq3 <= lser2_time) {
		      if (sweep1.sweep_ptr >= 16) {
	  		    sweep_disp();	 					  // Update Display
		  	    laser_off();	   	   					// Turn-Off Laser.
				sweep_flg = 0;						  //Turn Off Sweep.
	            cnt_dwn_flg = 0;	 		 	 	  // Stop Event and disable Sweep Ticks.
			    fast_flg = 0;
			  } // EndIf (sweep1.sweep_ptr >= 16)
			  else {
		        setup_sweep(lser2_time);	 	 	  // Setup next Frequency


				  laser1P_time = calc_sweeptimeP( lser2_time, LaserDiode0);
				  if(laser1P_time.Special1 == MODE_ERROR)
				  {
					  laser1P_time.Special1 = 0;
					  laser1P_time.cnt_value =  0;
					  laser1P_time.prescaler = 0;
				  }
				  laser2P_time = calc_sweeptimeP( lser2_time, LaserDiode1);
				  if(laser2P_time.Special1 == MODE_ERROR)
				  {
					  laser2P_time.Special1 = 0;
					  laser2P_time.cnt_value =  0;
					  laser2P_time.prescaler = 0;
				  }
				  Sweep_Tst = (OSC_FREQUENCY/2)/lser2_time;
				  laser3P_time = calc_sweeptimeP( lser2_time, LaserDiode2);
				  if(laser3P_time.Special1 == MODE_ERROR)
				  {
					  laser3P_time.Special1 = 0;
					  laser3P_time.cnt_value =  0;
					  laser3P_time.prescaler = 0;
				  }
				  laser4P_time = calc_sweeptimeP( lser2_time, LaserDiode3);
				  if(laser4P_time.Special1 == MODE_ERROR)
				  {
					  laser4P_time.Special1 = 0;
					  laser4P_time.cnt_value =  0;
					  laser4P_time.prescaler = 0;
				  }
				  write_plmLasers( laser1P_time, laser2P_time, laser3P_time, laser4P_time );
				  sweep_disp();	 					  // Update Display
			  } // EndElse (sweep1.sweep_ptr >= 16)
			} // EndIf (sweep1.t_freq3 <= lser2_time)
		  } // EndElse (sweep1.sweep_dir == 0)
		  break;
	  } // End Switch
	} // EndIf ((sweep_flg > 0) && (sweep_flg< 0xF0)) // Process Sweep Flag

	// Kick the Watchdog Timer.
    WDR(); //this prevents a timout on enabling

	// Update Timers and Ticks.
    if (ticker >= TICKER_LIMIT) {
      ticker = 0;
      // Place 1 Second Functions here.
      if(p5_second > 0)
	    p5_second--;
      if(two_second > 0)
	    two_second--;
      if(five_second > 0)
	    five_second--;
      if(two_minute > 0)
	    two_minute--;
      if(five_minute > 0)
	    five_minute--;
      if(var_timer > 0)
    	  var_timer--;
	  if(cnt_dwn_flg > 0) {
	    d_tick++;
		if (d_tick >= 2) {
		  d_tick = 0;
	      if (tmr_sec == 0)
	      {
	        if (tmr_min == 0)
	        {
			  if (fast_flg != 4) 				// This is added for Sweep Mode.
			  {
		        cnt_dwn_flg = 0;
			  }
	        }
		    else {
		      tmr_sec = 59;
		      tmr_min -= 1;
			  opmin_cnt++; 	 					 // Increment Operational Minute Count
		    }
	      }
	      else
	        tmr_sec--;
	      // Update Battery Status and Time Display.
	      //update_time();
		} // End d_tick Test.
	  }
    } // End Timer Tests.
#ifdef DEBUGGR
	debug1(5);
#endif
    // _StackCheck(); 		   	 	  	   // Check Stack for Overflow
	Mntr_Loop_Clr();					   // Check to clear outstanding Character in Monitor Code.
    /*******************************************************************
     *
     * PLM_MONITOR: Last thing is handle the USART5 Port for messages
     *
     ******************************************************************/
	//accurate_delay(10);
	/*if (gp_sci5_rx_state != RX_COMPLETE)
	{
		sci5_strikeCnt++;
		if (sci5_strikeCnt >= SCI5_STRIKE_MAX)
		{
			sci5_strikeCnt = 0;
			gp_sci5_rx_state = RX_COMPLETE;
			if (R_SCI5_Enable() != 0)
				monPrint("ERR", "R_SCI5_Enable()");					// Send Status Message
		}
	} */
#if 0
	if (R_SCI5_Serial_Rceive( &tempchar, RX_CHAR) == 0x00)
	{
		//We have new Char...Save it.
		tempcharSave = tempchar;
		// Now get next Char
	    tempchar = 0x00;
	    R_SCI5_Serial_Rceive( &tempchar, RX_CHAR);
		//accurate_delay(100);
		if (tempcharSave != 0x00)
		{
			*tempString_ptr++ = tempcharSave;
			if (tempcharSave == 0x0d)
			{
				sscanf(tmpString,"%s %s",cmdString,parm1);
				strcpy(tmpString, "");
				MonitorParse2 (cmdString, parm1);
				// Clean out Buffers and reset.
				tempString_ptr = tmpString;
				for (x=0; x<80; x++)
				{
					tmpString[x] = 0x00;
					cmdString[x] = 0x00;
					parm1[x] = 0x00;
				}
				// Force tempchar to clear.
				tempcharSave = 0x00;
			} // EndIf (tempchar == 0x0d)
		} // EndIf (*tempchar != 0x00)
	} // EndIf (R_SCI5_Serial_Rceive( tempchar, RX_CHAR) == 0x00)
#else
	if (R_SCI5_Serial_Rceive( tmpString, RX_STRING2) == 0x00)
	{
		sscanf(tmpString,"%s %s",cmdString,parm1);
		strcpy(tmpString, "");
		MonitorParse2 (cmdString, parm1);
		// Clean out Buffers and reset.
		//tempString_ptr = tmpString;
		for (x=0; x<80; x++)
		{
			tmpString[x] = 0x00;
			cmdString[x] = 0x00;
			parm1[x] = 0x00;
		}
	} // EndIf (R_SCI5_Serial_Rceive( tempchar, RX_CHAR) == 0x00)
#endif
  } // MAIN_END End While
}

void Clr_Mode( void )
{
	laser_hold = 0; 			  	    // Only one Keypress is legal.
	nobeep_flg = 0;					    // Turn Off Beep Till mode determined.
	//once = 0;							// Clear once flag for next mode.
}

void Over_Ride( void )
{
	OverRide = 1;
}
/* End user code. Do not edit comment generated here */
