import time
import requests
import serial
import json
import os
from requests_auth_aws_sigv4 import AWSSigV4
from dotenv import load_dotenv

load_dotenv()

AWS_ACCESS_KEY = os.getenv('AWS_ACCESS_KEY')
AWS_SECRET_KEY = os.getenv('AWS_SECRET_KEY')

input_path = '/dev/tty.usbmodem1101' # Change to correct path on rpi
ser = serial.Serial(input_path)


# url = 'https://httpbin.org/post' # Change url to AWS api endpoint
url = 'https://1rf9nmj62a.execute-api.us-east-1.amazonaws.com/items'
header = {'Content-Type':'application/json'}
aws_auth = AWSSigV4(
    'execute-api',
    aws_access_key_id=AWS_ACCESS_KEY
    aws_secret_access_key=AWS_SECRET_KEY
    region='us-east-1'
)

try:
    while True:
        # Take the reading from the arduino - stops reading at \n
        reading = ser.read_until() # This line may need changed for 2 sensors
        # Decode reading as is initially 'bytes' object thus needs decoded
        # reading = round(float(reading.decode().strip()), 1)
        reading = reading.decode().split(',')
        t_in, t_out = reading[0], reading[1]
        t_in = round(float(t_in), 1)
        t_out = round(float(t_out.strip()), 1)

        # Read current time and convert to epoch time
        t = int(time.mktime(time.localtime()))

        # Create json object for posting data
        payload = json.dumps(dict(
            time = t,
            temp_in=t_in,
            temp_out=t_out
        ))

        r = requests.post(url, headers=header, data=payload, auth=aws_auth)

except KeyboardInterrupt:
    ser.close()
    print("\nProgram has stopped.")
