################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Synth/MIDI_application.c \
../Synth/adsr.c \
../Synth/audio_conf.c \
../Synth/blepvco.c \
../Synth/chorusFD.c \
../Synth/delay.c \
../Synth/drifter.c \
../Synth/main.c \
../Synth/math_tools.c \
../Synth/minblep_tables.c \
../Synth/notesTables.c \
../Synth/oscillators.c \
../Synth/phaser.c \
../Synth/random.c \
../Synth/resonantFilter.c \
../Synth/sequencer.c \
../Synth/sinetable.c \
../Synth/soundGen.c \
../Synth/timers.c 

OBJS += \
./Synth/MIDI_application.o \
./Synth/adsr.o \
./Synth/audio_conf.o \
./Synth/blepvco.o \
./Synth/chorusFD.o \
./Synth/delay.o \
./Synth/drifter.o \
./Synth/main.o \
./Synth/math_tools.o \
./Synth/minblep_tables.o \
./Synth/notesTables.o \
./Synth/oscillators.o \
./Synth/phaser.o \
./Synth/random.o \
./Synth/resonantFilter.o \
./Synth/sequencer.o \
./Synth/sinetable.o \
./Synth/soundGen.o \
./Synth/timers.o 

C_DEPS += \
./Synth/MIDI_application.d \
./Synth/adsr.d \
./Synth/audio_conf.d \
./Synth/blepvco.d \
./Synth/chorusFD.d \
./Synth/delay.d \
./Synth/drifter.d \
./Synth/main.d \
./Synth/math_tools.d \
./Synth/minblep_tables.d \
./Synth/notesTables.d \
./Synth/oscillators.d \
./Synth/phaser.d \
./Synth/random.d \
./Synth/resonantFilter.d \
./Synth/sequencer.d \
./Synth/sinetable.d \
./Synth/soundGen.d \
./Synth/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Synth/%.o: ../Synth/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O3 -ffunction-sections -fdata-sections -fsingle-precision-constant -flto -Wunused -Wuninitialized -Wall -Wconversion -Wshadow -Wfloat-equal -D__FPU_USED=1 -DHSE_VALUE=8000000 -DUSE_HAL_DRIVER -DUSE_STM32F4_DISCO -DSTM32F407xx -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\STM32_USB_Host_Library\Core\Inc" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\BSP" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\cmsis" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\STM32F4xx_HAL_Driver\Inc" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\drivers\USBH_midi_class\Inc" -I"C:\xav_dev\eclipse_luna\Dekrispator_v2\Synth" -std=c11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


