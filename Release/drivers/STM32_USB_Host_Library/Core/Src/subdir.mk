################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
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
drivers/STM32_USB_Host_Library/Core/Src/%.o drivers/STM32_USB_Host_Library/Core/Src/%.su drivers/STM32_USB_Host_Library/Core/Src/%.cyclo: ../drivers/STM32_USB_Host_Library/Core/Src/%.c drivers/STM32_USB_Host_Library/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F407xx -DUSE_HAL_DRIVER -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/BSP" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/cmsis" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/STM32_USB_Host_Library/Core/Inc" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/USBH_midi_class/Inc" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers-2f-STM32_USB_Host_Library-2f-Core-2f-Src

clean-drivers-2f-STM32_USB_Host_Library-2f-Core-2f-Src:
	-$(RM) ./drivers/STM32_USB_Host_Library/Core/Src/usbh_core.cyclo ./drivers/STM32_USB_Host_Library/Core/Src/usbh_core.d ./drivers/STM32_USB_Host_Library/Core/Src/usbh_core.o ./drivers/STM32_USB_Host_Library/Core/Src/usbh_core.su ./drivers/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.cyclo ./drivers/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.d ./drivers/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.o ./drivers/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.su ./drivers/STM32_USB_Host_Library/Core/Src/usbh_ioreq.cyclo ./drivers/STM32_USB_Host_Library/Core/Src/usbh_ioreq.d ./drivers/STM32_USB_Host_Library/Core/Src/usbh_ioreq.o ./drivers/STM32_USB_Host_Library/Core/Src/usbh_ioreq.su ./drivers/STM32_USB_Host_Library/Core/Src/usbh_pipes.cyclo ./drivers/STM32_USB_Host_Library/Core/Src/usbh_pipes.d ./drivers/STM32_USB_Host_Library/Core/Src/usbh_pipes.o ./drivers/STM32_USB_Host_Library/Core/Src/usbh_pipes.su

.PHONY: clean-drivers-2f-STM32_USB_Host_Library-2f-Core-2f-Src

