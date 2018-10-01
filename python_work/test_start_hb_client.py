import subprocess
import random
import time

pid_list = []
for x in range(1,500):
    p = subprocess.Popen(['python', 'test_hb_client.py','&'])
    pid_list.append(p.pid)


print pid_list

l = len(pid_list)

time.sleep(10)

while 1:
    idx = random.randint(1,10000)
    i = idx%l
    p = pid_list[i]
    cmd = subprocess.Popen(['kill', '-STOP', str(p)])
    #time.sleep(1)
    idx = random.randint(1,10000)
    i = idx%l
    p = pid_list[i]
    cmd = subprocess.Popen(['kill', '-CONT', str(p)])



