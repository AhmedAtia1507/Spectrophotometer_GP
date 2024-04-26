################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/ADC.c \
../Src/HAL/MCP4151.c 

OBJS += \
./Src/HAL/ADC.o \
./Src/HAL/MCP4151.o 

C_DEPS += \
./Src/HAL/ADC.d \
./Src/HAL/MCP4151.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/%.o Src/HAL/%.su Src/HAL/%.cyclo: ../Src/HAL/%.c Src/HAL/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/APP" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/HAL" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/LIB" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/MCAL/GPIO" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/MCAL/I2C" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/MCAL/NVIC" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/MCAL/RCC" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/MCAL/SPI" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/MCAL/SYSTICK" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL

clean-Src-2f-HAL:
	-$(RM) ./Src/HAL/ADC.cyclo ./Src/HAL/ADC.d ./Src/HAL/ADC.o ./Src/HAL/ADC.su ./Src/HAL/MCP4151.cyclo ./Src/HAL/MCP4151.d ./Src/HAL/MCP4151.o ./Src/HAL/MCP4151.su

.PHONY: clean-Src-2f-HAL

