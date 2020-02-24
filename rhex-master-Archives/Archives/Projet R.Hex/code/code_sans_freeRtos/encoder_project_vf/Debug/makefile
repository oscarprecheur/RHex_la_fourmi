################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include encoder_lib/src/subdir.mk
-include cmsis/device/src/subdir.mk
-include bsp/src/subdir.mk
-include app/src/subdir.mk
-include Control_Leg/src/subdir.mk
-include .metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: encoder_project_vf.elf

# Tool invocations
encoder_project_vf.elf: $(OBJS) $(USER_OBJS) C:\Users\PIFE\Documents\le\ renouveau\ -\ Can2\encoder_project_vf\LinkerScript.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -T"C:\Users\PIFE\Documents\le renouveau - Can2\encoder_project_vf\LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "encoder_project_vf.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "encoder_project_vf.elf" "encoder_project_vf.bin"
	arm-none-eabi-size "encoder_project_vf.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
