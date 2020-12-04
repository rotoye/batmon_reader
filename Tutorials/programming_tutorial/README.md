# BatMon Programming Guide

## Required Materials

*   Microchip ICE Programmer

![](http://batmonfiles.rotoye.com/userguide/atmel_ice.jpg)

*   Programmer cable adapter

![](http://batmonfiles.rotoye.com/userguide/adapter_2.png)

*   Programmer cable

![](http://batmonfiles.rotoye.com/userguide/programming_cable.jpg | width=4.903673447069116in height=1.3153083989501313in)

*   BatMon board

![](http://batmonfiles.rotoye.com/userguide/batmon.jpg)

*   Battery

*   Computer with Atmel Studio and Git Bash installed

## Procedure

1.  Remove case

![](http://batmonfiles.rotoye.com/userguide/batmon_case.jpg)

1.  Locate ICE programmer

2.  Plug cable into SAM port

![](http://batmonfiles.rotoye.com/userguide/program_connect.jpg)

1.  Connect to Adapter

![](http://batmonfiles.rotoye.com/userguide/cable_in_adapter.jpg)

1.  Connect to BatMon

![](http://batmonfiles.rotoye.com/userguide/batmon_program.jpg)

1.  Turn on the BatMon by pressing on the button.

2.  Connect to computer.

3.  Open Atmel Studio.

4.  Click on the *Device Programming* icon in the upper-right side of the window or press Ctrl+Shift+P on the keyboard.

![](http://batmonfiles.rotoye.com/userguide/programming_icon.png)

1.  Select the Atmel ICE as the tool. Make sure *ATSAMC21E18A* is set as the device, and make sure the Interface is set as *SWD*.

1.  Click *Apply*.

2.  Click on the *Read* button under Device Signature. The signature of this device should appear in the text box. The *3.3V* should be read as the Target Voltage.

![](http://batmonfiles.rotoye.com/userguide/start_debug.png)

1.  Contact Rotoye for access to the Github repository [https://github.com/rotoye/batmon](https://github.com/rotoye/batmon)

2.  Open Git Bash.

3.  Navigate the the folder of your choice and enter the command: `git clone https://github.com/rotoye/batmon.git`

4.  Go to File\>Open\>Project/Solution.

![](http://batmonfiles.rotoye.com/userguide/open_project.png)

1.  Browse for the location of the *batmon* repository and open the Batmon_firm.atsln* file found in the folder *batmon/Batmon_firm/*.

![](http://batmonfiles.rotoye.com/userguide/project_file.png)

1.  Click on the *Start Without Debugging* icon on the toolbar or press Ctrl+Alt+F5 on the keyboard.

![](http://batmonfiles.rotoye.com/userguide/start_debug.png)

1.  Wait for the programming to finish (can take up to a minute).

2.  Disconnect the programmer and enjoy!

## Troubleshooting

### Programming Errors

There might be errors like the following when trying to read the device
signature.

![](http://batmonfiles.rotoye.com/userguide/error_msg.png)

If this happens, it means the programmer isn't detecting 3.3V at the
programming connector. Try the following:

1.  Try pressing the power button and holding for two seconds before releasing.

2.  Check that the programming cable is connected from the Atmel ICE programmer to the BatMon.

3.  Check that the battery is connected properly to the BatMon using the correct cables.