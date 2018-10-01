#!/usr/bin/env python

import socket
import time
import datetime
from thread import *
import threading
import os


s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = ('localhost', 10000)

id = os.getpid()
message = str(id) + ' hello'


while 1:
    sent = s.sendto(message,server_address)
    #print "Sent " + str(sent) + "bytes"

    time.sleep(2)

