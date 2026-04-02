# BATMON V5 guide to update firmware
## Items Required
*   BATMON V5 Assembled on a battery
![](https://rotoye.com/wp-content/uploads/2021/04/Battery-Pack-v5.png)
*   Microchip ICE Programmer
![](http://batmonfiles.rotoye.com/userguide/atmel_ice.jpg)
*   Programmer cable adapter
![](http://batmonfiles.rotoye.com/userguide/adapter_2.png)
*   Programmer cable
![](http://batmonfiles.rotoye.com/userguide/programming_cable.jpg)

## Procedure
&nbsp;&nbsp;&nbsp;&nbsp; 1. Connect Microchip ICE Programmer to your computer and connect the programmer cable to SAM port of the ICE Programmer.
&nbsp;&nbsp;&nbsp;&nbsp; 2. Connect the other end of the programmer cable to the cable adapter and from the adapter to BATMON.
&nbsp;&nbsp;&nbsp;&nbsp; 3. Open [Microchip Studio](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio#Downloads) 
&nbsp;&nbsp;&nbsp;&nbsp; 4. Refer to [Batmon Firmware Flashing Instructions](https://drive.google.com/file/d/1i3FtJegiDbdkC-YvEikniwFUjrS6eBBp/view?usp=sharing)

## Troubleshooting
#### Programming Errors
There might be errors like the following when trying to read the device
signature.
![](http://batmonfiles.rotoye.com/userguide/error_msg.png)

If this happens, it means the programmer isn't detecting 3.3V at the
programming connector. Try the following:

1.  Try pressing the power button and holding for two seconds before releasing.

2.  Check that the programming cable is connected from the Atmel ICE programmer to the BatMon.

3.  Check that the battery is connected properly to the BatMon using the correct cables.