################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/BSP/cs43l22.c \
../drivers/BSP/lis302dl.c \
../drivers/BSP/lis3dsh.c \
../drivers/BSP/stm32f4_discovery.c \
../drivers/BSP/stm32f4_discovery_accelerometer.c \
../drivers/BSP/stm32f4_discovery_audio.c \
../drivers/BSP/stm32f4xx_it.c \
../drivers/BSP/system_stm32f4xx.c \
../drivers/BSP/usbh_conf.c 

S_UPPER_SRCS += \
../drivers/BSP/startup_stm32f407xx.S 

OBJS += \
./drivers/BSP/cs43l22.o \
./drivers/BSP/lis302dl.o \
./drivers/BSP/lis3dsh.o \
./drivers/BSP/startup_stm32f407xx.o \
./drivers/BSP/stm32f4_discovery.o \
./drivers/BSP/stm32f4_discovery_accelerometer.o \
./drivers/BSP/stm32f4_discovery_audio.o \
./drivers/BSP/stm32f4xx_it.o \
./drivers/BSP/system_stm32f4xx.o \
./drivers/BSP/usbh_conf.o 

C_DEPS += \
./drivers/BSP/cs43l22.d \
./drivers/BSP/lis302dl.d \
./drivers/BSP/lis3dsh.d \
./drivers/BSP/stm32f4_discovery.d \
./drivers/BSP/stm32f4_discovery_accelerometer.d \
./drivers/BSP/stm32f4_discovery_audio.d \
./drivers/BSP/stm32f4xx_it.d \
./drivers/BSP/system_stm32f4xx.d \
./drivers/BSP/usbh_conf.d 

S_UPPER_DEPS += \
./drivers/BSP/startup_stm32f407xx.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/BSP/%.o: ../drivers/BSP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O3 -ffunction-sections -fdata-sections -fno-builtin -fsingle-precision-constant -flto -Wall -D__FPU_USED=1 -DHSE_VALUE=8000000 -DUSE_HAL_DRIVER -DUSE_STM32F4_DISCO -DSTM32F407xx -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\STM32_USB_Host_Library\Core\Inc" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\BSP" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\cmsis" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\STM32F4xx_HAL_Driver\Inc" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\USBH_midi_class\Inc" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\Synth" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/BSP/%.o: ../drivers/BSP/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O3 -ffunction-sections -fdata-sections -fno-builtin -fsingle-precision-constant -flto -Wall -x assembler-with-cpp -DSTM32F40_41xxx -D__FPU_USED=1 -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DSTM32F407VG -DUSE_HAL_DRIVER -DSTM32F407XX -DUSE_STM32F4_DISCO -DSTM32F407xx -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


