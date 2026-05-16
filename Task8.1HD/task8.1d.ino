#include <ArduinoBLE.h>
#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

const int bathroomLED = 2;
const int hallwayLED = 3;
const int fanLED = 4;

BLEService voiceService("19B10000-E8F2-537E-4F6C-D104768A1214");

BLEStringCharacteristic commandChar(
  "19B10001-E8F2-537E-4F6C-D104768A1214",
  BLEWrite,
  30
);

void setup() {
  Serial.begin(9600);

  pinMode(bathroomLED, OUTPUT);
  pinMode(hallwayLED, OUTPUT);
  pinMode(fanLED, OUTPUT);

  Wire.begin();
  lightMeter.begin();

  if (!BLE.begin()) {
    Serial.println("BLE failed");
    while (1);
  }

  BLE.setLocalName("VoiceLightSystem");
  BLE.setAdvertisedService(voiceService);
  voiceService.addCharacteristic(commandChar);
  BLE.addService(voiceService);
  BLE.advertise();

  Serial.println("Waiting for Raspberry Pi...");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.println("Connected");

    while (central.connected()) {
      if (commandChar.written()) {
        String command = commandChar.value();
        command.toLowerCase();

        float lux = lightMeter.readLightLevel();

        Serial.print("Received: ");
        Serial.println(command);

        if (command == "bathroom" && lux < 300) {
          digitalWrite(bathroomLED, HIGH);
        }

        else if (command == "hallway" && lux < 300) {
          digitalWrite(hallwayLED, HIGH);
        }

        else if (command == "fan") {
          digitalWrite(fanLED, HIGH);
        }

        else if (command == "all off") {
          digitalWrite(bathroomLED, LOW);
          digitalWrite(hallwayLED, LOW);
          digitalWrite(fanLED, LOW);
        }
      }
    }
  }
}
