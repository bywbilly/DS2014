#!/usr/bin/python
import sys
f1=sys.argv[1]
f2=sys.argv[2]
f1=open(f1)
f2=open(f2)
t1=f1.readlines()
t2=f2.readlines()
t=min(len(t1),len(t2))
for i in range(t):
    if t1[i].strip().split()!=t2[i].strip().split():
        print "diff here"
        print "line %d:"%(i+1)
        print t1[i],t2[i]
        exit(0)
if t<len(t1):
    print "file 2 is larger"
elif t<len(t2):
    print "file 1 is larger"
else:
    print "correct"
