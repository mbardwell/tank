# ESP8266 (NodeMCU) tank control

This code is the first step of my 3D printed tank control project. I have already bricked a Feather Huzzah, so this is round 2.

## Dependencies
- Blynk library v0.5.3 by V. Shymanskyy
- passwords.h file in ../lib/foldername/passwords.h which should include _SSID, _PASS and _AUTHTOKEN values

Install using PlatformIO Library Manager

## Getting Started
- Joystick feature sends two analog values for one coordinated movement
- Button feature stalls tank when off
- Slider feature provides a speed maximum

## Software development strategy
- Get stall button working
- Receive an analog movement value and hold it between sample periods
- Map joystick values to PWM values based on speed outputs
- Add more control with slider speed capping
