#include "Batmon.h"
#include <Wire.h>
Batmon::Batmon(byte _i2cAddress, byte _numTherms)
{
	i2cAddress = _i2cAddress;
	numTherms = _numTherms;
}

/*byte Batmon::shutdown()
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
}*/
////////////////////////////////
// Return 0: No error
// 		  1: CRC error
// 		  2: i2c error
//      3: status error; read status
byte Batmon::readCellVoltages(CVolts &cv)
{
  unsigned short *ptr;
  ptr = (unsigned short *)&cv.VCell1;
  int i;
  for(i = SMBUS_VCELL1; i >= SMBUS_VCELL10;i--)
  {
    Wire.beginTransmission(i2cAddress);
    Wire.write(i);
  
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
      case 3:   // Its upto the user on whether to read the data in this case. Sometimes, you might want to read it, sometime not
        Wire.endTransmission(true);
        return 3;
    }
  
    unsigned char readNum =3; // CRC + size
    if( Wire.requestFrom(i2cAddress, readNum) == readNum) 
    {
        ptr[i-0x36] = Wire.read();
        ptr[i-0x36] += Wire.read()<<8;
        Wire.read();
    }
    else 
    return 2;
  }
  /*if (CRC8.smbus(ptr,10) == cv.CRC)
    {
      return 0;
    }
  else
    return 1;*/
    return 0;
}

////////////////////////////////
// Return 0: No error
//       1: CRC error
//      2: i2c error
//      3: status error without CRC error
//      4: status error with CRC error
// Check Batmon_struct.h for &st values

byte Batmon::readStatus(byte &st)
{
  Wire.beginTransmission(i2cAddress);
  Wire.write(SMBUS_SAFETY_STATUS);
  
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
    case 3:
      break;
    case 1:
    case 2:
    case 4:
      Wire.endTransmission(true);
      return 2;
  }

  unsigned char readNum =1+1; // CRC + size
  if( Wire.requestFrom(i2cAddress, readNum) == readNum) 
  {
    st = Wire.read();
    if (CRC8.smbus(&st,1) == Wire.read())
    {
      if(ret ==3)
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
// 		  1: CRC error
// 		  2: i2c error
//      3: status error; read status
byte Batmon::readTotalVoltage(TotVolt &tv)
{
  Wire.beginTransmission(i2cAddress);
  Wire.write(SMBUS_VOLTAGE);
  
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
    case 3: // Its upto the user on whether to read the data in this case. Sometimes, you might want to read it, sometime not
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
//      3: status error; read status

byte Batmon::readTherms(Therms &ts, byte num)
{
	if( num > 2)
		return 3;
   
	Wire.beginTransmission(i2cAddress);
	if( num ==0 )
	{
		Wire.write(SMBUS_TEMP);
	}
	else if(num ==1)
	{
		Wire.write(SMBUS_TEMP);
	}
	else if(num ==2)
	{
		Wire.write(SMBUS_TEMP);
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
		case 3: // Its upto the user on whether to read the data in this case. Sometimes, you might want to read it, sometime not
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

unsigned char* Batmon::getMan(unsigned char *buf){
  Wire.beginTransmission(i2cAddress);
  Wire.write(0x20);
  Wire.endTransmission();
  int i = 0;
  if(Wire.requestFrom(i2cAddress,8)){
    while(Wire.available()){
      buf[i] = Wire.read();
      i++;
    }
  }
  return buf;
}

unsigned int Batmon::getCur(){
  unsigned int current; 
  Wire.beginTransmission(i2cAddress);
  Wire.write(SMBUS_CURRENT);
  Wire.endTransmission();
  if(Wire.requestFrom(i2cAddress,3)){
    current = (int)Wire.read();
    current |= (int)Wire.read()<<8;
    Wire.read();
  }
  return current;
}

float Batmon::read_mAh_discharged(){
  unsigned int discharged;
  Wire.beginTransmission(i2cAddress);
  Wire.write(SMBUS_MAH_DISCHARGED);
  Wire.endTransmission();
  if(Wire.requestFrom(i2cAddress,3)){
    discharged = (unsigned int)Wire.read();
    discharged |= (unsigned int)Wire.read()<<8;
    Wire.read(); //throw out crc
  }
  return (float)discharged;
}
