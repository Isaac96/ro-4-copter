# Jumper Configuration Summary #

<img src='http://frank.circleofcurrent.com/junk/aq64_img/solderjumpers1.png' />

|AREF-SEL|Selects the analog reference voltage between 3V3 and 5V|
|:-------|:------------------------------------------------------|
|SJ1     |Joins the 5V from RC pulse ESCs to the 5V system power supply|
|SJ2     |Selects 5V or 3V3 for the RC receiver signals          |
|SJ3     |Joins the power from I2C ESCs to either the 5V RC pulse ESCs power, or to 3V3 power. Alternatively, if you wish to use only 3 wires to connect to I2C ESCs, then short the V+ pins of the I2C-GROUP headers with the ground pins, and DO NOT use SJ3 at all.|
|SJ4     |Selects 5V from the system supply or 5V from the ESCs for the auxiliary servos|
|SJ5     |Selects 5V or 3V3 for the auxiliary I2C device connector|
|SJ6     |Selects the voltage supplied to the auxiliary serial device, either 5V or 3V3|
|SJ7 and SJ8|Selects between SER0 and SER1 for the bluetooth connector|
|SJ9 and SJ10|Selects between SER0 and SER1 for the FTDI cable connector|
|SJ11 and SJ12|Selects between SER0 and SER1 for the XBee             |
|SJ13 and SJ14|Selects between SER0 and SER1 for the auxiliary serial device|
|SJ15    |Allows you to join the center pin of the PORTA headers to the same power used by the RC signal input headers, or to ground so you can use them with jumper shunt blocks.|
|SJ16    |Selects between supplying 5V or 3V3 to the auxiliary serial device|
|SJ17    |Selects either the 5V from the ESCs or the 5V from the system power supply for the headers connected to PORTA|
|SJ18    |Joins the 5V from the USB bus to the 5V system power   |

Important: If you select ground for SJ15, then do not select anything using SJ17, doing so will short-circuit the power supply connected to SJ17 with ground, which can cause damage to the various power supply components.

Important: If you select V-RC with SJ15 (to use the same voltage that the RC inputs are using) and you have selected 3V3 using SJ3, then you must not use SJ17 to select anything. Doing so will cause the 5V supply to be joined with the 3V3 supply, which can cause damage to 3V3 devices.