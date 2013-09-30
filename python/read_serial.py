import serial
import time


# open serial port
ser = serial.Serial('/dev/ttyACM0',9600,timeout=2) 
ser.open()


while True:
    print('dev 0' + ser.read())     
    pass

ser.close()
