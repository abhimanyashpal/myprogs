import random
import time


list = []
list_len = 0
count = 0

start_ts = time.time()
k = 48
n = 50
while list_len != k:
    num = random.randint(1,n)
    count += 1
    
    if num not in list:
      list.append(num)
      list_len = len(list)

print list
print "Random generator called ", count
print time.time() - start_ts
