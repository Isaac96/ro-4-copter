# Pin Assignments #

Here is the pin chart for the ATmega644PA on the Ro4Copter PCB

|LED1, detecting USB cable presence|Digital 0 (Debug LED)|PB0|1|`+--v--+`|40|PA0, ADC0|Digital 31, Analog 0|Battery Monitor|
|:---------------------------------|:--------------------|:--|:|:--------|:-|:--------|:-------------------|:--------------|
|LED2, USB bus D-                  |Digital 1            |PB1|2|`o`      |39|PA1, ADC1|Digital 30, Analog 1|GPIO, do anything|
|LED3, USB bus D+                  |Digital 2            |PB2, INT2|3|         |38|PA2, ADC2|Digital 29, Analog 2|GPIO, do anything|
|SERVO1 (camera pitch)             |Digital 3 (PWM)      |PB3|4|         |37|PA3, ADC3|Digital 28, Analog 3|GPIO, do anything|
|SERVO2 (camera roll)              |Digital 4 (PWM)      |PB4|5|         |36|PA4, ADC4|Digital 27, Analog 4|GPIO, do anything|
|SERVO3 (camera yaw), MOSI         |Digital 5            |PB5, MOSI|6|         |35|PA5, ADC5|Digital 26, Analog 5|GPIO, do anything|
|SERVO4 (camera aux), MISO, BOOT button|Digital 6            |PB6, MISO|7|         |34|PA6, ADC6|Digital 25, Analog 6|GPIO, do anything|
|SCK                               |Digital 7            |PB7, SCK|8|         |33|PA7, ADC7|Digital 24, Analog 7|GPIO, do anything|
|RESET                             |                     |RESET|9|         |32|AREF     |                    |AREF           |
|VCC                               |                     |VCC|10|         |31|GND      |                    |GND            |
|GND                               |                     |GND|11|         |30|AVCC     |                    |AVCC           |
|XTAL2                             |                     |XTAL2|12|         |29|PC7, PCINT23|Digital 23          |RC-IN-6, Auxiliary|
|XTAL1                             |                     |XTAL1|13|         |28|PC6, PCINT22|Digital 22          |RC-IN-5, Gear  |
|SER0 RX                           |Digital 8, RX0       |PD0, RXD0|14|         |27|PC5, PCINT21|Digital 21          |RC-IN-4, Pitch/Rudder|
|SER0 TX                           |Digital 9, TX0       |PD1, TXD0|15|         |26|PC4, PCINT20|Digital 20          |RC-IN-3, Roll/Elevator|
|SER1 RX                           |Digital 10, RX1      |PD2, RXD1|16|         |25|PC3, PCINT19|Digital 19          |RC-IN-2, Yaw/Aileron|
|SER1 TX                           |Digital 11, TX1      |PD3, TXD1|17|         |24|PC2, PCINT18|Digital 18          |RC-IN-1, Throttle, PPM|
|ESC-BACK                          |Digital 12 (PWM)     |PD4, OC1B|18|         |23|PC1, SDA |Digital 17          |SDA            |
|ESC-RIGHT                         |Digital 13 (PWM)     |PD5, OC1A|19|         |22|PC0, SCL |Digital 16          |SCL            |
|ESC-FRONT                         |Digital 14 (PWM)     |PD6, OC2B|20|`+-----+`|21|PD7, OC2A|Digital 15 (PWM)    |ESC-LEFT       |

Of course, a lot of this is configurable in the source code.

# The Common 3-Pin Cable #

Hey you! Are you about to plug something in? Take a look at this:

<img src='http://frank.circleofcurrent.com/junk/aq64_img/3pinservoref1.png' />

DO NOT EVER SCREW THIS UP!