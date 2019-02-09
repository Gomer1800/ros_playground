#!/usr/bin/env python

import sys
import rospy
from beginner_tutorials.srv import *

def add_two_ints_client(x, y):
    # cleint code for calling services is simple
    # clients dont have to call init_node()
    # convenience method that blocks until the service 'add_two_ints' is free
    rospy.wait_for_service('add_two_ints')
    try:
        # create handle, for calling service
        add_two_ints = rospy.ServiceProxy('add_two_ints', AddTwoInts)
        # can use the handle like a normal function
        # because we devclared type of service of type 'AddTwoInts', the serice does 
        # the work of generating the AddTwoIntsREquest object for us (we can still pass in our own instead) 
        resp1 = add_two_ints(x, y)
        return resp1.sum
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e

def usage():
    return "%s [x y]"%sys.argv[0]

if __name__ == "__main__":
    if len(sys.argv) == 3:
        x = int(sys.argv[1])
        y = int(sys.argv[2])
    else:
        print usage()
        sys.exit(1)
    print "Requesting %s+%s"%(x, y)
    print "%s + %s = %s"%(x, y, add_two_ints_client(x, y))
