#include "bluetooth.h"
#include "bluetooth_callback.h"

BluetoothHandler::BluetoothHandler()
{
  BLEDevice::init("ESP32");
  
  Serial.print("\n[info] init ble \n");

}

void BluetoothHandler::setup() {
  // Configura o dispositivo como Servidor BLE
  bsc = new BluetoothServerCallbacks();
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(bsc);

  Serial.print("\n[info] create ble server \n");
  
  // Cria o servico UART
  pService = pServer->createService(SERVICE_UUID);

    // Cria uma Característica BLE para envio dos dados
  pCharacteristicTx = pService->createCharacteristic(
                        DHTDATA_CHAR_UUID,
                        BLECharacteristic::PROPERTY_NOTIFY
                      );
                       
  pCharacteristicTx->addDescriptor(new BLE2902());

  Serial.print("\n[info] create tx \n");
  
  // cria uma característica BLE para recebimento dos dados
  pCharacteristicRx = pService->createCharacteristic(
                         CHARACTERISTIC_UUID_RX,
                         BLECharacteristic::PROPERTY_WRITE
                       );
  
  pCharacteristicRx->setCallbacks(new BluetoothCallbacks());

  Serial.print("\n[info] create ble rx \n");
}

void BluetoothHandler::startServer(){
  Serial.print("\n[info] start ble service \n");
  
  pService->start();
}

void BluetoothHandler::startAdversiting(){
  // Inicia a descoberta do ESP32
  pServer->getAdvertising()->start();

  Serial.print("\n[info] start ble discovery service \n");
}

void BluetoothHandler::send(String message){
   pCharacteristicTx->setValue(message.c_str());
   pCharacteristicTx->notify();

   Serial.print("\n[info] sending data "+message+"\n");
}

bool BluetoothHandler::isDeviceConnected(){
  return bsc->isDeviceConnected();
}

uint32_t BluetoothHandler::getConnectedCount(){
  uint32_t count = pServer->getConnectedCount();
  Serial.print("\n[info] connected clients "+String(count)+" \n");
  return count;
}
