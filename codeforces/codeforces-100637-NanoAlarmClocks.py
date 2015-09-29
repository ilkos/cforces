#!/usr/bin/env python

import sys

def to_seconds(clock):
	return clock[0] * 1000000000000 + clock[1] * 1000000 + clock[2]

def to_clock(seconds):
	clock = [ 0, 0, 0 ]
	ctr = len(clock) - 1
	while seconds > 0:
		clock[ctr] = seconds % 1000000
		seconds /= 1000000
		ctr -= 1
	return clock

def solve(clocks):
	result = 12000000000000 * 10**5

	# equiv of n^2 loop where we calculate the distance between all clocks
	clock_sum = sum(clocks)
	for i in xrange(len(clocks) - 1, -1, -1):
		pivot = clocks[i]
		c_result = pivot * len(clocks) + 12000000000000 * (len(clocks) - 1 - i) - clock_sum
		result = min(result, c_result)

	return to_clock(result)

if __name__ == "__main__":
	num_clocks = int(sys.stdin.readline())
	clocks = []
	for i in xrange(num_clocks):
		clock = map(lambda x: int(x), sys.stdin.readline().split())
		clocks.append(to_seconds(clock))

	clocks.sort()
	solution = solve(clocks)
	print solution[0], solution[1], solution[2]
