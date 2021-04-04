#include "Arduino.h"
#include "bluetooth.h"
#include "giroscope.h"

BluetoothHandler* bluetoothHandler;
Giroscope* giroscope;
GiroscopeData giroscopeData;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  giroscope->setup();

  bluetoothHandler = new BluetoothHandler();
  bluetoothHandler->setup();
  bluetoothHandler->start();
}

void loop() {
  if(bluetoothHandler->isDeviceConnected()){
    //envia dados ao dispositivo conectado
    
    giroscopeData = giroscope->read();
    
    bluetoothHandler->send("testando");
  }
  
  delay(5000);
}
