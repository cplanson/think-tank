#!/usr/bin/python

def max_subArray(l):
	beginning = 0
	end = 0
	sum = 0
	maxBeginning = 0
	maxEnd = 0
	maxSum = sum

	for i in range(len(l)):
		sum += l[i]
		if sum >= maxSum:
			maxBeginning = beginning
			maxEnd = i
			maxSum = sum
		if sum < 0:
			beginning = i + 1
			sum = 0
			
	return (l[maxBeginning:(maxEnd+1)])

print max_subArray([3, -20, 40, -30, 15, 17])
print max_subArray([22, -2, 3, -20, 40, -30, 15, 17])

