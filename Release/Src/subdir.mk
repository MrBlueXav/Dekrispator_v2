################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MIDI_application.c \
../Src/adsr.c \
../Src/audio_conf.c \
../Src/blepvco.c \
../Src/chorusFD.c \
../Src/delay.c \
../Src/drifter.c \
../Src/main.c \
../Src/math_tools.c \
../Src/minblep_tables.c \
../Src/notesTables.c \
../Src/oscillators.c \
../Src/phaser.c \
../Src/random.c \
../Src/resonantFilter.c \
../Src/sequencer.c \
../Src/sinetable.c \
../Src/soundGen.c \
../Src/stm32f4xx_it.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f4xx.c \
../Src/timers.c \
../Src/usbh_conf.c 

OBJS += \
./Src/MIDI_application.o \
./Src/adsr.o \
./Src/audio_conf.o \
./Src/blepvco.o \
./Src/chorusFD.o \
./Src/delay.o \
./Src/drifter.o \
./Src/main.o \
./Src/math_tools.o \
./Src/minblep_tables.o \
./Src/notesTables.o \
./Src/oscillators.o \
./Src/phaser.o \
./Src/random.o \
./Src/resonantFilter.o \
./Src/sequencer.o \
./Src/sinetable.o \
./Src/soundGen.o \
./Src/stm32f4xx_it.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f4xx.o \
./Src/timers.o \
./Src/usbh_conf.o 

C_DEPS += \
./Src/MIDI_application.d \
./Src/adsr.d \
./Src/audio_conf.d \
./Src/blepvco.d \
./Src/chorusFD.d \
./Src/delay.d \
./Src/drifter.d \
./Src/main.d \
./Src/math_tools.d \
./Src/minblep_tables.d \
./Src/notesTables.d \
./Src/oscillators.d \
./Src/phaser.d \
./Src/random.d \
./Src/resonantFilter.d \
./Src/sequencer.d \
./Src/sinetable.d \
./Src/soundGen.d \
./Src/stm32f4xx_it.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f4xx.d \
./Src/timers.d \
./Src/usbh_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F407xx -DUSE_HAL_DRIVER -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/BSP" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/cmsis" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/STM32_USB_Host_Library/Core/Inc" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/DeveloppementXav/Dekrispator/Dekrispator_v2_STM32F4DK/Dekrispator_v2/drivers/USBH_midi_class/Inc" -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/MIDI_application.cyclo ./Src/MIDI_application.d ./Src/MIDI_application.o ./Src/MIDI_application.su ./Src/adsr.cyclo ./Src/adsr.d ./Src/adsr.o ./Src/adsr.su ./Src/audio_conf.cyclo ./Src/audio_conf.d ./Src/audio_conf.o ./Src/audio_conf.su ./Src/blepvco.cyclo ./Src/blepvco.d ./Src/blepvco.o ./Src/blepvco.su ./Src/chorusFD.cyclo ./Src/chorusFD.d ./Src/chorusFD.o ./Src/chorusFD.su ./Src/delay.cyclo ./Src/delay.d ./Src/delay.o ./Src/delay.su ./Src/drifter.cyclo ./Src/drifter.d ./Src/drifter.o ./Src/drifter.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/math_tools.cyclo ./Src/math_tools.d ./Src/math_tools.o ./Src/math_tools.su ./Src/minblep_tables.cyclo ./Src/minblep_tables.d ./Src/minblep_tables.o ./Src/minblep_tables.su ./Src/notesTables.cyclo ./Src/notesTables.d ./Src/notesTables.o ./Src/notesTables.su ./Src/oscillators.cyclo ./Src/oscillators.d ./Src/oscillators.o ./Src/oscillators.su ./Src/phaser.cyclo ./Src/phaser.d ./Src/phaser.o ./Src/phaser.su ./Src/random.cyclo ./Src/random.d ./Src/random.o ./Src/random.su ./Src/resonantFilter.cyclo ./Src/resonantFilter.d ./Src/resonantFilter.o ./Src/resonantFilter.su ./Src/sequencer.cyclo ./Src/sequencer.d ./Src/sequencer.o ./Src/sequencer.su ./Src/sinetable.cyclo ./Src/sinetable.d ./Src/sinetable.o ./Src/sinetable.su ./Src/soundGen.cyclo ./Src/soundGen.d ./Src/soundGen.o ./Src/soundGen.su ./Src/stm32f4xx_it.cyclo ./Src/stm32f4xx_it.d ./Src/stm32f4xx_it.o ./Src/stm32f4xx_it.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32f4xx.cyclo ./Src/system_stm32f4xx.d ./Src/system_stm32f4xx.o ./Src/system_stm32f4xx.su ./Src/timers.cyclo ./Src/timers.d ./Src/timers.o ./Src/timers.su ./Src/usbh_conf.cyclo ./Src/usbh_conf.d ./Src/usbh_conf.o ./Src/usbh_conf.su

.PHONY: clean-Src

