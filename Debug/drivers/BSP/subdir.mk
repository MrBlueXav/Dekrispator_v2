################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/BSP/cs43l22.c \
../drivers/BSP/lis302dl.c \
../drivers/BSP/lis3dsh.c \
../drivers/BSP/stm32f4_discovery.c \
../drivers/BSP/stm32f4_discovery_accelerometer.c \
../drivers/BSP/stm32f4_discovery_audio.c 

OBJS += \
./drivers/BSP/cs43l22.o \
./drivers/BSP/lis302dl.o \
./drivers/BSP/lis3dsh.o \
./drivers/BSP/stm32f4_discovery.o \
./drivers/BSP/stm32f4_discovery_accelerometer.o \
./drivers/BSP/stm32f4_discovery_audio.o 

C_DEPS += \
./drivers/BSP/cs43l22.d \
./drivers/BSP/lis302dl.d \
./drivers/BSP/lis3dsh.d \
./drivers/BSP/stm32f4_discovery.d \
./drivers/BSP/stm32f4_discovery_accelerometer.d \
./drivers/BSP/stm32f4_discovery_audio.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/BSP/%.o drivers/BSP/%.su drivers/BSP/%.cyclo: ../drivers/BSP/%.c drivers/BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/BSP" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/cmsis" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/STM32_USB_Host_Library/Core/Inc" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/USBH_midi_class/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers-2f-BSP

clean-drivers-2f-BSP:
	-$(RM) ./drivers/BSP/cs43l22.cyclo ./drivers/BSP/cs43l22.d ./drivers/BSP/cs43l22.o ./drivers/BSP/cs43l22.su ./drivers/BSP/lis302dl.cyclo ./drivers/BSP/lis302dl.d ./drivers/BSP/lis302dl.o ./drivers/BSP/lis302dl.su ./drivers/BSP/lis3dsh.cyclo ./drivers/BSP/lis3dsh.d ./drivers/BSP/lis3dsh.o ./drivers/BSP/lis3dsh.su ./drivers/BSP/stm32f4_discovery.cyclo ./drivers/BSP/stm32f4_discovery.d ./drivers/BSP/stm32f4_discovery.o ./drivers/BSP/stm32f4_discovery.su ./drivers/BSP/stm32f4_discovery_accelerometer.cyclo ./drivers/BSP/stm32f4_discovery_accelerometer.d ./drivers/BSP/stm32f4_discovery_accelerometer.o ./drivers/BSP/stm32f4_discovery_accelerometer.su ./drivers/BSP/stm32f4_discovery_audio.cyclo ./drivers/BSP/stm32f4_discovery_audio.d ./drivers/BSP/stm32f4_discovery_audio.o ./drivers/BSP/stm32f4_discovery_audio.su

.PHONY: clean-drivers-2f-BSP

