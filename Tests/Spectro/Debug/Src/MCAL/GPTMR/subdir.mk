################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/GPTMR/GPTMR_Program.c 

OBJS += \
./Src/MCAL/GPTMR/GPTMR_Program.o 

C_DEPS += \
./Src/MCAL/GPTMR/GPTMR_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/GPTMR/%.o Src/MCAL/GPTMR/%.su Src/MCAL/GPTMR/%.cyclo: ../Src/MCAL/GPTMR/%.c Src/MCAL/GPTMR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-GPTMR

clean-Src-2f-MCAL-2f-GPTMR:
	-$(RM) ./Src/MCAL/GPTMR/GPTMR_Program.cyclo ./Src/MCAL/GPTMR/GPTMR_Program.d ./Src/MCAL/GPTMR/GPTMR_Program.o ./Src/MCAL/GPTMR/GPTMR_Program.su

.PHONY: clean-Src-2f-MCAL-2f-GPTMR

