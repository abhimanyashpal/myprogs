#!/usr/bin/env python

import socket
import time
import datetime
from thread import *
import threading
import Queue
import select
import os
import signal
import errno
import random

TIMEOUT = 5

do_work = 1

def proc_evt_q(q,pid_list):
    while not q.empty():
        item = q.get()
        pid_list[item[0]] = item[1]
        q.task_done()
        

def proc_pid_list(pid_list):
    start_ts = time.time()
    bad_proc = 0
    for item in pid_list.keys():
        curr_ts = time.time()
        last_seen = pid_list[item]
        delta = curr_ts - last_seen

        if delta > TIMEOUT:
          print "Something wrong with pid %d" % (int(item))
          bad_proc += 1
          #del pid_list[item]

    print "it took", time.time() - start_ts, "seconds."
    print "Dict length", len(pid_list), "Stuck proc ", bad_proc

def timer_thread(q):
    pid_list = {}
    while do_work:
        time.sleep(2)
        #print "Check event queue."
        proc_evt_q(q,pid_list)
        #print "Processed element in queue"
        
        proc_pid_list(pid_list)
        #print pid_list

    print "Killing all processes in list..."
    for item in pid_list.keys():
        cmd = "kill -9 {0}".format(item)
        os.system(cmd)

def my_handler(sig, frame):
   global do_work
   print "Clearing up child processes"
   do_work = 0

q = Queue.Queue()

""" Create a background thread to do work """
timer_t = threading.Thread(target=timer_thread, args=(q,))
timer_t.daemon = True
timer_t.start()


signal.signal(signal.SIGINT, my_handler)
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(('localhost', 10000))

while do_work:
    try:
        data, address = s.recvfrom(4096)

        #print "Received %s bytes from %s" % (len(data), address)

        if data:
            elems = data.split()
            #print elems
            q.put((elems[0],time.time()))
    except socket.error as (code,msg):
        if code != errno.EINTR:
            raise

print "Main thread done"
timer_t.join()
