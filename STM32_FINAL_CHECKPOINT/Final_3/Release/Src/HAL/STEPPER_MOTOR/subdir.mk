################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/STEPPER_MOTOR/MOTORS_Program.c 

OBJS += \
./Src/HAL/STEPPER_MOTOR/MOTORS_Program.o 

C_DEPS += \
./Src/HAL/STEPPER_MOTOR/MOTORS_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/STEPPER_MOTOR/%.o Src/HAL/STEPPER_MOTOR/%.su Src/HAL/STEPPER_MOTOR/%.cyclo: ../Src/HAL/STEPPER_MOTOR/%.c Src/HAL/STEPPER_MOTOR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-STEPPER_MOTOR

clean-Src-2f-HAL-2f-STEPPER_MOTOR:
	-$(RM) ./Src/HAL/STEPPER_MOTOR/MOTORS_Program.cyclo ./Src/HAL/STEPPER_MOTOR/MOTORS_Program.d ./Src/HAL/STEPPER_MOTOR/MOTORS_Program.o ./Src/HAL/STEPPER_MOTOR/MOTORS_Program.su

.PHONY: clean-Src-2f-HAL-2f-STEPPER_MOTOR

