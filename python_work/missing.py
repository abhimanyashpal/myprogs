
"""
Given a array of 'n' elements with numbers in the range of 1-n
There is exactly 1 number missing that we need to find
"""

def find_missing (arr):
	n = len(arr)
	l = 0 
	u = n-1
	m = 0

	while l < u:
		#Compute mid-point
		m = (l+u)/2

		# Only 2 elements are left in the array
		if u-l is 1:
			if arr[u] - arr[l] is not 1:
				return arr[u]-1
			else:
				return -1

		#If the list is sorted then the value should be in
		#it's correct index position Eg: value 1 should be 
		# at index 0 , value 2 should be at index 1

		#Hole in the left array
		if m - l is not arr[m] - arr[l]:
			#Only 2 elements are left
			if m-l is 1 and arr[m]-arr[l] is not 1:
				return arr[m]-1

			#Above condition not satisfied then move to left
			u = m
			continue

		#Hole if right
		if u - m is not arr[u] - arr[m]:
			#2 element case
			if u-m is 1 and arr[u]-arr[m] is not 1:
				return arr[m]+1

			#Move to right
			l = m
			continue

		#No hole present
		return -1

	return -1 #nothing is missing



arr = [1,2,4,5,6]

print find_missing(arr)




