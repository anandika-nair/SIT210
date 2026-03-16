#include <WiFiNINA.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

char ssid[] = "Optus_256F68";
char pass[] = "essay34996tw";

String apiKey = "BXG2MKZ7VROV61I9";

WiFiClient client;
DHT dht(DHTPIN, DHTTYPE);

int lightPin = A0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  dht.begin();

  Serial.println("Starting...");
  Serial.print("Connecting to WiFi");

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    delay(2000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected to WiFi");
}

void loop() {
  int lightValue = analogRead(lightPin);
  float temperature = dht.readTemperature();

  Serial.print("Light: ");
  Serial.print(lightValue);
  Serial.print(" | Temp: ");
  Serial.println(temperature);

  if (client.connect("api.thingspeak.com", 80)) {
    String data = "GET /update?api_key=" + apiKey;
    data += "&field1=" + String(lightValue);
    data += "&field2=" + String(temperature);

    client.print(data);
    client.print(" HTTP/1.1\r\n");
    client.print("Host: api.thingspeak.com\r\n");
    client.print("Connection: close\r\n\r\n");

    Serial.println("Data sent to ThingSpeak");
  } else {
    Serial.println("ThingSpeak connection failed");
  }

  delay(30000);
}