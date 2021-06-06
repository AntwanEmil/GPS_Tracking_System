import gmplot
import re

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
