################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/USBH_midi_class/Src/usbh_MIDI.c 

OBJS += \
./drivers/USBH_midi_class/Src/usbh_MIDI.o 

C_DEPS += \
./drivers/USBH_midi_class/Src/usbh_MIDI.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/USBH_midi_class/Src/%.o drivers/USBH_midi_class/Src/%.su drivers/USBH_midi_class/Src/%.cyclo: ../drivers/USBH_midi_class/Src/%.c drivers/USBH_midi_class/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/BSP" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/cmsis" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/STM32_USB_Host_Library/Core/Inc" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/USBH_midi_class/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers-2f-USBH_midi_class-2f-Src

clean-drivers-2f-USBH_midi_class-2f-Src:
	-$(RM) ./drivers/USBH_midi_class/Src/usbh_MIDI.cyclo ./drivers/USBH_midi_class/Src/usbh_MIDI.d ./drivers/USBH_midi_class/Src/usbh_MIDI.o ./drivers/USBH_midi_class/Src/usbh_MIDI.su

.PHONY: clean-drivers-2f-USBH_midi_class-2f-Src

