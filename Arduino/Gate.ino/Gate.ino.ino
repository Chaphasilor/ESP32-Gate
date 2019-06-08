#include <Arduino.h>
/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by chegewara
*/

// Bluetooth LE ---------------------------

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
bool deviceConnected = false;
BLEServer *pServer;
BLEService *pTempService;
BLECharacteristic *pTemp, *pTempType, *pLED, *pGate;
float currentTemp;

class ServerCallbacks: public BLEServerCallbacks { // server/connection event handlers
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class LEDCallbacks: public BLECharacteristicCallbacks { // characteristic event handlers
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (value == "on") {
      digitalWrite(2, HIGH);
      Serial.println("LED is on");
    } else {
      digitalWrite(2, LOW);
      Serial.println("LED is off");
    }
  }
};

int gatePin = 13;
int pulseLengthLow = 1000;
int pulseLengthHigh = 1000;

void setStateWithDelay(int pin, int state, int delayTime) {

  if(state==1)
    digitalWrite(pin,HIGH);
    // digitalWrite(2, HIGH);
  else
    digitalWrite(pin,LOW);
    // digitalWrite(2, LOW);

  delayMicroseconds((unsigned long) delayTime);

}

void sendTransmission() { // Funktelplaegramm für Gartentor

  for (int count = 0; count < 15; count++) {

  // Bitfolge Kanal 1:
  // 110100101101010101010010101100110011001011001101001011001011010100110101010010110011001011010101

    setStateWithDelay(gatePin, 0, 8000);  // passende Lücke zwischen den Paketen, Paketlänge insgesamt ca. 105 ms)
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthLow);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    digitalWrite(gatePin, LOW);
    Serial.println(count);
    }
}

class Gate: public BLECharacteristicCallbacks { // characteristic event handlers
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (value == "trigger") {
      // digitalWrite(2, HIGH);
      sendTransmission();
      Serial.println("Gate was triggered");
    } else {
      // digitalWrite(2, LOW);
      Serial.println("Gate was NOT triggered");
    }
  }
};

// Transmitter --------------------

// #include "RCSwitch.h"
//
// RCSwitch gateTransmitter = RCSwitch();

void setup() {
  Serial.begin(115200);

  // Bluetooth LE -----------------
  Serial.println("Starting BLE work!");

  BLEDevice::setPower(ESP_PWR_LVL_P7);
  BLEDevice::init("Gate");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks()); // define event handling

  pTempService = pServer->createService(BLEUUID((uint16_t)0x1809));
  // BLECharacteristic *pTempMeasure = pTempService->createCharacteristic(BLEUUID((uint16_t)0x2A1C), BLECharacteristic::PROPERTY_READ);
  pTemp = pTempService->createCharacteristic(BLEUUID((uint16_t)0x2A6E), BLECharacteristic::PROPERTY_READ);
  pTempType = pTempService->createCharacteristic(BLEUUID((uint16_t)0x2A1D), BLECharacteristic::PROPERTY_READ);

  pLED = pTempService->createCharacteristic(BLEUUID((uint16_t)0x25CD), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  pLED->setCallbacks(new LEDCallbacks()); // define event handling
  pGate = pTempService->createCharacteristic(BLEUUID((uint16_t)0xD64C), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  pGate->setCallbacks(new Gate()); // define event handling

  int typeKey = 1; // Armpit
  pTempType->setValue(typeKey);
  int currentTemp = 3690;
  pTemp->setValue(currentTemp);
  // int flags = 4; // 8Bit: 00000100 => 2nd Bit set to 1 => include temp type
  // int measuredTemp = 37.2;
  // int tempMeasureValue [3] = {flags, measuredTemp, typeKey};
  // pTempMeasure->setValue(tempMeasureValue);
  pLED->setValue("off");
  pGate->setValue("null");

  pTempService->addCharacteristic(pTemp);
  pTempService->addCharacteristic(pTempType);
  pTempService->addCharacteristic(pLED);
  pTempService->addCharacteristic(pGate);
  pTempService->start();


  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->addServiceUUID(BLEUUID((uint16_t)0x1809));
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  // Transmitter ------------------------

  pinMode(gatePin, OUTPUT);
  digitalWrite(gatePin, LOW);

  // gateTransmitter.enableTransmit(gatePin);    // Hier ist der Sende-Pin GPIO14 für den 868 Mhz Transmitter
  // gateTransmitter.setProtocol(1);
  // gateTransmitter.setPulseLength(1000);//  1ms, gemessen/probiert
  // gateTransmitter.setRepeatTransmit(1);   // 1 ist Minimum


}

void loop() {
  // put your main code here, to run repeatedly:

  if (deviceConnected) {
    // digitalWrite(2, HIGH);
    int newTemp = static_cast<int>(temperatureRead()*100);
    if (currentTemp != newTemp) {
      Serial.print("Setting temp to: ");
      Serial.println(newTemp);
      pTemp->setValue(newTemp);
    }
    currentTemp = newTemp;
  } else {
    // digitalWrite(2, LOW);
  }

  // Serial.print("Current temp: ");
  // Serial.print(currentTemp);
  // Serial.println("C");

  delay(5000);

}
