#include "giroscope.h"

Giroscope::Giroscope(){}

void Giroscope::setup() 
{
    if (!mpu.begin()) {
      Serial.println("Failed to find MPU6050 chip");
      while (1) {
        delay(10);
      }
    }
    
    Serial.println("MPU6050 Found!");
  
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void Giroscope::read(){
  mpu.getEvent(&a, &g, &temp);
}

String Giroscope::readAsJson(){
  StaticJsonDocument<200> doc;
  
  doc["AccelerationX"] = a.acceleration.x;
  doc["AccelerationY"] = a.acceleration.y;
  doc["AccelerationZ"] = a.acceleration.z;
  
  doc["GyroAccelerationX"] = g.gyro.x;
  doc["GyroAccelerationY"] = g.gyro.y;
  doc["GyroAccelerationZ"] = g.gyro.z;

  doc["Temp"] = temp.temperature;
  
  String jsonFormated;
  serializeJson(doc,jsonFormated);
  
  return jsonFormated;
}


void Giroscope::print(){
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

}
