# Movement camera
For a school assignment we had to demonstrate that we understood and could implement stateful concepts and could wrap our head around Arduino's.
To prove that I'm sufficient with this subjects I created a motionsensor that takes a picture in another part of the room then when where the motion is detected.

The motion sensor has a range for up to 7 meters but just as everbody else you will have a living room that is far longer then 7 meters ;) so that's why the different modules.

## What do you need?
For this project you will need the following components:

- Raspberry Pi model 3 or 4 with WiFi and Raspbian installed.
- Arduino Nano IoT 33
- Raspberry Pi NoIR Camera V2 or Camera Module V2
- PIR Motion sensor
- Solder
- Soldering iron
- 3 Male to Female cables
- 2 jumper cables
- BreadBoard
- Multimeter
- USB-C cable
- 5V power supply with usb connection

##  The start..
### Making 5V possible
To start the project we will start by soldering the jumper on the back side of the Arduino.
On the picture underneath you see in the yellow circle the 5V jumper. This is located at the back of the Arduino Nano IoT 33.

<img alt="Arduino 5v Jumper" src="https://git.fhict.nl/I424717/bewegingscamera/-/raw/master/images/Arduino-usb-jumper.jpeg" width="400" height="500" />

Place the solder on the two copper plates right next to VUSB. This will give you the following result:

<img alt="Arduino with solder" src="https://git.fhict.nl/I424717/bewegingscamera/-/raw/master/images/Arduino-with-solder-Jumper.jpeg" width="400" height="500" />

To test the solder we will have to attach the arduino to a breadboard and connect the Arduino to a 5v power supply. 
This can be done by plugging in your Arduino by USB to your computer.

See the picture below how to attach your Arduino to the breadboard:

<img alt="Test setup" src="https://git.fhict.nl/I424717/bewegingscamera/-/raw/master/images/Volt-Test.jpg" width="650" height="500" />

When everything is attached grab your multimeter en check if the right amounts of volts are comming thru.

## Setting up the Arduino
###  Connecting the PIR motion sensor

See the picture below on how to connect the PIR motionsensor to the Arduino.

<img alt="PIR motionsensor attached to Arduino" src="https://git.fhict.nl/I424717/bewegingscamera/-/raw/master/images/MotionSensor-Arduino.png" width="650" height="500" />

When everything is connected it's time to connect your Arduino with USB to you computer to upload. When your Arduino is connected upload to following sketch: [ArduinoBewegingsSensor.ino](ArduinoBewegingsSensor/ArduinoBewegingsSensor.ino) to your Arduino and replace the WiFi SSID, IP Adress and WIFI password to your liking. Also in the MQTT setup the topics to your liking.

## Setting up the Rapsberry PI

To setup the Raspberry Pi you first need to connect the camera to the Raspberry Pi. This can be done by connecting the camera cable to the Raspberry Pi Camera port, the blue side of the cable has to point to the usb ports of the Raspberry Pi.






