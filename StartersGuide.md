# Starters Guide #

This page is intended for people who just want a inexpensive quadcopter that flies with minimal work. This will detail the bare recommended minimum setup for Ro4Copter's PCB.

I won't go into too much detail here because I'm not the best person to write them. I'm more focused towards the electronics design of Ro4Copter. If you want to learn more about anything, this [mega link index on RC Groups](http://www.rcgroups.com/forums/showthread.php?t=1097355) is an awesome resource.

Skills I'll assume you already have:
  * Understand how a quadcopter works
  * How to use Arduino, compile and upload using the IDE
  * How to use an AVR programmer to program in a bootloader if you need it
  * How to solder stuff, wire stuff, basic electronics
  * How to use a drill, screw driver, and other basic hand tools


## The Target Design ##

Since you are just starting out, we won't get into any fancy "mini" or "micro" configurations. I will try and describe a design that will be about as big as a pizza.

## Circuit Board ##

Assemble the circuit board following the guide.

Ignore all components related to voltage level shifting for the serial ports.

Select SER0 with SJ9 and SJ10.

Choose the option for SJ2 depending on your RC receiver (most likely 5V, but double check).

Don't bother with the native USB components.

For this minimal setup, don't bother with battery monitoring related stuff. You don't even need to connect the battery to the PCB. Make sure you bridge SJ1 so that the ESCs are supplying 5V into the main power bus.

## Frame ##

You can buy cheap quadcopter frames online. Buy one that will fit the Ro4Copter PCB. I know Hobby King sells a $14.99 quadcopter frame kit that's made of laser-cut wood. That's pretty cheap considering two sticks of aluminum would end up costing just as much at Home Depot.

Once you get it, assemble it. Mount your motors to it with machine screws, and mount the PCB as well. It's easy to mount the Ro4Copter PCB on to any frame because of the slots cut on each corner. I can't tell you exactly how to do it since there are many different frames, but the general idea is to screw down the PCB to the frame with some sort of standoff in between.

Everything else (ESCs, wires, battery, etc) you should mount using light weight materials (screws are pretty heavy once you use a lot of them), think of velcro or rubber bands, tape and zip-ties also work but they are more permanent.

Links that might interest you
  * [AeroQuad Wiki: Frame FAQ](http://www.google.com/search?q=site:aeroquad.com+wiki+Frame+FAQ&btnI)
  * [AeroQuad Wiki: Frame Materials](http://www.google.com/search?q=site:aeroquad.com+wiki+Frame+Materials&btnI)
  * [MultiWiiCopter: A design guide - How to build a MultiCopter](http://www.google.com/search?q=site:multiwiicopter.comA+design+guide+How+to+build+a+MultiCopter&btnI)

## Four is the Magic Number ##

You need four brushless motors, ESCs, and propellers.

Links that might interest you
  * [AeroQuad Wiki: Motors and Propellers FAQ](http://www.google.com/search?q=site:aeroquad.com+wiki+Motors+and+Propellers+FAQ&btnI)

### Motors ###

First, just do some quick research on the Internet to see what motors are popular and are known to work well. Also I have some information about various [motor thrust and power specifications here](MotorSpecs.md).

### Propellers ###

You need two pairs (thus 4 total) of counter-rotating propellers. You need them to be counter-rotating pairs because if they all spun in the same direction, you would not be able to control rotation about the yaw (vertical) axis. Read the [Wikipedia article about quadcopters](http://en.wikipedia.org/wiki/Quadrotor) to understand.

I have used the EPP1045 before, which is 10 inches in diameter. You can use a smaller propeller for a lighter design, or a larger one for a heavier design. Obviously you'll need more power with heavier designs and larger propellers.

Make sure that the propellers will fit on the shaft of the motors somehow. You need to find various adapters or "prop-savers" to do this. The propellers I use have a 3 mm diameter hole, and my motors have a 3 mm diameter shaft, and I use a 3 mm prop-saver to hold them in place.

### ESCs ###

The ESCs must be able to handle the current drawn by your motors. For most quadcopters, 18 amp each should work. This should cost about $10 each, I've seen them as low as $6 each.

It's nice to get a ESC that also uses a "programming card" to configure it but it's not a requirement. Some of them you program by using your RC radio instead of a card.

Wiring up these is dead simple. There are usually 8 wires. Two goes to your battery to get the power. Three goes to your brushless motor. The last three is the control signal wire that plugs into the Ro4Copter PCB where it says "ESC-FRONT" "ESC-BACK" "ESC-LEFT" "ESC-RIGHT".

If the motor is not spinning in the right direction, simply swap the connection between two of the three wires between the motor and the ESC.

### Orientation ###

This is known in AeroQuad code as "plus configuration". Note that the PCB has an arrow that indicates which corner points forward. Also take note of which propeller should spin in which direction.

<img src='http://frank.circleofcurrent.com/junk/aq64_img/propellerdirections.png' />

## Remote Control ##

Get a RC transmitter and receiver with 6 channels, they are about $30 now for a 2.4 GHz system with 6 channels. Plug in all 6 channels into the Ro4Copter PCB where it says RC 1 to 6. Do this while following the [pin assignments](ConnectionSummary.md).

Don't worry if you get this wrong, you can always just look at the channels on your computer and swap the wires if the wrong channel responds. Or you can just make some small re-assignments in the source code.

Make sure your RC receiver is powered. Some are powered from the channel connections, some others have a dedicated connection just for power. Remember that the Ro4Copter PCB has power-tap connectors that you can use.

Links that might interest you
  * [AeroQuad Wiki: Control Equipment FAQ](http://www.google.com/search?q=site:aeroquad.com+wiki+Control+Equipment+FAQ)

## Power System ##

You need a 3 cell lithium polymer battery (3S meaning 3 cells in series, P means parallel). Get a battery rated for at least 20C discharge rate. Buy the appropriate connector for your battery (this really depends on the battery) and solder wires to the connector.

Lithium polymer batteries are a touchy subject, you should read this: [RC Groups: Complete Guide to Lithium Polymer Batteries](http://www.rcgroups.com/forums/showthread.php?t=209187)

If you don't have a charger, obviously you'll need to get one.

You need wire as least as thick as the wires used on the ESCs. Any decent ESC will use wires that can handle the current that they are rated for so following this rule will make sure your wire can handle the same current.

Get a power switch between the battery and everything else. Alternatively, you can always just keep un-plugging your battery to turn off your quadcopter but this becomes a pain. (But some people don't put a switch because they are extra weight)

Now connect the power to the four ESCs, it sounds simple, but make sure you do a good job that is solid and well insulated. These batteries can explode if you short circuit them.

You don't need to connect the battery to the Ro4Copter PCB since the ESCs will be providing power to the PCB instead, remember?

## Sensors ##

I think for the most basic setup, just go to SparkFun and buy the 6 DOF IMU combo board since it combines both the ITG-3200 gyro and ADXL345 accelerometer.

## Other Electronics ##

You're going to need a serial connection, so get a USB-to-serial cable such as the FTDI cable or a similar product.

You'll probably need an AVR programmer to load the firmware to the ATmega644PA.

## Generalized Wiring Diagram ##

<img src='http://frank.circleofcurrent.com/junk/aq64_img/generalwiringdiagram.png' />

## Software Setup ##

Read "[general software setup](GeneralSoftwareSetup.md)" first.

You need to choose between AeroQuad or MultiWiiCopter software, but since you are reading this "starter's" guide, just go with AeroQuad.

Now configure the software source code [following the guide](AeroQuadDerivedCodeSetup.md), keeping in mind what we've done so far so you know what features to enable or disable, and what selections we have made.

Compile it and upload the binary to the ATmega644PA using an AVR programmer or the bootloader. Connect to the ATmega using the serial cable and run the configuration utility (AeroQuad Configurator). [Follow the instructions for that utility](http://www.google.com/search?q=site:aeroquad.com+wiki+AeroQuad+Configurator+Manual&btnI) (but keep in mind the differences between Ro4Copter's PCB and AeroQuad's electronics).

Some more [AeroQuad wiki pages](http://aeroquad.com/showwiki.php) you must read:
  * [Setup and Calibration](http://www.google.com/search?q=site:aeroquad.com+wiki+Setup+and+Calibration&btnI)
  * [Pre-Flight Checkout List](http://www.google.com/search?q=site:aeroquad.com+wiki+Pre+Flight+Checkout+List&btnI)
  * [PID Tuning](http://www.google.com/search?q=site:aeroquad.com+wiki+PID+Tuning&btnI)
