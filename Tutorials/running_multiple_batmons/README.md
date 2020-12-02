# Running Multiple Batmons on One Bus
## Physical Layer
The Opto-Isolation of the signals is **always** recommended to reduce noise and improve reliability on the bus, and is **absolutely necessary on the higher battery** when the batteries are in series. 

![Opto-iso I2C block diagram](http://batmonfiles.rotoye.com/userguide/Opto-iso%20connection.jpg)

When using two Batmons on the same bus, an I2C splitter, like the one shown here, is useful:
![I2C signal splitter](http://batmonfiles.rotoye.com/userguide/splitter.png)

## Firmware
When using two Batmons on the same I2C bus, they cannot have the same I2C slave adress. This needs to be changed in the Batmon Firmware