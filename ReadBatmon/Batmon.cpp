#include "Batmon.h"
#include <Wire.h>

Batmon::Batmon(byte _i2cAddress, byte _numTherms)
{
  i2cAddress = _i2cAddress;
  numTherms = _numTherms;
}

//byte Batmon::shutdown()
//{
//  Wire.beginTransmission(i2cAddress);
//  Wire.write(SHUTDOWN);
//  return Wire.endTransmission();
//}
//byte Batmon::powerup()
//{
//  Wire.beginTransmission(i2cAddress);
//  Wire.write(POWERUP);
//  return Wire.endTransmission();
//}

////////////////////////////////
// Return 0: No error
//        1: CRC error
//        2: i2c error
//        3: status error; read status
byte Batmon::readCellVoltages(CVolts &cv)
{
  unsigned short *ptr;
  ptr = (unsigned short *)&cv.VCell1;
  uint8_t i ;
  int cellCount;
  cellCount = getCellCount();
  for(i = 0; i < cellCount; i++)
  {
    Wire.beginTransmission(i2cAddress);
    Wire.write(SMBUS_VCELL1 - i);

    // endTransmission return
    // Output 0 .. success
    //        1 .. length to long for buffer
    //        2 .. address send, NACK received
    //        3 .. data send, NACK received
    //        4 .. other twi error (lost bus arbitration, bus error, ..)
    unsigned char ret = Wire.endTransmission(false);
    switch(ret)
    {
      case 0:
        break;
      case 1:
      case 2:
      case 4:
        Wire.endTransmission(true);
        return 2;
      case 3:   // Its upto the user on whether to read the data in this case. Sometimes, you might want to read it, sometime not
        Wire.endTransmission(true);
        return 3;
    }

    unsigned char readNum = 3; // CRC + size
    if(Wire.requestFrom(i2cAddress, readNum) == readNum)
    {
        ptr[i ] = Wire.read();
        ptr[i ] += Wire.read() << 8;
        Wire.read();
    }
    else
      return 2;
  }
  //if(CRC8.smbus(ptr,10) == cv.CRC)
  //{
  //  return 0;
  //}
  //else
  //  return 1;
  return 0;
}

////////////////////////////////
// Return 0: No error
//        1: CRC error
//        2: i2c error
//        3: status error without CRC error
//        4: status error with CRC error
// Check Batmon_struct.h for &st values
byte Batmon::readStatus(byte &st)
{
  Wire.beginTransmission(i2cAddress);
  Wire.write(SMBUS_SAFETY_STATUS);

  // endTransmission return
  // Output 0 .. success
  //        1 .. length to long for buffer
  //        2 .. address send, NACK received
  //        3 .. data send, NACK received
  //        4 .. other twi error (lost bus arbitration, bus error, ..)
  unsigned char ret = Wire.endTransmission(false);
  switch(ret)
  {
    case 0:
    case 3:
      break;
    case 1:
    case 2:
    case 4:
      Wire.endTransmission(true);
      return 2;
  }

  unsigned char readNum = 1 + 1; // CRC + size
  if(Wire.requestFrom(i2cAddress, readNum) == readNum)
  {
    st = Wire.read();
    if(CRC8.smbus(&st,1) == Wire.read())
    {
      if(ret == 3)
        return 3;
      else
        return 0;
    }
    else
    {
      if(ret == 3)
        return 4;
      else
        return 1;
    }
  }
  else
    return 2;
}

////////////////////////////////
// Return 0: No error
//        1: CRC error
//        2: i2c error
//        3: status error; read status
byte Batmon::readTotalVoltage(TotVolt &tv)
{
  Wire.beginTransmission(i2cAddress);
  Wire.write(SMBUS_VOLTAGE);

  // endTransmission return
  // Output 0 .. success
  //        1 .. length to long for buffer
  //        2 .. address send, NACK received
  //        3 .. data send, NACK received
  //        4 .. other twi error (lost bus arbitration, bus error, ..)
  unsigned char ret = Wire.endTransmission(false);
  switch(ret)
  {
    case 0:
      break;
    case 1:
    case 2:
    case 4:
      Wire.endTransmission(true);
      return 2;
    case 3: // Its upto the user on whether to read the data in this case. Sometimes, you might want to read it, sometime not
      Wire.endTransmission(true);
      return 3;
  }

  unsigned char readNum = sizeof(tv); // CRC + size
  if(Wire.requestFrom(i2cAddress, readNum) == readNum)
  {
    tv.TV.VTotByte.VTot_HI = Wire.read();
    tv.TV.VTotByte.VTot_LO = Wire.read();
    tv.CRC = Wire.read();
    unsigned char *ptr = (unsigned char *)&tv.TV.VTotWord;
    if(CRC8.smbus(ptr, sizeof(tv.TV.VTotWord)) == tv.CRC)
    {
      return 0;
    }
    else
      return 1;
  }
  else
    return 2;
}

byte Batmon::readTherms(Therms &ts)
{
  return readTherms(ts, numTherms);
}

////////////////////////////////
// Return 0: No error
//        1: CRC error
//        2: i2c error
//        3: status error; read status
byte Batmon::readTherms(Therms &ts, byte num)
{
  if(num > 2)
    return 3;

  Wire.beginTransmission(i2cAddress);
  if(num == 0)
  {
    Wire.write(SMBUS_TEMP_INT);
  }
  else if(num == 1)
  {
    Wire.write(SMBUS_TEMP_EXTERNAL_1);
  }
  else if(num == 2)
  {
    Wire.write(SMBUS_TEMP_EXTERNAL_2);
  }

  // endTransmission return
  // Output 0 .. success
  //        1 .. length to long for buffer
  //        2 .. address send, NACK received
  //        3 .. data send, NACK received
  //        4 .. other twi error (lost bus arbitration, bus error, ..)
  unsigned char ret = Wire.endTransmission(false);
  switch(ret)
  {
    case 0:
      break;
    case 1:
    case 2:
    case 4:
      Wire.endTransmission(true);
      return 2;
    case 3: // Its upto the user on whether to read the data in this case. Sometimes, you might want to read it, sometime not
      Wire.endTransmission(true);
      return 3;
  }

  unsigned char readNum = sizeof(ts.T_int) * (num + 1) + 1; // CRC + size
  if(Wire.requestFrom(i2cAddress, readNum) == readNum)
  {
    unsigned char *ptr;
    if(num == 0)
    {
      ptr = (unsigned char *)&ts.T_int;
    }
    else if(num == 1)
    {
      ptr = (unsigned char *)&ts.T1;
    }
    else if(num == 2)
    {
      ptr = (unsigned char *)&ts.T2;
    }

    for(int i = 0; i < readNum; i++)
    {
      ptr[i] = Wire.read();
    }

    if (CRC8.smbus(ptr, readNum-1) == ts.CRC)
    {
      return 0;
    }
    else
      return 1;
  }
  else
    return 2;
}

unsigned char* Batmon::getMan(unsigned char *buf)
{
  Wire.beginTransmission(i2cAddress);
  Wire.write(0x20);
  Wire.endTransmission();
  int i = 0;
  if(Wire.requestFrom(i2cAddress, 8))
  {
    while(Wire.available())
    {
      buf[i] = Wire.read();
      i++;
    }
  }
  return buf;
}

int Batmon::getCur()
{
  int current;
  Wire.beginTransmission(i2cAddress);
  Wire.write(SMBUS_CURRENT);
  Wire.endTransmission();
  if(Wire.requestFrom(i2cAddress, 3))
  {
    current = (int)Wire.read();
    current |= (int)Wire.read() << 8;
    Wire.read();
  }
  return current;
}

int Batmon::getDeciCur()
{
  int current;
  Wire.beginTransmission(i2cAddress);
  Wire.write(SMBUS_DECI_CURRENT);
  Wire.endTransmission();
  if(Wire.requestFrom(i2cAddress, 3))
  {
    current = (int)Wire.read();
    current |= (int)Wire.read() << 8;
    Wire.read();
  }
  return current;
}

// deciCelcius output
int Batmon::getTInt()
{
  int t;
  Wire.beginTransmission(i2cAddress);
  Wire.write(SMBUS_TEMP_INT);
  Wire.endTransmission();
  if(Wire.requestFrom(i2cAddress, 3))
  {
    t = (int)Wire.read();
    t |= (int)Wire.read() << 8;
    Wire.read();
    t = t - 2731;
  }
  return t;
}
// deciCelcius output
int Batmon::getTExt(byte extThermNum)
{
  int t;
  Wire.beginTransmission(i2cAddress);
  switch(extThermNum)
  {
    case 0:
      Wire.write(SMBUS_TEMP_EXTERNAL_1);  
    break;
    case 1:
      Wire.write(SMBUS_TEMP_EXTERNAL_2);  
    break;
  }
  Wire.endTransmission();
  if(Wire.requestFrom(i2cAddress, 3))
  {
    t = (int)Wire.read();
    t |= (int)Wire.read() << 8;
    Wire.read();
    t = t - 2731;
  }
  return t;
}

int16_t Batmon::read_mAh_discharged()
{
  uint8_t num = 2;
  char discharged[num];
  Wire.beginTransmission(i2cAddress);
  Wire.write(SMBUS_MAH_DISCHARGED);
  Wire.endTransmission();
  if(Wire.requestFrom(i2cAddress, num + 1))
  {
    discharged[0] = Wire.read();
    discharged[1] = Wire.read();
    //discharged[2] = Wire.read();
    //discharged[3] = Wire.read();
    Wire.read(); //throw out crc
  }
  return *((int16_t *)discharged);
}

unsigned int Batmon::getSOC()
{
  unsigned int soc;
  Wire.beginTransmission(i2cAddress);
  Wire.write(SMBUS_RELATIVE_SOC);
  Wire.endTransmission();
  if(Wire.requestFrom(i2cAddress, 3))
  {
    soc = (unsigned int)Wire.read();
    soc |= (unsigned int)Wire.read() << 8;
    Wire.read();// throw out crc
  }
  return soc;
}

unsigned int Batmon::readRemainCap()
{
  unsigned int cap;
  Wire.beginTransmission(i2cAddress);
  Wire.write(SMBUS_REMAIN_CAP);
  Wire.endTransmission();
  if(Wire.requestFrom(i2cAddress, 3))
  {
    cap = (unsigned int)Wire.read();
    cap |= (unsigned int)Wire.read() << 8;
    Wire.read();// throw out crc
  }
  return cap;
}

uint8_t Batmon::getCellCount()
{
  unsigned int cellCount;
  Wire.beginTransmission(i2cAddress);
  Wire.write(SMBUS_CELL_COUNT);
  Wire.endTransmission();
  if(Wire.requestFrom(i2cAddress, 3))
  {
    cellCount = (unsigned int)Wire.read();
    cellCount |= (unsigned int)Wire.read() << 8;
    Wire.read();// throw out crc
  }
  return cellCount;
}

uint16_t Batmon::getHash()
{
  uint16_t hash;
  Wire.beginTransmission(i2cAddress);
  Wire.write(SMBUS_SERIAL_NUM);
  Wire.endTransmission();
  if(Wire.requestFrom(i2cAddress, 3))
  {
    hash = (uint16_t)Wire.read();
    hash |= (uint16_t)Wire.read() << 8;
    Wire.read();// throw out crc
  }
  return hash;
}
// Return true if successfully read the serial number
bool Batmon::getSN(uint16_t sn[8])
{
  Wire.beginTransmission(i2cAddress);
  Wire.write(SMBUS_MANUFACTURER_DATA);
  Wire.endTransmission();
  //  TODO: should BATMON return less than 18 for firmware without full serial number?
  if(Wire.requestFrom(i2cAddress, 18) == 18) 
  {
    if(Wire.read() != 16)
      return false; 
    uint16_t sn1, sn2, sn3, sn4, sn5, sn6, sn7, sn8;
    sn[0] = Wire.read() | Wire.read() << 8;
    sn[1] = Wire.read() | Wire.read() << 8;
    sn[2] = Wire.read() | Wire.read() << 8;
    sn[3] = Wire.read() | Wire.read() << 8;
    sn[4] = Wire.read() | Wire.read() << 8;
    sn[5] = Wire.read() | Wire.read() << 8;
    sn[6] = Wire.read() | Wire.read() << 8;
    sn[7] = Wire.read() | Wire.read() << 8;
    Wire.read();
    return true;
  }
  return false;
}
