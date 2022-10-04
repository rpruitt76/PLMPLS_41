################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/cg_src/r_cg_cac.c \
../src/cg_src/r_cg_cac_user.c \
../src/cg_src/r_cg_cgc.c \
../src/cg_src/r_cg_cgc_user.c \
../src/cg_src/r_cg_cmt.c \
../src/cg_src/r_cg_cmt_user.c \
../src/cg_src/r_cg_crc.c \
../src/cg_src/r_cg_hardware_setup.c \
../src/cg_src/r_cg_icu.c \
../src/cg_src/r_cg_icu_user.c \
../src/cg_src/r_cg_lpc.c \
../src/cg_src/r_cg_lpc_user.c \
../src/cg_src/r_cg_main.c \
../src/cg_src/r_cg_mtu3.c \
../src/cg_src/r_cg_mtu3_user.c \
../src/cg_src/r_cg_port.c \
../src/cg_src/r_cg_port_user.c \
../src/cg_src/r_cg_rtc.c \
../src/cg_src/r_cg_rtc_user.c \
../src/cg_src/r_cg_s12ad.c \
../src/cg_src/r_cg_s12ad_user.c \
../src/cg_src/r_cg_sci.c \
../src/cg_src/r_cg_sci_user.c \
../src/cg_src/r_cg_tmr.c \
../src/cg_src/r_cg_tmr_user.c \
../src/cg_src/r_cg_wdt.c \
../src/cg_src/r_cg_wdt_user.c 

COMPILER_OBJS += \
src/cg_src/r_cg_cac.obj \
src/cg_src/r_cg_cac_user.obj \
src/cg_src/r_cg_cgc.obj \
src/cg_src/r_cg_cgc_user.obj \
src/cg_src/r_cg_cmt.obj \
src/cg_src/r_cg_cmt_user.obj \
src/cg_src/r_cg_crc.obj \
src/cg_src/r_cg_hardware_setup.obj \
src/cg_src/r_cg_icu.obj \
src/cg_src/r_cg_icu_user.obj \
src/cg_src/r_cg_lpc.obj \
src/cg_src/r_cg_lpc_user.obj \
src/cg_src/r_cg_main.obj \
src/cg_src/r_cg_mtu3.obj \
src/cg_src/r_cg_mtu3_user.obj \
src/cg_src/r_cg_port.obj \
src/cg_src/r_cg_port_user.obj \
src/cg_src/r_cg_rtc.obj \
src/cg_src/r_cg_rtc_user.obj \
src/cg_src/r_cg_s12ad.obj \
src/cg_src/r_cg_s12ad_user.obj \
src/cg_src/r_cg_sci.obj \
src/cg_src/r_cg_sci_user.obj \
src/cg_src/r_cg_tmr.obj \
src/cg_src/r_cg_tmr_user.obj \
src/cg_src/r_cg_wdt.obj \
src/cg_src/r_cg_wdt_user.obj 

C_DEPS += \
src/cg_src/r_cg_cac.d \
src/cg_src/r_cg_cac_user.d \
src/cg_src/r_cg_cgc.d \
src/cg_src/r_cg_cgc_user.d \
src/cg_src/r_cg_cmt.d \
src/cg_src/r_cg_cmt_user.d \
src/cg_src/r_cg_crc.d \
src/cg_src/r_cg_hardware_setup.d \
src/cg_src/r_cg_icu.d \
src/cg_src/r_cg_icu_user.d \
src/cg_src/r_cg_lpc.d \
src/cg_src/r_cg_lpc_user.d \
src/cg_src/r_cg_main.d \
src/cg_src/r_cg_mtu3.d \
src/cg_src/r_cg_mtu3_user.d \
src/cg_src/r_cg_port.d \
src/cg_src/r_cg_port_user.d \
src/cg_src/r_cg_rtc.d \
src/cg_src/r_cg_rtc_user.d \
src/cg_src/r_cg_s12ad.d \
src/cg_src/r_cg_s12ad_user.d \
src/cg_src/r_cg_sci.d \
src/cg_src/r_cg_sci_user.d \
src/cg_src/r_cg_tmr.d \
src/cg_src/r_cg_tmr_user.d \
src/cg_src/r_cg_wdt.d \
src/cg_src/r_cg_wdt_user.d 

# Each subdirectory must supply rules for building sources it contributes
src/cg_src/%.obj: ../src/cg_src/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	scandep1 -MM -MP -MF"$(@:%.obj=%.d)" -MT"$(@:%.d=%.obj)" -MT"$(@:%.obj=%.d)" -I"C:\Program Files (x86)\Renesas\RX\2_1_0\include" -I"C:\Software3\PLMPLS_41\r_bsp" -I"C:\Software3\PLMPLS_41\r_config" -I"C:\Software3\PLMPLS_41\r_bsp\board\rskrx64m" -I"C:\Software3\PLMPLS_41\r_bsp\mcu" -I"C:\Software3\PLMPLS_41\r_bsp\mcu\rx64m" -I"C:\Software3\PLMPLS_41\r_bsp\mcu\rx64m\register_access" -I"C:\Software3\PLMPLS_41\r_flash_rx" -I"C:\Software3\PLMPLS_41\r_flash_rx\src" -I"C:\Software3\PLMPLS_41\r_flash_rx\src\targets" -I"C:\Software3\PLMPLS_41\r_flash_rx\src\non_fcu\rx100" -I"C:\Software3\PLMPLS_41\r_flash_rx\src\fcu" -I"C:\Software3\PLMPLS_41\src\cg_src" -I"C:\Software3\PLMPLS_41\src" -I"C:\Software3\PLMPLS_41\App" -I"C:\Software3\PLMPLS_41\USBStack" -I"C:\Software3\PLMPLS_41\USBStack\MSC" -DSTRM_COM -DCLW -D__RX -DDEBUGGR -DMONITOR_APP_EN=1 -DPLM_HARDWARE -DDDFB -DSTRM_NO -DCOSMAN -D__STDC_VERSION__=199901L -D__STDC_HOSTED__=1 -D__STDC_IEC_559__=1 -D__STDC_IEC_559_COMPLEX__=1 -D__STDC_ISO_10646__=199712L -D__LIT=1 -D__DBL8=1 -D__UCHAR=1 -D__UBIT=1 -D__RON=1 -D__DOFF=1 -D__BITRIGHT=1 -D__INTRINSIC_LIB=1 -D__FPU=1 -D__RX600=1 -D__RENESAS__=1 -D__RENESAS_VERSION__=0x02010000 -D__RX=1 -D__STDC__=1 -U_STDC_HOSTED_ -U_WIN32 -UWIN32 -U_WIN32_ -U_GNUC_ -U_GNUC_MINOR_ -U_GNUC_PATCHLEVEL_ -E -quiet -I. -C  "$<"
	@echo src\cg_src\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\cg_src\cSubCommand.tmp"
	ccrx -subcommand="src\cg_src\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

