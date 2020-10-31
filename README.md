Dekrispator (v3)
===========

Updates ! Responds now to notes on/off and can be played with a keyboard (Thanks to GaryA and Tomas Scherrer).

Transform your STM32F4 Discovery board into an experimental music synthesizer or autonomous noise box with USB MIDI Host function for interaction !

Sound demos are here : https://soundcloud.com/bluexav

A video : http://youtu.be/fcLrcDCaI7w

- - - -

**Usage**

Flash your board with "Dekrispator_v2.bin" or .elf (in Release folder) and enjoy hours and hours of sweet music coming of it ! Sounds can be loud so beware !

When powering up the board, the synth starts in "demo mode". The synth works on its own, sounds are perpetually changing. 

If you press the user button, sequencer will stop, it will run again if you press the button once again.

To control Dekrispator's parameters you can connect at any time an USB MIDI controller (like Korg NanoKontrol...) to the board's micro USB connector.

You can also play notes if you connect a keyboard and turn off the sequencer.

CC68 (= 127) : reset synth with basic sound and sequencer running.

CC67 (= 127) : toggle demo mode.

CC69 (= 127) : toggles sequencer run/stop



Ready-to-use files are in Ressources folder.

The MIDI mapping of the synth controls are in MIDI_mapping.ods file. I used the factory settings of Korg NanoKontrol V1 (some momentary/toggle buttons modified). 


- - - -

**Dekrispator features** :

 * monophonic
 * all digital !
 * sound generators :
   * oscillators with very low aliased analog waveforms with superb minBLEP oscillators (thanks to Sean Bolton)
   * 4 operators FM generator
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
 * random sound and FX patch generator
 * LED information :
   * The orange LED reflects the CPU usage : when it's dim CPU gets overloaded.
   * The red LED lights on when sequencer is stopped or when a system error occurs.
   * The green LED indicates a midi usb is connected and recognized.
   * The blue LED indicates midi activity.

- - - -
Special thanks : Sean Bolton, Perry R. Cook and Gary P. Scavone, Gabriel Rivas, Ross Bencina, GaryA, Thorsten Klose, erwincoumans, ST

- - - - 

**Building from source :**

Go to Release folder and type "make". Then flash the mcu with your prefered tool.

Linux example with stlink-tools : 

```
$ st-flash write Dekrispator_v2.bin 0x8000000
```

Note : I have to run st-flash (v 1.6.1) twice because there is always an error during first run ! I don't know why...
- - - 

**Developpers notes :**

* RAM is almost full !
* Extensive use of CCM RAM for stack, heap, and global variables
* Link Time Optimization ( -flto ) 
* audio DMA and USB interrupts priorities are set equal to 6
* Flash size is about 141752 bytes (-O3)
* Size of the audio buffer (affects latency) can be tweaked in CONSTANTS.h file (BUFF_LEN must be a multiple of 4).
It is set at 4000 bytes long (BUFF_LEN = 2000) but it can be reduced.

* Compiler : arm-none-eabi-gcc (GNU Arm Embedded Toolchain 9-2020-q2-update) 9.3.1 20200408 (release)

* Cross ARM C Compiler options :

arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O3 -ffunction-sections -fdata-sections  -fsingle-precision-constant -flto -Wall -D__FPU_USED=1 -DHSE_VALUE=8000000 -DUSE_HAL_DRIVER -DUSE_STM32F4_DISCO -DSTM32F407xx -I"........................................."

* Linker options :

arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O3 -ffunction-sections -fdata-sections  -fsingle-precision-constant -flto -Wall -T ".............\STM32F407VG_FLASH.ld" -Xlinker --gc-sections -Wl,-Map,"Dekrispator_v2.map" --specs=nosys.specs -flto -o "Dekrispator_v2.elf"  ..............  -lm
  
- - - 
**See also the port to Windows, Linux, Mac and Raspberry Pi  by erwincoumans :**

 https://github.com/erwincoumans/StkDekrispatorSynthesizer
 
 Thank you Thorsten Klose for your inspirational work and especially MIOS32 !
