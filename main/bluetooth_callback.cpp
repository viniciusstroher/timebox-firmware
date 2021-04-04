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

  // Processa o caracter recebido do aplicativo. Se for A acende o LED. B apaga o LED
  if (rxValue.find("A") != -1) {
    Serial.println("Turning ON!");
    //    digitalWrite(LED, HIGH);
  }
  else if (rxValue.find("B") != -1) {
    Serial.println("Turning OFF!");
    //    digitalWrite(LED, LOW);
  }
}
