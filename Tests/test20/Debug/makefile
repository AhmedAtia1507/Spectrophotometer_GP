################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
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
-include Src/HAL/I2C_EEPROM/subdir.mk
-include Src/HAL/ADS1115/subdir.mk
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


BUILD_ARTIFACT_NAME := test20
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
test20.elf \

MAP_FILES += \
test20.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
test20.list \


# All Target
all: main-build

# Main-build Target
main-build: test20.elf secondary-outputs

# Tool invocations
test20.elf test20.map: $(OBJS) $(USER_OBJS) D:\ASU\ ENG\GP_Spectrophotometer\ADC\test20\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -gdwarf-2 -o "test20.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\ASU ENG\GP_Spectrophotometer\ADC\test20\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="test20.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

test20.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "test20.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout test20.elf test20.list test20.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
