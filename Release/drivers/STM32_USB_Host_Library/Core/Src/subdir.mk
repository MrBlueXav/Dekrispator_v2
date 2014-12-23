################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/STM32_USB_Host_Library/Core/Src/usbh_core.c \
../drivers/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c \
../drivers/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c \
../drivers/STM32_USB_Host_Library/Core/Src/usbh_pipes.c 

OBJS += \
./drivers/STM32_USB_Host_Library/Core/Src/usbh_core.o \
./drivers/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.o \
./drivers/STM32_USB_Host_Library/Core/Src/usbh_ioreq.o \
./drivers/STM32_USB_Host_Library/Core/Src/usbh_pipes.o 

C_DEPS += \
./drivers/STM32_USB_Host_Library/Core/Src/usbh_core.d \
./drivers/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.d \
./drivers/STM32_USB_Host_Library/Core/Src/usbh_ioreq.d \
./drivers/STM32_USB_Host_Library/Core/Src/usbh_pipes.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/STM32_USB_Host_Library/Core/Src/%.o: ../drivers/STM32_USB_Host_Library/Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fsingle-precision-constant -Wall -DSTM32F40_41xxx -D__FPU_USED=1 -DHSE_VALUE=8000000 -DSTM32F407VG -DUSE_HAL_DRIVER -DUSE_STM32F4_DISCO -DSTM32F407xx -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\STM32_USB_Host_Library\Core\Inc" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\BSP" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\cmsis" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\STM32F4xx_HAL_Driver\Inc" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\USBH_midi_class\Inc" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\Synth" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


