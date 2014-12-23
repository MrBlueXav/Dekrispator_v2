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
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fsingle-precision-constant -Wall -DSTM32F40_41xxx -D__FPU_USED=1 -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DSTM32F407VG -DUSE_HAL_DRIVER -DSTM32F407XX -DUSE_STM32F4_DISCO -DSTM32F407xx -I../Synth -I../USB -I../USB/MIDIstream_class -I../Lib/STM32F4xx_StdPeriph_Driver/inc -I../Lib/STM32_USB_OTG_Driver/inc -I../Lib/STM32_USB_HOST_Library/Core/inc -I../System -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\STM32_USB_Host_Library\Core\Inc" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\BSP" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\cmsis" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\STM32F4xx_HAL_Driver\Inc" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\USBH_midi_class\Inc" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\Synth" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


