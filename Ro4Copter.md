# Ro4Copter #

This is my circuit and PCB design for a quadrotor helicopter flight controller.

The goal of this project is to create an inexpensive flight controller PCB that is both flexible to DIY quadcopter developers, while being almost ready-to-fly with little software development. Normally a new project like this would require both extensive hardware and software development, but this design minimizes both by being compatible with existing open source designs and software, with the additional benefit of extra features to make it even better. This means I can create this inexpensive PCB without rewriting the core flight control code, a GUI for tuning/configuration, and other stuff that's already been done a million times.

This design is supposed to be very compatible with AeroQuad and MultiWiiCopter. Both are fairly mature cross platform open source projects with GUI configuration/tuning utilities. Both are based on the Arduino, which is an AVR microcontroller. Both designs has a focus on similar sensors.

This design uses the ATmega644PA AVR microcontroller, from a general view point, it can be seen as being twice as "good" as the ATmega328P used by the AeroQuad and MultiWiiCopter. If you also consider the "AeroQuad Mega", then it can be seen as right in between the AeroQuad "Mega" variant and the original AeroQuad.

<img src='http://frank.circleofcurrent.com/junk/aq64_img/overview1.png' />

<img src='http://frank.circleofcurrent.com/junk/aq64_img/overview2.png' />

<img src='http://frank.circleofcurrent.com/junk/aq64_img/pcbsize1.png' />

## Features and General Specifications ##

  * ATmega644PA, 16 MHz, 64KB of flash memory, 4KB of SRAM memory
  * Two serial ports, both are level shifted, and can be easily routed to different devices
  * Plenty of pins for extra servos, digital and analog inputs, and digital outputs
  * Code size large enough for all existing AeroQuad and MultiWiiCopter code (even the stuff that only fits on the Arduino Mega and AeroQuad Mega Shield)
  * Supports ESCs which use RC pulse signals or I2C
  * Supports the following SparkFun breakout boards: ITG-3200 gyro, 6 DOF IMU, BMA180 accelerometer, BMP085 barometic pressure sensor, HMC5842 compass, IMU3000 IMU
  * Circuitry for battery monitoring
  * Connectors for FTDI cable, bluetooth, XBee, GPS, AVR programmer, V-USB, and more
  * 3 user LEDs and 1 power indicator LED
  * Reset switch, and another switch that you can use
  * Plenty of extra connectors, plenty of connection options
  * Plenty of configurations options available
  * Slotted corners allows for flexible mounting

  * PCB is 3.9 inch X 3.9 inch, 1.6 mm thick
  * Most traces are 0.016 inch wide with 0.012 inch minimum clearance
    * Wider traces and clearance for high current and high voltage signals
  * Most vias are 0.5 mm diameter, most holes are 1 mm in diameter
  * These PCB specs means it can be made by Seeed Studio or ITead Studio or BatchPCB easily

  * The choosen 5V and 3V3 voltage regulators are rated for 800 mA

# Quick Feature Walkthrough #

## Sensors ##

### Gyro ###
You absolutely must have a 3 axis gyro sensor.

Ro4Copter supports
  * The ITG-3200 gyro breakout board from SparkFun
  * The 6 DOF IMU combo board from SparkFun, which contains both an ITG-3200 gyro and a ADXL345 accelerometer

The AeroQuad derived and MultiWiiCopter derived code supports the ITG-3200

### Accelerometer ###

An accelerometer is optional but having one will help the software to hold the helicopter stable at a particular orientation.

Ro4Copter supports
  * The BMA180 breakout board from SparkFun
  * The 6 DOF IMU combo board from SparkFun, which contains both an ITG-3200 gyro and a ADXL345 accelerometer

### Barometric Pressure ###

Having one of these is optional. But if you have one, then the software can determine the helicopter's altitude by measuring air pressure, and then it can try to keep it steady at a particular altitude automatically.

The BMP085 sensor is supported by the Ro4Copter PCB, AeroQuad derived, and MultiWiiCopter derived code.

### Compass ###

Having one of these is optional. But if you have one, then the software can determine the helicopter's heading by measuring the Earth's magnetic field, and then it can try to keep it pointed in a particular direction.

The Ro4Copter PCB supports several of SparkFun's magnetic compass breakout boards, as long as they use I2C and the pins matches the footprint on the PCB.

AeroQuad derived code supports the HMC5843

MultiWiiCopter derived code supports the HMC5843 and HMC5883

## ESCs ##

You can use cheap DC brushless motor ESCs which communicate using RC PWM signals, or ones which communicate via the I2C bus. The Ro4Copter PCB supports both kinds.

AeroQuad derived code supports both kinds

MultiWiiCopter derived code does NOT support the I2C type

## Remote Control ##

The Ro4Copter PCB can let you plug in 6 channels of RC signals, or one PPM sum signal. Both these configurations are supported by the code derived from AeroQuad and code derived from MultiWiiCopter

## Auxiliary/Camera Servos ##

You can plug in more servos to the Ro4Copter PCB. Most people use extra servos to move around an on-board camera.

I've added some code to the original AeroQuad code so you can add in 4 servos designated for controlling a camera.

There's some pin definitions in the MultiWiiCopter code that I've changed so you can plug in extra servos.

## Battery Monitor ##

You can measure your current battery level, and perhaps perform some sort of action based on the measurement.

Both the code derived from AeroQuad and MultiWiiCopter supports this.

## Bluetooth and XBee ##

Both AeroQuad and MultiWiiCopter are configured and tuned through a GUI utility, but this requires a serial connection, typically using a USB-to-serial cable.

Ro4Copter's PCB has connectors for an XBee module or Bluetooth Mate or BlueSMIRF, these devices act as wireless serial ports, so you can monitor your aircraft while in the air, and configure/tune your settings without a cable (I highly suggest you land before doing any tuning, regardless of having wireless communication)