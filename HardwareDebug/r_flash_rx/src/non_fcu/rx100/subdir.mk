################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../r_flash_rx/src/non_fcu/rx100/r_codeflash_extra_rx100.c \
../r_flash_rx/src/non_fcu/rx100/r_codeflash_rx100.c \
../r_flash_rx/src/non_fcu/rx100/r_dataflash_rx100.c \
../r_flash_rx/src/non_fcu/rx100/r_flash_rx100_rx.c \
../r_flash_rx/src/non_fcu/rx100/r_flash_utils.c 

COMPILER_OBJS += \
r_flash_rx/src/non_fcu/rx100/r_codeflash_extra_rx100.obj \
r_flash_rx/src/non_fcu/rx100/r_codeflash_rx100.obj \
r_flash_rx/src/non_fcu/rx100/r_dataflash_rx100.obj \
r_flash_rx/src/non_fcu/rx100/r_flash_rx100_rx.obj \
r_flash_rx/src/non_fcu/rx100/r_flash_utils.obj 

C_DEPS += \
r_flash_rx/src/non_fcu/rx100/r_codeflash_extra_rx100.d \
r_flash_rx/src/non_fcu/rx100/r_codeflash_rx100.d \
r_flash_rx/src/non_fcu/rx100/r_dataflash_rx100.d \
r_flash_rx/src/non_fcu/rx100/r_flash_rx100_rx.d \
r_flash_rx/src/non_fcu/rx100/r_flash_utils.d 

# Each subdirectory must supply rules for building sources it contributes
r_flash_rx/src/non_fcu/rx100/%.obj: ../r_flash_rx/src/non_fcu/rx100/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	scandep1 -MM -MP -MF"$(@:%.obj=%.d)" -MT"$(@:%.d=%.obj)" -MT"$(@:%.obj=%.d)" -I"C:\Program Files (x86)\Renesas\RX\2_1_0\include" -I"C:\Software3\PLMPLS_41\r_bsp" -I"C:\Software3\PLMPLS_41\r_config" -I"C:\Software3\PLMPLS_41\r_bsp\board\rskrx64m" -I"C:\Software3\PLMPLS_41\r_bsp\mcu" -I"C:\Software3\PLMPLS_41\r_bsp\mcu\rx64m" -I"C:\Software3\PLMPLS_41\r_bsp\mcu\rx64m\register_access" -I"C:\Software3\PLMPLS_41\r_flash_rx" -I"C:\Software3\PLMPLS_41\r_flash_rx\src" -I"C:\Software3\PLMPLS_41\r_flash_rx\src\targets" -I"C:\Software3\PLMPLS_41\r_flash_rx\src\non_fcu\rx100" -I"C:\Software3\PLMPLS_41\r_flash_rx\src\fcu" -I"C:\Software3\PLMPLS_41\src\cg_src" -I"C:\Software3\PLMPLS_41\src" -I"C:\Software3\PLMPLS_41\App" -I"C:\Software3\PLMPLS_41\USBStack" -I"C:\Software3\PLMPLS_41\USBStack\MSC" -DSTRM_COM -DCLW -D__RX -DDEBUGGR -DMONITOR_APP_EN=1 -DPLM_HARDWARE -DDDFB -DSTRM_NO -DCOSMAN -D__STDC_VERSION__=199901L -D__STDC_HOSTED__=1 -D__STDC_IEC_559__=1 -D__STDC_IEC_559_COMPLEX__=1 -D__STDC_ISO_10646__=199712L -D__LIT=1 -D__DBL8=1 -D__UCHAR=1 -D__UBIT=1 -D__RON=1 -D__DOFF=1 -D__BITRIGHT=1 -D__INTRINSIC_LIB=1 -D__FPU=1 -D__RX600=1 -D__RENESAS__=1 -D__RENESAS_VERSION__=0x02010000 -D__RX=1 -D__STDC__=1 -U_STDC_HOSTED_ -U_WIN32 -UWIN32 -U_WIN32_ -U_GNUC_ -U_GNUC_MINOR_ -U_GNUC_PATCHLEVEL_ -E -quiet -I. -C  "$<"
	@echo r_flash_rx\src\non_fcu\rx100\cSubCommand.tmp=
	@sed -e "s/^/ /" "r_flash_rx\src\non_fcu\rx100\cSubCommand.tmp"
	ccrx -subcommand="r_flash_rx\src\non_fcu\rx100\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

