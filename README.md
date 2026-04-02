
# Rotoye Batmon

## _The Dumb-Battery Era is Over_
<img width="752" height="471" alt="Battery Pack v5" src="https://github.com/user-attachments/assets/761135dd-d366-4a2d-a846-f18beab27468" />



## Getting Started

When you receive a battery with integrated BATMON, the OLED display (if applicable) and red/green LED's should be flashing periodically, displaying the battery state of charge, the min and max cell voltages, and current in Amps. The button is used to cycle through screens.

_**If you see the < ! > symbol on the OLED display, this means that one or more safety warning conditions have been met. Press the button to see the warning(s) present.**_

### Buzzer/OLED board
![Batmon v5 programming 1](https://github.com/user-attachments/assets/32696ba2-4d95-4388-ab3f-3d50fafc7e6c)


The optional OLED display/buzzer attachment extends BATMON functionality by providing a user-friendly interface for displaying state of charge, voltages, warnings, and more. The small board is attached to the main BATMON board via a flex connector. This connector is rated for a limited number of plug-unplug cycles. It is recommended to attach/detach this accessory as little, and as carefully as possible.

## Interfacing with an Autopilot
### Wiring to autopilot

### Wiring to cells
Ensure that you have received BATMON with the right cell count as your batteries. You may connect the JST balance leads of a battery to BATMON to power it up. Ensure that the negative of the battery is connected to the negative terminal on the power board(the top board with the Prolanv connector). You'd need this connection to power up BATMON even if you are just testing the board. 

### PX4
#### Stable

BATMON is supported on the stock firmware of PX4 since the [v1.12.2](https://github.com/PX4/PX4-Autopilot/releases/tag/v1.12.2) version.

Connect SMBUS/I2C of BATMON to the appropriate bus on the autopilot.

In ground control software of choice, set 

 - BAT_SOURCE parameter to "External"
 - BATMON_DRIVER_EN to 1

Start BATMON on nsh using the script: 

`batmon start -X` 						 * Search all the external bus and connect to the first BATMON detected

`batmon start -X -b 1 -a 11` * External bus 1, address 0x0b  

`batmon start -X -b 1 -a 12` * External bus 1, address 0x0c

<img width="340" height="63" alt="batmon start" src="https://github.com/user-attachments/assets/5dbec1a7-469d-4425-91c3-5722afc87b3c" />

I2C devices connected on the different bus can be identified by running nsh script:
`i2cdetect -b <bus number>`

<img width="375" height="181" alt="i2cdetect screenshot" src="https://github.com/user-attachments/assets/b8548d8f-84a4-40fa-9241-d0979145ad6f" />

*battery_status* uorb messages may be inspected using the command 
`listener battery_status 1`

<img width="988" height="606" alt="listener" src="https://github.com/user-attachments/assets/238908d6-145d-4d8c-85ee-bb18457cc2c8" />


### Ardupilot

Clone or download [Ardupilot firmware](https://github.com/ArduPilot/ardupilot)

Check out the master branch, [build from source](https://ardupilot.org/dev/docs/building-the-code.html), and flash the firmware. **BATMON support is not yet in a stable release of Ardupilot.** 

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
-   Connect the cells to BATMON
-   Upload code to Arduino
-   Run serial monitor to see output

<img width="1418" height="104" alt="batmon_reader serial output" src="https://github.com/user-attachments/assets/1407f716-34f4-4a2f-bdf3-36db59734e75" />
