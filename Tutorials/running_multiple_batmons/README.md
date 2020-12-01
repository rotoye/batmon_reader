# Running Multiple Batmons on One Bus
## Physical Layer
The Opto-Isolation of the signals is **always** recommended to reduce noise and improve reliability on the bus, and is **absolutely necessary** when the batteries are in series. 

<img src="https://docs.google.com/drawings/d/e/2PACX-1vSSV6fyriaixp0PDRjBdxFIVxhZ8ELfCNcv5u7R1rt2QOZqrMRk21A_jorUJ8LesAISPXVZpax_tMhw/pub?w=392&amp;h=128">

When using two Batmons on the same bus, an I2C splitter, like the one shown here, is useful:
<iframe src="https://drive.google.com/file/d/1kdmGyS9dustdxNOiyFwbxRhe6sMN49XO/preview" width="208" height="129"></iframe>

## Firmware
When using two Batmons on the same I2C bus, they cannot have the same I2C slave adress. This needs to be changed in the Batmon Firmware
 
 <!--- TODO: update the actual Batmon Firmware, and reference that code here --->