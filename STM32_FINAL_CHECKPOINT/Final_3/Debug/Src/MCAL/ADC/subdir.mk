################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
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
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/APP/SCommands" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/APP/Signal_Conditioning" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/APP/SPECTRO" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/APP/SpectroStatus" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/HAL/ADS1115" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/HAL/EEPROM" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/HAL/ESP32" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/HAL/LCD" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/HAL/MCP4151" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/HAL/PWRSupply" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/HAL/SPWRVolt" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/HAL/STEPPER_MOTOR" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/LIB/BIT_MATH" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/LIB/STD_TYPES" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/MCAL/ADC" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/MCAL/AFIO" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/MCAL/EXTI" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/MCAL/GI" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/MCAL/GPIO" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/MCAL/GPTMR" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/MCAL/I2C" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/MCAL/NVIC" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/MCAL/RCC" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/MCAL/RTC" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/MCAL/SCB" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/MCAL/SPI" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/MCAL/STK" -I"C:/Users/Ahmed/Downloads/Final_3/Final_3/Src/MCAL/UART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-ADC

clean-Src-2f-MCAL-2f-ADC:
	-$(RM) ./Src/MCAL/ADC/ADC_Program.cyclo ./Src/MCAL/ADC/ADC_Program.d ./Src/MCAL/ADC/ADC_Program.o ./Src/MCAL/ADC/ADC_Program.su

.PHONY: clean-Src-2f-MCAL-2f-ADC

