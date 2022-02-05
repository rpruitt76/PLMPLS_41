//****************************************************************************
//*
//* LaserP.h
//*
//****************************************************************************
//* Laser Pulsar Embedded Software
//* Date: December 1, 2003
//* Updated for Mark III: September 29,2006
//* Designer: Ralph Pruitt
//* Property: LED Healing Light, INC.
//* Copyright: December 2003
//* Description: This software is used with the 1st release of the "Laser Pulsar".
//* This product is used in cold Laser Therapy. This design supports this product
//* to read the keyboard, display important Information via the LCD Display, and
//* to energize the four 635nm Laser Diodes with modulation frequencies between
//* 1Hz and 100Khz.
//*****************************************************************************
//*
//* This set of code supports all unique defines needed to support the Laser
//* Pulsar software.
//*****************************************************************************

//*****************************************************************************
//* Misc Configurations with the following flags...
//* Mark IV New LCD
//* PROFSNL:YES  DEBUGGR:YES   SLOWCLK:YES  MARKIV:YES  NEW_LCD:YES   PARKCL:NO
//*
//* Mark IV Old LCD
//* PROFSNL:YES  DEBUGGR:YES   SLOWCLK:YES  MARKIV:YES  NEW_LCD:NO    PARKCL:NO
//*
//* Mark III Professional Old LCD
//* PROFSNL:YES  DEBUGGR:YES   SLOWCLK:YES  MARKIV:NO   NEW_LCD:NO    PARKCL:NO
//*
//* Mark III Professional New LCD
//* PROFSNL:YES  DEBUGGR:YES   SLOWCLK:YES  MARKIV:NO   NEW_LCD:YES   PARKCL:NO
//*
//* Mark III Personal New LCD
//* PROFSNL:NO   DEBUGGR:YES   SLOWCLK:YES  MARKIV:NO   NEW_LCD:YES   PARKCL:NO
//*
//* Mark III Personal Old LCD
//* PROFSNL:NO   DEBUGGR:YES   SLOWCLK:YES  MARKIV:NO   NEW_LCD:NO    PARKCL:NO
//*
//* Mark III Parker College Personal Old LCD
//* PROFSNL:NO   DEBUGGR:YES   SLOWCLK:YES  MARKIV:NO   NEW_LCD:NO    PARKCL:YES
//*
//* Mark III Parker College Personal New LCD
//* PROFSNL:NO   DEBUGGR:YES   SLOWCLK:YES  MARKIV:NO   NEW_LCD:YES   PARKCL:YES
//*
//* Mark III Parker College Professional New LCD
//* PROFSNL:YES  DEBUGGR:YES   SLOWCLK:YES  MARKIV:NO   NEW_LCD:YES   PARKCL:YES
//*
//* Mark III Parker College Professional Old LCD
//* PROFSNL:YES  DEBUGGR:YES   SLOWCLK:YES  MARKIV:NO   NEW_LCD:NO    PARKCL:YES
//*

#include "hmc832.h"
//*****************************************************************************
//*
//* Switch Definitions
//*
//*****************************************************************************
#define	 GRAPHICS			1			// Define to enable Graphics LCD Module.
//*****************************************************************************
//*
//* Compiler Flags
//*
//*****************************************************************************
//       KEY_FREQ       133          : A. 133.33 Mhz Design
//       KEY_FREQ       120          : B. 120 Mhz Design
//       KEY_FREQ       80           : C.  80 Mhz Design
//       KEY_FREQ       32           : D.  32 Mhz Design
//       KEY_FREQ       140          : E. 140 Mhz Design
//       KEY_FREQ       78           : F. 78 Mhz Design
#define  KEY_FREQ		120          // This Flag is used to activate Different Designs.
//#define  MCP4725		1			 // Define this flag if we are using the Mark IV MCP4725 Hardware.
#define	 AUDIO_HIGH		0xFFF		 // High Level Audio
#define	 AUDIO_LOW		0x0		 	 // Low Level Audio
//#define  BT_TEST		1			 // Define this flag for current BT Test Code to be active.
//#define  BT_DEV		1			 // Define this flag for current New BT Test Code to be active.
#define  PROFSNL		1			 // Define this flag to activate Professional Mode design else it will be a personal
//#define  DEBUGGR        1			 // Define this flag to activate debugger...
//#define	 LEASEOP		1			 // Define this flag if this unit has controlled minutes for users.
#define  PHONENUM       "(303)570-3206" // Phone number to call for more minutes.
#define	 SLOWCLK	    1			 // Define to use 8Mhz Internal Micro Clock
//#define  MARKIV         1			 // Define if this is a Mark IV Load
//#define  MARKIVE          1			 // Define if this is a Mark IV Expanded Load
//#define  MARKVA         1			 // Define if this is a Mark IV Audio Load
//#define  MARKV        1			 // Define if this is a Mark V Load
//#define  MARK3SP		1			 // Define if this is a Mark III SP Load.
//#define  MARK1B		1			 // Define if this is a Mark Ib load.
//#define	 sixdigit		1			 // Define this to allow 6 digit selection for entries.
		 							 // NOTE: Only use sixdigit in Mark3SP Mode.
#define  NEW_LCD		1			 // Define if this uses the new AZ White Display.
//#define Vers1_2HW		1			 // Define if this is an older 2.1 Version Board.
									 // NOTE: This above flag is specific to Mark V Build.
									 //       Enable for older HW...1.2 Boards.
//#define  PARKCL			1			 // Define if this is a Mark III Park College Design
                                     // Comment it out for a Mark III Load.
// Mark III Version Numbers and Dates...Release 3.3
#define	 VERSIONNUM		"4.04" 		 // Current Version Revision.(4 CHARS)
#define  RELDATE		"02/05/22"	 // Current Release Date.(8 Chars)
#define	 VERSIONSTR		"PLM PLUS V4.04 Feb 5, 2022" 		 // Current Version String Revision.

//#define	 MAX_MULT_FREQ  195000000		// Highest Frequency is 195000000MHz
//#define	 DEF_HIGH_FREQ	180000000		// Default High Frequency.
#define	 MAX_MULT_FREQ  150000000		// Highest Frequency is 195000000MHz
#define	 DEF_HIGH_FREQ	150000000		// Default High Frequency.
// Mark III
#define	 DELAY_KEY			50			// Delay between Keys

#ifdef CLW
#define	 CUSTOM_START		1		    // Start of Custom Protocols
#define	 CUSTOM_END			300			// End of Custom Protocols
#define  CUSTOM_REND		233			// Real End of Custom Protocols
#define	 CUSTOM2_START		301		    // Start of Custom Protocols
#define	 CUSTOM2_END		400			// End of Custom Protocols
#define  CUSTOM2_REND		387			// Real End of Custom Protocols
#define	 CUSTOM3_START		401		    // Start of Custom Protocols
#define	 CUSTOM3_END		500			// End of Custom Protocols
#define  CUSTOM3_REND		462			// Real End of Custom Protocols
#define	 CUSTOM4_START		501		    // Start of Custom Protocols
#define	 CUSTOM4_END		599			// End of Custom Protocols
#define  CUSTOM4_REND		551			// Real End of Custom Protocols
#else
#define	 CUSTOM_START		1		    // Start of Custom Protocols
#define	 CUSTOM_END			500			// End of Custom Protocols
#define  CUSTOM_REND		44			// Real End of Custom Protocols
#endif
#define	 USER_STRT			600			// Start of User Protocols
#define	 USER_END			799			// End of User Protocols
#define	 USER_REND			799			// Real End of User Protocols
#define	 SWEEP_STRT			990			// Start of Sweep Protocols
#define	 SWEEP_END			999			// End of Sweep Protocols
#define	 SWEEP_REND			999			// Real End of Sweep Protocols
#define	 CSTMSUPR_STRT		800			// Start of Custom Macros
#define	 CSTMSUPR_REND		839			// Real End of Custom Macros
#define	 CSTMSUPR_END		899			// End of Custom Macros
#define	 USERSUPR_STRT		900			// Start of User Macros
#define	 USERSUPR_REND		929			// Real End of User Macros
#define	 USERSUPR_END		989			// End of User Macros
//*****************************************************************************
//*
//* Key Type Definitions
//*
//*****************************************************************************
typedef unsigned char unsigned8;
typedef signed char signed8;
typedef unsigned int unsigned16;
typedef signed int signed16;
typedef unsigned long int unsigned32;
typedef signed long int signed32;
typedef unsigned8 atomic_int;

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char UCHAR;
typedef unsigned int UINT;
typedef unsigned long ULONG;

//*****************************************************************************
//*
//* External Routine Definitions
//*
//*****************************************************************************
extern char task(char );
extern void led_on(void);
extern void led_off(void);
extern void led_fade(void);
extern void accurate_delay(unsigned char);
extern void configure_lcd(unsigned char);
extern void configure_lcdoff(unsigned char);
extern void turnon_lcd(void);
extern void turnoff_lcd(void);
extern unsigned char set_cursor(unsigned char, unsigned char, unsigned char);
extern unsigned char clear_screen(void);
extern unsigned char back_space(void);
extern void short_delay(unsigned char);
extern unsigned char scan_keyboard(void);
extern void monPrint_Key(unsigned char keynum);
extern void  MonitorParse2 (char *cmdString, char *parm1);
//extern char *itoaa(unsigned char);
extern void save_vars(void);
extern void restore_vars(void);
extern void laser_off(void);
extern void run_laser(void);
extern void two_sec_start(void);			   // Start or re-start 2 Second Timer.
extern unsigned char p5_sec_test(void);	       // Test Two Second Timer.
extern void p5_sec_clear(void);			       // Clear Two Second Timer
extern void p5_sec_start(void);			       // Start or re-start 2 Second Timer.
extern unsigned char two_sec_test(void);	   // Test Two Second Timer.
extern void two_sec_clear(void);			   // Clear Two Second Timer
extern void five_sec_start(void);			   // Start or re-start 5 Second Timer.
extern unsigned char five_sec_test(void);	   // Test five Second Timer.
extern void five_sec_clear(void);			   // Clear five Second Timer
extern void two_min_start(void);			   // Start or re-start 2 Minute Timer.
extern unsigned char two_min_test(void);	   // Test Two Minute Timer.
extern void two_min_clear(void);			   // Clear Two Minute Timer.
extern void Timout_start(void);					// Start or re-start Timeout Timer.
extern void Timeout_clear(void);				// Test Timeout Timer.
extern unsigned char Timeout_test(void);		// Clear Timeout Timer.
extern unsigned char Timeout_active(void);
extern void five_min_start(void);			   // Start or re-start 2 Minute Timer.
extern unsigned char five_min_test(void);	   // Test Two Minute Timer.
extern void five_min_clear(void);			   // Clear Two Minute Timer.
extern void sleep_code(void);				   // Force code into low-power Sleep.
extern char *Battery_Level(void);			   // Use ADC to measure Battery.
extern char *Battery_Test(void);  			   // Use ADC to measure Battery.
extern void shft_str_left(char *, unsigned char);
extern char *get_numstr(unsigned char);
extern void Backspace_Char(char *, unsigned char);
extern unsigned long str_chg_to_long(char *);
extern void str_chg_long2(char *, unsigned char , float );
extern void str_chg_to_long2(void);
extern void New_Prog_Screen(void);
extern void Delete_Prog_Screen(void);
extern void str_chg_char(char *, unsigned char, unsigned char, unsigned char);
extern void str_chg_long(char *, unsigned char, float);
extern void remain_screen(void);
extern void update_time(void);
extern void itoa2(unsigned char);
extern void asrt_col0(void);
extern unsigned char tst_power(void);
extern unsigned char tst_laser(void);
extern void asrt_col1(void);
extern unsigned char tst_cancel(void);
extern void str_chg_int(char *, unsigned char, unsigned int, unsigned char);
extern void str_chg_ulong(char *temp, unsigned char length, unsigned long var1, unsigned char type_flag);
extern char *cstrncpy2(char *, const char *, size_t );
extern char tst_bat(void);
extern void update_sweep(void);
extern void display_sweep(void);
extern unsigned long calc_sweeptime( float frequency1);
extern void setup_sweep(unsigned long laser2_time);
extern void sweep_disp(void);
extern void very_accurate_delay(unsigned char delay1);
extern void beep_400hz(uint time_count);
extern void beep_600hz(uint time_count);
extern void beep_800hz(uint time_count);
extern void beep_1Khz(uint time_count);
extern void beep_1K2hz(uint time_count);
extern void beep_1K4hz(uint time_count);
extern void beep_1K6hz(uint time_count);
extern void beep_GNote(uint time_count);
extern void beep_BNote(uint time_count);
extern void beep_DNote(uint time_count);
extern void beep_tick(void);
extern void beep_ArpUp(void);
extern void beep_ArpDn(void);
extern void beep_3Bp(void);
extern void beep_3low(void);
extern void force_beep(uint time_count);
//extern struct super_macro *read_macros1(unsigned int entry_num);
//extern struct super_macro *read_macros2(unsigned int entry_num);
extern void cleanup_macros(void);
extern void display_macro(void);
extern void update_macro(void);
//extern void write_macro1(unsigned int entry_num, struct user_macro data1);
extern void write_macro(unsigned int entry_num);
extern uchar SPI_RW( uchar output );
extern void write_lasers(ulong laser1, ulong laser2, ulong laser3, ulong laser4);
extern void spi_long(ulong value1);
extern void spi_reset(void);
extern void lasers_on(void);
extern void lasers_off(void);
extern void ldlsrs_dis(void);
extern void ldlsrs_ena(void);
extern void spi_init(void);
extern uchar Mem_Status(void);
extern void Mem_Read( int num_bytes, long address, uchar *ptr );
extern void Mem_ReadS( int num_bytes, long address, void *ptr );
extern uchar Mem_Write( int num_bytes, long address, uchar *ptr );
extern void init_devices(void);
extern unsigned char init_lcd2(void);
extern void timer0_init(void);
extern void port_init(void);
extern void watchdog_init(void);
extern void write_char(unsigned char var1);
extern void asrt_col6(void);
extern void power_up( void );
extern void power_dn( void );
extern void power_up1( void );
extern void power_up2( void );
extern void factory_screen(void);
extern void boot_screen(void);
extern void main_screen(void);
extern void Delay(void);
extern void smmain_screen(void);
extern void LowBat_Screen(void);
extern void PwrDwn_Screen(void);
extern void proc_buffer(void);
extern unsigned char write_lcd(char *s);
extern void init_usart0(unsigned long baud);
extern void init_btooth(void);
extern void USART_Xmit(char data);
extern unsigned int USART_Recv(unsigned int loopcnt);
extern void xmit_bt(char *ptr);
extern unsigned char recv_bt(char *ptr, char type);
extern void add_cr(char *input);
extern void AssertBT_rst(void);
extern void Enable_BT(void);
extern void init_sound(void);
extern void powerdn_sound(void);
extern void stream_data(unsigned char data1);
extern void send_high(int time_count);
extern void send_low(int time_count);
extern void enable_tx(void);
extern void disable_tx(void);
extern void long_delay(unsigned char delay1);
extern void str_chg_long3(char *temp, unsigned char length, unsigned long var1);
extern void SerialNumScrn(void);
extern void MonitorScrn(void);
extern void TimeScrn(void);
extern void PBFEntryScrn(void);
extern void PBFErrorScrn(int code);
extern void WDR( void );
extern void CLI( void );
extern void SEI( void );
extern char* itoa(char* str, int num, int base);
extern char* ltoa(char* str, long num, int base);
extern char* ultoa(char* str, unsigned long num, int base);
extern char *ftoa(float f, int *status);
extern void reverse(char str[], int length);
extern void LCDmonitor( char* parm1);
extern void Save_Timer(char time_str[]);
extern char *Get_Timer( void );
extern void Init_Timer( void );
extern void monPrint(char Stat_Cd[], char str[]);
extern void Clr_Mode( void );
extern void Over_Ride( void );
extern void printf2(char str[]);
extern void Delay( void );
extern flash_err_t EEPROM_WRITE(uint32_t src_address, uint32_t dest_address, uint32_t num_bytes);
extern void EEPROM_READ(uchar *src_address, uchar *dest_address, uint32_t num_bytes);
extern void speaker_on( void );
extern void speaker_off( void );
extern void Soundsmonitor( char* parm1);
extern void Protocolmonitor( char* parm1);
extern void Macromonitor( char* parm1);
extern void write_plmLasers(struct plmLaser_entry laser1, struct plmLaser_entry laser2, struct plmLaser_entry laser3, struct plmLaser_entry laser4);
extern HAL_StatusTypeDef write_HFLasers(struct plmLaser_entry laser1, struct plmLaser_entry laser2, struct plmLaser_entry laser3, struct plmLaser_entry laser4);
extern void disp_HF_Parms( float disp_freq );
extern struct plmLaserE_entry calc_sweeptimeE( float frequency1, unsigned long passed_cnt, int LaserNumber);
extern struct plmLaser_entry calc_sweeptimeP( unsigned long frequency1, int LaserNumber);
extern struct plmLaser_entry calc_ratio( unsigned long cnt_value, int timer_number);
extern void Lasermonitor( char* parm1);
extern void hmcmonitor(char *parm1);
extern void KeyPressmonitor(char *parm1);
extern void Mntr_Loop_Clr( void );
extern void ModeMonitor( char* parm1);
extern void LaserOnmonitor( char* parm1);
extern void Keymonitor( char* parm1);
extern void int0_isr(void);
extern void timer0t_comp_isr(void);
extern unsigned char scan_keyboard_low();
extern void speaker_enable( void );
extern void speaker_disable( void );
extern void TL_Armed_screen(void);
extern void Laser_Armed_screen(void);
extern void Pulse_Armed_screen(void);
extern unsigned char tst_Start(void);
extern void getTime(int* hour, int* minute, int* second);
extern void getDate(int* month, int* day, int* year);
extern unsigned long calcPBF(void);
extern int decodePBFcode( char* parm1, int* leaseDays, int* Mode);
extern int NumDaysOrigin( int month, int day, int year );
extern int CalcLeaseDays( void );
extern void HardwareWakeup(void);
extern void my_sw_warmstart_beep(void);
extern void Miscmonitor( char* parm1);
extern void SetTimer( char* parm1);
extern void SetProgram( char* parm1);
extern void SetTimemonitor( char* parm1);
extern void SetDatemonitor( char* parm1);
extern void SetSNmonitor( char* parm1);
extern void SetModeMonitor( char* parm1);
extern void SetLDayMonitor( char* parm1);
extern void testPBFmonitor( char* parm1);
extern void setPBFmonitor( char* parm1);
extern void setUPgmmonitor( char* parm1);
extern void TestOriginmonitor( char* parm1);
extern 	void timeOutmonitor( char* parm1);
extern unsigned char reverseChar( unsigned char parm1);
extern void DateEntryScrn(void);
extern void TimeEntryScrn(void);
extern char* getTimeStr( void );
extern char* getDateStr( void );

#ifdef TST_PATCH
extern unsigned char MonitorParse(void);
#endif

#ifdef DEBUGGR
extern void debug1(unsigned char s);
#endif

#if LEASEOP
extern void KeyEntryScrn(void);
#endif
extern int init_laser(unsigned int, unsigned char);
extern void read_macro2(unsigned int entry_num);
extern void quick_laser(unsigned int);
extern struct super_macro *read_macro(unsigned int entry_num);
extern struct laser_entry *read_entry(unsigned int);
extern void write_entry(unsigned int entry_num, struct laser_entry data1);
extern struct sweep_entry *read_sweep(uint);
extern void write_sweep(unsigned int entry_num, struct sweep_entry data1);
extern void read_sweep2(uint);

#ifndef GRAPHICS
extern unsigned char lcd_comm(unsigned char ,unsigned char );
extern unsigned char lcd_status(void);
extern unsigned char lcd_read(void);
extern unsigned char init_lcd(void);
#endif

#if GRAPHICS
extern unsigned char lcd_comm2(unsigned char, unsigned char, unsigned char);
extern unsigned char lcd_status2(unsigned char);
extern unsigned char lcd_read2(unsigned char);
extern void  fill_temp2( unsigned char, unsigned char *);
extern unsigned char verify_char(unsigned char);
extern unsigned char verify_lcd(unsigned char *);
extern unsigned char wait_busy2(unsigned char);
extern unsigned char init_lcd2(void); 
extern unsigned char init_lcd2off(void);
#endif

//*****************************************************************************
//*
//* Misc Constants
//*
//*****************************************************************************
#define  SCRNRF             100         // Number millisec before next refresh.
#define  OPMIN_SIZE			10          // String Length for Display Purposes
#define  SWEEP_LIMIT        15          // Maximum number of Sweep Steps.
#define  MACRO_LMT			15			// Maximum number of Macro Steps that can be processed.
#define  UMACRO_LMT			10			// Maximum number of User Macro Steps.
#define  AUDIO_LMT			3			// Maximum number of Audio Phrases per Macro Entry.
#define	 TASKBUFF	  		10			// Number of queued tasks available.
#define	 LCD_INTEN			0x07		// Set Intensity at Full On.
#define	 ZEROS				0			// Fill with Zeros.
#define	 SPACES				1			// Fill with Spaces.
#define  INITIALIZE			0			// Initialize Vars Only
#define	 LASERSINIT			1			// Initialize and Run Lasers
#define	 FREQ_STR_LEN		10			// Frequency String Length...lser1_strng
#define  FREQ_OSC			16000000	// Frequency of base oscilator of crystal for micro.
#define  BTOOTH_BAUD		115200		// BlueTooth Base Baud Rate to use.
#define  BT_DELAY			50000		// Number of loops to wait for valid character.
#define  BT_OK				0			// Wait forever for OK.
#define  VCC_PWRDELAY		50			// Number msec to wait for VCC to stabilize after powerup.
#define  VDD_PWRDELAY		150			// Number msec to wait for VDD to stabilize after powerup.
#define  MEM_PWRDELAY		6			// Number msec to wait for VDD to stabilize after powerup for Mem.
#define  _FTOA_TOO_LARGE        1                       // FTOA TOO LARGE
#define  _FTOA_TOO_SMALL        2                       // FTOA TOO SMALL
#define  OK                     0
#define  FALSE                  0
#define  TRUE                   1
// Pseudo Blow Fish Constants
#define	 FACTOR1			0x243f6a88		// PBF Factor 1
#define	 FACTOR2			0xd1310ba6		// PBF Factor 2
#define	 FACTOR3			0x85a308d3

#if (KEY_FREQ == 120)
  #define  OSC_FREQUENCY		120000000	// FPGA Oscillator Frequency
#else
 #if (KEY_FREQ == 80)
  #define  OSC_FREQUENCY		80000000	// FPGA Oscillator Frequency
 #else
   #if (KEY_FREQ == 32)
     #define  OSC_FREQUENCY		32000000	// FPGA Oscillator Frequency
   #else
     #if (KEY_FREQ == 133)
       #define  OSC_FREQUENCY		133330000	// FPGA Oscillator Frequency
     #else
      #if (KEY_FREQ == 140)
       #define  OSC_FREQUENCY		140000000	// FPGA Oscillator Frequency
      #else
       #if (KEY_FREQ == 78)
        #define  OSC_FREQUENCY		78000000	// FPGA Oscillator Frequency
       #endif
      #endif
     #endif
   #endif
 #endif
#endif

//*****************************************************************************
//*
//* External Variable Definitions
//*
//*****************************************************************************
extern unsigned long 		lser1_time;		 // Laser 1 Load.
extern unsigned long 		lser2_time;		 // Laser 2 Load.
extern unsigned long 		lser3_time;		 // Laser 3 Load.
extern unsigned long 		lser4_time;		 // Laser 4 Load.
extern unsigned int	    	prog_num;		 // Program Number
extern unsigned long		opmin_cnt;		 	 // Operational Minute Count for Unit.
extern const unsigned long		eopmin_cnt;		 	 // Operational Minute Count for Unit.
extern const unsigned int 		eprog_num;		 // Program Number
#if MCP4725
extern unsigned int			save_tick;				 // Global var to track Ticks for I2C..sounds.c
#endif 
#if LEASEOP
extern const unsigned long        eopmin_lmt;		 	 // Number minutes to limit operation.
extern unsigned long        opmin_lmt;		 	 // Number minutes to limit operation.
#endif
#define	 LEASE_STR_LEN		13			// Frequency String Length...lser1_strng
extern char				    lease_str[LEASE_STR_LEN];
extern const unsigned long		eserial_number;			 // Serial Number of unit.
extern unsigned long		serial_number;			 // Serial Number of unit.

extern unsigned long		laser1_count;	 // Laser 1 Count.
extern unsigned long		laser2_count;	 // Laser 2 Count.
extern unsigned long		laser3_count;	 // Laser 3 Count.
extern unsigned long		laser4_count;	 // Laser 4 Count.
extern const unsigned long 		lser1e_time;	 // Laser 1 Load EEPROM.
extern const unsigned long 		lser2se_time;	 // Laser 2 Sweep Load.
extern const unsigned long 		lser2e_time;	 // Laser 2 Load EEPROM.
extern const unsigned long 		lser3e_time;	 // Laser 3 Load EEPROM.
extern const unsigned long 		lser4e_time;	 // Laser 4 Load EEPROM.
extern unsigned char 		stimer_low;		 // Timer 2 Count Saved.
extern unsigned char 		sprescale;		 // Timer 2 Prescale.
extern const unsigned char 		etimer_low;	 	 // Timer 2 Count Saved.
extern const unsigned char 		eprescale;	 	 // Timer 2 Prescale.
extern unsigned char 		stimer_low2;	 // Timer 2 Count Saved.
extern unsigned char 		sprescale2;		 // Timer 2 Prescale.
extern const unsigned char 		etimer_low2; 	 // Timer 2 Count Saved.
extern const unsigned char 		eprescale2;	 	 // Timer 2 Prescale.
extern const unsigned char		emode;			 // System Tasking Mode.
extern const unsigned char		esm;			 // Sub-Mode Variable
extern unsigned char		mode;			 // System Tasking Mode.
extern unsigned char		sm;			 	 // Sub-Mode Variable
extern unsigned int		tmr_min;		 // Timer Minutes
extern unsigned char		tmr_sec;		 // Timer Seconds
extern const unsigned int		etmr_min;		 // Timer Minutes
extern const unsigned char		etmr_sec;		 // Timer Seconds
extern unsigned char		p5_second;		 // 0.5 Second Timer
extern unsigned char		two_second;		 // Two Second Timer
extern unsigned char		five_second;	 // Five Second Timer
extern unsigned char		two_minute;		 // Two Minute Timer
extern unsigned int			five_minute;	 // Five Minute Timer
extern unsigned char		cnt_dwn_flg;	 // Flag to start Count Down.
extern unsigned char		tmr_update_flg;	 // Flag to over-ride update to timers.
extern unsigned char		lsr_update_flg;	 // Flag to over-ride update to Lasers.
extern unsigned char		alsr_update_flg; // Flag for updating all lasers.
extern unsigned char		key_down_flg;	 // This flag is set when a Keypress is detected.
extern unsigned char		fast_flg;		 // Set...Faster than 10Khz
extern unsigned char		save_char;		 // Current count of char pointer.
extern unsigned char		underline;				 // Underline Flag
extern unsigned char		laser_flg;				 // Flag set while Laser Event Active.
extern unsigned char		mntr_key_var;	 // Holds the state of an active Key Press from the Monitor
extern unsigned char      	StrmOn;					 // Used to enable/Disable Streaming Console Information
extern unsigned char		subClock_Fail;			 // SubClock Failure. Set if could not get RTC to work.
extern unsigned char		Booted;					 // Simple Flag to track Boot State.
extern float	 			laser1_disp;			 // Laser 1 Display Value.
extern float	 			laser2_disp;			 // Laser 2 Display Value.
extern float	 			laser3_disp;			 // Laser 3 Display Value.
extern float	 			laser4_disp;			 // Laser 4 Display Value.
extern char	   				prog_str[];
extern char	   				tmr_minstr[];
extern char	   				tmr_secstr[];
extern char	  	  			Bat_Lvl[];
extern char	   				lser1_strng[];
extern char	   				lser2_strng[];
extern char	   				lser3_strng[];
extern char	   				lser4_strng[];
extern unsigned char		entry_flg;				 // Used to indicate if a string will be displayed.
extern char					save_str[];
extern uchar				debug_buffr[];
extern char					dig_str[];	   			 // Permanent string for digit calculations.
extern struct sweep_var 	sweep1;					 // Sweep Tracking Structure
extern struct sweep_entry	sweep2;					 // Sweep Entry Structure
extern struct macro_var   	macro1;					 // Macro Tracking Structure
extern struct user_macro  	macro2;					 // Macro Entry Structure
extern unsigned char	    sweep_flg;				 // Sweep Flag for Int to use for comunication.
extern unsigned char		audio_flg;				 // Set when Speaker is on.
extern unsigned char		nobeep_flg;				 // Set when Speaker is on(Local Control).
extern unsigned char		macro_flg;				 // Indicates that we are processing a macro.
extern unsigned char	    cntrl_flg;				 // Control flag that controls prime freq generation through FPGA.
#if sixdigit
extern char	   				progwk_str[7];
extern unsigned long		progwk_num;				 // Program Number
#else
extern char	   				progwk_str[4];
extern unsigned int			progwk_num;				 // Program Number
#endif
extern uchar				min_chg, sec_chg;		 // Generic vars for Changing timers.
extern char					min_str[3];				 // Generic String for Minutes.
extern char					sec_str[3];				 // Generic String for Seconds.
extern unsigned int 		deb_count;			 // Counter for debugger.
extern unsigned char		buf[TASKBUFF];	 // Defines Tasking Buffer
extern unsigned char		buf_in;			 // Buffer Input Pointer
extern unsigned char		buf_out;		 // Buffer Output Pointer
extern unsigned char		buf_cnt;		 //	Number of outstanding tasks
extern unsigned char		led_coff;		 // Number of Clicks/Cycle LED Off.
extern unsigned char		led_cnt;		 // Used for LED Fade off function.
extern unsigned char		led_fcnt;		 // Used for LED Fade off function.
extern unsigned char 	    ticker, d_tick;			 // 1 Second Ticker Used to count Seconds.
extern unsigned long 		lser2S_time;		 	 // Laser 2 Sweep Load.
extern int					opMode;					// Mode for unit to operate
													// 0:Normal	1: Demo		2:Lease
extern int					leaseDays;				// Number of days to operate Lease
extern int					leaseDay;				// Lock Down Lease Day of Month
extern int					leaseMnth;				// Lock Down Lease Month
extern int					leaseYear;				// Lock Down Lease Year.
extern const int			eopMode; 		  		// Mode for unit to operate
								      	  	  	  	// 0:Normal	1: Demo		2:Lease
extern const int			eleaseDays; 		  	// Number of days to operate Lease
extern const int			eleaseDay; 	  			// Lock Down Lease Day of Month
extern const int			eleaseMnth;	  			// Lock Down Lease Month
extern const int			eleaseYear; 			// Lock Down Lease Year.

extern unsigned int			var_timer;				// Timer to be used for shutdown timeout.
extern unsigned int			timeout_Value;			// Timeout Value used to be saved and restored.
extern const unsigned int	etimeout_Value;			// Timeout Value used to be saved and restored.

//EEPROM Variable Definitions
//extern const struct laseru_entry laserStart_data[];
extern const struct laseru_entry  laser0_data;
extern const struct sweep_entry 	sweep1_data;
extern const struct user_macro 	macro1_data;


//#define TICKER_LIMIT	29				// Limit to count for PLM Design at 500msec
#define TICKER_LIMIT	20				// 6/24/15 Modified to 10 to allow accurate 500ms
//*****************************************************************************
//*
//* Battery Constants
//*
//*****************************************************************************
//** MarkIII Battery Constants
//  #define	 BAT_HIGH			770			// Battery High >7.8V.
//  #define	 BAT_MEDIUM			685			// Battery Medium >7.0V.
//  #define	 BAT_MEDLOW			620			// Battery Medium Low >6.1V.
//  #define	 BAT_LOW			530			// Battery Low >5.4V.
//** MarkIII Battery Constants
  #define	 BAT_HIGH			152		// Battery High >7.8V.
  #define	 BAT_MEDIUM			148			// Battery Medium >7.0V.
  #define	 BAT_MEDLOW			136			// Battery Medium Low >6.1V.
  #define	 BAT_LOW			132			// Battery Low >5.4V.

//*****************************************************************************
//*
//* Task Definitions
//*
//*****************************************************************************
#define  Bcklght_ON			1			// Force Backlight On, Defeat Fade Off
#define	 Bcklght_OFF		2			// Force Backlight Off, Defeat Fade Off
#define	 Bcklght_Fade		3			// Fade Backlight off...1 second.
#define	 MAXENTRY			4			// After Last Entry in Table.

//*****************************************************************************
//*
//* Mark IV Definitions
//*
//*****************************************************************************
#define  Timer0OUT			1			// Control Bit for Timer 0.
#define  Timer1OUT			2			// Control Bit for Timer 1.
#define  Timer2OUT			4			// Control Bit for Timer 2.
#define  Timer3OUT			8			// Control Bit for Timer 3.
#define  AllTmrsOut			0			// Set All Timers as Out.
#define  AllTmrsPll			15			// Set All Timers as pll.
#define	 AllTmrsDbl			7			// Set all Dblr pins for Double Speed.
#define  Timer0Dbl			1			// Control Bit for Timer 0 Dblr.
#define  Timer1Dbl			2			// Control Bit for Timer 1 Dblr.
#define  Timer2Dbl			4			// Control Bit for Timer 2 Dblr.
#define  TimerMode			1			// Enable load to Output Timers.
#define  pll0Mode			2			// Enable load to pll0.
#define  pll1Mode			4			// Enable load to pll1.
#define  pll2Mode			8			// Enable load to pll2.
#define  pll3Mode			16			// Enable load to pll3.
#define  DEF_CPC			3			// Default Charge Pump Current Value...Default 3uA
#define	 DEF_PSD			0			// Default VCO Post-Scale Divider..Default 0
#define  DEF_LFC			1			// Default Loop Filter Capacitor Value..Default 10pf
#define	 DEF_LFR			10			// Default Loop Filter Resistor Value..Default 10K
#define  PLL0				0			// Definition for PLL0
#define  PLL1				1			// Definition for PLL1
#define  PLL2				2			// Definition for PLL2
#define  PLL3				3			// Definition for PLL3
#define  BYPASSV			-1			// Bypass Postcounter by using this value.
#define  PLL0M				25			// Mutiplier value for PLL0 Initialize 500MHZ
#define	 PLL0N				6			// Divisor value for PLL0 Initialize 500MHZ
#define	 NRML_PLL			0			// Flag for Calculation on PLLs
#define	 NO_PLL				1			// Flag for no PLL Calculation
#define	 N_CNTR				0			// Pointer to Pre-Scale Counter Parameters.
#define	 M_CNTR				1			// Pointer to Feedback Counter Parameters.
#define	 CP_LF				2			// Pointer to Capacitor/ Loop Filter Parameters.
#define	 VCO				3			// Pointer to VCO Parameters
#define	 C0CNTR				4			// Pointer to Counter 0 Parameters.
#define	 C1CNTR				5			// Pointer to Counter 1 Parameters.
#define	 C2CNTR				6			// Pointer to Counter 2 Parameters.
#define	 C3CNTR				7			// Pointer to Counter 3 Parameters.
#define	 C4CNTR				8			// Pointer to Counter 4 Parameters.
#define	 C5CNTR				9			// Pointer to Counter 5 Parameters.
#define	 C6CNTR				10			// Pointer to Counter 6 Parameters.
#define	 C7CNTR				11			// Pointer to Counter 7 Parameters.
#define	 C8CNTR				12			// Pointer to Counter 8 Parameters.
#define	 C9CNTR				13			// Pointer to Counter 9 Parameters.
#define	 H_CNT				0			// High Count for C0-C9, M and N.
#define	 L_CNT				1			// Low Count for C0-C9, M and N.
#define	 MODE				5			// Mode for C0-C9, M and N.
#define	 BYPASS				4			// Bypass for C0-C9, M and N.
#define	 CHRGPU				5			// Charge Pump Unused for CP/LF.
#define	 CHRGPC				0			// Charge Pump Current for CP/LF.
#define	 LPFLTU				4			// Loop Filter Unused for CP/LF.
#define	 LPFLTR				1			// Loop Filter Resistor for CP/LF.
#define	 LPFLTC				5			// Loop Filter Capacitance for CP/LF.
#define	 VCOPST				0			// VCO Post Scale for VCO.
#define	 MBYPSS				4			// Bypass for M/N.
#define	 NMNL				7			// Nominal Count for M/N.
#define	 READPLL			1			// Set for Read Operation
#define	 WRITEPLL			1			// Set for Write Operation
#define	 RECONFIGURE		2			// Force Reconfigure
#define	 REPEAT_CNT			100			// Number of times to repeat a try at load to PLL.
#define	 TIMEOUT_CNT		1000		// Number of times to repeat test for Busy on Reconfig.
#define  LOW_OUTFREQ		100000000	// Output Frequency low limit for PLLs.
#define	 HIGH_OUTFREQ		1300000000	// Output Frequency High Limit for PLLs.
#define  MAXOUT_FREQ		1000000000  // Maximum Frequency that will be allowed to be generated.
#define	 LOGIC_FREQ			500000000	// Logic Limit for Operation of FPGA
//*****************************************************************************
//*
//* Mode Definitions
//*
//*****************************************************************************
#define  Factory			0			// **** Factory Boot Mode(DEFAULT START MODE)
#define  Factory_Screen		1			// Factory Boot: Factory Screen
#define	 Boot_Screen		2			// **** Boot Screen
#define  Locked			    3			// **** Locked
#define  Locked_1			4			// Locked: First Key Matched for UnLock.
#define  Locked_2			5			// Locked: Second Key Matched for Unlock.
#define  Main				6		    // **** Main Menu
#define  Timed_Test			7			// Main Menu: Timed Test for Timed Laser Mode
#define  Soft_PD			8			// **** Soft Power Down
#define  Test1				9			// **** Test1/ Soft_PD
#define  Laser_On			10			// **** Laser On Momentary
#define  Wait_Release		11			// Laser On Momentary: Wait For Key Release
#define  Timed_Laser		12			// **** Timed Laser Mode
#define  Pause_Laser		13			// Timed Laser Mode: Wait for Key Release
#define  Pause_Laser2		14			// Timed Laser Mode: Wait for Laser to Restart
#define  Pause_Laser3		15			// Timed Laser Mode: Wait for Key Release.
#define  Five_Min_Mode		16			// **** Five Minute Laser On Mode
#define  Pause1				17			// Five Minute Laser On Mode: Pause Laser and Wait Key Release
#define  Pause				18			// Five Minute Laser On Mode: Wait for Power Key
#define  Pause2				19			// Five Minute Laser On Mode: Restart Laser and Wait Key Release
#define  Program			20			// **** Programming Mode
#define  Incr_Prog			21			// Programming Mode: Increment Program Count and Recalculate
#define  Decr_Prog			22			// Programming Mode: Decreement Program Count and Recalculate
#define  Build_Prog			23			// Programming Mode: Build Program Buffer.
#define  Activate_Prog		24			// Programming Mode: Activate New Program ID.
#define  Time_Value			25			// **** Time Program Mode
#define  Remove_1Key		26			// Time Program Mode: Remove 1 Key from Buffer
#define  Incr_Second		27			// Time Program Mode: Increment Second Buffer
#define  Decr_Second		28			// Time Program Mode: Decrement Second Buffer
#define  Incr_Minute		29			// Time Program Mode: Increment Minute Buffer
#define  Buffer_Build		30			// Time Program Mode: Build Time Buffer
#define  Decr_Minute		31			// Time Program Mode: Decrement Minute Buffer
#define  Save_Settings		32			// Time Program Mode: Save Time Settings
#define  Laser_Value		33			// **** Laser Root Program Menu
#define  Laser1_Value		34			// **** Laser 1 Program Menu
#define  LSR1_SM3			35			// Laser 1 Program Menu: Set SM=3 and Goto Laser3_Value
#define  LSR1_SM2			36			// Laser 1 Program Menu: Set SM=2 and Goto Laser2_Value
#define  LSR1_BffrBuild		37			// Laser 1 Program Menu: Buffer Build
#define  LSR1_RemvKey		38			// Laser 1 Program Menu: Remove One Key From Buffer
#define  LSR1_BlnkLaser		39			// Laser 1 Program Menu: Blank Laser Buffer
#define  LSR1_SaveLsr		40			// Laser 1 Program Menu: Save Laser Setting
#define  Laser2_Value		41			// **** Laser 2 Program Menu
#define  LSR2_SM4			42			// Laser 2 Program Menu: Set SM=4 and Goto Laser4_Value
#define  LSR2_SM1			43			// Laser 2 Program Menu: Set SM=1 and Goto Laser1_Value
#define  LSR2_BffrBuild		44			// Laser 2 Program Menu: Buffer Build
#define  LSR2_RemvKey		45			// Laser 2 Program Menu: Remove One Key From Buffer
#define  LSR2_BlnkLaser		46			// Laser 2 Program Menu: Blank Laser Buffer
#define  LSR2_SaveLsr		47			// Laser 2 Program Menu: Save Laser Setting
#define  Laser3_Value		48			// **** Laser 3 Program Menu
#define  LSR3_SM1			49			// Laser 3 Program Menu: Set SM=1 and Goto Laser1_Value
#define  LSR3_SM4			50			// Laser 3 Program Menu: Set SM=4 and Goto Laser4_Value
#define  LSR3_BffrBuild		51			// Laser 3 Program Menu: Buffer Build
#define  LSR3_RemvKey		52			// Laser 3 Program Menu: Remove One Key From Buffer
#define  LSR3_BlnkLaser		53			// Laser 3 Program Menu: Blank Laser Buffer
#define  LSR3_SaveLsr		54			// Laser 3 Program Menu: Save Laser Setting
#define  Laser4_Value		55			// **** Laser 4 Program Menu
#define  LSR4_SM2			56			// Laser 4 Program Menu: Set SM=2 and Goto Laser2_Value
#define  LSR4_SM3			57			// Laser 4 Program Menu: Set SM=3 and Goto Laser3_Value
#define  LSR4_BffrBuild		58			// Laser 4 Program Menu: Buffer Build
#define  LSR4_RemvKey		59			// Laser 4 Program Menu: Remove One Key From Buffer
#define  LSR4_BlnkLaser		60			// Laser 4 Program Menu: Blank Laser Buffer
#define  LSR4_SaveLsr		61			// Laser 4 Program Menu: Save Laser Setting
#define  New_Prog			62			// **** New Program Menu
#define  New_Prog_SM1		63			// New Program Menu: Set SM=1 and Goto Laser_Value
#define  Delete_Prog		64			// **** Delete Program Menu
#define  Blank_Settings		65			// Delete Program Menu: Blank Settings and goto Main
#define  LOW_BAT		    66			// Battery Low...Die Now!!!!
#define  Low_PD		        67			// Battery Low Power Down...No Save Vars...SLEEP!!!!
#define  FPGA_BAT		    68			// FPGA Battery Low...Shutdown Now!!!!
#define	 Special4			69			// Special Sequence From Main to start limited Monitor Mode....Step 1
#define	 Special4a			70			// Special Sequence From Main to start limited Monitor Mode....Step 2
#define	 Special9			71			// Special Sequence From Main to start limited Monitor Mode....Step 3
#define	 Special3			72			// Special Sequence From Main to start limited Monitor Mode....Step 4
#define	 ProgramMode		73			// Special Sequence From PowerOff to Load Serial Flash....FINAL STEP
#define	 DB_Screen			74			// Database Screen Showing DB Versions.
#define	 SndScreen			75			// Sound Configuration Screen.
#define  KeyScreen			76			// Key Entry Screen.
#define  SerialNumScreen	77			// Serial Number Entry Screen.
#define  Timed_Laser_Armed	78			// Timed Laser Armed Screen.
#define  Timed_Laser_Armed2	79			// Timed Laser Armed Screen Part2.
#define  Laser_On_Armed		80			// Laser On Armed Screen.
#define  Laser_On_Armed2	81			// Laser On Armed Screen Part2.
#define  Five_Min_Armed		82			// Five Minute Armed Screen.
#define  Five_Min_Armed2	83			// Five Minute Armed Screen Part2.
#define	 Soft_PD_CONTINUE	84			// Soft PD Continue after Wait.
#define  Locked_CONTINUE	85			// Need this for Locked wakeup
#define	 SpecialSelect		86			// Special Sequence From Main to start limited Monitor Mode....Step 5
#define	 MonitorMode		87			// Special Sequence From Main to start limited Monitor Mode....FINAL STEP
#define	 ShowTimeMode		88			// Show Time and Date mode.
#define	 PBFEntryScreen		89			// PBF Entry mode.
#define	 PBFErrorScreen		90			// PBF Error mode.
#define	 DateEntryScreen	91			// Date Entry Screen.
#define	 TimeEntryScreen	92			// Time Entry Screen
#define	 END_SETTING		93			// End of Entries
//*****************************************************************************
//*
//* LCD Control Definitions
//*
//*****************************************************************************
#define	 RSCOMMAND			0x00		// Used by RS to index Command Registers.
#define	 RSDATA				0x01		// Used by RS to index Data Registers.
#ifdef PCB_1_00
#define	 LINE1				0x00		// Define Line 1 Number.
#define	 LINE2				0x01		// Define Line 2 Number.
#define	 LINE3				0x02		// Define Line 3 Number.
#define	 LINE4				0x03		// Define Line 4 Number.
#else
#define	 LINE1				0x03		// Define Line 1 Number.
#define	 LINE2				0x02		// Define Line 2 Number.
#define	 LINE3				0x01		// Define Line 3 Number.
#define	 LINE4				0x00		// Define Line 4 Number.
#endif
#define	 NOCURSOR			0x00		// Cursor set as NO Cursor.
#define	 UNDERLINE			0x01		// Cursor set as Underline.
#define	 BLINK				0x02		// Cursor set as Blink.
#define	 GR1				0x00		// Select as Graphics Device 0.
#define	 GR2				0x01		// Select as Graphics Device 1.
//*****************************************************************************
//*
//* LCD Command Definitions
//*
//*****************************************************************************
#define  Clear_Display      0x01        // Clear LCD Display
#define	 Cursor_Home		0x02		// Set Cursor to Home
#define	 Entry_Mode			0x04		// Entry Mode Set
#define	 Display_On			0x08		// Display On/Off
#define	 Cursor_Display		0x10		// Cursor Select and Display
#define	 Function_Set		0x20		// Function Set
#define	 Set_CG_RAM			0x40		// Set CG RAM Address
#define	 Set_DD_RAM			0x80		// Set DD RAM Address


#define  Display_On2		0xAF		// Set Graphics LCD Display ON.
#define	 Display_Off2		0xAE		// Set Graphics LCD Display OFF.
#define	 Display_Start_LN	0xC0		// Set Display Start Line.
#define	 Page_Address		0xB8		// Set Display Page Address.
#define	 Set_Col_Addr		0x00		// Set Display Column Address
#define  Select_ADC			0xA0		// Select ADC Mode
#define  Select_ADC_INV		0xA1		// Select ADC Mode INVERT
#define	 Static_DRV_ON		0xA5		// Static Drive...Power Saving
#define	 Static_DRV_OFF		0xA4		// Normal Driving
#define	 Duty_1_32			0xA9		// Select Duty 1/32
#define	 Duty_1_16			0xA8		// Select Duty 1/16
#define	 Rd_Mdfy_Wrt		0xE0		// Select Read Modify Write Mode.
#define	 End_Rd_Mdfy_Wrt	0xEE		// End Read Modify Write Mode.
#define	 Reset_Sft			0xE2		// Soft Reset of Graphics Chip.  
//*****************************************************************************
//*
//* Key Name Definitions
//*
//*****************************************************************************
// *****OLD STYLE
//#define	 LIGHT				01		    // Backlight Key
//#define	 TIME				02		    // Activate Time Key
//#define	 POWER				03		    // Power Key
//#define	 LASER				04		    // Activate Laser Key
//#define	 CANCEL				05		    // Cancel Key
//#define	 DELETE				06		    // Delete Key
//#define	 SELECT				20		    // Four Key

// *****New Style Manufactured Laser Pulser
#define	 DELETE				03		    // Delete Key
#define	 CANCEL				01		    // Cancel Key
#define	 LASER				20		    // Activate Laser Key
#define	 SELECT				02		    // Select Key
#define	 LIGHT				06		    // Backlight Key
#define	 POWER				04		    // Power Key
#define	 TIME				05		    // Activate Time Key

#define	 ONE				07		    // One Key
#define	 TWO				8		    // Two Key
#define	 THREE				9		    // Three Key
#define	 FOUR				10		    // Four Key
#define	 FIVE				11		    // Backlight Key
#define	 SIX				12		    // Activate Time Key
#define	 SEVEN				13		    // Power Key
#define	 EIGHT				14		    // Activate Laser Key
#define	 NINE				15		    // Cancel Key
#define	 PERIOD				16		    // Delete Key
#define	 ZERO				17		    // One Key
#define	 BACK				18		    // Two Key
#define	 LEFT				19		    // Three Key
#define	 RIGHT				21		    // Backlight Key
#define	 UP					22		    // Activate Time Key
#define	 DOWN				23		    // Power Key
#define	 OFF				24			// Off Key
#define	 START				25			// Start Thumb Switch.
#define  SPACE_VAL			1000		// Special code for no processing.
#define	 PROG_CNT			CUSTOM_END	// Total Number of predefined Programs.

#define	 PROG_NUMBR			USERSUPR_REND	// Total Number of active Programs.

#define	 SWEEP_NUM			SWEEP_STRT	// Sweep Protocol Number.

#define  RESERVE_STRING		"    Reserved    "	// Reserved Display String.
#define  ILLEGAL_STRING		"     Illegal    "	// Illegal Display String.
#define	 BLANK_STRING		"                "  // Blank String.
#define	 WAIT_STRING		"     -Wait-     "  // Blank String.
#define	 BLANK_SHRTSTRNG	"         "  // Blank String.
//#define	 MACRO_STRING		"   USER MACRO   "  // User Macro String.
#define	 MACRO_STRING		"   User Group   "  // User Macro String.

//*****************************************************************************
//*
//* BlueTooth Command Strings
//*
//*****************************************************************************
#define	 AT_STRING			"AT"  	 	// BlueTooth Generic BlueTooth Preamble "AT"
#define	 CR_STRING			0x0d  	 	// Generic Carriage Return.
#define	 I_STRING			"I"  	 	// BlueTooth CMD: I - Information, Returns Product Information
#define	 ESC_STRING			"+++"  	 	// BlueTooth Escape Sequence...Should be sent before any commands are attempted.
#define	 BTINQ_STRING		"+BTINQ=5" 	// BlueTooth CMD: +BTINQ - Query for BlueTooth Transceivers in Range.
#define	 BTSDP_STRING		"+BTSDP=" 	// BlueTooth CMD: +BTSDP - Query for Active BlueTooth Services on Transceiver.
#define	 BTCLT_STRING		"+BTCLT=" 	// BlueTooth CMD: +BTCLT - Connect as Client to BT Transceiver.
#define  BTLNM_STRING		"+BTLNM=\"LAZRPULSR\""	// BlueTooth CMD: +BTLNM - Set Name of Unit
#define  BTRXT_STRING		"+BTRXT=1," // BlueTooth RF Test Command
#define  BTSET_STRING		"+BTSET=2,96" // BlueTooth Set RFTUN Command.
//*****************************************************************************
//*
//* M25P64 Command Definitions
//*
//*****************************************************************************
#define  M25P_WREN		       0x06               // Write Enable.
#define	 M25P_WRDI			   0x04				  // Write Disable.
#define	 M25P_RDID			   0x9F				  // Read Identification.
#define	 M25P_RDSR			   0x05				  // Read Status Register.
#define	 M25P_WRSR			   0x01				  // Write Status Register.
#define	 M25P_READ			   0x03				  // Read Data Bytes.
#define	 M25P_FAST_READ		   0x0b				  // Read Data Bytes at a higher speed.
#define	 M25P_PP			   0x02				  // Page Program.
#define	 M25P_SE			   0xd8				  // Sector Erase.
#define	 M25P_BE			   0xc7				  // Bulk Erase.
#define	 M25P_RES			   0xab				  // Read Electronic Signature.

//*****************************************************************************
//*
//* MCP4725 Command Definitions
//*
//*****************************************************************************
#define  MCP_GENERAL		   0x00               // General Call.
#define  MCP_RESET			   0x06               // General Call Reset.
#define  MCP_WAKEUP			   0x09               // General Call Wakeup.
#define  MCP_HIGHSPEED		   0x08               // High-Speed Mode.
#define  MCP_DEVADDR		   0xC0               // Device Address.
#define  MCP_FASTMDCMD		   0x00               // Fast Mode Command.
#define  MCP_WRITEDAC		   0x40				  // Write DAC Input Register
#define	 MCP_WRTDACEEP		   0x60				  // Write DAC Input and EEPROM
#define	 MCP_DEVREAD		   0xC1				  // Read Command
#define  MCP_TIMEOUT		   100				  // Timeout Loop value to wait for ack.
#define  DEFAULT_MCPTICK	   1				  // Default Tick Delay per operation.
		 					   					  // 1 Tick = 10.8 usec.
//*****************************************************************************
//*
//* Key Enum Definitions
//*
//*****************************************************************************
enum SCI_TX_STATUS
{
  TX_COMPLETE = 0x00,
  TX_ERROR = 0x02,
  TX_BUSY = 0x01,
  TX_NOINIT = 0x03,
  TX_STOP = 0x04
};

enum SCI_RX_STATUS
{
  RX_COMPLETE = 0x00,			// Msg has been transferred to str and is ready to return
  RX_BUSY = 0x01,				// Assigned before a R_SCI5_Serial_Receive transaction
  RX_ERROR = 0x02,
  RX_NOINIT = 0x03,				// SCI5 Receive hardware has not been initialized
  RX_STOP = 0x04,
  RX_RECEIVED = 0x05,			// Assigned when a msg(1 Char) has been received by serial port
  RX_MSG_READY = 0x06			// Assigned when logic determines CR received in msg buffer
};
  
enum TASK_CMD
{
  TX_STATUS = 0x00,
  TX_SEND = 0x01,
  TX_SEND_WAIT = 0x02,
  TX_ERRORCD = 0x03
};

enum RECEIVE_CMD
{
  RX_STATUS = 0x00,
  RX_STRING = 0x01,
  RX_STRING_WAIT = 0x02,
  RX_CHAR = 0x03,
  RX_CHAR_WAIT = 0x04,
  RX_ERRORCD = 0x05,
  RX_STRING2 = 0x06
};

enum DEBUG_MSGS
{
	D_PRINTF2 = 100,
	D_SCI5_PRINT = 101,
	D_SCI5_TXEND = 102,
	D_SCI5_TXINT = 103,
	D_SCI5_SEND = 104
};

enum MULTIPLIER_VALUES
{
	MULTIPLY_1X = 0,	// MULTIPLY OFF
	MULTIPLY_2X = 1,	// LL -  2X
	MULTIPLY_2_5 = 2,	// HH - 2.5X
	MULTIPLY_3X = 3,	// ML - 3X
	MULTIPLY_3_33X = 4,	// MH - 3.33X
	MULTIPLY_4X = 5,	// HL - 4X
	MULTIPLY_5X = 6		// LH - 5X
};

enum MTU3_TIMERS
{
	MTU0_LaserDiode0 = 0,	// MULTIPLY OFF
	MTU1_LaserDiode1 = 1,	// LL -  2X
	MTU3_PLLInput2	 = 2,	// HH - 2.5X
	MTU4_LaserDiode2b = 3,	// ML - 3X
	MTU6_PLLInput3 = 4,	// MH - 3.33X
	MTU7_LaserDiode3b = 5	// HL - 4X
};

enum LaserNumbers
{
	LaserDiode0 = 0,
	LaserDiode1 = 1,
	LaserDiode2 = 2,
	LaserDiode3 = 3
};

enum Laser_Modes
{
	NO_SETTING = 0,
	MODE_TCR = 1,
	MODE_TCR2 = 2,
	MODE_ERROR = 0x10
};

typedef enum
{
	NO_HFMODES = 0,
	PLLC_HFMODE = 1,
	PLLD_HFMODE = 2,
	BOTH_HFMODES = 3
} HF_Avail_Modes;

#define RX_BUFFERSIZE   500     // Size of receive buffer for RX Charachters.
//*****************************************************************************
//*
//* Key Structure Definitions
//*
//*****************************************************************************
union lasertim {
  unsigned int value;
  struct {
	unsigned time: 15;
    unsigned res_flg: 1;
  } data1;
};

struct laseru_entry {
  float laser1_time;
  float laser2_time;
  float laser3_time;
  float laser4_time;
  char string1[10];
  uchar entry_flg;
};

struct laser_entry {
  float laser1_time;
  float laser2_time;
  float laser3_time;
  float laser4_time;
  char string1[17];
  uchar entry_flg;
};

struct timer_val {
  unsigned char	   minutes;					 // Generic Minutes Entry
  unsigned char	   seconds;					 // Generic Seconds Entry
};

struct macro_entry {
  struct timer_val delay;					 // Time to Delay before executing protocol.
  struct timer_val Time;					 // Length of time to run protocol.
  uint	   		   protocol;				 // Protocol number to execute.
  unsigned char	   num_audio;				 // Number of Audio Phrases to play.
  unsigned char	   phrase[AUDIO_LMT];		 // Array of Audio Phrase offsets.
}; // 10 Bytes Each.

struct macro_var {
  struct super_macro	*macro1;			 // Entry for all key information.
  unsigned int			macro_step;			 // Current Macro Step being executed.
  unsigned int			prog_save;			 // Save Current Program for after execution.
  unsigned int			protocol_save;		 // Used by remain_screen to display the correct protocol.
  unsigned char			save_min;			 // Save Current tmr_min.
  unsigned char			save_sec;			 // Save Current tmr_sec.
  unsigned char			save_flg;			 // Indicate first pass of code to save values.
  		   									 // 0: New execution save values
											 // 1: Current run of event. No save.
  unsigned char			macro_flg;			 // Flag to determine execution state.  		   									 // 0: sweep_lmt represents number ticks before modifying timer_value.
											 // 0: Normal Macro Execution.
											 // 1: Execute Delay.
  unsigned char			minute_flg;			 // Flag to determine execution state.  		   									 // 0: sweep_lmt represents number ticks before modifying timer_value.
											 // 0: Edit Minutes.
											 // 1: Edit Seconds.
};

struct super_macro {
  unsigned int	   num_entries;	             // Number of Entries to Process
  struct macro_entry	mac_entry[MACRO_LMT];	 // Array of Macro Entries to process.
  char string1[18];
};

struct user_macro {
  unsigned int	   num_entries;	             // Number of Entries to Process
  struct macro_entry	mac_entry[UMACRO_LMT];	 // Array of Macro Entries to process.
  char string1[18];
};

struct sweep_entry {
  unsigned char		tmr_min;				 // Timer Minutes
  unsigned char		tmr_sec;				 // Timer Seconds
  float sweep_low;							 // Sweep Lower Limit
  float sweep_high;							 // Sweep Upper Limit
  float laser_time[SWEEP_LIMIT];
};

struct sweep_var {
  struct sweep_entry	*sweep1;			 // Entry for all key information.
  unsigned long  t_freq1;					 // Target Frequency 1.
  unsigned long  t_freq2;					 // Target Frequency 2.
  unsigned long  t_freq3;					 // Target Frequency 3.

  unsigned long		sweep_tlmt;				 // Total Tick Limit per segment.
  unsigned int		sweep_cnt;				 // Current Sweep Count in 50msec ticks.
  unsigned int		sweep_lmt;				 // Next limit in 50msec ticks to count.
  unsigned char		sweep_flg;				 // Flag to determine meaning of sweep_lmt:
  		   									 // 0: sweep_lmt represents number ticks before modifying timer_value.
											 // 1: sweep_lmt represents value to modify timer_value.
  unsigned char		sweep_dir;				 // Direction to modify current Frequency.
  		   									 // + - 0
											 // - - 1
  unsigned char		sweep_state;			 // Current State of Sweep function.
  		   									 // 0-Initial Sweep	 1-Sweep Down   2-Final Sweep
  unsigned char		sweep_ptr;				 // Current State of sweep frequencies.
  		   									 // 0:Lower Limit   1-15:Freq1-15   16:Final Limit
  unsigned char		sweep_key;				 // Indicates Current Variable being loaded.
  		   									 // 0: Timer Minutes and Seconds
											 // 1: Lower Limit Sweep
											 // 2: Upper Limit
											 // 3-17: Target Freqs 1-15.
};

struct lsrcalc_entry {
  unsigned int		m_value;				 // Feedback Counter
  unsigned int		n_value;				 // Pre-Scale Counter
  unsigned int		post_value;				 // Post Counter Value.
  unsigned long     cnt_value;				 // Long Count Value.
};

struct plmLaser_entry {
	float 			laser_Freq;			 	// Desired Freq of Laser Diode.
	unsigned int 	Special1;				// Used to adjust for absolute fastest frequency.
	unsigned int 	prescaler;				// Prescaler Value
	unsigned long 	cnt_value;				// Long Count Value.
};

struct plmLaserE_entry {
  unsigned int		Special1;				 // Used to adjust for absolute fastest frequency.
  unsigned int		prescaler;				 // Prescaler Value
  unsigned long     cnt_value;				 // Long Count Value.
  bool				Multiplier;				 // If set, indicates that multiplier is active.
  unsigned int		Multipler_Value;		 // Will contain the enum for the correct multiplier.
};

union bt_status {
  unsigned int value;
  struct {
	unsigned reserved1: 5;
    unsigned overrun: 1;
	unsigned frameerr: 1;
	unsigned timeout: 1;
	unsigned char data;
  } data1;
};

struct MapData {
  unsigned short Custom_Start;
  unsigned short Custom_End;
  unsigned short Custom_REnd;
  unsigned short User_Start;
  unsigned short User_End;
  unsigned short User_REnd;
  unsigned short Sweep_Start;
  unsigned short Sweep_End;
  unsigned short Sweep_REnd;
  unsigned short CstmSupr_Start;
  unsigned short CstmSupr_End;
  unsigned short CstmSupr_REnd;
  unsigned short UserSupr_Start;
  unsigned short UserSupr_End;
  unsigned short UserSupr_REnd;
  unsigned short Custom2_Start;
  unsigned short Custom2_End;
  unsigned short Custom2_REnd;
  unsigned short CstmSupr2_Start;
  unsigned short CstmSupr2_End;
  unsigned short CstmSupr2_REnd;
  unsigned short Custom3_Start;
  unsigned short Custom3_End;
  unsigned short Custom3_REnd;
  unsigned short CstmSupr3_Start;
  unsigned short CstmSupr3_End;
  unsigned short CstmSupr3_REnd;
};
#define	 MapDataSize		54			// Size of Map Data Structure

typedef union {
  long	L;
  float	F;
}LF_t;

//*****************************************************************************
//*
//* Macro Definitions
//*
//*****************************************************************************
#define SetBit(x,y)	      (x|=(1<<y))
#define ClrBit(x,y)  	  (x&=~(1<<y))
#define ToggleBit(x,y)	  (x^=(1<<y))
#define FlipBit(x,y)	  (x^=(1<<y))  //Same as ToggleBit.
#define TestBit(x,y)	  (x&(1<<y))

