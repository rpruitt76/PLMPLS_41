################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include makefile.init

RM := rm -rf *.sni *.dbg *.lst *.lis *.lpp *.map *.x *.lbp *.bls *.libelf *.rel *.lbk *.abs *.mi *.jmp *.fsy *.ud *.udm 1st/*.abs 1st/*.jmp 1st/*.fsy

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include USBStack/subdir.mk
-include r_flash_rx/src/non_fcu/rx100/subdir.mk
-include App/subdir.mk
-include r_bsp/mcu/all/subdir.mk
-include src/cg_src/subdir.mk
-include r_flash_rx/src/subdir.mk
-include r_bsp/board/rskrx64m/subdir.mk
-include USBStack/MSC/subdir.mk
-include r_bsp/mcu/rx64m/subdir.mk
-include r_flash_rx/src/fcu/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif 
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif 
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif 
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif 
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif 
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif 
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif 
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif 
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif 
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif 
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif 
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif 
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif 
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif 
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif


-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables
LINKER_OUTPUT_OUTPUTS += \
PLM_CG_FIT_Flash.abs

LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS += \
PLM_CG_FIT_Flash.lib

CONVERTOR_OUTPUT_OUTPUTS += \
PLM_CG_FIT_Flash.mot

OBJS := \
$(COMPILER_OBJS) \
$(INDIVIDUAL_COMPILER_OBJS) \
$(ASSEMBLER_OBJS) \
$(CUSTOM_OBJS)

# All Target
all: $(CONVERTOR_OUTPUT_OUTPUTS) PLM_CG_FIT_Flash.x

	@echo 'Build complete.'

PLM_CG_FIT_Flash.mot: $(LINKER_OUTPUT_OUTPUTS) 
	@echo 'Invoking: Converter'
	@echo 'Building target:'
	@echo ConverterPLM_CG_FIT_Flash.tmp=
	@sed -e "s/^/    /" "ConverterPLM_CG_FIT_Flash.tmp"
	rlink   "PLM_CG_FIT_Flash.abs" -subcommand="ConverterPLM_CG_FIT_Flash.tmp"
	@echo 'Finished building target:'
	@echo.


PLM_CG_FIT_Flash.abs: $(OBJS)  $(ALL_ASMS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) 
	@echo 'Invoking: Linker'
	@echo LinkerPLM_CG_FIT_Flash.tmp=
	@sed -e "s/^/    /" "LinkerPLM_CG_FIT_Flash.tmp"
	rlink -subcommand="LinkerPLM_CG_FIT_Flash.tmp"
	@echo 'Finished building:'
	@echo.


PLM_CG_FIT_Flash.lib: 
	@echo 'Invoking: Library Generator'
	@echo LibraryGeneratorPLM_CG_FIT_Flash.tmp=
	@sed -e "s/^/    /" "LibraryGeneratorPLM_CG_FIT_Flash.tmp"
	lbgrx -subcommand="LibraryGeneratorPLM_CG_FIT_Flash.tmp"
	@echo 'Finished building:'
	@echo.

PLM_CG_FIT_Flash.x: PLM_CG_FIT_Flash.abs
		-C:\Users\rprui\.eclipse\com.renesas.platform_1435879475\Utilities\\ccrx\renesas_cc_converter.exe PLM_CG_FIT_Flash.abs PLM_CG_FIT_Flash.x

# Other Targets
clean:
	-$(RM) $(LINKER_OUTPUT_OUTPUTS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(CONVERTOR_OUTPUT_OUTPUTS)
	-rm -rf $(OBJS) $(C_DEPS) $(ASM_DEPS) $(DSP_DEPS) 
	-rm -rf src/*.asm src/*.p src/*.pp src/*.src src/*.jmp src/*.lst src/*.prn src/*.i src/*.ud 
	-rm -rf USBStack/*.asm USBStack/*.p USBStack/*.pp USBStack/*.src USBStack/*.jmp USBStack/*.lst USBStack/*.prn USBStack/*.i USBStack/*.ud 
	-rm -rf r_flash_rx/src/non_fcu/rx100/*.asm r_flash_rx/src/non_fcu/rx100/*.p r_flash_rx/src/non_fcu/rx100/*.pp r_flash_rx/src/non_fcu/rx100/*.src r_flash_rx/src/non_fcu/rx100/*.jmp r_flash_rx/src/non_fcu/rx100/*.lst r_flash_rx/src/non_fcu/rx100/*.prn r_flash_rx/src/non_fcu/rx100/*.i r_flash_rx/src/non_fcu/rx100/*.ud 
	-rm -rf App/*.asm App/*.p App/*.pp App/*.src App/*.jmp App/*.lst App/*.prn App/*.i App/*.ud 
	-rm -rf r_bsp/mcu/all/*.asm r_bsp/mcu/all/*.p r_bsp/mcu/all/*.pp r_bsp/mcu/all/*.src r_bsp/mcu/all/*.jmp r_bsp/mcu/all/*.lst r_bsp/mcu/all/*.prn r_bsp/mcu/all/*.i r_bsp/mcu/all/*.ud 
	-rm -rf src/cg_src/*.asm src/cg_src/*.p src/cg_src/*.pp src/cg_src/*.src src/cg_src/*.jmp src/cg_src/*.lst src/cg_src/*.prn src/cg_src/*.i src/cg_src/*.ud 
	-rm -rf r_flash_rx/src/*.asm r_flash_rx/src/*.p r_flash_rx/src/*.pp r_flash_rx/src/*.src r_flash_rx/src/*.jmp r_flash_rx/src/*.lst r_flash_rx/src/*.prn r_flash_rx/src/*.i r_flash_rx/src/*.ud 
	-rm -rf r_bsp/board/rskrx64m/*.asm r_bsp/board/rskrx64m/*.p r_bsp/board/rskrx64m/*.pp r_bsp/board/rskrx64m/*.src r_bsp/board/rskrx64m/*.jmp r_bsp/board/rskrx64m/*.lst r_bsp/board/rskrx64m/*.prn r_bsp/board/rskrx64m/*.i r_bsp/board/rskrx64m/*.ud 
	-rm -rf USBStack/MSC/*.asm USBStack/MSC/*.p USBStack/MSC/*.pp USBStack/MSC/*.src USBStack/MSC/*.jmp USBStack/MSC/*.lst USBStack/MSC/*.prn USBStack/MSC/*.i USBStack/MSC/*.ud 
	-rm -rf r_bsp/mcu/rx64m/*.asm r_bsp/mcu/rx64m/*.p r_bsp/mcu/rx64m/*.pp r_bsp/mcu/rx64m/*.src r_bsp/mcu/rx64m/*.jmp r_bsp/mcu/rx64m/*.lst r_bsp/mcu/rx64m/*.prn r_bsp/mcu/rx64m/*.i r_bsp/mcu/rx64m/*.ud 
	-rm -rf r_flash_rx/src/fcu/*.asm r_flash_rx/src/fcu/*.p r_flash_rx/src/fcu/*.pp r_flash_rx/src/fcu/*.src r_flash_rx/src/fcu/*.jmp r_flash_rx/src/fcu/*.lst r_flash_rx/src/fcu/*.prn r_flash_rx/src/fcu/*.i r_flash_rx/src/fcu/*.ud 
	@echo
	@echo 'Clean complete.'

.PHONY: all clean 
-include ../makefile.targets