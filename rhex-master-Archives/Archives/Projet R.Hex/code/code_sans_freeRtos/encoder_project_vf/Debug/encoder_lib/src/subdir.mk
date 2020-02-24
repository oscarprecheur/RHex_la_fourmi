################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../encoder_lib/src/can_fct.c \
../encoder_lib/src/encoder_fct.c \
../encoder_lib/src/stm32f4xx_can.c \
../encoder_lib/src/stm32f4xx_gpio.c 

OBJS += \
./encoder_lib/src/can_fct.o \
./encoder_lib/src/encoder_fct.o \
./encoder_lib/src/stm32f4xx_can.o \
./encoder_lib/src/stm32f4xx_gpio.o 

C_DEPS += \
./encoder_lib/src/can_fct.d \
./encoder_lib/src/encoder_fct.d \
./encoder_lib/src/stm32f4xx_can.d \
./encoder_lib/src/stm32f4xx_gpio.d 


# Each subdirectory must supply rules for building sources it contributes
encoder_lib/src/%.o: ../encoder_lib/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F429xx -DUSE_STDPERIPH_DRIVER -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/encoder_lib/inc" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/Control_Leg/inc" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/Control_Leg/src" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/app/inc" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/cmsis/device/inc" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/cmsis/core" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/bsp/inc" -I"C:/Users/PIFE/Documents/le renouveau - Can2/encoder_project_vf/app/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


