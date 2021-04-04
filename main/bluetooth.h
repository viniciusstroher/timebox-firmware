#ifndef BluetoothHandler_h
#define BluetoothHandler_h

#include "Arduino.h"
#include "bluetooth_server_callback.h"


#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#include <iostream>
#include <string>

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define DHTDATA_CHAR_UUID "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

class BluetoothHandler
{
  public:
    BluetoothHandler();
    void setup();
    void startServer();
    void startAdversiting();
    void send(std::string message);
    bool isDeviceConnected();
    uint32_t getConnectedCount();
    
    BluetoothServerCallbacks* bsc;
    BLECharacteristic *pCharacteristicRx;
    BLECharacteristic *pCharacteristicTx;
  private:
    int _pin;
    
    BLEServer *pServer;
    BLEService *pService;
};

#endif
