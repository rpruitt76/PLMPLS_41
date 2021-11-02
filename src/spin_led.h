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
*                                        SPIN LEDs APPLICATION
*
*                                            Renesas RX64M
*                                                on the
*                                      RSKRX64M Evaluation Board
*
* Filename      : spin_led.h
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/

#if SPIN_LEDS_APP_EN > 0u
void  SpinLEDsInit (void);
void  SpinLEDsTask (void *p_arg);

void  SpinLEDsSeq0 (void);
void  SpinLEDsSeq1 (void);
void  SpinLEDsSeq2 (void);
void  SpinLEDson (void);
void  SpinLEDsoff (void);
void SpinLEDmonitor( char* param1);
//void  SpinLEDsDly  (CPU_INT16U ms);
void  SpinLEDsDly  (int ms);
void  BSP_LED_Off ( void );
void  BSP_LED_On ( void );
void  BSP_LED_Toggle( int LED_Number );
#endif

