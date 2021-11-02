/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*                           (c) Copyright 2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                          APPLICATION CODE
*
*                                            Renesas RX64M
*                                                on the
*                                      RSKRX64M Evaluation Board
*
* Filename      : spin_led.c
* Version       : V1.00
* Programmer(s) : AA
*                 DC
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include "r_flash_rx_if.h"
//#include  "app_cfg.h"
//#include  "bsp_cfg.h"

//#include  <cpu.h>
//#include  <lib_def.h>

#if       BSP_CFG_OS2_EN   > 0u
#include  <ucos_ii.h>
#endif

#if       BSP_CFG_OS3_EN   > 0u
#include  <os.h>
#endif

//#include  "..\bsp\bsp_led.h"
#include  "spin_led.h"
#include  <LaserP.h>

#if SPIN_LEDS_APP_EN > 0u
#if BSP_CFG_LED_EN   > 0u

#define DEF_ON 1
/*$PAGE*/
/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

#if       BSP_CFG_OS2_EN   > 0u
static  OS_STK   SpinLEDsTaskStk[SPIN_LEDS_APP_TASK_STK_SIZE];
#endif


#if       BSP_CFG_OS3_EN   > 0u
static  CPU_STK  SpinLEDsTaskStk[SPIN_LEDS_APP_TASK_STK_SIZE];
static  OS_TCB   SpinLEDsTCB;
#endif

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*$PAGE*/
/*
*********************************************************************************************************
*                                          SPIN LEDs TASK
*
* Description : Toggles the LEDs in four different sequences.
*
* Arguments   : p_arg   is the argument passed to 'Start()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

void  SpinLEDsTask (void *p_arg)
{
    int  seq;


    (void)&p_arg;

    BSP_LED_Off();                                             /* Turn all LEDs off.                                   */

    seq = 0;

    while (DEF_ON) {                                            /* Task body, always written as an infinite loop.       */

        switch (seq){
            case 0:
                 SpinLEDsSeq0();
                 seq++;
                 break;

            case 1:
                 SpinLEDsSeq1();
                 seq++;
                 break;

            case 2:
                 SpinLEDsSeq2();
                 seq = 0;
                 break;

            default:
                 seq = 0;
                 break;
        }
    }
}


/*
*********************************************************************************************************
*                                    Initialize the Spin LED task
*
* Description :  Create the application tasks.
*
* Argument(s) :  none.
*
* Return(s)   :  none.
*
* Note(s)     :  none.
*********************************************************************************************************
*/

void  SpinLEDsInit (void)
{
#if 0
#if  BSP_CFG_OS2_EN  > 0u
#if (OS_TASK_NAME_EN > 0u)
    CPU_INT08U  err;
#endif


    OSTaskCreateExt((void (*)(void *)) SpinLEDsTask,           /* Create the LEDs task                                 */
                    (void           *) 0,
                    (OS_STK         *)&SpinLEDsTaskStk[SPIN_LEDS_APP_TASK_STK_SIZE - 1],
                    (INT8U           ) SPIN_LEDS_APP_TASK_PRIO,
                    (INT16U          ) SPIN_LEDS_APP_TASK_PRIO,
                    (OS_STK         *)&SpinLEDsTaskStk[0],
                    (INT32U          ) SPIN_LEDS_APP_TASK_STK_SIZE,
                    (void           *) 0,
                    (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

#if (OS_TASK_NAME_EN > 0u)
    OSTaskNameSet(SPIN_LEDS_APP_TASK_PRIO, (INT8U *)"Spin LEDs Task", &err);
#endif
#endif



#if  BSP_CFG_OS3_EN  > 0u
    OS_ERR  err;


    OSTaskCreate((OS_TCB     *)&SpinLEDsTCB,                 /* Create the LEDs task                                 */
                 (CPU_CHAR   *)"Spin LEDs Task",
                 (OS_TASK_PTR ) SpinLEDsTask,
                 (void       *) 0,
                 (OS_PRIO     ) SPIN_LEDS_APP_TASK_PRIO,
                 (CPU_STK    *)&SpinLEDsTaskStk[0],
                 (CPU_STK_SIZE) SPIN_LEDS_APP_TASK_STK_SIZE / 10u,
                 (CPU_STK_SIZE) SPIN_LEDS_APP_TASK_STK_SIZE,
                 (OS_MSG_QTY  ) 0u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
#endif
    (void)&err;
#endif
}


/*
*********************************************************************************************************
*                                         LEDs Sequence #0
*
* Description : This function manipulates the YRDKRX63N's LEDs
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

void  SpinLEDsSeq0 (void)
{
    int  i;
    int  repeat = 0;


    BSP_LED_Off();

    while (repeat != 10) {
        for (i = 1; i <= 4; i++) {
            BSP_LED_Toggle(i);
            SpinLEDsDly(100u);
            BSP_LED_Toggle(i);
        }
        repeat++;
    }
}


/*
*********************************************************************************************************
*                                         LEDs Sequence #1
*
* Description : This function manipulates the YRDKRX63N's LEDs
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

void  SpinLEDsSeq1 (void)
{
    int  repeat = 0;

    BSP_LED_Off();

    while (repeat != 10) {
        BSP_LED_Toggle(0u);
        SpinLEDsDly(100u);
        repeat++;
    }
}


/*
*********************************************************************************************************
*                                         LEDs Sequence #2
*
* Description : This function manipulates the YRDKRX63N's LEDs
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

void  SpinLEDsSeq2 (void)
{
    int  i;
    int  repeat = 0;


    BSP_LED_Off();

    while (repeat != 10) {
        for (i = 4; i >= 1; i--) {
            BSP_LED_Toggle(i);
            SpinLEDsDly(100u);
            BSP_LED_Toggle(i);
        }
        repeat++;
    }
}

/*
*********************************************************************************************************
*                                         LEDs Sequence #2
*
* Description : This function manipulates the YRDKRX63N's LEDs
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

void  SpinLEDson (void)
{
    BSP_LED_On();
}

/*
*********************************************************************************************************
*                                         LEDs Sequence #2
*
* Description : This function manipulates the YRDKRX63N's LEDs
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

void  SpinLEDsoff (void)
{
    BSP_LED_Off();
}

/*
*********************************************************************************************************
*                                          Spin LEDs Dly
*
* Description :  This function delays the LEDs for the given amount of time.
*
* Argument(s) :  none.
*
* Return(s)   :  none.
*
* Note(s)     :  none.
*********************************************************************************************************
*/

void  SpinLEDsDly  (int ms)
{
#if  BSP_CFG_OS2_EN  > 0u
    OSTimeDlyHMSM(0u, 0u, 0u, ms);
#endif


#if  BSP_CFG_OS3_EN  > 0u
    OS_ERR  err;


    OSTimeDlyHMSM(0u, 0u, 0u, ms,
                  OS_OPT_TIME_HMSM_STRICT,
                  &err);
    (void)&err;
#else
    /* Delay 50 microseconds before returning */
    R_BSP_SoftwareDelay(ms, BSP_DELAY_MILLISECS);
#endif
}
    
void SpinLEDmonitor( char* parm1)
{
  char ch;
  // Get passed parameter
  ch = parm1[0];
  switch (ch)
  {
    case '1':
      printf2("Spin LEDs right.\n");
      SpinLEDsSeq0();
      break;
    case '2':
      printf2("Blink LEDs.\n");
      SpinLEDsSeq1();
      break;
    case '3':
      printf2("Spin LEDs left.\n");
      SpinLEDsSeq2();
      break;
    case '4':
      printf2("Turn LEDs On\n");
      SpinLEDson();                                             /* Turn all LEDs off.                                   */
      break;
    case '5':
      printf2("Turn LEDs Off\n");
      SpinLEDsoff();                                             /* Turn all LEDs off.                                   */
      break;
    default:
      printf2("ILLEGAL LED Parameter!!\n");
      break;
  }
}


/*
*********************************************************************************************************
*                                          BSP_LED_Off
*
* Description :  This function Turns off All LEDs
*
* Argument(s) :  none.
*
* Return(s)   :  none.
*
* Note(s)     :  none.
*********************************************************************************************************
*/
void  BSP_LED_Off ( void )
{
    LED0 = LED_OFF;
    LED1 = LED_OFF;
    LED2 = LED_OFF;
    LED3 = LED_OFF;
}

/*
*********************************************************************************************************
*                                          BSP_LED_On
*
* Description :  This function Turns on All LEDs
*
* Argument(s) :  none.
*
* Return(s)   :  none.
*
* Note(s)     :  none.
*********************************************************************************************************
*/
void  BSP_LED_On ( void )
{
    LED0 = LED_ON;
    LED1 = LED_ON;
    LED2 = LED_ON;
    LED3 = LED_ON;
}

/*
*********************************************************************************************************
*                                          BSP_LED_Toggle
*
* Description :  This function Toggles the indicated LED
*
* Argument(s) :  LED_Number
*					0: Toggle All LEDs
*					1: Toggle LED 1
*					2: Toggle LED 2
*					3: Toggle LED 3
*					4: Toggle LED 4
*
* Return(s)   :  none.
*
* Note(s)     :  none.
*********************************************************************************************************
*/
void  BSP_LED_Toggle( int LED_Number )
{
	switch( LED_Number )
	{
	case 0:
		if (LED0 == LED_OFF)
			LED0 = LED_ON;
		else
			LED0 = LED_OFF;
		if (LED1 == LED_OFF)
			LED1 = LED_ON;
		else
			LED1 = LED_OFF;
		if (LED2 == LED_OFF)
			LED2 = LED_ON;
		else
			LED2 = LED_OFF;
		if (LED3 == LED_OFF)
			LED3 = LED_ON;
		else
			LED3 = LED_OFF;
		break;
	case 1:
		if (LED0 == LED_OFF)
			LED0 = LED_ON;
		else
			LED0 = LED_OFF;
		break;
	case 2:
		if (LED1 == LED_OFF)
			LED1 = LED_ON;
		else
			LED1 = LED_OFF;
		break;
	case 3:
		if (LED2 == LED_OFF)
			LED2 = LED_ON;
		else
			LED2 = LED_OFF;
		break;
	case 4:
		if (LED3 == LED_OFF)
			LED3 = LED_ON;
		else
			LED3 = LED_OFF;
		break;
	default:
		break;
	}
}
#endif
#endif
