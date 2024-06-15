################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/SCB/SCB_Program.c 

OBJS += \
./Src/MCAL/SCB/SCB_Program.o 

C_DEPS += \
./Src/MCAL/SCB/SCB_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/SCB/%.o Src/MCAL/SCB/%.su Src/MCAL/SCB/%.cyclo: ../Src/MCAL/SCB/%.c Src/MCAL/SCB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-SCB

clean-Src-2f-MCAL-2f-SCB:
	-$(RM) ./Src/MCAL/SCB/SCB_Program.cyclo ./Src/MCAL/SCB/SCB_Program.d ./Src/MCAL/SCB/SCB_Program.o ./Src/MCAL/SCB/SCB_Program.su

.PHONY: clean-Src-2f-MCAL-2f-SCB

