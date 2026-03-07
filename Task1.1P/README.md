# SIT210 Task 1.1P – Switching ON Lights

## Project Description
This project demonstrates a modular programming approach using the Arduino Nano 33 IoT. The system simulates an assisted living scenario where lights automatically turn on when triggered.

Two LEDs represent the porch light and the hallway light.

When the system is triggered, both LEDs turn on. The porch light stays on for 30 seconds and then turns off automatically. The hallway light stays on for 60 seconds before turning off.

## Hardware Components
- Arduino Nano 33 IoT
- Breadboard
- 2 LEDs
- 2 Resistors
- Jumper wires
- USB cable

## Pin Connections

Porch LED  
Arduino Pin D2 → LED → Resistor → GND

Hallway LED  
Arduino Pin D3 → LED → Resistor → GND

## How the System Works
The system waits for a trigger from the Serial Monitor. When the user types '1' and presses Enter, both LEDs turn on.

The Arduino records time using the millis() function.

The porch LED turns off after 30 seconds and the hallway LED turns off after 60 seconds.

## Modular Programming Approach
The program is divided into several functions that perform specific tasks.

setupPins() initializes the LED pins.

checkSerialInput() reads the user input.

startLights() activates both LEDs and starts the timers.

updatePorchLight() controls the porch LED timing.

updateHallwayLight() controls the hallway LED timing.

This modular structure makes the program easier to read, maintain, and debug.


## Trigger Method

The original task suggests using a push button or slide switch to activate the lights. However, the available kit did not contain these components. Therefore, the system was triggered using input from the Arduino Serial Monitor. When the user types '1' and presses Enter, both LEDs are activated and the timing sequence begins.
