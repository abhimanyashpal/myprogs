#!/usr/bin/env python

import socket
import time
import datetime
from thread import *
import threading


def wait_for_data(conn):
   while 1:
       data = conn.recv(20)

       if not data:
         break

       print "TID::",threading.current_thread()
       print "Received: " + data
       conn.send(data)

   print "TID::",threading.current_thread()
   print "Closing conn"
   conn.close()



#TCP_IP='10.54.10.55'
TCP_IP='127.0.0.1'
TCP_PORT = 5005
BUFFER_SIZE = 20

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(500)


while 1:
    conn, addr = s.accept()
    print 'Connection address:', addr
    #ret = wait_for_data(conn)
    start_new_thread(wait_for_data, (conn,))

