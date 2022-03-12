/*
*********************************************************************************************************
*
* Filename      : monitor.c
* Version       : V1.00
* Programmer(s) : Ralph Pruitt
* Date:           January 3, 2015
* Updated:        January 3, 2015
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

//#include  "app_cfg.h"
//#include  "bsp_cfg.h"
#include "r_flash_rx_if.h"
#include  "LaserP.h"

#if MONITOR_APP_EN > 0u
//#include  <cpu.h>
//#include  <lib_def.h>
#include  <stdio.h>
#include  <string.h>
#include <r_cg_userdefine.h>
#include "r_cg_macrodriver.h"
#include "r_cg_sci.h"

#if       BSP_CFG_OS2_EN   > 0u
#include  <ucos_ii.h>
#endif

#if       BSP_CFG_OS3_EN   > 0u
#include  <os.h>
#endif
#include  "spin_led.h"
#include "platform.h"
//#include  "fs_app.h"

#define DEF_ON 1
/*$PAGE*/
/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
#define	INIT_LOOP_CNT	20			// Initial Loop Count for a key Press.

static int	Loop_Var_Count = 0;		// Variable to track Loop Count.

#if       BSP_CFG_OS3_EN   > 0u
static  CPU_STK  MonitorTaskStk[MONITOR_APP_TASK_STK_SIZE];
static  OS_TCB   MonitorTCB;
#endif

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*$PAGE*/
/*
*********************************************************************************************************
*                                          Monitor TASK
*
* Description : Monitors the console input and activates user requested functions
*
* Arguments   : p_arg   is the argument passed to 'Start()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

//void  MonitorTask (void *p_arg)
void  MonitorTask (void)
{
	int x;
#ifdef STRM_BOTH
  #ifdef STRM_SPY
    char parm1[80];
    char cmdString[80];
  #else
	char tmpString[80];
    char parm1[80];
    char cmdString[80];
  #endif
#endif
#ifdef STRM_PRINTF
    char parm1[80];
    char cmdString[80];
#endif
#ifdef STRM_COM
    char tmpString[80];
    char tempchar;
    char *tempString_ptr;
   	char parm1[80];
   	char cmdString[80];
#endif

    //(void)&p_arg;

#ifdef STRM_BOTH
    // Clear tmpString.
#endif
   	// Enable Streaming for Monitor
   	StrmOn = 1;

    printf2("***************************************************************\n");
    printf2("PLM Monitor Starting... \n\n");
    printf2("***************************************************************\n");
    printf2("PLM OS Version 3.01\n");
    printf2("Copyright: Oct 11, 2020\n");
    printf2("Property of Cold Laser Therapeutics, LLC\n");
    printf2("***************************************************************\n\n\n");
    
    while (DEF_ON) {                                            /* Task body, always written as an infinite loop.       */
    	// Clear strings for next pass;
    	for (x=0; x<80; x++)
    	{
#ifdef STRM_BOTH
  #ifdef STRM_SPY
    		cmdString[x] = 0x00;
    		parm1[x] = 0x00;
  #else
    		tmpString[x] = 0x00;
    		cmdString[x] = 0x00;
    		parm1[x] = 0x00;
  #endif
#endif
#ifdef STRM_PRINTF
    		cmdString[x] = 0x00;
    		parm1[x] = 0x00;
#endif
#ifdef STRM_COM
    		tmpString[x] = 0x00;
    		cmdString[x] = 0x00;
    		parm1[x] = 0x00;
#endif
    	}
        // Force tempchar to clear.
        tempchar = 0x00;

    	printf2("\n");
    	printf2(" > ");

        //NOTE: There are two ways to perform the following. Will use scanf while I am using the builtin monitor. The problem with this
        //      method is that it will lock the tass until the next message is received. It is not truly multitasking in nature. But
        //      there is no choice while in early. The second method will use custom code that will scan the attached COM port and will
        //      fill the buffer one character at a time till we have all needed characters. In between each character, it will sleep for 50 msec
        //      to allow all other tasks to be active.
        
#ifdef STRM_BOTH
  #ifdef STRM_SPY
        scanf("%s %s", cmdString, parm1);
  #else
        R_SCI5_Serial_Rceive( tmpString, RX_STRING_WAIT);
        printf("%s\n",tmpString);
        sscanf(tmpString,"%s ,%s",cmdString,parm1);
        strcpy(tmpString, "");
  #endif
#else
  #ifdef STRM_PRINTF
        // METHOD 1
        scanf("%s %s", cmdString, parm1);
  #endif
  #ifdef STRM_COM
        // METHOD 1
//        R_SCI5_Serial_Rceive( tmpString, RX_STRING_WAIT);
//        sscanf(tmpString,"%s %s",cmdString,parm1);
//        strcpy(tmpString, "");
        // METHOD 2
        tempString_ptr = tmpString;
        while (tempchar != 0x0d)
        {
        	if (R_SCI5_Serial_Rceive( &tempchar, RX_CHAR) == 0x00)
        	{
        		if (tempchar != 0x00)
        		{
        			*tempString_ptr++ = tempchar;
        		} // EndIf (*tempchar != 0x00)
        	} // EndIf (R_SCI5_Serial_Rceive( tempchar, RX_CHAR) == 0x00)
        } //EndWhile (tempchar[0] != 0x0d)
        sscanf(tmpString,"%s %s",cmdString,parm1);
        strcpy(tmpString, "");
  #endif
#endif
        MonitorParse2 (cmdString, parm1);
#if 0
        printf("%s %s\n\n", cmdString, parm1);
        // Now determine what kind of string.
        if( strncmp(cmdString, "fs_app", 6) == 0)
        {
          //App_Fs_monitor( parm1 );
        }
#if SPIN_LEDS_APP_EN > 0u
#if BSP_CFG_LED_EN   > 0u
        else if( strncmp(cmdString, "leds", 4) == 0)
        {
          // LED Command...Pass parameter to SpinLedmonitor for processing.
          SpinLEDmonitor( parm1 );
        } // EndIf
#endif
#endif
        else if( strncmp(cmdString, "LCD", 3) == 0)
        {
          LCDmonitor( parm1 );
        }
        else if( strncmp(cmdString, "sounds", 6) == 0)
        {
        	Soundsmonitor( parm1 );
        }
        else if( strncmp(cmdString, "protocol", 8) == 0)
        {
        	Protocolmonitor( parm1 );
        }
        else if( strncmp(cmdString, "macro", 4) == 0)
        {
        	Macromonitor( parm1 );
        }
        else if( strncmp(cmdString, "laser", 5) == 0)
        {
        	Lasermonitor( parm1 );
        }
        else if( strncmp(cmdString, "laseron", 7) == 0)
        {
        	LaserOnmonitor( parm1 );
        }
        else if( strncmp(cmdString, "Key", 3) == 0)
        {
        	Keymonitor( parm1 );
        }
        else if( strncmp(cmdString, "misc", 4) == 0)
        {
        	Miscmonitor( parm1 );
        }
        else if( strncmp(cmdString, "setTime", 7) == 0)
        {
        	SetTimemonitor( parm1 );
        }
        else if( strncmp(cmdString, "setDate", 7) == 0)
        {
        	SetDatemonitor( parm1 );
        }
        else if( strncmp(cmdString, "setSN", 5) == 0)
        {
        	SetSNmonitor( parm1 );
        }
        else if( strncmp(cmdString, "setMode", 7) == 0)
        {
        	SetModeMonitor( parm1 );
        }
        else if( strncmp(cmdString, "setLDay", 7) == 0)
        {
        	SetLDayMonitor( parm1 );
        }
        else if( strncmp(cmdString, "testPBF", 7) == 0)
        {
        	testPBFmonitor( parm1 );
        }
        else if( strncmp(cmdString, "testO", 5) == 0)
        {
        	TestOriginmonitor( parm1 );
        }
        else
        {
          printf2("Bad Command!!\n");
        } // EndElse
#endif
    } // EndWhile
}

void  MonitorParse2 (char *cmdString, char *parm1)
{
	// Kick Two Minute Timer..
	two_min_start();

	// Enable Streaming for Monitor
	StrmOn = 1;

	printf("%s %s\n\n", cmdString, parm1);
	// Now determine what kind of string.
	if( strncmp(cmdString, "TR", 2) == 0)
	{
		monPrint("MNTR", "TR Command");		// Send Status Message
		sleep_code();							// Place Hardware into Sleep Mode.
//		PowerON_Reset_PC();
	}
	else if( strncmp(cmdString, "TS", 2) == 0)
	{
		monPrint("MNTR", "TS Command");		// Send Status Message
		sleep_code();							// Place Hardware into Sleep Mode.
	}
	else if( strncmp(cmdString, "CLR", 3) == 0)
	{
		cleanup_macros();						// Test and cleanup Macro Vars.
		cnt_dwn_flg = 0;						// Deactivate Timer.
		tmr_update_flg = 2;						// Arm Update to Deactivate Var Update.
		monPrint("MNTR", "CLR-Restore Command");		// Send Status Message
		restore_vars();									// Restore Vars.
	}
	else if( strncmp(cmdString, "STOP", 4) == 0)
	{
		cleanup_macros();						// Test and cleanup Macro Vars.
		cnt_dwn_flg = 0;						// Deactivate Timer.
		tmr_update_flg = 2;					// Arm Update to Deactivate Var Update.
		laser_off();	   	   					// Turn-Off Laser.
		monPrint("MNTR", "STOP-Lasers Off..Main");		// Send Status Message
		restore_vars();  			   	 		// Restore Key Variables.
		mode = Main;	  						// Set New Mode.
	}
	else if( strncmp(cmdString, "fs_app", 6) == 0)
	{
		//App_Fs_monitor( parm1 );
	}
#if SPIN_LEDS_APP_EN > 0u
#if BSP_CFG_LED_EN   > 0u
	else if( strncmp(cmdString, "leds", 4) == 0)
	{
		// LED Command...Pass parameter to SpinLedmonitor for processing.
		SpinLEDmonitor( parm1 );
	} // EndIf
#endif
#endif
	else if( strncmp(cmdString, "LCD", 3) == 0)
	{
		LCDmonitor( parm1 );
	}
	else if( strncmp(cmdString, "sounds", 6) == 0)
	{
		Soundsmonitor( parm1 );
	}
	else if( strncmp(cmdString, "protocol", 8) == 0)
	{
		Protocolmonitor( parm1 );
	}
	else if( strncmp(cmdString, "macro", 4) == 0)
	{
		Macromonitor( parm1 );
	}
	else if(( strncmp(cmdString, "laser", 5) == 0)
			&& (!tst_laser_active()))
	{
		Lasermonitor( parm1 );
	}
	else if(( strncmp(cmdString, "laseron", 7) == 0)
			&& (!tst_laser_active()))
	{
		LaserOnmonitor( parm1 );
	}
	else if( strncmp(cmdString, "Key", 3) == 0)
	{
		Keymonitor( parm1 );
	}
	else if( strncmp(cmdString, "misc", 4) == 0)
	{
		Miscmonitor( parm1 );
	}
	else if(( strncmp(cmdString, "SetPGM", 6) == 0)
			&& (!tst_laser_active()))
	{
		SetProgram( parm1 );
	}
	else if(( strncmp(cmdString, "TimerSet", 8) == 0)
			&& (!tst_laser_active()))
	{
		SetTimer( parm1 );
	}
	else if( strncmp(cmdString, "setTime", 7) == 0)
	{
		SetTimemonitor( parm1 );
	}
	else if( strncmp(cmdString, "setDate", 7) == 0)
	{
		SetDatemonitor( parm1 );
	}
	else if( strncmp(cmdString, "setSN", 5) == 0)
	{
		SetSNmonitor( parm1 );
	}
	else if(( strncmp(cmdString, "setMode", 7) == 0)
		&& (!tst_laser_active()))
	{
		SetModeMonitor( parm1 );
	}
	else if( strncmp(cmdString, "setLDay", 7) == 0)
	{
		SetLDayMonitor( parm1 );
	}
	else if( strncmp(cmdString, "testPBF", 7) == 0)
	{
		testPBFmonitor( parm1 );
	}
	else if( strncmp(cmdString, "setPBF", 6) == 0)
	{
		setPBFmonitor( parm1 );
	}
	else if( strncmp(cmdString, "setUPgm", 7) == 0)
	{
		setUPgmmonitor( parm1 );
	}
	else if(( strncmp(cmdString, "testO", 5) == 0)
		&& (!tst_laser_active()))
	{
		TestOriginmonitor( parm1 );
	}
	else if(( strncmp(cmdString, "mode", 4) == 0)
		&& (!tst_laser_active()))
	{
		ModeMonitor( parm1 );
	}
	else if(( strncmp(cmdString, "hmc", 3) == 0)
		&& (!tst_laser_active()))
	{
		hmcmonitor( parm1 );
	}
	else if( strncmp(cmdString, "KP", 2) == 0)
	{
		KeyPressmonitor( parm1 );
	}
	else if( strncmp(cmdString, "timeOut", 7) == 0)
	{
		timeOutmonitor( parm1 );
	}
	else if( strncmp(cmdString, "WrMAdr", 6) == 0)
	{
		Wr_MacAddrmonitor( parm1 );
	}
	else if( strncmp(cmdString, "RdMAdr", 6) == 0)
	{
		Rd_MacAddrmonitor( parm1 );
	}
	else
	{
		if  (tst_laser_active())
			printf2("Laser Event Active!!\n");
		else
			printf2("Bad Command!!\n");
	} // EndElse

	// Disable Streaming for Monitor
	StrmOn = 0;
}

/*****************************************************************************
 *
 * routine: KeyPressmonitor
 * Date: 	February 6, 2021
 * Updated: February 6, 2021
 * Author:  Ralph Pruitt
 * @brief	This routine processes all key presses from Monitor
 *
 * INPUT:
 *  @param	None
 *
 * OUTPUT:
 * 	@retval None
 *
 *****************************************************************************/
void KeyPressmonitor(char *parm1) {

	// First Validate if we can receive a Key Press..
	if (Loop_Var_Count > 0)
	{
		monPrint("ERROR", "Key Press Active");		// Send Status Message
	} // EndIf (Loop_Var_Count > 0)
	else
	{
		if ( strcmp(parm1, "1") == 0)
		{
			// Key 1					ONE		07
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = ONE;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "2") == 0)
		{
			// Key 2					TWO		8
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = TWO;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "3") == 0)
		{
			// Key 3					THREE		9
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = THREE;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "4") == 0)
		{
			// Key 4					FOUR		10
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = FOUR;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "5") == 0)
		{
			// Key 5					FIVE		11
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = FIVE;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "6") == 0)
		{
			// Key 6					SIX			12
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = SIX;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "7") == 0)
		{
			// Key 7					SEVEN		13
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = SEVEN;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "8") == 0)
		{
			// Key 8					EIGHT		14
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = EIGHT;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "9") == 0)
		{
			// Key 9					NINE		15
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = NINE;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "0") == 0)
		{
			// Key 0					ZERO		17
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = ZERO;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "DP") == 0)
		{
			// Key .(DP)				PERIOD		16
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = PERIOD;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "BS") == 0)
		{
			// Key <(BS)				BACK		18
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = BACK;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "UP") == 0)
		{
			// Key Up					UP			22
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = UP;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "DOWN") == 0)
		{
			// Key Down					DOWN		23
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = DOWN;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "LEFT") == 0)
		{
			// Key Left				LEFT		19
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = LEFT;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "RIGHT") == 0)
		{
			// Key Right				RIGHT		21
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = RIGHT;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "OK") == 0)
		{
			// Key OK					LASER		20
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = LASER;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "CANCEL") == 0)
		{
			// Key Cancel				CANCEL		01
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = CANCEL;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "SELECT") == 0)
		{
			// Key Select				SELECT		02
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = SELECT;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "DELETE") == 0)
		{
			// Key Delete				DELETE		03
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = DELETE;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "TIME") == 0)
		{
			// Key Time				TIME		05
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = TIME;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "LIGHT") == 0)
		{
			// Key Light				LIGHT		06
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = LIGHT;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "POWER") == 0)
		{
			// Key Laser On/Off			POWER		04
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = POWER;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "OFF") == 0)
		{
			// Key Off					OFF		24
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = OFF;					// Setup Key Var.
		}
		else if ( strcmp(parm1, "START") == 0)
		{
			// Key Start				START		25
			Loop_Var_Count = INIT_LOOP_CNT;		// Setup Loop Count
			mntr_key_var = START;					// Setup Key Var.
		}
	} // EnndElse (Loop_Var_Count > 0)
}
/*****************************************************************************
 *
 * routine: Mntr_Loop_Clr
 * Date: 	February 6, 2021
 * Updated: February 6, 2021
 * Author:  Ralph Pruitt
 * @brief	This routine decrements the loaded count(Loop_Var_Count) and clears mntr_key_var
 * 			when count gets to zero.
 *
 * INPUT:
 *  @param	None
 *
 * OUTPUT:
 * 	@retval None
 *
 *****************************************************************************/
void Mntr_Loop_Clr( void )
{
	// Test if Loop_Var_Count is active.
	if (Loop_Var_Count > 0)
	{
		// If Yes, Decrement.
		Loop_Var_Count--;
		// If zero, Clear active character.
		if (Loop_Var_Count == 0)
			mntr_key_var = 0;
	}
}

#ifdef TST_PATCH
unsigned char MonitorParse(void)
{
	int x;
#ifdef STRM_BOTH
  #ifdef STRM_SPY
    char parm1[80];
    char cmdString[80];
  #else
	char tmpString[80];
    char parm1[80];
    char cmdString[80];
  #endif
#endif
#ifdef STRM_PRINTF
    char parm1[80];
    char cmdString[80];
#endif
#ifdef STRM_COM
    char tmpString[80];
   	char parm1[80];
   	char cmdString[80];
#endif

    //(void)&p_arg;

#ifdef STRM_BOTH
    // Clear tmpString.
#endif
    	// Clear strings for next pass;
    	for (x=0; x<80; x++)
    	{
#ifdef STRM_BOTH
  #ifdef STRM_SPY
    		cmdString[x] = 0x00;
    		parm1[x] = 0x00;
  #else
    		tmpString[x] = 0x00;
    		cmdString[x] = 0x00;
    		parm1[x] = 0x00;
  #endif
#endif
#ifdef STRM_PRINTF
    		cmdString[x] = 0x00;
    		parm1[x] = 0x00;
#endif
#ifdef STRM_COM
    		tmpString[x] = 0x00;
    		cmdString[x] = 0x00;
    		parm1[x] = 0x00;
#endif
    	}


    	printf2("\n > ");

        //NOTE: There are two ways to perform the following. Will use scanf while I am using the builtin monitor. The problem with this
        //      method is that it will lock the tass until the next message is received. It is not truly multitasking in nature. But
        //      there is no choice while in early. The second method will use custom code that will scan the attached COM port and will
        //      fill the buffer one character at a time till we have all needed characters. In between each character, it will sleep for 50 msec
        //      to allow all other tasks to be active.

#ifdef STRM_BOTH
  #ifdef STRM_SPY
        scanf("%s %s", cmdString, parm1);
  #else
        R_SCI5_Serial_Rceive( tmpString, RX_STRING_WAIT);
        printf("%s\n",tmpString);
        sscanf(tmpString,"%s ,%s",cmdString,parm1);
        strcpy(tmpString, "");
  #endif
#else
  #ifdef STRM_PRINTF
        // METHOD 1
        scanf("%s %s", cmdString, parm1);
  #endif
  #ifdef STRM_COM
        // METHOD 1
        R_SCI5_Serial_Rceive( tmpString, RX_STRING_WAIT);
        sscanf(tmpString,"%s %s",cmdString,parm1);
        strcpy(tmpString, "");
  #endif
#endif
        printf("%s %s\n\n", cmdString, parm1);
        // Now determine what kind of string.
        if( strncmp(cmdString, "cmd", 3) == 0)
        {
        	if(strncmp(parm1, "cancel", 6) == 0)
        		return 1;
        	else if(strncmp(parm1, "select", 6) == 0)
        		return 2;
        	else if(strncmp(parm1, "delete", 6) == 0)
        		return 3;
        	else if(strncmp(parm1, "on", 2) == 0)
        		return 4;
        	else if(strncmp(parm1, "time", 4) == 0)
        		return 5;
        	else if(strncmp(parm1, "light", 5) == 0)
        		return 6;
        	else if(strncmp(parm1, "1", 1) == 0)
        		return 7;
        	else if(strncmp(parm1, "2", 1) == 0)
        		return 8;
        	else if(strncmp(parm1, "3", 1) == 0)
        		return 9;
        	else if(strncmp(parm1, "4", 1) == 0)
        		return 10;
        	else if(strncmp(parm1, "5", 1) == 0)
        		return 11;
        	else if(strncmp(parm1, "6", 1) == 0)
        		return 12;
        	else if(strncmp(parm1, "7", 1) == 0)
        		return 13;
        	else if(strncmp(parm1, "8", 1) == 0)
        		return 14;
        	else if(strncmp(parm1, "9", 1) == 0)
        		return 15;
        	else if(strncmp(parm1, ".", 1) == 0)
        		return 16;
        	else if(strncmp(parm1, "0", 1) == 0)
        		return 17;
        	else if(strncmp(parm1, "back", 4) == 0)
        		return 18;
        	else if(strncmp(parm1, "left", 4) == 0)
        		return 19;
        	else if(strncmp(parm1, "pulse", 5) == 0)
        		return 20;
        	else if(strncmp(parm1, "right", 5) == 0)
        		return 21;
        	else if(strncmp(parm1, "up", 2) == 0)
        		return 22;
        	else if(strncmp(parm1, "down", 4) == 0)
        		return 23;
        	else if(strncmp(parm1, "off", 3) == 0)
        		return 24;
        	else
        		return 0;
        }
        else
        {
			if( strncmp(cmdString, "fs_app", 6) == 0)
			{
			  //App_Fs_monitor( parm1 );
			}
#if SPIN_LEDS_APP_EN > 0u
#if BSP_CFG_LED_EN   > 0u
			else if( strncmp(cmdString, "leds", 4) == 0)
			{
			  // LED Command...Pass parameter to SpinLedmonitor for processing.
			  SpinLEDmonitor( parm1 );
			} // EndIf
#endif
#endif
			else if( strncmp(cmdString, "LCD", 3) == 0)
			{
			  LCDmonitor( parm1 );
			}
			else if( strncmp(cmdString, "sounds", 6) == 0)
			{
				Soundsmonitor( parm1 );
			}
			else if( strncmp(cmdString, "protocol", 8) == 0)
			{
				Protocolmonitor( parm1 );
			}
			else if( strncmp(cmdString, "macro", 4) == 0)
			{
				Macromonitor( parm1 );
			}
			else if( strncmp(cmdString, "laser", 5) == 0)
			{
				Lasermonitor( parm1 );
			}
			else if( strncmp(cmdString, "laseron", 7) == 0)
			{
				LaserOnmonitor( parm1 );
			}
			else if( strncmp(cmdString, "Key", 3) == 0)
			{
				Keymonitor( parm1 );
			}
			else if( strncmp(cmdString, "misc", 4) == 0)
			{
				Miscmonitor( parm1 );
			}
			else
			{
			  printf2("Bad Command!!\n");
			} // EndElse
			return 0;
        } // EndElse ( strncmp(cmdString, "cmd", 4) == 0)
}
#endif

/*
*********************************************************************************************************
*                                    Initialize the Monitor task
*
* Description :  Create the Monitor task.
*
* Argument(s) :  none.
*
* Return(s)   :  none.
*
* Note(s)     :  none.
*********************************************************************************************************
*/
#if 0
void  MonitorInit (void)
{
#if  BSP_CFG_OS3_EN  > 0u
    OS_ERR  err;


    OSTaskCreate((OS_TCB     *)&MonitorTCB,                 /* Create the LEDs task                                 */
                 (CPU_CHAR   *)"Monitor Task",
                 (OS_TASK_PTR ) MonitorTask,
                 (void       *) 0,
                 (OS_PRIO     ) MONITOR_APP_TASK_PRIO,
                 (CPU_STK    *)&MonitorTaskStk[0],
                 (CPU_STK_SIZE) MONITOR_APP_TASK_STK_SIZE / 10u,
                 (CPU_STK_SIZE) MONITOR_APP_TASK_STK_SIZE,
                 (OS_MSG_QTY  ) 0u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
#endif
    (void)&err;
}
#endif

#endif

