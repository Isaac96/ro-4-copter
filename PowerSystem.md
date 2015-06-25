## Battery ##

A three cell (3S1P, 11.1 volts) lithium polymer battery with a 20C discharge rate should be used.

At the time of writing this wiki entry, Hobby King offers a decent [3S1P 20C 5000mAH battery](http://www.hobbyking.com/hobbycity/store/uh_viewItem.asp?idProduct=8579) for $26.72.

A [three cell battery monitor](http://www.hobbyking.com/hobbycity/store/uh_viewItem.asp?idProduct=4175) is recommended to prevent damage to a lithium polymer cell if one cell becomes too depleted. It is also recommended that the connector on this particular battery monitor be replaced by a matching connector (4 pin JST-XH) to prevent the user from plugging in the battery backwards. This battery monitor should be mounted on the frame using adhesive-backed velcro.

A three cell balance charger is required to charge the battery pack.

Remember, using polarized connectors will save you from a lot of headaches and explosions!

## Power Requirements ##

A graph depicting expected flight times is shown on [this forum thread](http://www.rcgroups.com/forums/showthread.php?t=768115). Here is a [direct image link](http://www.af9y.com/PowerChart.jpg).

The graph also shows that one ounce of flight weight would need one watt of power, and the two are linearly correlated. Assuming the craft is 60 ounces, 60 watts of power is needed.

Assuming a 11.1V battery is used, this means the average current draw is roughly 5.4 amps.

Assuming a 7.4V battery is used (which is unlikely but possible), this means the average current draw is roughly 8.1 amps.

## Power Regulation ##

The ESCs are connected to the battery directly, and a 5V output is provided on their control wire. This is used to power the flight controller. The four ESCs should be able to provide enough power for several servos as well.

A 3.3V voltage regulator is required for the IMU sensors.

## Power Distribution ##

The power from the battery needs a wire to be split for each ESC. This is done by a terminal block strip. This is the most durable way since the strip can be bolted to the frame and no soldering or electrical tape is required during construction or repairs.

## Power Switch ##

A SPST switch capable of 20A or more should be adequate. A switch with a screw terminal is preferable due to their durable nature.