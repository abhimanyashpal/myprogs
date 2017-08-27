"""
Find the number of hops to reach to 1 

If number is odd then next is 3*n+1 else n = n /2

Eg:

5 ---> 16 ----> 8 ---> 4 ----> 2 ----> 1

Result : 5

"""


def get_next(n):
	if n%2 == 0:
		return n/2
	else:
	    return 3*n+1

#This is not efficient because we are repeating some of the steps already done
# Eg: I may call this API for the first time with 5 , then next time i may call it with
# 8 in which case when we worked on 5 we had already crossed through 8. So if we had
# that result we could return it automatically
def get_hops(n):
	if n is 0 or 1:
		return 0

	hop  = 0
	while n is not 1:
		n = get_next(n)
		hop += 1

	return hop


#Pre-init the dictionary with the last node which is
# 0 hops away from itself
d = {1:0}

def get_hops_optimized(n):

	#create a list used as a stack
	s = []
	if n is 0:
		return 0
	
	#Hash lookup
	if n in d:
		print "Found in HT"
		return d[n]

	hops = 0
	while n not in d:
		s.append(n)
		n = get_next(n)
	#print s

	while s:
		elem = s.pop()
		hops += 1
		d[elem] = hops

	#print d
	return hops




n = 5
print "Hops: " + str(get_hops_optimized(n))

print "======="
n = 16
print "Hops: " + str(get_hops_optimized(n))

print "======="
n = 100
print "Hops: " + str(get_hops_optimized(n))

print "======="
n = 62
print "Hops: " + str(get_hops_optimized(n))

