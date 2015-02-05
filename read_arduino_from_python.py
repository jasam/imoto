# Import pySerial
import serial
import time
from datetime import datetime

start = datetime.now()

# Port Name
# To find out the correct port type the line below into the terminal
# python -m serial.tools.list_ports
board = 'com10'

# Baud Rate
# Match baud rate with the rate used in the Arduino sketch and the Max patch
baud = 9600

# Define the connected port
arduino = serial.Serial(board, baud, timeout=1)

# Keep the data flowing with an infinite while loop
infinite = 1

toArduino = raw_input('Write to Serial buffer: ')
#print('Write to Serial buffer', toArduino)
arduino.write(toArduino + '\n')
output = 'IOF'
#File datapump
file = open("datapump_imoto.txt", "w")
while (output != 'EOF'):
  # Read each line of the serial output 
  output = arduino.readline()
  print(output)
  file.write(output)
file.close()
#lines = file("datapump_imoto.txt", "r").readlines() 
#del lines[-1]
print (datetime.now()-start)