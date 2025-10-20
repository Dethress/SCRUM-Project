################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USB_HOST/Target/subdir.mk
-include USB_HOST/App/subdir.mk
-include Middlewares/ST/STM32_USB_Host_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Src/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/Legacy/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/STM3210C_EVAL/subdir.mk
-include Drivers/BSP/Components/stmpe811/subdir.mk
-include Drivers/BSP/Components/stlm75/subdir.mk
-include Drivers/BSP/Components/st7735/subdir.mk
-include Drivers/BSP/Components/spfd5408/subdir.mk
-include Drivers/BSP/Components/lis302dl/subdir.mk
-include Drivers/BSP/Components/ili9325/subdir.mk
-include Drivers/BSP/Components/ili9320/subdir.mk
-include Drivers/BSP/Components/hx8347d/subdir.mk
-include Drivers/BSP/Components/cs43l22/subdir.mk
-include Drivers/BSP/Components/ak4343/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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


BUILD_ARTIFACT_NAME := Pac-Man
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Pac-Man.elf \

MAP_FILES += \
Pac-Man.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Pac-Man.list \


# All Target
all: main-build

# Main-build Target
main-build: Pac-Man.elf secondary-outputs

# Tool invocations
Pac-Man.elf Pac-Man.map: $(OBJS) $(USER_OBJS) C:\Users\micha\Desktop\embeded\Pac-Man\STM32F107VCTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Pac-Man.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\micha\Desktop\embeded\Pac-Man\STM32F107VCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Pac-Man.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Pac-Man.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Pac-Man.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Pac-Man.elf Pac-Man.list Pac-Man.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
