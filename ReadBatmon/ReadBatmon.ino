
#include <Wire.h>
#include "Batmon.h"

// Include the required Wire library for I2C<br>#include 
int x = 0;
uint8_t i2cAddress = I2CADDRESS4;
Batmon bm(i2cAddress ,2);
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
  byte st;
  Serial.print("RdStat(i2c):");
  Serial.print( bm.readStatus(st));
  Serial.print(" Stat:");
  Serial.print(st);
  Serial.print(" RdCell(i2c):");
  Serial.print( bm.readCellVoltages(cv) );
  Serial.print(" RdTot(i2c):");
  Serial.print( bm.readTotalVoltage(tv) );
  Serial.print(" TotVolt:");
  unsigned short *ptr = (unsigned short *)&cv;
  Serial.print(tv.TV.VTotWord);
  Serial.print("\t");
  for(int i =0;i<10;i++)
  {
    Serial.print(ptr[i]); 
    Serial.print("\t");
  }
  Serial.print("|| RdTherm(i2c):");
  Serial.print( bm.readTherms(ts) );
  Serial.print(" T_int:");
  Serial.print(ts.T_int.T_int_Word);
  Serial.print(" T1:");
  Serial.print(ts.T1.T1Word);
  Serial.print(" T2:");
  Serial.print(ts.T2.T2Word);

  Serial.println();

  //bm.shutdown();
  delay(200);
}
