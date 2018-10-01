

def get_next(n):
	if n%2 == 0:
	  return n/2
	else:
	  return 3*n+1


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

        hops = d[n] #Figure out where we stopped, this could be the last 
                    #node or an intermediate node

        #Now keeping popping the temp elements in the list and update hops
	while s:
		elem = s.pop()
		hops += 1
		d[elem] = hops

	#print d
	return hops



n = 32
print "Hops: " + str(get_hops_optimized(n))

n = 5
print "Hops: " + str(get_hops_optimized(n))

