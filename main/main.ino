#include "Arduino.h"
#include "bluetooth.h"

BluetoothHandler* bh;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  bh = new BluetoothHandler();
  bh->setup();
  bh->start();
}

void loop() {
  if(bh->bsc->isDeviceConnected()){
    //envia dados ao dispositivo conectado
    bh->pCharacteristicTx->setValue("#123#teste");
    bh->pCharacteristicTx->notify();
  }
  
  delay(5000);
}
