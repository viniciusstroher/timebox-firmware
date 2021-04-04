#include "giroscope.h"

void Giroscope::setup() 
{
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR_GIROSCOPE);
  Wire.write(PWR_MGMT_1);
  Wire.write(0);
  Wire.endTransmission(true);
}

GiroscopeData Giroscope::read() 
{
   int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
   GiroscopeData returnGiro;
  
   Wire.beginTransmission(MPU_ADDR_GIROSCOPE);
   Wire.write(ACCEL_XOUT_H);  // starting with register 0x3B (ACCEL_XOUT_H)
   Wire.endTransmission(false);
   Wire.requestFrom(MPU_ADDR_GIROSCOPE,14,true);  // request a total of 14 registers
   
   AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
   AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
   AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
   
   //Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
   GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
   GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
   GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
   
 
   Serial.print("\n[info] accelerometer vals \n");
   Serial.print("\n[info] AcX: "+String(AcX)+" \n");
   Serial.print("\n[info] AcY: "+String(AcY)+" \n");
   Serial.print("\n[info] AcZ: "+String(AcZ)+" \n");
   Serial.print("\n[info] giroscope vals \n");
   Serial.print("\n[info] GyX: "+String(GyX)+" \n");
   Serial.print("\n[info] GyY: "+String(GyY)+" \n");
   Serial.print("\n[info] GyZ: "+String(GyZ)+" \n");
     
   returnGiro.AcX = AcX;
   returnGiro.AcY = AcY;
   returnGiro.AcZ = AcZ;
   returnGiro.Tmp = Tmp;
   returnGiro.GyX = GyX;
   returnGiro.GyY = GyY;
   returnGiro.GyZ = GyZ;

   return returnGiro;
}
