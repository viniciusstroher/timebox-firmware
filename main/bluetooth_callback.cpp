#include "bluetooth_callback.h"

void BluetoothCallbacks::onWrite(BLECharacteristic *pCharacteristic) {
  std::string rxValue = pCharacteristic->getValue();
  Serial.println(rxValue[0]);

  if (rxValue.length() > 0) {
    Serial.println("*********");
    Serial.print("Received Value: ");

    for (int i = 0; i < rxValue.length(); i++) {
      Serial.print(rxValue[i]);
    }
    Serial.println();
    Serial.println("*********");
  }
}
