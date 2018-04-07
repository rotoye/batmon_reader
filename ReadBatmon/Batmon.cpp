#include "Batmon.h"
#include <Wire.h>
Batmon::Batmon(byte _i2cAddress, byte _numTherms)
{
	i2cAddress = _i2cAddress;
	numTherms = _numTherms;
}

byte Batmon::shutdown()
{
  Wire.beginTransmission(i2cAddress);
  Wire.write(SHUTDOWN);
  return Wire.endTransmission();
}
byte Batmon::powerup()
{
  Wire.beginTransmission(i2cAddress);
  Wire.write(POWERUP);
  return Wire.endTransmission();
}
////////////////////////////////
// Return 0: No error
// 		  1: CRC error
// 		  2: i2c error
byte Batmon::readCellVoltages(CVolts &cv)
{
  Wire.beginTransmission(i2cAddress);
  Wire.write(READCELLVOLTAGES);

  // endTransmission return 
   //Output   0 .. success
  //         1 .. length to long for buffer
  //         2 .. address send, NACK received
  //         3 .. data send, NACK received
  //         4 .. other twi error (lost bus arbitration, bus error, ..)
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
    case 3:
      Wire.endTransmission(true);
      return 3;
  }

  unsigned char readNum =sizeof(cv); // CRC + size
  if( Wire.requestFrom(i2cAddress, readNum) == readNum) 
  {
    unsigned char *ptr;
    ptr = (unsigned char *)&cv.VCell1;
    int i;
    for(i = 0; i < readNum;i++)
    {
      ptr[i] = Wire.read();
    }
    
    if (CRC8.smbus(ptr,readNum-1) == cv.CRC)
    {
      return 0;
    }
    else
      return 1;
  }
  else 
    return 2;
}


////////////////////////////////
// Return 0: No error
//       1: CRC error
//      2: i2c error
// Check Batmon_struct.h for &st values

byte Batmon::readStatus(byte &st)
{
  Wire.beginTransmission(i2cAddress);
  Wire.write(READSTATUS);
  
  // endTransmission return 
   //Output   0 .. success
  //         1 .. length to long for buffer
  //         2 .. address send, NACK received
  //         3 .. data send, NACK received
  //         4 .. other twi error (lost bus arbitration, bus error, ..)
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
    case 3:
      Wire.endTransmission(true);
      return 3;
  }

  unsigned char readNum =1+1; // CRC + size
  if( Wire.requestFrom(i2cAddress, readNum) == readNum) 
  {
    st = Wire.read();
    if (CRC8.smbus(&st,1) == Wire.read())
    {
      return 0;
    }
    else
      return 1;
  }
  else 
    return 2;
}


////////////////////////////////
// Return 0: No error
// 		  1: CRC error
// 		  2: i2c error
byte Batmon::readTotalVoltage(TotVolt &tv)
{
  Wire.beginTransmission(i2cAddress);
  Wire.write(READTOTVOLTAGE);
  
  // endTransmission return 
   //Output   0 .. success
  //         1 .. length to long for buffer
  //         2 .. address send, NACK received
  //         3 .. data send, NACK received
  //         4 .. other twi error (lost bus arbitration, bus error, ..)
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
    case 3:
      Wire.endTransmission(true);
      return 3;
  }

  unsigned char readNum =sizeof(tv); // CRC + size
  if( Wire.requestFrom(i2cAddress, readNum) == readNum) 
  {
    tv.TV.VTotByte.VTot_HI = Wire.read();
    tv.TV.VTotByte.VTot_LO = Wire.read();
    tv.CRC = Wire.read();
    unsigned char *ptr = (unsigned char *)&tv.TV.VTotWord;
    if (CRC8.smbus(ptr, sizeof(tv.TV.VTotWord)) == tv.CRC)
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
	return readTherms(ts,numTherms);
}


////////////////////////////////
// Return 0: No error
// 		  1: CRC error
// 		  2: i2c error
//		  3: incorrect number of thermistors supported by the monitor

byte Batmon::readTherms(Therms &ts, byte num)
{
	if( num > 2)
		return 3;
   
	Wire.beginTransmission(i2cAddress);
	if( num ==0 )
	{
		Wire.write(READTHERM0);
	}
	else if(num ==1)
	{
		Wire.write(READTHERM1);
	}
	else if(num ==2)
	{
		Wire.write(READTHERM2);
	}
	
	// endTransmission return	
	 //Output   0 .. success
	//         1 .. length to long for buffer
	//         2 .. address send, NACK received
	//         3 .. data send, NACK received
	//         4 .. other twi error (lost bus arbitration, bus error, ..)
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
		case 3:
			Wire.endTransmission(true);
			return 3;
	}

	unsigned char readNum =sizeof(ts.T_int)*(num+1)+1; // CRC + size
	if( Wire.requestFrom(i2cAddress, readNum) == readNum) 
	{
		unsigned char *ptr;
		if(num ==0)
		{
			ptr = (unsigned char *)&ts.T_int;
		}
		else if(num ==1)
		{
			ptr = (unsigned char *)&ts.T1;
		}
		else if(num ==2)
		{
			ptr = (unsigned char *)&ts.T2;
		}
		
		for(int i = 0; i < readNum;i++)
		{
			ptr[i] = Wire.read();
		}
		
		if (CRC8.smbus(ptr,readNum-1) == ts.CRC)
		{
			return 0;
		}
		else
			return 1;
	}
	else 
		return 2;
	
}
	
