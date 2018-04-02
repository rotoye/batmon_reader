#include "Batmon.h"
#include <Wire.h>
Batmon::Batmon(byte _i2cAddress, byte _numTherms)
{
	i2cAddress = _i2cAddress;
	numTherms = _numTherms;
}

////////////////////////////////
// Return 0: No error
// 		  1: CRC error
// 		  2: i2c error
byte Batmon::readCellVoltages(CVolts &cv)
{
	
}
////////////////////////////////
// Return 0: No error
// 		  1: CRC error
// 		  2: i2c error
byte Batmon::readTotalVoltage(TotVolt &tv)
{
	
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
	byte error = 0;
	Wire.beginTransmission(i2cAddress);
	if( num ==0 )
	{
		Wire.write(readTherm0);
	}
	else if(num ==1)
	{
		Wire.write(readTherm1);
	}
	else if(num ==2)
	{
		Wire.write(readTherm2);
	}
	
	if(error ==0)
	{	
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
	}
	else if (error ==1)
	{
		Wire.endTransmission(true);
		return 2; // i2c error
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
		
		for(int i = 0; i < readNum-1;i++)
		{
			ptr[i] = Wire.read();
		}
		
		if (CRC8.smbus(ptr,readNum-1) == Wire.read())
		{
			return 0;
		}
		else
			return 1;
	}
	else 
		return 2;
	
}
	