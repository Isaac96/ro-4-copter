# Assembly Guide and Circuit Walkthrough #

Note that all resistors are in 0805 packaging, although 0603 will also fit perfectly fine. They should be 1/16 watt or greater. Note that all capacitors, unless otherwise specified, are ceramic chip capacitors in 0805 packaging (or 0603 since they will also fit perfectly fine). They should be rated 16V or greater.

This assembly guide also contains some notes about the various areas on the circuit.

## Microcontroller ##

<img src='http://frank.circleofcurrent.com/junk/aq64_img/microcontroller1.png' />
<img src='http://frank.circleofcurrent.com/junk/aq64_img/microcontroller2.png' />

The ATmega644PA obviously must be installed, solder in a 40 pin DIP socket so you are able to replace the IC if you need to.

The ATmega644PA requires a 16 MHz resonator.

The resonator footprint also allows you to use a 16 MHz crystal in HC49 packaging, but if you do this, you must install two 27 pF capacitors to the underside of the board. You should only choose a 16 MHz crystal if you have a good reason not to use a 16 MHz resonator.

You must solder C1 and C2, which are 0.1 uF decoupling capacitors for the ATmega644PA. Also solder C9 which is a 0.1 uF decoupling capacitor for the analog reference.

On the bottom of the board, there is a footprint labelled "AREF-SEL", which allows you to choose the analog reference voltage by soldering over the pads labelled 5V or 3V3. You may also use a 0 ohm resistor here, or an ferrite bead. Note that AVCC is always connected to 5V.

## Microcontroller Supporting Areas ##

<img src='http://frank.circleofcurrent.com/junk/aq64_img/mcusupport1.png' />
<img src='http://frank.circleofcurrent.com/junk/aq64_img/mcusupport2.png' />

The reset switch must be installed, `R`13 10K ohm is the pull-up resistor for the reset switch. This resistor is optional because the ATmega644PA has a built-in pull-up resistor on the reset pin. You should install this if you do not trust the built-in resistor.

A push button labelled "BOOT" can be installed only if you are using a non-Arduino-standard bootloader. I personally hate the way "time sensitive" bootloaders work. This button is active low and connected to PB6 on the ATmega. Be sure to enable internal pull-up resistors for this button.

The ISP header (labelled AVRISP) should be installed if you need to use an AVR programmer (perhaps to load the bootloader for the first time, etc). The long line at the side indicates the side that the "red wire" (also pin 1) of the cable should be, and the short line at the bottom indicates where the notch of the connector should be.

## LED Indicators ##

<img src='http://frank.circleofcurrent.com/junk/aq64_img/leds1.png' />

LED1, LED2, LED3 are 3 mm LEDs, choose your own colours. They can be mounted vertically or horizontally (pointing out). Please watch the polarity indicated by the hole shape and silkscreen. `R`3, `R`4, and `R`5, are all 1K ohm resistors to limit current to these LEDs. They are 1K ohm instead of a lower value because the signals may be used for some other purpose later, you may substitute a lower resistance if you want brighter LEDs and do not want to experiment with native USB funtionality.

LED3 does not currently serve any purpose in the existing software, it is there for you to use for your own custom application. LED1 is conencted to PB0 (Sanguino pin 0), LED2 is connected to PB1 (Sanguino pin 1), and LED3 is connected to PB2 (Sanguino pin 2). LED1 and LED2 should perform the same functions as the two LEDs on the AeroQuad V1.8 shield.

## Power Supply ##

<img src='http://frank.circleofcurrent.com/junk/aq64_img/pwrsupply1.png' />

Solder a LM1117 3V3 regulator in SOT-233-3 packaging where indicated on the PCB. Also solder the accompanying C3, which is 1 uF.

LED-PWR is a 3 mm LED that indicates that there is power present on the 3V3 supply bus. You may solder this vertically or sideways (pointing out). `R`12 is the 1K ohm current limiting resistor for this LED.

Two rows of 3 pin male headers should be installed at "3V3-TAP", these headers give you access to the 3V3 supply bus. Two rows of 3 pin male headers should be installed at "5V-TAP", these headers give you access to the "SYS" 5V supply bus.

If you are powering this circuit from a battery, you must install a LM1117 5V regulator in SOT-233-3 packaging where indicated on the PCB. This may be omitted if you are using the ESCs as the power supply (be sure to set SJ1 correctly), or under other circumstances that you are under.

The 1 uF capacitor C4 should be always soldered regardless of whether or not you are using a 5V regulator.

The battery power input is used if you need to connect a battery. There are four ways to do this:

<img src='http://frank.circleofcurrent.com/junk/aq64_img/batteryoptions1.png' />

  * Using a barrel jack
  * Solder wire directly onto PCB (you can enlarge some holes to act as strain relief)
  * using a screw terminal
  * Using a 3 pin header

A beefy diode should be installed at D2 to protect the circuit from a battery connected backwards (so omit this diode if you believe in your own competence, you must bridge the pads of the diode footprint with solder if you omit this diode). This must be a diode that can handle 20V of reverse voltage, and handle 1.5A of forward current. The footprint is SMB or similar.

C5 and C6 are aluminum electrolytic 5.3mm x 5.3mm capacitors that must be installed, solder them in the correct orientation according to polarity.

### Battery Monitor ###

<img src='http://frank.circleofcurrent.com/junk/aq64_img/battmon1.png' />

If you want to use the battery voltage monitor capabilies, install D1 (1N4148 in MELF packaging), `R`7 (7K5 ohm), and `R`6 (15K ohm). There's a 3 pin header near these components labelled "BATT-MON" that you can use to connect the battery that you wish to monitor. Alternatively, bridging SJ16 will connect the battery supply to the battery monitor circuit instead. The battery monitor and battery supply sections are separated in case you use two separate batteries (one for motors, another for control electronics). Remember to enable the battery monitor software, and note that this is connected to analog channel 0 (PORTA's PA0).

Remember to measure the voltage drop across D1 and also the values of `R`6 and `R`7. Set these values in the software so the sampled data is accurate.

Note: MultiWiiCopter's circuitry uses `R`7 = 33K ohm and `R`6 = 51K ohm without any diodes.

## Port A Auxiliary GPIOs ##

<img src='http://frank.circleofcurrent.com/junk/aq64_img/portapins1.png' />

There are 7x3 headers connected to PORTA's pins PA1 to PA7. The top row of pins is ground, the voltage for the center row of pins is selectable, and the pins in the bottom row are connected to PORTA's pins. You must select the voltage for the center row according to how you plan to use them. These pins have no specific purpose and are meant for you to experiment with. Here are your options and how you should choose the voltage.

  * Control more servos
    * Use SJ17 to power the servos via the system supply (might be weak) or the power supplied by the ESCs (recommended).
  * Read more RC input channels
    * Use SJ15 to connect the same voltage used by the RC input headers
  * General purpose digital input/output
    * Select either 5V or 3V3 using SJ15 and SJ2 together
  * Read in analog voltages
    * Select either 5V or 3V3 using SJ15 and SJ2 together
  * Use with jumper shunt blocks
    * Select ground using SJ15, also remember to enable the internal pull-up resistors on these pins

Important: If you select ground for SJ15, then do not select anything using SJ17, doing so will short-circuit the power supply connected to SJ17 with ground, which can cause damage to the various power supply components.

Important: If you select V-RC with SJ15 (to use the same voltage that the RC inputs are using) and you have selected 3V3 using SJ3, then you must not use SJ17 to select anything. Doing so will cause the 5V supply to be joined with the 3V3 supply, which can cause damage to 3V3 devices.

## RC Input ##

<img src='http://frank.circleofcurrent.com/junk/aq64_img/rcinputpins1.png' />

PORTC's pins PC7 to PC2 are connected to 6x3 headers, solder in male headers here. These are dedicated to taking RC pulse signals from your RC receiver. The voltage for the center pin can be connected to 5V or 3V3 using SJ2, and remember that there is a "5V-TAP" and "3V-TAP" if your receiver needs power from a 7th cable.

Important: If you select V-RC with SJ15 (to use the same voltage that the RC inputs are using) and you have selected 3V3 using SJ3, then you must not use SJ17 to select anything. Doing so will cause the 5V supply to be joined with the 3V3 supply, which can cause damage to 3V3 devices.

## Sensors ##

<img src='http://frank.circleofcurrent.com/junk/aq64_img/sensors1.png' />

Solder `R`1 and `R`2, which are 4K7 pull-up resistors for the I2C bus. Be sure that you disable internal pull-up resistors in the software. This allows you to use 3V3 I2C sensors without using a level shifter.

Note that some of the SparkFun breakout boards already include a pull-up resistor, if so, then do not install `R`1 and `R`2.

You may choose to install either the 6-DOF IMU (gyro and accelerometer combined) breakout board, or a ITG-3200 gyro breakout board. If you do choose the ITG-3200, you may then also choose to install a BMA180 accelerometer breakout board. You must always have a gyro but the accelerometer is optional (it allows you to enable auto-leveling flight). Be sure to configure this correctly in the software.

If you are feeling experimental, the IMU3000 breakout board also fits into the ITG-3200 breakout board footprint, with similar pin assignments.

You may also choose to install a BMP085 barometric sensor breakout board, and a HMC5842 compass breakout board. These are optional and you can configure the software to use them for altitude-hold and compass-heading-hold.

## Outputs to Motors and Servos ##

<img src='http://frank.circleofcurrent.com/junk/aq64_img/variousoutputs1.png' />

Four sets of 3-pin male headers should be soldered near "ESC" labels, these are connections for standard RC pulse signal ESCs. SJ1 can be used to connect the voltage supplied by the ESCs to the main system supply bus.

Four sets of 4-pin headers can be soldered near "I2C-GROUP", these are meant for connections to any ESCs that use I2C. SJ3 Can be used to connect the 5V supply or 3V3 supply to the ESCs's supply voltage. Alternatively, if you wish to use only 3 wires to connect to I2C ESCs, then short the V+ pins of the I2C-GROUP headers with the ground pins, and DO NOT use SJ3 at all.

There's another 4-pin header also meant for an auxilliary I2C connection, SJ5 selects the voltage supplied to this connector. This connection is for experimentation with I2C devices. Personally, I think it's useful for connecting a logic analyzer to debug the I2C bus.

There's a set of four 3-pin headers labelled "SERVO" 1 to 4. Solder these if you have any servos to control (maybe for a camera? AreoQuad supports camera control), you can also use these as general purpose digital input/output pins. SJ4 is used to select the power supply for these servos, either from the system 5V supply, or the 5V supplied by the ESCs (recommended). These pins are connected to PB3 to PB6.

## Native USB ##

<img src='http://frank.circleofcurrent.com/junk/aq64_img/usbsection1.png' />

There is a section designed with [V-USB circuitry](http://obdev.at/products/vusb/index.html) so the ATmega644PA can communicate with a computer via native low speed USB. This can be used to implement FTDI-less communication, bootloading, and configuration. This is current meant just for experimentation.

### [IMPORTANT NOTE: Testing proved that V-USB will not work with a 16 MHz ceramic resonator](UsbTesting.md) ###

SJ18 is used to join the 5V power supply with the 5V coming from the computer's USB port, this is not recommended as the 5V from the computer is also connected to PB0 so that it can detect whether or not USB is connected.

Do not solder anything to the USB section unless you really want to experiment. It is possible for LED2 and LED3 to cause too much load on the USB bus, if you suspect that they are causing problems, uninstall `R`4 and `R`5.

C10 is a tantalum 4u7 capacitor, solder it on if you are playing with USB. This capacitor is polarized so install it in the right orientation as indicated. If you install a ceramic capacitor here, then most likely the orientation will not matter. `R`14 and `R`15 are 68 ohm terminating resistors for the D+ and D- signals of the USB bus, `R`16 is a 2K2 pull-up resistor which causes the computer to recognize the bus as low speed USB. D3 and D4 must be 3.6V zener diodes in MELF package (suggested 1N5227B, use 500 mW versions, will not work with 200 mW versions) which clamp the USB bus voltage.

## Serial Ports ##

<img src='http://frank.circleofcurrent.com/junk/aq64_img/sersection1.png' />

There are a few possible serial port devices. The ATmega644PA has two serial ports, USART0 and USART1, they are probably labelled SER0 and SER1 on the PCB.

Use horizontal mount male headers for the FTDI cable connection. This connection is always powered by 5V, RX and TX are at 5V level. Use SJ9 and SJ10 to decide whether to connect this to SER0 or SER1.

There's a connection designed for a Bluetooth Mate (or BlueSMIRF), and since they don't come with default headers, you should decide between either male or female headers yourself. This connection is always powered by 5V, RX and TX are at 5V level. Use SJ7 and SJ8 to decide whether to connect this to SER0 or SER1.

There's a connection meant for a general purpose serial device (GPS, datalogger, etc). Use SJ13 and SJ14 to decide whether to connect this to SER0 or SER1. Use SJ6 to decide whether to power this device from 5V or 3V3. It is important to note that the RX and TX signals are always at 3V3 level regardless of the supplied power. You must install the level shifter circuit or bypass it correctly if you plan on using this connector.

Install 2 mm female headers on the XBee footprint if you plan on using a XBee radio module. This is always powered by 3V3, RX and TX always uses the level shifted serial signals. SJ11 and SJ12 are used to select between using SER0 and SER1 for the XBee module.

### Level Shifters ###

<img src='http://frank.circleofcurrent.com/junk/aq64_img/levelshifting1.png' />
<img src='http://frank.circleofcurrent.com/junk/aq64_img/levelshifting2.png' />

If you plan on interfacing any 3V3 devices with the serial ports, you should implement the level shifting circuitry. XBee is known to not work well with 5V microcontrollers directly.

Each level shifter circuit uses a voltage divider for the TX signal and a TXB0101 (IC4 and IC5, SOT-23 package) bidirectional level translator for the RX signal. `R`9 (4K7 ohm), `R`8 (10K ohm) and IC4 are used for SER0. `R`10 (4K7 ohm), `R`11 (10K ohm) and IC5 are used for SER1. C7 and C8 (0.1 uF) are there to decouple the 3V3 and 5V supplies for IC4 and IC5. Do not omit C7 and C8 if either IC4 or IC5 is installed (otherwise, omit C7 and C8 if both IC4 and IC5 are omitted).

To bypass a level shifter circuit, short out the corresponding 4K7 ohm resistor footprint, omit the TXB0101, and join pin 3 and 4 (signal A and B) of the TXB0101 with a wire.

<img src='http://frank.circleofcurrent.com/junk/aq64_img/levelshifting_bypass.png' />