# LightPong

LightPong is a real life game that allows you to play pingpong with light.

This repository contains all the software that allows you to build the yourself and some tools that could help with debugging and configuration. 

The files and folders in this repository have the following purposes: 
- `3d_print`: contains the files you need to 3D print the gimbal used in this project
- `game`: contains the lightpong game that should be flashed on an arduino
- `joystick`: contains a script that allows you to move the light on the gimal through commands it receives on the serial monitor (should be run with `joystick01`)
- `joystick01`: contains a Processing script that allows you to send commands to the gimal (should be run with `joystick`)
- `lightres`: contains a small script that prints lightresistor values to the serial monitor 
- `schematic`: contains a schematic that allows for a rebuild of the hardware

This project is licensed with the Creative Commons Attribution 4.0 International Public (CC BY 4.0) license. Please read `LICENSE.md` for more information. 