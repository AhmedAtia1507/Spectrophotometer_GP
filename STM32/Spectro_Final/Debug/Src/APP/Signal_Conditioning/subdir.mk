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
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/APP/SCommands" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/APP/Signal_Conditioning" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/APP/SPECTRO" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/APP/SpectroStatus" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/HAL/ADS1115" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/HAL/EEPROM" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/HAL/ESP32" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/HAL/LCD" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/HAL/MCP4151" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/HAL/PWRSupply" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/HAL/SPWRVolt" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/HAL/STEPPER_MOTOR" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/LIB/BIT_MATH" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/LIB/STD_TYPES" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/MCAL/ADC" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/MCAL/AFIO" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/MCAL/EXTI" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/MCAL/GI" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/MCAL/GPIO" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/MCAL/GPTMR" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/MCAL/I2C" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/MCAL/NVIC" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/MCAL/RCC" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/MCAL/RTC" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/MCAL/SCB" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/MCAL/SPI" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/MCAL/STK" -I"C:/Users/Ahmed/Downloads/Final_3/Spectro_Final/Src/MCAL/UART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-APP-2f-Signal_Conditioning

clean-Src-2f-APP-2f-Signal_Conditioning:
	-$(RM) ./Src/APP/Signal_Conditioning/signal_conditioning.cyclo ./Src/APP/Signal_Conditioning/signal_conditioning.d ./Src/APP/Signal_Conditioning/signal_conditioning.o ./Src/APP/Signal_Conditioning/signal_conditioning.su

.PHONY: clean-Src-2f-APP-2f-Signal_Conditioning

