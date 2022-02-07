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

#define I2CADDRESS1 0x0E
#define I2CADDRESS2 0x0D
#define I2CADDRESS3 0x0C
#define I2CADDRESS4 0x0B // (Default for SMbus smart batteries)

//SMBUS Register enumeration
enum smbus_reg : unsigned char
{
  SMBUS_VOLTAGE = 0x09,         // <Total volt            > <uint16> <format mV > <WordRead>
  SMBUS_CURRENT = 0x0a,         // <Current             > <int16_t> <format mA> <WordRead>. TODO: implement different variable for higher than ~32A
  SMBUS_AVG_CURRENT = 0x0b,     // Not implemented
  SMBUS_TEMP_INT = 0x08,        // <Battery Temperature       > <uint16> <format deciKelvin > <WordRead>
  SMBUS_TEMP_EXT = 0x07,        // TODO: This needs to be removed as it conflicts with SBS protocol. 
  SMBUS_MAN_NAME = 0x20,        // <Manufacturer Name "Rotoye"    > <char*> <format > <BlockRead>
  SMBUS_MAN_DATE = 0x1b,
  SMBUS_SERIAL_NUM = 0x1c,          // Send a hashed serial number based on SAM device's UID
  SMBUS_FULL_SERIAL = 0x23,         // Send the full 128 bit SAM device UID, SBS:ManufacturerData <hex> <128bit serial number> <BlockRead>
  SMBUS_RUN_TIME_TO_EMPTY = 0x11,   //  Not implemented
  SMBUS_AVG_TIME_TO_EMPTY = 0x12,   //  Not implemented
  SMBUS_RELATIVE_SOC = 0x0d,        // <Remaining capacity        > <uint16> <format %  > <WordRead>
  SMBUS_REMAIN_CAP = 0x0f,        // <Remaining capacity        > <uint16> <format mAh> <WordRead>
  SMBUS_FULL_CAP = 0x10,          // <Full capacity         > <uint16> <format mAh> <WordRead>
  SMBUS_CYCLE_COUNT = 0x17,       // <Number of cycles on the battery > <uint16> <format num> <WordRead>
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

typedef unsigned char uint8_t;
typedef long unsigned int uint32_t;

//typedef struct _Batmon_struct
struct Batmon_thermistors
{

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

struct Batmon_totalVoltage
{
  union
  {
    struct
    {
      unsigned char VTot_HI;
      unsigned char VTot_LO;
    }VTotByte;
    unsigned short VTotWord; //mV
  }TV;
  unsigned char CRC;
};

struct Batmon_cellVoltages
{
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
  union
  {
    struct
    {
      unsigned char VC11_HI;
      unsigned char VC11_LO;
    }VCell11Byte;
    unsigned short VCell11Word;
  }VCell11;
  union
  {
    struct
    {
      unsigned char VC12_HI;
      unsigned char VC12_LO;
    }VCell12Byte;
    unsigned short VCell12Word;
  }VCell12;
  unsigned char CRC;
};
//}Batmon_struct;

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
