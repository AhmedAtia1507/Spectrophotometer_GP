################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/MCP4151/MCP4151.c 

OBJS += \
./Src/HAL/MCP4151/MCP4151.o 

C_DEPS += \
./Src/HAL/MCP4151/MCP4151.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/MCP4151/%.o Src/HAL/MCP4151/%.su Src/HAL/MCP4151/%.cyclo: ../Src/HAL/MCP4151/%.c Src/HAL/MCP4151/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-MCP4151

clean-Src-2f-HAL-2f-MCP4151:
	-$(RM) ./Src/HAL/MCP4151/MCP4151.cyclo ./Src/HAL/MCP4151/MCP4151.d ./Src/HAL/MCP4151/MCP4151.o ./Src/HAL/MCP4151/MCP4151.su

.PHONY: clean-Src-2f-HAL-2f-MCP4151

