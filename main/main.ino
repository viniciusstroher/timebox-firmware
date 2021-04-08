#include "Arduino.h"
#include "bluetooth.h"
#include "giroscope.h"
#include "clock.h"

#define BOARD_SPEED 115200

BluetoothHandler* bluetoothHandler;
Giroscope* giroscope;
GiroscopeData giroscopeData;
Clock* clock1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BOARD_SPEED);

  giroscope->setup();

  bluetoothHandler = new BluetoothHandler();
  bluetoothHandler->setup();
  bluetoothHandler->startServer();
  bluetoothHandler->startAdversiting();

  clock1 = new Clock(1617845194); //unix
}

void loop() {
  
  clock1->getTime();
  
  bluetoothHandler->getConnectedCount();
  if(bluetoothHandler->isDeviceConnected()){
    //envia dados ao dispositivo conectado
    
    giroscopeData = giroscope->read();
    
    bluetoothHandler->send("testando");
  }else{
    bluetoothHandler->startAdversiting();
  }
  
  delay(5000);
}
