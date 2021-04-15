#include <Wire.h>
#include "Batmon.h"

class Batt{
private:
  uint8_t i2cAddress, numTherms, cellCount, isDetected;
public:
  Batmon bm;
  CVolts cv;
  TotVolt tv;
  Therms ts;
  uint8_t MAXCELLCOUNT = 12;
  Batt(uint8_t _i2cAddress, uint8_t _numTherms):bm(_i2cAddress,_numTherms){
    i2cAddress = _i2cAddress;
    numTherms = _numTherms;
  }
  // Returns true for succeed
  bool checkConnection()
  {
    Wire.beginTransmission(i2cAddress);
    uint8_t error = Wire.endTransmission();
    if (error == 0)
      return true;
    else
      return false;
  }
  bool init()
  {
    if(checkConnection())
    {
      cellCount = bm.getCellCount();
      if(cellCount == 0 || cellCount == 0xFF)
        isDetected = false;
      else
        isDetected = true;
      return isDetected;
    }
    return false;
  }
  void readVoltages()
  {
    bm.readCellVoltages(cv);
    bm.readTotalVoltage(tv);
  }
  void printBatteryInfo(bool heading =false)
  {
    char str[50];
    if (heading)
    {
      Serial.print(" I2C ");
      Serial.print(" TV  ");
      for(int i = 0; i<MAXCELLCOUNT; i++)
      {
        sprintf(str, " %2dC ", i+1);
        Serial.print(str); 
      }
      Serial.print(" Current ");
      Serial.print("mAh_Discharged ");
      Serial.print("SOC ");
      Serial.print("RemainCap ");
      Serial.print("IntTemp ");
      Serial.print("ExtTemp ");
      Serial.println();
    }
    else
    {
      if (isDetected && checkConnection())
      {
        sprintf(str, "0x%02X ", i2cAddress);
        Serial.print(str);
        readVoltages();
        unsigned short *ptr = (unsigned short *)&cv;
        sprintf(str, "%5u", tv.TV.VTotWord);
        Serial.print(str);
        Serial.print(",");
        int i;
        // Printing cell voltages
        for(i = 0; i < cellCount; i++)
        {
          sprintf(str, "%4d", ptr[i]);
          Serial.print(str);
          Serial.print(",");
        }
        // Adding space for non existent cells
        for(;i<MAXCELLCOUNT; i++)
        {
          Serial.print("    ,"); 
        }
        Serial.print("\t");
        sprintf(str, "%5d ",bm.getCur());
        Serial.print(str);
        sprintf(str, "  %5d        ",bm.read_mAh_discharged());
        Serial.print(str);
        sprintf(str, "  %2d",bm.getSOC());
        Serial.print(str);
        sprintf(str, "  %5u        ",bm.readRemainCap());
        Serial.print(str);
        dtostrf(float(bm.getTInt())*0.1,4,1,str); // Since float doesn't work with Arduino sprintf
        Serial.print(str);Serial.print("  ");
        dtostrf(float(bm.getTExt())*0.1,4,1,str);
        Serial.print(str);Serial.print("  ");
      }
      else
        init();
    }
  }
};

Batt bat3(I2CADDRESS3, 2);
Batt bat4(I2CADDRESS4, 2);
void setup()
{
  // Start the I2C Bus as Master
  Serial.begin(115200);
  //Serial.println("Read Batmon");
  Wire.setClock(100000);
  bat3.init();
  bat4.init();
  //Serial.println("Total Voltage, Cell 10, Cell 9, Cell 8, Cell 7, Cell 6, Cell 5, Cell 4, Cell 3, Cell 2, Cell 1, Current, Discharged Current");
}



void loop()
{
  Serial.write(0x0C); // Command to clear screen for non-Arduino terminals like putty 

  bat3.printBatteryInfo(true);
  bat3.printBatteryInfo();
  Serial.println();
  bat4.printBatteryInfo();
  Serial.println();
  //Serial.print("|| RdTherm(i2c):");
  //Serial.print( bm.readTherms(ts) );
  //Serial.print(" T_int:");
  //Serial.print(ts.T_int.T_int_Word);
  //Serial.print(" T1:");
  //Serial.print(ts.T1.T1Word);
  //Serial.print(" T2:");
  //Serial.print(ts.T2.T2Word);
/*
  //Serial.print("\tManufacturer's Name: ");
  //unsigned char man_name [20];
  //Serial.print((char *)bm.getMan(man_name));

*/
  Serial.println();

  //bm.shutdown();
  delay(200);
}
