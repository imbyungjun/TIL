#!/usr/bin/python
import subprocess
import re

class MemInfo :
    def __init__(self) :
        info = re.compile('\d+').findall(getMem())
        self.memTotal = info[0]
        self.memFree = info[1]
        self.buffers = info[2]
        self.cached = info[3]
        self.swapCached = info[4]
        self.active = info[5]
        self.inactive = info[6]

    def printALL(self):
        print 'memTotal =', self.memTotal
        print 'memFree =', self.memFree
        print 'buffers =', self.buffers
        print 'cached =', self.cached
        print 'swapCached =', self.swapCached
        print 'active =', self.active
        print 'inactive =', self.inactive

def getMem():
    out = subprocess.Popen(['head', '-n', '7', '/proc/meminfo'], stdout=subprocess.PIPE)
    return out.stdout.read()

m = MemInfo()

m.printALL()
