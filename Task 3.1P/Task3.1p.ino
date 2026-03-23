#include <Wire.h>
#include <BH1750.h>
#include <WiFiNINA.h>
#include <PubSubClient.h>

// Here my wifi details are added 
const char* ssid = "Optus_256F68";
const char* password = "essay34996tw";

// MQTT broker (public broker)
const char* mqtt_server = "test.mosquitto.org";

// creating objects
WiFiClient wifiClient;
PubSubClient client(wifiClient);
BH1750 lightMeter;

void setup() {
  Serial.begin(9600);

  // he the light sensor starts
  Wire.begin();
  lightMeter.begin();

  // connecting to my wifi
  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    delay(1000);
  }
  Serial.println("WiFi connected!");

  // setting MQTT server
  client.setServer(mqtt_server, 1883);
}

void loop() {

  // this will help to reconnect MQTT if disconnected
  if (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    client.connect("ArduinoClient");
    delay(1000);
  }

  client.loop();

  // reads the light value from sensor
  float lux = lightMeter.readLightLevel();

  // prints the value to check
  Serial.print("Light value: ");
  Serial.println(lux);

  // converts float to string
  char msg[50];
  String data = String(lux);
  data.toCharArray(msg, 50);

  // sends data to MQTT topic
  client.publish("light/data", msg);

  delay(2000);
}