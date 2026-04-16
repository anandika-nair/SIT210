// Task 4.1P - Interrupts
// In this task I am using interrupts with a PIR sensor and a slider switch.
// The system turns ON the LEDs when motion is detected in dark conditions.
// The slider switch is used as a manual override to control the LEDs.

#include <Wire.h>        // I am using this for I2C communication
#include <BH1750.h>     // This library is for the light sensor

BH1750 lightMeter;      // I am creating an object to read light values

// LED pins
const int led1 = 6;     // LED 1 is connected to pin 6
const int led2 = 7;     // LED 2 is connected to pin 7

// sensor pins
const int pirPin = 2;       // PIR sensor output is connected to pin 2
const int switchPin = 3;    // slider switch is connected to pin 3

// threshold for darkness
float darkThreshold = 100.0;  // if value is below this, it will be considered dark

// interrupt flags
volatile bool motionDetected = false;   // I use this to check if motion happened
volatile bool switchChanged = false;    // I use this to check if switch changed

// manual mode
bool manualMode = false;  // this tells if system is in manual mode or not

// for serial monitor timing
unsigned long lastPrintTime = 0;          
const unsigned long printInterval = 1000; 

// PIR interrupt function
void pirISR()
{
  // when motion happens, I just set this flag
  motionDetected = true;
}

// switch interrupt function
void switchISR()
{
  // when switch changes, I set this flag
  switchChanged = true;
}

void setup()
{
  Serial.begin(9600);   // starts serial monitor
  delay(1500);          

  Wire.begin();         // starts I2C communication

  // starting BH1750 sensor
  if (lightMeter.begin())
  {
    Serial.println("BH1750 started properly");
  }
  else
  {
    Serial.println("BH1750 did not start properly");
  }

  // LED setup
  pinMode(led1, OUTPUT);   // setting LED pins as output
  pinMode(led2, OUTPUT);

  digitalWrite(led1, LOW); // initially I keep LEDs OFF
  digitalWrite(led2, LOW);

  // PIR and switch setup
  pinMode(pirPin, INPUT);            // PIR is input
  pinMode(switchPin, INPUT_PULLUP);  // switch uses pull-up (HIGH normally)

  // attach interrupts
  attachInterrupt(digitalPinToInterrupt(pirPin), pirISR, RISING);   // motion triggers interrupt
  attachInterrupt(digitalPinToInterrupt(switchPin), switchISR, CHANGE); // switch change triggers interrupt

  Serial.println("System started");
}

void loop()
{
  float lux = lightMeter.readLightLevel(); // I read current light value

  // print light reading regularly
  if (millis() - lastPrintTime >= printInterval)
  {
    lastPrintTime = millis();

    Serial.print("Current light level: ");
    Serial.println(lux);

    // I check if it is dark or bright
    if (lux < darkThreshold)
    {
      Serial.println("Condition: Dark");
    }
    else
    {
      Serial.println("Condition: Bright");
    }
  }

  // handle switch (manual override)
  if (switchChanged)
  {
    switchChanged = false;   // reset flag
    delay(100);              // small delay to avoid noise (debounce)

    // if switch is LOW, it means it is turned ON
    if (digitalRead(switchPin) == LOW)
    {
      manualMode = true;  // I turn ON manual mode
      digitalWrite(led1, HIGH); // I turn ON both LEDs
      digitalWrite(led2, HIGH);
      Serial.println("Slider switch used. Both LEDs turned ON manually.");
    }
    else
    {
      manualMode = false; // I turn OFF manual mode
      digitalWrite(led1, LOW);  // I turn OFF both LEDs
      digitalWrite(led2, LOW);
      Serial.println("Slider switch used. Both LEDs turned OFF manually.");
    }
  }

  // automatic control only when manual mode is OFF
  if (!manualMode)
  {
    if (motionDetected)
    {
      motionDetected = false; // reset flag

      Serial.print("Motion detected. Light level: ");
      Serial.println(lux);

      // I check light condition
      if (lux < darkThreshold)
      {
        // if dark, I turn ON LEDs
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        Serial.println("It is dark, so both LEDs turned ON.");
      }
      else
      {
        // if bright, I turn OFF LEDs
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        Serial.println("It is bright, so both LEDs turned OFF.");
      }
    }

    // extra check: if it becomes bright, I turn OFF LEDs immediately
    if (lux >= darkThreshold)
    {
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
    }
  }
  else
  {
    // if manual mode is ON, I ignore automatic system
    if (motionDetected)
    {
      motionDetected = false;
      Serial.println("Manual mode is ON, so switch controls LEDs.");
    }
  }
}