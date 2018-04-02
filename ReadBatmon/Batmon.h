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
  private:
	byte i2cAddress;
	byte numTherms;
	byte readTherms(Therms &ts, byte num);
};
