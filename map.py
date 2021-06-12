import gmplot
import re
import serial
from serial import Serial
import serial.tools.list_ports

print("1")
ports = serial.tools.list_ports.comports()

for port, desc, hwid in sorted(ports):
        print("{}: {} [{}]".format(port, desc, hwid))

print("2")
ser = serial.Serial('COM5', baudrate = 9600, timeout=5)
while 1:

	coordinate = ser.readline().decode('ascii')
	print(coordinate)



lat = []
long= []
i=0
lat_string = ""
long_string = ""
with open('array.txt') as f:
	for line in f:
		lat_string,long_string = line.split()
		lat.append(lat_string)
		long.append(long_string)
		lat[i] = float(lat[i])
		long[i] = float(long[i])
		i=i+1


gmapOne = gmplot.GoogleMapPlotter(lat[0],long[0], 20)
gmapOne.scatter(lat, long, '#0000ff', size=0.5, marker=False)
gmapOne.plot(lat, long, 'red', edge_width=2.5)
gmapOne.draw("map.html")
