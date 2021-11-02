/*
 * macros.c
 *
 *  Created on: Feb 4, 2015
 *      Author: rpruitt76
 */
//****************************************************************************
//*
//*	macros
//*
//* There is one routine here that is used to load the correct Protocol for User Memory.
//*	struct super_macro *read_macro(unsigned int entry_num):  read the indicated entry from the EEPROM or Memory.
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
//* Prototypes
//*
//*****************************************************************************
//Macro00
extern const struct super_macro Macro00;
extern const struct super_macro Macro01;
extern const struct super_macro Macro02;
extern const struct super_macro Macro03;
extern const struct super_macro Macro04;
extern const struct super_macro Macro05;
extern const struct super_macro Macro06;
extern const struct super_macro Macro07;
extern const struct super_macro Macro08;
extern const struct super_macro Macro09;
//Macro10
extern const struct super_macro Macro10;
extern const struct super_macro Macro11;
extern const struct super_macro Macro12;
extern const struct super_macro Macro13;
extern const struct super_macro Macro14;
extern const struct super_macro Macro15;
extern const struct super_macro Macro16;
extern const struct super_macro Macro17;
extern const struct super_macro Macro18;
extern const struct super_macro Macro19;
//Macro20
extern const struct super_macro Macro20;
extern const struct super_macro Macro21;
extern const struct super_macro Macro22;
extern const struct super_macro Macro23;
extern const struct super_macro Macro24;
extern const struct super_macro Macro25;
extern const struct super_macro Macro26;
extern const struct super_macro Macro27;
extern const struct super_macro Macro28;
extern const struct super_macro Macro29;
//Macro30
extern const struct super_macro Macro30;
extern const struct super_macro Macro31;
extern const struct super_macro Macro32;
extern const struct super_macro Macro33;
extern const struct super_macro Macro34;
extern const struct super_macro Macro35;
extern const struct super_macro Macro36;
extern const struct super_macro Macro37;
extern const struct super_macro Macro38;
extern const struct super_macro Macro39;
//Macro40
extern const struct super_macro Macro40;
extern const struct super_macro Macro41;
extern const struct super_macro Macro42;
extern const struct super_macro Macro43;
extern const struct super_macro Macro44;
extern const struct super_macro Macro45;
extern const struct super_macro Macro46;
extern const struct super_macro Macro47;
extern const struct super_macro Macro48;
extern const struct super_macro Macro49;
//Macro50
extern const struct super_macro Macro50;
extern const struct super_macro Macro51;
extern const struct super_macro Macro52;
extern const struct super_macro Macro53;
extern const struct super_macro Macro54;
extern const struct super_macro Macro55;
extern const struct super_macro Macro56;
extern const struct super_macro Macro57;
extern const struct super_macro Macro58;
extern const struct super_macro Macro59;
//Macro60
extern const struct super_macro Macro60;
extern const struct super_macro Macro61;
extern const struct super_macro Macro62;
extern const struct super_macro Macro63;
extern const struct super_macro Macro64;
extern const struct super_macro Macro65;
extern const struct super_macro Macro66;
extern const struct super_macro Macro67;
extern const struct super_macro Macro68;
extern const struct super_macro Macro69;
//Macro70
extern const struct super_macro Macro70;
extern const struct super_macro Macro71;
extern const struct super_macro Macro72;
extern const struct super_macro Macro73;
extern const struct super_macro Macro74;
extern const struct super_macro Macro75;
extern const struct super_macro Macro76;
extern const struct super_macro Macro77;
extern const struct super_macro Macro78;
extern const struct super_macro Macro79;
//Macro80
extern const struct super_macro Macro80;
extern const struct super_macro Macro81;
extern const struct super_macro Macro82;
extern const struct super_macro Macro83;
extern const struct super_macro Macro84;
extern const struct super_macro Macro85;
extern const struct super_macro Macro86;
extern const struct super_macro Macro87;
extern const struct super_macro Macro88;
extern const struct super_macro Macro89;
//Macro90
extern const struct super_macro Macro90;
extern const struct super_macro Macro91;
extern const struct super_macro Macro92;
extern const struct super_macro Macro93;
extern const struct super_macro Macro94;
extern const struct super_macro Macro95;
extern const struct super_macro Macro96;
extern const struct super_macro Macro97;
extern const struct super_macro Macro98;
extern const struct super_macro Macro99;
/*
//Macro100
extern const struct super_macro Macro100;
extern const struct super_macro Macro101;
extern const struct super_macro Macro102;
extern const struct super_macro Macro103;
extern const struct super_macro Macro104;
extern const struct super_macro Macro105;
extern const struct super_macro Macro106;
extern const struct super_macro Macro107;
extern const struct super_macro Macro108;
extern const struct super_macro Macro109;
//Macro110
extern const struct super_macro Macro110;
extern const struct super_macro Macro111;
extern const struct super_macro Macro112;
extern const struct super_macro Macro113;
extern const struct super_macro Macro114;
extern const struct super_macro Macro115;
extern const struct super_macro Macro116;
extern const struct super_macro Macro117;
extern const struct super_macro Macro118;
extern const struct super_macro Macro119;
//Macro120
extern const struct super_macro Macro120;
extern const struct super_macro Macro121;
extern const struct super_macro Macro122;
extern const struct super_macro Macro123;
extern const struct super_macro Macro124;
extern const struct super_macro Macro125;
extern const struct super_macro Macro126;
extern const struct super_macro Macro127;
extern const struct super_macro Macro128;
extern const struct super_macro Macro129;
//Macro130
extern const struct super_macro Macro130;
extern const struct super_macro Macro131;
extern const struct super_macro Macro132;
extern const struct super_macro Macro133;
extern const struct super_macro Macro134;
extern const struct super_macro Macro135;
extern const struct super_macro Macro136;
extern const struct super_macro Macro137;
extern const struct super_macro Macro138;
extern const struct super_macro Macro139;
//Macro140
extern const struct super_macro Macro140;
extern const struct super_macro Macro141;
extern const struct super_macro Macro142;
extern const struct super_macro Macro143;
extern const struct super_macro Macro144;
extern const struct super_macro Macro145;
extern const struct super_macro Macro146;
extern const struct super_macro Macro147;
extern const struct super_macro Macro148;
extern const struct super_macro Macro149;
//Macro150
extern const struct super_macro Macro150;
extern const struct super_macro Macro151;
extern const struct super_macro Macro152;
extern const struct super_macro Macro153;
extern const struct super_macro Macro154;
extern const struct super_macro Macro155;
extern const struct super_macro Macro156;
extern const struct super_macro Macro157;
extern const struct super_macro Macro158;
extern const struct super_macro Macro159;
//Macro160
extern const struct super_macro Macro160;
extern const struct super_macro Macro161;
extern const struct super_macro Macro162;
extern const struct super_macro Macro163;
extern const struct super_macro Macro164;
extern const struct super_macro Macro165;
extern const struct super_macro Macro166;
extern const struct super_macro Macro167;
extern const struct super_macro Macro168;
extern const struct super_macro Macro169;
//Macro170
extern const struct super_macro Macro170;
extern const struct super_macro Macro171;
extern const struct super_macro Macro172;
extern const struct super_macro Macro173;
extern const struct super_macro Macro174;
extern const struct super_macro Macro175;
extern const struct super_macro Macro176;
extern const struct super_macro Macro177;
extern const struct super_macro Macro178;
extern const struct super_macro Macro179;
//Macro180
extern const struct super_macro Macro180;
extern const struct super_macro Macro181;
extern const struct super_macro Macro182;
extern const struct super_macro Macro183;
extern const struct super_macro Macro184;
extern const struct super_macro Macro185;
extern const struct super_macro Macro186;
extern const struct super_macro Macro187;
extern const struct super_macro Macro188;
extern const struct super_macro Macro189;
//Macro190
extern const struct super_macro Macro190;
extern const struct super_macro Macro191;
extern const struct super_macro Macro192;
extern const struct super_macro Macro193;
extern const struct super_macro Macro194;
extern const struct super_macro Macro195;
extern const struct super_macro Macro196;
extern const struct super_macro Macro197;
extern const struct super_macro Macro198;
extern const struct super_macro Macro199; */


const struct super_macro Blank_Entry = {0,
		         0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 RESERVE_STRING};

//*****************************************************************************
//*
//* routine: read_macro
//* Date: 	 June 12, 2006
//* Updated: February 5, 2015
//* Author:  Ralph Pruitt
//* This routine is used to read the indicated entry from the EEPROM of the AVR.
//*
//* INPUT:
//*   uint entry_num - Entry Number to read.
//*
//* OUTPUT:
//*   Pointer to Sweep Structure: Returns a pointer to the Sweep Structure
//*                               retrieved from EEPROM.
//*****************************************************************************
struct super_macro *read_macro(unsigned int entry_num)
{
  char tempstr[80];

  struct user_macro *address1;
  unsigned long address;
  unsigned char *clearptr;
  int x;
  static struct super_macro temp2;			// Declare Static Structure to be written.
  struct super_macro *temp3;
  struct user_macro temp1;					// Declare struct to read a user_macro.

  // Clear temp2 for new data
  clearptr = (unsigned char *)&temp2;
  for (x=0; x<sizeof(temp2); x++)
	  *clearptr++ = 0;

  // Code logic for Custom Macros Calculation and Loading Follows
  if ((entry_num >= CSTMSUPR_STRT) && (entry_num <= CSTMSUPR_REND)) {
    entry_num -= CSTMSUPR_STRT;	   	    	// Adjust entry to start of table.

    switch (entry_num) {
	  case 0:
	    temp3 = (struct super_macro *)&Macro00;
		break;
	  case 1:
	    temp3 = (struct super_macro *)&Macro01;
		break;
	  case 2:
	    temp3 = (struct super_macro *)&Macro02;
		break;
	  case 3:
	    temp3 = (struct super_macro *)&Macro03;
		break;
	  case 4:
	    temp3 = (struct super_macro *)&Macro04;
		break;
	  case 5:
	    temp3 = (struct super_macro *)&Macro05;
		break;
	  case 6:
	    temp3 = (struct super_macro *)&Macro06;
		break;
	  case 7:
	    temp3 = (struct super_macro *)&Macro07;
		break;
	  case 8:
	    temp3 = (struct super_macro *)&Macro08;
		break;
	  case 9:
	    temp3 = (struct super_macro *)&Macro09;
		break;
	  case 10:
	    temp3 = (struct super_macro *)&Macro10;
		break;
	  case 11:
	    temp3 = (struct super_macro *)&Macro11;
		break;
	  case 12:
	    temp3 = (struct super_macro *)&Macro12;
		break;
	  case 13:
	    temp3 = (struct super_macro *)&Macro13;
		break;
	  case 14:
	    temp3 = (struct super_macro *)&Macro14;
		break;
	  case 15:
	    temp3 = (struct super_macro *)&Macro15;
		break;
	  case 16:
	    temp3 = (struct super_macro *)&Macro16;
		break;
	  case 17:
	    temp3 = (struct super_macro *)&Macro17;
		break;
	  case 18:
	    temp3 = (struct super_macro *)&Macro18;
		break;
	  case 19:
	    temp3 = (struct super_macro *)&Macro19;
		break;
	  case 20:
	    temp3 = (struct super_macro *)&Macro20;
		break;
	  case 21:
	    temp3 = (struct super_macro *)&Macro21;
		break;
	  case 22:
	    temp3 = (struct super_macro *)&Macro22;
		break;
	  case 23:
	    temp3 = (struct super_macro *)&Macro23;
		break;
	  case 24:
	    temp3 = (struct super_macro *)&Macro24;
		break;
	  case 25:
	    temp3 = (struct super_macro *)&Macro25;
		break;
	  case 26:
	    temp3 = (struct super_macro *)&Macro26;
		break;
	  case 27:
	    temp3 = (struct super_macro *)&Macro27;
		break;
	  case 28:
	    temp3 = (struct super_macro *)&Macro28;
		break;
	  case 29:
	    temp3 = (struct super_macro *)&Macro29;
		break;
	  case 30:
	    temp3 = (struct super_macro *)&Macro30;
		break;
	  case 31:
	    temp3 = (struct super_macro *)&Macro31;
		break;
	  case 32:
	    temp3 = (struct super_macro *)&Macro32;
		break;
	  case 33:
	    temp3 = (struct super_macro *)&Macro33;
		break;
	  case 34:
	    temp3 = (struct super_macro *)&Macro34;
		break;
	  case 35:
	    temp3 = (struct super_macro *)&Macro35;
		break;
	  case 36:
	    temp3 = (struct super_macro *)&Macro36;
		break;
	  case 37:
	    temp3 = (struct super_macro *)&Macro37;
		break;
	  case 38:
	    temp3 = (struct super_macro *)&Macro38;
		break;
	  case 39:
	    temp3 = (struct super_macro *)&Macro39;
		break;
	  case 40:
	    temp3 = (struct super_macro *)&Macro40;
		break;
	  case 41:
	    temp3 = (struct super_macro *)&Macro41;
		break;
	  case 42:
	    temp3 = (struct super_macro *)&Macro42;
		break;
	  case 43:
	    temp3 = (struct super_macro *)&Macro43;
		break;
	  case 44:
	    temp3 = (struct super_macro *)&Macro44;
		break;
	  case 45:
	    temp3 = (struct super_macro *)&Macro45;
		break;
	  case 46:
	    temp3 = (struct super_macro *)&Macro46;
		break;
	  case 47:
	    temp3 = (struct super_macro *)&Macro47;
		break;
	  case 48:
	    temp3 = (struct super_macro *)&Macro48;
		break;
	  case 49:
	    temp3 = (struct super_macro *)&Macro49;
		break;
	  case 50:
	    temp3 = (struct super_macro *)&Macro50;
		break;
	  case 51:
	    temp3 = (struct super_macro *)&Macro51;
		break;
	  case 52:
	    temp3 = (struct super_macro *)&Macro52;
		break;
	  case 53:
	    temp3 = (struct super_macro *)&Macro53;
		break;
	  case 54:
	    temp3 = (struct super_macro *)&Macro54;
		break;
	  case 55:
	    temp3 = (struct super_macro *)&Macro55;
		break;
	  case 56:
	    temp3 = (struct super_macro *)&Macro56;
		break;
	  case 57:
	    temp3 = (struct super_macro *)&Macro57;
		break;
	  case 58:
	    temp3 = (struct super_macro *)&Macro58;
		break;
	  case 59:
	    temp3 = (struct super_macro *)&Macro59;
		break;
	  case 60:
	    temp3 = (struct super_macro *)&Macro60;
		break;
	  case 61:
	    temp3 = (struct super_macro *)&Macro61;
		break;
	  case 62:
	    temp3 = (struct super_macro *)&Macro62;
		break;
	  case 63:
	    temp3 = (struct super_macro *)&Macro63;
		break;
	  case 64:
	    temp3 = (struct super_macro *)&Macro64;
		break;
	  case 65:
	    temp3 = (struct super_macro *)&Macro65;
		break;
	  case 66:
	    temp3 = (struct super_macro *)&Macro66;
		break;
	  case 67:
	    temp3 = (struct super_macro *)&Macro67;
		break;
	  case 68:
	    temp3 = (struct super_macro *)&Macro68;
		break;
	  case 69:
	    temp3 = (struct super_macro *)&Macro69;
		break;
	  case 70:
	    temp3 = (struct super_macro *)&Macro70;
		break;
	  case 71:
	    temp3 = (struct super_macro *)&Macro71;
		break;
	  case 72:
	    temp3 = (struct super_macro *)&Macro72;
		break;
	  case 73:
	    temp3 = (struct super_macro *)&Macro73;
		break;
	  case 74:
	    temp3 = (struct super_macro *)&Macro74;
		break;
	  case 75:
	    temp3 = (struct super_macro *)&Macro75;
		break;
	  case 76:
	    temp3 = (struct super_macro *)&Macro76;
		break;
	  case 77:
	    temp3 = (struct super_macro *)&Macro77;
		break;
	  case 78:
	    temp3 = (struct super_macro *)&Macro78;
		break;
	  case 79:
	    temp3 = (struct super_macro *)&Macro79;
		break;
	  case 80:
	    temp3 = (struct super_macro *)&Macro80;
		break;
	  case 81:
	    temp3 = (struct super_macro *)&Macro81;
		break;
	  case 82:
	    temp3 = (struct super_macro *)&Macro82;
		break;
	  case 83:
	    temp3 = (struct super_macro *)&Macro83;
		break;
	  case 84:
	    temp3 = (struct super_macro *)&Macro84;
		break;
	  case 85:
	    temp3 = (struct super_macro *)&Macro85;
		break;
	  case 86:
	    temp3 = (struct super_macro *)&Macro86;
		break;
	  case 87:
	    temp3 = (struct super_macro *)&Macro87;
		break;
	  case 88:
	    temp3 = (struct super_macro *)&Macro88;
		break;
	  case 89:
	    temp3 = (struct super_macro *)&Macro89;
		break;
	  case 90:
	    temp3 = (struct super_macro *)&Macro90;
		break;
	  case 91:
	    temp3 = (struct super_macro *)&Macro91;
		break;
	  case 92:
	    temp3 = (struct super_macro *)&Macro92;
		break;
	  case 93:
	    temp3 = (struct super_macro *)&Macro93;
		break;
	  case 94:
	    temp3 = (struct super_macro *)&Macro94;
		break;
	  case 95:
	    temp3 = (struct super_macro *)&Macro95;
		break;
	  case 96:
	    temp3 = (struct super_macro *)&Macro96;
		break;
	  case 97:
	    temp3 = (struct super_macro *)&Macro97;
		break;
	  case 98:
	    temp3 = (struct super_macro *)&Macro98;
		break;
	  case 99:
	    temp3 = (struct super_macro *)&Macro99;
		break;
/*	  case 100:
	    temp3 = (struct super_macro *)&Macro100;
		break;
	  case 101:
	    temp3 = (struct super_macro *)&Macro101;
		break;
	  case 102:
	    temp3 = (struct super_macro *)&Macro102;
		break;
	  case 103:
	    temp3 = (struct super_macro *)&Macro103;
		break;
	  case 104:
	    temp3 = (struct super_macro *)&Macro104;
		break;
	  case 105:
	    temp3 = (struct super_macro *)&Macro105;
		break;
	  case 106:
	    temp3 = (struct super_macro *)&Macro106;
		break;
	  case 107:
	    temp3 = (struct super_macro *)&Macro107;
		break;
	  case 108:
	    temp3 = (struct super_macro *)&Macro108;
		break;
	  case 109:
	    temp3 = (struct super_macro *)&Macro109;
		break;
	  case 110:
	    temp3 = (struct super_macro *)&Macro110;
		break;
	  case 111:
	    temp3 = (struct super_macro *)&Macro111;
		break;
	  case 112:
	    temp3 = (struct super_macro *)&Macro112;
		break;
	  case 113:
	    temp3 = (struct super_macro *)&Macro113;
		break;
	  case 114:
	    temp3 = (struct super_macro *)&Macro114;
		break;
	  case 115:
	    temp3 = (struct super_macro *)&Macro115;
		break;
	  case 116:
	    temp3 = (struct super_macro *)&Macro116;
		break;
	  case 117:
	    temp3 = (struct super_macro *)&Macro117;
		break;
	  case 118:
	    temp3 = (struct super_macro *)&Macro118;
		break;
	  case 119:
	    temp3 = (struct super_macro *)&Macro119;
		break;
	  case 120:
	    temp3 = (struct super_macro *)&Macro120;
		break;
	  case 121:
	    temp3 = (struct super_macro *)&Macro121;
		break;
	  case 122:
	    temp3 = (struct super_macro *)&Macro122;
		break;
	  case 123:
	    temp3 = (struct super_macro *)&Macro123;
		break;
	  case 124:
	    temp3 = (struct super_macro *)&Macro124;
		break;
	  case 125:
	    temp3 = (struct super_macro *)&Macro125;
		break;
	  case 126:
	    temp3 = (struct super_macro *)&Macro126;
		break;
	  case 127:
	    temp3 = (struct super_macro *)&Macro127;
		break;
	  case 128:
	    temp3 = (struct super_macro *)&Macro128;
		break;
	  case 129:
	    temp3 = (struct super_macro *)&Macro129;
		break;
	  case 130:
	    temp3 = (struct super_macro *)&Macro130;
		break;
	  case 131:
	    temp3 = (struct super_macro *)&Macro131;
		break;
	  case 132:
	    temp3 = (struct super_macro *)&Macro132;
		break;
	  case 133:
	    temp3 = (struct super_macro *)&Macro133;
		break;
	  case 134:
	    temp3 = (struct super_macro *)&Macro134;
		break;
	  case 135:
	    temp3 = (struct super_macro *)&Macro135;
		break;
	  case 136:
	    temp3 = (struct super_macro *)&Macro136;
		break;
	  case 137:
	    temp3 = (struct super_macro *)&Macro137;
		break;
	  case 138:
	    temp3 = (struct super_macro *)&Macro138;
		break;
	  case 139:
	    temp3 = (struct super_macro *)&Macro139;
		break;
	  case 140:
	    temp3 = (struct super_macro *)&Macro140;
		break;
	  case 141:
	    temp3 = (struct super_macro *)&Macro141;
		break;
	  case 142:
	    temp3 = (struct super_macro *)&Macro142;
		break;
	  case 143:
	    temp3 = (struct super_macro *)&Macro143;
		break;
	  case 144:
	    temp3 = (struct super_macro *)&Macro144;
		break;
	  case 145:
	    temp3 = (struct super_macro *)&Macro145;
		break;
	  case 146:
	    temp3 = (struct super_macro *)&Macro146;
		break;
	  case 147:
	    temp3 = (struct super_macro *)&Macro147;
		break;
	  case 148:
	    temp3 = (struct super_macro *)&Macro148;
		break;
	  case 149:
	    temp3 = (struct super_macro *)&Macro149;
		break;
	  case 150:
	    temp3 = (struct super_macro *)&Macro150;
		break;
	  case 151:
	    temp3 = (struct super_macro *)&Macro151;
		break;
	  case 152:
	    temp3 = (struct super_macro *)&Macro152;
		break;
	  case 153:
	    temp3 = (struct super_macro *)&Macro153;
		break;
	  case 154:
	    temp3 = (struct super_macro *)&Macro154;
		break;
	  case 155:
	    temp3 = (struct super_macro *)&Macro155;
		break;
	  case 156:
	    temp3 = (struct super_macro *)&Macro156;
		break;
	  case 157:
	    temp3 = (struct super_macro *)&Macro157;
		break;
	  case 158:
	    temp3 = (struct super_macro *)&Macro158;
		break;
	  case 159:
	    temp3 = (struct super_macro *)&Macro159;
		break;
	  case 160:
	    temp3 = (struct super_macro *)&Macro160;
		break;
	  case 161:
	    temp3 = (struct super_macro *)&Macro161;
		break;
	  case 162:
	    temp3 = (struct super_macro *)&Macro162;
		break;
	  case 163:
	    temp3 = (struct super_macro *)&Macro163;
		break;
	  case 164:
	    temp3 = (struct super_macro *)&Macro164;
		break;
	  case 165:
	    temp3 = (struct super_macro *)&Macro165;
		break;
	  case 166:
	    temp3 = (struct super_macro *)&Macro166;
		break;
	  case 167:
	    temp3 = (struct super_macro *)&Macro167;
		break;
	  case 168:
	    temp3 = (struct super_macro *)&Macro168;
		break;
	  case 169:
	    temp3 = (struct super_macro *)&Macro169;
		break;
	  case 170:
	    temp3 = (struct super_macro *)&Macro170;
		break;
	  case 171:
	    temp3 = (struct super_macro *)&Macro171;
		break;
	  case 172:
	    temp3 = (struct super_macro *)&Macro172;
		break;
	  case 173:
	    temp3 = (struct super_macro *)&Macro173;
		break;
	  case 174:
	    temp3 = (struct super_macro *)&Macro174;
		break;
	  case 175:
	    temp3 = (struct super_macro *)&Macro175;
		break;
	  case 176:
	    temp3 = (struct super_macro *)&Macro176;
		break;
	  case 177:
	    temp3 = (struct super_macro *)&Macro177;
		break;
	  case 178:
	    temp3 = (struct super_macro *)&Macro178;
		break;
	  case 179:
	    temp3 = (struct super_macro *)&Macro179;
		break;
	  case 180:
	    temp3 = (struct super_macro *)&Macro180;
		break;
	  case 181:
	    temp3 = (struct super_macro *)&Macro181;
		break;
	  case 182:
	    temp3 = (struct super_macro *)&Macro182;
		break;
	  case 183:
	    temp3 = (struct super_macro *)&Macro183;
		break;
	  case 184:
	    temp3 = (struct super_macro *)&Macro184;
		break;
	  case 185:
	    temp3 = (struct super_macro *)&Macro185;
		break;
	  case 186:
	    temp3 = (struct super_macro *)&Macro186;
		break;
	  case 187:
	    temp3 = (struct super_macro *)&Macro187;
		break;
	  case 188:
	    temp3 = (struct super_macro *)&Macro188;
		break;
	  case 189:
	    temp3 = (struct super_macro *)&Macro189;
		break;
	  case 190:
	    temp3 = (struct super_macro *)&Macro190;
		break;
	  case 191:
	    temp3 = (struct super_macro *)&Macro191;
		break;
	  case 192:
	    temp3 = (struct super_macro *)&Macro192;
		break;
	  case 193:
	    temp3 = (struct super_macro *)&Macro193;
		break;
	  case 194:
	    temp3 = (struct super_macro *)&Macro194;
		break;
	  case 195:
	    temp3 = (struct super_macro *)&Macro195;
		break;
	  case 196:
	    temp3 = (struct super_macro *)&Macro196;
		break;
	  case 197:
	    temp3 = (struct super_macro *)&Macro197;
		break;
	  case 198:
	    temp3 = (struct super_macro *)&Macro198;
		break;
	  case 199:
	    temp3 = (struct super_macro *)&Macro199;
		break; */
	  default:
	    temp3 = (struct super_macro *)&Blank_Entry;
		break;
	}
    temp2.num_entries = temp3->num_entries;				   		  // Number of entries.
	strcpy(temp2.string1, temp3->string1); 						  // Display String
    for (x=0; x<15; x++) {
	  temp2.mac_entry[x].delay.minutes = temp3->mac_entry[x].delay.minutes;
	  temp2.mac_entry[x].delay.seconds = temp3->mac_entry[x].delay.seconds;
	  temp2.mac_entry[x].Time.minutes = temp3->mac_entry[x].Time.minutes;
	  temp2.mac_entry[x].Time.seconds = temp3->mac_entry[x].Time.seconds;
	  temp2.mac_entry[x].protocol = temp3->mac_entry[x].protocol;
	  temp2.mac_entry[x].num_audio = temp3->mac_entry[x].num_audio;
	}
    return(&temp2);	   						// Return the address of the structure.
  }
  // Code logic for User Macros Calculation and Loading Follows
  else if ((entry_num >= USERSUPR_STRT) && (entry_num <= USERSUPR_REND)) {
    entry_num -= USERSUPR_STRT;	   	    	// Adjust entry to start of table.

    //address = (uint) &macro1_data;		   	// Get the address of the start of Sweep Variables.
	//address = address + (entry_num * 120);   // Adjust address for correct entry.

    address1 = (struct user_macro *)&macro1_data;
    // Test Code to display vars.
    sprintf(tempstr,"address1: %lx\n", address1);
    printf2(tempstr);
    address = (unsigned long)address1;
    sprintf(tempstr,"address: %lx\n", address);
    printf2(tempstr);
    address = address + (entry_num * sizeof(macro1_data));   // Adjust address for correct entry.
    sprintf(tempstr,"address: %lx\n", address);
    printf2(tempstr);
    EEPROM_READ((uchar *)address, (uchar *)&temp1, sizeof(temp1));	  	// Retrieve the data from EEPROM.
    //EEPROM_READ(address, temp1);	  		// Retrieve the data from EEPROM.

	// Copy user_macro(temp1) to super_macro(temp2)
	temp2.num_entries = temp1.num_entries;
	strcpy(temp2.string1, temp1.string1);   // Copy String.
    for (x=0; x<temp1.num_entries; x++) {
	  temp2.mac_entry[x].delay.minutes = temp1.mac_entry[x].delay.minutes;
	  temp2.mac_entry[x].delay.seconds = temp1.mac_entry[x].delay.seconds;
	  temp2.mac_entry[x].Time.minutes = temp1.mac_entry[x].Time.minutes;
	  temp2.mac_entry[x].Time.seconds = temp1.mac_entry[x].Time.seconds;
	  temp2.mac_entry[x].protocol = temp1.mac_entry[x].protocol;
	  temp2.mac_entry[x].num_audio = temp1.mac_entry[x].num_audio;
	  temp2.mac_entry[x].phrase[0] = temp1.mac_entry[x].phrase[0];
	  temp2.mac_entry[x].phrase[1] = temp1.mac_entry[x].phrase[1];
	  temp2.mac_entry[x].phrase[2] = temp1.mac_entry[x].phrase[2];
	}
//    for (x=temp1.num_entries; x<UMACRO_LMT; x++) {
/*    for (x=temp1.num_entries; x<10; x++) {
	  temp2.mac_entry[x].delay.minutes = 0;
	  temp2.mac_entry[x].delay.seconds = 0;
	  temp2.mac_entry[x].Time.minutes = 0;
	  temp2.mac_entry[x].Time.seconds = 0;
	  temp2.mac_entry[x].protocol = 0;
	  temp2.mac_entry[x].num_audio = 0;
	  temp2.mac_entry[x].phrase[0] = 0;
	  temp2.mac_entry[x].phrase[1] = 0;
	  temp2.mac_entry[x].phrase[2] = 0;
	} */
    return(&temp2);	   						// Return the address of the structure.
  }
  return(&temp2);	   						// Return the address of the structure.
}

void Macromonitor( char* parm1)
{
	struct super_macro *tempMacro;
	int x;
	char tempstr[80];
	int start, end, relative;

	if( strncmp(parm1, "map", 3) == 0)
	{
		printf2("*****************************************\n");
		printf2("          Entry Map\n");
		printf2("Custom Protocols:\n");
		start = CUSTOM_START;
		end = CUSTOM_END;
		relative = CUSTOM_REND;
		sprintf(tempstr,"     %d to %d      <%d>\n\n", start, end, relative);
		printf2(tempstr);
#ifdef CLW
		printf2("Custom Protocols2:\n");
		start = CUSTOM2_START;
		end = CUSTOM2_END;
		relative = CUSTOM2_REND;
		sprintf(tempstr,"     %d to %d      <%d>\n\n", start, end, relative);
		printf2(tempstr);
		printf2("Custom Protocols3:\n");
		start = CUSTOM3_START;
		end = CUSTOM3_END;
		relative = CUSTOM3_REND;
		sprintf(tempstr,"     %d to %d      <%d>\n\n", start, end, relative);
		printf2(tempstr);
#endif
		printf2("User Protocols:\n");
		start = USER_STRT;
		end = USER_END;
		relative = USER_REND;
		sprintf(tempstr,"     %d to %d      <%d>\n\n", start, end, relative);
		printf2(tempstr);
		printf2("Custom Macros:\n");
		start = CSTMSUPR_STRT;
		end = CSTMSUPR_END;
		relative = CSTMSUPR_REND;
		sprintf(tempstr,"     %d to %d      <%d>\n\n", start, end, relative);
		printf2(tempstr);
		printf2("User Macros:\n");
		start = USERSUPR_STRT;
		end = USERSUPR_END;
		relative = USERSUPR_REND;
		sprintf(tempstr,"     %d to %d      <%d>\n\n", start, end, relative);
		printf2(tempstr);
		printf2("Sweep Macros:\n");
		start = SWEEP_STRT;
		end = SWEEP_END;
		relative = SWEEP_REND;
		sprintf(tempstr,"     %d to %d      <%d>\n\n", start, end, relative);
		printf2(tempstr);
	}
	else
	{
		// Read Entry and print results.
		tempMacro = read_macro((unsigned int) atoi(parm1));

		printf2("*****************************************\n");
		sprintf(tempstr,"read_macro results. Entry: %s\n", parm1);
		printf2(tempstr);

		sprintf(tempstr,"string1: %s\n", tempMacro->string1);
		printf2(tempstr);
		sprintf(tempstr,"Number of entries: %d\n", tempMacro->num_entries);
		printf2(tempstr);

	    for (x=0; x<tempMacro->num_entries; x++) {
	    	sprintf(tempstr,"---------[ENTRY%d]----------------------------\n", x);
	    	printf2(tempstr);
	    	sprintf(tempstr,"  delay.minutes: %d\n", tempMacro->mac_entry[x].delay.minutes);
	    	printf2(tempstr);

	    	sprintf(tempstr,"  delay.seconds: %d\n", tempMacro->mac_entry[x].delay.seconds);
			printf2(tempstr);

			sprintf(tempstr,"  Time.minutes: %d\n", tempMacro->mac_entry[x].Time.minutes);
			printf2(tempstr);

			sprintf(tempstr,"  Time.seconds: %d\n", tempMacro->mac_entry[x].Time.seconds);
			printf2(tempstr);

			sprintf(tempstr,"  protocol: %d\n", tempMacro->mac_entry[x].protocol);
			printf2(tempstr);

			sprintf(tempstr,"  num_audio: %d\n", tempMacro->mac_entry[x].num_audio);
			printf2(tempstr);

			sprintf(tempstr,"  phrase[0]: %d\n", tempMacro->mac_entry[x].phrase[0]);
			printf2(tempstr);

			sprintf(tempstr,"  phrase[1]: %d\n", tempMacro->mac_entry[x].phrase[1]);
			printf2(tempstr);

			sprintf(tempstr,"  phrase[2]: %d\n", tempMacro->mac_entry[x].phrase[2]);
			printf2(tempstr);
		}

	}
	printf2("\n\n");
}

//Professional Macro Definitions
#if PROFSNL
const struct super_macro Macro00 = {Macro00_NumEntries,
		         Macro00_Entry1_DelayMin, Macro00_Entry1_DelaySec, Macro00_Entry1_TimMin, Macro00_Entry1_TimSec, Macro00_Entry1_Protocol, 0, 0, 0, 0,
		         Macro00_Entry2_DelayMin, Macro00_Entry2_DelaySec, Macro00_Entry2_TimMin, Macro00_Entry2_TimSec, Macro00_Entry2_Protocol, 0, 0, 0, 0,
		         Macro00_Entry3_DelayMin, Macro00_Entry3_DelaySec, Macro00_Entry3_TimMin, Macro00_Entry3_TimSec, Macro00_Entry3_Protocol, 0, 0, 0, 0,
		         Macro00_Entry4_DelayMin, Macro00_Entry4_DelaySec, Macro00_Entry4_TimMin, Macro00_Entry4_TimSec, Macro00_Entry4_Protocol, 0, 0, 0, 0,
		         Macro00_Entry5_DelayMin, Macro00_Entry5_DelaySec, Macro00_Entry5_TimMin, Macro00_Entry5_TimSec, Macro00_Entry5_Protocol, 0, 0, 0, 0,
		         Macro00_Entry6_DelayMin, Macro00_Entry6_DelaySec, Macro00_Entry6_TimMin, Macro00_Entry6_TimSec, Macro00_Entry6_Protocol, 0, 0, 0, 0,
		         Macro00_Entry7_DelayMin, Macro00_Entry7_DelaySec, Macro00_Entry7_TimMin, Macro00_Entry7_TimSec, Macro00_Entry7_Protocol, 0, 0, 0, 0,
		         Macro00_Entry8_DelayMin, Macro00_Entry8_DelaySec, Macro00_Entry8_TimMin, Macro00_Entry8_TimSec, Macro00_Entry8_Protocol, 0, 0, 0, 0,
		         Macro00_Entry9_DelayMin, Macro00_Entry9_DelaySec, Macro00_Entry9_TimMin, Macro00_Entry9_TimSec, Macro00_Entry9_Protocol, 0, 0, 0, 0,
		         Macro00_Entry10_DelayMin, Macro00_Entry10_DelaySec, Macro00_Entry10_TimMin, Macro00_Entry10_TimSec, Macro00_Entry10_Protocol, 0, 0, 0, 0,
		         Macro00_Entry11_DelayMin, Macro00_Entry11_DelaySec, Macro00_Entry11_TimMin, Macro00_Entry11_TimSec, Macro00_Entry11_Protocol, 0, 0, 0, 0,
		         Macro00_Entry12_DelayMin, Macro00_Entry12_DelaySec, Macro00_Entry12_TimMin, Macro00_Entry12_TimSec, Macro00_Entry12_Protocol, 0, 0, 0, 0,
		         Macro00_Entry13_DelayMin, Macro00_Entry13_DelaySec, Macro00_Entry13_TimMin, Macro00_Entry13_TimSec, Macro00_Entry13_Protocol, 0, 0, 0, 0,
		         Macro00_Entry14_DelayMin, Macro00_Entry14_DelaySec, Macro00_Entry14_TimMin, Macro00_Entry14_TimSec, Macro00_Entry14_Protocol, 0, 0, 0, 0,
		         Macro00_Entry15_DelayMin, Macro00_Entry15_DelaySec, Macro00_Entry15_TimMin, Macro00_Entry15_TimSec, Macro00_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR00_STRING};

const struct super_macro Macro01 = {Macro01_NumEntries,
		         Macro01_Entry1_DelayMin, Macro01_Entry1_DelaySec, Macro01_Entry1_TimMin, Macro01_Entry1_TimSec, Macro01_Entry1_Protocol, 0, 0, 0, 0,
		         Macro01_Entry2_DelayMin, Macro01_Entry2_DelaySec, Macro01_Entry2_TimMin, Macro01_Entry2_TimSec, Macro01_Entry2_Protocol, 0, 0, 0, 0,
		         Macro01_Entry3_DelayMin, Macro01_Entry3_DelaySec, Macro01_Entry3_TimMin, Macro01_Entry3_TimSec, Macro01_Entry3_Protocol, 0, 0, 0, 0,
		         Macro01_Entry4_DelayMin, Macro01_Entry4_DelaySec, Macro01_Entry4_TimMin, Macro01_Entry4_TimSec, Macro01_Entry4_Protocol, 0, 0, 0, 0,
		         Macro01_Entry5_DelayMin, Macro01_Entry5_DelaySec, Macro01_Entry5_TimMin, Macro01_Entry5_TimSec, Macro01_Entry5_Protocol, 0, 0, 0, 0,
		         Macro01_Entry6_DelayMin, Macro01_Entry6_DelaySec, Macro01_Entry6_TimMin, Macro01_Entry6_TimSec, Macro01_Entry6_Protocol, 0, 0, 0, 0,
		         Macro01_Entry7_DelayMin, Macro01_Entry7_DelaySec, Macro01_Entry7_TimMin, Macro01_Entry7_TimSec, Macro01_Entry7_Protocol, 0, 0, 0, 0,
		         Macro01_Entry8_DelayMin, Macro01_Entry8_DelaySec, Macro01_Entry8_TimMin, Macro01_Entry8_TimSec, Macro01_Entry8_Protocol, 0, 0, 0, 0,
		         Macro01_Entry9_DelayMin, Macro01_Entry9_DelaySec, Macro01_Entry9_TimMin, Macro01_Entry9_TimSec, Macro01_Entry9_Protocol, 0, 0, 0, 0,
		         Macro01_Entry10_DelayMin, Macro01_Entry10_DelaySec, Macro01_Entry10_TimMin, Macro01_Entry10_TimSec, Macro01_Entry10_Protocol, 0, 0, 0, 0,
		         Macro01_Entry11_DelayMin, Macro01_Entry11_DelaySec, Macro01_Entry11_TimMin, Macro01_Entry11_TimSec, Macro01_Entry11_Protocol, 0, 0, 0, 0,
		         Macro01_Entry12_DelayMin, Macro01_Entry12_DelaySec, Macro01_Entry12_TimMin, Macro01_Entry12_TimSec, Macro01_Entry12_Protocol, 0, 0, 0, 0,
		         Macro01_Entry13_DelayMin, Macro01_Entry13_DelaySec, Macro01_Entry13_TimMin, Macro01_Entry13_TimSec, Macro01_Entry13_Protocol, 0, 0, 0, 0,
		         Macro01_Entry14_DelayMin, Macro01_Entry14_DelaySec, Macro01_Entry14_TimMin, Macro01_Entry14_TimSec, Macro01_Entry14_Protocol, 0, 0, 0, 0,
		         Macro01_Entry15_DelayMin, Macro01_Entry15_DelaySec, Macro01_Entry15_TimMin, Macro01_Entry15_TimSec, Macro01_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR01_STRING};

const struct super_macro Macro02 = {Macro02_NumEntries,
		         Macro02_Entry1_DelayMin, Macro02_Entry1_DelaySec, Macro02_Entry1_TimMin, Macro02_Entry1_TimSec, Macro02_Entry1_Protocol, 0, 0, 0, 0,
		         Macro02_Entry2_DelayMin, Macro02_Entry2_DelaySec, Macro02_Entry2_TimMin, Macro02_Entry2_TimSec, Macro02_Entry2_Protocol, 0, 0, 0, 0,
		         Macro02_Entry3_DelayMin, Macro02_Entry3_DelaySec, Macro02_Entry3_TimMin, Macro02_Entry3_TimSec, Macro02_Entry3_Protocol, 0, 0, 0, 0,
		         Macro02_Entry4_DelayMin, Macro02_Entry4_DelaySec, Macro02_Entry4_TimMin, Macro02_Entry4_TimSec, Macro02_Entry4_Protocol, 0, 0, 0, 0,
		         Macro02_Entry5_DelayMin, Macro02_Entry5_DelaySec, Macro02_Entry5_TimMin, Macro02_Entry5_TimSec, Macro02_Entry5_Protocol, 0, 0, 0, 0,
		         Macro02_Entry6_DelayMin, Macro02_Entry6_DelaySec, Macro02_Entry6_TimMin, Macro02_Entry6_TimSec, Macro02_Entry6_Protocol, 0, 0, 0, 0,
		         Macro02_Entry7_DelayMin, Macro02_Entry7_DelaySec, Macro02_Entry7_TimMin, Macro02_Entry7_TimSec, Macro02_Entry7_Protocol, 0, 0, 0, 0,
		         Macro02_Entry8_DelayMin, Macro02_Entry8_DelaySec, Macro02_Entry8_TimMin, Macro02_Entry8_TimSec, Macro02_Entry8_Protocol, 0, 0, 0, 0,
		         Macro02_Entry9_DelayMin, Macro02_Entry9_DelaySec, Macro02_Entry9_TimMin, Macro02_Entry9_TimSec, Macro02_Entry9_Protocol, 0, 0, 0, 0,
		         Macro02_Entry10_DelayMin, Macro02_Entry10_DelaySec, Macro02_Entry10_TimMin, Macro02_Entry10_TimSec, Macro02_Entry10_Protocol, 0, 0, 0, 0,
		         Macro02_Entry11_DelayMin, Macro02_Entry11_DelaySec, Macro02_Entry11_TimMin, Macro02_Entry11_TimSec, Macro02_Entry11_Protocol, 0, 0, 0, 0,
		         Macro02_Entry12_DelayMin, Macro02_Entry12_DelaySec, Macro02_Entry12_TimMin, Macro02_Entry12_TimSec, Macro02_Entry12_Protocol, 0, 0, 0, 0,
		         Macro02_Entry13_DelayMin, Macro02_Entry13_DelaySec, Macro02_Entry13_TimMin, Macro02_Entry13_TimSec, Macro02_Entry13_Protocol, 0, 0, 0, 0,
		         Macro02_Entry14_DelayMin, Macro02_Entry14_DelaySec, Macro02_Entry14_TimMin, Macro02_Entry14_TimSec, Macro02_Entry14_Protocol, 0, 0, 0, 0,
		         Macro02_Entry15_DelayMin, Macro02_Entry15_DelaySec, Macro02_Entry15_TimMin, Macro02_Entry15_TimSec, Macro02_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR02_STRING};

const struct super_macro Macro03 = {Macro03_NumEntries,
		         Macro03_Entry1_DelayMin, Macro03_Entry1_DelaySec, Macro03_Entry1_TimMin, Macro03_Entry1_TimSec, Macro03_Entry1_Protocol, 0, 0, 0, 0,
		         Macro03_Entry2_DelayMin, Macro03_Entry2_DelaySec, Macro03_Entry2_TimMin, Macro03_Entry2_TimSec, Macro03_Entry2_Protocol, 0, 0, 0, 0,
		         Macro03_Entry3_DelayMin, Macro03_Entry3_DelaySec, Macro03_Entry3_TimMin, Macro03_Entry3_TimSec, Macro03_Entry3_Protocol, 0, 0, 0, 0,
		         Macro03_Entry4_DelayMin, Macro03_Entry4_DelaySec, Macro03_Entry4_TimMin, Macro03_Entry4_TimSec, Macro03_Entry4_Protocol, 0, 0, 0, 0,
		         Macro03_Entry5_DelayMin, Macro03_Entry5_DelaySec, Macro03_Entry5_TimMin, Macro03_Entry5_TimSec, Macro03_Entry5_Protocol, 0, 0, 0, 0,
		         Macro03_Entry6_DelayMin, Macro03_Entry6_DelaySec, Macro03_Entry6_TimMin, Macro03_Entry6_TimSec, Macro03_Entry6_Protocol, 0, 0, 0, 0,
		         Macro03_Entry7_DelayMin, Macro03_Entry7_DelaySec, Macro03_Entry7_TimMin, Macro03_Entry7_TimSec, Macro03_Entry7_Protocol, 0, 0, 0, 0,
		         Macro03_Entry8_DelayMin, Macro03_Entry8_DelaySec, Macro03_Entry8_TimMin, Macro03_Entry8_TimSec, Macro03_Entry8_Protocol, 0, 0, 0, 0,
		         Macro03_Entry9_DelayMin, Macro03_Entry9_DelaySec, Macro03_Entry9_TimMin, Macro03_Entry9_TimSec, Macro03_Entry9_Protocol, 0, 0, 0, 0,
		         Macro03_Entry10_DelayMin, Macro03_Entry10_DelaySec, Macro03_Entry10_TimMin, Macro03_Entry10_TimSec, Macro03_Entry10_Protocol, 0, 0, 0, 0,
		         Macro03_Entry11_DelayMin, Macro03_Entry11_DelaySec, Macro03_Entry11_TimMin, Macro03_Entry11_TimSec, Macro03_Entry11_Protocol, 0, 0, 0, 0,
		         Macro03_Entry12_DelayMin, Macro03_Entry12_DelaySec, Macro03_Entry12_TimMin, Macro03_Entry12_TimSec, Macro03_Entry12_Protocol, 0, 0, 0, 0,
		         Macro03_Entry13_DelayMin, Macro03_Entry13_DelaySec, Macro03_Entry13_TimMin, Macro03_Entry13_TimSec, Macro03_Entry13_Protocol, 0, 0, 0, 0,
		         Macro03_Entry14_DelayMin, Macro03_Entry14_DelaySec, Macro03_Entry14_TimMin, Macro03_Entry14_TimSec, Macro03_Entry14_Protocol, 0, 0, 0, 0,
		         Macro03_Entry15_DelayMin, Macro03_Entry15_DelaySec, Macro03_Entry15_TimMin, Macro03_Entry15_TimSec, Macro03_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR03_STRING};

const struct super_macro Macro04 = {Macro04_NumEntries,
		         Macro04_Entry1_DelayMin, Macro04_Entry1_DelaySec, Macro04_Entry1_TimMin, Macro04_Entry1_TimSec, Macro04_Entry1_Protocol, 0, 0, 0, 0,
		         Macro04_Entry2_DelayMin, Macro04_Entry2_DelaySec, Macro04_Entry2_TimMin, Macro04_Entry2_TimSec, Macro04_Entry2_Protocol, 0, 0, 0, 0,
		         Macro04_Entry3_DelayMin, Macro04_Entry3_DelaySec, Macro04_Entry3_TimMin, Macro04_Entry3_TimSec, Macro04_Entry3_Protocol, 0, 0, 0, 0,
		         Macro04_Entry4_DelayMin, Macro04_Entry4_DelaySec, Macro04_Entry4_TimMin, Macro04_Entry4_TimSec, Macro04_Entry4_Protocol, 0, 0, 0, 0,
		         Macro04_Entry5_DelayMin, Macro04_Entry5_DelaySec, Macro04_Entry5_TimMin, Macro04_Entry5_TimSec, Macro04_Entry5_Protocol, 0, 0, 0, 0,
		         Macro04_Entry6_DelayMin, Macro04_Entry6_DelaySec, Macro04_Entry6_TimMin, Macro04_Entry6_TimSec, Macro04_Entry6_Protocol, 0, 0, 0, 0,
		         Macro04_Entry7_DelayMin, Macro04_Entry7_DelaySec, Macro04_Entry7_TimMin, Macro04_Entry7_TimSec, Macro04_Entry7_Protocol, 0, 0, 0, 0,
		         Macro04_Entry8_DelayMin, Macro04_Entry8_DelaySec, Macro04_Entry8_TimMin, Macro04_Entry8_TimSec, Macro04_Entry8_Protocol, 0, 0, 0, 0,
		         Macro04_Entry9_DelayMin, Macro04_Entry9_DelaySec, Macro04_Entry9_TimMin, Macro04_Entry9_TimSec, Macro04_Entry9_Protocol, 0, 0, 0, 0,
		         Macro04_Entry10_DelayMin, Macro04_Entry10_DelaySec, Macro04_Entry10_TimMin, Macro04_Entry10_TimSec, Macro04_Entry10_Protocol, 0, 0, 0, 0,
		         Macro04_Entry11_DelayMin, Macro04_Entry11_DelaySec, Macro04_Entry11_TimMin, Macro04_Entry11_TimSec, Macro04_Entry11_Protocol, 0, 0, 0, 0,
		         Macro04_Entry12_DelayMin, Macro04_Entry12_DelaySec, Macro04_Entry12_TimMin, Macro04_Entry12_TimSec, Macro04_Entry12_Protocol, 0, 0, 0, 0,
		         Macro04_Entry13_DelayMin, Macro04_Entry13_DelaySec, Macro04_Entry13_TimMin, Macro04_Entry13_TimSec, Macro04_Entry13_Protocol, 0, 0, 0, 0,
		         Macro04_Entry14_DelayMin, Macro04_Entry14_DelaySec, Macro04_Entry14_TimMin, Macro04_Entry14_TimSec, Macro04_Entry14_Protocol, 0, 0, 0, 0,
		         Macro04_Entry15_DelayMin, Macro04_Entry15_DelaySec, Macro04_Entry15_TimMin, Macro04_Entry15_TimSec, Macro04_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR04_STRING};

const struct super_macro Macro05 = {Macro05_NumEntries,
		         Macro05_Entry1_DelayMin, Macro05_Entry1_DelaySec, Macro05_Entry1_TimMin, Macro05_Entry1_TimSec, Macro05_Entry1_Protocol, 0, 0, 0, 0,
		         Macro05_Entry2_DelayMin, Macro05_Entry2_DelaySec, Macro05_Entry2_TimMin, Macro05_Entry2_TimSec, Macro05_Entry2_Protocol, 0, 0, 0, 0,
		         Macro05_Entry3_DelayMin, Macro05_Entry3_DelaySec, Macro05_Entry3_TimMin, Macro05_Entry3_TimSec, Macro05_Entry3_Protocol, 0, 0, 0, 0,
		         Macro05_Entry4_DelayMin, Macro05_Entry4_DelaySec, Macro05_Entry4_TimMin, Macro05_Entry4_TimSec, Macro05_Entry4_Protocol, 0, 0, 0, 0,
		         Macro05_Entry5_DelayMin, Macro05_Entry5_DelaySec, Macro05_Entry5_TimMin, Macro05_Entry5_TimSec, Macro05_Entry5_Protocol, 0, 0, 0, 0,
		         Macro05_Entry6_DelayMin, Macro05_Entry6_DelaySec, Macro05_Entry6_TimMin, Macro05_Entry6_TimSec, Macro05_Entry6_Protocol, 0, 0, 0, 0,
		         Macro05_Entry7_DelayMin, Macro05_Entry7_DelaySec, Macro05_Entry7_TimMin, Macro05_Entry7_TimSec, Macro05_Entry7_Protocol, 0, 0, 0, 0,
		         Macro05_Entry8_DelayMin, Macro05_Entry8_DelaySec, Macro05_Entry8_TimMin, Macro05_Entry8_TimSec, Macro05_Entry8_Protocol, 0, 0, 0, 0,
		         Macro05_Entry9_DelayMin, Macro05_Entry9_DelaySec, Macro05_Entry9_TimMin, Macro05_Entry9_TimSec, Macro05_Entry9_Protocol, 0, 0, 0, 0,
		         Macro05_Entry10_DelayMin, Macro05_Entry10_DelaySec, Macro05_Entry10_TimMin, Macro05_Entry10_TimSec, Macro05_Entry10_Protocol, 0, 0, 0, 0,
		         Macro05_Entry11_DelayMin, Macro05_Entry11_DelaySec, Macro05_Entry11_TimMin, Macro05_Entry11_TimSec, Macro05_Entry11_Protocol, 0, 0, 0, 0,
		         Macro05_Entry12_DelayMin, Macro05_Entry12_DelaySec, Macro05_Entry12_TimMin, Macro05_Entry12_TimSec, Macro05_Entry12_Protocol, 0, 0, 0, 0,
		         Macro05_Entry13_DelayMin, Macro05_Entry13_DelaySec, Macro05_Entry13_TimMin, Macro05_Entry13_TimSec, Macro05_Entry13_Protocol, 0, 0, 0, 0,
		         Macro05_Entry14_DelayMin, Macro05_Entry14_DelaySec, Macro05_Entry14_TimMin, Macro05_Entry14_TimSec, Macro05_Entry14_Protocol, 0, 0, 0, 0,
		         Macro05_Entry15_DelayMin, Macro05_Entry15_DelaySec, Macro05_Entry15_TimMin, Macro05_Entry15_TimSec, Macro05_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR05_STRING};

const struct super_macro Macro06 = {Macro06_NumEntries,
		         Macro06_Entry1_DelayMin, Macro06_Entry1_DelaySec, Macro06_Entry1_TimMin, Macro06_Entry1_TimSec, Macro06_Entry1_Protocol, 0, 0, 0, 0,
		         Macro06_Entry2_DelayMin, Macro06_Entry2_DelaySec, Macro06_Entry2_TimMin, Macro06_Entry2_TimSec, Macro06_Entry2_Protocol, 0, 0, 0, 0,
		         Macro06_Entry3_DelayMin, Macro06_Entry3_DelaySec, Macro06_Entry3_TimMin, Macro06_Entry3_TimSec, Macro06_Entry3_Protocol, 0, 0, 0, 0,
		         Macro06_Entry4_DelayMin, Macro06_Entry4_DelaySec, Macro06_Entry4_TimMin, Macro06_Entry4_TimSec, Macro06_Entry4_Protocol, 0, 0, 0, 0,
		         Macro06_Entry5_DelayMin, Macro06_Entry5_DelaySec, Macro06_Entry5_TimMin, Macro06_Entry5_TimSec, Macro06_Entry5_Protocol, 0, 0, 0, 0,
		         Macro06_Entry6_DelayMin, Macro06_Entry6_DelaySec, Macro06_Entry6_TimMin, Macro06_Entry6_TimSec, Macro06_Entry6_Protocol, 0, 0, 0, 0,
		         Macro06_Entry7_DelayMin, Macro06_Entry7_DelaySec, Macro06_Entry7_TimMin, Macro06_Entry7_TimSec, Macro06_Entry7_Protocol, 0, 0, 0, 0,
		         Macro06_Entry8_DelayMin, Macro06_Entry8_DelaySec, Macro06_Entry8_TimMin, Macro06_Entry8_TimSec, Macro06_Entry8_Protocol, 0, 0, 0, 0,
		         Macro06_Entry9_DelayMin, Macro06_Entry9_DelaySec, Macro06_Entry9_TimMin, Macro06_Entry9_TimSec, Macro06_Entry9_Protocol, 0, 0, 0, 0,
		         Macro06_Entry10_DelayMin, Macro06_Entry10_DelaySec, Macro06_Entry10_TimMin, Macro06_Entry10_TimSec, Macro06_Entry10_Protocol, 0, 0, 0, 0,
		         Macro06_Entry11_DelayMin, Macro06_Entry11_DelaySec, Macro06_Entry11_TimMin, Macro06_Entry11_TimSec, Macro06_Entry11_Protocol, 0, 0, 0, 0,
		         Macro06_Entry12_DelayMin, Macro06_Entry12_DelaySec, Macro06_Entry12_TimMin, Macro06_Entry12_TimSec, Macro06_Entry12_Protocol, 0, 0, 0, 0,
		         Macro06_Entry13_DelayMin, Macro06_Entry13_DelaySec, Macro06_Entry13_TimMin, Macro06_Entry13_TimSec, Macro06_Entry13_Protocol, 0, 0, 0, 0,
		         Macro06_Entry14_DelayMin, Macro06_Entry14_DelaySec, Macro06_Entry14_TimMin, Macro06_Entry14_TimSec, Macro06_Entry14_Protocol, 0, 0, 0, 0,
		         Macro06_Entry15_DelayMin, Macro06_Entry15_DelaySec, Macro06_Entry15_TimMin, Macro06_Entry15_TimSec, Macro06_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR06_STRING};

const struct super_macro Macro07 = {Macro07_NumEntries,
		         Macro07_Entry1_DelayMin, Macro07_Entry1_DelaySec, Macro07_Entry1_TimMin, Macro07_Entry1_TimSec, Macro07_Entry1_Protocol, 0, 0, 0, 0,
		         Macro07_Entry2_DelayMin, Macro07_Entry2_DelaySec, Macro07_Entry2_TimMin, Macro07_Entry2_TimSec, Macro07_Entry2_Protocol, 0, 0, 0, 0,
		         Macro07_Entry3_DelayMin, Macro07_Entry3_DelaySec, Macro07_Entry3_TimMin, Macro07_Entry3_TimSec, Macro07_Entry3_Protocol, 0, 0, 0, 0,
		         Macro07_Entry4_DelayMin, Macro07_Entry4_DelaySec, Macro07_Entry4_TimMin, Macro07_Entry4_TimSec, Macro07_Entry4_Protocol, 0, 0, 0, 0,
		         Macro07_Entry5_DelayMin, Macro07_Entry5_DelaySec, Macro07_Entry5_TimMin, Macro07_Entry5_TimSec, Macro07_Entry5_Protocol, 0, 0, 0, 0,
		         Macro07_Entry6_DelayMin, Macro07_Entry6_DelaySec, Macro07_Entry6_TimMin, Macro07_Entry6_TimSec, Macro07_Entry6_Protocol, 0, 0, 0, 0,
		         Macro07_Entry7_DelayMin, Macro07_Entry7_DelaySec, Macro07_Entry7_TimMin, Macro07_Entry7_TimSec, Macro07_Entry7_Protocol, 0, 0, 0, 0,
		         Macro07_Entry8_DelayMin, Macro07_Entry8_DelaySec, Macro07_Entry8_TimMin, Macro07_Entry8_TimSec, Macro07_Entry8_Protocol, 0, 0, 0, 0,
		         Macro07_Entry9_DelayMin, Macro07_Entry9_DelaySec, Macro07_Entry9_TimMin, Macro07_Entry9_TimSec, Macro07_Entry9_Protocol, 0, 0, 0, 0,
		         Macro07_Entry10_DelayMin, Macro07_Entry10_DelaySec, Macro07_Entry10_TimMin, Macro07_Entry10_TimSec, Macro07_Entry10_Protocol, 0, 0, 0, 0,
		         Macro07_Entry11_DelayMin, Macro07_Entry11_DelaySec, Macro07_Entry11_TimMin, Macro07_Entry11_TimSec, Macro07_Entry11_Protocol, 0, 0, 0, 0,
		         Macro07_Entry12_DelayMin, Macro07_Entry12_DelaySec, Macro07_Entry12_TimMin, Macro07_Entry12_TimSec, Macro07_Entry12_Protocol, 0, 0, 0, 0,
		         Macro07_Entry13_DelayMin, Macro07_Entry13_DelaySec, Macro07_Entry13_TimMin, Macro07_Entry13_TimSec, Macro07_Entry13_Protocol, 0, 0, 0, 0,
		         Macro07_Entry14_DelayMin, Macro07_Entry14_DelaySec, Macro07_Entry14_TimMin, Macro07_Entry14_TimSec, Macro07_Entry14_Protocol, 0, 0, 0, 0,
		         Macro07_Entry15_DelayMin, Macro07_Entry15_DelaySec, Macro07_Entry15_TimMin, Macro07_Entry15_TimSec, Macro07_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR07_STRING};

const struct super_macro Macro08 = {Macro08_NumEntries,
		         Macro08_Entry1_DelayMin, Macro08_Entry1_DelaySec, Macro08_Entry1_TimMin, Macro08_Entry1_TimSec, Macro08_Entry1_Protocol, 0, 0, 0, 0,
		         Macro08_Entry2_DelayMin, Macro08_Entry2_DelaySec, Macro08_Entry2_TimMin, Macro08_Entry2_TimSec, Macro08_Entry2_Protocol, 0, 0, 0, 0,
		         Macro08_Entry3_DelayMin, Macro08_Entry3_DelaySec, Macro08_Entry3_TimMin, Macro08_Entry3_TimSec, Macro08_Entry3_Protocol, 0, 0, 0, 0,
		         Macro08_Entry4_DelayMin, Macro08_Entry4_DelaySec, Macro08_Entry4_TimMin, Macro08_Entry4_TimSec, Macro08_Entry4_Protocol, 0, 0, 0, 0,
		         Macro08_Entry5_DelayMin, Macro08_Entry5_DelaySec, Macro08_Entry5_TimMin, Macro08_Entry5_TimSec, Macro08_Entry5_Protocol, 0, 0, 0, 0,
		         Macro08_Entry6_DelayMin, Macro08_Entry6_DelaySec, Macro08_Entry6_TimMin, Macro08_Entry6_TimSec, Macro08_Entry6_Protocol, 0, 0, 0, 0,
		         Macro08_Entry7_DelayMin, Macro08_Entry7_DelaySec, Macro08_Entry7_TimMin, Macro08_Entry7_TimSec, Macro08_Entry7_Protocol, 0, 0, 0, 0,
		         Macro08_Entry8_DelayMin, Macro08_Entry8_DelaySec, Macro08_Entry8_TimMin, Macro08_Entry8_TimSec, Macro08_Entry8_Protocol, 0, 0, 0, 0,
		         Macro08_Entry9_DelayMin, Macro08_Entry9_DelaySec, Macro08_Entry9_TimMin, Macro08_Entry9_TimSec, Macro08_Entry9_Protocol, 0, 0, 0, 0,
		         Macro08_Entry10_DelayMin, Macro08_Entry10_DelaySec, Macro08_Entry10_TimMin, Macro08_Entry10_TimSec, Macro08_Entry10_Protocol, 0, 0, 0, 0,
		         Macro08_Entry11_DelayMin, Macro08_Entry11_DelaySec, Macro08_Entry11_TimMin, Macro08_Entry11_TimSec, Macro08_Entry11_Protocol, 0, 0, 0, 0,
		         Macro08_Entry12_DelayMin, Macro08_Entry12_DelaySec, Macro08_Entry12_TimMin, Macro08_Entry12_TimSec, Macro08_Entry12_Protocol, 0, 0, 0, 0,
		         Macro08_Entry13_DelayMin, Macro08_Entry13_DelaySec, Macro08_Entry13_TimMin, Macro08_Entry13_TimSec, Macro08_Entry13_Protocol, 0, 0, 0, 0,
		         Macro08_Entry14_DelayMin, Macro08_Entry14_DelaySec, Macro08_Entry14_TimMin, Macro08_Entry14_TimSec, Macro08_Entry14_Protocol, 0, 0, 0, 0,
		         Macro08_Entry15_DelayMin, Macro08_Entry15_DelaySec, Macro08_Entry15_TimMin, Macro08_Entry15_TimSec, Macro08_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR08_STRING};

const struct super_macro Macro09 = {Macro09_NumEntries,
		         Macro09_Entry1_DelayMin, Macro09_Entry1_DelaySec, Macro09_Entry1_TimMin, Macro09_Entry1_TimSec, Macro09_Entry1_Protocol, 0, 0, 0, 0,
		         Macro09_Entry2_DelayMin, Macro09_Entry2_DelaySec, Macro09_Entry2_TimMin, Macro09_Entry2_TimSec, Macro09_Entry2_Protocol, 0, 0, 0, 0,
		         Macro09_Entry3_DelayMin, Macro09_Entry3_DelaySec, Macro09_Entry3_TimMin, Macro09_Entry3_TimSec, Macro09_Entry3_Protocol, 0, 0, 0, 0,
		         Macro09_Entry4_DelayMin, Macro09_Entry4_DelaySec, Macro09_Entry4_TimMin, Macro09_Entry4_TimSec, Macro09_Entry4_Protocol, 0, 0, 0, 0,
		         Macro09_Entry5_DelayMin, Macro09_Entry5_DelaySec, Macro09_Entry5_TimMin, Macro09_Entry5_TimSec, Macro09_Entry5_Protocol, 0, 0, 0, 0,
		         Macro09_Entry6_DelayMin, Macro09_Entry6_DelaySec, Macro09_Entry6_TimMin, Macro09_Entry6_TimSec, Macro09_Entry6_Protocol, 0, 0, 0, 0,
		         Macro09_Entry7_DelayMin, Macro09_Entry7_DelaySec, Macro09_Entry7_TimMin, Macro09_Entry7_TimSec, Macro09_Entry7_Protocol, 0, 0, 0, 0,
		         Macro09_Entry8_DelayMin, Macro09_Entry8_DelaySec, Macro09_Entry8_TimMin, Macro09_Entry8_TimSec, Macro09_Entry8_Protocol, 0, 0, 0, 0,
		         Macro09_Entry9_DelayMin, Macro09_Entry9_DelaySec, Macro09_Entry9_TimMin, Macro09_Entry9_TimSec, Macro09_Entry9_Protocol, 0, 0, 0, 0,
		         Macro09_Entry10_DelayMin, Macro09_Entry10_DelaySec, Macro09_Entry10_TimMin, Macro09_Entry10_TimSec, Macro09_Entry10_Protocol, 0, 0, 0, 0,
		         Macro09_Entry11_DelayMin, Macro09_Entry11_DelaySec, Macro09_Entry11_TimMin, Macro09_Entry11_TimSec, Macro09_Entry11_Protocol, 0, 0, 0, 0,
		         Macro09_Entry12_DelayMin, Macro09_Entry12_DelaySec, Macro09_Entry12_TimMin, Macro09_Entry12_TimSec, Macro09_Entry12_Protocol, 0, 0, 0, 0,
		         Macro09_Entry13_DelayMin, Macro09_Entry13_DelaySec, Macro09_Entry13_TimMin, Macro09_Entry13_TimSec, Macro09_Entry13_Protocol, 0, 0, 0, 0,
		         Macro09_Entry14_DelayMin, Macro09_Entry14_DelaySec, Macro09_Entry14_TimMin, Macro09_Entry14_TimSec, Macro09_Entry14_Protocol, 0, 0, 0, 0,
		         Macro09_Entry15_DelayMin, Macro09_Entry15_DelaySec, Macro09_Entry15_TimMin, Macro09_Entry15_TimSec, Macro09_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR09_STRING};

const struct super_macro Macro10 = {Macro10_NumEntries,
		         Macro10_Entry1_DelayMin, Macro10_Entry1_DelaySec, Macro10_Entry1_TimMin, Macro10_Entry1_TimSec, Macro10_Entry1_Protocol, 0, 0, 0, 0,
		         Macro10_Entry2_DelayMin, Macro10_Entry2_DelaySec, Macro10_Entry2_TimMin, Macro10_Entry2_TimSec, Macro10_Entry2_Protocol, 0, 0, 0, 0,
		         Macro10_Entry3_DelayMin, Macro10_Entry3_DelaySec, Macro10_Entry3_TimMin, Macro10_Entry3_TimSec, Macro10_Entry3_Protocol, 0, 0, 0, 0,
		         Macro10_Entry4_DelayMin, Macro10_Entry4_DelaySec, Macro10_Entry4_TimMin, Macro10_Entry4_TimSec, Macro10_Entry4_Protocol, 0, 0, 0, 0,
		         Macro10_Entry5_DelayMin, Macro10_Entry5_DelaySec, Macro10_Entry5_TimMin, Macro10_Entry5_TimSec, Macro10_Entry5_Protocol, 0, 0, 0, 0,
		         Macro10_Entry6_DelayMin, Macro10_Entry6_DelaySec, Macro10_Entry6_TimMin, Macro10_Entry6_TimSec, Macro10_Entry6_Protocol, 0, 0, 0, 0,
		         Macro10_Entry7_DelayMin, Macro10_Entry7_DelaySec, Macro10_Entry7_TimMin, Macro10_Entry7_TimSec, Macro10_Entry7_Protocol, 0, 0, 0, 0,
		         Macro10_Entry8_DelayMin, Macro10_Entry8_DelaySec, Macro10_Entry8_TimMin, Macro10_Entry8_TimSec, Macro10_Entry8_Protocol, 0, 0, 0, 0,
		         Macro10_Entry9_DelayMin, Macro10_Entry9_DelaySec, Macro10_Entry9_TimMin, Macro10_Entry9_TimSec, Macro10_Entry9_Protocol, 0, 0, 0, 0,
		         Macro10_Entry10_DelayMin, Macro10_Entry10_DelaySec, Macro10_Entry10_TimMin, Macro10_Entry10_TimSec, Macro10_Entry10_Protocol, 0, 0, 0, 0,
		         Macro10_Entry11_DelayMin, Macro10_Entry11_DelaySec, Macro10_Entry11_TimMin, Macro10_Entry11_TimSec, Macro10_Entry11_Protocol, 0, 0, 0, 0,
		         Macro10_Entry12_DelayMin, Macro10_Entry12_DelaySec, Macro10_Entry12_TimMin, Macro10_Entry12_TimSec, Macro10_Entry12_Protocol, 0, 0, 0, 0,
		         Macro10_Entry13_DelayMin, Macro10_Entry13_DelaySec, Macro10_Entry13_TimMin, Macro10_Entry13_TimSec, Macro10_Entry13_Protocol, 0, 0, 0, 0,
		         Macro10_Entry14_DelayMin, Macro10_Entry14_DelaySec, Macro10_Entry14_TimMin, Macro10_Entry14_TimSec, Macro10_Entry14_Protocol, 0, 0, 0, 0,
		         Macro10_Entry15_DelayMin, Macro10_Entry15_DelaySec, Macro10_Entry15_TimMin, Macro10_Entry15_TimSec, Macro10_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR10_STRING};

const struct super_macro Macro11 = {Macro11_NumEntries,
		         Macro11_Entry1_DelayMin, Macro11_Entry1_DelaySec, Macro11_Entry1_TimMin, Macro11_Entry1_TimSec, Macro11_Entry1_Protocol, 0, 0, 0, 0,
		         Macro11_Entry2_DelayMin, Macro11_Entry2_DelaySec, Macro11_Entry2_TimMin, Macro11_Entry2_TimSec, Macro11_Entry2_Protocol, 0, 0, 0, 0,
		         Macro11_Entry3_DelayMin, Macro11_Entry3_DelaySec, Macro11_Entry3_TimMin, Macro11_Entry3_TimSec, Macro11_Entry3_Protocol, 0, 0, 0, 0,
		         Macro11_Entry4_DelayMin, Macro11_Entry4_DelaySec, Macro11_Entry4_TimMin, Macro11_Entry4_TimSec, Macro11_Entry4_Protocol, 0, 0, 0, 0,
		         Macro11_Entry5_DelayMin, Macro11_Entry5_DelaySec, Macro11_Entry5_TimMin, Macro11_Entry5_TimSec, Macro11_Entry5_Protocol, 0, 0, 0, 0,
		         Macro11_Entry6_DelayMin, Macro11_Entry6_DelaySec, Macro11_Entry6_TimMin, Macro11_Entry6_TimSec, Macro11_Entry6_Protocol, 0, 0, 0, 0,
		         Macro11_Entry7_DelayMin, Macro11_Entry7_DelaySec, Macro11_Entry7_TimMin, Macro11_Entry7_TimSec, Macro11_Entry7_Protocol, 0, 0, 0, 0,
		         Macro11_Entry8_DelayMin, Macro11_Entry8_DelaySec, Macro11_Entry8_TimMin, Macro11_Entry8_TimSec, Macro11_Entry8_Protocol, 0, 0, 0, 0,
		         Macro11_Entry9_DelayMin, Macro11_Entry9_DelaySec, Macro11_Entry9_TimMin, Macro11_Entry9_TimSec, Macro11_Entry9_Protocol, 0, 0, 0, 0,
		         Macro11_Entry10_DelayMin, Macro11_Entry10_DelaySec, Macro11_Entry10_TimMin, Macro11_Entry10_TimSec, Macro11_Entry10_Protocol, 0, 0, 0, 0,
		         Macro11_Entry11_DelayMin, Macro11_Entry11_DelaySec, Macro11_Entry11_TimMin, Macro11_Entry11_TimSec, Macro11_Entry11_Protocol, 0, 0, 0, 0,
		         Macro11_Entry12_DelayMin, Macro11_Entry12_DelaySec, Macro11_Entry12_TimMin, Macro11_Entry12_TimSec, Macro11_Entry12_Protocol, 0, 0, 0, 0,
		         Macro11_Entry13_DelayMin, Macro11_Entry13_DelaySec, Macro11_Entry13_TimMin, Macro11_Entry13_TimSec, Macro11_Entry13_Protocol, 0, 0, 0, 0,
		         Macro11_Entry14_DelayMin, Macro11_Entry14_DelaySec, Macro11_Entry14_TimMin, Macro11_Entry14_TimSec, Macro11_Entry14_Protocol, 0, 0, 0, 0,
		         Macro11_Entry15_DelayMin, Macro11_Entry15_DelaySec, Macro11_Entry15_TimMin, Macro11_Entry15_TimSec, Macro11_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR11_STRING};

const struct super_macro Macro12 = {Macro12_NumEntries,
		         Macro12_Entry1_DelayMin, Macro12_Entry1_DelaySec, Macro12_Entry1_TimMin, Macro12_Entry1_TimSec, Macro12_Entry1_Protocol, 0, 0, 0, 0,
		         Macro12_Entry2_DelayMin, Macro12_Entry2_DelaySec, Macro12_Entry2_TimMin, Macro12_Entry2_TimSec, Macro12_Entry2_Protocol, 0, 0, 0, 0,
		         Macro12_Entry3_DelayMin, Macro12_Entry3_DelaySec, Macro12_Entry3_TimMin, Macro12_Entry3_TimSec, Macro12_Entry3_Protocol, 0, 0, 0, 0,
		         Macro12_Entry4_DelayMin, Macro12_Entry4_DelaySec, Macro12_Entry4_TimMin, Macro12_Entry4_TimSec, Macro12_Entry4_Protocol, 0, 0, 0, 0,
		         Macro12_Entry5_DelayMin, Macro12_Entry5_DelaySec, Macro12_Entry5_TimMin, Macro12_Entry5_TimSec, Macro12_Entry5_Protocol, 0, 0, 0, 0,
		         Macro12_Entry6_DelayMin, Macro12_Entry6_DelaySec, Macro12_Entry6_TimMin, Macro12_Entry6_TimSec, Macro12_Entry6_Protocol, 0, 0, 0, 0,
		         Macro12_Entry7_DelayMin, Macro12_Entry7_DelaySec, Macro12_Entry7_TimMin, Macro12_Entry7_TimSec, Macro12_Entry7_Protocol, 0, 0, 0, 0,
		         Macro12_Entry8_DelayMin, Macro12_Entry8_DelaySec, Macro12_Entry8_TimMin, Macro12_Entry8_TimSec, Macro12_Entry8_Protocol, 0, 0, 0, 0,
		         Macro12_Entry9_DelayMin, Macro12_Entry9_DelaySec, Macro12_Entry9_TimMin, Macro12_Entry9_TimSec, Macro12_Entry9_Protocol, 0, 0, 0, 0,
		         Macro12_Entry10_DelayMin, Macro12_Entry10_DelaySec, Macro12_Entry10_TimMin, Macro12_Entry10_TimSec, Macro12_Entry10_Protocol, 0, 0, 0, 0,
		         Macro12_Entry11_DelayMin, Macro12_Entry11_DelaySec, Macro12_Entry11_TimMin, Macro12_Entry11_TimSec, Macro12_Entry11_Protocol, 0, 0, 0, 0,
		         Macro12_Entry12_DelayMin, Macro12_Entry12_DelaySec, Macro12_Entry12_TimMin, Macro12_Entry12_TimSec, Macro12_Entry12_Protocol, 0, 0, 0, 0,
		         Macro12_Entry13_DelayMin, Macro12_Entry13_DelaySec, Macro12_Entry13_TimMin, Macro12_Entry13_TimSec, Macro12_Entry13_Protocol, 0, 0, 0, 0,
		         Macro12_Entry14_DelayMin, Macro12_Entry14_DelaySec, Macro12_Entry14_TimMin, Macro12_Entry14_TimSec, Macro12_Entry14_Protocol, 0, 0, 0, 0,
		         Macro12_Entry15_DelayMin, Macro12_Entry15_DelaySec, Macro12_Entry15_TimMin, Macro12_Entry15_TimSec, Macro12_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR12_STRING};

const struct super_macro Macro13 = {Macro13_NumEntries,
		         Macro13_Entry1_DelayMin, Macro13_Entry1_DelaySec, Macro13_Entry1_TimMin, Macro13_Entry1_TimSec, Macro13_Entry1_Protocol, 0, 0, 0, 0,
		         Macro13_Entry2_DelayMin, Macro13_Entry2_DelaySec, Macro13_Entry2_TimMin, Macro13_Entry2_TimSec, Macro13_Entry2_Protocol, 0, 0, 0, 0,
		         Macro13_Entry3_DelayMin, Macro13_Entry3_DelaySec, Macro13_Entry3_TimMin, Macro13_Entry3_TimSec, Macro13_Entry3_Protocol, 0, 0, 0, 0,
		         Macro13_Entry4_DelayMin, Macro13_Entry4_DelaySec, Macro13_Entry4_TimMin, Macro13_Entry4_TimSec, Macro13_Entry4_Protocol, 0, 0, 0, 0,
		         Macro13_Entry5_DelayMin, Macro13_Entry5_DelaySec, Macro13_Entry5_TimMin, Macro13_Entry5_TimSec, Macro13_Entry5_Protocol, 0, 0, 0, 0,
		         Macro13_Entry6_DelayMin, Macro13_Entry6_DelaySec, Macro13_Entry6_TimMin, Macro13_Entry6_TimSec, Macro13_Entry6_Protocol, 0, 0, 0, 0,
		         Macro13_Entry7_DelayMin, Macro13_Entry7_DelaySec, Macro13_Entry7_TimMin, Macro13_Entry7_TimSec, Macro13_Entry7_Protocol, 0, 0, 0, 0,
		         Macro13_Entry8_DelayMin, Macro13_Entry8_DelaySec, Macro13_Entry8_TimMin, Macro13_Entry8_TimSec, Macro13_Entry8_Protocol, 0, 0, 0, 0,
		         Macro13_Entry9_DelayMin, Macro13_Entry9_DelaySec, Macro13_Entry9_TimMin, Macro13_Entry9_TimSec, Macro13_Entry9_Protocol, 0, 0, 0, 0,
		         Macro13_Entry10_DelayMin, Macro13_Entry10_DelaySec, Macro13_Entry10_TimMin, Macro13_Entry10_TimSec, Macro13_Entry10_Protocol, 0, 0, 0, 0,
		         Macro13_Entry11_DelayMin, Macro13_Entry11_DelaySec, Macro13_Entry11_TimMin, Macro13_Entry11_TimSec, Macro13_Entry11_Protocol, 0, 0, 0, 0,
		         Macro13_Entry12_DelayMin, Macro13_Entry12_DelaySec, Macro13_Entry12_TimMin, Macro13_Entry12_TimSec, Macro13_Entry12_Protocol, 0, 0, 0, 0,
		         Macro13_Entry13_DelayMin, Macro13_Entry13_DelaySec, Macro13_Entry13_TimMin, Macro13_Entry13_TimSec, Macro13_Entry13_Protocol, 0, 0, 0, 0,
		         Macro13_Entry14_DelayMin, Macro13_Entry14_DelaySec, Macro13_Entry14_TimMin, Macro13_Entry14_TimSec, Macro13_Entry14_Protocol, 0, 0, 0, 0,
		         Macro13_Entry15_DelayMin, Macro13_Entry15_DelaySec, Macro13_Entry15_TimMin, Macro13_Entry15_TimSec, Macro13_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR13_STRING};

const struct super_macro Macro14 = {Macro14_NumEntries,
		         Macro14_Entry1_DelayMin, Macro14_Entry1_DelaySec, Macro14_Entry1_TimMin, Macro14_Entry1_TimSec, Macro14_Entry1_Protocol, 0, 0, 0, 0,
		         Macro14_Entry2_DelayMin, Macro14_Entry2_DelaySec, Macro14_Entry2_TimMin, Macro14_Entry2_TimSec, Macro14_Entry2_Protocol, 0, 0, 0, 0,
		         Macro14_Entry3_DelayMin, Macro14_Entry3_DelaySec, Macro14_Entry3_TimMin, Macro14_Entry3_TimSec, Macro14_Entry3_Protocol, 0, 0, 0, 0,
		         Macro14_Entry4_DelayMin, Macro14_Entry4_DelaySec, Macro14_Entry4_TimMin, Macro14_Entry4_TimSec, Macro14_Entry4_Protocol, 0, 0, 0, 0,
		         Macro14_Entry5_DelayMin, Macro14_Entry5_DelaySec, Macro14_Entry5_TimMin, Macro14_Entry5_TimSec, Macro14_Entry5_Protocol, 0, 0, 0, 0,
		         Macro14_Entry6_DelayMin, Macro14_Entry6_DelaySec, Macro14_Entry6_TimMin, Macro14_Entry6_TimSec, Macro14_Entry6_Protocol, 0, 0, 0, 0,
		         Macro14_Entry7_DelayMin, Macro14_Entry7_DelaySec, Macro14_Entry7_TimMin, Macro14_Entry7_TimSec, Macro14_Entry7_Protocol, 0, 0, 0, 0,
		         Macro14_Entry8_DelayMin, Macro14_Entry8_DelaySec, Macro14_Entry8_TimMin, Macro14_Entry8_TimSec, Macro14_Entry8_Protocol, 0, 0, 0, 0,
		         Macro14_Entry9_DelayMin, Macro14_Entry9_DelaySec, Macro14_Entry9_TimMin, Macro14_Entry9_TimSec, Macro14_Entry9_Protocol, 0, 0, 0, 0,
		         Macro14_Entry10_DelayMin, Macro14_Entry10_DelaySec, Macro14_Entry10_TimMin, Macro14_Entry10_TimSec, Macro14_Entry10_Protocol, 0, 0, 0, 0,
		         Macro14_Entry11_DelayMin, Macro14_Entry11_DelaySec, Macro14_Entry11_TimMin, Macro14_Entry11_TimSec, Macro14_Entry11_Protocol, 0, 0, 0, 0,
		         Macro14_Entry12_DelayMin, Macro14_Entry12_DelaySec, Macro14_Entry12_TimMin, Macro14_Entry12_TimSec, Macro14_Entry12_Protocol, 0, 0, 0, 0,
		         Macro14_Entry13_DelayMin, Macro14_Entry13_DelaySec, Macro14_Entry13_TimMin, Macro14_Entry13_TimSec, Macro14_Entry13_Protocol, 0, 0, 0, 0,
		         Macro14_Entry14_DelayMin, Macro14_Entry14_DelaySec, Macro14_Entry14_TimMin, Macro14_Entry14_TimSec, Macro14_Entry14_Protocol, 0, 0, 0, 0,
		         Macro14_Entry15_DelayMin, Macro14_Entry15_DelaySec, Macro14_Entry15_TimMin, Macro14_Entry15_TimSec, Macro14_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR14_STRING};

const struct super_macro Macro15 = {Macro15_NumEntries,
		         Macro15_Entry1_DelayMin, Macro15_Entry1_DelaySec, Macro15_Entry1_TimMin, Macro15_Entry1_TimSec, Macro15_Entry1_Protocol, 0, 0, 0, 0,
		         Macro15_Entry2_DelayMin, Macro15_Entry2_DelaySec, Macro15_Entry2_TimMin, Macro15_Entry2_TimSec, Macro15_Entry2_Protocol, 0, 0, 0, 0,
		         Macro15_Entry3_DelayMin, Macro15_Entry3_DelaySec, Macro15_Entry3_TimMin, Macro15_Entry3_TimSec, Macro15_Entry3_Protocol, 0, 0, 0, 0,
		         Macro15_Entry4_DelayMin, Macro15_Entry4_DelaySec, Macro15_Entry4_TimMin, Macro15_Entry4_TimSec, Macro15_Entry4_Protocol, 0, 0, 0, 0,
		         Macro15_Entry5_DelayMin, Macro15_Entry5_DelaySec, Macro15_Entry5_TimMin, Macro15_Entry5_TimSec, Macro15_Entry5_Protocol, 0, 0, 0, 0,
		         Macro15_Entry6_DelayMin, Macro15_Entry6_DelaySec, Macro15_Entry6_TimMin, Macro15_Entry6_TimSec, Macro15_Entry6_Protocol, 0, 0, 0, 0,
		         Macro15_Entry7_DelayMin, Macro15_Entry7_DelaySec, Macro15_Entry7_TimMin, Macro15_Entry7_TimSec, Macro15_Entry7_Protocol, 0, 0, 0, 0,
		         Macro15_Entry8_DelayMin, Macro15_Entry8_DelaySec, Macro15_Entry8_TimMin, Macro15_Entry8_TimSec, Macro15_Entry8_Protocol, 0, 0, 0, 0,
		         Macro15_Entry9_DelayMin, Macro15_Entry9_DelaySec, Macro15_Entry9_TimMin, Macro15_Entry9_TimSec, Macro15_Entry9_Protocol, 0, 0, 0, 0,
		         Macro15_Entry10_DelayMin, Macro15_Entry10_DelaySec, Macro15_Entry10_TimMin, Macro15_Entry10_TimSec, Macro15_Entry10_Protocol, 0, 0, 0, 0,
		         Macro15_Entry11_DelayMin, Macro15_Entry11_DelaySec, Macro15_Entry11_TimMin, Macro15_Entry11_TimSec, Macro15_Entry11_Protocol, 0, 0, 0, 0,
		         Macro15_Entry12_DelayMin, Macro15_Entry12_DelaySec, Macro15_Entry12_TimMin, Macro15_Entry12_TimSec, Macro15_Entry12_Protocol, 0, 0, 0, 0,
		         Macro15_Entry13_DelayMin, Macro15_Entry13_DelaySec, Macro15_Entry13_TimMin, Macro15_Entry13_TimSec, Macro15_Entry13_Protocol, 0, 0, 0, 0,
		         Macro15_Entry14_DelayMin, Macro15_Entry14_DelaySec, Macro15_Entry14_TimMin, Macro15_Entry14_TimSec, Macro15_Entry14_Protocol, 0, 0, 0, 0,
		         Macro15_Entry15_DelayMin, Macro15_Entry15_DelaySec, Macro15_Entry15_TimMin, Macro15_Entry15_TimSec, Macro15_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR15_STRING};

const struct super_macro Macro16 = {Macro16_NumEntries,
		         Macro16_Entry1_DelayMin, Macro16_Entry1_DelaySec, Macro16_Entry1_TimMin, Macro16_Entry1_TimSec, Macro16_Entry1_Protocol, 0, 0, 0, 0,
		         Macro16_Entry2_DelayMin, Macro16_Entry2_DelaySec, Macro16_Entry2_TimMin, Macro16_Entry2_TimSec, Macro16_Entry2_Protocol, 0, 0, 0, 0,
		         Macro16_Entry3_DelayMin, Macro16_Entry3_DelaySec, Macro16_Entry3_TimMin, Macro16_Entry3_TimSec, Macro16_Entry3_Protocol, 0, 0, 0, 0,
		         Macro16_Entry4_DelayMin, Macro16_Entry4_DelaySec, Macro16_Entry4_TimMin, Macro16_Entry4_TimSec, Macro16_Entry4_Protocol, 0, 0, 0, 0,
		         Macro16_Entry5_DelayMin, Macro16_Entry5_DelaySec, Macro16_Entry5_TimMin, Macro16_Entry5_TimSec, Macro16_Entry5_Protocol, 0, 0, 0, 0,
		         Macro16_Entry6_DelayMin, Macro16_Entry6_DelaySec, Macro16_Entry6_TimMin, Macro16_Entry6_TimSec, Macro16_Entry6_Protocol, 0, 0, 0, 0,
		         Macro16_Entry7_DelayMin, Macro16_Entry7_DelaySec, Macro16_Entry7_TimMin, Macro16_Entry7_TimSec, Macro16_Entry7_Protocol, 0, 0, 0, 0,
		         Macro16_Entry8_DelayMin, Macro16_Entry8_DelaySec, Macro16_Entry8_TimMin, Macro16_Entry8_TimSec, Macro16_Entry8_Protocol, 0, 0, 0, 0,
		         Macro16_Entry9_DelayMin, Macro16_Entry9_DelaySec, Macro16_Entry9_TimMin, Macro16_Entry9_TimSec, Macro16_Entry9_Protocol, 0, 0, 0, 0,
		         Macro16_Entry10_DelayMin, Macro16_Entry10_DelaySec, Macro16_Entry10_TimMin, Macro16_Entry10_TimSec, Macro16_Entry10_Protocol, 0, 0, 0, 0,
		         Macro16_Entry11_DelayMin, Macro16_Entry11_DelaySec, Macro16_Entry11_TimMin, Macro16_Entry11_TimSec, Macro16_Entry11_Protocol, 0, 0, 0, 0,
		         Macro16_Entry12_DelayMin, Macro16_Entry12_DelaySec, Macro16_Entry12_TimMin, Macro16_Entry12_TimSec, Macro16_Entry12_Protocol, 0, 0, 0, 0,
		         Macro16_Entry13_DelayMin, Macro16_Entry13_DelaySec, Macro16_Entry13_TimMin, Macro16_Entry13_TimSec, Macro16_Entry13_Protocol, 0, 0, 0, 0,
		         Macro16_Entry14_DelayMin, Macro16_Entry14_DelaySec, Macro16_Entry14_TimMin, Macro16_Entry14_TimSec, Macro16_Entry14_Protocol, 0, 0, 0, 0,
		         Macro16_Entry15_DelayMin, Macro16_Entry15_DelaySec, Macro16_Entry15_TimMin, Macro16_Entry15_TimSec, Macro16_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR16_STRING};

const struct super_macro Macro17 = {Macro17_NumEntries,
		         Macro17_Entry1_DelayMin, Macro17_Entry1_DelaySec, Macro17_Entry1_TimMin, Macro17_Entry1_TimSec, Macro17_Entry1_Protocol, 0, 0, 0, 0,
		         Macro17_Entry2_DelayMin, Macro17_Entry2_DelaySec, Macro17_Entry2_TimMin, Macro17_Entry2_TimSec, Macro17_Entry2_Protocol, 0, 0, 0, 0,
		         Macro17_Entry3_DelayMin, Macro17_Entry3_DelaySec, Macro17_Entry3_TimMin, Macro17_Entry3_TimSec, Macro17_Entry3_Protocol, 0, 0, 0, 0,
		         Macro17_Entry4_DelayMin, Macro17_Entry4_DelaySec, Macro17_Entry4_TimMin, Macro17_Entry4_TimSec, Macro17_Entry4_Protocol, 0, 0, 0, 0,
		         Macro17_Entry5_DelayMin, Macro17_Entry5_DelaySec, Macro17_Entry5_TimMin, Macro17_Entry5_TimSec, Macro17_Entry5_Protocol, 0, 0, 0, 0,
		         Macro17_Entry6_DelayMin, Macro17_Entry6_DelaySec, Macro17_Entry6_TimMin, Macro17_Entry6_TimSec, Macro17_Entry6_Protocol, 0, 0, 0, 0,
		         Macro17_Entry7_DelayMin, Macro17_Entry7_DelaySec, Macro17_Entry7_TimMin, Macro17_Entry7_TimSec, Macro17_Entry7_Protocol, 0, 0, 0, 0,
		         Macro17_Entry8_DelayMin, Macro17_Entry8_DelaySec, Macro17_Entry8_TimMin, Macro17_Entry8_TimSec, Macro17_Entry8_Protocol, 0, 0, 0, 0,
		         Macro17_Entry9_DelayMin, Macro17_Entry9_DelaySec, Macro17_Entry9_TimMin, Macro17_Entry9_TimSec, Macro17_Entry9_Protocol, 0, 0, 0, 0,
		         Macro17_Entry10_DelayMin, Macro17_Entry10_DelaySec, Macro17_Entry10_TimMin, Macro17_Entry10_TimSec, Macro17_Entry10_Protocol, 0, 0, 0, 0,
		         Macro17_Entry11_DelayMin, Macro17_Entry11_DelaySec, Macro17_Entry11_TimMin, Macro17_Entry11_TimSec, Macro17_Entry11_Protocol, 0, 0, 0, 0,
		         Macro17_Entry12_DelayMin, Macro17_Entry12_DelaySec, Macro17_Entry12_TimMin, Macro17_Entry12_TimSec, Macro17_Entry12_Protocol, 0, 0, 0, 0,
		         Macro17_Entry13_DelayMin, Macro17_Entry13_DelaySec, Macro17_Entry13_TimMin, Macro17_Entry13_TimSec, Macro17_Entry13_Protocol, 0, 0, 0, 0,
		         Macro17_Entry14_DelayMin, Macro17_Entry14_DelaySec, Macro17_Entry14_TimMin, Macro17_Entry14_TimSec, Macro17_Entry14_Protocol, 0, 0, 0, 0,
		         Macro17_Entry15_DelayMin, Macro17_Entry15_DelaySec, Macro17_Entry15_TimMin, Macro17_Entry15_TimSec, Macro17_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR17_STRING};

const struct super_macro Macro18 = {Macro18_NumEntries,
		         Macro18_Entry1_DelayMin, Macro18_Entry1_DelaySec, Macro18_Entry1_TimMin, Macro18_Entry1_TimSec, Macro18_Entry1_Protocol, 0, 0, 0, 0,
		         Macro18_Entry2_DelayMin, Macro18_Entry2_DelaySec, Macro18_Entry2_TimMin, Macro18_Entry2_TimSec, Macro18_Entry2_Protocol, 0, 0, 0, 0,
		         Macro18_Entry3_DelayMin, Macro18_Entry3_DelaySec, Macro18_Entry3_TimMin, Macro18_Entry3_TimSec, Macro18_Entry3_Protocol, 0, 0, 0, 0,
		         Macro18_Entry4_DelayMin, Macro18_Entry4_DelaySec, Macro18_Entry4_TimMin, Macro18_Entry4_TimSec, Macro18_Entry4_Protocol, 0, 0, 0, 0,
		         Macro18_Entry5_DelayMin, Macro18_Entry5_DelaySec, Macro18_Entry5_TimMin, Macro18_Entry5_TimSec, Macro18_Entry5_Protocol, 0, 0, 0, 0,
		         Macro18_Entry6_DelayMin, Macro18_Entry6_DelaySec, Macro18_Entry6_TimMin, Macro18_Entry6_TimSec, Macro18_Entry6_Protocol, 0, 0, 0, 0,
		         Macro18_Entry7_DelayMin, Macro18_Entry7_DelaySec, Macro18_Entry7_TimMin, Macro18_Entry7_TimSec, Macro18_Entry7_Protocol, 0, 0, 0, 0,
		         Macro18_Entry8_DelayMin, Macro18_Entry8_DelaySec, Macro18_Entry8_TimMin, Macro18_Entry8_TimSec, Macro18_Entry8_Protocol, 0, 0, 0, 0,
		         Macro18_Entry9_DelayMin, Macro18_Entry9_DelaySec, Macro18_Entry9_TimMin, Macro18_Entry9_TimSec, Macro18_Entry9_Protocol, 0, 0, 0, 0,
		         Macro18_Entry10_DelayMin, Macro18_Entry10_DelaySec, Macro18_Entry10_TimMin, Macro18_Entry10_TimSec, Macro18_Entry10_Protocol, 0, 0, 0, 0,
		         Macro18_Entry11_DelayMin, Macro18_Entry11_DelaySec, Macro18_Entry11_TimMin, Macro18_Entry11_TimSec, Macro18_Entry11_Protocol, 0, 0, 0, 0,
		         Macro18_Entry12_DelayMin, Macro18_Entry12_DelaySec, Macro18_Entry12_TimMin, Macro18_Entry12_TimSec, Macro18_Entry12_Protocol, 0, 0, 0, 0,
		         Macro18_Entry13_DelayMin, Macro18_Entry13_DelaySec, Macro18_Entry13_TimMin, Macro18_Entry13_TimSec, Macro18_Entry13_Protocol, 0, 0, 0, 0,
		         Macro18_Entry14_DelayMin, Macro18_Entry14_DelaySec, Macro18_Entry14_TimMin, Macro18_Entry14_TimSec, Macro18_Entry14_Protocol, 0, 0, 0, 0,
		         Macro18_Entry15_DelayMin, Macro18_Entry15_DelaySec, Macro18_Entry15_TimMin, Macro18_Entry15_TimSec, Macro18_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR18_STRING};

const struct super_macro Macro19 = {Macro19_NumEntries,
		         Macro19_Entry1_DelayMin, Macro19_Entry1_DelaySec, Macro19_Entry1_TimMin, Macro19_Entry1_TimSec, Macro19_Entry1_Protocol, 0, 0, 0, 0,
		         Macro19_Entry2_DelayMin, Macro19_Entry2_DelaySec, Macro19_Entry2_TimMin, Macro19_Entry2_TimSec, Macro19_Entry2_Protocol, 0, 0, 0, 0,
		         Macro19_Entry3_DelayMin, Macro19_Entry3_DelaySec, Macro19_Entry3_TimMin, Macro19_Entry3_TimSec, Macro19_Entry3_Protocol, 0, 0, 0, 0,
		         Macro19_Entry4_DelayMin, Macro19_Entry4_DelaySec, Macro19_Entry4_TimMin, Macro19_Entry4_TimSec, Macro19_Entry4_Protocol, 0, 0, 0, 0,
		         Macro19_Entry5_DelayMin, Macro19_Entry5_DelaySec, Macro19_Entry5_TimMin, Macro19_Entry5_TimSec, Macro19_Entry5_Protocol, 0, 0, 0, 0,
		         Macro19_Entry6_DelayMin, Macro19_Entry6_DelaySec, Macro19_Entry6_TimMin, Macro19_Entry6_TimSec, Macro19_Entry6_Protocol, 0, 0, 0, 0,
		         Macro19_Entry7_DelayMin, Macro19_Entry7_DelaySec, Macro19_Entry7_TimMin, Macro19_Entry7_TimSec, Macro19_Entry7_Protocol, 0, 0, 0, 0,
		         Macro19_Entry8_DelayMin, Macro19_Entry8_DelaySec, Macro19_Entry8_TimMin, Macro19_Entry8_TimSec, Macro19_Entry8_Protocol, 0, 0, 0, 0,
		         Macro19_Entry9_DelayMin, Macro19_Entry9_DelaySec, Macro19_Entry9_TimMin, Macro19_Entry9_TimSec, Macro19_Entry9_Protocol, 0, 0, 0, 0,
		         Macro19_Entry10_DelayMin, Macro19_Entry10_DelaySec, Macro19_Entry10_TimMin, Macro19_Entry10_TimSec, Macro19_Entry10_Protocol, 0, 0, 0, 0,
		         Macro19_Entry11_DelayMin, Macro19_Entry11_DelaySec, Macro19_Entry11_TimMin, Macro19_Entry11_TimSec, Macro19_Entry11_Protocol, 0, 0, 0, 0,
		         Macro19_Entry12_DelayMin, Macro19_Entry12_DelaySec, Macro19_Entry12_TimMin, Macro19_Entry12_TimSec, Macro19_Entry12_Protocol, 0, 0, 0, 0,
		         Macro19_Entry13_DelayMin, Macro19_Entry13_DelaySec, Macro19_Entry13_TimMin, Macro19_Entry13_TimSec, Macro19_Entry13_Protocol, 0, 0, 0, 0,
		         Macro19_Entry14_DelayMin, Macro19_Entry14_DelaySec, Macro19_Entry14_TimMin, Macro19_Entry14_TimSec, Macro19_Entry14_Protocol, 0, 0, 0, 0,
		         Macro19_Entry15_DelayMin, Macro19_Entry15_DelaySec, Macro19_Entry15_TimMin, Macro19_Entry15_TimSec, Macro19_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR19_STRING};

const struct super_macro Macro20 = {Macro20_NumEntries,
		         Macro20_Entry1_DelayMin, Macro20_Entry1_DelaySec, Macro20_Entry1_TimMin, Macro20_Entry1_TimSec, Macro20_Entry1_Protocol, 0, 0, 0, 0,
		         Macro20_Entry2_DelayMin, Macro20_Entry2_DelaySec, Macro20_Entry2_TimMin, Macro20_Entry2_TimSec, Macro20_Entry2_Protocol, 0, 0, 0, 0,
		         Macro20_Entry3_DelayMin, Macro20_Entry3_DelaySec, Macro20_Entry3_TimMin, Macro20_Entry3_TimSec, Macro20_Entry3_Protocol, 0, 0, 0, 0,
		         Macro20_Entry4_DelayMin, Macro20_Entry4_DelaySec, Macro20_Entry4_TimMin, Macro20_Entry4_TimSec, Macro20_Entry4_Protocol, 0, 0, 0, 0,
		         Macro20_Entry5_DelayMin, Macro20_Entry5_DelaySec, Macro20_Entry5_TimMin, Macro20_Entry5_TimSec, Macro20_Entry5_Protocol, 0, 0, 0, 0,
		         Macro20_Entry6_DelayMin, Macro20_Entry6_DelaySec, Macro20_Entry6_TimMin, Macro20_Entry6_TimSec, Macro20_Entry6_Protocol, 0, 0, 0, 0,
		         Macro20_Entry7_DelayMin, Macro20_Entry7_DelaySec, Macro20_Entry7_TimMin, Macro20_Entry7_TimSec, Macro20_Entry7_Protocol, 0, 0, 0, 0,
		         Macro20_Entry8_DelayMin, Macro20_Entry8_DelaySec, Macro20_Entry8_TimMin, Macro20_Entry8_TimSec, Macro20_Entry8_Protocol, 0, 0, 0, 0,
		         Macro20_Entry9_DelayMin, Macro20_Entry9_DelaySec, Macro20_Entry9_TimMin, Macro20_Entry9_TimSec, Macro20_Entry9_Protocol, 0, 0, 0, 0,
		         Macro20_Entry10_DelayMin, Macro20_Entry10_DelaySec, Macro20_Entry10_TimMin, Macro20_Entry10_TimSec, Macro20_Entry10_Protocol, 0, 0, 0, 0,
		         Macro20_Entry11_DelayMin, Macro20_Entry11_DelaySec, Macro20_Entry11_TimMin, Macro20_Entry11_TimSec, Macro20_Entry11_Protocol, 0, 0, 0, 0,
		         Macro20_Entry12_DelayMin, Macro20_Entry12_DelaySec, Macro20_Entry12_TimMin, Macro20_Entry12_TimSec, Macro20_Entry12_Protocol, 0, 0, 0, 0,
		         Macro20_Entry13_DelayMin, Macro20_Entry13_DelaySec, Macro20_Entry13_TimMin, Macro20_Entry13_TimSec, Macro20_Entry13_Protocol, 0, 0, 0, 0,
		         Macro20_Entry14_DelayMin, Macro20_Entry14_DelaySec, Macro20_Entry14_TimMin, Macro20_Entry14_TimSec, Macro20_Entry14_Protocol, 0, 0, 0, 0,
		         Macro20_Entry15_DelayMin, Macro20_Entry15_DelaySec, Macro20_Entry15_TimMin, Macro20_Entry15_TimSec, Macro20_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR20_STRING};

const struct super_macro Macro21 = {Macro21_NumEntries,
		         Macro21_Entry1_DelayMin, Macro21_Entry1_DelaySec, Macro21_Entry1_TimMin, Macro21_Entry1_TimSec, Macro21_Entry1_Protocol, 0, 0, 0, 0,
		         Macro21_Entry2_DelayMin, Macro21_Entry2_DelaySec, Macro21_Entry2_TimMin, Macro21_Entry2_TimSec, Macro21_Entry2_Protocol, 0, 0, 0, 0,
		         Macro21_Entry3_DelayMin, Macro21_Entry3_DelaySec, Macro21_Entry3_TimMin, Macro21_Entry3_TimSec, Macro21_Entry3_Protocol, 0, 0, 0, 0,
		         Macro21_Entry4_DelayMin, Macro21_Entry4_DelaySec, Macro21_Entry4_TimMin, Macro21_Entry4_TimSec, Macro21_Entry4_Protocol, 0, 0, 0, 0,
		         Macro21_Entry5_DelayMin, Macro21_Entry5_DelaySec, Macro21_Entry5_TimMin, Macro21_Entry5_TimSec, Macro21_Entry5_Protocol, 0, 0, 0, 0,
		         Macro21_Entry6_DelayMin, Macro21_Entry6_DelaySec, Macro21_Entry6_TimMin, Macro21_Entry6_TimSec, Macro21_Entry6_Protocol, 0, 0, 0, 0,
		         Macro21_Entry7_DelayMin, Macro21_Entry7_DelaySec, Macro21_Entry7_TimMin, Macro21_Entry7_TimSec, Macro21_Entry7_Protocol, 0, 0, 0, 0,
		         Macro21_Entry8_DelayMin, Macro21_Entry8_DelaySec, Macro21_Entry8_TimMin, Macro21_Entry8_TimSec, Macro21_Entry8_Protocol, 0, 0, 0, 0,
		         Macro21_Entry9_DelayMin, Macro21_Entry9_DelaySec, Macro21_Entry9_TimMin, Macro21_Entry9_TimSec, Macro21_Entry9_Protocol, 0, 0, 0, 0,
		         Macro21_Entry10_DelayMin, Macro21_Entry10_DelaySec, Macro21_Entry10_TimMin, Macro21_Entry10_TimSec, Macro21_Entry10_Protocol, 0, 0, 0, 0,
		         Macro21_Entry11_DelayMin, Macro21_Entry11_DelaySec, Macro21_Entry11_TimMin, Macro21_Entry11_TimSec, Macro21_Entry11_Protocol, 0, 0, 0, 0,
		         Macro21_Entry12_DelayMin, Macro21_Entry12_DelaySec, Macro21_Entry12_TimMin, Macro21_Entry12_TimSec, Macro21_Entry12_Protocol, 0, 0, 0, 0,
		         Macro21_Entry13_DelayMin, Macro21_Entry13_DelaySec, Macro21_Entry13_TimMin, Macro21_Entry13_TimSec, Macro21_Entry13_Protocol, 0, 0, 0, 0,
		         Macro21_Entry14_DelayMin, Macro21_Entry14_DelaySec, Macro21_Entry14_TimMin, Macro21_Entry14_TimSec, Macro21_Entry14_Protocol, 0, 0, 0, 0,
		         Macro21_Entry15_DelayMin, Macro21_Entry15_DelaySec, Macro21_Entry15_TimMin, Macro21_Entry15_TimSec, Macro21_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR21_STRING};

const struct super_macro Macro22 = {Macro22_NumEntries,
		         Macro22_Entry1_DelayMin, Macro22_Entry1_DelaySec, Macro22_Entry1_TimMin, Macro22_Entry1_TimSec, Macro22_Entry1_Protocol, 0, 0, 0, 0,
		         Macro22_Entry2_DelayMin, Macro22_Entry2_DelaySec, Macro22_Entry2_TimMin, Macro22_Entry2_TimSec, Macro22_Entry2_Protocol, 0, 0, 0, 0,
		         Macro22_Entry3_DelayMin, Macro22_Entry3_DelaySec, Macro22_Entry3_TimMin, Macro22_Entry3_TimSec, Macro22_Entry3_Protocol, 0, 0, 0, 0,
		         Macro22_Entry4_DelayMin, Macro22_Entry4_DelaySec, Macro22_Entry4_TimMin, Macro22_Entry4_TimSec, Macro22_Entry4_Protocol, 0, 0, 0, 0,
		         Macro22_Entry5_DelayMin, Macro22_Entry5_DelaySec, Macro22_Entry5_TimMin, Macro22_Entry5_TimSec, Macro22_Entry5_Protocol, 0, 0, 0, 0,
		         Macro22_Entry6_DelayMin, Macro22_Entry6_DelaySec, Macro22_Entry6_TimMin, Macro22_Entry6_TimSec, Macro22_Entry6_Protocol, 0, 0, 0, 0,
		         Macro22_Entry7_DelayMin, Macro22_Entry7_DelaySec, Macro22_Entry7_TimMin, Macro22_Entry7_TimSec, Macro22_Entry7_Protocol, 0, 0, 0, 0,
		         Macro22_Entry8_DelayMin, Macro22_Entry8_DelaySec, Macro22_Entry8_TimMin, Macro22_Entry8_TimSec, Macro22_Entry8_Protocol, 0, 0, 0, 0,
		         Macro22_Entry9_DelayMin, Macro22_Entry9_DelaySec, Macro22_Entry9_TimMin, Macro22_Entry9_TimSec, Macro22_Entry9_Protocol, 0, 0, 0, 0,
		         Macro22_Entry10_DelayMin, Macro22_Entry10_DelaySec, Macro22_Entry10_TimMin, Macro22_Entry10_TimSec, Macro22_Entry10_Protocol, 0, 0, 0, 0,
		         Macro22_Entry11_DelayMin, Macro22_Entry11_DelaySec, Macro22_Entry11_TimMin, Macro22_Entry11_TimSec, Macro22_Entry11_Protocol, 0, 0, 0, 0,
		         Macro22_Entry12_DelayMin, Macro22_Entry12_DelaySec, Macro22_Entry12_TimMin, Macro22_Entry12_TimSec, Macro22_Entry12_Protocol, 0, 0, 0, 0,
		         Macro22_Entry13_DelayMin, Macro22_Entry13_DelaySec, Macro22_Entry13_TimMin, Macro22_Entry13_TimSec, Macro22_Entry13_Protocol, 0, 0, 0, 0,
		         Macro22_Entry14_DelayMin, Macro22_Entry14_DelaySec, Macro22_Entry14_TimMin, Macro22_Entry14_TimSec, Macro22_Entry14_Protocol, 0, 0, 0, 0,
		         Macro22_Entry15_DelayMin, Macro22_Entry15_DelaySec, Macro22_Entry15_TimMin, Macro22_Entry15_TimSec, Macro22_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR22_STRING};

const struct super_macro Macro23 = {Macro23_NumEntries,
		         Macro23_Entry1_DelayMin, Macro23_Entry1_DelaySec, Macro23_Entry1_TimMin, Macro23_Entry1_TimSec, Macro23_Entry1_Protocol, 0, 0, 0, 0,
		         Macro23_Entry2_DelayMin, Macro23_Entry2_DelaySec, Macro23_Entry2_TimMin, Macro23_Entry2_TimSec, Macro23_Entry2_Protocol, 0, 0, 0, 0,
		         Macro23_Entry3_DelayMin, Macro23_Entry3_DelaySec, Macro23_Entry3_TimMin, Macro23_Entry3_TimSec, Macro23_Entry3_Protocol, 0, 0, 0, 0,
		         Macro23_Entry4_DelayMin, Macro23_Entry4_DelaySec, Macro23_Entry4_TimMin, Macro23_Entry4_TimSec, Macro23_Entry4_Protocol, 0, 0, 0, 0,
		         Macro23_Entry5_DelayMin, Macro23_Entry5_DelaySec, Macro23_Entry5_TimMin, Macro23_Entry5_TimSec, Macro23_Entry5_Protocol, 0, 0, 0, 0,
		         Macro23_Entry6_DelayMin, Macro23_Entry6_DelaySec, Macro23_Entry6_TimMin, Macro23_Entry6_TimSec, Macro23_Entry6_Protocol, 0, 0, 0, 0,
		         Macro23_Entry7_DelayMin, Macro23_Entry7_DelaySec, Macro23_Entry7_TimMin, Macro23_Entry7_TimSec, Macro23_Entry7_Protocol, 0, 0, 0, 0,
		         Macro23_Entry8_DelayMin, Macro23_Entry8_DelaySec, Macro23_Entry8_TimMin, Macro23_Entry8_TimSec, Macro23_Entry8_Protocol, 0, 0, 0, 0,
		         Macro23_Entry9_DelayMin, Macro23_Entry9_DelaySec, Macro23_Entry9_TimMin, Macro23_Entry9_TimSec, Macro23_Entry9_Protocol, 0, 0, 0, 0,
		         Macro23_Entry10_DelayMin, Macro23_Entry10_DelaySec, Macro23_Entry10_TimMin, Macro23_Entry10_TimSec, Macro23_Entry10_Protocol, 0, 0, 0, 0,
		         Macro23_Entry11_DelayMin, Macro23_Entry11_DelaySec, Macro23_Entry11_TimMin, Macro23_Entry11_TimSec, Macro23_Entry11_Protocol, 0, 0, 0, 0,
		         Macro23_Entry12_DelayMin, Macro23_Entry12_DelaySec, Macro23_Entry12_TimMin, Macro23_Entry12_TimSec, Macro23_Entry12_Protocol, 0, 0, 0, 0,
		         Macro23_Entry13_DelayMin, Macro23_Entry13_DelaySec, Macro23_Entry13_TimMin, Macro23_Entry13_TimSec, Macro23_Entry13_Protocol, 0, 0, 0, 0,
		         Macro23_Entry14_DelayMin, Macro23_Entry14_DelaySec, Macro23_Entry14_TimMin, Macro23_Entry14_TimSec, Macro23_Entry14_Protocol, 0, 0, 0, 0,
		         Macro23_Entry15_DelayMin, Macro23_Entry15_DelaySec, Macro23_Entry15_TimMin, Macro23_Entry15_TimSec, Macro23_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR23_STRING};

const struct super_macro Macro24 = {Macro24_NumEntries,
		         Macro24_Entry1_DelayMin, Macro24_Entry1_DelaySec, Macro24_Entry1_TimMin, Macro24_Entry1_TimSec, Macro24_Entry1_Protocol, 0, 0, 0, 0,
		         Macro24_Entry2_DelayMin, Macro24_Entry2_DelaySec, Macro24_Entry2_TimMin, Macro24_Entry2_TimSec, Macro24_Entry2_Protocol, 0, 0, 0, 0,
		         Macro24_Entry3_DelayMin, Macro24_Entry3_DelaySec, Macro24_Entry3_TimMin, Macro24_Entry3_TimSec, Macro24_Entry3_Protocol, 0, 0, 0, 0,
		         Macro24_Entry4_DelayMin, Macro24_Entry4_DelaySec, Macro24_Entry4_TimMin, Macro24_Entry4_TimSec, Macro24_Entry4_Protocol, 0, 0, 0, 0,
		         Macro24_Entry5_DelayMin, Macro24_Entry5_DelaySec, Macro24_Entry5_TimMin, Macro24_Entry5_TimSec, Macro24_Entry5_Protocol, 0, 0, 0, 0,
		         Macro24_Entry6_DelayMin, Macro24_Entry6_DelaySec, Macro24_Entry6_TimMin, Macro24_Entry6_TimSec, Macro24_Entry6_Protocol, 0, 0, 0, 0,
		         Macro24_Entry7_DelayMin, Macro24_Entry7_DelaySec, Macro24_Entry7_TimMin, Macro24_Entry7_TimSec, Macro24_Entry7_Protocol, 0, 0, 0, 0,
		         Macro24_Entry8_DelayMin, Macro24_Entry8_DelaySec, Macro24_Entry8_TimMin, Macro24_Entry8_TimSec, Macro24_Entry8_Protocol, 0, 0, 0, 0,
		         Macro24_Entry9_DelayMin, Macro24_Entry9_DelaySec, Macro24_Entry9_TimMin, Macro24_Entry9_TimSec, Macro24_Entry9_Protocol, 0, 0, 0, 0,
		         Macro24_Entry10_DelayMin, Macro24_Entry10_DelaySec, Macro24_Entry10_TimMin, Macro24_Entry10_TimSec, Macro24_Entry10_Protocol, 0, 0, 0, 0,
		         Macro24_Entry11_DelayMin, Macro24_Entry11_DelaySec, Macro24_Entry11_TimMin, Macro24_Entry11_TimSec, Macro24_Entry11_Protocol, 0, 0, 0, 0,
		         Macro24_Entry12_DelayMin, Macro24_Entry12_DelaySec, Macro24_Entry12_TimMin, Macro24_Entry12_TimSec, Macro24_Entry12_Protocol, 0, 0, 0, 0,
		         Macro24_Entry13_DelayMin, Macro24_Entry13_DelaySec, Macro24_Entry13_TimMin, Macro24_Entry13_TimSec, Macro24_Entry13_Protocol, 0, 0, 0, 0,
		         Macro24_Entry14_DelayMin, Macro24_Entry14_DelaySec, Macro24_Entry14_TimMin, Macro24_Entry14_TimSec, Macro24_Entry14_Protocol, 0, 0, 0, 0,
		         Macro24_Entry15_DelayMin, Macro24_Entry15_DelaySec, Macro24_Entry15_TimMin, Macro24_Entry15_TimSec, Macro24_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR24_STRING};

const struct super_macro Macro25 = {Macro25_NumEntries,
		         Macro25_Entry1_DelayMin, Macro25_Entry1_DelaySec, Macro25_Entry1_TimMin, Macro25_Entry1_TimSec, Macro25_Entry1_Protocol, 0, 0, 0, 0,
		         Macro25_Entry2_DelayMin, Macro25_Entry2_DelaySec, Macro25_Entry2_TimMin, Macro25_Entry2_TimSec, Macro25_Entry2_Protocol, 0, 0, 0, 0,
		         Macro25_Entry3_DelayMin, Macro25_Entry3_DelaySec, Macro25_Entry3_TimMin, Macro25_Entry3_TimSec, Macro25_Entry3_Protocol, 0, 0, 0, 0,
		         Macro25_Entry4_DelayMin, Macro25_Entry4_DelaySec, Macro25_Entry4_TimMin, Macro25_Entry4_TimSec, Macro25_Entry4_Protocol, 0, 0, 0, 0,
		         Macro25_Entry5_DelayMin, Macro25_Entry5_DelaySec, Macro25_Entry5_TimMin, Macro25_Entry5_TimSec, Macro25_Entry5_Protocol, 0, 0, 0, 0,
		         Macro25_Entry6_DelayMin, Macro25_Entry6_DelaySec, Macro25_Entry6_TimMin, Macro25_Entry6_TimSec, Macro25_Entry6_Protocol, 0, 0, 0, 0,
		         Macro25_Entry7_DelayMin, Macro25_Entry7_DelaySec, Macro25_Entry7_TimMin, Macro25_Entry7_TimSec, Macro25_Entry7_Protocol, 0, 0, 0, 0,
		         Macro25_Entry8_DelayMin, Macro25_Entry8_DelaySec, Macro25_Entry8_TimMin, Macro25_Entry8_TimSec, Macro25_Entry8_Protocol, 0, 0, 0, 0,
		         Macro25_Entry9_DelayMin, Macro25_Entry9_DelaySec, Macro25_Entry9_TimMin, Macro25_Entry9_TimSec, Macro25_Entry9_Protocol, 0, 0, 0, 0,
		         Macro25_Entry10_DelayMin, Macro25_Entry10_DelaySec, Macro25_Entry10_TimMin, Macro25_Entry10_TimSec, Macro25_Entry10_Protocol, 0, 0, 0, 0,
		         Macro25_Entry11_DelayMin, Macro25_Entry11_DelaySec, Macro25_Entry11_TimMin, Macro25_Entry11_TimSec, Macro25_Entry11_Protocol, 0, 0, 0, 0,
		         Macro25_Entry12_DelayMin, Macro25_Entry12_DelaySec, Macro25_Entry12_TimMin, Macro25_Entry12_TimSec, Macro25_Entry12_Protocol, 0, 0, 0, 0,
		         Macro25_Entry13_DelayMin, Macro25_Entry13_DelaySec, Macro25_Entry13_TimMin, Macro25_Entry13_TimSec, Macro25_Entry13_Protocol, 0, 0, 0, 0,
		         Macro25_Entry14_DelayMin, Macro25_Entry14_DelaySec, Macro25_Entry14_TimMin, Macro25_Entry14_TimSec, Macro25_Entry14_Protocol, 0, 0, 0, 0,
		         Macro25_Entry15_DelayMin, Macro25_Entry15_DelaySec, Macro25_Entry15_TimMin, Macro25_Entry15_TimSec, Macro25_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR25_STRING};

const struct super_macro Macro26 = {Macro26_NumEntries,
		         Macro26_Entry1_DelayMin, Macro26_Entry1_DelaySec, Macro26_Entry1_TimMin, Macro26_Entry1_TimSec, Macro26_Entry1_Protocol, 0, 0, 0, 0,
		         Macro26_Entry2_DelayMin, Macro26_Entry2_DelaySec, Macro26_Entry2_TimMin, Macro26_Entry2_TimSec, Macro26_Entry2_Protocol, 0, 0, 0, 0,
		         Macro26_Entry3_DelayMin, Macro26_Entry3_DelaySec, Macro26_Entry3_TimMin, Macro26_Entry3_TimSec, Macro26_Entry3_Protocol, 0, 0, 0, 0,
		         Macro26_Entry4_DelayMin, Macro26_Entry4_DelaySec, Macro26_Entry4_TimMin, Macro26_Entry4_TimSec, Macro26_Entry4_Protocol, 0, 0, 0, 0,
		         Macro26_Entry5_DelayMin, Macro26_Entry5_DelaySec, Macro26_Entry5_TimMin, Macro26_Entry5_TimSec, Macro26_Entry5_Protocol, 0, 0, 0, 0,
		         Macro26_Entry6_DelayMin, Macro26_Entry6_DelaySec, Macro26_Entry6_TimMin, Macro26_Entry6_TimSec, Macro26_Entry6_Protocol, 0, 0, 0, 0,
		         Macro26_Entry7_DelayMin, Macro26_Entry7_DelaySec, Macro26_Entry7_TimMin, Macro26_Entry7_TimSec, Macro26_Entry7_Protocol, 0, 0, 0, 0,
		         Macro26_Entry8_DelayMin, Macro26_Entry8_DelaySec, Macro26_Entry8_TimMin, Macro26_Entry8_TimSec, Macro26_Entry8_Protocol, 0, 0, 0, 0,
		         Macro26_Entry9_DelayMin, Macro26_Entry9_DelaySec, Macro26_Entry9_TimMin, Macro26_Entry9_TimSec, Macro26_Entry9_Protocol, 0, 0, 0, 0,
		         Macro26_Entry10_DelayMin, Macro26_Entry10_DelaySec, Macro26_Entry10_TimMin, Macro26_Entry10_TimSec, Macro26_Entry10_Protocol, 0, 0, 0, 0,
		         Macro26_Entry11_DelayMin, Macro26_Entry11_DelaySec, Macro26_Entry11_TimMin, Macro26_Entry11_TimSec, Macro26_Entry11_Protocol, 0, 0, 0, 0,
		         Macro26_Entry12_DelayMin, Macro26_Entry12_DelaySec, Macro26_Entry12_TimMin, Macro26_Entry12_TimSec, Macro26_Entry12_Protocol, 0, 0, 0, 0,
		         Macro26_Entry13_DelayMin, Macro26_Entry13_DelaySec, Macro26_Entry13_TimMin, Macro26_Entry13_TimSec, Macro26_Entry13_Protocol, 0, 0, 0, 0,
		         Macro26_Entry14_DelayMin, Macro26_Entry14_DelaySec, Macro26_Entry14_TimMin, Macro26_Entry14_TimSec, Macro26_Entry14_Protocol, 0, 0, 0, 0,
		         Macro26_Entry15_DelayMin, Macro26_Entry15_DelaySec, Macro26_Entry15_TimMin, Macro26_Entry15_TimSec, Macro26_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR26_STRING};

const struct super_macro Macro27 = {Macro27_NumEntries,
		         Macro27_Entry1_DelayMin, Macro27_Entry1_DelaySec, Macro27_Entry1_TimMin, Macro27_Entry1_TimSec, Macro27_Entry1_Protocol, 0, 0, 0, 0,
		         Macro27_Entry2_DelayMin, Macro27_Entry2_DelaySec, Macro27_Entry2_TimMin, Macro27_Entry2_TimSec, Macro27_Entry2_Protocol, 0, 0, 0, 0,
		         Macro27_Entry3_DelayMin, Macro27_Entry3_DelaySec, Macro27_Entry3_TimMin, Macro27_Entry3_TimSec, Macro27_Entry3_Protocol, 0, 0, 0, 0,
		         Macro27_Entry4_DelayMin, Macro27_Entry4_DelaySec, Macro27_Entry4_TimMin, Macro27_Entry4_TimSec, Macro27_Entry4_Protocol, 0, 0, 0, 0,
		         Macro27_Entry5_DelayMin, Macro27_Entry5_DelaySec, Macro27_Entry5_TimMin, Macro27_Entry5_TimSec, Macro27_Entry5_Protocol, 0, 0, 0, 0,
		         Macro27_Entry6_DelayMin, Macro27_Entry6_DelaySec, Macro27_Entry6_TimMin, Macro27_Entry6_TimSec, Macro27_Entry6_Protocol, 0, 0, 0, 0,
		         Macro27_Entry7_DelayMin, Macro27_Entry7_DelaySec, Macro27_Entry7_TimMin, Macro27_Entry7_TimSec, Macro27_Entry7_Protocol, 0, 0, 0, 0,
		         Macro27_Entry8_DelayMin, Macro27_Entry8_DelaySec, Macro27_Entry8_TimMin, Macro27_Entry8_TimSec, Macro27_Entry8_Protocol, 0, 0, 0, 0,
		         Macro27_Entry9_DelayMin, Macro27_Entry9_DelaySec, Macro27_Entry9_TimMin, Macro27_Entry9_TimSec, Macro27_Entry9_Protocol, 0, 0, 0, 0,
		         Macro27_Entry10_DelayMin, Macro27_Entry10_DelaySec, Macro27_Entry10_TimMin, Macro27_Entry10_TimSec, Macro27_Entry10_Protocol, 0, 0, 0, 0,
		         Macro27_Entry11_DelayMin, Macro27_Entry11_DelaySec, Macro27_Entry11_TimMin, Macro27_Entry11_TimSec, Macro27_Entry11_Protocol, 0, 0, 0, 0,
		         Macro27_Entry12_DelayMin, Macro27_Entry12_DelaySec, Macro27_Entry12_TimMin, Macro27_Entry12_TimSec, Macro27_Entry12_Protocol, 0, 0, 0, 0,
		         Macro27_Entry13_DelayMin, Macro27_Entry13_DelaySec, Macro27_Entry13_TimMin, Macro27_Entry13_TimSec, Macro27_Entry13_Protocol, 0, 0, 0, 0,
		         Macro27_Entry14_DelayMin, Macro27_Entry14_DelaySec, Macro27_Entry14_TimMin, Macro27_Entry14_TimSec, Macro27_Entry14_Protocol, 0, 0, 0, 0,
		         Macro27_Entry15_DelayMin, Macro27_Entry15_DelaySec, Macro27_Entry15_TimMin, Macro27_Entry15_TimSec, Macro27_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR27_STRING};

const struct super_macro Macro28 = {Macro28_NumEntries,
		         Macro28_Entry1_DelayMin, Macro28_Entry1_DelaySec, Macro28_Entry1_TimMin, Macro28_Entry1_TimSec, Macro28_Entry1_Protocol, 0, 0, 0, 0,
		         Macro28_Entry2_DelayMin, Macro28_Entry2_DelaySec, Macro28_Entry2_TimMin, Macro28_Entry2_TimSec, Macro28_Entry2_Protocol, 0, 0, 0, 0,
		         Macro28_Entry3_DelayMin, Macro28_Entry3_DelaySec, Macro28_Entry3_TimMin, Macro28_Entry3_TimSec, Macro28_Entry3_Protocol, 0, 0, 0, 0,
		         Macro28_Entry4_DelayMin, Macro28_Entry4_DelaySec, Macro28_Entry4_TimMin, Macro28_Entry4_TimSec, Macro28_Entry4_Protocol, 0, 0, 0, 0,
		         Macro28_Entry5_DelayMin, Macro28_Entry5_DelaySec, Macro28_Entry5_TimMin, Macro28_Entry5_TimSec, Macro28_Entry5_Protocol, 0, 0, 0, 0,
		         Macro28_Entry6_DelayMin, Macro28_Entry6_DelaySec, Macro28_Entry6_TimMin, Macro28_Entry6_TimSec, Macro28_Entry6_Protocol, 0, 0, 0, 0,
		         Macro28_Entry7_DelayMin, Macro28_Entry7_DelaySec, Macro28_Entry7_TimMin, Macro28_Entry7_TimSec, Macro28_Entry7_Protocol, 0, 0, 0, 0,
		         Macro28_Entry8_DelayMin, Macro28_Entry8_DelaySec, Macro28_Entry8_TimMin, Macro28_Entry8_TimSec, Macro28_Entry8_Protocol, 0, 0, 0, 0,
		         Macro28_Entry9_DelayMin, Macro28_Entry9_DelaySec, Macro28_Entry9_TimMin, Macro28_Entry9_TimSec, Macro28_Entry9_Protocol, 0, 0, 0, 0,
		         Macro28_Entry10_DelayMin, Macro28_Entry10_DelaySec, Macro28_Entry10_TimMin, Macro28_Entry10_TimSec, Macro28_Entry10_Protocol, 0, 0, 0, 0,
		         Macro28_Entry11_DelayMin, Macro28_Entry11_DelaySec, Macro28_Entry11_TimMin, Macro28_Entry11_TimSec, Macro28_Entry11_Protocol, 0, 0, 0, 0,
		         Macro28_Entry12_DelayMin, Macro28_Entry12_DelaySec, Macro28_Entry12_TimMin, Macro28_Entry12_TimSec, Macro28_Entry12_Protocol, 0, 0, 0, 0,
		         Macro28_Entry13_DelayMin, Macro28_Entry13_DelaySec, Macro28_Entry13_TimMin, Macro28_Entry13_TimSec, Macro28_Entry13_Protocol, 0, 0, 0, 0,
		         Macro28_Entry14_DelayMin, Macro28_Entry14_DelaySec, Macro28_Entry14_TimMin, Macro28_Entry14_TimSec, Macro28_Entry14_Protocol, 0, 0, 0, 0,
		         Macro28_Entry15_DelayMin, Macro28_Entry15_DelaySec, Macro28_Entry15_TimMin, Macro28_Entry15_TimSec, Macro28_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR28_STRING};

const struct super_macro Macro29 = {Macro29_NumEntries,
		         Macro29_Entry1_DelayMin, Macro29_Entry1_DelaySec, Macro29_Entry1_TimMin, Macro29_Entry1_TimSec, Macro29_Entry1_Protocol, 0, 0, 0, 0,
		         Macro29_Entry2_DelayMin, Macro29_Entry2_DelaySec, Macro29_Entry2_TimMin, Macro29_Entry2_TimSec, Macro29_Entry2_Protocol, 0, 0, 0, 0,
		         Macro29_Entry3_DelayMin, Macro29_Entry3_DelaySec, Macro29_Entry3_TimMin, Macro29_Entry3_TimSec, Macro29_Entry3_Protocol, 0, 0, 0, 0,
		         Macro29_Entry4_DelayMin, Macro29_Entry4_DelaySec, Macro29_Entry4_TimMin, Macro29_Entry4_TimSec, Macro29_Entry4_Protocol, 0, 0, 0, 0,
		         Macro29_Entry5_DelayMin, Macro29_Entry5_DelaySec, Macro29_Entry5_TimMin, Macro29_Entry5_TimSec, Macro29_Entry5_Protocol, 0, 0, 0, 0,
		         Macro29_Entry6_DelayMin, Macro29_Entry6_DelaySec, Macro29_Entry6_TimMin, Macro29_Entry6_TimSec, Macro29_Entry6_Protocol, 0, 0, 0, 0,
		         Macro29_Entry7_DelayMin, Macro29_Entry7_DelaySec, Macro29_Entry7_TimMin, Macro29_Entry7_TimSec, Macro29_Entry7_Protocol, 0, 0, 0, 0,
		         Macro29_Entry8_DelayMin, Macro29_Entry8_DelaySec, Macro29_Entry8_TimMin, Macro29_Entry8_TimSec, Macro29_Entry8_Protocol, 0, 0, 0, 0,
		         Macro29_Entry9_DelayMin, Macro29_Entry9_DelaySec, Macro29_Entry9_TimMin, Macro29_Entry9_TimSec, Macro29_Entry9_Protocol, 0, 0, 0, 0,
		         Macro29_Entry10_DelayMin, Macro29_Entry10_DelaySec, Macro29_Entry10_TimMin, Macro29_Entry10_TimSec, Macro29_Entry10_Protocol, 0, 0, 0, 0,
		         Macro29_Entry11_DelayMin, Macro29_Entry11_DelaySec, Macro29_Entry11_TimMin, Macro29_Entry11_TimSec, Macro29_Entry11_Protocol, 0, 0, 0, 0,
		         Macro29_Entry12_DelayMin, Macro29_Entry12_DelaySec, Macro29_Entry12_TimMin, Macro29_Entry12_TimSec, Macro29_Entry12_Protocol, 0, 0, 0, 0,
		         Macro29_Entry13_DelayMin, Macro29_Entry13_DelaySec, Macro29_Entry13_TimMin, Macro29_Entry13_TimSec, Macro29_Entry13_Protocol, 0, 0, 0, 0,
		         Macro29_Entry14_DelayMin, Macro29_Entry14_DelaySec, Macro29_Entry14_TimMin, Macro29_Entry14_TimSec, Macro29_Entry14_Protocol, 0, 0, 0, 0,
		         Macro29_Entry15_DelayMin, Macro29_Entry15_DelaySec, Macro29_Entry15_TimMin, Macro29_Entry15_TimSec, Macro29_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR29_STRING};

const struct super_macro Macro30 = {Macro30_NumEntries,
		         Macro30_Entry1_DelayMin, Macro30_Entry1_DelaySec, Macro30_Entry1_TimMin, Macro30_Entry1_TimSec, Macro30_Entry1_Protocol, 0, 0, 0, 0,
		         Macro30_Entry2_DelayMin, Macro30_Entry2_DelaySec, Macro30_Entry2_TimMin, Macro30_Entry2_TimSec, Macro30_Entry2_Protocol, 0, 0, 0, 0,
		         Macro30_Entry3_DelayMin, Macro30_Entry3_DelaySec, Macro30_Entry3_TimMin, Macro30_Entry3_TimSec, Macro30_Entry3_Protocol, 0, 0, 0, 0,
		         Macro30_Entry4_DelayMin, Macro30_Entry4_DelaySec, Macro30_Entry4_TimMin, Macro30_Entry4_TimSec, Macro30_Entry4_Protocol, 0, 0, 0, 0,
		         Macro30_Entry5_DelayMin, Macro30_Entry5_DelaySec, Macro30_Entry5_TimMin, Macro30_Entry5_TimSec, Macro30_Entry5_Protocol, 0, 0, 0, 0,
		         Macro30_Entry6_DelayMin, Macro30_Entry6_DelaySec, Macro30_Entry6_TimMin, Macro30_Entry6_TimSec, Macro30_Entry6_Protocol, 0, 0, 0, 0,
		         Macro30_Entry7_DelayMin, Macro30_Entry7_DelaySec, Macro30_Entry7_TimMin, Macro30_Entry7_TimSec, Macro30_Entry7_Protocol, 0, 0, 0, 0,
		         Macro30_Entry8_DelayMin, Macro30_Entry8_DelaySec, Macro30_Entry8_TimMin, Macro30_Entry8_TimSec, Macro30_Entry8_Protocol, 0, 0, 0, 0,
		         Macro30_Entry9_DelayMin, Macro30_Entry9_DelaySec, Macro30_Entry9_TimMin, Macro30_Entry9_TimSec, Macro30_Entry9_Protocol, 0, 0, 0, 0,
		         Macro30_Entry10_DelayMin, Macro30_Entry10_DelaySec, Macro30_Entry10_TimMin, Macro30_Entry10_TimSec, Macro30_Entry10_Protocol, 0, 0, 0, 0,
		         Macro30_Entry11_DelayMin, Macro30_Entry11_DelaySec, Macro30_Entry11_TimMin, Macro30_Entry11_TimSec, Macro30_Entry11_Protocol, 0, 0, 0, 0,
		         Macro30_Entry12_DelayMin, Macro30_Entry12_DelaySec, Macro30_Entry12_TimMin, Macro30_Entry12_TimSec, Macro30_Entry12_Protocol, 0, 0, 0, 0,
		         Macro30_Entry13_DelayMin, Macro30_Entry13_DelaySec, Macro30_Entry13_TimMin, Macro30_Entry13_TimSec, Macro30_Entry13_Protocol, 0, 0, 0, 0,
		         Macro30_Entry14_DelayMin, Macro30_Entry14_DelaySec, Macro30_Entry14_TimMin, Macro30_Entry14_TimSec, Macro30_Entry14_Protocol, 0, 0, 0, 0,
		         Macro30_Entry15_DelayMin, Macro30_Entry15_DelaySec, Macro30_Entry15_TimMin, Macro30_Entry15_TimSec, Macro30_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR30_STRING};

const struct super_macro Macro31 = {Macro31_NumEntries,
		         Macro31_Entry1_DelayMin, Macro31_Entry1_DelaySec, Macro31_Entry1_TimMin, Macro31_Entry1_TimSec, Macro31_Entry1_Protocol, 0, 0, 0, 0,
		         Macro31_Entry2_DelayMin, Macro31_Entry2_DelaySec, Macro31_Entry2_TimMin, Macro31_Entry2_TimSec, Macro31_Entry2_Protocol, 0, 0, 0, 0,
		         Macro31_Entry3_DelayMin, Macro31_Entry3_DelaySec, Macro31_Entry3_TimMin, Macro31_Entry3_TimSec, Macro31_Entry3_Protocol, 0, 0, 0, 0,
		         Macro31_Entry4_DelayMin, Macro31_Entry4_DelaySec, Macro31_Entry4_TimMin, Macro31_Entry4_TimSec, Macro31_Entry4_Protocol, 0, 0, 0, 0,
		         Macro31_Entry5_DelayMin, Macro31_Entry5_DelaySec, Macro31_Entry5_TimMin, Macro31_Entry5_TimSec, Macro31_Entry5_Protocol, 0, 0, 0, 0,
		         Macro31_Entry6_DelayMin, Macro31_Entry6_DelaySec, Macro31_Entry6_TimMin, Macro31_Entry6_TimSec, Macro31_Entry6_Protocol, 0, 0, 0, 0,
		         Macro31_Entry7_DelayMin, Macro31_Entry7_DelaySec, Macro31_Entry7_TimMin, Macro31_Entry7_TimSec, Macro31_Entry7_Protocol, 0, 0, 0, 0,
		         Macro31_Entry8_DelayMin, Macro31_Entry8_DelaySec, Macro31_Entry8_TimMin, Macro31_Entry8_TimSec, Macro31_Entry8_Protocol, 0, 0, 0, 0,
		         Macro31_Entry9_DelayMin, Macro31_Entry9_DelaySec, Macro31_Entry9_TimMin, Macro31_Entry9_TimSec, Macro31_Entry9_Protocol, 0, 0, 0, 0,
		         Macro31_Entry10_DelayMin, Macro31_Entry10_DelaySec, Macro31_Entry10_TimMin, Macro31_Entry10_TimSec, Macro31_Entry10_Protocol, 0, 0, 0, 0,
		         Macro31_Entry11_DelayMin, Macro31_Entry11_DelaySec, Macro31_Entry11_TimMin, Macro31_Entry11_TimSec, Macro31_Entry11_Protocol, 0, 0, 0, 0,
		         Macro31_Entry12_DelayMin, Macro31_Entry12_DelaySec, Macro31_Entry12_TimMin, Macro31_Entry12_TimSec, Macro31_Entry12_Protocol, 0, 0, 0, 0,
		         Macro31_Entry13_DelayMin, Macro31_Entry13_DelaySec, Macro31_Entry13_TimMin, Macro31_Entry13_TimSec, Macro31_Entry13_Protocol, 0, 0, 0, 0,
		         Macro31_Entry14_DelayMin, Macro31_Entry14_DelaySec, Macro31_Entry14_TimMin, Macro31_Entry14_TimSec, Macro31_Entry14_Protocol, 0, 0, 0, 0,
		         Macro31_Entry15_DelayMin, Macro31_Entry15_DelaySec, Macro31_Entry15_TimMin, Macro31_Entry15_TimSec, Macro31_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR31_STRING};

const struct super_macro Macro32 = {Macro32_NumEntries,
		         Macro32_Entry1_DelayMin, Macro32_Entry1_DelaySec, Macro32_Entry1_TimMin, Macro32_Entry1_TimSec, Macro32_Entry1_Protocol, 0, 0, 0, 0,
		         Macro32_Entry2_DelayMin, Macro32_Entry2_DelaySec, Macro32_Entry2_TimMin, Macro32_Entry2_TimSec, Macro32_Entry2_Protocol, 0, 0, 0, 0,
		         Macro32_Entry3_DelayMin, Macro32_Entry3_DelaySec, Macro32_Entry3_TimMin, Macro32_Entry3_TimSec, Macro32_Entry3_Protocol, 0, 0, 0, 0,
		         Macro32_Entry4_DelayMin, Macro32_Entry4_DelaySec, Macro32_Entry4_TimMin, Macro32_Entry4_TimSec, Macro32_Entry4_Protocol, 0, 0, 0, 0,
		         Macro32_Entry5_DelayMin, Macro32_Entry5_DelaySec, Macro32_Entry5_TimMin, Macro32_Entry5_TimSec, Macro32_Entry5_Protocol, 0, 0, 0, 0,
		         Macro32_Entry6_DelayMin, Macro32_Entry6_DelaySec, Macro32_Entry6_TimMin, Macro32_Entry6_TimSec, Macro32_Entry6_Protocol, 0, 0, 0, 0,
		         Macro32_Entry7_DelayMin, Macro32_Entry7_DelaySec, Macro32_Entry7_TimMin, Macro32_Entry7_TimSec, Macro32_Entry7_Protocol, 0, 0, 0, 0,
		         Macro32_Entry8_DelayMin, Macro32_Entry8_DelaySec, Macro32_Entry8_TimMin, Macro32_Entry8_TimSec, Macro32_Entry8_Protocol, 0, 0, 0, 0,
		         Macro32_Entry9_DelayMin, Macro32_Entry9_DelaySec, Macro32_Entry9_TimMin, Macro32_Entry9_TimSec, Macro32_Entry9_Protocol, 0, 0, 0, 0,
		         Macro32_Entry10_DelayMin, Macro32_Entry10_DelaySec, Macro32_Entry10_TimMin, Macro32_Entry10_TimSec, Macro32_Entry10_Protocol, 0, 0, 0, 0,
		         Macro32_Entry11_DelayMin, Macro32_Entry11_DelaySec, Macro32_Entry11_TimMin, Macro32_Entry11_TimSec, Macro32_Entry11_Protocol, 0, 0, 0, 0,
		         Macro32_Entry12_DelayMin, Macro32_Entry12_DelaySec, Macro32_Entry12_TimMin, Macro32_Entry12_TimSec, Macro32_Entry12_Protocol, 0, 0, 0, 0,
		         Macro32_Entry13_DelayMin, Macro32_Entry13_DelaySec, Macro32_Entry13_TimMin, Macro32_Entry13_TimSec, Macro32_Entry13_Protocol, 0, 0, 0, 0,
		         Macro32_Entry14_DelayMin, Macro32_Entry14_DelaySec, Macro32_Entry14_TimMin, Macro32_Entry14_TimSec, Macro32_Entry14_Protocol, 0, 0, 0, 0,
		         Macro32_Entry15_DelayMin, Macro32_Entry15_DelaySec, Macro32_Entry15_TimMin, Macro32_Entry15_TimSec, Macro32_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR32_STRING};

const struct super_macro Macro33 = {Macro33_NumEntries,
		         Macro33_Entry1_DelayMin, Macro33_Entry1_DelaySec, Macro33_Entry1_TimMin, Macro33_Entry1_TimSec, Macro33_Entry1_Protocol, 0, 0, 0, 0,
		         Macro33_Entry2_DelayMin, Macro33_Entry2_DelaySec, Macro33_Entry2_TimMin, Macro33_Entry2_TimSec, Macro33_Entry2_Protocol, 0, 0, 0, 0,
		         Macro33_Entry3_DelayMin, Macro33_Entry3_DelaySec, Macro33_Entry3_TimMin, Macro33_Entry3_TimSec, Macro33_Entry3_Protocol, 0, 0, 0, 0,
		         Macro33_Entry4_DelayMin, Macro33_Entry4_DelaySec, Macro33_Entry4_TimMin, Macro33_Entry4_TimSec, Macro33_Entry4_Protocol, 0, 0, 0, 0,
		         Macro33_Entry5_DelayMin, Macro33_Entry5_DelaySec, Macro33_Entry5_TimMin, Macro33_Entry5_TimSec, Macro33_Entry5_Protocol, 0, 0, 0, 0,
		         Macro33_Entry6_DelayMin, Macro33_Entry6_DelaySec, Macro33_Entry6_TimMin, Macro33_Entry6_TimSec, Macro33_Entry6_Protocol, 0, 0, 0, 0,
		         Macro33_Entry7_DelayMin, Macro33_Entry7_DelaySec, Macro33_Entry7_TimMin, Macro33_Entry7_TimSec, Macro33_Entry7_Protocol, 0, 0, 0, 0,
		         Macro33_Entry8_DelayMin, Macro33_Entry8_DelaySec, Macro33_Entry8_TimMin, Macro33_Entry8_TimSec, Macro33_Entry8_Protocol, 0, 0, 0, 0,
		         Macro33_Entry9_DelayMin, Macro33_Entry9_DelaySec, Macro33_Entry9_TimMin, Macro33_Entry9_TimSec, Macro33_Entry9_Protocol, 0, 0, 0, 0,
		         Macro33_Entry10_DelayMin, Macro33_Entry10_DelaySec, Macro33_Entry10_TimMin, Macro33_Entry10_TimSec, Macro33_Entry10_Protocol, 0, 0, 0, 0,
		         Macro33_Entry11_DelayMin, Macro33_Entry11_DelaySec, Macro33_Entry11_TimMin, Macro33_Entry11_TimSec, Macro33_Entry11_Protocol, 0, 0, 0, 0,
		         Macro33_Entry12_DelayMin, Macro33_Entry12_DelaySec, Macro33_Entry12_TimMin, Macro33_Entry12_TimSec, Macro33_Entry12_Protocol, 0, 0, 0, 0,
		         Macro33_Entry13_DelayMin, Macro33_Entry13_DelaySec, Macro33_Entry13_TimMin, Macro33_Entry13_TimSec, Macro33_Entry13_Protocol, 0, 0, 0, 0,
		         Macro33_Entry14_DelayMin, Macro33_Entry14_DelaySec, Macro33_Entry14_TimMin, Macro33_Entry14_TimSec, Macro33_Entry14_Protocol, 0, 0, 0, 0,
		         Macro33_Entry15_DelayMin, Macro33_Entry15_DelaySec, Macro33_Entry15_TimMin, Macro33_Entry15_TimSec, Macro33_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR33_STRING};

const struct super_macro Macro34 = {Macro34_NumEntries,
		         Macro34_Entry1_DelayMin, Macro34_Entry1_DelaySec, Macro34_Entry1_TimMin, Macro34_Entry1_TimSec, Macro34_Entry1_Protocol, 0, 0, 0, 0,
		         Macro34_Entry2_DelayMin, Macro34_Entry2_DelaySec, Macro34_Entry2_TimMin, Macro34_Entry2_TimSec, Macro34_Entry2_Protocol, 0, 0, 0, 0,
		         Macro34_Entry3_DelayMin, Macro34_Entry3_DelaySec, Macro34_Entry3_TimMin, Macro34_Entry3_TimSec, Macro34_Entry3_Protocol, 0, 0, 0, 0,
		         Macro34_Entry4_DelayMin, Macro34_Entry4_DelaySec, Macro34_Entry4_TimMin, Macro34_Entry4_TimSec, Macro34_Entry4_Protocol, 0, 0, 0, 0,
		         Macro34_Entry5_DelayMin, Macro34_Entry5_DelaySec, Macro34_Entry5_TimMin, Macro34_Entry5_TimSec, Macro34_Entry5_Protocol, 0, 0, 0, 0,
		         Macro34_Entry6_DelayMin, Macro34_Entry6_DelaySec, Macro34_Entry6_TimMin, Macro34_Entry6_TimSec, Macro34_Entry6_Protocol, 0, 0, 0, 0,
		         Macro34_Entry7_DelayMin, Macro34_Entry7_DelaySec, Macro34_Entry7_TimMin, Macro34_Entry7_TimSec, Macro34_Entry7_Protocol, 0, 0, 0, 0,
		         Macro34_Entry8_DelayMin, Macro34_Entry8_DelaySec, Macro34_Entry8_TimMin, Macro34_Entry8_TimSec, Macro34_Entry8_Protocol, 0, 0, 0, 0,
		         Macro34_Entry9_DelayMin, Macro34_Entry9_DelaySec, Macro34_Entry9_TimMin, Macro34_Entry9_TimSec, Macro34_Entry9_Protocol, 0, 0, 0, 0,
		         Macro34_Entry10_DelayMin, Macro34_Entry10_DelaySec, Macro34_Entry10_TimMin, Macro34_Entry10_TimSec, Macro34_Entry10_Protocol, 0, 0, 0, 0,
		         Macro34_Entry11_DelayMin, Macro34_Entry11_DelaySec, Macro34_Entry11_TimMin, Macro34_Entry11_TimSec, Macro34_Entry11_Protocol, 0, 0, 0, 0,
		         Macro34_Entry12_DelayMin, Macro34_Entry12_DelaySec, Macro34_Entry12_TimMin, Macro34_Entry12_TimSec, Macro34_Entry12_Protocol, 0, 0, 0, 0,
		         Macro34_Entry13_DelayMin, Macro34_Entry13_DelaySec, Macro34_Entry13_TimMin, Macro34_Entry13_TimSec, Macro34_Entry13_Protocol, 0, 0, 0, 0,
		         Macro34_Entry14_DelayMin, Macro34_Entry14_DelaySec, Macro34_Entry14_TimMin, Macro34_Entry14_TimSec, Macro34_Entry14_Protocol, 0, 0, 0, 0,
		         Macro34_Entry15_DelayMin, Macro34_Entry15_DelaySec, Macro34_Entry15_TimMin, Macro34_Entry15_TimSec, Macro34_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR34_STRING};

const struct super_macro Macro35 = {Macro35_NumEntries,
		         Macro35_Entry1_DelayMin, Macro35_Entry1_DelaySec, Macro35_Entry1_TimMin, Macro35_Entry1_TimSec, Macro35_Entry1_Protocol, 0, 0, 0, 0,
		         Macro35_Entry2_DelayMin, Macro35_Entry2_DelaySec, Macro35_Entry2_TimMin, Macro35_Entry2_TimSec, Macro35_Entry2_Protocol, 0, 0, 0, 0,
		         Macro35_Entry3_DelayMin, Macro35_Entry3_DelaySec, Macro35_Entry3_TimMin, Macro35_Entry3_TimSec, Macro35_Entry3_Protocol, 0, 0, 0, 0,
		         Macro35_Entry4_DelayMin, Macro35_Entry4_DelaySec, Macro35_Entry4_TimMin, Macro35_Entry4_TimSec, Macro35_Entry4_Protocol, 0, 0, 0, 0,
		         Macro35_Entry5_DelayMin, Macro35_Entry5_DelaySec, Macro35_Entry5_TimMin, Macro35_Entry5_TimSec, Macro35_Entry5_Protocol, 0, 0, 0, 0,
		         Macro35_Entry6_DelayMin, Macro35_Entry6_DelaySec, Macro35_Entry6_TimMin, Macro35_Entry6_TimSec, Macro35_Entry6_Protocol, 0, 0, 0, 0,
		         Macro35_Entry7_DelayMin, Macro35_Entry7_DelaySec, Macro35_Entry7_TimMin, Macro35_Entry7_TimSec, Macro35_Entry7_Protocol, 0, 0, 0, 0,
		         Macro35_Entry8_DelayMin, Macro35_Entry8_DelaySec, Macro35_Entry8_TimMin, Macro35_Entry8_TimSec, Macro35_Entry8_Protocol, 0, 0, 0, 0,
		         Macro35_Entry9_DelayMin, Macro35_Entry9_DelaySec, Macro35_Entry9_TimMin, Macro35_Entry9_TimSec, Macro35_Entry9_Protocol, 0, 0, 0, 0,
		         Macro35_Entry10_DelayMin, Macro35_Entry10_DelaySec, Macro35_Entry10_TimMin, Macro35_Entry10_TimSec, Macro35_Entry10_Protocol, 0, 0, 0, 0,
		         Macro35_Entry11_DelayMin, Macro35_Entry11_DelaySec, Macro35_Entry11_TimMin, Macro35_Entry11_TimSec, Macro35_Entry11_Protocol, 0, 0, 0, 0,
		         Macro35_Entry12_DelayMin, Macro35_Entry12_DelaySec, Macro35_Entry12_TimMin, Macro35_Entry12_TimSec, Macro35_Entry12_Protocol, 0, 0, 0, 0,
		         Macro35_Entry13_DelayMin, Macro35_Entry13_DelaySec, Macro35_Entry13_TimMin, Macro35_Entry13_TimSec, Macro35_Entry13_Protocol, 0, 0, 0, 0,
		         Macro35_Entry14_DelayMin, Macro35_Entry14_DelaySec, Macro35_Entry14_TimMin, Macro35_Entry14_TimSec, Macro35_Entry14_Protocol, 0, 0, 0, 0,
		         Macro35_Entry15_DelayMin, Macro35_Entry15_DelaySec, Macro35_Entry15_TimMin, Macro35_Entry15_TimSec, Macro35_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR35_STRING};

const struct super_macro Macro36 = {Macro36_NumEntries,
		         Macro36_Entry1_DelayMin, Macro36_Entry1_DelaySec, Macro36_Entry1_TimMin, Macro36_Entry1_TimSec, Macro36_Entry1_Protocol, 0, 0, 0, 0,
		         Macro36_Entry2_DelayMin, Macro36_Entry2_DelaySec, Macro36_Entry2_TimMin, Macro36_Entry2_TimSec, Macro36_Entry2_Protocol, 0, 0, 0, 0,
		         Macro36_Entry3_DelayMin, Macro36_Entry3_DelaySec, Macro36_Entry3_TimMin, Macro36_Entry3_TimSec, Macro36_Entry3_Protocol, 0, 0, 0, 0,
		         Macro36_Entry4_DelayMin, Macro36_Entry4_DelaySec, Macro36_Entry4_TimMin, Macro36_Entry4_TimSec, Macro36_Entry4_Protocol, 0, 0, 0, 0,
		         Macro36_Entry5_DelayMin, Macro36_Entry5_DelaySec, Macro36_Entry5_TimMin, Macro36_Entry5_TimSec, Macro36_Entry5_Protocol, 0, 0, 0, 0,
		         Macro36_Entry6_DelayMin, Macro36_Entry6_DelaySec, Macro36_Entry6_TimMin, Macro36_Entry6_TimSec, Macro36_Entry6_Protocol, 0, 0, 0, 0,
		         Macro36_Entry7_DelayMin, Macro36_Entry7_DelaySec, Macro36_Entry7_TimMin, Macro36_Entry7_TimSec, Macro36_Entry7_Protocol, 0, 0, 0, 0,
		         Macro36_Entry8_DelayMin, Macro36_Entry8_DelaySec, Macro36_Entry8_TimMin, Macro36_Entry8_TimSec, Macro36_Entry8_Protocol, 0, 0, 0, 0,
		         Macro36_Entry9_DelayMin, Macro36_Entry9_DelaySec, Macro36_Entry9_TimMin, Macro36_Entry9_TimSec, Macro36_Entry9_Protocol, 0, 0, 0, 0,
		         Macro36_Entry10_DelayMin, Macro36_Entry10_DelaySec, Macro36_Entry10_TimMin, Macro36_Entry10_TimSec, Macro36_Entry10_Protocol, 0, 0, 0, 0,
		         Macro36_Entry11_DelayMin, Macro36_Entry11_DelaySec, Macro36_Entry11_TimMin, Macro36_Entry11_TimSec, Macro36_Entry11_Protocol, 0, 0, 0, 0,
		         Macro36_Entry12_DelayMin, Macro36_Entry12_DelaySec, Macro36_Entry12_TimMin, Macro36_Entry12_TimSec, Macro36_Entry12_Protocol, 0, 0, 0, 0,
		         Macro36_Entry13_DelayMin, Macro36_Entry13_DelaySec, Macro36_Entry13_TimMin, Macro36_Entry13_TimSec, Macro36_Entry13_Protocol, 0, 0, 0, 0,
		         Macro36_Entry14_DelayMin, Macro36_Entry14_DelaySec, Macro36_Entry14_TimMin, Macro36_Entry14_TimSec, Macro36_Entry14_Protocol, 0, 0, 0, 0,
		         Macro36_Entry15_DelayMin, Macro36_Entry15_DelaySec, Macro36_Entry15_TimMin, Macro36_Entry15_TimSec, Macro36_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR36_STRING};

const struct super_macro Macro37 = {Macro37_NumEntries,
		         Macro37_Entry1_DelayMin, Macro37_Entry1_DelaySec, Macro37_Entry1_TimMin, Macro37_Entry1_TimSec, Macro37_Entry1_Protocol, 0, 0, 0, 0,
		         Macro37_Entry2_DelayMin, Macro37_Entry2_DelaySec, Macro37_Entry2_TimMin, Macro37_Entry2_TimSec, Macro37_Entry2_Protocol, 0, 0, 0, 0,
		         Macro37_Entry3_DelayMin, Macro37_Entry3_DelaySec, Macro37_Entry3_TimMin, Macro37_Entry3_TimSec, Macro37_Entry3_Protocol, 0, 0, 0, 0,
		         Macro37_Entry4_DelayMin, Macro37_Entry4_DelaySec, Macro37_Entry4_TimMin, Macro37_Entry4_TimSec, Macro37_Entry4_Protocol, 0, 0, 0, 0,
		         Macro37_Entry5_DelayMin, Macro37_Entry5_DelaySec, Macro37_Entry5_TimMin, Macro37_Entry5_TimSec, Macro37_Entry5_Protocol, 0, 0, 0, 0,
		         Macro37_Entry6_DelayMin, Macro37_Entry6_DelaySec, Macro37_Entry6_TimMin, Macro37_Entry6_TimSec, Macro37_Entry6_Protocol, 0, 0, 0, 0,
		         Macro37_Entry7_DelayMin, Macro37_Entry7_DelaySec, Macro37_Entry7_TimMin, Macro37_Entry7_TimSec, Macro37_Entry7_Protocol, 0, 0, 0, 0,
		         Macro37_Entry8_DelayMin, Macro37_Entry8_DelaySec, Macro37_Entry8_TimMin, Macro37_Entry8_TimSec, Macro37_Entry8_Protocol, 0, 0, 0, 0,
		         Macro37_Entry9_DelayMin, Macro37_Entry9_DelaySec, Macro37_Entry9_TimMin, Macro37_Entry9_TimSec, Macro37_Entry9_Protocol, 0, 0, 0, 0,
		         Macro37_Entry10_DelayMin, Macro37_Entry10_DelaySec, Macro37_Entry10_TimMin, Macro37_Entry10_TimSec, Macro37_Entry10_Protocol, 0, 0, 0, 0,
		         Macro37_Entry11_DelayMin, Macro37_Entry11_DelaySec, Macro37_Entry11_TimMin, Macro37_Entry11_TimSec, Macro37_Entry11_Protocol, 0, 0, 0, 0,
		         Macro37_Entry12_DelayMin, Macro37_Entry12_DelaySec, Macro37_Entry12_TimMin, Macro37_Entry12_TimSec, Macro37_Entry12_Protocol, 0, 0, 0, 0,
		         Macro37_Entry13_DelayMin, Macro37_Entry13_DelaySec, Macro37_Entry13_TimMin, Macro37_Entry13_TimSec, Macro37_Entry13_Protocol, 0, 0, 0, 0,
		         Macro37_Entry14_DelayMin, Macro37_Entry14_DelaySec, Macro37_Entry14_TimMin, Macro37_Entry14_TimSec, Macro37_Entry14_Protocol, 0, 0, 0, 0,
		         Macro37_Entry15_DelayMin, Macro37_Entry15_DelaySec, Macro37_Entry15_TimMin, Macro37_Entry15_TimSec, Macro37_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR37_STRING};

const struct super_macro Macro38 = {Macro38_NumEntries,
		         Macro38_Entry1_DelayMin, Macro38_Entry1_DelaySec, Macro38_Entry1_TimMin, Macro38_Entry1_TimSec, Macro38_Entry1_Protocol, 0, 0, 0, 0,
		         Macro38_Entry2_DelayMin, Macro38_Entry2_DelaySec, Macro38_Entry2_TimMin, Macro38_Entry2_TimSec, Macro38_Entry2_Protocol, 0, 0, 0, 0,
		         Macro38_Entry3_DelayMin, Macro38_Entry3_DelaySec, Macro38_Entry3_TimMin, Macro38_Entry3_TimSec, Macro38_Entry3_Protocol, 0, 0, 0, 0,
		         Macro38_Entry4_DelayMin, Macro38_Entry4_DelaySec, Macro38_Entry4_TimMin, Macro38_Entry4_TimSec, Macro38_Entry4_Protocol, 0, 0, 0, 0,
		         Macro38_Entry5_DelayMin, Macro38_Entry5_DelaySec, Macro38_Entry5_TimMin, Macro38_Entry5_TimSec, Macro38_Entry5_Protocol, 0, 0, 0, 0,
		         Macro38_Entry6_DelayMin, Macro38_Entry6_DelaySec, Macro38_Entry6_TimMin, Macro38_Entry6_TimSec, Macro38_Entry6_Protocol, 0, 0, 0, 0,
		         Macro38_Entry7_DelayMin, Macro38_Entry7_DelaySec, Macro38_Entry7_TimMin, Macro38_Entry7_TimSec, Macro38_Entry7_Protocol, 0, 0, 0, 0,
		         Macro38_Entry8_DelayMin, Macro38_Entry8_DelaySec, Macro38_Entry8_TimMin, Macro38_Entry8_TimSec, Macro38_Entry8_Protocol, 0, 0, 0, 0,
		         Macro38_Entry9_DelayMin, Macro38_Entry9_DelaySec, Macro38_Entry9_TimMin, Macro38_Entry9_TimSec, Macro38_Entry9_Protocol, 0, 0, 0, 0,
		         Macro38_Entry10_DelayMin, Macro38_Entry10_DelaySec, Macro38_Entry10_TimMin, Macro38_Entry10_TimSec, Macro38_Entry10_Protocol, 0, 0, 0, 0,
		         Macro38_Entry11_DelayMin, Macro38_Entry11_DelaySec, Macro38_Entry11_TimMin, Macro38_Entry11_TimSec, Macro38_Entry11_Protocol, 0, 0, 0, 0,
		         Macro38_Entry12_DelayMin, Macro38_Entry12_DelaySec, Macro38_Entry12_TimMin, Macro38_Entry12_TimSec, Macro38_Entry12_Protocol, 0, 0, 0, 0,
		         Macro38_Entry13_DelayMin, Macro38_Entry13_DelaySec, Macro38_Entry13_TimMin, Macro38_Entry13_TimSec, Macro38_Entry13_Protocol, 0, 0, 0, 0,
		         Macro38_Entry14_DelayMin, Macro38_Entry14_DelaySec, Macro38_Entry14_TimMin, Macro38_Entry14_TimSec, Macro38_Entry14_Protocol, 0, 0, 0, 0,
		         Macro38_Entry15_DelayMin, Macro38_Entry15_DelaySec, Macro38_Entry15_TimMin, Macro38_Entry15_TimSec, Macro38_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR38_STRING};

const struct super_macro Macro39 = {Macro39_NumEntries,
		         Macro39_Entry1_DelayMin, Macro39_Entry1_DelaySec, Macro39_Entry1_TimMin, Macro39_Entry1_TimSec, Macro39_Entry1_Protocol, 0, 0, 0, 0,
		         Macro39_Entry2_DelayMin, Macro39_Entry2_DelaySec, Macro39_Entry2_TimMin, Macro39_Entry2_TimSec, Macro39_Entry2_Protocol, 0, 0, 0, 0,
		         Macro39_Entry3_DelayMin, Macro39_Entry3_DelaySec, Macro39_Entry3_TimMin, Macro39_Entry3_TimSec, Macro39_Entry3_Protocol, 0, 0, 0, 0,
		         Macro39_Entry4_DelayMin, Macro39_Entry4_DelaySec, Macro39_Entry4_TimMin, Macro39_Entry4_TimSec, Macro39_Entry4_Protocol, 0, 0, 0, 0,
		         Macro39_Entry5_DelayMin, Macro39_Entry5_DelaySec, Macro39_Entry5_TimMin, Macro39_Entry5_TimSec, Macro39_Entry5_Protocol, 0, 0, 0, 0,
		         Macro39_Entry6_DelayMin, Macro39_Entry6_DelaySec, Macro39_Entry6_TimMin, Macro39_Entry6_TimSec, Macro39_Entry6_Protocol, 0, 0, 0, 0,
		         Macro39_Entry7_DelayMin, Macro39_Entry7_DelaySec, Macro39_Entry7_TimMin, Macro39_Entry7_TimSec, Macro39_Entry7_Protocol, 0, 0, 0, 0,
		         Macro39_Entry8_DelayMin, Macro39_Entry8_DelaySec, Macro39_Entry8_TimMin, Macro39_Entry8_TimSec, Macro39_Entry8_Protocol, 0, 0, 0, 0,
		         Macro39_Entry9_DelayMin, Macro39_Entry9_DelaySec, Macro39_Entry9_TimMin, Macro39_Entry9_TimSec, Macro39_Entry9_Protocol, 0, 0, 0, 0,
		         Macro39_Entry10_DelayMin, Macro39_Entry10_DelaySec, Macro39_Entry10_TimMin, Macro39_Entry10_TimSec, Macro39_Entry10_Protocol, 0, 0, 0, 0,
		         Macro39_Entry11_DelayMin, Macro39_Entry11_DelaySec, Macro39_Entry11_TimMin, Macro39_Entry11_TimSec, Macro39_Entry11_Protocol, 0, 0, 0, 0,
		         Macro39_Entry12_DelayMin, Macro39_Entry12_DelaySec, Macro39_Entry12_TimMin, Macro39_Entry12_TimSec, Macro39_Entry12_Protocol, 0, 0, 0, 0,
		         Macro39_Entry13_DelayMin, Macro39_Entry13_DelaySec, Macro39_Entry13_TimMin, Macro39_Entry13_TimSec, Macro39_Entry13_Protocol, 0, 0, 0, 0,
		         Macro39_Entry14_DelayMin, Macro39_Entry14_DelaySec, Macro39_Entry14_TimMin, Macro39_Entry14_TimSec, Macro39_Entry14_Protocol, 0, 0, 0, 0,
		         Macro39_Entry15_DelayMin, Macro39_Entry15_DelaySec, Macro39_Entry15_TimMin, Macro39_Entry15_TimSec, Macro39_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR39_STRING};

const struct super_macro Macro40 = {Macro40_NumEntries,
		         Macro40_Entry1_DelayMin, Macro40_Entry1_DelaySec, Macro40_Entry1_TimMin, Macro40_Entry1_TimSec, Macro40_Entry1_Protocol, 0, 0, 0, 0,
		         Macro40_Entry2_DelayMin, Macro40_Entry2_DelaySec, Macro40_Entry2_TimMin, Macro40_Entry2_TimSec, Macro40_Entry2_Protocol, 0, 0, 0, 0,
		         Macro40_Entry3_DelayMin, Macro40_Entry3_DelaySec, Macro40_Entry3_TimMin, Macro40_Entry3_TimSec, Macro40_Entry3_Protocol, 0, 0, 0, 0,
		         Macro40_Entry4_DelayMin, Macro40_Entry4_DelaySec, Macro40_Entry4_TimMin, Macro40_Entry4_TimSec, Macro40_Entry4_Protocol, 0, 0, 0, 0,
		         Macro40_Entry5_DelayMin, Macro40_Entry5_DelaySec, Macro40_Entry5_TimMin, Macro40_Entry5_TimSec, Macro40_Entry5_Protocol, 0, 0, 0, 0,
		         Macro40_Entry6_DelayMin, Macro40_Entry6_DelaySec, Macro40_Entry6_TimMin, Macro40_Entry6_TimSec, Macro40_Entry6_Protocol, 0, 0, 0, 0,
		         Macro40_Entry7_DelayMin, Macro40_Entry7_DelaySec, Macro40_Entry7_TimMin, Macro40_Entry7_TimSec, Macro40_Entry7_Protocol, 0, 0, 0, 0,
		         Macro40_Entry8_DelayMin, Macro40_Entry8_DelaySec, Macro40_Entry8_TimMin, Macro40_Entry8_TimSec, Macro40_Entry8_Protocol, 0, 0, 0, 0,
		         Macro40_Entry9_DelayMin, Macro40_Entry9_DelaySec, Macro40_Entry9_TimMin, Macro40_Entry9_TimSec, Macro40_Entry9_Protocol, 0, 0, 0, 0,
		         Macro40_Entry10_DelayMin, Macro40_Entry10_DelaySec, Macro40_Entry10_TimMin, Macro40_Entry10_TimSec, Macro40_Entry10_Protocol, 0, 0, 0, 0,
		         Macro40_Entry11_DelayMin, Macro40_Entry11_DelaySec, Macro40_Entry11_TimMin, Macro40_Entry11_TimSec, Macro40_Entry11_Protocol, 0, 0, 0, 0,
		         Macro40_Entry12_DelayMin, Macro40_Entry12_DelaySec, Macro40_Entry12_TimMin, Macro40_Entry12_TimSec, Macro40_Entry12_Protocol, 0, 0, 0, 0,
		         Macro40_Entry13_DelayMin, Macro40_Entry13_DelaySec, Macro40_Entry13_TimMin, Macro40_Entry13_TimSec, Macro40_Entry13_Protocol, 0, 0, 0, 0,
		         Macro40_Entry14_DelayMin, Macro40_Entry14_DelaySec, Macro40_Entry14_TimMin, Macro40_Entry14_TimSec, Macro40_Entry14_Protocol, 0, 0, 0, 0,
		         Macro40_Entry15_DelayMin, Macro40_Entry15_DelaySec, Macro40_Entry15_TimMin, Macro40_Entry15_TimSec, Macro40_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR40_STRING};

const struct super_macro Macro41 = {Macro41_NumEntries,
		         Macro41_Entry1_DelayMin, Macro41_Entry1_DelaySec, Macro41_Entry1_TimMin, Macro41_Entry1_TimSec, Macro41_Entry1_Protocol, 0, 0, 0, 0,
		         Macro41_Entry2_DelayMin, Macro41_Entry2_DelaySec, Macro41_Entry2_TimMin, Macro41_Entry2_TimSec, Macro41_Entry2_Protocol, 0, 0, 0, 0,
		         Macro41_Entry3_DelayMin, Macro41_Entry3_DelaySec, Macro41_Entry3_TimMin, Macro41_Entry3_TimSec, Macro41_Entry3_Protocol, 0, 0, 0, 0,
		         Macro41_Entry4_DelayMin, Macro41_Entry4_DelaySec, Macro41_Entry4_TimMin, Macro41_Entry4_TimSec, Macro41_Entry4_Protocol, 0, 0, 0, 0,
		         Macro41_Entry5_DelayMin, Macro41_Entry5_DelaySec, Macro41_Entry5_TimMin, Macro41_Entry5_TimSec, Macro41_Entry5_Protocol, 0, 0, 0, 0,
		         Macro41_Entry6_DelayMin, Macro41_Entry6_DelaySec, Macro41_Entry6_TimMin, Macro41_Entry6_TimSec, Macro41_Entry6_Protocol, 0, 0, 0, 0,
		         Macro41_Entry7_DelayMin, Macro41_Entry7_DelaySec, Macro41_Entry7_TimMin, Macro41_Entry7_TimSec, Macro41_Entry7_Protocol, 0, 0, 0, 0,
		         Macro41_Entry8_DelayMin, Macro41_Entry8_DelaySec, Macro41_Entry8_TimMin, Macro41_Entry8_TimSec, Macro41_Entry8_Protocol, 0, 0, 0, 0,
		         Macro41_Entry9_DelayMin, Macro41_Entry9_DelaySec, Macro41_Entry9_TimMin, Macro41_Entry9_TimSec, Macro41_Entry9_Protocol, 0, 0, 0, 0,
		         Macro41_Entry10_DelayMin, Macro41_Entry10_DelaySec, Macro41_Entry10_TimMin, Macro41_Entry10_TimSec, Macro41_Entry10_Protocol, 0, 0, 0, 0,
		         Macro41_Entry11_DelayMin, Macro41_Entry11_DelaySec, Macro41_Entry11_TimMin, Macro41_Entry11_TimSec, Macro41_Entry11_Protocol, 0, 0, 0, 0,
		         Macro41_Entry12_DelayMin, Macro41_Entry12_DelaySec, Macro41_Entry12_TimMin, Macro41_Entry12_TimSec, Macro41_Entry12_Protocol, 0, 0, 0, 0,
		         Macro41_Entry13_DelayMin, Macro41_Entry13_DelaySec, Macro41_Entry13_TimMin, Macro41_Entry13_TimSec, Macro41_Entry13_Protocol, 0, 0, 0, 0,
		         Macro41_Entry14_DelayMin, Macro41_Entry14_DelaySec, Macro41_Entry14_TimMin, Macro41_Entry14_TimSec, Macro41_Entry14_Protocol, 0, 0, 0, 0,
		         Macro41_Entry15_DelayMin, Macro41_Entry15_DelaySec, Macro41_Entry15_TimMin, Macro41_Entry15_TimSec, Macro41_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR41_STRING};

const struct super_macro Macro42 = {Macro42_NumEntries,
		         Macro42_Entry1_DelayMin, Macro42_Entry1_DelaySec, Macro42_Entry1_TimMin, Macro42_Entry1_TimSec, Macro42_Entry1_Protocol, 0, 0, 0, 0,
		         Macro42_Entry2_DelayMin, Macro42_Entry2_DelaySec, Macro42_Entry2_TimMin, Macro42_Entry2_TimSec, Macro42_Entry2_Protocol, 0, 0, 0, 0,
		         Macro42_Entry3_DelayMin, Macro42_Entry3_DelaySec, Macro42_Entry3_TimMin, Macro42_Entry3_TimSec, Macro42_Entry3_Protocol, 0, 0, 0, 0,
		         Macro42_Entry4_DelayMin, Macro42_Entry4_DelaySec, Macro42_Entry4_TimMin, Macro42_Entry4_TimSec, Macro42_Entry4_Protocol, 0, 0, 0, 0,
		         Macro42_Entry5_DelayMin, Macro42_Entry5_DelaySec, Macro42_Entry5_TimMin, Macro42_Entry5_TimSec, Macro42_Entry5_Protocol, 0, 0, 0, 0,
		         Macro42_Entry6_DelayMin, Macro42_Entry6_DelaySec, Macro42_Entry6_TimMin, Macro42_Entry6_TimSec, Macro42_Entry6_Protocol, 0, 0, 0, 0,
		         Macro42_Entry7_DelayMin, Macro42_Entry7_DelaySec, Macro42_Entry7_TimMin, Macro42_Entry7_TimSec, Macro42_Entry7_Protocol, 0, 0, 0, 0,
		         Macro42_Entry8_DelayMin, Macro42_Entry8_DelaySec, Macro42_Entry8_TimMin, Macro42_Entry8_TimSec, Macro42_Entry8_Protocol, 0, 0, 0, 0,
		         Macro42_Entry9_DelayMin, Macro42_Entry9_DelaySec, Macro42_Entry9_TimMin, Macro42_Entry9_TimSec, Macro42_Entry9_Protocol, 0, 0, 0, 0,
		         Macro42_Entry10_DelayMin, Macro42_Entry10_DelaySec, Macro42_Entry10_TimMin, Macro42_Entry10_TimSec, Macro42_Entry10_Protocol, 0, 0, 0, 0,
		         Macro42_Entry11_DelayMin, Macro42_Entry11_DelaySec, Macro42_Entry11_TimMin, Macro42_Entry11_TimSec, Macro42_Entry11_Protocol, 0, 0, 0, 0,
		         Macro42_Entry12_DelayMin, Macro42_Entry12_DelaySec, Macro42_Entry12_TimMin, Macro42_Entry12_TimSec, Macro42_Entry12_Protocol, 0, 0, 0, 0,
		         Macro42_Entry13_DelayMin, Macro42_Entry13_DelaySec, Macro42_Entry13_TimMin, Macro42_Entry13_TimSec, Macro42_Entry13_Protocol, 0, 0, 0, 0,
		         Macro42_Entry14_DelayMin, Macro42_Entry14_DelaySec, Macro42_Entry14_TimMin, Macro42_Entry14_TimSec, Macro42_Entry14_Protocol, 0, 0, 0, 0,
		         Macro42_Entry15_DelayMin, Macro42_Entry15_DelaySec, Macro42_Entry15_TimMin, Macro42_Entry15_TimSec, Macro42_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR42_STRING};

const struct super_macro Macro43 = {Macro43_NumEntries,
		         Macro43_Entry1_DelayMin, Macro43_Entry1_DelaySec, Macro43_Entry1_TimMin, Macro43_Entry1_TimSec, Macro43_Entry1_Protocol, 0, 0, 0, 0,
		         Macro43_Entry2_DelayMin, Macro43_Entry2_DelaySec, Macro43_Entry2_TimMin, Macro43_Entry2_TimSec, Macro43_Entry2_Protocol, 0, 0, 0, 0,
		         Macro43_Entry3_DelayMin, Macro43_Entry3_DelaySec, Macro43_Entry3_TimMin, Macro43_Entry3_TimSec, Macro43_Entry3_Protocol, 0, 0, 0, 0,
		         Macro43_Entry4_DelayMin, Macro43_Entry4_DelaySec, Macro43_Entry4_TimMin, Macro43_Entry4_TimSec, Macro43_Entry4_Protocol, 0, 0, 0, 0,
		         Macro43_Entry5_DelayMin, Macro43_Entry5_DelaySec, Macro43_Entry5_TimMin, Macro43_Entry5_TimSec, Macro43_Entry5_Protocol, 0, 0, 0, 0,
		         Macro43_Entry6_DelayMin, Macro43_Entry6_DelaySec, Macro43_Entry6_TimMin, Macro43_Entry6_TimSec, Macro43_Entry6_Protocol, 0, 0, 0, 0,
		         Macro43_Entry7_DelayMin, Macro43_Entry7_DelaySec, Macro43_Entry7_TimMin, Macro43_Entry7_TimSec, Macro43_Entry7_Protocol, 0, 0, 0, 0,
		         Macro43_Entry8_DelayMin, Macro43_Entry8_DelaySec, Macro43_Entry8_TimMin, Macro43_Entry8_TimSec, Macro43_Entry8_Protocol, 0, 0, 0, 0,
		         Macro43_Entry9_DelayMin, Macro43_Entry9_DelaySec, Macro43_Entry9_TimMin, Macro43_Entry9_TimSec, Macro43_Entry9_Protocol, 0, 0, 0, 0,
		         Macro43_Entry10_DelayMin, Macro43_Entry10_DelaySec, Macro43_Entry10_TimMin, Macro43_Entry10_TimSec, Macro43_Entry10_Protocol, 0, 0, 0, 0,
		         Macro43_Entry11_DelayMin, Macro43_Entry11_DelaySec, Macro43_Entry11_TimMin, Macro43_Entry11_TimSec, Macro43_Entry11_Protocol, 0, 0, 0, 0,
		         Macro43_Entry12_DelayMin, Macro43_Entry12_DelaySec, Macro43_Entry12_TimMin, Macro43_Entry12_TimSec, Macro43_Entry12_Protocol, 0, 0, 0, 0,
		         Macro43_Entry13_DelayMin, Macro43_Entry13_DelaySec, Macro43_Entry13_TimMin, Macro43_Entry13_TimSec, Macro43_Entry13_Protocol, 0, 0, 0, 0,
		         Macro43_Entry14_DelayMin, Macro43_Entry14_DelaySec, Macro43_Entry14_TimMin, Macro43_Entry14_TimSec, Macro43_Entry14_Protocol, 0, 0, 0, 0,
		         Macro43_Entry15_DelayMin, Macro43_Entry15_DelaySec, Macro43_Entry15_TimMin, Macro43_Entry15_TimSec, Macro43_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR43_STRING};

const struct super_macro Macro44 = {Macro44_NumEntries,
		         Macro44_Entry1_DelayMin, Macro44_Entry1_DelaySec, Macro44_Entry1_TimMin, Macro44_Entry1_TimSec, Macro44_Entry1_Protocol, 0, 0, 0, 0,
		         Macro44_Entry2_DelayMin, Macro44_Entry2_DelaySec, Macro44_Entry2_TimMin, Macro44_Entry2_TimSec, Macro44_Entry2_Protocol, 0, 0, 0, 0,
		         Macro44_Entry3_DelayMin, Macro44_Entry3_DelaySec, Macro44_Entry3_TimMin, Macro44_Entry3_TimSec, Macro44_Entry3_Protocol, 0, 0, 0, 0,
		         Macro44_Entry4_DelayMin, Macro44_Entry4_DelaySec, Macro44_Entry4_TimMin, Macro44_Entry4_TimSec, Macro44_Entry4_Protocol, 0, 0, 0, 0,
		         Macro44_Entry5_DelayMin, Macro44_Entry5_DelaySec, Macro44_Entry5_TimMin, Macro44_Entry5_TimSec, Macro44_Entry5_Protocol, 0, 0, 0, 0,
		         Macro44_Entry6_DelayMin, Macro44_Entry6_DelaySec, Macro44_Entry6_TimMin, Macro44_Entry6_TimSec, Macro44_Entry6_Protocol, 0, 0, 0, 0,
		         Macro44_Entry7_DelayMin, Macro44_Entry7_DelaySec, Macro44_Entry7_TimMin, Macro44_Entry7_TimSec, Macro44_Entry7_Protocol, 0, 0, 0, 0,
		         Macro44_Entry8_DelayMin, Macro44_Entry8_DelaySec, Macro44_Entry8_TimMin, Macro44_Entry8_TimSec, Macro44_Entry8_Protocol, 0, 0, 0, 0,
		         Macro44_Entry9_DelayMin, Macro44_Entry9_DelaySec, Macro44_Entry9_TimMin, Macro44_Entry9_TimSec, Macro44_Entry9_Protocol, 0, 0, 0, 0,
		         Macro44_Entry10_DelayMin, Macro44_Entry10_DelaySec, Macro44_Entry10_TimMin, Macro44_Entry10_TimSec, Macro44_Entry10_Protocol, 0, 0, 0, 0,
		         Macro44_Entry11_DelayMin, Macro44_Entry11_DelaySec, Macro44_Entry11_TimMin, Macro44_Entry11_TimSec, Macro44_Entry11_Protocol, 0, 0, 0, 0,
		         Macro44_Entry12_DelayMin, Macro44_Entry12_DelaySec, Macro44_Entry12_TimMin, Macro44_Entry12_TimSec, Macro44_Entry12_Protocol, 0, 0, 0, 0,
		         Macro44_Entry13_DelayMin, Macro44_Entry13_DelaySec, Macro44_Entry13_TimMin, Macro44_Entry13_TimSec, Macro44_Entry13_Protocol, 0, 0, 0, 0,
		         Macro44_Entry14_DelayMin, Macro44_Entry14_DelaySec, Macro44_Entry14_TimMin, Macro44_Entry14_TimSec, Macro44_Entry14_Protocol, 0, 0, 0, 0,
		         Macro44_Entry15_DelayMin, Macro44_Entry15_DelaySec, Macro44_Entry15_TimMin, Macro44_Entry15_TimSec, Macro44_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR44_STRING};

const struct super_macro Macro45 = {Macro45_NumEntries,
		         Macro45_Entry1_DelayMin, Macro45_Entry1_DelaySec, Macro45_Entry1_TimMin, Macro45_Entry1_TimSec, Macro45_Entry1_Protocol, 0, 0, 0, 0,
		         Macro45_Entry2_DelayMin, Macro45_Entry2_DelaySec, Macro45_Entry2_TimMin, Macro45_Entry2_TimSec, Macro45_Entry2_Protocol, 0, 0, 0, 0,
		         Macro45_Entry3_DelayMin, Macro45_Entry3_DelaySec, Macro45_Entry3_TimMin, Macro45_Entry3_TimSec, Macro45_Entry3_Protocol, 0, 0, 0, 0,
		         Macro45_Entry4_DelayMin, Macro45_Entry4_DelaySec, Macro45_Entry4_TimMin, Macro45_Entry4_TimSec, Macro45_Entry4_Protocol, 0, 0, 0, 0,
		         Macro45_Entry5_DelayMin, Macro45_Entry5_DelaySec, Macro45_Entry5_TimMin, Macro45_Entry5_TimSec, Macro45_Entry5_Protocol, 0, 0, 0, 0,
		         Macro45_Entry6_DelayMin, Macro45_Entry6_DelaySec, Macro45_Entry6_TimMin, Macro45_Entry6_TimSec, Macro45_Entry6_Protocol, 0, 0, 0, 0,
		         Macro45_Entry7_DelayMin, Macro45_Entry7_DelaySec, Macro45_Entry7_TimMin, Macro45_Entry7_TimSec, Macro45_Entry7_Protocol, 0, 0, 0, 0,
		         Macro45_Entry8_DelayMin, Macro45_Entry8_DelaySec, Macro45_Entry8_TimMin, Macro45_Entry8_TimSec, Macro45_Entry8_Protocol, 0, 0, 0, 0,
		         Macro45_Entry9_DelayMin, Macro45_Entry9_DelaySec, Macro45_Entry9_TimMin, Macro45_Entry9_TimSec, Macro45_Entry9_Protocol, 0, 0, 0, 0,
		         Macro45_Entry10_DelayMin, Macro45_Entry10_DelaySec, Macro45_Entry10_TimMin, Macro45_Entry10_TimSec, Macro45_Entry10_Protocol, 0, 0, 0, 0,
		         Macro45_Entry11_DelayMin, Macro45_Entry11_DelaySec, Macro45_Entry11_TimMin, Macro45_Entry11_TimSec, Macro45_Entry11_Protocol, 0, 0, 0, 0,
		         Macro45_Entry12_DelayMin, Macro45_Entry12_DelaySec, Macro45_Entry12_TimMin, Macro45_Entry12_TimSec, Macro45_Entry12_Protocol, 0, 0, 0, 0,
		         Macro45_Entry13_DelayMin, Macro45_Entry13_DelaySec, Macro45_Entry13_TimMin, Macro45_Entry13_TimSec, Macro45_Entry13_Protocol, 0, 0, 0, 0,
		         Macro45_Entry14_DelayMin, Macro45_Entry14_DelaySec, Macro45_Entry14_TimMin, Macro45_Entry14_TimSec, Macro45_Entry14_Protocol, 0, 0, 0, 0,
		         Macro45_Entry15_DelayMin, Macro45_Entry15_DelaySec, Macro45_Entry15_TimMin, Macro45_Entry15_TimSec, Macro45_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR45_STRING};

const struct super_macro Macro46 = {Macro46_NumEntries,
		         Macro46_Entry1_DelayMin, Macro46_Entry1_DelaySec, Macro46_Entry1_TimMin, Macro46_Entry1_TimSec, Macro46_Entry1_Protocol, 0, 0, 0, 0,
		         Macro46_Entry2_DelayMin, Macro46_Entry2_DelaySec, Macro46_Entry2_TimMin, Macro46_Entry2_TimSec, Macro46_Entry2_Protocol, 0, 0, 0, 0,
		         Macro46_Entry3_DelayMin, Macro46_Entry3_DelaySec, Macro46_Entry3_TimMin, Macro46_Entry3_TimSec, Macro46_Entry3_Protocol, 0, 0, 0, 0,
		         Macro46_Entry4_DelayMin, Macro46_Entry4_DelaySec, Macro46_Entry4_TimMin, Macro46_Entry4_TimSec, Macro46_Entry4_Protocol, 0, 0, 0, 0,
		         Macro46_Entry5_DelayMin, Macro46_Entry5_DelaySec, Macro46_Entry5_TimMin, Macro46_Entry5_TimSec, Macro46_Entry5_Protocol, 0, 0, 0, 0,
		         Macro46_Entry6_DelayMin, Macro46_Entry6_DelaySec, Macro46_Entry6_TimMin, Macro46_Entry6_TimSec, Macro46_Entry6_Protocol, 0, 0, 0, 0,
		         Macro46_Entry7_DelayMin, Macro46_Entry7_DelaySec, Macro46_Entry7_TimMin, Macro46_Entry7_TimSec, Macro46_Entry7_Protocol, 0, 0, 0, 0,
		         Macro46_Entry8_DelayMin, Macro46_Entry8_DelaySec, Macro46_Entry8_TimMin, Macro46_Entry8_TimSec, Macro46_Entry8_Protocol, 0, 0, 0, 0,
		         Macro46_Entry9_DelayMin, Macro46_Entry9_DelaySec, Macro46_Entry9_TimMin, Macro46_Entry9_TimSec, Macro46_Entry9_Protocol, 0, 0, 0, 0,
		         Macro46_Entry10_DelayMin, Macro46_Entry10_DelaySec, Macro46_Entry10_TimMin, Macro46_Entry10_TimSec, Macro46_Entry10_Protocol, 0, 0, 0, 0,
		         Macro46_Entry11_DelayMin, Macro46_Entry11_DelaySec, Macro46_Entry11_TimMin, Macro46_Entry11_TimSec, Macro46_Entry11_Protocol, 0, 0, 0, 0,
		         Macro46_Entry12_DelayMin, Macro46_Entry12_DelaySec, Macro46_Entry12_TimMin, Macro46_Entry12_TimSec, Macro46_Entry12_Protocol, 0, 0, 0, 0,
		         Macro46_Entry13_DelayMin, Macro46_Entry13_DelaySec, Macro46_Entry13_TimMin, Macro46_Entry13_TimSec, Macro46_Entry13_Protocol, 0, 0, 0, 0,
		         Macro46_Entry14_DelayMin, Macro46_Entry14_DelaySec, Macro46_Entry14_TimMin, Macro46_Entry14_TimSec, Macro46_Entry14_Protocol, 0, 0, 0, 0,
		         Macro46_Entry15_DelayMin, Macro46_Entry15_DelaySec, Macro46_Entry15_TimMin, Macro46_Entry15_TimSec, Macro46_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR46_STRING};

const struct super_macro Macro47 = {Macro47_NumEntries,
		         Macro47_Entry1_DelayMin, Macro47_Entry1_DelaySec, Macro47_Entry1_TimMin, Macro47_Entry1_TimSec, Macro47_Entry1_Protocol, 0, 0, 0, 0,
		         Macro47_Entry2_DelayMin, Macro47_Entry2_DelaySec, Macro47_Entry2_TimMin, Macro47_Entry2_TimSec, Macro47_Entry2_Protocol, 0, 0, 0, 0,
		         Macro47_Entry3_DelayMin, Macro47_Entry3_DelaySec, Macro47_Entry3_TimMin, Macro47_Entry3_TimSec, Macro47_Entry3_Protocol, 0, 0, 0, 0,
		         Macro47_Entry4_DelayMin, Macro47_Entry4_DelaySec, Macro47_Entry4_TimMin, Macro47_Entry4_TimSec, Macro47_Entry4_Protocol, 0, 0, 0, 0,
		         Macro47_Entry5_DelayMin, Macro47_Entry5_DelaySec, Macro47_Entry5_TimMin, Macro47_Entry5_TimSec, Macro47_Entry5_Protocol, 0, 0, 0, 0,
		         Macro47_Entry6_DelayMin, Macro47_Entry6_DelaySec, Macro47_Entry6_TimMin, Macro47_Entry6_TimSec, Macro47_Entry6_Protocol, 0, 0, 0, 0,
		         Macro47_Entry7_DelayMin, Macro47_Entry7_DelaySec, Macro47_Entry7_TimMin, Macro47_Entry7_TimSec, Macro47_Entry7_Protocol, 0, 0, 0, 0,
		         Macro47_Entry8_DelayMin, Macro47_Entry8_DelaySec, Macro47_Entry8_TimMin, Macro47_Entry8_TimSec, Macro47_Entry8_Protocol, 0, 0, 0, 0,
		         Macro47_Entry9_DelayMin, Macro47_Entry9_DelaySec, Macro47_Entry9_TimMin, Macro47_Entry9_TimSec, Macro47_Entry9_Protocol, 0, 0, 0, 0,
		         Macro47_Entry10_DelayMin, Macro47_Entry10_DelaySec, Macro47_Entry10_TimMin, Macro47_Entry10_TimSec, Macro47_Entry10_Protocol, 0, 0, 0, 0,
		         Macro47_Entry11_DelayMin, Macro47_Entry11_DelaySec, Macro47_Entry11_TimMin, Macro47_Entry11_TimSec, Macro47_Entry11_Protocol, 0, 0, 0, 0,
		         Macro47_Entry12_DelayMin, Macro47_Entry12_DelaySec, Macro47_Entry12_TimMin, Macro47_Entry12_TimSec, Macro47_Entry12_Protocol, 0, 0, 0, 0,
		         Macro47_Entry13_DelayMin, Macro47_Entry13_DelaySec, Macro47_Entry13_TimMin, Macro47_Entry13_TimSec, Macro47_Entry13_Protocol, 0, 0, 0, 0,
		         Macro47_Entry14_DelayMin, Macro47_Entry14_DelaySec, Macro47_Entry14_TimMin, Macro47_Entry14_TimSec, Macro47_Entry14_Protocol, 0, 0, 0, 0,
		         Macro47_Entry15_DelayMin, Macro47_Entry15_DelaySec, Macro47_Entry15_TimMin, Macro47_Entry15_TimSec, Macro47_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR47_STRING};

const struct super_macro Macro48 = {Macro48_NumEntries,
		         Macro48_Entry1_DelayMin, Macro48_Entry1_DelaySec, Macro48_Entry1_TimMin, Macro48_Entry1_TimSec, Macro48_Entry1_Protocol, 0, 0, 0, 0,
		         Macro48_Entry2_DelayMin, Macro48_Entry2_DelaySec, Macro48_Entry2_TimMin, Macro48_Entry2_TimSec, Macro48_Entry2_Protocol, 0, 0, 0, 0,
		         Macro48_Entry3_DelayMin, Macro48_Entry3_DelaySec, Macro48_Entry3_TimMin, Macro48_Entry3_TimSec, Macro48_Entry3_Protocol, 0, 0, 0, 0,
		         Macro48_Entry4_DelayMin, Macro48_Entry4_DelaySec, Macro48_Entry4_TimMin, Macro48_Entry4_TimSec, Macro48_Entry4_Protocol, 0, 0, 0, 0,
		         Macro48_Entry5_DelayMin, Macro48_Entry5_DelaySec, Macro48_Entry5_TimMin, Macro48_Entry5_TimSec, Macro48_Entry5_Protocol, 0, 0, 0, 0,
		         Macro48_Entry6_DelayMin, Macro48_Entry6_DelaySec, Macro48_Entry6_TimMin, Macro48_Entry6_TimSec, Macro48_Entry6_Protocol, 0, 0, 0, 0,
		         Macro48_Entry7_DelayMin, Macro48_Entry7_DelaySec, Macro48_Entry7_TimMin, Macro48_Entry7_TimSec, Macro48_Entry7_Protocol, 0, 0, 0, 0,
		         Macro48_Entry8_DelayMin, Macro48_Entry8_DelaySec, Macro48_Entry8_TimMin, Macro48_Entry8_TimSec, Macro48_Entry8_Protocol, 0, 0, 0, 0,
		         Macro48_Entry9_DelayMin, Macro48_Entry9_DelaySec, Macro48_Entry9_TimMin, Macro48_Entry9_TimSec, Macro48_Entry9_Protocol, 0, 0, 0, 0,
		         Macro48_Entry10_DelayMin, Macro48_Entry10_DelaySec, Macro48_Entry10_TimMin, Macro48_Entry10_TimSec, Macro48_Entry10_Protocol, 0, 0, 0, 0,
		         Macro48_Entry11_DelayMin, Macro48_Entry11_DelaySec, Macro48_Entry11_TimMin, Macro48_Entry11_TimSec, Macro48_Entry11_Protocol, 0, 0, 0, 0,
		         Macro48_Entry12_DelayMin, Macro48_Entry12_DelaySec, Macro48_Entry12_TimMin, Macro48_Entry12_TimSec, Macro48_Entry12_Protocol, 0, 0, 0, 0,
		         Macro48_Entry13_DelayMin, Macro48_Entry13_DelaySec, Macro48_Entry13_TimMin, Macro48_Entry13_TimSec, Macro48_Entry13_Protocol, 0, 0, 0, 0,
		         Macro48_Entry14_DelayMin, Macro48_Entry14_DelaySec, Macro48_Entry14_TimMin, Macro48_Entry14_TimSec, Macro48_Entry14_Protocol, 0, 0, 0, 0,
		         Macro48_Entry15_DelayMin, Macro48_Entry15_DelaySec, Macro48_Entry15_TimMin, Macro48_Entry15_TimSec, Macro48_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR48_STRING};

const struct super_macro Macro49 = {Macro49_NumEntries,
		         Macro49_Entry1_DelayMin, Macro49_Entry1_DelaySec, Macro49_Entry1_TimMin, Macro49_Entry1_TimSec, Macro49_Entry1_Protocol, 0, 0, 0, 0,
		         Macro49_Entry2_DelayMin, Macro49_Entry2_DelaySec, Macro49_Entry2_TimMin, Macro49_Entry2_TimSec, Macro49_Entry2_Protocol, 0, 0, 0, 0,
		         Macro49_Entry3_DelayMin, Macro49_Entry3_DelaySec, Macro49_Entry3_TimMin, Macro49_Entry3_TimSec, Macro49_Entry3_Protocol, 0, 0, 0, 0,
		         Macro49_Entry4_DelayMin, Macro49_Entry4_DelaySec, Macro49_Entry4_TimMin, Macro49_Entry4_TimSec, Macro49_Entry4_Protocol, 0, 0, 0, 0,
		         Macro49_Entry5_DelayMin, Macro49_Entry5_DelaySec, Macro49_Entry5_TimMin, Macro49_Entry5_TimSec, Macro49_Entry5_Protocol, 0, 0, 0, 0,
		         Macro49_Entry6_DelayMin, Macro49_Entry6_DelaySec, Macro49_Entry6_TimMin, Macro49_Entry6_TimSec, Macro49_Entry6_Protocol, 0, 0, 0, 0,
		         Macro49_Entry7_DelayMin, Macro49_Entry7_DelaySec, Macro49_Entry7_TimMin, Macro49_Entry7_TimSec, Macro49_Entry7_Protocol, 0, 0, 0, 0,
		         Macro49_Entry8_DelayMin, Macro49_Entry8_DelaySec, Macro49_Entry8_TimMin, Macro49_Entry8_TimSec, Macro49_Entry8_Protocol, 0, 0, 0, 0,
		         Macro49_Entry9_DelayMin, Macro49_Entry9_DelaySec, Macro49_Entry9_TimMin, Macro49_Entry9_TimSec, Macro49_Entry9_Protocol, 0, 0, 0, 0,
		         Macro49_Entry10_DelayMin, Macro49_Entry10_DelaySec, Macro49_Entry10_TimMin, Macro49_Entry10_TimSec, Macro49_Entry10_Protocol, 0, 0, 0, 0,
		         Macro49_Entry11_DelayMin, Macro49_Entry11_DelaySec, Macro49_Entry11_TimMin, Macro49_Entry11_TimSec, Macro49_Entry11_Protocol, 0, 0, 0, 0,
		         Macro49_Entry12_DelayMin, Macro49_Entry12_DelaySec, Macro49_Entry12_TimMin, Macro49_Entry12_TimSec, Macro49_Entry12_Protocol, 0, 0, 0, 0,
		         Macro49_Entry13_DelayMin, Macro49_Entry13_DelaySec, Macro49_Entry13_TimMin, Macro49_Entry13_TimSec, Macro49_Entry13_Protocol, 0, 0, 0, 0,
		         Macro49_Entry14_DelayMin, Macro49_Entry14_DelaySec, Macro49_Entry14_TimMin, Macro49_Entry14_TimSec, Macro49_Entry14_Protocol, 0, 0, 0, 0,
		         Macro49_Entry15_DelayMin, Macro49_Entry15_DelaySec, Macro49_Entry15_TimMin, Macro49_Entry15_TimSec, Macro49_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR49_STRING};

const struct super_macro Macro50 = {Macro50_NumEntries,
		         Macro50_Entry1_DelayMin, Macro50_Entry1_DelaySec, Macro50_Entry1_TimMin, Macro50_Entry1_TimSec, Macro50_Entry1_Protocol, 0, 0, 0, 0,
		         Macro50_Entry2_DelayMin, Macro50_Entry2_DelaySec, Macro50_Entry2_TimMin, Macro50_Entry2_TimSec, Macro50_Entry2_Protocol, 0, 0, 0, 0,
		         Macro50_Entry3_DelayMin, Macro50_Entry3_DelaySec, Macro50_Entry3_TimMin, Macro50_Entry3_TimSec, Macro50_Entry3_Protocol, 0, 0, 0, 0,
		         Macro50_Entry4_DelayMin, Macro50_Entry4_DelaySec, Macro50_Entry4_TimMin, Macro50_Entry4_TimSec, Macro50_Entry4_Protocol, 0, 0, 0, 0,
		         Macro50_Entry5_DelayMin, Macro50_Entry5_DelaySec, Macro50_Entry5_TimMin, Macro50_Entry5_TimSec, Macro50_Entry5_Protocol, 0, 0, 0, 0,
		         Macro50_Entry6_DelayMin, Macro50_Entry6_DelaySec, Macro50_Entry6_TimMin, Macro50_Entry6_TimSec, Macro50_Entry6_Protocol, 0, 0, 0, 0,
		         Macro50_Entry7_DelayMin, Macro50_Entry7_DelaySec, Macro50_Entry7_TimMin, Macro50_Entry7_TimSec, Macro50_Entry7_Protocol, 0, 0, 0, 0,
		         Macro50_Entry8_DelayMin, Macro50_Entry8_DelaySec, Macro50_Entry8_TimMin, Macro50_Entry8_TimSec, Macro50_Entry8_Protocol, 0, 0, 0, 0,
		         Macro50_Entry9_DelayMin, Macro50_Entry9_DelaySec, Macro50_Entry9_TimMin, Macro50_Entry9_TimSec, Macro50_Entry9_Protocol, 0, 0, 0, 0,
		         Macro50_Entry10_DelayMin, Macro50_Entry10_DelaySec, Macro50_Entry10_TimMin, Macro50_Entry10_TimSec, Macro50_Entry10_Protocol, 0, 0, 0, 0,
		         Macro50_Entry11_DelayMin, Macro50_Entry11_DelaySec, Macro50_Entry11_TimMin, Macro50_Entry11_TimSec, Macro50_Entry11_Protocol, 0, 0, 0, 0,
		         Macro50_Entry12_DelayMin, Macro50_Entry12_DelaySec, Macro50_Entry12_TimMin, Macro50_Entry12_TimSec, Macro50_Entry12_Protocol, 0, 0, 0, 0,
		         Macro50_Entry13_DelayMin, Macro50_Entry13_DelaySec, Macro50_Entry13_TimMin, Macro50_Entry13_TimSec, Macro50_Entry13_Protocol, 0, 0, 0, 0,
		         Macro50_Entry14_DelayMin, Macro50_Entry14_DelaySec, Macro50_Entry14_TimMin, Macro50_Entry14_TimSec, Macro50_Entry14_Protocol, 0, 0, 0, 0,
		         Macro50_Entry15_DelayMin, Macro50_Entry15_DelaySec, Macro50_Entry15_TimMin, Macro50_Entry15_TimSec, Macro50_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR50_STRING};

const struct super_macro Macro51 = {Macro51_NumEntries,
		         Macro51_Entry1_DelayMin, Macro51_Entry1_DelaySec, Macro51_Entry1_TimMin, Macro51_Entry1_TimSec, Macro51_Entry1_Protocol, 0, 0, 0, 0,
		         Macro51_Entry2_DelayMin, Macro51_Entry2_DelaySec, Macro51_Entry2_TimMin, Macro51_Entry2_TimSec, Macro51_Entry2_Protocol, 0, 0, 0, 0,
		         Macro51_Entry3_DelayMin, Macro51_Entry3_DelaySec, Macro51_Entry3_TimMin, Macro51_Entry3_TimSec, Macro51_Entry3_Protocol, 0, 0, 0, 0,
		         Macro51_Entry4_DelayMin, Macro51_Entry4_DelaySec, Macro51_Entry4_TimMin, Macro51_Entry4_TimSec, Macro51_Entry4_Protocol, 0, 0, 0, 0,
		         Macro51_Entry5_DelayMin, Macro51_Entry5_DelaySec, Macro51_Entry5_TimMin, Macro51_Entry5_TimSec, Macro51_Entry5_Protocol, 0, 0, 0, 0,
		         Macro51_Entry6_DelayMin, Macro51_Entry6_DelaySec, Macro51_Entry6_TimMin, Macro51_Entry6_TimSec, Macro51_Entry6_Protocol, 0, 0, 0, 0,
		         Macro51_Entry7_DelayMin, Macro51_Entry7_DelaySec, Macro51_Entry7_TimMin, Macro51_Entry7_TimSec, Macro51_Entry7_Protocol, 0, 0, 0, 0,
		         Macro51_Entry8_DelayMin, Macro51_Entry8_DelaySec, Macro51_Entry8_TimMin, Macro51_Entry8_TimSec, Macro51_Entry8_Protocol, 0, 0, 0, 0,
		         Macro51_Entry9_DelayMin, Macro51_Entry9_DelaySec, Macro51_Entry9_TimMin, Macro51_Entry9_TimSec, Macro51_Entry9_Protocol, 0, 0, 0, 0,
		         Macro51_Entry10_DelayMin, Macro51_Entry10_DelaySec, Macro51_Entry10_TimMin, Macro51_Entry10_TimSec, Macro51_Entry10_Protocol, 0, 0, 0, 0,
		         Macro51_Entry11_DelayMin, Macro51_Entry11_DelaySec, Macro51_Entry11_TimMin, Macro51_Entry11_TimSec, Macro51_Entry11_Protocol, 0, 0, 0, 0,
		         Macro51_Entry12_DelayMin, Macro51_Entry12_DelaySec, Macro51_Entry12_TimMin, Macro51_Entry12_TimSec, Macro51_Entry12_Protocol, 0, 0, 0, 0,
		         Macro51_Entry13_DelayMin, Macro51_Entry13_DelaySec, Macro51_Entry13_TimMin, Macro51_Entry13_TimSec, Macro51_Entry13_Protocol, 0, 0, 0, 0,
		         Macro51_Entry14_DelayMin, Macro51_Entry14_DelaySec, Macro51_Entry14_TimMin, Macro51_Entry14_TimSec, Macro51_Entry14_Protocol, 0, 0, 0, 0,
		         Macro51_Entry15_DelayMin, Macro51_Entry15_DelaySec, Macro51_Entry15_TimMin, Macro51_Entry15_TimSec, Macro51_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR51_STRING};

const struct super_macro Macro52 = {Macro52_NumEntries,
		         Macro52_Entry1_DelayMin, Macro52_Entry1_DelaySec, Macro52_Entry1_TimMin, Macro52_Entry1_TimSec, Macro52_Entry1_Protocol, 0, 0, 0, 0,
		         Macro52_Entry2_DelayMin, Macro52_Entry2_DelaySec, Macro52_Entry2_TimMin, Macro52_Entry2_TimSec, Macro52_Entry2_Protocol, 0, 0, 0, 0,
		         Macro52_Entry3_DelayMin, Macro52_Entry3_DelaySec, Macro52_Entry3_TimMin, Macro52_Entry3_TimSec, Macro52_Entry3_Protocol, 0, 0, 0, 0,
		         Macro52_Entry4_DelayMin, Macro52_Entry4_DelaySec, Macro52_Entry4_TimMin, Macro52_Entry4_TimSec, Macro52_Entry4_Protocol, 0, 0, 0, 0,
		         Macro52_Entry5_DelayMin, Macro52_Entry5_DelaySec, Macro52_Entry5_TimMin, Macro52_Entry5_TimSec, Macro52_Entry5_Protocol, 0, 0, 0, 0,
		         Macro52_Entry6_DelayMin, Macro52_Entry6_DelaySec, Macro52_Entry6_TimMin, Macro52_Entry6_TimSec, Macro52_Entry6_Protocol, 0, 0, 0, 0,
		         Macro52_Entry7_DelayMin, Macro52_Entry7_DelaySec, Macro52_Entry7_TimMin, Macro52_Entry7_TimSec, Macro52_Entry7_Protocol, 0, 0, 0, 0,
		         Macro52_Entry8_DelayMin, Macro52_Entry8_DelaySec, Macro52_Entry8_TimMin, Macro52_Entry8_TimSec, Macro52_Entry8_Protocol, 0, 0, 0, 0,
		         Macro52_Entry9_DelayMin, Macro52_Entry9_DelaySec, Macro52_Entry9_TimMin, Macro52_Entry9_TimSec, Macro52_Entry9_Protocol, 0, 0, 0, 0,
		         Macro52_Entry10_DelayMin, Macro52_Entry10_DelaySec, Macro52_Entry10_TimMin, Macro52_Entry10_TimSec, Macro52_Entry10_Protocol, 0, 0, 0, 0,
		         Macro52_Entry11_DelayMin, Macro52_Entry11_DelaySec, Macro52_Entry11_TimMin, Macro52_Entry11_TimSec, Macro52_Entry11_Protocol, 0, 0, 0, 0,
		         Macro52_Entry12_DelayMin, Macro52_Entry12_DelaySec, Macro52_Entry12_TimMin, Macro52_Entry12_TimSec, Macro52_Entry12_Protocol, 0, 0, 0, 0,
		         Macro52_Entry13_DelayMin, Macro52_Entry13_DelaySec, Macro52_Entry13_TimMin, Macro52_Entry13_TimSec, Macro52_Entry13_Protocol, 0, 0, 0, 0,
		         Macro52_Entry14_DelayMin, Macro52_Entry14_DelaySec, Macro52_Entry14_TimMin, Macro52_Entry14_TimSec, Macro52_Entry14_Protocol, 0, 0, 0, 0,
		         Macro52_Entry15_DelayMin, Macro52_Entry15_DelaySec, Macro52_Entry15_TimMin, Macro52_Entry15_TimSec, Macro52_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR52_STRING};

const struct super_macro Macro53 = {Macro53_NumEntries,
		         Macro53_Entry1_DelayMin, Macro53_Entry1_DelaySec, Macro53_Entry1_TimMin, Macro53_Entry1_TimSec, Macro53_Entry1_Protocol, 0, 0, 0, 0,
		         Macro53_Entry2_DelayMin, Macro53_Entry2_DelaySec, Macro53_Entry2_TimMin, Macro53_Entry2_TimSec, Macro53_Entry2_Protocol, 0, 0, 0, 0,
		         Macro53_Entry3_DelayMin, Macro53_Entry3_DelaySec, Macro53_Entry3_TimMin, Macro53_Entry3_TimSec, Macro53_Entry3_Protocol, 0, 0, 0, 0,
		         Macro53_Entry4_DelayMin, Macro53_Entry4_DelaySec, Macro53_Entry4_TimMin, Macro53_Entry4_TimSec, Macro53_Entry4_Protocol, 0, 0, 0, 0,
		         Macro53_Entry5_DelayMin, Macro53_Entry5_DelaySec, Macro53_Entry5_TimMin, Macro53_Entry5_TimSec, Macro53_Entry5_Protocol, 0, 0, 0, 0,
		         Macro53_Entry6_DelayMin, Macro53_Entry6_DelaySec, Macro53_Entry6_TimMin, Macro53_Entry6_TimSec, Macro53_Entry6_Protocol, 0, 0, 0, 0,
		         Macro53_Entry7_DelayMin, Macro53_Entry7_DelaySec, Macro53_Entry7_TimMin, Macro53_Entry7_TimSec, Macro53_Entry7_Protocol, 0, 0, 0, 0,
		         Macro53_Entry8_DelayMin, Macro53_Entry8_DelaySec, Macro53_Entry8_TimMin, Macro53_Entry8_TimSec, Macro53_Entry8_Protocol, 0, 0, 0, 0,
		         Macro53_Entry9_DelayMin, Macro53_Entry9_DelaySec, Macro53_Entry9_TimMin, Macro53_Entry9_TimSec, Macro53_Entry9_Protocol, 0, 0, 0, 0,
		         Macro53_Entry10_DelayMin, Macro53_Entry10_DelaySec, Macro53_Entry10_TimMin, Macro53_Entry10_TimSec, Macro53_Entry10_Protocol, 0, 0, 0, 0,
		         Macro53_Entry11_DelayMin, Macro53_Entry11_DelaySec, Macro53_Entry11_TimMin, Macro53_Entry11_TimSec, Macro53_Entry11_Protocol, 0, 0, 0, 0,
		         Macro53_Entry12_DelayMin, Macro53_Entry12_DelaySec, Macro53_Entry12_TimMin, Macro53_Entry12_TimSec, Macro53_Entry12_Protocol, 0, 0, 0, 0,
		         Macro53_Entry13_DelayMin, Macro53_Entry13_DelaySec, Macro53_Entry13_TimMin, Macro53_Entry13_TimSec, Macro53_Entry13_Protocol, 0, 0, 0, 0,
		         Macro53_Entry14_DelayMin, Macro53_Entry14_DelaySec, Macro53_Entry14_TimMin, Macro53_Entry14_TimSec, Macro53_Entry14_Protocol, 0, 0, 0, 0,
		         Macro53_Entry15_DelayMin, Macro53_Entry15_DelaySec, Macro53_Entry15_TimMin, Macro53_Entry15_TimSec, Macro53_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR53_STRING};

const struct super_macro Macro54 = {Macro54_NumEntries,
		         Macro54_Entry1_DelayMin, Macro54_Entry1_DelaySec, Macro54_Entry1_TimMin, Macro54_Entry1_TimSec, Macro54_Entry1_Protocol, 0, 0, 0, 0,
		         Macro54_Entry2_DelayMin, Macro54_Entry2_DelaySec, Macro54_Entry2_TimMin, Macro54_Entry2_TimSec, Macro54_Entry2_Protocol, 0, 0, 0, 0,
		         Macro54_Entry3_DelayMin, Macro54_Entry3_DelaySec, Macro54_Entry3_TimMin, Macro54_Entry3_TimSec, Macro54_Entry3_Protocol, 0, 0, 0, 0,
		         Macro54_Entry4_DelayMin, Macro54_Entry4_DelaySec, Macro54_Entry4_TimMin, Macro54_Entry4_TimSec, Macro54_Entry4_Protocol, 0, 0, 0, 0,
		         Macro54_Entry5_DelayMin, Macro54_Entry5_DelaySec, Macro54_Entry5_TimMin, Macro54_Entry5_TimSec, Macro54_Entry5_Protocol, 0, 0, 0, 0,
		         Macro54_Entry6_DelayMin, Macro54_Entry6_DelaySec, Macro54_Entry6_TimMin, Macro54_Entry6_TimSec, Macro54_Entry6_Protocol, 0, 0, 0, 0,
		         Macro54_Entry7_DelayMin, Macro54_Entry7_DelaySec, Macro54_Entry7_TimMin, Macro54_Entry7_TimSec, Macro54_Entry7_Protocol, 0, 0, 0, 0,
		         Macro54_Entry8_DelayMin, Macro54_Entry8_DelaySec, Macro54_Entry8_TimMin, Macro54_Entry8_TimSec, Macro54_Entry8_Protocol, 0, 0, 0, 0,
		         Macro54_Entry9_DelayMin, Macro54_Entry9_DelaySec, Macro54_Entry9_TimMin, Macro54_Entry9_TimSec, Macro54_Entry9_Protocol, 0, 0, 0, 0,
		         Macro54_Entry10_DelayMin, Macro54_Entry10_DelaySec, Macro54_Entry10_TimMin, Macro54_Entry10_TimSec, Macro54_Entry10_Protocol, 0, 0, 0, 0,
		         Macro54_Entry11_DelayMin, Macro54_Entry11_DelaySec, Macro54_Entry11_TimMin, Macro54_Entry11_TimSec, Macro54_Entry11_Protocol, 0, 0, 0, 0,
		         Macro54_Entry12_DelayMin, Macro54_Entry12_DelaySec, Macro54_Entry12_TimMin, Macro54_Entry12_TimSec, Macro54_Entry12_Protocol, 0, 0, 0, 0,
		         Macro54_Entry13_DelayMin, Macro54_Entry13_DelaySec, Macro54_Entry13_TimMin, Macro54_Entry13_TimSec, Macro54_Entry13_Protocol, 0, 0, 0, 0,
		         Macro54_Entry14_DelayMin, Macro54_Entry14_DelaySec, Macro54_Entry14_TimMin, Macro54_Entry14_TimSec, Macro54_Entry14_Protocol, 0, 0, 0, 0,
		         Macro54_Entry15_DelayMin, Macro54_Entry15_DelaySec, Macro54_Entry15_TimMin, Macro54_Entry15_TimSec, Macro54_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR54_STRING};

const struct super_macro Macro55 = {Macro55_NumEntries,
		         Macro55_Entry1_DelayMin, Macro55_Entry1_DelaySec, Macro55_Entry1_TimMin, Macro55_Entry1_TimSec, Macro55_Entry1_Protocol, 0, 0, 0, 0,
		         Macro55_Entry2_DelayMin, Macro55_Entry2_DelaySec, Macro55_Entry2_TimMin, Macro55_Entry2_TimSec, Macro55_Entry2_Protocol, 0, 0, 0, 0,
		         Macro55_Entry3_DelayMin, Macro55_Entry3_DelaySec, Macro55_Entry3_TimMin, Macro55_Entry3_TimSec, Macro55_Entry3_Protocol, 0, 0, 0, 0,
		         Macro55_Entry4_DelayMin, Macro55_Entry4_DelaySec, Macro55_Entry4_TimMin, Macro55_Entry4_TimSec, Macro55_Entry4_Protocol, 0, 0, 0, 0,
		         Macro55_Entry5_DelayMin, Macro55_Entry5_DelaySec, Macro55_Entry5_TimMin, Macro55_Entry5_TimSec, Macro55_Entry5_Protocol, 0, 0, 0, 0,
		         Macro55_Entry6_DelayMin, Macro55_Entry6_DelaySec, Macro55_Entry6_TimMin, Macro55_Entry6_TimSec, Macro55_Entry6_Protocol, 0, 0, 0, 0,
		         Macro55_Entry7_DelayMin, Macro55_Entry7_DelaySec, Macro55_Entry7_TimMin, Macro55_Entry7_TimSec, Macro55_Entry7_Protocol, 0, 0, 0, 0,
		         Macro55_Entry8_DelayMin, Macro55_Entry8_DelaySec, Macro55_Entry8_TimMin, Macro55_Entry8_TimSec, Macro55_Entry8_Protocol, 0, 0, 0, 0,
		         Macro55_Entry9_DelayMin, Macro55_Entry9_DelaySec, Macro55_Entry9_TimMin, Macro55_Entry9_TimSec, Macro55_Entry9_Protocol, 0, 0, 0, 0,
		         Macro55_Entry10_DelayMin, Macro55_Entry10_DelaySec, Macro55_Entry10_TimMin, Macro55_Entry10_TimSec, Macro55_Entry10_Protocol, 0, 0, 0, 0,
		         Macro55_Entry11_DelayMin, Macro55_Entry11_DelaySec, Macro55_Entry11_TimMin, Macro55_Entry11_TimSec, Macro55_Entry11_Protocol, 0, 0, 0, 0,
		         Macro55_Entry12_DelayMin, Macro55_Entry12_DelaySec, Macro55_Entry12_TimMin, Macro55_Entry12_TimSec, Macro55_Entry12_Protocol, 0, 0, 0, 0,
		         Macro55_Entry13_DelayMin, Macro55_Entry13_DelaySec, Macro55_Entry13_TimMin, Macro55_Entry13_TimSec, Macro55_Entry13_Protocol, 0, 0, 0, 0,
		         Macro55_Entry14_DelayMin, Macro55_Entry14_DelaySec, Macro55_Entry14_TimMin, Macro55_Entry14_TimSec, Macro55_Entry14_Protocol, 0, 0, 0, 0,
		         Macro55_Entry15_DelayMin, Macro55_Entry15_DelaySec, Macro55_Entry15_TimMin, Macro55_Entry15_TimSec, Macro55_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR55_STRING};

const struct super_macro Macro56 = {Macro56_NumEntries,
		         Macro56_Entry1_DelayMin, Macro56_Entry1_DelaySec, Macro56_Entry1_TimMin, Macro56_Entry1_TimSec, Macro56_Entry1_Protocol, 0, 0, 0, 0,
		         Macro56_Entry2_DelayMin, Macro56_Entry2_DelaySec, Macro56_Entry2_TimMin, Macro56_Entry2_TimSec, Macro56_Entry2_Protocol, 0, 0, 0, 0,
		         Macro56_Entry3_DelayMin, Macro56_Entry3_DelaySec, Macro56_Entry3_TimMin, Macro56_Entry3_TimSec, Macro56_Entry3_Protocol, 0, 0, 0, 0,
		         Macro56_Entry4_DelayMin, Macro56_Entry4_DelaySec, Macro56_Entry4_TimMin, Macro56_Entry4_TimSec, Macro56_Entry4_Protocol, 0, 0, 0, 0,
		         Macro56_Entry5_DelayMin, Macro56_Entry5_DelaySec, Macro56_Entry5_TimMin, Macro56_Entry5_TimSec, Macro56_Entry5_Protocol, 0, 0, 0, 0,
		         Macro56_Entry6_DelayMin, Macro56_Entry6_DelaySec, Macro56_Entry6_TimMin, Macro56_Entry6_TimSec, Macro56_Entry6_Protocol, 0, 0, 0, 0,
		         Macro56_Entry7_DelayMin, Macro56_Entry7_DelaySec, Macro56_Entry7_TimMin, Macro56_Entry7_TimSec, Macro56_Entry7_Protocol, 0, 0, 0, 0,
		         Macro56_Entry8_DelayMin, Macro56_Entry8_DelaySec, Macro56_Entry8_TimMin, Macro56_Entry8_TimSec, Macro56_Entry8_Protocol, 0, 0, 0, 0,
		         Macro56_Entry9_DelayMin, Macro56_Entry9_DelaySec, Macro56_Entry9_TimMin, Macro56_Entry9_TimSec, Macro56_Entry9_Protocol, 0, 0, 0, 0,
		         Macro56_Entry10_DelayMin, Macro56_Entry10_DelaySec, Macro56_Entry10_TimMin, Macro56_Entry10_TimSec, Macro56_Entry10_Protocol, 0, 0, 0, 0,
		         Macro56_Entry11_DelayMin, Macro56_Entry11_DelaySec, Macro56_Entry11_TimMin, Macro56_Entry11_TimSec, Macro56_Entry11_Protocol, 0, 0, 0, 0,
		         Macro56_Entry12_DelayMin, Macro56_Entry12_DelaySec, Macro56_Entry12_TimMin, Macro56_Entry12_TimSec, Macro56_Entry12_Protocol, 0, 0, 0, 0,
		         Macro56_Entry13_DelayMin, Macro56_Entry13_DelaySec, Macro56_Entry13_TimMin, Macro56_Entry13_TimSec, Macro56_Entry13_Protocol, 0, 0, 0, 0,
		         Macro56_Entry14_DelayMin, Macro56_Entry14_DelaySec, Macro56_Entry14_TimMin, Macro56_Entry14_TimSec, Macro56_Entry14_Protocol, 0, 0, 0, 0,
		         Macro56_Entry15_DelayMin, Macro56_Entry15_DelaySec, Macro56_Entry15_TimMin, Macro56_Entry15_TimSec, Macro56_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR56_STRING};

const struct super_macro Macro57 = {Macro57_NumEntries,
		         Macro57_Entry1_DelayMin, Macro57_Entry1_DelaySec, Macro57_Entry1_TimMin, Macro57_Entry1_TimSec, Macro57_Entry1_Protocol, 0, 0, 0, 0,
		         Macro57_Entry2_DelayMin, Macro57_Entry2_DelaySec, Macro57_Entry2_TimMin, Macro57_Entry2_TimSec, Macro57_Entry2_Protocol, 0, 0, 0, 0,
		         Macro57_Entry3_DelayMin, Macro57_Entry3_DelaySec, Macro57_Entry3_TimMin, Macro57_Entry3_TimSec, Macro57_Entry3_Protocol, 0, 0, 0, 0,
		         Macro57_Entry4_DelayMin, Macro57_Entry4_DelaySec, Macro57_Entry4_TimMin, Macro57_Entry4_TimSec, Macro57_Entry4_Protocol, 0, 0, 0, 0,
		         Macro57_Entry5_DelayMin, Macro57_Entry5_DelaySec, Macro57_Entry5_TimMin, Macro57_Entry5_TimSec, Macro57_Entry5_Protocol, 0, 0, 0, 0,
		         Macro57_Entry6_DelayMin, Macro57_Entry6_DelaySec, Macro57_Entry6_TimMin, Macro57_Entry6_TimSec, Macro57_Entry6_Protocol, 0, 0, 0, 0,
		         Macro57_Entry7_DelayMin, Macro57_Entry7_DelaySec, Macro57_Entry7_TimMin, Macro57_Entry7_TimSec, Macro57_Entry7_Protocol, 0, 0, 0, 0,
		         Macro57_Entry8_DelayMin, Macro57_Entry8_DelaySec, Macro57_Entry8_TimMin, Macro57_Entry8_TimSec, Macro57_Entry8_Protocol, 0, 0, 0, 0,
		         Macro57_Entry9_DelayMin, Macro57_Entry9_DelaySec, Macro57_Entry9_TimMin, Macro57_Entry9_TimSec, Macro57_Entry9_Protocol, 0, 0, 0, 0,
		         Macro57_Entry10_DelayMin, Macro57_Entry10_DelaySec, Macro57_Entry10_TimMin, Macro57_Entry10_TimSec, Macro57_Entry10_Protocol, 0, 0, 0, 0,
		         Macro57_Entry11_DelayMin, Macro57_Entry11_DelaySec, Macro57_Entry11_TimMin, Macro57_Entry11_TimSec, Macro57_Entry11_Protocol, 0, 0, 0, 0,
		         Macro57_Entry12_DelayMin, Macro57_Entry12_DelaySec, Macro57_Entry12_TimMin, Macro57_Entry12_TimSec, Macro57_Entry12_Protocol, 0, 0, 0, 0,
		         Macro57_Entry13_DelayMin, Macro57_Entry13_DelaySec, Macro57_Entry13_TimMin, Macro57_Entry13_TimSec, Macro57_Entry13_Protocol, 0, 0, 0, 0,
		         Macro57_Entry14_DelayMin, Macro57_Entry14_DelaySec, Macro57_Entry14_TimMin, Macro57_Entry14_TimSec, Macro57_Entry14_Protocol, 0, 0, 0, 0,
		         Macro57_Entry15_DelayMin, Macro57_Entry15_DelaySec, Macro57_Entry15_TimMin, Macro57_Entry15_TimSec, Macro57_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR57_STRING};

const struct super_macro Macro58 = {Macro58_NumEntries,
		         Macro58_Entry1_DelayMin, Macro58_Entry1_DelaySec, Macro58_Entry1_TimMin, Macro58_Entry1_TimSec, Macro58_Entry1_Protocol, 0, 0, 0, 0,
		         Macro58_Entry2_DelayMin, Macro58_Entry2_DelaySec, Macro58_Entry2_TimMin, Macro58_Entry2_TimSec, Macro58_Entry2_Protocol, 0, 0, 0, 0,
		         Macro58_Entry3_DelayMin, Macro58_Entry3_DelaySec, Macro58_Entry3_TimMin, Macro58_Entry3_TimSec, Macro58_Entry3_Protocol, 0, 0, 0, 0,
		         Macro58_Entry4_DelayMin, Macro58_Entry4_DelaySec, Macro58_Entry4_TimMin, Macro58_Entry4_TimSec, Macro58_Entry4_Protocol, 0, 0, 0, 0,
		         Macro58_Entry5_DelayMin, Macro58_Entry5_DelaySec, Macro58_Entry5_TimMin, Macro58_Entry5_TimSec, Macro58_Entry5_Protocol, 0, 0, 0, 0,
		         Macro58_Entry6_DelayMin, Macro58_Entry6_DelaySec, Macro58_Entry6_TimMin, Macro58_Entry6_TimSec, Macro58_Entry6_Protocol, 0, 0, 0, 0,
		         Macro58_Entry7_DelayMin, Macro58_Entry7_DelaySec, Macro58_Entry7_TimMin, Macro58_Entry7_TimSec, Macro58_Entry7_Protocol, 0, 0, 0, 0,
		         Macro58_Entry8_DelayMin, Macro58_Entry8_DelaySec, Macro58_Entry8_TimMin, Macro58_Entry8_TimSec, Macro58_Entry8_Protocol, 0, 0, 0, 0,
		         Macro58_Entry9_DelayMin, Macro58_Entry9_DelaySec, Macro58_Entry9_TimMin, Macro58_Entry9_TimSec, Macro58_Entry9_Protocol, 0, 0, 0, 0,
		         Macro58_Entry10_DelayMin, Macro58_Entry10_DelaySec, Macro58_Entry10_TimMin, Macro58_Entry10_TimSec, Macro58_Entry10_Protocol, 0, 0, 0, 0,
		         Macro58_Entry11_DelayMin, Macro58_Entry11_DelaySec, Macro58_Entry11_TimMin, Macro58_Entry11_TimSec, Macro58_Entry11_Protocol, 0, 0, 0, 0,
		         Macro58_Entry12_DelayMin, Macro58_Entry12_DelaySec, Macro58_Entry12_TimMin, Macro58_Entry12_TimSec, Macro58_Entry12_Protocol, 0, 0, 0, 0,
		         Macro58_Entry13_DelayMin, Macro58_Entry13_DelaySec, Macro58_Entry13_TimMin, Macro58_Entry13_TimSec, Macro58_Entry13_Protocol, 0, 0, 0, 0,
		         Macro58_Entry14_DelayMin, Macro58_Entry14_DelaySec, Macro58_Entry14_TimMin, Macro58_Entry14_TimSec, Macro58_Entry14_Protocol, 0, 0, 0, 0,
		         Macro58_Entry15_DelayMin, Macro58_Entry15_DelaySec, Macro58_Entry15_TimMin, Macro58_Entry15_TimSec, Macro58_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR58_STRING};

const struct super_macro Macro59 = {Macro59_NumEntries,
		         Macro59_Entry1_DelayMin, Macro59_Entry1_DelaySec, Macro59_Entry1_TimMin, Macro59_Entry1_TimSec, Macro59_Entry1_Protocol, 0, 0, 0, 0,
		         Macro59_Entry2_DelayMin, Macro59_Entry2_DelaySec, Macro59_Entry2_TimMin, Macro59_Entry2_TimSec, Macro59_Entry2_Protocol, 0, 0, 0, 0,
		         Macro59_Entry3_DelayMin, Macro59_Entry3_DelaySec, Macro59_Entry3_TimMin, Macro59_Entry3_TimSec, Macro59_Entry3_Protocol, 0, 0, 0, 0,
		         Macro59_Entry4_DelayMin, Macro59_Entry4_DelaySec, Macro59_Entry4_TimMin, Macro59_Entry4_TimSec, Macro59_Entry4_Protocol, 0, 0, 0, 0,
		         Macro59_Entry5_DelayMin, Macro59_Entry5_DelaySec, Macro59_Entry5_TimMin, Macro59_Entry5_TimSec, Macro59_Entry5_Protocol, 0, 0, 0, 0,
		         Macro59_Entry6_DelayMin, Macro59_Entry6_DelaySec, Macro59_Entry6_TimMin, Macro59_Entry6_TimSec, Macro59_Entry6_Protocol, 0, 0, 0, 0,
		         Macro59_Entry7_DelayMin, Macro59_Entry7_DelaySec, Macro59_Entry7_TimMin, Macro59_Entry7_TimSec, Macro59_Entry7_Protocol, 0, 0, 0, 0,
		         Macro59_Entry8_DelayMin, Macro59_Entry8_DelaySec, Macro59_Entry8_TimMin, Macro59_Entry8_TimSec, Macro59_Entry8_Protocol, 0, 0, 0, 0,
		         Macro59_Entry9_DelayMin, Macro59_Entry9_DelaySec, Macro59_Entry9_TimMin, Macro59_Entry9_TimSec, Macro59_Entry9_Protocol, 0, 0, 0, 0,
		         Macro59_Entry10_DelayMin, Macro59_Entry10_DelaySec, Macro59_Entry10_TimMin, Macro59_Entry10_TimSec, Macro59_Entry10_Protocol, 0, 0, 0, 0,
		         Macro59_Entry11_DelayMin, Macro59_Entry11_DelaySec, Macro59_Entry11_TimMin, Macro59_Entry11_TimSec, Macro59_Entry11_Protocol, 0, 0, 0, 0,
		         Macro59_Entry12_DelayMin, Macro59_Entry12_DelaySec, Macro59_Entry12_TimMin, Macro59_Entry12_TimSec, Macro59_Entry12_Protocol, 0, 0, 0, 0,
		         Macro59_Entry13_DelayMin, Macro59_Entry13_DelaySec, Macro59_Entry13_TimMin, Macro59_Entry13_TimSec, Macro59_Entry13_Protocol, 0, 0, 0, 0,
		         Macro59_Entry14_DelayMin, Macro59_Entry14_DelaySec, Macro59_Entry14_TimMin, Macro59_Entry14_TimSec, Macro59_Entry14_Protocol, 0, 0, 0, 0,
		         Macro59_Entry15_DelayMin, Macro59_Entry15_DelaySec, Macro59_Entry15_TimMin, Macro59_Entry15_TimSec, Macro59_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR59_STRING};

const struct super_macro Macro60 = {Macro60_NumEntries,
		         Macro60_Entry1_DelayMin, Macro60_Entry1_DelaySec, Macro60_Entry1_TimMin, Macro60_Entry1_TimSec, Macro60_Entry1_Protocol, 0, 0, 0, 0,
		         Macro60_Entry2_DelayMin, Macro60_Entry2_DelaySec, Macro60_Entry2_TimMin, Macro60_Entry2_TimSec, Macro60_Entry2_Protocol, 0, 0, 0, 0,
		         Macro60_Entry3_DelayMin, Macro60_Entry3_DelaySec, Macro60_Entry3_TimMin, Macro60_Entry3_TimSec, Macro60_Entry3_Protocol, 0, 0, 0, 0,
		         Macro60_Entry4_DelayMin, Macro60_Entry4_DelaySec, Macro60_Entry4_TimMin, Macro60_Entry4_TimSec, Macro60_Entry4_Protocol, 0, 0, 0, 0,
		         Macro60_Entry5_DelayMin, Macro60_Entry5_DelaySec, Macro60_Entry5_TimMin, Macro60_Entry5_TimSec, Macro60_Entry5_Protocol, 0, 0, 0, 0,
		         Macro60_Entry6_DelayMin, Macro60_Entry6_DelaySec, Macro60_Entry6_TimMin, Macro60_Entry6_TimSec, Macro60_Entry6_Protocol, 0, 0, 0, 0,
		         Macro60_Entry7_DelayMin, Macro60_Entry7_DelaySec, Macro60_Entry7_TimMin, Macro60_Entry7_TimSec, Macro60_Entry7_Protocol, 0, 0, 0, 0,
		         Macro60_Entry8_DelayMin, Macro60_Entry8_DelaySec, Macro60_Entry8_TimMin, Macro60_Entry8_TimSec, Macro60_Entry8_Protocol, 0, 0, 0, 0,
		         Macro60_Entry9_DelayMin, Macro60_Entry9_DelaySec, Macro60_Entry9_TimMin, Macro60_Entry9_TimSec, Macro60_Entry9_Protocol, 0, 0, 0, 0,
		         Macro60_Entry10_DelayMin, Macro60_Entry10_DelaySec, Macro60_Entry10_TimMin, Macro60_Entry10_TimSec, Macro60_Entry10_Protocol, 0, 0, 0, 0,
		         Macro60_Entry11_DelayMin, Macro60_Entry11_DelaySec, Macro60_Entry11_TimMin, Macro60_Entry11_TimSec, Macro60_Entry11_Protocol, 0, 0, 0, 0,
		         Macro60_Entry12_DelayMin, Macro60_Entry12_DelaySec, Macro60_Entry12_TimMin, Macro60_Entry12_TimSec, Macro60_Entry12_Protocol, 0, 0, 0, 0,
		         Macro60_Entry13_DelayMin, Macro60_Entry13_DelaySec, Macro60_Entry13_TimMin, Macro60_Entry13_TimSec, Macro60_Entry13_Protocol, 0, 0, 0, 0,
		         Macro60_Entry14_DelayMin, Macro60_Entry14_DelaySec, Macro60_Entry14_TimMin, Macro60_Entry14_TimSec, Macro60_Entry14_Protocol, 0, 0, 0, 0,
		         Macro60_Entry15_DelayMin, Macro60_Entry15_DelaySec, Macro60_Entry15_TimMin, Macro60_Entry15_TimSec, Macro60_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR60_STRING};

const struct super_macro Macro61 = {Macro61_NumEntries,
		         Macro61_Entry1_DelayMin, Macro61_Entry1_DelaySec, Macro61_Entry1_TimMin, Macro61_Entry1_TimSec, Macro61_Entry1_Protocol, 0, 0, 0, 0,
		         Macro61_Entry2_DelayMin, Macro61_Entry2_DelaySec, Macro61_Entry2_TimMin, Macro61_Entry2_TimSec, Macro61_Entry2_Protocol, 0, 0, 0, 0,
		         Macro61_Entry3_DelayMin, Macro61_Entry3_DelaySec, Macro61_Entry3_TimMin, Macro61_Entry3_TimSec, Macro61_Entry3_Protocol, 0, 0, 0, 0,
		         Macro61_Entry4_DelayMin, Macro61_Entry4_DelaySec, Macro61_Entry4_TimMin, Macro61_Entry4_TimSec, Macro61_Entry4_Protocol, 0, 0, 0, 0,
		         Macro61_Entry5_DelayMin, Macro61_Entry5_DelaySec, Macro61_Entry5_TimMin, Macro61_Entry5_TimSec, Macro61_Entry5_Protocol, 0, 0, 0, 0,
		         Macro61_Entry6_DelayMin, Macro61_Entry6_DelaySec, Macro61_Entry6_TimMin, Macro61_Entry6_TimSec, Macro61_Entry6_Protocol, 0, 0, 0, 0,
		         Macro61_Entry7_DelayMin, Macro61_Entry7_DelaySec, Macro61_Entry7_TimMin, Macro61_Entry7_TimSec, Macro61_Entry7_Protocol, 0, 0, 0, 0,
		         Macro61_Entry8_DelayMin, Macro61_Entry8_DelaySec, Macro61_Entry8_TimMin, Macro61_Entry8_TimSec, Macro61_Entry8_Protocol, 0, 0, 0, 0,
		         Macro61_Entry9_DelayMin, Macro61_Entry9_DelaySec, Macro61_Entry9_TimMin, Macro61_Entry9_TimSec, Macro61_Entry9_Protocol, 0, 0, 0, 0,
		         Macro61_Entry10_DelayMin, Macro61_Entry10_DelaySec, Macro61_Entry10_TimMin, Macro61_Entry10_TimSec, Macro61_Entry10_Protocol, 0, 0, 0, 0,
		         Macro61_Entry11_DelayMin, Macro61_Entry11_DelaySec, Macro61_Entry11_TimMin, Macro61_Entry11_TimSec, Macro61_Entry11_Protocol, 0, 0, 0, 0,
		         Macro61_Entry12_DelayMin, Macro61_Entry12_DelaySec, Macro61_Entry12_TimMin, Macro61_Entry12_TimSec, Macro61_Entry12_Protocol, 0, 0, 0, 0,
		         Macro61_Entry13_DelayMin, Macro61_Entry13_DelaySec, Macro61_Entry13_TimMin, Macro61_Entry13_TimSec, Macro61_Entry13_Protocol, 0, 0, 0, 0,
		         Macro61_Entry14_DelayMin, Macro61_Entry14_DelaySec, Macro61_Entry14_TimMin, Macro61_Entry14_TimSec, Macro61_Entry14_Protocol, 0, 0, 0, 0,
		         Macro61_Entry15_DelayMin, Macro61_Entry15_DelaySec, Macro61_Entry15_TimMin, Macro61_Entry15_TimSec, Macro61_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR61_STRING};

const struct super_macro Macro62 = {Macro62_NumEntries,
		         Macro62_Entry1_DelayMin, Macro62_Entry1_DelaySec, Macro62_Entry1_TimMin, Macro62_Entry1_TimSec, Macro62_Entry1_Protocol, 0, 0, 0, 0,
		         Macro62_Entry2_DelayMin, Macro62_Entry2_DelaySec, Macro62_Entry2_TimMin, Macro62_Entry2_TimSec, Macro62_Entry2_Protocol, 0, 0, 0, 0,
		         Macro62_Entry3_DelayMin, Macro62_Entry3_DelaySec, Macro62_Entry3_TimMin, Macro62_Entry3_TimSec, Macro62_Entry3_Protocol, 0, 0, 0, 0,
		         Macro62_Entry4_DelayMin, Macro62_Entry4_DelaySec, Macro62_Entry4_TimMin, Macro62_Entry4_TimSec, Macro62_Entry4_Protocol, 0, 0, 0, 0,
		         Macro62_Entry5_DelayMin, Macro62_Entry5_DelaySec, Macro62_Entry5_TimMin, Macro62_Entry5_TimSec, Macro62_Entry5_Protocol, 0, 0, 0, 0,
		         Macro62_Entry6_DelayMin, Macro62_Entry6_DelaySec, Macro62_Entry6_TimMin, Macro62_Entry6_TimSec, Macro62_Entry6_Protocol, 0, 0, 0, 0,
		         Macro62_Entry7_DelayMin, Macro62_Entry7_DelaySec, Macro62_Entry7_TimMin, Macro62_Entry7_TimSec, Macro62_Entry7_Protocol, 0, 0, 0, 0,
		         Macro62_Entry8_DelayMin, Macro62_Entry8_DelaySec, Macro62_Entry8_TimMin, Macro62_Entry8_TimSec, Macro62_Entry8_Protocol, 0, 0, 0, 0,
		         Macro62_Entry9_DelayMin, Macro62_Entry9_DelaySec, Macro62_Entry9_TimMin, Macro62_Entry9_TimSec, Macro62_Entry9_Protocol, 0, 0, 0, 0,
		         Macro62_Entry10_DelayMin, Macro62_Entry10_DelaySec, Macro62_Entry10_TimMin, Macro62_Entry10_TimSec, Macro62_Entry10_Protocol, 0, 0, 0, 0,
		         Macro62_Entry11_DelayMin, Macro62_Entry11_DelaySec, Macro62_Entry11_TimMin, Macro62_Entry11_TimSec, Macro62_Entry11_Protocol, 0, 0, 0, 0,
		         Macro62_Entry12_DelayMin, Macro62_Entry12_DelaySec, Macro62_Entry12_TimMin, Macro62_Entry12_TimSec, Macro62_Entry12_Protocol, 0, 0, 0, 0,
		         Macro62_Entry13_DelayMin, Macro62_Entry13_DelaySec, Macro62_Entry13_TimMin, Macro62_Entry13_TimSec, Macro62_Entry13_Protocol, 0, 0, 0, 0,
		         Macro62_Entry14_DelayMin, Macro62_Entry14_DelaySec, Macro62_Entry14_TimMin, Macro62_Entry14_TimSec, Macro62_Entry14_Protocol, 0, 0, 0, 0,
		         Macro62_Entry15_DelayMin, Macro62_Entry15_DelaySec, Macro62_Entry15_TimMin, Macro62_Entry15_TimSec, Macro62_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR62_STRING};

const struct super_macro Macro63 = {Macro63_NumEntries,
		         Macro63_Entry1_DelayMin, Macro63_Entry1_DelaySec, Macro63_Entry1_TimMin, Macro63_Entry1_TimSec, Macro63_Entry1_Protocol, 0, 0, 0, 0,
		         Macro63_Entry2_DelayMin, Macro63_Entry2_DelaySec, Macro63_Entry2_TimMin, Macro63_Entry2_TimSec, Macro63_Entry2_Protocol, 0, 0, 0, 0,
		         Macro63_Entry3_DelayMin, Macro63_Entry3_DelaySec, Macro63_Entry3_TimMin, Macro63_Entry3_TimSec, Macro63_Entry3_Protocol, 0, 0, 0, 0,
		         Macro63_Entry4_DelayMin, Macro63_Entry4_DelaySec, Macro63_Entry4_TimMin, Macro63_Entry4_TimSec, Macro63_Entry4_Protocol, 0, 0, 0, 0,
		         Macro63_Entry5_DelayMin, Macro63_Entry5_DelaySec, Macro63_Entry5_TimMin, Macro63_Entry5_TimSec, Macro63_Entry5_Protocol, 0, 0, 0, 0,
		         Macro63_Entry6_DelayMin, Macro63_Entry6_DelaySec, Macro63_Entry6_TimMin, Macro63_Entry6_TimSec, Macro63_Entry6_Protocol, 0, 0, 0, 0,
		         Macro63_Entry7_DelayMin, Macro63_Entry7_DelaySec, Macro63_Entry7_TimMin, Macro63_Entry7_TimSec, Macro63_Entry7_Protocol, 0, 0, 0, 0,
		         Macro63_Entry8_DelayMin, Macro63_Entry8_DelaySec, Macro63_Entry8_TimMin, Macro63_Entry8_TimSec, Macro63_Entry8_Protocol, 0, 0, 0, 0,
		         Macro63_Entry9_DelayMin, Macro63_Entry9_DelaySec, Macro63_Entry9_TimMin, Macro63_Entry9_TimSec, Macro63_Entry9_Protocol, 0, 0, 0, 0,
		         Macro63_Entry10_DelayMin, Macro63_Entry10_DelaySec, Macro63_Entry10_TimMin, Macro63_Entry10_TimSec, Macro63_Entry10_Protocol, 0, 0, 0, 0,
		         Macro63_Entry11_DelayMin, Macro63_Entry11_DelaySec, Macro63_Entry11_TimMin, Macro63_Entry11_TimSec, Macro63_Entry11_Protocol, 0, 0, 0, 0,
		         Macro63_Entry12_DelayMin, Macro63_Entry12_DelaySec, Macro63_Entry12_TimMin, Macro63_Entry12_TimSec, Macro63_Entry12_Protocol, 0, 0, 0, 0,
		         Macro63_Entry13_DelayMin, Macro63_Entry13_DelaySec, Macro63_Entry13_TimMin, Macro63_Entry13_TimSec, Macro63_Entry13_Protocol, 0, 0, 0, 0,
		         Macro63_Entry14_DelayMin, Macro63_Entry14_DelaySec, Macro63_Entry14_TimMin, Macro63_Entry14_TimSec, Macro63_Entry14_Protocol, 0, 0, 0, 0,
		         Macro63_Entry15_DelayMin, Macro63_Entry15_DelaySec, Macro63_Entry15_TimMin, Macro63_Entry15_TimSec, Macro63_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR63_STRING};

const struct super_macro Macro64 = {Macro64_NumEntries,
		         Macro64_Entry1_DelayMin, Macro64_Entry1_DelaySec, Macro64_Entry1_TimMin, Macro64_Entry1_TimSec, Macro64_Entry1_Protocol, 0, 0, 0, 0,
		         Macro64_Entry2_DelayMin, Macro64_Entry2_DelaySec, Macro64_Entry2_TimMin, Macro64_Entry2_TimSec, Macro64_Entry2_Protocol, 0, 0, 0, 0,
		         Macro64_Entry3_DelayMin, Macro64_Entry3_DelaySec, Macro64_Entry3_TimMin, Macro64_Entry3_TimSec, Macro64_Entry3_Protocol, 0, 0, 0, 0,
		         Macro64_Entry4_DelayMin, Macro64_Entry4_DelaySec, Macro64_Entry4_TimMin, Macro64_Entry4_TimSec, Macro64_Entry4_Protocol, 0, 0, 0, 0,
		         Macro64_Entry5_DelayMin, Macro64_Entry5_DelaySec, Macro64_Entry5_TimMin, Macro64_Entry5_TimSec, Macro64_Entry5_Protocol, 0, 0, 0, 0,
		         Macro64_Entry6_DelayMin, Macro64_Entry6_DelaySec, Macro64_Entry6_TimMin, Macro64_Entry6_TimSec, Macro64_Entry6_Protocol, 0, 0, 0, 0,
		         Macro64_Entry7_DelayMin, Macro64_Entry7_DelaySec, Macro64_Entry7_TimMin, Macro64_Entry7_TimSec, Macro64_Entry7_Protocol, 0, 0, 0, 0,
		         Macro64_Entry8_DelayMin, Macro64_Entry8_DelaySec, Macro64_Entry8_TimMin, Macro64_Entry8_TimSec, Macro64_Entry8_Protocol, 0, 0, 0, 0,
		         Macro64_Entry9_DelayMin, Macro64_Entry9_DelaySec, Macro64_Entry9_TimMin, Macro64_Entry9_TimSec, Macro64_Entry9_Protocol, 0, 0, 0, 0,
		         Macro64_Entry10_DelayMin, Macro64_Entry10_DelaySec, Macro64_Entry10_TimMin, Macro64_Entry10_TimSec, Macro64_Entry10_Protocol, 0, 0, 0, 0,
		         Macro64_Entry11_DelayMin, Macro64_Entry11_DelaySec, Macro64_Entry11_TimMin, Macro64_Entry11_TimSec, Macro64_Entry11_Protocol, 0, 0, 0, 0,
		         Macro64_Entry12_DelayMin, Macro64_Entry12_DelaySec, Macro64_Entry12_TimMin, Macro64_Entry12_TimSec, Macro64_Entry12_Protocol, 0, 0, 0, 0,
		         Macro64_Entry13_DelayMin, Macro64_Entry13_DelaySec, Macro64_Entry13_TimMin, Macro64_Entry13_TimSec, Macro64_Entry13_Protocol, 0, 0, 0, 0,
		         Macro64_Entry14_DelayMin, Macro64_Entry14_DelaySec, Macro64_Entry14_TimMin, Macro64_Entry14_TimSec, Macro64_Entry14_Protocol, 0, 0, 0, 0,
		         Macro64_Entry15_DelayMin, Macro64_Entry15_DelaySec, Macro64_Entry15_TimMin, Macro64_Entry15_TimSec, Macro64_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR64_STRING};

const struct super_macro Macro65 = {Macro65_NumEntries,
		         Macro65_Entry1_DelayMin, Macro65_Entry1_DelaySec, Macro65_Entry1_TimMin, Macro65_Entry1_TimSec, Macro65_Entry1_Protocol, 0, 0, 0, 0,
		         Macro65_Entry2_DelayMin, Macro65_Entry2_DelaySec, Macro65_Entry2_TimMin, Macro65_Entry2_TimSec, Macro65_Entry2_Protocol, 0, 0, 0, 0,
		         Macro65_Entry3_DelayMin, Macro65_Entry3_DelaySec, Macro65_Entry3_TimMin, Macro65_Entry3_TimSec, Macro65_Entry3_Protocol, 0, 0, 0, 0,
		         Macro65_Entry4_DelayMin, Macro65_Entry4_DelaySec, Macro65_Entry4_TimMin, Macro65_Entry4_TimSec, Macro65_Entry4_Protocol, 0, 0, 0, 0,
		         Macro65_Entry5_DelayMin, Macro65_Entry5_DelaySec, Macro65_Entry5_TimMin, Macro65_Entry5_TimSec, Macro65_Entry5_Protocol, 0, 0, 0, 0,
		         Macro65_Entry6_DelayMin, Macro65_Entry6_DelaySec, Macro65_Entry6_TimMin, Macro65_Entry6_TimSec, Macro65_Entry6_Protocol, 0, 0, 0, 0,
		         Macro65_Entry7_DelayMin, Macro65_Entry7_DelaySec, Macro65_Entry7_TimMin, Macro65_Entry7_TimSec, Macro65_Entry7_Protocol, 0, 0, 0, 0,
		         Macro65_Entry8_DelayMin, Macro65_Entry8_DelaySec, Macro65_Entry8_TimMin, Macro65_Entry8_TimSec, Macro65_Entry8_Protocol, 0, 0, 0, 0,
		         Macro65_Entry9_DelayMin, Macro65_Entry9_DelaySec, Macro65_Entry9_TimMin, Macro65_Entry9_TimSec, Macro65_Entry9_Protocol, 0, 0, 0, 0,
		         Macro65_Entry10_DelayMin, Macro65_Entry10_DelaySec, Macro65_Entry10_TimMin, Macro65_Entry10_TimSec, Macro65_Entry10_Protocol, 0, 0, 0, 0,
		         Macro65_Entry11_DelayMin, Macro65_Entry11_DelaySec, Macro65_Entry11_TimMin, Macro65_Entry11_TimSec, Macro65_Entry11_Protocol, 0, 0, 0, 0,
		         Macro65_Entry12_DelayMin, Macro65_Entry12_DelaySec, Macro65_Entry12_TimMin, Macro65_Entry12_TimSec, Macro65_Entry12_Protocol, 0, 0, 0, 0,
		         Macro65_Entry13_DelayMin, Macro65_Entry13_DelaySec, Macro65_Entry13_TimMin, Macro65_Entry13_TimSec, Macro65_Entry13_Protocol, 0, 0, 0, 0,
		         Macro65_Entry14_DelayMin, Macro65_Entry14_DelaySec, Macro65_Entry14_TimMin, Macro65_Entry14_TimSec, Macro65_Entry14_Protocol, 0, 0, 0, 0,
		         Macro65_Entry15_DelayMin, Macro65_Entry15_DelaySec, Macro65_Entry15_TimMin, Macro65_Entry15_TimSec, Macro65_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR65_STRING};

const struct super_macro Macro66 = {Macro66_NumEntries,
		         Macro66_Entry1_DelayMin, Macro66_Entry1_DelaySec, Macro66_Entry1_TimMin, Macro66_Entry1_TimSec, Macro66_Entry1_Protocol, 0, 0, 0, 0,
		         Macro66_Entry2_DelayMin, Macro66_Entry2_DelaySec, Macro66_Entry2_TimMin, Macro66_Entry2_TimSec, Macro66_Entry2_Protocol, 0, 0, 0, 0,
		         Macro66_Entry3_DelayMin, Macro66_Entry3_DelaySec, Macro66_Entry3_TimMin, Macro66_Entry3_TimSec, Macro66_Entry3_Protocol, 0, 0, 0, 0,
		         Macro66_Entry4_DelayMin, Macro66_Entry4_DelaySec, Macro66_Entry4_TimMin, Macro66_Entry4_TimSec, Macro66_Entry4_Protocol, 0, 0, 0, 0,
		         Macro66_Entry5_DelayMin, Macro66_Entry5_DelaySec, Macro66_Entry5_TimMin, Macro66_Entry5_TimSec, Macro66_Entry5_Protocol, 0, 0, 0, 0,
		         Macro66_Entry6_DelayMin, Macro66_Entry6_DelaySec, Macro66_Entry6_TimMin, Macro66_Entry6_TimSec, Macro66_Entry6_Protocol, 0, 0, 0, 0,
		         Macro66_Entry7_DelayMin, Macro66_Entry7_DelaySec, Macro66_Entry7_TimMin, Macro66_Entry7_TimSec, Macro66_Entry7_Protocol, 0, 0, 0, 0,
		         Macro66_Entry8_DelayMin, Macro66_Entry8_DelaySec, Macro66_Entry8_TimMin, Macro66_Entry8_TimSec, Macro66_Entry8_Protocol, 0, 0, 0, 0,
		         Macro66_Entry9_DelayMin, Macro66_Entry9_DelaySec, Macro66_Entry9_TimMin, Macro66_Entry9_TimSec, Macro66_Entry9_Protocol, 0, 0, 0, 0,
		         Macro66_Entry10_DelayMin, Macro66_Entry10_DelaySec, Macro66_Entry10_TimMin, Macro66_Entry10_TimSec, Macro66_Entry10_Protocol, 0, 0, 0, 0,
		         Macro66_Entry11_DelayMin, Macro66_Entry11_DelaySec, Macro66_Entry11_TimMin, Macro66_Entry11_TimSec, Macro66_Entry11_Protocol, 0, 0, 0, 0,
		         Macro66_Entry12_DelayMin, Macro66_Entry12_DelaySec, Macro66_Entry12_TimMin, Macro66_Entry12_TimSec, Macro66_Entry12_Protocol, 0, 0, 0, 0,
		         Macro66_Entry13_DelayMin, Macro66_Entry13_DelaySec, Macro66_Entry13_TimMin, Macro66_Entry13_TimSec, Macro66_Entry13_Protocol, 0, 0, 0, 0,
		         Macro66_Entry14_DelayMin, Macro66_Entry14_DelaySec, Macro66_Entry14_TimMin, Macro66_Entry14_TimSec, Macro66_Entry14_Protocol, 0, 0, 0, 0,
		         Macro66_Entry15_DelayMin, Macro66_Entry15_DelaySec, Macro66_Entry15_TimMin, Macro66_Entry15_TimSec, Macro66_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR66_STRING};

const struct super_macro Macro67 = {Macro67_NumEntries,
		         Macro67_Entry1_DelayMin, Macro67_Entry1_DelaySec, Macro67_Entry1_TimMin, Macro67_Entry1_TimSec, Macro67_Entry1_Protocol, 0, 0, 0, 0,
		         Macro67_Entry2_DelayMin, Macro67_Entry2_DelaySec, Macro67_Entry2_TimMin, Macro67_Entry2_TimSec, Macro67_Entry2_Protocol, 0, 0, 0, 0,
		         Macro67_Entry3_DelayMin, Macro67_Entry3_DelaySec, Macro67_Entry3_TimMin, Macro67_Entry3_TimSec, Macro67_Entry3_Protocol, 0, 0, 0, 0,
		         Macro67_Entry4_DelayMin, Macro67_Entry4_DelaySec, Macro67_Entry4_TimMin, Macro67_Entry4_TimSec, Macro67_Entry4_Protocol, 0, 0, 0, 0,
		         Macro67_Entry5_DelayMin, Macro67_Entry5_DelaySec, Macro67_Entry5_TimMin, Macro67_Entry5_TimSec, Macro67_Entry5_Protocol, 0, 0, 0, 0,
		         Macro67_Entry6_DelayMin, Macro67_Entry6_DelaySec, Macro67_Entry6_TimMin, Macro67_Entry6_TimSec, Macro67_Entry6_Protocol, 0, 0, 0, 0,
		         Macro67_Entry7_DelayMin, Macro67_Entry7_DelaySec, Macro67_Entry7_TimMin, Macro67_Entry7_TimSec, Macro67_Entry7_Protocol, 0, 0, 0, 0,
		         Macro67_Entry8_DelayMin, Macro67_Entry8_DelaySec, Macro67_Entry8_TimMin, Macro67_Entry8_TimSec, Macro67_Entry8_Protocol, 0, 0, 0, 0,
		         Macro67_Entry9_DelayMin, Macro67_Entry9_DelaySec, Macro67_Entry9_TimMin, Macro67_Entry9_TimSec, Macro67_Entry9_Protocol, 0, 0, 0, 0,
		         Macro67_Entry10_DelayMin, Macro67_Entry10_DelaySec, Macro67_Entry10_TimMin, Macro67_Entry10_TimSec, Macro67_Entry10_Protocol, 0, 0, 0, 0,
		         Macro67_Entry11_DelayMin, Macro67_Entry11_DelaySec, Macro67_Entry11_TimMin, Macro67_Entry11_TimSec, Macro67_Entry11_Protocol, 0, 0, 0, 0,
		         Macro67_Entry12_DelayMin, Macro67_Entry12_DelaySec, Macro67_Entry12_TimMin, Macro67_Entry12_TimSec, Macro67_Entry12_Protocol, 0, 0, 0, 0,
		         Macro67_Entry13_DelayMin, Macro67_Entry13_DelaySec, Macro67_Entry13_TimMin, Macro67_Entry13_TimSec, Macro67_Entry13_Protocol, 0, 0, 0, 0,
		         Macro67_Entry14_DelayMin, Macro67_Entry14_DelaySec, Macro67_Entry14_TimMin, Macro67_Entry14_TimSec, Macro67_Entry14_Protocol, 0, 0, 0, 0,
		         Macro67_Entry15_DelayMin, Macro67_Entry15_DelaySec, Macro67_Entry15_TimMin, Macro67_Entry15_TimSec, Macro67_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR67_STRING};

const struct super_macro Macro68 = {Macro68_NumEntries,
		         Macro68_Entry1_DelayMin, Macro68_Entry1_DelaySec, Macro68_Entry1_TimMin, Macro68_Entry1_TimSec, Macro68_Entry1_Protocol, 0, 0, 0, 0,
		         Macro68_Entry2_DelayMin, Macro68_Entry2_DelaySec, Macro68_Entry2_TimMin, Macro68_Entry2_TimSec, Macro68_Entry2_Protocol, 0, 0, 0, 0,
		         Macro68_Entry3_DelayMin, Macro68_Entry3_DelaySec, Macro68_Entry3_TimMin, Macro68_Entry3_TimSec, Macro68_Entry3_Protocol, 0, 0, 0, 0,
		         Macro68_Entry4_DelayMin, Macro68_Entry4_DelaySec, Macro68_Entry4_TimMin, Macro68_Entry4_TimSec, Macro68_Entry4_Protocol, 0, 0, 0, 0,
		         Macro68_Entry5_DelayMin, Macro68_Entry5_DelaySec, Macro68_Entry5_TimMin, Macro68_Entry5_TimSec, Macro68_Entry5_Protocol, 0, 0, 0, 0,
		         Macro68_Entry6_DelayMin, Macro68_Entry6_DelaySec, Macro68_Entry6_TimMin, Macro68_Entry6_TimSec, Macro68_Entry6_Protocol, 0, 0, 0, 0,
		         Macro68_Entry7_DelayMin, Macro68_Entry7_DelaySec, Macro68_Entry7_TimMin, Macro68_Entry7_TimSec, Macro68_Entry7_Protocol, 0, 0, 0, 0,
		         Macro68_Entry8_DelayMin, Macro68_Entry8_DelaySec, Macro68_Entry8_TimMin, Macro68_Entry8_TimSec, Macro68_Entry8_Protocol, 0, 0, 0, 0,
		         Macro68_Entry9_DelayMin, Macro68_Entry9_DelaySec, Macro68_Entry9_TimMin, Macro68_Entry9_TimSec, Macro68_Entry9_Protocol, 0, 0, 0, 0,
		         Macro68_Entry10_DelayMin, Macro68_Entry10_DelaySec, Macro68_Entry10_TimMin, Macro68_Entry10_TimSec, Macro68_Entry10_Protocol, 0, 0, 0, 0,
		         Macro68_Entry11_DelayMin, Macro68_Entry11_DelaySec, Macro68_Entry11_TimMin, Macro68_Entry11_TimSec, Macro68_Entry11_Protocol, 0, 0, 0, 0,
		         Macro68_Entry12_DelayMin, Macro68_Entry12_DelaySec, Macro68_Entry12_TimMin, Macro68_Entry12_TimSec, Macro68_Entry12_Protocol, 0, 0, 0, 0,
		         Macro68_Entry13_DelayMin, Macro68_Entry13_DelaySec, Macro68_Entry13_TimMin, Macro68_Entry13_TimSec, Macro68_Entry13_Protocol, 0, 0, 0, 0,
		         Macro68_Entry14_DelayMin, Macro68_Entry14_DelaySec, Macro68_Entry14_TimMin, Macro68_Entry14_TimSec, Macro68_Entry14_Protocol, 0, 0, 0, 0,
		         Macro68_Entry15_DelayMin, Macro68_Entry15_DelaySec, Macro68_Entry15_TimMin, Macro68_Entry15_TimSec, Macro68_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR68_STRING};

const struct super_macro Macro69 = {Macro69_NumEntries,
		         Macro69_Entry1_DelayMin, Macro69_Entry1_DelaySec, Macro69_Entry1_TimMin, Macro69_Entry1_TimSec, Macro69_Entry1_Protocol, 0, 0, 0, 0,
		         Macro69_Entry2_DelayMin, Macro69_Entry2_DelaySec, Macro69_Entry2_TimMin, Macro69_Entry2_TimSec, Macro69_Entry2_Protocol, 0, 0, 0, 0,
		         Macro69_Entry3_DelayMin, Macro69_Entry3_DelaySec, Macro69_Entry3_TimMin, Macro69_Entry3_TimSec, Macro69_Entry3_Protocol, 0, 0, 0, 0,
		         Macro69_Entry4_DelayMin, Macro69_Entry4_DelaySec, Macro69_Entry4_TimMin, Macro69_Entry4_TimSec, Macro69_Entry4_Protocol, 0, 0, 0, 0,
		         Macro69_Entry5_DelayMin, Macro69_Entry5_DelaySec, Macro69_Entry5_TimMin, Macro69_Entry5_TimSec, Macro69_Entry5_Protocol, 0, 0, 0, 0,
		         Macro69_Entry6_DelayMin, Macro69_Entry6_DelaySec, Macro69_Entry6_TimMin, Macro69_Entry6_TimSec, Macro69_Entry6_Protocol, 0, 0, 0, 0,
		         Macro69_Entry7_DelayMin, Macro69_Entry7_DelaySec, Macro69_Entry7_TimMin, Macro69_Entry7_TimSec, Macro69_Entry7_Protocol, 0, 0, 0, 0,
		         Macro69_Entry8_DelayMin, Macro69_Entry8_DelaySec, Macro69_Entry8_TimMin, Macro69_Entry8_TimSec, Macro69_Entry8_Protocol, 0, 0, 0, 0,
		         Macro69_Entry9_DelayMin, Macro69_Entry9_DelaySec, Macro69_Entry9_TimMin, Macro69_Entry9_TimSec, Macro69_Entry9_Protocol, 0, 0, 0, 0,
		         Macro69_Entry10_DelayMin, Macro69_Entry10_DelaySec, Macro69_Entry10_TimMin, Macro69_Entry10_TimSec, Macro69_Entry10_Protocol, 0, 0, 0, 0,
		         Macro69_Entry11_DelayMin, Macro69_Entry11_DelaySec, Macro69_Entry11_TimMin, Macro69_Entry11_TimSec, Macro69_Entry11_Protocol, 0, 0, 0, 0,
		         Macro69_Entry12_DelayMin, Macro69_Entry12_DelaySec, Macro69_Entry12_TimMin, Macro69_Entry12_TimSec, Macro69_Entry12_Protocol, 0, 0, 0, 0,
		         Macro69_Entry13_DelayMin, Macro69_Entry13_DelaySec, Macro69_Entry13_TimMin, Macro69_Entry13_TimSec, Macro69_Entry13_Protocol, 0, 0, 0, 0,
		         Macro69_Entry14_DelayMin, Macro69_Entry14_DelaySec, Macro69_Entry14_TimMin, Macro69_Entry14_TimSec, Macro69_Entry14_Protocol, 0, 0, 0, 0,
		         Macro69_Entry15_DelayMin, Macro69_Entry15_DelaySec, Macro69_Entry15_TimMin, Macro69_Entry15_TimSec, Macro69_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR69_STRING};

const struct super_macro Macro70 = {Macro70_NumEntries,
		         Macro70_Entry1_DelayMin, Macro70_Entry1_DelaySec, Macro70_Entry1_TimMin, Macro70_Entry1_TimSec, Macro70_Entry1_Protocol, 0, 0, 0, 0,
		         Macro70_Entry2_DelayMin, Macro70_Entry2_DelaySec, Macro70_Entry2_TimMin, Macro70_Entry2_TimSec, Macro70_Entry2_Protocol, 0, 0, 0, 0,
		         Macro70_Entry3_DelayMin, Macro70_Entry3_DelaySec, Macro70_Entry3_TimMin, Macro70_Entry3_TimSec, Macro70_Entry3_Protocol, 0, 0, 0, 0,
		         Macro70_Entry4_DelayMin, Macro70_Entry4_DelaySec, Macro70_Entry4_TimMin, Macro70_Entry4_TimSec, Macro70_Entry4_Protocol, 0, 0, 0, 0,
		         Macro70_Entry5_DelayMin, Macro70_Entry5_DelaySec, Macro70_Entry5_TimMin, Macro70_Entry5_TimSec, Macro70_Entry5_Protocol, 0, 0, 0, 0,
		         Macro70_Entry6_DelayMin, Macro70_Entry6_DelaySec, Macro70_Entry6_TimMin, Macro70_Entry6_TimSec, Macro70_Entry6_Protocol, 0, 0, 0, 0,
		         Macro70_Entry7_DelayMin, Macro70_Entry7_DelaySec, Macro70_Entry7_TimMin, Macro70_Entry7_TimSec, Macro70_Entry7_Protocol, 0, 0, 0, 0,
		         Macro70_Entry8_DelayMin, Macro70_Entry8_DelaySec, Macro70_Entry8_TimMin, Macro70_Entry8_TimSec, Macro70_Entry8_Protocol, 0, 0, 0, 0,
		         Macro70_Entry9_DelayMin, Macro70_Entry9_DelaySec, Macro70_Entry9_TimMin, Macro70_Entry9_TimSec, Macro70_Entry9_Protocol, 0, 0, 0, 0,
		         Macro70_Entry10_DelayMin, Macro70_Entry10_DelaySec, Macro70_Entry10_TimMin, Macro70_Entry10_TimSec, Macro70_Entry10_Protocol, 0, 0, 0, 0,
		         Macro70_Entry11_DelayMin, Macro70_Entry11_DelaySec, Macro70_Entry11_TimMin, Macro70_Entry11_TimSec, Macro70_Entry11_Protocol, 0, 0, 0, 0,
		         Macro70_Entry12_DelayMin, Macro70_Entry12_DelaySec, Macro70_Entry12_TimMin, Macro70_Entry12_TimSec, Macro70_Entry12_Protocol, 0, 0, 0, 0,
		         Macro70_Entry13_DelayMin, Macro70_Entry13_DelaySec, Macro70_Entry13_TimMin, Macro70_Entry13_TimSec, Macro70_Entry13_Protocol, 0, 0, 0, 0,
		         Macro70_Entry14_DelayMin, Macro70_Entry14_DelaySec, Macro70_Entry14_TimMin, Macro70_Entry14_TimSec, Macro70_Entry14_Protocol, 0, 0, 0, 0,
		         Macro70_Entry15_DelayMin, Macro70_Entry15_DelaySec, Macro70_Entry15_TimMin, Macro70_Entry15_TimSec, Macro70_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR70_STRING};

const struct super_macro Macro71 = {Macro71_NumEntries,
		         Macro71_Entry1_DelayMin, Macro71_Entry1_DelaySec, Macro71_Entry1_TimMin, Macro71_Entry1_TimSec, Macro71_Entry1_Protocol, 0, 0, 0, 0,
		         Macro71_Entry2_DelayMin, Macro71_Entry2_DelaySec, Macro71_Entry2_TimMin, Macro71_Entry2_TimSec, Macro71_Entry2_Protocol, 0, 0, 0, 0,
		         Macro71_Entry3_DelayMin, Macro71_Entry3_DelaySec, Macro71_Entry3_TimMin, Macro71_Entry3_TimSec, Macro71_Entry3_Protocol, 0, 0, 0, 0,
		         Macro71_Entry4_DelayMin, Macro71_Entry4_DelaySec, Macro71_Entry4_TimMin, Macro71_Entry4_TimSec, Macro71_Entry4_Protocol, 0, 0, 0, 0,
		         Macro71_Entry5_DelayMin, Macro71_Entry5_DelaySec, Macro71_Entry5_TimMin, Macro71_Entry5_TimSec, Macro71_Entry5_Protocol, 0, 0, 0, 0,
		         Macro71_Entry6_DelayMin, Macro71_Entry6_DelaySec, Macro71_Entry6_TimMin, Macro71_Entry6_TimSec, Macro71_Entry6_Protocol, 0, 0, 0, 0,
		         Macro71_Entry7_DelayMin, Macro71_Entry7_DelaySec, Macro71_Entry7_TimMin, Macro71_Entry7_TimSec, Macro71_Entry7_Protocol, 0, 0, 0, 0,
		         Macro71_Entry8_DelayMin, Macro71_Entry8_DelaySec, Macro71_Entry8_TimMin, Macro71_Entry8_TimSec, Macro71_Entry8_Protocol, 0, 0, 0, 0,
		         Macro71_Entry9_DelayMin, Macro71_Entry9_DelaySec, Macro71_Entry9_TimMin, Macro71_Entry9_TimSec, Macro71_Entry9_Protocol, 0, 0, 0, 0,
		         Macro71_Entry10_DelayMin, Macro71_Entry10_DelaySec, Macro71_Entry10_TimMin, Macro71_Entry10_TimSec, Macro71_Entry10_Protocol, 0, 0, 0, 0,
		         Macro71_Entry11_DelayMin, Macro71_Entry11_DelaySec, Macro71_Entry11_TimMin, Macro71_Entry11_TimSec, Macro71_Entry11_Protocol, 0, 0, 0, 0,
		         Macro71_Entry12_DelayMin, Macro71_Entry12_DelaySec, Macro71_Entry12_TimMin, Macro71_Entry12_TimSec, Macro71_Entry12_Protocol, 0, 0, 0, 0,
		         Macro71_Entry13_DelayMin, Macro71_Entry13_DelaySec, Macro71_Entry13_TimMin, Macro71_Entry13_TimSec, Macro71_Entry13_Protocol, 0, 0, 0, 0,
		         Macro71_Entry14_DelayMin, Macro71_Entry14_DelaySec, Macro71_Entry14_TimMin, Macro71_Entry14_TimSec, Macro71_Entry14_Protocol, 0, 0, 0, 0,
		         Macro71_Entry15_DelayMin, Macro71_Entry15_DelaySec, Macro71_Entry15_TimMin, Macro71_Entry15_TimSec, Macro71_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR71_STRING};

const struct super_macro Macro72 = {Macro72_NumEntries,
		         Macro72_Entry1_DelayMin, Macro72_Entry1_DelaySec, Macro72_Entry1_TimMin, Macro72_Entry1_TimSec, Macro72_Entry1_Protocol, 0, 0, 0, 0,
		         Macro72_Entry2_DelayMin, Macro72_Entry2_DelaySec, Macro72_Entry2_TimMin, Macro72_Entry2_TimSec, Macro72_Entry2_Protocol, 0, 0, 0, 0,
		         Macro72_Entry3_DelayMin, Macro72_Entry3_DelaySec, Macro72_Entry3_TimMin, Macro72_Entry3_TimSec, Macro72_Entry3_Protocol, 0, 0, 0, 0,
		         Macro72_Entry4_DelayMin, Macro72_Entry4_DelaySec, Macro72_Entry4_TimMin, Macro72_Entry4_TimSec, Macro72_Entry4_Protocol, 0, 0, 0, 0,
		         Macro72_Entry5_DelayMin, Macro72_Entry5_DelaySec, Macro72_Entry5_TimMin, Macro72_Entry5_TimSec, Macro72_Entry5_Protocol, 0, 0, 0, 0,
		         Macro72_Entry6_DelayMin, Macro72_Entry6_DelaySec, Macro72_Entry6_TimMin, Macro72_Entry6_TimSec, Macro72_Entry6_Protocol, 0, 0, 0, 0,
		         Macro72_Entry7_DelayMin, Macro72_Entry7_DelaySec, Macro72_Entry7_TimMin, Macro72_Entry7_TimSec, Macro72_Entry7_Protocol, 0, 0, 0, 0,
		         Macro72_Entry8_DelayMin, Macro72_Entry8_DelaySec, Macro72_Entry8_TimMin, Macro72_Entry8_TimSec, Macro72_Entry8_Protocol, 0, 0, 0, 0,
		         Macro72_Entry9_DelayMin, Macro72_Entry9_DelaySec, Macro72_Entry9_TimMin, Macro72_Entry9_TimSec, Macro72_Entry9_Protocol, 0, 0, 0, 0,
		         Macro72_Entry10_DelayMin, Macro72_Entry10_DelaySec, Macro72_Entry10_TimMin, Macro72_Entry10_TimSec, Macro72_Entry10_Protocol, 0, 0, 0, 0,
		         Macro72_Entry11_DelayMin, Macro72_Entry11_DelaySec, Macro72_Entry11_TimMin, Macro72_Entry11_TimSec, Macro72_Entry11_Protocol, 0, 0, 0, 0,
		         Macro72_Entry12_DelayMin, Macro72_Entry12_DelaySec, Macro72_Entry12_TimMin, Macro72_Entry12_TimSec, Macro72_Entry12_Protocol, 0, 0, 0, 0,
		         Macro72_Entry13_DelayMin, Macro72_Entry13_DelaySec, Macro72_Entry13_TimMin, Macro72_Entry13_TimSec, Macro72_Entry13_Protocol, 0, 0, 0, 0,
		         Macro72_Entry14_DelayMin, Macro72_Entry14_DelaySec, Macro72_Entry14_TimMin, Macro72_Entry14_TimSec, Macro72_Entry14_Protocol, 0, 0, 0, 0,
		         Macro72_Entry15_DelayMin, Macro72_Entry15_DelaySec, Macro72_Entry15_TimMin, Macro72_Entry15_TimSec, Macro72_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR72_STRING};

const struct super_macro Macro73 = {Macro73_NumEntries,
		         Macro73_Entry1_DelayMin, Macro73_Entry1_DelaySec, Macro73_Entry1_TimMin, Macro73_Entry1_TimSec, Macro73_Entry1_Protocol, 0, 0, 0, 0,
		         Macro73_Entry2_DelayMin, Macro73_Entry2_DelaySec, Macro73_Entry2_TimMin, Macro73_Entry2_TimSec, Macro73_Entry2_Protocol, 0, 0, 0, 0,
		         Macro73_Entry3_DelayMin, Macro73_Entry3_DelaySec, Macro73_Entry3_TimMin, Macro73_Entry3_TimSec, Macro73_Entry3_Protocol, 0, 0, 0, 0,
		         Macro73_Entry4_DelayMin, Macro73_Entry4_DelaySec, Macro73_Entry4_TimMin, Macro73_Entry4_TimSec, Macro73_Entry4_Protocol, 0, 0, 0, 0,
		         Macro73_Entry5_DelayMin, Macro73_Entry5_DelaySec, Macro73_Entry5_TimMin, Macro73_Entry5_TimSec, Macro73_Entry5_Protocol, 0, 0, 0, 0,
		         Macro73_Entry6_DelayMin, Macro73_Entry6_DelaySec, Macro73_Entry6_TimMin, Macro73_Entry6_TimSec, Macro73_Entry6_Protocol, 0, 0, 0, 0,
		         Macro73_Entry7_DelayMin, Macro73_Entry7_DelaySec, Macro73_Entry7_TimMin, Macro73_Entry7_TimSec, Macro73_Entry7_Protocol, 0, 0, 0, 0,
		         Macro73_Entry8_DelayMin, Macro73_Entry8_DelaySec, Macro73_Entry8_TimMin, Macro73_Entry8_TimSec, Macro73_Entry8_Protocol, 0, 0, 0, 0,
		         Macro73_Entry9_DelayMin, Macro73_Entry9_DelaySec, Macro73_Entry9_TimMin, Macro73_Entry9_TimSec, Macro73_Entry9_Protocol, 0, 0, 0, 0,
		         Macro73_Entry10_DelayMin, Macro73_Entry10_DelaySec, Macro73_Entry10_TimMin, Macro73_Entry10_TimSec, Macro73_Entry10_Protocol, 0, 0, 0, 0,
		         Macro73_Entry11_DelayMin, Macro73_Entry11_DelaySec, Macro73_Entry11_TimMin, Macro73_Entry11_TimSec, Macro73_Entry11_Protocol, 0, 0, 0, 0,
		         Macro73_Entry12_DelayMin, Macro73_Entry12_DelaySec, Macro73_Entry12_TimMin, Macro73_Entry12_TimSec, Macro73_Entry12_Protocol, 0, 0, 0, 0,
		         Macro73_Entry13_DelayMin, Macro73_Entry13_DelaySec, Macro73_Entry13_TimMin, Macro73_Entry13_TimSec, Macro73_Entry13_Protocol, 0, 0, 0, 0,
		         Macro73_Entry14_DelayMin, Macro73_Entry14_DelaySec, Macro73_Entry14_TimMin, Macro73_Entry14_TimSec, Macro73_Entry14_Protocol, 0, 0, 0, 0,
		         Macro73_Entry15_DelayMin, Macro73_Entry15_DelaySec, Macro73_Entry15_TimMin, Macro73_Entry15_TimSec, Macro73_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR73_STRING};

const struct super_macro Macro74 = {Macro74_NumEntries,
		         Macro74_Entry1_DelayMin, Macro74_Entry1_DelaySec, Macro74_Entry1_TimMin, Macro74_Entry1_TimSec, Macro74_Entry1_Protocol, 0, 0, 0, 0,
		         Macro74_Entry2_DelayMin, Macro74_Entry2_DelaySec, Macro74_Entry2_TimMin, Macro74_Entry2_TimSec, Macro74_Entry2_Protocol, 0, 0, 0, 0,
		         Macro74_Entry3_DelayMin, Macro74_Entry3_DelaySec, Macro74_Entry3_TimMin, Macro74_Entry3_TimSec, Macro74_Entry3_Protocol, 0, 0, 0, 0,
		         Macro74_Entry4_DelayMin, Macro74_Entry4_DelaySec, Macro74_Entry4_TimMin, Macro74_Entry4_TimSec, Macro74_Entry4_Protocol, 0, 0, 0, 0,
		         Macro74_Entry5_DelayMin, Macro74_Entry5_DelaySec, Macro74_Entry5_TimMin, Macro74_Entry5_TimSec, Macro74_Entry5_Protocol, 0, 0, 0, 0,
		         Macro74_Entry6_DelayMin, Macro74_Entry6_DelaySec, Macro74_Entry6_TimMin, Macro74_Entry6_TimSec, Macro74_Entry6_Protocol, 0, 0, 0, 0,
		         Macro74_Entry7_DelayMin, Macro74_Entry7_DelaySec, Macro74_Entry7_TimMin, Macro74_Entry7_TimSec, Macro74_Entry7_Protocol, 0, 0, 0, 0,
		         Macro74_Entry8_DelayMin, Macro74_Entry8_DelaySec, Macro74_Entry8_TimMin, Macro74_Entry8_TimSec, Macro74_Entry8_Protocol, 0, 0, 0, 0,
		         Macro74_Entry9_DelayMin, Macro74_Entry9_DelaySec, Macro74_Entry9_TimMin, Macro74_Entry9_TimSec, Macro74_Entry9_Protocol, 0, 0, 0, 0,
		         Macro74_Entry10_DelayMin, Macro74_Entry10_DelaySec, Macro74_Entry10_TimMin, Macro74_Entry10_TimSec, Macro74_Entry10_Protocol, 0, 0, 0, 0,
		         Macro74_Entry11_DelayMin, Macro74_Entry11_DelaySec, Macro74_Entry11_TimMin, Macro74_Entry11_TimSec, Macro74_Entry11_Protocol, 0, 0, 0, 0,
		         Macro74_Entry12_DelayMin, Macro74_Entry12_DelaySec, Macro74_Entry12_TimMin, Macro74_Entry12_TimSec, Macro74_Entry12_Protocol, 0, 0, 0, 0,
		         Macro74_Entry13_DelayMin, Macro74_Entry13_DelaySec, Macro74_Entry13_TimMin, Macro74_Entry13_TimSec, Macro74_Entry13_Protocol, 0, 0, 0, 0,
		         Macro74_Entry14_DelayMin, Macro74_Entry14_DelaySec, Macro74_Entry14_TimMin, Macro74_Entry14_TimSec, Macro74_Entry14_Protocol, 0, 0, 0, 0,
		         Macro74_Entry15_DelayMin, Macro74_Entry15_DelaySec, Macro74_Entry15_TimMin, Macro74_Entry15_TimSec, Macro74_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR74_STRING};

const struct super_macro Macro75 = {Macro75_NumEntries,
		         Macro75_Entry1_DelayMin, Macro75_Entry1_DelaySec, Macro75_Entry1_TimMin, Macro75_Entry1_TimSec, Macro75_Entry1_Protocol, 0, 0, 0, 0,
		         Macro75_Entry2_DelayMin, Macro75_Entry2_DelaySec, Macro75_Entry2_TimMin, Macro75_Entry2_TimSec, Macro75_Entry2_Protocol, 0, 0, 0, 0,
		         Macro75_Entry3_DelayMin, Macro75_Entry3_DelaySec, Macro75_Entry3_TimMin, Macro75_Entry3_TimSec, Macro75_Entry3_Protocol, 0, 0, 0, 0,
		         Macro75_Entry4_DelayMin, Macro75_Entry4_DelaySec, Macro75_Entry4_TimMin, Macro75_Entry4_TimSec, Macro75_Entry4_Protocol, 0, 0, 0, 0,
		         Macro75_Entry5_DelayMin, Macro75_Entry5_DelaySec, Macro75_Entry5_TimMin, Macro75_Entry5_TimSec, Macro75_Entry5_Protocol, 0, 0, 0, 0,
		         Macro75_Entry6_DelayMin, Macro75_Entry6_DelaySec, Macro75_Entry6_TimMin, Macro75_Entry6_TimSec, Macro75_Entry6_Protocol, 0, 0, 0, 0,
		         Macro75_Entry7_DelayMin, Macro75_Entry7_DelaySec, Macro75_Entry7_TimMin, Macro75_Entry7_TimSec, Macro75_Entry7_Protocol, 0, 0, 0, 0,
		         Macro75_Entry8_DelayMin, Macro75_Entry8_DelaySec, Macro75_Entry8_TimMin, Macro75_Entry8_TimSec, Macro75_Entry8_Protocol, 0, 0, 0, 0,
		         Macro75_Entry9_DelayMin, Macro75_Entry9_DelaySec, Macro75_Entry9_TimMin, Macro75_Entry9_TimSec, Macro75_Entry9_Protocol, 0, 0, 0, 0,
		         Macro75_Entry10_DelayMin, Macro75_Entry10_DelaySec, Macro75_Entry10_TimMin, Macro75_Entry10_TimSec, Macro75_Entry10_Protocol, 0, 0, 0, 0,
		         Macro75_Entry11_DelayMin, Macro75_Entry11_DelaySec, Macro75_Entry11_TimMin, Macro75_Entry11_TimSec, Macro75_Entry11_Protocol, 0, 0, 0, 0,
		         Macro75_Entry12_DelayMin, Macro75_Entry12_DelaySec, Macro75_Entry12_TimMin, Macro75_Entry12_TimSec, Macro75_Entry12_Protocol, 0, 0, 0, 0,
		         Macro75_Entry13_DelayMin, Macro75_Entry13_DelaySec, Macro75_Entry13_TimMin, Macro75_Entry13_TimSec, Macro75_Entry13_Protocol, 0, 0, 0, 0,
		         Macro75_Entry14_DelayMin, Macro75_Entry14_DelaySec, Macro75_Entry14_TimMin, Macro75_Entry14_TimSec, Macro75_Entry14_Protocol, 0, 0, 0, 0,
		         Macro75_Entry15_DelayMin, Macro75_Entry15_DelaySec, Macro75_Entry15_TimMin, Macro75_Entry15_TimSec, Macro75_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR75_STRING};

const struct super_macro Macro76 = {Macro76_NumEntries,
		         Macro76_Entry1_DelayMin, Macro76_Entry1_DelaySec, Macro76_Entry1_TimMin, Macro76_Entry1_TimSec, Macro76_Entry1_Protocol, 0, 0, 0, 0,
		         Macro76_Entry2_DelayMin, Macro76_Entry2_DelaySec, Macro76_Entry2_TimMin, Macro76_Entry2_TimSec, Macro76_Entry2_Protocol, 0, 0, 0, 0,
		         Macro76_Entry3_DelayMin, Macro76_Entry3_DelaySec, Macro76_Entry3_TimMin, Macro76_Entry3_TimSec, Macro76_Entry3_Protocol, 0, 0, 0, 0,
		         Macro76_Entry4_DelayMin, Macro76_Entry4_DelaySec, Macro76_Entry4_TimMin, Macro76_Entry4_TimSec, Macro76_Entry4_Protocol, 0, 0, 0, 0,
		         Macro76_Entry5_DelayMin, Macro76_Entry5_DelaySec, Macro76_Entry5_TimMin, Macro76_Entry5_TimSec, Macro76_Entry5_Protocol, 0, 0, 0, 0,
		         Macro76_Entry6_DelayMin, Macro76_Entry6_DelaySec, Macro76_Entry6_TimMin, Macro76_Entry6_TimSec, Macro76_Entry6_Protocol, 0, 0, 0, 0,
		         Macro76_Entry7_DelayMin, Macro76_Entry7_DelaySec, Macro76_Entry7_TimMin, Macro76_Entry7_TimSec, Macro76_Entry7_Protocol, 0, 0, 0, 0,
		         Macro76_Entry8_DelayMin, Macro76_Entry8_DelaySec, Macro76_Entry8_TimMin, Macro76_Entry8_TimSec, Macro76_Entry8_Protocol, 0, 0, 0, 0,
		         Macro76_Entry9_DelayMin, Macro76_Entry9_DelaySec, Macro76_Entry9_TimMin, Macro76_Entry9_TimSec, Macro76_Entry9_Protocol, 0, 0, 0, 0,
		         Macro76_Entry10_DelayMin, Macro76_Entry10_DelaySec, Macro76_Entry10_TimMin, Macro76_Entry10_TimSec, Macro76_Entry10_Protocol, 0, 0, 0, 0,
		         Macro76_Entry11_DelayMin, Macro76_Entry11_DelaySec, Macro76_Entry11_TimMin, Macro76_Entry11_TimSec, Macro76_Entry11_Protocol, 0, 0, 0, 0,
		         Macro76_Entry12_DelayMin, Macro76_Entry12_DelaySec, Macro76_Entry12_TimMin, Macro76_Entry12_TimSec, Macro76_Entry12_Protocol, 0, 0, 0, 0,
		         Macro76_Entry13_DelayMin, Macro76_Entry13_DelaySec, Macro76_Entry13_TimMin, Macro76_Entry13_TimSec, Macro76_Entry13_Protocol, 0, 0, 0, 0,
		         Macro76_Entry14_DelayMin, Macro76_Entry14_DelaySec, Macro76_Entry14_TimMin, Macro76_Entry14_TimSec, Macro76_Entry14_Protocol, 0, 0, 0, 0,
		         Macro76_Entry15_DelayMin, Macro76_Entry15_DelaySec, Macro76_Entry15_TimMin, Macro76_Entry15_TimSec, Macro76_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR76_STRING};

const struct super_macro Macro77 = {Macro77_NumEntries,
		         Macro77_Entry1_DelayMin, Macro77_Entry1_DelaySec, Macro77_Entry1_TimMin, Macro77_Entry1_TimSec, Macro77_Entry1_Protocol, 0, 0, 0, 0,
		         Macro77_Entry2_DelayMin, Macro77_Entry2_DelaySec, Macro77_Entry2_TimMin, Macro77_Entry2_TimSec, Macro77_Entry2_Protocol, 0, 0, 0, 0,
		         Macro77_Entry3_DelayMin, Macro77_Entry3_DelaySec, Macro77_Entry3_TimMin, Macro77_Entry3_TimSec, Macro77_Entry3_Protocol, 0, 0, 0, 0,
		         Macro77_Entry4_DelayMin, Macro77_Entry4_DelaySec, Macro77_Entry4_TimMin, Macro77_Entry4_TimSec, Macro77_Entry4_Protocol, 0, 0, 0, 0,
		         Macro77_Entry5_DelayMin, Macro77_Entry5_DelaySec, Macro77_Entry5_TimMin, Macro77_Entry5_TimSec, Macro77_Entry5_Protocol, 0, 0, 0, 0,
		         Macro77_Entry6_DelayMin, Macro77_Entry6_DelaySec, Macro77_Entry6_TimMin, Macro77_Entry6_TimSec, Macro77_Entry6_Protocol, 0, 0, 0, 0,
		         Macro77_Entry7_DelayMin, Macro77_Entry7_DelaySec, Macro77_Entry7_TimMin, Macro77_Entry7_TimSec, Macro77_Entry7_Protocol, 0, 0, 0, 0,
		         Macro77_Entry8_DelayMin, Macro77_Entry8_DelaySec, Macro77_Entry8_TimMin, Macro77_Entry8_TimSec, Macro77_Entry8_Protocol, 0, 0, 0, 0,
		         Macro77_Entry9_DelayMin, Macro77_Entry9_DelaySec, Macro77_Entry9_TimMin, Macro77_Entry9_TimSec, Macro77_Entry9_Protocol, 0, 0, 0, 0,
		         Macro77_Entry10_DelayMin, Macro77_Entry10_DelaySec, Macro77_Entry10_TimMin, Macro77_Entry10_TimSec, Macro77_Entry10_Protocol, 0, 0, 0, 0,
		         Macro77_Entry11_DelayMin, Macro77_Entry11_DelaySec, Macro77_Entry11_TimMin, Macro77_Entry11_TimSec, Macro77_Entry11_Protocol, 0, 0, 0, 0,
		         Macro77_Entry12_DelayMin, Macro77_Entry12_DelaySec, Macro77_Entry12_TimMin, Macro77_Entry12_TimSec, Macro77_Entry12_Protocol, 0, 0, 0, 0,
		         Macro77_Entry13_DelayMin, Macro77_Entry13_DelaySec, Macro77_Entry13_TimMin, Macro77_Entry13_TimSec, Macro77_Entry13_Protocol, 0, 0, 0, 0,
		         Macro77_Entry14_DelayMin, Macro77_Entry14_DelaySec, Macro77_Entry14_TimMin, Macro77_Entry14_TimSec, Macro77_Entry14_Protocol, 0, 0, 0, 0,
		         Macro77_Entry15_DelayMin, Macro77_Entry15_DelaySec, Macro77_Entry15_TimMin, Macro77_Entry15_TimSec, Macro77_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR77_STRING};

const struct super_macro Macro78 = {Macro78_NumEntries,
		         Macro78_Entry1_DelayMin, Macro78_Entry1_DelaySec, Macro78_Entry1_TimMin, Macro78_Entry1_TimSec, Macro78_Entry1_Protocol, 0, 0, 0, 0,
		         Macro78_Entry2_DelayMin, Macro78_Entry2_DelaySec, Macro78_Entry2_TimMin, Macro78_Entry2_TimSec, Macro78_Entry2_Protocol, 0, 0, 0, 0,
		         Macro78_Entry3_DelayMin, Macro78_Entry3_DelaySec, Macro78_Entry3_TimMin, Macro78_Entry3_TimSec, Macro78_Entry3_Protocol, 0, 0, 0, 0,
		         Macro78_Entry4_DelayMin, Macro78_Entry4_DelaySec, Macro78_Entry4_TimMin, Macro78_Entry4_TimSec, Macro78_Entry4_Protocol, 0, 0, 0, 0,
		         Macro78_Entry5_DelayMin, Macro78_Entry5_DelaySec, Macro78_Entry5_TimMin, Macro78_Entry5_TimSec, Macro78_Entry5_Protocol, 0, 0, 0, 0,
		         Macro78_Entry6_DelayMin, Macro78_Entry6_DelaySec, Macro78_Entry6_TimMin, Macro78_Entry6_TimSec, Macro78_Entry6_Protocol, 0, 0, 0, 0,
		         Macro78_Entry7_DelayMin, Macro78_Entry7_DelaySec, Macro78_Entry7_TimMin, Macro78_Entry7_TimSec, Macro78_Entry7_Protocol, 0, 0, 0, 0,
		         Macro78_Entry8_DelayMin, Macro78_Entry8_DelaySec, Macro78_Entry8_TimMin, Macro78_Entry8_TimSec, Macro78_Entry8_Protocol, 0, 0, 0, 0,
		         Macro78_Entry9_DelayMin, Macro78_Entry9_DelaySec, Macro78_Entry9_TimMin, Macro78_Entry9_TimSec, Macro78_Entry9_Protocol, 0, 0, 0, 0,
		         Macro78_Entry10_DelayMin, Macro78_Entry10_DelaySec, Macro78_Entry10_TimMin, Macro78_Entry10_TimSec, Macro78_Entry10_Protocol, 0, 0, 0, 0,
		         Macro78_Entry11_DelayMin, Macro78_Entry11_DelaySec, Macro78_Entry11_TimMin, Macro78_Entry11_TimSec, Macro78_Entry11_Protocol, 0, 0, 0, 0,
		         Macro78_Entry12_DelayMin, Macro78_Entry12_DelaySec, Macro78_Entry12_TimMin, Macro78_Entry12_TimSec, Macro78_Entry12_Protocol, 0, 0, 0, 0,
		         Macro78_Entry13_DelayMin, Macro78_Entry13_DelaySec, Macro78_Entry13_TimMin, Macro78_Entry13_TimSec, Macro78_Entry13_Protocol, 0, 0, 0, 0,
		         Macro78_Entry14_DelayMin, Macro78_Entry14_DelaySec, Macro78_Entry14_TimMin, Macro78_Entry14_TimSec, Macro78_Entry14_Protocol, 0, 0, 0, 0,
		         Macro78_Entry15_DelayMin, Macro78_Entry15_DelaySec, Macro78_Entry15_TimMin, Macro78_Entry15_TimSec, Macro78_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR78_STRING};

const struct super_macro Macro79 = {Macro79_NumEntries,
		         Macro79_Entry1_DelayMin, Macro79_Entry1_DelaySec, Macro79_Entry1_TimMin, Macro79_Entry1_TimSec, Macro79_Entry1_Protocol, 0, 0, 0, 0,
		         Macro79_Entry2_DelayMin, Macro79_Entry2_DelaySec, Macro79_Entry2_TimMin, Macro79_Entry2_TimSec, Macro79_Entry2_Protocol, 0, 0, 0, 0,
		         Macro79_Entry3_DelayMin, Macro79_Entry3_DelaySec, Macro79_Entry3_TimMin, Macro79_Entry3_TimSec, Macro79_Entry3_Protocol, 0, 0, 0, 0,
		         Macro79_Entry4_DelayMin, Macro79_Entry4_DelaySec, Macro79_Entry4_TimMin, Macro79_Entry4_TimSec, Macro79_Entry4_Protocol, 0, 0, 0, 0,
		         Macro79_Entry5_DelayMin, Macro79_Entry5_DelaySec, Macro79_Entry5_TimMin, Macro79_Entry5_TimSec, Macro79_Entry5_Protocol, 0, 0, 0, 0,
		         Macro79_Entry6_DelayMin, Macro79_Entry6_DelaySec, Macro79_Entry6_TimMin, Macro79_Entry6_TimSec, Macro79_Entry6_Protocol, 0, 0, 0, 0,
		         Macro79_Entry7_DelayMin, Macro79_Entry7_DelaySec, Macro79_Entry7_TimMin, Macro79_Entry7_TimSec, Macro79_Entry7_Protocol, 0, 0, 0, 0,
		         Macro79_Entry8_DelayMin, Macro79_Entry8_DelaySec, Macro79_Entry8_TimMin, Macro79_Entry8_TimSec, Macro79_Entry8_Protocol, 0, 0, 0, 0,
		         Macro79_Entry9_DelayMin, Macro79_Entry9_DelaySec, Macro79_Entry9_TimMin, Macro79_Entry9_TimSec, Macro79_Entry9_Protocol, 0, 0, 0, 0,
		         Macro79_Entry10_DelayMin, Macro79_Entry10_DelaySec, Macro79_Entry10_TimMin, Macro79_Entry10_TimSec, Macro79_Entry10_Protocol, 0, 0, 0, 0,
		         Macro79_Entry11_DelayMin, Macro79_Entry11_DelaySec, Macro79_Entry11_TimMin, Macro79_Entry11_TimSec, Macro79_Entry11_Protocol, 0, 0, 0, 0,
		         Macro79_Entry12_DelayMin, Macro79_Entry12_DelaySec, Macro79_Entry12_TimMin, Macro79_Entry12_TimSec, Macro79_Entry12_Protocol, 0, 0, 0, 0,
		         Macro79_Entry13_DelayMin, Macro79_Entry13_DelaySec, Macro79_Entry13_TimMin, Macro79_Entry13_TimSec, Macro79_Entry13_Protocol, 0, 0, 0, 0,
		         Macro79_Entry14_DelayMin, Macro79_Entry14_DelaySec, Macro79_Entry14_TimMin, Macro79_Entry14_TimSec, Macro79_Entry14_Protocol, 0, 0, 0, 0,
		         Macro79_Entry15_DelayMin, Macro79_Entry15_DelaySec, Macro79_Entry15_TimMin, Macro79_Entry15_TimSec, Macro79_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR79_STRING};

const struct super_macro Macro80 = {Macro80_NumEntries,
		         Macro80_Entry1_DelayMin, Macro80_Entry1_DelaySec, Macro80_Entry1_TimMin, Macro80_Entry1_TimSec, Macro80_Entry1_Protocol, 0, 0, 0, 0,
		         Macro80_Entry2_DelayMin, Macro80_Entry2_DelaySec, Macro80_Entry2_TimMin, Macro80_Entry2_TimSec, Macro80_Entry2_Protocol, 0, 0, 0, 0,
		         Macro80_Entry3_DelayMin, Macro80_Entry3_DelaySec, Macro80_Entry3_TimMin, Macro80_Entry3_TimSec, Macro80_Entry3_Protocol, 0, 0, 0, 0,
		         Macro80_Entry4_DelayMin, Macro80_Entry4_DelaySec, Macro80_Entry4_TimMin, Macro80_Entry4_TimSec, Macro80_Entry4_Protocol, 0, 0, 0, 0,
		         Macro80_Entry5_DelayMin, Macro80_Entry5_DelaySec, Macro80_Entry5_TimMin, Macro80_Entry5_TimSec, Macro80_Entry5_Protocol, 0, 0, 0, 0,
		         Macro80_Entry6_DelayMin, Macro80_Entry6_DelaySec, Macro80_Entry6_TimMin, Macro80_Entry6_TimSec, Macro80_Entry6_Protocol, 0, 0, 0, 0,
		         Macro80_Entry7_DelayMin, Macro80_Entry7_DelaySec, Macro80_Entry7_TimMin, Macro80_Entry7_TimSec, Macro80_Entry7_Protocol, 0, 0, 0, 0,
		         Macro80_Entry8_DelayMin, Macro80_Entry8_DelaySec, Macro80_Entry8_TimMin, Macro80_Entry8_TimSec, Macro80_Entry8_Protocol, 0, 0, 0, 0,
		         Macro80_Entry9_DelayMin, Macro80_Entry9_DelaySec, Macro80_Entry9_TimMin, Macro80_Entry9_TimSec, Macro80_Entry9_Protocol, 0, 0, 0, 0,
		         Macro80_Entry10_DelayMin, Macro80_Entry10_DelaySec, Macro80_Entry10_TimMin, Macro80_Entry10_TimSec, Macro80_Entry10_Protocol, 0, 0, 0, 0,
		         Macro80_Entry11_DelayMin, Macro80_Entry11_DelaySec, Macro80_Entry11_TimMin, Macro80_Entry11_TimSec, Macro80_Entry11_Protocol, 0, 0, 0, 0,
		         Macro80_Entry12_DelayMin, Macro80_Entry12_DelaySec, Macro80_Entry12_TimMin, Macro80_Entry12_TimSec, Macro80_Entry12_Protocol, 0, 0, 0, 0,
		         Macro80_Entry13_DelayMin, Macro80_Entry13_DelaySec, Macro80_Entry13_TimMin, Macro80_Entry13_TimSec, Macro80_Entry13_Protocol, 0, 0, 0, 0,
		         Macro80_Entry14_DelayMin, Macro80_Entry14_DelaySec, Macro80_Entry14_TimMin, Macro80_Entry14_TimSec, Macro80_Entry14_Protocol, 0, 0, 0, 0,
		         Macro80_Entry15_DelayMin, Macro80_Entry15_DelaySec, Macro80_Entry15_TimMin, Macro80_Entry15_TimSec, Macro80_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR80_STRING};

const struct super_macro Macro81 = {Macro81_NumEntries,
		         Macro81_Entry1_DelayMin, Macro81_Entry1_DelaySec, Macro81_Entry1_TimMin, Macro81_Entry1_TimSec, Macro81_Entry1_Protocol, 0, 0, 0, 0,
		         Macro81_Entry2_DelayMin, Macro81_Entry2_DelaySec, Macro81_Entry2_TimMin, Macro81_Entry2_TimSec, Macro81_Entry2_Protocol, 0, 0, 0, 0,
		         Macro81_Entry3_DelayMin, Macro81_Entry3_DelaySec, Macro81_Entry3_TimMin, Macro81_Entry3_TimSec, Macro81_Entry3_Protocol, 0, 0, 0, 0,
		         Macro81_Entry4_DelayMin, Macro81_Entry4_DelaySec, Macro81_Entry4_TimMin, Macro81_Entry4_TimSec, Macro81_Entry4_Protocol, 0, 0, 0, 0,
		         Macro81_Entry5_DelayMin, Macro81_Entry5_DelaySec, Macro81_Entry5_TimMin, Macro81_Entry5_TimSec, Macro81_Entry5_Protocol, 0, 0, 0, 0,
		         Macro81_Entry6_DelayMin, Macro81_Entry6_DelaySec, Macro81_Entry6_TimMin, Macro81_Entry6_TimSec, Macro81_Entry6_Protocol, 0, 0, 0, 0,
		         Macro81_Entry7_DelayMin, Macro81_Entry7_DelaySec, Macro81_Entry7_TimMin, Macro81_Entry7_TimSec, Macro81_Entry7_Protocol, 0, 0, 0, 0,
		         Macro81_Entry8_DelayMin, Macro81_Entry8_DelaySec, Macro81_Entry8_TimMin, Macro81_Entry8_TimSec, Macro81_Entry8_Protocol, 0, 0, 0, 0,
		         Macro81_Entry9_DelayMin, Macro81_Entry9_DelaySec, Macro81_Entry9_TimMin, Macro81_Entry9_TimSec, Macro81_Entry9_Protocol, 0, 0, 0, 0,
		         Macro81_Entry10_DelayMin, Macro81_Entry10_DelaySec, Macro81_Entry10_TimMin, Macro81_Entry10_TimSec, Macro81_Entry10_Protocol, 0, 0, 0, 0,
		         Macro81_Entry11_DelayMin, Macro81_Entry11_DelaySec, Macro81_Entry11_TimMin, Macro81_Entry11_TimSec, Macro81_Entry11_Protocol, 0, 0, 0, 0,
		         Macro81_Entry12_DelayMin, Macro81_Entry12_DelaySec, Macro81_Entry12_TimMin, Macro81_Entry12_TimSec, Macro81_Entry12_Protocol, 0, 0, 0, 0,
		         Macro81_Entry13_DelayMin, Macro81_Entry13_DelaySec, Macro81_Entry13_TimMin, Macro81_Entry13_TimSec, Macro81_Entry13_Protocol, 0, 0, 0, 0,
		         Macro81_Entry14_DelayMin, Macro81_Entry14_DelaySec, Macro81_Entry14_TimMin, Macro81_Entry14_TimSec, Macro81_Entry14_Protocol, 0, 0, 0, 0,
		         Macro81_Entry15_DelayMin, Macro81_Entry15_DelaySec, Macro81_Entry15_TimMin, Macro81_Entry15_TimSec, Macro81_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR81_STRING};

const struct super_macro Macro82 = {Macro82_NumEntries,
		         Macro82_Entry1_DelayMin, Macro82_Entry1_DelaySec, Macro82_Entry1_TimMin, Macro82_Entry1_TimSec, Macro82_Entry1_Protocol, 0, 0, 0, 0,
		         Macro82_Entry2_DelayMin, Macro82_Entry2_DelaySec, Macro82_Entry2_TimMin, Macro82_Entry2_TimSec, Macro82_Entry2_Protocol, 0, 0, 0, 0,
		         Macro82_Entry3_DelayMin, Macro82_Entry3_DelaySec, Macro82_Entry3_TimMin, Macro82_Entry3_TimSec, Macro82_Entry3_Protocol, 0, 0, 0, 0,
		         Macro82_Entry4_DelayMin, Macro82_Entry4_DelaySec, Macro82_Entry4_TimMin, Macro82_Entry4_TimSec, Macro82_Entry4_Protocol, 0, 0, 0, 0,
		         Macro82_Entry5_DelayMin, Macro82_Entry5_DelaySec, Macro82_Entry5_TimMin, Macro82_Entry5_TimSec, Macro82_Entry5_Protocol, 0, 0, 0, 0,
		         Macro82_Entry6_DelayMin, Macro82_Entry6_DelaySec, Macro82_Entry6_TimMin, Macro82_Entry6_TimSec, Macro82_Entry6_Protocol, 0, 0, 0, 0,
		         Macro82_Entry7_DelayMin, Macro82_Entry7_DelaySec, Macro82_Entry7_TimMin, Macro82_Entry7_TimSec, Macro82_Entry7_Protocol, 0, 0, 0, 0,
		         Macro82_Entry8_DelayMin, Macro82_Entry8_DelaySec, Macro82_Entry8_TimMin, Macro82_Entry8_TimSec, Macro82_Entry8_Protocol, 0, 0, 0, 0,
		         Macro82_Entry9_DelayMin, Macro82_Entry9_DelaySec, Macro82_Entry9_TimMin, Macro82_Entry9_TimSec, Macro82_Entry9_Protocol, 0, 0, 0, 0,
		         Macro82_Entry10_DelayMin, Macro82_Entry10_DelaySec, Macro82_Entry10_TimMin, Macro82_Entry10_TimSec, Macro82_Entry10_Protocol, 0, 0, 0, 0,
		         Macro82_Entry11_DelayMin, Macro82_Entry11_DelaySec, Macro82_Entry11_TimMin, Macro82_Entry11_TimSec, Macro82_Entry11_Protocol, 0, 0, 0, 0,
		         Macro82_Entry12_DelayMin, Macro82_Entry12_DelaySec, Macro82_Entry12_TimMin, Macro82_Entry12_TimSec, Macro82_Entry12_Protocol, 0, 0, 0, 0,
		         Macro82_Entry13_DelayMin, Macro82_Entry13_DelaySec, Macro82_Entry13_TimMin, Macro82_Entry13_TimSec, Macro82_Entry13_Protocol, 0, 0, 0, 0,
		         Macro82_Entry14_DelayMin, Macro82_Entry14_DelaySec, Macro82_Entry14_TimMin, Macro82_Entry14_TimSec, Macro82_Entry14_Protocol, 0, 0, 0, 0,
		         Macro82_Entry15_DelayMin, Macro82_Entry15_DelaySec, Macro82_Entry15_TimMin, Macro82_Entry15_TimSec, Macro82_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR82_STRING};

const struct super_macro Macro83 = {Macro83_NumEntries,
		         Macro83_Entry1_DelayMin, Macro83_Entry1_DelaySec, Macro83_Entry1_TimMin, Macro83_Entry1_TimSec, Macro83_Entry1_Protocol, 0, 0, 0, 0,
		         Macro83_Entry2_DelayMin, Macro83_Entry2_DelaySec, Macro83_Entry2_TimMin, Macro83_Entry2_TimSec, Macro83_Entry2_Protocol, 0, 0, 0, 0,
		         Macro83_Entry3_DelayMin, Macro83_Entry3_DelaySec, Macro83_Entry3_TimMin, Macro83_Entry3_TimSec, Macro83_Entry3_Protocol, 0, 0, 0, 0,
		         Macro83_Entry4_DelayMin, Macro83_Entry4_DelaySec, Macro83_Entry4_TimMin, Macro83_Entry4_TimSec, Macro83_Entry4_Protocol, 0, 0, 0, 0,
		         Macro83_Entry5_DelayMin, Macro83_Entry5_DelaySec, Macro83_Entry5_TimMin, Macro83_Entry5_TimSec, Macro83_Entry5_Protocol, 0, 0, 0, 0,
		         Macro83_Entry6_DelayMin, Macro83_Entry6_DelaySec, Macro83_Entry6_TimMin, Macro83_Entry6_TimSec, Macro83_Entry6_Protocol, 0, 0, 0, 0,
		         Macro83_Entry7_DelayMin, Macro83_Entry7_DelaySec, Macro83_Entry7_TimMin, Macro83_Entry7_TimSec, Macro83_Entry7_Protocol, 0, 0, 0, 0,
		         Macro83_Entry8_DelayMin, Macro83_Entry8_DelaySec, Macro83_Entry8_TimMin, Macro83_Entry8_TimSec, Macro83_Entry8_Protocol, 0, 0, 0, 0,
		         Macro83_Entry9_DelayMin, Macro83_Entry9_DelaySec, Macro83_Entry9_TimMin, Macro83_Entry9_TimSec, Macro83_Entry9_Protocol, 0, 0, 0, 0,
		         Macro83_Entry10_DelayMin, Macro83_Entry10_DelaySec, Macro83_Entry10_TimMin, Macro83_Entry10_TimSec, Macro83_Entry10_Protocol, 0, 0, 0, 0,
		         Macro83_Entry11_DelayMin, Macro83_Entry11_DelaySec, Macro83_Entry11_TimMin, Macro83_Entry11_TimSec, Macro83_Entry11_Protocol, 0, 0, 0, 0,
		         Macro83_Entry12_DelayMin, Macro83_Entry12_DelaySec, Macro83_Entry12_TimMin, Macro83_Entry12_TimSec, Macro83_Entry12_Protocol, 0, 0, 0, 0,
		         Macro83_Entry13_DelayMin, Macro83_Entry13_DelaySec, Macro83_Entry13_TimMin, Macro83_Entry13_TimSec, Macro83_Entry13_Protocol, 0, 0, 0, 0,
		         Macro83_Entry14_DelayMin, Macro83_Entry14_DelaySec, Macro83_Entry14_TimMin, Macro83_Entry14_TimSec, Macro83_Entry14_Protocol, 0, 0, 0, 0,
		         Macro83_Entry15_DelayMin, Macro83_Entry15_DelaySec, Macro83_Entry15_TimMin, Macro83_Entry15_TimSec, Macro83_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR83_STRING};

const struct super_macro Macro84 = {Macro84_NumEntries,
		         Macro84_Entry1_DelayMin, Macro84_Entry1_DelaySec, Macro84_Entry1_TimMin, Macro84_Entry1_TimSec, Macro84_Entry1_Protocol, 0, 0, 0, 0,
		         Macro84_Entry2_DelayMin, Macro84_Entry2_DelaySec, Macro84_Entry2_TimMin, Macro84_Entry2_TimSec, Macro84_Entry2_Protocol, 0, 0, 0, 0,
		         Macro84_Entry3_DelayMin, Macro84_Entry3_DelaySec, Macro84_Entry3_TimMin, Macro84_Entry3_TimSec, Macro84_Entry3_Protocol, 0, 0, 0, 0,
		         Macro84_Entry4_DelayMin, Macro84_Entry4_DelaySec, Macro84_Entry4_TimMin, Macro84_Entry4_TimSec, Macro84_Entry4_Protocol, 0, 0, 0, 0,
		         Macro84_Entry5_DelayMin, Macro84_Entry5_DelaySec, Macro84_Entry5_TimMin, Macro84_Entry5_TimSec, Macro84_Entry5_Protocol, 0, 0, 0, 0,
		         Macro84_Entry6_DelayMin, Macro84_Entry6_DelaySec, Macro84_Entry6_TimMin, Macro84_Entry6_TimSec, Macro84_Entry6_Protocol, 0, 0, 0, 0,
		         Macro84_Entry7_DelayMin, Macro84_Entry7_DelaySec, Macro84_Entry7_TimMin, Macro84_Entry7_TimSec, Macro84_Entry7_Protocol, 0, 0, 0, 0,
		         Macro84_Entry8_DelayMin, Macro84_Entry8_DelaySec, Macro84_Entry8_TimMin, Macro84_Entry8_TimSec, Macro84_Entry8_Protocol, 0, 0, 0, 0,
		         Macro84_Entry9_DelayMin, Macro84_Entry9_DelaySec, Macro84_Entry9_TimMin, Macro84_Entry9_TimSec, Macro84_Entry9_Protocol, 0, 0, 0, 0,
		         Macro84_Entry10_DelayMin, Macro84_Entry10_DelaySec, Macro84_Entry10_TimMin, Macro84_Entry10_TimSec, Macro84_Entry10_Protocol, 0, 0, 0, 0,
		         Macro84_Entry11_DelayMin, Macro84_Entry11_DelaySec, Macro84_Entry11_TimMin, Macro84_Entry11_TimSec, Macro84_Entry11_Protocol, 0, 0, 0, 0,
		         Macro84_Entry12_DelayMin, Macro84_Entry12_DelaySec, Macro84_Entry12_TimMin, Macro84_Entry12_TimSec, Macro84_Entry12_Protocol, 0, 0, 0, 0,
		         Macro84_Entry13_DelayMin, Macro84_Entry13_DelaySec, Macro84_Entry13_TimMin, Macro84_Entry13_TimSec, Macro84_Entry13_Protocol, 0, 0, 0, 0,
		         Macro84_Entry14_DelayMin, Macro84_Entry14_DelaySec, Macro84_Entry14_TimMin, Macro84_Entry14_TimSec, Macro84_Entry14_Protocol, 0, 0, 0, 0,
		         Macro84_Entry15_DelayMin, Macro84_Entry15_DelaySec, Macro84_Entry15_TimMin, Macro84_Entry15_TimSec, Macro84_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR84_STRING};

const struct super_macro Macro85 = {Macro85_NumEntries,
		         Macro85_Entry1_DelayMin, Macro85_Entry1_DelaySec, Macro85_Entry1_TimMin, Macro85_Entry1_TimSec, Macro85_Entry1_Protocol, 0, 0, 0, 0,
		         Macro85_Entry2_DelayMin, Macro85_Entry2_DelaySec, Macro85_Entry2_TimMin, Macro85_Entry2_TimSec, Macro85_Entry2_Protocol, 0, 0, 0, 0,
		         Macro85_Entry3_DelayMin, Macro85_Entry3_DelaySec, Macro85_Entry3_TimMin, Macro85_Entry3_TimSec, Macro85_Entry3_Protocol, 0, 0, 0, 0,
		         Macro85_Entry4_DelayMin, Macro85_Entry4_DelaySec, Macro85_Entry4_TimMin, Macro85_Entry4_TimSec, Macro85_Entry4_Protocol, 0, 0, 0, 0,
		         Macro85_Entry5_DelayMin, Macro85_Entry5_DelaySec, Macro85_Entry5_TimMin, Macro85_Entry5_TimSec, Macro85_Entry5_Protocol, 0, 0, 0, 0,
		         Macro85_Entry6_DelayMin, Macro85_Entry6_DelaySec, Macro85_Entry6_TimMin, Macro85_Entry6_TimSec, Macro85_Entry6_Protocol, 0, 0, 0, 0,
		         Macro85_Entry7_DelayMin, Macro85_Entry7_DelaySec, Macro85_Entry7_TimMin, Macro85_Entry7_TimSec, Macro85_Entry7_Protocol, 0, 0, 0, 0,
		         Macro85_Entry8_DelayMin, Macro85_Entry8_DelaySec, Macro85_Entry8_TimMin, Macro85_Entry8_TimSec, Macro85_Entry8_Protocol, 0, 0, 0, 0,
		         Macro85_Entry9_DelayMin, Macro85_Entry9_DelaySec, Macro85_Entry9_TimMin, Macro85_Entry9_TimSec, Macro85_Entry9_Protocol, 0, 0, 0, 0,
		         Macro85_Entry10_DelayMin, Macro85_Entry10_DelaySec, Macro85_Entry10_TimMin, Macro85_Entry10_TimSec, Macro85_Entry10_Protocol, 0, 0, 0, 0,
		         Macro85_Entry11_DelayMin, Macro85_Entry11_DelaySec, Macro85_Entry11_TimMin, Macro85_Entry11_TimSec, Macro85_Entry11_Protocol, 0, 0, 0, 0,
		         Macro85_Entry12_DelayMin, Macro85_Entry12_DelaySec, Macro85_Entry12_TimMin, Macro85_Entry12_TimSec, Macro85_Entry12_Protocol, 0, 0, 0, 0,
		         Macro85_Entry13_DelayMin, Macro85_Entry13_DelaySec, Macro85_Entry13_TimMin, Macro85_Entry13_TimSec, Macro85_Entry13_Protocol, 0, 0, 0, 0,
		         Macro85_Entry14_DelayMin, Macro85_Entry14_DelaySec, Macro85_Entry14_TimMin, Macro85_Entry14_TimSec, Macro85_Entry14_Protocol, 0, 0, 0, 0,
		         Macro85_Entry15_DelayMin, Macro85_Entry15_DelaySec, Macro85_Entry15_TimMin, Macro85_Entry15_TimSec, Macro85_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR85_STRING};

const struct super_macro Macro86 = {Macro86_NumEntries,
		         Macro86_Entry1_DelayMin, Macro86_Entry1_DelaySec, Macro86_Entry1_TimMin, Macro86_Entry1_TimSec, Macro86_Entry1_Protocol, 0, 0, 0, 0,
		         Macro86_Entry2_DelayMin, Macro86_Entry2_DelaySec, Macro86_Entry2_TimMin, Macro86_Entry2_TimSec, Macro86_Entry2_Protocol, 0, 0, 0, 0,
		         Macro86_Entry3_DelayMin, Macro86_Entry3_DelaySec, Macro86_Entry3_TimMin, Macro86_Entry3_TimSec, Macro86_Entry3_Protocol, 0, 0, 0, 0,
		         Macro86_Entry4_DelayMin, Macro86_Entry4_DelaySec, Macro86_Entry4_TimMin, Macro86_Entry4_TimSec, Macro86_Entry4_Protocol, 0, 0, 0, 0,
		         Macro86_Entry5_DelayMin, Macro86_Entry5_DelaySec, Macro86_Entry5_TimMin, Macro86_Entry5_TimSec, Macro86_Entry5_Protocol, 0, 0, 0, 0,
		         Macro86_Entry6_DelayMin, Macro86_Entry6_DelaySec, Macro86_Entry6_TimMin, Macro86_Entry6_TimSec, Macro86_Entry6_Protocol, 0, 0, 0, 0,
		         Macro86_Entry7_DelayMin, Macro86_Entry7_DelaySec, Macro86_Entry7_TimMin, Macro86_Entry7_TimSec, Macro86_Entry7_Protocol, 0, 0, 0, 0,
		         Macro86_Entry8_DelayMin, Macro86_Entry8_DelaySec, Macro86_Entry8_TimMin, Macro86_Entry8_TimSec, Macro86_Entry8_Protocol, 0, 0, 0, 0,
		         Macro86_Entry9_DelayMin, Macro86_Entry9_DelaySec, Macro86_Entry9_TimMin, Macro86_Entry9_TimSec, Macro86_Entry9_Protocol, 0, 0, 0, 0,
		         Macro86_Entry10_DelayMin, Macro86_Entry10_DelaySec, Macro86_Entry10_TimMin, Macro86_Entry10_TimSec, Macro86_Entry10_Protocol, 0, 0, 0, 0,
		         Macro86_Entry11_DelayMin, Macro86_Entry11_DelaySec, Macro86_Entry11_TimMin, Macro86_Entry11_TimSec, Macro86_Entry11_Protocol, 0, 0, 0, 0,
		         Macro86_Entry12_DelayMin, Macro86_Entry12_DelaySec, Macro86_Entry12_TimMin, Macro86_Entry12_TimSec, Macro86_Entry12_Protocol, 0, 0, 0, 0,
		         Macro86_Entry13_DelayMin, Macro86_Entry13_DelaySec, Macro86_Entry13_TimMin, Macro86_Entry13_TimSec, Macro86_Entry13_Protocol, 0, 0, 0, 0,
		         Macro86_Entry14_DelayMin, Macro86_Entry14_DelaySec, Macro86_Entry14_TimMin, Macro86_Entry14_TimSec, Macro86_Entry14_Protocol, 0, 0, 0, 0,
		         Macro86_Entry15_DelayMin, Macro86_Entry15_DelaySec, Macro86_Entry15_TimMin, Macro86_Entry15_TimSec, Macro86_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR86_STRING};

const struct super_macro Macro87 = {Macro87_NumEntries,
		         Macro87_Entry1_DelayMin, Macro87_Entry1_DelaySec, Macro87_Entry1_TimMin, Macro87_Entry1_TimSec, Macro87_Entry1_Protocol, 0, 0, 0, 0,
		         Macro87_Entry2_DelayMin, Macro87_Entry2_DelaySec, Macro87_Entry2_TimMin, Macro87_Entry2_TimSec, Macro87_Entry2_Protocol, 0, 0, 0, 0,
		         Macro87_Entry3_DelayMin, Macro87_Entry3_DelaySec, Macro87_Entry3_TimMin, Macro87_Entry3_TimSec, Macro87_Entry3_Protocol, 0, 0, 0, 0,
		         Macro87_Entry4_DelayMin, Macro87_Entry4_DelaySec, Macro87_Entry4_TimMin, Macro87_Entry4_TimSec, Macro87_Entry4_Protocol, 0, 0, 0, 0,
		         Macro87_Entry5_DelayMin, Macro87_Entry5_DelaySec, Macro87_Entry5_TimMin, Macro87_Entry5_TimSec, Macro87_Entry5_Protocol, 0, 0, 0, 0,
		         Macro87_Entry6_DelayMin, Macro87_Entry6_DelaySec, Macro87_Entry6_TimMin, Macro87_Entry6_TimSec, Macro87_Entry6_Protocol, 0, 0, 0, 0,
		         Macro87_Entry7_DelayMin, Macro87_Entry7_DelaySec, Macro87_Entry7_TimMin, Macro87_Entry7_TimSec, Macro87_Entry7_Protocol, 0, 0, 0, 0,
		         Macro87_Entry8_DelayMin, Macro87_Entry8_DelaySec, Macro87_Entry8_TimMin, Macro87_Entry8_TimSec, Macro87_Entry8_Protocol, 0, 0, 0, 0,
		         Macro87_Entry9_DelayMin, Macro87_Entry9_DelaySec, Macro87_Entry9_TimMin, Macro87_Entry9_TimSec, Macro87_Entry9_Protocol, 0, 0, 0, 0,
		         Macro87_Entry10_DelayMin, Macro87_Entry10_DelaySec, Macro87_Entry10_TimMin, Macro87_Entry10_TimSec, Macro87_Entry10_Protocol, 0, 0, 0, 0,
		         Macro87_Entry11_DelayMin, Macro87_Entry11_DelaySec, Macro87_Entry11_TimMin, Macro87_Entry11_TimSec, Macro87_Entry11_Protocol, 0, 0, 0, 0,
		         Macro87_Entry12_DelayMin, Macro87_Entry12_DelaySec, Macro87_Entry12_TimMin, Macro87_Entry12_TimSec, Macro87_Entry12_Protocol, 0, 0, 0, 0,
		         Macro87_Entry13_DelayMin, Macro87_Entry13_DelaySec, Macro87_Entry13_TimMin, Macro87_Entry13_TimSec, Macro87_Entry13_Protocol, 0, 0, 0, 0,
		         Macro87_Entry14_DelayMin, Macro87_Entry14_DelaySec, Macro87_Entry14_TimMin, Macro87_Entry14_TimSec, Macro87_Entry14_Protocol, 0, 0, 0, 0,
		         Macro87_Entry15_DelayMin, Macro87_Entry15_DelaySec, Macro87_Entry15_TimMin, Macro87_Entry15_TimSec, Macro87_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR87_STRING};

const struct super_macro Macro88 = {Macro88_NumEntries,
		         Macro88_Entry1_DelayMin, Macro88_Entry1_DelaySec, Macro88_Entry1_TimMin, Macro88_Entry1_TimSec, Macro88_Entry1_Protocol, 0, 0, 0, 0,
		         Macro88_Entry2_DelayMin, Macro88_Entry2_DelaySec, Macro88_Entry2_TimMin, Macro88_Entry2_TimSec, Macro88_Entry2_Protocol, 0, 0, 0, 0,
		         Macro88_Entry3_DelayMin, Macro88_Entry3_DelaySec, Macro88_Entry3_TimMin, Macro88_Entry3_TimSec, Macro88_Entry3_Protocol, 0, 0, 0, 0,
		         Macro88_Entry4_DelayMin, Macro88_Entry4_DelaySec, Macro88_Entry4_TimMin, Macro88_Entry4_TimSec, Macro88_Entry4_Protocol, 0, 0, 0, 0,
		         Macro88_Entry5_DelayMin, Macro88_Entry5_DelaySec, Macro88_Entry5_TimMin, Macro88_Entry5_TimSec, Macro88_Entry5_Protocol, 0, 0, 0, 0,
		         Macro88_Entry6_DelayMin, Macro88_Entry6_DelaySec, Macro88_Entry6_TimMin, Macro88_Entry6_TimSec, Macro88_Entry6_Protocol, 0, 0, 0, 0,
		         Macro88_Entry7_DelayMin, Macro88_Entry7_DelaySec, Macro88_Entry7_TimMin, Macro88_Entry7_TimSec, Macro88_Entry7_Protocol, 0, 0, 0, 0,
		         Macro88_Entry8_DelayMin, Macro88_Entry8_DelaySec, Macro88_Entry8_TimMin, Macro88_Entry8_TimSec, Macro88_Entry8_Protocol, 0, 0, 0, 0,
		         Macro88_Entry9_DelayMin, Macro88_Entry9_DelaySec, Macro88_Entry9_TimMin, Macro88_Entry9_TimSec, Macro88_Entry9_Protocol, 0, 0, 0, 0,
		         Macro88_Entry10_DelayMin, Macro88_Entry10_DelaySec, Macro88_Entry10_TimMin, Macro88_Entry10_TimSec, Macro88_Entry10_Protocol, 0, 0, 0, 0,
		         Macro88_Entry11_DelayMin, Macro88_Entry11_DelaySec, Macro88_Entry11_TimMin, Macro88_Entry11_TimSec, Macro88_Entry11_Protocol, 0, 0, 0, 0,
		         Macro88_Entry12_DelayMin, Macro88_Entry12_DelaySec, Macro88_Entry12_TimMin, Macro88_Entry12_TimSec, Macro88_Entry12_Protocol, 0, 0, 0, 0,
		         Macro88_Entry13_DelayMin, Macro88_Entry13_DelaySec, Macro88_Entry13_TimMin, Macro88_Entry13_TimSec, Macro88_Entry13_Protocol, 0, 0, 0, 0,
		         Macro88_Entry14_DelayMin, Macro88_Entry14_DelaySec, Macro88_Entry14_TimMin, Macro88_Entry14_TimSec, Macro88_Entry14_Protocol, 0, 0, 0, 0,
		         Macro88_Entry15_DelayMin, Macro88_Entry15_DelaySec, Macro88_Entry15_TimMin, Macro88_Entry15_TimSec, Macro88_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR88_STRING};

const struct super_macro Macro89 = {Macro89_NumEntries,
		         Macro89_Entry1_DelayMin, Macro89_Entry1_DelaySec, Macro89_Entry1_TimMin, Macro89_Entry1_TimSec, Macro89_Entry1_Protocol, 0, 0, 0, 0,
		         Macro89_Entry2_DelayMin, Macro89_Entry2_DelaySec, Macro89_Entry2_TimMin, Macro89_Entry2_TimSec, Macro89_Entry2_Protocol, 0, 0, 0, 0,
		         Macro89_Entry3_DelayMin, Macro89_Entry3_DelaySec, Macro89_Entry3_TimMin, Macro89_Entry3_TimSec, Macro89_Entry3_Protocol, 0, 0, 0, 0,
		         Macro89_Entry4_DelayMin, Macro89_Entry4_DelaySec, Macro89_Entry4_TimMin, Macro89_Entry4_TimSec, Macro89_Entry4_Protocol, 0, 0, 0, 0,
		         Macro89_Entry5_DelayMin, Macro89_Entry5_DelaySec, Macro89_Entry5_TimMin, Macro89_Entry5_TimSec, Macro89_Entry5_Protocol, 0, 0, 0, 0,
		         Macro89_Entry6_DelayMin, Macro89_Entry6_DelaySec, Macro89_Entry6_TimMin, Macro89_Entry6_TimSec, Macro89_Entry6_Protocol, 0, 0, 0, 0,
		         Macro89_Entry7_DelayMin, Macro89_Entry7_DelaySec, Macro89_Entry7_TimMin, Macro89_Entry7_TimSec, Macro89_Entry7_Protocol, 0, 0, 0, 0,
		         Macro89_Entry8_DelayMin, Macro89_Entry8_DelaySec, Macro89_Entry8_TimMin, Macro89_Entry8_TimSec, Macro89_Entry8_Protocol, 0, 0, 0, 0,
		         Macro89_Entry9_DelayMin, Macro89_Entry9_DelaySec, Macro89_Entry9_TimMin, Macro89_Entry9_TimSec, Macro89_Entry9_Protocol, 0, 0, 0, 0,
		         Macro89_Entry10_DelayMin, Macro89_Entry10_DelaySec, Macro89_Entry10_TimMin, Macro89_Entry10_TimSec, Macro89_Entry10_Protocol, 0, 0, 0, 0,
		         Macro89_Entry11_DelayMin, Macro89_Entry11_DelaySec, Macro89_Entry11_TimMin, Macro89_Entry11_TimSec, Macro89_Entry11_Protocol, 0, 0, 0, 0,
		         Macro89_Entry12_DelayMin, Macro89_Entry12_DelaySec, Macro89_Entry12_TimMin, Macro89_Entry12_TimSec, Macro89_Entry12_Protocol, 0, 0, 0, 0,
		         Macro89_Entry13_DelayMin, Macro89_Entry13_DelaySec, Macro89_Entry13_TimMin, Macro89_Entry13_TimSec, Macro89_Entry13_Protocol, 0, 0, 0, 0,
		         Macro89_Entry14_DelayMin, Macro89_Entry14_DelaySec, Macro89_Entry14_TimMin, Macro89_Entry14_TimSec, Macro89_Entry14_Protocol, 0, 0, 0, 0,
		         Macro89_Entry15_DelayMin, Macro89_Entry15_DelaySec, Macro89_Entry15_TimMin, Macro89_Entry15_TimSec, Macro89_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR89_STRING};

const struct super_macro Macro90 = {Macro90_NumEntries,
		         Macro90_Entry1_DelayMin, Macro90_Entry1_DelaySec, Macro90_Entry1_TimMin, Macro90_Entry1_TimSec, Macro90_Entry1_Protocol, 0, 0, 0, 0,
		         Macro90_Entry2_DelayMin, Macro90_Entry2_DelaySec, Macro90_Entry2_TimMin, Macro90_Entry2_TimSec, Macro90_Entry2_Protocol, 0, 0, 0, 0,
		         Macro90_Entry3_DelayMin, Macro90_Entry3_DelaySec, Macro90_Entry3_TimMin, Macro90_Entry3_TimSec, Macro90_Entry3_Protocol, 0, 0, 0, 0,
		         Macro90_Entry4_DelayMin, Macro90_Entry4_DelaySec, Macro90_Entry4_TimMin, Macro90_Entry4_TimSec, Macro90_Entry4_Protocol, 0, 0, 0, 0,
		         Macro90_Entry5_DelayMin, Macro90_Entry5_DelaySec, Macro90_Entry5_TimMin, Macro90_Entry5_TimSec, Macro90_Entry5_Protocol, 0, 0, 0, 0,
		         Macro90_Entry6_DelayMin, Macro90_Entry6_DelaySec, Macro90_Entry6_TimMin, Macro90_Entry6_TimSec, Macro90_Entry6_Protocol, 0, 0, 0, 0,
		         Macro90_Entry7_DelayMin, Macro90_Entry7_DelaySec, Macro90_Entry7_TimMin, Macro90_Entry7_TimSec, Macro90_Entry7_Protocol, 0, 0, 0, 0,
		         Macro90_Entry8_DelayMin, Macro90_Entry8_DelaySec, Macro90_Entry8_TimMin, Macro90_Entry8_TimSec, Macro90_Entry8_Protocol, 0, 0, 0, 0,
		         Macro90_Entry9_DelayMin, Macro90_Entry9_DelaySec, Macro90_Entry9_TimMin, Macro90_Entry9_TimSec, Macro90_Entry9_Protocol, 0, 0, 0, 0,
		         Macro90_Entry10_DelayMin, Macro90_Entry10_DelaySec, Macro90_Entry10_TimMin, Macro90_Entry10_TimSec, Macro90_Entry10_Protocol, 0, 0, 0, 0,
		         Macro90_Entry11_DelayMin, Macro90_Entry11_DelaySec, Macro90_Entry11_TimMin, Macro90_Entry11_TimSec, Macro90_Entry11_Protocol, 0, 0, 0, 0,
		         Macro90_Entry12_DelayMin, Macro90_Entry12_DelaySec, Macro90_Entry12_TimMin, Macro90_Entry12_TimSec, Macro90_Entry12_Protocol, 0, 0, 0, 0,
		         Macro90_Entry13_DelayMin, Macro90_Entry13_DelaySec, Macro90_Entry13_TimMin, Macro90_Entry13_TimSec, Macro90_Entry13_Protocol, 0, 0, 0, 0,
		         Macro90_Entry14_DelayMin, Macro90_Entry14_DelaySec, Macro90_Entry14_TimMin, Macro90_Entry14_TimSec, Macro90_Entry14_Protocol, 0, 0, 0, 0,
		         Macro90_Entry15_DelayMin, Macro90_Entry15_DelaySec, Macro90_Entry15_TimMin, Macro90_Entry15_TimSec, Macro90_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR90_STRING};

const struct super_macro Macro91 = {Macro91_NumEntries,
		         Macro91_Entry1_DelayMin, Macro91_Entry1_DelaySec, Macro91_Entry1_TimMin, Macro91_Entry1_TimSec, Macro91_Entry1_Protocol, 0, 0, 0, 0,
		         Macro91_Entry2_DelayMin, Macro91_Entry2_DelaySec, Macro91_Entry2_TimMin, Macro91_Entry2_TimSec, Macro91_Entry2_Protocol, 0, 0, 0, 0,
		         Macro91_Entry3_DelayMin, Macro91_Entry3_DelaySec, Macro91_Entry3_TimMin, Macro91_Entry3_TimSec, Macro91_Entry3_Protocol, 0, 0, 0, 0,
		         Macro91_Entry4_DelayMin, Macro91_Entry4_DelaySec, Macro91_Entry4_TimMin, Macro91_Entry4_TimSec, Macro91_Entry4_Protocol, 0, 0, 0, 0,
		         Macro91_Entry5_DelayMin, Macro91_Entry5_DelaySec, Macro91_Entry5_TimMin, Macro91_Entry5_TimSec, Macro91_Entry5_Protocol, 0, 0, 0, 0,
		         Macro91_Entry6_DelayMin, Macro91_Entry6_DelaySec, Macro91_Entry6_TimMin, Macro91_Entry6_TimSec, Macro91_Entry6_Protocol, 0, 0, 0, 0,
		         Macro91_Entry7_DelayMin, Macro91_Entry7_DelaySec, Macro91_Entry7_TimMin, Macro91_Entry7_TimSec, Macro91_Entry7_Protocol, 0, 0, 0, 0,
		         Macro91_Entry8_DelayMin, Macro91_Entry8_DelaySec, Macro91_Entry8_TimMin, Macro91_Entry8_TimSec, Macro91_Entry8_Protocol, 0, 0, 0, 0,
		         Macro91_Entry9_DelayMin, Macro91_Entry9_DelaySec, Macro91_Entry9_TimMin, Macro91_Entry9_TimSec, Macro91_Entry9_Protocol, 0, 0, 0, 0,
		         Macro91_Entry10_DelayMin, Macro91_Entry10_DelaySec, Macro91_Entry10_TimMin, Macro91_Entry10_TimSec, Macro91_Entry10_Protocol, 0, 0, 0, 0,
		         Macro91_Entry11_DelayMin, Macro91_Entry11_DelaySec, Macro91_Entry11_TimMin, Macro91_Entry11_TimSec, Macro91_Entry11_Protocol, 0, 0, 0, 0,
		         Macro91_Entry12_DelayMin, Macro91_Entry12_DelaySec, Macro91_Entry12_TimMin, Macro91_Entry12_TimSec, Macro91_Entry12_Protocol, 0, 0, 0, 0,
		         Macro91_Entry13_DelayMin, Macro91_Entry13_DelaySec, Macro91_Entry13_TimMin, Macro91_Entry13_TimSec, Macro91_Entry13_Protocol, 0, 0, 0, 0,
		         Macro91_Entry14_DelayMin, Macro91_Entry14_DelaySec, Macro91_Entry14_TimMin, Macro91_Entry14_TimSec, Macro91_Entry14_Protocol, 0, 0, 0, 0,
		         Macro91_Entry15_DelayMin, Macro91_Entry15_DelaySec, Macro91_Entry15_TimMin, Macro91_Entry15_TimSec, Macro91_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR91_STRING};

const struct super_macro Macro92 = {Macro92_NumEntries,
		         Macro92_Entry1_DelayMin, Macro92_Entry1_DelaySec, Macro92_Entry1_TimMin, Macro92_Entry1_TimSec, Macro92_Entry1_Protocol, 0, 0, 0, 0,
		         Macro92_Entry2_DelayMin, Macro92_Entry2_DelaySec, Macro92_Entry2_TimMin, Macro92_Entry2_TimSec, Macro92_Entry2_Protocol, 0, 0, 0, 0,
		         Macro92_Entry3_DelayMin, Macro92_Entry3_DelaySec, Macro92_Entry3_TimMin, Macro92_Entry3_TimSec, Macro92_Entry3_Protocol, 0, 0, 0, 0,
		         Macro92_Entry4_DelayMin, Macro92_Entry4_DelaySec, Macro92_Entry4_TimMin, Macro92_Entry4_TimSec, Macro92_Entry4_Protocol, 0, 0, 0, 0,
		         Macro92_Entry5_DelayMin, Macro92_Entry5_DelaySec, Macro92_Entry5_TimMin, Macro92_Entry5_TimSec, Macro92_Entry5_Protocol, 0, 0, 0, 0,
		         Macro92_Entry6_DelayMin, Macro92_Entry6_DelaySec, Macro92_Entry6_TimMin, Macro92_Entry6_TimSec, Macro92_Entry6_Protocol, 0, 0, 0, 0,
		         Macro92_Entry7_DelayMin, Macro92_Entry7_DelaySec, Macro92_Entry7_TimMin, Macro92_Entry7_TimSec, Macro92_Entry7_Protocol, 0, 0, 0, 0,
		         Macro92_Entry8_DelayMin, Macro92_Entry8_DelaySec, Macro92_Entry8_TimMin, Macro92_Entry8_TimSec, Macro92_Entry8_Protocol, 0, 0, 0, 0,
		         Macro92_Entry9_DelayMin, Macro92_Entry9_DelaySec, Macro92_Entry9_TimMin, Macro92_Entry9_TimSec, Macro92_Entry9_Protocol, 0, 0, 0, 0,
		         Macro92_Entry10_DelayMin, Macro92_Entry10_DelaySec, Macro92_Entry10_TimMin, Macro92_Entry10_TimSec, Macro92_Entry10_Protocol, 0, 0, 0, 0,
		         Macro92_Entry11_DelayMin, Macro92_Entry11_DelaySec, Macro92_Entry11_TimMin, Macro92_Entry11_TimSec, Macro92_Entry11_Protocol, 0, 0, 0, 0,
		         Macro92_Entry12_DelayMin, Macro92_Entry12_DelaySec, Macro92_Entry12_TimMin, Macro92_Entry12_TimSec, Macro92_Entry12_Protocol, 0, 0, 0, 0,
		         Macro92_Entry13_DelayMin, Macro92_Entry13_DelaySec, Macro92_Entry13_TimMin, Macro92_Entry13_TimSec, Macro92_Entry13_Protocol, 0, 0, 0, 0,
		         Macro92_Entry14_DelayMin, Macro92_Entry14_DelaySec, Macro92_Entry14_TimMin, Macro92_Entry14_TimSec, Macro92_Entry14_Protocol, 0, 0, 0, 0,
		         Macro92_Entry15_DelayMin, Macro92_Entry15_DelaySec, Macro92_Entry15_TimMin, Macro92_Entry15_TimSec, Macro92_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR92_STRING};

const struct super_macro Macro93 = {Macro93_NumEntries,
		         Macro93_Entry1_DelayMin, Macro93_Entry1_DelaySec, Macro93_Entry1_TimMin, Macro93_Entry1_TimSec, Macro93_Entry1_Protocol, 0, 0, 0, 0,
		         Macro93_Entry2_DelayMin, Macro93_Entry2_DelaySec, Macro93_Entry2_TimMin, Macro93_Entry2_TimSec, Macro93_Entry2_Protocol, 0, 0, 0, 0,
		         Macro93_Entry3_DelayMin, Macro93_Entry3_DelaySec, Macro93_Entry3_TimMin, Macro93_Entry3_TimSec, Macro93_Entry3_Protocol, 0, 0, 0, 0,
		         Macro93_Entry4_DelayMin, Macro93_Entry4_DelaySec, Macro93_Entry4_TimMin, Macro93_Entry4_TimSec, Macro93_Entry4_Protocol, 0, 0, 0, 0,
		         Macro93_Entry5_DelayMin, Macro93_Entry5_DelaySec, Macro93_Entry5_TimMin, Macro93_Entry5_TimSec, Macro93_Entry5_Protocol, 0, 0, 0, 0,
		         Macro93_Entry6_DelayMin, Macro93_Entry6_DelaySec, Macro93_Entry6_TimMin, Macro93_Entry6_TimSec, Macro93_Entry6_Protocol, 0, 0, 0, 0,
		         Macro93_Entry7_DelayMin, Macro93_Entry7_DelaySec, Macro93_Entry7_TimMin, Macro93_Entry7_TimSec, Macro93_Entry7_Protocol, 0, 0, 0, 0,
		         Macro93_Entry8_DelayMin, Macro93_Entry8_DelaySec, Macro93_Entry8_TimMin, Macro93_Entry8_TimSec, Macro93_Entry8_Protocol, 0, 0, 0, 0,
		         Macro93_Entry9_DelayMin, Macro93_Entry9_DelaySec, Macro93_Entry9_TimMin, Macro93_Entry9_TimSec, Macro93_Entry9_Protocol, 0, 0, 0, 0,
		         Macro93_Entry10_DelayMin, Macro93_Entry10_DelaySec, Macro93_Entry10_TimMin, Macro93_Entry10_TimSec, Macro93_Entry10_Protocol, 0, 0, 0, 0,
		         Macro93_Entry11_DelayMin, Macro93_Entry11_DelaySec, Macro93_Entry11_TimMin, Macro93_Entry11_TimSec, Macro93_Entry11_Protocol, 0, 0, 0, 0,
		         Macro93_Entry12_DelayMin, Macro93_Entry12_DelaySec, Macro93_Entry12_TimMin, Macro93_Entry12_TimSec, Macro93_Entry12_Protocol, 0, 0, 0, 0,
		         Macro93_Entry13_DelayMin, Macro93_Entry13_DelaySec, Macro93_Entry13_TimMin, Macro93_Entry13_TimSec, Macro93_Entry13_Protocol, 0, 0, 0, 0,
		         Macro93_Entry14_DelayMin, Macro93_Entry14_DelaySec, Macro93_Entry14_TimMin, Macro93_Entry14_TimSec, Macro93_Entry14_Protocol, 0, 0, 0, 0,
		         Macro93_Entry15_DelayMin, Macro93_Entry15_DelaySec, Macro93_Entry15_TimMin, Macro93_Entry15_TimSec, Macro93_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR93_STRING};

const struct super_macro Macro94 = {Macro94_NumEntries,
		         Macro94_Entry1_DelayMin, Macro94_Entry1_DelaySec, Macro94_Entry1_TimMin, Macro94_Entry1_TimSec, Macro94_Entry1_Protocol, 0, 0, 0, 0,
		         Macro94_Entry2_DelayMin, Macro94_Entry2_DelaySec, Macro94_Entry2_TimMin, Macro94_Entry2_TimSec, Macro94_Entry2_Protocol, 0, 0, 0, 0,
		         Macro94_Entry3_DelayMin, Macro94_Entry3_DelaySec, Macro94_Entry3_TimMin, Macro94_Entry3_TimSec, Macro94_Entry3_Protocol, 0, 0, 0, 0,
		         Macro94_Entry4_DelayMin, Macro94_Entry4_DelaySec, Macro94_Entry4_TimMin, Macro94_Entry4_TimSec, Macro94_Entry4_Protocol, 0, 0, 0, 0,
		         Macro94_Entry5_DelayMin, Macro94_Entry5_DelaySec, Macro94_Entry5_TimMin, Macro94_Entry5_TimSec, Macro94_Entry5_Protocol, 0, 0, 0, 0,
		         Macro94_Entry6_DelayMin, Macro94_Entry6_DelaySec, Macro94_Entry6_TimMin, Macro94_Entry6_TimSec, Macro94_Entry6_Protocol, 0, 0, 0, 0,
		         Macro94_Entry7_DelayMin, Macro94_Entry7_DelaySec, Macro94_Entry7_TimMin, Macro94_Entry7_TimSec, Macro94_Entry7_Protocol, 0, 0, 0, 0,
		         Macro94_Entry8_DelayMin, Macro94_Entry8_DelaySec, Macro94_Entry8_TimMin, Macro94_Entry8_TimSec, Macro94_Entry8_Protocol, 0, 0, 0, 0,
		         Macro94_Entry9_DelayMin, Macro94_Entry9_DelaySec, Macro94_Entry9_TimMin, Macro94_Entry9_TimSec, Macro94_Entry9_Protocol, 0, 0, 0, 0,
		         Macro94_Entry10_DelayMin, Macro94_Entry10_DelaySec, Macro94_Entry10_TimMin, Macro94_Entry10_TimSec, Macro94_Entry10_Protocol, 0, 0, 0, 0,
		         Macro94_Entry11_DelayMin, Macro94_Entry11_DelaySec, Macro94_Entry11_TimMin, Macro94_Entry11_TimSec, Macro94_Entry11_Protocol, 0, 0, 0, 0,
		         Macro94_Entry12_DelayMin, Macro94_Entry12_DelaySec, Macro94_Entry12_TimMin, Macro94_Entry12_TimSec, Macro94_Entry12_Protocol, 0, 0, 0, 0,
		         Macro94_Entry13_DelayMin, Macro94_Entry13_DelaySec, Macro94_Entry13_TimMin, Macro94_Entry13_TimSec, Macro94_Entry13_Protocol, 0, 0, 0, 0,
		         Macro94_Entry14_DelayMin, Macro94_Entry14_DelaySec, Macro94_Entry14_TimMin, Macro94_Entry14_TimSec, Macro94_Entry14_Protocol, 0, 0, 0, 0,
		         Macro94_Entry15_DelayMin, Macro94_Entry15_DelaySec, Macro94_Entry15_TimMin, Macro94_Entry15_TimSec, Macro94_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR94_STRING};

const struct super_macro Macro95 = {Macro95_NumEntries,
		         Macro95_Entry1_DelayMin, Macro95_Entry1_DelaySec, Macro95_Entry1_TimMin, Macro95_Entry1_TimSec, Macro95_Entry1_Protocol, 0, 0, 0, 0,
		         Macro95_Entry2_DelayMin, Macro95_Entry2_DelaySec, Macro95_Entry2_TimMin, Macro95_Entry2_TimSec, Macro95_Entry2_Protocol, 0, 0, 0, 0,
		         Macro95_Entry3_DelayMin, Macro95_Entry3_DelaySec, Macro95_Entry3_TimMin, Macro95_Entry3_TimSec, Macro95_Entry3_Protocol, 0, 0, 0, 0,
		         Macro95_Entry4_DelayMin, Macro95_Entry4_DelaySec, Macro95_Entry4_TimMin, Macro95_Entry4_TimSec, Macro95_Entry4_Protocol, 0, 0, 0, 0,
		         Macro95_Entry5_DelayMin, Macro95_Entry5_DelaySec, Macro95_Entry5_TimMin, Macro95_Entry5_TimSec, Macro95_Entry5_Protocol, 0, 0, 0, 0,
		         Macro95_Entry6_DelayMin, Macro95_Entry6_DelaySec, Macro95_Entry6_TimMin, Macro95_Entry6_TimSec, Macro95_Entry6_Protocol, 0, 0, 0, 0,
		         Macro95_Entry7_DelayMin, Macro95_Entry7_DelaySec, Macro95_Entry7_TimMin, Macro95_Entry7_TimSec, Macro95_Entry7_Protocol, 0, 0, 0, 0,
		         Macro95_Entry8_DelayMin, Macro95_Entry8_DelaySec, Macro95_Entry8_TimMin, Macro95_Entry8_TimSec, Macro95_Entry8_Protocol, 0, 0, 0, 0,
		         Macro95_Entry9_DelayMin, Macro95_Entry9_DelaySec, Macro95_Entry9_TimMin, Macro95_Entry9_TimSec, Macro95_Entry9_Protocol, 0, 0, 0, 0,
		         Macro95_Entry10_DelayMin, Macro95_Entry10_DelaySec, Macro95_Entry10_TimMin, Macro95_Entry10_TimSec, Macro95_Entry10_Protocol, 0, 0, 0, 0,
		         Macro95_Entry11_DelayMin, Macro95_Entry11_DelaySec, Macro95_Entry11_TimMin, Macro95_Entry11_TimSec, Macro95_Entry11_Protocol, 0, 0, 0, 0,
		         Macro95_Entry12_DelayMin, Macro95_Entry12_DelaySec, Macro95_Entry12_TimMin, Macro95_Entry12_TimSec, Macro95_Entry12_Protocol, 0, 0, 0, 0,
		         Macro95_Entry13_DelayMin, Macro95_Entry13_DelaySec, Macro95_Entry13_TimMin, Macro95_Entry13_TimSec, Macro95_Entry13_Protocol, 0, 0, 0, 0,
		         Macro95_Entry14_DelayMin, Macro95_Entry14_DelaySec, Macro95_Entry14_TimMin, Macro95_Entry14_TimSec, Macro95_Entry14_Protocol, 0, 0, 0, 0,
		         Macro95_Entry15_DelayMin, Macro95_Entry15_DelaySec, Macro95_Entry15_TimMin, Macro95_Entry15_TimSec, Macro95_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR95_STRING};

const struct super_macro Macro96 = {Macro96_NumEntries,
		         Macro96_Entry1_DelayMin, Macro96_Entry1_DelaySec, Macro96_Entry1_TimMin, Macro96_Entry1_TimSec, Macro96_Entry1_Protocol, 0, 0, 0, 0,
		         Macro96_Entry2_DelayMin, Macro96_Entry2_DelaySec, Macro96_Entry2_TimMin, Macro96_Entry2_TimSec, Macro96_Entry2_Protocol, 0, 0, 0, 0,
		         Macro96_Entry3_DelayMin, Macro96_Entry3_DelaySec, Macro96_Entry3_TimMin, Macro96_Entry3_TimSec, Macro96_Entry3_Protocol, 0, 0, 0, 0,
		         Macro96_Entry4_DelayMin, Macro96_Entry4_DelaySec, Macro96_Entry4_TimMin, Macro96_Entry4_TimSec, Macro96_Entry4_Protocol, 0, 0, 0, 0,
		         Macro96_Entry5_DelayMin, Macro96_Entry5_DelaySec, Macro96_Entry5_TimMin, Macro96_Entry5_TimSec, Macro96_Entry5_Protocol, 0, 0, 0, 0,
		         Macro96_Entry6_DelayMin, Macro96_Entry6_DelaySec, Macro96_Entry6_TimMin, Macro96_Entry6_TimSec, Macro96_Entry6_Protocol, 0, 0, 0, 0,
		         Macro96_Entry7_DelayMin, Macro96_Entry7_DelaySec, Macro96_Entry7_TimMin, Macro96_Entry7_TimSec, Macro96_Entry7_Protocol, 0, 0, 0, 0,
		         Macro96_Entry8_DelayMin, Macro96_Entry8_DelaySec, Macro96_Entry8_TimMin, Macro96_Entry8_TimSec, Macro96_Entry8_Protocol, 0, 0, 0, 0,
		         Macro96_Entry9_DelayMin, Macro96_Entry9_DelaySec, Macro96_Entry9_TimMin, Macro96_Entry9_TimSec, Macro96_Entry9_Protocol, 0, 0, 0, 0,
		         Macro96_Entry10_DelayMin, Macro96_Entry10_DelaySec, Macro96_Entry10_TimMin, Macro96_Entry10_TimSec, Macro96_Entry10_Protocol, 0, 0, 0, 0,
		         Macro96_Entry11_DelayMin, Macro96_Entry11_DelaySec, Macro96_Entry11_TimMin, Macro96_Entry11_TimSec, Macro96_Entry11_Protocol, 0, 0, 0, 0,
		         Macro96_Entry12_DelayMin, Macro96_Entry12_DelaySec, Macro96_Entry12_TimMin, Macro96_Entry12_TimSec, Macro96_Entry12_Protocol, 0, 0, 0, 0,
		         Macro96_Entry13_DelayMin, Macro96_Entry13_DelaySec, Macro96_Entry13_TimMin, Macro96_Entry13_TimSec, Macro96_Entry13_Protocol, 0, 0, 0, 0,
		         Macro96_Entry14_DelayMin, Macro96_Entry14_DelaySec, Macro96_Entry14_TimMin, Macro96_Entry14_TimSec, Macro96_Entry14_Protocol, 0, 0, 0, 0,
		         Macro96_Entry15_DelayMin, Macro96_Entry15_DelaySec, Macro96_Entry15_TimMin, Macro96_Entry15_TimSec, Macro96_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR96_STRING};

const struct super_macro Macro97 = {Macro97_NumEntries,
		         Macro97_Entry1_DelayMin, Macro97_Entry1_DelaySec, Macro97_Entry1_TimMin, Macro97_Entry1_TimSec, Macro97_Entry1_Protocol, 0, 0, 0, 0,
		         Macro97_Entry2_DelayMin, Macro97_Entry2_DelaySec, Macro97_Entry2_TimMin, Macro97_Entry2_TimSec, Macro97_Entry2_Protocol, 0, 0, 0, 0,
		         Macro97_Entry3_DelayMin, Macro97_Entry3_DelaySec, Macro97_Entry3_TimMin, Macro97_Entry3_TimSec, Macro97_Entry3_Protocol, 0, 0, 0, 0,
		         Macro97_Entry4_DelayMin, Macro97_Entry4_DelaySec, Macro97_Entry4_TimMin, Macro97_Entry4_TimSec, Macro97_Entry4_Protocol, 0, 0, 0, 0,
		         Macro97_Entry5_DelayMin, Macro97_Entry5_DelaySec, Macro97_Entry5_TimMin, Macro97_Entry5_TimSec, Macro97_Entry5_Protocol, 0, 0, 0, 0,
		         Macro97_Entry6_DelayMin, Macro97_Entry6_DelaySec, Macro97_Entry6_TimMin, Macro97_Entry6_TimSec, Macro97_Entry6_Protocol, 0, 0, 0, 0,
		         Macro97_Entry7_DelayMin, Macro97_Entry7_DelaySec, Macro97_Entry7_TimMin, Macro97_Entry7_TimSec, Macro97_Entry7_Protocol, 0, 0, 0, 0,
		         Macro97_Entry8_DelayMin, Macro97_Entry8_DelaySec, Macro97_Entry8_TimMin, Macro97_Entry8_TimSec, Macro97_Entry8_Protocol, 0, 0, 0, 0,
		         Macro97_Entry9_DelayMin, Macro97_Entry9_DelaySec, Macro97_Entry9_TimMin, Macro97_Entry9_TimSec, Macro97_Entry9_Protocol, 0, 0, 0, 0,
		         Macro97_Entry10_DelayMin, Macro97_Entry10_DelaySec, Macro97_Entry10_TimMin, Macro97_Entry10_TimSec, Macro97_Entry10_Protocol, 0, 0, 0, 0,
		         Macro97_Entry11_DelayMin, Macro97_Entry11_DelaySec, Macro97_Entry11_TimMin, Macro97_Entry11_TimSec, Macro97_Entry11_Protocol, 0, 0, 0, 0,
		         Macro97_Entry12_DelayMin, Macro97_Entry12_DelaySec, Macro97_Entry12_TimMin, Macro97_Entry12_TimSec, Macro97_Entry12_Protocol, 0, 0, 0, 0,
		         Macro97_Entry13_DelayMin, Macro97_Entry13_DelaySec, Macro97_Entry13_TimMin, Macro97_Entry13_TimSec, Macro97_Entry13_Protocol, 0, 0, 0, 0,
		         Macro97_Entry14_DelayMin, Macro97_Entry14_DelaySec, Macro97_Entry14_TimMin, Macro97_Entry14_TimSec, Macro97_Entry14_Protocol, 0, 0, 0, 0,
		         Macro97_Entry15_DelayMin, Macro97_Entry15_DelaySec, Macro97_Entry15_TimMin, Macro97_Entry15_TimSec, Macro97_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR97_STRING};

const struct super_macro Macro98 = {Macro98_NumEntries,
		         Macro98_Entry1_DelayMin, Macro98_Entry1_DelaySec, Macro98_Entry1_TimMin, Macro98_Entry1_TimSec, Macro98_Entry1_Protocol, 0, 0, 0, 0,
		         Macro98_Entry2_DelayMin, Macro98_Entry2_DelaySec, Macro98_Entry2_TimMin, Macro98_Entry2_TimSec, Macro98_Entry2_Protocol, 0, 0, 0, 0,
		         Macro98_Entry3_DelayMin, Macro98_Entry3_DelaySec, Macro98_Entry3_TimMin, Macro98_Entry3_TimSec, Macro98_Entry3_Protocol, 0, 0, 0, 0,
		         Macro98_Entry4_DelayMin, Macro98_Entry4_DelaySec, Macro98_Entry4_TimMin, Macro98_Entry4_TimSec, Macro98_Entry4_Protocol, 0, 0, 0, 0,
		         Macro98_Entry5_DelayMin, Macro98_Entry5_DelaySec, Macro98_Entry5_TimMin, Macro98_Entry5_TimSec, Macro98_Entry5_Protocol, 0, 0, 0, 0,
		         Macro98_Entry6_DelayMin, Macro98_Entry6_DelaySec, Macro98_Entry6_TimMin, Macro98_Entry6_TimSec, Macro98_Entry6_Protocol, 0, 0, 0, 0,
		         Macro98_Entry7_DelayMin, Macro98_Entry7_DelaySec, Macro98_Entry7_TimMin, Macro98_Entry7_TimSec, Macro98_Entry7_Protocol, 0, 0, 0, 0,
		         Macro98_Entry8_DelayMin, Macro98_Entry8_DelaySec, Macro98_Entry8_TimMin, Macro98_Entry8_TimSec, Macro98_Entry8_Protocol, 0, 0, 0, 0,
		         Macro98_Entry9_DelayMin, Macro98_Entry9_DelaySec, Macro98_Entry9_TimMin, Macro98_Entry9_TimSec, Macro98_Entry9_Protocol, 0, 0, 0, 0,
		         Macro98_Entry10_DelayMin, Macro98_Entry10_DelaySec, Macro98_Entry10_TimMin, Macro98_Entry10_TimSec, Macro98_Entry10_Protocol, 0, 0, 0, 0,
		         Macro98_Entry11_DelayMin, Macro98_Entry11_DelaySec, Macro98_Entry11_TimMin, Macro98_Entry11_TimSec, Macro98_Entry11_Protocol, 0, 0, 0, 0,
		         Macro98_Entry12_DelayMin, Macro98_Entry12_DelaySec, Macro98_Entry12_TimMin, Macro98_Entry12_TimSec, Macro98_Entry12_Protocol, 0, 0, 0, 0,
		         Macro98_Entry13_DelayMin, Macro98_Entry13_DelaySec, Macro98_Entry13_TimMin, Macro98_Entry13_TimSec, Macro98_Entry13_Protocol, 0, 0, 0, 0,
		         Macro98_Entry14_DelayMin, Macro98_Entry14_DelaySec, Macro98_Entry14_TimMin, Macro98_Entry14_TimSec, Macro98_Entry14_Protocol, 0, 0, 0, 0,
		         Macro98_Entry15_DelayMin, Macro98_Entry15_DelaySec, Macro98_Entry15_TimMin, Macro98_Entry15_TimSec, Macro98_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR98_STRING};

const struct super_macro Macro99 = {Macro99_NumEntries,
		         Macro99_Entry1_DelayMin, Macro99_Entry1_DelaySec, Macro99_Entry1_TimMin, Macro99_Entry1_TimSec, Macro99_Entry1_Protocol, 0, 0, 0, 0,
		         Macro99_Entry2_DelayMin, Macro99_Entry2_DelaySec, Macro99_Entry2_TimMin, Macro99_Entry2_TimSec, Macro99_Entry2_Protocol, 0, 0, 0, 0,
		         Macro99_Entry3_DelayMin, Macro99_Entry3_DelaySec, Macro99_Entry3_TimMin, Macro99_Entry3_TimSec, Macro99_Entry3_Protocol, 0, 0, 0, 0,
		         Macro99_Entry4_DelayMin, Macro99_Entry4_DelaySec, Macro99_Entry4_TimMin, Macro99_Entry4_TimSec, Macro99_Entry4_Protocol, 0, 0, 0, 0,
		         Macro99_Entry5_DelayMin, Macro99_Entry5_DelaySec, Macro99_Entry5_TimMin, Macro99_Entry5_TimSec, Macro99_Entry5_Protocol, 0, 0, 0, 0,
		         Macro99_Entry6_DelayMin, Macro99_Entry6_DelaySec, Macro99_Entry6_TimMin, Macro99_Entry6_TimSec, Macro99_Entry6_Protocol, 0, 0, 0, 0,
		         Macro99_Entry7_DelayMin, Macro99_Entry7_DelaySec, Macro99_Entry7_TimMin, Macro99_Entry7_TimSec, Macro99_Entry7_Protocol, 0, 0, 0, 0,
		         Macro99_Entry8_DelayMin, Macro99_Entry8_DelaySec, Macro99_Entry8_TimMin, Macro99_Entry8_TimSec, Macro99_Entry8_Protocol, 0, 0, 0, 0,
		         Macro99_Entry9_DelayMin, Macro99_Entry9_DelaySec, Macro99_Entry9_TimMin, Macro99_Entry9_TimSec, Macro99_Entry9_Protocol, 0, 0, 0, 0,
		         Macro99_Entry10_DelayMin, Macro99_Entry10_DelaySec, Macro99_Entry10_TimMin, Macro99_Entry10_TimSec, Macro99_Entry10_Protocol, 0, 0, 0, 0,
		         Macro99_Entry11_DelayMin, Macro99_Entry11_DelaySec, Macro99_Entry11_TimMin, Macro99_Entry11_TimSec, Macro99_Entry11_Protocol, 0, 0, 0, 0,
		         Macro99_Entry12_DelayMin, Macro99_Entry12_DelaySec, Macro99_Entry12_TimMin, Macro99_Entry12_TimSec, Macro99_Entry12_Protocol, 0, 0, 0, 0,
		         Macro99_Entry13_DelayMin, Macro99_Entry13_DelaySec, Macro99_Entry13_TimMin, Macro99_Entry13_TimSec, Macro99_Entry13_Protocol, 0, 0, 0, 0,
		         Macro99_Entry14_DelayMin, Macro99_Entry14_DelaySec, Macro99_Entry14_TimMin, Macro99_Entry14_TimSec, Macro99_Entry14_Protocol, 0, 0, 0, 0,
		         Macro99_Entry15_DelayMin, Macro99_Entry15_DelaySec, Macro99_Entry15_TimMin, Macro99_Entry15_TimSec, Macro99_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR99_STRING};
/*
const struct super_macro Macro100 = {Macro100_NumEntries,
		         Macro100_Entry1_DelayMin, Macro100_Entry1_DelaySec, Macro100_Entry1_TimMin, Macro100_Entry1_TimSec, Macro100_Entry1_Protocol, 0, 0, 0, 0,
		         Macro100_Entry2_DelayMin, Macro100_Entry2_DelaySec, Macro100_Entry2_TimMin, Macro100_Entry2_TimSec, Macro100_Entry2_Protocol, 0, 0, 0, 0,
		         Macro100_Entry3_DelayMin, Macro100_Entry3_DelaySec, Macro100_Entry3_TimMin, Macro100_Entry3_TimSec, Macro100_Entry3_Protocol, 0, 0, 0, 0,
		         Macro100_Entry4_DelayMin, Macro100_Entry4_DelaySec, Macro100_Entry4_TimMin, Macro100_Entry4_TimSec, Macro100_Entry4_Protocol, 0, 0, 0, 0,
		         Macro100_Entry5_DelayMin, Macro100_Entry5_DelaySec, Macro100_Entry5_TimMin, Macro100_Entry5_TimSec, Macro100_Entry5_Protocol, 0, 0, 0, 0,
		         Macro100_Entry6_DelayMin, Macro100_Entry6_DelaySec, Macro100_Entry6_TimMin, Macro100_Entry6_TimSec, Macro100_Entry6_Protocol, 0, 0, 0, 0,
		         Macro100_Entry7_DelayMin, Macro100_Entry7_DelaySec, Macro100_Entry7_TimMin, Macro100_Entry7_TimSec, Macro100_Entry7_Protocol, 0, 0, 0, 0,
		         Macro100_Entry8_DelayMin, Macro100_Entry8_DelaySec, Macro100_Entry8_TimMin, Macro100_Entry8_TimSec, Macro100_Entry8_Protocol, 0, 0, 0, 0,
		         Macro100_Entry9_DelayMin, Macro100_Entry9_DelaySec, Macro100_Entry9_TimMin, Macro100_Entry9_TimSec, Macro100_Entry9_Protocol, 0, 0, 0, 0,
		         Macro100_Entry10_DelayMin, Macro100_Entry10_DelaySec, Macro100_Entry10_TimMin, Macro100_Entry10_TimSec, Macro100_Entry10_Protocol, 0, 0, 0, 0,
		         Macro100_Entry11_DelayMin, Macro100_Entry11_DelaySec, Macro100_Entry11_TimMin, Macro100_Entry11_TimSec, Macro100_Entry11_Protocol, 0, 0, 0, 0,
		         Macro100_Entry12_DelayMin, Macro100_Entry12_DelaySec, Macro100_Entry12_TimMin, Macro100_Entry12_TimSec, Macro100_Entry12_Protocol, 0, 0, 0, 0,
		         Macro100_Entry13_DelayMin, Macro100_Entry13_DelaySec, Macro100_Entry13_TimMin, Macro100_Entry13_TimSec, Macro100_Entry13_Protocol, 0, 0, 0, 0,
		         Macro100_Entry14_DelayMin, Macro100_Entry14_DelaySec, Macro100_Entry14_TimMin, Macro100_Entry14_TimSec, Macro100_Entry14_Protocol, 0, 0, 0, 0,
		         Macro100_Entry15_DelayMin, Macro100_Entry15_DelaySec, Macro100_Entry15_TimMin, Macro100_Entry15_TimSec, Macro100_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR100_STRING};

const struct super_macro Macro101 = {Macro101_NumEntries,
		         Macro101_Entry1_DelayMin, Macro101_Entry1_DelaySec, Macro101_Entry1_TimMin, Macro101_Entry1_TimSec, Macro101_Entry1_Protocol, 0, 0, 0, 0,
		         Macro101_Entry2_DelayMin, Macro101_Entry2_DelaySec, Macro101_Entry2_TimMin, Macro101_Entry2_TimSec, Macro101_Entry2_Protocol, 0, 0, 0, 0,
		         Macro101_Entry3_DelayMin, Macro101_Entry3_DelaySec, Macro101_Entry3_TimMin, Macro101_Entry3_TimSec, Macro101_Entry3_Protocol, 0, 0, 0, 0,
		         Macro101_Entry4_DelayMin, Macro101_Entry4_DelaySec, Macro101_Entry4_TimMin, Macro101_Entry4_TimSec, Macro101_Entry4_Protocol, 0, 0, 0, 0,
		         Macro101_Entry5_DelayMin, Macro101_Entry5_DelaySec, Macro101_Entry5_TimMin, Macro101_Entry5_TimSec, Macro101_Entry5_Protocol, 0, 0, 0, 0,
		         Macro101_Entry6_DelayMin, Macro101_Entry6_DelaySec, Macro101_Entry6_TimMin, Macro101_Entry6_TimSec, Macro101_Entry6_Protocol, 0, 0, 0, 0,
		         Macro101_Entry7_DelayMin, Macro101_Entry7_DelaySec, Macro101_Entry7_TimMin, Macro101_Entry7_TimSec, Macro101_Entry7_Protocol, 0, 0, 0, 0,
		         Macro101_Entry8_DelayMin, Macro101_Entry8_DelaySec, Macro101_Entry8_TimMin, Macro101_Entry8_TimSec, Macro101_Entry8_Protocol, 0, 0, 0, 0,
		         Macro101_Entry9_DelayMin, Macro101_Entry9_DelaySec, Macro101_Entry9_TimMin, Macro101_Entry9_TimSec, Macro101_Entry9_Protocol, 0, 0, 0, 0,
		         Macro101_Entry10_DelayMin, Macro101_Entry10_DelaySec, Macro101_Entry10_TimMin, Macro101_Entry10_TimSec, Macro101_Entry10_Protocol, 0, 0, 0, 0,
		         Macro101_Entry11_DelayMin, Macro101_Entry11_DelaySec, Macro101_Entry11_TimMin, Macro101_Entry11_TimSec, Macro101_Entry11_Protocol, 0, 0, 0, 0,
		         Macro101_Entry12_DelayMin, Macro101_Entry12_DelaySec, Macro101_Entry12_TimMin, Macro101_Entry12_TimSec, Macro101_Entry12_Protocol, 0, 0, 0, 0,
		         Macro101_Entry13_DelayMin, Macro101_Entry13_DelaySec, Macro101_Entry13_TimMin, Macro101_Entry13_TimSec, Macro101_Entry13_Protocol, 0, 0, 0, 0,
		         Macro101_Entry14_DelayMin, Macro101_Entry14_DelaySec, Macro101_Entry14_TimMin, Macro101_Entry14_TimSec, Macro101_Entry14_Protocol, 0, 0, 0, 0,
		         Macro101_Entry15_DelayMin, Macro101_Entry15_DelaySec, Macro101_Entry15_TimMin, Macro101_Entry15_TimSec, Macro101_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR101_STRING};

const struct super_macro Macro102 = {Macro102_NumEntries,
		         Macro102_Entry1_DelayMin, Macro102_Entry1_DelaySec, Macro102_Entry1_TimMin, Macro102_Entry1_TimSec, Macro102_Entry1_Protocol, 0, 0, 0, 0,
		         Macro102_Entry2_DelayMin, Macro102_Entry2_DelaySec, Macro102_Entry2_TimMin, Macro102_Entry2_TimSec, Macro102_Entry2_Protocol, 0, 0, 0, 0,
		         Macro102_Entry3_DelayMin, Macro102_Entry3_DelaySec, Macro102_Entry3_TimMin, Macro102_Entry3_TimSec, Macro102_Entry3_Protocol, 0, 0, 0, 0,
		         Macro102_Entry4_DelayMin, Macro102_Entry4_DelaySec, Macro102_Entry4_TimMin, Macro102_Entry4_TimSec, Macro102_Entry4_Protocol, 0, 0, 0, 0,
		         Macro102_Entry5_DelayMin, Macro102_Entry5_DelaySec, Macro102_Entry5_TimMin, Macro102_Entry5_TimSec, Macro102_Entry5_Protocol, 0, 0, 0, 0,
		         Macro102_Entry6_DelayMin, Macro102_Entry6_DelaySec, Macro102_Entry6_TimMin, Macro102_Entry6_TimSec, Macro102_Entry6_Protocol, 0, 0, 0, 0,
		         Macro102_Entry7_DelayMin, Macro102_Entry7_DelaySec, Macro102_Entry7_TimMin, Macro102_Entry7_TimSec, Macro102_Entry7_Protocol, 0, 0, 0, 0,
		         Macro102_Entry8_DelayMin, Macro102_Entry8_DelaySec, Macro102_Entry8_TimMin, Macro102_Entry8_TimSec, Macro102_Entry8_Protocol, 0, 0, 0, 0,
		         Macro102_Entry9_DelayMin, Macro102_Entry9_DelaySec, Macro102_Entry9_TimMin, Macro102_Entry9_TimSec, Macro102_Entry9_Protocol, 0, 0, 0, 0,
		         Macro102_Entry10_DelayMin, Macro102_Entry10_DelaySec, Macro102_Entry10_TimMin, Macro102_Entry10_TimSec, Macro102_Entry10_Protocol, 0, 0, 0, 0,
		         Macro102_Entry11_DelayMin, Macro102_Entry11_DelaySec, Macro102_Entry11_TimMin, Macro102_Entry11_TimSec, Macro102_Entry11_Protocol, 0, 0, 0, 0,
		         Macro102_Entry12_DelayMin, Macro102_Entry12_DelaySec, Macro102_Entry12_TimMin, Macro102_Entry12_TimSec, Macro102_Entry12_Protocol, 0, 0, 0, 0,
		         Macro102_Entry13_DelayMin, Macro102_Entry13_DelaySec, Macro102_Entry13_TimMin, Macro102_Entry13_TimSec, Macro102_Entry13_Protocol, 0, 0, 0, 0,
		         Macro102_Entry14_DelayMin, Macro102_Entry14_DelaySec, Macro102_Entry14_TimMin, Macro102_Entry14_TimSec, Macro102_Entry14_Protocol, 0, 0, 0, 0,
		         Macro102_Entry15_DelayMin, Macro102_Entry15_DelaySec, Macro102_Entry15_TimMin, Macro102_Entry15_TimSec, Macro102_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR102_STRING};

const struct super_macro Macro103 = {Macro103_NumEntries,
		         Macro103_Entry1_DelayMin, Macro103_Entry1_DelaySec, Macro103_Entry1_TimMin, Macro103_Entry1_TimSec, Macro103_Entry1_Protocol, 0, 0, 0, 0,
		         Macro103_Entry2_DelayMin, Macro103_Entry2_DelaySec, Macro103_Entry2_TimMin, Macro103_Entry2_TimSec, Macro103_Entry2_Protocol, 0, 0, 0, 0,
		         Macro103_Entry3_DelayMin, Macro103_Entry3_DelaySec, Macro103_Entry3_TimMin, Macro103_Entry3_TimSec, Macro103_Entry3_Protocol, 0, 0, 0, 0,
		         Macro103_Entry4_DelayMin, Macro103_Entry4_DelaySec, Macro103_Entry4_TimMin, Macro103_Entry4_TimSec, Macro103_Entry4_Protocol, 0, 0, 0, 0,
		         Macro103_Entry5_DelayMin, Macro103_Entry5_DelaySec, Macro103_Entry5_TimMin, Macro103_Entry5_TimSec, Macro103_Entry5_Protocol, 0, 0, 0, 0,
		         Macro103_Entry6_DelayMin, Macro103_Entry6_DelaySec, Macro103_Entry6_TimMin, Macro103_Entry6_TimSec, Macro103_Entry6_Protocol, 0, 0, 0, 0,
		         Macro103_Entry7_DelayMin, Macro103_Entry7_DelaySec, Macro103_Entry7_TimMin, Macro103_Entry7_TimSec, Macro103_Entry7_Protocol, 0, 0, 0, 0,
		         Macro103_Entry8_DelayMin, Macro103_Entry8_DelaySec, Macro103_Entry8_TimMin, Macro103_Entry8_TimSec, Macro103_Entry8_Protocol, 0, 0, 0, 0,
		         Macro103_Entry9_DelayMin, Macro103_Entry9_DelaySec, Macro103_Entry9_TimMin, Macro103_Entry9_TimSec, Macro103_Entry9_Protocol, 0, 0, 0, 0,
		         Macro103_Entry10_DelayMin, Macro103_Entry10_DelaySec, Macro103_Entry10_TimMin, Macro103_Entry10_TimSec, Macro103_Entry10_Protocol, 0, 0, 0, 0,
		         Macro103_Entry11_DelayMin, Macro103_Entry11_DelaySec, Macro103_Entry11_TimMin, Macro103_Entry11_TimSec, Macro103_Entry11_Protocol, 0, 0, 0, 0,
		         Macro103_Entry12_DelayMin, Macro103_Entry12_DelaySec, Macro103_Entry12_TimMin, Macro103_Entry12_TimSec, Macro103_Entry12_Protocol, 0, 0, 0, 0,
		         Macro103_Entry13_DelayMin, Macro103_Entry13_DelaySec, Macro103_Entry13_TimMin, Macro103_Entry13_TimSec, Macro103_Entry13_Protocol, 0, 0, 0, 0,
		         Macro103_Entry14_DelayMin, Macro103_Entry14_DelaySec, Macro103_Entry14_TimMin, Macro103_Entry14_TimSec, Macro103_Entry14_Protocol, 0, 0, 0, 0,
		         Macro103_Entry15_DelayMin, Macro103_Entry15_DelaySec, Macro103_Entry15_TimMin, Macro103_Entry15_TimSec, Macro103_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR103_STRING};

const struct super_macro Macro104 = {Macro104_NumEntries,
		         Macro104_Entry1_DelayMin, Macro104_Entry1_DelaySec, Macro104_Entry1_TimMin, Macro104_Entry1_TimSec, Macro104_Entry1_Protocol, 0, 0, 0, 0,
		         Macro104_Entry2_DelayMin, Macro104_Entry2_DelaySec, Macro104_Entry2_TimMin, Macro104_Entry2_TimSec, Macro104_Entry2_Protocol, 0, 0, 0, 0,
		         Macro104_Entry3_DelayMin, Macro104_Entry3_DelaySec, Macro104_Entry3_TimMin, Macro104_Entry3_TimSec, Macro104_Entry3_Protocol, 0, 0, 0, 0,
		         Macro104_Entry4_DelayMin, Macro104_Entry4_DelaySec, Macro104_Entry4_TimMin, Macro104_Entry4_TimSec, Macro104_Entry4_Protocol, 0, 0, 0, 0,
		         Macro104_Entry5_DelayMin, Macro104_Entry5_DelaySec, Macro104_Entry5_TimMin, Macro104_Entry5_TimSec, Macro104_Entry5_Protocol, 0, 0, 0, 0,
		         Macro104_Entry6_DelayMin, Macro104_Entry6_DelaySec, Macro104_Entry6_TimMin, Macro104_Entry6_TimSec, Macro104_Entry6_Protocol, 0, 0, 0, 0,
		         Macro104_Entry7_DelayMin, Macro104_Entry7_DelaySec, Macro104_Entry7_TimMin, Macro104_Entry7_TimSec, Macro104_Entry7_Protocol, 0, 0, 0, 0,
		         Macro104_Entry8_DelayMin, Macro104_Entry8_DelaySec, Macro104_Entry8_TimMin, Macro104_Entry8_TimSec, Macro104_Entry8_Protocol, 0, 0, 0, 0,
		         Macro104_Entry9_DelayMin, Macro104_Entry9_DelaySec, Macro104_Entry9_TimMin, Macro104_Entry9_TimSec, Macro104_Entry9_Protocol, 0, 0, 0, 0,
		         Macro104_Entry10_DelayMin, Macro104_Entry10_DelaySec, Macro104_Entry10_TimMin, Macro104_Entry10_TimSec, Macro104_Entry10_Protocol, 0, 0, 0, 0,
		         Macro104_Entry11_DelayMin, Macro104_Entry11_DelaySec, Macro104_Entry11_TimMin, Macro104_Entry11_TimSec, Macro104_Entry11_Protocol, 0, 0, 0, 0,
		         Macro104_Entry12_DelayMin, Macro104_Entry12_DelaySec, Macro104_Entry12_TimMin, Macro104_Entry12_TimSec, Macro104_Entry12_Protocol, 0, 0, 0, 0,
		         Macro104_Entry13_DelayMin, Macro104_Entry13_DelaySec, Macro104_Entry13_TimMin, Macro104_Entry13_TimSec, Macro104_Entry13_Protocol, 0, 0, 0, 0,
		         Macro104_Entry14_DelayMin, Macro104_Entry14_DelaySec, Macro104_Entry14_TimMin, Macro104_Entry14_TimSec, Macro104_Entry14_Protocol, 0, 0, 0, 0,
		         Macro104_Entry15_DelayMin, Macro104_Entry15_DelaySec, Macro104_Entry15_TimMin, Macro104_Entry15_TimSec, Macro104_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR104_STRING};

const struct super_macro Macro105 = {Macro105_NumEntries,
		         Macro105_Entry1_DelayMin, Macro105_Entry1_DelaySec, Macro105_Entry1_TimMin, Macro105_Entry1_TimSec, Macro105_Entry1_Protocol, 0, 0, 0, 0,
		         Macro105_Entry2_DelayMin, Macro105_Entry2_DelaySec, Macro105_Entry2_TimMin, Macro105_Entry2_TimSec, Macro105_Entry2_Protocol, 0, 0, 0, 0,
		         Macro105_Entry3_DelayMin, Macro105_Entry3_DelaySec, Macro105_Entry3_TimMin, Macro105_Entry3_TimSec, Macro105_Entry3_Protocol, 0, 0, 0, 0,
		         Macro105_Entry4_DelayMin, Macro105_Entry4_DelaySec, Macro105_Entry4_TimMin, Macro105_Entry4_TimSec, Macro105_Entry4_Protocol, 0, 0, 0, 0,
		         Macro105_Entry5_DelayMin, Macro105_Entry5_DelaySec, Macro105_Entry5_TimMin, Macro105_Entry5_TimSec, Macro105_Entry5_Protocol, 0, 0, 0, 0,
		         Macro105_Entry6_DelayMin, Macro105_Entry6_DelaySec, Macro105_Entry6_TimMin, Macro105_Entry6_TimSec, Macro105_Entry6_Protocol, 0, 0, 0, 0,
		         Macro105_Entry7_DelayMin, Macro105_Entry7_DelaySec, Macro105_Entry7_TimMin, Macro105_Entry7_TimSec, Macro105_Entry7_Protocol, 0, 0, 0, 0,
		         Macro105_Entry8_DelayMin, Macro105_Entry8_DelaySec, Macro105_Entry8_TimMin, Macro105_Entry8_TimSec, Macro105_Entry8_Protocol, 0, 0, 0, 0,
		         Macro105_Entry9_DelayMin, Macro105_Entry9_DelaySec, Macro105_Entry9_TimMin, Macro105_Entry9_TimSec, Macro105_Entry9_Protocol, 0, 0, 0, 0,
		         Macro105_Entry10_DelayMin, Macro105_Entry10_DelaySec, Macro105_Entry10_TimMin, Macro105_Entry10_TimSec, Macro105_Entry10_Protocol, 0, 0, 0, 0,
		         Macro105_Entry11_DelayMin, Macro105_Entry11_DelaySec, Macro105_Entry11_TimMin, Macro105_Entry11_TimSec, Macro105_Entry11_Protocol, 0, 0, 0, 0,
		         Macro105_Entry12_DelayMin, Macro105_Entry12_DelaySec, Macro105_Entry12_TimMin, Macro105_Entry12_TimSec, Macro105_Entry12_Protocol, 0, 0, 0, 0,
		         Macro105_Entry13_DelayMin, Macro105_Entry13_DelaySec, Macro105_Entry13_TimMin, Macro105_Entry13_TimSec, Macro105_Entry13_Protocol, 0, 0, 0, 0,
		         Macro105_Entry14_DelayMin, Macro105_Entry14_DelaySec, Macro105_Entry14_TimMin, Macro105_Entry14_TimSec, Macro105_Entry14_Protocol, 0, 0, 0, 0,
		         Macro105_Entry15_DelayMin, Macro105_Entry15_DelaySec, Macro105_Entry15_TimMin, Macro105_Entry15_TimSec, Macro105_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR105_STRING};

const struct super_macro Macro106 = {Macro106_NumEntries,
		         Macro106_Entry1_DelayMin, Macro106_Entry1_DelaySec, Macro106_Entry1_TimMin, Macro106_Entry1_TimSec, Macro106_Entry1_Protocol, 0, 0, 0, 0,
		         Macro106_Entry2_DelayMin, Macro106_Entry2_DelaySec, Macro106_Entry2_TimMin, Macro106_Entry2_TimSec, Macro106_Entry2_Protocol, 0, 0, 0, 0,
		         Macro106_Entry3_DelayMin, Macro106_Entry3_DelaySec, Macro106_Entry3_TimMin, Macro106_Entry3_TimSec, Macro106_Entry3_Protocol, 0, 0, 0, 0,
		         Macro106_Entry4_DelayMin, Macro106_Entry4_DelaySec, Macro106_Entry4_TimMin, Macro106_Entry4_TimSec, Macro106_Entry4_Protocol, 0, 0, 0, 0,
		         Macro106_Entry5_DelayMin, Macro106_Entry5_DelaySec, Macro106_Entry5_TimMin, Macro106_Entry5_TimSec, Macro106_Entry5_Protocol, 0, 0, 0, 0,
		         Macro106_Entry6_DelayMin, Macro106_Entry6_DelaySec, Macro106_Entry6_TimMin, Macro106_Entry6_TimSec, Macro106_Entry6_Protocol, 0, 0, 0, 0,
		         Macro106_Entry7_DelayMin, Macro106_Entry7_DelaySec, Macro106_Entry7_TimMin, Macro106_Entry7_TimSec, Macro106_Entry7_Protocol, 0, 0, 0, 0,
		         Macro106_Entry8_DelayMin, Macro106_Entry8_DelaySec, Macro106_Entry8_TimMin, Macro106_Entry8_TimSec, Macro106_Entry8_Protocol, 0, 0, 0, 0,
		         Macro106_Entry9_DelayMin, Macro106_Entry9_DelaySec, Macro106_Entry9_TimMin, Macro106_Entry9_TimSec, Macro106_Entry9_Protocol, 0, 0, 0, 0,
		         Macro106_Entry10_DelayMin, Macro106_Entry10_DelaySec, Macro106_Entry10_TimMin, Macro106_Entry10_TimSec, Macro106_Entry10_Protocol, 0, 0, 0, 0,
		         Macro106_Entry11_DelayMin, Macro106_Entry11_DelaySec, Macro106_Entry11_TimMin, Macro106_Entry11_TimSec, Macro106_Entry11_Protocol, 0, 0, 0, 0,
		         Macro106_Entry12_DelayMin, Macro106_Entry12_DelaySec, Macro106_Entry12_TimMin, Macro106_Entry12_TimSec, Macro106_Entry12_Protocol, 0, 0, 0, 0,
		         Macro106_Entry13_DelayMin, Macro106_Entry13_DelaySec, Macro106_Entry13_TimMin, Macro106_Entry13_TimSec, Macro106_Entry13_Protocol, 0, 0, 0, 0,
		         Macro106_Entry14_DelayMin, Macro106_Entry14_DelaySec, Macro106_Entry14_TimMin, Macro106_Entry14_TimSec, Macro106_Entry14_Protocol, 0, 0, 0, 0,
		         Macro106_Entry15_DelayMin, Macro106_Entry15_DelaySec, Macro106_Entry15_TimMin, Macro106_Entry15_TimSec, Macro106_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR106_STRING};

const struct super_macro Macro107 = {Macro107_NumEntries,
		         Macro107_Entry1_DelayMin, Macro107_Entry1_DelaySec, Macro107_Entry1_TimMin, Macro107_Entry1_TimSec, Macro107_Entry1_Protocol, 0, 0, 0, 0,
		         Macro107_Entry2_DelayMin, Macro107_Entry2_DelaySec, Macro107_Entry2_TimMin, Macro107_Entry2_TimSec, Macro107_Entry2_Protocol, 0, 0, 0, 0,
		         Macro107_Entry3_DelayMin, Macro107_Entry3_DelaySec, Macro107_Entry3_TimMin, Macro107_Entry3_TimSec, Macro107_Entry3_Protocol, 0, 0, 0, 0,
		         Macro107_Entry4_DelayMin, Macro107_Entry4_DelaySec, Macro107_Entry4_TimMin, Macro107_Entry4_TimSec, Macro107_Entry4_Protocol, 0, 0, 0, 0,
		         Macro107_Entry5_DelayMin, Macro107_Entry5_DelaySec, Macro107_Entry5_TimMin, Macro107_Entry5_TimSec, Macro107_Entry5_Protocol, 0, 0, 0, 0,
		         Macro107_Entry6_DelayMin, Macro107_Entry6_DelaySec, Macro107_Entry6_TimMin, Macro107_Entry6_TimSec, Macro107_Entry6_Protocol, 0, 0, 0, 0,
		         Macro107_Entry7_DelayMin, Macro107_Entry7_DelaySec, Macro107_Entry7_TimMin, Macro107_Entry7_TimSec, Macro107_Entry7_Protocol, 0, 0, 0, 0,
		         Macro107_Entry8_DelayMin, Macro107_Entry8_DelaySec, Macro107_Entry8_TimMin, Macro107_Entry8_TimSec, Macro107_Entry8_Protocol, 0, 0, 0, 0,
		         Macro107_Entry9_DelayMin, Macro107_Entry9_DelaySec, Macro107_Entry9_TimMin, Macro107_Entry9_TimSec, Macro107_Entry9_Protocol, 0, 0, 0, 0,
		         Macro107_Entry10_DelayMin, Macro107_Entry10_DelaySec, Macro107_Entry10_TimMin, Macro107_Entry10_TimSec, Macro107_Entry10_Protocol, 0, 0, 0, 0,
		         Macro107_Entry11_DelayMin, Macro107_Entry11_DelaySec, Macro107_Entry11_TimMin, Macro107_Entry11_TimSec, Macro107_Entry11_Protocol, 0, 0, 0, 0,
		         Macro107_Entry12_DelayMin, Macro107_Entry12_DelaySec, Macro107_Entry12_TimMin, Macro107_Entry12_TimSec, Macro107_Entry12_Protocol, 0, 0, 0, 0,
		         Macro107_Entry13_DelayMin, Macro107_Entry13_DelaySec, Macro107_Entry13_TimMin, Macro107_Entry13_TimSec, Macro107_Entry13_Protocol, 0, 0, 0, 0,
		         Macro107_Entry14_DelayMin, Macro107_Entry14_DelaySec, Macro107_Entry14_TimMin, Macro107_Entry14_TimSec, Macro107_Entry14_Protocol, 0, 0, 0, 0,
		         Macro107_Entry15_DelayMin, Macro107_Entry15_DelaySec, Macro107_Entry15_TimMin, Macro107_Entry15_TimSec, Macro107_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR107_STRING};

const struct super_macro Macro108 = {Macro108_NumEntries,
		         Macro108_Entry1_DelayMin, Macro108_Entry1_DelaySec, Macro108_Entry1_TimMin, Macro108_Entry1_TimSec, Macro108_Entry1_Protocol, 0, 0, 0, 0,
		         Macro108_Entry2_DelayMin, Macro108_Entry2_DelaySec, Macro108_Entry2_TimMin, Macro108_Entry2_TimSec, Macro108_Entry2_Protocol, 0, 0, 0, 0,
		         Macro108_Entry3_DelayMin, Macro108_Entry3_DelaySec, Macro108_Entry3_TimMin, Macro108_Entry3_TimSec, Macro108_Entry3_Protocol, 0, 0, 0, 0,
		         Macro108_Entry4_DelayMin, Macro108_Entry4_DelaySec, Macro108_Entry4_TimMin, Macro108_Entry4_TimSec, Macro108_Entry4_Protocol, 0, 0, 0, 0,
		         Macro108_Entry5_DelayMin, Macro108_Entry5_DelaySec, Macro108_Entry5_TimMin, Macro108_Entry5_TimSec, Macro108_Entry5_Protocol, 0, 0, 0, 0,
		         Macro108_Entry6_DelayMin, Macro108_Entry6_DelaySec, Macro108_Entry6_TimMin, Macro108_Entry6_TimSec, Macro108_Entry6_Protocol, 0, 0, 0, 0,
		         Macro108_Entry7_DelayMin, Macro108_Entry7_DelaySec, Macro108_Entry7_TimMin, Macro108_Entry7_TimSec, Macro108_Entry7_Protocol, 0, 0, 0, 0,
		         Macro108_Entry8_DelayMin, Macro108_Entry8_DelaySec, Macro108_Entry8_TimMin, Macro108_Entry8_TimSec, Macro108_Entry8_Protocol, 0, 0, 0, 0,
		         Macro108_Entry9_DelayMin, Macro108_Entry9_DelaySec, Macro108_Entry9_TimMin, Macro108_Entry9_TimSec, Macro108_Entry9_Protocol, 0, 0, 0, 0,
		         Macro108_Entry10_DelayMin, Macro108_Entry10_DelaySec, Macro108_Entry10_TimMin, Macro108_Entry10_TimSec, Macro108_Entry10_Protocol, 0, 0, 0, 0,
		         Macro108_Entry11_DelayMin, Macro108_Entry11_DelaySec, Macro108_Entry11_TimMin, Macro108_Entry11_TimSec, Macro108_Entry11_Protocol, 0, 0, 0, 0,
		         Macro108_Entry12_DelayMin, Macro108_Entry12_DelaySec, Macro108_Entry12_TimMin, Macro108_Entry12_TimSec, Macro108_Entry12_Protocol, 0, 0, 0, 0,
		         Macro108_Entry13_DelayMin, Macro108_Entry13_DelaySec, Macro108_Entry13_TimMin, Macro108_Entry13_TimSec, Macro108_Entry13_Protocol, 0, 0, 0, 0,
		         Macro108_Entry14_DelayMin, Macro108_Entry14_DelaySec, Macro108_Entry14_TimMin, Macro108_Entry14_TimSec, Macro108_Entry14_Protocol, 0, 0, 0, 0,
		         Macro108_Entry15_DelayMin, Macro108_Entry15_DelaySec, Macro108_Entry15_TimMin, Macro108_Entry15_TimSec, Macro108_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR108_STRING};

const struct super_macro Macro109 = {Macro109_NumEntries,
		         Macro109_Entry1_DelayMin, Macro109_Entry1_DelaySec, Macro109_Entry1_TimMin, Macro109_Entry1_TimSec, Macro109_Entry1_Protocol, 0, 0, 0, 0,
		         Macro109_Entry2_DelayMin, Macro109_Entry2_DelaySec, Macro109_Entry2_TimMin, Macro109_Entry2_TimSec, Macro109_Entry2_Protocol, 0, 0, 0, 0,
		         Macro109_Entry3_DelayMin, Macro109_Entry3_DelaySec, Macro109_Entry3_TimMin, Macro109_Entry3_TimSec, Macro109_Entry3_Protocol, 0, 0, 0, 0,
		         Macro109_Entry4_DelayMin, Macro109_Entry4_DelaySec, Macro109_Entry4_TimMin, Macro109_Entry4_TimSec, Macro109_Entry4_Protocol, 0, 0, 0, 0,
		         Macro109_Entry5_DelayMin, Macro109_Entry5_DelaySec, Macro109_Entry5_TimMin, Macro109_Entry5_TimSec, Macro109_Entry5_Protocol, 0, 0, 0, 0,
		         Macro109_Entry6_DelayMin, Macro109_Entry6_DelaySec, Macro109_Entry6_TimMin, Macro109_Entry6_TimSec, Macro109_Entry6_Protocol, 0, 0, 0, 0,
		         Macro109_Entry7_DelayMin, Macro109_Entry7_DelaySec, Macro109_Entry7_TimMin, Macro109_Entry7_TimSec, Macro109_Entry7_Protocol, 0, 0, 0, 0,
		         Macro109_Entry8_DelayMin, Macro109_Entry8_DelaySec, Macro109_Entry8_TimMin, Macro109_Entry8_TimSec, Macro109_Entry8_Protocol, 0, 0, 0, 0,
		         Macro109_Entry9_DelayMin, Macro109_Entry9_DelaySec, Macro109_Entry9_TimMin, Macro109_Entry9_TimSec, Macro109_Entry9_Protocol, 0, 0, 0, 0,
		         Macro109_Entry10_DelayMin, Macro109_Entry10_DelaySec, Macro109_Entry10_TimMin, Macro109_Entry10_TimSec, Macro109_Entry10_Protocol, 0, 0, 0, 0,
		         Macro109_Entry11_DelayMin, Macro109_Entry11_DelaySec, Macro109_Entry11_TimMin, Macro109_Entry11_TimSec, Macro109_Entry11_Protocol, 0, 0, 0, 0,
		         Macro109_Entry12_DelayMin, Macro109_Entry12_DelaySec, Macro109_Entry12_TimMin, Macro109_Entry12_TimSec, Macro109_Entry12_Protocol, 0, 0, 0, 0,
		         Macro109_Entry13_DelayMin, Macro109_Entry13_DelaySec, Macro109_Entry13_TimMin, Macro109_Entry13_TimSec, Macro109_Entry13_Protocol, 0, 0, 0, 0,
		         Macro109_Entry14_DelayMin, Macro109_Entry14_DelaySec, Macro109_Entry14_TimMin, Macro109_Entry14_TimSec, Macro109_Entry14_Protocol, 0, 0, 0, 0,
		         Macro109_Entry15_DelayMin, Macro109_Entry15_DelaySec, Macro109_Entry15_TimMin, Macro109_Entry15_TimSec, Macro109_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR109_STRING};

const struct super_macro Macro110 = {Macro110_NumEntries,
		         Macro110_Entry1_DelayMin, Macro110_Entry1_DelaySec, Macro110_Entry1_TimMin, Macro110_Entry1_TimSec, Macro110_Entry1_Protocol, 0, 0, 0, 0,
		         Macro110_Entry2_DelayMin, Macro110_Entry2_DelaySec, Macro110_Entry2_TimMin, Macro110_Entry2_TimSec, Macro110_Entry2_Protocol, 0, 0, 0, 0,
		         Macro110_Entry3_DelayMin, Macro110_Entry3_DelaySec, Macro110_Entry3_TimMin, Macro110_Entry3_TimSec, Macro110_Entry3_Protocol, 0, 0, 0, 0,
		         Macro110_Entry4_DelayMin, Macro110_Entry4_DelaySec, Macro110_Entry4_TimMin, Macro110_Entry4_TimSec, Macro110_Entry4_Protocol, 0, 0, 0, 0,
		         Macro110_Entry5_DelayMin, Macro110_Entry5_DelaySec, Macro110_Entry5_TimMin, Macro110_Entry5_TimSec, Macro110_Entry5_Protocol, 0, 0, 0, 0,
		         Macro110_Entry6_DelayMin, Macro110_Entry6_DelaySec, Macro110_Entry6_TimMin, Macro110_Entry6_TimSec, Macro110_Entry6_Protocol, 0, 0, 0, 0,
		         Macro110_Entry7_DelayMin, Macro110_Entry7_DelaySec, Macro110_Entry7_TimMin, Macro110_Entry7_TimSec, Macro110_Entry7_Protocol, 0, 0, 0, 0,
		         Macro110_Entry8_DelayMin, Macro110_Entry8_DelaySec, Macro110_Entry8_TimMin, Macro110_Entry8_TimSec, Macro110_Entry8_Protocol, 0, 0, 0, 0,
		         Macro110_Entry9_DelayMin, Macro110_Entry9_DelaySec, Macro110_Entry9_TimMin, Macro110_Entry9_TimSec, Macro110_Entry9_Protocol, 0, 0, 0, 0,
		         Macro110_Entry10_DelayMin, Macro110_Entry10_DelaySec, Macro110_Entry10_TimMin, Macro110_Entry10_TimSec, Macro110_Entry10_Protocol, 0, 0, 0, 0,
		         Macro110_Entry11_DelayMin, Macro110_Entry11_DelaySec, Macro110_Entry11_TimMin, Macro110_Entry11_TimSec, Macro110_Entry11_Protocol, 0, 0, 0, 0,
		         Macro110_Entry12_DelayMin, Macro110_Entry12_DelaySec, Macro110_Entry12_TimMin, Macro110_Entry12_TimSec, Macro110_Entry12_Protocol, 0, 0, 0, 0,
		         Macro110_Entry13_DelayMin, Macro110_Entry13_DelaySec, Macro110_Entry13_TimMin, Macro110_Entry13_TimSec, Macro110_Entry13_Protocol, 0, 0, 0, 0,
		         Macro110_Entry14_DelayMin, Macro110_Entry14_DelaySec, Macro110_Entry14_TimMin, Macro110_Entry14_TimSec, Macro110_Entry14_Protocol, 0, 0, 0, 0,
		         Macro110_Entry15_DelayMin, Macro110_Entry15_DelaySec, Macro110_Entry15_TimMin, Macro110_Entry15_TimSec, Macro110_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR110_STRING};

const struct super_macro Macro111 = {Macro111_NumEntries,
		         Macro111_Entry1_DelayMin, Macro111_Entry1_DelaySec, Macro111_Entry1_TimMin, Macro111_Entry1_TimSec, Macro111_Entry1_Protocol, 0, 0, 0, 0,
		         Macro111_Entry2_DelayMin, Macro111_Entry2_DelaySec, Macro111_Entry2_TimMin, Macro111_Entry2_TimSec, Macro111_Entry2_Protocol, 0, 0, 0, 0,
		         Macro111_Entry3_DelayMin, Macro111_Entry3_DelaySec, Macro111_Entry3_TimMin, Macro111_Entry3_TimSec, Macro111_Entry3_Protocol, 0, 0, 0, 0,
		         Macro111_Entry4_DelayMin, Macro111_Entry4_DelaySec, Macro111_Entry4_TimMin, Macro111_Entry4_TimSec, Macro111_Entry4_Protocol, 0, 0, 0, 0,
		         Macro111_Entry5_DelayMin, Macro111_Entry5_DelaySec, Macro111_Entry5_TimMin, Macro111_Entry5_TimSec, Macro111_Entry5_Protocol, 0, 0, 0, 0,
		         Macro111_Entry6_DelayMin, Macro111_Entry6_DelaySec, Macro111_Entry6_TimMin, Macro111_Entry6_TimSec, Macro111_Entry6_Protocol, 0, 0, 0, 0,
		         Macro111_Entry7_DelayMin, Macro111_Entry7_DelaySec, Macro111_Entry7_TimMin, Macro111_Entry7_TimSec, Macro111_Entry7_Protocol, 0, 0, 0, 0,
		         Macro111_Entry8_DelayMin, Macro111_Entry8_DelaySec, Macro111_Entry8_TimMin, Macro111_Entry8_TimSec, Macro111_Entry8_Protocol, 0, 0, 0, 0,
		         Macro111_Entry9_DelayMin, Macro111_Entry9_DelaySec, Macro111_Entry9_TimMin, Macro111_Entry9_TimSec, Macro111_Entry9_Protocol, 0, 0, 0, 0,
		         Macro111_Entry10_DelayMin, Macro111_Entry10_DelaySec, Macro111_Entry10_TimMin, Macro111_Entry10_TimSec, Macro111_Entry10_Protocol, 0, 0, 0, 0,
		         Macro111_Entry11_DelayMin, Macro111_Entry11_DelaySec, Macro111_Entry11_TimMin, Macro111_Entry11_TimSec, Macro111_Entry11_Protocol, 0, 0, 0, 0,
		         Macro111_Entry12_DelayMin, Macro111_Entry12_DelaySec, Macro111_Entry12_TimMin, Macro111_Entry12_TimSec, Macro111_Entry12_Protocol, 0, 0, 0, 0,
		         Macro111_Entry13_DelayMin, Macro111_Entry13_DelaySec, Macro111_Entry13_TimMin, Macro111_Entry13_TimSec, Macro111_Entry13_Protocol, 0, 0, 0, 0,
		         Macro111_Entry14_DelayMin, Macro111_Entry14_DelaySec, Macro111_Entry14_TimMin, Macro111_Entry14_TimSec, Macro111_Entry14_Protocol, 0, 0, 0, 0,
		         Macro111_Entry15_DelayMin, Macro111_Entry15_DelaySec, Macro111_Entry15_TimMin, Macro111_Entry15_TimSec, Macro111_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR111_STRING};

const struct super_macro Macro112 = {Macro112_NumEntries,
		         Macro112_Entry1_DelayMin, Macro112_Entry1_DelaySec, Macro112_Entry1_TimMin, Macro112_Entry1_TimSec, Macro112_Entry1_Protocol, 0, 0, 0, 0,
		         Macro112_Entry2_DelayMin, Macro112_Entry2_DelaySec, Macro112_Entry2_TimMin, Macro112_Entry2_TimSec, Macro112_Entry2_Protocol, 0, 0, 0, 0,
		         Macro112_Entry3_DelayMin, Macro112_Entry3_DelaySec, Macro112_Entry3_TimMin, Macro112_Entry3_TimSec, Macro112_Entry3_Protocol, 0, 0, 0, 0,
		         Macro112_Entry4_DelayMin, Macro112_Entry4_DelaySec, Macro112_Entry4_TimMin, Macro112_Entry4_TimSec, Macro112_Entry4_Protocol, 0, 0, 0, 0,
		         Macro112_Entry5_DelayMin, Macro112_Entry5_DelaySec, Macro112_Entry5_TimMin, Macro112_Entry5_TimSec, Macro112_Entry5_Protocol, 0, 0, 0, 0,
		         Macro112_Entry6_DelayMin, Macro112_Entry6_DelaySec, Macro112_Entry6_TimMin, Macro112_Entry6_TimSec, Macro112_Entry6_Protocol, 0, 0, 0, 0,
		         Macro112_Entry7_DelayMin, Macro112_Entry7_DelaySec, Macro112_Entry7_TimMin, Macro112_Entry7_TimSec, Macro112_Entry7_Protocol, 0, 0, 0, 0,
		         Macro112_Entry8_DelayMin, Macro112_Entry8_DelaySec, Macro112_Entry8_TimMin, Macro112_Entry8_TimSec, Macro112_Entry8_Protocol, 0, 0, 0, 0,
		         Macro112_Entry9_DelayMin, Macro112_Entry9_DelaySec, Macro112_Entry9_TimMin, Macro112_Entry9_TimSec, Macro112_Entry9_Protocol, 0, 0, 0, 0,
		         Macro112_Entry10_DelayMin, Macro112_Entry10_DelaySec, Macro112_Entry10_TimMin, Macro112_Entry10_TimSec, Macro112_Entry10_Protocol, 0, 0, 0, 0,
		         Macro112_Entry11_DelayMin, Macro112_Entry11_DelaySec, Macro112_Entry11_TimMin, Macro112_Entry11_TimSec, Macro112_Entry11_Protocol, 0, 0, 0, 0,
		         Macro112_Entry12_DelayMin, Macro112_Entry12_DelaySec, Macro112_Entry12_TimMin, Macro112_Entry12_TimSec, Macro112_Entry12_Protocol, 0, 0, 0, 0,
		         Macro112_Entry13_DelayMin, Macro112_Entry13_DelaySec, Macro112_Entry13_TimMin, Macro112_Entry13_TimSec, Macro112_Entry13_Protocol, 0, 0, 0, 0,
		         Macro112_Entry14_DelayMin, Macro112_Entry14_DelaySec, Macro112_Entry14_TimMin, Macro112_Entry14_TimSec, Macro112_Entry14_Protocol, 0, 0, 0, 0,
		         Macro112_Entry15_DelayMin, Macro112_Entry15_DelaySec, Macro112_Entry15_TimMin, Macro112_Entry15_TimSec, Macro112_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR112_STRING};

const struct super_macro Macro113 = {Macro113_NumEntries,
		         Macro113_Entry1_DelayMin, Macro113_Entry1_DelaySec, Macro113_Entry1_TimMin, Macro113_Entry1_TimSec, Macro113_Entry1_Protocol, 0, 0, 0, 0,
		         Macro113_Entry2_DelayMin, Macro113_Entry2_DelaySec, Macro113_Entry2_TimMin, Macro113_Entry2_TimSec, Macro113_Entry2_Protocol, 0, 0, 0, 0,
		         Macro113_Entry3_DelayMin, Macro113_Entry3_DelaySec, Macro113_Entry3_TimMin, Macro113_Entry3_TimSec, Macro113_Entry3_Protocol, 0, 0, 0, 0,
		         Macro113_Entry4_DelayMin, Macro113_Entry4_DelaySec, Macro113_Entry4_TimMin, Macro113_Entry4_TimSec, Macro113_Entry4_Protocol, 0, 0, 0, 0,
		         Macro113_Entry5_DelayMin, Macro113_Entry5_DelaySec, Macro113_Entry5_TimMin, Macro113_Entry5_TimSec, Macro113_Entry5_Protocol, 0, 0, 0, 0,
		         Macro113_Entry6_DelayMin, Macro113_Entry6_DelaySec, Macro113_Entry6_TimMin, Macro113_Entry6_TimSec, Macro113_Entry6_Protocol, 0, 0, 0, 0,
		         Macro113_Entry7_DelayMin, Macro113_Entry7_DelaySec, Macro113_Entry7_TimMin, Macro113_Entry7_TimSec, Macro113_Entry7_Protocol, 0, 0, 0, 0,
		         Macro113_Entry8_DelayMin, Macro113_Entry8_DelaySec, Macro113_Entry8_TimMin, Macro113_Entry8_TimSec, Macro113_Entry8_Protocol, 0, 0, 0, 0,
		         Macro113_Entry9_DelayMin, Macro113_Entry9_DelaySec, Macro113_Entry9_TimMin, Macro113_Entry9_TimSec, Macro113_Entry9_Protocol, 0, 0, 0, 0,
		         Macro113_Entry10_DelayMin, Macro113_Entry10_DelaySec, Macro113_Entry10_TimMin, Macro113_Entry10_TimSec, Macro113_Entry10_Protocol, 0, 0, 0, 0,
		         Macro113_Entry11_DelayMin, Macro113_Entry11_DelaySec, Macro113_Entry11_TimMin, Macro113_Entry11_TimSec, Macro113_Entry11_Protocol, 0, 0, 0, 0,
		         Macro113_Entry12_DelayMin, Macro113_Entry12_DelaySec, Macro113_Entry12_TimMin, Macro113_Entry12_TimSec, Macro113_Entry12_Protocol, 0, 0, 0, 0,
		         Macro113_Entry13_DelayMin, Macro113_Entry13_DelaySec, Macro113_Entry13_TimMin, Macro113_Entry13_TimSec, Macro113_Entry13_Protocol, 0, 0, 0, 0,
		         Macro113_Entry14_DelayMin, Macro113_Entry14_DelaySec, Macro113_Entry14_TimMin, Macro113_Entry14_TimSec, Macro113_Entry14_Protocol, 0, 0, 0, 0,
		         Macro113_Entry15_DelayMin, Macro113_Entry15_DelaySec, Macro113_Entry15_TimMin, Macro113_Entry15_TimSec, Macro113_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR113_STRING};

const struct super_macro Macro114 = {Macro114_NumEntries,
		         Macro114_Entry1_DelayMin, Macro114_Entry1_DelaySec, Macro114_Entry1_TimMin, Macro114_Entry1_TimSec, Macro114_Entry1_Protocol, 0, 0, 0, 0,
		         Macro114_Entry2_DelayMin, Macro114_Entry2_DelaySec, Macro114_Entry2_TimMin, Macro114_Entry2_TimSec, Macro114_Entry2_Protocol, 0, 0, 0, 0,
		         Macro114_Entry3_DelayMin, Macro114_Entry3_DelaySec, Macro114_Entry3_TimMin, Macro114_Entry3_TimSec, Macro114_Entry3_Protocol, 0, 0, 0, 0,
		         Macro114_Entry4_DelayMin, Macro114_Entry4_DelaySec, Macro114_Entry4_TimMin, Macro114_Entry4_TimSec, Macro114_Entry4_Protocol, 0, 0, 0, 0,
		         Macro114_Entry5_DelayMin, Macro114_Entry5_DelaySec, Macro114_Entry5_TimMin, Macro114_Entry5_TimSec, Macro114_Entry5_Protocol, 0, 0, 0, 0,
		         Macro114_Entry6_DelayMin, Macro114_Entry6_DelaySec, Macro114_Entry6_TimMin, Macro114_Entry6_TimSec, Macro114_Entry6_Protocol, 0, 0, 0, 0,
		         Macro114_Entry7_DelayMin, Macro114_Entry7_DelaySec, Macro114_Entry7_TimMin, Macro114_Entry7_TimSec, Macro114_Entry7_Protocol, 0, 0, 0, 0,
		         Macro114_Entry8_DelayMin, Macro114_Entry8_DelaySec, Macro114_Entry8_TimMin, Macro114_Entry8_TimSec, Macro114_Entry8_Protocol, 0, 0, 0, 0,
		         Macro114_Entry9_DelayMin, Macro114_Entry9_DelaySec, Macro114_Entry9_TimMin, Macro114_Entry9_TimSec, Macro114_Entry9_Protocol, 0, 0, 0, 0,
		         Macro114_Entry10_DelayMin, Macro114_Entry10_DelaySec, Macro114_Entry10_TimMin, Macro114_Entry10_TimSec, Macro114_Entry10_Protocol, 0, 0, 0, 0,
		         Macro114_Entry11_DelayMin, Macro114_Entry11_DelaySec, Macro114_Entry11_TimMin, Macro114_Entry11_TimSec, Macro114_Entry11_Protocol, 0, 0, 0, 0,
		         Macro114_Entry12_DelayMin, Macro114_Entry12_DelaySec, Macro114_Entry12_TimMin, Macro114_Entry12_TimSec, Macro114_Entry12_Protocol, 0, 0, 0, 0,
		         Macro114_Entry13_DelayMin, Macro114_Entry13_DelaySec, Macro114_Entry13_TimMin, Macro114_Entry13_TimSec, Macro114_Entry13_Protocol, 0, 0, 0, 0,
		         Macro114_Entry14_DelayMin, Macro114_Entry14_DelaySec, Macro114_Entry14_TimMin, Macro114_Entry14_TimSec, Macro114_Entry14_Protocol, 0, 0, 0, 0,
		         Macro114_Entry15_DelayMin, Macro114_Entry15_DelaySec, Macro114_Entry15_TimMin, Macro114_Entry15_TimSec, Macro114_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR114_STRING};

const struct super_macro Macro115 = {Macro115_NumEntries,
		         Macro115_Entry1_DelayMin, Macro115_Entry1_DelaySec, Macro115_Entry1_TimMin, Macro115_Entry1_TimSec, Macro115_Entry1_Protocol, 0, 0, 0, 0,
		         Macro115_Entry2_DelayMin, Macro115_Entry2_DelaySec, Macro115_Entry2_TimMin, Macro115_Entry2_TimSec, Macro115_Entry2_Protocol, 0, 0, 0, 0,
		         Macro115_Entry3_DelayMin, Macro115_Entry3_DelaySec, Macro115_Entry3_TimMin, Macro115_Entry3_TimSec, Macro115_Entry3_Protocol, 0, 0, 0, 0,
		         Macro115_Entry4_DelayMin, Macro115_Entry4_DelaySec, Macro115_Entry4_TimMin, Macro115_Entry4_TimSec, Macro115_Entry4_Protocol, 0, 0, 0, 0,
		         Macro115_Entry5_DelayMin, Macro115_Entry5_DelaySec, Macro115_Entry5_TimMin, Macro115_Entry5_TimSec, Macro115_Entry5_Protocol, 0, 0, 0, 0,
		         Macro115_Entry6_DelayMin, Macro115_Entry6_DelaySec, Macro115_Entry6_TimMin, Macro115_Entry6_TimSec, Macro115_Entry6_Protocol, 0, 0, 0, 0,
		         Macro115_Entry7_DelayMin, Macro115_Entry7_DelaySec, Macro115_Entry7_TimMin, Macro115_Entry7_TimSec, Macro115_Entry7_Protocol, 0, 0, 0, 0,
		         Macro115_Entry8_DelayMin, Macro115_Entry8_DelaySec, Macro115_Entry8_TimMin, Macro115_Entry8_TimSec, Macro115_Entry8_Protocol, 0, 0, 0, 0,
		         Macro115_Entry9_DelayMin, Macro115_Entry9_DelaySec, Macro115_Entry9_TimMin, Macro115_Entry9_TimSec, Macro115_Entry9_Protocol, 0, 0, 0, 0,
		         Macro115_Entry10_DelayMin, Macro115_Entry10_DelaySec, Macro115_Entry10_TimMin, Macro115_Entry10_TimSec, Macro115_Entry10_Protocol, 0, 0, 0, 0,
		         Macro115_Entry11_DelayMin, Macro115_Entry11_DelaySec, Macro115_Entry11_TimMin, Macro115_Entry11_TimSec, Macro115_Entry11_Protocol, 0, 0, 0, 0,
		         Macro115_Entry12_DelayMin, Macro115_Entry12_DelaySec, Macro115_Entry12_TimMin, Macro115_Entry12_TimSec, Macro115_Entry12_Protocol, 0, 0, 0, 0,
		         Macro115_Entry13_DelayMin, Macro115_Entry13_DelaySec, Macro115_Entry13_TimMin, Macro115_Entry13_TimSec, Macro115_Entry13_Protocol, 0, 0, 0, 0,
		         Macro115_Entry14_DelayMin, Macro115_Entry14_DelaySec, Macro115_Entry14_TimMin, Macro115_Entry14_TimSec, Macro115_Entry14_Protocol, 0, 0, 0, 0,
		         Macro115_Entry15_DelayMin, Macro115_Entry15_DelaySec, Macro115_Entry15_TimMin, Macro115_Entry15_TimSec, Macro115_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR115_STRING};

const struct super_macro Macro116 = {Macro116_NumEntries,
		         Macro116_Entry1_DelayMin, Macro116_Entry1_DelaySec, Macro116_Entry1_TimMin, Macro116_Entry1_TimSec, Macro116_Entry1_Protocol, 0, 0, 0, 0,
		         Macro116_Entry2_DelayMin, Macro116_Entry2_DelaySec, Macro116_Entry2_TimMin, Macro116_Entry2_TimSec, Macro116_Entry2_Protocol, 0, 0, 0, 0,
		         Macro116_Entry3_DelayMin, Macro116_Entry3_DelaySec, Macro116_Entry3_TimMin, Macro116_Entry3_TimSec, Macro116_Entry3_Protocol, 0, 0, 0, 0,
		         Macro116_Entry4_DelayMin, Macro116_Entry4_DelaySec, Macro116_Entry4_TimMin, Macro116_Entry4_TimSec, Macro116_Entry4_Protocol, 0, 0, 0, 0,
		         Macro116_Entry5_DelayMin, Macro116_Entry5_DelaySec, Macro116_Entry5_TimMin, Macro116_Entry5_TimSec, Macro116_Entry5_Protocol, 0, 0, 0, 0,
		         Macro116_Entry6_DelayMin, Macro116_Entry6_DelaySec, Macro116_Entry6_TimMin, Macro116_Entry6_TimSec, Macro116_Entry6_Protocol, 0, 0, 0, 0,
		         Macro116_Entry7_DelayMin, Macro116_Entry7_DelaySec, Macro116_Entry7_TimMin, Macro116_Entry7_TimSec, Macro116_Entry7_Protocol, 0, 0, 0, 0,
		         Macro116_Entry8_DelayMin, Macro116_Entry8_DelaySec, Macro116_Entry8_TimMin, Macro116_Entry8_TimSec, Macro116_Entry8_Protocol, 0, 0, 0, 0,
		         Macro116_Entry9_DelayMin, Macro116_Entry9_DelaySec, Macro116_Entry9_TimMin, Macro116_Entry9_TimSec, Macro116_Entry9_Protocol, 0, 0, 0, 0,
		         Macro116_Entry10_DelayMin, Macro116_Entry10_DelaySec, Macro116_Entry10_TimMin, Macro116_Entry10_TimSec, Macro116_Entry10_Protocol, 0, 0, 0, 0,
		         Macro116_Entry11_DelayMin, Macro116_Entry11_DelaySec, Macro116_Entry11_TimMin, Macro116_Entry11_TimSec, Macro116_Entry11_Protocol, 0, 0, 0, 0,
		         Macro116_Entry12_DelayMin, Macro116_Entry12_DelaySec, Macro116_Entry12_TimMin, Macro116_Entry12_TimSec, Macro116_Entry12_Protocol, 0, 0, 0, 0,
		         Macro116_Entry13_DelayMin, Macro116_Entry13_DelaySec, Macro116_Entry13_TimMin, Macro116_Entry13_TimSec, Macro116_Entry13_Protocol, 0, 0, 0, 0,
		         Macro116_Entry14_DelayMin, Macro116_Entry14_DelaySec, Macro116_Entry14_TimMin, Macro116_Entry14_TimSec, Macro116_Entry14_Protocol, 0, 0, 0, 0,
		         Macro116_Entry15_DelayMin, Macro116_Entry15_DelaySec, Macro116_Entry15_TimMin, Macro116_Entry15_TimSec, Macro116_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR116_STRING};

const struct super_macro Macro117 = {Macro117_NumEntries,
		         Macro117_Entry1_DelayMin, Macro117_Entry1_DelaySec, Macro117_Entry1_TimMin, Macro117_Entry1_TimSec, Macro117_Entry1_Protocol, 0, 0, 0, 0,
		         Macro117_Entry2_DelayMin, Macro117_Entry2_DelaySec, Macro117_Entry2_TimMin, Macro117_Entry2_TimSec, Macro117_Entry2_Protocol, 0, 0, 0, 0,
		         Macro117_Entry3_DelayMin, Macro117_Entry3_DelaySec, Macro117_Entry3_TimMin, Macro117_Entry3_TimSec, Macro117_Entry3_Protocol, 0, 0, 0, 0,
		         Macro117_Entry4_DelayMin, Macro117_Entry4_DelaySec, Macro117_Entry4_TimMin, Macro117_Entry4_TimSec, Macro117_Entry4_Protocol, 0, 0, 0, 0,
		         Macro117_Entry5_DelayMin, Macro117_Entry5_DelaySec, Macro117_Entry5_TimMin, Macro117_Entry5_TimSec, Macro117_Entry5_Protocol, 0, 0, 0, 0,
		         Macro117_Entry6_DelayMin, Macro117_Entry6_DelaySec, Macro117_Entry6_TimMin, Macro117_Entry6_TimSec, Macro117_Entry6_Protocol, 0, 0, 0, 0,
		         Macro117_Entry7_DelayMin, Macro117_Entry7_DelaySec, Macro117_Entry7_TimMin, Macro117_Entry7_TimSec, Macro117_Entry7_Protocol, 0, 0, 0, 0,
		         Macro117_Entry8_DelayMin, Macro117_Entry8_DelaySec, Macro117_Entry8_TimMin, Macro117_Entry8_TimSec, Macro117_Entry8_Protocol, 0, 0, 0, 0,
		         Macro117_Entry9_DelayMin, Macro117_Entry9_DelaySec, Macro117_Entry9_TimMin, Macro117_Entry9_TimSec, Macro117_Entry9_Protocol, 0, 0, 0, 0,
		         Macro117_Entry10_DelayMin, Macro117_Entry10_DelaySec, Macro117_Entry10_TimMin, Macro117_Entry10_TimSec, Macro117_Entry10_Protocol, 0, 0, 0, 0,
		         Macro117_Entry11_DelayMin, Macro117_Entry11_DelaySec, Macro117_Entry11_TimMin, Macro117_Entry11_TimSec, Macro117_Entry11_Protocol, 0, 0, 0, 0,
		         Macro117_Entry12_DelayMin, Macro117_Entry12_DelaySec, Macro117_Entry12_TimMin, Macro117_Entry12_TimSec, Macro117_Entry12_Protocol, 0, 0, 0, 0,
		         Macro117_Entry13_DelayMin, Macro117_Entry13_DelaySec, Macro117_Entry13_TimMin, Macro117_Entry13_TimSec, Macro117_Entry13_Protocol, 0, 0, 0, 0,
		         Macro117_Entry14_DelayMin, Macro117_Entry14_DelaySec, Macro117_Entry14_TimMin, Macro117_Entry14_TimSec, Macro117_Entry14_Protocol, 0, 0, 0, 0,
		         Macro117_Entry15_DelayMin, Macro117_Entry15_DelaySec, Macro117_Entry15_TimMin, Macro117_Entry15_TimSec, Macro117_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR117_STRING};

const struct super_macro Macro118 = {Macro118_NumEntries,
		         Macro118_Entry1_DelayMin, Macro118_Entry1_DelaySec, Macro118_Entry1_TimMin, Macro118_Entry1_TimSec, Macro118_Entry1_Protocol, 0, 0, 0, 0,
		         Macro118_Entry2_DelayMin, Macro118_Entry2_DelaySec, Macro118_Entry2_TimMin, Macro118_Entry2_TimSec, Macro118_Entry2_Protocol, 0, 0, 0, 0,
		         Macro118_Entry3_DelayMin, Macro118_Entry3_DelaySec, Macro118_Entry3_TimMin, Macro118_Entry3_TimSec, Macro118_Entry3_Protocol, 0, 0, 0, 0,
		         Macro118_Entry4_DelayMin, Macro118_Entry4_DelaySec, Macro118_Entry4_TimMin, Macro118_Entry4_TimSec, Macro118_Entry4_Protocol, 0, 0, 0, 0,
		         Macro118_Entry5_DelayMin, Macro118_Entry5_DelaySec, Macro118_Entry5_TimMin, Macro118_Entry5_TimSec, Macro118_Entry5_Protocol, 0, 0, 0, 0,
		         Macro118_Entry6_DelayMin, Macro118_Entry6_DelaySec, Macro118_Entry6_TimMin, Macro118_Entry6_TimSec, Macro118_Entry6_Protocol, 0, 0, 0, 0,
		         Macro118_Entry7_DelayMin, Macro118_Entry7_DelaySec, Macro118_Entry7_TimMin, Macro118_Entry7_TimSec, Macro118_Entry7_Protocol, 0, 0, 0, 0,
		         Macro118_Entry8_DelayMin, Macro118_Entry8_DelaySec, Macro118_Entry8_TimMin, Macro118_Entry8_TimSec, Macro118_Entry8_Protocol, 0, 0, 0, 0,
		         Macro118_Entry9_DelayMin, Macro118_Entry9_DelaySec, Macro118_Entry9_TimMin, Macro118_Entry9_TimSec, Macro118_Entry9_Protocol, 0, 0, 0, 0,
		         Macro118_Entry10_DelayMin, Macro118_Entry10_DelaySec, Macro118_Entry10_TimMin, Macro118_Entry10_TimSec, Macro118_Entry10_Protocol, 0, 0, 0, 0,
		         Macro118_Entry11_DelayMin, Macro118_Entry11_DelaySec, Macro118_Entry11_TimMin, Macro118_Entry11_TimSec, Macro118_Entry11_Protocol, 0, 0, 0, 0,
		         Macro118_Entry12_DelayMin, Macro118_Entry12_DelaySec, Macro118_Entry12_TimMin, Macro118_Entry12_TimSec, Macro118_Entry12_Protocol, 0, 0, 0, 0,
		         Macro118_Entry13_DelayMin, Macro118_Entry13_DelaySec, Macro118_Entry13_TimMin, Macro118_Entry13_TimSec, Macro118_Entry13_Protocol, 0, 0, 0, 0,
		         Macro118_Entry14_DelayMin, Macro118_Entry14_DelaySec, Macro118_Entry14_TimMin, Macro118_Entry14_TimSec, Macro118_Entry14_Protocol, 0, 0, 0, 0,
		         Macro118_Entry15_DelayMin, Macro118_Entry15_DelaySec, Macro118_Entry15_TimMin, Macro118_Entry15_TimSec, Macro118_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR118_STRING};

const struct super_macro Macro119 = {Macro119_NumEntries,
		         Macro119_Entry1_DelayMin, Macro119_Entry1_DelaySec, Macro119_Entry1_TimMin, Macro119_Entry1_TimSec, Macro119_Entry1_Protocol, 0, 0, 0, 0,
		         Macro119_Entry2_DelayMin, Macro119_Entry2_DelaySec, Macro119_Entry2_TimMin, Macro119_Entry2_TimSec, Macro119_Entry2_Protocol, 0, 0, 0, 0,
		         Macro119_Entry3_DelayMin, Macro119_Entry3_DelaySec, Macro119_Entry3_TimMin, Macro119_Entry3_TimSec, Macro119_Entry3_Protocol, 0, 0, 0, 0,
		         Macro119_Entry4_DelayMin, Macro119_Entry4_DelaySec, Macro119_Entry4_TimMin, Macro119_Entry4_TimSec, Macro119_Entry4_Protocol, 0, 0, 0, 0,
		         Macro119_Entry5_DelayMin, Macro119_Entry5_DelaySec, Macro119_Entry5_TimMin, Macro119_Entry5_TimSec, Macro119_Entry5_Protocol, 0, 0, 0, 0,
		         Macro119_Entry6_DelayMin, Macro119_Entry6_DelaySec, Macro119_Entry6_TimMin, Macro119_Entry6_TimSec, Macro119_Entry6_Protocol, 0, 0, 0, 0,
		         Macro119_Entry7_DelayMin, Macro119_Entry7_DelaySec, Macro119_Entry7_TimMin, Macro119_Entry7_TimSec, Macro119_Entry7_Protocol, 0, 0, 0, 0,
		         Macro119_Entry8_DelayMin, Macro119_Entry8_DelaySec, Macro119_Entry8_TimMin, Macro119_Entry8_TimSec, Macro119_Entry8_Protocol, 0, 0, 0, 0,
		         Macro119_Entry9_DelayMin, Macro119_Entry9_DelaySec, Macro119_Entry9_TimMin, Macro119_Entry9_TimSec, Macro119_Entry9_Protocol, 0, 0, 0, 0,
		         Macro119_Entry10_DelayMin, Macro119_Entry10_DelaySec, Macro119_Entry10_TimMin, Macro119_Entry10_TimSec, Macro119_Entry10_Protocol, 0, 0, 0, 0,
		         Macro119_Entry11_DelayMin, Macro119_Entry11_DelaySec, Macro119_Entry11_TimMin, Macro119_Entry11_TimSec, Macro119_Entry11_Protocol, 0, 0, 0, 0,
		         Macro119_Entry12_DelayMin, Macro119_Entry12_DelaySec, Macro119_Entry12_TimMin, Macro119_Entry12_TimSec, Macro119_Entry12_Protocol, 0, 0, 0, 0,
		         Macro119_Entry13_DelayMin, Macro119_Entry13_DelaySec, Macro119_Entry13_TimMin, Macro119_Entry13_TimSec, Macro119_Entry13_Protocol, 0, 0, 0, 0,
		         Macro119_Entry14_DelayMin, Macro119_Entry14_DelaySec, Macro119_Entry14_TimMin, Macro119_Entry14_TimSec, Macro119_Entry14_Protocol, 0, 0, 0, 0,
		         Macro119_Entry15_DelayMin, Macro119_Entry15_DelaySec, Macro119_Entry15_TimMin, Macro119_Entry15_TimSec, Macro119_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR119_STRING};

const struct super_macro Macro120 = {Macro120_NumEntries,
		         Macro120_Entry1_DelayMin, Macro120_Entry1_DelaySec, Macro120_Entry1_TimMin, Macro120_Entry1_TimSec, Macro120_Entry1_Protocol, 0, 0, 0, 0,
		         Macro120_Entry2_DelayMin, Macro120_Entry2_DelaySec, Macro120_Entry2_TimMin, Macro120_Entry2_TimSec, Macro120_Entry2_Protocol, 0, 0, 0, 0,
		         Macro120_Entry3_DelayMin, Macro120_Entry3_DelaySec, Macro120_Entry3_TimMin, Macro120_Entry3_TimSec, Macro120_Entry3_Protocol, 0, 0, 0, 0,
		         Macro120_Entry4_DelayMin, Macro120_Entry4_DelaySec, Macro120_Entry4_TimMin, Macro120_Entry4_TimSec, Macro120_Entry4_Protocol, 0, 0, 0, 0,
		         Macro120_Entry5_DelayMin, Macro120_Entry5_DelaySec, Macro120_Entry5_TimMin, Macro120_Entry5_TimSec, Macro120_Entry5_Protocol, 0, 0, 0, 0,
		         Macro120_Entry6_DelayMin, Macro120_Entry6_DelaySec, Macro120_Entry6_TimMin, Macro120_Entry6_TimSec, Macro120_Entry6_Protocol, 0, 0, 0, 0,
		         Macro120_Entry7_DelayMin, Macro120_Entry7_DelaySec, Macro120_Entry7_TimMin, Macro120_Entry7_TimSec, Macro120_Entry7_Protocol, 0, 0, 0, 0,
		         Macro120_Entry8_DelayMin, Macro120_Entry8_DelaySec, Macro120_Entry8_TimMin, Macro120_Entry8_TimSec, Macro120_Entry8_Protocol, 0, 0, 0, 0,
		         Macro120_Entry9_DelayMin, Macro120_Entry9_DelaySec, Macro120_Entry9_TimMin, Macro120_Entry9_TimSec, Macro120_Entry9_Protocol, 0, 0, 0, 0,
		         Macro120_Entry10_DelayMin, Macro120_Entry10_DelaySec, Macro120_Entry10_TimMin, Macro120_Entry10_TimSec, Macro120_Entry10_Protocol, 0, 0, 0, 0,
		         Macro120_Entry11_DelayMin, Macro120_Entry11_DelaySec, Macro120_Entry11_TimMin, Macro120_Entry11_TimSec, Macro120_Entry11_Protocol, 0, 0, 0, 0,
		         Macro120_Entry12_DelayMin, Macro120_Entry12_DelaySec, Macro120_Entry12_TimMin, Macro120_Entry12_TimSec, Macro120_Entry12_Protocol, 0, 0, 0, 0,
		         Macro120_Entry13_DelayMin, Macro120_Entry13_DelaySec, Macro120_Entry13_TimMin, Macro120_Entry13_TimSec, Macro120_Entry13_Protocol, 0, 0, 0, 0,
		         Macro120_Entry14_DelayMin, Macro120_Entry14_DelaySec, Macro120_Entry14_TimMin, Macro120_Entry14_TimSec, Macro120_Entry14_Protocol, 0, 0, 0, 0,
		         Macro120_Entry15_DelayMin, Macro120_Entry15_DelaySec, Macro120_Entry15_TimMin, Macro120_Entry15_TimSec, Macro120_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR120_STRING};

const struct super_macro Macro121 = {Macro121_NumEntries,
		         Macro121_Entry1_DelayMin, Macro121_Entry1_DelaySec, Macro121_Entry1_TimMin, Macro121_Entry1_TimSec, Macro121_Entry1_Protocol, 0, 0, 0, 0,
		         Macro121_Entry2_DelayMin, Macro121_Entry2_DelaySec, Macro121_Entry2_TimMin, Macro121_Entry2_TimSec, Macro121_Entry2_Protocol, 0, 0, 0, 0,
		         Macro121_Entry3_DelayMin, Macro121_Entry3_DelaySec, Macro121_Entry3_TimMin, Macro121_Entry3_TimSec, Macro121_Entry3_Protocol, 0, 0, 0, 0,
		         Macro121_Entry4_DelayMin, Macro121_Entry4_DelaySec, Macro121_Entry4_TimMin, Macro121_Entry4_TimSec, Macro121_Entry4_Protocol, 0, 0, 0, 0,
		         Macro121_Entry5_DelayMin, Macro121_Entry5_DelaySec, Macro121_Entry5_TimMin, Macro121_Entry5_TimSec, Macro121_Entry5_Protocol, 0, 0, 0, 0,
		         Macro121_Entry6_DelayMin, Macro121_Entry6_DelaySec, Macro121_Entry6_TimMin, Macro121_Entry6_TimSec, Macro121_Entry6_Protocol, 0, 0, 0, 0,
		         Macro121_Entry7_DelayMin, Macro121_Entry7_DelaySec, Macro121_Entry7_TimMin, Macro121_Entry7_TimSec, Macro121_Entry7_Protocol, 0, 0, 0, 0,
		         Macro121_Entry8_DelayMin, Macro121_Entry8_DelaySec, Macro121_Entry8_TimMin, Macro121_Entry8_TimSec, Macro121_Entry8_Protocol, 0, 0, 0, 0,
		         Macro121_Entry9_DelayMin, Macro121_Entry9_DelaySec, Macro121_Entry9_TimMin, Macro121_Entry9_TimSec, Macro121_Entry9_Protocol, 0, 0, 0, 0,
		         Macro121_Entry10_DelayMin, Macro121_Entry10_DelaySec, Macro121_Entry10_TimMin, Macro121_Entry10_TimSec, Macro121_Entry10_Protocol, 0, 0, 0, 0,
		         Macro121_Entry11_DelayMin, Macro121_Entry11_DelaySec, Macro121_Entry11_TimMin, Macro121_Entry11_TimSec, Macro121_Entry11_Protocol, 0, 0, 0, 0,
		         Macro121_Entry12_DelayMin, Macro121_Entry12_DelaySec, Macro121_Entry12_TimMin, Macro121_Entry12_TimSec, Macro121_Entry12_Protocol, 0, 0, 0, 0,
		         Macro121_Entry13_DelayMin, Macro121_Entry13_DelaySec, Macro121_Entry13_TimMin, Macro121_Entry13_TimSec, Macro121_Entry13_Protocol, 0, 0, 0, 0,
		         Macro121_Entry14_DelayMin, Macro121_Entry14_DelaySec, Macro121_Entry14_TimMin, Macro121_Entry14_TimSec, Macro121_Entry14_Protocol, 0, 0, 0, 0,
		         Macro121_Entry15_DelayMin, Macro121_Entry15_DelaySec, Macro121_Entry15_TimMin, Macro121_Entry15_TimSec, Macro121_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR121_STRING};

const struct super_macro Macro122 = {Macro122_NumEntries,
		         Macro122_Entry1_DelayMin, Macro122_Entry1_DelaySec, Macro122_Entry1_TimMin, Macro122_Entry1_TimSec, Macro122_Entry1_Protocol, 0, 0, 0, 0,
		         Macro122_Entry2_DelayMin, Macro122_Entry2_DelaySec, Macro122_Entry2_TimMin, Macro122_Entry2_TimSec, Macro122_Entry2_Protocol, 0, 0, 0, 0,
		         Macro122_Entry3_DelayMin, Macro122_Entry3_DelaySec, Macro122_Entry3_TimMin, Macro122_Entry3_TimSec, Macro122_Entry3_Protocol, 0, 0, 0, 0,
		         Macro122_Entry4_DelayMin, Macro122_Entry4_DelaySec, Macro122_Entry4_TimMin, Macro122_Entry4_TimSec, Macro122_Entry4_Protocol, 0, 0, 0, 0,
		         Macro122_Entry5_DelayMin, Macro122_Entry5_DelaySec, Macro122_Entry5_TimMin, Macro122_Entry5_TimSec, Macro122_Entry5_Protocol, 0, 0, 0, 0,
		         Macro122_Entry6_DelayMin, Macro122_Entry6_DelaySec, Macro122_Entry6_TimMin, Macro122_Entry6_TimSec, Macro122_Entry6_Protocol, 0, 0, 0, 0,
		         Macro122_Entry7_DelayMin, Macro122_Entry7_DelaySec, Macro122_Entry7_TimMin, Macro122_Entry7_TimSec, Macro122_Entry7_Protocol, 0, 0, 0, 0,
		         Macro122_Entry8_DelayMin, Macro122_Entry8_DelaySec, Macro122_Entry8_TimMin, Macro122_Entry8_TimSec, Macro122_Entry8_Protocol, 0, 0, 0, 0,
		         Macro122_Entry9_DelayMin, Macro122_Entry9_DelaySec, Macro122_Entry9_TimMin, Macro122_Entry9_TimSec, Macro122_Entry9_Protocol, 0, 0, 0, 0,
		         Macro122_Entry10_DelayMin, Macro122_Entry10_DelaySec, Macro122_Entry10_TimMin, Macro122_Entry10_TimSec, Macro122_Entry10_Protocol, 0, 0, 0, 0,
		         Macro122_Entry11_DelayMin, Macro122_Entry11_DelaySec, Macro122_Entry11_TimMin, Macro122_Entry11_TimSec, Macro122_Entry11_Protocol, 0, 0, 0, 0,
		         Macro122_Entry12_DelayMin, Macro122_Entry12_DelaySec, Macro122_Entry12_TimMin, Macro122_Entry12_TimSec, Macro122_Entry12_Protocol, 0, 0, 0, 0,
		         Macro122_Entry13_DelayMin, Macro122_Entry13_DelaySec, Macro122_Entry13_TimMin, Macro122_Entry13_TimSec, Macro122_Entry13_Protocol, 0, 0, 0, 0,
		         Macro122_Entry14_DelayMin, Macro122_Entry14_DelaySec, Macro122_Entry14_TimMin, Macro122_Entry14_TimSec, Macro122_Entry14_Protocol, 0, 0, 0, 0,
		         Macro122_Entry15_DelayMin, Macro122_Entry15_DelaySec, Macro122_Entry15_TimMin, Macro122_Entry15_TimSec, Macro122_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR122_STRING};

const struct super_macro Macro123 = {Macro123_NumEntries,
		         Macro123_Entry1_DelayMin, Macro123_Entry1_DelaySec, Macro123_Entry1_TimMin, Macro123_Entry1_TimSec, Macro123_Entry1_Protocol, 0, 0, 0, 0,
		         Macro123_Entry2_DelayMin, Macro123_Entry2_DelaySec, Macro123_Entry2_TimMin, Macro123_Entry2_TimSec, Macro123_Entry2_Protocol, 0, 0, 0, 0,
		         Macro123_Entry3_DelayMin, Macro123_Entry3_DelaySec, Macro123_Entry3_TimMin, Macro123_Entry3_TimSec, Macro123_Entry3_Protocol, 0, 0, 0, 0,
		         Macro123_Entry4_DelayMin, Macro123_Entry4_DelaySec, Macro123_Entry4_TimMin, Macro123_Entry4_TimSec, Macro123_Entry4_Protocol, 0, 0, 0, 0,
		         Macro123_Entry5_DelayMin, Macro123_Entry5_DelaySec, Macro123_Entry5_TimMin, Macro123_Entry5_TimSec, Macro123_Entry5_Protocol, 0, 0, 0, 0,
		         Macro123_Entry6_DelayMin, Macro123_Entry6_DelaySec, Macro123_Entry6_TimMin, Macro123_Entry6_TimSec, Macro123_Entry6_Protocol, 0, 0, 0, 0,
		         Macro123_Entry7_DelayMin, Macro123_Entry7_DelaySec, Macro123_Entry7_TimMin, Macro123_Entry7_TimSec, Macro123_Entry7_Protocol, 0, 0, 0, 0,
		         Macro123_Entry8_DelayMin, Macro123_Entry8_DelaySec, Macro123_Entry8_TimMin, Macro123_Entry8_TimSec, Macro123_Entry8_Protocol, 0, 0, 0, 0,
		         Macro123_Entry9_DelayMin, Macro123_Entry9_DelaySec, Macro123_Entry9_TimMin, Macro123_Entry9_TimSec, Macro123_Entry9_Protocol, 0, 0, 0, 0,
		         Macro123_Entry10_DelayMin, Macro123_Entry10_DelaySec, Macro123_Entry10_TimMin, Macro123_Entry10_TimSec, Macro123_Entry10_Protocol, 0, 0, 0, 0,
		         Macro123_Entry11_DelayMin, Macro123_Entry11_DelaySec, Macro123_Entry11_TimMin, Macro123_Entry11_TimSec, Macro123_Entry11_Protocol, 0, 0, 0, 0,
		         Macro123_Entry12_DelayMin, Macro123_Entry12_DelaySec, Macro123_Entry12_TimMin, Macro123_Entry12_TimSec, Macro123_Entry12_Protocol, 0, 0, 0, 0,
		         Macro123_Entry13_DelayMin, Macro123_Entry13_DelaySec, Macro123_Entry13_TimMin, Macro123_Entry13_TimSec, Macro123_Entry13_Protocol, 0, 0, 0, 0,
		         Macro123_Entry14_DelayMin, Macro123_Entry14_DelaySec, Macro123_Entry14_TimMin, Macro123_Entry14_TimSec, Macro123_Entry14_Protocol, 0, 0, 0, 0,
		         Macro123_Entry15_DelayMin, Macro123_Entry15_DelaySec, Macro123_Entry15_TimMin, Macro123_Entry15_TimSec, Macro123_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR123_STRING};

const struct super_macro Macro124 = {Macro124_NumEntries,
		         Macro124_Entry1_DelayMin, Macro124_Entry1_DelaySec, Macro124_Entry1_TimMin, Macro124_Entry1_TimSec, Macro124_Entry1_Protocol, 0, 0, 0, 0,
		         Macro124_Entry2_DelayMin, Macro124_Entry2_DelaySec, Macro124_Entry2_TimMin, Macro124_Entry2_TimSec, Macro124_Entry2_Protocol, 0, 0, 0, 0,
		         Macro124_Entry3_DelayMin, Macro124_Entry3_DelaySec, Macro124_Entry3_TimMin, Macro124_Entry3_TimSec, Macro124_Entry3_Protocol, 0, 0, 0, 0,
		         Macro124_Entry4_DelayMin, Macro124_Entry4_DelaySec, Macro124_Entry4_TimMin, Macro124_Entry4_TimSec, Macro124_Entry4_Protocol, 0, 0, 0, 0,
		         Macro124_Entry5_DelayMin, Macro124_Entry5_DelaySec, Macro124_Entry5_TimMin, Macro124_Entry5_TimSec, Macro124_Entry5_Protocol, 0, 0, 0, 0,
		         Macro124_Entry6_DelayMin, Macro124_Entry6_DelaySec, Macro124_Entry6_TimMin, Macro124_Entry6_TimSec, Macro124_Entry6_Protocol, 0, 0, 0, 0,
		         Macro124_Entry7_DelayMin, Macro124_Entry7_DelaySec, Macro124_Entry7_TimMin, Macro124_Entry7_TimSec, Macro124_Entry7_Protocol, 0, 0, 0, 0,
		         Macro124_Entry8_DelayMin, Macro124_Entry8_DelaySec, Macro124_Entry8_TimMin, Macro124_Entry8_TimSec, Macro124_Entry8_Protocol, 0, 0, 0, 0,
		         Macro124_Entry9_DelayMin, Macro124_Entry9_DelaySec, Macro124_Entry9_TimMin, Macro124_Entry9_TimSec, Macro124_Entry9_Protocol, 0, 0, 0, 0,
		         Macro124_Entry10_DelayMin, Macro124_Entry10_DelaySec, Macro124_Entry10_TimMin, Macro124_Entry10_TimSec, Macro124_Entry10_Protocol, 0, 0, 0, 0,
		         Macro124_Entry11_DelayMin, Macro124_Entry11_DelaySec, Macro124_Entry11_TimMin, Macro124_Entry11_TimSec, Macro124_Entry11_Protocol, 0, 0, 0, 0,
		         Macro124_Entry12_DelayMin, Macro124_Entry12_DelaySec, Macro124_Entry12_TimMin, Macro124_Entry12_TimSec, Macro124_Entry12_Protocol, 0, 0, 0, 0,
		         Macro124_Entry13_DelayMin, Macro124_Entry13_DelaySec, Macro124_Entry13_TimMin, Macro124_Entry13_TimSec, Macro124_Entry13_Protocol, 0, 0, 0, 0,
		         Macro124_Entry14_DelayMin, Macro124_Entry14_DelaySec, Macro124_Entry14_TimMin, Macro124_Entry14_TimSec, Macro124_Entry14_Protocol, 0, 0, 0, 0,
		         Macro124_Entry15_DelayMin, Macro124_Entry15_DelaySec, Macro124_Entry15_TimMin, Macro124_Entry15_TimSec, Macro124_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR124_STRING};

const struct super_macro Macro125 = {Macro125_NumEntries,
		         Macro125_Entry1_DelayMin, Macro125_Entry1_DelaySec, Macro125_Entry1_TimMin, Macro125_Entry1_TimSec, Macro125_Entry1_Protocol, 0, 0, 0, 0,
		         Macro125_Entry2_DelayMin, Macro125_Entry2_DelaySec, Macro125_Entry2_TimMin, Macro125_Entry2_TimSec, Macro125_Entry2_Protocol, 0, 0, 0, 0,
		         Macro125_Entry3_DelayMin, Macro125_Entry3_DelaySec, Macro125_Entry3_TimMin, Macro125_Entry3_TimSec, Macro125_Entry3_Protocol, 0, 0, 0, 0,
		         Macro125_Entry4_DelayMin, Macro125_Entry4_DelaySec, Macro125_Entry4_TimMin, Macro125_Entry4_TimSec, Macro125_Entry4_Protocol, 0, 0, 0, 0,
		         Macro125_Entry5_DelayMin, Macro125_Entry5_DelaySec, Macro125_Entry5_TimMin, Macro125_Entry5_TimSec, Macro125_Entry5_Protocol, 0, 0, 0, 0,
		         Macro125_Entry6_DelayMin, Macro125_Entry6_DelaySec, Macro125_Entry6_TimMin, Macro125_Entry6_TimSec, Macro125_Entry6_Protocol, 0, 0, 0, 0,
		         Macro125_Entry7_DelayMin, Macro125_Entry7_DelaySec, Macro125_Entry7_TimMin, Macro125_Entry7_TimSec, Macro125_Entry7_Protocol, 0, 0, 0, 0,
		         Macro125_Entry8_DelayMin, Macro125_Entry8_DelaySec, Macro125_Entry8_TimMin, Macro125_Entry8_TimSec, Macro125_Entry8_Protocol, 0, 0, 0, 0,
		         Macro125_Entry9_DelayMin, Macro125_Entry9_DelaySec, Macro125_Entry9_TimMin, Macro125_Entry9_TimSec, Macro125_Entry9_Protocol, 0, 0, 0, 0,
		         Macro125_Entry10_DelayMin, Macro125_Entry10_DelaySec, Macro125_Entry10_TimMin, Macro125_Entry10_TimSec, Macro125_Entry10_Protocol, 0, 0, 0, 0,
		         Macro125_Entry11_DelayMin, Macro125_Entry11_DelaySec, Macro125_Entry11_TimMin, Macro125_Entry11_TimSec, Macro125_Entry11_Protocol, 0, 0, 0, 0,
		         Macro125_Entry12_DelayMin, Macro125_Entry12_DelaySec, Macro125_Entry12_TimMin, Macro125_Entry12_TimSec, Macro125_Entry12_Protocol, 0, 0, 0, 0,
		         Macro125_Entry13_DelayMin, Macro125_Entry13_DelaySec, Macro125_Entry13_TimMin, Macro125_Entry13_TimSec, Macro125_Entry13_Protocol, 0, 0, 0, 0,
		         Macro125_Entry14_DelayMin, Macro125_Entry14_DelaySec, Macro125_Entry14_TimMin, Macro125_Entry14_TimSec, Macro125_Entry14_Protocol, 0, 0, 0, 0,
		         Macro125_Entry15_DelayMin, Macro125_Entry15_DelaySec, Macro125_Entry15_TimMin, Macro125_Entry15_TimSec, Macro125_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR125_STRING};

const struct super_macro Macro126 = {Macro126_NumEntries,
		         Macro126_Entry1_DelayMin, Macro126_Entry1_DelaySec, Macro126_Entry1_TimMin, Macro126_Entry1_TimSec, Macro126_Entry1_Protocol, 0, 0, 0, 0,
		         Macro126_Entry2_DelayMin, Macro126_Entry2_DelaySec, Macro126_Entry2_TimMin, Macro126_Entry2_TimSec, Macro126_Entry2_Protocol, 0, 0, 0, 0,
		         Macro126_Entry3_DelayMin, Macro126_Entry3_DelaySec, Macro126_Entry3_TimMin, Macro126_Entry3_TimSec, Macro126_Entry3_Protocol, 0, 0, 0, 0,
		         Macro126_Entry4_DelayMin, Macro126_Entry4_DelaySec, Macro126_Entry4_TimMin, Macro126_Entry4_TimSec, Macro126_Entry4_Protocol, 0, 0, 0, 0,
		         Macro126_Entry5_DelayMin, Macro126_Entry5_DelaySec, Macro126_Entry5_TimMin, Macro126_Entry5_TimSec, Macro126_Entry5_Protocol, 0, 0, 0, 0,
		         Macro126_Entry6_DelayMin, Macro126_Entry6_DelaySec, Macro126_Entry6_TimMin, Macro126_Entry6_TimSec, Macro126_Entry6_Protocol, 0, 0, 0, 0,
		         Macro126_Entry7_DelayMin, Macro126_Entry7_DelaySec, Macro126_Entry7_TimMin, Macro126_Entry7_TimSec, Macro126_Entry7_Protocol, 0, 0, 0, 0,
		         Macro126_Entry8_DelayMin, Macro126_Entry8_DelaySec, Macro126_Entry8_TimMin, Macro126_Entry8_TimSec, Macro126_Entry8_Protocol, 0, 0, 0, 0,
		         Macro126_Entry9_DelayMin, Macro126_Entry9_DelaySec, Macro126_Entry9_TimMin, Macro126_Entry9_TimSec, Macro126_Entry9_Protocol, 0, 0, 0, 0,
		         Macro126_Entry10_DelayMin, Macro126_Entry10_DelaySec, Macro126_Entry10_TimMin, Macro126_Entry10_TimSec, Macro126_Entry10_Protocol, 0, 0, 0, 0,
		         Macro126_Entry11_DelayMin, Macro126_Entry11_DelaySec, Macro126_Entry11_TimMin, Macro126_Entry11_TimSec, Macro126_Entry11_Protocol, 0, 0, 0, 0,
		         Macro126_Entry12_DelayMin, Macro126_Entry12_DelaySec, Macro126_Entry12_TimMin, Macro126_Entry12_TimSec, Macro126_Entry12_Protocol, 0, 0, 0, 0,
		         Macro126_Entry13_DelayMin, Macro126_Entry13_DelaySec, Macro126_Entry13_TimMin, Macro126_Entry13_TimSec, Macro126_Entry13_Protocol, 0, 0, 0, 0,
		         Macro126_Entry14_DelayMin, Macro126_Entry14_DelaySec, Macro126_Entry14_TimMin, Macro126_Entry14_TimSec, Macro126_Entry14_Protocol, 0, 0, 0, 0,
		         Macro126_Entry15_DelayMin, Macro126_Entry15_DelaySec, Macro126_Entry15_TimMin, Macro126_Entry15_TimSec, Macro126_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR126_STRING};

const struct super_macro Macro127 = {Macro127_NumEntries,
		         Macro127_Entry1_DelayMin, Macro127_Entry1_DelaySec, Macro127_Entry1_TimMin, Macro127_Entry1_TimSec, Macro127_Entry1_Protocol, 0, 0, 0, 0,
		         Macro127_Entry2_DelayMin, Macro127_Entry2_DelaySec, Macro127_Entry2_TimMin, Macro127_Entry2_TimSec, Macro127_Entry2_Protocol, 0, 0, 0, 0,
		         Macro127_Entry3_DelayMin, Macro127_Entry3_DelaySec, Macro127_Entry3_TimMin, Macro127_Entry3_TimSec, Macro127_Entry3_Protocol, 0, 0, 0, 0,
		         Macro127_Entry4_DelayMin, Macro127_Entry4_DelaySec, Macro127_Entry4_TimMin, Macro127_Entry4_TimSec, Macro127_Entry4_Protocol, 0, 0, 0, 0,
		         Macro127_Entry5_DelayMin, Macro127_Entry5_DelaySec, Macro127_Entry5_TimMin, Macro127_Entry5_TimSec, Macro127_Entry5_Protocol, 0, 0, 0, 0,
		         Macro127_Entry6_DelayMin, Macro127_Entry6_DelaySec, Macro127_Entry6_TimMin, Macro127_Entry6_TimSec, Macro127_Entry6_Protocol, 0, 0, 0, 0,
		         Macro127_Entry7_DelayMin, Macro127_Entry7_DelaySec, Macro127_Entry7_TimMin, Macro127_Entry7_TimSec, Macro127_Entry7_Protocol, 0, 0, 0, 0,
		         Macro127_Entry8_DelayMin, Macro127_Entry8_DelaySec, Macro127_Entry8_TimMin, Macro127_Entry8_TimSec, Macro127_Entry8_Protocol, 0, 0, 0, 0,
		         Macro127_Entry9_DelayMin, Macro127_Entry9_DelaySec, Macro127_Entry9_TimMin, Macro127_Entry9_TimSec, Macro127_Entry9_Protocol, 0, 0, 0, 0,
		         Macro127_Entry10_DelayMin, Macro127_Entry10_DelaySec, Macro127_Entry10_TimMin, Macro127_Entry10_TimSec, Macro127_Entry10_Protocol, 0, 0, 0, 0,
		         Macro127_Entry11_DelayMin, Macro127_Entry11_DelaySec, Macro127_Entry11_TimMin, Macro127_Entry11_TimSec, Macro127_Entry11_Protocol, 0, 0, 0, 0,
		         Macro127_Entry12_DelayMin, Macro127_Entry12_DelaySec, Macro127_Entry12_TimMin, Macro127_Entry12_TimSec, Macro127_Entry12_Protocol, 0, 0, 0, 0,
		         Macro127_Entry13_DelayMin, Macro127_Entry13_DelaySec, Macro127_Entry13_TimMin, Macro127_Entry13_TimSec, Macro127_Entry13_Protocol, 0, 0, 0, 0,
		         Macro127_Entry14_DelayMin, Macro127_Entry14_DelaySec, Macro127_Entry14_TimMin, Macro127_Entry14_TimSec, Macro127_Entry14_Protocol, 0, 0, 0, 0,
		         Macro127_Entry15_DelayMin, Macro127_Entry15_DelaySec, Macro127_Entry15_TimMin, Macro127_Entry15_TimSec, Macro127_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR127_STRING};

const struct super_macro Macro128 = {Macro128_NumEntries,
		         Macro128_Entry1_DelayMin, Macro128_Entry1_DelaySec, Macro128_Entry1_TimMin, Macro128_Entry1_TimSec, Macro128_Entry1_Protocol, 0, 0, 0, 0,
		         Macro128_Entry2_DelayMin, Macro128_Entry2_DelaySec, Macro128_Entry2_TimMin, Macro128_Entry2_TimSec, Macro128_Entry2_Protocol, 0, 0, 0, 0,
		         Macro128_Entry3_DelayMin, Macro128_Entry3_DelaySec, Macro128_Entry3_TimMin, Macro128_Entry3_TimSec, Macro128_Entry3_Protocol, 0, 0, 0, 0,
		         Macro128_Entry4_DelayMin, Macro128_Entry4_DelaySec, Macro128_Entry4_TimMin, Macro128_Entry4_TimSec, Macro128_Entry4_Protocol, 0, 0, 0, 0,
		         Macro128_Entry5_DelayMin, Macro128_Entry5_DelaySec, Macro128_Entry5_TimMin, Macro128_Entry5_TimSec, Macro128_Entry5_Protocol, 0, 0, 0, 0,
		         Macro128_Entry6_DelayMin, Macro128_Entry6_DelaySec, Macro128_Entry6_TimMin, Macro128_Entry6_TimSec, Macro128_Entry6_Protocol, 0, 0, 0, 0,
		         Macro128_Entry7_DelayMin, Macro128_Entry7_DelaySec, Macro128_Entry7_TimMin, Macro128_Entry7_TimSec, Macro128_Entry7_Protocol, 0, 0, 0, 0,
		         Macro128_Entry8_DelayMin, Macro128_Entry8_DelaySec, Macro128_Entry8_TimMin, Macro128_Entry8_TimSec, Macro128_Entry8_Protocol, 0, 0, 0, 0,
		         Macro128_Entry9_DelayMin, Macro128_Entry9_DelaySec, Macro128_Entry9_TimMin, Macro128_Entry9_TimSec, Macro128_Entry9_Protocol, 0, 0, 0, 0,
		         Macro128_Entry10_DelayMin, Macro128_Entry10_DelaySec, Macro128_Entry10_TimMin, Macro128_Entry10_TimSec, Macro128_Entry10_Protocol, 0, 0, 0, 0,
		         Macro128_Entry11_DelayMin, Macro128_Entry11_DelaySec, Macro128_Entry11_TimMin, Macro128_Entry11_TimSec, Macro128_Entry11_Protocol, 0, 0, 0, 0,
		         Macro128_Entry12_DelayMin, Macro128_Entry12_DelaySec, Macro128_Entry12_TimMin, Macro128_Entry12_TimSec, Macro128_Entry12_Protocol, 0, 0, 0, 0,
		         Macro128_Entry13_DelayMin, Macro128_Entry13_DelaySec, Macro128_Entry13_TimMin, Macro128_Entry13_TimSec, Macro128_Entry13_Protocol, 0, 0, 0, 0,
		         Macro128_Entry14_DelayMin, Macro128_Entry14_DelaySec, Macro128_Entry14_TimMin, Macro128_Entry14_TimSec, Macro128_Entry14_Protocol, 0, 0, 0, 0,
		         Macro128_Entry15_DelayMin, Macro128_Entry15_DelaySec, Macro128_Entry15_TimMin, Macro128_Entry15_TimSec, Macro128_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR128_STRING};

const struct super_macro Macro129 = {Macro129_NumEntries,
		         Macro129_Entry1_DelayMin, Macro129_Entry1_DelaySec, Macro129_Entry1_TimMin, Macro129_Entry1_TimSec, Macro129_Entry1_Protocol, 0, 0, 0, 0,
		         Macro129_Entry2_DelayMin, Macro129_Entry2_DelaySec, Macro129_Entry2_TimMin, Macro129_Entry2_TimSec, Macro129_Entry2_Protocol, 0, 0, 0, 0,
		         Macro129_Entry3_DelayMin, Macro129_Entry3_DelaySec, Macro129_Entry3_TimMin, Macro129_Entry3_TimSec, Macro129_Entry3_Protocol, 0, 0, 0, 0,
		         Macro129_Entry4_DelayMin, Macro129_Entry4_DelaySec, Macro129_Entry4_TimMin, Macro129_Entry4_TimSec, Macro129_Entry4_Protocol, 0, 0, 0, 0,
		         Macro129_Entry5_DelayMin, Macro129_Entry5_DelaySec, Macro129_Entry5_TimMin, Macro129_Entry5_TimSec, Macro129_Entry5_Protocol, 0, 0, 0, 0,
		         Macro129_Entry6_DelayMin, Macro129_Entry6_DelaySec, Macro129_Entry6_TimMin, Macro129_Entry6_TimSec, Macro129_Entry6_Protocol, 0, 0, 0, 0,
		         Macro129_Entry7_DelayMin, Macro129_Entry7_DelaySec, Macro129_Entry7_TimMin, Macro129_Entry7_TimSec, Macro129_Entry7_Protocol, 0, 0, 0, 0,
		         Macro129_Entry8_DelayMin, Macro129_Entry8_DelaySec, Macro129_Entry8_TimMin, Macro129_Entry8_TimSec, Macro129_Entry8_Protocol, 0, 0, 0, 0,
		         Macro129_Entry9_DelayMin, Macro129_Entry9_DelaySec, Macro129_Entry9_TimMin, Macro129_Entry9_TimSec, Macro129_Entry9_Protocol, 0, 0, 0, 0,
		         Macro129_Entry10_DelayMin, Macro129_Entry10_DelaySec, Macro129_Entry10_TimMin, Macro129_Entry10_TimSec, Macro129_Entry10_Protocol, 0, 0, 0, 0,
		         Macro129_Entry11_DelayMin, Macro129_Entry11_DelaySec, Macro129_Entry11_TimMin, Macro129_Entry11_TimSec, Macro129_Entry11_Protocol, 0, 0, 0, 0,
		         Macro129_Entry12_DelayMin, Macro129_Entry12_DelaySec, Macro129_Entry12_TimMin, Macro129_Entry12_TimSec, Macro129_Entry12_Protocol, 0, 0, 0, 0,
		         Macro129_Entry13_DelayMin, Macro129_Entry13_DelaySec, Macro129_Entry13_TimMin, Macro129_Entry13_TimSec, Macro129_Entry13_Protocol, 0, 0, 0, 0,
		         Macro129_Entry14_DelayMin, Macro129_Entry14_DelaySec, Macro129_Entry14_TimMin, Macro129_Entry14_TimSec, Macro129_Entry14_Protocol, 0, 0, 0, 0,
		         Macro129_Entry15_DelayMin, Macro129_Entry15_DelaySec, Macro129_Entry15_TimMin, Macro129_Entry15_TimSec, Macro129_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR129_STRING};

const struct super_macro Macro130 = {Macro130_NumEntries,
		         Macro130_Entry1_DelayMin, Macro130_Entry1_DelaySec, Macro130_Entry1_TimMin, Macro130_Entry1_TimSec, Macro130_Entry1_Protocol, 0, 0, 0, 0,
		         Macro130_Entry2_DelayMin, Macro130_Entry2_DelaySec, Macro130_Entry2_TimMin, Macro130_Entry2_TimSec, Macro130_Entry2_Protocol, 0, 0, 0, 0,
		         Macro130_Entry3_DelayMin, Macro130_Entry3_DelaySec, Macro130_Entry3_TimMin, Macro130_Entry3_TimSec, Macro130_Entry3_Protocol, 0, 0, 0, 0,
		         Macro130_Entry4_DelayMin, Macro130_Entry4_DelaySec, Macro130_Entry4_TimMin, Macro130_Entry4_TimSec, Macro130_Entry4_Protocol, 0, 0, 0, 0,
		         Macro130_Entry5_DelayMin, Macro130_Entry5_DelaySec, Macro130_Entry5_TimMin, Macro130_Entry5_TimSec, Macro130_Entry5_Protocol, 0, 0, 0, 0,
		         Macro130_Entry6_DelayMin, Macro130_Entry6_DelaySec, Macro130_Entry6_TimMin, Macro130_Entry6_TimSec, Macro130_Entry6_Protocol, 0, 0, 0, 0,
		         Macro130_Entry7_DelayMin, Macro130_Entry7_DelaySec, Macro130_Entry7_TimMin, Macro130_Entry7_TimSec, Macro130_Entry7_Protocol, 0, 0, 0, 0,
		         Macro130_Entry8_DelayMin, Macro130_Entry8_DelaySec, Macro130_Entry8_TimMin, Macro130_Entry8_TimSec, Macro130_Entry8_Protocol, 0, 0, 0, 0,
		         Macro130_Entry9_DelayMin, Macro130_Entry9_DelaySec, Macro130_Entry9_TimMin, Macro130_Entry9_TimSec, Macro130_Entry9_Protocol, 0, 0, 0, 0,
		         Macro130_Entry10_DelayMin, Macro130_Entry10_DelaySec, Macro130_Entry10_TimMin, Macro130_Entry10_TimSec, Macro130_Entry10_Protocol, 0, 0, 0, 0,
		         Macro130_Entry11_DelayMin, Macro130_Entry11_DelaySec, Macro130_Entry11_TimMin, Macro130_Entry11_TimSec, Macro130_Entry11_Protocol, 0, 0, 0, 0,
		         Macro130_Entry12_DelayMin, Macro130_Entry12_DelaySec, Macro130_Entry12_TimMin, Macro130_Entry12_TimSec, Macro130_Entry12_Protocol, 0, 0, 0, 0,
		         Macro130_Entry13_DelayMin, Macro130_Entry13_DelaySec, Macro130_Entry13_TimMin, Macro130_Entry13_TimSec, Macro130_Entry13_Protocol, 0, 0, 0, 0,
		         Macro130_Entry14_DelayMin, Macro130_Entry14_DelaySec, Macro130_Entry14_TimMin, Macro130_Entry14_TimSec, Macro130_Entry14_Protocol, 0, 0, 0, 0,
		         Macro130_Entry15_DelayMin, Macro130_Entry15_DelaySec, Macro130_Entry15_TimMin, Macro130_Entry15_TimSec, Macro130_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR130_STRING};

const struct super_macro Macro131 = {Macro131_NumEntries,
		         Macro131_Entry1_DelayMin, Macro131_Entry1_DelaySec, Macro131_Entry1_TimMin, Macro131_Entry1_TimSec, Macro131_Entry1_Protocol, 0, 0, 0, 0,
		         Macro131_Entry2_DelayMin, Macro131_Entry2_DelaySec, Macro131_Entry2_TimMin, Macro131_Entry2_TimSec, Macro131_Entry2_Protocol, 0, 0, 0, 0,
		         Macro131_Entry3_DelayMin, Macro131_Entry3_DelaySec, Macro131_Entry3_TimMin, Macro131_Entry3_TimSec, Macro131_Entry3_Protocol, 0, 0, 0, 0,
		         Macro131_Entry4_DelayMin, Macro131_Entry4_DelaySec, Macro131_Entry4_TimMin, Macro131_Entry4_TimSec, Macro131_Entry4_Protocol, 0, 0, 0, 0,
		         Macro131_Entry5_DelayMin, Macro131_Entry5_DelaySec, Macro131_Entry5_TimMin, Macro131_Entry5_TimSec, Macro131_Entry5_Protocol, 0, 0, 0, 0,
		         Macro131_Entry6_DelayMin, Macro131_Entry6_DelaySec, Macro131_Entry6_TimMin, Macro131_Entry6_TimSec, Macro131_Entry6_Protocol, 0, 0, 0, 0,
		         Macro131_Entry7_DelayMin, Macro131_Entry7_DelaySec, Macro131_Entry7_TimMin, Macro131_Entry7_TimSec, Macro131_Entry7_Protocol, 0, 0, 0, 0,
		         Macro131_Entry8_DelayMin, Macro131_Entry8_DelaySec, Macro131_Entry8_TimMin, Macro131_Entry8_TimSec, Macro131_Entry8_Protocol, 0, 0, 0, 0,
		         Macro131_Entry9_DelayMin, Macro131_Entry9_DelaySec, Macro131_Entry9_TimMin, Macro131_Entry9_TimSec, Macro131_Entry9_Protocol, 0, 0, 0, 0,
		         Macro131_Entry10_DelayMin, Macro131_Entry10_DelaySec, Macro131_Entry10_TimMin, Macro131_Entry10_TimSec, Macro131_Entry10_Protocol, 0, 0, 0, 0,
		         Macro131_Entry11_DelayMin, Macro131_Entry11_DelaySec, Macro131_Entry11_TimMin, Macro131_Entry11_TimSec, Macro131_Entry11_Protocol, 0, 0, 0, 0,
		         Macro131_Entry12_DelayMin, Macro131_Entry12_DelaySec, Macro131_Entry12_TimMin, Macro131_Entry12_TimSec, Macro131_Entry12_Protocol, 0, 0, 0, 0,
		         Macro131_Entry13_DelayMin, Macro131_Entry13_DelaySec, Macro131_Entry13_TimMin, Macro131_Entry13_TimSec, Macro131_Entry13_Protocol, 0, 0, 0, 0,
		         Macro131_Entry14_DelayMin, Macro131_Entry14_DelaySec, Macro131_Entry14_TimMin, Macro131_Entry14_TimSec, Macro131_Entry14_Protocol, 0, 0, 0, 0,
		         Macro131_Entry15_DelayMin, Macro131_Entry15_DelaySec, Macro131_Entry15_TimMin, Macro131_Entry15_TimSec, Macro131_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR131_STRING};

const struct super_macro Macro132 = {Macro132_NumEntries,
		         Macro132_Entry1_DelayMin, Macro132_Entry1_DelaySec, Macro132_Entry1_TimMin, Macro132_Entry1_TimSec, Macro132_Entry1_Protocol, 0, 0, 0, 0,
		         Macro132_Entry2_DelayMin, Macro132_Entry2_DelaySec, Macro132_Entry2_TimMin, Macro132_Entry2_TimSec, Macro132_Entry2_Protocol, 0, 0, 0, 0,
		         Macro132_Entry3_DelayMin, Macro132_Entry3_DelaySec, Macro132_Entry3_TimMin, Macro132_Entry3_TimSec, Macro132_Entry3_Protocol, 0, 0, 0, 0,
		         Macro132_Entry4_DelayMin, Macro132_Entry4_DelaySec, Macro132_Entry4_TimMin, Macro132_Entry4_TimSec, Macro132_Entry4_Protocol, 0, 0, 0, 0,
		         Macro132_Entry5_DelayMin, Macro132_Entry5_DelaySec, Macro132_Entry5_TimMin, Macro132_Entry5_TimSec, Macro132_Entry5_Protocol, 0, 0, 0, 0,
		         Macro132_Entry6_DelayMin, Macro132_Entry6_DelaySec, Macro132_Entry6_TimMin, Macro132_Entry6_TimSec, Macro132_Entry6_Protocol, 0, 0, 0, 0,
		         Macro132_Entry7_DelayMin, Macro132_Entry7_DelaySec, Macro132_Entry7_TimMin, Macro132_Entry7_TimSec, Macro132_Entry7_Protocol, 0, 0, 0, 0,
		         Macro132_Entry8_DelayMin, Macro132_Entry8_DelaySec, Macro132_Entry8_TimMin, Macro132_Entry8_TimSec, Macro132_Entry8_Protocol, 0, 0, 0, 0,
		         Macro132_Entry9_DelayMin, Macro132_Entry9_DelaySec, Macro132_Entry9_TimMin, Macro132_Entry9_TimSec, Macro132_Entry9_Protocol, 0, 0, 0, 0,
		         Macro132_Entry10_DelayMin, Macro132_Entry10_DelaySec, Macro132_Entry10_TimMin, Macro132_Entry10_TimSec, Macro132_Entry10_Protocol, 0, 0, 0, 0,
		         Macro132_Entry11_DelayMin, Macro132_Entry11_DelaySec, Macro132_Entry11_TimMin, Macro132_Entry11_TimSec, Macro132_Entry11_Protocol, 0, 0, 0, 0,
		         Macro132_Entry12_DelayMin, Macro132_Entry12_DelaySec, Macro132_Entry12_TimMin, Macro132_Entry12_TimSec, Macro132_Entry12_Protocol, 0, 0, 0, 0,
		         Macro132_Entry13_DelayMin, Macro132_Entry13_DelaySec, Macro132_Entry13_TimMin, Macro132_Entry13_TimSec, Macro132_Entry13_Protocol, 0, 0, 0, 0,
		         Macro132_Entry14_DelayMin, Macro132_Entry14_DelaySec, Macro132_Entry14_TimMin, Macro132_Entry14_TimSec, Macro132_Entry14_Protocol, 0, 0, 0, 0,
		         Macro132_Entry15_DelayMin, Macro132_Entry15_DelaySec, Macro132_Entry15_TimMin, Macro132_Entry15_TimSec, Macro132_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR132_STRING};

const struct super_macro Macro133 = {Macro133_NumEntries,
		         Macro133_Entry1_DelayMin, Macro133_Entry1_DelaySec, Macro133_Entry1_TimMin, Macro133_Entry1_TimSec, Macro133_Entry1_Protocol, 0, 0, 0, 0,
		         Macro133_Entry2_DelayMin, Macro133_Entry2_DelaySec, Macro133_Entry2_TimMin, Macro133_Entry2_TimSec, Macro133_Entry2_Protocol, 0, 0, 0, 0,
		         Macro133_Entry3_DelayMin, Macro133_Entry3_DelaySec, Macro133_Entry3_TimMin, Macro133_Entry3_TimSec, Macro133_Entry3_Protocol, 0, 0, 0, 0,
		         Macro133_Entry4_DelayMin, Macro133_Entry4_DelaySec, Macro133_Entry4_TimMin, Macro133_Entry4_TimSec, Macro133_Entry4_Protocol, 0, 0, 0, 0,
		         Macro133_Entry5_DelayMin, Macro133_Entry5_DelaySec, Macro133_Entry5_TimMin, Macro133_Entry5_TimSec, Macro133_Entry5_Protocol, 0, 0, 0, 0,
		         Macro133_Entry6_DelayMin, Macro133_Entry6_DelaySec, Macro133_Entry6_TimMin, Macro133_Entry6_TimSec, Macro133_Entry6_Protocol, 0, 0, 0, 0,
		         Macro133_Entry7_DelayMin, Macro133_Entry7_DelaySec, Macro133_Entry7_TimMin, Macro133_Entry7_TimSec, Macro133_Entry7_Protocol, 0, 0, 0, 0,
		         Macro133_Entry8_DelayMin, Macro133_Entry8_DelaySec, Macro133_Entry8_TimMin, Macro133_Entry8_TimSec, Macro133_Entry8_Protocol, 0, 0, 0, 0,
		         Macro133_Entry9_DelayMin, Macro133_Entry9_DelaySec, Macro133_Entry9_TimMin, Macro133_Entry9_TimSec, Macro133_Entry9_Protocol, 0, 0, 0, 0,
		         Macro133_Entry10_DelayMin, Macro133_Entry10_DelaySec, Macro133_Entry10_TimMin, Macro133_Entry10_TimSec, Macro133_Entry10_Protocol, 0, 0, 0, 0,
		         Macro133_Entry11_DelayMin, Macro133_Entry11_DelaySec, Macro133_Entry11_TimMin, Macro133_Entry11_TimSec, Macro133_Entry11_Protocol, 0, 0, 0, 0,
		         Macro133_Entry12_DelayMin, Macro133_Entry12_DelaySec, Macro133_Entry12_TimMin, Macro133_Entry12_TimSec, Macro133_Entry12_Protocol, 0, 0, 0, 0,
		         Macro133_Entry13_DelayMin, Macro133_Entry13_DelaySec, Macro133_Entry13_TimMin, Macro133_Entry13_TimSec, Macro133_Entry13_Protocol, 0, 0, 0, 0,
		         Macro133_Entry14_DelayMin, Macro133_Entry14_DelaySec, Macro133_Entry14_TimMin, Macro133_Entry14_TimSec, Macro133_Entry14_Protocol, 0, 0, 0, 0,
		         Macro133_Entry15_DelayMin, Macro133_Entry15_DelaySec, Macro133_Entry15_TimMin, Macro133_Entry15_TimSec, Macro133_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR133_STRING};

const struct super_macro Macro134 = {Macro134_NumEntries,
		         Macro134_Entry1_DelayMin, Macro134_Entry1_DelaySec, Macro134_Entry1_TimMin, Macro134_Entry1_TimSec, Macro134_Entry1_Protocol, 0, 0, 0, 0,
		         Macro134_Entry2_DelayMin, Macro134_Entry2_DelaySec, Macro134_Entry2_TimMin, Macro134_Entry2_TimSec, Macro134_Entry2_Protocol, 0, 0, 0, 0,
		         Macro134_Entry3_DelayMin, Macro134_Entry3_DelaySec, Macro134_Entry3_TimMin, Macro134_Entry3_TimSec, Macro134_Entry3_Protocol, 0, 0, 0, 0,
		         Macro134_Entry4_DelayMin, Macro134_Entry4_DelaySec, Macro134_Entry4_TimMin, Macro134_Entry4_TimSec, Macro134_Entry4_Protocol, 0, 0, 0, 0,
		         Macro134_Entry5_DelayMin, Macro134_Entry5_DelaySec, Macro134_Entry5_TimMin, Macro134_Entry5_TimSec, Macro134_Entry5_Protocol, 0, 0, 0, 0,
		         Macro134_Entry6_DelayMin, Macro134_Entry6_DelaySec, Macro134_Entry6_TimMin, Macro134_Entry6_TimSec, Macro134_Entry6_Protocol, 0, 0, 0, 0,
		         Macro134_Entry7_DelayMin, Macro134_Entry7_DelaySec, Macro134_Entry7_TimMin, Macro134_Entry7_TimSec, Macro134_Entry7_Protocol, 0, 0, 0, 0,
		         Macro134_Entry8_DelayMin, Macro134_Entry8_DelaySec, Macro134_Entry8_TimMin, Macro134_Entry8_TimSec, Macro134_Entry8_Protocol, 0, 0, 0, 0,
		         Macro134_Entry9_DelayMin, Macro134_Entry9_DelaySec, Macro134_Entry9_TimMin, Macro134_Entry9_TimSec, Macro134_Entry9_Protocol, 0, 0, 0, 0,
		         Macro134_Entry10_DelayMin, Macro134_Entry10_DelaySec, Macro134_Entry10_TimMin, Macro134_Entry10_TimSec, Macro134_Entry10_Protocol, 0, 0, 0, 0,
		         Macro134_Entry11_DelayMin, Macro134_Entry11_DelaySec, Macro134_Entry11_TimMin, Macro134_Entry11_TimSec, Macro134_Entry11_Protocol, 0, 0, 0, 0,
		         Macro134_Entry12_DelayMin, Macro134_Entry12_DelaySec, Macro134_Entry12_TimMin, Macro134_Entry12_TimSec, Macro134_Entry12_Protocol, 0, 0, 0, 0,
		         Macro134_Entry13_DelayMin, Macro134_Entry13_DelaySec, Macro134_Entry13_TimMin, Macro134_Entry13_TimSec, Macro134_Entry13_Protocol, 0, 0, 0, 0,
		         Macro134_Entry14_DelayMin, Macro134_Entry14_DelaySec, Macro134_Entry14_TimMin, Macro134_Entry14_TimSec, Macro134_Entry14_Protocol, 0, 0, 0, 0,
		         Macro134_Entry15_DelayMin, Macro134_Entry15_DelaySec, Macro134_Entry15_TimMin, Macro134_Entry15_TimSec, Macro134_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR134_STRING};

const struct super_macro Macro135 = {Macro135_NumEntries,
		         Macro135_Entry1_DelayMin, Macro135_Entry1_DelaySec, Macro135_Entry1_TimMin, Macro135_Entry1_TimSec, Macro135_Entry1_Protocol, 0, 0, 0, 0,
		         Macro135_Entry2_DelayMin, Macro135_Entry2_DelaySec, Macro135_Entry2_TimMin, Macro135_Entry2_TimSec, Macro135_Entry2_Protocol, 0, 0, 0, 0,
		         Macro135_Entry3_DelayMin, Macro135_Entry3_DelaySec, Macro135_Entry3_TimMin, Macro135_Entry3_TimSec, Macro135_Entry3_Protocol, 0, 0, 0, 0,
		         Macro135_Entry4_DelayMin, Macro135_Entry4_DelaySec, Macro135_Entry4_TimMin, Macro135_Entry4_TimSec, Macro135_Entry4_Protocol, 0, 0, 0, 0,
		         Macro135_Entry5_DelayMin, Macro135_Entry5_DelaySec, Macro135_Entry5_TimMin, Macro135_Entry5_TimSec, Macro135_Entry5_Protocol, 0, 0, 0, 0,
		         Macro135_Entry6_DelayMin, Macro135_Entry6_DelaySec, Macro135_Entry6_TimMin, Macro135_Entry6_TimSec, Macro135_Entry6_Protocol, 0, 0, 0, 0,
		         Macro135_Entry7_DelayMin, Macro135_Entry7_DelaySec, Macro135_Entry7_TimMin, Macro135_Entry7_TimSec, Macro135_Entry7_Protocol, 0, 0, 0, 0,
		         Macro135_Entry8_DelayMin, Macro135_Entry8_DelaySec, Macro135_Entry8_TimMin, Macro135_Entry8_TimSec, Macro135_Entry8_Protocol, 0, 0, 0, 0,
		         Macro135_Entry9_DelayMin, Macro135_Entry9_DelaySec, Macro135_Entry9_TimMin, Macro135_Entry9_TimSec, Macro135_Entry9_Protocol, 0, 0, 0, 0,
		         Macro135_Entry10_DelayMin, Macro135_Entry10_DelaySec, Macro135_Entry10_TimMin, Macro135_Entry10_TimSec, Macro135_Entry10_Protocol, 0, 0, 0, 0,
		         Macro135_Entry11_DelayMin, Macro135_Entry11_DelaySec, Macro135_Entry11_TimMin, Macro135_Entry11_TimSec, Macro135_Entry11_Protocol, 0, 0, 0, 0,
		         Macro135_Entry12_DelayMin, Macro135_Entry12_DelaySec, Macro135_Entry12_TimMin, Macro135_Entry12_TimSec, Macro135_Entry12_Protocol, 0, 0, 0, 0,
		         Macro135_Entry13_DelayMin, Macro135_Entry13_DelaySec, Macro135_Entry13_TimMin, Macro135_Entry13_TimSec, Macro135_Entry13_Protocol, 0, 0, 0, 0,
		         Macro135_Entry14_DelayMin, Macro135_Entry14_DelaySec, Macro135_Entry14_TimMin, Macro135_Entry14_TimSec, Macro135_Entry14_Protocol, 0, 0, 0, 0,
		         Macro135_Entry15_DelayMin, Macro135_Entry15_DelaySec, Macro135_Entry15_TimMin, Macro135_Entry15_TimSec, Macro135_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR135_STRING};

const struct super_macro Macro136 = {Macro136_NumEntries,
		         Macro136_Entry1_DelayMin, Macro136_Entry1_DelaySec, Macro136_Entry1_TimMin, Macro136_Entry1_TimSec, Macro136_Entry1_Protocol, 0, 0, 0, 0,
		         Macro136_Entry2_DelayMin, Macro136_Entry2_DelaySec, Macro136_Entry2_TimMin, Macro136_Entry2_TimSec, Macro136_Entry2_Protocol, 0, 0, 0, 0,
		         Macro136_Entry3_DelayMin, Macro136_Entry3_DelaySec, Macro136_Entry3_TimMin, Macro136_Entry3_TimSec, Macro136_Entry3_Protocol, 0, 0, 0, 0,
		         Macro136_Entry4_DelayMin, Macro136_Entry4_DelaySec, Macro136_Entry4_TimMin, Macro136_Entry4_TimSec, Macro136_Entry4_Protocol, 0, 0, 0, 0,
		         Macro136_Entry5_DelayMin, Macro136_Entry5_DelaySec, Macro136_Entry5_TimMin, Macro136_Entry5_TimSec, Macro136_Entry5_Protocol, 0, 0, 0, 0,
		         Macro136_Entry6_DelayMin, Macro136_Entry6_DelaySec, Macro136_Entry6_TimMin, Macro136_Entry6_TimSec, Macro136_Entry6_Protocol, 0, 0, 0, 0,
		         Macro136_Entry7_DelayMin, Macro136_Entry7_DelaySec, Macro136_Entry7_TimMin, Macro136_Entry7_TimSec, Macro136_Entry7_Protocol, 0, 0, 0, 0,
		         Macro136_Entry8_DelayMin, Macro136_Entry8_DelaySec, Macro136_Entry8_TimMin, Macro136_Entry8_TimSec, Macro136_Entry8_Protocol, 0, 0, 0, 0,
		         Macro136_Entry9_DelayMin, Macro136_Entry9_DelaySec, Macro136_Entry9_TimMin, Macro136_Entry9_TimSec, Macro136_Entry9_Protocol, 0, 0, 0, 0,
		         Macro136_Entry10_DelayMin, Macro136_Entry10_DelaySec, Macro136_Entry10_TimMin, Macro136_Entry10_TimSec, Macro136_Entry10_Protocol, 0, 0, 0, 0,
		         Macro136_Entry11_DelayMin, Macro136_Entry11_DelaySec, Macro136_Entry11_TimMin, Macro136_Entry11_TimSec, Macro136_Entry11_Protocol, 0, 0, 0, 0,
		         Macro136_Entry12_DelayMin, Macro136_Entry12_DelaySec, Macro136_Entry12_TimMin, Macro136_Entry12_TimSec, Macro136_Entry12_Protocol, 0, 0, 0, 0,
		         Macro136_Entry13_DelayMin, Macro136_Entry13_DelaySec, Macro136_Entry13_TimMin, Macro136_Entry13_TimSec, Macro136_Entry13_Protocol, 0, 0, 0, 0,
		         Macro136_Entry14_DelayMin, Macro136_Entry14_DelaySec, Macro136_Entry14_TimMin, Macro136_Entry14_TimSec, Macro136_Entry14_Protocol, 0, 0, 0, 0,
		         Macro136_Entry15_DelayMin, Macro136_Entry15_DelaySec, Macro136_Entry15_TimMin, Macro136_Entry15_TimSec, Macro136_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR136_STRING};

const struct super_macro Macro137 = {Macro137_NumEntries,
		         Macro137_Entry1_DelayMin, Macro137_Entry1_DelaySec, Macro137_Entry1_TimMin, Macro137_Entry1_TimSec, Macro137_Entry1_Protocol, 0, 0, 0, 0,
		         Macro137_Entry2_DelayMin, Macro137_Entry2_DelaySec, Macro137_Entry2_TimMin, Macro137_Entry2_TimSec, Macro137_Entry2_Protocol, 0, 0, 0, 0,
		         Macro137_Entry3_DelayMin, Macro137_Entry3_DelaySec, Macro137_Entry3_TimMin, Macro137_Entry3_TimSec, Macro137_Entry3_Protocol, 0, 0, 0, 0,
		         Macro137_Entry4_DelayMin, Macro137_Entry4_DelaySec, Macro137_Entry4_TimMin, Macro137_Entry4_TimSec, Macro137_Entry4_Protocol, 0, 0, 0, 0,
		         Macro137_Entry5_DelayMin, Macro137_Entry5_DelaySec, Macro137_Entry5_TimMin, Macro137_Entry5_TimSec, Macro137_Entry5_Protocol, 0, 0, 0, 0,
		         Macro137_Entry6_DelayMin, Macro137_Entry6_DelaySec, Macro137_Entry6_TimMin, Macro137_Entry6_TimSec, Macro137_Entry6_Protocol, 0, 0, 0, 0,
		         Macro137_Entry7_DelayMin, Macro137_Entry7_DelaySec, Macro137_Entry7_TimMin, Macro137_Entry7_TimSec, Macro137_Entry7_Protocol, 0, 0, 0, 0,
		         Macro137_Entry8_DelayMin, Macro137_Entry8_DelaySec, Macro137_Entry8_TimMin, Macro137_Entry8_TimSec, Macro137_Entry8_Protocol, 0, 0, 0, 0,
		         Macro137_Entry9_DelayMin, Macro137_Entry9_DelaySec, Macro137_Entry9_TimMin, Macro137_Entry9_TimSec, Macro137_Entry9_Protocol, 0, 0, 0, 0,
		         Macro137_Entry10_DelayMin, Macro137_Entry10_DelaySec, Macro137_Entry10_TimMin, Macro137_Entry10_TimSec, Macro137_Entry10_Protocol, 0, 0, 0, 0,
		         Macro137_Entry11_DelayMin, Macro137_Entry11_DelaySec, Macro137_Entry11_TimMin, Macro137_Entry11_TimSec, Macro137_Entry11_Protocol, 0, 0, 0, 0,
		         Macro137_Entry12_DelayMin, Macro137_Entry12_DelaySec, Macro137_Entry12_TimMin, Macro137_Entry12_TimSec, Macro137_Entry12_Protocol, 0, 0, 0, 0,
		         Macro137_Entry13_DelayMin, Macro137_Entry13_DelaySec, Macro137_Entry13_TimMin, Macro137_Entry13_TimSec, Macro137_Entry13_Protocol, 0, 0, 0, 0,
		         Macro137_Entry14_DelayMin, Macro137_Entry14_DelaySec, Macro137_Entry14_TimMin, Macro137_Entry14_TimSec, Macro137_Entry14_Protocol, 0, 0, 0, 0,
		         Macro137_Entry15_DelayMin, Macro137_Entry15_DelaySec, Macro137_Entry15_TimMin, Macro137_Entry15_TimSec, Macro137_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR137_STRING};

const struct super_macro Macro138 = {Macro138_NumEntries,
		         Macro138_Entry1_DelayMin, Macro138_Entry1_DelaySec, Macro138_Entry1_TimMin, Macro138_Entry1_TimSec, Macro138_Entry1_Protocol, 0, 0, 0, 0,
		         Macro138_Entry2_DelayMin, Macro138_Entry2_DelaySec, Macro138_Entry2_TimMin, Macro138_Entry2_TimSec, Macro138_Entry2_Protocol, 0, 0, 0, 0,
		         Macro138_Entry3_DelayMin, Macro138_Entry3_DelaySec, Macro138_Entry3_TimMin, Macro138_Entry3_TimSec, Macro138_Entry3_Protocol, 0, 0, 0, 0,
		         Macro138_Entry4_DelayMin, Macro138_Entry4_DelaySec, Macro138_Entry4_TimMin, Macro138_Entry4_TimSec, Macro138_Entry4_Protocol, 0, 0, 0, 0,
		         Macro138_Entry5_DelayMin, Macro138_Entry5_DelaySec, Macro138_Entry5_TimMin, Macro138_Entry5_TimSec, Macro138_Entry5_Protocol, 0, 0, 0, 0,
		         Macro138_Entry6_DelayMin, Macro138_Entry6_DelaySec, Macro138_Entry6_TimMin, Macro138_Entry6_TimSec, Macro138_Entry6_Protocol, 0, 0, 0, 0,
		         Macro138_Entry7_DelayMin, Macro138_Entry7_DelaySec, Macro138_Entry7_TimMin, Macro138_Entry7_TimSec, Macro138_Entry7_Protocol, 0, 0, 0, 0,
		         Macro138_Entry8_DelayMin, Macro138_Entry8_DelaySec, Macro138_Entry8_TimMin, Macro138_Entry8_TimSec, Macro138_Entry8_Protocol, 0, 0, 0, 0,
		         Macro138_Entry9_DelayMin, Macro138_Entry9_DelaySec, Macro138_Entry9_TimMin, Macro138_Entry9_TimSec, Macro138_Entry9_Protocol, 0, 0, 0, 0,
		         Macro138_Entry10_DelayMin, Macro138_Entry10_DelaySec, Macro138_Entry10_TimMin, Macro138_Entry10_TimSec, Macro138_Entry10_Protocol, 0, 0, 0, 0,
		         Macro138_Entry11_DelayMin, Macro138_Entry11_DelaySec, Macro138_Entry11_TimMin, Macro138_Entry11_TimSec, Macro138_Entry11_Protocol, 0, 0, 0, 0,
		         Macro138_Entry12_DelayMin, Macro138_Entry12_DelaySec, Macro138_Entry12_TimMin, Macro138_Entry12_TimSec, Macro138_Entry12_Protocol, 0, 0, 0, 0,
		         Macro138_Entry13_DelayMin, Macro138_Entry13_DelaySec, Macro138_Entry13_TimMin, Macro138_Entry13_TimSec, Macro138_Entry13_Protocol, 0, 0, 0, 0,
		         Macro138_Entry14_DelayMin, Macro138_Entry14_DelaySec, Macro138_Entry14_TimMin, Macro138_Entry14_TimSec, Macro138_Entry14_Protocol, 0, 0, 0, 0,
		         Macro138_Entry15_DelayMin, Macro138_Entry15_DelaySec, Macro138_Entry15_TimMin, Macro138_Entry15_TimSec, Macro138_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR138_STRING};

const struct super_macro Macro139 = {Macro139_NumEntries,
		         Macro139_Entry1_DelayMin, Macro139_Entry1_DelaySec, Macro139_Entry1_TimMin, Macro139_Entry1_TimSec, Macro139_Entry1_Protocol, 0, 0, 0, 0,
		         Macro139_Entry2_DelayMin, Macro139_Entry2_DelaySec, Macro139_Entry2_TimMin, Macro139_Entry2_TimSec, Macro139_Entry2_Protocol, 0, 0, 0, 0,
		         Macro139_Entry3_DelayMin, Macro139_Entry3_DelaySec, Macro139_Entry3_TimMin, Macro139_Entry3_TimSec, Macro139_Entry3_Protocol, 0, 0, 0, 0,
		         Macro139_Entry4_DelayMin, Macro139_Entry4_DelaySec, Macro139_Entry4_TimMin, Macro139_Entry4_TimSec, Macro139_Entry4_Protocol, 0, 0, 0, 0,
		         Macro139_Entry5_DelayMin, Macro139_Entry5_DelaySec, Macro139_Entry5_TimMin, Macro139_Entry5_TimSec, Macro139_Entry5_Protocol, 0, 0, 0, 0,
		         Macro139_Entry6_DelayMin, Macro139_Entry6_DelaySec, Macro139_Entry6_TimMin, Macro139_Entry6_TimSec, Macro139_Entry6_Protocol, 0, 0, 0, 0,
		         Macro139_Entry7_DelayMin, Macro139_Entry7_DelaySec, Macro139_Entry7_TimMin, Macro139_Entry7_TimSec, Macro139_Entry7_Protocol, 0, 0, 0, 0,
		         Macro139_Entry8_DelayMin, Macro139_Entry8_DelaySec, Macro139_Entry8_TimMin, Macro139_Entry8_TimSec, Macro139_Entry8_Protocol, 0, 0, 0, 0,
		         Macro139_Entry9_DelayMin, Macro139_Entry9_DelaySec, Macro139_Entry9_TimMin, Macro139_Entry9_TimSec, Macro139_Entry9_Protocol, 0, 0, 0, 0,
		         Macro139_Entry10_DelayMin, Macro139_Entry10_DelaySec, Macro139_Entry10_TimMin, Macro139_Entry10_TimSec, Macro139_Entry10_Protocol, 0, 0, 0, 0,
		         Macro139_Entry11_DelayMin, Macro139_Entry11_DelaySec, Macro139_Entry11_TimMin, Macro139_Entry11_TimSec, Macro139_Entry11_Protocol, 0, 0, 0, 0,
		         Macro139_Entry12_DelayMin, Macro139_Entry12_DelaySec, Macro139_Entry12_TimMin, Macro139_Entry12_TimSec, Macro139_Entry12_Protocol, 0, 0, 0, 0,
		         Macro139_Entry13_DelayMin, Macro139_Entry13_DelaySec, Macro139_Entry13_TimMin, Macro139_Entry13_TimSec, Macro139_Entry13_Protocol, 0, 0, 0, 0,
		         Macro139_Entry14_DelayMin, Macro139_Entry14_DelaySec, Macro139_Entry14_TimMin, Macro139_Entry14_TimSec, Macro139_Entry14_Protocol, 0, 0, 0, 0,
		         Macro139_Entry15_DelayMin, Macro139_Entry15_DelaySec, Macro139_Entry15_TimMin, Macro139_Entry15_TimSec, Macro139_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR139_STRING};

const struct super_macro Macro140 = {Macro140_NumEntries,
		         Macro140_Entry1_DelayMin, Macro140_Entry1_DelaySec, Macro140_Entry1_TimMin, Macro140_Entry1_TimSec, Macro140_Entry1_Protocol, 0, 0, 0, 0,
		         Macro140_Entry2_DelayMin, Macro140_Entry2_DelaySec, Macro140_Entry2_TimMin, Macro140_Entry2_TimSec, Macro140_Entry2_Protocol, 0, 0, 0, 0,
		         Macro140_Entry3_DelayMin, Macro140_Entry3_DelaySec, Macro140_Entry3_TimMin, Macro140_Entry3_TimSec, Macro140_Entry3_Protocol, 0, 0, 0, 0,
		         Macro140_Entry4_DelayMin, Macro140_Entry4_DelaySec, Macro140_Entry4_TimMin, Macro140_Entry4_TimSec, Macro140_Entry4_Protocol, 0, 0, 0, 0,
		         Macro140_Entry5_DelayMin, Macro140_Entry5_DelaySec, Macro140_Entry5_TimMin, Macro140_Entry5_TimSec, Macro140_Entry5_Protocol, 0, 0, 0, 0,
		         Macro140_Entry6_DelayMin, Macro140_Entry6_DelaySec, Macro140_Entry6_TimMin, Macro140_Entry6_TimSec, Macro140_Entry6_Protocol, 0, 0, 0, 0,
		         Macro140_Entry7_DelayMin, Macro140_Entry7_DelaySec, Macro140_Entry7_TimMin, Macro140_Entry7_TimSec, Macro140_Entry7_Protocol, 0, 0, 0, 0,
		         Macro140_Entry8_DelayMin, Macro140_Entry8_DelaySec, Macro140_Entry8_TimMin, Macro140_Entry8_TimSec, Macro140_Entry8_Protocol, 0, 0, 0, 0,
		         Macro140_Entry9_DelayMin, Macro140_Entry9_DelaySec, Macro140_Entry9_TimMin, Macro140_Entry9_TimSec, Macro140_Entry9_Protocol, 0, 0, 0, 0,
		         Macro140_Entry10_DelayMin, Macro140_Entry10_DelaySec, Macro140_Entry10_TimMin, Macro140_Entry10_TimSec, Macro140_Entry10_Protocol, 0, 0, 0, 0,
		         Macro140_Entry11_DelayMin, Macro140_Entry11_DelaySec, Macro140_Entry11_TimMin, Macro140_Entry11_TimSec, Macro140_Entry11_Protocol, 0, 0, 0, 0,
		         Macro140_Entry12_DelayMin, Macro140_Entry12_DelaySec, Macro140_Entry12_TimMin, Macro140_Entry12_TimSec, Macro140_Entry12_Protocol, 0, 0, 0, 0,
		         Macro140_Entry13_DelayMin, Macro140_Entry13_DelaySec, Macro140_Entry13_TimMin, Macro140_Entry13_TimSec, Macro140_Entry13_Protocol, 0, 0, 0, 0,
		         Macro140_Entry14_DelayMin, Macro140_Entry14_DelaySec, Macro140_Entry14_TimMin, Macro140_Entry14_TimSec, Macro140_Entry14_Protocol, 0, 0, 0, 0,
		         Macro140_Entry15_DelayMin, Macro140_Entry15_DelaySec, Macro140_Entry15_TimMin, Macro140_Entry15_TimSec, Macro140_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR140_STRING};

const struct super_macro Macro141 = {Macro141_NumEntries,
		         Macro141_Entry1_DelayMin, Macro141_Entry1_DelaySec, Macro141_Entry1_TimMin, Macro141_Entry1_TimSec, Macro141_Entry1_Protocol, 0, 0, 0, 0,
		         Macro141_Entry2_DelayMin, Macro141_Entry2_DelaySec, Macro141_Entry2_TimMin, Macro141_Entry2_TimSec, Macro141_Entry2_Protocol, 0, 0, 0, 0,
		         Macro141_Entry3_DelayMin, Macro141_Entry3_DelaySec, Macro141_Entry3_TimMin, Macro141_Entry3_TimSec, Macro141_Entry3_Protocol, 0, 0, 0, 0,
		         Macro141_Entry4_DelayMin, Macro141_Entry4_DelaySec, Macro141_Entry4_TimMin, Macro141_Entry4_TimSec, Macro141_Entry4_Protocol, 0, 0, 0, 0,
		         Macro141_Entry5_DelayMin, Macro141_Entry5_DelaySec, Macro141_Entry5_TimMin, Macro141_Entry5_TimSec, Macro141_Entry5_Protocol, 0, 0, 0, 0,
		         Macro141_Entry6_DelayMin, Macro141_Entry6_DelaySec, Macro141_Entry6_TimMin, Macro141_Entry6_TimSec, Macro141_Entry6_Protocol, 0, 0, 0, 0,
		         Macro141_Entry7_DelayMin, Macro141_Entry7_DelaySec, Macro141_Entry7_TimMin, Macro141_Entry7_TimSec, Macro141_Entry7_Protocol, 0, 0, 0, 0,
		         Macro141_Entry8_DelayMin, Macro141_Entry8_DelaySec, Macro141_Entry8_TimMin, Macro141_Entry8_TimSec, Macro141_Entry8_Protocol, 0, 0, 0, 0,
		         Macro141_Entry9_DelayMin, Macro141_Entry9_DelaySec, Macro141_Entry9_TimMin, Macro141_Entry9_TimSec, Macro141_Entry9_Protocol, 0, 0, 0, 0,
		         Macro141_Entry10_DelayMin, Macro141_Entry10_DelaySec, Macro141_Entry10_TimMin, Macro141_Entry10_TimSec, Macro141_Entry10_Protocol, 0, 0, 0, 0,
		         Macro141_Entry11_DelayMin, Macro141_Entry11_DelaySec, Macro141_Entry11_TimMin, Macro141_Entry11_TimSec, Macro141_Entry11_Protocol, 0, 0, 0, 0,
		         Macro141_Entry12_DelayMin, Macro141_Entry12_DelaySec, Macro141_Entry12_TimMin, Macro141_Entry12_TimSec, Macro141_Entry12_Protocol, 0, 0, 0, 0,
		         Macro141_Entry13_DelayMin, Macro141_Entry13_DelaySec, Macro141_Entry13_TimMin, Macro141_Entry13_TimSec, Macro141_Entry13_Protocol, 0, 0, 0, 0,
		         Macro141_Entry14_DelayMin, Macro141_Entry14_DelaySec, Macro141_Entry14_TimMin, Macro141_Entry14_TimSec, Macro141_Entry14_Protocol, 0, 0, 0, 0,
		         Macro141_Entry15_DelayMin, Macro141_Entry15_DelaySec, Macro141_Entry15_TimMin, Macro141_Entry15_TimSec, Macro141_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR141_STRING};

const struct super_macro Macro142 = {Macro142_NumEntries,
		         Macro142_Entry1_DelayMin, Macro142_Entry1_DelaySec, Macro142_Entry1_TimMin, Macro142_Entry1_TimSec, Macro142_Entry1_Protocol, 0, 0, 0, 0,
		         Macro142_Entry2_DelayMin, Macro142_Entry2_DelaySec, Macro142_Entry2_TimMin, Macro142_Entry2_TimSec, Macro142_Entry2_Protocol, 0, 0, 0, 0,
		         Macro142_Entry3_DelayMin, Macro142_Entry3_DelaySec, Macro142_Entry3_TimMin, Macro142_Entry3_TimSec, Macro142_Entry3_Protocol, 0, 0, 0, 0,
		         Macro142_Entry4_DelayMin, Macro142_Entry4_DelaySec, Macro142_Entry4_TimMin, Macro142_Entry4_TimSec, Macro142_Entry4_Protocol, 0, 0, 0, 0,
		         Macro142_Entry5_DelayMin, Macro142_Entry5_DelaySec, Macro142_Entry5_TimMin, Macro142_Entry5_TimSec, Macro142_Entry5_Protocol, 0, 0, 0, 0,
		         Macro142_Entry6_DelayMin, Macro142_Entry6_DelaySec, Macro142_Entry6_TimMin, Macro142_Entry6_TimSec, Macro142_Entry6_Protocol, 0, 0, 0, 0,
		         Macro142_Entry7_DelayMin, Macro142_Entry7_DelaySec, Macro142_Entry7_TimMin, Macro142_Entry7_TimSec, Macro142_Entry7_Protocol, 0, 0, 0, 0,
		         Macro142_Entry8_DelayMin, Macro142_Entry8_DelaySec, Macro142_Entry8_TimMin, Macro142_Entry8_TimSec, Macro142_Entry8_Protocol, 0, 0, 0, 0,
		         Macro142_Entry9_DelayMin, Macro142_Entry9_DelaySec, Macro142_Entry9_TimMin, Macro142_Entry9_TimSec, Macro142_Entry9_Protocol, 0, 0, 0, 0,
		         Macro142_Entry10_DelayMin, Macro142_Entry10_DelaySec, Macro142_Entry10_TimMin, Macro142_Entry10_TimSec, Macro142_Entry10_Protocol, 0, 0, 0, 0,
		         Macro142_Entry11_DelayMin, Macro142_Entry11_DelaySec, Macro142_Entry11_TimMin, Macro142_Entry11_TimSec, Macro142_Entry11_Protocol, 0, 0, 0, 0,
		         Macro142_Entry12_DelayMin, Macro142_Entry12_DelaySec, Macro142_Entry12_TimMin, Macro142_Entry12_TimSec, Macro142_Entry12_Protocol, 0, 0, 0, 0,
		         Macro142_Entry13_DelayMin, Macro142_Entry13_DelaySec, Macro142_Entry13_TimMin, Macro142_Entry13_TimSec, Macro142_Entry13_Protocol, 0, 0, 0, 0,
		         Macro142_Entry14_DelayMin, Macro142_Entry14_DelaySec, Macro142_Entry14_TimMin, Macro142_Entry14_TimSec, Macro142_Entry14_Protocol, 0, 0, 0, 0,
		         Macro142_Entry15_DelayMin, Macro142_Entry15_DelaySec, Macro142_Entry15_TimMin, Macro142_Entry15_TimSec, Macro142_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR142_STRING};

const struct super_macro Macro143 = {Macro143_NumEntries,
		         Macro143_Entry1_DelayMin, Macro143_Entry1_DelaySec, Macro143_Entry1_TimMin, Macro143_Entry1_TimSec, Macro143_Entry1_Protocol, 0, 0, 0, 0,
		         Macro143_Entry2_DelayMin, Macro143_Entry2_DelaySec, Macro143_Entry2_TimMin, Macro143_Entry2_TimSec, Macro143_Entry2_Protocol, 0, 0, 0, 0,
		         Macro143_Entry3_DelayMin, Macro143_Entry3_DelaySec, Macro143_Entry3_TimMin, Macro143_Entry3_TimSec, Macro143_Entry3_Protocol, 0, 0, 0, 0,
		         Macro143_Entry4_DelayMin, Macro143_Entry4_DelaySec, Macro143_Entry4_TimMin, Macro143_Entry4_TimSec, Macro143_Entry4_Protocol, 0, 0, 0, 0,
		         Macro143_Entry5_DelayMin, Macro143_Entry5_DelaySec, Macro143_Entry5_TimMin, Macro143_Entry5_TimSec, Macro143_Entry5_Protocol, 0, 0, 0, 0,
		         Macro143_Entry6_DelayMin, Macro143_Entry6_DelaySec, Macro143_Entry6_TimMin, Macro143_Entry6_TimSec, Macro143_Entry6_Protocol, 0, 0, 0, 0,
		         Macro143_Entry7_DelayMin, Macro143_Entry7_DelaySec, Macro143_Entry7_TimMin, Macro143_Entry7_TimSec, Macro143_Entry7_Protocol, 0, 0, 0, 0,
		         Macro143_Entry8_DelayMin, Macro143_Entry8_DelaySec, Macro143_Entry8_TimMin, Macro143_Entry8_TimSec, Macro143_Entry8_Protocol, 0, 0, 0, 0,
		         Macro143_Entry9_DelayMin, Macro143_Entry9_DelaySec, Macro143_Entry9_TimMin, Macro143_Entry9_TimSec, Macro143_Entry9_Protocol, 0, 0, 0, 0,
		         Macro143_Entry10_DelayMin, Macro143_Entry10_DelaySec, Macro143_Entry10_TimMin, Macro143_Entry10_TimSec, Macro143_Entry10_Protocol, 0, 0, 0, 0,
		         Macro143_Entry11_DelayMin, Macro143_Entry11_DelaySec, Macro143_Entry11_TimMin, Macro143_Entry11_TimSec, Macro143_Entry11_Protocol, 0, 0, 0, 0,
		         Macro143_Entry12_DelayMin, Macro143_Entry12_DelaySec, Macro143_Entry12_TimMin, Macro143_Entry12_TimSec, Macro143_Entry12_Protocol, 0, 0, 0, 0,
		         Macro143_Entry13_DelayMin, Macro143_Entry13_DelaySec, Macro143_Entry13_TimMin, Macro143_Entry13_TimSec, Macro143_Entry13_Protocol, 0, 0, 0, 0,
		         Macro143_Entry14_DelayMin, Macro143_Entry14_DelaySec, Macro143_Entry14_TimMin, Macro143_Entry14_TimSec, Macro143_Entry14_Protocol, 0, 0, 0, 0,
		         Macro143_Entry15_DelayMin, Macro143_Entry15_DelaySec, Macro143_Entry15_TimMin, Macro143_Entry15_TimSec, Macro143_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR143_STRING};

const struct super_macro Macro144 = {Macro144_NumEntries,
		         Macro144_Entry1_DelayMin, Macro144_Entry1_DelaySec, Macro144_Entry1_TimMin, Macro144_Entry1_TimSec, Macro144_Entry1_Protocol, 0, 0, 0, 0,
		         Macro144_Entry2_DelayMin, Macro144_Entry2_DelaySec, Macro144_Entry2_TimMin, Macro144_Entry2_TimSec, Macro144_Entry2_Protocol, 0, 0, 0, 0,
		         Macro144_Entry3_DelayMin, Macro144_Entry3_DelaySec, Macro144_Entry3_TimMin, Macro144_Entry3_TimSec, Macro144_Entry3_Protocol, 0, 0, 0, 0,
		         Macro144_Entry4_DelayMin, Macro144_Entry4_DelaySec, Macro144_Entry4_TimMin, Macro144_Entry4_TimSec, Macro144_Entry4_Protocol, 0, 0, 0, 0,
		         Macro144_Entry5_DelayMin, Macro144_Entry5_DelaySec, Macro144_Entry5_TimMin, Macro144_Entry5_TimSec, Macro144_Entry5_Protocol, 0, 0, 0, 0,
		         Macro144_Entry6_DelayMin, Macro144_Entry6_DelaySec, Macro144_Entry6_TimMin, Macro144_Entry6_TimSec, Macro144_Entry6_Protocol, 0, 0, 0, 0,
		         Macro144_Entry7_DelayMin, Macro144_Entry7_DelaySec, Macro144_Entry7_TimMin, Macro144_Entry7_TimSec, Macro144_Entry7_Protocol, 0, 0, 0, 0,
		         Macro144_Entry8_DelayMin, Macro144_Entry8_DelaySec, Macro144_Entry8_TimMin, Macro144_Entry8_TimSec, Macro144_Entry8_Protocol, 0, 0, 0, 0,
		         Macro144_Entry9_DelayMin, Macro144_Entry9_DelaySec, Macro144_Entry9_TimMin, Macro144_Entry9_TimSec, Macro144_Entry9_Protocol, 0, 0, 0, 0,
		         Macro144_Entry10_DelayMin, Macro144_Entry10_DelaySec, Macro144_Entry10_TimMin, Macro144_Entry10_TimSec, Macro144_Entry10_Protocol, 0, 0, 0, 0,
		         Macro144_Entry11_DelayMin, Macro144_Entry11_DelaySec, Macro144_Entry11_TimMin, Macro144_Entry11_TimSec, Macro144_Entry11_Protocol, 0, 0, 0, 0,
		         Macro144_Entry12_DelayMin, Macro144_Entry12_DelaySec, Macro144_Entry12_TimMin, Macro144_Entry12_TimSec, Macro144_Entry12_Protocol, 0, 0, 0, 0,
		         Macro144_Entry13_DelayMin, Macro144_Entry13_DelaySec, Macro144_Entry13_TimMin, Macro144_Entry13_TimSec, Macro144_Entry13_Protocol, 0, 0, 0, 0,
		         Macro144_Entry14_DelayMin, Macro144_Entry14_DelaySec, Macro144_Entry14_TimMin, Macro144_Entry14_TimSec, Macro144_Entry14_Protocol, 0, 0, 0, 0,
		         Macro144_Entry15_DelayMin, Macro144_Entry15_DelaySec, Macro144_Entry15_TimMin, Macro144_Entry15_TimSec, Macro144_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR144_STRING};

const struct super_macro Macro145 = {Macro145_NumEntries,
		         Macro145_Entry1_DelayMin, Macro145_Entry1_DelaySec, Macro145_Entry1_TimMin, Macro145_Entry1_TimSec, Macro145_Entry1_Protocol, 0, 0, 0, 0,
		         Macro145_Entry2_DelayMin, Macro145_Entry2_DelaySec, Macro145_Entry2_TimMin, Macro145_Entry2_TimSec, Macro145_Entry2_Protocol, 0, 0, 0, 0,
		         Macro145_Entry3_DelayMin, Macro145_Entry3_DelaySec, Macro145_Entry3_TimMin, Macro145_Entry3_TimSec, Macro145_Entry3_Protocol, 0, 0, 0, 0,
		         Macro145_Entry4_DelayMin, Macro145_Entry4_DelaySec, Macro145_Entry4_TimMin, Macro145_Entry4_TimSec, Macro145_Entry4_Protocol, 0, 0, 0, 0,
		         Macro145_Entry5_DelayMin, Macro145_Entry5_DelaySec, Macro145_Entry5_TimMin, Macro145_Entry5_TimSec, Macro145_Entry5_Protocol, 0, 0, 0, 0,
		         Macro145_Entry6_DelayMin, Macro145_Entry6_DelaySec, Macro145_Entry6_TimMin, Macro145_Entry6_TimSec, Macro145_Entry6_Protocol, 0, 0, 0, 0,
		         Macro145_Entry7_DelayMin, Macro145_Entry7_DelaySec, Macro145_Entry7_TimMin, Macro145_Entry7_TimSec, Macro145_Entry7_Protocol, 0, 0, 0, 0,
		         Macro145_Entry8_DelayMin, Macro145_Entry8_DelaySec, Macro145_Entry8_TimMin, Macro145_Entry8_TimSec, Macro145_Entry8_Protocol, 0, 0, 0, 0,
		         Macro145_Entry9_DelayMin, Macro145_Entry9_DelaySec, Macro145_Entry9_TimMin, Macro145_Entry9_TimSec, Macro145_Entry9_Protocol, 0, 0, 0, 0,
		         Macro145_Entry10_DelayMin, Macro145_Entry10_DelaySec, Macro145_Entry10_TimMin, Macro145_Entry10_TimSec, Macro145_Entry10_Protocol, 0, 0, 0, 0,
		         Macro145_Entry11_DelayMin, Macro145_Entry11_DelaySec, Macro145_Entry11_TimMin, Macro145_Entry11_TimSec, Macro145_Entry11_Protocol, 0, 0, 0, 0,
		         Macro145_Entry12_DelayMin, Macro145_Entry12_DelaySec, Macro145_Entry12_TimMin, Macro145_Entry12_TimSec, Macro145_Entry12_Protocol, 0, 0, 0, 0,
		         Macro145_Entry13_DelayMin, Macro145_Entry13_DelaySec, Macro145_Entry13_TimMin, Macro145_Entry13_TimSec, Macro145_Entry13_Protocol, 0, 0, 0, 0,
		         Macro145_Entry14_DelayMin, Macro145_Entry14_DelaySec, Macro145_Entry14_TimMin, Macro145_Entry14_TimSec, Macro145_Entry14_Protocol, 0, 0, 0, 0,
		         Macro145_Entry15_DelayMin, Macro145_Entry15_DelaySec, Macro145_Entry15_TimMin, Macro145_Entry15_TimSec, Macro145_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR145_STRING};

const struct super_macro Macro146 = {Macro146_NumEntries,
		         Macro146_Entry1_DelayMin, Macro146_Entry1_DelaySec, Macro146_Entry1_TimMin, Macro146_Entry1_TimSec, Macro146_Entry1_Protocol, 0, 0, 0, 0,
		         Macro146_Entry2_DelayMin, Macro146_Entry2_DelaySec, Macro146_Entry2_TimMin, Macro146_Entry2_TimSec, Macro146_Entry2_Protocol, 0, 0, 0, 0,
		         Macro146_Entry3_DelayMin, Macro146_Entry3_DelaySec, Macro146_Entry3_TimMin, Macro146_Entry3_TimSec, Macro146_Entry3_Protocol, 0, 0, 0, 0,
		         Macro146_Entry4_DelayMin, Macro146_Entry4_DelaySec, Macro146_Entry4_TimMin, Macro146_Entry4_TimSec, Macro146_Entry4_Protocol, 0, 0, 0, 0,
		         Macro146_Entry5_DelayMin, Macro146_Entry5_DelaySec, Macro146_Entry5_TimMin, Macro146_Entry5_TimSec, Macro146_Entry5_Protocol, 0, 0, 0, 0,
		         Macro146_Entry6_DelayMin, Macro146_Entry6_DelaySec, Macro146_Entry6_TimMin, Macro146_Entry6_TimSec, Macro146_Entry6_Protocol, 0, 0, 0, 0,
		         Macro146_Entry7_DelayMin, Macro146_Entry7_DelaySec, Macro146_Entry7_TimMin, Macro146_Entry7_TimSec, Macro146_Entry7_Protocol, 0, 0, 0, 0,
		         Macro146_Entry8_DelayMin, Macro146_Entry8_DelaySec, Macro146_Entry8_TimMin, Macro146_Entry8_TimSec, Macro146_Entry8_Protocol, 0, 0, 0, 0,
		         Macro146_Entry9_DelayMin, Macro146_Entry9_DelaySec, Macro146_Entry9_TimMin, Macro146_Entry9_TimSec, Macro146_Entry9_Protocol, 0, 0, 0, 0,
		         Macro146_Entry10_DelayMin, Macro146_Entry10_DelaySec, Macro146_Entry10_TimMin, Macro146_Entry10_TimSec, Macro146_Entry10_Protocol, 0, 0, 0, 0,
		         Macro146_Entry11_DelayMin, Macro146_Entry11_DelaySec, Macro146_Entry11_TimMin, Macro146_Entry11_TimSec, Macro146_Entry11_Protocol, 0, 0, 0, 0,
		         Macro146_Entry12_DelayMin, Macro146_Entry12_DelaySec, Macro146_Entry12_TimMin, Macro146_Entry12_TimSec, Macro146_Entry12_Protocol, 0, 0, 0, 0,
		         Macro146_Entry13_DelayMin, Macro146_Entry13_DelaySec, Macro146_Entry13_TimMin, Macro146_Entry13_TimSec, Macro146_Entry13_Protocol, 0, 0, 0, 0,
		         Macro146_Entry14_DelayMin, Macro146_Entry14_DelaySec, Macro146_Entry14_TimMin, Macro146_Entry14_TimSec, Macro146_Entry14_Protocol, 0, 0, 0, 0,
		         Macro146_Entry15_DelayMin, Macro146_Entry15_DelaySec, Macro146_Entry15_TimMin, Macro146_Entry15_TimSec, Macro146_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR146_STRING};

const struct super_macro Macro147 = {Macro147_NumEntries,
		         Macro147_Entry1_DelayMin, Macro147_Entry1_DelaySec, Macro147_Entry1_TimMin, Macro147_Entry1_TimSec, Macro147_Entry1_Protocol, 0, 0, 0, 0,
		         Macro147_Entry2_DelayMin, Macro147_Entry2_DelaySec, Macro147_Entry2_TimMin, Macro147_Entry2_TimSec, Macro147_Entry2_Protocol, 0, 0, 0, 0,
		         Macro147_Entry3_DelayMin, Macro147_Entry3_DelaySec, Macro147_Entry3_TimMin, Macro147_Entry3_TimSec, Macro147_Entry3_Protocol, 0, 0, 0, 0,
		         Macro147_Entry4_DelayMin, Macro147_Entry4_DelaySec, Macro147_Entry4_TimMin, Macro147_Entry4_TimSec, Macro147_Entry4_Protocol, 0, 0, 0, 0,
		         Macro147_Entry5_DelayMin, Macro147_Entry5_DelaySec, Macro147_Entry5_TimMin, Macro147_Entry5_TimSec, Macro147_Entry5_Protocol, 0, 0, 0, 0,
		         Macro147_Entry6_DelayMin, Macro147_Entry6_DelaySec, Macro147_Entry6_TimMin, Macro147_Entry6_TimSec, Macro147_Entry6_Protocol, 0, 0, 0, 0,
		         Macro147_Entry7_DelayMin, Macro147_Entry7_DelaySec, Macro147_Entry7_TimMin, Macro147_Entry7_TimSec, Macro147_Entry7_Protocol, 0, 0, 0, 0,
		         Macro147_Entry8_DelayMin, Macro147_Entry8_DelaySec, Macro147_Entry8_TimMin, Macro147_Entry8_TimSec, Macro147_Entry8_Protocol, 0, 0, 0, 0,
		         Macro147_Entry9_DelayMin, Macro147_Entry9_DelaySec, Macro147_Entry9_TimMin, Macro147_Entry9_TimSec, Macro147_Entry9_Protocol, 0, 0, 0, 0,
		         Macro147_Entry10_DelayMin, Macro147_Entry10_DelaySec, Macro147_Entry10_TimMin, Macro147_Entry10_TimSec, Macro147_Entry10_Protocol, 0, 0, 0, 0,
		         Macro147_Entry11_DelayMin, Macro147_Entry11_DelaySec, Macro147_Entry11_TimMin, Macro147_Entry11_TimSec, Macro147_Entry11_Protocol, 0, 0, 0, 0,
		         Macro147_Entry12_DelayMin, Macro147_Entry12_DelaySec, Macro147_Entry12_TimMin, Macro147_Entry12_TimSec, Macro147_Entry12_Protocol, 0, 0, 0, 0,
		         Macro147_Entry13_DelayMin, Macro147_Entry13_DelaySec, Macro147_Entry13_TimMin, Macro147_Entry13_TimSec, Macro147_Entry13_Protocol, 0, 0, 0, 0,
		         Macro147_Entry14_DelayMin, Macro147_Entry14_DelaySec, Macro147_Entry14_TimMin, Macro147_Entry14_TimSec, Macro147_Entry14_Protocol, 0, 0, 0, 0,
		         Macro147_Entry15_DelayMin, Macro147_Entry15_DelaySec, Macro147_Entry15_TimMin, Macro147_Entry15_TimSec, Macro147_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR147_STRING};

const struct super_macro Macro148 = {Macro148_NumEntries,
		         Macro148_Entry1_DelayMin, Macro148_Entry1_DelaySec, Macro148_Entry1_TimMin, Macro148_Entry1_TimSec, Macro148_Entry1_Protocol, 0, 0, 0, 0,
		         Macro148_Entry2_DelayMin, Macro148_Entry2_DelaySec, Macro148_Entry2_TimMin, Macro148_Entry2_TimSec, Macro148_Entry2_Protocol, 0, 0, 0, 0,
		         Macro148_Entry3_DelayMin, Macro148_Entry3_DelaySec, Macro148_Entry3_TimMin, Macro148_Entry3_TimSec, Macro148_Entry3_Protocol, 0, 0, 0, 0,
		         Macro148_Entry4_DelayMin, Macro148_Entry4_DelaySec, Macro148_Entry4_TimMin, Macro148_Entry4_TimSec, Macro148_Entry4_Protocol, 0, 0, 0, 0,
		         Macro148_Entry5_DelayMin, Macro148_Entry5_DelaySec, Macro148_Entry5_TimMin, Macro148_Entry5_TimSec, Macro148_Entry5_Protocol, 0, 0, 0, 0,
		         Macro148_Entry6_DelayMin, Macro148_Entry6_DelaySec, Macro148_Entry6_TimMin, Macro148_Entry6_TimSec, Macro148_Entry6_Protocol, 0, 0, 0, 0,
		         Macro148_Entry7_DelayMin, Macro148_Entry7_DelaySec, Macro148_Entry7_TimMin, Macro148_Entry7_TimSec, Macro148_Entry7_Protocol, 0, 0, 0, 0,
		         Macro148_Entry8_DelayMin, Macro148_Entry8_DelaySec, Macro148_Entry8_TimMin, Macro148_Entry8_TimSec, Macro148_Entry8_Protocol, 0, 0, 0, 0,
		         Macro148_Entry9_DelayMin, Macro148_Entry9_DelaySec, Macro148_Entry9_TimMin, Macro148_Entry9_TimSec, Macro148_Entry9_Protocol, 0, 0, 0, 0,
		         Macro148_Entry10_DelayMin, Macro148_Entry10_DelaySec, Macro148_Entry10_TimMin, Macro148_Entry10_TimSec, Macro148_Entry10_Protocol, 0, 0, 0, 0,
		         Macro148_Entry11_DelayMin, Macro148_Entry11_DelaySec, Macro148_Entry11_TimMin, Macro148_Entry11_TimSec, Macro148_Entry11_Protocol, 0, 0, 0, 0,
		         Macro148_Entry12_DelayMin, Macro148_Entry12_DelaySec, Macro148_Entry12_TimMin, Macro148_Entry12_TimSec, Macro148_Entry12_Protocol, 0, 0, 0, 0,
		         Macro148_Entry13_DelayMin, Macro148_Entry13_DelaySec, Macro148_Entry13_TimMin, Macro148_Entry13_TimSec, Macro148_Entry13_Protocol, 0, 0, 0, 0,
		         Macro148_Entry14_DelayMin, Macro148_Entry14_DelaySec, Macro148_Entry14_TimMin, Macro148_Entry14_TimSec, Macro148_Entry14_Protocol, 0, 0, 0, 0,
		         Macro148_Entry15_DelayMin, Macro148_Entry15_DelaySec, Macro148_Entry15_TimMin, Macro148_Entry15_TimSec, Macro148_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR148_STRING};

const struct super_macro Macro149 = {Macro149_NumEntries,
		         Macro149_Entry1_DelayMin, Macro149_Entry1_DelaySec, Macro149_Entry1_TimMin, Macro149_Entry1_TimSec, Macro149_Entry1_Protocol, 0, 0, 0, 0,
		         Macro149_Entry2_DelayMin, Macro149_Entry2_DelaySec, Macro149_Entry2_TimMin, Macro149_Entry2_TimSec, Macro149_Entry2_Protocol, 0, 0, 0, 0,
		         Macro149_Entry3_DelayMin, Macro149_Entry3_DelaySec, Macro149_Entry3_TimMin, Macro149_Entry3_TimSec, Macro149_Entry3_Protocol, 0, 0, 0, 0,
		         Macro149_Entry4_DelayMin, Macro149_Entry4_DelaySec, Macro149_Entry4_TimMin, Macro149_Entry4_TimSec, Macro149_Entry4_Protocol, 0, 0, 0, 0,
		         Macro149_Entry5_DelayMin, Macro149_Entry5_DelaySec, Macro149_Entry5_TimMin, Macro149_Entry5_TimSec, Macro149_Entry5_Protocol, 0, 0, 0, 0,
		         Macro149_Entry6_DelayMin, Macro149_Entry6_DelaySec, Macro149_Entry6_TimMin, Macro149_Entry6_TimSec, Macro149_Entry6_Protocol, 0, 0, 0, 0,
		         Macro149_Entry7_DelayMin, Macro149_Entry7_DelaySec, Macro149_Entry7_TimMin, Macro149_Entry7_TimSec, Macro149_Entry7_Protocol, 0, 0, 0, 0,
		         Macro149_Entry8_DelayMin, Macro149_Entry8_DelaySec, Macro149_Entry8_TimMin, Macro149_Entry8_TimSec, Macro149_Entry8_Protocol, 0, 0, 0, 0,
		         Macro149_Entry9_DelayMin, Macro149_Entry9_DelaySec, Macro149_Entry9_TimMin, Macro149_Entry9_TimSec, Macro149_Entry9_Protocol, 0, 0, 0, 0,
		         Macro149_Entry10_DelayMin, Macro149_Entry10_DelaySec, Macro149_Entry10_TimMin, Macro149_Entry10_TimSec, Macro149_Entry10_Protocol, 0, 0, 0, 0,
		         Macro149_Entry11_DelayMin, Macro149_Entry11_DelaySec, Macro149_Entry11_TimMin, Macro149_Entry11_TimSec, Macro149_Entry11_Protocol, 0, 0, 0, 0,
		         Macro149_Entry12_DelayMin, Macro149_Entry12_DelaySec, Macro149_Entry12_TimMin, Macro149_Entry12_TimSec, Macro149_Entry12_Protocol, 0, 0, 0, 0,
		         Macro149_Entry13_DelayMin, Macro149_Entry13_DelaySec, Macro149_Entry13_TimMin, Macro149_Entry13_TimSec, Macro149_Entry13_Protocol, 0, 0, 0, 0,
		         Macro149_Entry14_DelayMin, Macro149_Entry14_DelaySec, Macro149_Entry14_TimMin, Macro149_Entry14_TimSec, Macro149_Entry14_Protocol, 0, 0, 0, 0,
		         Macro149_Entry15_DelayMin, Macro149_Entry15_DelaySec, Macro149_Entry15_TimMin, Macro149_Entry15_TimSec, Macro149_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR149_STRING};

const struct super_macro Macro150 = {Macro150_NumEntries,
		         Macro150_Entry1_DelayMin, Macro150_Entry1_DelaySec, Macro150_Entry1_TimMin, Macro150_Entry1_TimSec, Macro150_Entry1_Protocol, 0, 0, 0, 0,
		         Macro150_Entry2_DelayMin, Macro150_Entry2_DelaySec, Macro150_Entry2_TimMin, Macro150_Entry2_TimSec, Macro150_Entry2_Protocol, 0, 0, 0, 0,
		         Macro150_Entry3_DelayMin, Macro150_Entry3_DelaySec, Macro150_Entry3_TimMin, Macro150_Entry3_TimSec, Macro150_Entry3_Protocol, 0, 0, 0, 0,
		         Macro150_Entry4_DelayMin, Macro150_Entry4_DelaySec, Macro150_Entry4_TimMin, Macro150_Entry4_TimSec, Macro150_Entry4_Protocol, 0, 0, 0, 0,
		         Macro150_Entry5_DelayMin, Macro150_Entry5_DelaySec, Macro150_Entry5_TimMin, Macro150_Entry5_TimSec, Macro150_Entry5_Protocol, 0, 0, 0, 0,
		         Macro150_Entry6_DelayMin, Macro150_Entry6_DelaySec, Macro150_Entry6_TimMin, Macro150_Entry6_TimSec, Macro150_Entry6_Protocol, 0, 0, 0, 0,
		         Macro150_Entry7_DelayMin, Macro150_Entry7_DelaySec, Macro150_Entry7_TimMin, Macro150_Entry7_TimSec, Macro150_Entry7_Protocol, 0, 0, 0, 0,
		         Macro150_Entry8_DelayMin, Macro150_Entry8_DelaySec, Macro150_Entry8_TimMin, Macro150_Entry8_TimSec, Macro150_Entry8_Protocol, 0, 0, 0, 0,
		         Macro150_Entry9_DelayMin, Macro150_Entry9_DelaySec, Macro150_Entry9_TimMin, Macro150_Entry9_TimSec, Macro150_Entry9_Protocol, 0, 0, 0, 0,
		         Macro150_Entry10_DelayMin, Macro150_Entry10_DelaySec, Macro150_Entry10_TimMin, Macro150_Entry10_TimSec, Macro150_Entry10_Protocol, 0, 0, 0, 0,
		         Macro150_Entry11_DelayMin, Macro150_Entry11_DelaySec, Macro150_Entry11_TimMin, Macro150_Entry11_TimSec, Macro150_Entry11_Protocol, 0, 0, 0, 0,
		         Macro150_Entry12_DelayMin, Macro150_Entry12_DelaySec, Macro150_Entry12_TimMin, Macro150_Entry12_TimSec, Macro150_Entry12_Protocol, 0, 0, 0, 0,
		         Macro150_Entry13_DelayMin, Macro150_Entry13_DelaySec, Macro150_Entry13_TimMin, Macro150_Entry13_TimSec, Macro150_Entry13_Protocol, 0, 0, 0, 0,
		         Macro150_Entry14_DelayMin, Macro150_Entry14_DelaySec, Macro150_Entry14_TimMin, Macro150_Entry14_TimSec, Macro150_Entry14_Protocol, 0, 0, 0, 0,
		         Macro150_Entry15_DelayMin, Macro150_Entry15_DelaySec, Macro150_Entry15_TimMin, Macro150_Entry15_TimSec, Macro150_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR150_STRING};

const struct super_macro Macro151 = {Macro151_NumEntries,
		         Macro151_Entry1_DelayMin, Macro151_Entry1_DelaySec, Macro151_Entry1_TimMin, Macro151_Entry1_TimSec, Macro151_Entry1_Protocol, 0, 0, 0, 0,
		         Macro151_Entry2_DelayMin, Macro151_Entry2_DelaySec, Macro151_Entry2_TimMin, Macro151_Entry2_TimSec, Macro151_Entry2_Protocol, 0, 0, 0, 0,
		         Macro151_Entry3_DelayMin, Macro151_Entry3_DelaySec, Macro151_Entry3_TimMin, Macro151_Entry3_TimSec, Macro151_Entry3_Protocol, 0, 0, 0, 0,
		         Macro151_Entry4_DelayMin, Macro151_Entry4_DelaySec, Macro151_Entry4_TimMin, Macro151_Entry4_TimSec, Macro151_Entry4_Protocol, 0, 0, 0, 0,
		         Macro151_Entry5_DelayMin, Macro151_Entry5_DelaySec, Macro151_Entry5_TimMin, Macro151_Entry5_TimSec, Macro151_Entry5_Protocol, 0, 0, 0, 0,
		         Macro151_Entry6_DelayMin, Macro151_Entry6_DelaySec, Macro151_Entry6_TimMin, Macro151_Entry6_TimSec, Macro151_Entry6_Protocol, 0, 0, 0, 0,
		         Macro151_Entry7_DelayMin, Macro151_Entry7_DelaySec, Macro151_Entry7_TimMin, Macro151_Entry7_TimSec, Macro151_Entry7_Protocol, 0, 0, 0, 0,
		         Macro151_Entry8_DelayMin, Macro151_Entry8_DelaySec, Macro151_Entry8_TimMin, Macro151_Entry8_TimSec, Macro151_Entry8_Protocol, 0, 0, 0, 0,
		         Macro151_Entry9_DelayMin, Macro151_Entry9_DelaySec, Macro151_Entry9_TimMin, Macro151_Entry9_TimSec, Macro151_Entry9_Protocol, 0, 0, 0, 0,
		         Macro151_Entry10_DelayMin, Macro151_Entry10_DelaySec, Macro151_Entry10_TimMin, Macro151_Entry10_TimSec, Macro151_Entry10_Protocol, 0, 0, 0, 0,
		         Macro151_Entry11_DelayMin, Macro151_Entry11_DelaySec, Macro151_Entry11_TimMin, Macro151_Entry11_TimSec, Macro151_Entry11_Protocol, 0, 0, 0, 0,
		         Macro151_Entry12_DelayMin, Macro151_Entry12_DelaySec, Macro151_Entry12_TimMin, Macro151_Entry12_TimSec, Macro151_Entry12_Protocol, 0, 0, 0, 0,
		         Macro151_Entry13_DelayMin, Macro151_Entry13_DelaySec, Macro151_Entry13_TimMin, Macro151_Entry13_TimSec, Macro151_Entry13_Protocol, 0, 0, 0, 0,
		         Macro151_Entry14_DelayMin, Macro151_Entry14_DelaySec, Macro151_Entry14_TimMin, Macro151_Entry14_TimSec, Macro151_Entry14_Protocol, 0, 0, 0, 0,
		         Macro151_Entry15_DelayMin, Macro151_Entry15_DelaySec, Macro151_Entry15_TimMin, Macro151_Entry15_TimSec, Macro151_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR151_STRING};

const struct super_macro Macro152 = {Macro152_NumEntries,
		         Macro152_Entry1_DelayMin, Macro152_Entry1_DelaySec, Macro152_Entry1_TimMin, Macro152_Entry1_TimSec, Macro152_Entry1_Protocol, 0, 0, 0, 0,
		         Macro152_Entry2_DelayMin, Macro152_Entry2_DelaySec, Macro152_Entry2_TimMin, Macro152_Entry2_TimSec, Macro152_Entry2_Protocol, 0, 0, 0, 0,
		         Macro152_Entry3_DelayMin, Macro152_Entry3_DelaySec, Macro152_Entry3_TimMin, Macro152_Entry3_TimSec, Macro152_Entry3_Protocol, 0, 0, 0, 0,
		         Macro152_Entry4_DelayMin, Macro152_Entry4_DelaySec, Macro152_Entry4_TimMin, Macro152_Entry4_TimSec, Macro152_Entry4_Protocol, 0, 0, 0, 0,
		         Macro152_Entry5_DelayMin, Macro152_Entry5_DelaySec, Macro152_Entry5_TimMin, Macro152_Entry5_TimSec, Macro152_Entry5_Protocol, 0, 0, 0, 0,
		         Macro152_Entry6_DelayMin, Macro152_Entry6_DelaySec, Macro152_Entry6_TimMin, Macro152_Entry6_TimSec, Macro152_Entry6_Protocol, 0, 0, 0, 0,
		         Macro152_Entry7_DelayMin, Macro152_Entry7_DelaySec, Macro152_Entry7_TimMin, Macro152_Entry7_TimSec, Macro152_Entry7_Protocol, 0, 0, 0, 0,
		         Macro152_Entry8_DelayMin, Macro152_Entry8_DelaySec, Macro152_Entry8_TimMin, Macro152_Entry8_TimSec, Macro152_Entry8_Protocol, 0, 0, 0, 0,
		         Macro152_Entry9_DelayMin, Macro152_Entry9_DelaySec, Macro152_Entry9_TimMin, Macro152_Entry9_TimSec, Macro152_Entry9_Protocol, 0, 0, 0, 0,
		         Macro152_Entry10_DelayMin, Macro152_Entry10_DelaySec, Macro152_Entry10_TimMin, Macro152_Entry10_TimSec, Macro152_Entry10_Protocol, 0, 0, 0, 0,
		         Macro152_Entry11_DelayMin, Macro152_Entry11_DelaySec, Macro152_Entry11_TimMin, Macro152_Entry11_TimSec, Macro152_Entry11_Protocol, 0, 0, 0, 0,
		         Macro152_Entry12_DelayMin, Macro152_Entry12_DelaySec, Macro152_Entry12_TimMin, Macro152_Entry12_TimSec, Macro152_Entry12_Protocol, 0, 0, 0, 0,
		         Macro152_Entry13_DelayMin, Macro152_Entry13_DelaySec, Macro152_Entry13_TimMin, Macro152_Entry13_TimSec, Macro152_Entry13_Protocol, 0, 0, 0, 0,
		         Macro152_Entry14_DelayMin, Macro152_Entry14_DelaySec, Macro152_Entry14_TimMin, Macro152_Entry14_TimSec, Macro152_Entry14_Protocol, 0, 0, 0, 0,
		         Macro152_Entry15_DelayMin, Macro152_Entry15_DelaySec, Macro152_Entry15_TimMin, Macro152_Entry15_TimSec, Macro152_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR152_STRING};

const struct super_macro Macro153 = {Macro153_NumEntries,
		         Macro153_Entry1_DelayMin, Macro153_Entry1_DelaySec, Macro153_Entry1_TimMin, Macro153_Entry1_TimSec, Macro153_Entry1_Protocol, 0, 0, 0, 0,
		         Macro153_Entry2_DelayMin, Macro153_Entry2_DelaySec, Macro153_Entry2_TimMin, Macro153_Entry2_TimSec, Macro153_Entry2_Protocol, 0, 0, 0, 0,
		         Macro153_Entry3_DelayMin, Macro153_Entry3_DelaySec, Macro153_Entry3_TimMin, Macro153_Entry3_TimSec, Macro153_Entry3_Protocol, 0, 0, 0, 0,
		         Macro153_Entry4_DelayMin, Macro153_Entry4_DelaySec, Macro153_Entry4_TimMin, Macro153_Entry4_TimSec, Macro153_Entry4_Protocol, 0, 0, 0, 0,
		         Macro153_Entry5_DelayMin, Macro153_Entry5_DelaySec, Macro153_Entry5_TimMin, Macro153_Entry5_TimSec, Macro153_Entry5_Protocol, 0, 0, 0, 0,
		         Macro153_Entry6_DelayMin, Macro153_Entry6_DelaySec, Macro153_Entry6_TimMin, Macro153_Entry6_TimSec, Macro153_Entry6_Protocol, 0, 0, 0, 0,
		         Macro153_Entry7_DelayMin, Macro153_Entry7_DelaySec, Macro153_Entry7_TimMin, Macro153_Entry7_TimSec, Macro153_Entry7_Protocol, 0, 0, 0, 0,
		         Macro153_Entry8_DelayMin, Macro153_Entry8_DelaySec, Macro153_Entry8_TimMin, Macro153_Entry8_TimSec, Macro153_Entry8_Protocol, 0, 0, 0, 0,
		         Macro153_Entry9_DelayMin, Macro153_Entry9_DelaySec, Macro153_Entry9_TimMin, Macro153_Entry9_TimSec, Macro153_Entry9_Protocol, 0, 0, 0, 0,
		         Macro153_Entry10_DelayMin, Macro153_Entry10_DelaySec, Macro153_Entry10_TimMin, Macro153_Entry10_TimSec, Macro153_Entry10_Protocol, 0, 0, 0, 0,
		         Macro153_Entry11_DelayMin, Macro153_Entry11_DelaySec, Macro153_Entry11_TimMin, Macro153_Entry11_TimSec, Macro153_Entry11_Protocol, 0, 0, 0, 0,
		         Macro153_Entry12_DelayMin, Macro153_Entry12_DelaySec, Macro153_Entry12_TimMin, Macro153_Entry12_TimSec, Macro153_Entry12_Protocol, 0, 0, 0, 0,
		         Macro153_Entry13_DelayMin, Macro153_Entry13_DelaySec, Macro153_Entry13_TimMin, Macro153_Entry13_TimSec, Macro153_Entry13_Protocol, 0, 0, 0, 0,
		         Macro153_Entry14_DelayMin, Macro153_Entry14_DelaySec, Macro153_Entry14_TimMin, Macro153_Entry14_TimSec, Macro153_Entry14_Protocol, 0, 0, 0, 0,
		         Macro153_Entry15_DelayMin, Macro153_Entry15_DelaySec, Macro153_Entry15_TimMin, Macro153_Entry15_TimSec, Macro153_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR153_STRING};

const struct super_macro Macro154 = {Macro154_NumEntries,
		         Macro154_Entry1_DelayMin, Macro154_Entry1_DelaySec, Macro154_Entry1_TimMin, Macro154_Entry1_TimSec, Macro154_Entry1_Protocol, 0, 0, 0, 0,
		         Macro154_Entry2_DelayMin, Macro154_Entry2_DelaySec, Macro154_Entry2_TimMin, Macro154_Entry2_TimSec, Macro154_Entry2_Protocol, 0, 0, 0, 0,
		         Macro154_Entry3_DelayMin, Macro154_Entry3_DelaySec, Macro154_Entry3_TimMin, Macro154_Entry3_TimSec, Macro154_Entry3_Protocol, 0, 0, 0, 0,
		         Macro154_Entry4_DelayMin, Macro154_Entry4_DelaySec, Macro154_Entry4_TimMin, Macro154_Entry4_TimSec, Macro154_Entry4_Protocol, 0, 0, 0, 0,
		         Macro154_Entry5_DelayMin, Macro154_Entry5_DelaySec, Macro154_Entry5_TimMin, Macro154_Entry5_TimSec, Macro154_Entry5_Protocol, 0, 0, 0, 0,
		         Macro154_Entry6_DelayMin, Macro154_Entry6_DelaySec, Macro154_Entry6_TimMin, Macro154_Entry6_TimSec, Macro154_Entry6_Protocol, 0, 0, 0, 0,
		         Macro154_Entry7_DelayMin, Macro154_Entry7_DelaySec, Macro154_Entry7_TimMin, Macro154_Entry7_TimSec, Macro154_Entry7_Protocol, 0, 0, 0, 0,
		         Macro154_Entry8_DelayMin, Macro154_Entry8_DelaySec, Macro154_Entry8_TimMin, Macro154_Entry8_TimSec, Macro154_Entry8_Protocol, 0, 0, 0, 0,
		         Macro154_Entry9_DelayMin, Macro154_Entry9_DelaySec, Macro154_Entry9_TimMin, Macro154_Entry9_TimSec, Macro154_Entry9_Protocol, 0, 0, 0, 0,
		         Macro154_Entry10_DelayMin, Macro154_Entry10_DelaySec, Macro154_Entry10_TimMin, Macro154_Entry10_TimSec, Macro154_Entry10_Protocol, 0, 0, 0, 0,
		         Macro154_Entry11_DelayMin, Macro154_Entry11_DelaySec, Macro154_Entry11_TimMin, Macro154_Entry11_TimSec, Macro154_Entry11_Protocol, 0, 0, 0, 0,
		         Macro154_Entry12_DelayMin, Macro154_Entry12_DelaySec, Macro154_Entry12_TimMin, Macro154_Entry12_TimSec, Macro154_Entry12_Protocol, 0, 0, 0, 0,
		         Macro154_Entry13_DelayMin, Macro154_Entry13_DelaySec, Macro154_Entry13_TimMin, Macro154_Entry13_TimSec, Macro154_Entry13_Protocol, 0, 0, 0, 0,
		         Macro154_Entry14_DelayMin, Macro154_Entry14_DelaySec, Macro154_Entry14_TimMin, Macro154_Entry14_TimSec, Macro154_Entry14_Protocol, 0, 0, 0, 0,
		         Macro154_Entry15_DelayMin, Macro154_Entry15_DelaySec, Macro154_Entry15_TimMin, Macro154_Entry15_TimSec, Macro154_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR154_STRING};

const struct super_macro Macro155 = {Macro155_NumEntries,
		         Macro155_Entry1_DelayMin, Macro155_Entry1_DelaySec, Macro155_Entry1_TimMin, Macro155_Entry1_TimSec, Macro155_Entry1_Protocol, 0, 0, 0, 0,
		         Macro155_Entry2_DelayMin, Macro155_Entry2_DelaySec, Macro155_Entry2_TimMin, Macro155_Entry2_TimSec, Macro155_Entry2_Protocol, 0, 0, 0, 0,
		         Macro155_Entry3_DelayMin, Macro155_Entry3_DelaySec, Macro155_Entry3_TimMin, Macro155_Entry3_TimSec, Macro155_Entry3_Protocol, 0, 0, 0, 0,
		         Macro155_Entry4_DelayMin, Macro155_Entry4_DelaySec, Macro155_Entry4_TimMin, Macro155_Entry4_TimSec, Macro155_Entry4_Protocol, 0, 0, 0, 0,
		         Macro155_Entry5_DelayMin, Macro155_Entry5_DelaySec, Macro155_Entry5_TimMin, Macro155_Entry5_TimSec, Macro155_Entry5_Protocol, 0, 0, 0, 0,
		         Macro155_Entry6_DelayMin, Macro155_Entry6_DelaySec, Macro155_Entry6_TimMin, Macro155_Entry6_TimSec, Macro155_Entry6_Protocol, 0, 0, 0, 0,
		         Macro155_Entry7_DelayMin, Macro155_Entry7_DelaySec, Macro155_Entry7_TimMin, Macro155_Entry7_TimSec, Macro155_Entry7_Protocol, 0, 0, 0, 0,
		         Macro155_Entry8_DelayMin, Macro155_Entry8_DelaySec, Macro155_Entry8_TimMin, Macro155_Entry8_TimSec, Macro155_Entry8_Protocol, 0, 0, 0, 0,
		         Macro155_Entry9_DelayMin, Macro155_Entry9_DelaySec, Macro155_Entry9_TimMin, Macro155_Entry9_TimSec, Macro155_Entry9_Protocol, 0, 0, 0, 0,
		         Macro155_Entry10_DelayMin, Macro155_Entry10_DelaySec, Macro155_Entry10_TimMin, Macro155_Entry10_TimSec, Macro155_Entry10_Protocol, 0, 0, 0, 0,
		         Macro155_Entry11_DelayMin, Macro155_Entry11_DelaySec, Macro155_Entry11_TimMin, Macro155_Entry11_TimSec, Macro155_Entry11_Protocol, 0, 0, 0, 0,
		         Macro155_Entry12_DelayMin, Macro155_Entry12_DelaySec, Macro155_Entry12_TimMin, Macro155_Entry12_TimSec, Macro155_Entry12_Protocol, 0, 0, 0, 0,
		         Macro155_Entry13_DelayMin, Macro155_Entry13_DelaySec, Macro155_Entry13_TimMin, Macro155_Entry13_TimSec, Macro155_Entry13_Protocol, 0, 0, 0, 0,
		         Macro155_Entry14_DelayMin, Macro155_Entry14_DelaySec, Macro155_Entry14_TimMin, Macro155_Entry14_TimSec, Macro155_Entry14_Protocol, 0, 0, 0, 0,
		         Macro155_Entry15_DelayMin, Macro155_Entry15_DelaySec, Macro155_Entry15_TimMin, Macro155_Entry15_TimSec, Macro155_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR155_STRING};

const struct super_macro Macro156 = {Macro156_NumEntries,
		         Macro156_Entry1_DelayMin, Macro156_Entry1_DelaySec, Macro156_Entry1_TimMin, Macro156_Entry1_TimSec, Macro156_Entry1_Protocol, 0, 0, 0, 0,
		         Macro156_Entry2_DelayMin, Macro156_Entry2_DelaySec, Macro156_Entry2_TimMin, Macro156_Entry2_TimSec, Macro156_Entry2_Protocol, 0, 0, 0, 0,
		         Macro156_Entry3_DelayMin, Macro156_Entry3_DelaySec, Macro156_Entry3_TimMin, Macro156_Entry3_TimSec, Macro156_Entry3_Protocol, 0, 0, 0, 0,
		         Macro156_Entry4_DelayMin, Macro156_Entry4_DelaySec, Macro156_Entry4_TimMin, Macro156_Entry4_TimSec, Macro156_Entry4_Protocol, 0, 0, 0, 0,
		         Macro156_Entry5_DelayMin, Macro156_Entry5_DelaySec, Macro156_Entry5_TimMin, Macro156_Entry5_TimSec, Macro156_Entry5_Protocol, 0, 0, 0, 0,
		         Macro156_Entry6_DelayMin, Macro156_Entry6_DelaySec, Macro156_Entry6_TimMin, Macro156_Entry6_TimSec, Macro156_Entry6_Protocol, 0, 0, 0, 0,
		         Macro156_Entry7_DelayMin, Macro156_Entry7_DelaySec, Macro156_Entry7_TimMin, Macro156_Entry7_TimSec, Macro156_Entry7_Protocol, 0, 0, 0, 0,
		         Macro156_Entry8_DelayMin, Macro156_Entry8_DelaySec, Macro156_Entry8_TimMin, Macro156_Entry8_TimSec, Macro156_Entry8_Protocol, 0, 0, 0, 0,
		         Macro156_Entry9_DelayMin, Macro156_Entry9_DelaySec, Macro156_Entry9_TimMin, Macro156_Entry9_TimSec, Macro156_Entry9_Protocol, 0, 0, 0, 0,
		         Macro156_Entry10_DelayMin, Macro156_Entry10_DelaySec, Macro156_Entry10_TimMin, Macro156_Entry10_TimSec, Macro156_Entry10_Protocol, 0, 0, 0, 0,
		         Macro156_Entry11_DelayMin, Macro156_Entry11_DelaySec, Macro156_Entry11_TimMin, Macro156_Entry11_TimSec, Macro156_Entry11_Protocol, 0, 0, 0, 0,
		         Macro156_Entry12_DelayMin, Macro156_Entry12_DelaySec, Macro156_Entry12_TimMin, Macro156_Entry12_TimSec, Macro156_Entry12_Protocol, 0, 0, 0, 0,
		         Macro156_Entry13_DelayMin, Macro156_Entry13_DelaySec, Macro156_Entry13_TimMin, Macro156_Entry13_TimSec, Macro156_Entry13_Protocol, 0, 0, 0, 0,
		         Macro156_Entry14_DelayMin, Macro156_Entry14_DelaySec, Macro156_Entry14_TimMin, Macro156_Entry14_TimSec, Macro156_Entry14_Protocol, 0, 0, 0, 0,
		         Macro156_Entry15_DelayMin, Macro156_Entry15_DelaySec, Macro156_Entry15_TimMin, Macro156_Entry15_TimSec, Macro156_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR156_STRING};

const struct super_macro Macro157 = {Macro157_NumEntries,
		         Macro157_Entry1_DelayMin, Macro157_Entry1_DelaySec, Macro157_Entry1_TimMin, Macro157_Entry1_TimSec, Macro157_Entry1_Protocol, 0, 0, 0, 0,
		         Macro157_Entry2_DelayMin, Macro157_Entry2_DelaySec, Macro157_Entry2_TimMin, Macro157_Entry2_TimSec, Macro157_Entry2_Protocol, 0, 0, 0, 0,
		         Macro157_Entry3_DelayMin, Macro157_Entry3_DelaySec, Macro157_Entry3_TimMin, Macro157_Entry3_TimSec, Macro157_Entry3_Protocol, 0, 0, 0, 0,
		         Macro157_Entry4_DelayMin, Macro157_Entry4_DelaySec, Macro157_Entry4_TimMin, Macro157_Entry4_TimSec, Macro157_Entry4_Protocol, 0, 0, 0, 0,
		         Macro157_Entry5_DelayMin, Macro157_Entry5_DelaySec, Macro157_Entry5_TimMin, Macro157_Entry5_TimSec, Macro157_Entry5_Protocol, 0, 0, 0, 0,
		         Macro157_Entry6_DelayMin, Macro157_Entry6_DelaySec, Macro157_Entry6_TimMin, Macro157_Entry6_TimSec, Macro157_Entry6_Protocol, 0, 0, 0, 0,
		         Macro157_Entry7_DelayMin, Macro157_Entry7_DelaySec, Macro157_Entry7_TimMin, Macro157_Entry7_TimSec, Macro157_Entry7_Protocol, 0, 0, 0, 0,
		         Macro157_Entry8_DelayMin, Macro157_Entry8_DelaySec, Macro157_Entry8_TimMin, Macro157_Entry8_TimSec, Macro157_Entry8_Protocol, 0, 0, 0, 0,
		         Macro157_Entry9_DelayMin, Macro157_Entry9_DelaySec, Macro157_Entry9_TimMin, Macro157_Entry9_TimSec, Macro157_Entry9_Protocol, 0, 0, 0, 0,
		         Macro157_Entry10_DelayMin, Macro157_Entry10_DelaySec, Macro157_Entry10_TimMin, Macro157_Entry10_TimSec, Macro157_Entry10_Protocol, 0, 0, 0, 0,
		         Macro157_Entry11_DelayMin, Macro157_Entry11_DelaySec, Macro157_Entry11_TimMin, Macro157_Entry11_TimSec, Macro157_Entry11_Protocol, 0, 0, 0, 0,
		         Macro157_Entry12_DelayMin, Macro157_Entry12_DelaySec, Macro157_Entry12_TimMin, Macro157_Entry12_TimSec, Macro157_Entry12_Protocol, 0, 0, 0, 0,
		         Macro157_Entry13_DelayMin, Macro157_Entry13_DelaySec, Macro157_Entry13_TimMin, Macro157_Entry13_TimSec, Macro157_Entry13_Protocol, 0, 0, 0, 0,
		         Macro157_Entry14_DelayMin, Macro157_Entry14_DelaySec, Macro157_Entry14_TimMin, Macro157_Entry14_TimSec, Macro157_Entry14_Protocol, 0, 0, 0, 0,
		         Macro157_Entry15_DelayMin, Macro157_Entry15_DelaySec, Macro157_Entry15_TimMin, Macro157_Entry15_TimSec, Macro157_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR157_STRING};

const struct super_macro Macro158 = {Macro158_NumEntries,
		         Macro158_Entry1_DelayMin, Macro158_Entry1_DelaySec, Macro158_Entry1_TimMin, Macro158_Entry1_TimSec, Macro158_Entry1_Protocol, 0, 0, 0, 0,
		         Macro158_Entry2_DelayMin, Macro158_Entry2_DelaySec, Macro158_Entry2_TimMin, Macro158_Entry2_TimSec, Macro158_Entry2_Protocol, 0, 0, 0, 0,
		         Macro158_Entry3_DelayMin, Macro158_Entry3_DelaySec, Macro158_Entry3_TimMin, Macro158_Entry3_TimSec, Macro158_Entry3_Protocol, 0, 0, 0, 0,
		         Macro158_Entry4_DelayMin, Macro158_Entry4_DelaySec, Macro158_Entry4_TimMin, Macro158_Entry4_TimSec, Macro158_Entry4_Protocol, 0, 0, 0, 0,
		         Macro158_Entry5_DelayMin, Macro158_Entry5_DelaySec, Macro158_Entry5_TimMin, Macro158_Entry5_TimSec, Macro158_Entry5_Protocol, 0, 0, 0, 0,
		         Macro158_Entry6_DelayMin, Macro158_Entry6_DelaySec, Macro158_Entry6_TimMin, Macro158_Entry6_TimSec, Macro158_Entry6_Protocol, 0, 0, 0, 0,
		         Macro158_Entry7_DelayMin, Macro158_Entry7_DelaySec, Macro158_Entry7_TimMin, Macro158_Entry7_TimSec, Macro158_Entry7_Protocol, 0, 0, 0, 0,
		         Macro158_Entry8_DelayMin, Macro158_Entry8_DelaySec, Macro158_Entry8_TimMin, Macro158_Entry8_TimSec, Macro158_Entry8_Protocol, 0, 0, 0, 0,
		         Macro158_Entry9_DelayMin, Macro158_Entry9_DelaySec, Macro158_Entry9_TimMin, Macro158_Entry9_TimSec, Macro158_Entry9_Protocol, 0, 0, 0, 0,
		         Macro158_Entry10_DelayMin, Macro158_Entry10_DelaySec, Macro158_Entry10_TimMin, Macro158_Entry10_TimSec, Macro158_Entry10_Protocol, 0, 0, 0, 0,
		         Macro158_Entry11_DelayMin, Macro158_Entry11_DelaySec, Macro158_Entry11_TimMin, Macro158_Entry11_TimSec, Macro158_Entry11_Protocol, 0, 0, 0, 0,
		         Macro158_Entry12_DelayMin, Macro158_Entry12_DelaySec, Macro158_Entry12_TimMin, Macro158_Entry12_TimSec, Macro158_Entry12_Protocol, 0, 0, 0, 0,
		         Macro158_Entry13_DelayMin, Macro158_Entry13_DelaySec, Macro158_Entry13_TimMin, Macro158_Entry13_TimSec, Macro158_Entry13_Protocol, 0, 0, 0, 0,
		         Macro158_Entry14_DelayMin, Macro158_Entry14_DelaySec, Macro158_Entry14_TimMin, Macro158_Entry14_TimSec, Macro158_Entry14_Protocol, 0, 0, 0, 0,
		         Macro158_Entry15_DelayMin, Macro158_Entry15_DelaySec, Macro158_Entry15_TimMin, Macro158_Entry15_TimSec, Macro158_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR158_STRING};

const struct super_macro Macro159 = {Macro159_NumEntries,
		         Macro159_Entry1_DelayMin, Macro159_Entry1_DelaySec, Macro159_Entry1_TimMin, Macro159_Entry1_TimSec, Macro159_Entry1_Protocol, 0, 0, 0, 0,
		         Macro159_Entry2_DelayMin, Macro159_Entry2_DelaySec, Macro159_Entry2_TimMin, Macro159_Entry2_TimSec, Macro159_Entry2_Protocol, 0, 0, 0, 0,
		         Macro159_Entry3_DelayMin, Macro159_Entry3_DelaySec, Macro159_Entry3_TimMin, Macro159_Entry3_TimSec, Macro159_Entry3_Protocol, 0, 0, 0, 0,
		         Macro159_Entry4_DelayMin, Macro159_Entry4_DelaySec, Macro159_Entry4_TimMin, Macro159_Entry4_TimSec, Macro159_Entry4_Protocol, 0, 0, 0, 0,
		         Macro159_Entry5_DelayMin, Macro159_Entry5_DelaySec, Macro159_Entry5_TimMin, Macro159_Entry5_TimSec, Macro159_Entry5_Protocol, 0, 0, 0, 0,
		         Macro159_Entry6_DelayMin, Macro159_Entry6_DelaySec, Macro159_Entry6_TimMin, Macro159_Entry6_TimSec, Macro159_Entry6_Protocol, 0, 0, 0, 0,
		         Macro159_Entry7_DelayMin, Macro159_Entry7_DelaySec, Macro159_Entry7_TimMin, Macro159_Entry7_TimSec, Macro159_Entry7_Protocol, 0, 0, 0, 0,
		         Macro159_Entry8_DelayMin, Macro159_Entry8_DelaySec, Macro159_Entry8_TimMin, Macro159_Entry8_TimSec, Macro159_Entry8_Protocol, 0, 0, 0, 0,
		         Macro159_Entry9_DelayMin, Macro159_Entry9_DelaySec, Macro159_Entry9_TimMin, Macro159_Entry9_TimSec, Macro159_Entry9_Protocol, 0, 0, 0, 0,
		         Macro159_Entry10_DelayMin, Macro159_Entry10_DelaySec, Macro159_Entry10_TimMin, Macro159_Entry10_TimSec, Macro159_Entry10_Protocol, 0, 0, 0, 0,
		         Macro159_Entry11_DelayMin, Macro159_Entry11_DelaySec, Macro159_Entry11_TimMin, Macro159_Entry11_TimSec, Macro159_Entry11_Protocol, 0, 0, 0, 0,
		         Macro159_Entry12_DelayMin, Macro159_Entry12_DelaySec, Macro159_Entry12_TimMin, Macro159_Entry12_TimSec, Macro159_Entry12_Protocol, 0, 0, 0, 0,
		         Macro159_Entry13_DelayMin, Macro159_Entry13_DelaySec, Macro159_Entry13_TimMin, Macro159_Entry13_TimSec, Macro159_Entry13_Protocol, 0, 0, 0, 0,
		         Macro159_Entry14_DelayMin, Macro159_Entry14_DelaySec, Macro159_Entry14_TimMin, Macro159_Entry14_TimSec, Macro159_Entry14_Protocol, 0, 0, 0, 0,
		         Macro159_Entry15_DelayMin, Macro159_Entry15_DelaySec, Macro159_Entry15_TimMin, Macro159_Entry15_TimSec, Macro159_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR159_STRING};

const struct super_macro Macro160 = {Macro160_NumEntries,
		         Macro160_Entry1_DelayMin, Macro160_Entry1_DelaySec, Macro160_Entry1_TimMin, Macro160_Entry1_TimSec, Macro160_Entry1_Protocol, 0, 0, 0, 0,
		         Macro160_Entry2_DelayMin, Macro160_Entry2_DelaySec, Macro160_Entry2_TimMin, Macro160_Entry2_TimSec, Macro160_Entry2_Protocol, 0, 0, 0, 0,
		         Macro160_Entry3_DelayMin, Macro160_Entry3_DelaySec, Macro160_Entry3_TimMin, Macro160_Entry3_TimSec, Macro160_Entry3_Protocol, 0, 0, 0, 0,
		         Macro160_Entry4_DelayMin, Macro160_Entry4_DelaySec, Macro160_Entry4_TimMin, Macro160_Entry4_TimSec, Macro160_Entry4_Protocol, 0, 0, 0, 0,
		         Macro160_Entry5_DelayMin, Macro160_Entry5_DelaySec, Macro160_Entry5_TimMin, Macro160_Entry5_TimSec, Macro160_Entry5_Protocol, 0, 0, 0, 0,
		         Macro160_Entry6_DelayMin, Macro160_Entry6_DelaySec, Macro160_Entry6_TimMin, Macro160_Entry6_TimSec, Macro160_Entry6_Protocol, 0, 0, 0, 0,
		         Macro160_Entry7_DelayMin, Macro160_Entry7_DelaySec, Macro160_Entry7_TimMin, Macro160_Entry7_TimSec, Macro160_Entry7_Protocol, 0, 0, 0, 0,
		         Macro160_Entry8_DelayMin, Macro160_Entry8_DelaySec, Macro160_Entry8_TimMin, Macro160_Entry8_TimSec, Macro160_Entry8_Protocol, 0, 0, 0, 0,
		         Macro160_Entry9_DelayMin, Macro160_Entry9_DelaySec, Macro160_Entry9_TimMin, Macro160_Entry9_TimSec, Macro160_Entry9_Protocol, 0, 0, 0, 0,
		         Macro160_Entry10_DelayMin, Macro160_Entry10_DelaySec, Macro160_Entry10_TimMin, Macro160_Entry10_TimSec, Macro160_Entry10_Protocol, 0, 0, 0, 0,
		         Macro160_Entry11_DelayMin, Macro160_Entry11_DelaySec, Macro160_Entry11_TimMin, Macro160_Entry11_TimSec, Macro160_Entry11_Protocol, 0, 0, 0, 0,
		         Macro160_Entry12_DelayMin, Macro160_Entry12_DelaySec, Macro160_Entry12_TimMin, Macro160_Entry12_TimSec, Macro160_Entry12_Protocol, 0, 0, 0, 0,
		         Macro160_Entry13_DelayMin, Macro160_Entry13_DelaySec, Macro160_Entry13_TimMin, Macro160_Entry13_TimSec, Macro160_Entry13_Protocol, 0, 0, 0, 0,
		         Macro160_Entry14_DelayMin, Macro160_Entry14_DelaySec, Macro160_Entry14_TimMin, Macro160_Entry14_TimSec, Macro160_Entry14_Protocol, 0, 0, 0, 0,
		         Macro160_Entry15_DelayMin, Macro160_Entry15_DelaySec, Macro160_Entry15_TimMin, Macro160_Entry15_TimSec, Macro160_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR160_STRING};

const struct super_macro Macro161 = {Macro161_NumEntries,
		         Macro161_Entry1_DelayMin, Macro161_Entry1_DelaySec, Macro161_Entry1_TimMin, Macro161_Entry1_TimSec, Macro161_Entry1_Protocol, 0, 0, 0, 0,
		         Macro161_Entry2_DelayMin, Macro161_Entry2_DelaySec, Macro161_Entry2_TimMin, Macro161_Entry2_TimSec, Macro161_Entry2_Protocol, 0, 0, 0, 0,
		         Macro161_Entry3_DelayMin, Macro161_Entry3_DelaySec, Macro161_Entry3_TimMin, Macro161_Entry3_TimSec, Macro161_Entry3_Protocol, 0, 0, 0, 0,
		         Macro161_Entry4_DelayMin, Macro161_Entry4_DelaySec, Macro161_Entry4_TimMin, Macro161_Entry4_TimSec, Macro161_Entry4_Protocol, 0, 0, 0, 0,
		         Macro161_Entry5_DelayMin, Macro161_Entry5_DelaySec, Macro161_Entry5_TimMin, Macro161_Entry5_TimSec, Macro161_Entry5_Protocol, 0, 0, 0, 0,
		         Macro161_Entry6_DelayMin, Macro161_Entry6_DelaySec, Macro161_Entry6_TimMin, Macro161_Entry6_TimSec, Macro161_Entry6_Protocol, 0, 0, 0, 0,
		         Macro161_Entry7_DelayMin, Macro161_Entry7_DelaySec, Macro161_Entry7_TimMin, Macro161_Entry7_TimSec, Macro161_Entry7_Protocol, 0, 0, 0, 0,
		         Macro161_Entry8_DelayMin, Macro161_Entry8_DelaySec, Macro161_Entry8_TimMin, Macro161_Entry8_TimSec, Macro161_Entry8_Protocol, 0, 0, 0, 0,
		         Macro161_Entry9_DelayMin, Macro161_Entry9_DelaySec, Macro161_Entry9_TimMin, Macro161_Entry9_TimSec, Macro161_Entry9_Protocol, 0, 0, 0, 0,
		         Macro161_Entry10_DelayMin, Macro161_Entry10_DelaySec, Macro161_Entry10_TimMin, Macro161_Entry10_TimSec, Macro161_Entry10_Protocol, 0, 0, 0, 0,
		         Macro161_Entry11_DelayMin, Macro161_Entry11_DelaySec, Macro161_Entry11_TimMin, Macro161_Entry11_TimSec, Macro161_Entry11_Protocol, 0, 0, 0, 0,
		         Macro161_Entry12_DelayMin, Macro161_Entry12_DelaySec, Macro161_Entry12_TimMin, Macro161_Entry12_TimSec, Macro161_Entry12_Protocol, 0, 0, 0, 0,
		         Macro161_Entry13_DelayMin, Macro161_Entry13_DelaySec, Macro161_Entry13_TimMin, Macro161_Entry13_TimSec, Macro161_Entry13_Protocol, 0, 0, 0, 0,
		         Macro161_Entry14_DelayMin, Macro161_Entry14_DelaySec, Macro161_Entry14_TimMin, Macro161_Entry14_TimSec, Macro161_Entry14_Protocol, 0, 0, 0, 0,
		         Macro161_Entry15_DelayMin, Macro161_Entry15_DelaySec, Macro161_Entry15_TimMin, Macro161_Entry15_TimSec, Macro161_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR161_STRING};

const struct super_macro Macro162 = {Macro162_NumEntries,
		         Macro162_Entry1_DelayMin, Macro162_Entry1_DelaySec, Macro162_Entry1_TimMin, Macro162_Entry1_TimSec, Macro162_Entry1_Protocol, 0, 0, 0, 0,
		         Macro162_Entry2_DelayMin, Macro162_Entry2_DelaySec, Macro162_Entry2_TimMin, Macro162_Entry2_TimSec, Macro162_Entry2_Protocol, 0, 0, 0, 0,
		         Macro162_Entry3_DelayMin, Macro162_Entry3_DelaySec, Macro162_Entry3_TimMin, Macro162_Entry3_TimSec, Macro162_Entry3_Protocol, 0, 0, 0, 0,
		         Macro162_Entry4_DelayMin, Macro162_Entry4_DelaySec, Macro162_Entry4_TimMin, Macro162_Entry4_TimSec, Macro162_Entry4_Protocol, 0, 0, 0, 0,
		         Macro162_Entry5_DelayMin, Macro162_Entry5_DelaySec, Macro162_Entry5_TimMin, Macro162_Entry5_TimSec, Macro162_Entry5_Protocol, 0, 0, 0, 0,
		         Macro162_Entry6_DelayMin, Macro162_Entry6_DelaySec, Macro162_Entry6_TimMin, Macro162_Entry6_TimSec, Macro162_Entry6_Protocol, 0, 0, 0, 0,
		         Macro162_Entry7_DelayMin, Macro162_Entry7_DelaySec, Macro162_Entry7_TimMin, Macro162_Entry7_TimSec, Macro162_Entry7_Protocol, 0, 0, 0, 0,
		         Macro162_Entry8_DelayMin, Macro162_Entry8_DelaySec, Macro162_Entry8_TimMin, Macro162_Entry8_TimSec, Macro162_Entry8_Protocol, 0, 0, 0, 0,
		         Macro162_Entry9_DelayMin, Macro162_Entry9_DelaySec, Macro162_Entry9_TimMin, Macro162_Entry9_TimSec, Macro162_Entry9_Protocol, 0, 0, 0, 0,
		         Macro162_Entry10_DelayMin, Macro162_Entry10_DelaySec, Macro162_Entry10_TimMin, Macro162_Entry10_TimSec, Macro162_Entry10_Protocol, 0, 0, 0, 0,
		         Macro162_Entry11_DelayMin, Macro162_Entry11_DelaySec, Macro162_Entry11_TimMin, Macro162_Entry11_TimSec, Macro162_Entry11_Protocol, 0, 0, 0, 0,
		         Macro162_Entry12_DelayMin, Macro162_Entry12_DelaySec, Macro162_Entry12_TimMin, Macro162_Entry12_TimSec, Macro162_Entry12_Protocol, 0, 0, 0, 0,
		         Macro162_Entry13_DelayMin, Macro162_Entry13_DelaySec, Macro162_Entry13_TimMin, Macro162_Entry13_TimSec, Macro162_Entry13_Protocol, 0, 0, 0, 0,
		         Macro162_Entry14_DelayMin, Macro162_Entry14_DelaySec, Macro162_Entry14_TimMin, Macro162_Entry14_TimSec, Macro162_Entry14_Protocol, 0, 0, 0, 0,
		         Macro162_Entry15_DelayMin, Macro162_Entry15_DelaySec, Macro162_Entry15_TimMin, Macro162_Entry15_TimSec, Macro162_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR162_STRING};

const struct super_macro Macro163 = {Macro163_NumEntries,
		         Macro163_Entry1_DelayMin, Macro163_Entry1_DelaySec, Macro163_Entry1_TimMin, Macro163_Entry1_TimSec, Macro163_Entry1_Protocol, 0, 0, 0, 0,
		         Macro163_Entry2_DelayMin, Macro163_Entry2_DelaySec, Macro163_Entry2_TimMin, Macro163_Entry2_TimSec, Macro163_Entry2_Protocol, 0, 0, 0, 0,
		         Macro163_Entry3_DelayMin, Macro163_Entry3_DelaySec, Macro163_Entry3_TimMin, Macro163_Entry3_TimSec, Macro163_Entry3_Protocol, 0, 0, 0, 0,
		         Macro163_Entry4_DelayMin, Macro163_Entry4_DelaySec, Macro163_Entry4_TimMin, Macro163_Entry4_TimSec, Macro163_Entry4_Protocol, 0, 0, 0, 0,
		         Macro163_Entry5_DelayMin, Macro163_Entry5_DelaySec, Macro163_Entry5_TimMin, Macro163_Entry5_TimSec, Macro163_Entry5_Protocol, 0, 0, 0, 0,
		         Macro163_Entry6_DelayMin, Macro163_Entry6_DelaySec, Macro163_Entry6_TimMin, Macro163_Entry6_TimSec, Macro163_Entry6_Protocol, 0, 0, 0, 0,
		         Macro163_Entry7_DelayMin, Macro163_Entry7_DelaySec, Macro163_Entry7_TimMin, Macro163_Entry7_TimSec, Macro163_Entry7_Protocol, 0, 0, 0, 0,
		         Macro163_Entry8_DelayMin, Macro163_Entry8_DelaySec, Macro163_Entry8_TimMin, Macro163_Entry8_TimSec, Macro163_Entry8_Protocol, 0, 0, 0, 0,
		         Macro163_Entry9_DelayMin, Macro163_Entry9_DelaySec, Macro163_Entry9_TimMin, Macro163_Entry9_TimSec, Macro163_Entry9_Protocol, 0, 0, 0, 0,
		         Macro163_Entry10_DelayMin, Macro163_Entry10_DelaySec, Macro163_Entry10_TimMin, Macro163_Entry10_TimSec, Macro163_Entry10_Protocol, 0, 0, 0, 0,
		         Macro163_Entry11_DelayMin, Macro163_Entry11_DelaySec, Macro163_Entry11_TimMin, Macro163_Entry11_TimSec, Macro163_Entry11_Protocol, 0, 0, 0, 0,
		         Macro163_Entry12_DelayMin, Macro163_Entry12_DelaySec, Macro163_Entry12_TimMin, Macro163_Entry12_TimSec, Macro163_Entry12_Protocol, 0, 0, 0, 0,
		         Macro163_Entry13_DelayMin, Macro163_Entry13_DelaySec, Macro163_Entry13_TimMin, Macro163_Entry13_TimSec, Macro163_Entry13_Protocol, 0, 0, 0, 0,
		         Macro163_Entry14_DelayMin, Macro163_Entry14_DelaySec, Macro163_Entry14_TimMin, Macro163_Entry14_TimSec, Macro163_Entry14_Protocol, 0, 0, 0, 0,
		         Macro163_Entry15_DelayMin, Macro163_Entry15_DelaySec, Macro163_Entry15_TimMin, Macro163_Entry15_TimSec, Macro163_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR163_STRING};

const struct super_macro Macro164 = {Macro164_NumEntries,
		         Macro164_Entry1_DelayMin, Macro164_Entry1_DelaySec, Macro164_Entry1_TimMin, Macro164_Entry1_TimSec, Macro164_Entry1_Protocol, 0, 0, 0, 0,
		         Macro164_Entry2_DelayMin, Macro164_Entry2_DelaySec, Macro164_Entry2_TimMin, Macro164_Entry2_TimSec, Macro164_Entry2_Protocol, 0, 0, 0, 0,
		         Macro164_Entry3_DelayMin, Macro164_Entry3_DelaySec, Macro164_Entry3_TimMin, Macro164_Entry3_TimSec, Macro164_Entry3_Protocol, 0, 0, 0, 0,
		         Macro164_Entry4_DelayMin, Macro164_Entry4_DelaySec, Macro164_Entry4_TimMin, Macro164_Entry4_TimSec, Macro164_Entry4_Protocol, 0, 0, 0, 0,
		         Macro164_Entry5_DelayMin, Macro164_Entry5_DelaySec, Macro164_Entry5_TimMin, Macro164_Entry5_TimSec, Macro164_Entry5_Protocol, 0, 0, 0, 0,
		         Macro164_Entry6_DelayMin, Macro164_Entry6_DelaySec, Macro164_Entry6_TimMin, Macro164_Entry6_TimSec, Macro164_Entry6_Protocol, 0, 0, 0, 0,
		         Macro164_Entry7_DelayMin, Macro164_Entry7_DelaySec, Macro164_Entry7_TimMin, Macro164_Entry7_TimSec, Macro164_Entry7_Protocol, 0, 0, 0, 0,
		         Macro164_Entry8_DelayMin, Macro164_Entry8_DelaySec, Macro164_Entry8_TimMin, Macro164_Entry8_TimSec, Macro164_Entry8_Protocol, 0, 0, 0, 0,
		         Macro164_Entry9_DelayMin, Macro164_Entry9_DelaySec, Macro164_Entry9_TimMin, Macro164_Entry9_TimSec, Macro164_Entry9_Protocol, 0, 0, 0, 0,
		         Macro164_Entry10_DelayMin, Macro164_Entry10_DelaySec, Macro164_Entry10_TimMin, Macro164_Entry10_TimSec, Macro164_Entry10_Protocol, 0, 0, 0, 0,
		         Macro164_Entry11_DelayMin, Macro164_Entry11_DelaySec, Macro164_Entry11_TimMin, Macro164_Entry11_TimSec, Macro164_Entry11_Protocol, 0, 0, 0, 0,
		         Macro164_Entry12_DelayMin, Macro164_Entry12_DelaySec, Macro164_Entry12_TimMin, Macro164_Entry12_TimSec, Macro164_Entry12_Protocol, 0, 0, 0, 0,
		         Macro164_Entry13_DelayMin, Macro164_Entry13_DelaySec, Macro164_Entry13_TimMin, Macro164_Entry13_TimSec, Macro164_Entry13_Protocol, 0, 0, 0, 0,
		         Macro164_Entry14_DelayMin, Macro164_Entry14_DelaySec, Macro164_Entry14_TimMin, Macro164_Entry14_TimSec, Macro164_Entry14_Protocol, 0, 0, 0, 0,
		         Macro164_Entry15_DelayMin, Macro164_Entry15_DelaySec, Macro164_Entry15_TimMin, Macro164_Entry15_TimSec, Macro164_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR164_STRING};

const struct super_macro Macro165 = {Macro165_NumEntries,
		         Macro165_Entry1_DelayMin, Macro165_Entry1_DelaySec, Macro165_Entry1_TimMin, Macro165_Entry1_TimSec, Macro165_Entry1_Protocol, 0, 0, 0, 0,
		         Macro165_Entry2_DelayMin, Macro165_Entry2_DelaySec, Macro165_Entry2_TimMin, Macro165_Entry2_TimSec, Macro165_Entry2_Protocol, 0, 0, 0, 0,
		         Macro165_Entry3_DelayMin, Macro165_Entry3_DelaySec, Macro165_Entry3_TimMin, Macro165_Entry3_TimSec, Macro165_Entry3_Protocol, 0, 0, 0, 0,
		         Macro165_Entry4_DelayMin, Macro165_Entry4_DelaySec, Macro165_Entry4_TimMin, Macro165_Entry4_TimSec, Macro165_Entry4_Protocol, 0, 0, 0, 0,
		         Macro165_Entry5_DelayMin, Macro165_Entry5_DelaySec, Macro165_Entry5_TimMin, Macro165_Entry5_TimSec, Macro165_Entry5_Protocol, 0, 0, 0, 0,
		         Macro165_Entry6_DelayMin, Macro165_Entry6_DelaySec, Macro165_Entry6_TimMin, Macro165_Entry6_TimSec, Macro165_Entry6_Protocol, 0, 0, 0, 0,
		         Macro165_Entry7_DelayMin, Macro165_Entry7_DelaySec, Macro165_Entry7_TimMin, Macro165_Entry7_TimSec, Macro165_Entry7_Protocol, 0, 0, 0, 0,
		         Macro165_Entry8_DelayMin, Macro165_Entry8_DelaySec, Macro165_Entry8_TimMin, Macro165_Entry8_TimSec, Macro165_Entry8_Protocol, 0, 0, 0, 0,
		         Macro165_Entry9_DelayMin, Macro165_Entry9_DelaySec, Macro165_Entry9_TimMin, Macro165_Entry9_TimSec, Macro165_Entry9_Protocol, 0, 0, 0, 0,
		         Macro165_Entry10_DelayMin, Macro165_Entry10_DelaySec, Macro165_Entry10_TimMin, Macro165_Entry10_TimSec, Macro165_Entry10_Protocol, 0, 0, 0, 0,
		         Macro165_Entry11_DelayMin, Macro165_Entry11_DelaySec, Macro165_Entry11_TimMin, Macro165_Entry11_TimSec, Macro165_Entry11_Protocol, 0, 0, 0, 0,
		         Macro165_Entry12_DelayMin, Macro165_Entry12_DelaySec, Macro165_Entry12_TimMin, Macro165_Entry12_TimSec, Macro165_Entry12_Protocol, 0, 0, 0, 0,
		         Macro165_Entry13_DelayMin, Macro165_Entry13_DelaySec, Macro165_Entry13_TimMin, Macro165_Entry13_TimSec, Macro165_Entry13_Protocol, 0, 0, 0, 0,
		         Macro165_Entry14_DelayMin, Macro165_Entry14_DelaySec, Macro165_Entry14_TimMin, Macro165_Entry14_TimSec, Macro165_Entry14_Protocol, 0, 0, 0, 0,
		         Macro165_Entry15_DelayMin, Macro165_Entry15_DelaySec, Macro165_Entry15_TimMin, Macro165_Entry15_TimSec, Macro165_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR165_STRING};

const struct super_macro Macro166 = {Macro166_NumEntries,
		         Macro166_Entry1_DelayMin, Macro166_Entry1_DelaySec, Macro166_Entry1_TimMin, Macro166_Entry1_TimSec, Macro166_Entry1_Protocol, 0, 0, 0, 0,
		         Macro166_Entry2_DelayMin, Macro166_Entry2_DelaySec, Macro166_Entry2_TimMin, Macro166_Entry2_TimSec, Macro166_Entry2_Protocol, 0, 0, 0, 0,
		         Macro166_Entry3_DelayMin, Macro166_Entry3_DelaySec, Macro166_Entry3_TimMin, Macro166_Entry3_TimSec, Macro166_Entry3_Protocol, 0, 0, 0, 0,
		         Macro166_Entry4_DelayMin, Macro166_Entry4_DelaySec, Macro166_Entry4_TimMin, Macro166_Entry4_TimSec, Macro166_Entry4_Protocol, 0, 0, 0, 0,
		         Macro166_Entry5_DelayMin, Macro166_Entry5_DelaySec, Macro166_Entry5_TimMin, Macro166_Entry5_TimSec, Macro166_Entry5_Protocol, 0, 0, 0, 0,
		         Macro166_Entry6_DelayMin, Macro166_Entry6_DelaySec, Macro166_Entry6_TimMin, Macro166_Entry6_TimSec, Macro166_Entry6_Protocol, 0, 0, 0, 0,
		         Macro166_Entry7_DelayMin, Macro166_Entry7_DelaySec, Macro166_Entry7_TimMin, Macro166_Entry7_TimSec, Macro166_Entry7_Protocol, 0, 0, 0, 0,
		         Macro166_Entry8_DelayMin, Macro166_Entry8_DelaySec, Macro166_Entry8_TimMin, Macro166_Entry8_TimSec, Macro166_Entry8_Protocol, 0, 0, 0, 0,
		         Macro166_Entry9_DelayMin, Macro166_Entry9_DelaySec, Macro166_Entry9_TimMin, Macro166_Entry9_TimSec, Macro166_Entry9_Protocol, 0, 0, 0, 0,
		         Macro166_Entry10_DelayMin, Macro166_Entry10_DelaySec, Macro166_Entry10_TimMin, Macro166_Entry10_TimSec, Macro166_Entry10_Protocol, 0, 0, 0, 0,
		         Macro166_Entry11_DelayMin, Macro166_Entry11_DelaySec, Macro166_Entry11_TimMin, Macro166_Entry11_TimSec, Macro166_Entry11_Protocol, 0, 0, 0, 0,
		         Macro166_Entry12_DelayMin, Macro166_Entry12_DelaySec, Macro166_Entry12_TimMin, Macro166_Entry12_TimSec, Macro166_Entry12_Protocol, 0, 0, 0, 0,
		         Macro166_Entry13_DelayMin, Macro166_Entry13_DelaySec, Macro166_Entry13_TimMin, Macro166_Entry13_TimSec, Macro166_Entry13_Protocol, 0, 0, 0, 0,
		         Macro166_Entry14_DelayMin, Macro166_Entry14_DelaySec, Macro166_Entry14_TimMin, Macro166_Entry14_TimSec, Macro166_Entry14_Protocol, 0, 0, 0, 0,
		         Macro166_Entry15_DelayMin, Macro166_Entry15_DelaySec, Macro166_Entry15_TimMin, Macro166_Entry15_TimSec, Macro166_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR166_STRING};

const struct super_macro Macro167 = {Macro167_NumEntries,
		         Macro167_Entry1_DelayMin, Macro167_Entry1_DelaySec, Macro167_Entry1_TimMin, Macro167_Entry1_TimSec, Macro167_Entry1_Protocol, 0, 0, 0, 0,
		         Macro167_Entry2_DelayMin, Macro167_Entry2_DelaySec, Macro167_Entry2_TimMin, Macro167_Entry2_TimSec, Macro167_Entry2_Protocol, 0, 0, 0, 0,
		         Macro167_Entry3_DelayMin, Macro167_Entry3_DelaySec, Macro167_Entry3_TimMin, Macro167_Entry3_TimSec, Macro167_Entry3_Protocol, 0, 0, 0, 0,
		         Macro167_Entry4_DelayMin, Macro167_Entry4_DelaySec, Macro167_Entry4_TimMin, Macro167_Entry4_TimSec, Macro167_Entry4_Protocol, 0, 0, 0, 0,
		         Macro167_Entry5_DelayMin, Macro167_Entry5_DelaySec, Macro167_Entry5_TimMin, Macro167_Entry5_TimSec, Macro167_Entry5_Protocol, 0, 0, 0, 0,
		         Macro167_Entry6_DelayMin, Macro167_Entry6_DelaySec, Macro167_Entry6_TimMin, Macro167_Entry6_TimSec, Macro167_Entry6_Protocol, 0, 0, 0, 0,
		         Macro167_Entry7_DelayMin, Macro167_Entry7_DelaySec, Macro167_Entry7_TimMin, Macro167_Entry7_TimSec, Macro167_Entry7_Protocol, 0, 0, 0, 0,
		         Macro167_Entry8_DelayMin, Macro167_Entry8_DelaySec, Macro167_Entry8_TimMin, Macro167_Entry8_TimSec, Macro167_Entry8_Protocol, 0, 0, 0, 0,
		         Macro167_Entry9_DelayMin, Macro167_Entry9_DelaySec, Macro167_Entry9_TimMin, Macro167_Entry9_TimSec, Macro167_Entry9_Protocol, 0, 0, 0, 0,
		         Macro167_Entry10_DelayMin, Macro167_Entry10_DelaySec, Macro167_Entry10_TimMin, Macro167_Entry10_TimSec, Macro167_Entry10_Protocol, 0, 0, 0, 0,
		         Macro167_Entry11_DelayMin, Macro167_Entry11_DelaySec, Macro167_Entry11_TimMin, Macro167_Entry11_TimSec, Macro167_Entry11_Protocol, 0, 0, 0, 0,
		         Macro167_Entry12_DelayMin, Macro167_Entry12_DelaySec, Macro167_Entry12_TimMin, Macro167_Entry12_TimSec, Macro167_Entry12_Protocol, 0, 0, 0, 0,
		         Macro167_Entry13_DelayMin, Macro167_Entry13_DelaySec, Macro167_Entry13_TimMin, Macro167_Entry13_TimSec, Macro167_Entry13_Protocol, 0, 0, 0, 0,
		         Macro167_Entry14_DelayMin, Macro167_Entry14_DelaySec, Macro167_Entry14_TimMin, Macro167_Entry14_TimSec, Macro167_Entry14_Protocol, 0, 0, 0, 0,
		         Macro167_Entry15_DelayMin, Macro167_Entry15_DelaySec, Macro167_Entry15_TimMin, Macro167_Entry15_TimSec, Macro167_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR167_STRING};

const struct super_macro Macro168 = {Macro168_NumEntries,
		         Macro168_Entry1_DelayMin, Macro168_Entry1_DelaySec, Macro168_Entry1_TimMin, Macro168_Entry1_TimSec, Macro168_Entry1_Protocol, 0, 0, 0, 0,
		         Macro168_Entry2_DelayMin, Macro168_Entry2_DelaySec, Macro168_Entry2_TimMin, Macro168_Entry2_TimSec, Macro168_Entry2_Protocol, 0, 0, 0, 0,
		         Macro168_Entry3_DelayMin, Macro168_Entry3_DelaySec, Macro168_Entry3_TimMin, Macro168_Entry3_TimSec, Macro168_Entry3_Protocol, 0, 0, 0, 0,
		         Macro168_Entry4_DelayMin, Macro168_Entry4_DelaySec, Macro168_Entry4_TimMin, Macro168_Entry4_TimSec, Macro168_Entry4_Protocol, 0, 0, 0, 0,
		         Macro168_Entry5_DelayMin, Macro168_Entry5_DelaySec, Macro168_Entry5_TimMin, Macro168_Entry5_TimSec, Macro168_Entry5_Protocol, 0, 0, 0, 0,
		         Macro168_Entry6_DelayMin, Macro168_Entry6_DelaySec, Macro168_Entry6_TimMin, Macro168_Entry6_TimSec, Macro168_Entry6_Protocol, 0, 0, 0, 0,
		         Macro168_Entry7_DelayMin, Macro168_Entry7_DelaySec, Macro168_Entry7_TimMin, Macro168_Entry7_TimSec, Macro168_Entry7_Protocol, 0, 0, 0, 0,
		         Macro168_Entry8_DelayMin, Macro168_Entry8_DelaySec, Macro168_Entry8_TimMin, Macro168_Entry8_TimSec, Macro168_Entry8_Protocol, 0, 0, 0, 0,
		         Macro168_Entry9_DelayMin, Macro168_Entry9_DelaySec, Macro168_Entry9_TimMin, Macro168_Entry9_TimSec, Macro168_Entry9_Protocol, 0, 0, 0, 0,
		         Macro168_Entry10_DelayMin, Macro168_Entry10_DelaySec, Macro168_Entry10_TimMin, Macro168_Entry10_TimSec, Macro168_Entry10_Protocol, 0, 0, 0, 0,
		         Macro168_Entry11_DelayMin, Macro168_Entry11_DelaySec, Macro168_Entry11_TimMin, Macro168_Entry11_TimSec, Macro168_Entry11_Protocol, 0, 0, 0, 0,
		         Macro168_Entry12_DelayMin, Macro168_Entry12_DelaySec, Macro168_Entry12_TimMin, Macro168_Entry12_TimSec, Macro168_Entry12_Protocol, 0, 0, 0, 0,
		         Macro168_Entry13_DelayMin, Macro168_Entry13_DelaySec, Macro168_Entry13_TimMin, Macro168_Entry13_TimSec, Macro168_Entry13_Protocol, 0, 0, 0, 0,
		         Macro168_Entry14_DelayMin, Macro168_Entry14_DelaySec, Macro168_Entry14_TimMin, Macro168_Entry14_TimSec, Macro168_Entry14_Protocol, 0, 0, 0, 0,
		         Macro168_Entry15_DelayMin, Macro168_Entry15_DelaySec, Macro168_Entry15_TimMin, Macro168_Entry15_TimSec, Macro168_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR168_STRING};

const struct super_macro Macro169 = {Macro169_NumEntries,
		         Macro169_Entry1_DelayMin, Macro169_Entry1_DelaySec, Macro169_Entry1_TimMin, Macro169_Entry1_TimSec, Macro169_Entry1_Protocol, 0, 0, 0, 0,
		         Macro169_Entry2_DelayMin, Macro169_Entry2_DelaySec, Macro169_Entry2_TimMin, Macro169_Entry2_TimSec, Macro169_Entry2_Protocol, 0, 0, 0, 0,
		         Macro169_Entry3_DelayMin, Macro169_Entry3_DelaySec, Macro169_Entry3_TimMin, Macro169_Entry3_TimSec, Macro169_Entry3_Protocol, 0, 0, 0, 0,
		         Macro169_Entry4_DelayMin, Macro169_Entry4_DelaySec, Macro169_Entry4_TimMin, Macro169_Entry4_TimSec, Macro169_Entry4_Protocol, 0, 0, 0, 0,
		         Macro169_Entry5_DelayMin, Macro169_Entry5_DelaySec, Macro169_Entry5_TimMin, Macro169_Entry5_TimSec, Macro169_Entry5_Protocol, 0, 0, 0, 0,
		         Macro169_Entry6_DelayMin, Macro169_Entry6_DelaySec, Macro169_Entry6_TimMin, Macro169_Entry6_TimSec, Macro169_Entry6_Protocol, 0, 0, 0, 0,
		         Macro169_Entry7_DelayMin, Macro169_Entry7_DelaySec, Macro169_Entry7_TimMin, Macro169_Entry7_TimSec, Macro169_Entry7_Protocol, 0, 0, 0, 0,
		         Macro169_Entry8_DelayMin, Macro169_Entry8_DelaySec, Macro169_Entry8_TimMin, Macro169_Entry8_TimSec, Macro169_Entry8_Protocol, 0, 0, 0, 0,
		         Macro169_Entry9_DelayMin, Macro169_Entry9_DelaySec, Macro169_Entry9_TimMin, Macro169_Entry9_TimSec, Macro169_Entry9_Protocol, 0, 0, 0, 0,
		         Macro169_Entry10_DelayMin, Macro169_Entry10_DelaySec, Macro169_Entry10_TimMin, Macro169_Entry10_TimSec, Macro169_Entry10_Protocol, 0, 0, 0, 0,
		         Macro169_Entry11_DelayMin, Macro169_Entry11_DelaySec, Macro169_Entry11_TimMin, Macro169_Entry11_TimSec, Macro169_Entry11_Protocol, 0, 0, 0, 0,
		         Macro169_Entry12_DelayMin, Macro169_Entry12_DelaySec, Macro169_Entry12_TimMin, Macro169_Entry12_TimSec, Macro169_Entry12_Protocol, 0, 0, 0, 0,
		         Macro169_Entry13_DelayMin, Macro169_Entry13_DelaySec, Macro169_Entry13_TimMin, Macro169_Entry13_TimSec, Macro169_Entry13_Protocol, 0, 0, 0, 0,
		         Macro169_Entry14_DelayMin, Macro169_Entry14_DelaySec, Macro169_Entry14_TimMin, Macro169_Entry14_TimSec, Macro169_Entry14_Protocol, 0, 0, 0, 0,
		         Macro169_Entry15_DelayMin, Macro169_Entry15_DelaySec, Macro169_Entry15_TimMin, Macro169_Entry15_TimSec, Macro169_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR169_STRING};

const struct super_macro Macro170 = {Macro170_NumEntries,
		         Macro170_Entry1_DelayMin, Macro170_Entry1_DelaySec, Macro170_Entry1_TimMin, Macro170_Entry1_TimSec, Macro170_Entry1_Protocol, 0, 0, 0, 0,
		         Macro170_Entry2_DelayMin, Macro170_Entry2_DelaySec, Macro170_Entry2_TimMin, Macro170_Entry2_TimSec, Macro170_Entry2_Protocol, 0, 0, 0, 0,
		         Macro170_Entry3_DelayMin, Macro170_Entry3_DelaySec, Macro170_Entry3_TimMin, Macro170_Entry3_TimSec, Macro170_Entry3_Protocol, 0, 0, 0, 0,
		         Macro170_Entry4_DelayMin, Macro170_Entry4_DelaySec, Macro170_Entry4_TimMin, Macro170_Entry4_TimSec, Macro170_Entry4_Protocol, 0, 0, 0, 0,
		         Macro170_Entry5_DelayMin, Macro170_Entry5_DelaySec, Macro170_Entry5_TimMin, Macro170_Entry5_TimSec, Macro170_Entry5_Protocol, 0, 0, 0, 0,
		         Macro170_Entry6_DelayMin, Macro170_Entry6_DelaySec, Macro170_Entry6_TimMin, Macro170_Entry6_TimSec, Macro170_Entry6_Protocol, 0, 0, 0, 0,
		         Macro170_Entry7_DelayMin, Macro170_Entry7_DelaySec, Macro170_Entry7_TimMin, Macro170_Entry7_TimSec, Macro170_Entry7_Protocol, 0, 0, 0, 0,
		         Macro170_Entry8_DelayMin, Macro170_Entry8_DelaySec, Macro170_Entry8_TimMin, Macro170_Entry8_TimSec, Macro170_Entry8_Protocol, 0, 0, 0, 0,
		         Macro170_Entry9_DelayMin, Macro170_Entry9_DelaySec, Macro170_Entry9_TimMin, Macro170_Entry9_TimSec, Macro170_Entry9_Protocol, 0, 0, 0, 0,
		         Macro170_Entry10_DelayMin, Macro170_Entry10_DelaySec, Macro170_Entry10_TimMin, Macro170_Entry10_TimSec, Macro170_Entry10_Protocol, 0, 0, 0, 0,
		         Macro170_Entry11_DelayMin, Macro170_Entry11_DelaySec, Macro170_Entry11_TimMin, Macro170_Entry11_TimSec, Macro170_Entry11_Protocol, 0, 0, 0, 0,
		         Macro170_Entry12_DelayMin, Macro170_Entry12_DelaySec, Macro170_Entry12_TimMin, Macro170_Entry12_TimSec, Macro170_Entry12_Protocol, 0, 0, 0, 0,
		         Macro170_Entry13_DelayMin, Macro170_Entry13_DelaySec, Macro170_Entry13_TimMin, Macro170_Entry13_TimSec, Macro170_Entry13_Protocol, 0, 0, 0, 0,
		         Macro170_Entry14_DelayMin, Macro170_Entry14_DelaySec, Macro170_Entry14_TimMin, Macro170_Entry14_TimSec, Macro170_Entry14_Protocol, 0, 0, 0, 0,
		         Macro170_Entry15_DelayMin, Macro170_Entry15_DelaySec, Macro170_Entry15_TimMin, Macro170_Entry15_TimSec, Macro170_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR170_STRING};

const struct super_macro Macro171 = {Macro171_NumEntries,
		         Macro171_Entry1_DelayMin, Macro171_Entry1_DelaySec, Macro171_Entry1_TimMin, Macro171_Entry1_TimSec, Macro171_Entry1_Protocol, 0, 0, 0, 0,
		         Macro171_Entry2_DelayMin, Macro171_Entry2_DelaySec, Macro171_Entry2_TimMin, Macro171_Entry2_TimSec, Macro171_Entry2_Protocol, 0, 0, 0, 0,
		         Macro171_Entry3_DelayMin, Macro171_Entry3_DelaySec, Macro171_Entry3_TimMin, Macro171_Entry3_TimSec, Macro171_Entry3_Protocol, 0, 0, 0, 0,
		         Macro171_Entry4_DelayMin, Macro171_Entry4_DelaySec, Macro171_Entry4_TimMin, Macro171_Entry4_TimSec, Macro171_Entry4_Protocol, 0, 0, 0, 0,
		         Macro171_Entry5_DelayMin, Macro171_Entry5_DelaySec, Macro171_Entry5_TimMin, Macro171_Entry5_TimSec, Macro171_Entry5_Protocol, 0, 0, 0, 0,
		         Macro171_Entry6_DelayMin, Macro171_Entry6_DelaySec, Macro171_Entry6_TimMin, Macro171_Entry6_TimSec, Macro171_Entry6_Protocol, 0, 0, 0, 0,
		         Macro171_Entry7_DelayMin, Macro171_Entry7_DelaySec, Macro171_Entry7_TimMin, Macro171_Entry7_TimSec, Macro171_Entry7_Protocol, 0, 0, 0, 0,
		         Macro171_Entry8_DelayMin, Macro171_Entry8_DelaySec, Macro171_Entry8_TimMin, Macro171_Entry8_TimSec, Macro171_Entry8_Protocol, 0, 0, 0, 0,
		         Macro171_Entry9_DelayMin, Macro171_Entry9_DelaySec, Macro171_Entry9_TimMin, Macro171_Entry9_TimSec, Macro171_Entry9_Protocol, 0, 0, 0, 0,
		         Macro171_Entry10_DelayMin, Macro171_Entry10_DelaySec, Macro171_Entry10_TimMin, Macro171_Entry10_TimSec, Macro171_Entry10_Protocol, 0, 0, 0, 0,
		         Macro171_Entry11_DelayMin, Macro171_Entry11_DelaySec, Macro171_Entry11_TimMin, Macro171_Entry11_TimSec, Macro171_Entry11_Protocol, 0, 0, 0, 0,
		         Macro171_Entry12_DelayMin, Macro171_Entry12_DelaySec, Macro171_Entry12_TimMin, Macro171_Entry12_TimSec, Macro171_Entry12_Protocol, 0, 0, 0, 0,
		         Macro171_Entry13_DelayMin, Macro171_Entry13_DelaySec, Macro171_Entry13_TimMin, Macro171_Entry13_TimSec, Macro171_Entry13_Protocol, 0, 0, 0, 0,
		         Macro171_Entry14_DelayMin, Macro171_Entry14_DelaySec, Macro171_Entry14_TimMin, Macro171_Entry14_TimSec, Macro171_Entry14_Protocol, 0, 0, 0, 0,
		         Macro171_Entry15_DelayMin, Macro171_Entry15_DelaySec, Macro171_Entry15_TimMin, Macro171_Entry15_TimSec, Macro171_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR171_STRING};

const struct super_macro Macro172 = {Macro172_NumEntries,
		         Macro172_Entry1_DelayMin, Macro172_Entry1_DelaySec, Macro172_Entry1_TimMin, Macro172_Entry1_TimSec, Macro172_Entry1_Protocol, 0, 0, 0, 0,
		         Macro172_Entry2_DelayMin, Macro172_Entry2_DelaySec, Macro172_Entry2_TimMin, Macro172_Entry2_TimSec, Macro172_Entry2_Protocol, 0, 0, 0, 0,
		         Macro172_Entry3_DelayMin, Macro172_Entry3_DelaySec, Macro172_Entry3_TimMin, Macro172_Entry3_TimSec, Macro172_Entry3_Protocol, 0, 0, 0, 0,
		         Macro172_Entry4_DelayMin, Macro172_Entry4_DelaySec, Macro172_Entry4_TimMin, Macro172_Entry4_TimSec, Macro172_Entry4_Protocol, 0, 0, 0, 0,
		         Macro172_Entry5_DelayMin, Macro172_Entry5_DelaySec, Macro172_Entry5_TimMin, Macro172_Entry5_TimSec, Macro172_Entry5_Protocol, 0, 0, 0, 0,
		         Macro172_Entry6_DelayMin, Macro172_Entry6_DelaySec, Macro172_Entry6_TimMin, Macro172_Entry6_TimSec, Macro172_Entry6_Protocol, 0, 0, 0, 0,
		         Macro172_Entry7_DelayMin, Macro172_Entry7_DelaySec, Macro172_Entry7_TimMin, Macro172_Entry7_TimSec, Macro172_Entry7_Protocol, 0, 0, 0, 0,
		         Macro172_Entry8_DelayMin, Macro172_Entry8_DelaySec, Macro172_Entry8_TimMin, Macro172_Entry8_TimSec, Macro172_Entry8_Protocol, 0, 0, 0, 0,
		         Macro172_Entry9_DelayMin, Macro172_Entry9_DelaySec, Macro172_Entry9_TimMin, Macro172_Entry9_TimSec, Macro172_Entry9_Protocol, 0, 0, 0, 0,
		         Macro172_Entry10_DelayMin, Macro172_Entry10_DelaySec, Macro172_Entry10_TimMin, Macro172_Entry10_TimSec, Macro172_Entry10_Protocol, 0, 0, 0, 0,
		         Macro172_Entry11_DelayMin, Macro172_Entry11_DelaySec, Macro172_Entry11_TimMin, Macro172_Entry11_TimSec, Macro172_Entry11_Protocol, 0, 0, 0, 0,
		         Macro172_Entry12_DelayMin, Macro172_Entry12_DelaySec, Macro172_Entry12_TimMin, Macro172_Entry12_TimSec, Macro172_Entry12_Protocol, 0, 0, 0, 0,
		         Macro172_Entry13_DelayMin, Macro172_Entry13_DelaySec, Macro172_Entry13_TimMin, Macro172_Entry13_TimSec, Macro172_Entry13_Protocol, 0, 0, 0, 0,
		         Macro172_Entry14_DelayMin, Macro172_Entry14_DelaySec, Macro172_Entry14_TimMin, Macro172_Entry14_TimSec, Macro172_Entry14_Protocol, 0, 0, 0, 0,
		         Macro172_Entry15_DelayMin, Macro172_Entry15_DelaySec, Macro172_Entry15_TimMin, Macro172_Entry15_TimSec, Macro172_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR172_STRING};

const struct super_macro Macro173 = {Macro173_NumEntries,
		         Macro173_Entry1_DelayMin, Macro173_Entry1_DelaySec, Macro173_Entry1_TimMin, Macro173_Entry1_TimSec, Macro173_Entry1_Protocol, 0, 0, 0, 0,
		         Macro173_Entry2_DelayMin, Macro173_Entry2_DelaySec, Macro173_Entry2_TimMin, Macro173_Entry2_TimSec, Macro173_Entry2_Protocol, 0, 0, 0, 0,
		         Macro173_Entry3_DelayMin, Macro173_Entry3_DelaySec, Macro173_Entry3_TimMin, Macro173_Entry3_TimSec, Macro173_Entry3_Protocol, 0, 0, 0, 0,
		         Macro173_Entry4_DelayMin, Macro173_Entry4_DelaySec, Macro173_Entry4_TimMin, Macro173_Entry4_TimSec, Macro173_Entry4_Protocol, 0, 0, 0, 0,
		         Macro173_Entry5_DelayMin, Macro173_Entry5_DelaySec, Macro173_Entry5_TimMin, Macro173_Entry5_TimSec, Macro173_Entry5_Protocol, 0, 0, 0, 0,
		         Macro173_Entry6_DelayMin, Macro173_Entry6_DelaySec, Macro173_Entry6_TimMin, Macro173_Entry6_TimSec, Macro173_Entry6_Protocol, 0, 0, 0, 0,
		         Macro173_Entry7_DelayMin, Macro173_Entry7_DelaySec, Macro173_Entry7_TimMin, Macro173_Entry7_TimSec, Macro173_Entry7_Protocol, 0, 0, 0, 0,
		         Macro173_Entry8_DelayMin, Macro173_Entry8_DelaySec, Macro173_Entry8_TimMin, Macro173_Entry8_TimSec, Macro173_Entry8_Protocol, 0, 0, 0, 0,
		         Macro173_Entry9_DelayMin, Macro173_Entry9_DelaySec, Macro173_Entry9_TimMin, Macro173_Entry9_TimSec, Macro173_Entry9_Protocol, 0, 0, 0, 0,
		         Macro173_Entry10_DelayMin, Macro173_Entry10_DelaySec, Macro173_Entry10_TimMin, Macro173_Entry10_TimSec, Macro173_Entry10_Protocol, 0, 0, 0, 0,
		         Macro173_Entry11_DelayMin, Macro173_Entry11_DelaySec, Macro173_Entry11_TimMin, Macro173_Entry11_TimSec, Macro173_Entry11_Protocol, 0, 0, 0, 0,
		         Macro173_Entry12_DelayMin, Macro173_Entry12_DelaySec, Macro173_Entry12_TimMin, Macro173_Entry12_TimSec, Macro173_Entry12_Protocol, 0, 0, 0, 0,
		         Macro173_Entry13_DelayMin, Macro173_Entry13_DelaySec, Macro173_Entry13_TimMin, Macro173_Entry13_TimSec, Macro173_Entry13_Protocol, 0, 0, 0, 0,
		         Macro173_Entry14_DelayMin, Macro173_Entry14_DelaySec, Macro173_Entry14_TimMin, Macro173_Entry14_TimSec, Macro173_Entry14_Protocol, 0, 0, 0, 0,
		         Macro173_Entry15_DelayMin, Macro173_Entry15_DelaySec, Macro173_Entry15_TimMin, Macro173_Entry15_TimSec, Macro173_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR173_STRING};

const struct super_macro Macro174 = {Macro174_NumEntries,
		         Macro174_Entry1_DelayMin, Macro174_Entry1_DelaySec, Macro174_Entry1_TimMin, Macro174_Entry1_TimSec, Macro174_Entry1_Protocol, 0, 0, 0, 0,
		         Macro174_Entry2_DelayMin, Macro174_Entry2_DelaySec, Macro174_Entry2_TimMin, Macro174_Entry2_TimSec, Macro174_Entry2_Protocol, 0, 0, 0, 0,
		         Macro174_Entry3_DelayMin, Macro174_Entry3_DelaySec, Macro174_Entry3_TimMin, Macro174_Entry3_TimSec, Macro174_Entry3_Protocol, 0, 0, 0, 0,
		         Macro174_Entry4_DelayMin, Macro174_Entry4_DelaySec, Macro174_Entry4_TimMin, Macro174_Entry4_TimSec, Macro174_Entry4_Protocol, 0, 0, 0, 0,
		         Macro174_Entry5_DelayMin, Macro174_Entry5_DelaySec, Macro174_Entry5_TimMin, Macro174_Entry5_TimSec, Macro174_Entry5_Protocol, 0, 0, 0, 0,
		         Macro174_Entry6_DelayMin, Macro174_Entry6_DelaySec, Macro174_Entry6_TimMin, Macro174_Entry6_TimSec, Macro174_Entry6_Protocol, 0, 0, 0, 0,
		         Macro174_Entry7_DelayMin, Macro174_Entry7_DelaySec, Macro174_Entry7_TimMin, Macro174_Entry7_TimSec, Macro174_Entry7_Protocol, 0, 0, 0, 0,
		         Macro174_Entry8_DelayMin, Macro174_Entry8_DelaySec, Macro174_Entry8_TimMin, Macro174_Entry8_TimSec, Macro174_Entry8_Protocol, 0, 0, 0, 0,
		         Macro174_Entry9_DelayMin, Macro174_Entry9_DelaySec, Macro174_Entry9_TimMin, Macro174_Entry9_TimSec, Macro174_Entry9_Protocol, 0, 0, 0, 0,
		         Macro174_Entry10_DelayMin, Macro174_Entry10_DelaySec, Macro174_Entry10_TimMin, Macro174_Entry10_TimSec, Macro174_Entry10_Protocol, 0, 0, 0, 0,
		         Macro174_Entry11_DelayMin, Macro174_Entry11_DelaySec, Macro174_Entry11_TimMin, Macro174_Entry11_TimSec, Macro174_Entry11_Protocol, 0, 0, 0, 0,
		         Macro174_Entry12_DelayMin, Macro174_Entry12_DelaySec, Macro174_Entry12_TimMin, Macro174_Entry12_TimSec, Macro174_Entry12_Protocol, 0, 0, 0, 0,
		         Macro174_Entry13_DelayMin, Macro174_Entry13_DelaySec, Macro174_Entry13_TimMin, Macro174_Entry13_TimSec, Macro174_Entry13_Protocol, 0, 0, 0, 0,
		         Macro174_Entry14_DelayMin, Macro174_Entry14_DelaySec, Macro174_Entry14_TimMin, Macro174_Entry14_TimSec, Macro174_Entry14_Protocol, 0, 0, 0, 0,
		         Macro174_Entry15_DelayMin, Macro174_Entry15_DelaySec, Macro174_Entry15_TimMin, Macro174_Entry15_TimSec, Macro174_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR174_STRING};

const struct super_macro Macro175 = {Macro175_NumEntries,
		         Macro175_Entry1_DelayMin, Macro175_Entry1_DelaySec, Macro175_Entry1_TimMin, Macro175_Entry1_TimSec, Macro175_Entry1_Protocol, 0, 0, 0, 0,
		         Macro175_Entry2_DelayMin, Macro175_Entry2_DelaySec, Macro175_Entry2_TimMin, Macro175_Entry2_TimSec, Macro175_Entry2_Protocol, 0, 0, 0, 0,
		         Macro175_Entry3_DelayMin, Macro175_Entry3_DelaySec, Macro175_Entry3_TimMin, Macro175_Entry3_TimSec, Macro175_Entry3_Protocol, 0, 0, 0, 0,
		         Macro175_Entry4_DelayMin, Macro175_Entry4_DelaySec, Macro175_Entry4_TimMin, Macro175_Entry4_TimSec, Macro175_Entry4_Protocol, 0, 0, 0, 0,
		         Macro175_Entry5_DelayMin, Macro175_Entry5_DelaySec, Macro175_Entry5_TimMin, Macro175_Entry5_TimSec, Macro175_Entry5_Protocol, 0, 0, 0, 0,
		         Macro175_Entry6_DelayMin, Macro175_Entry6_DelaySec, Macro175_Entry6_TimMin, Macro175_Entry6_TimSec, Macro175_Entry6_Protocol, 0, 0, 0, 0,
		         Macro175_Entry7_DelayMin, Macro175_Entry7_DelaySec, Macro175_Entry7_TimMin, Macro175_Entry7_TimSec, Macro175_Entry7_Protocol, 0, 0, 0, 0,
		         Macro175_Entry8_DelayMin, Macro175_Entry8_DelaySec, Macro175_Entry8_TimMin, Macro175_Entry8_TimSec, Macro175_Entry8_Protocol, 0, 0, 0, 0,
		         Macro175_Entry9_DelayMin, Macro175_Entry9_DelaySec, Macro175_Entry9_TimMin, Macro175_Entry9_TimSec, Macro175_Entry9_Protocol, 0, 0, 0, 0,
		         Macro175_Entry10_DelayMin, Macro175_Entry10_DelaySec, Macro175_Entry10_TimMin, Macro175_Entry10_TimSec, Macro175_Entry10_Protocol, 0, 0, 0, 0,
		         Macro175_Entry11_DelayMin, Macro175_Entry11_DelaySec, Macro175_Entry11_TimMin, Macro175_Entry11_TimSec, Macro175_Entry11_Protocol, 0, 0, 0, 0,
		         Macro175_Entry12_DelayMin, Macro175_Entry12_DelaySec, Macro175_Entry12_TimMin, Macro175_Entry12_TimSec, Macro175_Entry12_Protocol, 0, 0, 0, 0,
		         Macro175_Entry13_DelayMin, Macro175_Entry13_DelaySec, Macro175_Entry13_TimMin, Macro175_Entry13_TimSec, Macro175_Entry13_Protocol, 0, 0, 0, 0,
		         Macro175_Entry14_DelayMin, Macro175_Entry14_DelaySec, Macro175_Entry14_TimMin, Macro175_Entry14_TimSec, Macro175_Entry14_Protocol, 0, 0, 0, 0,
		         Macro175_Entry15_DelayMin, Macro175_Entry15_DelaySec, Macro175_Entry15_TimMin, Macro175_Entry15_TimSec, Macro175_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR175_STRING};

const struct super_macro Macro176 = {Macro176_NumEntries,
		         Macro176_Entry1_DelayMin, Macro176_Entry1_DelaySec, Macro176_Entry1_TimMin, Macro176_Entry1_TimSec, Macro176_Entry1_Protocol, 0, 0, 0, 0,
		         Macro176_Entry2_DelayMin, Macro176_Entry2_DelaySec, Macro176_Entry2_TimMin, Macro176_Entry2_TimSec, Macro176_Entry2_Protocol, 0, 0, 0, 0,
		         Macro176_Entry3_DelayMin, Macro176_Entry3_DelaySec, Macro176_Entry3_TimMin, Macro176_Entry3_TimSec, Macro176_Entry3_Protocol, 0, 0, 0, 0,
		         Macro176_Entry4_DelayMin, Macro176_Entry4_DelaySec, Macro176_Entry4_TimMin, Macro176_Entry4_TimSec, Macro176_Entry4_Protocol, 0, 0, 0, 0,
		         Macro176_Entry5_DelayMin, Macro176_Entry5_DelaySec, Macro176_Entry5_TimMin, Macro176_Entry5_TimSec, Macro176_Entry5_Protocol, 0, 0, 0, 0,
		         Macro176_Entry6_DelayMin, Macro176_Entry6_DelaySec, Macro176_Entry6_TimMin, Macro176_Entry6_TimSec, Macro176_Entry6_Protocol, 0, 0, 0, 0,
		         Macro176_Entry7_DelayMin, Macro176_Entry7_DelaySec, Macro176_Entry7_TimMin, Macro176_Entry7_TimSec, Macro176_Entry7_Protocol, 0, 0, 0, 0,
		         Macro176_Entry8_DelayMin, Macro176_Entry8_DelaySec, Macro176_Entry8_TimMin, Macro176_Entry8_TimSec, Macro176_Entry8_Protocol, 0, 0, 0, 0,
		         Macro176_Entry9_DelayMin, Macro176_Entry9_DelaySec, Macro176_Entry9_TimMin, Macro176_Entry9_TimSec, Macro176_Entry9_Protocol, 0, 0, 0, 0,
		         Macro176_Entry10_DelayMin, Macro176_Entry10_DelaySec, Macro176_Entry10_TimMin, Macro176_Entry10_TimSec, Macro176_Entry10_Protocol, 0, 0, 0, 0,
		         Macro176_Entry11_DelayMin, Macro176_Entry11_DelaySec, Macro176_Entry11_TimMin, Macro176_Entry11_TimSec, Macro176_Entry11_Protocol, 0, 0, 0, 0,
		         Macro176_Entry12_DelayMin, Macro176_Entry12_DelaySec, Macro176_Entry12_TimMin, Macro176_Entry12_TimSec, Macro176_Entry12_Protocol, 0, 0, 0, 0,
		         Macro176_Entry13_DelayMin, Macro176_Entry13_DelaySec, Macro176_Entry13_TimMin, Macro176_Entry13_TimSec, Macro176_Entry13_Protocol, 0, 0, 0, 0,
		         Macro176_Entry14_DelayMin, Macro176_Entry14_DelaySec, Macro176_Entry14_TimMin, Macro176_Entry14_TimSec, Macro176_Entry14_Protocol, 0, 0, 0, 0,
		         Macro176_Entry15_DelayMin, Macro176_Entry15_DelaySec, Macro176_Entry15_TimMin, Macro176_Entry15_TimSec, Macro176_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR176_STRING};

const struct super_macro Macro177 = {Macro177_NumEntries,
		         Macro177_Entry1_DelayMin, Macro177_Entry1_DelaySec, Macro177_Entry1_TimMin, Macro177_Entry1_TimSec, Macro177_Entry1_Protocol, 0, 0, 0, 0,
		         Macro177_Entry2_DelayMin, Macro177_Entry2_DelaySec, Macro177_Entry2_TimMin, Macro177_Entry2_TimSec, Macro177_Entry2_Protocol, 0, 0, 0, 0,
		         Macro177_Entry3_DelayMin, Macro177_Entry3_DelaySec, Macro177_Entry3_TimMin, Macro177_Entry3_TimSec, Macro177_Entry3_Protocol, 0, 0, 0, 0,
		         Macro177_Entry4_DelayMin, Macro177_Entry4_DelaySec, Macro177_Entry4_TimMin, Macro177_Entry4_TimSec, Macro177_Entry4_Protocol, 0, 0, 0, 0,
		         Macro177_Entry5_DelayMin, Macro177_Entry5_DelaySec, Macro177_Entry5_TimMin, Macro177_Entry5_TimSec, Macro177_Entry5_Protocol, 0, 0, 0, 0,
		         Macro177_Entry6_DelayMin, Macro177_Entry6_DelaySec, Macro177_Entry6_TimMin, Macro177_Entry6_TimSec, Macro177_Entry6_Protocol, 0, 0, 0, 0,
		         Macro177_Entry7_DelayMin, Macro177_Entry7_DelaySec, Macro177_Entry7_TimMin, Macro177_Entry7_TimSec, Macro177_Entry7_Protocol, 0, 0, 0, 0,
		         Macro177_Entry8_DelayMin, Macro177_Entry8_DelaySec, Macro177_Entry8_TimMin, Macro177_Entry8_TimSec, Macro177_Entry8_Protocol, 0, 0, 0, 0,
		         Macro177_Entry9_DelayMin, Macro177_Entry9_DelaySec, Macro177_Entry9_TimMin, Macro177_Entry9_TimSec, Macro177_Entry9_Protocol, 0, 0, 0, 0,
		         Macro177_Entry10_DelayMin, Macro177_Entry10_DelaySec, Macro177_Entry10_TimMin, Macro177_Entry10_TimSec, Macro177_Entry10_Protocol, 0, 0, 0, 0,
		         Macro177_Entry11_DelayMin, Macro177_Entry11_DelaySec, Macro177_Entry11_TimMin, Macro177_Entry11_TimSec, Macro177_Entry11_Protocol, 0, 0, 0, 0,
		         Macro177_Entry12_DelayMin, Macro177_Entry12_DelaySec, Macro177_Entry12_TimMin, Macro177_Entry12_TimSec, Macro177_Entry12_Protocol, 0, 0, 0, 0,
		         Macro177_Entry13_DelayMin, Macro177_Entry13_DelaySec, Macro177_Entry13_TimMin, Macro177_Entry13_TimSec, Macro177_Entry13_Protocol, 0, 0, 0, 0,
		         Macro177_Entry14_DelayMin, Macro177_Entry14_DelaySec, Macro177_Entry14_TimMin, Macro177_Entry14_TimSec, Macro177_Entry14_Protocol, 0, 0, 0, 0,
		         Macro177_Entry15_DelayMin, Macro177_Entry15_DelaySec, Macro177_Entry15_TimMin, Macro177_Entry15_TimSec, Macro177_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR177_STRING};

const struct super_macro Macro178 = {Macro178_NumEntries,
		         Macro178_Entry1_DelayMin, Macro178_Entry1_DelaySec, Macro178_Entry1_TimMin, Macro178_Entry1_TimSec, Macro178_Entry1_Protocol, 0, 0, 0, 0,
		         Macro178_Entry2_DelayMin, Macro178_Entry2_DelaySec, Macro178_Entry2_TimMin, Macro178_Entry2_TimSec, Macro178_Entry2_Protocol, 0, 0, 0, 0,
		         Macro178_Entry3_DelayMin, Macro178_Entry3_DelaySec, Macro178_Entry3_TimMin, Macro178_Entry3_TimSec, Macro178_Entry3_Protocol, 0, 0, 0, 0,
		         Macro178_Entry4_DelayMin, Macro178_Entry4_DelaySec, Macro178_Entry4_TimMin, Macro178_Entry4_TimSec, Macro178_Entry4_Protocol, 0, 0, 0, 0,
		         Macro178_Entry5_DelayMin, Macro178_Entry5_DelaySec, Macro178_Entry5_TimMin, Macro178_Entry5_TimSec, Macro178_Entry5_Protocol, 0, 0, 0, 0,
		         Macro178_Entry6_DelayMin, Macro178_Entry6_DelaySec, Macro178_Entry6_TimMin, Macro178_Entry6_TimSec, Macro178_Entry6_Protocol, 0, 0, 0, 0,
		         Macro178_Entry7_DelayMin, Macro178_Entry7_DelaySec, Macro178_Entry7_TimMin, Macro178_Entry7_TimSec, Macro178_Entry7_Protocol, 0, 0, 0, 0,
		         Macro178_Entry8_DelayMin, Macro178_Entry8_DelaySec, Macro178_Entry8_TimMin, Macro178_Entry8_TimSec, Macro178_Entry8_Protocol, 0, 0, 0, 0,
		         Macro178_Entry9_DelayMin, Macro178_Entry9_DelaySec, Macro178_Entry9_TimMin, Macro178_Entry9_TimSec, Macro178_Entry9_Protocol, 0, 0, 0, 0,
		         Macro178_Entry10_DelayMin, Macro178_Entry10_DelaySec, Macro178_Entry10_TimMin, Macro178_Entry10_TimSec, Macro178_Entry10_Protocol, 0, 0, 0, 0,
		         Macro178_Entry11_DelayMin, Macro178_Entry11_DelaySec, Macro178_Entry11_TimMin, Macro178_Entry11_TimSec, Macro178_Entry11_Protocol, 0, 0, 0, 0,
		         Macro178_Entry12_DelayMin, Macro178_Entry12_DelaySec, Macro178_Entry12_TimMin, Macro178_Entry12_TimSec, Macro178_Entry12_Protocol, 0, 0, 0, 0,
		         Macro178_Entry13_DelayMin, Macro178_Entry13_DelaySec, Macro178_Entry13_TimMin, Macro178_Entry13_TimSec, Macro178_Entry13_Protocol, 0, 0, 0, 0,
		         Macro178_Entry14_DelayMin, Macro178_Entry14_DelaySec, Macro178_Entry14_TimMin, Macro178_Entry14_TimSec, Macro178_Entry14_Protocol, 0, 0, 0, 0,
		         Macro178_Entry15_DelayMin, Macro178_Entry15_DelaySec, Macro178_Entry15_TimMin, Macro178_Entry15_TimSec, Macro178_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR178_STRING};

const struct super_macro Macro179 = {Macro179_NumEntries,
		         Macro179_Entry1_DelayMin, Macro179_Entry1_DelaySec, Macro179_Entry1_TimMin, Macro179_Entry1_TimSec, Macro179_Entry1_Protocol, 0, 0, 0, 0,
		         Macro179_Entry2_DelayMin, Macro179_Entry2_DelaySec, Macro179_Entry2_TimMin, Macro179_Entry2_TimSec, Macro179_Entry2_Protocol, 0, 0, 0, 0,
		         Macro179_Entry3_DelayMin, Macro179_Entry3_DelaySec, Macro179_Entry3_TimMin, Macro179_Entry3_TimSec, Macro179_Entry3_Protocol, 0, 0, 0, 0,
		         Macro179_Entry4_DelayMin, Macro179_Entry4_DelaySec, Macro179_Entry4_TimMin, Macro179_Entry4_TimSec, Macro179_Entry4_Protocol, 0, 0, 0, 0,
		         Macro179_Entry5_DelayMin, Macro179_Entry5_DelaySec, Macro179_Entry5_TimMin, Macro179_Entry5_TimSec, Macro179_Entry5_Protocol, 0, 0, 0, 0,
		         Macro179_Entry6_DelayMin, Macro179_Entry6_DelaySec, Macro179_Entry6_TimMin, Macro179_Entry6_TimSec, Macro179_Entry6_Protocol, 0, 0, 0, 0,
		         Macro179_Entry7_DelayMin, Macro179_Entry7_DelaySec, Macro179_Entry7_TimMin, Macro179_Entry7_TimSec, Macro179_Entry7_Protocol, 0, 0, 0, 0,
		         Macro179_Entry8_DelayMin, Macro179_Entry8_DelaySec, Macro179_Entry8_TimMin, Macro179_Entry8_TimSec, Macro179_Entry8_Protocol, 0, 0, 0, 0,
		         Macro179_Entry9_DelayMin, Macro179_Entry9_DelaySec, Macro179_Entry9_TimMin, Macro179_Entry9_TimSec, Macro179_Entry9_Protocol, 0, 0, 0, 0,
		         Macro179_Entry10_DelayMin, Macro179_Entry10_DelaySec, Macro179_Entry10_TimMin, Macro179_Entry10_TimSec, Macro179_Entry10_Protocol, 0, 0, 0, 0,
		         Macro179_Entry11_DelayMin, Macro179_Entry11_DelaySec, Macro179_Entry11_TimMin, Macro179_Entry11_TimSec, Macro179_Entry11_Protocol, 0, 0, 0, 0,
		         Macro179_Entry12_DelayMin, Macro179_Entry12_DelaySec, Macro179_Entry12_TimMin, Macro179_Entry12_TimSec, Macro179_Entry12_Protocol, 0, 0, 0, 0,
		         Macro179_Entry13_DelayMin, Macro179_Entry13_DelaySec, Macro179_Entry13_TimMin, Macro179_Entry13_TimSec, Macro179_Entry13_Protocol, 0, 0, 0, 0,
		         Macro179_Entry14_DelayMin, Macro179_Entry14_DelaySec, Macro179_Entry14_TimMin, Macro179_Entry14_TimSec, Macro179_Entry14_Protocol, 0, 0, 0, 0,
		         Macro179_Entry15_DelayMin, Macro179_Entry15_DelaySec, Macro179_Entry15_TimMin, Macro179_Entry15_TimSec, Macro179_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR179_STRING};

const struct super_macro Macro180 = {Macro180_NumEntries,
		         Macro180_Entry1_DelayMin, Macro180_Entry1_DelaySec, Macro180_Entry1_TimMin, Macro180_Entry1_TimSec, Macro180_Entry1_Protocol, 0, 0, 0, 0,
		         Macro180_Entry2_DelayMin, Macro180_Entry2_DelaySec, Macro180_Entry2_TimMin, Macro180_Entry2_TimSec, Macro180_Entry2_Protocol, 0, 0, 0, 0,
		         Macro180_Entry3_DelayMin, Macro180_Entry3_DelaySec, Macro180_Entry3_TimMin, Macro180_Entry3_TimSec, Macro180_Entry3_Protocol, 0, 0, 0, 0,
		         Macro180_Entry4_DelayMin, Macro180_Entry4_DelaySec, Macro180_Entry4_TimMin, Macro180_Entry4_TimSec, Macro180_Entry4_Protocol, 0, 0, 0, 0,
		         Macro180_Entry5_DelayMin, Macro180_Entry5_DelaySec, Macro180_Entry5_TimMin, Macro180_Entry5_TimSec, Macro180_Entry5_Protocol, 0, 0, 0, 0,
		         Macro180_Entry6_DelayMin, Macro180_Entry6_DelaySec, Macro180_Entry6_TimMin, Macro180_Entry6_TimSec, Macro180_Entry6_Protocol, 0, 0, 0, 0,
		         Macro180_Entry7_DelayMin, Macro180_Entry7_DelaySec, Macro180_Entry7_TimMin, Macro180_Entry7_TimSec, Macro180_Entry7_Protocol, 0, 0, 0, 0,
		         Macro180_Entry8_DelayMin, Macro180_Entry8_DelaySec, Macro180_Entry8_TimMin, Macro180_Entry8_TimSec, Macro180_Entry8_Protocol, 0, 0, 0, 0,
		         Macro180_Entry9_DelayMin, Macro180_Entry9_DelaySec, Macro180_Entry9_TimMin, Macro180_Entry9_TimSec, Macro180_Entry9_Protocol, 0, 0, 0, 0,
		         Macro180_Entry10_DelayMin, Macro180_Entry10_DelaySec, Macro180_Entry10_TimMin, Macro180_Entry10_TimSec, Macro180_Entry10_Protocol, 0, 0, 0, 0,
		         Macro180_Entry11_DelayMin, Macro180_Entry11_DelaySec, Macro180_Entry11_TimMin, Macro180_Entry11_TimSec, Macro180_Entry11_Protocol, 0, 0, 0, 0,
		         Macro180_Entry12_DelayMin, Macro180_Entry12_DelaySec, Macro180_Entry12_TimMin, Macro180_Entry12_TimSec, Macro180_Entry12_Protocol, 0, 0, 0, 0,
		         Macro180_Entry13_DelayMin, Macro180_Entry13_DelaySec, Macro180_Entry13_TimMin, Macro180_Entry13_TimSec, Macro180_Entry13_Protocol, 0, 0, 0, 0,
		         Macro180_Entry14_DelayMin, Macro180_Entry14_DelaySec, Macro180_Entry14_TimMin, Macro180_Entry14_TimSec, Macro180_Entry14_Protocol, 0, 0, 0, 0,
		         Macro180_Entry15_DelayMin, Macro180_Entry15_DelaySec, Macro180_Entry15_TimMin, Macro180_Entry15_TimSec, Macro180_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR180_STRING};

const struct super_macro Macro181 = {Macro181_NumEntries,
		         Macro181_Entry1_DelayMin, Macro181_Entry1_DelaySec, Macro181_Entry1_TimMin, Macro181_Entry1_TimSec, Macro181_Entry1_Protocol, 0, 0, 0, 0,
		         Macro181_Entry2_DelayMin, Macro181_Entry2_DelaySec, Macro181_Entry2_TimMin, Macro181_Entry2_TimSec, Macro181_Entry2_Protocol, 0, 0, 0, 0,
		         Macro181_Entry3_DelayMin, Macro181_Entry3_DelaySec, Macro181_Entry3_TimMin, Macro181_Entry3_TimSec, Macro181_Entry3_Protocol, 0, 0, 0, 0,
		         Macro181_Entry4_DelayMin, Macro181_Entry4_DelaySec, Macro181_Entry4_TimMin, Macro181_Entry4_TimSec, Macro181_Entry4_Protocol, 0, 0, 0, 0,
		         Macro181_Entry5_DelayMin, Macro181_Entry5_DelaySec, Macro181_Entry5_TimMin, Macro181_Entry5_TimSec, Macro181_Entry5_Protocol, 0, 0, 0, 0,
		         Macro181_Entry6_DelayMin, Macro181_Entry6_DelaySec, Macro181_Entry6_TimMin, Macro181_Entry6_TimSec, Macro181_Entry6_Protocol, 0, 0, 0, 0,
		         Macro181_Entry7_DelayMin, Macro181_Entry7_DelaySec, Macro181_Entry7_TimMin, Macro181_Entry7_TimSec, Macro181_Entry7_Protocol, 0, 0, 0, 0,
		         Macro181_Entry8_DelayMin, Macro181_Entry8_DelaySec, Macro181_Entry8_TimMin, Macro181_Entry8_TimSec, Macro181_Entry8_Protocol, 0, 0, 0, 0,
		         Macro181_Entry9_DelayMin, Macro181_Entry9_DelaySec, Macro181_Entry9_TimMin, Macro181_Entry9_TimSec, Macro181_Entry9_Protocol, 0, 0, 0, 0,
		         Macro181_Entry10_DelayMin, Macro181_Entry10_DelaySec, Macro181_Entry10_TimMin, Macro181_Entry10_TimSec, Macro181_Entry10_Protocol, 0, 0, 0, 0,
		         Macro181_Entry11_DelayMin, Macro181_Entry11_DelaySec, Macro181_Entry11_TimMin, Macro181_Entry11_TimSec, Macro181_Entry11_Protocol, 0, 0, 0, 0,
		         Macro181_Entry12_DelayMin, Macro181_Entry12_DelaySec, Macro181_Entry12_TimMin, Macro181_Entry12_TimSec, Macro181_Entry12_Protocol, 0, 0, 0, 0,
		         Macro181_Entry13_DelayMin, Macro181_Entry13_DelaySec, Macro181_Entry13_TimMin, Macro181_Entry13_TimSec, Macro181_Entry13_Protocol, 0, 0, 0, 0,
		         Macro181_Entry14_DelayMin, Macro181_Entry14_DelaySec, Macro181_Entry14_TimMin, Macro181_Entry14_TimSec, Macro181_Entry14_Protocol, 0, 0, 0, 0,
		         Macro181_Entry15_DelayMin, Macro181_Entry15_DelaySec, Macro181_Entry15_TimMin, Macro181_Entry15_TimSec, Macro181_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR181_STRING};

const struct super_macro Macro182 = {Macro182_NumEntries,
		         Macro182_Entry1_DelayMin, Macro182_Entry1_DelaySec, Macro182_Entry1_TimMin, Macro182_Entry1_TimSec, Macro182_Entry1_Protocol, 0, 0, 0, 0,
		         Macro182_Entry2_DelayMin, Macro182_Entry2_DelaySec, Macro182_Entry2_TimMin, Macro182_Entry2_TimSec, Macro182_Entry2_Protocol, 0, 0, 0, 0,
		         Macro182_Entry3_DelayMin, Macro182_Entry3_DelaySec, Macro182_Entry3_TimMin, Macro182_Entry3_TimSec, Macro182_Entry3_Protocol, 0, 0, 0, 0,
		         Macro182_Entry4_DelayMin, Macro182_Entry4_DelaySec, Macro182_Entry4_TimMin, Macro182_Entry4_TimSec, Macro182_Entry4_Protocol, 0, 0, 0, 0,
		         Macro182_Entry5_DelayMin, Macro182_Entry5_DelaySec, Macro182_Entry5_TimMin, Macro182_Entry5_TimSec, Macro182_Entry5_Protocol, 0, 0, 0, 0,
		         Macro182_Entry6_DelayMin, Macro182_Entry6_DelaySec, Macro182_Entry6_TimMin, Macro182_Entry6_TimSec, Macro182_Entry6_Protocol, 0, 0, 0, 0,
		         Macro182_Entry7_DelayMin, Macro182_Entry7_DelaySec, Macro182_Entry7_TimMin, Macro182_Entry7_TimSec, Macro182_Entry7_Protocol, 0, 0, 0, 0,
		         Macro182_Entry8_DelayMin, Macro182_Entry8_DelaySec, Macro182_Entry8_TimMin, Macro182_Entry8_TimSec, Macro182_Entry8_Protocol, 0, 0, 0, 0,
		         Macro182_Entry9_DelayMin, Macro182_Entry9_DelaySec, Macro182_Entry9_TimMin, Macro182_Entry9_TimSec, Macro182_Entry9_Protocol, 0, 0, 0, 0,
		         Macro182_Entry10_DelayMin, Macro182_Entry10_DelaySec, Macro182_Entry10_TimMin, Macro182_Entry10_TimSec, Macro182_Entry10_Protocol, 0, 0, 0, 0,
		         Macro182_Entry11_DelayMin, Macro182_Entry11_DelaySec, Macro182_Entry11_TimMin, Macro182_Entry11_TimSec, Macro182_Entry11_Protocol, 0, 0, 0, 0,
		         Macro182_Entry12_DelayMin, Macro182_Entry12_DelaySec, Macro182_Entry12_TimMin, Macro182_Entry12_TimSec, Macro182_Entry12_Protocol, 0, 0, 0, 0,
		         Macro182_Entry13_DelayMin, Macro182_Entry13_DelaySec, Macro182_Entry13_TimMin, Macro182_Entry13_TimSec, Macro182_Entry13_Protocol, 0, 0, 0, 0,
		         Macro182_Entry14_DelayMin, Macro182_Entry14_DelaySec, Macro182_Entry14_TimMin, Macro182_Entry14_TimSec, Macro182_Entry14_Protocol, 0, 0, 0, 0,
		         Macro182_Entry15_DelayMin, Macro182_Entry15_DelaySec, Macro182_Entry15_TimMin, Macro182_Entry15_TimSec, Macro182_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR182_STRING};

const struct super_macro Macro183 = {Macro183_NumEntries,
		         Macro183_Entry1_DelayMin, Macro183_Entry1_DelaySec, Macro183_Entry1_TimMin, Macro183_Entry1_TimSec, Macro183_Entry1_Protocol, 0, 0, 0, 0,
		         Macro183_Entry2_DelayMin, Macro183_Entry2_DelaySec, Macro183_Entry2_TimMin, Macro183_Entry2_TimSec, Macro183_Entry2_Protocol, 0, 0, 0, 0,
		         Macro183_Entry3_DelayMin, Macro183_Entry3_DelaySec, Macro183_Entry3_TimMin, Macro183_Entry3_TimSec, Macro183_Entry3_Protocol, 0, 0, 0, 0,
		         Macro183_Entry4_DelayMin, Macro183_Entry4_DelaySec, Macro183_Entry4_TimMin, Macro183_Entry4_TimSec, Macro183_Entry4_Protocol, 0, 0, 0, 0,
		         Macro183_Entry5_DelayMin, Macro183_Entry5_DelaySec, Macro183_Entry5_TimMin, Macro183_Entry5_TimSec, Macro183_Entry5_Protocol, 0, 0, 0, 0,
		         Macro183_Entry6_DelayMin, Macro183_Entry6_DelaySec, Macro183_Entry6_TimMin, Macro183_Entry6_TimSec, Macro183_Entry6_Protocol, 0, 0, 0, 0,
		         Macro183_Entry7_DelayMin, Macro183_Entry7_DelaySec, Macro183_Entry7_TimMin, Macro183_Entry7_TimSec, Macro183_Entry7_Protocol, 0, 0, 0, 0,
		         Macro183_Entry8_DelayMin, Macro183_Entry8_DelaySec, Macro183_Entry8_TimMin, Macro183_Entry8_TimSec, Macro183_Entry8_Protocol, 0, 0, 0, 0,
		         Macro183_Entry9_DelayMin, Macro183_Entry9_DelaySec, Macro183_Entry9_TimMin, Macro183_Entry9_TimSec, Macro183_Entry9_Protocol, 0, 0, 0, 0,
		         Macro183_Entry10_DelayMin, Macro183_Entry10_DelaySec, Macro183_Entry10_TimMin, Macro183_Entry10_TimSec, Macro183_Entry10_Protocol, 0, 0, 0, 0,
		         Macro183_Entry11_DelayMin, Macro183_Entry11_DelaySec, Macro183_Entry11_TimMin, Macro183_Entry11_TimSec, Macro183_Entry11_Protocol, 0, 0, 0, 0,
		         Macro183_Entry12_DelayMin, Macro183_Entry12_DelaySec, Macro183_Entry12_TimMin, Macro183_Entry12_TimSec, Macro183_Entry12_Protocol, 0, 0, 0, 0,
		         Macro183_Entry13_DelayMin, Macro183_Entry13_DelaySec, Macro183_Entry13_TimMin, Macro183_Entry13_TimSec, Macro183_Entry13_Protocol, 0, 0, 0, 0,
		         Macro183_Entry14_DelayMin, Macro183_Entry14_DelaySec, Macro183_Entry14_TimMin, Macro183_Entry14_TimSec, Macro183_Entry14_Protocol, 0, 0, 0, 0,
		         Macro183_Entry15_DelayMin, Macro183_Entry15_DelaySec, Macro183_Entry15_TimMin, Macro183_Entry15_TimSec, Macro183_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR183_STRING};

const struct super_macro Macro184 = {Macro184_NumEntries,
		         Macro184_Entry1_DelayMin, Macro184_Entry1_DelaySec, Macro184_Entry1_TimMin, Macro184_Entry1_TimSec, Macro184_Entry1_Protocol, 0, 0, 0, 0,
		         Macro184_Entry2_DelayMin, Macro184_Entry2_DelaySec, Macro184_Entry2_TimMin, Macro184_Entry2_TimSec, Macro184_Entry2_Protocol, 0, 0, 0, 0,
		         Macro184_Entry3_DelayMin, Macro184_Entry3_DelaySec, Macro184_Entry3_TimMin, Macro184_Entry3_TimSec, Macro184_Entry3_Protocol, 0, 0, 0, 0,
		         Macro184_Entry4_DelayMin, Macro184_Entry4_DelaySec, Macro184_Entry4_TimMin, Macro184_Entry4_TimSec, Macro184_Entry4_Protocol, 0, 0, 0, 0,
		         Macro184_Entry5_DelayMin, Macro184_Entry5_DelaySec, Macro184_Entry5_TimMin, Macro184_Entry5_TimSec, Macro184_Entry5_Protocol, 0, 0, 0, 0,
		         Macro184_Entry6_DelayMin, Macro184_Entry6_DelaySec, Macro184_Entry6_TimMin, Macro184_Entry6_TimSec, Macro184_Entry6_Protocol, 0, 0, 0, 0,
		         Macro184_Entry7_DelayMin, Macro184_Entry7_DelaySec, Macro184_Entry7_TimMin, Macro184_Entry7_TimSec, Macro184_Entry7_Protocol, 0, 0, 0, 0,
		         Macro184_Entry8_DelayMin, Macro184_Entry8_DelaySec, Macro184_Entry8_TimMin, Macro184_Entry8_TimSec, Macro184_Entry8_Protocol, 0, 0, 0, 0,
		         Macro184_Entry9_DelayMin, Macro184_Entry9_DelaySec, Macro184_Entry9_TimMin, Macro184_Entry9_TimSec, Macro184_Entry9_Protocol, 0, 0, 0, 0,
		         Macro184_Entry10_DelayMin, Macro184_Entry10_DelaySec, Macro184_Entry10_TimMin, Macro184_Entry10_TimSec, Macro184_Entry10_Protocol, 0, 0, 0, 0,
		         Macro184_Entry11_DelayMin, Macro184_Entry11_DelaySec, Macro184_Entry11_TimMin, Macro184_Entry11_TimSec, Macro184_Entry11_Protocol, 0, 0, 0, 0,
		         Macro184_Entry12_DelayMin, Macro184_Entry12_DelaySec, Macro184_Entry12_TimMin, Macro184_Entry12_TimSec, Macro184_Entry12_Protocol, 0, 0, 0, 0,
		         Macro184_Entry13_DelayMin, Macro184_Entry13_DelaySec, Macro184_Entry13_TimMin, Macro184_Entry13_TimSec, Macro184_Entry13_Protocol, 0, 0, 0, 0,
		         Macro184_Entry14_DelayMin, Macro184_Entry14_DelaySec, Macro184_Entry14_TimMin, Macro184_Entry14_TimSec, Macro184_Entry14_Protocol, 0, 0, 0, 0,
		         Macro184_Entry15_DelayMin, Macro184_Entry15_DelaySec, Macro184_Entry15_TimMin, Macro184_Entry15_TimSec, Macro184_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR184_STRING};

const struct super_macro Macro185 = {Macro185_NumEntries,
		         Macro185_Entry1_DelayMin, Macro185_Entry1_DelaySec, Macro185_Entry1_TimMin, Macro185_Entry1_TimSec, Macro185_Entry1_Protocol, 0, 0, 0, 0,
		         Macro185_Entry2_DelayMin, Macro185_Entry2_DelaySec, Macro185_Entry2_TimMin, Macro185_Entry2_TimSec, Macro185_Entry2_Protocol, 0, 0, 0, 0,
		         Macro185_Entry3_DelayMin, Macro185_Entry3_DelaySec, Macro185_Entry3_TimMin, Macro185_Entry3_TimSec, Macro185_Entry3_Protocol, 0, 0, 0, 0,
		         Macro185_Entry4_DelayMin, Macro185_Entry4_DelaySec, Macro185_Entry4_TimMin, Macro185_Entry4_TimSec, Macro185_Entry4_Protocol, 0, 0, 0, 0,
		         Macro185_Entry5_DelayMin, Macro185_Entry5_DelaySec, Macro185_Entry5_TimMin, Macro185_Entry5_TimSec, Macro185_Entry5_Protocol, 0, 0, 0, 0,
		         Macro185_Entry6_DelayMin, Macro185_Entry6_DelaySec, Macro185_Entry6_TimMin, Macro185_Entry6_TimSec, Macro185_Entry6_Protocol, 0, 0, 0, 0,
		         Macro185_Entry7_DelayMin, Macro185_Entry7_DelaySec, Macro185_Entry7_TimMin, Macro185_Entry7_TimSec, Macro185_Entry7_Protocol, 0, 0, 0, 0,
		         Macro185_Entry8_DelayMin, Macro185_Entry8_DelaySec, Macro185_Entry8_TimMin, Macro185_Entry8_TimSec, Macro185_Entry8_Protocol, 0, 0, 0, 0,
		         Macro185_Entry9_DelayMin, Macro185_Entry9_DelaySec, Macro185_Entry9_TimMin, Macro185_Entry9_TimSec, Macro185_Entry9_Protocol, 0, 0, 0, 0,
		         Macro185_Entry10_DelayMin, Macro185_Entry10_DelaySec, Macro185_Entry10_TimMin, Macro185_Entry10_TimSec, Macro185_Entry10_Protocol, 0, 0, 0, 0,
		         Macro185_Entry11_DelayMin, Macro185_Entry11_DelaySec, Macro185_Entry11_TimMin, Macro185_Entry11_TimSec, Macro185_Entry11_Protocol, 0, 0, 0, 0,
		         Macro185_Entry12_DelayMin, Macro185_Entry12_DelaySec, Macro185_Entry12_TimMin, Macro185_Entry12_TimSec, Macro185_Entry12_Protocol, 0, 0, 0, 0,
		         Macro185_Entry13_DelayMin, Macro185_Entry13_DelaySec, Macro185_Entry13_TimMin, Macro185_Entry13_TimSec, Macro185_Entry13_Protocol, 0, 0, 0, 0,
		         Macro185_Entry14_DelayMin, Macro185_Entry14_DelaySec, Macro185_Entry14_TimMin, Macro185_Entry14_TimSec, Macro185_Entry14_Protocol, 0, 0, 0, 0,
		         Macro185_Entry15_DelayMin, Macro185_Entry15_DelaySec, Macro185_Entry15_TimMin, Macro185_Entry15_TimSec, Macro185_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR185_STRING};

const struct super_macro Macro186 = {Macro186_NumEntries,
		         Macro186_Entry1_DelayMin, Macro186_Entry1_DelaySec, Macro186_Entry1_TimMin, Macro186_Entry1_TimSec, Macro186_Entry1_Protocol, 0, 0, 0, 0,
		         Macro186_Entry2_DelayMin, Macro186_Entry2_DelaySec, Macro186_Entry2_TimMin, Macro186_Entry2_TimSec, Macro186_Entry2_Protocol, 0, 0, 0, 0,
		         Macro186_Entry3_DelayMin, Macro186_Entry3_DelaySec, Macro186_Entry3_TimMin, Macro186_Entry3_TimSec, Macro186_Entry3_Protocol, 0, 0, 0, 0,
		         Macro186_Entry4_DelayMin, Macro186_Entry4_DelaySec, Macro186_Entry4_TimMin, Macro186_Entry4_TimSec, Macro186_Entry4_Protocol, 0, 0, 0, 0,
		         Macro186_Entry5_DelayMin, Macro186_Entry5_DelaySec, Macro186_Entry5_TimMin, Macro186_Entry5_TimSec, Macro186_Entry5_Protocol, 0, 0, 0, 0,
		         Macro186_Entry6_DelayMin, Macro186_Entry6_DelaySec, Macro186_Entry6_TimMin, Macro186_Entry6_TimSec, Macro186_Entry6_Protocol, 0, 0, 0, 0,
		         Macro186_Entry7_DelayMin, Macro186_Entry7_DelaySec, Macro186_Entry7_TimMin, Macro186_Entry7_TimSec, Macro186_Entry7_Protocol, 0, 0, 0, 0,
		         Macro186_Entry8_DelayMin, Macro186_Entry8_DelaySec, Macro186_Entry8_TimMin, Macro186_Entry8_TimSec, Macro186_Entry8_Protocol, 0, 0, 0, 0,
		         Macro186_Entry9_DelayMin, Macro186_Entry9_DelaySec, Macro186_Entry9_TimMin, Macro186_Entry9_TimSec, Macro186_Entry9_Protocol, 0, 0, 0, 0,
		         Macro186_Entry10_DelayMin, Macro186_Entry10_DelaySec, Macro186_Entry10_TimMin, Macro186_Entry10_TimSec, Macro186_Entry10_Protocol, 0, 0, 0, 0,
		         Macro186_Entry11_DelayMin, Macro186_Entry11_DelaySec, Macro186_Entry11_TimMin, Macro186_Entry11_TimSec, Macro186_Entry11_Protocol, 0, 0, 0, 0,
		         Macro186_Entry12_DelayMin, Macro186_Entry12_DelaySec, Macro186_Entry12_TimMin, Macro186_Entry12_TimSec, Macro186_Entry12_Protocol, 0, 0, 0, 0,
		         Macro186_Entry13_DelayMin, Macro186_Entry13_DelaySec, Macro186_Entry13_TimMin, Macro186_Entry13_TimSec, Macro186_Entry13_Protocol, 0, 0, 0, 0,
		         Macro186_Entry14_DelayMin, Macro186_Entry14_DelaySec, Macro186_Entry14_TimMin, Macro186_Entry14_TimSec, Macro186_Entry14_Protocol, 0, 0, 0, 0,
		         Macro186_Entry15_DelayMin, Macro186_Entry15_DelaySec, Macro186_Entry15_TimMin, Macro186_Entry15_TimSec, Macro186_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR186_STRING};

const struct super_macro Macro187 = {Macro187_NumEntries,
		         Macro187_Entry1_DelayMin, Macro187_Entry1_DelaySec, Macro187_Entry1_TimMin, Macro187_Entry1_TimSec, Macro187_Entry1_Protocol, 0, 0, 0, 0,
		         Macro187_Entry2_DelayMin, Macro187_Entry2_DelaySec, Macro187_Entry2_TimMin, Macro187_Entry2_TimSec, Macro187_Entry2_Protocol, 0, 0, 0, 0,
		         Macro187_Entry3_DelayMin, Macro187_Entry3_DelaySec, Macro187_Entry3_TimMin, Macro187_Entry3_TimSec, Macro187_Entry3_Protocol, 0, 0, 0, 0,
		         Macro187_Entry4_DelayMin, Macro187_Entry4_DelaySec, Macro187_Entry4_TimMin, Macro187_Entry4_TimSec, Macro187_Entry4_Protocol, 0, 0, 0, 0,
		         Macro187_Entry5_DelayMin, Macro187_Entry5_DelaySec, Macro187_Entry5_TimMin, Macro187_Entry5_TimSec, Macro187_Entry5_Protocol, 0, 0, 0, 0,
		         Macro187_Entry6_DelayMin, Macro187_Entry6_DelaySec, Macro187_Entry6_TimMin, Macro187_Entry6_TimSec, Macro187_Entry6_Protocol, 0, 0, 0, 0,
		         Macro187_Entry7_DelayMin, Macro187_Entry7_DelaySec, Macro187_Entry7_TimMin, Macro187_Entry7_TimSec, Macro187_Entry7_Protocol, 0, 0, 0, 0,
		         Macro187_Entry8_DelayMin, Macro187_Entry8_DelaySec, Macro187_Entry8_TimMin, Macro187_Entry8_TimSec, Macro187_Entry8_Protocol, 0, 0, 0, 0,
		         Macro187_Entry9_DelayMin, Macro187_Entry9_DelaySec, Macro187_Entry9_TimMin, Macro187_Entry9_TimSec, Macro187_Entry9_Protocol, 0, 0, 0, 0,
		         Macro187_Entry10_DelayMin, Macro187_Entry10_DelaySec, Macro187_Entry10_TimMin, Macro187_Entry10_TimSec, Macro187_Entry10_Protocol, 0, 0, 0, 0,
		         Macro187_Entry11_DelayMin, Macro187_Entry11_DelaySec, Macro187_Entry11_TimMin, Macro187_Entry11_TimSec, Macro187_Entry11_Protocol, 0, 0, 0, 0,
		         Macro187_Entry12_DelayMin, Macro187_Entry12_DelaySec, Macro187_Entry12_TimMin, Macro187_Entry12_TimSec, Macro187_Entry12_Protocol, 0, 0, 0, 0,
		         Macro187_Entry13_DelayMin, Macro187_Entry13_DelaySec, Macro187_Entry13_TimMin, Macro187_Entry13_TimSec, Macro187_Entry13_Protocol, 0, 0, 0, 0,
		         Macro187_Entry14_DelayMin, Macro187_Entry14_DelaySec, Macro187_Entry14_TimMin, Macro187_Entry14_TimSec, Macro187_Entry14_Protocol, 0, 0, 0, 0,
		         Macro187_Entry15_DelayMin, Macro187_Entry15_DelaySec, Macro187_Entry15_TimMin, Macro187_Entry15_TimSec, Macro187_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR187_STRING};

const struct super_macro Macro188 = {Macro188_NumEntries,
		         Macro188_Entry1_DelayMin, Macro188_Entry1_DelaySec, Macro188_Entry1_TimMin, Macro188_Entry1_TimSec, Macro188_Entry1_Protocol, 0, 0, 0, 0,
		         Macro188_Entry2_DelayMin, Macro188_Entry2_DelaySec, Macro188_Entry2_TimMin, Macro188_Entry2_TimSec, Macro188_Entry2_Protocol, 0, 0, 0, 0,
		         Macro188_Entry3_DelayMin, Macro188_Entry3_DelaySec, Macro188_Entry3_TimMin, Macro188_Entry3_TimSec, Macro188_Entry3_Protocol, 0, 0, 0, 0,
		         Macro188_Entry4_DelayMin, Macro188_Entry4_DelaySec, Macro188_Entry4_TimMin, Macro188_Entry4_TimSec, Macro188_Entry4_Protocol, 0, 0, 0, 0,
		         Macro188_Entry5_DelayMin, Macro188_Entry5_DelaySec, Macro188_Entry5_TimMin, Macro188_Entry5_TimSec, Macro188_Entry5_Protocol, 0, 0, 0, 0,
		         Macro188_Entry6_DelayMin, Macro188_Entry6_DelaySec, Macro188_Entry6_TimMin, Macro188_Entry6_TimSec, Macro188_Entry6_Protocol, 0, 0, 0, 0,
		         Macro188_Entry7_DelayMin, Macro188_Entry7_DelaySec, Macro188_Entry7_TimMin, Macro188_Entry7_TimSec, Macro188_Entry7_Protocol, 0, 0, 0, 0,
		         Macro188_Entry8_DelayMin, Macro188_Entry8_DelaySec, Macro188_Entry8_TimMin, Macro188_Entry8_TimSec, Macro188_Entry8_Protocol, 0, 0, 0, 0,
		         Macro188_Entry9_DelayMin, Macro188_Entry9_DelaySec, Macro188_Entry9_TimMin, Macro188_Entry9_TimSec, Macro188_Entry9_Protocol, 0, 0, 0, 0,
		         Macro188_Entry10_DelayMin, Macro188_Entry10_DelaySec, Macro188_Entry10_TimMin, Macro188_Entry10_TimSec, Macro188_Entry10_Protocol, 0, 0, 0, 0,
		         Macro188_Entry11_DelayMin, Macro188_Entry11_DelaySec, Macro188_Entry11_TimMin, Macro188_Entry11_TimSec, Macro188_Entry11_Protocol, 0, 0, 0, 0,
		         Macro188_Entry12_DelayMin, Macro188_Entry12_DelaySec, Macro188_Entry12_TimMin, Macro188_Entry12_TimSec, Macro188_Entry12_Protocol, 0, 0, 0, 0,
		         Macro188_Entry13_DelayMin, Macro188_Entry13_DelaySec, Macro188_Entry13_TimMin, Macro188_Entry13_TimSec, Macro188_Entry13_Protocol, 0, 0, 0, 0,
		         Macro188_Entry14_DelayMin, Macro188_Entry14_DelaySec, Macro188_Entry14_TimMin, Macro188_Entry14_TimSec, Macro188_Entry14_Protocol, 0, 0, 0, 0,
		         Macro188_Entry15_DelayMin, Macro188_Entry15_DelaySec, Macro188_Entry15_TimMin, Macro188_Entry15_TimSec, Macro188_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR188_STRING};

const struct super_macro Macro189 = {Macro189_NumEntries,
		         Macro189_Entry1_DelayMin, Macro189_Entry1_DelaySec, Macro189_Entry1_TimMin, Macro189_Entry1_TimSec, Macro189_Entry1_Protocol, 0, 0, 0, 0,
		         Macro189_Entry2_DelayMin, Macro189_Entry2_DelaySec, Macro189_Entry2_TimMin, Macro189_Entry2_TimSec, Macro189_Entry2_Protocol, 0, 0, 0, 0,
		         Macro189_Entry3_DelayMin, Macro189_Entry3_DelaySec, Macro189_Entry3_TimMin, Macro189_Entry3_TimSec, Macro189_Entry3_Protocol, 0, 0, 0, 0,
		         Macro189_Entry4_DelayMin, Macro189_Entry4_DelaySec, Macro189_Entry4_TimMin, Macro189_Entry4_TimSec, Macro189_Entry4_Protocol, 0, 0, 0, 0,
		         Macro189_Entry5_DelayMin, Macro189_Entry5_DelaySec, Macro189_Entry5_TimMin, Macro189_Entry5_TimSec, Macro189_Entry5_Protocol, 0, 0, 0, 0,
		         Macro189_Entry6_DelayMin, Macro189_Entry6_DelaySec, Macro189_Entry6_TimMin, Macro189_Entry6_TimSec, Macro189_Entry6_Protocol, 0, 0, 0, 0,
		         Macro189_Entry7_DelayMin, Macro189_Entry7_DelaySec, Macro189_Entry7_TimMin, Macro189_Entry7_TimSec, Macro189_Entry7_Protocol, 0, 0, 0, 0,
		         Macro189_Entry8_DelayMin, Macro189_Entry8_DelaySec, Macro189_Entry8_TimMin, Macro189_Entry8_TimSec, Macro189_Entry8_Protocol, 0, 0, 0, 0,
		         Macro189_Entry9_DelayMin, Macro189_Entry9_DelaySec, Macro189_Entry9_TimMin, Macro189_Entry9_TimSec, Macro189_Entry9_Protocol, 0, 0, 0, 0,
		         Macro189_Entry10_DelayMin, Macro189_Entry10_DelaySec, Macro189_Entry10_TimMin, Macro189_Entry10_TimSec, Macro189_Entry10_Protocol, 0, 0, 0, 0,
		         Macro189_Entry11_DelayMin, Macro189_Entry11_DelaySec, Macro189_Entry11_TimMin, Macro189_Entry11_TimSec, Macro189_Entry11_Protocol, 0, 0, 0, 0,
		         Macro189_Entry12_DelayMin, Macro189_Entry12_DelaySec, Macro189_Entry12_TimMin, Macro189_Entry12_TimSec, Macro189_Entry12_Protocol, 0, 0, 0, 0,
		         Macro189_Entry13_DelayMin, Macro189_Entry13_DelaySec, Macro189_Entry13_TimMin, Macro189_Entry13_TimSec, Macro189_Entry13_Protocol, 0, 0, 0, 0,
		         Macro189_Entry14_DelayMin, Macro189_Entry14_DelaySec, Macro189_Entry14_TimMin, Macro189_Entry14_TimSec, Macro189_Entry14_Protocol, 0, 0, 0, 0,
		         Macro189_Entry15_DelayMin, Macro189_Entry15_DelaySec, Macro189_Entry15_TimMin, Macro189_Entry15_TimSec, Macro189_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR189_STRING};

const struct super_macro Macro190 = {Macro190_NumEntries,
		         Macro190_Entry1_DelayMin, Macro190_Entry1_DelaySec, Macro190_Entry1_TimMin, Macro190_Entry1_TimSec, Macro190_Entry1_Protocol, 0, 0, 0, 0,
		         Macro190_Entry2_DelayMin, Macro190_Entry2_DelaySec, Macro190_Entry2_TimMin, Macro190_Entry2_TimSec, Macro190_Entry2_Protocol, 0, 0, 0, 0,
		         Macro190_Entry3_DelayMin, Macro190_Entry3_DelaySec, Macro190_Entry3_TimMin, Macro190_Entry3_TimSec, Macro190_Entry3_Protocol, 0, 0, 0, 0,
		         Macro190_Entry4_DelayMin, Macro190_Entry4_DelaySec, Macro190_Entry4_TimMin, Macro190_Entry4_TimSec, Macro190_Entry4_Protocol, 0, 0, 0, 0,
		         Macro190_Entry5_DelayMin, Macro190_Entry5_DelaySec, Macro190_Entry5_TimMin, Macro190_Entry5_TimSec, Macro190_Entry5_Protocol, 0, 0, 0, 0,
		         Macro190_Entry6_DelayMin, Macro190_Entry6_DelaySec, Macro190_Entry6_TimMin, Macro190_Entry6_TimSec, Macro190_Entry6_Protocol, 0, 0, 0, 0,
		         Macro190_Entry7_DelayMin, Macro190_Entry7_DelaySec, Macro190_Entry7_TimMin, Macro190_Entry7_TimSec, Macro190_Entry7_Protocol, 0, 0, 0, 0,
		         Macro190_Entry8_DelayMin, Macro190_Entry8_DelaySec, Macro190_Entry8_TimMin, Macro190_Entry8_TimSec, Macro190_Entry8_Protocol, 0, 0, 0, 0,
		         Macro190_Entry9_DelayMin, Macro190_Entry9_DelaySec, Macro190_Entry9_TimMin, Macro190_Entry9_TimSec, Macro190_Entry9_Protocol, 0, 0, 0, 0,
		         Macro190_Entry10_DelayMin, Macro190_Entry10_DelaySec, Macro190_Entry10_TimMin, Macro190_Entry10_TimSec, Macro190_Entry10_Protocol, 0, 0, 0, 0,
		         Macro190_Entry11_DelayMin, Macro190_Entry11_DelaySec, Macro190_Entry11_TimMin, Macro190_Entry11_TimSec, Macro190_Entry11_Protocol, 0, 0, 0, 0,
		         Macro190_Entry12_DelayMin, Macro190_Entry12_DelaySec, Macro190_Entry12_TimMin, Macro190_Entry12_TimSec, Macro190_Entry12_Protocol, 0, 0, 0, 0,
		         Macro190_Entry13_DelayMin, Macro190_Entry13_DelaySec, Macro190_Entry13_TimMin, Macro190_Entry13_TimSec, Macro190_Entry13_Protocol, 0, 0, 0, 0,
		         Macro190_Entry14_DelayMin, Macro190_Entry14_DelaySec, Macro190_Entry14_TimMin, Macro190_Entry14_TimSec, Macro190_Entry14_Protocol, 0, 0, 0, 0,
		         Macro190_Entry15_DelayMin, Macro190_Entry15_DelaySec, Macro190_Entry15_TimMin, Macro190_Entry15_TimSec, Macro190_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR190_STRING};

const struct super_macro Macro191 = {Macro191_NumEntries,
		         Macro191_Entry1_DelayMin, Macro191_Entry1_DelaySec, Macro191_Entry1_TimMin, Macro191_Entry1_TimSec, Macro191_Entry1_Protocol, 0, 0, 0, 0,
		         Macro191_Entry2_DelayMin, Macro191_Entry2_DelaySec, Macro191_Entry2_TimMin, Macro191_Entry2_TimSec, Macro191_Entry2_Protocol, 0, 0, 0, 0,
		         Macro191_Entry3_DelayMin, Macro191_Entry3_DelaySec, Macro191_Entry3_TimMin, Macro191_Entry3_TimSec, Macro191_Entry3_Protocol, 0, 0, 0, 0,
		         Macro191_Entry4_DelayMin, Macro191_Entry4_DelaySec, Macro191_Entry4_TimMin, Macro191_Entry4_TimSec, Macro191_Entry4_Protocol, 0, 0, 0, 0,
		         Macro191_Entry5_DelayMin, Macro191_Entry5_DelaySec, Macro191_Entry5_TimMin, Macro191_Entry5_TimSec, Macro191_Entry5_Protocol, 0, 0, 0, 0,
		         Macro191_Entry6_DelayMin, Macro191_Entry6_DelaySec, Macro191_Entry6_TimMin, Macro191_Entry6_TimSec, Macro191_Entry6_Protocol, 0, 0, 0, 0,
		         Macro191_Entry7_DelayMin, Macro191_Entry7_DelaySec, Macro191_Entry7_TimMin, Macro191_Entry7_TimSec, Macro191_Entry7_Protocol, 0, 0, 0, 0,
		         Macro191_Entry8_DelayMin, Macro191_Entry8_DelaySec, Macro191_Entry8_TimMin, Macro191_Entry8_TimSec, Macro191_Entry8_Protocol, 0, 0, 0, 0,
		         Macro191_Entry9_DelayMin, Macro191_Entry9_DelaySec, Macro191_Entry9_TimMin, Macro191_Entry9_TimSec, Macro191_Entry9_Protocol, 0, 0, 0, 0,
		         Macro191_Entry10_DelayMin, Macro191_Entry10_DelaySec, Macro191_Entry10_TimMin, Macro191_Entry10_TimSec, Macro191_Entry10_Protocol, 0, 0, 0, 0,
		         Macro191_Entry11_DelayMin, Macro191_Entry11_DelaySec, Macro191_Entry11_TimMin, Macro191_Entry11_TimSec, Macro191_Entry11_Protocol, 0, 0, 0, 0,
		         Macro191_Entry12_DelayMin, Macro191_Entry12_DelaySec, Macro191_Entry12_TimMin, Macro191_Entry12_TimSec, Macro191_Entry12_Protocol, 0, 0, 0, 0,
		         Macro191_Entry13_DelayMin, Macro191_Entry13_DelaySec, Macro191_Entry13_TimMin, Macro191_Entry13_TimSec, Macro191_Entry13_Protocol, 0, 0, 0, 0,
		         Macro191_Entry14_DelayMin, Macro191_Entry14_DelaySec, Macro191_Entry14_TimMin, Macro191_Entry14_TimSec, Macro191_Entry14_Protocol, 0, 0, 0, 0,
		         Macro191_Entry15_DelayMin, Macro191_Entry15_DelaySec, Macro191_Entry15_TimMin, Macro191_Entry15_TimSec, Macro191_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR191_STRING};

const struct super_macro Macro192 = {Macro192_NumEntries,
		         Macro192_Entry1_DelayMin, Macro192_Entry1_DelaySec, Macro192_Entry1_TimMin, Macro192_Entry1_TimSec, Macro192_Entry1_Protocol, 0, 0, 0, 0,
		         Macro192_Entry2_DelayMin, Macro192_Entry2_DelaySec, Macro192_Entry2_TimMin, Macro192_Entry2_TimSec, Macro192_Entry2_Protocol, 0, 0, 0, 0,
		         Macro192_Entry3_DelayMin, Macro192_Entry3_DelaySec, Macro192_Entry3_TimMin, Macro192_Entry3_TimSec, Macro192_Entry3_Protocol, 0, 0, 0, 0,
		         Macro192_Entry4_DelayMin, Macro192_Entry4_DelaySec, Macro192_Entry4_TimMin, Macro192_Entry4_TimSec, Macro192_Entry4_Protocol, 0, 0, 0, 0,
		         Macro192_Entry5_DelayMin, Macro192_Entry5_DelaySec, Macro192_Entry5_TimMin, Macro192_Entry5_TimSec, Macro192_Entry5_Protocol, 0, 0, 0, 0,
		         Macro192_Entry6_DelayMin, Macro192_Entry6_DelaySec, Macro192_Entry6_TimMin, Macro192_Entry6_TimSec, Macro192_Entry6_Protocol, 0, 0, 0, 0,
		         Macro192_Entry7_DelayMin, Macro192_Entry7_DelaySec, Macro192_Entry7_TimMin, Macro192_Entry7_TimSec, Macro192_Entry7_Protocol, 0, 0, 0, 0,
		         Macro192_Entry8_DelayMin, Macro192_Entry8_DelaySec, Macro192_Entry8_TimMin, Macro192_Entry8_TimSec, Macro192_Entry8_Protocol, 0, 0, 0, 0,
		         Macro192_Entry9_DelayMin, Macro192_Entry9_DelaySec, Macro192_Entry9_TimMin, Macro192_Entry9_TimSec, Macro192_Entry9_Protocol, 0, 0, 0, 0,
		         Macro192_Entry10_DelayMin, Macro192_Entry10_DelaySec, Macro192_Entry10_TimMin, Macro192_Entry10_TimSec, Macro192_Entry10_Protocol, 0, 0, 0, 0,
		         Macro192_Entry11_DelayMin, Macro192_Entry11_DelaySec, Macro192_Entry11_TimMin, Macro192_Entry11_TimSec, Macro192_Entry11_Protocol, 0, 0, 0, 0,
		         Macro192_Entry12_DelayMin, Macro192_Entry12_DelaySec, Macro192_Entry12_TimMin, Macro192_Entry12_TimSec, Macro192_Entry12_Protocol, 0, 0, 0, 0,
		         Macro192_Entry13_DelayMin, Macro192_Entry13_DelaySec, Macro192_Entry13_TimMin, Macro192_Entry13_TimSec, Macro192_Entry13_Protocol, 0, 0, 0, 0,
		         Macro192_Entry14_DelayMin, Macro192_Entry14_DelaySec, Macro192_Entry14_TimMin, Macro192_Entry14_TimSec, Macro192_Entry14_Protocol, 0, 0, 0, 0,
		         Macro192_Entry15_DelayMin, Macro192_Entry15_DelaySec, Macro192_Entry15_TimMin, Macro192_Entry15_TimSec, Macro192_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR192_STRING};

const struct super_macro Macro193 = {Macro193_NumEntries,
		         Macro193_Entry1_DelayMin, Macro193_Entry1_DelaySec, Macro193_Entry1_TimMin, Macro193_Entry1_TimSec, Macro193_Entry1_Protocol, 0, 0, 0, 0,
		         Macro193_Entry2_DelayMin, Macro193_Entry2_DelaySec, Macro193_Entry2_TimMin, Macro193_Entry2_TimSec, Macro193_Entry2_Protocol, 0, 0, 0, 0,
		         Macro193_Entry3_DelayMin, Macro193_Entry3_DelaySec, Macro193_Entry3_TimMin, Macro193_Entry3_TimSec, Macro193_Entry3_Protocol, 0, 0, 0, 0,
		         Macro193_Entry4_DelayMin, Macro193_Entry4_DelaySec, Macro193_Entry4_TimMin, Macro193_Entry4_TimSec, Macro193_Entry4_Protocol, 0, 0, 0, 0,
		         Macro193_Entry5_DelayMin, Macro193_Entry5_DelaySec, Macro193_Entry5_TimMin, Macro193_Entry5_TimSec, Macro193_Entry5_Protocol, 0, 0, 0, 0,
		         Macro193_Entry6_DelayMin, Macro193_Entry6_DelaySec, Macro193_Entry6_TimMin, Macro193_Entry6_TimSec, Macro193_Entry6_Protocol, 0, 0, 0, 0,
		         Macro193_Entry7_DelayMin, Macro193_Entry7_DelaySec, Macro193_Entry7_TimMin, Macro193_Entry7_TimSec, Macro193_Entry7_Protocol, 0, 0, 0, 0,
		         Macro193_Entry8_DelayMin, Macro193_Entry8_DelaySec, Macro193_Entry8_TimMin, Macro193_Entry8_TimSec, Macro193_Entry8_Protocol, 0, 0, 0, 0,
		         Macro193_Entry9_DelayMin, Macro193_Entry9_DelaySec, Macro193_Entry9_TimMin, Macro193_Entry9_TimSec, Macro193_Entry9_Protocol, 0, 0, 0, 0,
		         Macro193_Entry10_DelayMin, Macro193_Entry10_DelaySec, Macro193_Entry10_TimMin, Macro193_Entry10_TimSec, Macro193_Entry10_Protocol, 0, 0, 0, 0,
		         Macro193_Entry11_DelayMin, Macro193_Entry11_DelaySec, Macro193_Entry11_TimMin, Macro193_Entry11_TimSec, Macro193_Entry11_Protocol, 0, 0, 0, 0,
		         Macro193_Entry12_DelayMin, Macro193_Entry12_DelaySec, Macro193_Entry12_TimMin, Macro193_Entry12_TimSec, Macro193_Entry12_Protocol, 0, 0, 0, 0,
		         Macro193_Entry13_DelayMin, Macro193_Entry13_DelaySec, Macro193_Entry13_TimMin, Macro193_Entry13_TimSec, Macro193_Entry13_Protocol, 0, 0, 0, 0,
		         Macro193_Entry14_DelayMin, Macro193_Entry14_DelaySec, Macro193_Entry14_TimMin, Macro193_Entry14_TimSec, Macro193_Entry14_Protocol, 0, 0, 0, 0,
		         Macro193_Entry15_DelayMin, Macro193_Entry15_DelaySec, Macro193_Entry15_TimMin, Macro193_Entry15_TimSec, Macro193_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR193_STRING};

const struct super_macro Macro194 = {Macro194_NumEntries,
		         Macro194_Entry1_DelayMin, Macro194_Entry1_DelaySec, Macro194_Entry1_TimMin, Macro194_Entry1_TimSec, Macro194_Entry1_Protocol, 0, 0, 0, 0,
		         Macro194_Entry2_DelayMin, Macro194_Entry2_DelaySec, Macro194_Entry2_TimMin, Macro194_Entry2_TimSec, Macro194_Entry2_Protocol, 0, 0, 0, 0,
		         Macro194_Entry3_DelayMin, Macro194_Entry3_DelaySec, Macro194_Entry3_TimMin, Macro194_Entry3_TimSec, Macro194_Entry3_Protocol, 0, 0, 0, 0,
		         Macro194_Entry4_DelayMin, Macro194_Entry4_DelaySec, Macro194_Entry4_TimMin, Macro194_Entry4_TimSec, Macro194_Entry4_Protocol, 0, 0, 0, 0,
		         Macro194_Entry5_DelayMin, Macro194_Entry5_DelaySec, Macro194_Entry5_TimMin, Macro194_Entry5_TimSec, Macro194_Entry5_Protocol, 0, 0, 0, 0,
		         Macro194_Entry6_DelayMin, Macro194_Entry6_DelaySec, Macro194_Entry6_TimMin, Macro194_Entry6_TimSec, Macro194_Entry6_Protocol, 0, 0, 0, 0,
		         Macro194_Entry7_DelayMin, Macro194_Entry7_DelaySec, Macro194_Entry7_TimMin, Macro194_Entry7_TimSec, Macro194_Entry7_Protocol, 0, 0, 0, 0,
		         Macro194_Entry8_DelayMin, Macro194_Entry8_DelaySec, Macro194_Entry8_TimMin, Macro194_Entry8_TimSec, Macro194_Entry8_Protocol, 0, 0, 0, 0,
		         Macro194_Entry9_DelayMin, Macro194_Entry9_DelaySec, Macro194_Entry9_TimMin, Macro194_Entry9_TimSec, Macro194_Entry9_Protocol, 0, 0, 0, 0,
		         Macro194_Entry10_DelayMin, Macro194_Entry10_DelaySec, Macro194_Entry10_TimMin, Macro194_Entry10_TimSec, Macro194_Entry10_Protocol, 0, 0, 0, 0,
		         Macro194_Entry11_DelayMin, Macro194_Entry11_DelaySec, Macro194_Entry11_TimMin, Macro194_Entry11_TimSec, Macro194_Entry11_Protocol, 0, 0, 0, 0,
		         Macro194_Entry12_DelayMin, Macro194_Entry12_DelaySec, Macro194_Entry12_TimMin, Macro194_Entry12_TimSec, Macro194_Entry12_Protocol, 0, 0, 0, 0,
		         Macro194_Entry13_DelayMin, Macro194_Entry13_DelaySec, Macro194_Entry13_TimMin, Macro194_Entry13_TimSec, Macro194_Entry13_Protocol, 0, 0, 0, 0,
		         Macro194_Entry14_DelayMin, Macro194_Entry14_DelaySec, Macro194_Entry14_TimMin, Macro194_Entry14_TimSec, Macro194_Entry14_Protocol, 0, 0, 0, 0,
		         Macro194_Entry15_DelayMin, Macro194_Entry15_DelaySec, Macro194_Entry15_TimMin, Macro194_Entry15_TimSec, Macro194_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR194_STRING};

const struct super_macro Macro195 = {Macro195_NumEntries,
		         Macro195_Entry1_DelayMin, Macro195_Entry1_DelaySec, Macro195_Entry1_TimMin, Macro195_Entry1_TimSec, Macro195_Entry1_Protocol, 0, 0, 0, 0,
		         Macro195_Entry2_DelayMin, Macro195_Entry2_DelaySec, Macro195_Entry2_TimMin, Macro195_Entry2_TimSec, Macro195_Entry2_Protocol, 0, 0, 0, 0,
		         Macro195_Entry3_DelayMin, Macro195_Entry3_DelaySec, Macro195_Entry3_TimMin, Macro195_Entry3_TimSec, Macro195_Entry3_Protocol, 0, 0, 0, 0,
		         Macro195_Entry4_DelayMin, Macro195_Entry4_DelaySec, Macro195_Entry4_TimMin, Macro195_Entry4_TimSec, Macro195_Entry4_Protocol, 0, 0, 0, 0,
		         Macro195_Entry5_DelayMin, Macro195_Entry5_DelaySec, Macro195_Entry5_TimMin, Macro195_Entry5_TimSec, Macro195_Entry5_Protocol, 0, 0, 0, 0,
		         Macro195_Entry6_DelayMin, Macro195_Entry6_DelaySec, Macro195_Entry6_TimMin, Macro195_Entry6_TimSec, Macro195_Entry6_Protocol, 0, 0, 0, 0,
		         Macro195_Entry7_DelayMin, Macro195_Entry7_DelaySec, Macro195_Entry7_TimMin, Macro195_Entry7_TimSec, Macro195_Entry7_Protocol, 0, 0, 0, 0,
		         Macro195_Entry8_DelayMin, Macro195_Entry8_DelaySec, Macro195_Entry8_TimMin, Macro195_Entry8_TimSec, Macro195_Entry8_Protocol, 0, 0, 0, 0,
		         Macro195_Entry9_DelayMin, Macro195_Entry9_DelaySec, Macro195_Entry9_TimMin, Macro195_Entry9_TimSec, Macro195_Entry9_Protocol, 0, 0, 0, 0,
		         Macro195_Entry10_DelayMin, Macro195_Entry10_DelaySec, Macro195_Entry10_TimMin, Macro195_Entry10_TimSec, Macro195_Entry10_Protocol, 0, 0, 0, 0,
		         Macro195_Entry11_DelayMin, Macro195_Entry11_DelaySec, Macro195_Entry11_TimMin, Macro195_Entry11_TimSec, Macro195_Entry11_Protocol, 0, 0, 0, 0,
		         Macro195_Entry12_DelayMin, Macro195_Entry12_DelaySec, Macro195_Entry12_TimMin, Macro195_Entry12_TimSec, Macro195_Entry12_Protocol, 0, 0, 0, 0,
		         Macro195_Entry13_DelayMin, Macro195_Entry13_DelaySec, Macro195_Entry13_TimMin, Macro195_Entry13_TimSec, Macro195_Entry13_Protocol, 0, 0, 0, 0,
		         Macro195_Entry14_DelayMin, Macro195_Entry14_DelaySec, Macro195_Entry14_TimMin, Macro195_Entry14_TimSec, Macro195_Entry14_Protocol, 0, 0, 0, 0,
		         Macro195_Entry15_DelayMin, Macro195_Entry15_DelaySec, Macro195_Entry15_TimMin, Macro195_Entry15_TimSec, Macro195_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR195_STRING};

const struct super_macro Macro196 = {Macro196_NumEntries,
		         Macro196_Entry1_DelayMin, Macro196_Entry1_DelaySec, Macro196_Entry1_TimMin, Macro196_Entry1_TimSec, Macro196_Entry1_Protocol, 0, 0, 0, 0,
		         Macro196_Entry2_DelayMin, Macro196_Entry2_DelaySec, Macro196_Entry2_TimMin, Macro196_Entry2_TimSec, Macro196_Entry2_Protocol, 0, 0, 0, 0,
		         Macro196_Entry3_DelayMin, Macro196_Entry3_DelaySec, Macro196_Entry3_TimMin, Macro196_Entry3_TimSec, Macro196_Entry3_Protocol, 0, 0, 0, 0,
		         Macro196_Entry4_DelayMin, Macro196_Entry4_DelaySec, Macro196_Entry4_TimMin, Macro196_Entry4_TimSec, Macro196_Entry4_Protocol, 0, 0, 0, 0,
		         Macro196_Entry5_DelayMin, Macro196_Entry5_DelaySec, Macro196_Entry5_TimMin, Macro196_Entry5_TimSec, Macro196_Entry5_Protocol, 0, 0, 0, 0,
		         Macro196_Entry6_DelayMin, Macro196_Entry6_DelaySec, Macro196_Entry6_TimMin, Macro196_Entry6_TimSec, Macro196_Entry6_Protocol, 0, 0, 0, 0,
		         Macro196_Entry7_DelayMin, Macro196_Entry7_DelaySec, Macro196_Entry7_TimMin, Macro196_Entry7_TimSec, Macro196_Entry7_Protocol, 0, 0, 0, 0,
		         Macro196_Entry8_DelayMin, Macro196_Entry8_DelaySec, Macro196_Entry8_TimMin, Macro196_Entry8_TimSec, Macro196_Entry8_Protocol, 0, 0, 0, 0,
		         Macro196_Entry9_DelayMin, Macro196_Entry9_DelaySec, Macro196_Entry9_TimMin, Macro196_Entry9_TimSec, Macro196_Entry9_Protocol, 0, 0, 0, 0,
		         Macro196_Entry10_DelayMin, Macro196_Entry10_DelaySec, Macro196_Entry10_TimMin, Macro196_Entry10_TimSec, Macro196_Entry10_Protocol, 0, 0, 0, 0,
		         Macro196_Entry11_DelayMin, Macro196_Entry11_DelaySec, Macro196_Entry11_TimMin, Macro196_Entry11_TimSec, Macro196_Entry11_Protocol, 0, 0, 0, 0,
		         Macro196_Entry12_DelayMin, Macro196_Entry12_DelaySec, Macro196_Entry12_TimMin, Macro196_Entry12_TimSec, Macro196_Entry12_Protocol, 0, 0, 0, 0,
		         Macro196_Entry13_DelayMin, Macro196_Entry13_DelaySec, Macro196_Entry13_TimMin, Macro196_Entry13_TimSec, Macro196_Entry13_Protocol, 0, 0, 0, 0,
		         Macro196_Entry14_DelayMin, Macro196_Entry14_DelaySec, Macro196_Entry14_TimMin, Macro196_Entry14_TimSec, Macro196_Entry14_Protocol, 0, 0, 0, 0,
		         Macro196_Entry15_DelayMin, Macro196_Entry15_DelaySec, Macro196_Entry15_TimMin, Macro196_Entry15_TimSec, Macro196_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR196_STRING};

const struct super_macro Macro197 = {Macro197_NumEntries,
		         Macro197_Entry1_DelayMin, Macro197_Entry1_DelaySec, Macro197_Entry1_TimMin, Macro197_Entry1_TimSec, Macro197_Entry1_Protocol, 0, 0, 0, 0,
		         Macro197_Entry2_DelayMin, Macro197_Entry2_DelaySec, Macro197_Entry2_TimMin, Macro197_Entry2_TimSec, Macro197_Entry2_Protocol, 0, 0, 0, 0,
		         Macro197_Entry3_DelayMin, Macro197_Entry3_DelaySec, Macro197_Entry3_TimMin, Macro197_Entry3_TimSec, Macro197_Entry3_Protocol, 0, 0, 0, 0,
		         Macro197_Entry4_DelayMin, Macro197_Entry4_DelaySec, Macro197_Entry4_TimMin, Macro197_Entry4_TimSec, Macro197_Entry4_Protocol, 0, 0, 0, 0,
		         Macro197_Entry5_DelayMin, Macro197_Entry5_DelaySec, Macro197_Entry5_TimMin, Macro197_Entry5_TimSec, Macro197_Entry5_Protocol, 0, 0, 0, 0,
		         Macro197_Entry6_DelayMin, Macro197_Entry6_DelaySec, Macro197_Entry6_TimMin, Macro197_Entry6_TimSec, Macro197_Entry6_Protocol, 0, 0, 0, 0,
		         Macro197_Entry7_DelayMin, Macro197_Entry7_DelaySec, Macro197_Entry7_TimMin, Macro197_Entry7_TimSec, Macro197_Entry7_Protocol, 0, 0, 0, 0,
		         Macro197_Entry8_DelayMin, Macro197_Entry8_DelaySec, Macro197_Entry8_TimMin, Macro197_Entry8_TimSec, Macro197_Entry8_Protocol, 0, 0, 0, 0,
		         Macro197_Entry9_DelayMin, Macro197_Entry9_DelaySec, Macro197_Entry9_TimMin, Macro197_Entry9_TimSec, Macro197_Entry9_Protocol, 0, 0, 0, 0,
		         Macro197_Entry10_DelayMin, Macro197_Entry10_DelaySec, Macro197_Entry10_TimMin, Macro197_Entry10_TimSec, Macro197_Entry10_Protocol, 0, 0, 0, 0,
		         Macro197_Entry11_DelayMin, Macro197_Entry11_DelaySec, Macro197_Entry11_TimMin, Macro197_Entry11_TimSec, Macro197_Entry11_Protocol, 0, 0, 0, 0,
		         Macro197_Entry12_DelayMin, Macro197_Entry12_DelaySec, Macro197_Entry12_TimMin, Macro197_Entry12_TimSec, Macro197_Entry12_Protocol, 0, 0, 0, 0,
		         Macro197_Entry13_DelayMin, Macro197_Entry13_DelaySec, Macro197_Entry13_TimMin, Macro197_Entry13_TimSec, Macro197_Entry13_Protocol, 0, 0, 0, 0,
		         Macro197_Entry14_DelayMin, Macro197_Entry14_DelaySec, Macro197_Entry14_TimMin, Macro197_Entry14_TimSec, Macro197_Entry14_Protocol, 0, 0, 0, 0,
		         Macro197_Entry15_DelayMin, Macro197_Entry15_DelaySec, Macro197_Entry15_TimMin, Macro197_Entry15_TimSec, Macro197_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR197_STRING};

const struct super_macro Macro198 = {Macro198_NumEntries,
		         Macro198_Entry1_DelayMin, Macro198_Entry1_DelaySec, Macro198_Entry1_TimMin, Macro198_Entry1_TimSec, Macro198_Entry1_Protocol, 0, 0, 0, 0,
		         Macro198_Entry2_DelayMin, Macro198_Entry2_DelaySec, Macro198_Entry2_TimMin, Macro198_Entry2_TimSec, Macro198_Entry2_Protocol, 0, 0, 0, 0,
		         Macro198_Entry3_DelayMin, Macro198_Entry3_DelaySec, Macro198_Entry3_TimMin, Macro198_Entry3_TimSec, Macro198_Entry3_Protocol, 0, 0, 0, 0,
		         Macro198_Entry4_DelayMin, Macro198_Entry4_DelaySec, Macro198_Entry4_TimMin, Macro198_Entry4_TimSec, Macro198_Entry4_Protocol, 0, 0, 0, 0,
		         Macro198_Entry5_DelayMin, Macro198_Entry5_DelaySec, Macro198_Entry5_TimMin, Macro198_Entry5_TimSec, Macro198_Entry5_Protocol, 0, 0, 0, 0,
		         Macro198_Entry6_DelayMin, Macro198_Entry6_DelaySec, Macro198_Entry6_TimMin, Macro198_Entry6_TimSec, Macro198_Entry6_Protocol, 0, 0, 0, 0,
		         Macro198_Entry7_DelayMin, Macro198_Entry7_DelaySec, Macro198_Entry7_TimMin, Macro198_Entry7_TimSec, Macro198_Entry7_Protocol, 0, 0, 0, 0,
		         Macro198_Entry8_DelayMin, Macro198_Entry8_DelaySec, Macro198_Entry8_TimMin, Macro198_Entry8_TimSec, Macro198_Entry8_Protocol, 0, 0, 0, 0,
		         Macro198_Entry9_DelayMin, Macro198_Entry9_DelaySec, Macro198_Entry9_TimMin, Macro198_Entry9_TimSec, Macro198_Entry9_Protocol, 0, 0, 0, 0,
		         Macro198_Entry10_DelayMin, Macro198_Entry10_DelaySec, Macro198_Entry10_TimMin, Macro198_Entry10_TimSec, Macro198_Entry10_Protocol, 0, 0, 0, 0,
		         Macro198_Entry11_DelayMin, Macro198_Entry11_DelaySec, Macro198_Entry11_TimMin, Macro198_Entry11_TimSec, Macro198_Entry11_Protocol, 0, 0, 0, 0,
		         Macro198_Entry12_DelayMin, Macro198_Entry12_DelaySec, Macro198_Entry12_TimMin, Macro198_Entry12_TimSec, Macro198_Entry12_Protocol, 0, 0, 0, 0,
		         Macro198_Entry13_DelayMin, Macro198_Entry13_DelaySec, Macro198_Entry13_TimMin, Macro198_Entry13_TimSec, Macro198_Entry13_Protocol, 0, 0, 0, 0,
		         Macro198_Entry14_DelayMin, Macro198_Entry14_DelaySec, Macro198_Entry14_TimMin, Macro198_Entry14_TimSec, Macro198_Entry14_Protocol, 0, 0, 0, 0,
		         Macro198_Entry15_DelayMin, Macro198_Entry15_DelaySec, Macro198_Entry15_TimMin, Macro198_Entry15_TimSec, Macro198_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR198_STRING};

const struct super_macro Macro199 = {Macro199_NumEntries,
		         Macro199_Entry1_DelayMin, Macro199_Entry1_DelaySec, Macro199_Entry1_TimMin, Macro199_Entry1_TimSec, Macro199_Entry1_Protocol, 0, 0, 0, 0,
		         Macro199_Entry2_DelayMin, Macro199_Entry2_DelaySec, Macro199_Entry2_TimMin, Macro199_Entry2_TimSec, Macro199_Entry2_Protocol, 0, 0, 0, 0,
		         Macro199_Entry3_DelayMin, Macro199_Entry3_DelaySec, Macro199_Entry3_TimMin, Macro199_Entry3_TimSec, Macro199_Entry3_Protocol, 0, 0, 0, 0,
		         Macro199_Entry4_DelayMin, Macro199_Entry4_DelaySec, Macro199_Entry4_TimMin, Macro199_Entry4_TimSec, Macro199_Entry4_Protocol, 0, 0, 0, 0,
		         Macro199_Entry5_DelayMin, Macro199_Entry5_DelaySec, Macro199_Entry5_TimMin, Macro199_Entry5_TimSec, Macro199_Entry5_Protocol, 0, 0, 0, 0,
		         Macro199_Entry6_DelayMin, Macro199_Entry6_DelaySec, Macro199_Entry6_TimMin, Macro199_Entry6_TimSec, Macro199_Entry6_Protocol, 0, 0, 0, 0,
		         Macro199_Entry7_DelayMin, Macro199_Entry7_DelaySec, Macro199_Entry7_TimMin, Macro199_Entry7_TimSec, Macro199_Entry7_Protocol, 0, 0, 0, 0,
		         Macro199_Entry8_DelayMin, Macro199_Entry8_DelaySec, Macro199_Entry8_TimMin, Macro199_Entry8_TimSec, Macro199_Entry8_Protocol, 0, 0, 0, 0,
		         Macro199_Entry9_DelayMin, Macro199_Entry9_DelaySec, Macro199_Entry9_TimMin, Macro199_Entry9_TimSec, Macro199_Entry9_Protocol, 0, 0, 0, 0,
		         Macro199_Entry10_DelayMin, Macro199_Entry10_DelaySec, Macro199_Entry10_TimMin, Macro199_Entry10_TimSec, Macro199_Entry10_Protocol, 0, 0, 0, 0,
		         Macro199_Entry11_DelayMin, Macro199_Entry11_DelaySec, Macro199_Entry11_TimMin, Macro199_Entry11_TimSec, Macro199_Entry11_Protocol, 0, 0, 0, 0,
		         Macro199_Entry12_DelayMin, Macro199_Entry12_DelaySec, Macro199_Entry12_TimMin, Macro199_Entry12_TimSec, Macro199_Entry12_Protocol, 0, 0, 0, 0,
		         Macro199_Entry13_DelayMin, Macro199_Entry13_DelaySec, Macro199_Entry13_TimMin, Macro199_Entry13_TimSec, Macro199_Entry13_Protocol, 0, 0, 0, 0,
		         Macro199_Entry14_DelayMin, Macro199_Entry14_DelaySec, Macro199_Entry14_TimMin, Macro199_Entry14_TimSec, Macro199_Entry14_Protocol, 0, 0, 0, 0,
		         Macro199_Entry15_DelayMin, Macro199_Entry15_DelaySec, Macro199_Entry15_TimMin, Macro199_Entry15_TimSec, Macro199_Entry15_Protocol, 0, 0, 0, 0,
				 SUPR199_STRING}; */
//Personal Macro Definitions
#else
const struct super_macro Macro00 = {PMacro00_NumEntries,
		         PMacro00_Entry1_DelayMin, PMacro00_Entry1_DelaySec, PMacro00_Entry1_TimMin, PMacro00_Entry1_TimSec, PMacro00_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro00_Entry2_DelayMin, PMacro00_Entry2_DelaySec, PMacro00_Entry2_TimMin, PMacro00_Entry2_TimSec, PMacro00_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro00_Entry3_DelayMin, PMacro00_Entry3_DelaySec, PMacro00_Entry3_TimMin, PMacro00_Entry3_TimSec, PMacro00_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro00_Entry4_DelayMin, PMacro00_Entry4_DelaySec, PMacro00_Entry4_TimMin, PMacro00_Entry4_TimSec, PMacro00_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro00_Entry5_DelayMin, PMacro00_Entry5_DelaySec, PMacro00_Entry5_TimMin, PMacro00_Entry5_TimSec, PMacro00_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro00_Entry6_DelayMin, PMacro00_Entry6_DelaySec, PMacro00_Entry6_TimMin, PMacro00_Entry6_TimSec, PMacro00_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro00_Entry7_DelayMin, PMacro00_Entry7_DelaySec, PMacro00_Entry7_TimMin, PMacro00_Entry7_TimSec, PMacro00_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro00_Entry8_DelayMin, PMacro00_Entry8_DelaySec, PMacro00_Entry8_TimMin, PMacro00_Entry8_TimSec, PMacro00_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro00_Entry9_DelayMin, PMacro00_Entry9_DelaySec, PMacro00_Entry9_TimMin, PMacro00_Entry9_TimSec, PMacro00_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro00_Entry10_DelayMin, PMacro00_Entry10_DelaySec, PMacro00_Entry10_TimMin, PMacro00_Entry10_TimSec, PMacro00_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro00_Entry11_DelayMin, PMacro00_Entry11_DelaySec, PMacro00_Entry11_TimMin, PMacro00_Entry11_TimSec, PMacro00_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro00_Entry12_DelayMin, PMacro00_Entry12_DelaySec, PMacro00_Entry12_TimMin, PMacro00_Entry12_TimSec, PMacro00_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro00_Entry13_DelayMin, PMacro00_Entry13_DelaySec, PMacro00_Entry13_TimMin, PMacro00_Entry13_TimSec, PMacro00_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro00_Entry14_DelayMin, PMacro00_Entry14_DelaySec, PMacro00_Entry14_TimMin, PMacro00_Entry14_TimSec, PMacro00_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro00_Entry15_DelayMin, PMacro00_Entry15_DelaySec, PMacro00_Entry15_TimMin, PMacro00_Entry15_TimSec, PMacro00_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR00_STRING};

const struct super_macro Macro01 = {PMacro01_NumEntries,
		         PMacro01_Entry1_DelayMin, PMacro01_Entry1_DelaySec, PMacro01_Entry1_TimMin, PMacro01_Entry1_TimSec, PMacro01_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro01_Entry2_DelayMin, PMacro01_Entry2_DelaySec, PMacro01_Entry2_TimMin, PMacro01_Entry2_TimSec, PMacro01_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro01_Entry3_DelayMin, PMacro01_Entry3_DelaySec, PMacro01_Entry3_TimMin, PMacro01_Entry3_TimSec, PMacro01_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro01_Entry4_DelayMin, PMacro01_Entry4_DelaySec, PMacro01_Entry4_TimMin, PMacro01_Entry4_TimSec, PMacro01_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro01_Entry5_DelayMin, PMacro01_Entry5_DelaySec, PMacro01_Entry5_TimMin, PMacro01_Entry5_TimSec, PMacro01_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro01_Entry6_DelayMin, PMacro01_Entry6_DelaySec, PMacro01_Entry6_TimMin, PMacro01_Entry6_TimSec, PMacro01_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro01_Entry7_DelayMin, PMacro01_Entry7_DelaySec, PMacro01_Entry7_TimMin, PMacro01_Entry7_TimSec, PMacro01_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro01_Entry8_DelayMin, PMacro01_Entry8_DelaySec, PMacro01_Entry8_TimMin, PMacro01_Entry8_TimSec, PMacro01_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro01_Entry9_DelayMin, PMacro01_Entry9_DelaySec, PMacro01_Entry9_TimMin, PMacro01_Entry9_TimSec, PMacro01_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro01_Entry10_DelayMin, PMacro01_Entry10_DelaySec, PMacro01_Entry10_TimMin, PMacro01_Entry10_TimSec, PMacro01_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro01_Entry11_DelayMin, PMacro01_Entry11_DelaySec, PMacro01_Entry11_TimMin, PMacro01_Entry11_TimSec, PMacro01_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro01_Entry12_DelayMin, PMacro01_Entry12_DelaySec, PMacro01_Entry12_TimMin, PMacro01_Entry12_TimSec, PMacro01_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro01_Entry13_DelayMin, PMacro01_Entry13_DelaySec, PMacro01_Entry13_TimMin, PMacro01_Entry13_TimSec, PMacro01_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro01_Entry14_DelayMin, PMacro01_Entry14_DelaySec, PMacro01_Entry14_TimMin, PMacro01_Entry14_TimSec, PMacro01_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro01_Entry15_DelayMin, PMacro01_Entry15_DelaySec, PMacro01_Entry15_TimMin, PMacro01_Entry15_TimSec, PMacro01_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR01_STRING};

const struct super_macro Macro02 = {PMacro02_NumEntries,
		         PMacro02_Entry1_DelayMin, PMacro02_Entry1_DelaySec, PMacro02_Entry1_TimMin, PMacro02_Entry1_TimSec, PMacro02_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro02_Entry2_DelayMin, PMacro02_Entry2_DelaySec, PMacro02_Entry2_TimMin, PMacro02_Entry2_TimSec, PMacro02_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro02_Entry3_DelayMin, PMacro02_Entry3_DelaySec, PMacro02_Entry3_TimMin, PMacro02_Entry3_TimSec, PMacro02_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro02_Entry4_DelayMin, PMacro02_Entry4_DelaySec, PMacro02_Entry4_TimMin, PMacro02_Entry4_TimSec, PMacro02_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro02_Entry5_DelayMin, PMacro02_Entry5_DelaySec, PMacro02_Entry5_TimMin, PMacro02_Entry5_TimSec, PMacro02_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro02_Entry6_DelayMin, PMacro02_Entry6_DelaySec, PMacro02_Entry6_TimMin, PMacro02_Entry6_TimSec, PMacro02_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro02_Entry7_DelayMin, PMacro02_Entry7_DelaySec, PMacro02_Entry7_TimMin, PMacro02_Entry7_TimSec, PMacro02_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro02_Entry8_DelayMin, PMacro02_Entry8_DelaySec, PMacro02_Entry8_TimMin, PMacro02_Entry8_TimSec, PMacro02_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro02_Entry9_DelayMin, PMacro02_Entry9_DelaySec, PMacro02_Entry9_TimMin, PMacro02_Entry9_TimSec, PMacro02_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro02_Entry10_DelayMin, PMacro02_Entry10_DelaySec, PMacro02_Entry10_TimMin, PMacro02_Entry10_TimSec, PMacro02_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro02_Entry11_DelayMin, PMacro02_Entry11_DelaySec, PMacro02_Entry11_TimMin, PMacro02_Entry11_TimSec, PMacro02_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro02_Entry12_DelayMin, PMacro02_Entry12_DelaySec, PMacro02_Entry12_TimMin, PMacro02_Entry12_TimSec, PMacro02_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro02_Entry13_DelayMin, PMacro02_Entry13_DelaySec, PMacro02_Entry13_TimMin, PMacro02_Entry13_TimSec, PMacro02_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro02_Entry14_DelayMin, PMacro02_Entry14_DelaySec, PMacro02_Entry14_TimMin, PMacro02_Entry14_TimSec, PMacro02_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro02_Entry15_DelayMin, PMacro02_Entry15_DelaySec, PMacro02_Entry15_TimMin, PMacro02_Entry15_TimSec, PMacro02_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR02_STRING};

const struct super_macro Macro03 = {PMacro03_NumEntries,
		         PMacro03_Entry1_DelayMin, PMacro03_Entry1_DelaySec, PMacro03_Entry1_TimMin, PMacro03_Entry1_TimSec, PMacro03_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro03_Entry2_DelayMin, PMacro03_Entry2_DelaySec, PMacro03_Entry2_TimMin, PMacro03_Entry2_TimSec, PMacro03_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro03_Entry3_DelayMin, PMacro03_Entry3_DelaySec, PMacro03_Entry3_TimMin, PMacro03_Entry3_TimSec, PMacro03_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro03_Entry4_DelayMin, PMacro03_Entry4_DelaySec, PMacro03_Entry4_TimMin, PMacro03_Entry4_TimSec, PMacro03_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro03_Entry5_DelayMin, PMacro03_Entry5_DelaySec, PMacro03_Entry5_TimMin, PMacro03_Entry5_TimSec, PMacro03_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro03_Entry6_DelayMin, PMacro03_Entry6_DelaySec, PMacro03_Entry6_TimMin, PMacro03_Entry6_TimSec, PMacro03_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro03_Entry7_DelayMin, PMacro03_Entry7_DelaySec, PMacro03_Entry7_TimMin, PMacro03_Entry7_TimSec, PMacro03_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro03_Entry8_DelayMin, PMacro03_Entry8_DelaySec, PMacro03_Entry8_TimMin, PMacro03_Entry8_TimSec, PMacro03_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro03_Entry9_DelayMin, PMacro03_Entry9_DelaySec, PMacro03_Entry9_TimMin, PMacro03_Entry9_TimSec, PMacro03_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro03_Entry10_DelayMin, PMacro03_Entry10_DelaySec, PMacro03_Entry10_TimMin, PMacro03_Entry10_TimSec, PMacro03_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro03_Entry11_DelayMin, PMacro03_Entry11_DelaySec, PMacro03_Entry11_TimMin, PMacro03_Entry11_TimSec, PMacro03_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro03_Entry12_DelayMin, PMacro03_Entry12_DelaySec, PMacro03_Entry12_TimMin, PMacro03_Entry12_TimSec, PMacro03_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro03_Entry13_DelayMin, PMacro03_Entry13_DelaySec, PMacro03_Entry13_TimMin, PMacro03_Entry13_TimSec, PMacro03_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro03_Entry14_DelayMin, PMacro03_Entry14_DelaySec, PMacro03_Entry14_TimMin, PMacro03_Entry14_TimSec, PMacro03_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro03_Entry15_DelayMin, PMacro03_Entry15_DelaySec, PMacro03_Entry15_TimMin, PMacro03_Entry15_TimSec, PMacro03_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR03_STRING};

const struct super_macro Macro04 = {PMacro04_NumEntries,
		         PMacro04_Entry1_DelayMin, PMacro04_Entry1_DelaySec, PMacro04_Entry1_TimMin, PMacro04_Entry1_TimSec, PMacro04_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro04_Entry2_DelayMin, PMacro04_Entry2_DelaySec, PMacro04_Entry2_TimMin, PMacro04_Entry2_TimSec, PMacro04_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro04_Entry3_DelayMin, PMacro04_Entry3_DelaySec, PMacro04_Entry3_TimMin, PMacro04_Entry3_TimSec, PMacro04_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro04_Entry4_DelayMin, PMacro04_Entry4_DelaySec, PMacro04_Entry4_TimMin, PMacro04_Entry4_TimSec, PMacro04_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro04_Entry5_DelayMin, PMacro04_Entry5_DelaySec, PMacro04_Entry5_TimMin, PMacro04_Entry5_TimSec, PMacro04_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro04_Entry6_DelayMin, PMacro04_Entry6_DelaySec, PMacro04_Entry6_TimMin, PMacro04_Entry6_TimSec, PMacro04_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro04_Entry7_DelayMin, PMacro04_Entry7_DelaySec, PMacro04_Entry7_TimMin, PMacro04_Entry7_TimSec, PMacro04_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro04_Entry8_DelayMin, PMacro04_Entry8_DelaySec, PMacro04_Entry8_TimMin, PMacro04_Entry8_TimSec, PMacro04_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro04_Entry9_DelayMin, PMacro04_Entry9_DelaySec, PMacro04_Entry9_TimMin, PMacro04_Entry9_TimSec, PMacro04_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro04_Entry10_DelayMin, PMacro04_Entry10_DelaySec, PMacro04_Entry10_TimMin, PMacro04_Entry10_TimSec, PMacro04_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro04_Entry11_DelayMin, PMacro04_Entry11_DelaySec, PMacro04_Entry11_TimMin, PMacro04_Entry11_TimSec, PMacro04_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro04_Entry12_DelayMin, PMacro04_Entry12_DelaySec, PMacro04_Entry12_TimMin, PMacro04_Entry12_TimSec, PMacro04_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro04_Entry13_DelayMin, PMacro04_Entry13_DelaySec, PMacro04_Entry13_TimMin, PMacro04_Entry13_TimSec, PMacro04_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro04_Entry14_DelayMin, PMacro04_Entry14_DelaySec, PMacro04_Entry14_TimMin, PMacro04_Entry14_TimSec, PMacro04_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro04_Entry15_DelayMin, PMacro04_Entry15_DelaySec, PMacro04_Entry15_TimMin, PMacro04_Entry15_TimSec, PMacro04_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR04_STRING};

const struct super_macro Macro05 = {PMacro05_NumEntries,
		         PMacro05_Entry1_DelayMin, PMacro05_Entry1_DelaySec, PMacro05_Entry1_TimMin, PMacro05_Entry1_TimSec, PMacro05_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro05_Entry2_DelayMin, PMacro05_Entry2_DelaySec, PMacro05_Entry2_TimMin, PMacro05_Entry2_TimSec, PMacro05_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro05_Entry3_DelayMin, PMacro05_Entry3_DelaySec, PMacro05_Entry3_TimMin, PMacro05_Entry3_TimSec, PMacro05_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro05_Entry4_DelayMin, PMacro05_Entry4_DelaySec, PMacro05_Entry4_TimMin, PMacro05_Entry4_TimSec, PMacro05_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro05_Entry5_DelayMin, PMacro05_Entry5_DelaySec, PMacro05_Entry5_TimMin, PMacro05_Entry5_TimSec, PMacro05_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro05_Entry6_DelayMin, PMacro05_Entry6_DelaySec, PMacro05_Entry6_TimMin, PMacro05_Entry6_TimSec, PMacro05_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro05_Entry7_DelayMin, PMacro05_Entry7_DelaySec, PMacro05_Entry7_TimMin, PMacro05_Entry7_TimSec, PMacro05_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro05_Entry8_DelayMin, PMacro05_Entry8_DelaySec, PMacro05_Entry8_TimMin, PMacro05_Entry8_TimSec, PMacro05_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro05_Entry9_DelayMin, PMacro05_Entry9_DelaySec, PMacro05_Entry9_TimMin, PMacro05_Entry9_TimSec, PMacro05_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro05_Entry10_DelayMin, PMacro05_Entry10_DelaySec, PMacro05_Entry10_TimMin, PMacro05_Entry10_TimSec, PMacro05_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro05_Entry11_DelayMin, PMacro05_Entry11_DelaySec, PMacro05_Entry11_TimMin, PMacro05_Entry11_TimSec, PMacro05_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro05_Entry12_DelayMin, PMacro05_Entry12_DelaySec, PMacro05_Entry12_TimMin, PMacro05_Entry12_TimSec, PMacro05_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro05_Entry13_DelayMin, PMacro05_Entry13_DelaySec, PMacro05_Entry13_TimMin, PMacro05_Entry13_TimSec, PMacro05_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro05_Entry14_DelayMin, PMacro05_Entry14_DelaySec, PMacro05_Entry14_TimMin, PMacro05_Entry14_TimSec, PMacro05_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro05_Entry15_DelayMin, PMacro05_Entry15_DelaySec, PMacro05_Entry15_TimMin, PMacro05_Entry15_TimSec, PMacro05_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR05_STRING};

const struct super_macro Macro06 = {PMacro06_NumEntries,
		         PMacro06_Entry1_DelayMin, PMacro06_Entry1_DelaySec, PMacro06_Entry1_TimMin, PMacro06_Entry1_TimSec, PMacro06_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro06_Entry2_DelayMin, PMacro06_Entry2_DelaySec, PMacro06_Entry2_TimMin, PMacro06_Entry2_TimSec, PMacro06_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro06_Entry3_DelayMin, PMacro06_Entry3_DelaySec, PMacro06_Entry3_TimMin, PMacro06_Entry3_TimSec, PMacro06_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro06_Entry4_DelayMin, PMacro06_Entry4_DelaySec, PMacro06_Entry4_TimMin, PMacro06_Entry4_TimSec, PMacro06_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro06_Entry5_DelayMin, PMacro06_Entry5_DelaySec, PMacro06_Entry5_TimMin, PMacro06_Entry5_TimSec, PMacro06_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro06_Entry6_DelayMin, PMacro06_Entry6_DelaySec, PMacro06_Entry6_TimMin, PMacro06_Entry6_TimSec, PMacro06_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro06_Entry7_DelayMin, PMacro06_Entry7_DelaySec, PMacro06_Entry7_TimMin, PMacro06_Entry7_TimSec, PMacro06_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro06_Entry8_DelayMin, PMacro06_Entry8_DelaySec, PMacro06_Entry8_TimMin, PMacro06_Entry8_TimSec, PMacro06_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro06_Entry9_DelayMin, PMacro06_Entry9_DelaySec, PMacro06_Entry9_TimMin, PMacro06_Entry9_TimSec, PMacro06_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro06_Entry10_DelayMin, PMacro06_Entry10_DelaySec, PMacro06_Entry10_TimMin, PMacro06_Entry10_TimSec, PMacro06_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro06_Entry11_DelayMin, PMacro06_Entry11_DelaySec, PMacro06_Entry11_TimMin, PMacro06_Entry11_TimSec, PMacro06_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro06_Entry12_DelayMin, PMacro06_Entry12_DelaySec, PMacro06_Entry12_TimMin, PMacro06_Entry12_TimSec, PMacro06_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro06_Entry13_DelayMin, PMacro06_Entry13_DelaySec, PMacro06_Entry13_TimMin, PMacro06_Entry13_TimSec, PMacro06_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro06_Entry14_DelayMin, PMacro06_Entry14_DelaySec, PMacro06_Entry14_TimMin, PMacro06_Entry14_TimSec, PMacro06_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro06_Entry15_DelayMin, PMacro06_Entry15_DelaySec, PMacro06_Entry15_TimMin, PMacro06_Entry15_TimSec, PMacro06_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR06_STRING};

const struct super_macro Macro07 = {PMacro07_NumEntries,
		         PMacro07_Entry1_DelayMin, PMacro07_Entry1_DelaySec, PMacro07_Entry1_TimMin, PMacro07_Entry1_TimSec, PMacro07_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro07_Entry2_DelayMin, PMacro07_Entry2_DelaySec, PMacro07_Entry2_TimMin, PMacro07_Entry2_TimSec, PMacro07_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro07_Entry3_DelayMin, PMacro07_Entry3_DelaySec, PMacro07_Entry3_TimMin, PMacro07_Entry3_TimSec, PMacro07_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro07_Entry4_DelayMin, PMacro07_Entry4_DelaySec, PMacro07_Entry4_TimMin, PMacro07_Entry4_TimSec, PMacro07_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro07_Entry5_DelayMin, PMacro07_Entry5_DelaySec, PMacro07_Entry5_TimMin, PMacro07_Entry5_TimSec, PMacro07_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro07_Entry6_DelayMin, PMacro07_Entry6_DelaySec, PMacro07_Entry6_TimMin, PMacro07_Entry6_TimSec, PMacro07_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro07_Entry7_DelayMin, PMacro07_Entry7_DelaySec, PMacro07_Entry7_TimMin, PMacro07_Entry7_TimSec, PMacro07_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro07_Entry8_DelayMin, PMacro07_Entry8_DelaySec, PMacro07_Entry8_TimMin, PMacro07_Entry8_TimSec, PMacro07_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro07_Entry9_DelayMin, PMacro07_Entry9_DelaySec, PMacro07_Entry9_TimMin, PMacro07_Entry9_TimSec, PMacro07_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro07_Entry10_DelayMin, PMacro07_Entry10_DelaySec, PMacro07_Entry10_TimMin, PMacro07_Entry10_TimSec, PMacro07_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro07_Entry11_DelayMin, PMacro07_Entry11_DelaySec, PMacro07_Entry11_TimMin, PMacro07_Entry11_TimSec, PMacro07_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro07_Entry12_DelayMin, PMacro07_Entry12_DelaySec, PMacro07_Entry12_TimMin, PMacro07_Entry12_TimSec, PMacro07_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro07_Entry13_DelayMin, PMacro07_Entry13_DelaySec, PMacro07_Entry13_TimMin, PMacro07_Entry13_TimSec, PMacro07_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro07_Entry14_DelayMin, PMacro07_Entry14_DelaySec, PMacro07_Entry14_TimMin, PMacro07_Entry14_TimSec, PMacro07_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro07_Entry15_DelayMin, PMacro07_Entry15_DelaySec, PMacro07_Entry15_TimMin, PMacro07_Entry15_TimSec, PMacro07_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR07_STRING};

const struct super_macro Macro08 = {PMacro08_NumEntries,
		         PMacro08_Entry1_DelayMin, PMacro08_Entry1_DelaySec, PMacro08_Entry1_TimMin, PMacro08_Entry1_TimSec, PMacro08_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro08_Entry2_DelayMin, PMacro08_Entry2_DelaySec, PMacro08_Entry2_TimMin, PMacro08_Entry2_TimSec, PMacro08_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro08_Entry3_DelayMin, PMacro08_Entry3_DelaySec, PMacro08_Entry3_TimMin, PMacro08_Entry3_TimSec, PMacro08_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro08_Entry4_DelayMin, PMacro08_Entry4_DelaySec, PMacro08_Entry4_TimMin, PMacro08_Entry4_TimSec, PMacro08_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro08_Entry5_DelayMin, PMacro08_Entry5_DelaySec, PMacro08_Entry5_TimMin, PMacro08_Entry5_TimSec, PMacro08_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro08_Entry6_DelayMin, PMacro08_Entry6_DelaySec, PMacro08_Entry6_TimMin, PMacro08_Entry6_TimSec, PMacro08_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro08_Entry7_DelayMin, PMacro08_Entry7_DelaySec, PMacro08_Entry7_TimMin, PMacro08_Entry7_TimSec, PMacro08_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro08_Entry8_DelayMin, PMacro08_Entry8_DelaySec, PMacro08_Entry8_TimMin, PMacro08_Entry8_TimSec, PMacro08_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro08_Entry9_DelayMin, PMacro08_Entry9_DelaySec, PMacro08_Entry9_TimMin, PMacro08_Entry9_TimSec, PMacro08_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro08_Entry10_DelayMin, PMacro08_Entry10_DelaySec, PMacro08_Entry10_TimMin, PMacro08_Entry10_TimSec, PMacro08_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro08_Entry11_DelayMin, PMacro08_Entry11_DelaySec, PMacro08_Entry11_TimMin, PMacro08_Entry11_TimSec, PMacro08_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro08_Entry12_DelayMin, PMacro08_Entry12_DelaySec, PMacro08_Entry12_TimMin, PMacro08_Entry12_TimSec, PMacro08_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro08_Entry13_DelayMin, PMacro08_Entry13_DelaySec, PMacro08_Entry13_TimMin, PMacro08_Entry13_TimSec, PMacro08_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro08_Entry14_DelayMin, PMacro08_Entry14_DelaySec, PMacro08_Entry14_TimMin, PMacro08_Entry14_TimSec, PMacro08_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro08_Entry15_DelayMin, PMacro08_Entry15_DelaySec, PMacro08_Entry15_TimMin, PMacro08_Entry15_TimSec, PMacro08_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR08_STRING};

const struct super_macro Macro09 = {PMacro09_NumEntries,
		         PMacro09_Entry1_DelayMin, PMacro09_Entry1_DelaySec, PMacro09_Entry1_TimMin, PMacro09_Entry1_TimSec, PMacro09_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro09_Entry2_DelayMin, PMacro09_Entry2_DelaySec, PMacro09_Entry2_TimMin, PMacro09_Entry2_TimSec, PMacro09_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro09_Entry3_DelayMin, PMacro09_Entry3_DelaySec, PMacro09_Entry3_TimMin, PMacro09_Entry3_TimSec, PMacro09_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro09_Entry4_DelayMin, PMacro09_Entry4_DelaySec, PMacro09_Entry4_TimMin, PMacro09_Entry4_TimSec, PMacro09_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro09_Entry5_DelayMin, PMacro09_Entry5_DelaySec, PMacro09_Entry5_TimMin, PMacro09_Entry5_TimSec, PMacro09_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro09_Entry6_DelayMin, PMacro09_Entry6_DelaySec, PMacro09_Entry6_TimMin, PMacro09_Entry6_TimSec, PMacro09_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro09_Entry7_DelayMin, PMacro09_Entry7_DelaySec, PMacro09_Entry7_TimMin, PMacro09_Entry7_TimSec, PMacro09_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro09_Entry8_DelayMin, PMacro09_Entry8_DelaySec, PMacro09_Entry8_TimMin, PMacro09_Entry8_TimSec, PMacro09_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro09_Entry9_DelayMin, PMacro09_Entry9_DelaySec, PMacro09_Entry9_TimMin, PMacro09_Entry9_TimSec, PMacro09_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro09_Entry10_DelayMin, PMacro09_Entry10_DelaySec, PMacro09_Entry10_TimMin, PMacro09_Entry10_TimSec, PMacro09_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro09_Entry11_DelayMin, PMacro09_Entry11_DelaySec, PMacro09_Entry11_TimMin, PMacro09_Entry11_TimSec, PMacro09_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro09_Entry12_DelayMin, PMacro09_Entry12_DelaySec, PMacro09_Entry12_TimMin, PMacro09_Entry12_TimSec, PMacro09_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro09_Entry13_DelayMin, PMacro09_Entry13_DelaySec, PMacro09_Entry13_TimMin, PMacro09_Entry13_TimSec, PMacro09_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro09_Entry14_DelayMin, PMacro09_Entry14_DelaySec, PMacro09_Entry14_TimMin, PMacro09_Entry14_TimSec, PMacro09_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro09_Entry15_DelayMin, PMacro09_Entry15_DelaySec, PMacro09_Entry15_TimMin, PMacro09_Entry15_TimSec, PMacro09_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR09_STRING};

const struct super_macro Macro10 = {PMacro10_NumEntries,
		         PMacro10_Entry1_DelayMin, PMacro10_Entry1_DelaySec, PMacro10_Entry1_TimMin, PMacro10_Entry1_TimSec, PMacro10_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro10_Entry2_DelayMin, PMacro10_Entry2_DelaySec, PMacro10_Entry2_TimMin, PMacro10_Entry2_TimSec, PMacro10_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro10_Entry3_DelayMin, PMacro10_Entry3_DelaySec, PMacro10_Entry3_TimMin, PMacro10_Entry3_TimSec, PMacro10_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro10_Entry4_DelayMin, PMacro10_Entry4_DelaySec, PMacro10_Entry4_TimMin, PMacro10_Entry4_TimSec, PMacro10_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro10_Entry5_DelayMin, PMacro10_Entry5_DelaySec, PMacro10_Entry5_TimMin, PMacro10_Entry5_TimSec, PMacro10_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro10_Entry6_DelayMin, PMacro10_Entry6_DelaySec, PMacro10_Entry6_TimMin, PMacro10_Entry6_TimSec, PMacro10_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro10_Entry7_DelayMin, PMacro10_Entry7_DelaySec, PMacro10_Entry7_TimMin, PMacro10_Entry7_TimSec, PMacro10_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro10_Entry8_DelayMin, PMacro10_Entry8_DelaySec, PMacro10_Entry8_TimMin, PMacro10_Entry8_TimSec, PMacro10_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro10_Entry9_DelayMin, PMacro10_Entry9_DelaySec, PMacro10_Entry9_TimMin, PMacro10_Entry9_TimSec, PMacro10_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro10_Entry10_DelayMin, PMacro10_Entry10_DelaySec, PMacro10_Entry10_TimMin, PMacro10_Entry10_TimSec, PMacro10_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro10_Entry11_DelayMin, PMacro10_Entry11_DelaySec, PMacro10_Entry11_TimMin, PMacro10_Entry11_TimSec, PMacro10_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro10_Entry12_DelayMin, PMacro10_Entry12_DelaySec, PMacro10_Entry12_TimMin, PMacro10_Entry12_TimSec, PMacro10_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro10_Entry13_DelayMin, PMacro10_Entry13_DelaySec, PMacro10_Entry13_TimMin, PMacro10_Entry13_TimSec, PMacro10_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro10_Entry14_DelayMin, PMacro10_Entry14_DelaySec, PMacro10_Entry14_TimMin, PMacro10_Entry14_TimSec, PMacro10_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro10_Entry15_DelayMin, PMacro10_Entry15_DelaySec, PMacro10_Entry15_TimMin, PMacro10_Entry15_TimSec, PMacro10_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR10_STRING};

const struct super_macro Macro11 = {PMacro11_NumEntries,
		         PMacro11_Entry1_DelayMin, PMacro11_Entry1_DelaySec, PMacro11_Entry1_TimMin, PMacro11_Entry1_TimSec, PMacro11_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro11_Entry2_DelayMin, PMacro11_Entry2_DelaySec, PMacro11_Entry2_TimMin, PMacro11_Entry2_TimSec, PMacro11_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro11_Entry3_DelayMin, PMacro11_Entry3_DelaySec, PMacro11_Entry3_TimMin, PMacro11_Entry3_TimSec, PMacro11_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro11_Entry4_DelayMin, PMacro11_Entry4_DelaySec, PMacro11_Entry4_TimMin, PMacro11_Entry4_TimSec, PMacro11_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro11_Entry5_DelayMin, PMacro11_Entry5_DelaySec, PMacro11_Entry5_TimMin, PMacro11_Entry5_TimSec, PMacro11_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro11_Entry6_DelayMin, PMacro11_Entry6_DelaySec, PMacro11_Entry6_TimMin, PMacro11_Entry6_TimSec, PMacro11_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro11_Entry7_DelayMin, PMacro11_Entry7_DelaySec, PMacro11_Entry7_TimMin, PMacro11_Entry7_TimSec, PMacro11_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro11_Entry8_DelayMin, PMacro11_Entry8_DelaySec, PMacro11_Entry8_TimMin, PMacro11_Entry8_TimSec, PMacro11_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro11_Entry9_DelayMin, PMacro11_Entry9_DelaySec, PMacro11_Entry9_TimMin, PMacro11_Entry9_TimSec, PMacro11_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro11_Entry10_DelayMin, PMacro11_Entry10_DelaySec, PMacro11_Entry10_TimMin, PMacro11_Entry10_TimSec, PMacro11_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro11_Entry11_DelayMin, PMacro11_Entry11_DelaySec, PMacro11_Entry11_TimMin, PMacro11_Entry11_TimSec, PMacro11_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro11_Entry12_DelayMin, PMacro11_Entry12_DelaySec, PMacro11_Entry12_TimMin, PMacro11_Entry12_TimSec, PMacro11_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro11_Entry13_DelayMin, PMacro11_Entry13_DelaySec, PMacro11_Entry13_TimMin, PMacro11_Entry13_TimSec, PMacro11_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro11_Entry14_DelayMin, PMacro11_Entry14_DelaySec, PMacro11_Entry14_TimMin, PMacro11_Entry14_TimSec, PMacro11_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro11_Entry15_DelayMin, PMacro11_Entry15_DelaySec, PMacro11_Entry15_TimMin, PMacro11_Entry15_TimSec, PMacro11_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR11_STRING};

const struct super_macro Macro12 = {PMacro12_NumEntries,
		         PMacro12_Entry1_DelayMin, PMacro12_Entry1_DelaySec, PMacro12_Entry1_TimMin, PMacro12_Entry1_TimSec, PMacro12_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro12_Entry2_DelayMin, PMacro12_Entry2_DelaySec, PMacro12_Entry2_TimMin, PMacro12_Entry2_TimSec, PMacro12_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro12_Entry3_DelayMin, PMacro12_Entry3_DelaySec, PMacro12_Entry3_TimMin, PMacro12_Entry3_TimSec, PMacro12_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro12_Entry4_DelayMin, PMacro12_Entry4_DelaySec, PMacro12_Entry4_TimMin, PMacro12_Entry4_TimSec, PMacro12_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro12_Entry5_DelayMin, PMacro12_Entry5_DelaySec, PMacro12_Entry5_TimMin, PMacro12_Entry5_TimSec, PMacro12_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro12_Entry6_DelayMin, PMacro12_Entry6_DelaySec, PMacro12_Entry6_TimMin, PMacro12_Entry6_TimSec, PMacro12_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro12_Entry7_DelayMin, PMacro12_Entry7_DelaySec, PMacro12_Entry7_TimMin, PMacro12_Entry7_TimSec, PMacro12_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro12_Entry8_DelayMin, PMacro12_Entry8_DelaySec, PMacro12_Entry8_TimMin, PMacro12_Entry8_TimSec, PMacro12_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro12_Entry9_DelayMin, PMacro12_Entry9_DelaySec, PMacro12_Entry9_TimMin, PMacro12_Entry9_TimSec, PMacro12_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro12_Entry10_DelayMin, PMacro12_Entry10_DelaySec, PMacro12_Entry10_TimMin, PMacro12_Entry10_TimSec, PMacro12_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro12_Entry11_DelayMin, PMacro12_Entry11_DelaySec, PMacro12_Entry11_TimMin, PMacro12_Entry11_TimSec, PMacro12_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro12_Entry12_DelayMin, PMacro12_Entry12_DelaySec, PMacro12_Entry12_TimMin, PMacro12_Entry12_TimSec, PMacro12_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro12_Entry13_DelayMin, PMacro12_Entry13_DelaySec, PMacro12_Entry13_TimMin, PMacro12_Entry13_TimSec, PMacro12_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro12_Entry14_DelayMin, PMacro12_Entry14_DelaySec, PMacro12_Entry14_TimMin, PMacro12_Entry14_TimSec, PMacro12_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro12_Entry15_DelayMin, PMacro12_Entry15_DelaySec, PMacro12_Entry15_TimMin, PMacro12_Entry15_TimSec, PMacro12_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR12_STRING};

const struct super_macro Macro13 = {PMacro13_NumEntries,
		         PMacro13_Entry1_DelayMin, PMacro13_Entry1_DelaySec, PMacro13_Entry1_TimMin, PMacro13_Entry1_TimSec, PMacro13_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro13_Entry2_DelayMin, PMacro13_Entry2_DelaySec, PMacro13_Entry2_TimMin, PMacro13_Entry2_TimSec, PMacro13_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro13_Entry3_DelayMin, PMacro13_Entry3_DelaySec, PMacro13_Entry3_TimMin, PMacro13_Entry3_TimSec, PMacro13_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro13_Entry4_DelayMin, PMacro13_Entry4_DelaySec, PMacro13_Entry4_TimMin, PMacro13_Entry4_TimSec, PMacro13_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro13_Entry5_DelayMin, PMacro13_Entry5_DelaySec, PMacro13_Entry5_TimMin, PMacro13_Entry5_TimSec, PMacro13_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro13_Entry6_DelayMin, PMacro13_Entry6_DelaySec, PMacro13_Entry6_TimMin, PMacro13_Entry6_TimSec, PMacro13_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro13_Entry7_DelayMin, PMacro13_Entry7_DelaySec, PMacro13_Entry7_TimMin, PMacro13_Entry7_TimSec, PMacro13_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro13_Entry8_DelayMin, PMacro13_Entry8_DelaySec, PMacro13_Entry8_TimMin, PMacro13_Entry8_TimSec, PMacro13_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro13_Entry9_DelayMin, PMacro13_Entry9_DelaySec, PMacro13_Entry9_TimMin, PMacro13_Entry9_TimSec, PMacro13_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro13_Entry10_DelayMin, PMacro13_Entry10_DelaySec, PMacro13_Entry10_TimMin, PMacro13_Entry10_TimSec, PMacro13_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro13_Entry11_DelayMin, PMacro13_Entry11_DelaySec, PMacro13_Entry11_TimMin, PMacro13_Entry11_TimSec, PMacro13_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro13_Entry12_DelayMin, PMacro13_Entry12_DelaySec, PMacro13_Entry12_TimMin, PMacro13_Entry12_TimSec, PMacro13_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro13_Entry13_DelayMin, PMacro13_Entry13_DelaySec, PMacro13_Entry13_TimMin, PMacro13_Entry13_TimSec, PMacro13_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro13_Entry14_DelayMin, PMacro13_Entry14_DelaySec, PMacro13_Entry14_TimMin, PMacro13_Entry14_TimSec, PMacro13_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro13_Entry15_DelayMin, PMacro13_Entry15_DelaySec, PMacro13_Entry15_TimMin, PMacro13_Entry15_TimSec, PMacro13_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR13_STRING};

const struct super_macro Macro14 = {PMacro14_NumEntries,
		         PMacro14_Entry1_DelayMin, PMacro14_Entry1_DelaySec, PMacro14_Entry1_TimMin, PMacro14_Entry1_TimSec, PMacro14_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro14_Entry2_DelayMin, PMacro14_Entry2_DelaySec, PMacro14_Entry2_TimMin, PMacro14_Entry2_TimSec, PMacro14_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro14_Entry3_DelayMin, PMacro14_Entry3_DelaySec, PMacro14_Entry3_TimMin, PMacro14_Entry3_TimSec, PMacro14_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro14_Entry4_DelayMin, PMacro14_Entry4_DelaySec, PMacro14_Entry4_TimMin, PMacro14_Entry4_TimSec, PMacro14_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro14_Entry5_DelayMin, PMacro14_Entry5_DelaySec, PMacro14_Entry5_TimMin, PMacro14_Entry5_TimSec, PMacro14_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro14_Entry6_DelayMin, PMacro14_Entry6_DelaySec, PMacro14_Entry6_TimMin, PMacro14_Entry6_TimSec, PMacro14_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro14_Entry7_DelayMin, PMacro14_Entry7_DelaySec, PMacro14_Entry7_TimMin, PMacro14_Entry7_TimSec, PMacro14_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro14_Entry8_DelayMin, PMacro14_Entry8_DelaySec, PMacro14_Entry8_TimMin, PMacro14_Entry8_TimSec, PMacro14_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro14_Entry9_DelayMin, PMacro14_Entry9_DelaySec, PMacro14_Entry9_TimMin, PMacro14_Entry9_TimSec, PMacro14_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro14_Entry10_DelayMin, PMacro14_Entry10_DelaySec, PMacro14_Entry10_TimMin, PMacro14_Entry10_TimSec, PMacro14_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro14_Entry11_DelayMin, PMacro14_Entry11_DelaySec, PMacro14_Entry11_TimMin, PMacro14_Entry11_TimSec, PMacro14_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro14_Entry12_DelayMin, PMacro14_Entry12_DelaySec, PMacro14_Entry12_TimMin, PMacro14_Entry12_TimSec, PMacro14_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro14_Entry13_DelayMin, PMacro14_Entry13_DelaySec, PMacro14_Entry13_TimMin, PMacro14_Entry13_TimSec, PMacro14_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro14_Entry14_DelayMin, PMacro14_Entry14_DelaySec, PMacro14_Entry14_TimMin, PMacro14_Entry14_TimSec, PMacro14_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro14_Entry15_DelayMin, PMacro14_Entry15_DelaySec, PMacro14_Entry15_TimMin, PMacro14_Entry15_TimSec, PMacro14_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR14_STRING};

const struct super_macro Macro15 = {PMacro15_NumEntries,
		         PMacro15_Entry1_DelayMin, PMacro15_Entry1_DelaySec, PMacro15_Entry1_TimMin, PMacro15_Entry1_TimSec, PMacro15_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro15_Entry2_DelayMin, PMacro15_Entry2_DelaySec, PMacro15_Entry2_TimMin, PMacro15_Entry2_TimSec, PMacro15_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro15_Entry3_DelayMin, PMacro15_Entry3_DelaySec, PMacro15_Entry3_TimMin, PMacro15_Entry3_TimSec, PMacro15_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro15_Entry4_DelayMin, PMacro15_Entry4_DelaySec, PMacro15_Entry4_TimMin, PMacro15_Entry4_TimSec, PMacro15_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro15_Entry5_DelayMin, PMacro15_Entry5_DelaySec, PMacro15_Entry5_TimMin, PMacro15_Entry5_TimSec, PMacro15_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro15_Entry6_DelayMin, PMacro15_Entry6_DelaySec, PMacro15_Entry6_TimMin, PMacro15_Entry6_TimSec, PMacro15_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro15_Entry7_DelayMin, PMacro15_Entry7_DelaySec, PMacro15_Entry7_TimMin, PMacro15_Entry7_TimSec, PMacro15_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro15_Entry8_DelayMin, PMacro15_Entry8_DelaySec, PMacro15_Entry8_TimMin, PMacro15_Entry8_TimSec, PMacro15_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro15_Entry9_DelayMin, PMacro15_Entry9_DelaySec, PMacro15_Entry9_TimMin, PMacro15_Entry9_TimSec, PMacro15_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro15_Entry10_DelayMin, PMacro15_Entry10_DelaySec, PMacro15_Entry10_TimMin, PMacro15_Entry10_TimSec, PMacro15_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro15_Entry11_DelayMin, PMacro15_Entry11_DelaySec, PMacro15_Entry11_TimMin, PMacro15_Entry11_TimSec, PMacro15_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro15_Entry12_DelayMin, PMacro15_Entry12_DelaySec, PMacro15_Entry12_TimMin, PMacro15_Entry12_TimSec, PMacro15_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro15_Entry13_DelayMin, PMacro15_Entry13_DelaySec, PMacro15_Entry13_TimMin, PMacro15_Entry13_TimSec, PMacro15_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro15_Entry14_DelayMin, PMacro15_Entry14_DelaySec, PMacro15_Entry14_TimMin, PMacro15_Entry14_TimSec, PMacro15_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro15_Entry15_DelayMin, PMacro15_Entry15_DelaySec, PMacro15_Entry15_TimMin, PMacro15_Entry15_TimSec, PMacro15_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR15_STRING};

const struct super_macro Macro16 = {PMacro16_NumEntries,
		         PMacro16_Entry1_DelayMin, PMacro16_Entry1_DelaySec, PMacro16_Entry1_TimMin, PMacro16_Entry1_TimSec, PMacro16_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro16_Entry2_DelayMin, PMacro16_Entry2_DelaySec, PMacro16_Entry2_TimMin, PMacro16_Entry2_TimSec, PMacro16_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro16_Entry3_DelayMin, PMacro16_Entry3_DelaySec, PMacro16_Entry3_TimMin, PMacro16_Entry3_TimSec, PMacro16_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro16_Entry4_DelayMin, PMacro16_Entry4_DelaySec, PMacro16_Entry4_TimMin, PMacro16_Entry4_TimSec, PMacro16_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro16_Entry5_DelayMin, PMacro16_Entry5_DelaySec, PMacro16_Entry5_TimMin, PMacro16_Entry5_TimSec, PMacro16_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro16_Entry6_DelayMin, PMacro16_Entry6_DelaySec, PMacro16_Entry6_TimMin, PMacro16_Entry6_TimSec, PMacro16_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro16_Entry7_DelayMin, PMacro16_Entry7_DelaySec, PMacro16_Entry7_TimMin, PMacro16_Entry7_TimSec, PMacro16_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro16_Entry8_DelayMin, PMacro16_Entry8_DelaySec, PMacro16_Entry8_TimMin, PMacro16_Entry8_TimSec, PMacro16_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro16_Entry9_DelayMin, PMacro16_Entry9_DelaySec, PMacro16_Entry9_TimMin, PMacro16_Entry9_TimSec, PMacro16_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro16_Entry10_DelayMin, PMacro16_Entry10_DelaySec, PMacro16_Entry10_TimMin, PMacro16_Entry10_TimSec, PMacro16_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro16_Entry11_DelayMin, PMacro16_Entry11_DelaySec, PMacro16_Entry11_TimMin, PMacro16_Entry11_TimSec, PMacro16_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro16_Entry12_DelayMin, PMacro16_Entry12_DelaySec, PMacro16_Entry12_TimMin, PMacro16_Entry12_TimSec, PMacro16_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro16_Entry13_DelayMin, PMacro16_Entry13_DelaySec, PMacro16_Entry13_TimMin, PMacro16_Entry13_TimSec, PMacro16_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro16_Entry14_DelayMin, PMacro16_Entry14_DelaySec, PMacro16_Entry14_TimMin, PMacro16_Entry14_TimSec, PMacro16_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro16_Entry15_DelayMin, PMacro16_Entry15_DelaySec, PMacro16_Entry15_TimMin, PMacro16_Entry15_TimSec, PMacro16_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR16_STRING};

const struct super_macro Macro17 = {PMacro17_NumEntries,
		         PMacro17_Entry1_DelayMin, PMacro17_Entry1_DelaySec, PMacro17_Entry1_TimMin, PMacro17_Entry1_TimSec, PMacro17_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro17_Entry2_DelayMin, PMacro17_Entry2_DelaySec, PMacro17_Entry2_TimMin, PMacro17_Entry2_TimSec, PMacro17_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro17_Entry3_DelayMin, PMacro17_Entry3_DelaySec, PMacro17_Entry3_TimMin, PMacro17_Entry3_TimSec, PMacro17_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro17_Entry4_DelayMin, PMacro17_Entry4_DelaySec, PMacro17_Entry4_TimMin, PMacro17_Entry4_TimSec, PMacro17_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro17_Entry5_DelayMin, PMacro17_Entry5_DelaySec, PMacro17_Entry5_TimMin, PMacro17_Entry5_TimSec, PMacro17_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro17_Entry6_DelayMin, PMacro17_Entry6_DelaySec, PMacro17_Entry6_TimMin, PMacro17_Entry6_TimSec, PMacro17_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro17_Entry7_DelayMin, PMacro17_Entry7_DelaySec, PMacro17_Entry7_TimMin, PMacro17_Entry7_TimSec, PMacro17_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro17_Entry8_DelayMin, PMacro17_Entry8_DelaySec, PMacro17_Entry8_TimMin, PMacro17_Entry8_TimSec, PMacro17_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro17_Entry9_DelayMin, PMacro17_Entry9_DelaySec, PMacro17_Entry9_TimMin, PMacro17_Entry9_TimSec, PMacro17_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro17_Entry10_DelayMin, PMacro17_Entry10_DelaySec, PMacro17_Entry10_TimMin, PMacro17_Entry10_TimSec, PMacro17_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro17_Entry11_DelayMin, PMacro17_Entry11_DelaySec, PMacro17_Entry11_TimMin, PMacro17_Entry11_TimSec, PMacro17_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro17_Entry12_DelayMin, PMacro17_Entry12_DelaySec, PMacro17_Entry12_TimMin, PMacro17_Entry12_TimSec, PMacro17_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro17_Entry13_DelayMin, PMacro17_Entry13_DelaySec, PMacro17_Entry13_TimMin, PMacro17_Entry13_TimSec, PMacro17_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro17_Entry14_DelayMin, PMacro17_Entry14_DelaySec, PMacro17_Entry14_TimMin, PMacro17_Entry14_TimSec, PMacro17_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro17_Entry15_DelayMin, PMacro17_Entry15_DelaySec, PMacro17_Entry15_TimMin, PMacro17_Entry15_TimSec, PMacro17_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR17_STRING};

const struct super_macro Macro18 = {PMacro18_NumEntries,
		         PMacro18_Entry1_DelayMin, PMacro18_Entry1_DelaySec, PMacro18_Entry1_TimMin, PMacro18_Entry1_TimSec, PMacro18_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro18_Entry2_DelayMin, PMacro18_Entry2_DelaySec, PMacro18_Entry2_TimMin, PMacro18_Entry2_TimSec, PMacro18_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro18_Entry3_DelayMin, PMacro18_Entry3_DelaySec, PMacro18_Entry3_TimMin, PMacro18_Entry3_TimSec, PMacro18_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro18_Entry4_DelayMin, PMacro18_Entry4_DelaySec, PMacro18_Entry4_TimMin, PMacro18_Entry4_TimSec, PMacro18_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro18_Entry5_DelayMin, PMacro18_Entry5_DelaySec, PMacro18_Entry5_TimMin, PMacro18_Entry5_TimSec, PMacro18_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro18_Entry6_DelayMin, PMacro18_Entry6_DelaySec, PMacro18_Entry6_TimMin, PMacro18_Entry6_TimSec, PMacro18_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro18_Entry7_DelayMin, PMacro18_Entry7_DelaySec, PMacro18_Entry7_TimMin, PMacro18_Entry7_TimSec, PMacro18_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro18_Entry8_DelayMin, PMacro18_Entry8_DelaySec, PMacro18_Entry8_TimMin, PMacro18_Entry8_TimSec, PMacro18_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro18_Entry9_DelayMin, PMacro18_Entry9_DelaySec, PMacro18_Entry9_TimMin, PMacro18_Entry9_TimSec, PMacro18_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro18_Entry10_DelayMin, PMacro18_Entry10_DelaySec, PMacro18_Entry10_TimMin, PMacro18_Entry10_TimSec, PMacro18_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro18_Entry11_DelayMin, PMacro18_Entry11_DelaySec, PMacro18_Entry11_TimMin, PMacro18_Entry11_TimSec, PMacro18_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro18_Entry12_DelayMin, PMacro18_Entry12_DelaySec, PMacro18_Entry12_TimMin, PMacro18_Entry12_TimSec, PMacro18_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro18_Entry13_DelayMin, PMacro18_Entry13_DelaySec, PMacro18_Entry13_TimMin, PMacro18_Entry13_TimSec, PMacro18_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro18_Entry14_DelayMin, PMacro18_Entry14_DelaySec, PMacro18_Entry14_TimMin, PMacro18_Entry14_TimSec, PMacro18_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro18_Entry15_DelayMin, PMacro18_Entry15_DelaySec, PMacro18_Entry15_TimMin, PMacro18_Entry15_TimSec, PMacro18_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR18_STRING};

const struct super_macro Macro19 = {PMacro19_NumEntries,
		         PMacro19_Entry1_DelayMin, PMacro19_Entry1_DelaySec, PMacro19_Entry1_TimMin, PMacro19_Entry1_TimSec, PMacro19_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro19_Entry2_DelayMin, PMacro19_Entry2_DelaySec, PMacro19_Entry2_TimMin, PMacro19_Entry2_TimSec, PMacro19_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro19_Entry3_DelayMin, PMacro19_Entry3_DelaySec, PMacro19_Entry3_TimMin, PMacro19_Entry3_TimSec, PMacro19_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro19_Entry4_DelayMin, PMacro19_Entry4_DelaySec, PMacro19_Entry4_TimMin, PMacro19_Entry4_TimSec, PMacro19_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro19_Entry5_DelayMin, PMacro19_Entry5_DelaySec, PMacro19_Entry5_TimMin, PMacro19_Entry5_TimSec, PMacro19_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro19_Entry6_DelayMin, PMacro19_Entry6_DelaySec, PMacro19_Entry6_TimMin, PMacro19_Entry6_TimSec, PMacro19_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro19_Entry7_DelayMin, PMacro19_Entry7_DelaySec, PMacro19_Entry7_TimMin, PMacro19_Entry7_TimSec, PMacro19_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro19_Entry8_DelayMin, PMacro19_Entry8_DelaySec, PMacro19_Entry8_TimMin, PMacro19_Entry8_TimSec, PMacro19_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro19_Entry9_DelayMin, PMacro19_Entry9_DelaySec, PMacro19_Entry9_TimMin, PMacro19_Entry9_TimSec, PMacro19_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro19_Entry10_DelayMin, PMacro19_Entry10_DelaySec, PMacro19_Entry10_TimMin, PMacro19_Entry10_TimSec, PMacro19_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro19_Entry11_DelayMin, PMacro19_Entry11_DelaySec, PMacro19_Entry11_TimMin, PMacro19_Entry11_TimSec, PMacro19_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro19_Entry12_DelayMin, PMacro19_Entry12_DelaySec, PMacro19_Entry12_TimMin, PMacro19_Entry12_TimSec, PMacro19_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro19_Entry13_DelayMin, PMacro19_Entry13_DelaySec, PMacro19_Entry13_TimMin, PMacro19_Entry13_TimSec, PMacro19_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro19_Entry14_DelayMin, PMacro19_Entry14_DelaySec, PMacro19_Entry14_TimMin, PMacro19_Entry14_TimSec, PMacro19_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro19_Entry15_DelayMin, PMacro19_Entry15_DelaySec, PMacro19_Entry15_TimMin, PMacro19_Entry15_TimSec, PMacro19_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR19_STRING};

const struct super_macro Macro20 = {PMacro20_NumEntries,
		         PMacro20_Entry1_DelayMin, PMacro20_Entry1_DelaySec, PMacro20_Entry1_TimMin, PMacro20_Entry1_TimSec, PMacro20_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro20_Entry2_DelayMin, PMacro20_Entry2_DelaySec, PMacro20_Entry2_TimMin, PMacro20_Entry2_TimSec, PMacro20_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro20_Entry3_DelayMin, PMacro20_Entry3_DelaySec, PMacro20_Entry3_TimMin, PMacro20_Entry3_TimSec, PMacro20_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro20_Entry4_DelayMin, PMacro20_Entry4_DelaySec, PMacro20_Entry4_TimMin, PMacro20_Entry4_TimSec, PMacro20_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro20_Entry5_DelayMin, PMacro20_Entry5_DelaySec, PMacro20_Entry5_TimMin, PMacro20_Entry5_TimSec, PMacro20_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro20_Entry6_DelayMin, PMacro20_Entry6_DelaySec, PMacro20_Entry6_TimMin, PMacro20_Entry6_TimSec, PMacro20_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro20_Entry7_DelayMin, PMacro20_Entry7_DelaySec, PMacro20_Entry7_TimMin, PMacro20_Entry7_TimSec, PMacro20_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro20_Entry8_DelayMin, PMacro20_Entry8_DelaySec, PMacro20_Entry8_TimMin, PMacro20_Entry8_TimSec, PMacro20_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro20_Entry9_DelayMin, PMacro20_Entry9_DelaySec, PMacro20_Entry9_TimMin, PMacro20_Entry9_TimSec, PMacro20_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro20_Entry10_DelayMin, PMacro20_Entry10_DelaySec, PMacro20_Entry10_TimMin, PMacro20_Entry10_TimSec, PMacro20_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro20_Entry11_DelayMin, PMacro20_Entry11_DelaySec, PMacro20_Entry11_TimMin, PMacro20_Entry11_TimSec, PMacro20_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro20_Entry12_DelayMin, PMacro20_Entry12_DelaySec, PMacro20_Entry12_TimMin, PMacro20_Entry12_TimSec, PMacro20_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro20_Entry13_DelayMin, PMacro20_Entry13_DelaySec, PMacro20_Entry13_TimMin, PMacro20_Entry13_TimSec, PMacro20_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro20_Entry14_DelayMin, PMacro20_Entry14_DelaySec, PMacro20_Entry14_TimMin, PMacro20_Entry14_TimSec, PMacro20_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro20_Entry15_DelayMin, PMacro20_Entry15_DelaySec, PMacro20_Entry15_TimMin, PMacro20_Entry15_TimSec, PMacro20_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR20_STRING};

const struct super_macro Macro21 = {PMacro21_NumEntries,
		         PMacro21_Entry1_DelayMin, PMacro21_Entry1_DelaySec, PMacro21_Entry1_TimMin, PMacro21_Entry1_TimSec, PMacro21_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro21_Entry2_DelayMin, PMacro21_Entry2_DelaySec, PMacro21_Entry2_TimMin, PMacro21_Entry2_TimSec, PMacro21_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro21_Entry3_DelayMin, PMacro21_Entry3_DelaySec, PMacro21_Entry3_TimMin, PMacro21_Entry3_TimSec, PMacro21_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro21_Entry4_DelayMin, PMacro21_Entry4_DelaySec, PMacro21_Entry4_TimMin, PMacro21_Entry4_TimSec, PMacro21_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro21_Entry5_DelayMin, PMacro21_Entry5_DelaySec, PMacro21_Entry5_TimMin, PMacro21_Entry5_TimSec, PMacro21_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro21_Entry6_DelayMin, PMacro21_Entry6_DelaySec, PMacro21_Entry6_TimMin, PMacro21_Entry6_TimSec, PMacro21_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro21_Entry7_DelayMin, PMacro21_Entry7_DelaySec, PMacro21_Entry7_TimMin, PMacro21_Entry7_TimSec, PMacro21_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro21_Entry8_DelayMin, PMacro21_Entry8_DelaySec, PMacro21_Entry8_TimMin, PMacro21_Entry8_TimSec, PMacro21_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro21_Entry9_DelayMin, PMacro21_Entry9_DelaySec, PMacro21_Entry9_TimMin, PMacro21_Entry9_TimSec, PMacro21_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro21_Entry10_DelayMin, PMacro21_Entry10_DelaySec, PMacro21_Entry10_TimMin, PMacro21_Entry10_TimSec, PMacro21_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro21_Entry11_DelayMin, PMacro21_Entry11_DelaySec, PMacro21_Entry11_TimMin, PMacro21_Entry11_TimSec, PMacro21_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro21_Entry12_DelayMin, PMacro21_Entry12_DelaySec, PMacro21_Entry12_TimMin, PMacro21_Entry12_TimSec, PMacro21_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro21_Entry13_DelayMin, PMacro21_Entry13_DelaySec, PMacro21_Entry13_TimMin, PMacro21_Entry13_TimSec, PMacro21_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro21_Entry14_DelayMin, PMacro21_Entry14_DelaySec, PMacro21_Entry14_TimMin, PMacro21_Entry14_TimSec, PMacro21_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro21_Entry15_DelayMin, PMacro21_Entry15_DelaySec, PMacro21_Entry15_TimMin, PMacro21_Entry15_TimSec, PMacro21_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR21_STRING};

const struct super_macro Macro22 = {PMacro22_NumEntries,
		         PMacro22_Entry1_DelayMin, PMacro22_Entry1_DelaySec, PMacro22_Entry1_TimMin, PMacro22_Entry1_TimSec, PMacro22_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro22_Entry2_DelayMin, PMacro22_Entry2_DelaySec, PMacro22_Entry2_TimMin, PMacro22_Entry2_TimSec, PMacro22_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro22_Entry3_DelayMin, PMacro22_Entry3_DelaySec, PMacro22_Entry3_TimMin, PMacro22_Entry3_TimSec, PMacro22_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro22_Entry4_DelayMin, PMacro22_Entry4_DelaySec, PMacro22_Entry4_TimMin, PMacro22_Entry4_TimSec, PMacro22_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro22_Entry5_DelayMin, PMacro22_Entry5_DelaySec, PMacro22_Entry5_TimMin, PMacro22_Entry5_TimSec, PMacro22_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro22_Entry6_DelayMin, PMacro22_Entry6_DelaySec, PMacro22_Entry6_TimMin, PMacro22_Entry6_TimSec, PMacro22_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro22_Entry7_DelayMin, PMacro22_Entry7_DelaySec, PMacro22_Entry7_TimMin, PMacro22_Entry7_TimSec, PMacro22_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro22_Entry8_DelayMin, PMacro22_Entry8_DelaySec, PMacro22_Entry8_TimMin, PMacro22_Entry8_TimSec, PMacro22_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro22_Entry9_DelayMin, PMacro22_Entry9_DelaySec, PMacro22_Entry9_TimMin, PMacro22_Entry9_TimSec, PMacro22_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro22_Entry10_DelayMin, PMacro22_Entry10_DelaySec, PMacro22_Entry10_TimMin, PMacro22_Entry10_TimSec, PMacro22_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro22_Entry11_DelayMin, PMacro22_Entry11_DelaySec, PMacro22_Entry11_TimMin, PMacro22_Entry11_TimSec, PMacro22_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro22_Entry12_DelayMin, PMacro22_Entry12_DelaySec, PMacro22_Entry12_TimMin, PMacro22_Entry12_TimSec, PMacro22_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro22_Entry13_DelayMin, PMacro22_Entry13_DelaySec, PMacro22_Entry13_TimMin, PMacro22_Entry13_TimSec, PMacro22_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro22_Entry14_DelayMin, PMacro22_Entry14_DelaySec, PMacro22_Entry14_TimMin, PMacro22_Entry14_TimSec, PMacro22_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro22_Entry15_DelayMin, PMacro22_Entry15_DelaySec, PMacro22_Entry15_TimMin, PMacro22_Entry15_TimSec, PMacro22_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR22_STRING};

const struct super_macro Macro23 = {PMacro23_NumEntries,
		         PMacro23_Entry1_DelayMin, PMacro23_Entry1_DelaySec, PMacro23_Entry1_TimMin, PMacro23_Entry1_TimSec, PMacro23_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro23_Entry2_DelayMin, PMacro23_Entry2_DelaySec, PMacro23_Entry2_TimMin, PMacro23_Entry2_TimSec, PMacro23_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro23_Entry3_DelayMin, PMacro23_Entry3_DelaySec, PMacro23_Entry3_TimMin, PMacro23_Entry3_TimSec, PMacro23_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro23_Entry4_DelayMin, PMacro23_Entry4_DelaySec, PMacro23_Entry4_TimMin, PMacro23_Entry4_TimSec, PMacro23_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro23_Entry5_DelayMin, PMacro23_Entry5_DelaySec, PMacro23_Entry5_TimMin, PMacro23_Entry5_TimSec, PMacro23_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro23_Entry6_DelayMin, PMacro23_Entry6_DelaySec, PMacro23_Entry6_TimMin, PMacro23_Entry6_TimSec, PMacro23_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro23_Entry7_DelayMin, PMacro23_Entry7_DelaySec, PMacro23_Entry7_TimMin, PMacro23_Entry7_TimSec, PMacro23_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro23_Entry8_DelayMin, PMacro23_Entry8_DelaySec, PMacro23_Entry8_TimMin, PMacro23_Entry8_TimSec, PMacro23_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro23_Entry9_DelayMin, PMacro23_Entry9_DelaySec, PMacro23_Entry9_TimMin, PMacro23_Entry9_TimSec, PMacro23_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro23_Entry10_DelayMin, PMacro23_Entry10_DelaySec, PMacro23_Entry10_TimMin, PMacro23_Entry10_TimSec, PMacro23_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro23_Entry11_DelayMin, PMacro23_Entry11_DelaySec, PMacro23_Entry11_TimMin, PMacro23_Entry11_TimSec, PMacro23_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro23_Entry12_DelayMin, PMacro23_Entry12_DelaySec, PMacro23_Entry12_TimMin, PMacro23_Entry12_TimSec, PMacro23_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro23_Entry13_DelayMin, PMacro23_Entry13_DelaySec, PMacro23_Entry13_TimMin, PMacro23_Entry13_TimSec, PMacro23_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro23_Entry14_DelayMin, PMacro23_Entry14_DelaySec, PMacro23_Entry14_TimMin, PMacro23_Entry14_TimSec, PMacro23_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro23_Entry15_DelayMin, PMacro23_Entry15_DelaySec, PMacro23_Entry15_TimMin, PMacro23_Entry15_TimSec, PMacro23_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR23_STRING};

const struct super_macro Macro24 = {PMacro24_NumEntries,
		         PMacro24_Entry1_DelayMin, PMacro24_Entry1_DelaySec, PMacro24_Entry1_TimMin, PMacro24_Entry1_TimSec, PMacro24_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro24_Entry2_DelayMin, PMacro24_Entry2_DelaySec, PMacro24_Entry2_TimMin, PMacro24_Entry2_TimSec, PMacro24_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro24_Entry3_DelayMin, PMacro24_Entry3_DelaySec, PMacro24_Entry3_TimMin, PMacro24_Entry3_TimSec, PMacro24_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro24_Entry4_DelayMin, PMacro24_Entry4_DelaySec, PMacro24_Entry4_TimMin, PMacro24_Entry4_TimSec, PMacro24_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro24_Entry5_DelayMin, PMacro24_Entry5_DelaySec, PMacro24_Entry5_TimMin, PMacro24_Entry5_TimSec, PMacro24_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro24_Entry6_DelayMin, PMacro24_Entry6_DelaySec, PMacro24_Entry6_TimMin, PMacro24_Entry6_TimSec, PMacro24_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro24_Entry7_DelayMin, PMacro24_Entry7_DelaySec, PMacro24_Entry7_TimMin, PMacro24_Entry7_TimSec, PMacro24_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro24_Entry8_DelayMin, PMacro24_Entry8_DelaySec, PMacro24_Entry8_TimMin, PMacro24_Entry8_TimSec, PMacro24_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro24_Entry9_DelayMin, PMacro24_Entry9_DelaySec, PMacro24_Entry9_TimMin, PMacro24_Entry9_TimSec, PMacro24_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro24_Entry10_DelayMin, PMacro24_Entry10_DelaySec, PMacro24_Entry10_TimMin, PMacro24_Entry10_TimSec, PMacro24_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro24_Entry11_DelayMin, PMacro24_Entry11_DelaySec, PMacro24_Entry11_TimMin, PMacro24_Entry11_TimSec, PMacro24_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro24_Entry12_DelayMin, PMacro24_Entry12_DelaySec, PMacro24_Entry12_TimMin, PMacro24_Entry12_TimSec, PMacro24_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro24_Entry13_DelayMin, PMacro24_Entry13_DelaySec, PMacro24_Entry13_TimMin, PMacro24_Entry13_TimSec, PMacro24_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro24_Entry14_DelayMin, PMacro24_Entry14_DelaySec, PMacro24_Entry14_TimMin, PMacro24_Entry14_TimSec, PMacro24_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro24_Entry15_DelayMin, PMacro24_Entry15_DelaySec, PMacro24_Entry15_TimMin, PMacro24_Entry15_TimSec, PMacro24_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR24_STRING};

const struct super_macro Macro25 = {PMacro25_NumEntries,
		         PMacro25_Entry1_DelayMin, PMacro25_Entry1_DelaySec, PMacro25_Entry1_TimMin, PMacro25_Entry1_TimSec, PMacro25_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro25_Entry2_DelayMin, PMacro25_Entry2_DelaySec, PMacro25_Entry2_TimMin, PMacro25_Entry2_TimSec, PMacro25_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro25_Entry3_DelayMin, PMacro25_Entry3_DelaySec, PMacro25_Entry3_TimMin, PMacro25_Entry3_TimSec, PMacro25_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro25_Entry4_DelayMin, PMacro25_Entry4_DelaySec, PMacro25_Entry4_TimMin, PMacro25_Entry4_TimSec, PMacro25_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro25_Entry5_DelayMin, PMacro25_Entry5_DelaySec, PMacro25_Entry5_TimMin, PMacro25_Entry5_TimSec, PMacro25_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro25_Entry6_DelayMin, PMacro25_Entry6_DelaySec, PMacro25_Entry6_TimMin, PMacro25_Entry6_TimSec, PMacro25_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro25_Entry7_DelayMin, PMacro25_Entry7_DelaySec, PMacro25_Entry7_TimMin, PMacro25_Entry7_TimSec, PMacro25_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro25_Entry8_DelayMin, PMacro25_Entry8_DelaySec, PMacro25_Entry8_TimMin, PMacro25_Entry8_TimSec, PMacro25_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro25_Entry9_DelayMin, PMacro25_Entry9_DelaySec, PMacro25_Entry9_TimMin, PMacro25_Entry9_TimSec, PMacro25_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro25_Entry10_DelayMin, PMacro25_Entry10_DelaySec, PMacro25_Entry10_TimMin, PMacro25_Entry10_TimSec, PMacro25_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro25_Entry11_DelayMin, PMacro25_Entry11_DelaySec, PMacro25_Entry11_TimMin, PMacro25_Entry11_TimSec, PMacro25_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro25_Entry12_DelayMin, PMacro25_Entry12_DelaySec, PMacro25_Entry12_TimMin, PMacro25_Entry12_TimSec, PMacro25_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro25_Entry13_DelayMin, PMacro25_Entry13_DelaySec, PMacro25_Entry13_TimMin, PMacro25_Entry13_TimSec, PMacro25_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro25_Entry14_DelayMin, PMacro25_Entry14_DelaySec, PMacro25_Entry14_TimMin, PMacro25_Entry14_TimSec, PMacro25_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro25_Entry15_DelayMin, PMacro25_Entry15_DelaySec, PMacro25_Entry15_TimMin, PMacro25_Entry15_TimSec, PMacro25_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR25_STRING};

const struct super_macro Macro26 = {PMacro26_NumEntries,
		         PMacro26_Entry1_DelayMin, PMacro26_Entry1_DelaySec, PMacro26_Entry1_TimMin, PMacro26_Entry1_TimSec, PMacro26_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro26_Entry2_DelayMin, PMacro26_Entry2_DelaySec, PMacro26_Entry2_TimMin, PMacro26_Entry2_TimSec, PMacro26_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro26_Entry3_DelayMin, PMacro26_Entry3_DelaySec, PMacro26_Entry3_TimMin, PMacro26_Entry3_TimSec, PMacro26_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro26_Entry4_DelayMin, PMacro26_Entry4_DelaySec, PMacro26_Entry4_TimMin, PMacro26_Entry4_TimSec, PMacro26_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro26_Entry5_DelayMin, PMacro26_Entry5_DelaySec, PMacro26_Entry5_TimMin, PMacro26_Entry5_TimSec, PMacro26_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro26_Entry6_DelayMin, PMacro26_Entry6_DelaySec, PMacro26_Entry6_TimMin, PMacro26_Entry6_TimSec, PMacro26_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro26_Entry7_DelayMin, PMacro26_Entry7_DelaySec, PMacro26_Entry7_TimMin, PMacro26_Entry7_TimSec, PMacro26_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro26_Entry8_DelayMin, PMacro26_Entry8_DelaySec, PMacro26_Entry8_TimMin, PMacro26_Entry8_TimSec, PMacro26_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro26_Entry9_DelayMin, PMacro26_Entry9_DelaySec, PMacro26_Entry9_TimMin, PMacro26_Entry9_TimSec, PMacro26_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro26_Entry10_DelayMin, PMacro26_Entry10_DelaySec, PMacro26_Entry10_TimMin, PMacro26_Entry10_TimSec, PMacro26_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro26_Entry11_DelayMin, PMacro26_Entry11_DelaySec, PMacro26_Entry11_TimMin, PMacro26_Entry11_TimSec, PMacro26_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro26_Entry12_DelayMin, PMacro26_Entry12_DelaySec, PMacro26_Entry12_TimMin, PMacro26_Entry12_TimSec, PMacro26_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro26_Entry13_DelayMin, PMacro26_Entry13_DelaySec, PMacro26_Entry13_TimMin, PMacro26_Entry13_TimSec, PMacro26_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro26_Entry14_DelayMin, PMacro26_Entry14_DelaySec, PMacro26_Entry14_TimMin, PMacro26_Entry14_TimSec, PMacro26_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro26_Entry15_DelayMin, PMacro26_Entry15_DelaySec, PMacro26_Entry15_TimMin, PMacro26_Entry15_TimSec, PMacro26_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR26_STRING};

const struct super_macro Macro27 = {PMacro27_NumEntries,
		         PMacro27_Entry1_DelayMin, PMacro27_Entry1_DelaySec, PMacro27_Entry1_TimMin, PMacro27_Entry1_TimSec, PMacro27_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro27_Entry2_DelayMin, PMacro27_Entry2_DelaySec, PMacro27_Entry2_TimMin, PMacro27_Entry2_TimSec, PMacro27_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro27_Entry3_DelayMin, PMacro27_Entry3_DelaySec, PMacro27_Entry3_TimMin, PMacro27_Entry3_TimSec, PMacro27_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro27_Entry4_DelayMin, PMacro27_Entry4_DelaySec, PMacro27_Entry4_TimMin, PMacro27_Entry4_TimSec, PMacro27_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro27_Entry5_DelayMin, PMacro27_Entry5_DelaySec, PMacro27_Entry5_TimMin, PMacro27_Entry5_TimSec, PMacro27_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro27_Entry6_DelayMin, PMacro27_Entry6_DelaySec, PMacro27_Entry6_TimMin, PMacro27_Entry6_TimSec, PMacro27_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro27_Entry7_DelayMin, PMacro27_Entry7_DelaySec, PMacro27_Entry7_TimMin, PMacro27_Entry7_TimSec, PMacro27_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro27_Entry8_DelayMin, PMacro27_Entry8_DelaySec, PMacro27_Entry8_TimMin, PMacro27_Entry8_TimSec, PMacro27_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro27_Entry9_DelayMin, PMacro27_Entry9_DelaySec, PMacro27_Entry9_TimMin, PMacro27_Entry9_TimSec, PMacro27_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro27_Entry10_DelayMin, PMacro27_Entry10_DelaySec, PMacro27_Entry10_TimMin, PMacro27_Entry10_TimSec, PMacro27_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro27_Entry11_DelayMin, PMacro27_Entry11_DelaySec, PMacro27_Entry11_TimMin, PMacro27_Entry11_TimSec, PMacro27_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro27_Entry12_DelayMin, PMacro27_Entry12_DelaySec, PMacro27_Entry12_TimMin, PMacro27_Entry12_TimSec, PMacro27_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro27_Entry13_DelayMin, PMacro27_Entry13_DelaySec, PMacro27_Entry13_TimMin, PMacro27_Entry13_TimSec, PMacro27_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro27_Entry14_DelayMin, PMacro27_Entry14_DelaySec, PMacro27_Entry14_TimMin, PMacro27_Entry14_TimSec, PMacro27_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro27_Entry15_DelayMin, PMacro27_Entry15_DelaySec, PMacro27_Entry15_TimMin, PMacro27_Entry15_TimSec, PMacro27_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR27_STRING};

const struct super_macro Macro28 = {PMacro28_NumEntries,
		         PMacro28_Entry1_DelayMin, PMacro28_Entry1_DelaySec, PMacro28_Entry1_TimMin, PMacro28_Entry1_TimSec, PMacro28_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro28_Entry2_DelayMin, PMacro28_Entry2_DelaySec, PMacro28_Entry2_TimMin, PMacro28_Entry2_TimSec, PMacro28_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro28_Entry3_DelayMin, PMacro28_Entry3_DelaySec, PMacro28_Entry3_TimMin, PMacro28_Entry3_TimSec, PMacro28_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro28_Entry4_DelayMin, PMacro28_Entry4_DelaySec, PMacro28_Entry4_TimMin, PMacro28_Entry4_TimSec, PMacro28_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro28_Entry5_DelayMin, PMacro28_Entry5_DelaySec, PMacro28_Entry5_TimMin, PMacro28_Entry5_TimSec, PMacro28_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro28_Entry6_DelayMin, PMacro28_Entry6_DelaySec, PMacro28_Entry6_TimMin, PMacro28_Entry6_TimSec, PMacro28_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro28_Entry7_DelayMin, PMacro28_Entry7_DelaySec, PMacro28_Entry7_TimMin, PMacro28_Entry7_TimSec, PMacro28_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro28_Entry8_DelayMin, PMacro28_Entry8_DelaySec, PMacro28_Entry8_TimMin, PMacro28_Entry8_TimSec, PMacro28_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro28_Entry9_DelayMin, PMacro28_Entry9_DelaySec, PMacro28_Entry9_TimMin, PMacro28_Entry9_TimSec, PMacro28_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro28_Entry10_DelayMin, PMacro28_Entry10_DelaySec, PMacro28_Entry10_TimMin, PMacro28_Entry10_TimSec, PMacro28_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro28_Entry11_DelayMin, PMacro28_Entry11_DelaySec, PMacro28_Entry11_TimMin, PMacro28_Entry11_TimSec, PMacro28_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro28_Entry12_DelayMin, PMacro28_Entry12_DelaySec, PMacro28_Entry12_TimMin, PMacro28_Entry12_TimSec, PMacro28_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro28_Entry13_DelayMin, PMacro28_Entry13_DelaySec, PMacro28_Entry13_TimMin, PMacro28_Entry13_TimSec, PMacro28_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro28_Entry14_DelayMin, PMacro28_Entry14_DelaySec, PMacro28_Entry14_TimMin, PMacro28_Entry14_TimSec, PMacro28_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro28_Entry15_DelayMin, PMacro28_Entry15_DelaySec, PMacro28_Entry15_TimMin, PMacro28_Entry15_TimSec, PMacro28_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR28_STRING};

const struct super_macro Macro29 = {PMacro29_NumEntries,
		         PMacro29_Entry1_DelayMin, PMacro29_Entry1_DelaySec, PMacro29_Entry1_TimMin, PMacro29_Entry1_TimSec, PMacro29_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro29_Entry2_DelayMin, PMacro29_Entry2_DelaySec, PMacro29_Entry2_TimMin, PMacro29_Entry2_TimSec, PMacro29_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro29_Entry3_DelayMin, PMacro29_Entry3_DelaySec, PMacro29_Entry3_TimMin, PMacro29_Entry3_TimSec, PMacro29_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro29_Entry4_DelayMin, PMacro29_Entry4_DelaySec, PMacro29_Entry4_TimMin, PMacro29_Entry4_TimSec, PMacro29_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro29_Entry5_DelayMin, PMacro29_Entry5_DelaySec, PMacro29_Entry5_TimMin, PMacro29_Entry5_TimSec, PMacro29_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro29_Entry6_DelayMin, PMacro29_Entry6_DelaySec, PMacro29_Entry6_TimMin, PMacro29_Entry6_TimSec, PMacro29_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro29_Entry7_DelayMin, PMacro29_Entry7_DelaySec, PMacro29_Entry7_TimMin, PMacro29_Entry7_TimSec, PMacro29_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro29_Entry8_DelayMin, PMacro29_Entry8_DelaySec, PMacro29_Entry8_TimMin, PMacro29_Entry8_TimSec, PMacro29_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro29_Entry9_DelayMin, PMacro29_Entry9_DelaySec, PMacro29_Entry9_TimMin, PMacro29_Entry9_TimSec, PMacro29_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro29_Entry10_DelayMin, PMacro29_Entry10_DelaySec, PMacro29_Entry10_TimMin, PMacro29_Entry10_TimSec, PMacro29_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro29_Entry11_DelayMin, PMacro29_Entry11_DelaySec, PMacro29_Entry11_TimMin, PMacro29_Entry11_TimSec, PMacro29_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro29_Entry12_DelayMin, PMacro29_Entry12_DelaySec, PMacro29_Entry12_TimMin, PMacro29_Entry12_TimSec, PMacro29_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro29_Entry13_DelayMin, PMacro29_Entry13_DelaySec, PMacro29_Entry13_TimMin, PMacro29_Entry13_TimSec, PMacro29_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro29_Entry14_DelayMin, PMacro29_Entry14_DelaySec, PMacro29_Entry14_TimMin, PMacro29_Entry14_TimSec, PMacro29_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro29_Entry15_DelayMin, PMacro29_Entry15_DelaySec, PMacro29_Entry15_TimMin, PMacro29_Entry15_TimSec, PMacro29_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR29_STRING};

const struct super_macro Macro30 = {PMacro30_NumEntries,
		         PMacro30_Entry1_DelayMin, PMacro30_Entry1_DelaySec, PMacro30_Entry1_TimMin, PMacro30_Entry1_TimSec, PMacro30_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro30_Entry2_DelayMin, PMacro30_Entry2_DelaySec, PMacro30_Entry2_TimMin, PMacro30_Entry2_TimSec, PMacro30_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro30_Entry3_DelayMin, PMacro30_Entry3_DelaySec, PMacro30_Entry3_TimMin, PMacro30_Entry3_TimSec, PMacro30_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro30_Entry4_DelayMin, PMacro30_Entry4_DelaySec, PMacro30_Entry4_TimMin, PMacro30_Entry4_TimSec, PMacro30_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro30_Entry5_DelayMin, PMacro30_Entry5_DelaySec, PMacro30_Entry5_TimMin, PMacro30_Entry5_TimSec, PMacro30_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro30_Entry6_DelayMin, PMacro30_Entry6_DelaySec, PMacro30_Entry6_TimMin, PMacro30_Entry6_TimSec, PMacro30_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro30_Entry7_DelayMin, PMacro30_Entry7_DelaySec, PMacro30_Entry7_TimMin, PMacro30_Entry7_TimSec, PMacro30_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro30_Entry8_DelayMin, PMacro30_Entry8_DelaySec, PMacro30_Entry8_TimMin, PMacro30_Entry8_TimSec, PMacro30_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro30_Entry9_DelayMin, PMacro30_Entry9_DelaySec, PMacro30_Entry9_TimMin, PMacro30_Entry9_TimSec, PMacro30_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro30_Entry10_DelayMin, PMacro30_Entry10_DelaySec, PMacro30_Entry10_TimMin, PMacro30_Entry10_TimSec, PMacro30_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro30_Entry11_DelayMin, PMacro30_Entry11_DelaySec, PMacro30_Entry11_TimMin, PMacro30_Entry11_TimSec, PMacro30_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro30_Entry12_DelayMin, PMacro30_Entry12_DelaySec, PMacro30_Entry12_TimMin, PMacro30_Entry12_TimSec, PMacro30_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro30_Entry13_DelayMin, PMacro30_Entry13_DelaySec, PMacro30_Entry13_TimMin, PMacro30_Entry13_TimSec, PMacro30_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro30_Entry14_DelayMin, PMacro30_Entry14_DelaySec, PMacro30_Entry14_TimMin, PMacro30_Entry14_TimSec, PMacro30_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro30_Entry15_DelayMin, PMacro30_Entry15_DelaySec, PMacro30_Entry15_TimMin, PMacro30_Entry15_TimSec, PMacro30_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR30_STRING};

const struct super_macro Macro31 = {PMacro31_NumEntries,
		         PMacro31_Entry1_DelayMin, PMacro31_Entry1_DelaySec, PMacro31_Entry1_TimMin, PMacro31_Entry1_TimSec, PMacro31_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro31_Entry2_DelayMin, PMacro31_Entry2_DelaySec, PMacro31_Entry2_TimMin, PMacro31_Entry2_TimSec, PMacro31_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro31_Entry3_DelayMin, PMacro31_Entry3_DelaySec, PMacro31_Entry3_TimMin, PMacro31_Entry3_TimSec, PMacro31_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro31_Entry4_DelayMin, PMacro31_Entry4_DelaySec, PMacro31_Entry4_TimMin, PMacro31_Entry4_TimSec, PMacro31_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro31_Entry5_DelayMin, PMacro31_Entry5_DelaySec, PMacro31_Entry5_TimMin, PMacro31_Entry5_TimSec, PMacro31_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro31_Entry6_DelayMin, PMacro31_Entry6_DelaySec, PMacro31_Entry6_TimMin, PMacro31_Entry6_TimSec, PMacro31_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro31_Entry7_DelayMin, PMacro31_Entry7_DelaySec, PMacro31_Entry7_TimMin, PMacro31_Entry7_TimSec, PMacro31_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro31_Entry8_DelayMin, PMacro31_Entry8_DelaySec, PMacro31_Entry8_TimMin, PMacro31_Entry8_TimSec, PMacro31_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro31_Entry9_DelayMin, PMacro31_Entry9_DelaySec, PMacro31_Entry9_TimMin, PMacro31_Entry9_TimSec, PMacro31_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro31_Entry10_DelayMin, PMacro31_Entry10_DelaySec, PMacro31_Entry10_TimMin, PMacro31_Entry10_TimSec, PMacro31_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro31_Entry11_DelayMin, PMacro31_Entry11_DelaySec, PMacro31_Entry11_TimMin, PMacro31_Entry11_TimSec, PMacro31_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro31_Entry12_DelayMin, PMacro31_Entry12_DelaySec, PMacro31_Entry12_TimMin, PMacro31_Entry12_TimSec, PMacro31_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro31_Entry13_DelayMin, PMacro31_Entry13_DelaySec, PMacro31_Entry13_TimMin, PMacro31_Entry13_TimSec, PMacro31_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro31_Entry14_DelayMin, PMacro31_Entry14_DelaySec, PMacro31_Entry14_TimMin, PMacro31_Entry14_TimSec, PMacro31_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro31_Entry15_DelayMin, PMacro31_Entry15_DelaySec, PMacro31_Entry15_TimMin, PMacro31_Entry15_TimSec, PMacro31_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR31_STRING};

const struct super_macro Macro32 = {PMacro32_NumEntries,
		         PMacro32_Entry1_DelayMin, PMacro32_Entry1_DelaySec, PMacro32_Entry1_TimMin, PMacro32_Entry1_TimSec, PMacro32_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro32_Entry2_DelayMin, PMacro32_Entry2_DelaySec, PMacro32_Entry2_TimMin, PMacro32_Entry2_TimSec, PMacro32_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro32_Entry3_DelayMin, PMacro32_Entry3_DelaySec, PMacro32_Entry3_TimMin, PMacro32_Entry3_TimSec, PMacro32_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro32_Entry4_DelayMin, PMacro32_Entry4_DelaySec, PMacro32_Entry4_TimMin, PMacro32_Entry4_TimSec, PMacro32_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro32_Entry5_DelayMin, PMacro32_Entry5_DelaySec, PMacro32_Entry5_TimMin, PMacro32_Entry5_TimSec, PMacro32_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro32_Entry6_DelayMin, PMacro32_Entry6_DelaySec, PMacro32_Entry6_TimMin, PMacro32_Entry6_TimSec, PMacro32_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro32_Entry7_DelayMin, PMacro32_Entry7_DelaySec, PMacro32_Entry7_TimMin, PMacro32_Entry7_TimSec, PMacro32_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro32_Entry8_DelayMin, PMacro32_Entry8_DelaySec, PMacro32_Entry8_TimMin, PMacro32_Entry8_TimSec, PMacro32_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro32_Entry9_DelayMin, PMacro32_Entry9_DelaySec, PMacro32_Entry9_TimMin, PMacro32_Entry9_TimSec, PMacro32_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro32_Entry10_DelayMin, PMacro32_Entry10_DelaySec, PMacro32_Entry10_TimMin, PMacro32_Entry10_TimSec, PMacro32_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro32_Entry11_DelayMin, PMacro32_Entry11_DelaySec, PMacro32_Entry11_TimMin, PMacro32_Entry11_TimSec, PMacro32_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro32_Entry12_DelayMin, PMacro32_Entry12_DelaySec, PMacro32_Entry12_TimMin, PMacro32_Entry12_TimSec, PMacro32_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro32_Entry13_DelayMin, PMacro32_Entry13_DelaySec, PMacro32_Entry13_TimMin, PMacro32_Entry13_TimSec, PMacro32_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro32_Entry14_DelayMin, PMacro32_Entry14_DelaySec, PMacro32_Entry14_TimMin, PMacro32_Entry14_TimSec, PMacro32_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro32_Entry15_DelayMin, PMacro32_Entry15_DelaySec, PMacro32_Entry15_TimMin, PMacro32_Entry15_TimSec, PMacro32_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR32_STRING};

const struct super_macro Macro33 = {PMacro33_NumEntries,
		         PMacro33_Entry1_DelayMin, PMacro33_Entry1_DelaySec, PMacro33_Entry1_TimMin, PMacro33_Entry1_TimSec, PMacro33_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro33_Entry2_DelayMin, PMacro33_Entry2_DelaySec, PMacro33_Entry2_TimMin, PMacro33_Entry2_TimSec, PMacro33_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro33_Entry3_DelayMin, PMacro33_Entry3_DelaySec, PMacro33_Entry3_TimMin, PMacro33_Entry3_TimSec, PMacro33_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro33_Entry4_DelayMin, PMacro33_Entry4_DelaySec, PMacro33_Entry4_TimMin, PMacro33_Entry4_TimSec, PMacro33_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro33_Entry5_DelayMin, PMacro33_Entry5_DelaySec, PMacro33_Entry5_TimMin, PMacro33_Entry5_TimSec, PMacro33_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro33_Entry6_DelayMin, PMacro33_Entry6_DelaySec, PMacro33_Entry6_TimMin, PMacro33_Entry6_TimSec, PMacro33_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro33_Entry7_DelayMin, PMacro33_Entry7_DelaySec, PMacro33_Entry7_TimMin, PMacro33_Entry7_TimSec, PMacro33_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro33_Entry8_DelayMin, PMacro33_Entry8_DelaySec, PMacro33_Entry8_TimMin, PMacro33_Entry8_TimSec, PMacro33_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro33_Entry9_DelayMin, PMacro33_Entry9_DelaySec, PMacro33_Entry9_TimMin, PMacro33_Entry9_TimSec, PMacro33_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro33_Entry10_DelayMin, PMacro33_Entry10_DelaySec, PMacro33_Entry10_TimMin, PMacro33_Entry10_TimSec, PMacro33_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro33_Entry11_DelayMin, PMacro33_Entry11_DelaySec, PMacro33_Entry11_TimMin, PMacro33_Entry11_TimSec, PMacro33_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro33_Entry12_DelayMin, PMacro33_Entry12_DelaySec, PMacro33_Entry12_TimMin, PMacro33_Entry12_TimSec, PMacro33_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro33_Entry13_DelayMin, PMacro33_Entry13_DelaySec, PMacro33_Entry13_TimMin, PMacro33_Entry13_TimSec, PMacro33_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro33_Entry14_DelayMin, PMacro33_Entry14_DelaySec, PMacro33_Entry14_TimMin, PMacro33_Entry14_TimSec, PMacro33_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro33_Entry15_DelayMin, PMacro33_Entry15_DelaySec, PMacro33_Entry15_TimMin, PMacro33_Entry15_TimSec, PMacro33_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR33_STRING};

const struct super_macro Macro34 = {PMacro34_NumEntries,
		         PMacro34_Entry1_DelayMin, PMacro34_Entry1_DelaySec, PMacro34_Entry1_TimMin, PMacro34_Entry1_TimSec, PMacro34_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro34_Entry2_DelayMin, PMacro34_Entry2_DelaySec, PMacro34_Entry2_TimMin, PMacro34_Entry2_TimSec, PMacro34_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro34_Entry3_DelayMin, PMacro34_Entry3_DelaySec, PMacro34_Entry3_TimMin, PMacro34_Entry3_TimSec, PMacro34_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro34_Entry4_DelayMin, PMacro34_Entry4_DelaySec, PMacro34_Entry4_TimMin, PMacro34_Entry4_TimSec, PMacro34_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro34_Entry5_DelayMin, PMacro34_Entry5_DelaySec, PMacro34_Entry5_TimMin, PMacro34_Entry5_TimSec, PMacro34_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro34_Entry6_DelayMin, PMacro34_Entry6_DelaySec, PMacro34_Entry6_TimMin, PMacro34_Entry6_TimSec, PMacro34_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro34_Entry7_DelayMin, PMacro34_Entry7_DelaySec, PMacro34_Entry7_TimMin, PMacro34_Entry7_TimSec, PMacro34_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro34_Entry8_DelayMin, PMacro34_Entry8_DelaySec, PMacro34_Entry8_TimMin, PMacro34_Entry8_TimSec, PMacro34_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro34_Entry9_DelayMin, PMacro34_Entry9_DelaySec, PMacro34_Entry9_TimMin, PMacro34_Entry9_TimSec, PMacro34_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro34_Entry10_DelayMin, PMacro34_Entry10_DelaySec, PMacro34_Entry10_TimMin, PMacro34_Entry10_TimSec, PMacro34_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro34_Entry11_DelayMin, PMacro34_Entry11_DelaySec, PMacro34_Entry11_TimMin, PMacro34_Entry11_TimSec, PMacro34_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro34_Entry12_DelayMin, PMacro34_Entry12_DelaySec, PMacro34_Entry12_TimMin, PMacro34_Entry12_TimSec, PMacro34_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro34_Entry13_DelayMin, PMacro34_Entry13_DelaySec, PMacro34_Entry13_TimMin, PMacro34_Entry13_TimSec, PMacro34_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro34_Entry14_DelayMin, PMacro34_Entry14_DelaySec, PMacro34_Entry14_TimMin, PMacro34_Entry14_TimSec, PMacro34_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro34_Entry15_DelayMin, PMacro34_Entry15_DelaySec, PMacro34_Entry15_TimMin, PMacro34_Entry15_TimSec, PMacro34_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR34_STRING};

const struct super_macro Macro35 = {PMacro35_NumEntries,
		         PMacro35_Entry1_DelayMin, PMacro35_Entry1_DelaySec, PMacro35_Entry1_TimMin, PMacro35_Entry1_TimSec, PMacro35_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro35_Entry2_DelayMin, PMacro35_Entry2_DelaySec, PMacro35_Entry2_TimMin, PMacro35_Entry2_TimSec, PMacro35_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro35_Entry3_DelayMin, PMacro35_Entry3_DelaySec, PMacro35_Entry3_TimMin, PMacro35_Entry3_TimSec, PMacro35_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro35_Entry4_DelayMin, PMacro35_Entry4_DelaySec, PMacro35_Entry4_TimMin, PMacro35_Entry4_TimSec, PMacro35_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro35_Entry5_DelayMin, PMacro35_Entry5_DelaySec, PMacro35_Entry5_TimMin, PMacro35_Entry5_TimSec, PMacro35_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro35_Entry6_DelayMin, PMacro35_Entry6_DelaySec, PMacro35_Entry6_TimMin, PMacro35_Entry6_TimSec, PMacro35_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro35_Entry7_DelayMin, PMacro35_Entry7_DelaySec, PMacro35_Entry7_TimMin, PMacro35_Entry7_TimSec, PMacro35_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro35_Entry8_DelayMin, PMacro35_Entry8_DelaySec, PMacro35_Entry8_TimMin, PMacro35_Entry8_TimSec, PMacro35_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro35_Entry9_DelayMin, PMacro35_Entry9_DelaySec, PMacro35_Entry9_TimMin, PMacro35_Entry9_TimSec, PMacro35_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro35_Entry10_DelayMin, PMacro35_Entry10_DelaySec, PMacro35_Entry10_TimMin, PMacro35_Entry10_TimSec, PMacro35_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro35_Entry11_DelayMin, PMacro35_Entry11_DelaySec, PMacro35_Entry11_TimMin, PMacro35_Entry11_TimSec, PMacro35_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro35_Entry12_DelayMin, PMacro35_Entry12_DelaySec, PMacro35_Entry12_TimMin, PMacro35_Entry12_TimSec, PMacro35_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro35_Entry13_DelayMin, PMacro35_Entry13_DelaySec, PMacro35_Entry13_TimMin, PMacro35_Entry13_TimSec, PMacro35_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro35_Entry14_DelayMin, PMacro35_Entry14_DelaySec, PMacro35_Entry14_TimMin, PMacro35_Entry14_TimSec, PMacro35_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro35_Entry15_DelayMin, PMacro35_Entry15_DelaySec, PMacro35_Entry15_TimMin, PMacro35_Entry15_TimSec, PMacro35_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR35_STRING};

const struct super_macro Macro36 = {PMacro36_NumEntries,
		         PMacro36_Entry1_DelayMin, PMacro36_Entry1_DelaySec, PMacro36_Entry1_TimMin, PMacro36_Entry1_TimSec, PMacro36_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro36_Entry2_DelayMin, PMacro36_Entry2_DelaySec, PMacro36_Entry2_TimMin, PMacro36_Entry2_TimSec, PMacro36_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro36_Entry3_DelayMin, PMacro36_Entry3_DelaySec, PMacro36_Entry3_TimMin, PMacro36_Entry3_TimSec, PMacro36_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro36_Entry4_DelayMin, PMacro36_Entry4_DelaySec, PMacro36_Entry4_TimMin, PMacro36_Entry4_TimSec, PMacro36_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro36_Entry5_DelayMin, PMacro36_Entry5_DelaySec, PMacro36_Entry5_TimMin, PMacro36_Entry5_TimSec, PMacro36_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro36_Entry6_DelayMin, PMacro36_Entry6_DelaySec, PMacro36_Entry6_TimMin, PMacro36_Entry6_TimSec, PMacro36_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro36_Entry7_DelayMin, PMacro36_Entry7_DelaySec, PMacro36_Entry7_TimMin, PMacro36_Entry7_TimSec, PMacro36_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro36_Entry8_DelayMin, PMacro36_Entry8_DelaySec, PMacro36_Entry8_TimMin, PMacro36_Entry8_TimSec, PMacro36_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro36_Entry9_DelayMin, PMacro36_Entry9_DelaySec, PMacro36_Entry9_TimMin, PMacro36_Entry9_TimSec, PMacro36_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro36_Entry10_DelayMin, PMacro36_Entry10_DelaySec, PMacro36_Entry10_TimMin, PMacro36_Entry10_TimSec, PMacro36_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro36_Entry11_DelayMin, PMacro36_Entry11_DelaySec, PMacro36_Entry11_TimMin, PMacro36_Entry11_TimSec, PMacro36_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro36_Entry12_DelayMin, PMacro36_Entry12_DelaySec, PMacro36_Entry12_TimMin, PMacro36_Entry12_TimSec, PMacro36_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro36_Entry13_DelayMin, PMacro36_Entry13_DelaySec, PMacro36_Entry13_TimMin, PMacro36_Entry13_TimSec, PMacro36_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro36_Entry14_DelayMin, PMacro36_Entry14_DelaySec, PMacro36_Entry14_TimMin, PMacro36_Entry14_TimSec, PMacro36_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro36_Entry15_DelayMin, PMacro36_Entry15_DelaySec, PMacro36_Entry15_TimMin, PMacro36_Entry15_TimSec, PMacro36_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR36_STRING};

const struct super_macro Macro37 = {PMacro37_NumEntries,
		         PMacro37_Entry1_DelayMin, PMacro37_Entry1_DelaySec, PMacro37_Entry1_TimMin, PMacro37_Entry1_TimSec, PMacro37_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro37_Entry2_DelayMin, PMacro37_Entry2_DelaySec, PMacro37_Entry2_TimMin, PMacro37_Entry2_TimSec, PMacro37_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro37_Entry3_DelayMin, PMacro37_Entry3_DelaySec, PMacro37_Entry3_TimMin, PMacro37_Entry3_TimSec, PMacro37_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro37_Entry4_DelayMin, PMacro37_Entry4_DelaySec, PMacro37_Entry4_TimMin, PMacro37_Entry4_TimSec, PMacro37_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro37_Entry5_DelayMin, PMacro37_Entry5_DelaySec, PMacro37_Entry5_TimMin, PMacro37_Entry5_TimSec, PMacro37_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro37_Entry6_DelayMin, PMacro37_Entry6_DelaySec, PMacro37_Entry6_TimMin, PMacro37_Entry6_TimSec, PMacro37_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro37_Entry7_DelayMin, PMacro37_Entry7_DelaySec, PMacro37_Entry7_TimMin, PMacro37_Entry7_TimSec, PMacro37_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro37_Entry8_DelayMin, PMacro37_Entry8_DelaySec, PMacro37_Entry8_TimMin, PMacro37_Entry8_TimSec, PMacro37_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro37_Entry9_DelayMin, PMacro37_Entry9_DelaySec, PMacro37_Entry9_TimMin, PMacro37_Entry9_TimSec, PMacro37_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro37_Entry10_DelayMin, PMacro37_Entry10_DelaySec, PMacro37_Entry10_TimMin, PMacro37_Entry10_TimSec, PMacro37_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro37_Entry11_DelayMin, PMacro37_Entry11_DelaySec, PMacro37_Entry11_TimMin, PMacro37_Entry11_TimSec, PMacro37_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro37_Entry12_DelayMin, PMacro37_Entry12_DelaySec, PMacro37_Entry12_TimMin, PMacro37_Entry12_TimSec, PMacro37_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro37_Entry13_DelayMin, PMacro37_Entry13_DelaySec, PMacro37_Entry13_TimMin, PMacro37_Entry13_TimSec, PMacro37_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro37_Entry14_DelayMin, PMacro37_Entry14_DelaySec, PMacro37_Entry14_TimMin, PMacro37_Entry14_TimSec, PMacro37_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro37_Entry15_DelayMin, PMacro37_Entry15_DelaySec, PMacro37_Entry15_TimMin, PMacro37_Entry15_TimSec, PMacro37_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR37_STRING};

const struct super_macro Macro38 = {PMacro38_NumEntries,
		         PMacro38_Entry1_DelayMin, PMacro38_Entry1_DelaySec, PMacro38_Entry1_TimMin, PMacro38_Entry1_TimSec, PMacro38_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro38_Entry2_DelayMin, PMacro38_Entry2_DelaySec, PMacro38_Entry2_TimMin, PMacro38_Entry2_TimSec, PMacro38_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro38_Entry3_DelayMin, PMacro38_Entry3_DelaySec, PMacro38_Entry3_TimMin, PMacro38_Entry3_TimSec, PMacro38_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro38_Entry4_DelayMin, PMacro38_Entry4_DelaySec, PMacro38_Entry4_TimMin, PMacro38_Entry4_TimSec, PMacro38_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro38_Entry5_DelayMin, PMacro38_Entry5_DelaySec, PMacro38_Entry5_TimMin, PMacro38_Entry5_TimSec, PMacro38_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro38_Entry6_DelayMin, PMacro38_Entry6_DelaySec, PMacro38_Entry6_TimMin, PMacro38_Entry6_TimSec, PMacro38_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro38_Entry7_DelayMin, PMacro38_Entry7_DelaySec, PMacro38_Entry7_TimMin, PMacro38_Entry7_TimSec, PMacro38_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro38_Entry8_DelayMin, PMacro38_Entry8_DelaySec, PMacro38_Entry8_TimMin, PMacro38_Entry8_TimSec, PMacro38_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro38_Entry9_DelayMin, PMacro38_Entry9_DelaySec, PMacro38_Entry9_TimMin, PMacro38_Entry9_TimSec, PMacro38_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro38_Entry10_DelayMin, PMacro38_Entry10_DelaySec, PMacro38_Entry10_TimMin, PMacro38_Entry10_TimSec, PMacro38_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro38_Entry11_DelayMin, PMacro38_Entry11_DelaySec, PMacro38_Entry11_TimMin, PMacro38_Entry11_TimSec, PMacro38_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro38_Entry12_DelayMin, PMacro38_Entry12_DelaySec, PMacro38_Entry12_TimMin, PMacro38_Entry12_TimSec, PMacro38_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro38_Entry13_DelayMin, PMacro38_Entry13_DelaySec, PMacro38_Entry13_TimMin, PMacro38_Entry13_TimSec, PMacro38_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro38_Entry14_DelayMin, PMacro38_Entry14_DelaySec, PMacro38_Entry14_TimMin, PMacro38_Entry14_TimSec, PMacro38_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro38_Entry15_DelayMin, PMacro38_Entry15_DelaySec, PMacro38_Entry15_TimMin, PMacro38_Entry15_TimSec, PMacro38_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR38_STRING};

const struct super_macro Macro39 = {PMacro39_NumEntries,
		         PMacro39_Entry1_DelayMin, PMacro39_Entry1_DelaySec, PMacro39_Entry1_TimMin, PMacro39_Entry1_TimSec, PMacro39_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro39_Entry2_DelayMin, PMacro39_Entry2_DelaySec, PMacro39_Entry2_TimMin, PMacro39_Entry2_TimSec, PMacro39_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro39_Entry3_DelayMin, PMacro39_Entry3_DelaySec, PMacro39_Entry3_TimMin, PMacro39_Entry3_TimSec, PMacro39_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro39_Entry4_DelayMin, PMacro39_Entry4_DelaySec, PMacro39_Entry4_TimMin, PMacro39_Entry4_TimSec, PMacro39_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro39_Entry5_DelayMin, PMacro39_Entry5_DelaySec, PMacro39_Entry5_TimMin, PMacro39_Entry5_TimSec, PMacro39_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro39_Entry6_DelayMin, PMacro39_Entry6_DelaySec, PMacro39_Entry6_TimMin, PMacro39_Entry6_TimSec, PMacro39_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro39_Entry7_DelayMin, PMacro39_Entry7_DelaySec, PMacro39_Entry7_TimMin, PMacro39_Entry7_TimSec, PMacro39_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro39_Entry8_DelayMin, PMacro39_Entry8_DelaySec, PMacro39_Entry8_TimMin, PMacro39_Entry8_TimSec, PMacro39_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro39_Entry9_DelayMin, PMacro39_Entry9_DelaySec, PMacro39_Entry9_TimMin, PMacro39_Entry9_TimSec, PMacro39_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro39_Entry10_DelayMin, PMacro39_Entry10_DelaySec, PMacro39_Entry10_TimMin, PMacro39_Entry10_TimSec, PMacro39_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro39_Entry11_DelayMin, PMacro39_Entry11_DelaySec, PMacro39_Entry11_TimMin, PMacro39_Entry11_TimSec, PMacro39_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro39_Entry12_DelayMin, PMacro39_Entry12_DelaySec, PMacro39_Entry12_TimMin, PMacro39_Entry12_TimSec, PMacro39_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro39_Entry13_DelayMin, PMacro39_Entry13_DelaySec, PMacro39_Entry13_TimMin, PMacro39_Entry13_TimSec, PMacro39_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro39_Entry14_DelayMin, PMacro39_Entry14_DelaySec, PMacro39_Entry14_TimMin, PMacro39_Entry14_TimSec, PMacro39_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro39_Entry15_DelayMin, PMacro39_Entry15_DelaySec, PMacro39_Entry15_TimMin, PMacro39_Entry15_TimSec, PMacro39_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR39_STRING};

const struct super_macro Macro40 = {PMacro40_NumEntries,
		         PMacro40_Entry1_DelayMin, PMacro40_Entry1_DelaySec, PMacro40_Entry1_TimMin, PMacro40_Entry1_TimSec, PMacro40_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro40_Entry2_DelayMin, PMacro40_Entry2_DelaySec, PMacro40_Entry2_TimMin, PMacro40_Entry2_TimSec, PMacro40_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro40_Entry3_DelayMin, PMacro40_Entry3_DelaySec, PMacro40_Entry3_TimMin, PMacro40_Entry3_TimSec, PMacro40_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro40_Entry4_DelayMin, PMacro40_Entry4_DelaySec, PMacro40_Entry4_TimMin, PMacro40_Entry4_TimSec, PMacro40_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro40_Entry5_DelayMin, PMacro40_Entry5_DelaySec, PMacro40_Entry5_TimMin, PMacro40_Entry5_TimSec, PMacro40_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro40_Entry6_DelayMin, PMacro40_Entry6_DelaySec, PMacro40_Entry6_TimMin, PMacro40_Entry6_TimSec, PMacro40_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro40_Entry7_DelayMin, PMacro40_Entry7_DelaySec, PMacro40_Entry7_TimMin, PMacro40_Entry7_TimSec, PMacro40_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro40_Entry8_DelayMin, PMacro40_Entry8_DelaySec, PMacro40_Entry8_TimMin, PMacro40_Entry8_TimSec, PMacro40_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro40_Entry9_DelayMin, PMacro40_Entry9_DelaySec, PMacro40_Entry9_TimMin, PMacro40_Entry9_TimSec, PMacro40_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro40_Entry10_DelayMin, PMacro40_Entry10_DelaySec, PMacro40_Entry10_TimMin, PMacro40_Entry10_TimSec, PMacro40_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro40_Entry11_DelayMin, PMacro40_Entry11_DelaySec, PMacro40_Entry11_TimMin, PMacro40_Entry11_TimSec, PMacro40_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro40_Entry12_DelayMin, PMacro40_Entry12_DelaySec, PMacro40_Entry12_TimMin, PMacro40_Entry12_TimSec, PMacro40_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro40_Entry13_DelayMin, PMacro40_Entry13_DelaySec, PMacro40_Entry13_TimMin, PMacro40_Entry13_TimSec, PMacro40_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro40_Entry14_DelayMin, PMacro40_Entry14_DelaySec, PMacro40_Entry14_TimMin, PMacro40_Entry14_TimSec, PMacro40_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro40_Entry15_DelayMin, PMacro40_Entry15_DelaySec, PMacro40_Entry15_TimMin, PMacro40_Entry15_TimSec, PMacro40_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR40_STRING};

const struct super_macro Macro41 = {PMacro41_NumEntries,
		         PMacro41_Entry1_DelayMin, PMacro41_Entry1_DelaySec, PMacro41_Entry1_TimMin, PMacro41_Entry1_TimSec, PMacro41_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro41_Entry2_DelayMin, PMacro41_Entry2_DelaySec, PMacro41_Entry2_TimMin, PMacro41_Entry2_TimSec, PMacro41_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro41_Entry3_DelayMin, PMacro41_Entry3_DelaySec, PMacro41_Entry3_TimMin, PMacro41_Entry3_TimSec, PMacro41_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro41_Entry4_DelayMin, PMacro41_Entry4_DelaySec, PMacro41_Entry4_TimMin, PMacro41_Entry4_TimSec, PMacro41_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro41_Entry5_DelayMin, PMacro41_Entry5_DelaySec, PMacro41_Entry5_TimMin, PMacro41_Entry5_TimSec, PMacro41_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro41_Entry6_DelayMin, PMacro41_Entry6_DelaySec, PMacro41_Entry6_TimMin, PMacro41_Entry6_TimSec, PMacro41_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro41_Entry7_DelayMin, PMacro41_Entry7_DelaySec, PMacro41_Entry7_TimMin, PMacro41_Entry7_TimSec, PMacro41_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro41_Entry8_DelayMin, PMacro41_Entry8_DelaySec, PMacro41_Entry8_TimMin, PMacro41_Entry8_TimSec, PMacro41_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro41_Entry9_DelayMin, PMacro41_Entry9_DelaySec, PMacro41_Entry9_TimMin, PMacro41_Entry9_TimSec, PMacro41_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro41_Entry10_DelayMin, PMacro41_Entry10_DelaySec, PMacro41_Entry10_TimMin, PMacro41_Entry10_TimSec, PMacro41_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro41_Entry11_DelayMin, PMacro41_Entry11_DelaySec, PMacro41_Entry11_TimMin, PMacro41_Entry11_TimSec, PMacro41_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro41_Entry12_DelayMin, PMacro41_Entry12_DelaySec, PMacro41_Entry12_TimMin, PMacro41_Entry12_TimSec, PMacro41_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro41_Entry13_DelayMin, PMacro41_Entry13_DelaySec, PMacro41_Entry13_TimMin, PMacro41_Entry13_TimSec, PMacro41_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro41_Entry14_DelayMin, PMacro41_Entry14_DelaySec, PMacro41_Entry14_TimMin, PMacro41_Entry14_TimSec, PMacro41_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro41_Entry15_DelayMin, PMacro41_Entry15_DelaySec, PMacro41_Entry15_TimMin, PMacro41_Entry15_TimSec, PMacro41_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR41_STRING};

const struct super_macro Macro42 = {PMacro42_NumEntries,
		         PMacro42_Entry1_DelayMin, PMacro42_Entry1_DelaySec, PMacro42_Entry1_TimMin, PMacro42_Entry1_TimSec, PMacro42_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro42_Entry2_DelayMin, PMacro42_Entry2_DelaySec, PMacro42_Entry2_TimMin, PMacro42_Entry2_TimSec, PMacro42_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro42_Entry3_DelayMin, PMacro42_Entry3_DelaySec, PMacro42_Entry3_TimMin, PMacro42_Entry3_TimSec, PMacro42_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro42_Entry4_DelayMin, PMacro42_Entry4_DelaySec, PMacro42_Entry4_TimMin, PMacro42_Entry4_TimSec, PMacro42_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro42_Entry5_DelayMin, PMacro42_Entry5_DelaySec, PMacro42_Entry5_TimMin, PMacro42_Entry5_TimSec, PMacro42_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro42_Entry6_DelayMin, PMacro42_Entry6_DelaySec, PMacro42_Entry6_TimMin, PMacro42_Entry6_TimSec, PMacro42_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro42_Entry7_DelayMin, PMacro42_Entry7_DelaySec, PMacro42_Entry7_TimMin, PMacro42_Entry7_TimSec, PMacro42_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro42_Entry8_DelayMin, PMacro42_Entry8_DelaySec, PMacro42_Entry8_TimMin, PMacro42_Entry8_TimSec, PMacro42_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro42_Entry9_DelayMin, PMacro42_Entry9_DelaySec, PMacro42_Entry9_TimMin, PMacro42_Entry9_TimSec, PMacro42_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro42_Entry10_DelayMin, PMacro42_Entry10_DelaySec, PMacro42_Entry10_TimMin, PMacro42_Entry10_TimSec, PMacro42_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro42_Entry11_DelayMin, PMacro42_Entry11_DelaySec, PMacro42_Entry11_TimMin, PMacro42_Entry11_TimSec, PMacro42_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro42_Entry12_DelayMin, PMacro42_Entry12_DelaySec, PMacro42_Entry12_TimMin, PMacro42_Entry12_TimSec, PMacro42_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro42_Entry13_DelayMin, PMacro42_Entry13_DelaySec, PMacro42_Entry13_TimMin, PMacro42_Entry13_TimSec, PMacro42_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro42_Entry14_DelayMin, PMacro42_Entry14_DelaySec, PMacro42_Entry14_TimMin, PMacro42_Entry14_TimSec, PMacro42_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro42_Entry15_DelayMin, PMacro42_Entry15_DelaySec, PMacro42_Entry15_TimMin, PMacro42_Entry15_TimSec, PMacro42_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR42_STRING};

const struct super_macro Macro43 = {PMacro43_NumEntries,
		         PMacro43_Entry1_DelayMin, PMacro43_Entry1_DelaySec, PMacro43_Entry1_TimMin, PMacro43_Entry1_TimSec, PMacro43_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro43_Entry2_DelayMin, PMacro43_Entry2_DelaySec, PMacro43_Entry2_TimMin, PMacro43_Entry2_TimSec, PMacro43_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro43_Entry3_DelayMin, PMacro43_Entry3_DelaySec, PMacro43_Entry3_TimMin, PMacro43_Entry3_TimSec, PMacro43_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro43_Entry4_DelayMin, PMacro43_Entry4_DelaySec, PMacro43_Entry4_TimMin, PMacro43_Entry4_TimSec, PMacro43_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro43_Entry5_DelayMin, PMacro43_Entry5_DelaySec, PMacro43_Entry5_TimMin, PMacro43_Entry5_TimSec, PMacro43_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro43_Entry6_DelayMin, PMacro43_Entry6_DelaySec, PMacro43_Entry6_TimMin, PMacro43_Entry6_TimSec, PMacro43_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro43_Entry7_DelayMin, PMacro43_Entry7_DelaySec, PMacro43_Entry7_TimMin, PMacro43_Entry7_TimSec, PMacro43_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro43_Entry8_DelayMin, PMacro43_Entry8_DelaySec, PMacro43_Entry8_TimMin, PMacro43_Entry8_TimSec, PMacro43_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro43_Entry9_DelayMin, PMacro43_Entry9_DelaySec, PMacro43_Entry9_TimMin, PMacro43_Entry9_TimSec, PMacro43_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro43_Entry10_DelayMin, PMacro43_Entry10_DelaySec, PMacro43_Entry10_TimMin, PMacro43_Entry10_TimSec, PMacro43_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro43_Entry11_DelayMin, PMacro43_Entry11_DelaySec, PMacro43_Entry11_TimMin, PMacro43_Entry11_TimSec, PMacro43_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro43_Entry12_DelayMin, PMacro43_Entry12_DelaySec, PMacro43_Entry12_TimMin, PMacro43_Entry12_TimSec, PMacro43_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro43_Entry13_DelayMin, PMacro43_Entry13_DelaySec, PMacro43_Entry13_TimMin, PMacro43_Entry13_TimSec, PMacro43_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro43_Entry14_DelayMin, PMacro43_Entry14_DelaySec, PMacro43_Entry14_TimMin, PMacro43_Entry14_TimSec, PMacro43_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro43_Entry15_DelayMin, PMacro43_Entry15_DelaySec, PMacro43_Entry15_TimMin, PMacro43_Entry15_TimSec, PMacro43_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR43_STRING};

const struct super_macro Macro44 = {PMacro44_NumEntries,
		         PMacro44_Entry1_DelayMin, PMacro44_Entry1_DelaySec, PMacro44_Entry1_TimMin, PMacro44_Entry1_TimSec, PMacro44_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro44_Entry2_DelayMin, PMacro44_Entry2_DelaySec, PMacro44_Entry2_TimMin, PMacro44_Entry2_TimSec, PMacro44_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro44_Entry3_DelayMin, PMacro44_Entry3_DelaySec, PMacro44_Entry3_TimMin, PMacro44_Entry3_TimSec, PMacro44_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro44_Entry4_DelayMin, PMacro44_Entry4_DelaySec, PMacro44_Entry4_TimMin, PMacro44_Entry4_TimSec, PMacro44_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro44_Entry5_DelayMin, PMacro44_Entry5_DelaySec, PMacro44_Entry5_TimMin, PMacro44_Entry5_TimSec, PMacro44_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro44_Entry6_DelayMin, PMacro44_Entry6_DelaySec, PMacro44_Entry6_TimMin, PMacro44_Entry6_TimSec, PMacro44_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro44_Entry7_DelayMin, PMacro44_Entry7_DelaySec, PMacro44_Entry7_TimMin, PMacro44_Entry7_TimSec, PMacro44_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro44_Entry8_DelayMin, PMacro44_Entry8_DelaySec, PMacro44_Entry8_TimMin, PMacro44_Entry8_TimSec, PMacro44_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro44_Entry9_DelayMin, PMacro44_Entry9_DelaySec, PMacro44_Entry9_TimMin, PMacro44_Entry9_TimSec, PMacro44_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro44_Entry10_DelayMin, PMacro44_Entry10_DelaySec, PMacro44_Entry10_TimMin, PMacro44_Entry10_TimSec, PMacro44_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro44_Entry11_DelayMin, PMacro44_Entry11_DelaySec, PMacro44_Entry11_TimMin, PMacro44_Entry11_TimSec, PMacro44_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro44_Entry12_DelayMin, PMacro44_Entry12_DelaySec, PMacro44_Entry12_TimMin, PMacro44_Entry12_TimSec, PMacro44_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro44_Entry13_DelayMin, PMacro44_Entry13_DelaySec, PMacro44_Entry13_TimMin, PMacro44_Entry13_TimSec, PMacro44_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro44_Entry14_DelayMin, PMacro44_Entry14_DelaySec, PMacro44_Entry14_TimMin, PMacro44_Entry14_TimSec, PMacro44_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro44_Entry15_DelayMin, PMacro44_Entry15_DelaySec, PMacro44_Entry15_TimMin, PMacro44_Entry15_TimSec, PMacro44_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR44_STRING};

const struct super_macro Macro45 = {PMacro45_NumEntries,
		         PMacro45_Entry1_DelayMin, PMacro45_Entry1_DelaySec, PMacro45_Entry1_TimMin, PMacro45_Entry1_TimSec, PMacro45_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro45_Entry2_DelayMin, PMacro45_Entry2_DelaySec, PMacro45_Entry2_TimMin, PMacro45_Entry2_TimSec, PMacro45_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro45_Entry3_DelayMin, PMacro45_Entry3_DelaySec, PMacro45_Entry3_TimMin, PMacro45_Entry3_TimSec, PMacro45_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro45_Entry4_DelayMin, PMacro45_Entry4_DelaySec, PMacro45_Entry4_TimMin, PMacro45_Entry4_TimSec, PMacro45_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro45_Entry5_DelayMin, PMacro45_Entry5_DelaySec, PMacro45_Entry5_TimMin, PMacro45_Entry5_TimSec, PMacro45_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro45_Entry6_DelayMin, PMacro45_Entry6_DelaySec, PMacro45_Entry6_TimMin, PMacro45_Entry6_TimSec, PMacro45_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro45_Entry7_DelayMin, PMacro45_Entry7_DelaySec, PMacro45_Entry7_TimMin, PMacro45_Entry7_TimSec, PMacro45_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro45_Entry8_DelayMin, PMacro45_Entry8_DelaySec, PMacro45_Entry8_TimMin, PMacro45_Entry8_TimSec, PMacro45_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro45_Entry9_DelayMin, PMacro45_Entry9_DelaySec, PMacro45_Entry9_TimMin, PMacro45_Entry9_TimSec, PMacro45_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro45_Entry10_DelayMin, PMacro45_Entry10_DelaySec, PMacro45_Entry10_TimMin, PMacro45_Entry10_TimSec, PMacro45_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro45_Entry11_DelayMin, PMacro45_Entry11_DelaySec, PMacro45_Entry11_TimMin, PMacro45_Entry11_TimSec, PMacro45_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro45_Entry12_DelayMin, PMacro45_Entry12_DelaySec, PMacro45_Entry12_TimMin, PMacro45_Entry12_TimSec, PMacro45_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro45_Entry13_DelayMin, PMacro45_Entry13_DelaySec, PMacro45_Entry13_TimMin, PMacro45_Entry13_TimSec, PMacro45_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro45_Entry14_DelayMin, PMacro45_Entry14_DelaySec, PMacro45_Entry14_TimMin, PMacro45_Entry14_TimSec, PMacro45_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro45_Entry15_DelayMin, PMacro45_Entry15_DelaySec, PMacro45_Entry15_TimMin, PMacro45_Entry15_TimSec, PMacro45_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR45_STRING};

const struct super_macro Macro46 = {PMacro46_NumEntries,
		         PMacro46_Entry1_DelayMin, PMacro46_Entry1_DelaySec, PMacro46_Entry1_TimMin, PMacro46_Entry1_TimSec, PMacro46_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro46_Entry2_DelayMin, PMacro46_Entry2_DelaySec, PMacro46_Entry2_TimMin, PMacro46_Entry2_TimSec, PMacro46_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro46_Entry3_DelayMin, PMacro46_Entry3_DelaySec, PMacro46_Entry3_TimMin, PMacro46_Entry3_TimSec, PMacro46_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro46_Entry4_DelayMin, PMacro46_Entry4_DelaySec, PMacro46_Entry4_TimMin, PMacro46_Entry4_TimSec, PMacro46_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro46_Entry5_DelayMin, PMacro46_Entry5_DelaySec, PMacro46_Entry5_TimMin, PMacro46_Entry5_TimSec, PMacro46_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro46_Entry6_DelayMin, PMacro46_Entry6_DelaySec, PMacro46_Entry6_TimMin, PMacro46_Entry6_TimSec, PMacro46_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro46_Entry7_DelayMin, PMacro46_Entry7_DelaySec, PMacro46_Entry7_TimMin, PMacro46_Entry7_TimSec, PMacro46_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro46_Entry8_DelayMin, PMacro46_Entry8_DelaySec, PMacro46_Entry8_TimMin, PMacro46_Entry8_TimSec, PMacro46_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro46_Entry9_DelayMin, PMacro46_Entry9_DelaySec, PMacro46_Entry9_TimMin, PMacro46_Entry9_TimSec, PMacro46_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro46_Entry10_DelayMin, PMacro46_Entry10_DelaySec, PMacro46_Entry10_TimMin, PMacro46_Entry10_TimSec, PMacro46_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro46_Entry11_DelayMin, PMacro46_Entry11_DelaySec, PMacro46_Entry11_TimMin, PMacro46_Entry11_TimSec, PMacro46_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro46_Entry12_DelayMin, PMacro46_Entry12_DelaySec, PMacro46_Entry12_TimMin, PMacro46_Entry12_TimSec, PMacro46_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro46_Entry13_DelayMin, PMacro46_Entry13_DelaySec, PMacro46_Entry13_TimMin, PMacro46_Entry13_TimSec, PMacro46_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro46_Entry14_DelayMin, PMacro46_Entry14_DelaySec, PMacro46_Entry14_TimMin, PMacro46_Entry14_TimSec, PMacro46_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro46_Entry15_DelayMin, PMacro46_Entry15_DelaySec, PMacro46_Entry15_TimMin, PMacro46_Entry15_TimSec, PMacro46_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR46_STRING};

const struct super_macro Macro47 = {PMacro47_NumEntries,
		         PMacro47_Entry1_DelayMin, PMacro47_Entry1_DelaySec, PMacro47_Entry1_TimMin, PMacro47_Entry1_TimSec, PMacro47_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro47_Entry2_DelayMin, PMacro47_Entry2_DelaySec, PMacro47_Entry2_TimMin, PMacro47_Entry2_TimSec, PMacro47_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro47_Entry3_DelayMin, PMacro47_Entry3_DelaySec, PMacro47_Entry3_TimMin, PMacro47_Entry3_TimSec, PMacro47_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro47_Entry4_DelayMin, PMacro47_Entry4_DelaySec, PMacro47_Entry4_TimMin, PMacro47_Entry4_TimSec, PMacro47_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro47_Entry5_DelayMin, PMacro47_Entry5_DelaySec, PMacro47_Entry5_TimMin, PMacro47_Entry5_TimSec, PMacro47_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro47_Entry6_DelayMin, PMacro47_Entry6_DelaySec, PMacro47_Entry6_TimMin, PMacro47_Entry6_TimSec, PMacro47_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro47_Entry7_DelayMin, PMacro47_Entry7_DelaySec, PMacro47_Entry7_TimMin, PMacro47_Entry7_TimSec, PMacro47_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro47_Entry8_DelayMin, PMacro47_Entry8_DelaySec, PMacro47_Entry8_TimMin, PMacro47_Entry8_TimSec, PMacro47_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro47_Entry9_DelayMin, PMacro47_Entry9_DelaySec, PMacro47_Entry9_TimMin, PMacro47_Entry9_TimSec, PMacro47_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro47_Entry10_DelayMin, PMacro47_Entry10_DelaySec, PMacro47_Entry10_TimMin, PMacro47_Entry10_TimSec, PMacro47_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro47_Entry11_DelayMin, PMacro47_Entry11_DelaySec, PMacro47_Entry11_TimMin, PMacro47_Entry11_TimSec, PMacro47_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro47_Entry12_DelayMin, PMacro47_Entry12_DelaySec, PMacro47_Entry12_TimMin, PMacro47_Entry12_TimSec, PMacro47_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro47_Entry13_DelayMin, PMacro47_Entry13_DelaySec, PMacro47_Entry13_TimMin, PMacro47_Entry13_TimSec, PMacro47_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro47_Entry14_DelayMin, PMacro47_Entry14_DelaySec, PMacro47_Entry14_TimMin, PMacro47_Entry14_TimSec, PMacro47_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro47_Entry15_DelayMin, PMacro47_Entry15_DelaySec, PMacro47_Entry15_TimMin, PMacro47_Entry15_TimSec, PMacro47_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR47_STRING};

const struct super_macro Macro48 = {PMacro48_NumEntries,
		         PMacro48_Entry1_DelayMin, PMacro48_Entry1_DelaySec, PMacro48_Entry1_TimMin, PMacro48_Entry1_TimSec, PMacro48_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro48_Entry2_DelayMin, PMacro48_Entry2_DelaySec, PMacro48_Entry2_TimMin, PMacro48_Entry2_TimSec, PMacro48_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro48_Entry3_DelayMin, PMacro48_Entry3_DelaySec, PMacro48_Entry3_TimMin, PMacro48_Entry3_TimSec, PMacro48_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro48_Entry4_DelayMin, PMacro48_Entry4_DelaySec, PMacro48_Entry4_TimMin, PMacro48_Entry4_TimSec, PMacro48_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro48_Entry5_DelayMin, PMacro48_Entry5_DelaySec, PMacro48_Entry5_TimMin, PMacro48_Entry5_TimSec, PMacro48_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro48_Entry6_DelayMin, PMacro48_Entry6_DelaySec, PMacro48_Entry6_TimMin, PMacro48_Entry6_TimSec, PMacro48_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro48_Entry7_DelayMin, PMacro48_Entry7_DelaySec, PMacro48_Entry7_TimMin, PMacro48_Entry7_TimSec, PMacro48_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro48_Entry8_DelayMin, PMacro48_Entry8_DelaySec, PMacro48_Entry8_TimMin, PMacro48_Entry8_TimSec, PMacro48_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro48_Entry9_DelayMin, PMacro48_Entry9_DelaySec, PMacro48_Entry9_TimMin, PMacro48_Entry9_TimSec, PMacro48_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro48_Entry10_DelayMin, PMacro48_Entry10_DelaySec, PMacro48_Entry10_TimMin, PMacro48_Entry10_TimSec, PMacro48_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro48_Entry11_DelayMin, PMacro48_Entry11_DelaySec, PMacro48_Entry11_TimMin, PMacro48_Entry11_TimSec, PMacro48_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro48_Entry12_DelayMin, PMacro48_Entry12_DelaySec, PMacro48_Entry12_TimMin, PMacro48_Entry12_TimSec, PMacro48_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro48_Entry13_DelayMin, PMacro48_Entry13_DelaySec, PMacro48_Entry13_TimMin, PMacro48_Entry13_TimSec, PMacro48_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro48_Entry14_DelayMin, PMacro48_Entry14_DelaySec, PMacro48_Entry14_TimMin, PMacro48_Entry14_TimSec, PMacro48_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro48_Entry15_DelayMin, PMacro48_Entry15_DelaySec, PMacro48_Entry15_TimMin, PMacro48_Entry15_TimSec, PMacro48_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR48_STRING};

const struct super_macro Macro49 = {PMacro49_NumEntries,
		         PMacro49_Entry1_DelayMin, PMacro49_Entry1_DelaySec, PMacro49_Entry1_TimMin, PMacro49_Entry1_TimSec, PMacro49_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro49_Entry2_DelayMin, PMacro49_Entry2_DelaySec, PMacro49_Entry2_TimMin, PMacro49_Entry2_TimSec, PMacro49_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro49_Entry3_DelayMin, PMacro49_Entry3_DelaySec, PMacro49_Entry3_TimMin, PMacro49_Entry3_TimSec, PMacro49_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro49_Entry4_DelayMin, PMacro49_Entry4_DelaySec, PMacro49_Entry4_TimMin, PMacro49_Entry4_TimSec, PMacro49_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro49_Entry5_DelayMin, PMacro49_Entry5_DelaySec, PMacro49_Entry5_TimMin, PMacro49_Entry5_TimSec, PMacro49_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro49_Entry6_DelayMin, PMacro49_Entry6_DelaySec, PMacro49_Entry6_TimMin, PMacro49_Entry6_TimSec, PMacro49_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro49_Entry7_DelayMin, PMacro49_Entry7_DelaySec, PMacro49_Entry7_TimMin, PMacro49_Entry7_TimSec, PMacro49_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro49_Entry8_DelayMin, PMacro49_Entry8_DelaySec, PMacro49_Entry8_TimMin, PMacro49_Entry8_TimSec, PMacro49_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro49_Entry9_DelayMin, PMacro49_Entry9_DelaySec, PMacro49_Entry9_TimMin, PMacro49_Entry9_TimSec, PMacro49_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro49_Entry10_DelayMin, PMacro49_Entry10_DelaySec, PMacro49_Entry10_TimMin, PMacro49_Entry10_TimSec, PMacro49_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro49_Entry11_DelayMin, PMacro49_Entry11_DelaySec, PMacro49_Entry11_TimMin, PMacro49_Entry11_TimSec, PMacro49_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro49_Entry12_DelayMin, PMacro49_Entry12_DelaySec, PMacro49_Entry12_TimMin, PMacro49_Entry12_TimSec, PMacro49_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro49_Entry13_DelayMin, PMacro49_Entry13_DelaySec, PMacro49_Entry13_TimMin, PMacro49_Entry13_TimSec, PMacro49_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro49_Entry14_DelayMin, PMacro49_Entry14_DelaySec, PMacro49_Entry14_TimMin, PMacro49_Entry14_TimSec, PMacro49_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro49_Entry15_DelayMin, PMacro49_Entry15_DelaySec, PMacro49_Entry15_TimMin, PMacro49_Entry15_TimSec, PMacro49_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR49_STRING};

const struct super_macro Macro50 = {PMacro50_NumEntries,
		         PMacro50_Entry1_DelayMin, PMacro50_Entry1_DelaySec, PMacro50_Entry1_TimMin, PMacro50_Entry1_TimSec, PMacro50_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro50_Entry2_DelayMin, PMacro50_Entry2_DelaySec, PMacro50_Entry2_TimMin, PMacro50_Entry2_TimSec, PMacro50_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro50_Entry3_DelayMin, PMacro50_Entry3_DelaySec, PMacro50_Entry3_TimMin, PMacro50_Entry3_TimSec, PMacro50_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro50_Entry4_DelayMin, PMacro50_Entry4_DelaySec, PMacro50_Entry4_TimMin, PMacro50_Entry4_TimSec, PMacro50_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro50_Entry5_DelayMin, PMacro50_Entry5_DelaySec, PMacro50_Entry5_TimMin, PMacro50_Entry5_TimSec, PMacro50_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro50_Entry6_DelayMin, PMacro50_Entry6_DelaySec, PMacro50_Entry6_TimMin, PMacro50_Entry6_TimSec, PMacro50_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro50_Entry7_DelayMin, PMacro50_Entry7_DelaySec, PMacro50_Entry7_TimMin, PMacro50_Entry7_TimSec, PMacro50_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro50_Entry8_DelayMin, PMacro50_Entry8_DelaySec, PMacro50_Entry8_TimMin, PMacro50_Entry8_TimSec, PMacro50_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro50_Entry9_DelayMin, PMacro50_Entry9_DelaySec, PMacro50_Entry9_TimMin, PMacro50_Entry9_TimSec, PMacro50_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro50_Entry10_DelayMin, PMacro50_Entry10_DelaySec, PMacro50_Entry10_TimMin, PMacro50_Entry10_TimSec, PMacro50_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro50_Entry11_DelayMin, PMacro50_Entry11_DelaySec, PMacro50_Entry11_TimMin, PMacro50_Entry11_TimSec, PMacro50_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro50_Entry12_DelayMin, PMacro50_Entry12_DelaySec, PMacro50_Entry12_TimMin, PMacro50_Entry12_TimSec, PMacro50_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro50_Entry13_DelayMin, PMacro50_Entry13_DelaySec, PMacro50_Entry13_TimMin, PMacro50_Entry13_TimSec, PMacro50_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro50_Entry14_DelayMin, PMacro50_Entry14_DelaySec, PMacro50_Entry14_TimMin, PMacro50_Entry14_TimSec, PMacro50_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro50_Entry15_DelayMin, PMacro50_Entry15_DelaySec, PMacro50_Entry15_TimMin, PMacro50_Entry15_TimSec, PMacro50_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR50_STRING};

const struct super_macro Macro51 = {PMacro51_NumEntries,
		         PMacro51_Entry1_DelayMin, PMacro51_Entry1_DelaySec, PMacro51_Entry1_TimMin, PMacro51_Entry1_TimSec, PMacro51_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro51_Entry2_DelayMin, PMacro51_Entry2_DelaySec, PMacro51_Entry2_TimMin, PMacro51_Entry2_TimSec, PMacro51_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro51_Entry3_DelayMin, PMacro51_Entry3_DelaySec, PMacro51_Entry3_TimMin, PMacro51_Entry3_TimSec, PMacro51_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro51_Entry4_DelayMin, PMacro51_Entry4_DelaySec, PMacro51_Entry4_TimMin, PMacro51_Entry4_TimSec, PMacro51_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro51_Entry5_DelayMin, PMacro51_Entry5_DelaySec, PMacro51_Entry5_TimMin, PMacro51_Entry5_TimSec, PMacro51_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro51_Entry6_DelayMin, PMacro51_Entry6_DelaySec, PMacro51_Entry6_TimMin, PMacro51_Entry6_TimSec, PMacro51_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro51_Entry7_DelayMin, PMacro51_Entry7_DelaySec, PMacro51_Entry7_TimMin, PMacro51_Entry7_TimSec, PMacro51_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro51_Entry8_DelayMin, PMacro51_Entry8_DelaySec, PMacro51_Entry8_TimMin, PMacro51_Entry8_TimSec, PMacro51_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro51_Entry9_DelayMin, PMacro51_Entry9_DelaySec, PMacro51_Entry9_TimMin, PMacro51_Entry9_TimSec, PMacro51_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro51_Entry10_DelayMin, PMacro51_Entry10_DelaySec, PMacro51_Entry10_TimMin, PMacro51_Entry10_TimSec, PMacro51_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro51_Entry11_DelayMin, PMacro51_Entry11_DelaySec, PMacro51_Entry11_TimMin, PMacro51_Entry11_TimSec, PMacro51_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro51_Entry12_DelayMin, PMacro51_Entry12_DelaySec, PMacro51_Entry12_TimMin, PMacro51_Entry12_TimSec, PMacro51_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro51_Entry13_DelayMin, PMacro51_Entry13_DelaySec, PMacro51_Entry13_TimMin, PMacro51_Entry13_TimSec, PMacro51_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro51_Entry14_DelayMin, PMacro51_Entry14_DelaySec, PMacro51_Entry14_TimMin, PMacro51_Entry14_TimSec, PMacro51_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro51_Entry15_DelayMin, PMacro51_Entry15_DelaySec, PMacro51_Entry15_TimMin, PMacro51_Entry15_TimSec, PMacro51_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR51_STRING};

const struct super_macro Macro52 = {PMacro52_NumEntries,
		         PMacro52_Entry1_DelayMin, PMacro52_Entry1_DelaySec, PMacro52_Entry1_TimMin, PMacro52_Entry1_TimSec, PMacro52_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro52_Entry2_DelayMin, PMacro52_Entry2_DelaySec, PMacro52_Entry2_TimMin, PMacro52_Entry2_TimSec, PMacro52_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro52_Entry3_DelayMin, PMacro52_Entry3_DelaySec, PMacro52_Entry3_TimMin, PMacro52_Entry3_TimSec, PMacro52_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro52_Entry4_DelayMin, PMacro52_Entry4_DelaySec, PMacro52_Entry4_TimMin, PMacro52_Entry4_TimSec, PMacro52_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro52_Entry5_DelayMin, PMacro52_Entry5_DelaySec, PMacro52_Entry5_TimMin, PMacro52_Entry5_TimSec, PMacro52_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro52_Entry6_DelayMin, PMacro52_Entry6_DelaySec, PMacro52_Entry6_TimMin, PMacro52_Entry6_TimSec, PMacro52_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro52_Entry7_DelayMin, PMacro52_Entry7_DelaySec, PMacro52_Entry7_TimMin, PMacro52_Entry7_TimSec, PMacro52_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro52_Entry8_DelayMin, PMacro52_Entry8_DelaySec, PMacro52_Entry8_TimMin, PMacro52_Entry8_TimSec, PMacro52_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro52_Entry9_DelayMin, PMacro52_Entry9_DelaySec, PMacro52_Entry9_TimMin, PMacro52_Entry9_TimSec, PMacro52_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro52_Entry10_DelayMin, PMacro52_Entry10_DelaySec, PMacro52_Entry10_TimMin, PMacro52_Entry10_TimSec, PMacro52_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro52_Entry11_DelayMin, PMacro52_Entry11_DelaySec, PMacro52_Entry11_TimMin, PMacro52_Entry11_TimSec, PMacro52_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro52_Entry12_DelayMin, PMacro52_Entry12_DelaySec, PMacro52_Entry12_TimMin, PMacro52_Entry12_TimSec, PMacro52_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro52_Entry13_DelayMin, PMacro52_Entry13_DelaySec, PMacro52_Entry13_TimMin, PMacro52_Entry13_TimSec, PMacro52_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro52_Entry14_DelayMin, PMacro52_Entry14_DelaySec, PMacro52_Entry14_TimMin, PMacro52_Entry14_TimSec, PMacro52_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro52_Entry15_DelayMin, PMacro52_Entry15_DelaySec, PMacro52_Entry15_TimMin, PMacro52_Entry15_TimSec, PMacro52_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR52_STRING};

const struct super_macro Macro53 = {PMacro53_NumEntries,
		         PMacro53_Entry1_DelayMin, PMacro53_Entry1_DelaySec, PMacro53_Entry1_TimMin, PMacro53_Entry1_TimSec, PMacro53_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro53_Entry2_DelayMin, PMacro53_Entry2_DelaySec, PMacro53_Entry2_TimMin, PMacro53_Entry2_TimSec, PMacro53_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro53_Entry3_DelayMin, PMacro53_Entry3_DelaySec, PMacro53_Entry3_TimMin, PMacro53_Entry3_TimSec, PMacro53_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro53_Entry4_DelayMin, PMacro53_Entry4_DelaySec, PMacro53_Entry4_TimMin, PMacro53_Entry4_TimSec, PMacro53_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro53_Entry5_DelayMin, PMacro53_Entry5_DelaySec, PMacro53_Entry5_TimMin, PMacro53_Entry5_TimSec, PMacro53_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro53_Entry6_DelayMin, PMacro53_Entry6_DelaySec, PMacro53_Entry6_TimMin, PMacro53_Entry6_TimSec, PMacro53_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro53_Entry7_DelayMin, PMacro53_Entry7_DelaySec, PMacro53_Entry7_TimMin, PMacro53_Entry7_TimSec, PMacro53_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro53_Entry8_DelayMin, PMacro53_Entry8_DelaySec, PMacro53_Entry8_TimMin, PMacro53_Entry8_TimSec, PMacro53_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro53_Entry9_DelayMin, PMacro53_Entry9_DelaySec, PMacro53_Entry9_TimMin, PMacro53_Entry9_TimSec, PMacro53_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro53_Entry10_DelayMin, PMacro53_Entry10_DelaySec, PMacro53_Entry10_TimMin, PMacro53_Entry10_TimSec, PMacro53_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro53_Entry11_DelayMin, PMacro53_Entry11_DelaySec, PMacro53_Entry11_TimMin, PMacro53_Entry11_TimSec, PMacro53_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro53_Entry12_DelayMin, PMacro53_Entry12_DelaySec, PMacro53_Entry12_TimMin, PMacro53_Entry12_TimSec, PMacro53_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro53_Entry13_DelayMin, PMacro53_Entry13_DelaySec, PMacro53_Entry13_TimMin, PMacro53_Entry13_TimSec, PMacro53_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro53_Entry14_DelayMin, PMacro53_Entry14_DelaySec, PMacro53_Entry14_TimMin, PMacro53_Entry14_TimSec, PMacro53_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro53_Entry15_DelayMin, PMacro53_Entry15_DelaySec, PMacro53_Entry15_TimMin, PMacro53_Entry15_TimSec, PMacro53_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR53_STRING};

const struct super_macro Macro54 = {PMacro54_NumEntries,
		         PMacro54_Entry1_DelayMin, PMacro54_Entry1_DelaySec, PMacro54_Entry1_TimMin, PMacro54_Entry1_TimSec, PMacro54_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro54_Entry2_DelayMin, PMacro54_Entry2_DelaySec, PMacro54_Entry2_TimMin, PMacro54_Entry2_TimSec, PMacro54_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro54_Entry3_DelayMin, PMacro54_Entry3_DelaySec, PMacro54_Entry3_TimMin, PMacro54_Entry3_TimSec, PMacro54_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro54_Entry4_DelayMin, PMacro54_Entry4_DelaySec, PMacro54_Entry4_TimMin, PMacro54_Entry4_TimSec, PMacro54_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro54_Entry5_DelayMin, PMacro54_Entry5_DelaySec, PMacro54_Entry5_TimMin, PMacro54_Entry5_TimSec, PMacro54_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro54_Entry6_DelayMin, PMacro54_Entry6_DelaySec, PMacro54_Entry6_TimMin, PMacro54_Entry6_TimSec, PMacro54_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro54_Entry7_DelayMin, PMacro54_Entry7_DelaySec, PMacro54_Entry7_TimMin, PMacro54_Entry7_TimSec, PMacro54_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro54_Entry8_DelayMin, PMacro54_Entry8_DelaySec, PMacro54_Entry8_TimMin, PMacro54_Entry8_TimSec, PMacro54_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro54_Entry9_DelayMin, PMacro54_Entry9_DelaySec, PMacro54_Entry9_TimMin, PMacro54_Entry9_TimSec, PMacro54_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro54_Entry10_DelayMin, PMacro54_Entry10_DelaySec, PMacro54_Entry10_TimMin, PMacro54_Entry10_TimSec, PMacro54_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro54_Entry11_DelayMin, PMacro54_Entry11_DelaySec, PMacro54_Entry11_TimMin, PMacro54_Entry11_TimSec, PMacro54_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro54_Entry12_DelayMin, PMacro54_Entry12_DelaySec, PMacro54_Entry12_TimMin, PMacro54_Entry12_TimSec, PMacro54_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro54_Entry13_DelayMin, PMacro54_Entry13_DelaySec, PMacro54_Entry13_TimMin, PMacro54_Entry13_TimSec, PMacro54_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro54_Entry14_DelayMin, PMacro54_Entry14_DelaySec, PMacro54_Entry14_TimMin, PMacro54_Entry14_TimSec, PMacro54_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro54_Entry15_DelayMin, PMacro54_Entry15_DelaySec, PMacro54_Entry15_TimMin, PMacro54_Entry15_TimSec, PMacro54_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR54_STRING};

const struct super_macro Macro55 = {PMacro55_NumEntries,
		         PMacro55_Entry1_DelayMin, PMacro55_Entry1_DelaySec, PMacro55_Entry1_TimMin, PMacro55_Entry1_TimSec, PMacro55_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro55_Entry2_DelayMin, PMacro55_Entry2_DelaySec, PMacro55_Entry2_TimMin, PMacro55_Entry2_TimSec, PMacro55_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro55_Entry3_DelayMin, PMacro55_Entry3_DelaySec, PMacro55_Entry3_TimMin, PMacro55_Entry3_TimSec, PMacro55_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro55_Entry4_DelayMin, PMacro55_Entry4_DelaySec, PMacro55_Entry4_TimMin, PMacro55_Entry4_TimSec, PMacro55_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro55_Entry5_DelayMin, PMacro55_Entry5_DelaySec, PMacro55_Entry5_TimMin, PMacro55_Entry5_TimSec, PMacro55_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro55_Entry6_DelayMin, PMacro55_Entry6_DelaySec, PMacro55_Entry6_TimMin, PMacro55_Entry6_TimSec, PMacro55_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro55_Entry7_DelayMin, PMacro55_Entry7_DelaySec, PMacro55_Entry7_TimMin, PMacro55_Entry7_TimSec, PMacro55_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro55_Entry8_DelayMin, PMacro55_Entry8_DelaySec, PMacro55_Entry8_TimMin, PMacro55_Entry8_TimSec, PMacro55_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro55_Entry9_DelayMin, PMacro55_Entry9_DelaySec, PMacro55_Entry9_TimMin, PMacro55_Entry9_TimSec, PMacro55_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro55_Entry10_DelayMin, PMacro55_Entry10_DelaySec, PMacro55_Entry10_TimMin, PMacro55_Entry10_TimSec, PMacro55_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro55_Entry11_DelayMin, PMacro55_Entry11_DelaySec, PMacro55_Entry11_TimMin, PMacro55_Entry11_TimSec, PMacro55_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro55_Entry12_DelayMin, PMacro55_Entry12_DelaySec, PMacro55_Entry12_TimMin, PMacro55_Entry12_TimSec, PMacro55_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro55_Entry13_DelayMin, PMacro55_Entry13_DelaySec, PMacro55_Entry13_TimMin, PMacro55_Entry13_TimSec, PMacro55_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro55_Entry14_DelayMin, PMacro55_Entry14_DelaySec, PMacro55_Entry14_TimMin, PMacro55_Entry14_TimSec, PMacro55_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro55_Entry15_DelayMin, PMacro55_Entry15_DelaySec, PMacro55_Entry15_TimMin, PMacro55_Entry15_TimSec, PMacro55_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR55_STRING};

const struct super_macro Macro56 = {PMacro56_NumEntries,
		         PMacro56_Entry1_DelayMin, PMacro56_Entry1_DelaySec, PMacro56_Entry1_TimMin, PMacro56_Entry1_TimSec, PMacro56_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro56_Entry2_DelayMin, PMacro56_Entry2_DelaySec, PMacro56_Entry2_TimMin, PMacro56_Entry2_TimSec, PMacro56_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro56_Entry3_DelayMin, PMacro56_Entry3_DelaySec, PMacro56_Entry3_TimMin, PMacro56_Entry3_TimSec, PMacro56_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro56_Entry4_DelayMin, PMacro56_Entry4_DelaySec, PMacro56_Entry4_TimMin, PMacro56_Entry4_TimSec, PMacro56_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro56_Entry5_DelayMin, PMacro56_Entry5_DelaySec, PMacro56_Entry5_TimMin, PMacro56_Entry5_TimSec, PMacro56_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro56_Entry6_DelayMin, PMacro56_Entry6_DelaySec, PMacro56_Entry6_TimMin, PMacro56_Entry6_TimSec, PMacro56_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro56_Entry7_DelayMin, PMacro56_Entry7_DelaySec, PMacro56_Entry7_TimMin, PMacro56_Entry7_TimSec, PMacro56_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro56_Entry8_DelayMin, PMacro56_Entry8_DelaySec, PMacro56_Entry8_TimMin, PMacro56_Entry8_TimSec, PMacro56_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro56_Entry9_DelayMin, PMacro56_Entry9_DelaySec, PMacro56_Entry9_TimMin, PMacro56_Entry9_TimSec, PMacro56_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro56_Entry10_DelayMin, PMacro56_Entry10_DelaySec, PMacro56_Entry10_TimMin, PMacro56_Entry10_TimSec, PMacro56_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro56_Entry11_DelayMin, PMacro56_Entry11_DelaySec, PMacro56_Entry11_TimMin, PMacro56_Entry11_TimSec, PMacro56_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro56_Entry12_DelayMin, PMacro56_Entry12_DelaySec, PMacro56_Entry12_TimMin, PMacro56_Entry12_TimSec, PMacro56_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro56_Entry13_DelayMin, PMacro56_Entry13_DelaySec, PMacro56_Entry13_TimMin, PMacro56_Entry13_TimSec, PMacro56_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro56_Entry14_DelayMin, PMacro56_Entry14_DelaySec, PMacro56_Entry14_TimMin, PMacro56_Entry14_TimSec, PMacro56_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro56_Entry15_DelayMin, PMacro56_Entry15_DelaySec, PMacro56_Entry15_TimMin, PMacro56_Entry15_TimSec, PMacro56_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR56_STRING};

const struct super_macro Macro57 = {PMacro57_NumEntries,
		         PMacro57_Entry1_DelayMin, PMacro57_Entry1_DelaySec, PMacro57_Entry1_TimMin, PMacro57_Entry1_TimSec, PMacro57_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro57_Entry2_DelayMin, PMacro57_Entry2_DelaySec, PMacro57_Entry2_TimMin, PMacro57_Entry2_TimSec, PMacro57_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro57_Entry3_DelayMin, PMacro57_Entry3_DelaySec, PMacro57_Entry3_TimMin, PMacro57_Entry3_TimSec, PMacro57_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro57_Entry4_DelayMin, PMacro57_Entry4_DelaySec, PMacro57_Entry4_TimMin, PMacro57_Entry4_TimSec, PMacro57_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro57_Entry5_DelayMin, PMacro57_Entry5_DelaySec, PMacro57_Entry5_TimMin, PMacro57_Entry5_TimSec, PMacro57_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro57_Entry6_DelayMin, PMacro57_Entry6_DelaySec, PMacro57_Entry6_TimMin, PMacro57_Entry6_TimSec, PMacro57_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro57_Entry7_DelayMin, PMacro57_Entry7_DelaySec, PMacro57_Entry7_TimMin, PMacro57_Entry7_TimSec, PMacro57_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro57_Entry8_DelayMin, PMacro57_Entry8_DelaySec, PMacro57_Entry8_TimMin, PMacro57_Entry8_TimSec, PMacro57_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro57_Entry9_DelayMin, PMacro57_Entry9_DelaySec, PMacro57_Entry9_TimMin, PMacro57_Entry9_TimSec, PMacro57_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro57_Entry10_DelayMin, PMacro57_Entry10_DelaySec, PMacro57_Entry10_TimMin, PMacro57_Entry10_TimSec, PMacro57_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro57_Entry11_DelayMin, PMacro57_Entry11_DelaySec, PMacro57_Entry11_TimMin, PMacro57_Entry11_TimSec, PMacro57_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro57_Entry12_DelayMin, PMacro57_Entry12_DelaySec, PMacro57_Entry12_TimMin, PMacro57_Entry12_TimSec, PMacro57_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro57_Entry13_DelayMin, PMacro57_Entry13_DelaySec, PMacro57_Entry13_TimMin, PMacro57_Entry13_TimSec, PMacro57_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro57_Entry14_DelayMin, PMacro57_Entry14_DelaySec, PMacro57_Entry14_TimMin, PMacro57_Entry14_TimSec, PMacro57_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro57_Entry15_DelayMin, PMacro57_Entry15_DelaySec, PMacro57_Entry15_TimMin, PMacro57_Entry15_TimSec, PMacro57_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR57_STRING};

const struct super_macro Macro58 = {PMacro58_NumEntries,
		         PMacro58_Entry1_DelayMin, PMacro58_Entry1_DelaySec, PMacro58_Entry1_TimMin, PMacro58_Entry1_TimSec, PMacro58_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro58_Entry2_DelayMin, PMacro58_Entry2_DelaySec, PMacro58_Entry2_TimMin, PMacro58_Entry2_TimSec, PMacro58_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro58_Entry3_DelayMin, PMacro58_Entry3_DelaySec, PMacro58_Entry3_TimMin, PMacro58_Entry3_TimSec, PMacro58_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro58_Entry4_DelayMin, PMacro58_Entry4_DelaySec, PMacro58_Entry4_TimMin, PMacro58_Entry4_TimSec, PMacro58_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro58_Entry5_DelayMin, PMacro58_Entry5_DelaySec, PMacro58_Entry5_TimMin, PMacro58_Entry5_TimSec, PMacro58_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro58_Entry6_DelayMin, PMacro58_Entry6_DelaySec, PMacro58_Entry6_TimMin, PMacro58_Entry6_TimSec, PMacro58_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro58_Entry7_DelayMin, PMacro58_Entry7_DelaySec, PMacro58_Entry7_TimMin, PMacro58_Entry7_TimSec, PMacro58_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro58_Entry8_DelayMin, PMacro58_Entry8_DelaySec, PMacro58_Entry8_TimMin, PMacro58_Entry8_TimSec, PMacro58_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro58_Entry9_DelayMin, PMacro58_Entry9_DelaySec, PMacro58_Entry9_TimMin, PMacro58_Entry9_TimSec, PMacro58_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro58_Entry10_DelayMin, PMacro58_Entry10_DelaySec, PMacro58_Entry10_TimMin, PMacro58_Entry10_TimSec, PMacro58_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro58_Entry11_DelayMin, PMacro58_Entry11_DelaySec, PMacro58_Entry11_TimMin, PMacro58_Entry11_TimSec, PMacro58_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro58_Entry12_DelayMin, PMacro58_Entry12_DelaySec, PMacro58_Entry12_TimMin, PMacro58_Entry12_TimSec, PMacro58_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro58_Entry13_DelayMin, PMacro58_Entry13_DelaySec, PMacro58_Entry13_TimMin, PMacro58_Entry13_TimSec, PMacro58_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro58_Entry14_DelayMin, PMacro58_Entry14_DelaySec, PMacro58_Entry14_TimMin, PMacro58_Entry14_TimSec, PMacro58_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro58_Entry15_DelayMin, PMacro58_Entry15_DelaySec, PMacro58_Entry15_TimMin, PMacro58_Entry15_TimSec, PMacro58_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR58_STRING};

const struct super_macro Macro59 = {PMacro59_NumEntries,
		         PMacro59_Entry1_DelayMin, PMacro59_Entry1_DelaySec, PMacro59_Entry1_TimMin, PMacro59_Entry1_TimSec, PMacro59_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro59_Entry2_DelayMin, PMacro59_Entry2_DelaySec, PMacro59_Entry2_TimMin, PMacro59_Entry2_TimSec, PMacro59_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro59_Entry3_DelayMin, PMacro59_Entry3_DelaySec, PMacro59_Entry3_TimMin, PMacro59_Entry3_TimSec, PMacro59_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro59_Entry4_DelayMin, PMacro59_Entry4_DelaySec, PMacro59_Entry4_TimMin, PMacro59_Entry4_TimSec, PMacro59_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro59_Entry5_DelayMin, PMacro59_Entry5_DelaySec, PMacro59_Entry5_TimMin, PMacro59_Entry5_TimSec, PMacro59_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro59_Entry6_DelayMin, PMacro59_Entry6_DelaySec, PMacro59_Entry6_TimMin, PMacro59_Entry6_TimSec, PMacro59_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro59_Entry7_DelayMin, PMacro59_Entry7_DelaySec, PMacro59_Entry7_TimMin, PMacro59_Entry7_TimSec, PMacro59_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro59_Entry8_DelayMin, PMacro59_Entry8_DelaySec, PMacro59_Entry8_TimMin, PMacro59_Entry8_TimSec, PMacro59_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro59_Entry9_DelayMin, PMacro59_Entry9_DelaySec, PMacro59_Entry9_TimMin, PMacro59_Entry9_TimSec, PMacro59_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro59_Entry10_DelayMin, PMacro59_Entry10_DelaySec, PMacro59_Entry10_TimMin, PMacro59_Entry10_TimSec, PMacro59_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro59_Entry11_DelayMin, PMacro59_Entry11_DelaySec, PMacro59_Entry11_TimMin, PMacro59_Entry11_TimSec, PMacro59_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro59_Entry12_DelayMin, PMacro59_Entry12_DelaySec, PMacro59_Entry12_TimMin, PMacro59_Entry12_TimSec, PMacro59_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro59_Entry13_DelayMin, PMacro59_Entry13_DelaySec, PMacro59_Entry13_TimMin, PMacro59_Entry13_TimSec, PMacro59_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro59_Entry14_DelayMin, PMacro59_Entry14_DelaySec, PMacro59_Entry14_TimMin, PMacro59_Entry14_TimSec, PMacro59_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro59_Entry15_DelayMin, PMacro59_Entry15_DelaySec, PMacro59_Entry15_TimMin, PMacro59_Entry15_TimSec, PMacro59_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR59_STRING};

const struct super_macro Macro60 = {PMacro60_NumEntries,
		         PMacro60_Entry1_DelayMin, PMacro60_Entry1_DelaySec, PMacro60_Entry1_TimMin, PMacro60_Entry1_TimSec, PMacro60_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro60_Entry2_DelayMin, PMacro60_Entry2_DelaySec, PMacro60_Entry2_TimMin, PMacro60_Entry2_TimSec, PMacro60_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro60_Entry3_DelayMin, PMacro60_Entry3_DelaySec, PMacro60_Entry3_TimMin, PMacro60_Entry3_TimSec, PMacro60_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro60_Entry4_DelayMin, PMacro60_Entry4_DelaySec, PMacro60_Entry4_TimMin, PMacro60_Entry4_TimSec, PMacro60_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro60_Entry5_DelayMin, PMacro60_Entry5_DelaySec, PMacro60_Entry5_TimMin, PMacro60_Entry5_TimSec, PMacro60_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro60_Entry6_DelayMin, PMacro60_Entry6_DelaySec, PMacro60_Entry6_TimMin, PMacro60_Entry6_TimSec, PMacro60_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro60_Entry7_DelayMin, PMacro60_Entry7_DelaySec, PMacro60_Entry7_TimMin, PMacro60_Entry7_TimSec, PMacro60_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro60_Entry8_DelayMin, PMacro60_Entry8_DelaySec, PMacro60_Entry8_TimMin, PMacro60_Entry8_TimSec, PMacro60_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro60_Entry9_DelayMin, PMacro60_Entry9_DelaySec, PMacro60_Entry9_TimMin, PMacro60_Entry9_TimSec, PMacro60_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro60_Entry10_DelayMin, PMacro60_Entry10_DelaySec, PMacro60_Entry10_TimMin, PMacro60_Entry10_TimSec, PMacro60_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro60_Entry11_DelayMin, PMacro60_Entry11_DelaySec, PMacro60_Entry11_TimMin, PMacro60_Entry11_TimSec, PMacro60_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro60_Entry12_DelayMin, PMacro60_Entry12_DelaySec, PMacro60_Entry12_TimMin, PMacro60_Entry12_TimSec, PMacro60_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro60_Entry13_DelayMin, PMacro60_Entry13_DelaySec, PMacro60_Entry13_TimMin, PMacro60_Entry13_TimSec, PMacro60_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro60_Entry14_DelayMin, PMacro60_Entry14_DelaySec, PMacro60_Entry14_TimMin, PMacro60_Entry14_TimSec, PMacro60_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro60_Entry15_DelayMin, PMacro60_Entry15_DelaySec, PMacro60_Entry15_TimMin, PMacro60_Entry15_TimSec, PMacro60_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR60_STRING};

const struct super_macro Macro61 = {PMacro61_NumEntries,
		         PMacro61_Entry1_DelayMin, PMacro61_Entry1_DelaySec, PMacro61_Entry1_TimMin, PMacro61_Entry1_TimSec, PMacro61_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro61_Entry2_DelayMin, PMacro61_Entry2_DelaySec, PMacro61_Entry2_TimMin, PMacro61_Entry2_TimSec, PMacro61_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro61_Entry3_DelayMin, PMacro61_Entry3_DelaySec, PMacro61_Entry3_TimMin, PMacro61_Entry3_TimSec, PMacro61_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro61_Entry4_DelayMin, PMacro61_Entry4_DelaySec, PMacro61_Entry4_TimMin, PMacro61_Entry4_TimSec, PMacro61_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro61_Entry5_DelayMin, PMacro61_Entry5_DelaySec, PMacro61_Entry5_TimMin, PMacro61_Entry5_TimSec, PMacro61_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro61_Entry6_DelayMin, PMacro61_Entry6_DelaySec, PMacro61_Entry6_TimMin, PMacro61_Entry6_TimSec, PMacro61_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro61_Entry7_DelayMin, PMacro61_Entry7_DelaySec, PMacro61_Entry7_TimMin, PMacro61_Entry7_TimSec, PMacro61_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro61_Entry8_DelayMin, PMacro61_Entry8_DelaySec, PMacro61_Entry8_TimMin, PMacro61_Entry8_TimSec, PMacro61_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro61_Entry9_DelayMin, PMacro61_Entry9_DelaySec, PMacro61_Entry9_TimMin, PMacro61_Entry9_TimSec, PMacro61_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro61_Entry10_DelayMin, PMacro61_Entry10_DelaySec, PMacro61_Entry10_TimMin, PMacro61_Entry10_TimSec, PMacro61_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro61_Entry11_DelayMin, PMacro61_Entry11_DelaySec, PMacro61_Entry11_TimMin, PMacro61_Entry11_TimSec, PMacro61_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro61_Entry12_DelayMin, PMacro61_Entry12_DelaySec, PMacro61_Entry12_TimMin, PMacro61_Entry12_TimSec, PMacro61_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro61_Entry13_DelayMin, PMacro61_Entry13_DelaySec, PMacro61_Entry13_TimMin, PMacro61_Entry13_TimSec, PMacro61_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro61_Entry14_DelayMin, PMacro61_Entry14_DelaySec, PMacro61_Entry14_TimMin, PMacro61_Entry14_TimSec, PMacro61_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro61_Entry15_DelayMin, PMacro61_Entry15_DelaySec, PMacro61_Entry15_TimMin, PMacro61_Entry15_TimSec, PMacro61_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR61_STRING};

const struct super_macro Macro62 = {PMacro62_NumEntries,
		         PMacro62_Entry1_DelayMin, PMacro62_Entry1_DelaySec, PMacro62_Entry1_TimMin, PMacro62_Entry1_TimSec, PMacro62_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro62_Entry2_DelayMin, PMacro62_Entry2_DelaySec, PMacro62_Entry2_TimMin, PMacro62_Entry2_TimSec, PMacro62_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro62_Entry3_DelayMin, PMacro62_Entry3_DelaySec, PMacro62_Entry3_TimMin, PMacro62_Entry3_TimSec, PMacro62_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro62_Entry4_DelayMin, PMacro62_Entry4_DelaySec, PMacro62_Entry4_TimMin, PMacro62_Entry4_TimSec, PMacro62_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro62_Entry5_DelayMin, PMacro62_Entry5_DelaySec, PMacro62_Entry5_TimMin, PMacro62_Entry5_TimSec, PMacro62_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro62_Entry6_DelayMin, PMacro62_Entry6_DelaySec, PMacro62_Entry6_TimMin, PMacro62_Entry6_TimSec, PMacro62_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro62_Entry7_DelayMin, PMacro62_Entry7_DelaySec, PMacro62_Entry7_TimMin, PMacro62_Entry7_TimSec, PMacro62_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro62_Entry8_DelayMin, PMacro62_Entry8_DelaySec, PMacro62_Entry8_TimMin, PMacro62_Entry8_TimSec, PMacro62_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro62_Entry9_DelayMin, PMacro62_Entry9_DelaySec, PMacro62_Entry9_TimMin, PMacro62_Entry9_TimSec, PMacro62_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro62_Entry10_DelayMin, PMacro62_Entry10_DelaySec, PMacro62_Entry10_TimMin, PMacro62_Entry10_TimSec, PMacro62_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro62_Entry11_DelayMin, PMacro62_Entry11_DelaySec, PMacro62_Entry11_TimMin, PMacro62_Entry11_TimSec, PMacro62_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro62_Entry12_DelayMin, PMacro62_Entry12_DelaySec, PMacro62_Entry12_TimMin, PMacro62_Entry12_TimSec, PMacro62_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro62_Entry13_DelayMin, PMacro62_Entry13_DelaySec, PMacro62_Entry13_TimMin, PMacro62_Entry13_TimSec, PMacro62_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro62_Entry14_DelayMin, PMacro62_Entry14_DelaySec, PMacro62_Entry14_TimMin, PMacro62_Entry14_TimSec, PMacro62_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro62_Entry15_DelayMin, PMacro62_Entry15_DelaySec, PMacro62_Entry15_TimMin, PMacro62_Entry15_TimSec, PMacro62_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR62_STRING};

const struct super_macro Macro63 = {PMacro63_NumEntries,
		         PMacro63_Entry1_DelayMin, PMacro63_Entry1_DelaySec, PMacro63_Entry1_TimMin, PMacro63_Entry1_TimSec, PMacro63_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro63_Entry2_DelayMin, PMacro63_Entry2_DelaySec, PMacro63_Entry2_TimMin, PMacro63_Entry2_TimSec, PMacro63_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro63_Entry3_DelayMin, PMacro63_Entry3_DelaySec, PMacro63_Entry3_TimMin, PMacro63_Entry3_TimSec, PMacro63_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro63_Entry4_DelayMin, PMacro63_Entry4_DelaySec, PMacro63_Entry4_TimMin, PMacro63_Entry4_TimSec, PMacro63_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro63_Entry5_DelayMin, PMacro63_Entry5_DelaySec, PMacro63_Entry5_TimMin, PMacro63_Entry5_TimSec, PMacro63_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro63_Entry6_DelayMin, PMacro63_Entry6_DelaySec, PMacro63_Entry6_TimMin, PMacro63_Entry6_TimSec, PMacro63_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro63_Entry7_DelayMin, PMacro63_Entry7_DelaySec, PMacro63_Entry7_TimMin, PMacro63_Entry7_TimSec, PMacro63_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro63_Entry8_DelayMin, PMacro63_Entry8_DelaySec, PMacro63_Entry8_TimMin, PMacro63_Entry8_TimSec, PMacro63_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro63_Entry9_DelayMin, PMacro63_Entry9_DelaySec, PMacro63_Entry9_TimMin, PMacro63_Entry9_TimSec, PMacro63_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro63_Entry10_DelayMin, PMacro63_Entry10_DelaySec, PMacro63_Entry10_TimMin, PMacro63_Entry10_TimSec, PMacro63_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro63_Entry11_DelayMin, PMacro63_Entry11_DelaySec, PMacro63_Entry11_TimMin, PMacro63_Entry11_TimSec, PMacro63_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro63_Entry12_DelayMin, PMacro63_Entry12_DelaySec, PMacro63_Entry12_TimMin, PMacro63_Entry12_TimSec, PMacro63_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro63_Entry13_DelayMin, PMacro63_Entry13_DelaySec, PMacro63_Entry13_TimMin, PMacro63_Entry13_TimSec, PMacro63_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro63_Entry14_DelayMin, PMacro63_Entry14_DelaySec, PMacro63_Entry14_TimMin, PMacro63_Entry14_TimSec, PMacro63_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro63_Entry15_DelayMin, PMacro63_Entry15_DelaySec, PMacro63_Entry15_TimMin, PMacro63_Entry15_TimSec, PMacro63_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR63_STRING};

const struct super_macro Macro64 = {PMacro64_NumEntries,
		         PMacro64_Entry1_DelayMin, PMacro64_Entry1_DelaySec, PMacro64_Entry1_TimMin, PMacro64_Entry1_TimSec, PMacro64_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro64_Entry2_DelayMin, PMacro64_Entry2_DelaySec, PMacro64_Entry2_TimMin, PMacro64_Entry2_TimSec, PMacro64_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro64_Entry3_DelayMin, PMacro64_Entry3_DelaySec, PMacro64_Entry3_TimMin, PMacro64_Entry3_TimSec, PMacro64_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro64_Entry4_DelayMin, PMacro64_Entry4_DelaySec, PMacro64_Entry4_TimMin, PMacro64_Entry4_TimSec, PMacro64_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro64_Entry5_DelayMin, PMacro64_Entry5_DelaySec, PMacro64_Entry5_TimMin, PMacro64_Entry5_TimSec, PMacro64_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro64_Entry6_DelayMin, PMacro64_Entry6_DelaySec, PMacro64_Entry6_TimMin, PMacro64_Entry6_TimSec, PMacro64_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro64_Entry7_DelayMin, PMacro64_Entry7_DelaySec, PMacro64_Entry7_TimMin, PMacro64_Entry7_TimSec, PMacro64_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro64_Entry8_DelayMin, PMacro64_Entry8_DelaySec, PMacro64_Entry8_TimMin, PMacro64_Entry8_TimSec, PMacro64_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro64_Entry9_DelayMin, PMacro64_Entry9_DelaySec, PMacro64_Entry9_TimMin, PMacro64_Entry9_TimSec, PMacro64_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro64_Entry10_DelayMin, PMacro64_Entry10_DelaySec, PMacro64_Entry10_TimMin, PMacro64_Entry10_TimSec, PMacro64_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro64_Entry11_DelayMin, PMacro64_Entry11_DelaySec, PMacro64_Entry11_TimMin, PMacro64_Entry11_TimSec, PMacro64_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro64_Entry12_DelayMin, PMacro64_Entry12_DelaySec, PMacro64_Entry12_TimMin, PMacro64_Entry12_TimSec, PMacro64_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro64_Entry13_DelayMin, PMacro64_Entry13_DelaySec, PMacro64_Entry13_TimMin, PMacro64_Entry13_TimSec, PMacro64_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro64_Entry14_DelayMin, PMacro64_Entry14_DelaySec, PMacro64_Entry14_TimMin, PMacro64_Entry14_TimSec, PMacro64_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro64_Entry15_DelayMin, PMacro64_Entry15_DelaySec, PMacro64_Entry15_TimMin, PMacro64_Entry15_TimSec, PMacro64_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR64_STRING};

const struct super_macro Macro65 = {PMacro65_NumEntries,
		         PMacro65_Entry1_DelayMin, PMacro65_Entry1_DelaySec, PMacro65_Entry1_TimMin, PMacro65_Entry1_TimSec, PMacro65_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro65_Entry2_DelayMin, PMacro65_Entry2_DelaySec, PMacro65_Entry2_TimMin, PMacro65_Entry2_TimSec, PMacro65_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro65_Entry3_DelayMin, PMacro65_Entry3_DelaySec, PMacro65_Entry3_TimMin, PMacro65_Entry3_TimSec, PMacro65_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro65_Entry4_DelayMin, PMacro65_Entry4_DelaySec, PMacro65_Entry4_TimMin, PMacro65_Entry4_TimSec, PMacro65_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro65_Entry5_DelayMin, PMacro65_Entry5_DelaySec, PMacro65_Entry5_TimMin, PMacro65_Entry5_TimSec, PMacro65_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro65_Entry6_DelayMin, PMacro65_Entry6_DelaySec, PMacro65_Entry6_TimMin, PMacro65_Entry6_TimSec, PMacro65_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro65_Entry7_DelayMin, PMacro65_Entry7_DelaySec, PMacro65_Entry7_TimMin, PMacro65_Entry7_TimSec, PMacro65_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro65_Entry8_DelayMin, PMacro65_Entry8_DelaySec, PMacro65_Entry8_TimMin, PMacro65_Entry8_TimSec, PMacro65_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro65_Entry9_DelayMin, PMacro65_Entry9_DelaySec, PMacro65_Entry9_TimMin, PMacro65_Entry9_TimSec, PMacro65_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro65_Entry10_DelayMin, PMacro65_Entry10_DelaySec, PMacro65_Entry10_TimMin, PMacro65_Entry10_TimSec, PMacro65_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro65_Entry11_DelayMin, PMacro65_Entry11_DelaySec, PMacro65_Entry11_TimMin, PMacro65_Entry11_TimSec, PMacro65_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro65_Entry12_DelayMin, PMacro65_Entry12_DelaySec, PMacro65_Entry12_TimMin, PMacro65_Entry12_TimSec, PMacro65_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro65_Entry13_DelayMin, PMacro65_Entry13_DelaySec, PMacro65_Entry13_TimMin, PMacro65_Entry13_TimSec, PMacro65_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro65_Entry14_DelayMin, PMacro65_Entry14_DelaySec, PMacro65_Entry14_TimMin, PMacro65_Entry14_TimSec, PMacro65_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro65_Entry15_DelayMin, PMacro65_Entry15_DelaySec, PMacro65_Entry15_TimMin, PMacro65_Entry15_TimSec, PMacro65_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR65_STRING};

const struct super_macro Macro66 = {PMacro66_NumEntries,
		         PMacro66_Entry1_DelayMin, PMacro66_Entry1_DelaySec, PMacro66_Entry1_TimMin, PMacro66_Entry1_TimSec, PMacro66_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro66_Entry2_DelayMin, PMacro66_Entry2_DelaySec, PMacro66_Entry2_TimMin, PMacro66_Entry2_TimSec, PMacro66_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro66_Entry3_DelayMin, PMacro66_Entry3_DelaySec, PMacro66_Entry3_TimMin, PMacro66_Entry3_TimSec, PMacro66_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro66_Entry4_DelayMin, PMacro66_Entry4_DelaySec, PMacro66_Entry4_TimMin, PMacro66_Entry4_TimSec, PMacro66_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro66_Entry5_DelayMin, PMacro66_Entry5_DelaySec, PMacro66_Entry5_TimMin, PMacro66_Entry5_TimSec, PMacro66_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro66_Entry6_DelayMin, PMacro66_Entry6_DelaySec, PMacro66_Entry6_TimMin, PMacro66_Entry6_TimSec, PMacro66_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro66_Entry7_DelayMin, PMacro66_Entry7_DelaySec, PMacro66_Entry7_TimMin, PMacro66_Entry7_TimSec, PMacro66_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro66_Entry8_DelayMin, PMacro66_Entry8_DelaySec, PMacro66_Entry8_TimMin, PMacro66_Entry8_TimSec, PMacro66_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro66_Entry9_DelayMin, PMacro66_Entry9_DelaySec, PMacro66_Entry9_TimMin, PMacro66_Entry9_TimSec, PMacro66_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro66_Entry10_DelayMin, PMacro66_Entry10_DelaySec, PMacro66_Entry10_TimMin, PMacro66_Entry10_TimSec, PMacro66_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro66_Entry11_DelayMin, PMacro66_Entry11_DelaySec, PMacro66_Entry11_TimMin, PMacro66_Entry11_TimSec, PMacro66_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro66_Entry12_DelayMin, PMacro66_Entry12_DelaySec, PMacro66_Entry12_TimMin, PMacro66_Entry12_TimSec, PMacro66_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro66_Entry13_DelayMin, PMacro66_Entry13_DelaySec, PMacro66_Entry13_TimMin, PMacro66_Entry13_TimSec, PMacro66_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro66_Entry14_DelayMin, PMacro66_Entry14_DelaySec, PMacro66_Entry14_TimMin, PMacro66_Entry14_TimSec, PMacro66_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro66_Entry15_DelayMin, PMacro66_Entry15_DelaySec, PMacro66_Entry15_TimMin, PMacro66_Entry15_TimSec, PMacro66_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR66_STRING};

const struct super_macro Macro67 = {PMacro67_NumEntries,
		         PMacro67_Entry1_DelayMin, PMacro67_Entry1_DelaySec, PMacro67_Entry1_TimMin, PMacro67_Entry1_TimSec, PMacro67_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro67_Entry2_DelayMin, PMacro67_Entry2_DelaySec, PMacro67_Entry2_TimMin, PMacro67_Entry2_TimSec, PMacro67_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro67_Entry3_DelayMin, PMacro67_Entry3_DelaySec, PMacro67_Entry3_TimMin, PMacro67_Entry3_TimSec, PMacro67_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro67_Entry4_DelayMin, PMacro67_Entry4_DelaySec, PMacro67_Entry4_TimMin, PMacro67_Entry4_TimSec, PMacro67_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro67_Entry5_DelayMin, PMacro67_Entry5_DelaySec, PMacro67_Entry5_TimMin, PMacro67_Entry5_TimSec, PMacro67_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro67_Entry6_DelayMin, PMacro67_Entry6_DelaySec, PMacro67_Entry6_TimMin, PMacro67_Entry6_TimSec, PMacro67_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro67_Entry7_DelayMin, PMacro67_Entry7_DelaySec, PMacro67_Entry7_TimMin, PMacro67_Entry7_TimSec, PMacro67_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro67_Entry8_DelayMin, PMacro67_Entry8_DelaySec, PMacro67_Entry8_TimMin, PMacro67_Entry8_TimSec, PMacro67_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro67_Entry9_DelayMin, PMacro67_Entry9_DelaySec, PMacro67_Entry9_TimMin, PMacro67_Entry9_TimSec, PMacro67_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro67_Entry10_DelayMin, PMacro67_Entry10_DelaySec, PMacro67_Entry10_TimMin, PMacro67_Entry10_TimSec, PMacro67_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro67_Entry11_DelayMin, PMacro67_Entry11_DelaySec, PMacro67_Entry11_TimMin, PMacro67_Entry11_TimSec, PMacro67_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro67_Entry12_DelayMin, PMacro67_Entry12_DelaySec, PMacro67_Entry12_TimMin, PMacro67_Entry12_TimSec, PMacro67_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro67_Entry13_DelayMin, PMacro67_Entry13_DelaySec, PMacro67_Entry13_TimMin, PMacro67_Entry13_TimSec, PMacro67_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro67_Entry14_DelayMin, PMacro67_Entry14_DelaySec, PMacro67_Entry14_TimMin, PMacro67_Entry14_TimSec, PMacro67_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro67_Entry15_DelayMin, PMacro67_Entry15_DelaySec, PMacro67_Entry15_TimMin, PMacro67_Entry15_TimSec, PMacro67_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR67_STRING};

const struct super_macro Macro68 = {PMacro68_NumEntries,
		         PMacro68_Entry1_DelayMin, PMacro68_Entry1_DelaySec, PMacro68_Entry1_TimMin, PMacro68_Entry1_TimSec, PMacro68_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro68_Entry2_DelayMin, PMacro68_Entry2_DelaySec, PMacro68_Entry2_TimMin, PMacro68_Entry2_TimSec, PMacro68_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro68_Entry3_DelayMin, PMacro68_Entry3_DelaySec, PMacro68_Entry3_TimMin, PMacro68_Entry3_TimSec, PMacro68_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro68_Entry4_DelayMin, PMacro68_Entry4_DelaySec, PMacro68_Entry4_TimMin, PMacro68_Entry4_TimSec, PMacro68_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro68_Entry5_DelayMin, PMacro68_Entry5_DelaySec, PMacro68_Entry5_TimMin, PMacro68_Entry5_TimSec, PMacro68_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro68_Entry6_DelayMin, PMacro68_Entry6_DelaySec, PMacro68_Entry6_TimMin, PMacro68_Entry6_TimSec, PMacro68_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro68_Entry7_DelayMin, PMacro68_Entry7_DelaySec, PMacro68_Entry7_TimMin, PMacro68_Entry7_TimSec, PMacro68_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro68_Entry8_DelayMin, PMacro68_Entry8_DelaySec, PMacro68_Entry8_TimMin, PMacro68_Entry8_TimSec, PMacro68_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro68_Entry9_DelayMin, PMacro68_Entry9_DelaySec, PMacro68_Entry9_TimMin, PMacro68_Entry9_TimSec, PMacro68_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro68_Entry10_DelayMin, PMacro68_Entry10_DelaySec, PMacro68_Entry10_TimMin, PMacro68_Entry10_TimSec, PMacro68_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro68_Entry11_DelayMin, PMacro68_Entry11_DelaySec, PMacro68_Entry11_TimMin, PMacro68_Entry11_TimSec, PMacro68_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro68_Entry12_DelayMin, PMacro68_Entry12_DelaySec, PMacro68_Entry12_TimMin, PMacro68_Entry12_TimSec, PMacro68_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro68_Entry13_DelayMin, PMacro68_Entry13_DelaySec, PMacro68_Entry13_TimMin, PMacro68_Entry13_TimSec, PMacro68_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro68_Entry14_DelayMin, PMacro68_Entry14_DelaySec, PMacro68_Entry14_TimMin, PMacro68_Entry14_TimSec, PMacro68_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro68_Entry15_DelayMin, PMacro68_Entry15_DelaySec, PMacro68_Entry15_TimMin, PMacro68_Entry15_TimSec, PMacro68_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR68_STRING};

const struct super_macro Macro69 = {PMacro69_NumEntries,
		         PMacro69_Entry1_DelayMin, PMacro69_Entry1_DelaySec, PMacro69_Entry1_TimMin, PMacro69_Entry1_TimSec, PMacro69_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro69_Entry2_DelayMin, PMacro69_Entry2_DelaySec, PMacro69_Entry2_TimMin, PMacro69_Entry2_TimSec, PMacro69_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro69_Entry3_DelayMin, PMacro69_Entry3_DelaySec, PMacro69_Entry3_TimMin, PMacro69_Entry3_TimSec, PMacro69_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro69_Entry4_DelayMin, PMacro69_Entry4_DelaySec, PMacro69_Entry4_TimMin, PMacro69_Entry4_TimSec, PMacro69_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro69_Entry5_DelayMin, PMacro69_Entry5_DelaySec, PMacro69_Entry5_TimMin, PMacro69_Entry5_TimSec, PMacro69_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro69_Entry6_DelayMin, PMacro69_Entry6_DelaySec, PMacro69_Entry6_TimMin, PMacro69_Entry6_TimSec, PMacro69_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro69_Entry7_DelayMin, PMacro69_Entry7_DelaySec, PMacro69_Entry7_TimMin, PMacro69_Entry7_TimSec, PMacro69_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro69_Entry8_DelayMin, PMacro69_Entry8_DelaySec, PMacro69_Entry8_TimMin, PMacro69_Entry8_TimSec, PMacro69_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro69_Entry9_DelayMin, PMacro69_Entry9_DelaySec, PMacro69_Entry9_TimMin, PMacro69_Entry9_TimSec, PMacro69_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro69_Entry10_DelayMin, PMacro69_Entry10_DelaySec, PMacro69_Entry10_TimMin, PMacro69_Entry10_TimSec, PMacro69_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro69_Entry11_DelayMin, PMacro69_Entry11_DelaySec, PMacro69_Entry11_TimMin, PMacro69_Entry11_TimSec, PMacro69_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro69_Entry12_DelayMin, PMacro69_Entry12_DelaySec, PMacro69_Entry12_TimMin, PMacro69_Entry12_TimSec, PMacro69_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro69_Entry13_DelayMin, PMacro69_Entry13_DelaySec, PMacro69_Entry13_TimMin, PMacro69_Entry13_TimSec, PMacro69_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro69_Entry14_DelayMin, PMacro69_Entry14_DelaySec, PMacro69_Entry14_TimMin, PMacro69_Entry14_TimSec, PMacro69_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro69_Entry15_DelayMin, PMacro69_Entry15_DelaySec, PMacro69_Entry15_TimMin, PMacro69_Entry15_TimSec, PMacro69_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR69_STRING};

const struct super_macro Macro70 = {PMacro70_NumEntries,
		         PMacro70_Entry1_DelayMin, PMacro70_Entry1_DelaySec, PMacro70_Entry1_TimMin, PMacro70_Entry1_TimSec, PMacro70_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro70_Entry2_DelayMin, PMacro70_Entry2_DelaySec, PMacro70_Entry2_TimMin, PMacro70_Entry2_TimSec, PMacro70_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro70_Entry3_DelayMin, PMacro70_Entry3_DelaySec, PMacro70_Entry3_TimMin, PMacro70_Entry3_TimSec, PMacro70_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro70_Entry4_DelayMin, PMacro70_Entry4_DelaySec, PMacro70_Entry4_TimMin, PMacro70_Entry4_TimSec, PMacro70_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro70_Entry5_DelayMin, PMacro70_Entry5_DelaySec, PMacro70_Entry5_TimMin, PMacro70_Entry5_TimSec, PMacro70_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro70_Entry6_DelayMin, PMacro70_Entry6_DelaySec, PMacro70_Entry6_TimMin, PMacro70_Entry6_TimSec, PMacro70_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro70_Entry7_DelayMin, PMacro70_Entry7_DelaySec, PMacro70_Entry7_TimMin, PMacro70_Entry7_TimSec, PMacro70_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro70_Entry8_DelayMin, PMacro70_Entry8_DelaySec, PMacro70_Entry8_TimMin, PMacro70_Entry8_TimSec, PMacro70_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro70_Entry9_DelayMin, PMacro70_Entry9_DelaySec, PMacro70_Entry9_TimMin, PMacro70_Entry9_TimSec, PMacro70_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro70_Entry10_DelayMin, PMacro70_Entry10_DelaySec, PMacro70_Entry10_TimMin, PMacro70_Entry10_TimSec, PMacro70_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro70_Entry11_DelayMin, PMacro70_Entry11_DelaySec, PMacro70_Entry11_TimMin, PMacro70_Entry11_TimSec, PMacro70_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro70_Entry12_DelayMin, PMacro70_Entry12_DelaySec, PMacro70_Entry12_TimMin, PMacro70_Entry12_TimSec, PMacro70_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro70_Entry13_DelayMin, PMacro70_Entry13_DelaySec, PMacro70_Entry13_TimMin, PMacro70_Entry13_TimSec, PMacro70_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro70_Entry14_DelayMin, PMacro70_Entry14_DelaySec, PMacro70_Entry14_TimMin, PMacro70_Entry14_TimSec, PMacro70_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro70_Entry15_DelayMin, PMacro70_Entry15_DelaySec, PMacro70_Entry15_TimMin, PMacro70_Entry15_TimSec, PMacro70_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR70_STRING};

const struct super_macro Macro71 = {PMacro71_NumEntries,
		         PMacro71_Entry1_DelayMin, PMacro71_Entry1_DelaySec, PMacro71_Entry1_TimMin, PMacro71_Entry1_TimSec, PMacro71_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro71_Entry2_DelayMin, PMacro71_Entry2_DelaySec, PMacro71_Entry2_TimMin, PMacro71_Entry2_TimSec, PMacro71_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro71_Entry3_DelayMin, PMacro71_Entry3_DelaySec, PMacro71_Entry3_TimMin, PMacro71_Entry3_TimSec, PMacro71_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro71_Entry4_DelayMin, PMacro71_Entry4_DelaySec, PMacro71_Entry4_TimMin, PMacro71_Entry4_TimSec, PMacro71_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro71_Entry5_DelayMin, PMacro71_Entry5_DelaySec, PMacro71_Entry5_TimMin, PMacro71_Entry5_TimSec, PMacro71_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro71_Entry6_DelayMin, PMacro71_Entry6_DelaySec, PMacro71_Entry6_TimMin, PMacro71_Entry6_TimSec, PMacro71_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro71_Entry7_DelayMin, PMacro71_Entry7_DelaySec, PMacro71_Entry7_TimMin, PMacro71_Entry7_TimSec, PMacro71_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro71_Entry8_DelayMin, PMacro71_Entry8_DelaySec, PMacro71_Entry8_TimMin, PMacro71_Entry8_TimSec, PMacro71_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro71_Entry9_DelayMin, PMacro71_Entry9_DelaySec, PMacro71_Entry9_TimMin, PMacro71_Entry9_TimSec, PMacro71_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro71_Entry10_DelayMin, PMacro71_Entry10_DelaySec, PMacro71_Entry10_TimMin, PMacro71_Entry10_TimSec, PMacro71_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro71_Entry11_DelayMin, PMacro71_Entry11_DelaySec, PMacro71_Entry11_TimMin, PMacro71_Entry11_TimSec, PMacro71_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro71_Entry12_DelayMin, PMacro71_Entry12_DelaySec, PMacro71_Entry12_TimMin, PMacro71_Entry12_TimSec, PMacro71_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro71_Entry13_DelayMin, PMacro71_Entry13_DelaySec, PMacro71_Entry13_TimMin, PMacro71_Entry13_TimSec, PMacro71_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro71_Entry14_DelayMin, PMacro71_Entry14_DelaySec, PMacro71_Entry14_TimMin, PMacro71_Entry14_TimSec, PMacro71_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro71_Entry15_DelayMin, PMacro71_Entry15_DelaySec, PMacro71_Entry15_TimMin, PMacro71_Entry15_TimSec, PMacro71_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR71_STRING};

const struct super_macro Macro72 = {PMacro72_NumEntries,
		         PMacro72_Entry1_DelayMin, PMacro72_Entry1_DelaySec, PMacro72_Entry1_TimMin, PMacro72_Entry1_TimSec, PMacro72_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro72_Entry2_DelayMin, PMacro72_Entry2_DelaySec, PMacro72_Entry2_TimMin, PMacro72_Entry2_TimSec, PMacro72_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro72_Entry3_DelayMin, PMacro72_Entry3_DelaySec, PMacro72_Entry3_TimMin, PMacro72_Entry3_TimSec, PMacro72_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro72_Entry4_DelayMin, PMacro72_Entry4_DelaySec, PMacro72_Entry4_TimMin, PMacro72_Entry4_TimSec, PMacro72_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro72_Entry5_DelayMin, PMacro72_Entry5_DelaySec, PMacro72_Entry5_TimMin, PMacro72_Entry5_TimSec, PMacro72_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro72_Entry6_DelayMin, PMacro72_Entry6_DelaySec, PMacro72_Entry6_TimMin, PMacro72_Entry6_TimSec, PMacro72_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro72_Entry7_DelayMin, PMacro72_Entry7_DelaySec, PMacro72_Entry7_TimMin, PMacro72_Entry7_TimSec, PMacro72_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro72_Entry8_DelayMin, PMacro72_Entry8_DelaySec, PMacro72_Entry8_TimMin, PMacro72_Entry8_TimSec, PMacro72_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro72_Entry9_DelayMin, PMacro72_Entry9_DelaySec, PMacro72_Entry9_TimMin, PMacro72_Entry9_TimSec, PMacro72_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro72_Entry10_DelayMin, PMacro72_Entry10_DelaySec, PMacro72_Entry10_TimMin, PMacro72_Entry10_TimSec, PMacro72_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro72_Entry11_DelayMin, PMacro72_Entry11_DelaySec, PMacro72_Entry11_TimMin, PMacro72_Entry11_TimSec, PMacro72_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro72_Entry12_DelayMin, PMacro72_Entry12_DelaySec, PMacro72_Entry12_TimMin, PMacro72_Entry12_TimSec, PMacro72_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro72_Entry13_DelayMin, PMacro72_Entry13_DelaySec, PMacro72_Entry13_TimMin, PMacro72_Entry13_TimSec, PMacro72_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro72_Entry14_DelayMin, PMacro72_Entry14_DelaySec, PMacro72_Entry14_TimMin, PMacro72_Entry14_TimSec, PMacro72_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro72_Entry15_DelayMin, PMacro72_Entry15_DelaySec, PMacro72_Entry15_TimMin, PMacro72_Entry15_TimSec, PMacro72_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR72_STRING};

const struct super_macro Macro73 = {PMacro73_NumEntries,
		         PMacro73_Entry1_DelayMin, PMacro73_Entry1_DelaySec, PMacro73_Entry1_TimMin, PMacro73_Entry1_TimSec, PMacro73_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro73_Entry2_DelayMin, PMacro73_Entry2_DelaySec, PMacro73_Entry2_TimMin, PMacro73_Entry2_TimSec, PMacro73_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro73_Entry3_DelayMin, PMacro73_Entry3_DelaySec, PMacro73_Entry3_TimMin, PMacro73_Entry3_TimSec, PMacro73_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro73_Entry4_DelayMin, PMacro73_Entry4_DelaySec, PMacro73_Entry4_TimMin, PMacro73_Entry4_TimSec, PMacro73_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro73_Entry5_DelayMin, PMacro73_Entry5_DelaySec, PMacro73_Entry5_TimMin, PMacro73_Entry5_TimSec, PMacro73_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro73_Entry6_DelayMin, PMacro73_Entry6_DelaySec, PMacro73_Entry6_TimMin, PMacro73_Entry6_TimSec, PMacro73_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro73_Entry7_DelayMin, PMacro73_Entry7_DelaySec, PMacro73_Entry7_TimMin, PMacro73_Entry7_TimSec, PMacro73_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro73_Entry8_DelayMin, PMacro73_Entry8_DelaySec, PMacro73_Entry8_TimMin, PMacro73_Entry8_TimSec, PMacro73_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro73_Entry9_DelayMin, PMacro73_Entry9_DelaySec, PMacro73_Entry9_TimMin, PMacro73_Entry9_TimSec, PMacro73_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro73_Entry10_DelayMin, PMacro73_Entry10_DelaySec, PMacro73_Entry10_TimMin, PMacro73_Entry10_TimSec, PMacro73_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro73_Entry11_DelayMin, PMacro73_Entry11_DelaySec, PMacro73_Entry11_TimMin, PMacro73_Entry11_TimSec, PMacro73_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro73_Entry12_DelayMin, PMacro73_Entry12_DelaySec, PMacro73_Entry12_TimMin, PMacro73_Entry12_TimSec, PMacro73_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro73_Entry13_DelayMin, PMacro73_Entry13_DelaySec, PMacro73_Entry13_TimMin, PMacro73_Entry13_TimSec, PMacro73_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro73_Entry14_DelayMin, PMacro73_Entry14_DelaySec, PMacro73_Entry14_TimMin, PMacro73_Entry14_TimSec, PMacro73_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro73_Entry15_DelayMin, PMacro73_Entry15_DelaySec, PMacro73_Entry15_TimMin, PMacro73_Entry15_TimSec, PMacro73_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR73_STRING};

const struct super_macro Macro74 = {PMacro74_NumEntries,
		         PMacro74_Entry1_DelayMin, PMacro74_Entry1_DelaySec, PMacro74_Entry1_TimMin, PMacro74_Entry1_TimSec, PMacro74_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro74_Entry2_DelayMin, PMacro74_Entry2_DelaySec, PMacro74_Entry2_TimMin, PMacro74_Entry2_TimSec, PMacro74_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro74_Entry3_DelayMin, PMacro74_Entry3_DelaySec, PMacro74_Entry3_TimMin, PMacro74_Entry3_TimSec, PMacro74_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro74_Entry4_DelayMin, PMacro74_Entry4_DelaySec, PMacro74_Entry4_TimMin, PMacro74_Entry4_TimSec, PMacro74_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro74_Entry5_DelayMin, PMacro74_Entry5_DelaySec, PMacro74_Entry5_TimMin, PMacro74_Entry5_TimSec, PMacro74_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro74_Entry6_DelayMin, PMacro74_Entry6_DelaySec, PMacro74_Entry6_TimMin, PMacro74_Entry6_TimSec, PMacro74_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro74_Entry7_DelayMin, PMacro74_Entry7_DelaySec, PMacro74_Entry7_TimMin, PMacro74_Entry7_TimSec, PMacro74_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro74_Entry8_DelayMin, PMacro74_Entry8_DelaySec, PMacro74_Entry8_TimMin, PMacro74_Entry8_TimSec, PMacro74_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro74_Entry9_DelayMin, PMacro74_Entry9_DelaySec, PMacro74_Entry9_TimMin, PMacro74_Entry9_TimSec, PMacro74_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro74_Entry10_DelayMin, PMacro74_Entry10_DelaySec, PMacro74_Entry10_TimMin, PMacro74_Entry10_TimSec, PMacro74_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro74_Entry11_DelayMin, PMacro74_Entry11_DelaySec, PMacro74_Entry11_TimMin, PMacro74_Entry11_TimSec, PMacro74_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro74_Entry12_DelayMin, PMacro74_Entry12_DelaySec, PMacro74_Entry12_TimMin, PMacro74_Entry12_TimSec, PMacro74_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro74_Entry13_DelayMin, PMacro74_Entry13_DelaySec, PMacro74_Entry13_TimMin, PMacro74_Entry13_TimSec, PMacro74_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro74_Entry14_DelayMin, PMacro74_Entry14_DelaySec, PMacro74_Entry14_TimMin, PMacro74_Entry14_TimSec, PMacro74_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro74_Entry15_DelayMin, PMacro74_Entry15_DelaySec, PMacro74_Entry15_TimMin, PMacro74_Entry15_TimSec, PMacro74_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR74_STRING};

const struct super_macro Macro75 = {PMacro75_NumEntries,
		         PMacro75_Entry1_DelayMin, PMacro75_Entry1_DelaySec, PMacro75_Entry1_TimMin, PMacro75_Entry1_TimSec, PMacro75_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro75_Entry2_DelayMin, PMacro75_Entry2_DelaySec, PMacro75_Entry2_TimMin, PMacro75_Entry2_TimSec, PMacro75_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro75_Entry3_DelayMin, PMacro75_Entry3_DelaySec, PMacro75_Entry3_TimMin, PMacro75_Entry3_TimSec, PMacro75_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro75_Entry4_DelayMin, PMacro75_Entry4_DelaySec, PMacro75_Entry4_TimMin, PMacro75_Entry4_TimSec, PMacro75_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro75_Entry5_DelayMin, PMacro75_Entry5_DelaySec, PMacro75_Entry5_TimMin, PMacro75_Entry5_TimSec, PMacro75_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro75_Entry6_DelayMin, PMacro75_Entry6_DelaySec, PMacro75_Entry6_TimMin, PMacro75_Entry6_TimSec, PMacro75_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro75_Entry7_DelayMin, PMacro75_Entry7_DelaySec, PMacro75_Entry7_TimMin, PMacro75_Entry7_TimSec, PMacro75_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro75_Entry8_DelayMin, PMacro75_Entry8_DelaySec, PMacro75_Entry8_TimMin, PMacro75_Entry8_TimSec, PMacro75_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro75_Entry9_DelayMin, PMacro75_Entry9_DelaySec, PMacro75_Entry9_TimMin, PMacro75_Entry9_TimSec, PMacro75_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro75_Entry10_DelayMin, PMacro75_Entry10_DelaySec, PMacro75_Entry10_TimMin, PMacro75_Entry10_TimSec, PMacro75_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro75_Entry11_DelayMin, PMacro75_Entry11_DelaySec, PMacro75_Entry11_TimMin, PMacro75_Entry11_TimSec, PMacro75_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro75_Entry12_DelayMin, PMacro75_Entry12_DelaySec, PMacro75_Entry12_TimMin, PMacro75_Entry12_TimSec, PMacro75_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro75_Entry13_DelayMin, PMacro75_Entry13_DelaySec, PMacro75_Entry13_TimMin, PMacro75_Entry13_TimSec, PMacro75_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro75_Entry14_DelayMin, PMacro75_Entry14_DelaySec, PMacro75_Entry14_TimMin, PMacro75_Entry14_TimSec, PMacro75_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro75_Entry15_DelayMin, PMacro75_Entry15_DelaySec, PMacro75_Entry15_TimMin, PMacro75_Entry15_TimSec, PMacro75_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR75_STRING};

const struct super_macro Macro76 = {PMacro76_NumEntries,
		         PMacro76_Entry1_DelayMin, PMacro76_Entry1_DelaySec, PMacro76_Entry1_TimMin, PMacro76_Entry1_TimSec, PMacro76_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro76_Entry2_DelayMin, PMacro76_Entry2_DelaySec, PMacro76_Entry2_TimMin, PMacro76_Entry2_TimSec, PMacro76_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro76_Entry3_DelayMin, PMacro76_Entry3_DelaySec, PMacro76_Entry3_TimMin, PMacro76_Entry3_TimSec, PMacro76_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro76_Entry4_DelayMin, PMacro76_Entry4_DelaySec, PMacro76_Entry4_TimMin, PMacro76_Entry4_TimSec, PMacro76_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro76_Entry5_DelayMin, PMacro76_Entry5_DelaySec, PMacro76_Entry5_TimMin, PMacro76_Entry5_TimSec, PMacro76_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro76_Entry6_DelayMin, PMacro76_Entry6_DelaySec, PMacro76_Entry6_TimMin, PMacro76_Entry6_TimSec, PMacro76_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro76_Entry7_DelayMin, PMacro76_Entry7_DelaySec, PMacro76_Entry7_TimMin, PMacro76_Entry7_TimSec, PMacro76_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro76_Entry8_DelayMin, PMacro76_Entry8_DelaySec, PMacro76_Entry8_TimMin, PMacro76_Entry8_TimSec, PMacro76_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro76_Entry9_DelayMin, PMacro76_Entry9_DelaySec, PMacro76_Entry9_TimMin, PMacro76_Entry9_TimSec, PMacro76_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro76_Entry10_DelayMin, PMacro76_Entry10_DelaySec, PMacro76_Entry10_TimMin, PMacro76_Entry10_TimSec, PMacro76_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro76_Entry11_DelayMin, PMacro76_Entry11_DelaySec, PMacro76_Entry11_TimMin, PMacro76_Entry11_TimSec, PMacro76_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro76_Entry12_DelayMin, PMacro76_Entry12_DelaySec, PMacro76_Entry12_TimMin, PMacro76_Entry12_TimSec, PMacro76_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro76_Entry13_DelayMin, PMacro76_Entry13_DelaySec, PMacro76_Entry13_TimMin, PMacro76_Entry13_TimSec, PMacro76_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro76_Entry14_DelayMin, PMacro76_Entry14_DelaySec, PMacro76_Entry14_TimMin, PMacro76_Entry14_TimSec, PMacro76_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro76_Entry15_DelayMin, PMacro76_Entry15_DelaySec, PMacro76_Entry15_TimMin, PMacro76_Entry15_TimSec, PMacro76_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR76_STRING};

const struct super_macro Macro77 = {PMacro77_NumEntries,
		         PMacro77_Entry1_DelayMin, PMacro77_Entry1_DelaySec, PMacro77_Entry1_TimMin, PMacro77_Entry1_TimSec, PMacro77_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro77_Entry2_DelayMin, PMacro77_Entry2_DelaySec, PMacro77_Entry2_TimMin, PMacro77_Entry2_TimSec, PMacro77_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro77_Entry3_DelayMin, PMacro77_Entry3_DelaySec, PMacro77_Entry3_TimMin, PMacro77_Entry3_TimSec, PMacro77_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro77_Entry4_DelayMin, PMacro77_Entry4_DelaySec, PMacro77_Entry4_TimMin, PMacro77_Entry4_TimSec, PMacro77_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro77_Entry5_DelayMin, PMacro77_Entry5_DelaySec, PMacro77_Entry5_TimMin, PMacro77_Entry5_TimSec, PMacro77_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro77_Entry6_DelayMin, PMacro77_Entry6_DelaySec, PMacro77_Entry6_TimMin, PMacro77_Entry6_TimSec, PMacro77_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro77_Entry7_DelayMin, PMacro77_Entry7_DelaySec, PMacro77_Entry7_TimMin, PMacro77_Entry7_TimSec, PMacro77_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro77_Entry8_DelayMin, PMacro77_Entry8_DelaySec, PMacro77_Entry8_TimMin, PMacro77_Entry8_TimSec, PMacro77_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro77_Entry9_DelayMin, PMacro77_Entry9_DelaySec, PMacro77_Entry9_TimMin, PMacro77_Entry9_TimSec, PMacro77_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro77_Entry10_DelayMin, PMacro77_Entry10_DelaySec, PMacro77_Entry10_TimMin, PMacro77_Entry10_TimSec, PMacro77_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro77_Entry11_DelayMin, PMacro77_Entry11_DelaySec, PMacro77_Entry11_TimMin, PMacro77_Entry11_TimSec, PMacro77_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro77_Entry12_DelayMin, PMacro77_Entry12_DelaySec, PMacro77_Entry12_TimMin, PMacro77_Entry12_TimSec, PMacro77_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro77_Entry13_DelayMin, PMacro77_Entry13_DelaySec, PMacro77_Entry13_TimMin, PMacro77_Entry13_TimSec, PMacro77_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro77_Entry14_DelayMin, PMacro77_Entry14_DelaySec, PMacro77_Entry14_TimMin, PMacro77_Entry14_TimSec, PMacro77_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro77_Entry15_DelayMin, PMacro77_Entry15_DelaySec, PMacro77_Entry15_TimMin, PMacro77_Entry15_TimSec, PMacro77_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR77_STRING};

const struct super_macro Macro78 = {PMacro78_NumEntries,
		         PMacro78_Entry1_DelayMin, PMacro78_Entry1_DelaySec, PMacro78_Entry1_TimMin, PMacro78_Entry1_TimSec, PMacro78_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro78_Entry2_DelayMin, PMacro78_Entry2_DelaySec, PMacro78_Entry2_TimMin, PMacro78_Entry2_TimSec, PMacro78_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro78_Entry3_DelayMin, PMacro78_Entry3_DelaySec, PMacro78_Entry3_TimMin, PMacro78_Entry3_TimSec, PMacro78_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro78_Entry4_DelayMin, PMacro78_Entry4_DelaySec, PMacro78_Entry4_TimMin, PMacro78_Entry4_TimSec, PMacro78_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro78_Entry5_DelayMin, PMacro78_Entry5_DelaySec, PMacro78_Entry5_TimMin, PMacro78_Entry5_TimSec, PMacro78_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro78_Entry6_DelayMin, PMacro78_Entry6_DelaySec, PMacro78_Entry6_TimMin, PMacro78_Entry6_TimSec, PMacro78_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro78_Entry7_DelayMin, PMacro78_Entry7_DelaySec, PMacro78_Entry7_TimMin, PMacro78_Entry7_TimSec, PMacro78_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro78_Entry8_DelayMin, PMacro78_Entry8_DelaySec, PMacro78_Entry8_TimMin, PMacro78_Entry8_TimSec, PMacro78_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro78_Entry9_DelayMin, PMacro78_Entry9_DelaySec, PMacro78_Entry9_TimMin, PMacro78_Entry9_TimSec, PMacro78_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro78_Entry10_DelayMin, PMacro78_Entry10_DelaySec, PMacro78_Entry10_TimMin, PMacro78_Entry10_TimSec, PMacro78_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro78_Entry11_DelayMin, PMacro78_Entry11_DelaySec, PMacro78_Entry11_TimMin, PMacro78_Entry11_TimSec, PMacro78_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro78_Entry12_DelayMin, PMacro78_Entry12_DelaySec, PMacro78_Entry12_TimMin, PMacro78_Entry12_TimSec, PMacro78_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro78_Entry13_DelayMin, PMacro78_Entry13_DelaySec, PMacro78_Entry13_TimMin, PMacro78_Entry13_TimSec, PMacro78_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro78_Entry14_DelayMin, PMacro78_Entry14_DelaySec, PMacro78_Entry14_TimMin, PMacro78_Entry14_TimSec, PMacro78_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro78_Entry15_DelayMin, PMacro78_Entry15_DelaySec, PMacro78_Entry15_TimMin, PMacro78_Entry15_TimSec, PMacro78_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR78_STRING};

const struct super_macro Macro79 = {PMacro79_NumEntries,
		         PMacro79_Entry1_DelayMin, PMacro79_Entry1_DelaySec, PMacro79_Entry1_TimMin, PMacro79_Entry1_TimSec, PMacro79_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro79_Entry2_DelayMin, PMacro79_Entry2_DelaySec, PMacro79_Entry2_TimMin, PMacro79_Entry2_TimSec, PMacro79_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro79_Entry3_DelayMin, PMacro79_Entry3_DelaySec, PMacro79_Entry3_TimMin, PMacro79_Entry3_TimSec, PMacro79_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro79_Entry4_DelayMin, PMacro79_Entry4_DelaySec, PMacro79_Entry4_TimMin, PMacro79_Entry4_TimSec, PMacro79_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro79_Entry5_DelayMin, PMacro79_Entry5_DelaySec, PMacro79_Entry5_TimMin, PMacro79_Entry5_TimSec, PMacro79_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro79_Entry6_DelayMin, PMacro79_Entry6_DelaySec, PMacro79_Entry6_TimMin, PMacro79_Entry6_TimSec, PMacro79_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro79_Entry7_DelayMin, PMacro79_Entry7_DelaySec, PMacro79_Entry7_TimMin, PMacro79_Entry7_TimSec, PMacro79_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro79_Entry8_DelayMin, PMacro79_Entry8_DelaySec, PMacro79_Entry8_TimMin, PMacro79_Entry8_TimSec, PMacro79_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro79_Entry9_DelayMin, PMacro79_Entry9_DelaySec, PMacro79_Entry9_TimMin, PMacro79_Entry9_TimSec, PMacro79_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro79_Entry10_DelayMin, PMacro79_Entry10_DelaySec, PMacro79_Entry10_TimMin, PMacro79_Entry10_TimSec, PMacro79_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro79_Entry11_DelayMin, PMacro79_Entry11_DelaySec, PMacro79_Entry11_TimMin, PMacro79_Entry11_TimSec, PMacro79_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro79_Entry12_DelayMin, PMacro79_Entry12_DelaySec, PMacro79_Entry12_TimMin, PMacro79_Entry12_TimSec, PMacro79_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro79_Entry13_DelayMin, PMacro79_Entry13_DelaySec, PMacro79_Entry13_TimMin, PMacro79_Entry13_TimSec, PMacro79_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro79_Entry14_DelayMin, PMacro79_Entry14_DelaySec, PMacro79_Entry14_TimMin, PMacro79_Entry14_TimSec, PMacro79_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro79_Entry15_DelayMin, PMacro79_Entry15_DelaySec, PMacro79_Entry15_TimMin, PMacro79_Entry15_TimSec, PMacro79_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR79_STRING};

const struct super_macro Macro80 = {PMacro80_NumEntries,
		         PMacro80_Entry1_DelayMin, PMacro80_Entry1_DelaySec, PMacro80_Entry1_TimMin, PMacro80_Entry1_TimSec, PMacro80_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro80_Entry2_DelayMin, PMacro80_Entry2_DelaySec, PMacro80_Entry2_TimMin, PMacro80_Entry2_TimSec, PMacro80_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro80_Entry3_DelayMin, PMacro80_Entry3_DelaySec, PMacro80_Entry3_TimMin, PMacro80_Entry3_TimSec, PMacro80_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro80_Entry4_DelayMin, PMacro80_Entry4_DelaySec, PMacro80_Entry4_TimMin, PMacro80_Entry4_TimSec, PMacro80_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro80_Entry5_DelayMin, PMacro80_Entry5_DelaySec, PMacro80_Entry5_TimMin, PMacro80_Entry5_TimSec, PMacro80_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro80_Entry6_DelayMin, PMacro80_Entry6_DelaySec, PMacro80_Entry6_TimMin, PMacro80_Entry6_TimSec, PMacro80_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro80_Entry7_DelayMin, PMacro80_Entry7_DelaySec, PMacro80_Entry7_TimMin, PMacro80_Entry7_TimSec, PMacro80_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro80_Entry8_DelayMin, PMacro80_Entry8_DelaySec, PMacro80_Entry8_TimMin, PMacro80_Entry8_TimSec, PMacro80_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro80_Entry9_DelayMin, PMacro80_Entry9_DelaySec, PMacro80_Entry9_TimMin, PMacro80_Entry9_TimSec, PMacro80_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro80_Entry10_DelayMin, PMacro80_Entry10_DelaySec, PMacro80_Entry10_TimMin, PMacro80_Entry10_TimSec, PMacro80_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro80_Entry11_DelayMin, PMacro80_Entry11_DelaySec, PMacro80_Entry11_TimMin, PMacro80_Entry11_TimSec, PMacro80_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro80_Entry12_DelayMin, PMacro80_Entry12_DelaySec, PMacro80_Entry12_TimMin, PMacro80_Entry12_TimSec, PMacro80_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro80_Entry13_DelayMin, PMacro80_Entry13_DelaySec, PMacro80_Entry13_TimMin, PMacro80_Entry13_TimSec, PMacro80_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro80_Entry14_DelayMin, PMacro80_Entry14_DelaySec, PMacro80_Entry14_TimMin, PMacro80_Entry14_TimSec, PMacro80_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro80_Entry15_DelayMin, PMacro80_Entry15_DelaySec, PMacro80_Entry15_TimMin, PMacro80_Entry15_TimSec, PMacro80_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR80_STRING};

const struct super_macro Macro81 = {PMacro81_NumEntries,
		         PMacro81_Entry1_DelayMin, PMacro81_Entry1_DelaySec, PMacro81_Entry1_TimMin, PMacro81_Entry1_TimSec, PMacro81_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro81_Entry2_DelayMin, PMacro81_Entry2_DelaySec, PMacro81_Entry2_TimMin, PMacro81_Entry2_TimSec, PMacro81_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro81_Entry3_DelayMin, PMacro81_Entry3_DelaySec, PMacro81_Entry3_TimMin, PMacro81_Entry3_TimSec, PMacro81_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro81_Entry4_DelayMin, PMacro81_Entry4_DelaySec, PMacro81_Entry4_TimMin, PMacro81_Entry4_TimSec, PMacro81_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro81_Entry5_DelayMin, PMacro81_Entry5_DelaySec, PMacro81_Entry5_TimMin, PMacro81_Entry5_TimSec, PMacro81_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro81_Entry6_DelayMin, PMacro81_Entry6_DelaySec, PMacro81_Entry6_TimMin, PMacro81_Entry6_TimSec, PMacro81_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro81_Entry7_DelayMin, PMacro81_Entry7_DelaySec, PMacro81_Entry7_TimMin, PMacro81_Entry7_TimSec, PMacro81_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro81_Entry8_DelayMin, PMacro81_Entry8_DelaySec, PMacro81_Entry8_TimMin, PMacro81_Entry8_TimSec, PMacro81_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro81_Entry9_DelayMin, PMacro81_Entry9_DelaySec, PMacro81_Entry9_TimMin, PMacro81_Entry9_TimSec, PMacro81_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro81_Entry10_DelayMin, PMacro81_Entry10_DelaySec, PMacro81_Entry10_TimMin, PMacro81_Entry10_TimSec, PMacro81_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro81_Entry11_DelayMin, PMacro81_Entry11_DelaySec, PMacro81_Entry11_TimMin, PMacro81_Entry11_TimSec, PMacro81_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro81_Entry12_DelayMin, PMacro81_Entry12_DelaySec, PMacro81_Entry12_TimMin, PMacro81_Entry12_TimSec, PMacro81_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro81_Entry13_DelayMin, PMacro81_Entry13_DelaySec, PMacro81_Entry13_TimMin, PMacro81_Entry13_TimSec, PMacro81_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro81_Entry14_DelayMin, PMacro81_Entry14_DelaySec, PMacro81_Entry14_TimMin, PMacro81_Entry14_TimSec, PMacro81_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro81_Entry15_DelayMin, PMacro81_Entry15_DelaySec, PMacro81_Entry15_TimMin, PMacro81_Entry15_TimSec, PMacro81_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR81_STRING};

const struct super_macro Macro82 = {PMacro82_NumEntries,
		         PMacro82_Entry1_DelayMin, PMacro82_Entry1_DelaySec, PMacro82_Entry1_TimMin, PMacro82_Entry1_TimSec, PMacro82_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro82_Entry2_DelayMin, PMacro82_Entry2_DelaySec, PMacro82_Entry2_TimMin, PMacro82_Entry2_TimSec, PMacro82_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro82_Entry3_DelayMin, PMacro82_Entry3_DelaySec, PMacro82_Entry3_TimMin, PMacro82_Entry3_TimSec, PMacro82_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro82_Entry4_DelayMin, PMacro82_Entry4_DelaySec, PMacro82_Entry4_TimMin, PMacro82_Entry4_TimSec, PMacro82_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro82_Entry5_DelayMin, PMacro82_Entry5_DelaySec, PMacro82_Entry5_TimMin, PMacro82_Entry5_TimSec, PMacro82_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro82_Entry6_DelayMin, PMacro82_Entry6_DelaySec, PMacro82_Entry6_TimMin, PMacro82_Entry6_TimSec, PMacro82_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro82_Entry7_DelayMin, PMacro82_Entry7_DelaySec, PMacro82_Entry7_TimMin, PMacro82_Entry7_TimSec, PMacro82_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro82_Entry8_DelayMin, PMacro82_Entry8_DelaySec, PMacro82_Entry8_TimMin, PMacro82_Entry8_TimSec, PMacro82_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro82_Entry9_DelayMin, PMacro82_Entry9_DelaySec, PMacro82_Entry9_TimMin, PMacro82_Entry9_TimSec, PMacro82_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro82_Entry10_DelayMin, PMacro82_Entry10_DelaySec, PMacro82_Entry10_TimMin, PMacro82_Entry10_TimSec, PMacro82_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro82_Entry11_DelayMin, PMacro82_Entry11_DelaySec, PMacro82_Entry11_TimMin, PMacro82_Entry11_TimSec, PMacro82_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro82_Entry12_DelayMin, PMacro82_Entry12_DelaySec, PMacro82_Entry12_TimMin, PMacro82_Entry12_TimSec, PMacro82_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro82_Entry13_DelayMin, PMacro82_Entry13_DelaySec, PMacro82_Entry13_TimMin, PMacro82_Entry13_TimSec, PMacro82_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro82_Entry14_DelayMin, PMacro82_Entry14_DelaySec, PMacro82_Entry14_TimMin, PMacro82_Entry14_TimSec, PMacro82_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro82_Entry15_DelayMin, PMacro82_Entry15_DelaySec, PMacro82_Entry15_TimMin, PMacro82_Entry15_TimSec, PMacro82_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR82_STRING};

const struct super_macro Macro83 = {PMacro83_NumEntries,
		         PMacro83_Entry1_DelayMin, PMacro83_Entry1_DelaySec, PMacro83_Entry1_TimMin, PMacro83_Entry1_TimSec, PMacro83_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro83_Entry2_DelayMin, PMacro83_Entry2_DelaySec, PMacro83_Entry2_TimMin, PMacro83_Entry2_TimSec, PMacro83_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro83_Entry3_DelayMin, PMacro83_Entry3_DelaySec, PMacro83_Entry3_TimMin, PMacro83_Entry3_TimSec, PMacro83_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro83_Entry4_DelayMin, PMacro83_Entry4_DelaySec, PMacro83_Entry4_TimMin, PMacro83_Entry4_TimSec, PMacro83_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro83_Entry5_DelayMin, PMacro83_Entry5_DelaySec, PMacro83_Entry5_TimMin, PMacro83_Entry5_TimSec, PMacro83_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro83_Entry6_DelayMin, PMacro83_Entry6_DelaySec, PMacro83_Entry6_TimMin, PMacro83_Entry6_TimSec, PMacro83_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro83_Entry7_DelayMin, PMacro83_Entry7_DelaySec, PMacro83_Entry7_TimMin, PMacro83_Entry7_TimSec, PMacro83_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro83_Entry8_DelayMin, PMacro83_Entry8_DelaySec, PMacro83_Entry8_TimMin, PMacro83_Entry8_TimSec, PMacro83_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro83_Entry9_DelayMin, PMacro83_Entry9_DelaySec, PMacro83_Entry9_TimMin, PMacro83_Entry9_TimSec, PMacro83_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro83_Entry10_DelayMin, PMacro83_Entry10_DelaySec, PMacro83_Entry10_TimMin, PMacro83_Entry10_TimSec, PMacro83_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro83_Entry11_DelayMin, PMacro83_Entry11_DelaySec, PMacro83_Entry11_TimMin, PMacro83_Entry11_TimSec, PMacro83_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro83_Entry12_DelayMin, PMacro83_Entry12_DelaySec, PMacro83_Entry12_TimMin, PMacro83_Entry12_TimSec, PMacro83_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro83_Entry13_DelayMin, PMacro83_Entry13_DelaySec, PMacro83_Entry13_TimMin, PMacro83_Entry13_TimSec, PMacro83_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro83_Entry14_DelayMin, PMacro83_Entry14_DelaySec, PMacro83_Entry14_TimMin, PMacro83_Entry14_TimSec, PMacro83_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro83_Entry15_DelayMin, PMacro83_Entry15_DelaySec, PMacro83_Entry15_TimMin, PMacro83_Entry15_TimSec, PMacro83_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR83_STRING};

const struct super_macro Macro84 = {PMacro84_NumEntries,
		         PMacro84_Entry1_DelayMin, PMacro84_Entry1_DelaySec, PMacro84_Entry1_TimMin, PMacro84_Entry1_TimSec, PMacro84_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro84_Entry2_DelayMin, PMacro84_Entry2_DelaySec, PMacro84_Entry2_TimMin, PMacro84_Entry2_TimSec, PMacro84_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro84_Entry3_DelayMin, PMacro84_Entry3_DelaySec, PMacro84_Entry3_TimMin, PMacro84_Entry3_TimSec, PMacro84_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro84_Entry4_DelayMin, PMacro84_Entry4_DelaySec, PMacro84_Entry4_TimMin, PMacro84_Entry4_TimSec, PMacro84_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro84_Entry5_DelayMin, PMacro84_Entry5_DelaySec, PMacro84_Entry5_TimMin, PMacro84_Entry5_TimSec, PMacro84_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro84_Entry6_DelayMin, PMacro84_Entry6_DelaySec, PMacro84_Entry6_TimMin, PMacro84_Entry6_TimSec, PMacro84_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro84_Entry7_DelayMin, PMacro84_Entry7_DelaySec, PMacro84_Entry7_TimMin, PMacro84_Entry7_TimSec, PMacro84_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro84_Entry8_DelayMin, PMacro84_Entry8_DelaySec, PMacro84_Entry8_TimMin, PMacro84_Entry8_TimSec, PMacro84_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro84_Entry9_DelayMin, PMacro84_Entry9_DelaySec, PMacro84_Entry9_TimMin, PMacro84_Entry9_TimSec, PMacro84_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro84_Entry10_DelayMin, PMacro84_Entry10_DelaySec, PMacro84_Entry10_TimMin, PMacro84_Entry10_TimSec, PMacro84_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro84_Entry11_DelayMin, PMacro84_Entry11_DelaySec, PMacro84_Entry11_TimMin, PMacro84_Entry11_TimSec, PMacro84_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro84_Entry12_DelayMin, PMacro84_Entry12_DelaySec, PMacro84_Entry12_TimMin, PMacro84_Entry12_TimSec, PMacro84_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro84_Entry13_DelayMin, PMacro84_Entry13_DelaySec, PMacro84_Entry13_TimMin, PMacro84_Entry13_TimSec, PMacro84_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro84_Entry14_DelayMin, PMacro84_Entry14_DelaySec, PMacro84_Entry14_TimMin, PMacro84_Entry14_TimSec, PMacro84_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro84_Entry15_DelayMin, PMacro84_Entry15_DelaySec, PMacro84_Entry15_TimMin, PMacro84_Entry15_TimSec, PMacro84_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR84_STRING};

const struct super_macro Macro85 = {PMacro85_NumEntries,
		         PMacro85_Entry1_DelayMin, PMacro85_Entry1_DelaySec, PMacro85_Entry1_TimMin, PMacro85_Entry1_TimSec, PMacro85_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro85_Entry2_DelayMin, PMacro85_Entry2_DelaySec, PMacro85_Entry2_TimMin, PMacro85_Entry2_TimSec, PMacro85_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro85_Entry3_DelayMin, PMacro85_Entry3_DelaySec, PMacro85_Entry3_TimMin, PMacro85_Entry3_TimSec, PMacro85_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro85_Entry4_DelayMin, PMacro85_Entry4_DelaySec, PMacro85_Entry4_TimMin, PMacro85_Entry4_TimSec, PMacro85_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro85_Entry5_DelayMin, PMacro85_Entry5_DelaySec, PMacro85_Entry5_TimMin, PMacro85_Entry5_TimSec, PMacro85_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro85_Entry6_DelayMin, PMacro85_Entry6_DelaySec, PMacro85_Entry6_TimMin, PMacro85_Entry6_TimSec, PMacro85_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro85_Entry7_DelayMin, PMacro85_Entry7_DelaySec, PMacro85_Entry7_TimMin, PMacro85_Entry7_TimSec, PMacro85_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro85_Entry8_DelayMin, PMacro85_Entry8_DelaySec, PMacro85_Entry8_TimMin, PMacro85_Entry8_TimSec, PMacro85_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro85_Entry9_DelayMin, PMacro85_Entry9_DelaySec, PMacro85_Entry9_TimMin, PMacro85_Entry9_TimSec, PMacro85_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro85_Entry10_DelayMin, PMacro85_Entry10_DelaySec, PMacro85_Entry10_TimMin, PMacro85_Entry10_TimSec, PMacro85_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro85_Entry11_DelayMin, PMacro85_Entry11_DelaySec, PMacro85_Entry11_TimMin, PMacro85_Entry11_TimSec, PMacro85_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro85_Entry12_DelayMin, PMacro85_Entry12_DelaySec, PMacro85_Entry12_TimMin, PMacro85_Entry12_TimSec, PMacro85_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro85_Entry13_DelayMin, PMacro85_Entry13_DelaySec, PMacro85_Entry13_TimMin, PMacro85_Entry13_TimSec, PMacro85_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro85_Entry14_DelayMin, PMacro85_Entry14_DelaySec, PMacro85_Entry14_TimMin, PMacro85_Entry14_TimSec, PMacro85_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro85_Entry15_DelayMin, PMacro85_Entry15_DelaySec, PMacro85_Entry15_TimMin, PMacro85_Entry15_TimSec, PMacro85_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR85_STRING};

const struct super_macro Macro86 = {PMacro86_NumEntries,
		         PMacro86_Entry1_DelayMin, PMacro86_Entry1_DelaySec, PMacro86_Entry1_TimMin, PMacro86_Entry1_TimSec, PMacro86_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro86_Entry2_DelayMin, PMacro86_Entry2_DelaySec, PMacro86_Entry2_TimMin, PMacro86_Entry2_TimSec, PMacro86_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro86_Entry3_DelayMin, PMacro86_Entry3_DelaySec, PMacro86_Entry3_TimMin, PMacro86_Entry3_TimSec, PMacro86_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro86_Entry4_DelayMin, PMacro86_Entry4_DelaySec, PMacro86_Entry4_TimMin, PMacro86_Entry4_TimSec, PMacro86_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro86_Entry5_DelayMin, PMacro86_Entry5_DelaySec, PMacro86_Entry5_TimMin, PMacro86_Entry5_TimSec, PMacro86_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro86_Entry6_DelayMin, PMacro86_Entry6_DelaySec, PMacro86_Entry6_TimMin, PMacro86_Entry6_TimSec, PMacro86_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro86_Entry7_DelayMin, PMacro86_Entry7_DelaySec, PMacro86_Entry7_TimMin, PMacro86_Entry7_TimSec, PMacro86_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro86_Entry8_DelayMin, PMacro86_Entry8_DelaySec, PMacro86_Entry8_TimMin, PMacro86_Entry8_TimSec, PMacro86_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro86_Entry9_DelayMin, PMacro86_Entry9_DelaySec, PMacro86_Entry9_TimMin, PMacro86_Entry9_TimSec, PMacro86_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro86_Entry10_DelayMin, PMacro86_Entry10_DelaySec, PMacro86_Entry10_TimMin, PMacro86_Entry10_TimSec, PMacro86_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro86_Entry11_DelayMin, PMacro86_Entry11_DelaySec, PMacro86_Entry11_TimMin, PMacro86_Entry11_TimSec, PMacro86_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro86_Entry12_DelayMin, PMacro86_Entry12_DelaySec, PMacro86_Entry12_TimMin, PMacro86_Entry12_TimSec, PMacro86_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro86_Entry13_DelayMin, PMacro86_Entry13_DelaySec, PMacro86_Entry13_TimMin, PMacro86_Entry13_TimSec, PMacro86_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro86_Entry14_DelayMin, PMacro86_Entry14_DelaySec, PMacro86_Entry14_TimMin, PMacro86_Entry14_TimSec, PMacro86_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro86_Entry15_DelayMin, PMacro86_Entry15_DelaySec, PMacro86_Entry15_TimMin, PMacro86_Entry15_TimSec, PMacro86_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR86_STRING};

const struct super_macro Macro87 = {PMacro87_NumEntries,
		         PMacro87_Entry1_DelayMin, PMacro87_Entry1_DelaySec, PMacro87_Entry1_TimMin, PMacro87_Entry1_TimSec, PMacro87_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro87_Entry2_DelayMin, PMacro87_Entry2_DelaySec, PMacro87_Entry2_TimMin, PMacro87_Entry2_TimSec, PMacro87_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro87_Entry3_DelayMin, PMacro87_Entry3_DelaySec, PMacro87_Entry3_TimMin, PMacro87_Entry3_TimSec, PMacro87_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro87_Entry4_DelayMin, PMacro87_Entry4_DelaySec, PMacro87_Entry4_TimMin, PMacro87_Entry4_TimSec, PMacro87_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro87_Entry5_DelayMin, PMacro87_Entry5_DelaySec, PMacro87_Entry5_TimMin, PMacro87_Entry5_TimSec, PMacro87_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro87_Entry6_DelayMin, PMacro87_Entry6_DelaySec, PMacro87_Entry6_TimMin, PMacro87_Entry6_TimSec, PMacro87_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro87_Entry7_DelayMin, PMacro87_Entry7_DelaySec, PMacro87_Entry7_TimMin, PMacro87_Entry7_TimSec, PMacro87_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro87_Entry8_DelayMin, PMacro87_Entry8_DelaySec, PMacro87_Entry8_TimMin, PMacro87_Entry8_TimSec, PMacro87_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro87_Entry9_DelayMin, PMacro87_Entry9_DelaySec, PMacro87_Entry9_TimMin, PMacro87_Entry9_TimSec, PMacro87_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro87_Entry10_DelayMin, PMacro87_Entry10_DelaySec, PMacro87_Entry10_TimMin, PMacro87_Entry10_TimSec, PMacro87_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro87_Entry11_DelayMin, PMacro87_Entry11_DelaySec, PMacro87_Entry11_TimMin, PMacro87_Entry11_TimSec, PMacro87_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro87_Entry12_DelayMin, PMacro87_Entry12_DelaySec, PMacro87_Entry12_TimMin, PMacro87_Entry12_TimSec, PMacro87_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro87_Entry13_DelayMin, PMacro87_Entry13_DelaySec, PMacro87_Entry13_TimMin, PMacro87_Entry13_TimSec, PMacro87_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro87_Entry14_DelayMin, PMacro87_Entry14_DelaySec, PMacro87_Entry14_TimMin, PMacro87_Entry14_TimSec, PMacro87_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro87_Entry15_DelayMin, PMacro87_Entry15_DelaySec, PMacro87_Entry15_TimMin, PMacro87_Entry15_TimSec, PMacro87_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR87_STRING};

const struct super_macro Macro88 = {PMacro88_NumEntries,
		         PMacro88_Entry1_DelayMin, PMacro88_Entry1_DelaySec, PMacro88_Entry1_TimMin, PMacro88_Entry1_TimSec, PMacro88_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro88_Entry2_DelayMin, PMacro88_Entry2_DelaySec, PMacro88_Entry2_TimMin, PMacro88_Entry2_TimSec, PMacro88_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro88_Entry3_DelayMin, PMacro88_Entry3_DelaySec, PMacro88_Entry3_TimMin, PMacro88_Entry3_TimSec, PMacro88_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro88_Entry4_DelayMin, PMacro88_Entry4_DelaySec, PMacro88_Entry4_TimMin, PMacro88_Entry4_TimSec, PMacro88_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro88_Entry5_DelayMin, PMacro88_Entry5_DelaySec, PMacro88_Entry5_TimMin, PMacro88_Entry5_TimSec, PMacro88_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro88_Entry6_DelayMin, PMacro88_Entry6_DelaySec, PMacro88_Entry6_TimMin, PMacro88_Entry6_TimSec, PMacro88_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro88_Entry7_DelayMin, PMacro88_Entry7_DelaySec, PMacro88_Entry7_TimMin, PMacro88_Entry7_TimSec, PMacro88_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro88_Entry8_DelayMin, PMacro88_Entry8_DelaySec, PMacro88_Entry8_TimMin, PMacro88_Entry8_TimSec, PMacro88_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro88_Entry9_DelayMin, PMacro88_Entry9_DelaySec, PMacro88_Entry9_TimMin, PMacro88_Entry9_TimSec, PMacro88_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro88_Entry10_DelayMin, PMacro88_Entry10_DelaySec, PMacro88_Entry10_TimMin, PMacro88_Entry10_TimSec, PMacro88_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro88_Entry11_DelayMin, PMacro88_Entry11_DelaySec, PMacro88_Entry11_TimMin, PMacro88_Entry11_TimSec, PMacro88_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro88_Entry12_DelayMin, PMacro88_Entry12_DelaySec, PMacro88_Entry12_TimMin, PMacro88_Entry12_TimSec, PMacro88_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro88_Entry13_DelayMin, PMacro88_Entry13_DelaySec, PMacro88_Entry13_TimMin, PMacro88_Entry13_TimSec, PMacro88_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro88_Entry14_DelayMin, PMacro88_Entry14_DelaySec, PMacro88_Entry14_TimMin, PMacro88_Entry14_TimSec, PMacro88_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro88_Entry15_DelayMin, PMacro88_Entry15_DelaySec, PMacro88_Entry15_TimMin, PMacro88_Entry15_TimSec, PMacro88_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR88_STRING};

const struct super_macro Macro89 = {PMacro89_NumEntries,
		         PMacro89_Entry1_DelayMin, PMacro89_Entry1_DelaySec, PMacro89_Entry1_TimMin, PMacro89_Entry1_TimSec, PMacro89_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro89_Entry2_DelayMin, PMacro89_Entry2_DelaySec, PMacro89_Entry2_TimMin, PMacro89_Entry2_TimSec, PMacro89_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro89_Entry3_DelayMin, PMacro89_Entry3_DelaySec, PMacro89_Entry3_TimMin, PMacro89_Entry3_TimSec, PMacro89_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro89_Entry4_DelayMin, PMacro89_Entry4_DelaySec, PMacro89_Entry4_TimMin, PMacro89_Entry4_TimSec, PMacro89_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro89_Entry5_DelayMin, PMacro89_Entry5_DelaySec, PMacro89_Entry5_TimMin, PMacro89_Entry5_TimSec, PMacro89_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro89_Entry6_DelayMin, PMacro89_Entry6_DelaySec, PMacro89_Entry6_TimMin, PMacro89_Entry6_TimSec, PMacro89_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro89_Entry7_DelayMin, PMacro89_Entry7_DelaySec, PMacro89_Entry7_TimMin, PMacro89_Entry7_TimSec, PMacro89_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro89_Entry8_DelayMin, PMacro89_Entry8_DelaySec, PMacro89_Entry8_TimMin, PMacro89_Entry8_TimSec, PMacro89_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro89_Entry9_DelayMin, PMacro89_Entry9_DelaySec, PMacro89_Entry9_TimMin, PMacro89_Entry9_TimSec, PMacro89_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro89_Entry10_DelayMin, PMacro89_Entry10_DelaySec, PMacro89_Entry10_TimMin, PMacro89_Entry10_TimSec, PMacro89_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro89_Entry11_DelayMin, PMacro89_Entry11_DelaySec, PMacro89_Entry11_TimMin, PMacro89_Entry11_TimSec, PMacro89_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro89_Entry12_DelayMin, PMacro89_Entry12_DelaySec, PMacro89_Entry12_TimMin, PMacro89_Entry12_TimSec, PMacro89_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro89_Entry13_DelayMin, PMacro89_Entry13_DelaySec, PMacro89_Entry13_TimMin, PMacro89_Entry13_TimSec, PMacro89_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro89_Entry14_DelayMin, PMacro89_Entry14_DelaySec, PMacro89_Entry14_TimMin, PMacro89_Entry14_TimSec, PMacro89_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro89_Entry15_DelayMin, PMacro89_Entry15_DelaySec, PMacro89_Entry15_TimMin, PMacro89_Entry15_TimSec, PMacro89_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR89_STRING};

const struct super_macro Macro90 = {PMacro90_NumEntries,
		         PMacro90_Entry1_DelayMin, PMacro90_Entry1_DelaySec, PMacro90_Entry1_TimMin, PMacro90_Entry1_TimSec, PMacro90_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro90_Entry2_DelayMin, PMacro90_Entry2_DelaySec, PMacro90_Entry2_TimMin, PMacro90_Entry2_TimSec, PMacro90_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro90_Entry3_DelayMin, PMacro90_Entry3_DelaySec, PMacro90_Entry3_TimMin, PMacro90_Entry3_TimSec, PMacro90_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro90_Entry4_DelayMin, PMacro90_Entry4_DelaySec, PMacro90_Entry4_TimMin, PMacro90_Entry4_TimSec, PMacro90_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro90_Entry5_DelayMin, PMacro90_Entry5_DelaySec, PMacro90_Entry5_TimMin, PMacro90_Entry5_TimSec, PMacro90_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro90_Entry6_DelayMin, PMacro90_Entry6_DelaySec, PMacro90_Entry6_TimMin, PMacro90_Entry6_TimSec, PMacro90_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro90_Entry7_DelayMin, PMacro90_Entry7_DelaySec, PMacro90_Entry7_TimMin, PMacro90_Entry7_TimSec, PMacro90_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro90_Entry8_DelayMin, PMacro90_Entry8_DelaySec, PMacro90_Entry8_TimMin, PMacro90_Entry8_TimSec, PMacro90_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro90_Entry9_DelayMin, PMacro90_Entry9_DelaySec, PMacro90_Entry9_TimMin, PMacro90_Entry9_TimSec, PMacro90_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro90_Entry10_DelayMin, PMacro90_Entry10_DelaySec, PMacro90_Entry10_TimMin, PMacro90_Entry10_TimSec, PMacro90_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro90_Entry11_DelayMin, PMacro90_Entry11_DelaySec, PMacro90_Entry11_TimMin, PMacro90_Entry11_TimSec, PMacro90_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro90_Entry12_DelayMin, PMacro90_Entry12_DelaySec, PMacro90_Entry12_TimMin, PMacro90_Entry12_TimSec, PMacro90_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro90_Entry13_DelayMin, PMacro90_Entry13_DelaySec, PMacro90_Entry13_TimMin, PMacro90_Entry13_TimSec, PMacro90_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro90_Entry14_DelayMin, PMacro90_Entry14_DelaySec, PMacro90_Entry14_TimMin, PMacro90_Entry14_TimSec, PMacro90_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro90_Entry15_DelayMin, PMacro90_Entry15_DelaySec, PMacro90_Entry15_TimMin, PMacro90_Entry15_TimSec, PMacro90_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR90_STRING};

const struct super_macro Macro91 = {PMacro91_NumEntries,
		         PMacro91_Entry1_DelayMin, PMacro91_Entry1_DelaySec, PMacro91_Entry1_TimMin, PMacro91_Entry1_TimSec, PMacro91_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro91_Entry2_DelayMin, PMacro91_Entry2_DelaySec, PMacro91_Entry2_TimMin, PMacro91_Entry2_TimSec, PMacro91_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro91_Entry3_DelayMin, PMacro91_Entry3_DelaySec, PMacro91_Entry3_TimMin, PMacro91_Entry3_TimSec, PMacro91_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro91_Entry4_DelayMin, PMacro91_Entry4_DelaySec, PMacro91_Entry4_TimMin, PMacro91_Entry4_TimSec, PMacro91_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro91_Entry5_DelayMin, PMacro91_Entry5_DelaySec, PMacro91_Entry5_TimMin, PMacro91_Entry5_TimSec, PMacro91_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro91_Entry6_DelayMin, PMacro91_Entry6_DelaySec, PMacro91_Entry6_TimMin, PMacro91_Entry6_TimSec, PMacro91_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro91_Entry7_DelayMin, PMacro91_Entry7_DelaySec, PMacro91_Entry7_TimMin, PMacro91_Entry7_TimSec, PMacro91_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro91_Entry8_DelayMin, PMacro91_Entry8_DelaySec, PMacro91_Entry8_TimMin, PMacro91_Entry8_TimSec, PMacro91_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro91_Entry9_DelayMin, PMacro91_Entry9_DelaySec, PMacro91_Entry9_TimMin, PMacro91_Entry9_TimSec, PMacro91_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro91_Entry10_DelayMin, PMacro91_Entry10_DelaySec, PMacro91_Entry10_TimMin, PMacro91_Entry10_TimSec, PMacro91_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro91_Entry11_DelayMin, PMacro91_Entry11_DelaySec, PMacro91_Entry11_TimMin, PMacro91_Entry11_TimSec, PMacro91_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro91_Entry12_DelayMin, PMacro91_Entry12_DelaySec, PMacro91_Entry12_TimMin, PMacro91_Entry12_TimSec, PMacro91_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro91_Entry13_DelayMin, PMacro91_Entry13_DelaySec, PMacro91_Entry13_TimMin, PMacro91_Entry13_TimSec, PMacro91_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro91_Entry14_DelayMin, PMacro91_Entry14_DelaySec, PMacro91_Entry14_TimMin, PMacro91_Entry14_TimSec, PMacro91_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro91_Entry15_DelayMin, PMacro91_Entry15_DelaySec, PMacro91_Entry15_TimMin, PMacro91_Entry15_TimSec, PMacro91_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR91_STRING};

const struct super_macro Macro92 = {PMacro92_NumEntries,
		         PMacro92_Entry1_DelayMin, PMacro92_Entry1_DelaySec, PMacro92_Entry1_TimMin, PMacro92_Entry1_TimSec, PMacro92_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro92_Entry2_DelayMin, PMacro92_Entry2_DelaySec, PMacro92_Entry2_TimMin, PMacro92_Entry2_TimSec, PMacro92_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro92_Entry3_DelayMin, PMacro92_Entry3_DelaySec, PMacro92_Entry3_TimMin, PMacro92_Entry3_TimSec, PMacro92_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro92_Entry4_DelayMin, PMacro92_Entry4_DelaySec, PMacro92_Entry4_TimMin, PMacro92_Entry4_TimSec, PMacro92_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro92_Entry5_DelayMin, PMacro92_Entry5_DelaySec, PMacro92_Entry5_TimMin, PMacro92_Entry5_TimSec, PMacro92_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro92_Entry6_DelayMin, PMacro92_Entry6_DelaySec, PMacro92_Entry6_TimMin, PMacro92_Entry6_TimSec, PMacro92_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro92_Entry7_DelayMin, PMacro92_Entry7_DelaySec, PMacro92_Entry7_TimMin, PMacro92_Entry7_TimSec, PMacro92_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro92_Entry8_DelayMin, PMacro92_Entry8_DelaySec, PMacro92_Entry8_TimMin, PMacro92_Entry8_TimSec, PMacro92_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro92_Entry9_DelayMin, PMacro92_Entry9_DelaySec, PMacro92_Entry9_TimMin, PMacro92_Entry9_TimSec, PMacro92_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro92_Entry10_DelayMin, PMacro92_Entry10_DelaySec, PMacro92_Entry10_TimMin, PMacro92_Entry10_TimSec, PMacro92_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro92_Entry11_DelayMin, PMacro92_Entry11_DelaySec, PMacro92_Entry11_TimMin, PMacro92_Entry11_TimSec, PMacro92_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro92_Entry12_DelayMin, PMacro92_Entry12_DelaySec, PMacro92_Entry12_TimMin, PMacro92_Entry12_TimSec, PMacro92_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro92_Entry13_DelayMin, PMacro92_Entry13_DelaySec, PMacro92_Entry13_TimMin, PMacro92_Entry13_TimSec, PMacro92_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro92_Entry14_DelayMin, PMacro92_Entry14_DelaySec, PMacro92_Entry14_TimMin, PMacro92_Entry14_TimSec, PMacro92_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro92_Entry15_DelayMin, PMacro92_Entry15_DelaySec, PMacro92_Entry15_TimMin, PMacro92_Entry15_TimSec, PMacro92_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR92_STRING};

const struct super_macro Macro93 = {PMacro93_NumEntries,
		         PMacro93_Entry1_DelayMin, PMacro93_Entry1_DelaySec, PMacro93_Entry1_TimMin, PMacro93_Entry1_TimSec, PMacro93_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro93_Entry2_DelayMin, PMacro93_Entry2_DelaySec, PMacro93_Entry2_TimMin, PMacro93_Entry2_TimSec, PMacro93_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro93_Entry3_DelayMin, PMacro93_Entry3_DelaySec, PMacro93_Entry3_TimMin, PMacro93_Entry3_TimSec, PMacro93_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro93_Entry4_DelayMin, PMacro93_Entry4_DelaySec, PMacro93_Entry4_TimMin, PMacro93_Entry4_TimSec, PMacro93_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro93_Entry5_DelayMin, PMacro93_Entry5_DelaySec, PMacro93_Entry5_TimMin, PMacro93_Entry5_TimSec, PMacro93_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro93_Entry6_DelayMin, PMacro93_Entry6_DelaySec, PMacro93_Entry6_TimMin, PMacro93_Entry6_TimSec, PMacro93_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro93_Entry7_DelayMin, PMacro93_Entry7_DelaySec, PMacro93_Entry7_TimMin, PMacro93_Entry7_TimSec, PMacro93_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro93_Entry8_DelayMin, PMacro93_Entry8_DelaySec, PMacro93_Entry8_TimMin, PMacro93_Entry8_TimSec, PMacro93_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro93_Entry9_DelayMin, PMacro93_Entry9_DelaySec, PMacro93_Entry9_TimMin, PMacro93_Entry9_TimSec, PMacro93_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro93_Entry10_DelayMin, PMacro93_Entry10_DelaySec, PMacro93_Entry10_TimMin, PMacro93_Entry10_TimSec, PMacro93_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro93_Entry11_DelayMin, PMacro93_Entry11_DelaySec, PMacro93_Entry11_TimMin, PMacro93_Entry11_TimSec, PMacro93_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro93_Entry12_DelayMin, PMacro93_Entry12_DelaySec, PMacro93_Entry12_TimMin, PMacro93_Entry12_TimSec, PMacro93_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro93_Entry13_DelayMin, PMacro93_Entry13_DelaySec, PMacro93_Entry13_TimMin, PMacro93_Entry13_TimSec, PMacro93_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro93_Entry14_DelayMin, PMacro93_Entry14_DelaySec, PMacro93_Entry14_TimMin, PMacro93_Entry14_TimSec, PMacro93_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro93_Entry15_DelayMin, PMacro93_Entry15_DelaySec, PMacro93_Entry15_TimMin, PMacro93_Entry15_TimSec, PMacro93_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR93_STRING};

const struct super_macro Macro94 = {PMacro94_NumEntries,
		         PMacro94_Entry1_DelayMin, PMacro94_Entry1_DelaySec, PMacro94_Entry1_TimMin, PMacro94_Entry1_TimSec, PMacro94_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro94_Entry2_DelayMin, PMacro94_Entry2_DelaySec, PMacro94_Entry2_TimMin, PMacro94_Entry2_TimSec, PMacro94_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro94_Entry3_DelayMin, PMacro94_Entry3_DelaySec, PMacro94_Entry3_TimMin, PMacro94_Entry3_TimSec, PMacro94_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro94_Entry4_DelayMin, PMacro94_Entry4_DelaySec, PMacro94_Entry4_TimMin, PMacro94_Entry4_TimSec, PMacro94_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro94_Entry5_DelayMin, PMacro94_Entry5_DelaySec, PMacro94_Entry5_TimMin, PMacro94_Entry5_TimSec, PMacro94_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro94_Entry6_DelayMin, PMacro94_Entry6_DelaySec, PMacro94_Entry6_TimMin, PMacro94_Entry6_TimSec, PMacro94_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro94_Entry7_DelayMin, PMacro94_Entry7_DelaySec, PMacro94_Entry7_TimMin, PMacro94_Entry7_TimSec, PMacro94_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro94_Entry8_DelayMin, PMacro94_Entry8_DelaySec, PMacro94_Entry8_TimMin, PMacro94_Entry8_TimSec, PMacro94_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro94_Entry9_DelayMin, PMacro94_Entry9_DelaySec, PMacro94_Entry9_TimMin, PMacro94_Entry9_TimSec, PMacro94_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro94_Entry10_DelayMin, PMacro94_Entry10_DelaySec, PMacro94_Entry10_TimMin, PMacro94_Entry10_TimSec, PMacro94_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro94_Entry11_DelayMin, PMacro94_Entry11_DelaySec, PMacro94_Entry11_TimMin, PMacro94_Entry11_TimSec, PMacro94_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro94_Entry12_DelayMin, PMacro94_Entry12_DelaySec, PMacro94_Entry12_TimMin, PMacro94_Entry12_TimSec, PMacro94_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro94_Entry13_DelayMin, PMacro94_Entry13_DelaySec, PMacro94_Entry13_TimMin, PMacro94_Entry13_TimSec, PMacro94_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro94_Entry14_DelayMin, PMacro94_Entry14_DelaySec, PMacro94_Entry14_TimMin, PMacro94_Entry14_TimSec, PMacro94_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro94_Entry15_DelayMin, PMacro94_Entry15_DelaySec, PMacro94_Entry15_TimMin, PMacro94_Entry15_TimSec, PMacro94_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR94_STRING};

const struct super_macro Macro95 = {PMacro95_NumEntries,
		         PMacro95_Entry1_DelayMin, PMacro95_Entry1_DelaySec, PMacro95_Entry1_TimMin, PMacro95_Entry1_TimSec, PMacro95_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro95_Entry2_DelayMin, PMacro95_Entry2_DelaySec, PMacro95_Entry2_TimMin, PMacro95_Entry2_TimSec, PMacro95_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro95_Entry3_DelayMin, PMacro95_Entry3_DelaySec, PMacro95_Entry3_TimMin, PMacro95_Entry3_TimSec, PMacro95_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro95_Entry4_DelayMin, PMacro95_Entry4_DelaySec, PMacro95_Entry4_TimMin, PMacro95_Entry4_TimSec, PMacro95_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro95_Entry5_DelayMin, PMacro95_Entry5_DelaySec, PMacro95_Entry5_TimMin, PMacro95_Entry5_TimSec, PMacro95_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro95_Entry6_DelayMin, PMacro95_Entry6_DelaySec, PMacro95_Entry6_TimMin, PMacro95_Entry6_TimSec, PMacro95_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro95_Entry7_DelayMin, PMacro95_Entry7_DelaySec, PMacro95_Entry7_TimMin, PMacro95_Entry7_TimSec, PMacro95_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro95_Entry8_DelayMin, PMacro95_Entry8_DelaySec, PMacro95_Entry8_TimMin, PMacro95_Entry8_TimSec, PMacro95_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro95_Entry9_DelayMin, PMacro95_Entry9_DelaySec, PMacro95_Entry9_TimMin, PMacro95_Entry9_TimSec, PMacro95_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro95_Entry10_DelayMin, PMacro95_Entry10_DelaySec, PMacro95_Entry10_TimMin, PMacro95_Entry10_TimSec, PMacro95_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro95_Entry11_DelayMin, PMacro95_Entry11_DelaySec, PMacro95_Entry11_TimMin, PMacro95_Entry11_TimSec, PMacro95_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro95_Entry12_DelayMin, PMacro95_Entry12_DelaySec, PMacro95_Entry12_TimMin, PMacro95_Entry12_TimSec, PMacro95_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro95_Entry13_DelayMin, PMacro95_Entry13_DelaySec, PMacro95_Entry13_TimMin, PMacro95_Entry13_TimSec, PMacro95_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro95_Entry14_DelayMin, PMacro95_Entry14_DelaySec, PMacro95_Entry14_TimMin, PMacro95_Entry14_TimSec, PMacro95_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro95_Entry15_DelayMin, PMacro95_Entry15_DelaySec, PMacro95_Entry15_TimMin, PMacro95_Entry15_TimSec, PMacro95_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR95_STRING};

const struct super_macro Macro96 = {PMacro96_NumEntries,
		         PMacro96_Entry1_DelayMin, PMacro96_Entry1_DelaySec, PMacro96_Entry1_TimMin, PMacro96_Entry1_TimSec, PMacro96_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro96_Entry2_DelayMin, PMacro96_Entry2_DelaySec, PMacro96_Entry2_TimMin, PMacro96_Entry2_TimSec, PMacro96_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro96_Entry3_DelayMin, PMacro96_Entry3_DelaySec, PMacro96_Entry3_TimMin, PMacro96_Entry3_TimSec, PMacro96_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro96_Entry4_DelayMin, PMacro96_Entry4_DelaySec, PMacro96_Entry4_TimMin, PMacro96_Entry4_TimSec, PMacro96_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro96_Entry5_DelayMin, PMacro96_Entry5_DelaySec, PMacro96_Entry5_TimMin, PMacro96_Entry5_TimSec, PMacro96_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro96_Entry6_DelayMin, PMacro96_Entry6_DelaySec, PMacro96_Entry6_TimMin, PMacro96_Entry6_TimSec, PMacro96_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro96_Entry7_DelayMin, PMacro96_Entry7_DelaySec, PMacro96_Entry7_TimMin, PMacro96_Entry7_TimSec, PMacro96_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro96_Entry8_DelayMin, PMacro96_Entry8_DelaySec, PMacro96_Entry8_TimMin, PMacro96_Entry8_TimSec, PMacro96_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro96_Entry9_DelayMin, PMacro96_Entry9_DelaySec, PMacro96_Entry9_TimMin, PMacro96_Entry9_TimSec, PMacro96_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro96_Entry10_DelayMin, PMacro96_Entry10_DelaySec, PMacro96_Entry10_TimMin, PMacro96_Entry10_TimSec, PMacro96_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro96_Entry11_DelayMin, PMacro96_Entry11_DelaySec, PMacro96_Entry11_TimMin, PMacro96_Entry11_TimSec, PMacro96_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro96_Entry12_DelayMin, PMacro96_Entry12_DelaySec, PMacro96_Entry12_TimMin, PMacro96_Entry12_TimSec, PMacro96_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro96_Entry13_DelayMin, PMacro96_Entry13_DelaySec, PMacro96_Entry13_TimMin, PMacro96_Entry13_TimSec, PMacro96_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro96_Entry14_DelayMin, PMacro96_Entry14_DelaySec, PMacro96_Entry14_TimMin, PMacro96_Entry14_TimSec, PMacro96_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro96_Entry15_DelayMin, PMacro96_Entry15_DelaySec, PMacro96_Entry15_TimMin, PMacro96_Entry15_TimSec, PMacro96_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR96_STRING};

const struct super_macro Macro97 = {PMacro97_NumEntries,
		         PMacro97_Entry1_DelayMin, PMacro97_Entry1_DelaySec, PMacro97_Entry1_TimMin, PMacro97_Entry1_TimSec, PMacro97_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro97_Entry2_DelayMin, PMacro97_Entry2_DelaySec, PMacro97_Entry2_TimMin, PMacro97_Entry2_TimSec, PMacro97_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro97_Entry3_DelayMin, PMacro97_Entry3_DelaySec, PMacro97_Entry3_TimMin, PMacro97_Entry3_TimSec, PMacro97_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro97_Entry4_DelayMin, PMacro97_Entry4_DelaySec, PMacro97_Entry4_TimMin, PMacro97_Entry4_TimSec, PMacro97_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro97_Entry5_DelayMin, PMacro97_Entry5_DelaySec, PMacro97_Entry5_TimMin, PMacro97_Entry5_TimSec, PMacro97_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro97_Entry6_DelayMin, PMacro97_Entry6_DelaySec, PMacro97_Entry6_TimMin, PMacro97_Entry6_TimSec, PMacro97_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro97_Entry7_DelayMin, PMacro97_Entry7_DelaySec, PMacro97_Entry7_TimMin, PMacro97_Entry7_TimSec, PMacro97_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro97_Entry8_DelayMin, PMacro97_Entry8_DelaySec, PMacro97_Entry8_TimMin, PMacro97_Entry8_TimSec, PMacro97_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro97_Entry9_DelayMin, PMacro97_Entry9_DelaySec, PMacro97_Entry9_TimMin, PMacro97_Entry9_TimSec, PMacro97_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro97_Entry10_DelayMin, PMacro97_Entry10_DelaySec, PMacro97_Entry10_TimMin, PMacro97_Entry10_TimSec, PMacro97_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro97_Entry11_DelayMin, PMacro97_Entry11_DelaySec, PMacro97_Entry11_TimMin, PMacro97_Entry11_TimSec, PMacro97_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro97_Entry12_DelayMin, PMacro97_Entry12_DelaySec, PMacro97_Entry12_TimMin, PMacro97_Entry12_TimSec, PMacro97_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro97_Entry13_DelayMin, PMacro97_Entry13_DelaySec, PMacro97_Entry13_TimMin, PMacro97_Entry13_TimSec, PMacro97_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro97_Entry14_DelayMin, PMacro97_Entry14_DelaySec, PMacro97_Entry14_TimMin, PMacro97_Entry14_TimSec, PMacro97_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro97_Entry15_DelayMin, PMacro97_Entry15_DelaySec, PMacro97_Entry15_TimMin, PMacro97_Entry15_TimSec, PMacro97_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR97_STRING};

const struct super_macro Macro98 = {PMacro98_NumEntries,
		         PMacro98_Entry1_DelayMin, PMacro98_Entry1_DelaySec, PMacro98_Entry1_TimMin, PMacro98_Entry1_TimSec, PMacro98_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro98_Entry2_DelayMin, PMacro98_Entry2_DelaySec, PMacro98_Entry2_TimMin, PMacro98_Entry2_TimSec, PMacro98_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro98_Entry3_DelayMin, PMacro98_Entry3_DelaySec, PMacro98_Entry3_TimMin, PMacro98_Entry3_TimSec, PMacro98_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro98_Entry4_DelayMin, PMacro98_Entry4_DelaySec, PMacro98_Entry4_TimMin, PMacro98_Entry4_TimSec, PMacro98_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro98_Entry5_DelayMin, PMacro98_Entry5_DelaySec, PMacro98_Entry5_TimMin, PMacro98_Entry5_TimSec, PMacro98_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro98_Entry6_DelayMin, PMacro98_Entry6_DelaySec, PMacro98_Entry6_TimMin, PMacro98_Entry6_TimSec, PMacro98_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro98_Entry7_DelayMin, PMacro98_Entry7_DelaySec, PMacro98_Entry7_TimMin, PMacro98_Entry7_TimSec, PMacro98_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro98_Entry8_DelayMin, PMacro98_Entry8_DelaySec, PMacro98_Entry8_TimMin, PMacro98_Entry8_TimSec, PMacro98_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro98_Entry9_DelayMin, PMacro98_Entry9_DelaySec, PMacro98_Entry9_TimMin, PMacro98_Entry9_TimSec, PMacro98_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro98_Entry10_DelayMin, PMacro98_Entry10_DelaySec, PMacro98_Entry10_TimMin, PMacro98_Entry10_TimSec, PMacro98_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro98_Entry11_DelayMin, PMacro98_Entry11_DelaySec, PMacro98_Entry11_TimMin, PMacro98_Entry11_TimSec, PMacro98_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro98_Entry12_DelayMin, PMacro98_Entry12_DelaySec, PMacro98_Entry12_TimMin, PMacro98_Entry12_TimSec, PMacro98_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro98_Entry13_DelayMin, PMacro98_Entry13_DelaySec, PMacro98_Entry13_TimMin, PMacro98_Entry13_TimSec, PMacro98_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro98_Entry14_DelayMin, PMacro98_Entry14_DelaySec, PMacro98_Entry14_TimMin, PMacro98_Entry14_TimSec, PMacro98_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro98_Entry15_DelayMin, PMacro98_Entry15_DelaySec, PMacro98_Entry15_TimMin, PMacro98_Entry15_TimSec, PMacro98_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR98_STRING};

const struct super_macro Macro99 = {PMacro99_NumEntries,
		         PMacro99_Entry1_DelayMin, PMacro99_Entry1_DelaySec, PMacro99_Entry1_TimMin, PMacro99_Entry1_TimSec, PMacro99_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro99_Entry2_DelayMin, PMacro99_Entry2_DelaySec, PMacro99_Entry2_TimMin, PMacro99_Entry2_TimSec, PMacro99_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro99_Entry3_DelayMin, PMacro99_Entry3_DelaySec, PMacro99_Entry3_TimMin, PMacro99_Entry3_TimSec, PMacro99_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro99_Entry4_DelayMin, PMacro99_Entry4_DelaySec, PMacro99_Entry4_TimMin, PMacro99_Entry4_TimSec, PMacro99_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro99_Entry5_DelayMin, PMacro99_Entry5_DelaySec, PMacro99_Entry5_TimMin, PMacro99_Entry5_TimSec, PMacro99_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro99_Entry6_DelayMin, PMacro99_Entry6_DelaySec, PMacro99_Entry6_TimMin, PMacro99_Entry6_TimSec, PMacro99_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro99_Entry7_DelayMin, PMacro99_Entry7_DelaySec, PMacro99_Entry7_TimMin, PMacro99_Entry7_TimSec, PMacro99_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro99_Entry8_DelayMin, PMacro99_Entry8_DelaySec, PMacro99_Entry8_TimMin, PMacro99_Entry8_TimSec, PMacro99_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro99_Entry9_DelayMin, PMacro99_Entry9_DelaySec, PMacro99_Entry9_TimMin, PMacro99_Entry9_TimSec, PMacro99_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro99_Entry10_DelayMin, PMacro99_Entry10_DelaySec, PMacro99_Entry10_TimMin, PMacro99_Entry10_TimSec, PMacro99_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro99_Entry11_DelayMin, PMacro99_Entry11_DelaySec, PMacro99_Entry11_TimMin, PMacro99_Entry11_TimSec, PMacro99_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro99_Entry12_DelayMin, PMacro99_Entry12_DelaySec, PMacro99_Entry12_TimMin, PMacro99_Entry12_TimSec, PMacro99_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro99_Entry13_DelayMin, PMacro99_Entry13_DelaySec, PMacro99_Entry13_TimMin, PMacro99_Entry13_TimSec, PMacro99_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro99_Entry14_DelayMin, PMacro99_Entry14_DelaySec, PMacro99_Entry14_TimMin, PMacro99_Entry14_TimSec, PMacro99_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro99_Entry15_DelayMin, PMacro99_Entry15_DelaySec, PMacro99_Entry15_TimMin, PMacro99_Entry15_TimSec, PMacro99_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR99_STRING};

const struct super_macro Macro100 = {PMacro100_NumEntries,
		         PMacro100_Entry1_DelayMin, PMacro100_Entry1_DelaySec, PMacro100_Entry1_TimMin, PMacro100_Entry1_TimSec, PMacro100_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro100_Entry2_DelayMin, PMacro100_Entry2_DelaySec, PMacro100_Entry2_TimMin, PMacro100_Entry2_TimSec, PMacro100_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro100_Entry3_DelayMin, PMacro100_Entry3_DelaySec, PMacro100_Entry3_TimMin, PMacro100_Entry3_TimSec, PMacro100_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro100_Entry4_DelayMin, PMacro100_Entry4_DelaySec, PMacro100_Entry4_TimMin, PMacro100_Entry4_TimSec, PMacro100_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro100_Entry5_DelayMin, PMacro100_Entry5_DelaySec, PMacro100_Entry5_TimMin, PMacro100_Entry5_TimSec, PMacro100_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro100_Entry6_DelayMin, PMacro100_Entry6_DelaySec, PMacro100_Entry6_TimMin, PMacro100_Entry6_TimSec, PMacro100_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro100_Entry7_DelayMin, PMacro100_Entry7_DelaySec, PMacro100_Entry7_TimMin, PMacro100_Entry7_TimSec, PMacro100_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro100_Entry8_DelayMin, PMacro100_Entry8_DelaySec, PMacro100_Entry8_TimMin, PMacro100_Entry8_TimSec, PMacro100_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro100_Entry9_DelayMin, PMacro100_Entry9_DelaySec, PMacro100_Entry9_TimMin, PMacro100_Entry9_TimSec, PMacro100_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro100_Entry10_DelayMin, PMacro100_Entry10_DelaySec, PMacro100_Entry10_TimMin, PMacro100_Entry10_TimSec, PMacro100_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro100_Entry11_DelayMin, PMacro100_Entry11_DelaySec, PMacro100_Entry11_TimMin, PMacro100_Entry11_TimSec, PMacro100_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro100_Entry12_DelayMin, PMacro100_Entry12_DelaySec, PMacro100_Entry12_TimMin, PMacro100_Entry12_TimSec, PMacro100_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro100_Entry13_DelayMin, PMacro100_Entry13_DelaySec, PMacro100_Entry13_TimMin, PMacro100_Entry13_TimSec, PMacro100_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro100_Entry14_DelayMin, PMacro100_Entry14_DelaySec, PMacro100_Entry14_TimMin, PMacro100_Entry14_TimSec, PMacro100_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro100_Entry15_DelayMin, PMacro100_Entry15_DelaySec, PMacro100_Entry15_TimMin, PMacro100_Entry15_TimSec, PMacro100_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR100_STRING};

const struct super_macro Macro101 = {PMacro101_NumEntries,
		         PMacro101_Entry1_DelayMin, PMacro101_Entry1_DelaySec, PMacro101_Entry1_TimMin, PMacro101_Entry1_TimSec, PMacro101_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro101_Entry2_DelayMin, PMacro101_Entry2_DelaySec, PMacro101_Entry2_TimMin, PMacro101_Entry2_TimSec, PMacro101_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro101_Entry3_DelayMin, PMacro101_Entry3_DelaySec, PMacro101_Entry3_TimMin, PMacro101_Entry3_TimSec, PMacro101_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro101_Entry4_DelayMin, PMacro101_Entry4_DelaySec, PMacro101_Entry4_TimMin, PMacro101_Entry4_TimSec, PMacro101_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro101_Entry5_DelayMin, PMacro101_Entry5_DelaySec, PMacro101_Entry5_TimMin, PMacro101_Entry5_TimSec, PMacro101_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro101_Entry6_DelayMin, PMacro101_Entry6_DelaySec, PMacro101_Entry6_TimMin, PMacro101_Entry6_TimSec, PMacro101_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro101_Entry7_DelayMin, PMacro101_Entry7_DelaySec, PMacro101_Entry7_TimMin, PMacro101_Entry7_TimSec, PMacro101_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro101_Entry8_DelayMin, PMacro101_Entry8_DelaySec, PMacro101_Entry8_TimMin, PMacro101_Entry8_TimSec, PMacro101_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro101_Entry9_DelayMin, PMacro101_Entry9_DelaySec, PMacro101_Entry9_TimMin, PMacro101_Entry9_TimSec, PMacro101_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro101_Entry10_DelayMin, PMacro101_Entry10_DelaySec, PMacro101_Entry10_TimMin, PMacro101_Entry10_TimSec, PMacro101_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro101_Entry11_DelayMin, PMacro101_Entry11_DelaySec, PMacro101_Entry11_TimMin, PMacro101_Entry11_TimSec, PMacro101_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro101_Entry12_DelayMin, PMacro101_Entry12_DelaySec, PMacro101_Entry12_TimMin, PMacro101_Entry12_TimSec, PMacro101_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro101_Entry13_DelayMin, PMacro101_Entry13_DelaySec, PMacro101_Entry13_TimMin, PMacro101_Entry13_TimSec, PMacro101_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro101_Entry14_DelayMin, PMacro101_Entry14_DelaySec, PMacro101_Entry14_TimMin, PMacro101_Entry14_TimSec, PMacro101_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro101_Entry15_DelayMin, PMacro101_Entry15_DelaySec, PMacro101_Entry15_TimMin, PMacro101_Entry15_TimSec, PMacro101_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR101_STRING};

const struct super_macro Macro102 = {PMacro102_NumEntries,
		         PMacro102_Entry1_DelayMin, PMacro102_Entry1_DelaySec, PMacro102_Entry1_TimMin, PMacro102_Entry1_TimSec, PMacro102_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro102_Entry2_DelayMin, PMacro102_Entry2_DelaySec, PMacro102_Entry2_TimMin, PMacro102_Entry2_TimSec, PMacro102_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro102_Entry3_DelayMin, PMacro102_Entry3_DelaySec, PMacro102_Entry3_TimMin, PMacro102_Entry3_TimSec, PMacro102_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro102_Entry4_DelayMin, PMacro102_Entry4_DelaySec, PMacro102_Entry4_TimMin, PMacro102_Entry4_TimSec, PMacro102_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro102_Entry5_DelayMin, PMacro102_Entry5_DelaySec, PMacro102_Entry5_TimMin, PMacro102_Entry5_TimSec, PMacro102_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro102_Entry6_DelayMin, PMacro102_Entry6_DelaySec, PMacro102_Entry6_TimMin, PMacro102_Entry6_TimSec, PMacro102_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro102_Entry7_DelayMin, PMacro102_Entry7_DelaySec, PMacro102_Entry7_TimMin, PMacro102_Entry7_TimSec, PMacro102_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro102_Entry8_DelayMin, PMacro102_Entry8_DelaySec, PMacro102_Entry8_TimMin, PMacro102_Entry8_TimSec, PMacro102_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro102_Entry9_DelayMin, PMacro102_Entry9_DelaySec, PMacro102_Entry9_TimMin, PMacro102_Entry9_TimSec, PMacro102_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro102_Entry10_DelayMin, PMacro102_Entry10_DelaySec, PMacro102_Entry10_TimMin, PMacro102_Entry10_TimSec, PMacro102_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro102_Entry11_DelayMin, PMacro102_Entry11_DelaySec, PMacro102_Entry11_TimMin, PMacro102_Entry11_TimSec, PMacro102_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro102_Entry12_DelayMin, PMacro102_Entry12_DelaySec, PMacro102_Entry12_TimMin, PMacro102_Entry12_TimSec, PMacro102_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro102_Entry13_DelayMin, PMacro102_Entry13_DelaySec, PMacro102_Entry13_TimMin, PMacro102_Entry13_TimSec, PMacro102_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro102_Entry14_DelayMin, PMacro102_Entry14_DelaySec, PMacro102_Entry14_TimMin, PMacro102_Entry14_TimSec, PMacro102_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro102_Entry15_DelayMin, PMacro102_Entry15_DelaySec, PMacro102_Entry15_TimMin, PMacro102_Entry15_TimSec, PMacro102_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR102_STRING};

const struct super_macro Macro103 = {PMacro103_NumEntries,
		         PMacro103_Entry1_DelayMin, PMacro103_Entry1_DelaySec, PMacro103_Entry1_TimMin, PMacro103_Entry1_TimSec, PMacro103_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro103_Entry2_DelayMin, PMacro103_Entry2_DelaySec, PMacro103_Entry2_TimMin, PMacro103_Entry2_TimSec, PMacro103_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro103_Entry3_DelayMin, PMacro103_Entry3_DelaySec, PMacro103_Entry3_TimMin, PMacro103_Entry3_TimSec, PMacro103_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro103_Entry4_DelayMin, PMacro103_Entry4_DelaySec, PMacro103_Entry4_TimMin, PMacro103_Entry4_TimSec, PMacro103_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro103_Entry5_DelayMin, PMacro103_Entry5_DelaySec, PMacro103_Entry5_TimMin, PMacro103_Entry5_TimSec, PMacro103_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro103_Entry6_DelayMin, PMacro103_Entry6_DelaySec, PMacro103_Entry6_TimMin, PMacro103_Entry6_TimSec, PMacro103_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro103_Entry7_DelayMin, PMacro103_Entry7_DelaySec, PMacro103_Entry7_TimMin, PMacro103_Entry7_TimSec, PMacro103_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro103_Entry8_DelayMin, PMacro103_Entry8_DelaySec, PMacro103_Entry8_TimMin, PMacro103_Entry8_TimSec, PMacro103_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro103_Entry9_DelayMin, PMacro103_Entry9_DelaySec, PMacro103_Entry9_TimMin, PMacro103_Entry9_TimSec, PMacro103_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro103_Entry10_DelayMin, PMacro103_Entry10_DelaySec, PMacro103_Entry10_TimMin, PMacro103_Entry10_TimSec, PMacro103_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro103_Entry11_DelayMin, PMacro103_Entry11_DelaySec, PMacro103_Entry11_TimMin, PMacro103_Entry11_TimSec, PMacro103_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro103_Entry12_DelayMin, PMacro103_Entry12_DelaySec, PMacro103_Entry12_TimMin, PMacro103_Entry12_TimSec, PMacro103_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro103_Entry13_DelayMin, PMacro103_Entry13_DelaySec, PMacro103_Entry13_TimMin, PMacro103_Entry13_TimSec, PMacro103_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro103_Entry14_DelayMin, PMacro103_Entry14_DelaySec, PMacro103_Entry14_TimMin, PMacro103_Entry14_TimSec, PMacro103_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro103_Entry15_DelayMin, PMacro103_Entry15_DelaySec, PMacro103_Entry15_TimMin, PMacro103_Entry15_TimSec, PMacro103_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR103_STRING};

const struct super_macro Macro104 = {PMacro104_NumEntries,
		         PMacro104_Entry1_DelayMin, PMacro104_Entry1_DelaySec, PMacro104_Entry1_TimMin, PMacro104_Entry1_TimSec, PMacro104_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro104_Entry2_DelayMin, PMacro104_Entry2_DelaySec, PMacro104_Entry2_TimMin, PMacro104_Entry2_TimSec, PMacro104_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro104_Entry3_DelayMin, PMacro104_Entry3_DelaySec, PMacro104_Entry3_TimMin, PMacro104_Entry3_TimSec, PMacro104_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro104_Entry4_DelayMin, PMacro104_Entry4_DelaySec, PMacro104_Entry4_TimMin, PMacro104_Entry4_TimSec, PMacro104_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro104_Entry5_DelayMin, PMacro104_Entry5_DelaySec, PMacro104_Entry5_TimMin, PMacro104_Entry5_TimSec, PMacro104_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro104_Entry6_DelayMin, PMacro104_Entry6_DelaySec, PMacro104_Entry6_TimMin, PMacro104_Entry6_TimSec, PMacro104_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro104_Entry7_DelayMin, PMacro104_Entry7_DelaySec, PMacro104_Entry7_TimMin, PMacro104_Entry7_TimSec, PMacro104_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro104_Entry8_DelayMin, PMacro104_Entry8_DelaySec, PMacro104_Entry8_TimMin, PMacro104_Entry8_TimSec, PMacro104_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro104_Entry9_DelayMin, PMacro104_Entry9_DelaySec, PMacro104_Entry9_TimMin, PMacro104_Entry9_TimSec, PMacro104_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro104_Entry10_DelayMin, PMacro104_Entry10_DelaySec, PMacro104_Entry10_TimMin, PMacro104_Entry10_TimSec, PMacro104_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro104_Entry11_DelayMin, PMacro104_Entry11_DelaySec, PMacro104_Entry11_TimMin, PMacro104_Entry11_TimSec, PMacro104_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro104_Entry12_DelayMin, PMacro104_Entry12_DelaySec, PMacro104_Entry12_TimMin, PMacro104_Entry12_TimSec, PMacro104_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro104_Entry13_DelayMin, PMacro104_Entry13_DelaySec, PMacro104_Entry13_TimMin, PMacro104_Entry13_TimSec, PMacro104_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro104_Entry14_DelayMin, PMacro104_Entry14_DelaySec, PMacro104_Entry14_TimMin, PMacro104_Entry14_TimSec, PMacro104_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro104_Entry15_DelayMin, PMacro104_Entry15_DelaySec, PMacro104_Entry15_TimMin, PMacro104_Entry15_TimSec, PMacro104_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR104_STRING};

const struct super_macro Macro105 = {PMacro105_NumEntries,
		         PMacro105_Entry1_DelayMin, PMacro105_Entry1_DelaySec, PMacro105_Entry1_TimMin, PMacro105_Entry1_TimSec, PMacro105_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro105_Entry2_DelayMin, PMacro105_Entry2_DelaySec, PMacro105_Entry2_TimMin, PMacro105_Entry2_TimSec, PMacro105_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro105_Entry3_DelayMin, PMacro105_Entry3_DelaySec, PMacro105_Entry3_TimMin, PMacro105_Entry3_TimSec, PMacro105_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro105_Entry4_DelayMin, PMacro105_Entry4_DelaySec, PMacro105_Entry4_TimMin, PMacro105_Entry4_TimSec, PMacro105_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro105_Entry5_DelayMin, PMacro105_Entry5_DelaySec, PMacro105_Entry5_TimMin, PMacro105_Entry5_TimSec, PMacro105_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro105_Entry6_DelayMin, PMacro105_Entry6_DelaySec, PMacro105_Entry6_TimMin, PMacro105_Entry6_TimSec, PMacro105_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro105_Entry7_DelayMin, PMacro105_Entry7_DelaySec, PMacro105_Entry7_TimMin, PMacro105_Entry7_TimSec, PMacro105_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro105_Entry8_DelayMin, PMacro105_Entry8_DelaySec, PMacro105_Entry8_TimMin, PMacro105_Entry8_TimSec, PMacro105_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro105_Entry9_DelayMin, PMacro105_Entry9_DelaySec, PMacro105_Entry9_TimMin, PMacro105_Entry9_TimSec, PMacro105_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro105_Entry10_DelayMin, PMacro105_Entry10_DelaySec, PMacro105_Entry10_TimMin, PMacro105_Entry10_TimSec, PMacro105_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro105_Entry11_DelayMin, PMacro105_Entry11_DelaySec, PMacro105_Entry11_TimMin, PMacro105_Entry11_TimSec, PMacro105_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro105_Entry12_DelayMin, PMacro105_Entry12_DelaySec, PMacro105_Entry12_TimMin, PMacro105_Entry12_TimSec, PMacro105_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro105_Entry13_DelayMin, PMacro105_Entry13_DelaySec, PMacro105_Entry13_TimMin, PMacro105_Entry13_TimSec, PMacro105_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro105_Entry14_DelayMin, PMacro105_Entry14_DelaySec, PMacro105_Entry14_TimMin, PMacro105_Entry14_TimSec, PMacro105_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro105_Entry15_DelayMin, PMacro105_Entry15_DelaySec, PMacro105_Entry15_TimMin, PMacro105_Entry15_TimSec, PMacro105_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR105_STRING};

const struct super_macro Macro106 = {PMacro106_NumEntries,
		         PMacro106_Entry1_DelayMin, PMacro106_Entry1_DelaySec, PMacro106_Entry1_TimMin, PMacro106_Entry1_TimSec, PMacro106_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro106_Entry2_DelayMin, PMacro106_Entry2_DelaySec, PMacro106_Entry2_TimMin, PMacro106_Entry2_TimSec, PMacro106_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro106_Entry3_DelayMin, PMacro106_Entry3_DelaySec, PMacro106_Entry3_TimMin, PMacro106_Entry3_TimSec, PMacro106_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro106_Entry4_DelayMin, PMacro106_Entry4_DelaySec, PMacro106_Entry4_TimMin, PMacro106_Entry4_TimSec, PMacro106_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro106_Entry5_DelayMin, PMacro106_Entry5_DelaySec, PMacro106_Entry5_TimMin, PMacro106_Entry5_TimSec, PMacro106_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro106_Entry6_DelayMin, PMacro106_Entry6_DelaySec, PMacro106_Entry6_TimMin, PMacro106_Entry6_TimSec, PMacro106_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro106_Entry7_DelayMin, PMacro106_Entry7_DelaySec, PMacro106_Entry7_TimMin, PMacro106_Entry7_TimSec, PMacro106_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro106_Entry8_DelayMin, PMacro106_Entry8_DelaySec, PMacro106_Entry8_TimMin, PMacro106_Entry8_TimSec, PMacro106_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro106_Entry9_DelayMin, PMacro106_Entry9_DelaySec, PMacro106_Entry9_TimMin, PMacro106_Entry9_TimSec, PMacro106_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro106_Entry10_DelayMin, PMacro106_Entry10_DelaySec, PMacro106_Entry10_TimMin, PMacro106_Entry10_TimSec, PMacro106_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro106_Entry11_DelayMin, PMacro106_Entry11_DelaySec, PMacro106_Entry11_TimMin, PMacro106_Entry11_TimSec, PMacro106_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro106_Entry12_DelayMin, PMacro106_Entry12_DelaySec, PMacro106_Entry12_TimMin, PMacro106_Entry12_TimSec, PMacro106_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro106_Entry13_DelayMin, PMacro106_Entry13_DelaySec, PMacro106_Entry13_TimMin, PMacro106_Entry13_TimSec, PMacro106_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro106_Entry14_DelayMin, PMacro106_Entry14_DelaySec, PMacro106_Entry14_TimMin, PMacro106_Entry14_TimSec, PMacro106_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro106_Entry15_DelayMin, PMacro106_Entry15_DelaySec, PMacro106_Entry15_TimMin, PMacro106_Entry15_TimSec, PMacro106_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR106_STRING};

const struct super_macro Macro107 = {PMacro107_NumEntries,
		         PMacro107_Entry1_DelayMin, PMacro107_Entry1_DelaySec, PMacro107_Entry1_TimMin, PMacro107_Entry1_TimSec, PMacro107_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro107_Entry2_DelayMin, PMacro107_Entry2_DelaySec, PMacro107_Entry2_TimMin, PMacro107_Entry2_TimSec, PMacro107_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro107_Entry3_DelayMin, PMacro107_Entry3_DelaySec, PMacro107_Entry3_TimMin, PMacro107_Entry3_TimSec, PMacro107_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro107_Entry4_DelayMin, PMacro107_Entry4_DelaySec, PMacro107_Entry4_TimMin, PMacro107_Entry4_TimSec, PMacro107_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro107_Entry5_DelayMin, PMacro107_Entry5_DelaySec, PMacro107_Entry5_TimMin, PMacro107_Entry5_TimSec, PMacro107_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro107_Entry6_DelayMin, PMacro107_Entry6_DelaySec, PMacro107_Entry6_TimMin, PMacro107_Entry6_TimSec, PMacro107_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro107_Entry7_DelayMin, PMacro107_Entry7_DelaySec, PMacro107_Entry7_TimMin, PMacro107_Entry7_TimSec, PMacro107_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro107_Entry8_DelayMin, PMacro107_Entry8_DelaySec, PMacro107_Entry8_TimMin, PMacro107_Entry8_TimSec, PMacro107_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro107_Entry9_DelayMin, PMacro107_Entry9_DelaySec, PMacro107_Entry9_TimMin, PMacro107_Entry9_TimSec, PMacro107_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro107_Entry10_DelayMin, PMacro107_Entry10_DelaySec, PMacro107_Entry10_TimMin, PMacro107_Entry10_TimSec, PMacro107_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro107_Entry11_DelayMin, PMacro107_Entry11_DelaySec, PMacro107_Entry11_TimMin, PMacro107_Entry11_TimSec, PMacro107_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro107_Entry12_DelayMin, PMacro107_Entry12_DelaySec, PMacro107_Entry12_TimMin, PMacro107_Entry12_TimSec, PMacro107_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro107_Entry13_DelayMin, PMacro107_Entry13_DelaySec, PMacro107_Entry13_TimMin, PMacro107_Entry13_TimSec, PMacro107_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro107_Entry14_DelayMin, PMacro107_Entry14_DelaySec, PMacro107_Entry14_TimMin, PMacro107_Entry14_TimSec, PMacro107_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro107_Entry15_DelayMin, PMacro107_Entry15_DelaySec, PMacro107_Entry15_TimMin, PMacro107_Entry15_TimSec, PMacro107_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR107_STRING};

const struct super_macro Macro108 = {PMacro108_NumEntries,
		         PMacro108_Entry1_DelayMin, PMacro108_Entry1_DelaySec, PMacro108_Entry1_TimMin, PMacro108_Entry1_TimSec, PMacro108_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro108_Entry2_DelayMin, PMacro108_Entry2_DelaySec, PMacro108_Entry2_TimMin, PMacro108_Entry2_TimSec, PMacro108_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro108_Entry3_DelayMin, PMacro108_Entry3_DelaySec, PMacro108_Entry3_TimMin, PMacro108_Entry3_TimSec, PMacro108_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro108_Entry4_DelayMin, PMacro108_Entry4_DelaySec, PMacro108_Entry4_TimMin, PMacro108_Entry4_TimSec, PMacro108_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro108_Entry5_DelayMin, PMacro108_Entry5_DelaySec, PMacro108_Entry5_TimMin, PMacro108_Entry5_TimSec, PMacro108_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro108_Entry6_DelayMin, PMacro108_Entry6_DelaySec, PMacro108_Entry6_TimMin, PMacro108_Entry6_TimSec, PMacro108_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro108_Entry7_DelayMin, PMacro108_Entry7_DelaySec, PMacro108_Entry7_TimMin, PMacro108_Entry7_TimSec, PMacro108_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro108_Entry8_DelayMin, PMacro108_Entry8_DelaySec, PMacro108_Entry8_TimMin, PMacro108_Entry8_TimSec, PMacro108_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro108_Entry9_DelayMin, PMacro108_Entry9_DelaySec, PMacro108_Entry9_TimMin, PMacro108_Entry9_TimSec, PMacro108_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro108_Entry10_DelayMin, PMacro108_Entry10_DelaySec, PMacro108_Entry10_TimMin, PMacro108_Entry10_TimSec, PMacro108_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro108_Entry11_DelayMin, PMacro108_Entry11_DelaySec, PMacro108_Entry11_TimMin, PMacro108_Entry11_TimSec, PMacro108_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro108_Entry12_DelayMin, PMacro108_Entry12_DelaySec, PMacro108_Entry12_TimMin, PMacro108_Entry12_TimSec, PMacro108_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro108_Entry13_DelayMin, PMacro108_Entry13_DelaySec, PMacro108_Entry13_TimMin, PMacro108_Entry13_TimSec, PMacro108_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro108_Entry14_DelayMin, PMacro108_Entry14_DelaySec, PMacro108_Entry14_TimMin, PMacro108_Entry14_TimSec, PMacro108_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro108_Entry15_DelayMin, PMacro108_Entry15_DelaySec, PMacro108_Entry15_TimMin, PMacro108_Entry15_TimSec, PMacro108_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR108_STRING};

const struct super_macro Macro109 = {PMacro109_NumEntries,
		         PMacro109_Entry1_DelayMin, PMacro109_Entry1_DelaySec, PMacro109_Entry1_TimMin, PMacro109_Entry1_TimSec, PMacro109_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro109_Entry2_DelayMin, PMacro109_Entry2_DelaySec, PMacro109_Entry2_TimMin, PMacro109_Entry2_TimSec, PMacro109_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro109_Entry3_DelayMin, PMacro109_Entry3_DelaySec, PMacro109_Entry3_TimMin, PMacro109_Entry3_TimSec, PMacro109_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro109_Entry4_DelayMin, PMacro109_Entry4_DelaySec, PMacro109_Entry4_TimMin, PMacro109_Entry4_TimSec, PMacro109_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro109_Entry5_DelayMin, PMacro109_Entry5_DelaySec, PMacro109_Entry5_TimMin, PMacro109_Entry5_TimSec, PMacro109_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro109_Entry6_DelayMin, PMacro109_Entry6_DelaySec, PMacro109_Entry6_TimMin, PMacro109_Entry6_TimSec, PMacro109_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro109_Entry7_DelayMin, PMacro109_Entry7_DelaySec, PMacro109_Entry7_TimMin, PMacro109_Entry7_TimSec, PMacro109_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro109_Entry8_DelayMin, PMacro109_Entry8_DelaySec, PMacro109_Entry8_TimMin, PMacro109_Entry8_TimSec, PMacro109_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro109_Entry9_DelayMin, PMacro109_Entry9_DelaySec, PMacro109_Entry9_TimMin, PMacro109_Entry9_TimSec, PMacro109_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro109_Entry10_DelayMin, PMacro109_Entry10_DelaySec, PMacro109_Entry10_TimMin, PMacro109_Entry10_TimSec, PMacro109_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro109_Entry11_DelayMin, PMacro109_Entry11_DelaySec, PMacro109_Entry11_TimMin, PMacro109_Entry11_TimSec, PMacro109_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro109_Entry12_DelayMin, PMacro109_Entry12_DelaySec, PMacro109_Entry12_TimMin, PMacro109_Entry12_TimSec, PMacro109_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro109_Entry13_DelayMin, PMacro109_Entry13_DelaySec, PMacro109_Entry13_TimMin, PMacro109_Entry13_TimSec, PMacro109_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro109_Entry14_DelayMin, PMacro109_Entry14_DelaySec, PMacro109_Entry14_TimMin, PMacro109_Entry14_TimSec, PMacro109_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro109_Entry15_DelayMin, PMacro109_Entry15_DelaySec, PMacro109_Entry15_TimMin, PMacro109_Entry15_TimSec, PMacro109_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR109_STRING};

const struct super_macro Macro110 = {PMacro110_NumEntries,
		         PMacro110_Entry1_DelayMin, PMacro110_Entry1_DelaySec, PMacro110_Entry1_TimMin, PMacro110_Entry1_TimSec, PMacro110_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro110_Entry2_DelayMin, PMacro110_Entry2_DelaySec, PMacro110_Entry2_TimMin, PMacro110_Entry2_TimSec, PMacro110_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro110_Entry3_DelayMin, PMacro110_Entry3_DelaySec, PMacro110_Entry3_TimMin, PMacro110_Entry3_TimSec, PMacro110_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro110_Entry4_DelayMin, PMacro110_Entry4_DelaySec, PMacro110_Entry4_TimMin, PMacro110_Entry4_TimSec, PMacro110_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro110_Entry5_DelayMin, PMacro110_Entry5_DelaySec, PMacro110_Entry5_TimMin, PMacro110_Entry5_TimSec, PMacro110_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro110_Entry6_DelayMin, PMacro110_Entry6_DelaySec, PMacro110_Entry6_TimMin, PMacro110_Entry6_TimSec, PMacro110_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro110_Entry7_DelayMin, PMacro110_Entry7_DelaySec, PMacro110_Entry7_TimMin, PMacro110_Entry7_TimSec, PMacro110_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro110_Entry8_DelayMin, PMacro110_Entry8_DelaySec, PMacro110_Entry8_TimMin, PMacro110_Entry8_TimSec, PMacro110_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro110_Entry9_DelayMin, PMacro110_Entry9_DelaySec, PMacro110_Entry9_TimMin, PMacro110_Entry9_TimSec, PMacro110_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro110_Entry10_DelayMin, PMacro110_Entry10_DelaySec, PMacro110_Entry10_TimMin, PMacro110_Entry10_TimSec, PMacro110_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro110_Entry11_DelayMin, PMacro110_Entry11_DelaySec, PMacro110_Entry11_TimMin, PMacro110_Entry11_TimSec, PMacro110_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro110_Entry12_DelayMin, PMacro110_Entry12_DelaySec, PMacro110_Entry12_TimMin, PMacro110_Entry12_TimSec, PMacro110_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro110_Entry13_DelayMin, PMacro110_Entry13_DelaySec, PMacro110_Entry13_TimMin, PMacro110_Entry13_TimSec, PMacro110_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro110_Entry14_DelayMin, PMacro110_Entry14_DelaySec, PMacro110_Entry14_TimMin, PMacro110_Entry14_TimSec, PMacro110_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro110_Entry15_DelayMin, PMacro110_Entry15_DelaySec, PMacro110_Entry15_TimMin, PMacro110_Entry15_TimSec, PMacro110_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR110_STRING};

const struct super_macro Macro111 = {PMacro111_NumEntries,
		         PMacro111_Entry1_DelayMin, PMacro111_Entry1_DelaySec, PMacro111_Entry1_TimMin, PMacro111_Entry1_TimSec, PMacro111_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro111_Entry2_DelayMin, PMacro111_Entry2_DelaySec, PMacro111_Entry2_TimMin, PMacro111_Entry2_TimSec, PMacro111_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro111_Entry3_DelayMin, PMacro111_Entry3_DelaySec, PMacro111_Entry3_TimMin, PMacro111_Entry3_TimSec, PMacro111_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro111_Entry4_DelayMin, PMacro111_Entry4_DelaySec, PMacro111_Entry4_TimMin, PMacro111_Entry4_TimSec, PMacro111_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro111_Entry5_DelayMin, PMacro111_Entry5_DelaySec, PMacro111_Entry5_TimMin, PMacro111_Entry5_TimSec, PMacro111_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro111_Entry6_DelayMin, PMacro111_Entry6_DelaySec, PMacro111_Entry6_TimMin, PMacro111_Entry6_TimSec, PMacro111_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro111_Entry7_DelayMin, PMacro111_Entry7_DelaySec, PMacro111_Entry7_TimMin, PMacro111_Entry7_TimSec, PMacro111_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro111_Entry8_DelayMin, PMacro111_Entry8_DelaySec, PMacro111_Entry8_TimMin, PMacro111_Entry8_TimSec, PMacro111_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro111_Entry9_DelayMin, PMacro111_Entry9_DelaySec, PMacro111_Entry9_TimMin, PMacro111_Entry9_TimSec, PMacro111_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro111_Entry10_DelayMin, PMacro111_Entry10_DelaySec, PMacro111_Entry10_TimMin, PMacro111_Entry10_TimSec, PMacro111_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro111_Entry11_DelayMin, PMacro111_Entry11_DelaySec, PMacro111_Entry11_TimMin, PMacro111_Entry11_TimSec, PMacro111_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro111_Entry12_DelayMin, PMacro111_Entry12_DelaySec, PMacro111_Entry12_TimMin, PMacro111_Entry12_TimSec, PMacro111_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro111_Entry13_DelayMin, PMacro111_Entry13_DelaySec, PMacro111_Entry13_TimMin, PMacro111_Entry13_TimSec, PMacro111_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro111_Entry14_DelayMin, PMacro111_Entry14_DelaySec, PMacro111_Entry14_TimMin, PMacro111_Entry14_TimSec, PMacro111_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro111_Entry15_DelayMin, PMacro111_Entry15_DelaySec, PMacro111_Entry15_TimMin, PMacro111_Entry15_TimSec, PMacro111_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR111_STRING};

const struct super_macro Macro112 = {PMacro112_NumEntries,
		         PMacro112_Entry1_DelayMin, PMacro112_Entry1_DelaySec, PMacro112_Entry1_TimMin, PMacro112_Entry1_TimSec, PMacro112_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro112_Entry2_DelayMin, PMacro112_Entry2_DelaySec, PMacro112_Entry2_TimMin, PMacro112_Entry2_TimSec, PMacro112_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro112_Entry3_DelayMin, PMacro112_Entry3_DelaySec, PMacro112_Entry3_TimMin, PMacro112_Entry3_TimSec, PMacro112_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro112_Entry4_DelayMin, PMacro112_Entry4_DelaySec, PMacro112_Entry4_TimMin, PMacro112_Entry4_TimSec, PMacro112_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro112_Entry5_DelayMin, PMacro112_Entry5_DelaySec, PMacro112_Entry5_TimMin, PMacro112_Entry5_TimSec, PMacro112_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro112_Entry6_DelayMin, PMacro112_Entry6_DelaySec, PMacro112_Entry6_TimMin, PMacro112_Entry6_TimSec, PMacro112_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro112_Entry7_DelayMin, PMacro112_Entry7_DelaySec, PMacro112_Entry7_TimMin, PMacro112_Entry7_TimSec, PMacro112_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro112_Entry8_DelayMin, PMacro112_Entry8_DelaySec, PMacro112_Entry8_TimMin, PMacro112_Entry8_TimSec, PMacro112_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro112_Entry9_DelayMin, PMacro112_Entry9_DelaySec, PMacro112_Entry9_TimMin, PMacro112_Entry9_TimSec, PMacro112_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro112_Entry10_DelayMin, PMacro112_Entry10_DelaySec, PMacro112_Entry10_TimMin, PMacro112_Entry10_TimSec, PMacro112_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro112_Entry11_DelayMin, PMacro112_Entry11_DelaySec, PMacro112_Entry11_TimMin, PMacro112_Entry11_TimSec, PMacro112_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro112_Entry12_DelayMin, PMacro112_Entry12_DelaySec, PMacro112_Entry12_TimMin, PMacro112_Entry12_TimSec, PMacro112_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro112_Entry13_DelayMin, PMacro112_Entry13_DelaySec, PMacro112_Entry13_TimMin, PMacro112_Entry13_TimSec, PMacro112_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro112_Entry14_DelayMin, PMacro112_Entry14_DelaySec, PMacro112_Entry14_TimMin, PMacro112_Entry14_TimSec, PMacro112_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro112_Entry15_DelayMin, PMacro112_Entry15_DelaySec, PMacro112_Entry15_TimMin, PMacro112_Entry15_TimSec, PMacro112_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR112_STRING};

const struct super_macro Macro113 = {PMacro113_NumEntries,
		         PMacro113_Entry1_DelayMin, PMacro113_Entry1_DelaySec, PMacro113_Entry1_TimMin, PMacro113_Entry1_TimSec, PMacro113_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro113_Entry2_DelayMin, PMacro113_Entry2_DelaySec, PMacro113_Entry2_TimMin, PMacro113_Entry2_TimSec, PMacro113_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro113_Entry3_DelayMin, PMacro113_Entry3_DelaySec, PMacro113_Entry3_TimMin, PMacro113_Entry3_TimSec, PMacro113_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro113_Entry4_DelayMin, PMacro113_Entry4_DelaySec, PMacro113_Entry4_TimMin, PMacro113_Entry4_TimSec, PMacro113_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro113_Entry5_DelayMin, PMacro113_Entry5_DelaySec, PMacro113_Entry5_TimMin, PMacro113_Entry5_TimSec, PMacro113_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro113_Entry6_DelayMin, PMacro113_Entry6_DelaySec, PMacro113_Entry6_TimMin, PMacro113_Entry6_TimSec, PMacro113_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro113_Entry7_DelayMin, PMacro113_Entry7_DelaySec, PMacro113_Entry7_TimMin, PMacro113_Entry7_TimSec, PMacro113_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro113_Entry8_DelayMin, PMacro113_Entry8_DelaySec, PMacro113_Entry8_TimMin, PMacro113_Entry8_TimSec, PMacro113_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro113_Entry9_DelayMin, PMacro113_Entry9_DelaySec, PMacro113_Entry9_TimMin, PMacro113_Entry9_TimSec, PMacro113_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro113_Entry10_DelayMin, PMacro113_Entry10_DelaySec, PMacro113_Entry10_TimMin, PMacro113_Entry10_TimSec, PMacro113_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro113_Entry11_DelayMin, PMacro113_Entry11_DelaySec, PMacro113_Entry11_TimMin, PMacro113_Entry11_TimSec, PMacro113_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro113_Entry12_DelayMin, PMacro113_Entry12_DelaySec, PMacro113_Entry12_TimMin, PMacro113_Entry12_TimSec, PMacro113_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro113_Entry13_DelayMin, PMacro113_Entry13_DelaySec, PMacro113_Entry13_TimMin, PMacro113_Entry13_TimSec, PMacro113_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro113_Entry14_DelayMin, PMacro113_Entry14_DelaySec, PMacro113_Entry14_TimMin, PMacro113_Entry14_TimSec, PMacro113_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro113_Entry15_DelayMin, PMacro113_Entry15_DelaySec, PMacro113_Entry15_TimMin, PMacro113_Entry15_TimSec, PMacro113_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR113_STRING};

const struct super_macro Macro114 = {PMacro114_NumEntries,
		         PMacro114_Entry1_DelayMin, PMacro114_Entry1_DelaySec, PMacro114_Entry1_TimMin, PMacro114_Entry1_TimSec, PMacro114_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro114_Entry2_DelayMin, PMacro114_Entry2_DelaySec, PMacro114_Entry2_TimMin, PMacro114_Entry2_TimSec, PMacro114_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro114_Entry3_DelayMin, PMacro114_Entry3_DelaySec, PMacro114_Entry3_TimMin, PMacro114_Entry3_TimSec, PMacro114_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro114_Entry4_DelayMin, PMacro114_Entry4_DelaySec, PMacro114_Entry4_TimMin, PMacro114_Entry4_TimSec, PMacro114_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro114_Entry5_DelayMin, PMacro114_Entry5_DelaySec, PMacro114_Entry5_TimMin, PMacro114_Entry5_TimSec, PMacro114_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro114_Entry6_DelayMin, PMacro114_Entry6_DelaySec, PMacro114_Entry6_TimMin, PMacro114_Entry6_TimSec, PMacro114_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro114_Entry7_DelayMin, PMacro114_Entry7_DelaySec, PMacro114_Entry7_TimMin, PMacro114_Entry7_TimSec, PMacro114_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro114_Entry8_DelayMin, PMacro114_Entry8_DelaySec, PMacro114_Entry8_TimMin, PMacro114_Entry8_TimSec, PMacro114_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro114_Entry9_DelayMin, PMacro114_Entry9_DelaySec, PMacro114_Entry9_TimMin, PMacro114_Entry9_TimSec, PMacro114_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro114_Entry10_DelayMin, PMacro114_Entry10_DelaySec, PMacro114_Entry10_TimMin, PMacro114_Entry10_TimSec, PMacro114_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro114_Entry11_DelayMin, PMacro114_Entry11_DelaySec, PMacro114_Entry11_TimMin, PMacro114_Entry11_TimSec, PMacro114_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro114_Entry12_DelayMin, PMacro114_Entry12_DelaySec, PMacro114_Entry12_TimMin, PMacro114_Entry12_TimSec, PMacro114_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro114_Entry13_DelayMin, PMacro114_Entry13_DelaySec, PMacro114_Entry13_TimMin, PMacro114_Entry13_TimSec, PMacro114_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro114_Entry14_DelayMin, PMacro114_Entry14_DelaySec, PMacro114_Entry14_TimMin, PMacro114_Entry14_TimSec, PMacro114_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro114_Entry15_DelayMin, PMacro114_Entry15_DelaySec, PMacro114_Entry15_TimMin, PMacro114_Entry15_TimSec, PMacro114_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR114_STRING};

const struct super_macro Macro115 = {PMacro115_NumEntries,
		         PMacro115_Entry1_DelayMin, PMacro115_Entry1_DelaySec, PMacro115_Entry1_TimMin, PMacro115_Entry1_TimSec, PMacro115_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro115_Entry2_DelayMin, PMacro115_Entry2_DelaySec, PMacro115_Entry2_TimMin, PMacro115_Entry2_TimSec, PMacro115_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro115_Entry3_DelayMin, PMacro115_Entry3_DelaySec, PMacro115_Entry3_TimMin, PMacro115_Entry3_TimSec, PMacro115_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro115_Entry4_DelayMin, PMacro115_Entry4_DelaySec, PMacro115_Entry4_TimMin, PMacro115_Entry4_TimSec, PMacro115_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro115_Entry5_DelayMin, PMacro115_Entry5_DelaySec, PMacro115_Entry5_TimMin, PMacro115_Entry5_TimSec, PMacro115_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro115_Entry6_DelayMin, PMacro115_Entry6_DelaySec, PMacro115_Entry6_TimMin, PMacro115_Entry6_TimSec, PMacro115_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro115_Entry7_DelayMin, PMacro115_Entry7_DelaySec, PMacro115_Entry7_TimMin, PMacro115_Entry7_TimSec, PMacro115_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro115_Entry8_DelayMin, PMacro115_Entry8_DelaySec, PMacro115_Entry8_TimMin, PMacro115_Entry8_TimSec, PMacro115_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro115_Entry9_DelayMin, PMacro115_Entry9_DelaySec, PMacro115_Entry9_TimMin, PMacro115_Entry9_TimSec, PMacro115_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro115_Entry10_DelayMin, PMacro115_Entry10_DelaySec, PMacro115_Entry10_TimMin, PMacro115_Entry10_TimSec, PMacro115_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro115_Entry11_DelayMin, PMacro115_Entry11_DelaySec, PMacro115_Entry11_TimMin, PMacro115_Entry11_TimSec, PMacro115_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro115_Entry12_DelayMin, PMacro115_Entry12_DelaySec, PMacro115_Entry12_TimMin, PMacro115_Entry12_TimSec, PMacro115_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro115_Entry13_DelayMin, PMacro115_Entry13_DelaySec, PMacro115_Entry13_TimMin, PMacro115_Entry13_TimSec, PMacro115_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro115_Entry14_DelayMin, PMacro115_Entry14_DelaySec, PMacro115_Entry14_TimMin, PMacro115_Entry14_TimSec, PMacro115_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro115_Entry15_DelayMin, PMacro115_Entry15_DelaySec, PMacro115_Entry15_TimMin, PMacro115_Entry15_TimSec, PMacro115_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR115_STRING};

const struct super_macro Macro116 = {PMacro116_NumEntries,
		         PMacro116_Entry1_DelayMin, PMacro116_Entry1_DelaySec, PMacro116_Entry1_TimMin, PMacro116_Entry1_TimSec, PMacro116_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro116_Entry2_DelayMin, PMacro116_Entry2_DelaySec, PMacro116_Entry2_TimMin, PMacro116_Entry2_TimSec, PMacro116_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro116_Entry3_DelayMin, PMacro116_Entry3_DelaySec, PMacro116_Entry3_TimMin, PMacro116_Entry3_TimSec, PMacro116_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro116_Entry4_DelayMin, PMacro116_Entry4_DelaySec, PMacro116_Entry4_TimMin, PMacro116_Entry4_TimSec, PMacro116_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro116_Entry5_DelayMin, PMacro116_Entry5_DelaySec, PMacro116_Entry5_TimMin, PMacro116_Entry5_TimSec, PMacro116_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro116_Entry6_DelayMin, PMacro116_Entry6_DelaySec, PMacro116_Entry6_TimMin, PMacro116_Entry6_TimSec, PMacro116_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro116_Entry7_DelayMin, PMacro116_Entry7_DelaySec, PMacro116_Entry7_TimMin, PMacro116_Entry7_TimSec, PMacro116_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro116_Entry8_DelayMin, PMacro116_Entry8_DelaySec, PMacro116_Entry8_TimMin, PMacro116_Entry8_TimSec, PMacro116_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro116_Entry9_DelayMin, PMacro116_Entry9_DelaySec, PMacro116_Entry9_TimMin, PMacro116_Entry9_TimSec, PMacro116_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro116_Entry10_DelayMin, PMacro116_Entry10_DelaySec, PMacro116_Entry10_TimMin, PMacro116_Entry10_TimSec, PMacro116_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro116_Entry11_DelayMin, PMacro116_Entry11_DelaySec, PMacro116_Entry11_TimMin, PMacro116_Entry11_TimSec, PMacro116_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro116_Entry12_DelayMin, PMacro116_Entry12_DelaySec, PMacro116_Entry12_TimMin, PMacro116_Entry12_TimSec, PMacro116_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro116_Entry13_DelayMin, PMacro116_Entry13_DelaySec, PMacro116_Entry13_TimMin, PMacro116_Entry13_TimSec, PMacro116_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro116_Entry14_DelayMin, PMacro116_Entry14_DelaySec, PMacro116_Entry14_TimMin, PMacro116_Entry14_TimSec, PMacro116_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro116_Entry15_DelayMin, PMacro116_Entry15_DelaySec, PMacro116_Entry15_TimMin, PMacro116_Entry15_TimSec, PMacro116_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR116_STRING};

const struct super_macro Macro117 = {PMacro117_NumEntries,
		         PMacro117_Entry1_DelayMin, PMacro117_Entry1_DelaySec, PMacro117_Entry1_TimMin, PMacro117_Entry1_TimSec, PMacro117_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro117_Entry2_DelayMin, PMacro117_Entry2_DelaySec, PMacro117_Entry2_TimMin, PMacro117_Entry2_TimSec, PMacro117_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro117_Entry3_DelayMin, PMacro117_Entry3_DelaySec, PMacro117_Entry3_TimMin, PMacro117_Entry3_TimSec, PMacro117_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro117_Entry4_DelayMin, PMacro117_Entry4_DelaySec, PMacro117_Entry4_TimMin, PMacro117_Entry4_TimSec, PMacro117_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro117_Entry5_DelayMin, PMacro117_Entry5_DelaySec, PMacro117_Entry5_TimMin, PMacro117_Entry5_TimSec, PMacro117_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro117_Entry6_DelayMin, PMacro117_Entry6_DelaySec, PMacro117_Entry6_TimMin, PMacro117_Entry6_TimSec, PMacro117_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro117_Entry7_DelayMin, PMacro117_Entry7_DelaySec, PMacro117_Entry7_TimMin, PMacro117_Entry7_TimSec, PMacro117_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro117_Entry8_DelayMin, PMacro117_Entry8_DelaySec, PMacro117_Entry8_TimMin, PMacro117_Entry8_TimSec, PMacro117_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro117_Entry9_DelayMin, PMacro117_Entry9_DelaySec, PMacro117_Entry9_TimMin, PMacro117_Entry9_TimSec, PMacro117_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro117_Entry10_DelayMin, PMacro117_Entry10_DelaySec, PMacro117_Entry10_TimMin, PMacro117_Entry10_TimSec, PMacro117_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro117_Entry11_DelayMin, PMacro117_Entry11_DelaySec, PMacro117_Entry11_TimMin, PMacro117_Entry11_TimSec, PMacro117_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro117_Entry12_DelayMin, PMacro117_Entry12_DelaySec, PMacro117_Entry12_TimMin, PMacro117_Entry12_TimSec, PMacro117_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro117_Entry13_DelayMin, PMacro117_Entry13_DelaySec, PMacro117_Entry13_TimMin, PMacro117_Entry13_TimSec, PMacro117_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro117_Entry14_DelayMin, PMacro117_Entry14_DelaySec, PMacro117_Entry14_TimMin, PMacro117_Entry14_TimSec, PMacro117_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro117_Entry15_DelayMin, PMacro117_Entry15_DelaySec, PMacro117_Entry15_TimMin, PMacro117_Entry15_TimSec, PMacro117_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR117_STRING};

const struct super_macro Macro118 = {PMacro118_NumEntries,
		         PMacro118_Entry1_DelayMin, PMacro118_Entry1_DelaySec, PMacro118_Entry1_TimMin, PMacro118_Entry1_TimSec, PMacro118_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro118_Entry2_DelayMin, PMacro118_Entry2_DelaySec, PMacro118_Entry2_TimMin, PMacro118_Entry2_TimSec, PMacro118_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro118_Entry3_DelayMin, PMacro118_Entry3_DelaySec, PMacro118_Entry3_TimMin, PMacro118_Entry3_TimSec, PMacro118_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro118_Entry4_DelayMin, PMacro118_Entry4_DelaySec, PMacro118_Entry4_TimMin, PMacro118_Entry4_TimSec, PMacro118_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro118_Entry5_DelayMin, PMacro118_Entry5_DelaySec, PMacro118_Entry5_TimMin, PMacro118_Entry5_TimSec, PMacro118_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro118_Entry6_DelayMin, PMacro118_Entry6_DelaySec, PMacro118_Entry6_TimMin, PMacro118_Entry6_TimSec, PMacro118_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro118_Entry7_DelayMin, PMacro118_Entry7_DelaySec, PMacro118_Entry7_TimMin, PMacro118_Entry7_TimSec, PMacro118_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro118_Entry8_DelayMin, PMacro118_Entry8_DelaySec, PMacro118_Entry8_TimMin, PMacro118_Entry8_TimSec, PMacro118_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro118_Entry9_DelayMin, PMacro118_Entry9_DelaySec, PMacro118_Entry9_TimMin, PMacro118_Entry9_TimSec, PMacro118_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro118_Entry10_DelayMin, PMacro118_Entry10_DelaySec, PMacro118_Entry10_TimMin, PMacro118_Entry10_TimSec, PMacro118_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro118_Entry11_DelayMin, PMacro118_Entry11_DelaySec, PMacro118_Entry11_TimMin, PMacro118_Entry11_TimSec, PMacro118_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro118_Entry12_DelayMin, PMacro118_Entry12_DelaySec, PMacro118_Entry12_TimMin, PMacro118_Entry12_TimSec, PMacro118_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro118_Entry13_DelayMin, PMacro118_Entry13_DelaySec, PMacro118_Entry13_TimMin, PMacro118_Entry13_TimSec, PMacro118_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro118_Entry14_DelayMin, PMacro118_Entry14_DelaySec, PMacro118_Entry14_TimMin, PMacro118_Entry14_TimSec, PMacro118_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro118_Entry15_DelayMin, PMacro118_Entry15_DelaySec, PMacro118_Entry15_TimMin, PMacro118_Entry15_TimSec, PMacro118_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR118_STRING};

const struct super_macro Macro119 = {PMacro119_NumEntries,
		         PMacro119_Entry1_DelayMin, PMacro119_Entry1_DelaySec, PMacro119_Entry1_TimMin, PMacro119_Entry1_TimSec, PMacro119_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro119_Entry2_DelayMin, PMacro119_Entry2_DelaySec, PMacro119_Entry2_TimMin, PMacro119_Entry2_TimSec, PMacro119_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro119_Entry3_DelayMin, PMacro119_Entry3_DelaySec, PMacro119_Entry3_TimMin, PMacro119_Entry3_TimSec, PMacro119_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro119_Entry4_DelayMin, PMacro119_Entry4_DelaySec, PMacro119_Entry4_TimMin, PMacro119_Entry4_TimSec, PMacro119_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro119_Entry5_DelayMin, PMacro119_Entry5_DelaySec, PMacro119_Entry5_TimMin, PMacro119_Entry5_TimSec, PMacro119_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro119_Entry6_DelayMin, PMacro119_Entry6_DelaySec, PMacro119_Entry6_TimMin, PMacro119_Entry6_TimSec, PMacro119_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro119_Entry7_DelayMin, PMacro119_Entry7_DelaySec, PMacro119_Entry7_TimMin, PMacro119_Entry7_TimSec, PMacro119_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro119_Entry8_DelayMin, PMacro119_Entry8_DelaySec, PMacro119_Entry8_TimMin, PMacro119_Entry8_TimSec, PMacro119_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro119_Entry9_DelayMin, PMacro119_Entry9_DelaySec, PMacro119_Entry9_TimMin, PMacro119_Entry9_TimSec, PMacro119_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro119_Entry10_DelayMin, PMacro119_Entry10_DelaySec, PMacro119_Entry10_TimMin, PMacro119_Entry10_TimSec, PMacro119_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro119_Entry11_DelayMin, PMacro119_Entry11_DelaySec, PMacro119_Entry11_TimMin, PMacro119_Entry11_TimSec, PMacro119_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro119_Entry12_DelayMin, PMacro119_Entry12_DelaySec, PMacro119_Entry12_TimMin, PMacro119_Entry12_TimSec, PMacro119_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro119_Entry13_DelayMin, PMacro119_Entry13_DelaySec, PMacro119_Entry13_TimMin, PMacro119_Entry13_TimSec, PMacro119_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro119_Entry14_DelayMin, PMacro119_Entry14_DelaySec, PMacro119_Entry14_TimMin, PMacro119_Entry14_TimSec, PMacro119_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro119_Entry15_DelayMin, PMacro119_Entry15_DelaySec, PMacro119_Entry15_TimMin, PMacro119_Entry15_TimSec, PMacro119_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR119_STRING};

const struct super_macro Macro120 = {PMacro120_NumEntries,
		         PMacro120_Entry1_DelayMin, PMacro120_Entry1_DelaySec, PMacro120_Entry1_TimMin, PMacro120_Entry1_TimSec, PMacro120_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro120_Entry2_DelayMin, PMacro120_Entry2_DelaySec, PMacro120_Entry2_TimMin, PMacro120_Entry2_TimSec, PMacro120_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro120_Entry3_DelayMin, PMacro120_Entry3_DelaySec, PMacro120_Entry3_TimMin, PMacro120_Entry3_TimSec, PMacro120_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro120_Entry4_DelayMin, PMacro120_Entry4_DelaySec, PMacro120_Entry4_TimMin, PMacro120_Entry4_TimSec, PMacro120_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro120_Entry5_DelayMin, PMacro120_Entry5_DelaySec, PMacro120_Entry5_TimMin, PMacro120_Entry5_TimSec, PMacro120_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro120_Entry6_DelayMin, PMacro120_Entry6_DelaySec, PMacro120_Entry6_TimMin, PMacro120_Entry6_TimSec, PMacro120_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro120_Entry7_DelayMin, PMacro120_Entry7_DelaySec, PMacro120_Entry7_TimMin, PMacro120_Entry7_TimSec, PMacro120_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro120_Entry8_DelayMin, PMacro120_Entry8_DelaySec, PMacro120_Entry8_TimMin, PMacro120_Entry8_TimSec, PMacro120_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro120_Entry9_DelayMin, PMacro120_Entry9_DelaySec, PMacro120_Entry9_TimMin, PMacro120_Entry9_TimSec, PMacro120_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro120_Entry10_DelayMin, PMacro120_Entry10_DelaySec, PMacro120_Entry10_TimMin, PMacro120_Entry10_TimSec, PMacro120_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro120_Entry11_DelayMin, PMacro120_Entry11_DelaySec, PMacro120_Entry11_TimMin, PMacro120_Entry11_TimSec, PMacro120_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro120_Entry12_DelayMin, PMacro120_Entry12_DelaySec, PMacro120_Entry12_TimMin, PMacro120_Entry12_TimSec, PMacro120_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro120_Entry13_DelayMin, PMacro120_Entry13_DelaySec, PMacro120_Entry13_TimMin, PMacro120_Entry13_TimSec, PMacro120_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro120_Entry14_DelayMin, PMacro120_Entry14_DelaySec, PMacro120_Entry14_TimMin, PMacro120_Entry14_TimSec, PMacro120_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro120_Entry15_DelayMin, PMacro120_Entry15_DelaySec, PMacro120_Entry15_TimMin, PMacro120_Entry15_TimSec, PMacro120_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR120_STRING};

const struct super_macro Macro121 = {PMacro121_NumEntries,
		         PMacro121_Entry1_DelayMin, PMacro121_Entry1_DelaySec, PMacro121_Entry1_TimMin, PMacro121_Entry1_TimSec, PMacro121_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro121_Entry2_DelayMin, PMacro121_Entry2_DelaySec, PMacro121_Entry2_TimMin, PMacro121_Entry2_TimSec, PMacro121_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro121_Entry3_DelayMin, PMacro121_Entry3_DelaySec, PMacro121_Entry3_TimMin, PMacro121_Entry3_TimSec, PMacro121_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro121_Entry4_DelayMin, PMacro121_Entry4_DelaySec, PMacro121_Entry4_TimMin, PMacro121_Entry4_TimSec, PMacro121_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro121_Entry5_DelayMin, PMacro121_Entry5_DelaySec, PMacro121_Entry5_TimMin, PMacro121_Entry5_TimSec, PMacro121_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro121_Entry6_DelayMin, PMacro121_Entry6_DelaySec, PMacro121_Entry6_TimMin, PMacro121_Entry6_TimSec, PMacro121_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro121_Entry7_DelayMin, PMacro121_Entry7_DelaySec, PMacro121_Entry7_TimMin, PMacro121_Entry7_TimSec, PMacro121_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro121_Entry8_DelayMin, PMacro121_Entry8_DelaySec, PMacro121_Entry8_TimMin, PMacro121_Entry8_TimSec, PMacro121_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro121_Entry9_DelayMin, PMacro121_Entry9_DelaySec, PMacro121_Entry9_TimMin, PMacro121_Entry9_TimSec, PMacro121_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro121_Entry10_DelayMin, PMacro121_Entry10_DelaySec, PMacro121_Entry10_TimMin, PMacro121_Entry10_TimSec, PMacro121_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro121_Entry11_DelayMin, PMacro121_Entry11_DelaySec, PMacro121_Entry11_TimMin, PMacro121_Entry11_TimSec, PMacro121_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro121_Entry12_DelayMin, PMacro121_Entry12_DelaySec, PMacro121_Entry12_TimMin, PMacro121_Entry12_TimSec, PMacro121_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro121_Entry13_DelayMin, PMacro121_Entry13_DelaySec, PMacro121_Entry13_TimMin, PMacro121_Entry13_TimSec, PMacro121_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro121_Entry14_DelayMin, PMacro121_Entry14_DelaySec, PMacro121_Entry14_TimMin, PMacro121_Entry14_TimSec, PMacro121_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro121_Entry15_DelayMin, PMacro121_Entry15_DelaySec, PMacro121_Entry15_TimMin, PMacro121_Entry15_TimSec, PMacro121_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR121_STRING};

const struct super_macro Macro122 = {PMacro122_NumEntries,
		         PMacro122_Entry1_DelayMin, PMacro122_Entry1_DelaySec, PMacro122_Entry1_TimMin, PMacro122_Entry1_TimSec, PMacro122_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro122_Entry2_DelayMin, PMacro122_Entry2_DelaySec, PMacro122_Entry2_TimMin, PMacro122_Entry2_TimSec, PMacro122_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro122_Entry3_DelayMin, PMacro122_Entry3_DelaySec, PMacro122_Entry3_TimMin, PMacro122_Entry3_TimSec, PMacro122_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro122_Entry4_DelayMin, PMacro122_Entry4_DelaySec, PMacro122_Entry4_TimMin, PMacro122_Entry4_TimSec, PMacro122_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro122_Entry5_DelayMin, PMacro122_Entry5_DelaySec, PMacro122_Entry5_TimMin, PMacro122_Entry5_TimSec, PMacro122_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro122_Entry6_DelayMin, PMacro122_Entry6_DelaySec, PMacro122_Entry6_TimMin, PMacro122_Entry6_TimSec, PMacro122_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro122_Entry7_DelayMin, PMacro122_Entry7_DelaySec, PMacro122_Entry7_TimMin, PMacro122_Entry7_TimSec, PMacro122_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro122_Entry8_DelayMin, PMacro122_Entry8_DelaySec, PMacro122_Entry8_TimMin, PMacro122_Entry8_TimSec, PMacro122_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro122_Entry9_DelayMin, PMacro122_Entry9_DelaySec, PMacro122_Entry9_TimMin, PMacro122_Entry9_TimSec, PMacro122_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro122_Entry10_DelayMin, PMacro122_Entry10_DelaySec, PMacro122_Entry10_TimMin, PMacro122_Entry10_TimSec, PMacro122_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro122_Entry11_DelayMin, PMacro122_Entry11_DelaySec, PMacro122_Entry11_TimMin, PMacro122_Entry11_TimSec, PMacro122_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro122_Entry12_DelayMin, PMacro122_Entry12_DelaySec, PMacro122_Entry12_TimMin, PMacro122_Entry12_TimSec, PMacro122_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro122_Entry13_DelayMin, PMacro122_Entry13_DelaySec, PMacro122_Entry13_TimMin, PMacro122_Entry13_TimSec, PMacro122_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro122_Entry14_DelayMin, PMacro122_Entry14_DelaySec, PMacro122_Entry14_TimMin, PMacro122_Entry14_TimSec, PMacro122_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro122_Entry15_DelayMin, PMacro122_Entry15_DelaySec, PMacro122_Entry15_TimMin, PMacro122_Entry15_TimSec, PMacro122_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR122_STRING};

const struct super_macro Macro123 = {PMacro123_NumEntries,
		         PMacro123_Entry1_DelayMin, PMacro123_Entry1_DelaySec, PMacro123_Entry1_TimMin, PMacro123_Entry1_TimSec, PMacro123_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro123_Entry2_DelayMin, PMacro123_Entry2_DelaySec, PMacro123_Entry2_TimMin, PMacro123_Entry2_TimSec, PMacro123_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro123_Entry3_DelayMin, PMacro123_Entry3_DelaySec, PMacro123_Entry3_TimMin, PMacro123_Entry3_TimSec, PMacro123_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro123_Entry4_DelayMin, PMacro123_Entry4_DelaySec, PMacro123_Entry4_TimMin, PMacro123_Entry4_TimSec, PMacro123_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro123_Entry5_DelayMin, PMacro123_Entry5_DelaySec, PMacro123_Entry5_TimMin, PMacro123_Entry5_TimSec, PMacro123_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro123_Entry6_DelayMin, PMacro123_Entry6_DelaySec, PMacro123_Entry6_TimMin, PMacro123_Entry6_TimSec, PMacro123_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro123_Entry7_DelayMin, PMacro123_Entry7_DelaySec, PMacro123_Entry7_TimMin, PMacro123_Entry7_TimSec, PMacro123_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro123_Entry8_DelayMin, PMacro123_Entry8_DelaySec, PMacro123_Entry8_TimMin, PMacro123_Entry8_TimSec, PMacro123_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro123_Entry9_DelayMin, PMacro123_Entry9_DelaySec, PMacro123_Entry9_TimMin, PMacro123_Entry9_TimSec, PMacro123_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro123_Entry10_DelayMin, PMacro123_Entry10_DelaySec, PMacro123_Entry10_TimMin, PMacro123_Entry10_TimSec, PMacro123_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro123_Entry11_DelayMin, PMacro123_Entry11_DelaySec, PMacro123_Entry11_TimMin, PMacro123_Entry11_TimSec, PMacro123_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro123_Entry12_DelayMin, PMacro123_Entry12_DelaySec, PMacro123_Entry12_TimMin, PMacro123_Entry12_TimSec, PMacro123_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro123_Entry13_DelayMin, PMacro123_Entry13_DelaySec, PMacro123_Entry13_TimMin, PMacro123_Entry13_TimSec, PMacro123_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro123_Entry14_DelayMin, PMacro123_Entry14_DelaySec, PMacro123_Entry14_TimMin, PMacro123_Entry14_TimSec, PMacro123_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro123_Entry15_DelayMin, PMacro123_Entry15_DelaySec, PMacro123_Entry15_TimMin, PMacro123_Entry15_TimSec, PMacro123_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR123_STRING};

const struct super_macro Macro124 = {PMacro124_NumEntries,
		         PMacro124_Entry1_DelayMin, PMacro124_Entry1_DelaySec, PMacro124_Entry1_TimMin, PMacro124_Entry1_TimSec, PMacro124_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro124_Entry2_DelayMin, PMacro124_Entry2_DelaySec, PMacro124_Entry2_TimMin, PMacro124_Entry2_TimSec, PMacro124_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro124_Entry3_DelayMin, PMacro124_Entry3_DelaySec, PMacro124_Entry3_TimMin, PMacro124_Entry3_TimSec, PMacro124_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro124_Entry4_DelayMin, PMacro124_Entry4_DelaySec, PMacro124_Entry4_TimMin, PMacro124_Entry4_TimSec, PMacro124_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro124_Entry5_DelayMin, PMacro124_Entry5_DelaySec, PMacro124_Entry5_TimMin, PMacro124_Entry5_TimSec, PMacro124_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro124_Entry6_DelayMin, PMacro124_Entry6_DelaySec, PMacro124_Entry6_TimMin, PMacro124_Entry6_TimSec, PMacro124_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro124_Entry7_DelayMin, PMacro124_Entry7_DelaySec, PMacro124_Entry7_TimMin, PMacro124_Entry7_TimSec, PMacro124_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro124_Entry8_DelayMin, PMacro124_Entry8_DelaySec, PMacro124_Entry8_TimMin, PMacro124_Entry8_TimSec, PMacro124_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro124_Entry9_DelayMin, PMacro124_Entry9_DelaySec, PMacro124_Entry9_TimMin, PMacro124_Entry9_TimSec, PMacro124_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro124_Entry10_DelayMin, PMacro124_Entry10_DelaySec, PMacro124_Entry10_TimMin, PMacro124_Entry10_TimSec, PMacro124_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro124_Entry11_DelayMin, PMacro124_Entry11_DelaySec, PMacro124_Entry11_TimMin, PMacro124_Entry11_TimSec, PMacro124_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro124_Entry12_DelayMin, PMacro124_Entry12_DelaySec, PMacro124_Entry12_TimMin, PMacro124_Entry12_TimSec, PMacro124_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro124_Entry13_DelayMin, PMacro124_Entry13_DelaySec, PMacro124_Entry13_TimMin, PMacro124_Entry13_TimSec, PMacro124_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro124_Entry14_DelayMin, PMacro124_Entry14_DelaySec, PMacro124_Entry14_TimMin, PMacro124_Entry14_TimSec, PMacro124_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro124_Entry15_DelayMin, PMacro124_Entry15_DelaySec, PMacro124_Entry15_TimMin, PMacro124_Entry15_TimSec, PMacro124_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR124_STRING};

const struct super_macro Macro125 = {PMacro125_NumEntries,
		         PMacro125_Entry1_DelayMin, PMacro125_Entry1_DelaySec, PMacro125_Entry1_TimMin, PMacro125_Entry1_TimSec, PMacro125_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro125_Entry2_DelayMin, PMacro125_Entry2_DelaySec, PMacro125_Entry2_TimMin, PMacro125_Entry2_TimSec, PMacro125_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro125_Entry3_DelayMin, PMacro125_Entry3_DelaySec, PMacro125_Entry3_TimMin, PMacro125_Entry3_TimSec, PMacro125_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro125_Entry4_DelayMin, PMacro125_Entry4_DelaySec, PMacro125_Entry4_TimMin, PMacro125_Entry4_TimSec, PMacro125_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro125_Entry5_DelayMin, PMacro125_Entry5_DelaySec, PMacro125_Entry5_TimMin, PMacro125_Entry5_TimSec, PMacro125_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro125_Entry6_DelayMin, PMacro125_Entry6_DelaySec, PMacro125_Entry6_TimMin, PMacro125_Entry6_TimSec, PMacro125_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro125_Entry7_DelayMin, PMacro125_Entry7_DelaySec, PMacro125_Entry7_TimMin, PMacro125_Entry7_TimSec, PMacro125_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro125_Entry8_DelayMin, PMacro125_Entry8_DelaySec, PMacro125_Entry8_TimMin, PMacro125_Entry8_TimSec, PMacro125_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro125_Entry9_DelayMin, PMacro125_Entry9_DelaySec, PMacro125_Entry9_TimMin, PMacro125_Entry9_TimSec, PMacro125_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro125_Entry10_DelayMin, PMacro125_Entry10_DelaySec, PMacro125_Entry10_TimMin, PMacro125_Entry10_TimSec, PMacro125_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro125_Entry11_DelayMin, PMacro125_Entry11_DelaySec, PMacro125_Entry11_TimMin, PMacro125_Entry11_TimSec, PMacro125_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro125_Entry12_DelayMin, PMacro125_Entry12_DelaySec, PMacro125_Entry12_TimMin, PMacro125_Entry12_TimSec, PMacro125_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro125_Entry13_DelayMin, PMacro125_Entry13_DelaySec, PMacro125_Entry13_TimMin, PMacro125_Entry13_TimSec, PMacro125_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro125_Entry14_DelayMin, PMacro125_Entry14_DelaySec, PMacro125_Entry14_TimMin, PMacro125_Entry14_TimSec, PMacro125_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro125_Entry15_DelayMin, PMacro125_Entry15_DelaySec, PMacro125_Entry15_TimMin, PMacro125_Entry15_TimSec, PMacro125_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR125_STRING};

const struct super_macro Macro126 = {PMacro126_NumEntries,
		         PMacro126_Entry1_DelayMin, PMacro126_Entry1_DelaySec, PMacro126_Entry1_TimMin, PMacro126_Entry1_TimSec, PMacro126_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro126_Entry2_DelayMin, PMacro126_Entry2_DelaySec, PMacro126_Entry2_TimMin, PMacro126_Entry2_TimSec, PMacro126_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro126_Entry3_DelayMin, PMacro126_Entry3_DelaySec, PMacro126_Entry3_TimMin, PMacro126_Entry3_TimSec, PMacro126_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro126_Entry4_DelayMin, PMacro126_Entry4_DelaySec, PMacro126_Entry4_TimMin, PMacro126_Entry4_TimSec, PMacro126_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro126_Entry5_DelayMin, PMacro126_Entry5_DelaySec, PMacro126_Entry5_TimMin, PMacro126_Entry5_TimSec, PMacro126_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro126_Entry6_DelayMin, PMacro126_Entry6_DelaySec, PMacro126_Entry6_TimMin, PMacro126_Entry6_TimSec, PMacro126_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro126_Entry7_DelayMin, PMacro126_Entry7_DelaySec, PMacro126_Entry7_TimMin, PMacro126_Entry7_TimSec, PMacro126_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro126_Entry8_DelayMin, PMacro126_Entry8_DelaySec, PMacro126_Entry8_TimMin, PMacro126_Entry8_TimSec, PMacro126_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro126_Entry9_DelayMin, PMacro126_Entry9_DelaySec, PMacro126_Entry9_TimMin, PMacro126_Entry9_TimSec, PMacro126_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro126_Entry10_DelayMin, PMacro126_Entry10_DelaySec, PMacro126_Entry10_TimMin, PMacro126_Entry10_TimSec, PMacro126_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro126_Entry11_DelayMin, PMacro126_Entry11_DelaySec, PMacro126_Entry11_TimMin, PMacro126_Entry11_TimSec, PMacro126_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro126_Entry12_DelayMin, PMacro126_Entry12_DelaySec, PMacro126_Entry12_TimMin, PMacro126_Entry12_TimSec, PMacro126_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro126_Entry13_DelayMin, PMacro126_Entry13_DelaySec, PMacro126_Entry13_TimMin, PMacro126_Entry13_TimSec, PMacro126_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro126_Entry14_DelayMin, PMacro126_Entry14_DelaySec, PMacro126_Entry14_TimMin, PMacro126_Entry14_TimSec, PMacro126_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro126_Entry15_DelayMin, PMacro126_Entry15_DelaySec, PMacro126_Entry15_TimMin, PMacro126_Entry15_TimSec, PMacro126_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR126_STRING};

const struct super_macro Macro127 = {PMacro127_NumEntries,
		         PMacro127_Entry1_DelayMin, PMacro127_Entry1_DelaySec, PMacro127_Entry1_TimMin, PMacro127_Entry1_TimSec, PMacro127_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro127_Entry2_DelayMin, PMacro127_Entry2_DelaySec, PMacro127_Entry2_TimMin, PMacro127_Entry2_TimSec, PMacro127_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro127_Entry3_DelayMin, PMacro127_Entry3_DelaySec, PMacro127_Entry3_TimMin, PMacro127_Entry3_TimSec, PMacro127_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro127_Entry4_DelayMin, PMacro127_Entry4_DelaySec, PMacro127_Entry4_TimMin, PMacro127_Entry4_TimSec, PMacro127_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro127_Entry5_DelayMin, PMacro127_Entry5_DelaySec, PMacro127_Entry5_TimMin, PMacro127_Entry5_TimSec, PMacro127_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro127_Entry6_DelayMin, PMacro127_Entry6_DelaySec, PMacro127_Entry6_TimMin, PMacro127_Entry6_TimSec, PMacro127_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro127_Entry7_DelayMin, PMacro127_Entry7_DelaySec, PMacro127_Entry7_TimMin, PMacro127_Entry7_TimSec, PMacro127_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro127_Entry8_DelayMin, PMacro127_Entry8_DelaySec, PMacro127_Entry8_TimMin, PMacro127_Entry8_TimSec, PMacro127_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro127_Entry9_DelayMin, PMacro127_Entry9_DelaySec, PMacro127_Entry9_TimMin, PMacro127_Entry9_TimSec, PMacro127_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro127_Entry10_DelayMin, PMacro127_Entry10_DelaySec, PMacro127_Entry10_TimMin, PMacro127_Entry10_TimSec, PMacro127_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro127_Entry11_DelayMin, PMacro127_Entry11_DelaySec, PMacro127_Entry11_TimMin, PMacro127_Entry11_TimSec, PMacro127_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro127_Entry12_DelayMin, PMacro127_Entry12_DelaySec, PMacro127_Entry12_TimMin, PMacro127_Entry12_TimSec, PMacro127_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro127_Entry13_DelayMin, PMacro127_Entry13_DelaySec, PMacro127_Entry13_TimMin, PMacro127_Entry13_TimSec, PMacro127_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro127_Entry14_DelayMin, PMacro127_Entry14_DelaySec, PMacro127_Entry14_TimMin, PMacro127_Entry14_TimSec, PMacro127_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro127_Entry15_DelayMin, PMacro127_Entry15_DelaySec, PMacro127_Entry15_TimMin, PMacro127_Entry15_TimSec, PMacro127_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR127_STRING};

const struct super_macro Macro128 = {PMacro128_NumEntries,
		         PMacro128_Entry1_DelayMin, PMacro128_Entry1_DelaySec, PMacro128_Entry1_TimMin, PMacro128_Entry1_TimSec, PMacro128_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro128_Entry2_DelayMin, PMacro128_Entry2_DelaySec, PMacro128_Entry2_TimMin, PMacro128_Entry2_TimSec, PMacro128_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro128_Entry3_DelayMin, PMacro128_Entry3_DelaySec, PMacro128_Entry3_TimMin, PMacro128_Entry3_TimSec, PMacro128_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro128_Entry4_DelayMin, PMacro128_Entry4_DelaySec, PMacro128_Entry4_TimMin, PMacro128_Entry4_TimSec, PMacro128_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro128_Entry5_DelayMin, PMacro128_Entry5_DelaySec, PMacro128_Entry5_TimMin, PMacro128_Entry5_TimSec, PMacro128_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro128_Entry6_DelayMin, PMacro128_Entry6_DelaySec, PMacro128_Entry6_TimMin, PMacro128_Entry6_TimSec, PMacro128_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro128_Entry7_DelayMin, PMacro128_Entry7_DelaySec, PMacro128_Entry7_TimMin, PMacro128_Entry7_TimSec, PMacro128_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro128_Entry8_DelayMin, PMacro128_Entry8_DelaySec, PMacro128_Entry8_TimMin, PMacro128_Entry8_TimSec, PMacro128_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro128_Entry9_DelayMin, PMacro128_Entry9_DelaySec, PMacro128_Entry9_TimMin, PMacro128_Entry9_TimSec, PMacro128_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro128_Entry10_DelayMin, PMacro128_Entry10_DelaySec, PMacro128_Entry10_TimMin, PMacro128_Entry10_TimSec, PMacro128_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro128_Entry11_DelayMin, PMacro128_Entry11_DelaySec, PMacro128_Entry11_TimMin, PMacro128_Entry11_TimSec, PMacro128_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro128_Entry12_DelayMin, PMacro128_Entry12_DelaySec, PMacro128_Entry12_TimMin, PMacro128_Entry12_TimSec, PMacro128_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro128_Entry13_DelayMin, PMacro128_Entry13_DelaySec, PMacro128_Entry13_TimMin, PMacro128_Entry13_TimSec, PMacro128_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro128_Entry14_DelayMin, PMacro128_Entry14_DelaySec, PMacro128_Entry14_TimMin, PMacro128_Entry14_TimSec, PMacro128_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro128_Entry15_DelayMin, PMacro128_Entry15_DelaySec, PMacro128_Entry15_TimMin, PMacro128_Entry15_TimSec, PMacro128_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR128_STRING};

const struct super_macro Macro129 = {PMacro129_NumEntries,
		         PMacro129_Entry1_DelayMin, PMacro129_Entry1_DelaySec, PMacro129_Entry1_TimMin, PMacro129_Entry1_TimSec, PMacro129_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro129_Entry2_DelayMin, PMacro129_Entry2_DelaySec, PMacro129_Entry2_TimMin, PMacro129_Entry2_TimSec, PMacro129_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro129_Entry3_DelayMin, PMacro129_Entry3_DelaySec, PMacro129_Entry3_TimMin, PMacro129_Entry3_TimSec, PMacro129_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro129_Entry4_DelayMin, PMacro129_Entry4_DelaySec, PMacro129_Entry4_TimMin, PMacro129_Entry4_TimSec, PMacro129_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro129_Entry5_DelayMin, PMacro129_Entry5_DelaySec, PMacro129_Entry5_TimMin, PMacro129_Entry5_TimSec, PMacro129_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro129_Entry6_DelayMin, PMacro129_Entry6_DelaySec, PMacro129_Entry6_TimMin, PMacro129_Entry6_TimSec, PMacro129_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro129_Entry7_DelayMin, PMacro129_Entry7_DelaySec, PMacro129_Entry7_TimMin, PMacro129_Entry7_TimSec, PMacro129_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro129_Entry8_DelayMin, PMacro129_Entry8_DelaySec, PMacro129_Entry8_TimMin, PMacro129_Entry8_TimSec, PMacro129_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro129_Entry9_DelayMin, PMacro129_Entry9_DelaySec, PMacro129_Entry9_TimMin, PMacro129_Entry9_TimSec, PMacro129_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro129_Entry10_DelayMin, PMacro129_Entry10_DelaySec, PMacro129_Entry10_TimMin, PMacro129_Entry10_TimSec, PMacro129_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro129_Entry11_DelayMin, PMacro129_Entry11_DelaySec, PMacro129_Entry11_TimMin, PMacro129_Entry11_TimSec, PMacro129_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro129_Entry12_DelayMin, PMacro129_Entry12_DelaySec, PMacro129_Entry12_TimMin, PMacro129_Entry12_TimSec, PMacro129_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro129_Entry13_DelayMin, PMacro129_Entry13_DelaySec, PMacro129_Entry13_TimMin, PMacro129_Entry13_TimSec, PMacro129_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro129_Entry14_DelayMin, PMacro129_Entry14_DelaySec, PMacro129_Entry14_TimMin, PMacro129_Entry14_TimSec, PMacro129_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro129_Entry15_DelayMin, PMacro129_Entry15_DelaySec, PMacro129_Entry15_TimMin, PMacro129_Entry15_TimSec, PMacro129_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR129_STRING};

const struct super_macro Macro130 = {PMacro130_NumEntries,
		         PMacro130_Entry1_DelayMin, PMacro130_Entry1_DelaySec, PMacro130_Entry1_TimMin, PMacro130_Entry1_TimSec, PMacro130_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro130_Entry2_DelayMin, PMacro130_Entry2_DelaySec, PMacro130_Entry2_TimMin, PMacro130_Entry2_TimSec, PMacro130_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro130_Entry3_DelayMin, PMacro130_Entry3_DelaySec, PMacro130_Entry3_TimMin, PMacro130_Entry3_TimSec, PMacro130_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro130_Entry4_DelayMin, PMacro130_Entry4_DelaySec, PMacro130_Entry4_TimMin, PMacro130_Entry4_TimSec, PMacro130_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro130_Entry5_DelayMin, PMacro130_Entry5_DelaySec, PMacro130_Entry5_TimMin, PMacro130_Entry5_TimSec, PMacro130_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro130_Entry6_DelayMin, PMacro130_Entry6_DelaySec, PMacro130_Entry6_TimMin, PMacro130_Entry6_TimSec, PMacro130_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro130_Entry7_DelayMin, PMacro130_Entry7_DelaySec, PMacro130_Entry7_TimMin, PMacro130_Entry7_TimSec, PMacro130_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro130_Entry8_DelayMin, PMacro130_Entry8_DelaySec, PMacro130_Entry8_TimMin, PMacro130_Entry8_TimSec, PMacro130_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro130_Entry9_DelayMin, PMacro130_Entry9_DelaySec, PMacro130_Entry9_TimMin, PMacro130_Entry9_TimSec, PMacro130_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro130_Entry10_DelayMin, PMacro130_Entry10_DelaySec, PMacro130_Entry10_TimMin, PMacro130_Entry10_TimSec, PMacro130_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro130_Entry11_DelayMin, PMacro130_Entry11_DelaySec, PMacro130_Entry11_TimMin, PMacro130_Entry11_TimSec, PMacro130_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro130_Entry12_DelayMin, PMacro130_Entry12_DelaySec, PMacro130_Entry12_TimMin, PMacro130_Entry12_TimSec, PMacro130_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro130_Entry13_DelayMin, PMacro130_Entry13_DelaySec, PMacro130_Entry13_TimMin, PMacro130_Entry13_TimSec, PMacro130_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro130_Entry14_DelayMin, PMacro130_Entry14_DelaySec, PMacro130_Entry14_TimMin, PMacro130_Entry14_TimSec, PMacro130_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro130_Entry15_DelayMin, PMacro130_Entry15_DelaySec, PMacro130_Entry15_TimMin, PMacro130_Entry15_TimSec, PMacro130_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR130_STRING};

const struct super_macro Macro131 = {PMacro131_NumEntries,
		         PMacro131_Entry1_DelayMin, PMacro131_Entry1_DelaySec, PMacro131_Entry1_TimMin, PMacro131_Entry1_TimSec, PMacro131_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro131_Entry2_DelayMin, PMacro131_Entry2_DelaySec, PMacro131_Entry2_TimMin, PMacro131_Entry2_TimSec, PMacro131_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro131_Entry3_DelayMin, PMacro131_Entry3_DelaySec, PMacro131_Entry3_TimMin, PMacro131_Entry3_TimSec, PMacro131_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro131_Entry4_DelayMin, PMacro131_Entry4_DelaySec, PMacro131_Entry4_TimMin, PMacro131_Entry4_TimSec, PMacro131_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro131_Entry5_DelayMin, PMacro131_Entry5_DelaySec, PMacro131_Entry5_TimMin, PMacro131_Entry5_TimSec, PMacro131_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro131_Entry6_DelayMin, PMacro131_Entry6_DelaySec, PMacro131_Entry6_TimMin, PMacro131_Entry6_TimSec, PMacro131_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro131_Entry7_DelayMin, PMacro131_Entry7_DelaySec, PMacro131_Entry7_TimMin, PMacro131_Entry7_TimSec, PMacro131_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro131_Entry8_DelayMin, PMacro131_Entry8_DelaySec, PMacro131_Entry8_TimMin, PMacro131_Entry8_TimSec, PMacro131_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro131_Entry9_DelayMin, PMacro131_Entry9_DelaySec, PMacro131_Entry9_TimMin, PMacro131_Entry9_TimSec, PMacro131_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro131_Entry10_DelayMin, PMacro131_Entry10_DelaySec, PMacro131_Entry10_TimMin, PMacro131_Entry10_TimSec, PMacro131_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro131_Entry11_DelayMin, PMacro131_Entry11_DelaySec, PMacro131_Entry11_TimMin, PMacro131_Entry11_TimSec, PMacro131_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro131_Entry12_DelayMin, PMacro131_Entry12_DelaySec, PMacro131_Entry12_TimMin, PMacro131_Entry12_TimSec, PMacro131_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro131_Entry13_DelayMin, PMacro131_Entry13_DelaySec, PMacro131_Entry13_TimMin, PMacro131_Entry13_TimSec, PMacro131_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro131_Entry14_DelayMin, PMacro131_Entry14_DelaySec, PMacro131_Entry14_TimMin, PMacro131_Entry14_TimSec, PMacro131_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro131_Entry15_DelayMin, PMacro131_Entry15_DelaySec, PMacro131_Entry15_TimMin, PMacro131_Entry15_TimSec, PMacro131_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR131_STRING};

const struct super_macro Macro132 = {PMacro132_NumEntries,
		         PMacro132_Entry1_DelayMin, PMacro132_Entry1_DelaySec, PMacro132_Entry1_TimMin, PMacro132_Entry1_TimSec, PMacro132_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro132_Entry2_DelayMin, PMacro132_Entry2_DelaySec, PMacro132_Entry2_TimMin, PMacro132_Entry2_TimSec, PMacro132_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro132_Entry3_DelayMin, PMacro132_Entry3_DelaySec, PMacro132_Entry3_TimMin, PMacro132_Entry3_TimSec, PMacro132_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro132_Entry4_DelayMin, PMacro132_Entry4_DelaySec, PMacro132_Entry4_TimMin, PMacro132_Entry4_TimSec, PMacro132_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro132_Entry5_DelayMin, PMacro132_Entry5_DelaySec, PMacro132_Entry5_TimMin, PMacro132_Entry5_TimSec, PMacro132_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro132_Entry6_DelayMin, PMacro132_Entry6_DelaySec, PMacro132_Entry6_TimMin, PMacro132_Entry6_TimSec, PMacro132_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro132_Entry7_DelayMin, PMacro132_Entry7_DelaySec, PMacro132_Entry7_TimMin, PMacro132_Entry7_TimSec, PMacro132_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro132_Entry8_DelayMin, PMacro132_Entry8_DelaySec, PMacro132_Entry8_TimMin, PMacro132_Entry8_TimSec, PMacro132_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro132_Entry9_DelayMin, PMacro132_Entry9_DelaySec, PMacro132_Entry9_TimMin, PMacro132_Entry9_TimSec, PMacro132_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro132_Entry10_DelayMin, PMacro132_Entry10_DelaySec, PMacro132_Entry10_TimMin, PMacro132_Entry10_TimSec, PMacro132_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro132_Entry11_DelayMin, PMacro132_Entry11_DelaySec, PMacro132_Entry11_TimMin, PMacro132_Entry11_TimSec, PMacro132_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro132_Entry12_DelayMin, PMacro132_Entry12_DelaySec, PMacro132_Entry12_TimMin, PMacro132_Entry12_TimSec, PMacro132_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro132_Entry13_DelayMin, PMacro132_Entry13_DelaySec, PMacro132_Entry13_TimMin, PMacro132_Entry13_TimSec, PMacro132_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro132_Entry14_DelayMin, PMacro132_Entry14_DelaySec, PMacro132_Entry14_TimMin, PMacro132_Entry14_TimSec, PMacro132_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro132_Entry15_DelayMin, PMacro132_Entry15_DelaySec, PMacro132_Entry15_TimMin, PMacro132_Entry15_TimSec, PMacro132_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR132_STRING};

const struct super_macro Macro133 = {PMacro133_NumEntries,
		         PMacro133_Entry1_DelayMin, PMacro133_Entry1_DelaySec, PMacro133_Entry1_TimMin, PMacro133_Entry1_TimSec, PMacro133_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro133_Entry2_DelayMin, PMacro133_Entry2_DelaySec, PMacro133_Entry2_TimMin, PMacro133_Entry2_TimSec, PMacro133_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro133_Entry3_DelayMin, PMacro133_Entry3_DelaySec, PMacro133_Entry3_TimMin, PMacro133_Entry3_TimSec, PMacro133_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro133_Entry4_DelayMin, PMacro133_Entry4_DelaySec, PMacro133_Entry4_TimMin, PMacro133_Entry4_TimSec, PMacro133_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro133_Entry5_DelayMin, PMacro133_Entry5_DelaySec, PMacro133_Entry5_TimMin, PMacro133_Entry5_TimSec, PMacro133_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro133_Entry6_DelayMin, PMacro133_Entry6_DelaySec, PMacro133_Entry6_TimMin, PMacro133_Entry6_TimSec, PMacro133_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro133_Entry7_DelayMin, PMacro133_Entry7_DelaySec, PMacro133_Entry7_TimMin, PMacro133_Entry7_TimSec, PMacro133_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro133_Entry8_DelayMin, PMacro133_Entry8_DelaySec, PMacro133_Entry8_TimMin, PMacro133_Entry8_TimSec, PMacro133_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro133_Entry9_DelayMin, PMacro133_Entry9_DelaySec, PMacro133_Entry9_TimMin, PMacro133_Entry9_TimSec, PMacro133_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro133_Entry10_DelayMin, PMacro133_Entry10_DelaySec, PMacro133_Entry10_TimMin, PMacro133_Entry10_TimSec, PMacro133_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro133_Entry11_DelayMin, PMacro133_Entry11_DelaySec, PMacro133_Entry11_TimMin, PMacro133_Entry11_TimSec, PMacro133_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro133_Entry12_DelayMin, PMacro133_Entry12_DelaySec, PMacro133_Entry12_TimMin, PMacro133_Entry12_TimSec, PMacro133_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro133_Entry13_DelayMin, PMacro133_Entry13_DelaySec, PMacro133_Entry13_TimMin, PMacro133_Entry13_TimSec, PMacro133_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro133_Entry14_DelayMin, PMacro133_Entry14_DelaySec, PMacro133_Entry14_TimMin, PMacro133_Entry14_TimSec, PMacro133_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro133_Entry15_DelayMin, PMacro133_Entry15_DelaySec, PMacro133_Entry15_TimMin, PMacro133_Entry15_TimSec, PMacro133_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR133_STRING};

const struct super_macro Macro134 = {PMacro134_NumEntries,
		         PMacro134_Entry1_DelayMin, PMacro134_Entry1_DelaySec, PMacro134_Entry1_TimMin, PMacro134_Entry1_TimSec, PMacro134_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro134_Entry2_DelayMin, PMacro134_Entry2_DelaySec, PMacro134_Entry2_TimMin, PMacro134_Entry2_TimSec, PMacro134_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro134_Entry3_DelayMin, PMacro134_Entry3_DelaySec, PMacro134_Entry3_TimMin, PMacro134_Entry3_TimSec, PMacro134_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro134_Entry4_DelayMin, PMacro134_Entry4_DelaySec, PMacro134_Entry4_TimMin, PMacro134_Entry4_TimSec, PMacro134_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro134_Entry5_DelayMin, PMacro134_Entry5_DelaySec, PMacro134_Entry5_TimMin, PMacro134_Entry5_TimSec, PMacro134_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro134_Entry6_DelayMin, PMacro134_Entry6_DelaySec, PMacro134_Entry6_TimMin, PMacro134_Entry6_TimSec, PMacro134_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro134_Entry7_DelayMin, PMacro134_Entry7_DelaySec, PMacro134_Entry7_TimMin, PMacro134_Entry7_TimSec, PMacro134_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro134_Entry8_DelayMin, PMacro134_Entry8_DelaySec, PMacro134_Entry8_TimMin, PMacro134_Entry8_TimSec, PMacro134_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro134_Entry9_DelayMin, PMacro134_Entry9_DelaySec, PMacro134_Entry9_TimMin, PMacro134_Entry9_TimSec, PMacro134_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro134_Entry10_DelayMin, PMacro134_Entry10_DelaySec, PMacro134_Entry10_TimMin, PMacro134_Entry10_TimSec, PMacro134_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro134_Entry11_DelayMin, PMacro134_Entry11_DelaySec, PMacro134_Entry11_TimMin, PMacro134_Entry11_TimSec, PMacro134_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro134_Entry12_DelayMin, PMacro134_Entry12_DelaySec, PMacro134_Entry12_TimMin, PMacro134_Entry12_TimSec, PMacro134_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro134_Entry13_DelayMin, PMacro134_Entry13_DelaySec, PMacro134_Entry13_TimMin, PMacro134_Entry13_TimSec, PMacro134_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro134_Entry14_DelayMin, PMacro134_Entry14_DelaySec, PMacro134_Entry14_TimMin, PMacro134_Entry14_TimSec, PMacro134_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro134_Entry15_DelayMin, PMacro134_Entry15_DelaySec, PMacro134_Entry15_TimMin, PMacro134_Entry15_TimSec, PMacro134_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR134_STRING};

const struct super_macro Macro135 = {PMacro135_NumEntries,
		         PMacro135_Entry1_DelayMin, PMacro135_Entry1_DelaySec, PMacro135_Entry1_TimMin, PMacro135_Entry1_TimSec, PMacro135_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro135_Entry2_DelayMin, PMacro135_Entry2_DelaySec, PMacro135_Entry2_TimMin, PMacro135_Entry2_TimSec, PMacro135_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro135_Entry3_DelayMin, PMacro135_Entry3_DelaySec, PMacro135_Entry3_TimMin, PMacro135_Entry3_TimSec, PMacro135_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro135_Entry4_DelayMin, PMacro135_Entry4_DelaySec, PMacro135_Entry4_TimMin, PMacro135_Entry4_TimSec, PMacro135_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro135_Entry5_DelayMin, PMacro135_Entry5_DelaySec, PMacro135_Entry5_TimMin, PMacro135_Entry5_TimSec, PMacro135_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro135_Entry6_DelayMin, PMacro135_Entry6_DelaySec, PMacro135_Entry6_TimMin, PMacro135_Entry6_TimSec, PMacro135_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro135_Entry7_DelayMin, PMacro135_Entry7_DelaySec, PMacro135_Entry7_TimMin, PMacro135_Entry7_TimSec, PMacro135_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro135_Entry8_DelayMin, PMacro135_Entry8_DelaySec, PMacro135_Entry8_TimMin, PMacro135_Entry8_TimSec, PMacro135_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro135_Entry9_DelayMin, PMacro135_Entry9_DelaySec, PMacro135_Entry9_TimMin, PMacro135_Entry9_TimSec, PMacro135_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro135_Entry10_DelayMin, PMacro135_Entry10_DelaySec, PMacro135_Entry10_TimMin, PMacro135_Entry10_TimSec, PMacro135_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro135_Entry11_DelayMin, PMacro135_Entry11_DelaySec, PMacro135_Entry11_TimMin, PMacro135_Entry11_TimSec, PMacro135_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro135_Entry12_DelayMin, PMacro135_Entry12_DelaySec, PMacro135_Entry12_TimMin, PMacro135_Entry12_TimSec, PMacro135_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro135_Entry13_DelayMin, PMacro135_Entry13_DelaySec, PMacro135_Entry13_TimMin, PMacro135_Entry13_TimSec, PMacro135_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro135_Entry14_DelayMin, PMacro135_Entry14_DelaySec, PMacro135_Entry14_TimMin, PMacro135_Entry14_TimSec, PMacro135_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro135_Entry15_DelayMin, PMacro135_Entry15_DelaySec, PMacro135_Entry15_TimMin, PMacro135_Entry15_TimSec, PMacro135_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR135_STRING};

const struct super_macro Macro136 = {PMacro136_NumEntries,
		         PMacro136_Entry1_DelayMin, PMacro136_Entry1_DelaySec, PMacro136_Entry1_TimMin, PMacro136_Entry1_TimSec, PMacro136_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro136_Entry2_DelayMin, PMacro136_Entry2_DelaySec, PMacro136_Entry2_TimMin, PMacro136_Entry2_TimSec, PMacro136_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro136_Entry3_DelayMin, PMacro136_Entry3_DelaySec, PMacro136_Entry3_TimMin, PMacro136_Entry3_TimSec, PMacro136_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro136_Entry4_DelayMin, PMacro136_Entry4_DelaySec, PMacro136_Entry4_TimMin, PMacro136_Entry4_TimSec, PMacro136_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro136_Entry5_DelayMin, PMacro136_Entry5_DelaySec, PMacro136_Entry5_TimMin, PMacro136_Entry5_TimSec, PMacro136_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro136_Entry6_DelayMin, PMacro136_Entry6_DelaySec, PMacro136_Entry6_TimMin, PMacro136_Entry6_TimSec, PMacro136_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro136_Entry7_DelayMin, PMacro136_Entry7_DelaySec, PMacro136_Entry7_TimMin, PMacro136_Entry7_TimSec, PMacro136_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro136_Entry8_DelayMin, PMacro136_Entry8_DelaySec, PMacro136_Entry8_TimMin, PMacro136_Entry8_TimSec, PMacro136_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro136_Entry9_DelayMin, PMacro136_Entry9_DelaySec, PMacro136_Entry9_TimMin, PMacro136_Entry9_TimSec, PMacro136_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro136_Entry10_DelayMin, PMacro136_Entry10_DelaySec, PMacro136_Entry10_TimMin, PMacro136_Entry10_TimSec, PMacro136_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro136_Entry11_DelayMin, PMacro136_Entry11_DelaySec, PMacro136_Entry11_TimMin, PMacro136_Entry11_TimSec, PMacro136_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro136_Entry12_DelayMin, PMacro136_Entry12_DelaySec, PMacro136_Entry12_TimMin, PMacro136_Entry12_TimSec, PMacro136_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro136_Entry13_DelayMin, PMacro136_Entry13_DelaySec, PMacro136_Entry13_TimMin, PMacro136_Entry13_TimSec, PMacro136_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro136_Entry14_DelayMin, PMacro136_Entry14_DelaySec, PMacro136_Entry14_TimMin, PMacro136_Entry14_TimSec, PMacro136_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro136_Entry15_DelayMin, PMacro136_Entry15_DelaySec, PMacro136_Entry15_TimMin, PMacro136_Entry15_TimSec, PMacro136_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR136_STRING};

const struct super_macro Macro137 = {PMacro137_NumEntries,
		         PMacro137_Entry1_DelayMin, PMacro137_Entry1_DelaySec, PMacro137_Entry1_TimMin, PMacro137_Entry1_TimSec, PMacro137_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro137_Entry2_DelayMin, PMacro137_Entry2_DelaySec, PMacro137_Entry2_TimMin, PMacro137_Entry2_TimSec, PMacro137_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro137_Entry3_DelayMin, PMacro137_Entry3_DelaySec, PMacro137_Entry3_TimMin, PMacro137_Entry3_TimSec, PMacro137_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro137_Entry4_DelayMin, PMacro137_Entry4_DelaySec, PMacro137_Entry4_TimMin, PMacro137_Entry4_TimSec, PMacro137_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro137_Entry5_DelayMin, PMacro137_Entry5_DelaySec, PMacro137_Entry5_TimMin, PMacro137_Entry5_TimSec, PMacro137_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro137_Entry6_DelayMin, PMacro137_Entry6_DelaySec, PMacro137_Entry6_TimMin, PMacro137_Entry6_TimSec, PMacro137_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro137_Entry7_DelayMin, PMacro137_Entry7_DelaySec, PMacro137_Entry7_TimMin, PMacro137_Entry7_TimSec, PMacro137_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro137_Entry8_DelayMin, PMacro137_Entry8_DelaySec, PMacro137_Entry8_TimMin, PMacro137_Entry8_TimSec, PMacro137_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro137_Entry9_DelayMin, PMacro137_Entry9_DelaySec, PMacro137_Entry9_TimMin, PMacro137_Entry9_TimSec, PMacro137_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro137_Entry10_DelayMin, PMacro137_Entry10_DelaySec, PMacro137_Entry10_TimMin, PMacro137_Entry10_TimSec, PMacro137_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro137_Entry11_DelayMin, PMacro137_Entry11_DelaySec, PMacro137_Entry11_TimMin, PMacro137_Entry11_TimSec, PMacro137_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro137_Entry12_DelayMin, PMacro137_Entry12_DelaySec, PMacro137_Entry12_TimMin, PMacro137_Entry12_TimSec, PMacro137_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro137_Entry13_DelayMin, PMacro137_Entry13_DelaySec, PMacro137_Entry13_TimMin, PMacro137_Entry13_TimSec, PMacro137_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro137_Entry14_DelayMin, PMacro137_Entry14_DelaySec, PMacro137_Entry14_TimMin, PMacro137_Entry14_TimSec, PMacro137_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro137_Entry15_DelayMin, PMacro137_Entry15_DelaySec, PMacro137_Entry15_TimMin, PMacro137_Entry15_TimSec, PMacro137_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR137_STRING};

const struct super_macro Macro138 = {PMacro138_NumEntries,
		         PMacro138_Entry1_DelayMin, PMacro138_Entry1_DelaySec, PMacro138_Entry1_TimMin, PMacro138_Entry1_TimSec, PMacro138_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro138_Entry2_DelayMin, PMacro138_Entry2_DelaySec, PMacro138_Entry2_TimMin, PMacro138_Entry2_TimSec, PMacro138_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro138_Entry3_DelayMin, PMacro138_Entry3_DelaySec, PMacro138_Entry3_TimMin, PMacro138_Entry3_TimSec, PMacro138_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro138_Entry4_DelayMin, PMacro138_Entry4_DelaySec, PMacro138_Entry4_TimMin, PMacro138_Entry4_TimSec, PMacro138_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro138_Entry5_DelayMin, PMacro138_Entry5_DelaySec, PMacro138_Entry5_TimMin, PMacro138_Entry5_TimSec, PMacro138_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro138_Entry6_DelayMin, PMacro138_Entry6_DelaySec, PMacro138_Entry6_TimMin, PMacro138_Entry6_TimSec, PMacro138_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro138_Entry7_DelayMin, PMacro138_Entry7_DelaySec, PMacro138_Entry7_TimMin, PMacro138_Entry7_TimSec, PMacro138_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro138_Entry8_DelayMin, PMacro138_Entry8_DelaySec, PMacro138_Entry8_TimMin, PMacro138_Entry8_TimSec, PMacro138_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro138_Entry9_DelayMin, PMacro138_Entry9_DelaySec, PMacro138_Entry9_TimMin, PMacro138_Entry9_TimSec, PMacro138_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro138_Entry10_DelayMin, PMacro138_Entry10_DelaySec, PMacro138_Entry10_TimMin, PMacro138_Entry10_TimSec, PMacro138_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro138_Entry11_DelayMin, PMacro138_Entry11_DelaySec, PMacro138_Entry11_TimMin, PMacro138_Entry11_TimSec, PMacro138_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro138_Entry12_DelayMin, PMacro138_Entry12_DelaySec, PMacro138_Entry12_TimMin, PMacro138_Entry12_TimSec, PMacro138_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro138_Entry13_DelayMin, PMacro138_Entry13_DelaySec, PMacro138_Entry13_TimMin, PMacro138_Entry13_TimSec, PMacro138_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro138_Entry14_DelayMin, PMacro138_Entry14_DelaySec, PMacro138_Entry14_TimMin, PMacro138_Entry14_TimSec, PMacro138_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro138_Entry15_DelayMin, PMacro138_Entry15_DelaySec, PMacro138_Entry15_TimMin, PMacro138_Entry15_TimSec, PMacro138_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR138_STRING};

const struct super_macro Macro139 = {PMacro139_NumEntries,
		         PMacro139_Entry1_DelayMin, PMacro139_Entry1_DelaySec, PMacro139_Entry1_TimMin, PMacro139_Entry1_TimSec, PMacro139_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro139_Entry2_DelayMin, PMacro139_Entry2_DelaySec, PMacro139_Entry2_TimMin, PMacro139_Entry2_TimSec, PMacro139_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro139_Entry3_DelayMin, PMacro139_Entry3_DelaySec, PMacro139_Entry3_TimMin, PMacro139_Entry3_TimSec, PMacro139_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro139_Entry4_DelayMin, PMacro139_Entry4_DelaySec, PMacro139_Entry4_TimMin, PMacro139_Entry4_TimSec, PMacro139_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro139_Entry5_DelayMin, PMacro139_Entry5_DelaySec, PMacro139_Entry5_TimMin, PMacro139_Entry5_TimSec, PMacro139_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro139_Entry6_DelayMin, PMacro139_Entry6_DelaySec, PMacro139_Entry6_TimMin, PMacro139_Entry6_TimSec, PMacro139_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro139_Entry7_DelayMin, PMacro139_Entry7_DelaySec, PMacro139_Entry7_TimMin, PMacro139_Entry7_TimSec, PMacro139_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro139_Entry8_DelayMin, PMacro139_Entry8_DelaySec, PMacro139_Entry8_TimMin, PMacro139_Entry8_TimSec, PMacro139_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro139_Entry9_DelayMin, PMacro139_Entry9_DelaySec, PMacro139_Entry9_TimMin, PMacro139_Entry9_TimSec, PMacro139_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro139_Entry10_DelayMin, PMacro139_Entry10_DelaySec, PMacro139_Entry10_TimMin, PMacro139_Entry10_TimSec, PMacro139_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro139_Entry11_DelayMin, PMacro139_Entry11_DelaySec, PMacro139_Entry11_TimMin, PMacro139_Entry11_TimSec, PMacro139_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro139_Entry12_DelayMin, PMacro139_Entry12_DelaySec, PMacro139_Entry12_TimMin, PMacro139_Entry12_TimSec, PMacro139_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro139_Entry13_DelayMin, PMacro139_Entry13_DelaySec, PMacro139_Entry13_TimMin, PMacro139_Entry13_TimSec, PMacro139_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro139_Entry14_DelayMin, PMacro139_Entry14_DelaySec, PMacro139_Entry14_TimMin, PMacro139_Entry14_TimSec, PMacro139_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro139_Entry15_DelayMin, PMacro139_Entry15_DelaySec, PMacro139_Entry15_TimMin, PMacro139_Entry15_TimSec, PMacro139_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR139_STRING};

const struct super_macro Macro140 = {PMacro140_NumEntries,
		         PMacro140_Entry1_DelayMin, PMacro140_Entry1_DelaySec, PMacro140_Entry1_TimMin, PMacro140_Entry1_TimSec, PMacro140_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro140_Entry2_DelayMin, PMacro140_Entry2_DelaySec, PMacro140_Entry2_TimMin, PMacro140_Entry2_TimSec, PMacro140_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro140_Entry3_DelayMin, PMacro140_Entry3_DelaySec, PMacro140_Entry3_TimMin, PMacro140_Entry3_TimSec, PMacro140_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro140_Entry4_DelayMin, PMacro140_Entry4_DelaySec, PMacro140_Entry4_TimMin, PMacro140_Entry4_TimSec, PMacro140_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro140_Entry5_DelayMin, PMacro140_Entry5_DelaySec, PMacro140_Entry5_TimMin, PMacro140_Entry5_TimSec, PMacro140_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro140_Entry6_DelayMin, PMacro140_Entry6_DelaySec, PMacro140_Entry6_TimMin, PMacro140_Entry6_TimSec, PMacro140_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro140_Entry7_DelayMin, PMacro140_Entry7_DelaySec, PMacro140_Entry7_TimMin, PMacro140_Entry7_TimSec, PMacro140_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro140_Entry8_DelayMin, PMacro140_Entry8_DelaySec, PMacro140_Entry8_TimMin, PMacro140_Entry8_TimSec, PMacro140_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro140_Entry9_DelayMin, PMacro140_Entry9_DelaySec, PMacro140_Entry9_TimMin, PMacro140_Entry9_TimSec, PMacro140_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro140_Entry10_DelayMin, PMacro140_Entry10_DelaySec, PMacro140_Entry10_TimMin, PMacro140_Entry10_TimSec, PMacro140_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro140_Entry11_DelayMin, PMacro140_Entry11_DelaySec, PMacro140_Entry11_TimMin, PMacro140_Entry11_TimSec, PMacro140_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro140_Entry12_DelayMin, PMacro140_Entry12_DelaySec, PMacro140_Entry12_TimMin, PMacro140_Entry12_TimSec, PMacro140_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro140_Entry13_DelayMin, PMacro140_Entry13_DelaySec, PMacro140_Entry13_TimMin, PMacro140_Entry13_TimSec, PMacro140_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro140_Entry14_DelayMin, PMacro140_Entry14_DelaySec, PMacro140_Entry14_TimMin, PMacro140_Entry14_TimSec, PMacro140_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro140_Entry15_DelayMin, PMacro140_Entry15_DelaySec, PMacro140_Entry15_TimMin, PMacro140_Entry15_TimSec, PMacro140_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR140_STRING};

const struct super_macro Macro141 = {PMacro141_NumEntries,
		         PMacro141_Entry1_DelayMin, PMacro141_Entry1_DelaySec, PMacro141_Entry1_TimMin, PMacro141_Entry1_TimSec, PMacro141_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro141_Entry2_DelayMin, PMacro141_Entry2_DelaySec, PMacro141_Entry2_TimMin, PMacro141_Entry2_TimSec, PMacro141_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro141_Entry3_DelayMin, PMacro141_Entry3_DelaySec, PMacro141_Entry3_TimMin, PMacro141_Entry3_TimSec, PMacro141_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro141_Entry4_DelayMin, PMacro141_Entry4_DelaySec, PMacro141_Entry4_TimMin, PMacro141_Entry4_TimSec, PMacro141_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro141_Entry5_DelayMin, PMacro141_Entry5_DelaySec, PMacro141_Entry5_TimMin, PMacro141_Entry5_TimSec, PMacro141_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro141_Entry6_DelayMin, PMacro141_Entry6_DelaySec, PMacro141_Entry6_TimMin, PMacro141_Entry6_TimSec, PMacro141_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro141_Entry7_DelayMin, PMacro141_Entry7_DelaySec, PMacro141_Entry7_TimMin, PMacro141_Entry7_TimSec, PMacro141_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro141_Entry8_DelayMin, PMacro141_Entry8_DelaySec, PMacro141_Entry8_TimMin, PMacro141_Entry8_TimSec, PMacro141_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro141_Entry9_DelayMin, PMacro141_Entry9_DelaySec, PMacro141_Entry9_TimMin, PMacro141_Entry9_TimSec, PMacro141_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro141_Entry10_DelayMin, PMacro141_Entry10_DelaySec, PMacro141_Entry10_TimMin, PMacro141_Entry10_TimSec, PMacro141_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro141_Entry11_DelayMin, PMacro141_Entry11_DelaySec, PMacro141_Entry11_TimMin, PMacro141_Entry11_TimSec, PMacro141_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro141_Entry12_DelayMin, PMacro141_Entry12_DelaySec, PMacro141_Entry12_TimMin, PMacro141_Entry12_TimSec, PMacro141_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro141_Entry13_DelayMin, PMacro141_Entry13_DelaySec, PMacro141_Entry13_TimMin, PMacro141_Entry13_TimSec, PMacro141_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro141_Entry14_DelayMin, PMacro141_Entry14_DelaySec, PMacro141_Entry14_TimMin, PMacro141_Entry14_TimSec, PMacro141_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro141_Entry15_DelayMin, PMacro141_Entry15_DelaySec, PMacro141_Entry15_TimMin, PMacro141_Entry15_TimSec, PMacro141_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR141_STRING};

const struct super_macro Macro142 = {PMacro142_NumEntries,
		         PMacro142_Entry1_DelayMin, PMacro142_Entry1_DelaySec, PMacro142_Entry1_TimMin, PMacro142_Entry1_TimSec, PMacro142_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro142_Entry2_DelayMin, PMacro142_Entry2_DelaySec, PMacro142_Entry2_TimMin, PMacro142_Entry2_TimSec, PMacro142_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro142_Entry3_DelayMin, PMacro142_Entry3_DelaySec, PMacro142_Entry3_TimMin, PMacro142_Entry3_TimSec, PMacro142_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro142_Entry4_DelayMin, PMacro142_Entry4_DelaySec, PMacro142_Entry4_TimMin, PMacro142_Entry4_TimSec, PMacro142_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro142_Entry5_DelayMin, PMacro142_Entry5_DelaySec, PMacro142_Entry5_TimMin, PMacro142_Entry5_TimSec, PMacro142_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro142_Entry6_DelayMin, PMacro142_Entry6_DelaySec, PMacro142_Entry6_TimMin, PMacro142_Entry6_TimSec, PMacro142_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro142_Entry7_DelayMin, PMacro142_Entry7_DelaySec, PMacro142_Entry7_TimMin, PMacro142_Entry7_TimSec, PMacro142_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro142_Entry8_DelayMin, PMacro142_Entry8_DelaySec, PMacro142_Entry8_TimMin, PMacro142_Entry8_TimSec, PMacro142_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro142_Entry9_DelayMin, PMacro142_Entry9_DelaySec, PMacro142_Entry9_TimMin, PMacro142_Entry9_TimSec, PMacro142_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro142_Entry10_DelayMin, PMacro142_Entry10_DelaySec, PMacro142_Entry10_TimMin, PMacro142_Entry10_TimSec, PMacro142_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro142_Entry11_DelayMin, PMacro142_Entry11_DelaySec, PMacro142_Entry11_TimMin, PMacro142_Entry11_TimSec, PMacro142_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro142_Entry12_DelayMin, PMacro142_Entry12_DelaySec, PMacro142_Entry12_TimMin, PMacro142_Entry12_TimSec, PMacro142_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro142_Entry13_DelayMin, PMacro142_Entry13_DelaySec, PMacro142_Entry13_TimMin, PMacro142_Entry13_TimSec, PMacro142_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro142_Entry14_DelayMin, PMacro142_Entry14_DelaySec, PMacro142_Entry14_TimMin, PMacro142_Entry14_TimSec, PMacro142_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro142_Entry15_DelayMin, PMacro142_Entry15_DelaySec, PMacro142_Entry15_TimMin, PMacro142_Entry15_TimSec, PMacro142_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR142_STRING};

const struct super_macro Macro143 = {PMacro143_NumEntries,
		         PMacro143_Entry1_DelayMin, PMacro143_Entry1_DelaySec, PMacro143_Entry1_TimMin, PMacro143_Entry1_TimSec, PMacro143_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro143_Entry2_DelayMin, PMacro143_Entry2_DelaySec, PMacro143_Entry2_TimMin, PMacro143_Entry2_TimSec, PMacro143_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro143_Entry3_DelayMin, PMacro143_Entry3_DelaySec, PMacro143_Entry3_TimMin, PMacro143_Entry3_TimSec, PMacro143_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro143_Entry4_DelayMin, PMacro143_Entry4_DelaySec, PMacro143_Entry4_TimMin, PMacro143_Entry4_TimSec, PMacro143_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro143_Entry5_DelayMin, PMacro143_Entry5_DelaySec, PMacro143_Entry5_TimMin, PMacro143_Entry5_TimSec, PMacro143_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro143_Entry6_DelayMin, PMacro143_Entry6_DelaySec, PMacro143_Entry6_TimMin, PMacro143_Entry6_TimSec, PMacro143_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro143_Entry7_DelayMin, PMacro143_Entry7_DelaySec, PMacro143_Entry7_TimMin, PMacro143_Entry7_TimSec, PMacro143_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro143_Entry8_DelayMin, PMacro143_Entry8_DelaySec, PMacro143_Entry8_TimMin, PMacro143_Entry8_TimSec, PMacro143_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro143_Entry9_DelayMin, PMacro143_Entry9_DelaySec, PMacro143_Entry9_TimMin, PMacro143_Entry9_TimSec, PMacro143_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro143_Entry10_DelayMin, PMacro143_Entry10_DelaySec, PMacro143_Entry10_TimMin, PMacro143_Entry10_TimSec, PMacro143_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro143_Entry11_DelayMin, PMacro143_Entry11_DelaySec, PMacro143_Entry11_TimMin, PMacro143_Entry11_TimSec, PMacro143_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro143_Entry12_DelayMin, PMacro143_Entry12_DelaySec, PMacro143_Entry12_TimMin, PMacro143_Entry12_TimSec, PMacro143_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro143_Entry13_DelayMin, PMacro143_Entry13_DelaySec, PMacro143_Entry13_TimMin, PMacro143_Entry13_TimSec, PMacro143_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro143_Entry14_DelayMin, PMacro143_Entry14_DelaySec, PMacro143_Entry14_TimMin, PMacro143_Entry14_TimSec, PMacro143_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro143_Entry15_DelayMin, PMacro143_Entry15_DelaySec, PMacro143_Entry15_TimMin, PMacro143_Entry15_TimSec, PMacro143_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR143_STRING};

const struct super_macro Macro144 = {PMacro144_NumEntries,
		         PMacro144_Entry1_DelayMin, PMacro144_Entry1_DelaySec, PMacro144_Entry1_TimMin, PMacro144_Entry1_TimSec, PMacro144_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro144_Entry2_DelayMin, PMacro144_Entry2_DelaySec, PMacro144_Entry2_TimMin, PMacro144_Entry2_TimSec, PMacro144_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro144_Entry3_DelayMin, PMacro144_Entry3_DelaySec, PMacro144_Entry3_TimMin, PMacro144_Entry3_TimSec, PMacro144_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro144_Entry4_DelayMin, PMacro144_Entry4_DelaySec, PMacro144_Entry4_TimMin, PMacro144_Entry4_TimSec, PMacro144_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro144_Entry5_DelayMin, PMacro144_Entry5_DelaySec, PMacro144_Entry5_TimMin, PMacro144_Entry5_TimSec, PMacro144_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro144_Entry6_DelayMin, PMacro144_Entry6_DelaySec, PMacro144_Entry6_TimMin, PMacro144_Entry6_TimSec, PMacro144_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro144_Entry7_DelayMin, PMacro144_Entry7_DelaySec, PMacro144_Entry7_TimMin, PMacro144_Entry7_TimSec, PMacro144_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro144_Entry8_DelayMin, PMacro144_Entry8_DelaySec, PMacro144_Entry8_TimMin, PMacro144_Entry8_TimSec, PMacro144_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro144_Entry9_DelayMin, PMacro144_Entry9_DelaySec, PMacro144_Entry9_TimMin, PMacro144_Entry9_TimSec, PMacro144_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro144_Entry10_DelayMin, PMacro144_Entry10_DelaySec, PMacro144_Entry10_TimMin, PMacro144_Entry10_TimSec, PMacro144_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro144_Entry11_DelayMin, PMacro144_Entry11_DelaySec, PMacro144_Entry11_TimMin, PMacro144_Entry11_TimSec, PMacro144_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro144_Entry12_DelayMin, PMacro144_Entry12_DelaySec, PMacro144_Entry12_TimMin, PMacro144_Entry12_TimSec, PMacro144_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro144_Entry13_DelayMin, PMacro144_Entry13_DelaySec, PMacro144_Entry13_TimMin, PMacro144_Entry13_TimSec, PMacro144_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro144_Entry14_DelayMin, PMacro144_Entry14_DelaySec, PMacro144_Entry14_TimMin, PMacro144_Entry14_TimSec, PMacro144_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro144_Entry15_DelayMin, PMacro144_Entry15_DelaySec, PMacro144_Entry15_TimMin, PMacro144_Entry15_TimSec, PMacro144_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR144_STRING};

const struct super_macro Macro145 = {PMacro145_NumEntries,
		         PMacro145_Entry1_DelayMin, PMacro145_Entry1_DelaySec, PMacro145_Entry1_TimMin, PMacro145_Entry1_TimSec, PMacro145_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro145_Entry2_DelayMin, PMacro145_Entry2_DelaySec, PMacro145_Entry2_TimMin, PMacro145_Entry2_TimSec, PMacro145_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro145_Entry3_DelayMin, PMacro145_Entry3_DelaySec, PMacro145_Entry3_TimMin, PMacro145_Entry3_TimSec, PMacro145_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro145_Entry4_DelayMin, PMacro145_Entry4_DelaySec, PMacro145_Entry4_TimMin, PMacro145_Entry4_TimSec, PMacro145_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro145_Entry5_DelayMin, PMacro145_Entry5_DelaySec, PMacro145_Entry5_TimMin, PMacro145_Entry5_TimSec, PMacro145_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro145_Entry6_DelayMin, PMacro145_Entry6_DelaySec, PMacro145_Entry6_TimMin, PMacro145_Entry6_TimSec, PMacro145_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro145_Entry7_DelayMin, PMacro145_Entry7_DelaySec, PMacro145_Entry7_TimMin, PMacro145_Entry7_TimSec, PMacro145_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro145_Entry8_DelayMin, PMacro145_Entry8_DelaySec, PMacro145_Entry8_TimMin, PMacro145_Entry8_TimSec, PMacro145_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro145_Entry9_DelayMin, PMacro145_Entry9_DelaySec, PMacro145_Entry9_TimMin, PMacro145_Entry9_TimSec, PMacro145_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro145_Entry10_DelayMin, PMacro145_Entry10_DelaySec, PMacro145_Entry10_TimMin, PMacro145_Entry10_TimSec, PMacro145_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro145_Entry11_DelayMin, PMacro145_Entry11_DelaySec, PMacro145_Entry11_TimMin, PMacro145_Entry11_TimSec, PMacro145_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro145_Entry12_DelayMin, PMacro145_Entry12_DelaySec, PMacro145_Entry12_TimMin, PMacro145_Entry12_TimSec, PMacro145_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro145_Entry13_DelayMin, PMacro145_Entry13_DelaySec, PMacro145_Entry13_TimMin, PMacro145_Entry13_TimSec, PMacro145_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro145_Entry14_DelayMin, PMacro145_Entry14_DelaySec, PMacro145_Entry14_TimMin, PMacro145_Entry14_TimSec, PMacro145_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro145_Entry15_DelayMin, PMacro145_Entry15_DelaySec, PMacro145_Entry15_TimMin, PMacro145_Entry15_TimSec, PMacro145_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR145_STRING};

const struct super_macro Macro146 = {PMacro146_NumEntries,
		         PMacro146_Entry1_DelayMin, PMacro146_Entry1_DelaySec, PMacro146_Entry1_TimMin, PMacro146_Entry1_TimSec, PMacro146_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro146_Entry2_DelayMin, PMacro146_Entry2_DelaySec, PMacro146_Entry2_TimMin, PMacro146_Entry2_TimSec, PMacro146_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro146_Entry3_DelayMin, PMacro146_Entry3_DelaySec, PMacro146_Entry3_TimMin, PMacro146_Entry3_TimSec, PMacro146_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro146_Entry4_DelayMin, PMacro146_Entry4_DelaySec, PMacro146_Entry4_TimMin, PMacro146_Entry4_TimSec, PMacro146_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro146_Entry5_DelayMin, PMacro146_Entry5_DelaySec, PMacro146_Entry5_TimMin, PMacro146_Entry5_TimSec, PMacro146_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro146_Entry6_DelayMin, PMacro146_Entry6_DelaySec, PMacro146_Entry6_TimMin, PMacro146_Entry6_TimSec, PMacro146_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro146_Entry7_DelayMin, PMacro146_Entry7_DelaySec, PMacro146_Entry7_TimMin, PMacro146_Entry7_TimSec, PMacro146_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro146_Entry8_DelayMin, PMacro146_Entry8_DelaySec, PMacro146_Entry8_TimMin, PMacro146_Entry8_TimSec, PMacro146_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro146_Entry9_DelayMin, PMacro146_Entry9_DelaySec, PMacro146_Entry9_TimMin, PMacro146_Entry9_TimSec, PMacro146_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro146_Entry10_DelayMin, PMacro146_Entry10_DelaySec, PMacro146_Entry10_TimMin, PMacro146_Entry10_TimSec, PMacro146_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro146_Entry11_DelayMin, PMacro146_Entry11_DelaySec, PMacro146_Entry11_TimMin, PMacro146_Entry11_TimSec, PMacro146_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro146_Entry12_DelayMin, PMacro146_Entry12_DelaySec, PMacro146_Entry12_TimMin, PMacro146_Entry12_TimSec, PMacro146_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro146_Entry13_DelayMin, PMacro146_Entry13_DelaySec, PMacro146_Entry13_TimMin, PMacro146_Entry13_TimSec, PMacro146_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro146_Entry14_DelayMin, PMacro146_Entry14_DelaySec, PMacro146_Entry14_TimMin, PMacro146_Entry14_TimSec, PMacro146_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro146_Entry15_DelayMin, PMacro146_Entry15_DelaySec, PMacro146_Entry15_TimMin, PMacro146_Entry15_TimSec, PMacro146_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR146_STRING};

const struct super_macro Macro147 = {PMacro147_NumEntries,
		         PMacro147_Entry1_DelayMin, PMacro147_Entry1_DelaySec, PMacro147_Entry1_TimMin, PMacro147_Entry1_TimSec, PMacro147_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro147_Entry2_DelayMin, PMacro147_Entry2_DelaySec, PMacro147_Entry2_TimMin, PMacro147_Entry2_TimSec, PMacro147_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro147_Entry3_DelayMin, PMacro147_Entry3_DelaySec, PMacro147_Entry3_TimMin, PMacro147_Entry3_TimSec, PMacro147_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro147_Entry4_DelayMin, PMacro147_Entry4_DelaySec, PMacro147_Entry4_TimMin, PMacro147_Entry4_TimSec, PMacro147_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro147_Entry5_DelayMin, PMacro147_Entry5_DelaySec, PMacro147_Entry5_TimMin, PMacro147_Entry5_TimSec, PMacro147_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro147_Entry6_DelayMin, PMacro147_Entry6_DelaySec, PMacro147_Entry6_TimMin, PMacro147_Entry6_TimSec, PMacro147_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro147_Entry7_DelayMin, PMacro147_Entry7_DelaySec, PMacro147_Entry7_TimMin, PMacro147_Entry7_TimSec, PMacro147_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro147_Entry8_DelayMin, PMacro147_Entry8_DelaySec, PMacro147_Entry8_TimMin, PMacro147_Entry8_TimSec, PMacro147_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro147_Entry9_DelayMin, PMacro147_Entry9_DelaySec, PMacro147_Entry9_TimMin, PMacro147_Entry9_TimSec, PMacro147_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro147_Entry10_DelayMin, PMacro147_Entry10_DelaySec, PMacro147_Entry10_TimMin, PMacro147_Entry10_TimSec, PMacro147_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro147_Entry11_DelayMin, PMacro147_Entry11_DelaySec, PMacro147_Entry11_TimMin, PMacro147_Entry11_TimSec, PMacro147_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro147_Entry12_DelayMin, PMacro147_Entry12_DelaySec, PMacro147_Entry12_TimMin, PMacro147_Entry12_TimSec, PMacro147_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro147_Entry13_DelayMin, PMacro147_Entry13_DelaySec, PMacro147_Entry13_TimMin, PMacro147_Entry13_TimSec, PMacro147_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro147_Entry14_DelayMin, PMacro147_Entry14_DelaySec, PMacro147_Entry14_TimMin, PMacro147_Entry14_TimSec, PMacro147_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro147_Entry15_DelayMin, PMacro147_Entry15_DelaySec, PMacro147_Entry15_TimMin, PMacro147_Entry15_TimSec, PMacro147_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR147_STRING};

const struct super_macro Macro148 = {PMacro148_NumEntries,
		         PMacro148_Entry1_DelayMin, PMacro148_Entry1_DelaySec, PMacro148_Entry1_TimMin, PMacro148_Entry1_TimSec, PMacro148_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro148_Entry2_DelayMin, PMacro148_Entry2_DelaySec, PMacro148_Entry2_TimMin, PMacro148_Entry2_TimSec, PMacro148_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro148_Entry3_DelayMin, PMacro148_Entry3_DelaySec, PMacro148_Entry3_TimMin, PMacro148_Entry3_TimSec, PMacro148_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro148_Entry4_DelayMin, PMacro148_Entry4_DelaySec, PMacro148_Entry4_TimMin, PMacro148_Entry4_TimSec, PMacro148_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro148_Entry5_DelayMin, PMacro148_Entry5_DelaySec, PMacro148_Entry5_TimMin, PMacro148_Entry5_TimSec, PMacro148_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro148_Entry6_DelayMin, PMacro148_Entry6_DelaySec, PMacro148_Entry6_TimMin, PMacro148_Entry6_TimSec, PMacro148_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro148_Entry7_DelayMin, PMacro148_Entry7_DelaySec, PMacro148_Entry7_TimMin, PMacro148_Entry7_TimSec, PMacro148_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro148_Entry8_DelayMin, PMacro148_Entry8_DelaySec, PMacro148_Entry8_TimMin, PMacro148_Entry8_TimSec, PMacro148_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro148_Entry9_DelayMin, PMacro148_Entry9_DelaySec, PMacro148_Entry9_TimMin, PMacro148_Entry9_TimSec, PMacro148_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro148_Entry10_DelayMin, PMacro148_Entry10_DelaySec, PMacro148_Entry10_TimMin, PMacro148_Entry10_TimSec, PMacro148_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro148_Entry11_DelayMin, PMacro148_Entry11_DelaySec, PMacro148_Entry11_TimMin, PMacro148_Entry11_TimSec, PMacro148_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro148_Entry12_DelayMin, PMacro148_Entry12_DelaySec, PMacro148_Entry12_TimMin, PMacro148_Entry12_TimSec, PMacro148_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro148_Entry13_DelayMin, PMacro148_Entry13_DelaySec, PMacro148_Entry13_TimMin, PMacro148_Entry13_TimSec, PMacro148_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro148_Entry14_DelayMin, PMacro148_Entry14_DelaySec, PMacro148_Entry14_TimMin, PMacro148_Entry14_TimSec, PMacro148_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro148_Entry15_DelayMin, PMacro148_Entry15_DelaySec, PMacro148_Entry15_TimMin, PMacro148_Entry15_TimSec, PMacro148_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR148_STRING};

const struct super_macro Macro149 = {PMacro149_NumEntries,
		         PMacro149_Entry1_DelayMin, PMacro149_Entry1_DelaySec, PMacro149_Entry1_TimMin, PMacro149_Entry1_TimSec, PMacro149_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro149_Entry2_DelayMin, PMacro149_Entry2_DelaySec, PMacro149_Entry2_TimMin, PMacro149_Entry2_TimSec, PMacro149_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro149_Entry3_DelayMin, PMacro149_Entry3_DelaySec, PMacro149_Entry3_TimMin, PMacro149_Entry3_TimSec, PMacro149_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro149_Entry4_DelayMin, PMacro149_Entry4_DelaySec, PMacro149_Entry4_TimMin, PMacro149_Entry4_TimSec, PMacro149_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro149_Entry5_DelayMin, PMacro149_Entry5_DelaySec, PMacro149_Entry5_TimMin, PMacro149_Entry5_TimSec, PMacro149_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro149_Entry6_DelayMin, PMacro149_Entry6_DelaySec, PMacro149_Entry6_TimMin, PMacro149_Entry6_TimSec, PMacro149_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro149_Entry7_DelayMin, PMacro149_Entry7_DelaySec, PMacro149_Entry7_TimMin, PMacro149_Entry7_TimSec, PMacro149_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro149_Entry8_DelayMin, PMacro149_Entry8_DelaySec, PMacro149_Entry8_TimMin, PMacro149_Entry8_TimSec, PMacro149_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro149_Entry9_DelayMin, PMacro149_Entry9_DelaySec, PMacro149_Entry9_TimMin, PMacro149_Entry9_TimSec, PMacro149_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro149_Entry10_DelayMin, PMacro149_Entry10_DelaySec, PMacro149_Entry10_TimMin, PMacro149_Entry10_TimSec, PMacro149_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro149_Entry11_DelayMin, PMacro149_Entry11_DelaySec, PMacro149_Entry11_TimMin, PMacro149_Entry11_TimSec, PMacro149_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro149_Entry12_DelayMin, PMacro149_Entry12_DelaySec, PMacro149_Entry12_TimMin, PMacro149_Entry12_TimSec, PMacro149_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro149_Entry13_DelayMin, PMacro149_Entry13_DelaySec, PMacro149_Entry13_TimMin, PMacro149_Entry13_TimSec, PMacro149_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro149_Entry14_DelayMin, PMacro149_Entry14_DelaySec, PMacro149_Entry14_TimMin, PMacro149_Entry14_TimSec, PMacro149_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro149_Entry15_DelayMin, PMacro149_Entry15_DelaySec, PMacro149_Entry15_TimMin, PMacro149_Entry15_TimSec, PMacro149_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR149_STRING};

const struct super_macro Macro150 = {PMacro150_NumEntries,
		         PMacro150_Entry1_DelayMin, PMacro150_Entry1_DelaySec, PMacro150_Entry1_TimMin, PMacro150_Entry1_TimSec, PMacro150_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro150_Entry2_DelayMin, PMacro150_Entry2_DelaySec, PMacro150_Entry2_TimMin, PMacro150_Entry2_TimSec, PMacro150_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro150_Entry3_DelayMin, PMacro150_Entry3_DelaySec, PMacro150_Entry3_TimMin, PMacro150_Entry3_TimSec, PMacro150_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro150_Entry4_DelayMin, PMacro150_Entry4_DelaySec, PMacro150_Entry4_TimMin, PMacro150_Entry4_TimSec, PMacro150_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro150_Entry5_DelayMin, PMacro150_Entry5_DelaySec, PMacro150_Entry5_TimMin, PMacro150_Entry5_TimSec, PMacro150_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro150_Entry6_DelayMin, PMacro150_Entry6_DelaySec, PMacro150_Entry6_TimMin, PMacro150_Entry6_TimSec, PMacro150_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro150_Entry7_DelayMin, PMacro150_Entry7_DelaySec, PMacro150_Entry7_TimMin, PMacro150_Entry7_TimSec, PMacro150_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro150_Entry8_DelayMin, PMacro150_Entry8_DelaySec, PMacro150_Entry8_TimMin, PMacro150_Entry8_TimSec, PMacro150_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro150_Entry9_DelayMin, PMacro150_Entry9_DelaySec, PMacro150_Entry9_TimMin, PMacro150_Entry9_TimSec, PMacro150_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro150_Entry10_DelayMin, PMacro150_Entry10_DelaySec, PMacro150_Entry10_TimMin, PMacro150_Entry10_TimSec, PMacro150_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro150_Entry11_DelayMin, PMacro150_Entry11_DelaySec, PMacro150_Entry11_TimMin, PMacro150_Entry11_TimSec, PMacro150_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro150_Entry12_DelayMin, PMacro150_Entry12_DelaySec, PMacro150_Entry12_TimMin, PMacro150_Entry12_TimSec, PMacro150_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro150_Entry13_DelayMin, PMacro150_Entry13_DelaySec, PMacro150_Entry13_TimMin, PMacro150_Entry13_TimSec, PMacro150_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro150_Entry14_DelayMin, PMacro150_Entry14_DelaySec, PMacro150_Entry14_TimMin, PMacro150_Entry14_TimSec, PMacro150_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro150_Entry15_DelayMin, PMacro150_Entry15_DelaySec, PMacro150_Entry15_TimMin, PMacro150_Entry15_TimSec, PMacro150_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR150_STRING};

const struct super_macro Macro151 = {PMacro151_NumEntries,
		         PMacro151_Entry1_DelayMin, PMacro151_Entry1_DelaySec, PMacro151_Entry1_TimMin, PMacro151_Entry1_TimSec, PMacro151_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro151_Entry2_DelayMin, PMacro151_Entry2_DelaySec, PMacro151_Entry2_TimMin, PMacro151_Entry2_TimSec, PMacro151_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro151_Entry3_DelayMin, PMacro151_Entry3_DelaySec, PMacro151_Entry3_TimMin, PMacro151_Entry3_TimSec, PMacro151_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro151_Entry4_DelayMin, PMacro151_Entry4_DelaySec, PMacro151_Entry4_TimMin, PMacro151_Entry4_TimSec, PMacro151_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro151_Entry5_DelayMin, PMacro151_Entry5_DelaySec, PMacro151_Entry5_TimMin, PMacro151_Entry5_TimSec, PMacro151_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro151_Entry6_DelayMin, PMacro151_Entry6_DelaySec, PMacro151_Entry6_TimMin, PMacro151_Entry6_TimSec, PMacro151_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro151_Entry7_DelayMin, PMacro151_Entry7_DelaySec, PMacro151_Entry7_TimMin, PMacro151_Entry7_TimSec, PMacro151_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro151_Entry8_DelayMin, PMacro151_Entry8_DelaySec, PMacro151_Entry8_TimMin, PMacro151_Entry8_TimSec, PMacro151_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro151_Entry9_DelayMin, PMacro151_Entry9_DelaySec, PMacro151_Entry9_TimMin, PMacro151_Entry9_TimSec, PMacro151_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro151_Entry10_DelayMin, PMacro151_Entry10_DelaySec, PMacro151_Entry10_TimMin, PMacro151_Entry10_TimSec, PMacro151_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro151_Entry11_DelayMin, PMacro151_Entry11_DelaySec, PMacro151_Entry11_TimMin, PMacro151_Entry11_TimSec, PMacro151_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro151_Entry12_DelayMin, PMacro151_Entry12_DelaySec, PMacro151_Entry12_TimMin, PMacro151_Entry12_TimSec, PMacro151_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro151_Entry13_DelayMin, PMacro151_Entry13_DelaySec, PMacro151_Entry13_TimMin, PMacro151_Entry13_TimSec, PMacro151_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro151_Entry14_DelayMin, PMacro151_Entry14_DelaySec, PMacro151_Entry14_TimMin, PMacro151_Entry14_TimSec, PMacro151_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro151_Entry15_DelayMin, PMacro151_Entry15_DelaySec, PMacro151_Entry15_TimMin, PMacro151_Entry15_TimSec, PMacro151_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR151_STRING};

const struct super_macro Macro152 = {PMacro152_NumEntries,
		         PMacro152_Entry1_DelayMin, PMacro152_Entry1_DelaySec, PMacro152_Entry1_TimMin, PMacro152_Entry1_TimSec, PMacro152_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro152_Entry2_DelayMin, PMacro152_Entry2_DelaySec, PMacro152_Entry2_TimMin, PMacro152_Entry2_TimSec, PMacro152_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro152_Entry3_DelayMin, PMacro152_Entry3_DelaySec, PMacro152_Entry3_TimMin, PMacro152_Entry3_TimSec, PMacro152_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro152_Entry4_DelayMin, PMacro152_Entry4_DelaySec, PMacro152_Entry4_TimMin, PMacro152_Entry4_TimSec, PMacro152_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro152_Entry5_DelayMin, PMacro152_Entry5_DelaySec, PMacro152_Entry5_TimMin, PMacro152_Entry5_TimSec, PMacro152_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro152_Entry6_DelayMin, PMacro152_Entry6_DelaySec, PMacro152_Entry6_TimMin, PMacro152_Entry6_TimSec, PMacro152_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro152_Entry7_DelayMin, PMacro152_Entry7_DelaySec, PMacro152_Entry7_TimMin, PMacro152_Entry7_TimSec, PMacro152_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro152_Entry8_DelayMin, PMacro152_Entry8_DelaySec, PMacro152_Entry8_TimMin, PMacro152_Entry8_TimSec, PMacro152_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro152_Entry9_DelayMin, PMacro152_Entry9_DelaySec, PMacro152_Entry9_TimMin, PMacro152_Entry9_TimSec, PMacro152_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro152_Entry10_DelayMin, PMacro152_Entry10_DelaySec, PMacro152_Entry10_TimMin, PMacro152_Entry10_TimSec, PMacro152_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro152_Entry11_DelayMin, PMacro152_Entry11_DelaySec, PMacro152_Entry11_TimMin, PMacro152_Entry11_TimSec, PMacro152_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro152_Entry12_DelayMin, PMacro152_Entry12_DelaySec, PMacro152_Entry12_TimMin, PMacro152_Entry12_TimSec, PMacro152_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro152_Entry13_DelayMin, PMacro152_Entry13_DelaySec, PMacro152_Entry13_TimMin, PMacro152_Entry13_TimSec, PMacro152_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro152_Entry14_DelayMin, PMacro152_Entry14_DelaySec, PMacro152_Entry14_TimMin, PMacro152_Entry14_TimSec, PMacro152_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro152_Entry15_DelayMin, PMacro152_Entry15_DelaySec, PMacro152_Entry15_TimMin, PMacro152_Entry15_TimSec, PMacro152_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR152_STRING};

const struct super_macro Macro153 = {PMacro153_NumEntries,
		         PMacro153_Entry1_DelayMin, PMacro153_Entry1_DelaySec, PMacro153_Entry1_TimMin, PMacro153_Entry1_TimSec, PMacro153_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro153_Entry2_DelayMin, PMacro153_Entry2_DelaySec, PMacro153_Entry2_TimMin, PMacro153_Entry2_TimSec, PMacro153_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro153_Entry3_DelayMin, PMacro153_Entry3_DelaySec, PMacro153_Entry3_TimMin, PMacro153_Entry3_TimSec, PMacro153_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro153_Entry4_DelayMin, PMacro153_Entry4_DelaySec, PMacro153_Entry4_TimMin, PMacro153_Entry4_TimSec, PMacro153_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro153_Entry5_DelayMin, PMacro153_Entry5_DelaySec, PMacro153_Entry5_TimMin, PMacro153_Entry5_TimSec, PMacro153_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro153_Entry6_DelayMin, PMacro153_Entry6_DelaySec, PMacro153_Entry6_TimMin, PMacro153_Entry6_TimSec, PMacro153_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro153_Entry7_DelayMin, PMacro153_Entry7_DelaySec, PMacro153_Entry7_TimMin, PMacro153_Entry7_TimSec, PMacro153_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro153_Entry8_DelayMin, PMacro153_Entry8_DelaySec, PMacro153_Entry8_TimMin, PMacro153_Entry8_TimSec, PMacro153_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro153_Entry9_DelayMin, PMacro153_Entry9_DelaySec, PMacro153_Entry9_TimMin, PMacro153_Entry9_TimSec, PMacro153_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro153_Entry10_DelayMin, PMacro153_Entry10_DelaySec, PMacro153_Entry10_TimMin, PMacro153_Entry10_TimSec, PMacro153_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro153_Entry11_DelayMin, PMacro153_Entry11_DelaySec, PMacro153_Entry11_TimMin, PMacro153_Entry11_TimSec, PMacro153_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro153_Entry12_DelayMin, PMacro153_Entry12_DelaySec, PMacro153_Entry12_TimMin, PMacro153_Entry12_TimSec, PMacro153_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro153_Entry13_DelayMin, PMacro153_Entry13_DelaySec, PMacro153_Entry13_TimMin, PMacro153_Entry13_TimSec, PMacro153_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro153_Entry14_DelayMin, PMacro153_Entry14_DelaySec, PMacro153_Entry14_TimMin, PMacro153_Entry14_TimSec, PMacro153_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro153_Entry15_DelayMin, PMacro153_Entry15_DelaySec, PMacro153_Entry15_TimMin, PMacro153_Entry15_TimSec, PMacro153_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR153_STRING};

const struct super_macro Macro154 = {PMacro154_NumEntries,
		         PMacro154_Entry1_DelayMin, PMacro154_Entry1_DelaySec, PMacro154_Entry1_TimMin, PMacro154_Entry1_TimSec, PMacro154_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro154_Entry2_DelayMin, PMacro154_Entry2_DelaySec, PMacro154_Entry2_TimMin, PMacro154_Entry2_TimSec, PMacro154_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro154_Entry3_DelayMin, PMacro154_Entry3_DelaySec, PMacro154_Entry3_TimMin, PMacro154_Entry3_TimSec, PMacro154_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro154_Entry4_DelayMin, PMacro154_Entry4_DelaySec, PMacro154_Entry4_TimMin, PMacro154_Entry4_TimSec, PMacro154_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro154_Entry5_DelayMin, PMacro154_Entry5_DelaySec, PMacro154_Entry5_TimMin, PMacro154_Entry5_TimSec, PMacro154_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro154_Entry6_DelayMin, PMacro154_Entry6_DelaySec, PMacro154_Entry6_TimMin, PMacro154_Entry6_TimSec, PMacro154_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro154_Entry7_DelayMin, PMacro154_Entry7_DelaySec, PMacro154_Entry7_TimMin, PMacro154_Entry7_TimSec, PMacro154_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro154_Entry8_DelayMin, PMacro154_Entry8_DelaySec, PMacro154_Entry8_TimMin, PMacro154_Entry8_TimSec, PMacro154_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro154_Entry9_DelayMin, PMacro154_Entry9_DelaySec, PMacro154_Entry9_TimMin, PMacro154_Entry9_TimSec, PMacro154_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro154_Entry10_DelayMin, PMacro154_Entry10_DelaySec, PMacro154_Entry10_TimMin, PMacro154_Entry10_TimSec, PMacro154_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro154_Entry11_DelayMin, PMacro154_Entry11_DelaySec, PMacro154_Entry11_TimMin, PMacro154_Entry11_TimSec, PMacro154_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro154_Entry12_DelayMin, PMacro154_Entry12_DelaySec, PMacro154_Entry12_TimMin, PMacro154_Entry12_TimSec, PMacro154_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro154_Entry13_DelayMin, PMacro154_Entry13_DelaySec, PMacro154_Entry13_TimMin, PMacro154_Entry13_TimSec, PMacro154_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro154_Entry14_DelayMin, PMacro154_Entry14_DelaySec, PMacro154_Entry14_TimMin, PMacro154_Entry14_TimSec, PMacro154_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro154_Entry15_DelayMin, PMacro154_Entry15_DelaySec, PMacro154_Entry15_TimMin, PMacro154_Entry15_TimSec, PMacro154_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR154_STRING};

const struct super_macro Macro155 = {PMacro155_NumEntries,
		         PMacro155_Entry1_DelayMin, PMacro155_Entry1_DelaySec, PMacro155_Entry1_TimMin, PMacro155_Entry1_TimSec, PMacro155_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro155_Entry2_DelayMin, PMacro155_Entry2_DelaySec, PMacro155_Entry2_TimMin, PMacro155_Entry2_TimSec, PMacro155_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro155_Entry3_DelayMin, PMacro155_Entry3_DelaySec, PMacro155_Entry3_TimMin, PMacro155_Entry3_TimSec, PMacro155_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro155_Entry4_DelayMin, PMacro155_Entry4_DelaySec, PMacro155_Entry4_TimMin, PMacro155_Entry4_TimSec, PMacro155_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro155_Entry5_DelayMin, PMacro155_Entry5_DelaySec, PMacro155_Entry5_TimMin, PMacro155_Entry5_TimSec, PMacro155_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro155_Entry6_DelayMin, PMacro155_Entry6_DelaySec, PMacro155_Entry6_TimMin, PMacro155_Entry6_TimSec, PMacro155_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro155_Entry7_DelayMin, PMacro155_Entry7_DelaySec, PMacro155_Entry7_TimMin, PMacro155_Entry7_TimSec, PMacro155_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro155_Entry8_DelayMin, PMacro155_Entry8_DelaySec, PMacro155_Entry8_TimMin, PMacro155_Entry8_TimSec, PMacro155_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro155_Entry9_DelayMin, PMacro155_Entry9_DelaySec, PMacro155_Entry9_TimMin, PMacro155_Entry9_TimSec, PMacro155_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro155_Entry10_DelayMin, PMacro155_Entry10_DelaySec, PMacro155_Entry10_TimMin, PMacro155_Entry10_TimSec, PMacro155_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro155_Entry11_DelayMin, PMacro155_Entry11_DelaySec, PMacro155_Entry11_TimMin, PMacro155_Entry11_TimSec, PMacro155_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro155_Entry12_DelayMin, PMacro155_Entry12_DelaySec, PMacro155_Entry12_TimMin, PMacro155_Entry12_TimSec, PMacro155_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro155_Entry13_DelayMin, PMacro155_Entry13_DelaySec, PMacro155_Entry13_TimMin, PMacro155_Entry13_TimSec, PMacro155_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro155_Entry14_DelayMin, PMacro155_Entry14_DelaySec, PMacro155_Entry14_TimMin, PMacro155_Entry14_TimSec, PMacro155_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro155_Entry15_DelayMin, PMacro155_Entry15_DelaySec, PMacro155_Entry15_TimMin, PMacro155_Entry15_TimSec, PMacro155_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR155_STRING};

const struct super_macro Macro156 = {PMacro156_NumEntries,
		         PMacro156_Entry1_DelayMin, PMacro156_Entry1_DelaySec, PMacro156_Entry1_TimMin, PMacro156_Entry1_TimSec, PMacro156_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro156_Entry2_DelayMin, PMacro156_Entry2_DelaySec, PMacro156_Entry2_TimMin, PMacro156_Entry2_TimSec, PMacro156_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro156_Entry3_DelayMin, PMacro156_Entry3_DelaySec, PMacro156_Entry3_TimMin, PMacro156_Entry3_TimSec, PMacro156_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro156_Entry4_DelayMin, PMacro156_Entry4_DelaySec, PMacro156_Entry4_TimMin, PMacro156_Entry4_TimSec, PMacro156_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro156_Entry5_DelayMin, PMacro156_Entry5_DelaySec, PMacro156_Entry5_TimMin, PMacro156_Entry5_TimSec, PMacro156_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro156_Entry6_DelayMin, PMacro156_Entry6_DelaySec, PMacro156_Entry6_TimMin, PMacro156_Entry6_TimSec, PMacro156_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro156_Entry7_DelayMin, PMacro156_Entry7_DelaySec, PMacro156_Entry7_TimMin, PMacro156_Entry7_TimSec, PMacro156_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro156_Entry8_DelayMin, PMacro156_Entry8_DelaySec, PMacro156_Entry8_TimMin, PMacro156_Entry8_TimSec, PMacro156_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro156_Entry9_DelayMin, PMacro156_Entry9_DelaySec, PMacro156_Entry9_TimMin, PMacro156_Entry9_TimSec, PMacro156_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro156_Entry10_DelayMin, PMacro156_Entry10_DelaySec, PMacro156_Entry10_TimMin, PMacro156_Entry10_TimSec, PMacro156_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro156_Entry11_DelayMin, PMacro156_Entry11_DelaySec, PMacro156_Entry11_TimMin, PMacro156_Entry11_TimSec, PMacro156_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro156_Entry12_DelayMin, PMacro156_Entry12_DelaySec, PMacro156_Entry12_TimMin, PMacro156_Entry12_TimSec, PMacro156_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro156_Entry13_DelayMin, PMacro156_Entry13_DelaySec, PMacro156_Entry13_TimMin, PMacro156_Entry13_TimSec, PMacro156_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro156_Entry14_DelayMin, PMacro156_Entry14_DelaySec, PMacro156_Entry14_TimMin, PMacro156_Entry14_TimSec, PMacro156_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro156_Entry15_DelayMin, PMacro156_Entry15_DelaySec, PMacro156_Entry15_TimMin, PMacro156_Entry15_TimSec, PMacro156_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR156_STRING};

const struct super_macro Macro157 = {PMacro157_NumEntries,
		         PMacro157_Entry1_DelayMin, PMacro157_Entry1_DelaySec, PMacro157_Entry1_TimMin, PMacro157_Entry1_TimSec, PMacro157_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro157_Entry2_DelayMin, PMacro157_Entry2_DelaySec, PMacro157_Entry2_TimMin, PMacro157_Entry2_TimSec, PMacro157_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro157_Entry3_DelayMin, PMacro157_Entry3_DelaySec, PMacro157_Entry3_TimMin, PMacro157_Entry3_TimSec, PMacro157_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro157_Entry4_DelayMin, PMacro157_Entry4_DelaySec, PMacro157_Entry4_TimMin, PMacro157_Entry4_TimSec, PMacro157_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro157_Entry5_DelayMin, PMacro157_Entry5_DelaySec, PMacro157_Entry5_TimMin, PMacro157_Entry5_TimSec, PMacro157_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro157_Entry6_DelayMin, PMacro157_Entry6_DelaySec, PMacro157_Entry6_TimMin, PMacro157_Entry6_TimSec, PMacro157_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro157_Entry7_DelayMin, PMacro157_Entry7_DelaySec, PMacro157_Entry7_TimMin, PMacro157_Entry7_TimSec, PMacro157_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro157_Entry8_DelayMin, PMacro157_Entry8_DelaySec, PMacro157_Entry8_TimMin, PMacro157_Entry8_TimSec, PMacro157_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro157_Entry9_DelayMin, PMacro157_Entry9_DelaySec, PMacro157_Entry9_TimMin, PMacro157_Entry9_TimSec, PMacro157_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro157_Entry10_DelayMin, PMacro157_Entry10_DelaySec, PMacro157_Entry10_TimMin, PMacro157_Entry10_TimSec, PMacro157_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro157_Entry11_DelayMin, PMacro157_Entry11_DelaySec, PMacro157_Entry11_TimMin, PMacro157_Entry11_TimSec, PMacro157_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro157_Entry12_DelayMin, PMacro157_Entry12_DelaySec, PMacro157_Entry12_TimMin, PMacro157_Entry12_TimSec, PMacro157_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro157_Entry13_DelayMin, PMacro157_Entry13_DelaySec, PMacro157_Entry13_TimMin, PMacro157_Entry13_TimSec, PMacro157_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro157_Entry14_DelayMin, PMacro157_Entry14_DelaySec, PMacro157_Entry14_TimMin, PMacro157_Entry14_TimSec, PMacro157_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro157_Entry15_DelayMin, PMacro157_Entry15_DelaySec, PMacro157_Entry15_TimMin, PMacro157_Entry15_TimSec, PMacro157_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR157_STRING};

const struct super_macro Macro158 = {PMacro158_NumEntries,
		         PMacro158_Entry1_DelayMin, PMacro158_Entry1_DelaySec, PMacro158_Entry1_TimMin, PMacro158_Entry1_TimSec, PMacro158_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro158_Entry2_DelayMin, PMacro158_Entry2_DelaySec, PMacro158_Entry2_TimMin, PMacro158_Entry2_TimSec, PMacro158_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro158_Entry3_DelayMin, PMacro158_Entry3_DelaySec, PMacro158_Entry3_TimMin, PMacro158_Entry3_TimSec, PMacro158_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro158_Entry4_DelayMin, PMacro158_Entry4_DelaySec, PMacro158_Entry4_TimMin, PMacro158_Entry4_TimSec, PMacro158_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro158_Entry5_DelayMin, PMacro158_Entry5_DelaySec, PMacro158_Entry5_TimMin, PMacro158_Entry5_TimSec, PMacro158_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro158_Entry6_DelayMin, PMacro158_Entry6_DelaySec, PMacro158_Entry6_TimMin, PMacro158_Entry6_TimSec, PMacro158_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro158_Entry7_DelayMin, PMacro158_Entry7_DelaySec, PMacro158_Entry7_TimMin, PMacro158_Entry7_TimSec, PMacro158_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro158_Entry8_DelayMin, PMacro158_Entry8_DelaySec, PMacro158_Entry8_TimMin, PMacro158_Entry8_TimSec, PMacro158_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro158_Entry9_DelayMin, PMacro158_Entry9_DelaySec, PMacro158_Entry9_TimMin, PMacro158_Entry9_TimSec, PMacro158_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro158_Entry10_DelayMin, PMacro158_Entry10_DelaySec, PMacro158_Entry10_TimMin, PMacro158_Entry10_TimSec, PMacro158_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro158_Entry11_DelayMin, PMacro158_Entry11_DelaySec, PMacro158_Entry11_TimMin, PMacro158_Entry11_TimSec, PMacro158_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro158_Entry12_DelayMin, PMacro158_Entry12_DelaySec, PMacro158_Entry12_TimMin, PMacro158_Entry12_TimSec, PMacro158_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro158_Entry13_DelayMin, PMacro158_Entry13_DelaySec, PMacro158_Entry13_TimMin, PMacro158_Entry13_TimSec, PMacro158_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro158_Entry14_DelayMin, PMacro158_Entry14_DelaySec, PMacro158_Entry14_TimMin, PMacro158_Entry14_TimSec, PMacro158_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro158_Entry15_DelayMin, PMacro158_Entry15_DelaySec, PMacro158_Entry15_TimMin, PMacro158_Entry15_TimSec, PMacro158_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR158_STRING};

const struct super_macro Macro159 = {PMacro159_NumEntries,
		         PMacro159_Entry1_DelayMin, PMacro159_Entry1_DelaySec, PMacro159_Entry1_TimMin, PMacro159_Entry1_TimSec, PMacro159_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro159_Entry2_DelayMin, PMacro159_Entry2_DelaySec, PMacro159_Entry2_TimMin, PMacro159_Entry2_TimSec, PMacro159_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro159_Entry3_DelayMin, PMacro159_Entry3_DelaySec, PMacro159_Entry3_TimMin, PMacro159_Entry3_TimSec, PMacro159_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro159_Entry4_DelayMin, PMacro159_Entry4_DelaySec, PMacro159_Entry4_TimMin, PMacro159_Entry4_TimSec, PMacro159_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro159_Entry5_DelayMin, PMacro159_Entry5_DelaySec, PMacro159_Entry5_TimMin, PMacro159_Entry5_TimSec, PMacro159_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro159_Entry6_DelayMin, PMacro159_Entry6_DelaySec, PMacro159_Entry6_TimMin, PMacro159_Entry6_TimSec, PMacro159_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro159_Entry7_DelayMin, PMacro159_Entry7_DelaySec, PMacro159_Entry7_TimMin, PMacro159_Entry7_TimSec, PMacro159_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro159_Entry8_DelayMin, PMacro159_Entry8_DelaySec, PMacro159_Entry8_TimMin, PMacro159_Entry8_TimSec, PMacro159_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro159_Entry9_DelayMin, PMacro159_Entry9_DelaySec, PMacro159_Entry9_TimMin, PMacro159_Entry9_TimSec, PMacro159_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro159_Entry10_DelayMin, PMacro159_Entry10_DelaySec, PMacro159_Entry10_TimMin, PMacro159_Entry10_TimSec, PMacro159_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro159_Entry11_DelayMin, PMacro159_Entry11_DelaySec, PMacro159_Entry11_TimMin, PMacro159_Entry11_TimSec, PMacro159_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro159_Entry12_DelayMin, PMacro159_Entry12_DelaySec, PMacro159_Entry12_TimMin, PMacro159_Entry12_TimSec, PMacro159_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro159_Entry13_DelayMin, PMacro159_Entry13_DelaySec, PMacro159_Entry13_TimMin, PMacro159_Entry13_TimSec, PMacro159_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro159_Entry14_DelayMin, PMacro159_Entry14_DelaySec, PMacro159_Entry14_TimMin, PMacro159_Entry14_TimSec, PMacro159_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro159_Entry15_DelayMin, PMacro159_Entry15_DelaySec, PMacro159_Entry15_TimMin, PMacro159_Entry15_TimSec, PMacro159_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR159_STRING};

const struct super_macro Macro160 = {PMacro160_NumEntries,
		         PMacro160_Entry1_DelayMin, PMacro160_Entry1_DelaySec, PMacro160_Entry1_TimMin, PMacro160_Entry1_TimSec, PMacro160_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro160_Entry2_DelayMin, PMacro160_Entry2_DelaySec, PMacro160_Entry2_TimMin, PMacro160_Entry2_TimSec, PMacro160_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro160_Entry3_DelayMin, PMacro160_Entry3_DelaySec, PMacro160_Entry3_TimMin, PMacro160_Entry3_TimSec, PMacro160_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro160_Entry4_DelayMin, PMacro160_Entry4_DelaySec, PMacro160_Entry4_TimMin, PMacro160_Entry4_TimSec, PMacro160_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro160_Entry5_DelayMin, PMacro160_Entry5_DelaySec, PMacro160_Entry5_TimMin, PMacro160_Entry5_TimSec, PMacro160_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro160_Entry6_DelayMin, PMacro160_Entry6_DelaySec, PMacro160_Entry6_TimMin, PMacro160_Entry6_TimSec, PMacro160_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro160_Entry7_DelayMin, PMacro160_Entry7_DelaySec, PMacro160_Entry7_TimMin, PMacro160_Entry7_TimSec, PMacro160_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro160_Entry8_DelayMin, PMacro160_Entry8_DelaySec, PMacro160_Entry8_TimMin, PMacro160_Entry8_TimSec, PMacro160_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro160_Entry9_DelayMin, PMacro160_Entry9_DelaySec, PMacro160_Entry9_TimMin, PMacro160_Entry9_TimSec, PMacro160_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro160_Entry10_DelayMin, PMacro160_Entry10_DelaySec, PMacro160_Entry10_TimMin, PMacro160_Entry10_TimSec, PMacro160_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro160_Entry11_DelayMin, PMacro160_Entry11_DelaySec, PMacro160_Entry11_TimMin, PMacro160_Entry11_TimSec, PMacro160_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro160_Entry12_DelayMin, PMacro160_Entry12_DelaySec, PMacro160_Entry12_TimMin, PMacro160_Entry12_TimSec, PMacro160_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro160_Entry13_DelayMin, PMacro160_Entry13_DelaySec, PMacro160_Entry13_TimMin, PMacro160_Entry13_TimSec, PMacro160_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro160_Entry14_DelayMin, PMacro160_Entry14_DelaySec, PMacro160_Entry14_TimMin, PMacro160_Entry14_TimSec, PMacro160_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro160_Entry15_DelayMin, PMacro160_Entry15_DelaySec, PMacro160_Entry15_TimMin, PMacro160_Entry15_TimSec, PMacro160_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR160_STRING};

const struct super_macro Macro161 = {PMacro161_NumEntries,
		         PMacro161_Entry1_DelayMin, PMacro161_Entry1_DelaySec, PMacro161_Entry1_TimMin, PMacro161_Entry1_TimSec, PMacro161_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro161_Entry2_DelayMin, PMacro161_Entry2_DelaySec, PMacro161_Entry2_TimMin, PMacro161_Entry2_TimSec, PMacro161_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro161_Entry3_DelayMin, PMacro161_Entry3_DelaySec, PMacro161_Entry3_TimMin, PMacro161_Entry3_TimSec, PMacro161_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro161_Entry4_DelayMin, PMacro161_Entry4_DelaySec, PMacro161_Entry4_TimMin, PMacro161_Entry4_TimSec, PMacro161_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro161_Entry5_DelayMin, PMacro161_Entry5_DelaySec, PMacro161_Entry5_TimMin, PMacro161_Entry5_TimSec, PMacro161_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro161_Entry6_DelayMin, PMacro161_Entry6_DelaySec, PMacro161_Entry6_TimMin, PMacro161_Entry6_TimSec, PMacro161_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro161_Entry7_DelayMin, PMacro161_Entry7_DelaySec, PMacro161_Entry7_TimMin, PMacro161_Entry7_TimSec, PMacro161_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro161_Entry8_DelayMin, PMacro161_Entry8_DelaySec, PMacro161_Entry8_TimMin, PMacro161_Entry8_TimSec, PMacro161_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro161_Entry9_DelayMin, PMacro161_Entry9_DelaySec, PMacro161_Entry9_TimMin, PMacro161_Entry9_TimSec, PMacro161_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro161_Entry10_DelayMin, PMacro161_Entry10_DelaySec, PMacro161_Entry10_TimMin, PMacro161_Entry10_TimSec, PMacro161_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro161_Entry11_DelayMin, PMacro161_Entry11_DelaySec, PMacro161_Entry11_TimMin, PMacro161_Entry11_TimSec, PMacro161_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro161_Entry12_DelayMin, PMacro161_Entry12_DelaySec, PMacro161_Entry12_TimMin, PMacro161_Entry12_TimSec, PMacro161_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro161_Entry13_DelayMin, PMacro161_Entry13_DelaySec, PMacro161_Entry13_TimMin, PMacro161_Entry13_TimSec, PMacro161_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro161_Entry14_DelayMin, PMacro161_Entry14_DelaySec, PMacro161_Entry14_TimMin, PMacro161_Entry14_TimSec, PMacro161_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro161_Entry15_DelayMin, PMacro161_Entry15_DelaySec, PMacro161_Entry15_TimMin, PMacro161_Entry15_TimSec, PMacro161_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR161_STRING};

const struct super_macro Macro162 = {PMacro162_NumEntries,
		         PMacro162_Entry1_DelayMin, PMacro162_Entry1_DelaySec, PMacro162_Entry1_TimMin, PMacro162_Entry1_TimSec, PMacro162_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro162_Entry2_DelayMin, PMacro162_Entry2_DelaySec, PMacro162_Entry2_TimMin, PMacro162_Entry2_TimSec, PMacro162_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro162_Entry3_DelayMin, PMacro162_Entry3_DelaySec, PMacro162_Entry3_TimMin, PMacro162_Entry3_TimSec, PMacro162_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro162_Entry4_DelayMin, PMacro162_Entry4_DelaySec, PMacro162_Entry4_TimMin, PMacro162_Entry4_TimSec, PMacro162_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro162_Entry5_DelayMin, PMacro162_Entry5_DelaySec, PMacro162_Entry5_TimMin, PMacro162_Entry5_TimSec, PMacro162_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro162_Entry6_DelayMin, PMacro162_Entry6_DelaySec, PMacro162_Entry6_TimMin, PMacro162_Entry6_TimSec, PMacro162_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro162_Entry7_DelayMin, PMacro162_Entry7_DelaySec, PMacro162_Entry7_TimMin, PMacro162_Entry7_TimSec, PMacro162_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro162_Entry8_DelayMin, PMacro162_Entry8_DelaySec, PMacro162_Entry8_TimMin, PMacro162_Entry8_TimSec, PMacro162_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro162_Entry9_DelayMin, PMacro162_Entry9_DelaySec, PMacro162_Entry9_TimMin, PMacro162_Entry9_TimSec, PMacro162_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro162_Entry10_DelayMin, PMacro162_Entry10_DelaySec, PMacro162_Entry10_TimMin, PMacro162_Entry10_TimSec, PMacro162_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro162_Entry11_DelayMin, PMacro162_Entry11_DelaySec, PMacro162_Entry11_TimMin, PMacro162_Entry11_TimSec, PMacro162_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro162_Entry12_DelayMin, PMacro162_Entry12_DelaySec, PMacro162_Entry12_TimMin, PMacro162_Entry12_TimSec, PMacro162_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro162_Entry13_DelayMin, PMacro162_Entry13_DelaySec, PMacro162_Entry13_TimMin, PMacro162_Entry13_TimSec, PMacro162_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro162_Entry14_DelayMin, PMacro162_Entry14_DelaySec, PMacro162_Entry14_TimMin, PMacro162_Entry14_TimSec, PMacro162_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro162_Entry15_DelayMin, PMacro162_Entry15_DelaySec, PMacro162_Entry15_TimMin, PMacro162_Entry15_TimSec, PMacro162_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR162_STRING};

const struct super_macro Macro163 = {PMacro163_NumEntries,
		         PMacro163_Entry1_DelayMin, PMacro163_Entry1_DelaySec, PMacro163_Entry1_TimMin, PMacro163_Entry1_TimSec, PMacro163_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro163_Entry2_DelayMin, PMacro163_Entry2_DelaySec, PMacro163_Entry2_TimMin, PMacro163_Entry2_TimSec, PMacro163_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro163_Entry3_DelayMin, PMacro163_Entry3_DelaySec, PMacro163_Entry3_TimMin, PMacro163_Entry3_TimSec, PMacro163_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro163_Entry4_DelayMin, PMacro163_Entry4_DelaySec, PMacro163_Entry4_TimMin, PMacro163_Entry4_TimSec, PMacro163_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro163_Entry5_DelayMin, PMacro163_Entry5_DelaySec, PMacro163_Entry5_TimMin, PMacro163_Entry5_TimSec, PMacro163_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro163_Entry6_DelayMin, PMacro163_Entry6_DelaySec, PMacro163_Entry6_TimMin, PMacro163_Entry6_TimSec, PMacro163_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro163_Entry7_DelayMin, PMacro163_Entry7_DelaySec, PMacro163_Entry7_TimMin, PMacro163_Entry7_TimSec, PMacro163_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro163_Entry8_DelayMin, PMacro163_Entry8_DelaySec, PMacro163_Entry8_TimMin, PMacro163_Entry8_TimSec, PMacro163_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro163_Entry9_DelayMin, PMacro163_Entry9_DelaySec, PMacro163_Entry9_TimMin, PMacro163_Entry9_TimSec, PMacro163_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro163_Entry10_DelayMin, PMacro163_Entry10_DelaySec, PMacro163_Entry10_TimMin, PMacro163_Entry10_TimSec, PMacro163_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro163_Entry11_DelayMin, PMacro163_Entry11_DelaySec, PMacro163_Entry11_TimMin, PMacro163_Entry11_TimSec, PMacro163_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro163_Entry12_DelayMin, PMacro163_Entry12_DelaySec, PMacro163_Entry12_TimMin, PMacro163_Entry12_TimSec, PMacro163_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro163_Entry13_DelayMin, PMacro163_Entry13_DelaySec, PMacro163_Entry13_TimMin, PMacro163_Entry13_TimSec, PMacro163_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro163_Entry14_DelayMin, PMacro163_Entry14_DelaySec, PMacro163_Entry14_TimMin, PMacro163_Entry14_TimSec, PMacro163_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro163_Entry15_DelayMin, PMacro163_Entry15_DelaySec, PMacro163_Entry15_TimMin, PMacro163_Entry15_TimSec, PMacro163_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR163_STRING};

const struct super_macro Macro164 = {PMacro164_NumEntries,
		         PMacro164_Entry1_DelayMin, PMacro164_Entry1_DelaySec, PMacro164_Entry1_TimMin, PMacro164_Entry1_TimSec, PMacro164_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro164_Entry2_DelayMin, PMacro164_Entry2_DelaySec, PMacro164_Entry2_TimMin, PMacro164_Entry2_TimSec, PMacro164_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro164_Entry3_DelayMin, PMacro164_Entry3_DelaySec, PMacro164_Entry3_TimMin, PMacro164_Entry3_TimSec, PMacro164_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro164_Entry4_DelayMin, PMacro164_Entry4_DelaySec, PMacro164_Entry4_TimMin, PMacro164_Entry4_TimSec, PMacro164_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro164_Entry5_DelayMin, PMacro164_Entry5_DelaySec, PMacro164_Entry5_TimMin, PMacro164_Entry5_TimSec, PMacro164_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro164_Entry6_DelayMin, PMacro164_Entry6_DelaySec, PMacro164_Entry6_TimMin, PMacro164_Entry6_TimSec, PMacro164_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro164_Entry7_DelayMin, PMacro164_Entry7_DelaySec, PMacro164_Entry7_TimMin, PMacro164_Entry7_TimSec, PMacro164_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro164_Entry8_DelayMin, PMacro164_Entry8_DelaySec, PMacro164_Entry8_TimMin, PMacro164_Entry8_TimSec, PMacro164_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro164_Entry9_DelayMin, PMacro164_Entry9_DelaySec, PMacro164_Entry9_TimMin, PMacro164_Entry9_TimSec, PMacro164_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro164_Entry10_DelayMin, PMacro164_Entry10_DelaySec, PMacro164_Entry10_TimMin, PMacro164_Entry10_TimSec, PMacro164_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro164_Entry11_DelayMin, PMacro164_Entry11_DelaySec, PMacro164_Entry11_TimMin, PMacro164_Entry11_TimSec, PMacro164_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro164_Entry12_DelayMin, PMacro164_Entry12_DelaySec, PMacro164_Entry12_TimMin, PMacro164_Entry12_TimSec, PMacro164_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro164_Entry13_DelayMin, PMacro164_Entry13_DelaySec, PMacro164_Entry13_TimMin, PMacro164_Entry13_TimSec, PMacro164_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro164_Entry14_DelayMin, PMacro164_Entry14_DelaySec, PMacro164_Entry14_TimMin, PMacro164_Entry14_TimSec, PMacro164_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro164_Entry15_DelayMin, PMacro164_Entry15_DelaySec, PMacro164_Entry15_TimMin, PMacro164_Entry15_TimSec, PMacro164_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR164_STRING};

const struct super_macro Macro165 = {PMacro165_NumEntries,
		         PMacro165_Entry1_DelayMin, PMacro165_Entry1_DelaySec, PMacro165_Entry1_TimMin, PMacro165_Entry1_TimSec, PMacro165_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro165_Entry2_DelayMin, PMacro165_Entry2_DelaySec, PMacro165_Entry2_TimMin, PMacro165_Entry2_TimSec, PMacro165_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro165_Entry3_DelayMin, PMacro165_Entry3_DelaySec, PMacro165_Entry3_TimMin, PMacro165_Entry3_TimSec, PMacro165_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro165_Entry4_DelayMin, PMacro165_Entry4_DelaySec, PMacro165_Entry4_TimMin, PMacro165_Entry4_TimSec, PMacro165_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro165_Entry5_DelayMin, PMacro165_Entry5_DelaySec, PMacro165_Entry5_TimMin, PMacro165_Entry5_TimSec, PMacro165_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro165_Entry6_DelayMin, PMacro165_Entry6_DelaySec, PMacro165_Entry6_TimMin, PMacro165_Entry6_TimSec, PMacro165_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro165_Entry7_DelayMin, PMacro165_Entry7_DelaySec, PMacro165_Entry7_TimMin, PMacro165_Entry7_TimSec, PMacro165_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro165_Entry8_DelayMin, PMacro165_Entry8_DelaySec, PMacro165_Entry8_TimMin, PMacro165_Entry8_TimSec, PMacro165_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro165_Entry9_DelayMin, PMacro165_Entry9_DelaySec, PMacro165_Entry9_TimMin, PMacro165_Entry9_TimSec, PMacro165_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro165_Entry10_DelayMin, PMacro165_Entry10_DelaySec, PMacro165_Entry10_TimMin, PMacro165_Entry10_TimSec, PMacro165_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro165_Entry11_DelayMin, PMacro165_Entry11_DelaySec, PMacro165_Entry11_TimMin, PMacro165_Entry11_TimSec, PMacro165_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro165_Entry12_DelayMin, PMacro165_Entry12_DelaySec, PMacro165_Entry12_TimMin, PMacro165_Entry12_TimSec, PMacro165_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro165_Entry13_DelayMin, PMacro165_Entry13_DelaySec, PMacro165_Entry13_TimMin, PMacro165_Entry13_TimSec, PMacro165_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro165_Entry14_DelayMin, PMacro165_Entry14_DelaySec, PMacro165_Entry14_TimMin, PMacro165_Entry14_TimSec, PMacro165_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro165_Entry15_DelayMin, PMacro165_Entry15_DelaySec, PMacro165_Entry15_TimMin, PMacro165_Entry15_TimSec, PMacro165_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR165_STRING};

const struct super_macro Macro166 = {PMacro166_NumEntries,
		         PMacro166_Entry1_DelayMin, PMacro166_Entry1_DelaySec, PMacro166_Entry1_TimMin, PMacro166_Entry1_TimSec, PMacro166_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro166_Entry2_DelayMin, PMacro166_Entry2_DelaySec, PMacro166_Entry2_TimMin, PMacro166_Entry2_TimSec, PMacro166_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro166_Entry3_DelayMin, PMacro166_Entry3_DelaySec, PMacro166_Entry3_TimMin, PMacro166_Entry3_TimSec, PMacro166_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro166_Entry4_DelayMin, PMacro166_Entry4_DelaySec, PMacro166_Entry4_TimMin, PMacro166_Entry4_TimSec, PMacro166_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro166_Entry5_DelayMin, PMacro166_Entry5_DelaySec, PMacro166_Entry5_TimMin, PMacro166_Entry5_TimSec, PMacro166_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro166_Entry6_DelayMin, PMacro166_Entry6_DelaySec, PMacro166_Entry6_TimMin, PMacro166_Entry6_TimSec, PMacro166_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro166_Entry7_DelayMin, PMacro166_Entry7_DelaySec, PMacro166_Entry7_TimMin, PMacro166_Entry7_TimSec, PMacro166_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro166_Entry8_DelayMin, PMacro166_Entry8_DelaySec, PMacro166_Entry8_TimMin, PMacro166_Entry8_TimSec, PMacro166_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro166_Entry9_DelayMin, PMacro166_Entry9_DelaySec, PMacro166_Entry9_TimMin, PMacro166_Entry9_TimSec, PMacro166_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro166_Entry10_DelayMin, PMacro166_Entry10_DelaySec, PMacro166_Entry10_TimMin, PMacro166_Entry10_TimSec, PMacro166_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro166_Entry11_DelayMin, PMacro166_Entry11_DelaySec, PMacro166_Entry11_TimMin, PMacro166_Entry11_TimSec, PMacro166_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro166_Entry12_DelayMin, PMacro166_Entry12_DelaySec, PMacro166_Entry12_TimMin, PMacro166_Entry12_TimSec, PMacro166_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro166_Entry13_DelayMin, PMacro166_Entry13_DelaySec, PMacro166_Entry13_TimMin, PMacro166_Entry13_TimSec, PMacro166_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro166_Entry14_DelayMin, PMacro166_Entry14_DelaySec, PMacro166_Entry14_TimMin, PMacro166_Entry14_TimSec, PMacro166_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro166_Entry15_DelayMin, PMacro166_Entry15_DelaySec, PMacro166_Entry15_TimMin, PMacro166_Entry15_TimSec, PMacro166_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR166_STRING};

const struct super_macro Macro167 = {PMacro167_NumEntries,
		         PMacro167_Entry1_DelayMin, PMacro167_Entry1_DelaySec, PMacro167_Entry1_TimMin, PMacro167_Entry1_TimSec, PMacro167_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro167_Entry2_DelayMin, PMacro167_Entry2_DelaySec, PMacro167_Entry2_TimMin, PMacro167_Entry2_TimSec, PMacro167_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro167_Entry3_DelayMin, PMacro167_Entry3_DelaySec, PMacro167_Entry3_TimMin, PMacro167_Entry3_TimSec, PMacro167_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro167_Entry4_DelayMin, PMacro167_Entry4_DelaySec, PMacro167_Entry4_TimMin, PMacro167_Entry4_TimSec, PMacro167_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro167_Entry5_DelayMin, PMacro167_Entry5_DelaySec, PMacro167_Entry5_TimMin, PMacro167_Entry5_TimSec, PMacro167_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro167_Entry6_DelayMin, PMacro167_Entry6_DelaySec, PMacro167_Entry6_TimMin, PMacro167_Entry6_TimSec, PMacro167_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro167_Entry7_DelayMin, PMacro167_Entry7_DelaySec, PMacro167_Entry7_TimMin, PMacro167_Entry7_TimSec, PMacro167_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro167_Entry8_DelayMin, PMacro167_Entry8_DelaySec, PMacro167_Entry8_TimMin, PMacro167_Entry8_TimSec, PMacro167_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro167_Entry9_DelayMin, PMacro167_Entry9_DelaySec, PMacro167_Entry9_TimMin, PMacro167_Entry9_TimSec, PMacro167_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro167_Entry10_DelayMin, PMacro167_Entry10_DelaySec, PMacro167_Entry10_TimMin, PMacro167_Entry10_TimSec, PMacro167_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro167_Entry11_DelayMin, PMacro167_Entry11_DelaySec, PMacro167_Entry11_TimMin, PMacro167_Entry11_TimSec, PMacro167_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro167_Entry12_DelayMin, PMacro167_Entry12_DelaySec, PMacro167_Entry12_TimMin, PMacro167_Entry12_TimSec, PMacro167_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro167_Entry13_DelayMin, PMacro167_Entry13_DelaySec, PMacro167_Entry13_TimMin, PMacro167_Entry13_TimSec, PMacro167_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro167_Entry14_DelayMin, PMacro167_Entry14_DelaySec, PMacro167_Entry14_TimMin, PMacro167_Entry14_TimSec, PMacro167_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro167_Entry15_DelayMin, PMacro167_Entry15_DelaySec, PMacro167_Entry15_TimMin, PMacro167_Entry15_TimSec, PMacro167_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR167_STRING};

const struct super_macro Macro168 = {PMacro168_NumEntries,
		         PMacro168_Entry1_DelayMin, PMacro168_Entry1_DelaySec, PMacro168_Entry1_TimMin, PMacro168_Entry1_TimSec, PMacro168_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro168_Entry2_DelayMin, PMacro168_Entry2_DelaySec, PMacro168_Entry2_TimMin, PMacro168_Entry2_TimSec, PMacro168_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro168_Entry3_DelayMin, PMacro168_Entry3_DelaySec, PMacro168_Entry3_TimMin, PMacro168_Entry3_TimSec, PMacro168_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro168_Entry4_DelayMin, PMacro168_Entry4_DelaySec, PMacro168_Entry4_TimMin, PMacro168_Entry4_TimSec, PMacro168_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro168_Entry5_DelayMin, PMacro168_Entry5_DelaySec, PMacro168_Entry5_TimMin, PMacro168_Entry5_TimSec, PMacro168_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro168_Entry6_DelayMin, PMacro168_Entry6_DelaySec, PMacro168_Entry6_TimMin, PMacro168_Entry6_TimSec, PMacro168_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro168_Entry7_DelayMin, PMacro168_Entry7_DelaySec, PMacro168_Entry7_TimMin, PMacro168_Entry7_TimSec, PMacro168_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro168_Entry8_DelayMin, PMacro168_Entry8_DelaySec, PMacro168_Entry8_TimMin, PMacro168_Entry8_TimSec, PMacro168_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro168_Entry9_DelayMin, PMacro168_Entry9_DelaySec, PMacro168_Entry9_TimMin, PMacro168_Entry9_TimSec, PMacro168_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro168_Entry10_DelayMin, PMacro168_Entry10_DelaySec, PMacro168_Entry10_TimMin, PMacro168_Entry10_TimSec, PMacro168_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro168_Entry11_DelayMin, PMacro168_Entry11_DelaySec, PMacro168_Entry11_TimMin, PMacro168_Entry11_TimSec, PMacro168_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro168_Entry12_DelayMin, PMacro168_Entry12_DelaySec, PMacro168_Entry12_TimMin, PMacro168_Entry12_TimSec, PMacro168_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro168_Entry13_DelayMin, PMacro168_Entry13_DelaySec, PMacro168_Entry13_TimMin, PMacro168_Entry13_TimSec, PMacro168_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro168_Entry14_DelayMin, PMacro168_Entry14_DelaySec, PMacro168_Entry14_TimMin, PMacro168_Entry14_TimSec, PMacro168_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro168_Entry15_DelayMin, PMacro168_Entry15_DelaySec, PMacro168_Entry15_TimMin, PMacro168_Entry15_TimSec, PMacro168_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR168_STRING};

const struct super_macro Macro169 = {PMacro169_NumEntries,
		         PMacro169_Entry1_DelayMin, PMacro169_Entry1_DelaySec, PMacro169_Entry1_TimMin, PMacro169_Entry1_TimSec, PMacro169_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro169_Entry2_DelayMin, PMacro169_Entry2_DelaySec, PMacro169_Entry2_TimMin, PMacro169_Entry2_TimSec, PMacro169_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro169_Entry3_DelayMin, PMacro169_Entry3_DelaySec, PMacro169_Entry3_TimMin, PMacro169_Entry3_TimSec, PMacro169_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro169_Entry4_DelayMin, PMacro169_Entry4_DelaySec, PMacro169_Entry4_TimMin, PMacro169_Entry4_TimSec, PMacro169_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro169_Entry5_DelayMin, PMacro169_Entry5_DelaySec, PMacro169_Entry5_TimMin, PMacro169_Entry5_TimSec, PMacro169_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro169_Entry6_DelayMin, PMacro169_Entry6_DelaySec, PMacro169_Entry6_TimMin, PMacro169_Entry6_TimSec, PMacro169_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro169_Entry7_DelayMin, PMacro169_Entry7_DelaySec, PMacro169_Entry7_TimMin, PMacro169_Entry7_TimSec, PMacro169_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro169_Entry8_DelayMin, PMacro169_Entry8_DelaySec, PMacro169_Entry8_TimMin, PMacro169_Entry8_TimSec, PMacro169_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro169_Entry9_DelayMin, PMacro169_Entry9_DelaySec, PMacro169_Entry9_TimMin, PMacro169_Entry9_TimSec, PMacro169_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro169_Entry10_DelayMin, PMacro169_Entry10_DelaySec, PMacro169_Entry10_TimMin, PMacro169_Entry10_TimSec, PMacro169_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro169_Entry11_DelayMin, PMacro169_Entry11_DelaySec, PMacro169_Entry11_TimMin, PMacro169_Entry11_TimSec, PMacro169_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro169_Entry12_DelayMin, PMacro169_Entry12_DelaySec, PMacro169_Entry12_TimMin, PMacro169_Entry12_TimSec, PMacro169_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro169_Entry13_DelayMin, PMacro169_Entry13_DelaySec, PMacro169_Entry13_TimMin, PMacro169_Entry13_TimSec, PMacro169_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro169_Entry14_DelayMin, PMacro169_Entry14_DelaySec, PMacro169_Entry14_TimMin, PMacro169_Entry14_TimSec, PMacro169_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro169_Entry15_DelayMin, PMacro169_Entry15_DelaySec, PMacro169_Entry15_TimMin, PMacro169_Entry15_TimSec, PMacro169_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR169_STRING};

const struct super_macro Macro170 = {PMacro170_NumEntries,
		         PMacro170_Entry1_DelayMin, PMacro170_Entry1_DelaySec, PMacro170_Entry1_TimMin, PMacro170_Entry1_TimSec, PMacro170_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro170_Entry2_DelayMin, PMacro170_Entry2_DelaySec, PMacro170_Entry2_TimMin, PMacro170_Entry2_TimSec, PMacro170_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro170_Entry3_DelayMin, PMacro170_Entry3_DelaySec, PMacro170_Entry3_TimMin, PMacro170_Entry3_TimSec, PMacro170_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro170_Entry4_DelayMin, PMacro170_Entry4_DelaySec, PMacro170_Entry4_TimMin, PMacro170_Entry4_TimSec, PMacro170_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro170_Entry5_DelayMin, PMacro170_Entry5_DelaySec, PMacro170_Entry5_TimMin, PMacro170_Entry5_TimSec, PMacro170_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro170_Entry6_DelayMin, PMacro170_Entry6_DelaySec, PMacro170_Entry6_TimMin, PMacro170_Entry6_TimSec, PMacro170_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro170_Entry7_DelayMin, PMacro170_Entry7_DelaySec, PMacro170_Entry7_TimMin, PMacro170_Entry7_TimSec, PMacro170_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro170_Entry8_DelayMin, PMacro170_Entry8_DelaySec, PMacro170_Entry8_TimMin, PMacro170_Entry8_TimSec, PMacro170_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro170_Entry9_DelayMin, PMacro170_Entry9_DelaySec, PMacro170_Entry9_TimMin, PMacro170_Entry9_TimSec, PMacro170_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro170_Entry10_DelayMin, PMacro170_Entry10_DelaySec, PMacro170_Entry10_TimMin, PMacro170_Entry10_TimSec, PMacro170_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro170_Entry11_DelayMin, PMacro170_Entry11_DelaySec, PMacro170_Entry11_TimMin, PMacro170_Entry11_TimSec, PMacro170_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro170_Entry12_DelayMin, PMacro170_Entry12_DelaySec, PMacro170_Entry12_TimMin, PMacro170_Entry12_TimSec, PMacro170_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro170_Entry13_DelayMin, PMacro170_Entry13_DelaySec, PMacro170_Entry13_TimMin, PMacro170_Entry13_TimSec, PMacro170_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro170_Entry14_DelayMin, PMacro170_Entry14_DelaySec, PMacro170_Entry14_TimMin, PMacro170_Entry14_TimSec, PMacro170_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro170_Entry15_DelayMin, PMacro170_Entry15_DelaySec, PMacro170_Entry15_TimMin, PMacro170_Entry15_TimSec, PMacro170_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR170_STRING};

const struct super_macro Macro171 = {PMacro171_NumEntries,
		         PMacro171_Entry1_DelayMin, PMacro171_Entry1_DelaySec, PMacro171_Entry1_TimMin, PMacro171_Entry1_TimSec, PMacro171_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro171_Entry2_DelayMin, PMacro171_Entry2_DelaySec, PMacro171_Entry2_TimMin, PMacro171_Entry2_TimSec, PMacro171_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro171_Entry3_DelayMin, PMacro171_Entry3_DelaySec, PMacro171_Entry3_TimMin, PMacro171_Entry3_TimSec, PMacro171_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro171_Entry4_DelayMin, PMacro171_Entry4_DelaySec, PMacro171_Entry4_TimMin, PMacro171_Entry4_TimSec, PMacro171_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro171_Entry5_DelayMin, PMacro171_Entry5_DelaySec, PMacro171_Entry5_TimMin, PMacro171_Entry5_TimSec, PMacro171_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro171_Entry6_DelayMin, PMacro171_Entry6_DelaySec, PMacro171_Entry6_TimMin, PMacro171_Entry6_TimSec, PMacro171_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro171_Entry7_DelayMin, PMacro171_Entry7_DelaySec, PMacro171_Entry7_TimMin, PMacro171_Entry7_TimSec, PMacro171_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro171_Entry8_DelayMin, PMacro171_Entry8_DelaySec, PMacro171_Entry8_TimMin, PMacro171_Entry8_TimSec, PMacro171_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro171_Entry9_DelayMin, PMacro171_Entry9_DelaySec, PMacro171_Entry9_TimMin, PMacro171_Entry9_TimSec, PMacro171_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro171_Entry10_DelayMin, PMacro171_Entry10_DelaySec, PMacro171_Entry10_TimMin, PMacro171_Entry10_TimSec, PMacro171_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro171_Entry11_DelayMin, PMacro171_Entry11_DelaySec, PMacro171_Entry11_TimMin, PMacro171_Entry11_TimSec, PMacro171_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro171_Entry12_DelayMin, PMacro171_Entry12_DelaySec, PMacro171_Entry12_TimMin, PMacro171_Entry12_TimSec, PMacro171_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro171_Entry13_DelayMin, PMacro171_Entry13_DelaySec, PMacro171_Entry13_TimMin, PMacro171_Entry13_TimSec, PMacro171_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro171_Entry14_DelayMin, PMacro171_Entry14_DelaySec, PMacro171_Entry14_TimMin, PMacro171_Entry14_TimSec, PMacro171_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro171_Entry15_DelayMin, PMacro171_Entry15_DelaySec, PMacro171_Entry15_TimMin, PMacro171_Entry15_TimSec, PMacro171_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR171_STRING};

const struct super_macro Macro172 = {PMacro172_NumEntries,
		         PMacro172_Entry1_DelayMin, PMacro172_Entry1_DelaySec, PMacro172_Entry1_TimMin, PMacro172_Entry1_TimSec, PMacro172_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro172_Entry2_DelayMin, PMacro172_Entry2_DelaySec, PMacro172_Entry2_TimMin, PMacro172_Entry2_TimSec, PMacro172_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro172_Entry3_DelayMin, PMacro172_Entry3_DelaySec, PMacro172_Entry3_TimMin, PMacro172_Entry3_TimSec, PMacro172_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro172_Entry4_DelayMin, PMacro172_Entry4_DelaySec, PMacro172_Entry4_TimMin, PMacro172_Entry4_TimSec, PMacro172_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro172_Entry5_DelayMin, PMacro172_Entry5_DelaySec, PMacro172_Entry5_TimMin, PMacro172_Entry5_TimSec, PMacro172_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro172_Entry6_DelayMin, PMacro172_Entry6_DelaySec, PMacro172_Entry6_TimMin, PMacro172_Entry6_TimSec, PMacro172_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro172_Entry7_DelayMin, PMacro172_Entry7_DelaySec, PMacro172_Entry7_TimMin, PMacro172_Entry7_TimSec, PMacro172_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro172_Entry8_DelayMin, PMacro172_Entry8_DelaySec, PMacro172_Entry8_TimMin, PMacro172_Entry8_TimSec, PMacro172_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro172_Entry9_DelayMin, PMacro172_Entry9_DelaySec, PMacro172_Entry9_TimMin, PMacro172_Entry9_TimSec, PMacro172_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro172_Entry10_DelayMin, PMacro172_Entry10_DelaySec, PMacro172_Entry10_TimMin, PMacro172_Entry10_TimSec, PMacro172_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro172_Entry11_DelayMin, PMacro172_Entry11_DelaySec, PMacro172_Entry11_TimMin, PMacro172_Entry11_TimSec, PMacro172_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro172_Entry12_DelayMin, PMacro172_Entry12_DelaySec, PMacro172_Entry12_TimMin, PMacro172_Entry12_TimSec, PMacro172_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro172_Entry13_DelayMin, PMacro172_Entry13_DelaySec, PMacro172_Entry13_TimMin, PMacro172_Entry13_TimSec, PMacro172_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro172_Entry14_DelayMin, PMacro172_Entry14_DelaySec, PMacro172_Entry14_TimMin, PMacro172_Entry14_TimSec, PMacro172_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro172_Entry15_DelayMin, PMacro172_Entry15_DelaySec, PMacro172_Entry15_TimMin, PMacro172_Entry15_TimSec, PMacro172_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR172_STRING};

const struct super_macro Macro173 = {PMacro173_NumEntries,
		         PMacro173_Entry1_DelayMin, PMacro173_Entry1_DelaySec, PMacro173_Entry1_TimMin, PMacro173_Entry1_TimSec, PMacro173_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro173_Entry2_DelayMin, PMacro173_Entry2_DelaySec, PMacro173_Entry2_TimMin, PMacro173_Entry2_TimSec, PMacro173_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro173_Entry3_DelayMin, PMacro173_Entry3_DelaySec, PMacro173_Entry3_TimMin, PMacro173_Entry3_TimSec, PMacro173_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro173_Entry4_DelayMin, PMacro173_Entry4_DelaySec, PMacro173_Entry4_TimMin, PMacro173_Entry4_TimSec, PMacro173_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro173_Entry5_DelayMin, PMacro173_Entry5_DelaySec, PMacro173_Entry5_TimMin, PMacro173_Entry5_TimSec, PMacro173_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro173_Entry6_DelayMin, PMacro173_Entry6_DelaySec, PMacro173_Entry6_TimMin, PMacro173_Entry6_TimSec, PMacro173_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro173_Entry7_DelayMin, PMacro173_Entry7_DelaySec, PMacro173_Entry7_TimMin, PMacro173_Entry7_TimSec, PMacro173_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro173_Entry8_DelayMin, PMacro173_Entry8_DelaySec, PMacro173_Entry8_TimMin, PMacro173_Entry8_TimSec, PMacro173_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro173_Entry9_DelayMin, PMacro173_Entry9_DelaySec, PMacro173_Entry9_TimMin, PMacro173_Entry9_TimSec, PMacro173_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro173_Entry10_DelayMin, PMacro173_Entry10_DelaySec, PMacro173_Entry10_TimMin, PMacro173_Entry10_TimSec, PMacro173_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro173_Entry11_DelayMin, PMacro173_Entry11_DelaySec, PMacro173_Entry11_TimMin, PMacro173_Entry11_TimSec, PMacro173_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro173_Entry12_DelayMin, PMacro173_Entry12_DelaySec, PMacro173_Entry12_TimMin, PMacro173_Entry12_TimSec, PMacro173_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro173_Entry13_DelayMin, PMacro173_Entry13_DelaySec, PMacro173_Entry13_TimMin, PMacro173_Entry13_TimSec, PMacro173_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro173_Entry14_DelayMin, PMacro173_Entry14_DelaySec, PMacro173_Entry14_TimMin, PMacro173_Entry14_TimSec, PMacro173_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro173_Entry15_DelayMin, PMacro173_Entry15_DelaySec, PMacro173_Entry15_TimMin, PMacro173_Entry15_TimSec, PMacro173_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR173_STRING};

const struct super_macro Macro174 = {PMacro174_NumEntries,
		         PMacro174_Entry1_DelayMin, PMacro174_Entry1_DelaySec, PMacro174_Entry1_TimMin, PMacro174_Entry1_TimSec, PMacro174_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro174_Entry2_DelayMin, PMacro174_Entry2_DelaySec, PMacro174_Entry2_TimMin, PMacro174_Entry2_TimSec, PMacro174_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro174_Entry3_DelayMin, PMacro174_Entry3_DelaySec, PMacro174_Entry3_TimMin, PMacro174_Entry3_TimSec, PMacro174_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro174_Entry4_DelayMin, PMacro174_Entry4_DelaySec, PMacro174_Entry4_TimMin, PMacro174_Entry4_TimSec, PMacro174_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro174_Entry5_DelayMin, PMacro174_Entry5_DelaySec, PMacro174_Entry5_TimMin, PMacro174_Entry5_TimSec, PMacro174_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro174_Entry6_DelayMin, PMacro174_Entry6_DelaySec, PMacro174_Entry6_TimMin, PMacro174_Entry6_TimSec, PMacro174_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro174_Entry7_DelayMin, PMacro174_Entry7_DelaySec, PMacro174_Entry7_TimMin, PMacro174_Entry7_TimSec, PMacro174_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro174_Entry8_DelayMin, PMacro174_Entry8_DelaySec, PMacro174_Entry8_TimMin, PMacro174_Entry8_TimSec, PMacro174_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro174_Entry9_DelayMin, PMacro174_Entry9_DelaySec, PMacro174_Entry9_TimMin, PMacro174_Entry9_TimSec, PMacro174_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro174_Entry10_DelayMin, PMacro174_Entry10_DelaySec, PMacro174_Entry10_TimMin, PMacro174_Entry10_TimSec, PMacro174_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro174_Entry11_DelayMin, PMacro174_Entry11_DelaySec, PMacro174_Entry11_TimMin, PMacro174_Entry11_TimSec, PMacro174_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro174_Entry12_DelayMin, PMacro174_Entry12_DelaySec, PMacro174_Entry12_TimMin, PMacro174_Entry12_TimSec, PMacro174_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro174_Entry13_DelayMin, PMacro174_Entry13_DelaySec, PMacro174_Entry13_TimMin, PMacro174_Entry13_TimSec, PMacro174_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro174_Entry14_DelayMin, PMacro174_Entry14_DelaySec, PMacro174_Entry14_TimMin, PMacro174_Entry14_TimSec, PMacro174_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro174_Entry15_DelayMin, PMacro174_Entry15_DelaySec, PMacro174_Entry15_TimMin, PMacro174_Entry15_TimSec, PMacro174_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR174_STRING};

const struct super_macro Macro175 = {PMacro175_NumEntries,
		         PMacro175_Entry1_DelayMin, PMacro175_Entry1_DelaySec, PMacro175_Entry1_TimMin, PMacro175_Entry1_TimSec, PMacro175_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro175_Entry2_DelayMin, PMacro175_Entry2_DelaySec, PMacro175_Entry2_TimMin, PMacro175_Entry2_TimSec, PMacro175_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro175_Entry3_DelayMin, PMacro175_Entry3_DelaySec, PMacro175_Entry3_TimMin, PMacro175_Entry3_TimSec, PMacro175_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro175_Entry4_DelayMin, PMacro175_Entry4_DelaySec, PMacro175_Entry4_TimMin, PMacro175_Entry4_TimSec, PMacro175_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro175_Entry5_DelayMin, PMacro175_Entry5_DelaySec, PMacro175_Entry5_TimMin, PMacro175_Entry5_TimSec, PMacro175_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro175_Entry6_DelayMin, PMacro175_Entry6_DelaySec, PMacro175_Entry6_TimMin, PMacro175_Entry6_TimSec, PMacro175_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro175_Entry7_DelayMin, PMacro175_Entry7_DelaySec, PMacro175_Entry7_TimMin, PMacro175_Entry7_TimSec, PMacro175_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro175_Entry8_DelayMin, PMacro175_Entry8_DelaySec, PMacro175_Entry8_TimMin, PMacro175_Entry8_TimSec, PMacro175_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro175_Entry9_DelayMin, PMacro175_Entry9_DelaySec, PMacro175_Entry9_TimMin, PMacro175_Entry9_TimSec, PMacro175_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro175_Entry10_DelayMin, PMacro175_Entry10_DelaySec, PMacro175_Entry10_TimMin, PMacro175_Entry10_TimSec, PMacro175_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro175_Entry11_DelayMin, PMacro175_Entry11_DelaySec, PMacro175_Entry11_TimMin, PMacro175_Entry11_TimSec, PMacro175_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro175_Entry12_DelayMin, PMacro175_Entry12_DelaySec, PMacro175_Entry12_TimMin, PMacro175_Entry12_TimSec, PMacro175_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro175_Entry13_DelayMin, PMacro175_Entry13_DelaySec, PMacro175_Entry13_TimMin, PMacro175_Entry13_TimSec, PMacro175_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro175_Entry14_DelayMin, PMacro175_Entry14_DelaySec, PMacro175_Entry14_TimMin, PMacro175_Entry14_TimSec, PMacro175_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro175_Entry15_DelayMin, PMacro175_Entry15_DelaySec, PMacro175_Entry15_TimMin, PMacro175_Entry15_TimSec, PMacro175_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR175_STRING};

const struct super_macro Macro176 = {PMacro176_NumEntries,
		         PMacro176_Entry1_DelayMin, PMacro176_Entry1_DelaySec, PMacro176_Entry1_TimMin, PMacro176_Entry1_TimSec, PMacro176_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro176_Entry2_DelayMin, PMacro176_Entry2_DelaySec, PMacro176_Entry2_TimMin, PMacro176_Entry2_TimSec, PMacro176_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro176_Entry3_DelayMin, PMacro176_Entry3_DelaySec, PMacro176_Entry3_TimMin, PMacro176_Entry3_TimSec, PMacro176_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro176_Entry4_DelayMin, PMacro176_Entry4_DelaySec, PMacro176_Entry4_TimMin, PMacro176_Entry4_TimSec, PMacro176_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro176_Entry5_DelayMin, PMacro176_Entry5_DelaySec, PMacro176_Entry5_TimMin, PMacro176_Entry5_TimSec, PMacro176_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro176_Entry6_DelayMin, PMacro176_Entry6_DelaySec, PMacro176_Entry6_TimMin, PMacro176_Entry6_TimSec, PMacro176_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro176_Entry7_DelayMin, PMacro176_Entry7_DelaySec, PMacro176_Entry7_TimMin, PMacro176_Entry7_TimSec, PMacro176_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro176_Entry8_DelayMin, PMacro176_Entry8_DelaySec, PMacro176_Entry8_TimMin, PMacro176_Entry8_TimSec, PMacro176_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro176_Entry9_DelayMin, PMacro176_Entry9_DelaySec, PMacro176_Entry9_TimMin, PMacro176_Entry9_TimSec, PMacro176_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro176_Entry10_DelayMin, PMacro176_Entry10_DelaySec, PMacro176_Entry10_TimMin, PMacro176_Entry10_TimSec, PMacro176_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro176_Entry11_DelayMin, PMacro176_Entry11_DelaySec, PMacro176_Entry11_TimMin, PMacro176_Entry11_TimSec, PMacro176_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro176_Entry12_DelayMin, PMacro176_Entry12_DelaySec, PMacro176_Entry12_TimMin, PMacro176_Entry12_TimSec, PMacro176_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro176_Entry13_DelayMin, PMacro176_Entry13_DelaySec, PMacro176_Entry13_TimMin, PMacro176_Entry13_TimSec, PMacro176_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro176_Entry14_DelayMin, PMacro176_Entry14_DelaySec, PMacro176_Entry14_TimMin, PMacro176_Entry14_TimSec, PMacro176_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro176_Entry15_DelayMin, PMacro176_Entry15_DelaySec, PMacro176_Entry15_TimMin, PMacro176_Entry15_TimSec, PMacro176_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR176_STRING};

const struct super_macro Macro177 = {PMacro177_NumEntries,
		         PMacro177_Entry1_DelayMin, PMacro177_Entry1_DelaySec, PMacro177_Entry1_TimMin, PMacro177_Entry1_TimSec, PMacro177_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro177_Entry2_DelayMin, PMacro177_Entry2_DelaySec, PMacro177_Entry2_TimMin, PMacro177_Entry2_TimSec, PMacro177_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro177_Entry3_DelayMin, PMacro177_Entry3_DelaySec, PMacro177_Entry3_TimMin, PMacro177_Entry3_TimSec, PMacro177_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro177_Entry4_DelayMin, PMacro177_Entry4_DelaySec, PMacro177_Entry4_TimMin, PMacro177_Entry4_TimSec, PMacro177_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro177_Entry5_DelayMin, PMacro177_Entry5_DelaySec, PMacro177_Entry5_TimMin, PMacro177_Entry5_TimSec, PMacro177_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro177_Entry6_DelayMin, PMacro177_Entry6_DelaySec, PMacro177_Entry6_TimMin, PMacro177_Entry6_TimSec, PMacro177_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro177_Entry7_DelayMin, PMacro177_Entry7_DelaySec, PMacro177_Entry7_TimMin, PMacro177_Entry7_TimSec, PMacro177_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro177_Entry8_DelayMin, PMacro177_Entry8_DelaySec, PMacro177_Entry8_TimMin, PMacro177_Entry8_TimSec, PMacro177_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro177_Entry9_DelayMin, PMacro177_Entry9_DelaySec, PMacro177_Entry9_TimMin, PMacro177_Entry9_TimSec, PMacro177_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro177_Entry10_DelayMin, PMacro177_Entry10_DelaySec, PMacro177_Entry10_TimMin, PMacro177_Entry10_TimSec, PMacro177_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro177_Entry11_DelayMin, PMacro177_Entry11_DelaySec, PMacro177_Entry11_TimMin, PMacro177_Entry11_TimSec, PMacro177_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro177_Entry12_DelayMin, PMacro177_Entry12_DelaySec, PMacro177_Entry12_TimMin, PMacro177_Entry12_TimSec, PMacro177_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro177_Entry13_DelayMin, PMacro177_Entry13_DelaySec, PMacro177_Entry13_TimMin, PMacro177_Entry13_TimSec, PMacro177_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro177_Entry14_DelayMin, PMacro177_Entry14_DelaySec, PMacro177_Entry14_TimMin, PMacro177_Entry14_TimSec, PMacro177_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro177_Entry15_DelayMin, PMacro177_Entry15_DelaySec, PMacro177_Entry15_TimMin, PMacro177_Entry15_TimSec, PMacro177_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR177_STRING};

const struct super_macro Macro178 = {PMacro178_NumEntries,
		         PMacro178_Entry1_DelayMin, PMacro178_Entry1_DelaySec, PMacro178_Entry1_TimMin, PMacro178_Entry1_TimSec, PMacro178_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro178_Entry2_DelayMin, PMacro178_Entry2_DelaySec, PMacro178_Entry2_TimMin, PMacro178_Entry2_TimSec, PMacro178_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro178_Entry3_DelayMin, PMacro178_Entry3_DelaySec, PMacro178_Entry3_TimMin, PMacro178_Entry3_TimSec, PMacro178_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro178_Entry4_DelayMin, PMacro178_Entry4_DelaySec, PMacro178_Entry4_TimMin, PMacro178_Entry4_TimSec, PMacro178_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro178_Entry5_DelayMin, PMacro178_Entry5_DelaySec, PMacro178_Entry5_TimMin, PMacro178_Entry5_TimSec, PMacro178_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro178_Entry6_DelayMin, PMacro178_Entry6_DelaySec, PMacro178_Entry6_TimMin, PMacro178_Entry6_TimSec, PMacro178_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro178_Entry7_DelayMin, PMacro178_Entry7_DelaySec, PMacro178_Entry7_TimMin, PMacro178_Entry7_TimSec, PMacro178_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro178_Entry8_DelayMin, PMacro178_Entry8_DelaySec, PMacro178_Entry8_TimMin, PMacro178_Entry8_TimSec, PMacro178_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro178_Entry9_DelayMin, PMacro178_Entry9_DelaySec, PMacro178_Entry9_TimMin, PMacro178_Entry9_TimSec, PMacro178_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro178_Entry10_DelayMin, PMacro178_Entry10_DelaySec, PMacro178_Entry10_TimMin, PMacro178_Entry10_TimSec, PMacro178_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro178_Entry11_DelayMin, PMacro178_Entry11_DelaySec, PMacro178_Entry11_TimMin, PMacro178_Entry11_TimSec, PMacro178_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro178_Entry12_DelayMin, PMacro178_Entry12_DelaySec, PMacro178_Entry12_TimMin, PMacro178_Entry12_TimSec, PMacro178_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro178_Entry13_DelayMin, PMacro178_Entry13_DelaySec, PMacro178_Entry13_TimMin, PMacro178_Entry13_TimSec, PMacro178_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro178_Entry14_DelayMin, PMacro178_Entry14_DelaySec, PMacro178_Entry14_TimMin, PMacro178_Entry14_TimSec, PMacro178_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro178_Entry15_DelayMin, PMacro178_Entry15_DelaySec, PMacro178_Entry15_TimMin, PMacro178_Entry15_TimSec, PMacro178_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR178_STRING};

const struct super_macro Macro179 = {PMacro179_NumEntries,
		         PMacro179_Entry1_DelayMin, PMacro179_Entry1_DelaySec, PMacro179_Entry1_TimMin, PMacro179_Entry1_TimSec, PMacro179_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro179_Entry2_DelayMin, PMacro179_Entry2_DelaySec, PMacro179_Entry2_TimMin, PMacro179_Entry2_TimSec, PMacro179_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro179_Entry3_DelayMin, PMacro179_Entry3_DelaySec, PMacro179_Entry3_TimMin, PMacro179_Entry3_TimSec, PMacro179_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro179_Entry4_DelayMin, PMacro179_Entry4_DelaySec, PMacro179_Entry4_TimMin, PMacro179_Entry4_TimSec, PMacro179_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro179_Entry5_DelayMin, PMacro179_Entry5_DelaySec, PMacro179_Entry5_TimMin, PMacro179_Entry5_TimSec, PMacro179_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro179_Entry6_DelayMin, PMacro179_Entry6_DelaySec, PMacro179_Entry6_TimMin, PMacro179_Entry6_TimSec, PMacro179_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro179_Entry7_DelayMin, PMacro179_Entry7_DelaySec, PMacro179_Entry7_TimMin, PMacro179_Entry7_TimSec, PMacro179_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro179_Entry8_DelayMin, PMacro179_Entry8_DelaySec, PMacro179_Entry8_TimMin, PMacro179_Entry8_TimSec, PMacro179_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro179_Entry9_DelayMin, PMacro179_Entry9_DelaySec, PMacro179_Entry9_TimMin, PMacro179_Entry9_TimSec, PMacro179_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro179_Entry10_DelayMin, PMacro179_Entry10_DelaySec, PMacro179_Entry10_TimMin, PMacro179_Entry10_TimSec, PMacro179_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro179_Entry11_DelayMin, PMacro179_Entry11_DelaySec, PMacro179_Entry11_TimMin, PMacro179_Entry11_TimSec, PMacro179_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro179_Entry12_DelayMin, PMacro179_Entry12_DelaySec, PMacro179_Entry12_TimMin, PMacro179_Entry12_TimSec, PMacro179_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro179_Entry13_DelayMin, PMacro179_Entry13_DelaySec, PMacro179_Entry13_TimMin, PMacro179_Entry13_TimSec, PMacro179_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro179_Entry14_DelayMin, PMacro179_Entry14_DelaySec, PMacro179_Entry14_TimMin, PMacro179_Entry14_TimSec, PMacro179_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro179_Entry15_DelayMin, PMacro179_Entry15_DelaySec, PMacro179_Entry15_TimMin, PMacro179_Entry15_TimSec, PMacro179_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR179_STRING};

const struct super_macro Macro180 = {PMacro180_NumEntries,
		         PMacro180_Entry1_DelayMin, PMacro180_Entry1_DelaySec, PMacro180_Entry1_TimMin, PMacro180_Entry1_TimSec, PMacro180_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro180_Entry2_DelayMin, PMacro180_Entry2_DelaySec, PMacro180_Entry2_TimMin, PMacro180_Entry2_TimSec, PMacro180_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro180_Entry3_DelayMin, PMacro180_Entry3_DelaySec, PMacro180_Entry3_TimMin, PMacro180_Entry3_TimSec, PMacro180_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro180_Entry4_DelayMin, PMacro180_Entry4_DelaySec, PMacro180_Entry4_TimMin, PMacro180_Entry4_TimSec, PMacro180_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro180_Entry5_DelayMin, PMacro180_Entry5_DelaySec, PMacro180_Entry5_TimMin, PMacro180_Entry5_TimSec, PMacro180_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro180_Entry6_DelayMin, PMacro180_Entry6_DelaySec, PMacro180_Entry6_TimMin, PMacro180_Entry6_TimSec, PMacro180_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro180_Entry7_DelayMin, PMacro180_Entry7_DelaySec, PMacro180_Entry7_TimMin, PMacro180_Entry7_TimSec, PMacro180_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro180_Entry8_DelayMin, PMacro180_Entry8_DelaySec, PMacro180_Entry8_TimMin, PMacro180_Entry8_TimSec, PMacro180_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro180_Entry9_DelayMin, PMacro180_Entry9_DelaySec, PMacro180_Entry9_TimMin, PMacro180_Entry9_TimSec, PMacro180_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro180_Entry10_DelayMin, PMacro180_Entry10_DelaySec, PMacro180_Entry10_TimMin, PMacro180_Entry10_TimSec, PMacro180_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro180_Entry11_DelayMin, PMacro180_Entry11_DelaySec, PMacro180_Entry11_TimMin, PMacro180_Entry11_TimSec, PMacro180_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro180_Entry12_DelayMin, PMacro180_Entry12_DelaySec, PMacro180_Entry12_TimMin, PMacro180_Entry12_TimSec, PMacro180_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro180_Entry13_DelayMin, PMacro180_Entry13_DelaySec, PMacro180_Entry13_TimMin, PMacro180_Entry13_TimSec, PMacro180_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro180_Entry14_DelayMin, PMacro180_Entry14_DelaySec, PMacro180_Entry14_TimMin, PMacro180_Entry14_TimSec, PMacro180_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro180_Entry15_DelayMin, PMacro180_Entry15_DelaySec, PMacro180_Entry15_TimMin, PMacro180_Entry15_TimSec, PMacro180_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR180_STRING};

const struct super_macro Macro181 = {PMacro181_NumEntries,
		         PMacro181_Entry1_DelayMin, PMacro181_Entry1_DelaySec, PMacro181_Entry1_TimMin, PMacro181_Entry1_TimSec, PMacro181_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro181_Entry2_DelayMin, PMacro181_Entry2_DelaySec, PMacro181_Entry2_TimMin, PMacro181_Entry2_TimSec, PMacro181_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro181_Entry3_DelayMin, PMacro181_Entry3_DelaySec, PMacro181_Entry3_TimMin, PMacro181_Entry3_TimSec, PMacro181_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro181_Entry4_DelayMin, PMacro181_Entry4_DelaySec, PMacro181_Entry4_TimMin, PMacro181_Entry4_TimSec, PMacro181_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro181_Entry5_DelayMin, PMacro181_Entry5_DelaySec, PMacro181_Entry5_TimMin, PMacro181_Entry5_TimSec, PMacro181_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro181_Entry6_DelayMin, PMacro181_Entry6_DelaySec, PMacro181_Entry6_TimMin, PMacro181_Entry6_TimSec, PMacro181_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro181_Entry7_DelayMin, PMacro181_Entry7_DelaySec, PMacro181_Entry7_TimMin, PMacro181_Entry7_TimSec, PMacro181_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro181_Entry8_DelayMin, PMacro181_Entry8_DelaySec, PMacro181_Entry8_TimMin, PMacro181_Entry8_TimSec, PMacro181_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro181_Entry9_DelayMin, PMacro181_Entry9_DelaySec, PMacro181_Entry9_TimMin, PMacro181_Entry9_TimSec, PMacro181_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro181_Entry10_DelayMin, PMacro181_Entry10_DelaySec, PMacro181_Entry10_TimMin, PMacro181_Entry10_TimSec, PMacro181_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro181_Entry11_DelayMin, PMacro181_Entry11_DelaySec, PMacro181_Entry11_TimMin, PMacro181_Entry11_TimSec, PMacro181_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro181_Entry12_DelayMin, PMacro181_Entry12_DelaySec, PMacro181_Entry12_TimMin, PMacro181_Entry12_TimSec, PMacro181_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro181_Entry13_DelayMin, PMacro181_Entry13_DelaySec, PMacro181_Entry13_TimMin, PMacro181_Entry13_TimSec, PMacro181_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro181_Entry14_DelayMin, PMacro181_Entry14_DelaySec, PMacro181_Entry14_TimMin, PMacro181_Entry14_TimSec, PMacro181_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro181_Entry15_DelayMin, PMacro181_Entry15_DelaySec, PMacro181_Entry15_TimMin, PMacro181_Entry15_TimSec, PMacro181_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR181_STRING};

const struct super_macro Macro182 = {PMacro182_NumEntries,
		         PMacro182_Entry1_DelayMin, PMacro182_Entry1_DelaySec, PMacro182_Entry1_TimMin, PMacro182_Entry1_TimSec, PMacro182_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro182_Entry2_DelayMin, PMacro182_Entry2_DelaySec, PMacro182_Entry2_TimMin, PMacro182_Entry2_TimSec, PMacro182_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro182_Entry3_DelayMin, PMacro182_Entry3_DelaySec, PMacro182_Entry3_TimMin, PMacro182_Entry3_TimSec, PMacro182_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro182_Entry4_DelayMin, PMacro182_Entry4_DelaySec, PMacro182_Entry4_TimMin, PMacro182_Entry4_TimSec, PMacro182_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro182_Entry5_DelayMin, PMacro182_Entry5_DelaySec, PMacro182_Entry5_TimMin, PMacro182_Entry5_TimSec, PMacro182_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro182_Entry6_DelayMin, PMacro182_Entry6_DelaySec, PMacro182_Entry6_TimMin, PMacro182_Entry6_TimSec, PMacro182_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro182_Entry7_DelayMin, PMacro182_Entry7_DelaySec, PMacro182_Entry7_TimMin, PMacro182_Entry7_TimSec, PMacro182_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro182_Entry8_DelayMin, PMacro182_Entry8_DelaySec, PMacro182_Entry8_TimMin, PMacro182_Entry8_TimSec, PMacro182_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro182_Entry9_DelayMin, PMacro182_Entry9_DelaySec, PMacro182_Entry9_TimMin, PMacro182_Entry9_TimSec, PMacro182_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro182_Entry10_DelayMin, PMacro182_Entry10_DelaySec, PMacro182_Entry10_TimMin, PMacro182_Entry10_TimSec, PMacro182_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro182_Entry11_DelayMin, PMacro182_Entry11_DelaySec, PMacro182_Entry11_TimMin, PMacro182_Entry11_TimSec, PMacro182_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro182_Entry12_DelayMin, PMacro182_Entry12_DelaySec, PMacro182_Entry12_TimMin, PMacro182_Entry12_TimSec, PMacro182_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro182_Entry13_DelayMin, PMacro182_Entry13_DelaySec, PMacro182_Entry13_TimMin, PMacro182_Entry13_TimSec, PMacro182_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro182_Entry14_DelayMin, PMacro182_Entry14_DelaySec, PMacro182_Entry14_TimMin, PMacro182_Entry14_TimSec, PMacro182_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro182_Entry15_DelayMin, PMacro182_Entry15_DelaySec, PMacro182_Entry15_TimMin, PMacro182_Entry15_TimSec, PMacro182_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR182_STRING};

const struct super_macro Macro183 = {PMacro183_NumEntries,
		         PMacro183_Entry1_DelayMin, PMacro183_Entry1_DelaySec, PMacro183_Entry1_TimMin, PMacro183_Entry1_TimSec, PMacro183_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro183_Entry2_DelayMin, PMacro183_Entry2_DelaySec, PMacro183_Entry2_TimMin, PMacro183_Entry2_TimSec, PMacro183_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro183_Entry3_DelayMin, PMacro183_Entry3_DelaySec, PMacro183_Entry3_TimMin, PMacro183_Entry3_TimSec, PMacro183_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro183_Entry4_DelayMin, PMacro183_Entry4_DelaySec, PMacro183_Entry4_TimMin, PMacro183_Entry4_TimSec, PMacro183_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro183_Entry5_DelayMin, PMacro183_Entry5_DelaySec, PMacro183_Entry5_TimMin, PMacro183_Entry5_TimSec, PMacro183_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro183_Entry6_DelayMin, PMacro183_Entry6_DelaySec, PMacro183_Entry6_TimMin, PMacro183_Entry6_TimSec, PMacro183_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro183_Entry7_DelayMin, PMacro183_Entry7_DelaySec, PMacro183_Entry7_TimMin, PMacro183_Entry7_TimSec, PMacro183_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro183_Entry8_DelayMin, PMacro183_Entry8_DelaySec, PMacro183_Entry8_TimMin, PMacro183_Entry8_TimSec, PMacro183_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro183_Entry9_DelayMin, PMacro183_Entry9_DelaySec, PMacro183_Entry9_TimMin, PMacro183_Entry9_TimSec, PMacro183_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro183_Entry10_DelayMin, PMacro183_Entry10_DelaySec, PMacro183_Entry10_TimMin, PMacro183_Entry10_TimSec, PMacro183_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro183_Entry11_DelayMin, PMacro183_Entry11_DelaySec, PMacro183_Entry11_TimMin, PMacro183_Entry11_TimSec, PMacro183_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro183_Entry12_DelayMin, PMacro183_Entry12_DelaySec, PMacro183_Entry12_TimMin, PMacro183_Entry12_TimSec, PMacro183_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro183_Entry13_DelayMin, PMacro183_Entry13_DelaySec, PMacro183_Entry13_TimMin, PMacro183_Entry13_TimSec, PMacro183_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro183_Entry14_DelayMin, PMacro183_Entry14_DelaySec, PMacro183_Entry14_TimMin, PMacro183_Entry14_TimSec, PMacro183_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro183_Entry15_DelayMin, PMacro183_Entry15_DelaySec, PMacro183_Entry15_TimMin, PMacro183_Entry15_TimSec, PMacro183_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR183_STRING};

const struct super_macro Macro184 = {PMacro184_NumEntries,
		         PMacro184_Entry1_DelayMin, PMacro184_Entry1_DelaySec, PMacro184_Entry1_TimMin, PMacro184_Entry1_TimSec, PMacro184_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro184_Entry2_DelayMin, PMacro184_Entry2_DelaySec, PMacro184_Entry2_TimMin, PMacro184_Entry2_TimSec, PMacro184_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro184_Entry3_DelayMin, PMacro184_Entry3_DelaySec, PMacro184_Entry3_TimMin, PMacro184_Entry3_TimSec, PMacro184_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro184_Entry4_DelayMin, PMacro184_Entry4_DelaySec, PMacro184_Entry4_TimMin, PMacro184_Entry4_TimSec, PMacro184_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro184_Entry5_DelayMin, PMacro184_Entry5_DelaySec, PMacro184_Entry5_TimMin, PMacro184_Entry5_TimSec, PMacro184_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro184_Entry6_DelayMin, PMacro184_Entry6_DelaySec, PMacro184_Entry6_TimMin, PMacro184_Entry6_TimSec, PMacro184_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro184_Entry7_DelayMin, PMacro184_Entry7_DelaySec, PMacro184_Entry7_TimMin, PMacro184_Entry7_TimSec, PMacro184_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro184_Entry8_DelayMin, PMacro184_Entry8_DelaySec, PMacro184_Entry8_TimMin, PMacro184_Entry8_TimSec, PMacro184_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro184_Entry9_DelayMin, PMacro184_Entry9_DelaySec, PMacro184_Entry9_TimMin, PMacro184_Entry9_TimSec, PMacro184_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro184_Entry10_DelayMin, PMacro184_Entry10_DelaySec, PMacro184_Entry10_TimMin, PMacro184_Entry10_TimSec, PMacro184_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro184_Entry11_DelayMin, PMacro184_Entry11_DelaySec, PMacro184_Entry11_TimMin, PMacro184_Entry11_TimSec, PMacro184_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro184_Entry12_DelayMin, PMacro184_Entry12_DelaySec, PMacro184_Entry12_TimMin, PMacro184_Entry12_TimSec, PMacro184_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro184_Entry13_DelayMin, PMacro184_Entry13_DelaySec, PMacro184_Entry13_TimMin, PMacro184_Entry13_TimSec, PMacro184_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro184_Entry14_DelayMin, PMacro184_Entry14_DelaySec, PMacro184_Entry14_TimMin, PMacro184_Entry14_TimSec, PMacro184_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro184_Entry15_DelayMin, PMacro184_Entry15_DelaySec, PMacro184_Entry15_TimMin, PMacro184_Entry15_TimSec, PMacro184_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR184_STRING};

const struct super_macro Macro185 = {PMacro185_NumEntries,
		         PMacro185_Entry1_DelayMin, PMacro185_Entry1_DelaySec, PMacro185_Entry1_TimMin, PMacro185_Entry1_TimSec, PMacro185_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro185_Entry2_DelayMin, PMacro185_Entry2_DelaySec, PMacro185_Entry2_TimMin, PMacro185_Entry2_TimSec, PMacro185_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro185_Entry3_DelayMin, PMacro185_Entry3_DelaySec, PMacro185_Entry3_TimMin, PMacro185_Entry3_TimSec, PMacro185_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro185_Entry4_DelayMin, PMacro185_Entry4_DelaySec, PMacro185_Entry4_TimMin, PMacro185_Entry4_TimSec, PMacro185_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro185_Entry5_DelayMin, PMacro185_Entry5_DelaySec, PMacro185_Entry5_TimMin, PMacro185_Entry5_TimSec, PMacro185_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro185_Entry6_DelayMin, PMacro185_Entry6_DelaySec, PMacro185_Entry6_TimMin, PMacro185_Entry6_TimSec, PMacro185_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro185_Entry7_DelayMin, PMacro185_Entry7_DelaySec, PMacro185_Entry7_TimMin, PMacro185_Entry7_TimSec, PMacro185_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro185_Entry8_DelayMin, PMacro185_Entry8_DelaySec, PMacro185_Entry8_TimMin, PMacro185_Entry8_TimSec, PMacro185_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro185_Entry9_DelayMin, PMacro185_Entry9_DelaySec, PMacro185_Entry9_TimMin, PMacro185_Entry9_TimSec, PMacro185_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro185_Entry10_DelayMin, PMacro185_Entry10_DelaySec, PMacro185_Entry10_TimMin, PMacro185_Entry10_TimSec, PMacro185_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro185_Entry11_DelayMin, PMacro185_Entry11_DelaySec, PMacro185_Entry11_TimMin, PMacro185_Entry11_TimSec, PMacro185_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro185_Entry12_DelayMin, PMacro185_Entry12_DelaySec, PMacro185_Entry12_TimMin, PMacro185_Entry12_TimSec, PMacro185_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro185_Entry13_DelayMin, PMacro185_Entry13_DelaySec, PMacro185_Entry13_TimMin, PMacro185_Entry13_TimSec, PMacro185_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro185_Entry14_DelayMin, PMacro185_Entry14_DelaySec, PMacro185_Entry14_TimMin, PMacro185_Entry14_TimSec, PMacro185_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro185_Entry15_DelayMin, PMacro185_Entry15_DelaySec, PMacro185_Entry15_TimMin, PMacro185_Entry15_TimSec, PMacro185_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR185_STRING};

const struct super_macro Macro186 = {PMacro186_NumEntries,
		         PMacro186_Entry1_DelayMin, PMacro186_Entry1_DelaySec, PMacro186_Entry1_TimMin, PMacro186_Entry1_TimSec, PMacro186_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro186_Entry2_DelayMin, PMacro186_Entry2_DelaySec, PMacro186_Entry2_TimMin, PMacro186_Entry2_TimSec, PMacro186_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro186_Entry3_DelayMin, PMacro186_Entry3_DelaySec, PMacro186_Entry3_TimMin, PMacro186_Entry3_TimSec, PMacro186_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro186_Entry4_DelayMin, PMacro186_Entry4_DelaySec, PMacro186_Entry4_TimMin, PMacro186_Entry4_TimSec, PMacro186_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro186_Entry5_DelayMin, PMacro186_Entry5_DelaySec, PMacro186_Entry5_TimMin, PMacro186_Entry5_TimSec, PMacro186_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro186_Entry6_DelayMin, PMacro186_Entry6_DelaySec, PMacro186_Entry6_TimMin, PMacro186_Entry6_TimSec, PMacro186_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro186_Entry7_DelayMin, PMacro186_Entry7_DelaySec, PMacro186_Entry7_TimMin, PMacro186_Entry7_TimSec, PMacro186_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro186_Entry8_DelayMin, PMacro186_Entry8_DelaySec, PMacro186_Entry8_TimMin, PMacro186_Entry8_TimSec, PMacro186_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro186_Entry9_DelayMin, PMacro186_Entry9_DelaySec, PMacro186_Entry9_TimMin, PMacro186_Entry9_TimSec, PMacro186_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro186_Entry10_DelayMin, PMacro186_Entry10_DelaySec, PMacro186_Entry10_TimMin, PMacro186_Entry10_TimSec, PMacro186_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro186_Entry11_DelayMin, PMacro186_Entry11_DelaySec, PMacro186_Entry11_TimMin, PMacro186_Entry11_TimSec, PMacro186_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro186_Entry12_DelayMin, PMacro186_Entry12_DelaySec, PMacro186_Entry12_TimMin, PMacro186_Entry12_TimSec, PMacro186_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro186_Entry13_DelayMin, PMacro186_Entry13_DelaySec, PMacro186_Entry13_TimMin, PMacro186_Entry13_TimSec, PMacro186_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro186_Entry14_DelayMin, PMacro186_Entry14_DelaySec, PMacro186_Entry14_TimMin, PMacro186_Entry14_TimSec, PMacro186_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro186_Entry15_DelayMin, PMacro186_Entry15_DelaySec, PMacro186_Entry15_TimMin, PMacro186_Entry15_TimSec, PMacro186_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR186_STRING};

const struct super_macro Macro187 = {PMacro187_NumEntries,
		         PMacro187_Entry1_DelayMin, PMacro187_Entry1_DelaySec, PMacro187_Entry1_TimMin, PMacro187_Entry1_TimSec, PMacro187_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro187_Entry2_DelayMin, PMacro187_Entry2_DelaySec, PMacro187_Entry2_TimMin, PMacro187_Entry2_TimSec, PMacro187_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro187_Entry3_DelayMin, PMacro187_Entry3_DelaySec, PMacro187_Entry3_TimMin, PMacro187_Entry3_TimSec, PMacro187_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro187_Entry4_DelayMin, PMacro187_Entry4_DelaySec, PMacro187_Entry4_TimMin, PMacro187_Entry4_TimSec, PMacro187_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro187_Entry5_DelayMin, PMacro187_Entry5_DelaySec, PMacro187_Entry5_TimMin, PMacro187_Entry5_TimSec, PMacro187_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro187_Entry6_DelayMin, PMacro187_Entry6_DelaySec, PMacro187_Entry6_TimMin, PMacro187_Entry6_TimSec, PMacro187_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro187_Entry7_DelayMin, PMacro187_Entry7_DelaySec, PMacro187_Entry7_TimMin, PMacro187_Entry7_TimSec, PMacro187_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro187_Entry8_DelayMin, PMacro187_Entry8_DelaySec, PMacro187_Entry8_TimMin, PMacro187_Entry8_TimSec, PMacro187_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro187_Entry9_DelayMin, PMacro187_Entry9_DelaySec, PMacro187_Entry9_TimMin, PMacro187_Entry9_TimSec, PMacro187_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro187_Entry10_DelayMin, PMacro187_Entry10_DelaySec, PMacro187_Entry10_TimMin, PMacro187_Entry10_TimSec, PMacro187_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro187_Entry11_DelayMin, PMacro187_Entry11_DelaySec, PMacro187_Entry11_TimMin, PMacro187_Entry11_TimSec, PMacro187_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro187_Entry12_DelayMin, PMacro187_Entry12_DelaySec, PMacro187_Entry12_TimMin, PMacro187_Entry12_TimSec, PMacro187_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro187_Entry13_DelayMin, PMacro187_Entry13_DelaySec, PMacro187_Entry13_TimMin, PMacro187_Entry13_TimSec, PMacro187_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro187_Entry14_DelayMin, PMacro187_Entry14_DelaySec, PMacro187_Entry14_TimMin, PMacro187_Entry14_TimSec, PMacro187_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro187_Entry15_DelayMin, PMacro187_Entry15_DelaySec, PMacro187_Entry15_TimMin, PMacro187_Entry15_TimSec, PMacro187_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR187_STRING};

const struct super_macro Macro188 = {PMacro188_NumEntries,
		         PMacro188_Entry1_DelayMin, PMacro188_Entry1_DelaySec, PMacro188_Entry1_TimMin, PMacro188_Entry1_TimSec, PMacro188_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro188_Entry2_DelayMin, PMacro188_Entry2_DelaySec, PMacro188_Entry2_TimMin, PMacro188_Entry2_TimSec, PMacro188_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro188_Entry3_DelayMin, PMacro188_Entry3_DelaySec, PMacro188_Entry3_TimMin, PMacro188_Entry3_TimSec, PMacro188_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro188_Entry4_DelayMin, PMacro188_Entry4_DelaySec, PMacro188_Entry4_TimMin, PMacro188_Entry4_TimSec, PMacro188_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro188_Entry5_DelayMin, PMacro188_Entry5_DelaySec, PMacro188_Entry5_TimMin, PMacro188_Entry5_TimSec, PMacro188_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro188_Entry6_DelayMin, PMacro188_Entry6_DelaySec, PMacro188_Entry6_TimMin, PMacro188_Entry6_TimSec, PMacro188_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro188_Entry7_DelayMin, PMacro188_Entry7_DelaySec, PMacro188_Entry7_TimMin, PMacro188_Entry7_TimSec, PMacro188_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro188_Entry8_DelayMin, PMacro188_Entry8_DelaySec, PMacro188_Entry8_TimMin, PMacro188_Entry8_TimSec, PMacro188_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro188_Entry9_DelayMin, PMacro188_Entry9_DelaySec, PMacro188_Entry9_TimMin, PMacro188_Entry9_TimSec, PMacro188_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro188_Entry10_DelayMin, PMacro188_Entry10_DelaySec, PMacro188_Entry10_TimMin, PMacro188_Entry10_TimSec, PMacro188_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro188_Entry11_DelayMin, PMacro188_Entry11_DelaySec, PMacro188_Entry11_TimMin, PMacro188_Entry11_TimSec, PMacro188_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro188_Entry12_DelayMin, PMacro188_Entry12_DelaySec, PMacro188_Entry12_TimMin, PMacro188_Entry12_TimSec, PMacro188_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro188_Entry13_DelayMin, PMacro188_Entry13_DelaySec, PMacro188_Entry13_TimMin, PMacro188_Entry13_TimSec, PMacro188_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro188_Entry14_DelayMin, PMacro188_Entry14_DelaySec, PMacro188_Entry14_TimMin, PMacro188_Entry14_TimSec, PMacro188_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro188_Entry15_DelayMin, PMacro188_Entry15_DelaySec, PMacro188_Entry15_TimMin, PMacro188_Entry15_TimSec, PMacro188_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR188_STRING};

const struct super_macro Macro189 = {PMacro189_NumEntries,
		         PMacro189_Entry1_DelayMin, PMacro189_Entry1_DelaySec, PMacro189_Entry1_TimMin, PMacro189_Entry1_TimSec, PMacro189_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro189_Entry2_DelayMin, PMacro189_Entry2_DelaySec, PMacro189_Entry2_TimMin, PMacro189_Entry2_TimSec, PMacro189_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro189_Entry3_DelayMin, PMacro189_Entry3_DelaySec, PMacro189_Entry3_TimMin, PMacro189_Entry3_TimSec, PMacro189_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro189_Entry4_DelayMin, PMacro189_Entry4_DelaySec, PMacro189_Entry4_TimMin, PMacro189_Entry4_TimSec, PMacro189_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro189_Entry5_DelayMin, PMacro189_Entry5_DelaySec, PMacro189_Entry5_TimMin, PMacro189_Entry5_TimSec, PMacro189_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro189_Entry6_DelayMin, PMacro189_Entry6_DelaySec, PMacro189_Entry6_TimMin, PMacro189_Entry6_TimSec, PMacro189_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro189_Entry7_DelayMin, PMacro189_Entry7_DelaySec, PMacro189_Entry7_TimMin, PMacro189_Entry7_TimSec, PMacro189_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro189_Entry8_DelayMin, PMacro189_Entry8_DelaySec, PMacro189_Entry8_TimMin, PMacro189_Entry8_TimSec, PMacro189_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro189_Entry9_DelayMin, PMacro189_Entry9_DelaySec, PMacro189_Entry9_TimMin, PMacro189_Entry9_TimSec, PMacro189_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro189_Entry10_DelayMin, PMacro189_Entry10_DelaySec, PMacro189_Entry10_TimMin, PMacro189_Entry10_TimSec, PMacro189_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro189_Entry11_DelayMin, PMacro189_Entry11_DelaySec, PMacro189_Entry11_TimMin, PMacro189_Entry11_TimSec, PMacro189_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro189_Entry12_DelayMin, PMacro189_Entry12_DelaySec, PMacro189_Entry12_TimMin, PMacro189_Entry12_TimSec, PMacro189_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro189_Entry13_DelayMin, PMacro189_Entry13_DelaySec, PMacro189_Entry13_TimMin, PMacro189_Entry13_TimSec, PMacro189_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro189_Entry14_DelayMin, PMacro189_Entry14_DelaySec, PMacro189_Entry14_TimMin, PMacro189_Entry14_TimSec, PMacro189_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro189_Entry15_DelayMin, PMacro189_Entry15_DelaySec, PMacro189_Entry15_TimMin, PMacro189_Entry15_TimSec, PMacro189_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR189_STRING};

const struct super_macro Macro190 = {PMacro190_NumEntries,
		         PMacro190_Entry1_DelayMin, PMacro190_Entry1_DelaySec, PMacro190_Entry1_TimMin, PMacro190_Entry1_TimSec, PMacro190_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro190_Entry2_DelayMin, PMacro190_Entry2_DelaySec, PMacro190_Entry2_TimMin, PMacro190_Entry2_TimSec, PMacro190_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro190_Entry3_DelayMin, PMacro190_Entry3_DelaySec, PMacro190_Entry3_TimMin, PMacro190_Entry3_TimSec, PMacro190_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro190_Entry4_DelayMin, PMacro190_Entry4_DelaySec, PMacro190_Entry4_TimMin, PMacro190_Entry4_TimSec, PMacro190_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro190_Entry5_DelayMin, PMacro190_Entry5_DelaySec, PMacro190_Entry5_TimMin, PMacro190_Entry5_TimSec, PMacro190_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro190_Entry6_DelayMin, PMacro190_Entry6_DelaySec, PMacro190_Entry6_TimMin, PMacro190_Entry6_TimSec, PMacro190_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro190_Entry7_DelayMin, PMacro190_Entry7_DelaySec, PMacro190_Entry7_TimMin, PMacro190_Entry7_TimSec, PMacro190_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro190_Entry8_DelayMin, PMacro190_Entry8_DelaySec, PMacro190_Entry8_TimMin, PMacro190_Entry8_TimSec, PMacro190_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro190_Entry9_DelayMin, PMacro190_Entry9_DelaySec, PMacro190_Entry9_TimMin, PMacro190_Entry9_TimSec, PMacro190_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro190_Entry10_DelayMin, PMacro190_Entry10_DelaySec, PMacro190_Entry10_TimMin, PMacro190_Entry10_TimSec, PMacro190_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro190_Entry11_DelayMin, PMacro190_Entry11_DelaySec, PMacro190_Entry11_TimMin, PMacro190_Entry11_TimSec, PMacro190_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro190_Entry12_DelayMin, PMacro190_Entry12_DelaySec, PMacro190_Entry12_TimMin, PMacro190_Entry12_TimSec, PMacro190_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro190_Entry13_DelayMin, PMacro190_Entry13_DelaySec, PMacro190_Entry13_TimMin, PMacro190_Entry13_TimSec, PMacro190_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro190_Entry14_DelayMin, PMacro190_Entry14_DelaySec, PMacro190_Entry14_TimMin, PMacro190_Entry14_TimSec, PMacro190_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro190_Entry15_DelayMin, PMacro190_Entry15_DelaySec, PMacro190_Entry15_TimMin, PMacro190_Entry15_TimSec, PMacro190_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR190_STRING};

const struct super_macro Macro191 = {PMacro191_NumEntries,
		         PMacro191_Entry1_DelayMin, PMacro191_Entry1_DelaySec, PMacro191_Entry1_TimMin, PMacro191_Entry1_TimSec, PMacro191_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro191_Entry2_DelayMin, PMacro191_Entry2_DelaySec, PMacro191_Entry2_TimMin, PMacro191_Entry2_TimSec, PMacro191_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro191_Entry3_DelayMin, PMacro191_Entry3_DelaySec, PMacro191_Entry3_TimMin, PMacro191_Entry3_TimSec, PMacro191_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro191_Entry4_DelayMin, PMacro191_Entry4_DelaySec, PMacro191_Entry4_TimMin, PMacro191_Entry4_TimSec, PMacro191_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro191_Entry5_DelayMin, PMacro191_Entry5_DelaySec, PMacro191_Entry5_TimMin, PMacro191_Entry5_TimSec, PMacro191_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro191_Entry6_DelayMin, PMacro191_Entry6_DelaySec, PMacro191_Entry6_TimMin, PMacro191_Entry6_TimSec, PMacro191_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro191_Entry7_DelayMin, PMacro191_Entry7_DelaySec, PMacro191_Entry7_TimMin, PMacro191_Entry7_TimSec, PMacro191_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro191_Entry8_DelayMin, PMacro191_Entry8_DelaySec, PMacro191_Entry8_TimMin, PMacro191_Entry8_TimSec, PMacro191_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro191_Entry9_DelayMin, PMacro191_Entry9_DelaySec, PMacro191_Entry9_TimMin, PMacro191_Entry9_TimSec, PMacro191_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro191_Entry10_DelayMin, PMacro191_Entry10_DelaySec, PMacro191_Entry10_TimMin, PMacro191_Entry10_TimSec, PMacro191_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro191_Entry11_DelayMin, PMacro191_Entry11_DelaySec, PMacro191_Entry11_TimMin, PMacro191_Entry11_TimSec, PMacro191_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro191_Entry12_DelayMin, PMacro191_Entry12_DelaySec, PMacro191_Entry12_TimMin, PMacro191_Entry12_TimSec, PMacro191_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro191_Entry13_DelayMin, PMacro191_Entry13_DelaySec, PMacro191_Entry13_TimMin, PMacro191_Entry13_TimSec, PMacro191_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro191_Entry14_DelayMin, PMacro191_Entry14_DelaySec, PMacro191_Entry14_TimMin, PMacro191_Entry14_TimSec, PMacro191_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro191_Entry15_DelayMin, PMacro191_Entry15_DelaySec, PMacro191_Entry15_TimMin, PMacro191_Entry15_TimSec, PMacro191_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR191_STRING};

const struct super_macro Macro192 = {PMacro192_NumEntries,
		         PMacro192_Entry1_DelayMin, PMacro192_Entry1_DelaySec, PMacro192_Entry1_TimMin, PMacro192_Entry1_TimSec, PMacro192_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro192_Entry2_DelayMin, PMacro192_Entry2_DelaySec, PMacro192_Entry2_TimMin, PMacro192_Entry2_TimSec, PMacro192_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro192_Entry3_DelayMin, PMacro192_Entry3_DelaySec, PMacro192_Entry3_TimMin, PMacro192_Entry3_TimSec, PMacro192_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro192_Entry4_DelayMin, PMacro192_Entry4_DelaySec, PMacro192_Entry4_TimMin, PMacro192_Entry4_TimSec, PMacro192_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro192_Entry5_DelayMin, PMacro192_Entry5_DelaySec, PMacro192_Entry5_TimMin, PMacro192_Entry5_TimSec, PMacro192_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro192_Entry6_DelayMin, PMacro192_Entry6_DelaySec, PMacro192_Entry6_TimMin, PMacro192_Entry6_TimSec, PMacro192_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro192_Entry7_DelayMin, PMacro192_Entry7_DelaySec, PMacro192_Entry7_TimMin, PMacro192_Entry7_TimSec, PMacro192_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro192_Entry8_DelayMin, PMacro192_Entry8_DelaySec, PMacro192_Entry8_TimMin, PMacro192_Entry8_TimSec, PMacro192_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro192_Entry9_DelayMin, PMacro192_Entry9_DelaySec, PMacro192_Entry9_TimMin, PMacro192_Entry9_TimSec, PMacro192_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro192_Entry10_DelayMin, PMacro192_Entry10_DelaySec, PMacro192_Entry10_TimMin, PMacro192_Entry10_TimSec, PMacro192_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro192_Entry11_DelayMin, PMacro192_Entry11_DelaySec, PMacro192_Entry11_TimMin, PMacro192_Entry11_TimSec, PMacro192_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro192_Entry12_DelayMin, PMacro192_Entry12_DelaySec, PMacro192_Entry12_TimMin, PMacro192_Entry12_TimSec, PMacro192_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro192_Entry13_DelayMin, PMacro192_Entry13_DelaySec, PMacro192_Entry13_TimMin, PMacro192_Entry13_TimSec, PMacro192_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro192_Entry14_DelayMin, PMacro192_Entry14_DelaySec, PMacro192_Entry14_TimMin, PMacro192_Entry14_TimSec, PMacro192_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro192_Entry15_DelayMin, PMacro192_Entry15_DelaySec, PMacro192_Entry15_TimMin, PMacro192_Entry15_TimSec, PMacro192_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR192_STRING};

const struct super_macro Macro193 = {PMacro193_NumEntries,
		         PMacro193_Entry1_DelayMin, PMacro193_Entry1_DelaySec, PMacro193_Entry1_TimMin, PMacro193_Entry1_TimSec, PMacro193_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro193_Entry2_DelayMin, PMacro193_Entry2_DelaySec, PMacro193_Entry2_TimMin, PMacro193_Entry2_TimSec, PMacro193_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro193_Entry3_DelayMin, PMacro193_Entry3_DelaySec, PMacro193_Entry3_TimMin, PMacro193_Entry3_TimSec, PMacro193_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro193_Entry4_DelayMin, PMacro193_Entry4_DelaySec, PMacro193_Entry4_TimMin, PMacro193_Entry4_TimSec, PMacro193_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro193_Entry5_DelayMin, PMacro193_Entry5_DelaySec, PMacro193_Entry5_TimMin, PMacro193_Entry5_TimSec, PMacro193_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro193_Entry6_DelayMin, PMacro193_Entry6_DelaySec, PMacro193_Entry6_TimMin, PMacro193_Entry6_TimSec, PMacro193_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro193_Entry7_DelayMin, PMacro193_Entry7_DelaySec, PMacro193_Entry7_TimMin, PMacro193_Entry7_TimSec, PMacro193_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro193_Entry8_DelayMin, PMacro193_Entry8_DelaySec, PMacro193_Entry8_TimMin, PMacro193_Entry8_TimSec, PMacro193_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro193_Entry9_DelayMin, PMacro193_Entry9_DelaySec, PMacro193_Entry9_TimMin, PMacro193_Entry9_TimSec, PMacro193_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro193_Entry10_DelayMin, PMacro193_Entry10_DelaySec, PMacro193_Entry10_TimMin, PMacro193_Entry10_TimSec, PMacro193_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro193_Entry11_DelayMin, PMacro193_Entry11_DelaySec, PMacro193_Entry11_TimMin, PMacro193_Entry11_TimSec, PMacro193_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro193_Entry12_DelayMin, PMacro193_Entry12_DelaySec, PMacro193_Entry12_TimMin, PMacro193_Entry12_TimSec, PMacro193_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro193_Entry13_DelayMin, PMacro193_Entry13_DelaySec, PMacro193_Entry13_TimMin, PMacro193_Entry13_TimSec, PMacro193_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro193_Entry14_DelayMin, PMacro193_Entry14_DelaySec, PMacro193_Entry14_TimMin, PMacro193_Entry14_TimSec, PMacro193_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro193_Entry15_DelayMin, PMacro193_Entry15_DelaySec, PMacro193_Entry15_TimMin, PMacro193_Entry15_TimSec, PMacro193_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR193_STRING};

const struct super_macro Macro194 = {PMacro194_NumEntries,
		         PMacro194_Entry1_DelayMin, PMacro194_Entry1_DelaySec, PMacro194_Entry1_TimMin, PMacro194_Entry1_TimSec, PMacro194_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro194_Entry2_DelayMin, PMacro194_Entry2_DelaySec, PMacro194_Entry2_TimMin, PMacro194_Entry2_TimSec, PMacro194_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro194_Entry3_DelayMin, PMacro194_Entry3_DelaySec, PMacro194_Entry3_TimMin, PMacro194_Entry3_TimSec, PMacro194_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro194_Entry4_DelayMin, PMacro194_Entry4_DelaySec, PMacro194_Entry4_TimMin, PMacro194_Entry4_TimSec, PMacro194_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro194_Entry5_DelayMin, PMacro194_Entry5_DelaySec, PMacro194_Entry5_TimMin, PMacro194_Entry5_TimSec, PMacro194_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro194_Entry6_DelayMin, PMacro194_Entry6_DelaySec, PMacro194_Entry6_TimMin, PMacro194_Entry6_TimSec, PMacro194_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro194_Entry7_DelayMin, PMacro194_Entry7_DelaySec, PMacro194_Entry7_TimMin, PMacro194_Entry7_TimSec, PMacro194_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro194_Entry8_DelayMin, PMacro194_Entry8_DelaySec, PMacro194_Entry8_TimMin, PMacro194_Entry8_TimSec, PMacro194_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro194_Entry9_DelayMin, PMacro194_Entry9_DelaySec, PMacro194_Entry9_TimMin, PMacro194_Entry9_TimSec, PMacro194_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro194_Entry10_DelayMin, PMacro194_Entry10_DelaySec, PMacro194_Entry10_TimMin, PMacro194_Entry10_TimSec, PMacro194_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro194_Entry11_DelayMin, PMacro194_Entry11_DelaySec, PMacro194_Entry11_TimMin, PMacro194_Entry11_TimSec, PMacro194_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro194_Entry12_DelayMin, PMacro194_Entry12_DelaySec, PMacro194_Entry12_TimMin, PMacro194_Entry12_TimSec, PMacro194_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro194_Entry13_DelayMin, PMacro194_Entry13_DelaySec, PMacro194_Entry13_TimMin, PMacro194_Entry13_TimSec, PMacro194_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro194_Entry14_DelayMin, PMacro194_Entry14_DelaySec, PMacro194_Entry14_TimMin, PMacro194_Entry14_TimSec, PMacro194_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro194_Entry15_DelayMin, PMacro194_Entry15_DelaySec, PMacro194_Entry15_TimMin, PMacro194_Entry15_TimSec, PMacro194_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR194_STRING};

const struct super_macro Macro195 = {PMacro195_NumEntries,
		         PMacro195_Entry1_DelayMin, PMacro195_Entry1_DelaySec, PMacro195_Entry1_TimMin, PMacro195_Entry1_TimSec, PMacro195_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro195_Entry2_DelayMin, PMacro195_Entry2_DelaySec, PMacro195_Entry2_TimMin, PMacro195_Entry2_TimSec, PMacro195_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro195_Entry3_DelayMin, PMacro195_Entry3_DelaySec, PMacro195_Entry3_TimMin, PMacro195_Entry3_TimSec, PMacro195_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro195_Entry4_DelayMin, PMacro195_Entry4_DelaySec, PMacro195_Entry4_TimMin, PMacro195_Entry4_TimSec, PMacro195_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro195_Entry5_DelayMin, PMacro195_Entry5_DelaySec, PMacro195_Entry5_TimMin, PMacro195_Entry5_TimSec, PMacro195_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro195_Entry6_DelayMin, PMacro195_Entry6_DelaySec, PMacro195_Entry6_TimMin, PMacro195_Entry6_TimSec, PMacro195_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro195_Entry7_DelayMin, PMacro195_Entry7_DelaySec, PMacro195_Entry7_TimMin, PMacro195_Entry7_TimSec, PMacro195_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro195_Entry8_DelayMin, PMacro195_Entry8_DelaySec, PMacro195_Entry8_TimMin, PMacro195_Entry8_TimSec, PMacro195_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro195_Entry9_DelayMin, PMacro195_Entry9_DelaySec, PMacro195_Entry9_TimMin, PMacro195_Entry9_TimSec, PMacro195_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro195_Entry10_DelayMin, PMacro195_Entry10_DelaySec, PMacro195_Entry10_TimMin, PMacro195_Entry10_TimSec, PMacro195_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro195_Entry11_DelayMin, PMacro195_Entry11_DelaySec, PMacro195_Entry11_TimMin, PMacro195_Entry11_TimSec, PMacro195_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro195_Entry12_DelayMin, PMacro195_Entry12_DelaySec, PMacro195_Entry12_TimMin, PMacro195_Entry12_TimSec, PMacro195_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro195_Entry13_DelayMin, PMacro195_Entry13_DelaySec, PMacro195_Entry13_TimMin, PMacro195_Entry13_TimSec, PMacro195_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro195_Entry14_DelayMin, PMacro195_Entry14_DelaySec, PMacro195_Entry14_TimMin, PMacro195_Entry14_TimSec, PMacro195_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro195_Entry15_DelayMin, PMacro195_Entry15_DelaySec, PMacro195_Entry15_TimMin, PMacro195_Entry15_TimSec, PMacro195_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR195_STRING};

const struct super_macro Macro196 = {PMacro196_NumEntries,
		         PMacro196_Entry1_DelayMin, PMacro196_Entry1_DelaySec, PMacro196_Entry1_TimMin, PMacro196_Entry1_TimSec, PMacro196_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro196_Entry2_DelayMin, PMacro196_Entry2_DelaySec, PMacro196_Entry2_TimMin, PMacro196_Entry2_TimSec, PMacro196_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro196_Entry3_DelayMin, PMacro196_Entry3_DelaySec, PMacro196_Entry3_TimMin, PMacro196_Entry3_TimSec, PMacro196_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro196_Entry4_DelayMin, PMacro196_Entry4_DelaySec, PMacro196_Entry4_TimMin, PMacro196_Entry4_TimSec, PMacro196_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro196_Entry5_DelayMin, PMacro196_Entry5_DelaySec, PMacro196_Entry5_TimMin, PMacro196_Entry5_TimSec, PMacro196_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro196_Entry6_DelayMin, PMacro196_Entry6_DelaySec, PMacro196_Entry6_TimMin, PMacro196_Entry6_TimSec, PMacro196_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro196_Entry7_DelayMin, PMacro196_Entry7_DelaySec, PMacro196_Entry7_TimMin, PMacro196_Entry7_TimSec, PMacro196_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro196_Entry8_DelayMin, PMacro196_Entry8_DelaySec, PMacro196_Entry8_TimMin, PMacro196_Entry8_TimSec, PMacro196_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro196_Entry9_DelayMin, PMacro196_Entry9_DelaySec, PMacro196_Entry9_TimMin, PMacro196_Entry9_TimSec, PMacro196_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro196_Entry10_DelayMin, PMacro196_Entry10_DelaySec, PMacro196_Entry10_TimMin, PMacro196_Entry10_TimSec, PMacro196_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro196_Entry11_DelayMin, PMacro196_Entry11_DelaySec, PMacro196_Entry11_TimMin, PMacro196_Entry11_TimSec, PMacro196_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro196_Entry12_DelayMin, PMacro196_Entry12_DelaySec, PMacro196_Entry12_TimMin, PMacro196_Entry12_TimSec, PMacro196_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro196_Entry13_DelayMin, PMacro196_Entry13_DelaySec, PMacro196_Entry13_TimMin, PMacro196_Entry13_TimSec, PMacro196_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro196_Entry14_DelayMin, PMacro196_Entry14_DelaySec, PMacro196_Entry14_TimMin, PMacro196_Entry14_TimSec, PMacro196_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro196_Entry15_DelayMin, PMacro196_Entry15_DelaySec, PMacro196_Entry15_TimMin, PMacro196_Entry15_TimSec, PMacro196_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR196_STRING};

const struct super_macro Macro197 = {PMacro197_NumEntries,
		         PMacro197_Entry1_DelayMin, PMacro197_Entry1_DelaySec, PMacro197_Entry1_TimMin, PMacro197_Entry1_TimSec, PMacro197_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro197_Entry2_DelayMin, PMacro197_Entry2_DelaySec, PMacro197_Entry2_TimMin, PMacro197_Entry2_TimSec, PMacro197_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro197_Entry3_DelayMin, PMacro197_Entry3_DelaySec, PMacro197_Entry3_TimMin, PMacro197_Entry3_TimSec, PMacro197_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro197_Entry4_DelayMin, PMacro197_Entry4_DelaySec, PMacro197_Entry4_TimMin, PMacro197_Entry4_TimSec, PMacro197_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro197_Entry5_DelayMin, PMacro197_Entry5_DelaySec, PMacro197_Entry5_TimMin, PMacro197_Entry5_TimSec, PMacro197_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro197_Entry6_DelayMin, PMacro197_Entry6_DelaySec, PMacro197_Entry6_TimMin, PMacro197_Entry6_TimSec, PMacro197_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro197_Entry7_DelayMin, PMacro197_Entry7_DelaySec, PMacro197_Entry7_TimMin, PMacro197_Entry7_TimSec, PMacro197_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro197_Entry8_DelayMin, PMacro197_Entry8_DelaySec, PMacro197_Entry8_TimMin, PMacro197_Entry8_TimSec, PMacro197_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro197_Entry9_DelayMin, PMacro197_Entry9_DelaySec, PMacro197_Entry9_TimMin, PMacro197_Entry9_TimSec, PMacro197_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro197_Entry10_DelayMin, PMacro197_Entry10_DelaySec, PMacro197_Entry10_TimMin, PMacro197_Entry10_TimSec, PMacro197_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro197_Entry11_DelayMin, PMacro197_Entry11_DelaySec, PMacro197_Entry11_TimMin, PMacro197_Entry11_TimSec, PMacro197_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro197_Entry12_DelayMin, PMacro197_Entry12_DelaySec, PMacro197_Entry12_TimMin, PMacro197_Entry12_TimSec, PMacro197_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro197_Entry13_DelayMin, PMacro197_Entry13_DelaySec, PMacro197_Entry13_TimMin, PMacro197_Entry13_TimSec, PMacro197_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro197_Entry14_DelayMin, PMacro197_Entry14_DelaySec, PMacro197_Entry14_TimMin, PMacro197_Entry14_TimSec, PMacro197_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro197_Entry15_DelayMin, PMacro197_Entry15_DelaySec, PMacro197_Entry15_TimMin, PMacro197_Entry15_TimSec, PMacro197_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR197_STRING};

const struct super_macro Macro198 = {PMacro198_NumEntries,
		         PMacro198_Entry1_DelayMin, PMacro198_Entry1_DelaySec, PMacro198_Entry1_TimMin, PMacro198_Entry1_TimSec, PMacro198_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro198_Entry2_DelayMin, PMacro198_Entry2_DelaySec, PMacro198_Entry2_TimMin, PMacro198_Entry2_TimSec, PMacro198_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro198_Entry3_DelayMin, PMacro198_Entry3_DelaySec, PMacro198_Entry3_TimMin, PMacro198_Entry3_TimSec, PMacro198_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro198_Entry4_DelayMin, PMacro198_Entry4_DelaySec, PMacro198_Entry4_TimMin, PMacro198_Entry4_TimSec, PMacro198_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro198_Entry5_DelayMin, PMacro198_Entry5_DelaySec, PMacro198_Entry5_TimMin, PMacro198_Entry5_TimSec, PMacro198_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro198_Entry6_DelayMin, PMacro198_Entry6_DelaySec, PMacro198_Entry6_TimMin, PMacro198_Entry6_TimSec, PMacro198_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro198_Entry7_DelayMin, PMacro198_Entry7_DelaySec, PMacro198_Entry7_TimMin, PMacro198_Entry7_TimSec, PMacro198_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro198_Entry8_DelayMin, PMacro198_Entry8_DelaySec, PMacro198_Entry8_TimMin, PMacro198_Entry8_TimSec, PMacro198_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro198_Entry9_DelayMin, PMacro198_Entry9_DelaySec, PMacro198_Entry9_TimMin, PMacro198_Entry9_TimSec, PMacro198_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro198_Entry10_DelayMin, PMacro198_Entry10_DelaySec, PMacro198_Entry10_TimMin, PMacro198_Entry10_TimSec, PMacro198_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro198_Entry11_DelayMin, PMacro198_Entry11_DelaySec, PMacro198_Entry11_TimMin, PMacro198_Entry11_TimSec, PMacro198_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro198_Entry12_DelayMin, PMacro198_Entry12_DelaySec, PMacro198_Entry12_TimMin, PMacro198_Entry12_TimSec, PMacro198_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro198_Entry13_DelayMin, PMacro198_Entry13_DelaySec, PMacro198_Entry13_TimMin, PMacro198_Entry13_TimSec, PMacro198_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro198_Entry14_DelayMin, PMacro198_Entry14_DelaySec, PMacro198_Entry14_TimMin, PMacro198_Entry14_TimSec, PMacro198_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro198_Entry15_DelayMin, PMacro198_Entry15_DelaySec, PMacro198_Entry15_TimMin, PMacro198_Entry15_TimSec, PMacro198_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR198_STRING};

const struct super_macro Macro199 = {PMacro199_NumEntries,
		         PMacro199_Entry1_DelayMin, PMacro199_Entry1_DelaySec, PMacro199_Entry1_TimMin, PMacro199_Entry1_TimSec, PMacro199_Entry1_Protocol, 0, 0, 0, 0,
		         PMacro199_Entry2_DelayMin, PMacro199_Entry2_DelaySec, PMacro199_Entry2_TimMin, PMacro199_Entry2_TimSec, PMacro199_Entry2_Protocol, 0, 0, 0, 0,
		         PMacro199_Entry3_DelayMin, PMacro199_Entry3_DelaySec, PMacro199_Entry3_TimMin, PMacro199_Entry3_TimSec, PMacro199_Entry3_Protocol, 0, 0, 0, 0,
		         PMacro199_Entry4_DelayMin, PMacro199_Entry4_DelaySec, PMacro199_Entry4_TimMin, PMacro199_Entry4_TimSec, PMacro199_Entry4_Protocol, 0, 0, 0, 0,
		         PMacro199_Entry5_DelayMin, PMacro199_Entry5_DelaySec, PMacro199_Entry5_TimMin, PMacro199_Entry5_TimSec, PMacro199_Entry5_Protocol, 0, 0, 0, 0,
		         PMacro199_Entry6_DelayMin, PMacro199_Entry6_DelaySec, PMacro199_Entry6_TimMin, PMacro199_Entry6_TimSec, PMacro199_Entry6_Protocol, 0, 0, 0, 0,
		         PMacro199_Entry7_DelayMin, PMacro199_Entry7_DelaySec, PMacro199_Entry7_TimMin, PMacro199_Entry7_TimSec, PMacro199_Entry7_Protocol, 0, 0, 0, 0,
		         PMacro199_Entry8_DelayMin, PMacro199_Entry8_DelaySec, PMacro199_Entry8_TimMin, PMacro199_Entry8_TimSec, PMacro199_Entry8_Protocol, 0, 0, 0, 0,
		         PMacro199_Entry9_DelayMin, PMacro199_Entry9_DelaySec, PMacro199_Entry9_TimMin, PMacro199_Entry9_TimSec, PMacro199_Entry9_Protocol, 0, 0, 0, 0,
		         PMacro199_Entry10_DelayMin, PMacro199_Entry10_DelaySec, PMacro199_Entry10_TimMin, PMacro199_Entry10_TimSec, PMacro199_Entry10_Protocol, 0, 0, 0, 0,
		         PMacro199_Entry11_DelayMin, PMacro199_Entry11_DelaySec, PMacro199_Entry11_TimMin, PMacro199_Entry11_TimSec, PMacro199_Entry11_Protocol, 0, 0, 0, 0,
		         PMacro199_Entry12_DelayMin, PMacro199_Entry12_DelaySec, PMacro199_Entry12_TimMin, PMacro199_Entry12_TimSec, PMacro199_Entry12_Protocol, 0, 0, 0, 0,
		         PMacro199_Entry13_DelayMin, PMacro199_Entry13_DelaySec, PMacro199_Entry13_TimMin, PMacro199_Entry13_TimSec, PMacro199_Entry13_Protocol, 0, 0, 0, 0,
		         PMacro199_Entry14_DelayMin, PMacro199_Entry14_DelaySec, PMacro199_Entry14_TimMin, PMacro199_Entry14_TimSec, PMacro199_Entry14_Protocol, 0, 0, 0, 0,
		         PMacro199_Entry15_DelayMin, PMacro199_Entry15_DelaySec, PMacro199_Entry15_TimMin, PMacro199_Entry15_TimSec, PMacro199_Entry15_Protocol, 0, 0, 0, 0,
				 PSUPR199_STRING};
#endif



