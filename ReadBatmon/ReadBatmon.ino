#include <Wire.h>
#include "Batmon.h"

int x = 0;
uint8_t i2cAddress = I2CADDRESS4;
Batmon bm(i2cAddress, 2);
CVolts cv;
TotVolt tv;
Therms ts;

void setup()
{
  // Start the I2C Bus as Master
  Serial.begin(115200);
  //Serial.println("Read Batmon");
  Wire.setClock(100000);
  //Serial.println("Total Voltage, Cell 10, Cell 9, Cell 8, Cell 7, Cell 6, Cell 5, Cell 4, Cell 3, Cell 2, Cell 1, Current, Discharged Current");
}

void loop()
{
  byte st;
  //Serial.print("RdStat(i2c):");
  //Serial.print(bm.readStatus(st));
  //Serial.print(" Stat:");
  //Serial.print(st);
  //Serial.print(" RdCell(i2c):");
  bm.readCellVoltages(cv);
  //Serial.print(" RdTot(i2c):");
  bm.readTotalVoltage(tv);
  //Serial.print(" TotVolt:");
  unsigned short *ptr = (unsigned short *)&cv;
  Serial.print(tv.TV.VTotWord);
  Serial.print(",");
  for(int i = 0; i < 10; i++)
  {
    Serial.print(ptr[i]);
    Serial.print(",");
  }
  //Serial.print("|| RdTherm(i2c):");
  //Serial.print( bm.readTherms(ts) );
  //Serial.print(" T_int:");
  //Serial.print(ts.T_int.T_int_Word);
  //Serial.print(" T1:");
  //Serial.print(ts.T1.T1Word);
  //Serial.print(" T2:");
  //Serial.print(ts.T2.T2Word);

  //Serial.print("\tManufacturer's Name: ");
  //unsigned char man_name [20];
  //Serial.print((char *)bm.getMan(man_name));
  Serial.print("\t");
  Serial.print(bm.getCur());
  Serial.print(",\t");
  Serial.print(bm.read_mAh_discharged());
  Serial.print(",\t");
  Serial.print(bm.getSOC());
  Serial.print(",\t");
  Serial.print(bm.readRemainCap());
  Serial.print(",\t");
  Serial.print(bm.getTInt());
  Serial.print(",\t");
  Serial.print(bm.getTExt());
  Serial.print(",\t");

  Serial.println();

  //bm.shutdown();
  delay(200);
}
