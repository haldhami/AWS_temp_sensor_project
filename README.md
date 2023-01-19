# AWS Temperature Sensor Project
A small project that combines reading thermistors from an Arduino to posting readings to a DynamoDB instance

## Why do this project?
I have a keen interest in working with sensor data and plan to start a more ambitious project in the future, but I wanted to show in this project that I am capable of setting up, reading, and working with sensor data in the cloud.

## Aim
The purpose of this project was to allow me to highlight and practice several of my skills, including: Python, sensors, Arduino, electronics, data handling, AWS, and security. This was done by setting up sensors on an Ardunio, learning how to get these readings onto a computer using Python, and uploading the data to a DynamoDB instance on AWS via an HTTP API endpoint secured by IAM authentication.

## How I achieved it
The kit used was an Elegoo Arduino Uno connected to a Raspberry Pi 4 via USB which would read the sensor data with pySerial. The thermistors were NTC thermistors (NJ28NA0103, see attached data sheet for more info), and the Steinhart-Hart equation was used to correlate the readings from the thermistor into temperatures. As the purpose of this project was not to obtain accurate readings, but instead to obtain ball-park readings which could be uploaded, the code used for the equation was not double checked, and may have errors.

Readings were taken every 300ms and averaged out over 200 readings, thus are reported approximately every minute. The two temperatures are then read via pySerial through the Python script, which are then formatted correctly into a JSON object and send along with the current time to the HTTP PUT endpoint hosted on AWS API Gateway. The PUT and DELETE endpoints have IAM authentication attached and require an authorised signature in order to execute, to prevent any malicious behaviour. If given the sender is authorised, API Gateway then calls the AWS Lambda function stored in index.mjs, which then sends the payload into the DynamoDB instance. 
