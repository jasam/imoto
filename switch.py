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

# IN buffer
toArduino = raw_input('Write to Serial buffer: ')

# Message header
header = toArduino[:2]

# Lock for exit loop
output = 'SOA'

# convert GMT - 5
jetLag = 60*60*5

# Sync time
def syncDateTime():
   unixTime =str(int(time.time() - jetLag));
   arduino.write("a2" + unixTime + '\n')
   print("sync time: " + unixTime);
   return;

# switch options (service contrate)
# Download data
if header == "a1":
  arduino.write(toArduino + '\n')
  file = open("datapump_imoto.txt", "w")
  while (output != 'EOA'):
    # Read each line of the serial output 
    output = arduino.readline()
    print(output)
    file.write(output)
  file.close()
  syncDateTime()

# Sync datetime  
elif header == "a2":
  syncDateTime()

# Get dateTime 
elif header == "a3":
  arduino.write(toArduino + '\n')
  while (output != 'EOA'):
    # Read each line of the serial output 
    output = arduino.readline()
    print(output)
  syncDateTime()

# Set computer name  
elif header == "a4": 
  arduino.write(toArduino + '\n')
  while (output != 'EOA'):
    # Read each line of the serial output 
    output = arduino.readline()
    print(output)
  syncDateTime()

# Get comnputer nane
elif header == "a5": 
  arduino.write(toArduino + '\n')
  while (output != 'EOA'):
    # Read each line of the serial output 
    output = arduino.readline()
    print(output)
  syncDateTime()

# Delete file
elif header == "a6": 
  arduino.write(toArduino + '\n')
  while (output != 'EOA'):
    # Read each line of the serial output 
    output = arduino.readline()
    print(output)
  syncDateTime()