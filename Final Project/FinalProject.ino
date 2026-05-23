#include <Arduino_LSM6DS3.h>   // for using built-in accelerometer and gyroscope
#include <WiFiNINA.h>          // for connecting Arduino to WiFi
#include <PubSubClient.h>      // for MQTT communication
#include <math.h>              // for square root calculations

// WiFi details
char ssid[] = "add_your_wifi_name";
char pass[] = "add_your_wifi_password";

// MQTT broker details
const char* mqttServer = "add_your_broker";
const int mqttPort = 1883;

// topic where emergency messages will be sent
const char* topic = "add_your_topic";

// hardware pin connections
const int buzzerPin = 2;          // buzzer connected to D2
const int resetSwitchPin = 3;     // slider switch connected to D3

// fall detection thresholds
const float impactThreshold = 2.5;        // sudden strong movement
const float stillThresholdLow = 0.8;      // lower range for still position
const float stillThresholdHigh = 1.2;     // upper range for still position

bool fallDetected = false;   // this checks if fall already happened

WiFiClient wifiClient;
PubSubClient client(wifiClient);

// function to connect Arduino to WiFi
void connectWiFi() {
  Serial.print("Connecting to WiFi");

  // keep trying until WiFi connects
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(3000);
  }

  Serial.println();
  Serial.println("WiFi connected");
}

// function to connect to MQTT broker
void connectMQTT() {
  Serial.print("Connecting to MQTT");

  // keep trying until MQTT connects
  while (!client.connected()) {
    if (client.connect("add_your_device_name")) {
      Serial.println();
      Serial.println("MQTT connected");
    } else {
      Serial.print(".");
      delay(3000);
    }
  }
}

// function to send MQTT message
void publishStatus(const char* message) {

  // reconnect if connection drops
  if (!client.connected()) {
    connectMQTT();
  }

  // publish emergency message
  client.publish(topic, message);

  Serial.print("MQTT message sent: ");
  Serial.println(message);
}

void setup() {

  // start serial monitor
  Serial.begin(9600);
  delay(2000);

  // set buzzer as output
  pinMode(buzzerPin, OUTPUT);

  // switch uses internal pullup resistor
  pinMode(resetSwitchPin, INPUT_PULLUP);

  // make sure buzzer starts OFF
  noTone(buzzerPin);

  // check if IMU sensor is working
  if (!IMU.begin()) {
    Serial.println("IMU not detected!");
    while (1);
  }

  // connect WiFi
  connectWiFi();

  // set MQTT server details
  client.setServer(mqttServer, mqttPort);

  // connect MQTT
  connectMQTT();

  // send initial safe status
  publishStatus("SAFE");

  Serial.println("Smart Wearable Fall Detection System Started");
}

void loop() {

  // keeps MQTT communication alive
  client.loop();

  // if switch is pressed, reset emergency
  if (digitalRead(resetSwitchPin) == LOW) {

    // reset fall state
    fallDetected = false;

    // stop buzzer
    noTone(buzzerPin);

    Serial.println("System reset. Patient status: SAFE");

    // tell caregiver patient is safe again
    publishStatus("SAFE");

    delay(500);

    // wait until switch released
    while (digitalRead(resetSwitchPin) == LOW) {
      client.loop();
      delay(100);
    }
  }

  // if fall already detected, keep buzzer ON
  if (fallDetected == true) {
    tone(buzzerPin, 1000);
    return;
  }

  float x, y, z;

  // check if acceleration data is available
  if (IMU.accelerationAvailable()) {

    // read movement values
    IMU.readAcceleration(x, y, z);

    // calculate total movement force
    float totalAcceleration = sqrt((x * x) + (y * y) + (z * z));

    Serial.print("Total Acceleration: ");
    Serial.println(totalAcceleration);

    // if sudden strong movement happens
    if (totalAcceleration > impactThreshold) {

      Serial.println("Impact detected. Checking if patient is still...");

      // wait 2 seconds to confirm
      delay(2000);

      if (IMU.accelerationAvailable()) {

        IMU.readAcceleration(x, y, z);

        // check movement after impact
        float afterImpactAcceleration = sqrt((x * x) + (y * y) + (z * z));

        Serial.print("After impact acceleration: ");
        Serial.println(afterImpactAcceleration);

        // if person is mostly still, confirm fall
        if (afterImpactAcceleration > stillThresholdLow &&
            afterImpactAcceleration < stillThresholdHigh) {

          fallDetected = true;

          // turn buzzer ON
          tone(buzzerPin, 1000);

          Serial.println("FALL DETECTED! Buzzer ON until reset switch is used.");

          // send emergency alert
          publishStatus("FALL_DETECTED");

        } else {

          // normal movement, not a fall
          Serial.println("Movement continued. Fall not confirmed.");
        }
      }
    }
  }

  // small delay to make readings stable
  delay(300);
}