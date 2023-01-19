# AWS Temperature Sensor Project
A small project that combines reading thermistors from an Arduino to posting readings to a DynamoDB instance

## Why do this project?
I have a keen interest in working with sensor data and plan to start a more ambitious project in the future, but I wanted to show in this project that I am capable of setting up, reading, and working with sensor data in the cloud.

## Aim
The purpose of this project was to allow me to highlight and practice several of my skills, including: Python, sensors, Arduino, electronics, data handling, AWS, and security. This was done by setting up sensors on an Ardunio, learning how to get these readings onto a computer using Python, and uploading the data to a DynamoDB instance on AWS via an HTTP API endpoint secured by IAM authentication.

## Electronics Setup

<img width="513" alt="Screenshot 2023-01-19 at 14 21 17" src="https://user-images.githubusercontent.com/66445070/213466603-dca4c95d-a0c0-4ac4-b3dd-667aa606d013.png">

The setup used was similar to the above, with the differences being that the thermistors were plugged into A0 and A1. 

## How I achieved it
I have two thermistors connected to an Arduino, as described in *insert file name*, where one thermistor is on the electronic breadboard inside my flat, and the other is outside via a window. The kit used was an Elegoo Arduino Uno connected to a Raspberry Pi 4 via USB which would read the sensor data with pySerial. The thermistors were NTC thermistors (NJ28NA0103, see attached data sheet for more info), and the Steinhart-Hart equation was used to correlate the readings from the thermistor into temperatures. 

Readings were taken every 300ms and averaged out over 200 readings, thus are reported approximately every minute. The two temperatures are then read via pySerial through the Python script, which are then formatted correctly into a JSON object and send along with the current time to the HTTP PUT endpoint hosted on AWS API Gateway. The PUT and DELETE endpoints have IAM authentication attached and require an authorised signature in order to execute, to prevent any malicious behaviour. If given the sender is authorised, API Gateway then calls the AWS Lambda function stored in index.mjs, which then sends the payload into the DynamoDB instance. 

## Brief Discussion of Readings
The values obtained from the thermistors, in particular the outside thermistor, may be inaccurate for a few reasons. 
- The code used for the Steinhart-Hart equation wasn't double-checked, and followed a methodology that perhaps could have been made more accurate with the aid of the thermistor spec sheet.
- The outside thermistor is < 5cm outside of the window. Being an old flat, the windows are not well insulated and this may contribute to the thermistor being located in a thermodynamic boundary layer betweeen the temperature inside the flat and the outside bulk temperature, which would not be representative of the outside bulk temperature that I am trying to read.
- To protect the thermistor from any possible issues with rain, I've covered the exposed wires of the thermistor, as well as the thermistor itself, in plastic cling-film, which may have a small insulating effect, also contributing to higher-than-expected readings.

As the purpose of this project was not to obtain accurate readings, but instead to obtain ball-park readings which could be uploaded, these issues were noted but not rectified.
