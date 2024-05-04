################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/I2C/I2C_Program.c 

OBJS += \
./Src/MCAL/I2C/I2C_Program.o 

C_DEPS += \
./Src/MCAL/I2C/I2C_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/I2C/%.o Src/MCAL/I2C/%.su Src/MCAL/I2C/%.cyclo: ../Src/MCAL/I2C/%.c Src/MCAL/I2C/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-I2C

clean-Src-2f-MCAL-2f-I2C:
	-$(RM) ./Src/MCAL/I2C/I2C_Program.cyclo ./Src/MCAL/I2C/I2C_Program.d ./Src/MCAL/I2C/I2C_Program.o ./Src/MCAL/I2C/I2C_Program.su

.PHONY: clean-Src-2f-MCAL-2f-I2C

