//****************************************************************************
//* 
//*	LCD_Control
//* 
//* These routines are used to control the LCD Display. The display is a 20 character by four line
//* display. The routines are broken into low level and high level routines. These are as follows:
//*  LOW Level Routines:
//*	lcd_comm();			Send commands or data to the LCD Display
//*	lcd_status();		Retrieve LCD Display Status
//*	lcd_read();			Read data from the LCD Display
//* configure_lcd;		Configure and Power-Up LCD Display.
//* turnon_lcd;			Power-Up LCD Display.
//* turnoff_lcd;		Power-Down LCD Display
//* accurate_delay();   Delay set for 1 msec increments
//* wait_busy;			Wait for Busy Signal to Clear
//*  High Level Routines:
//*	init_lcd();			Perform Low Level Soft Reset to LCD Display.
//*	set_cursor();		Set Cursor of LCD Display.
//*	clear_screen();		Clear the LCD Display Screen.
//*	write_lcd();		Write String to LCD Display.
//* char *str_chg_char(size_t length, unsigned char var1)
//* char *str_chg_long(size_t length, unsigned long var1)
//*
//****************************************************************************
//* Laser Pulsar Embedded Software
//* Date: December 11, 2003
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
//#include <iom128v.h>
//#include <macros.h>
#include "r_flash_rx_if.h"
#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
#include <string.h>
#include <stdlib.h>
//#include <cpu.h>
#include  <stdio.h>
//#include <eeprom.h>
#include <r_cg_userdefine.h>
#include "LaserP.h"

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
#define LCD_DELAY	10	// Delay in usec between operations
#if GRAPHICS
//*****************************************************************************
//*
//* routine: lcd_comm2
//* Date:    February 29, 2004
//* Author:  Ralph Pruitt
//* This routine sends data and commands to the Graphics LCD interface. For details of
//* legal commands see the LCD Users Manual. 
//*
//* Input:
//*
//*		  unsigned char dev:   0 - Device A for Commanding
//*		  		   			   1 - Device B for Commanding
//*		  unsigned char rs:	   0 - Send Commands to the LCD Display.
//*		  		   			   1 - Send Data to the LCD Display.
//*		  unsigned char data:  Send 8 Bits of Data to the LCD as a command or data.
//* Output:
//*		  returns Status:	   0 - No Error. Good Completion.
//*		  		  			   1 - RS Parameter Error.
//*
//*****************************************************************************
unsigned char lcd_comm2(unsigned char dev, unsigned char rs, register unsigned char data)
{
// 	 register unsigned char temp1;
//	 unsigned char portb_save;
	 

	 // Mask Interrupts
	 //CLI();
//	 portb_save = PORTB.PODR.BYTE;	// Save PORTB.
	 //long_delay(1);

 	 if (rs >1)
	   return(1);
	 if (rs == 0)
           PORT2.PODR.BYTE &= ~0x02;    // Set RS to Zero/Command.
	 else
           PORT2.PODR.BYTE |= 0x02;     // Set RS to One/Data.

         PORT1.PODR.BYTE &= ~0x40;      // Set RW to Write/Zero.

         PORTB.PODR.BYTE = data;	        // Set Data to PortB.
	 
//	 short_delay(1);   //R
//	 short_delay(LCD_DELAY);
     if (dev == 0) {
	   // Assert E1 to Pulse Data to LCD.
           PORT1.PODR.BYTE |= 0x04;		// Assert E1 Signal.
     }
	 else {
	   // Assert E2 to Pulse Data to LCD.
           PORT1.PODR.BYTE |= 0x20;		// Assert E2 Signal.
	 }
	 // Delay Wait for Port to settle.
	 short_delay(1);
//	 short_delay(LCD_DELAY);
     if (dev == 0) {
           PORT1.PODR.BYTE &= ~0x04;    // Clear E1 Signal.
     }
	 else {
           PORT1.PODR.BYTE &= ~0x20;    // Clear E2 Signal.
	 }
	   	 
	 // Delay Wait for Port to settle.
	 short_delay(1);
//	 short_delay(LCD_DELAY);
         PORT1.PODR.BYTE &= ~0x04;    // Clear E1 Signal.
         PORT1.PODR.BYTE &= ~0x20;    // Clear E2 Signal.
	 
//T	 short_delay(3);
	 short_delay(1);
     // Enable Interrupts.
	 //SEI();
	 return(0); 
}
#endif

#if GRAPHICS
//*****************************************************************************
//*
//* routine: lcd_status2
//* Date:    February 29, 2004
//* Author:  Ralph Pruitt
//* This routine reads the current status from the LCD Display.
//* Output:
//*		  returns Status:	 Bit 7:  0 - LCD Not Busy.
//*		  		  			         1 - LCD Busy...Do not Task.
//*							 Bit6-0: Current Address Counter.
//*
//*****************************************************************************
unsigned char lcd_status2(unsigned char dev)
{
  	 unsigned char status;
	 
         PORT2.PODR.BYTE &= ~0x02;    // Set RS to Zero/Command.

         PORT1.PODR.BYTE |=  0x40;      // Set RW to Read/One.

	 // Set Port B as Input.
         PORTB.PDR.BYTE = 0x00;	        // Set PortB as Input.
	 
//	 short_delay(100);
     if (dev == 0) {
	   // Assert E1 to Pulse Data to LCD.
           PORT1.PODR.BYTE |= 0x04;		// Assert E1 Signal.
     }
	 else {
	   // Assert E2 to Pulse Data to LCD.
           PORT1.PODR.BYTE |= 0x20;		// Assert E2 Signal.
	 }
	 // Delay Wait for Port to settle.
	 short_delay(3);
//	 short_delay(LCD_DELAY);

     status = PORTB.PIDR.BYTE;	// Read Data from PortB.
	 
     PORT2.PODR.BYTE &= ~0x02;      // Clear RS .
     PORT1.PODR.BYTE &= ~0x40;      // Set RW to Write/Zero.
     PORT1.PODR.BYTE &= ~0x20;      // Clear E2 Signal.
     PORT1.PODR.BYTE &= ~0x04;      // Clear E1 Signal.
	 
	 short_delay(1);
	 // Set Port B as Output Low.
     PORTB.PODR.BYTE = 0x00;         // Set Output Low.
     PORTB.PDR.BYTE = 0xFF;	        // Set PortB as Output.

	 return(status);
}
#endif

#if GRAPHICS
//*****************************************************************************
//*
//* routine: lcd_read2
//* Date:    February 29, 2004
//* Author:  Ralph Pruitt
//* This routine reads data from the LCD Display indexed by the current pointer.
//* Output:
//*		  returns 	   Data Indexed Pointer
//*
//*****************************************************************************
unsigned char lcd_read2(unsigned char dev)
{
  	 unsigned char data;
	 
         PORT2.PODR.BYTE |= 0x02;     // Set RS to One/Data.

         PORT1.PODR.BYTE |= 0x40;       // Set RW to Read/One.

	 short_delay(3);
//	 short_delay(LCD_DELAY);
	 
     if (dev == 0) {
	   // Assert E1 to Pulse Data to LCD.
           PORT1.PODR.BYTE |= 0x04;		// Assert E1 Signal.
     }
	 else {
	   // Assert E2 to Pulse Data to LCD.
           PORT1.PODR.BYTE |= 0x20;		// Assert E2 Signal.
	 }

	 // Delay Wait for Port to settle.
	 short_delay(200);
         data = PORTB.PIDR.BYTE;	// Read Data from PortB.
	 
         PORT2.PODR.BYTE &= ~0x02;      // Clear RS .
         PORT1.PODR.BYTE &= ~0x40;      // Set RW to Write/Zero.
         PORT1.PODR.BYTE &= ~0x20;      // Clear E2 Signal.
         PORT1.PODR.BYTE &= ~0x04;      // Clear E1 Signal.

	 
	 // Set Port B as Output Low.
         PORTB.PODR.BYTE = 0x00;         // Set Output Low.
         PORTB.PDR.BYTE = 0xFF;	        // Set PortB as Output.

	 return(data);
}
#endif

//*****************************************************************************
//*
//* routine: configure_lcdoff
//* Date:    January 2, 2009
//* Author:  Ralph Pruitt
//* This routine is used to power-on the LCD Display and control the LCD contrast.
//* routine. 
//*
//* Input:
//*		  contrast:	 	 Sets the value of the contrast for the LCD Display
//*		  				 Legal Values are 0-7. Any others will be stripped off.
//*
//*****************************************************************************
void configure_lcdoff(unsigned char contrast)
{
 	 contrast = 2*contrast + 1;		 // Shift contrast by 2 and Turn On LCD.
	 contrast &= 0x0F;		 		 // Strip off MSB  4 Bits.
}

//*****************************************************************************
//*
//* routine: configure_lcd
//* Date:    December 13, 2003
//* Author:  Ralph Pruitt
//* This routine is used to power-on the LCD Display and control the LCD contrast.
//* routine. 
//*
//* Input:
//*		  contrast:	 	 Sets the value of the contrast for the LCD Display
//*		  				 Legal Values are 0-7. Any others will be stripped off.
//*
//*****************************************************************************
void configure_lcd(unsigned char contrast)
{
  contrast = 2*contrast + 1;		 // Shift contrast by 2 and Turn On LCD.
  contrast &= 0x0F;		 		 // Strip off MSB  4 Bits.
  PORT6.PODR.BYTE &= ~0x30;                   // Disable LCDPWR and BCKLGHT;
     
  PORT1.PODR.BYTE &= ~0x20;                   // Disable E2.
  PORT1.PODR.BYTE |= 0x04;                    // Assert E1.
     
  //PORT6.PODR.BYTE |= 0x20;					// Turn on LCD Backlight.
  PORT6.PODR.BYTE |= 0x30;					// Turn on LCD Backlight and power.
}

//*****************************************************************************
//*
//* routine: turnoff_lcd
//* Date:    December 13, 2003
//* Author:  Ralph Pruitt
//* This routine is used to turn off the LCD Display.
//*
//*****************************************************************************
void turnoff_lcd(void)
{
  // Disable Output from Register to Power-Down LCD.
  PORT6.PODR.BYTE &= ~0x30;                   // Disable LCDPWR and BCKLGHT;
}

//*****************************************************************************
//*
//* routine: turnon_lcd
//* Date:    December 13, 2003
//* Author:  Ralph Pruitt
//* This routine is used to turn on the LCD Display.
//*
//*****************************************************************************
void turnon_lcd(void)
{
  PORT6.PODR.BYTE |= 0x30;                   // Turn On LCDPWR and BCKLGHT;
}

#if GRAPHICS
//*****************************************************************************
//*
//* routine: wait_busy2
//* Date:    February 29, 2004
//* Author:  Ralph Pruitt
//* This routine reads the LCD Status and waits for the Busy flag to clear.
//* If it does not clear after 200 checks, it will return with an error.
//*
//* Output:
//*		  returns Status:	   0 - No Error. Busy Status Cleared.
//*		  		  			   1 - Error. Busy Never Cleared.
//*
//*****************************************************************************
unsigned char wait_busy2(unsigned char dev)
{
   unsigned char status;
   unsigned int count1;
   
   for (count1=0; count1<600; count1++)
   {
     status = lcd_status2(dev);			 // Get LCD Status.
	 status &= 0x80;  				 // Strip to get the Busy Flag
	 if (status == 0)
	   return(0);  	 				 // If Busy Flag Clear, we are done.
     WDR(); //this prevents a timout on enabling
   }
   return(1);
}
#endif

#if GRAPHICS
//*****************************************************************************
//*
//* routine: init_lcd2off
//* Date:    January 2, 2009
//* Author:  Ralph Pruitt
//* This routine performs a powers up the Graphics LCD screen and then performs a soft 
//* reset function to the LCD Screen. 
//*
//* Output:
//*		  returns Status:	   0 - No Error. Busy Status Cleared.
//*		  		  			   1 - Error. Busy Never Cleared.
//*****************************************************************************
unsigned char init_lcd2off(void)
{
//*
//* 1. Power Up LCD Hardware.
//*
   configure_lcdoff(LCD_INTEN);	 	      // Set LCD On with Full Intensity.
   underline = 0;   
//*
//* 2. Wait at Least 50 msec for hardware to power-up.
//*
   accurate_delay(51);		 	 	  // Wait 51 msec for Hardware to Settle.
   return(0);
}

//*****************************************************************************
//*
//* routine: init_lcd2
//* Date:    December 12, 2003
//* Author:  Ralph Pruitt
//* This routine performs a powers up the Graphics LCD screen and then performs a soft 
//* reset function to the LCD Screen. 
//*
//* Output:
//*		  returns Status:	   0 - No Error. Busy Status Cleared.
//*		  		  			   1 - Error. Busy Never Cleared.
//*****************************************************************************
unsigned char init_lcd2(void)
{
   unsigned char status;
//*
//* 1. Power Up LCD Hardware.
//*
   configure_lcd(LCD_INTEN);	 	      // Set LCD On with Full Intensity.
   underline = 0;   
//*
//* 2. Wait at Least 50 msec for hardware to power-up.
//*
   accurate_delay(51);		 	 	  // Wait 51 msec for Hardware to Settle.
//*
//* 3. Display Off. 
//*
   lcd_comm2(GR1, RSCOMMAND, Display_Off2);		  // Send Command to LCD Device 1.   
   lcd_comm2(GR2, RSCOMMAND, Display_Off2);		  // Send Command to LCD Device 2.   
// Wait For Busy Flag to Clear.
   status = wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 1.
   if (status !=0)					  // If failed return from routine.		  
     return(status);
   status = wait_busy2(GR2); 	  	  // Wait for Busy Flag to Clear Device 2.
   if (status !=0)					  // If failed return from routine.		  
     return(status);
	 
//*
//* 4. Soft Reset.
//*
   save_char = 0;	   							  // Reset Pointer.
   lcd_comm2(GR1, RSCOMMAND, Reset_Sft);		  // Send Command to LCD Device 1.   
   lcd_comm2(GR2, RSCOMMAND, Reset_Sft);		  // Send Command to LCD Device 2.   
// Wait For Busy Flag to Clear.
   status = wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 1.
   if (status !=0)					  // If failed return from routine.		  
     return(status);
   status = wait_busy2(GR2); 	  	  // Wait for Busy Flag to Clear Device 2.
   if (status !=0)					  // If failed return from routine.		  
     return(status);

//*
//* 5. Static Drive OFF.
//*
   lcd_comm2(GR1, RSCOMMAND, Static_DRV_OFF);		  // Send Command to LCD Device 1.   
   lcd_comm2(GR2, RSCOMMAND, Static_DRV_OFF);		  // Send Command to LCD Device 2.   
// Wait For Busy Flag to Clear.
   status = wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 1.
   if (status !=0)					  // If failed return from routine.		  
     return(status);
   status = wait_busy2(GR2); 	  	  // Wait for Busy Flag to Clear Device 2.
   if (status !=0)					  // If failed return from routine.		  
     return(status);

//*
//* 6. Select Duty Cycle 1/32. 
//*
   lcd_comm2(GR1, RSCOMMAND, Duty_1_32);		  // Send Command to LCD Device 1.   
   lcd_comm2(GR2, RSCOMMAND, Duty_1_32);		  // Send Command to LCD Device 2.   
// Wait For Busy Flag to Clear.
   status = wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 1.
   if (status !=0)					  // If failed return from routine.		  
     return(status);
   status = wait_busy2(GR2); 	  	  // Wait for Busy Flag to Clear Device 2.
   if (status !=0)					  // If failed return from routine.		  
     return(status);

//*
//* 7. Select ADC Forward.
//*
#ifdef PCB_1_00
   lcd_comm2(GR1, RSCOMMAND, Select_ADC);		  // Send Command to LCD Device 1.   
   lcd_comm2(GR2, RSCOMMAND, Select_ADC);		  // Send Command to LCD Device 2.   
#else
   lcd_comm2(GR1, RSCOMMAND, Select_ADC);		  // Send Command to LCD Device 1.
   lcd_comm2(GR2, RSCOMMAND, Select_ADC);		  // Send Command to LCD Device 2.
#endif
// Wait For Busy Flag to Clear.
   status = wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 1.
   if (status !=0)					  // If failed return from routine.		  
     return(status);
   status = wait_busy2(GR2); 	  	  // Wait for Busy Flag to Clear Device 2.
   if (status !=0)					  // If failed return from routine.		  
     return(status);

//*
//* 8. End Read Modify Write. 
//*
   lcd_comm2(GR1, RSCOMMAND, End_Rd_Mdfy_Wrt);		  // Send Command to LCD Device 1.   
   lcd_comm2(GR2, RSCOMMAND, End_Rd_Mdfy_Wrt);		  // Send Command to LCD Device 2.   
// Wait For Busy Flag to Clear.
   status = wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 1.
   if (status !=0)					  // If failed return from routine.		  
     return(status);
   status = wait_busy2(GR2); 	  	  // Wait for Busy Flag to Clear Device 2.
   if (status !=0)					  // If failed return from routine.		  
     return(status);

//*
//* 9. Display On. 
//*
   lcd_comm2(GR1, RSCOMMAND, Display_On2);		  // Send Command to LCD Device 1.   
   lcd_comm2(GR2, RSCOMMAND, Display_On2);		  // Send Command to LCD Device 2.   
// Wait For Busy Flag to Clear.
   status = wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 1.
   if (status !=0)					  // If failed return from routine.		  
     return(status);
   status = wait_busy2(GR2); 	  	  // Wait for Busy Flag to Clear Device 2.
   if (status !=0)					  // If failed return from routine.		  
     return(status);
//*
//* 3a. Clear Display. 
//*
   clear_screen();					  // Clear Display.	 
   return(0);
}
#endif

//*****************************************************************************
//*
//* routine: set_cursor
//* Date:    December 13, 2003
//* Author:  Ralph Pruitt
//* This routine Sets the user cursor to a specific location within the LCD
//* display. This involves selecting one of the four lines, the cursor type, 
//* and the character location. 
//*
//* Input:
//*		  line_no:	  		   Specifies the line number to set to. Note that
//*		  					   only 0-3 are legal.
//*		  char_no:			   Specifies the character within the line to set
//*  	  					   the cursor to. Note that only 0-19 are legal.
//*		  cursor:		0:	   No Cursor
//*		  				1:	   Underline Cursor
//*						2:	   Blink Cursor
//* Output:
//*		  returns Status:	   0 - No Error. 
//*		  		  			   1 - Illegal Line Number.
//*							   2 - Illegal Character Number.
//*							   3 - Illegal Cursor Selection.
//*							   4 - LCD Timeout. (Busy Flag Not Cleared.
//*
//*****************************************************************************
unsigned char set_cursor(unsigned char line_no, 
		 	  			 unsigned char char_no, 
						 unsigned char cursor)
{
  unsigned char temp1;
  char str[30];

  // Send Line Break.
  printf2("\n");
  
  // Test Parameters.
  if (line_no > 3)
    return(1);
  #if GRAPHICS
  if (char_no >15)
    return(2);
  #else
  if (char_no >19)
    return(2);
  #endif
  if (cursor >2)
    return(3);
	
  #ifndef GRAPHICS
  // Adjust char_no for Line Number.
  switch (line_no) {
    case 0:
	  break;
    case 1:
	  char_no += 0x40;
	  break;
	case 2:
	  char_no += 0x14;
	  break;
	case 3:
	  char_no += 0x54;
	  break;
  }
  
  // OK Lets set the cursor command now.
  switch (cursor) {
    case 0:		  // No Cursor
	  temp1 = 0x0C;
	  break;
	case 1:		  // Underline Cursor
	  temp1 = 0x0E;
l	  break;
	case 2:		  // Blink Cursor
	  temp1 = 0x0D;
	  break;
  }

  // Send the Cursor comand and test for failure.
  lcd_comm(RSCOMMAND, temp1);		  // Send Command to LCD.   
  status = wait_busy();	 	  	  	  // Wait for Busy Flag to Clear
  if (status !=0)					  // If failed return from routine.		  
    return(4);
  #endif
  
  #if GRAPHICS
  temp1 = Page_Address + line_no;	  // Prepare command for transmission.
  lcd_comm2(GR1, RSCOMMAND, temp1);	  // Send Command to LCD Device 1.   
  lcd_comm2(GR2, RSCOMMAND, temp1);	  // Send Command to LCD Device 2.   
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
//   wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 1.
// Calculate char_no for Graphics Display.
  char_no *= 6;
// Adjust Char_Pno if this is an AZ Display..
#if NEW_LCD
  char_no += 4;
#endif
#ifndef PCB_1_00
  //char_no = (16*6) - char_no;
#endif
  sprintf(str, "SC:<%d>", char_no);
  printf2(str);

  save_char = char_no;	 		  	  // Save char_no for later use
  if (char_no > 49) {
    char_no -= 50;
    temp1 = Set_Col_Addr + char_no;	  // Prepare command for transmission.
    lcd_comm2(GR2, RSCOMMAND, temp1);	  // Send Command to LCD Device 2.   
//  Wait For Busy Flag to Clear.
/*T    status = wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 1.
    if (status !=0)					  // If failed return from routine.		  
      return(status);
    else  */
      return(0);
  }
  else {
    temp1 = Set_Col_Addr + char_no;	  // Prepare command for transmission.
    lcd_comm2(GR1, RSCOMMAND, temp1);	  // Send Command to LCD Device 2.   
    lcd_comm2(GR2, RSCOMMAND, Set_Col_Addr);	  // Send Command to LCD Device 2.   
/*T    status = wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 1.
    if (status !=0)					  // If failed return from routine.		  
      return(status);
    else  */
      return(0);
  }
  #else
  // Send the Set Cursor Command Now.
  temp1 = Set_DD_RAM + char_no;	 	  // Prepare command for transmission.
  lcd_comm(RSCOMMAND, temp1);		  // Send Command to LCD.   
  status = wait_busy();	 	  	  	  // Wait for Busy Flag to Clear
  if (status !=0)					  // If failed return from routine.		  
    return(4);
  else
    return(0);
  #endif  
}		

//*****************************************************************************
//*
//* routine: clear_screen
//* Date:    December 13, 2003
//* Author:  Ralph Pruitt
//* This routine clears the LCD memory.
//*		  returns Status:	   0 - No Error. 
//*							   1 - LCD Timeout. (Busy Flag Not Cleared.
//*
//*****************************************************************************
unsigned char clear_screen(void)
{
  unsigned char x, y, temp1;
  
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**                CLEAR SCREEN                                *\n");
  printf2("***************************************************************\n\n\n");

  #if GRAPHICS
  for (y=0; y<4; y++) {
    temp1 = Page_Address + y;
    lcd_comm2(GR1, RSCOMMAND, temp1); 
    lcd_comm2(GR2, RSCOMMAND, temp1); 
    lcd_comm2(GR1, RSCOMMAND, Set_Col_Addr);     // Set to Line 1 Col 0.
    lcd_comm2(GR2, RSCOMMAND, Set_Col_Addr);     // Set to Line 1 Col 0.
    for (x=0 ; x<50; x++) {
      lcd_comm2(GR1, RSDATA, 0x00);     // Send DATA to LCD Device 2.
      lcd_comm2(GR2, RSDATA, 0x00);     // Send DATA to LCD Device 2.
    }
  }
  return(0);
  #else
  lcd_comm(RSCOMMAND, Clear_Display);		  // Send Command to LCD.   
  status = wait_busy();	 	  	  	  // Wait for Busy Flag to Clear
  if (status !=0)					  // If failed return from routine.		  
    return(1);
  else
    return(0);  
  #endif
}
				
//*****************************************************************************
//*
//* routine: write_lcd
//* Date:    December 13, 2003
//* Author:  Ralph Pruitt
//* This routine sends an ascii string to the LCD display indexed by the current
//* cursor. Note that the routine will check for current location of cursor and
//* will not allow wrap-around to the next line.
//*
//* Input:
//*		  String:	  		   Or Pointer to String to transmit.
//* Output:
//*		  returns Status:	   0 - No Error. 
//*		  		  			   1 - String Wrap Occurred.
//*							   4 - LCD Timeout. (Busy Flag Not Cleared.
//*
//*****************************************************************************
unsigned char write_lcd(char *s)
{
  unsigned char temp1;
#ifdef CHAR_HOLD
  char tmpString[10];
  unsigned char flag1;
#endif
  char str[30];
#ifndef PCB_1_00
  int length, x;
#endif
  
  // Printf command
  sprintf(str, "%s", s);
  printf2(str);

#ifndef PCB_1_00
  // Set Ptr to end of string.
  length = strlen(s);
  s += length - 1;
#endif

  #if GRAPHICS
#ifdef PCB_1_00
  while(*s != '\0')
  {
    temp1 = *s;
#ifdef CHAR_HOLD
    sprintf(str, "<%c/%d>",temp1,temp1);
    printf2(str);
#endif
    write_char(temp1);	 				// Send DATA to LCD Screen.
#ifdef CHAR_HOLD
    flag1 = 1;
    while(flag1)
    {
    	R_SCI5_Serial_Rceive( tmpString, RX_STRING_WAIT);
    		flag1=0;
    }
    sprintf(str, "-");
    printf2(str);
#endif
  }
#else
  for( x=0; x<length; x++)
  {
    temp1 = *s;
#ifdef CHAR_HOLD
    sprintf(str, "<%c/%d>",temp1,temp1);
    printf2(str);
#endif
    write_char(temp1);	 				// Send DATA to LCD Screen.
#ifdef CHAR_HOLD
    flag1 = 1;
    while(flag1)
    {
    	R_SCI5_Serial_Rceive( tmpString, RX_STRING_WAIT);
    		flag1=0;
    }
    sprintf(str, "-");
    printf2(str);
#endif
    s--;							  // Decrement Pointers and Counters.
  }
  s += length;
#endif
  return(0);
  #else
  // Get The current Address.
  addrss1 = lcd_status() & 0x7F; 	  // Strip off The Busy Flag.
  
  if (addrss1>0x53)
    addrss1 -= 0x54;
  else if (addrss1>0x3f)
    addrss1 -= 0x40;
  else if (addrss1>0x13)
    addrss1 -= 0x14;
  
  // Send String to LCD Display.
  while(*s != '\0')
  {
    temp1 = *s;
    lcd_comm(RSDATA, temp1);		  // Send Command to LCD.   
    status = wait_busy();	 	  	  // Wait for Busy Flag to Clear
    if (status !=0)					  // If failed return from routine.		  
      return(4);
	s++;							  // Increment Pointers and Counters.
	addrss1++;
    if (addrss1>19)					  // If Address is to big..exit.
	  return(1);
  }
  return(0);
  #endif
}

#if GRAPHICS
//*****************************************************************************
//*
//* routine: write_char
//* Date:    March 1, 2004
//* Author:  Ralph Pruitt
//* This routine writes the correct character to the LCD Screen.
//*
//* Input:
//*		  var1:	 Character to write to LCD.
//* Output:
//*		  None
//*
//*****************************************************************************
void write_char(unsigned char var1)
{
  int x;
  unsigned char temp2[7];
  unsigned char	col_offset;
  unsigned char temp1;

  switch (var1) {
    // Character "0"
    case 0x30:
#ifdef PCB_1_00
	  temp2[0] = 0x3E;
	  temp2[1] = 0x51;
	  temp2[2] = 0x49;
	  temp2[3] = 0x45;
	  temp2[4] = 0x3E;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x7C;	//00111110 > 01111100
	  temp2[1] = 0x8A;	//01010001 > 10001010
	  temp2[2] = 0x92;	//01001001 > 10010010
	  temp2[3] = 0xA2;	//01000101 > 10100010
	  temp2[4] = 0x7C;	//00111110 > 01111100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "1"
    case 0x31:
#ifdef PCB_1_00
	  temp2[0] = 0x00;
	  temp2[1] = 0x42;
	  temp2[2] = 0x7F;
	  temp2[3] = 0x40;
	  temp2[4] = 0x00;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x00;	//00000000 > 00000000
	  temp2[1] = 0x42;	//01000010 > 01000010
	  temp2[2] = 0xFE;	//01111111 > 11111110
	  temp2[3] = 0x02;	//01000000 > 00000010
	  temp2[4] = 0x00;	//00000000 > 00000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "2"
    case 0x32:
#ifdef PCB_1_00
	  temp2[0] = 0x42;
	  temp2[1] = 0x61;
	  temp2[2] = 0x51;
	  temp2[3] = 0x49;
	  temp2[4] = 0x66;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x42;	//01000010 > 01000010
	  temp2[1] = 0x86;	//01100001 > 10000110
	  temp2[2] = 0x8A;	//01010001 > 10001010
	  temp2[3] = 0x92;	//01001001 > 10010010
	  temp2[4] = 0x66;	//01100110 > 01100110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "3"
    case 0x33:
#ifdef PCB_1_00
	  temp2[0] = 0x22;
	  temp2[1] = 0x41;
	  temp2[2] = 0x49;
	  temp2[3] = 0x49;
	  temp2[4] = 0x36;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x44;	//00100010 > 01000100
	  temp2[1] = 0x82;	//01000001 > 10000010
	  temp2[2] = 0x92;	//01001001 > 10010010
	  temp2[3] = 0x92;	//01001001 > 10010010
	  temp2[4] = 0x6C;	//00110110 > 01101100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "4"
    case 0x34:
#ifdef PCB_1_00
	  temp2[0] = 0x18;
	  temp2[1] = 0x14;
	  temp2[2] = 0x52;
	  temp2[3] = 0x7F;
	  temp2[4] = 0x50;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x18;	//00011000 > 00011000
	  temp2[1] = 0x28;	//00010100 > 00101000
	  temp2[2] = 0x4A;	//01010010 > 01001010
	  temp2[3] = 0xFE;	//01111111 > 11111110
	  temp2[4] = 0x0A;	//01010000 > 00001010
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "5"
    case 0x35:
#ifdef PCB_1_00
	  temp2[0] = 0x27;
	  temp2[1] = 0x45;
	  temp2[2] = 0x45;
	  temp2[3] = 0x45;
	  temp2[4] = 0x39;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xE4;	//00100111 > 11100100
	  temp2[1] = 0xA2;	//01000101 > 10100010
	  temp2[2] = 0xA2;	//01000101 > 10100010
	  temp2[3] = 0xA2;	//01000101 > 10100010
	  temp2[4] = 0x9C;	//00111001 > 10011100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "6"
    case 0x36:
#ifdef PCB_1_00
	  temp2[0] = 0x3C;
	  temp2[1] = 0x4A;
	  temp2[2] = 0x49;
	  temp2[3] = 0x49;
	  temp2[4] = 0x30;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x3C;	//00111100 > 00111100
	  temp2[1] = 0x52;	//01001010 > 01010010
	  temp2[2] = 0x92;	//01001001 > 10010010
	  temp2[3] = 0x92;	//01001001 > 10010010
	  temp2[4] = 0x0C;	//00110000 > 00001100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "7"
    case 0x37:
#ifdef PCB_1_00
	  temp2[0] = 0x03;
	  temp2[1] = 0x71;
	  temp2[2] = 0x09;
	  temp2[3] = 0x05;
	  temp2[4] = 0x03;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xC0;	//00000011 > 11000000
	  temp2[1] = 0x8E;	//01110001 > 10001110
	  temp2[2] = 0x90;	//00001001 > 10010000
	  temp2[3] = 0xA0;	//00000101 > 10100000
	  temp2[4] = 0xC0;	//00000011 > 11000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "8"
    case 0x38:
#ifdef PCB_1_00
	  temp2[0] = 0x36;
	  temp2[1] = 0x49;
	  temp2[2] = 0x49;
	  temp2[3] = 0x49;
	  temp2[4] = 0x36;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x6C;	//00110110 > 01101100
	  temp2[1] = 0x92;	//01001001 > 10010010
	  temp2[2] = 0x92;	//01001001 > 10010010
	  temp2[3] = 0x92;	//01001001 > 10010010
	  temp2[4] = 0x6c;	//00110110 > 01101100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "9"
    case 0x39:
#ifdef PCB_1_00
	  temp2[0] = 0x06;
	  temp2[1] = 0x49;
	  temp2[2] = 0x29;
	  temp2[3] = 0x19;
	  temp2[4] = 0x0E;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x60;	//00000110 > 01100000
	  temp2[1] = 0x92;	//01001001 > 10010010
	  temp2[2] = 0x94;	//00101001 > 10010100
	  temp2[3] = 0x98;	//00011001 > 10011000
	  temp2[4] = 0x70;	//00001110 > 01110000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "Space"
    case 0x20:
#ifdef PCB_1_00
	  temp2[0] = 0x00;
	  temp2[1] = 0x00;
	  temp2[2] = 0x00;
	  temp2[3] = 0x00;
	  temp2[4] = 0x00;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x00;	//00000000 > 00000000
	  temp2[1] = 0x00;	//00000000 > 00000000
	  temp2[2] = 0x00;	//00000000 > 00000000
	  temp2[3] = 0x00;	//00000000 > 00000000
	  temp2[4] = 0x00;	//00000000 > 00000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "*"
    case 0x2A:
#ifdef PCB_1_00
	  temp2[0] = 0x2A;
	  temp2[1] = 0x1C;
	  temp2[2] = 0x7F;
	  temp2[3] = 0x1C;
	  temp2[4] = 0x2A;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x54;	//00101010 > 01010100
	  temp2[1] = 0x38;	//00011100 > 00111000
	  temp2[2] = 0xFE;	//01111111 > 11111110
	  temp2[3] = 0x38;	//00011100 > 00111000
	  temp2[4] = 0x54;	//00101010 > 01010100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character ":"
    case 0x3A:
#ifdef PCB_1_00
	  temp2[0] = 0x00;
	  temp2[1] = 0x00;
	  temp2[2] = 0x36;
	  temp2[3] = 0x00;
	  temp2[4] = 0x00;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x00;	//00000000 > 00000000
	  temp2[1] = 0x00;	//00000000 > 00000000
	  temp2[2] = 0x6C;	//00110110 > 01101100
	  temp2[3] = 0x00;	//00000000 > 00000000
	  temp2[4] = 0x00;	//00000000 > 00000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "+"
    case 0x2B:
#ifdef PCB_1_00
	  temp2[0] = 0x08;
	  temp2[1] = 0x08;
	  temp2[2] = 0x3E;
	  temp2[3] = 0x08;
	  temp2[4] = 0x08;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x10;	//00001000 > 00010000
	  temp2[1] = 0x10;	//00001000 > 00010000
	  temp2[2] = 0x7C;	//00111110 > 01111100
	  temp2[3] = 0x10;	//00001000 > 00010000
	  temp2[4] = 0x10;	//00001000 > 00010000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "-"
    case 0x2D:
#ifdef PCB_1_00
	  temp2[0] = 0x00;
	  temp2[1] = 0x08;
	  temp2[2] = 0x08;
	  temp2[3] = 0x08;
	  temp2[4] = 0x00;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x00;	//00000000 > 00000000
	  temp2[1] = 0x10;	//00001000 > 00010000
	  temp2[2] = 0x10;	//00001000 > 00010000
	  temp2[3] = 0x10;	//00001000 > 00010000
	  temp2[4] = 0x00;	//00000000 > 00000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "period"
    case 0x2E:
#ifdef PCB_1_00
	  temp2[0] = 0x00;
	  temp2[1] = 0x00;
	  temp2[2] = 0x40;
	  temp2[3] = 0x00;
	  temp2[4] = 0x00;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x00;	//00000000 > 00000000
	  temp2[1] = 0x00;	//00000000 > 00000000
	  temp2[2] = 0x02;	//01000000 > 00000010
	  temp2[3] = 0x00;	//00000000 > 00000000
	  temp2[4] = 0x00;	//00000000 > 00000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "/"
    case 0x2F:
#ifdef PCB_1_00
	  temp2[0] = 0x60;
	  temp2[1] = 0x10;
	  temp2[2] = 0x08;
	  temp2[3] = 0x04;
	  temp2[4] = 0x03;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x06;	//01100000 > 00000110
	  temp2[1] = 0x08;	//00010000 > 00001000
	  temp2[2] = 0x10;	//00001000 > 00010000
	  temp2[3] = 0x20;	//00000100 > 00100000
	  temp2[4] = 0xC0;	//00000011 > 11000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break;
    // Character "#"
    case 0x23:
#ifdef PCB_1_00
	  temp2[0] = 0x14;
	  temp2[1] = 0x3E;
	  temp2[2] = 0x14;
	  temp2[3] = 0x3E;
	  temp2[4] = 0x14;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x28;	//00010100 > 00101000
	  temp2[1] = 0x7C;	//00111110 > 01111100
	  temp2[2] = 0x28;	//00010100 > 00101000
	  temp2[3] = 0x7C;	//00111110 > 01111100
	  temp2[4] = 0x28;	//00010100 > 00101000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break;
    // Character "?"
    case 0x3F:
#ifdef PCB_1_00
	  temp2[0] = 0x06;
	  temp2[1] = 0x01;
	  temp2[2] = 0x51;
	  temp2[3] = 0x09;
	  temp2[4] = 0x06;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x60;	//00000110 > 01100000
	  temp2[1] = 0x80;	//00000001 > 10000000
	  temp2[2] = 0x8A;	//01010001 > 10001010
	  temp2[3] = 0x90;	//00001001 > 10010000
	  temp2[4] = 0x60;	//00000110 > 01100000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break;
    // Character "_"
    case 0x5F:
#ifdef PCB_1_00
	  temp2[0] = 0x40;
	  temp2[1] = 0x40;
	  temp2[2] = 0x40;
	  temp2[3] = 0x40;
	  temp2[4] = 0x40;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x02;	//01000000 > 00000010
	  temp2[1] = 0x02;	//01000000 > 00000010
	  temp2[2] = 0x02;	//01000000 > 00000010
	  temp2[3] = 0x02;	//01000000 > 00000010
	  temp2[4] = 0x02;	//01000000 > 00000010
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break;
    // Character "a"
    case 0x61:
#ifdef PCB_1_00
	  temp2[0] = 0x20;
	  temp2[1] = 0x54;
	  temp2[2] = 0x54;
	  temp2[3] = 0x38;
	  temp2[4] = 0x40;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x04;	//00100000 > 00000100
	  temp2[1] = 0x2A;	//01010100 > 00101010
	  temp2[2] = 0x2A;	//01010100 > 00101010
	  temp2[3] = 0x1C;	//00111000 > 00011100
	  temp2[4] = 0x02;	//01000000 > 00000010
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "b"
    case 0x62:
#ifdef PCB_1_00
	  temp2[0] = 0x42;
	  temp2[1] = 0x7E;
	  temp2[2] = 0x48;
	  temp2[3] = 0x48;
	  temp2[4] = 0x30;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x42;	//01000010 > 01000010
	  temp2[1] = 0x7E;	//01111110 > 01111110
	  temp2[2] = 0x22;	//01001000 > 00010010
	  temp2[3] = 0x22;	//01001000 > 00010010
	  temp2[4] = 0x00;	//00110000 > 00001100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "c"
	  case 0x63:
#ifdef PCB_1_00
	  temp2[0] = 0x38;
	  temp2[1] = 0x44;
	  temp2[2] = 0x44;
	  temp2[3] = 0x28;
	  temp2[4] = 0x00;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x1C;	//00111000 > 00011100
	  temp2[1] = 0x22;	//01000100 > 00100010
	  temp2[2] = 0x22;	//01000100 > 00100010
	  temp2[3] = 0x14;  //00101000 > 00010100
	  temp2[4] = 0x00;	//00000000 > 00000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00;	//00000000 > 00000000
#endif
	  break;
    // Character "d"
    case 0x64:
#ifdef PCB_1_00
	  temp2[0] = 0x30;
	  temp2[1] = 0x48;
	  temp2[2] = 0x49;
	  temp2[3] = 0x3F;
	  temp2[4] = 0x40;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x0C;	//00110000 > 00001100
	  temp2[1] = 0x12;	//01001000 > 00010010
	  temp2[2] = 0x92;	//01001001 > 10010010
	  temp2[3] = 0xFC;	//00111111 > 11111100
	  temp2[4] = 0x02;	//01000000 > 00000010
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "e"
    case 0x65:
#ifdef PCB_1_00
	  temp2[0] = 0x38;
	  temp2[1] = 0x54;
	  temp2[2] = 0x54;
	  temp2[3] = 0x48;
	  temp2[4] = 0x00;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x1C;	//00111000 > 00011100
	  temp2[1] = 0x2A;	//01010100 > 00101010
	  temp2[2] = 0x2A;	//01010100 > 00101010
	  temp2[3] = 0x12;	//01001000 > 00010010
	  temp2[4] = 0x00;	//00000000 > 00000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "f"
    case 0x66:
#ifdef PCB_1_00
	  temp2[0] = 0x00;
	  temp2[1] = 0x50;
	  temp2[2] = 0x7C;
	  temp2[3] = 0x52;
	  temp2[4] = 0x04;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x00;	//00000000 > 00000000
	  temp2[1] = 0x0A;	//01010000 > 00001010
	  temp2[2] = 0x3E;	//01111100 > 00111110
	  temp2[3] = 0x4A;	//01010010 > 01001010
	  temp2[4] = 0x20;	//00000100 > 00100000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "g"
    case 0x67:
#ifdef PCB_1_00
	  temp2[0] = 0x48;
	  temp2[1] = 0x54;
	  temp2[2] = 0x54;
	  temp2[3] = 0x38;
	  temp2[4] = 0x00;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x12;	//01001000 > 00010010
	  temp2[1] = 0x2A;	//01010100 > 00101010
	  temp2[2] = 0x2A;	//01010100 > 00101010
	  temp2[3] = 0x1C;	//00111000 > 00011100
	  temp2[4] = 0x00;	//00000000 > 00000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "h"
    case 0x68:
#ifdef PCB_1_00
	  temp2[0] = 0x42;
	  temp2[1] = 0x7E;
	  temp2[2] = 0x08;
	  temp2[3] = 0x08;
	  temp2[4] = 0x70;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x42;	//01000010 > 01000010
	  temp2[1] = 0x7E;	//01111110 > 01111110
	  temp2[2] = 0x10;	//00001000 > 00010000
	  temp2[3] = 0x10;	//00001000 > 00010000
	  temp2[4] = 0x0E;	//01110000 > 00001110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "i"
    case 0x69:
#ifdef PCB_1_00
	  temp2[0] = 0x00;
	  temp2[1] = 0x44;
	  temp2[2] = 0x7D;
	  temp2[3] = 0x40;
	  temp2[4] = 0x00;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x00;	//00000000 > 00000000
	  temp2[1] = 0x22;	//01000100 > 00100010
	  temp2[2] = 0xAE;	//01111101 > 10101110
	  temp2[3] = 0x02;	//01000000 > 00000010
	  temp2[4] = 0x00;	//00000000 > 00000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "j"
    case 0x6A:
#ifdef PCB_1_00
	  temp2[0] = 0x30;
	  temp2[1] = 0x40;
	  temp2[2] = 0x40;
	  temp2[3] = 0x3D;
	  temp2[4] = 0x00;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x0C;	//00110000 > 00001100
	  temp2[1] = 0x02;	//01000000 > 00000010
	  temp2[2] = 0x02;	//01000000 > 00000010
	  temp2[3] = 0xAC;	//00111101 > 10101100
	  temp2[4] = 0x00;	//00000000 > 00000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "k"
    case 0x6B:
#ifdef PCB_1_00
	  temp2[0] = 0x42;
	  temp2[1] = 0x7E;
	  temp2[2] = 0x20;
	  temp2[3] = 0x30;
	  temp2[4] = 0x48;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x42;	//01000010 > 01000010
	  temp2[1] = 0x7E;	//01111110 > 01111110
	  temp2[2] = 0x04;	//00100000 > 00000100
	  temp2[3] = 0x0C;	//00110000 > 00001100
	  temp2[4] = 0x12;	//01001000 > 00010010
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "l"
    case 0x6C:
#ifdef PCB_1_00
	  temp2[0] = 0x00;
	  temp2[1] = 0x41;
	  temp2[2] = 0x7F;
	  temp2[3] = 0x40;
	  temp2[4] = 0x00;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x00;	//00000000 > 00000000
	  temp2[1] = 0x82;	//01000001 > 10000010
	  temp2[2] = 0xFE;	//01111111 > 11111110
	  temp2[3] = 0x02;	//01000000 > 00000010
	  temp2[4] = 0x00;	//00000000 > 00000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "m"
    case 0x6D:
#ifdef PCB_1_00
	  temp2[0] = 0x7C;
	  temp2[1] = 0x08;
	  temp2[2] = 0x18;
	  temp2[3] = 0x0C;
	  temp2[4] = 0x78;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x3E;	//01111100 > 00111110
	  temp2[1] = 0x10;	//00001000 > 00010000
	  temp2[2] = 0x18;	//00011000 > 00011000
	  temp2[3] = 0x30;	//00001100 > 00110000
	  temp2[4] = 0x1E;	//01111000 > 00011110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "n"
    case 0x6E:
#ifdef PCB_1_00
	  temp2[0] = 0x7C;
	  temp2[1] = 0x04;
	  temp2[2] = 0x04;
	  temp2[3] = 0x04;
	  temp2[4] = 0x78;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x3E;	//01111100 > 00111110
	  temp2[1] = 0x20;	//00000100 > 00100000
	  temp2[2] = 0x20;	//00000100 > 00100000
	  temp2[3] = 0x20;	//00000100 > 00100000
	  temp2[4] = 0x1E;	//01111000 > 00011110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "o"
    case 0x6F:
#ifdef PCB_1_00
	  temp2[0] = 0x38;
	  temp2[1] = 0x44;
	  temp2[2] = 0x44;
	  temp2[3] = 0x44;
	  temp2[4] = 0x38;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x1C;	//00111000 > 00011100
	  temp2[1] = 0x22;	//01000100 > 00100010
	  temp2[2] = 0x22;	//01000100 > 00100010
	  temp2[3] = 0x22;	//01000100 > 00100010
	  temp2[4] = 0x1C;	//00111000 > 00011100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "p"
    case 0x70:
#ifdef PCB_1_00
	  temp2[0] = 0x42;
	  temp2[1] = 0x7C;
	  temp2[2] = 0x52;
	  temp2[3] = 0x12;
	  temp2[4] = 0x0C;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x42;	//01000010 > 01000010
	  temp2[1] = 0x3E;	//01111100 > 00111110
	  temp2[2] = 0x4A;	//01010010 > 01001010
	  temp2[3] = 0x48;	//00010010 > 01001000
	  temp2[4] = 0x30;	//00001100 > 00110000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "q"
    case 0x71:
#ifdef PCB_1_00
	  temp2[0] = 0x0C;
	  temp2[1] = 0x12;
	  temp2[2] = 0x52;
	  temp2[3] = 0x7C;
	  temp2[4] = 0x42;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x30;	//00001100 > 00110000
	  temp2[1] = 0x48;	//00010010 > 01001000
	  temp2[2] = 0x4A;	//01010010 > 01001010
	  temp2[3] = 0x3E;	//01111100 > 00111110
	  temp2[4] = 0x42;	//01000010 > 01000010
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "r"
    case 0x72:
#ifdef PCB_1_00
	  temp2[0] = 0x44;
	  temp2[1] = 0x78;
	  temp2[2] = 0x44;
	  temp2[3] = 0x04;
	  temp2[4] = 0x08;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x22;	//01000100 > 00100010
	  temp2[1] = 0x1E;	//01111000 > 00011110
	  temp2[2] = 0x22;	//01000100 > 00100010
	  temp2[3] = 0x20;	//00000100 > 00100000
	  temp2[4] = 0x10;	//00001000 > 00010000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "s"
    case 0x73:
#ifdef PCB_1_00
	  temp2[0] = 0x48;
	  temp2[1] = 0x54;
	  temp2[2] = 0x54;
	  temp2[3] = 0x54;
	  temp2[4] = 0x24;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x12;	//01001000 > 00010010
	  temp2[1] = 0x2A;	//01010100 > 00101010
	  temp2[2] = 0x2A;	//01010100 > 00101010
	  temp2[3] = 0x2A;	//01010100 > 00101010
	  temp2[4] = 0x2A;	//00100100 > 00100100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "t"
    case 0x74:
#ifdef PCB_1_00
	  temp2[0] = 0x00;
	  temp2[1] = 0x04;
	  temp2[2] = 0x3E;
	  temp2[3] = 0x44;
	  temp2[4] = 0x20;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x00;	//00000000 > 00000000
	  temp2[1] = 0x20;	//00000100 > 00100000
	  temp2[2] = 0x7C;	//00111110 > 01111100
	  temp2[3] = 0x22;	//01000100 > 00100010
	  temp2[4] = 0x04;	//00100000 > 00000100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "u"
    case 0x75:
#ifdef PCB_1_00
	  temp2[0] = 0x3C;
	  temp2[1] = 0x40;
	  temp2[2] = 0x40;
	  temp2[3] = 0x3C;
	  temp2[4] = 0x40;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x3C;	//00111100 > 00111100
	  temp2[1] = 0x02;	//01000000 > 00000010
	  temp2[2] = 0x02;	//01000000 > 00000010
	  temp2[3] = 0x3C;	//00111100 > 00111100
	  temp2[4] = 0x02;	//01000000 > 00000010
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "v"
    case 0x76:
#ifdef PCB_1_00
	  temp2[0] = 0x1C;
	  temp2[1] = 0x20;
	  temp2[2] = 0x40;
	  temp2[3] = 0x20;
	  temp2[4] = 0x1C;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x38;	//00011100 > 00111000
	  temp2[1] = 0x04;	//00100000 > 00000100
	  temp2[2] = 0x02;	//01000000 > 00000010
	  temp2[3] = 0x04;	//00100000 > 00000100
	  temp2[4] = 0x38;	//00011100 > 00111000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "w"
    case 0x77:
#ifdef PCB_1_00
	  temp2[0] = 0x3C;
	  temp2[1] = 0x40;
	  temp2[2] = 0x20;
	  temp2[3] = 0x40;
	  temp2[4] = 0x3C;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x3C;	//00111100 > 00111100
	  temp2[1] = 0x02;	//01000000 > 00000010
	  temp2[2] = 0x04;	//00100000 > 00000100
	  temp2[3] = 0x02;	//01000000 > 00000010
	  temp2[4] = 0x3C;	//00111100 > 00111100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "x"
    case 0x78:
#ifdef PCB_1_00
	  temp2[0] = 0x44;
	  temp2[1] = 0x28;
	  temp2[2] = 0x10;
	  temp2[3] = 0x28;
	  temp2[4] = 0x44;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x22;	//01000100 > 00100010
	  temp2[1] = 0x14;	//00101000 > 00010100
	  temp2[2] = 0x08;	//00010000 > 00001000
	  temp2[3] = 0x14;	//00101000 > 00010100
	  temp2[4] = 0x22;	//01000100 > 00100010
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "y"
    case 0x79:
#ifdef PCB_1_00
	  temp2[0] = 0x4E;
	  temp2[1] = 0x50;
	  temp2[2] = 0x50;
	  temp2[3] = 0x30;
	  temp2[4] = 0x1E;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x72;	//01001110 > 01110010
	  temp2[1] = 0x0A;	//01010000 > 00001010
	  temp2[2] = 0x0A;	//01010000 > 00001010
	  temp2[3] = 0x0C;	//00110000 > 00001100
	  temp2[4] = 0x78;	//00011110 > 01111000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "z"
    case 0x7A:
#ifdef PCB_1_00
	  temp2[0] = 0x44;
	  temp2[1] = 0x64;
	  temp2[2] = 0x54;
	  temp2[3] = 0x4C;
	  temp2[4] = 0x44;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00;
#else
	  temp2[0] = 0x22;	//01000100 > 00100010
	  temp2[1] = 0x26;	//01100100 > 00100110
	  temp2[2] = 0x2A;	//01010100 > 00101010
	  temp2[3] = 0x32;	//01001100 > 00110010
	  temp2[4] = 0x22;	//01000100 > 00100010
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00;	//00000000 > 00000000
#endif
	  break; 
    // Character "A"
    case 0x41:
#ifdef PCB_1_00
	  temp2[0] = 0x7E;
	  temp2[1] = 0x09;
	  temp2[2] = 0x09;
	  temp2[3] = 0x09;
	  temp2[4] = 0x7E;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00;
#else
	  temp2[0] = 0x7E;	//01111110 > 01111110
	  temp2[1] = 0x90;	//00001001 > 10010000
	  temp2[2] = 0x90;	//00001001 > 10010000
	  temp2[3] = 0x90;	//00001001 > 10010000
	  temp2[4] = 0x7E;	//01111110 > 01111110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00;	//00000000 > 00000000
#endif
	  break; 
    // Character "B"
    case 0x42:
#ifdef PCB_1_00
	  temp2[0] = 0x41;
	  temp2[1] = 0x7F;
	  temp2[2] = 0x49;
	  temp2[3] = 0x49;
	  temp2[4] = 0x36;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x82;	//01000001 > 10000010
	  temp2[1] = 0xFE;	//01111111 > 11111110
	  temp2[2] = 0x92;	//01001001 > 10010010
	  temp2[3] = 0x92;	//01001001 > 10010010
	  temp2[4] = 0x6C;	//00110110 > 01101100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "C"
    case 0x43:
#ifdef PCB_1_00
	  temp2[0] = 0x1C;
	  temp2[1] = 0x22;
	  temp2[2] = 0x41;
	  temp2[3] = 0x41;
	  temp2[4] = 0x22;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x38;	//00011100 > 00111000
	  temp2[1] = 0x44;	//00100010 > 01000100
	  temp2[2] = 0x82;	//01000001 > 10000010
	  temp2[3] = 0x82;	//01000001 > 10000010
	  temp2[4] = 0x44;	//00100010 > 01000100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "D"
    case 0x44:
#ifdef PCB_1_00
	  temp2[0] = 0x41;
	  temp2[1] = 0x7F;
	  temp2[2] = 0x41;
	  temp2[3] = 0x41;
	  temp2[4] = 0x3E;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x82;	//01000001 > 10000010
	  temp2[1] = 0xFE;	//01111111 > 11111110
	  temp2[2] = 0x82;	//01000001 > 10000010
	  temp2[3] = 0x82;	//01000001 > 10000010
	  temp2[4] = 0x7C;	//00111110 > 01111100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "E"
    case 0x45:
#ifdef PCB_1_00
	  temp2[0] = 0x41;
	  temp2[1] = 0x7F;
	  temp2[2] = 0x49;
	  temp2[3] = 0x49;
	  temp2[4] = 0x63;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x82;	//01000001 > 10000010
	  temp2[1] = 0xFE;	//01111111 > 11111110
	  temp2[2] = 0x92;	//01001001 > 10010010
	  temp2[3] = 0x92;	//01001001 > 10010010
	  temp2[4] = 0xC6;	//01100011 > 11000110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "F"
    case 0x46:
#ifdef PCB_1_00
	  temp2[0] = 0x41;
	  temp2[1] = 0x7F;
	  temp2[2] = 0x49;
	  temp2[3] = 0x09;
	  temp2[4] = 0x03;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x82;	//01000001 > 10000010
	  temp2[1] = 0xFE;	//01111111 > 11111110
	  temp2[2] = 0x92;	//01001001 > 10010010
	  temp2[3] = 0x90;	//00001001 > 10010000
	  temp2[4] = 0xC0;	//00000011 > 11000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "G"
    case 0x47:
#ifdef PCB_1_00
	  temp2[0] = 0x1E;
	  temp2[1] = 0x21;
	  temp2[2] = 0x41;
	  temp2[3] = 0x51;
	  temp2[4] = 0x72;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x78;	//00011110 > 01111000
	  temp2[1] = 0x84;	//00100001 > 10000100
	  temp2[2] = 0x82;	//01000001 > 10000010
	  temp2[3] = 0x8A;	//01010001 > 10001010
	  temp2[4] = 0x4E;	//01110010 > 01001110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "H"
    case 0x48:
#ifdef PCB_1_00
	  temp2[0] = 0x7F;
	  temp2[1] = 0x08;
	  temp2[2] = 0x08;
	  temp2[3] = 0x08;
	  temp2[4] = 0x7F;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xFE;	//01111111 > 11111110
	  temp2[1] = 0x10;	//00001000 > 00010000
	  temp2[2] = 0x10;	//00001000 > 00010000
	  temp2[3] = 0x10;	//00001000 > 00010000
	  temp2[4] = 0xFE;	//01111111 > 11111110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "I"
    case 0x49:
#ifdef PCB_1_00
	  temp2[0] = 0x00;
	  temp2[1] = 0x41;
	  temp2[2] = 0x7F;
	  temp2[3] = 0x41;
	  temp2[4] = 0x00;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x00;	//00000000 > 00000000
	  temp2[1] = 0x82;	//01000001 > 10000010
	  temp2[2] = 0xFE;	//01111111 > 11111110
	  temp2[3] = 0x82;	//01000001 > 10000010
	  temp2[4] = 0x00;	//00000000 > 00000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "J"
    case 0x4A:
#ifdef PCB_1_00
	  temp2[0] = 0x20;
	  temp2[1] = 0x40;
	  temp2[2] = 0x40;
	  temp2[3] = 0x41;
	  temp2[4] = 0x3F;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x04;	//00100000 > 00000100
	  temp2[1] = 0x02;	//01000000 > 00000010
	  temp2[2] = 0x02;	//01000000 > 00000010
	  temp2[3] = 0x82;	//01000001 > 10000010
	  temp2[4] = 0xFC;	//00111111 > 11111100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "K"
    case 0x4B:
#ifdef PCB_1_00
	  temp2[0] = 0x41;
	  temp2[1] = 0x7F;
	  temp2[2] = 0x18;
	  temp2[3] = 0x18;
	  temp2[4] = 0x67;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x82;	//01000001 > 10000010
	  temp2[1] = 0xFE;	//01111111 > 11111110
	  temp2[2] = 0x18;	//00011000 > 00011000
	  temp2[3] = 0x18;	//00011000 > 00011000
	  temp2[4] = 0xE6;	//01100111 > 11100110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "L"
    case 0x4C:
#ifdef PCB_1_00
	  temp2[0] = 0x41;
	  temp2[1] = 0x7F;
	  temp2[2] = 0x41;
	  temp2[3] = 0x40;
	  temp2[4] = 0x60;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x82;	//01000001 > 10000010
	  temp2[1] = 0xFE;	//01111111 > 11111110
	  temp2[2] = 0x82;	//01000001 > 10000010
	  temp2[3] = 0x02;	//01000000 > 00000010
	  temp2[4] = 0x06;	//01100000 > 00000110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "M"
    case 0x4D:
#ifdef PCB_1_00
	  temp2[0] = 0x7F;
	  temp2[1] = 0x02;
	  temp2[2] = 0x04;
	  temp2[3] = 0x02;
	  temp2[4] = 0x7F;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xFE;	//01111111 > 11111110
	  temp2[1] = 0x40;	//00000010 > 01000000
	  temp2[2] = 0x20;	//00000100 > 00100000
	  temp2[3] = 0x40;	//00000010 > 01000000
	  temp2[4] = 0xFE;	//01111111 > 11111110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "N"
    case 0x4E:
#ifdef PCB_1_00
	  temp2[0] = 0x7F;
	  temp2[1] = 0x06;
	  temp2[2] = 0x08;
	  temp2[3] = 0x30;
	  temp2[4] = 0x7F;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xFE;	//01111111 > 11111110
	  temp2[1] = 0x60;	//00000110 > 01100000
	  temp2[2] = 0x10;	//00001000 > 00010000
	  temp2[3] = 0x0C;	//00110000 > 00001100
	  temp2[4] = 0xFE;	//01111111 > 11111110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "O"
    case 0x4F:
#ifdef PCB_1_00
	  temp2[0] = 0x3E;
	  temp2[1] = 0x41;
	  temp2[2] = 0x41;
	  temp2[3] = 0x41;
	  temp2[4] = 0x3E;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x7C;	//00111110 > 01111100
	  temp2[1] = 0x82;	//01000001 > 10000010
	  temp2[2] = 0x82;	//01000001 > 10000010
	  temp2[3] = 0x82;	//01000001 > 10000010
	  temp2[4] = 0x7C;	//00111110 > 01111100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "P"
    case 0x50:
#ifdef PCB_1_00
	  temp2[0] = 0x41;
	  temp2[1] = 0x7F;
	  temp2[2] = 0x49;
	  temp2[3] = 0x09;
	  temp2[4] = 0x06;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x82;	//01000001 > 10000010
	  temp2[1] = 0xFE;	//01111111 > 11111110
	  temp2[2] = 0x92;	//01001001 > 10010010
	  temp2[3] = 0x90;	//00001001 > 10010000
	  temp2[4] = 0x60;	//00000110 > 01100000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "Q"
    case 0x51:
#ifdef PCB_1_00
	  temp2[0] = 0x1E;
	  temp2[1] = 0x21;
	  temp2[2] = 0x21;
	  temp2[3] = 0x61;
	  temp2[4] = 0x5E;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x78;	//00011110 > 01111000
	  temp2[1] = 0x84;	//00100001 > 10000100
	  temp2[2] = 0x84;	//00100001 > 10000100
	  temp2[3] = 0x86;	//01100001 > 10000110
	  temp2[4] = 0x7A;	//01011110 > 01111010
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "R"
    case 0x52:
#ifdef PCB_1_00
	  temp2[0] = 0x41;
	  temp2[1] = 0x7F;
	  temp2[2] = 0x09;
	  temp2[3] = 0x09;
	  temp2[4] = 0x76;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x82;	//01000001 > 10000010
	  temp2[1] = 0xFE;	//01111111 > 11111110
	  temp2[2] = 0x90;	//00001001 > 10010000
	  temp2[3] = 0x90;	//00001001 > 10010000
	  temp2[4] = 0x6E;	//01110110 > 01101110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break;
// Character "S"
    case 0x53:
#ifdef PCB_1_00
	  temp2[0] = 0x26;
	  temp2[1] = 0x49;
	  temp2[2] = 0x49;
	  temp2[3] = 0x49;
	  temp2[4] = 0x32;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x64;	//00100110 > 01100100
	  temp2[1] = 0x92;	//01001001 > 10010010
	  temp2[2] = 0x92;	//01001001 > 10010010
	  temp2[3] = 0x92;	//01001001 > 10010010
	  temp2[4] = 0x4C;	//00110010 > 01001100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "T"
    case 0x54:
#ifdef PCB_1_00
	  temp2[0] = 0x03;
	  temp2[1] = 0x41;
	  temp2[2] = 0x7F;
	  temp2[3] = 0x41;
	  temp2[4] = 0x03;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xC0;	//00000011 > 11000000
	  temp2[1] = 0x82;	//01000001 > 10000010
	  temp2[2] = 0xFE;	//01111111 > 11111110
	  temp2[3] = 0x82;	//01000001 > 10000010
	  temp2[4] = 0xC0;	//00000011 > 11000000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "U"
    case 0x55:
#ifdef PCB_1_00
	  temp2[0] = 0x7F;
	  temp2[1] = 0x40;
	  temp2[2] = 0x40;
	  temp2[3] = 0x40;
	  temp2[4] = 0x7F;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xFE;	//01111111 > 11111110
	  temp2[1] = 0x02;	//01000000 > 00000010
	  temp2[2] = 0x02;	//01000000 > 00000010
	  temp2[3] = 0x02;	//01000000 > 00000010
	  temp2[4] = 0xFE;	//01111111 > 11111110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "V"
    case 0x56:
#ifdef PCB_1_00
	  temp2[0] = 0x0F;
	  temp2[1] = 0x30;
	  temp2[2] = 0x40;
	  temp2[3] = 0x30;
	  temp2[4] = 0x0F;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xF0;	//00001111 > 11110000
	  temp2[1] = 0x0C;	//00110000 > 00001100
	  temp2[2] = 0x02;	//01000000 > 00000010
	  temp2[3] = 0x0C;	//00110000 > 00001100
	  temp2[4] = 0xF0;	//00001111 > 11110000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "W"
    case 0x57:
#ifdef PCB_1_00
	  temp2[0] = 0x7F;
	  temp2[1] = 0x20;
	  temp2[2] = 0x10;
	  temp2[3] = 0x20;
	  temp2[4] = 0x7F;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xFE;	//01111111 > 11111110
	  temp2[1] = 0x04;	//00100000 > 00000100
	  temp2[2] = 0x08;	//00010000 > 00001000
	  temp2[3] = 0x04;	//00100000 > 00000100
	  temp2[4] = 0xFE;	//01111111 > 11111110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "X"
    case 0x58:
#ifdef PCB_1_00
	  temp2[0] = 0x63;
	  temp2[1] = 0x14;
	  temp2[2] = 0x08;
	  temp2[3] = 0x14;
	  temp2[4] = 0x63;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xC6;	//01100011 > 11000110
	  temp2[1] = 0x28;	//00010100 > 00101000
	  temp2[2] = 0x10;	//00001000 > 00010000
	  temp2[3] = 0x28;	//00010100 > 00101000
	  temp2[4] = 0xC6;	//01100011 > 11000110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "Y"
    case 0x59:
#ifdef PCB_1_00
	  temp2[0] = 0x07;
	  temp2[1] = 0x48;
	  temp2[2] = 0x70;
	  temp2[3] = 0x48;
	  temp2[4] = 0x07;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xE0;	//00000111 > 11100000
	  temp2[1] = 0x12;	//01001000 > 00010010
	  temp2[2] = 0x0E;	//01110000 > 00001110
	  temp2[3] = 0x12;	//01001000 > 00010010
	  temp2[4] = 0xE0;	//00000111 > 11100000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "Z"
    case 0x5A:
#ifdef PCB_1_00
	  temp2[0] = 0x63;
	  temp2[1] = 0x51;
	  temp2[2] = 0x49;
	  temp2[3] = 0x45;
	  temp2[4] = 0x63;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xC6;	//01100011 > 11000110
	  temp2[1] = 0x8A;	//01010001 > 10001010
	  temp2[2] = 0x92;	//01001001 > 10010010
	  temp2[3] = 0xA2;	//01000101 > 10100010
	  temp2[4] = 0xC6;	//01100011 > 11000110
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "Inverse 1"
    case 0xF1:
#ifdef PCB_1_00
	  temp2[0] = 0xFF;
	  temp2[1] = 0xBD;
	  temp2[2] = 0x80;
	  temp2[3] = 0xBF;
	  temp2[4] = 0xFF;
	  temp2[5] = 0xFF;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xFF;	//11111111 > 11111111
	  temp2[1] = 0xBD;	//10111101 > 10111101
	  temp2[2] = 0x01;	//10000000 > 00000001
	  temp2[3] = 0xFD;	//10111111 > 11111101
	  temp2[4] = 0xFF;	//11111111 > 11111111
	  temp2[5] = 0xFF;	//11111111 > 11111111
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "Inverse 2"
    case 0xF2:
#ifdef PCB_1_00
	  temp2[0] = 0xBD;
	  temp2[1] = 0x9E;
	  temp2[2] = 0xAE;
	  temp2[3] = 0xB6;
	  temp2[4] = 0x99;
	  temp2[5] = 0xFF;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xBD;	//10111101 > 10111101
	  temp2[1] = 0x79;	//10011110 > 01111001
	  temp2[2] = 0x75;	//10101110 > 01110101
	  temp2[3] = 0x6D;	//10110110 > 01101101
	  temp2[4] = 0x99;	//10011001 > 10011001
	  temp2[5] = 0xFF;	//11111111 > 11111111
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "Inverse 3"
    case 0xF3:
#ifdef PCB_1_00
	  temp2[0] = 0xDD;
	  temp2[1] = 0xBE;
	  temp2[2] = 0xB6;
	  temp2[3] = 0xB6;
	  temp2[4] = 0xC9;
	  temp2[5] = 0xFF;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xBB;	//11011101 > 10111011
	  temp2[1] = 0x7D;	//10111110 > 01111101
	  temp2[2] = 0x6D;	//10110110 > 01101101
	  temp2[3] = 0x6D;	//10110110 > 01101101
	  temp2[4] = 0x93;	//11001001 > 10010011
	  temp2[5] = 0xFF;	//11111111 > 11111111
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "Inverse 4"
    case 0xF4:
#ifdef PCB_1_00
	  temp2[0] = 0xE7;
	  temp2[1] = 0xEB;
	  temp2[2] = 0xAD;
	  temp2[3] = 0x80;
	  temp2[4] = 0xAF;
	  temp2[5] = 0xFF;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xE7;	//11100111 > 11100111
	  temp2[1] = 0xD7;	//11101011 > 11010111
	  temp2[2] = 0xB5;	//10101101 > 10110101
	  temp2[3] = 0x01;	//10000000 > 00000001
	  temp2[4] = 0xF5;	//10101111 > 11110101
	  temp2[5] = 0xFF;	//11111111 > 11111111
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "Up Indicator"
    case 0xF5:
#ifdef PCB_1_00
	  temp2[0] = 0x30;
	  temp2[1] = 0x3C;
	  temp2[2] = 0x3E;
	  temp2[3] = 0x3C;
	  temp2[4] = 0x30;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x0C;	//00110000 > 00001100
	  temp2[1] = 0x3C;	//00111100 > 00111100
	  temp2[2] = 0x7C;	//00111110 > 01111100
	  temp2[3] = 0x3C;	//00111100 > 00111100
	  temp2[4] = 0x0C;	//00110000 > 00001100
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "Down Indicator"
    case 0xF6:
#ifdef PCB_1_00
	  temp2[0] = 0x06;
	  temp2[1] = 0x1E;
	  temp2[2] = 0x3E;
	  temp2[3] = 0x1E;
	  temp2[4] = 0x06;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0x60;	//00000110 > 01100000
	  temp2[1] = 0x78;	//00011110 > 01111000
	  temp2[2] = 0x7C;	//00111110 > 01111100
	  temp2[3] = 0x78;	//00011110 > 01111000
	  temp2[4] = 0x60;	//00000110 > 01100000
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
    // Character "Block Indicator"
    case 0xF7:
#ifdef PCB_1_00
	  temp2[0] = 0xFF;
	  temp2[1] = 0xFF;
	  temp2[2] = 0xFF;
	  temp2[3] = 0xFF;
	  temp2[4] = 0xFF;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xFF;	//11111111 > 11111111
	  temp2[1] = 0xFF;	//11111111 > 11111111
	  temp2[2] = 0xFF;	//11111111 > 11111111
	  temp2[3] = 0xFF;	//11111111 > 11111111
	  temp2[4] = 0xFF;	//11111111 > 11111111
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 


	// Character UNKNOWN
    default:
#ifdef PCB_1_00
	  temp2[0] = 0xFF;
	  temp2[1] = 0xFF;
	  temp2[2] = 0xFF;
	  temp2[3] = 0xFF;
	  temp2[4] = 0xFF;
	  temp2[5] = 0x00;
	  temp2[6] = 0x00; 
#else
	  temp2[0] = 0xFF;	//11111111 > 11111111
	  temp2[1] = 0xFF;	//11111111 > 11111111
	  temp2[2] = 0xFF;	//11111111 > 11111111
	  temp2[3] = 0xFF;	//11111111 > 11111111
	  temp2[4] = 0xFF;	//11111111 > 11111111
	  temp2[5] = 0x00;	//00000000 > 00000000
	  temp2[6] = 0x00; 	//00000000 > 00000000
#endif
	  break; 
  }
  //long_delay(1);
#ifdef PCB_1_00
  for (x=0; x<6; x++ )
  {
    if (underline > 0) {
      if (save_char > 49) {
  	    col_offset = save_char - 50;
  	    temp1 = Set_Col_Addr + col_offset;	  // Prepare command for transmission.
  	    lcd_comm2(GR2, RSCOMMAND, temp1);	  // Send Command to LCD Device 2.
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
//      wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
        lcd_comm2(GR2, RSDATA, (temp2[x] + 0x80));  // Send DATA to LCD Device 2.
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
//      wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
	  }
	  else {
	  	col_offset = save_char;
	  	temp1 = Set_Col_Addr + col_offset;	  // Prepare command for transmission.
	  	lcd_comm2(GR1, RSCOMMAND, temp1);	  // Send Command to LCD Device 2.
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
//      wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
	  	lcd_comm2(GR1, RSDATA, (temp2[x] + 0x80));  // Send DATA to LCD Device 2.
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
//      wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
	  }
	}
	else {
      if (save_char > 49) {
        col_offset = save_char - 50;
        temp1 = Set_Col_Addr + col_offset;	  // Prepare command for transmission.
        lcd_comm2(GR2, RSCOMMAND, temp1);	  // Send Command to LCD Device 2.
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
//      wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
        lcd_comm2(GR2, RSDATA, temp2[x]);  // Send DATA to LCD Device 2.
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
//      wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
	  }
	  else {
		col_offset = save_char;
		temp1 = Set_Col_Addr + col_offset;	  // Prepare command for transmission.
		lcd_comm2(GR1, RSCOMMAND, temp1);	  // Send Command to LCD Device 2.
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
//      wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
        lcd_comm2(GR1, RSDATA, temp2[x]);  // Send DATA to LCD Device 2.
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
//      wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
	  }
	}
    save_char++;
  }
#else
  //save_char += 3;
//  for (x=0; x<6; x++ )
  for (x=5; x>=0; x-- )
  {
    if (underline > 0) {
      if (save_char > 49) {
  	    col_offset = save_char - 50;
  	    temp1 = Set_Col_Addr + col_offset;	  // Prepare command for transmission.
  	    lcd_comm2(GR2, RSCOMMAND, temp1);	  // Send Command to LCD Device 2.
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
        wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
#ifdef PCB_1_00
	  	lcd_comm2(GR2, RSDATA, reverseChar(temp2[x] + 0x80));  // Send DATA to LCD Device 2.
#else
	  	lcd_comm2(GR2, RSDATA, reverseChar(temp2[x] + 0x01));  // Send DATA to LCD Device 2.
#endif
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
        wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
	  }
	  else {
	  	col_offset = save_char;
	  	temp1 = Set_Col_Addr + col_offset;	  // Prepare command for transmission.
	  	lcd_comm2(GR1, RSCOMMAND, temp1);	  // Send Command to LCD Device 2.
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
//        wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
#ifdef PCB_1_00
	  	lcd_comm2(GR1, RSDATA, reverseChar(temp2[x] + 0x80));  // Send DATA to LCD Device 2.
#else
	  	lcd_comm2(GR1, RSDATA, reverseChar(temp2[x] + 0x01));  // Send DATA to LCD Device 2.
#endif
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
        wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
	  }
	}
	else {
      if (save_char > 49) {
        col_offset = save_char - 50;
        temp1 = Set_Col_Addr + col_offset;	  // Prepare command for transmission.
        lcd_comm2(GR2, RSCOMMAND, temp1);	  // Send Command to LCD Device 2.
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
        wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
        lcd_comm2(GR2, RSDATA, reverseChar(temp2[x]));  // Send DATA to LCD Device 2.
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
        wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
	  }
	  else {
		col_offset = save_char;
		temp1 = Set_Col_Addr + col_offset;	  // Prepare command for transmission.
		lcd_comm2(GR1, RSCOMMAND, temp1);	  // Send Command to LCD Device 2.
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
//        wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
        lcd_comm2(GR1, RSDATA, reverseChar(temp2[x]));  // Send DATA to LCD Device 2.
// Wait For Busy Flag to Clear. NOTE....In ATMEGA128...This test causes LCD not to work on Left Side.
        wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
	  }
	}
    save_char++;
  }
#endif
}
#endif

//*****************************************************************************
//*
//* routine: debug1
//* Date:    December 13, 2003
//* Author:  Ralph Pruitt
//* This routine sends the passed msg to Line 4 of the LCD Display.
//*
//* Input:
//*		  String:	  		   Or Pointer to String to transmit.
//*
//*****************************************************************************
#ifdef DEBUGGR
void debug1(unsigned char s)
{
  CLI();
//  if (count<sizeof(debug_buffr)) {
  debug_buffr[deb_count++] = s;
  if (deb_count >=509)
    deb_count = 0;
//  }
  SEI();
}
#endif

//*****************************************************************************
//*
//* routine: factory_screen
//* Date:    January 1, 2004
//* Author:  Ralph Pruitt
//* Display the factory Screen on a 20x4Line LCD Screen.
//*
//*****************************************************************************
void factory_screen(void)
{
  char tempstr[18];
  char tempstr2[18];

  clear_screen();							// Clear Screen.
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**                Factory SCREEN                              *\n");

  set_cursor(LINE1, 0, NOCURSOR);
  //.............."1234567890123456"	// Program 1 Display String.
  //.............."  PLM PLS 1.00  "	// Program 1 Display String.
  strcpy(tempstr, "  PLM PLS ");
  strcpy(tempstr2, (const char*)VERSIONNUM);
  strcat(tempstr, tempstr2);
  strcpy(tempstr2, "  ");
  strcat(tempstr, tempstr2);
  write_lcd(tempstr);
  set_cursor(LINE2, 0, NOCURSOR);
  //.............."1234567890123456"	// Program 1 Display String.
  //.............."  C: 03/05/15   "	// Program 1 Display String.
  strcpy(tempstr, "  C: ");
  strcpy(tempstr2, (const char*)RELDATE);
  strcat(tempstr, tempstr2);
  strcpy(tempstr2, "   ");
  strcat(tempstr, tempstr2);
  write_lcd(tempstr);
  set_cursor(LINE3, 0, NOCURSOR);
  //.............."1234567890123456"	// Program 1 Display String.
  strcpy(tempstr, "  Property of   ");
  write_lcd(tempstr);
  set_cursor(LINE4, 0, NOCURSOR);
  //.............."1234567890123456"	// Program 1 Display String.
  strcpy(tempstr, "    CLT LLC.    ");
  write_lcd(tempstr);
  printf2("\n***************************************************************\n\n\n");
}

//*****************************************************************************
//*
//* routine: boot_screen
//* Date:    January 1, 2004
//* Author:  Ralph Pruitt
//* Display the Boot Screen on a 20x4Line LCD Screen.
//*
//*****************************************************************************
void boot_screen(void)
{
  char tempstr[18];
  char tempstr2[18];
  int numDays;


  clear_screen();							// Clear Screen.
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**                Boot SCREEN                                 *\n");

  set_cursor(LINE1, 0, NOCURSOR);
#if LEASEOP
  EEPROM_READ((int)&eopmin_lmt, opmin_lmt);	 		 // Read the data to EEPROM.
  if (opmin_lmt == 0) {
    strcpy(tempstr, "****************");
  }
  else {
    WDR(); //this prevents a timout on enabling
    strcpy(tempstr, "**");
    str_chg_long3(tempstr2, OPMIN_SIZE, opmin_lmt);
    strcat(tempstr, tempstr2);
    strcat(tempstr, "lmt*");
  }
#else
  strcpy(tempstr, "****************");
#endif
  write_lcd(tempstr);
  set_cursor(LINE2, 0, NOCURSOR);
  //................"1234567890123456"	// Program 1 Display String.
  //................"* PLM PLS 1.00  "	// Program 1 Display String.
  strcpy(tempstr, "* PLM PLS ");
  strcpy(tempstr2, (const char*)VERSIONNUM);
  strcat(tempstr, tempstr2);
  strcpy(tempstr2, " *");
  strcat(tempstr, tempstr2);
  write_lcd(tempstr);
  set_cursor(LINE3, 0, NOCURSOR);
//................"1234567890123456"	// Program 1 Display String.
//................"* C: 03/05/15  *"	// Program 1 Display String.
  strcpy(tempstr, "* C: ");
  strcpy(tempstr2, (const char*)RELDATE);
  strcat(tempstr, tempstr2);
  strcpy(tempstr2, "  *");
  strcat(tempstr, tempstr2);
  write_lcd(tempstr);
  set_cursor(LINE4, 0, NOCURSOR);
  opmin_cnt = eopmin_cnt;								 // Read the data from Data Flash.
  WDR(); //this prevents a timout on enabling
  if ((opMode == 0) || (opMode == 3))
  {
	  strcpy(tempstr, "***");
	  str_chg_long3(tempstr2, OPMIN_SIZE, opmin_cnt);
	  strcat(tempstr, tempstr2);
	  strcat(tempstr, "***");
  }
  else if (opMode == 1)
  {
	  strcpy(tempstr, "*");
	  // Calculate Number of Days.
	  numDays = CalcLeaseDays();
	  if (numDays == -1)
	  {
		  strcpy(tempstr2, "** EXPIRED ***");
	  }
	  else
	  {
		  sprintf(tempstr2," DEMO %03dDays ", numDays);
	  }
	  strcat(tempstr, tempstr2);
	  strcat(tempstr, "*");
  }
  else if (opMode == 2)
  {
	  strcpy(tempstr, "*");
	  // Calculate Number of Days.
	  numDays = CalcLeaseDays();
	  if (numDays == -1)
	  {
		  strcpy(tempstr2, "** EXPIRED ***");
	  }
	  else
	  {
		  sprintf(tempstr2,"LEASE %03dDays ", numDays);
	  }
	  strcat(tempstr, tempstr2);
	  strcat(tempstr, "*");
  }
  write_lcd(tempstr);
  printf2("\n***************************************************************\n\n\n");
}

//*****************************************************************************
//*
//* routine: TL_Armed_screen
//* Date:    February 28, 2015
//* Author:  Ralph Pruitt
//* Display Timed Laser Screen on a 20x4Line LCD Screen.
//*
//*****************************************************************************
void TL_Armed_screen(void)
{
  char tempstr[18];

  clear_screen();							// Clear Screen.
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**          Timed Laser Arm SCREEN                            *\n");

  set_cursor(LINE1, 0, NOCURSOR);
  strcpy(tempstr, "****************");
  write_lcd(tempstr);
  set_cursor(LINE2, 0, NOCURSOR);
  strcpy(tempstr, "Timed Laser ARM ");
  write_lcd(tempstr);
  set_cursor(LINE3, 0, NOCURSOR);
  strcpy(tempstr, "  Press START   ");
  write_lcd(tempstr);
  set_cursor(LINE4, 0, NOCURSOR);
  strcpy(tempstr, "****************");
  write_lcd(tempstr);

  printf2("\n***************************************************************\n\n\n");
}

//*****************************************************************************
//*
//* routine: Laser_Armed_screen
//* Date:    February 28, 2015
//* Author:  Ralph Pruitt
//* Display Laser On Screen on a 20x4Line LCD Screen.
//*
//*****************************************************************************
void Laser_Armed_screen(void)
{
  char tempstr[18];

  clear_screen();							// Clear Screen.
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**             Laser On Arm SCREEN                            *\n");

  set_cursor(LINE1, 0, NOCURSOR);
  strcpy(tempstr, "****************");
  write_lcd(tempstr);
  set_cursor(LINE2, 0, NOCURSOR);
  strcpy(tempstr, " Laser On ARM   ");
  write_lcd(tempstr);
  set_cursor(LINE3, 0, NOCURSOR);
  strcpy(tempstr, "  Press START   ");
  write_lcd(tempstr);
  set_cursor(LINE4, 0, NOCURSOR);
  strcpy(tempstr, "****************");
  write_lcd(tempstr);

  printf2("\n***************************************************************\n\n\n");
}

//*****************************************************************************
//*
//* routine: Pulse_Armed_screen
//* Date:    February 28, 2015
//* Author:  Ralph Pruitt
//* Display Laser Pulse Screen on a 20x4Line LCD Screen.
//*
//*****************************************************************************
void Pulse_Armed_screen(void)
{
  char tempstr[18];

  clear_screen();							// Clear Screen.
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**          Laser Pulse Arm SCREEN                            *\n");

  set_cursor(LINE1, 0, NOCURSOR);
  strcpy(tempstr, "****************");
  write_lcd(tempstr);
  set_cursor(LINE2, 0, NOCURSOR);
  strcpy(tempstr, "Laser Pulse ARM ");
  write_lcd(tempstr);
  set_cursor(LINE3, 0, NOCURSOR);
  strcpy(tempstr, "Press/Hold START");
  write_lcd(tempstr);
  set_cursor(LINE4, 0, NOCURSOR);
  strcpy(tempstr, "****************");
  write_lcd(tempstr);

  printf2("\n***************************************************************\n\n\n");
}

//*****************************************************************************
//*
//* routine: PBFEntryScrn
//* Date:    May 25, 2015
//* Author:  Ralph Pruitt
//* Display the PBF Entry Screen for valid PBF code to be entered.
//*
//*****************************************************************************
void PBFEntryScrn(void)
{
  char tempstr[18];

  clear_screen();							// Clear Screen.
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**                PBF Entry SCREEN                            *\n");

  set_cursor(LINE1, 0, NOCURSOR);
  strcpy(tempstr, "Enter Code Below");
  write_lcd(tempstr);
  set_cursor(LINE2, 0, NOCURSOR);
  strcpy(tempstr, "? ");
  write_lcd(tempstr);
  underline = 1;
#ifndef PCB_1_00
  set_cursor(LINE2,1, BLINK);
#endif
  write_lcd(lease_str);
  underline = 0;
#ifndef PCB_1_00
  set_cursor(LINE2, 0, NOCURSOR);
#endif
  strcpy(tempstr, " ");
  write_lcd(tempstr);

  set_cursor(LINE3, 0, NOCURSOR);
  strcpy(tempstr, " Call Ph Below  ");
  write_lcd(tempstr);

  set_cursor(LINE4, 0, NOCURSOR);
  strcpy(tempstr, "  866-694-6116  ");
  write_lcd(tempstr);
  printf2("\n***************************************************************\n\n\n");
}

//*****************************************************************************
//*
//* routine: PBFErrorScrn
//* Date:    May 23, 2015
//* Author:  Ralph Pruitt
//* Display Error Screen and show Date and SN.
//* INPUT:
//*		int code: 0 - This screen shown when expired PBF Code.
//*               1 - This screen shown when Bad PBF Code entered.
//*
//*****************************************************************************
void PBFErrorScrn(int code)
{
  char tempstr[18];
  int month, day, year;

  // Get current date and time.
  getDate(&month, &day, &year);

  clear_screen();							// Clear Screen.
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**                   PBFErrorScrn SCREEN                      *\n");

  set_cursor(LINE1, 0, NOCURSOR);
  if (code>0)
	  strcpy(tempstr, "Bad Code Entered");
  else
  	  strcpy(tempstr, "Expired Lse/Demo");
  write_lcd(tempstr);

  set_cursor(LINE2, 0, NOCURSOR);
  sprintf(tempstr, "SN: %09d", serial_number);
  write_lcd(tempstr);

  set_cursor(LINE3, 0, NOCURSOR);
  sprintf(tempstr, "Date: %02d/%02d/%04d", month, day, year);
  write_lcd(tempstr);

  set_cursor(LINE4, 0, NOCURSOR);
  strcpy(tempstr, " SELECT to cont ");
  write_lcd(tempstr);

  printf2("\n***************************************************************\n\n\n");
}

//*****************************************************************************
//*
//* routine: DateEntryScrn
//* Date:    December 3, 2017
//* Author:  Ralph Pruitt
//* Display the Date Entry Screen for Date to be entered.
//*
//*****************************************************************************
void DateEntryScrn(void)
{
  char tempstr[18];
  //int x;

  clear_screen();							// Clear Screen.
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**                Date Entry SCREEN                           *\n");

  set_cursor(LINE1, 0, NOCURSOR);
  strcpy(tempstr, "    New Date#   ");
  write_lcd(tempstr);
#ifndef PCB_1_00
  set_cursor(LINE2,11, NOCURSOR);
#else
  set_cursor(LINE2, 0, NOCURSOR);
#endif
  //strcpy(tempstr, "                ");
  strcpy(tempstr, "OLD:");
  write_lcd(tempstr);
  // Clear tempstr for next operation.
  //for (x=0; x<18; x++)
  //	  tempstr[x] = 0;
  //str_chg_long3(tempstr, 9, serial_number);
  //x = strlen(tempstr);
  //tempstr[x-2] = 0;
  strcpy(tempstr, getDateStr());
#ifndef PCB_1_00
  set_cursor(LINE2, 1, NOCURSOR);
#endif
  write_lcd(tempstr);
  set_cursor(LINE3, 0, NOCURSOR);
  strcpy(tempstr, "? ");
  write_lcd(tempstr);
  underline = 1;
#ifndef PCB_1_00
  set_cursor(LINE3, 2, BLINK);
#endif
  write_lcd(lease_str);
  underline = 0;
  strcpy(tempstr, " ");
#ifndef PCB_1_00
  set_cursor(LINE3,0, NOCURSOR);
#endif
  write_lcd(tempstr);
  set_cursor(LINE4, 0, NOCURSOR);
  strcpy(tempstr, "                ");
  write_lcd(tempstr);
  printf2("\n***************************************************************\n\n\n");
}

//*****************************************************************************
//*
//* routine: TimeEntryScrn
//* Date:    December 12, 2010
//* Author:  Ralph Pruitt
//* Display the Time Entry Screen for Time to be entered.
//*
//*****************************************************************************
void TimeEntryScrn(void)
{
  char tempstr[18];
  //int x;

  clear_screen();							// Clear Screen.
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**                Time Entry SCREEN                           *\n");

  set_cursor(LINE1, 0, NOCURSOR);
  strcpy(tempstr, "    New Time#   ");
  write_lcd(tempstr);
#ifndef PCB_1_00
  set_cursor(LINE2,11, NOCURSOR);
#else
  set_cursor(LINE2, 0, NOCURSOR);
#endif
  //strcpy(tempstr, "                ");
  strcpy(tempstr, "OLD:");
  write_lcd(tempstr);
  // Clear tempstr for next operation.
  //for (x=0; x<18; x++)
  //tempstr[x] = 0;
  //str_chg_long3(tempstr, 9, serial_number);
  //x = strlen(tempstr);
  //tempstr[x-2] = 0;
  strcpy(tempstr, getTimeStr());
#ifndef PCB_1_00
  set_cursor(LINE2, 2, NOCURSOR);
#endif
  write_lcd(tempstr);
  set_cursor(LINE3, 0, NOCURSOR);
  strcpy(tempstr, "? ");
  write_lcd(tempstr);
  underline = 1;
#ifndef PCB_1_00
  set_cursor(LINE3, 2, BLINK);
#endif
  write_lcd(lease_str);
  underline = 0;
  strcpy(tempstr, " ");
#ifndef PCB_1_00
  set_cursor(LINE3,0, NOCURSOR);
#endif
  write_lcd(tempstr);
  set_cursor(LINE4, 0, NOCURSOR);
  strcpy(tempstr, "                ");
  write_lcd(tempstr);
  printf2("\n***************************************************************\n\n\n");
}

//*****************************************************************************
//*
//* routine: SerialNumScrn
//* Date:    December 12, 2010
//* Author:  Ralph Pruitt
//* Display the Serial Number Entry Screen for Serial Number to be entered.
//*
//*****************************************************************************
void SerialNumScrn(void)
{
  char tempstr[18];
  int x;

  clear_screen();							// Clear Screen.
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**                Serial Num SCREEN                           *\n");

  set_cursor(LINE1, 0, NOCURSOR);
  strcpy(tempstr, "   New Serial#  ");
  write_lcd(tempstr);
#ifndef PCB_1_00
  set_cursor(LINE2,11, NOCURSOR);
#else
  set_cursor(LINE2, 0, NOCURSOR);
#endif
  //strcpy(tempstr, "                ");
  strcpy(tempstr, "OLD:");
  write_lcd(tempstr);
  // Clear tempstr for next operation.
  for (x=0; x<18; x++)
	  tempstr[x] = 0;
  str_chg_long3(tempstr, 9, serial_number);
  x = strlen(tempstr);
  //tempstr[x-2] = 0;
#ifndef PCB_1_00
  set_cursor(LINE2, 2, NOCURSOR);
#endif
  write_lcd(tempstr);
  set_cursor(LINE3, 0, NOCURSOR);
  strcpy(tempstr, "? ");
  write_lcd(tempstr);
  underline = 1;
#ifndef PCB_1_00
  set_cursor(LINE3, 2, BLINK);
#endif
  write_lcd(lease_str);
  underline = 0;
  strcpy(tempstr, " ");
#ifndef PCB_1_00
  set_cursor(LINE3,0, NOCURSOR);
#endif
  write_lcd(tempstr);
  set_cursor(LINE4, 0, NOCURSOR);
  strcpy(tempstr, "                ");
  write_lcd(tempstr);
  printf2("\n***************************************************************\n\n\n");
}

//*****************************************************************************
//*
//* routine: TimeScrn
//* Date:    May 23, 2015
//* Author:  Ralph Pruitt
//* Display the Time and Date from the RTC.
//*
//*****************************************************************************
void TimeScrn(void)
{
  char tempstr[18];
  int hour, minute, second, month, day, year;

  // Get current date and time.
  getTime(&hour, &minute, &second);
  getDate(&month, &day, &year);

  clear_screen();							// Clear Screen.
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**                   Time SCREEN                              *\n");

  set_cursor(LINE1, 0, NOCURSOR);
  sprintf(tempstr, "Time: %02d:%02d:%02d", hour, minute, second);
  write_lcd(tempstr);

  set_cursor(LINE3, 0, NOCURSOR);
  sprintf(tempstr, "Date: %02d/%02d/%04d", month, day, year);
  write_lcd(tempstr);
  printf2("\n***************************************************************\n\n\n");
}

//*****************************************************************************
//*
//* routine: MonitorScrn
//* Date:    May 23, 2015
//* Author:  Ralph Pruitt
//* Display the Monitor Title and Instructions to exit mode.
//*
//*****************************************************************************
void MonitorScrn(void)
{
  char tempstr[18];

  clear_screen();							// Clear Screen.
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**                Monitor SCREEN                           *\n");

  set_cursor(LINE1, 0, NOCURSOR);
  strcpy(tempstr, " Monitor Screen ");
  write_lcd(tempstr);
  set_cursor(LINE3, 0, NOCURSOR);
  strcpy(tempstr, " RESET to Exit ");
  write_lcd(tempstr);
  printf2("\n***************************************************************\n\n\n");
}

#if LEASEOP
//*****************************************************************************
//*
//* routine: KeyEntryScrn
//* Date:    December 11, 2010
//* Author:  Ralph Pruitt
//* Display the Key Entry Screen for Key to be entered.
//*
//*****************************************************************************
void KeyEntryScrn(void)
{
  char tempstr[18];
  char tempstr2[18];
  int x;

  clear_screen();							// Clear Screen.
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**                Serial Num SCREEN                           *\n");

  set_cursor(LINE1, 0, NOCURSOR);
  strcpy(tempstr, " Limit Reached. ");
  write_lcd(tempstr);
  set_cursor(LINE2, 0, NOCURSOR);
//  strcpy(tempstr, " 303-570-3206  ");
  strcpy(tempstr, " ");
  strcpy(tempstr2, (const char*)PHONENUM);
  strcat(tempstr, tempstr2);
  strcpy(tempstr2, "   ");
  strcat(tempstr, tempstr2);
  write_lcd(tempstr);
  
  write_lcd(tempstr);
  set_cursor(LINE3, 0, NOCURSOR);
  strcpy(tempstr, " More Minutes.  ");
  write_lcd(tempstr);
  set_cursor(LINE4, 0, NOCURSOR);
  strcpy(tempstr, "? ");
  write_lcd(tempstr);
  underline = 1;
  write_lcd(lease_str);
  underline = 0;
  strcpy(tempstr, "  ");
  write_lcd(tempstr);
  printf2("\n***************************************************************\n\n\n");
}
#endif

//*****************************************************************************
//*
//* routine: main_screen
//* Date:    January 2, 2004
//* Author:  Ralph Pruitt
//* Display the Main Screen on a 20x4Line LCD Screen. Note that this involves
//* reading each of the key variables and updating their information on the screen.
//* This information includes the following:
//* 	 Timer Settings:
//*		 	   Minutes:
//*			   		  unsigned char			tmr_min;
//*					  char	   				tmr_minstr[2];
//*			   Seconds:
//*	   		  		  unsigned char			tmr_sec;
//*					  char	   				tmr_secstr[2];
//*			   Battery Level: 
//*			   		  char	  	  			Bat_Lvl[3];
//*			   Laser1 Setting:
//*			   		  unsigned long 		lser1_time;
//*					  char	   				lser1_strng[7];
//*			   Laser2 Setting:
//*			   		  unsigned long 		lser2_time;
//*					  char	   				lser2_strng[7];
//*			   Laser3 Setting:
//*			   		  unsigned long 		lser3_time;
//*					  char	   				lser3_strng[7];
//*			   Laser4 Setting:
//*			   		  unsigned long 		lser4_time;
//*					  char	   				lser4_strng[7];
//*			   Current Program Number:
//*			   		  unsigned char			prog_num;
//*					  char	   				prog_str[3];
//*
//*****************************************************************************
void main_screen(void)
{
  clear_screen();							// Clear Screen.
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**                      Main SCREEN                           *\n");

  remain_screen();							// Display Main Screen.
  printf2("\n***************************************************************\n\n\n");
}

//*****************************************************************************
//*
//* routine: remain_screen
//* Date:    January 2, 2004
//* Author:  Ralph Pruitt
//* Display the Main Screen on a 20x4Line LCD Screen without a Clear Screen. Note that this involves
//* reading each of the key variables and updating their information on the screen.
//* This information includes the following:
//* 	 Timer Settings:
//*		 	   Minutes:
//*			   		  unsigned char			tmr_min;
//*					  char	   				tmr_minstr[2];
//*			   Seconds:
//*	   		  		  unsigned char			tmr_sec;
//*					  char	   				tmr_secstr[2];
//*			   Battery Level: 
//*			   		  char	  	  			Bat_Lvl[3];
//*			   Laser1 Setting:
//*			   		  unsigned long 		lser1_time;
//*					  char	   				lser1_strng[7];
//*			   Laser2 Setting:
//*			   		  unsigned long 		lser2_time;
//*					  char	   				lser2_strng[7];
//*			   Laser3 Setting:
//*			   		  unsigned long 		lser3_time;
//*					  char	   				lser3_strng[7];
//*			   Laser4 Setting:
//*			   		  unsigned long 		lser4_time;
//*					  char	   				lser4_strng[7];
//*			   Current Program Number:
//*			   		  unsigned char			prog_num;
//*					  char	   				prog_str[3];
//*
//*****************************************************************************
void remain_screen(void)
{
  char tempstr[18];
  char time_str[12];
  unsigned char save_min, save_sec;
  int  tempvar;
  char tempstr2[4];
  unsigned char temp1;
  struct laser_entry *data1;
  
  // Printf commands
  printf2("***************************************************************\n");
  printf2("**                    ReMain SCREEN                           *\n");
  printf2("***************************************************************\n");

  // Force read of Current Program Laser Settings.
  if ((lsr_update_flg == 0) &&
      (mode != Program) &&
	  (mode != Build_Prog) &&
	  (macro_flg == 0) &&
	  ((prog_num < SWEEP_STRT) || (prog_num > SWEEP_END)))
  {
    short_delay(0x10);
    quick_laser(prog_num);
    //init_laser(prog_num, INITIALIZE);
  }
  else {
    short_delay(0x10);
    Delay();
  }

  // Time to convert numbers to strings
  // Test for Macros and display them instead of tmr_min.....
  if ((macro_flg == 0) &&
     (((prog_num >= CSTMSUPR_STRT) && (prog_num <= CSTMSUPR_REND)) ||
      ((prog_num >= USERSUPR_STRT) && (prog_num <= USERSUPR_REND)))) {
    // Save Timers.
    save_min = tmr_min;
	save_sec = tmr_sec;
	// Load timers from entry 0 of Macro.
	tmr_min = macro1.macro1->mac_entry[0].Time.minutes;
    tmr_sec = macro1.macro1->mac_entry[0].Time.seconds;
    // Convert Timer values to strings.
    str_chg_char(tmr_minstr, 2, tmr_min, ZEROS);
    str_chg_char(tmr_secstr, 2, tmr_sec, ZEROS);
    // Restore Timers.
    tmr_min = save_min;
	tmr_sec = save_sec;
  }
  else {  
    str_chg_char(tmr_minstr, 2, tmr_min, ZEROS);
    str_chg_char(tmr_secstr, 2, tmr_sec, ZEROS);
  }
  // If lsr_update_flg is set we are loading new values...Don't Change!!!
  if (lsr_update_flg == 0) {
    // If alsr_update_flg is set...We are hardcoding new numbers via entry,
	// and not using the EEPROM to recall values.
    if (alsr_update_flg == 1) {
      str_chg_long2(lser1_strng, FREQ_STR_LEN+1, laser1_disp);
      str_chg_long2(lser2_strng, FREQ_STR_LEN+1, laser2_disp);
      str_chg_long2(lser3_strng, FREQ_STR_LEN+1, laser3_disp);
      str_chg_long2(lser4_strng, FREQ_STR_LEN+1, laser4_disp);
	}
	else {
      str_chg_long(lser1_strng, FREQ_STR_LEN+1, laser1_disp);
      str_chg_long(lser2_strng, FREQ_STR_LEN+1, laser2_disp);
      str_chg_long(lser3_strng, FREQ_STR_LEN+1, laser3_disp);
      str_chg_long(lser4_strng, FREQ_STR_LEN+1, laser4_disp);
	}
  }
  lser1_strng[FREQ_STR_LEN] = 0x00;
  lser2_strng[FREQ_STR_LEN] = 0x00;
  lser3_strng[FREQ_STR_LEN] = 0x00;
  lser4_strng[FREQ_STR_LEN] = 0x00;
#if sixdigit
  str_chg_ulong(prog_str, 6, prog_num, ZEROS);
#else
  str_chg_int(prog_str, 3, prog_num, ZEROS);
#endif
  
  // Lets Determine Battery Level.
  strcpy(Bat_Lvl, "????");
  strcpy(Bat_Lvl, Battery_Test());
    
  // Build LCD Screen.
#ifdef PCB_1_00
  set_cursor(LINE1, 0, NOCURSOR);
#else
  set_cursor(LINE1,13, NOCURSOR);
#endif
  sprintf(time_str,"%s:%s|%s", tmr_minstr, tmr_secstr, Battery_Level());
  Save_Timer(time_str);
  strcpy(tempstr, "Tm:");
  write_lcd(tempstr);
  if (mode == Time_Value)
    underline = 1;
#ifndef PCB_1_00
  set_cursor(LINE1,11, NOCURSOR);
#endif
  write_lcd(tmr_minstr);
  strcpy(tempstr, ":");
#ifndef PCB_1_00
  set_cursor(LINE1,10, NOCURSOR);
#endif
  write_lcd(tempstr);
#ifndef PCB_1_00
  set_cursor(LINE1,8, NOCURSOR);
#endif
  write_lcd(tmr_secstr);
  underline = 0;
#ifndef PCB_1_00
  set_cursor(LINE1,4, NOCURSOR);
#endif
  strcpy(tempstr, "   E");
  write_lcd(tempstr);
#ifndef PCB_1_00
  set_cursor(LINE1,1, NOCURSOR);
#endif
  write_lcd(Bat_Lvl);
#ifndef PCB_1_00
  set_cursor(LINE1,0, NOCURSOR);
  strcpy(tempstr, "F");
#else
  strcpy(tempstr, "F ");
#endif
  write_lcd(tempstr);
  set_cursor(LINE2, 0, NOCURSOR);
  data1 = read_entry(prog_num);			// Read Current Mode Entry.

  if (((prog_num >= CSTMSUPR_STRT) && (prog_num <= CSTMSUPR_REND)) ||
      ((prog_num >= USERSUPR_STRT) && (prog_num <= USERSUPR_REND))) {
	strcpy(tempstr, macro1.macro1->string1);
	write_lcd(tempstr);
    set_cursor(LINE3, 0, NOCURSOR);
	if (macro_flg == 3) {
	  sprintf(tempstr, "-Wait-Step %02d ", (macro1.macro_step+1));
	  //strcpy(tempstr, " -Wait-Step ");
	  //write_lcd(tempstr);
      //str_chg_int(tempstr, 2, (macro1.macro_step+1), ZEROS);
	  write_lcd(tempstr);
	  //strcpy(tempstr, " ");
	  //write_lcd(tempstr);
	}
	else if (macro1.protocol_save != SPACE_VAL) {
          data1 = read_entry(macro1.protocol_save);			// Read Current Mode Entry.
          strcpy(tempstr, data1->string1);
	  write_lcd(tempstr);
	}
	else {
	  if (macro1.macro1->num_entries == 0) {
	    strcpy(tempstr, "               ");
	    write_lcd(tempstr);
	  }
	  else if (macro1.macro_step == macro1.macro1->num_entries) {
	    strcpy(tempstr, "  --COMPLETE-- ");
	    write_lcd(tempstr);
      }	
	  else {
	    strcpy(tempstr, " -Wait-Step ");
	    write_lcd(tempstr);
        str_chg_int(tempstr, 2, (macro1.macro_step+1), ZEROS);
	    write_lcd(tempstr);
	    strcpy(tempstr, " ");
	    write_lcd(tempstr);
	  }
	}
  }
  else if ((prog_num >= SWEEP_STRT) && (prog_num <= SWEEP_REND)) {
    if (sweep1.sweep_ptr == 0) {
      strcpy(tempstr, "                ");
	  write_lcd(tempstr);
	}
	else {
      switch (sweep1.sweep_ptr) {	   // Switch Variable Pointer to Display Data Correctly.
  		case 0:					   // Lower Sweep Limit.
          strcpy(tempstr, "Lower Sweep Freq");
	      write_lcd(tempstr);
		  break;
  		case 1:					   // Sweep Frequency 1.
  		case 2:					   // Sweep Frequency 2.
  		case 3:					   // Sweep Frequency 3.
  		case 4:					   // Sweep Frequency 4.
  		case 5:					   // Sweep Frequency 5.
  		case 6:					   // Sweep Frequency 6.
  		case 7:					   // Sweep Frequency 7.
  		case 8:					   // Sweep Frequency 8.
  		case 9:					   // Sweep Frequency 9.
  		case 10:				   // Sweep Frequency 10.
  		case 11:				   // Sweep Frequency 11.
  		case 12:				   // Sweep Frequency 12.
  		case 13:				   // Sweep Frequency 13.
  		case 14:				   // Sweep Frequency 14.
  		case 15:				   // Sweep Frequency 15.
          strcpy(tempstr, "  Sweep Freq ");
	      write_lcd(tempstr);
		  tempvar = sweep1.sweep_ptr;
		  itoa(tempstr2, tempvar, 10);
		  write_lcd(tempstr2); 		  
          strcpy(tempstr, "  ");
	      write_lcd(tempstr);
		  break;
  		case 16:				   // Final Sweep Limit.
          strcpy(tempstr, "Final Sweep Freq");
	      write_lcd(tempstr);
		  break;
  	  }
      // OK...Now show Sweep direction
      set_cursor(LINE3, 0, NOCURSOR);
      if (sweep1.sweep_dir == 0) { 
        // Show Up Direction.
        temp1 = 0xf5;
      }
      else {
        // Show Down Direction.
        temp1 = 0xf6;
      }
      write_char(temp1);
	}
    set_cursor(LINE3, 0, NOCURSOR);
    strcpy(tempstr,"  Sweep Function");
    write_lcd(tempstr);
  }
  else if (data1->entry_flg > 0) {
    strcpy(tempstr, "                ");
	write_lcd(tempstr);
    set_cursor(LINE3, 0, NOCURSOR);
    strcpy(tempstr, "                ");
	write_lcd(tempstr);
    set_cursor(LINE3, 0, NOCURSOR);
    strcpy(tempstr, data1->string1);
	write_lcd(tempstr);
  }
  else {
#ifdef CLW
	    if ((prog_num > CUSTOM4_END) && (prog_num <= USER_REND)) {
#else
    if ((prog_num > CUSTOM_END) && (prog_num <= USER_REND)) {
#endif
    sprintf(tempstr, "1- %s    ", lser1_strng);
    //strcpy(tempstr, "1- ");
    //write_lcd(tempstr);
    //write_lcd(lser1_strng);
    //strcpy(tempstr, "     ");
    write_lcd(tempstr);
  	set_cursor(LINE3, 0, NOCURSOR);
  	sprintf(tempstr, "2- %s    ", lser2_strng);
    //strcpy(tempstr, "2- ");
    //write_lcd(tempstr);
  	//write_lcd(lser2_strng);
    //strcpy(tempstr, "     ");
    write_lcd(tempstr);
	}
    else if (((prog_num > USER_REND) && (prog_num < SWEEP_STRT)) ||
	         ((prog_num > SWEEP_REND) && (prog_num <= SWEEP_END))) {
      strcpy(tempstr, "                ");
	  write_lcd(tempstr);
      set_cursor(LINE3, 0, NOCURSOR);
      strcpy(tempstr, (const char*)RESERVE_STRING);
	  write_lcd(tempstr);
	}
	else {
      strcpy(tempstr, "                ");
	  write_lcd(tempstr);
      set_cursor(LINE3, 0, NOCURSOR);
      strcpy(tempstr, (const char*)ILLEGAL_STRING);
	  write_lcd(tempstr);
	}
  }
#ifndef PCB_1_00
#if sixdigit
  set_cursor(LINE4, 9, NOCURSOR);
  strcpy(tempstr, "  Prog#");
#else
  set_cursor(LINE4, 7, NOCURSOR);
  strcpy(tempstr, "    Prog#");
#endif
#else
  set_cursor(LINE4, 0, NOCURSOR);
#if sixdigit
  strcpy(tempstr, "  Prog#");
#else
  strcpy(tempstr, "    Prog#");
#endif
#endif
  write_lcd(tempstr);
#ifndef PCB_1_00
#if sixdigit
    set_cursor(LINE4, 3, NOCURSOR);
#else
    set_cursor(LINE4, 3, NOCURSOR);
#endif
#endif
  if (mode == Program)
    underline = 1;
  write_lcd(prog_str);
  underline = 0;
  // If we are not in a laser event, clear last 4 chars. We are getting
  // garbage from new Sound Device....This is a patch, but needed.
  if (laser_flg == 0) {
    strcpy(tempstr, "   ");
#ifndef PCB_1_00
#if sixdigit
    set_cursor(LINE4, 0, NOCURSOR);
#else
    set_cursor(LINE4, 0, NOCURSOR);
#endif
#endif
    write_lcd(tempstr);
  }
}

//*****************************************************************************
//*
//* routine: smmain_screen
//* Date:    March 1, 2004
//* Author:  Ralph Pruitt
//* Display the Main Screen on a 20x4Line LCD Screen without a Clear Screen. Note that this involves
//* reading each of the key variables and updating their information on the screen.
//* This information includes the following:
//* 	 Timer Settings:
//*		 	   Minutes:
//*			   		  unsigned char			tmr_min;
//*					  char	   				tmr_minstr[2];
//*			   Seconds:
//*	   		  		  unsigned char			tmr_sec;
//*					  char	   				tmr_secstr[2];
//*			   Battery Level: 
//*			   		  char	  	  			Bat_Lvl[3];
//*			   Laser1 Setting:
//*			   		  unsigned long 		lser1_time;
//*					  char	   				lser1_strng[7];
//*			   Laser2 Setting:
//*			   		  unsigned long 		lser2_time;
//*					  char	   				lser2_strng[7];
//*			   Laser3 Setting:
//*			   		  unsigned long 		lser3_time;
//*					  char	   				lser3_strng[7];
//*			   Laser4 Setting:
//*			   		  unsigned long 		lser4_time;
//*					  char	   				lser4_strng[7];
//*			   Current Program Number:
//*			   		  unsigned char			prog_num;
//*					  char	   				prog_str[3];
//*
//*****************************************************************************
void smmain_screen(void)
{
  char tempstr[18];
  char tempstr2[4];
  int  tempvar;
//  unsigned char temp1;
  printf2("***************************************************************\n");
  printf2("**                    SmMain SCREEN                           *\n");
  printf2("***************************************************************\n");
  // Force read of Current Program Laser Settings.
  if ((lsr_update_flg == 0) &&
      (mode != Program) &&
	  (mode != Build_Prog) &&
	  (sm != 5) &&
	  (sm != 6))
  {
    short_delay(0x10);
    init_laser(prog_num, INITIALIZE);
  }
  else {
    short_delay(0x10);
    Delay();
  }

  // Time to convert numbers to strings
  str_chg_char(tmr_minstr, 2, tmr_min, ZEROS);
  str_chg_char(tmr_secstr, 2, tmr_sec, ZEROS);
  // If lsr_update_flg is set we are loading new values...Don't Change!!!
  if (lsr_update_flg == 0) {
    // If alsr_update_flg is set...We are hardcoding new numbers via entry,
	// and not using the EEPROM to recall values.
    if (alsr_update_flg == 1) {
      str_chg_long2(lser1_strng, FREQ_STR_LEN+1, laser1_disp);
      str_chg_long2(lser2_strng, FREQ_STR_LEN+1, laser2_disp);
      str_chg_long2(lser3_strng, FREQ_STR_LEN+1, laser3_disp);
      str_chg_long2(lser4_strng, FREQ_STR_LEN+1, laser4_disp);
	}
	else {
      str_chg_long(lser1_strng, FREQ_STR_LEN+1, laser1_disp);
      str_chg_long(lser2_strng, FREQ_STR_LEN+1, laser2_disp);
      str_chg_long(lser3_strng, FREQ_STR_LEN+1, laser3_disp);
      str_chg_long(lser4_strng, FREQ_STR_LEN+1, laser4_disp);
	}
  }
  lser1_strng[FREQ_STR_LEN] = 0x00;
  lser2_strng[FREQ_STR_LEN] = 0x00;
  lser3_strng[FREQ_STR_LEN] = 0x00;
  lser4_strng[FREQ_STR_LEN] = 0x00;
#if sixdigit
  str_chg_ulong(prog_str, 6, prog_num, ZEROS);
#else
  str_chg_int(prog_str, 3, prog_num, ZEROS);
#endif
  
  // Lets Determine Battery Level.
  strcpy(Bat_Lvl, Battery_Test());
    
  // Build LCD Screen.
#ifdef PCB_1_00
  set_cursor(LINE1, 0, NOCURSOR);
#else
  set_cursor(LINE1, 13, NOCURSOR);
#endif
  strcpy(tempstr, "Tm:");
  write_lcd(tempstr);
#ifndef PCB_1_00
  set_cursor(LINE1,11, NOCURSOR);
#endif
  write_lcd(tmr_minstr);
  strcpy(tempstr, ":");
#ifndef PCB_1_00
  set_cursor(LINE1,10, NOCURSOR);
#endif
  write_lcd(tempstr);
#ifndef PCB_1_00
  set_cursor(LINE1,8, NOCURSOR);
#endif
  write_lcd(tmr_secstr);
#ifndef PCB_1_00
  set_cursor(LINE1,4, NOCURSOR);
#endif
  strcpy(tempstr, "   E");
  write_lcd(tempstr);
#ifndef PCB_1_00
  set_cursor(LINE1,1, NOCURSOR);
#endif
  write_lcd(Bat_Lvl);
#ifndef PCB_1_00
  set_cursor(LINE1,0, NOCURSOR);
  strcpy(tempstr, "F");
#else
  strcpy(tempstr, "F ");
#endif
  write_lcd(tempstr);
  set_cursor(LINE2, 0, NOCURSOR);
  if (sm == 6) {
   	switch (macro1.macro_flg)
	{
	  case 2:  //Display Delay Time.
#ifndef PCB_1_00
		set_cursor(LINE2, 8, NOCURSOR);
#endif
		strcpy(tempstr, "  Delay:");
	    write_lcd(tempstr);
		if (macro1.minute_flg == 0) {
          underline = 1;
#ifndef PCB_1_00
  		  set_cursor(LINE2, 6, BLINK);
#else
  		  set_cursor(LINE2, 8, UNDERLINE);
#endif
	      write_lcd(min_str);
          underline = 0;
#ifndef PCB_1_00
  		  set_cursor(LINE2, 5, NOCURSOR);
#else
  		  set_cursor(LINE2, 10, NOCURSOR);
#endif
		  strcpy(tempstr, ":");
		  write_lcd(tempstr);
#ifndef PCB_1_00
  set_cursor(LINE2, 3, NOCURSOR);
#endif
		  write_lcd(sec_str);
#ifndef PCB_1_00
  		  set_cursor(LINE2, 0, NOCURSOR);
#endif
		  strcpy(tempstr, "   ");
		  write_lcd(tempstr);
		}
		else {
#ifndef PCB_1_00
  		  set_cursor(LINE2, 6, NOCURSOR);
#endif
	      write_lcd(min_str);
#ifndef PCB_1_00
  		  set_cursor(LINE2, 5, NOCURSOR);
#endif
		  strcpy(tempstr, ":");
		  write_lcd(tempstr);
          underline = 1;
#ifndef PCB_1_00
  		  set_cursor(LINE2, 3, BLINK);
#else
 		  set_cursor(LINE2, 11, UNDERLINE);
#endif
		  write_lcd(sec_str);
          underline = 0;
#ifndef PCB_1_00
  		  set_cursor(LINE2, 0, NOCURSOR);
#else
 		  set_cursor(LINE2, 13, NOCURSOR);
#endif
		  strcpy(tempstr, "   ");
		  write_lcd(tempstr);
		}
		break;
	  case 1:  //Display Execution Time.
#ifndef PCB_1_00
        set_cursor(LINE2, 8, NOCURSOR);
#endif
		strcpy(tempstr, "   Time:");
	    write_lcd(tempstr);
		if (macro1.minute_flg == 0) {
          underline = 1;
#ifndef PCB_1_00
  		  set_cursor(LINE2, 6, BLINK);
#else
  		  set_cursor(LINE2, 8, UNDERLINE);
#endif
	      write_lcd(min_str);
          underline = 0;
#ifndef PCB_1_00
  		  set_cursor(LINE2, 0, NOCURSOR);
#else
  		  set_cursor(LINE2, 10, NOCURSOR);
#endif
//		  strcpy(tempstr, ":%s   ", sec_str);
		  sprintf(tempstr, ":%s   ", sec_str);
		  write_lcd(tempstr);
//		  write_lcd(sec_str);
//		  strcpy(tempstr, "   ");
//		  write_lcd(tempstr);
		}
		else {
#ifndef PCB_1_00
  		  set_cursor(LINE2, 6, NOCURSOR);
#endif
	      write_lcd(min_str);
#ifndef PCB_1_00
  		  set_cursor(LINE2, 5, NOCURSOR);
#endif
		  strcpy(tempstr, ":");
		  write_lcd(tempstr);
          underline = 1;
#ifndef PCB_1_00
  		  set_cursor(LINE2, 3, BLINK);
#else
  		  set_cursor(LINE2, 11, UNDERLINE);
#endif
		  write_lcd(sec_str);
          underline = 0;
#ifndef PCB_1_00
  		  set_cursor(LINE2, 0, NOCURSOR);
#else
  		  set_cursor(LINE2, 13, NOCURSOR);
#endif
		  strcpy(tempstr, "   ");
		  write_lcd(tempstr);
		}
		break;
	  case 0:  //Display Prog_number
#if sixdigit
		strcpy(tempstr, " Program# ");
	    write_lcd(tempstr);
        underline = 1;
  		set_cursor(LINE2, 11, UNDERLINE);
	    write_lcd(progwk_str);
        underline = 0;
  		set_cursor(LINE2, 14, NOCURSOR);
#else
#ifndef PCB_1_00
  		set_cursor(LINE2, 5, NOCURSOR);
#endif
		strcpy(tempstr, "  Program# ");
	    write_lcd(tempstr);
        underline = 1;
#ifndef PCB_1_00
  		set_cursor(LINE2, 1, BLINK);
#else
  		set_cursor(LINE2, 11, UNDERLINE);
#endif
	    write_lcd(progwk_str);
        underline = 0;
#ifndef PCB_1_00
  		set_cursor(LINE2, 0, NOCURSOR);
#else
  		set_cursor(LINE2, 14, NOCURSOR);
#endif
		strcpy(tempstr, " ");
#endif
		write_lcd(tempstr);
		break;
	}
    tempvar = macro1.macro_step + 1;
    str_chg_int(tempstr2, 2, tempvar, ZEROS);
  	set_cursor(LINE3, 0, NOCURSOR);
    sprintf(tempstr, "    STEP# %02d   ", tempvar);
  	//write_lcd(tempstr);
	//write_lcd(tempstr2);
    //strcpy(tempstr, "    ");
  	write_lcd(tempstr);
  }
  else if (sm == 5) {
      switch (sweep1.sweep_key) {	   // Switch Variable Pointer to Display Data Correctly.
  		case 0:					   // Lower Sweep Limit.
#ifndef PCB_1_00
  		  set_cursor(LINE2, 0, NOCURSOR);
#endif
          strcpy(tempstr, "Lower Sweep Freq");
	      write_lcd(tempstr);
		  break;
  		case 1:					   // Sweep Frequency 1.
  		case 2:					   // Sweep Frequency 2.
  		case 3:					   // Sweep Frequency 3.
  		case 4:					   // Sweep Frequency 4.
  		case 5:					   // Sweep Frequency 5.
  		case 6:					   // Sweep Frequency 6.
  		case 7:					   // Sweep Frequency 7.
  		case 8:					   // Sweep Frequency 8.
  		case 9:					   // Sweep Frequency 9.
  		case 10:				   // Sweep Frequency 10.
  		case 11:				   // Sweep Frequency 11.
  		case 12:				   // Sweep Frequency 12.
  		case 13:				   // Sweep Frequency 13.
  		case 14:				   // Sweep Frequency 14.
  		case 15:				   // Sweep Frequency 15.

#ifndef PCB_1_00
  		  set_cursor(LINE2, 0, NOCURSOR);
#endif
  		  tempvar = sweep1.sweep_key;
  		  sprintf( tempstr, "  Sweep Freq %02d ", tempvar);
  		  //strcpy(tempstr, "  Sweep Freq ");
	      //write_lcd(tempstr);
		  //itoa(tempstr2,tempvar,10);
		  //write_lcd(tempstr2);
          //strcpy(tempstr, "  ");
	      write_lcd(tempstr);
		  break;
  		case 16:				   // Final Sweep Limit.
#ifndef PCB_1_00
  		  set_cursor(LINE2, 0, NOCURSOR);
#endif
          strcpy(tempstr, "Final Sweep Freq");
	      write_lcd(tempstr);
		  break;
  	  }
#ifdef PCB_1_00
  	  set_cursor(LINE3, 0, NOCURSOR);
#else
  	  set_cursor(LINE3, 11, NOCURSOR);
#endif
  	  set_cursor(LINE3, 0, NOCURSOR);
  	  strcpy(tempstr, "    :");
  	  write_lcd(tempstr);
#ifndef PCB_1_00
  	  set_cursor(LINE3, 2, BLINK);
#endif
	  underline = 1;
  	  write_lcd(lser1_strng);
#ifndef PCB_1_00
  	  set_cursor(LINE3, 0, NOCURSOR);
#endif
	  underline = 0;
      strcpy(tempstr, "  ");
  	  write_lcd(tempstr);
  }
  else {
      switch (sm)
	  {
	    case 1:
#ifndef PCB_1_00
	      set_cursor(LINE2, 13, NOCURSOR);
#endif
	      strcpy(tempstr, "1- ");
          write_lcd(tempstr);
#ifndef PCB_1_00
	      set_cursor(LINE2, 4, BLINK);
#endif
		  underline = 1;
          write_lcd(lser1_strng);
#ifndef PCB_1_00
	      set_cursor(LINE2, 0, NOCURSOR);
#endif
		  underline = 0;
          strcpy(tempstr, "    ");
          write_lcd(tempstr);
  		  set_cursor(LINE3, 0, NOCURSOR);
          sprintf(tempstr, "2- %010s    ", lser2_strng);
          //strcpy(tempstr, "2- ");
          //write_lcd(tempstr);
  		  //write_lcd(lser2_strng);
          //strcpy(tempstr, "     ");
          write_lcd(tempstr);
	      break;
	    case 2:
	      sprintf(tempstr, "1- %010s    ", lser1_strng);
          //strcpy(tempstr, "1- ");
          //write_lcd(tempstr);
          //write_lcd(lser1_strng);
          //strcpy(tempstr, "     ");
          write_lcd(tempstr);
#ifdef PCB_1_00
          set_cursor(LINE3, 0, NOCURSOR);
#else
          set_cursor(LINE3, 13, NOCURSOR);
#endif
          strcpy(tempstr, "2- ");
          write_lcd(tempstr);
#ifndef PCB_1_00
	      set_cursor(LINE3, 4, BLINK);
#endif
		  underline = 1;
  		  write_lcd(lser2_strng);
#ifndef PCB_1_00
	      set_cursor(LINE3, 0, NOCURSOR);
#endif
		  underline = 0;
          strcpy(tempstr, "    ");
          write_lcd(tempstr);
	      break;
	    case 3:
	      sprintf(tempstr, "2- %010s    ", lser2_strng);
	      //strcpy(tempstr, "2- ");
          //write_lcd(tempstr);
          //write_lcd(lser2_strng);
          //strcpy(tempstr, "     ");
          write_lcd(tempstr);
#ifdef PCB_1_00
          set_cursor(LINE3, 0, NOCURSOR);
#else
          set_cursor(LINE3, 13, NOCURSOR);
#endif
          strcpy(tempstr, "3- ");
          write_lcd(tempstr);
#ifndef PCB_1_00
	      set_cursor(LINE3, 4, BLINK);
#endif
		  underline = 1;
  		  write_lcd(lser3_strng);
#ifndef PCB_1_00
	      set_cursor(LINE3, 0, NOCURSOR);
#endif
		  underline = 0;
          strcpy(tempstr, "    ");
          write_lcd(tempstr);
          break;	  
	    case 4:
	      sprintf(tempstr, "3- %010s    ", lser3_strng);
	      //strcpy(tempstr, "3- ");
          //write_lcd(tempstr);
          //write_lcd(lser3_strng);
          //strcpy(tempstr, "     ");
          write_lcd(tempstr);
#ifdef PCB_1_00
          set_cursor(LINE3, 0, NOCURSOR);
#else
          set_cursor(LINE3, 13, NOCURSOR);
#endif
          strcpy(tempstr, "4- ");
          write_lcd(tempstr);
#ifndef PCB_1_00
	      set_cursor(LINE3, 4, BLINK);
#endif
		  underline = 1;
  		  write_lcd(lser4_strng);
#ifndef PCB_1_00
	      set_cursor(LINE3, 0, NOCURSOR);
#endif
		  underline = 0;
          strcpy(tempstr, "    ");
          write_lcd(tempstr);
	      break;
	  }
    }
    set_cursor(LINE4, 0, NOCURSOR);
#ifndef PCB_1_00
#if sixdigit
  set_cursor(LINE4, 5, NOCURSOR);
  strcpy(tempstr, "  Prog#");
#else
  set_cursor(LINE4, 7, NOCURSOR);
  strcpy(tempstr, "    Prog#");
#endif
#else
  set_cursor(LINE4, 0, NOCURSOR);
#if sixdigit
    strcpy(tempstr, "  Prog#");
#else
    strcpy(tempstr, "    Prog#");
#endif
#endif
	write_lcd(tempstr);
#ifndef PCB_1_00
#if sixdigit
    set_cursor(LINE4, 3, NOCURSOR);
#else
    set_cursor(LINE4, 3, NOCURSOR);
#endif
#endif
    write_lcd(prog_str);
}

//*****************************************************************************
//*
//* routine: update_time
//* Date:    January 16, 2004
//* Author:  Ralph Pruitt
//* Update Timer Display Only.
//* 	 Timer Settings:
//*		 	   Minutes:
//*			   		  unsigned char			tmr_min;
//*					  char	   				tmr_minstr[2];
//*			   Seconds:
//*	   		  		  unsigned char			tmr_sec;
//*					  char	   				tmr_secstr[2];
//*			   Battery Level: 
//*			   		  char	  	  			Bat_Lvl[3];
//*
//*****************************************************************************
void update_time(void)
{
  static unsigned char min_save=0;
  static unsigned char sec_save=0;
  
  // Time to convert numbers to strings
#ifdef DEBUGGR
  debug1(6);
  #endif

  // Lets Determine Battery Level.
  // strcpy(Bat_Lvl, Battery_Test());
    
  // Build LCD Screen.
  // If Minute has changed..Then display..else skip
  if (min_save != tmr_min) {
#if NEW_LCD
//    init_lcd2();						    // Initialize the LCD Screen.
#endif
	remain_screen();						// Display Main Screen.
/*    #if GRAPHICS
    lcd_comm2(GR1, RSCOMMAND, Page_Address); 
//    wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
#if NEW_LCD
	save_char = 22;
    lcd_comm2(GR1, RSCOMMAND, (Set_Col_Addr + 22));		  // Send Command to LCD.   
#else
	save_char = 18;
    lcd_comm2(GR1, RSCOMMAND, (Set_Col_Addr + 18));		  // Send Command to LCD.   
#endif
//    wait_busy2(GR1);	 	  	  	  // Wait for Busy Flag to Clear

	#else
    lcd_comm(RSCOMMAND, (Set_DD_RAM + 5));		  // Send Command to LCD.   
    wait_busy();	 	  	  	  // Wait for Busy Flag to Clear
	#endif
#if DEBUGGR
	debug1(7);
    #endif
//    itoa2(tmr_min);
    #if GRAPHICS
    wait_busy2(GR1);	 	  	  	  // Wait for Busy Flag to Clear

	#else
    wait_busy();	 	  	  	  // Wait for Busy Flag to Clear
    #endif  */
	min_save = tmr_min;		  	  // Update min_save.
  }
  
  // If Second has changed..Then display..else skip
  if (sec_save != tmr_sec) {
#if NEW_LCD
//    init_lcd2();						    // Initialize the LCD Screen.
#endif
	remain_screen();						// Display Main Screen.
/*    #if GRAPHICS
    lcd_comm2(GR1, RSCOMMAND, Page_Address); 
//    wait_busy2(GR1); 	  	  // Wait for Busy Flag to Clear Device 2.
#if NEW_LCD
	save_char = 40;
    lcd_comm2(GR1, RSCOMMAND, (Set_Col_Addr + 40));		  // Send Command to LCD.   
    lcd_comm2(GR2, RSCOMMAND, Set_Col_Addr);	  // Send Command to LCD Device 2.   
#else
	save_char = 36;
    lcd_comm2(GR1, RSCOMMAND, (Set_Col_Addr + 36));		  // Send Command to LCD.   
#endif
//    wait_busy2(GR1);	 	  	  	  // Wait for Busy Flag to Clear
	
	#else
    lcd_comm(RSCOMMAND, (Set_DD_RAM + 8));		  // Send Command to LCD.   
    wait_busy();	 	  	  	  // Wait for Busy Flag to Clear
    #endif
#if DEBUGGR
	debug1(8);
    #endif
    itoa2(tmr_sec); */
	sec_save = tmr_sec;		  	  // Update sec_save.
	// Time to Build Monitor Information on Time.
	monPrint("TIMER", Get_Timer());		// Send Status Message
  }
  
  //write_lcd(" Bat E");
  //write_lcd(Bat_Lvl);
  //write_lcd("F ");
}

//*****************************************************************************
//*
//* routine: New_Prog_Screen
//* Date:    January 1, 2004
//* Author:  Ralph Pruitt
//* Display the Boot Screen on a 20x4Line LCD Screen.
//*
//*****************************************************************************
void New_Prog_Screen(void)
{
  char tempstr[18];

  clear_screen();							// Clear Screen.
  set_cursor(LINE1, 0, NOCURSOR);
  strcpy(tempstr, "New Program?");
  write_lcd(tempstr);
  set_cursor(LINE2, 0, NOCURSOR);
  strcpy(tempstr, "Select: Yes");
  write_lcd(tempstr);
  set_cursor(LINE3, 0, NOCURSOR);
  strcpy(tempstr, "Cancel: No");
  write_lcd(tempstr);
  set_cursor(LINE4, 0, BLINK);
  strcpy(tempstr, ": ");
  write_lcd(tempstr);
}

//*****************************************************************************
//*
//* routine: Delete_Prog_Screen
//* Date:    January 1, 2004
//* Author:  Ralph Pruitt
//* Display the Boot Screen on a 20x4Line LCD Screen.
//*
//*****************************************************************************
void Delete_Prog_Screen(void)
{
  char tempstr[18];

  clear_screen();							// Clear Screen.
  set_cursor(LINE1, 0, NOCURSOR);
#if sixdigit
  strcpy(tempstr, "Dlete P# ");
  write_lcd(tempstr);
  write_lcd(prog_str);
  strcpy(tempstr, "?");
#else
  sprintf(tempstr, "Delete Prog %03s?", prog_str);
  //strcpy(tempstr, "Delete Prog ");
  //write_lcd(tempstr);
  //write_lcd(prog_str);
  //strcpy(tempstr, "?");
#endif
  write_lcd(tempstr);
  set_cursor(LINE2, 0, NOCURSOR);
  strcpy(tempstr, "Select: Yes");
  write_lcd(tempstr);
  set_cursor(LINE3, 0, NOCURSOR);
  strcpy(tempstr, "Cancel: No");
  write_lcd(tempstr);
#ifdef PCB_1_00
  set_cursor(LINE4, 0, BLINK);
#else
  set_cursor(LINE4, 15, BLINK);
#endif
  strcpy(tempstr, ": ");
  write_lcd(tempstr);
}

//*****************************************************************************
//*
//* routine: LowBat_Screen
//* Date:    March 7, 2004
//* Author:  Ralph Pruitt
//* Display the Low Battery LCD Screen.
//*
//*****************************************************************************
void LowBat_Screen(void)
{
  char tempstr[18];

  clear_screen();							// Clear Screen.
  set_cursor(LINE2, 0, NOCURSOR);
  strcpy(tempstr, "  LOW BATTERY");
  write_lcd(tempstr);
}

//*****************************************************************************
//*
//* routine: PwrDwn_Screen
//* Date:    November 5, 2021
//* Author:  Ralph Pruitt
//* Display the Power Down LCD Screen.
//*
//*****************************************************************************
void PwrDwn_Screen(void)
{
  char tempstr[18];

  clear_screen();							// Clear Screen.
  set_cursor(LINE2, 0, NOCURSOR);
  strcpy(tempstr, " POWERING DOWN ");
  write_lcd(tempstr);
}

//*****************************************************************************
//*
//* routine: sweep_disp
//* Date:    July 13, 2005
//* Author:  Ralph Pruitt
//* Update LCD Key sections for Sweep Display.
//*
//*****************************************************************************
void sweep_disp(void)
{
  char tempstr[18];
  int  tempvar;
  char tempstr2[4];
  unsigned char temp1;

  set_cursor(LINE2, 0, NOCURSOR);
  switch (sweep1.sweep_ptr - 1) {  // Switch Variable Pointer to Display Data Correctly.
  		case 0:					   // Lower Sweep Limit.
          strcpy(tempstr, "Lower Sweep Freq");
	      write_lcd(tempstr);
		  break;
  		case 1:					   // Sweep Frequency 1.
  		case 2:					   // Sweep Frequency 2.
  		case 3:					   // Sweep Frequency 3.
  		case 4:					   // Sweep Frequency 4.
  		case 5:					   // Sweep Frequency 5.
  		case 6:					   // Sweep Frequency 6.
  		case 7:					   // Sweep Frequency 7.
  		case 8:					   // Sweep Frequency 8.
  		case 9:					   // Sweep Frequency 9.
  		case 10:				   // Sweep Frequency 10.
  		case 11:				   // Sweep Frequency 11.
  		case 12:				   // Sweep Frequency 12.
  		case 13:				   // Sweep Frequency 13.
  		case 14:				   // Sweep Frequency 14.
  		case 15:				   // Sweep Frequency 15.
          //strcpy(tempstr, "  Sweep Freq ");
	      //write_lcd(tempstr);
		  tempvar = sweep1.sweep_ptr - 1;
		  sprintf(tempstr, "  Sweep Freq %02d  ", tempvar);
		  //itoa(tempstr2,tempvar,10);
		  write_lcd(tempstr2); 		  
          //strcpy(tempstr, "  ");
	      //write_lcd(tempstr);
		  break;
  		case 16:				   // Final Sweep Limit.
          strcpy(tempstr, "Final Sweep Freq");
	      write_lcd(tempstr);
		  break;
  }
  // OK...Now show Sweep direction
  set_cursor(LINE3, 0, NOCURSOR);
  if (sweep1.sweep_dir == 0) { 
    // Show Up Direction.
    temp1 = 0xf5;
  }
  else {
    // Show Down Direction.
    temp1 = 0xf6;
  }
  write_char(temp1);
}

//*****************************************************************************
//*
//* routine: LCDmonitor
//* Date:    January 11, 2015
//* Author:  Ralph Pruitt
//* LCD Monitor commands
//*
//*****************************************************************************
void LCDmonitor( char* parm1)
{
  if( strcmp(parm1, "clear") == 0)
  {
      printf2("LCD Clear Screen.\n");
      clear_screen();
  }
  else if( strcmp(parm1, "factory") == 0)
  {
      printf2("LCD factory Screen.\n");
      factory_screen();
  }
  else if( strcmp(parm1, "boot") == 0)
  {
      printf2("LCD boot Screen.\n");
      boot_screen();
  }
 else if( strcmp(parm1, "SerialNum") == 0)
  {
      printf2("LCD SerialNum Screen.\n");
      SerialNumScrn();
  }
#if LEASEOP
 else if( strcmp(parm1, "KeyEntry") == 0)
  {
      printf2("LCD KeyEntry Screen.\n");
      KeyEntryScrn();
  }
#endif
 else if( strcmp(parm1, "main") == 0)
  {
      printf2("LCD main Screen.\n");
      main_screen();
  }
 else if( strcmp(parm1, "remain") == 0)
  {
      printf2("LCD remain Screen.\n");
      remain_screen();
  }
 else if( strcmp(parm1, "smmain") == 0)
  {
      printf2("LCD smmain Screen.\n");
      smmain_screen();
  }
 else if( strcmp(parm1, "com0") == 0)
  {
      printf2("LCD com0.\n");
      lcd_comm2( 0, 0, 0x55);
  }
 else if( strcmp(parm1, "com1") == 0)
  {
      printf2("LCD com1.\n");
      lcd_comm2( 0, 1, 0x55);
  }
 else if( strcmp(parm1, "com2") == 0)
  {
      printf2("LCD com2.\n");
      lcd_comm2( 1, 0, 0x55);
  }
 else if( strcmp(parm1, "com3") == 0)
  {
      printf2("LCD com3.\n");
      lcd_comm2( 1, 1, 0x55);
  }
 else if( strcmp(parm1, "stat0") == 0)
  {
  	  uchar tempval;
  	  char str[30];
  	  printf2("LCD stat0.\n");
	  tempval = lcd_status2(0);
	  sprintf(str, "Status: %xd\n", tempval);
      printf2(str);
  }
 else if( strcmp(parm1, "stat1") == 0)
  {
  	  uchar tempval;
  	  char str[30];
  	  printf2("LCD stat1.\n");
	  tempval = lcd_status2(1);
	  sprintf(str, "Status: %xd\n", tempval);
      printf2(str);
  }
 else if( strcmp(parm1, "read0") == 0)
  {
  	  uchar tempval;
  	  char str[30];
      printf2("LCD read0.\n");
      tempval = lcd_read2(0);
	  sprintf(str, "Value: %xd\n", tempval);
      printf2(str);
  }
 else if( strcmp(parm1, "read1") == 0)
  {
  	  uchar tempval;
  	  char str[30];
      printf2("LCD read1.\n");
      tempval = lcd_read2(1);
	  sprintf(str, "Value: %xd\n", tempval);
      printf2(str);
  }
  else
  {
      printf2("ILLEGAL LCD Parameter!!\n");
  }
}


//*****************************************************************************
//*
//* routine: reverseChar
//* Date:    October 1, 2016
//* Author:  Ralph Pruitt
//* Reverse passed bits.
//*
//*****************************************************************************
unsigned char reverseChar( unsigned char parm1)
{
/*unsigned char temp=0;
int x;

	for (x=0; x<8; x++)
	{
		temp = parm1 & 0x01;
		temp = temp << 1;
		parm1 = parm1 >>1;
	}
	return temp; */
	return parm1;
}
