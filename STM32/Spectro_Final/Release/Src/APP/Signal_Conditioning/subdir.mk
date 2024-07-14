################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/APP/Signal_Conditioning/signal_conditioning.c 

OBJS += \
./Src/APP/Signal_Conditioning/signal_conditioning.o 

C_DEPS += \
./Src/APP/Signal_Conditioning/signal_conditioning.d 


# Each subdirectory must supply rules for building sources it contributes
Src/APP/Signal_Conditioning/%.o Src/APP/Signal_Conditioning/%.su Src/APP/Signal_Conditioning/%.cyclo: ../Src/APP/Signal_Conditioning/%.c Src/APP/Signal_Conditioning/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-APP-2f-Signal_Conditioning

clean-Src-2f-APP-2f-Signal_Conditioning:
	-$(RM) ./Src/APP/Signal_Conditioning/signal_conditioning.cyclo ./Src/APP/Signal_Conditioning/signal_conditioning.d ./Src/APP/Signal_Conditioning/signal_conditioning.o ./Src/APP/Signal_Conditioning/signal_conditioning.su

.PHONY: clean-Src-2f-APP-2f-Signal_Conditioning

