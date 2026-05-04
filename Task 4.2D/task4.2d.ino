#include <WiFiNINA.h>
#include <PubSubClient.h>

// WiFi details
char ssid[] = "Optus_256F68";
char pass[] = "essay34996tw";

// MQTT broker details
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;

// Topic used by both the web page and Arduino
const char* lightTopic = "sit210/anandika/lights/control";

// LED pins
int livingLED = 2;
int bathroomLED = 3;
int closetLED = 4;

// Variables to remember whether each light is ON or OFF
bool livingState = false;
bool bathroomState = false;
bool closetState = false;

// Create WiFi and MQTT client objects
WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() 
{
  Serial.begin(9600);

  // Set LED pins as outputs
  pinMode(livingLED, OUTPUT);
  pinMode(bathroomLED, OUTPUT);
  pinMode(closetLED, OUTPUT);

  // Start with all lights OFF
  digitalWrite(livingLED, LOW);
  digitalWrite(bathroomLED, LOW);
  digitalWrite(closetLED, LOW);

  connectToWiFi();

  // Set MQTT broker and message receiving function
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  connectToMQTT();
}

void loop() 
{
  // Reconnect if MQTT disconnects
  if (!client.connected()) 
  {
    connectToMQTT();
  }

  // Keep checking for MQTT messages
  client.loop();
}

void connectToWiFi() 
{
  Serial.print("Connecting to WiFi");

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(2000);
  }

  Serial.println();
  Serial.println("WiFi connected");
}

void connectToMQTT() 
{
  while (!client.connected()) 
  {
    Serial.print("Connecting to MQTT... ");

    // Random client ID helps avoid duplicate MQTT client names
    String clientId = "Nano33IoTClient_";
    clientId += String(random(1000, 9999));

    if (client.connect(clientId.c_str())) 
    {
      Serial.println("connected");

      // Arduino listens to this topic for light commands
      client.subscribe(lightTopic);
      Serial.print("Subscribed to topic: ");
      Serial.println(lightTopic);
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  String roomName = "";

  // Convert MQTT message into a normal string
  for (int i = 0; i < length; i++) 
  {
    roomName += (char)payload[i];
  }

  Serial.print("Message received: ");
  Serial.println(roomName);

  // Send the room name to the function that controls LEDs
  toggleRoom(roomName);
}

void toggleRoom(String roomName) 
{
  if (roomName == "living room") 
  {
    livingState = !livingState;
    digitalWrite(livingLED, livingState);
    Serial.println("Living room light toggled");
  } 
  else if (roomName == "bathroom") 
  {
    bathroomState = !bathroomState;
    digitalWrite(bathroomLED, bathroomState);
    Serial.println("Bathroom light toggled");
  } 
  else if (roomName == "closet") 
  {
    closetState = !closetState;
    digitalWrite(closetLED, closetState);
    Serial.println("Closet light toggled");
  } 
  else 
  {
    Serial.println("Unknown room name");
  }
}
