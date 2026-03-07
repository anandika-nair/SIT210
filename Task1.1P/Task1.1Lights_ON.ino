const int porchLed = 2;
const int hallwayLed = 3;

bool porchOn = false;
bool hallwayOn = false;

unsigned long porchStartTime = 0;
unsigned long hallwayStartTime = 0;

const unsigned long porchDuration = 30000;    // 30 seconds
const unsigned long hallwayDuration = 60000;  // 60 seconds

void setupPins() {
  pinMode(porchLed, OUTPUT);
  pinMode(hallwayLed, OUTPUT);

  digitalWrite(porchLed, LOW);
  digitalWrite(hallwayLed, LOW);
}

void startLights() {
  digitalWrite(porchLed, HIGH);
  digitalWrite(hallwayLed, HIGH);

  porchOn = true;
  hallwayOn = true;

  porchStartTime = millis();
  hallwayStartTime = millis();

  Serial.println("Lights turned ON.");
  Serial.println("Porch light: 30 seconds");
  Serial.println("Hallway light: 60 seconds");
}

void checkSerialInput() {
  if (Serial.available() > 0) {
    char input = Serial.read();

    if (input == '1') {
      startLights();
    }
  }
}

void updatePorchLight() {
  if (porchOn && millis() - porchStartTime >= porchDuration) {
    digitalWrite(porchLed, LOW);
    porchOn = false;
    Serial.println("Porch light turned OFF.");
  }
}

void updateHallwayLight() {
  if (hallwayOn && millis() - hallwayStartTime >= hallwayDuration) {
    digitalWrite(hallwayLed, LOW);
    hallwayOn = false;
    Serial.println("Hallway light turned OFF.");
  }
}

void setup() {
  Serial.begin(9600);
  setupPins();

  Serial.println("System ready.");
  Serial.println("Type 1 in Serial Monitor and press Enter to turn ON both lights.");
}

void loop() {
  checkSerialInput();
  updatePorchLight();
  updateHallwayLight();
}
