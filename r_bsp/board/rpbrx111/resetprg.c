/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer 
*
* Copyright (C) 2014 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : resetprg.c
* Device(s)    : RX111
* Description  : Defines post-reset routines that are used to configure the MCU prior to the main program starting. 
*                This is were the program counter starts on power-up or reset.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 08.11.2012 1.00     First Release
*         : 19.11.2012 1.10     Updated code to use 'BSP_' and 'BSP_CFG_' prefix for macros.
*         : 28.01.2013 1.20     Added code to properly set the MOFCR register.
*         : 08.05.2013 1.30     Added option to use r_cgc_rx module for clock management.
*         : 24.06.2013 1.40     Removed auto-enabling of NMI pin interrupt handling. Fixed a couple of typos. Fixed
*                               a warning that was being produced by '#pragma inline_asm' directive. Added a call
*                               to bsp_interrupt_open() to init callbacks. Added ability to use 1 or both stacks.
*         : 25.11.2013 1.50     Code now uses clock stabilization flags for testing instead of SW delays. The LOCO
*                               is now turned off when it is not chosen to be used. Replaced stdbool.h and stdint.h 
*                               includes with include for platform.h.
*         : 31.03.2014 1.60     Added the ability for the user to define two 'warm start' callback functions which when
*                               defined result in a callback from PowerON_Reset_PC() before and/or after initialization
*                               of the C runtime environment. Uses the new R_BSP_SoftwareDelay() to do software delays
*                               instead of a loop count.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Defines MCU configuration functions used in this file */
#include    <_h_c_lib.h>

/* This macro is here so that the stack will be declared here. This is used to prevent multiplication of stack size. */
#define     BSP_DECLARE_STACK
/* Define the target platform */
#include    "platform.h"

/* BCH - 01/16/2013 */
/* 0602: Defect for macro names with '_[A-Z]' is also being suppressed since these are default names from toolchain.
   3447: External linkage is not needed for these toolchain supplied library functions. */
/* PRQA S 0602, 3447 ++ */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* If the user chooses only 1 stack then the 'U' bit will not be set and the CPU will always use the interrupt stack. */
#if (BSP_CFG_USER_STACK_ENABLE == 1)
    #define PSW_init  (0x00030000)
#else
    #define PSW_init  (0x00010000)
#endif

/***********************************************************************************************************************
Pre-processor Directives
***********************************************************************************************************************/
/* Set this as the entry point from a power-on reset */
#pragma entry PowerON_Reset_PC

/***********************************************************************************************************************
External function Prototypes
***********************************************************************************************************************/
/* Functions to setup I/O library */
extern void _INIT_IOLIB(void);
extern void _CLOSEALL(void);

#if BSP_CFG_USER_WARM_START_CALLBACK_PRE_INITC_ENABLED != 0
/* If user is requesting warm start callback functions then these are the prototypes. */
void BSP_CFG_USER_WARM_START_PRE_C_FUNCTION(void);
#endif

#if BSP_CFG_USER_WARM_START_CALLBACK_POST_INITC_ENABLED != 0
/* If user is requesting warm start callback functions then these are the prototypes. */
void BSP_CFG_USER_WARM_START_POST_C_FUNCTION(void);
#endif
/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* Power-on reset function declaration */
void PowerON_Reset_PC(void);

#if BSP_CFG_RUN_IN_USER_MODE==1
    #if __RENESAS_VERSION__ < 0x01010000
        /* Declare the contents of the function 'Change_PSW_PM_to_UserMode' as assembler to the compiler */
        #pragma inline_asm Change_PSW_PM_to_UserMode

        /* MCU user mode switcher function declaration */
        static void Change_PSW_PM_to_UserMode(void);
    #endif
#endif

/* Main program function declaration */
void main(void);
#if (BSP_CFG_USE_CGC_MODULE == 0)
static void operating_frequency_set(void);
static void clock_source_select(void);
#else
static void cgc_clock_config(void);
#endif
/***********************************************************************************************************************
* Function name: PowerON_Reset_PC
* Description  : This function is the MCU's entry point from a power-on reset.
*                The following steps are taken in the startup code:
*                1. The User Stack Pointer (USP) and Interrupt Stack Pointer (ISP) are both set immediately after entry 
*                   to this function. The USP and ISP stack sizes are set in the file bsp_config.h.
*                   Default sizes are USP=1K and ISP=256.
*                2. The interrupt vector base register is set to point to the beginning of the relocatable interrupt 
*                   vector table.
*                3. The MCU operating frequency is set by configuring the Clock Generation Circuit (CGC) in
*                   operating_frequency_set.
*                4. Calls are made to functions to setup the C runtime environment which involves initializing all 
*                   initialed data, zeroing all uninitialized variables, and configuring STDIO if used
*                   (calls to _INITSCT and _INIT_IOLIB).
*                5. Board-specific hardware setup, including configuring I/O pins on the MCU, in hardware_setup.
*                6. Global interrupts are enabled by setting the I bit in the Program Status Word (PSW), and the stack 
*                   is switched from the ISP to the USP.  The initial Interrupt Priority Level is set to zero, enabling 
*                   any interrupts with a priority greater than zero to be serviced.
*                7. The processor is optionally switched to user mode.  To run in user mode, set the macro 
*                   BSP_CFG_RUN_IN_USER_MODE above to a 1.
*                8. The bus error interrupt is enabled to catch any accesses to invalid or reserved areas of memory.
*
*                Once this initialization is complete, the user's main() function is called.  It should not return.
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
void PowerON_Reset_PC(void)
{
    /* Stack pointers are setup prior to calling this function - see comments above */    
    
    /* Initialise the MCU processor word */
#if __RENESAS_VERSION__ >= 0x01010000    
    set_intb((void *)__sectop("C$VECT"));
#else
    set_intb((unsigned long)__sectop("C$VECT"));
#endif    

#if (BSP_CFG_USE_CGC_MODULE == 0)
    /* Switch to high-speed operation */
    operating_frequency_set();
#else
    cgc_clock_config();
#endif

    /* If the warm start Pre C runtime callback is enabled, then call it. */
#if BSP_CFG_USER_WARM_START_CALLBACK_PRE_INITC_ENABLED == 1
     BSP_CFG_USER_WARM_START_PRE_C_FUNCTION();
#endif

    /* Initialize C runtime environment */
    _INITSCT();

    /* If the warm start Post C runtime callback is enabled, then call it. */
#if BSP_CFG_USER_WARM_START_CALLBACK_POST_INITC_ENABLED == 1
     BSP_CFG_USER_WARM_START_POST_C_FUNCTION();
#endif

#if BSP_CFG_IO_LIB_ENABLE == 1
    /* Comment this out if not using I/O lib */
    _INIT_IOLIB();
#endif

    /* Initialize MCU interrupt callbacks. */
    bsp_interrupt_open();

    /* Initialize register protection functionality. */
    bsp_register_protect_open();

    /* Configure the MCU and board hardware */
    hardware_setup();

    /* Change the MCU's user mode from supervisor to user */
    nop();
    set_psw(PSW_init);      
#if BSP_CFG_RUN_IN_USER_MODE==1
    /* Use chg_pmusr() intrinsic if possible. */
    #if __RENESAS_VERSION__ >= 0x01010000
    chg_pmusr() ;
    #else
    Change_PSW_PM_to_UserMode();
    #endif
#endif

    /* Enable the bus error interrupt to catch accesses to illegal/reserved areas of memory */
    R_BSP_InterruptControl(BSP_INT_SRC_BUS_ERROR, BSP_INT_CMD_INTERRUPT_ENABLE, FIT_NO_PTR);

    /* Call the main program function (should not return) */
    main();
    
#if BSP_CFG_IO_LIB_ENABLE == 1
    /* Comment this out if not using I/O lib - cleans up open files */
    _CLOSEALL();
#endif

    /* BCH - 01/16/2013 */
    /* Infinite loop is intended here. */    
    while(1) /* PRQA S 2740 */
    {
        /* Infinite loop. Put a breakpoint here if you want to catch an exit of main(). */
    }
}


#if (BSP_CFG_USE_CGC_MODULE == 0)

/***********************************************************************************************************************
* Function name: operating_frequency_set
* Description  : Configures the clock settings for each of the device clocks
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void operating_frequency_set (void)
{
    /* Used for constructing value to write to SCKCR and CKOCR registers. */
    uint32_t temp_clock = 0;
    
    /* 
    Default settings:
    Clock Description              Frequency
    ----------------------------------------
    Input Clock Frequency............  16 MHz
    PLL frequency (x3)...............  48 MHz
    Internal Clock Frequency.........  24 MHz
    Peripheral Clock Frequency.......  24 MHz
    Clock Out Frequency..............  1  MHz */

    /* Protect off. */
    SYSTEM.PRCR.WORD = 0xA50F;
    
    /* Select the clock based upon user's choice. */
    clock_source_select();

    /* Figure out setting for FCK bits. */
#if   BSP_CFG_FCK_DIV == 1
    /* Do nothing since FCK bits should be 0. */
#elif BSP_CFG_FCK_DIV == 2
    temp_clock |= 0x10000000;
#elif BSP_CFG_FCK_DIV == 4
    temp_clock |= 0x20000000;
#elif BSP_CFG_FCK_DIV == 8
    temp_clock |= 0x30000000;
#elif BSP_CFG_FCK_DIV == 16
    temp_clock |= 0x40000000;
#elif BSP_CFG_FCK_DIV == 32
    temp_clock |= 0x50000000;
#elif BSP_CFG_FCK_DIV == 64
    temp_clock |= 0x60000000;
#else
    #error "Error! Invalid setting for BSP_CFG_FCK_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for ICK bits. */
#if   BSP_CFG_ICK_DIV == 1
    /* Do nothing since ICK bits should be 0. */
#elif BSP_CFG_ICK_DIV == 2
    temp_clock |= 0x01000000;
#elif BSP_CFG_ICK_DIV == 4
    temp_clock |= 0x02000000;
#elif BSP_CFG_ICK_DIV == 8
    temp_clock |= 0x03000000;
#elif BSP_CFG_ICK_DIV == 16
    temp_clock |= 0x04000000;
#elif BSP_CFG_ICK_DIV == 32
    temp_clock |= 0x05000000;
#elif BSP_CFG_ICK_DIV == 64
    temp_clock |= 0x06000000;
#else
    #error "Error! Invalid setting for BSP_CFG_ICK_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for PCKB bits. */
#if   BSP_CFG_PCKB_DIV == 1
    /* Do nothing since PCKB bits should be 0. */
#elif BSP_CFG_PCKB_DIV == 2
    temp_clock |= 0x00000100;
#elif BSP_CFG_PCKB_DIV == 4
    temp_clock |= 0x00000200;
#elif BSP_CFG_PCKB_DIV == 8
    temp_clock |= 0x00000300;
#elif BSP_CFG_PCKB_DIV == 16
    temp_clock |= 0x00000400;
#elif BSP_CFG_PCKB_DIV == 32
    temp_clock |= 0x00000500;
#elif BSP_CFG_PCKB_DIV == 64
    temp_clock |= 0x00000600;
#else
    #error "Error! Invalid setting for BSP_CFG_PCKB_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for PCKD bits. */
#if   BSP_CFG_PCKD_DIV == 1
    /* Do nothing since PCKD bits should be 0. */
#elif BSP_CFG_PCKD_DIV == 2
    temp_clock |= 0x00000001;
#elif BSP_CFG_PCKD_DIV == 4
    temp_clock |= 0x00000002;
#elif BSP_CFG_PCKD_DIV == 8
    temp_clock |= 0x00000003;
#elif BSP_CFG_PCKD_DIV == 16
    temp_clock |= 0x00000004;
#elif BSP_CFG_PCKD_DIV == 32
    temp_clock |= 0x00000005;
#elif BSP_CFG_PCKD_DIV == 64
    temp_clock |= 0x00000006;
#else
    #error "Error! Invalid setting for BSP_CFG_PCKD_DIV in r_bsp_config.h"
#endif

    /* Set SCKCR register. */
    SYSTEM.SCKCR.LONG = temp_clock;
    
    /* Choose clock source. Default for r_bsp_config.h is PLL. */
    SYSTEM.SCKCR3.WORD = ((uint16_t)BSP_CFG_CLOCK_SOURCE) << 8;

#if (BSP_CFG_CLOCK_SOURCE != 0)
    /* We can now turn LOCO off since it is not going to be used. */
    SYSTEM.LOCOCR.BYTE = 0x01;
#endif

    /* Protect on. */
    SYSTEM.PRCR.WORD = 0xA500;          
}

/***********************************************************************************************************************
* Function name: clock_source_select
* Description  : Enables and disables clocks as chosen by the user. If a clock other than LOCO or HOCO is already
*                running when this function is called then that usually means a bootloader was run beforehand and set
*                up the clocks already.
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void clock_source_select (void)
{

#if (BSP_CFG_CLOCK_SOURCE == 1)
    /* HOCO is chosen. Start it operating if it is not already operating. */
    if (1 == SYSTEM.HOCOCR.BIT.HCSTP)
    {
        /* Set HOCO wait control register for 266 cycles. */
        SYSTEM.HOCOWTCR.BYTE = 0x06;

        /* Start HOCO operating. */
        SYSTEM.HOCOCR.BYTE = 0x00;
    }

    while (0 == SYSTEM.OSCOVFSR.BIT.HCOVF)
    {
        /* Make sure clock has stabilized. */
    }

#else
    /* HOCO is not chosen. Stop the HOCO. */
    SYSTEM.HOCOCR.BYTE = 0x01;
#endif

#if (BSP_CFG_CLOCK_SOURCE == 2)

    /* Main clock oscillator is chosen. Start it operating if it is not already operating. If it was already operating*/
    if (1 == SYSTEM.MOSCCR.BIT.MOSTP)
    {
        /* If the main oscillator is >10MHz then the main clock oscillator forced oscillation control register (MOFCR) must
           be changed. */
        if (BSP_CFG_XTAL_HZ > 10000000)
        {
            /* 10 - 20MHz. */
            SYSTEM.MOFCR.BIT.MODRV21 = 1;
        }
        else
        {
            /* 1 - 10MHz. */
            SYSTEM.MOFCR.BIT.MODRV21 = 0;
        }

        /* Wait 32768 cycles (8.192ms). Adjust if needed. */
        SYSTEM.MOSCWTCR.BYTE = 0x06;

        /* Set the main clock to operating. */
        SYSTEM.MOSCCR.BYTE = 0x00;
    }

    while (0 == SYSTEM.OSCOVFSR.BIT.MOOVF)
    {
        /* Make sure clock has stabilized. */
    }
#else
    /* Set the main clock to stopped. */
    SYSTEM.MOSCCR.BYTE = 0x01;          
#endif

#if (BSP_CFG_CLOCK_SOURCE == 3)
    /* Sub-clock oscillator is chosen. Start it operating. */

    /* Set the sub-clock to operating. */
    SYSTEM.SOSCCR.BYTE = 0x00;

    /* The delay loops used below have been measured to take 11 cycles per iteration. This has been verified using the
       Renesas RX Toolchain with optimizations set to 2, size priority. The same result was obtained using 2, speed
       priority. At this time the MCU is still running on the 4MHz LOCO so it is approximately 2.75us per iteration. */

    /* There is not an oscillation stabilization flag for the sub-clock so a software delay is used.
       The delay period needed is to make sure that the sub-clock has stabilized. According to Rev.1.00 of the RX111's
       HW manual the delay period is tSUBOSC which is typically 0.5 seconds. */
    R_BSP_SoftwareDelay(500, BSP_DELAY_MILLISECS);
#else
    /* Set the sub-clock to stopped. */
    SYSTEM.SOSCCR.BYTE = 0x01;
#endif

#if (BSP_CFG_CLOCK_SOURCE == 4)
    /* PLL is chosen. Start it operating if it is not already. Must start main clock as well since PLL uses it. */

    if (1 == SYSTEM.PLLCR2.BIT.PLLEN)
    {
        /* If the main oscillator is >10MHz then the main clock oscillator forced oscillation control register (MOFCR) must
           be changed. */
        if (BSP_CFG_XTAL_HZ > 10000000)
        {
            /* 10 - 20MHz. */
            SYSTEM.MOFCR.BIT.MODRV21 = 1;
        }
        else
        {
            /* 1 - 10MHz. */
            SYSTEM.MOFCR.BIT.MODRV21 = 0;
        }

        /* Wait 32768 cycles (8.192ms). Adjust if needed. */
        SYSTEM.MOSCWTCR.BYTE = 0x06;

        /* Set the main clock to operating. */
        SYSTEM.MOSCCR.BYTE = 0x00;

        /* Set PLL Input Divisor. */
        SYSTEM.PLLCR.BIT.PLIDIV = BSP_CFG_PLL_DIV >> 1;

        /* Set PLL Multiplier. */
        SYSTEM.PLLCR.BIT.STC = (BSP_CFG_PLL_MUL * 2) - 1;

        /* Set the PLL to operating. */
        SYSTEM.PLLCR2.BYTE = 0x00;
    }

    while (0 == SYSTEM.OSCOVFSR.BIT.PLOVF)
    {
        /* Make sure clock has stabilized. */
    }
#else
    /* Set the PLL to stopped. */
    SYSTEM.PLLCR2.BYTE = 0x01;          
#endif

    /* LOCO is saved for last since it is what is running by default out of reset. This means you do not want to turn
       it off until another clock has been enabled and is ready to use. */
#if (BSP_CFG_CLOCK_SOURCE == 0)
    /* LOCO is chosen. This is the default out of reset. */
    SYSTEM.LOCOCR.BYTE = 0x00;
#else
    /* LOCO is not chosen but it cannot be turned off yet since it is still being used. */
#endif

    /* Make sure a valid clock was chosen. */
#if (BSP_CFG_CLOCK_SOURCE > 4) || (BSP_CFG_CLOCK_SOURCE < 0)
    #error "ERROR - Valid clock source must be chosen in r_bsp_config.h using BSP_CFG_CLOCK_SOURCE macro."
#endif
}

#else

/***********************************************************************************************************************
* Function name: cgc_clock_config
* Description  : Configures the clock settings for each of the device clocks. Uses the r_cgc_rx module.
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void cgc_clock_config (void)
{
    cgc_clocks_t                clock;
    cgc_clock_config_t          pll_config;
    cgc_system_clock_config_t   sys_config;

    /* Figure out setting for FCK bits. */
#if   BSP_CFG_FCK_DIV == 1
    sys_config.fclk_div = CGC_SYS_CLOCK_DIV_1;
#elif BSP_CFG_FCK_DIV == 2
    sys_config.fclk_div = CGC_SYS_CLOCK_DIV_2;
#elif BSP_CFG_FCK_DIV == 4
    sys_config.fclk_div = CGC_SYS_CLOCK_DIV_4;
#elif BSP_CFG_FCK_DIV == 8
    sys_config.fclk_div = CGC_SYS_CLOCK_DIV_8;
#elif BSP_CFG_FCK_DIV == 16
    sys_config.fclk_div = CGC_SYS_CLOCK_DIV_16;
#elif BSP_CFG_FCK_DIV == 32
    sys_config.fclk_div = CGC_SYS_CLOCK_DIV_32;
#elif BSP_CFG_FCK_DIV == 64
    sys_config.fclk_div = CGC_SYS_CLOCK_DIV_64;
#else
    #error "Error! Invalid setting for BSP_CFG_FCK_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for ICK bits. */
#if   BSP_CFG_ICK_DIV == 1
    sys_config.iclk_div = CGC_SYS_CLOCK_DIV_1;
#elif BSP_CFG_ICK_DIV == 2
    sys_config.iclk_div = CGC_SYS_CLOCK_DIV_2;
#elif BSP_CFG_ICK_DIV == 4
    sys_config.iclk_div = CGC_SYS_CLOCK_DIV_4;
#elif BSP_CFG_ICK_DIV == 8
    sys_config.iclk_div = CGC_SYS_CLOCK_DIV_8;
#elif BSP_CFG_ICK_DIV == 16
    sys_config.iclk_div = CGC_SYS_CLOCK_DIV_16;
#elif BSP_CFG_ICK_DIV == 32
    sys_config.iclk_div = CGC_SYS_CLOCK_DIV_32;
#elif BSP_CFG_ICK_DIV == 64
    sys_config.iclk_div = CGC_SYS_CLOCK_DIV_64;
#else
    #error "Error! Invalid setting for BSP_CFG_ICK_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for PCKB bits. */
#if   BSP_CFG_PCKB_DIV == 1
    sys_config.pclkb_div = CGC_SYS_CLOCK_DIV_1;
#elif BSP_CFG_PCKB_DIV == 2
    sys_config.pclkb_div = CGC_SYS_CLOCK_DIV_2;
#elif BSP_CFG_PCKB_DIV == 4
    sys_config.pclkb_div = CGC_SYS_CLOCK_DIV_4;
#elif BSP_CFG_PCKB_DIV == 8
    sys_config.pclkb_div = CGC_SYS_CLOCK_DIV_8;
#elif BSP_CFG_PCKB_DIV == 16
    sys_config.pclkb_div = CGC_SYS_CLOCK_DIV_16;
#elif BSP_CFG_PCKB_DIV == 32
    sys_config.pclkb_div = CGC_SYS_CLOCK_DIV_32;
#elif BSP_CFG_PCKB_DIV == 64
    sys_config.pclkb_div = CGC_SYS_CLOCK_DIV_64;
#else
    #error "Error! Invalid setting for BSP_CFG_PCKB_DIV in r_bsp_config.h"
#endif

    /* Figure out setting for PCKD bits. */
#if   BSP_CFG_PCKD_DIV == 1
    sys_config.pclkd_div = CGC_SYS_CLOCK_DIV_1;
#elif BSP_CFG_PCKD_DIV == 2
    sys_config.pclkd_div = CGC_SYS_CLOCK_DIV_2;
#elif BSP_CFG_PCKD_DIV == 4
    sys_config.pclkd_div = CGC_SYS_CLOCK_DIV_4;
#elif BSP_CFG_PCKD_DIV == 8
    sys_config.pclkd_div = CGC_SYS_CLOCK_DIV_8;
#elif BSP_CFG_PCKD_DIV == 16
    sys_config.pclkd_div = CGC_SYS_CLOCK_DIV_16;
#elif BSP_CFG_PCKD_DIV == 32
    sys_config.pclkd_div = CGC_SYS_CLOCK_DIV_32;
#elif BSP_CFG_PCKD_DIV == 64
    sys_config.pclkd_div = CGC_SYS_CLOCK_DIV_64;
#else
    #error "Error! Invalid setting for BSP_CFG_PCKD_DIV in r_bsp_config.h"
#endif

    /* Initialize CGC. */
    R_CGC_Open();

#if (BSP_CFG_CLOCK_SOURCE == 1)
    /* HOCO is chosen. Start it operating. */
    clock = CGC_HOCO;
    R_CGC_ClockStart(clock, (cgc_clock_config_t *)FIT_NO_PTR);
#else
    /* HOCO is not chosen. Stop the HOCO. */
    R_CGC_ClockStop(CGC_HOCO);
#endif

#if (BSP_CFG_CLOCK_SOURCE == 2)
    /* Main clock oscillator is chosen. Start it operating. */
    clock = CGC_MAIN_OSC;
    R_CGC_ClockStart(clock, (cgc_clock_config_t *)FIT_NO_PTR);
#else
    /* Set the main clock to stopped. */
    R_CGC_ClockStop(CGC_MAIN_OSC);
#endif

#if (BSP_CFG_CLOCK_SOURCE == 3)
    /* Sub-clock oscillator is chosen. Start it operating. */
    clock = CGC_SUBCLOCK;
    R_CGC_ClockStart(clock, (cgc_clock_config_t *)FIT_NO_PTR);
#else
    /* Set the sub-clock to stopped. */
    R_CGC_ClockStop(CGC_SUBCLOCK);
#endif

#if (BSP_CFG_CLOCK_SOURCE == 4)
    /* PLL is chosen. Start it operating. Must start main clock as well since PLL uses it. */
    clock = CGC_PLL;

    #if   (BSP_CFG_PLL_DIV == 1)
    pll_config.divider = CGC_PLL_DIV_1;
    #elif (BSP_CFG_PLL_DIV == 2)
    pll_config.divider = CGC_PLL_DIV_2;
    #elif (BSP_CFG_PLL_DIV == 4)
    pll_config.divider = CGC_PLL_DIV_4;
    #else
        #error "Error! Invalid setting for BSP_CFG_PLL_DIV in r_bsp_config.h"
    #endif

    #if   (BSP_CFG_PLL_MUL == 6)
    pll_config.multiplier = CGC_PLL_MUL_6;
    #elif (BSP_CFG_PLL_MUL == 8)
    pll_config.multiplier = CGC_PLL_MUL_8;
    #else
        #error "Error! Invalid setting for BSP_CFG_PLL_MUL in r_bsp_config.h"
    #endif

    R_CGC_ClockStart(CGC_MAIN_OSC, (cgc_clock_config_t *)FIT_NO_PTR);
    R_CGC_ClockStart(clock, &pll_config);
#else
    /* Set the PLL to stopped. */
    R_CGC_ClockStop(CGC_PLL);
#endif

    /* LOCO is saved for last since it is what is running by default out of reset. This means you do not want to turn
       it off until another clock has been enabled and is ready to use. */
#if (BSP_CFG_CLOCK_SOURCE == 0)
    /* LOCO is chosen. This is the default out of reset. */
#else
    /* LOCO is not chosen. Turn off the LOCO and switch to other clock. */
    while (R_CGC_ClockCheck(clock) == CGC_ERR_NOT_STABILIZED)
    {
        /* Wait for chosen clock to stabilize. */
    }

    R_CGC_SystemClockSet(clock, &sys_config);
#endif

    /* Make sure a valid clock was chosen. */
#if (BSP_CFG_CLOCK_SOURCE > 4) || (BSP_CFG_CLOCK_SOURCE < 0)
    #error "ERROR - Valid clock source must be chosen in r_bsp_config.h using BSP_CFG_CLOCK_SOURCE macro."
#endif
}

#endif /* BSP_CFG_USE_CGC_MODULE */

/***********************************************************************************************************************
* Function name: Change_PSW_PM_to_UserMode
* Description  : Assembler function, used to change the MCU's user mode from supervisor to user.
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
#if BSP_CFG_RUN_IN_USER_MODE==1
    #if __RENESAS_VERSION__ < 0x01010000
static void Change_PSW_PM_to_UserMode(void)
{
    MVFC   PSW,R1
    OR     #00100000h,R1
    PUSH.L R1
    MVFC   PC,R1
    ADD    #10,R1
    PUSH.L R1
    RTE
    NOP
    NOP
}
    #endif
#endif
