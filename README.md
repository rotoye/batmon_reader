
# Rotoye Batmon

## _The Dumb-Battery Era is Over_

[![](https://camo.githubusercontent.com/8552c5280963ba768ce83da9ed6a53c3a2b3f103/68747470733a2f2f6c68332e676f6f676c6575736572636f6e74656e742e636f6d2f4834375333664565756f6f695073486e5648323938776e7750724e365264515a474b764a557a6c352d685133384161587a576c61527a52776278464d6e6d33347a70494e344635632d6d3435 "Rotoye Batmon 2.2")](https://camo.githubusercontent.com/8552c5280963ba768ce83da9ed6a53c3a2b3f103/68747470733a2f2f6c68332e676f6f676c6575736572636f6e74656e742e636f6d2f4834375333664565756f6f695073486e5648323938776e7750724e365264515a474b764a557a6c352d685133384161587a576c61527a52776278464d6e6d33347a70494e344635632d6d3435)

## Getting Started

When you receive a battery with integrated Batmon, the OLED display (if applicable) and red/green LED's should be flashing periodically, displaying the battery state of charge, the min and max cell voltages, and current in Amps. The button is used to cycle through screens. Batmon will default back to the periodically flashing screen after some time to conserve energy; the lower the state of charge, the less frequently data will be displayed.

_**If you see the < ! > symbol on the OLED display, this means that one or more safety warning conditions have been met. Press the button to see the warning(s) present.**_

### Buzzer/OLED board
![](http://batmonfiles.rotoye.com/userguide/OLED_buzzer_board.png)
The optional OLED display/buzzer attachment extends Batmon functionality by providing a user-friendly interface for displaying state of charge, voltages, warnings, and more. The small board is attached to the main Batmon board via a small connector. 

**Warning: this connector is rated for a limited number of plug-unplug cycles. It is recommended to attach/detach this accessory as little, and as carefully as possible.**

## Interfacing with an Autopilot

### Wiring to autopilot

You’ll notice that the XT90 on a Batmon equipped smart battery, while compatible with all XT90 connectors, is not standard. The two small pins in the middle of the connector are for interfacing with an autopilot via an opto-isolated I2C connection.

Connect the smart battery and I2C opto-isolator board to one of the autopilot’s I2C ports as shown: 

![Batmon wiring](http://batmonfiles.rotoye.com/userguide/wiring.png)

### Wiring to cells

[![](https://raw.githubusercontent.com/rotoye/batmon_reader/ArduinoAsMaster/HARDWARE/Batmon-pcb.jpg)](https://raw.githubusercontent.com/rotoye/batmon_reader/ArduinoAsMaster/HARDWARE/Batmon-pcb.jpg)

Follow the schematics from [https://github.com/rotoye/batmon_reader/blob/ArduinoAsMaster/HARDWARE/6-10%20Cell%20Connection%20schematic.pdf](https://github.com/rotoye/batmon_reader/blob/ArduinoAsMaster/HARDWARE/6-10%20Cell%20Connection%20schematic.pdf) to remove the jumpers before connecting any battery to BatMon

_**If cell voltage is applied across any cell jumpers, they will short the cell and blow. Please check that your pack configuration corresponds appropriately to the jumpers.**_

### PX4
#### Stable

Clone or download [Rotoye's fork of PX4](https://github.com/rotoye/px4_firmware_batmon)

Checkout the batmon_v2.02 branch

[Build and upload](https://dev.px4.io/v1.9.0/en/setup/building_px4.html) the firmware according to PX4 documentation instructions

In ground control software of choice, set the BAT_SOURCE parameter to "External," and set SENS_EN_BAT to true

Start the batt_smbus [script](https://dev.px4.io/v1.9.0/en/middleware/modules_driver.html)

[![](https://camo.githubusercontent.com/4f57fdfe4af663bcc7d0dcd78faa980823dc97ec/68747470733a2f2f6c68352e676f6f676c6575736572636f6e74656e742e636f6d2f32625263586a7864547164626f6a367157534b6b7768744a4f466f75326f486859524a7a6b415957696b5f766f727a494431612d324b35654f356b39724d456f644f6742754d5038312d43327646304c785644527356364a374f6c5847456a49632d33645a6677566a6f7868413564544850594b564a42733135685a726950644f31486976525a4b)](https://camo.githubusercontent.com/4f57fdfe4af663bcc7d0dcd78faa980823dc97ec/68747470733a2f2f6c68352e676f6f676c6575736572636f6e74656e742e636f6d2f32625263586a7864547164626f6a367157534b6b7768744a4f466f75326f486859524a7a6b415957696b5f766f727a494431612d324b35654f356b39724d456f644f6742754d5038312d43327646304c785644527356364a374f6c5847456a49632d33645a6677566a6f7868413564544850594b564a42733135685a726950644f31486976525a4b)

#### Beta
*PX4 v1.11.0 is still in Beta; as such, so is BatMon support*
Clone or download [Rotoye's fork of PX4:](https://github.com/rotoye/px4_firmware_batmon)
    
Checkout the batmon_v2.02_px4_v1.11 branch
    
Build and upload the firmware according to [PX4 documentation instructions](https://dev.px4.io/master/en/setup/building_px4.html)
    
In ground control software of choice, set the BATx_SOURCE parameters to "External", and set SENS_EN_BAT to true
    
Start the batt_smbus [script](https://dev.px4.io/master/en/middleware/modules_driver.html) on NuttShell

For example, running two BatMons on the same bus:

`batt_smbus start -X -b 1 -a 11` * External bus 1, address 0x0b  
`batt_smbus start -X -b 1 -a 12` * External bus 1, address 0x0c

### Ardupilot

Clone or download [Ardupilot firmware](https://github.com/ArduPilot/ardupilot)

Check out the master branch, [build from source](https://ardupilot.org/dev/docs/building-the-code.html), and flash the firmware. **Batmon support is not yet in a stable release of Ardupilot.** 

In ground control software of choice, manually set the BATTx_MONITOR parameter to 19 (or select Rotoye by name, if enumerated), and select the appropriate BATTx_BUS (0-3), where *x* is the Batt number (multiple Smart Batteries can be used at once!)

See the [full list](https://ardupilot.org/copter/docs/parameters.html#batt2-parameters) of parameters for more detail [![](https://camo.githubusercontent.com/4e0d13de8634b0ae88226aba1f015ae81a342f7f/68747470733a2f2f6c68362e676f6f676c6575736572636f6e74656e742e636f6d2f6a477257786b4d4b6f384e495f49764f6d6d665a6a334f6c644b4537477051666c5253756c6f45514b3652456b30797a47325a6e717244506f6d48565479574d68386e7447594838476c533139774d5f736d6c4438495732717a6e324f544d4346756d772d7243674e4c2d46496936596b7032785f717853724a506a7337316d747573564d336454)](https://camo.githubusercontent.com/4e0d13de8634b0ae88226aba1f015ae81a342f7f/68747470733a2f2f6c68362e676f6f676c6575736572636f6e74656e742e636f6d2f6a477257786b4d4b6f384e495f49764f6d6d665a6a334f6c644b4537477051666c5253756c6f45514b3652456b30797a47325a6e717244506f6d48565479574d68386e7447594838476c533139774d5f736d6c4438495732717a6e324f544d4346756d772d7243674e4c2d46496936596b7032785f717853724a506a7337316d747573564d336454)

### Ground Control:

You should now be able to verify through a tool such as MAVLink Inspector in QGroundControl that Batmon is sending data to the autopilot: [![](https://camo.githubusercontent.com/b2bfaff53eeb6a400d0f91813a3dc36f3d63df9a/68747470733a2f2f6c68352e676f6f676c6575736572636f6e74656e742e636f6d2f56304a737455317947524632544435665f6a4730725464314730414f64796c6e4261334d786b454257444472425549396d687563714430794c5936506b4c38614d49694e67734f4a77345576334a5054476753562d336e4d647045595f796f4d6a6c692d79725044547165346c315268534d697044694b6478314c643964465171676a3061334c7a)](https://camo.githubusercontent.com/b2bfaff53eeb6a400d0f91813a3dc36f3d63df9a/68747470733a2f2f6c68352e676f6f676c6575736572636f6e74656e742e636f6d2f56304a737455317947524632544435665f6a4730725464314730414f64796c6e4261334d786b454257444472425549396d687563714430794c5936506b4c38614d49694e67734f4a77345576334a5054476753562d336e4d647045595f796f4d6a6c692d79725044547165346c315268534d697044694b6478314c643964465171676a3061334c7a)

## Arduino Library:

### ReadBatmon: Arduino code to access the Batmon battery monitor.

Instruction to run ReadBatmon

-   Copy the ReadBatmon folder to local directory.
-   Open the sketch using Arduino IDE.
-   Open Sketch->Include Library-> Add .ZIP library
-   Give location of FastCRC.zip file. The FastCRC library would now be added.
-   Connect the Power, GND, SDA, SCL lines from Arduino to Batmon
-   Connect the cells to Batmon pcb as given by [6-10 cell connection schematic](https://github.com/rotoye/batmon_reader/blob/ArduinoAsMaster/HARDWARE/6-10%20Cell%20Connection%20schematic.pdf)
-   Upload code to Arduino
-   Run serial monitor to see output
