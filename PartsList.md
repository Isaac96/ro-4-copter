# Part List #

Note that in this list, all components are listed regardless of whether or not you need them.

SparkFun breakout boards, XBee, Bluetooth Mate, and FTDI cables are not listed.
Quadcopter parts such as ESCs, RC receivers, battery, etc, are not listed

|Part|Other Attributes|Identifiers|Quantity Required|Example Product|
|:---|:---------------|:----------|:----------------|:--------------|
|ATmega644PA|40 pin plastic DIP|IC1        |1                |Digikey: ATMEGA644PA-PU-ND|
|40 pin DIP socket|                |IC1        |1                |Digikey: A411-ND|
|4K7 ohm resistor|0805 or 0603 packaging, 1/16 W minimum|`R`1, `R`2, `R`9, `R`10|4                |Digikey: P4.7KACT-ND|
|10K ohm resistor|0805 or 0603 packaging, 1/16 W minimum|`R`8, `R`11, `R`13|3                |Digikey: P10KACT-ND|
|68R ohm resistor|0805 or 0603 packaging, 1/16 W minimum|`R`14, `R`15|2                |Digikey: P68ACT-ND|
|2K2 ohm resistor|0805 or 0603 packaging, 1/16 W minimum|`R`16      |1                |Digikey: P2.2KACT-ND|
|15K ohm resistor|0805 or 0603 packaging, 1/16 W minimum|`R`6       |1                |Digikey: P15KACT-ND|
|7K5 ohm resistor|0805 or 0603 packaging, 1/16 W minimum|`R`7       |1                |Digikey: P7.5KACT-ND|
|1K ohm resistor|0805 or 0603 packaging, 1/16 W minimum|`R`3-5, `R`12|4                |Digikey: P1.0KACT-ND|
|1 uF capacitor|ceramic, 0805 or 0603 packaging, 16V rating minimum|C3, C4     |2                |Digikey: 311-1358-1-ND|
|0.1 uF capacitor|ceramic, 0805 or 0603 packaging, 16V rating minimum|C1, C2, C7, C8, C9|5                |Digikey: 311-1361-1-ND|
|33 uF capacitor|electrolytic, 5.3 mm x 5.3 mm SMD aluminum can, 16V rating minimum|C5, C6     |2                |Digikey: PCE3886CT-ND|
|4u7 capacitor|tantalum, 1210 package, rated 6V minimum|C10        |1                |Digikey: 478-3887-1-ND|
|1N4148 diode|MELF packaging  |D1         |1                |Digikey: LL4148DICT-ND|
|Rectifier Diode|SMB packaging, 20V reverse voltage minimum, high forward current rating|D2         |1                |Digikey: SSB44-E3/52TGICT-ND|
|3V6 zener diode (1N5227B)|MELF packaging, 500 mW rating|D3, D4     |2                |Digikey: ZMM5227BDICT-ND|
|16 MHz resonator|                |Y1 (16 MHz on PCB)|1                |SparkFun: COM-09420|
|Male headers|0.1 inch pitch  |ESC, I2C, I2C-GROUP, BARO, ACCEL, IMU, GYRO, MAG, BATTERY, BATT-MON, ADC1-7, RC1-6, 5V-TAP, 3V3-TAP, SERIAL, FTDI, maybe BLUETOOTH|Buy long strips and break them off|               |
|2x3 male headers|0.1 inch pitch, no shroud allowed|AVRISP     |1                |Use the male headers you buy|
|TXB0101 bidirectional level shifter|SOT-23-6 package|IC4, IC5   |2                |Digikey: 296-21664-1-ND|
|Tactile momentary push button switch SPST|Right angle, 7.50mm x 7.10mm|RESET, BOOT|2                |Digikey: P12232SCT-ND|
|5V regulator|SOT223, SOT-223-3 package|5V-REG     |1                |LM1117MPX-5.0  |
|3V3 regulator|SOT223 package  |3V3-REG    |1                |LM1117MPX-3.3  |
|LED |3 mm, any colour|LED1-4     |4                |SparkFun: COM-00533|
|Barrel jack|                |Battery    |1                |SparkFun: PRT-00119|
|USB mini-B female connector|Surface mount   |USB        |1                |SparkFun: PRT-00587|
|2mm female pin headers|                |Xbee       |2                |SparkFun: PRT-08272|

### [IMPORTANT NOTE](UsbTesting.md): `R`14, `R`15, `R`16, USB, D3, D4, C10, are useless if you are using a 16 MHz ceramic resonator, I found out this after testing ###