# AeroQuad Derived Sketch #

The sketch itself is a heavily modified version of AeroQuad Flight Software V2.4 , which requires the special Arduino core developed for the Ro4Copter PCB.

When a new version of AeroQuad becomes available, I will synchronize the changes between it and Ro4Copter's source code. It is also my hope that the AeroQuad developers will accept my changes into their official distribution someday.

The AeroQuad Configurator should be able to connect to Ro4Copter if this sketch is used. This sketch will mimic a AeroQuad shield of the "Mega" variant.

## Source Code Configuration ##

You must decide what features you want, and configure the source code correctly before compiling and uploading the firmware to the microcontroller. The steps are very similar to how you would configure the original AeroQuad source code.

### Mounting Orientation ###

The Ro4Copter PCB supports both X and + configurations, see `Ro4Copter_AeroQuad.pde` about `#define XConfig` and `#define plusConfig`.

### Remote Control ###

Connect your RC receiver to the RC input pins, preferably in the order shown in the pin chart. You can also change the pin assignments in the source code if you edit `Receiver.h`

There's some experimental code that uses the first RC input to take in RC PPM signal instead of regular RC PWM signal. To enable this, enable "R4C\_OPTION\_USE\_RC\_PPM" in `Ro4Copter_AeroQuad.pde`. The channel ordering is done in `Receiver.h` under `Receiver_Ro4Copter_PPM`.

If you are not using PPM signals, then just enable "R4C\_OPTION\_USE\_RC\_PWM".

### Flight Sensors ###

Note: the original AeroQuad code has been changed to disable the AVR's internal pull-up resistors which would be activated incorrectly by the Wire library, this is so that the I2C bus can operate at 3V3 using the `R`1 and `R`2 as external pull-up resistors. The Wire library never accounted for the possibility of using an ATmega644PA so it enables internal pull-up resistors on the wrong pins, this is reverted manually in the new code.

#### Gyro ####

No choices need to be made here since all you can use is the ITG-3200 at the moment.

See `Ro4Copter_AeroQuad.pde` about `#define FlightAngleARG`, or `#define FlightAngleMARG` if a compass is used.

#### Accelerometer ####

The 6 DOF IMU breakoutboard uses a ADXL345, while the BMA180 breakout board obviously uses a BMA180.

see `Ro4Copter_AeroQuad.pde` about `#define FlightAngleARG`, or `#define FlightAngleMARG` if a compass is used. Choose between the two different accelerometers using `R4C_OPTION_USE_BMA180_ACCEL` or `R4C_OPTION_USE_ADXL345_ACCEL`.

#### Barometric Pressure Sensor ####

Please read `Ro4Copter_AeroQuad.pde` about the `AltitudeHold` definition, which you need to enable if you've installed this sensor.

#### Magnetic Compass ####

There is a footprint available for the HMC5842 hall effect sensor. This sensor can measure the Earth's magnetic fields to determine the current magnetic heading of the helicopter. It is then able to keep that direction constantly. You need to enable this in the source code.

Please read `Ro4Copter_AeroQuad.pde` about the `HeadingMagHold` and `FlightAngleMARG` definitions, which you need to enable.

#### Others ####

The footprint for the ITG-3200 breakout board actually fits the IMU3000 breakout board from SparkFun, and the pins are compatible. Somebody just needs to write the software for it.

### Battery Monitor ###

If you have installed the components for the battery monitor circuit, then you can enable battery monitoring in the source code.

Enable the `BattMonitor` definition in `Ro4Copter_AeroQuad.pde` if you want to use this capability.

Please see `BatteryMonitor.h` , where you can program the behaviour of the helicopter when the battery voltage reaches a certain level. For example, you can program it to slowly land, flash warning lights, etc.

You also need to get the precise measurements of the components used in your battery monitoring circuitry, this means the voltage drop across D1, and the true values of `R`6 and `R`7. Put these values where indicated in `BatteryMonitor.h` .

### Wireless ###

There's a place to put down a XBee module, and a place to put a Bluetooth Mate or BlueSMIRF module. See the hardware assembly guide about how to route the serial port signals to these connectors.

The XBee setup is similar to how you would have done it for the original AeroQuad (read: [XBee installation guide for AeroQuad](http://aeroquad.com/showwiki.php?title=Xbee+Installation)), and the Bluetooth setup should be done according to the instruction provided for the module you are using.

### ESCs ###

Take a look at `Motors.h` for more information about using ESCs (both PWM and I2C variants).

I've added definitions in `Ro4Copter_AeroQuad.pde` called `R4C_OPTION_USE_PWM_ESC` and `R4C_OPTION_USE_I2C_ESC` so you can choose between them.

### Camera or Auxiliary Servos ###

I have made some changes to `Camera.h` to add a new camera class called "`Ro4Copter_Camera`" which uses my servo code (called SoftServo) included in the core. `Ro4Copter_AeroQuad.pde` will create an instance of this new class and use it in a similar fashion as how cameras are controlled in the origial AeroQuad.

If you want the servos to do something else besides controlling a camera, the class is still "camera" but you simply use it for your own application. Use your head.

If you want direct RC control from your RC transmitter to the servo, this should not be done by the Ro4Copter PCB or software, instead you should be connecting your RC receiver directly to the servo instead.

Feel free to disable the camera code if you want to use those pins for something else.

## Other Stuff ##

The original AeroQuad code has some other code, such as for GPS, data logging, and others.

If you want to experiment with these, remember that I have incorporated auxiliary I2C, serial ports, GPIOs of all kinds, and SPI can be accessed through the ISP header.

USART0 is called "`Serial`" and USART1 is called "`Serial1`", remember that!

If you decide to use the PORTA GPIOs with jumper shunt blocks, you can modify the source code such that you compile all the options and use the blocks to select the option at runtime, so you don't have to constantly recompile in the field.