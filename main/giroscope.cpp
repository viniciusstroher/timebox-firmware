#include "giroscope.h"

Giroscope::Giroscope(){}

void Giroscope::setup() 
{
  //INIT WIRES SD & SC
  Wire.begin(SDA, SCL);
  
  //SETUP GYRO
  delay(150);
  I2CWrite(MPU6050SlaveAddress, MPU6050_REGISTER_SMPLRT_DIV, 0x07);
  I2CWrite(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_1, 0x01);
  I2CWrite(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_2, 0x00);
  I2CWrite(MPU6050SlaveAddress, MPU6050_REGISTER_CONFIG, 0x00);
  I2CWrite(MPU6050SlaveAddress, MPU6050_REGISTER_GYRO_CONFIG, 0x00);//set +/-250 degree/second full scale
  I2CWrite(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_CONFIG, 0x00);// set +/- 2g full scale
  I2CWrite(MPU6050SlaveAddress, MPU6050_REGISTER_FIFO_EN, 0x00);
  I2CWrite(MPU6050SlaveAddress, MPU6050_REGISTER_INT_ENABLE, 0x01);
  I2CWrite(MPU6050SlaveAddress, MPU6050_REGISTER_SIGNAL_PATH_RESET, 0x00);
  I2CWrite(MPU6050SlaveAddress, MPU6050_REGISTER_USER_CTRL, 0x00);
}


void Giroscope::I2CWrite(uint8_t deviceAddress, uint8_t regAddress, uint8_t data){
  Wire.beginTransmission(deviceAddress);
  Wire.write(regAddress);
  Wire.write(data);
  Wire.endTransmission();
}

void Giroscope::readRaw(uint8_t deviceAddress, uint8_t regAddress) 
{
  
   Wire.beginTransmission(deviceAddress);
   Wire.write(regAddress);
   Wire.endTransmission();
   Wire.requestFrom(deviceAddress, (uint8_t)14);

   AcX = (((int16_t)Wire.read()<<8) | Wire.read());
   AcY = (((int16_t)Wire.read()<<8) | Wire.read());
   AcZ = (((int16_t)Wire.read()<<8) | Wire.read());
   Tmp = (((int16_t)Wire.read()<<8) | Wire.read());
   GyX = (((int16_t)Wire.read()<<8) | Wire.read());
   GyY = (((int16_t)Wire.read()<<8) | Wire.read());
   GyZ = (((int16_t)Wire.read()<<8) | Wire.read());
}

void Giroscope::calculateGyroscopeRaw(){
  AcX = (double)AcX/AccelScaleFactor;
  AcY = (double)AcY/AccelScaleFactor;
  AcZ = (double)AcZ/AccelScaleFactor;
  Tmp  = (double)Tmp/340+36.53; //temperature formula
  GyX = (double)GyX/GyroScaleFactor;
  GyY = (double)GyY/GyroScaleFactor;
  GyZ = (double)GyZ/GyroScaleFactor;
}


GiroscopeData Giroscope::read(){
   readRaw(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);
   calculateGyroscopeRaw();
   
   GiroscopeData giroscopeData;
   
   giroscopeData.AcX = AcX;
   giroscopeData.AcY = AcY;
   giroscopeData.AcZ = AcZ;
   giroscopeData.Tmp = Tmp;
   giroscopeData.GyX = GyX;
   giroscopeData.GyY = GyY;
   giroscopeData.GyZ = GyZ;

   return giroscopeData;
}

void Giroscope::print(){
   Serial.print("\n [info] accelerometer vals \n");
   Serial.print("\n [info] AcX: "+String(AcX)+" \n");
   Serial.print("\n [info] AcY: "+String(AcY)+" \n");
   Serial.print("\n [info] AcZ: "+String(AcZ)+" \n");
   Serial.print("\n [info] tmp vals \n");
   Serial.print("\n [info] Tmp: "+String(Tmp)+" \n");
   Serial.print("\n [info] giroscope vals \n");
   Serial.print("\n [info] GyX: "+String(GyX)+" \n");
   Serial.print("\n [info] GyY: "+String(GyY)+" \n");
   Serial.print("\n [info] GyZ: "+String(GyZ)+" \n");

}

int Giroscope::getState(){
  double x1 = 0.8;
  double x2 = -0.8;

  //eixo y
  double y1 = -0.8;
  double y2 = 0.8;

  //eixo z
  double z1 = 0.8;
  double z2 = -0.8;
  
  int face = 0;
  
  if (AcX > x1) {
    face = 4;
  } else if (AcX < x2) {
    face = 2;
  } else if (AcY < y1) {
    face = 5;
  } else if (AcY > y2) {
    face = 6;
  } else if (AcZ < y1) {
    face = 3;
  } else if (AcZ > z1){
    face = 1;
  }

  Serial.print("\n [info] Face: "+String(face)+" \n");
  
}
