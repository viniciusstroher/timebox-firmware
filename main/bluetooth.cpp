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

void BluetoothHandler::start(){
  Serial.print("\n[info] start ble service \n");
  
  pService->start();

  // Inicia a descoberta do ESP32
  pServer->getAdvertising()->start();

  Serial.print("\n[info] start ble discovery service \n");
}
