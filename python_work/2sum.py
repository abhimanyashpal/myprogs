"""
Given a target sum, find the indices of the
2 numbers that give this target sum
"""

def find_indices(arr, target_sum):
	d = {}
	result = []

    
	for elem in arr:
		diff = target_sum - elem

		#Check to see if this number was seen before
		if diff in d:
			result.append(d[diff])
			result.append(arr.index(elem))
			return result
		else:
			d[elem] = arr.index(elem)

	return result


arr = [5, 6, 1 , 3 ,4, 6, 7]

target = 8
res = find_indices(arr,target)
print res


