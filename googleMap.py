import gmplot
import re
import serial
from serial import Serial
import serial.tools.list_ports

ports = serial.tools.list_ports.comports()

for port, desc, hwid in sorted(ports):
        print("{}: {} [{}]".format(port, desc, hwid))


ser = serial.Serial('COM1', baudrate = 9600, timeout=5)
j = 0
lat = []
longet= []


while 1:
	coordinate = ser.readline().decode('ascii')
	if(j%2 == 0):
		lat.append(float(coordinate))
	else:
		longet.append(float(coordinate))
	j = j + 1







'''i=0
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

'''
gmapOne = gmplot.GoogleMapPlotter(lat[0],longet[0], 20)
gmapOne.scatter(lat, longet, '#0000ff', size=0.5, marker=False)
gmapOne.plot(lat, longet, 'red', edge_width=2.5)
gmapOne.draw("map.html")
