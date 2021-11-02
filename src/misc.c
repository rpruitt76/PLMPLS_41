//****************************************************************************
//* 
//*	misc.c
//* 
//* These routines are used to all PLM processing.
//* accurate_delay();   Delay set for 1 msec increments
//* char *str_chg_char(size_t length, unsigned char var1)
//* char *str_chg_long(size_t length, unsigned long var1)
//*
//****************************************************************************
//* Laser Pulsar Embedded Software
//* Date: December 11, 2003
//* Updated: January 9, 2015
//* Designer: Ralph Pruitt
//* Property: LED Healing Light, INC.
//* Copyright: December 2003
//* Description: This software is used with the 1st release of the "PLM".
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
#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
#include <string.h>
#include <stdlib.h>
#include  <stdio.h>
#include <r_cg_userdefine.h>
#include "LaserP.h"
#include "r_cg_s12ad.h"
#include "r_cg_tmr.h"
#include "r_cg_mtu3.h"
#include "r_cg_icu.h"
#include "r_cg_wdt.h"
#include "r_cg_rtc.h"
#include "gpio.h"
#include "hmc832.h"

static char Save_Time[20];
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
//* routine: sleep_code
//* Date: 	 January 2, 2004
//* Author:  Ralph Pruitt
//* This routine performs several key functions involved in putting the Laser
//* Pulsar into and out of Low Power State. These steps are as follows:
//*	1. Disable Timer 0.
//*	2. Clear LCD Screen.
//*	3. Turn off LCD Screen.
//*     4. Set Micro Hardware for Low Power Mode with External Int0 Only.
//*	5. Sleep
//*	6. Re-enable key Hardware after wake-up.
//*
//*****************************************************************************
void sleep_code(void)
{
	// 0. Save New Mode of
	// If shutdown is because of locked, we need to wakeup in locked state.
	if ( mode == Locked )
		mode = Locked_CONTINUE;
	else
		mode = Soft_PD_CONTINUE;					// After wakeup will need to process as reset restore.
	save_vars();  	 	  					    // Save Updated Variables.

	// 1. Disable Timers.
	R_TMR0_Stop();
	R_MTU3_AllLasers_Off();

	// 1a. Disable Watchdog Timer.
	R_WDT_Disable();  		  //Disable WATCHDOG.

	// 1b. Power Down PLLs and Laser Driver Pins.
	lasers_off();

	/*
	 * 1c. Power Off Lasers.
	 */
	accurate_delay(10);
	hmc_PwrOff_Lsrs();
	accurate_delay(10);

	// If in a Fast Shutdown mode, No Need to turn off or clear LCD....
//  if (mode != Low_PD) {
	if ((mode != Low_PD) &&
			(mode != Soft_PD) &&
			(mode != Locked)) {
		// 1b. Perform Misc steps to cleanup for sleep.
#if GRAPHICS
		init_lcd2();	 	 	   		 		  	    // Initialize Graphics LCD Display.
#else
		init_lcd();	 	 	   		 		  	    // Initialize Alpha LCD Display.
#endif

		// 2. Clear LCD Screen.
		clear_screen();

		// 3. Turn Off LCD Screen.
		turnoff_lcd();
	}
	else {
#if GRAPHICS
		init_lcd2off();	 	 	   		 		  	    // Initialize Graphics LCD Display.
#else
		init_lcd();	 	 	   		 		  	    // Initialize Alpha LCD Display.
#endif
	}
	//init_devices();

	// Power-down Key power-supplies.
	power_dn();

	// Power-down Audio Hardware.
	powerdn_sound();

	// 3a. Force All Pending Ints Clear.
	R_ICU_Software_Stop();
	R_ICU_Software2_Stop();

	// 3b. Enable External Int for Key Scan Wakeup.
//	R_ICU_Create();
//	R_ICU_IRQ15_Start();

  // 4. Set Micro Hardware for Low Power Mode with External Int0 Only.
	PORT0.PDR.BYTE &= ~0x80U;	// Tri-State XCS.
	PORT1.PDR.BYTE &= ~0x64U;	// Tri-State E1, E2, and R/W.
	PORT2.PDR.BYTE &= ~0xC2U;	// Tri-State RS, TDO, and TCK.
	PORT3.PDR.BYTE = 0x00U;		// Tri-State TDI, TMS, DIN, CCLK, TRSTn, and NMI.
	PORT4.PDR.BYTE &= ~0x7FU;	// Tri-State BATVLTG, PinDiode0, PinDiode1, PinDiode2,
								// PinDiode3, START, and SDPWREN.
	PORT6.PDR.BYTE &= ~0x30U;	// Tri-State LCDPWR and BCKLGHT.
	PORT9.PDR.BYTE &= ~0x0CU;	// Tri-State ~Fault and ~CHRG.
	PORTA.PDR.BYTE &= ~0x40U;	// Tri-State RTS5#.
	PORTB.PDR.BYTE = 0x00U;		// Tri-State SDCD and SDWP.
	PORTC.PDR.BYTE = 0x00U;		// Tri-State TXD5, RXD5, and CTS5#.
	PORTD.PDR.BYTE = 0x00U;		// Tri-State SDD2, SDD3, SDCMD, SDCLK, SDD0, and SDD1.

	/*
	 * Sleep all External IO Pins tracked by gpio Driver....11/27/2020...RP
	 */
	GPIO_Sleep();

	// Configure Port 7 as Output Low(Columns) for Wakeup
	PORT7.PDR.BYTE = 0xFFU;		// Set Port 7 as Output Low.
	PORT7.PODR.BYTE = 0x00U;

	PORT6.PDR.BYTE = 0x00;		// Set Port 6 Bits 0-2 as Input(ROWs).
	PORT6.PCR.BYTE = 0x07;		// Enable Pull up Resistors(ROWs)

	// 3b. Enable External Int for Key Scan Wakeup.
	R_ICU_Create();
	R_ICU_IRQ15_Start();

	// Set Delay to allow ports to settle before sleep
	accurate_delay(30); 		// Delay for 30msec.
	//accurate_delay(180); 		// Delay for 30msec.

	SYSTEM.PRCR.WORD = 0xA50BU;
	SYSTEM.DPSIEGR1.BYTE &= ~0x80;
	SYSTEM.DPSIER1.BYTE |= 0x80;
	accurate_delay(1); 		// Delay for 1msec.
	//accurate_delay(6); 		// Delay for 1msec.
	while ((SYSTEM.DPSIFR1.BYTE & 0x80) > 1)
		SYSTEM.DPSIFR1.BYTE = 0;
	SYSTEM.SBYCR.WORD |=0x8000U;
	SYSTEM.DPSBYCR.BYTE |= 0xC3U;

	// Set Delay to allow ports to settle before sleep
	accurate_delay(30); 		// Delay for 30msec.
	//accurate_delay(180); 		// Delay for 30msec.
	SYSTEM.PRCR.WORD = 0xA500U;

	// 5. Sleep.
	wait();

	//NOTE: Code from here forward will not be accessed since we are dropping into Deep Sleep/Deep software Standby Mode.


	//  MCUCSR = 0x00; 	 // Turn On JTAG for Debug.
	//  MCUCSR = 0x00;
	// 6. Re-enable Key Hardware after wake-up.
	SYSTEM.PRCR.WORD = 0xA50BU;
	SYSTEM.SBYCR.WORD &= ~0x8000U;
	SYSTEM.DPSIER1.BYTE |= 0x80;
	SYSTEM.DPSIFR1.BYTE = 0;
	SYSTEM.DPSBYCR.BYTE = 0x03U;
	SYSTEM.PRCR.WORD = 0xA500U;

	accurate_delay(1); 		// Delay for 1msec.

	// 6a. Disable Keyscan Wakeup Int.
	R_ICU_IRQ15_Stop();

	// Initialize HW
	HardwareWakeup();

	strcpy(Bat_Lvl, Battery_Test());    // Get Battery Status.....
	if ((mode == LOW_BAT) ||
			(mode == Soft_PD) ||
			(mode == Locked) ||
			(mode == Low_PD)) {				// But...is battery now low?

		if (mode == LOW_BAT)
			mode = Low_PD;	  				// YES...We are now in true Low Power Mode..

		nobeep_flg = 0;				    // Turn Off Beep Till mode determined.
		// Re-enable Timer 0.
		timer0_init();
	}
	else { 	 							// NO...Perform Normal Wakeup on LCD.
		// 7. Re-enable Timer 0.
		timer0_init();

		// 7a1. Init Key Ports.
		port_init();

		// 7a. Re-enable Watchdog Timer.
		watchdog_init();

		// Power-up Key power-supplies.
		power_up1();
		// DeAssert Lasers FPGA...
		ldlsrs_dis();


		// Wait for 70msec.
		accurate_delay(70);

		init_devices();

		// Clear All Lasers to Off.
		lasers_off();

		// Power-up Key power-supplies.
		power_up();

		//Initialize Audio Hardware.
		init_sound();

		// 8. Configure LCD ON...
#if GRAPHICS
		init_lcd2();
#else
		init_lcd();
#endif
	}
}

//*****************************************************************************
//*
//* routine: very_accurate_delay
//* Date:    June 1, 2006
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine is used to set a very small accurate delays based on the value passed to the
//* routine. 
//* Input:
//*		  delay value:	 	 This value is used as a multiplier to the basic
//*		  					 delay value of 10 usec.
//*
//*****************************************************************************
void very_accurate_delay(unsigned char delay1)
{
  R_BSP_SoftwareDelay((10 * delay1) , BSP_DELAY_MICROSECS);

  //unsigned char b, c;
/*  for (c=0; c<delay1; c++)
    for (b=0; b<200; b++)
      WDR(); //this prevents a timout on enabling */
}

//*****************************************************************************
//*
//* routine: accurate_delay
//* Date:    December 12, 2003
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine is used to set accurate delays based on the value passed to the
//* routine. 
//* Input:
//*		  delay value:	 	 This value is used as a multiplier to the basic
//*		  					 delay value of 1 msec.
//*
//*****************************************************************************
void accurate_delay(unsigned char delay1)
{
	unsigned char c;

  	for (c=0; c<delay1; c++)
  	{
  		  R_BSP_SoftwareDelay(1 , BSP_DELAY_MILLISECS);
  		  WDR(); //this prevents a timout on enabling
  	}
}

//*****************************************************************************
//*
//* routine: short_delay
//* Date:    December 14, 2003
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine is used for a short delay. Each Tick= 1usec.
//*
//*****************************************************************************
void short_delay(unsigned char b)
{
	  R_BSP_SoftwareDelay(b, BSP_DELAY_MICROSECS);
}

//*****************************************************************************
//*
//* routine: Delay
//* Date:    January 12, 2015
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine is used for a defined short delay. Each Call= 250usec.
//*
//*****************************************************************************
void Delay( void )
{
	  R_BSP_SoftwareDelay(250, BSP_DELAY_MICROSECS);
}

//*****************************************************************************
//*
//* routine: long_delay
//* Date:    April 13, 2007
//* Author:  Ralph Pruitt
//* This routine is used to set long delays based on the value passed to the
//* routine. 
//* Input:
//*		  delay value:	 	 This value is used as a multiplier to the basic
//*		  					 delay value of 1 sec.
//*
//*****************************************************************************
void long_delay(unsigned char delay1)
{
  unsigned char b,c;

  for (c=0; c<delay1; c++)
    for (b=0; b<5; b++)
      accurate_delay(200);
}

//*****************************************************************************
//*
//* routine: str_chg_char
//* Date:    January 2, 2004
//* Author:  Ralph Pruitt
//* Convert Target unsigned char var to certain length string buffered by spaces.
//*
//*****************************************************************************
void str_chg_char(char *temp, unsigned char length, unsigned char var1, unsigned char type_flag)
{
  size_t temp2;
  char temp3[9];

  itoa(temp3, (int)var1, 10);
  if (length < strlen(temp3)) {
    strncpy(temp, temp3, length);
  }
  else {
    temp2 = length - strlen(temp3);
    if (type_flag == ZEROS)
    {
      short_delay(0x10);
      cstrncpy2(temp, "000000000", temp2);
    }
    else
    {
      short_delay(0x10);
      cstrncpy2(temp, "         ", temp2);
    }
    temp[temp2] = NULL;
    strcat(temp, temp3);
  }
} 

//*****************************************************************************
//*
//* routine: str_chg_int
//* Date:    February 14, 2004
//* Author:  Ralph Pruitt
//* Convert Target unsigned int var to certain length string buffered by spaces.
//*
//*****************************************************************************
void str_chg_int(char *temp, unsigned char length, unsigned int var1, unsigned char type_flag)
{
  size_t temp2;
  char temp3[9];

  itoa(temp3, var1, 10);
  temp2 = length - strlen(temp3);
  if (type_flag == ZEROS)
  {
    short_delay(0x10);
    cstrncpy2(temp, "000000000", temp2);
  }
  else
  {
    short_delay(0x10);
    cstrncpy2(temp, "         ", temp2);
  }
  temp[temp2] = NULL;
  strcat(temp, temp3);
} 

//*****************************************************************************
//*
//* routine: str_chg_ulong
//* Date:    June 1, 2010
//* Author:  Ralph Pruitt
//* Convert Target unsigned long var to certain length string buffered by spaces.
//*
//*****************************************************************************
void str_chg_ulong(char *temp, unsigned char length, unsigned long var1, unsigned char type_flag)
{
  size_t temp2;
  char temp3[9];

  ultoa(temp3, var1, 10);
  temp2 = length - strlen(temp3);
  if (type_flag == ZEROS)
  {
    short_delay(0x10);
    cstrncpy2(temp, "000000000", temp2);
  }
  else
  {
    short_delay(0x10);
    cstrncpy2(temp, "         ", temp2);
  }
  temp[temp2] = NULL;
  strcat(temp, temp3);
} 

//*****************************************************************************
//*
//* routine: str_chg_long
//* Date:    January 2, 2004
//* Author:  Ralph Pruitt
//* Convert Target unsigned long var to certain length string buffered by spaces.
//*
//*****************************************************************************
void str_chg_long(char *temp, unsigned char length, float var1)
{
//  size_t temp2;
//  long ticks;
//  float temp3;
//  char temp4[12];
  
  str_chg_long2(temp, length, var1);
} 

//*****************************************************************************
//*
//* routine: str_chg_long2
//* Date:    January 2, 2004
//* Updated: March 3, 2021
//* Author:  Ralph Pruitt
//* Convert Target unsigned long var to certain length string buffered by spaces.
//*
//*****************************************************************************
void str_chg_long2(char *temp, unsigned char length, float var1)
{
  char tempstr[18];
  char tempstr2[11];
  unsigned char length2;
  size_t temp2;
//  float temp3;
//  char *temp4;
  int status;
  
  // If var1=0..Then return a zero for Null.
  if (var1 == 0)
  {
    short_delay(0x10);
    cstrncpy2(temp, "0         ",length);
  }
  else if (var1 < 0)
  {
    cstrncpy2(temp, "0         ",length);
  }
  else {
	snprintf(tempstr2, 11, "%f", var1);
    //temp4 = ftoa(var1, &status);
    if (status == -1)
      cstrncpy2(temp, "000000000", length);
    else if (status == -2)
      cstrncpy2(temp, "Too Big!   ",length);
    else {
	  // Find length of converted string.
	  length2 = strlen(tempstr2);
	  // If new string is size is less then desired length, then add zeros
	  if (length2 < length) {
        temp2 = length - length2;
	    strcpy(tempstr, "         ");
        strncat(tempstr2, tempstr, temp2);
	  }
	  // Now copy result to final location.
      strncpy(temp, tempstr2, length);
      temp[length-1] = 0;
    }
  }
} 

//*****************************************************************************
//*
//* routine: str_chg_long3
//* Date:    September 26, 2008
//* Author:  Ralph Pruitt
//* Convert Target unsigned long var to certain length string buffered by zeros.
//*
//*****************************************************************************
void str_chg_long3(char *temp, unsigned char length, unsigned long var1)
{
  char tempstr[18];
  unsigned char length2;
//  char temp3[18];
  char temp4[18];
  size_t temp2;
//  float temp3;
  
  // If var1=0..Then return a zero for Null.
  ultoa(temp4, var1, 10);
  // Find length of converted string.
  length2 = strlen(temp4);
  // If new string is size is less then desired length, then add zeros
  if (length2 < length) {
    temp2 = length - length2;
    cstrncpy2(tempstr, "000000000000", temp2);
    tempstr[temp2] = 0;
    strcat(tempstr, temp4);
    strncpy(temp, tempstr, length+1);
  }
  else
	  strncpy(temp, temp4, length+1);
} 

//*****************************************************************************
//*
//* routine: str_chg_to_long
//* Date:    January 2, 2004
//* Author:  Ralph Pruitt
//* Convert Target string freq to long int count at 8 Mhz.
//*
//*****************************************************************************
unsigned long str_chg_to_long(char *temp)
{
  long result;
  float temp3;
  
  temp3 = atof(temp);
  result = (unsigned long)(1000000/(temp3 * 2));
  return(result);
} 

//*****************************************************************************
//*
//* routine: str_chg_to_long2
//* Date:    January 2, 2004
//* Author:  Ralph Pruitt
//* Convert Target string freq to long int count at 8 Mhz based on SM Value
//*
//*****************************************************************************
void str_chg_to_long2(void)
{
  switch (sm) {
    case 5:
    case 1:
	  laser1_disp = atof(lser1_strng);			  // Convert String to Laser Variable.
	  break;
	case 2:
	  laser2_disp = atof(lser2_strng);			  // Convert String to Laser Variable.
	  break;
	case 3:
	  laser3_disp = atof(lser3_strng);			  // Convert String to Laser Variable.
	  break;
	case 4:
	  laser4_disp = atof(lser4_strng);			  // Convert String to Laser Variable.
	  break;
    case 6:
	  min_chg = atoi(min_str);					  // Convert String to min_chg.
	  sec_chg = atoi(sec_str);					  // Convert String to sec_chg.
	  progwk_num = atoi(progwk_str);			  // Convert String to progwk_num.
	  break;
  }
} 

//*****************************************************************************
//*
//* routine: WDR
//* Date:    January 8, 2015
//* Updated: February 1, 2015
//* Author:  Ralph Pruitt
//* Perform Watchdog refresh.
//*
//*****************************************************************************
void WDR( void )
{
  // Refresh the Watchdog Timer. See Section 33 in Users Guide.
  // Timer should be kicked every 69.907ms.
  WDT.WDTRR = 0x00;
  WDT.WDTRR = 0x00;
}

//*****************************************************************************
//*
//* routine: CLI
//* Date:    January 8, 2015
//* Author:  Ralph Pruitt
//* Disable Interrupts.
//*
//*****************************************************************************
void CLI( void )
{
  // Disable Interrupts
	R_BSP_InterruptsDisable();
}

//*****************************************************************************
//*
//* routine: SEI
//* Date:    January 8, 2015
//* Author:  Ralph Pruitt
//* Enable Interrupts.
//*
//*****************************************************************************
void SEI( void )
{
  // Enable Interrupts
	R_BSP_InterruptsEnable ();
}

//*****************************************************************************
//*
//* routine: itoa
//* Date:    January 8, 2015
//* Author:  Ralph Pruitt
//* Implements the standard itoa library routine.
//*
//*****************************************************************************
// Implementation of itoa()
char* itoa(char* str, int num, int base)
{
    int i = 0;
    uchar isNegative = FALSE;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = TRUE;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative == TRUE)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}

//*****************************************************************************
//*
//* routine: ltoa
//* Date:    January 8, 2015
//* Author:  Ralph Pruitt
//* Implements the standard ltoa library routine.
//*
//*****************************************************************************
// Implementation of ltoa()
char* ltoa(char* str, long num, int base)
{
    int i = 0;
    uchar isNegative = FALSE;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = TRUE;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative == TRUE)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}

//*****************************************************************************
//*
//* routine: ultoa
//* Date:    January 8, 2015
//* Author:  Ralph Pruitt
//* Implements the standard ultoa library routine.
//*
//*****************************************************************************
// Implementation of ultoa()
char* ultoa(char* str, unsigned long num, int base)
{
    int i = 0;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}

//*****************************************************************************
//*
//* routine: ftoa
//* Date:    January 8, 2015
//* Author:  Ralph Pruitt
//* Implements the standard ftoa library routine.
//*
//*****************************************************************************
char *ftoa(float f, int *status)
{
  long mantissa, int_part, frac_part;
  short exp2;
  LF_t x;
  char *p;
  static char outbuf[15];

  *status = 0;
  if (f == 0.0)
  {
    outbuf[0] = '0';
    outbuf[1] = '.';
    outbuf[2] = '0';
    outbuf[3] = 0;
    return outbuf;
  }
  x.F = f;

  exp2 = (unsigned char)(x.L >> 23) - 127;
  mantissa = (x.L & 0xFFFFFF) | 0x800000;
  frac_part = 0;
  int_part = 0;

  if (exp2 >= 31)
  {
    *status = _FTOA_TOO_LARGE;
    return 0;
  }
  else if (exp2 < -23)
  {
    *status = _FTOA_TOO_SMALL;
    return 0;
  }
  else if (exp2 >= 23)
    int_part = mantissa << (exp2 - 23);
  else if (exp2 >= 0) 
  {
    int_part = mantissa >> (23 - exp2);
    frac_part = (mantissa << (exp2 + 1)) & 0xFFFFFF;
  }
  else /* if (exp2 < 0) */
    frac_part = (mantissa & 0xFFFFFF) >> -(exp2 + 1);

  p = outbuf;

  if (x.L < 0)
    *p++ = '-';

  if (int_part == 0)
    *p++ = '0';
  else
  {
    ltoa(p, int_part, 10);
    while (*p)
      p++;
  }
  *p++ = '.';

  if (frac_part == 0)
    *p++ = '0';
  else
  {
    char m, max;

    max = sizeof (outbuf) - (p - outbuf) - 1;
    if (max > 7)
      max = 7;
    /* print BCD */
    for (m = 0; m < max; m++)
    {
      /* frac_part *= 10;	*/
      frac_part = (frac_part << 3) + (frac_part << 1); 

      *p++ = (frac_part >> 24) + '0';
      frac_part &= 0xFFFFFF;
    }
    /* delete ending zeroes */
    for (--p; p[0] == '0' && p[-1] != '.'; --p)
      ;
    ++p;
  }
  *p = 0;

  return outbuf;
}

//*****************************************************************************
//*
//* routine: reverse
//* Date:    January 9, 2015
//* Author:  Ralph Pruitt
//* Reverses the string that is passed.
//*
//*****************************************************************************
void reverse(char str[], int length)
{
    int i,j;
    char temp[100];
    for(i=length-1,j=0; i+1!=0; --i,++j)
    {
        temp[j]=str[i];
    }
    temp[j]='\0';
    strcpy(str,temp);
}

//*****************************************************************************
//*
//* routine: Save_Timer
//* Date:    August 20, 2020
//* Author:  Ralph Pruitt
//* Saves passed string to accesible Static Variable.
//*
//*****************************************************************************
void Save_Timer(char time_str[])
{
	strcpy(Save_Time, time_str);
}

//*****************************************************************************
//*
//* routine: Get_Timer
//* Date:    August 20, 2020
//* Author:  Ralph Pruitt
//* Returns ptr to accesible Static Variable of Saved Timer.
//*
//*****************************************************************************
char *Get_Timer( void )
{
	return Save_Time;
}

//*****************************************************************************
//*
//* routine: Init_Timer
//* Date:    August 20, 2020
//* Author:  Ralph Pruitt
//* Clear Static Variable of Saved Timer.
//*
//*****************************************************************************
void Init_Timer( void )
{
	int x;
	for (x=0; x<20; x++)
		Save_Time[x] = 0x00;
}

//*****************************************************************************
//*
//* routine: monPrint
//* Date:    August 20, 2020
//* Author:  Ralph Pruitt
//* Controlled Console print command.
//*
//*****************************************************************************
void monPrint(char Stat_Cd[], char str[])
{
	char temp_String[80];
	int x;
	//char linefeed[] = { 0x0d, 0x00 };
//#ifndef STRM_NO
	// Test StrmOn Flag and send console if set
#ifdef DEBUGGR
		debug1(D_PRINTF2);
#endif
#ifdef STRM_COM
		for (x=0;x<80;x++)
			temp_String[x] = 0x00;
		sprintf (temp_String, "%s:%s\r\n", Stat_Cd, str);
		R_SCI5_Serial_Print( temp_String, TX_SEND_WAIT);
		// If string contains a LF, Add CR.
		//if (strchr(str, '\x0a') != 0)
		//	R_SCI5_Serial_Print( linefeed, TX_SEND_WAIT);
#endif
#ifdef STRM_PRINTF
		printf("%s", str);
		printf("%s", linefeed);
#endif
#ifdef STRM_BOTH
		R_SCI5_Serial_Print( str, TX_SEND_WAIT);
		R_SCI5_Serial_Print( linefeed, TX_SEND_WAIT);
		printf("%s", str);
		printf("%s", linefeed);
#endif
//#endif
}

//*****************************************************************************
//*
//* routine: printf2
//* Date:    January 11, 2015
//* Author:  Ralph Pruitt
//* Controlled Console print command.
//*
//*****************************************************************************
void printf2(char str[])
{
	char linefeed[] = { 0x0d, 0x00 };
//#ifndef STRM_NO
	// Test StrmOn Flag and send console if set
	if (StrmOn)
	{
#ifdef DEBUGGR
		debug1(D_PRINTF2);
#endif
#ifdef STRM_COM
		R_SCI5_Serial_Print( str, TX_SEND_WAIT);
		// If string contains a LF, Add CR.
		if (strchr(str, '\x0a') != 0)
			R_SCI5_Serial_Print( linefeed, TX_SEND_WAIT);
#endif
#ifdef STRM_PRINTF
		printf("%s", str);
		printf("%s", linefeed);
#endif
#ifdef STRM_BOTH
		R_SCI5_Serial_Print( str, TX_SEND_WAIT);
		R_SCI5_Serial_Print( linefeed, TX_SEND_WAIT);
		printf("%s", str);
		printf("%s", linefeed);
#endif
	} // EndIf (StrmOn)
//#endif
}

//*****************************************************************************
//*
//* routine: EEPROM_WRITE
//* Date:    January 29, 2015
//* Author:  Ralph Pruitt
//* Flash Write Command
//*
//*****************************************************************************
#define FLASH_DBLOCK_SZ		64		// Size of Flash Data Block.
flash_err_t EEPROM_WRITE(uint32_t src_address, uint32_t dest_address, uint32_t num_bytes)
{
#ifdef MN_FLASH
	char tempstr[80];
#endif
	flash_err_t err;
	uint32_t Block_Address;
	uint32_t compare_Count;
	//flash_block_address_t Block_Address;
	uint8_t write_buffer[FLASH_DBLOCK_SZ], *temp_pointer, *mem_pointer;
	int x, c;

#ifdef MN_FLASH
	printf2("***********************************\n");
	printf2("EEPROM_WRITE\n");
	sprintf(tempstr,"Source Address: %xld\n", src_address);
	printf2(tempstr);
	sprintf(tempstr,"Destination Address: %xld\n", dest_address);
	printf2(tempstr);
	sprintf(tempstr,"Length: %ld\n", num_bytes);
	printf2(tempstr);
#endif
	// 1. Test and validate if destination is Valid
	if (((dest_address+num_bytes)>=FLASH_DF_BLOCK_INVALID) ||
		(dest_address<FLASH_DF_BLOCK_0))
	{
		printf2("Error. Invalid Destination Address\n");
		return FLASH_ERR_ADDRESS;
	}

	// 2. Test Destination Range and determine if write crosses Block boundary.
	Block_Address = dest_address & 0xFFFFFFC0;	// Strip Dest to Block Address.

	if ((dest_address+num_bytes) > (Block_Address+FLASH_DBLOCK_SZ))
	{
#ifdef MN_FLASH
		printf2("Two Block Operation..\n");
		// Process operation as two EEPROM Writes
		//WRITE1...Block 1
		// A. Read 64 Bytes from Data Flash.
		printf2("A. Read 64 Bytes from Data Flash.\n");
#endif
		temp_pointer = (uint8_t *)Block_Address;
		for (x=0; x<FLASH_DBLOCK_SZ; x++ )
		{
			write_buffer[x] = *temp_pointer++;
#ifdef MN_FLASH
			sprintf(tempstr,"%d/%xd  ", x, write_buffer[x]);
			printf2(tempstr);
#endif
		}
#ifdef MN_FLASH
		printf2("\n");
#endif
		// B. Now Copy source data into block.
#ifdef MN_FLASH
		printf2("B. Now Copy source data into block.\n");
#endif
		temp_pointer = (uint8_t *)src_address;
		c = dest_address-Block_Address;
		//for (x=(dest_address-Block_Address); x++; x<num_bytes-((Block_Address+FLASH_DBLOCK_SZ)-dest_address) )
		for (x=0; x<(FLASH_DBLOCK_SZ-(dest_address-Block_Address)); x++ )
		{
			write_buffer[c] = *temp_pointer++;
#ifdef MN_FLASH
			sprintf(tempstr,"%d/%xd  ", c, write_buffer[c]);
			printf2(tempstr);
#endif
			c += 1;
		}
#ifdef MN_FLASH
		printf2("\n");
#endif
		// C. Erase Target Block
#ifdef MN_FLASH
		printf2("C. Erase Target Block\n");
#endif
		err = R_FLASH_Erase((flash_block_address_t)Block_Address, 1);
		/* Check for errors. */
		if (FLASH_SUCCESS != err)
		{
			printf("ERROR: R_FLASH_Erase failed: %d\n", err);
			return err;
		}

		// Check for status through control function and move operation to
		// completion.
		//	do
		//	{
		//		// This will move the write sequence along...
		//		err = R_FLASH_Control(FLASH_CMD_STATUS_GET, NULL);
		//	}
		//	while (FLASH_ERR_BUSY == err);
		// D. Write Block to Data Flash.
#ifdef MN_FLASH
		printf2("D. Write Block to Data Flash.\n");
#endif
		err = R_FLASH_Write((uint32_t)write_buffer, Block_Address, FLASH_DBLOCK_SZ);
		/* Check for errors. */
		if (FLASH_SUCCESS != err)
		{
			printf("ERROR: R_FLASH_Write failed: %d\n", err);
			return err;
		}
#ifdef MN_FLASH
		printf2("Block 1 completed.\n");
#endif

		//WRITE2...Block 2
		Block_Address += FLASH_DBLOCK_SZ;
		// A. Read 64 Bytes from Data Flash.
#ifdef MN_FLASH
		printf2("A. Read 64 Bytes from Data Flash.\n");
#endif
		mem_pointer = (uint8_t *)Block_Address;
		for (x=0; x<FLASH_DBLOCK_SZ; x++)
		{
			write_buffer[x] = *mem_pointer++;
#ifdef MN_FLASH
			sprintf(tempstr,"%d/%xd  ", x, write_buffer[x]);
			printf2(tempstr);
#endif
		}
#ifdef MN_FLASH
		printf2("\n");
#endif
		// B. Now Copy source data into block.
#ifdef MN_FLASH
		printf2("B. Now Copy source data into block.\n");
#endif
		//temp_pointer = (uint8_t *)src_address;
		compare_Count = (num_bytes - ((uint32_t)temp_pointer - src_address));
		for (x=0; x<compare_Count; x++ )
		{
			write_buffer[x] = *temp_pointer++;
#ifdef MN_FLASH
			sprintf(tempstr,"%d/%xd  ", c, write_buffer[c]);
			printf2(tempstr);
#endif
		}
#ifdef MN_FLASH
		printf2("\n");
#endif
		// C. Erase Target Block
#ifdef MN_FLASH
		printf2("C. Erase Target Block\n");
#endif
		err = R_FLASH_Erase((flash_block_address_t)Block_Address, 1);
		/* Check for errors. */
		if (FLASH_SUCCESS != err)
		{
			printf("ERROR: R_FLASH_Erase failed: %d\n", err);
			return err;
		}

		// Check for status through control function and move operation to
		// completion.
		//	do
		//	{
		//		// This will move the write sequence along...
		//		err = R_FLASH_Control(FLASH_CMD_STATUS_GET, NULL);
		//	}
		//	while (FLASH_ERR_BUSY == err);
		// D. Write Block to Data Flash.
#ifdef MN_FLASH
		printf2("D. Write Block to Data Flash.\n");
#endif
		err = R_FLASH_Write((uint32_t)write_buffer, Block_Address, FLASH_DBLOCK_SZ);
		/* Check for errors. */
		if (FLASH_SUCCESS != err)
		{
			printf("ERROR: R_FLASH_Write failed: %d\n", err);
			return err;
		}
#ifdef MN_FLASH
		printf2("Block 1 completed.\n");
#endif
	}
	else
	{
#ifdef MN_FLASH
		printf2("One Block Operation..\n");
#endif
		// Process operation as one EEPROM Write.
		// A. Read 64 Bytes from Data Flash.
#ifdef MN_FLASH
		printf2("A. Read 64 Bytes from Data Flash.\n");
#endif
		temp_pointer = (uint8_t *)Block_Address;
		for (x=0; x<FLASH_DBLOCK_SZ; x++)
		{
			write_buffer[x] = *temp_pointer++;
#ifdef MN_FLASH
			sprintf(tempstr,"%d/%xd  ", x, write_buffer[x]);
			printf2(tempstr);
#endif
		}
#ifdef MN_FLASH
		printf2("\n");
#endif
		// B. Now Copy source data into block.
#ifdef MN_FLASH
		printf2("B. Now Copy source data into block.\n");
#endif
		temp_pointer = (uint8_t *)src_address;
		c = dest_address-Block_Address;
		for (x=0; x<num_bytes; x++)
		{
			write_buffer[c] = *temp_pointer++;
#ifdef MN_FLASH
			sprintf(tempstr,"%d/%xd  ", c, write_buffer[c]);
			printf2(tempstr);
#endif
			c += 1;
		}
#ifdef MN_FLASH
		printf2("\n");
#endif
		// C. Erase Target Block
#ifdef MN_FLASH
		printf2("C. Erase Target Block\n");
#endif
		err = R_FLASH_Erase((flash_block_address_t)Block_Address, 1);
		/* Check for errors. */
		if (FLASH_SUCCESS != err)
		{
			printf("ERROR: R_FLASH_Erase failed: %d\n", err);
			return err;
		}

		// Check for status through control function and move operation to
		// completion.
		//	do
		//	{
		//		// This will move the write sequence along...
		//		err = R_FLASH_Control(FLASH_CMD_STATUS_GET, NULL);
		//	}
		//	while (FLASH_ERR_BUSY == err);
		// D. Write Block to Data Flash.
#ifdef MN_FLASH
		printf2("D. Write Block to Data Flash.\n");
#endif
		err = R_FLASH_Write((uint32_t)write_buffer, Block_Address, FLASH_DBLOCK_SZ);
		/* Check for errors. */
		if (FLASH_SUCCESS != err)
		{
			printf("ERROR: R_FLASH_Write failed: %d\n", err);
			return err;
		}
#ifdef MN_FLASH
		printf2("Block Write completed.\n");
#endif
	}

	return err;
}

//*****************************************************************************
//*
//* routine: EEPROM_READ
//* Date:    February 3, 2015
//* Author:  Ralph Pruitt
//* Flash Read Command
//*
//*****************************************************************************
void EEPROM_READ(uchar *src_address, uchar *dest_address, uint32_t num_bytes)
{
	int x;
	for (x=0; x<num_bytes; x++)
	{
		*dest_address++ = *src_address++;
	}
}

//*****************************************************************************
//*
//* routine: Battery_Level
//* Date: 	 August 20, 2020
//* Updated: August 20, 2020
//* Author:  Ralph Pruitt
//* This routine returns a pointer to a three Character string that indicates
//* the current state of the battery equated as follows:
//*	<115		=	000
//*	116-165		=	002-100
//* >165		=   100
//*
//*****************************************************************************
char *Battery_Level(void)
{
  static char tempstr[4];
  uint16_t result;

  // 1. Start A/D Channel
  R_S12AD0_Start();

  // 1a. Delay to allow channel to stabilize. (10 msec)
  accurate_delay(10);

  // 2. Read ADCHANNEL0 and place in value1.
  R_S12AD0_Get_ValueResult(ADCHANNEL0, &result);

  // 3. Power Down ADC.
  R_S12AD0_Stop();
#ifdef TST_PATCH
//  result = BAT_HIGH+10;
#endif

  // 4. Filter and adjust value.
  if (result <= 120)
	  result = 0;
  else if (result >=160)
	  result = 100;
  else
	  result = (result - 120) * 2.5;

  // 4a. Build String.
  sprintf(tempstr, "%3d", result);

  return(tempstr);
}

//*****************************************************************************
//*
//* routine: Battery_Test
//* Date: 	 January 3, 2004
//* Updated: January 30, 2015
//* Author:  Ralph Pruitt
//* This routine returns a pointer to a three character string that indicates
//* the current state of the battery.
//*
//*****************************************************************************
char *Battery_Test(void)
{
  static char tempstr[4];
  uint16_t result;

  // 1. Start A/D Channel
  R_S12AD0_Start();

  // 1a. Delay to allow channel to stabilize. (10 msec)
  accurate_delay(10);

  // 2. Read ADCHANNEL0 and place in value1.
  R_S12AD0_Get_ValueResult(ADCHANNEL0, &result);

  // 3. Power Down ADC.
  R_S12AD0_Stop();
#ifdef TST_PATCH
//  result = BAT_HIGH+10;
#endif

  // 4. Test result and return correct string.
  if (result > BAT_HIGH)
    strcpy(tempstr, "***");
  else if (result > BAT_MEDIUM)
    strcpy(tempstr, "**_");
  else if (result > BAT_MEDLOW)
    strcpy(tempstr, "*__");
  else if (result > BAT_LOW)
    strcpy(tempstr, "___");
  else {
    mode = LOW_BAT;
	strcpy(tempstr, "___");
  }
  return(tempstr);
}

//*****************************************************************************
//*
//* routine: shft_str_left
//* Date: 	 January 3, 2004
//* Author:  Ralph Pruitt
//* This routine Shifts the passed string left by one char shortening it by one
//* character.
//*
//*****************************************************************************
void shft_str_left(char *string1, unsigned char length)
{
  unsigned char x;

  for (x=0; x<length; x++)
    string1[x] = string1[x+1];
  string1[length] = 0x00;
}

//*****************************************************************************
//*
//* routine: Backspace_Char
//* Date: 	 January 4, 2004
//* Author:  Ralph Pruitt
//* This routine Shifts the passed string Right by one char shortening it by one
//* character.
//*
//*****************************************************************************
void Backspace_Char(char *string1, unsigned char length)
{
  unsigned char x;

  for (x=length-1; x>0; x--)
    string1[x] = string1[x-1];
  string1[0] = ' ';
}

//*****************************************************************************
//*
//* routine: get_numstr
//* Date: 	 January 3, 2004
//* Author:  Ralph Pruitt
//* This routine Shifts the passed string left by one char shortening it by one
//* character.
//*
//*****************************************************************************
void itoa2(unsigned char mode_num)
{
#if GRAPHICS
   switch (mode_num) {
    case 0:
      write_char('0');					  // Send Data to LCD.
	  write_char('0');
	  break;
    case 1:
	  write_char('0');					  // Send Data to LCD.
	  write_char('1');
	  break;
    case 2:
	  write_char('0');					  // Send Data to LCD.
	  write_char('2');
	  break;
    case 3:
	  write_char('0');					  // Send Data to LCD.
	  write_char('3');
	  break;
    case 4:
	  write_char('0');					  // Send Data to LCD.
	  write_char('4');
	  break;
    case 5:
	  write_char('0');					  // Send Data to LCD.
	  write_char('5');
	  break;
    case 6:
	  write_char('0');					  // Send Data to LCD.
	  write_char('6');
	  break;
    case 7:
	  write_char('0');					  // Send Data to LCD.
	  write_char('7');
	  break;
    case 8:
	  write_char('0');					  // Send Data to LCD.
	  write_char('8');
	  break;
    case 9:
	  write_char('0');					  // Send Data to LCD.
	  write_char('9');
	  break;
    case 10:
	  write_char('1');					  // Send Data to LCD.
	  write_char('0');
	  break;
    case 11:
	  write_char('1');					  // Send Data to LCD.
	  write_char('1');
	  break;
    case 12:
	  write_char('1');					  // Send Data to LCD.
	  write_char('2');
	  break;
    case 13:
	  write_char('1');					  // Send Data to LCD.
	  write_char('3');
	  break;
    case 14:
	  write_char('1');					  // Send Data to LCD.
	  write_char('4');
	  break;
    case 15:
	  write_char('1');					  // Send Data to LCD.
	  write_char('5');
	  break;
    case 16:
	  write_char('1');					  // Send Data to LCD.
	  write_char('6');
	  break;
    case 17:
	  write_char('1');					  // Send Data to LCD.
	  write_char('7');
	  break;
    case 18:
	  write_char('1');					  // Send Data to LCD.
	  write_char('8');
	  break;
    case 19:
	  write_char('1');					  // Send Data to LCD.
	  write_char('9');
	  break;
    case 20:
	  write_char('2');					  // Send Data to LCD.
	  write_char('0');
	  break;
    case 21:
	  write_char('2');					  // Send Data to LCD.
	  write_char('1');
	  break;
    case 22:
	  write_char('2');					  // Send Data to LCD.
	  write_char('2');
	  break;
    case 23:
	  write_char('2');					  // Send Data to LCD.
	  write_char('3');
	  break;
    case 24:
	  write_char('2');					  // Send Data to LCD.
	  write_char('4');
	  break;
    case 25:
	  write_char('2');					  // Send Data to LCD.
	  write_char('5');
	  break;
    case 26:
	  write_char('2');					  // Send Data to LCD.
	  write_char('6');
	  break;
    case 27:
	  write_char('2');					  // Send Data to LCD.
	  write_char('7');
	  break;
    case 28:
	  write_char('2');					  // Send Data to LCD.
	  write_char('8');
	  break;
    case 29:
	  write_char('2');					  // Send Data to LCD.
	  write_char('9');
	  break;
    case 30:
	  write_char('3');					  // Send Data to LCD.
	  write_char('0');
	  break;
    case 31:
	  write_char('3');					  // Send Data to LCD.
	  write_char('1');
	  break;
    case 32:
	  write_char('3');					  // Send Data to LCD.
	  write_char('2');
	  break;
    case 33:
	  write_char('3');					  // Send Data to LCD.
	  write_char('3');
	  break;
    case 34:
	  write_char('3');					  // Send Data to LCD.
	  write_char('4');
	  break;
    case 35:
	  write_char('3');					  // Send Data to LCD.
	  write_char('5');
	  break;
    case 36:
	  write_char('3');					  // Send Data to LCD.
	  write_char('6');
	  break;
    case 37:
	  write_char('3');					  // Send Data to LCD.
	  write_char('7');
	  break;
    case 38:
	  write_char('3');					  // Send Data to LCD.
	  write_char('8');
	  break;
    case 39:
	  write_char('3');					  // Send Data to LCD.
	  write_char('9');
	  break;
    case 40:
	  write_char('4');					  // Send Data to LCD.
	  write_char('0');
	  break;
    case 41:
	  write_char('4');					  // Send Data to LCD.
	  write_char('1');
	  break;
    case 42:
	  write_char('4');					  // Send Data to LCD.
	  write_char('2');
	  break;
    case 43:
	  write_char('4');					  // Send Data to LCD.
	  write_char('3');
	  break;
    case 44:
	  write_char('4');					  // Send Data to LCD.
	  write_char('4');
	  break;
    case 45:
	  write_char('4');					  // Send Data to LCD.
	  write_char('5');
	  break;
    case 46:
	  write_char('4');					  // Send Data to LCD.
	  write_char('6');
	  break;
    case 47:
	  write_char('4');					  // Send Data to LCD.
	  write_char('7');
	  break;
    case 48:
	  write_char('4');					  // Send Data to LCD.
	  write_char('8');
	  break;
    case 49:
	  write_char('4');					  // Send Data to LCD.
	  write_char('9');
	  break;
    case 50:
	  write_char('5');					  // Send Data to LCD.
	  write_char('0');
	  break;
    case 51:
	  write_char('5');					  // Send Data to LCD.
	  write_char('1');
	  break;
    case 52:
	  write_char('5');					  // Send Data to LCD.
	  write_char('2');
	  break;
    case 53:
	  write_char('5');					  // Send Data to LCD.
	  write_char('3');
	  break;
    case 54:
	  write_char('5');					  // Send Data to LCD.
	  write_char('4');
	  break;
    case 55:
	  write_char('5');					  // Send Data to LCD.
	  write_char('5');
	  break;
    case 56:
	  write_char('5');					  // Send Data to LCD.
	  write_char('6');
	  break;
    case 57:
	  write_char('5');					  // Send Data to LCD.
	  write_char('7');
	  break;
    case 58:
	  write_char('5');					  // Send Data to LCD.
	  write_char('8');
	  break;
    case 59:
	  write_char('5');					  // Send Data to LCD.
	  write_char('9');
	  break;
    case 60:
	  write_char('6');					  // Send Data to LCD.
	  write_char('0');
	  break;
    case 61:
	  write_char('6');					  // Send Data to LCD.
	  write_char('1');
	  break;
    case 62:
	  write_char('6');					  // Send Data to LCD.
	  write_char('2');
	  break;
    case 63:
	  write_char('6');					  // Send Data to LCD.
	  write_char('3');
	  break;
    case 64:
	  write_char('6');					  // Send Data to LCD.
	  write_char('4');
	  break;
    case 65:
	  write_char('6');					  // Send Data to LCD.
	  write_char('5');
	  break;
    case 66:
	  write_char('6');					  // Send Data to LCD.
	  write_char('6');
	  break;
    case 67:
	  write_char('6');					  // Send Data to LCD.
	  write_char('7');
	  break;
    case 68:
	  write_char('6');					  // Send Data to LCD.
	  write_char('8');
	  break;
    case 69:
	  write_char('6');					  // Send Data to LCD.
	  write_char('9');
	  break;
    case 70:
	  write_char('7');					  // Send Data to LCD.
	  write_char('0');
	  break;
    case 71:
	  write_char('7');					  // Send Data to LCD.
	  write_char('1');
	  break;
    case 72:
	  write_char('7');					  // Send Data to LCD.
	  write_char('2');
	  break;
    case 73:
	  write_char('7');					  // Send Data to LCD.
	  write_char('3');
	  break;
    case 74:
	  write_char('7');					  // Send Data to LCD.
	  write_char('4');
	  break;
    case 75:
	  write_char('7');					  // Send Data to LCD.
	  write_char('5');
	  break;
    case 76:
	  write_char('7');					  // Send Data to LCD.
	  write_char('6');
	  break;
    case 77:
	  write_char('7');					  // Send Data to LCD.
	  write_char('7');
	  break;
    case 78:
	  write_char('7');					  // Send Data to LCD.
	  write_char('8');
	  break;
    case 79:
	  write_char('7');					  // Send Data to LCD.
	  write_char('9');
	  break;
    case 80:
	  write_char('8');					  // Send Data to LCD.
	  write_char('0');
	  break;
    case 81:
	  write_char('8');					  // Send Data to LCD.
	  write_char('1');
	  break;
    case 82:
	  write_char('8');					  // Send Data to LCD.
	  write_char('2');
	  break;
    case 83:
	  write_char('8');					  // Send Data to LCD.
	  write_char('3');
	  break;
    case 84:
	  write_char('8');					  // Send Data to LCD.
	  write_char('4');
	  break;
    case 85:
	  write_char('8');					  // Send Data to LCD.
	  write_char('5');
	  break;
    case 86:
	  write_char('8');					  // Send Data to LCD.
	  write_char('6');
	  break;
    case 87:
	  write_char('8');					  // Send Data to LCD.
	  write_char('7');
	  break;
    case 88:
	  write_char('8');					  // Send Data to LCD.
	  write_char('8');
	  break;
    case 89:
	  write_char('8');					  // Send Data to LCD.
	  write_char('9');
	  break;
    case 90:
	  write_char('9');					  // Send Data to LCD.
	  write_char('0');
	  break;
    case 91:
	  write_char('9');					  // Send Data to LCD.
	  write_char('1');
	  break;
    case 92:
	  write_char('9');					  // Send Data to LCD.
	  write_char('2');
	  break;
    case 93:
	  write_char('9');					  // Send Data to LCD.
	  write_char('3');
	  break;
    case 94:
	  write_char('9');					  // Send Data to LCD.
	  write_char('4');
	  break;
    case 95:
	  write_char('9');					  // Send Data to LCD.
	  write_char('5');
	  break;
    case 96:
	  write_char('9');					  // Send Data to LCD.
	  write_char('6');
	  break;
    case 97:
	  write_char('9');					  // Send Data to LCD.
	  write_char('7');
	  break;
    case 98:
	  write_char('9');					  // Send Data to LCD.
	  write_char('8');
	  break;
    case 99:
	  write_char('9');					  // Send Data to LCD.
	  write_char('9');
	  break;
  }
#else
   switch (mode_num) {
    case 0:
      lcd_comm(RSDATA, '0');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '0');
	  break;
    case 1:
	  lcd_comm(RSDATA, '0');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '1');
	  break;
    case 2:
	  lcd_comm(RSDATA, '0');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '2');
	  break;
    case 3:
	  lcd_comm(RSDATA, '0');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '3');
	  break;
    case 4:
	  lcd_comm(RSDATA, '0');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '4');
	  break;
    case 5:
	  lcd_comm(RSDATA, '0');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '5');
	  break;
    case 6:
	  lcd_comm(RSDATA, '0');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '6');
	  break;
    case 7:
	  lcd_comm(RSDATA, '0');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '7');
	  break;
    case 8:
	  lcd_comm(RSDATA, '0');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '8');
	  break;
    case 9:
	  lcd_comm(RSDATA, '0');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '9');
	  break;
    case 10:
	  lcd_comm(RSDATA, '1');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '0');
	  break;
    case 11:
	  lcd_comm(RSDATA, '1');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '1');
	  break;
    case 12:
	  lcd_comm(RSDATA, '1');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '2');
	  break;
    case 13:
	  lcd_comm(RSDATA, '1');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '3');
	  break;
    case 14:
	  lcd_comm(RSDATA, '1');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '4');
	  break;
    case 15:
	  lcd_comm(RSDATA, '1');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '5');
	  break;
    case 16:
	  lcd_comm(RSDATA, '1');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '6');
	  break;
    case 17:
	  lcd_comm(RSDATA, '1');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '7');
	  break;
    case 18:
	  lcd_comm(RSDATA, '1');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '8');
	  break;
    case 19:
	  lcd_comm(RSDATA, '1');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '9');
	  break;
    case 20:
	  lcd_comm(RSDATA, '2');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '0');
	  break;
    case 21:
	  lcd_comm(RSDATA, '2');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '1');
	  break;
    case 22:
	  lcd_comm(RSDATA, '2');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '2');
	  break;
    case 23:
	  lcd_comm(RSDATA, '2');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '3');
	  break;
    case 24:
	  lcd_comm(RSDATA, '2');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '4');
	  break;
    case 25:
	  lcd_comm(RSDATA, '2');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '5');
	  break;
    case 26:
	  lcd_comm(RSDATA, '2');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '6');
	  break;
    case 27:
	  lcd_comm(RSDATA, '2');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '7');
	  break;
    case 28:
	  lcd_comm(RSDATA, '2');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '8');
	  break;
    case 29:
	  lcd_comm(RSDATA, '2');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '9');
	  break;
    case 30:
	  lcd_comm(RSDATA, '3');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '0');
	  break;
    case 31:
	  lcd_comm(RSDATA, '3');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '1');
	  break;
    case 32:
	  lcd_comm(RSDATA, '3');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '2');
	  break;
    case 33:
	  lcd_comm(RSDATA, '3');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '3');
	  break;
    case 34:
	  lcd_comm(RSDATA, '3');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '4');
	  break;
    case 35:
	  lcd_comm(RSDATA, '3');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '5');
	  break;
    case 36:
	  lcd_comm(RSDATA, '3');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '6');
	  break;
    case 37:
	  lcd_comm(RSDATA, '3');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '7');
	  break;
    case 38:
	  lcd_comm(RSDATA, '3');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '8');
	  break;
    case 39:
	  lcd_comm(RSDATA, '3');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '9');
	  break;
    case 40:
	  lcd_comm(RSDATA, '4');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '0');
	  break;
    case 41:
	  lcd_comm(RSDATA, '4');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '1');
	  break;
    case 42:
	  lcd_comm(RSDATA, '4');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '2');
	  break;
    case 43:
	  lcd_comm(RSDATA, '4');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '3');
	  break;
    case 44:
	  lcd_comm(RSDATA, '4');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '4');
	  break;
    case 45:
	  lcd_comm(RSDATA, '4');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '5');
	  break;
    case 46:
	  lcd_comm(RSDATA, '4');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '6');
	  break;
    case 47:
	  lcd_comm(RSDATA, '4');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '7');
	  break;
    case 48:
	  lcd_comm(RSDATA, '4');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '8');
	  break;
    case 49:
	  lcd_comm(RSDATA, '4');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '9');
	  break;
    case 50:
	  lcd_comm(RSDATA, '5');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '0');
	  break;
    case 51:
	  lcd_comm(RSDATA, '5');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '1');
	  break;
    case 52:
	  lcd_comm(RSDATA, '5');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '2');
	  break;
    case 53:
	  lcd_comm(RSDATA, '5');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '3');
	  break;
    case 54:
	  lcd_comm(RSDATA, '5');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '4');
	  break;
    case 55:
	  lcd_comm(RSDATA, '5');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '5');
	  break;
    case 56:
	  lcd_comm(RSDATA, '5');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '6');
	  break;
    case 57:
	  lcd_comm(RSDATA, '5');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '7');
	  break;
    case 58:
	  lcd_comm(RSDATA, '5');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '8');
	  break;
    case 59:
	  lcd_comm(RSDATA, '5');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '9');
	  break;
    case 60:
	  lcd_comm(RSDATA, '6');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '0');
	  break;
    case 61:
	  lcd_comm(RSDATA, '6');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '1');
	  break;
    case 62:
	  lcd_comm(RSDATA, '6');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '2');
	  break;
    case 63:
	  lcd_comm(RSDATA, '6');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '3');
	  break;
    case 64:
	  lcd_comm(RSDATA, '6');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '4');
	  break;
    case 65:
	  lcd_comm(RSDATA, '6');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '5');
	  break;
    case 66:
	  lcd_comm(RSDATA, '6');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '6');
	  break;
    case 67:
	  lcd_comm(RSDATA, '6');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '7');
	  break;
    case 68:
	  lcd_comm(RSDATA, '6');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '8');
	  break;
    case 69:
	  lcd_comm(RSDATA, '6');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '9');
	  break;
    case 70:
	  lcd_comm(RSDATA, '7');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '0');
	  break;
    case 71:
	  lcd_comm(RSDATA, '7');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '1');
	  break;
    case 72:
	  lcd_comm(RSDATA, '7');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '2');
	  break;
    case 73:
	  lcd_comm(RSDATA, '7');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '3');
	  break;
    case 74:
	  lcd_comm(RSDATA, '7');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '4');
	  break;
    case 75:
	  lcd_comm(RSDATA, '7');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '5');
	  break;
    case 76:
	  lcd_comm(RSDATA, '7');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '6');
	  break;
    case 77:
	  lcd_comm(RSDATA, '7');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '7');
	  break;
    case 78:
	  lcd_comm(RSDATA, '7');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '8');
	  break;
    case 79:
	  lcd_comm(RSDATA, '7');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '9');
	  break;
    case 80:
	  lcd_comm(RSDATA, '8');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '0');
	  break;
    case 81:
	  lcd_comm(RSDATA, '8');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '1');
	  break;
    case 82:
	  lcd_comm(RSDATA, '8');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '2');
	  break;
    case 83:
	  lcd_comm(RSDATA, '8');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '3');
	  break;
    case 84:
	  lcd_comm(RSDATA, '8');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '4');
	  break;
    case 85:
	  lcd_comm(RSDATA, '8');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '5');
	  break;
    case 86:
	  lcd_comm(RSDATA, '8');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '6');
	  break;
    case 87:
	  lcd_comm(RSDATA, '8');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '7');
	  break;
    case 88:
	  lcd_comm(RSDATA, '8');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '8');
	  break;
    case 89:
	  lcd_comm(RSDATA, '8');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '9');
	  break;
    case 90:
	  lcd_comm(RSDATA, '9');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '0');
	  break;
    case 91:
	  lcd_comm(RSDATA, '9');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '1');
	  break;
    case 92:
	  lcd_comm(RSDATA, '9');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '2');
	  break;
    case 93:
	  lcd_comm(RSDATA, '9');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '3');
	  break;
    case 94:
	  lcd_comm(RSDATA, '9');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '4');
	  break;
    case 95:
	  lcd_comm(RSDATA, '9');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '5');
	  break;
    case 96:
	  lcd_comm(RSDATA, '9');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '6');
	  break;
    case 97:
	  lcd_comm(RSDATA, '9');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '7');
	  break;
    case 98:
	  lcd_comm(RSDATA, '9');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '8');
	  break;
    case 99:
	  lcd_comm(RSDATA, '9');		  // Send Data to LCD.
      wait_busy();	 	  			  // Wait for Busy Flag to Clear
	  lcd_comm(RSDATA, '9');
	  break;
  }
#endif
}

//*****************************************************************************
//*
//* routine: get_numstr
//* Date: 	 January 3, 2004
//* Author:  Ralph Pruitt
//* This routine Shifts the passed string left by one char shortening it by one
//* character.
//*
//*****************************************************************************
char *get_numstr(unsigned char mode_num)
{
   switch (mode_num) {
    case ZERO:
	      strcpy(dig_str, "0");
	  break;
    case ONE:
	      strcpy(dig_str, "1");
	  break;
    case TWO:
	      strcpy(dig_str, "2");
	  break;
    case THREE:
	      strcpy(dig_str, "3");
	  break;
    case FOUR:
	      strcpy(dig_str, "4");
	  break;
    case FIVE:
	      strcpy(dig_str, "5");
	  break;
    case SIX:
	      strcpy(dig_str, "6");
	  break;
    case SEVEN:
	      strcpy(dig_str, "7");
	  break;
    case EIGHT:
	      strcpy(dig_str, "8");
	  break;
    case NINE:
	      strcpy(dig_str, "9");
	  break;
    case PERIOD:
	      strcpy(dig_str, ".");
	  break;
 }
 return(dig_str);

}

//*****************************************************************************
//*
//* routine: cstrncpy2
//* Date: 	 July 21, 2004
//* Author:  Ralph Pruitt
//* This routine performs an selective string copy from a Flash string to a local
//* string.
//*
//*****************************************************************************
char *cstrncpy2(char *s1, const char *s2, size_t n)
{
 	 char  tempstr[18];

	 strcpy(tempstr, s2);
	 strncpy(s1, tempstr, n);

	 return(s1);
}

//*****************************************************************************
//*
//* routine: tst_bat
//* Date: 	 January 4, 2005
//* Author:  Ralph Pruitt
//* This routine tests the Bat_Lvl String and if Bat_Lvl[0] = "*" returns a 1
//* else returns a zero.
//*
//*****************************************************************************
char tst_bat(void)
{
  strcpy(Bat_Lvl, Battery_Test());     // Get Battery Status.....
//  if (Bat_Lvl[0] == 42)
  if (mode != LOW_BAT)
    return(1);
  else
    return(0);
}

//*****************************************************************************
//*
//* routine: update_macro
//* Date: 	 June 15, 2006
//* Author:  Ralph Pruitt
//* This routine updates key vars in structure macro2.
//*
//*****************************************************************************
void update_macro(void)
{
 	switch (macro1.macro_flg)
	{
	  case 2:  //Save Delay Time.
		if (sec_chg > 59) {
		  min_chg++;
		  sec_chg -= 60;
		  if (min_chg > 99)
		    min_chg = 99;
		}
		macro2.mac_entry[macro1.macro_step].delay.minutes = min_chg;
		macro2.mac_entry[macro1.macro_step].delay.seconds = sec_chg;
		break;
	  case 1:  //Save Execution Time.
		if (sec_chg > 59) {
		  min_chg++;
		  sec_chg -= 60;
		  if (min_chg > 99)
		    min_chg = 99;
		}
		macro2.mac_entry[macro1.macro_step].Time.minutes = min_chg;
		macro2.mac_entry[macro1.macro_step].Time.seconds = sec_chg;
		break;
	  case 0:  //Save Protocol Number.
	    if (progwk_num > SWEEP_REND)
	      progwk_num = SWEEP_REND;
		macro2.mac_entry[macro1.macro_step].protocol = progwk_num;
		break;
	}
}

//*****************************************************************************
//*
//* routine: update_sweep
//* Date: 	 July 5, 2005
//* Author:  Ralph Pruitt
//* This routine updates key vars in structure sweep2.
//*
//*****************************************************************************
void update_sweep(void)
{
    if (laser1_disp > 15000)
	  laser1_disp = 15000;				 // Force value to be no greater than 15K.
    //BETAFIX...Note that for this release no less than 100Hz.
//    if (laser1_disp <= 10)
//	  laser1_disp = 10;				 // Force value to be no less than 100.
 	switch (sweep1.sweep_key)
	{
	  case 0:  //Initial Sweep Save.
		sweep2.sweep_low = laser1_disp;	 // Save Sweep Low Item.
		break;
	  case 1:  //Frequency 1 Save.
	  case 2:  //Frequency 2 Save.
	  case 3:  //Frequency 3 Save.
	  case 4:  //Frequency 4 Save.
	  case 5:  //Frequency 5 Save.
	  case 6:  //Frequency 6 Save.
	  case 7:  //Frequency 7 Save.
	  case 8:  //Frequency 8 Save.
	  case 9:  //Frequency 9 Save.
	  case 10:  //Frequency 10 Save.
	  case 11:  //Frequency 11 Save.
	  case 12:  //Frequency 12 Save.
	  case 13:  //Frequency 13 Save.
	  case 14:  //Frequency 14 Save.
	  case 15:  //Frequency 15 Save.
	    sweep2.laser_time[sweep1.sweep_key-1] = laser1_disp;	 // Save Sweep Low Item.
		break;
	  case 16:  //Final Sweep Save.
	    sweep2.sweep_high = laser1_disp;	 // Save Sweep Low Item.
		break;
	}
}

//*****************************************************************************
//*
//* routine: display_sweep
//* Date: 	 July 5, 2005
//* Author:  Ralph Pruitt
//* This routine updates lser1_strng based on the indexed value of sweep2.
//*
//*****************************************************************************
void display_sweep(void)
{
 	switch (sweep1.sweep_key)
	{
	  case 0:  //Initial Sweep Save.
		laser1_disp = sweep2.sweep_low;	 // Save Sweep Low Item.
		break;
	  case 1:  //Frequency 1 Save.
	  case 2:  //Frequency 2 Save.
	  case 3:  //Frequency 3 Save.
	  case 4:  //Frequency 4 Save.
	  case 5:  //Frequency 5 Save.
	  case 6:  //Frequency 6 Save.
	  case 7:  //Frequency 7 Save.
	  case 8:  //Frequency 8 Save.
	  case 9:  //Frequency 9 Save.
	  case 10:  //Frequency 10 Save.
	  case 11:  //Frequency 11 Save.
	  case 12:  //Frequency 12 Save.
	  case 13:  //Frequency 13 Save.
	  case 14:  //Frequency 14 Save.
	  case 15:  //Frequency 15 Save.
	    laser1_disp = sweep2.laser_time[sweep1.sweep_key-1];	 // Save Sweep Low Item.
		break;
	  case 16:  //Final Sweep Save.
	    laser1_disp = sweep2.sweep_high;	 // Save Sweep Low Item.
		break;
	}
    str_chg_long2(lser1_strng, 8, laser1_disp);

}

//*****************************************************************************
//*
//* routine: display_macro
//* Date: 	 June 15, 2006
//* Author:  Ralph Pruitt
//* This routine updates lser1_strng, min_str, and sec_str based on the indexed
//* value of sweep2 according to the following:
//* macro1.macro_step: Points to entry to interogate for information.
//* macro1.macro_flg: Indicates which paramter to return:
//*                   0: Delay.....lser1_strng:0..min_str:delay_min..sec_str:delay_sec
//*					  1: Time......lser1_strng:0..min_str:time_min...sec_str:time_sec
//*					  2: Protocol..lser1_strng:Protocol...min_str:0...sec_str:0
//*
//*****************************************************************************
void display_macro(void)
{
 	switch (macro1.macro_flg)
	{
	  case 2:  //Retrieve Delay Time.
		progwk_num = 0;	 // Save Sweep Low Item.
		min_chg = macro2.mac_entry[macro1.macro_step].delay.minutes;
		sec_chg = macro2.mac_entry[macro1.macro_step].delay.seconds;
		break;
	  case 1:  //Retrieve Execution Time.
		progwk_num = 0;	 // Save Sweep Low Item.
		min_chg = macro2.mac_entry[macro1.macro_step].Time.minutes;
		sec_chg = macro2.mac_entry[macro1.macro_step].Time.seconds;
		break;
	  case 0:  //Retrieve Execution Time.
		progwk_num = macro2.mac_entry[macro1.macro_step].protocol;
		min_chg = 0;
		sec_chg = 0;
		break;
	}
#if sixdigit
    str_chg_ulong(progwk_str, 6, progwk_num, ZEROS);
#else
    str_chg_int(progwk_str, 3, progwk_num, ZEROS);
#endif
    str_chg_char(min_str, 2, min_chg, ZEROS);
#if MARK3SP
    str_chg_char(sec_str, 2, (sec_chg/2), ZEROS);
#else
    str_chg_char(sec_str, 2, sec_chg, ZEROS);
#endif
}

//*****************************************************************************
//*
//* routine: power_up
//* Date: 	 September 30, 2006
//* Updated: January 30, 2015
//* Author:  Ralph Pruitt
//* Description: Enable Power Supply Control Pins P_EN and P_ENP as outputs and
//* assert them in Power-Up Mode.
//*
//*****************************************************************************
void power_up( void )
{
	// Turn off Lasers to ensure no Laser light on Outputs.
	lasers_off();

#ifndef DISABLE_PWR
    PORT9.PDR.BYTE |= 0x03;	    // Set P_EN and P_ENP as output.

	PORT9.PODR.BYTE |= 0x02;		// Assert P_EN (Power up 5V Power Supply/U1).

	// Wait 100 msec for 5V plane to stabilize.
	accurate_delay(100);

	PORT9.PODR.BYTE |= 0x03;		// Assert P_EN (Power up 5V Power Supply/U1).
    								// Assert PENP (Power up VLaser0 and VLaser1/U1).
#endif
}
//*****************************************************************************
//*
//* routine: power_up1
//* Date: 	 September 30, 2006
//* Updated: January 30, 2015
//* Author:  Ralph Pruitt
//* Description: Enable Power Supply Control Pins P_EN and P_ENP as outputs and
//* assert them in Power-Up Mode.
//*
//*****************************************************************************
void power_up1( void )
{
	// Turn off Lasers to ensure no Laser light on Outputs.
	lasers_off();

#ifndef DISABLE_PWR
    PORT9.PDR.BYTE |= 0x03;	    // Set P_EN and P_ENP as output.

	PORT9.PODR.BYTE |= 0x02;		// Assert P_EN (Power up 5V Power Supply/U1).

	// Wait 100 msec for 5V plane to stabilize.
	accurate_delay(100);

	PORT9.PODR.BYTE |= 0x03;		// Assert P_EN (Power up 5V Power Supply/U1).
    								// Assert PENP (Power up VLaser0 and VLaser1/U1).
#endif
}

//*****************************************************************************
//*
//* routine: power_up2
//* Date: 	 September 30, 2006
//* Updated: December 19, 2020
//* Author:  Ralph Pruitt
//* Description: Enable Power Supply Control Pins P_EN and P_ENP as outputs and
//* assert them in Power-Up Mode.
//*
//*****************************************************************************
void power_up2( void )
{
#ifndef DISABLE_PWR
    PORT9.PDR.BYTE |= 0x03;	    // Set P_EN and P_ENP as output.

	PORT9.PODR.BYTE |= 0x02;		// Assert P_EN (Power up 5V Power Supply/U1).

	// Wait 100 msec for 5V plane to stabilize.
	accurate_delay(100);

	PORT9.PODR.BYTE |= 0x03;		// Assert P_EN (Power up 5V Power Supply/U1).
    								// Assert PENP (Power up VLaser0 and VLaser1/U1).
#endif
}

//*****************************************************************************
//*
//* routine: power_dn
//* Date: 	 September 30, 2006
//* Updated: January 30, 2015
//* Author:  Ralph Pruitt
//* Description: Disable Power Supply Control Pins P_EN and P_ENP as outputs and
//* deassert them in Power-dn Mode.
//*
//*****************************************************************************
void power_dn( void )
{
	PORT9.PODR.BYTE &= ~0x03;		// Clear P_EN (Power down 5V Power Supply/U1).
    								// Clear PENP (Power down VLaser0 and VLaser1/U1).

	PORT9.PDR.BYTE &= ~0x03;	    // Set P_EN and P_ENP as input.
}

//*****************************************************************************
//*
//* routine: save_vars
//* Date: 	 December 27, 2003
//* Updated: May 24, 2015
//* Author:  Ralph Pruitt
//* This routine is used to write key vars to EEPROM.
//*
//*****************************************************************************
void save_vars(void)
{
	//	flash_err_t EEPROM_WRITE(uint32_t src_address, uint32_t dest_address, uint32_t num_bytes)

	EEPROM_WRITE((uint32_t)&lser1_time, (uint32_t)&lser1e_time, sizeof(lser1_time));	 // Write the data to EEPROM.
	//EEPROM_WRITE((int)&lser1e_time, lser1_time);	 // Write the data to EEPROM.

	EEPROM_WRITE((uint32_t)&lser2S_time, (uint32_t)&lser2se_time, sizeof(lser2S_time));	 // Write the data to EEPROM.
	//EEPROM_WRITE((int)&lser2e_time, lser2_time);	 // Write the data to EEPROM.

	EEPROM_WRITE((uint32_t)&lser2_time, (uint32_t)&lser2e_time, sizeof(lser2_time));	 // Write the data to EEPROM.
	//EEPROM_WRITE((int)&lser2e_time, lser2_time);	 // Write the data to EEPROM.

	EEPROM_WRITE((uint32_t)&lser3_time, (uint32_t)&lser3e_time, sizeof(lser3_time));	 // Write the data to EEPROM.
	//EEPROM_WRITE((int)&lser3e_time, lser3_time);	 // Write the data to EEPROM.
	WDR(); //this prevents a timout on enabling

	EEPROM_WRITE((uint32_t)&lser4_time, (uint32_t)&lser4e_time, sizeof(lser4_time));	 // Write the data to EEPROM.
	//EEPROM_WRITE((int)&lser4e_time, lser4_time);	 // Write the data to EEPROM.

	EEPROM_WRITE((uint32_t)&opmin_cnt, (uint32_t)&eopmin_cnt, sizeof(opmin_cnt));	 // Write the data to EEPROM.
	//EEPROM_WRITE((int)&eopmin_cnt, opmin_cnt);	 		 // Write the data to EEPROM.

	EEPROM_WRITE((uint32_t)&prog_num, (uint32_t)&eprog_num, sizeof(prog_num));	 // Write the data to EEPROM.
	//EEPROM_WRITE((int)&eprog_num, prog_num);	  	 // Write the data to EEPROM.

	EEPROM_WRITE((uint32_t)&stimer_low, (uint32_t)&etimer_low, sizeof(stimer_low));	 // Write the data to EEPROM.
	//EEPROM_WRITE((int)&etimer_low, stimer_low);	 // Write the data to EEPROM.

	EEPROM_WRITE((uint32_t)&sprescale, (uint32_t)&eprescale, sizeof(sprescale));	 // Write the data to EEPROM.
	//EEPROM_WRITE((int)&eprescale, sprescale);	 	 // Write the data to EEPROM.
	WDR(); //this prevents a timout on enabling

	EEPROM_WRITE((uint32_t)&stimer_low2, (uint32_t)&etimer_low2, sizeof(stimer_low2));	 // Write the data to EEPROM.
	//EEPROM_WRITE((int)&etimer_low2, stimer_low2);	 // Write the data to EEPROM.

	EEPROM_WRITE((uint32_t)&sprescale2, (uint32_t)&eprescale2, sizeof(sprescale2));	 // Write the data to EEPROM.
	//EEPROM_WRITE((int)&eprescale2, sprescale2);	 	 // Write the data to EEPROM.
	WDR(); //this prevents a timout on enabling

	EEPROM_WRITE((uint32_t)&mode, (uint32_t)&emode, sizeof(mode));	 // Write the data to EEPROM.
	//EEPROM_WRITE((int)&emode, mode);	 	 		 // Write the data to EEPROM.

	EEPROM_WRITE((uint32_t)&sm, (uint32_t)&esm, sizeof(sm));	 // Write the data to EEPROM.
	//EEPROM_WRITE((int)&esm, sm);	 	 		 	 // Write the data to EEPROM.
	WDR(); //this prevents a timout on enabling

	// Write Lease/Demo Vars
	EEPROM_WRITE((uint32_t)&opMode, (uint32_t)&eopMode, sizeof(opMode));	 			// Write opMode to Flash.
	EEPROM_WRITE((uint32_t)&leaseDays, (uint32_t)&eleaseDays, sizeof(leaseDays));	 	// Write leaseDays to Flash.
	EEPROM_WRITE((uint32_t)&leaseDay, (uint32_t)&eleaseDay, sizeof(leaseDay));	 		// Write leaseDay to Flash.
	EEPROM_WRITE((uint32_t)&leaseMnth, (uint32_t)&eleaseMnth, sizeof(leaseMnth));	 	// Write leaseMnth to Flash.
	EEPROM_WRITE((uint32_t)&leaseYear, (uint32_t)&eleaseYear, sizeof(leaseYear));	 	// Write leaseYear to Flash.
	WDR(); //this prevents a timout on enabling

	if (tmr_update_flg == 0) {

		EEPROM_WRITE((uint32_t)&tmr_min, (uint32_t)&etmr_min, sizeof(tmr_min));	 // Write the data to EEPROM.
		//EEPROM_WRITE((int)&etmr_min, tmr_min);	  	 // Write the data to EEPROM.

		EEPROM_WRITE((uint32_t)&tmr_sec, (uint32_t)&etmr_sec, sizeof(tmr_sec));	 // Write the data to EEPROM.
		//EEPROM_WRITE((int)&etmr_sec, tmr_sec);	  	 // Write the data to EEPROM.
	}
	if (tmr_update_flg == 2)
		tmr_update_flg = 0;  						 // If Armed, Deactivate Update Flag.
	if (cnt_dwn_flg == 2)
		cnt_dwn_flg = 0;  							 // If Armed, Deactivate Timer Flag.
}

//*****************************************************************************
//*
//* routine: restore_vars
//* Date: 	 December 27, 2003
//* Updated: May 24, 2015
//* Author:  Ralph Pruitt
//* This routine is used to retrieve key vars from EEPROM.
//*
//*****************************************************************************
void restore_vars(void)
{
	lser1_time = lser1e_time;
	//EEPROM_READ((int)&lser1e_time, lser1_time);	 // Read the data to EEPROM.

	lser2S_time = lser2se_time;
	//EEPROM_READ((int)&lser2se_time, lser2S_time);	 // Read the data to EEPROM.

	lser2_time = lser2e_time;
	//EEPROM_READ((int)&lser2e_time, lser2_time);	 // Read the data to EEPROM.

	lser3_time = lser3e_time;
	//EEPROM_READ((int)&lser3e_time, lser3_time);	 // Read the data to EEPROM.
	WDR(); //this prevents a timout on enabling

	lser4_time = lser4e_time;
	//EEPROM_READ((int)&lser4e_time, lser4_time);	 // Read the data to EEPROM.

	prog_num = eprog_num;
	//EEPROM_READ((int)&eprog_num, prog_num);	  	 // Read the data from EEPROM.

	stimer_low = etimer_low;
  	//EEPROM_READ((int)&etimer_low, stimer_low);	 // Read the data to EEPROM.

	sprescale = eprescale;
  	//EEPROM_READ((int)&eprescale, sprescale);	 	 // Read the data to EEPROM.
  	WDR(); //this prevents a timout on enabling

  	stimer_low2 = etimer_low2;
  	//EEPROM_READ((int)&etimer_low2, stimer_low2);	 // Read the data to EEPROM.

  	sprescale2 = eprescale2;
  	//EEPROM_READ((int)&eprescale2, sprescale2);	 // Read the data to EEPROM.
  	WDR(); //this prevents a timout on enabling

  	mode = emode;
  	//EEPROM_READ((int)&emode, mode);	 	 		 // Read the data from EEPROM.

  	sm = esm;
  	//EEPROM_READ((int)&esm, sm);	 	 		 	 // Read the data from EEPROM.
  	WDR(); //this prevents a timout on enabling

	// Read Lease/Demo Vars
	opMode = eopMode;					 			// Write opMode to Flash.
	leaseDays = eleaseDays;						 	// Write leaseDays to Flash.
	leaseDay = eleaseDay;					 		// Write leaseDay to Flash.
	leaseMnth = eleaseMnth;						 	// Write leaseMnth to Flash.
	leaseYear = eleaseYear;	 						// Write leaseYear to Flash.
	WDR(); 											//this prevents a timeout on enabling

//  if ((cnt_dwn_flg == 0) && (tmr_update_flg == 0)) {
  	if (cnt_dwn_flg == 0)
  	{

  		tmr_min = etmr_min;
  		//EEPROM_READ((int)&etmr_min, tmr_min);	  	 	 // Read the data from EEPROM.

  		tmr_sec = etmr_sec;
  		//EEPROM_READ((int)&etmr_sec, tmr_sec);	  	 	 // Read the data from EEPROM.
  	}
}

//*****************************************************************************
//*
//* routine: p5_sec_start
//* Date: 	 February 27, 2004
//* Author:  Ralph Pruitt
//* This routine starts or restarts the 0.5 second timer.
//*
//*****************************************************************************
void p5_sec_start(void)
{
  p5_second = 1;			// Initialize 0.5 Second Timer.
  ticker = 0;  				// Sync Timer for countdown.
}

//*****************************************************************************
//*
//* routine: p5_sec_clear
//* Date: 	 February 27, 2004
//* Author:  Ralph Pruitt
//* This routine clears the 0.5 second timer.
//*
//*****************************************************************************
void p5_sec_clear(void)
{
  p5_second = 0;			// Clear the Two Second Timer.
}

//*****************************************************************************
//*
//* routine: p5_sec_test
//* Date: 	 February 27, 2004
//* Author:  Ralph Pruitt
//* This routine tests the 0.5 second timer and returns status.
//*
//* Returns:
//*				1:		Timer still Active.
//*			    0:      Timer Clear.
//*
//*****************************************************************************
unsigned char p5_sec_test(void)
{
  if (p5_second > 0)
    return(1);
  else
	return(0);
}

//*****************************************************************************
//*
//* routine: two_sec_start
//* Date: 	 January 1, 2004
//* Author:  Ralph Pruitt
//* This routine starts or restarts the two second timer.
//*
//*****************************************************************************
void two_sec_start(void)
{
  two_second = 4;			// Initialize Two Second Timer.
  ticker = 0;  				// Sync Timer for countdown.
}

//*****************************************************************************
//*
//* routine: two_sec_clear
//* Date: 	 January 1, 2004
//* Author:  Ralph Pruitt
//* This routine clears the two second timer.
//*
//*****************************************************************************
void two_sec_clear(void)
{
  two_second = 0;			// Clear the Two Second Timer.
}

//*****************************************************************************
//*
//* routine: two_sec_test
//* Date: 	 January 1, 2004
//* Author:  Ralph Pruitt
//* This routine tests the two second timer and returns status.
//*
//* Returns:
//*				1:		Timer still Active.
//*			    0:      Timer Clear.
//*
//*****************************************************************************
unsigned char two_sec_test(void)
{
  if (two_second > 0)
    return(1);
  else
	return(0);
}

//*****************************************************************************
//*
//* routine: five_sec_start
//* Date: 	 January 1, 2004
//* Author:  Ralph Pruitt
//* This routine starts or restarts the five second timer.
//*
//*****************************************************************************
void five_sec_start(void)
{
  five_second = 10;			// Initialize five Second Timer.
  ticker = 0;  				// Sync Timer for countdown.
}

//*****************************************************************************
//*
//* routine: five_sec_clear
//* Date: 	 January 1, 2004
//* Author:  Ralph Pruitt
//* This routine clears the five second timer.
//*
//*****************************************************************************
void five_sec_clear(void)
{
  five_second = 0;			// Clear the five Second Timer.
}

//*****************************************************************************
//*
//* routine: five_sec_test
//* Date: 	 January 1, 2004
//* Author:  Ralph Pruitt
//* This routine tests the five second timer and returns status.
//*
//* Returns:
//*				1:		Timer still Active.
//*			    0:      Timer Clear.
//*
//*****************************************************************************
unsigned char five_sec_test(void)
{
  if (five_second > 0)
    return(1);
  else
	return(0);
}

//*****************************************************************************
//*
//* routine: two_min_start
//* Date: 	 January 1, 2004
//* Author:  Ralph Pruitt
//* This routine starts or restarts the two minute timer.
//*
//*****************************************************************************
void two_min_start(void)
{
  two_minute = 240;			// Initialize two minute Timer.
  ticker = 0;  				// Sync Timer for countdown.
}

//*****************************************************************************
//*
//* routine: two_min_clear
//* Date: 	 January 1, 2004
//* Author:  Ralph Pruitt
//* This routine clears the two minute timer.
//*
//*****************************************************************************
void two_min_clear(void)
{
  two_minute = 0;			// Clear the two minute Timer.
}

//*****************************************************************************
//*
//* routine: two_min_test
//* Date: 	 January 1, 2004
//* Author:  Ralph Pruitt
//* This routine tests the two minute timer and returns status.
//*
//* Returns:
//*				1:		Timer still Active.
//*			    0:      Timer Clear.
//*
//*****************************************************************************
unsigned char two_min_test(void)
{
  if (two_minute > 0)
    return(1);
  else
	return(0);
}

//*****************************************************************************
//*
//* routine: five_min_start
//* Date: 	 January 1, 2004
//* Author:  Ralph Pruitt
//* This routine starts or restarts the five minute timer.
//*
//*****************************************************************************
void five_min_start(void)
{
  five_minute = 600;		// Initialize five minute Timer.
  ticker = 0;  				// Sync Timer for countdown.
}

//*****************************************************************************
//*
//* routine: five_min_clear
//* Date: 	 January 1, 2004
//* Author:  Ralph Pruitt
//* This routine clears the five minute timer.
//*
//*****************************************************************************
void five_min_clear(void)
{
  five_minute = 0;			// Clear the five minute Timer.
}

//*****************************************************************************
//*
//* routine: five_min_test
//* Date: 	 January 1, 2004
//* Author:  Ralph Pruitt
//* This routine tests the five minute timer and returns status.
//*
//* Returns:
//*				1:		Timer still Active.
//*			    0:      Timer Clear.
//*
//*****************************************************************************
unsigned char five_min_test(void)
{
  if (five_minute > 0)
    return(1);
  else
	return(0);
}

//*****************************************************************************
//*
//* routine: getTime
//* Date: 	 May 23, 2015
//* Author:  Ralph Pruitt
//* This routine retrieves the time as three referenced parameters.
//*
//* Paramters:
//*			int* hour:		RTC Hour
//*			int* minute:	RTC minute
//*			int* second:	RTC second
//*
//* Returns:
//*			int* hour:		RTC Hour
//*			int* minute:	RTC minute
//*			int* second:	RTC second
//*
//*****************************************************************************
void getTime(int* hour, int* minute, int* second)
{
	rtc_calendarcounter_value_t Time_value;

	// Get Time Value.
	R_RTC_Get_CalendarCounterValue(&Time_value);

	*hour = ((Time_value.rhrcnt & 0xf0)/16) * 10 + (Time_value.rhrcnt & 0x0f);
	*minute = ((Time_value.rmincnt & 0xf0)/16) * 10 + (Time_value.rmincnt & 0x0f);
	*second = ((Time_value.rseccnt & 0xf0)/16) * 10 + (Time_value.rseccnt & 0x0f);
}

//*****************************************************************************
//* routine: getDate
//* Date: 	 May 23, 2015
//* Author:  Ralph Pruitt
//* This routine retrieves the date as three referenced parameters.
//*
//* Paramters:
//*			int* month:		RTC Month
//*			int* day:		RTC Day
//*			int* year:		RTC Year
//*
//* Returns:
//*			int* month:		RTC Month
//*			int* day:		RTC Day
//*			int* year:		RTC Year
//*
//*****************************************************************************
void getDate(int* month, int* day, int* year)
{
	rtc_calendarcounter_value_t Time_value;

	// Get Time Value.
	R_RTC_Get_CalendarCounterValue(&Time_value);

	*month = ((Time_value.rmoncnt & 0xf0)/16) * 10 + (Time_value.rmoncnt & 0x0f);
	*day = ((Time_value.rdaycnt & 0xf0)/16) * 10 + (Time_value.rdaycnt & 0x0f);
	*year = ((Time_value.ryrcnt & 0xf0)/16) * 10 + (Time_value.ryrcnt & 0x0f) + 2000;
}

//*****************************************************************************
//*
//* routine: calcPBF
//* Date: 	 May 24, 2015
//* Author:  Ralph Pruitt
//* This routine calculates the PBF factor based on the date(month, day, year) and the SN. It then
//* returns this code as an unsigned long value.
//*
//* Paramters:
//*
//* Returns:
//*			unsigned long:	the PBF factor based on the current date and SN
//*
//*****************************************************************************
unsigned long calcPBF( void )
{
	unsigned long result;
	int month, day, year;

	// Get Date and SN.
	getDate( &month, &day, &year);
	serial_number = eserial_number;

	// Calculate the PBF
	result = serial_number + (month * day * year);
	result = result ^ FACTOR1;
	result += FACTOR2;
	result = result ^ FACTOR3;

	// Strip to least significant 8 digits.
	result = result % 100000000;
	return result;
}

//*****************************************************************************
//* routine: decodePBFcode
//* Date: 	 May 25, 2015
//* Author:  Ralph Pruitt
//* This routine decodes the passed PBF code and verifies if it is a good code.
//* If it is a good code, it then decodes the LeaseDays and Mode variable and
//* returns those. This routine returns a 1 if the result is good else returns a
//* zero
//*
//* Paramters:
//*			char* parm1:		12 Digit string containing the PBF code to be tested.
//*			int* leaseDays:		Pointer to variable to be set with # of lease days.
//*			int* Mode:			Pointer to variable to be set with Mode.
//*
//* Returns:
//*			int 	0:		Bad PBF Code
//*					1:		Good PBF Code
//*****************************************************************************
int decodePBFcode( char* parm1, int* leaseDays, int* Mode)
{
	char tempstr[12];
	char tempstr2[12];
	int x;
	unsigned long tempResult;
	unsigned long passedPBF;

	// Test length of string first.
	if (strlen(parm1) == 12)
	{
		// Length of string is correct. Extract first 8 chars as PBF Code to test.
		strncpy(tempstr, parm1, 8);

		// Convert string to number value
		passedPBF = atol(tempstr);

		// Test passed PBF with true PBF
		if (passedPBF == calcPBF())
		{

			// 1. Extract last 4 digits for Mode and leaseDays
			for (x=0; x<4; x++)
				tempstr2[x] = parm1[x+8];

			// 2. Exclusive Or with passed PBF
			tempResult = atol(tempstr2);
			tempResult = tempResult ^ (passedPBF & 0x3ff);

			// Strip out Mode
			*Mode = (int)tempResult % 10;

			// Strip out leaseDays.
			*leaseDays = ((int)tempResult - *Mode)/10;

			// Good result. Return 1.
			return 1;

		}
		else
			// PBF does not match. return null
			return 0;
	}
	else
		// Length wrong. return null
		return 0;
}

//*****************************************************************************
//* routine: NumDaysOrigin
//* Date: 	 May 25, 2015
//* Author:  Ralph Pruitt
//* This routine calculates the number of days since origin for the passed date.
//* Note that origin is considered to be Jan 1, 2000.
//*
//* Paramters:
//*			 int month:			Month of date to be calculated.
//*          int day:			Day of month for date to be calculated.
//*          int year:			Year of date to be calculated.
//*
//* Returns:
//*			int 	Number of days since origin
//*					-1:		Bad date
//*****************************************************************************
int NumDaysOrigin( int month, int day, int year )
{
	const int months[] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
	int NumDays;

	// Validate parameters
	if((month>0) && (month<=12))
	{
		// Valid Month
		if((day>0) && (day<=31))
		{
			// Valid Day
			if((year>=2000) && (year<=2100))
			{
				// Valid Parameters. Calculate Days since Origin. Jan 1, 2000
				NumDays = (year-2000) * 365;
				NumDays += months[month];
				NumDays += day;

				// Return Result
				return NumDays;
			}
			else
			{
				// Invalid Year. Return -1
				return -1;
			}
		}
		else
		{
			// Invalid Day. Return -1
			return -1;
		}
	}
	else
	{
		// Invalid Month. Return -1
		return -1;
	}
}

//*****************************************************************************
//* routine: CalcLeaseDays
//* Date: 	 May 25, 2015
//* Author:  Ralph Pruitt
//* This routine Calculates the number of days since the last target stored date
//* for lease.
//*
//* Paramters:
//*          None
//*
//* Returns:
//*			int 	Number of days since Lease Date.
//*****************************************************************************
int CalcLeaseDays( void )
{
	int NumDays;
	int month, day, year;
	int numLeaseDays;
	int numDaysOrigin;

	// Get Current Date
	getDate( &month, &day, &year);

	// Calculate the number of days since origin.
	numDaysOrigin = NumDaysOrigin(month, day, year);

	// Caculate the number of Lease Days since origin.
	numLeaseDays = NumDaysOrigin(leaseMnth, leaseDay, leaseYear);

	// Calculate the number of Days before lease will expire.
	NumDays = (numLeaseDays + eleaseDays) - numDaysOrigin;
	if(NumDays <= 0)
		return -1;
	else
		return NumDays;
}

char* getTimeStr( void )
{
	int hour, minute, second;
	rtc_calendarcounter_value_t Time_value;

//	int errCode;
	static char tempstr[80];
	// Get Time Value.
	R_RTC_Get_CalendarCounterValue(&Time_value);

	hour = ((Time_value.rhrcnt & 0xf0)/16) * 10 + (Time_value.rhrcnt & 0x0f);
	minute = ((Time_value.rmincnt & 0xf0)/16) * 10 + (Time_value.rmincnt & 0x0f);
	second = ((Time_value.rseccnt & 0xf0)/16) * 10 + (Time_value.rseccnt & 0x0f);

	sprintf(tempstr,"%02d:%02d:%02d",
			hour,
			minute,
			second);

	return tempstr;
}

char* getDateStr( void )
{
	int month, day, year;
	rtc_calendarcounter_value_t Time_value;

//	int errCode;
	static char tempstr[80];
	// Get Time Value.
	R_RTC_Get_CalendarCounterValue(&Time_value);

	month = ((Time_value.rmoncnt & 0xf0)/16) * 10 + (Time_value.rmoncnt & 0x0f);
	day = ((Time_value.rdaycnt & 0xf0)/16) * 10 + (Time_value.rdaycnt & 0x0f);
	year = ((Time_value.ryrcnt & 0xf0)/16) * 10 + (Time_value.ryrcnt & 0x0f) + 2000;

	sprintf(tempstr,"%02d/%02d/%04d",
			month,
			day,
			year);

	return tempstr;
}

void Miscmonitor( char* parm1)
{
	uint16_t result;
	int hour, minute, second, month, day, year;
	rtc_calendarcounter_value_t Time_value;
	unsigned long PBF_value;

//	int errCode;
	char tempstr[80];

	if( strcmp(parm1, "Bat") == 0)
	{
		  // 1. Start A/D Channel
		  R_S12AD0_Start();

		  // 1a. Delay to allow channel to stabilize. (10 msec)
		  accurate_delay(10);

		  // 2. Read ADCHANNEL0 and place in value1.
		  R_S12AD0_Get_ValueResult(ADCHANNEL0, &result);

		  // 3. Power Down ADC.
		  R_S12AD0_Stop();
		  printf2("*****************************************\n");
		  sprintf(tempstr,"Battery Level: %d\n", result);
		  printf2(tempstr);
	}
	else 	if( strcmp(parm1, "Version") == 0)
	{
		  sprintf(tempstr,"%s\n", (const char*)VERSIONSTR);
		  printf2(tempstr);
	}
	else if( strcmp(parm1, "Time") == 0)
	{
		// Get Time Value.
		R_RTC_Get_CalendarCounterValue(&Time_value);

		hour = ((Time_value.rhrcnt & 0xf0)/16) * 10 + (Time_value.rhrcnt & 0x0f);
		minute = ((Time_value.rmincnt & 0xf0)/16) * 10 + (Time_value.rmincnt & 0x0f);
		second = ((Time_value.rseccnt & 0xf0)/16) * 10 + (Time_value.rseccnt & 0x0f);
		month = ((Time_value.rmoncnt & 0xf0)/16) * 10 + (Time_value.rmoncnt & 0x0f);
		day = ((Time_value.rdaycnt & 0xf0)/16) * 10 + (Time_value.rdaycnt & 0x0f);
		year = ((Time_value.ryrcnt & 0xf0)/16) * 10 + (Time_value.ryrcnt & 0x0f) + 2000;

		printf2("*****************************************\n");
		sprintf(tempstr,"Time: %d:%d:%d\n",
				hour,
				minute,
				second);
		printf2(tempstr);
		sprintf(tempstr,"Date: %d/%d/%d\n",
				month,
				day,
				year);
		printf2(tempstr);
	}
	else if( strcmp(parm1, "PBF") == 0)
	{
		// Get Date Value.
		getDate(&month, &day, &year);

		// get PBF Value.
		PBF_value = calcPBF();

		printf2("*****************************************\n");
		sprintf(tempstr,"Date: %d/%d/%d\n",
				month,
				day,
				year);
		printf2(tempstr);

		sprintf(tempstr,"SN: %d\n", serial_number);
		printf2(tempstr);

		sprintf(tempstr,"PBF Code: %d\n", PBF_value);
		printf2(tempstr);
	}
	else if( strcmp(parm1, "SN") == 0)
	{
		printf2("*****************************************\n");
		sprintf(tempstr,"Serial Number: %09d\n", serial_number);
		printf2(tempstr);
	}
	else if( strcmp(parm1, "Mode") == 0)
	{
		printf2("*****************************************\n");
		sprintf(tempstr,"Mode: %02d\n", opMode);
		printf2(tempstr);
	}
	else if( strcmp(parm1, "LDay") == 0)
	{
		printf2("*****************************************\n");
		sprintf(tempstr,"Number Lease Days: %03d\n", leaseDays);
		printf2(tempstr);

		sprintf(tempstr,"Lease Date Start: %02d/%02d/%04d\n",
				leaseMnth,
				leaseDay,
				leaseYear);
		printf2(tempstr);
	}
	else if( strcmp(parm1, "NumLDay") == 0)
	{
		printf2("*****************************************\n");
		sprintf(tempstr,"Number Lease Days: %03d\n", leaseDays);
		printf2(tempstr);

		sprintf(tempstr,"Lease Date Start: %02d/%02d/%04d\n",
				leaseMnth,
				leaseDay,
				leaseYear);
		printf2(tempstr);

		sprintf(tempstr,"Days Left on Lease: %03d\n", CalcLeaseDays());
		printf2(tempstr);
	}
	else
	{
	      printf2("ILLEGAL Misc Parameter!!\n");
	}
	printf2("\n\n");
}

void SetTimemonitor( char* parm1)
{
	int hour, minute, second, month, day, year;
	rtc_calendarcounter_value_t Time_value;

//	int errCode;
	char tempstr[80];

	// Test Prameter and see if we have three values.
	if (sscanf(parm1,"%d:%d:%d", &hour, &minute, &second) == 3)
	{
		// 1. Get Time Value.
		R_RTC_Get_CalendarCounterValue(&Time_value);

		// 2. Set Structure for Time
		Time_value.rhrcnt = (hour % 10) + ((hour - (hour % 10))/10)*16;
		Time_value.rmincnt = (minute % 10) + ((minute - (minute % 10))/10)*16;
		Time_value.rseccnt = (second % 10) + ((second - (second % 10))/10)*16;

		// 3. Update and restart RTC
		R_RTC_Restart(Time_value);

		// 4. Now show updated Time.
		R_RTC_Get_CalendarCounterValue(&Time_value);

		hour = ((Time_value.rhrcnt & 0xf0)/16) * 10 + (Time_value.rhrcnt & 0x0f);
		minute = ((Time_value.rmincnt & 0xf0)/16) * 10 + (Time_value.rmincnt & 0x0f);
		second = ((Time_value.rseccnt & 0xf0)/16) * 10 + (Time_value.rseccnt & 0x0f);
		month = ((Time_value.rmoncnt & 0xf0)/16) * 10 + (Time_value.rmoncnt & 0x0f);
		day = ((Time_value.rdaycnt & 0xf0)/16) * 10 + (Time_value.rdaycnt & 0x0f);
		year = ((Time_value.ryrcnt & 0xf0)/16) * 10 + (Time_value.ryrcnt & 0x0f) + 2000;

		printf2("*****************************************\n");
		sprintf(tempstr,"Updated Time: %d:%d:%d\n",
				hour,
				minute,
				second);
		printf2(tempstr);
		sprintf(tempstr,"Date: %d/%d/%d\n",
				month,
				day,
				year);
		printf2(tempstr);
	}
	else
	{
	      printf2("ILLEGAL setTime Parameter!!\n");
	}
	printf2("\n\n");
}

void SetTimer( char* parm1)
{
	int minute, second;

	char tempstr[80];

	// Test Prameter and see if we have three values.
	if (sscanf(parm1,"%d:%d", &minute, &second) == 2)
	{
		// Verify Legal Values
		if ((minute>99) || (minute<0))
		{
			printf2("Illegal Value for Minutes passed!\r\n");
		}
		else if ((second>59) || (second<0))
		{
			printf2("Illegal Value for Seconds passed!\r\n");
		}
		else
		{
			tmr_min = minute;		// Build new tmr_min.
			tmr_sec = second;		// Build new tmr_min.
			save_vars();  	 	  	// Save Updated Variables.
			sprintf(tempstr,"Updated Timer:%d:%d\n",
					minute,
					second);
			printf2(tempstr);
			// Reset back to main.
			if ( Booted )
			{
				ModeMonitor( "Main");
			}
		}
	}
	else
	{
	      printf2("ILLEGAL TimerSet Parameter!!\n");
	}
	printf2("\n\n");
}

void SetProgram( char* parm1)
{
	int Prgram;

	char tempstr[80];

	// Test Prameter and see if we have three values.
	if (sscanf(parm1,"%d", &Prgram) == 1)
	{
		// Verify Legal Values
		if ((Prgram>999) || (Prgram<0))
		{
			printf2("Illegal Value for Program Value passed!\r\n");
		}
		else
		{
		    if (opMode == 3)			// Legacy is only active.
		    {
			    if ((Prgram > CUSTOM4_REND) && (Prgram <= CUSTOM4_END))
			    	Prgram = CUSTOM4_REND;
		    }
		    else
		    {
		    	prog_num = Prgram;
		    	if ((Prgram > CUSTOM_REND) && (Prgram <= CUSTOM_END))
		    		Prgram = CUSTOM_REND;
		    	else if ((Prgram > CUSTOM2_REND) && (Prgram <= CUSTOM2_END))
		    		Prgram = CUSTOM2_REND;
		    	else if ((Prgram > CUSTOM3_REND) && (Prgram <= CUSTOM3_END))
		    		Prgram = CUSTOM3_REND;
		    	else if ((Prgram > CUSTOM4_REND) && (Prgram <= CUSTOM4_END))
		    		Prgram = CUSTOM4_REND;
		    }

			save_vars();  	 	  	// Save Updated Variables.
			sprintf(tempstr,"Updated Program:%d\n",
					Prgram);
			printf2(tempstr);
			// Reset back to main.
			if ( Booted )
			{
				ModeMonitor( "Main");
			}
		}
	}
	else
	{
	      printf2("ILLEGAL SetPGM Parameter!!\n");
	}
	printf2("\n\n");
}

void SetDatemonitor( char* parm1)
{
	int hour, minute, second, month, day, year;
	rtc_calendarcounter_value_t Time_value;

//	int errCode;
	char tempstr[80];

	// Test Prameter and see if we have three values.
	if (sscanf(parm1,"%d/%d/%d", &month, &day, &year) == 3)
	{
		// 1. Get Time Value.
		R_RTC_Get_CalendarCounterValue(&Time_value);

		// 2. Set Structure for Time
		Time_value.rmoncnt = (month % 10) + ((month - (month % 10))/10)*16;
		Time_value.rdaycnt = (day % 10) + ((day - (day % 10))/10)*16;
		year = year-2000;
		Time_value.ryrcnt = (year % 10) + ((year - (year % 10))/10)*16;

		// 3. Update and restart RTC
		R_RTC_Restart(Time_value);

		// 4. Now show updated Time.
		R_RTC_Get_CalendarCounterValue(&Time_value);

		hour = ((Time_value.rhrcnt & 0xf0)/16) * 10 + (Time_value.rhrcnt & 0x0f);
		minute = ((Time_value.rmincnt & 0xf0)/16) * 10 + (Time_value.rmincnt & 0x0f);
		second = ((Time_value.rseccnt & 0xf0)/16) * 10 + (Time_value.rseccnt & 0x0f);
		month = ((Time_value.rmoncnt & 0xf0)/16) * 10 + (Time_value.rmoncnt & 0x0f);
		day = ((Time_value.rdaycnt & 0xf0)/16) * 10 + (Time_value.rdaycnt & 0x0f);
		year = ((Time_value.ryrcnt & 0xf0)/16) * 10 + (Time_value.ryrcnt & 0x0f) + 2000;

		printf2("*****************************************\n");
		sprintf(tempstr,"Updated Time: %d:%d:%d\n",
				hour,
				minute,
				second);
		printf2(tempstr);
		sprintf(tempstr,"Date: %d/%d/%d\n",
				month,
				day,
				year);
		printf2(tempstr);
	}
	else
	{
	      printf2("ILLEGAL setDate Parameter!!\n");
	}
	printf2("\n\n");
}

void SetSNmonitor( char* parm1)
{
	char tempstr[80];

	// Convert string to serial_number.
	serial_number = atol( parm1 );

	// Save new value to Data Flash.
	EEPROM_WRITE((uint32_t)&serial_number, (uint32_t)&eserial_number, sizeof(serial_number));	 		 // Write the data to EEPROM.

	// Show new Value.
	printf2("*****************************************\n");
	sprintf(tempstr,"New Serial Number: %09d\n", serial_number);
	printf2(tempstr);

	printf2("\n\n");
}

void SetModeMonitor( char* parm1)
{
	char tempstr[80];
	int  tmpMode;

	// Convert string to serial_number.
	tmpMode = atoi( parm1 );

	if (( tmpMode <= 3) && ( tmpMode >= 0 ))
	{
		opMode = tmpMode;

		// Save new value to Data Flash.
		EEPROM_WRITE((uint32_t)&opMode, (uint32_t)&eopMode, sizeof(opMode));	 		 // Write the data to EEPROM.

		// Show new Value.
		printf2("*****************************************\n");
		sprintf(tempstr,"New Operation Mode: %02d\n", opMode);
		printf2(tempstr);
	}
	else
	{
	      printf2("ILLEGAL setMode Parameter!!\n");
	}

	printf2("\n\n");
}

void SetLDayMonitor( char* parm1)
{
	char tempstr[80];
	int  tmpLDay;

	// Convert string to serial_number.
	tmpLDay = atoi( parm1 );

	if (( tmpLDay <= 90) && ( tmpLDay >= 0 ))
	{
		leaseDays = tmpLDay;
		// Get Date Value.
		getDate(&leaseMnth, &leaseDay, &leaseYear);

		// Save new values to Data Flash.
		EEPROM_WRITE((uint32_t)&leaseDays, (uint32_t)&eleaseDays, sizeof(leaseDays));	 // Write the data to EEPROM.
		EEPROM_WRITE((uint32_t)&leaseMnth, (uint32_t)&eleaseMnth, sizeof(leaseMnth));	 // Write the data to EEPROM.
		EEPROM_WRITE((uint32_t)&leaseDay, (uint32_t)&eleaseDay, sizeof(leaseDay));	 	 // Write the data to EEPROM.
		EEPROM_WRITE((uint32_t)&leaseYear, (uint32_t)&eleaseYear, sizeof(leaseYear));	 // Write the data to EEPROM.

		// Show new Value.
		printf2("*****************************************\n");
		sprintf(tempstr,"Updated Number Lease Days: %03d\n", leaseDays);
		printf2(tempstr);

		sprintf(tempstr,"Updated Lease Date Start: %02d/%02d/%04d\n",
				leaseMnth,
				leaseDay,
				leaseYear);
		printf2(tempstr);
	}
	else
	{
	      printf2("ILLEGAL setLDay Parameter!!\n");
	}

	printf2("\n\n");
}

void testPBFmonitor( char* parm1)
{
	char tempstr[80];
	int  tmpleaseDays;
	int  tmpMode;

	// Test string and determine if it is a good PBF.
	if (decodePBFcode( parm1, &tmpleaseDays, &tmpMode))
	{
		// Show new Value.
		printf2("*****************************************\n");
		sprintf(tempstr,"PBF %s is GOOD!\n", parm1);
		printf2(tempstr);

		sprintf(tempstr,"Lease Days: %03d\n", tmpleaseDays);
		printf2(tempstr);
		sprintf(tempstr,"Mode: %1d\n", tmpMode);
		printf2(tempstr);
	}
	else
	{
	      printf2("ILLEGAL/Bad PBF Parameter!!\n");
	}

	printf2("\n\n");
}

void TestOriginmonitor( char* parm1)
{
	int month, day, year, NumDays;

	char tempstr[80];

	// Test Parmeter and see if we have three values.
	if (sscanf(parm1,"%d/%d/%d", &month, &day, &year) == 3)
	{
		// Calc Num Days
		NumDays = NumDaysOrigin( month, day, year);
		// Validate result
		if(NumDays >= 0)
		{
			printf2("*****************************************\n");
			sprintf(tempstr,"Target Date: %d/%d/%d\n",
					month,
					day,
					year);
			printf2(tempstr);

			sprintf(tempstr,"Number Days Since Origin: %d\n", NumDays);
			printf2(tempstr);
		}
		else
		{
		      printf2("ILLEGAL TestOrigin Parameters!!\n");
		}
	}
	printf2("\n\n");
}
