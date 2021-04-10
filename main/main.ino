#include "Arduino.h"
#include "bluetooth.h"
#include "giroscope.h"
#include "clock.h"

#define BOARD_SPEED 115200

BluetoothHandler* bluetoothHandler;
Giroscope* giroscope;
GiroscopeData giroscopeData;
Clock* clock1;
String timeNow;

void waitForSerialOpen(){
  while (!Serial){
    delay(10); //Espera serial
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BOARD_SPEED);
  waitForSerialOpen();

  giroscope = new Giroscope();
  giroscope->setup();

  bluetoothHandler = new BluetoothHandler();
  bluetoothHandler->setup();
  bluetoothHandler->startServer();
  bluetoothHandler->startAdversiting();

  clock1 = new Clock(1617848887); //unix
}

void loop() {
  
//  timeNow = clock1->getTime();
  giroscopeData = giroscope->read();
  giroscope->print();
  giroscope->getState();
  
  Serial.print("\n [info] current time "+timeNow+" \n");
  
  bluetoothHandler->getConnectedCount();
  if(bluetoothHandler->isDeviceConnected()){
    //envia dados ao dispositivo conectado
    
//    giroscopeData = giroscope->read();
//    giroscope->readRaw(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);
//    giroscope->getState();
    
    bluetoothHandler->send("testando");
  }else{
    bluetoothHandler->startAdversiting();
  }
  
  delay(5000);
}
