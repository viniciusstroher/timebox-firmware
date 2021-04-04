#include "Arduino.h"

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

class BluetoothCallbacks: public BLECharacteristicCallbacks 
{
  public:
    void onWrite(BLECharacteristic *pCharacteristic);
};
