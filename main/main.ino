#include "Arduino.h"
#include "bluetooth.h"
#include "giroscope.h"
#include "clock.h"

#define BOARD_SPEED 115200

BluetoothHandler* bluetoothHandler;
Giroscope* giroscope;
Clock* clocker;
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

  clocker = new Clock(1617848887); //unix
}

void loop() {
  
//  timeNow = clocker->getTime();
  giroscope->read();
//  giroscope->print();

  Serial.print("\n [info] current time "+timeNow+" \n");
  
  bluetoothHandler->getConnectedCount();
  if(bluetoothHandler->isDeviceConnected()){
    //envia dados ao dispositivo conectado    
    String gyroscopeData = String(giroscope->readAsJson());
    bluetoothHandler->send(gyroscopeData);
  }else{
    //rodar este comando de 1 em 1 min
    bluetoothHandler->startAdversiting();
  }
  
  delay(5000);
}
