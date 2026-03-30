# Task4.1Interrupts

## Overview
In this task, I created a system using Arduino Nano 33 IoT with a PIR motion sensor, BH1750 light sensor, a slider switch, and two LEDs.

The system turns ON the LEDs when motion is detected in dark conditions. I also used a slider switch as a manual override to control the LEDs.

## Components Used
- Arduino Nano 33 IoT
- PIR Motion Sensor
- BH1750 Light Sensor (GY-30)
- Slider Switch
- 2 LEDs
- Resistors
- Breadboard and jumper wires

## How it Works
The PIR sensor detects motion and the light sensor checks the light intensity.

- If motion is detected and it is dark (below 100 lux), the LEDs turn ON.
- If it is bright, the LEDs stay OFF.
- The slider switch is used to manually turn the LEDs ON or OFF.

Interrupts are used so the system responds immediately when motion or switch change happens.

## Files
- `Task4.1Interrupts.ino` – Arduino code for the system
- Circuit setup pictures

## Notes
This project helped me understand how to use interrupts and combine multiple sensors in one system.
