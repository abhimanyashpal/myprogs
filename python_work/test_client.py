#!/usr/bin/env python

import socket
import time
import datetime
import sys
import select
import random


#TCP_IP = '2.2.2.101'
TCP_IP = '127.0.0.1'
TCP_PORT = 5005
BUFFER_SIZE = 1024
MESSAGE = "Hello, World!"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
need_close = 0

s_list = []
i = 0
num_socks = 1
while i < num_socks:
     s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
     s.connect((TCP_IP, TCP_PORT))
     s_list.append(s)
     i = i + 1

s_list.append(sys.stdin)
while 1:
    socket_list = s_list

    read_sockets, write_sockets, error_sockets = select.select(socket_list , [], [])

    for sock in read_sockets:
       if sock != sys.stdin:
         data = sock.recv(BUFFER_SIZE)
         print "received data:",data
       else:
         msg = sys.stdin.readline()
         m1 = msg.rstrip()
         if m1 == "abhi":
           print "Client initiating a close"
           need_close = 1
           break

         e = random.randint(0,999)
         i = e % num_socks
         s_list[i].send(msg)

    if need_close == 1:
       break

print "Closing all sockets"
ts = time.time()
st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')
print st + " Client closing the connection"
for s in s_list:
   s.close()
