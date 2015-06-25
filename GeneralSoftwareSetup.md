# Software Setup Guide for Ro4Copter #

You'll need Arduino installed first.

# Special ATmega644PA Core #

I'm using a modified Arduino core so that the Arduino sketches will compile for the ATmega644PA correctly, which obviously have different pin designations. Also some additional functionality has been added.

I've included TWI code that is more efficient than the "Wire" I2C library (the Wire library is not suited for master-only operation). The old code still uses the Wire library but the new code gets used if `Ro4Copter` is defined.

`wiring.c` is modified so that timer0's overflow interrupt vector can be utilized to control servos without distrubing the functionality of the `millis()` function. My own timer0 servo control library called `SoftServo` is also incorporated into the core. An additional function called `millis_fast()` is also added and it is designed to be used from within interrupt routines.

Install the core by copying the folder `Ro4Copter_Core` into your Arduino installation such that you create `\arduino-0022\hardware\arduino\cores\Ro4Copter_Core\`.

You will also need to modify `boards.txt` to include the entry

```

Ro4Copter.name=Ro4Copter
Ro4Copter.upload.protocol=stk500
Ro4Copter.upload.maximum_size=57344
Ro4Copter.upload.speed=57600
Ro4Copter.bootloader.low_fuses=0xFF
Ro4Copter.bootloader.high_fuses=0xD8
Ro4Copter.bootloader.extended_fuses=0xFF
Ro4Copter.bootloader.path=Ro4Copter_Boot
Ro4Copter.bootloader.file=Ro4Copter_Boot_arduino.hex
Ro4Copter.bootloader.unlock_bits=0x3F
Ro4Copter.bootloader.lock_bits=0x0F
Ro4Copter.build.mcu=atmega644p
Ro4Copter.build.f_cpu=16000000L
Ro4Copter.build.core=Ro4Copter_Core

```

Note: settings in `boards.txt` will only take effect when you close and re-open Arduino IDE

# Bootloaders #

You'll need to change the `bootloader.file` and `upload.protocol` in `boards.txt' according to the bootloader you want to use.

Several special bootloaders are developed, copy the folder `Ro4Copter_Boot` as `\arduino-0022\hardware\arduino\bootloaders\Ro4Copter_Boot\`

`Ro4Copter_Boot_arduino.hex` requires the stk500 protocol, and requires you to use a FTDI cable. Use it as if the Ro4Copter is an Arduino without auto-reset. This bootloader has a timeout like the regular Arduino bootloader. It's been modified from the Sanguino bootloader.

`Ro4Copter_Boot_stk500_w_btn.hex` requires the stk500 protocol, and requires you to use a FTDI cable. Hold down the BOOT button while clicking the RESET button, this bootloader will never time out. Pressing RESET without holding down BOOT will not engage the bootloader. Not having to wait and not having a timeout feels much better than the default Arduino bootloader.

`Ro4Copter_Boot_usbasp.hex` requires the protocol to be set as `usbasp`. Add the line `Ro4Copter.upload.disable_flushing=true` Hold down the BOOT button while clicking the RESET button, this bootloader will never time out. Pressing RESET without holding down BOOT will not engage the bootloader. You can only use this if you have installed all of the components required for native USB. You'll also need the [drivers for USBasp from its website](http://www.fischl.de/usbasp/). This bootloader does not occupy any serial ports, so you don't have to mess with constantly disconnecting, reconnecting, selecting, and configuring serial ports.

### [IMPORTANT NOTE: After testing, I found that USBaspLoader will not work with a 16 MHz ceramic resonator](UsbTesting.md) ###