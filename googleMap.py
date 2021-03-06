import gmplot
import re
import serial
from serial import Serial
import serial.tools.list_ports

ports = serial.tools.list_ports.comports()

for port, desc, hwid in sorted(ports):
        print("{}: {} [{}]".format(port, desc, hwid))

f = open("map_out.txt", "w")

ser = serial.Serial('COM5', baudrate = 9600, timeout=5)
#while 1: 
while 1: 
	coordinate = ser.readline().decode('ascii')
	if coordinate[-4:]!="0000":
		print(coordinate)
		f.write(coordinate)
		f.write(" ")
	else:
		break
f.close()







j = 0
lat = []
longet= []

lat_value = 0.0
longet_value = 0.0
file_in= open('map_out.txt','r').readline()
points=file_in.split(' ')
print(points)
i = 0

for point in points:
	if (point != ''):
		lat_value = float(point.split("&")[0][0:2]) + float(point.split("&")[0][2:])/60
		longet_value = float(point.split("&")[1][0:3] )+float(point.split("&")[1][3:])/60
		if (lat_value > 22 and lat_value < 32 and longet_value > 25 and longet_value < 34):	##added max & min lat/longet of EGYPT because some error redings from gps
			lat.append(  lat_value )
			print(float(point.split("&")[0]))
			print(float(point.split("&")[1]))
			longet.append(longet_value)


print(lat)
print(longet)

gmapOne = gmplot.GoogleMapPlotter(lat[0],longet[0], 20)
gmapOne.scatter(lat, longet, '#0000ff', size=0.5, marker=False)
gmapOne.plot(lat, longet, 'red', edge_width=2.5)
gmapOne.draw("map.html")


