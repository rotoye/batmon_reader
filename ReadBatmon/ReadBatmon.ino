
#include <Wire.h>
#include "Batmon.h"

// Include the required Wire library for I2C<br>#include 
int x = 0;
Batmon bm(0x21,0);
Therms ts;
#define num
void setup() {
  // Start the I2C Bus as Master
  Serial.begin(115200);
  Serial.println("Read Batmon");
}
void loop() {
  Serial.println("Read Batmon 1");
  byte a = bm.readTherms(ts);
  Serial.print(a);
  Serial.print( " ---- ");
//  Serial.println(ts.T2Byte.T2_HI);
//  Serial.println(ts.T2Byte.T2_LO);
  Serial.print(ts.T2.T2Byte.T2_HI);
  Serial.print( " ---- ");
  Serial.println(ts.T2.T2Byte.T2_LO);  
  delay(200);
}

