import time
import serial
from random import randint

ser = serial.Serial('/dev/ttyACM0',
                    baudrate=9600,
                    parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE,
                    bytesize=serial.EIGHTBITS,
                    timeout=1)

#pipe testing
def generate_random_update():
    data_type = randint(1,6)
    data_val = 0
    if data_type == 1: #speed
        data_val = randint(50,59)
    elif data_type == 2: #range
        data_val = randint(40,49)
    elif data_type == 3: #battery
        data_val = randint(0,99)
    elif data_type == 4: #temp
        data_val = randint(60,69)
    elif data_type == 5: #current
        data_val = randint(60,69)
    elif data_type == 6: #power
        data_val = randint(60,69)
    return (data_type,data_val)

while 1:

    x = ser.readline()
    print(x)
