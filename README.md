
# Rotoye Batmon

## _The Dumb-Battery Era is Over_

[![](https://camo.githubusercontent.com/8552c5280963ba768ce83da9ed6a53c3a2b3f103/68747470733a2f2f6c68332e676f6f676c6575736572636f6e74656e742e636f6d2f4834375333664565756f6f695073486e5648323938776e7750724e365264515a474b764a557a6c352d685133384161587a576c61527a52776278464d6e6d33347a70494e344635632d6d3435 "Rotoye Batmon 2.2")](https://camo.githubusercontent.com/8552c5280963ba768ce83da9ed6a53c3a2b3f103/68747470733a2f2f6c68332e676f6f676c6575736572636f6e74656e742e636f6d2f4834375333664565756f6f695073486e5648323938776e7750724e365264515a474b764a557a6c352d685133384161587a576c61527a52776278464d6e6d33347a70494e344635632d6d3435)

## Getting Started

When you receive a battery with integrated Batmon, the OLED display and red/green LED should be flashing periodically, displaying the battery state of charge, the min and max cell voltages, and current in Amps. The button is used to cycle through screens, or to reset Batmon if held down for 5 seconds. Batmon will default back to the periodically flashing screen after some time to conserve energy; the lower the state of charge, the less frequently data will be displayed.

_**If you see the < ! > symbol on the OLED display, this means that one or more safety warning conditions have been met. Press the button to see the warning(s) present.**_

#### Setting I2C address
There are two jumpers, labeled X and Y on the PCB, which set the I2C address of the Batmon (0x0b by default, as per the SMBus standard). By selectively removing these jumpers, up to 4 addresses can be encoded so that multiple Batmons can exist on the same bus. 

## Programming

The Batmon board feautures a standard 6pin ISP header for easy programming of the microcontroller. [![](https://camo.githubusercontent.com/87956ae73d0ba6199c77059022bd55fda05c393a/68747470733a2f2f64726976652e676f6f676c652e636f6d2f7468756d626e61696c3f69643d31477a454272626233452d4c50725a4b655242796b7a6d58704f7372336170615a)](https://camo.githubusercontent.com/87956ae73d0ba6199c77059022bd55fda05c393a/68747470733a2f2f64726976652e676f6f676c652e636f6d2f7468756d626e61696c3f69643d31477a454272626233452d4c50725a4b655242796b7a6d58704f7372336170615a) [![](https://camo.githubusercontent.com/5604128564feb428af4f304526b46358887854dd/68747470733a2f2f7777772e617672667265616b732e6e65742f73697465732f64656661756c742f66696c65732f696373705f3670696e2e706e67)](https://camo.githubusercontent.com/5604128564feb428af4f304526b46358887854dd/68747470733a2f2f7777772e617672667265616b732e6e65742f73697465732f64656661756c742f66696c65732f696373705f3670696e2e706e67)

## Interfacing with an Autopilot

### Wiring to autopilot

You’ll notice that the XT90 on a Batmon equipped smart battery, while compatible with all XT90 connectors, is not standard. The two small pins in the middle of the connector are for interfacing with an autopilot via an opto-isolated I2C connection.

Connect the smart battery and I2C opto-isolator board to one of the autopilot’s I2C ports as shown: [![](https://camo.githubusercontent.com/605abaf3633f06cebd314a9c57cee7c5e1a3fd52/68747470733a2f2f6c68332e676f6f676c6575736572636f6e74656e742e636f6d2f674253346e3650796e6474723579516835796b34436134336a7562565a3258754e463561594f564944367950626f33645961557a6f4655374b302d6962787479674b6d596f6443396d77387a616944594b5a2d5848576b4950644d32535931696e4e414a466830534e616d674558437a505a727735757435775a3230583175326a6b39596358514b)](https://camo.githubusercontent.com/605abaf3633f06cebd314a9c57cee7c5e1a3fd52/68747470733a2f2f6c68332e676f6f676c6575736572636f6e74656e742e636f6d2f674253346e3650796e6474723579516835796b34436134336a7562565a3258754e463561594f564944367950626f33645961557a6f4655374b302d6962787479674b6d596f6443396d77387a616944594b5a2d5848576b4950644d32535931696e4e414a466830534e616d674558437a505a727735757435775a3230583175326a6b39596358514b)

### Wiring to cells

[![](https://raw.githubusercontent.com/rotoye/batmon_reader/ArduinoAsMaster/HARDWARE/Batmon-pcb.jpg)](https://raw.githubusercontent.com/rotoye/batmon_reader/ArduinoAsMaster/HARDWARE/Batmon-pcb.jpg)

Follow the schematics from [https://github.com/rotoye/batmon_reader/blob/ArduinoAsMaster/HARDWARE/6-10%20Cell%20Connection%20schematic.pdf](https://github.com/rotoye/batmon_reader/blob/ArduinoAsMaster/HARDWARE/6-10%20Cell%20Connection%20schematic.pdf) to remove the jumpers before connecting any battery to BatMon

_**If cell voltage is applied across any cell jumpers, they will short the cell and blow. Please check that your pack configuration corresponds appropriately to the jumpers.**_

### PX4
#### Stable

Clone or download [Rotoye's fork of PX4](https://github.com/rotoye/px4_firmware_batmon)

Checkout the batmon_v2.02 branch

[Build and upload](https://dev.px4.io/v1.9.0/en/setup/building_px4.html) the firmware according to PX4 documentation instructions

In ground control software of choice, set the BAT_SOURCE parameter to "External" [](https://github.com/rotoye/batmon_reader)

Start the batt_smbus [script](https://dev.px4.io/v1.9.0/en/middleware/modules_driver.html)

[![](https://camo.githubusercontent.com/4f57fdfe4af663bcc7d0dcd78faa980823dc97ec/68747470733a2f2f6c68352e676f6f676c6575736572636f6e74656e742e636f6d2f32625263586a7864547164626f6a367157534b6b7768744a4f466f75326f486859524a7a6b415957696b5f766f727a494431612d324b35654f356b39724d456f644f6742754d5038312d43327646304c785644527356364a374f6c5847456a49632d33645a6677566a6f7868413564544850594b564a42733135685a726950644f31486976525a4b)](https://camo.githubusercontent.com/4f57fdfe4af663bcc7d0dcd78faa980823dc97ec/68747470733a2f2f6c68352e676f6f676c6575736572636f6e74656e742e636f6d2f32625263586a7864547164626f6a367157534b6b7768744a4f466f75326f486859524a7a6b415957696b5f766f727a494431612d324b35654f356b39724d456f644f6742754d5038312d43327646304c785644527356364a374f6c5847456a49632d33645a6677566a6f7868413564544850594b564a42733135685a726950644f31486976525a4b)

#### Beta
*PX4 v1.11.0 is still in Beta; as such, so is BatMon support*
Clone or download [Rotoye's fork of PX4:](https://github.com/rotoye/px4_firmware_batmon)
    
Checkout the batmon_v2.02_px4_v1.11 branch
    
Build and upload the firmware according to [PX4 documentation instructions](https://dev.px4.io/master/en/setup/building_px4.html)
    
In ground control software of choice, set the BATx_SOURCE parameters to "External"
    
Start the batt_smbus [script](https://dev.px4.io/master/en/middleware/modules_driver.html) on NuttShell

For example, running two BatMons on the same bus:

`batt_smbus start -X -b 1 -a 11` * External bus 1, address 0x0b  
`batt_smbus start -X -b 1 -a 12` * External bus 1, address 0x0c

### Ardupilot

Clone or download [Rotoye's fork of Ardupilot](https://github.com/rotoye/ardupilot)

Check out the rotoye_batmon branch

In ground control software of choice, manually set the BATT_MONITOR parameter to 16 [![](https://camo.githubusercontent.com/4e0d13de8634b0ae88226aba1f015ae81a342f7f/68747470733a2f2f6c68362e676f6f676c6575736572636f6e74656e742e636f6d2f6a477257786b4d4b6f384e495f49764f6d6d665a6a334f6c644b4537477051666c5253756c6f45514b3652456b30797a47325a6e717244506f6d48565479574d68386e7447594838476c533139774d5f736d6c4438495732717a6e324f544d4346756d772d7243674e4c2d46496936596b7032785f717853724a506a7337316d747573564d336454)](https://camo.githubusercontent.com/4e0d13de8634b0ae88226aba1f015ae81a342f7f/68747470733a2f2f6c68362e676f6f676c6575736572636f6e74656e742e636f6d2f6a477257786b4d4b6f384e495f49764f6d6d665a6a334f6c644b4537477051666c5253756c6f45514b3652456b30797a47325a6e717244506f6d48565479574d68386e7447594838476c533139774d5f736d6c4438495732717a6e324f544d4346756d772d7243674e4c2d46496936596b7032785f717853724a506a7337316d747573564d336454)

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
