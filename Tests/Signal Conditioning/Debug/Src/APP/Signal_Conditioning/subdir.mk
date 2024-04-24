################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
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
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/APP" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/HAL" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/LIB" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/MCAL/GPIO" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/MCAL/I2C" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/MCAL/NVIC" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/MCAL/RCC" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/MCAL/SPI" -I"D:/ASU ENG/GP_Spectrophotometer/Final tests/Signal Conditioning/Src/MCAL/SYSTICK" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-APP-2f-Signal_Conditioning

clean-Src-2f-APP-2f-Signal_Conditioning:
	-$(RM) ./Src/APP/Signal_Conditioning/signal_conditioning.cyclo ./Src/APP/Signal_Conditioning/signal_conditioning.d ./Src/APP/Signal_Conditioning/signal_conditioning.o ./Src/APP/Signal_Conditioning/signal_conditioning.su

.PHONY: clean-Src-2f-APP-2f-Signal_Conditioning

