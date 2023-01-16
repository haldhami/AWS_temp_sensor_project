import time
import requests
import serial
import json

input_path = '/dev/tty.usbmodem1101' # Change to correct path on rpi

ser = serial.Serial(input_path)

try:
    while True:
        # Take the reading from the arduino - stops reading at \n
        reading = ser.read_until() # This line may need changed for 2 sensors
        # Decode reading as is initially 'bytes' object
        reading = round(float(reading.decode().strip()), 1)

        # Read current time and covert to unix time
        t = int(time.mktime(time.localtime()))
        print(f"The reading is: {reading} at time: {t}")

        # Create json object for posting data
        params = json.dumps(dict(   # add second temp to dict
            inside_temp=reading,
            time=t
        ))

        url = 'https://httpbin.org/put' # Change url to AWS api endpoint
        r = requests.put(url, data=params)
        # print(r.status_code)

except KeyboardInterrupt:
    ser.close()
    print("\nProgram has stopped.")
