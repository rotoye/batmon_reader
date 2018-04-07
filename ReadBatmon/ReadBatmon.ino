
#include <Wire.h>
#include "Batmon.h"

// Include the required Wire library for I2C<br>#include 
int x = 0;
uint8_t i2cAddress = 0x21;
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
  Serial.print( bm.readStatus(st));
  Serial.print("\t");
  Serial.print(st);
  Serial.print("\t");
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
  Serial.print( bm.readTherms(ts) );
  Serial.print("\t");
  Serial.print(ts.T_int.T_int_Word);
  Serial.print("\t");
  Serial.print(ts.T1.T1Word);
  Serial.print("\t");
  Serial.print(ts.T2.T2Word);

  Serial.println();

  bm.shutdown();
  delay(2000);
}

