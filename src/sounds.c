/*
 * sounds.c
 *
 *  Created on: Feb 3, 2015
 *      Author: rpruitt76
 */
//****************************************************************************
//*
//*	Sounds.c
//*
//* These routines are used to support all audio processing.
//*
//****************************************************************************
//* Laser Pulsar Embedded Software
//* Date: June 1, 2006
//* Updated: February 3, 2015
//* Designer: Ralph Pruitt
//* Property: LED Healing Light, INC.
//* Copyright: June 2006
//* Description: This software is used with the Beta release and all subsequent
//* releases of the Mark II Laser Pulsar Systems. This design supports this product
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
#include <string.h>
#include <stdlib.h>
#include "LaserP.h"

//*****************************************************************************
//*
//* Routine Declarations
//*
//*****************************************************************************
void amp_on(void);
void amp_off(void);
void i2c_init(void);
void i2c_off(void);
void i2c_SetTick(uint tick_var);
void i2c_Tick(void);
uchar mcp_GenReset(void);
uchar mcp_GenWakeup(void);
uchar mcp_ShrtRd(void);
void snd_high(uint time_count);
void snd_low(uint time_count);
void i2c_FStop(void);
void i2c_fstrt(void);
void i2c_SndFByte(uchar data1);
uchar i2c_WaitFAck(uint numloops);

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
//* routine: init_sound
//* Date:    January 8, 2007
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine initializes all key sound hardware for correct operation.
//*
//*****************************************************************************
void init_sound(void)
{
#if MCP4725
  uchar temp1;
  uchar temp2;
// Enable I2C Bus and Set Tick to Default Tick Value.
  i2c_init(); 	  	  	  	   	  		  // Initialize I2C Bus.
  i2c_SetTick(DEFAULT_MCPTICK);			  // Initialize Tick Value.
  temp1 = mcp_GenReset();				  // Reset DAC.
  if(temp1 > 0)
	  printf2("init_sound: ACK Timeout\n");
  temp2 = 0;
  while (temp2 == 0)
  {
	  if (mcp_ShrtRd() & 0x01)
	  {
		  printf2("init_sound: ACK Timeout\n");
		  break;
	  }
	  temp2 = mcp_ShrtRd() & 0x80;	  	  // Get Busy Bit
  }
  temp1 = mcp_GenWakeup();				  // Wakeup DAC.
  if(temp1 > 0)
	  printf2("init_sound: ACK Timeout\n");
  temp2 = 0;
  while (temp2 == 0)
  {
	  if (mcp_ShrtRd() & 0x01)
	  {
		  printf2("init_sound: ACK Timeout\n");
		  break;
	  }
   temp2 = mcp_ShrtRd() & 0x80;	  	  // Get Busy Bit
  }
// Test Code to Exercise DAC Port
//  amp_on();				   				  // Power-up Booster Amp.
//  beep_400hz(1000);
//  amp_off();	   						  // Power-Down Booster Amp.
/*  temp1 = mcp_FWrtDac(AUDIO_HIGH);		  // Send Audio High
  temp1 = mcp_FWrtDac(AUDIO_LOW);		  // Send Audio Low
  temp1 = mcp_FWrtDac(AUDIO_HIGH);		  // Send Audio High
  temp1 = mcp_FWrtDac(AUDIO_LOW);		  // Send Audio Low
  temp1 = mcp_FWrtDac(AUDIO_HIGH);		  // Send Audio High
  temp1 = mcp_FWrtDac(AUDIO_LOW);		  // Send Audio Low
  temp1 = mcp_FWrtDac(AUDIO_HIGH);		  // Send Audio High
  temp1 = mcp_FWrtDac(AUDIO_LOW);		  // Send Audio Low
  temp1 = mcp_FWrtDac(AUDIO_HIGH);		  // Send Audio High
  temp1 = mcp_FWrtDac(AUDIO_LOW);		  // Send Audio Low
  temp2 = mcp_ShrtRd() & 0x80;	  	  // Get Busy Bit */
#else
	PORT3.PDR.BYTE |= 0x04;		// Set as Output.
#endif
}

//*****************************************************************************
//*
//* routine: powerdn_sound
//* Date:    January 8, 2007
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine powers down the audio hardware.
//*
//*****************************************************************************
void powerdn_sound(void)
{
#if MCP4725
  i2c_off();		// Power Down DAC.
#else
	PORT3.PDR.BYTE &= ~0x04;		// Set as Input.
#endif
}

//*****************************************************************************
//*
//* routine: beep_400hz
//* Date:    June 1, 2006
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine beeps the speaker at around 400hz for the specified number of
//* milliseconds passed.
//*
//*****************************************************************************
void beep_400hz(uint time_count)
{
  uint x;

  // Adjust time_count for Period to delay for one cycle.
  time_count *= 0.4;

  // Time to generate the audio.
  if ((audio_flg == 1) && (nobeep_flg == 1)) {
#if MCP4725 != 1
	speaker_enable();				// Enable Speaker for Sound.
#endif
    for(x=0; x<time_count; x++) {
#if MCP4725
	  snd_high(8500);       //Cnt = (1250)/0.15 = 3290
	  snd_low(8500);
#else
      // Turn on Speaker
	  speaker_on();
      // Delay 1250usec
      very_accurate_delay(125);
      // Turn off Speaker
      speaker_off();
      // Delay 1250usec...8usec
      very_accurate_delay(125);
#endif
	} //ENDF X
  } //ENDIF audio_flg
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#else
  speaker_disable();					  // Disable Speaker for Sound.
#endif
}

//*****************************************************************************
//*
//* routine: beep_600hz
//* Date:    June 1, 2006
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine beeps the speaker at around 600hz for the specified number of
//* milliseconds passed.
//*
//*****************************************************************************
void beep_600hz(uint time_count)
{
  uint x;

  // Adjust time_count for Period to delay for one cycle.
  time_count *= 0.6;

  // Time to generate the audio.
  if ((audio_flg == 1) && (nobeep_flg == 1)) {
#if MCP4725 != 1
	speaker_enable();				// Enable Speaker for Sound.
#endif
    for(x=0; x<time_count; x++) {
#if MCP4725
	  snd_high(5333);	  	   //Cnt = (830)/0.15 = 5333
	  snd_low(5333);				//Cnt = (830)/0.15 = 5333
#else
      // Turn on Speaker
	  speaker_on();
      // Delay 830usec
      very_accurate_delay(83);
      // Turn off Speaker
      speaker_off();
      // Delay 830usec
      very_accurate_delay(83);
#endif
	} //ENDF X
  } //ENDIF audio_flg
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#else
  speaker_disable();					  // Disable Speaker for Sound.
#endif
}

//*****************************************************************************
//*
//* routine: beep_800hz
//* Date:    June 1, 2006
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine beeps the speaker at around 800hz for the specified number of
//* milliseconds passed.
//*
//*****************************************************************************
void beep_800hz(uint time_count)
{
  uint x;

  // Adjust time_count for Period to delay for one cycle.
  time_count *= 0.8;

  // Time to generate the audio.
  if ((audio_flg == 1) && (nobeep_flg == 1)) {
#if MCP4725 != 1
	speaker_enable();				// Enable Speaker for Sound.
#endif
    for(x=0; x<time_count; x++) {
#if MCP4725
	  snd_high(4133);	  	   //Cnt = (620)/0.15 = 4133
	  snd_low(4133);				//Cnt = (620)/0.15 = 4133
#else
      // Turn on Speaker
	  speaker_on();
      // Delay 620usec
      very_accurate_delay(62);
      // Turn off Speaker
      speaker_off();
      // Delay 620usec
      very_accurate_delay(62);
#endif
	} //ENDF X
  } //ENDIF audio_flg
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#else
  speaker_disable();					  // Disable Speaker for Sound.
#endif
}

//*****************************************************************************
//*
//* routine: beep_1Khz
//* Date:    June 1, 2006
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine beeps the speaker at around 1Khz for the specified number of
//* milliseconds passed.
//*
//*****************************************************************************
void beep_1Khz(uint time_count)
{
  uint x;

  if ((audio_flg == 1) && (nobeep_flg == 1)) {
#if MCP4725 != 1
	speaker_enable();				// Enable Speaker for Sound.
#endif
    for(x=0; x<time_count; x++) {
#if MCP4725 == 1
	  snd_high(3333);	  	   //Cnt = (500)/0.15 = 3333
	  snd_low(3333);				//Cnt = (500)/0.15 = 3333
#else
      // Turn on Speaker
	  speaker_on();
      // Delay 500usec
      very_accurate_delay(50);
      // Turn off Speaker
      speaker_off();
      // Delay 500usec
      very_accurate_delay(50);
#endif
	} //ENDF X
  } //ENDIF audio_flg
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#else
  speaker_disable();					  // Disable Speaker for Sound.
#endif
}

//*****************************************************************************
//*
//* routine: beep_1K2hz
//* Date:    June 1, 2006
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine beeps the speaker at around 1.2Khz for the specified number of
//* milliseconds passed.
//*
//*****************************************************************************
void beep_1K2hz(uint time_count)
{
  uint x;

  // Adjust time_count for Period to delay for one cycle.
  time_count *= 1.2;

  // Time to generate the audio.
  if ((audio_flg == 1) && (nobeep_flg == 1)) {
#if MCP4725 != 1
	speaker_enable();				// Enable Speaker for Sound.
#endif
    for(x=0; x<time_count; x++) {
#if MCP4725
	  snd_high(2800);	  	   //Cnt = (420)/0.15 = 2800
	  snd_low(2800);				//Cnt = (420)/0.15 = 2800
#else
      // Turn on Speaker
	  speaker_on();
      // Delay 420usec
      very_accurate_delay(42);
      // Turn off Speaker
      speaker_off();
      // Delay 420usec
      very_accurate_delay(42);
#endif
	} //ENDF X
  } //ENDIF audio_flg
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#else
  speaker_disable();					  // Disable Speaker for Sound.
#endif
}

//*****************************************************************************
//*
//* routine: beep_1K4hz
//* Date:    June 1, 2006
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine beeps the speaker at around 1.4Khz for the specified number of
//* milliseconds passed.
//*
//*****************************************************************************
void beep_1K4hz(uint time_count)
{
  uint x;

  // Adjust time_count for Period to delay for one cycle.
  time_count *= 1.4;

  // Time to generate the audio.
  if ((audio_flg == 1) && (nobeep_flg == 1)) {
#if MCP4725 != 1
	speaker_enable();				// Enable Speaker for Sound.
#endif
    for(x=0; x<time_count; x++) {
#if MCP4725
	  snd_high(2400);	  	   //Cnt = (360)/0.15 = 2400
	  snd_low(2400);				//Cnt = (360)/0.15 = 2400
#else
      // Turn on Speaker
	  speaker_on();
      // Delay 360usec
      very_accurate_delay(36);
      // Turn off Speaker
      speaker_off();
      // Delay 360usec
      very_accurate_delay(36);
#endif
	} //ENDF X
  } //ENDIF audio_flg
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#else
  speaker_disable();					  // Disable Speaker for Sound.
#endif
}

//*****************************************************************************
//*
//* routine: beep_1K6hz
//* Date:    June 1, 2006
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine beeps the speaker at around 1.6Khz for the specified number of
//* milliseconds passed.
//*
//*****************************************************************************
void beep_1K6hz(uint time_count)
{
  uint x;

  // Adjust time_count for Period to delay for one cycle.
  time_count *= 1.6;

  // Time to generate the audio.
  if ((audio_flg == 1) && (nobeep_flg == 1)) {
#if MCP4725 != 1
	speaker_enable();				// Enable Speaker for Sound.
#endif
    for(x=0; x<time_count; x++) {
#if MCP4725
	  snd_high(2067);	  	   //Cnt = (310)/0.15 = 2067
	  snd_low(2067);				//Cnt = (310)/0.15 = 2067
#else
      // Turn on Speaker
	  speaker_on();
      // Delay 310usec
      very_accurate_delay(31);
      // Turn off Speaker
      speaker_off();
      // Delay 310usec
      very_accurate_delay(31);
#endif
	} //ENDF X
  } //ENDIF audio_flg
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#else
  speaker_disable();					  // Disable Speaker for Sound.
#endif
}

//*****************************************************************************
//*
//* routine: beep_GNote
//* Date:    June 1, 2006
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine beeps the speaker at the note G around 783.99hz for the specified number of
//* milliseconds passed.
//*
//*****************************************************************************
void beep_GNote(uint time_count)
{
  uint x;

  // Adjust time_count for Period to delay for one cycle.
  time_count *= 0.784;

  // Time to generate the audio.
  if ((audio_flg == 1) && (nobeep_flg == 1)) {
#if MCP4725 != 1
	speaker_enable();				// Enable Speaker for Sound.
#endif
    for(x=0; x<time_count; x++) {
#if MCP4725
	  snd_high(4267);	  	   //Cnt = (640)/0.15 = 4267
	  snd_low(4267);				//Cnt = (640)/0.15 = 4267
#else
      // Turn on Speaker
	  speaker_on();
      // Delay 640usec
      very_accurate_delay(64);
      // Turn off Speaker
      speaker_off();
      // Delay 640usec
      very_accurate_delay(64);
#endif
	} //ENDF X
  } //ENDIF audio_flg
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#else
  speaker_disable();					  // Disable Speaker for Sound.
#endif
}

//*****************************************************************************
//*
//* routine: beep_BNote
//* Date:    June 1, 2006
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine beeps the speaker at the note B around 987.77hz for the specified number of
//* milliseconds passed.
//*
//*****************************************************************************
void beep_BNote(uint time_count)
{
  uint x;

  // Adjust time_count for Period to delay for one cycle.
  time_count *= 0.987;

  // Time to generate the audio.
  if ((audio_flg == 1) && (nobeep_flg == 1)) {
#if MCP4725 != 1
	speaker_enable();				// Enable Speaker for Sound.
#endif
    for(x=0; x<time_count; x++) {
#if MCP4725
	  snd_high(3400);	  	   //Cnt = (510)/0.15 = 3400
	  snd_low(3400);				//Cnt = (510)/0.15 = 3400
#else
      // Turn on Speaker
	  speaker_on();
      // Delay 510usec
      very_accurate_delay(51);
      // Turn off Speaker
      speaker_off();
      // Delay 510usec
      very_accurate_delay(51);
#endif
	} //ENDF X
  } //ENDIF audio_flg
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#else
  speaker_disable();					  // Disable Speaker for Sound.
#endif
}

//*****************************************************************************
//*
//* routine: beep_DNote
//* Date:    June 1, 2006
//* Updated: February 3, 2015
/* Author:  Ralph Pruitt
//* This routine beeps the speaker at the note D around 1.174Khz for the specified number of
//* milliseconds passed.
//*
//*****************************************************************************/
void beep_DNote(uint time_count)
{
  uint x;

  // Adjust time_count for Period to delay for one cycle.
  time_count *= 1.17;

  // Time to generate the audio.
  if ((audio_flg == 1) && (nobeep_flg == 1)) {
#if MCP4725 != 1
	speaker_enable();				// Enable Speaker for Sound.
#endif
    for(x=0; x<time_count; x++) {
#if MCP4725
	  snd_high(2867);	  	   //Cnt = (430)/0.15 = 2867
	  snd_low(2867);				//Cnt = (430)/0.15 = 2867
#else
      // Turn on Speaker
      speaker_on();
      // Delay 430usec
      very_accurate_delay(43);
      // Turn off Speaker
      speaker_off();
      // Delay 430usec
      very_accurate_delay(43);
#endif
	} //ENDF X
  } //ENDIF audio_flg
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#else
  speaker_disable();					  // Disable Speaker for Sound.
#endif
}

//*****************************************************************************
//*
//* routine: beep_tick
//* Date:    June 7, 2010
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine plays the speaker in a short tick sound.
//*
//*****************************************************************************
void beep_tick(void)
{
#if MCP4725
  amp_on();				   				  // Power-up Booster Amp.
#else
  speaker_enable();				// Enable Speaker for Sound.
#endif
  // Play G for 50msec.
  beep_GNote(10);
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#else
  speaker_disable();					  // Disable Speaker for Sound.
#endif
}
//*****************************************************************************
//*
//* routine: beep_ArpUp
//* Date:    June 1, 2006
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine plays the speaker in an Arpagio of G-B-D each in 50msec Beeps and a 30msec Gap.
//*
//*****************************************************************************
void beep_ArpUp(void)
{
#if MCP4725
  amp_on();				   				  // Power-up Booster Amp.
#endif
  // Play G for 50msec.
  beep_GNote(50);
  // Wait for 30msec.
  accurate_delay(70);

  // Play B for 50msec.
  beep_BNote(50);
  // Wait for 30msec.
  accurate_delay(70);

  // Play D for 50msec.
  beep_DNote(50);
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#endif
}

//*****************************************************************************
//*
//* routine: beep_ArpDn
//* Date:    June 1, 2006
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine plays the speaker in an Arpagio of D-B-G each in 50msec Beeps and a 30msec Gap.
//*
//*****************************************************************************
void beep_ArpDn(void)
{
#if MCP4725
  amp_on();				   				  // Power-up Booster Amp.
#endif
  // Play D for 50msec.
  beep_DNote(80);
  // Wait for 30msec.
  accurate_delay(100);

  // Play B for 50msec.
  beep_BNote(80);
  // Wait for 30msec.
  accurate_delay(100);

  // Play G for 50msec.
  beep_GNote(80);
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#endif
}

//*****************************************************************************
//*
//* routine: beep_3Bp
//* Date:    June 1, 2006
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine plays the speaker in an 3Beeps of Beep for 50msec and a 30msec Gap.
//*
//*****************************************************************************
void beep_3Bp(void)
{
#if MCP4725
  amp_on();				   				  // Power-up Booster Amp.
#endif
  // Play D for 50msec.
  beep_BNote(50);
  // Wait for 30msec.
  accurate_delay(70);

  // Play B for 50msec.
  beep_BNote(50);
  // Wait for 30msec.
  accurate_delay(70);

  // Play G for 50msec.
  beep_BNote(50);
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#endif
}

//*****************************************************************************
//*
//* routine: beep_3low
//* Date:    June 2, 2006
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine plays the speaker in an 3 low Beeps for 50msec and a 70msec Gap.
//*
//*****************************************************************************
void beep_3low(void)
{
#if MCP4725
  amp_on();				   				  // Power-up Booster Amp.
#endif
  // Play D for 50msec.
  beep_400hz(50);
  // Wait for 30msec.
  accurate_delay(70);

  // Play B for 50msec.
  beep_400hz(50);
  // Wait for 30msec.
  accurate_delay(70);

  // Play G for 50msec.
  beep_400hz(50);
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#endif
}

//*****************************************************************************
//*
//* routine: force_beep
//* Date:    June 1, 2006
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine beeps the speaker at around 1Khz the same as beep_1Khz except that
//* no check is made against nobeep_flgg. One parameter is passed for the specified
//* number of milliseconds passed.
//*
//*****************************************************************************
void force_beep(uint time_count)
{
  uint x;

#if MCP4725
  amp_on();				   				  // Power-up Booster Amp.
#endif
  if (audio_flg == 1) {
    for(x=0; x<time_count; x++) {
#if MCP4725
	  snd_high(150);	  	   //Cnt = (500-170)/2.2 = 150
	  snd_low(150);
#else
      // Turn on Speaker
      speaker_on();
      // Delay 500usec
      very_accurate_delay(50);
      // Turn off Speaker
      speaker_off();
      // Delay 500usec
      very_accurate_delay(50);
#endif
	} //ENDF X
  } //ENDIF audio_flg
#if MCP4725
  amp_off();	   						  // Power-Down Booster Amp.
#endif
}
#if MCP4725
//*****************************************************************************
//*  I2C Routines to support MCP4725 Hardware
//*
//*****************************************************************************

//*****************************************************************************
//*
//* routine: i2c_init
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine sets the Din(P32) and CClk(P33) pins as Output and High. This State is
//* known as "Bus Not Ready(A)".
//*
//*****************************************************************************
void i2c_init(void)
{
	PORT3.PODR.BYTE |= 0x0C;		// Set CClk(P33) and Din(P32) to High
	PORT3.PDR.BYTE |= 0x0C;			// Set CClk(P33) and Din(P32) as Output.
}

//*****************************************************************************
//*
//* routine: i2c_off
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine sets the Din(P32) and CClk(P33) pins as TriState Input.
//*
//*****************************************************************************
void i2c_off(void)
{
 PORT3.PODR.BYTE &= ~0x0C;				// Set CClk(P33) and Din(P32) to TriState.
 PORT3.PDR.BYTE  &= ~0x0C;				// Set CClk(P33) and Din(P32) as Input.
}

//*****************************************************************************
//*
//* routine: i2c_strt
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine transitions ths SDA/DIN(P32) Pin from High to low while holding the
//* clock/CClk(P33) pin high. This State is known as "Start Data Transfer(B)".
//*
//*****************************************************************************
void i2c_strt(void)
{
  PORT3.PDR.BYTE  |= 0x04;				// Set Din(P32) as Output.
  PORT3.PODR.BYTE |= 0x04;			    // Transition  Din(P32) to H.
  short_delay(1);						// Allow Data to settle.
  PORT3.PODR.BYTE |= 0x08;  			// Force Clock to High.
  i2c_Tick();							// Tick for needed delay before continuing.
  PORT3.PODR.BYTE &= ~0x04;				// Transition  Din(P32) from H->L.
  i2c_Tick();							// Tick for needed delay before continuing.
}

//*****************************************************************************
//*
//* routine: i2c_SndBit
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine sends the passed bit via the I2C bus. This State is
//* known as "Data Valid(D)".
//*
//*****************************************************************************
void i2c_SndBit(uchar dbit1)
{
 PORT3.PODR.BYTE &= ~0x08;				// Transition  CClk(P33) from H->L.
 i2c_Tick();							// Tick for needed delay before continuing.
 if (dbit1 & 0x01)
   PORT3.PODR.BYTE |= 0x04;				// Force Din(P32) to High.
 else
   PORT3.PODR.BYTE &= ~0x04;			// Force Din(P32) to Low.
 i2c_Tick();							// Tick for needed delay before continuing.
 PORT3.PODR.BYTE |= 0x08;				// Transition  CClk(P33) from L->H.
 i2c_Tick();							// Tick for needed delay before continuing.
}

//*****************************************************************************
//*
//* routine: i2c_SndByte
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine sends the passed data via the I2C bus by calling the
//* routine i2c_SndBit.
//*
//*****************************************************************************
void i2c_SndByte(uchar data1)
{
  unsigned char x, temp1;

  //Set Din(P32) as Output.
  PORT3.PDR.BYTE  |= 0x04;			// Set Din(P32) as Output.

  for(x=0; x<8; x++)
  {
    temp1 = data1 & 0x80;	 		// Get MS Bit to test....
	if(temp1)	  					// If set send a 1 bit else a zero bit
	  i2c_SndBit(1);
	else
	  i2c_SndBit(0);
	data1 <<= 1;					// Shift to next bit to send.
  }
//  i2c_Tick();							// Tick for needed delay before continuing.
}

//*****************************************************************************
//*
//* routine: i2c_WaitAck
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine waits the passed amount of time for the ACK from the I2C Bus.
//* If no ACK is seen, then the error flag will be returned set. ACK is known as a
//* pulled High to Low Transition of the SDA/DIN(P32) Pin.
//*
//*	Returns : uchar      		0: ACK Received. No errors.
//*								1: No Ack received...Timeout.
//*	Parameters : uint numloops: Number of loops to wait for ACK from Hardware.
//*			   	 	 			Note that this value should not exceed 256 bytes.
//*
//*****************************************************************************
uchar i2c_WaitAck(uint numloops)
{
  uint cnt;
  uchar temp1;

  PORT3.PODR.BYTE &= ~0x08;				// Transition  CClk(P33) from H->L.
  i2c_Tick();							// Tick for needed delay before continuing.
  //Set Din(P32) as Input.
  PORT3.PODR.BYTE &= ~0x04;	   			// Set Din(P32) to TriState.
  PORT3.PDR.BYTE  &= ~0x04;				// Set Din(P32) as Input.
  i2c_Tick();							// Tick for needed delay before continuing.
  cnt = numloops;	   			        // Set Loopcnt.

  PORT3.PODR.BYTE |= 0x08; 				// Transition  CClk(P33) from L->H.
  i2c_Tick();							// Tick for needed delay before continuing.

  temp1 = PORT3.PIDR.BYTE & 0x04;	 			    // Read Din(P32) value
  while(temp1 && (cnt-->1)) {			// Loop until ACK or timeout.
    temp1 = PORT3.PIDR.BYTE & 0x04;	 	// Read Din(P32) value
	short_delay(1);						// Delay for 10.8usec.
  }
  PORT3.PODR.BYTE &= ~0x08;				// Transition  CClk(P33) from H->L.
  PORT3.PDR.BYTE  |= 0x04;				// Set Din(P32) as Output.
  i2c_Tick();							// Tick for needed delay before continuing.
  if(cnt > 0)
    return(0);							// If cnt positive, no timeout.
  else
    return(1);							// Else timeout.
}

//*****************************************************************************
//*
//* routine: i2c_SendAck
//* Date:    May 19, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine sends an Ack back to the Slave Part.
//*****************************************************************************
void i2c_SendAck(void)
{
  PORT3.PODR.BYTE &= ~0x08;				// Transition  CClk(P33) from H->L.
  i2c_Tick();							// Tick for needed delay before continuing.
  PORT3.PDR.BYTE |= 0x04;				// Set Din(P32) as Output.
  PORT3.PODR.BYTE &= ~0x04;				// Force Din(P32) low
  i2c_Tick();							// Tick for needed delay before continuing.
  PORT3.PODR.BYTE |= 0x08;				// Transition  CClk(P33) from L->H.
  i2c_Tick();							// Tick for needed delay before continuing.
  PORT3.PODR.BYTE &= ~0x08;   			// Transition  CClk(P33) from H->L.
  i2c_Tick();							// Tick for needed delay before continuing.
}

//*****************************************************************************
//*
//* routine: i2c_Stop
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine transitions the DIN/SDA(P32) pin from low to high while the Clk pin
//* is held High. This State is known as "Stop Data Transfer(C)".
//*****************************************************************************
void i2c_Stop(void)
{
  PORT3.PDR.BYTE  |= 0x04;				// Set Din(P32) as Output.
  PORT3.PODR.BYTE |= 0x08;				// Force Clock to High.
  i2c_Tick();							// Tick for needed delay before continuing.
  PORT3.PODR.BYTE |= 0x04;				// Transition  Din(P32) from L->H.
  i2c_Tick();							// Tick for needed delay before continuing.
}

//*****************************************************************************
//*
//* routine: i2c_RdBit
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine sets the Din(P32) pin as an input and pulses the CClk(P33) pin to receive one
//* valid bit from the I2C bus.
//*
//*
//*	Returns : uchar   		Bit 0 Contains valid bit
//*****************************************************************************
uchar i2c_RdBit(void)
{
  uchar temp1;

  PORT3.PODR.BYTE &= ~0x08;				// Transition  CClk(P33) from H->L.
  i2c_Tick();							// Tick for needed delay before continuing.

  PORT3.PODR.BYTE |= 0x08;  			// Transition  CClk(P33) from L->H.
  i2c_Tick();							// Tick for needed delay before continuing.

  temp1 = PORT3.PIDR.BYTE & 0x04;	 			    // Read Din(P32) value
  i2c_Tick();							// Tick for needed delay before continuing.
  if (temp1)
    return(1);							// If positive, return1.
  else
    return(0);							// Else zero.
}

//*****************************************************************************
//*
//* routine: i2c_RdByte
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine reads a byte from the I2C bus by calling the routine i2c_RdBit.
//*
//*	Returns : uchar      		Valid Byte.
//*****************************************************************************
uchar i2c_RdByte(void)
{
  unsigned char x, temp1;

  //Set Din(P32) as Input.
  PORT3.PODR.BYTE &= ~0x04;				// Set Din(P32) to TriState.
  PORT3.PDR.BYTE  &= ~0x04;				// Set Din(P32) as Input.

  temp1 = 0;
  for(x=0; x<8; x++)
  {
    temp1 += i2c_RdBit();
	temp1 <<= 1;
  }
  return(temp1);
}

//*****************************************************************************
//*
//* routine: i2c_SetTick
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine sets the tick value for the normal I2C wait between steps. It is
//* coded as a uint value in 10 usec ticks.
//*
//*	Parameters : uint tick_var: Number of 10usec Ticks to wait.
//*****************************************************************************
void i2c_SetTick(uint tick_var)
{
 	 save_tick = tick_var;
}

//*****************************************************************************
//*
//* routine: i2c_Tick
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* Delay specified number of microseconds from save_tick.
//*****************************************************************************
void i2c_Tick(void)
{
	short_delay(1);		// Delay 1 Microsecond.
}

//*****************************************************************************
//*
//* routine: mcp_GenReset
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This command sends a General Reset Command to the MCP4725.
//*
//*	Returns : uchar      		0: ACK Received. No errors.
//*								1: No Ack received...Timeout.
//*****************************************************************************
uchar mcp_GenReset(void)
{
     uchar temp1, x;
	 for (x=0; x<5; x++) {
       i2c_strt();		   			        // Send Start Command
	   i2c_SndByte(MCP_GENERAL);			// Send General Call
	   temp1 = i2c_WaitAck(MCP_TIMEOUT);	// Wait for ACK.
	   if (temp1 == 0) {
	     i2c_SndByte(MCP_RESET);			// Send General Reset.
	     temp1 = i2c_WaitAck(MCP_TIMEOUT);	// Wait for ACK.
	   }
	   i2c_Stop();							// Stop Command
       i2c_Tick();							// Tick for needed delay before continuing.
       i2c_Tick();							// Tick for needed delay before continuing.
	   if (temp1 == 0)
	     return(0);	  						// Return
	 }
	 return(1);								// Return.
}

//*****************************************************************************
//*
//* routine: mcp_GenWakeup
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This command sends a General Wakeup Command to the MCP4725.
//*
//*	Returns : uchar      		0: ACK Received. No errors.
//*								1: No Ack received...Timeout.
//*****************************************************************************
uchar mcp_GenWakeup(void)
{
     uchar temp1, x;
	 for (x=0; x<5; x++) {
       i2c_strt();		   			        // Send Start Command
	   i2c_SndByte(MCP_GENERAL);			// Send General Call
	   temp1 = i2c_WaitAck(MCP_TIMEOUT);	// Wait for ACK.
	   if (temp1 == 0) {
	     i2c_SndByte(MCP_WAKEUP);			// Send General Reset.
	     temp1 = i2c_WaitAck(MCP_TIMEOUT);	// Wait for ACK.
	   }
	   i2c_Stop();							// Stop Command
       i2c_Tick();							// Tick for needed delay before continuing.
       i2c_Tick();							// Tick for needed delay before continuing.
	   if (temp1 == 0)
	     return(0);	  						// Return
	 }
	 return(1);								// Return.
}

//*****************************************************************************
//*
//* routine: mcp_Read
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This command sends a Read Command to the MCP4725 and returns the value of the
//* read.
//*
//*	Returns : ulong      Bit 23 0: Busy
//*						        1: Ready
//*					     Bit 22 :  POR Status
//*                      Bit 18 :  PD1
//*                      Bit 17 :  PD0
//*                      Bits 16-4: DAC Register Data
//*						 Bit 0	0: ACK Received. No errors.
//*								1: No Ack received...Timeout.
//*****************************************************************************
ulong mcp_Read(void)
{
     uchar temp1;
	 ulong data1;

// Special Code to Test ALL 6 Addresses for mcp_read.
     i2c_strt();		   			        // Send Start Command
	 i2c_SndByte(MCP_DEVREAD);				// Send Device Read.
	 temp1 = i2c_WaitAck(MCP_TIMEOUT);		// Wait for ACK.
	 if(temp1) {
	   i2c_Stop();							// Stop Command
	   return(1);							// No Ack....Return.
	 }
	 temp1 = i2c_RdByte();					// Read Byte from DAC
	 i2c_SendAck();							// Send ACK.
	 data1 = temp1;							// Good first Byte...Save to output data.
	 data1 <<= 8;							// Shift Result for next read.
	 temp1 = i2c_RdByte();					// Read Byte from DAC
	 i2c_SendAck();							// Send ACK.
	 data1 += temp1;						// Good first Byte...Save to output data.
	 data1 <<= 8;							// Shift Result for next read.
	 temp1 = i2c_RdByte();					// Read Byte from DAC
	 i2c_SendAck();							// Send ACK.
	 data1 += temp1;						// Good first Byte...Save to output data.
	 data1 <<= 8;							// Shift Result for next read.
	 temp1 = i2c_RdByte();					// Read Byte from DAC
	 i2c_SendAck();							// Send ACK.
	 temp1 = i2c_RdByte();					// Read Byte from DAC
	 i2c_SendAck();							// Send ACK.
	 i2c_Stop();							// Stop Command
     i2c_Tick();							// Tick for needed delay before continuing.
//     i2c_Tick();							// Tick for needed delay before continuing.
     return(data1);							// Good Return....Return.
}

//*****************************************************************************
//*
//* routine: mcp_ShrtRd
//* Date:    May 19, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This command sends a Read Command to the MCP4725 and returns the value of the
//* 1st Byte Read.
//*
//*	Returns : uchar      Bit 7  0: Busy
//*						        1: Ready
//*					     Bit 6  :  POR Status
//*                      Bit 2  :  PD1
//*                      Bit 1  :  PD0
//*						 Bit 0	0: ACK Received. No errors.
//*								1: No Ack received...Timeout.
//*
//*****************************************************************************
uchar mcp_ShrtRd(void)
{
     uchar temp1;
	 uchar data1;

// Special Code to Test ALL 6 Addresses for mcp_read.
     i2c_strt();		   			        // Send Start Command
	 i2c_SndByte(MCP_DEVREAD);				// Send Device Read.
	 temp1 = i2c_WaitAck(MCP_TIMEOUT);		// Wait for ACK.
	 if(temp1) {
	   i2c_Stop();							// Stop Command
	   return(1);							// No Ack....Return.
	 }
	 temp1 = i2c_RdByte();					// Read Byte from DAC
	 i2c_SendAck();							// Send ACK.
	 data1 = temp1;							// Good first Byte...Save to output data.
	 temp1 = i2c_RdByte();					// Read Byte from DAC
	 i2c_SendAck();							// Send ACK.
	 temp1 = i2c_RdByte();					// Read Byte from DAC
	 i2c_SendAck();							// Send ACK.
	 temp1 = i2c_RdByte();					// Read Byte from DAC
	 i2c_SendAck();							// Send ACK.
	 temp1 = i2c_RdByte();					// Read Byte from DAC
	 i2c_SendAck();							// Send ACK.
	 i2c_Stop();							// Stop Command
     i2c_Tick();							// Tick for needed delay before continuing.
//     i2c_Tick();							// Tick for needed delay before continuing.
     return(data1);							// Good Return....Return.
}

//*****************************************************************************
//*
//* routine: mcp_WrtDac
//* Date:    May 19, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This command sends 12 Bit Value to the DAC.
//*
//* Parameter:  uint data1:     LSB 12 Bits used for Data to DAC.
//*
//*	Returns : uchar      		0: ACK Received. No errors.
//*								1: No Ack received...Timeout.
//*****************************************************************************
uchar mcp_WrtDac(uint data1)
{
     uchar temp1;
     uchar temp2;
	 uint  temp3;
     i2c_strt();		   			        // Send Start Command
	 i2c_SndByte(MCP_DEVADDR);				// Send Device Address
	 temp1 = i2c_WaitAck(MCP_TIMEOUT);		// Wait for ACK.
/*	 if (temp1) {
	   i2c_Stop();							// Stop Command
       i2c_Tick();							// Tick for needed delay before continuing.
       i2c_Tick();							// Tick for needed delay before continuing.
	   return(1);	  						// Return
	 } */
	 temp2 = (data1 >> 8) & 0x0f;
     temp2 += MCP_FASTMDCMD;	 			// Add in Command Byte.
	 i2c_SndByte(temp2);					// Send MSB 4 Bits.
	 temp1 = i2c_WaitAck(MCP_TIMEOUT);	    // Wait for ACK.
/*	 if (temp1) {
	   i2c_Stop();							// Stop Command
       i2c_Tick();							// Tick for needed delay before continuing.
       i2c_Tick();							// Tick for needed delay before continuing.
	   return(1);	  						// Return
	 } */
	 temp3 = data1 & 0xff;
	 temp1 = (uchar)temp3;
	 i2c_SndByte(temp1);					// Send LSB 8 Bits.
	 temp1 = i2c_WaitAck(MCP_TIMEOUT);	    // Wait for ACK.
/*	 if (temp1) {
	   i2c_Stop();							// Stop Command
       i2c_Tick();							// Tick for needed delay before continuing.
       i2c_Tick();							// Tick for needed delay before continuing.
	   return(1);	  						// Return
	 } */
	 i2c_Stop();							// Stop Command
     i2c_Tick();							// Tick for needed delay before continuing.
//     i2c_Tick();							// Tick for needed delay before continuing.
//	 if (temp1 == 0)
       return(0);	  						// Return
//	 else
//	   return(1);
}

//*****************************************************************************
//*
//* routine: i2c_SndFBit
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine sends the passed bit via the I2C bus. This State is
//* known as "Data Valid(D)".
//*
//*****************************************************************************
void i2c_SndFBit(uchar dbit1)
{
 PORT3.PODR.BYTE &= ~0x08;				// Transition  CClk(P33) from H->L.
 i2c_Tick();							// Tick for needed delay before continuing.
 if (dbit1 & 0x01)
   PORT3.PODR.BYTE |= 0x04;				// Force Din(P32) to High.
 else
   PORT3.PODR.BYTE &= ~0x04;			// Force Din(P32) to Low.
 i2c_Tick();							// Tick for needed delay before continuing.
 PORT3.PODR.BYTE |= 0x08;				// Transition  CClk(P33) from L->H.
 i2c_Tick();							// Tick for needed delay before continuing.
}

//*****************************************************************************
//*
//* routine: i2c_SndFByte
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine sends the passed data via the I2C bus by calling the
//* routine i2c_SndBit.
//*
//*****************************************************************************
void i2c_SndFByte(uchar data1)
{
  unsigned char x, temp1;

  //Set Din(P32) as Output.
  PORT3.PDR.BYTE  |= 0x04;			// Set Din(P32) as Output.

  for(x=0; x<8; x++)
  {
    temp1 = data1 & 0x80;	 		// Get MS Bit to test....
    PORT3.PODR.BYTE &= ~0x08;		// Transition  CClk(P33) from H->L.
	if(temp1)	  					// If set send a 1 bit else a zero bit
      PORT3.PODR.BYTE |= 0x04;		// Force Din(P32) to High.
	else
      PORT3.PODR.BYTE &= ~0x04;		// Force Din(P32) to Low.
    PORT3.PODR.BYTE |= 0x08;		// Transition  CClk(P33) from L->H.
	short_delay(11);						// Delay for 10.8usec.
	data1 <<= 1;					// Shift to next bit to send.
  }
}

//*****************************************************************************
//*
//* routine: i2c_WaitFAck
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine waits the passed amount of time for the ACK from the I2C Bus.
//* If no ACK is seen, then the error flag will be returned set. ACK is known as a
//* pulled High to Low Transition of the SDA/DIN(P32) Pin.
//*
//*	Returns : uchar      		0: ACK Received. No errors.
//*								1: No Ack received...Timeout.
//*	Parameters : uint numloops: Number of loops to wait for ACK from Hardware.
//*			   	 	 			Note that this value should not exceed 256 bytes.
//*
//*****************************************************************************
uchar i2c_WaitFAck(uint numloops)
{
  uint cnt;
  uchar temp1;

  PORT3.PODR.BYTE &= ~0x08;				// Transition  CClk(P33) from H->L.
  //Set Din(P32) as Input.
  PORT3.PODR.BYTE &= ~0x04;				// Set Din(P32) to TriState.
  PORT3.PDR.BYTE  &= ~0x04;				// Set Din(P32) as Input.
  cnt = numloops;	   			        // Set Loopcnt.

  PORT3.PODR.BYTE |= 0x08;				// Transition  CClk(P33) from L->H.
  i2c_Tick();							// Tick for needed delay before continuing.

  temp1 = PORT3.PIDR.BYTE & 0x04;	    // Read Din(P32) value
  while(temp1 && (cnt-->1)) {			// Loop until ACK or timeout.
    temp1 = PORT3.PIDR.BYTE & 0x04;	// Read Din(P32) value
	short_delay(11);						// Delay for 10.8usec.
  }
  PORT3.PODR.BYTE &= ~0x08;				// Transition  CClk(P33) from H->L.
  PORT3.PDR.BYTE  |= 0x04;				// Set Din(P32) as Output.
  if(cnt > 0)
    return(0);							// If cnt positive, no timeout.
  else
    return(1);							// Else timeout.
}

//*****************************************************************************
//*
//* routine: i2c_FStop
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine transitions the DIN/SDA(P32) pin from low to high while the Clk pin
//* is held High. This State is known as "Stop Data Transfer(C)".
//*****************************************************************************
void i2c_FStop(void)
{
  PORT3.PDR.BYTE  |= 0x04;				// Set Din(P32) as Output.
  PORT3.PODR.BYTE |= 0x08;				// Force Clock to High.
  i2c_Tick();							// Tick for needed delay before continuing.
  PORT3.PODR.BYTE |= 0x04;   			// Transition  Din(P32) from L->H.
  i2c_Tick();							// Tick for needed delay before continuing.
}

//*****************************************************************************
//*
//* routine: i2c_fstrt
//* Date:    May 14, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine transitions ths SDA/DIN(P32) Pin from High to low while holding the
//* clock/CClk(P33) pin high. This State is known as "Start Data Transfer(B)".
//*
//*****************************************************************************
void i2c_fstrt(void)
{
  PORT3.PDR.BYTE  |= 0x04;				// Set Din(P32) as Output.
  PORT3.PODR.BYTE |= 0x04;			    // Transition  Din(P32) to H.
  short_delay(1);						// Allow Data to settle.
  PORT3.PODR.BYTE |= 0x08;				// Force Clock to High.
  i2c_Tick();							// Tick for needed delay before continuing.
  PORT3.PODR.BYTE &= ~0x04;				// Transition  Din(P32) from H->L.
  i2c_Tick();							// Tick for needed delay before continuing.
}

//*****************************************************************************
//*
//* routine: mcp_FWrtDac
//* Date:    May 19, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This command sends 12 Bit Value to the DAC.
//*
//* Parameter:  uint data1:     LSB 12 Bits used for Data to DAC.
//*
//*	Returns : uchar      		0: ACK Received. No errors.
//*								1: No Ack received...Timeout.
//*****************************************************************************
uchar mcp_FWrtDac(uint data1)
{
     uchar temp1;
     uchar temp2;
	 uint  temp3;
     i2c_fstrt();		   			        // Send Start Command
	 i2c_SndFByte(MCP_DEVADDR);				// Send Device Address
	 temp1 = i2c_WaitFAck(MCP_TIMEOUT);		// Wait for ACK.
	 temp2 = (data1 >> 8) & 0x0f;
     temp2 += MCP_FASTMDCMD;	 			// Add in Command Byte.
	 i2c_SndFByte(temp2);					// Send MSB 4 Bits.
	 temp1 = i2c_WaitFAck(MCP_TIMEOUT);	    // Wait for ACK.
	 temp3 = data1 & 0xff;
	 temp1 = (uchar)temp3;
	 i2c_SndFByte(temp1);					// Send LSB 8 Bits.
	 temp1 = i2c_WaitFAck(MCP_TIMEOUT);	    // Wait for ACK.
	 i2c_FStop();							// Stop Command
     i2c_Tick();							// Tick for needed delay before continuing.
//     i2c_Tick();							// Tick for needed delay before continuing.
     return(0);	  							// Return
}

//*****************************************************************************
//*
//* routine: mcp_FWrtRpt
//* Date:    Dec 4, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This command sends 12 Bit Value to the DAC.
//*
//* Parameter:  uint data1:     LSB 12 Bits used for Data to DAC.
//*
//*	Returns : uchar      		0: ACK Received. No errors.
//*								1: No Ack received...Timeout.
//*****************************************************************************
uchar mcp_FWrtRpt(uint data1)
{
     uchar temp1;
     uchar temp2;
	 uint  temp3;
	 temp2 = (data1 >> 8) & 0x0f;
     temp2 += MCP_FASTMDCMD;	 			// Add in Command Byte.
	 i2c_SndFByte(temp2);					// Send MSB 4 Bits.
	 temp1 = i2c_WaitFAck(MCP_TIMEOUT);	    // Wait for ACK.
	 temp3 = data1 & 0xff;
	 temp1 = (uchar)temp3;
	 i2c_SndFByte(temp1);					// Send LSB 8 Bits.
	 temp1 = i2c_WaitFAck(MCP_TIMEOUT);	    // Wait for ACK.
	 i2c_FStop();							// Stop Command
     return(0);	  							// Return
}

//*****************************************************************************
//*
//* routine: snd_high
//* Date:    May 19, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine calls the audio output routine and sends a High followed by a delay
//* of 10.8uSec for every tick. Note that the baseline execution of the High is
//* 170usec.
//* Parameter:  uint data1:     Number of 10.8usec Ticks to delay.
//*
//*****************************************************************************
void snd_high(uint time_count)
{
   uint a;
   mcp_FWrtDac(AUDIO_HIGH);
   for (a=0; a<time_count; a++)
     WDR(); //this prevents a timout on enabling
}

//*****************************************************************************
//*
//* routine: snd_low
//* Date:    May 19, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine calls the audio output routine and sends a Low followed by a delay
//* of 10.8uSec for every tick. Note that the baseline execution of the High is
//* 170usec.
//* Parameter:  uint data1:     Number of 10.8usec Ticks to delay.
//*
//*****************************************************************************
void snd_low(uint time_count)
{
   uint a;
   mcp_FWrtDac(AUDIO_LOW);
   for (a=0; a<time_count; a++)
     WDR(); //this prevents a timout on enabling
}

//*****************************************************************************
//*
//* routine: amp_on
//* Date:    May 19, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine powers up the Power Amp.
//*
//*****************************************************************************
void amp_on(void)
{
	// Power On Amp.
	PORT0.PODR.BYTE |= 0x08;				  // Set SD-Amp(P07) to High
	PORT0.PDR.BYTE  |= 0x08;				  // Set SD-Amp(P07) as Output.
}

//*****************************************************************************
//*
//* routine: amp_off
//* Date:    May 19, 2009
//* Updated: February 3, 2015
//* Author:  Ralph Pruitt
//* This routine powers down the Power Amp.
//*
//*****************************************************************************
void amp_off(void)
{
	// Power On Amp.
	PORT0.PODR.BYTE &= ~0x08;	  			  // Set SD-Amp(P07) to High
	PORT0.PDR.BYTE  |= 0x08;				  // Set SD-Amp(P07) as Output.
	// Wait for 50 msec.
	accurate_delay(100);
//  remain_screen();						  // Display Main Screen.
}

#endif

//*****************************************************************************
//*
//* routine: speaker_on
//* Date:    February 3, 2015
//* Author:  Ralph Pruitt
//* This routine turns on the speaker by setting DIN(P32) low.
//*
//*****************************************************************************
void speaker_on( void )
{
	PORT3.PODR.BYTE &= ~0x04;	// Assert Low.
}

//*****************************************************************************
//*
//* routine: speaker_off
//* Date:    February 3, 2015
//* Author:  Ralph Pruitt
//* This routine turns off the speaker by setting DIN(P32) high.
//*
//*****************************************************************************
void speaker_off( void )
{
	PORT3.PODR.BYTE |= 0x04;	// Assert high.
}

//*****************************************************************************
//*
//* routine: speaker_enable
//* Date:    February 27, 2015
//* Author:  Ralph Pruitt
//* This routine enables on the speaker by setting DIN(P32) as Output.
//*
//*****************************************************************************
void speaker_enable( void )
{
	PORT3.PDR.BYTE |= 0x04;		// Assert High for Output.
}

//*****************************************************************************
//*
//* routine: speaker_disable
//* Date:    February 27, 2015
//* Author:  Ralph Pruitt
//* This routine disables the speaker by setting DIN(P32) as Tri-State(Input).
//*
//*****************************************************************************
void speaker_disable( void )
{
	PORT3.PDR.BYTE &= ~0x04;		// Assert Low for Tri-State(Input).
}

//*****************************************************************************
//*
//* routine: Soundsmonitor
//* Date:    February 3, 2015
//* Author:  Ralph Pruitt
//* Sounds Monitor commands
//*
//*****************************************************************************
void Soundsmonitor( char* parm1)
{
  if( strcmp(parm1, "beep400") == 0)
  {
      printf2("Play sound beep400.\n");
      init_sound();
      beep_400hz(500);
      powerdn_sound();
  }
  else if( strcmp(parm1, "beep600") == 0)
  {
      printf2("Play sound beep600.\n");
      init_sound();
      beep_600hz(500);
      powerdn_sound();
  }
  else if( strcmp(parm1, "beep800") == 0)
  {
      printf2("Play sound beep800.\n");
      init_sound();
      beep_800hz(500);
      powerdn_sound();
  }
 else if( strcmp(parm1, "beep1khz") == 0)
  {
     printf2("Play sound beep1khz.\n");
     init_sound();
     beep_1Khz(500);
     powerdn_sound();
  }
 else if( strcmp(parm1, "beep1.2khz") == 0)
  {
     printf2("Play sound beep1.2khz.\n");
     init_sound();
     beep_1K2hz(500);
     powerdn_sound();
  }
 else if( strcmp(parm1, "beep1.4khz") == 0)
  {
     printf2("Play sound beep1.4khz.\n");
     init_sound();
     beep_1K4hz(500);
     powerdn_sound();
  }
 else if( strcmp(parm1, "beep1.6khz") == 0)
  {
     printf2("Play sound beep1.6khz.\n");
     init_sound();
     beep_1K6hz(500);
     powerdn_sound();
  }
 else if( strcmp(parm1, "beepGnote") == 0)
  {
      printf2("Play sound beepGnote.\n");
      init_sound();
      beep_GNote(500);
      powerdn_sound();
  }
 else if( strcmp(parm1, "beepBnote") == 0)
  {
      printf2("Play sound beepBnote.\n");
      init_sound();
      beep_BNote(500);
      powerdn_sound();
  }
 else if( strcmp(parm1, "beepDnote") == 0)
  {
      printf2("Play sound beepDnote.\n");
      init_sound();
      beep_DNote(500);
      powerdn_sound();
  }
 else if( strcmp(parm1, "beepTick") == 0)
  {
      printf2("Play sound beepTick.\n");
      init_sound();
      beep_tick();
      powerdn_sound();
  }
 else if( strcmp(parm1, "beepArpUp") == 0)
  {
      printf2("Play sound beepArpUp.\n");
      init_sound();
      beep_ArpUp();
      powerdn_sound();
  }
 else if( strcmp(parm1, "beepArpDn") == 0)
  {
      printf2("Play sound beepArpDn.\n");
      init_sound();
      beep_ArpDn();
      powerdn_sound();
  }
 else if( strcmp(parm1, "beep3BPulse") == 0)
  {
      printf2("Play sound beep3BPulse.\n");
      init_sound();
      beep_3Bp();
      powerdn_sound();
  }
 else if( strcmp(parm1, "beep3Low") == 0)
  {
      printf2("Play sound beep3Low.\n");
      init_sound();
      beep_3low();
      powerdn_sound();
  }
  else
  {
      printf2("ILLEGAL Sounds Parameter!!\n");
  }
}
