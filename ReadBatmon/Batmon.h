#pragma once
#include "Batmon_struct.h"
#include <Arduino.h>
#include <FastCRC.h>

typedef Batmon_cellVoltages CVolts;
typedef Batmon_thermistors Therms;
typedef Batmon_totalVoltage TotVolt;
class Batmon{
  FastCRC8 CRC8;
  public:
	Batmon(byte _i2cAddress, byte _numTherms);
	byte readCellVoltages(CVolts &cv);
	byte readTotalVoltage(TotVolt &tv);
	byte readTherms(Therms &ts);
  byte readStatus(byte &st);
  uint16_t read_mAh_discharged();
  unsigned int readRemainCap();
  byte shutdown();
  byte powerup();
  unsigned char *getMan(unsigned char *buf);
  int getCur();
  double getSOC();
  private:
	byte i2cAddress;
	byte numTherms;
	byte readTherms(Therms &ts, byte num);
};
