"""
Find the pivot point in a sorted and rotated array

Eg = [3, 4, 5, 1, 2]

The above array is rotated by 2 , the pivot point is index 3

Eg = [1,2,3,4,5]

No pivot here
"""

def find_pivot(arr):
	n  = len(arr)
	l = 0
	u = n-1
	m = 0


	while l < u:
		m = (l+u)/2

		#2 elements left
		if u-l is 1:
			if arr[u] >= arr[l]:
				return -1
			else:
				return u

		#No hole in left
		if arr[m] >= arr[l]:
			l = m
			continue

		#No hole in right
		if arr[m] < arr[u]:
			u = m
			continue

		return -1

	return -1

arr = [3, 4, 5, 1, 2]
arr = [1,2,1]

print find_pivot(arr)
