################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/UART/UART_Program.c 

OBJS += \
./Src/MCAL/UART/UART_Program.o 

C_DEPS += \
./Src/MCAL/UART/UART_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/UART/%.o Src/MCAL/UART/%.su Src/MCAL/UART/%.cyclo: ../Src/MCAL/UART/%.c Src/MCAL/UART/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/MCAL/GPIO" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/LIB/BIT_MATH" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/LIB/STD_TYPES" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/MCAL/I2C" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/MCAL/RCC" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/HAL/ADS1115" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/HAL/I2C_EEPROM" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-UART

clean-Src-2f-MCAL-2f-UART:
	-$(RM) ./Src/MCAL/UART/UART_Program.cyclo ./Src/MCAL/UART/UART_Program.d ./Src/MCAL/UART/UART_Program.o ./Src/MCAL/UART/UART_Program.su

.PHONY: clean-Src-2f-MCAL-2f-UART

