################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/Senior_2/Graduation_Project/GRADUATION_PROJECT_REPO/Spectrophotometer_GP/Tests/Signal Conditioning/Src/APP" -I"D:/Senior_2/Graduation_Project/GRADUATION_PROJECT_REPO/Spectrophotometer_GP/Tests/Signal Conditioning/Src/HAL" -I"D:/Senior_2/Graduation_Project/GRADUATION_PROJECT_REPO/Spectrophotometer_GP/Tests/Signal Conditioning/Src/LIB" -I"D:/Senior_2/Graduation_Project/GRADUATION_PROJECT_REPO/Spectrophotometer_GP/Tests/Signal Conditioning/Src/MCAL/GPIO" -I"D:/Senior_2/Graduation_Project/GRADUATION_PROJECT_REPO/Spectrophotometer_GP/Tests/Signal Conditioning/Src/MCAL/I2C" -I"D:/Senior_2/Graduation_Project/GRADUATION_PROJECT_REPO/Spectrophotometer_GP/Tests/Signal Conditioning/Src/MCAL/NVIC" -I"D:/Senior_2/Graduation_Project/GRADUATION_PROJECT_REPO/Spectrophotometer_GP/Tests/Signal Conditioning/Src/MCAL/RCC" -I"D:/Senior_2/Graduation_Project/GRADUATION_PROJECT_REPO/Spectrophotometer_GP/Tests/Signal Conditioning/Src/MCAL/SPI" -I"D:/Senior_2/Graduation_Project/GRADUATION_PROJECT_REPO/Spectrophotometer_GP/Tests/Signal Conditioning/Src/MCAL/SYSTICK" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

