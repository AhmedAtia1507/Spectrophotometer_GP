################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/KEYPAD/KEYPAD_prg.c 

OBJS += \
./Src/HAL/KEYPAD/KEYPAD_prg.o 

C_DEPS += \
./Src/HAL/KEYPAD/KEYPAD_prg.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/KEYPAD/%.o Src/HAL/KEYPAD/%.su Src/HAL/KEYPAD/%.cyclo: ../Src/HAL/KEYPAD/%.c Src/HAL/KEYPAD/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-KEYPAD

clean-Src-2f-HAL-2f-KEYPAD:
	-$(RM) ./Src/HAL/KEYPAD/KEYPAD_prg.cyclo ./Src/HAL/KEYPAD/KEYPAD_prg.d ./Src/HAL/KEYPAD/KEYPAD_prg.o ./Src/HAL/KEYPAD/KEYPAD_prg.su

.PHONY: clean-Src-2f-HAL-2f-KEYPAD

