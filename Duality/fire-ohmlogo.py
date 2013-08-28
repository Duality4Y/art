#!/usr/bin/python
#import pygame
import random
import math
import time
import socket

UDP_IP = "10.42.0.48"
UDP_PORT = 6454
def buildPacket(universe, pixels):
	size = len(pixels) * 3
	#              01234567   8   9   a   b   c   d   e   f   10  11  
	#                         op-code protver seq phy universe len  
	data = bytearray("Art-Net\x00\x00\x50\x00\x0e\x00\x00")
	data += chr(int(universe % 256))
	data += chr(int(universe / 256))
	data += chr(int(size / 256))
	data += chr(int(size % 256))
	for (r, g, b) in pixels:
		data += chr(r)
		data += chr(g)
		data += chr(b)
	return data

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP


letters = [
	{'name': 'O', 'x': 0, 'y': 0, 'universe': 1551, 'pixels': [(0,2), (0,3), (0,4), (0,5), (0,6), (0,7), (0,8), (0,9), (1, 10), (2, 10), (3, 10), (4, 9), (4, 8), (4, 7), (4, 6), (4, 5), (4, 4), (4, 3), (4, 2), (4, 2), (4, 1), (3, 0), (2, 0), (2, 0), (1, 0), (0, 1), (1,2), (1,2), (1, 3), (1, 4), (1, 5), (1, 6), (1, 7), (1,8), (1, 9), (2, 9), (3, 9), (3, 8), (3, 7), (3, 6), (3, 5), (3,4), (3, 3), (3,2), (3,2), (2,1), (2,1)]},
	{'name': 'H', 'x': 5, 'y': 0, 'universe': 1552, 'pixels': [(0,2), (0,3), (0,4), (0,5), (0,6), (0,7), (0,8), (0,9), (0,10), (1, 10), (1,9), (1,8), (1,7), (1,6), (2,6), (3,6), (3,7), (3,8), (3,9), (3,10), (4,10), (4,9), (4,8), (4,7), (4,6), (4,5), (4,3), (4,2), (4,1), (4,0), (3,0), (3,1), (3,2), (3,3), (3,4), (2,4), (1,4), (1,3), (1,2), (1,1), (1,0), (0,0), (0,0), (0,1)]},
	{'name': 'M', 'x': 10, 'y': 0, 'universe': 1553, 'pixels': [(0,2), (0,3), (0,4), (0,5), (0,7), (0,8), (0,9), (0,10), (1,10), (1,9), (1,8), (2,7), (2,6), (3,7), (4,8), (4,9), (4,10), (5,10), (5,9), (5,8), (5,7), (5,6), (5,4), (5,3), (5,2), (5,1), (5,0), (4,0), (4,1), (4,2), (4,3), (4,4), (4,6), (3,4), (3,3), (3,2), (2,2), (2,3), (2,4), (1,6), (1,5), (1,4), (1,3), (1,2), (1,1), (1,0), (0,0), (0,1)]},
	{'name': '2', 'x': 16, 'y': 0, 'universe': 1554, 'pixels': [(0,2), (1,3), (2,4), (3,5), (4,6), (4,7), (4,8), (4,9), (3,9), (2,9), (1,9), (1,8), (1,7), (1,6), (0,7), (0,8), (0,9), (0,10), (1,10), (2,10), (3,10), (5,10), (5,9), (5,8), (5,7), (4,6), (4,5), (3,4), (2,3), (1,2), (1,1), (2,1), (3,1), (4,1), (5,1), (5,0), (4,0), (3,0), (2,0), (0,1)]},
	{'name': '0', 'x': 22, 'y': 0, 'universe': 1555, 'pixels': [(0,2), (0,3), (0,4), (0,6), (0,7), (1,7), (2,6), (3,5), (3,4), (4,3), (4,2), (4,1), (3,1), (2,1), (1,1), (1,2), (1,3), (1,4), (1,6), (1,7), (1,8), (1,9), (2, 9), (3,9), (4,9), (4,8), (4,7), (4,6), (4,5), (4,4), (4,3), (3,4), (3,5), (2,6), (2,7), (0,8), (0,9), (0,10), (1,10), (2,10), (4,10), (5,10), (5,9), (5,8), (5,7), (5,6), (5,4), (5,3), (5,2), (5,1), (4,0), (3,0), (2,0), (1,0), (0,0), (0,1)]},
	{'name': '1', 'x': 28, 'y': 0, 'universe': 1556, 'pixels': [(2,2), (2,3), (2,4), (2,4), (2,5), (2,6), (2,7), (2,8), (2,9), (1,8), (0,8), (1,9), (2,10), (2,10), (3,9), (3,8), (3,7), (3,6), (3,5), (3,4), (3,4), (3,3), (3,2), (3,1), (3,0), (2,0), (2,1)]},
	{'name': '3', 'x': 32, 'y': 0, 'universe': 1557, 'pixels': [(0,2), (0,3), (1,4), (1,3), (1,2), (2,1), (3,1), (4,1), (4,2), (4,3), (4,3), (4,4), (4,5), (4,5), (3,5), (2,5), (2,6), (2,7), (3,7), (4,8), (4,9), (4,9), (3,9), (2,9), (1,9), (0,9), (0,10), (1,10), (2,10), (3,10), (4,10), (5,10), (5,9), (5,9), (4,8), (4,7), (3,7), (3,6), (4,6), (5,6), (5,4), (5,4), (5,3), (5,2), (5,1), (4,0), (3,0), (2,0), (1,0), (1,0)]},
]


rdata = {}
gdata = {}
bdata = {}

pixelswide=38
pixelshigh=12

pcount = pixelswide * pixelshigh * 2

class Particle:
	def updateparticle(self):
		# Fire goes from white -> yellow -> deep orange
		d = 45 + random.randint(0, 30)
		if self.rgb[2] >= d:
			self.rgb = (255, 255, self.rgb[2] - d)
		else:
			if self.rgb[1] >= d:
				self.rgb = (255, self.rgb[1] - d, 0)
			else:
				if self.rgb[0] >= d / 5:
					self.rgb = (self.rgb[0] - int(d / 5), self.rgb[1], 0)

		self.y -= self.speed

		intx = int(self.x)
		inty = int(self.y)

		intoarray(intx, pixelshigh - inty - 1, self.rgb)
		if self.y < self.life or self.y < 0.5:
			self.__init__(self.x, pixelshigh)

	def __init__(self, x, y):
		self.rgb = (255,255,random.randint(0,255))
		self.y = y
		self.x = x
		# self.speed = random.uniform(0.05,0.10)
		self.rnderp = id(self) % 12
		self.speed = (self.rnderp / 24) + 1
		self.life = random.uniform(1, pixelshigh)

def cleanarray():
	for i in range(pixelshigh*pixelswide):
		rdata[i] = 0
		gdata[i] = 0
		bdata[i] = 0
			
def intoarray(x, y, rgb):
	rdata[y*pixelswide+x] = rgb[0]
	gdata[y*pixelswide+x] = rgb[1]
	bdata[y*pixelswide+x] = rgb[2]

particles = [Particle(random.randint(0,pixelswide-1), random.randint(0,pixelshigh)) for each in range(pcount)]


while (True):
	cleanarray()
	for i in range(pcount):
		particles[i].updateparticle()
	
	for letter in letters:
		pixels = []
		for (x, y) in letter['pixels']:
			index = (y + letter['y']) * pixelswide + x + letter['x']
			pixels.append((rdata[index], gdata[index], bdata[index]))
		
		sock.sendto(buildPacket(letter['universe'], pixels), (UDP_IP, UDP_PORT))

	time.sleep(0.02)	

sock.close()
