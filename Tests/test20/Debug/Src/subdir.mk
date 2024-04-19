################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/MCAL/GPIO" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/LIB/BIT_MATH" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/LIB/STD_TYPES" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/MCAL/I2C" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/MCAL/RCC" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/HAL/ADS1115" -I"D:/ASU ENG/GP_Spectrophotometer/ADC/test20/Src/HAL/I2C_EEPROM" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

