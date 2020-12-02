# BatMon Programming Guide

## Required Materials

*   Microchip ICE Programmer

![](media/image15.jpg){width="2.125in" height="2.48786854768154in"}

*   Programmer cable adapter

> ![](media/image14.jpg){width="1.9385301837270341in"
> height="1.346900699912511in"}

*   Programmer cable

![](media/image13.jpg){width="4.903673447069116in"
height="1.3153083989501313in"}

*   BatMon board

> ![](media/image12.jpg){width="2.3229166666666665in"
> height="3.4479166666666665in"}

*   Battery

*   Computer with Atmel Studio and Git Bash installed

## Procedure

1.  Remove case

![](media/image6.jpg){width="4.25in" height="2.7298982939632546in"}

2.  Locate ICE programmer

3.  Plug cable into SAM port

![](media/image7.jpg){width="3.5520833333333335in"
height="2.420392607174103in"}

4.  Connect to Adapter

![](media/image3.jpg){width="2.4218755468066493in"
height="1.839070428696413in"}

5.  Connect to BatMon

![](media/image2.jpg){width="2.7754418197725284in"
height="2.1923654855643044in"}

6.  Turn on the BatMon by pressing on the button.

7.  Connect to computer.

8.  Open Atmel Studio.

9.  Click on the *Device Programming* icon in the upper-right side of
    > the window or press Ctrl+Shift+P on the keyboard.

> ![](media/image1.png){width="4.791666666666667in"
> height="0.9453040244969378in"}

10. Select the Atmel ICE as the tool. Make sure *ATSAMC21E18A* is set as
    > the device, and make sure the Interface is set as *SWD*.

> ![](media/image5.png){width="2.9479166666666665in"
> height="1.1041666666666667in"}

11. Click *Apply*.

12. Click on the *Read* button under Device Signature. The signature of
    > this device should appear in the text box. The *3.3V* should be
    > read as the Target Voltage.

> ![](media/image4.png){width="3.9114588801399823in"
> height="0.8031135170603675in"}

13. Contact Rotoye for access to the Github repository.
    > [[https://github.com/rotoye/batmon]{.ul}](https://github.com/rotoye/batmon)

14. Open Git Bash.

15. Navigate the the folder of your choice and enter the command: *git
    > clone https://github.com/rotoye/batmon.git*

16. Go to File\>Open\>Project/Solution.

> ![](media/image11.png){width="5.750043744531934in"
> height="3.6216360454943133in"}

17. Browse for the location of the *batmon* repository and open the
    > *Batmon_firm.atsln* file found in the folder
    > *batmon/Batmon_firm/*.

> ![](media/image8.png){width="5.598958880139983in"
> height="3.867228783902012in"}

18. Click on the *Start Without Debugging* icon on the toolbar or press
    > Ctrl+Alt+F5 on the keyboard.

> ![](media/image10.png){width="5.617095363079615in"
> height="0.8277821522309712in"}

19. Wait for the programming to finish (can take up to a minute).

20. Disconnect the programmer and enjoy!

**Troubleshooting**

**Programming Errors**

There might be errors like the following when trying to read the device
signature.

![](media/image9.png){width="4.598958880139983in"
height="1.5993175853018373in"}

If this happens, it means the programmer isn't detecting 3.3V at the
programming connector. Try the following:

1.  Try pressing the power button and holding for two seconds before
    > releasing.

2.  Check that the programming cable is connected from the Atmel ICE
    > programmer to the BatMon.

3.  Check that the battery is connected properly to the BatMon using the
    > correct cables.
