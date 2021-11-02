/*
 * Laser_Control.c
 *
 *  Created on: Feb 7, 2015
 *      Author: rpruitt76
 */
//****************************************************************************
//*
//*	Laser_Control
//*
//* These routines are used to control the Laser Diodes. The routines are as follows:
//*	void init_laser():	Read entry from EEPROM and init timer.
//*	void run_laser():	Called from Timer int and runs Lasers.
//* struct laser_entry *read_entry(): Read Laser Struct from EEPROM.
//* void write_entry(): Write Laser Struct to EEPROM.
//* void save_vars():   Save Key Vars to EEPROM.
//* void restore_vars(): Restore Key Vars from EEPROM.
//* void laser_off():   Turn off all Laser Processing.
//* void run_laser():   Handle Timer 2 Interrupt for Lasers.
//*
//****************************************************************************
//* Laser Pulsar Embedded Software
//* Date: December 27, 2003
//* Designer: Ralph Pruitt
//* Property: LED Healing Light, INC.
//* Copyright: December 2003
//* Description: This software is used with the 1st release of the "Laser Pulsar".
//* This product is used in cold Laser Therapy. This design supports this product
//* to read the keyboard, display important Information via the LCD Display, and
//* to energize the four 635nm Laser Diodes with modulation frequencies between
//* 1Hz and 100Khz.
//*****************************************************************************
//*****************************************************************************
//*
//* Module Includes
//*
//*****************************************************************************
#include "r_flash_rx_if.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LaserP.h"
#include <math.h>
#include "r_cg_mtu3.h"
#include "hmc832.h"
#include "gpio.h"

//*****************************************************************************
//*
//* Signal Bit Definitions
//*
//*****************************************************************************
//Signal bit definitions
#define	Bat_Sense	7	//PA7
#define	LCD_BEn		6	//PA6
#define	LCD_BLCK	5	//PA5
#define	Blght_LCD	4	//PA4
#define	LCD_C3		3	//PA3
#define	LCD_C2		2	//PA2
#define	LCD_C1		1	//PA1
#define	LCD_C0		0	//PA0
#define	Col7		7	//PB7
#define	Col6		6	//PB6
#define	Col5		5	//PB5
#define	Col4		4	//PB4
#define	Col3		3	//PB3
#define	Col2		2	//PB2
#define	Col1		1	//PB1
#define	Col0		0	//PB0
#define	Row1		1	//PC1
#define	Row0		0	//PC0
#define	Laser_pwr	7	//PD7
#define	Row2		5	//PD5

//*****************************************************************************
//*
//* routine: quick_laser
//* Date: 	 February 15, 2004
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* This routine performs a quick load of laser Values from EEPROM. Note this should
//* be used to update the screen and not to prepare timers for operation of a laser.
//* INPUT:
//*		    entry_num:	 1-499:  Read Entry from EEPROM and setup.
//*
//*****************************************************************************
void quick_laser(unsigned int entry_num) {
	struct laser_entry *data1;
	// Test entry_num for restart command.
	WDR(); //this prevents a timout on enabling
	// Read Entry from EEPROM.
	if (((entry_num >= CSTMSUPR_STRT) && (entry_num <= CSTMSUPR_REND))
			|| ((entry_num >= USERSUPR_STRT) && (entry_num <= USERSUPR_REND))) {
		macro1.macro1 = read_macro(prog_num);		// Read Sweep Entry.
		// Save entry_num.
		macro1.prog_save = entry_num;	 	// Save old Program Number.
		if (macro1.macro1->num_entries > 0) {
			entry_num = macro1.macro1->mac_entry[0].protocol;
			// Now validate is legal protocol...
#ifdef CLW
			if ((entry_num < CUSTOM_START) || (entry_num > CUSTOM3_END))
#else
	  if ((entry_num < CUSTOM_START) || (entry_num > CUSTOM_END))
#endif
				entry_num = SPACE_VAL;				   // Set to illegal number
			quick_laser(entry_num);				// Recursuvely call quick_laser.
		} else {
			entry_num = SPACE_VAL;				   // Set to illegal number
			quick_laser(entry_num);				// Recursuvely call quick_laser.
		}
		macro1.protocol_save = entry_num;		   	  // Save Display Protocol
		// Restore entry_num.
		entry_num = macro1.prog_save;	 		  // Restore old Program Number.
	} else if ((entry_num >= SWEEP_STRT) && (entry_num <= SWEEP_REND)) {
		sweep1.sweep1 = read_sweep(entry_num);		// Read Sweep Entry.
		// Save Float Data for LCD Display Later.
		laser1_disp = sweep1.sweep1->sweep_low;
		laser2_disp = sweep1.sweep1->sweep_low;
		laser3_disp = sweep1.sweep1->sweep_low;
		laser4_disp = sweep1.sweep1->sweep_low;
	} else {
		data1 = read_entry(entry_num);			// Read Current Mode Entry.
		// Save Float Data for LCD Display Later.
		laser1_disp = data1->laser1_time;
		laser2_disp = data1->laser2_time;
		laser3_disp = data1->laser3_time;
		laser4_disp = data1->laser4_time;
		strcpy(save_str, data1->string1);
		entry_flg = data1->entry_flg;
	}
}

//*****************************************************************************
//*
//* routine: init_laser
//* Date: 	 December 1, 2003
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* This routine takes the indicated entry_num and reads this from EEPROM. It then
//* sets the Timer2 to the correct resolution. It then calculates the correct count
//* for each laser based on the entry. It finally activates the timer for Laser
//* operation.
//* INPUT:
//*		    entry_num:	 0: 	Restart Laser with current parameters
//*						 1-499:  Read Entry from EEPROM and setup.
//*			run_flg:     0:		Initialize Variables Only...No Laser On.
//*						 1:		Initialize and run Laser.
//* OUTPUT:
//*       					    Returns:   0 - No Errors were found
//*		  								  -1 - Parameter Error: Passed paramter
//*										       was illegal.
//*										  -2 - Busy Timeout: After command sent to
//*										  	   Reconfig...Waited for Busy to deassert.
//*											   This never occurred...Timeout.
//*										  -3 - Parameter Failure: Read of written
//*										       parameter did not match to what was
//*											   written to reconfig.
//*
//*****************************************************************************
int init_laser(unsigned int entry_num, unsigned char run_flg) {
	//float Sweep_Tst;
	unsigned long sweep_limit;
	unsigned int segments, x;
	unsigned long laser1_time;
	unsigned long laser2_time;
	unsigned long laser2S_time;
	unsigned long laser3_time;
	unsigned long laser4_time;
	struct plmLaser_entry laser1P_time;
	struct plmLaser_entry laser2P_time;
	struct plmLaser_entry laser3P_time;
	struct plmLaser_entry laser4P_time;
	//struct plmLaserE_entry laser3P_time;
	//struct plmLaserE_entry laser4P_time;
	struct laser_entry *data1;

	// Test entry_num for restart command.
	WDR(); //this prevents a timout on enabling
	/*******************************************************************************
	 *
	 * Custom Macros
	 *
	 ******************************************************************************/
	if (((entry_num >= CSTMSUPR_STRT) && (entry_num <= CSTMSUPR_REND))
			|| ((entry_num >= USERSUPR_STRT) && (entry_num <= USERSUPR_REND))) {
		macro1.macro1 = read_macro(entry_num);		// Read Sweep Entry.
		//If run_flg at LASERINIT then we must assume we are in run mode.
		if (run_flg == LASERSINIT) {
			// Test save_flg and verify first pass for new event.
			if (macro1.save_flg == 0) {
				macro1.save_flg = 1;

				// Force macro_flg active.
				macro_flg = 1;

				// Save Timers.
				macro1.save_min = tmr_min;	  	// Save Old Minutes.
				macro1.save_sec = tmr_sec;		// Save Old Seconds.

				// Save entry_num.
				macro1.prog_save = entry_num;	 	// Save old Program Number.
			} //First Pass save_flg==0
			if (macro1.macro1->num_entries > 0) {
				// Test....Are we restarting a paused event?
				if (macro_flg == 2) {
					macro_flg = 1; 	   		   	    // Reset flg back.
					// Yes...Just find current program and restart...no change.
					///Back Vars up one step now....
					if (macro1.macro_flg == 0) {
						// Turn off beep for delay cycle.
						nobeep_flg = 0;	// Turn Off Beep Till mode determined.
						force_beep(50);				// Beep Once for this key.
						entry_num = SPACE_VAL;			// Set to illegal number
						macro1.protocol_save = entry_num;// Save Display Protocol
						init_laser(entry_num, run_flg);	// Recursuvely call init_laser.
					} //ENDIF Delay Phase....macro_flg==0
					else {
						// We have a new Protocol to process.
						entry_num = macro1.macro1->mac_entry[macro1.macro_step
								- 1].protocol;
						macro1.protocol_save = entry_num;// Save Display Protocol
						init_laser(entry_num, run_flg);	// Recursuvely call init_laser.
					} //ENDELSE Normal Run....More Steps
				} //ENDIF.....Restart Test.
				else if (macro_flg == 3) { ///We are restarting from a Timer Mode.
					macro_flg = 1; 	   		   	    // Reset flg back.
					// We have finished current protocol.....Increment pointer to next protocol.
					macro1.macro_step++;
					if (macro1.macro_step > macro1.macro1->num_entries) {
						// Turn on beep...We are done.
						nobeep_flg = 1;					    	// Turn On Beep.
						//We are done....Time to cleanup
						macro_flg = 0;		   		  		// Turn Macros off.
						macro1.save_flg = 0;
						macro1.macro_step = 0;
						macro1.macro_flg = 0;
						// Restore entry_num.
						entry_num = macro1.prog_save;// Restore old Program Number.
						// Restore Timers.
						tmr_min = macro1.save_min;	  	// Restore Old Minutes.
						tmr_sec = macro1.save_sec;		// Restore Old Seconds.
					} //ENDIF End Run...No more steps
					else {
						// Turn on beep...New Protocol.
						nobeep_flg = 1;					    	// Turn On Beep.
						// Set macro_flg for next iteration.
						macro1.macro_flg = 1;
						// We have a new Protocol to process.
						entry_num = macro1.macro1->mac_entry[macro1.macro_step
								- 1].protocol;
						// Now validate is legal protocol...
#ifdef CLW
						if ((entry_num < CUSTOM_START)
								|| (entry_num > CUSTOM3_END))
#else
	          if ((entry_num < CUSTOM_START) || (entry_num > CUSTOM_END))
#endif
							entry_num = SPACE_VAL;		// Set to illegal number
						// Update Timer with correct delay.
						tmr_min =
								macro1.macro1->mac_entry[macro1.macro_step - 1].Time.minutes;
						tmr_sec =
								macro1.macro1->mac_entry[macro1.macro_step - 1].Time.seconds;

						macro1.protocol_save = entry_num;// Save Display Protocol
						init_laser(entry_num, run_flg);	// Recursuvely call init_laser.
					} //ENDELSE Normal Run....More Steps
				} //ENDIF.....Restart Test.
				else {
					//No....Perform Normal operation.

					if (macro1.macro_flg == 0) {
						// We have finished current protocol.....Increment pointer to next protocol.
						macro1.macro_step++;
						if (macro1.macro_step > macro1.macro1->num_entries) {
							// Turn on beep...We are done.
							nobeep_flg = 1;					    // Turn On Beep.
							//We are done....Time to cleanup
							macro_flg = 0;		   		  	// Turn Macros off.
							macro1.save_flg = 0;
							macro1.macro_step = 0;
							macro1.macro_flg = 0;
							// Restore entry_num.
							entry_num = macro1.prog_save;// Restore old Program Number.
							// Restore Timers.
							tmr_min = macro1.save_min;	 // Restore Old Minutes.
							tmr_sec = macro1.save_sec;	// Restore Old Seconds.
						} //ENDIF End Run...No more steps
						else {
							// Turn on beep...New Protocol.
							nobeep_flg = 1;					    // Turn On Beep.
							// Set macro_flg for next iteration.
							macro1.macro_flg = 1;
							// We have a new Protocol to process.
							entry_num =
									macro1.macro1->mac_entry[macro1.macro_step
											- 1].protocol;
							// Now validate is legal protocol...
#ifdef CLW
							if ((entry_num < CUSTOM_START)
									|| (entry_num > CUSTOM3_END))
#else
	            if ((entry_num < CUSTOM_START) || (entry_num > CUSTOM_END))
#endif
								entry_num = SPACE_VAL;	// Set to illegal number
							// Update Timer with correct delay.
							tmr_min = macro1.macro1->mac_entry[macro1.macro_step
									- 1].Time.minutes;
							tmr_sec = macro1.macro1->mac_entry[macro1.macro_step
									- 1].Time.seconds;

							macro1.protocol_save = entry_num;// Save Display Protocol
							init_laser(entry_num, run_flg);	// Recursuvely call init_laser.
						} //ENDELSE Normal Run....More Steps
					} //ENDIF Delay Phase....macro_flg==0
					else {
						// Clear macro_flg for next iteration.
						macro1.macro_flg = 0;
						// Turn off beep for delay cycle.
						nobeep_flg = 0;	// Turn Off Beep Till mode determined.
						// If this is the last step....Force short on delay...
						if (macro1.macro_step == macro1.macro1->num_entries) {
							// Update Timer with ZERO delay.
							tmr_min = 0;
							tmr_sec = 0;
						} else {
							// Update Timer with correct delay.
							tmr_min = macro1.macro1->mac_entry[macro1.macro_step
									- 1].delay.minutes;
							tmr_sec = macro1.macro1->mac_entry[macro1.macro_step
									- 1].delay.seconds;
						}
						// We need this test for any Macros that have a zero.zero delay...then start the next step.
						if ((tmr_min == 0) && (tmr_sec == 0)) {
							// We have finished current protocol.....Increment pointer to next protocol.
							macro1.macro_step++;
							if (macro1.macro_step
									> macro1.macro1->num_entries) {
								// Turn on beep...We are done.
								nobeep_flg = 1;					// Turn On Beep.
								//We are done....Time to cleanup
								macro_flg = 0;		   		 // Turn Macros off.
								macro1.save_flg = 0;
								macro1.macro_step = 0;
								macro1.macro_flg = 0;
								// Restore entry_num.
								entry_num = macro1.prog_save;// Restore old Program Number.
								// Restore Timers.
								tmr_min = macro1.save_min;// Restore Old Minutes.
								tmr_sec = macro1.save_sec;// Restore Old Seconds.
							} //ENDIF End Run...No more steps
							else {
								// Turn on beep...New Protocol.
								nobeep_flg = 1;					// Turn On Beep.
								// Set macro_flg for next iteration.
								macro1.macro_flg = 1;
								// We have a new Protocol to process.
								entry_num =
										macro1.macro1->mac_entry[macro1.macro_step
												- 1].protocol;
								// Now validate is legal protocol...
#ifdef CLW
								if ((entry_num < CUSTOM_START)
										|| (entry_num > CUSTOM3_END))
#else
	              if ((entry_num < CUSTOM_START) || (entry_num > CUSTOM_END))
#endif
									entry_num = SPACE_VAL;// Set to illegal number
								// Update Timer with correct delay.
								tmr_min =
										macro1.macro1->mac_entry[macro1.macro_step
												- 1].Time.minutes;
								tmr_sec =
										macro1.macro1->mac_entry[macro1.macro_step
												- 1].Time.seconds;

								macro1.protocol_save = entry_num;// Save Display Protocol
								init_laser(entry_num, run_flg);	// Recursuvely call init_laser.
							} //ENDELSE Normal Run....More Steps
						} else {
							entry_num = SPACE_VAL;		// Set to illegal number
							macro1.protocol_save = entry_num;// Save Display Protocol
							init_laser(entry_num, run_flg);	// Recursuvely call init_laser.
						}
					} //ENDELSE Normal Protocol Mode...macro_flg==1

				} //ENDELSE.....Restart Test.
			} //ENDIF num_entries>0
			else {
				entry_num = SPACE_VAL;					// Set to illegal number
				macro1.protocol_save = entry_num;		// Save Display Protocol
				init_laser(entry_num, run_flg);	// Recursuvely call init_laser.
			} //ENDELSE No num_entries>0
		} //ENDIF run_flg==LASERINIT
		else {
			// Save entry_num.
			macro1.prog_save = entry_num;	 	// Save old Program Number.
			if (macro1.macro1->num_entries > 0) {
				entry_num = macro1.macro1->mac_entry[0].protocol;
				// Now validate is legal protocol...
#ifdef CLW
				if ((entry_num < CUSTOM_START) || (entry_num > CUSTOM3_END))
#else
	      if ((entry_num < CUSTOM_START) || (entry_num > CUSTOM_END))
#endif
					entry_num = SPACE_VAL;				// Set to illegal number
				macro1.protocol_save = entry_num;		// Save Display Protocol
				init_laser(entry_num, run_flg);	// Recursuvely call init_laser.
			} else {
				entry_num = SPACE_VAL;					// Set to illegal number
				macro1.protocol_save = entry_num;		// Save Display Protocol
				init_laser(entry_num, run_flg);	// Recursuvely call init_laser.
			}
			// Restore entry_num.
			entry_num = macro1.prog_save;	 	// Restore old Program Number.
		} //ELSE run_flg==LASERINIT
	} //ENDIF MACRO Program
	else {
		/**************************************************************************
		 *
		 * Sweep Protocols
		 *
		 *************************************************************************/
		// Read Entry from EEPROM.
		if ((entry_num >= SWEEP_STRT) && (entry_num <= SWEEP_REND)) {
			if (sweep_flg != 0xF0) {
				sweep1.sweep1 = read_sweep(entry_num);		// Read Sweep Entry.
				// OK lets calculate how many 20msec ticks we have right now.
				sweep_limit = tmr_sec + (tmr_min * 60);
				sweep_limit *= 19;

				// Now determine how many Timer segements we have.
				segments = 1;
				for (x = 0; x < 15; x++) {
					if (sweep1.sweep1->laser_time[x] != 0)
						segments++;
				}
				// If segments is 1, there are no intermediate segments....multiply by 3.
				if (segments == 1)
					sweep1.sweep_tlmt = sweep_limit * 3;
				else
					// Else...Set the size of the count limit based on segments and 10msec ticks.
					sweep1.sweep_tlmt = sweep_limit / segments;

				// Calculate Laser2 Time.
				laser2S_time = calc_sweeptime(sweep1.sweep1->sweep_low);
				sweep1.sweep_ptr = 1;

				// Find and setup first valid Frequency to use
				setup_sweep(laser2S_time);
				sweep_flg = 0;
				//Set Resolution of timer based on 2Mhz clock.
				WDR(); //this prevents a timout on enabling
				if (run_flg == LASERSINIT) {
					fast_flg = 4;	  			// Set for Sweep IRQ processing.
					sweep_disp();	 			    // Update Display
//            beep_ArpUp();					// Beep Speaker to indicate Laser Start.
				} else {
					fast_flg = 0;					// Force fast_flg to off.
					sweep1.sweep_ptr = 0;			// Set for Display.
				}
			} //End of Unique for new Sweep Mode.
			else {
				laser2S_time = lser2S_time;		   // Reset back to old value.
				sweep_flg = 0;  	  	  // Force Back to a normal sweep Mode.
				fast_flg = 4;	  				// Set for Sweep IRQ processing.
				sweep_disp();	 			       // Update Display
				// Clear cntrl_flg.
				cntrl_flg = 0;

				laser_flg = 1;	 			   // New Event Set laser_flg.
				// Send Data to FPGA and Prep for Lasers On.
				laser1P_time = calc_sweeptimeP(lser2S_time, LaserDiode0);
				if (laser1P_time.Special1 == MODE_ERROR)
					return -1;
				laser2P_time = calc_sweeptimeP(lser2S_time, LaserDiode1);
				if (laser2P_time.Special1 == MODE_ERROR)
					return -1;
				//Sweep_Tst = (OSC_FREQUENCY / 2) / lser2S_time;
				laser3P_time = calc_sweeptimeP(lser2S_time, LaserDiode2);
				if (laser3P_time.Special1 == MODE_ERROR)
					return -1;
				laser4P_time = calc_sweeptimeP(lser2S_time, LaserDiode3);
				if (laser4P_time.Special1 == MODE_ERROR)
					return -1;
				write_plmLasers(laser1P_time, laser2P_time, laser3P_time, laser4P_time);
				return 0;
			} //End of Sweep Mode Paused
			  // Clear cntrl_flg.
			cntrl_flg = 0;
		} //EndIf ((entry_num >= SWEEP_STRT) && (entry_num <= SWEEP_REND))
		//*
		//* End Find Resolution for timer for Sweep Mode
		//*
		else {
			//**********************************************************
			//*
			//* Mark III Calculations
			//*
			//**********************************************************
			data1 = read_entry(entry_num);			// Read Current Mode Entry.

			// Clear cntrl_flg.
			cntrl_flg = 0;
			// Test Frequency and if needed, set cntrl_flg to get prime frequency from HW.
			//NOTE: cntrl_flg allows us to set a direct pipe from the Oscillator to
			// the output pin....2/8/15 RP
			if (data1->laser1_time > (float) ((OSC_FREQUENCY / 4) * 1.1)) {
				cntrl_flg |= 0x01;
			}
			laser1_time = calc_sweeptime(data1->laser1_time);
			//NOTE: cntrl_flg allows us to set a direct pipe from the Oscillator to
			// the output pin....2/8/15 RP
			// Test Frequency and if needed, set cntrl_flg to get prime frequency from HW.
			if (data1->laser2_time > (float) ((OSC_FREQUENCY / 4) * 1.1)) {
				cntrl_flg |= 0x02;
			}
			laser2_time = calc_sweeptime(data1->laser2_time);

			//NOTE: cntrl_flg allows us to set a direct pipe from the Oscillator to
			// the output pin. This will not be needed since this has a frequency
			// multiplier...2/8/15 RP
			if (data1->laser3_time > (float) ((OSC_FREQUENCY / 4) * 1.1)) {
				cntrl_flg |= 0x04;
			}
			laser3_time = calc_sweeptime(data1->laser3_time);

			//NOTE: cntrl_flg allows us to set a direct pipe from the Oscillator to
			// the output pin. This will not be needed since this has a frequency
			// multiplier...2/8/15 RP
			// Test Frequency and if needed, set cntrl_flg to get prime frequency from HW.
			laser4_time = calc_sweeptime(data1->laser4_time);
			if (data1->laser4_time > (float) ((OSC_FREQUENCY / 4) * 1.1)) {
				cntrl_flg |= 0x08;
			}

			//**********************************************************
			//*
			//* END PLM PLUS Calculations
			//*
			//**********************************************************
		} // EndElse ((entry_num >= SWEEP_STRT) && (entry_num <= SWEEP_REND))

		WDR(); //this prevents a timout on enabling
		// Update Key Variables from new data.
		lser1_time = laser1_time;
		lser2_time = laser2_time;
		lser3_time = laser3_time;
		lser4_time = laser4_time;
		laser1_count = lser1_time;	 // Laser 1 Count.
		laser2_count = lser2_time;	 // Laser 2 Count.
		laser3_count = lser3_time;	 // Laser 3 Count.
		laser4_count = lser4_time;	 // Laser 4 Count.

		// Save Key Variables to EEPROM.
		WDR(); //this prevents a timeout on enabling
		save_vars();

		// If run_flg set then setup to run this event.
		if (entry_num == 0) {
			//printf2("init_laser: entry_num=0");
			if (run_flg == LASERSINIT) {
				//printf2(" LASERINIT");
				beep_ArpUp();			// Beep Speaker to indicate Laser Start.
				laser_flg = 1;	 			   // New Event Set laser_flg.
				// Send Data to FPGA to turn on Laser Continuous.
				lasers_on();
			}
			//printf2("\n");
			return 0;
		} //EndIf (entry_num == 0)
		else
		{
			laser1P_time = calc_sweeptimeP(lser1_time, LaserDiode0);
			laser1P_time.laser_Freq = data1->laser1_time;	// Load Structure with Freq for HF Setup.
			if (laser1P_time.Special1 == MODE_ERROR) {
				//printf2("init_laser: calc_sweeptimeP() for Laser1 Failed with MODE_ERROR.\n");
				return -1;
			}
			laser2P_time = calc_sweeptimeP(lser2_time, LaserDiode1);
			laser2P_time.laser_Freq = data1->laser2_time;	// Load Structure with Freq for HF Setup.
			if (laser2P_time.Special1 == MODE_ERROR) {
				//printf2("init_laser: calc_sweeptimeP() for Laser2 Failed with MODE_ERROR.\n");
				return -1;
			}
			laser3P_time = calc_sweeptimeP(lser3_time, LaserDiode2);
			laser3P_time.laser_Freq = data1->laser3_time;	// Load Structure with Freq for HF Setup.
			if (laser3P_time.Special1 == MODE_ERROR) {
				//printf2("init_laser: calc_sweeptimeP() for Laser3 Failed with MODE_ERROR.\n");
				return -1;
			}
			laser4P_time = calc_sweeptimeP(lser4_time, LaserDiode3);
			laser4P_time.laser_Freq = data1->laser4_time;	// Load Structure with Freq for HF Setup.
			if (laser4P_time.Special1 == MODE_ERROR) {
				//printf2("init_laser: calc_sweeptimeP() for Laser4 Failed with MODE_ERROR.\n");
				return -1;
			}
			if (run_flg == LASERSINIT) {
				printf2("init_laser: LASERSINIT\n");
				beep_ArpUp();			// Beep Speaker to indicate Laser Start.
				laser_flg = 1;	 			   // New Event Set laser_flg.
				// Send Data to FPGA and Prep for Lasers On.
				write_plmLasers(laser1P_time, laser2P_time, laser3P_time,
						laser4P_time);
			}
			return 0;
		} // End Else If prog_num == 0
	} //ENDELSE MACRO Program
	return 0;
}

//*****************************************************************************
//*
//* routine: laser_off
//* Date: 	 December 27, 2003
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* This routine turns off and deactivates all Laser Processing.
//*
//*****************************************************************************
void laser_off(void) {
	laser_flg = 0;	 			   // End Event. Clear laser_flg.
	// Deactivate Laser Timers.
	lasers_off();

	// Reset Sweep Variables
	fast_flg = 0;
//	sweep_flg = 0;

	// Clear all counters for next time.
	laser1_count = 0;	 // Laser 1 Count.
	laser2_count = 0;	 // Laser 2 Count.
	laser3_count = 0;	 // Laser 3 Count.
	laser4_count = 0;	 // Laser 4 Count.

	beep_ArpDn();					// Beep Speaker to indicate Laser Stop.
}

//*****************************************************************************
//*
//* routine: read_sweep
//* Date: 	 June 24, 2005
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* This routine is used to read the indicated entry from the Data Flash.
//*
//* INPUT:
//*   None.
//*
//* OUTPUT:
//*   Pointer to Sweep Structure: Returns a pointer to the Sweep Structure
//*                               retrieved from EEPROM.
//*****************************************************************************
struct sweep_entry* read_sweep(unsigned int entry_num) {
	int address;
	static struct sweep_entry temp2;// Declare Static Structure to be written.

	if ((entry_num >= SWEEP_STRT) && (entry_num <= SWEEP_REND)) {
		entry_num -= SWEEP_STRT;	   	    // Adjust entry to start of table.

		address = (uint) &sweep1_data;// Get the address of the start of Sweep Variables.
		address = address + (entry_num * sizeof(sweep1_data)); // Adjust address for correct entry.

		EEPROM_READ((uchar*) address, (uchar*) &temp2, sizeof(temp2));// Retrieve the data from EEPROM.
		//OLD    EEPROM_READ(address, temp2);	  		// Retrieve the data from EEPROM.
		return (&temp2);	   			// Return the address of the structure.
	}
	return (&temp2);	   				// Return the address of the structure.
}

//*****************************************************************************
//*
//* routine: read_sweep2
//* Date: 	 July 5, 2005
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* This routine is used to read the indicated entry from the Data Flash.
//*
//* INPUT:
//*   Sweep Structure to be modified.
//*
//* OUTPUT:
//*   None.
//*****************************************************************************
void read_sweep2(unsigned int entry_num) {
	int address;

	if ((entry_num >= SWEEP_STRT) && (entry_num <= SWEEP_REND)) {
		entry_num -= SWEEP_STRT;	   	    // Adjust entry to start of table.

		address = (uint) &sweep1_data;// Get the address of the start of Sweep Variables.
		address = address + (entry_num * 70); // Adjust address for correct entry.

		EEPROM_READ((uchar*) address, (uchar*) &sweep2, sizeof(sweep2));// Retrieve the data from EEPROM.
		//OLD    EEPROM_READ(address, sweep2);	  		// Retrieve the data from EEPROM.
	}
}

//*****************************************************************************
//*
//* routine: read_macro
//* Date: 	 June 12, 2006
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* This routine is used to read the indicated entry from the Data Flash.
//*
//* INPUT:
//*   uint entry_num - Entry Number to read.
//*
//* OUTPUT:
//*   Pointer to Sweep Structure: Returns a pointer to the Sweep Structure
//*                               retrieved from EEPROM.
//*****************************************************************************
void read_macro2(unsigned int entry_num) {
//  int address, x;
	int address;
//  struct user_macro temp1;					// Declare struct to read a user_macro.

	if ((entry_num >= USERSUPR_STRT) && (entry_num <= USERSUPR_REND)) {
		entry_num -= USERSUPR_STRT;	   	    // Adjust entry to start of table.
		address = (uint) &macro1_data;// Get the address of the start of Sweep Variables.
		address = address + (entry_num * sizeof(macro2)); // Adjust address for correct entry.
		EEPROM_READ((uchar*) address, (uchar*) &macro2, sizeof(macro2));// Retrieve the data from EEPROM.
		//OLD    EEPROM_READ(address, macro2);	  		// Retrieve the data from EEPROM.
	}
}

//*****************************************************************************
//*
//* routine: write_entry
//* Date: 	 December 27, 2003
//* Author:  Ralph Pruitt
//* Updated: February 7, 2015
//* This routine is used to write the indicated entry to Data Flash.
//*
//* INPUT:
//*   entry_num:  1-60 - Entry Number of Laser Data to read.
//*   Laser Structure: Structure containing timing values for all lasers.
//*****************************************************************************
void write_entry(unsigned int entry_num, struct laser_entry data1) {
	char tempstr[10];
	int x;
	int address;
	struct laseru_entry temp1;		// Declare Static Structure to be written.

#ifdef CLW
	if ((entry_num > CUSTOM4_END) && (entry_num <= USER_END)) {
		if (entry_num <= USER_REND) {
			entry_num -= (CUSTOM4_END + 1); // Adjust entry_num for Custom Numbers skipped
#else
      if ((entry_num > CUSTOM_END) && (entry_num <= USER_END)) {
        if (entry_num <= USER_REND) {
          entry_num -= (CUSTOM_END+1);   			// Adjust entry_num for Custom Numbers skipped
#endif
			address = (uint) &laser0_data;// Get the address of the start of Sweep Variables.
			address = address + (entry_num * sizeof(laser0_data)); // Adjust address for correct entry.
			//Create laseru_entry from laser_entry.
			temp1.laser1_time = data1.laser1_time;
			temp1.laser2_time = data1.laser2_time;
			temp1.laser3_time = data1.laser3_time;
			temp1.laser4_time = data1.laser4_time;
			for (x = 0; x < 9; x++) {
				tempstr[x] = data1.string1[x + 3];
			}
			tempstr[9] = 0;
			strncpy(temp1.string1, tempstr, FREQ_STR_LEN+1);// add string to temp2 structure.
			temp1.entry_flg = data1.entry_flg;
			EEPROM_WRITE((uint32_t) &temp1, (uint32_t) address, sizeof(temp1));	// Write the data to EEPROM.
			//OLD      EEPROM_WRITE(address, temp1);		    // Write the data to EEPROM.
		}
	}
}

//*****************************************************************************
//*
//* routine: write_macro
//* Date: 	 June 24, 2005
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* This routine is used to write the user macro data entry to Data Flash.
//*
//* INPUT:
//*   Laser Structure: Structure containing timing values for all lasers.
//*****************************************************************************
//void write_macro(unsigned int entry_num, struct user_macro data1)
void write_macro(unsigned int entry_num) {
	int address;
	if ((entry_num >= USERSUPR_STRT) && (entry_num <= USERSUPR_REND)) {
		entry_num -= USERSUPR_STRT;	   	    // Adjust entry to start of table.
		address = (uint) &macro1_data;// Get the address of the start of Sweep Variables.
		address = address + (entry_num * sizeof(macro2)); // Adjust address for correct entry.
		EEPROM_WRITE((uint32_t) &macro2, (uint32_t) address, sizeof(macro2));// Write the data to EEPROM.
		//OLD    EEPROM_WRITE(address, macro2);	  		// Retrieve the data from EEPROM.
	}
}

//*****************************************************************************
//*
//* routine: write_sweep
//* Date: 	 June 24, 2005
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* This routine is used to write the sweep data entry to Data Flash.
//*
//* INPUT:
//*   Laser Structure: Structure containing timing values for all lasers.
//*****************************************************************************
void write_sweep(unsigned int entry_num, struct sweep_entry data1) {
	int address;
	if ((entry_num >= SWEEP_STRT) && (entry_num <= SWEEP_REND)) {
		entry_num -= SWEEP_STRT;	   	    // Adjust entry to start of table.

		address = (uint) &sweep1_data;// Get the address of the start of Sweep Variables.
		address = address + (entry_num * sizeof(data1)); // Adjust address for correct entry.

		EEPROM_WRITE((uint32_t) &data1, (uint32_t) address, sizeof(data1));	// Write the data to EEPROM.
		//OLD    EEPROM_WRITE(address, data1);	  		// Retrieve the data to EEPROM.
	}
}

//*****************************************************************************
//*
//* routine: calc_sweeptimeE
//* Date: 	 February 8, 2015
//* Updated: February 8, 2015
//* Author:  Ralph Pruitt
//* Calculate New Frequency count based on passed Frequency. This also
//* Involves determining the optimum parameters for this event.
//*
//*****************************************************************************
#define MIN_FREQ_MULTIPLY	4000000		// Set as 4,000,000.
struct plmLaserE_entry calc_sweeptimeE(float frequency1,
		unsigned long passed_cnt, int LaserNumber) {
	char tempstr[80];
	struct plmLaserE_entry temp2;
	struct plmLaser_entry temp3;
	unsigned long temp1;
	unsigned long Save_Cnt;
	float Error = 0;
	float calc_error;
	float Test_Freq, Test_Freq2, Save_Freq;
	int mode;

	Error = 0;

#ifdef MN_LASER
	printf2("*****************************************\n");
	sprintf(tempstr,"calc_sweeptimeE  Cnt:%ld Laser:%d\n", passed_cnt, LaserNumber);
	printf2(tempstr);
#endif
	// 1. Determine best multiplier quotient for Operation for this frequency
	// Test Value...If zero, then we return a zero cnt.
	// Test 1X
	Test_Freq = frequency1;
	temp1 = passed_cnt;
#ifdef MN_LASER
	sprintf(tempstr,"  Freq:%f\n", frequency1);
	printf2(tempstr);
#endif
	// If we are greater than 30MHz...Force to 60MHz..Ensures accuracy.
	if (Test_Freq > ((float) OSC_FREQUENCY / 4))
		Test_Freq2 = ((float) OSC_FREQUENCY / 2);
	else
		Test_Freq2 = ((float) OSC_FREQUENCY / 2) / (float) temp1;
#ifdef MN_LASER
	sprintf(tempstr,"   Test_Freq2:%f  Test_Freq2+1:%f  Test_Freq:%f Save_Cnt:%ld\n", Test_Freq2, Test_Freq2+1, Test_Freq );
	printf2(tempstr);
#endif
	// If Frequency requested is greater than 60MHz. This mode will not work. Set ERROR.
	if (frequency1 > (float) OSC_FREQUENCY / 2) {
		Error = 10000;
	} else {
		Error = fabs((Test_Freq / (Test_Freq2 + 1)) - 1);
	}
	//if(Error>=1)			// Normalize Error to fraction.
	//	Error -= 1;
	mode = MULTIPLY_1X;	// Set mode to current mode
	Save_Cnt = temp1;		// This could be the final count.
//	Save_Freq = frequency1;
	Save_Freq = Test_Freq2;
#ifdef MN_LASER
	sprintf(tempstr,"   MULTIPLY_1X:  Error:%f  mode:%d Save_Cnt:%ld\n", Error, mode, Save_Cnt);
	printf2(tempstr);
#endif
	if (frequency1 > MIN_FREQ_MULTIPLY) {
		// Test 2X
		Test_Freq = frequency1 / 2;
		temp1 = ((float) OSC_FREQUENCY / 2) / (float) Test_Freq;
		// If we are greater than 30MHz...Force to 60MHz..Ensures accuracy.
		if (Test_Freq > ((float) OSC_FREQUENCY / 4))
//			Test_Freq2 = ((float)OSC_FREQUENCY/2);
			Test_Freq2 = ((float) OSC_FREQUENCY / 4);
		else
			Test_Freq2 = ((float) OSC_FREQUENCY / 2) / (float) temp1;
#ifdef MN_LASER
		sprintf(tempstr,"   Test_Freq2:%f  Test_Freq2+1:%f  Test_Freq:%f Save_Cnt:%ld\n", Test_Freq2, Test_Freq2+1, Test_Freq );
		printf2(tempstr);
#endif
		// If Frequency requested is greater than 60MHz(30MHz). This mode will not work. Set ERROR.
//		if (Test_Freq2 > (float)OSC_FREQUENCY/2)
		if (Test_Freq2 > (float) OSC_FREQUENCY / 4) {
			calc_error = 10000;
		} else {
			// Test Against max frequency. If this causes too high, error
			if ((Test_Freq2 * 2) > MAX_MULT_FREQ) {
				calc_error = 10000;
			} else {
				calc_error = fabs((Test_Freq / (Test_Freq2 + 1)) - 1);
			}
		}
#ifdef MN_LASER
		sprintf(tempstr,"   calc_error:%f  Error:%f\n", calc_error, Error );
		printf2(tempstr);
#endif
		if (calc_error < Error)	// Test Error and see if this mode is better.
				{
			mode = MULTIPLY_2X;	// Set mode to current mode
			Error = calc_error;
			Save_Cnt = temp1;		// This could be the final count.
			Save_Freq = Test_Freq2;
		}
#ifdef MN_LASER
		sprintf(tempstr,"   MULTIPLY_2X:  Error:%f  mode:%d Save_Cnt:%ld\n", Error, mode, Save_Cnt);
		printf2(tempstr);
#endif

		// Test 2.5X
		Test_Freq = frequency1 / 2.5;
		temp1 = ((float) OSC_FREQUENCY / 2) / (float) Test_Freq;
		// If we are greater than 30MHz...Force to 60MHz..Ensures accuracy.
		if (Test_Freq > ((float) OSC_FREQUENCY / 4))
//			Test_Freq2 = ((float)OSC_FREQUENCY/2);
			Test_Freq2 = ((float) OSC_FREQUENCY / 4);
		else
			Test_Freq2 = ((float) OSC_FREQUENCY / 2) / (float) temp1;
#ifdef MN_LASER
		sprintf(tempstr,"   Test_Freq2:%f  Test_Freq2+1:%f  Test_Freq:%f Save_Cnt:%ld\n", Test_Freq2, Test_Freq2+1, Test_Freq );
		printf2(tempstr);
#endif
		// If Frequency requested is greater than 60MHz(30MHz). This mode will not work. Set ERROR.
//		if (Test_Freq2 > (float)OSC_FREQUENCY/2)
		if (Test_Freq2 > (float) OSC_FREQUENCY / 4) {
			calc_error = 10000;
		} else {
			// Test Against max frequency. If this causes too high, error
			if ((Test_Freq2 * 2.5) > MAX_MULT_FREQ) {
//				Test_Freq2 = ((float)OSC_FREQUENCY/2);
				Test_Freq2 = ((float) OSC_FREQUENCY / 4);
				temp1 = ((float) OSC_FREQUENCY / 2)
						/ ((float) OSC_FREQUENCY / 4);
				calc_error = fabs((Test_Freq / (Test_Freq2 + 1)) - 1);
			} else {
				calc_error = fabs((Test_Freq / (Test_Freq2 + 1)) - 1);
			}
		}
#ifdef MN_LASER
		sprintf(tempstr,"   calc_error:%f  Error:%f\n", calc_error, Error );
		printf2(tempstr);
#endif
		if (calc_error < Error)	// Test Error and see if this mode is better.
				{
			mode = MULTIPLY_2_5;	// Set mode to current mode
			Error = calc_error;
			Save_Cnt = temp1;		// This could be the final count.
			Save_Freq = Test_Freq2;
		}
#ifdef MN_LASER
		sprintf(tempstr,"   MULTIPLY_2_5:  Error:%f  mode:%d Save_Cnt:%ld\n", Error, mode, Save_Cnt);
		printf2(tempstr);
#endif

		// Test 3X
		Test_Freq = frequency1 / 3;
		temp1 = ((float) OSC_FREQUENCY / 2) / (float) Test_Freq;
		// If we are greater than 30MHz...Force to 60MHz..Ensures accuracy.
		if (Test_Freq > ((float) OSC_FREQUENCY / 4))
//			Test_Freq2 = ((float)OSC_FREQUENCY/2);
			Test_Freq2 = ((float) OSC_FREQUENCY / 4);
		else
			Test_Freq2 = ((float) OSC_FREQUENCY / 2) / (float) temp1;
#ifdef MN_LASER
		sprintf(tempstr,"   Test_Freq2:%f  Test_Freq2+1:%f  Test_Freq:%f Save_Cnt:%ld\n", Test_Freq2, Test_Freq2+1, Test_Freq );
		printf2(tempstr);
#endif
		// If Frequency requested is greater than 60MHz(30MHz). This mode will not work. Set ERROR.
//		if (Test_Freq2 > (float)OSC_FREQUENCY/2)
		if (Test_Freq2 > (float) OSC_FREQUENCY / 4) {
			calc_error = 10000;
		} else {
			// Test Against max frequency. If this causes too high, error
			if ((Test_Freq2 * 3) > MAX_MULT_FREQ) {
//				Test_Freq2 = ((float)OSC_FREQUENCY/2);
				Test_Freq2 = ((float) OSC_FREQUENCY / 4);
				temp1 = ((float) OSC_FREQUENCY / 2)
						/ ((float) OSC_FREQUENCY / 4);
				calc_error = fabs((Test_Freq / (Test_Freq2 + 1)) - 1);
			} else {
				calc_error = fabs((Test_Freq / (Test_Freq2 + 1)) - 1);
			}
		}
#ifdef MN_LASER
		sprintf(tempstr,"   calc_error:%f  Error:%f\n", calc_error, Error );
		printf2(tempstr);
#endif
		if (calc_error < Error)	// Test Error and see if this mode is better.
				{
			mode = MULTIPLY_3X;	// Set mode to current mode
			Error = calc_error;
			Save_Cnt = temp1;		// This could be the final count.
			Save_Freq = Test_Freq2;
		}
#ifdef MN_LASER
		sprintf(tempstr,"   MULTIPLY_3X:  Error:%f  mode:%d Save_Cnt:%ld\n", Error, mode, Save_Cnt);
		printf2(tempstr);
#endif

		// Test 3.33X
		Test_Freq = frequency1 / 3.33;
		temp1 = ((float) OSC_FREQUENCY / 2) / (float) Test_Freq;
		// If we are greater than 30MHz...Force to 60MHz..Ensures accuracy.
		if (Test_Freq > ((float) OSC_FREQUENCY / 4))
//			Test_Freq2 = ((float)OSC_FREQUENCY/2);
			Test_Freq2 = ((float) OSC_FREQUENCY / 4);
		else
			Test_Freq2 = ((float) OSC_FREQUENCY / 2) / (float) temp1;
#ifdef MN_LASER
		sprintf(tempstr,"   Test_Freq2:%f  Test_Freq2+1:%f  Test_Freq:%f Save_Cnt:%ld\n", Test_Freq2, Test_Freq2+1, Test_Freq );
		printf2(tempstr);
#endif
		// If Frequency requested is greater than 60MHz(30MHz). This mode will not work. Set ERROR.
//		if (Test_Freq2 > (float)OSC_FREQUENCY/2)
		if (Test_Freq2 > (float) OSC_FREQUENCY / 4) {
			calc_error = 10000;
		} else {
			// Test Against max frequency. If this causes too high, error
			if ((Test_Freq2 * 3.33) > MAX_MULT_FREQ) {
//				Test_Freq2 = ((float)OSC_FREQUENCY/2);
				Test_Freq2 = ((float) OSC_FREQUENCY / 4);
				temp1 = ((float) OSC_FREQUENCY / 2)
						/ ((float) OSC_FREQUENCY / 4);
				calc_error = fabs((Test_Freq / (Test_Freq2 + 1)) - 1);
			} else {
				calc_error = fabs((Test_Freq / (Test_Freq2 + 1)) - 1);
			}
		}
#ifdef MN_LASER
		sprintf(tempstr,"   calc_error:%f  Error:%f\n", calc_error, Error );
		printf2(tempstr);
#endif
		if (calc_error < Error)	// Test Error and see if this mode is better.
				{
			mode = MULTIPLY_3_33X;	// Set mode to current mode
			Error = calc_error;
			Save_Cnt = temp1;		// This could be the final count.
			Save_Freq = Test_Freq2;
		}
#ifdef MN_LASER
		sprintf(tempstr,"   MULTIPLY_3_33X:  Error:%f  mode:%d Save_Cnt:%ld\n", Error, mode, Save_Cnt);
		printf2(tempstr);
#endif

		// Test 4X
		Test_Freq = frequency1 / 4;
		temp1 = ((float) OSC_FREQUENCY / 2) / (float) Test_Freq;
		// If we are greater than 30MHz...Force to 60MHz..Ensures accuracy.
		if (Test_Freq > ((float) OSC_FREQUENCY / 4))
//			Test_Freq2 = ((float)OSC_FREQUENCY/2);
			Test_Freq2 = ((float) OSC_FREQUENCY / 4);
		else
			Test_Freq2 = ((float) OSC_FREQUENCY / 2) / (float) temp1;
#ifdef MN_LASER
		sprintf(tempstr,"   Test_Freq2:%f  Test_Freq2+1:%f  Test_Freq:%f Save_Cnt:%ld\n", Test_Freq2, Test_Freq2+1, Test_Freq );
		printf2(tempstr);
#endif
		// If Frequency requested is greater than 60MHz(30MHz). This mode will not work. Set ERROR.
//		if (Test_Freq2 > (float)OSC_FREQUENCY/2)
		if (Test_Freq2 > (float) OSC_FREQUENCY / 4) {
			calc_error = 10000;
		} else {
			// Test Against max frequency. If this causes too high, error
			if ((Test_Freq2 * 4) > MAX_MULT_FREQ) {
//				Test_Freq2 = ((float)OSC_FREQUENCY/2);
				Test_Freq2 = ((float) OSC_FREQUENCY / 4);
				temp1 = ((float) OSC_FREQUENCY / 2)
						/ ((float) OSC_FREQUENCY / 4);
				calc_error = fabs((Test_Freq / (Test_Freq2 + 1)) - 1);
			} else {
				calc_error = fabs((Test_Freq / (Test_Freq2 + 1)) - 1);
			}
		}
#ifdef MN_LASER
		sprintf(tempstr,"   calc_error:%f  Error:%f\n", calc_error, Error );
		printf2(tempstr);
#endif
		if (calc_error < Error)	// Test Error and see if this mode is better.
				{
			mode = MULTIPLY_4X;	// Set mode to current mode
			Error = calc_error;
			Save_Cnt = temp1;		// This could be the final count.
			Save_Freq = Test_Freq2;
		}
#ifdef MN_LASER
		sprintf(tempstr,"   MULTIPLY_4X:  Error:%f  mode:%d Save_Cnt:%ld\n", Error, mode, Save_Cnt);
		printf2(tempstr);
#endif

		// Test 5X
		Test_Freq = frequency1 / 5;
		temp1 = ((float) OSC_FREQUENCY / 2) / (float) Test_Freq;
		// If we are greater than 30MHz...Force to 60MHz..Ensures accuracy.
		if (Test_Freq > ((float) OSC_FREQUENCY / 4))
//			Test_Freq2 = ((float)OSC_FREQUENCY/2);
			Test_Freq2 = ((float) OSC_FREQUENCY / 4);
		else
			Test_Freq2 = ((float) OSC_FREQUENCY / 2) / (float) temp1;
#ifdef MN_LASER
		sprintf(tempstr,"   Test_Freq2:%f  Test_Freq2+1:%f  Test_Freq:%f Save_Cnt:%ld\n", Test_Freq2, Test_Freq2+1, Test_Freq );
		printf2(tempstr);
#endif
		// If Frequency requested is greater than 60MHz(30MHz). This mode will not work. Set ERROR.
//		if (Test_Freq2 > (float)OSC_FREQUENCY/2)
		if (Test_Freq2 > (float) OSC_FREQUENCY / 4) {
			calc_error = 10000;
		} else {
			// Test Against max frequency. If this causes too high, error
			if ((Test_Freq2 * 5) > MAX_MULT_FREQ) {
//				Test_Freq2 = ((float)OSC_FREQUENCY/2);
				Test_Freq2 = ((float) OSC_FREQUENCY / 4);
				temp1 = ((float) OSC_FREQUENCY / 2)
						/ ((float) OSC_FREQUENCY / 4);
				calc_error = fabs((Test_Freq / (Test_Freq2 + 1)) - 1);
			} else {
				calc_error = fabs((Test_Freq / (Test_Freq2 + 1)) - 1);
			}
		}
#ifdef MN_LASER
		sprintf(tempstr,"   calc_error:%f  Error:%f\n", calc_error, Error );
		printf2(tempstr);
#endif
		if (calc_error < Error)	// Test Error and see if this mode is better.
				{
			mode = MULTIPLY_5X;	// Set mode to current mode
			Error = calc_error;
			Save_Cnt = temp1;		// This could be the final count.
			Save_Freq = Test_Freq2;
		}
#ifdef MN_LASER
		sprintf(tempstr,"   MULTIPLY_5X:  Error:%f  mode:%d Save_Cnt:%ld\n", Error, mode, Save_Cnt);
		printf2(tempstr);
#endif
	} // EndIf (frequency1 > 10000000)
	  // Test Error. If greater than one, it failed and need to return blank structure.
	if (Error > 1) {
		temp2.Multipler_Value = 0;
		temp2.prescaler = 0;
		temp2.cnt_value = 0;
		temp2.Multiplier = TRUE;
		temp2.Special1 = MODE_ERROR;
		sprintf(tempstr, "   ERROR:  Error:%f  mode:%d Save_Cnt:%ld\n", Error,
				mode, Save_Cnt);
		printf2(tempstr);
	} else if (mode == MULTIPLY_1X) {
		temp2.Multipler_Value = mode;
		temp2.prescaler = _00_MTU_PCLK_1;
		temp2.cnt_value = Save_Cnt;
		temp2.Multiplier = FALSE;
		temp2.Special1 = NO_SETTING;
		switch (LaserNumber) {
		case LaserDiode0:
			temp3 = calc_ratio(temp2.cnt_value, MTU0_LaserDiode0);
			break;
		case LaserDiode1:
			temp3 = calc_ratio(temp2.cnt_value, MTU1_LaserDiode1);
			break;
		case LaserDiode2:
			if (temp2.Multiplier) {
				temp3 = calc_ratio(temp2.cnt_value, MTU3_PLLInput2);
			} else {
				temp3 = calc_ratio(temp2.cnt_value, MTU4_LaserDiode2b);
			}
			break;
		case LaserDiode3:
			if (temp2.Multiplier) {
				temp3 = calc_ratio(temp2.cnt_value, MTU6_PLLInput3);
			} else {
				temp3 = calc_ratio(temp2.cnt_value, MTU7_LaserDiode3b);
			}
			break;
		} // EndSwitch ( LaserNumber )
		if (temp3.Special1 == MODE_ERROR) {
			temp2.Multipler_Value = 0;
			temp2.prescaler = 0;
			temp2.cnt_value = 0;
			temp2.Multiplier = TRUE;
			temp2.Special1 = MODE_ERROR;
		} // EndIf (temp3.Special1 == MODE_ERROR)
		else {
			temp2.Special1 = temp3.Special1;
			temp2.prescaler = temp3.prescaler;
			temp2.cnt_value = temp3.cnt_value;
		} // EndElse (temp3.Special1 == MODE_ERROR)
	} // EndIf(mode == MULTIPLY_1X)
	else {
		temp2.Multipler_Value = mode;
		temp2.prescaler = _00_MTU_PCLK_1;
		temp2.cnt_value = Save_Cnt;
		temp2.Multiplier = TRUE;
		temp2.Special1 = NO_SETTING;
		switch (LaserNumber) {
		case LaserDiode0:
			temp3 = calc_ratio(temp2.cnt_value, MTU0_LaserDiode0);
			break;
		case LaserDiode1:
			temp3 = calc_ratio(temp2.cnt_value, MTU1_LaserDiode1);
			break;
		case LaserDiode2:
			// Test Frequency to determine Special 60MHz generation.
			// This ensures that clock is set at fastest level.
			if (Save_Freq > ((float) OSC_FREQUENCY / 4))
				cntrl_flg |= 0x04;
			temp3 = calc_ratio(temp2.cnt_value, MTU4_LaserDiode2b);
			break;
		case LaserDiode3:
			// Test Frequency to determine Special 60MHz generation.
			// This ensures that clock is set at fastest level.
			if (Save_Freq > ((float) OSC_FREQUENCY / 4))
				cntrl_flg |= 0x08;
			temp3 = calc_ratio(temp2.cnt_value, MTU7_LaserDiode3b);
			break;
		} // EndSwitch ( LaserNumber )
		if (temp3.Special1 == MODE_ERROR) {
			temp2.Multipler_Value = 0;
			temp2.prescaler = 0;
			temp2.cnt_value = 0;
			temp2.Multiplier = TRUE;
			temp2.Special1 = MODE_ERROR;
		} // EndIf (temp3.Special1 == MODE_ERROR)
		else {
			temp2.Special1 = temp3.Special1;
			temp2.prescaler = temp3.prescaler;
			temp2.cnt_value = temp3.cnt_value;
		} // EndElse (temp3.Special1 == MODE_ERROR)
	} // EndElse (mode == MULTIPLY_1X)
	if (frequency1 == 0) {
		temp2.Multipler_Value = 0;
		temp2.prescaler = 0;
		temp2.cnt_value = 0;
		temp2.Multiplier = TRUE;
		temp2.Special1 = NO_SETTING;
	} // EndIf (temp3.Special1 == MODE_ERROR)
	printf2("*****************************************\n");
	sprintf(tempstr, "calc_sweeptimeE results.\n");
	printf2(tempstr);

	sprintf(tempstr, "cntrl_flg: %xd\n", cntrl_flg);
	printf2(tempstr);

	sprintf(tempstr, "Frequency: %f\n", frequency1);
	printf2(tempstr);

	switch (LaserNumber) {
	case LaserDiode0:
		printf2("Laser Diode 1\n");
		break;
	case LaserDiode1:
		printf2("Laser Diode 2\n");
		break;
	case LaserDiode2:
		printf2("Laser Diode 3\n");
		break;
	case LaserDiode3:
		printf2("Laser Diode 4\n\n");
		break;
	}
	sprintf(tempstr, "Special: %d\n", temp2.Special1);
	printf2(tempstr);
	sprintf(tempstr, "Prescaler: %d\n", temp2.prescaler);
	printf2(tempstr);
	sprintf(tempstr, "cnt_value: %ld\n", temp2.cnt_value);
	printf2(tempstr);
	if (temp2.Multiplier) {
		sprintf(tempstr, "Multipler_Value: %d\n", temp2.Multipler_Value);
		printf2(tempstr);
	}

	return (temp2);	  	  	//Done....Return new value.
}

//*****************************************************************************
//*
//* routine: calc_sweeptimeP
//* Date: 	 February 9, 2015
//* Updated: February 9, 2015
//* Author:  Ralph Pruitt
//* Calculate New Frequency count based on passed Frequency. This also
//* Involves determining the optimum parameters for this event.
//*
//*****************************************************************************
struct plmLaser_entry calc_sweeptimeP(unsigned long frequency1, int LaserNumber) {
	char tempstr[80];
	struct plmLaser_entry temp2;
	struct plmLaser_entry temp3;
	//unsigned long Save_Cnt;

	printf2("*****************************************\n");
	sprintf(tempstr, "calc_sweeptimeP  Cnt:%ld Laser:%d\n", frequency1,
			LaserNumber);
	temp2.prescaler = _00_MTU_PCLK_1;
	temp2.cnt_value = frequency1;
	temp2.Special1 = NO_SETTING;
	switch (LaserNumber) {
	case LaserDiode0:
		temp3 = calc_ratio(temp2.cnt_value, MTU0_LaserDiode0);
		break;
	case LaserDiode1:
		temp3 = calc_ratio(temp2.cnt_value, MTU1_LaserDiode1);
		break;
	case LaserDiode2:
		temp3 = calc_ratio(temp2.cnt_value, MTU4_LaserDiode2b);
		break;
	case LaserDiode3:
		temp3 = calc_ratio(temp2.cnt_value, MTU7_LaserDiode3b);
		break;
	} // EndSwitch ( LaserNumber )
	if (temp3.Special1 == MODE_ERROR) {
		temp2.prescaler = 0;
		temp2.cnt_value = 0;
		temp2.Special1 = MODE_ERROR;
	} // EndIf (temp3.Special1 == MODE_ERROR)
	else {
		temp2.Special1 = temp3.Special1;
		temp2.prescaler = temp3.prescaler;
		temp2.cnt_value = temp3.cnt_value;
	} // EndElse (temp3.Special1 == MODE_ERROR)
	if (frequency1 == 0) {
		temp2.prescaler = 0;
		temp2.cnt_value = 0;
		temp2.Special1 = NO_SETTING;
	} // EndIf (temp3.Special1 == MODE_ERROR)
	printf2("*****************************************\n");
	sprintf(tempstr, "calc_sweeptimeP results.\n");
	printf2(tempstr);

	sprintf(tempstr, "CNT: %ld\n", frequency1);
	printf2(tempstr);

	switch (LaserNumber) {
	case LaserDiode0:
		printf2("Laser Diode 1\n");
		break;
	case LaserDiode1:
		printf2("Laser Diode 2\n");
		break;
	case LaserDiode2:
		printf2("Laser Diode 3\n");
		break;
	case LaserDiode3:
		printf2("Laser Diode 4\n\n");
		break;
	}
	sprintf(tempstr, "cntrl_flg: %xd\n", cntrl_flg);
	printf2(tempstr);
	sprintf(tempstr, "Special: %d\n", temp2.Special1);
	printf2(tempstr);
	sprintf(tempstr, "Prescaler: %d\n", temp2.prescaler);
	printf2(tempstr);
	sprintf(tempstr, "cnt_value: %ld\n", temp2.cnt_value);
	printf2(tempstr);

	return (temp2);	  	  	//Done....Return new value.
}

//*****************************************************************************
//*
//* routine: calc_ratio
//* Date: 	 February 8, 2015
//* Updated: February 8, 2015
//* Author:  Ralph Pruitt
//* Calculate New Frequency count based on passed Frequency. This also
//* Involves determining the optimum parameters for this event.
//*
//*****************************************************************************
struct plmLaser_entry calc_ratio(unsigned long cnt_value, int timer_number) {
	struct plmLaser_entry temp1;
#ifdef MN_LASER
	char tempstr[80];
#endif

#ifdef MN_LASER
	printf2("***********************************\n");
	sprintf(tempstr,"calc_ratio cnt_vale:%ld   timer_number:%d\n", cnt_value, timer_number );
	printf2(tempstr);
#endif
	switch (timer_number) {
	case MTU0_LaserDiode0:
		if (cnt_value > 6000000) {
#ifdef MN_LASER
				printf2("   cnt_value>6,000,000\n");
#endif
			temp1.prescaler = _05_MTU_PCLK_1024;
			temp1.cnt_value = cnt_value / 1024;
			temp1.Special1 = MODE_TCR2;
		} else if (cnt_value > 600000) {
#ifdef MN_LASER
				printf2("   cnt_value>600,000\n");
#endif
			temp1.prescaler = _04_MTU_PCLK_256;
			temp1.cnt_value = cnt_value / 256;
			temp1.Special1 = MODE_TCR2;
		} else {
			temp1.prescaler = _00_MTU_PCLK_1;
			temp1.cnt_value = cnt_value;
			temp1.Special1 = MODE_TCR;
		}
#ifdef MN_LASER
			sprintf(tempstr,"   prescaler:%d   cnt_vale:%ld   Special1:%d\n", temp1.prescaler, temp1.cnt_value, temp1.Special1 );
			printf2(tempstr);
#endif
		return temp1;
		break;
	case MTU1_LaserDiode1:
		if (cnt_value > 6000000) {
#ifdef MN_LASER
				printf2("   cnt_value>6,000,000\n");
#endif
			temp1.prescaler = _04_MTU_PCLK_1024;
			temp1.cnt_value = cnt_value / 1024;
			temp1.Special1 = MODE_TCR2;
		} else if (cnt_value > 600000) {
#ifdef MN_LASER
				printf2("   cnt_value>600,000\n");
#endif
			temp1.prescaler = _06_MTU_PCLK_256;
			temp1.cnt_value = cnt_value / 256;
			temp1.Special1 = MODE_TCR;
		} else {
			temp1.prescaler = _00_MTU_PCLK_1;
			temp1.cnt_value = cnt_value;
			temp1.Special1 = MODE_TCR;
		}
#ifdef MN_LASER
			sprintf(tempstr,"   prescaler:%d   cnt_vale:%ld   Special1:%d\n", temp1.prescaler, temp1.cnt_value, temp1.Special1 );
			printf2(tempstr);
#endif
		return temp1;
		break;
	case MTU3_PLLInput2:
	case MTU4_LaserDiode2b:
	case MTU6_PLLInput3:
	case MTU7_LaserDiode3b:
		if (cnt_value > 6000000) {
#ifdef MN_LASER
				printf2("   cnt_value>6,000,000\n");
#endif
			temp1.prescaler = _05_MTU_PCLK_1024;
			temp1.cnt_value = cnt_value / 1024;
			temp1.Special1 = MODE_TCR;
		} else if (cnt_value > 600000) {
#ifdef MN_LASER
				printf2("   cnt_value>600,000\n");
#endif
			temp1.prescaler = _04_MTU_PCLK_256;
			temp1.cnt_value = cnt_value / 256;
			temp1.Special1 = MODE_TCR;
		} else {
			temp1.prescaler = _00_MTU_PCLK_1;
			temp1.cnt_value = cnt_value;
			temp1.Special1 = MODE_TCR;
		}
#ifdef MN_LASER
			sprintf(tempstr,"   prescaler:%d   cnt_vale:%ld   Special1:%d\n", temp1.prescaler, temp1.cnt_value, temp1.Special1 );
			printf2(tempstr);
#endif
		return temp1;
		break;
	default:
		printf2("MODE_ERROR\n");
		temp1.prescaler = 0;
		temp1.cnt_value = 0;
		temp1.Special1 = MODE_ERROR;
		break;
	}
	return temp1;
}
//*****************************************************************************
//*
//* routine: calc_sweeptime
//* Date: 	 July 7, 2005
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* Calculate New Frequency count based on passed Frequency.
//*
//*****************************************************************************
unsigned long calc_sweeptime(float frequency1) {
	unsigned long temp1;

	// Test Value...If zero, then we return a zero cnt.
	if (frequency1 == 0)
		return (0);
	// Calculate Count Step1.
	temp1 = (OSC_FREQUENCY / 2) / (float) frequency1;

	return (temp1);	  	  	//Done....Return new value.
}

//*****************************************************************************
//*
//* routine: setup_sweep
//* Date: 	 July 8, 2005
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* Setup New Sweep Frequency.
//*
//*****************************************************************************
void setup_sweep(unsigned long laser2_time) {
	float temp_freq;
	unsigned long temp_count;
	unsigned long temp_count1;

	// Find first good Frequency in Sweepentry and store to temp_freq.
	while (sweep1.sweep_ptr < 16) {
		if (sweep1.sweep1->laser_time[sweep1.sweep_ptr - 1] != 0) {
			temp_freq = sweep1.sweep1->laser_time[sweep1.sweep_ptr - 1];
			sweep1.sweep_ptr++;
			break;
		} else
			sweep1.sweep_ptr++;
	}
	// If ptr past all entries then load temp_freq with final frequency.
	if (sweep1.sweep_ptr >= 16) {
		temp_freq = sweep1.sweep1->sweep_high;
		sweep1.sweep_ptr = 17;			// Set to insure Display can find it.
	}
	// OK....we now have a target_freq.Now calculate the count.
	temp_count = calc_sweeptime(temp_freq);
	// Now setup Key variables from this count.
	sweep1.t_freq1 = temp_count * 0.9;
	sweep1.t_freq3 = sweep1.t_freq1;
	sweep1.t_freq2 = temp_count * 1.1;
	temp_count1 = (sweep1.t_freq2 - sweep1.t_freq1) * 2;
	if (sweep1.t_freq1 < laser2_time) {
		sweep1.sweep_dir = 0;			   // Positive movement of Frequency
		temp_count = laser2_time - sweep1.t_freq1;
	} else {
		sweep1.sweep_dir = 1;			   // Negative movement of Frequency
		temp_count = sweep1.t_freq1 - laser2_time;
	}
	temp_count += temp_count1;
	sweep1.sweep_lmt = sweep1.sweep_tlmt / temp_count;
	if (sweep1.sweep_lmt == 0) {
		// OK...We need to set limit to number of ticks to modify timer value and set sweep_lmt flag.
		sweep1.sweep_lmt = temp_count / sweep1.sweep_tlmt;
		sweep1.sweep_flg = 1;
		sweep1.sweep_cnt = 1;			  					// Set for one tick
	} else {
		// Else...Clear Sweeplmt flag
		sweep1.sweep_flg = 0;
		sweep1.sweep_cnt = sweep1.sweep_lmt;			// Set for tick limit.
	}
	// Set as Initial Sweep State.
	sweep1.sweep_state = 0;
}

//*****************************************************************************
//*
//* routine: cleanup_macros
//* Date: 	 June 13, 2006
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* Cleanup key variables for next run including possible macros.
//*
//*****************************************************************************
void cleanup_macros(void) {
	if (macro_flg > 0) {
		macro_flg = 0;		   		  			   // Turn Macros off.
		macro1.save_flg = 0;
		macro1.macro_step = 0;
		macro1.macro_flg = 0;
		// Restore entry_num.
		// prog_num = macro1.prog_save;	 		       // Restore old Program Number.
		// Restore Timers.
		tmr_min = macro1.save_min;	  			   // Restore Old Minutes.
		tmr_sec = macro1.save_sec;				   // Restore Old Seconds.
	}
}

//*****************************************************************************
//*
//* routine: write_plmLasers
//* Date: 	 February 7, 2015
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* This routine will write the 4 passed structures to timers and Laser Configuration
//* hardware.
//*
//*****************************************************************************
void write_plmLasers(struct plmLaser_entry laser1, struct plmLaser_entry laser2,
		struct plmLaser_entry laser3, struct plmLaser_entry laser4) {

	printf2("write_plmLasers: Before Call to R_MTU3_plmCreate.\n");
	// Initialize Laser 1-4
	R_MTU3_plmCreate(laser1, laser2, laser3, laser4);
	printf2("write_plmLasers: After Call to R_MTU3_plmCreate.\n");

	// Configure Multipliers/PLLs

	// TBD

	// Wait for 30msec.
	accurate_delay(70);

	// Start Timers
	if (laser1.cnt_value > 0)
		R_MTU3_C0_Start();
	else
		R_MTU3_LaserDiode0_Off();
	if (laser2.cnt_value > 0)
		R_MTU3_C1_Start();
	else
		R_MTU3_LaserDiode1_Off();
	if (laser3.cnt_value > 0)
	{
			R_MTU3_LaserDiode2b_Enable();
			R_MTU3_C4_Start();
			R_MTU3_LaserDiode2a_Off();
	}
	else
	{
		R_MTU3_LaserDiode2a_Off();
		R_MTU3_LaserDiode2b_Off();
	}
	if (laser4.cnt_value > 0)
	{
			R_MTU3_LaserDiode3b_Enable();
			R_MTU3_C7_Start();
			R_MTU3_LaserDiode3a_Off();
	}
	else
	{
		R_MTU3_LaserDiode3a_Off();
		R_MTU3_LaserDiode3b_Off();
	}

	// Wait for 30msec.
	accurate_delay(70);
	printf2("write_plmLasers: Timers started.\n");

	// Setup HF Drivers.
	write_HFLasers(laser1, laser2, laser3, laser4);
	// Enable Multipliers
	//PORT0.PDR.BYTE |= 0x02;						// Set PLLC_Enable as Output
	//PORT2.PDR.BYTE |= 0x10;						// Set PLLD_Enable as Output
	//PORT0.PODR.BYTE |= 0x04;
	//PORT2.PODR.BYTE |= 0x10;
	printf2("write_plmLasers: HF Drivers Enabled.\n");

	// Wait for 30msec.
	accurate_delay(70);

}

/*****************************************************************************
 *
 * routine: disp_HF_Parms
 * Date: 	December 29, 2020
 * Updated: December 29, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine displays the HF Parms using printf2 for a passed freq.
 *
 * INPUT:
 *  @param	float disp_freq		Freq to be displayed
 *
 * OUTPUT:
 * 	None
 *
 *****************************************************************************/
void disp_HF_Parms( float disp_freq )
{
	PLL_Parameters Template_Parms;
	char tempstr[80];

	// Lets Get parameters first so we can See values.
	Template_Parms.Desired_Freq = disp_freq;
	hmc_calc_parameters(&Template_Parms);
	// Now Print Parms.
	sprintf(tempstr, "		Output_Divider:%d\n", Template_Parms.Output_Divider);
	printf2(tempstr);
	sprintf(tempstr, "		N_Divider:%d / %d\n", Template_Parms.N_Divider_int,
			Template_Parms.N_Divider_frac);
	printf2(tempstr);
	sprintf(tempstr, "		R_Divider:%d\n", Template_Parms.R_Divider);
	printf2(tempstr);
}

/*****************************************************************************
 *
 * routine: write_HFLasers
 * Date: 	December 27, 2020
 * Updated: December 27, 2020
 * Author:  Ralph Pruitt
 * @brief	This routine Performs sets up the HF Lasers based on the parameters passed.
 * 			NOTE: The produced freqs are  based on the following exceptions that return an error:
 * 				* The Frequency allowed: 25.0MHz to 3.0GHz(3,000,000,000).
 * 				* Only two legal Frequencies are allowed above 33.0MHz.
 * 				* Multiple Lasers can be used above 33.0MHz
 *
 * INPUT:
 *  @param	struct plmLaser_entry laser1:		Key Information for Laser Freq 1
 *  @param	struct plmLaser_entry laser2:		Key Information for Laser Freq 2
 *  @param	struct plmLaser_entry laser3:		Key Information for Laser Freq 3
 *  @param	struct plmLaser_entry laser4:		Key Information for Laser Freq 4
 *  @param	unsigned char	      cntrl_flg;	Control flag that controls HF vs LF
 *
 * OUTPUT:
 * 	@retval HAL_StatusTypeDef	-	HAL_OK       = 0x00:	No Errors
 * 									HAL_ERROR    = 0x01:	Bad Parameter or Error
 *
 *****************************************************************************/
#define LFMAX_FREQ	33000000.0			// Maximum Freq that the LF Driver can Generate...33.0MHz
#define HFMAX_FREQ	3000000000.0		// Maximum Freq that the HF Driver can Generate...3.0GHz
int cmpfunc (const void * a, const void * b) {
//   return ( *(float*)a - *(float*)b );
    float f1=*((float*)a);
    float f2=*((float*)b);
    if(f1 < f2)
            return 1;
    else if(f1 > f2)
            return -1;
    return 0;
}

HAL_StatusTypeDef write_HFLasers(struct plmLaser_entry laser1,
		struct plmLaser_entry laser2,
		struct plmLaser_entry laser3,
		struct plmLaser_entry laser4)
{

	int HFlaser_cnt = 0;
	int x,y;
	float temp_float;
	float HF_Laser_Freq[4];
	HF_Avail_Modes	 HF_Avail;
	char tempstr[80];
	int HFCount1, HFCount2;

	// Clear temp_laser[].
	for (x=0;x<4;x++)
	{
		HF_Laser_Freq[x] = 0.0;
	}

	/*
	 * Verify if any of the passed Frews are greater than HFMAX_FREQ. If they are then return HAL_ERROR.
	 */
	if (( (cntrl_flg & 0x01) > 0 ) && (laser1.laser_Freq > HFMAX_FREQ))
		return HAL_ERROR;
	if (( (cntrl_flg & 0x02) > 0 ) && (laser2.laser_Freq > HFMAX_FREQ))
		return HAL_ERROR;
	if (( (cntrl_flg & 0x04) > 0 ) && (laser3.laser_Freq > HFMAX_FREQ))
		return HAL_ERROR;
	if (( (cntrl_flg & 0x08) > 0 ) && (laser4.laser_Freq > HFMAX_FREQ))
		return HAL_ERROR;

	/*
	 * Determine the number of lasers that are being programmed greater than LFMAX_FREQ and make a list.
	 * 		HFlaser_cnt:		Number of High Freq Lasers
	 * 		HF_Laser_Freq[]:	Array of High Freq Lasers.
	 */
	if(( (cntrl_flg & 0x01) > 0 ) && (laser1.laser_Freq > LFMAX_FREQ))
	{
		HF_Laser_Freq[HFlaser_cnt] = laser1.laser_Freq;
		HFlaser_cnt++;
	}
	if(( (cntrl_flg & 0x02) > 0 ) && (laser2.laser_Freq > LFMAX_FREQ))
	{
		HF_Laser_Freq[HFlaser_cnt] = laser2.laser_Freq;
		HFlaser_cnt++;
	}
	if(( (cntrl_flg & 0x04) > 0 ) && (laser3.laser_Freq > LFMAX_FREQ))
	{
		HF_Laser_Freq[HFlaser_cnt] = laser3.laser_Freq;
		HFlaser_cnt++;
	}
	if(( (cntrl_flg & 0x08) > 0 ) && (laser4.laser_Freq > LFMAX_FREQ))
	{
		HF_Laser_Freq[HFlaser_cnt] = laser4.laser_Freq;
		HFlaser_cnt++;
	}

	/*
	 * 	3. Determine Action Based on Number of HF Lasers to Program.
	 */
	switch(HFlaser_cnt)
	{
	//  HFlaser_cnt: 0	Return...No Action
	case 0:
		return HAL_OK;
		break;
	/*********************************************************************************
	 *
	 * HFlaser_cnt: 1
	 *
	 ********************************************************************************/
	case 1:
		// Find a HF Channel Available
		// Is it either Ch 1 or Ch3?
		if ( (cntrl_flg & 0x05) > 0 )
		{
			// Set PLL C to New Freq in HF_Laser_Freq[0]
			/*
			 * Power Up PLLs.
			 */
			hmc_pll_powerUp(PLL_C_HW);

			// Power Up Clock Circuit.
			PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

			// Setup Synth for HF_Laser_Freq[0].
			hmc_SetupFreq(PLL_C_HW, HF_Laser_Freq[0]);
			// Is Channel 1 Available
			if ( (cntrl_flg & 0x01) > 0 )
			{
				/*
				 * Enable Channel 1
				 * 	Powerup Channel 1 Common.
				 * 		P13/Pin 44: MTU0: LaserDiode0
				 */
				MPC.P13PFS.BYTE = 0x00U;					// No Periph Control.
				PORT1.PMR.BYTE &= ~0x08U;					// Setup as I/O.
				PORT1.PDR.BYTE |= 0x08U;					// Setup as Output.
				PORT1.PODR.BYTE &= ~0x08U;					// Set as LOW.
				/*
				 * Powerup HF Drivers Power Supply
				 */
				accurate_delay(10);
				PLMpls_gpio_Off( HF_Laser_Enable );
				/*
				 * Enable HF Laser 1 Driver.
				 */
				accurate_delay(10);
				PLMpls_HFlaser_enable( HF_LSR1_CNTL );
			} // EndIf ( (cntrl_flg & 0x01) > 0 )
			else
			{
				/*
				 * Enable Channel 3
				 * 	Powerup Channel 3 Common.
				 * 		P17/Pin 38: MTU4: LaserDiode2b
				 */
				MPC.P17PFS.BYTE = 0x00U;					// No Periph Control.
				PORT1.PMR.BYTE &= ~0x80U;					// Setup as I/O.
				PORT1.PDR.BYTE |= 0x80U;					// Setup as Output.
				PORT1.PODR.BYTE &= ~0x80U;					// Set as LOW.
				/*
				 * Powerup HF Drivers Power Supply
				 */
				accurate_delay(10);
				PLMpls_gpio_Off( HF_Laser_Enable );
				/*
				 * Enable HF Laser 3 Driver.
				 */
				accurate_delay(10);
				PLMpls_HFlaser_enable( HF_LSR3_CNTL );
			} // EndElse ( (cntrl_flg & 0x01) > 0 )
		} // EndIf ( (cntrl_flg & 0x05) > 0 )
		else
		{
			// Set PLL D to New Freq in HF_Laser_Freq[0]
			/*
			 * Power Up PLLs.
			 */
			hmc_pll_powerUp(PLL_D_HW);

			// Power Up Clock Circuit.
			PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

			// Setup Synth for HF_Laser_Freq[0].
			hmc_SetupFreq(PLL_D_HW, HF_Laser_Freq[0]);
			// Is Channel 2 Available
			if ( (cntrl_flg & 0x02) > 0 )
			{
				/*
				 * Enable Channel 2
				 * 	Powerup Channel 2 Common.
				 * 		P20/Pin 37: MTU1: LaserDiode1
				 */
				MPC.P20PFS.BYTE = 0x00U;					// No Periph Control.
				PORT2.PMR.BYTE &= ~0x01U;					// Setup as I/O.
				PORT2.PDR.BYTE |= 0x01U;					// Setup as Output.
				PORT2.PODR.BYTE &= ~0x01U;					// Set as LOW.
				/*
				 * Powerup HF Drivers Power Supply
				 */
				accurate_delay(10);
				PLMpls_gpio_Off( HF_Laser_Enable );
				/*
				 * Enable HF Laser 1 Driver.
				 */
				accurate_delay(10);
				PLMpls_HFlaser_enable( HF_LSR2_CNTL );
			} // EndIf ( (cntrl_flg & 0x02) > 0 )
			else
			{
				/*
				 * Enable Channel 4
				 * 	Powerup Channel 1 Common.
				 * 		PA1/Pin 96: MTU7: LaserDiode3b
				 */
				MPC.PA1PFS.BYTE = 0x00U;					// No Periph Control.
				PORTA.PMR.BYTE &= ~0x02U;					// Setup as I/O.
				PORTA.PDR.BYTE |= 0x02U;					// Setup as Output.
				PORTA.PODR.BYTE &= ~0x02U;					// Set as LOW.
				/*
				 * Powerup HF Drivers Power Supply
				 */
				accurate_delay(10);
				PLMpls_gpio_Off( HF_Laser_Enable );
				/*
				 * Enable HF Laser 4 Driver.
				 */
				accurate_delay(10);
				PLMpls_HFlaser_enable( HF_LSR4_CNTL );
			} // EndElse ( (cntrl_flg & 0x02) > 0 )
		} // EndElse ( (cntrl_flg & 0x05) > 0 )
		break;

	/*********************************************************************************
	 *
	 * HFlaser_cnt: 2
	 *
	 ********************************************************************************/
	case 2:
		// 	A. If Ch1 or Ch 3 Available
		if ( (cntrl_flg & 0x05) > 0 )
		{
			// Set PLL C to New Freq in HF_Laser_Freq[0]
			/*
			 * Power Up PLLs.
			 */
			hmc_pll_powerUp(PLL_C_HW);

			// Power Up Clock Circuit.
			PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

			// Setup Synth for HF_Laser_Freq[0].
			hmc_SetupFreq(PLL_C_HW, HF_Laser_Freq[0]);
			// Is Channel 1 Available
			if ( (cntrl_flg & 0x01) > 0 )
			{
				/*
				 * Enable Channel 1
				 * 	Powerup Channel 1 Common.
				 * 		P13/Pin 44: MTU0: LaserDiode0
				 */
				MPC.P13PFS.BYTE = 0x00U;					// No Periph Control.
				PORT1.PMR.BYTE &= ~0x08U;					// Setup as I/O.
				PORT1.PDR.BYTE |= 0x08U;					// Setup as Output.
				PORT1.PODR.BYTE &= ~0x08U;					// Set as LOW.
				/*
				 * Powerup HF Drivers Power Supply
				 */
				accurate_delay(10);
				PLMpls_gpio_Off( HF_Laser_Enable );
				/*
				 * Enable HF Laser 1 Driver.
				 */
				accurate_delay(10);
				PLMpls_HFlaser_enable( HF_LSR1_CNTL );
			} // EndIf ( (cntrl_flg & 0x01) > 0 )
			if ( (cntrl_flg & 0x04) > 0 )
			{
				/*
				 * Enable Channel 3
				 * 	Powerup Channel 3 Common.
				 * 		P17/Pin 38: MTU4: LaserDiode2b
				 */
				MPC.P17PFS.BYTE = 0x00U;					// No Periph Control.
				PORT1.PMR.BYTE &= ~0x80U;					// Setup as I/O.
				PORT1.PDR.BYTE |= 0x80U;					// Setup as Output.
				PORT1.PODR.BYTE &= ~0x80U;					// Set as LOW.
				/*
				 * Powerup HF Drivers Power Supply
				 */
				accurate_delay(10);
				PLMpls_gpio_Off( HF_Laser_Enable );
				/*
				 * Enable HF Laser 3 Driver.
				 */
				accurate_delay(10);
				PLMpls_HFlaser_enable( HF_LSR3_CNTL );
			} // EndIf ( (cntrl_flg & 0x04) > 0 )
		} // EndIf ( (cntrl_flg & 0x05) > 0 )

		// 	B. If Ch2 or Ch4 Available
		if ( (cntrl_flg & 0x0A) > 0 )
		{
			// Set PLL D to New Freq in HF_Laser_Freq[1]
			/*
			 * Power Up PLLs.
			 */
			hmc_pll_powerUp(PLL_D_HW);

			// Power Up Clock Circuit.
			PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

			// Setup Synth for HF_Laser_Freq[1].
			hmc_SetupFreq(PLL_D_HW, HF_Laser_Freq[1]);
			// Is Channel 2 Available
			if ( (cntrl_flg & 0x02) > 0 )
			{
				/*
				 * Enable Channel 2
				 * 	Powerup Channel 2 Common.
				 * 		P20/Pin 37: MTU1: LaserDiode1
				 */
				MPC.P20PFS.BYTE = 0x00U;					// No Periph Control.
				PORT2.PMR.BYTE &= ~0x01U;					// Setup as I/O.
				PORT2.PDR.BYTE |= 0x01U;					// Setup as Output.
				PORT2.PODR.BYTE &= ~0x01U;					// Set as LOW.
				/*
				 * Powerup HF Drivers Power Supply
				 */
				accurate_delay(10);
				PLMpls_gpio_Off( HF_Laser_Enable );
				/*
				 * Enable HF Laser 1 Driver.
				 */
				accurate_delay(10);
				PLMpls_HFlaser_enable( HF_LSR2_CNTL );
			} // EndIf ( (cntrl_flg & 0x02) > 0 )
			if ( (cntrl_flg & 0x08) > 0 )
			{
				/*
				 * Enable Channel 4
				 * 	Powerup Channel 1 Common.
				 * 		PA1/Pin 96: MTU7: LaserDiode3b
				 */
				MPC.PA1PFS.BYTE = 0x00U;					// No Periph Control.
				PORTA.PMR.BYTE &= ~0x02U;					// Setup as I/O.
				PORTA.PDR.BYTE |= 0x02U;					// Setup as Output.
				PORTA.PODR.BYTE &= ~0x02U;					// Set as LOW.
				/*
				 * Powerup HF Drivers Power Supply
				 */
				accurate_delay(10);
				PLMpls_gpio_Off( HF_Laser_Enable );
				/*
				 * Enable HF Laser 4 Driver.
				 */
				accurate_delay(10);
				PLMpls_HFlaser_enable( HF_LSR4_CNTL );
			} // EndIf ( (cntrl_flg & 0x08) > 0 )
		} // EndIf ( (cntrl_flg & 0x0A) > 0 )
		break;

	/*********************************************************************************
	 *
	 * HFlaser_cnt: 3 or 4
	 *
	 ********************************************************************************/
	case 3:
	case 4:
		// A. Determine which Chs are both Available for HF.
		switch (cntrl_flg)
		{
		case 0x00:			//	Lasers: 0000	-	NO_HFMODES
		case 0x01:			//	Lasers: 0001	-	NO_HFMODES
		case 0x02:			//	Lasers: 0010	-	NO_HFMODES
		case 0x03:			//	Lasers: 0011	-	NO_HFMODES
		case 0x04:			//	Lasers: 0100	-	NO_HFMODES
		case 0x06:			//	Lasers: 0110	-	NO_HFMODES
		case 0x08:			//	Lasers: 1000	-	NO_HFMODES
		case 0x09:			//	Lasers: 1001	-	NO_HFMODES
		case 0x0C:			//	Lasers: 1100	-	NO_HFMODES
			HF_Avail = NO_HFMODES;
			break;
		case 0x05:			//	Lasers: 0101	-	PLLC_HFMODE
		case 0x07:			//	Lasers: 0111	-	PLLC_HFMODE
		case 0x0D:			//	Lasers: 1101	-	PLLC_HFMODE
			HF_Avail = PLLC_HFMODE;
			break;
		case 0x0A:			//	Lasers: 1010	-	PLLD_HFMODE
		case 0x0B:			//	Lasers: 1011	-	PLLD_HFMODE
		case 0x0E:			//	Lasers: 1110	-	PLLD_HFMODE
			HF_Avail = PLLD_HFMODE;
			break;
		case 0x0F:			//	Lasers: 1111	-	BOTH_HFMODES
			HF_Avail = BOTH_HFMODES;
			break;
		}

		// A1. Qsort Freqs Highest to lowest.
		qsort(HF_Laser_Freq, 4, sizeof(float), cmpfunc);
#if 0
		/*********************************************************
		 *
		 * TEST CODE FOR PRINTING QSORT VALUES
		 ********************************************************/
		StrmOn = 1;
		for (x=0;x<4;x++)
		{
			sprintf(tempstr,"HF_Laser_Freq[%d]:		%f\n", x, HF_Laser_Freq[x]);
			printf2(tempstr);
		}
		printf2("\n");
		StrmOn = 0;
		/*********************************************************
		 * END TEST CODE
		 ********************************************************/
#endif
		/*
		 * 	B. Count Number of Duplicate Freqs in List
		 * 		HFCount1:	Number repeats Freq 1
		 * 		HFCount2:	Number repeats Freq 2
		 * 			NOTE: Only two freqs allowed. Zero out all remaining freqs.
		 */
		//.....Zero Out Key Accumulators
		HFCount1 = 1;
		HFCount2 = 0;
		// Load First Value and set HFCount1 to one.
		temp_float = HF_Laser_Freq[0];
		// Loop on Key Freqs...and Accumulate
		for (x=1;x<HFlaser_cnt;x++)
		{
			if(temp_float == HF_Laser_Freq[x])
			{
				HF_Laser_Freq[x] = 0.0;			// Zero Out Value
				HFCount1++;						// Increment Count
			}
			else
				break;							// If No Match, we are done.
		}
		// Are we done or is there another freq?
		if (HF_Laser_Freq[x] != 0.0)
		{
			// Load Next Value and set HFCount2 to one.
			temp_float = HF_Laser_Freq[x];
			HFCount2 = 1;
			// Loop on Key Freqs...and Accumulate
			for (y = (x+1);y < HFlaser_cnt;y++) {
				if (temp_float == HF_Laser_Freq[y]) {
					HF_Laser_Freq[y] = 0.0;			// Zero Out Value
					HFCount2++;						// Increment Count
				} else
					break;							// If No Match, we are done.
			}
		}
		// Blank out remaining values...
		if (y<HFlaser_cnt)
		{
			for(x=y;x<HFlaser_cnt;x++)
				HF_Laser_Freq[x] = 0.0;			// Zero Out Value
		}
#if 0
		/*********************************************************
		 *
		 * TEST CODE FOR PRINTING QSORT VALUES
		 ********************************************************/
		StrmOn = 1;
		for (x=0;x<4;x++)
		{
			sprintf(tempstr,"HF_Laser_Freq[%d]:		%f\n", x, HF_Laser_Freq[x]);
			printf2(tempstr);
		}
		sprintf(tempstr,"HFCount1:		%d\n", HFCount1);
		printf2(tempstr);
		sprintf(tempstr,"HFCount2:		%d\n", HFCount2);
		printf2(tempstr);
		printf2("\n");
		StrmOn = 0;
		/*********************************************************
		 * END TEST CODE
		 ********************************************************/
#endif
		/*
		 * 	C. Qsort again Freqs Highest to lowest.
		 *
		 */
		qsort(HF_Laser_Freq, 4, sizeof(float), cmpfunc);
		/*********************************************************
		 *
		 * TEST CODE FOR PRINTING QSORT VALUES
		 ********************************************************/
		StrmOn = 1;
		for (x=0;x<4;x++)
		{
			sprintf(tempstr,"HF_Laser_Freq[%d]:		%f\n", x, HF_Laser_Freq[x]);
			printf2(tempstr);
		}
		sprintf(tempstr,"HFCount1:		%d\n", HFCount1);
		printf2(tempstr);
		sprintf(tempstr,"HFCount2:		%d\n", HFCount2);
		printf2(tempstr);
		printf2("\n");
//		StrmOn = 0;
		/*********************************************************
		 * END TEST CODE
		 ********************************************************/

		/*
		 * 	D. Program Lasers
		 */
		// Determine action from HF_Avail State.
		switch(HF_Avail)
		{
		case PLLC_HFMODE:
			// PLLC Channels All Available
			// Set PLL C to New Freq in HF_Laser_Freq[0]
			/*
			 * Power Up PLLs.
			 */
			hmc_pll_powerUp(PLL_C_HW);

			// Power Up Clock Circuit.
			PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

			// Determine which Freq is on both PLLC Channels
			if (HFCount1 == 2)
			{
				// Use HF_Laser_Freq[0] for Channels 1 and 3...PLLC
				printf2("PLLC: Ch1 and Ch3 Set to HF_Laser_Freq[0]\n");
				disp_HF_Parms( HF_Laser_Freq[0] );
				// Setup Synth for HF_Laser_Freq[0].
				hmc_SetupFreq(PLL_C_HW, HF_Laser_Freq[0]);
			} // EndIf (HFCount1 == 2)
			else
			{
				// Use HF_Laser_Freq[1] for Channels 1 and 3...PLLC
				printf2("PLLC: Ch1 and Ch3 Set to HF_Laser_Freq[1]\n");
				disp_HF_Parms( HF_Laser_Freq[1] );
				// Setup Synth for HF_Laser_Freq[1].
				hmc_SetupFreq(PLL_C_HW, HF_Laser_Freq[1]);
			} // EndElse (HFCount1 == 2)
			/*
			 * Enable Channel 1
			 * 	Powerup Channel 1 Common.
			 * 		P13/Pin 44: MTU0: LaserDiode0
			 */
			MPC.P13PFS.BYTE = 0x00U;					// No Periph Control.
			PORT1.PMR.BYTE &= ~0x08U;					// Setup as I/O.
			PORT1.PDR.BYTE |= 0x08U;					// Setup as Output.
			PORT1.PODR.BYTE &= ~0x08U;					// Set as LOW.
			/*
			 * Enable Channel 3
			 * 	Powerup Channel 3 Common.
			 * 		P17/Pin 38: MTU4: LaserDiode2b
			 */
			MPC.P17PFS.BYTE = 0x00U;					// No Periph Control.
			PORT1.PMR.BYTE &= ~0x80U;					// Setup as I/O.
			PORT1.PDR.BYTE |= 0x80U;					// Setup as Output.
			PORT1.PODR.BYTE &= ~0x80U;					// Set as LOW.
			/*
			 * Powerup HF Drivers Power Supply
			 */
			accurate_delay(10);
			PLMpls_gpio_Off( HF_Laser_Enable );
			/*
			 * Enable HF Laser 1 Driver.
			 */
			accurate_delay(10);
			PLMpls_HFlaser_enable( HF_LSR1_CNTL );
			PLMpls_HFlaser_enable( HF_LSR3_CNTL );

			/*------------------------------------------
			 * Need to Program Remaining Freq on PLLD
			 *-----------------------------------------*/
			// Set PLL D to New Freq in HF_Laser_Freq[0]
			/*
			 * Power Up PLLs.
			 */
			hmc_pll_powerUp(PLL_D_HW);

			// Power Up Clock Circuit.
			PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

			if (HFCount1 == 1)
			{
				// Use HF_Laser_Freq[0] for Channels 2 or 4...PLLD
				printf2("PLLD: Ch2 or Ch4 Set to HF_Laser_Freq[0]\n");
				disp_HF_Parms( HF_Laser_Freq[0] );
				// Setup Synth for HF_Laser_Freq[0].
				hmc_SetupFreq(PLL_D_HW, HF_Laser_Freq[0]);
			} // EndIf (HFCount1 == 1)
			else
			{
				// Use HF_Laser_Freq[1] for Channels 2 or 4...PLLD
				printf2("PLLD: Ch2 or Ch4 Set to HF_Laser_Freq[1]\n");
				disp_HF_Parms( HF_Laser_Freq[1] );
				// Setup Synth for HF_Laser_Freq[1].
				hmc_SetupFreq(PLL_D_HW, HF_Laser_Freq[1]);
			} // EndElse (HFCount1 == 1)

			// Is Channel 2 Available
			if ( (cntrl_flg & 0x02) > 0 )
			{
				/*
				 * Enable Channel 2
				 * 	Powerup Channel 2 Common.
				 * 		P20/Pin 37: MTU1: LaserDiode1
				 */
				MPC.P20PFS.BYTE = 0x00U;					// No Periph Control.
				PORT2.PMR.BYTE &= ~0x01U;					// Setup as I/O.
				PORT2.PDR.BYTE |= 0x01U;					// Setup as Output.
				PORT2.PODR.BYTE &= ~0x01U;					// Set as LOW.
				/*
				 * Powerup HF Drivers Power Supply
				 */
				accurate_delay(10);
				PLMpls_gpio_Off( HF_Laser_Enable );
				/*
				 * Enable HF Laser 1 Driver.
				 */
				accurate_delay(10);
				PLMpls_HFlaser_enable( HF_LSR2_CNTL );
			} // EndIf ( (cntrl_flg & 0x02) > 0 )
			else
			{
				/*
				 * Enable Channel 4
				 * 	Powerup Channel 1 Common.
				 * 		PA1/Pin 96: MTU7: LaserDiode3b
				 */
				MPC.PA1PFS.BYTE = 0x00U;					// No Periph Control.
				PORTA.PMR.BYTE &= ~0x02U;					// Setup as I/O.
				PORTA.PDR.BYTE |= 0x02U;					// Setup as Output.
				PORTA.PODR.BYTE &= ~0x02U;					// Set as LOW.
				/*
				 * Powerup HF Drivers Power Supply
				 */
				accurate_delay(10);
				PLMpls_gpio_Off( HF_Laser_Enable );
				/*
				 * Enable HF Laser 4 Driver.
				 */
				accurate_delay(10);
				PLMpls_HFlaser_enable( HF_LSR4_CNTL );
			} // EndElse ( (cntrl_flg & 0x02) > 0 )
			break;
		case PLLD_HFMODE:
			// PLLD Channels All Available
			/*
			 * Power Up PLLs.
			 */
			hmc_pll_powerUp(PLL_D_HW);

			// Power Up Clock Circuit.
			PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

			// Determine which Freq is on both PLLD Channels
			if (HFCount1 == 2)
			{
				// Use HF_Laser_Freq[0] for Channels 2 and 4...PLLD
				printf2("PLLD: Ch2 and Ch4 Set to HF_Laser_Freq[0]\n");
				disp_HF_Parms( HF_Laser_Freq[0] );
				// Setup Synth for HF_Laser_Freq[0].
				hmc_SetupFreq(PLL_D_HW, HF_Laser_Freq[0]);
			} // EndIf (HFCount1 == 2)
			else
			{
				// Use HF_Laser_Freq[1] for Channels 2 and 4...PLLD
				printf2("PLLD: Ch2 and Ch4 Set to HF_Laser_Freq[1]\n");
				disp_HF_Parms( HF_Laser_Freq[1] );
				// Setup Synth for HF_Laser_Freq[1].
				hmc_SetupFreq(PLL_D_HW, HF_Laser_Freq[1]);
			} // EndElse (HFCount1 == 2)
			/*
			 * Enable Channel 2
			 * 	Powerup Channel 2 Common.
			 * 		P20/Pin 37: MTU1: LaserDiode1
			 */
			MPC.P20PFS.BYTE = 0x00U;					// No Periph Control.
			PORT2.PMR.BYTE &= ~0x01U;					// Setup as I/O.
			PORT2.PDR.BYTE |= 0x01U;					// Setup as Output.
			PORT2.PODR.BYTE &= ~0x01U;					// Set as LOW.
			/*
			 * Enable Channel 4
			 * 	Powerup Channel 1 Common.
			 * 		PA1/Pin 96: MTU7: LaserDiode3b
			 */
			MPC.PA1PFS.BYTE = 0x00U;					// No Periph Control.
			PORTA.PMR.BYTE &= ~0x02U;					// Setup as I/O.
			PORTA.PDR.BYTE |= 0x02U;					// Setup as Output.
			PORTA.PODR.BYTE &= ~0x02U;					// Set as LOW.
			/*
			 * Powerup HF Drivers Power Supply
			 */
			accurate_delay(10);
			PLMpls_gpio_Off( HF_Laser_Enable );
			/*
			 * Enable HF Laser 1 Driver.
			 */
			accurate_delay(10);
			PLMpls_HFlaser_enable( HF_LSR2_CNTL );
			PLMpls_HFlaser_enable( HF_LSR4_CNTL );
			/*------------------------------------------
			 * Need to Program Remaining Freq on PLLC
			 *-----------------------------------------*/
			// Set PLL C to New Freq in HF_Laser_Freq[0]
			/*
			 * Power Up PLLs.
			 */
			hmc_pll_powerUp(PLL_C_HW);

			// Power Up Clock Circuit.
			PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

			if (HFCount1 == 1) {
				// Use HF_Laser_Freq[0] for Channels 1 or 3...PLLC
				printf2("PLLC: Ch1 or Ch3 Set to HF_Laser_Freq[0]\n");
				disp_HF_Parms( HF_Laser_Freq[0] );
				// Setup Synth for HF_Laser_Freq[0].
				hmc_SetupFreq(PLL_C_HW, HF_Laser_Freq[0]);
			} // EndIf (HFCount1 == 1)
			else {
				// Use HF_Laser_Freq[1] for Channels 1 or 3...PLLC
				printf2("PLLC: Ch1 or Ch3 Set to HF_Laser_Freq[1]\n");
				disp_HF_Parms( HF_Laser_Freq[1] );
				// Setup Synth for HF_Laser_Freq[1].
				hmc_SetupFreq(PLL_C_HW, HF_Laser_Freq[1]);
			} // EndElse (HFCount1 == 1)
			  // Is Channel 1 Available
			if ((cntrl_flg & 0x01) > 0) {
				/*
				 * Enable Channel 1
				 * 	Powerup Channel 1 Common.
				 * 		P13/Pin 44: MTU0: LaserDiode0
				 */
				MPC.P13PFS.BYTE = 0x00U;			// No Periph Control.
				PORT1.PMR.BYTE &= ~0x08U;					// Setup as I/O.
				PORT1.PDR.BYTE |= 0x08U;				// Setup as Output.
				PORT1.PODR.BYTE &= ~0x08U;					// Set as LOW.
				/*
				 * Powerup HF Drivers Power Supply
				 */
				accurate_delay(10);
				PLMpls_gpio_Off(HF_Laser_Enable);
				/*
				 * Enable HF Laser 1 Driver.
				 */
				accurate_delay(10);
				PLMpls_HFlaser_enable(HF_LSR1_CNTL);
			} // EndIf ( (cntrl_flg & 0x01) > 0 )
			else {
				/*
				 * Enable Channel 3
				 * 	Powerup Channel 3 Common.
				 * 		P17/Pin 38: MTU4: LaserDiode2b
				 */
				MPC.P17PFS.BYTE = 0x00U;			// No Periph Control.
				PORT1.PMR.BYTE &= ~0x80U;					// Setup as I/O.
				PORT1.PDR.BYTE |= 0x80U;				// Setup as Output.
				PORT1.PODR.BYTE &= ~0x80U;					// Set as LOW.
				/*
				 * Powerup HF Drivers Power Supply
				 */
				accurate_delay(10);
				PLMpls_gpio_Off(HF_Laser_Enable);
				/*
				 * Enable HF Laser 3 Driver.
				 */
				accurate_delay(10);
				PLMpls_HFlaser_enable(HF_LSR3_CNTL);
			} //EndElse ( (cntrl_flg & 0x01) > 0 )
			break;
		case BOTH_HFMODES:
			// All Channels Available
			// Program HF_Laser_Freq[0] for PLLC and PLLD.
			/*
			 * Power Up PLLs.
			 */
			hmc_pll_powerUp(PLL_C_HW);
			accurate_delay(10);
			hmc_pll_powerUp(PLL_D_HW);
			accurate_delay(10);

			// Power Up Clock Circuit.
			PLMpls_gpio_On(PLL_CLK_EN);	// Enable HF Clock by Setting Pin High.

			accurate_delay(10);
			// Test for Special Mode...
			if ((HFCount1 == 2) && (HFCount1 == 2))
			{
				// Set HF_Laser_Freq[0] Freq on both PLLC Channels.
				printf2("PLLC: Ch1 and Ch3 Set to HF_Laser_Freq[0]\n");
				disp_HF_Parms( HF_Laser_Freq[0] );
				hmc_SetupFreq(PLL_C_HW, HF_Laser_Freq[0]);
				accurate_delay(10);
				// Set HF_Laser_Freq[1] Freq on both PLLD Channels.
				printf2("PLLD: Ch2 and Ch4 Set to HF_Laser_Freq[1]\n");
				disp_HF_Parms( HF_Laser_Freq[1] );
				hmc_SetupFreq(PLL_D_HW, HF_Laser_Freq[1]);
				accurate_delay(10);
			} //EndIf ((HFCount1 == 2) && (HFCount1 == 2))
			else
			{
				// Set HF_Laser_Freq[0] Freq on both PLLC Channels.
				printf2("PLLC: Ch1 and Ch3 Set to HF_Laser_Freq[0]\n");
				disp_HF_Parms( HF_Laser_Freq[0] );
				hmc_SetupFreq(PLL_C_HW, HF_Laser_Freq[0]);
				accurate_delay(10);
				// Set HF_Laser_Freq[0] Freq on both PLLD Channels.
				printf2("PLLD: Ch2 and Ch4 Set to HF_Laser_Freq[0]\n");
				hmc_SetupFreq(PLL_D_HW, HF_Laser_Freq[0]);
				disp_HF_Parms( HF_Laser_Freq[0] );
				accurate_delay(10);
			} //EndElse ((HFCount1 == 2) && (HFCount1 == 2))
			  // Use all Channels for This mode.
			/*
			 * Enable Channel 1
			 * 	Powerup Channel 1 Common.
			 * 		P13/Pin 44: MTU0: LaserDiode0
			 */
			MPC.P13PFS.BYTE = 0x00U;				// No Periph Control.
			PORT1.PMR.BYTE &= ~0x08U;					// Setup as I/O.
			PORT1.PDR.BYTE |= 0x08U;					// Setup as Output.
			PORT1.PODR.BYTE &= ~0x08U;					// Set as LOW.
			/*
			 * Enable Channel 2
			 * 	Powerup Channel 2 Common.
			 * 		P20/Pin 37: MTU1: LaserDiode1
			 */
			MPC.P20PFS.BYTE = 0x00U;				// No Periph Control.
			PORT2.PMR.BYTE &= ~0x01U;					// Setup as I/O.
			PORT2.PDR.BYTE |= 0x01U;					// Setup as Output.
			PORT2.PODR.BYTE &= ~0x01U;					// Set as LOW.
			/*
			 * Enable Channel 3
			 * 	Powerup Channel 3 Common.
			 * 		P17/Pin 38: MTU4: LaserDiode2b
			 */
			MPC.P17PFS.BYTE = 0x00U;				// No Periph Control.
			PORT1.PMR.BYTE &= ~0x80U;					// Setup as I/O.
			PORT1.PDR.BYTE |= 0x80U;					// Setup as Output.
			PORT1.PODR.BYTE &= ~0x80U;					// Set as LOW.
			/*
			 * Enable Channel 4
			 * 	Powerup Channel 1 Common.
			 * 		PA1/Pin 96: MTU7: LaserDiode3b
			 */
			MPC.PA1PFS.BYTE = 0x00U;				// No Periph Control.
			PORTA.PMR.BYTE &= ~0x02U;					// Setup as I/O.
			PORTA.PDR.BYTE |= 0x02U;					// Setup as Output.
			PORTA.PODR.BYTE &= ~0x02U;					// Set as LOW.
			/*
			 * Powerup HF Drivers Power Supply
			 */
			accurate_delay(10);
			PLMpls_gpio_Off(HF_Laser_Enable);
			/*
			 * Enable HF Laser 1 Driver.
			 */
			accurate_delay(10);
			PLMpls_HFlaser_enable(HF_LSR1_CNTL);
			PLMpls_HFlaser_enable(HF_LSR2_CNTL);
			PLMpls_HFlaser_enable(HF_LSR3_CNTL);
			PLMpls_HFlaser_enable(HF_LSR4_CNTL);
			break;
		} // EndSwitch(HF_Avail)
		break;
	} // EndSwitch(HFlaser_cnt)

	StrmOn = 0;

	return HAL_OK;
}

//*****************************************************************************
//*
//* routine: ldlsrs_ena
//* Date: 	 May 16, 2006
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* Enable FPGA to load.
//*
//*****************************************************************************
void ldlsrs_ena(void) {
	//PORTE |= (1<<PORTE7);		               // Enable FPGA to load.
}

//*****************************************************************************
//*
//* routine: ldlsrs_dis
//* Date: 	 May 16, 2006
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* Disable FPGA to load.
//*
//*****************************************************************************
void ldlsrs_dis(void) {
	// Pulse Test0 to load data to Internal Latch
	//PORTB |= (1<<PORTB4);
	//PORTB &= ~(1<<PORTB4);
	// De-assert CLK_SLCT/ Reset
	//PORTE &= ~(1<<PORTE7);	   			               // Disable FPGA to load/Deassert CLK_SLCT.
}
//*****************************************************************************
//*
//* routine: lasers_off
//* Date: 	 May 16, 2006
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* Turn off all lasers by loading zero.
//*
//*****************************************************************************
void lasers_off(void) {
	// Power Down all lasers.
	R_MTU3_AllLasers_Off();
	// Now Disable HF PLLs.
	hmc_sleep_plls();
}

//*****************************************************************************
//*
//* routine: lasers_on
//* Date: 	 May 22, 2006
//* Updated: February 7, 2015
//* Author:  Ralph Pruitt
//* Turn on all lasers by loading zero.
//*
//*****************************************************************************
void lasers_on(void) {
	//	Set Each Pin of Laser Control as Output High No Peripheral.
	//P13/Pin 44: MTU0: LaserDiode0
	MPC.P13PFS.BYTE = 0x00U;					// No Periph Control.
	PORT1.PMR.BYTE &= ~0x08U;					// Setup as I/O.
	PORT1.PDR.BYTE |= 0x08U;					// Setup as Output.
	PORT1.PODR.BYTE &= ~0x08U;					// Set as LOW.
	//P20/Pin 37: MTU1: LaserDiode1
	MPC.P20PFS.BYTE = 0x00U;					// No Periph Control.
	PORT2.PMR.BYTE &= ~0x01U;					// Setup as I/O.
	PORT2.PDR.BYTE |= 0x01U;					// Setup as Output.
	PORT2.PODR.BYTE &= ~0x01U;					// Set as LOW.
	//P14/Pin 43: MTU3: PLLInput2
	MPC.P14PFS.BYTE = 0x00U;					// No Periph Control.
	PORT1.PMR.BYTE &= ~0x10U;					// Setup as I/O.
	PORT1.PDR.BYTE |= 0x10U;					// Setup as Output.
	PORT1.PODR.BYTE |= 0x10U;					// Set as HIGH.
	// P17/Pin 38: MTU4: LaserDiode2b
	MPC.P17PFS.BYTE = 0x00U;					// No Periph Control.
	PORT1.PMR.BYTE &= ~0x80U;					// Setup as I/O.
	PORT1.PDR.BYTE |= 0x80U;					// Setup as Output.
	PORT1.PODR.BYTE &= ~0x80U;					// Set as LOW.
	//PA0/Pin 97: MTU6: PLLInput3
	MPC.PA0PFS.BYTE = 0x00U;					// No Periph Control.
	PORTA.PMR.BYTE &= ~0x01U;					// Setup as I/O.
	PORTA.PDR.BYTE |= 0x01U;					// Setup as Output.
	PORTA.PODR.BYTE |= 0x01U;					// Set as HIGH.
	//PA1/Pin 96: MTU7: LaserDiode3b
	MPC.PA1PFS.BYTE = 0x00U;					// No Periph Control.
	PORTA.PMR.BYTE &= ~0x02U;					// Setup as I/O.
	PORTA.PDR.BYTE |= 0x02U;					// Setup as Output.
	PORTA.PODR.BYTE &= ~0x02U;					// Set as LOW.

	//  Disable Frequency Multipliers....Set Enable Pins as Output Low.
	PORT0.PDR.BYTE |= 0x02;						// Set PLLC_Enable as Output
	PORT0.PODR.BYTE &= ~0x02;					// Set PLLC_Enable as LOW.
	PORT2.PDR.BYTE |= 0x10;						// Set PLLD_Enable as Output
	PORT2.PODR.BYTE &= ~0x10;					// Set PLLD_Enable as LOW.
}

void Lasermonitor(char *parm1) {
	int errCode;
	if ( strcmp(parm1, "on") == 0) {
		printf2("Laser On.\n");
		errCode = init_laser(0, 1);
		if (errCode == 0)
			printf2("Succesful!\n");
		else if (errCode == -1)
			printf2(" Parameter Error!\n");
		else if (errCode == -2)
			printf2(" Busy Timeout!\n");
		else if (errCode == -3)
			printf2(" Parameter Failure!\n");
	} else if ( strcmp(parm1, "off") == 0) {
		printf2("Laser Off.\n");
		laser_off();
	} else if ( strcmp(parm1, "hmc25_c") == 0) {
		printf2("PLLC set to 25MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		PLLC PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		VCOCC PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Setup Synth for 25MHz.
		if (hmc_SetupFreq(PLL_C_HW, 25000000.0) == HAL_OK)
			printf2("		Task Synth 25Mhz: SUCCESS!\n");
	} else if ( strcmp(parm1, "hmc50_c") == 0) {
		printf2("PLLC set to 25MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		PLLC PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		VCOCC PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Setup Synth for 50MHz.
		if (hmc_SetupFreq(PLL_C_HW, 50000000.0) == HAL_OK)
			printf2("		Task Synth 50Mhz: SUCCESS!\n");
	} else if ( strcmp(parm1, "hmc66_c") == 0) {
		printf2("PLLC set to 25MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		PLLC PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		VCOCC PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Setup Synth for 66MHz.
		if (hmc_SetupFreq(PLL_C_HW, 66000000.0) == HAL_OK)
			printf2("		Task Synth 66Mhz: SUCCESS!\n");
	} else if ( strcmp(parm1, "hmcOFF_c") == 0) {
		printf2("PLLC disabled.\n");
		// Power Down Clock Circuit.
		PLMpls_gpio_Off(PLL_CLK_EN);	// Disable HF Clock by Setting Pin Low.

		/*
		 * Power Down VCOs.
		 */
		hmc_vco_powerDn(PLL_C_HW);

		/*
		 * Power Down PLLs.
		 */
		hmc_pll_powerDn(PLL_C_HW);
	} else {
		errCode = init_laser((unsigned int) atoi(parm1), 1);
		if (errCode == 0)
			printf2("Succesful!\n");
		else if (errCode == -1)
			printf2(" Parameter Error!\n");
		else if (errCode == -2)
			printf2(" Busy Timeout!\n");
		else if (errCode == -3)
			printf2(" Parameter Failure!\n");
	}
	printf2("\n\n");
}

#define SIG_25MHZ	25000000.0
#define SIG_50MHZ	50000000.0
#define SIG_66MHZ	66000000.0
#define SIG_90MHZ	90000000.0
#define WAIT_DELAY	10
void hmcmonitor(char *parm1) {
	char tempstr[80];
	pll_registers pll_data1, Test_Data1;
	PLL_Port_Regs pll_rxdata2;

	PLL_Parameters Template_Parms;

	if ( strcmp(parm1, "25_c") == 0)
	{
		printf2("PLLC set to 25MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		PLLC PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCOCC PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Lets Get parameters first so we can See values.
		Template_Parms.Desired_Freq = SIG_25MHZ;
		hmc_calc_parameters(&Template_Parms);
		// Now Print Parms.
		sprintf(tempstr, "	Output_Divider:%d\n", Template_Parms.Output_Divider);
		printf2(tempstr);
		sprintf(tempstr, "	N_Divider:%d / %d\n", Template_Parms.N_Divider_int, Template_Parms.N_Divider_frac);
		printf2(tempstr);
		sprintf(tempstr, "	R_Divider:%d\n", Template_Parms.R_Divider);
		printf2(tempstr);
		// Setup Synth for 25MHz.
		if (hmc_SetupFreq(PLL_C_HW, SIG_25MHZ) == HAL_OK)
			printf2("		Task Synth 25Mhz: SUCCESS!\n");
		else
			printf2("		Task Synth 25Mhz: FAILED!\n");
	}
	else if ( strcmp(parm1, "50_c") == 0)
	{
		printf2("PLLC set to 50MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		PLL C PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCO C PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Lets Get parameters first so we can See values.
		Template_Parms.Desired_Freq = SIG_50MHZ;
		hmc_calc_parameters(&Template_Parms);
		// Now Print Parms.
		sprintf(tempstr, "	Output_Divider:%d\n", Template_Parms.Output_Divider);
		printf2(tempstr);
		sprintf(tempstr, "	N_Divider:%d / %d\n", Template_Parms.N_Divider_int, Template_Parms.N_Divider_frac);
		printf2(tempstr);
		sprintf(tempstr, "	R_Divider:%d\n", Template_Parms.R_Divider);
		printf2(tempstr);
		// Setup Synth for 50MHz.
		if (hmc_SetupFreq(PLL_C_HW, SIG_50MHZ) == HAL_OK)
			printf2("		Task Synth 50Mhz: SUCCESS!\n");
		else
			printf2("		Task Synth 50Mhz: Failed!\n");
	}
	else if ( strcmp(parm1, "66_c") == 0) {
		printf2("PLLC set to 66MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		PLLC PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCO C PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Lets Get parameters first so we can See values.
		Template_Parms.Desired_Freq = SIG_66MHZ;
		hmc_calc_parameters(&Template_Parms);
		// Now Print Parms.
		sprintf(tempstr, "	Output_Divider:%d\n", Template_Parms.Output_Divider);
		printf2(tempstr);
		sprintf(tempstr, "	N_Divider:%d / %d\n", Template_Parms.N_Divider_int, Template_Parms.N_Divider_frac);
		printf2(tempstr);
		sprintf(tempstr, "	R_Divider:%d\n", Template_Parms.R_Divider);
		printf2(tempstr);
		// Setup Synth for 66MHz.
		if (hmc_SetupFreq(PLL_C_HW, SIG_66MHZ) == HAL_OK)
			printf2("		Task Synth 66Mhz: SUCCESS!\n");
		else
			printf2("		Task Synth 66Mhz: FAILED!\n");
	}
	else if ( strcmp(parm1, "90_c") == 0) {
		printf2("PLLC set to 90MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		PLLC PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCO C PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Lets Get parameters first so we can See values.
		Template_Parms.Desired_Freq = SIG_90MHZ;
		hmc_calc_parameters(&Template_Parms);
		// Now Print Parms.
		sprintf(tempstr, "	Output_Divider:%d\n", Template_Parms.Output_Divider);
		printf2(tempstr);
		sprintf(tempstr, "	N_Divider:%d / %d\n", Template_Parms.N_Divider_int, Template_Parms.N_Divider_frac);
		printf2(tempstr);
		sprintf(tempstr, "	R_Divider:%d\n", Template_Parms.R_Divider);
		printf2(tempstr);
		// Setup Synth for 66MHz.
		if (hmc_SetupFreq(PLL_C_HW, SIG_90MHZ) == HAL_OK)
			printf2("		Task Synth 90Mhz: SUCCESS!\n");
		else
			printf2("		Task Synth 90Mhz: FAILED!\n");
	}
	else if ( strcmp(parm1, "TST_c") == 0) {
		printf2("PLLC set to 90MHz...TEST.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		PLLC PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCO C PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Lets Get parameters first so we can See values.
		Template_Parms.Desired_Freq = SIG_90MHZ;
		hmc_calc_parameters(&Template_Parms);
		// Now Print Parms.
		sprintf(tempstr, "	Output_Divider:%d\n", Template_Parms.Output_Divider);
		printf2(tempstr);
		sprintf(tempstr, "	N_Divider:%d / %d\n", Template_Parms.N_Divider_int, Template_Parms.N_Divider_frac);
		printf2(tempstr);
		sprintf(tempstr, "	R_Divider:%d\n", Template_Parms.R_Divider);
		printf2(tempstr);

		// BIT BANG SETTINGS...
		// 1. Write to REG 0 20.
		// 			Reg00 = 00100000  -  RESET command.
		pll_data1.Data = 0x20;
		Test_Data1.chip_idRD.Soft_Rst = 1;		// RESET command.
		sprintf(tempstr, "1. RAW: %08x	STRCT: %08X\n", pll_data1.Data, Test_Data1.Data);
		printf2(tempstr);
		if (hmc_spi_write_read(PLL_C_HW, 0x00, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 1: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 1: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 *  2. Write to REG 1 2.
		 *		Reg01 = 00000010 - Default = 2.
		 * 			This value assigns PLL Chip Enable control to the SPI Reg 1 [1], 1 enabled, 0 disabled.
		 * 			To assign PLL CE control to CE pin, write Reg 1[0]=1.
		 */
		pll_data1.Data = 0x02;
		if (hmc_spi_write_read(PLL_C_HW, 0x01, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 2: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 2: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	3. Write to REG 2 1.
		 * 		Reg02 = 00000001 - REFDIV Register =  0x01 Ref Divider Register-Default value = 1h (Rdiv=1). Program as needed.
		 */
		pll_data1.Data = 0x01;
		if (hmc_spi_write_read(PLL_C_HW, 0x02, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 3: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 3: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	4. Write to REG 3 B4.
		 * 		Reg03 = 10110100 - Frequency Register, Integer Part Integer VCO Divider Register-Progarm as needed to set frequency.
		 */
		//pll_data1.Data = 0xB4;
		pll_data1.Data = 0x87;
		if (hmc_spi_write_read(PLL_C_HW, 0x03, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 4: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 4: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 5. Write to REG 5 1010   // Reg02 = 000010000 = fo (VCO output Div-by-32);
		//pll_data1.Data = 0x1010;
		pll_data1.Data = 0x0C10;					// 0000.1100.0001.0000
		Test_Data1.spi_vco.VCO_REGADDR = 0x02;		// Reg02
		Test_Data1.spi_vco.VCO_ID = 0x00;			// ID always zero
		Test_Data1.spi_vco.VCO_DATA = 24;			// Set Divisor as 24.
		sprintf(tempstr, "5. RAW: %08x	STRCT: %08X\n", pll_data1.Data, Test_Data1.Data);
		printf2(tempstr);
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 5: SUCCESS!\n");
		else
			printf2("		CMD 5: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * Power Up VCOs.
		 */
		if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		VCO POWERUP: SUCCESS!\n");
		else
			printf2("		VCO POWERUP: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 6. Write to REG 5 F98    // Reg03 = 000011111 = Hi Perf, RF_P & RF_N enabled, 5dB RL,
		pll_data1.Data = 0x0F98;
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 6: SUCCESS!\n");
		else
			printf2("		CMD 6: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 7. Write to REG 5 4B38   // Reg07 = 010010110 = o/p -6dB.  For maximum o/p power program 4DB8h.
		pll_data1.Data = 0x4B38;
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 7: SUCCESS!\n");
		else
			printf2("		CMD 7: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 8. Write to REG 5 0.
		pll_data1.Data = 0x0;
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 8: SUCCESS!\n");
		else
			printf2("		CMD 8: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	9. Write to REG 6 F4A.
		 * 		Reg06 = F4A Delta-Sigma Modulator Configuration Register. Program this value for Frac Mode.
		 */
		pll_data1.Data = 0x0F4A;
		if (hmc_spi_write_read(PLL_C_HW, 0x06, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 9: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 9: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	10. Write to REG 7 14D.
		 * 		14Dh is the default value for LD programming (correct for 50MHz comparison).
		 * 		For different configurations, especially higher PFD rates, this may need to change.
		 */
		pll_data1.Data = 0x014D;
		if (hmc_spi_write_read(PLL_C_HW, 0x07, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 10: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 10: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	11. Write to REG 8 C1BEFF.
		 * 		Default value = C1BEFFh.  No need to program.
		 */
		pll_data1.Data = 0xC1BEFF;
		if (hmc_spi_write_read(PLL_C_HW, 0x08, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 11: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 11: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	12. Write to REG 9 3FFEFD.
		 * 		CP Register-Program as needed. 3FFEFDh = 2.54mA CP current with 635uA Up CP Offset current.
		 */
		pll_data1.Data = 0x3FFEFD;
		if (hmc_spi_write_read(PLL_C_HW, 0x09, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 12: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 12: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	13. Write to REG A 2046.
		 * 		VCO Tuning Configuration Register-Program this value.
		 */
		pll_data1.Data = 0x2046;
		if (hmc_spi_write_read(PLL_C_HW, 0x0A, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 13: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 13: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	14. Write to REG B 4F8061.
		 * 		PFD/CP Control Register.  Default value = F8061h.
		 * 		4F8061h sets LD/SDO output level to 3.3V from 1.8V default (bit[22]=1 sets 3.3V output level).
		 */
		pll_data1.Data = 0x4F8061;
		if (hmc_spi_write_read(PLL_C_HW, 0x0B, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 14: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 14: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	15. Write to REG C 0.
		 * 		Exact Frequency register.  Default value =0h.  No need to program if not using Exact Frequency Mode.
		 */
		pll_data1.Data = 0x00;
		if (hmc_spi_write_read(PLL_C_HW, 0x0C, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 15: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 15: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	16. Write to REG F 81.
		 * 		Default vaue =1. 81h configures LD/SDO pin to output LD status always,
		 * 			except during SPI reads when the pin is automatically mux'ed to output the serial data.
		 */
#if 0
		pll_data1.Data = 0x81;
		if (hmc_spi_write_read(PLL_C_HW, 0x0F, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 16: SUCCESS!\n");
		else
			printf2("		CMD 16: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command
#endif

		/*
		 * 	17. Write to REG 4 0.
		 * 		Fractional VCO Divider Register-Program as needed to set frequency. When this register is written, a VCO auto-cal is initiated.
		 */
		pll_data1.Data = 0x00;
		if (hmc_spi_write_read(PLL_C_HW, 0x04, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 17: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 17: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

	}
	else if ( strcmp(parm1, "TST1_c") == 0) {
		printf2("PLLC set to 90MHz...TEST.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		PLLC PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCO C PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Lets Get parameters first so we can See values.
		Template_Parms.Desired_Freq = SIG_90MHZ;
		hmc_calc_parameters(&Template_Parms);
		// Now Print Parms.
		sprintf(tempstr, "	Output_Divider:%d\n", Template_Parms.Output_Divider);
		printf2(tempstr);
		sprintf(tempstr, "	N_Divider:%d / %d\n", Template_Parms.N_Divider_int, Template_Parms.N_Divider_frac);
		printf2(tempstr);
		sprintf(tempstr, "	R_Divider:%d\n", Template_Parms.R_Divider);
		printf2(tempstr);

		// BIT BANG SETTINGS...
		// 1. Write to REG 0 20.
		// 			Reg00 = 00100000  -  RESET command.
		pll_data1.Data = 0x20;
		Test_Data1.chip_idRD.Soft_Rst = 1;		// RESET command.
		sprintf(tempstr, "1. RAW: %08x	STRCT: %08X\n", pll_data1.Data, Test_Data1.Data);
		printf2(tempstr);
		if (hmc_spi_write_read(PLL_C_HW, 0x00, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 1: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 1: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 *  2. Write to REG 1 2.
		 *		Reg01 = 00000010 - Default = 2.
		 * 			This value assigns PLL Chip Enable control to the SPI Reg 1 [1], 1 enabled, 0 disabled.
		 * 			To assign PLL CE control to CE pin, write Reg 1[0]=1.
		 */
		pll_data1.Data = 0x02;
		if (hmc_spi_write_read(PLL_C_HW, 0x01, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 2: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 2: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	3. Write to REG 2 1.
		 * 		Reg02 = 00000001 - REFDIV Register =  0x01 Ref Divider Register-Default value = 1h (Rdiv=1). Program as needed.
		 */
		pll_data1.Data = 0x01;
		if (hmc_spi_write_read(PLL_C_HW, 0x02, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 3: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 3: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	4. Write to REG 3 B4.
		 * 		Reg03 = 10110100 - Frequency Register, Integer Part Integer VCO Divider Register-Progarm as needed to set frequency.
		 */
		pll_data1.Data = 0xB4;
		if (hmc_spi_write_read(PLL_C_HW, 0x03, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 4: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 4: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 5. Write to REG 5 1010   // Reg02 = 000010000 = fo (VCO output Div-by-32);
		pll_data1.Data = 0x1010;
		Test_Data1.spi_vco.VCO_REGADDR = 0x02;		// Reg02
		Test_Data1.spi_vco.VCO_ID = 0x00;			// ID always zero
		Test_Data1.spi_vco.VCO_DATA = 32;			// Set Divisor as 32.
		sprintf(tempstr, "5. RAW: %08x	STRCT: %08X\n", pll_data1.Data, Test_Data1.Data);
		printf2(tempstr);
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 5: SUCCESS!\n");
		else
			printf2("		CMD 5: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * Power Up VCOs.
		 */
		if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		VCO POWERUP: SUCCESS!\n");
		else
			printf2("		VCO POWERUP: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 6. Write to REG 5 F98    // Reg03 = 000011111 = Hi Perf, RF_P & RF_N enabled, 5dB RL,
		pll_data1.Data = 0x0F98;
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 6: SUCCESS!\n");
		else
			printf2("		CMD 6: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 7. Write to REG 5 4B38   // Reg07 = 010010110 = o/p -6dB.  For maximum o/p power program 4DB8h.
		pll_data1.Data = 0x4B38;
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 7: SUCCESS!\n");
		else
			printf2("		CMD 7: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 8. Write to REG 5 0.
		pll_data1.Data = 0x0;
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 8: SUCCESS!\n");
		else
			printf2("		CMD 8: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	9. Write to REG 6 F4A.
		 * 		Reg06 = F4A Delta-Sigma Modulator Configuration Register. Program this value for Frac Mode.
		 */
		pll_data1.Data = 0x0F4A;
		if (hmc_spi_write_read(PLL_C_HW, 0x06, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 9: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 9: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	10. Write to REG 7 14D.
		 * 		14Dh is the default value for LD programming (correct for 50MHz comparison).
		 * 		For different configurations, especially higher PFD rates, this may need to change.
		 */
		pll_data1.Data = 0x014D;
		if (hmc_spi_write_read(PLL_C_HW, 0x07, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 10: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 10: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	11. Write to REG 8 C1BEFF.
		 * 		Default value = C1BEFFh.  No need to program.
		 */
		pll_data1.Data = 0xC1BEFF;
		if (hmc_spi_write_read(PLL_C_HW, 0x08, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 11: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 11: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	12. Write to REG 9 3FFEFD.
		 * 		CP Register-Program as needed. 3FFEFDh = 2.54mA CP current with 635uA Up CP Offset current.
		 */
		pll_data1.Data = 0x3FFEFD;
		if (hmc_spi_write_read(PLL_C_HW, 0x09, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 12: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 12: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	13. Write to REG A 2046.
		 * 		VCO Tuning Configuration Register-Program this value.
		 */
		pll_data1.Data = 0x2046;
		if (hmc_spi_write_read(PLL_C_HW, 0x0A, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 13: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 13: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	14. Write to REG B 4F8061.
		 * 		PFD/CP Control Register.  Default value = F8061h.
		 * 		4F8061h sets LD/SDO output level to 3.3V from 1.8V default (bit[22]=1 sets 3.3V output level).
		 */
		pll_data1.Data = 0x4F8061;
		if (hmc_spi_write_read(PLL_C_HW, 0x0B, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 14: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 14: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	15. Write to REG C 0.
		 * 		Exact Frequency register.  Default value =0h.  No need to program if not using Exact Frequency Mode.
		 */
		pll_data1.Data = 0x00;
		if (hmc_spi_write_read(PLL_C_HW, 0x0C, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 15: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 15: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	16. Write to REG F 81.
		 * 		Default vaue =1. 81h configures LD/SDO pin to output LD status always,
		 * 			except during SPI reads when the pin is automatically mux'ed to output the serial data.
		 */
#if 0
		pll_data1.Data = 0x81;
		if (hmc_spi_write_read(PLL_C_HW, 0x0F, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 16: SUCCESS!\n");
		else
			printf2("		CMD 16: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command
#endif

		/*
		 * 	17. Write to REG 4 0.
		 * 		Fractional VCO Divider Register-Program as needed to set frequency. When this register is written, a VCO auto-cal is initiated.
		 */
		pll_data1.Data = 0x00;
		if (hmc_spi_write_read(PLL_C_HW, 0x04, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 17: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 17: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

	}
	else if ( strcmp(parm1, "TST66_c") == 0) {
		printf2("PLLC set to 90MHz...TEST.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		PLLC PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCO C PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Lets Get parameters first so we can See values.
		Template_Parms.Desired_Freq = SIG_66MHZ;
		hmc_calc_parameters(&Template_Parms);
		// Now Print Parms.
		sprintf(tempstr, "	Output_Divider:%d\n", Template_Parms.Output_Divider);
		printf2(tempstr);
		sprintf(tempstr, "	N_Divider:%d / %d\n", Template_Parms.N_Divider_int, Template_Parms.N_Divider_frac);
		printf2(tempstr);
		sprintf(tempstr, "	R_Divider:%d\n", Template_Parms.R_Divider);
		printf2(tempstr);

		// BIT BANG SETTINGS...
		// 1. Write to REG 0 20.
		// 			Reg00 = 00100000  -  RESET command.
		pll_data1.Data = 0x20;
		Test_Data1.chip_idRD.Soft_Rst = 1;		// RESET command.
		sprintf(tempstr, "1. RAW: %08x	STRCT: %08X\n", pll_data1.Data, Test_Data1.Data);
		printf2(tempstr);
		if (hmc_spi_write_read(PLL_C_HW, 0x00, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 1: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 1: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 *  2. Write to REG 1 2.
		 *		Reg01 = 00000010 - Default = 2.
		 * 			This value assigns PLL Chip Enable control to the SPI Reg 1 [1], 1 enabled, 0 disabled.
		 * 			To assign PLL CE control to CE pin, write Reg 1[0]=1.
		 */
		pll_data1.Data = 0x02;
		if (hmc_spi_write_read(PLL_C_HW, 0x01, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 2: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 2: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	3. Write to REG 2 1.
		 * 		Reg02 = 00000001 - REFDIV Register =  0x01 Ref Divider Register-Default value = 1h (Rdiv=1). Program as needed.
		 */
		pll_data1.Data = 0x01;
		if (hmc_spi_write_read(PLL_C_HW, 0x02, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 3: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 3: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	4. Write to REG 3 B4.
		 * 		Reg03 = 10110100 - Frequency Register, Integer Part Integer VCO Divider Register-Progarm as needed to set frequency.
		 */
		//pll_data1.Data = 0xB4;
		pll_data1.Data = 136;
		if (hmc_spi_write_read(PLL_C_HW, 0x03, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 4: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 4: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 5. Write to REG 5 1010   // Reg02 = 000010000 = fo (VCO output Div-by-33);
		//pll_data1.Data = 0x1010;
		pll_data1.Data = 0x1090;					// 0001.0000.1001.0000
		Test_Data1.spi_vco.VCO_REGADDR = 0x02;		// Reg02
		Test_Data1.spi_vco.VCO_ID = 0x00;			// ID always zero
		Test_Data1.spi_vco.VCO_DATA = 33;			// Set Divisor as 24.
		sprintf(tempstr, "5. RAW: %08x	STRCT: %08X\n", pll_data1.Data, Test_Data1.Data);
		printf2(tempstr);
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 5: SUCCESS!\n");
		else
			printf2("		CMD 5: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * Power Up VCOs.
		 */
		if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		VCO POWERUP: SUCCESS!\n");
		else
			printf2("		VCO POWERUP: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 6. Write to REG 5 F98    // Reg03 = 000011111 = Hi Perf, RF_P & RF_N enabled, 5dB RL,
		pll_data1.Data = 0x0F98;
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 6: SUCCESS!\n");
		else
			printf2("		CMD 6: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 7. Write to REG 5 4B38   // Reg07 = 010010110 = o/p -6dB.  For maximum o/p power program 4DB8h.
		pll_data1.Data = 0x4B38;
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 7: SUCCESS!\n");
		else
			printf2("		CMD 7: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 8. Write to REG 5 0.
		pll_data1.Data = 0x0;
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 8: SUCCESS!\n");
		else
			printf2("		CMD 8: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	9. Write to REG 6 F4A.
		 * 		Reg06 = F4A Delta-Sigma Modulator Configuration Register. Program this value for Frac Mode.
		 */
		pll_data1.Data = 0x0F4A;
		if (hmc_spi_write_read(PLL_C_HW, 0x06, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 9: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 9: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	10. Write to REG 7 14D.
		 * 		14Dh is the default value for LD programming (correct for 50MHz comparison).
		 * 		For different configurations, especially higher PFD rates, this may need to change.
		 */
		pll_data1.Data = 0x014D;
		if (hmc_spi_write_read(PLL_C_HW, 0x07, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 10: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 10: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	11. Write to REG 8 C1BEFF.
		 * 		Default value = C1BEFFh.  No need to program.
		 */
		pll_data1.Data = 0xC1BEFF;
		if (hmc_spi_write_read(PLL_C_HW, 0x08, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 11: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 11: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	12. Write to REG 9 3FFEFD.
		 * 		CP Register-Program as needed. 3FFEFDh = 2.54mA CP current with 635uA Up CP Offset current.
		 */
		pll_data1.Data = 0x3FFEFD;
		if (hmc_spi_write_read(PLL_C_HW, 0x09, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 12: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 12: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	13. Write to REG A 2046.
		 * 		VCO Tuning Configuration Register-Program this value.
		 */
		pll_data1.Data = 0x2046;
		if (hmc_spi_write_read(PLL_C_HW, 0x0A, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 13: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 13: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	14. Write to REG B 4F8061.
		 * 		PFD/CP Control Register.  Default value = F8061h.
		 * 		4F8061h sets LD/SDO output level to 3.3V from 1.8V default (bit[22]=1 sets 3.3V output level).
		 */
		pll_data1.Data = 0x4F8061;
		if (hmc_spi_write_read(PLL_C_HW, 0x0B, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 14: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 14: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	15. Write to REG C 0.
		 * 		Exact Frequency register.  Default value =0h.  No need to program if not using Exact Frequency Mode.
		 */
		pll_data1.Data = 0x00;
		if (hmc_spi_write_read(PLL_C_HW, 0x0C, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 15: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 15: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	16. Write to REG F 81.
		 * 		Default vaue =1. 81h configures LD/SDO pin to output LD status always,
		 * 			except during SPI reads when the pin is automatically mux'ed to output the serial data.
		 */
#if 0
		pll_data1.Data = 0x81;
		if (hmc_spi_write_read(PLL_C_HW, 0x0F, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 16: SUCCESS!\n");
		else
			printf2("		CMD 16: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command
#endif

		/*
		 * 	17. Write to REG 4 0.
		 * 		Fractional VCO Divider Register-Program as needed to set frequency. When this register is written, a VCO auto-cal is initiated.
		 */
		pll_data1.Data = 0x1fff00;
		if (hmc_spi_write_read(PLL_C_HW, 0x04, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 17: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 17: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

	}
	else if ( strcmp(parm1, "TST66a_c") == 0) {
		printf2("PLLC set to 90MHz...TEST.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		PLLC PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCO C PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Lets Get parameters first so we can See values.
		Template_Parms.Desired_Freq = SIG_90MHZ;
		hmc_calc_parameters(&Template_Parms);
		// Now Print Parms.
		sprintf(tempstr, "	Output_Divider:%d\n", Template_Parms.Output_Divider);
		printf2(tempstr);
		sprintf(tempstr, "	N_Divider:%d / %d\n", Template_Parms.N_Divider_int, Template_Parms.N_Divider_frac);
		printf2(tempstr);
		sprintf(tempstr, "	R_Divider:%d\n", Template_Parms.R_Divider);
		printf2(tempstr);

		// BIT BANG SETTINGS...
		// 1. Write to REG 0 20.
		// 			Reg00 = 00100000  -  RESET command.
		pll_data1.Data = 0x20;
		Test_Data1.chip_idRD.Soft_Rst = 1;		// RESET command.
		sprintf(tempstr, "1. RAW: %08x	STRCT: %08X\n", pll_data1.Data, Test_Data1.Data);
		printf2(tempstr);
		if (hmc_spi_write_read(PLL_C_HW, 0x00, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 1: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 1: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 *  2. Write to REG 1 2.
		 *		Reg01 = 00000010 - Default = 2.
		 * 			This value assigns PLL Chip Enable control to the SPI Reg 1 [1], 1 enabled, 0 disabled.
		 * 			To assign PLL CE control to CE pin, write Reg 1[0]=1.
		 */
		pll_data1.Data = 0x02;
		if (hmc_spi_write_read(PLL_C_HW, 0x01, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 2: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 2: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	3. Write to REG 2 1.
		 * 		Reg02 = 00000001 - REFDIV Register =  0x01 Ref Divider Register-Default value = 1h (Rdiv=1). Program as needed.
		 */
		pll_data1.Data = 0x01;
		if (hmc_spi_write_read(PLL_C_HW, 0x02, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 3: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 3: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	4. Write to REG 3 B4.
		 * 		Reg03 = 10110100 - Frequency Register, Integer Part Integer VCO Divider Register-Progarm as needed to set frequency.
		 */
		pll_data1.Data = 0xB5;
		if (hmc_spi_write_read(PLL_C_HW, 0x03, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 4: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 4: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 5. Write to REG 5 1010   // Reg02 = 000010000 = fo (VCO output Div-by-44);
		pll_data1.Data = 0x1610;
		Test_Data1.spi_vco.VCO_REGADDR = 0x02;		// Reg02
		Test_Data1.spi_vco.VCO_ID = 0x00;			// ID always zero
		Test_Data1.spi_vco.VCO_DATA = 44;			// Set Divisor as 32.
		sprintf(tempstr, "5. RAW: %08x	STRCT: %08X\n", pll_data1.Data, Test_Data1.Data);
		printf2(tempstr);
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 5: SUCCESS!\n");
		else
			printf2("		CMD 5: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * Power Up VCOs.
		 */
		if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		VCO POWERUP: SUCCESS!\n");
		else
			printf2("		VCO POWERUP: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 6. Write to REG 5 F98    // Reg03 = 000011111 = Hi Perf, RF_P & RF_N enabled, 5dB RL,
		pll_data1.Data = 0x0F98;
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 6: SUCCESS!\n");
		else
			printf2("		CMD 6: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 7. Write to REG 5 4B38   // Reg07 = 010010110 = o/p -6dB.  For maximum o/p power program 4DB8h.
		pll_data1.Data = 0x4B38;
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 7: SUCCESS!\n");
		else
			printf2("		CMD 7: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 8. Write to REG 5 0.
		pll_data1.Data = 0x0;
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 8: SUCCESS!\n");
		else
			printf2("		CMD 8: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	9. Write to REG 6 F4A.
		 * 		Reg06 = F4A Delta-Sigma Modulator Configuration Register. Program this value for Frac Mode.
		 */
		pll_data1.Data = 0x0F4A;
		if (hmc_spi_write_read(PLL_C_HW, 0x06, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 9: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 9: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	10. Write to REG 7 14D.
		 * 		14Dh is the default value for LD programming (correct for 50MHz comparison).
		 * 		For different configurations, especially higher PFD rates, this may need to change.
		 */
		pll_data1.Data = 0x014D;
		if (hmc_spi_write_read(PLL_C_HW, 0x07, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 10: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 10: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	11. Write to REG 8 C1BEFF.
		 * 		Default value = C1BEFFh.  No need to program.
		 */
		pll_data1.Data = 0xC1BEFF;
		if (hmc_spi_write_read(PLL_C_HW, 0x08, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 11: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 11: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	12. Write to REG 9 3FFEFD.
		 * 		CP Register-Program as needed. 3FFEFDh = 2.54mA CP current with 635uA Up CP Offset current.
		 */
		pll_data1.Data = 0x3FFEFD;
		if (hmc_spi_write_read(PLL_C_HW, 0x09, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 12: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 12: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	13. Write to REG A 2046.
		 * 		VCO Tuning Configuration Register-Program this value.
		 */
		pll_data1.Data = 0x2046;
		if (hmc_spi_write_read(PLL_C_HW, 0x0A, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 13: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 13: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	14. Write to REG B 4F8061.
		 * 		PFD/CP Control Register.  Default value = F8061h.
		 * 		4F8061h sets LD/SDO output level to 3.3V from 1.8V default (bit[22]=1 sets 3.3V output level).
		 */
		pll_data1.Data = 0x4F8061;
		if (hmc_spi_write_read(PLL_C_HW, 0x0B, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 14: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 14: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	15. Write to REG C 0.
		 * 		Exact Frequency register.  Default value =0h.  No need to program if not using Exact Frequency Mode.
		 */
		pll_data1.Data = 0x00;
		if (hmc_spi_write_read(PLL_C_HW, 0x0C, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 15: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 15: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	16. Write to REG F 81.
		 * 		Default vaue =1. 81h configures LD/SDO pin to output LD status always,
		 * 			except during SPI reads when the pin is automatically mux'ed to output the serial data.
		 */
#if 0
		pll_data1.Data = 0x81;
		if (hmc_spi_write_read(PLL_C_HW, 0x0F, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 16: SUCCESS!\n");
		else
			printf2("		CMD 16: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command
#endif

		/*
		 * 	17. Write to REG 4 0.
		 * 		Fractional VCO Divider Register-Program as needed to set frequency. When this register is written, a VCO auto-cal is initiated.
		 */
		pll_data1.Data = 0x800000;
		if (hmc_spi_write_read(PLL_C_HW, 0x04, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 17: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 17: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

	}
	else if ( strcmp(parm1, "TST66b_c") == 0) {
		printf2("PLLC set to 90MHz...TEST.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		PLLC PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Lets Get parameters first so we can See values.
		Template_Parms.Desired_Freq = SIG_90MHZ;
		hmc_calc_parameters(&Template_Parms);
		// Now Print Parms.
		sprintf(tempstr, "	Output_Divider:%d\n", Template_Parms.Output_Divider);
		printf2(tempstr);
		sprintf(tempstr, "	N_Divider:%d / %d\n", Template_Parms.N_Divider_int, Template_Parms.N_Divider_frac);
		printf2(tempstr);
		sprintf(tempstr, "	R_Divider:%d\n", Template_Parms.R_Divider);
		printf2(tempstr);

		// BIT BANG SETTINGS...
		// 1. Write to REG 0 20.
		// 			Reg00 = 00100000  -  RESET command.
		pll_data1.Data = 0x20;
		Test_Data1.chip_idRD.Soft_Rst = 1;		// RESET command.
		sprintf(tempstr, "1. RAW: %08x	STRCT: %08X\n", pll_data1.Data, Test_Data1.Data);
		printf2(tempstr);
		if (hmc_spi_write_read(PLL_C_HW, 0x00, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 1: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 1: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 *  2. Write to REG 1 2.
		 *		Reg01 = 00000010 - Default = 2.
		 * 			This value assigns PLL Chip Enable control to the SPI Reg 1 [1], 1 enabled, 0 disabled.
		 * 			To assign PLL CE control to CE pin, write Reg 1[0]=1.
		 */
		pll_data1.Data = 0x02;
		if (hmc_spi_write_read(PLL_C_HW, 0x01, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 2: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 2: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	3. Write to REG 2 1.
		 * 		Reg02 = 00000001 - REFDIV Register =  0x01 Ref Divider Register-Default value = 1h (Rdiv=1). Program as needed.
		 */
		pll_data1.Data = 0x01;
		if (hmc_spi_write_read(PLL_C_HW, 0x02, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 3: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 3: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	4. Write to REG 3 B4.
		 * 		Reg03 = 10110100 - Frequency Register, Integer Part Integer VCO Divider Register-Progarm as needed to set frequency.
		 */
		pll_data1.Data = 0xB5;
		if (hmc_spi_write_read(PLL_C_HW, 0x03, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 4: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 4: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

#if 0
		/*
		 * 	17. Write to REG 4 0.
		 * 		Fractional VCO Divider Register-Program as needed to set frequency. When this register is written, a VCO auto-cal is initiated.
		 */
		pll_data1.Data = 0x800000;
		if (hmc_spi_write_read(PLL_C_HW, 0x04, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 17: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 17: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command
#endif

		// 5. Write to REG 5 1010   // Reg02 = 000010000 = fo (VCO output Div-by-44);
		pll_data1.Data = 0x1610;
		Test_Data1.spi_vco.VCO_REGADDR = 0x02;		// Reg02
		Test_Data1.spi_vco.VCO_ID = 0x00;			// ID always zero
		Test_Data1.spi_vco.VCO_DATA = 44;			// Set Divisor as 32.
		sprintf(tempstr, "5. RAW: %08x	STRCT: %08X\n", pll_data1.Data, Test_Data1.Data);
		printf2(tempstr);
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 5: SUCCESS!\n");
		else
			printf2("		CMD 5: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * Power Up VCOs.
		 */
		if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
			printf2("		VCO POWERUP: SUCCESS!\n");
		else
			printf2("		VCO POWERUP: FAILED!\n");

		// 6. Write to REG 5 F98    // Reg03 = 000011111 = Hi Perf, RF_P & RF_N enabled, 5dB RL,
		pll_data1.Data = 0x0F98;
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 6: SUCCESS!\n");
		else
			printf2("		CMD 6: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 7. Write to REG 5 4B38   // Reg07 = 010010110 = o/p -6dB.  For maximum o/p power program 4DB8h.
		pll_data1.Data = 0x4B38;
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 7: SUCCESS!\n");
		else
			printf2("		CMD 7: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		// 8. Write to REG 5 0.
		pll_data1.Data = 0x0;
		if (hmc_spi_write_read(PLL_C_HW, 0x05, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 8: SUCCESS!\n");
		else
			printf2("		CMD 8: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	9. Write to REG 6 F4A.
		 * 		Reg06 = F4A Delta-Sigma Modulator Configuration Register. Program this value for Frac Mode.
		 */
		pll_data1.Data = 0x0F4A;
		if (hmc_spi_write_read(PLL_C_HW, 0x06, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 9: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 9: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	10. Write to REG 7 14D.
		 * 		14Dh is the default value for LD programming (correct for 50MHz comparison).
		 * 		For different configurations, especially higher PFD rates, this may need to change.
		 */
		pll_data1.Data = 0x014D;
		if (hmc_spi_write_read(PLL_C_HW, 0x07, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 10: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 10: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	11. Write to REG 8 C1BEFF.
		 * 		Default value = C1BEFFh.  No need to program.
		 */
		pll_data1.Data = 0xC1BEFF;
		if (hmc_spi_write_read(PLL_C_HW, 0x08, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 11: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 11: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	12. Write to REG 9 3FFEFD.
		 * 		CP Register-Program as needed. 3FFEFDh = 2.54mA CP current with 635uA Up CP Offset current.
		 */
		pll_data1.Data = 0x3FFEFD;
		if (hmc_spi_write_read(PLL_C_HW, 0x09, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 12: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 12: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	13. Write to REG A 2046.
		 * 		VCO Tuning Configuration Register-Program this value.
		 */
		pll_data1.Data = 0x2046;
		if (hmc_spi_write_read(PLL_C_HW, 0x0A, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 13: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 13: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	14. Write to REG B 4F8061.
		 * 		PFD/CP Control Register.  Default value = F8061h.
		 * 		4F8061h sets LD/SDO output level to 3.3V from 1.8V default (bit[22]=1 sets 3.3V output level).
		 */
		pll_data1.Data = 0x4F8061;
		if (hmc_spi_write_read(PLL_C_HW, 0x0B, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 14: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 14: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	15. Write to REG C 0.
		 * 		Exact Frequency register.  Default value =0h.  No need to program if not using Exact Frequency Mode.
		 */
		pll_data1.Data = 0x00;
		if (hmc_spi_write_read(PLL_C_HW, 0x0C, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 15: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 15: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command

		/*
		 * 	16. Write to REG F 81.
		 * 		Default vaue =1. 81h configures LD/SDO pin to output LD status always,
		 * 			except during SPI reads when the pin is automatically mux'ed to output the serial data.
		 */
#if 0
		pll_data1.Data = 0x81;
		if (hmc_spi_write_read(PLL_C_HW, 0x0F, pll_data1, &pll_rxdata2) == HAL_OK)
			printf2("		CMD 16: SUCCESS!\n");
		else
			printf2("		CMD 16: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command
#endif

		/*
		 * 	17. Write to REG 4 0.
		 * 		Fractional VCO Divider Register-Program as needed to set frequency. When this register is written, a VCO auto-cal is initiated.
		 */
		pll_data1.Data = 0x800000;
		if (hmc_spi_write_read(PLL_C_HW, 0x04, pll_data1, &pll_rxdata2) == HAL_OK)
		{
			printf2("		CMD 17: SUCCESS!\n");
			sprintf(tempstr, "		    DATA:%06X\n", (pll_rxdata2.DATA >> 8));
			printf2(tempstr);
		}
		else
			printf2("		CMD 17: FAILED!\n");
		accurate_delay(WAIT_DELAY);		// Wait before next Command






#if 0
#endif
	}
	else if ( strcmp(parm1, "25_d") == 0)
	{
		printf2("PLLD set to 25MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_D_HW) == HAL_OK)
			printf2("		PLLD PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCOCC PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Lets Get parameters first so we can See values.
		Template_Parms.Desired_Freq = SIG_25MHZ;
		hmc_calc_parameters(&Template_Parms);
		// Now Print Parms.
		sprintf(tempstr, "	Output_Divider:%d\n", Template_Parms.Output_Divider);
		printf2(tempstr);
		sprintf(tempstr, "	N_Divider:%d / %d\n", Template_Parms.N_Divider_int, Template_Parms.N_Divider_frac);
		printf2(tempstr);
		sprintf(tempstr, "	R_Divider:%d\n", Template_Parms.R_Divider);
		printf2(tempstr);
		// Setup Synth for 25MHz.
		if (hmc_SetupFreq(PLL_D_HW, SIG_25MHZ) == HAL_OK)
			printf2("		Task Synth 25Mhz: SUCCESS!\n");
		else
			printf2("		Task Synth 25Mhz: FAILED!\n");
	}
	else if ( strcmp(parm1, "50_d") == 0)
	{
		printf2("PLLD set to 50MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_D_HW) == HAL_OK)
			printf2("		PLL D PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCO C PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Lets Get parameters first so we can See values.
		Template_Parms.Desired_Freq = SIG_50MHZ;
		hmc_calc_parameters(&Template_Parms);
		// Now Print Parms.
		sprintf(tempstr, "	Output_Divider:%d\n", Template_Parms.Output_Divider);
		printf2(tempstr);
		sprintf(tempstr, "	N_Divider:%d / %d\n", Template_Parms.N_Divider_int, Template_Parms.N_Divider_frac);
		printf2(tempstr);
		sprintf(tempstr, "	R_Divider:%d\n", Template_Parms.R_Divider);
		printf2(tempstr);
		// Setup Synth for 50MHz.
		if (hmc_SetupFreq(PLL_D_HW, SIG_50MHZ) == HAL_OK)
			printf2("		Task Synth 50Mhz: SUCCESS!\n");
		else
			printf2("		Task Synth 50Mhz: Failed!\n");
	}
	else if ( strcmp(parm1, "OFF_c") == 0) {
		printf2("PLLC disabled.\n");

		/*
		 * Powerup PLL C just in case they are jammed.
		 */
		hmc_pll_powerUp(PLL_C_HW);
		hmc_Disable_VCO(PLL_C_HW);
		hmc_vco_powerUp(PLL_C_HW);

		// Power Down Clock Circuit.
		PLMpls_gpio_Off(PLL_CLK_EN);	// Disable HF Clock by Setting Pin Low.

		/*
		 * Disable VCO Output .
		 */
		hmc_Disable_VCO(PLL_C_HW);

		/*
		 * Power Down VCOs.
		 */
		hmc_vco_powerDn(PLL_C_HW);

		/*
		 * Power Down PLLs.
		 */
		hmc_pll_powerDn(PLL_C_HW);
	}
	else if ( strcmp(parm1, "OFF") == 0) {
		printf2("Disable ALL Lasers HF/LF.\n");
		// Power Off Lasers.
		hmc_PwrOff_Lsrs();
		printf2("	COMPLETE.\n");

	}
	else if ( strcmp(parm1, "Calib_1") == 0) {
		printf2("HF Channel 1 Calibration/No Laser....25MHz.\n");
		printf2("	PLLC set to 25MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("	PLLC PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCOCC PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Setup Synth for 25MHz.
		if (hmc_SetupFreq(PLL_C_HW, SIG_25MHZ) == HAL_OK)
			printf2("	Task Synth 25Mhz: SUCCESS!\n");
		else
			printf2("	Task Synth 25Mhz: FAILED!\n");
		/*
		 * Powerup Channel 1 Common.
		 * 		P13/Pin 44: MTU0: LaserDiode0
		 */
		MPC.P13PFS.BYTE = 0x00U;					// No Periph Control.
		PORT1.PMR.BYTE &= ~0x08U;					// Setup as I/O.
		PORT1.PDR.BYTE |= 0x08U;					// Setup as Output.
		PORT1.PODR.BYTE &= ~0x08U;					// Set as LOW.
		/*
		 * Powerup HF Drivers Power Supply
		 */
		accurate_delay(10);
		//PLMpls_gpio_On(HF_Laser_Enable);
		PLMpls_gpio_Off( HF_Laser_Enable );
		/*
		 * Enable HF Laser 1 Driver.
		 */
		accurate_delay(10);
		PLMpls_HFlaser_enable( HF_LSR1_CNTL );
		printf2("	Calibration Setup Complete.\n");
	}
	else if ( strcmp(parm1, "Calib_2") == 0) {
		printf2("HF Channel 2 Calibration/No Laser....25MHz.\n");
		printf2("	PLLD set to 25MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_D_HW) == HAL_OK)
			printf2("	PLLD PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCOCC PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Setup Synth for 25MHz.
		if (hmc_SetupFreq(PLL_D_HW, SIG_25MHZ) == HAL_OK)
			printf2("	Task Synth 25Mhz: SUCCESS!\n");
		else
			printf2("	Task Synth 25Mhz: FAILED!\n");
		/*
		 * Powerup Channel 2 Common.
		 * 		P20/Pin 37: MTU1: LaserDiode1
		 */
		MPC.P20PFS.BYTE = 0x00U;					// No Periph Control.
		PORT2.PMR.BYTE &= ~0x01U;					// Setup as I/O.
		PORT2.PDR.BYTE |= 0x01U;					// Setup as Output.
		PORT2.PODR.BYTE &= ~0x01U;					// Set as LOW.
		/*
		 * Powerup HF Drivers Power Supply
		 */
		accurate_delay(10);
		//PLMpls_gpio_On(HF_Laser_Enable);
		PLMpls_gpio_Off( HF_Laser_Enable );
		/*
		 * Enable HF Laser 1 Driver.
		 */
		accurate_delay(10);
		PLMpls_HFlaser_enable( HF_LSR2_CNTL );
		printf2("	Calibration Setup Complete.\n");
	}
	else if ( strcmp(parm1, "Calib_3") == 0) {
		printf2("HF Channel 3 Calibration/No Laser....25MHz.\n");
		printf2("	PLLC set to 25MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("	PLLC PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCOCC PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Setup Synth for 25MHz.
		if (hmc_SetupFreq(PLL_C_HW, SIG_25MHZ) == HAL_OK)
			printf2("	Task Synth 25Mhz: SUCCESS!\n");
		else
			printf2("	Task Synth 25Mhz: FAILED!\n");
		/*
		 * Powerup Channel 3 Common.
		 * 		P17/Pin 38: MTU4: LaserDiode2b
		 */
		MPC.P17PFS.BYTE = 0x00U;					// No Periph Control.
		PORT1.PMR.BYTE &= ~0x80U;					// Setup as I/O.
		PORT1.PDR.BYTE |= 0x80U;					// Setup as Output.
		PORT1.PODR.BYTE &= ~0x80U;					// Set as LOW.
		/*
		 * Powerup HF Drivers Power Supply
		 */
		accurate_delay(10);
		//PLMpls_gpio_On(HF_Laser_Enable);
		PLMpls_gpio_Off( HF_Laser_Enable );
		/*
		 * Enable HF Laser 3 Driver.
		 */
		accurate_delay(10);
		PLMpls_HFlaser_enable( HF_LSR3_CNTL );
		printf2("	Calibration Setup Complete.\n");
	}
	else if ( strcmp(parm1, "Calib_4") == 0) {
		printf2("HF Channel 4 Calibration....25MHz.\n");
		printf2("	PLLD set to 25MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_D_HW) == HAL_OK)
			printf2("	PLLD PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCOCC PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Setup Synth for 25MHz.
		if (hmc_SetupFreq(PLL_D_HW, SIG_25MHZ) == HAL_OK)
			printf2("	Task Synth 25Mhz: SUCCESS!\n");
		else
			printf2("	Task Synth 25Mhz: FAILED!\n");
		/*
		 * Powerup Channel 1 Common.
		 * 		PA1/Pin 96: MTU7: LaserDiode3b
		 */
		MPC.PA1PFS.BYTE = 0x00U;					// No Periph Control.
		PORTA.PMR.BYTE &= ~0x02U;					// Setup as I/O.
		PORTA.PDR.BYTE |= 0x02U;					// Setup as Output.
		PORTA.PODR.BYTE &= ~0x02U;					// Set as LOW.
		/*
		 * Powerup HF Drivers Power Supply
		 */
		accurate_delay(10);
		//PLMpls_gpio_On(HF_Laser_Enable);
		PLMpls_gpio_Off( HF_Laser_Enable );
		/*
		 * Enable HF Laser 4 Driver.
		 */
		accurate_delay(10);
		PLMpls_HFlaser_enable( HF_LSR4_CNTL );
		printf2("	Calibration Setup Complete.\n");
	}
	else if ( strcmp(parm1, "CalibN_1") == 0) {
		printf2("HF Channel 1 Calibration/No Laser....25MHz.\n");
		printf2("	PLLC set to 25MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("	PLLC PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCOCC PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Setup Synth for 25MHz.
		if (hmc_SetupFreq(PLL_C_HW, SIG_25MHZ) == HAL_OK)
			printf2("	Task Synth 25Mhz: SUCCESS!\n");
		else
			printf2("	Task Synth 25Mhz: FAILED!\n");
		/*
		 * Powerup Channel 1 Common.
		 * 		P13/Pin 44: MTU0: LaserDiode0
		 */
		//MPC.P13PFS.BYTE = 0x00U;					// No Periph Control.
		//PORT1.PMR.BYTE &= ~0x08U;					// Setup as I/O.
		//PORT1.PDR.BYTE |= 0x08U;					// Setup as Output.
		//PORT1.PODR.BYTE &= ~0x08U;					// Set as LOW.
		/*
		 * Powerup HF Drivers Power Supply
		 */
		accurate_delay(10);
		//PLMpls_gpio_On(HF_Laser_Enable);
		PLMpls_gpio_Off( HF_Laser_Enable );
		/*
		 * Enable HF Laser 1 Driver.
		 */
		accurate_delay(10);
		PLMpls_HFlaser_enable( HF_LSR1_CNTL );
		printf2("	Calibration Setup Complete.\n");
	}
	else if ( strcmp(parm1, "CalibN_2") == 0) {
		printf2("HF Channel 2 Calibration/No Laser....25MHz.\n");
		printf2("	PLLD set to 25MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_D_HW) == HAL_OK)
			printf2("	PLLD PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCOCC PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Setup Synth for 25MHz.
		if (hmc_SetupFreq(PLL_D_HW, SIG_25MHZ) == HAL_OK)
			printf2("	Task Synth 25Mhz: SUCCESS!\n");
		else
			printf2("	Task Synth 25Mhz: FAILED!\n");
		/*
		 * Powerup Channel 2 Common.
		 * 		P20/Pin 37: MTU1: LaserDiode1
		 */
		//MPC.P20PFS.BYTE = 0x00U;					// No Periph Control.
		//PORT2.PMR.BYTE &= ~0x01U;					// Setup as I/O.
		//PORT2.PDR.BYTE |= 0x01U;					// Setup as Output.
		//PORT2.PODR.BYTE &= ~0x01U;					// Set as LOW.
		/*
		 * Powerup HF Drivers Power Supply
		 */
		accurate_delay(10);
		//PLMpls_gpio_On(HF_Laser_Enable);
		PLMpls_gpio_Off( HF_Laser_Enable );
		/*
		 * Enable HF Laser 1 Driver.
		 */
		accurate_delay(10);
		PLMpls_HFlaser_enable( HF_LSR2_CNTL );
		printf2("	Calibration Setup Complete.\n");
	}
	else if ( strcmp(parm1, "CalibN_3") == 0) {
		printf2("HF Channel 3 Calibration/No Laser....25MHz.\n");
		printf2("	PLLC set to 25MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_C_HW) == HAL_OK)
			printf2("	PLLC PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCOCC PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Setup Synth for 25MHz.
		if (hmc_SetupFreq(PLL_C_HW, SIG_25MHZ) == HAL_OK)
			printf2("	Task Synth 25Mhz: SUCCESS!\n");
		else
			printf2("	Task Synth 25Mhz: FAILED!\n");
		/*
		 * Powerup Channel 3 Common.
		 * 		P17/Pin 38: MTU4: LaserDiode2b
		 */
		//MPC.P17PFS.BYTE = 0x00U;					// No Periph Control.
		//PORT1.PMR.BYTE &= ~0x80U;					// Setup as I/O.
		//PORT1.PDR.BYTE |= 0x80U;					// Setup as Output.
		//PORT1.PODR.BYTE &= ~0x80U;					// Set as LOW.
		/*
		 * Powerup HF Drivers Power Supply
		 */
		accurate_delay(10);
		//PLMpls_gpio_On(HF_Laser_Enable);
		PLMpls_gpio_Off( HF_Laser_Enable );
		/*
		 * Enable HF Laser 3 Driver.
		 */
		accurate_delay(10);
		PLMpls_HFlaser_enable( HF_LSR3_CNTL );
		printf2("	Calibration Setup Complete.\n");
	}
	else if ( strcmp(parm1, "CalibN_4") == 0) {
		printf2("HF Channel 4 Calibration/No Laser....25MHz.\n");
		printf2("	PLLD set to 25MHz.\n");
		/*
		 * Power Up PLLs.
		 */
		if (hmc_pll_powerUp(PLL_D_HW) == HAL_OK)
			printf2("	PLLD PowerUP: SUCCEED!\n");

		/*
		 * Power Up VCOs.
		 */
		//if (hmc_vco_powerUp(PLL_C_HW) == HAL_OK)
		//	printf2("		VCOCC PowerUP: SUCCEED!\n");

		// Power Up Clock Circuit.
		PLMpls_gpio_On(PLL_CLK_EN);		// Enable HF Clock by Setting Pin High.

		// Setup Synth for 25MHz.
		if (hmc_SetupFreq(PLL_D_HW, SIG_25MHZ) == HAL_OK)
			printf2("	Task Synth 25Mhz: SUCCESS!\n");
		else
			printf2("	Task Synth 25Mhz: FAILED!\n");
		/*
		 * Powerup Channel 1 Common.
		 * 		PA1/Pin 96: MTU7: LaserDiode3b
		 */
		//MPC.PA1PFS.BYTE = 0x00U;					// No Periph Control.
		//PORTA.PMR.BYTE &= ~0x02U;					// Setup as I/O.
		//PORTA.PDR.BYTE |= 0x02U;					// Setup as Output.
		//PORTA.PODR.BYTE &= ~0x02U;					// Set as LOW.
		/*
		 * Powerup HF Drivers Power Supply
		 */
		accurate_delay(10);
		//PLMpls_gpio_On(HF_Laser_Enable);
		PLMpls_gpio_Off( HF_Laser_Enable );
		/*
		 * Enable HF Laser 4 Driver.
		 */
		accurate_delay(10);
		PLMpls_HFlaser_enable( HF_LSR4_CNTL );
		printf2("	Calibration Setup Complete.\n");
	}
	else if ( strcmp(parm1, "LCK_c") == 0) {
		if (hmc_TestPll_Lock(PLL_C_HW))
			printf2("PLLC Locked on Freq.\n");
		else
			printf2("PLLC NOT Locked.\n");
	}
	else
	{
	      printf2("ILLEGAL hmc Parameter!!\n");
	}
	printf2("\n\n");
}

void LaserOnmonitor(char *parm1) {
	int errCode;
	errCode = init_laser((unsigned int) atoi(parm1), 1);
	if (errCode == 0)
		printf2("Succesful!\n");
	else if (errCode == -1)
		printf2(" Parameter Error!\n");
	else if (errCode == -2)
		printf2(" Busy Timeout!\n");
	else if (errCode == -3)
		printf2(" Parameter Failure!\n");
	printf2("\n\n");
}

const char *const ModeString[] = { "Factory",// Code	0 **** Factory Boot Mode(DEFAULT START MODE)
		"Factory_Screen",	// Code	1			// Factory Boot: Factory Screen
		"Boot_Screen",			// Code	2			// **** Boot Screen
		"Locked	",		    	// Code	3			// **** Locked
		"Locked_1",	// Code	4			// Locked: First Key Matched for UnLock.
		"Locked_2",	// Code	5			// Locked: Second Key Matched for Unlock.
		"Main",					// Code	6		    // **** Main Menu
		"Timed_Test",// Code	7			// Main Menu: Timed Test for Timed Laser Mode
		"Soft_PD",				// Code	8			// **** Soft Power Down
		"Test1",				// Code	9			// **** Test1/ Soft_PD
		"Laser_On",				// Code	10			// **** Laser On Momentary
		"Wait_Release",	// Code	11			// Laser On Momentary: Wait For Key Release
		"Timed_Laser",			// Code	12			// **** Timed Laser Mode
		"Pause_Laser",// Code	13			// Timed Laser Mode: Wait for Key Release
		"Pause_Laser2",	// Code	14			// Timed Laser Mode: Wait for Laser to Restart
		"Pause_Laser3",	// Code	15			// Timed Laser Mode: Wait for Key Release.
		"Five_Min_Mode",// Code	16			// **** Five Minute Laser On Mode
		"Pause1",// Code	17			// Five Minute Laser On Mode: Pause Laser and Wait Key Release
		"Pause",// Code	18			// Five Minute Laser On Mode: Wait for Power Key
		"Pause2",// Code	19			// Five Minute Laser On Mode: Restart Laser and Wait Key Release
		"Program",				// Code	20			// **** Programming Mode
		"Incr_Prog",// Code	21			// Programming Mode: Increment Program Count and Recalculate
		"Decr_Prog",// Code	22			// Programming Mode: Decreement Program Count and Recalculate
		"Build_Prog",// Code	23			// Programming Mode: Build Program Buffer.
		"Activate_Prog",// Code	24			// Programming Mode: Activate New Program ID.
		"Time_Value",			// Code	25			// **** Time Program Mode
		"Remove_1Key",// Code	26			// Time Program Mode: Remove 1 Key from Buffer
		"Incr_Second",// Code	27			// Time Program Mode: Increment Second Buffer
		"Decr_Second",// Code	28			// Time Program Mode: Decrement Second Buffer
		"Incr_Minute",// Code	29			// Time Program Mode: Increment Minute Buffer
		"Buffer_Build",	// Code	30			// Time Program Mode: Build Time Buffer
		"Decr_Minute",// Code	31			// Time Program Mode: Decrement Minute Buffer
		"Save_Settings",// Code	32			// Time Program Mode: Save Time Settings
		"Laser_Value",		// Code	33			// **** Laser Root Program Menu
		"Laser1_Value",			// Code	34			// **** Laser 1 Program Menu
		"LSR1_SM3",	// Code	35			// Laser 1 Program Menu: Set SM=3 and Goto Laser3_Value
		"LSR1_SM2",	// Code	36			// Laser 1 Program Menu: Set SM=2 and Goto Laser2_Value
		"LSR1_BffrBuild",// Code	37			// Laser 1 Program Menu: Buffer Build
		"LSR1_RemvKey",	// Code	38			// Laser 1 Program Menu: Remove One Key From Buffer
		"LSR1_BlnkLaser",// Code	39			// Laser 1 Program Menu: Blank Laser Buffer
		"LSR1_SaveLsr",	// Code	40			// Laser 1 Program Menu: Save Laser Setting
		"Laser2_Value",			// Code	41			// **** Laser 2 Program Menu
		"LSR2_SM4",	// Code	42			// Laser 2 Program Menu: Set SM=4 and Goto Laser4_Value
		"LSR2_SM1",	// Code	43			// Laser 2 Program Menu: Set SM=1 and Goto Laser1_Value
		"LSR2_BffrBuild",// Code	44			// Laser 2 Program Menu: Buffer Build
		"LSR2_RemvKey",	// Code	45			// Laser 2 Program Menu: Remove One Key From Buffer
		"LSR2_BlnkLaser",// Code	46			// Laser 2 Program Menu: Blank Laser Buffer
		"LSR2_SaveLsr",	// Code	47			// Laser 2 Program Menu: Save Laser Setting
		"Laser3_Value",			// Code	48			// **** Laser 3 Program Menu
		"LSR3_SM1",	// Code	49			// Laser 3 Program Menu: Set SM=1 and Goto Laser1_Value
		"LSR3_SM4",	// Code	50			// Laser 3 Program Menu: Set SM=4 and Goto Laser4_Value
		"LSR3_BffrBuild",// Code	51			// Laser 3 Program Menu: Buffer Build
		"LSR3_RemvKey",	// Code	52			// Laser 3 Program Menu: Remove One Key From Buffer
		"LSR3_BlnkLaser",// Code	53			// Laser 3 Program Menu: Blank Laser Buffer
		"LSR3_SaveLsr",	// Code	54			// Laser 3 Program Menu: Save Laser Setting
		"Laser4_Value",			// Code	55			// **** Laser 4 Program Menu
		"LSR4_SM2",	// Code	56			// Laser 4 Program Menu: Set SM=2 and Goto Laser2_Value
		"LSR4_SM3",	// Code	57			// Laser 4 Program Menu: Set SM=3 and Goto Laser3_Value
		"LSR4_BffrBuild",// Code	58			// Laser 4 Program Menu: Buffer Build
		"LSR4_RemvKey",	// Code	59			// Laser 4 Program Menu: Remove One Key From Buffer
		"LSR4_BlnkLaser",// Code	60			// Laser 4 Program Menu: Blank Laser Buffer
		"LSR4_SaveLsr",	// Code	61			// Laser 4 Program Menu: Save Laser Setting
		"New_Prog",				// Code	62			// **** New Program Menu
		"New_Prog_SM1",	// Code	63			// New Program Menu: Set SM=1 and Goto Laser_Value
		"Delete_Prog",			// Code	64			// **** Delete Program Menu
		"Blank_Settings",// Code	65			// Delete Program Menu: Blank Settings and goto Main
		"LOW_BAT",		    	// Code	66			// Battery Low...Die Now!!!!
		"Low_PD",// Code	67			// Battery Low Power Down...No Save Vars...SLEEP!!!!
		"FPGA_BAT",	// Code	68			// FPGA Battery Low...Shutdown Now!!!!
		"Special4",	// Code	69			// Special Sequence From Main to start limited Monitor Mode....Step 1
		"Special4a",// Code	70			// Special Sequence From Main to start limited Monitor Mode....Step 2
		"Special9",	// Code	71			// Special Sequence From Main to start limited Monitor Mode....Step 3
		"Special3",	// Code	72			// Special Sequence From Main to start limited Monitor Mode....Step 4
		"ProgramMode",// Code	73			// Special Sequence From PowerOff to Load Serial Flash....FINAL STEP
		"DB_Screen",// Code	74			// Database Screen Showing DB Versions.
		"SndScreen",		// Code	75			// Sound Configuration Screen.
		"KeyScreen",			// Code	76			// Key Entry Screen.
		"SerialNumScreen",	// Code	77			// Serial Number Entry Screen.
		"Timed_Laser_Armed",	// Code	78			// Timed Laser Armed Screen.
		"Timed_Laser_Armed2",// Code	79			// Timed Laser Armed Screen Part2.
		"Laser_On_Armed",		// Code	80			// Laser On Armed Screen.
		"Laser_On_Armed2",	// Code	81			// Laser On Armed Screen Part2.
		"Five_Min_Armed",		// Code	82			// Five Minute Armed Screen.
		"Five_Min_Armed2",// Code	83			// Five Minute Armed Screen Part2.
		"Soft_PD_CONTINUE",	// Code	84			// Soft PD Continue after Wait.
		"Locked_CONTINUE",	// Code	85			// Need this for Locked wakeup
		"SpecialSelect",// Code	86			// Special Sequence From Main to start limited Monitor Mode....Step 5
		"MonitorMode",// Code	87			// Special Sequence From Main to start limited Monitor Mode....FINAL STEP
		"ShowTimeMode",			// Code	88			// Show Time and Date mode.
		"PBFEntryScreen",		// Code	89			// PBF Entry mode.
		"PBFErrorScreen",		// Code	90			// PBF Error mode.
		"DateEntryScreen",		// Code	91			// Date Entry Screen.
		"TimeEntryScreen" };		// Code	92			// Time Entry Screen

void ModeMonitor(char *parm1) {
	int x;
	char tempBuff[80];
	for (x = 0; x < END_SETTING; x++) {
		//Search all Mode Sttings for Match
		if ( strcmp(parm1, ModeString[x]) == 0) {
			// Found one....Set Mode to Value found...
			mode = x;
			Over_Ride();
			sprintf(tempBuff, "New Mode: %s\n", ModeString[x]);
			printf2(tempBuff);
			break;
		} // EndIf ( strcmp(parm1, ModeString[x]) == 0)
	} //EndFor (x=0;x<END_SETTING;x++)
	if (x >= END_SETTING)
		printf2("New Mode ERROR! NO MODE FOUND!!\n");
	printf2("\n\n");
}

