#include "Arduino.h"

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

class BluetoothServerCallbacks: public BLEServerCallbacks
{
  public:
    void onConnect(BLEServer* pServer);
    void onDisconnect(BLEServer* pServer);
    bool isDeviceConnected();
  private:
    bool deviceConnected;
};
