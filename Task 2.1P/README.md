# SIT210 Task 2.1P – Environmental Sensor Monitor

## Overview
This project demonstrates an Internet of Things (IoT) system using the Arduino Nano 33 IoT. The system collects environmental data using sensors and sends the data to the ThingSpeak cloud platform for visualisation.

## Hardware Components
The following components were used in this project:
- Arduino Nano 33 IoT
- DHT11 Temperature and Humidity Sensor
- LDR (Light Dependent Resistor)
- 1kΩ Resistor
- Breadboard
- Jumper Wires

## System Description
The LDR sensor is connected to the Arduino’s analog pin to measure light intensity. The DHT11 sensor is connected to a digital pin to measure temperature and humidity. The Arduino reads these sensor values and processes the data.

The Arduino Nano 33 IoT connects to WiFi using the WiFiNINA library. After connecting to the internet, the device sends the sensor data to the ThingSpeak cloud platform using an HTTP request and the channel Write API key.

## Data Visualisation
The data collected from the sensors is uploaded to a ThingSpeak channel where it is displayed as graphs:
- Field 1: Light intensity
- Field 2: Temperature

The data is updated approximately every 30 seconds and can be monitored through the ThingSpeak dashboard.

## Conclusion
This project demonstrates how IoT devices can collect environmental data and transmit it to a cloud platform for remote monitoring and analysis.
