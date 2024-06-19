################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/EEPROM/I2C_Slave_EEPROM.c 

OBJS += \
./Src/HAL/EEPROM/I2C_Slave_EEPROM.o 

C_DEPS += \
./Src/HAL/EEPROM/I2C_Slave_EEPROM.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/EEPROM/%.o Src/HAL/EEPROM/%.su Src/HAL/EEPROM/%.cyclo: ../Src/HAL/EEPROM/%.c Src/HAL/EEPROM/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-EEPROM

clean-Src-2f-HAL-2f-EEPROM:
	-$(RM) ./Src/HAL/EEPROM/I2C_Slave_EEPROM.cyclo ./Src/HAL/EEPROM/I2C_Slave_EEPROM.d ./Src/HAL/EEPROM/I2C_Slave_EEPROM.o ./Src/HAL/EEPROM/I2C_Slave_EEPROM.su

.PHONY: clean-Src-2f-HAL-2f-EEPROM

