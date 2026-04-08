#include <WiFiNINA.h>   // this library is used to connect Arduino to WiFi

// WiFi details (my home network)
char ssid[] = "Optus_256F68";
char pass[] = "essay34996tw";

// creating a web server on port 80 (standard HTTP port)
WiFiServer server(80);

// assigning pins for each room LED
int livingRoomPin = 2;   // LED for living room
int bathroomPin = 3;     // LED for bathroom
int closetPin = 4;       // LED for closet

// this function takes room name as input and toggles that LED
void toggleRoom(String roomName) {

  roomName.toLowerCase();  // converting to lowercase to avoid mismatch

  // checking which room is requested and toggling that LED
  if (roomName == "living room") {
    digitalWrite(livingRoomPin, !digitalRead(livingRoomPin));  
    // this flips the current state (ON becomes OFF, OFF becomes ON)
  }
  else if (roomName == "bathroom") {
    digitalWrite(bathroomPin, !digitalRead(bathroomPin));
  }
  else if (roomName == "closet") {
    digitalWrite(closetPin, !digitalRead(closetPin));
  }
}

void setup() {

  Serial.begin(9600);   // starting serial monitor for debugging

  // setting all LED pins as output
  pinMode(livingRoomPin, OUTPUT);
  pinMode(bathroomPin, OUTPUT);
  pinMode(closetPin, OUTPUT);

  // connecting to WiFi
  WiFi.begin(ssid, pass);

  // keep trying until WiFi connects
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // once connected, print confirmation and IP address
  Serial.println("Connected!");
  Serial.println(WiFi.localIP());  
  // this IP is used in browser to open the web page

  server.begin();  // starting the web server
}

void loop() {

  // checking if any client (browser) is trying to connect
  WiFiClient client = server.available();

  if (client) {

    // reading the request sent by browser
    String request = client.readStringUntil('\r');
    Serial.println(request);   // printing request for understanding

    // checking which button was pressed based on URL
    if (request.indexOf("/living") != -1) {
      toggleRoom("living room");   // calling function with string
    }
    else if (request.indexOf("/bathroom") != -1) {
      toggleRoom("bathroom");
    }
    else if (request.indexOf("/closet") != -1) {
      toggleRoom("closet");
    }

    // sending response back to browser (this is the HTML page)
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");

    // this part creates the simple web interface with buttons
    client.println("<h2>LED Control</h2>");
    client.println("<button onclick=\"location.href='/living'\">Living Room</button><br><br>");
    client.println("<button onclick=\"location.href='/bathroom'\">Bathroom</button><br><br>");
    client.println("<button onclick=\"location.href='/closet'\">Closet</button>");

    delay(1);        // small delay for stability
    client.stop();   // closing connection after response
  }
}