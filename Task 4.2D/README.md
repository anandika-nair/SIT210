# Task 4.2D – LED Control using Arduino Nano 33 IoT

## Overview

In this task, I developed a simple smart lighting system using Arduino Nano 33 IoT. The system allows three LEDs to be controlled separately using a web-based interface. Each LED represents a room: living room, bathroom, and closet.

## Hardware Components

* Arduino Nano 33 IoT
* Breadboard
* 3 LEDs
* 3 Resistors
* Jumper wires

## Circuit Setup

* Living Room LED → Pin D2
* Bathroom LED → Pin D3
* Closet LED → Pin D4

Each LED is connected through a resistor to ground. A common ground rail is used on the breadboard.

## Software Implementation

The Arduino connects to WiFi using the WiFiNINA library and runs a simple web server.

A function called `toggleRoom(String roomName)` is used to control the LEDs. It takes a string input:

* "living room"
* "bathroom"
* "closet"

Based on the input, it toggles the corresponding LED ON or OFF.

## Web Interface

The Arduino hosts a simple HTML page with three buttons:

* Living Room
* Bathroom
* Closet

When a button is clicked, a request is sent to the Arduino, and the corresponding LED is toggled.

## How It Works

1. User opens the Arduino IP address in a browser
2. The HTML page is displayed
3. User clicks a button
4. Arduino receives the request
5. The `toggleRoom` function is called
6. The selected LED is toggled

## Output

All three LEDs can be controlled independently through the web interface. The system works in real time using WiFi communication.

## Files Included

* Arduino code (.ino file)
* README.md
* Circuit images

## Notes

This project demonstrates basic IoT concepts including:

* WiFi communication
* Web server on Arduino
* Interaction between frontend (HTML) and hardware
