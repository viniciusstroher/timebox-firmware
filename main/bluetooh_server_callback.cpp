#include "bluetooth_server_callback.h"

void BluetoothServerCallbacks::onConnect(BLEServer* pServer) {
  Serial.print("\n[info] device connected to ble server \n");
  deviceConnected = true;
}

void BluetoothServerCallbacks::onDisconnect(BLEServer* pServer) {
  Serial.print("\n[info] device disconnected to ble server \n");
  deviceConnected = false;
}

bool BluetoothServerCallbacks::isDeviceConnected(){
  return deviceConnected;
}
