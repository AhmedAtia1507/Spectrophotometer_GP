################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/GPIO/GPIO_Program.c 

OBJS += \
./Src/MCAL/GPIO/GPIO_Program.o 

C_DEPS += \
./Src/MCAL/GPIO/GPIO_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/GPIO/%.o Src/MCAL/GPIO/%.su Src/MCAL/GPIO/%.cyclo: ../Src/MCAL/GPIO/%.c Src/MCAL/GPIO/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/ASU ENG/GP_Spectrophotometer/Drivers/MCP4151/Src/LIB/BIT_MATH" -I"D:/ASU ENG/GP_Spectrophotometer/Drivers/MCP4151/Src/LIB/STD_TYPES" -I"D:/ASU ENG/GP_Spectrophotometer/Drivers/MCP4151/Src/MCAL/GPIO" -I"D:/ASU ENG/GP_Spectrophotometer/Drivers/MCP4151/Src/MCAL/RCC" -I"D:/ASU ENG/GP_Spectrophotometer/Drivers/MCP4151/Src/MCAL/SPI" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-GPIO

clean-Src-2f-MCAL-2f-GPIO:
	-$(RM) ./Src/MCAL/GPIO/GPIO_Program.cyclo ./Src/MCAL/GPIO/GPIO_Program.d ./Src/MCAL/GPIO/GPIO_Program.o ./Src/MCAL/GPIO/GPIO_Program.su

.PHONY: clean-Src-2f-MCAL-2f-GPIO
