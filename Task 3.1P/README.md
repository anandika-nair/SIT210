# Task 3.1 Trigger/Notification System

## Overview
In this task, I built a simple system using Arduino Nano 33 IoT and a light sensor (BH1750) to detect sunlight. 

## How it works
- The light sensor reads the light intensity (lux value)
- Arduino sends the data to MQTT topic `light/data`
- Node-RED receives the data
- A switch node checks the condition
- A Telegram message is sent to the user

## Tools and Technologies
- Arduino Nano 33 IoT
- BH1750 Light Sensor
- MQTT (test.mosquitto.org)
- Node-RED
- Telegram Bot
