# BatMon Programming Guide

## Required Materials

*   Microchip ICE Programmer

![atmel_ice](https://github.com/user-attachments/assets/e7e87c37-c42c-42ff-9723-44236e6bff39)

*   Programmer cable adapter

<img width="281" height="190" alt="adapter_2" src="https://github.com/user-attachments/assets/3831ac21-f73e-4487-b0ac-62acf39f199a" />


*   Programmer cable

![programming_cable](https://github.com/user-attachments/assets/1b883db3-0471-41d6-b7dd-1564eb59cab1)


*   BatMon board

![batmon](https://github.com/user-attachments/assets/4dc41a91-c9ca-4684-aba2-032d7bf46e64)


*   Battery

*   Computer with Atmel Studio and Git Bash installed

## Procedure

1.  Remove case

![batmon_case](https://github.com/user-attachments/assets/49240f3c-01c8-49b0-8a5c-9b44ccf34af1)


1.  Locate ICE programmer

2.  Plug cable into SAM port

![program_connect](https://github.com/user-attachments/assets/8f1c4a18-2563-474b-91aa-2b84c3796ae6)

1.  Connect to Adapter

![cable_in_adapter](https://github.com/user-attachments/assets/76d96d42-f9dd-432e-87cd-efee44a2c780)


1.  Connect to BatMon

![batmon_program](https://github.com/user-attachments/assets/942c13a7-8e5c-4601-bdb1-08cad6bff428)


1.  Turn on the BatMon by pressing on the button.

2.  Connect to computer.

3.  Open Atmel Studio.

4.  Click on the *Device Programming* icon in the upper-right side of the window or press Ctrl+Shift+P on the keyboard.

<img width="609" height="133" alt="programming_icon" src="https://github.com/user-attachments/assets/da12f4f7-38fd-4f31-ae9a-b30fa8c199b9" />


1.  Select the Atmel ICE as the tool. Make sure *ATSAMC21E18A* is set as the device, and make sure the Interface is set as *SWD*.

1.  Click *Apply*.

2.  Click on the *Read* button under Device Signature. The signature of this device should appear in the text box. The *3.3V* should be read as the Target Voltage.

<img width="390" height="110" alt="start_debug" src="https://github.com/user-attachments/assets/bf56be2d-d3bc-4e84-a425-a05096ab75e4" />


1.  Contact Rotoye for access to the Github repository [https://github.com/rotoye/batmon](https://github.com/rotoye/batmon)

2.  Open Git Bash.

3.  Navigate the the folder of your choice and enter the command: `git clone https://github.com/rotoye/batmon.git`

4.  Go to File\>Open\>Project/Solution.

<img width="816" height="513" alt="open_project" src="https://github.com/user-attachments/assets/2313bac1-2e8f-4391-81d3-b5d672efc163" />


1.  Browse for the location of the *batmon* repository and open the Batmon_firm.atsln* file found in the folder *batmon/Batmon_firm/*.

<img width="666" height="343" alt="project_file" src="https://github.com/user-attachments/assets/f7eba801-6dd2-4933-97b7-9de4ceace8c3" />


1.  Click on the *Start Without Debugging* icon on the toolbar or press Ctrl+Alt+F5 on the keyboard.

<img width="390" height="110" alt="start_debug" src="https://github.com/user-attachments/assets/fca8e90e-80e3-41b0-9dbf-295c99f2e334" />


1.  Wait for the programming to finish (can take up to a minute).

2.  Disconnect the programmer and enjoy!

## Troubleshooting

### Programming Errors

There might be errors like the following when trying to read the device
signature.

<img width="626" height="218" alt="error_msg" src="https://github.com/user-attachments/assets/614d6a41-25e8-4d66-a79a-a50f9331803e" />


If this happens, it means the programmer isn't detecting 3.3V at the
programming connector. Try the following:

1.  Try pressing the power button and holding for two seconds before releasing.

2.  Check that the programming cable is connected from the Atmel ICE programmer to the BatMon.

3.  Check that the battery is connected properly to the BatMon using the correct cables.
