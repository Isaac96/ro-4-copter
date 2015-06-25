# MultiWiiCopter Derived Sketch #

So I've taken a look at MultiWiiCopter, and I tried to make Ro4Copter compatible with it. An untested sample modification of MultiWiiCopter version 1.7 is included in the download above. Most features are supported, you should read through the code to see how it is configured differently. The matching GUI configurator utility should also be compatible.

MultiWiiCopter is developed in a more C sytle as opposed to C++ like AeroQuad. MultiWiiCopter's code appears more compact, neat, and efficient. Also everything is done in one file.

Most configuration is already described in detail if you read the sketch file. I will only cover the bits that require attention with regards to Ro4Copter. Do a search for "Ro4Copter" in the source code to find the related code.

## Source Code Configuration ##

You must decide what features you want, and configure the source code correctly before compiling and uploading the firmware to the microcontroller. The steps are very similar to how you would configure the original AeroQuad source code.

### Aircraft Configuration ###

Most of the configurations (plus, X, bi, tri, hex, etc) should be supported. Look under "type of multicopter" to pick one.

### Remote Control ###

Connect your RC receiver to the RC input pins, preferably in the order shown in the pin chart. You can also change the pin assignments in the source code, look for

```
#define THROTTLEPIN                2
#define ROLLPIN                    4
#define PITCHPIN                   5
#define YAWPIN                     3
#define AUX1PIN                    6
#define AUX2PIN                    7
```

Also PPM sum signals can also be used, look for `SERIAL_SUM_PPM` in the source code

### Flight Sensors ###

#### Gyro ####

MultiWiiCopter supports two gyroscope sensors but we are only interested in the ITG-3200 here since it's the one supported by the Ro4Copter PCB, so enable that in the source code. Look for `#define ITG3200` to select this.

#### Accelerometer ####

Both the ADXL345 and BMA180 are supported by the MultiWiiCopter code and the Ro4Copter PCB, look under `/* I2C accelerometer */` to select one.

#### Barometer ####

The BMP085 is supported by the MultiWiiCopter code and the Ro4Copter PCB, look under `/* I2C barometer */` to activate it if you have one installed.

#### Compass ####

Both the HMC5843 and HMC5883 are supported by the MultiWiiCopter code and the Ro4Copter PCB, look under `/* I2C magnetometer */` to select one if you have one installed.

### Battery Monitor ###

If you have the battery monitoring circuit soldered, then you can enable battery monitoring, look for `#define VBAT` in the code for more details.

### Wireless ###

If you want to use wireless modules such as XBee or Bluetooth:
  * Make sure that the baud rate is setup correctly in both the modules and the source code
    * Look for `SERIAL_COM_SPEED` in the source code
  * Select SER0 using the solder jumpers, just because MultiWiiCopter is designed for ATmega328P which only has one serial port

That's about it

### ESCs and Servos ###

MultiWiiCopter is designed not just for quadcopters, but it can do bi-, tri-, hex- copters too, some of the configurations also require servos.

Look under the pin assignment section to figure out where to plug stuff in. I have already changed most of them to work with Ro4Copter.
