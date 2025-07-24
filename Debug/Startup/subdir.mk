################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Startup/startup_stm32f407xx.S 

OBJS += \
./Startup/startup_stm32f407xx.o 

S_UPPER_DEPS += \
./Startup/startup_stm32f407xx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.S Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/BSP" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/cmsis" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/STM32_USB_Host_Library/Core/Inc" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/USBH_midi_class/Inc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32f407xx.d ./Startup/startup_stm32f407xx.o

.PHONY: clean-Startup

