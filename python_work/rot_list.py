
def bin_search(a,key):
	n = len(a)
	l = 0
	u = n

	if n is 0:
		return "Not Found"

	if n is 1:
		if key is a[0]:
			return "Found"
		else:
			return "not found"



	while l < u:

		print l,u
		m = (l+u)/2

		if (u - l) is 1:
			if key is a[u]:
				return "Found"
			elif key is a[l]:
				return "Found"
			else:
				return "Not found"

		if key is a[m]:
			return "Found"
		elif key < a[m]:
			u = m-1
		else:
			l = m+1

	if l == u and l < len(a):
		if key is a[l]:
			return "Found"

	return "Not found"
a = [1,2]

print bin_search(a,1)
#a = a[2:] + a[0:2]
#print a