
#include <Wire.h>
#include "Batmon.h"

// Include the required Wire library for I2C<br>#include 
int x = 0;
uint8_t i2cAddress = 0x21;
Batmon bm(i2cAddress ,0);
CVolts cv;
TotVolt tv;
Therms ts;
#define num
void setup() {
  // Start the I2C Bus as Master
  Serial.begin(115200);
  Serial.println("Read Batmon");
  Wire.setClock(100000);
}
void loop() {
  Serial.print( bm.readCellVoltages(cv) );
  Serial.print("\t");
  Serial.print( bm.readTotalVoltage(tv) );
  Serial.print("\t");
  unsigned short *ptr = (unsigned short *)&cv;
  Serial.print(tv.TV.VTotWord);
  Serial.print("\t");
  for(int i =0;i<10;i++)
  {
    Serial.print(ptr[i]); 
    Serial.print("\t");
  }
  Serial.print("\t||\t");
  Serial.print( bm.readTherms(ts,0) );
  Serial.print("\t");
  Serial.print(ts.T_int.T_int_Word);
  Serial.println();
  /*
  uint8_t numB= 10, actNum, tranErr;
  Wire.beginTransmission(i2cAddress);
  Wire.write(0x11);
  tranErr = Wire.endTransmission(false);
  actNum = Wire.requestFrom(i2cAddress, numB);
  
  Serial.print(tranErr);
  Serial.print(" -- ");

  Serial.print(actNum);
  Serial.print(" -- ");
  for (int i =0;i<10;i++)
  {
    Serial.print((unsigned char)Wire.read()); 
    Serial.print("  ");
  }
  Serial.println();*/
  /*
  Serial.println("Read Batmon 1");
  byte a = bm.readTherms(ts);
  Serial.print(a);
  Serial.print( " ---- ");
//  Serial.println(ts.T2Byte.T2_HI);
//  Serial.println(ts.T2Byte.T2_LO);
  Serial.print(ts.T2.T2Byte.T2_HI);
  Serial.print( " ---- ");
  Serial.println(ts.T2.T2Byte.T2_LO);  
  */
  delay(200);
}

