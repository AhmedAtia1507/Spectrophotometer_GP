################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/ADS1115/ADC.c 

OBJS += \
./Src/HAL/ADS1115/ADC.o 

C_DEPS += \
./Src/HAL/ADS1115/ADC.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/ADS1115/%.o Src/HAL/ADS1115/%.su Src/HAL/ADS1115/%.cyclo: ../Src/HAL/ADS1115/%.c Src/HAL/ADS1115/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-ADS1115

clean-Src-2f-HAL-2f-ADS1115:
	-$(RM) ./Src/HAL/ADS1115/ADC.cyclo ./Src/HAL/ADS1115/ADC.d ./Src/HAL/ADS1115/ADC.o ./Src/HAL/ADS1115/ADC.su

.PHONY: clean-Src-2f-HAL-2f-ADS1115

