/**************************************************************************************************
*
*   Copyright (c) 2020-2022, SkyMul Inc.
*   All Rights Reserved.
*
*   BatMon and its associated brands and logos published in the website and source code
*   are Trademarks of SkyMul Inc.
*
*   Redistribution and use in source and binary forms, with or without
*   modification, are permitted provided that the following conditions are met:
*
*   * Adheres to the rules of GNU GENERAL PUBLIC LICENSE, Version 3
*
*   * Redistributions of source code and the binary form must retain this copyright notice,
*       this list of conditions and disclaimer in the documentation and literature provided with
*       the distribution.
*
*   * Neither the name of the copyright holder nor the names of its contributors may be used to
*       endorse or promote products derived from this software without specific prior written
*       permission.
*
**************************************************************************************************/

/**
 * @file ReadBatmon.ino
 *
 * @author Eohan George <eohan@rotoye.com>
 */

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
      Serial.print(" dCur  ");
      Serial.print("mAh_Discharged ");
      Serial.print("SOC ");
      Serial.print("RemainCap ");
      Serial.print("IntTemp ");
      Serial.print("ExtTemp1 ");
      Serial.print("ExtTemp2 ");
      Serial.print("HashSN  "); // Hashed serial number (16bit)
      Serial.print("FullSN  "); // Serial number (128bit)
      Serial.println();
    }
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
      sprintf(str, "  %5d",bm.getCur());
      Serial.print(str);
      sprintf(str, " %5d",bm.getDeciCur());
      Serial.print(str);
      sprintf(str, "            %5d",bm.read_mAh_discharged());
      Serial.print(str);
      sprintf(str, "  %2d",bm.getSOC());
      Serial.print(str);
      sprintf(str, "    %5u",bm.readRemainCap());
      Serial.print(str);
      dtostrf(float(bm.getTInt())*0.1,4,1,str); // Since float doesn't work with Arduino sprintf
      Serial.print("    ");Serial.print(str);
      dtostrf(float(bm.getTExt(0))*0.1,4,1,str);
      Serial.print("     ");Serial.print(str);
      dtostrf(float(bm.getTExt(1))*0.1,4,1,str);
      Serial.print("     ");Serial.print(str);
      uint16_t hash = bm.getHash();
      Serial.print("  ");Serial.print(hash); 
      // get the 128bit serial number 
      uint16_t sn[8];
      uint8_t *sn_byte;
      sn_byte = (uint8_t *)sn;
      Serial.print("   ");
      if(bm.getSN(sn))
      {
        sprintf(str,"0x,");
        for(int i = 15;i>=0;i--)
        {
          sprintf(str,"%s%02X",str,sn_byte[i]);
          if(i%2==0 && i!=0)
            sprintf(str,"%s-",str);
        }
        Serial.print(str); Serial.print("  ");
      }
      else
        Serial.print("ERR");
    }
    else
      init();
  }
};

Batt batt[]= {Batt(BATMON_SMBUS_ADDRESS_ARRAY[0], NUM_THERM_TO_READ), 
              Batt(BATMON_SMBUS_ADDRESS_ARRAY[1], NUM_THERM_TO_READ), 
              Batt(BATMON_SMBUS_ADDRESS_ARRAY[2], NUM_THERM_TO_READ), 
              Batt(BATMON_SMBUS_ADDRESS_ARRAY[3], NUM_THERM_TO_READ), 
              Batt(BATMON_SMBUS_ADDRESS_ARRAY[4], NUM_THERM_TO_READ), 
              Batt(BATMON_SMBUS_ADDRESS_ARRAY[5], NUM_THERM_TO_READ), 
              Batt(BATMON_SMBUS_ADDRESS_ARRAY[6], NUM_THERM_TO_READ), 
              Batt(BATMON_SMBUS_ADDRESS_ARRAY[7], NUM_THERM_TO_READ), 
              Batt(BATMON_SMBUS_ADDRESS_ARRAY[8], NUM_THERM_TO_READ), 
              Batt(BATMON_SMBUS_ADDRESS_ARRAY[9], NUM_THERM_TO_READ)};
              
void setup()
{
  // Start the I2C Bus as Master
  Serial.begin(115200);
  //Serial.println("Read Batmon");
  Wire.setClock(100000);
  for (uint8_t i = 0; i < BATMON_SMBUS_TOTAL_ADDRESS; i++) {
    batt[i].init();
  }
  
  //Serial.println("Total Voltage, Cell 10, Cell 9, Cell 8, Cell 7, Cell 6, Cell 5, Cell 4, Cell 3, Cell 2, Cell 1, Current, Discharged Current");
  Serial.println("Starting BATMON Reader");
}



void loop()
{
  Serial.write(0x0C); // Command to clear screen for non-Arduino terminals like putty 

  for (uint8_t i = 0; i < BATMON_SMBUS_TOTAL_ADDRESS; i++) {
    if (i==0)
      batt[i].printBatteryInfo(true);
    else
      batt[i].printBatteryInfo(false);
    Serial.println();
  }
/*
  //Serial.print("\tManufacturer's Name: ");
  //unsigned char man_name [20];
  //Serial.print((char *)bm.getMan(man_name));

*/
  Serial.println();

  //bm.shutdown();
  delay(200);
}
