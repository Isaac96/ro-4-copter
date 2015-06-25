# Design Notes #

Most footprints support multiple device packaging, just in case you have something already on hand

No copper near where abrasion is expected (near around the FTDI connector, and the mounting slots)

No copper under the XBee antenna

No copper under the compass sensor

I did my best to label everything on the silk screen layer

All traces are 0.016" wide or greater. If you need to cut a trace, but then later want to re-connect it, the thick trace makes this easy for you.

Most header footprints have a tiny locking offset similar to how SparkFun does it in their Eagle library, however my footprints are easier to center correctly.

I know AeroQuad depends on all the timers except timer0 (reserved so `millis()` works) to control auxiliary servos on the Arduino Mega, so you might be wondering how I plan on controlling four more servos when the ATmega644PA only has timer0 available to use. Don't worry, I have compare match driven servo control code (called SoftServo) that utilizes timer0 without disturbing the operation of `millis()`, and actually my code can target any pin on the ATmega, even the ones on PORTA (where there are 7 available GPIOs).

## Improvements Over Various Other Products ##

Stop spending money on Arduinos and its cousins, being stand-alone means you can use your Arduino for other stuff without removing it from your aircraft. If you have money to blow on an Arduino Mega, blow it on something like a Teensy++ or mbed instead. (I might consider redoing this PCB to use the mbed later)

The AeroQuad shields look kind of "Eagle auto-routed" (judging from the trace width, apparent routing grid, and weird cornering of the traces), I think I'm being very picky about this sort of stuff.

The AeroQuad shield have mandatory level shifting for the I2C bus which is totally unnessesary, but no level shifting for any serial port devices. My design has **optional** level shifting for both serial ports, and I2C uses external pull-up resistors to 3V3 so it doesn't need level shifting. (I have not heard of a 5V I2C device that wouldn't work on a I2C bus that used 3V3, and lately 5V I2C devices are extremely rare)

The LEDs on the AeroQuad V1.8 shield are supposed to be special LEDs with current limiting resistors built inside, but this makes it dangerous for anybody not using the same special LEDs. Also the LED on pin 13 can cause problems for any SPI devices and ISP programming.

The AeroQuad shields do not provide a 3V3 supply, it uses the one built into the Arduino. The 3V3 supply from the Arduino boards before UNO are kind of bad, limited, and noisy.

The ArduPilot is hideously expensive in comparison.

## After Thoughts ##

I didn't put any designation on the first batch of PCBs, version 1 is dated TODO and can be recognized by the test pattern on the PCB

### Version 1 After Thoughts ###

This PCB might be **too** configurable for some people, but if you are smart enough to build a quadrotor helicopter, you better be smart enough to read this page.

AREF probably should just be connected directly to 3V3, since you can select 5V as the reference through software.

More attention could have been paid towards SPI, but nothing uses SPI yet. The ISP header is the only way to access the SPI signals. To experiment with SPI devices, I suggest you connect it with this header by using a 2X3 IDC cable, and then use a pin from PORTA or PORTB as the CS or SS signal. Remember that the voltage here is 5V and if your device uses 3V3, external level shifters might be needed. Luckily, there's two connectors (labelled 3V3-TAP) near the voltage regulators that give you access to 3V3.

The native USB stuff probably causes a lot of confusion. Just don't bother with it if you don't understand how to use it.

No mounting holes for IMU3000 breakout board, oh well, see [this thread](http://aeroquad.com/showthread.php?2655)

Timer1's ICP is not available for use since it is occupied by OC2B. However I do have working and tested code from a `non-AeroQuad` quadcopter that can use timer1 to drive 7 servos (via a decade counter or serial-to-parallel shift register) while reading PPM from ICP. (This code is not included, I'm just mentioning it so you know it's possible)

RSSI pin is not used on the XBee. Various shields on the market include a LED on this pin, but I think you can always just look at the ground station XBee's RSSI instead of the one that is flying.

INT0, INT1, and INT2 are the only external interrupt pins on the ATmega644PA, but there's no easy way to use them on this PCB. Good thing there are plenty of PCINT pins.

My code for the 4 camera/auxiliary servos work, but I'm not sure how having more interrupt routines will bother the rest of the time sensitive software.

`R`4's silkscreen is covering a via, this was because the USB stuff was added at the end.

I forgot to label the USB connector footprint with silkscreen text, although it is pretty obvious that it is for a USB mini B female connector.

I don't think there's a standard I2C cable, and my connectors for I2C ESCs are different from what's on the AeroQuad Mega shield, but if you just follow the labelling on the pins, you'll have no problem making a custom 4 pin to 3 pin cable.

### Version 2 Future Plans ###

See how useful the native USB is

Extensive testing with XBee to see if level shifting is actually required

Tie AREF to 3V3 by default, however, leave the solder jumper footprint

Maybe add trim-pots

Change the I2C ESC connectors slightly

Maybe move right to using the mbed, but that will probably be called another project

More to come...