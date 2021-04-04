#include "Arduino.h"
#include <Wire.h>

#define MPU_ADDR_GIROSCOPE           0x68
#define PWR_MGMT_1 0x6B
#define ACCEL_XOUT_H "0x3B"

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

class Giroscope{
  public:
    void setup();
    GiroscopeData read();
  private:
    int sda_pin;
    int scl_pin; 
};
