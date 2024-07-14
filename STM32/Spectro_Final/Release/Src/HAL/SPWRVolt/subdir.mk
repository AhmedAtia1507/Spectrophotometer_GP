################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/SPWRVolt/SPWRVolt_Program.c 

OBJS += \
./Src/HAL/SPWRVolt/SPWRVolt_Program.o 

C_DEPS += \
./Src/HAL/SPWRVolt/SPWRVolt_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/SPWRVolt/%.o Src/HAL/SPWRVolt/%.su Src/HAL/SPWRVolt/%.cyclo: ../Src/HAL/SPWRVolt/%.c Src/HAL/SPWRVolt/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-SPWRVolt

clean-Src-2f-HAL-2f-SPWRVolt:
	-$(RM) ./Src/HAL/SPWRVolt/SPWRVolt_Program.cyclo ./Src/HAL/SPWRVolt/SPWRVolt_Program.d ./Src/HAL/SPWRVolt/SPWRVolt_Program.o ./Src/HAL/SPWRVolt/SPWRVolt_Program.su

.PHONY: clean-Src-2f-HAL-2f-SPWRVolt

