################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/PWRSupply/HPWRSupply_Program.c 

OBJS += \
./Src/HAL/PWRSupply/HPWRSupply_Program.o 

C_DEPS += \
./Src/HAL/PWRSupply/HPWRSupply_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/PWRSupply/%.o Src/HAL/PWRSupply/%.su Src/HAL/PWRSupply/%.cyclo: ../Src/HAL/PWRSupply/%.c Src/HAL/PWRSupply/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-PWRSupply

clean-Src-2f-HAL-2f-PWRSupply:
	-$(RM) ./Src/HAL/PWRSupply/HPWRSupply_Program.cyclo ./Src/HAL/PWRSupply/HPWRSupply_Program.d ./Src/HAL/PWRSupply/HPWRSupply_Program.o ./Src/HAL/PWRSupply/HPWRSupply_Program.su

.PHONY: clean-Src-2f-HAL-2f-PWRSupply

