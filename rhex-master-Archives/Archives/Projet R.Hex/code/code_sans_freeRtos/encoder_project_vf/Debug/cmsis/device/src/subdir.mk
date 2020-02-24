################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cmsis/device/src/system_stm32f4xx.c 

S_UPPER_SRCS += \
../cmsis/device/src/startup_stm32f429xx.S 

OBJS += \
./cmsis/device/src/startup_stm32f429xx.o \
./cmsis/device/src/system_stm32f4xx.o 

S_UPPER_DEPS += \
./cmsis/device/src/startup_stm32f429xx.d 

C_DEPS += \
./cmsis/device/src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
cmsis/device/src/%.o: ../cmsis/device/src/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F429xx -DUSE_STDPERIPH_DRIVER -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/encoder_lib/inc" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/Control_Leg/inc" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/Control_Leg/src" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/app/inc" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/cmsis/device/inc" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/cmsis/core" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/bsp/inc" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/app/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cmsis/device/src/%.o: ../cmsis/device/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F429xx -DUSE_STDPERIPH_DRIVER -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/encoder_lib/inc" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/Control_Leg/inc" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/Control_Leg/src" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/app/inc" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/cmsis/device/inc" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/cmsis/core" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/bsp/inc" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/app/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


