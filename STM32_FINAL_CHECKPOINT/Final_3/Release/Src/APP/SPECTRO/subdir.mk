################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/APP/SPECTRO/SPECTRO_Program.c 

OBJS += \
./Src/APP/SPECTRO/SPECTRO_Program.o 

C_DEPS += \
./Src/APP/SPECTRO/SPECTRO_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/APP/SPECTRO/%.o Src/APP/SPECTRO/%.su Src/APP/SPECTRO/%.cyclo: ../Src/APP/SPECTRO/%.c Src/APP/SPECTRO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-APP-2f-SPECTRO

clean-Src-2f-APP-2f-SPECTRO:
	-$(RM) ./Src/APP/SPECTRO/SPECTRO_Program.cyclo ./Src/APP/SPECTRO/SPECTRO_Program.d ./Src/APP/SPECTRO/SPECTRO_Program.o ./Src/APP/SPECTRO/SPECTRO_Program.su

.PHONY: clean-Src-2f-APP-2f-SPECTRO

