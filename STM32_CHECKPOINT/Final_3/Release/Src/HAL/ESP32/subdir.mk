################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/ESP32/ESP32_Program.c 

OBJS += \
./Src/HAL/ESP32/ESP32_Program.o 

C_DEPS += \
./Src/HAL/ESP32/ESP32_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/ESP32/%.o Src/HAL/ESP32/%.su Src/HAL/ESP32/%.cyclo: ../Src/HAL/ESP32/%.c Src/HAL/ESP32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-ESP32

clean-Src-2f-HAL-2f-ESP32:
	-$(RM) ./Src/HAL/ESP32/ESP32_Program.cyclo ./Src/HAL/ESP32/ESP32_Program.d ./Src/HAL/ESP32/ESP32_Program.o ./Src/HAL/ESP32/ESP32_Program.su

.PHONY: clean-Src-2f-HAL-2f-ESP32

