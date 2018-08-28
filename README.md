# Batmon battery monitor access
#This branch is modified with significant commenting for Zack's reference

## ReadBatmon: Arduino code to access the Batmon battery monitor.
Instruction to run ReadBatmon
- Copy the ReadBatmon folder to local directory. 
- Open the sketch using Arduino IDE. 
- Open Sketch->Include Library-> Add .ZIP library
- Give location of FastCRC.zip file. The FastCRC library would now be added.
- Connect the Power, GND, SDA, SCL lines from Arduino to Batmon
- Connect the cells to Batmon pcb as given by [6-10 cell connection schematic](https://github.com/rotoye/batmon_reader/blob/ArduinoAsMaster/HARDWARE/6-10%20Cell%20Connection%20schematic.pdf)
- Upload code to Arduino
- Run serial monitor to see output

