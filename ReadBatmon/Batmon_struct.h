#pragma once

#define i2cAddress1 0x21

#define readTherm0 0x10
#define readTherm1 0x11
#define readTherm2 0x12

#define statusWait 0xE0
#define statusReady 0xE1
#define statusError 0xE2

//typedef struct _Batmon_struct{
	struct Batmon_thermistors{

		union
		{
			struct
			{
				unsigned char T2_HI;
				unsigned char T2_LO;
			}T2Byte;
			unsigned short T2Word;
		}T2;
		
		union
		{
			struct
			{
				unsigned char T1_HI;
				unsigned char T1_LO;
			}T1Byte;
			unsigned short T1Word;
		}T1;
		
		union
		{
			struct
			{
				unsigned char T_int_HI;
				unsigned char T_int_LO;
			}T_int_Byte;
			unsigned short T_int_Word;
		}T_int;
	};
	
	union Batmon_totalVoltage{
		struct
		{
			unsigned char VTot_HI;
			unsigned char VTot_LO;
		}VTotByte;
		unsigned short VTotWord;
	};
	
	struct Batmon_cellVoltages{
		union
		{
			struct
			{
				unsigned char VC1_HI;
				unsigned char VC1_LO;
			}VCell1Byte;
			unsigned short VCell1Word;
		}VCell1;
		union
		{
			struct
			{
				unsigned char VC2_HI;
				unsigned char VC2_LO;
			}VCell1Byte;
			unsigned short VCell2Word;
		}VCell2;
		union
		{
			struct
			{
				unsigned char VC3_HI;
				unsigned char VC3_LO;
			}VCell1Byte;
			unsigned short VCell3Word;
		}VCell3;
		union
		{
			struct
			{
				unsigned char VC4_HI;
				unsigned char VC4_LO;
			}VCell1Byte;
			unsigned short VCell4Word;
		}VCell4;
		union
		{
			struct
			{
				unsigned char VC5_HI;
				unsigned char VC5_LO;
			}VCell1Byte;
			unsigned short VCell5Word;
		}VCell5;
		union
		{
			struct
			{
				unsigned char VC6_HI;
				unsigned char VC6_LO;
			}VCell1Byte;
			unsigned short VCell6Word;
		}VCell6;
		union
		{
			struct
			{
				unsigned char VC7_HI;
				unsigned char VC7_LO;
			}VCell1Byte;
			unsigned short VCell7Word;
		}VCell7;
		union
		{
			struct
			{
				unsigned char VC8_HI;
				unsigned char VC8_LO;
			}VCell1Byte;
			unsigned short VCell8Word;
		}VCell8;
		union
		{
			struct
			{
				unsigned char VC9_HI;
				unsigned char VC9_LO;
			}VCell1Byte;
			unsigned short VCell9Word;
		}VCell9;
		union
		{
			struct
			{
				unsigned char VC10_HI;
				unsigned char VC10_LO;
			}VCell1Byte;
			unsigned short VCell10Word;
		}VCell10;
	};
//}Batmon_struct;