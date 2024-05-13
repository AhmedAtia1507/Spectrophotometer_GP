################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/APP/SpectroStatus/SpectroStatus_Program.c 

OBJS += \
./Src/APP/SpectroStatus/SpectroStatus_Program.o 

C_DEPS += \
./Src/APP/SpectroStatus/SpectroStatus_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/APP/SpectroStatus/%.o Src/APP/SpectroStatus/%.su Src/APP/SpectroStatus/%.cyclo: ../Src/APP/SpectroStatus/%.c Src/APP/SpectroStatus/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-APP-2f-SpectroStatus

clean-Src-2f-APP-2f-SpectroStatus:
	-$(RM) ./Src/APP/SpectroStatus/SpectroStatus_Program.cyclo ./Src/APP/SpectroStatus/SpectroStatus_Program.d ./Src/APP/SpectroStatus/SpectroStatus_Program.o ./Src/APP/SpectroStatus/SpectroStatus_Program.su

.PHONY: clean-Src-2f-APP-2f-SpectroStatus

