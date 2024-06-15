################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/MCAL/UART/subdir.mk
-include Src/MCAL/STK/subdir.mk
-include Src/MCAL/SPI/subdir.mk
-include Src/MCAL/SCB/subdir.mk
-include Src/MCAL/RTC/subdir.mk
-include Src/MCAL/RCC/subdir.mk
-include Src/MCAL/NVIC/subdir.mk
-include Src/MCAL/I2C/subdir.mk
-include Src/MCAL/GPTMR/subdir.mk
-include Src/MCAL/GPIO/subdir.mk
-include Src/MCAL/GI/subdir.mk
-include Src/MCAL/EXTI/subdir.mk
-include Src/MCAL/AFIO/subdir.mk
-include Src/MCAL/ADC/subdir.mk
-include Src/HAL/STEPPER_MOTOR/subdir.mk
-include Src/HAL/SPWRVolt/subdir.mk
-include Src/HAL/PWRSupply/subdir.mk
-include Src/HAL/MCP4151/subdir.mk
-include Src/HAL/LCD/subdir.mk
-include Src/HAL/ESP32/subdir.mk
-include Src/HAL/EEPROM/subdir.mk
-include Src/HAL/ADS1115/subdir.mk
-include Src/APP/SpectroStatus/subdir.mk
-include Src/APP/Signal_Conditioning/subdir.mk
-include Src/APP/SPECTRO/subdir.mk
-include Src/APP/SCommands/subdir.mk
-include Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Final_3
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Final_3.elf \

MAP_FILES += \
Final_3.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Final_3.list \


# All Target
all: main-build

# Main-build Target
main-build: Final_3.elf secondary-outputs

# Tool invocations
Final_3.elf Final_3.map: $(OBJS) $(USER_OBJS) C:\Users\Ahmed\Downloads\Final_3\Final_3\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -gdwarf-2 -o "Final_3.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\Ahmed\Downloads\Final_3\Final_3\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Final_3.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Final_3.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Final_3.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Final_3.elf Final_3.list Final_3.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
