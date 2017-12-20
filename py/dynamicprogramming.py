#!/usr/bin/python

def get_climbing_ways(stairs):
	if stairs < 1:
		return 0
	
	if stairs == 1:
		return 1
	
	if stairs == 2:
		return 2
	
	a = 1
	b = 2
	ways = 0
	
	for i in range(3, stairs):
		ways = a + b
		a = b
		b = ways
	
	return ways	

if __name__ == '__main__':
	print get_climbing_ways(10)