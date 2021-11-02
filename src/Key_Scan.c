/*
 * Key_Scan.c
 *
 *  Created on: Feb 10, 2015
 *      Author: rpruitt76
 */
//****************************************************************************
//*
//*	Key_Scan
//*
//* These routines are used to scan the keyboard. Each Column will be asserted low and then the rows will
//* be scanned. The routines are as follows:
//*  LOW Level Routines:
//*	scan_keybaord();	Scan Keyboard and return keyscan results.
//****************************************************************************
//* Laser Pulsar Embedded Software
//* Date: December 19, 2003
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
#define	Row2		2	//P62
#define	Row1		1	//P61
#define	Row0		0	//P60
#define	Laser_pwr	7	//PD7

//*****************************************************************************
//*
//* routine: monPrint_Key
//* Date:    October 11, 2020
//* Author:  Ralph Pruitt
//* This routine sends a monitor message for each key value sent.
//*	Input:
//* 	  unsigned char keynum: Keyvalue to be sent
//*			Legal vales: 1-25
//* Output:
//*		  None
//*
//*****************************************************************************
void monPrint_Key(unsigned char keynum)
{
	if((keynum<=START) && (keynum>0))
	{
		switch(keynum)
		{
		case ONE:
			monPrint("KEY", "1");			// Display Key
			break;
		case TWO:
			monPrint("KEY", "2");			// Display Key
			break;
		case THREE:
			monPrint("KEY", "3");			// Display Key
			break;
		case FOUR:
			monPrint("KEY", "4");			// Display Key
			break;
		case FIVE:
			monPrint("KEY", "5");			// Display Key
			break;
		case SIX:
			monPrint("KEY", "6");			// Display Key
			break;
		case SEVEN:
			monPrint("KEY", "7");			// Display Key
			break;
		case EIGHT:
			monPrint("KEY", "8");			// Display Key
			break;
		case NINE:
			monPrint("KEY", "9");			// Display Key
			break;
		case ZERO:
			monPrint("KEY", "0");			// Display Key
			break;
		case PERIOD:
			monPrint("KEY", "DP");			// Display Key
			break;
		case BACK:
			monPrint("KEY", "<BS");			// Display Key
			break;
		case UP:
			monPrint("KEY", "UP");			// Display Key
			break;
		case DOWN:
			monPrint("KEY", "DOWN");		// Display Key
			break;
		case LEFT:
			monPrint("KEY", "LEFT");		// Display Key
			break;
		case RIGHT:
			monPrint("KEY", "RIGHT");		// Display Key
			break;
		case LASER:
			monPrint("KEY", "OK");			// Display Key
			break;
		case CANCEL:
			monPrint("KEY", "CANCEL");		// Display Key
			break;
		case SELECT:
			monPrint("KEY", "SELECT");		// Display Key
			break;
		case DELETE:
			monPrint("KEY", "DELETE");		// Display Key
			break;
		case TIME:
			monPrint("KEY", "TIME");		// Display Key
			break;
		case LIGHT:
			monPrint("KEY", "LIGHT");		// Display Key
			break;
		case POWER:
			monPrint("KEY", "LASERARM");	// Display Key
			break;
		case OFF:
			monPrint("KEY", "OFF");			// Display Key
			break;
		case START:
			monPrint("KEY", "START");		// Display Key
			break;
		} // EndSwitch (keynum)
	} // EndIf ((keynum<=START) && (keynum>0))
}

//*****************************************************************************
//*
//* routine: scan_keybaord
//* Date:    December 19, 2003
//* Author:  Ralph Pruitt
//* This routine scans the user keyboard and returns the status of which key is
//* pressed. If no key is pressed, the routine will return null. Note that the routine will return
//* key status based on keys indicated in LaserP.h.
//*
//* Output:
//*		  returns Status:   0	  - No Key found.
//*		  		    1-23  - Valid Key Number.
//*
//*****************************************************************************
unsigned char scan_keyboard()
{
    unsigned char key_num;
    // Test to see if we have an active Monitor Key...
    if (mntr_key_var > 0)
    	return mntr_key_var;
#ifdef TST_PATCH
    char tempstr[80];
    key_num = MonitorParse();
    sprintf(tempstr,"Key Entered:%d\n", key_num);
    printf2(tempstr);
    return key_num;
#else
    key_num = scan_keyboard_low();
    return key_num;
#endif
}

//*****************************************************************************
//*
//* routine: scan_keyboard_low
//* Date:    February 19, 2015
//* Author:  Ralph Pruitt
//* This routine scans the user keyboard and returns the status of which key is
//* pressed. If no key is pressed, the routine will return null. Note that the routine will return
//* key status based on keys indicated in LaserP.h.
//*
//* Output:
//*		  returns Status:   0	  - No Key found.
//*		  		    1-23  - Valid Key Number.
//*
//*****************************************************************************
unsigned char scan_keyboard_low()
{
    unsigned char key_num, column, x, temp1;


//   1. Configure Hardware for Scanning.

    // Enable START KEY. P45 as Input
#ifdef PCB_1_00
    PORT4.PDR.BYTE &= ~0x02U;	// Enable P41 as Input.
#else
    PORT4.PDR.BYTE &= ~0x20U;	// Enable P45 as Input.
#endif

	 //DDRB = 0xFF; 		   // Configure Columns for Output.
     PORT7.PDR.BYTE = 0xFF;
     PORT7.PODR.BYTE = 0xFF;

	 //PORTC |= 0x43;		   // Configure Pull-Ups for Rows.
     PORT6.PCR.BYTE |= 0x07;

     //DDRC &= ~0x43;		   // Configure Rows as Inputs.
     PORT6.PDR.BYTE &= ~0x07;

     //	 2a. Scan Start switch first. If active return this key first
          // Loop 5 times to allow debounce.
          for(x=0; x<10; x++)
          {
         	 // If no Switch found...break from loop...NO START KEY
     #ifdef PCB_1_00
         	 if((PORT4.PIDR.BYTE & 0x02U) != 0)
     #else
         	 if((PORT4.PIDR.BYTE & 0x20U) != 0)
     #endif
         	 {
         		 break;
         	 }
         	 short_delay(1);   // Wait 1usec for each loop.
          }
          // If loop count is 10, then we have found a START press, we are done.
          if( x == 10)
          {
     		 beep_1Khz(50);
         	 return START;			// Return START if this is 10.
          }
//   2. Setup loop for scanning.
     key_num = 0;          // Set Key Num accumulator at 0.
	 column = 0xFE;		   // Set Column to assert column 0 first.

//   3. Loop on all four Columns.
     for (x=0; x<8; x++) {
	   PORT7.PODR.BYTE = column;	   // Assert Column to Keyboard.

	   short_delay(200);   // Wait 100usec for port to settle.

	   temp1 = ~PORT6.PIDR.BYTE & 0x07;
	   //temp1 = ~PINC & 0x43; // Read Rows Filter and complement to get Row.

	   if (temp1 > 0) {
	     // OK...Play a beep for the new Key Found.
		 beep_1Khz(50);

	     // We found a Key!
		 if (temp1 >= 0x04)
		   temp1 = 3;
		 else if (temp1 >=2)
		   temp1 = 2;
		 key_num += temp1;
		 return(key_num);
	   }
	   else {
	     key_num += 3;       // Update Key_num by 3 for next loop.
		 column = column << 1;  // Shift Column Left by 1.
		 column |= 0x01; 		// Add in LSB Bit.
	   }
	 }
	 return(0);
}

//*****************************************************************************
//*
//* routine: asrt_col0
//* Date:    January 17, 2004
//* Author:  Ralph Pruitt
//* This routine will assert Column 0 and wait 100usec for it to
//* stabilize. This routine should be called before testing for power, time, or
//* light keys.
//*
//* Output:
//*		     NONE.
//*****************************************************************************
void asrt_col0()
{
//   1. Configure Hardware for Scanning.
	 // DDRB = 0xFF; 		   // Configure Columns for Output.
     PORT7.PDR.BYTE = 0xFF;
     PORT7.PODR.BYTE = 0xFF;

     // PORTC |= 0x43;		   // Configure Pull-Ups for Rows.
     PORT6.PCR.BYTE |= 0x07;

     //DDRC &= ~0x43;		   // Configure Rows as Inputs.
     PORT6.PDR.BYTE &= ~0x07;

     PORT7.PODR.BYTE = 0xFE;	     // Assert Column 0 to Keyboard.

	 short_delay(200);   // Wait 100usec for port to settle.
}

//*****************************************************************************
//*
//* routine: asrt_col6
//* Date:    April 21, 2004
//* Author:  Ralph Pruitt
//* This routine will assert Column 6 and wait 100usec for it to
//* stabilize. This routine should be called before testing for laser, cancel, or
//* delete keys.
//*
//* Output:
//*		     NONE.
//*****************************************************************************
void asrt_col6()
{
//   1. Configure Hardware for Scanning.
	 // DDRB = 0xFF; 		   // Configure Columns for Output.
     PORT7.PDR.BYTE = 0xFF;
     PORT7.PODR.BYTE = 0xFF;

     // PORTC |= 0x43;		   // Configure Pull-Ups for Rows.
     PORT6.PCR.BYTE |= 0x07;

     //DDRC &= ~0x43;		   // Configure Rows as Inputs.
     PORT6.PDR.BYTE &= ~0x07;

     PORT7.PODR.BYTE = 0xBF;	     // Assert Column 1 to Keyboard.

	 short_delay(200);   // Wait 100usec for port to settle.
}

//*****************************************************************************
//*
//* routine: asrt_col1
//* Date:    January 17, 2004
//* Author:  Ralph Pruitt
//* This routine will assert Column 0 and wait 100usec for it to
//* stabilize. This routine should be called before testing for laser, cancel, or
//* delete keys.
//*
//* Output:
//*		     NONE.
//*****************************************************************************
void asrt_col1()
{
//   1. Configure Hardware for Scanning.
	 // DDRB = 0xFF; 		   // Configure Columns for Output.
     PORT7.PDR.BYTE = 0xFF;
     PORT7.PODR.BYTE = 0xFF;

     // PORTC |= 0x43;		   // Configure Pull-Ups for Rows.
     PORT6.PCR.BYTE |= 0x07;

     //DDRC &= ~0x43;		   // Configure Rows as Inputs.
     PORT6.PDR.BYTE &= ~0x07;

     PORT7.PODR.BYTE = 0xFD;	     // Assert Column 0 to Keyboard.

	 short_delay(200);   // Wait 100usec for port to settle.
}

//*****************************************************************************
//*
//* routine: tst_Start
//* Date:    March 1, 2015
//* Author:  Ralph Pruitt
//* This routine will test only the STart key and will return status only for that
//* specific key.
//*
//* Output:
//*		  returns Status:   0	  - No Key found.
//*		  		    		1     - Key found.
//*
//*****************************************************************************
unsigned char tst_Start(void)
{
	int x;

    if (mntr_key_var == START)
   	 return(1);			// If Monitor Start Key Active Must report as found.
    // Loop 5 times to allow debounce.
	for(x=0; x<10; x++)
	{
    // If no Switch found...break from loop...NO START KEY
#ifdef PCB_1_00
		if((PORT4.PIDR.BYTE & 0x02U) != 0)
#else
		if((PORT4.PIDR.BYTE & 0x20U) != 0)
#endif
		{
			break;
		}
		short_delay(1);   // Wait 1usec for each loop.
	}
    // If loop count is 10, then we have found a START press, we are done.
	if( x == 10)
    {
   	 return(1);				// Return 1 if this is 10.
    }
    else
    {
   	 return(0);				// else Return 0.
    }
}

//*****************************************************************************
//*
//* routine: tst_power
//* Date:    January 17, 2004
//* Author:  Ralph Pruitt
//* This routine will test only the power key and will return status only for that
//* specific key.
//*
//* Output:
//*		  returns Status:   0	  - No Key found.
//*		  		    		1     - Key found.
//*
//*****************************************************************************
unsigned char tst_power()
{
     unsigned char temp1;

     if (mntr_key_var == POWER)
    	 return(1);			// If Monitor Power Key Active Must report as found.
     temp1 = ~PORT6.PIDR.BYTE & 0x07;
     //temp1 = ~PINC & 0x43; // Read Rows Filter and complement to get Row.

	 if (temp1 & 0x01)
	   return(1);	   	   // We found the Power Key.
	 else
	   return(0);		   // No Power Key found.
}

//*****************************************************************************
//*
//* routine: tst_laser
//* Date:    January 17, 2004
//* Author:  Ralph Pruitt
//* This routine will test only the power key and will return status only for that
//* specific key.
//*
//* Output:
//*		  returns Status:   0	  - No Key found.
//*		  		    		1     - Key found.
//*
//*****************************************************************************
unsigned char tst_laser()
{
     unsigned char temp1;

     if (mntr_key_var == LASER)
    	 return(1);			// If Monitor Laser Key Active Must report as found.
     temp1 = ~PORT6.PIDR.BYTE & 0x07;
	 //temp1 = ~PINC & 0x43; // Read Rows Filter and complement to get Row.

	 if (temp1 & 0x02)
	   return(1);	   	   // We found the Power Key.
	 else
	   return(0);		   // No Power Key found.
}

//*****************************************************************************
//*
//* routine: tst_cancel
//* Date:    February 14, 2004
//* Author:  Ralph Pruitt
//* This routine will test only the Cancel key and will return status only for that
//* specific key.
//*
//* Output:
//*		  returns Status:   0	  - No Key found.
//*		  		    		1     - Key found.
//*
//*****************************************************************************
unsigned char tst_cancel()
{
     unsigned char temp1;

     if (mntr_key_var == CANCEL)
    	 return(1);			// If Monitor Cancel Key Active Must report as found.
     temp1 = ~PORT6.PIDR.BYTE & 0x07;
	 //temp1 = ~PINC & 0x43; // Read Rows Filter and complement to get Row.

	 if (temp1 & 0x01)
	   return(1);	   	   // We found the Power Key.
	 else
	   return(0);		   // No Power Key found.
}

//*****************************************************************************
//*
//* routine: Keymonitor
//* Date:    February 10, 2015
//* Author:  Ralph Pruitt
//* Key Monitor commands
//*
//*****************************************************************************
void Keymonitor( char* parm1)
{
  int x;
  unsigned char key;

  if( strcmp(parm1, "Wait") == 0)
  {
      printf2("Keyboard Wait Scan.\n");
      for( x=0; x< 200; x++)
      {
    	  key = scan_keyboard_low();
    	  switch(key)
    	  {
    	  	  //case 0:
    	  	  //	  printf2(" Key Pressed: NONE\n");
    	  	  //	  break;
    	  	  case 1:
    	  	  	  printf2(" Key Pressed: CANCEL\n");
    	  	  	  break;
    	  	  case 2:
    	  	  	  printf2(" Key Pressed: SELECT\n");
    	  	  	  break;
    	  	  case 3:
    	  	  	  printf2(" Key Pressed: DELETE\n");
    	  	  	  break;
    	  	  case 4:
    	  	  	  printf2(" Key Pressed: LASER ON/OFF\n");
    	  	  	  break;
    	  	  case 5:
    	  	  	  printf2(" Key Pressed: TIME\n");
    	  	  	  break;
    	  	  case 6:
    	  	  	  printf2(" Key Pressed: LIGHT\n");
    	  	  	  break;
    	  	  case 7:
    	  	  	  printf2(" Key Pressed: ONE\n");
    	  	  	  break;
    	  	  case 8:
    	  	  	  printf2(" Key Pressed: TWO\n");
    	  	  	  break;
    	  	  case 9:
    	  	  	  printf2(" Key Pressed: THREE\n");
    	  	  	  break;
    	  	  case 10:
    	  	  	  printf2(" Key Pressed: FOUR\n");
    	  	  	  break;
    	  	  case 11:
    	  	  	  printf2(" Key Pressed: FIVE\n");
    	  	  	  break;
    	  	  case 12:
    	  	  	  printf2(" Key Pressed: SIX\n");
    	  	  	  break;
    	  	  case 13:
    	  	  	  printf2(" Key Pressed: SEVEN\n");
    	  	  	  break;
    	  	  case 14:
    	  	  	  printf2(" Key Pressed: EIGHT\n");
    	  	  	  break;
    	  	  case 15:
    	  	  	  printf2(" Key Pressed: NINE\n");
    	  	  	  break;
    	  	  case 16:
    	  	  	  printf2(" Key Pressed: PERIOD\n");
    	  	  	  break;
    	  	  case 17:
    	  	  	  printf2(" Key Pressed: ZERO\n");
    	  	  	  break;
    	  	  case 18:
    	  	  	  printf2(" Key Pressed: BACKSPACE\n");
    	  	  	  break;
    	  	  case 19:
    	  	  	  printf2(" Key Pressed: LEFT ARROW\n");
    	  	  	  break;
    	  	  case 20:
    	  	  	  printf2(" Key Pressed: LASER PULSE\n");
    	  	  	  break;
    	  	  case 21:
    	  	  	  printf2(" Key Pressed: RIGHT ARROW\n");
    	  	  	  break;
    	  	  case 22:
    	  	  	  printf2(" Key Pressed: UP ARROW\n");
    	  	  	  break;
    	  	  case 23:
    	  	  	  printf2(" Key Pressed: DOWN ARROW\n");
    	  	  	  break;
    	  	  case 24:
    	  	  	  printf2(" Key Pressed: OFF\n");
    	  	  	  break;
    	  } // EndSwitch
    	  accurate_delay(100);	// Delay 100 msec.
      } // endFor
  } // EndIf ( strcmp(parm1, "Wait") == 0)
  else if( strcmp(parm1, "Now") == 0)
  {
      printf2("Keyboard Scan Now.\n");
	  key = scan_keyboard_low();
	  switch(key)
	  {
	  	  case 0:
	  	  	  printf2(" Key Pressed: NONE\n");
	  	  	  break;
	  	  case 1:
	  	  	  printf2(" Key Pressed: CANCEL\n");
	  	  	  break;
	  	  case 2:
	  	  	  printf2(" Key Pressed: SELECT\n");
	  	  	  break;
	  	  case 3:
	  	  	  printf2(" Key Pressed: DELETE\n");
	  	  	  break;
	  	  case 4:
	  	  	  printf2(" Key Pressed: LASER ON/OFF\n");
	  	  	  break;
	  	  case 5:
	  	  	  printf2(" Key Pressed: TIME\n");
	  	  	  break;
	  	  case 6:
	  	  	  printf2(" Key Pressed: LIGHT\n");
	  	  	  break;
	  	  case 7:
	  	  	  printf2(" Key Pressed: ONE\n");
	  	  	  break;
	  	  case 8:
	  	  	  printf2(" Key Pressed: TWO\n");
	  	  	  break;
	  	  case 9:
	  	  	  printf2(" Key Pressed: THREE\n");
	  	  	  break;
	  	  case 10:
	  	  	  printf2(" Key Pressed: FOUR\n");
	  	  	  break;
	  	  case 11:
	  	  	  printf2(" Key Pressed: FIVE\n");
	  	  	  break;
	  	  case 12:
	  	  	  printf2(" Key Pressed: SIX\n");
	  	  	  break;
	  	  case 13:
	  	  	  printf2(" Key Pressed: SEVEN\n");
	  	  	  break;
	  	  case 14:
	  	  	  printf2(" Key Pressed: EIGHT\n");
	  	  	  break;
	  	  case 15:
	  	  	  printf2(" Key Pressed: NINE\n");
	  	  	  break;
	  	  case 16:
	  	  	  printf2(" Key Pressed: PERIOD\n");
	  	  	  break;
	  	  case 17:
	  	  	  printf2(" Key Pressed: ZERO\n");
	  	  	  break;
	  	  case 18:
	  	  	  printf2(" Key Pressed: BACKSPACE\n");
	  	  	  break;
	  	  case 19:
	  	  	  printf2(" Key Pressed: LEFT ARROW\n");
	  	  	  break;
	  	  case 20:
	  	  	  printf2(" Key Pressed: LASER PULSE\n");
	  	  	  break;
	  	  case 21:
	  	  	  printf2(" Key Pressed: RIGHT ARROW\n");
	  	  	  break;
	  	  case 22:
	  	  	  printf2(" Key Pressed: UP ARROW\n");
	  	  	  break;
	  	  case 23:
	  	  	  printf2(" Key Pressed: DOWN ARROW\n");
	  	  	  break;
	  	  case 24:
	  	  	  printf2(" Key Pressed: OFF\n");
	  	  	  break;
	  } // EndSwitch
  } // Endif ( strcmp(parm1, "Now") == 0)
  else
  {
      printf2("ILLEGAL KEYBOARD Parameter!!\n");
  }
}
