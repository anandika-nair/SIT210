#include <Wire.h>
#include <BH1750.h>
#include <ArduinoBLE.h>

BH1750 lightMeter;

// LED pins
const int bathroomLED = 2;
const int hallwayLED = 3;
const int fanLED = 4;

// Bluetooth service
BLEService lightService("180A");

// Bluetooth characteristic
BLEStringCharacteristic commandCharacteristic(
  "2A57",
  BLERead | BLEWrite,
  50
);

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // LED setup
  pinMode(bathroomLED, OUTPUT);
  pinMode(hallwayLED, OUTPUT);
  pinMode(fanLED, OUTPUT);

  digitalWrite(bathroomLED, LOW);
  digitalWrite(hallwayLED, LOW);
  digitalWrite(fanLED, LOW);

  // Start light sensor
  if (lightMeter.begin()) {
    Serial.println("BH1750 started");
  } else {
    Serial.println("BH1750 error");
  }

  // Start Bluetooth
  if (!BLE.begin()) {
    Serial.println("Bluetooth failed");
    while (1);
  }

  BLE.setLocalName("SmartLights");
  BLE.setAdvertisedService(lightService);

  lightService.addCharacteristic(commandCharacteristic);
  BLE.addService(lightService);

  commandCharacteristic.writeValue("");

  BLE.advertise();

  Serial.println("Bluetooth device active");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.println("Connected to central");

    while (central.connected()) {

      float lux = lightMeter.readLightLevel();

      if (commandCharacteristic.written()) {

        String command = commandCharacteristic.value();

        Serial.print("Command received: ");
        Serial.println(command);

        Serial.print("Light Level: ");
        Serial.println(lux);

        // Bathroom command
        if (command == "bathroom on") {

          if (lux < 50) {
            digitalWrite(bathroomLED, HIGH);
            Serial.println("Bathroom light ON");
          } else {
            Serial.println("Room already bright");
          }
        }

        // Hallway command
        else if (command == "hallway on") {

          if (lux < 50) {
            digitalWrite(hallwayLED, HIGH);
            Serial.println("Hallway light ON");
          } else {
            Serial.println("Room already bright");
          }
        }

        // Fan command
        else if (command == "fan on") {

          digitalWrite(fanLED, HIGH);
          Serial.println("Fan ON");
        }

        // Turn everything OFF
        else if (command == "all off") {

          digitalWrite(bathroomLED, LOW);
          digitalWrite(hallwayLED, LOW);
          digitalWrite(fanLED, LOW);

          Serial.println("All outputs OFF");
        }
      }
    }

    Serial.println("Disconnected");
  }
}