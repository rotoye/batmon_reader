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
// Set to true to read the memory records from BATMON
const bool READ_BATMON_MEMORY = true;
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
      Serial.print(" dCur   ");
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
      Serial.print("   ");Serial.print(str);
      dtostrf(float(bm.getTExt(1))*0.1,4,1,str);
      Serial.print("   ");Serial.print(str);
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
      Serial.println();
    }
    else
      init();
  }
  void readNSave()
  {
   char str[50];
   char floatStr[10];
   if (isDetected && checkConnection())
   {
      BATMON_Mem_Info mem_info;
      bm.getMemoryInfo(mem_info);
      Serial.print(" I2C ");
      Serial.print("bytesPerRecord ");
      Serial.print("numPartitionsPerRecord ");
      Serial.print("bytesinPartition1 ");
      Serial.print("bytesinPartition2 ");
      Serial.print("bytesinPartition3 ");
      Serial.println("totalMemoryRecords ");
      sprintf(str, "0x%02X ", i2cAddress); Serial.print(str);
      sprintf(str, "           %3d",mem_info.data.bytesPerRecord); Serial.print(str);
      sprintf(str, "                    %3d",mem_info.data.numPartitionsPerRecord); Serial.print(str);
      sprintf(str, "               %3d",mem_info.data.bytesinPartition1); Serial.print(str);
      sprintf(str, "               %3d",mem_info.data.bytesinPartition2); Serial.print(str);
      sprintf(str, "               %3d",mem_info.data.bytesinPartition3); Serial.print(str);
      sprintf(str, "                %3d",mem_info.data.totalMemoryRecords); Serial.print(str);
      Serial.println();


      Serial.print("MemoryIndex  ");
      // for(int i = 0; i<MAXCELLCOUNT; i++)
      // {
      //   sprintf(str, " %2dC ", i+1);
      //   Serial.print(str); 
      // }
      Serial.print("minSOC ");
      Serial.print("maxSOC ");
      Serial.print("SOH ");
      Serial.print("minTempCycle ");
      Serial.print("maxTempCycle ");
      Serial.print("maxIntTempCycle ");
      Serial.print("maxDrainedCurrentCycle ");
      Serial.print("battCycle ");
      Serial.print("bootupMinCellV ");
      Serial.print("bootupMaxCellV ");
      Serial.print("bootupMinCellVIndex ");
      Serial.print("bootupMaxCellVIndex ");
      Serial.print("shutdownMinCellV ");
      Serial.print("shutdownMaxCellV ");
      Serial.print("shutdownMinCellVIndex ");
      Serial.print("shutdownMaxCellVIndex ");
      Serial.print("shutdownRemainCap ");
      Serial.print("accumulatedCharged ");
      Serial.print("accumulatedDischarged ");
      Serial.print("recNewCycle ");
      Serial.print("loggedWithoutSleep ");
      Serial.print("bqStat:POR ");
      Serial.print("bqStat:WDT ");
      Serial.print("bqStat:OAT ");
      Serial.print("accumTimeDiff ");
      Serial.print("clampVal ");
      Serial.print("mAh_discharged_cc_before_reset ");
      Serial.print("shutdown_mAh_discharged_cc ");
      
      // Serial.print("IR1Tag ");
      // Serial.print("IR1Min ");
      // Serial.print("IR1MinIndex ");
      // Serial.print("IR1Max ");
      // Serial.print("IR1MaxIndex ");
      // Serial.print("IR2Tag ");
      // Serial.print("IR2Min ");
      // Serial.print("IR2MinIndex ");
      // Serial.print("IR2Max ");
      // Serial.print("IR2MaxIndex ");
      // Serial.print("IR3Tag ");
      // Serial.print("IR3Min ");
      // Serial.print("IR3MinIndex ");
      // Serial.print("IR3Max ");
      // Serial.print("IR3MaxIndex ");
      // Serial.print("IR4Tag ");
      // Serial.print("IR4Min ");
      // Serial.print("IR4MinIndex ");
      // Serial.print("IR4Max ");
      // Serial.print("IR4MaxIndex ");
      Serial.println();
      BatmonMemory batmem;
      for(uint8_t i =0; i<mem_info.data.totalMemoryRecords; i++)  
      {
        if (bm.getMemory(batmem, mem_info) == false)
        {
          Serial.println("Record corrupted");
          continue;
        }
        sprintf(str, "        %3d",batmem.data.memoryIndex); Serial.print(str);
        sprintf(str, "     %3d",batmem.data.minSOC); Serial.print(str);
        sprintf(str, "    %3d",batmem.data.maxSOC); Serial.print(str);
        sprintf(str, " %3d",batmem.data.SOH); Serial.print(str);
        sprintf(str, "         %4d",batmem.MembyteToDecikelvin(batmem.data.minTempCycle)); Serial.print(str);
        sprintf(str, "         %4d",batmem.MembyteToDecikelvin(batmem.data.maxTempCycle)); Serial.print(str);
        sprintf(str, "            %4d",batmem.MembyteToDecikelvin(batmem.data.maxIntTempCycle)); Serial.print(str);
        sprintf(str, "                    %3d",batmem.data.maxDrainedCurrentCycle); Serial.print(str);
        sprintf(str, "       %3d",batmem.data.log.battCycle); Serial.print(str);
        sprintf(str, "           %4d",batmem.membyteToMilliVolt(batmem.data.bootupMinCellV)); Serial.print(str);
        sprintf(str, "           %4d",batmem.membyteToMilliVolt(batmem.data.bootupMaxCellV)); Serial.print(str);
        sprintf(str, "                 %3d",batmem.data.bootupMinCellVIndex); Serial.print(str);
        sprintf(str, "                 %3d",batmem.data.bootupMaxCellVIndex); Serial.print(str);
        sprintf(str, "             %3d",batmem.membyteToMilliVolt(batmem.data.shutdownMinCellV)); Serial.print(str);
        sprintf(str, "             %3d",batmem.membyteToMilliVolt(batmem.data.shutdownMaxCellV)); Serial.print(str);
        sprintf(str, "                  %4d",batmem.data.shutdownMinCellVIndex); Serial.print(str);
        sprintf(str, "                  %4d",batmem.data.shutdownMaxCellVIndex); Serial.print(str);
        sprintf(str, "             %5d",batmem.data.shutdownRemainCap); Serial.print(str);
        sprintf(str, "              %5d",batmem.data.accumulatedCharged); Serial.print(str);
        sprintf(str, "                 %5d",batmem.data.accumulatedDischarged); Serial.print(str);
        sprintf(str, "           %1d",batmem.data.log.recNewCycle); Serial.print(str);
        sprintf(str, "                  %1d",batmem.data.log.loggedWithoutSleep); Serial.print(str);
        sprintf(str, "          %1d",batmem.data.bq_status.POWER_ON_RESET); Serial.print(str);
        sprintf(str, "          %1d",batmem.data.bq_status.WATCHDOG_TRIGGERED); Serial.print(str);
        sprintf(str, "          %1d",batmem.data.bq_status.OVER_ACCUM_TIME); Serial.print(str);
        sprintf(str, "          %4d",batmem.data.accumTimeDiff); Serial.print(str);
        dtostrf(batmem.data.clampVal, 5, 1, floatStr);
        sprintf(str, "%9s",floatStr); Serial.print(str);
        dtostrf(batmem.data.mAh_discharged_cc_before_reset, 5, 1, floatStr);
        sprintf(str, "                     %10s",floatStr); Serial.print(str);
        dtostrf(batmem.data.shutdown_mAh_discharged_cc, 5, 1, floatStr);
        sprintf(str, "                 %10s",floatStr); Serial.print(str);

      //  sprintf(str, "    %3d",batmem.data.intRes[0].intResTag.int_res_tag); Serial.print(str);
      //  sprintf(str, "    %3d",batmem.data.intRes[0].minIntRes); Serial.print(str);
      //  sprintf(str, "         %3d",batmem.data.intRes[0].IntResIndices.minIntResIndex); Serial.print(str);
      //  sprintf(str, "    %3d",batmem.data.intRes[0].maxIntRes); Serial.print(str);
      //  sprintf(str, "         %3d",batmem.data.intRes[0].IntResIndices.maxIntResIndex); Serial.print(str);
      //  sprintf(str, "    %3d",batmem.data.intRes[1].intResTag.int_res_tag); Serial.print(str);
      //  sprintf(str, "    %3d",batmem.data.intRes[1].minIntRes); Serial.print(str);
      //  sprintf(str, "         %3d",batmem.data.intRes[1].IntResIndices.minIntResIndex); Serial.print(str);
      //  sprintf(str, "    %3d",batmem.data.intRes[1].maxIntRes); Serial.print(str);
      //  sprintf(str, "         %3d",batmem.data.intRes[1].IntResIndices.maxIntResIndex); Serial.print(str);
      //  sprintf(str, "    %3d",batmem.data.intRes[2].intResTag.int_res_tag); Serial.print(str);
      //  sprintf(str, "    %3d",batmem.data.intRes[2].minIntRes); Serial.print(str);
      //  sprintf(str, "         %3d",batmem.data.intRes[2].IntResIndices.minIntResIndex); Serial.print(str);
      //  sprintf(str, "    %3d",batmem.data.intRes[2].maxIntRes); Serial.print(str);
      //  sprintf(str, "         %3d",batmem.data.intRes[2].IntResIndices.maxIntResIndex); Serial.print(str);
      //  sprintf(str, "    %3d",batmem.data.intRes[3].intResTag.int_res_tag); Serial.print(str);
      //  sprintf(str, "    %3d",batmem.data.intRes[3].minIntRes); Serial.print(str);
      //  sprintf(str, "         %3d",batmem.data.intRes[3].IntResIndices.minIntResIndex); Serial.print(str);
      //  sprintf(str, "    %3d",batmem.data.intRes[3].maxIntRes); Serial.print(str);
      //  sprintf(str, "         %3d",batmem.data.intRes[3].IntResIndices.maxIntResIndex); Serial.print(str);
        Serial.println();
      }
    }
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
  if(READ_BATMON_MEMORY == true)
  {
    Serial.println("Printing BATMON memory");
    for (uint8_t i = 0; i < BATMON_SMBUS_TOTAL_ADDRESS; i++) 
      batt[i].readNSave();
  }
  else
    Serial.println("Starting BATMON Reader");
}



void loop()
{
  if(READ_BATMON_MEMORY == true)
    return;

  Serial.write(0x0C); // Command to clear screen for non-Arduino terminals like putty 

  for (uint8_t i = 0; i < BATMON_SMBUS_TOTAL_ADDRESS; i++) {
    if (i==0)
      batt[i].printBatteryInfo(true);
    else
      batt[i].printBatteryInfo(false);
  }
/*
  //Serial.print("\tManufacturer's Name: ");
  //unsigned char man_name [20];
  //Serial.print((char *)bm.getMan(man_name));

*/
  Serial.println();

  //bm.shutdown();
  delay(1000);
}
