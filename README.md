# AWS Temperature Sensor Project
A small project that combines reading thermistors from an Arduino to posting readings to a DynamoDB instance

## Why do this project?
I have a keen interest in working with sensor data and plan to start a more ambitious project in the future, but I wanted to show in this project that I am capable of setting up, reading, and working with sensor data in the cloud.

## Aim
The purpose of this project was to allow me to highlight and practice several of my skills, including: Python, sensors, Arduino, electronics, data handling, AWS, and security. This was done by setting up sensors on an Ardunio, learning how to get these readings onto a computer using Python, and uploading the data to a DynamoDB instance on AWS via an HTTP API endpoint secured by IAM authentication.

## How I achieved it
The kit used was an Arduino Uno connected to a Raspberry Pi via USB which would read the sensor data with pySerial. The script then uses a http POST request to upload the sensor data to DynamoDB.
