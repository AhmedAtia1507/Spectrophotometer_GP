################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/I2C_EEPROM/I2C_Slave_EEPROM.c 

OBJS += \
./Src/HAL/I2C_EEPROM/I2C_Slave_EEPROM.o 

C_DEPS += \
./Src/HAL/I2C_EEPROM/I2C_Slave_EEPROM.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/I2C_EEPROM/%.o Src/HAL/I2C_EEPROM/%.su Src/HAL/I2C_EEPROM/%.cyclo: ../Src/HAL/I2C_EEPROM/%.c Src/HAL/I2C_EEPROM/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-I2C_EEPROM

clean-Src-2f-HAL-2f-I2C_EEPROM:
	-$(RM) ./Src/HAL/I2C_EEPROM/I2C_Slave_EEPROM.cyclo ./Src/HAL/I2C_EEPROM/I2C_Slave_EEPROM.d ./Src/HAL/I2C_EEPROM/I2C_Slave_EEPROM.o ./Src/HAL/I2C_EEPROM/I2C_Slave_EEPROM.su

.PHONY: clean-Src-2f-HAL-2f-I2C_EEPROM

