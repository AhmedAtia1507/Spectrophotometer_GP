################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/ADC/ADC_Program.c 

OBJS += \
./Src/MCAL/ADC/ADC_Program.o 

C_DEPS += \
./Src/MCAL/ADC/ADC_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/ADC/%.o Src/MCAL/ADC/%.su Src/MCAL/ADC/%.cyclo: ../Src/MCAL/ADC/%.c Src/MCAL/ADC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-ADC

clean-Src-2f-MCAL-2f-ADC:
	-$(RM) ./Src/MCAL/ADC/ADC_Program.cyclo ./Src/MCAL/ADC/ADC_Program.d ./Src/MCAL/ADC/ADC_Program.o ./Src/MCAL/ADC/ADC_Program.su

.PHONY: clean-Src-2f-MCAL-2f-ADC

