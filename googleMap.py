import gmplot
import re
import serial
from serial import Serial
import serial.tools.list_ports

ports = serial.tools.list_ports.comports()

for port, desc, hwid in sorted(ports):
        print("{}: {} [{}]".format(port, desc, hwid))


ser = serial.Serial('COM5', baudrate = 9600, timeout=5)
j = 0
lat = []
longet= []









"""
i=0
lat_string = ""
long_string = ""
combination = ""
with open('map_out.txt') as f:

		combination = f.split()


		lat.append(lat_string)
		long.append(long_string)
		lat[i] = float(lat[i])
		long[i] = float(long[i])
		i=i+1

"""

file_in= open('map_out','r').readline()
points=file_in.split(' ')
print(points)
i = 0

for point in points:
	if (point != ''):
		lat.append(   float(point.split("&")[0][0:2]   )+float(point.split("&")[0][2:])/60 )
		print(float(point.split("&")[0]))
		print(float(point.split("&")[1]   ))
		longet.append(   float(point.split("&")[1][0:3]   )+float(point.split("&")[1][3:])/60 )


print(lat)
print(longet)

gmapOne = gmplot.GoogleMapPlotter(lat[0],longet[0], 20)
gmapOne.scatter(lat, longet, '#0000ff', size=0.5, marker=False)
gmapOne.plot(lat, longet, 'red', edge_width=2.5)
gmapOne.draw("map.html")


30+02.59201/60