/**************************************************************************************************
*
*   Copyright (c) 2020-2022, SkyMul Inc.
*   All Rights Reserved.
*
*   BATMON and its associated brands and logos published in the website and source code
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
 * @file Batmon_struct.h
 *
 * @author Eohan George <eohan@rotoye.com>
 */

#pragma once
#include <stdint.h>
#include <math.h>

#define BATMON_SMBUS_TOTAL_ADDRESS 10
const uint8_t BATMON_SMBUS_ADDRESS_ARRAY[BATMON_SMBUS_TOTAL_ADDRESS] = {0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14};
// The default SMBUS address is first one. Other values can be selected based on resistance connected to CAN_ID pin
//									{Inf, 59k, 30k, 20k, 15k, 8.45k, 6.49k, 4.42k, 1.8k, 0}
#define ADC_TOTAL_THRESHOLD (BATMON_SMBUS_TOTAL_ADDRESS-1)
const uint8_t ADC_READING_THRESHOLD_ARRAY[ADC_TOTAL_THRESHOLD] = {13, 54, 84, 110, 132, 153, 172, 201, 230};

#define NUM_THERM_TO_READ 2     // Number of external thermistor to read
#define MAX_CELL_COUNT (12)
#define KELVIN_CELCIUS (273.15)
#define MEM_VOLT_STORAGE_RESOLUTION (20) // 1unit is 20mV

#define INT_RES_PER_MEMORY 4

//SMBUS Register enumeration
enum smbus_reg : uint8_t
{
  SMBUS_VOLTAGE = 0x09,         // <Total volt            > <uint16> <format mV > <WordRead>
  SMBUS_CURRENT = 0x0a,         // <Current             > <int16_t> <format mA> <WordRead>  
  SMBUS_AVG_CURRENT = 0x0b,     // Not implemented
  SMBUS_TEMP_INT = 0x08,        // <Board Temperature       > <uint16> <format deciKelvin > <WordRead>
  SMBUS_MAN_NAME = 0x20,        // <Manufacturer Name "Rotoye"    > <char*> <format > <BlockRead>
  SMBUS_MAN_DATE = 0x1b,
  SMBUS_SERIAL_NUM = 0x1c,          // Send a hashed serial number based on SAM device's UID
  SMBUS_MANUFACTURER_DATA = 0x23,         // Send the full 128 bit SAM device UID, SBS:ManufacturerData <hex> <128bit serial number> <BlockRead>
  SMBUS_RUN_TIME_TO_EMPTY = 0x11,   //  Not implemented
  SMBUS_AVG_TIME_TO_EMPTY = 0x12,   //  Not implemented
  SMBUS_CHG_CURRENT = 0x14,         // <Max Charging Current      > <int16_t> <format mA> <WordRead>
  SMBUS_CHG_VOLTAGE = 0x15,        // <Max Charging Voltage      > <int16_t> <format mV> <WordRead>
  SMBUS_BATT_STATUS = 0x16,        // <Battery Status bit   > <uint16_t>  Only over-temp alarm is implemented
  SMBUS_RELATIVE_SOC = 0x0d,        // <Remaining capacity        > <uint16> <format %  > <WordRead>
  SMBUS_REMAIN_CAP = 0x0f,        // <Remaining capacity        > <uint16> <format mAh> <WordRead>
  SMBUS_FULL_CAP = 0x10,          // <Full capacity         > <uint16> <format mAh> <WordRead>
  SMBUS_CYCLE_COUNT = 0x17,       // <Number of cycles on the battery > <uint16> <format num> <WordRead>
  // Reset the index of reading batmon memory back to zero, send the number of recorded memory, number of required read/write times for each memory object and the array of how many bytes are divided into each read/write, and status of memory reading
  SMBUS_RESET_BATMEM = 0x2e,      // <1 byte: byte count> <6 bytes: Bytes per memory record, number of partitions, 1st partition size, 2nd partition size, 3rd partition size, total number of memory records available> <1byte: CRC><BlockRead>
  SMBUS_BATMEM = 0x2f,            // <1 byte: byte count> <memory block size varies determined by getMemBlockSize func> <2 bytes block tag: block number AND memory index> <1byte: CRC> <BlockRead>
  SMBUS_BATT_HEALTH = 0x30,      //
  SMBUS_VCELL1 = 0x3f,        // <Cell Volt           > <uint16> <format mV > <WordRead>
  SMBUS_VCELL2 = 0x3e,          //  Same as above
  SMBUS_VCELL3 = 0x3d,          //  Same as above
  SMBUS_VCELL4 = 0x3c,          //  Same as above
  SMBUS_VCELL5 = 0x3b,          //  Same as above
  SMBUS_VCELL6 = 0x3a,          //  Same as above
  SMBUS_VCELL7 = 0x39,          //  Same as above
  SMBUS_VCELL8 = 0x38,          //  Same as above
  SMBUS_VCELL9 = 0x37,          //  Same as above
  SMBUS_VCELL10 = 0x36,         //  Same as above
  SMBUS_VCELL11 = 0x35,         //  Same as above
  SMBUS_VCELL12 = 0x34,         //  Same as above
  SMBUS_CELL_COUNT = 0x40,        // <Cell Volt           > <uint16> <format num> <WordRead>
  SMBUS_DECI_CURRENT = 0x41,	// <Current             > <int16_t> <format deci Ampere> <WordRead>
  SMBUS_TEMP_EXTERNAL_1 = 0x48, // <Battery Temperature 1> <uint16> <format deciKelvin > <WordRead>
  SMBUS_TEMP_EXTERNAL_2 = 0X49, // <Battery Temperature 2> <uint16> <format deciKelvin > <WordRead>
  SMBUS_SAFETY_STATUS = 0x51,     // <SafetyStatus structure below  > <ByteArray> <format SafetyStatus> <BlockRead>
  SMBUS_ALERT_STATUS = 0x50,        // Not implemented
  SMBUS_MAH_DISCHARGED = 0x4f,

  
  //EEPROM parameter addresses
  EEPROM_SHUNT_VAL_SET = 0,
  EEPROM_CAPACITY_SET = 2,
  EEPROM_EST_SET = 4,

  //Defines for BATMON specific I2C functionality : Not using this now.
  BATMON_MAIN_RESET_ADDRESS = 0x90,
  BATMON_BQ_RESET_ADDRESS = 0x91,
  BATMON_SHUNT_VAL_SET_ADDRESS = 0x92,
  BATMON_CAPACITY_SET_ADDRESS = 0x93
};

//For reference: pixhawk must have 8,9,a,b,f,10,11,12,17,1b,1c,20,3c to 45 reserved
//#define READTHERM0 0x10
//#define READTHERM1 0x11
//#define READTHERM2 0x12
//#define READTOTVOLTAGE 0x13
//#define READCELLVOLTAGES 0x14
//#define READSTATUS 0x15
//#define SHUTDOWN 0x16
//#define POWERUP 0x17
//Can't use these because conflicts


// STATUS messages
#define BATMON_NOT_BOOTED 0x43
#define ADC_CHIP_CONNECTION_ERROR 0x44
#define ADC_CANT_WRITE_CHIP 0x45
#define ADC_CHIP_NOT_FOUND 0x46
#define ADC_I2C_ERROR 0x47
#define BATMON_READY 0x48
#define DEF_ERROR 0x49
#define BATMON_SLEEPING 0x40

//typedef struct _Batmon_struct
struct Batmon_thermistors
{
  union
  {
    struct
    {
      uint8_t T_HI;
      uint8_t T_LO;
    }TByte;
    unsigned short TWord; // decikelvin
  }T2,T1,T_int;
	uint8_t CRC;
};

struct Batmon_totalVoltage
{
  union
  {
    struct
    {
      uint8_t VTot_HI;
      uint8_t VTot_LO;
    }VTotByte;
    unsigned short VTotWord; //mV
  }TV;
  uint8_t CRC;
};

struct Batmon_cellVoltages
{
  union
  {
    struct
    {
      uint8_t VC_HI;
      uint8_t VC_LO;
    }VCellByte;
    unsigned short VCellWord; //mV
  }VCell[MAX_CELL_COUNT];
  uint8_t CRC;
};
//}Batmon_struct;
struct BatteryStatus
{
	union {
		struct {
			uint8_t reserved_0123:4;
			uint8_t FULLY_DISCHARGED:1;
			uint8_t FULLY_CHARGED:1;
			uint8_t DISCHARGING:1;
			uint8_t INITIALIZED:1;
			uint8_t REMAINING_TIME_ALARM:1;
			uint8_t REMAINING_CAPACITY_ALARM:1;
			uint8_t reserved_10:1;
			uint8_t TERMINAT_DISCHARGE_ALARM:1;
			uint8_t OVER_TEMP_ALARM:1;
			uint8_t reserved_13:1;
			uint8_t TERMINATE_CHARGE_ALARM:1;
			uint8_t OVER_CHARGED_ALARM:1;
		}bits;
		uint16_t status;
	};
};

struct SafetyStatus
{
  uint8_t len = 4;
  union
  {
    struct
    {
      uint8_t _rsvd_31:1;
      uint8_t _rsvd_30:1;
      uint8_t FLAG_DISCHARGE_OVERCURRENT:1;
      uint8_t FLAG_CELL_OVERVOLTAGE_LATCH:1;
      uint8_t FLAG_DISCHARGE_UNDERTEMP:1;
      uint8_t FLAG_CHARGE_UNDERTEMP:1;
      uint8_t FLAG_OVERPRECHARGE_CURRENT:1;
      uint8_t FLAG_OVERCHARGE_VOLTAGE:1;
      uint8_t FLAG_OVERCHARGE_CURRENT:1;
      uint8_t FLAG_OVERCHARGE:1;
      uint8_t _rsvd_21:1;
      uint8_t FLAG_CHARGE_TIMEOUT:1;
      uint8_t _rsvd_19:1;
      uint8_t FLAG_PRECHARGE_TIMEOUT:1;
      uint8_t _rsvd_17:1;
      uint8_t FLAG_FET_OVERTEMP:1;
      uint8_t _rsvd_15:1;
      uint8_t FLAG_CELL_UNDERVOLTAGE_COMPENSATED:1;
      uint8_t FLAG_DISCHARGE_OVERTEMP:1;
      uint8_t FLAG_CHARGE_OVERTEMP:1;
      uint8_t FLAG_DISHCARGE_LATCH_SHORT_CIRCUIT:1;
      uint8_t FLAG_DISCHARGE_SHORT_CIRCUIT:1;
      uint8_t FLAG_CHARGE_LATCH_SHORT_CIRCUIT:1;
      uint8_t FLAG_CHARGE_SHORT_CIRCUIT:1;
      uint8_t FLAG_DISCHARGE_LATCH_OVERLOAD:1;
      uint8_t FLAG_DISCHARGE_OVERLOAD:1;
      uint8_t FLAG_DISCHARGE_OVERCURRENT_2:1;
      uint8_t FLAG_DISCHARGE_OVERCURRENT_1:1;
      uint8_t FLAG_CHARGE_OVERCURRENT_2:1;
      uint8_t FLAG_CHARGE_OVERCURRENT_1:1;
      uint8_t FLAG_CELL_OVERVOLTAGE:1;
      uint8_t FLAG_CELL_UNDERVOLTAGE:1;
    }flags;
    uint32_t data;
  }flag;
  uint8_t crc;
};

#define MEMORY_TEMP_OFFSET (-225) //Unit in Kelvin
#define MEMORY_BLOCK_SIZE 64 //Current implementation only support up to 64. Any number greater than 64 would not be valid
#if (MEMORY_BLOCK_SIZE <= 56)
	#define NUM_MEMORY_BLOCK_PARTITION 2
#else
	#define NUM_MEMORY_BLOCK_PARTITION 3     //Note: Memory block size larger than 64 byte (page size) is currently not supported
#endif
#pragma pack(push, 1)
struct intResConditions {
	union {
		struct {
			uint8_t current_interval:3;
			uint8_t temperature_interval:3;
			uint8_t SOC_interval:2;
		}tag;
		uint8_t int_res_tag;
	};
};

struct IntRes{
	intResConditions intResTag;
	uint8_t minIntRes;
	uint8_t maxIntRes;
	struct {
		uint8_t minIntResIndex:4;
		uint8_t maxIntResIndex:4;
	}IntResIndices;
};

struct BatmonMemory {
	union {
		struct {
			// Note that the variables may be packed to be word aligned. So aligned it as a word
			//	address may be needed
			uint8_t memoryIndex;
			uint8_t minSOC; //0-255 instead of 0-100?
			uint8_t maxSOC; //0-255 instead of 0-100?
			uint8_t SOH; //0-255 instead of 0-100?
			uint8_t minTempCycle;             // Unit is in Celsius with MEMORY_TEMP_OFFSET K offset
			uint8_t maxTempCycle;             // Unit is in Celsius with MEMORY_TEMP_OFFSET K offset
			uint16_t maxDrainedCurrentEver;	  // The unit is Amps
			struct{
				uint16_t battCycle:14; 
				uint8_t loggedWithoutSleep:1; // bit is one if the log was created in between a run.
				uint8_t recNewCycle:1;		  // bit is one if the cycle was incremented in this record
			}log;
			uint8_t bootupMinCellVIndex:4;
			uint8_t bootupMaxCellVIndex:4;
			uint8_t bootupMinCellV;			  // Unit: custom. check membyteToMilliVolt()
			uint8_t bootupMaxCellV;			  // Unit: custom. check membyteToMilliVolt()
			uint8_t shutdownMinCellVIndex:4;
			uint8_t shutdownMaxCellVIndex:4;
			uint8_t shutdownMinCellV;		  // Unit: custom. check membyteToMilliVolt()
			uint8_t shutdownMaxCellV;		  // Unit: custom. check membyteToMilliVolt()
			uint16_t shutdownRemainCap;		  // Capacity available during shutdown in mAh
			uint32_t accumulatedCharged:20;	  // Accumulated Charge in current memory record cycle. Unit: mAh
			uint32_t accumulatedDischarged:20;// Accumulated Discharge in current memory record cycle. Unit: mAh
			IntRes intRes[INT_RES_PER_MEMORY];
		}data;
		uint8_t bytedata[MEMORY_BLOCK_SIZE];
	};
	uint16_t membyteToMilliVolt(uint8_t memByte){
		return ((uint16_t)memByte)*MEM_VOLT_STORAGE_RESOLUTION;
	}
	uint8_t milliVoltToMembyte(uint16_t milliVolt){
		return (uint8_t)(milliVolt*(1.0/MEM_VOLT_STORAGE_RESOLUTION));
	}
	uint8_t decikelvinToMembyte(uint16_t temperature){
		float byteTemp = temperature*0.1 + MEMORY_TEMP_OFFSET;
		return (uint8_t) floatToUint(byteTemp,0,UINT8_MAX);
	}
	uint16_t MembyteToDecikelvin(uint8_t short memByte){
		uint16_t temp = memByte;
		temp = (temp -MEMORY_TEMP_OFFSET)*10;
		return temp;
	}
	inline uint32_t floatToUint(float f, uint32_t min, uint32_t max){
		if (f <= min)	f = min;
		if (f >= max)	f = max;
		return round(f);
	}
};

struct BATMON_Mem_Info{
	uint8_t length;
	struct {
		uint8_t bytesPerRecord;
		uint8_t numPartitionsPerRecord;
		uint8_t bytesinPartition1;
		uint8_t bytesinPartition2;
		uint8_t bytesinPartition3;
		uint8_t totalMemoryRecords;
	}data;
  uint8_t crc;
};

#pragma pack(pop)