################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/RCC/RCC_Program.c 

OBJS += \
./Src/MCAL/RCC/RCC_Program.o 

C_DEPS += \
./Src/MCAL/RCC/RCC_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/RCC/RCC_Program.o: ../Src/MCAL/RCC/RCC_Program.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/MCAL/RCC/RCC_Program.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

