################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/ADS1115/ADS1115.c 

OBJS += \
./Src/HAL/ADS1115/ADS1115.o 

C_DEPS += \
./Src/HAL/ADS1115/ADS1115.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/ADS1115/%.o Src/HAL/ADS1115/%.su Src/HAL/ADS1115/%.cyclo: ../Src/HAL/ADS1115/%.c Src/HAL/ADS1115/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/MCAL/GPIO" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/LIB/BIT_MATH" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/LIB/STD_TYPES" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/MCAL/I2C" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/MCAL/RCC" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/HAL/ADS1115" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/HAL/I2C_EEPROM" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-ADS1115

clean-Src-2f-HAL-2f-ADS1115:
	-$(RM) ./Src/HAL/ADS1115/ADS1115.cyclo ./Src/HAL/ADS1115/ADS1115.d ./Src/HAL/ADS1115/ADS1115.o ./Src/HAL/ADS1115/ADS1115.su

.PHONY: clean-Src-2f-HAL-2f-ADS1115

