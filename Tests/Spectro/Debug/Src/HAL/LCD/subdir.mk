################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/LCD/LCD_Program.c 

OBJS += \
./Src/HAL/LCD/LCD_Program.o 

C_DEPS += \
./Src/HAL/LCD/LCD_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/LCD/%.o Src/HAL/LCD/%.su Src/HAL/LCD/%.cyclo: ../Src/HAL/LCD/%.c Src/HAL/LCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-LCD

clean-Src-2f-HAL-2f-LCD:
	-$(RM) ./Src/HAL/LCD/LCD_Program.cyclo ./Src/HAL/LCD/LCD_Program.d ./Src/HAL/LCD/LCD_Program.o ./Src/HAL/LCD/LCD_Program.su

.PHONY: clean-Src-2f-HAL-2f-LCD

