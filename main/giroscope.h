#include "Arduino.h"
#include <Wire.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

const uint8_t MPU6050SlaveAddress = 0x68;
const uint16_t AccelScaleFactor = 16384;
const uint16_t GyroScaleFactor = 131;
const uint8_t MPU6050_REGISTER_SMPLRT_DIV   =  0x19;
const uint8_t MPU6050_REGISTER_USER_CTRL    =  0x6A;
const uint8_t MPU6050_REGISTER_PWR_MGMT_1   =  0x6B;
const uint8_t MPU6050_REGISTER_PWR_MGMT_2   =  0x6C;
const uint8_t MPU6050_REGISTER_CONFIG       =  0x1A;
const uint8_t MPU6050_REGISTER_GYRO_CONFIG  =  0x1B;
const uint8_t MPU6050_REGISTER_ACCEL_CONFIG =  0x1C;
const uint8_t MPU6050_REGISTER_FIFO_EN      =  0x23;
const uint8_t MPU6050_REGISTER_INT_ENABLE   =  0x38;
const uint8_t MPU6050_REGISTER_ACCEL_XOUT_H =  0x3B;
const uint8_t MPU6050_REGISTER_SIGNAL_PATH_RESET  = 0x68;

struct giroscope_data {
  int16_t AcX;
  int16_t AcY;
  int16_t AcZ;
  int16_t Tmp;
  int16_t GyX;
  int16_t GyY;
  int16_t GyZ;
};
typedef struct giroscope_data GiroscopeData;

class Giroscope {
  public:
    Giroscope();
    void setup();
    GiroscopeData read();
    int getState();
    void print();
    void readRaw(uint8_t deviceAddress, uint8_t regAddress);

  private:
    void I2CWrite(uint8_t deviceAddress, uint8_t regAddress, uint8_t data);
    void calculateGyroscopeRaw();
    int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

};
