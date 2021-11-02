/*
 * Protocol.c
 *
 *  Created on: Feb 3, 2015
 *      Author: rpruitt76
 */
//****************************************************************************
//*
//*	Protocol
//*
//* There is one routine here that is used to load the correct Protocol for User Memory.
//*	struct laser_entry *read_entry(unsigned int entry_num): read the indicated entry from the EEPROM or memory.
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
#ifdef CLW
  // CLW Protocols and Macros
  #include "ProtocolCLW.h"
  #include "macrosCLW.h"
#else
  // OLD Mark III Protocols and Macros
  #include "Protocol.h"
  #include "macros.h"
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
//* routine: read_entry
//* Date: 	 December 27, 2003
//* Updated: February 4, 2015
//* Author:  Ralph Pruitt
//* This routine is used to read the indicated entry from the EEPROM of the AVR.
//*
//* INPUT:
//*   entry_num:  1-499 - Entry Number of Laser Data to read.
//*
//* OUTPUT:
//*   Pointer to Laser Structure: Returns a pointer to the Laser Structure
//*                               retrieved from EEPROM.
//*****************************************************************************
struct laser_entry *read_entry(unsigned int entry_num)
{
  char tempstr[80];
  unsigned long address;
  static struct laser_entry temp1;		// Declare Static Structure to be written.
  struct laseru_entry temp2;		// Declare Static Structure to be written.
  struct laseru_entry *address1;

  if (entry_num == SPACE_VAL) {     // Set Pattern for -Wait-
    temp1.laser1_time = 0;
    temp1.laser2_time = 0;
    temp1.laser3_time = 0;
    temp1.laser4_time = 0;
    strcpy(temp1.string1, WAIT_STRING);
	temp1.entry_flg = 1;
  }
#ifdef CLW
  else if (entry_num <= CUSTOM4_END) {  // Set Protocol fot "Continuous Wave.
#else
  else if (entry_num <= CUSTOM_END) {  // Set Protocol fot "Continuous Wave.
#endif
    if (entry_num == 0) {
      temp1.laser1_time = 0;
      temp1.laser2_time = 0;
      temp1.laser3_time = 0;
      temp1.laser4_time = 0;
      strcpy(temp1.string1, "Continuous Wave ");
	  temp1.entry_flg = 1;
	}
#ifdef CLW
// 		    else if (opMode == 3)			// Legacy is only active.
//    else if (entry_num <= CUSTOM4_END) {  // Set Protocol fot Custom Protocol
    else if ( ((opMode == 3) && (entry_num <= CUSTOM4_END) && (entry_num >= CUSTOM4_START)) ||
    		  ((opMode < 3) && (entry_num <= CUSTOM4_END)) ) {  // Set Protocol for Custom Protocol
#else
    else if (entry_num <= CUSTOM_END) {  // Set Protocol fot Custom Protocol
#endif
      switch (entry_num){
	    case 1:
          temp1.laser1_time = PROG1_1;
          temp1.laser2_time = PROG1_2;
          temp1.laser3_time = PROG1_3;
          temp1.laser4_time = PROG1_4;
          strcpy(temp1.string1, PROG1_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 2:
          temp1.laser1_time = PROG2_1;
          temp1.laser2_time = PROG2_2;
          temp1.laser3_time = PROG2_3;
          temp1.laser4_time = PROG2_4;
		  strcpy(temp1.string1, PROG2_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 3:
          temp1.laser1_time = PROG3_1;
          temp1.laser2_time = PROG3_2;
          temp1.laser3_time = PROG3_3;
          temp1.laser4_time = PROG3_4;
		  strcpy(temp1.string1, PROG3_STRING);
		  temp1.entry_flg = 1;
          break;
		case 4:
          temp1.laser1_time = PROG4_1;
          temp1.laser2_time = PROG4_2;
          temp1.laser3_time = PROG4_3;
          temp1.laser4_time = PROG4_4;
		  strcpy(temp1.string1, PROG4_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 5:
          temp1.laser1_time = PROG5_1;
          temp1.laser2_time = PROG5_2;
          temp1.laser3_time = PROG5_3;
          temp1.laser4_time = PROG5_4;
		  strcpy(temp1.string1, PROG5_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 6:
          temp1.laser1_time = PROG6_1;
          temp1.laser2_time = PROG6_2;
          temp1.laser3_time = PROG6_3;
          temp1.laser4_time = PROG6_4;
		  strcpy(temp1.string1, PROG6_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 7:
          temp1.laser1_time = PROG7_1;
          temp1.laser2_time = PROG7_2;
          temp1.laser3_time = PROG7_3;
          temp1.laser4_time = PROG7_4;
		  strcpy(temp1.string1, PROG7_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 8:
          temp1.laser1_time = PROG8_1;
          temp1.laser2_time = PROG8_2;
          temp1.laser3_time = PROG8_3;
          temp1.laser4_time = PROG8_4;
		  strcpy(temp1.string1, PROG8_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 9:
          temp1.laser1_time = PROG9_1;
          temp1.laser2_time = PROG9_2;
          temp1.laser3_time = PROG9_3;
          temp1.laser4_time = PROG9_4;
		  strcpy(temp1.string1, PROG9_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 10:
          temp1.laser1_time = PROG10_1;
          temp1.laser2_time = PROG10_2;
          temp1.laser3_time = PROG10_3;
          temp1.laser4_time = PROG10_4;
	      strcpy(temp1.string1, PROG10_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 11:
          temp1.laser1_time = PROG11_1;
          temp1.laser2_time = PROG11_2;
          temp1.laser3_time = PROG11_3;
          temp1.laser4_time = PROG11_4;
		  strcpy(temp1.string1, PROG11_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 12:
          temp1.laser1_time = PROG12_1;
          temp1.laser2_time = PROG12_2;
          temp1.laser3_time = PROG12_3;
          temp1.laser4_time = PROG12_4;
		  strcpy(temp1.string1, PROG12_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 13:
          temp1.laser1_time = PROG13_1;
          temp1.laser2_time = PROG13_2;
          temp1.laser3_time = PROG13_3;
          temp1.laser4_time = PROG13_4;
		  strcpy(temp1.string1, PROG13_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 14:
          temp1.laser1_time = PROG14_1;
          temp1.laser2_time = PROG14_2;
          temp1.laser3_time = PROG14_3;
          temp1.laser4_time = PROG14_4;
		  strcpy(temp1.string1, PROG14_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 15:
          temp1.laser1_time = PROG15_1;
          temp1.laser2_time = PROG15_2;
          temp1.laser3_time = PROG15_3;
          temp1.laser4_time = PROG15_4;
		  strcpy(temp1.string1, PROG15_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 16:
          temp1.laser1_time = PROG16_1;
          temp1.laser2_time = PROG16_2;
          temp1.laser3_time = PROG16_3;
          temp1.laser4_time = PROG16_4;
		  strcpy(temp1.string1, PROG16_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 17:
          temp1.laser1_time = PROG17_1;
          temp1.laser2_time = PROG17_2;
          temp1.laser3_time = PROG17_3;
          temp1.laser4_time = PROG17_4;
		  strcpy(temp1.string1, PROG17_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 18:
          temp1.laser1_time = PROG18_1;
          temp1.laser2_time = PROG18_2;
          temp1.laser3_time = PROG18_3;
          temp1.laser4_time = PROG18_4;
		  strcpy(temp1.string1, PROG18_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 19:
          temp1.laser1_time = PROG19_1;
          temp1.laser2_time = PROG19_2;
          temp1.laser3_time = PROG19_3;
          temp1.laser4_time = PROG19_4;
		  strcpy(temp1.string1, PROG19_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 20:
          temp1.laser1_time = PROG20_1;
          temp1.laser2_time = PROG20_2;
          temp1.laser3_time = PROG20_3;
          temp1.laser4_time = PROG20_4;
		  strcpy(temp1.string1, PROG20_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 21:
          temp1.laser1_time = PROG21_1;
          temp1.laser2_time = PROG21_2;
          temp1.laser3_time = PROG21_3;
          temp1.laser4_time = PROG21_4;
		  strcpy(temp1.string1, PROG21_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 22:
          temp1.laser1_time = PROG22_1;
          temp1.laser2_time = PROG22_2;
          temp1.laser3_time = PROG22_3;
          temp1.laser4_time = PROG22_4;
		  strcpy(temp1.string1, PROG22_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 23:
          temp1.laser1_time = PROG23_1;
          temp1.laser2_time = PROG23_2;
          temp1.laser3_time = PROG23_3;
          temp1.laser4_time = PROG23_4;
		  strcpy(temp1.string1, PROG23_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 24:
          temp1.laser1_time = PROG24_1;
          temp1.laser2_time = PROG24_2;
          temp1.laser3_time = PROG24_3;
          temp1.laser4_time = PROG24_4;
		  strcpy(temp1.string1, PROG24_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 25:
          temp1.laser1_time = PROG25_1;
          temp1.laser2_time = PROG25_2;
          temp1.laser3_time = PROG25_3;
          temp1.laser4_time = PROG25_4;
		  strcpy(temp1.string1, PROG25_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 26:
          temp1.laser1_time = PROG26_1;
          temp1.laser2_time = PROG26_2;
          temp1.laser3_time = PROG26_3;
          temp1.laser4_time = PROG26_4;
		  strcpy(temp1.string1, PROG26_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 27:
          temp1.laser1_time = PROG27_1;
          temp1.laser2_time = PROG27_2;
          temp1.laser3_time = PROG27_3;
          temp1.laser4_time = PROG27_4;
		  strcpy(temp1.string1, PROG27_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 28:
          temp1.laser1_time = PROG28_1;
          temp1.laser2_time = PROG28_2;
          temp1.laser3_time = PROG28_3;
          temp1.laser4_time = PROG28_4;
		  strcpy(temp1.string1, PROG28_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 29:
          temp1.laser1_time = PROG29_1;
          temp1.laser2_time = PROG29_2;
          temp1.laser3_time = PROG29_3;
          temp1.laser4_time = PROG29_4;
		  strcpy(temp1.string1, PROG29_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 30:
          temp1.laser1_time = PROG30_1;
          temp1.laser2_time = PROG30_2;
          temp1.laser3_time = PROG30_3;
          temp1.laser4_time = PROG30_4;
		  strcpy(temp1.string1, PROG30_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 31:
          temp1.laser1_time = PROG31_1;
          temp1.laser2_time = PROG31_2;
          temp1.laser3_time = PROG31_3;
          temp1.laser4_time = PROG31_4;
		  strcpy(temp1.string1, PROG31_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 32:
          temp1.laser1_time = PROG32_1;
          temp1.laser2_time = PROG32_2;
          temp1.laser3_time = PROG32_3;
          temp1.laser4_time = PROG32_4;
		  strcpy(temp1.string1, PROG32_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 33:
          temp1.laser1_time = PROG33_1;
          temp1.laser2_time = PROG33_2;
          temp1.laser3_time = PROG33_3;
          temp1.laser4_time = PROG33_4;
		  strcpy(temp1.string1, PROG33_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 34:
          temp1.laser1_time = PROG34_1;
          temp1.laser2_time = PROG34_2;
          temp1.laser3_time = PROG34_3;
          temp1.laser4_time = PROG34_4;
		  strcpy(temp1.string1, PROG34_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 35:
          temp1.laser1_time = PROG35_1;
          temp1.laser2_time = PROG35_2;
          temp1.laser3_time = PROG35_3;
          temp1.laser4_time = PROG35_4;
		  strcpy(temp1.string1, PROG35_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 36:
          temp1.laser1_time = PROG36_1;
          temp1.laser2_time = PROG36_2;
          temp1.laser3_time = PROG36_3;
          temp1.laser4_time = PROG36_4;
		  strcpy(temp1.string1, PROG36_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 37:
          temp1.laser1_time = PROG37_1;
          temp1.laser2_time = PROG37_2;
          temp1.laser3_time = PROG37_3;
          temp1.laser4_time = PROG37_4;
		  strcpy(temp1.string1, PROG37_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 38:
          temp1.laser1_time = PROG38_1;
          temp1.laser2_time = PROG38_2;
          temp1.laser3_time = PROG38_3;
          temp1.laser4_time = PROG38_4;
		  strcpy(temp1.string1, PROG38_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 39:
          temp1.laser1_time = PROG39_1;
          temp1.laser2_time = PROG39_2;
          temp1.laser3_time = PROG39_3;
          temp1.laser4_time = PROG39_4;
		  strcpy(temp1.string1, PROG39_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 40:
          temp1.laser1_time = PROG40_1;
          temp1.laser2_time = PROG40_2;
          temp1.laser3_time = PROG40_3;
          temp1.laser4_time = PROG40_4;
		  strcpy(temp1.string1, PROG40_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 41:
          temp1.laser1_time = PROG41_1;
          temp1.laser2_time = PROG41_2;
          temp1.laser3_time = PROG41_3;
          temp1.laser4_time = PROG41_4;
		  strcpy(temp1.string1, PROG41_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 42:
          temp1.laser1_time = PROG42_1;
          temp1.laser2_time = PROG42_2;
          temp1.laser3_time = PROG42_3;
          temp1.laser4_time = PROG42_4;
		  strcpy(temp1.string1, PROG42_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 43:
          temp1.laser1_time = PROG43_1;
          temp1.laser2_time = PROG43_2;
          temp1.laser3_time = PROG43_3;
          temp1.laser4_time = PROG43_4;
		  strcpy(temp1.string1, PROG43_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 44:
          temp1.laser1_time = PROG44_1;
          temp1.laser2_time = PROG44_2;
          temp1.laser3_time = PROG44_3;
          temp1.laser4_time = PROG44_4;
		  strcpy(temp1.string1, PROG44_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 45:
          temp1.laser1_time = PROG45_1;
          temp1.laser2_time = PROG45_2;
          temp1.laser3_time = PROG45_3;
          temp1.laser4_time = PROG45_4;
          strcpy(temp1.string1, PROG45_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 46:
          temp1.laser1_time = PROG46_1;
          temp1.laser2_time = PROG46_2;
          temp1.laser3_time = PROG46_3;
          temp1.laser4_time = PROG46_4;
          strcpy(temp1.string1, PROG46_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 47:
          temp1.laser1_time = PROG47_1;
          temp1.laser2_time = PROG47_2;
          temp1.laser3_time = PROG47_3;
          temp1.laser4_time = PROG47_4;
          strcpy(temp1.string1, PROG47_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 48:
          temp1.laser1_time = PROG48_1;
          temp1.laser2_time = PROG48_2;
          temp1.laser3_time = PROG48_3;
          temp1.laser4_time = PROG48_4;
          strcpy(temp1.string1, PROG48_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 49:
          temp1.laser1_time = PROG49_1;
          temp1.laser2_time = PROG49_2;
          temp1.laser3_time = PROG49_3;
          temp1.laser4_time = PROG49_4;
          strcpy(temp1.string1, PROG49_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 50:
          temp1.laser1_time = PROG50_1;
          temp1.laser2_time = PROG50_2;
          temp1.laser3_time = PROG50_3;
          temp1.laser4_time = PROG50_4;
          strcpy(temp1.string1, PROG50_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 51:
          temp1.laser1_time = PROG51_1;
          temp1.laser2_time = PROG51_2;
          temp1.laser3_time = PROG51_3;
          temp1.laser4_time = PROG51_4;
          strcpy(temp1.string1, PROG51_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 52:
          temp1.laser1_time = PROG52_1;
          temp1.laser2_time = PROG52_2;
          temp1.laser3_time = PROG52_3;
          temp1.laser4_time = PROG52_4;
          strcpy(temp1.string1, PROG52_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 53:
          temp1.laser1_time = PROG53_1;
          temp1.laser2_time = PROG53_2;
          temp1.laser3_time = PROG53_3;
          temp1.laser4_time = PROG53_4;
          strcpy(temp1.string1, PROG53_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 54:
          temp1.laser1_time = PROG54_1;
          temp1.laser2_time = PROG54_2;
          temp1.laser3_time = PROG54_3;
          temp1.laser4_time = PROG54_4;
          strcpy(temp1.string1, PROG54_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 55:
          temp1.laser1_time = PROG55_1;
          temp1.laser2_time = PROG55_2;
          temp1.laser3_time = PROG55_3;
          temp1.laser4_time = PROG55_4;
          strcpy(temp1.string1, PROG55_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 56:
          temp1.laser1_time = PROG56_1;
          temp1.laser2_time = PROG56_2;
          temp1.laser3_time = PROG56_3;
          temp1.laser4_time = PROG56_4;
          strcpy(temp1.string1, PROG56_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 57:
          temp1.laser1_time = PROG57_1;
          temp1.laser2_time = PROG57_2;
          temp1.laser3_time = PROG57_3;
          temp1.laser4_time = PROG57_4;
          strcpy(temp1.string1, PROG57_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 58:
          temp1.laser1_time = PROG58_1;
          temp1.laser2_time = PROG58_2;
          temp1.laser3_time = PROG58_3;
          temp1.laser4_time = PROG58_4;
          strcpy(temp1.string1, PROG58_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 59:
          temp1.laser1_time = PROG59_1;
          temp1.laser2_time = PROG59_2;
          temp1.laser3_time = PROG59_3;
          temp1.laser4_time = PROG59_4;
          strcpy(temp1.string1, PROG59_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 60:
          temp1.laser1_time = PROG60_1;
          temp1.laser2_time = PROG60_2;
          temp1.laser3_time = PROG60_3;
          temp1.laser4_time = PROG60_4;
          strcpy(temp1.string1, PROG60_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 61:
          temp1.laser1_time = PROG61_1;
          temp1.laser2_time = PROG61_2;
          temp1.laser3_time = PROG61_3;
          temp1.laser4_time = PROG61_4;
          strcpy(temp1.string1, PROG61_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 62:
          temp1.laser1_time = PROG62_1;
          temp1.laser2_time = PROG62_2;
          temp1.laser3_time = PROG62_3;
          temp1.laser4_time = PROG62_4;
          strcpy(temp1.string1, PROG62_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 63:
          temp1.laser1_time = PROG63_1;
          temp1.laser2_time = PROG63_2;
          temp1.laser3_time = PROG63_3;
          temp1.laser4_time = PROG63_4;
          strcpy(temp1.string1, PROG63_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 64:
          temp1.laser1_time = PROG64_1;
          temp1.laser2_time = PROG64_2;
          temp1.laser3_time = PROG64_3;
          temp1.laser4_time = PROG64_4;
          strcpy(temp1.string1, PROG64_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 65:
          temp1.laser1_time = PROG65_1;
          temp1.laser2_time = PROG65_2;
          temp1.laser3_time = PROG65_3;
          temp1.laser4_time = PROG65_4;
          strcpy(temp1.string1, PROG65_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 66:
          temp1.laser1_time = PROG66_1;
          temp1.laser2_time = PROG66_2;
          temp1.laser3_time = PROG66_3;
          temp1.laser4_time = PROG66_4;
          strcpy(temp1.string1, PROG66_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 67:
          temp1.laser1_time = PROG67_1;
          temp1.laser2_time = PROG67_2;
          temp1.laser3_time = PROG67_3;
          temp1.laser4_time = PROG67_4;
          strcpy(temp1.string1, PROG67_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 68:
          temp1.laser1_time = PROG68_1;
          temp1.laser2_time = PROG68_2;
          temp1.laser3_time = PROG68_3;
          temp1.laser4_time = PROG68_4;
          strcpy(temp1.string1, PROG68_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 69:
          temp1.laser1_time = PROG69_1;
          temp1.laser2_time = PROG69_2;
          temp1.laser3_time = PROG69_3;
          temp1.laser4_time = PROG69_4;
          strcpy(temp1.string1, PROG69_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 70:
          temp1.laser1_time = PROG70_1;
          temp1.laser2_time = PROG70_2;
          temp1.laser3_time = PROG70_3;
          temp1.laser4_time = PROG70_4;
          strcpy(temp1.string1, PROG70_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 71:
          temp1.laser1_time = PROG71_1;
          temp1.laser2_time = PROG71_2;
          temp1.laser3_time = PROG71_3;
          temp1.laser4_time = PROG71_4;
          strcpy(temp1.string1, PROG71_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 72:
          temp1.laser1_time = PROG72_1;
          temp1.laser2_time = PROG72_2;
          temp1.laser3_time = PROG72_3;
          temp1.laser4_time = PROG72_4;
          strcpy(temp1.string1, PROG72_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 73:
          temp1.laser1_time = PROG73_1;
          temp1.laser2_time = PROG73_2;
          temp1.laser3_time = PROG73_3;
          temp1.laser4_time = PROG73_4;
          strcpy(temp1.string1, PROG73_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 74:
          temp1.laser1_time = PROG74_1;
          temp1.laser2_time = PROG74_2;
          temp1.laser3_time = PROG74_3;
          temp1.laser4_time = PROG74_4;
          strcpy(temp1.string1, PROG74_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 75:
          temp1.laser1_time = PROG75_1;
          temp1.laser2_time = PROG75_2;
          temp1.laser3_time = PROG75_3;
          temp1.laser4_time = PROG75_4;
          strcpy(temp1.string1, PROG75_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 76:
          temp1.laser1_time = PROG76_1;
          temp1.laser2_time = PROG76_2;
          temp1.laser3_time = PROG76_3;
          temp1.laser4_time = PROG76_4;
          strcpy(temp1.string1, PROG76_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 77:
          temp1.laser1_time = PROG77_1;
          temp1.laser2_time = PROG77_2;
          temp1.laser3_time = PROG77_3;
          temp1.laser4_time = PROG77_4;
          strcpy(temp1.string1, PROG77_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 78:
          temp1.laser1_time = PROG78_1;
          temp1.laser2_time = PROG78_2;
          temp1.laser3_time = PROG78_3;
          temp1.laser4_time = PROG78_4;
          strcpy(temp1.string1, PROG78_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 79:
          temp1.laser1_time = PROG79_1;
          temp1.laser2_time = PROG79_2;
          temp1.laser3_time = PROG79_3;
          temp1.laser4_time = PROG79_4;
          strcpy(temp1.string1, PROG79_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 80:
          temp1.laser1_time = PROG80_1;
          temp1.laser2_time = PROG80_2;
          temp1.laser3_time = PROG80_3;
          temp1.laser4_time = PROG80_4;
          strcpy(temp1.string1, PROG80_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 81:
          temp1.laser1_time = PROG81_1;
          temp1.laser2_time = PROG81_2;
          temp1.laser3_time = PROG81_3;
          temp1.laser4_time = PROG81_4;
          strcpy(temp1.string1, PROG81_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 82:
          temp1.laser1_time = PROG82_1;
          temp1.laser2_time = PROG82_2;
          temp1.laser3_time = PROG82_3;
          temp1.laser4_time = PROG82_4;
          strcpy(temp1.string1, PROG82_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 83:
          temp1.laser1_time = PROG83_1;
          temp1.laser2_time = PROG83_2;
          temp1.laser3_time = PROG83_3;
          temp1.laser4_time = PROG83_4;
          strcpy(temp1.string1, PROG83_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 84:
          temp1.laser1_time = PROG84_1;
          temp1.laser2_time = PROG84_2;
          temp1.laser3_time = PROG84_3;
          temp1.laser4_time = PROG84_4;
          strcpy(temp1.string1, PROG84_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 85:
          temp1.laser1_time = PROG85_1;
          temp1.laser2_time = PROG85_2;
          temp1.laser3_time = PROG85_3;
          temp1.laser4_time = PROG85_4;
          strcpy(temp1.string1, PROG85_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 86:
          temp1.laser1_time = PROG86_1;
          temp1.laser2_time = PROG86_2;
          temp1.laser3_time = PROG86_3;
          temp1.laser4_time = PROG86_4;
          strcpy(temp1.string1, PROG86_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 87:
          temp1.laser1_time = PROG87_1;
          temp1.laser2_time = PROG87_2;
          temp1.laser3_time = PROG87_3;
          temp1.laser4_time = PROG87_4;
          strcpy(temp1.string1, PROG87_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 88:
          temp1.laser1_time = PROG88_1;
          temp1.laser2_time = PROG88_2;
          temp1.laser3_time = PROG88_3;
          temp1.laser4_time = PROG88_4;
          strcpy(temp1.string1, PROG88_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 89:
          temp1.laser1_time = PROG89_1;
          temp1.laser2_time = PROG89_2;
          temp1.laser3_time = PROG89_3;
          temp1.laser4_time = PROG89_4;
          strcpy(temp1.string1, PROG89_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 90:
          temp1.laser1_time = PROG90_1;
          temp1.laser2_time = PROG90_2;
          temp1.laser3_time = PROG90_3;
          temp1.laser4_time = PROG90_4;
          strcpy(temp1.string1, PROG90_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 91:
          temp1.laser1_time = PROG91_1;
          temp1.laser2_time = PROG91_2;
          temp1.laser3_time = PROG91_3;
          temp1.laser4_time = PROG91_4;
          strcpy(temp1.string1, PROG91_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 92:
          temp1.laser1_time = PROG92_1;
          temp1.laser2_time = PROG92_2;
          temp1.laser3_time = PROG92_3;
          temp1.laser4_time = PROG92_4;
          strcpy(temp1.string1, PROG92_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 93:
          temp1.laser1_time = PROG93_1;
          temp1.laser2_time = PROG93_2;
          temp1.laser3_time = PROG93_3;
          temp1.laser4_time = PROG93_4;
          strcpy(temp1.string1, PROG93_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 94:
          temp1.laser1_time = PROG94_1;
          temp1.laser2_time = PROG94_2;
          temp1.laser3_time = PROG94_3;
          temp1.laser4_time = PROG94_4;
          strcpy(temp1.string1, PROG94_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 95:
          temp1.laser1_time = PROG95_1;
          temp1.laser2_time = PROG95_2;
          temp1.laser3_time = PROG95_3;
          temp1.laser4_time = PROG95_4;
          strcpy(temp1.string1, PROG95_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 96:
          temp1.laser1_time = PROG96_1;
          temp1.laser2_time = PROG96_2;
          temp1.laser3_time = PROG96_3;
          temp1.laser4_time = PROG96_4;
          strcpy(temp1.string1, PROG96_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 97:
          temp1.laser1_time = PROG97_1;
          temp1.laser2_time = PROG97_2;
          temp1.laser3_time = PROG97_3;
          temp1.laser4_time = PROG97_4;
          strcpy(temp1.string1, PROG97_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 98:
          temp1.laser1_time = PROG98_1;
          temp1.laser2_time = PROG98_2;
          temp1.laser3_time = PROG98_3;
          temp1.laser4_time = PROG98_4;
          strcpy(temp1.string1, PROG98_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 99:
          temp1.laser1_time = PROG99_1;
          temp1.laser2_time = PROG99_2;
          temp1.laser3_time = PROG99_3;
          temp1.laser4_time = PROG99_4;
          strcpy(temp1.string1, PROG99_STRING);
	      temp1.entry_flg = 1;
		  break;
//CASE100
		case 100:
          temp1.laser1_time = PROG100_1;
          temp1.laser2_time = PROG100_2;
          temp1.laser3_time = PROG100_3;
          temp1.laser4_time = PROG100_4;
          strcpy(temp1.string1, PROG100_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 101:
          temp1.laser1_time = PROG101_1;
          temp1.laser2_time = PROG101_2;
          temp1.laser3_time = PROG101_3;
          temp1.laser4_time = PROG101_4;
          strcpy(temp1.string1, PROG101_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 102:
          temp1.laser1_time = PROG102_1;
          temp1.laser2_time = PROG102_2;
          temp1.laser3_time = PROG102_3;
          temp1.laser4_time = PROG102_4;
          strcpy(temp1.string1, PROG102_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 103:
          temp1.laser1_time = PROG103_1;
          temp1.laser2_time = PROG103_2;
          temp1.laser3_time = PROG103_3;
          temp1.laser4_time = PROG103_4;
          strcpy(temp1.string1, PROG103_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 104:
          temp1.laser1_time = PROG104_1;
          temp1.laser2_time = PROG104_2;
          temp1.laser3_time = PROG104_3;
          temp1.laser4_time = PROG104_4;
          strcpy(temp1.string1, PROG104_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 105:
          temp1.laser1_time = PROG105_1;
          temp1.laser2_time = PROG105_2;
          temp1.laser3_time = PROG105_3;
          temp1.laser4_time = PROG105_4;
          strcpy(temp1.string1, PROG105_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 106:
          temp1.laser1_time = PROG106_1;
          temp1.laser2_time = PROG106_2;
          temp1.laser3_time = PROG106_3;
          temp1.laser4_time = PROG106_4;
          strcpy(temp1.string1, PROG106_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 107:
          temp1.laser1_time = PROG107_1;
          temp1.laser2_time = PROG107_2;
          temp1.laser3_time = PROG107_3;
          temp1.laser4_time = PROG107_4;
          strcpy(temp1.string1, PROG107_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 108:
          temp1.laser1_time = PROG108_1;
          temp1.laser2_time = PROG108_2;
          temp1.laser3_time = PROG108_3;
          temp1.laser4_time = PROG108_4;
          strcpy(temp1.string1, PROG108_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 109:
          temp1.laser1_time = PROG109_1;
          temp1.laser2_time = PROG109_2;
          temp1.laser3_time = PROG109_3;
          temp1.laser4_time = PROG109_4;
          strcpy(temp1.string1, PROG109_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 110:
          temp1.laser1_time = PROG110_1;
          temp1.laser2_time = PROG110_2;
          temp1.laser3_time = PROG110_3;
          temp1.laser4_time = PROG110_4;
          strcpy(temp1.string1, PROG110_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 111:
          temp1.laser1_time = PROG111_1;
          temp1.laser2_time = PROG111_2;
          temp1.laser3_time = PROG111_3;
          temp1.laser4_time = PROG111_4;
          strcpy(temp1.string1, PROG111_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 112:
          temp1.laser1_time = PROG112_1;
          temp1.laser2_time = PROG112_2;
          temp1.laser3_time = PROG112_3;
          temp1.laser4_time = PROG112_4;
          strcpy(temp1.string1, PROG112_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 113:
          temp1.laser1_time = PROG113_1;
          temp1.laser2_time = PROG113_2;
          temp1.laser3_time = PROG113_3;
          temp1.laser4_time = PROG113_4;
          strcpy(temp1.string1, PROG113_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 114:
          temp1.laser1_time = PROG114_1;
          temp1.laser2_time = PROG114_2;
          temp1.laser3_time = PROG114_3;
          temp1.laser4_time = PROG114_4;
          strcpy(temp1.string1, PROG114_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 115:
          temp1.laser1_time = PROG115_1;
          temp1.laser2_time = PROG115_2;
          temp1.laser3_time = PROG115_3;
          temp1.laser4_time = PROG115_4;
          strcpy(temp1.string1, PROG115_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 116:
          temp1.laser1_time = PROG116_1;
          temp1.laser2_time = PROG116_2;
          temp1.laser3_time = PROG116_3;
          temp1.laser4_time = PROG116_4;
          strcpy(temp1.string1, PROG116_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 117:
          temp1.laser1_time = PROG117_1;
          temp1.laser2_time = PROG117_2;
          temp1.laser3_time = PROG117_3;
          temp1.laser4_time = PROG117_4;
          strcpy(temp1.string1, PROG117_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 118:
          temp1.laser1_time = PROG118_1;
          temp1.laser2_time = PROG118_2;
          temp1.laser3_time = PROG118_3;
          temp1.laser4_time = PROG118_4;
          strcpy(temp1.string1, PROG118_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 119:
          temp1.laser1_time = PROG119_1;
          temp1.laser2_time = PROG119_2;
          temp1.laser3_time = PROG119_3;
          temp1.laser4_time = PROG119_4;
          strcpy(temp1.string1, PROG119_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 120:
          temp1.laser1_time = PROG120_1;
          temp1.laser2_time = PROG120_2;
          temp1.laser3_time = PROG120_3;
          temp1.laser4_time = PROG120_4;
          strcpy(temp1.string1, PROG120_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 121:
          temp1.laser1_time = PROG121_1;
          temp1.laser2_time = PROG121_2;
          temp1.laser3_time = PROG121_3;
          temp1.laser4_time = PROG121_4;
          strcpy(temp1.string1, PROG121_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 122:
          temp1.laser1_time = PROG122_1;
          temp1.laser2_time = PROG122_2;
          temp1.laser3_time = PROG122_3;
          temp1.laser4_time = PROG122_4;
          strcpy(temp1.string1, PROG122_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 123:
          temp1.laser1_time = PROG123_1;
          temp1.laser2_time = PROG123_2;
          temp1.laser3_time = PROG123_3;
          temp1.laser4_time = PROG123_4;
          strcpy(temp1.string1, PROG123_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 124:
          temp1.laser1_time = PROG124_1;
          temp1.laser2_time = PROG124_2;
          temp1.laser3_time = PROG124_3;
          temp1.laser4_time = PROG124_4;
          strcpy(temp1.string1, PROG124_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 125:
          temp1.laser1_time = PROG125_1;
          temp1.laser2_time = PROG125_2;
          temp1.laser3_time = PROG125_3;
          temp1.laser4_time = PROG125_4;
          strcpy(temp1.string1, PROG125_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 126:
          temp1.laser1_time = PROG126_1;
          temp1.laser2_time = PROG126_2;
          temp1.laser3_time = PROG126_3;
          temp1.laser4_time = PROG126_4;
          strcpy(temp1.string1, PROG126_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 127:
          temp1.laser1_time = PROG127_1;
          temp1.laser2_time = PROG127_2;
          temp1.laser3_time = PROG127_3;
          temp1.laser4_time = PROG127_4;
          strcpy(temp1.string1, PROG127_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 128:
          temp1.laser1_time = PROG128_1;
          temp1.laser2_time = PROG128_2;
          temp1.laser3_time = PROG128_3;
          temp1.laser4_time = PROG128_4;
          strcpy(temp1.string1, PROG128_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 129:
          temp1.laser1_time = PROG129_1;
          temp1.laser2_time = PROG129_2;
          temp1.laser3_time = PROG129_3;
          temp1.laser4_time = PROG129_4;
          strcpy(temp1.string1, PROG129_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 130:
          temp1.laser1_time = PROG130_1;
          temp1.laser2_time = PROG130_2;
          temp1.laser3_time = PROG130_3;
          temp1.laser4_time = PROG130_4;
          strcpy(temp1.string1, PROG130_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 131:
          temp1.laser1_time = PROG131_1;
          temp1.laser2_time = PROG131_2;
          temp1.laser3_time = PROG131_3;
          temp1.laser4_time = PROG131_4;
          strcpy(temp1.string1, PROG131_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 132:
          temp1.laser1_time = PROG132_1;
          temp1.laser2_time = PROG132_2;
          temp1.laser3_time = PROG132_3;
          temp1.laser4_time = PROG132_4;
          strcpy(temp1.string1, PROG132_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 133:
          temp1.laser1_time = PROG133_1;
          temp1.laser2_time = PROG133_2;
          temp1.laser3_time = PROG133_3;
          temp1.laser4_time = PROG133_4;
          strcpy(temp1.string1, PROG133_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 134:
          temp1.laser1_time = PROG134_1;
          temp1.laser2_time = PROG134_2;
          temp1.laser3_time = PROG134_3;
          temp1.laser4_time = PROG134_4;
          strcpy(temp1.string1, PROG134_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 135:
          temp1.laser1_time = PROG135_1;
          temp1.laser2_time = PROG135_2;
          temp1.laser3_time = PROG135_3;
          temp1.laser4_time = PROG135_4;
          strcpy(temp1.string1, PROG135_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 136:
          temp1.laser1_time = PROG136_1;
          temp1.laser2_time = PROG136_2;
          temp1.laser3_time = PROG136_3;
          temp1.laser4_time = PROG136_4;
          strcpy(temp1.string1, PROG136_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 137:
          temp1.laser1_time = PROG137_1;
          temp1.laser2_time = PROG137_2;
          temp1.laser3_time = PROG137_3;
          temp1.laser4_time = PROG137_4;
          strcpy(temp1.string1, PROG137_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 138:
          temp1.laser1_time = PROG138_1;
          temp1.laser2_time = PROG138_2;
          temp1.laser3_time = PROG138_3;
          temp1.laser4_time = PROG138_4;
          strcpy(temp1.string1, PROG138_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 139:
          temp1.laser1_time = PROG139_1;
          temp1.laser2_time = PROG139_2;
          temp1.laser3_time = PROG139_3;
          temp1.laser4_time = PROG139_4;
          strcpy(temp1.string1, PROG139_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 140:
          temp1.laser1_time = PROG140_1;
          temp1.laser2_time = PROG140_2;
          temp1.laser3_time = PROG140_3;
          temp1.laser4_time = PROG140_4;
          strcpy(temp1.string1, PROG140_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 141:
          temp1.laser1_time = PROG141_1;
          temp1.laser2_time = PROG141_2;
          temp1.laser3_time = PROG141_3;
          temp1.laser4_time = PROG141_4;
          strcpy(temp1.string1, PROG141_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 142:
          temp1.laser1_time = PROG142_1;
          temp1.laser2_time = PROG142_2;
          temp1.laser3_time = PROG142_3;
          temp1.laser4_time = PROG142_4;
          strcpy(temp1.string1, PROG142_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 143:
          temp1.laser1_time = PROG143_1;
          temp1.laser2_time = PROG143_2;
          temp1.laser3_time = PROG143_3;
          temp1.laser4_time = PROG143_4;
          strcpy(temp1.string1, PROG143_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 144:
          temp1.laser1_time = PROG144_1;
          temp1.laser2_time = PROG144_2;
          temp1.laser3_time = PROG144_3;
          temp1.laser4_time = PROG144_4;
          strcpy(temp1.string1, PROG144_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 145:
          temp1.laser1_time = PROG145_1;
          temp1.laser2_time = PROG145_2;
          temp1.laser3_time = PROG145_3;
          temp1.laser4_time = PROG145_4;
          strcpy(temp1.string1, PROG145_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 146:
          temp1.laser1_time = PROG146_1;
          temp1.laser2_time = PROG146_2;
          temp1.laser3_time = PROG146_3;
          temp1.laser4_time = PROG146_4;
          strcpy(temp1.string1, PROG146_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 147:
          temp1.laser1_time = PROG147_1;
          temp1.laser2_time = PROG147_2;
          temp1.laser3_time = PROG147_3;
          temp1.laser4_time = PROG147_4;
          strcpy(temp1.string1, PROG147_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 148:
          temp1.laser1_time = PROG148_1;
          temp1.laser2_time = PROG148_2;
          temp1.laser3_time = PROG148_3;
          temp1.laser4_time = PROG148_4;
          strcpy(temp1.string1, PROG148_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 149:
          temp1.laser1_time = PROG149_1;
          temp1.laser2_time = PROG149_2;
          temp1.laser3_time = PROG149_3;
          temp1.laser4_time = PROG149_4;
          strcpy(temp1.string1, PROG149_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 150:
          temp1.laser1_time = PROG150_1;
          temp1.laser2_time = PROG150_2;
          temp1.laser3_time = PROG150_3;
          temp1.laser4_time = PROG150_4;
          strcpy(temp1.string1, PROG150_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 151:
          temp1.laser1_time = PROG151_1;
          temp1.laser2_time = PROG151_2;
          temp1.laser3_time = PROG151_3;
          temp1.laser4_time = PROG151_4;
          strcpy(temp1.string1, PROG151_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 152:
          temp1.laser1_time = PROG152_1;
          temp1.laser2_time = PROG152_2;
          temp1.laser3_time = PROG152_3;
          temp1.laser4_time = PROG152_4;
          strcpy(temp1.string1, PROG152_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 153:
          temp1.laser1_time = PROG153_1;
          temp1.laser2_time = PROG153_2;
          temp1.laser3_time = PROG153_3;
          temp1.laser4_time = PROG153_4;
          strcpy(temp1.string1, PROG153_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 154:
          temp1.laser1_time = PROG154_1;
          temp1.laser2_time = PROG154_2;
          temp1.laser3_time = PROG154_3;
          temp1.laser4_time = PROG154_4;
          strcpy(temp1.string1, PROG154_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 155:
          temp1.laser1_time = PROG155_1;
          temp1.laser2_time = PROG155_2;
          temp1.laser3_time = PROG155_3;
          temp1.laser4_time = PROG155_4;
          strcpy(temp1.string1, PROG155_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 156:
          temp1.laser1_time = PROG156_1;
          temp1.laser2_time = PROG156_2;
          temp1.laser3_time = PROG156_3;
          temp1.laser4_time = PROG156_4;
          strcpy(temp1.string1, PROG156_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 157:
          temp1.laser1_time = PROG157_1;
          temp1.laser2_time = PROG157_2;
          temp1.laser3_time = PROG157_3;
          temp1.laser4_time = PROG157_4;
          strcpy(temp1.string1, PROG157_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 158:
          temp1.laser1_time = PROG158_1;
          temp1.laser2_time = PROG158_2;
          temp1.laser3_time = PROG158_3;
          temp1.laser4_time = PROG158_4;
          strcpy(temp1.string1, PROG158_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 159:
          temp1.laser1_time = PROG159_1;
          temp1.laser2_time = PROG159_2;
          temp1.laser3_time = PROG159_3;
          temp1.laser4_time = PROG159_4;
          strcpy(temp1.string1, PROG159_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 160:
          temp1.laser1_time = PROG160_1;
          temp1.laser2_time = PROG160_2;
          temp1.laser3_time = PROG160_3;
          temp1.laser4_time = PROG160_4;
          strcpy(temp1.string1, PROG160_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 161:
          temp1.laser1_time = PROG161_1;
          temp1.laser2_time = PROG161_2;
          temp1.laser3_time = PROG161_3;
          temp1.laser4_time = PROG161_4;
          strcpy(temp1.string1, PROG161_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 162:
          temp1.laser1_time = PROG162_1;
          temp1.laser2_time = PROG162_2;
          temp1.laser3_time = PROG162_3;
          temp1.laser4_time = PROG162_4;
          strcpy(temp1.string1, PROG162_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 163:
          temp1.laser1_time = PROG163_1;
          temp1.laser2_time = PROG163_2;
          temp1.laser3_time = PROG163_3;
          temp1.laser4_time = PROG163_4;
          strcpy(temp1.string1, PROG163_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 164:
          temp1.laser1_time = PROG164_1;
          temp1.laser2_time = PROG164_2;
          temp1.laser3_time = PROG164_3;
          temp1.laser4_time = PROG164_4;
          strcpy(temp1.string1, PROG164_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 165:
          temp1.laser1_time = PROG165_1;
          temp1.laser2_time = PROG165_2;
          temp1.laser3_time = PROG165_3;
          temp1.laser4_time = PROG165_4;
          strcpy(temp1.string1, PROG165_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 166:
          temp1.laser1_time = PROG166_1;
          temp1.laser2_time = PROG166_2;
          temp1.laser3_time = PROG166_3;
          temp1.laser4_time = PROG166_4;
          strcpy(temp1.string1, PROG166_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 167:
          temp1.laser1_time = PROG167_1;
          temp1.laser2_time = PROG167_2;
          temp1.laser3_time = PROG167_3;
          temp1.laser4_time = PROG167_4;
		  strcpy(temp1.string1, PROG167_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 168:
          temp1.laser1_time = PROG168_1;
          temp1.laser2_time = PROG168_2;
          temp1.laser3_time = PROG168_3;
          temp1.laser4_time = PROG168_4;
		  strcpy(temp1.string1, PROG168_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 169:
          temp1.laser1_time = PROG169_1;
          temp1.laser2_time = PROG169_2;
          temp1.laser3_time = PROG169_3;
          temp1.laser4_time = PROG169_4;
		  strcpy(temp1.string1, PROG169_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 170:
          temp1.laser1_time = PROG170_1;
          temp1.laser2_time = PROG170_2;
          temp1.laser3_time = PROG170_3;
          temp1.laser4_time = PROG170_4;
		  strcpy(temp1.string1, PROG170_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 171:
          temp1.laser1_time = PROG171_1;
          temp1.laser2_time = PROG171_2;
          temp1.laser3_time = PROG171_3;
          temp1.laser4_time = PROG171_4;
		  strcpy(temp1.string1, PROG171_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 172:
          temp1.laser1_time = PROG172_1;
          temp1.laser2_time = PROG172_2;
          temp1.laser3_time = PROG172_3;
          temp1.laser4_time = PROG172_4;
		  strcpy(temp1.string1, PROG172_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 173:
          temp1.laser1_time = PROG173_1;
          temp1.laser2_time = PROG173_2;
          temp1.laser3_time = PROG173_3;
          temp1.laser4_time = PROG173_4;
		  strcpy(temp1.string1, PROG173_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 174:
          temp1.laser1_time = PROG174_1;
          temp1.laser2_time = PROG174_2;
          temp1.laser3_time = PROG174_3;
          temp1.laser4_time = PROG174_4;
		  strcpy(temp1.string1, PROG174_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 175:
          temp1.laser1_time = PROG175_1;
          temp1.laser2_time = PROG175_2;
          temp1.laser3_time = PROG175_3;
          temp1.laser4_time = PROG175_4;
		  strcpy(temp1.string1, PROG175_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 176:
          temp1.laser1_time = PROG176_1;
          temp1.laser2_time = PROG176_2;
          temp1.laser3_time = PROG176_3;
          temp1.laser4_time = PROG176_4;
		  strcpy(temp1.string1, PROG176_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 177:
          temp1.laser1_time = PROG177_1;
          temp1.laser2_time = PROG177_2;
          temp1.laser3_time = PROG177_3;
          temp1.laser4_time = PROG177_4;
		  strcpy(temp1.string1, PROG177_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 178:
          temp1.laser1_time = PROG178_1;
          temp1.laser2_time = PROG178_2;
          temp1.laser3_time = PROG178_3;
          temp1.laser4_time = PROG178_4;
		  strcpy(temp1.string1, PROG178_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 179:
          temp1.laser1_time = PROG179_1;
          temp1.laser2_time = PROG179_2;
          temp1.laser3_time = PROG179_3;
          temp1.laser4_time = PROG179_4;
		  strcpy(temp1.string1, PROG179_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 180:
          temp1.laser1_time = PROG180_1;
          temp1.laser2_time = PROG180_2;
          temp1.laser3_time = PROG180_3;
          temp1.laser4_time = PROG180_4;
		  strcpy(temp1.string1, PROG180_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 181:
          temp1.laser1_time = PROG181_1;
          temp1.laser2_time = PROG181_2;
          temp1.laser3_time = PROG181_3;
          temp1.laser4_time = PROG181_4;
		  strcpy(temp1.string1, PROG181_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 182:
          temp1.laser1_time = PROG182_1;
          temp1.laser2_time = PROG182_2;
          temp1.laser3_time = PROG182_3;
          temp1.laser4_time = PROG182_4;
		  strcpy(temp1.string1, PROG182_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 183:
          temp1.laser1_time = PROG183_1;
          temp1.laser2_time = PROG183_2;
          temp1.laser3_time = PROG183_3;
          temp1.laser4_time = PROG183_4;
		  strcpy(temp1.string1, PROG183_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 184:
          temp1.laser1_time = PROG184_1;
          temp1.laser2_time = PROG184_2;
          temp1.laser3_time = PROG184_3;
          temp1.laser4_time = PROG184_4;
		  strcpy(temp1.string1, PROG184_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 185:
          temp1.laser1_time = PROG185_1;
          temp1.laser2_time = PROG185_2;
          temp1.laser3_time = PROG185_3;
          temp1.laser4_time = PROG185_4;
		  strcpy(temp1.string1, PROG185_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 186:
          temp1.laser1_time = PROG186_1;
          temp1.laser2_time = PROG186_2;
          temp1.laser3_time = PROG186_3;
          temp1.laser4_time = PROG186_4;
		  strcpy(temp1.string1, PROG186_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 187:
          temp1.laser1_time = PROG187_1;
          temp1.laser2_time = PROG187_2;
          temp1.laser3_time = PROG187_3;
          temp1.laser4_time = PROG187_4;
		  strcpy(temp1.string1, PROG187_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 188:
          temp1.laser1_time = PROG188_1;
          temp1.laser2_time = PROG188_2;
          temp1.laser3_time = PROG188_3;
          temp1.laser4_time = PROG188_4;
		  strcpy(temp1.string1, PROG188_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 189:
          temp1.laser1_time = PROG189_1;
          temp1.laser2_time = PROG189_2;
          temp1.laser3_time = PROG189_3;
          temp1.laser4_time = PROG189_4;
		  strcpy(temp1.string1, PROG189_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 190:
          temp1.laser1_time = PROG190_1;
          temp1.laser2_time = PROG190_2;
          temp1.laser3_time = PROG190_3;
          temp1.laser4_time = PROG190_4;
		  strcpy(temp1.string1, PROG190_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 191:
          temp1.laser1_time = PROG191_1;
          temp1.laser2_time = PROG191_2;
          temp1.laser3_time = PROG191_3;
          temp1.laser4_time = PROG191_4;
		  strcpy(temp1.string1, PROG191_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 192:
          temp1.laser1_time = PROG192_1;
          temp1.laser2_time = PROG192_2;
          temp1.laser3_time = PROG192_3;
          temp1.laser4_time = PROG192_4;
		  strcpy(temp1.string1, PROG192_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 193:
          temp1.laser1_time = PROG193_1;
          temp1.laser2_time = PROG193_2;
          temp1.laser3_time = PROG193_3;
          temp1.laser4_time = PROG193_4;
		  strcpy(temp1.string1, PROG193_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 194:
          temp1.laser1_time = PROG194_1;
          temp1.laser2_time = PROG194_2;
          temp1.laser3_time = PROG194_3;
          temp1.laser4_time = PROG194_4;
		  strcpy(temp1.string1, PROG194_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 195:
          temp1.laser1_time = PROG195_1;
          temp1.laser2_time = PROG195_2;
          temp1.laser3_time = PROG195_3;
          temp1.laser4_time = PROG195_4;
		  strcpy(temp1.string1, PROG195_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 196:
          temp1.laser1_time = PROG196_1;
          temp1.laser2_time = PROG196_2;
          temp1.laser3_time = PROG196_3;
          temp1.laser4_time = PROG196_4;
		  strcpy(temp1.string1, PROG196_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 197:
          temp1.laser1_time = PROG197_1;
          temp1.laser2_time = PROG197_2;
          temp1.laser3_time = PROG197_3;
          temp1.laser4_time = PROG197_4;
		  strcpy(temp1.string1, PROG197_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 198:
          temp1.laser1_time = PROG198_1;
          temp1.laser2_time = PROG198_2;
          temp1.laser3_time = PROG198_3;
          temp1.laser4_time = PROG198_4;
		  strcpy(temp1.string1, PROG198_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 199:
          temp1.laser1_time = PROG199_1;
          temp1.laser2_time = PROG199_2;
          temp1.laser3_time = PROG199_3;
          temp1.laser4_time = PROG199_4;
		  strcpy(temp1.string1, PROG199_STRING);
		  temp1.entry_flg = 1;
		  break;
//CASE200
		case 200:
          temp1.laser1_time = PROG200_1;
          temp1.laser2_time = PROG200_2;
          temp1.laser3_time = PROG200_3;
          temp1.laser4_time = PROG200_4;
          strcpy(temp1.string1, PROG200_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 201:
          temp1.laser1_time = PROG201_1;
          temp1.laser2_time = PROG201_2;
          temp1.laser3_time = PROG201_3;
          temp1.laser4_time = PROG201_4;
          strcpy(temp1.string1, PROG201_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 202:
          temp1.laser1_time = PROG202_1;
          temp1.laser2_time = PROG202_2;
          temp1.laser3_time = PROG202_3;
          temp1.laser4_time = PROG202_4;
          strcpy(temp1.string1, PROG202_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 203:
          temp1.laser1_time = PROG203_1;
          temp1.laser2_time = PROG203_2;
          temp1.laser3_time = PROG203_3;
          temp1.laser4_time = PROG203_4;
          strcpy(temp1.string1, PROG203_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 204:
          temp1.laser1_time = PROG204_1;
          temp1.laser2_time = PROG204_2;
          temp1.laser3_time = PROG204_3;
          temp1.laser4_time = PROG204_4;
          strcpy(temp1.string1, PROG204_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 205:
          temp1.laser1_time = PROG205_1;
          temp1.laser2_time = PROG205_2;
          temp1.laser3_time = PROG205_3;
          temp1.laser4_time = PROG205_4;
          strcpy(temp1.string1, PROG205_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 206:
          temp1.laser1_time = PROG206_1;
          temp1.laser2_time = PROG206_2;
          temp1.laser3_time = PROG206_3;
          temp1.laser4_time = PROG206_4;
          strcpy(temp1.string1, PROG206_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 207:
          temp1.laser1_time = PROG207_1;
          temp1.laser2_time = PROG207_2;
          temp1.laser3_time = PROG207_3;
          temp1.laser4_time = PROG207_4;
          strcpy(temp1.string1, PROG207_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 208:
          temp1.laser1_time = PROG208_1;
          temp1.laser2_time = PROG208_2;
          temp1.laser3_time = PROG208_3;
          temp1.laser4_time = PROG208_4;
          strcpy(temp1.string1, PROG208_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 209:
          temp1.laser1_time = PROG209_1;
          temp1.laser2_time = PROG209_2;
          temp1.laser3_time = PROG209_3;
          temp1.laser4_time = PROG209_4;
          strcpy(temp1.string1, PROG209_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 210:
          temp1.laser1_time = PROG210_1;
          temp1.laser2_time = PROG210_2;
          temp1.laser3_time = PROG210_3;
          temp1.laser4_time = PROG210_4;
          strcpy(temp1.string1, PROG210_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 211:
          temp1.laser1_time = PROG211_1;
          temp1.laser2_time = PROG211_2;
          temp1.laser3_time = PROG211_3;
          temp1.laser4_time = PROG211_4;
          strcpy(temp1.string1, PROG211_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 212:
          temp1.laser1_time = PROG212_1;
          temp1.laser2_time = PROG212_2;
          temp1.laser3_time = PROG212_3;
          temp1.laser4_time = PROG212_4;
          strcpy(temp1.string1, PROG212_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 213:
          temp1.laser1_time = PROG213_1;
          temp1.laser2_time = PROG213_2;
          temp1.laser3_time = PROG213_3;
          temp1.laser4_time = PROG213_4;
          strcpy(temp1.string1, PROG213_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 214:
          temp1.laser1_time = PROG214_1;
          temp1.laser2_time = PROG214_2;
          temp1.laser3_time = PROG214_3;
          temp1.laser4_time = PROG214_4;
          strcpy(temp1.string1, PROG214_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 215:
          temp1.laser1_time = PROG215_1;
          temp1.laser2_time = PROG215_2;
          temp1.laser3_time = PROG215_3;
          temp1.laser4_time = PROG215_4;
          strcpy(temp1.string1, PROG215_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 216:
          temp1.laser1_time = PROG216_1;
          temp1.laser2_time = PROG216_2;
          temp1.laser3_time = PROG216_3;
          temp1.laser4_time = PROG216_4;
          strcpy(temp1.string1, PROG216_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 217:
          temp1.laser1_time = PROG217_1;
          temp1.laser2_time = PROG217_2;
          temp1.laser3_time = PROG217_3;
          temp1.laser4_time = PROG217_4;
          strcpy(temp1.string1, PROG217_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 218:
          temp1.laser1_time = PROG218_1;
          temp1.laser2_time = PROG218_2;
          temp1.laser3_time = PROG218_3;
          temp1.laser4_time = PROG218_4;
          strcpy(temp1.string1, PROG218_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 219:
          temp1.laser1_time = PROG219_1;
          temp1.laser2_time = PROG219_2;
          temp1.laser3_time = PROG219_3;
          temp1.laser4_time = PROG219_4;
          strcpy(temp1.string1, PROG219_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 220:
          temp1.laser1_time = PROG220_1;
          temp1.laser2_time = PROG220_2;
          temp1.laser3_time = PROG220_3;
          temp1.laser4_time = PROG220_4;
          strcpy(temp1.string1, PROG220_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 221:
          temp1.laser1_time = PROG221_1;
          temp1.laser2_time = PROG221_2;
          temp1.laser3_time = PROG221_3;
          temp1.laser4_time = PROG221_4;
          strcpy(temp1.string1, PROG221_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 222:
          temp1.laser1_time = PROG222_1;
          temp1.laser2_time = PROG222_2;
          temp1.laser3_time = PROG222_3;
          temp1.laser4_time = PROG222_4;
          strcpy(temp1.string1, PROG222_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 223:
          temp1.laser1_time = PROG223_1;
          temp1.laser2_time = PROG223_2;
          temp1.laser3_time = PROG223_3;
          temp1.laser4_time = PROG223_4;
          strcpy(temp1.string1, PROG223_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 224:
          temp1.laser1_time = PROG224_1;
          temp1.laser2_time = PROG224_2;
          temp1.laser3_time = PROG224_3;
          temp1.laser4_time = PROG224_4;
          strcpy(temp1.string1, PROG224_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 225:
          temp1.laser1_time = PROG225_1;
          temp1.laser2_time = PROG225_2;
          temp1.laser3_time = PROG225_3;
          temp1.laser4_time = PROG225_4;
          strcpy(temp1.string1, PROG225_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 226:
          temp1.laser1_time = PROG226_1;
          temp1.laser2_time = PROG226_2;
          temp1.laser3_time = PROG226_3;
          temp1.laser4_time = PROG226_4;
          strcpy(temp1.string1, PROG226_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 227:
          temp1.laser1_time = PROG227_1;
          temp1.laser2_time = PROG227_2;
          temp1.laser3_time = PROG227_3;
          temp1.laser4_time = PROG227_4;
          strcpy(temp1.string1, PROG227_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 228:
          temp1.laser1_time = PROG228_1;
          temp1.laser2_time = PROG228_2;
          temp1.laser3_time = PROG228_3;
          temp1.laser4_time = PROG228_4;
          strcpy(temp1.string1, PROG228_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 229:
          temp1.laser1_time = PROG229_1;
          temp1.laser2_time = PROG229_2;
          temp1.laser3_time = PROG229_3;
          temp1.laser4_time = PROG229_4;
          strcpy(temp1.string1, PROG229_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 230:
          temp1.laser1_time = PROG230_1;
          temp1.laser2_time = PROG230_2;
          temp1.laser3_time = PROG230_3;
          temp1.laser4_time = PROG230_4;
          strcpy(temp1.string1, PROG230_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 231:
          temp1.laser1_time = PROG231_1;
          temp1.laser2_time = PROG231_2;
          temp1.laser3_time = PROG231_3;
          temp1.laser4_time = PROG231_4;
          strcpy(temp1.string1, PROG231_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 232:
          temp1.laser1_time = PROG232_1;
          temp1.laser2_time = PROG232_2;
          temp1.laser3_time = PROG232_3;
          temp1.laser4_time = PROG232_4;
          strcpy(temp1.string1, PROG232_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 233:
          temp1.laser1_time = PROG233_1;
          temp1.laser2_time = PROG233_2;
          temp1.laser3_time = PROG233_3;
          temp1.laser4_time = PROG233_4;
          strcpy(temp1.string1, PROG233_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 234:
          temp1.laser1_time = PROG234_1;
          temp1.laser2_time = PROG234_2;
          temp1.laser3_time = PROG234_3;
          temp1.laser4_time = PROG234_4;
          strcpy(temp1.string1, PROG234_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 235:
          temp1.laser1_time = PROG235_1;
          temp1.laser2_time = PROG235_2;
          temp1.laser3_time = PROG235_3;
          temp1.laser4_time = PROG235_4;
          strcpy(temp1.string1, PROG235_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 236:
          temp1.laser1_time = PROG236_1;
          temp1.laser2_time = PROG236_2;
          temp1.laser3_time = PROG236_3;
          temp1.laser4_time = PROG236_4;
          strcpy(temp1.string1, PROG236_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 237:
          temp1.laser1_time = PROG237_1;
          temp1.laser2_time = PROG237_2;
          temp1.laser3_time = PROG237_3;
          temp1.laser4_time = PROG237_4;
          strcpy(temp1.string1, PROG237_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 238:
          temp1.laser1_time = PROG238_1;
          temp1.laser2_time = PROG238_2;
          temp1.laser3_time = PROG238_3;
          temp1.laser4_time = PROG238_4;
          strcpy(temp1.string1, PROG238_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 239:
          temp1.laser1_time = PROG239_1;
          temp1.laser2_time = PROG239_2;
          temp1.laser3_time = PROG239_3;
          temp1.laser4_time = PROG239_4;
          strcpy(temp1.string1, PROG239_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 240:
          temp1.laser1_time = PROG240_1;
          temp1.laser2_time = PROG240_2;
          temp1.laser3_time = PROG240_3;
          temp1.laser4_time = PROG240_4;
          strcpy(temp1.string1, PROG240_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 241:
          temp1.laser1_time = PROG241_1;
          temp1.laser2_time = PROG241_2;
          temp1.laser3_time = PROG241_3;
          temp1.laser4_time = PROG241_4;
          strcpy(temp1.string1, PROG241_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 242:
          temp1.laser1_time = PROG242_1;
          temp1.laser2_time = PROG242_2;
          temp1.laser3_time = PROG242_3;
          temp1.laser4_time = PROG242_4;
          strcpy(temp1.string1, PROG242_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 243:
          temp1.laser1_time = PROG243_1;
          temp1.laser2_time = PROG243_2;
          temp1.laser3_time = PROG243_3;
          temp1.laser4_time = PROG243_4;
          strcpy(temp1.string1, PROG243_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 244:
          temp1.laser1_time = PROG244_1;
          temp1.laser2_time = PROG244_2;
          temp1.laser3_time = PROG244_3;
          temp1.laser4_time = PROG244_4;
          strcpy(temp1.string1, PROG244_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 245:
          temp1.laser1_time = PROG245_1;
          temp1.laser2_time = PROG245_2;
          temp1.laser3_time = PROG245_3;
          temp1.laser4_time = PROG245_4;
          strcpy(temp1.string1, PROG245_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 246:
          temp1.laser1_time = PROG246_1;
          temp1.laser2_time = PROG246_2;
          temp1.laser3_time = PROG246_3;
          temp1.laser4_time = PROG246_4;
          strcpy(temp1.string1, PROG246_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 247:
          temp1.laser1_time = PROG247_1;
          temp1.laser2_time = PROG247_2;
          temp1.laser3_time = PROG247_3;
          temp1.laser4_time = PROG247_4;
          strcpy(temp1.string1, PROG247_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 248:
          temp1.laser1_time = PROG248_1;
          temp1.laser2_time = PROG248_2;
          temp1.laser3_time = PROG248_3;
          temp1.laser4_time = PROG248_4;
          strcpy(temp1.string1, PROG248_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 249:
          temp1.laser1_time = PROG249_1;
          temp1.laser2_time = PROG249_2;
          temp1.laser3_time = PROG249_3;
          temp1.laser4_time = PROG249_4;
          strcpy(temp1.string1, PROG249_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 250:
          temp1.laser1_time = PROG250_1;
          temp1.laser2_time = PROG250_2;
          temp1.laser3_time = PROG250_3;
          temp1.laser4_time = PROG250_4;
          strcpy(temp1.string1, PROG250_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 251:
          temp1.laser1_time = PROG251_1;
          temp1.laser2_time = PROG251_2;
          temp1.laser3_time = PROG251_3;
          temp1.laser4_time = PROG251_4;
          strcpy(temp1.string1, PROG251_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 252:
          temp1.laser1_time = PROG252_1;
          temp1.laser2_time = PROG252_2;
          temp1.laser3_time = PROG252_3;
          temp1.laser4_time = PROG252_4;
          strcpy(temp1.string1, PROG252_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 253:
          temp1.laser1_time = PROG253_1;
          temp1.laser2_time = PROG253_2;
          temp1.laser3_time = PROG253_3;
          temp1.laser4_time = PROG253_4;
          strcpy(temp1.string1, PROG253_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 254:
          temp1.laser1_time = PROG254_1;
          temp1.laser2_time = PROG254_2;
          temp1.laser3_time = PROG254_3;
          temp1.laser4_time = PROG254_4;
          strcpy(temp1.string1, PROG254_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 255:
          temp1.laser1_time = PROG255_1;
          temp1.laser2_time = PROG255_2;
          temp1.laser3_time = PROG255_3;
          temp1.laser4_time = PROG255_4;
          strcpy(temp1.string1, PROG255_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 256:
          temp1.laser1_time = PROG256_1;
          temp1.laser2_time = PROG256_2;
          temp1.laser3_time = PROG256_3;
          temp1.laser4_time = PROG256_4;
          strcpy(temp1.string1, PROG256_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 257:
          temp1.laser1_time = PROG257_1;
          temp1.laser2_time = PROG257_2;
          temp1.laser3_time = PROG257_3;
          temp1.laser4_time = PROG257_4;
          strcpy(temp1.string1, PROG257_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 258:
          temp1.laser1_time = PROG258_1;
          temp1.laser2_time = PROG258_2;
          temp1.laser3_time = PROG258_3;
          temp1.laser4_time = PROG258_4;
          strcpy(temp1.string1, PROG258_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 259:
          temp1.laser1_time = PROG259_1;
          temp1.laser2_time = PROG259_2;
          temp1.laser3_time = PROG259_3;
          temp1.laser4_time = PROG259_4;
          strcpy(temp1.string1, PROG259_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 260:
          temp1.laser1_time = PROG260_1;
          temp1.laser2_time = PROG260_2;
          temp1.laser3_time = PROG260_3;
          temp1.laser4_time = PROG260_4;
          strcpy(temp1.string1, PROG260_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 261:
          temp1.laser1_time = PROG261_1;
          temp1.laser2_time = PROG261_2;
          temp1.laser3_time = PROG261_3;
          temp1.laser4_time = PROG261_4;
          strcpy(temp1.string1, PROG261_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 262:
          temp1.laser1_time = PROG262_1;
          temp1.laser2_time = PROG262_2;
          temp1.laser3_time = PROG262_3;
          temp1.laser4_time = PROG262_4;
          strcpy(temp1.string1, PROG262_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 263:
          temp1.laser1_time = PROG263_1;
          temp1.laser2_time = PROG263_2;
          temp1.laser3_time = PROG263_3;
          temp1.laser4_time = PROG263_4;
          strcpy(temp1.string1, PROG263_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 264:
          temp1.laser1_time = PROG264_1;
          temp1.laser2_time = PROG264_2;
          temp1.laser3_time = PROG264_3;
          temp1.laser4_time = PROG264_4;
          strcpy(temp1.string1, PROG264_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 265:
          temp1.laser1_time = PROG265_1;
          temp1.laser2_time = PROG265_2;
          temp1.laser3_time = PROG265_3;
          temp1.laser4_time = PROG265_4;
          strcpy(temp1.string1, PROG265_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 266:
          temp1.laser1_time = PROG266_1;
          temp1.laser2_time = PROG266_2;
          temp1.laser3_time = PROG266_3;
          temp1.laser4_time = PROG266_4;
          strcpy(temp1.string1, PROG266_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 267:
          temp1.laser1_time = PROG267_1;
          temp1.laser2_time = PROG267_2;
          temp1.laser3_time = PROG267_3;
          temp1.laser4_time = PROG267_4;
		  strcpy(temp1.string1, PROG267_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 268:
          temp1.laser1_time = PROG268_1;
          temp1.laser2_time = PROG268_2;
          temp1.laser3_time = PROG268_3;
          temp1.laser4_time = PROG268_4;
		  strcpy(temp1.string1, PROG268_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 269:
          temp1.laser1_time = PROG269_1;
          temp1.laser2_time = PROG269_2;
          temp1.laser3_time = PROG269_3;
          temp1.laser4_time = PROG269_4;
		  strcpy(temp1.string1, PROG269_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 270:
          temp1.laser1_time = PROG270_1;
          temp1.laser2_time = PROG270_2;
          temp1.laser3_time = PROG270_3;
          temp1.laser4_time = PROG270_4;
		  strcpy(temp1.string1, PROG270_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 271:
          temp1.laser1_time = PROG271_1;
          temp1.laser2_time = PROG271_2;
          temp1.laser3_time = PROG271_3;
          temp1.laser4_time = PROG271_4;
		  strcpy(temp1.string1, PROG271_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 272:
          temp1.laser1_time = PROG272_1;
          temp1.laser2_time = PROG272_2;
          temp1.laser3_time = PROG272_3;
          temp1.laser4_time = PROG272_4;
		  strcpy(temp1.string1, PROG272_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 273:
          temp1.laser1_time = PROG273_1;
          temp1.laser2_time = PROG273_2;
          temp1.laser3_time = PROG273_3;
          temp1.laser4_time = PROG273_4;
		  strcpy(temp1.string1, PROG273_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 274:
          temp1.laser1_time = PROG274_1;
          temp1.laser2_time = PROG274_2;
          temp1.laser3_time = PROG274_3;
          temp1.laser4_time = PROG274_4;
		  strcpy(temp1.string1, PROG274_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 275:
          temp1.laser1_time = PROG275_1;
          temp1.laser2_time = PROG275_2;
          temp1.laser3_time = PROG275_3;
          temp1.laser4_time = PROG275_4;
		  strcpy(temp1.string1, PROG275_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 276:
          temp1.laser1_time = PROG276_1;
          temp1.laser2_time = PROG276_2;
          temp1.laser3_time = PROG276_3;
          temp1.laser4_time = PROG276_4;
		  strcpy(temp1.string1, PROG276_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 277:
          temp1.laser1_time = PROG277_1;
          temp1.laser2_time = PROG277_2;
          temp1.laser3_time = PROG277_3;
          temp1.laser4_time = PROG277_4;
		  strcpy(temp1.string1, PROG277_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 278:
          temp1.laser1_time = PROG278_1;
          temp1.laser2_time = PROG278_2;
          temp1.laser3_time = PROG278_3;
          temp1.laser4_time = PROG278_4;
		  strcpy(temp1.string1, PROG278_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 279:
          temp1.laser1_time = PROG279_1;
          temp1.laser2_time = PROG279_2;
          temp1.laser3_time = PROG279_3;
          temp1.laser4_time = PROG279_4;
		  strcpy(temp1.string1, PROG279_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 280:
          temp1.laser1_time = PROG280_1;
          temp1.laser2_time = PROG280_2;
          temp1.laser3_time = PROG280_3;
          temp1.laser4_time = PROG280_4;
		  strcpy(temp1.string1, PROG280_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 281:
          temp1.laser1_time = PROG281_1;
          temp1.laser2_time = PROG281_2;
          temp1.laser3_time = PROG281_3;
          temp1.laser4_time = PROG281_4;
		  strcpy(temp1.string1, PROG281_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 282:
          temp1.laser1_time = PROG282_1;
          temp1.laser2_time = PROG282_2;
          temp1.laser3_time = PROG282_3;
          temp1.laser4_time = PROG282_4;
		  strcpy(temp1.string1, PROG282_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 283:
          temp1.laser1_time = PROG283_1;
          temp1.laser2_time = PROG283_2;
          temp1.laser3_time = PROG283_3;
          temp1.laser4_time = PROG283_4;
		  strcpy(temp1.string1, PROG283_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 284:
          temp1.laser1_time = PROG284_1;
          temp1.laser2_time = PROG284_2;
          temp1.laser3_time = PROG284_3;
          temp1.laser4_time = PROG284_4;
		  strcpy(temp1.string1, PROG284_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 285:
          temp1.laser1_time = PROG285_1;
          temp1.laser2_time = PROG285_2;
          temp1.laser3_time = PROG285_3;
          temp1.laser4_time = PROG285_4;
		  strcpy(temp1.string1, PROG285_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 286:
          temp1.laser1_time = PROG286_1;
          temp1.laser2_time = PROG286_2;
          temp1.laser3_time = PROG286_3;
          temp1.laser4_time = PROG286_4;
		  strcpy(temp1.string1, PROG286_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 287:
          temp1.laser1_time = PROG287_1;
          temp1.laser2_time = PROG287_2;
          temp1.laser3_time = PROG287_3;
          temp1.laser4_time = PROG287_4;
		  strcpy(temp1.string1, PROG287_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 288:
          temp1.laser1_time = PROG288_1;
          temp1.laser2_time = PROG288_2;
          temp1.laser3_time = PROG288_3;
          temp1.laser4_time = PROG288_4;
		  strcpy(temp1.string1, PROG288_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 289:
          temp1.laser1_time = PROG289_1;
          temp1.laser2_time = PROG289_2;
          temp1.laser3_time = PROG289_3;
          temp1.laser4_time = PROG289_4;
		  strcpy(temp1.string1, PROG289_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 290:
          temp1.laser1_time = PROG290_1;
          temp1.laser2_time = PROG290_2;
          temp1.laser3_time = PROG290_3;
          temp1.laser4_time = PROG290_4;
		  strcpy(temp1.string1, PROG290_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 291:
          temp1.laser1_time = PROG291_1;
          temp1.laser2_time = PROG291_2;
          temp1.laser3_time = PROG291_3;
          temp1.laser4_time = PROG291_4;
		  strcpy(temp1.string1, PROG291_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 292:
          temp1.laser1_time = PROG292_1;
          temp1.laser2_time = PROG292_2;
          temp1.laser3_time = PROG292_3;
          temp1.laser4_time = PROG292_4;
		  strcpy(temp1.string1, PROG292_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 293:
          temp1.laser1_time = PROG293_1;
          temp1.laser2_time = PROG293_2;
          temp1.laser3_time = PROG293_3;
          temp1.laser4_time = PROG293_4;
		  strcpy(temp1.string1, PROG293_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 294:
          temp1.laser1_time = PROG294_1;
          temp1.laser2_time = PROG294_2;
          temp1.laser3_time = PROG294_3;
          temp1.laser4_time = PROG294_4;
		  strcpy(temp1.string1, PROG294_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 295:
          temp1.laser1_time = PROG295_1;
          temp1.laser2_time = PROG295_2;
          temp1.laser3_time = PROG295_3;
          temp1.laser4_time = PROG295_4;
		  strcpy(temp1.string1, PROG295_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 296:
          temp1.laser1_time = PROG296_1;
          temp1.laser2_time = PROG296_2;
          temp1.laser3_time = PROG296_3;
          temp1.laser4_time = PROG296_4;
		  strcpy(temp1.string1, PROG296_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 297:
          temp1.laser1_time = PROG297_1;
          temp1.laser2_time = PROG297_2;
          temp1.laser3_time = PROG297_3;
          temp1.laser4_time = PROG297_4;
		  strcpy(temp1.string1, PROG297_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 298:
          temp1.laser1_time = PROG298_1;
          temp1.laser2_time = PROG298_2;
          temp1.laser3_time = PROG298_3;
          temp1.laser4_time = PROG298_4;
		  strcpy(temp1.string1, PROG298_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 299:
          temp1.laser1_time = PROG299_1;
          temp1.laser2_time = PROG299_2;
          temp1.laser3_time = PROG299_3;
          temp1.laser4_time = PROG299_4;
		  strcpy(temp1.string1, PROG299_STRING);
		  temp1.entry_flg = 1;
		  break;
//CASE300
		case 300:
          temp1.laser1_time = PROG300_1;
          temp1.laser2_time = PROG300_2;
          temp1.laser3_time = PROG300_3;
          temp1.laser4_time = PROG300_4;
          strcpy(temp1.string1, PROG300_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 301:
          temp1.laser1_time = PROG301_1;
          temp1.laser2_time = PROG301_2;
          temp1.laser3_time = PROG301_3;
          temp1.laser4_time = PROG301_4;
          strcpy(temp1.string1, PROG301_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 302:
          temp1.laser1_time = PROG302_1;
          temp1.laser2_time = PROG302_2;
          temp1.laser3_time = PROG302_3;
          temp1.laser4_time = PROG302_4;
          strcpy(temp1.string1, PROG302_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 303:
          temp1.laser1_time = PROG303_1;
          temp1.laser2_time = PROG303_2;
          temp1.laser3_time = PROG303_3;
          temp1.laser4_time = PROG303_4;
          strcpy(temp1.string1, PROG303_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 304:
          temp1.laser1_time = PROG304_1;
          temp1.laser2_time = PROG304_2;
          temp1.laser3_time = PROG304_3;
          temp1.laser4_time = PROG304_4;
          strcpy(temp1.string1, PROG304_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 305:
          temp1.laser1_time = PROG305_1;
          temp1.laser2_time = PROG305_2;
          temp1.laser3_time = PROG305_3;
          temp1.laser4_time = PROG305_4;
          strcpy(temp1.string1, PROG305_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 306:
          temp1.laser1_time = PROG306_1;
          temp1.laser2_time = PROG306_2;
          temp1.laser3_time = PROG306_3;
          temp1.laser4_time = PROG306_4;
          strcpy(temp1.string1, PROG306_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 307:
          temp1.laser1_time = PROG307_1;
          temp1.laser2_time = PROG307_2;
          temp1.laser3_time = PROG307_3;
          temp1.laser4_time = PROG307_4;
          strcpy(temp1.string1, PROG307_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 308:
          temp1.laser1_time = PROG308_1;
          temp1.laser2_time = PROG308_2;
          temp1.laser3_time = PROG308_3;
          temp1.laser4_time = PROG308_4;
          strcpy(temp1.string1, PROG308_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 309:
          temp1.laser1_time = PROG309_1;
          temp1.laser2_time = PROG309_2;
          temp1.laser3_time = PROG309_3;
          temp1.laser4_time = PROG309_4;
          strcpy(temp1.string1, PROG309_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 310:
          temp1.laser1_time = PROG310_1;
          temp1.laser2_time = PROG310_2;
          temp1.laser3_time = PROG310_3;
          temp1.laser4_time = PROG310_4;
          strcpy(temp1.string1, PROG310_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 311:
          temp1.laser1_time = PROG311_1;
          temp1.laser2_time = PROG311_2;
          temp1.laser3_time = PROG311_3;
          temp1.laser4_time = PROG311_4;
          strcpy(temp1.string1, PROG311_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 312:
          temp1.laser1_time = PROG312_1;
          temp1.laser2_time = PROG312_2;
          temp1.laser3_time = PROG312_3;
          temp1.laser4_time = PROG312_4;
          strcpy(temp1.string1, PROG312_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 313:
          temp1.laser1_time = PROG313_1;
          temp1.laser2_time = PROG313_2;
          temp1.laser3_time = PROG313_3;
          temp1.laser4_time = PROG313_4;
          strcpy(temp1.string1, PROG313_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 314:
          temp1.laser1_time = PROG314_1;
          temp1.laser2_time = PROG314_2;
          temp1.laser3_time = PROG314_3;
          temp1.laser4_time = PROG314_4;
          strcpy(temp1.string1, PROG314_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 315:
          temp1.laser1_time = PROG315_1;
          temp1.laser2_time = PROG315_2;
          temp1.laser3_time = PROG315_3;
          temp1.laser4_time = PROG315_4;
          strcpy(temp1.string1, PROG315_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 316:
          temp1.laser1_time = PROG316_1;
          temp1.laser2_time = PROG316_2;
          temp1.laser3_time = PROG316_3;
          temp1.laser4_time = PROG316_4;
          strcpy(temp1.string1, PROG316_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 317:
          temp1.laser1_time = PROG317_1;
          temp1.laser2_time = PROG317_2;
          temp1.laser3_time = PROG317_3;
          temp1.laser4_time = PROG317_4;
          strcpy(temp1.string1, PROG317_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 318:
          temp1.laser1_time = PROG318_1;
          temp1.laser2_time = PROG318_2;
          temp1.laser3_time = PROG318_3;
          temp1.laser4_time = PROG318_4;
          strcpy(temp1.string1, PROG318_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 319:
          temp1.laser1_time = PROG319_1;
          temp1.laser2_time = PROG319_2;
          temp1.laser3_time = PROG319_3;
          temp1.laser4_time = PROG319_4;
          strcpy(temp1.string1, PROG319_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 320:
          temp1.laser1_time = PROG320_1;
          temp1.laser2_time = PROG320_2;
          temp1.laser3_time = PROG320_3;
          temp1.laser4_time = PROG320_4;
          strcpy(temp1.string1, PROG320_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 321:
          temp1.laser1_time = PROG321_1;
          temp1.laser2_time = PROG321_2;
          temp1.laser3_time = PROG321_3;
          temp1.laser4_time = PROG321_4;
          strcpy(temp1.string1, PROG321_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 322:
          temp1.laser1_time = PROG322_1;
          temp1.laser2_time = PROG322_2;
          temp1.laser3_time = PROG322_3;
          temp1.laser4_time = PROG322_4;
          strcpy(temp1.string1, PROG322_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 323:
          temp1.laser1_time = PROG323_1;
          temp1.laser2_time = PROG323_2;
          temp1.laser3_time = PROG323_3;
          temp1.laser4_time = PROG323_4;
          strcpy(temp1.string1, PROG323_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 324:
          temp1.laser1_time = PROG324_1;
          temp1.laser2_time = PROG324_2;
          temp1.laser3_time = PROG324_3;
          temp1.laser4_time = PROG324_4;
          strcpy(temp1.string1, PROG324_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 325:
          temp1.laser1_time = PROG325_1;
          temp1.laser2_time = PROG325_2;
          temp1.laser3_time = PROG325_3;
          temp1.laser4_time = PROG325_4;
          strcpy(temp1.string1, PROG325_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 326:
          temp1.laser1_time = PROG326_1;
          temp1.laser2_time = PROG326_2;
          temp1.laser3_time = PROG326_3;
          temp1.laser4_time = PROG326_4;
          strcpy(temp1.string1, PROG326_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 327:
          temp1.laser1_time = PROG327_1;
          temp1.laser2_time = PROG327_2;
          temp1.laser3_time = PROG327_3;
          temp1.laser4_time = PROG327_4;
          strcpy(temp1.string1, PROG327_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 328:
          temp1.laser1_time = PROG328_1;
          temp1.laser2_time = PROG328_2;
          temp1.laser3_time = PROG328_3;
          temp1.laser4_time = PROG328_4;
          strcpy(temp1.string1, PROG328_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 329:
          temp1.laser1_time = PROG329_1;
          temp1.laser2_time = PROG329_2;
          temp1.laser3_time = PROG329_3;
          temp1.laser4_time = PROG329_4;
          strcpy(temp1.string1, PROG329_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 330:
          temp1.laser1_time = PROG330_1;
          temp1.laser2_time = PROG330_2;
          temp1.laser3_time = PROG330_3;
          temp1.laser4_time = PROG330_4;
          strcpy(temp1.string1, PROG330_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 331:
          temp1.laser1_time = PROG331_1;
          temp1.laser2_time = PROG331_2;
          temp1.laser3_time = PROG331_3;
          temp1.laser4_time = PROG331_4;
          strcpy(temp1.string1, PROG331_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 332:
          temp1.laser1_time = PROG332_1;
          temp1.laser2_time = PROG332_2;
          temp1.laser3_time = PROG332_3;
          temp1.laser4_time = PROG332_4;
          strcpy(temp1.string1, PROG332_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 333:
          temp1.laser1_time = PROG333_1;
          temp1.laser2_time = PROG333_2;
          temp1.laser3_time = PROG333_3;
          temp1.laser4_time = PROG333_4;
          strcpy(temp1.string1, PROG333_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 334:
          temp1.laser1_time = PROG334_1;
          temp1.laser2_time = PROG334_2;
          temp1.laser3_time = PROG334_3;
          temp1.laser4_time = PROG334_4;
          strcpy(temp1.string1, PROG334_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 335:
          temp1.laser1_time = PROG335_1;
          temp1.laser2_time = PROG335_2;
          temp1.laser3_time = PROG335_3;
          temp1.laser4_time = PROG335_4;
          strcpy(temp1.string1, PROG335_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 336:
          temp1.laser1_time = PROG336_1;
          temp1.laser2_time = PROG336_2;
          temp1.laser3_time = PROG336_3;
          temp1.laser4_time = PROG336_4;
          strcpy(temp1.string1, PROG336_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 337:
          temp1.laser1_time = PROG337_1;
          temp1.laser2_time = PROG337_2;
          temp1.laser3_time = PROG337_3;
          temp1.laser4_time = PROG337_4;
          strcpy(temp1.string1, PROG337_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 338:
          temp1.laser1_time = PROG338_1;
          temp1.laser2_time = PROG338_2;
          temp1.laser3_time = PROG338_3;
          temp1.laser4_time = PROG338_4;
          strcpy(temp1.string1, PROG338_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 339:
          temp1.laser1_time = PROG339_1;
          temp1.laser2_time = PROG339_2;
          temp1.laser3_time = PROG339_3;
          temp1.laser4_time = PROG339_4;
          strcpy(temp1.string1, PROG339_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 340:
          temp1.laser1_time = PROG340_1;
          temp1.laser2_time = PROG340_2;
          temp1.laser3_time = PROG340_3;
          temp1.laser4_time = PROG340_4;
          strcpy(temp1.string1, PROG340_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 341:
          temp1.laser1_time = PROG341_1;
          temp1.laser2_time = PROG341_2;
          temp1.laser3_time = PROG341_3;
          temp1.laser4_time = PROG341_4;
          strcpy(temp1.string1, PROG341_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 342:
          temp1.laser1_time = PROG342_1;
          temp1.laser2_time = PROG342_2;
          temp1.laser3_time = PROG342_3;
          temp1.laser4_time = PROG342_4;
          strcpy(temp1.string1, PROG342_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 343:
          temp1.laser1_time = PROG343_1;
          temp1.laser2_time = PROG343_2;
          temp1.laser3_time = PROG343_3;
          temp1.laser4_time = PROG343_4;
          strcpy(temp1.string1, PROG343_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 344:
          temp1.laser1_time = PROG344_1;
          temp1.laser2_time = PROG344_2;
          temp1.laser3_time = PROG344_3;
          temp1.laser4_time = PROG344_4;
          strcpy(temp1.string1, PROG344_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 345:
          temp1.laser1_time = PROG345_1;
          temp1.laser2_time = PROG345_2;
          temp1.laser3_time = PROG345_3;
          temp1.laser4_time = PROG345_4;
          strcpy(temp1.string1, PROG345_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 346:
          temp1.laser1_time = PROG346_1;
          temp1.laser2_time = PROG346_2;
          temp1.laser3_time = PROG346_3;
          temp1.laser4_time = PROG346_4;
          strcpy(temp1.string1, PROG346_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 347:
          temp1.laser1_time = PROG347_1;
          temp1.laser2_time = PROG347_2;
          temp1.laser3_time = PROG347_3;
          temp1.laser4_time = PROG347_4;
          strcpy(temp1.string1, PROG347_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 348:
          temp1.laser1_time = PROG348_1;
          temp1.laser2_time = PROG348_2;
          temp1.laser3_time = PROG348_3;
          temp1.laser4_time = PROG348_4;
          strcpy(temp1.string1, PROG348_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 349:
          temp1.laser1_time = PROG349_1;
          temp1.laser2_time = PROG349_2;
          temp1.laser3_time = PROG349_3;
          temp1.laser4_time = PROG349_4;
          strcpy(temp1.string1, PROG349_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 350:
          temp1.laser1_time = PROG350_1;
          temp1.laser2_time = PROG350_2;
          temp1.laser3_time = PROG350_3;
          temp1.laser4_time = PROG350_4;
          strcpy(temp1.string1, PROG350_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 351:
          temp1.laser1_time = PROG351_1;
          temp1.laser2_time = PROG351_2;
          temp1.laser3_time = PROG351_3;
          temp1.laser4_time = PROG351_4;
          strcpy(temp1.string1, PROG351_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 352:
          temp1.laser1_time = PROG352_1;
          temp1.laser2_time = PROG352_2;
          temp1.laser3_time = PROG352_3;
          temp1.laser4_time = PROG352_4;
          strcpy(temp1.string1, PROG352_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 353:
          temp1.laser1_time = PROG353_1;
          temp1.laser2_time = PROG353_2;
          temp1.laser3_time = PROG353_3;
          temp1.laser4_time = PROG353_4;
          strcpy(temp1.string1, PROG353_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 354:
          temp1.laser1_time = PROG354_1;
          temp1.laser2_time = PROG354_2;
          temp1.laser3_time = PROG354_3;
          temp1.laser4_time = PROG354_4;
          strcpy(temp1.string1, PROG354_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 355:
          temp1.laser1_time = PROG355_1;
          temp1.laser2_time = PROG355_2;
          temp1.laser3_time = PROG355_3;
          temp1.laser4_time = PROG355_4;
          strcpy(temp1.string1, PROG355_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 356:
          temp1.laser1_time = PROG356_1;
          temp1.laser2_time = PROG356_2;
          temp1.laser3_time = PROG356_3;
          temp1.laser4_time = PROG356_4;
          strcpy(temp1.string1, PROG356_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 357:
          temp1.laser1_time = PROG357_1;
          temp1.laser2_time = PROG357_2;
          temp1.laser3_time = PROG357_3;
          temp1.laser4_time = PROG357_4;
          strcpy(temp1.string1, PROG357_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 358:
          temp1.laser1_time = PROG358_1;
          temp1.laser2_time = PROG358_2;
          temp1.laser3_time = PROG358_3;
          temp1.laser4_time = PROG358_4;
          strcpy(temp1.string1, PROG358_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 359:
          temp1.laser1_time = PROG359_1;
          temp1.laser2_time = PROG359_2;
          temp1.laser3_time = PROG359_3;
          temp1.laser4_time = PROG359_4;
          strcpy(temp1.string1, PROG359_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 360:
          temp1.laser1_time = PROG360_1;
          temp1.laser2_time = PROG360_2;
          temp1.laser3_time = PROG360_3;
          temp1.laser4_time = PROG360_4;
          strcpy(temp1.string1, PROG360_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 361:
          temp1.laser1_time = PROG361_1;
          temp1.laser2_time = PROG361_2;
          temp1.laser3_time = PROG361_3;
          temp1.laser4_time = PROG361_4;
          strcpy(temp1.string1, PROG361_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 362:
          temp1.laser1_time = PROG362_1;
          temp1.laser2_time = PROG362_2;
          temp1.laser3_time = PROG362_3;
          temp1.laser4_time = PROG362_4;
          strcpy(temp1.string1, PROG362_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 363:
          temp1.laser1_time = PROG363_1;
          temp1.laser2_time = PROG363_2;
          temp1.laser3_time = PROG363_3;
          temp1.laser4_time = PROG363_4;
          strcpy(temp1.string1, PROG363_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 364:
          temp1.laser1_time = PROG364_1;
          temp1.laser2_time = PROG364_2;
          temp1.laser3_time = PROG364_3;
          temp1.laser4_time = PROG364_4;
          strcpy(temp1.string1, PROG364_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 365:
          temp1.laser1_time = PROG365_1;
          temp1.laser2_time = PROG365_2;
          temp1.laser3_time = PROG365_3;
          temp1.laser4_time = PROG365_4;
          strcpy(temp1.string1, PROG365_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 366:
          temp1.laser1_time = PROG366_1;
          temp1.laser2_time = PROG366_2;
          temp1.laser3_time = PROG366_3;
          temp1.laser4_time = PROG366_4;
          strcpy(temp1.string1, PROG366_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 367:
          temp1.laser1_time = PROG367_1;
          temp1.laser2_time = PROG367_2;
          temp1.laser3_time = PROG367_3;
          temp1.laser4_time = PROG367_4;
		  strcpy(temp1.string1, PROG367_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 368:
          temp1.laser1_time = PROG368_1;
          temp1.laser2_time = PROG368_2;
          temp1.laser3_time = PROG368_3;
          temp1.laser4_time = PROG368_4;
		  strcpy(temp1.string1, PROG368_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 369:
          temp1.laser1_time = PROG369_1;
          temp1.laser2_time = PROG369_2;
          temp1.laser3_time = PROG369_3;
          temp1.laser4_time = PROG369_4;
		  strcpy(temp1.string1, PROG369_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 370:
          temp1.laser1_time = PROG370_1;
          temp1.laser2_time = PROG370_2;
          temp1.laser3_time = PROG370_3;
          temp1.laser4_time = PROG370_4;
		  strcpy(temp1.string1, PROG370_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 371:
          temp1.laser1_time = PROG371_1;
          temp1.laser2_time = PROG371_2;
          temp1.laser3_time = PROG371_3;
          temp1.laser4_time = PROG371_4;
		  strcpy(temp1.string1, PROG371_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 372:
          temp1.laser1_time = PROG372_1;
          temp1.laser2_time = PROG372_2;
          temp1.laser3_time = PROG372_3;
          temp1.laser4_time = PROG372_4;
		  strcpy(temp1.string1, PROG372_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 373:
          temp1.laser1_time = PROG373_1;
          temp1.laser2_time = PROG373_2;
          temp1.laser3_time = PROG373_3;
          temp1.laser4_time = PROG373_4;
		  strcpy(temp1.string1, PROG373_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 374:
          temp1.laser1_time = PROG374_1;
          temp1.laser2_time = PROG374_2;
          temp1.laser3_time = PROG374_3;
          temp1.laser4_time = PROG374_4;
		  strcpy(temp1.string1, PROG374_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 375:
          temp1.laser1_time = PROG375_1;
          temp1.laser2_time = PROG375_2;
          temp1.laser3_time = PROG375_3;
          temp1.laser4_time = PROG375_4;
		  strcpy(temp1.string1, PROG375_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 376:
          temp1.laser1_time = PROG376_1;
          temp1.laser2_time = PROG376_2;
          temp1.laser3_time = PROG376_3;
          temp1.laser4_time = PROG376_4;
		  strcpy(temp1.string1, PROG376_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 377:
          temp1.laser1_time = PROG377_1;
          temp1.laser2_time = PROG377_2;
          temp1.laser3_time = PROG377_3;
          temp1.laser4_time = PROG377_4;
		  strcpy(temp1.string1, PROG377_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 378:
          temp1.laser1_time = PROG378_1;
          temp1.laser2_time = PROG378_2;
          temp1.laser3_time = PROG378_3;
          temp1.laser4_time = PROG378_4;
		  strcpy(temp1.string1, PROG378_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 379:
          temp1.laser1_time = PROG379_1;
          temp1.laser2_time = PROG379_2;
          temp1.laser3_time = PROG379_3;
          temp1.laser4_time = PROG379_4;
		  strcpy(temp1.string1, PROG379_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 380:
          temp1.laser1_time = PROG380_1;
          temp1.laser2_time = PROG380_2;
          temp1.laser3_time = PROG380_3;
          temp1.laser4_time = PROG380_4;
		  strcpy(temp1.string1, PROG380_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 381:
          temp1.laser1_time = PROG381_1;
          temp1.laser2_time = PROG381_2;
          temp1.laser3_time = PROG381_3;
          temp1.laser4_time = PROG381_4;
		  strcpy(temp1.string1, PROG381_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 382:
          temp1.laser1_time = PROG382_1;
          temp1.laser2_time = PROG382_2;
          temp1.laser3_time = PROG382_3;
          temp1.laser4_time = PROG382_4;
		  strcpy(temp1.string1, PROG382_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 383:
          temp1.laser1_time = PROG383_1;
          temp1.laser2_time = PROG383_2;
          temp1.laser3_time = PROG383_3;
          temp1.laser4_time = PROG383_4;
		  strcpy(temp1.string1, PROG383_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 384:
          temp1.laser1_time = PROG384_1;
          temp1.laser2_time = PROG384_2;
          temp1.laser3_time = PROG384_3;
          temp1.laser4_time = PROG384_4;
		  strcpy(temp1.string1, PROG384_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 385:
          temp1.laser1_time = PROG385_1;
          temp1.laser2_time = PROG385_2;
          temp1.laser3_time = PROG385_3;
          temp1.laser4_time = PROG385_4;
		  strcpy(temp1.string1, PROG385_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 386:
          temp1.laser1_time = PROG386_1;
          temp1.laser2_time = PROG386_2;
          temp1.laser3_time = PROG386_3;
          temp1.laser4_time = PROG386_4;
		  strcpy(temp1.string1, PROG386_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 387:
          temp1.laser1_time = PROG387_1;
          temp1.laser2_time = PROG387_2;
          temp1.laser3_time = PROG387_3;
          temp1.laser4_time = PROG387_4;
		  strcpy(temp1.string1, PROG387_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 388:
          temp1.laser1_time = PROG388_1;
          temp1.laser2_time = PROG388_2;
          temp1.laser3_time = PROG388_3;
          temp1.laser4_time = PROG388_4;
		  strcpy(temp1.string1, PROG388_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 389:
          temp1.laser1_time = PROG389_1;
          temp1.laser2_time = PROG389_2;
          temp1.laser3_time = PROG389_3;
          temp1.laser4_time = PROG389_4;
		  strcpy(temp1.string1, PROG389_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 390:
          temp1.laser1_time = PROG390_1;
          temp1.laser2_time = PROG390_2;
          temp1.laser3_time = PROG390_3;
          temp1.laser4_time = PROG390_4;
		  strcpy(temp1.string1, PROG390_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 391:
          temp1.laser1_time = PROG391_1;
          temp1.laser2_time = PROG391_2;
          temp1.laser3_time = PROG391_3;
          temp1.laser4_time = PROG391_4;
		  strcpy(temp1.string1, PROG391_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 392:
          temp1.laser1_time = PROG392_1;
          temp1.laser2_time = PROG392_2;
          temp1.laser3_time = PROG392_3;
          temp1.laser4_time = PROG392_4;
		  strcpy(temp1.string1, PROG392_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 393:
          temp1.laser1_time = PROG393_1;
          temp1.laser2_time = PROG393_2;
          temp1.laser3_time = PROG393_3;
          temp1.laser4_time = PROG393_4;
		  strcpy(temp1.string1, PROG393_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 394:
          temp1.laser1_time = PROG394_1;
          temp1.laser2_time = PROG394_2;
          temp1.laser3_time = PROG394_3;
          temp1.laser4_time = PROG394_4;
		  strcpy(temp1.string1, PROG394_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 395:
          temp1.laser1_time = PROG395_1;
          temp1.laser2_time = PROG395_2;
          temp1.laser3_time = PROG395_3;
          temp1.laser4_time = PROG395_4;
		  strcpy(temp1.string1, PROG395_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 396:
          temp1.laser1_time = PROG396_1;
          temp1.laser2_time = PROG396_2;
          temp1.laser3_time = PROG396_3;
          temp1.laser4_time = PROG396_4;
		  strcpy(temp1.string1, PROG396_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 397:
          temp1.laser1_time = PROG397_1;
          temp1.laser2_time = PROG397_2;
          temp1.laser3_time = PROG397_3;
          temp1.laser4_time = PROG397_4;
		  strcpy(temp1.string1, PROG397_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 398:
          temp1.laser1_time = PROG398_1;
          temp1.laser2_time = PROG398_2;
          temp1.laser3_time = PROG398_3;
          temp1.laser4_time = PROG398_4;
		  strcpy(temp1.string1, PROG398_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 399:
          temp1.laser1_time = PROG399_1;
          temp1.laser2_time = PROG399_2;
          temp1.laser3_time = PROG399_3;
          temp1.laser4_time = PROG399_4;
		  strcpy(temp1.string1, PROG399_STRING);
		  temp1.entry_flg = 1;
		  break;
//CASE400
		case 400:
          temp1.laser1_time = PROG400_1;
          temp1.laser2_time = PROG400_2;
          temp1.laser3_time = PROG400_3;
          temp1.laser4_time = PROG400_4;
          strcpy(temp1.string1, PROG400_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 401:
          temp1.laser1_time = PROG401_1;
          temp1.laser2_time = PROG401_2;
          temp1.laser3_time = PROG401_3;
          temp1.laser4_time = PROG401_4;
          strcpy(temp1.string1, PROG401_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 402:
          temp1.laser1_time = PROG402_1;
          temp1.laser2_time = PROG402_2;
          temp1.laser3_time = PROG402_3;
          temp1.laser4_time = PROG402_4;
          strcpy(temp1.string1, PROG402_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 403:
          temp1.laser1_time = PROG403_1;
          temp1.laser2_time = PROG403_2;
          temp1.laser3_time = PROG403_3;
          temp1.laser4_time = PROG403_4;
          strcpy(temp1.string1, PROG403_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 404:
          temp1.laser1_time = PROG404_1;
          temp1.laser2_time = PROG404_2;
          temp1.laser3_time = PROG404_3;
          temp1.laser4_time = PROG404_4;
          strcpy(temp1.string1, PROG404_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 405:
          temp1.laser1_time = PROG405_1;
          temp1.laser2_time = PROG405_2;
          temp1.laser3_time = PROG405_3;
          temp1.laser4_time = PROG405_4;
          strcpy(temp1.string1, PROG405_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 406:
          temp1.laser1_time = PROG406_1;
          temp1.laser2_time = PROG406_2;
          temp1.laser3_time = PROG406_3;
          temp1.laser4_time = PROG406_4;
          strcpy(temp1.string1, PROG406_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 407:
          temp1.laser1_time = PROG407_1;
          temp1.laser2_time = PROG407_2;
          temp1.laser3_time = PROG407_3;
          temp1.laser4_time = PROG407_4;
          strcpy(temp1.string1, PROG407_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 408:
          temp1.laser1_time = PROG408_1;
          temp1.laser2_time = PROG408_2;
          temp1.laser3_time = PROG408_3;
          temp1.laser4_time = PROG408_4;
          strcpy(temp1.string1, PROG408_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 409:
          temp1.laser1_time = PROG409_1;
          temp1.laser2_time = PROG409_2;
          temp1.laser3_time = PROG409_3;
          temp1.laser4_time = PROG409_4;
          strcpy(temp1.string1, PROG409_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 410:
          temp1.laser1_time = PROG410_1;
          temp1.laser2_time = PROG410_2;
          temp1.laser3_time = PROG410_3;
          temp1.laser4_time = PROG410_4;
          strcpy(temp1.string1, PROG410_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 411:
          temp1.laser1_time = PROG411_1;
          temp1.laser2_time = PROG411_2;
          temp1.laser3_time = PROG411_3;
          temp1.laser4_time = PROG411_4;
          strcpy(temp1.string1, PROG411_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 412:
          temp1.laser1_time = PROG412_1;
          temp1.laser2_time = PROG412_2;
          temp1.laser3_time = PROG412_3;
          temp1.laser4_time = PROG412_4;
          strcpy(temp1.string1, PROG412_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 413:
          temp1.laser1_time = PROG413_1;
          temp1.laser2_time = PROG413_2;
          temp1.laser3_time = PROG413_3;
          temp1.laser4_time = PROG413_4;
          strcpy(temp1.string1, PROG413_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 414:
          temp1.laser1_time = PROG414_1;
          temp1.laser2_time = PROG414_2;
          temp1.laser3_time = PROG414_3;
          temp1.laser4_time = PROG414_4;
          strcpy(temp1.string1, PROG414_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 415:
          temp1.laser1_time = PROG415_1;
          temp1.laser2_time = PROG415_2;
          temp1.laser3_time = PROG415_3;
          temp1.laser4_time = PROG415_4;
          strcpy(temp1.string1, PROG415_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 416:
          temp1.laser1_time = PROG416_1;
          temp1.laser2_time = PROG416_2;
          temp1.laser3_time = PROG416_3;
          temp1.laser4_time = PROG416_4;
          strcpy(temp1.string1, PROG416_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 417:
          temp1.laser1_time = PROG417_1;
          temp1.laser2_time = PROG417_2;
          temp1.laser3_time = PROG417_3;
          temp1.laser4_time = PROG417_4;
          strcpy(temp1.string1, PROG417_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 418:
          temp1.laser1_time = PROG418_1;
          temp1.laser2_time = PROG418_2;
          temp1.laser3_time = PROG418_3;
          temp1.laser4_time = PROG418_4;
          strcpy(temp1.string1, PROG418_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 419:
          temp1.laser1_time = PROG419_1;
          temp1.laser2_time = PROG419_2;
          temp1.laser3_time = PROG419_3;
          temp1.laser4_time = PROG419_4;
          strcpy(temp1.string1, PROG419_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 420:
          temp1.laser1_time = PROG420_1;
          temp1.laser2_time = PROG420_2;
          temp1.laser3_time = PROG420_3;
          temp1.laser4_time = PROG420_4;
          strcpy(temp1.string1, PROG420_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 421:
          temp1.laser1_time = PROG421_1;
          temp1.laser2_time = PROG421_2;
          temp1.laser3_time = PROG421_3;
          temp1.laser4_time = PROG421_4;
          strcpy(temp1.string1, PROG421_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 422:
          temp1.laser1_time = PROG422_1;
          temp1.laser2_time = PROG422_2;
          temp1.laser3_time = PROG422_3;
          temp1.laser4_time = PROG422_4;
          strcpy(temp1.string1, PROG422_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 423:
          temp1.laser1_time = PROG423_1;
          temp1.laser2_time = PROG423_2;
          temp1.laser3_time = PROG423_3;
          temp1.laser4_time = PROG423_4;
          strcpy(temp1.string1, PROG423_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 424:
          temp1.laser1_time = PROG424_1;
          temp1.laser2_time = PROG424_2;
          temp1.laser3_time = PROG424_3;
          temp1.laser4_time = PROG424_4;
          strcpy(temp1.string1, PROG424_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 425:
          temp1.laser1_time = PROG425_1;
          temp1.laser2_time = PROG425_2;
          temp1.laser3_time = PROG425_3;
          temp1.laser4_time = PROG425_4;
          strcpy(temp1.string1, PROG425_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 426:
          temp1.laser1_time = PROG426_1;
          temp1.laser2_time = PROG426_2;
          temp1.laser3_time = PROG426_3;
          temp1.laser4_time = PROG426_4;
          strcpy(temp1.string1, PROG426_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 427:
          temp1.laser1_time = PROG427_1;
          temp1.laser2_time = PROG427_2;
          temp1.laser3_time = PROG427_3;
          temp1.laser4_time = PROG427_4;
          strcpy(temp1.string1, PROG427_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 428:
          temp1.laser1_time = PROG428_1;
          temp1.laser2_time = PROG428_2;
          temp1.laser3_time = PROG428_3;
          temp1.laser4_time = PROG428_4;
          strcpy(temp1.string1, PROG428_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 429:
          temp1.laser1_time = PROG429_1;
          temp1.laser2_time = PROG429_2;
          temp1.laser3_time = PROG429_3;
          temp1.laser4_time = PROG429_4;
          strcpy(temp1.string1, PROG429_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 430:
          temp1.laser1_time = PROG430_1;
          temp1.laser2_time = PROG430_2;
          temp1.laser3_time = PROG430_3;
          temp1.laser4_time = PROG430_4;
          strcpy(temp1.string1, PROG430_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 431:
          temp1.laser1_time = PROG431_1;
          temp1.laser2_time = PROG431_2;
          temp1.laser3_time = PROG431_3;
          temp1.laser4_time = PROG431_4;
          strcpy(temp1.string1, PROG431_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 432:
          temp1.laser1_time = PROG432_1;
          temp1.laser2_time = PROG432_2;
          temp1.laser3_time = PROG432_3;
          temp1.laser4_time = PROG432_4;
          strcpy(temp1.string1, PROG432_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 433:
          temp1.laser1_time = PROG433_1;
          temp1.laser2_time = PROG433_2;
          temp1.laser3_time = PROG433_3;
          temp1.laser4_time = PROG433_4;
          strcpy(temp1.string1, PROG433_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 434:
          temp1.laser1_time = PROG434_1;
          temp1.laser2_time = PROG434_2;
          temp1.laser3_time = PROG434_3;
          temp1.laser4_time = PROG434_4;
          strcpy(temp1.string1, PROG434_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 435:
          temp1.laser1_time = PROG435_1;
          temp1.laser2_time = PROG435_2;
          temp1.laser3_time = PROG435_3;
          temp1.laser4_time = PROG435_4;
          strcpy(temp1.string1, PROG435_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 436:
          temp1.laser1_time = PROG436_1;
          temp1.laser2_time = PROG436_2;
          temp1.laser3_time = PROG436_3;
          temp1.laser4_time = PROG436_4;
          strcpy(temp1.string1, PROG436_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 437:
          temp1.laser1_time = PROG437_1;
          temp1.laser2_time = PROG437_2;
          temp1.laser3_time = PROG437_3;
          temp1.laser4_time = PROG437_4;
          strcpy(temp1.string1, PROG437_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 438:
          temp1.laser1_time = PROG438_1;
          temp1.laser2_time = PROG438_2;
          temp1.laser3_time = PROG438_3;
          temp1.laser4_time = PROG438_4;
          strcpy(temp1.string1, PROG438_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 439:
          temp1.laser1_time = PROG439_1;
          temp1.laser2_time = PROG439_2;
          temp1.laser3_time = PROG439_3;
          temp1.laser4_time = PROG439_4;
          strcpy(temp1.string1, PROG439_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 440:
          temp1.laser1_time = PROG440_1;
          temp1.laser2_time = PROG440_2;
          temp1.laser3_time = PROG440_3;
          temp1.laser4_time = PROG440_4;
          strcpy(temp1.string1, PROG440_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 441:
          temp1.laser1_time = PROG441_1;
          temp1.laser2_time = PROG441_2;
          temp1.laser3_time = PROG441_3;
          temp1.laser4_time = PROG441_4;
          strcpy(temp1.string1, PROG441_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 442:
          temp1.laser1_time = PROG442_1;
          temp1.laser2_time = PROG442_2;
          temp1.laser3_time = PROG442_3;
          temp1.laser4_time = PROG442_4;
          strcpy(temp1.string1, PROG442_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 443:
          temp1.laser1_time = PROG443_1;
          temp1.laser2_time = PROG443_2;
          temp1.laser3_time = PROG443_3;
          temp1.laser4_time = PROG443_4;
          strcpy(temp1.string1, PROG443_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 444:
          temp1.laser1_time = PROG444_1;
          temp1.laser2_time = PROG444_2;
          temp1.laser3_time = PROG444_3;
          temp1.laser4_time = PROG444_4;
          strcpy(temp1.string1, PROG444_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 445:
          temp1.laser1_time = PROG445_1;
          temp1.laser2_time = PROG445_2;
          temp1.laser3_time = PROG445_3;
          temp1.laser4_time = PROG445_4;
          strcpy(temp1.string1, PROG445_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 446:
          temp1.laser1_time = PROG446_1;
          temp1.laser2_time = PROG446_2;
          temp1.laser3_time = PROG446_3;
          temp1.laser4_time = PROG446_4;
          strcpy(temp1.string1, PROG446_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 447:
          temp1.laser1_time = PROG447_1;
          temp1.laser2_time = PROG447_2;
          temp1.laser3_time = PROG447_3;
          temp1.laser4_time = PROG447_4;
          strcpy(temp1.string1, PROG447_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 448:
          temp1.laser1_time = PROG448_1;
          temp1.laser2_time = PROG448_2;
          temp1.laser3_time = PROG448_3;
          temp1.laser4_time = PROG448_4;
          strcpy(temp1.string1, PROG448_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 449:
          temp1.laser1_time = PROG449_1;
          temp1.laser2_time = PROG449_2;
          temp1.laser3_time = PROG449_3;
          temp1.laser4_time = PROG449_4;
          strcpy(temp1.string1, PROG449_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 450:
          temp1.laser1_time = PROG450_1;
          temp1.laser2_time = PROG450_2;
          temp1.laser3_time = PROG450_3;
          temp1.laser4_time = PROG450_4;
          strcpy(temp1.string1, PROG450_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 451:
          temp1.laser1_time = PROG451_1;
          temp1.laser2_time = PROG451_2;
          temp1.laser3_time = PROG451_3;
          temp1.laser4_time = PROG451_4;
          strcpy(temp1.string1, PROG451_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 452:
          temp1.laser1_time = PROG452_1;
          temp1.laser2_time = PROG452_2;
          temp1.laser3_time = PROG452_3;
          temp1.laser4_time = PROG452_4;
          strcpy(temp1.string1, PROG452_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 453:
          temp1.laser1_time = PROG453_1;
          temp1.laser2_time = PROG453_2;
          temp1.laser3_time = PROG453_3;
          temp1.laser4_time = PROG453_4;
          strcpy(temp1.string1, PROG453_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 454:
          temp1.laser1_time = PROG454_1;
          temp1.laser2_time = PROG454_2;
          temp1.laser3_time = PROG454_3;
          temp1.laser4_time = PROG454_4;
          strcpy(temp1.string1, PROG454_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 455:
          temp1.laser1_time = PROG455_1;
          temp1.laser2_time = PROG455_2;
          temp1.laser3_time = PROG455_3;
          temp1.laser4_time = PROG455_4;
          strcpy(temp1.string1, PROG455_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 456:
          temp1.laser1_time = PROG456_1;
          temp1.laser2_time = PROG456_2;
          temp1.laser3_time = PROG456_3;
          temp1.laser4_time = PROG456_4;
          strcpy(temp1.string1, PROG456_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 457:
          temp1.laser1_time = PROG457_1;
          temp1.laser2_time = PROG457_2;
          temp1.laser3_time = PROG457_3;
          temp1.laser4_time = PROG457_4;
          strcpy(temp1.string1, PROG457_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 458:
          temp1.laser1_time = PROG458_1;
          temp1.laser2_time = PROG458_2;
          temp1.laser3_time = PROG458_3;
          temp1.laser4_time = PROG458_4;
          strcpy(temp1.string1, PROG458_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 459:
          temp1.laser1_time = PROG459_1;
          temp1.laser2_time = PROG459_2;
          temp1.laser3_time = PROG459_3;
          temp1.laser4_time = PROG459_4;
          strcpy(temp1.string1, PROG459_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 460:
          temp1.laser1_time = PROG460_1;
          temp1.laser2_time = PROG460_2;
          temp1.laser3_time = PROG460_3;
          temp1.laser4_time = PROG460_4;
          strcpy(temp1.string1, PROG460_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 461:
          temp1.laser1_time = PROG461_1;
          temp1.laser2_time = PROG461_2;
          temp1.laser3_time = PROG461_3;
          temp1.laser4_time = PROG461_4;
          strcpy(temp1.string1, PROG461_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 462:
          temp1.laser1_time = PROG462_1;
          temp1.laser2_time = PROG462_2;
          temp1.laser3_time = PROG462_3;
          temp1.laser4_time = PROG462_4;
          strcpy(temp1.string1, PROG462_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 463:
          temp1.laser1_time = PROG463_1;
          temp1.laser2_time = PROG463_2;
          temp1.laser3_time = PROG463_3;
          temp1.laser4_time = PROG463_4;
          strcpy(temp1.string1, PROG463_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 464:
          temp1.laser1_time = PROG464_1;
          temp1.laser2_time = PROG464_2;
          temp1.laser3_time = PROG464_3;
          temp1.laser4_time = PROG464_4;
          strcpy(temp1.string1, PROG464_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 465:
          temp1.laser1_time = PROG465_1;
          temp1.laser2_time = PROG465_2;
          temp1.laser3_time = PROG465_3;
          temp1.laser4_time = PROG465_4;
          strcpy(temp1.string1, PROG465_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 466:
          temp1.laser1_time = PROG466_1;
          temp1.laser2_time = PROG466_2;
          temp1.laser3_time = PROG466_3;
          temp1.laser4_time = PROG466_4;
          strcpy(temp1.string1, PROG466_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 467:
          temp1.laser1_time = PROG467_1;
          temp1.laser2_time = PROG467_2;
          temp1.laser3_time = PROG467_3;
          temp1.laser4_time = PROG467_4;
		  strcpy(temp1.string1, PROG467_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 468:
          temp1.laser1_time = PROG468_1;
          temp1.laser2_time = PROG468_2;
          temp1.laser3_time = PROG468_3;
          temp1.laser4_time = PROG468_4;
		  strcpy(temp1.string1, PROG468_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 469:
          temp1.laser1_time = PROG469_1;
          temp1.laser2_time = PROG469_2;
          temp1.laser3_time = PROG469_3;
          temp1.laser4_time = PROG469_4;
		  strcpy(temp1.string1, PROG469_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 470:
          temp1.laser1_time = PROG470_1;
          temp1.laser2_time = PROG470_2;
          temp1.laser3_time = PROG470_3;
          temp1.laser4_time = PROG470_4;
		  strcpy(temp1.string1, PROG470_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 471:
          temp1.laser1_time = PROG471_1;
          temp1.laser2_time = PROG471_2;
          temp1.laser3_time = PROG471_3;
          temp1.laser4_time = PROG471_4;
		  strcpy(temp1.string1, PROG471_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 472:
          temp1.laser1_time = PROG472_1;
          temp1.laser2_time = PROG472_2;
          temp1.laser3_time = PROG472_3;
          temp1.laser4_time = PROG472_4;
		  strcpy(temp1.string1, PROG472_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 473:
          temp1.laser1_time = PROG473_1;
          temp1.laser2_time = PROG473_2;
          temp1.laser3_time = PROG473_3;
          temp1.laser4_time = PROG473_4;
		  strcpy(temp1.string1, PROG473_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 474:
          temp1.laser1_time = PROG474_1;
          temp1.laser2_time = PROG474_2;
          temp1.laser3_time = PROG474_3;
          temp1.laser4_time = PROG474_4;
		  strcpy(temp1.string1, PROG474_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 475:
          temp1.laser1_time = PROG475_1;
          temp1.laser2_time = PROG475_2;
          temp1.laser3_time = PROG475_3;
          temp1.laser4_time = PROG475_4;
		  strcpy(temp1.string1, PROG475_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 476:
          temp1.laser1_time = PROG476_1;
          temp1.laser2_time = PROG476_2;
          temp1.laser3_time = PROG476_3;
          temp1.laser4_time = PROG476_4;
		  strcpy(temp1.string1, PROG476_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 477:
          temp1.laser1_time = PROG477_1;
          temp1.laser2_time = PROG477_2;
          temp1.laser3_time = PROG477_3;
          temp1.laser4_time = PROG477_4;
		  strcpy(temp1.string1, PROG477_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 478:
          temp1.laser1_time = PROG478_1;
          temp1.laser2_time = PROG478_2;
          temp1.laser3_time = PROG478_3;
          temp1.laser4_time = PROG478_4;
		  strcpy(temp1.string1, PROG478_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 479:
          temp1.laser1_time = PROG479_1;
          temp1.laser2_time = PROG479_2;
          temp1.laser3_time = PROG479_3;
          temp1.laser4_time = PROG479_4;
		  strcpy(temp1.string1, PROG479_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 480:
          temp1.laser1_time = PROG480_1;
          temp1.laser2_time = PROG480_2;
          temp1.laser3_time = PROG480_3;
          temp1.laser4_time = PROG480_4;
		  strcpy(temp1.string1, PROG480_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 481:
          temp1.laser1_time = PROG481_1;
          temp1.laser2_time = PROG481_2;
          temp1.laser3_time = PROG481_3;
          temp1.laser4_time = PROG481_4;
		  strcpy(temp1.string1, PROG481_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 482:
          temp1.laser1_time = PROG482_1;
          temp1.laser2_time = PROG482_2;
          temp1.laser3_time = PROG482_3;
          temp1.laser4_time = PROG482_4;
		  strcpy(temp1.string1, PROG482_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 483:
          temp1.laser1_time = PROG483_1;
          temp1.laser2_time = PROG483_2;
          temp1.laser3_time = PROG483_3;
          temp1.laser4_time = PROG483_4;
		  strcpy(temp1.string1, PROG483_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 484:
          temp1.laser1_time = PROG484_1;
          temp1.laser2_time = PROG484_2;
          temp1.laser3_time = PROG484_3;
          temp1.laser4_time = PROG484_4;
		  strcpy(temp1.string1, PROG484_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 485:
          temp1.laser1_time = PROG485_1;
          temp1.laser2_time = PROG485_2;
          temp1.laser3_time = PROG485_3;
          temp1.laser4_time = PROG485_4;
		  strcpy(temp1.string1, PROG485_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 486:
          temp1.laser1_time = PROG486_1;
          temp1.laser2_time = PROG486_2;
          temp1.laser3_time = PROG486_3;
          temp1.laser4_time = PROG486_4;
		  strcpy(temp1.string1, PROG486_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 487:
          temp1.laser1_time = PROG487_1;
          temp1.laser2_time = PROG487_2;
          temp1.laser3_time = PROG487_3;
          temp1.laser4_time = PROG487_4;
		  strcpy(temp1.string1, PROG487_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 488:
          temp1.laser1_time = PROG488_1;
          temp1.laser2_time = PROG488_2;
          temp1.laser3_time = PROG488_3;
          temp1.laser4_time = PROG488_4;
		  strcpy(temp1.string1, PROG488_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 489:
          temp1.laser1_time = PROG489_1;
          temp1.laser2_time = PROG489_2;
          temp1.laser3_time = PROG489_3;
          temp1.laser4_time = PROG489_4;
		  strcpy(temp1.string1, PROG489_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 490:
          temp1.laser1_time = PROG490_1;
          temp1.laser2_time = PROG490_2;
          temp1.laser3_time = PROG490_3;
          temp1.laser4_time = PROG490_4;
		  strcpy(temp1.string1, PROG490_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 491:
          temp1.laser1_time = PROG491_1;
          temp1.laser2_time = PROG491_2;
          temp1.laser3_time = PROG491_3;
          temp1.laser4_time = PROG491_4;
		  strcpy(temp1.string1, PROG491_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 492:
          temp1.laser1_time = PROG492_1;
          temp1.laser2_time = PROG492_2;
          temp1.laser3_time = PROG492_3;
          temp1.laser4_time = PROG492_4;
		  strcpy(temp1.string1, PROG492_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 493:
          temp1.laser1_time = PROG493_1;
          temp1.laser2_time = PROG493_2;
          temp1.laser3_time = PROG493_3;
          temp1.laser4_time = PROG493_4;
		  strcpy(temp1.string1, PROG493_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 494:
          temp1.laser1_time = PROG494_1;
          temp1.laser2_time = PROG494_2;
          temp1.laser3_time = PROG494_3;
          temp1.laser4_time = PROG494_4;
		  strcpy(temp1.string1, PROG494_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 495:
          temp1.laser1_time = PROG495_1;
          temp1.laser2_time = PROG495_2;
          temp1.laser3_time = PROG495_3;
          temp1.laser4_time = PROG495_4;
		  strcpy(temp1.string1, PROG495_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 496:
          temp1.laser1_time = PROG496_1;
          temp1.laser2_time = PROG496_2;
          temp1.laser3_time = PROG496_3;
          temp1.laser4_time = PROG496_4;
		  strcpy(temp1.string1, PROG496_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 497:
          temp1.laser1_time = PROG497_1;
          temp1.laser2_time = PROG497_2;
          temp1.laser3_time = PROG497_3;
          temp1.laser4_time = PROG497_4;
		  strcpy(temp1.string1, PROG497_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 498:
          temp1.laser1_time = PROG498_1;
          temp1.laser2_time = PROG498_2;
          temp1.laser3_time = PROG498_3;
          temp1.laser4_time = PROG498_4;
		  strcpy(temp1.string1, PROG498_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 499:
          temp1.laser1_time = PROG499_1;
          temp1.laser2_time = PROG499_2;
          temp1.laser3_time = PROG499_3;
          temp1.laser4_time = PROG499_4;
		  strcpy(temp1.string1, PROG499_STRING);
		  temp1.entry_flg = 1;
		  break;
//CASE500
		case 500:
          temp1.laser1_time = PROG500_1;
          temp1.laser2_time = PROG500_2;
          temp1.laser3_time = PROG500_3;
          temp1.laser4_time = PROG500_4;
          strcpy(temp1.string1, PROG500_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 501:
          temp1.laser1_time = PROG501_1;
          temp1.laser2_time = PROG501_2;
          temp1.laser3_time = PROG501_3;
          temp1.laser4_time = PROG501_4;
          strcpy(temp1.string1, PROG501_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 502:
          temp1.laser1_time = PROG502_1;
          temp1.laser2_time = PROG502_2;
          temp1.laser3_time = PROG502_3;
          temp1.laser4_time = PROG502_4;
          strcpy(temp1.string1, PROG502_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 503:
          temp1.laser1_time = PROG503_1;
          temp1.laser2_time = PROG503_2;
          temp1.laser3_time = PROG503_3;
          temp1.laser4_time = PROG503_4;
          strcpy(temp1.string1, PROG503_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 504:
          temp1.laser1_time = PROG504_1;
          temp1.laser2_time = PROG504_2;
          temp1.laser3_time = PROG504_3;
          temp1.laser4_time = PROG504_4;
          strcpy(temp1.string1, PROG504_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 505:
          temp1.laser1_time = PROG505_1;
          temp1.laser2_time = PROG505_2;
          temp1.laser3_time = PROG505_3;
          temp1.laser4_time = PROG505_4;
          strcpy(temp1.string1, PROG505_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 506:
          temp1.laser1_time = PROG506_1;
          temp1.laser2_time = PROG506_2;
          temp1.laser3_time = PROG506_3;
          temp1.laser4_time = PROG506_4;
          strcpy(temp1.string1, PROG506_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 507:
          temp1.laser1_time = PROG507_1;
          temp1.laser2_time = PROG507_2;
          temp1.laser3_time = PROG507_3;
          temp1.laser4_time = PROG507_4;
          strcpy(temp1.string1, PROG507_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 508:
          temp1.laser1_time = PROG508_1;
          temp1.laser2_time = PROG508_2;
          temp1.laser3_time = PROG508_3;
          temp1.laser4_time = PROG508_4;
          strcpy(temp1.string1, PROG508_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 509:
          temp1.laser1_time = PROG509_1;
          temp1.laser2_time = PROG509_2;
          temp1.laser3_time = PROG509_3;
          temp1.laser4_time = PROG509_4;
          strcpy(temp1.string1, PROG509_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 510:
          temp1.laser1_time = PROG510_1;
          temp1.laser2_time = PROG510_2;
          temp1.laser3_time = PROG510_3;
          temp1.laser4_time = PROG510_4;
          strcpy(temp1.string1, PROG510_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 511:
          temp1.laser1_time = PROG511_1;
          temp1.laser2_time = PROG511_2;
          temp1.laser3_time = PROG511_3;
          temp1.laser4_time = PROG511_4;
          strcpy(temp1.string1, PROG511_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 512:
          temp1.laser1_time = PROG512_1;
          temp1.laser2_time = PROG512_2;
          temp1.laser3_time = PROG512_3;
          temp1.laser4_time = PROG512_4;
          strcpy(temp1.string1, PROG512_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 513:
          temp1.laser1_time = PROG513_1;
          temp1.laser2_time = PROG513_2;
          temp1.laser3_time = PROG513_3;
          temp1.laser4_time = PROG513_4;
          strcpy(temp1.string1, PROG513_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 514:
          temp1.laser1_time = PROG514_1;
          temp1.laser2_time = PROG514_2;
          temp1.laser3_time = PROG514_3;
          temp1.laser4_time = PROG514_4;
          strcpy(temp1.string1, PROG514_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 515:
          temp1.laser1_time = PROG515_1;
          temp1.laser2_time = PROG515_2;
          temp1.laser3_time = PROG515_3;
          temp1.laser4_time = PROG515_4;
          strcpy(temp1.string1, PROG515_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 516:
          temp1.laser1_time = PROG516_1;
          temp1.laser2_time = PROG516_2;
          temp1.laser3_time = PROG516_3;
          temp1.laser4_time = PROG516_4;
          strcpy(temp1.string1, PROG516_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 517:
          temp1.laser1_time = PROG517_1;
          temp1.laser2_time = PROG517_2;
          temp1.laser3_time = PROG517_3;
          temp1.laser4_time = PROG517_4;
          strcpy(temp1.string1, PROG517_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 518:
          temp1.laser1_time = PROG518_1;
          temp1.laser2_time = PROG518_2;
          temp1.laser3_time = PROG518_3;
          temp1.laser4_time = PROG518_4;
          strcpy(temp1.string1, PROG518_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 519:
          temp1.laser1_time = PROG519_1;
          temp1.laser2_time = PROG519_2;
          temp1.laser3_time = PROG519_3;
          temp1.laser4_time = PROG519_4;
          strcpy(temp1.string1, PROG519_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 520:
          temp1.laser1_time = PROG520_1;
          temp1.laser2_time = PROG520_2;
          temp1.laser3_time = PROG520_3;
          temp1.laser4_time = PROG520_4;
          strcpy(temp1.string1, PROG520_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 521:
          temp1.laser1_time = PROG521_1;
          temp1.laser2_time = PROG521_2;
          temp1.laser3_time = PROG521_3;
          temp1.laser4_time = PROG521_4;
          strcpy(temp1.string1, PROG521_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 522:
          temp1.laser1_time = PROG522_1;
          temp1.laser2_time = PROG522_2;
          temp1.laser3_time = PROG522_3;
          temp1.laser4_time = PROG522_4;
          strcpy(temp1.string1, PROG522_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 523:
          temp1.laser1_time = PROG523_1;
          temp1.laser2_time = PROG523_2;
          temp1.laser3_time = PROG523_3;
          temp1.laser4_time = PROG523_4;
          strcpy(temp1.string1, PROG523_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 524:
          temp1.laser1_time = PROG524_1;
          temp1.laser2_time = PROG524_2;
          temp1.laser3_time = PROG524_3;
          temp1.laser4_time = PROG524_4;
          strcpy(temp1.string1, PROG524_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 525:
          temp1.laser1_time = PROG525_1;
          temp1.laser2_time = PROG525_2;
          temp1.laser3_time = PROG525_3;
          temp1.laser4_time = PROG525_4;
          strcpy(temp1.string1, PROG525_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 526:
          temp1.laser1_time = PROG526_1;
          temp1.laser2_time = PROG526_2;
          temp1.laser3_time = PROG526_3;
          temp1.laser4_time = PROG526_4;
          strcpy(temp1.string1, PROG526_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 527:
          temp1.laser1_time = PROG527_1;
          temp1.laser2_time = PROG527_2;
          temp1.laser3_time = PROG527_3;
          temp1.laser4_time = PROG527_4;
          strcpy(temp1.string1, PROG527_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 528:
          temp1.laser1_time = PROG528_1;
          temp1.laser2_time = PROG528_2;
          temp1.laser3_time = PROG528_3;
          temp1.laser4_time = PROG528_4;
          strcpy(temp1.string1, PROG528_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 529:
          temp1.laser1_time = PROG529_1;
          temp1.laser2_time = PROG529_2;
          temp1.laser3_time = PROG529_3;
          temp1.laser4_time = PROG529_4;
          strcpy(temp1.string1, PROG529_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 530:
          temp1.laser1_time = PROG530_1;
          temp1.laser2_time = PROG530_2;
          temp1.laser3_time = PROG530_3;
          temp1.laser4_time = PROG530_4;
          strcpy(temp1.string1, PROG530_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 531:
          temp1.laser1_time = PROG531_1;
          temp1.laser2_time = PROG531_2;
          temp1.laser3_time = PROG531_3;
          temp1.laser4_time = PROG531_4;
          strcpy(temp1.string1, PROG531_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 532:
          temp1.laser1_time = PROG532_1;
          temp1.laser2_time = PROG532_2;
          temp1.laser3_time = PROG532_3;
          temp1.laser4_time = PROG532_4;
          strcpy(temp1.string1, PROG532_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 533:
          temp1.laser1_time = PROG533_1;
          temp1.laser2_time = PROG533_2;
          temp1.laser3_time = PROG533_3;
          temp1.laser4_time = PROG533_4;
          strcpy(temp1.string1, PROG533_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 534:
          temp1.laser1_time = PROG534_1;
          temp1.laser2_time = PROG534_2;
          temp1.laser3_time = PROG534_3;
          temp1.laser4_time = PROG534_4;
          strcpy(temp1.string1, PROG534_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 535:
          temp1.laser1_time = PROG535_1;
          temp1.laser2_time = PROG535_2;
          temp1.laser3_time = PROG535_3;
          temp1.laser4_time = PROG535_4;
          strcpy(temp1.string1, PROG535_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 536:
          temp1.laser1_time = PROG536_1;
          temp1.laser2_time = PROG536_2;
          temp1.laser3_time = PROG536_3;
          temp1.laser4_time = PROG536_4;
          strcpy(temp1.string1, PROG536_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 537:
          temp1.laser1_time = PROG537_1;
          temp1.laser2_time = PROG537_2;
          temp1.laser3_time = PROG537_3;
          temp1.laser4_time = PROG537_4;
          strcpy(temp1.string1, PROG537_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 538:
          temp1.laser1_time = PROG538_1;
          temp1.laser2_time = PROG538_2;
          temp1.laser3_time = PROG538_3;
          temp1.laser4_time = PROG538_4;
          strcpy(temp1.string1, PROG538_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 539:
          temp1.laser1_time = PROG539_1;
          temp1.laser2_time = PROG539_2;
          temp1.laser3_time = PROG539_3;
          temp1.laser4_time = PROG539_4;
          strcpy(temp1.string1, PROG539_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 540:
          temp1.laser1_time = PROG540_1;
          temp1.laser2_time = PROG540_2;
          temp1.laser3_time = PROG540_3;
          temp1.laser4_time = PROG540_4;
          strcpy(temp1.string1, PROG540_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 541:
          temp1.laser1_time = PROG541_1;
          temp1.laser2_time = PROG541_2;
          temp1.laser3_time = PROG541_3;
          temp1.laser4_time = PROG541_4;
          strcpy(temp1.string1, PROG541_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 542:
          temp1.laser1_time = PROG542_1;
          temp1.laser2_time = PROG542_2;
          temp1.laser3_time = PROG542_3;
          temp1.laser4_time = PROG542_4;
          strcpy(temp1.string1, PROG542_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 543:
          temp1.laser1_time = PROG543_1;
          temp1.laser2_time = PROG543_2;
          temp1.laser3_time = PROG543_3;
          temp1.laser4_time = PROG543_4;
          strcpy(temp1.string1, PROG543_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 544:
          temp1.laser1_time = PROG544_1;
          temp1.laser2_time = PROG544_2;
          temp1.laser3_time = PROG544_3;
          temp1.laser4_time = PROG544_4;
          strcpy(temp1.string1, PROG544_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 545:
          temp1.laser1_time = PROG545_1;
          temp1.laser2_time = PROG545_2;
          temp1.laser3_time = PROG545_3;
          temp1.laser4_time = PROG545_4;
          strcpy(temp1.string1, PROG545_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 546:
          temp1.laser1_time = PROG546_1;
          temp1.laser2_time = PROG546_2;
          temp1.laser3_time = PROG546_3;
          temp1.laser4_time = PROG546_4;
          strcpy(temp1.string1, PROG546_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 547:
          temp1.laser1_time = PROG547_1;
          temp1.laser2_time = PROG547_2;
          temp1.laser3_time = PROG547_3;
          temp1.laser4_time = PROG547_4;
          strcpy(temp1.string1, PROG547_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 548:
          temp1.laser1_time = PROG548_1;
          temp1.laser2_time = PROG548_2;
          temp1.laser3_time = PROG548_3;
          temp1.laser4_time = PROG548_4;
          strcpy(temp1.string1, PROG548_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 549:
          temp1.laser1_time = PROG549_1;
          temp1.laser2_time = PROG549_2;
          temp1.laser3_time = PROG549_3;
          temp1.laser4_time = PROG549_4;
          strcpy(temp1.string1, PROG549_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 550:
          temp1.laser1_time = PROG550_1;
          temp1.laser2_time = PROG550_2;
          temp1.laser3_time = PROG550_3;
          temp1.laser4_time = PROG550_4;
          strcpy(temp1.string1, PROG550_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 551:
          temp1.laser1_time = PROG551_1;
          temp1.laser2_time = PROG551_2;
          temp1.laser3_time = PROG551_3;
          temp1.laser4_time = PROG551_4;
          strcpy(temp1.string1, PROG551_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 552:
          temp1.laser1_time = PROG552_1;
          temp1.laser2_time = PROG552_2;
          temp1.laser3_time = PROG552_3;
          temp1.laser4_time = PROG552_4;
          strcpy(temp1.string1, PROG552_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 553:
          temp1.laser1_time = PROG553_1;
          temp1.laser2_time = PROG553_2;
          temp1.laser3_time = PROG553_3;
          temp1.laser4_time = PROG553_4;
          strcpy(temp1.string1, PROG553_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 554:
          temp1.laser1_time = PROG554_1;
          temp1.laser2_time = PROG554_2;
          temp1.laser3_time = PROG554_3;
          temp1.laser4_time = PROG554_4;
          strcpy(temp1.string1, PROG554_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 555:
          temp1.laser1_time = PROG555_1;
          temp1.laser2_time = PROG555_2;
          temp1.laser3_time = PROG555_3;
          temp1.laser4_time = PROG555_4;
          strcpy(temp1.string1, PROG555_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 556:
          temp1.laser1_time = PROG556_1;
          temp1.laser2_time = PROG556_2;
          temp1.laser3_time = PROG556_3;
          temp1.laser4_time = PROG556_4;
          strcpy(temp1.string1, PROG556_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 557:
          temp1.laser1_time = PROG557_1;
          temp1.laser2_time = PROG557_2;
          temp1.laser3_time = PROG557_3;
          temp1.laser4_time = PROG557_4;
          strcpy(temp1.string1, PROG557_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 558:
          temp1.laser1_time = PROG558_1;
          temp1.laser2_time = PROG558_2;
          temp1.laser3_time = PROG558_3;
          temp1.laser4_time = PROG558_4;
          strcpy(temp1.string1, PROG558_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 559:
          temp1.laser1_time = PROG559_1;
          temp1.laser2_time = PROG559_2;
          temp1.laser3_time = PROG559_3;
          temp1.laser4_time = PROG559_4;
          strcpy(temp1.string1, PROG559_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 560:
          temp1.laser1_time = PROG560_1;
          temp1.laser2_time = PROG560_2;
          temp1.laser3_time = PROG560_3;
          temp1.laser4_time = PROG560_4;
          strcpy(temp1.string1, PROG560_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 561:
          temp1.laser1_time = PROG561_1;
          temp1.laser2_time = PROG561_2;
          temp1.laser3_time = PROG561_3;
          temp1.laser4_time = PROG561_4;
          strcpy(temp1.string1, PROG561_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 562:
          temp1.laser1_time = PROG562_1;
          temp1.laser2_time = PROG562_2;
          temp1.laser3_time = PROG562_3;
          temp1.laser4_time = PROG562_4;
          strcpy(temp1.string1, PROG562_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 563:
          temp1.laser1_time = PROG563_1;
          temp1.laser2_time = PROG563_2;
          temp1.laser3_time = PROG563_3;
          temp1.laser4_time = PROG563_4;
          strcpy(temp1.string1, PROG563_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 564:
          temp1.laser1_time = PROG564_1;
          temp1.laser2_time = PROG564_2;
          temp1.laser3_time = PROG564_3;
          temp1.laser4_time = PROG564_4;
          strcpy(temp1.string1, PROG564_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 565:
          temp1.laser1_time = PROG565_1;
          temp1.laser2_time = PROG565_2;
          temp1.laser3_time = PROG565_3;
          temp1.laser4_time = PROG565_4;
          strcpy(temp1.string1, PROG565_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 566:
          temp1.laser1_time = PROG566_1;
          temp1.laser2_time = PROG566_2;
          temp1.laser3_time = PROG566_3;
          temp1.laser4_time = PROG566_4;
          strcpy(temp1.string1, PROG566_STRING);
	      temp1.entry_flg = 1;
		  break;
		case 567:
          temp1.laser1_time = PROG567_1;
          temp1.laser2_time = PROG567_2;
          temp1.laser3_time = PROG567_3;
          temp1.laser4_time = PROG567_4;
		  strcpy(temp1.string1, PROG567_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 568:
          temp1.laser1_time = PROG568_1;
          temp1.laser2_time = PROG568_2;
          temp1.laser3_time = PROG568_3;
          temp1.laser4_time = PROG568_4;
		  strcpy(temp1.string1, PROG568_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 569:
          temp1.laser1_time = PROG569_1;
          temp1.laser2_time = PROG569_2;
          temp1.laser3_time = PROG569_3;
          temp1.laser4_time = PROG569_4;
		  strcpy(temp1.string1, PROG569_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 570:
          temp1.laser1_time = PROG570_1;
          temp1.laser2_time = PROG570_2;
          temp1.laser3_time = PROG570_3;
          temp1.laser4_time = PROG570_4;
		  strcpy(temp1.string1, PROG570_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 571:
          temp1.laser1_time = PROG571_1;
          temp1.laser2_time = PROG571_2;
          temp1.laser3_time = PROG571_3;
          temp1.laser4_time = PROG571_4;
		  strcpy(temp1.string1, PROG571_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 572:
          temp1.laser1_time = PROG572_1;
          temp1.laser2_time = PROG572_2;
          temp1.laser3_time = PROG572_3;
          temp1.laser4_time = PROG572_4;
		  strcpy(temp1.string1, PROG572_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 573:
          temp1.laser1_time = PROG573_1;
          temp1.laser2_time = PROG573_2;
          temp1.laser3_time = PROG573_3;
          temp1.laser4_time = PROG573_4;
		  strcpy(temp1.string1, PROG573_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 574:
          temp1.laser1_time = PROG574_1;
          temp1.laser2_time = PROG574_2;
          temp1.laser3_time = PROG574_3;
          temp1.laser4_time = PROG574_4;
		  strcpy(temp1.string1, PROG574_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 575:
          temp1.laser1_time = PROG575_1;
          temp1.laser2_time = PROG575_2;
          temp1.laser3_time = PROG575_3;
          temp1.laser4_time = PROG575_4;
		  strcpy(temp1.string1, PROG575_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 576:
          temp1.laser1_time = PROG576_1;
          temp1.laser2_time = PROG576_2;
          temp1.laser3_time = PROG576_3;
          temp1.laser4_time = PROG576_4;
		  strcpy(temp1.string1, PROG576_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 577:
          temp1.laser1_time = PROG577_1;
          temp1.laser2_time = PROG577_2;
          temp1.laser3_time = PROG577_3;
          temp1.laser4_time = PROG577_4;
		  strcpy(temp1.string1, PROG577_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 578:
          temp1.laser1_time = PROG578_1;
          temp1.laser2_time = PROG578_2;
          temp1.laser3_time = PROG578_3;
          temp1.laser4_time = PROG578_4;
		  strcpy(temp1.string1, PROG578_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 579:
          temp1.laser1_time = PROG579_1;
          temp1.laser2_time = PROG579_2;
          temp1.laser3_time = PROG579_3;
          temp1.laser4_time = PROG579_4;
		  strcpy(temp1.string1, PROG579_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 580:
          temp1.laser1_time = PROG580_1;
          temp1.laser2_time = PROG580_2;
          temp1.laser3_time = PROG580_3;
          temp1.laser4_time = PROG580_4;
		  strcpy(temp1.string1, PROG580_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 581:
          temp1.laser1_time = PROG581_1;
          temp1.laser2_time = PROG581_2;
          temp1.laser3_time = PROG581_3;
          temp1.laser4_time = PROG581_4;
		  strcpy(temp1.string1, PROG581_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 582:
          temp1.laser1_time = PROG582_1;
          temp1.laser2_time = PROG582_2;
          temp1.laser3_time = PROG582_3;
          temp1.laser4_time = PROG582_4;
		  strcpy(temp1.string1, PROG582_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 583:
          temp1.laser1_time = PROG583_1;
          temp1.laser2_time = PROG583_2;
          temp1.laser3_time = PROG583_3;
          temp1.laser4_time = PROG583_4;
		  strcpy(temp1.string1, PROG583_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 584:
          temp1.laser1_time = PROG584_1;
          temp1.laser2_time = PROG584_2;
          temp1.laser3_time = PROG584_3;
          temp1.laser4_time = PROG584_4;
		  strcpy(temp1.string1, PROG584_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 585:
          temp1.laser1_time = PROG585_1;
          temp1.laser2_time = PROG585_2;
          temp1.laser3_time = PROG585_3;
          temp1.laser4_time = PROG585_4;
		  strcpy(temp1.string1, PROG585_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 586:
          temp1.laser1_time = PROG586_1;
          temp1.laser2_time = PROG586_2;
          temp1.laser3_time = PROG586_3;
          temp1.laser4_time = PROG586_4;
		  strcpy(temp1.string1, PROG586_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 587:
          temp1.laser1_time = PROG587_1;
          temp1.laser2_time = PROG587_2;
          temp1.laser3_time = PROG587_3;
          temp1.laser4_time = PROG587_4;
		  strcpy(temp1.string1, PROG587_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 588:
          temp1.laser1_time = PROG588_1;
          temp1.laser2_time = PROG588_2;
          temp1.laser3_time = PROG588_3;
          temp1.laser4_time = PROG588_4;
		  strcpy(temp1.string1, PROG588_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 589:
          temp1.laser1_time = PROG589_1;
          temp1.laser2_time = PROG589_2;
          temp1.laser3_time = PROG589_3;
          temp1.laser4_time = PROG589_4;
		  strcpy(temp1.string1, PROG589_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 590:
          temp1.laser1_time = PROG590_1;
          temp1.laser2_time = PROG590_2;
          temp1.laser3_time = PROG590_3;
          temp1.laser4_time = PROG590_4;
		  strcpy(temp1.string1, PROG590_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 591:
          temp1.laser1_time = PROG591_1;
          temp1.laser2_time = PROG591_2;
          temp1.laser3_time = PROG591_3;
          temp1.laser4_time = PROG591_4;
		  strcpy(temp1.string1, PROG591_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 592:
          temp1.laser1_time = PROG592_1;
          temp1.laser2_time = PROG592_2;
          temp1.laser3_time = PROG592_3;
          temp1.laser4_time = PROG592_4;
		  strcpy(temp1.string1, PROG592_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 593:
          temp1.laser1_time = PROG593_1;
          temp1.laser2_time = PROG593_2;
          temp1.laser3_time = PROG593_3;
          temp1.laser4_time = PROG593_4;
		  strcpy(temp1.string1, PROG593_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 594:
          temp1.laser1_time = PROG594_1;
          temp1.laser2_time = PROG594_2;
          temp1.laser3_time = PROG594_3;
          temp1.laser4_time = PROG594_4;
		  strcpy(temp1.string1, PROG594_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 595:
          temp1.laser1_time = PROG595_1;
          temp1.laser2_time = PROG595_2;
          temp1.laser3_time = PROG595_3;
          temp1.laser4_time = PROG595_4;
		  strcpy(temp1.string1, PROG595_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 596:
          temp1.laser1_time = PROG596_1;
          temp1.laser2_time = PROG596_2;
          temp1.laser3_time = PROG596_3;
          temp1.laser4_time = PROG596_4;
		  strcpy(temp1.string1, PROG596_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 597:
          temp1.laser1_time = PROG597_1;
          temp1.laser2_time = PROG597_2;
          temp1.laser3_time = PROG597_3;
          temp1.laser4_time = PROG597_4;
		  strcpy(temp1.string1, PROG597_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 598:
          temp1.laser1_time = PROG598_1;
          temp1.laser2_time = PROG598_2;
          temp1.laser3_time = PROG598_3;
          temp1.laser4_time = PROG598_4;
		  strcpy(temp1.string1, PROG598_STRING);
		  temp1.entry_flg = 1;
		  break;
		case 599:
          temp1.laser1_time = PROG599_1;
          temp1.laser2_time = PROG599_2;
          temp1.laser3_time = PROG599_3;
          temp1.laser4_time = PROG599_4;
		  strcpy(temp1.string1, PROG599_STRING);
		  temp1.entry_flg = 1;
		  break;
		
		default:
		  temp1.laser1_time = 0;
		  temp1.laser2_time = 0;
		  temp1.laser3_time = 0;
		  temp1.laser4_time = 0;
		  strcpy(temp1.string1, RESERVE_STRING);
		  temp1.entry_flg = 1;
		  break;
	  }
	}
	else {
      temp1.laser1_time = 0;
      temp1.laser2_time = 0;
      temp1.laser3_time = 0;
      temp1.laser4_time = 0;
      strcpy(temp1.string1, RESERVE_STRING);
	  temp1.entry_flg = 1;
	} //Endif Test entry_num
  } //Endif entry_num
  else {
#ifdef CLW
	    if ((entry_num > CUSTOM4_END) && (entry_num <= USER_END)) {
	      if (entry_num <= USER_REND) {
	        entry_num -= (CUSTOM4_END+1);   			// Adjust entry_num for Custom Numbers skipped
#else
    if ((entry_num > CUSTOM_END) && (entry_num <= USER_END)) {
      if (entry_num <= USER_REND) {
        entry_num -= (CUSTOM_END+1);   			// Adjust entry_num for Custom Numbers skipped
#endif
        //address = (unsigned long)&laser0_data;		   	// Get the address of the start of Sweep Variables.
	    address1 = (struct laseru_entry *)&laser0_data;
	    // Test Code to display vars.
	    //sprintf(tempstr,"address1: %lx\n", address1);
	    //printf2(tempstr);
	    address = (unsigned long)address1;
	    //sprintf(tempstr,"address: %lx\n", address);
	    //printf2(tempstr);
	    address = address + (entry_num * sizeof(laser0_data));   // Adjust address for correct entry.
        //sprintf(tempstr,"address: %lx\n", address);
        //printf2(tempstr);
        EEPROM_READ((uchar *)address, (uchar *)&temp2, sizeof(temp2));	  	// Retrieve the data from EEPROM.
		//Create laser_entry from laseru_entry.
        temp1.laser1_time = temp2.laser1_time;
        temp1.laser2_time = temp2.laser2_time;
        temp1.laser3_time = temp2.laser3_time;
        temp1.laser4_time = temp2.laser4_time;
	    strcpy(tempstr, "   ");				    // Create string with 3 spaces.
	    strcat(tempstr, temp2.string1);		    // Concat String to tempstr.
	    strcat(tempstr, "    ");					// Add Blanks to end of string.
        strcpy(temp1.string1, tempstr);			// add string to temp2 structure.
		temp1.entry_flg = temp2.entry_flg;
	  }
	  else {			  				  	    // Above USER_END...Reserved
        temp1.laser1_time = 0;
        temp1.laser2_time = 0;
        temp1.laser3_time = 0;
        temp1.laser4_time = 0;
        strcpy(temp1.string1, RESERVE_STRING);
	    temp1.entry_flg = 1;
	  }
	}
	else {				  	   				   	// Above USER_END...Reserved
      temp1.laser1_time = 0;
      temp1.laser2_time = 0;
      temp1.laser3_time = 0;
      temp1.laser4_time = 0;
      strcpy(temp1.string1, RESERVE_STRING);
	  temp1.entry_flg = 1;
	}
  } //EndElse entry_num
  printf2("*****************************************\n");
  sprintf(tempstr,"read_entry results. Entry:%d\n", entry_num);
  printf2(tempstr);
  sprintf(tempstr,"laser1_time: %f\n", temp1.laser1_time);
  printf2(tempstr);
  sprintf(tempstr,"laser2_time: %f\n", temp1.laser2_time);
  printf2(tempstr);
  sprintf(tempstr,"laser3_time: %f\n", temp1.laser3_time);
  printf2(tempstr);
  sprintf(tempstr,"laser4_time: %f\n", temp1.laser4_time);
  printf2(tempstr);
  sprintf(tempstr,"string1: %s\n", temp1.string1);
  printf2(tempstr);
  sprintf(tempstr,"entry_flg: %d\n", temp1.entry_flg);
  printf2(tempstr);
  printf2("*****************************************\n");
  return(&temp1);	   					// Return the address of the structure.
}

void Protocolmonitor( char* parm1)
{
	char tempstr[200];
	int x, y;
	struct laser_entry *data1;

	if( strcmp(parm1, "CSV") == 0)
	{
		// First Print Header to Monitor Screen.
		printf2("\n\nprog_num,string,laser1,lasere2,laser3,laser4\n");

		// Clear buffer
		for (y=0; y<200; y++)
			tempstr[y] = 0x00;

		// Turn off Printf2 for Reading entries.
		StrmOn = 0;

		// Now loop through all entries.
		for (x=1; x<CUSTOM4_END; x++)
//		for (x=1; x<10; x++)
		{
			// Read Entry.
			data1 = read_entry((unsigned int) x);
			// Turn on Printf2 to print entry.
			StrmOn = 1;
			sprintf(tempstr, "%d,%s,%f,%f,%f,%f\n", x,
					data1->string1,
					data1->laser1_time,
					data1->laser2_time,
					data1->laser3_time,
					data1->laser4_time);
			printf2(tempstr);
			// Turn off Printf2 for next entry.
			StrmOn = 0;
			// Clear buffer
			for (y=0; y<200; y++)
				tempstr[y] = 0x00;
		}
		// Turn on Printf2.
		StrmOn = 1;
		printf2("\n\n");
	}
	else
	{
		// Read Entry and print results.
		read_entry((unsigned int) atoi(parm1));
		printf2("\n\n");
	}
}

