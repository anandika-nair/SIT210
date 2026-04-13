# Task 5.2C – GUI Light Intensity Control

## Overview
In this task, I extended my previous GUI from Task 5.1 by adding a slider to control the brightness of a light. The idea was to not just turn the light ON and OFF, but also change its intensity using PWM.

## Components Used
- Raspberry Pi  
- LED  
- Resistor  
- Breadboard  
- Jumper wires  

## How it Works
The LED is connected to GPIO 18 because it supports PWM. Using PWM, I can control how bright the LED is by changing the duty cycle.

In the GUI, I used Tkinter to create a window with a slider and buttons. The slider allows me to change the brightness from 0 to 100. When I move the slider, the LED brightness changes accordingly.  

There are also ON and OFF buttons. The ON button sets the LED to full brightness, and the OFF button turns it off completely.

## Output
- Slider controls brightness smoothly  
- LED becomes dim or bright based on slider  
- ON button → full brightness  
- OFF button → light turns off  

## Conclusion
This task helped me understand how PWM works in a practical way. I also learned how to connect GUI with hardware using Python. Overall, it shows how we can control real devices using a simple interface.
