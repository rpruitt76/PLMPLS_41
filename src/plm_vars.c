//****************************************************************************
//* Laser Pulsar Embedded Software
//* Date: December 1, 2003
//* Updated: January 9, 2015
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
//#include <iom128v.h>
//#include <macros.h>
#include <string.h>
#include <stdlib.h>
//#include <eeprom.h>
#include "LaserP.h"

//*****************************************************************************
//*
//* Variable Definitions
//*
//*****************************************************************************
//#pragma data:data
		 float	 			laser1_disp;			 // Laser 1 Display Value.
		 float	 			laser2_disp;			 // Laser 2 Display Value.
		 float	 			laser3_disp;			 // Laser 3 Display Value.
		 float	 			laser4_disp;			 // Laser 4 Display Value.
		 float				BGM_Temp;				 // Temperature of BGM Module.
		 unsigned int		prog_num;				 // Program Number
		 unsigned long		opmin_cnt;			 	 // Operational Minute Count for Unit.
#if LEASEOP
         unsigned long      opmin_lmt;		 	 	 // Number minutes to limit operation.
#endif
         unsigned long		serial_number;			 // Serial Number of unit.
  		 unsigned long 		lser1_time;		 		 // Laser 1 Load.
  		 unsigned long 		lser2S_time;		 	 // Laser 2 Sweep Load.
  		 unsigned long 		lser2_time;		 		 // Laser 2 Load.
  		 unsigned long 		lser3_time;		 		 // Laser 3 Load.
  		 unsigned long 		lser4_time;		 		 // Laser 4 Load.
		 unsigned long		laser1_count;	 		 // Laser 1 Count.
		 unsigned long		laser2_count;	 		 // Laser 2 Count.
		 unsigned long		laser3_count;	 		 // Laser 3 Count.
		 unsigned long		laser4_count;	 		 // Laser 4 Count.

		 int				opMode;					// Mode for unit to operate
		 											// 0:Normal	1: Demo		2:Lease
		 unsigned int		lockCode;				// Lock Variable that allows code to be unlocked
													// 5A5A: Unlocked
		 int				leaseDays;				// Number of days to operate Lease
		 int				leaseDay;				// Lock Down Lease Day of Month
		 int				leaseMnth;				// Lock Down Lease Month
		 int				leaseYear;				// Lock Down Lease Year.

		 unsigned int		var_timer;				// Timer to be used for shutdown timeout.
		 unsigned int		timeout_Value;			// Timeout Value used to be saved and restored.

		 unsigned char		buf[TASKBUFF];	 // Defines Tasking Buffer
		 unsigned char		buf_in;			 // Buffer Input Pointer
		 unsigned char		buf_out;		 // Buffer Output Pointer
		 unsigned char		buf_cnt;		 //	Number of outstanding tasks
		 unsigned char		led_coff;		 // Number of Clicks/Cycle LED Off.
		 unsigned char		led_cnt;		 // Used for LED Fade off function.
		 unsigned char		led_fcnt;		 // Used for LED Fade off function.
		 unsigned char	    sweep_flg;				 // Sweep Flag for Int to use for comunication.
  		 unsigned char 	    ticker, d_tick;			 // 1 Second Ticker Used to count Seconds.
  		 unsigned char 		stimer_low;				 // 16 Bit Timer Count Saved.
  		 unsigned char 		sprescale;				 // 16 Bit Timer Prescale.
  		 unsigned char 		stimer_low2;			 // Timer 2 Count Saved.
  		 unsigned char 		sprescale2;				 // Timer 2 Prescale.
		 unsigned char		mode;					 // System Tasking Mode.
		 unsigned char		sm;						 // Sub-Mode Variable
		 unsigned char		save_char;				 // Save Char Pointer
		 unsigned char		underline;				 // Underline Flag
		 unsigned char		Booted;					 // Simple Flag to track Boot State.
#if sixdigit
		 char	   			progwk_str[7];
		 char	   			prog_str[7];
		 unsigned long		progwk_num;				 // Program Number
#else
		 char	   			progwk_str[4];
		 char	   			prog_str[4];
		 unsigned int		progwk_num;				 // Program Number
#endif
		 unsigned int		tmr_min;				 // Timer Minutes
		 char	   			tmr_minstr[4];
		 unsigned char		tmr_sec;				 // Timer Seconds
		 char	   			tmr_secstr[3];
		 uchar				min_chg, sec_chg;		 // Generic vars for Changing timers.
		 char				min_str[3];				 // Generic String for Minutes.
		 char				sec_str[3];				 // Generic String for Seconds.
		 unsigned char		p5_second;				 // 0.5 Second Timer
		 unsigned char		two_second;				 // Two Second Timer
		 unsigned char		five_second;			 // Five Second Timer
		 unsigned char		two_minute;				 // Two Minute Timer
		 unsigned char		cnt_dwn_flg;			 // Flag to start Count Down.
		 unsigned char		tmr_update_flg;			 // Flag to over-ride update to timers.
		 unsigned char		lsr_update_flg;			 // Flag to over-ride update to Lasers.
		 unsigned char		alsr_update_flg;		 // Flag for updating all lasers.
		 unsigned char		key_down_flg;			 // This flag is set when a Keypress is detected.
		 unsigned char		fast_flg;				 // Set...Faster than 10Khz
		 unsigned char		audio_flg;				 // Set when Speaker is on.
		 unsigned char		nobeep_flg;				 // Set when Speaker is on.
		 unsigned int		five_minute;			 // Five Minute Timer
		 unsigned char		macro_flg;				 // Indicates that we are processing a macro.
		 unsigned char		entry_flg;				 // Used to indicate if a string will be displayed.
		 unsigned char	    cntrl_flg;				 // Control flag that controls prime freq generation through FPGA.
		 unsigned char		laser_flg;				 // Flag set while Laser Event Active.
		 unsigned char      StrmOn;					 // Used to enable/Disable Streaming Console Information
		 unsigned char		subClock_Fail;			 // SubClock Failure. Set if could not get RTC to work.
		 unsigned char		mntr_key_var;			 // Holds the state of an active Key Press from the Monitor
#if MCP4725
		 unsigned int		save_tick;				 // Global var to track Ticks for I2C..sounds.c
#endif
		 struct sweep_var 	sweep1;					 // Sweep Tracking Structure
		 struct macro_var   macro1;					 // Macro Tracking Structure
		 struct sweep_entry	sweep2;					 // Sweep Entry Structure
		 struct user_macro  macro2;					 // Macro Entry Structure
		 char	  	  		Bat_Lvl[10];
		 char	   			lser1_strng[FREQ_STR_LEN+1];
		 char	   			lser2_strng[FREQ_STR_LEN+1];
		 char	   			lser3_strng[FREQ_STR_LEN+1];
		 char	   			lser4_strng[FREQ_STR_LEN+1];
		 char				save_str[17];
		 char				dig_str[4];	   			 // Permanent string for digit calculations.
		 char				lease_str[LEASE_STR_LEN];
		 char				tglease_str[TG_LEASE_STR_LEN];
	  	 char				PlaceHldrB[4];		 	 // Place Holder
		 char				mac_addr[8];			// Saves Mac Address from Monitor Command

#ifdef DEBUGGR
		 uchar				debug_buffr[512];
  		 unsigned int 		deb_count=0;			 // Counter for debugger.
#endif


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
//* EEPROM Variable Definitions
//*
//*****************************************************************************
#pragma section C DATAFLASH
//  		 unsigned long 		lser1e_time = 500;	 		 // Laser 1 Load.
//  		 unsigned long 		lser2e_time = 250;	 		 // Laser 2 Load.
//  		 unsigned long 		lser3e_time = 125;	 		 // Laser 3 Load.
  		 const unsigned long 		lser1e_time = 0;	 		 // Laser 1 Load.
  		 const unsigned long 		lser2se_time = 0;	 		 // Laser 2 Sweep Load.
  		 const unsigned long 		lser2e_time = 0;	 		 // Laser 2 Load.
  		 const unsigned long 		lser3e_time = 0;	 		 // Laser 3 Load.
  		const unsigned long 		lser4e_time = 4;	 		 // Laser 4 Load.
  		const unsigned long		eopmin_cnt = 0;			 // Operational Minute Count for Unit.
#if LEASEOP
  		const unsigned long      eopmin_lmt = 300;		 	 // Number minutes to limit operation.
#endif
  		const unsigned long		eserial_number = 0;			 // Serial Number of unit.
  		const int				eopMode = 0; 	  			 // Mode for unit to operate
  									      	  	  	  	     // 0:Normal	1: Demo		2:Lease
		const unsigned int		elockCode = 0;				 // EEPROM Lock code
  		const int				eleaseDays = 0; 	  		 // Number of days to operate Lease
  		const int				eleaseDay = 1; 	  			 // Lock Down Lease Day of Month
  		const int				eleaseMnth = 1;	  			 // Lock Down Lease Month
  		const int				eleaseYear = 2015; 		 	 // Lock Down Lease Year.

  		const unsigned int		etimeout_Value = 240;		 // Timeout Value used to be saved and restored.

  		const unsigned char 		etimer_low = 125;		 	 // Timer 2 Count Saved.
  		const unsigned char 		eprescale = 2;			 	 // Timer 2 Prescale.
  		const unsigned char 		etimer_low2 = 125;		 	 // Timer 2 Count Saved.
  		const unsigned char 		eprescale2 = 2;			 	 // Timer 2 Prescale.
  		const unsigned char		emode = 0;				 	 // System Tasking Mode.
  		const unsigned char		esm = 1;					 // Sub-Mode Variable
  		const unsigned int		etmr_min = 3;				 // Timer Minutes
  		const unsigned char		etmr_sec = 0;				 // Timer Seconds
  		const unsigned int		eprog_num = 1;				 // Program Number
  		const unsigned char		eetmp1 = 1;				 	 // EE Place Holder
  		const unsigned char		eetmp2 = 2;				 	 // EE Place Holder
  		const unsigned char		eetmp3 = 3;				 	 // EE Place Holder
  		const unsigned char		eetmp4 = 4;				 	 // EE Place Holder
  		const unsigned char		eetmp5 = 5;				 	 // EE Place Holder
  		const char				emac_addr[8] = {0, 0, 0, 0, 0, 0, 0, 0};	// Saved Mac Address.
//		 Program 0
//  		const struct laseru_entry laser0_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};
//  		const struct laseru_entry laser0_data = {1, 2, 3, 4, "Program 0", 1};
  		const struct laseru_entry laser0_data = {1, 2, 3, 4, BLANK_SHRTSTRNG, 0};

//		 Program 1
//  		const struct laseru_entry laser1_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};
  		const struct laseru_entry laser1_data = {111111, 111111, 111111, 111111, BLANK_SHRTSTRNG, 0};

//		 Program 2
  		const struct laseru_entry laser2_data = {222222, 222222, 222222, 222222, BLANK_SHRTSTRNG, 0};

//		 Program 3
  		const struct laseru_entry laser3_data = {333333, 333333, 333333, 333333, BLANK_SHRTSTRNG, 0};

//		 Program 4
  		const struct laseru_entry laser4_data = {444444, 444444, 444444, 444444, BLANK_SHRTSTRNG, 0};

//		 Program 5
  		const struct laseru_entry laser5_data = {555555, 555555, 555555, 555555, BLANK_SHRTSTRNG, 0};

//		 Program 6
         const struct laseru_entry laser6_data = {666666, 666666, 666666, 666666, BLANK_SHRTSTRNG, 0};

//		 Program 7
         const struct laseru_entry laser7_data = {777777, 777777, 777777, 777777, BLANK_SHRTSTRNG, 0};

//		 Program 8
         const struct laseru_entry laser8_data = {888888, 888888, 888888, 888888, BLANK_SHRTSTRNG, 0};

//		 Program 9
         const struct laseru_entry laser9_data = {999999, 999999, 999999, 999999, BLANK_SHRTSTRNG, 0};

//		 Program 10
         const struct laseru_entry laser10_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 11
         const struct laseru_entry laser11_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 12
         const struct laseru_entry laser12_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 13
         const struct laseru_entry laser13_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 14
         const struct laseru_entry laser14_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 15
         const struct laseru_entry laser15_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 16
         const struct laseru_entry laser16_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 17
         const struct laseru_entry laser17_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 18
         const struct laseru_entry laser18_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 19
         const struct laseru_entry laser19_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 20
         const struct laseru_entry laser20_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 21
         const struct laseru_entry laser21_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 22
         const struct laseru_entry laser22_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 23
         const struct laseru_entry laser23_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 24
         const struct laseru_entry laser24_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 25
         const struct laseru_entry laser25_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 26
         const struct laseru_entry laser26_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 27
         const struct laseru_entry laser27_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 28
         const struct laseru_entry laser28_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 29
         const struct laseru_entry laser29_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 30
         const struct laseru_entry laser30_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 31
         const struct laseru_entry laser31_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 32
         const struct laseru_entry laser32_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 33
         const struct laseru_entry laser33_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 34
         const struct laseru_entry laser34_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 35
         const struct laseru_entry laser35_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 36
         const struct laseru_entry laser36_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 37
         const struct laseru_entry laser37_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 38
         const struct laseru_entry laser38_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 39
         const struct laseru_entry laser39_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 40
         const struct laseru_entry laser40_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 41
         const struct laseru_entry laser41_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 42
         const struct laseru_entry laser42_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 43
         const struct laseru_entry laser43_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 44
         const struct laseru_entry laser44_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 45
         const struct laseru_entry laser45_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 46
         const struct laseru_entry laser46_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 47
         const struct laseru_entry laser47_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 48
         const struct laseru_entry laser48_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 49
         const struct laseru_entry laser49_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 50
         const struct laseru_entry laser50_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 51
         const struct laseru_entry laser51_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 52
         const struct laseru_entry laser52_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 53
         const struct laseru_entry laser53_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 54
         const struct laseru_entry laser54_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 55
         const struct laseru_entry laser55_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 56
         const struct laseru_entry laser56_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 57
         const struct laseru_entry laser57_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 58
         const struct laseru_entry laser58_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 59
         const struct laseru_entry laser59_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 60
         const struct laseru_entry laser60_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 61
         const struct laseru_entry laser61_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 62
         const struct laseru_entry laser62_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 63
         const struct laseru_entry laser63_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 64
         const struct laseru_entry laser64_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 65
         const struct laseru_entry laser65_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 66
         const struct laseru_entry laser66_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 67
         const struct laseru_entry laser67_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 68
         const struct laseru_entry laser68_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 69
         const struct laseru_entry laser69_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 70
         const struct laseru_entry laser70_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 71
         const struct laseru_entry laser71_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 72
         const struct laseru_entry laser72_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 73
         const struct laseru_entry laser73_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 74
         const struct laseru_entry laser74_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 75
         const struct laseru_entry laser75_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 76
         const struct laseru_entry laser76_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 77
         const struct laseru_entry laser77_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 78
         const struct laseru_entry laser78_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 79
         const struct laseru_entry laser79_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 80
         const struct laseru_entry laser80_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 81
         const struct laseru_entry laser81_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 82
         const struct laseru_entry laser82_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 83
         const struct laseru_entry laser83_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 84
         const struct laseru_entry laser84_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 85
         const struct laseru_entry laser85_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 86
         const struct laseru_entry laser86_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 87
         const struct laseru_entry laser87_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 88
         const struct laseru_entry laser88_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 89
         const struct laseru_entry laser89_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 90
         const struct laseru_entry laser90_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 91
         const struct laseru_entry laser91_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 92
         const struct laseru_entry laser92_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 93
         const struct laseru_entry laser93_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 94
         const struct laseru_entry laser94_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 95
         const struct laseru_entry laser95_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 96
         const struct laseru_entry laser96_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 97
         const struct laseru_entry laser97_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 98
         const struct laseru_entry laser98_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 99
         const struct laseru_entry laser99_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 100
   		 const struct laseru_entry laser100_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 101
   		 const struct laseru_entry laser101_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 102
   		 const struct laseru_entry laser102_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 103
   		 const struct laseru_entry laser103_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 104
   		 const struct laseru_entry laser104_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 105
   		 const struct laseru_entry laser105_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 106
   		 const struct laseru_entry laser106_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 107
   		 const struct laseru_entry laser107_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 108
   		 const struct laseru_entry laser108_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 109
   		 const struct laseru_entry laser109_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 110
   		 const struct laseru_entry laser110_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 111
   		 const struct laseru_entry laser111_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 112
   		 const struct laseru_entry laser112_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 113
   		 const struct laseru_entry laser113_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 114
   		 const struct laseru_entry laser114_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 115
   		 const struct laseru_entry laser115_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 116
   		 const struct laseru_entry laser116_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 117
   		 const struct laseru_entry laser117_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 118
   		 const struct laseru_entry laser118_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 119
   		 const struct laseru_entry laser119_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 120
   		 const struct laseru_entry laser120_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 121
   		 const struct laseru_entry laser121_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 122
   		 const struct laseru_entry laser122_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 123
   		 const struct laseru_entry laser123_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 124
   		 const struct laseru_entry laser124_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 125
   		 const struct laseru_entry laser125_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 126
   		 const struct laseru_entry laser126_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 127
   		 const struct laseru_entry laser127_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 128
   		 const struct laseru_entry laser128_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 129
   		 const struct laseru_entry laser129_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 130
   		 const struct laseru_entry laser130_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 131
   		 const struct laseru_entry laser131_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 132
   		 const struct laseru_entry laser132_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 133
   		 const struct laseru_entry laser133_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 134
   		 const struct laseru_entry laser134_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 135
   		 const struct laseru_entry laser135_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 136
   		 const struct laseru_entry laser136_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 137
   		 const struct laseru_entry laser137_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 138
   		 const struct laseru_entry laser138_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 139
   		 const struct laseru_entry laser139_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 140
   		 const struct laseru_entry laser140_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 141
   		 const struct laseru_entry laser141_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 142
   		 const struct laseru_entry laser142_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 143
   		 const struct laseru_entry laser143_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 144
   		 const struct laseru_entry laser144_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 145
   		 const struct laseru_entry laser145_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 146
   		 const struct laseru_entry laser146_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 147
   		 const struct laseru_entry laser147_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 148
   		 const struct laseru_entry laser148_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 149
   		 const struct laseru_entry laser149_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 150
   		 const struct laseru_entry laser150_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 151
   		 const struct laseru_entry laser151_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 152
   		 const struct laseru_entry laser152_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 153
   		 const struct laseru_entry laser153_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 154
   		 const struct laseru_entry laser154_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 155
   		 const struct laseru_entry laser155_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 156
   		 const struct laseru_entry laser156_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 157
   		 const struct laseru_entry laser157_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 158
   		 const struct laseru_entry laser158_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 159
   		 const struct laseru_entry laser159_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 160
   		 const struct laseru_entry laser160_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 161
   		 const struct laseru_entry laser161_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 162
   		 const struct laseru_entry laser162_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 163
   		 const struct laseru_entry laser163_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 164
   		 const struct laseru_entry laser164_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 165
   		 const struct laseru_entry laser165_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 166
   		 const struct laseru_entry laser166_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 167
   		 const struct laseru_entry laser167_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 168
   		 const struct laseru_entry laser168_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 169
   		 const struct laseru_entry laser169_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 170
   		 const struct laseru_entry laser170_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 171
   		 const struct laseru_entry laser171_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 172
   		 const struct laseru_entry laser172_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 173
   		 const struct laseru_entry laser173_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 174
   		 const struct laseru_entry laser174_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 175
   		 const struct laseru_entry laser175_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 176
   		 const struct laseru_entry laser176_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 177
   		 const struct laseru_entry laser177_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 178
   		 const struct laseru_entry laser178_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 179
   		 const struct laseru_entry laser179_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 180
   		 const struct laseru_entry laser180_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 181
   		 const struct laseru_entry laser181_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 182
   		 const struct laseru_entry laser182_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 183
   		 const struct laseru_entry laser183_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 184
   		 const struct laseru_entry laser184_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 185
   		 const struct laseru_entry laser185_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 186
   		 const struct laseru_entry laser186_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 187
   		 const struct laseru_entry laser187_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 188
   		 const struct laseru_entry laser188_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 189
   		 const struct laseru_entry laser189_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 190
   		 const struct laseru_entry laser190_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 191
   		 const struct laseru_entry laser191_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 192
   		 const struct laseru_entry laser192_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 193
   		 const struct laseru_entry laser193_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 194
   		 const struct laseru_entry laser194_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 195
   		 const struct laseru_entry laser195_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 196
   		 const struct laseru_entry laser196_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 197
   		 const struct laseru_entry laser197_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 198
   		 const struct laseru_entry laser198_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 199
   		 const struct laseru_entry laser199_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 200
         const struct laseru_entry laser200_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 201
         const struct laseru_entry laser201_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 202
         const struct laseru_entry laser202_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 203
         const struct laseru_entry laser203_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 204
         const struct laseru_entry laser204_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 205
         const struct laseru_entry laser205_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 206
         const struct laseru_entry laser206_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 207
   		 const struct laseru_entry laser207_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 208
   		 const struct laseru_entry laser208_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 209
   		 const struct laseru_entry laser209_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 210
   		 const struct laseru_entry laser210_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 211
   		 const struct laseru_entry laser211_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 212
   		 const struct laseru_entry laser212_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 213
   		 const struct laseru_entry laser213_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 214
   		 const struct laseru_entry laser214_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 215
   		 const struct laseru_entry laser215_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 216
   		 const struct laseru_entry laser216_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 217
   		 const struct laseru_entry laser217_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 218
   		 const struct laseru_entry laser218_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 219
   		 const struct laseru_entry laser219_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 220
   		 const struct laseru_entry laser220_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 221
   		 const struct laseru_entry laser221_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 222
   		 const struct laseru_entry laser222_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 223
   		 const struct laseru_entry laser223_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 224
   		 const struct laseru_entry laser224_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 225
   		 const struct laseru_entry laser225_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 226
   		 const struct laseru_entry laser226_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 227
   		 const struct laseru_entry laser227_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 228
   		 const struct laseru_entry laser228_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 229
   		 const struct laseru_entry laser229_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 230
   		 const struct laseru_entry laser230_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 231
   		 const struct laseru_entry laser231_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 232
   		 const struct laseru_entry laser232_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 233
   		 const struct laseru_entry laser233_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 234
   		 const struct laseru_entry laser234_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 235
   		 const struct laseru_entry laser235_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 236
   		 const struct laseru_entry laser236_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 237
   		 const struct laseru_entry laser237_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 238
   		 const struct laseru_entry laser238_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 239
   		 const struct laseru_entry laser239_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 240
   		 const struct laseru_entry laser240_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 241
   		 const struct laseru_entry laser241_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 242
   		 const struct laseru_entry laser242_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 243
   		 const struct laseru_entry laser243_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 244
   		 const struct laseru_entry laser244_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 245
   		 const struct laseru_entry laser245_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 246
   		 const struct laseru_entry laser246_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 247
   		 const struct laseru_entry laser247_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 248
   		 const struct laseru_entry laser248_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 249
   		 const struct laseru_entry laser249_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 250
   		 const struct laseru_entry laser250_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 251
   		 const struct laseru_entry laser251_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 252
   		 const struct laseru_entry laser252_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 253
   		 const struct laseru_entry laser253_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 254
   		 const struct laseru_entry laser254_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 255
   		 const struct laseru_entry laser255_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 256
   		 const struct laseru_entry laser256_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 257
   		 const struct laseru_entry laser257_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 258
   		 const struct laseru_entry laser258_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 259
   		 const struct laseru_entry laser259_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 260
   		 const struct laseru_entry laser260_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 261
   		 const struct laseru_entry laser261_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 262
   		 const struct laseru_entry laser262_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 263
   		 const struct laseru_entry laser263_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 264
   		 const struct laseru_entry laser264_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 265
   		 const struct laseru_entry laser265_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 266
   		 const struct laseru_entry laser266_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 267
   		 const struct laseru_entry laser267_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 268
   		 const struct laseru_entry laser268_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 269
   		 const struct laseru_entry laser269_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 270
   		 const struct laseru_entry laser270_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 271
   		 const struct laseru_entry laser271_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 272
   		 const struct laseru_entry laser272_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 273
   		 const struct laseru_entry laser273_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 274
   		 const struct laseru_entry laser274_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 275
   		 const struct laseru_entry laser275_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 276
   		 const struct laseru_entry laser276_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 277
   		 const struct laseru_entry laser277_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 278
   		 const struct laseru_entry laser278_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 279
   		 const struct laseru_entry laser279_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 280
   		 const struct laseru_entry laser280_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 281
   		 const struct laseru_entry laser281_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 282
   		 const struct laseru_entry laser282_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 283
   		 const struct laseru_entry laser283_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 284
   		 const struct laseru_entry laser284_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 285
   		 const struct laseru_entry laser285_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 286
   		 const struct laseru_entry laser286_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 287
   		 const struct laseru_entry laser287_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 288
   		 const struct laseru_entry laser288_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 289
   		 const struct laseru_entry laser289_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 290
   		 const struct laseru_entry laser290_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 291
   		 const struct laseru_entry laser291_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 292
   		 const struct laseru_entry laser292_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 293
   		 const struct laseru_entry laser293_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 294
   		 const struct laseru_entry laser294_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 295
   		 const struct laseru_entry laser295_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 296
   		 const struct laseru_entry laser296_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 297
   		 const struct laseru_entry laser297_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 298
   		 const struct laseru_entry laser298_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program 299
   		 const struct laseru_entry laser299_data = {0, 0, 0, 0, BLANK_SHRTSTRNG, 0};

//		 Program Sweep1
		 const struct sweep_entry sweep1_data = {0, 0, 100, 1000, 500, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

 		 const struct sweep_entry sweep2_data = {0, 0, 100, 1000, 700, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

		 const struct sweep_entry sweep3_data = {0, 0, 100, 1000, 800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		 
		 const struct sweep_entry sweep4_data = {0, 0, 100, 1000, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		 
		 const struct sweep_entry sweep5_data = {0, 0, 100, 1000, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

		 const struct sweep_entry sweep6_data = {0, 0, 100, 1000, 500, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

 		 const struct sweep_entry sweep7_data = {0, 0, 100, 1000, 700, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

		 const struct sweep_entry sweep8_data = {0, 0, 100, 1000, 800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

		 const struct sweep_entry sweep9_data = {0, 0, 100, 1000, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

		 const struct sweep_entry sweep10_data = {0, 0, 100, 1000, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//		 Program User Macros
/*		 const struct user_macro macro1_data = {1,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro2_data = {2,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING}; */

		 const struct user_macro macro1_data = {1,
		 		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  "User Macro 1"};

		 		 const struct user_macro macro2_data = {2,
		 		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
		 										  0, 4, 6, 0, 4, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  0, 0, 0, 0, 0, 0, 0, 0, 0,
		 										  "User Macro 2"};

		 const struct user_macro macro3_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};
		 
		 const struct user_macro macro4_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};
		 
		 const struct user_macro macro5_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};
		 
		 const struct user_macro macro6_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};
		 
		 const struct user_macro macro7_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};
		 
		 const struct user_macro macro8_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};
		 
		 const struct user_macro macro9_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro10_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro11_data = {1,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro12_data = {2,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro13_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro14_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro15_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro16_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro17_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro18_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro19_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro20_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro21_data = {1,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro22_data = {2,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro23_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro24_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro25_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro26_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro27_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro28_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro29_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

		 const struct user_macro macro30_data = {3,
		 				   			      0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 4, 6, 0, 4, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  0, 0, 0, 0, 0, 0, 0, 0, 0,
										  MACRO_STRING};

#pragma section
