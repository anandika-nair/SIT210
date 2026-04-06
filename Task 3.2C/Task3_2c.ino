// SIT210 Task 3.2C MQTT
//In this code I am using ultrasonic sensor to detect wave and pat.
//If wave is detected, it publishes to ES/Wave.
//If pat is detected, it publishes to ES/Pat.
//The board also subscribes to both topics and controls 2 LEDs.

// libraries included
#include <WiFiNINA.h> 
#include <PubSubClient.h>

// my wifi details
char ssid[] = "Optus_256F68";
char pass[] = "essay34996tw";

// the MQTT details
const char* mqttServer = "broker.emqx.io";
const int mqttPort = 1883;

const char* topicWave = "ES/Wave";
const char* topicPat  = "ES/Pat";

//pin definitions
const int trigPin = 2;
const int echoPin = 3;
const int led1Pin = 5;
const int led2Pin = 6;

//creating objects
WiFiClient wifiClient;
PubSubClient client(wifiClient);

//introducing variables
float distanceCm = 0.0;

bool objectWasClose = false;
unsigned long closeStartTime = 0;

bool waveSent = false;
bool patSent = false;

const float closeThreshold = 12.0;   // hand is close
const float farThreshold = 20.0;     // hand moved away

// connecting to the WiFi
void connectWiFi()
{
  Serial.print("Connecting to WiFi");

  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    Serial.print(".");
    delay(2000);
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// when MQTT message is received
void callback(char* topic, byte* payload, unsigned int length)
{
  String message = "";

  for (unsigned int i = 0; i < length; i++)
  {
    message += (char)payload[i];
  }

  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(message);

  if (String(topic) == "ES/Wave")
  {
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, HIGH);
    Serial.println("Both LEDs are ON");
  }
  else if (String(topic) == "ES/Pat")
  {
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    Serial.println("Both LEDs are OFF");
  }
}

// reconnect MQTT if disconnected
void reconnectMQTT()
{
  while (!client.connected())
  {
    Serial.print("Connecting to MQTT...");

    String clientId = "Nano33IoTClient-";
    clientId += String(random(1000, 9999));

    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      client.subscribe(topicWave);
      client.subscribe(topicPat);
      Serial.println("Subscribed to ES/Wave and ES/Pat");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again after 2 seconds");
      delay(2000);
    }
  }
}

// measures the distance from ultrasonic sensor
float getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0)
  {
    return 999.0;
  }

  float distance = duration * 0.0343 / 2.0;
  return distance;
}

// publish wave message
void publishWave()
{
  String msg = "Detected a WAVE";
  client.publish(topicWave, msg.c_str());
  Serial.println("Published to ES/Wave");
  Serial.println(msg);
}

// publish pat message
void publishPat()
{
  String msg = "Detected a PAT";
  client.publish(topicPat, msg.c_str());
  Serial.println("Published to ES/Pat");
  Serial.println(msg);
}


// setup
void setup()
{
  Serial.begin(9600);
  delay(1500);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);

  connectWiFi();

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  randomSeed(analogRead(A0));
}

// loop
void loop()
{
  if (!client.connected())
  {
    reconnectMQTT();
  }

  client.loop();

  distanceCm = getDistance();

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  unsigned long now = millis();

  // hand comes close
  if (distanceCm < closeThreshold)
  {
    if (!objectWasClose)
    {
      objectWasClose = true;
      closeStartTime = now;
      waveSent = false;
      patSent = false;
    }

    // pat = hand stays close for at least 1 second
    if (!patSent && (now - closeStartTime >= 1000))
    {
      publishPat();
      patSent = true;
      waveSent = true;
    }
  }
  // hand moved away
  else if (distanceCm > farThreshold)
  {
    if (objectWasClose)
    {
      unsigned long closeDuration = now - closeStartTime;

      // wave = hand was close only for short time
      if (!waveSent && !patSent && closeDuration < 700)
      {
        publishWave();
        waveSent = true;
      }

      objectWasClose = false;
    }
  }

  delay(100);
}