Dekrispator version 2
===========

This is a rewriting of the old Dekrispator but there is no new feature at the moment.
I've used the new STM32Cube library from ST (v1.3) with new HAL and USB host stack.
I've written a new USB host MIDI class driver which should accept more devices.

Transform your STM32F4 Discovery board into an experimental music synthesizer or autonomous noise box with USB MIDI Host function for interaction !

The sound demos are here : https://soundcloud.com/bluexav

A video is here : http://youtu.be/fcLrcDCaI7w

- - - -

**Usage**

Flash your board with "Dekrispator_v2.hex" (in Release folder) and enjoy hours and hours of sweet music coming of it ! Sounds can be loud so beware !

When powering up the board, the synth starts in "demo mode" unless you press and maintain a little the user button before power. In that case the synth enters "user mode".

*Demo mode* : The synth works on its own, sounds are perpetually changing. If you press the user button, sounds and effects stop always changing and the red LED lights on : the synth parameters are frozen. Press once again the user button and the red LED lights off : unfreeze.

*User mode* : Connect an USB MIDI controller (like Korg NanoKontrol...) to the board's micro USB connector and control the synth.
The MIDI mapping of the synth controls are in MIDI_mapping.ods file. I nearly used the factory settings of Korg NanoKontrol V1 (some momentary/toggle buttons modified). The blue LED indicates midi activity.


The orange LED reflects the CPU usage : when it's dim CPU gets overloaded.

Ready-to-use files are in Ressources folder.

- - - -

**Dekrispator features** :

 * monophonic
 * all digital !
 * oscillators with :
  * very low aliased analog waveforms with superb minBLEP oscillators (thanks to Sean Bolton)
  * 4 OP FM generator
  * multisaw (several saws with individual "drifters")
  * 10 sine additive generator
  * noise
 * 16 step random sequencer
 * several scales to choose from
 * 2 parallel filters LP/BP/HP with LFOs
 * Effects :
  * vibrato
  * tremolo
  * drive/distortion
  * echo
  * chorus/flanger
  * phaser
 * random sound/FX patch generator

- - - -

**Building from source :**

I've used (Windows Vista):

* Eclipse Luna
* GNU ARM plugin for Eclipse
* Yagarto tools for make, rm, ...
* GNU Tools for ARM Embedded Processors (gcc 4.9 2014 q4) 
* STM32 ST-LINK Utility for flashing the microcontroller

Compiles also on Linux (Debian 7) with Eclipse Luna and on command line with "make".

- - - 

**Dev notes :**

* RAM is almost full !
* Extensive use of CCM RAM for stack, heap, and global variables
* Link Time Optimization ( -flto ) 
* audio DMA and USB interrupts priorities are set equal to 6
* Flash size is about 128000 bytes (-O3)
* Size of the audio buffer (affects latency) can be tweaked in CONSTANTS.h file (BUFF_LEN must be a multiple of 4).
It is set at 4000 bytes long (BUFF_LEN = 2000) but it can be reduced.

* Cross ARM C Compiler options :

arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O3 -ffunction-sections -fdata-sections  -fsingle-precision-constant -flto -Wall -D__FPU_USED=1 -DHSE_VALUE=8000000 -DUSE_HAL_DRIVER -DUSE_STM32F4_DISCO -DSTM32F407xx -I"........................................."

* Linker options :

arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O3 -ffunction-sections -fdata-sections  -fsingle-precision-constant -flto -Wall -T ".............\STM32F407VG_FLASH.ld" -Xlinker --gc-sections -Wl,-Map,"Dekrispator_v2.map" --specs=nosys.specs -flto -o "Dekrispator_v2.elf"  ..............  -lm
  
- - - 
**See also the port to Windows, Linux, Mac and Raspberry Pi  by erwincoumans :**

 https://github.com/erwincoumans/StkDekrispatorSynthesizer
 
 Thank you Thorsten Klose for your inspirational work and especially MIOS32 !
