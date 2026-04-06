SIT210 Task 3.2C – MQTT Ultrasonic Gesture System
Overview

In this task, I designed an embedded system using an ultrasonic sensor and MQTT protocol to detect hand gestures and control LEDs. The system identifies two gestures: wave and pat, and performs actions accordingly.

Hardware Used
Arduino Nano 33 IoT
HC-SR04 Ultrasonic Sensor
2 LEDs
Resistors
Breadboard
Jumper wires
Software Used
Arduino IDE
WiFiNINA library
PubSubClient library
MQTT Broker: broker.emqx.io
System Explanation

The ultrasonic sensor is used to measure distance. Based on the distance, two gestures are detected:

Wave → quick hand movement
Pat → hand held close for a longer time

The Arduino connects to Wi-Fi and then to the MQTT broker. It publishes messages to topics based on the detected gesture:

ES/Wave → when a wave is detected
ES/Pat → when a pat is detected

The Arduino also subscribes to these topics:

When a message is received on ES/Wave, both LEDs turn ON
When a message is received on ES/Pat, both LEDs turn OFF
Circuit Connections
TRIG → D2
ECHO → D3
LED 1 → D5
LED 2 → D6
VCC → 3.3V
GND → GND

Each LED is connected with a resistor to ground.

How to Run
Upload the code to Arduino
Connect to Wi-Fi
Open Serial Monitor
Perform gestures:
Quick hand movement → LEDs ON
Hold hand close → LEDs OFF
Output

The Serial Monitor shows:

Distance values
MQTT messages published
Messages received from topics

The LEDs respond based on gestures:

Wave → ON
Pat → OFF
Conclusion

This task demonstrates how MQTT can be used for communication in embedded systems. It also shows how sensors can be used to detect gestures and control devices remotely.
