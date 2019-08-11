#pragma once

#define I2CADDRESS1 0x0B // x = (not filled) y = (not filled) (Default for SMbus smart batteries)
#define I2CADDRESS2 0x0B // x = (not filled) y = (filled)
#define I2CADDRESS3 0x0B // x = (filled) y = (not filled)
#define I2CADDRESS4 0x0B // x = (filled) y = (filled)

//SMBUS Register enumeration
#define SMBUS_VOLTAGE 0x09
#define SMBUS_CURRENT 0x0a
#define SMBUS_AVG_CURRENT 0x0b
#define SMBUS_TEMP 0x08
#define SMBUS_MAN_NAME 0x20
#define SMBUS_MAN_DATE 0x1b
#define SMBUS_SERIAL_NUM 0x1c
#define SMBUS_RUN_TIME_TO_EMPTY 0x11
#define SMBUS_AVG_TIME_TO_EMPTY 0x12
#define SMBUS_RELATIVE_SOC 0x0d
#define SMBUS_REMAIN_CAP 0x0f
#define SMBUS_FULL_CAP 0x10
#define SMBUS_CYCLE_COUNT 0x17
#define SMBUS_VCELL1 0x3c
#define SMBUS_VCELL2 0x3d
#define SMBUS_VCELL3 0x3e
#define SMBUS_VCELL4 0x3f
#define SMBUS_VCELL5 0x40
#define SMBUS_VCELL6 0x41
#define SMBUS_VCELL7 0x42
#define SMBUS_VCELL8 0x43
#define SMBUS_VCELL9 0x44
#define SMBUS_VCELL10 0x45

//EEPROM parameter addresses
#define EEPROM_SHUNT_VAL_SET 0
#define EEPROM_CAPACITY_SET 2

//Defines for BATMON specific I2C functionality
#define BATMON_MAIN_RESET_ADDRESS 0x90
#define BATMON_BQ_RESET_ADDRESS 0x91
#define BATMON_SHUNT_VAL_SET_ADDRESS 0x92
#define BATMON_CAPACITY_SET_ADDRESS 0x93

//For reference: pixhawk must have 8,9,a,b,f,10,11,12,17,1b,1c,20,3c to 45 reserved
/*
#define READTHERM0 0x10
#define READTHERM1 0x11
#define READTHERM2 0x12
#define READTOTVOLTAGE 0x13
#define READCELLVOLTAGES 0x14
#define READSTATUS 0x15
#define SHUTDOWN 0x16
#define POWERUP 0x17
Can't use these because conflicts*/


// STATUS messages 
#define BATMON_NOT_BOOTED 0x43
#define ADC_CHIP_CONNECTION_ERROR 0x44
#define ADC_CANT_WRITE_CHIP 0x45
#define ADC_CHIP_NOT_FOUND 0x46
#define ADC_I2C_ERROR 0x47
#define BATMON_READY 0x48
#define DEF_ERROR 0x49
#define BATMON_SLEEPING 0x40

//typedef struct _Batmon_struct{
	struct Batmon_thermistors{

		union
		{
			struct
			{
				unsigned char T2_HI;
				unsigned char T2_LO;
			}T2Byte;
			unsigned short T2Word; // temperature *10 (deg C)
		}T2;
		
		union
		{
			struct
			{
				unsigned char T1_HI;
				unsigned char T1_LO;
			}T1Byte;
			unsigned short T1Word; // temperature *10 (deg C)
		}T1;
		
		union
		{
			struct
			{
				unsigned char T_int_HI;
				unsigned char T_int_LO;
			}T_int_Byte;
			unsigned short T_int_Word; // temperature *10 (deg C)
		}T_int;
    unsigned char CRC;
	};

  struct Batmon_totalVoltage{
  	union {
  		struct
  		{
  			unsigned char VTot_HI;
  			unsigned char VTot_LO;
  		}VTotByte;
  		unsigned short VTotWord; //mV
  	}TV;
   unsigned char CRC;
  };
	
	struct Batmon_cellVoltages{
		union
		{
			struct
			{
				unsigned char VC1_HI;
				unsigned char VC1_LO;
			}VCell1Byte;
			unsigned short VCell1Word; //mV
		}VCell1;
		union
		{
			struct
			{
				unsigned char VC2_HI;
				unsigned char VC2_LO;
			}VCell2Byte;
			unsigned short VCell2Word; //mV
		}VCell2;
		union
		{
			struct
			{
				unsigned char VC3_HI;
				unsigned char VC3_LO;
			}VCell3Byte;
			unsigned short VCell3Word; //mV
		}VCell3;
		union
		{
			struct
			{
				unsigned char VC4_HI;
				unsigned char VC4_LO;
			}VCell4Byte;
			unsigned short VCell4Word; //mV
		}VCell4;
		union
		{
			struct
			{
				unsigned char VC5_HI;
				unsigned char VC5_LO;
			}VCell5Byte;
			unsigned short VCell5Word;
		}VCell5;
		union
		{
			struct
			{
				unsigned char VC6_HI;
				unsigned char VC6_LO;
			}VCell6Byte;
			unsigned short VCell6Word;
		}VCell6;
		union
		{
			struct
			{
				unsigned char VC7_HI;
				unsigned char VC7_LO;
			}VCell7Byte;
			unsigned short VCell7Word;
		}VCell7;
		union
		{
			struct
			{
				unsigned char VC8_HI;
				unsigned char VC8_LO;
			}VCell8Byte;
			unsigned short VCell8Word;
		}VCell8;
		union
		{
			struct
			{
				unsigned char VC9_HI;
				unsigned char VC9_LO;
			}VCell9Byte;
			unsigned short VCell9Word;
		}VCell9;
		union
		{
			struct
			{
				unsigned char VC10_HI;
				unsigned char VC10_LO;
			}VCell10Byte;
			unsigned short VCell10Word;
		}VCell10;
    unsigned char CRC;
	};
//}Batmon_struct;
