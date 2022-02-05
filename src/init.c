/*
 * init.c
 *
 *  Created on: Feb 1, 2015
 *      Author: rpruitt76
 */
//*****************************************************************************
//*
//* Module Includes
//*
//*****************************************************************************
//#include <iom128v.h>
//#include <macros.h>
#include "r_flash_rx_if.h"
#include <string.h>
#include <stdlib.h>
#include  <stdio.h>
#include "LaserP.h"
#include "r_cg_icu.h"
#include "r_cg_tmr.h"
#include "r_cg_mtu3.h"
#include "gpio.h"

//*****************************************************************************
//*
//* routine: keybrd_init
//* Date: 	 April 20, 2006
//* Updated: February 1, 2015
//* Author:  Ralph Pruitt
//* This routine initializes key hardware to track Keyboard Interrupts.
//*
//*****************************************************************************
void keybrd_init(void)
{
	// ROW_INT is now P47 and is active on a low going int.
	//R_ICU_IRQ15_Start();		  // Enable External Int 15 which processes all Keyboard Inputs.
}

//*****************************************************************************
//*
//* routine: port_init
//* Date: 	 December 1, 2003
//* Updated: February 1, 2015
//* Author:  Ralph Pruitt
//* This routine is used to perform the initial port initialization for normal
//* operation.
//*
//*****************************************************************************
void port_init(void)
{
	// Turn Off LCD Backlight...P65
	PORT6.PODR.BYTE &= ~0x20;

	// Set Cols as Output Low....Port 7
	PORT7.PODR.BYTE = 0x00;

	// Set all LCD CONtrol Pins Low
	// E1=0		...P12
	// E2=0		...P15
	// R/W=0	...P16
	PORT1.PODR.BYTE &= ~0x64;
	// RS=0		...P21
	PORT2.PODR.BYTE &= ~0x02;
	// LCDPWR=0	...P64
	PORT6.PODR.BYTE &= ~0x10;
}

//*****************************************************************************
//*
//* routine: watchdog_init
//* Date: 	 December 1, 2003
//* Updated: February 1, 2015
//* Author:  Ralph Pruitt
//* This routine is used to enable the Watch Dog Function.
//*
//*****************************************************************************
//Watchdog initialisation
// prescale: 128K cycles
void watchdog_init(void)
{
 WDR(); //this prevents a timout on enabling
// WATCHDOG ENABLED - dont forget to issue WDRs....69.907 milliseconds
}

//*****************************************************************************
//*
//* routine: timer0_init
//* Date: 	 December 1, 2003
//* Updated: February 2, 2015
//* Author:  Ralph Pruitt
//* This routine is used to initialize timer0 as a 50Hz timer. The prescale is set
//* at 1024 and the actual frequency is 50.080Hz.
//*
//*****************************************************************************
//TIMER0 initialisation - prescale:1024
// WGM: Normal
// desired value: 50Hz
// actual value: 50.080Hz (0.2%)
void timer0_init(void)
{
	// Initialize Timer that will be used for this timer.
	R_TMR0_Start();
}

//*****************************************************************************
//*
//* routine: task()
//* Date: 	 December 3, 2003
//* Author:  Ralph Pruitt
//* This routine is used to place a new task into the tasking queue. The tasking
//* queue executes each request in a FIFO order during the timer0 interrupt.
//* Input:
//*		  Task_item:	Char: indicating tasked request
//* Output:
//*		  Status:		Char: Indicates results of operation.
//*		  			0:		  Successful tasking.
//*					1:		  Failed to task...Bad ID
//* Variables:
//*	      char		buf[TASKBUFF];	 // Defines Tasking Buffer
//*		  char		buf_in;			 // Buffer Input Pointer
//*		  char		buf_out;		 // Buffer Output Pointer
//*		  char		buf_cnt;		 //	Number of outstanding tasks
//*
//*****************************************************************************
char task(char Task_item)
{
 // Test for Buffer Full
 if (buf_cnt >= TASKBUFF)
 	return(2);	//

 // Test Task for legal entry.
 if ((Task_item < MAXENTRY) && (Task_item>0)) {
   buf_cnt++;
   buf[buf_in++] = Task_item;
   if (buf_in >= MAXENTRY)
     buf_in = 0;
   return(0);
 }
 else
 	 return(1);
}

//*****************************************************************************
//*
//* routine: proc_buffer()
//* Date: 	 January 1, 2004
//* Author:  Ralph Pruitt
//* This routine is used to process items from the tasking buffer. All items will
//* be processed and then control will be returned.
//*
//*****************************************************************************
void proc_buffer(void)
{

  char item;
#ifdef DEBUGGR
   debug1(3);
#endif
  // Process Task Buffer.
  if (buf_cnt >0){
    while (buf_cnt > 0) {
      buf_cnt--;
      item = buf[buf_out++];
	  switch (item) {
	    case Bcklght_ON:
	      led_coff = 0;
		  led_cnt = 0;
		  PORT6.PODR.BYTE &= ~0x20;				// Turn on LCD Backlight.
	      break;
	  	case Bcklght_OFF:
	      led_coff = 0;
		  led_cnt = 0;
		  PORT6.PODR.BYTE &= ~0x20;				// Turn off LCD Backlight.
	      break;
	    case Bcklght_Fade:
	      led_coff = 1;
// 		  TCCR1A = 0x00;						// Start Fade Timer.
// 		  TCCR1B = 0x11;
	      break;
	  }
      if (buf_out >= MAXENTRY)
        buf_out = 0;
	} // End While
 } // EndIf
}

//*****************************************************************************
//*
//* routine: timer0t_comp_isr
//* Date: 	 December 1, 2003
//* Updated: February 2, 2015
//* Author:  Ralph Pruitt
//* This Interrupt handler is called each time that a match occurs for timer0.
//* Thus, every 50msec this routine is called. Operations will be minimized within
//* this routine unless we are performing a fade on the backlight LED.
//*
//* Variables:
//*		 static	 char		buf[TASKBUFF];	 // Defines Tasking Buffer
//*		 static	 char		buf_in;			 // Buffer Input Pointer
//*		 static	 char		buf_out;		 // Buffer Output Pointer
//*		 static	 char		buf_cnt;		 //	Number of outstanding tasks
//*		 static	 char		led_coff;		 // Number of Clicks/Cycle LED Off.
//*		 static	 char		led_cnt;		 // Used for LED Fade off function.
//*
//*****************************************************************************
void timer0t_comp_isr(void)
{
    ticker++;
#ifdef DEBUGGR
    debug1(2);
#endif
    // Lets deal with processing the Sweep Mode Here.
    if (fast_flg == 4) { 		   // If it is 4, then we are in sweep mode, else continue.
      sweep1.sweep_cnt--;		   // Decrement Sweep Count.
	  if (sweep1.sweep_cnt == 0) {
        sweep_flg++ ;
	    if (sweep1.sweep_flg == 1)
	      sweep1.sweep_cnt = 1;		  			  // Reset Count for next tick.
	    else
	      sweep1.sweep_cnt = sweep1.sweep_lmt;		  // Reset Count for next tick.
      }
    } // Endif fast_flg ==4
}
//*****************************************************************************
//*
//* routine: int0_isr
//* Date: 	 December 1, 2003
//* Author:  Ralph Pruitt
//* This Interrupt Service Routine is called when a key press is detected. Thus
//* it activates overall firmware execution.
//*
//*****************************************************************************
void int0_isr(void)
{
 //external interupt on INT0
 key_down_flg = 1;	 			 // This flag is set when a Keypress is detected.
 R_ICU_IRQ15_Stop();			// Deactivate Keypad Interrupt.
}

//*****************************************************************************
//*
//* routine: init_devices
//* Date: 	 December 1, 2003
//* Author:  Ralph Pruitt
//* This routine activates all user initialization routines during power-up.
//*
//*****************************************************************************
//call this routine to initialise all peripherals
void init_devices(void)
{
	int x;
	// Initialize Key Variables
	// Initialize Tasking Variables
	buf_in = 0;
	buf_out = 0;
	buf_cnt = 0;
	for(x=0; x<TASKBUFF; x++)
		buf[x]=0;
	// Initialize LED Fade Variable.
	led_coff = 0;
	led_cnt = 0;
	led_fcnt = 0;		 // Used for LED Fade off function.

	// Initialize Key Variables
	two_second = 0;				 // Two Second Timer
	five_second = 0;			 	 // Five Second Timer
	two_minute = 0;				 // Two Minute Timer
	five_minute = 0;			 	 // Five Minute Timer
	d_tick = 0;   					 // Clear Initial d_tick.
	ticker = 0;   					 // Clear Initial ticker.
	cnt_dwn_flg = 0;				 // Clear Count Down Flag.
	tmr_update_flg = 0;			 // Clear Timer Update Flag.
	lsr_update_flg = 0;			 // Clear Laser Update Flag.
	alsr_update_flg = 0;			 // Clear All Laser Update Flag.
	key_down_flg = 0;	 			 // This flag is set when a Keypress is detected.
	fast_flg = 0;					 // Clear fast_flg by default
	laser1_disp = 0;			 	 // Clear Laser 1 Display Value.
	laser2_disp = 0;			 	 // Clear Laser 2 Display Value.
	laser3_disp = 0;			 	 // Clear Laser 3 Display Value.
	laser4_disp = 0;			 	 // Clear Laser 4 Display Value.
	nobeep_flg = 1;				 // Force to One to allow Beeps.
#ifdef STRM_NO
	StrmOn = 0;						// Disable Streaming to Console.
#else
	StrmOn = 1;						// Enable Streaming to Console.
#endif

	//***MOD***
	macro_flg = 0;					 // Macros not currently active.
	laser_flg = 0;					 // By Default the Laser is off.
	mntr_key_var = 0;				 // No Key presses are active by default.

	// Set key user selectable variables
	audio_flg = 1;	 			     // Enable Audio.

	// Initialize key Sweep Variables.
	sweep1.sweep_cnt = 0;	 		 // Set Sweep Count to zero.
	sweep1.sweep_lmt = 0;			 // Set Sweep Limit to zero.
	sweep1.sweep_dir = 0;			 // Set to Positive Sweep.
	sweep1.sweep_state = 0;		 // Set sweep state to Initial state.
	sweep1.sweep_ptr = 0;			 // Set current Sweep execution state to Initial Sweep.
	sweep1.sweep_key = 0;			 // Set variable modification ptr to Timer values.

	// Initialize Key Strings.
//	strcpy(tmr_minstr, "--");
	strcpy(tmr_minstr, "---");
	strcpy(tmr_secstr, "--");
	strcpy(Bat_Lvl, "___");
#if LEASEOP
	strcpy(lease_str, "            ");
#endif
	strcpy(lser1_strng, "         ");
	strcpy(lser2_strng, "         ");
	strcpy(lser3_strng, "         ");
	strcpy(lser4_strng, "         ");
#if sixdigit
	strcpy(prog_str, "------");
#else
	strcpy(prog_str, "---");
#endif

	//stop errant interrupts until set up
	CLI(); //disable all interrupts
	port_init();

	// ONLY Perform these next operations if we are not in LOW Power Mode.
	if ((mode != Low_PD) &&
		(mode != Soft_PD) &&
		(mode != Locked))
	{
		watchdog_init();
		timer0_init();

		// Power Down all lasers.
		R_MTU3_AllLasers_Off();

		// Power-up Key power-supplies.
		power_up1();

		// DeAssert Lasers FPGA...
		//TODO: Un-comment below when Laser Code is added.
		//ldlsrs_dis();

		// Wait for 30msec.
		accurate_delay(70);

		// Clear All Lasers to Off.
		//TODO: Un-comment below when Laser Code is added.
		//lasers_off();

		// Assert Reset Pin For BlueTooth.
		//AssertBT_rst();

		// Power-up Key power-supplies.
		power_up();

		//Initialize Audio Hardware.
		//TODO: Un-comment below when Sound Code is added.
		//init_sound();

	}
	else
	{
		// Wait for 170msec....So that Reset can be held low to reset BeaconII
		accurate_delay(170);
	}

	R_TMR0_Start(); //Start Timer 0
	keybrd_init();// Enable Keyboard Interrupts

	SEI(); //re-enable interrupts

	//all peripherals are now initialised
}
