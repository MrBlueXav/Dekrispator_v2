################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include drivers/USBH_midi_class/Src/subdir.mk
-include drivers/STM32_USB_Host_Library/Core/Src/subdir.mk
-include drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include drivers/BSP/subdir.mk
-include Synth/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Dekrispator_v2.bin \

SECONDARY_LIST += \
Dekrispator_v2.lst \

SECONDARY_SIZE += \
Dekrispator_v2.siz \


# All Target
all: Dekrispator_v2.elf secondary-outputs

# Tool invocations
Dekrispator_v2.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O3 -ffunction-sections -fdata-sections -fsingle-precision-constant -flto -Wunused -Wuninitialized -Wall -Wconversion -Wshadow -Wfloat-equal -T "../STM32F407VG_FLASH.ld" -Xlinker --gc-sections -Wl,-Map,"Dekrispator_v2.map" --specs=nosys.specs -o "Dekrispator_v2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Dekrispator_v2.bin: Dekrispator_v2.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary "Dekrispator_v2.elf"  "Dekrispator_v2.bin"
	@echo 'Finished building: $@'
	@echo ' '

Dekrispator_v2.lst: Dekrispator_v2.elf
	@echo 'Invoking: Cross ARM GNU Create Listing'
	arm-none-eabi-objdump --source --all-headers --demangle --line-numbers --wide "Dekrispator_v2.elf" > "Dekrispator_v2.lst"
	@echo 'Finished building: $@'
	@echo ' '

Dekrispator_v2.siz: Dekrispator_v2.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley --totals "Dekrispator_v2.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) Dekrispator_v2.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
