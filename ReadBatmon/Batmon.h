#pragma once
#include "Batmon_struct.h"
#include <Arduino.h>
#include <FastCRC.h>

typedef Batmon_cellVoltages CVolts;
typedef Batmon_thermistors Therms;
typedef Batmon_totalVoltage TotVolt;
class Batmon
{
  FastCRC8 CRC8;
  public:
  Batmon(byte _i2cAddress, byte _numTherms);
  byte readCellVoltages(CVolts &cv);
  byte readTotalVoltage(TotVolt &tv);
  uint8_t getCellCount();
  byte readTherms(Therms &ts);
  byte readStatus(byte &st);
  int16_t read_mAh_discharged();
  unsigned int readRemainCap();
  byte shutdown();
  byte powerup();
  unsigned char *getMan(unsigned char *buf);
  int getCur();
  unsigned int getSOC();
  int getTInt();
  int getTExt();
  private:
  byte i2cAddress;
  byte numTherms;
  byte readTherms(Therms &ts, byte num);
};
