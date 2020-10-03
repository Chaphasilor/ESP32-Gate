#include <Arduino.h>

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
float currentTempFloat;
int currentTempInt;

void updateTemperature() {
  currentTempFloat = temperatureRead();
  currentTempInt = static_cast<int>(currentTempFloat*100);
  pTemp->setValue(currentTempInt);
}

class ServerCallbacks: public BLEServerCallbacks { // server/connection event handlers
    void onConnect(BLEServer* pServer) {
      updateTemperature();
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class TempCallbacks: public BLECharacteristicCallbacks { // characteristic event handlers
  void onRead() {
    updateTemperature();
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
  // 1101001011010101010010110100101010110101010101010100101011001101001101010100101100110011001100101

    setStateWithDelay(gatePin, 0, 8000);  // passende Lücke zwischen den Paketen, Paketlänge insgesamt ca. 105 ms)
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    setStateWithDelay(gatePin, 0, pulseLengthHigh);
    setStateWithDelay(gatePin, 1, pulseLengthHigh);
    digitalWrite(gatePin, LOW);
    Serial.println(count);
    }
}

class GateCallbacks: public BLECharacteristicCallbacks { // characteristic event handlers
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (value == "trigger") {
      digitalWrite(2, HIGH);
      sendTransmission();
      digitalWrite(2, LOW);
      Serial.println("Gate was triggered");
    } else {
      Serial.println("Gate was NOT triggered");
    }
  }
};

void setup() {
  Serial.begin(115200);

  // Bluetooth LE -----------------
  Serial.println("Starting BLE server!");

  BLEDevice::setPower(ESP_PWR_LVL_P7);
  BLEDevice::init("Gate");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks()); // define event handling

  pTempService = pServer->createService(BLEUUID((uint16_t)0x1809));
  pTemp = pTempService->createCharacteristic(BLEUUID((uint16_t)0x2A6E), BLECharacteristic::PROPERTY_READ);
  pTemp->setCallbacks(new TempCallbacks());
  pTempType = pTempService->createCharacteristic(BLEUUID((uint16_t)0x2A1D), BLECharacteristic::PROPERTY_READ);

  pLED = pTempService->createCharacteristic(BLEUUID((uint16_t)0x25CD), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  pLED->setCallbacks(new LEDCallbacks()); // define event handling
  pGate = pTempService->createCharacteristic(BLEUUID((uint16_t)0xD64C), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  pGate->setCallbacks(new GateCallbacks()); // define event handling

  int typeKey = 1; // Armpit
  pTempType->setValue(typeKey);
  int currentTemp = 3690;
  pTemp->setValue(currentTemp);
  pLED->setValue("off");
  pGate->setValue("null");

  pTempService->addCharacteristic(pTemp);
  pTempService->addCharacteristic(pTempType);
  pTempService->addCharacteristic(pLED);
  pTempService->addCharacteristic(pGate);
  pTempService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->addServiceUUID(BLEUUID((uint16_t)0x1809));
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Server initialized successfully!");

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  // Transmitter ------------------------

  pinMode(gatePin, OUTPUT);
  digitalWrite(gatePin, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

  if (deviceConnected) {
    Serial.println("A client is currently connected");
    Serial.print("Current temperature: ");
    Serial.print(currentTempFloat);
    Serial.println("°C");
  } else {
    Serial.println("No client connected");
  }

  delay(2000);
  
}
