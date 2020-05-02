
# Rotoye Batmon
## *The Dumb-Battery Era is Over*
![](https://lh3.googleusercontent.com/H47S3fEeuooiPsHnVH298wnwPrN6RdQZGKvJUzl5-hQ38AaXzWlaRzRwbxFMnm34zpIN4F5c-m45 "Rotoye Batmon 2.2")
## Getting Started
When you receive a battery with integrated Batmon, the OLED display and red/green LED should be flashing periodically, displaying the battery state of charge, the min and max cell voltages, and current in Amps. The button is used to cycle through screens, or to reset Batmon if held down for 5 seconds. Batmon will default back to the periodically flashing screen after some time to conserve energy; the lower the state of charge, the less frequently data will be displayed.

***If you see the < ! > symbol on the OLED display, this means that one or more safety warning conditions have been met. Press the button to see the warning(s) present.***

## Programming
The Batmon board feautures a standard 6pin ISP header for easy programming of the microcontroller. 
<img src="https://drive.google.com/thumbnail?id=1GzEBrbb3E-LPrZKeRBykzmXpOsr3apaZ" />
<img src="https://www.avrfreaks.net/sites/default/files/icsp_6pin.png" width="250px" height="250px" />


## Interfacing with an Autopilot
### Wiring to autopilot
You’ll notice that the XT90 on a Batmon equipped smart battery, while compatible with all XT90 connectors, is not standard. The two small pins in the middle of the connector are for interfacing with an autopilot via an opto-isolated I2C connection.

Connect the smart battery and I2C opto-isolator board to one of the autopilot’s I2C ports as shown:
<img src="https://lh3.googleusercontent.com/gBS4n6Pyndtr5yQh5yk4Ca43jubVZ2XuNF5aYOVID6yPbo3dYaUzoFU7K0-ibxtygKmYodC9mw8zaiDYKZ-XHWkIPdM2SY1inNAJFh0SNamgEXCzPZrw5ut5wZ20X1u2jk9YcXQK" width="250px" height="250px">

### Wiring to cells
<img src="https://raw.githubusercontent.com/rotoye/batmon_reader/ArduinoAsMaster/HARDWARE/Batmon-pcb.jpg">
Follow the schematics from https://github.com/rotoye/batmon_reader/blob/ArduinoAsMaster/HARDWARE/6-10%20Cell%20Connection%20schematic.pdf to remove the jumpers before connecting any battery to BatMon

### PX4
Clone or download [Rotoye's fork of PX4](https://github.com/rotoye/px4_firmware_batmon)

Checkout the batmon_v2.02 branch

[Build and upload](https://dev.px4.io/v1.9.0/en/setup/building_px4.html) the firmware according to PX4 documentation instructions

In ground control software of choice, set the BAT_SOURCE parameter to "External"
<img src="
https://lh5.googleusercontent.com/6m3g3ZVQEpYSnkg60MCGdOUvIyAk3zA0MdIZx2wb_jd7TS-ySbqFobVs8Gu4QLrsTdAUQ0HohmtlGcrXQJgTA-rChpIqQe-wW9eZAhlfe8ZHIXTYCos8Cra6gpfUnvTvtswJpY56">

Start the batt_smbus [script](https://dev.px4.io/v1.9.0/en/middleware/modules_driver.html)

![](https://lh5.googleusercontent.com/2bRcXjxdTqdboj6qWSKkwhtJOFou2oHhYRJzkAYWik_vorzID1a-2K5eO5k9rMEodOgBuMP81-C2vF0LxVDRsV6J7OlXGEjIc-3dZfwVjoxhA5dTHPYKVJBs15hZriPdO1HivRZK)
### Ardupilot
Clone or download [Rotoye's fork of Ardupilot](https://github.com/rotoye/ardupilot)

Check out the rotoye_batmon branch

In ground control software of choice, manually set the BATT_MONITOR parameter to 13
![](https://lh6.googleusercontent.com/jGrWxkMKo8NI_IvOmmfZj3OldKE7GpQflRSuloEQK6REk0yzG2ZnqrDPomHVTyWMh8ntGYH8GlS19wM_smlD8IW2qzn2OTMCFumw-rCgNL-FIi6Ykp2x_qxSrJPjs71mtusVM3dT)
### Ground Control: 
You should now be able to verify through a tool such as MAVLink Inspector in QGroundControl that Batmon is sending data to the autopilot:
![](https://lh5.googleusercontent.com/V0JstU1yGRF2TD5f_jG0rTd1G0AOdylnBa3MxkEBWDDrBUI9mhucqD0yLY6PkL8aMIiNgsOJw4Uv3JPTGgSV-3nMdpEY_yoMjli-yrPDTqe4l1RhSMipDiKdx1Ld9dFQqgj0a3Lz)

## Arduino Library:
### ReadBatmon: Arduino code to access the Batmon battery monitor.
Instruction to run ReadBatmon
- Copy the ReadBatmon folder to local directory. 
- Open the sketch using Arduino IDE. 
- Open Sketch->Include Library-> Add .ZIP library
- Give location of FastCRC.zip file. The FastCRC library would now be added.
- Connect the Power, GND, SDA, SCL lines from Arduino to Batmon
- Connect the cells to Batmon pcb as given by [6-10 cell connection schematic](https://github.com/rotoye/batmon_reader/blob/ArduinoAsMaster/HARDWARE/6-10%20Cell%20Connection%20schematic.pdf)
- Upload code to Arduino
- Run serial monitor to see output

