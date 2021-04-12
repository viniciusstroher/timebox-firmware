#include "Arduino.h"
#include <Wire.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#include <ArduinoJson.h>

class Giroscope {
  public:
    Giroscope();
    void setup();
    void read();
    String readAsJson();
    void print();
  private:
    Adafruit_MPU6050 mpu;
    sensors_event_t a, g, temp;
};
