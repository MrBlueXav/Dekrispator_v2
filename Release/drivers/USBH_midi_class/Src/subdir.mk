################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/USBH_midi_class/Src/usbh_MIDI.c 

OBJS += \
./drivers/USBH_midi_class/Src/usbh_MIDI.o 

C_DEPS += \
./drivers/USBH_midi_class/Src/usbh_MIDI.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/USBH_midi_class/Src/%.o: ../drivers/USBH_midi_class/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O3 -ffunction-sections -fdata-sections -fsingle-precision-constant -flto -Wunused -Wuninitialized -Wall -Wconversion -Wshadow -Wfloat-equal -D__FPU_USED=1 -DHSE_VALUE=8000000 -DUSE_HAL_DRIVER -DUSE_STM32F4_DISCO -DSTM32F407xx -I.././drivers/STM32_USB_Host_Library/Core/Inc -I../drivers/BSP -I../drivers/cmsis -I../drivers/STM32F4xx_HAL_Driver/Inc -I../Synth -I../drivers/USBH_midi_class/Inc -std=c11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


